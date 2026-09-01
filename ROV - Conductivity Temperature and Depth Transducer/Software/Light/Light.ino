/***********************************************************************
 *  ATtiny1614 RS-485 LED Node + WS2812 Ring (FastLED, GRB, ID-prefixed)
 *
 *  PROTOCOL OVERVIEW
 *  =================
 *
 *  Every message (inbound and outbound) has the form:
 *
 *      <ID>/<topic><SEP><value>\n
 *
 *  Where:
 *    - <ID>    : 4-hex-digit Adler-16 of the MCU's unique die ID
 *                (computed from SIGROW.SERNUM0..7, uppercase hex)
 *    - <topic> : ASCII topic string (e.g. "in/main/en", "out/temp")
 *    - <SEP>   : single configurable separator character (':' or '=')
 *    - <value> : ASCII value (integer, float, hex colour, etc.)
 *
 *  Example with CMD_SEP = ':' :
 *    ABCD/in/main/en:1
 *    ABCD/in/main/level:128
 *    ABCD/out/temp:42.3
 *
 *  Example with CMD_SEP = '=' :
 *    ABCD/in/main/en=1
 *    ABCD/in/main/level=128
 *    ABCD/out/temp=42.3
 *
 *  The node:
 *    - Computes its own <ID> at boot from SIGROW.SERNUM0..7
 *    - Sends this <ID> before EVERY outbound message
 *    - Expects EVERY inbound command to start with this same <ID>
 *    - Ignores any message whose <ID> does not match
 *
 *  INBOUND COMMANDS (PC → Node)
 *  ============================
 *
 *    <ID>/in/main/en<SEP>0|1
 *      - 0 → Main LED off
 *      - 1 → Main LED on (subject to thermal derating)
 *
 *    <ID>/in/main/level<SEP>0..255
 *      - Sets requested brightness for Main LED
 *
 *    <ID>/in/builtin/en<SEP>0|1
 *      - Controls the built-in LED on the PCB
 *
 *    <ID>/in/rgb/en<SEP>0|1
 *      - 0 → WS2812 ring off
 *      - 1 → WS2812 ring shows last set colour
 *
 *    <ID>/in/rgb/hex<SEP>#RRGGBB
 *      - Sets WS2812 ring colour (FastLED, GRB order)
 *      - Example: "#FF8000" = orange
 *
 *  OUTBOUND TELEMETRY (Node → PC)
 *  ==============================
 *
 *    <ID>/out/temp<SEP><float>
 *      - Main LED temperature estimate in °C (e.g. "42.3")
 *
 *    <ID>/out/volt<SEP><float>
 *      - VIN after diode, in volts (e.g. "12.1")
 *
 *    <ID>/out/main/pwm<SEP><0..255>
 *      - Actual PWM value currently driving the Main LED
 *
 *    <ID>/out/board/uptime<SEP><seconds>
 *      - Uptime in whole seconds since power-on/reset
 *
 *    <ID>/out/board/health<SEP>temp=..,volt=..,pwm=..,reset=..,uptime=..
 *      - Compact health summary string
 *
 *    <ID>/out/board/reset<SEP><cause>
 *      - Reset cause at boot:
 *          "poweron", "watchdog", "external", "brownout", "unknown"
 *
 *  TIMING / BUS BEHAVIOUR
 *  ======================
 *
 *    - Baud rate: 57600 8N1
 *    - Half-duplex RS-485, direction pin on RS485_DIR_PIN
 *    - Node only transmits when:
 *        * Its own UART RX buffer is empty, AND
 *        * No bytes have been received for BUS_IDLE_MS
 *    - Messages are line-based and terminated with '\n'
 *
 ***********************************************************************/

#include <avr/wdt.h>      // Watchdog timer
#include <avr/io.h>       // For SIGROW access (unique ID)
#include <FastLED.h>      // WS2812 driver
#include <math.h>         // pow() for gamma
#include <string.h>       // strlen, strcmp, strchr, strncpy
#include <stdlib.h>       // atoi, strtoul
#include <stdio.h>        // snprintf

/***********************************************************************
 *  CONFIGURABLE SEPARATOR FOR COMMANDS
 *
 *  Change this to ':' or '=' to switch wire format:
 *    ABCD/in/main/en:1  or  ABCD/in/main/en=1
 ***********************************************************************/
const char CMD_SEP = ':';   // Change to '=' if you prefer

/***********************************************************************
 *  Pin assignment (ATtiny1614, megaTinyCore)
 ***********************************************************************/

const uint8_t MAIN_LED_PIN       = PIN_PA0;   // Main LED PWM (physical pin 2)
const uint8_t STATUS_THERM_PIN   = PIN_PA1;   // Status LED + thermistor (physical pin 3)
const uint8_t BUILTIN_LED_PIN    = PIN_PA2;   // Built-in LED (physical pin 4)
const uint8_t RS485_DIR_PIN      = PIN_PA3;   // RS-485 DE+RE (physical pin 5)
const uint8_t VIN_SENSE_PIN      = PIN_PA4;   // VIN measurement (physical pin 11)
const uint8_t NEOPIXEL_PIN       = PIN_PA5;   // WS2812 ring data (physical pin 13)

/***********************************************************************
 *  VIN measurement configuration
 ***********************************************************************/

// Resistor divider: VIN -> R_TOP -> ADC node -> R_BOTTOM -> GND
const float VIN_R_TOP    = 37000.0f;   // 37k
const float VIN_R_BOTTOM = 12000.0f;   // 12k

// ADC reference and resolution
const float ADC_REF_VOLT  = 5.0f;      // Using VDD as reference
const float ADC_MAX_COUNT = 1023.0f;   // 10-bit ADC

// Expected VIN range
const float VIN_MAX      = 18.0f;
const float VIN_NOMINAL  = 12.6f;
const float VIN_MIN      = 9.6f;

// Latest measured VIN (volts)
float vinMeasured = VIN_NOMINAL;

/***********************************************************************
 *  Temperature / thermistor configuration
 ***********************************************************************/

// Estimated LED temperature in °C
float mainLedTemperatureC = 25.0f;

// ADC-to-temperature mapping (simple linear approximation)
const float TEMP_ADC_MIN = 200.0f;   // ADC count at ~20°C
const float TEMP_ADC_MAX = 800.0f;   // ADC count at ~80°C
const float TEMP_C_MIN   = 20.0f;
const float TEMP_C_MAX   = 80.0f;

/***********************************************************************
 *  Main LED thermal protection
 ***********************************************************************/

const float TEMP_DERATE_START = 55.0f;   // Start reducing brightness
const float TEMP_DERATE_END   = 65.0f;   // Force LED off
const float TEMP_HYSTERESIS   = 2.0f;    // Hysteresis band

// Smoothing factor for PWM transitions (0..1)
const float MAIN_LED_SMOOTHING = 0.15f;

// Soft-start duration (ms)
const uint16_t MAIN_LED_SOFTSTART_MS = 300;

/***********************************************************************
 *  Main LED control state
 ***********************************************************************/

// Current PWM value actually being output (0..255)
uint8_t  mainLedCurrentPwm     = 0;
// Whether we are in thermal shutdown
bool     thermalShutdownActive = false;
// When soft-start began (ms)
uint32_t mainLedSoftStartBegin = 0;
// Whether LED was enabled in previous loop iteration
bool     mainLedWasEnabled     = false;

// Logical control inputs (from RS-485)
uint8_t mainLedEnable = 0;   // 0 = off, 1 = on
uint8_t mainLedLevel  = 255; // Requested brightness (0..255)

/***********************************************************************
 *  Built-in LED state
 ***********************************************************************/

uint8_t builtinLedEnable = 0;

/***********************************************************************
 *  Status LED state (active-LOW, shared with thermistor)
 ***********************************************************************/

uint32_t statusLedLastToggleMs = 0;
const uint16_t STATUS_LED_BLINK_MS = 500;  // 1 Hz blink

// If true, some code wants status LED forced ON
bool statusLedForcedOn = false;

/***********************************************************************
 *  Measurement timing
 ***********************************************************************/

uint32_t lastVinMeasureMs  = 0;
uint32_t lastTempMeasureMs = 0;

const uint16_t VIN_MEASURE_PERIOD_MS  = 200;
const uint16_t TEMP_MEASURE_PERIOD_MS = 200;

/***********************************************************************
 *  RS-485 / Serial state
 ***********************************************************************/

uint32_t lastInboundMs = 0;          // Last time we received a byte
const uint16_t BUS_IDLE_MS = 2;      // Bus idle threshold (ms)

// Simple line buffer for inbound messages
const uint8_t RX_BUFFER_SIZE = 64;
char rxBuffer[RX_BUFFER_SIZE];
uint8_t rxIndex = 0;

/***********************************************************************
 *  Outbound topic scheduler
 ***********************************************************************/

struct OutTopic {
  const char* name;      // Topic name (without ID prefix)
  uint16_t    periodMs;  // How often to send
  uint32_t    nextSendMs;
};

// Outbound topics (note: "out/" prefix is part of the topic name)
OutTopic outTopics[] = {
  { "out/temp",         1000, 0 },
  { "out/volt",         1000, 0 },
  { "out/main/pwm",     1000, 0 },
  { "out/board/uptime", 5000, 0 },
  { "out/board/health", 2000, 0 }
};

const uint8_t OUT_TOPIC_COUNT = sizeof(outTopics) / sizeof(outTopics[0]);

/***********************************************************************
 *  WS2812 ring (FastLED, GRB)
 ***********************************************************************/

#define RGB_LED_COUNT 4

CRGB leds[RGB_LED_COUNT];

// RS-485 controlled state for ring
uint8_t  rgbEnable = 0;        // 0 = off, 1 = on
uint32_t rgbColor  = 0x000000; // 0xRRGGBB

const uint8_t RGB_FIXED_BRIGHTNESS = 64;

/***********************************************************************
 *  Reset cause detection
 ***********************************************************************/

const char* resetCause = "unknown";

/***********************************************************************
 *  Node ID (Adler-16 of unique die ID)
 ***********************************************************************/

// 4-hex-digit string, plus null terminator: "ABCD"
char nodeIdStr[5] = "0000";

/***********************************************************************
 *  Forward declarations
 ***********************************************************************/

void rs485SendLine(const char* topic, const char* value);
void processOutboundTopics();
void buildHealthString(char* out, size_t outSize);

/***********************************************************************
 *  Helper: Compute Adler-16 over a byte array
 ***********************************************************************/

uint16_t adler16(const uint8_t* data, uint8_t len) {
  const uint16_t MOD_ADLER = 251;
  uint16_t a = 1;
  uint16_t b = 0;

  for (uint8_t i = 0; i < len; i++) {
    a = (a + data[i]) % MOD_ADLER;
    b = (b + a)       % MOD_ADLER;
  }

  return (b << 8) | a;  // 16-bit result
}

/***********************************************************************
 *  Helper: Read unique die ID and derive nodeIdStr (4 hex chars)
 ***********************************************************************/

void initNodeIdFromSigrow() {
  uint8_t uid[8];

  uid[0] = SIGROW.SERNUM0;
  uid[1] = SIGROW.SERNUM1;
  uid[2] = SIGROW.SERNUM2;
  uid[3] = SIGROW.SERNUM3;
  uid[4] = SIGROW.SERNUM4;
  uid[5] = SIGROW.SERNUM5;
  uid[6] = SIGROW.SERNUM6;
  uid[7] = SIGROW.SERNUM7;

  uint16_t checksum = adler16(uid, 8);

  // Format as 4 hex digits, e.g. "1A2F"
  snprintf(nodeIdStr, sizeof(nodeIdStr), "%04X", checksum);
}

/***********************************************************************
 *  Helper: Detect reset cause (watchdog, power-on, etc.)
 ***********************************************************************/

void detectResetCause() {
  uint8_t flags = RSTCTRL.RSTFR;

  if (flags & RSTCTRL_WDRF_bm)      resetCause = "watchdog";
  else if (flags & RSTCTRL_PORF_bm) resetCause = "poweron";
  else if (flags & RSTCTRL_EXTRF_bm)resetCause = "external";
  else if (flags & RSTCTRL_BORF_bm) resetCause = "brownout";
  else                              resetCause = "unknown";

  // Clear flags so they don't accumulate
  RSTCTRL.RSTFR = 0xFF;
}

/***********************************************************************
 *  Helper: Gamma correction (perceptual brightness)
 ***********************************************************************/

uint8_t gammaCorrect(uint8_t level) {
  float normalized = level / 255.0f;
  float corrected  = pow(normalized, 2.2f);
  return (uint8_t)(corrected * 255.0f);
}

/***********************************************************************
 *  Helper: VIN compensation for Main LED brightness
 ***********************************************************************/

uint8_t applyVinCompensation(uint8_t level, float vin) {
  if (vin < VIN_MIN) vin = VIN_MIN;
  if (vin > VIN_MAX) vin = VIN_MAX;
  if (vin <= 0.1f)   return level;

  float scale = VIN_NOMINAL / vin;
  if (scale < 0.5f) scale = 0.5f;
  if (scale > 1.5f) scale = 1.5f;

  float adjusted = level * scale;
  if (adjusted > 255.0f) adjusted = 255.0f;
  if (adjusted < 0.0f)   adjusted = 0.0f;

  return (uint8_t)adjusted;
}

/***********************************************************************
 *  Helper: Thermal derating with hysteresis
 ***********************************************************************/

uint8_t applyThermalDerating(uint8_t level, float tempC) {
  // Handle shutdown region with hysteresis
  if (thermalShutdownActive) {
    if (tempC < TEMP_DERATE_END - TEMP_HYSTERESIS) {
      thermalShutdownActive = false;
    } else {
      return 0;
    }
  } else {
    if (tempC >= TEMP_DERATE_END) {
      thermalShutdownActive = true;
      return 0;
    }
  }

  // Below derate start → no change
  if (tempC <= TEMP_DERATE_START)
    return level;

  // Between start and end → linearly scale down to 0
  float scale = 1.0f - ((tempC - TEMP_DERATE_START) /
                        (TEMP_DERATE_END - TEMP_DERATE_START));
  if (scale < 0.0f) scale = 0.0f;
  if (scale > 1.0f) scale = 1.0f;

  float adjusted = level * scale;
  if (adjusted < 0.0f)   adjusted = 0.0f;
  if (adjusted > 255.0f) adjusted = 255.0f;

  return (uint8_t)adjusted;
}

/***********************************************************************
 *  Helper: Smooth PWM transitions (exponential moving average)
 ***********************************************************************/

uint8_t smoothPwm(uint8_t target) {
  float smoothed = (MAIN_LED_SMOOTHING * target) +
                   ((1.0f - MAIN_LED_SMOOTHING) * mainLedCurrentPwm);
  mainLedCurrentPwm = (uint8_t)smoothed;
  return mainLedCurrentPwm;
}

/***********************************************************************
 *  Helper: Soft-start scale factor (0..1)
 ***********************************************************************/

float softStartScale() {
  uint32_t now = millis();
  uint32_t elapsed = now - mainLedSoftStartBegin;

  if (elapsed >= MAIN_LED_SOFTSTART_MS)
    return 1.0f;

  return (float)elapsed / (float)MAIN_LED_SOFTSTART_MS;
}

/***********************************************************************
 *  VIN measurement (periodic)
 ***********************************************************************/

void measureVin() {
  uint32_t now = millis();
  if (now - lastVinMeasureMs < VIN_MEASURE_PERIOD_MS)
    return;

  lastVinMeasureMs = now;

  pinMode(VIN_SENSE_PIN, INPUT);
  analogReference(VDD);

  uint16_t adc = analogRead(VIN_SENSE_PIN);
  float vAdc = (adc / ADC_MAX_COUNT) * ADC_REF_VOLT;

  // Divider ratio
  float dividerRatio = VIN_R_BOTTOM / (VIN_R_TOP + VIN_R_BOTTOM);

  vinMeasured = vAdc / dividerRatio;
}

/***********************************************************************
 *  Temperature measurement (thermistor on STATUS_THERM_PIN)
 ***********************************************************************/

void measureTemperature() {
  uint32_t now = millis();
  if (now - lastTempMeasureMs < TEMP_MEASURE_PERIOD_MS)
    return;

  lastTempMeasureMs = now;

  // If status LED is forced ON, don't disturb the pin
  if (statusLedForcedOn)
    return;

  pinMode(STATUS_THERM_PIN, INPUT);
  analogReference(VDD);

  uint16_t adc = analogRead(STATUS_THERM_PIN);
  float adcF = (float)adc;

  if (adcF <= TEMP_ADC_MIN) {
    mainLedTemperatureC = TEMP_C_MIN;
  } else if (adcF >= TEMP_ADC_MAX) {
    mainLedTemperatureC = TEMP_C_MAX;
  } else {
    float t = (adcF - TEMP_ADC_MIN) / (TEMP_ADC_MAX - TEMP_ADC_MIN);
    mainLedTemperatureC = TEMP_C_MIN + t * (TEMP_C_MAX - TEMP_C_MIN);
  }
}

/***********************************************************************
 *  Status LED control (heartbeat, active-LOW)
 ***********************************************************************/

void updateStatusLed() {
  if (statusLedForcedOn) {
    pinMode(STATUS_THERM_PIN, OUTPUT);
    digitalWrite(STATUS_THERM_PIN, LOW);  // ON (active-LOW)
    return;
  }

  uint32_t now = millis();
  if (now - statusLedLastToggleMs >= STATUS_LED_BLINK_MS) {
    statusLedLastToggleMs = now;

    pinMode(STATUS_THERM_PIN, OUTPUT);
    int current = digitalRead(STATUS_THERM_PIN);

    if (current == LOW)
      digitalWrite(STATUS_THERM_PIN, HIGH); // OFF
    else
      digitalWrite(STATUS_THERM_PIN, LOW);  // ON
  }
}

/***********************************************************************
 *  Built-in LED control
 ***********************************************************************/

void updateBuiltinLed() {
  pinMode(BUILTIN_LED_PIN, OUTPUT);
  digitalWrite(BUILTIN_LED_PIN, builtinLedEnable ? HIGH : LOW);
}

/***********************************************************************
 *  Main LED control (gamma, VIN, thermal, soft-start, smoothing)
 ***********************************************************************/

void updateMainLed() {
  pinMode(MAIN_LED_PIN, OUTPUT);

  if (mainLedEnable == 0) {
    mainLedCurrentPwm = 0;
    mainLedWasEnabled = false;
    analogWrite(MAIN_LED_PIN, 0);
    return;
  }

  if (!mainLedWasEnabled) {
    mainLedWasEnabled = true;
    mainLedSoftStartBegin = millis();
    mainLedCurrentPwm = 0;
  }

  uint8_t corrected = gammaCorrect(mainLedLevel);
  corrected = applyVinCompensation(corrected, vinMeasured);
  corrected = applyThermalDerating(corrected, mainLedTemperatureC);

  float ss = softStartScale();
  corrected = (uint8_t)(corrected * ss);

  corrected = smoothPwm(corrected);

  analogWrite(MAIN_LED_PIN, corrected);
}

/***********************************************************************
 *  Hex colour parsing: "#RRGGBB" → 0xRRGGBB
 ***********************************************************************/

uint32_t parseHexColor(const char* hex) {
  if (hex[0] != '#' || strlen(hex) != 7)
    return 0x000000;

  char rStr[3] = { hex[1], hex[2], '\0' };
  char gStr[3] = { hex[3], hex[4], '\0' };
  char bStr[3] = { hex[5], hex[6], '\0' };

  uint8_t r = (uint8_t)strtoul(rStr, NULL, 16);
  uint8_t g = (uint8_t)strtoul(gStr, NULL, 16);
  uint8_t b = (uint8_t)strtoul(bStr, NULL, 16);

  return (uint32_t)((r << 16) | (g << 8) | b);
}

/***********************************************************************
 *  WS2812 ring update (FastLED, GRB)
 ***********************************************************************/

void updateNeopixelRing() {
  if (!rgbEnable) {
    for (uint8_t i = 0; i < RGB_LED_COUNT; i++)
      leds[i] = CRGB::Black;
    FastLED.show();
    return;
  }

  uint8_t r = (rgbColor >> 16) & 0xFF;
  uint8_t g = (rgbColor >> 8)  & 0xFF;
  uint8_t b = (rgbColor)       & 0xFF;

  for (uint8_t i = 0; i < RGB_LED_COUNT; i++)
    leds[i] = CRGB(r, g, b);

  FastLED.show();
}

/***********************************************************************
 *  RS-485 helpers (direction control + bus idle detection)
 ***********************************************************************/

void rs485ReceiveMode() {
  pinMode(RS485_DIR_PIN, OUTPUT);
  digitalWrite(RS485_DIR_PIN, LOW);  // DE=0, RE=0 → receive
}

void rs485TransmitMode() {
  pinMode(RS485_DIR_PIN, OUTPUT);
  digitalWrite(RS485_DIR_PIN, HIGH); // DE=1, RE=1 → transmit
  delayMicroseconds(10);             // Allow transceiver to turn around
}

bool isBusIdle() {
  uint32_t now = millis();
  if (Serial.available() > 0) return false;
  if (now - lastInboundMs < BUS_IDLE_MS) return false;
  return true;
}

/***********************************************************************
 *  RS-485 receive: parse "<ID>/<topic><SEP><value>\n"
 ***********************************************************************/

void handleInboundLine(const char* line) {
  // Find separator (CMD_SEP) between "<ID>/<topic>" and "<value>"
  const char* sep = strchr(line, CMD_SEP);
  if (!sep) return;

  // Copy left side into topicBuf (includes ID and topic)
  char topicBuf[32];
  size_t topicLen = sep - line;
  if (topicLen >= sizeof(topicBuf)) topicLen = sizeof(topicBuf) - 1;
  strncpy(topicBuf, line, topicLen);
  topicBuf[topicLen] = '\0';

  // Copy right side into valueBuf
  char valueBuf[32];
  strncpy(valueBuf, sep + 1, sizeof(valueBuf) - 1);
  valueBuf[sizeof(valueBuf) - 1] = '\0';

  // Strip CR/LF from value
  for (int i = 0; valueBuf[i]; i++) {
    if (valueBuf[i] == '\r' || valueBuf[i] == '\n') {
      valueBuf[i] = '\0';
      break;
    }
  }

  // topicBuf is "<ID>/<topic>". Split at '/'
  char* slash = strchr(topicBuf, '/');
  if (!slash) return;  // No '/', invalid

  *slash = '\0';       // topicBuf now "<ID>", slash+1 is "<topic>"
  const char* idPart    = topicBuf;
  const char* topicPart = slash + 1;

  // Check ID matches our nodeIdStr
  if (strcmp(idPart, nodeIdStr) != 0) {
    // Not for us → ignore
    return;
  }

  // Now topicPart is e.g. "in/main/en"
  const char* topic = topicPart;
  const char* value = valueBuf;

  // Main LED enable
  if (strcmp(topic, "in/main/en") == 0) {
    mainLedEnable = (uint8_t)atoi(value);
  }
  // Main LED brightness
  else if (strcmp(topic, "in/main/level") == 0) {
    int v = atoi(value);
    if (v < 0) v = 0;
    if (v > 255) v = 255;
    mainLedLevel = (uint8_t)v;
  }
  // Built-in LED enable
  else if (strcmp(topic, "in/builtin/en") == 0) {
    builtinLedEnable = (uint8_t)atoi(value);
  }
  // WS2812 ring enable
  else if (strcmp(topic, "in/rgb/en") == 0) {
    rgbEnable = (uint8_t)atoi(value);
  }
  // WS2812 ring colour (#RRGGBB)
  else if (strcmp(topic, "in/rgb/hex") == 0) {
    rgbColor = parseHexColor(value);
  }
  // Add more inbound topics here if needed
}

void pollRs485Rx() {
  while (Serial.available() > 0) {
    int c = Serial.read();
    lastInboundMs = millis();

    if (c == '\n') {
      // End of line → terminate and process
      rxBuffer[rxIndex] = '\0';
      handleInboundLine(rxBuffer);
      rxIndex = 0;
    } else {
      if (rxIndex < RX_BUFFER_SIZE - 1) {
        rxBuffer[rxIndex++] = (char)c;
      }
      // If overflow, extra chars are dropped until next '\n'
    }
  }
}

/***********************************************************************
 *  RS-485 send: "<ID>/<topic><SEP><value>\n"
 ***********************************************************************/

void rs485SendLine(const char* topic, const char* value) {
  if (!isBusIdle())
    return;

  rs485TransmitMode();

  // Prefix with node ID and '/'
  Serial.print(nodeIdStr);
  Serial.print('/');
  Serial.print(topic);
  Serial.print(CMD_SEP);
  Serial.println(value);

  Serial.flush();
  rs485ReceiveMode();
}

/***********************************************************************
 *  Board health string builder
 ***********************************************************************/

void buildHealthString(char* out, size_t outSize) {
  uint32_t uptimeSec = millis() / 1000;

  snprintf(out, outSize,
           "temp=%.1f,volt=%.1f,pwm=%u,reset=%s,uptime=%lu",
           mainLedTemperatureC,
           vinMeasured,
           mainLedCurrentPwm,
           resetCause,
           (unsigned long)uptimeSec);
}

/***********************************************************************
 *  Outbound topic scheduler
 ***********************************************************************/

void processOutboundTopics() {
  uint32_t now = millis();
  char value[64];

  for (uint8_t i = 0; i < OUT_TOPIC_COUNT; i++) {
    OutTopic &t = outTopics[i];
    if (now < t.nextSendMs) continue;

    t.nextSendMs = now + t.periodMs;

    if (strcmp(t.name, "out/temp") == 0) {
      snprintf(value, sizeof(value), "%.1f", mainLedTemperatureC);
      rs485SendLine("out/temp", value);
    } else if (strcmp(t.name, "out/volt") == 0) {
      snprintf(value, sizeof(value), "%.1f", vinMeasured);
      rs485SendLine("out/volt", value);
    } else if (strcmp(t.name, "out/main/pwm") == 0) {
      snprintf(value, sizeof(value), "%u", mainLedCurrentPwm);
      rs485SendLine("out/main/pwm", value);
    } else if (strcmp(t.name, "out/board/uptime") == 0) {
      uint32_t uptimeSec = millis() / 1000;
      snprintf(value, sizeof(value), "%lu", (unsigned long)uptimeSec);
      rs485SendLine("out/board/uptime", value);
    } else if (strcmp(t.name, "out/board/health") == 0) {
      buildHealthString(value, sizeof(value));
      rs485SendLine("out/board/health", value);
    }
  }
}

/***********************************************************************
 *  setup()
 ***********************************************************************/

void setup() {
  // Compute node ID from unique die ID
  initNodeIdFromSigrow();

  // Configure RS-485 direction pin and UART
  pinMode(RS485_DIR_PIN, OUTPUT);
  rs485ReceiveMode();
  Serial.begin(57600);

  // Detect reset cause
  detectResetCause();

  // FastLED setup (WS2812B, GRB)
  FastLED.addLeds<WS2812B, NEOPIXEL_PIN, GRB>(leds, RGB_LED_COUNT);
  FastLED.setBrightness(RGB_FIXED_BRIGHTNESS);
  for (uint8_t i = 0; i < RGB_LED_COUNT; i++)
    leds[i] = CRGB::Black;
  FastLED.show();

  // Main LED off
  pinMode(MAIN_LED_PIN, OUTPUT);
  analogWrite(MAIN_LED_PIN, 0);

  // Built-in LED off
  pinMode(BUILTIN_LED_PIN, OUTPUT);
  digitalWrite(BUILTIN_LED_PIN, LOW);

  // Status LED off (active-LOW)
  pinMode(STATUS_THERM_PIN, OUTPUT);
  digitalWrite(STATUS_THERM_PIN, HIGH);

  // Initialise outbound topic timers
  uint32_t now = millis();
  for (uint8_t i = 0; i < OUT_TOPIC_COUNT; i++) {
    outTopics[i].nextSendMs = now + outTopics[i].periodMs;
  }

  // Enable watchdog (1s timeout)
  wdt_enable(WDTO_1S);

  // Send reset cause once at boot
  rs485SendLine("out/board/reset", resetCause);
}

/***********************************************************************
 *  loop()
 ***********************************************************************/

void loop() {
  // Kick watchdog
  wdt_reset();

  // Handle inbound RS-485
  pollRs485Rx();

  // Periodic measurements
  measureVin();
  measureTemperature();

  // LED updates
  updateMainLed();
  updateBuiltinLed();
  updateStatusLed();
  updateNeopixelRing();

  // Outbound telemetry
  processOutboundTopics();
}
/*!
 * @file Arduino.ino
 *
 * @mainpage 
 *
 * @section intro_sec Introduction
 *
 * This is the documentation for ChargePoint's Mimic Octopus firmware. 
 * * It is specific to the FDC2.0 testers.
 *
 * @section dependencies Dependencies
 *
 * Dependancys for this firmware should be in the folder src 
 *
 * @section author Author
 *
 * Written by Philip McGaw - philip.mcgaw@chargepoint.com
 *
 * @section license License
 *
 * Copyright ChargePoint 2022 - All rights reserved.
 *
 */

#include <Arduino.h>
#include "src/ArduinoUniqueID/ArduinoUniqueID.h"
#include "src/Vrekrer_scpi_parser/Vrekrer_scpi_parser.h"

/*  
  This is the pin mapping for MimicOctopus. for the FDC 2.0 testers
*/

const byte HEART_LED = 13;       ///< This is the Pin the Heartbeat LED is on. \n\n Pin 13 is the built in LED pin on the Mega 2560. \n\n This is part of heartBeat().
const byte HEART_BEAT = 1;       ///< The Frequancy of the HeartBeat LED (in Hz). \n\n This is part of heartBeat().
bool heartBeatState = false;     ///< Stores the current state of the Heartbeat LED. \n\n This is part of heartBeat().
unsigned long previousBeat = 0;  ///< Stores the last change of state time for the HeartBeat. \n\n This is part of heartBeat().

const byte SDA_PIN = 20;  ///< The Pins that the I2C SDA Pin is pinned to.
const byte SCL_PIN = 21;  ///< The Pins that the I2C SCL Pin is pinned to.

const byte DATA_PIN = 23;
const byte LATCH_PIN = 25;
const byte CLOCK_PIN = 27;

const byte RELAY_COUNT = 150;  ///< Count of how many shift registers there are in total.
bool relayState[RELAY_COUNT];  ///< Array for storing state of the relay array in.

const byte V3_3_TEST = A0;  ///< Netname 3V3_TEST - 3V3 rail Pin name.
float v3_3_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float v3_3_Value = 0.0; ///< 3V3 Voltage value

const byte V5_TEST = A2;    ///< Netname 5v_TEST - 5V rail Pin name.
float v5_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float v5_Value = 0.0; ///< 5 Voltage value

const byte V12_TEST = A1;   ///< Netname 12V_TEST - 12V rail Pin name.
float v12_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float v12_Value = 0.0; ///< 12 Voltage value

const byte DUT_V_MON = A15; ///< DUT supply Voltage monitor Pin
float DUT_V_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float DUT_V_Value = 0.0; ///< DUT supply voltage value (This Voltage measurment is shared between channels 1 and 2).

const byte DUT_I_MON1 = A9; ///< DUT supply 1 current monitor Pin
float DUT_I_Mon1_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float DUT_I_Mon1_Value = 0.0; ///< DUT supply 1 supply current value

const byte DUT_I_MON2 = A10; ///< DUT supply 2 current monitor Pin
float DUT_I_Mon2_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float DUT_I_Mon2_Value = 0.0; ///<DUT supply 2 supply current value

const byte EQ_V_MON1 = A14; ///< External equipment Channel 1 Voltage monitor Pin
float EQ_V_Mon1_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float EQ_V_Mon1_Value = 0.0; ///< External equipment Channel 1 Voltage value

const byte EQ_I_MON1 = A8; ///< External equipment Channel 1 current monitor Pin
float EQ_I_Mon1_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float EQ_I_Mon1_Value = 0.0; ///< External equipment Channel 1 current value

const byte EQ_V_MON2 = A13; ///< External equipment Channel 2 Voltage monitor Pin
float EQ_V_Mon2_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float EQ_V_Mon2_Value = 0.0; ///< External equipment Channel 2 Voltage value

const byte EQ_I_MON2 = A7; ///< External equipment Channel 2 current monitor Pin
float EQ_I_Mon2_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float EQ_I_Mon2_Value = 0.0; ///< External equipment Channel 2 current value

const byte EQ_V_MON3 = A12; ///< External equipment Channel 3 Voltage monitor Pin
float EQ_V_Mon3_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float EQ_V_Mon3_Value = 0.0; ///< External equipment Channel 3 Voltage value

const byte EQ_I_MON3 = A6; ///< External equipment Channel 3 current monitor Pin
float EQ_I_Mon3_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float EQ_I_Mon3_Value = 0.0; ///< External equipment Channel 3 current value

const byte EQ_V_MON4 = A11; ///< External equipment Channel 4 Voltage monitor Pin
float EQ_V_Mon4_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float EQ_V_Mon4_Value = 0.0; ///< External equipment Channel 4 Voltage value

const byte EQ_I_MON4 = A5; ///< External equipment Channel 4 current monitor Pin
float EQ_I_Mon4_Calibration = 0.0; ///< Calibration value for getting correct value (Will need to read in from eprom in future).
float EQ_I_Mon4_Value = 0.0; ///< External equipment Channel 4 current value



const byte AIN3 = A3;
const byte AIN4 = A4;

const byte RAG1 = 36;    ///< 12V out for RAG LEDs. \n\n RAG 1 = 0, Rag 2 = 0, RED \n RAG 1 = 1, Rag 2 = 0, check \n RAG 1 = 0, Rag 2 = 1, check \n RAG 1 = 1, Rag 2 = 1, check \n\n There are two relays, that control these three light states.
const byte RAG2 = 37;    ///< 12V out for RAG LEDs, See #RAG1 for further details.
const byte Enable = 38;  ///< Dry contacts on the edge of the board for enabling external equipment.

const byte ESTOP_PIN = 10;  ///< Pin that eStop is on.
bool eStopPressed = LOW;    ///< eStop status flag.

const byte DOOR_CLOSED = 6;
const byte INTERLOCK_LOOP = 5;
const byte TEST_START = 4;

const byte CIO0 = 22;
const byte CIO1 = 12;
const byte CIO2 = 11;
const byte CIO3 = 10;

const byte EIO0 = 9;
const byte EIO1 = 8;
const byte EIO2 = 7;

const byte EIO6 = 3;
const byte EIO7 = 2;

const byte FIO3 = 39;
const byte FIO4 = 40;
const byte FIO5 = 41;
const byte FIO6 = 42;
const byte FIO7 = 43;

const byte MIO0 = 44;
const byte MIO1 = 45;
const byte MIO2 = 46;

// SCPI IDN Response

const String COPYRIGHT = "ChargePoint 2022";      ///< Copyright company and year. \n\n Part of the *IDN? response. See identify().
const String PRODUCT = "CIB - MimicOctopus";      ///< Project name. \n\n Part of the *IDN? response. See identify().
const String SOFTWAREREV = "0.1";                 ///< Firmware version. \n\n Part of the *IDN? response. See identify().
int hardwareRev = "-1";                           ///< Takes the value of the #VERSION_PINS. \n\n Part of the *IDN? response. See identify().
const byte VERSION_PINS[4] = { 50, 51, 52, 53 };  ///< The Pins that the hardware version is pinned to, Values are fed into #hardwareRev.
const String DIVIDER = ", ";                      ///< String divider. \n\n Part of the *IDN? response. See identify().

SCPI_Parser cib;  ///<  loads the SCPI_Parser function in as cib


/**
 * The standard Arduino setup function used for setup and configuration tasks.
 * 
 * Sets the pinmodes, 
 */
void setup() {
  initScpi();
  Serial.begin(9600);

  pinMode(HEART_LED, OUTPUT);

  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);

  clearRelayState();

  pinMode(V3_3_TEST, INPUT);
  pinMode(V5_TEST, INPUT);
  pinMode(V12_TEST, INPUT);

  pinMode(DUT_V_MON, INPUT);
  pinMode(DUT_I_MON1, INPUT);
  pinMode(DUT_I_MON2, INPUT);

  pinMode(EQ_V_MON1, INPUT);
  pinMode(EQ_I_MON1, INPUT);
  pinMode(EQ_V_MON2, INPUT);
  pinMode(EQ_I_MON2, INPUT);
  pinMode(EQ_V_MON3, INPUT);
  pinMode(EQ_I_MON3, INPUT);
  pinMode(EQ_V_MON4, INPUT);
  pinMode(EQ_I_MON4, INPUT);

  for (int i = 0; i < sizeof(VERSION_PINS); i++) {
    pinMode(VERSION_PINS[i], INPUT);
  }
}


/**
 * @brief Loop
 * The standard Arduino loop function used for repeating tasks.
 * 
 * heartBeat()
 * SCPI management
 * relays()
 */
void loop() {
  heartBeat();
  cib.ProcessInput(Serial, "\n");
  relays();
}

/** 
 * @brief eStop,
 * 
 * This checks the state of the eStop #ESTOP_PIN on each run round the loop. 
 * 
 * If the eStop has been pressed then the relays are all set to open using clearRelayState() and set the #eStopPressed flag.
 * 
 */
void eStop() {
  digitalRead(ESTOP_PIN);
  eStopPressed == HIGH;
  clearRelayState();
}

/**
 * @brief Set relays off
 * 
 */
void clearRelayState() {
  digitalWrite(LATCH_PIN, LOW);
  for (int i = 0; i < sizeof(relayState) + 1; i++) {
    // Fills the value on the array with a zero, then writes that value out.
    relayState[i] == LOW;
    digitalWrite(DATA_PIN, relayState[i]);
    // Toggle the clock
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }
  // bring the latches back up;
  digitalWrite(LATCH_PIN, HIGH);
}

/**
 * Sets up the SCPI command tree
 * 
 * Use <index> at the end of a token to accept numeric suffixes.
 * 
 *   * *IDN? - Identification. See identify().
 *   * *RST - Resets the CIB to initial state. See hardReset().
 *   * MEASure:VOLTage:
 *     * DUT? - Returns the supply voltage to the DUT. See getVoltDUT().
 *     * EQUIpment<index>? - Returns the voltage on the external equipment channels. See getVoltEquipment().
 *     * CIB? - Returns the voltage on the external equipment channels. See getVoltCIB().
 *   * MEASure:CURRent:
 *     * DUT? - Returns the supply Current to the DUT. See getCurDUT().
 *     * Equipment<index>? - Returns the voltage on the external equipment channels. See getCurEquipment().
 */
void initScpi() {
  cib.RegisterCommand(F("*IDN?"), &identify);
  cib.RegisterCommand(F("*RST"), &hardReset);

  cib.SetCommandTreeBase(F("MEASure:VOLTage"));
  cib.RegisterCommand(F(":DUT?"), &getVoltDUT);
  cib.RegisterCommand(F(":EQUIpment#?"), &getVoltEquipment);
  cib.RegisterCommand(F(":CIB#?"), &getVoltCIB);

  cib.SetCommandTreeBase(F(":MEASure:CURRent"));
  cib.RegisterCommand(F(":DUT#?"), &getCurDUT);
  cib.RegisterCommand(F(":EQUIpment#?"), &getCurEquipment);
}

/**
 * Respond to *IDN?
 * 
 * Returns the Manufacturer, hardware type, software version, and a serial number.
 * (This serial number is different to the one from the one of the USB/Serial converter.)
 * 
 * This value is made up of the followning: #COPYRIGHT, #PRODUCT, SW: #SOFTWAREREV, HW: #hardwareRev, SN: <UniqueID>.
 *
 * This is part of initScpi().
 */
void identify(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  byte hardwareRev;
  for (int i = 0; sizeof(VERSION_PINS); i++) {
    hardwareRev |= (digitalRead(VERSION_PINS[i]) << i);
  }
  interface.print(COPYRIGHT + DIVIDER + PRODUCT + DIVIDER + "SW:" + SOFTWAREREV + DIVIDER + "HW:" + hardwareRev + DIVIDER + "SN:");
  for (size_t i = 0; i < UniqueIDsize; i++) {
    interface.print(UniqueID[i], HEX);
  }
  interface.println(F(""));
}

/**
 * Respond to *RST
 *
 * Resets the CIB to initial state
 * 
 * The code contains a delay of one second, this is required to allow for entire string to be sent over serial.
 *
 * \todo Needs to be implimented in hardware!
 * \todo Set all relays to open, before restarting.
 *
 * This is part of initScpi().
 */
void hardReset(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  interface.print("Resetting");
  delay(1000);
}

/**
 * Respond to MEAS:VOLT:EQUIpment<index>?
 * 
 * Queries the voltage on <index>
 *
 * Return values are Analouge values, normalised to the expected voltage of the line being read.
 * 
 * Examples:
 * 
 * MEAS:VOLT:EQUP1? - Queries the Equipment Chanel 1
 *
 * This is part of initScpi().
 */
void getVoltEquipment(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  //Get the numeric suffix/index (if any) from the commands
  String header = String(commands.Last());
  header.toUpperCase();
  int suffix = -1;
  sscanf(header.c_str(), "%*[MEAS:VOLT]%u", &suffix);
  if (suffix = 1) {
    EQ_V_Mon1_Value == readVoltageValue(EQ_V_MON1, EQ_V_Mon1_Calibration);    
  } else if (suffix = 2) {
    EQ_V_Mon2_Value == readVoltageValue(EQ_V_MON2, EQ_V_Mon2_Calibration);
  } else if (suffix = 3) {
    EQ_V_Mon3_Value == readVoltageValue(EQ_V_MON2, EQ_V_Mon3_Calibration);
  } else if (suffix = 4) {
    EQ_V_Mon4_Value == readVoltageValue(EQ_V_MON2, EQ_V_Mon4_Calibration);
  }
}


/**
 * Respond to MEAS:VOLT:CIB?
 *
 * Return values are Analouge values, normalised to the expected voltage of the line being read.
 * 
 * Examples:
 * 
 * MEAS:VOLT:CIB? - Returns the value of the voltage on the three voltage rails as CSV string. (3V3, 5V, 12V)
 *
 * This is part of initScpi().
 */
void getVoltCIB(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  // This command has no peramiters
  interface.println(readVoltageValue(V3_3_TEST, 3.3) + DIVIDER + readVoltageValue(V5_TEST, 5) + DIVIDER + readVoltageValue(V12_TEST, 12));
}

/**
 * Respond to MEAS:VOLT:DUT?
 *
 * Queries the voltage on the DUT supply
 *
 * Return values are Analouge values, normalised to the expected voltage of the line being read.
 *
 * Examples:
 * 
 * MEAS:VOLT:DUT? -  Queries DUT supply Voltage
 *
 * This is part of initScpi().
*/
void getVoltDUT(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  // This command has no peramiters
  interface.println(readVoltageValue(DUT_V_MON, 12));
}

/**
 * Respond to MEAS:CURR:EQUIpment<index>?
 *
 * Queries the current on the equipment channel
 *
 * Returned value is the current, either +ve or -ve of the channel being quired.
 *
 * Examples:
 * 
 * MEAS:CURR:EQUI1? -  Queries DUT supply Voltage
 *
 * This is part of initScpi().
*/
void getCurEquipment(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  //Get the numeric suffix/index (if any) from the commands
  String header = String(commands.Last());
  header.toUpperCase();
  int suffix = -1;
  sscanf(header.c_str(), "%*[MEAS:VOLT]%u", &suffix);
  if (suffix = 1) {
    interface.println(readCurrentValue(EQ_I_MON1, 12));
  } else if (suffix = 2) {
    interface.println(readCurrentValue(EQ_I_MON2, 12));
  } else if (suffix = 3) {
    interface.println(readCurrentValue(EQ_I_MON3, 12));
  } else if (suffix = 4) {
    interface.println(readCurrentValue(EQ_I_MON4, 12));
  }
}

/**
 * Respond to MEAS:CURR:DUT<index>?
 *
 * Queries the current on the DUT channel
 *
 * Returned value is the current, either +ve or -ve of the channel being quired.
 *
 * Examples:
 * 
 * MEAS:CURR:DUT1? -  Queries DUT supply current of DUT Channel 1
 *
 * This is part of initScpi().
*/
void getCurDUT(SCPI_C commands, SCPI_P parameters, Stream& interface) {
  //Get the numeric suffix/index (if any) from the commands
  String header = String(commands.Last());
  header.toUpperCase();
  int suffix = -1;
  sscanf(header.c_str(), "%*[MEAS:VOLT]%u", &suffix);
  if (suffix = 1) {
    interface.println(readCurrentValue(DUT_I_MON1, 12));
  } else if (suffix = 2) {
    interface.println(readCurrentValue(DUT_I_MON2, 12));
  }
}

/**
 * Flashes the #HEART_LED at #HEART_BEAT, This flashing is to confirm the processor is still running.
 */
void heartBeat() {
  if (millis() - previousBeat >= 500) {
    // save the last time you blinked the LED
    previousBeat = millis();

    // if the LED is off turn it on and vice-versa:
    if (heartBeatState == false) {
      heartBeatState = true;
    } else {
      heartBeatState = false;
    }
    digitalWrite(HEART_LED, heartBeatState);
  }
}

/** 
 * @brief readVoltageValue,
 * 
 * readVoltageValue manages the reading in of analouge pins (Voltage).
 */
float readVoltageValue(byte pinNumber, float calibration) {
  float voltage = ((float(analogRead(pinNumber) / 1023.0) * 5.0) * calibration);
}

/** 
 * @brief readCurrentValue,
 * 
 * readCurrentValue manages the reading in of analouge pins (Voltage).
 */
float readCurrentValue(byte pinNumber, float calibration) {
  float current = ((float(analogRead(pinNumber) / 1023.0) * 5.0) * calibration);
}

/**
 * Sets the output chanels to the required state.
 */
void relays() {
  digitalWrite(LATCH_PIN, LOW);
  for (int i = 0; i < sizeof(relayState) + 1; i++) {
    // Writes the value of the array out.;
    digitalWrite(DATA_PIN, relayState[i]);
    // Toggle the clock
    digitalWrite(CLOCK_PIN, HIGH);
    digitalWrite(CLOCK_PIN, LOW);
  }
  // bring the latches back up;
  digitalWrite(LATCH_PIN, HIGH);
}
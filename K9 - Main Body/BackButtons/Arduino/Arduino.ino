#include "src/Charlieplex/Charlieplex.h"

#include <Keypad.h>

#define LED_Pin_1 2
#define LED_Pin_2 3
#define LED_Pin_3 4
#define LED_Pin_4 5

#define LED_A1 0
#define LED_A2 1
#define LED_A3 2
#define LED_A4 3

#define LED_B1 4
#define LED_B2 5
#define LED_B3 6
#define LED_B4 7

#define LED_C1 8
#define LED_C2 9
#define LED_C3 10
#define LED_C4 11

byte pins[] = {LED_Pin_1, LED_Pin_2, LED_Pin_3, LED_Pin_4};
Charlieplex charlie(pins, sizeof(pins));

const uint8_t ROWS = 4;
const uint8_t COLS = 3;
char keys[ROWS][COLS] = {
  { '4', '8', 'C'},
  { '3', '7', 'B'},
  { '2', '6', 'A'},
  { '1', '5', '9'}
};

bool LED_A1_Status, LED_A2_Status, LED_A3_Status, LED_A4_Status  = false;
bool LED_B1_Status, LED_B2_Status, LED_B3_Status, LED_B4_Status  = false;
bool LED_C1_Status, LED_C2_Status, LED_C3_Status, LED_C4_Status  = false;

uint8_t colPins[COLS] = { 8, 7, 6,}; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 12, 11, 10, 9 }; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


void setup() {

  Serial.begin(9600);
  
  charlie.setLed(LED_A1, LED_A1_Status);    // Turn off LED0
  charlie.setLed(LED_A2, LED_A2_Status);    // Turn off LED1
  charlie.setLed(LED_A3, LED_A3_Status);    // Turn off LED2
  charlie.setLed(LED_A4, LED_A4_Status);    // Turn off LED3
  charlie.setLed(LED_B1, LED_B1_Status);    // Turn off LED4
  charlie.setLed(LED_B2, LED_B1_Status);    // Turn off LED5
  charlie.setLed(LED_B3, LED_B1_Status);    // Turn off LED6
  charlie.setLed(LED_B4, LED_B1_Status);    // Turn off LED7
  charlie.setLed(LED_C1, LED_C1_Status);    // Turn off LED8
  charlie.setLed(LED_C2, LED_C2_Status);    // Turn off LED9
  charlie.setLed(LED_C3, LED_C3_Status);    // Turn off LED10
  charlie.setLed(LED_C4, LED_C4_Status);    // Turn off LED11

}
void loop() {
  charlie.loop();

  char key = keypad.getKey();

  if (key != NO_KEY) {
    if (key = "A") {
      key = 10;
    } else if (key = "B") {
      key = 11;
    } else if (key = "C") {
      key = 12;
    }

    Serial.println(key);

  }

}

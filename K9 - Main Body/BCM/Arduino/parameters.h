#ifndef PARAMETERS_H
#define PARAMETERS_H

#define SERIAL_BAUD 115200
#define MOTOR_PIN 3
#define DIRECTION_PIN 4
#define SERVOMOTOR_PIN 6
// Initial angle of the servomotor
#define INITIAL_THETA 110
// Min and max values for motors
#define THETA_MIN 60
#define THETA_MAX 150
#define SPEED_MAX 100
// If DEBUG is set to true, the arduino will send back all the received messages
#define DEBUG false

// Set speeds  zero if no messages where received after 500ms
#define TIMEOUT 500

// Pin Functions and numbers

#define TailServo_1_Pin 2
#define TailServo_2_Pin 3
#define NeckServo_PIN 4
#define EarServo_1_PIN 5
#define EarServo_2_PIN 6

#define LeftMotorDir_PIN 10
#define LeftMotorPWM_PIN 11
#define RightMotorDir_PIN 12
#define RightMotorPWM_PIN 13

#define EyesLight_1_PIN 23
#define EyesLight_2_PIN 24
#define NoseLight_PIN 25

#define DoorButton_1_PIN 27
#define DoorButton_2_PIN 28

#define BackButton_1_PIN 30
#define BackButton_2_PIN 32
#define BackButton_3_PIN 34
#define BackButton_4_PIN 36
#define BackButton_5_PIN 38
#define BackButton_6_PIN 40
#define BackButton_7_PIN 42
#define BackButton_8_PIN 44
#define BackButton_9_PIN 46
#define BackButton_10_PIN 48
#define BackButton_11_PIN 50
#define BackButton_12_PIN 52

#define BackLED_1_PIN 31
#define BackLED_2_PIN 33
#define BackLED_3_PIN 35
#define BackLED_4_PIN 37
#define BackLED_5_PIN 39
#define BackLED_6_PIN 41
#define BackLED_7_PIN 43
#define BackLED_8_PIN 45
#define BackLED_9_PIN 47
#define BackLED_10_PIN 49
#define BackLED_11_PIN 51
#define BackLED_12_PIN 53

#define ADC_I_PIN 0
#define ADC_V_PIN 1

#endif

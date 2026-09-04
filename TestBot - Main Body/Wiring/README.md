# Testbot wiring record

This is the working record for Testbot wiring. Update it from photographs, continuity checks, and bench tests. Do not treat a planned connection as an approved connection until it has been checked against the fitted ADM133 board.

## Initial allocation

| Function | Connection | Status | Evidence |
|---|---|---|---|
| Left motor | ADM133 M1 | Planned-unverified |  |
| Right motor | ADM133 M2 | Planned-unverified |  |
| Camera servo | PCA9685 channel 0 | Bench-tested | Philip McGaw ADM133 reference |
| Battery monitor | ADM133 battery input / ADC | Planned-unverified |  |
| Status LEDs | Two onboard WS2812 LEDs | Planned-unverified |  |
| Horn | Onboard passive buzzer | Planned-unverified |  |
| Pi Camera | Raspberry Pi CSI connector | Planned-unverified |  |

## PCA9685 reservations

The ADM133 motor driver uses PCA9685 channels 15/14 for M1, 12/13 for M2, 11/10 for M3, and 8/9 for M4. Testbot therefore reserves channels 12–15 for its fitted M1/M2 motor H-bridges and keeps channel 0 for the camera servo.

## Safety notes

- Test motor commands with the wheels raised or propulsion disconnected.
- Confirm battery polarity and charger behaviour before connecting the Raspberry Pi.
- Do not connect a servo to a channel reserved by an active motor H-bridge.
- Record connector orientation and motor polarity with photographs.
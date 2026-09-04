# Adeept ADM133 Robot HAT V3.1 interfaces

This is the maintained integration reference for the ADM133-Adeept Robot HAT
V3.1. It was transcribed from the vendor schematic and example programs stored
under `KiCAD/ADM133 - Adeept Robot/ADM133-Adeept_Robot_HAT-V3/`.

The KiCad design remains the authoritative source for board-level connectivity.
The mappings below are vendor-reference values and are **Planned or
unverified** for the current ROV installation unless a commissioning record
states otherwise.

## Buses and devices

| Function | Device/address or interface | Notes |
| --- | --- | --- |
| PWM and motor control | PCA9685 at I2C `0x5F` | Example frequency is 50 Hz. |
| Analogue input and battery monitor | ADS7830 at I2C `0x48` | Battery monitor uses ADC channel 0; light tracking uses channel 1. |
| Inertial measurement | MPU6050 at I2C `0x68` | Vendor example reads accelerometer data. |
| Display | SSD1306 OLED, 128 x 64 over I2C | The example does not explicitly set an address. |
| Addressable LEDs | SPI0 MOSI, BCM GPIO10 | SPI mode 0; vendor example uses `/dev/spidev0`, 8 LEDs, and approximately 6.4 MHz. |

The Raspberry Pi I2C pins are SDA1/BCM GPIO2 (physical pin 3) and SCL1/BCM
GPIO3 (physical pin 5).

## Motors and PCA9685 channels

The two DRV8833 motor-driver devices provide four H-bridge motor outputs. The
vendor software maps them as follows:

| Motor | Positive/input A | Negative/input B |
| --- | ---: | ---: |
| M1 | PCA9685 channel 15 | PCA9685 channel 14 |
| M2 | PCA9685 channel 12 | PCA9685 channel 13 |
| M3 | PCA9685 channel 11 | PCA9685 channel 10 |
| M4 | PCA9685 channel 8 | PCA9685 channel 9 |

Channels 0-7 are available for servo outputs in the vendor example. Motor
direction must be confirmed on the actual fitted motor before operation.

## Direct GPIO functions

The following BCM GPIO assignments are used by the vendor examples:

| Function | BCM GPIO |
| --- | ---: |
| Ultrasonic trigger / echo | 23 / 24 |
| Line sensor left / middle / right | 22 / 27 / 17 |
| Buzzer | 18 |
| IR receiver | 12 |
| Board indicator LEDs 1 / 2 / 3 | 9 / 25 / 11 |
| Left RGB LED, R / G / B | 13 / 19 / 0 |
| Right RGB LED, R / G / B | 1 / 5 / 6 |

The RGB example treats the outputs as active-low and uses 2 kHz PWM.

## Battery measurement

The battery sense divider is R15 = 3 kOhm and R17 = 1 kOhm, giving a division
ratio of 0.25. The vendor example assumes an 8.4 V full battery and a 6.0 V
warning threshold. The raw ADC calculation uses a 5 V ADC reference. Battery
percentage calculation and thresholds require verification for the installed
battery chemistry and calibration.

## Status

- Implemented: vendor reference schematic and example mappings are documented.
- Automated-test verification: documentation only; no electrical behaviour is
  verified by automated tests.
- Bench-tested: not recorded in this repository.
- Production-validated: not recorded in this repository.
- Planned or unverified: all physical pin reservations, motor polarity,
  battery calibration, and address conflicts for the current ROV installation.
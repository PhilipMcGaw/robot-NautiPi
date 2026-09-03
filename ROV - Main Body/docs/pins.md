# Historical pin-reference tables

These tables are a physical-reference starting point, not an approved runtime
allocation. In particular, the Adeept ADM133 control mapping is maintained in
`ROV---Control/docs/adeept-robot-hat-adm133-interfaces.md`; its Raspberry Pi
GPIO and motor/servo reservations must be verified on the fitted board before
use. Do not create Cockpit commands from these pin numbers. Control owns the
profile-defined physical mapping and safety validation.

The table may include historical board revisions, incomplete pins, and names
that do not reflect current robot profiles. Confirm every allocation against
the relevant KiCad design and commissioning record.

## Tables

| Device | Navigation   | Adeept |
| ----- | ------------- |:-------------:|
| UART 1 - /dev/ttyS0   | TXD [Pin 8] & RXD [Pin 10]  | TXD [Pin 8] & RXD [Pin 10] |
| UART 3 - /dev/ttyAMA1 | TX3 [Pin 7] & RX3 [Pin 29]  | n/a |
| UART 4 - /dev/ttyAMA2 | TX4 [Pin 24] & RX3 [Pin 21] | n/a |
| UART 5 - /dev/ttyAMA3 | TX5 [Pin 32] & RX5 [Pin 33] | n/a |
| I2C                   | See Magnetometer            | SCL1 [Pin 5] & SDA1 [Pin 3] |
| I2C - /dev/i2c-6      | SCL6 [Pin 16] & SDA6 [Pin 15] |
| Neopixle              | Pin 19 | Pin 19 |
| Status LED 1          | Pin 15 | Pin 21 |
| Status LED 2          | Pin 22 | Pin 22 |
| Status LED 3          | Pin 23 | Pin 23 |
| RGB LED 1             | n/a | Pin 33 & Pin 35 & Pin 27 |
| RGB LED 2             | n/a | Pin 28 & Pin 29 & Pin 31 |
| Line Tracking Module  | n/a | Pin 15 & Pin 13 & Pin 11 |
| Leak Signal           | Pin 13 | | 
| Ultrasonic Module     | n/a | Pin 16 & Pin 24 |
| Analog Input          | SCL1 [Pin 5] / SDA1 [Pin 3] - ADS1115IDGS | SCL [Pin 5] /SDA [Pin 3] - ADS7830 |
| Barometer             | SCL1 [Pin 5] / SDA1 [Pin 3] - BMP280 |
| IMU                   | SPI1_SCLK [Pin 40] / SPI1_MOSI [Pin 38] / SPI1_MISO [Pin 35] / SPI1_CS2 [Pin 36] - ICM-20602 | SCL [GPIO 03] / SDA [GPIO02] - MPU6050 |
| Magnetometer          | SCL1 [Pin 5] / SDA1 [Pin 3] - AK09915 |
| Magnetometer          | SPI1_SCLK [Pin 40] / SPI1_MOSI [Pin 38] / SPI1_MISO [Pin 35] / SPI1_CS1  [Pin 11] - MMC5983 |
| PWM Output            | SCL4 [Pin 26] / SDA4 [Pin 31] / PWM_OE [Pin 37] - PCA9685PW | SCL [Pin 5] / SDA [Pin 3] - PCA9685PW |
| EPROM                 | SCL0 [Pin 28] / SDA0 [Pin 27] - M24C32-DR |



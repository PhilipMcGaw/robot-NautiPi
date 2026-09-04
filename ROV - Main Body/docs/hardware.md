# Hardware interfaces

The main pin and bus reference is [pin reference](pins.md). The KiCad projects under `KiCAD/` are the authoritative source for board-level connectivity.

The maintained vendor-reference mapping for the Adeept ADM133 Robot HAT V3.1
is [ADM133 interfaces](reference/adeept-robot-hat-adm133-interfaces.md).

## Interfaces in use

- UART serial links to navigation and attached controllers.
- I2C for sensors, analogue input, PWM output, and EEPROM devices.
- SPI for selected IMU and magnetometer devices.
- GPIO for status, leak detection, and control signals.
- PWM through PCA9685 or board-specific outputs.

## Hardware safety

- Disconnect or inhibit thrusters before software changes are tested.
- Start actuator demands at zero and verify that command direction is correct.
- Test lights, servos, and H-bridges unloaded before wet testing.
- Verify battery voltage, current limits, fusing, polarity, and leak detection independently.
- Never rely on a browser control timeout as the only motor safety mechanism.

## Hardware-dependent paths

Historical code uses Raspberry Pi device paths such as `/dev/serial/by-id/...`. These are machine-specific and should be discovered and documented on the deployed Pi rather than copied blindly from an old test script.

# TestBot - Main Body

Physical design record for Testbot, a small differential-drive Raspberry Pi robot using an Adeept Robot HAT V3.1.

This folder is the source of truth for Testbot’s physical build record. It is deliberately separate from the future ROS 2/Gazebo digital twin. Record the real robot here first; create or update the digital twin only after the mechanical arrangement, wiring, and measurements are sufficiently stable.

## Current hardware

- Raspberry Pi with Pi Camera.
- Adeept Robot HAT V3.1.
- Two yellow 3–12 VDC motors, connected to M1 and M2 for differential steering.
- Two 18650 LiPo batteries in the HAT’s 2S1P arrangement.
- 9g servo for camera tilt, currently recorded on PCA9685 channel 0.
- Two onboard WS2812 LEDs for robot status indication.
- Onboard passive buzzer for the Cockpit horn function.

The hardware is a development build. The presence of an item in this list does not mean that its wiring, calibration, or operation has been fully validated.

## Folder layout

- [`CAD/`](CAD/) — Fusion 360 exports, working CAD, and mounting measurements.
- [`Wiring/`](Wiring/) — wiring diagrams, connector photographs, pin allocations, and revision notes.
- [`Photos/`](Photos/) — build photographs and inspection evidence.
- [`Reference/`](Reference/) — external mechanical references and supplier documentation.
- [`docs/`](docs/) — build notes, test records, and decisions.

## Provisional mechanical reference

The physical layout is expected to resemble the [Dual Drive Robot Base on Printables](https://www.printables.com/model/187907-dual-drive-robot-base). That model is a layout reference only. Testbot’s own CAD, dimensions, mounting points, and licensing record must be established before any derivative geometry is distributed.

## Related projects

- [CuttleOS Testbot profile](https://github.com/PhilipMcGaw/robot-CuttleOS/blob/main/configs/profiles/testbot.json) — robot-side software and logical hardware contract.
- [Adeept ADM133 hardware reference](https://github.com/PhilipMcGaw/robot-CuttleOS/blob/main/docs/adeept-robot-hat-adm133.md) — HAT capabilities, channel reservations, and validation status.
- [SquidLink](https://github.com/PhilipMcGaw/robot-SquidLink) — future ROS 2, Gazebo, and integration-test work.

## Validation status

Each item should be recorded separately as planned, bench-tested, or production-validated. Include the date, equipment, configuration, result, and evidence location. Do not mark the whole robot as validated because one component works.

## Licence

This folder follows the parent repository’s licensing map. See [`../LICENSES.md`](../LICENSES.md) before adding or distributing CAD, wiring, photographs, or derivative material.

## People who have helped

- Philip 'Skippy' McGaw - <philip@mcgaw.eu> - [philipmcgaw.com](https://philipmcgaw.com)
- Tamarisk 'NotQuiteHere' McGaw - <tamarisk@mcgaw.eu> - [tamarisk.it](https://tamarisk.it)
- Bob 'thinkl33t' Clough - <bob@clough.me> - [thinkl33t.co.uk](https://thinkl33t.co.uk)
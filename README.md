# robot-NautiPi

[![Software, documentation, and reference material: CC BY-NC-SA 4.0](https://img.shields.io/badge/Software_and_documentation-CC_BY--NC-SA_4.0-purple.svg)](LICENSE-CC-BY-NC-SA-4.0.txt)
[![Hardware: CERN-OHL-S 2.0](https://img.shields.io/badge/Hardware-CERN--OHL--S_2.0-purple.svg)](LICENSE-CERN-OHL-S-2.0.txt)
[![KiCad](https://img.shields.io/badge/Design-KiCad-314cb0.svg)](https://www.kicad.org/)
[![Fusion 360](https://img.shields.io/badge/Design-Fusion_360-f26b38.svg)](https://www.autodesk.com/products/fusion-360/overview)
[![Arduino](https://img.shields.io/badge/Embedded-Arduino-00878f.svg)](https://www.arduino.cc/)

NautiPi is the physical hardware and embedded-project repository for the robot projects. It contains electronics, PCB and KiCad work, Arduino projects, component records, mechanical references, photographs, and retained historical hardware material.

NautiPi works alongside the other current project repositories:

- [CuttleOS](https://github.com/PhilipMcGaw/robot-CuttleOS) owns the robot-side software, including Cockpit, Control, and Datalogger.
- [SquidLink](https://github.com/PhilipMcGaw/robot-SquidLink) provides the independent ROS 2/Gazebo simulation and integration-test environment.

The repositories are separate and connected by documented interfaces. NautiPi is the source of truth for the physical hardware design record; it is not the source of truth for software implementation or simulation behaviour.

The cross-repository system architecture is authoritative in [CuttleOS `docs/system-architecture.md`](https://github.com/PhilipMcGaw/robot-CuttleOS/blob/main/docs/system-architecture.md). NautiPi-specific physical hardware architecture is defined in [`docs/hardware-architecture.md`](docs/hardware-architecture.md).

## Repository layout

### ROV hardware

- [`ROV - Conductivity Temperature and Depth Transducer/`](<ROV - Conductivity Temperature and Depth Transducer/README.md>) — conductivity, temperature, and depth transducer design and embedded-project material.
- [`ROV - Light Module/`](<ROV - Light Module/README.md>) — ROV lighting electronics and embedded-project material.
- [`ROV - Main Body/`](<ROV - Main Body/README.md>) — main-body hardware archive, including PCB designs, component records, mechanical references, and historical integration material.
- [`ROV - Navigator/`](<ROV - Navigator/README.md>) — Navigator PCB, schematics, power-management, status LED, leak-detection, and shared KiCad resources.

### K9 hardware

- [`K9 - Camera/`](<K9 - Camera/>) — retained camera setup material and reference videos.
- [`K9 - Main Body/`](<K9 - Main Body/README.md>) — K9 main-body hardware designs, body-control modules, motor-driver material, and project references.

### Testbot hardware

- [TestBot - Main Body/](<TestBot - Main Body/README.md>) — physical Testbot CAD, wiring, build notes, photographs, and validation evidence.

### Other retained material

- [`Remote Sensors/`](<Remote Sensors/>) — retained remote-sensor project material.
- [`Traffic Light/`](<Traffic Light/>) — historical traffic-light project photographs and reference material.
- [`docs/images/`](docs/images/) — README and project imagery.

## Current status

NautiPi contains a mixture of current design work, development material, and historical project records. The presence of a design file, firmware, photograph, or other project artefact does not establish that the associated hardware is currently manufactured, assembled, commissioned, calibrated, or integrated.

Hardware assembly, electrical commissioning, calibration, environmental testing, and robot integration are separate engineering activities and require their own evidence.

The ROV hardware projects are not currently represented as production-validated by this repository unless explicit validation evidence is recorded.

## Relationship to software and simulation

CuttleOS is the current software architecture and runtime boundary. SquidLink is the current simulation and integration-test boundary. Historical software notes retained in NautiPi must not be treated as authoritative when they conflict with those repositories.

Hardware references in NautiPi do not, by themselves, authorise a Control allocation, GPIO assignment, RS-485 mapping, or production wiring arrangement. Such allocations must be established by the current engineering and software interface documentation.

## Documentation

The NautiPi documentation policy is maintained in [`docs/documentation-policy.md`](docs/documentation-policy.md). It follows the wider project documentation style, including formal British English, Oxford commas, NIST SI conventions, precise technical terminology, and explicit validation status.

Each substantial hardware project should have a local `README.md` describing its purpose, contents, current status, and relationship to the wider system.

## People who have helped

- Philip 'Skippy' McGaw - <philip@mcgaw.eu> - [philipmcgaw.com](https://philipmcgaw.com)
- Tamarisk 'NotQuiteHere' McGaw - <tamarisk@mcgaw.eu> - [tamarisk.it](https://tamarisk.it)
- Bob 'thinkl33t' Clough - <bob@clough.me> - [thinkl33t.co.uk](https://thinkl33t.co.uk)

## Licence

The repository uses separate licences for project software and documentation, and for hardware design material. See [`LICENSES.md`](LICENSES.md) for the authoritative licensing map and the complete licence texts.

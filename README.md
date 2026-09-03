# robot-NautiPi

[![Software, documentation, and reference material: CC BY-NC-SA 4.0](https://img.shields.io/badge/Software_and_documentation-CC_BY--NC--SA_4.0-purple.svg)](LICENSE-CC-BY-NC-SA-4.0.txt)
[![Hardware: CERN-OHL-S 2.0](https://img.shields.io/badge/Hardware-CERN--OHL--S_2.0-purple.svg)](LICENSE-CERN-OHL-S-2.0.txt)
[![KiCad](https://img.shields.io/badge/Design-KiCad-314cb0.svg)](https://www.kicad.org/)
[![Fusion 360](https://img.shields.io/badge/Design-Fusion_360-f26b38.svg)](https://www.autodesk.com/products/fusion-360/overview)
[![Arduino](https://img.shields.io/badge/Embedded-Arduino-00878f.svg)](https://www.arduino.cc/)

NautiPi is the physical hardware and embedded-project companion to the ROV
software. It contains electronics, PCB and KiCad work, Arduino projects,
component records and hardware reference material.

NautiPi works alongside the other related projects:

- [CuttleOS](https://github.com/PhilipMcGaw/robot-CuttleOS) runs the robot-side
  Cockpit, Control and Datalogger services on Raspberry Pi.
- [SquidLink](https://github.com/PhilipMcGaw/robot-SquidLink) provides the
  independent ROS 2/Gazebo software-in-the-loop and hardware-in-the-loop
  environment.

The projects are separate and connected by documented interfaces. Hardware
references in NautiPi do not automatically authorise a Control allocation or
claim that a board has been commissioned.

## People who have helped

- Philip 'Skippy' McGaw - <philip@mcgaw.eu> - [philipmcgaw.com](https://philipmcgaw.com)
- Tamarisk 'NotQuiteHere' McGaw - <tamarisk@mcgaw.eu> - [tamarisk.it](https://tamarisk.it)
- Bob 'thinkl33t' Clough - <bob@clough.me> - [thinkl33t.co.uk](https://thinkl33t.co.uk)

## Repository layout

- [`ROV - Conductivity Temperature and Depth Transducer/`](<ROV - Conductivity Temperature and Depth Transducer/README.md>) — KiCad design files, resources, and embedded project material for the conductivity, temperature, and depth transducer.
- [`ROV - Light Module/`](<ROV - Light Module/README.md>) — KiCad design files and embedded project material for the ROV light module.
- [ROV - Main Body/](<ROV - Main Body/README.md>) — the ROV main-body hardware archive, including PCB designs, BOMs, mechanical references, and historical integration material.
- [K9 - Main Body/](<K9 - Main Body/README.md>) — K9 main-body hardware designs, body-control modules, motor-driver material, and project references.
- [`docs/images/`](docs/images/) — README and project imagery.

## Current status

The repository contains the current design and reference material for the listed
hardware projects. Hardware assembly, electrical commissioning, and ROV
integration should be treated as separate activities and recorded with their
own evidence. No physical or production validation is claimed here without
that evidence.

## Documentation

The project-specific README files are the primary documentation for the
hardware folders. The related software and simulation projects are documented
in [CuttleOS](https://github.com/PhilipMcGaw/robot-CuttleOS) and
[SquidLink](https://github.com/PhilipMcGaw/robot-SquidLink).

## Licence

The repository uses separate licences for project software and documentation,
and for hardware design material. See [`LICENSES.md`](LICENSES.md) for the
licensing map and the complete licence texts.
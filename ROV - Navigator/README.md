# ROV Navigator

The Navigator directory contains the KiCad design material for the ROV Navigator hardware.

## Contents

- `Navigator.kicad_pro` — KiCad project file.
- `Navigator.kicad_sch` — main Navigator schematic.
- `Navigator.kicad_pcb` — Navigator PCB layout.
- `Power Managment.kicad_sch` — power-management schematic retained under its existing filename.
- `Status LEDs.kicad_sch` — status LED schematic.
- `leak detection.kicad_sch` — leak-detection schematic.
- `common/` — shared Navigator design resources.
- `fp-lib-table` — KiCad footprint library configuration.
- `sym-lib-table` — KiCad symbol library configuration.

## Current status

This directory is a hardware design record. The presence of KiCad project files does not, by itself, establish that the board has been manufactured, assembled, electrically commissioned, calibrated, or integrated with the current ROV software.

No production-validation claim is made here without explicit test evidence.

The current robot software architecture is maintained in CuttleOS, while simulation and integration testing are maintained in SquidLink. Hardware interfaces recorded here should therefore be treated as design information unless a separate engineering record establishes the current physical allocation.

## Documentation

Project-wide documentation requirements are defined by the [Robots Project Documentation Standard](https://chartroom.philipmcgaw.com/development/documentation-standard/), maintained in Chartroom.

The parent repository [`README.md`](../README.md) and [`LICENSES.md`](../LICENSES.md) provide the wider project context and licensing information.

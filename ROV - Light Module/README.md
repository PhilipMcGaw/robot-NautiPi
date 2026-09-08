# ROV Light Module

This folder contains the KiCad design files, reference material, and embedded-project material for the ROV light module.

## Contents

- `KiCAD/` — schematics, PCB layouts, project files, and generated documents.
- `Software/` — Arduino and PlatformIO firmware experiments and supporting libraries.

## Board-level design notes

The design input is **12–18 VDC nominal**, with a **24 VDC maximum design input**.
Do not operate the module above 24 VDC.

D1 is the Cree CXA1304 9 V variant. The LED-current set resistor is three 0.5 ohm
0805 resistors in parallel. The intended thermal strategy uses the module's water
proximity for cooling together with NTC feedback; this requires validation during
commissioning.

The final NeoPixel in the string is D9. Its data output is intentionally left
unconnected because there is no downstream NeoPixel device. No termination is
required on this output.

The planned field interface is Modbus RTU over RS-485, using 115200 8N1 by default.
500 kbit/s is an optional setting pending complete harness and populated-bus testing.

## Current status

The design and reference material are retained for continued development and
review. Assembly, electrical commissioning, thermal testing, and integration
with the ROV are not recorded as complete here.

## Related material

- [KiCad](https://www.kicad.org/) — PCB design software.
- `Software/Light/led-tricks-gamma-correction.pdf` — retained LED-control reference.

## Licensing

See the parent [NautiPi README](../README.md) and [licensing map](../LICENSES.md).
Hardware design files are covered by CERN-OHL-S 2.0; project software,
documentation, and reference material are covered by CC BY-NC-SA 4.0, subject to
any separate third-party notices.

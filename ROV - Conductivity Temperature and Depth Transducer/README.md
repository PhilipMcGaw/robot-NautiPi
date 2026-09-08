# ROV Conductivity, Temperature, and Depth Transducer

This folder contains the KiCad design files, reference material, and embedded-project material for the ROV conductivity, temperature, and depth transducer.

## Contents

- `KiCAD/` — schematics, PCB layouts, project files, generated documents, and component resources.
- `Software/` — Arduino and PlatformIO firmware experiments and supporting libraries.

## Interface baseline

The shared node design target is **12–18 VDC nominal**, with a **24 VDC maximum
design input**. The planned field interface is Modbus RTU over RS-485 at 115200 8N1;
500 kbit/s remains optional pending complete harness and populated-bus testing.

## Current status

The design and reference material are retained for continued development and
review. Assembly, electrical commissioning, sensor calibration, and integration
with the ROV are not recorded as complete here.

## Sources and related projects

- [OpenCTD](https://oceanographyforeveryone.com/)
- [OpenCTD on GitHub](https://github.com/OceanographyforEveryone/OpenCTD)
- [Conduino](https://github.com/feslab/conduino)
- [OpenCTD with Conduino](https://github.com/kpdangelo/OpenCTDwithConduino)
- [KiCad](https://www.kicad.org/) — PCB design software.

## Licensing

See the parent [NautiPi README](../README.md) and [licensing map](../LICENSES.md).
Hardware design files are covered by CERN-OHL-S 2.0; project software,
documentation, and reference material are covered by CC BY-NC-SA 4.0, subject to
any separate third-party notices.

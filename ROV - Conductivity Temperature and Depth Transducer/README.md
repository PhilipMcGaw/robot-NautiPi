# ROV Conductivity, Temperature, and Depth Transducer

This folder contains the KiCad design files, reference material, and embedded-project material for the ROV conductivity, temperature, and depth transducer.

## Contents

- `KiCAD/` — schematics, PCB layouts, project files, generated documents, and component resources.
- `Software/` — Arduino and PlatformIO firmware experiments and supporting libraries.

## Interface baseline

The shared node design target is **12–18 VDC nominal**, with a **24 VDC maximum
design input**. The planned field interface is Modbus RTU over RS-485 at 115200 8N1;
500 kbit/s remains optional pending complete harness and populated-bus testing.

## Development focus

The Light Module is currently the definitive playground and reference implementation for the shared ATtiny node framework. CTD firmware work is deferred while the Light Module commissioning, bus, and thermal behaviour are developed.

## Connector roles

- `J6` is the UPDI programming/diagnostic interface.
- `J7` is the external interface to the robot.
- `J2` plugs into `J3`, and `J4` plugs into `J5`, forming the CTD board stack.
## Temperature and TDS measurement

The CTD NTC is connected via `J1`, exposed to the water, and is intended to directly measure water
temperature. This temperature measurement forms part of the calculation used to
derive total dissolved solids (TDS); it is not primarily a board thermal-protection
sensor.
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
## Further reading

- [jwlauer/CTD](https://github.com/jwlauer/CTD) - MS5803, NTC, pseudo-AC conductivity measurement, and calibration examples.
- [CTDizzle](https://github.com/IanTBlack/CTDizzle) - Arduino CTD construction, waterproofing, logging, and calibration.
- [OpenCTD](https://github.com/OceanographyforEveryone/OpenCTD) - Open CTD construction, calibration, and field deployment reference.
- [OpenCTD research paper](https://tos.org/oceanography/article/the-openctd-a-low-cost-open-source-ctd-for-collecting-baseline-oceanographic-data-in-coastal-waters) - Architecture and field-use background.
- [Open-source four-pole EC/CTD validation study](https://research.fs.usda.gov/treesearch/66053) - Four-electrode measurement and validation methods.
- [Cost-efficient oceanographic CTD study](https://pmc.ncbi.nlm.nih.gov/articles/PMC11207868/) - Pressure housing and deeper-water design considerations.

## Transducer modularity

The CTD intentionally combines conductivity, temperature, and pressure because they form one coherent measurement system. Temperature compensates conductivity, pressure provides depth, and the three measurements support derived salinity and density.

Other sensing functions should normally be separate RS-485/Modbus transducers using the shared Arduino hardware and firmware framework. This includes optical absorbance, turbidity, pH, dissolved oxygen, and ORP modules.


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
Connector roles:

- `J4` plugs into `J7`, and `J8` plugs into `J9`, forming the three-PCB stack.
- `J1` is a diagnostic port for design and commissioning only.
- `J6` is the final interface to the rest of the robot.

## Interface and measurement details

`J6` is the production interface to the robot. Its input voltage is **12–18 VDC
nominal**, with a **24 VDC maximum operating input**. Do not exceed 24 VDC.

`J1` is the AVR UPDI diagnostic/programming header. The built-in feedback LED is
not part of the standard UPDI header, but is placed on an otherwise unused header
pin to provide visual status/feedback from the microcontroller during design,
commissioning, and operation.

### V_in measurement

The input voltage is measured through a 51 kΩ / 12 kΩ resistor divider:

`Vmeasure = V_in × 12 / (51 + 12)`

| Input voltage | Expected Vmeasure |
| ------------: | ----------------: |
|        12 VDC |            2.29 V |
|        18 VDC |            3.43 V |
|        24 VDC |            4.57 V |

These values assume ideal resistor values. Component tolerance and supply variation
will introduce small differences.
## TH1/D11 multiplexed temperature feedback

A1/D1 is multiplexed between status indication and temperature feedback:

- Output low: D11 is on for status indication.
- Output high: TH1 is connected directly to the 5 V rail and may self-heat; this
  state should be avoided or limited to brief controlled intervals.
- High-impedance analogue input: TH1 sinks current through the R8 and D11/R14 paths,
  providing an indicative temperature measurement.

TH1 is located near the high-power LED D1. D11 provides local status indication for
RS-485 and other conditions that cannot be reported through the data link.

The following indicative response assumes R8 = 10 kΩ, R14 = 1 kΩ, a 5 V rail, TH1
= 10 kΩ at 25 °C with B = 3590 K, and a green D11 Vf approximately 2.1 V when forward biased. The D11 glow is expected and normal. Actual
values require calibration with the assembled board and the LED's measured Vf.

| Temperature | TH1 resistance | A1 voltage | 10-bit ADC | D11 state |
|---:|---:|---:|---:|:---|
| 0 °C | 30.1 kΩ | 3.75 V | 768 | off |
| 10 °C | 18.9 kΩ | 3.27 V | 669 | off |
| 20 °C | 12.3 kΩ | 2.88 V | 589 | glowing |
| 25 °C | 10.0 kΩ | 2.83 V | 580 | glowing |
| 30 °C | 8.20 kΩ | 2.78 V | 569 | glowing |
| 40 °C | 5.62 kΩ | 2.66 V | 544 | glowing |
| 50 °C | 3.94 kΩ | 2.51 V | 514 | glowing |
| 60 °C | 2.82 kΩ | 2.34 V | 478 | glowing |
| 70 °C | 2.06 kΩ | 2.15 V | 439 | glowing |
| 80 °C | 1.53 kΩ | 1.94 V | 397 | glowing |
| 90 °C | 1.16 kΩ | 1.73 V | 354 | glowing |
| 100 °C | 889 Ω | 1.53 V | 313 | glowing |
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





# ROV safety and control record

This document records the physical evidence needed to implement the CuttleOS
safety and control policy on the ROV. The software-facing safety architecture
is maintained in [robot-CuttleOS](https://github.com/PhilipMcGaw/robot-CuttleOS).

## Physical safety record

Record, for each ROV revision:

- propulsion and payload actuator isolation method;
- physical emergency power cutoff;
- thruster guards and safe handling arrangements;
- fuses, current limits, polarity, and brown-out behaviour;
- pressure vessels, seals, penetrators, and leak detectors;
- pressure, temperature, and battery-monitor limits;
- tether arrangement, snag risks, and recovery procedure;
- payload effects on buoyancy, trim, stability, clearance, and entanglement;
- connector retention, strain relief, and service access.

## Pre-dive and post-dive checks

The ROV operating record should include a pre-dive checklist covering the
physical condition, electrical isolation, profile and configuration identity,
actuator neutral state, communications, camera, battery, leak detection,
seals, penetrators, payload attachment, tether, and recovery arrangements.

The post-dive record should cover power isolation, leak and ingress inspection,
connector and penetrator inspection, freshwater rinse where applicable, drying,
storage, damage, and logged faults.

## Recovery behaviour

An automatic surface or return action must not be assumed to be safe. The
physical record must establish whether it is possible with the installed
buoyancy, tether, payload, obstruction, and water conditions. Until then, the
ROV should use a warning and propulsion-stop response rather than claiming an
untested recovery mode.

## Evidence

Each safety test should identify the ROV revision, hardware and firmware
revisions, active CuttleOS profile, software revision, test conditions,
expected response, observed response, operator, date, and result. Mark the
result as designed, simulated, software-tested, bench-tested, commissioned, or
production-validated.

See the CuttleOS [safety and control architecture](https://github.com/PhilipMcGaw/robot-CuttleOS/blob/main/docs/safety-and-control.md)
for the logical state model, failure classes, and software test expectations.
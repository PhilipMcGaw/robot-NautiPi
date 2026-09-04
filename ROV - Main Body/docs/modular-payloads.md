# ROV modular payload interface

The ROV main body includes mounting holes intended for attaching sensors,
additional components, or a manipulator arm. This provides a defined mechanical
payload interface for future expansion.

## Design record

Record the following for every attached payload:

- mounting-hole locations and pattern used;
- payload name, revision, and purpose;
- mass and centre-of-mass effect where relevant;
- fasteners, brackets, and material;
- cable routing, strain relief, and connector details;
- power and communications requirements;
- impact on buoyancy, balance, clearance, and service access;
- associated CuttleOS capability and SquidLink representation, if applicable.

The mounting holes establish mechanical provision only. They do not establish
an electrical pinout, power allocation, software capability, or safe operating
limit. Those details require separate hardware, software, and test records.

## Payload interface definition

The mounting-hole interface should be recorded as a controlled mechanical
interface for external designs. For each payload position, record:

- the mounting datum and hole pattern;
- payload keep-out zones;
- maximum payload mass and moment;
- clearance from thrusters, cameras, and other moving parts;
- fastener, bracket, and material requirements;
- cable routing and strain relief;
- power and communications provision;
- effects on water flow, buoyancy, trim, and stability;
- access required for installation, inspection, and removal.

The design record should distinguish nominal CAD data from parts that have been
manufactured and verified. Each revision should identify which payloads remain
mechanically compatible.
## Planned payload records

Payload records should be added as the ROV is developed. Likely examples
include sensors, lights, a manipulator arm, and scientific instruments. Each
one should be marked as designed, assembled, bench-tested, commissioned, or
production-validated according to the evidence available.

## Related lessons from CPSdrone

The CPSdrone project is a useful external reference for modular underwater
vehicles, maintained bills of materials, staged build instructions, and
separate motor test fixtures. These ideas inform this repository but do not
replace ROV-specific measurements or validation.

- [CPSdrone repository](https://github.com/CPSdrone/CPS)
- [CPSdrone underwater robotics course](https://www.cpsdrone.com/cps-5-course/)
- [CPSdrone motor thrust tester](https://github.com/CPSdrone/CPS/tree/master/tests/motor%20thrust%20tester)
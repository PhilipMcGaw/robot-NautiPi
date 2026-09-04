# ROV Main Body documentation

This directory contains retained integration guidance and historical engineering
notes for the [ROV Main Body archive](../README.md). It does not contain the
active Cockpit, Control, Datalogger, or simulation implementations.

## Current sources of truth

- [robot-CuttleOS](https://github.com/PhilipMcGaw/robot-CuttleOS) — active
  Raspberry Pi robot software, profiles, deployment, Cockpit, Control, and
  Datalogger services.
- [robot-SquidLink](https://github.com/PhilipMcGaw/robot-SquidLink) — independent
  ROS 2/Gazebo simulation and integration testing.
- [`KiCAD/`](../KiCAD/) and [pin reference](pins.md) — hardware design and
- [ROV safety and control](safety-and-control.md) — physical cutoffs, pre-dive checks, recovery constraints, and evidence.
  historical physical-reference material. These require normal commissioning
  and do not authorise hardware use by themselves.

## Retained integration material

- [System overview](system-overview.md) — service ownership and data flow notes.
- [Hardware interfaces](hardware.md) — shared hardware safety boundaries.
- [Development orientation](development.md) — historical component workflows.
- [Deployment orientation](deployment.md) — historical deployment boundaries.
- [Platform support](platform-support.md) — development and runtime boundaries.
- [Engineering principles](engineering-principles.md) — practices for future work.
- [Roadmap](roadmap.md) — retained cross-project planning notes.
- [Current status](status.md) — implementation and evidence status for this archive.
- [Testing](testing.md) — staged integration and physical validation guidance.
- [Modular payloads](modular-payloads.md) — mounting-hole interface and payload-record requirements.
- [Documentation policy](documentation-policy.md) — documentation maintenance rules.

## Historical material

The documents in this directory may describe retired names, paths, serial
protocols, or deployment arrangements. Treat them as reference only. Current
CuttleOS and SquidLink documentation takes precedence where the material here
conflicts with the maintained repositories.
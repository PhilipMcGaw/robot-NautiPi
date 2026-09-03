# ROV development orientation

This repository has no monolithic application, dependency installer, virtual
environment, or start script. Develop each active service in its sibling
repository, using that repository's documented launcher and dependency setup.
Interactive examples assume Zsh.

## Component workflows

| Work area | Authoritative location |
|---|---|
| Cockpit web UI, simulator, profiles, camera presentation, and browser telemetry | `ROV---Cockpit/docs/development.md` and `ROV---Cockpit/docs/testing.md` |
| Control, hardware boundaries, NATS contract, network deployment, and ADM133 | `ROV---Control/docs/` |
| Change-only SQLite logging, retention, and CSV export | `ROV---Datalogger/MASTER_CONTEXT.md` and `ROV---Datalogger/docs/status.md` |
| ROS 2/Gazebo virtual HiL/SiL environment | `ROV---HiL-and-SiL/docs/` |

On Windows, use the relevant component's Windows launcher. On macOS and Linux,
use its declared shell script. Do not copy an earlier monolithic WinPython or
`uv` workflow into a component without checking that component's current
documentation first.

## Shared development rules

- Use the active profile matching the robot being developed. Profiles originate
  under `ROV---Cockpit/configs/profiles/` and are versioned in Git.
- Publish logical namespaced commands only. Control converts those commands to
  physical mappings and safety-limited outputs.
- Use SI units and the current NATS contract. Historical serial tables in the
  root `README.md` are not the source of truth.
- Develop hardware behaviour with propulsion disconnected or inhibited.
- Use Cockpit simulation, mocks, or HiL/SiL for early feedback; those do not
  prove physical hardware behaviour.

## Hardware records

[`pins.md`](pins.md), `KiCAD/`, and `CPS/` are valuable source/reference material for
physical design work. Verify a selected board revision and record commissioning
evidence before relying on a pin, connector, or electrical assumption.

# Shared robot framework roadmap

This is the cross-repository roadmap. Repository `docs/status.md` files record
the detailed implementation and evidence status. Planned work is not
implementation, bench validation, or production validation.

## 1. Shared profiles and operational deployment

- Maintain one Git-versioned JSON profile per robot, deployed at boot to
  `/etc/robot/profile.json`.
- Maintain functional ROV, K9, and PiWars examples using the same profile
  format, NATS Core namespaces, and SI-unit rules.
- Bench-validate the canonical Raspberry Pi provisioner, NetworkManager
  Wi-Fi/hotspot behaviour, SMB/Avahi, NATS systemd setup, and service startup
  on a clean target image.
- Configure optional per-robot remote SSH verification access using the
  least-privilege Control procedure, then record connection and host identity
  evidence.

Status: profile examples, provisioning, and deployment configuration exist;
physical deployment and remote-access validation remain unverified.

## 2. Cockpit

- Continue profile-selected instrument modules and robot-backed visual settings.
- Add a depth-scale configuration UI.
- Complete camera inventory configuration for CSI, USB, and virtual cameras,
  retaining an early de-warp processing injection point.
- Continue the Vue/TypeScript and icon-system migration while keeping the
  operator UI usable on supported development platforms.
- Complete production authentication, authorisation, and audit/safety
  hardening.

Status: current HUD, simulator, shared operator shell, soundboard drawer, and
camera foundations are implemented. Real camera paths and production security
remain unvalidated.

## 3. Control and hardware integration

- Implement the profile-driven ADM133 adapter for K9 and PiWars, including
  servo/motor allocation conflict checks, indicators, and safe limits.
- Bench-commission each ADM133 interface; `servo-00` through `servo-15` are
  stable aliases, not evidence that a physical output has been verified.
- Define and implement RS-485 transport for attached microcontrollers,
  including electrical arrangement, UART settings, addressing, framing, CRC,
  half-duplex control, timing, retries, and safe link-loss handling.
- Keep motor mixing, limits, neutral, timeouts, emergency stop, and hardware
  mappings in Control.

Status: NATS/service boundaries and configuration contracts exist; hardware
adapters, RS-485, and physical safety validation remain planned.

## 4. Datalogger

1. Reconnect and recover cleanly from NATS interruption without affecting
   Control or Cockpit.
2. Add data-integrity tests for delivery, change detection, timestamps,
   profile/namespace handling, concurrent access, and restart behaviour.
3. Bench-validate the deployed service, shared CSV directory, startup ordering,
   and retention behaviour.
4. Add safe batching/compaction and operational health reporting.

Status: NATS change-only SQLite storage, 30-day retention, CSV export, and
provisioning integration exist; operational resilience and Raspberry Pi
evidence remain planned.

## 5. HiL/SiL and evidence

- Complete ROS 2/Gazebo vehicle, sensor, camera, and NATS bridge integration.
- Run repeatable scenarios against a headless robot using the same profile and
  logical-command contract.
- Record simulation, bench, and production evidence separately.

Status: documentation and structure exist; complete models, bridge execution,
scenarios, and validation remain planned.


## 6. ROV physical development

- Record the ROV mounting-hole pattern as the mechanical payload interface.
- Define the payload datum, hole patterns, keep-out zones, mass and moment
  limits, clearances, fasteners, cable routing, power, and communications.
- Record the effects of each payload on buoyancy, trim, stability, water flow,
  service access, and thruster or camera clearance.
- Version the physical interface and record payload compatibility against each
  ROV revision.
- Create a maintained ROV bill of materials with revisions, substitutions, and
  availability notes.
- Add separate test records for motor thrust, buoyancy and balance, leak
  checks, payload fit, and tether or network operation as applicable.
- Link each payload to its physical record, CuttleOS profile capability, and
  SquidLink model only when the relevant information exists.

Status: mounting provision is recorded; the BOM and dedicated physical test
records remain planned.

## 7. ROV operational documentation

- [ ] Record the ROV physical emergency cutoff, propulsion isolation, guards,
  fusing, current limits, and brown-out behaviour.
- [ ] Record pressure vessels, seals, penetrators, leak detection, tether risks,
  recovery constraints, and payload entanglement risks.
- [ ] Create pre-dive, post-dive, leak, rinse, and storage checklists.
- [ ] Do not enable an automatic surface or return response until its physical
  behaviour is verified with the installed tether, buoyancy, and payload.
- Record depth, temperature, pressure, ingress, and environmental ratings for
  relevant components where the manufacturer provides them.
- Maintain wiring diagrams, connector records, and physical operating
  procedures alongside the applicable hardware revision.
- Record pre-dive, post-dive, leak, rinse, storage, and inspection checks where
  they apply to the ROV hardware.
- Link hardware revisions and commissioning records to the active CuttleOS
  profile and software revision where practical.

Status: the need for these records is established; the component register and
complete operational procedures remain planned.

## Completion rule

Each change updates the relevant component documentation and master context.
Each milestone is complete only when its repository status records the required
implementation, automated-test, bench, and production evidence.

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

## Completion rule

Each change updates the relevant component documentation and master context.
Each milestone is complete only when its repository status records the required
implementation, automated-test, bench, and production evidence.

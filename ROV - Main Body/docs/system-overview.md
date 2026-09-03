# ROV system overview

Each robot has a Raspberry Pi that runs Cockpit, Control, and Datalogger as
separate services. A browser connects to Cockpit; it does not connect directly
to NATS or hardware. HiL/SiL is a separate virtual-machine environment that
uses the same application-facing contracts when connected to a headless robot.

```text
Operator browser
  ├─ HTTP / WebSocket → Nginx → Cockpit
  └─ camera / media → Nginx → Cockpit camera pipeline

Cockpit ── NATS Core ── Control ── approved hardware adapters ── robot hardware
                              │
                              └── NATS Core ── Datalogger ── SQLite / CSV

HiL/SiL VM ── authenticated, approved NATS access ── headless robot
```

## Component ownership

### Cockpit

Cockpit is the operator-facing FastAPI application. It consumes NATS
server-side, provides browser telemetry through a WebSocket, renders
profile-selected instrumentation, and owns camera/media presentation. It
publishes only logical commands.

### Control

Control is the hardware-facing Raspberry Pi service. It validates active-profile
commands, applies safety behaviour, and owns physical mappings for motors,
actuators, GPIO, I2C, SPI, serial devices, and HAT adapters. It also owns
network deployment.

### Datalogger

Datalogger observes the NATS Core contract and persists changed payloads to
SQLite. It retains data for 30 days and exports CSV files to the shared Cockpit
media location. It is never a dependency for vehicle control.

### NATS Core

NATS Core is the internal message transport. Subjects are namespaced, payloads
are documented by the active contract, and units are SI. NATS JetStream is
outside this architecture.

### Camera/media services

The Cockpit camera pipeline supports a profile-defined inventory. Nginx is the
browser-facing reverse proxy; capture, processing, and streaming adapters stay
behind the Cockpit camera/media boundary. Camera configuration and real-device
operation remain separately validated work.

## Operational boundaries

- One active Git-versioned JSON robot profile is loaded at boot from
  `/etc/robot/profile.json`.
- Profiles and mappings are shared across services; they are not independently
  edited by Cockpit, Control, or Datalogger.
- A browser WebSocket is distinct from NATS Core.
- Control does not serve the web UI, and Cockpit does not directly access
  robot hardware.
- Software implementation and automated tests are not proof of bench or
  production validation.

# ROV integration and hardware test procedure

Run checks in increasing order of risk. Record the date, Git revision, active
profile revision, hardware revision, configuration, and result for every
session. Component-specific tests are authoritative for their service.

## 1. Documentation and software checks

Run each sibling repository's documented test suite and documentation audit.
This integration repository provides its own documentation check:

```zsh
python3 tests/test_documentation.py
```

Review the active contract before any message or profile test:

```text
robot-CuttleOS/docs/robot-profile-requirements.md
robot-CuttleOS/docs/nats.md
```

## 2. Disconnected integration checks

With propulsion disconnected or inhibited, confirm that the expected active
profile is installed and that Cockpit, Control, Datalogger, NATS, Nginx, and
camera services report the expected status. Use the checks in
`robot-CuttleOS/docs/deployment.md`; do not print NATS credentials.

Use Cockpit simulation or HiL/SiL to exercise presentation and logical-command
handling before connecting hardware. Simulation success is not physical
validation.

## 3. Hardware commissioning

For each attached board, sensor, camera, actuator, or HAT port:

1. Confirm its approved profile mapping and current board documentation.
2. Verify physical wiring, power, polarity, fuse protection, and connector
   orientation independently.
3. Run the component's documented bench procedure with safe outputs.
4. Record observed direction, range, neutral behaviour, telemetry units, and
   any reservations or conflicts.

Do not infer pin compatibility from historical root tables. The Adeept ADM133
requires the specific Control commissioning guidance and is not yet
bench-validated.

## 4. Dry and wet integration

Only after individual hardware commissioning passes, test the complete dry
electronics stack. Verify network, NATS, cameras, profile identity, telemetry,
logical-command safety, emergency-stop behaviour, and media/logging operation.

Perform a tethered shallow-water test only after the dry test passes. Inspect
seals and penetrators, continuously monitor leak detection, and retain an
independent physical power cutoff.

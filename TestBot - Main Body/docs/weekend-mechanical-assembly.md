# Testbot weekend mechanical assembly plan

## Scope

This weekend's activity is limited to mechanical assembly and documentation. Do
not treat the assembled robot as electrically commissioned or software-ready.
Motor, battery, HAT, camera, and servo operation remain deferred until a separate
safe commissioning session.

## Before assembly

- [ ] Confirm the available chassis, wheels, motors, battery holder, Raspberry Pi,
      ADM133 HAT, camera bracket, servo bracket, fasteners, and tools.
- [ ] Photograph all parts and record any missing or damaged items.
- [ ] Keep batteries disconnected during mechanical work.
- [ ] Keep propulsion disconnected or mechanically inhibited until the motor test.

## Mechanical checklist

- [ ] Assemble the chassis and wheel supports.
- [ ] Fit both motors and record which physical motor is connected to M1 and M2.
- [ ] Record left/right motor orientation and axle spacing.
- [ ] Fit the Raspberry Pi and ADM133 mounting hardware.
- [ ] Fit the battery holder and confirm cell clearance and retention.
- [ ] Fit the camera mount and camera-tilt servo bracket.
- [ ] Check the full camera tilt range for collisions and cable strain.
- [ ] Route cables with clearance from wheels, axles, gears, and moving brackets.
- [ ] Confirm that the camera view is not blocked by the chassis or hardware.
- [ ] Check that fasteners are secure without distorting printed or plastic parts.

## Measurements to record

Use millimetres unless another unit is explicitly stated.

- Chassis length, width, and height.
- Wheel diameter and width.
- Axle spacing and ground clearance.
- Raspberry Pi and HAT mounting-hole locations.
- Battery-holder position and clearance.
- Camera position relative to the chassis and wheel axes.
- Camera-servo pivot position and mechanical tilt limits.
- Approximate total mass and centre-of-mass location.

## Evidence to save

Create a dated evidence folder under Photos/ or the project evidence location
and save:

- overview photographs of the assembled robot;
- close photographs of motor, battery, Pi/HAT, and camera mounting;
- camera-servo bracket and full travel photographs;
- a measurement sketch or annotated photograph;
- a list of deviations from the provisional CAD or Printables reference;
- notes about missing parts, changes, and follow-up work.

Record the date, person performing the work, hardware revision, and result in the
build record in docs/build-notes.md.

## Deferred commissioning

The following are not part of the mechanical assembly session:

- battery charging, connection, or HAT power-up;
- continuity and polarity testing;
- motor or servo movement;
- CuttleOS provisioning or profile activation;
- camera streaming;
- battery-monitor, LED, buzzer, or sensor tests;
- water or environmental testing.

These require the documented safety checks, an independent power cutoff, and a
separate commissioning record. The current CuttleOS ADM133 driver remains
planned/unverified for physical Testbot operation.
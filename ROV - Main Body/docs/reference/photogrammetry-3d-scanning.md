# Photogrammetry and 3D scanning reference

[Raw Mechatronics Orbiter v0.1](https://rawmechatronics.com/projects/orbiter-v0-1/) is a useful reference for building calibrated multi-view capture rather than a direct ROV hardware dependency.

Orbiter uses a two-axis pan/tilt camera rig. Its server coordinates the camera
and actuator, records a photo at each pose, stores the scan session as images
and manifests, and can provide camera-pose priors to COLMAP for structure from
motion and dense point-cloud reconstruction.

## Transferable architecture

1. Calibrate the camera and lens for the exact production optical setup.
2. Move the camera or vehicle through a deliberate set of viewpoints.
3. Capture an image only after motion settles; record timestamp and pose with
   every image.
4. Store an immutable session manifest containing image identity, resolution,
   calibration identity, and pose data.
5. Reconstruct with a photogrammetry pipeline such as COLMAP, then inspect
   reprojection error and point-cloud quality.

The key idea for the ROV is the relationship between each image and its camera
pose. A folder of images without reliable pose, calibration, and timing data is
much less useful for metric reconstruction.

## Optional laser-line mode

A line laser can be added as an active structured-light option to the dual-camera
setup. The laser projects a calibrated plane onto the scene; the camera locates
the bright stripe and triangulates points where the plane intersects the
surface. This can provide useful local surface shape even when passive texture
is weak.

A practical dual-camera arrangement is:

- Camera A: primary laser-stripe measurement camera.
- Camera B: stereo/texture camera for coverage, occlusion checking, and fallback
  photogrammetry.
- Laser: switched only during capture frames, with its optical axis and plane
  calibrated relative to both cameras and the ROV body frame.

The laser mode needs its own calibration data: intrinsics and distortion for
both cameras, the rigid transform between cameras, the laser-plane equation,
and the transform from the camera pair to the vehicle frame. It should not be
assumed that a laser calibrated in air remains accurate through the installed
underwater housing; the housing, window/dome, water, and working distance are
part of the optical system.

Use a hardware-switched, current-limited laser module. Do not drive a laser
 diode directly from a Raspberry Pi GPIO. The ADM133 documentation does not
reserve a validated laser-control pin; select one through the active ROV
profile and switch the module with an appropriate transistor or driver. Include
an explicit laser interlock, startup default-off state, and a capture-timeout
shutoff. Laser safety and eye/underwater-visibility limits must be assessed
before use.

The laser line will be attenuated and scattered by water and suspended matter.
A narrow optical filter matched to the laser wavelength, controlled exposure,
short working distance, and frame differencing can improve detection, but all
must be validated in the actual water and lighting conditions.
## Underwater calibration and fiducials

A high-contrast chessboard can work underwater, but a ChArUco board is preferred
because it remains usable when part of the board is outside the image or
occluded. Use a rigid, matte, waterproof target with measured square and marker
dimensions. Avoid glossy lamination that creates specular reflections.

Calibrate through the complete optical stack: camera, lens, housing window or
dome, and water. The refractive interface changes the apparent camera model, so
a calibration performed with the camera in air or outside its housing should not
be treated as the production calibration.

Separate the calibration tasks:

- Intrinsic calibration: camera matrix and distortion for each camera, using
  many ChArUCO views underwater at the intended resolution, focus, and working
  distance.
- Stereo calibration: relative transform between the two cameras, using a
  target visible to both cameras.
- Laser calibration: the laser plane relative to the measuring camera, with the
  housing and water present.
- Camera-to-ROV calibration: rigid transform from each camera to the ROV body
  or navigation frame, using a surveyed target and known vehicle poses.

Calibration can also vary with depth. Pressure may flex a flat housing port,
distort a dome or window, move the camera mount, or alter the relative pose of
the two cameras. The effect may be negligible for a rigid, shallow-water
housing, but it must be measured rather than assumed away for metric scanning.

For accurate work, calibrate at or near the intended operating depth and repeat
the fixed-fiducial check at several representative depths. If the measured
change is significant, maintain depth-specific calibration profiles or model
the depth-dependent correction. Temperature, salinity, and pressure should be
recorded with the calibration evidence because they can affect the optical and
mechanical conditions.
Fiducials permanently mounted on the ROV are useful as a repeatable check of
camera-to-body alignment and for detecting a shifted camera or housing. They
can also support hand-eye calibration if the ROV is moved through sufficiently
diverse known poses relative to an external reference. However, fixed
fiducials that simply move with a rigid camera assembly do not, by themselves,
provide enough independent geometry to solve all camera intrinsics, stereo
transform, or laser-plane parameters. They are best treated as a validation
fixture after the full calibration.
## ROV-specific constraints

Orbiter is designed for small objects in a controlled, dry environment. An ROV
would additionally need to account for:

- Refraction through the camera housing window or dome; calibrate through the
  installed housing, not with the bare camera.
- Fixed focus, resolution, crop, and exposure settings during a scan.
- Poor visibility, suspended particles, changing illumination, and low surface
  texture underwater.
- Camera motion and vehicle navigation uncertainty; use IMU/pose telemetry and
  time synchronisation where available.
- The ADM133 HAT does not provide the scanner algorithm or camera interface. It
  may provide actuator and sensor I/O, but shared power, motor vibration, and
  GPIO/I2C/SPI resource use must be considered.

A pan/tilt scanner could use the HAT's PCA9685 channels 0-7 for servo outputs
according to the vendor examples, but this is only a candidate allocation and
requires mechanical, load, range, and safety validation.

## Status

- Implemented: external reference and proposed capture architecture documented.
- Automated-test verification: not applicable to reconstruction accuracy.
- Bench-tested: no ROV scanning test recorded.
- Production-validated: no underwater scanning validation recorded.
- Planned or unverified: housing calibration, pose synchronisation, scan
  trajectory, lighting, and reconstruction-quality acceptance criteria.
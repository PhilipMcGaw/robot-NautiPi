# Camera calibration with ArUco and ChArUco

Camera calibration is a prerequisite for reliable geometry from the ROV camera
feeds. It estimates the camera matrix (intrinsic parameters) and distortion
coefficients. These values remain valid unless the camera optics, focus, lens,
or image-processing mode changes.

Use the [OpenCV calibration with ArUco and ChArUco guide](https://docs.opencv.org/4.13.0/da/d13/tutorial_aruco_calibration.html) as the implementation reference.

## Recommended method

Use a ChArUco board where practical. OpenCV recommends ChArUco corners because
they are more accurate than raw ArUco marker corners and allow partial board
occlusion. Capture the board from multiple viewpoints, including different
orientations and positions across the image. Keep the capture resolution and
cropping identical to the production camera-feed mode.

The calibration process should:

1. Detect ChArUco corners in multiple frames.
2. Match the detected image points to the board’s known 3D points.
3. Run `calibrateCamera()` and save the camera matrix and distortion
   coefficients.
4. Record the image size, board square/marker dimensions, camera identity,
   lens/focus state, and reprojection error with the calibration output.
5. Validate the result on held-out frames before enabling pose or measurement
   features.

A standard ArUco GridBoard is an acceptable fallback when a ChArUco board cannot
be used. It is less accurate for calibration because it uses marker corners.

For the wider multi-view reconstruction workflow, see [photogrammetry and 3D scanning](photogrammetry-3d-scanning.md).

## ROV integration notes

Calibration belongs to the camera/media and vision pipeline, not to the ADM133
HAT. The HAT has no documented camera-interface connection. It can nevertheless
affect commissioning through shared Raspberry Pi power, GPIO, I2C/SPI resources,
and electrical noise from motors and LEDs.

Calibration status for the current ROV camera inventory is **Planned or
unverified**. Software support or a successful calibration run is not evidence
of optical or production validation.

## Evidence status

- Implemented: calibration procedure and source reference documented.
- Automated-test verification: not applicable to optical accuracy.
- Bench-tested: no calibration evidence recorded here.
- Production-validated: no camera-specific production evidence recorded here.
- Planned or unverified: camera-specific calibration files, reprojection-error
  acceptance limits, and validation under the final housing and lighting.
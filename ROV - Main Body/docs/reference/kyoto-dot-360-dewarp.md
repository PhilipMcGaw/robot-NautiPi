# Kyoto dot camera: 360-degree dewarp and upload reference

The Kyoto dot camera lens may be usable for a 360-degree video workflow, subject
to testing with the actual sensor, lens, housing, and image crop.

## Candidate references

- [`kscottz/dewarp`](https://github.com/kscottz/dewarp) is a Raspberry Pi
  experiment for dewarping unusual lens imagery.
- [`gigafide/360_pi_cam`](https://github.com/gigafide/360_pi_cam) contains Python
  code intended to dewarp a spherical Raspberry Pi image into usable video for
  YouTube.
- The original Tinkernut build article referenced by `360_pi_cam` is currently
  unavailable at the historical URL:
  `https://www.tinkernut.com/portfolio/make-cheap-360-video-camera-raspberry-pi/`.

These are candidate/legacy references, not approved production dependencies.

## Processing distinction

Dewarping corrects the lens projection. It does not automatically create a
complete spherical panorama. For YouTube 360 playback, the processed output
must be a correctly oriented equirectangular 360-degree video covering the
intended sphere. If the Kyoto lens provides only a fisheye or partial view, the
result may be a rectilinear or wide-angle video rather than a true 360 video.

The processing chain should therefore be treated as:

```text
sensor frames
  -> lens-specific dewarp
  -> stitch/reproject to equirectangular, if required
  -> encode video
  -> inject spherical/360 metadata
  -> verify 360 playback
```

Keep the original frames and the dewarp configuration. Lens centre, radius,
projection, rotation, crop, and output dimensions must be calibrated for the
actual camera assembly rather than copied from an example project.

## YouTube metadata

YouTube's current guidance says that a 180- or 360-degree file must be prepared
before upload, including stitching and a VR-compatible sequence. A metadata
injection step may be required when the encoder has not written the spherical
metadata. Verify the uploaded file after processing by checking that YouTube
shows 360-degree navigation controls.

This metadata identifies how the video should be displayed; it does not correct
lens distortion or turn incomplete coverage into 360-degree coverage.

## ROV considerations

For an underwater installation, perform the optical calibration through the
installed housing and at representative depth. A flat port or dome changes the
projection, and pressure can change it further. Record the camera mode,
resolution, crop, housing, depth, and calibration profile with every processed
video.

The live Cockpit feed and the offline YouTube export are separate products. A
low-latency dewarped preview may use a lower resolution or a simplified mapping,
while the archival/YouTube pipeline should preserve maximum source quality and
explicit processing metadata.

## Status

- Implemented: candidate dewarp references and processing stages documented.
- Automated-test verification: no Kyoto-lens dewarp or spherical-metadata test
  exists.
- Bench-tested: no Kyoto-lens result recorded.
- Production-validated: no underwater or YouTube production result recorded.
- Planned or unverified: lens model, projection, stitching requirement,
  housing-specific calibration, and encoder metadata behaviour.
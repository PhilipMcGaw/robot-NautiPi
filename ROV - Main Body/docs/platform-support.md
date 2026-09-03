# ROV platform support

The active component repositories define their detailed support matrices. This
document records the shared boundary: Cockpit can be developed on Windows,
macOS, and Linux; physical robot control is a Raspberry Pi/Linux concern.

| Capability | Windows | macOS | Linux / Raspberry Pi |
|---|:---:|:---:|:---:|
| Cockpit UI and simulator development | Supported by Cockpit's current launcher | Supported by Cockpit's current launcher | Supported |
| NATS-backed service development | Supported where the component dependencies run | Supported where the component dependencies run | Supported |
| HiL/SiL VM development | Supported host platform where the VM toolchain is available | Supported host platform where the VM toolchain is available | Supported |
| GPIO, I2C, SPI, PWM, serial, cameras, and HAT hardware | Not supported | Not supported | Target platform; requires commissioning |
| Canonical robot provisioning, NetworkManager, SMB, and Avahi | Not supported | Not supported | Target platform; deployment configuration requires bench validation |

Use mocks, Cockpit simulation, or HiL/SiL for Windows and macOS work. A
successful development-server start does not prove the Control loop, camera
path, networking, or hardware output.

## Browser and operator access

Cockpit uses standard browser APIs, including the Browser Gamepad API where a
profile enables it. Pair controllers in the operating system first and test
with propulsion disabled. Browser input is never the only safety mechanism;
Control owns dead-man, neutral, arming, timeout, and output safety behaviour.

The current Cockpit authentication and supported browser details are maintained
in `ROV---Cockpit/docs/`. Use HTTPS for Cockpit access beyond a trusted local
network. Do not copy a historical `Configs/users.json` path from this
repository; Cockpit owns its current authentication configuration.

## Platform rules

- Use component-specific launchers and declared script interpreters.
- Use stable Linux `/dev/serial/by-id/` paths only after device discovery and
  profile/Control configuration.
- Treat a hardware feature as simulated, automated-test verified, bench-tested,
  or production-validated only with corresponding evidence.

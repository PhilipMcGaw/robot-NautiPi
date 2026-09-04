# ROV deployment orientation

The original monolithic `ROV` deployment scripts and `Configs/` directory are
retired and are not present in this repository. Do not recreate or run an old
`setup.sh`, assume `/home/pi/ROV`, or copy historical systemd/Nginx/Motion
configuration from project notes.

## Current deployment ownership

CuttleOS contains the Cockpit, Control, and Datalogger services and owns their
co-located Raspberry Pi deployment. Follow the current CuttleOS provisioner and
service documentation for installation, networking, NATS, and local persistence.

From the CuttleOS repository, read and follow:

```
docs/deployment.md
docs/remote-ssh-access.md
docs/robot-profile-requirements.md
docs/status.md
```

The active robot profile is installed at `/etc/robot/profile.json`. Each robot
has one fixed active profile, loaded during boot. It is a Git-versioned JSON
profile originating from `robot-CuttleOS/configs/profiles/`; switching it is a
reviewed SSH maintenance operation followed by the required restart or reboot,
not a Cockpit UI operation.

## Deployment boundaries

- NATS Core is the internal service-to-service bus. It is loopback-only by
  default; authenticated remote access is enabled only for an explicitly
  trusted HiL/SiL network.
- Cockpit receives NATS server-side and provides browser telemetry over its
  WebSocket. Browsers do not connect directly to NATS.
- Control, not Cockpit, owns physical GPIO, I2C, SPI, PWM, serial, motor, and
  actuator mappings.
- Cockpit owns camera/media configuration and Nginx-facing presentation;
  Control owns network deployment.
- The `192.168.42.0/24` hotspot convention is a *Hitchhiker's Guide to the
  Galaxy* reference. It is not a promise that the subnet is conflict-free.

## First checks

After the component-specific provisioner has completed, run its documented
checks on the Pi. The normal read-only service check is:

```zsh
systemctl status nats-server python cockpit datalogger nginx motion --no-pager
```

Use the Control deployment documentation for `nmcli`, Avahi, SMB, NATS, and
network checks. Do not restart services while propulsion hardware can move.

The deployment configuration exists but has not yet been fully bench-validated
on a clean Raspberry Pi image with the intended hardware.

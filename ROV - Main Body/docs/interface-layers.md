# Robot interface layers

This diagram converts the useful structure from the former ROV overview presentation
into a Markdown-friendly view. It describes the logical interface layers shared
by the ROV, K9, and Testbot. Robot-specific hardware is shown as examples and
must be replaced with the active robot profile and hardware record.

The diagram is intentionally a logical architecture view. It does not replace
the KiCad schematic, wiring record, connector pinout, power budget, or safety
case for a particular robot.

```mermaid
flowchart LR
    operator[Operator device<br/>web browser]
    network[Wi-Fi / local network]

    subgraph robot[Robot boundary]
        subgraph runtime[RPi and CuttleOS runtime]
            cockpit[Cockpit<br/>operator interface]
            nats[NATS Core<br/>application boundary]
            control[Control<br/>commands, safety, hardware drivers]
            logger[Datalogger<br/>telemetry and event recording]
            media[Media services<br/>camera and audio paths]
        end

        subgraph hardware[Hardware interface layer]
            io[GPIO / I2C / UART / USB]
            motor[Motor and load control<br/>H-bridge, PCA9685, relays]
            sensors[Sensors<br/>camera, IMU, depth, temperature, etc.]
            indicators[Indicators and audio<br/>LEDs, buzzer, speaker, microphone]
        end

        power[Robot power system<br/>battery or onboard supply<br/>regulation and protection]
        physical[Physical robot<br/>motors, thrusters, lights,<br/>manipulator, and structure]
    end

    operator -->|HTTP / WebSocket| network
    network --> cockpit
    cockpit --> nats
    nats --> control
    nats --> logger
    nats --> media
    control --> io
    control --> motor
    control --> indicators
    sensors --> io
    sensors --> media
    io --> motor
    io --> sensors
    io --> indicators
    motor --> physical
    indicators --> physical
    power --> hardware
    power --> physical
```

## Layer responsibilities

- The operator device presents the human interface. It does not connect
  directly to NATS or physical hardware.
- Wi-Fi or another network carries the application traffic to the robot. The
  transport can vary by robot without changing the application contract.
- The RPi runs the CuttleOS services. Cockpit handles operator interaction,
  Control owns command validation and safety, Datalogger records agreed data,
  and media services handle camera and audio paths.
- NATS Core carries the application-facing commands and telemetry between the
  CuttleOS services.
- The hardware interface layer maps the robot profile to the physical buses,
  control boards, sensors, indicators, and audio devices.
- The power system is part of the robot hardware boundary. Its regulators,
  protection, distribution, and return paths belong in the hardware records.

For a particular robot, the authoritative implementation is split across the
three repositories: CuttleOS defines the application contract and profile,
NautiPi records the physical implementation, and SquidLink represents the
logical behaviour in ROS 2/Gazebo.
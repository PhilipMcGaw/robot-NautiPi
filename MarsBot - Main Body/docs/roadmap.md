# MarsBot - Main Body roadmap

This roadmap records long-horizon Mars Rover platform direction. Planned work is not implementation, bench validation, or production validation.

## Far-off Mars Rover direction

The OpenRover project report provides a useful long-horizon reference for a
Mars-rover-style platform. These items are roadmap candidates, not current
implementation claims:

- Preserve a modular split between real-time motion control, operator control
  and telemetry UI, and an onboard compute/camera module. Keep the interfaces
  portable across microcontrollers and Raspberry Pi-class computers.
- Evolve the six-wheel platform toward a validated rocker-bogie suspension,
  four-wheel steering, 360-degree turning, per-wheel speed control, and
  calibrated Ackermann geometry to reduce slip on uneven terrain.
- Add a proper rover communications layer with acknowledgements, bounded
  retries, sequence/error detection, link-loss state, and safe degraded-mode
  behaviour. Keep the logical frame contract independent of radio or wired
  transport.
- Develop autonomy in stages: scripted arm/head movements, waypoint and
  obstacle-aware driving, then camera-based target tracking and autonomous
  approach. Treat operator override, stop behaviour, and evidence capture as
  acceptance criteria for each stage.
- Expand onboard sensing and health telemetry for environmental conditions,
  power, compute load, wheel motion, distance, and thermal state, with local
  buffering and later synchronisation when communications are unavailable.
- Replace prototype wiring with serviceable, manufacturable boards and
  standard connectors, documented power distribution, protected electronics,
  and repeatable assembly/test procedures.
- Complete a browser control surface alongside monitoring, while retaining a
  dedicated physical control path and clear authority arbitration between
  local, remote, scripted, and autonomous commands.
- Use the Mars-rover analogy as a systems-engineering target: ruggedness,
  redundancy, dust/temperature awareness, fault containment, low-power modes,
  and high autonomy are design principles to approach progressively rather
  than assumptions about the current ROV hardware.

Source: Pol Valero Arjona, *OpenRover: A 3D-printed open-source robotic
platform for software and hardware development*, final degree project,
June 2025, especially the requirements, communication protocol, conclusions,
and “Future lines of work” sections. The report identifies communication
robustness, computer vision, automatic movements, manufacturable PCBs, and
browser-based control as future work.

Status: captured as a far-off direction only; no Mars-rover capability or
physical validation is implied by this section.

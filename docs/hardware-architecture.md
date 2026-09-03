# NautiPi Hardware Architecture

> **Status:** Authoritative for the physical hardware architecture represented
> by robot-NautiPi.
>
> CuttleOS owns the system-level software architecture and application-facing
> contracts. SquidLink owns simulation and integration-test implementation.

## 1. Purpose

NautiPi is the physical hardware and embedded-project repository. It owns the
physical implementation and evidence needed to build, test, commission, and
maintain robot hardware.

This includes:

- schematics and PCB designs;
- mechanical and CAD designs;
- embedded hardware projects;
- component and assembly records;
- wiring and physical interfaces;
- calibration information;
- photographs and retained engineering evidence;
- physical test and commissioning records.

## 2. Software boundary

CuttleOS defines the application-facing software contract. NautiPi implements
the physical hardware required to satisfy that contract.

```text
CuttleOS application contract
          ↓
        Control
          ↓
   Hardware interface
          ↓
     Physical bus
          ↓
     Embedded node
          ↓
     Physical I/O
```

Hardware design documentation MUST NOT silently redefine the CuttleOS
application contract.

## 3. Distributed nodes

The robot architecture supports distributed microcontroller nodes for physical
I/O where appropriate.

A node should have a recorded:

- manufacturer/device UID;
- configured bus address;
- hardware revision;
- firmware revision;
- capability set;
- installation function/location;
- commissioning and test status.

## 4. Node identity and addressing

The manufacturer's unique device identifier is treated as immutable identity,
not as the normal operational bus address.

The intended relationship is:

```text
Manufacturer UID
      ↓
Physical node identity
      ↓ provisioning
Configured bus address
      ↓
Operational communications
```

This permits address reassignment while retaining traceability to the physical
device.

The exact mechanism depends on the selected microcontroller and embedded
implementation.

## 5. RS-485

RS-485 is the intended physical communications medium for many distributed
nodes where appropriate.

The physical design must establish, and evidence should verify:

- topology;
- termination;
- failsafe biasing where required;
- cable selection and length;
- baud rate;
- node loading;
- grounding and shielding strategy;
- isolation where required;
- connector and wiring arrangements;
- EMC considerations;
- fault behaviour.

The RS-485 physical layer does not define the CuttleOS application contract.

## 6. Bus performance

Bus utilisation should be calculated and, where practical, measured.

The assessment should consider worst-case rather than average traffic, including
message size, update rate, protocol overhead, retries, turnaround time, and the
required control-loop timing.

A bus that appears acceptable under nominal traffic must not be assumed adequate
under worst-case control and telemetry loading.

## 7. Hardware safety

Where practical, hardware nodes should provide an appropriate local safe state
or watchdog independent of the operator interface.

The local mechanism complements rather than replaces CuttleOS Control's
system-level safety policy.

Loss of communications must have a defined hardware response for safety-relevant
outputs.

## 8. Commissioning evidence

Physical commissioning should record enough information to establish exactly
what was tested. At minimum, relevant records should identify:

- hardware revision;
- firmware revision;
- node identity and address;
- test equipment where relevant;
- test conditions;
- measured results;
- pass/fail outcome;
- date and operator;
- associated software/configuration revision.

A design file or photograph is not evidence that hardware has been manufactured,
assembled, commissioned, calibrated, or production-validated.

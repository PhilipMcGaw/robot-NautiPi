# ROV integration repository status

## Role

This repository retains shared ROV hardware design files, physical references,
project records, and integration orientation. Active service implementation and
operational documentation live in the sibling Cockpit, Control, Datalogger,
and HiL/SiL repositories.

## Implemented

- Cross-repository architecture and deployment orientation aligned to the
  current split-service layout.
- Explicit separation of historical root serial/pin notes from current NATS
  contracts, robot profiles, and Control-owned physical mappings.
- Documentation audit and change-policy checks for this repository.

## Automated-test verification

`tests/test_documentation.py` verifies the maintained root documentation set
and required status terminology. `tests/documentation_change_policy.py` checks
that behaviour-affecting root changes include documentation.

## Bench-tested and Production-validated status

This repository does not claim current physical ROV, ADM133, deployment,
network, camera, or production validation. Hardware evidence belongs with the
relevant Control, Cockpit, or HiL/SiL test record.

## Planned or unverified

- Raspberry Pi commissioning evidence for the retained ROV hardware designs
  and historical pin allocations.
- Cross-repository physical deployment, networking, camera, and safety
  validation.
- Consolidation or retirement of further historical research material when it
  is superseded by verified current engineering records.

## References

- `MASTER_CONTEXT.md`
- `docs/documentation-policy.md`
- `docs/roadmap.md`
- `ROV---Cockpit/docs/status.md`
- `ROV---Control/docs/status.md`
- `ROV---Datalogger/docs/status.md`
- `ROV---HiL-and-SiL/docs/status.md`

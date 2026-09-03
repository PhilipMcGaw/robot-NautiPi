# Documentation currency policy

Documentation is an engineering deliverable and must be updated in the same change as the behaviour it describes.

This is a hard completion requirement, not an optional follow-up. A behaviour-affecting change is incomplete until the same change set contains the relevant documentation updates and, where applicable, an updated `MASTER_CONTEXT.md`. Obsolete contradictory documentation must be corrected or removed. “To be documented later” is not an acceptable completion state.

Before reporting a change complete, check the relevant documentation, update the master context when architecture or current behaviour changes, remove stale contradictory text, and record any checks that could not be run.

This repository distinguishes active integration material from historical
reference material. Historical material MUST be labelled as such and MUST NOT
be presented as a current NATS contract, deployment instruction, profile, or
physical mapping. When a current component repository supersedes a root note,
the root note must link or refer to the maintained source of truth.

Run the root documentation checks before reporting an integration/hardware
documentation change complete:

```zsh
python3 tests/test_documentation.py
python3 tests/documentation_change_policy.py <changed repository-relative paths>
```

Use formal British English, SI units, and recognised symbols. State whether a
capability is implemented, automated-test verified, bench-tested,
production-validated, or planned/unverified; software presence alone is not
physical evidence.

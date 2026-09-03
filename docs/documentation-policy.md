# NautiPi documentation policy

Documentation is an engineering deliverable. Documentation that describes a hardware design, embedded project, interface, test result, or validation state MUST be updated when the corresponding information changes.

NautiPi follows the documentation style established for the wider robot project. The simulation repository contains the detailed policy in `robot-SquidLink/docs/documentation-policy.md`; this file records the NautiPi-specific application of that policy.

## Status language

Documentation MUST distinguish between:

- designed or documented;
- implemented;
- assembled;
- electrically tested;
- bench-tested;
- calibrated;
- integrated;
- production-validated;
- planned or unverified.

The existence of KiCad files, firmware, photographs, or historical notes is not evidence that hardware has been assembled, commissioned, calibrated, or production-validated.

A historical design may be retained for reference without implying that it is the current hardware implementation.

## Repository boundaries

NautiPi is the source of truth for the physical hardware design record. It does not define the CuttleOS software implementation, and it does not define the SquidLink simulation implementation.

Hardware documentation may identify intended interfaces, signals, electrical characteristics, and dependencies. It MUST NOT be treated as authorisation for physical wiring or software allocation unless the relevant engineering record explicitly establishes that relationship.

## Written style

Technical documentation shall use formal British English, clear and concise sentences, consistent terminology, and the Oxford comma. Avoid ambiguous pronouns and references such as “this”, “it”, “above”, or “below” where the intended object or location can be named explicitly.

Technical identifiers such as file names, paths, commands, component designators, connector names, signal names, and configuration keys shall be written as code.

## SI units and symbols

Technical quantities shall follow NIST SI conventions.

Use a non-breaking space between numerical values and unit symbols, for example `5 V`, `100 mm`, and `25 °C`. Use the degree symbol `°` where appropriate. Use the micro sign `µ` for the SI prefix micro, not the Greek small letter mu `μ`.

Use commas as thousands separators and a full stop as the decimal separator in prose, for example `1,000` and `1,234.56`. Do not alter machine-readable syntax to apply prose formatting rules.

Use the correct Unicode symbols where appropriate, including `±`, `≤`, `≥`, `Δ`, `θ`, `Ω`, `µ`, and `°`. Use an en dash `–` for numerical ranges and the mathematical minus sign `−` for negative values where rendered technical text permits.

## Cross-references

When referring to another section of the same document, use the section sign `§`, for example, “see §3.2”. Cross-references shall identify the referenced material precisely.

## Hardware evidence

Photographs and historical project material may provide useful evidence of construction or development, but they shall not be used to infer an undocumented electrical characteristic, revision, commissioning state, or production status.

Where a measurement is recorded, the documentation should identify the measurement condition, equipment where relevant, and the date or test record needed to interpret the result.

## Licensing

Hardware design material and project documentation are covered by separate licences. `LICENSES.md` is the authoritative licensing map and shall be updated when the scope of a licence changes.

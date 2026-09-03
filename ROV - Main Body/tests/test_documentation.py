"""ROV integration documentation currency checks."""

from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[1]
REQUIRED = (
    "MASTER_CONTEXT.md",
    "README.md",
    "LICENSES.md",
    "Pins.md",
    "docs/README.md",
    "docs/documentation-policy.md",
    "docs/status.md",
    "docs/roadmap.md",
)
TERMS = (
    "Implemented",
    "Automated-test verification",
    "Bench-tested",
    "Production-validated",
    "Planned or unverified",
)


def main() -> int:
    missing = [path for path in REQUIRED if not (ROOT / path).is_file()]
    if missing:
        print("[FAIL] Missing documentation: " + ", ".join(missing), file=sys.stderr)
        return 1

    documents = [ROOT / "MASTER_CONTEXT.md", ROOT / "README.md", *sorted((ROOT / "docs").glob("*.md"))]
    text = "\n".join(document.read_text(encoding="utf-8") for document in documents)
    missing_terms = [term for term in TERMS if term not in text]
    if missing_terms:
        print("[FAIL] Missing status terms: " + ", ".join(missing_terms), file=sys.stderr)
        return 1

    missing_headings = [str(document.relative_to(ROOT)) for document in documents if not document.read_text(encoding="utf-8").lstrip().startswith("#")]
    if missing_headings:
        print("[FAIL] Documents without Markdown headings: " + ", ".join(missing_headings), file=sys.stderr)
        return 1

    print(f"[PASS] Documentation currency audit passed for {len(documents)} maintained documents.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

"""Require documentation for behaviour-affecting root-repository changes."""

import fnmatch
import json
from pathlib import Path
import sys


ROOT = Path(__file__).resolve().parents[1]


def main() -> int:
    if len(sys.argv) < 2:
        print("[FAIL] Supply changed repository-relative paths.", file=sys.stderr)
        return 1

    rules = json.loads((ROOT / "tests" / "documentation_change_policy.json").read_text(encoding="utf-8"))
    paths = [path.replace("\\", "/") for path in sys.argv[1:] if path]
    documentation_changed = any(
        any(fnmatch.fnmatchcase(path, pattern) for pattern in rules["documentation_patterns"])
        for path in paths
    )
    behaviour = [
        path
        for path in paths
        if any(fnmatch.fnmatchcase(path, pattern) for pattern in rules["documentation_required_patterns"])
    ]
    if behaviour and not documentation_changed:
        print("[FAIL] Behaviour-affecting files changed without documentation: " + ", ".join(behaviour), file=sys.stderr)
        return 1

    print(f"[PASS] Documentation coverage checked for {len(paths)} changed file(s).")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

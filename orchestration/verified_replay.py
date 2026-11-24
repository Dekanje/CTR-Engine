"""Verify immutable run artifacts and replay the existing synthetic native contract."""
import pathlib
import subprocess
import sys
import tempfile

from orchestration import run_manifest

RULES = b"CTR-SYN-INTEGRATED-v1"
CONTENT = b"CTR-SYN-NO-CONTENT-v1"
SCHEMA = b"CTRI\x01\x01\x01\x01"
MAX_ENGINE = 32 * 1024 * 1024


class ReplayError(RuntimeError):
    """Native execution failed; never interpret as a successful replay."""


def verify_and_replay(manifest, artifacts, expected_digest, trusted_engine_path):
    """Caller supplies a trusted local executable and independently trusted digest.

    Linux only. Private temporary copy avoids reopening the original executable
    after verification. This is not a sandbox for hostile binaries or a hostile OS.
    """
    if sys.platform != "linux":
        raise ReplayError("unsupported replay platform")
    if type(artifacts) is not dict:
        raise ValueError("artifact roles")
    parts = artifacts.copy()
    if set(parts) != set(run_manifest.ROLES) or any(type(v) is not bytes for v in parts.values()):
        raise ValueError("artifact roles or types")
    if (not 0 < len(parts["engine"]) <= MAX_ENGINE
            or parts["rules"] != RULES or parts["content"] != CONTENT
            or parts["schema"] != SCHEMA):
        raise ValueError("unsupported replay identity or engine size")
    actions = parts["actions"]
    if len(parts["initial"]) != 26 or len(parts["final"]) != 26 or len(actions) > 128 or len(actions) % 4:
        raise ValueError("replay artifact size")
    run_manifest.verify(manifest, parts, expected_digest)
    try:
        with pathlib.Path(trusted_engine_path).open("rb") as source:
            engine = source.read(MAX_ENGINE + 1)
        if engine != parts["engine"]:
            raise ValueError("trusted executable mismatch")
        request = SCHEMA + parts["initial"] + bytes([len(actions) // 4]) + actions + parts["final"]
        with tempfile.TemporaryDirectory(prefix="ctr-replay-") as directory:
            executable = pathlib.Path(directory) / "ctr_replay"
            executable.write_bytes(engine)
            executable.chmod(0o500)
            result = subprocess.run([str(executable)], input=request, capture_output=True,
                                    timeout=5, check=False, cwd=directory)
    except (OSError, subprocess.TimeoutExpired) as error:
        raise ReplayError("native replay launch or timeout") from error
    if result.returncode != 0:
        raise ReplayError(f"native replay rejected: status {result.returncode}")
    if result.stderr or result.stdout != parts["final"]:
        raise ReplayError("native replay output mismatch")
    return result.stdout

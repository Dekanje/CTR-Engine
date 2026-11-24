"""Canonical, content-addressed run identity. No game-specific material."""
import hashlib
import hmac
import json

ROLES = ("engine", "rules", "content", "schema", "initial", "actions", "final")
MAX_MANIFEST = 4096


def sha256(data):
    if type(data) is not bytes:
        raise ValueError("artifact must be immutable bytes")
    return hashlib.sha256(data).hexdigest()


def canonical(artifacts):
    """Hash exact caller-supplied bytes; never resolve paths or fetch data."""
    if type(artifacts) is not dict or set(artifacts) != set(ROLES):
        raise ValueError("artifact roles")
    entries = {role: {"sha256": sha256(artifacts[role]),
                      "size": len(artifacts[role])} for role in ROLES}
    result = json.dumps({"version": 1, "artifacts": entries},
                        sort_keys=True, separators=(",", ":"),
                        ensure_ascii=True).encode("ascii")
    if len(result) > MAX_MANIFEST:
        raise ValueError("manifest size")
    return result


def verify(manifest, artifacts, expected_digest):
    """Check against an independently trusted digest and exact artifact bytes.

    Does not establish authorization, authenticity of the trusted digest, or
    correctness of the engine. Caller must replay the same verified bytes.
    """
    if type(manifest) is not bytes or len(manifest) > MAX_MANIFEST:
        raise ValueError("manifest size or type")
    if (type(expected_digest) is not str or len(expected_digest) != 64
            or any(c not in "0123456789abcdef" for c in expected_digest)):
        raise ValueError("trusted digest format")
    if not hmac.compare_digest(sha256(manifest), expected_digest):
        raise ValueError("manifest identity mismatch")
    if not hmac.compare_digest(manifest, canonical(artifacts)):
        raise ValueError("artifact or canonical manifest mismatch")
    return expected_digest

"""Validate trusted source-review records; never infer permission or fetch materials."""
from dataclasses import dataclass
from datetime import date
from hashlib import sha256
from hmac import compare_digest


@dataclass(frozen=True)
class Pin:
    source_id: str
    revision: str
    digest: str


@dataclass(frozen=True)
class Scope:
    region: str
    format: str
    event: str
    activity: str
    distribution: str


@dataclass(frozen=True)
class Review:
    pin: Pin
    scope: Scope
    publisher: str
    locator: str
    reviewer: str
    evidence_ref: str
    status: str
    acquired: date
    effective_from: date
    effective_until: date
    reviewed: date
    expires: date


def _text(value):
    return type(value) is str and 0 < len(value) <= 2048 and value == value.strip() and value.isprintable()


def _pin(pin):
    return (type(pin) is Pin and _text(pin.source_id) and _text(pin.revision)
            and type(pin.digest) is str and len(pin.digest) == 64
            and all(c in "0123456789abcdef" for c in pin.digest))


def _scope(scope):
    return type(scope) is Scope and all(_text(v) and v != "*" for v in vars(scope).values())


def verify_profile(pins, scope, rules_date, review_date, trusted_reviews, artifacts):
    """Require one exact trusted admission per pin; return immutable verified bytes.

    The caller must establish the completeness of pins, authentic review records,
    actual review date and source precedence. This is not a legal decision engine.
    Dates are inclusive; no open-ended permissions or wildcard scope matching.
    """
    if (type(pins) is not tuple or not 0 < len(pins) <= 64 or not all(_pin(p) for p in pins)
            or len({p.source_id for p in pins}) != len(pins)):
        raise ValueError("invalid or duplicate source pins")
    if not _scope(scope) or type(rules_date) is not date or type(review_date) is not date:
        raise ValueError("invalid profile scope or date")
    if type(trusted_reviews) is not tuple or len(trusted_reviews) != len(pins):
        raise ValueError("review count")
    if type(artifacts) is not dict or set(artifacts) != {p.source_id for p in pins}:
        raise ValueError("artifact set")
    by_id = {}
    for record in trusted_reviews:
        if type(record) is not Review or not _pin(record.pin) or not _scope(record.scope):
            raise ValueError("invalid review record")
        if record.pin.source_id in by_id:
            raise ValueError("ambiguous review")
        by_id[record.pin.source_id] = record
    verified = []
    for pin in pins:
        record = by_id.get(pin.source_id)
        if record is None or record.pin != pin or record.scope != scope or record.status != "admitted":
            raise ValueError("source not admitted for exact profile")
        if not all(_text(v) for v in (record.publisher, record.locator, record.reviewer, record.evidence_ref)):
            raise ValueError("incomplete provenance")
        dates = (record.acquired, record.effective_from, record.effective_until, record.reviewed, record.expires)
        if not all(type(d) is date for d in dates):
            raise ValueError("invalid review dates")
        if not (record.acquired <= record.reviewed <= review_date <= record.expires
                and record.effective_from <= rules_date <= record.effective_until):
            raise ValueError("source outside effective or review interval")
        data = artifacts[pin.source_id]
        if type(data) is not bytes or not 0 < len(data) <= 32 * 1024 * 1024:
            raise ValueError("artifact size or type")
        if not compare_digest(sha256(data).hexdigest(), pin.digest):
            raise ValueError("source digest mismatch")
        verified.append((pin, data))
    return tuple(verified)

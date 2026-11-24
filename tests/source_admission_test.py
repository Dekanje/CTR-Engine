import pathlib
import sys
import unittest
from dataclasses import replace
from datetime import date
from hashlib import sha256

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1]))
from orchestration import source_admission as a


class AdmissionTest(unittest.TestCase):
    def setUp(self):
        self.day = date(2026, 11, 25)
        self.scope = a.Scope("test-region", "test-format", "standard", "offline-test", "private")
        self.parts = {"core": b"original test bytes", "update": b"original test update"}
        self.pins = tuple(a.Pin(k, "v2", sha256(v).hexdigest()) for k, v in self.parts.items())
        self.reviews = tuple(a.Review(p, self.scope, "test publisher", "test locator", "test reviewer",
                                      "test review reference", "admitted", self.day, self.day,
                                      date(2026, 12, 1), self.day, date(2026, 12, 31)) for p in self.pins)

    def verify(self, **changes):
        args = dict(pins=self.pins, scope=self.scope, rules_date=self.day, review_date=self.day,
                    trusted_reviews=self.reviews, artifacts=self.parts)
        return a.verify_profile(**(args | changes))

    def test_exact_profile_and_order(self):
        expected = tuple((p, self.parts[p.source_id]) for p in self.pins)
        self.assertEqual(self.verify(), expected)
        self.assertEqual(self.verify(trusted_reviews=self.reviews[::-1]), expected)
        self.assertEqual(self.verify(rules_date=date(2026, 12, 1), review_date=date(2026, 12, 31)), expected)

    def test_source_identity_and_bytes(self):
        for name, data in self.parts.items():
            for n in range(len(data)):
                with self.subTest(name=name, offset=n), self.assertRaises(ValueError):
                    bad = bytearray(data); bad[n] ^= 1
                    self.verify(artifacts=self.parts | {name: bytes(bad)})
            for bad in (b"", bytearray(data), b"x" * (32 * 1024 * 1024 + 1)):
                with self.assertRaises(ValueError):
                    self.verify(artifacts=self.parts | {name: bad})
        for pin in (replace(self.pins[0], revision="v1"), replace(self.pins[0], digest="0" * 64),
                    replace(self.pins[0], digest="Z" * 64)):
            with self.assertRaises(ValueError):
                self.verify(pins=(pin, self.pins[1]))

    def test_review_and_scope(self):
        for field in vars(self.scope):
            with self.assertRaises(ValueError):
                self.verify(scope=replace(self.scope, **{field: "other"}))
        for field, value in (("status", "pending"), ("status", "denied"), ("evidence_ref", ""),
                             ("reviewer", " "), ("publisher", ""), ("locator", ""),
                             ("expires", date(2026, 11, 24)), ("reviewed", date(2026, 11, 26)),
                             ("acquired", date(2026, 11, 26)), ("effective_from", date(2026, 11, 26)),
                             ("effective_until", date(2026, 11, 24)), ("expires", None)):
            with self.subTest(field=field, value=value), self.assertRaises(ValueError):
                self.verify(trusted_reviews=(replace(self.reviews[0], **{field: value}), self.reviews[1]))
        for changes in ({"rules_date": date(2026, 12, 2)}, {"review_date": date(2027, 1, 1)},
                        {"scope": replace(self.scope, event="*")}, {"rules_date": "2026-11-25"}):
            with self.assertRaises(ValueError):
                self.verify(**changes)

    def test_missing_ambiguous_and_extra(self):
        for changes in ({"pins": ()}, {"pins": (self.pins[0], self.pins[0])},
                        {"trusted_reviews": ()}, {"trusted_reviews": (self.reviews[0], self.reviews[0])},
                        {"artifacts": {"core": self.parts["core"]}}, {"artifacts": self.parts | {"extra": b"x"}}):
            with self.assertRaises(ValueError):
                self.verify(**changes)


if __name__ == "__main__":
    unittest.main()

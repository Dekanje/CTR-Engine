import hashlib
import itertools
import json
import pathlib
import sys
import unittest

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1]))
from orchestration import run_manifest as m


class ManifestTest(unittest.TestCase):
    def setUp(self):
        self.parts = {role: bytes([i, 255, 0]) for i, role in enumerate(m.ROLES)}
        self.manifest = m.canonical(self.parts)
        self.digest = hashlib.sha256(self.manifest).hexdigest()

    def test_known_digest_and_structure(self):
        self.assertEqual(m.sha256(b"abc"),
                         "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad")
        obj = json.loads(self.manifest)
        self.assertEqual(obj["version"], 1)
        self.assertEqual(set(obj), {"version", "artifacts"})
        for role, data in self.parts.items():
            self.assertEqual(obj["artifacts"][role],
                             {"sha256": hashlib.sha256(data).hexdigest(), "size": 3})
        self.assertEqual(m.verify(self.manifest, self.parts, self.digest), self.digest)

    def test_all_registration_orders(self):
        for order in itertools.permutations(m.ROLES):
            self.assertEqual(m.canonical({r: self.parts[r] for r in order}), self.manifest)

    def test_artifact_mutations(self):
        for role in m.ROLES:
            for offset in range(3):
                for bit in range(8):
                    altered = dict(self.parts)
                    data = bytearray(altered[role]); data[offset] ^= 1 << bit
                    altered[role] = bytes(data)
                    with self.assertRaises(ValueError):
                        m.verify(self.manifest, altered, self.digest)
            for data in (b"", self.parts[role] + b"x", bytearray(b"abc")):
                with self.assertRaises(ValueError):
                    m.verify(self.manifest, dict(self.parts, **{role: data}), self.digest)
            missing = dict(self.parts); del missing[role]
            with self.assertRaises(ValueError):
                m.canonical(missing)
        with self.assertRaises(ValueError):
            m.canonical(dict(self.parts, extra=b"x"))

    def test_manifest_mutations(self):
        for offset in range(len(self.manifest)):
            bad = bytearray(self.manifest); bad[offset] ^= 1
            with self.assertRaises(ValueError):
                m.verify(bytes(bad), self.parts, self.digest)
        # Even a rehashed malformed or noncanonical manifest is rejected.
        for bad in (self.manifest + b"\n", b"{}", b"\xff", b"x" * 4097,
                    self.manifest.replace(b'"version":1', b'"version":2'),
                    self.manifest.replace(b'"version":1', b'"version":1,"version":1')):
            with self.assertRaises(ValueError):
                m.verify(bad, self.parts, hashlib.sha256(bad).hexdigest())
        for digest in (None, "", "z" * 64, self.digest.upper(), "0" * 64):
            with self.assertRaises(ValueError):
                m.verify(self.manifest, self.parts, digest)
        altered = dict(self.parts, engine=b"new engine")
        regenerated = m.canonical(altered)
        with self.assertRaises(ValueError):
            m.verify(regenerated, altered, self.digest)


if __name__ == "__main__":
    unittest.main()

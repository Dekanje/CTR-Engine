import pathlib
import subprocess
import sys
import unittest
from unittest.mock import patch

sys.path.insert(0, str(pathlib.Path(__file__).resolve().parents[1]))
from orchestration import run_manifest as m
from orchestration import verified_replay as r

ENGINE = pathlib.Path(sys.argv.pop(1)).resolve()


class ReplayTest(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        cls.engine = ENGINE.read_bytes()

    def setUp(self):
        # Independent expected state: first reveal exposes slot 0, costs two,
        # credits the other player one and transfers priority.
        initial = bytes([1, 0, 0, 0, 10, 10]) + bytes(20)
        final = bytes([1, 0, 1, 0, 8, 11, 1]) + bytes(19)
        self.parts = dict(engine=self.engine, rules=r.RULES, content=r.CONTENT,
                          schema=r.SCHEMA, initial=initial, actions=bytes([1, 0, 1, 0]), final=final)

    def invoke(self, parts):
        manifest = m.canonical(parts)
        return r.verify_and_replay(manifest, parts, m.sha256(manifest), ENGINE)

    def raw(self, request):
        return subprocess.run([str(ENGINE)], input=request, capture_output=True, timeout=5)

    def request(self):
        p = self.parts
        return p["schema"] + p["initial"] + b"\x01" + p["actions"] + p["final"]

    def test_valid(self):
        self.assertEqual(self.invoke(self.parts), self.parts["final"])
        empty = dict(self.parts, actions=b"", final=self.parts["initial"])
        self.assertEqual(self.invoke(empty), empty["final"])
        # Next player passes; priority returns to player 0, passed flag set.
        final = bytearray(self.parts["final"]); final[2:4] = b"\x00\x01"
        two = dict(self.parts, actions=self.parts["actions"] + bytes([1, 1, 0, 0]), final=bytes(final))
        self.assertEqual(self.invoke(two), two["final"])

    def test_preflight(self):
        manifest = m.canonical(self.parts); digest = m.sha256(manifest)
        with patch.object(r.subprocess, "run") as launch:
            for role in m.ROLES:
                bad = dict(self.parts, **{role: self.parts[role] + b"x"})
                with self.assertRaises(ValueError):
                    r.verify_and_replay(manifest, bad, digest, ENGINE)
            for role in ("engine", "rules", "content", "schema"):
                bad = dict(self.parts, **{role: b"wrong"})
                with self.assertRaises(ValueError):
                    self.invoke(bad)
            for actions in (b"x", bytes(132)):
                with self.assertRaises(ValueError):
                    self.invoke(dict(self.parts, actions=actions))
            with self.assertRaises(ValueError):
                r.verify_and_replay(manifest, self.parts, "0" * 64, ENGINE)
            launch.assert_not_called()

    def test_native_rejections(self):
        frame = self.request()
        for n in range(len(frame)):
            result = self.raw(frame[:n])
            self.assertEqual((result.returncode, result.stdout), (2, b""))
        for bad in (frame + b"x", frame + bytes(200), frame[:34] + b"\x21" + frame[35:]):
            result = self.raw(bad)
            self.assertEqual((result.returncode, result.stdout), (2, b""))
        for pos in (0, 8, 35, 39):
            bad = bytearray(frame); bad[pos] = 255
            result = self.raw(bytes(bad))
            self.assertEqual((result.returncode, result.stdout), (3, b""))
        with self.assertRaisesRegex(r.ReplayError, "status 3"):
            self.invoke(dict(self.parts, final=self.parts["initial"]))
        with self.assertRaisesRegex(r.ReplayError, "status 3"):
            self.invoke(dict(self.parts, actions=bytes([1, 1, 1, 2])))

    def test_worker_failures(self):
        for result in (subprocess.CompletedProcess([], 0, b"wrong", b""),
                       subprocess.CompletedProcess([], 0, self.parts["final"], b"error"),
                       subprocess.CompletedProcess([], 4, b"", b"")):
            with patch.object(r.subprocess, "run", return_value=result):
                with self.assertRaises(r.ReplayError):
                    self.invoke(self.parts)
        with patch.object(r.subprocess, "run", side_effect=subprocess.TimeoutExpired([], 5)):
            with self.assertRaises(r.ReplayError):
                self.invoke(self.parts)


if __name__ == "__main__":
    unittest.main()

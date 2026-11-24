"""Cross-process feasibility checks; not Riftbound behavioral tests."""
import subprocess
import sys
import unittest


class ProbeProtocol(unittest.TestCase):
    def test_repeatability(self):
        for _ in range(10):
            result = subprocess.run([PROBE], capture_output=True, timeout=3)
            self.assertEqual((result.returncode, result.stdout, result.stderr),
                             (0, b"ctr-probe-v1:42\n", b""))

    def test_reject_unknown_argument(self):
        result = subprocess.run([PROBE, "--unknown"], capture_output=True, timeout=3)
        self.assertEqual((result.returncode, result.stdout, result.stderr),
                         (2, b"", b""))


if __name__ == "__main__":
    PROBE = sys.argv.pop(1)
    unittest.main()

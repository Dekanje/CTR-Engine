# Evidence index

## CTR-E0001 — synthetic native feasibility, 2026-11-24
Execution environment: Linux x86_64; GCC 14.2.0 (Debian 14.2.0-19), Clang 17.0.0 (10999b6d034fe318f3d56c83bddb6572593a8bb0), CMake 3.31.6, Python 3.13.5, Git 2.47.3.

Exact locally tested Git blob IDs and SHA-256:
| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | 0a43b614be3d33723c93b03efbbae78b1d184b7d | a9247084a3d5088abc3c5890192ad008191d22994622f35c53593ee2b0b82fa6 |
| src/probe.cpp | 395c06320a7b2b3807a36ae1c549e88d7319a245 | 69bda40464cbf8f21e930cd76be47c4b92e1c4be0b4205a8b6cd049cc8076a64 |
| tests/probe_test.py | 46bc3d51058851ca740abb71ffda4c4d89451bad | dbacf10080f46edcdc4c6a420c157d596f0099b9bcc1060c12b926f70488ac8b |

Commands per compiler (g++/clang++) and mode (Debug/Release): cmake -S . -B <build> -DCMAKE_CXX_COMPILER=<compiler> -DCMAKE_BUILD_TYPE=<mode>; cmake --build <build> --parallel 2; ctest --test-dir <build> --output-on-failure.

| Build | Native protocol | Python protocol | Total CTest wall time |
| --- | --- | --- | --- |
| GCC Debug | PASS | PASS | 0.69 s |
| GCC Release | PASS | PASS | 0.67 s |
| Clang Debug | PASS | PASS | 0.79 s |
| Clang Release | PASS | PASS | 0.74 s |

8 CTest executions, 0 failures. Each Python suite repeats valid process output ten times and checks one invalid-argument rejection. No stochastic samples, seeds, game rules, agents, deck hashes or native games; these are not applicable. Wall times are test timings, not performance benchmarks. No CI ran. No external dependencies or historical project inputs. Tested source is identified by blob hash because local testing preceded publication. Verify published hashes before claiming source equivalence.

### Publication verification
Implementation commit e5cb2c73e654db5945cf02f906adc297f296659b, verified on main on 2026-11-24. All three published Git blob IDs exactly matched the tested local source identities listed above. All ten continuity documents were fetched at the implementation commit. No game or CI evidence claimed. CTR-0.1 baseline acceptance criteria satisfied; subsequent gates remain provisional.

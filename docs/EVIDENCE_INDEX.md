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

## CTR-E0002 — deterministic primitives and synthetic replay, 2026-11-24

Parent ae64ed534d8f3b601fac594e6fb7c78382cade4c; implementation a3a572e407e9ab7840da891e46ed33dd545f5fea. Recovered local session002 source after interrupted publication, reviewed it and reran all builds/tests before publishing. Same Linux x86_64 toolchain versions as E0001 (GCC 14.2.0, Clang 17.0.0, CMake 3.31.6, Python 3.13.5, Git 2.47.3). Exact tested identities:

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | 6a385e14ff0e2de13d7d4fe1c37d4f2562026898 | 3b10d7d5de95d66b7d5c7b69cc30da685def98f83728544453d47136ab66963c |
| include/ctr/core.hpp | dc0ce85ef249fbaabb2e096bad5851a1719b208b | d82a67b61a3e24122dc59508303beede4cdc46290da14cb94e592c13f60a5f64 |
| tests/core_test.cpp | a9b4ec0dcc3842fcdc51b19ee74f09f59ef76a1c | fcdf7c9e543ee05107d25ab064a0e5375e67f18d31eed4358cc4d0ba6cd53dfa |
| src/probe.cpp | 395c06320a7b2b3807a36ae1c549e88d7319a245 | 69bda40464cbf8f21e930cd76be47c4b92e1c4be0b4205a8b6cd049cc8076a64 |
| tests/probe_test.py | 46bc3d51058851ca740abb71ffda4c4d89451bad | dbacf10080f46edcdc4c6a420c157d596f0099b9bcc1060c12b926f70488ac8b |

All five fetched at implementation commit and matched before updating main. Build with CMake, g++ or clang++, Debug or Release; cmake --build <build> --parallel 2; ctest --test-dir <build> --output-on-failure. Sanitizer build Clang Debug with -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer; ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1.

| Build | CTest passed | Wall time |
| --- | --- | --- |
| GCC Debug | 3/3 | 1.27 s |
| GCC Release | 3/3 | 0.95 s |
| Clang Debug | 3/3 | 1.15 s |
| Clang Release | 3/3 | 0.98 s |
| Clang ASan/UBSan | 3/3 | 3.52 s |

15/15 CTest executions, zero failures on this rerun. Additionally ran core executable directly in all five configurations: rng-v1:871378669735641285 and core-v1:1000 traces:4864969216242844801 identical. Each core execution checks 65,536 version-1 payload combinations for each state and event encoding (131,072 total), 196 valid states x 8 well-formed events = 1,568 transition combinations, malformed version/size examples, typed-ID compile-time checks, rejection sampling boundaries, 1,000 stream isolation iterations, and 1,000 synthetic traces with replay of every prefix. Seed roots 42 (run 7, comparison run 8) and 123456 (runs 0..999), domains 1/2/3. Same fixtures across configurations, not independent random experiments. No sanitizer diagnostics reported. Fingerprint is a regression check, not a cryptographic hash. No statistical independence claim, no performance benchmark, no actual games or competitive results; uncertainty intervals not applicable to these deterministic tests. No CI jobs dispatched.

Baseline acceptance: stable synthetic encoding, explicit chance, bounded random sampling, stream isolation, illegal input rejection, cross-build replay and property checks all evidenced. CTR-0.2 baseline gate satisfied. CTR-1 game-specific implementation blocked by rights/provenance.

## CTR-E0003 — CTR-1 generic kernel subtask A, 2026-11-24

Parent 764ed77d7a6ac4109f204536dc4fe4baca39036d; implementation ae649d188d792a6a3e14dd61842b59e895d8417b. Ten continuity documents read, five local baseline source identities matched prior GitHub blobs. Prior GCC Release regression 3/3 CTest passed (1.17 s). No workflow directory present; commit workflow query returned no runs (connector scope limited to PR-triggered runs). No CI dispatched.

Locally tested source identities, verified against candidate commit before main advanced:

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | 5c9b2c45345b19c6390c9efafa16ad1613c00347 | f34c938c2a666a8de2896a4917dc1c9d84259cdcaf3adc7ca9403a9742bbfd11 |
| include/ctr/core.hpp | dc0ce85ef249fbaabb2e096bad5851a1719b208b | d82a67b61a3e24122dc59508303beede4cdc46290da14cb94e592c13f60a5f64 |
| include/ctr/kernel.hpp | fd14b2b69cc5e03e4d87c3d5b5da4f152bfe0e0a | 627138cf03a4943763e9a3e8bf41b7892785f4c8b5fa72d7eb625e600b2ab875 |
| tests/core_test.cpp | a9b4ec0dcc3842fcdc51b19ee74f09f59ef76a1c | fcdf7c9e543ee05107d25ab064a0e5375e67f18d31eed4358cc4d0ba6cd53dfa |
| tests/kernel_test.cpp | 6e755fa477631f50f440e66cfa5696ccc09e47ff | 75d119ade53c011385bafcd7bb4a73dde64974969b526145a3111071eb838d87 |
| src/probe.cpp | 395c06320a7b2b3807a36ae1c549e88d7319a245 | 69bda40464cbf8f21e930cd76be47c4b92e1c4be0b4205a8b6cd049cc8076a64 |
| tests/probe_test.py | 46bc3d51058851ca740abb71ffda4c4d89451bad | dbacf10080f46edcdc4c6a420c157d596f0099b9bcc1060c12b926f70488ac8b |

Linux x86_64, same local toolchain as E0002; GCC 14.2.0 and Clang 17.0.0 reconfirmed. CMake configure with compiler and build mode, build --parallel 2, ctest --test-dir <build> --output-on-failure. Clang sanitizer Debug uses -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer; ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1.

| Build | CTest passed | Wall time |
| --- | --- | --- |
| GCC Debug | 4/4 | 0.94 s |
| GCC Release | 4/4 | 0.90 s |
| Clang Debug | 4/4 | 1.10 s |
| Clang Release | 4/4 | 0.99 s |
| Clang ASan/UBSan | 4/4 | 3.66 s |

20/20 CTest executions passed, no sanitizer diagnostics. All five direct kernel runs: kernel-v1:208 states:6240 candidates:416 projections. All five direct core runs: rng-v1:871378669735641285 and core-v1:1000 traces:4864969216242844801. Combined shell tool timed out after all CTest runs and first four direct core outputs plus fifth kernel output; direct fifth core rerun succeeded. No code correction needed; no test failure.

Each new fixture test exhausts 16 visibility masks x (12 nonterminal structural combinations + 1 terminal) = 208 valid structural states (fixed labels), rejects 48 invalid terminal structural states, checks both viewer projections (416), checks 6,240 actor/action/target candidates including invalid kind and target, tests exact action enumeration, expected transition/invariants and opponent-private-label perturbation noninterference. Additional invalid actor/viewer/zone examples. Synthetic rule mapping SYN-K01..05 in RULE_TRACEABILITY.md. Counts are repeated per configuration, not independent random trials; new fixture uses no RNG. Previous seed roots unchanged per E0002. No official rules or deck hashes, no game samples, no competitive inference or statistical intervals. Timings are tests, not benchmark.

Subtask A validated; full CTR-1 gate NOT accepted. Manual ledger created with no official sources admitted; no machine enforcement or legal verification. Remaining generic and authorized game-specific work explicit in handover.

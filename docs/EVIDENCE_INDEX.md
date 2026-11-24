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

## CTR-E0004 — CTR-1 generic subtask B, 2026-11-24

Parent 96a4336ecfb1fdf60e91dd2acc20bea64290b2ac; implementation 3aac314886d83cdb4b159e84d097a58f10847cd8. Reviewed twelve continuity/source documents and verified seven prior local source hashes against recorded repository evidence. Local Linux x86_64, GCC 14.2.0, Clang 17.0.0, CMake 3.31.6, Python 3.13.5, Git 2.47.3. Exact tested Git blobs (all nine verified on candidate commit before publishing):

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | b8d148d146031d8b745f817633bd1c086235b6a5 | 3fa7bc53fbf9833ec191efab0848ad196941fd30d129403ed862aa0b485947b3 |
| include/ctr/core.hpp | dc0ce85ef249fbaabb2e096bad5851a1719b208b | d82a67b61a3e24122dc59508303beede4cdc46290da14cb94e592c13f60a5f64 |
| include/ctr/effects.hpp | 38213b24adac1a826c2e4e402bd1f921f4dfb50d | 66b32bdcba77346216e048383b68c4eb5802357e308221336eb3041ede000267 |
| include/ctr/kernel.hpp | fd14b2b69cc5e03e4d87c3d5b5da4f152bfe0e0a | 627138cf03a4943763e9a3e8bf41b7892785f4c8b5fa72d7eb625e600b2ab875 |
| src/probe.cpp | 395c06320a7b2b3807a36ae1c549e88d7319a245 | 69bda40464cbf8f21e930cd76be47c4b92e1c4be0b4205a8b6cd049cc8076a64 |
| tests/core_test.cpp | a9b4ec0dcc3842fcdc51b19ee74f09f59ef76a1c | fcdf7c9e543ee05107d25ab064a0e5375e67f18d31eed4358cc4d0ba6cd53dfa |
| tests/effect_test.cpp | 6ef6a30e8ade4edd4afa31e2519b33ab8e6c2946 | 66b4424f8ed2fe1871bf871ba92832f92c60d50851fe7c9bb75923ff3ab71d25 |
| tests/kernel_test.cpp | 6e755fa477631f50f440e66cfa5696ccc09e47ff | 75d119ade53c011385bafcd7bb4a73dde64974969b526145a3111071eb838d87 |
| tests/probe_test.py | 46bc3d51058851ca740abb71ffda4c4d89451bad | dbacf10080f46edcdc4c6a420c157d596f0099b9bcc1060c12b926f70488ac8b |

Commands: cmake -S . -B <build> -DCMAKE_CXX_COMPILER=<g++/clang++> -DCMAKE_BUILD_TYPE=<Debug/Release>; cmake --build <build> --parallel 2; ctest --test-dir <build> --output-on-failure. Clang sanitizer Debug CMAKE_CXX_FLAGS='-fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer'; ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1.

| Build | CTest passed | Wall time |
| --- | --- | --- |
| GCC Release | 5/5 | 0.97 s |
| GCC Debug | 5/5 | 1.16 s |
| Clang Debug | 5/5 | 1.20 s |
| Clang Release | 5/5 | 0.99 s |
| Clang ASan/UBSan | 5/5 | 4.56 s |

25/25 final CTest executions passed, no sanitizer diagnostics. Combined shell command timed out during first sanitizer CTest invocation; standalone full sanitizer rerun passed 5/5, no source correction needed. All five direct effect test outputs identical: effects-v1:40400 balance cases:2880 permutations. Each effect execution checks 101 balances x 100 amounts x 2 targets x 2 kinds with arithmetic oracle and input equality; 4! x 5! permutations of registration order against exact six-record oracle; replacement self/two-event cycles, trigger recursion, fan-out, late invalid transition, exact budget success, malformed input and program rejection. No RNG used by new tests; prior core seed roots unchanged. Counts repeat across configurations, not independent statistical trials. No game/deck hashes or game samples, no benchmark or competitive inference; no statistical intervals applicable. No cloud jobs dispatched. Subtask B validated only; full CTR-1 gate open.

## CTR-E0005 — CTR-1 generic subtask C, 2026-11-24

Parent abf264aa1cfd227c80bc33305e83360df7d6da66; implementation ee53d3104c5621772907209c93a3500ff56cf78c. Prior session interrupted before publishing. Recovered local source from ctr-session005, inspected it and reran all five build configurations. Twelve continuity/source documents and permanent project instructions reviewed. GitHub prior source hashes matched CTR-E0004; eight unchanged files retained exact hashes, and CMakeLists.txt extends prior configuration. Workflow query returned no runs (PR-triggered scope); no CI dispatched. Local Linux x86_64, GCC 14.2.0, Clang 17.0.0, CMake 3.31.6. Tested source identities, all eleven verified at candidate commit before main advanced:

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | 4c03e383e95d955f93ec52978ac60bca3bd8dfcf | 695f558b283bfa3c64e5390d1af7e54141b25cc9ae381d2ca973ee9094d53c14 |
| include/ctr/core.hpp | dc0ce85ef249fbaabb2e096bad5851a1719b208b | d82a67b61a3e24122dc59508303beede4cdc46290da14cb94e592c13f60a5f64 |
| include/ctr/effects.hpp | 38213b24adac1a826c2e4e402bd1f921f4dfb50d | 66b32bdcba77346216e048383b68c4eb5802357e308221336eb3041ede000267 |
| include/ctr/integrated.hpp | dba2cd03efaea71b95c8fe4f9c3626c99c3a3987 | e5e6a7eac7b83f0a968379aadd3d02e5992f7638b9c326ea3fdb7f4ee29cea65 |
| include/ctr/kernel.hpp | fd14b2b69cc5e03e4d87c3d5b5da4f152bfe0e0a | 627138cf03a4943763e9a3e8bf41b7892785f4c8b5fa72d7eb625e600b2ab875 |
| src/probe.cpp | 395c06320a7b2b3807a36ae1c549e88d7319a245 | 69bda40464cbf8f21e930cd76be47c4b92e1c4be0b4205a8b6cd049cc8076a64 |
| tests/core_test.cpp | a9b4ec0dcc3842fcdc51b19ee74f09f59ef76a1c | fcdf7c9e543ee05107d25ab064a0e5375e67f18d31eed4358cc4d0ba6cd53dfa |
| tests/effect_test.cpp | 6ef6a30e8ade4edd4afa31e2519b33ab8e6c2946 | 66b4424f8ed2fe1871bf871ba92832f92c60d50851fe7c9bb75923ff3ab71d25 |
| tests/integrated_test.cpp | 7283da8bcfb822a7b6c63939e07e2b5bebe1ead1 | f9e419ce591a6efbba73c9101d0b14100af30bfbe8bec72a37db1a413856822a |
| tests/kernel_test.cpp | 6e755fa477631f50f440e66cfa5696ccc09e47ff | 75d119ade53c011385bafcd7bb4a73dde64974969b526145a3111071eb838d87 |
| tests/probe_test.py | 46bc3d51058851ca740abb71ffda4c4d89451bad | dbacf10080f46edcdc4c6a420c157d596f0099b9bcc1060c12b926f70488ac8b |

Fresh rerun: cmake --build <existing-build> --parallel 2; ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1 ctest --test-dir <build> --output-on-failure; direct ctr_integrated_test. CMake cache checked for compiler/build mode and sanitizer flags -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer. No code changes needed on this rerun; an attempted streaming shell invocation was unsupported and retried with regular execution. Prior interrupted session reported correction of two one-action array deduction expressions; recovered corrected source contains explicit std::array<ActionBytes,1> in both places, and fresh tests verify them.

| Build | CTest passed | Wall time |
| --- | --- | --- |
| GCC Debug | 6/6 | 1.12 s |
| GCC Release | 6/6 | 0.92 s |
| Clang Debug | 6/6 | 1.42 s |
| Clang Release | 6/6 | 1.03 s |
| Clang ASan/UBSan | 6/6 | 4.61 s |

30/30 fresh CTest executions passed; no sanitizer diagnostics reported. All five direct integration outputs: integrated-v1:3072 candidates:1536 projections. Each checks 16 masks x 2 priority holders x 6 own balances x 4 other balances = 768 combinations, 4 reveal targets each, both viewer projections with hidden-label perturbation, pass checks, resource/zone state and replay checks, fixed nine-action terminal trace and malformed input examples. Counts repeat across configurations; no new RNG used. Previous core RNG seeds as in E0002. No native game/deck/agent hashes, actual games or statistical intervals; timings are test timings. No paid cloud or game material imports. Subtask C generic integration validated only; CTR-1 full acceptance NOT satisfied.

## CTR-E0006 — CTR-1 generic subtask D, 2026-11-24

Parent 66844d4cba872a1b82b9d88dd90bb4c87fe44e05; implementation and evidence reside in the same publication commit. Reviewed twelve continuity/source documents and permanent project instructions; eleven prior local source identities match CTR-E0005. No workflow runs returned for parent; no CI dispatched. Local Linux x86_64. Exact source identities computed after final tests:

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | b6c6089c7548057d891f88fa4b4b694e82777fa8 | 7c62464b97eac13e9aff3a9ccd2688d1b785f1bb34ff11bf2193f09f9cbca08a |
| include/ctr/conflict.hpp | 6dd88bccd4d4cf37cf65e00cc9b3e02c7a8f73c9 | 81ca53c41d43ea7f03954ed29afc199a93358cde99b649742c9a809df07a3508 |
| tests/conflict_test.cpp | b4e30168f73e11c52c77fe128d04687f3692d691 | c4e4dfc9c8e6ac1f1af76e9821e27c59a4376b83408b97e7b0310e26458376d2 |

The remaining ten source files retain their exact identities listed in CTR-E0005 (everything except CMakeLists.txt). Publication requires all thirteen identities match candidate tree before moving main.

Commands: cmake -S . -B <build> -DCMAKE_CXX_COMPILER=<g++/clang++> -DCMAKE_BUILD_TYPE=<Debug/Release>; cmake --build <build> --parallel 2; ctest --test-dir <build> --output-on-failure; direct ctr_conflict_test. Clang sanitizer Debug uses -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer; ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1. Initial GCC Release compilation failed due to std::apply ADL collision; renamed to resolve_round in header/test and reran. A streaming shell invocation was unsupported; normal shell calls succeeded.

| Build | CTest passed | Wall time |
| --- | --- | --- |
| GCC Release | 7/7 | 1.01 s |
| GCC Debug | 7/7 | 1.49 s |
| Clang Debug | 7/7 | 1.77 s |
| Clang Release | 7/7 | 1.08 s |
| Clang ASan/UBSan | 7/7 | 5.17 s |

35/35 final CTest executions passed, zero final failures and no sanitizer diagnostics. Direct output identical across five configurations: conflict-v1:1171875 candidates:48128 accepted. Per configuration: 5^4 x 3 = 1,875 state round-trips; 5^4 order vectors per state = 1,171,875 candidate checks, 48,128 accepted transitions with independent arithmetic/outcome oracle, unchanged input and replay. Explicit malformed/negative and terminal scenarios. New fixture deterministic, no RNG; prior core seeds unchanged from E0002. Counts repeat across builds, not independent statistical samples. No actual game/deck/agent hashes, native matches, uncertainty intervals or performance benchmark. No official source admission, paid compute or historical input. Subtask D synthetic validation only; full CTR-1 acceptance not satisfied.

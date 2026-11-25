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

## CTR-E0007 — CTR-1 generic subtask E, 2026-11-24

Parent 92ccf3ec5d961cb8cf77424964117b544af694cb; code and evidence in same publication commit. Reviewed twelve continuity/source documents and permanent project instructions. Verified thirteen local baseline Git blobs against E0005/E0006. No workflow runs returned for parent, no CI dispatched. Fresh local builds Linux x86_64, GCC 14.2.0 (Debian 14.2.0-19), Clang 17.0.0 (10999b6d034fe318f3d56c83bddb6572593a8bb0), CMake 3.31.6. Exact changed/new source identities from final local run:

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | b9ca0088b42dc3909c5882165f21c9d09725b47b | d5ff30a42e39d9a55c4ec471acb192a010cd7dde95d110eb0b86ee09c628bc0a |
| include/ctr/effects.hpp | 8dd8fd9c83ddaae94d656b52055c8354a805076b | c937b86cdf768bf1942ff8bcc21d7baf2419fd8eac66f5e7d3ff667659565f4f |
| include/ctr/integrated.hpp | 5cdd6f3f08543e2a442d1e2a79c19cb5eceaf1a6 | c9b9070cf24f2fd46d0beee39aaf790d507aebc36d487b632dae04f6187fe9da |
| include/ctr/modifiers.hpp | 1305a50fe65df0eb4e11a967e27930ee047637ae | f6299602fd2d58f3a701fc0409d242846468f39f476f90964587c5dd9815eea8 |
| tests/modifier_test.cpp | 780aabd13d7780ab1f90b20b4db8651709efd726 | 508db4eabe63705f4eaf17e9bc88c76ddedc7b469d43605e3b17f5a01da5c62d |

Remaining ten source files unchanged from E0005/E0006 (exclude CMakeLists.txt, effects.hpp and integrated.hpp from previous thirteen). Require fifteen source hash matches before main advances.

Commands: cmake -S . -B <build> -DCMAKE_CXX_COMPILER=<g++/clang++> -DCMAKE_BUILD_TYPE=<Debug/Release>; cmake --build <build> --parallel 2; ctest --test-dir <build> --output-on-failure; direct ctr_modifier_test. Clang sanitizer Debug uses -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer; ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1. First Release build passed. Unsupported streaming invocation for remaining builds retried via regular execution. No code/test failure or source correction needed.

| Build | CTest passed | Wall time |
| --- | --- | --- |
| GCC Release | 8/8 | 0.98 s |
| GCC Debug | 8/8 | 1.32 s |
| Clang Debug | 8/8 | 1.52 s |
| Clang Release | 8/8 | 1.13 s |
| Clang ASan/UBSan | 8/8 | 5.12 s |

40/40 CTest executions passed; no sanitizer diagnostics. All five direct outputs identical: modifiers-v1:7680 ordered cases. Each new test checks 4! registration permutations x 16 masks x 20 base values against independent ordered arithmetic, multi-mask and boundary examples, 11 invalid modifier input examples, separate inactive/active/inactive payment with distinct final balances, resource/illegal-action versus configuration failure checks including malformed observation propagation. Existing integration/replay/conflict regressions passed unchanged. No new RNG; prior seeds as E0002. Repeated configurations not independent stochastic samples. No native Riftbound games, card/agent/deck hashes, competitive estimates, statistical intervals or performance benchmark. No official source admission, historical inputs or paid jobs. Subtask E validated only; full CTR-1 gate OPEN.

## CTR-E0008 — CTR-1 gap audit and boundary hardening, 2026-11-24

Parent 3bb72e528d4240f9163fb3fa62bdfd2f8c683fb3; code and evidence in same publication commit. Twelve continuity/source documents and permanent project instructions reviewed. Fifteen local baseline blobs matched E0005..E0007. Parent workflow query returned no runs; no CI dispatched. Fresh Linux x86_64 local builds, GCC 14.2.0, Clang 17.0.0 (10999b6d034fe318f3d56c83bddb6572593a8bb0), CMake 3.31.6, Python 3.13.5, Git 2.47.3. Changed/new source identities:

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | 223b37fcd10e0cc92b59db9fa1f15674e2686171 | 17eb4b5e7906476fa996a20a56f08c0f3f0a2c9eff47dc265fdb32da0800e142 |
| include/ctr/kernel.hpp | df7ff6b7047ce50a077f93ab39f5265bc740e59f | b3178440678b5954137fbaf7b61c7106598a12378b22c1e7fba62872c96a3f35 |
| include/ctr/integrated.hpp | e1400572a494a760b2dac09d36cae3c64af4ea4a | 8440521249f8b2079dfc38b8fb84a0c7001544b3c49cadc7607d3a0fd478ca8d |
| include/ctr/replay_contract.hpp | 6f0f0440cfa9b07385715a95f71927b07f982f29 | d346096a905affbdc18357af844e21f35a77d5d9ab1f246d311f2ef13dc968e2 |
| tests/boundary_test.cpp | df79387fcf0d1f81e89fcbb6954a772e329e8970 | 02e4e10f8622a7e68d6742419717dc71b98ce75078481e31faa7b8f218c358a8 |

Remaining twelve source files retain E0005..E0007 identities. Require seventeen exact source blob matches before advancing main. Commands: cmake -S . -B <build> -DCMAKE_CXX_COMPILER=<g++/clang++> -DCMAKE_BUILD_TYPE=<Debug/Release>; cmake --build <build> --parallel 2; ctest --test-dir <build> --output-on-failure; direct ctr_boundary_test. Clang sanitizer Debug flags -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer; ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1.

| Build | CTest passed | Wall time |
| --- | --- | --- |
| GCC Release | 9/9 | 0.97 s |
| GCC Debug | 9/9 | 1.44 s |
| Clang Release | 9/9 | 1.00 s |
| Clang Debug | 9/9 | 1.65 s |
| Clang ASan/UBSan | 9/9 | 5.16 s |

45/45 CTest executions passed, no compilation/test failure or sanitizer diagnostics. All five direct outputs: boundary-v1:64 projections:752 mutations. New test: 16 masks x 2 viewers x 2 priority holders, 11 mandatory mutations each plus 48 opponent-public-to-private mutations, 64 invalid resource and 64 wrong-actor payment cases, replay identity byte mutations and final-state/missing-action/oversize/malformed rejection. Existing regressions including replay passed. No new RNG; prior seeds as E0002. Repeated build counts not independent samples. No benchmark, native games, card/agent/deck hashes, statistical intervals, official materials, historical inputs or paid compute. Gap audit CTR1_GATE_AUDIT.md explicitly leaves official gate open. Structural validation and tag comparison are not authentication.

## CTR-E0009 — canonical run manifest, 2026-11-24

Parent aba84cb17014c444e8b4200e6a213cf663757c34; code and evidence in same publication commit. Repository and thirteen continuity/audit documents reviewed; seventeen prior local source identities verified against recorded E0005..E0008. No parent workflow runs returned; no CI dispatched. Linux x86_64, GCC 14.2.0 (Debian 14.2.0-19), Clang 17.0.0 (10999b6d034fe318f3d56c83bddb6572593a8bb0), CMake 3.31.6, Python 3.13.5. Changed/new exact source identities:

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | 5d196fb43a590e36dcf206acb539f38c06846c47 | c2c1511bd4005bcd575ee9f9d54f11225548d5708c182b99d37fe090a65df1e5 |
| orchestration/run_manifest.py | 6ce7117b1247a0fd752ba0f010085cc6d7136929 | f41be3671364c73a55a358b773d5b374551190482b87d527fcf0ea73d5069c66 |
| tests/manifest_test.py | d62728b18bf816fa26f93b96169ed581dbebf32c | 8b1a4ac13528295f6ee32d7bed5b88ab2c56f29a57c384aebb518cdefe20cc9f |

Remaining sixteen source files unchanged from E0005..E0008. Nineteen exact source blob matches required before updating main. Direct python3 tests/manifest_test.py: 4 unittest methods passed (0.062 s). Fresh builds: cmake -S . -B <build> -DCMAKE_CXX_COMPILER=<g++/clang++> -DCMAKE_BUILD_TYPE=<Debug/Release>; cmake --build <build> --parallel 2; ctest --test-dir <build> --output-on-failure. Clang sanitizer Debug flags -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer; ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1. Streaming invocation unsupported; normal combined command timed out after two successful GCC suites. Clang Release resumed and Clang Debug/sanitizer completed in separate calls.

| Build | CTest passed | Wall time |
| --- | --- | --- |
| GCC Release | 10/10 | 1.73 s |
| GCC Debug | 10/10 | 2.07 s |
| Clang Release | 10/10 | 1.77 s |
| Clang Debug | 10/10 | 2.54 s |
| Clang ASan/UBSan | 10/10 | 6.09 s |

50/50 final CTest executions passed, no code/test failures or sanitizer diagnostics. Python manifest suite repeated under the same interpreter (not independent compiler validation of Python). Each checks known SHA-256 vector, structure, 7! = 5040 registration permutations, 168 single-bit artifact mutations, 700 manifest-byte mutations, missing/extra roles, changed sizes, mutable artifact rejection, malformed/noncanonical manifest even when rehashed, invalid trusted digest and regenerated altered artifacts. Fixture manifest length 700; separately computed SHA-256 4ec95a621314e00a35536418c8a842f8aec06a1eb850d4ea03ebc76fbb532d8c. No new RNG, prior seed roots E0002 unchanged. No native game, competitive inference, performance benchmark, official data/agent/deck hashes or statistical intervals. User directs continued development; policy review in ledger, no official source admitted, no new dependency, no paid compute. CTR-1 full gate OPEN.

## CTR-E0010 — verified native replay, 2026-11-24

Parent 8330440e49bc7c8f222f0afc558082200368fcf4; code and evidence in same publication commit. Reviewed continuity/audit documents and permanent project instructions; nineteen baseline local source identities matched prior evidence. No parent workflow runs returned, no CI dispatched. Linux x86_64, GCC 14.2.0 (Debian 14.2.0-19), Clang 17.0.0 (10999b6d034fe318f3d56c83bddb6572593a8bb0), CMake 3.31.6, Python 3.13.5, Git 2.47.3. Exact changed/new source identities:

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| CMakeLists.txt | cb1849eead38f173173d23a546abd141a437c627 | 718ecd21f4293b4cd8501d459b4931e9699643916f96367889b2334ac32dce12 |
| orchestration/verified_replay.py | f2874b2bdf82472b4720135d5fe04cbb37bc3b12 | db0b44a14a95862d137af84fe76767f30e1c949dfbb7fe4de5210ad1a54277e9 |
| src/replay.cpp | 68aaf37d1afac680f5fc05d17ad1275c61fbb0f9 | 4e6782740c9d4a6af85908031a8db0fa67694b0e006ba7333d64c4662c74f739 |
| tests/verified_replay_test.py | bdf77a5941144ae2cc30f4e4d2f32d6fe0e5fc67 | 0c82e1cddfb7b9c8758085816cfde74b928a20d7ec0bf402e535b69146830634 |

Remaining eighteen source files unchanged from E0005..E0009. Require twenty-two exact source blob matches before updating main. Fresh builds: cmake -S . -B <build> -DCMAKE_CXX_COMPILER=<g++/clang++> -DCMAKE_BUILD_TYPE=<Debug/Release>; cmake --build <build> --parallel 2; ctest --test-dir <build> --output-on-failure. Clang sanitizer Debug flags -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer; ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1. Combined build command timed out during Clang Debug compilation after three successful configurations; resumed separately, then sanitizer build and suite completed. No source/test failures.

| Build | CTest passed | Wall time | ctr_replay executable SHA-256 |
| --- | --- | --- | --- |
| GCC Release | 11/11 | 2.57 s | 14f11030aa712e27864f88928f8cbcf7d2840b45379d90443086c17b070385e6 |
| GCC Debug | 11/11 | 3.14 s | e3915fe5c325b65f77159a56f883e0e265ca69c39baa3a86d5d493960989af3f |
| Clang Release | 11/11 | 2.53 s | 298f00eb3205a08944dfb8ec8eb29795a1eee10deb98b138f781a2e6b2a8e21d |
| Clang Debug | 11/11 | 3.31 s | 5b0ad1ba06ec2a00198db853350193c951e8dc9d975fef4f852a3dd1bdc6486a |
| Clang ASan/UBSan | 11/11 | 7.38 s | f5d7f330c73375149d21d6230d2b3c826ea6305e3812aeb0efb3c18696dd6c13 |

55/55 CTest executions passed; no sanitizer diagnostic reported. New verified_replay test runs four unittest methods: three actual valid native replays (empty, one action, two actions) against independently constructed expected states; fourteen preflight rejections with mocked launch asserting no invocation; 65 truncated prefixes of a one-action 65-byte request, three trailing/oversize/count framing errors, four corrupt identity/state/action/final bytes, two native semantic rejections; four injected worker failure scenarios (wrong output, stderr, status 4, timeout), not actual crashes/timeouts. Valid and invalid native requests use actual compiled executable. Existing tests unchanged. No new RNG; prior core seed roots E0002. Counts repeat across builds, not independent statistical samples. No binaries published, native Riftbound games, card/agent/deck hashes, performance benchmark, uncertainty intervals, official game materials, historical input or paid compute. Full CTR-1 gate OPEN.

## CTR-E0011 — official source discovery, 2026-11-25
Parent 8133785c7c6d4cf1380f392a253492d51099b444. Verified repository identity, current main, write permission and reviewed permanent instructions, continuity/audit documentation and recorded E0010 evidence. Parent workflow query returned no entries (PR-triggered first page only); combined status empty. Documentation-only milestone, no new build, test, simulation or local source-hash verification. No prior local source workspace available. New document OFFICIAL_RULE_SOURCE_DISCOVERY.md records primary publisher metadata and URLs, conflicting hub retrieval dates, exact artifact gaps and proposed scope. Latest indexed hub reports CR/TR October 9 and legality November 23; opened cached hub reports July 16. Direct cache-busting hub and patch page opens failed; no current PDF or payload downloaded. Cross-checked Radiance patch/FAQ/errata and ban announcement, experimental start rules and NA-specific policy metadata. Reviewed public Riot developer policies and general copyright guidance from Croatian DZIV/WIPO. No official source admission, case-specific clearance, card corpus, official behavioral tests or new native games. Prior E0010 55/55 is historical evidence, not a rerun. Require candidate commit comparison to confirm documentation-only changes before advancing main. No new dependency or paid job; full CTR-1 OPEN.

## CTR-E0012 — source-profile admission validation, 2026-11-25

Parent 737e63f843093e41aa9acbf6774415a5d190088f. Repository identity/main/push verified, project instructions and continuity/audit records reviewed; no parent PR-triggered first-page workflow runs or combined status entries. Official Rules Hub search metadata and dated publisher announcements reconfirm October 9 revision and October 16 effective date; opened hub remains July. Alternative locator searches/open failed to expose verified current PDF links; direct local urllib request failed DNS. No official PDF acquired/analyzed or source admitted. No AlphaRune or historical project access. New independently authored Python source and tests only; no existing native or build file changes. Local full prior workspace absent, so no full native regression rerun; E0010 remains historical evidence only.

| Path | Git blob | SHA-256 |
| --- | --- | --- |
| orchestration/source_admission.py | aeb0f180b074d89b3b794e38ce7fcd6dfabbbd03 | e5dc9ee4a2318fc0de6f6ea071ea5995de7e09ca96c86750e6030101e4b1397f |
| tests/source_admission_test.py | 2f7198fb264e691b57ab115be580cb51b7ec7364 | 3077d14ab04e795112d16bc7a720c6d7bfb03dc9dd7df411cb653ac5b21477ff |

Command: python tests/source_admission_test.py -v; Python 3.13.5, local ephemeral Linux workspace. 4/4 unittest methods passed in 0.073 s, zero errors/failures. Positive exact profile, reverse review registration order and inclusive end dates. Negative tests for all individual byte offsets in two original fixture artifacts, empty/mutable/oversize data, stale revision and invalid digest, all five scope dimensions, pending/denied review, missing provenance, invalid/expired/future review dates, out-of-effective range, wildcard scope, duplicate/missing/extra sources and records. No official data, seed changes, performance benchmark, simulated game or competitive inference. Require exact new source blob matches and allowed-file diff before publication. No new external dependencies or paid compute. Full CTR-1 gate OPEN.

## CTR-E0013 — source verification checkpoint, 2026-11-25

Parent 7277d42a3cf14f2f4090bf9e8f36409464a78e4f. Repository identity, main, push and continuity reviewed; limited PR workflow query and combined status returned no entries. Existing local admission utility and test Git blobs and SHA-256 matched E0012. Command: python tests/source_admission_test.py -v; 4/4 methods passed, 0.083 s, zero errors/failures. No full native regression or source code changes. Source locator research and retrieval attempted; no verified official artifact bytes or scope admission. Detailed research record supplied separately for private retention. No new external dependencies, official behavior, game results or paid jobs. CTR-1 remains OPEN.

## CTR-E0014 — admission test registration, 2026-11-25

Parent 839efd405bec714b4d87c99d9dc088968d6cdf22. Repository identity, main, push permission, permanent instructions, separate research record and continuity/evidence reviewed. Parent PR-triggered first-page workflow query and combined status empty. Current rule artifact retrieval and file search did not establish current exact bytes or scoped admission. Details retained separately. Local Git clone failed DNS; full native workspace unavailable. Changed CMakeLists.txt only among executable/build files: append guarded source_admission test registration, TIMEOUT 15. Unchanged orchestration/source_admission.py and tests/source_admission_test.py matched both Git blob and SHA-256 identities in E0012 locally. CMake 3.31.6, Git 2.47.3, Python 3.13.5. Standalone harness uses LANGUAGES NONE, include(CTest), same guarded Python interpreter lookup and exact appended registration block. Commands: cmake -S . -B build-on -DBUILD_TESTING=ON; ctest --test-dir build-on -N; ctest --test-dir build-on --output-on-failure -V; cmake -S . -B build-off -DBUILD_TESTING=OFF; ctest --test-dir build-off -N. ON: one registered test, 1/1 passed, four unittest methods passed (0.039 s), CTest total 0.70 s, generated timeout 15. OFF: zero tests. No code/test failure. This is isolated registration validation, NOT full project configure/build or native regression. Require candidate exact CMake prefix/suffix and allowed-file diff verification before publication. No official game source admitted, no native Riftbound games, no external dependencies or paid jobs. CTR-1 OPEN; blocked on current verified artifacts and scoped admission.

## CTR-E0015 — requirements intake, 2026-11-25
Parent fb7b45cc606de60c0f6a8d50ad0ee88d76449f98. Repository identity/main/push verified, continuity and prior evidence reviewed; limited parent workflow query empty. Base reference access restored; local byte digests and structured numbered-entry index verified. Two independent extraction methods agreed on every page/ID occurrence after correcting initial block extraction omissions; uniqueness and output parse/count checks passed. Detailed evidence retained separately outside public version control. Structural verification only, no semantic coverage or source admission claim. No code changes, engine regression, native games, dependencies or paid jobs. CTR-1 OPEN; scope, completeness and behavioral requirements remain unresolved.

## CTR-E0016 — requirements routing, 2026-11-25
Parent 2393da37169603dbdcf1706a1c54d921732fe72b. Repository identity/main/push verified; continuity and prior evidence reviewed; limited parent workflow and combined status queries empty. Private inventory reconciled at provisional work-package level; verified supplied artifact digests, page/identifier matches, unique identities, complete routing, reference linkage and counts. Separate structural audit accepted inventory and rejected eight injected corruptions. Detailed research, candidate manual scenarios and reconciliation limitations retained outside public version control. No individual semantic completeness, admission or executable behavioral evidence. No runtime changes, engine regression, native games, external dependencies or paid jobs. CTR-1 OPEN.

## CTR-E0017 — full native regression recovery, 2026-11-25
Starting main af9fb00d01bb1c42b10563bc99f758a6c74f9611. Tested candidate af247582d26d82ee2875084f9f526bb685ce561e (tree ddae0dde814f8837c9298ff8f4003f66170ddaba), containing only added .github/workflows/native-regression.yml relative to starting main. Compared recursive trees: all 24 CMake/include/src/orchestration/tests blobs identical; runner git ls-tree output matches every identity. Exact HEAD verified by workflow. Local git ls-remote failed DNS. CI on ctr-qa-e0017: GitHub Actions run 45525217361, job 138906753229, run attempt 1, completed success. https://github.com/Dekanje/CTR-Engine/actions/runs/45525217361 . Full job log retrieved and reviewed, not just green status. Initial workflow lookup returned no runs before run appeared; one attempted workflow endpoint unsupported and one commit response shape inspection failed, then corrected; no build/test failures. Ubuntu 24.04.5 LTS x86_64 standard runner image ubuntu-24.04 version 20261116.376.1, runner 2.338.2, GCC 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04.1), Clang 18.1.3 (1ubuntu1), CMake 3.31.6, Python 3.12.3. Commands: fresh cmake -S . -B build-gcc-release -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTING=ON; build --parallel 2; ctest --output-on-failure --no-tests=error; require exact count 12. Clang Debug same with -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer and ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1. GCC 12/12, CTest 0.86 s; Clang 12/12, CTest 6.90 s. Both explicitly ran source_admission. No sanitizer diagnostic observed, no new seeds, no new behavioral tests or games. Counts repeated across toolchains, not independent statistical trials. Executable digests not emitted; image version recorded but not pinned. Standard public hosted runner free per GitHub runner documentation; no paid jobs, cache/artifact uploads, visibility/billing changes or new code dependency. No private research payload in CI. Full E0014 integration gap closed for tested configurations; official scope and rule evidence unchanged. CTR-1 OPEN.

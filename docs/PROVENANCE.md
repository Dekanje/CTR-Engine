# Dependency and source provenance manifest

2026-11-24. CMakeLists.txt, src/probe.cpp and tests/probe_test.py are original generic bootstrap code authored for CTR Engine in this session; no copied source or imported game materials. Documentation derived from project requirements and engineering decisions; no private deck data.

External application/library dependencies integrated: none. Build tools observed: GCC 14.2.0, Clang 17.0.0, CMake 3.31.6, CTest (bundled), Python 3.13.5 standard library, Git 2.47.3. Compiler/runtime/system-library licensing and redistribution obligations require review before distributing binaries; no binary redistribution here. OpenSpiel is a proposed optional Apache-2.0 dependency, not installed or integrated in this project; pin and review upstream license and transitive dependencies before adoption. PyTorch and storage libraries not selected.

AlphaRune and historical RB-Analyser: prohibited as implementation/evidence sources; no access or dependencies in this bootstrap. No official card text, data, imagery, rules extracts, game recordings or rankings used. Riot-related permissions unresolved. No project license granted or selected.

CTR-0.2: include/ctr/core.hpp and tests/core_test.cpp independently authored generic code and synthetic counter fixture; CMakeLists.txt extended. Standard C++ random, span, array and exception facilities only; no new external dependencies or game materials. Source identities and validation in CTR-E0002. No AlphaRune or legacy repository access.

CTR-1 subtask A: include/ctr/kernel.hpp and tests/kernel_test.cpp original synthetic contract and tests; CMakeLists.txt extended. No new external dependencies. docs/RULE_SOURCE_LEDGER.md schema 1 and docs/RULE_TRACEABILITY.md describe manual source admission and original fixture rules. No official game source or third-party implementation admitted; no AlphaRune or historical repository access. Rights unresolved.

CTR-1 subtask B: original include/ctr/effects.hpp and tests/effect_test.cpp; extended CMakeLists.txt and synthetic specification/traceability. Standard C++ containers and algorithms only, no external packages or official game materials. No AlphaRune or historical repository inputs. Evidence CTR-E0004.

CTR-1 subtask C: include/ctr/integrated.hpp and tests/integrated_test.cpp are original CTR synthetic integration code recovered from prior local work; CMakeLists.txt extended. Reuses only independently implemented CTR core/kernel/effects headers. No new external dependencies, official game materials, historical project or AlphaRune inputs. Evidence CTR-E0005; authorization remains unresolved.

CTR-1 subtask D: original include/ctr/conflict.hpp and tests/conflict_test.cpp; CMakeLists.txt extended. Uses CTR core and standard C++ only, no external dependencies or official materials. No AlphaRune or historical repository access. Evidence CTR-E0006, source ledger CTR-SYN-CONFLICT.

CTR-1 subtask E: original include/ctr/modifiers.hpp and tests/modifier_test.cpp; effects.hpp, integrated.hpp and CMakeLists.txt extended. Uses existing original CTR code and standard C++ only. No new external dependencies, official game materials, AlphaRune or historical repository inputs. Evidence CTR-E0007; authorization unresolved.

CTR-E0008: original include/ctr/replay_contract.hpp and tests/boundary_test.cpp; extended kernel.hpp, integrated.hpp and CMakeLists.txt. Uses only original CTR and C++ standard library. Gap audit derived from repository requirements/evidence, not official game materials. No new dependencies, AlphaRune or historical input; rights unresolved.

CTR-E0009: original orchestration/run_manifest.py and tests/manifest_test.py, CMakeLists.txt extended. Python standard-library hashlib, hmac, json and test utilities only; no external dependencies or game materials. Public Riot policy URLs reviewed for governance only (ledger). No historical or AlphaRune input. No third-party clearance asserted.

CTR-E0010: original src/replay.cpp, orchestration/verified_replay.py and tests/verified_replay_test.py; extended CMakeLists.txt. Reuses original CTR replay contract and Python/C++ standard libraries only. No external package, binary distribution, official game materials or historical/AlphaRune input. Local executable hashes recorded in E0010; dynamic dependencies/environment not yet pinned.

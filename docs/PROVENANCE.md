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

CTR-E0011: original documentation-only source discovery from public publisher metadata and general Croatian DZIV/WIPO legal guidance; locators and limitations in OFFICIAL_RULE_SOURCE_DISCOVERY.md. No official rulebook payload, card data, external code, AlphaRune or historical project imports. No new dependency, authorization determination or executable change.

CTR-E0012: original orchestration/source_admission.py and tests/source_admission_test.py, Python standard library only. Test artifacts are original short strings, no game content. Public publisher metadata rechecked; no current PDF payload imported, third-party transcripts used as rules, AlphaRune or historical project inputs. No external dependency or permission determination.

CTR-E0014: original CMake registration block for existing CTR source-admission tests. No new dependencies, external implementation, official game materials or runtime code. Private research record retained separately; no authorization inferred.

CTR-E0017: original CI workflow using standard hosted Ubuntu toolchain and Git/CMake/CTest/Python already present on image; no third-party workflow action, engine dependency or game materials added. Exact toolchain and source evidence in E0017. No AlphaRune or historical input.

CTR-E0018: original include/ctr/object_store.hpp and tests/object_store_test.cpp; existing CTR typed ID primitive and standard C++20 containers/algorithms. CMake registration and CI configuration extended. Generic storage contracts and original test cases only; no official game content or other engine code imported. No external dependency or scope clearance.

CTR-E0019: original include/ctr/ordered_sampling.hpp and tests/ordered_sampling_test.cpp; standard C++20 and original CTR store/random primitives. CMake registration and CI configuration extended. Private reference review separate from generic implementation; no official content payloads or external engine code imported. Scope review unresolved. No additional dependency.

CTR-E0020: independently authored private C++20 research code/test harness, standard library only, abstract IDs. User-supplied reference review and source identity retained privately. No third-party code, card assets, prior engine or AlphaRune imported; no production admission or license clearance asserted. Public update limited to continuity evidence.

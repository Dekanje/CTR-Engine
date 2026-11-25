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

CTR-E0021: private original setup modifications and turn research/test source, standard C++20 and exact original CTR RNG/store headers verified by Git blob identity. Detailed rule-derived mapping and source/binary identities in private package. No external engine, card text/art/catalog, historical code or new dependency. Public update limited to continuity evidence; no legal clearance or production admission asserted.

CTR-E0022: original private turn.hpp extension and chain_test.cpp using existing CTR core/store and C++20 standard library only; source-specific traceability, exact hashes and logs retained in private artifact. No actual card data, protected artwork/text, external engine, dependency, historical code or AlphaRune import. No source admission, clearance or public runtime change asserted.

CTR-E0023: original private turn.hpp extension and pending_test.cpp, shared existing CTR headers and standard C++20 only. Detailed source review, exact hashes and evidence retained in private package; no official card payload, third-party engine, AlphaRune, historical code or new dependency. No production admission or third-party permission asserted.

CTR-E0024: original private turn.hpp extension and trigger_test.cpp using existing CTR headers and C++20 standard library. Exact source/binary hashes, private reference mapping and test logs retained in private cumulative archive. No real card payload, protected artwork/text, external engine, historical code, AlphaRune or new dependencies imported. No source clearance or production admission asserted.

CTR-E0025: independently authored private turn.hpp extension and counter_test.cpp with original shared CTR headers and C++20 standard library. Exact source/binary hashes and selected rule traceability recorded in private cumulative package; no actual card data, protected expression/assets, external engine, historical code, AlphaRune or new dependency imported. No production admission or third-party permission asserted.

CTR-E0026: original private turn.hpp extension and cost_test.cpp, own prior CTR fixture and shared native headers, C++20 standard library. Selected rule mapping, actual source and 14 binary hashes and validation logs retained in private archive; no actual card content, protected expression/assets, external engine, historical code, AlphaRune or new dependency imported. No production admission or third-party permission asserted.

CTR-E0027: original private turn.hpp extension and unit_test.cpp using verified shared CTR native headers and C++20 standard library. Private selected rule mapping, exact source and 16 executable hashes and original validation logs retained separately. No actual card content, external engine, historical code, AlphaRune, new dependency, production admission or third-party permission asserted.

CTR-E0028: original private turn.hpp extension and movement_test.cpp, existing independently authored CTR headers and C++20 standard library. Selected source mapping, exact source and 18 executable hashes and raw validation logs retained privately. No actual card content, protected expression/assets, external engine, historical code, AlphaRune, new dependency, production admission or third-party permission asserted.

CTR-E0029: original isolated private combat_assignment.hpp, focused test and CMake harness; C++20 standard library only. Selected reference identity matched previous private record, detailed mapping and source/executable identities retained privately. No actual card data, source payload, external engine, historical code, AlphaRune or new dependencies; no third-party permission or production admission asserted. Public update limited to evidence and continuity.

CTR-E0030: original private combat_transaction.hpp and focused test extend exact verified E0029 allocation source, C++20 standard library only. Pinned reference identity unchanged; no new source semantics beyond restricted damage assignment/staging, no actual card payload, external engine, historical code, AlphaRune, new dependencies or scope clearance. Exact source/binary hashes and logs private; public update limited to continuity/evidence.

CTR-E0031: original private turn.hpp integration and combat_integration_test.cpp, exact recovered E0028 source and exact E0030 helper/test sources, C++20 standard library only. Selected supplied reference identity unchanged; detailed traceability, exact source and executable identities, baseline and final test logs retained privately. No protected source payload, actual card content, external engine, historical RB-Analyser, AlphaRune, new dependencies, scoped clearance or production admission. Public update limited to continuity and evidence.

CTR-E0032: original private turn.hpp extension and combat_keywords_test.cpp using exact E0031 helpers and original CTR fixture code, C++20 standard library only. Selected supplied reference identity unchanged; private traceability, exact source and executable hashes and raw logs retained. No actual card payload, external engine, AlphaRune, historical RB-Analyser, new dependencies, scoped clearance or production admission. Public update limited to continuity/evidence.

CTR-E0033: original private designation_events.hpp and designation_events_test.cpp, extended turn.hpp/CMake using exact E0032 candidate and original fixture helpers, C++20 standard library only. Selected reference identity unchanged; private traceability, exact source/executable identities and logs retained. No actual card payload, new dependency, historical code, AlphaRune, third-party clearance or production admission. Public update limited to evidence and continuity.

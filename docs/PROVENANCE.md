# Dependency and source provenance manifest

2026-11-24. CMakeLists.txt, src/probe.cpp and tests/probe_test.py are original generic bootstrap code authored for CTR Engine in this session; no copied source or imported game materials. Documentation derived from project requirements and engineering decisions; no private deck data.

External application/library dependencies integrated: none. Build tools observed: GCC 14.2.0, Clang 17.0.0, CMake 3.31.6, CTest (bundled), Python 3.13.5 standard library, Git 2.47.3. Compiler/runtime/system-library licensing and redistribution obligations require review before distributing binaries; no binary redistribution here. OpenSpiel is a proposed optional Apache-2.0 dependency, not installed or integrated in this project; pin and review upstream license and transitive dependencies before adoption. PyTorch and storage libraries not selected.

AlphaRune and historical RB-Analyser: prohibited as implementation/evidence sources; no access or dependencies in this bootstrap. No official card text, data, imagery, rules extracts, game recordings or rankings used. Riot-related permissions unresolved. No project license granted or selected.

CTR-0.2: include/ctr/core.hpp and tests/core_test.cpp independently authored generic code and synthetic counter fixture; CMakeLists.txt extended. Standard C++ random, span, array and exception facilities only; no new external dependencies or game materials. Source identities and validation in CTR-E0002. No AlphaRune or legacy repository access.

CTR-1 subtask A: include/ctr/kernel.hpp and tests/kernel_test.cpp original synthetic contract and tests; CMakeLists.txt extended. No new external dependencies. docs/RULE_SOURCE_LEDGER.md schema 1 and docs/RULE_TRACEABILITY.md describe manual source admission and original fixture rules. No official game source or third-party implementation admitted; no AlphaRune or historical repository access. Rights unresolved.

CTR-1 subtask B: original include/ctr/effects.hpp and tests/effect_test.cpp; extended CMakeLists.txt and synthetic specification/traceability. Standard C++ containers and algorithms only, no external packages or official game materials. No AlphaRune or historical repository inputs. Evidence CTR-E0004.

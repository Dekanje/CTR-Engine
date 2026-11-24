# CTR Engine

Independent native simulation research infrastructure. New implementation, not a fork, rename or continuation of another engine. No AlphaRune dependencies or imported implementation.

Status: CTR-0.1 and CTR-0.2 baseline gates satisfied; CTR-1 generic subtasks A–E validated (synthetic state/action/priority/observation, bounded effect resolution, integrated resource/action replay, standalone simultaneous conflict/scoring, and bounded modifiers/error classification). Full CTR-1 gate open; not a Riftbound rules engine. See docs/RULE_SOURCE_LEDGER.md and docs/RULE_TRACEABILITY.md. See MASTER_PLAN.md, DEVELOPMENT_STATUS.md and docs/HANDOVER.md.

Build and test (CMake >= 3.20, C++20 compiler, Python >= 3.10):
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build build --parallel 2
    ctest --test-dir build --output-on-failure

Public content is limited to generic infrastructure and documentation. No card data, private deck research, historical rankings or simulation evidence from other projects. No license grant is specified; distribution/reuse terms require an explicit owner decision.

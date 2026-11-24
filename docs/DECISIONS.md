# Decision log

2026-11-24 D001: Use verified independent repository ID 1470873291. No legacy project or AlphaRune inputs.
D002: Implement generic feasibility probe using C++20/CMake/CTest/Python standard library; no external packages. Process protocol chosen solely for smoke validation, not production IPC.
D003: Use local ephemeral builds with GCC/Clang, Debug/Release, warnings as errors; no CI dispatch or paid compute. CI policy deferred pending quota verification.
D004: Master plan baseline derives from approved architecture; subsequent gate numbering is provisional until the separate canonical plan is available.
D005: Keep public repository limited to generic infrastructure; rights for card materials and distribution license unresolved. No visibility changes.

D006: CTR-0.2 uses standard C++ mt19937_64/seed_seq with explicit stream domains and fixed word ordering; bounded sampling uses unsigned rejection threshold rather than std::uniform_int_distribution. No external dependencies.
D007: Use synthetic counter fixture with request/outcome separation and canonical three-byte encodings; do not promote this schema to game rules. Replay is deterministic event application, not seed-dependent re-simulation.
D008: Recover interrupted local source and rerun complete five-build matrix before publication. Verify all five Git blob identities before moving main. Gate acceptance limited to baseline CTR-0.2, not official game semantics.

D009: Divide open CTR-1 into independently validated generic subtasks while official rules authorization is unresolved; subtask A is not full-gate acceptance. Fixed-size synthetic slots and pass/reveal actions are deliberately non-game-specific.
D010: Separate authoritative state and trusted observation; generate fixture actions from the observation and validate against authority on application. Counts and slot identities are public/inferable in this model. No claim of general secrecy or sandboxing.
D011: Establish versioned manual source admission ledger and synthetic traceability. No official source admitted; machine enforcement and authorization verification remain open.

D012: Use explicit, versioned immutable synthetic event tables rather than arbitrary callbacks for first resolution contract; ascending ID precedence and FIFO scheduling are synthetic conventions, not official rules.
D013: Use bounded transactional value-returning resolution, exact repeated-event cycle detection for replacements, and finite event/queue budgets for trigger cascades. Reject on limit exhaustion, never truncate or commit partial results. Keep trace authoritative and in-memory until serialization/observation contract is defined.

D014: Integrate prior synthetic state and effect fixtures with a fixed, public-state-derived payment program and pure value transitions. Modifier recomputation occurs before replacement, and full trigger cascade determines affordability. Both legal reveal paths deliberately normalize to final debit 2; no general continuous-effect claim.
D015: Use explicit little-endian synthetic state encoding and bounded action replay; full-state bytes and authoritative trace are not agent-visible. Version 1 identifies immutable fixture behavior, not a production rules/content manifest.
D016: Recover interrupted local subtask C files, rerun all five configurations and compare all eleven source blob identities before publishing. Keep CTR-1 open. Next generic subdivision D is a local engineering choice, not an approved phase change.

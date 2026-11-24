# Synthetic kernel specification and traceability — v1

Independent fixture CTR-SYN-KERNEL v1. This is not Riftbound. It exercises typed IDs, validated pure transitions, priority and a player-specific observation boundary. Its constraints are test-only.

| Rule ID | Specification | Test evidence (tests/kernel_test.cpp, CTest synthetic_kernel) |
| --- | --- | --- |
| SYN-K01 | Two players, four fixed object slots, two per owner. Zone is private or public; labels are 32-bit. Turns 0..2 permit actions; terminal turn 3 requires priority 0 and passed false. | 208 valid structural combinations over 16 masks; 48 invalid terminal combinations; invalid zone/viewer examples |
| SYN-K02 | Only current priority holder can act, except terminal where no actions allowed. Pass target must be zero. Reveal targets an owned private slot. Unknown kind/actor/target rejected. | 6,240 candidates across both players, three kinds and five targets; exact legal generation agreement; invalid actor example |
| SYN-K03 | First pass transfers priority and sets passed. Second consecutive pass increments turn, resets passed, assigns priority by turn parity (zero at terminal). Reveal exposes object, clears passed and transfers priority. | Independent expected transition and invariant checks for every allowed candidate |
| SYN-K04 | Observation includes viewer, turn, priority, passed, private counts, own objects and public objects. Opponent private labels omitted. Offered actions derived from trusted observation, then authoritative state validates execution. | 416 player/state projections with exact visible-object/count checks and altered opponent private labels; actions unchanged under perturbation |
| SYN-K05 | Invalid actions reject before modifying input; valid actions return a new state. | Negative transition tests and selected unchanged-input field checks |

Not a comprehensive secrecy proof: slot IDs/ownership/counts are structurally public or inferable; no secret ordering, visibility history, randomized entities, timing leakage, untrusted observation deserialization, stale action protection or agent process sandbox. Observation is trusted output, not a security boundary against arbitrary in-process code. No official rule mapped; no combat, effects, resource, scoring or game-specific turn model. No production replay integration for this fixture yet.

## Independent synthetic effect contract CTR-SYN-EFFECTS v1

| Rule ID | Specification | Test evidence (tests/effect_test.cpp, CTest synthetic_effects) |
| --- | --- | --- |
| SYN-E01 | Two balances in 0..100; typed credit/debit with target 0/1 and amount 1..100. Reject out-of-range result; other balance unchanged. | 40,400 balance/amount/target/kind combinations, independent arithmetic oracle and unchanged input check |
| SYN-E02 | Version 1 only; validate whole program/input. IDs nonzero and unique within each table. Lowest matching replacement ID wins, restart matching after rewrite. Cancellation yields no mutation or triggers. | Exact six-record trace oracle across 4! x 5! = 2,880 registration permutations; invalid version, state, rules and event examples |
| SYN-E03 | Match triggers only against applied event; ascending trigger IDs enqueue FIFO after existing roots and pending work. | Same trace oracle tests nested trigger, original/cancelled events not triggering, and root precedence |
| SYN-E04 | Reject repeated replacement event; enforce rewrite, pending and total event budgets. Limits must be positive and capped at 64 rewrites, 256 pending/events; max 64 rules per table. | Self/two-event replacement cycles, rewrite limit, trigger cycle, fan-out queue limit, exact-limit success, invalid limit/input count |
| SYN-E05 | Transaction returns state and complete trace only on success; no external mutation. | Input state unchanged on arithmetic cases and late triggered failure; empty transaction preserves state |

No official semantics, independent of subtask A; no production replay/observation integration. Tests do not exhaust all possible programs or resource limit combinations.

## Independent synthetic integration contract CTR-SYN-INTEGRATED v1

| Rule ID | Specification | Test evidence (tests/integrated_test.cpp, CTest synthetic_integration) |
| --- | --- | --- |
| SYN-I01 | Authoritative state combines valid board and balances; observations include both public balances and viewer-specific board projection. Opponent private labels cannot influence offered actions. | 768 structural/resource combinations; 1,536 viewer projections with hidden-label perturbations and action equality |
| SYN-I02 | Reveal uses pre-action cost 3 minus own public slot count. Replacement changes debit 3 to 2; applied debit 2 triggers credit 1 to other player. Both legal reveal paths cost 2. Pass is free. | 3,072 reveal candidates; exact independent allowed predicate and expected resulting state; replacement-count oracle; pass resource/trace checks |
| SYN-I03 | Authority validates action, resolves entire payment including triggers, applies board transition only after success, and validates result. Reject insufficient balance or other player overflow atomically. | Candidate rejection and unchanged input checks; resource boundaries 0,1,2,3,99,100 for actor and 0,1,99,100 for other |
| SYN-I04 | Canonical 26-byte state and four-byte action encodings, version 1, little-endian label. Invalid version/size, actor/target/kind, zone, passed flag and balances rejected. | 768 state round-trips; explicit byte-order and malformed examples |
| SYN-I05 | Replay reconstructs final state by validated action application, max 32 actions; terminal or repeated illegal action rejected. | Single-action replay for allowed candidates, nine-action terminal fixture with expected balances 6/12, every prefix round-trip, terminal/repeated/oversize log rejection |

This is original synthetic semantics. Cost normalization means final legal reveal price is constant despite different pre-replacement paths. No general continuous-effect system, explicit chance in this fixture, official combat/scoring or authenticated replay. Full-state bytes are authority-only; trusted observations do not constitute a security sandbox. Tests are selected finite combinations, not exhaustive state space.

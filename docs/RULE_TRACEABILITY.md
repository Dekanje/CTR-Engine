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

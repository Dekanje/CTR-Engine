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

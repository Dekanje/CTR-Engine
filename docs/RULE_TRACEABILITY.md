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

## Independent synthetic conflict contract CTR-SYN-CONFLICT v1

| Rule ID | Specification | Test evidence (tests/conflict_test.cpp, CTest synthetic_conflict) |
| --- | --- | --- |
| SYN-D01 | Four fixed units, two per side; alive HP/power 1..3, removed (0,0). Score equals opposing removed-slot count; rounds 0..4. | 1,875 structural state round-trips (five unit variants x four slots as Cartesian power, three round values); invalid score/unit/version examples |
| SYN-D02 | One order per slot, opposing live target 0..3 or idle 4; no actions at terminal. Validate all orders before mutation. | 1,171,875 order candidates against independent predicate, including friendly, dead and terminal targets; explicit out-of-range and invalid transition rejection |
| SYN-D03 | All damage uses pre-round power; aggregate per target, remove once at zero HP, increment score per defeated unit. | 48,128 legal transitions against independent per-target subtraction and score recount oracle; input equality, invariants, simultaneous mutual elimination and focus-fire examples |
| SYN-D04 | End after round four or either side eliminated; compare scores, ties draw. | Expected outcome checked for each accepted transition, explicit first/second victory, mutual elimination and four-idle-round draw |
| SYN-D05 | Version-1 state bytes (12) and order bytes (5); replay at most four batches, rejecting malformed and post-terminal logs. | Single-batch replay for each accepted transition, multi-batch terminal fixture, malformed order/version/length and oversized/post-terminal rejection |

Finite domain is HP/power 1..2 plus removed for exhaustive candidate enumeration, round values 0,3,4; HP/power 3 covered by explicit cases. Not a full-state exhaustive proof. Standalone fixture with no official game semantics, hidden choices, effects, or integration with prior kernel.

## Generic modifier and error contract CTR-SYN-MODIFIERS v1

| Rule ID | Specification | Test evidence (tests/modifier_test.cpp, CTest continuous_modifiers) |
| --- | --- | --- |
| SYN-M01 | Base and every intermediate value 0..100; set 0..100, add -100..100, multiply 0..4; max 64 rules, layer 0..7, four-bit masks, unique nonzero IDs. Validate inactive rules too. | Boundary, malformed ID/mask/layer/operand/operation/count, duplicate ID and range rejection examples |
| SYN-M02 | Active iff all required mask bits present; evaluate from base each call in ascending (layer,id) order independent of registration order. | 7,680 cases: 24 registration permutations x 16 masks x 20 bases, independent arithmetic oracle; multi-bit activation and removal |
| SYN-M03 | Derived value may feed effect resolver. In separate fixture base debit 5, inactive replacement to 4; active discount gives debit 3 and triggers credit to opponent. | Inactive/active/inactive sequence gives final balances (6,10)/(7,11)/(6,10) from (10,10); trace length checked |
| SYN-M04 | Resource bounds failures are ResourceViolation; invalid kernel action IllegalAction; other configuration/input errors propagate; invariant faults are logic_error. Only ResourceViolation is filtered by integrated action enumeration. | Underflow and triggered overflow, bad program version, replacement loop, event budget, invalid state, illegal actor, and malformed duplicate public projection (must propagate) |
| SYN-M05 | Existing v1 payment semantics retained: public-slot mask drives equivalent cost calculation, fixed replacement/trigger program unchanged. | Full synthetic_integration regression, 3,072 reveal candidates, 1,536 projection perturbations and existing replay fixtures across all builds |

Bounded fixture/general utility, not official semantics. Separate variable-payment case is not the v1 integrated game; no dynamic dependency graph or complete observation validation. ResourceViolation does not yet distinguish expected unaffordability from a resource failure caused by arbitrary faulty rules.

## CTR-SYN-BOUNDARY v1 (hardening of existing contracts)

| Rule ID | Specification | Test evidence (tests/boundary_test.cpp, CTest validated_boundaries) |
| --- | --- | --- |
| SYN-V01 | Canonical projection validates viewer, priority, turn, terminal flags, unique ascending slot IDs, ownership, visibility and private counts; own slots must be present. Reject malformed projection even when not acting. | 64 genuine projections and 752 malformed projection mutations, including opponent private objects; existing kernel/integration regression |
| SYN-V02 | Payment requires valid resources and candidate membership, including pass. | 64 invalid balance and 64 wrong-actor payment cases; existing modifier and resource regressions |
| SYN-V03 | Authority-only replay envelope requires exact fixture identity and equal reconstructed final state, retaining existing bounded replay. | Valid one-action envelope, eight identity mutations, wrong final state, missing action, oversized log and malformed final encoding |

Structural validity is not truth/authentication/freshness. Identity tag is not a hash. No new official rules or general security proof.

## Generic run identity contract (not a game rule)
MAN-01: exact seven immutable byte roles, canonical v1 JSON containing lengths and SHA-256 hashes; 5040 input order permutations and known vector. MAN-02: verification requires trusted digest and exact canonical equality; 168 artifact bit mutations, 700 manifest mutations and invalid/noncanonical input tests. Evidence E0009, tests/manifest_test.py. No native execution, authorization or authentication guarantee.

## Verified native replay infrastructure (not a game rule)
REP-01: validate manifest, immutable role bytes, fixed compatibility markers, input sizes and trusted executable equality before launch; 14 preflight rejections assert no worker invocation. REP-02: EOF-framed request 61+4n bytes, n<=32, max 189; 65 truncated prefixes, three framing errors and four corrupted-field errors on real worker. REP-03: independently compare expected final bytes after validated native execution; three successful native replays, two semantic rejection examples, four mocked worker failures. Evidence CTR-E0010, tests/verified_replay_test.py. Linux-only, trusted local executable/environment, no official gameplay or security sandbox.

## Source-profile validation (not a game rule)
ADM-01: exact unique pins, trusted review records and immutable artifacts; reject missing/extra/duplicate sources and mismatched revisions/digests. ADM-02: exact five-dimensional scope, admitted status, complete provenance and inclusive effective/review windows; reject stale, pending or out-of-scope records. ADM-03: nonempty bounded immutable bytes and exact SHA-256 comparison; return in declared pin order. Evidence CTR-E0012, tests/source_admission_test.py, four focused unittest methods. No source authenticity, legal determination, completeness or native enforcement claim.

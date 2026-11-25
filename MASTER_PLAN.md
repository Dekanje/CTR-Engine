# CTR Engine master plan — baseline v0.1

2026-11-24. Architecture direction approved in project instructions. CTR-0.1 is the specified initial task. No separate detailed approved milestone document was available at bootstrap; the following later gate IDs and sequencing are an engineering proposal derived from those requirements, not additional user approval. Reconcile if the canonical detailed plan becomes available.

| Gate | Deliverable | Minimum acceptance evidence |
| --- | --- | --- |
| CTR-0.1 | Independent repository, continuity records, build and IPC feasibility | Identity/permissions verified, original generic build tested, exact source hashes and open blockers recorded |
| CTR-0.2 (proposed) | Deterministic generic primitives and replay contract | Stable encoding, explicit chance, bounded random sampling, seed isolation, illegal-input rejection, cross-build replay and property tests |
| CTR-1 (proposed) | Authorized rules specification and native rules kernel | Versioned source/rights ledger; rule-to-test traceability; zones, timing, priority, combat, resources, scoring, triggers, replacements, continuous effects and invariants; negative fixtures |
| CTR-2 (proposed) | Versioned content and legality | Every legal functional identity and legend covered for selected formats; print equivalence, errata, restrictions and deck legality; independent behavioral fixtures; unsupported entries block results |
| CTR-3 (proposed) | Agents and hidden-information evaluation | Observation-only interface, tactical/heuristic baselines, hidden-state sampling, search and optional learned agents; leakage tests and holdout quality/speed benchmarks |
| CTR-4 (proposed) | BO3 and all-legend discovery/optimization | Legal sideboarding from observed information, first-player selection, clocks/draws, directed matchups/mirrors, independently optimized strong opposition; blind/meta separation; paired uncertainty and holdout |
| CTR-5 (proposed) | Tournament research | Configurable Swiss, official tiebreakers, byes/drops, cuts and elimination; native results versus calibrated projections; championship probability with intervals and sensitivity |
| CTR-6 (proposed) | Durable execution, performance and extension | Atomic checkpoints, restart/retry, reproducible run manifests, resource caps, profiling; future-set regression and independent validation |

Stages may overlap only where prerequisites are satisfied. Rights and rules provenance gate all game-specific activity; generic work can proceed separately. No future Worlds format or hypothetical exclusions are assumed official. Do not claim full legality, simulation readiness or competitive strength until relevant gates are evidenced. No global-optimum or victory guarantees. Public repository excludes confidential research data. No paid infrastructure.

## Confirmed headless-only scope
Confirmed user scope (2026-11-25): headless offline computational research only. AI-controlled rules simulation, deck discovery/optimization, matchup and tournament statistics, reproducible logs and decklist/result exports. No GUI, visual simulation, human-controlled game client, online multiplayer, Riot API integration, live tournament assistance or commercial distribution. Preserve the separate scoped admission, content rights and behavioral validation requirements; this scope is not third-party permission.

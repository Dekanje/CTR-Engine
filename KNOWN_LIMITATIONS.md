# Known limitations

- Separate detailed approved master-plan text not available at bootstrap; later stage names and gates are provisional.
- Public repository: do not store confidential competitive research or unauthorized materials. Do not change visibility or spending settings without explicit authorization.
- No verified rights to use/distribute game-specific card data or conduct restricted automated gameplay; no such data or activity in bootstrap.
- No project distribution license selected. Toolchain inventory is not a complete transitive license audit.
- Synthetic probe validates only compilation and subprocess contract; it is not a game engine, agent or benchmark.
- Linux x86-64 tested only; Windows, macOS, MSVC and cross-platform reproducibility not yet validated. CTR-0.2 Clang ASan/UBSan passed; this is not exhaustive memory-safety proof.
- No official rules version, formats, functional identity catalog, card coverage, game-specific replay, agents, deck optimizer, match/tournament logic or simulation samples exist.
- No CI workflow or local PC execution configured; GitHub quota/spend settings not verified. Intensive computation remains unavailable in this session.

- CTR-0.2 fixture is deliberately synthetic; its three-byte state/event schemas are not production formats. Generic random streams use mt19937_64 and seed_seq; domain separation and consumption isolation tested, not statistical independence or cryptographic security.
- Bounded sampling requires uniform full-width input; untrusted/adversarial sources can stall rejection. No RNG persistence, authenticated replay, weighted chance, hidden-information interfaces or production performance benchmark yet.
- CTR-1 game-specific work blocked by authorization/provenance; generic contracts can proceed independently.

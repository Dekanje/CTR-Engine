# Architecture

The independent C++20 core will own rules, legality, explicit chance transitions, state invariants and replay. Keep versioned game definitions/data and effect composition separate from native extensions. Unknown mechanics and ambiguous legality fail closed. Rules version, identity mappings, errata and restriction tables are explicit inputs. Do not treat any AI library as rules authority.

Proposed module boundaries:
- core: typed IDs, canonical state/encoding, seed streams, transition and chance contracts.
- rules: versioned state machine, action generation, timing, effects and legality.
- content: rights-reviewed functional definitions, print mappings and behavioral coverage.
- agents: observation-only policies, heuristic/tactical/search baselines, optional learned policy/value.
- research: independent blind discovery, separate meta evaluation, strong-opponent co-evolution and holdout validation.
- matches/tournaments: BO3 policy, observed-information sideboarding, configurable event rules and distinct statistical projections.
- orchestration: Python workers, versioned manifests, atomic checkpoints, resource limits and reporting.

Native workers and Python communicate via versioned contracts; benchmark before committing to a binding or storage technology. The current executable is only a synthetic process probe, not a production protocol. OpenSpiel is optional and replaceable after license review; PyTorch/storage choices require justification. No external dependency is currently integrated. Future-set extension requires versioned legality, effect semantics and regression coverage.

## CTR-0.2 validated foundation
Header-only C++20 generic tagged IDs, explicitly domain-separated mt19937_64 streams seeded using seed_seq(root low/high, domain, run low/high), and rejection sampling for uniform full-width inputs. Version-1 synthetic fixture: three-byte state [version,value,pending] and event [version,kind,payload]. Explicit request/outcome events; validated pure value transitions; replay consumes encoded events without RNG. Prefixes may end pending. These are demonstrator schemas, not game-specific rules or production serialization. No weighted chance or RNG checkpointing yet. Future kernel must separate full state from agent observations and trace every implemented rule to authorized versioned sources and independent tests.

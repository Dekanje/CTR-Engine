# Development status — 2026-11-24

Repository: Dekanje/CTR-Engine (ID 1470873291), public, main, confirmed initially empty, push permission available. Identity commit: 8a8c60a6bd4ea204739f76a1f44ad25ce758b8fe.

CTR-0.1: bootstrap gate satisfied against baseline v0.1. Implementation commit e5cb2c73e654db5945cf02f906adc297f296659b; all three published source blob IDs matched locally tested IDs in docs/EVIDENCE_INDEX.md. All ten continuity files were fetched at that commit. Evidence is tied to the source blobs, not an inferred CI result. No GitHub Actions configured or executed in this session. No paid infrastructure purchased.

| Area | Status |
| --- | --- |
| C++20/Python feasibility probe | Locally validated, 8/8 CTest executions across four configurations |
| CTR-0.2 deterministic primitives and synthetic replay | Baseline gate satisfied; 15/15 CTest executions in five configurations, exact source verification (CTR-E0002) |
| CTR-1 generic kernel subtask A | Validated and published: synthetic state/action/priority/observation contracts; manual rights ledger and traceability (CTR-E0003) |
| CTR-1 generic subtask B | Validated: bounded transactional event resolution, replacement and trigger ordering (CTR-E0004) |
| CTR-1 generic subtask C | Validated: synthetic state/action/effect integration, zone-derived modifier and replay (CTR-E0005) |
| CTR-1 generic subtask D | Validated standalone simultaneous conflict, scoring and terminal replay (CTR-E0006) |
| CTR-1 generic subtask E | Validated: bounded continuous modifiers and distinct resource/action rejection (CTR-E0007) |
| CTR-1 boundary hardening and gap audit | Validated synthetic projection structure and replay identity/final-state checks (CTR-E0008); official gaps documented |
| CTR-1 run identity infrastructure | Validated canonical SHA-256 manifest and exact artifact verification (CTR-E0009) |
| CTR-1 verified native replay | Validated manifest-to-native synthetic replay path (CTR-E0010) |
| Rules kernel / format legality | CTR-1 in progress; official semantics not implemented |
| Card and legend behavior | Zero verified |
| Gameplay agents and BO3 | Not implemented |
| Optimization and tournament simulation | Not implemented |
| Native Riftbound games | 0 |
| Rights and dependency approval | Open |

CTR-0.2 implementation commit a3a572e407e9ab7840da891e46ed33dd545f5fea. All five tested source blob IDs verified against GitHub before advancing main. Rerun of recovered local session002 sources: GCC and Clang Debug/Release, Clang ASan/UBSan; 15/15 CTest executions, matching pinned fingerprints. No game simulations or CI jobs.

CTR-1 subtask A implementation ae649d188d792a6a3e14dd61842b59e895d8417b; 20/20 CTest executions across five local build configurations; all seven tested source blobs matched on GitHub. Manual admission ledger and synthetic rule-to-test mapping added. See CTR-E0003. CTR-1 gate remains OPEN; no official rules source admitted.

CTR-1 subtask B implementation 3aac314886d83cdb4b159e84d097a58f10847cd8: 25/25 final CTest executions in five local configurations; all nine tested source blob identities matched candidate commit before main advanced. Full CTR-1 gate remains open. See CTR-E0004.

CTR-1 subtask C implementation ee53d3104c5621772907209c93a3500ff56cf78c: recovered interrupted local implementation, reviewed source, reran 30/30 CTest executions across five configurations and verified all eleven tested source identities on GitHub. See CTR-E0005. Synthetic rules only; full CTR-1 gate remains OPEN.

CTR-1 subtask D: 35/35 final CTest executions, five configurations; 1,171,875 order candidates and 48,128 legal transitions per conflict test. Evidence CTR-E0006, identified by exact source blobs and the commit containing that record. Standalone synthetic fixture, not integrated with subtask C. Full CTR-1 gate remains OPEN.

CTR-1 subtask E: 40/40 CTest executions across five local build configurations. Generic modifier evaluator integrated into existing v1 cost computation; v1 behavior unchanged on regression fixtures. Separate variable-payment fixture demonstrates final-value changes with replacements and triggers. Action enumeration catches only ResourceViolation; configuration and engine failures propagate. See CTR-E0007, exact source identities, and the commit containing the record. Full CTR-1 gate remains OPEN.

CTR-E0008: 45/45 CTest executions across five local configurations; all seventeen tested source identities require matching before publication. Structural observation validation and direct payment action checks, replay envelope identity and expected final state verification. See docs/CTR1_GATE_AUDIT.md. No full CTR-1 acceptance.

CTR-E0009: 50/50 final CTest executions across five local configurations; canonical SHA-256 run manifest for seven artifact roles and trusted digest comparison. No gameplay changes. User directed continued development without a support ticket; this is development authorization, not evidence of third-party permission. Public Riot policy reviewed on 2026-11-24; no official game source admitted. CTR-1 remains open.

CTR-E0010: 55/55 CTest executions across five local configurations. Verified immutable artifact snapshot, exact trusted executable matching, bounded binary replay worker and final-state comparison. Existing synthetic rules unchanged. No official material or rights admission. Full CTR-1 remains OPEN.

CTR-E0011 (2026-11-25): official rule-source discovery and scope review, documentation only. Candidate references for CR/TR, Radiance changes/FAQ/errata, current legality and regional/event/experimental distinctions recorded in docs/OFFICIAL_RULE_SOURCE_DISCOVERY.md. Conflicting cached hub versions prevent exact current artifact pinning. No official source admitted, no rules implemented, no new test execution. Prior E0010 validation remains historical evidence for unchanged source.

CTR-E0012 (2026-11-25): generic source-profile admission checker implemented and directly tested (4/4 Python unittest methods). Exact trusted pins, provenance, scope, effective/review date intervals and SHA-256 byte identity required. No source admitted or game mechanic implemented; no existing native code or build changes. Prior E0010 55/55 remains historical evidence, not rerun. Source search reconfirmed October revision/effective dates but not exact current PDF bytes; local direct network unavailable.

CTR-E0013: source-admission suite rerun 4/4; both local source identities match E0012. Current rule artifacts and scoped admission remain unverified. Detailed research records are to remain outside public version control; required notices and accurate acceptance evidence remain mandatory. No executable changes or official gameplay.

CTR-E0014 (2026-11-25): registered existing source-admission suite in standard CTest configuration. Exact registration block exercised in a separate minimal CMake harness: BUILD_TESTING=ON 1/1 CTest passed (4/4 Python methods), OFF zero tests, timeout 15 s. Both existing Python source identities matched E0012. Full native clone failed DNS; no full project configure/build or regression rerun. No official source admitted or rule implemented.

CTR-E0015: required base reference artifacts are now locally available and structurally indexed. Independent extraction agreement verified; details and identifiers retained outside public version control. No engine behavior or test results changed. Reference completeness, effective scope and admission remain open.

CTR-E0016: private requirements-routing inventory and preliminary effective-profile reconciliation completed. Structural audit passed, including eight injected invalid-record cases. Individual semantic review, scoped admission, and execution evidence remain outstanding. No runtime changes or native tests in this milestone.

CTR-E0017: full current native and Python regression recovered via a bounded free standard hosted runner on a dedicated public validation branch. 24/24 CTest executions passed across GCC Release and Clang Debug ASan/UBSan, including source_admission in both complete builds. All 24 source/build/test blob identities match the starting revision. No runtime changes or official gameplay. Full integration gap from E0014 closed for these configurations.

CTR-E0018: reusable generic authoritative object storage implemented. Stable object/type/container/principal IDs, ordered membership, explicit visibility and count disclosure, validated snapshots, atomic batch transfers, and caller-supplied session/revision checks. Full GCC Release and Clang ASan/UBSan regression passed 26/26; all 26 source/build/test identities matched the runner. No new game-specific mechanics; existing fixture kernel unchanged.

CTR-E0019: implemented reusable ordered sampling, explicit permutation outcomes, exact front extraction and atomic draw-before-return exchange on the E0018 object store. Full GCC Release and Clang ASan/UBSan regression passed 28/28; all 28 source/build/test identities matched checkout log. Headless-only scope recorded. Private setup review identifies additional semantic gaps. No complete game initialization, official mechanics acceptance or native Riftbound games.

CTR-E0020: separate private original rules-derived setup research prototype implemented and locally tested for ordinary 1v1 constructed first-game initialization. Two focused native configurations passed; no production engine changes, full repository regression, actual games or scoped admission claim. Private implementation and detailed traceability retained in user-controlled artifact; production integration withheld.

CTR-E0021: private setup prototype migrated to exact existing CTR RNG; handoff into existing authoritative store preserves all physical identities, incarnations and ordered membership. Restricted rules-derived turn and basic resource operations implemented and tested locally with abstract types. Final 4/4 focused CTest executions passed, including setup regression. No production code change, full repository regression, source admission or complete games.

CTR-E0022: private restricted spell and finalized-chain research extends E0021 with atomic fixed Energy/domain-Power payment, reactions, priority passes, two untargeted effects and owner-trash transfer. Final 6/6 focused CTest executions passed after correcting a generated fixture and rerunning sanitizer with -O1. No production runtime change, full repository regression, complete source admission or complete games.

CTR-E0023: private rules-derived pending spell, payment-window and finalization extension with explicit cleanup barriers, controller-only resource abilities, prospective affordability, exact payment and restricted rollback. Existing pre-funded shortcut shares the new implementation. Final 8/8 focused regression executions passed. General task scheduler, multiple pending items and real effect cleanup remain incomplete. Public runtime unchanged; no production admission, complete games or full public regression.

CTR-E0024: private restricted trigger scheduling extension; explicit task queue, controller ordering, pending logical FIFO, optional finalization, immediate resources, mixed finalized stack and rollback preservation. Final 10/10 focused regression executions passed. Complete recursive scheduling, actual cleanup effects, triggered costs/targets and non-main-phase tasks remain open. Public runtime unchanged; no complete games or production admission.

CTR-E0025: private restricted finalized-chain targeting and counter effects. Revision-bound target selection binds physical ID/incarnation or logical ability instance; validates at finalization and revalidates at resolution. Supports non-top removal, no refund, independent draw after invalidation, and targeted rollback. Final 12/12 focused regression executions passed. No complete targeting evaluator, public runtime change, complete games or production admission.

CTR-E0026: private restricted resource-cost policy evaluation and locked spell payment, plus triggered-ability resource payment windows and explicit decline. Final 14/14 focused regression executions passed after correcting a compiler warning and separately rerunning an interrupted sanitizer test command. No general cost evaluator, public runtime change, complete games or production admission.

CTR-E0027: private base-only unit deployment and lifecycle extension. Hand/champion deployment uses shared pending payment and direct unit finalization; authoritative base membership, readiness, single board targets, marked damage, lethal cleanup, owner-trash transfer, healing and redeployment. Final 16/16 focused regression executions passed after correcting compile and fixture issues and resuming interrupted sanitizer build. No production runtime change, full public regression, complete games or production admission.

CTR-E0028: private restricted battlefield movement/control, controlled-field deployment, focus and showdown timing, Conquer/Hold scoring, final-point restriction and eight-point victory. Six scripted abstract terminal paths per configuration; contested combat stops at explicit unsupported handoff. Final 18/18 focused regression executions passed. No production runtime change, full public regression, complete competitive games or production admission.

Next: restore exact E0028 private archive and rerun both nine-test configurations; reconcile isolated E0029/E0030 with authoritative combat designation, snapshot identity, damage staging and effect admission. Apply marks to cumulative board, implement repeated cleanup, global healing, recall, result/control/scoring and trigger barriers. Extend effects/legality/catalog/serialization and scoped admission. CTR-1 OPEN; no CTR-2 advancement.

CTR-E0029 (2026-11-25): isolated private original combat assignment research candidate, not a cumulative E0028 continuation. E0028 private archive was located but raw-byte restoration rejected; exact baseline source and prior test rerun unavailable. Pinned Core Rules reference recovered and hash matched prior private evidence. Restricted effective-Might/stun/marked-damage, lethal allocation, priority conflicts and simultaneous damage calculation validated independently; final 2/2 focused CTest executions (GCC Release, Clang ASan/UBSan), 192456 candidate plans and 208494 independent oracle vectors per configuration. No public runtime change, complete combat resolution, production admission, games or gate advancement. See CTR-E0029.

CTR-E0030 (2026-11-25): verified exact E0029 private archive and extended it with isolated staged combat transactions: session/revision, actor and incarnation-bound roster checks, attacker-first assignment, simultaneous marked-damage result, empty-side authority skip and explicit cleanup-pending stop. Final GCC Release and Clang ASan/UBSan 4/4 focused CTest executions including unchanged E0029 suite. E0028 restoration still denied, no cumulative board integration, complete cleanup or production admission. See CTR-E0030. CTR-1 OPEN.

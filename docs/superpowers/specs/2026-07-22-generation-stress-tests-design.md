# Design Spec — Phase 24: Büyük Ölçekli Üretim Testleri (Large-Scale Generation Stress Tests)

## Problem

The dynamic generation system (`QuestionGenerationEngine`, `GeneratorRegistry`,
`GeneratorScoring`, `GeneratedQuestionValidator`, and 17 generators as of
Phase 23) is only tested at small scale: the per-generator test files each
run ~200 iterations, and `QuestionGenerationEngineTests.cpp` tests the
engine's escalation logic against a scripted test double
(`FixedSequenceGenerator`), not the real generators. The original spec asked
for a 10,000-iteration stress test exercising uniqueness, correctness, and
performance against the real system. No such test exists yet.

## What "stress test" means here, concretely

A manual 10,000-iteration integration run (registry + engine + scoring +
validator, all 17 real generators, fixed-seed RNG) was used to calibrate
this spec before writing it, rather than guessing at behavior or bounds:

- **Success rate: 10000/10000.** Total exhaustion (the engine returning
  `std::nullopt`) essentially never happens in the full 17-generator system,
  because `ArrayElementPredictGenerator`'s domain (5 elements × 100 values ×
  2 shapes ≈ 5×10^11 combinations) is practically inexhaustible, and the
  CrossTopic fallback stage can always reach it regardless of which topic
  was originally picked.
- **Uniqueness: 0 duplicate `exactHash` values** across all 10,000 returned
  questions, checked independently of the engine's own internal
  `QuestionHistory` (i.e., re-verified at the test level, not just trusted).
- **Correctness: 0 disagreements** between the engine's internal validation
  gate and an independent `GeneratedQuestionValidator::isValid` re-check on
  every returned question.
- **Performance: ~10.3 seconds** for 10,000 iterations on the dev machine.
  This is dominated by `QuestionGenerationEngine`'s developer-log writes
  (`appendLogLine` opens/appends/closes `data/question_generation.log` once
  per exhausted (stage, generator) pair) — small-domain generators like
  `BoolOutputPredictGenerator`, `ForLoopSumPredictGenerator`,
  `StringConcatPredictGenerator`, and `InheritanceOverridePredictGenerator`
  exhaust their own-topic stages on most calls and fall through to
  CrossTopic, each exhaustion contributing a log write.

Given ~10 seconds per full run, this test must **not** join the existing
`CppMasterConsoleTests` binary (which currently runs in well under a
second via `ctest` and is meant to be run constantly during development).
It needs its own opt-in executable.

## Scope

1. A new, separate test executable, `CppMasterConsoleStressTests`, built
   from a new `tests/StressTests/` directory (mirrors the existing
   `tests/Generators/` subdirectory convention introduced in Phase 23).
   Reuses the existing `TestRunner`/`TEST_CASE`/`CHECK` framework from
   `tests/TestRunner.h` — no new test framework.
2. Built by the normal `cmake --build` (so it's always compile-verified,
   catching bit-rot), but **not** registered via `add_test()` — it does not
   run under `ctest` or as part of the default fast suite. It is run
   manually: `./build/Debug/CppMasterConsoleStressTests.exe`.
3. Two test cases, both against the real `GeneratorRegistry` with all 17
   production generators registered (not test doubles) and a fixed-seed
   `std::mt19937_64` (determinism, matching every other test in this
   codebase):
   - **Mixed-topic stress test** (10,000 iterations): each iteration picks
     a uniformly random topic among the 17 registered generators (mirroring
     `Application::runQuickTest`'s actual selection logic) and calls
     `generateUniqueForTopic`. Asserts: every call succeeds; every returned
     question's `exactHash` is globally unique across the whole run
     (test-level `std::unordered_set`, independent of the engine's own
     history); every returned question independently passes
     `GeneratedQuestionValidator::isValid`; every returned question's
     `topicId` is one of the 17 registered topic ids. Elapsed wall-clock
     time is asserted under a generous 30-second budget (~3x the observed
     baseline — tight enough to catch a real regression, loose enough to
     not be flaky on a slower machine).
   - **Single-topic exhaustion stress test** (500 iterations, topic 9 only
     — `BoolOutputPredictGenerator`, chosen because it has one of the
     smallest domains in the system): repeatedly calls
     `generateUniqueForTopic(9, ...)` without ever picking another topic,
     deliberately forcing constant escalation through
     `ExpandedParameters`/`StructuralVariation` and CrossTopic fallback on
     nearly every call. Asserts every call still succeeds (proving the
     CrossTopic fallback alone is robust enough to sustain a fully
     exhausted single-generator topic indefinitely) and that global
     uniqueness still holds.
4. The engine's log file path is redirected to
   `tests/test_data/generation_stress_test.log` (the established
   test-artifact convention from Phase 23), with explicit
   `std::filesystem::remove()` cleanup — this test must never write to
   the real `data/question_generation.log`.
5. `docs/superpowers/roadmap.md`: strike through the "No large-scale
   generation tests" gap bullet with a resolution note, add the Phase 24
   COMPLETE summary bullet, update the Status section to point at Phase 25.

## Out of scope

- No changes to the generators, engine, or any Phase 23 architecture — this
  phase is purely additive testing.
- No CI wiring (this project has no CI pipeline as of this phase; the
  stress executable is a manually-run local tool).
- No attempt to reduce the ~10s runtime (e.g., batching log writes) — that
  would be a real code change to production logging behavior, not a test
  addition, and is out of scope for a testing-only phase. If a future phase
  wants faster logging, that's a separate, deliberate decision.

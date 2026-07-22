# Plan — Phase 24: Büyük Ölçekli Üretim Testleri (Large-Scale Generation Stress Tests)

Spec: `docs/superpowers/specs/2026-07-22-generation-stress-tests-design.md`

Base commit (before Task 1): `fb7ca95` (Phase 23 close-out, roadmap range fix)

## Task 1 — New stress-test executable

- `tests/StressTests/main.cpp` — same pattern as `tests/main.cpp`
  (`std::filesystem::create_directories("tests/test_data")` then
  `TestRunner::instance().runAll()`).
- `tests/StressTests/GenerationStressTests.cpp`:
  - Include all 17 production generator headers, `GeneratorRegistry`,
    `GeneratorScoring`, `GeneratedQuestionValidator`, `QuestionGenerationEngine`.
  - `TEST_CASE(GenerationStress_TenThousandMixedTopicIterationsAllUniqueAndValid)`:
    fixed-seed `std::mt19937_64`, all 17 generators registered, 10,000
    iterations picking a uniformly random registered topic per iteration
    (mirrors `Application::runQuickTest`'s selection). Per the spec: assert
    every call succeeds, assert global `exactHash` uniqueness via a
    test-level `std::unordered_set`, assert every result independently
    passes `GeneratedQuestionValidator::isValid`, assert `topicId` is
    always one of the 17 registered ids, assert total elapsed time is
    under 30 seconds (`std::chrono::steady_clock`).
  - `TEST_CASE(GenerationStress_FiveHundredSingleTopicExhaustionIterationsAllSucceed)`:
    same setup, but every one of 500 iterations targets topic 9
    (`BoolOutputPredictGenerator`) only. Assert every call still succeeds
    and global uniqueness still holds (proves the CrossTopic fallback
    alone sustains a fully-exhausted single topic).
  - Log path: `tests/test_data/generation_stress_test.log`, removed via
    `std::filesystem::remove()` before and after each test case (before, to
    ensure a clean start if a prior run crashed mid-test; after, as normal
    cleanup) — matches the existing `tests/test_data/` convention.
- `CMakeLists.txt`: new `add_executable(CppMasterConsoleStressTests ...)`
  target (`tests/TestRunner.h`, `tests/StressTests/main.cpp`,
  `tests/StressTests/GenerationStressTests.cpp`), linked against
  `CppMasterConsoleLib`, `apply_strict_warnings` applied, include dirs
  `src` (public, inherited) and `tests` (for `TestRunner.h`). Deliberately
  **no** `add_test()` call for this target — it must not join `ctest`.
- Build (`cmake --build build`), confirm zero warnings for the new target.
- Run `./build/Debug/CppMasterConsoleStressTests.exe` manually; confirm
  both test cases report `[PASS]` and the summary line reads `2/2`.
- Run the existing `CppMasterConsoleTests.exe` and `ctest` too, confirming
  the new target's addition didn't change the existing suite's count or
  runtime (it shouldn't, since it's a separate executable).

## Task 2 — Roadmap close-out

- `docs/superpowers/roadmap.md`: strike through the "No large-scale
  generation tests" gap bullet with a resolution note (10,000-iteration
  mixed-topic test + 500-iteration single-topic exhaustion test, both
  100% success / 0 duplicates / 0 validator disagreements, real elapsed
  time noted). Add the Phase 24 COMPLETE summary bullet with the commit
  range. Update the Status section to mark Phase 24 complete and point at
  Phase 25 next.
- Update `.superpowers/sdd/progress.md` (local ledger, gitignored) with
  Task 1/Task 2 entries and a phase-close entry, following the same
  format as every prior phase.

# CppMaster Console — Polish (Phase 7) Design

## Context

Final sub-project of the decomposition: Foundation → Static lesson + quiz
core → Richer question types → Persistence + review loop → Meta systems →
Dynamic generation → **Polish**. Phases 1-6 are complete, reviewed, and
merged. The app is feature-complete for its current scope: 100-topic
catalog (10 with real content), 11 question types, XP/leveling,
achievements, mistake review, daily review, a section exam, and dynamic
question generation via "Hızlı Test."

What's missing, carried since the very first spec: a real, permanent,
re-runnable test suite (every phase so far verified behavior with
temporary `main.cpp` swaps and hand-computed exact transcripts, then threw
the harness away), a README, and an honest cross-platform check (the
project has only ever been built with MSVC in this Windows environment;
GCC/Clang compliance has been asserted by code inspection every phase, never
verified by an actual build).

## Goal

Close out the project: add a standard-library-only unit test suite covering
the pure-logic and persistence layers, wire it into CMake/CTest, write a
README, and do a real cross-platform code-inspection pass — fixing anything
genuinely non-portable found, and stating plainly what remains
inspection-only (no GCC/Clang/Linux/macOS toolchain is available in this
dev environment to actually verify).

## Scope cuts (deliberate, not oversights)

- **No external test framework.** Same "standard library only" rule as
  every other phase. A small hand-rolled self-registering test runner
  (`tests/TestRunner.h`) replaces Catch2/doctest/GoogleTest — just enough
  structure (non-fatal `CHECK` assertions, per-test pass/fail, a summary
  line, a process exit code CTest can read) to be worth calling a "test
  suite," nothing more.
- **`Application` and `ConsoleUI` are not unit-tested.** They are the
  interactive shell: stdin-driven menu loops and console rendering. Testing
  them properly needs a fake-console/stdin-injection harness, which is a
  bigger investment than this phase's remaining scope justifies. They stay
  covered the way they always have been — the piped-exact-transcript manual
  verification recorded in every phase's plan — which is a real, repeatable
  procedure, just not an automated one. Every other class in `src/` (all
  pure logic or file persistence, no console I/O) gets real unit tests.
- **No CI pipeline.** `ctest` becomes runnable locally
  (`ctest --test-dir build`), which is what "unit tests" in the original
  spec actually requires. Standing up GitHub Actions or similar is a
  reasonable follow-up once the repo goes public, not part of closing out
  this phase.
- **Cross-platform verification is inspection-only, stated honestly.** No
  WSL, MinGW, or Clang toolchain exists in this environment (confirmed:
  `g++`/`clang++` not found, WSL not installed). The README will say so
  plainly rather than implying a build was actually run on Linux/macOS.
  Anything found to be genuinely non-portable during the inspection pass
  gets fixed; ConsoleUI already guards its one platform-specific piece
  (`cls`/`clear`, UTF-8 console codepage) behind `#ifdef _WIN32` — a quick
  read confirms no other file touches anything platform-specific.

## New files

```
tests/TestRunner.h                       (new — self-registering test framework, header-only)
tests/main.cpp                           (new — runs all registered tests, returns pass/fail exit code)
tests/FnvHashTests.cpp                   (new)
tests/LevelSystemTests.cpp               (new)
tests/UserProgressTests.cpp              (new)
tests/QuizEngineTests.cpp                (new — one test per question-type matching rule)
tests/ProgressManagerTests.cpp           (new — round-trip + corruption, via scratch files)
tests/MistakeTrackerTests.cpp            (new — round-trip + corruption, via scratch files)
tests/AchievementTrackerTests.cpp        (new — unlock-once + round-trip + corruption)
tests/QuestionHistoryTests.cpp           (new — round-trip + corruption)
tests/QuestionGenerationEngineTests.cpp  (new — retry/reject/exhaust, using a small test-only fake generator)
tests/GeneratorsTests.cpp                (new — fixed-seed determinism + range safety for both real generators)
tests/QuestionManagerTests.cpp           (new — data-integrity: every exam id resolves, no duplicate ids)
tests/LessonManagerTests.cpp             (new — data-integrity: topics 1-10 have content, 11-100 don't yet)
README.md                                (new)
CMakeLists.txt                           (modified — split into a library + app executable + test executable)
.gitignore                               (modified — add tests/test_data/, the scratch dir persistence tests write to)
```

## Test framework

```cpp
// tests/TestRunner.h
class TestRunner {
public:
    static TestRunner& instance();
    void addTest(std::string name, std::function<void()> testFunction);
    int runAll();
    void reportFailure(const std::string& expression, const std::string& file, int line);
private:
    struct TestCase { std::string name; std::function<void()> testFunction; };
    std::vector<TestCase> tests_;
    int currentTestFailureCount_ = 0;
};

#define CHECK(condition) /* records a non-fatal failure with file:line if false */
#define TEST_CASE(name) /* declares a function and self-registers it via a static registrar */
```

`CHECK` is non-fatal (a failed check doesn't abort the rest of the test —
matches how every prior phase's verification harness printed multiple
`(OK)`/`(HATA)` lines per run rather than stopping at the first mismatch).
`TEST_CASE(name) { ... }` expands to a function plus a file-scope static
registrar object whose constructor calls `TestRunner::instance().addTest(...)`
— so every `.cpp` file self-registers its tests just by being linked in;
`tests/main.cpp` never needs a manually-maintained list. `runAll()` prints
`[PASS]`/`[FAIL]` per test (with the failing `CHECK` expressions and
locations under any `[FAIL]`), then a final `N/M test(s) passed.` line, and
returns 0 only if every test passed — this is what CTest reads to report
green/red.

## CMake restructuring

Everything except `src/main.cpp` moves into a new `STATIC` library target,
`CppMasterConsoleLib`, so both the real app and the test binary link the
same compiled code instead of recompiling it twice or fighting over two
`main()` symbols:

```
CppMasterConsoleLib (STATIC lib: all of src/ except main.cpp)
  -> target_include_directories(... PUBLIC src)
  -> same /W4 /permissive- or -Wall -Wextra -Wpedantic -Wconversion -Wshadow as today

CppMasterConsole (executable: src/main.cpp only)
  -> links CppMasterConsoleLib

CppMasterConsoleTests (executable: tests/*.cpp)
  -> links CppMasterConsoleLib
  -> target_include_directories(... PRIVATE tests)
  -> same warning flags as the lib

enable_testing()
add_test(NAME CppMasterConsoleTests COMMAND CppMasterConsoleTests)
```

This is the one piece of this phase with real regression risk (it touches
the build of the already-shipped, already-reviewed app itself, for the
first time since Foundation) — the plan will require rebuilding
`CppMasterConsole` after the split and re-running a known-exact regression
transcript from an earlier phase to prove the split changed nothing
observable about the real app.

## Persistence test isolation

`ProgressManager`/`MistakeTracker`/`AchievementTracker`/`QuestionHistory`
tests write to `tests/test_data/<unique-name>.txt` — never `data/`, which
holds the real user's progress and must never be touched by a test run.
Each test cleans up its own scratch files at the end (delete after
asserting), so repeated `ctest` runs stay idempotent and the directory
doesn't accumulate stale fixtures. `tests/test_data/` is added to
`.gitignore` (mirrors the existing `data/` entry).

## What gets tested, and why

- **`FnvHash`**: the empty-string offset-basis identity, determinism
  (same input → same hash), and that two different inputs produce
  different hashes for a representative sample — the same three properties
  every phase-6 harness already checked by hand, now permanent.
- **`LevelSystem`**: all 10 level thresholds, including the boundary values
  themselves (e.g. exactly `50` XP → level 2, `49` → level 1).
- **`UserProgress`**: streak increment/reset-on-wrong/longest-streak
  tracking, typed-correct-answer counters (WriteCode vs. FindError/FixCode
  combined), `addXp` accumulation.
- **`QuizEngine::evaluate`**: one representative case per question type's
  matching rule — ASCII case-insensitive for MC/TF/FillBlank, case-sensitive
  whitespace-collapsed for CompleteLine/PredictOutput/FindError/FixCode,
  digit-sequence-tolerant for OrderCode, AND-all-substrings-required (not
  OR-any) plus bracket-balance for WriteCode — since this is the single
  most business-logic-dense file in the project.
- **`ProgressManager`/`MistakeTracker`/`AchievementTracker`/`QuestionHistory`**:
  save-then-load round trip preserves every field; a missing file loads as
  fresh/empty with no corruption flag; a deliberately malformed line is
  detected, backed up, and resets to fresh state — the corruption-safe
  contract every one of these classes shares.
- **`QuestionGenerationEngine`**: using a small test-only fake
  `IQuestionGenerator` whose next few return values the test controls
  directly, verify the OR-based (exact-or-semantic) rejection, the
  accept-only-on-success recording, and the 50-attempt exhaustion return of
  `std::nullopt` — properties that are awkward to pin down through the two
  real generators' own randomness, easy through a fake.
- **`IntArithmeticPredictGenerator`/`BoolOutputPredictGenerator`**: fixed
  `std::mt19937_64` seeds reproduce the exact same candidate every run
  (determinism), computed answers are correct for both operators/branches,
  no combination of parameters can produce undefined behavior or an
  unanswerable question, and `BoolOutputPredictGenerator`'s semantic
  signature genuinely depends only on the boolean value (proving its
  2-variant ceiling is real, not incidental).
- **`QuestionManager`/`LessonManager`**: data-integrity checks against the
  hand-authored catalogs themselves — every id in `Application`'s fixed
  20-question exam list resolves via `findById`, no duplicate question or
  topic ids exist, topics 1-10 have non-empty lesson content and 11-100
  intentionally don't (matching `openTopic`'s honest gate). These aren't
  "logic" tests so much as regression guards against ever silently breaking
  the hand-authored data while touching something else nearby.

## README contents

Written in Turkish, matching the app's own language and its target reader
(the project's author, learning C++). Covers: what the project is, current
feature scope (which topics have real content vs. not yet), how to build
(`cmake -B build`, `cmake --build build`, per-platform notes), how to run
the app and how to run the test suite (`ctest --test-dir build` or running
the `CppMasterConsoleTests` binary directly), project structure (`src/`,
`tests/`, `data/`, `docs/`), and an honest "Cross-Platform Notlar" section:
MSVC/Windows is the only toolchain this project has actually been built
with; the code avoids all known MSVC-only constructs and isolates its one
genuinely platform-specific behavior (console-clear command, UTF-8 codepage
setup) behind `#ifdef _WIN32`, but GCC/Clang/Linux/macOS compliance has not
been verified by an actual build in this environment.

## Testing / verification for this phase

The test suite is the deliverable, so it needs its own proof it actually
detects failure, not just success: at least one task's manual verification
step will temporarily introduce a deliberately-wrong `CHECK` (e.g. asserting
`1 == 2`) into a real test file, rebuild, confirm `CppMasterConsoleTests`
reports `[FAIL]` with the correct file:line and a non-zero exit code, then
remove it and rebuild clean — proving the harness's failure path works, not
just its happy path. Every other test file gets the exact expected pass
output verified directly (same rigor as every prior phase's hand-computed
transcripts, just against a permanent binary instead of a throwaway one).
The CMake restructuring step gets an explicit before/after regression check
against a known exact transcript from an earlier phase, since it's the one
change in this phase that touches the shipped app's own build.

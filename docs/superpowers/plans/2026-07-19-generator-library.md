# Üretici Kütüphanesi Genişletmesi Implementation Plan (Phase 23)

> **Execution note:** subagent dispatch remains blocked by a weekly
> rate limit; this plan is executed directly by the controller.
> Given the scale of this phase (17 total generators, 4 new classes, a
> redesigned engine), the shared architecture (Tasks 1-4) is specified
> here in full; the 15 new generators (Task 5) are specified as a
> design table (parameters, code shape, expected output) rather than
> full source, since each is implemented directly following the exact
> pattern established by Task 1's retrofit of the 2 existing
> generators — writing full source twice (plan + implementation) would
> be pure duplication for a phase this size. Each generator is still
> compile-verified, unit-tested, and committed individually with the
> same rigor as every other phase.

**Goal:** Expand the dynamic generator library from 2 to 17 generators
across the roadmap's 15 named topic areas, and replace the flat
50-attempt retry loop with a 4-stage escalation algorithm
(Normal → ExpandedParameters → StructuralVariation → CrossTopic),
backed by 4 new classes (`ParameterDomain`, `GeneratedQuestionValidator`,
`GeneratorRegistry`, `GeneratorScoring`) and a developer log.

## Global Constraints

- `IQuestionGenerator` gains `topicId()` and a `GenerationStage`
  parameter on `generate()` — both existing generators
  (`IntArithmeticPredictGenerator`, `BoolOutputPredictGenerator`) are
  updated to match, preserving their existing `Normal`-stage behavior
  exactly (same parameter ranges, same signatures) and adding a
  genuine `ExpandedParameters` response (wider `ParameterDomain`).
- Every new generator: pure, stateless (`const`-qualified `generate`,
  no member fields beyond `constexpr` data), uses `ParameterDomain`
  for every randomized range (no bare `std::uniform_int_distribution`
  calls with inline magic numbers), computes both `exactSignature`
  (every drawn parameter) and `semanticSignature` (only parameters
  that change the CORRECT ANSWER, matching the existing generators'
  documented convention), and hashes both via `fnv1a64`
  (`src/FnvHash.h`, already exists, no changes needed).
- `GeneratedQuestion`'s nested `Question.topicId`/`difficulty`/`baseXp`
  must be internally consistent with the fixed per-difficulty XP
  scheme already used everywhere else in this project (VeryEasy=5,
  Easy=10, Medium=20, Hard=30) — pick ONE difficulty per generator
  (documented in the Task 5 table) rather than varying it.
- `GeneratorRegistry` is non-owning (raw pointers into
  `Application`-owned generator members, mirroring the existing
  `intArithmeticGenerator_` pattern).
- `GeneratorScoring` is in-memory only (no persistence file).
- The developer log (`data/question_generation.log`) is a flat,
  append-only text file; the engine takes its path as a constructor
  parameter so tests can redirect it away from the real `data/`
  directory.
- `QuestionGenerationEngine`'s old single-generator
  `generateUnique(generator, rng)` method is REMOVED and replaced by
  `generateUniqueForTopic(topicId, registry, scoring, validator, rng)`.
  `QuestionHistory`'s public interface is UNCHANGED (still just
  exact/semantic hash set + record, reused as-is by the new engine).

---

### Task 1: `GenerationStage` + `ParameterDomain` + interface change + retrofit existing generators

**Files:**
- Modify: `src/IQuestionGenerator.h` (add `GenerationStage` enum,
  `topicId()`, stage parameter on `generate()`)
- Create: `src/ParameterDomain.h` (header-only)
- Modify: `src/generators/IntArithmeticPredictGenerator.h/.cpp`,
  `src/generators/BoolOutputPredictGenerator.h/.cpp` (implement
  `topicId()`, accept+honor `stage`, switch magic-number ranges to
  `ParameterDomain`)
- Modify: `tests/GeneratorsTests.cpp` (update call sites for the new
  `generate(rng, stage)` signature; add stage-specific assertions)
- Modify: `tests/QuestionGenerationEngineTests.cpp`'s
  `FixedSequenceGenerator` test double (implement `topicId()`, accept
  `stage` — can ignore its value, it just replays a fixed sequence)
- Create: `tests/ParameterDomainTests.cpp`
- Modify: `CMakeLists.txt` (register `src/ParameterDomain.h`,
  `tests/ParameterDomainTests.cpp`)

- [ ] **Step 1: `src/ParameterDomain.h`**

```cpp
#pragma once

#include <random>

struct ParameterDomain {
    int min;
    int max;

    [[nodiscard]] int draw(std::mt19937_64& randomEngine) const {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(randomEngine);
    }

    [[nodiscard]] ParameterDomain expanded() const {
        const int span = max - min;
        const int growth = span > 0 ? span : 1;
        return ParameterDomain{min - growth, max + growth};
    }
};
```

- [ ] **Step 2: `tests/ParameterDomainTests.cpp`**

```cpp
#include "ParameterDomain.h"

#include "TestRunner.h"

TEST_CASE(ParameterDomain_DrawStaysWithinBounds) {
    ParameterDomain domain{5, 10};
    std::mt19937_64 randomEngine(42);
    for (int i = 0; i < 200; ++i) {
        const int value = domain.draw(randomEngine);
        CHECK(value >= 5);
        CHECK(value <= 10);
    }
}

TEST_CASE(ParameterDomain_ExpandedCoversAndExceedsOriginalRange) {
    ParameterDomain domain{5, 10};
    const ParameterDomain expanded = domain.expanded();
    CHECK(expanded.min < domain.min);
    CHECK(expanded.max > domain.max);
    CHECK(expanded.min <= domain.min);
    CHECK(expanded.max >= domain.max);
}

TEST_CASE(ParameterDomain_ExpandedOfSinglePointDomainStillWidens) {
    ParameterDomain domain{7, 7};
    const ParameterDomain expanded = domain.expanded();
    CHECK(expanded.min < 7);
    CHECK(expanded.max > 7);
}
```

- [ ] **Step 3: Update `src/IQuestionGenerator.h`**

```cpp
#pragma once

#include <optional>
#include <random>
#include <string_view>

#include "GeneratedQuestion.h"

enum class GenerationStage { Normal, ExpandedParameters, StructuralVariation };

class IQuestionGenerator {
public:
    virtual ~IQuestionGenerator() = default;
    [[nodiscard]] virtual std::string_view id() const noexcept = 0;
    [[nodiscard]] virtual int topicId() const noexcept = 0;
    [[nodiscard]] virtual std::optional<GeneratedQuestion> generate(
        std::mt19937_64& randomEngine, GenerationStage stage) const = 0;
};
```

- [ ] **Step 4: Retrofit `IntArithmeticPredictGenerator`**

Add `int topicId() const noexcept override { return 6; }`. Change
`generate(std::mt19937_64&) const` to
`generate(std::mt19937_64& randomEngine, GenerationStage stage) const`.
Replace the existing inline `std::uniform_int_distribution` calls for
start value (`[-20,50]`) and operand (`[1,15]`) with two
`ParameterDomain` constants (`kStartDomain{-20,50}`,
`kOperandDomain{1,15}`); when `stage != GenerationStage::Normal`, draw
from `.expanded()` instead. `StructuralVariation` reuses the
`ExpandedParameters` response (no second natural shape for this
generator — document this with a one-line comment, not silently).
Same output-computation logic otherwise (unchanged).

- [ ] **Step 5: Retrofit `BoolOutputPredictGenerator`**

Same treatment: `topicId() { return 9; }`, stage parameter threaded
through, its single boolean parameter's "domain" is trivially binary
so `ExpandedParameters`/`StructuralVariation` both just reuse `Normal`
(there is nothing to expand — document why).

- [ ] **Step 6: Update `tests/GeneratorsTests.cpp` call sites**

Every existing `generator.generate(randomEngine)` call becomes
`generator.generate(randomEngine, GenerationStage::Normal)`. Add one
new test per generator confirming `topicId()` returns the expected
value, and one confirming `ExpandedParameters`-stage draws still
produce a valid `GeneratedQuestion` with a self-consistent
prompt/answer (reusing the same 200-iteration invariant-check pattern
already used for `Normal`).

- [ ] **Step 7: Update `tests/QuestionGenerationEngineTests.cpp`'s test double**

`FixedSequenceGenerator::generate` gains the `GenerationStage stage`
parameter (unused — the test double ignores it and just replays its
fixed sequence regardless of stage, which is the correct/simplest
behavior for a test double whose whole point is deterministic
replay). Add `topicId()` returning a fixed test value (e.g. `1`).

- [ ] **Step 8: Register new files in CMake, build, test**

Add `src/ParameterDomain.h` and `tests/ParameterDomainTests.cpp` to
`CMakeLists.txt`.

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: all existing tests still pass, plus 3 new `ParameterDomain_*`
tests and the new per-generator `topicId`/expanded-stage tests.

- [ ] **Step 9: Commit**

```bash
git add src/IQuestionGenerator.h src/ParameterDomain.h src/generators/IntArithmeticPredictGenerator.h src/generators/IntArithmeticPredictGenerator.cpp src/generators/BoolOutputPredictGenerator.h src/generators/BoolOutputPredictGenerator.cpp tests/GeneratorsTests.cpp tests/QuestionGenerationEngineTests.cpp tests/ParameterDomainTests.cpp CMakeLists.txt
git commit -m "feat(generators): add GenerationStage/ParameterDomain, retrofit existing generators"
```

---

### Task 2: `GeneratedQuestionValidator`

**Files:**
- Create: `src/GeneratedQuestionValidator.h/.cpp`
- Create: `tests/GeneratedQuestionValidatorTests.cpp`
- Modify: `CMakeLists.txt`

- [ ] **Step 1: `src/GeneratedQuestionValidator.h`**

```cpp
#pragma once

#include "GeneratedQuestion.h"

class GeneratedQuestionValidator {
public:
    [[nodiscard]] bool isValid(const GeneratedQuestion& candidate) const;
};
```

- [ ] **Step 2: `src/GeneratedQuestionValidator.cpp`**

```cpp
#include "GeneratedQuestionValidator.h"

#include "Enums.h"

bool GeneratedQuestionValidator::isValid(const GeneratedQuestion& candidate) const {
    const Question& question = candidate.question;

    if (question.prompt.empty()) {
        return false;
    }
    if (question.topicId < 1 || question.topicId > 100) {
        return false;
    }
    if (question.baseXp <= 0) {
        return false;
    }

    if (question.type == QuestionType::MultipleChoice) {
        if (question.options.size() != 4) {
            return false;
        }
        if (question.acceptedAnswers.size() != 1) {
            return false;
        }
        const std::string& answer = question.acceptedAnswers.front();
        if (answer.size() != 1 || answer[0] < 'a' || answer[0] > 'd') {
            return false;
        }
        return true;
    }

    if (question.type == QuestionType::TrueFalse) {
        if (!question.options.empty()) {
            return false;
        }
        if (question.acceptedAnswers.size() != 1) {
            return false;
        }
        const std::string& answer = question.acceptedAnswers.front();
        return answer == "1" || answer == "2";
    }

    return !question.acceptedAnswers.empty();
}
```

(Check `src/Enums.h` for the exact `QuestionType` enumerator names
before finalizing — confirm `MultipleChoice`/`TrueFalse` spelling
matches exactly.)

- [ ] **Step 3: `tests/GeneratedQuestionValidatorTests.cpp`**

Cover: a valid `MultipleChoice` candidate passes; wrong option count
fails; out-of-range `acceptedAnswers` letter fails; a valid
`TrueFalse` candidate passes; a `TrueFalse` candidate with a stray
`options` entry fails; a `TrueFalse` candidate with `acceptedAnswers`
other than `{"1"}`/`{"2"}` fails; empty prompt fails; `topicId` of 0
and 101 both fail; `baseXp` of 0 fails.

- [ ] **Step 4: Register, build, test, commit**

Add both new files to `CMakeLists.txt`. Build, run
`CppMasterConsoleTests.exe`, confirm all pass including the new
`GeneratedQuestionValidator_*` tests, then:

```bash
git add src/GeneratedQuestionValidator.h src/GeneratedQuestionValidator.cpp tests/GeneratedQuestionValidatorTests.cpp CMakeLists.txt
git commit -m "feat(generators): add GeneratedQuestionValidator"
```

---

### Task 3: `GeneratorRegistry` + `GeneratorScoring`

**Files:**
- Create: `src/GeneratorRegistry.h/.cpp`
- Create: `src/GeneratorScoring.h/.cpp`
- Create: `tests/GeneratorRegistryTests.cpp`,
  `tests/GeneratorScoringTests.cpp`
- Modify: `CMakeLists.txt`

- [ ] **Step 1: `src/GeneratorRegistry.h`**

```cpp
#pragma once

#include <vector>

#include "IQuestionGenerator.h"

class GeneratorRegistry {
public:
    void registerGenerator(const IQuestionGenerator& generator);
    [[nodiscard]] std::vector<const IQuestionGenerator*> generatorsForTopic(int topicId) const;
    [[nodiscard]] const std::vector<const IQuestionGenerator*>& allGenerators() const;

private:
    std::vector<const IQuestionGenerator*> generators_;
};
```

- [ ] **Step 2: `src/GeneratorRegistry.cpp`**

```cpp
#include "GeneratorRegistry.h"

void GeneratorRegistry::registerGenerator(const IQuestionGenerator& generator) {
    generators_.push_back(&generator);
}

std::vector<const IQuestionGenerator*> GeneratorRegistry::generatorsForTopic(int topicId) const {
    std::vector<const IQuestionGenerator*> result;
    for (const IQuestionGenerator* generator : generators_) {
        if (generator->topicId() == topicId) {
            result.push_back(generator);
        }
    }
    return result;
}

const std::vector<const IQuestionGenerator*>& GeneratorRegistry::allGenerators() const {
    return generators_;
}
```

- [ ] **Step 3: `tests/GeneratorRegistryTests.cpp`**

Use a tiny local test-double generator (or the existing real
`IntArithmeticPredictGenerator`/`BoolOutputPredictGenerator`) to
confirm: an unregistered topic returns an empty vector;
`generatorsForTopic` returns exactly the registered generator(s) for
its own topic and nothing for others; `allGenerators()` returns every
registered generator regardless of topic, in registration order.

- [ ] **Step 4: `src/GeneratorScoring.h`**

```cpp
#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

class GeneratorScoring {
public:
    void recordAttempt(std::string_view generatorId, bool succeeded);
    [[nodiscard]] double successRate(std::string_view generatorId) const;

private:
    struct Stats {
        int successes = 0;
        int attempts = 0;
    };
    std::unordered_map<std::string, Stats> statsByGeneratorId_;
};
```

- [ ] **Step 5: `src/GeneratorScoring.cpp`**

```cpp
#include "GeneratorScoring.h"

void GeneratorScoring::recordAttempt(std::string_view generatorId, bool succeeded) {
    Stats& stats = statsByGeneratorId_[std::string(generatorId)];
    ++stats.attempts;
    if (succeeded) {
        ++stats.successes;
    }
}

double GeneratorScoring::successRate(std::string_view generatorId) const {
    const auto it = statsByGeneratorId_.find(std::string(generatorId));
    if (it == statsByGeneratorId_.end() || it->second.attempts == 0) {
        return 0.5;
    }
    return static_cast<double>(it->second.successes) / static_cast<double>(it->second.attempts);
}
```

- [ ] **Step 6: `tests/GeneratorScoringTests.cpp`**

Cover: an untried generator id returns `0.5`; recording successes/
failures updates the ratio correctly (e.g. 3 successes out of 4
attempts → `0.75`); different generator ids are tracked independently.

- [ ] **Step 7: Register, build, test, commit**

```bash
git add src/GeneratorRegistry.h src/GeneratorRegistry.cpp src/GeneratorScoring.h src/GeneratorScoring.cpp tests/GeneratorRegistryTests.cpp tests/GeneratorScoringTests.cpp CMakeLists.txt
git commit -m "feat(generators): add GeneratorRegistry and GeneratorScoring"
```

---

### Task 4: Rewrite `QuestionGenerationEngine` (4-stage algorithm + dev log)

**Files:**
- Modify: `src/QuestionGenerationEngine.h/.cpp`
- Modify: `tests/QuestionGenerationEngineTests.cpp` (mostly rewritten
  — old single-generator tests replaced with 4-stage/cross-topic
  coverage)

- [ ] **Step 1: `src/QuestionGenerationEngine.h`**

```cpp
#pragma once

#include <optional>
#include <random>
#include <string>

#include "GeneratedQuestion.h"
#include "GeneratedQuestionValidator.h"
#include "GeneratorRegistry.h"
#include "GeneratorScoring.h"
#include "QuestionHistory.h"

class QuestionGenerationEngine {
public:
    explicit QuestionGenerationEngine(std::string logFilePath);

    [[nodiscard]] std::optional<GeneratedQuestion> generateUniqueForTopic(
        int topicId, const GeneratorRegistry& registry, GeneratorScoring& scoring,
        const GeneratedQuestionValidator& validator, std::mt19937_64& randomEngine);

    [[nodiscard]] bool loadHistory(const std::string& filePath, const std::string& backupPath);
    void saveHistory(const std::string& filePath) const;

private:
    QuestionHistory history_;
    std::string logFilePath_;
};
```

- [ ] **Step 2: `src/QuestionGenerationEngine.cpp`**

```cpp
#include "QuestionGenerationEngine.h"

#include <chrono>
#include <fstream>

namespace {

constexpr int kAttemptsPerStage = 20;

std::string stageName(GenerationStage stage) {
    switch (stage) {
        case GenerationStage::Normal:
            return "Normal";
        case GenerationStage::ExpandedParameters:
            return "ExpandedParameters";
        case GenerationStage::StructuralVariation:
            return "StructuralVariation";
    }
    return "Unknown";
}

std::string currentTimestamp() {
    const auto now = std::chrono::system_clock::now();
    return std::to_string(
        std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
}

}  // namespace

QuestionGenerationEngine::QuestionGenerationEngine(std::string logFilePath)
    : logFilePath_(std::move(logFilePath)) {}

namespace {

void appendLogLine(
    const std::string& logFilePath, int topicId, const std::string& stageLabel,
    const std::string& generatorId, const std::string& result, int attempts) {
    std::ofstream logFile(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        return;
    }
    logFile << "[" << currentTimestamp() << "] topic=" << topicId << " stage=" << stageLabel
            << " generator=" << (generatorId.empty() ? "-" : generatorId) << " result=" << result
            << " attempts=" << attempts << "\n";
}

std::optional<GeneratedQuestion> tryStage(
    QuestionHistory& history, GeneratorScoring& scoring, const GeneratedQuestionValidator& validator,
    const std::vector<const IQuestionGenerator*>& generators, GenerationStage stage,
    std::mt19937_64& randomEngine, const std::string& logFilePath, int topicId) {
    const std::string stageLabel = stageName(stage);
    for (const IQuestionGenerator* generator : generators) {
        int attempts = 0;
        for (int attempt = 0; attempt < kAttemptsPerStage; ++attempt) {
            ++attempts;
            const auto candidate = generator->generate(randomEngine, stage);
            if (!candidate.has_value()) {
                scoring.recordAttempt(generator->id(), false);
                continue;
            }
            if (!validator.isValid(*candidate)) {
                scoring.recordAttempt(generator->id(), false);
                continue;
            }
            if (history.hasSeenExact(candidate->exactHash) ||
                history.hasSeenSemantic(candidate->semanticHash)) {
                scoring.recordAttempt(generator->id(), false);
                continue;
            }
            history.record(*candidate);
            scoring.recordAttempt(generator->id(), true);
            appendLogLine(
                logFilePath, topicId, stageLabel, std::string(generator->id()), "success", attempts);
            return candidate;
        }
        appendLogLine(
            logFilePath, topicId, stageLabel, std::string(generator->id()), "exhausted", attempts);
    }
    return std::nullopt;
}

}  // namespace

std::optional<GeneratedQuestion> QuestionGenerationEngine::generateUniqueForTopic(
    int topicId, const GeneratorRegistry& registry, GeneratorScoring& scoring,
    const GeneratedQuestionValidator& validator, std::mt19937_64& randomEngine) {
    const std::vector<const IQuestionGenerator*> ownGenerators = registry.generatorsForTopic(topicId);

    for (const GenerationStage stage :
         {GenerationStage::Normal, GenerationStage::ExpandedParameters,
          GenerationStage::StructuralVariation}) {
        if (const auto result = tryStage(
                history_, scoring, validator, ownGenerators, stage, randomEngine, logFilePath_,
                topicId);
            result.has_value()) {
            return result;
        }
    }

    std::vector<const IQuestionGenerator*> otherGenerators;
    for (const IQuestionGenerator* generator : registry.allGenerators()) {
        if (generator->topicId() != topicId) {
            otherGenerators.push_back(generator);
        }
    }
    std::sort(
        otherGenerators.begin(), otherGenerators.end(),
        [&scoring](const IQuestionGenerator* a, const IQuestionGenerator* b) {
            return scoring.successRate(a->id()) > scoring.successRate(b->id());
        });

    if (const auto result = tryStage(
            history_, scoring, validator, otherGenerators, GenerationStage::Normal, randomEngine,
            logFilePath_, topicId);
        result.has_value()) {
        return result;
    }

    appendLogLine(logFilePath_, topicId, "CrossTopic", "", "exhausted", 0);
    return std::nullopt;
}

bool QuestionGenerationEngine::loadHistory(const std::string& filePath, const std::string& backupPath) {
    return history_.loadFromFile(filePath, backupPath);
}

void QuestionGenerationEngine::saveHistory(const std::string& filePath) const {
    history_.saveToFile(filePath);
}
```

(Add `#include <algorithm>` for `std::sort` and `#include <vector>` as
needed — verify during compilation.)

- [ ] **Step 3: Rewrite `tests/QuestionGenerationEngineTests.cpp`**

Keep the `FixedSequenceGenerator` test double (now stage-aware per
Task 1 Step 7) but restructure tests around the new
`generateUniqueForTopic` entry point: a registry with one
always-succeeding generator for topic 1 returns on the first `Normal`
attempt; a generator that only produces duplicates through `Normal`
and `ExpandedParameters` but a fresh candidate on
`StructuralVariation` is accepted at that stage (proves escalation
actually happens); a topic with NO registered generators but at least
one OTHER topic's generator registered falls through to CrossTopic and
succeeds; complete exhaustion (every stage's every generator only
ever produces duplicates) returns `std::nullopt`; an invalid candidate
(caught by a real `GeneratedQuestionValidator`) is rejected without
being recorded into history. Use a temp log file path (e.g. via the
project's scratch/temp directory pattern already used elsewhere in
this test suite, or simply a fixed test-only filename under `data/`
cleaned up in each test) so tests don't depend on or pollute the real
`data/question_generation.log`.

- [ ] **Step 4: Build, test, commit**

```bash
git add src/QuestionGenerationEngine.h src/QuestionGenerationEngine.cpp tests/QuestionGenerationEngineTests.cpp
git commit -m "feat(generators): rewrite QuestionGenerationEngine with 4-stage escalation + dev log"
```

---

### Task 5: Fifteen new generators

**Files (per generator, 15x):**
- Create: `src/generators/<Name>.h/.cpp`
- Create: `tests/Generators<Name>Tests.cpp` (or append to a shared
  `tests/GeneratorsTests.cpp` — controller's call at implementation
  time based on which keeps the test file readable; either is
  acceptable, consistency across all 15 matters more than which one)
- Modify: `CMakeLists.txt` (register each pair)

Each generator follows the EXACT shape established in Task 1's
retrofit: a `constexpr` id string, `topicId()` returning its assigned
topic, 2-4 `ParameterDomain` members for its randomized inputs, a
`Normal`-stage code shape with a deterministically computable correct
answer, an `ExpandedParameters` response using `.expanded()` domains,
a `StructuralVariation` response (a genuine second shape where one
exists naturally, otherwise an honest reuse of `ExpandedParameters`
with a one-line comment saying so), and `exactSignature`/
`semanticSignature` construction following the existing convention
(exact = every drawn parameter; semantic = only parameters that change
the correct answer).

Design table (topicId, parameters, Normal-stage shape, correct-answer
rule — implemented directly, one generator at a time, each
independently compile-verified/tested/committed before the next):

1. **`ArithmeticOperatorPredictGenerator`** (topic 11): params
   `a ∈ [1,50]`, `b ∈ [1,20]`, `op ∈ {+,-,*}` (3-way choice via a
   `ParameterDomain{0,2}` index). Shape: `int a = A; int b = B; std::cout << (a OP b);`.
   Answer: compute `A OP B` directly. `StructuralVariation`: also
   include `/` as a 4th op choice with integer-division semantics
   (genuinely different rounding behavior worth a separate structural
   case).
2. **`ModOperatorPredictGenerator`** (topic 12): params `a ∈ [10,99]`,
   `b ∈ [2,9]`. Shape: `std::cout << (a % b);`. Answer: `A % B`.
   `StructuralVariation`: negative `a` (`[-99,-10]`) to exercise C++'s
   truncating mod sign behavior — a real, distinct, worthwhile case.
3. **`IfElsePredictGenerator`** (topic 18): params `x ∈ [-50,50]`.
   Shape: `if (x > 0) { cout << "pozitif"; } else { cout << "negatif ya da sifir"; }`.
   Answer branches on `x`'s sign. `StructuralVariation`: a 3-way
   if/else-if/else on sign (pozitif/negatif/sifir) — genuinely
   different shape.
4. **`ForLoopSumPredictGenerator`** (topic 22): params
   `n ∈ [3,10]`. Shape: `for (int i = 1; i <= n; ++i) sum += i;`.
   Answer: `n*(n+1)/2`. `StructuralVariation`: sum only even `i`
   (`i += 2` starting at 2) — different loop shape, different formula.
5. **`WhileLoopCountPredictGenerator`** (topic 23): params
   `start ∈ [1,20]`, `divisor ∈ [2,5]`. Shape: `while (start > 1) { start /= divisor; ++count; }`
   (integer division). Answer computed by literally simulating the
   loop in the generator (not a closed-form formula — this is fine,
   the generator computes it once at generation time).
   `StructuralVariation`: count iterations of `start *= 2` until
   `start >= limit` instead.
6. **`ArrayElementPredictGenerator`** (topic 31): params: a 5-element
   `int` array with each element drawn from `[0,99]`, an index
   `∈ [0,4]`. Shape: `int arr[5] = {...}; std::cout << arr[index];`.
   Answer: the drawn element at that index. `StructuralVariation`:
   predict `arr[0] + arr[4]` (first+last) instead of a single index.
7. **`VectorPushBackPredictGenerator`** (topic 34): params: count
   `∈ [2,6]` push_back calls of sequential values starting from a
   random base `∈ [1,20]`, then `.size()` or `.back()` queried.
   Answer computed directly. `StructuralVariation`: a `pop_back()`
   then query `.size()`/`.back()`.
8. **`StringConcatPredictGenerator`** (topic 37): params: two short
   words drawn from small `constexpr` string arrays (5-6 entries
   each). Shape: `std::string s = w1 + w2; std::cout << s;`. Answer:
   concatenation. `StructuralVariation`: `s.length()` instead of `s`
   itself.
9. **`FunctionReturnPredictGenerator`** (topic 43): params `a,b ∈ [1,30]`.
   Shape: a named function `int topla(int a, int b) { return a + b; }`
   called as `topla(A, B)`. Answer: `A+B`. `StructuralVariation`: a
   function with a default parameter (`int carp(int a, int b = 2)`)
   called with only one argument.
10. **`PointerDereferencePredictGenerator`** (topic 52): params
    `value ∈ [1,100]`. Shape: `int x = value; int* p = &x; std::cout << *p;`.
    Answer: `value`. `StructuralVariation`: `*p = newValue; std::cout << x;`
    (mutate through the pointer, predict the original variable).
11. **`ClassMemberPredictGenerator`** (topic 64): params `value ∈ [1,100]`.
    Shape: a minimal class with one public int member, constructed
    with `value`, member accessed and printed. Answer: `value`.
    `StructuralVariation`: two instances, print the second instance's
    member after independently setting it (proves object
    independence).
12. **`InheritanceOverridePredictGenerator`** (topic 69): fixed base/
    derived classes (no randomized parameters beyond a bool "call
    through base pointer" choice — this generator's variety comes from
    structural stage, not parameter range). `Normal`: derived class's
    own overridden method called directly. `StructuralVariation`: same
    call made through a `Base*` pointing at a `Derived` instance
    (dispatch behavior) — genuinely different and pedagogically
    valuable given this project's established virtual-dispatch
    content.
13. **`MapLookupPredictGenerator`** (topic 84): params: 3 key-value
    int pairs (keys drawn from a small fixed word list, values
    `∈ [1,50]`), plus a queried key (one of the 3, or a 4th "missing"
    key). Shape: build the map, print `m[queriedKey]`. Answer: the
    value if present, `0` (default-constructed int) if the "missing"
    key path is chosen. `StructuralVariation`: query via `.find()` and
    print `"bulundu"`/`"bulunamadi"` instead of `operator[]`.
14. **`SortWithLambdaPredictGenerator`** (topic 91): params: a 4-5
    element int vector with randomized values `∈ [1,99]`. Shape:
    `std::sort(v.begin(), v.end(), [](int a, int b){ return a > b; });`
    (descending via lambda) then print all elements. Answer: the input
    values sorted descending. `StructuralVariation`: sort ascending by
    absolute value of `(x - pivot)` for a random pivot — a genuinely
    different lambda comparator.
15. **`TryCatchPredictGenerator`** (topic 99): params: a bool "throws"
    flag and an int value. Shape: a function that either
    `throw std::runtime_error("hata")` or returns `value`, called
    inside a try/catch that prints either the caught message or the
    returned value. Answer computed directly from the bool.
    `StructuralVariation`: two sequential try/catch blocks (predict
    which one catches).

- [ ] **Step (per generator): write, compile-verify (temp CMakeLists
  addition + build), unit test, commit** — repeated 15 times, in the
  exact discipline already used throughout this entire project (every
  content phase, plus Tasks 1-4 of this phase): write the `.h`/`.cpp`
  pair and its test file, register temporarily if needed for isolated
  compilation checks, run the FULL test suite (not just the new
  file's tests) after each addition, then commit that one generator
  before moving to the next. Runtime-verify each generator's `Normal`
  AND `StructuralVariation` answer by actually compiling and running
  a standalone snippet matching its code shape wherever the answer
  isn't trivially obvious by inspection (the mod-with-negative-operand
  case, the while-loop simulation, the map-lookup-with-missing-key
  case, and the inheritance-dispatch case are the ones most likely to
  hide a real bug — matching this project's established pattern of
  every phase finding at least one thing worth double-checking).

---

### Task 6: Wire into `Application.cpp`

**Files:**
- Modify: `src/Application.h` (new members: 15 generator instances,
  1 `GeneratorRegistry`, 1 `GeneratorScoring`, 1
  `GeneratedQuestionValidator`)
- Modify: `src/Application.cpp` (constructor: register all 17
  generators; `runQuickTest()`: replace the 2-generator coin-flip with
  a call through the registry/engine; add the dev-log path constant)

- [ ] **Step 1: Add members and constructor wiring**

Add one member per new generator (matching
`intArithmeticGenerator_`'s declaration style), a `GeneratorRegistry
generatorRegistry_;`, a `GeneratorScoring generatorScoring_;`, a
`GeneratedQuestionValidator generatedQuestionValidator_;`. In the
constructor body (after existing member initialization), call
`generatorRegistry_.registerGenerator(...)` once per generator (17
calls total). Add `constexpr const char* kGenerationLogFilePath = "data/question_generation.log";`
alongside the other file-path constants, and pass it to
`QuestionGenerationEngine`'s constructor (update the member
declaration/initializer to match the new constructor signature from
Task 4).

- [ ] **Step 2: Replace `runQuickTest()`'s generator selection**

Read the current implementation at `Application.cpp:682-746` (line
numbers may have shifted after Task 4/prior edits — locate by
function name, not literal line numbers) to see the exact surrounding
loop/XP/history-save structure, and replace ONLY the per-question
generator-selection block (currently: coin-flip between 2 hardcoded
generators with manual one-shot fallback) with: draw a topic id
uniformly from the DISTINCT set of `topicId()`s across all 17
registered generators, then call
`generationEngine_.generateUniqueForTopic(pickedTopicId, generatorRegistry_, generatorScoring_, generatedQuestionValidator_, randomEngine_)`.
Keep everything else in `runQuickTest()` (XP awarding, history
save-after-each-question, early-exit handling) unchanged.

- [ ] **Step 3: Build, test, manual verification, commit**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: all tests pass.

Manually run `./build/Debug/CppMasterConsole.exe`, choose "2. Hızlı
Test" a few times across separate runs, confirm varied questions
appear (not just the original 2 generators' style), confirm
`data/question_generation.log` is created with plausible lines. Clean
up `data/*.txt` and `data/question_generation.log` afterward.

```bash
git add src/Application.h src/Application.cpp
git commit -m "feat(generators): wire GeneratorRegistry/Engine into runQuickTest"
```

---

### Task 7: Roadmap update

- [ ] **Step 1: Update `docs/superpowers/roadmap.md`**

Strike through the generator-count and engine-architecture gap bullets
with a "resolved in Phase 23" note (mirroring the format used for
every prior resolved bullet). Add a Phase 23 COMPLETE bullet under
"Phase order" (commit range: this phase's spec commit through this
task's final commit). Update "Status": Phase 23 complete, Phase 24
(Büyük ölçekli üretim testleri) starting next.

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 23 complete in roadmap"
```

---

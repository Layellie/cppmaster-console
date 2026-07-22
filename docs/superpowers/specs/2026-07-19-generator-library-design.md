# CppMaster Console — Üretici Kütüphanesi Genişletmesi Design (Phase 23)

## Context

Roadmap gap (`docs/superpowers/roadmap.md:53-62`): "Only 2 dynamic
generators exist (`IntArithmeticPredictGenerator`,
`BoolOutputPredictGenerator`); the spec asked for at least 15 across
major topic areas (arithmetic, mod, if-else, for, while, arrays,
vector, string, functions, pointer, class, inheritance, map,
sort+lambda, try-catch). The generation engine is a single flat
50-attempt retry loop; the spec asked for a 3-stage escalation (Normal
→ ExpandedParameters → StructuralVariation, then CrossTopic fallback)
plus dedicated `GeneratedQuestionValidator`, `GeneratorRegistry`,
`GeneratorScoring`, `ParameterDomain` classes and a developer log
(`data/question_generation.log`)."

Researched (read-only) existing system: `IQuestionGenerator` (2
methods: `id()`, `generate(rng)`), two concrete generators with
hand-baked parameter ranges and generator-computed
exact/semantic signature strings (hashed via FNV-1a into
`GeneratedQuestion::exactHash`/`semanticHash`), a `QuestionGenerationEngine`
that is genuinely just a flat 50-attempt loop against ONE generator
passed in by the caller (no topic routing, no registry — that logic
is manual if/else in `Application.cpp`), and `QuestionHistory` (global,
file-backed, two hash sets). This system IS live — wired into "2.
Hızlı Test" only (not topic quizzes/exams, which use the static bank).

## Design

### 1. `IQuestionGenerator` interface change (breaking, both existing
generators updated)

```cpp
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

`topicId()` lets `GeneratorRegistry` self-index generators (no separate
manual mapping table). `stage` lets one generator implementation
respond differently per escalation stage: `Normal` uses its original
parameter domain; `ExpandedParameters` uses a WIDER `ParameterDomain`
(more distinct draws → more likely to dodge a duplicate-hash reject
without changing the underlying code shape); `StructuralVariation` uses
a genuinely different code shape for the same topic (e.g., a second
predict-the-output pattern) — each generator that supports a
structural variant switches on `stage == StructuralVariation`;
generators without a natural second shape simply reuse their
`ExpandedParameters` behavior for that stage (a valid, honest fallback,
not a violation of the contract).

### 2. `ParameterDomain` (`src/ParameterDomain.h`, header-only)

```cpp
struct ParameterDomain {
    int min;
    int max;
    [[nodiscard]] int draw(std::mt19937_64& randomEngine) const;
    [[nodiscard]] ParameterDomain expanded() const;
};
```

`expanded()` returns a domain covering the ORIGINAL range plus a
symmetric extension on both ends (roughly doubling the span), giving
every generator a mechanical, consistent way to get "more room" for the
`ExpandedParameters` stage without hand-picking new bounds per
generator. Used by every new generator (and retrofitted into the 2
existing ones) instead of ad hoc `std::uniform_int_distribution` calls
with inline magic numbers.

### 3. `GeneratedQuestionValidator` (`src/GeneratedQuestionValidator.h/.cpp`)

```cpp
class GeneratedQuestionValidator {
public:
    [[nodiscard]] bool isValid(const GeneratedQuestion& candidate) const;
};
```

Real content-correctness checks the current engine never does (it only
checks duplicate hashes): prompt non-empty; `topicId` in `[1,100]`;
`baseXp > 0`; `MultipleChoice` has exactly 4 options and
`acceptedAnswers` is a single lowercase letter within `a`-`d`;
`TrueFalse` has no `options` and `acceptedAnswers` is `{"1"}` or
`{"2"}`; every other type has non-empty `acceptedAnswers`. This runs
BEFORE the duplicate-hash check in the engine (an invalid candidate is
discarded immediately, without consuming a duplicate-check or being
recorded into history).

### 4. `GeneratorRegistry` (`src/GeneratorRegistry.h/.cpp`)

```cpp
class GeneratorRegistry {
public:
    void registerGenerator(const IQuestionGenerator& generator);
    [[nodiscard]] std::vector<const IQuestionGenerator*> generatorsForTopic(int topicId) const;
    [[nodiscard]] const std::vector<const IQuestionGenerator*>& allGenerators() const;
private:
    std::vector<const IQuestionGenerator*> generators_;
};
```

Non-owning (raw pointers to generator instances owned by `Application`
as members, exactly like today's `intArithmeticGenerator_`/
`boolOutputGenerator_` pattern — just more of them). Populated once at
app startup by registering all 17 generator instances (2 existing + 15
new). Replaces `Application.cpp`'s manual two-generator coin-flip/
fallback with `generatorsForTopic(topicId)` plus, for the CrossTopic
stage, `allGenerators()` filtered to exclude the current topic's own
generators.

### 5. `GeneratorScoring` (`src/GeneratorScoring.h/.cpp`)

```cpp
class GeneratorScoring {
public:
    void recordAttempt(std::string_view generatorId, bool succeeded);
    [[nodiscard]] double successRate(std::string_view generatorId) const;  // 0.5 if never tried (neutral prior)
private:
    struct Stats { int successes = 0; int attempts = 0; };
    std::unordered_map<std::string, Stats> statsByGeneratorId_;
};
```

Tracks each generator's historical fresh-yield rate (successes ÷
attempts across the whole run). Used ONLY by the CrossTopic fallback
stage to pick which of the "other topics'" generators to try first
(highest `successRate()` first) rather than a blind coin-flip — a
modest, well-scoped reading of "scoring generators" that doesn't
require restructuring the core loop into generate-many-then-pick-best.
In-memory only for now (no persistence file — this is a per-run
heuristic, not a durable stat; adding persistence would be
unrequested scope beyond what the roadmap gap asks for).

### 6. `QuestionGenerationEngine` — 4-stage algorithm

New method (old `generateUnique(generator, rng)` single-generator
method is REMOVED — nothing outside `Application.cpp`/its tests calls
it directly once this lands, and the whole point of this phase is that
callers stop hand-picking a generator):

```cpp
std::optional<GeneratedQuestion> generateUniqueForTopic(
    int topicId, const GeneratorRegistry& registry, GeneratorScoring& scoring,
    const GeneratedQuestionValidator& validator, std::mt19937_64& randomEngine);
```

Algorithm per call:
1. **Normal**: for each generator registered to `topicId`, attempt up
   to `kAttemptsPerStage` (20) draws at `GenerationStage::Normal`;
   each draw must pass `validator.isValid` and be exact+semantic-fresh
   against `history_`; first success wins, records history, logs, and
   returns.
2. **ExpandedParameters**: same generators, same attempt budget, stage
   `ExpandedParameters`.
3. **StructuralVariation**: same generators, same attempt budget,
   stage `StructuralVariation`.
4. **CrossTopic fallback**: `registry.allGenerators()` minus the
   topic's own generators, ORDERED by `scoring.successRate()`
   descending; for each, `kAttemptsPerStage` draws at `Normal` stage
   (a cross-topic question doesn't need its own expansion/structural
   escalation — simplicity here is deliberate, not a gap).
5. If every stage is exhausted, log the final failure and return
   `std::nullopt`.

Every generator draw's outcome (success/duplicate-rejected/invalid/
generator-returned-nullopt) updates `scoring.recordAttempt(id, bool)`
and appends one line to the developer log (see below). `history_`
recording only happens on an accepted (valid + fresh) candidate,
unchanged from today.

### 7. Developer log (`data/question_generation.log`)

Plain append-only text, one line per terminal event (not literally
per micro-attempt, to keep the file readable): `stage` entry when a
stage starts, and `result` entry when a candidate is accepted or a
stage is exhausted. Format:
```
[<iso8601 UTC via std::chrono>] topic=<id> stage=<Normal|ExpandedParameters|StructuralVariation|CrossTopic> generator=<id or -> result=<success|exhausted> attempts=<n>
```
Opened in `std::ios::app` mode per write (matching the project's
existing direct-`ofstream` file-I/O style — no logging abstraction
layer exists anywhere in this codebase, and adding one would be
disproportionate to this need). The engine takes the log file path as
a constructor parameter (defaulting to the real path in
`Application.cpp`, but overridable in tests so tests don't pollute
`data/`).

### 8. Fifteen new generators (one file pair each, `src/generators/`)

One generator per roadmap-listed area, each targeting the single
best-matching existing topic (mapping researched and confirmed against
`LessonManager.cpp`'s `kTopicSeeds`):

| # | Area | Generator class | topicId | Topic title |
|---|------|-----------------|---------|-------------|
| 1 | arithmetic (operators) | `ArithmeticOperatorPredictGenerator` | 11 | Matematiksel operatörler |
| 2 | mod | `ModOperatorPredictGenerator` | 12 | % mod operatörü |
| 3 | if-else | `IfElsePredictGenerator` | 18 | if-else |
| 4 | for | `ForLoopSumPredictGenerator` | 22 | for |
| 5 | while | `WhileLoopCountPredictGenerator` | 23 | while |
| 6 | arrays | `ArrayElementPredictGenerator` | 31 | Normal diziler |
| 7 | vector | `VectorPushBackPredictGenerator` | 34 | vector |
| 8 | string | `StringConcatPredictGenerator` | 37 | string |
| 9 | functions | `FunctionReturnPredictGenerator` | 43 | Değer döndüren fonksiyon |
| 10 | pointer | `PointerDereferencePredictGenerator` | 52 | Pointer tanımlama |
| 11 | class | `ClassMemberPredictGenerator` | 64 | Sınıf ve nesne |
| 12 | inheritance | `InheritanceOverridePredictGenerator` | 69 | Kalıtım |
| 13 | map | `MapLookupPredictGenerator` | 84 | map |
| 14 | sort+lambda | `SortWithLambdaPredictGenerator` | 91 | sort() (uses a lambda comparator, satisfying "sort+lambda" as one combined generator rather than splitting across topics 51 and 91) |
| 15 | try-catch | `TryCatchPredictGenerator` | 99 | try-catch |

(Topic 6 "int" and topic 9 "bool" — the 2 EXISTING generators' topics
— are intentionally left as-is; this table is exactly the 15 NEW
areas the roadmap lists, giving 17 total generators, comfortably
≥15.)

Each new generator: 2-4 randomized `ParameterDomain`-drawn parameters,
one `Normal`-stage code shape whose output is deterministically
computable from the drawn parameters, an `ExpandedParameters` stage
reusing the same shape with `.expanded()` domains, and — where a
second natural shape exists without forcing it (e.g. `ForLoopSumPredictGenerator`
can vary "sum forward" vs "sum with a step > 1"; `IfElsePredictGenerator`
can vary which branch fires) — a real `StructuralVariation` response;
otherwise `StructuralVariation` reuses the `ExpandedParameters` domain
(honest, not a shortfall — not every topic needs a second shape to
satisfy the escalation contract, since the ATTEMPT diversity from
wider parameter draws is still real fresh-question value). Each ships
with its own `GeneratorsTests.cpp`-style test cases (determinism,
per-draw invariants, exact-vs-semantic signature content) matching the
existing two generators' test conventions exactly.

### 9. `Application.cpp` wiring

- Add 15 new generator members (matching the existing
  `intArithmeticGenerator_`/`boolOutputGenerator_` pattern).
- Construct a `GeneratorRegistry` member, `registerGenerator`-ing all
  17 in the constructor.
- Add a `GeneratorScoring` member (in-memory, constructed empty, no
  load/save — see §5).
- Add a `GeneratedQuestionValidator` member (stateless, but kept as a
  member for consistency with the rest of the app's dependency style).
- `runQuickTest()`'s per-question generator selection (currently: coin
  -flip between the 2 hardcoded generators, `Application.cpp:694-708`)
  is replaced with a single call:
  `generationEngine_.generateUniqueForTopic(pickedTopicId, registry_, scoring_, validator_, randomEngine_)`.
  `pickedTopicId` is drawn uniformly from the 17 generators' distinct
  `topicId()`s (not all 100 topics — only topics that actually HAVE a
  generator can produce a quick-test question; this matches today's
  behavior of only ever drawing from the 2 existing generators'
  topics, just widened to 17).
- The developer log path constant (`data/question_generation.log`)
  joins the existing `kProgressFilePath`-style constant block.

## Testing / verification for this phase

- Unit tests for every new class (`ParameterDomainTests.cpp`,
  `GeneratedQuestionValidatorTests.cpp`, `GeneratorRegistryTests.cpp`,
  `GeneratorScoringTests.cpp`) plus one test file per new generator
  (15 files) plus a rewritten `QuestionGenerationEngineTests.cpp`
  covering all 4 stages and the cross-topic fallback with test-double
  generators (extending the existing `FixedSequenceGenerator` pattern
  to be stage-aware).
- Manual verification: run "2. Hızlı Test" several times, confirm
  varied topics/questions appear (not just the original 2 generators'
  output), confirm `data/question_generation.log` is created and has
  plausible content, clean it (and `data/generated_question_history.txt`)
  up afterward.
- Full existing suite must stay green throughout.

## Scope cuts (deliberate)

- `GeneratorScoring` is in-memory/per-run only, not persisted — a
  durable cross-session generator-quality file is a reasonable future
  idea but not what the roadmap gap asks for.
- The dev log is a flat text file, not structured (JSON/CSV) — matches
  every other data file in this project (`progress.txt`,
  `mistakes.txt`, etc., all simple line-oriented text).
- Quick Test's topic selection stays "any topic with a registered
  generator," not extended to try ALL 100 topics via CrossTopic
  fallback on every single quick-test question — CrossTopic fallback
  only fires when a picked topic's OWN generators exhaust all 3
  escalation stages, matching the roadmap's literal ask.
- Not every new generator needs a genuinely distinct
  `StructuralVariation` shape — those without a natural second shape
  fall back to their expanded-parameter response for that stage (noted
  per-generator in its own file, not hidden).
- No change to topic quizzes / section exams / final exam — dynamic
  generation remains a Quick-Test-only feature, matching current scope.

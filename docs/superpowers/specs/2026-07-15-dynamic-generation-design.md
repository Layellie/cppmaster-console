# CppMaster Console — Dynamic Question Generation (Phase 6) Design

## Context

Sub-project 6 of the decomposition: Foundation → Static lesson + quiz core
→ Richer question types → Persistence + review loop → Meta systems →
**Dynamic generation** → polish. Phases 1-5 are complete, reviewed, and
merged. Menu option 2 ("Hızlı Test") is the last one still showing the
Foundation-era "not yet available" message.

This is the largest single section of the original product mega-spec (its
own ~30-section "C++20 ve Tekrarsız Dinamik Soru Üretim Sistemi" update).
Built to the letter, it is easily bigger than every prior phase combined:
a multi-tier generation-attempt algorithm (normal → expanded parameters →
structural variation → cross-topic), a generator-scoring/weighted-selection
system for choosing among many generators, capacity/exhaustion tracking
per generator, distractor-generation for multiple-choice, and 15+
generators across every question type. Scoped autonomously per the user's
standing instruction, recorded here for transparency.

## Goal

Build the actual mechanism the mega-spec cares about — stable fingerprinting
(exact + semantic), a generator interface, non-repetition enforced by a
persisted history, and honest exhaustion handling — with **two working
generators**, wired into "Hızlı Test." Prove the architecture works, not
recreate the full 15-generator, multi-tier system in one pass.

## Scope cuts (deliberate, not oversights)

- **Two generators, not fifteen.** `IntArithmeticPredictGenerator` (large
  parameter space: ~2,800 semantic variants) and `BoolOutputPredictGenerator`
  (intentionally tiny: exactly 2 semantic variants ever) — chosen so this
  phase demonstrates both "plenty of room to generate" and "graceful
  exhaustion," the two behaviors the history/dedup system exists to handle.
  Both target already-taught topics (`int`, `bool` — topics 6 and 9), so no
  new lesson content is needed and nothing here contradicts what the user
  has actually learned.
- **No `GenerationContext`, no generator scoring/weighting, no multi-tier
  attempt escalation (normal → expanded → structural → cross-topic).** All
  of that machinery exists in the mega-spec to choose intelligently *among
  many* generators and to widen the search when one generator's space runs
  dry. With two generators, one large and one intentionally tiny, that
  machinery would be pure ceremony with nothing real to select between. The
  engine here does one thing: given a chosen generator, retry with fresh
  random parameters until a semantically-unseen question is found or a
  attempt cap is hit — then honestly reports it has nothing fresh, rather
  than silently repeating.
- **Only `PredictOutput` questions.** Both generators produce free-text
  "what does this print" questions — no multiple-choice distractor
  generation (a whole mega-spec section on its own) needed for this
  scope. `CompleteLine`/`FindError`/etc. generators are natural follow-ups
  once this mechanism is proven, not part of this phase.
- **No C++20 `concepts` for the generator interface.** The mega-spec offers
  concepts as an option for *template-based* generators; these two
  generators use ordinary virtual-function polymorphism (`IQuestionGenerator`
  as an abstract base), which needs no concept to be sound. Concepts remain
  a reasonable idea for later, more generic generator code.
- **No difficulty-scoring formula.** Difficulty is a fixed, hand-assigned
  value per generator (`IntArithmeticPredictGenerator` → `Medium`,
  `BoolOutputPredictGenerator` → `Easy`), not derived from the mega-spec's
  multi-factor complexity score — that formula needs data (branch counts,
  nesting depth, etc.) meaningless for these two simple, flat templates.
- **Real RNG seeding breaks this project's established exact-piped-input
  verification method — deliberately, for this one feature.** Every prior
  phase's manual test used exact expected transcripts because the app's
  behavior was fully deterministic. "Hızlı Test" is the first genuinely
  non-deterministic feature (that's the whole point), seeded from
  `std::chrono` + `std::random_device` like any real shipped feature should
  be — faking determinism here (e.g., a hardcoded seed in production) would
  mean every player sees identical "random" content forever, which is
  worse than the inconvenience of writing a different kind of test for it.
  So: the pure-logic pieces (hash function, a generator driven by an
  explicitly-constructed fixed-seed engine, the history's dedup logic) are
  still verified with exact expected values, same as always. Only the
  final `Application`-level integration test for "Hızlı Test" itself checks
  structural/behavioral properties (no crash, an answer is scored, two
  separate runs produce different questions) instead of an exact transcript
  — because nothing else is honestly checkable once real randomness is
  involved.
- **Generated questions never enter `MistakeTracker`.** A `MistakeRecord`
  only stores a `questionId`; "Hatalarımı Çöz"/"Günlük Tekrar" resolve it
  back to a real `Question` via `QuestionManager::findById`, which only
  knows the 72 hand-authored questions. A wrongly-answered *generated*
  question would create a mistake record `findById` can never resolve — a
  silent, permanent "ghost" entry. Rather than build a second retrieval
  path just for ephemeral generated content, `askOneQuestion` gains one
  `bool trackMistakes = true` parameter (defaulting to today's behavior for
  every existing call site); "Hızlı Test" is the one caller that passes
  `false`. Everything else (scoring, streak, typed-correct counters,
  achievements, XP) still applies to a "Hızlı Test" answer — only the
  mistake-bookkeeping is skipped, for the concrete reason above, not as a
  blanket "generated content is second-class" policy.

## New files

```
src/FnvHash.h                     (new — constexpr FNV-1a 64-bit hash, header-only)
src/GeneratedQuestion.h           (new — data structs, header-only)
src/IQuestionGenerator.h          (new — abstract interface, header-only)
src/QuestionHistory.h / .cpp      (new — exact/semantic hash-set persistence)
src/QuestionGenerationEngine.h / .cpp  (new — retry-until-fresh-or-exhausted)
src/generators/IntArithmeticPredictGenerator.h / .cpp  (new)
src/generators/BoolOutputPredictGenerator.h / .cpp     (new)
src/Application.h / .cpp          (modified — Hızlı Test wiring, askOneQuestion's new parameter)
```

## Fingerprinting

```cpp
// FnvHash.h
constexpr std::uint64_t fnv1a64(std::string_view text) noexcept {
    constexpr std::uint64_t offsetBasis = 14695981039346656037ULL;
    constexpr std::uint64_t prime = 1099511628211ULL;
    std::uint64_t hash = offsetBasis;
    for (const unsigned char character : text) {
        hash ^= character;
        hash *= prime;
    }
    return hash;
}
```

```cpp
// GeneratedQuestion.h
struct GeneratedQuestion {
    Question question;
    std::string generatorId;
    std::string exactSignature;
    std::string semanticSignature;
    std::uint64_t exactHash;
    std::uint64_t semanticHash;
};
```

Each generator builds both signature strings itself. For
`IntArithmeticPredictGenerator`: exact = `generator=IntArithmeticPredictGenerator;var={name};start={start};op={op};operand={operand}`;
semantic = the same string **without** `var={name}` — two generations that
only differ by variable name collapse to the same semantic hash, matching
the mega-spec's own worked example exactly. For
`BoolOutputPredictGenerator`: exact includes `var={name}`; semantic is just
`generator=BoolOutputPredictGenerator;value={true|false}` — exactly 2
possible semantic hashes ever exist for this generator, by design.

## `IQuestionGenerator`

```cpp
class IQuestionGenerator {
public:
    virtual ~IQuestionGenerator() = default;
    [[nodiscard]] virtual std::string_view id() const noexcept = 0;
    [[nodiscard]] virtual std::optional<GeneratedQuestion> generate(
        std::mt19937_64& randomEngine) const = 0;
};
```

`generate` must never produce undefined behavior or an ambiguous question
for any input the random engine can produce — enforced by construction
(bounded parameter ranges chosen so every combination is safe and has one
exact computable answer), not by a separate validator class (the mega-spec's
`GeneratedQuestionValidator` is real machinery for validating *many*
generator shapes; with two generators whose entire output space is
enumerable and inherently safe, a validator would check invariants the
generators structurally cannot violate).

## `QuestionHistory`

```cpp
class QuestionHistory {
public:
    [[nodiscard]] bool hasSeenExact(std::uint64_t exactHash) const;
    [[nodiscard]] bool hasSeenSemantic(std::uint64_t semanticHash) const;
    void record(const GeneratedQuestion& generated);

    [[nodiscard]] bool loadFromFile(const std::string& filePath, const std::string& backupPath);
    void saveToFile(const std::string& filePath) const;

private:
    std::unordered_set<std::uint64_t> seenExactHashes_;
    std::unordered_set<std::uint64_t> seenSemanticHashes_;
};
```

`data/generated_question_history.txt`: lines `exact <hash>` / `semantic
<hash>`, same corruption-safe load/save convention as every other data file
in this project (any unrecognized line marks the whole file corrupt →
backup → fresh empty history; a missing file is not corruption). History
survives restarts, so a generator's already-seen semantic space stays
exhausted across sessions, exactly as the mega-spec requires.

## `QuestionGenerationEngine`

```cpp
class QuestionGenerationEngine {
public:
    explicit QuestionGenerationEngine(QuestionHistory history);

    [[nodiscard]] std::optional<GeneratedQuestion> generateUnique(
        const IQuestionGenerator& generator, std::mt19937_64& randomEngine);

    [[nodiscard]] const QuestionHistory& history() const;
    void saveHistory(const std::string& filePath) const;

private:
    QuestionHistory history_;
};
```

`generateUnique`: up to 50 attempts, each calling `generator.generate`,
rejecting a candidate whose exact **or** semantic hash was already seen,
recording and returning the first fresh one. Returns `std::nullopt` if all
50 attempts were rejected (the generator's free space — for
`BoolOutputPredictGenerator`, all 2 possible variants — is exhausted for
this history). This is the mega-spec's "Adım 6/7/8" (validate, reject,
retry) collapsed to their essential shape, without the later escalation
tiers (Adım 9/10) that only make sense with more generators to escalate to.

## `Application` wiring

`askOneQuestion` gains one parameter: `bool trackMistakes = true` (every
existing call site is source-compatible with no change; only "Hızlı Test"
passes `false`, for the ghost-mistake reason above). A new
`std::mt19937_64 randomEngine_` member, seeded once at construction from
`std::chrono::high_resolution_clock` combined with `std::random_device`
(never `rand()`/`srand()`).

`runQuickTest()` (menu option 2): asks up to 5 questions, each generated by
randomly picking one of the two generators (a coin flip on `randomEngine_`)
and calling `generateUnique`; if that generator is exhausted, falls back to
the other one before giving up on that slot entirely. If a slot produces no
question, the session ends early with an honest "bu oturumda başka taze
soru üretemedim" message rather than repeating or padding with fake
content. Each generated question is asked via `askOneQuestion(question,
/*trackMistakes=*/false)`, so it still scores, updates streak/typed
counters, feeds achievements, and awards XP through
`awardXpAndCheckLevelUp` — only mistake-bookkeeping is skipped. History is
saved after every generated-and-answered question, same "save after every
meaningful event" discipline as the rest of the project.

## Testing / verification for this phase

Same corruption-safe/backward-compatible conventions as every prior data
file for `QuestionHistory`. The hash function, both generators (driven by
an explicitly-constructed `std::mt19937_64` with a literal fixed seed, per
the mega-spec's own testing guidance), and the engine's dedup logic are all
verified with exact expected values via temporary `main.cpp` harnesses,
identical in spirit to every prior phase. The final `Application`-level
"Hızlı Test" integration test is the one exception in this whole project:
because it uses a real, wall-clock-seeded engine, its manual verification
checks structural properties (build succeeds; a full 5-question session
completes without crashing or hanging; the session's XP/score line is
internally consistent with whatever was actually answered; running the
session twice in separate processes produces two different question sets)
rather than one fixed expected transcript.

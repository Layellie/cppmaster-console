# CppMaster Console — İpucu Sistemi (Hint System) Design (Phase 10)

## Context

The original brief (section 8) asks for five in-quiz commands available while
answering any question: `ipucu` (hint, 3 escalating levels), `konu` (re-show
the topic's lesson), `ornek` (re-show an example), `gec` (skip, counts as
wrong), `cikis` (abort to main menu) — plus "İpucu kullanılması kazanılan
puanı azaltmalıdır" (using a hint reduces the XP earned), and section 17
requires "İpucu kapalı olsun" during the section exam specifically.

## Why hints are computed, not hand-authored

The `Question` struct has no per-question hint content today (72 hand-written
questions, no `hints` field). Hand-authoring 3 hints × 72 questions (216
strings) is real content work with no reuse value beyond this phase, and it
would not automatically extend to Hızlı Test's dynamically generated
questions. Instead, every hint level is **computed from data that already
exists on every `Question`/`GeneratedQuestion`** — `type`, `acceptedAnswers`,
`options`, `explanation` — so hints work identically for hand-written and
generated questions, and adding topic 11-100 content later needs no hint
authoring either. This is not a lesser version of the feature — it is a
genuinely correct, individually-relevant hint every time, computed instead of
looked up.

## The three levels

1. **Level 1 — generic strategy tip**, one fixed string per `QuestionType`
   (e.g. MultipleChoice: "Seçenekleri tek tek elemeye çalış..."). Real
   test-taking guidance, not specific to the question, matching "küçük bir
   yönlendirme."
2. **Level 2 — a computed, type-aware clue** derived from the question's own
   accepted answer(s)/options:
   - `MultipleChoice`: names one option letter that is definitely wrong (the
     first option that isn't in `acceptedAnswers`).
   - `TrueFalse`: a generic but real test-taking tip (eliminating one of two
     options would nearly hand over the answer, so this level stays generic
     for this type specifically).
   - `FillBlank`/`CompleteLine`: reveals the accepted answer's word count.
   - `PredictOutput`: if the accepted answer parses as an integer, reveals
     its sign (pozitif/negatif/sıfır); otherwise falls back to word count.
   - `FindError`/`FixCode`: reveals the first character of the corrected
     line.
   - `OrderCode`: reveals which option letter/number the correct sequence
     starts with.
   - `WriteCode`: hints are not offered for this type at all (see below).
3. **Level 3 — near-answer explanation**: returns `question.explanation`
   verbatim. This is already-authored, always-accurate content — exactly
   "cevaba çok yakın bir açıklama" without literally handing over the
   accepted-answer string.

## Scope cuts (deliberate)

- **`WriteCode` questions don't support any in-quiz command.** Their answer
  is read via `ConsoleUI::readMultilineCode()` (multi-line, terminated by
  `BITIR`), a fundamentally different input mode than the single-line
  `ipucu`/`konu`/`ornek`/`gec`/`cikis` commands this phase adds. Extending
  multi-line input to also recognize commands is a separate, larger
  UX problem this phase doesn't take on.
- **`konu`/`ornek`/`ipucu` are all disabled during the section exam**
  (`runSectionExam`), matching the brief's explicit "İpucu kapalı olsun"
  exam rule — extended to all three help-style commands for consistency,
  since none of them belong in a graded exam. `gec`/`cikis` remain available
  everywhere (they are navigation, not help).
- **No "similar example" generation.** `ornek` re-shows the topic's existing
  `syntax`/`exampleCode` (labeled honestly as "the example," not "a similar
  one" — there is only one authored example per lesson today).

## XP penalty

```
0 hints used this question -> full XP (unchanged)
1 hint used                -> 75% of earned XP
2 hints used                -> 50% of earned XP
3 hints used                -> 25% of earned XP
```
Applied only if the question is ultimately answered correctly (a wrong
answer already earns 0 XP regardless of hints used). The multiplier is
keyed off the *highest* hint level reached in that question (asking for
level 1 then level 2 costs the level-2 rate, not both added together).

## Data model / interfaces

```cpp
// src/HintProvider.h — pure function, no state, testable independent of Application
[[nodiscard]] std::string generateHint(const Question& question, int hintLevel);
```

`QuizEngine` gains one new public method, extracting logic already private
inside `evaluate` so `Application` can show "the correct answer" for a
skipped (`gec`) question without needing to submit a fake answer through
`evaluate`:
```cpp
[[nodiscard]] std::string QuizEngine::correctAnswerDisplay(const Question& question) const;
```

`AnswerResult` (in `QuizEngine.h`) gains one new field:
```cpp
bool exitRequested = false;  // only ever set by Application::askOneQuestion, never by QuizEngine::evaluate
```

## Wiring into `Application`

`askOneQuestion` gains a fourth parameter,
`bool allowHints = true` (`runSectionExam`'s call site passes `false`; the
other three call sites — `runTopicQuiz`, `runQuickTest`,
`runMistakeQuestions` — use the default `true`). Its answer-reading step
becomes a loop (for every question type except `WriteCode`, which is
unaffected — see scope cuts): read a line; if it case-sensitively equals
`ipucu`/`konu`/`ornek`/`gec`/`cikis`, handle that command and loop back to
read again (except `gec`/`cikis`, which return immediately); anything else
is treated as the real answer and breaks the loop into the existing
evaluate-and-report flow.

Every one of the 4 call sites checks `result.exitRequested` after each
`askOneQuestion` call and, if true, stops iterating and returns to the main
menu immediately (no further questions, no completion/summary message for
that partial session — the user explicitly asked to leave).

## Testing / verification for this phase

- `tests/HintProviderTests.cpp`: one test per `QuestionType`'s level-2 clue,
  using small synthetic questions built via a local `makeQuestion` helper
  (matching `tests/QuizEngineTests.cpp`'s existing pattern, not the real
  question bank — keeps the tests independent of content changes), plus a
  test confirming level 3 always equals `question.explanation` and one
  confirming levels 1/2/3 are mutually distinct for the same question.
  `WriteCode` is excluded at the `Application` call site, not inside
  `generateHint` itself, so no test asserts a `WriteCode`-specific behavior
  for the function.
- `tests/QuizEngineTests.cpp`: a case confirming `correctAnswerDisplay`
  matches what `evaluate`'s own `result.correctAnswerDisplay` produces for a
  representative type, proving the extraction didn't change behavior.
- Manual piped-transcript verification (`Application`/`ConsoleUI` stay out
  of unit-test scope): using `ipucu` three times on one question and
  confirming three different, escalating hint texts print, then answering
  correctly and confirming the awarded XP is exactly 25% (rounded down) of
  the question's `baseXp`; using `gec` and confirming the question is
  recorded as a mistake with the correct answer shown; using `cikis`
  mid-quiz and confirming an immediate return to the main menu with no
  further questions asked; confirming `ipucu` inside the section exam
  prints a "kapalı" message instead of a hint and does not advance past the
  current question; a final regression check confirming a question
  answered correctly with zero hint commands still earns full, unreduced
  XP exactly as every prior phase's transcripts expect.

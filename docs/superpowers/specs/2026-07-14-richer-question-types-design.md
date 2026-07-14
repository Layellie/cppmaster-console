# CppMaster Console — Richer Question Types (Phase 3) Design

## Context

Sub-project 3 of the decomposition established in the Foundation design doc:
Foundation → Static lesson + quiz core → **Richer question types** →
persistence/review → meta systems → dynamic generation → polish. Phases 1-2
are complete, reviewed, and merged. Phase 2 built `Question`/`QuestionManager`
(60 questions, 3 types: MultipleChoice/TrueFalse/FillBlank), a stateless
`QuizEngine`, lesson content for topics 1-10, XP tracking, and the
`Application` quiz loop.

As with phase 2, this was scoped autonomously per the user's standing
instruction to proceed without a back-and-forth Q&A, and is recorded here
for transparency.

## Goal

Add working support for six more `QuestionType` values that already exist
in `Enums.h` but have never been used: `CompleteLine`, `PredictOutput`,
`FindError`, `FixCode`, `OrderCode`, `WriteCode`. Each gets real evaluation
logic in `QuizEngine`, real rendering/input handling in `Application`, and a
small set of genuine, correct, pedagogically sound questions using topics
1-10 (no new lesson content needed — these types work perfectly well as
code-reading/code-writing exercises on topics already taught).

`Matching` and `Scenario` (the two remaining unused `QuestionType` values)
are **not** in this phase's scope — the original decomposition's phase-3
description names only the six above.

## Scope cuts (deliberate, not oversights)

- **Twelve new questions, not sixty.** Phase 2's "6 per topic × 10 topics"
  pattern doesn't repeat here. Each new type gets exactly 2 hand-authored
  questions (12 total), spread across 7 of the 10 topics wherever the type
  fits naturally (e.g. `FixCode` reusing the exact commonMistakes already
  written for `double`/`cin` in phase 2's lesson content). Depth (more
  questions per type, per topic) is a later content-expansion concern, not
  this phase's job — this phase's job is proving each type's mechanism
  works correctly.
- **No new `Question` fields.** All six types reuse the existing struct:
  `options` doubles as `OrderCode`'s shuffled-line list, `acceptedAnswers`
  doubles as `OrderCode`'s canonical order string and as `WriteCode`'s list
  of required substrings. This was checked against every type's actual
  needs before committing to it — see "Data model" below.
- **Code-answer matching is case-sensitive and whitespace-normalized, not
  semantically aware.** The product spec dreams of accepting "mantıksal
  olarak eşdeğer kodlar" (logically equivalent code) — e.g. `i++` and
  `i = i + 1` as interchangeable. Actually detecting semantic equivalence
  would require a small C++ parser, which is out of scope for any phase,
  not just this one. Instead: each question authors multiple literal
  `acceptedAnswers` for the formatting variants that are actually likely
  (e.g. `"toplam + 5"` and `"toplam+5"`), and matching trims + collapses
  internal whitespace runs to a single space before comparing — tolerant of
  spacing, not of rewording. This is the same honest, non-fake tradeoff
  phase 2 made for answer matching generally.
- **`WriteCode` is a structural checker, not a compiler.** Per the product
  spec's own instruction ("kullanıcının kodunu otomatik şekilde çalıştırma
  ... metinsel ve yapısal değerlendirme yap"), a `WriteCode` answer is
  correct when (a) every required substring in `acceptedAnswers` appears
  literally in the submission, and (b) parentheses and braces are balanced.
  No compilation, no execution, no partial credit — pass/fail on those two
  checks. A full program wrapper (`int main() { ... }`) is *not* required;
  a bare snippet containing the required elements passes, matching the
  spec's own tolerance for "gereksiz fakat hatasız satırlar."
- **`OrderCode` is exact-match only.** The canonical order is a single
  accepted string (e.g. `"2 3 1"`); no partial credit for a mostly-right
  ordering.
- **`WriteCode` input needs multi-line entry.** `ConsoleUI` gains one new
  method, `readMultilineCode()`, reading lines until the user types
  `BITIR` (matching the product spec's exact convention), joined with `\n`.
  Every other new type reuses the existing `readLine`/`readMenuChoice` —
  their answers are single lines (a corrected line, a predicted output, an
  order string).

## Data model — no changes to `Question` or `Enums.h`

Confirmed each new type's needs map onto existing fields:

| Type | `options` | `acceptedAnswers` | `explanation` |
|---|---|---|---|
| `CompleteLine` | unused (empty) | accepted completions (1+, formatting variants) | as before |
| `PredictOutput` | unused (empty) | accepted output string(s) | as before |
| `FindError` | unused (empty) | accepted corrected line(s) | as before |
| `FixCode` | unused (empty) | accepted corrected line(s) | as before |
| `OrderCode` | shuffled lines, displayed numbered 1..N | the one canonical order, e.g. `"2 3 1"` | as before |
| `WriteCode` | unused (empty) | **all** required substrings (AND, not OR) | as before |

## `QuizEngine` changes

`evaluate` is restructured around a `switch (question.type)`, but
**MultipleChoice/TrueFalse/FillBlank keep their exact phase-2 behavior** —
same `trimAndLower`-based comparison, same `correctAnswerDisplayFor` call.
The switch is a refactor of dispatch, not a behavior change, for those three
types; this needs explicit reviewer attention since "refactor claims to
preserve behavior" is exactly the kind of claim that needs verifying, not
trusting.

New per-type logic:

- **`CompleteLine`/`PredictOutput`/`FindError`/`FixCode`**: match if the
  trimmed, whitespace-collapsed (internal runs → single space) answer
  equals any trimmed/collapsed entry in `acceptedAnswers` — **case
  preserved** (unlike phase 2's ASCII-lowercase ANY-match, because these
  answers are real C++ syntax where case matters). Display-on-wrong is
  `acceptedAnswers.front()`.
- **`OrderCode`**: extract the digit-runs from the answer (splitting on any
  non-digit separator — space, comma, dash, whatever the user typed) and
  join with single spaces; match against the same extraction applied to
  `acceptedAnswers`. Display-on-wrong is `acceptedAnswers.front()` (the
  canonical order string).
- **`WriteCode`**: correct only if (1) every entry in `acceptedAnswers`
  appears as a literal substring somewhere in the raw multi-line answer,
  AND (2) parentheses and braces in the answer are balanced (simple
  stack-depth check, no other bracket types tracked). Display-on-wrong (there
  is no single "correct answer") is a synthesized list: `"Gerekli öğeler: "`
  followed by the comma-joined `acceptedAnswers` — telling the user what was
  required, not what to have typed verbatim.

XP stays exactly as phase 2 defined it: `question.baseXp` on correct, `0` on
incorrect — no new XP mechanism. `WriteCode` questions are authored with
`baseXp = 40` directly (matching the product spec's explicit "Kod yazma
sorusu: +40 XP" line, which is a flat value, not difficulty-derived); their
`difficulty` field is set to `Hard` as descriptive metadata only, consistent
with how every other question's `baseXp` is already hand-authored rather
than computed from `difficulty` at evaluation time.

## `ConsoleUI` addition

```cpp
std::string readMultilineCode();
```

Reads lines via `std::getline` until one exactly equals `"BITIR"` or EOF is
reached (whichever first — EOF returns whatever was collected so far,
consistent with this project's "never hang on EOF" rule established in
Foundation), joining collected lines with `'\n'`.

## `Application` changes

`runTopicQuiz`'s per-question rendering gains two new branches (alongside
the existing MultipleChoice-lettering and TrueFalse-fixed-options
branches): `OrderCode` prints each `options[i]` prefixed with `i+1` and a
prompt for the order string; everything else with a non-empty `options`
falls through unchanged. Input selection: `WriteCode` prints a short "type
BITIR to finish" instruction and reads via the new `readMultilineCode()`;
every other type (including the four new single-line types, which need no
extra rendering — their code-with-a-blank is already embedded in `prompt`)
reads via the existing `readLine("Cevabınız: ")`.

No changes to XP display, status-marking logic, or the 70%-pass threshold —
phase 2's scoring flow already works generically over however many
questions `QuestionManager::questionsForTopic` returns, so topics gaining
extra questions (some of the 10 topics go from 6 to 7 or 8) needs no
`Application` change at all.

## New question content (12 total, ids 61-72)

| id | topic | type | difficulty | baseXp |
|---|---|---|---|---|
| 61 | 6 (int) | CompleteLine | Easy | 10 |
| 62 | 4 (cin) | CompleteLine | Medium | 20 |
| 63 | 6 (int) | PredictOutput | Easy | 10 |
| 64 | 9 (bool) | PredictOutput | Medium | 20 |
| 65 | 1 (cout) | FindError | Easy | 10 |
| 66 | 8 (char) | FindError | Medium | 20 |
| 67 | 7 (double) | FixCode | Medium | 20 |
| 68 | 4 (cin) | FixCode | Medium | 20 |
| 69 | 4 (cin) | OrderCode | Easy | 10 |
| 70 | 1 (cout) | OrderCode | Medium | 20 |
| 71 | 6 (int) | WriteCode | Hard | 40 |
| 72 | 10 (const) | WriteCode | Hard | 40 |

Exact prompts/answers/explanations are in the implementation plan (writing
them twice would risk them drifting out of sync). Several deliberately
reuse a commonMistake already authored in phase 2's lesson content (id 66
mirrors `char`'s quote-type mistake, id 67 mirrors `double`'s decimal-comma
mistake, id 68 mirrors `cin`'s `>>` mistake) so the quiz reinforces the
lesson the user already read, rather than testing an unrelated fact.

## Testing / verification for this phase

Same approach as phases 1-2 — no test framework yet. `QuizEngine`'s new
logic is verified via a temporary `main.cpp` harness constructing sample
`Question` values directly (not dependent on `QuestionManager`'s real
content, so this task doesn't need to wait on the content-authoring task).
The full `Application` flow is verified by piping one complete quiz session
per new type into the built executable and checking output against a
hand-traced expected script, the same technique used throughout phases 1-2.

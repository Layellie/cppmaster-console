# CppMaster Console — Static Lesson + Quiz Core (Phase 2) Design

## Context

This is sub-project 2 of the decomposition established in
`2026-07-14-foundation-phase-design.md`: Foundation → **Static lesson + quiz
core** → richer question types → persistence/review → meta systems →
dynamic generation → polish. Foundation (CMake, `ConsoleUI`,
`LessonManager`/`Lesson` with the full 100-topic catalog, `UserProgress`,
`Application` main menu) is complete and merged to `master`.

The user asked to proceed autonomously through scoping and implementation,
so this document records the scoping decisions made without a back-and-forth
Q&A, for transparency and so later phases can see the reasoning.

## Goal

Turn "Konuları Öğren" from a browse-only list into a real learning loop for
the first 10 topics (Bölüm 1: `cout`, `\n`, `endl`, `cin`, `getline()`,
`int`, `double`, `char`, `bool`, `const`): show real lesson content, then a
real quiz (multiple choice, true/false, fill-in-the-blank), then update XP
and topic status based on the result. Topics 11-100 keep Foundation's honest
"content not yet added" behavior — this phase does not touch them.

## Scope cuts (deliberate, not oversights)

- **Only 3 question types**: MultipleChoice, TrueFalse, FillBlank. The
  richer types (code completion, predict-output, find-error, write-code,
  etc.) are explicitly phase 3 in the decomposition.
- **No mini-question / application-question as separate stages.** The
  product spec's 8-stage lesson flow (explanation → syntax → example → line
  explanations → mistakes → mini quiz → application question → topic test)
  collapses here to: read the 5 content stages, then take one topic test.
  A separate "mini question" and "application question" are just the same
  question mechanism at an earlier point — not worth a distinct code path
  for 10 topics. Full staging can be reconsidered once content authoring
  scales to all 100 topics.
- **No hints, no adaptive difficulty, no streak bonuses.** The hint system
  (spec §8) and streak-based XP bonuses (spec §11) depend on state and UI
  this phase doesn't need yet; they land with the richer-question-types and
  meta-systems phases.
- **Topic completion is single-attempt, not cumulative.** The product spec's
  full completion rule ("≥5 questions solved *cumulatively*, ≥70% success
  rate") requires historical per-topic stats this phase doesn't persist yet.
  Here, completion is decided by one topic-test attempt: 6 questions asked,
  ≥70% correct (≥5/6) marks the topic `Completed`, otherwise `Learning`.
  Retaking a topic simply re-evaluates from the new attempt — no history is
  kept (consistent with `UserProgress` staying in-memory-only until the
  persistence phase). "Mastered" stays unreachable until that phase adds the
  streak/repeat-attempt tracking it requires.
- **XP has no bonuses, no levels/titles.** Just `basdifficulty → XP` on a
  correct answer, 0 on a wrong one, added to a running total. The 10-level
  naming/celebration system (spec §11) is a meta-systems-phase concern.
- **Answer matching stays ASCII-only by design.** Multiple-choice answers
  are a single letter (A-D); true/false answers are the digit shown (`1` or
  `2`) — not the words "Doğru"/"Yanlış" — specifically so comparison never
  needs Turkish-aware case folding (`İ`/`I`/`ı`/`i` are notoriously
  ambiguous under naive `tolower`). Fill-blank answers in this phase are all
  C++ keywords/identifiers (`cout`, `endl`, `int`, ...), which are ASCII, so
  plain ASCII lowercasing is correct and sufficient. Turkish is used freely
  in prompts, explanations, and lesson text — just never in the string
  being compared for correctness.

## New/changed files

```
src/Question.h                 (new — data struct, header-only like Lesson)
src/QuestionManager.h / .cpp    (new — owns the question bank, lookup by topic)
src/QuizEngine.h / .cpp         (new — answer evaluation + XP calculation)
src/LessonManager.cpp           (modified — populate content for topics 1-10)
src/UserProgress.h / .cpp       (modified — add XP tracking)
src/Application.h / .cpp        (modified — real topic-open/quiz flow)
```

## Data model

### `Question` (header-only struct, `src/Question.h`)

Trimmed from the product spec's full `Question` schema to only the fields
this phase's 3 question types actually use — `topicName` is dropped (`Lesson`
already owns topic titles; storing it twice would violate DRY), `hints` and
`exampleAnswer` are dropped (they belong to the hint system and to
`WriteCode`, neither built yet):

```cpp
struct Question {
    int id;
    int topicId;
    QuestionType type;
    Difficulty difficulty;
    std::string prompt;
    std::vector<std::string> options;         // MultipleChoice only; empty for TrueFalse/FillBlank
    std::vector<std::string> acceptedAnswers;  // normalized (trimmed, ASCII-lowercased) accepted answer(s)
    std::string explanation;
    int baseXp;
};
```

### `QuestionManager`

Owns a hardcoded seed of 60 questions (6 per topic × 10 topics: 2 MC + 2 TF
+ 2 FillBlank each), built in the constructor the same way `LessonManager`
built its 100-topic catalog.

```cpp
class QuestionManager {
public:
    QuestionManager();
    [[nodiscard]] std::vector<Question> questionsForTopic(int topicId) const;
private:
    std::vector<Question> questions_;
};
```

### `QuizEngine`

Stateless answer evaluator — scoped down from the product spec's full
`QuizEngine` responsibilities (question selection, streak tracking,
difficulty adaptation, mistake recording all belong to later phases; this
phase only needs evaluation + XP).

```cpp
struct AnswerResult {
    bool correct;
    int xpAwarded;
    std::string correctAnswerDisplay;  // for the wrong-answer feedback message
};

class QuizEngine {
public:
    [[nodiscard]] AnswerResult evaluate(const Question& question, const std::string& rawAnswer) const;
};
```

`evaluate` normalizes `rawAnswer` (trim + ASCII-lowercase) and checks it
against the question's (already-normalized) `acceptedAnswers`. On a correct
answer it returns the question's own `baseXp` field unchanged; on a wrong
answer it returns 0. `QuizEngine` itself has no difficulty→XP table — that
mapping is applied once, when `QuestionManager` authors each question's
`baseXp` from its `difficulty` (VeryEasy=5, Easy=10, Medium=20, Hard=30,
VeryHard=50 — the product spec gives Easy through VeryHard exactly this way;
VeryEasy isn't specified there, so 5, half of Easy, is this phase's reasoned
default). Keeping the mapping in one place (data, not evaluation logic)
avoids the two ever disagreeing.

### `UserProgress` addition

```cpp
[[nodiscard]] int totalXp() const;
void addXp(int amount);
```
(plus a new `int totalXp_ = 0;` private member). `statusOf`/`setStatus` are
unchanged from Foundation.

## Application flow changes

`showTopicBrowser()` gains a prompt after listing the catalog: "Görüntülemek
istediğiniz konu numarasını girin (0 = ana menüye dön):", read via the
existing `ui_.readMenuChoice(0, 100)` (no `ConsoleUI` changes needed — this
reuses Task 4's method as-is). Choosing `0` returns to the main menu;
choosing 1-100 opens that topic via a new `openTopic(int topicId)`.

`openTopic`:
- Looks up the `Lesson` via `lessons_.findById(topicId)` (always present,
  1-100 are all valid ids from Foundation's catalog).
- If `lesson.explanation.empty()` (true for ids 11-100 — untouched by this
  phase), print the honest "bu konu için ders içeriği bu sürümde henüz
  eklenmedi" message and return to the browser.
- Otherwise (ids 1-10): print the explanation, syntax, example code, each
  line explanation, and each common mistake, then call `runTopicQuiz(topicId)`.

`runTopicQuiz(int topicId)`:
- Fetches the topic's 6 questions from `QuestionManager`.
- For each: prints the prompt (plus lettered options for MultipleChoice, or
  the fixed "1. Doğru / 2. Yanlış" for TrueFalse), reads the raw answer via
  `ui_.readLine("Cevabınız: ")` (free-text — a fixed numeric range doesn't
  fit MultipleChoice's letter input), evaluates via `QuizEngine::evaluate`,
  and prints either a correct-with-XP line or the product spec's wrong-answer
  format (your answer / correct answer / explanation).
- After all 6: prints the score (correct/6, percentage, XP earned this
  session), calls `progress_.addXp(sessionXp)`, and marks the topic
  `Completed` (≥70%) or `Learning` (<70%) via `progress_.setStatus`.
- Prints the resulting status change so the user sees it reflected next time
  they open the topic browser (where the `[ ]`/`[-]`/`[+]` marker already
  renders from Foundation).

Main-menu options 2-10 are untouched (still honest "not yet available").

## Testing / verification for this phase

Same approach as Foundation — no test framework yet (still explicitly
deferred). `QuizEngine` and `QuestionManager` are pure-logic pieces verified
via a temporary `main.cpp` harness with printed expected-vs-actual output
(same technique used for `LessonManager`/`UserProgress` in Foundation); the
full `Application` flow is verified by piping a complete topic-quiz session
(including at least one deliberately wrong answer, to exercise the
wrong-answer feedback path) into the built executable and checking the
output against the expected script.

# CppMaster Console — Adaptif Zorluk Sistemi (Adaptive Difficulty) Design (Phase 12)

## Context

The original brief (section 10) asks for topic quizzes to order questions
easy-to-hard, escalate difficulty on a correct streak, and respond to a
wrong streak with easier questions, more hints, and a topic-summary
re-display. `Question` already carries a `Difficulty` field (unused for
ordering); `runTopicQuiz` currently just asks questions in whatever order
`QuestionManager::questionsForTopic` happens to return them (hand-authoring
order, not difficulty order).

## Deliberate, documented behavior change — read before implementing

Sorting topic 1's 8 questions by ascending difficulty **changes their
order** from every prior phase's regression transcript
(`1,2,3,4,5,6,65,70` → `3,1,70,6,2,65,5,4` when every answer is correct,
because of the streak-driven reordering described below — `3,1,4,5,65,2,6,70`
is only the intermediate difficulty-sorted order before streak-jumps are
applied). **This is
intentional, unavoidable, and correctly implements "kolaydan zora doğru
gelsin"** — the old order was never actually difficulty-sorted (it mixes
Easy/Medium/VeryEasy by hand-authoring convenience, not intent). The
**final summary output is unaffected**: `awardXpAndCheckLevelUp` still runs
once after the whole quiz, so `Sonuç: 8/8 doğru (%100), kazanılan XP: 105`
and the level-2 celebration still appear identically, in the same place,
with the same values — only the per-question order in the middle changes.
This phase's own manual verification uses the new, traced-by-hand order as
the updated canonical transcript; future phases should use this new order
as their reference, matching how Phase 9 updated the canonical topic-1
transcript once for its own necessary, documented change.

## Design

A new pure-logic header, `src/AdaptiveDifficulty.h` (matching the
established `TopicLock.h`/`HintProvider.h` pattern):

```cpp
[[nodiscard]] std::size_t selectNextQuestionIndex(
    const std::vector<Question>& remaining, int correctStreak, int wrongStreak);

[[nodiscard]] bool shouldShowExtraHelp(int wrongStreak);
```

- `remaining` is assumed sorted ascending by `difficulty` once, at quiz
  start (the caller's job, not this function's).
- `selectNextQuestionIndex`: if `correctStreak >= 2` and more than one
  question remains, jump to the **last** (hardest-remaining) index —
  concretely implementing "art arda doğru → zorluk artsın." Otherwise,
  return index `0` (the next-easiest remaining question) — this is also
  what naturally happens after a wrong answer, concretely implementing
  "art arda yanlış → zorluk düşürülsün" (there is nothing lower to drop
  to beyond "stay on the easy end of what's left," which is exactly what
  index 0 already means once the list is difficulty-sorted).
- `shouldShowExtraHelp`: `wrongStreak >= 2`. `Application` resets its own
  local `wrongStreak` to `0` immediately after acting on this, so it fires
  again only after two more consecutive misses.

## Wiring into `Application::runTopicQuiz`

1. Fetch the topic's questions, `std::sort` by ascending `difficulty`
   once (stable order for ties, preserving the original within-tier
   relative order).
2. Track two **local** counters (`correctStreak`, `wrongStreak`) separate
   from `UserProgress`'s own global streak — these drive only in-quiz
   question selection and help-triggering, nothing persisted.
3. Loop while questions remain: pick the next index via
   `selectNextQuestionIndex`; if `shouldShowExtraHelp(wrongStreak)`,
   re-print the topic's lesson explanation and one level-1 hint
   (`generateHint(question, 1)`, from Phase 10 — shown for free, no XP
   penalty, since this is system-initiated help, not a user-requested
   `ipucu`) for the question about to be asked, then reset
   `wrongStreak = 0`; remove the chosen question from `remaining`; ask it
   via the existing `askOneQuestion` (unchanged); update the local streaks
   from the result.
4. Everything after the loop (XP awarding, level-up check, topic
   completion/learning status, save) is unchanged from today.

## Scope cuts (deliberate)

- **No new question content ("benzer fakat daha kolay bir soru").** The
  hand-authored bank per topic is small (6-8 questions); "ask a similar
  but easier question" is approximated by "the easiest question still
  remaining in the bank" rather than generating a new one on the fly —
  consistent with every other phase's stance that dynamic generation is
  its own, separate, much larger subsystem (Phases 6, 23-24).
- **`runQuickTest`/`runSectionExam`/`runMistakeQuestions` are unaffected.**
  Adaptive ordering only applies to a single topic's own quiz
  (`runTopicQuiz`), where "starting a topic, easy to hard" is the brief's
  stated scenario. The exam explicitly forbids adaptivity of any kind
  ("Sorular geri alınamasın," already interpreted in Phase 10 as disabling
  help commands too); quick tests and mistake review already have their
  own selection logic unrelated to a single topic's authored difficulty
  curve.

## Testing / verification for this phase

- `tests/AdaptiveDifficultyTests.cpp`: `selectNextQuestionIndex` boundary
  cases (fewer than 2 correct → index 0; 2+ correct with 1 remaining →
  index 0, since there's nothing to jump to; 2+ correct with 2+ remaining
  → last index); `shouldShowExtraHelp` boundary (false at 0/1, true at 2+).
- Manual piped-transcript verification: the updated topic-1 transcript
  (new order, traced by hand against the real question bank, confirming
  the exact new per-question sequence and unchanged final summary), and a
  short transcript deliberately answering wrong twice in a row to confirm
  the topic-summary-plus-hint re-display fires exactly once at the right
  point and doesn't fire again until two more consecutive misses.

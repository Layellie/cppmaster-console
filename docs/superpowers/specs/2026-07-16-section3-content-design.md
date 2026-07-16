# CppMaster Console — Bölüm 3 İçerik Genişletmesi Design (Phase 14)

## Context

Second of nine section-by-section content phases (13-21) closing the
roadmap's lesson-content and question-bank gaps for topics 11-100.
This phase covers Section 3 (topics 21-30: "Seçim ve döngüler" — switch-case
and all loop constructs), following the exact same architecture, scope
decisions, and testing approach established and merged in Phase 13
(commits `6df525f..cf6b6f1`), which this document does not repeat in full.

## Topics covered (Section 3, sectionId 3, from `LessonManager.cpp`'s
`kTopicSeeds`)

21. switch-case
22. for
23. while
24. do-while
25. break
26. continue
27. İç içe döngüler (nested loops)
28. Range-based for
29. 1'den N'e kadar toplama (summing 1..N)
30. Faktöriyel hesaplama (factorial)

## Design (identical architecture to Phase 13)

- **Lesson content**: a new `applySection3LessonContent(std::vector<Lesson>&)`
  function in a new file `src/LessonContentSection3.cpp`, declared in
  `src/LessonContent.h` alongside Phase 13's `applySection2LessonContent`
  declaration, called from `LessonManager`'s constructor after the Phase 13
  call. Writes into `lessons[20]` through `lessons[29]` (topics 21-30),
  same positional-index convention.
- **Question content**: a new `appendSection3Questions(std::vector<Question>&)`
  function in a new file `src/QuestionsSection3.cpp`, declared in
  `src/QuestionContent.h` alongside Phase 13's `appendSection2Questions`
  declaration, called from `QuestionManager`'s constructor after the Phase
  13 call. Ids 363-652 (10 topics × 29 questions), sequential, continuing
  directly from Phase 13's last id (362).
- **Same fixed per-topic type/difficulty/baseXp distribution table** as
  Phase 13 (8 MultipleChoice, 6 TrueFalse, 6 FillBlank, 2 CompleteLine,
  2 PredictOutput, 2 FindError, 1 FixCode, 1 OrderCode, 1 WriteCode;
  baseXp 5/10/20/30/40 for VeryEasy/Easy/Medium/Hard/Hard-WriteCode) — kept
  identical across every content phase so the question bank has a
  consistent difficulty/reward curve regardless of topic.
- **No `Application.cpp` changes needed** — same reasoning as Phase 13:
  `openTopic`/`runTopicQuiz` already activate any topic generically once
  it has non-empty lesson content and at least one question.
- **`questions_.reserve(362)` becomes `questions_.reserve(652)`** in
  `QuestionManager.cpp` (72 + 290 + 290).

## Content-accuracy notes specific to this section

Loop constructs introduce two correctness areas Section 2 didn't have,
which the plan's authored content must get right:
- **`break`/`continue` scope**: both apply to the *innermost* enclosing
  loop (or `switch` for `break`) only — a nested-loop question must not
  imply `break` exits both loops at once.
- **`do-while`'s guaranteed-first-execution property**: unlike `while`,
  the body runs at least once even if the condition is false from the
  start; at least one question per topic 24 must exercise this
  distinction directly (e.g., a loop that would never run under `while`
  but runs exactly once under `do-while`).
- **Range-based `for`'s reference vs. value semantics**: `for (int& x : v)`
  mutates the container, `for (int x : v)` does not — at least one
  topic-28 question must cover this distinction, since it's the single
  most common beginner mistake with range-based for.

## Testing / verification for this phase

Same pattern as Phase 13:
- `tests/LessonManagerTests.cpp`: extend the topics-with-content range to
  11-30 and narrow the no-content range to 31-100 (replacing, not
  duplicating, Phase 13's own two tests — there should still be exactly
  one "has content" test and one "has no content yet" test after this
  phase, each covering the correct cumulative range).
- `tests/QuestionManagerTests.cpp`: add
  `QuestionManager_EveryTopicTwentyOneToThirtyHasAtLeastTwentyNineQuestions`,
  mirroring Phase 13's equivalent test. The existing
  `QuestionManager_NoDuplicateQuestionIds` already scans topics 1-100 (Phase
  13 widened it), so no further change is needed there.
- Manual verification: open topic 22 ("for") end-to-end (lesson displays,
  29-question quiz runs, adaptive difficulty engages, XP/level updates),
  confirming content-only activation again requires zero `Application.cpp`
  changes.

## Scope cuts (deliberate, same as Phase 13)

- No dynamic-generator wiring, no Section 3 exam, Section 1/2's question
  density is not revisited.

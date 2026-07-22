# CppMaster Console — Sınavlar (Section Exams + General Final Exam) Design (Phase 22)

## Context

With Phase 21 complete, all 100 topics now have full lesson content and
a ≥29-question bank. This phase closes two remaining roadmap gaps:
"Only one section exam exists (Section 1's fixed 20-question exam); the
spec asked for one per section (10 total) plus a 100-question general
final exam covering all topics."

Unlike Phases 13-21 (pure content authoring), this phase is
architecture work: it generalizes an existing single-section-only
mechanism (`Application::runSectionExam()`, hardcoded to Section 1 via
`kExamQuestionIds`/`kExamSectionId` in `src/Application.cpp:35-43`) to
work for all 10 sections, and adds a new 100-question final exam.

Researched existing behavior (read-only investigation, not guessed):
- Section 1's exam is a fixed, hand-curated 20-id array
  (`kExamQuestionIds`), unevenly covering only 6 of Section 1's 10
  topics.
- `runSectionExam()` (`src/Application.cpp:754-833`): gates on a
  70%-topic-completion ratio via `sectionExamIsUnlocked` (from
  `src/TopicLock.h`, already generic), asks each exam question via the
  same `askOneQuestion` used for regular quizzes (hints disabled),
  scores against a 70% pass threshold, calls
  `progress_.recordSectionExamPassed(sectionId)` on pass (already
  generic — takes a sectionId), and unlocks `AchievementId::PerfectExam`
  on a perfect score.
- `UserProgress` only tracks the single highest section-exam-passed
  (`highestSectionExamPassed_`, an int), not a per-section boolean set.
  This is intentional pre-existing behavior (Phase 9) — advisory-only,
  no topic access is ever blocked. Phase 22 does not change this data
  model.
- No general final exam scaffolding exists anywhere.
- `tests/QuestionManagerTests.cpp:8-24` keeps its OWN duplicated copy
  of `kExamQuestionIds` with a comment explicitly flagging the
  duplication risk ("will NOT notice if the real kExamQuestionIds
  itself is edited"). This phase fixes that by making the real list
  importable and testable directly.

## Design

### 1. New file: `src/ExamContent.h` / `src/ExamContent.cpp`

Two free functions (matching the existing free-function style of
`src/TopicLock.h`, `src/AdaptiveDifficulty.h` — no new class needed):

```cpp
std::vector<int> examQuestionIdsForSection(int sectionId);
std::vector<int> finalExamQuestionIds();
```

**`examQuestionIdsForSection(sectionId)`** (sectionId 1-10) returns 20
question ids:
- **Section 1**: returns the EXACT existing curated array
  (`{1, 2, 3, 4, 5, 6, 19, 20, 33, 35, 61, 62, 63, 64, 65, 66, 67, 68,
  69, 71}`), moved here verbatim — Section 1's exam behavior is
  UNCHANGED by this phase.
- **Sections 2-10**: computed, not hand-curated. For each of the
  section's 10 topics (topic T in `[(sectionId-1)*10+1,
  sectionId*10]`), include 2 ids: the topic's first Medium-difficulty
  MultipleChoice question and its first Medium-difficulty TrueFalse
  question. Every content phase (13-21) used the IDENTICAL fixed
  per-topic layout (8 MultipleChoice at offsets 0-7 with difficulties
  VeryEasy/Easy/Easy/Medium/Medium/Medium/Hard/Hard, 6 TrueFalse at
  offsets 8-13 with VeryEasy/VeryEasy/Easy/Easy/Medium/Medium, ...),
  confirmed by direct inspection of the committed source across
  multiple different phases (Section 2, Section 5, Section 7, Section
  10 all checked) — so for topic T (11 ≤ T ≤ 100), the topic's base id
  is `73 + (T - 11) * 29`, and the 2 exam ids are `base + 3` (Medium
  MC) and `base + 12` (Medium TF). This is a closed-form formula, not
  180 hardcoded ids — self-documenting and error-proof compared to
  manual curation, and (unlike Section 1's exam) gives EVEN coverage of
  all 10 topics per section.

**`finalExamQuestionIds()`** returns 100 ids, one per topic 1-100:
- Topics 1-10: `{1, 7, 13, 19, 25, 31, 37, 43, 49, 55}` — the first id
  of each topic's existing 6-question block in
  `src/QuestionManager.cpp` (ids 1-60).
- Topics 11-100: `base + 3` (the same Medium-MultipleChoice pick used
  for section exams) for each topic, using the same base-id formula.

Both functions are pure and side-effect-free — no `Question.h`/
`QuestionManager.h` dependency needed for generation (only for
*looking up* the actual questions at use time, which stays in
`Application.cpp` exactly as today via `questions_.findById(id)`).

### 2. `Application.cpp` / `Application.h` changes

- Remove `kExamQuestionIds`, `kExamQuestionCount`, `kExamSectionId`,
  `kExamSectionTopicCount` (now computed, not fixed constants). Keep
  `kExamPassThreshold` (0.7) and `kSectionCompletionGateThreshold`
  (0.7) — shared by section exams AND the final exam.
- `void runSectionExam();` → `void runSectionExam(int sectionId);`
  Generalizes the existing body: `lessons_.lessonsInSection(sectionId)`
  (already parameterized), `examQuestionIdsForSection(sectionId)`
  instead of the fixed array, header text uses `sectionId` instead of
  a hardcoded "BÖLÜM 1", `progress_.recordSectionExamPassed(sectionId)`
  (already generic). Gate/scoring/XP/achievement logic is otherwise
  IDENTICAL to today's behavior.
- New `void runFinalExam();`: same shape as `runSectionExam`, but
  gates on completion ratio across ALL 100 topics
  (`lessons_.allLessons()`, ≥70% Completed/Mastered) rather than one
  section, uses `finalExamQuestionIds()`, and does NOT call
  `recordSectionExamPassed` (there is no "section 11" — this is
  intentionally out of scope for the existing per-section tracking
  model, which Phase 22 does not extend). Still unlocks
  `AchievementId::PerfectExam` on a perfect 100/100, since that
  achievement's own text is being generalized (see below) to cover any
  exam, not just section exams.
- New `void showExamMenu()`: lists all 10 sections ("Bölüm N Sınavı: Title")
  plus an (N+1)th option "Genel Final Sınavı" and "0. Geri dön",
  mirroring `showTopicBrowser`'s existing list-then-pick pattern. Choice
  1-10 calls `runSectionExam(choice)`; choice 11 calls `runFinalExam()`;
  choice 0 returns.
- `handleChoice`'s `case 6:` calls `showExamMenu()` instead of calling
  `runSectionExam()` directly. Main menu label ("6. Seviye Sınavı")
  and `kMinChoice`/`kMaxChoice` (0-10) are UNCHANGED — the new picker
  lives one level down, exactly like topic browsing already works.

### 3. `AchievementTracker.cpp` — one-line text generalization

`achievementDescription(AchievementId::PerfectExam)` currently reads
"Bir bölüm sınavından %100 aldın." ("You got 100% on a SECTION exam").
Since Phase 22 makes this achievement reachable via the final exam too
(which is not a section exam), change the text to "Bir sınavdan %100
aldın." (dropping "bölüm") so the description stays accurate for both
cases. `achievementDisplayName` ("Mükemmel Sınav") already reads
generically and needs no change. No new `AchievementId` is introduced
— reusing the existing one is correct since "get a perfect score on
any exam" is exactly what it already represents.

### 4. Test changes

- New `tests/ExamContentTests.cpp`: for each section 1-10, verify
  `examQuestionIdsForSection` returns exactly 20 unique ids, all
  resolve via a real `QuestionManager::findById`, and (for sections
  2-10 specifically) map back to exactly 2 questions per topic across
  all 10 of that section's topics (confirming even coverage — the
  actual improvement over Section 1's uneven curated set). Verify
  `finalExamQuestionIds()` returns exactly 100 unique ids, all resolve,
  and map back to exactly 1 question per topic across all 100 topics
  (topics 1-100, no gaps, no duplicates).
- `tests/QuestionManagerTests.cpp`: replace the duplicated
  `kExamQuestionIds` array and `QuestionManager_EveryExamQuestionIdResolves`
  test with a version that calls `examQuestionIdsForSection(1)`
  directly — this is the actual fix for the staleness risk the
  existing comment flags.
- `CMakeLists.txt`: register `src/ExamContent.h`, `src/ExamContent.cpp`,
  `tests/ExamContentTests.cpp`.

## Testing / verification for this phase

- Unit tests as above (`ExamContentTests.cpp`, updated
  `QuestionManagerTests.cpp`).
- Manual end-to-end verification: run the built app, pick "6. Seviye
  Sınavı", confirm the new exam-picker menu lists all 10 sections plus
  "Genel Final Sınavı"; take a Section 2+ exam through to a result line
  (confirm 20 questions, correct/score/XP/pass-fail lines print, and
  `progress_.recordSectionExamPassed` persists); take the general final
  exam through to a result line (confirm 100 questions gate correctly,
  same result reporting, no `recordSectionExamPassed` call needed to
  compile/run correctly since it's simply not invoked for the final
  exam).
- Full existing suite must stay green — this phase changes shared
  `Application.cpp` code paths (`handleChoice`, `runSectionExam`), so
  regression risk is centered there; no other content/tests should be
  affected.

## Scope cuts (deliberate)

- No change to `UserProgress`'s per-section-exam-passed data model
  (still a single "highest" int, not a per-section set) — extending it
  is a legitimate future enhancement but not required by this phase's
  ask, and doing so would be an unrequested architecture change.
- No new `AchievementId` for the final exam specifically (reusing
  `PerfectExam`, with a one-line generalized description).
- No configurable "varsayılan sınav soru sayısı" (default exam question
  count) settings field — the roadmap explicitly defers this exact
  item to "Phase 22" in its settings-gap bullet, but researching
  `src/Settings.h` found no existing field at all (not even a stub);
  adding one is a bigger scope than "add exams" and is deferred further
  to Phase 25 (final polish), matching how the analogous "renk aç/kapa"
  and "sesli uyarı" settings bullets are already deferred there.
- No retroactive fix to Section 1's uneven topic coverage (6 of 10
  topics) — Section 1's exam is explicitly preserved byte-for-byte;
  only the NEW section exams (2-10) get even per-topic coverage.

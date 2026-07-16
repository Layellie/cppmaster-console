# CppMaster Console — Adaptif Zorluk Sistemi (Adaptive Difficulty) Implementation Plan (Phase 12)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make `runTopicQuiz` order its topic's questions easy-to-hard, jump
to the hardest remaining question after two correct answers in a row, and
respond to two wrong answers in a row by re-showing the topic's lesson
summary and an automatic level-1 hint for the next question.

**Architecture:** A tiny pure-logic header (`src/AdaptiveDifficulty.h`,
matching the established `TopicLock.h`/`HintProvider.h` pattern) holds the
two decision functions, fully unit-testable independent of `Application`.
`Application::runTopicQuiz` sorts its question list once by ascending
`Difficulty`, then drives the loop using these two functions plus two new
local streak counters — no changes to `askOneQuestion`, `QuizEngine`, or
any other caller of `askOneQuestion`.

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only.

**Spec:** `docs/superpowers/specs/2026-07-16-adaptive-difficulty-design.md`

## Global Constraints

- C++20 required, CMake ≥ 3.20, standard library only.
- Zero compiler warnings on the library, app, and test executable (`apply_strict_warnings()`).
- No `using namespace std;` anywhere.
- **This phase deliberately changes topic-quiz question order** (sorted
  ascending by `Difficulty`, then streak-driven jumps) — this is the
  feature, not a regression. The final quiz summary line and XP total are
  unaffected (still computed and printed once, after the loop, exactly as
  before); only the per-question order and which question a given
  achievement-unlock message follows changes. This phase's manual
  verification step traces and uses the new canonical topic-1 order; use
  that order (not the pre-Phase-12 one) as the reference for any future
  phase that needs a "known-good topic-1 transcript."
- Only `runTopicQuiz` gets adaptive ordering. `runQuickTest`,
  `runSectionExam`, and `runMistakeQuestions` are unaffected — do not
  touch them.
- Before running any task's manual verification below, delete
  `data/progress.txt`, `data/mistakes.txt`, `data/achievements.txt`,
  `data/generated_question_history.txt`, and `data/settings.txt` if they
  exist.
- After Task 2's final commit, update `docs/superpowers/roadmap.md`'s
  Phase 12 entry and Status section to mark it COMPLETE with its commit
  range starting at this plan's own commit (matching the Phase 8-11
  convention).

---

### Task 1: `AdaptiveDifficulty.h` pure-logic header and its tests

**Files:**
- Create: `src/AdaptiveDifficulty.h`
- Create: `tests/AdaptiveDifficultyTests.cpp`
- Modify: `CMakeLists.txt`

**Interfaces:**
- Consumes: `Question` (`src/Question.h`, unchanged).
- Produces: `std::size_t selectNextQuestionIndex(const std::vector<Question>& remaining, int correctStreak, int wrongStreak)`,
  `bool shouldShowExtraHelp(int wrongStreak)` — Task 2's
  `Application::runTopicQuiz` calls both by exact name.

- [ ] **Step 1: Create `src/AdaptiveDifficulty.h`**

```cpp
#pragma once

#include <cstddef>
#include <vector>

#include "Question.h"

// `remaining` must already be sorted ascending by `difficulty` (the
// caller's responsibility, done once at quiz start). Returns the index
// (into `remaining`) of which question to ask next.
[[nodiscard]] inline std::size_t selectNextQuestionIndex(
    const std::vector<Question>& remaining, int correctStreak, int wrongStreak) {
    (void)wrongStreak;
    if (correctStreak >= 2 && remaining.size() > 1) {
        return remaining.size() - 1;
    }
    return 0;
}

[[nodiscard]] inline bool shouldShowExtraHelp(int wrongStreak) {
    return wrongStreak >= 2;
}
```

(`wrongStreak` is accepted by `selectNextQuestionIndex` for a stable,
self-documenting signature even though the current selection rule doesn't
need it directly — dropping to the easiest remaining question on a wrong
streak is already what index `0` means once the list is difficulty-sorted.
The `(void)wrongStreak;` line avoids an unused-parameter warning.)

- [ ] **Step 2: Create `tests/AdaptiveDifficultyTests.cpp`**

```cpp
#include "AdaptiveDifficulty.h"

#include "TestRunner.h"

namespace {

Question makeQuestionWithDifficulty(int id, Difficulty difficulty) {
    Question question;
    question.id = id;
    question.difficulty = difficulty;
    return question;
}

}  // namespace

TEST_CASE(AdaptiveDifficulty_BelowTwoCorrectStreakStaysAtEasiestRemaining) {
    const std::vector<Question> remaining = {
        makeQuestionWithDifficulty(1, Difficulty::Easy),
        makeQuestionWithDifficulty(2, Difficulty::Medium),
        makeQuestionWithDifficulty(3, Difficulty::Hard),
    };
    CHECK(selectNextQuestionIndex(remaining, 0, 0) == 0);
    CHECK(selectNextQuestionIndex(remaining, 1, 0) == 0);
}

TEST_CASE(AdaptiveDifficulty_TwoPlusCorrectStreakJumpsToHardestRemaining) {
    const std::vector<Question> remaining = {
        makeQuestionWithDifficulty(1, Difficulty::Easy),
        makeQuestionWithDifficulty(2, Difficulty::Medium),
        makeQuestionWithDifficulty(3, Difficulty::Hard),
    };
    CHECK(selectNextQuestionIndex(remaining, 2, 0) == 2);
    CHECK(selectNextQuestionIndex(remaining, 5, 0) == 2);
}

TEST_CASE(AdaptiveDifficulty_TwoPlusCorrectStreakWithOneRemainingStaysAtZero) {
    const std::vector<Question> remaining = {makeQuestionWithDifficulty(1, Difficulty::Easy)};
    CHECK(selectNextQuestionIndex(remaining, 2, 0) == 0);
}

TEST_CASE(AdaptiveDifficulty_ShouldShowExtraHelpOnlyAtTwoOrMoreWrongInARow) {
    CHECK(!shouldShowExtraHelp(0));
    CHECK(!shouldShowExtraHelp(1));
    CHECK(shouldShowExtraHelp(2));
    CHECK(shouldShowExtraHelp(3));
}
```

- [ ] **Step 3: Add the new files to `CMakeLists.txt`**

Add `src/AdaptiveDifficulty.h` to `CppMasterConsoleLib`'s source list, and
`tests/AdaptiveDifficultyTests.cpp` to `CppMasterConsoleTests`'s source
list.

- [ ] **Step 4: Build and run**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
./build/Debug/CppMasterConsoleTests.exe
```
Expected: `87/87 test(s) passed.` (83 from Phase 11 + 4 new
`AdaptiveDifficulty` tests). Zero warnings.

- [ ] **Step 5: Commit**

```bash
git add CMakeLists.txt src/AdaptiveDifficulty.h tests/AdaptiveDifficultyTests.cpp
git commit -m "Add AdaptiveDifficulty pure-logic header for streak-driven question ordering"
```

---

### Task 2: Wire adaptive ordering into `runTopicQuiz`, manual verification

**Files:**
- Modify: `src/Application.cpp`

**Interfaces:**
- Consumes: `selectNextQuestionIndex`/`shouldShowExtraHelp` (Task 1), `generateHint` (Phase 10, unchanged, already available via `Application.h`'s existing `#include "HintProvider.h"`).
- Produces: nothing consumed by later tasks — final task of this phase.

- [ ] **Step 1: Add includes**

Add `#include <algorithm>` to the standard-library include block, and
`#include "AdaptiveDifficulty.h"` alongside the existing
`#include "TopicLock.h"`.

- [ ] **Step 2: Replace `Application::runTopicQuiz`'s body**

Replace the entire function with:

```cpp
void Application::runTopicQuiz(int topicId) {
    auto remaining = questions_.questionsForTopic(topicId);
    std::stable_sort(remaining.begin(), remaining.end(), [](const Question& a, const Question& b) {
        return a.difficulty < b.difficulty;
    });
    const auto totalQuestions = static_cast<int>(remaining.size());

    ui_.printLine("Konu testi başlıyor (" + std::to_string(totalQuestions) + " soru).");
    ui_.printLine("");

    const auto lesson = lessons_.findById(topicId);

    int correctCount = 0;
    int sessionXp = 0;
    int correctStreak = 0;
    int wrongStreak = 0;

    while (!remaining.empty()) {
        const std::size_t nextIndex = selectNextQuestionIndex(remaining, correctStreak, wrongStreak);
        const Question question = remaining[nextIndex];

        if (shouldShowExtraHelp(wrongStreak)) {
            if (lesson.has_value() && !lesson->explanation.empty()) {
                ui_.printLine("");
                ui_.printLine("Bu konuyu tekrar hatırlayalım:");
                ui_.printLine(lesson->explanation);
            }
            if (question.type != QuestionType::WriteCode) {
                ui_.printLine(generateHint(question, 1));
            }
            wrongStreak = 0;
        }

        remaining.erase(remaining.begin() + static_cast<std::ptrdiff_t>(nextIndex));

        const AnswerResult result = askOneQuestion(question);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(sessionXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
            ++correctStreak;
            wrongStreak = 0;
        } else {
            ++wrongStreak;
            correctStreak = 0;
        }
    }

    const double successRatio =
        totalQuestions == 0 ? 0.0
                            : static_cast<double>(correctCount) / static_cast<double>(totalQuestions);
    const int successPercent = static_cast<int>(successRatio * 100.0);

    ui_.printLine(
        "Sonuç: " + std::to_string(correctCount) + "/" + std::to_string(totalQuestions) +
        " doğru (%" + std::to_string(successPercent) + "), kazanılan XP: " +
        std::to_string(sessionXp));

    awardXpAndCheckLevelUp(sessionXp);

    if (successRatio >= kPassThreshold) {
        progress_.setStatus(topicId, TopicStatus::Completed);
        ui_.printLine("Bu konu tamamlandı olarak işaretlendi.");
    } else {
        progress_.setStatus(topicId, TopicStatus::Learning);
        ui_.printLine("Bu konuyu öğrenmeye devam ediyorsun; tekrar denemek için tekrar açabilirsin.");
    }
    ui_.printLine("");

    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
}
```

- [ ] **Step 3: Build**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
```
Expected: zero warnings.

- [ ] **Step 4: Run the full test suite**

```bash
./build/Debug/CppMasterConsoleTests.exe
cd build && ctest -C Debug --output-on-failure && cd ..
```
Expected: `87/87 test(s) passed.`, `ctest` 100%.

- [ ] **Step 5: Manual verification — new canonical topic-1 order, all answers correct**

Topic 1's 8 questions (ids 1,2,3,4,5,6,65,70) sorted ascending by
`Difficulty`, then walked through this task's streak-jump rule (traced by
hand against the real question bank — every answer below is correct),
produce this **new** order, replacing every prior phase's topic-1
transcript as the canonical reference from this phase onward:

| Order | id | Type | Correct answer | baseXp |
|---|---|---|---|---|
| 1 | 3 | TrueFalse | `2` | 5 |
| 2 | 1 | MultipleChoice | `b` | 10 |
| 3 | 70 | OrderCode | `3 2 1 4` | 20 |
| 4 | 6 | FillBlank | `iostream` | 20 |
| 5 | 2 | MultipleChoice | `c` | 20 |
| 6 | 65 | FindError | `int yas = 20;` | 10 |
| 7 | 5 | FillBlank | `cout` | 10 |
| 8 | 4 | TrueFalse | `1` | 10 |

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
printf "1\n1\n2\nb\n3 2 1 4\niostream\nc\nint yas = 20;\ncout\n1\n0\n" | ./build/Debug/CppMasterConsole.exe
```

Confirm: questions are asked in exactly the order in the table above (not
the old `1,2,3,4,5,6,65,70` order); `Yeni başarım kazandın: İlk Adım`
appears right after the **1st** question (id 3, the first-ever correct
answer); `Yeni başarım kazandın: Hatasız Beşli` appears right after the
**5th** question (id 2 — the 5th correct answer in a row); and the final
summary is **unchanged** from every prior phase: `Sonuç: 8/8 doğru (%100),
kazanılan XP: 105`, followed by the level-2 celebration
(`Tebrikler! Yeni seviyeye ulaştın: Değişken Ustası (Seviye 2)`), and
`data/mistakes.txt` remains empty afterward.

- [ ] **Step 6: Manual verification — two wrong in a row triggers the extra-help re-display**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
printf "1\n1\n1\na\ncikis\n0\n" | ./build/Debug/CppMasterConsole.exe
```

This pipes: main menu → Konuları Öğren (1), topic 1 (1); the quiz asks
question id 3 (TrueFalse, first in the new order) — answered `1` (**wrong**,
correct is `2`); then id 1 (MultipleChoice) — answered `a` (**wrong**,
correct is `b`) — two wrong in a row. Confirm that **before** the third
question (id 4, TrueFalse, next-easiest remaining) is shown, the app
prints:
```
Bu konuyu tekrar hatırlayalım:
cout, ekrana veri yazdırmak için kullanılan bir çıktı akışıdır (output stream). Kullanabilmek için <iostream> kütüphanesinin eklenmesi gerekir. << operatörü ile bir veya birden fazla değer art arda ekrana yazdırılabilir.
İfadeyi parça parça oku; tek bir kelime bile ifadeyi yanlış yapabilir.
```
(the topic's lesson explanation, then the level-1 hint for a `TrueFalse`
question — `genericTipFor(QuestionType::TrueFalse)` from
`src/HintProvider.cpp`) — then the `cikis` input exits the quiz
immediately without answering id 4, confirming no XP was awarded (both
prior answers were wrong, so `sessionXp` is `0` at the exit point) and no
further questions are asked.

Clean up all `data/*.txt` files after this step.

- [ ] **Step 7: Commit**

```bash
git add src/Application.cpp
git commit -m "Wire adaptive difficulty into runTopicQuiz: easy-to-hard ordering, streak-based jumps, extra help on repeated misses"
```

- [ ] **Step 8: Update the roadmap**

Edit `docs/superpowers/roadmap.md`: mark the Phase 12 entry COMPLETE with
its commit range (this plan's own commit through Task 2's final commit),
matching the style of the Phase 8-11 entries, and update the Status
section to name Phase 12 complete and Phase 13 starting next (the first of
the large content-expansion phases).

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 12 complete in roadmap"
```

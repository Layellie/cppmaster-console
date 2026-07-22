# Sınavlar (Section Exams + Final Exam) Implementation Plan (Phase 22)

> **Execution note:** subagent dispatch is currently blocked by a
> weekly rate limit (resets Jul 21, 8pm Europe/Istanbul), so this plan
> is executed directly by the controller rather than via
> subagent-driven-development. Tasks are still tracked and verified
> (build/test/diff) exactly as they would be for a dispatched
> implementer, and each task is self-reviewed against this plan's
> Global Constraints before moving to the next.

**Goal:** Generalize the existing Section-1-only exam mechanism to
support all 10 sections plus a new 100-question general final exam.

**Architecture:** New pure-function pair in `src/ExamContent.h/.cpp`
(`examQuestionIdsForSection`, `finalExamQuestionIds`) computing exam
question ids algorithmically (except Section 1's exam, preserved
byte-for-byte). `Application::runSectionExam` gains a `sectionId`
parameter; new `Application::runFinalExam` and
`Application::showExamMenu` complete the UI flow.

**Tech Stack:** C++20, CMake, the project's own minimal test framework.

## Global Constraints

- Topic-to-base-id formula for topics 11-100 (established and verified
  identical across Phases 13-21): `baseId(topic) = 73 + (topic - 11) * 29`.
  Within a topic's 29-id block: offset 0 = first MultipleChoice
  (VeryEasy); offsets 0-7 are the 8 MultipleChoice
  (VeryEasy,Easy,Easy,Medium,Medium,Medium,Hard,Hard); offset +3 is
  therefore the first Medium MultipleChoice. Offsets 8-13 are the 6
  TrueFalse (VeryEasy,VeryEasy,Easy,Easy,Medium,Medium); offset +12 is
  therefore the first Medium TrueFalse. Verified directly against the
  committed source of Sections 2, 5, 7, and 10.
- Topics 1-10 predate this fixed distribution (only 6 questions each,
  ids 1-60, plus 12 extra ids 61-72 used only by Section 1's existing
  exam) — handled as a fixed list, not a formula.
- Section 1's exam (`kExamQuestionIds` in `src/Application.cpp`) is
  moved into `examQuestionIdsForSection(1)` VERBATIM — same 20 ids, same
  order. Its behavior must be provably unchanged (same ids resolve to
  the same questions in the same order).
- Sections 2-10: `examQuestionIdsForSection(sectionId)` returns 20 ids
  — for each of the section's 10 topics `T` in
  `[(sectionId-1)*10+1, sectionId*10]`, push `baseId(T)+3` then
  `baseId(T)+12`.
- `finalExamQuestionIds()` returns 100 ids: `{1,7,13,19,25,31,37,43,49,55}`
  for topics 1-10 (the first id of each topic's existing 6-question
  block), then `baseId(T)+3` for each topic `T` in `[11,100]`.
- Pass threshold stays 0.7 (70%) for both section and final exams,
  reusing the existing `kExamPassThreshold`/`kSectionCompletionGateThreshold`
  constants.
- `AchievementId::PerfectExam` is reused for a perfect score on ANY
  exam (section or final) — its description text is generalized from
  "Bir bölüm sınavından %100 aldın." to "Bir sınavdan %100 aldın.";
  no new achievement id is added.
- `UserProgress`'s per-section-exam-passed tracking (`highestSectionExamPassed_`,
  a single int) is NOT changed. The final exam does not call
  `recordSectionExamPassed` (there is no section 11).
- No new Settings field, no `Application.cpp` main-menu structure
  change beyond routing case 6 through a new picker submenu
  (`kMinChoice`/`kMaxChoice` for the main menu stay 0-10).

---

### Task 1: `src/ExamContent.h` / `src/ExamContent.cpp` + unit tests

**Files:**
- Create: `src/ExamContent.h`, `src/ExamContent.cpp`
- Create: `tests/ExamContentTests.cpp`
- Modify: `CMakeLists.txt` (register all three)

**Interfaces:**
- Produces: `std::vector<int> examQuestionIdsForSection(int sectionId);`
  and `std::vector<int> finalExamQuestionIds();`, both declared in
  `src/ExamContent.h`, no dependency on `Question.h`/`QuestionManager.h`.

- [ ] **Step 1: Write `src/ExamContent.h`**

```cpp
#pragma once

#include <vector>

[[nodiscard]] std::vector<int> examQuestionIdsForSection(int sectionId);
[[nodiscard]] std::vector<int> finalExamQuestionIds();
```

- [ ] **Step 2: Write `src/ExamContent.cpp`**

```cpp
#include "ExamContent.h"

namespace {

constexpr int kFirstFormulaTopic = 11;
constexpr int kFirstFormulaTopicBaseId = 73;
constexpr int kQuestionsPerTopic = 29;
constexpr int kMediumMultipleChoiceOffset = 3;
constexpr int kMediumTrueFalseOffset = 12;
constexpr int kTopicsPerSection = 10;

int baseIdForTopic(int topicId) {
    return kFirstFormulaTopicBaseId + (topicId - kFirstFormulaTopic) * kQuestionsPerTopic;
}

}  // namespace

std::vector<int> examQuestionIdsForSection(int sectionId) {
    if (sectionId == 1) {
        return {1, 2, 3, 4, 5, 6, 19, 20, 33, 35, 61, 62, 63, 64, 65, 66, 67, 68, 69, 71};
    }

    std::vector<int> ids;
    const int firstTopic = (sectionId - 1) * kTopicsPerSection + 1;
    for (int topic = firstTopic; topic < firstTopic + kTopicsPerSection; ++topic) {
        const int base = baseIdForTopic(topic);
        ids.push_back(base + kMediumMultipleChoiceOffset);
        ids.push_back(base + kMediumTrueFalseOffset);
    }
    return ids;
}

std::vector<int> finalExamQuestionIds() {
    std::vector<int> ids = {1, 7, 13, 19, 25, 31, 37, 43, 49, 55};
    for (int topic = kFirstFormulaTopic; topic <= 100; ++topic) {
        ids.push_back(baseIdForTopic(topic) + kMediumMultipleChoiceOffset);
    }
    return ids;
}
```

- [ ] **Step 3: Register the new files in CMake**

In `CMakeLists.txt`, add `src/ExamContent.h` and `src/ExamContent.cpp`
to `CppMasterConsoleLib`'s sources (alphabetically near `src/Enums.h`
or grouped with other free-function headers like `src/TopicLock.h` —
place directly after `src/CodeExerciseManager.cpp` for minimal diff
noise), and add `tests/ExamContentTests.cpp` to
`CppMasterConsoleTests`'s sources (after `tests/CodeExerciseTests.cpp`).

- [ ] **Step 4: Write `tests/ExamContentTests.cpp`**

```cpp
#include "ExamContent.h"

#include <map>
#include <unordered_set>

#include "QuestionManager.h"
#include "TestRunner.h"

TEST_CASE(ExamContent_SectionOneExamMatchesExistingCuratedSet) {
    const auto ids = examQuestionIdsForSection(1);
    const std::vector<int> expected = {1, 2, 3, 4, 5, 6, 19, 20, 33, 35,
                                        61, 62, 63, 64, 65, 66, 67, 68, 69, 71};
    CHECK(ids == expected);
}

TEST_CASE(ExamContent_EverySectionExamHasTwentyUniqueResolvableIds) {
    QuestionManager manager;
    for (int sectionId = 1; sectionId <= 10; ++sectionId) {
        const auto ids = examQuestionIdsForSection(sectionId);
        CHECK(ids.size() == 20);
        std::unordered_set<int> seen;
        for (int id : ids) {
            CHECK(seen.insert(id).second);
            CHECK(manager.findById(id).has_value());
        }
    }
}

TEST_CASE(ExamContent_SectionsTwoToTenCoverEveryTopicTwice) {
    QuestionManager manager;
    for (int sectionId = 2; sectionId <= 10; ++sectionId) {
        const auto ids = examQuestionIdsForSection(sectionId);
        std::map<int, int> countPerTopic;
        for (int id : ids) {
            const auto question = manager.findById(id);
            CHECK(question.has_value());
            if (question.has_value()) {
                ++countPerTopic[question->topicId];
            }
        }
        const int firstTopic = (sectionId - 1) * 10 + 1;
        for (int topic = firstTopic; topic < firstTopic + 10; ++topic) {
            CHECK(countPerTopic[topic] == 2);
        }
    }
}

TEST_CASE(ExamContent_FinalExamHasOneHundredUniqueResolvableIdsCoveringEveryTopic) {
    QuestionManager manager;
    const auto ids = finalExamQuestionIds();
    CHECK(ids.size() == 100);
    std::unordered_set<int> seen;
    std::map<int, int> countPerTopic;
    for (int id : ids) {
        CHECK(seen.insert(id).second);
        const auto question = manager.findById(id);
        CHECK(question.has_value());
        if (question.has_value()) {
            ++countPerTopic[question->topicId];
        }
    }
    for (int topic = 1; topic <= 100; ++topic) {
        CHECK(countPerTopic[topic] == 1);
    }
}
```

- [ ] **Step 5: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" -S . -B build` then
`"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `100/100 test(s) passed.` (96 + 4 new `ExamContent_*` tests).

- [ ] **Step 6: Commit**

```bash
git add src/ExamContent.h src/ExamContent.cpp tests/ExamContentTests.cpp CMakeLists.txt
git commit -m "feat(exams): add examQuestionIdsForSection/finalExamQuestionIds"
```

---

### Task 2: Generalize `runSectionExam`, add `runFinalExam` and `showExamMenu`

**Files:**
- Modify: `src/Application.h` (signature change + 2 new declarations)
- Modify: `src/Application.cpp` (remove fixed exam constants, rewrite
  `runSectionExam`, add `runFinalExam`/`showExamMenu`, wire
  `#include "ExamContent.h"`, route `case 6` through `showExamMenu`)

**Interfaces:**
- Consumes: `examQuestionIdsForSection`/`finalExamQuestionIds` from
  Task 1.
- Produces: `void runSectionExam(int sectionId);`,
  `void runFinalExam();`, `void showExamMenu();` — no other file
  depends on these signatures.

- [ ] **Step 1: Update `src/Application.h`**

Change:
```cpp
    void runSectionExam();
```
to:
```cpp
    void runSectionExam(int sectionId);
    void runFinalExam();
    void showExamMenu();
```

- [ ] **Step 2: Update `src/Application.cpp`'s top-of-file constants**

Remove these four lines (no longer needed — computed by
`ExamContent.cpp` instead):
```cpp
constexpr int kExamQuestionIds[] = {
    1, 2, 3, 4, 5, 6, 19, 20, 33, 35,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 71,
};
constexpr int kExamQuestionCount = 20;
constexpr int kExamSectionId = 1;
constexpr int kExamSectionTopicCount = 10;
```
Keep `kExamPassThreshold` and `kSectionCompletionGateThreshold`
exactly as they are (both still used, now by both exam kinds).

Add `#include "ExamContent.h"` to the includes block (alongside the
existing `#include "AdaptiveDifficulty.h"` / `#include "LevelSystem.h"`
/ `#include "TopicLock.h"` group).

- [ ] **Step 3: Change `case 6:` in `handleChoice`**

Change:
```cpp
        case 6:
            runSectionExam();
            break;
```
to:
```cpp
        case 6:
            showExamMenu();
            break;
```

- [ ] **Step 4: Rewrite `runSectionExam` and add `runFinalExam`/`showExamMenu`**

Replace the existing `void Application::runSectionExam() { ... }`
(currently lines 754-833) with:

```cpp
void Application::runSectionExam(int sectionId) {
    int completedCount = 0;
    const auto topicsInSection = lessons_.lessonsInSection(sectionId);
    for (const Lesson& lesson : topicsInSection) {
        const TopicStatus status = progress_.statusOf(lesson.id);
        if (status == TopicStatus::Completed || status == TopicStatus::Mastered) {
            ++completedCount;
        }
    }
    const int topicCount = static_cast<int>(topicsInSection.size());

    const double completionRatio =
        static_cast<double>(completedCount) / static_cast<double>(topicCount);

    if (!sectionExamIsUnlocked(
            settings_.topicLockEnabled, completionRatio, kSectionCompletionGateThreshold)) {
        ui_.printLine("");
        ui_.printLine(
            "Bu bölümün sınavına girebilmek için konuların en az %70'ini tamamlamalısınız.");
        ui_.printLine(
            "Şu an " + std::to_string(completedCount) + "/" + std::to_string(topicCount) +
            " konu tamamlanmış.");
        return;
    }

    const std::vector<int> examQuestionIds = examQuestionIdsForSection(sectionId);
    const int examQuestionCount = static_cast<int>(examQuestionIds.size());

    ui_.printLine("");
    ui_.printHeader("BÖLÜM " + std::to_string(sectionId) + " SINAVI");
    ui_.printLine(
        std::to_string(examQuestionCount) + " soruluk sınav başlıyor. Geçme notu: %70.");
    ui_.printLine("");

    int correctCount = 0;
    int examXp = 0;

    for (const int questionId : examQuestionIds) {
        const auto question = questions_.findById(questionId);
        if (!question.has_value()) {
            continue;
        }
        const AnswerResult result = askOneQuestion(*question, /*trackMistakes=*/true, /*allowHints=*/false);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(examXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
        if (result.correct) {
            ++correctCount;
            examXp += result.xpAwarded;
        }
    }

    const double scoreRatio =
        static_cast<double>(correctCount) / static_cast<double>(examQuestionCount);
    const int scorePercent = static_cast<int>(scoreRatio * 100.0);

    ui_.printLine(
        "Doğru: " + std::to_string(correctCount) + "/" + std::to_string(examQuestionCount));
    ui_.printLine("Başarı: %" + std::to_string(scorePercent));
    ui_.printLine("Kazanılan XP: " + std::to_string(examXp));
    ui_.printLine(
        std::string("Sonuç: ") + (scoreRatio >= kExamPassThreshold ? "GEÇTİN" : "KALDIN"));

    if (scoreRatio >= kExamPassThreshold) {
        progress_.recordSectionExamPassed(sectionId);
    }

    if (correctCount == examQuestionCount) {
        if (achievements_.unlock(AchievementId::PerfectExam)) {
            ui_.printLine("");
            ui_.printLine(
                "Yeni başarım kazandın: " + achievementDisplayName(AchievementId::PerfectExam));
            ui_.printLine(achievementDescription(AchievementId::PerfectExam));
            achievements_.saveToFile(kAchievementsFilePath);
        }
    }

    awardXpAndCheckLevelUp(examXp);
    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));

    ui_.printLine("");
}

void Application::runFinalExam() {
    int completedCount = 0;
    const auto allTopics = lessons_.allLessons();
    for (const Lesson& lesson : allTopics) {
        const TopicStatus status = progress_.statusOf(lesson.id);
        if (status == TopicStatus::Completed || status == TopicStatus::Mastered) {
            ++completedCount;
        }
    }
    const int totalTopicCount = static_cast<int>(allTopics.size());

    const double completionRatio =
        static_cast<double>(completedCount) / static_cast<double>(totalTopicCount);

    if (!sectionExamIsUnlocked(
            settings_.topicLockEnabled, completionRatio, kSectionCompletionGateThreshold)) {
        ui_.printLine("");
        ui_.printLine(
            "Genel final sınavına girebilmek için tüm konuların en az %70'ini "
            "tamamlamalısınız.");
        ui_.printLine(
            "Şu an " + std::to_string(completedCount) + "/" + std::to_string(totalTopicCount) +
            " konu tamamlanmış.");
        return;
    }

    const std::vector<int> examQuestionIds = finalExamQuestionIds();
    const int examQuestionCount = static_cast<int>(examQuestionIds.size());

    ui_.printLine("");
    ui_.printHeader("GENEL FİNAL SINAVI");
    ui_.printLine(
        std::to_string(examQuestionCount) + " soruluk sınav başlıyor. Geçme notu: %70.");
    ui_.printLine("");

    int correctCount = 0;
    int examXp = 0;

    for (const int questionId : examQuestionIds) {
        const auto question = questions_.findById(questionId);
        if (!question.has_value()) {
            continue;
        }
        const AnswerResult result = askOneQuestion(*question, /*trackMistakes=*/true, /*allowHints=*/false);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(examXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
        if (result.correct) {
            ++correctCount;
            examXp += result.xpAwarded;
        }
    }

    const double scoreRatio =
        static_cast<double>(correctCount) / static_cast<double>(examQuestionCount);
    const int scorePercent = static_cast<int>(scoreRatio * 100.0);

    ui_.printLine(
        "Doğru: " + std::to_string(correctCount) + "/" + std::to_string(examQuestionCount));
    ui_.printLine("Başarı: %" + std::to_string(scorePercent));
    ui_.printLine("Kazanılan XP: " + std::to_string(examXp));
    ui_.printLine(
        std::string("Sonuç: ") + (scoreRatio >= kExamPassThreshold ? "GEÇTİN" : "KALDIN"));

    if (correctCount == examQuestionCount) {
        if (achievements_.unlock(AchievementId::PerfectExam)) {
            ui_.printLine("");
            ui_.printLine(
                "Yeni başarım kazandın: " + achievementDisplayName(AchievementId::PerfectExam));
            ui_.printLine(achievementDescription(AchievementId::PerfectExam));
            achievements_.saveToFile(kAchievementsFilePath);
        }
    }

    awardXpAndCheckLevelUp(examXp);
    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));

    ui_.printLine("");
}

void Application::showExamMenu() {
    ui_.printLine("");
    ui_.printLine("Hangi sınava girmek istiyorsunuz?");
    for (int sectionId = 1; sectionId <= lessons_.sectionCount(); ++sectionId) {
        ui_.printLine(
            std::to_string(sectionId) + ". Bölüm " + std::to_string(sectionId) + " Sınavı: " +
            lessons_.sectionTitle(sectionId));
    }
    const int finalExamChoice = lessons_.sectionCount() + 1;
    ui_.printLine(std::to_string(finalExamChoice) + ". Genel Final Sınavı");
    ui_.printLine("0. Geri dön");
    const int choice = ui_.readMenuChoice(0, finalExamChoice);
    if (choice == 0) {
        return;
    }
    if (choice == finalExamChoice) {
        runFinalExam();
        return;
    }
    runSectionExam(choice);
}
```

- [ ] **Step 5: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `100/100 test(s) passed.` (unchanged from Task 1's end state
— this task touches no test files).

- [ ] **Step 6: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "feat(exams): generalize runSectionExam, add runFinalExam and showExamMenu"
```

---

### Task 3: Generalize the `PerfectExam` achievement text + fix the stale test duplication

**Files:**
- Modify: `src/AchievementTracker.cpp` (one description string)
- Modify: `tests/QuestionManagerTests.cpp` (remove the duplicated
  `kExamQuestionIds` array, use `examQuestionIdsForSection(1)` instead)

**Interfaces:**
- Consumes: `examQuestionIdsForSection` from Task 1.

- [ ] **Step 1: Generalize the achievement description**

In `src/AchievementTracker.cpp`, change:
```cpp
        case AchievementId::PerfectExam:
            return "Bir bölüm sınavından %100 aldın.";
```
to:
```cpp
        case AchievementId::PerfectExam:
            return "Bir sınavdan %100 aldın.";
```

- [ ] **Step 2: Fix the stale test duplication**

In `tests/QuestionManagerTests.cpp`, replace:
```cpp
#include "QuestionManager.h"

#include <unordered_set>

#include "TestRunner.h"

namespace {
// A frozen copy of the Section 1 exam's question set, as defined in
// Application.cpp's kExamQuestionIds. This only catches the catalog dropping
// an id this list still references (Application.cpp silently skips missing
// ids otherwise) - it will NOT notice if the real kExamQuestionIds itself is
// edited, since this copy doesn't track it live.
constexpr int kExamQuestionIds[] = {
    1, 2, 3, 4, 5, 6, 19, 20, 33, 35,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 71,
};
}  // namespace

TEST_CASE(QuestionManager_EveryExamQuestionIdResolves) {
    QuestionManager manager;
    for (const int questionId : kExamQuestionIds) {
        CHECK(manager.findById(questionId).has_value());
    }
}
```
with:
```cpp
#include "QuestionManager.h"

#include <unordered_set>

#include "ExamContent.h"
#include "TestRunner.h"

TEST_CASE(QuestionManager_EveryExamQuestionIdResolves) {
    QuestionManager manager;
    for (const int questionId : examQuestionIdsForSection(1)) {
        CHECK(manager.findById(questionId).has_value());
    }
}
```
(keep the rest of the file, including `QuestionManager_NoDuplicateQuestionIds`
and everything after it, unchanged).

- [ ] **Step 3: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `100/100 test(s) passed.` (unchanged — one test's
implementation changed, none added/removed).

- [ ] **Step 4: Commit**

```bash
git add src/AchievementTracker.cpp tests/QuestionManagerTests.cpp
git commit -m "fix(exams): generalize PerfectExam text, remove stale exam-id test duplication"
```

---

### Task 4: Manual end-to-end verification + roadmap update

- [ ] **Step 1: Manual verification — exam menu, a Section 2+ exam, and the final exam**

Run `./build/Debug/CppMasterConsole.exe` and manually drive:
1. Complete enough of Section 2's topics (or disable
   `settings_.topicLockEnabled` via the Ayarlar menu, or directly edit
   `data/progress.txt` between runs) to pass the 70% gate, OR simply
   verify the gate MESSAGE appears correctly when NOT unlocked (both
   are valid manual checks — pick whichever is faster to set up).
2. From the main menu, choose "6. Seviye Sınavı" — confirm the new
   picker lists "1. Bölüm 1 Sınavı: ...", ..., "10. Bölüm 10 Sınavı:
   ...", "11. Genel Final Sınavı", "0. Geri dön".
3. Pick a Section 2-10 exam: confirm "BÖLÜM N SINAVI" header, "20
   soruluk sınav başlıyor..." line, that questions display and can be
   answered, and that the final "Doğru:/Başarı:/Kazanılan XP:/Sonuç:"
   lines print correctly.
4. Pick "11. Genel Final Sınavı": confirm "GENEL FİNAL SINAVI" header
   and "100 soruluk sınav başlıyor...", answer a few questions, use
   `cikis` to exit early, confirm partial XP is saved and the app
   returns to the main menu cleanly.
5. Clean up: `rm -f data/*.txt`.

- [ ] **Step 2: Update the roadmap**

In `docs/superpowers/roadmap.md`:
1. Strike through the "Only one section exam exists..." bullet in
   "Confirmed gaps" with a "resolved in Phase 22" note (mirroring the
   format already used for the Phase 21 content bullets).
2. Add a Phase 22 COMPLETE bullet under "Phase order," immediately
   after the Phase 21 entry, in the same format Phases 8-21 use, with
   the commit range from this phase's spec commit through this task's
   final commit.
3. Update the "Status" section: Phase 22 complete, Phase 23
   (Üretici kütüphanesini genişletme) starting next.

Then commit:

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 22 complete in roadmap"
```

---

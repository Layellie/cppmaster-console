# CppMaster Console — Konu Kilidi Sistemi (Topic Lock) Implementation Plan (Phase 9)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make the existing Section 1 exam completion-gate obey `settings_.topicLockEnabled`, track which section exams have been passed, and show a "not yet recommended" advisory tag on sections the user hasn't earned yet in the topic browser — with no hard block on actually opening any topic, matching the original brief exactly.

**Architecture:** A tiny pure-logic header (`src/TopicLock.h`, matching the existing `LevelSystem.h` header-only-inline-function pattern) holds the two decision functions. `UserProgress` gains one new persisted field (`highestSectionExamPassed`) following the exact `recordX`/`setX` pattern already used for streaks and typed-correct counters. `Application` wires both into `runSectionExam` (the gate + recording a pass) and `showTopicBrowser` (the advisory tag).

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only.

**Spec:** `docs/superpowers/specs/2026-07-16-topic-lock-design.md`

## Global Constraints

- C++20 required, CMake ≥ 3.20, standard library only.
- Zero compiler warnings on the library, app, and test executable (`apply_strict_warnings()`).
- No `using namespace std;` anywhere.
- Tests never touch `data/` — persistence tests write only to `tests/test_data/`, cleaning up files they create.
- **This phase deliberately changes default topic-browser output** (Sections 2-10 gain a `(henüz önerilmiyor)` suffix by default, since `settings_.topicLockEnabled` defaults to `true`) — this is the feature, not a regression. Every other prior phase's regression transcript that does NOT print the topic browser (e.g. the standard 8-question Topic-1-completion transcript) still applies unchanged; only transcripts that show the browser's section list need updating.
- Before running any task's manual verification below, delete `data/progress.txt`, `data/mistakes.txt`, `data/achievements.txt`, `data/generated_question_history.txt`, and `data/settings.txt` if they exist.
- No CI, no feature branches — direct commits to `master`.

---

### Task 1: `UserProgress` + `ProgressManager` track the highest section exam passed

**Files:**
- Modify: `src/UserProgress.h`
- Modify: `src/UserProgress.cpp`
- Modify: `src/ProgressManager.cpp`
- Modify: `tests/UserProgressTests.cpp`
- Modify: `tests/ProgressManagerTests.cpp`

**Interfaces:**
- Consumes: nothing new.
- Produces: `UserProgress::highestSectionExamPassed() const`, `UserProgress::recordSectionExamPassed(int sectionId)`, `UserProgress::setHighestSectionExamPassed(int value)` — Task 3's `Application::runSectionExam`/`showTopicBrowser` use these exact names.

- [ ] **Step 1: Modify `src/UserProgress.h`** — add three new method declarations right after the existing typed-correct-counter block, and one new private member. Full new file:

```cpp
#pragma once

#include <unordered_map>

#include "Enums.h"

class UserProgress {
public:
    explicit UserProgress(int topicCount);

    [[nodiscard]] TopicStatus statusOf(int topicId) const;
    void setStatus(int topicId, TopicStatus status);

    [[nodiscard]] int totalXp() const;
    void addXp(int amount);

    [[nodiscard]] int totalQuestionsAnswered() const;
    [[nodiscard]] int totalCorrectAnswers() const;
    void recordAnswer(bool correct);
    void setAnsweredCounters(int totalAnswered, int totalCorrect);

    [[nodiscard]] int currentStreak() const;
    [[nodiscard]] int longestStreak() const;
    void recordStreak(bool correct);
    void setStreakCounters(int current, int longest);

    [[nodiscard]] int writeCodeCorrectCount() const;
    [[nodiscard]] int errorFixCorrectCount() const;
    void recordTypedCorrectAnswer(QuestionType type);
    void setTypedCorrectCounters(int writeCode, int errorFix);

    [[nodiscard]] int highestSectionExamPassed() const;
    void recordSectionExamPassed(int sectionId);
    void setHighestSectionExamPassed(int value);

private:
    std::unordered_map<int, TopicStatus> statusByTopicId_;
    int totalXp_ = 0;
    int totalQuestionsAnswered_ = 0;
    int totalCorrectAnswers_ = 0;
    int currentStreak_ = 0;
    int longestStreak_ = 0;
    int writeCodeCorrectCount_ = 0;
    int errorFixCorrectCount_ = 0;
    int highestSectionExamPassed_ = 0;
};
```

- [ ] **Step 2: Modify `src/UserProgress.cpp`** — add three new method definitions at the end of the file, after `setTypedCorrectCounters`:

```cpp
int UserProgress::highestSectionExamPassed() const {
    return highestSectionExamPassed_;
}

void UserProgress::recordSectionExamPassed(int sectionId) {
    if (sectionId > highestSectionExamPassed_) {
        highestSectionExamPassed_ = sectionId;
    }
}

void UserProgress::setHighestSectionExamPassed(int value) {
    highestSectionExamPassed_ = value;
}
```

- [ ] **Step 3: Modify `src/ProgressManager.cpp`** — add a new persisted field. Full new file:

```cpp
#include "ProgressManager.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <system_error>
#include <utility>

namespace {

bool tryParseInt(const std::string& text, int& outValue) {
    if (text.empty()) {
        return false;
    }
    try {
        std::size_t consumedChars = 0;
        const int value = std::stoi(text, &consumedChars);
        if (consumedChars != text.size()) {
            return false;
        }
        outValue = value;
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool parseStatusName(const std::string& name, TopicStatus& outStatus) {
    if (name == "NotStarted") {
        outStatus = TopicStatus::NotStarted;
        return true;
    }
    if (name == "Learning") {
        outStatus = TopicStatus::Learning;
        return true;
    }
    if (name == "Completed") {
        outStatus = TopicStatus::Completed;
        return true;
    }
    if (name == "Mastered") {
        outStatus = TopicStatus::Mastered;
        return true;
    }
    return false;
}

std::string statusName(TopicStatus status) {
    switch (status) {
        case TopicStatus::NotStarted:
            return "NotStarted";
        case TopicStatus::Learning:
            return "Learning";
        case TopicStatus::Completed:
            return "Completed";
        case TopicStatus::Mastered:
            return "Mastered";
    }
    return "NotStarted";
}

}  // namespace

ProgressLoadResult ProgressManager::load(
    const std::string& filePath, const std::string& backupPath, int topicCount) const {
    UserProgress progress(topicCount);

    std::ifstream file(filePath);
    if (!file.is_open()) {
        return ProgressLoadResult{std::move(progress), false};
    }

    int xp = 0;
    int answered = 0;
    int correct = 0;
    int streakCurrent = 0;
    int streakLongest = 0;
    int writeCodeCorrect = 0;
    int errorFixCorrect = 0;
    int highestSectionExamPassed = 0;
    bool corrupted = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream lineStream(line);
        std::string recordType;
        lineStream >> recordType;

        if (recordType == "xp") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, xp)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "answered") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, answered)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "correct") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, correct)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "streak_current") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, streakCurrent)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "streak_longest") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, streakLongest)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "writecode_correct") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, writeCodeCorrect)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "errorfix_correct") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, errorFixCorrect)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "highest_section_exam_passed") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, highestSectionExamPassed)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "topic") {
            std::string topicIdText;
            std::string statusText;
            lineStream >> topicIdText >> statusText;
            int topicId = 0;
            TopicStatus status = TopicStatus::NotStarted;
            if (!tryParseInt(topicIdText, topicId) || !parseStatusName(statusText, status)) {
                corrupted = true;
                break;
            }
            progress.setStatus(topicId, status);
        } else {
            corrupted = true;
            break;
        }
    }

    if (corrupted) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        return ProgressLoadResult{UserProgress(topicCount), true};
    }

    progress.addXp(xp);
    progress.setAnsweredCounters(answered, correct);
    progress.setStreakCounters(streakCurrent, streakLongest);
    progress.setTypedCorrectCounters(writeCodeCorrect, errorFixCorrect);
    progress.setHighestSectionExamPassed(highestSectionExamPassed);
    return ProgressLoadResult{std::move(progress), false};
}

void ProgressManager::save(
    const UserProgress& progress, const std::string& filePath, int topicCount) const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        return;
    }
    file << "xp " << progress.totalXp() << '\n';
    file << "answered " << progress.totalQuestionsAnswered() << '\n';
    file << "correct " << progress.totalCorrectAnswers() << '\n';
    file << "streak_current " << progress.currentStreak() << '\n';
    file << "streak_longest " << progress.longestStreak() << '\n';
    file << "writecode_correct " << progress.writeCodeCorrectCount() << '\n';
    file << "errorfix_correct " << progress.errorFixCorrectCount() << '\n';
    file << "highest_section_exam_passed " << progress.highestSectionExamPassed() << '\n';
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        file << "topic " << topicId << ' ' << statusName(progress.statusOf(topicId)) << '\n';
    }
}
```

- [ ] **Step 4: Add a test to `tests/UserProgressTests.cpp`** — append at the end of the file:

```cpp
TEST_CASE(UserProgress_RecordSectionExamPassedOnlyIncreases) {
    UserProgress progress(5);
    CHECK(progress.highestSectionExamPassed() == 0);
    progress.recordSectionExamPassed(1);
    CHECK(progress.highestSectionExamPassed() == 1);
    progress.recordSectionExamPassed(1);
    CHECK(progress.highestSectionExamPassed() == 1);
    progress.recordSectionExamPassed(3);
    CHECK(progress.highestSectionExamPassed() == 3);
    progress.recordSectionExamPassed(2);
    CHECK(progress.highestSectionExamPassed() == 3);
}
```

- [ ] **Step 5: Extend `tests/ProgressManagerTests.cpp`**

In `ProgressManager_SaveThenLoadRoundTripsAllFields`, add a call to
`progress.recordSectionExamPassed(1);` right after the existing
`progress.setStatus(3, TopicStatus::Completed);` line, and add
`CHECK(result.progress.highestSectionExamPassed() == 1);` right after the
existing `CHECK(result.progress.statusOf(3) == TopicStatus::Completed);`
line.

In `ProgressManager_MissingFileLoadsFreshNotCorrupted`, add
`CHECK(result.progress.highestSectionExamPassed() == 0);` right after the
existing `CHECK(result.progress.totalXp() == 0);` line.

- [ ] **Step 6: Build and run**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
./build/Debug/CppMasterConsoleTests.exe
```
Expected: `63/63 test(s) passed.` (62 from Phase 8 + 1 new
`UserProgress_RecordSectionExamPassedOnlyIncreases` — the two extended
tests add assertions to existing tests, not new `TEST_CASE`s, so they don't
change the total count). Zero warnings.

- [ ] **Step 7: Commit**

```bash
git add src/UserProgress.h src/UserProgress.cpp src/ProgressManager.cpp tests/UserProgressTests.cpp tests/ProgressManagerTests.cpp
git commit -m "Track highest section exam passed in UserProgress and ProgressManager"
```

---

### Task 2: `TopicLock.h` pure-logic header and its tests

**Files:**
- Create: `src/TopicLock.h`
- Create: `tests/TopicLockTests.cpp`
- Modify: `CMakeLists.txt`

**Interfaces:**
- Consumes: nothing.
- Produces: `bool isSectionRecommended(int sectionId, int highestSectionExamPassed)`,
  `bool sectionExamIsUnlocked(bool topicLockEnabled, double completionRatio, double gateThreshold)`
  — Task 3's `Application.cpp` calls both by exact name.

- [ ] **Step 1: Create `src/TopicLock.h`**

```cpp
#pragma once

[[nodiscard]] inline bool isSectionRecommended(int sectionId, int highestSectionExamPassed) {
    return sectionId <= highestSectionExamPassed + 1;
}

[[nodiscard]] inline bool sectionExamIsUnlocked(
    bool topicLockEnabled, double completionRatio, double gateThreshold) {
    return !topicLockEnabled || completionRatio >= gateThreshold;
}
```

- [ ] **Step 2: Create `tests/TopicLockTests.cpp`**

```cpp
#include "TopicLock.h"

#include "TestRunner.h"

TEST_CASE(TopicLock_SectionOneIsAlwaysRecommendedWithNoExamsPassed) {
    CHECK(isSectionRecommended(1, 0));
    CHECK(!isSectionRecommended(2, 0));
    CHECK(!isSectionRecommended(10, 0));
}

TEST_CASE(TopicLock_SectionRecommendedExactlyAtHighestPlusOne) {
    CHECK(isSectionRecommended(3, 2));
    CHECK(!isSectionRecommended(4, 2));
    CHECK(isSectionRecommended(1, 2));
    CHECK(isSectionRecommended(2, 2));
}

TEST_CASE(TopicLock_ExamUnlockedWhenLockDisabledRegardlessOfRatio) {
    CHECK(sectionExamIsUnlocked(false, 0.0, 0.7));
    CHECK(sectionExamIsUnlocked(false, 1.0, 0.7));
}

TEST_CASE(TopicLock_ExamGateRespectsThresholdWhenLockEnabled) {
    CHECK(!sectionExamIsUnlocked(true, 0.69, 0.7));
    CHECK(sectionExamIsUnlocked(true, 0.7, 0.7));
    CHECK(sectionExamIsUnlocked(true, 1.0, 0.7));
}
```

- [ ] **Step 3: Add the new file to `CMakeLists.txt`'s test executable**

Add `tests/TopicLockTests.cpp` to the `add_executable(CppMasterConsoleTests ...)`
source list. `src/TopicLock.h` does NOT need adding to
`CppMasterConsoleLib`'s source list separately for compilation purposes
(header-only, included where used), but add it there too for IDE/build-file
completeness, matching how every other header in the project (e.g.
`src/LevelSystem.h`) is listed in `CppMasterConsoleLib`'s source list.

- [ ] **Step 4: Build and run**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
./build/Debug/CppMasterConsoleTests.exe
```
Expected: `67/67 test(s) passed.` (63 from Task 1 + 4 new `TopicLock` tests).
Zero warnings.

- [ ] **Step 5: Commit**

```bash
git add CMakeLists.txt src/TopicLock.h tests/TopicLockTests.cpp
git commit -m "Add TopicLock pure-logic header for section recommendation and exam gating"
```

---

### Task 3: Wire topic lock into `Application` — exam gate, recording, advisory tags, manual verification

**Files:**
- Modify: `src/Application.cpp`

**Interfaces:**
- Consumes: `UserProgress::highestSectionExamPassed`/`recordSectionExamPassed` (Task 1), `isSectionRecommended`/`sectionExamIsUnlocked` (Task 2), `Settings::topicLockEnabled` (Phase 8, unchanged).
- Produces: nothing consumed by later tasks — final task of this phase.

- [ ] **Step 1: Add the new include**

Add `#include "TopicLock.h"` to `src/Application.cpp`'s include block
(alongside the existing `#include "LevelSystem.h"`).

- [ ] **Step 2: Modify `runSectionExam`'s gate check**

Change:
```cpp
    if (completionRatio < kSectionCompletionGateThreshold) {
```
to:
```cpp
    if (!sectionExamIsUnlocked(
            settings_.topicLockEnabled, completionRatio, kSectionCompletionGateThreshold)) {
```
(The body of this `if` block — the two `ui_.printLine` calls and `return;`
— stays exactly as-is.)

- [ ] **Step 3: Record a passed exam in `runSectionExam`**

Right after the existing line:
```cpp
    ui_.printLine(
        std::string("Sonuç: ") + (scoreRatio >= kExamPassThreshold ? "GEÇTİN" : "KALDIN"));
```
add:
```cpp
    if (scoreRatio >= kExamPassThreshold) {
        progress_.recordSectionExamPassed(kExamSectionId);
    }
```

- [ ] **Step 4: Modify `showTopicBrowser`'s section header line**

Change:
```cpp
void Application::showTopicBrowser() {
    ui_.printLine("");
    for (int sectionId = 1; sectionId <= lessons_.sectionCount(); ++sectionId) {
        ui_.printLine(
            "Bölüm " + std::to_string(sectionId) + ": " + lessons_.sectionTitle(sectionId));
```
to:
```cpp
void Application::showTopicBrowser() {
    ui_.printLine("");
    for (int sectionId = 1; sectionId <= lessons_.sectionCount(); ++sectionId) {
        std::string sectionHeader =
            "Bölüm " + std::to_string(sectionId) + ": " + lessons_.sectionTitle(sectionId);
        if (settings_.topicLockEnabled &&
            !isSectionRecommended(sectionId, progress_.highestSectionExamPassed())) {
            sectionHeader += " (henüz önerilmiyor)";
        }
        ui_.printLine(sectionHeader);
```
(Everything after this — the per-lesson loop and the trailing
`ui_.printLine("");` — stays exactly as-is.)

- [ ] **Step 5: Build**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
```
Expected: zero warnings.

- [ ] **Step 6: Run the full test suite**

```bash
./build/Debug/CppMasterConsoleTests.exe
cd build && ctest -C Debug --output-on-failure && cd ..
```
Expected: `67/67 test(s) passed.`, `ctest` 100%.

- [ ] **Step 7: Manual verification — fresh topic browser shows the new advisory tags**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
printf "1\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```
(Opens the topic browser, then returns to main menu, then exits — no topic
selected.) Confirm section headers read exactly:
```
Bölüm 1: Giriş, çıkış ve değişkenler
Bölüm 2: Operatörler ve koşullar (henüz önerilmiyor)
Bölüm 3: Seçim ve döngüler (henüz önerilmiyor)
```
(and so on through Bölüm 10, each with the suffix) — Section 1 has no
suffix (it's always recommended at `highestSectionExamPassed == 0`), every
other section does.

- [ ] **Step 8: Manual verification — passing Section 1's exam removes Section 2's tag**

Reaching 70% completion on Section 1 through real quiz answers first would
need ~70 answers before the exam even becomes reachable. Instead, craft a
progress file that is already 100% complete on Section 1, in exactly the
format `ProgressManager::save` produces (this format is already covered by
`ProgressManagerTests.cpp`'s round-trip test, so the file is trustworthy):

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
{
  echo "xp 0"
  echo "answered 0"
  echo "correct 0"
  echo "streak_current 0"
  echo "streak_longest 0"
  echo "writecode_correct 0"
  echo "errorfix_correct 0"
  echo "highest_section_exam_passed 0"
  for i in $(seq 1 10); do echo "topic $i Completed"; done
  for i in $(seq 11 100); do echo "topic $i NotStarted"; done
} > data/progress.txt
```

Then take the Section 1 exam and answer all 20 questions correctly, in the
exact order `kExamQuestionIds` asks them (`Application.cpp:30-33`):

```bash
printf "6\nb\nc\n2\n1\ncout\niostream\nb\nd\n2\nint\ntoplam + 5\nb\n8\n0\nint yas = 20;\nchar harf = 'A';\ndouble ortalama = 87.5;\ncin >> yas;\n2 3 1\nint sayi;\ncin >> sayi;\ncout << sayi;\nBITIR\n1\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```

This pipes: main menu choice 6 (Seviye Sınavı — now unlocked, no "en az
%70'ini tamamlamalısınız" gate message should appear, since Section 1 is
already 100% complete); the 20 exam answers in order (the last one,
question 71/WriteCode, is multi-line — `int sayi;` / `cin >> sayi;` /
`cout << sayi;` / `BITIR`, matching the required substrings `cin`, `>>`,
`cout`, `<<`); then `1` (main menu → Konuları Öğren, to view the topic
browser), `0` (browser → back to main menu without selecting a topic), `0`
(exit).

Since `data/achievements.txt` was also deleted before this run,
`askOneQuestion`'s existing `checkAchievements` call (unchanged by this
phase) fires for every exam question too, not just topic-quiz questions —
expect `İlk Adım` to unlock after the 1st answer, `Hatasız Beşli` after the
5th, and `Seri Ustası` after the 10th (all answers are correct, so the
streak climbs straight through both thresholds); this is pre-existing
Phase 5 behavior being exercised via a new call path, not something this
phase changes — don't treat these as unexpected.

Confirm: `Doğru: 20/20`, `Başarı: %100`, `Sonuç: GEÇTİN`, and the `Mükemmel
Sınav` achievement unlock message at the end. Then confirm the topic
browser section printed by this same run shows:
```
Bölüm 1: Giriş, çıkış ve değişkenler
Bölüm 2: Operatörler ve koşullar
Bölüm 3: Seçim ve döngüler (henüz önerilmiyor)
```
— Section 2 no longer carries the `(henüz önerilmiyor)` suffix (since
`highestSectionExamPassed` is now `1`, and `isSectionRecommended(2, 1)` is
`2 <= 1+1` = true), while Section 3 onward still do. Finally:

```bash
grep highest_section_exam_passed data/progress.txt
```
Expected: `highest_section_exam_passed 1`.

- [ ] **Step 9: Manual verification — disabling topic lock removes tags immediately**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
printf "9\n1\n0\n1\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```
This pipes: open Settings (9), toggle topic lock off (1), back to main menu
(0), open the topic browser (1) with a completely fresh (0% complete)
progress state, back to main menu (0), exit (0). Confirm every section
header (2 through 10) prints with **no** `(henüz önerilmiyor)` suffix even
though `highestSectionExamPassed` is still `0` — proving
`settings_.topicLockEnabled = false` disables the advisory tags
independently of exam history. (The gate itself unblocking the exam when
the toggle is off is already proven directly by
`TopicLockTests.cpp`'s `TopicLock_ExamUnlockedWhenLockDisabledRegardlessOfRatio`
unit test — no need to also drive a full 20-question exam through stdin
just to re-prove the same underlying function.)

- [ ] **Step 10: Regression check — unrelated existing transcript still matches byte-for-byte**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
The first "1" opens "Konuları Öğren" (`showTopicBrowser`), so this run
prints the section list too — confirm it shows the same advisory tags as
Step 7 (fresh progress, so Sections 2-10 all carry the suffix). Then confirm
everything **after** the browser (the second "1" selecting topic 1, the
lesson content, the 8-question quiz, `İlk Adım`/`Hatasız Beşli` unlocks,
`Sonuç: 8/8 doğru (%100), kazanılan XP: 105`, the level-2 celebration, empty
`data/mistakes.txt`) is byte-for-byte identical to every prior phase's
known transcript — proving this phase's change is additive (new tags in the
browser only) and doesn't disturb anything downstream of topic selection.

Clean up all `data/*.txt` files after this step.

- [ ] **Step 11: Commit**

```bash
git add src/Application.cpp
git commit -m "Wire topic lock into Application: settings-gated exam threshold and section recommendation tags"
```

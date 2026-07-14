# CppMaster Console — Meta Systems (Phase 5) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add a 10-level XP ladder with celebration messages, 7 reachable achievements, and a real 20-question exam for Bölüm 1 gated behind 70% topic completion.

**Architecture:** `UserProgress` gains streak/typed-correct counters; a new header-only `LevelSystem.h` maps XP to a level; a new `AchievementTracker` class tracks an unlock-set with the same corruption-safe persistence pattern as every other data file; `MistakeTracker` gains one lookup method (`findMistake`) needed by achievement checks; `Application` gains a shared `awardXpAndCheckLevelUp` helper (replacing three existing `addXp` call sites), a `checkAchievements` hook inside `askOneQuestion`, and a new exam flow that reuses `askOneQuestion` exactly like every other quiz flow.

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only. Still no test framework.

**Spec:** `docs/superpowers/specs/2026-07-15-meta-systems-design.md`

## Global Constraints

- C++20 required, same CMake settings as before.
- No external libraries — standard library only.
- Compiler warnings: MSVC `/W4 /permissive-`; GCC/Clang `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`. Zero warnings required.
- No `using namespace std;` anywhere.
- No fake/placeholder code. The section exam only exists for Bölüm 1 (topics 1-10) — every other section still has no content, so there is nothing dishonest to build for them; this phase does not add a menu path to "select a section" that would imply otherwise.
- Any malformed line in a data file marks the WHOLE file corrupt (backup + fresh empty state); a missing file is not corruption — same rule as every existing data file.
- **Before running any task's manual verification below, delete `data/progress.txt`, `data/mistakes.txt`, and `data/achievements.txt`** if they exist, so every task's hand-computed expected values start from a clean slate.
- Adding a new field to `progress.txt` must not break loading an *older* file that lacks it — a missing field defaults to 0, exactly like every counter phase 4 already added.

---

### Task 1: `UserProgress` streak/typed counters + `ProgressManager` persistence

**Files:**
- Modify: `src/UserProgress.h`
- Modify: `src/UserProgress.cpp`
- Modify: `src/ProgressManager.cpp`
- Modify (temporarily, superseded in Task 2): `src/main.cpp`

**Interfaces:**
- Consumes: nothing new.
- Produces: `UserProgress` gains `currentStreak()`, `longestStreak()`, `recordStreak(bool)`, `setStreakCounters(int,int)`, `writeCodeCorrectCount()`, `errorFixCorrectCount()`, `recordTypedCorrectAnswer(QuestionType)`, `setTypedCorrectCounters(int,int)`. `ProgressManager::load`/`save` persist all four new counters, defaulting missing ones to 0 for backward compatibility with phase-4 `progress.txt` files.

- [ ] **Step 1: Modify `src/UserProgress.h`** — full file:

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

private:
    std::unordered_map<int, TopicStatus> statusByTopicId_;
    int totalXp_ = 0;
    int totalQuestionsAnswered_ = 0;
    int totalCorrectAnswers_ = 0;
    int currentStreak_ = 0;
    int longestStreak_ = 0;
    int writeCodeCorrectCount_ = 0;
    int errorFixCorrectCount_ = 0;
};
```

- [ ] **Step 2: Modify `src/UserProgress.cpp`** — full file:

```cpp
#include "UserProgress.h"

UserProgress::UserProgress(int topicCount) {
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        statusByTopicId_[topicId] = TopicStatus::NotStarted;
    }
}

TopicStatus UserProgress::statusOf(int topicId) const {
    const auto it = statusByTopicId_.find(topicId);
    if (it == statusByTopicId_.end()) {
        return TopicStatus::NotStarted;
    }
    return it->second;
}

void UserProgress::setStatus(int topicId, TopicStatus status) {
    statusByTopicId_[topicId] = status;
}

int UserProgress::totalXp() const {
    return totalXp_;
}

void UserProgress::addXp(int amount) {
    totalXp_ += amount;
}

int UserProgress::totalQuestionsAnswered() const {
    return totalQuestionsAnswered_;
}

int UserProgress::totalCorrectAnswers() const {
    return totalCorrectAnswers_;
}

void UserProgress::recordAnswer(bool correct) {
    ++totalQuestionsAnswered_;
    if (correct) {
        ++totalCorrectAnswers_;
    }
}

void UserProgress::setAnsweredCounters(int totalAnswered, int totalCorrect) {
    totalQuestionsAnswered_ = totalAnswered;
    totalCorrectAnswers_ = totalCorrect;
}

int UserProgress::currentStreak() const {
    return currentStreak_;
}

int UserProgress::longestStreak() const {
    return longestStreak_;
}

void UserProgress::recordStreak(bool correct) {
    if (correct) {
        ++currentStreak_;
        if (currentStreak_ > longestStreak_) {
            longestStreak_ = currentStreak_;
        }
    } else {
        currentStreak_ = 0;
    }
}

void UserProgress::setStreakCounters(int current, int longest) {
    currentStreak_ = current;
    longestStreak_ = longest;
}

int UserProgress::writeCodeCorrectCount() const {
    return writeCodeCorrectCount_;
}

int UserProgress::errorFixCorrectCount() const {
    return errorFixCorrectCount_;
}

void UserProgress::recordTypedCorrectAnswer(QuestionType type) {
    if (type == QuestionType::WriteCode) {
        ++writeCodeCorrectCount_;
    } else if (type == QuestionType::FindError || type == QuestionType::FixCode) {
        ++errorFixCorrectCount_;
    }
}

void UserProgress::setTypedCorrectCounters(int writeCode, int errorFix) {
    writeCodeCorrectCount_ = writeCode;
    errorFixCorrectCount_ = errorFix;
}
```

- [ ] **Step 3: Modify `src/ProgressManager.cpp`** — full file:

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
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        file << "topic " << topicId << ' ' << statusName(progress.statusOf(topicId)) << '\n';
    }
}
```

- [ ] **Step 4: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <filesystem>
#include <fstream>
#include <iostream>

#include "ProgressManager.h"
#include "UserProgress.h"

int main() {
    std::filesystem::create_directories("data");

    UserProgress progress(10);
    std::cout << "Baslangic streak: " << progress.currentStreak() << " (beklenen: 0)\n";

    progress.recordStreak(true);
    progress.recordStreak(true);
    progress.recordStreak(true);
    std::cout << "3 dogru sonrasi streak: " << progress.currentStreak() << " (beklenen: 3)\n";
    std::cout << "En uzun streak: " << progress.longestStreak() << " (beklenen: 3)\n";

    progress.recordStreak(false);
    std::cout << "Yanlis sonrasi streak: " << progress.currentStreak() << " (beklenen: 0)\n";
    std::cout << "En uzun streak (degismemeli): " << progress.longestStreak() << " (beklenen: 3)\n";

    progress.recordTypedCorrectAnswer(QuestionType::WriteCode);
    progress.recordTypedCorrectAnswer(QuestionType::WriteCode);
    progress.recordTypedCorrectAnswer(QuestionType::FindError);
    progress.recordTypedCorrectAnswer(QuestionType::FixCode);
    progress.recordTypedCorrectAnswer(QuestionType::MultipleChoice);
    std::cout << "WriteCode dogru sayisi: " << progress.writeCodeCorrectCount() << " (beklenen: 2)\n";
    std::cout << "ErrorFix dogru sayisi: " << progress.errorFixCorrectCount() << " (beklenen: 2)\n";

    ProgressManager manager;
    const std::string testPath = "data/test_progress_p5.txt";
    const std::string backupPath = "data/test_progress_p5_corrupted_backup.txt";
    manager.save(progress, testPath, 10);

    const auto loaded = manager.load(testPath, backupPath, 10);
    std::cout << "Yuklenen bozuk mu: " << (loaded.wasCorrupted ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Yuklenen streak: " << loaded.progress.currentStreak() << " (beklenen: 0)\n";
    std::cout << "Yuklenen en uzun streak: " << loaded.progress.longestStreak() << " (beklenen: 3)\n";
    std::cout << "Yuklenen WriteCode dogru: " << loaded.progress.writeCodeCorrectCount() << " (beklenen: 2)\n";
    std::cout << "Yuklenen ErrorFix dogru: " << loaded.progress.errorFixCorrectCount() << " (beklenen: 2)\n";

    {
        std::ofstream oldFormatFile(testPath, std::ios::trunc);
        oldFormatFile << "xp 50\n";
        oldFormatFile << "answered 5\n";
        oldFormatFile << "correct 4\n";
        oldFormatFile << "topic 1 Completed\n";
    }
    const auto oldFormatLoaded = manager.load(testPath, backupPath, 10);
    std::cout << "Eski format bozuk mu: " << (oldFormatLoaded.wasCorrupted ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Eski format XP: " << oldFormatLoaded.progress.totalXp() << " (beklenen: 50)\n";
    std::cout << "Eski format streak (yok, 0 olmali): " << oldFormatLoaded.progress.currentStreak()
              << " (beklenen: 0)\n";

    return 0;
}
```

- [ ] **Step 5: Build and run**

Run:
```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line ends in `(OK)`. Zero compiler warnings.

- [ ] **Step 6: Commit**

```bash
git add src/UserProgress.h src/UserProgress.cpp src/ProgressManager.cpp src/main.cpp
git commit -m "Add streak and typed-correct-answer counters to UserProgress"
```

---

### Task 2: `LevelSystem.h` + leveling wired into `Application`

**Files:**
- Create: `src/LevelSystem.h`
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`
- Modify: `CMakeLists.txt`

**Interfaces:**
- Consumes: `UserProgress::totalXp`/`addXp` (unchanged).
- Produces: `struct LevelInfo { int level; std::string name; }; LevelInfo levelForXp(int xp);` and `void Application::awardXpAndCheckLevelUp(int amount);` (replaces the three existing `progress_.addXp(sessionXp);` call sites).

- [ ] **Step 1: Create `src/LevelSystem.h`**

```cpp
#pragma once

#include <string>

struct LevelInfo {
    int level;
    std::string name;
};

[[nodiscard]] inline LevelInfo levelForXp(int xp) {
    struct LevelThreshold {
        int level;
        int xpThreshold;
        const char* name;
    };

    constexpr LevelThreshold kLevels[] = {
        {1, 0, "Başlangıç"},
        {2, 50, "Değişken Ustası"},
        {3, 120, "Koşul Çözücü"},
        {4, 220, "Döngü Ustası"},
        {5, 350, "Dizi Kaşifi"},
        {6, 500, "Fonksiyon Geliştiricisi"},
        {7, 700, "Pointer Öğrencisi"},
        {8, 950, "Nesne Tasarımcısı"},
        {9, 1250, "STL Kullanıcısı"},
        {10, 1600, "C++ Geliştiricisi"},
    };

    LevelInfo result{1, "Başlangıç"};
    for (const LevelThreshold& threshold : kLevels) {
        if (xp >= threshold.xpThreshold) {
            result.level = threshold.level;
            result.name = threshold.name;
        } else {
            break;
        }
    }
    return result;
}
```

- [ ] **Step 2: Modify `src/Application.h`** — add `#include "LevelSystem.h"` to the include block and `void awardXpAndCheckLevelUp(int amount);` to the private section, right after `askOneQuestion`'s declaration, so the private section reads:

```cpp
private:
    void showMainMenu();
    void handleChoice(int choice);
    void showTopicBrowser();
    void openTopic(int topicId);
    void showLessonContent(const Lesson& lesson);
    void runTopicQuiz(int topicId);
    AnswerResult askOneQuestion(const Question& question);
    void awardXpAndCheckLevelUp(int amount);
    void resetProgress();
    void showMistakeReview();
    void runMistakeQuestions(const std::vector<MistakeRecord>& mistakesToAsk);
    void showStatistics();
    void runDailyReview();
    void showNotYetAvailable(const std::string& featureName);
    void ensureDataDirectoryExists();
```

- [ ] **Step 3: Modify `src/Application.cpp`**

Add `#include "LevelSystem.h"` to the include block.

Add the new method right after `askOneQuestion`:

```cpp
void Application::awardXpAndCheckLevelUp(int amount) {
    const LevelInfo levelBefore = levelForXp(progress_.totalXp());
    progress_.addXp(amount);
    const LevelInfo levelAfter = levelForXp(progress_.totalXp());
    if (levelAfter.level > levelBefore.level) {
        ui_.printLine("");
        ui_.printLine(
            "Tebrikler! Yeni seviyeye ulaştın: " + levelAfter.name + " (Seviye " +
            std::to_string(levelAfter.level) + ")");
        ui_.printLine("");
    }
}
```

Replace `progress_.addXp(sessionXp);` with `awardXpAndCheckLevelUp(sessionXp);` in **both** `runTopicQuiz` and `runMistakeQuestions` (two separate call sites — do not touch anything else in either function).

Modify `showMainMenu` — replace:
```cpp
    ui_.printLine("Toplam XP: " + std::to_string(progress_.totalXp()));
    ui_.printLine("");
```
with:
```cpp
    ui_.printLine("Toplam XP: " + std::to_string(progress_.totalXp()));
    const LevelInfo level = levelForXp(progress_.totalXp());
    ui_.printLine("Seviye: " + level.name + " (Seviye " + std::to_string(level.level) + ")");
    ui_.printLine("");
```

- [ ] **Step 4: Update `CMakeLists.txt`'s `add_executable` call**, inserting the new header after `QuizEngine.cpp` and before `ProgressManager.h`:

```cmake
add_executable(CppMasterConsole
    src/main.cpp
    src/Enums.h
    src/UserProgress.h
    src/UserProgress.cpp
    src/Lesson.h
    src/LessonManager.h
    src/LessonManager.cpp
    src/ConsoleUI.h
    src/ConsoleUI.cpp
    src/Question.h
    src/QuestionManager.h
    src/QuestionManager.cpp
    src/QuizEngine.h
    src/QuizEngine.cpp
    src/LevelSystem.h
    src/ProgressManager.h
    src/ProgressManager.cpp
    src/MistakeTracker.h
    src/MistakeTracker.cpp
    src/Application.h
    src/Application.cpp
)
```

- [ ] **Step 5: Restore `src/main.cpp` to its real entry-point form** (Task 1 left it as scratch verification code — this task's own verification needs the real `Application` entry point):

```cpp
#include "Application.h"

int main() {
    Application app;
    app.run();
    return 0;
}
```

- [ ] **Step 6: Clean slate, then build**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt
cmake --build build
```
Expected: zero warnings.

- [ ] **Step 7: Manual verification**

```bash
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm, in order: the usual topic-1 flow (unchanged from phase 4 up through the `Sonuç:` line), then a new line block `Tebrikler! Yeni seviyeye ulaştın: Değişken Ustası (Seviye 2)` (105 XP crosses the 50-XP level-2 threshold from a starting level of 1), then the existing "tamamlandı" status line. Confirm `Sonuç: 8/8 doğru (%100), kazanılan XP: 105` is present and unchanged. Then confirm the *next* main-menu print (before the final `0` is consumed) shows both `Toplam XP: 105` and `Seviye: Değişken Ustası (Seviye 2)`.

- [ ] **Step 8: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/LevelSystem.h src/Application.h src/Application.cpp
git commit -m "Add LevelSystem and wire level-up celebrations into Application"
```

---

### Task 3: `AchievementTracker` + `MistakeTracker::findMistake`

**Files:**
- Create: `src/AchievementTracker.h`
- Create: `src/AchievementTracker.cpp`
- Modify: `src/MistakeTracker.h`
- Modify: `src/MistakeTracker.cpp`
- Modify: `CMakeLists.txt`
- Modify (temporarily, superseded in Task 4): `src/main.cpp`

**Interfaces:**
- Consumes: nothing new.
- Produces:
  - `enum class AchievementId { FirstStep, FlawlessFive, StreakMaster, CodeWriter, BugHunter, NeverGiveUp, PerfectExam };`
  - `std::vector<AchievementId> allAchievementIds();`, `std::string achievementDisplayName(AchievementId);`, `std::string achievementDescription(AchievementId);`
  - `class AchievementTracker { public: bool unlock(AchievementId); bool isUnlocked(AchievementId) const; std::vector<AchievementId> allUnlocked() const; bool loadFromFile(const std::string&, const std::string&); void saveToFile(const std::string&) const; };`
  - `MistakeTracker` gains `std::optional<MistakeRecord> findMistake(int questionId) const;`.

- [ ] **Step 1: Create `src/AchievementTracker.h`**

```cpp
#pragma once

#include <string>
#include <unordered_set>
#include <vector>

enum class AchievementId {
    FirstStep,
    FlawlessFive,
    StreakMaster,
    CodeWriter,
    BugHunter,
    NeverGiveUp,
    PerfectExam,
};

[[nodiscard]] std::vector<AchievementId> allAchievementIds();
[[nodiscard]] std::string achievementDisplayName(AchievementId id);
[[nodiscard]] std::string achievementDescription(AchievementId id);

class AchievementTracker {
public:
    bool unlock(AchievementId id);
    [[nodiscard]] bool isUnlocked(AchievementId id) const;
    [[nodiscard]] std::vector<AchievementId> allUnlocked() const;

    [[nodiscard]] bool loadFromFile(const std::string& filePath, const std::string& backupPath);
    void saveToFile(const std::string& filePath) const;

private:
    std::unordered_set<int> unlockedIds_;
};
```

- [ ] **Step 2: Create `src/AchievementTracker.cpp`**

```cpp
#include "AchievementTracker.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <system_error>
#include <utility>

namespace {

bool parseAchievementName(const std::string& name, AchievementId& outId) {
    if (name == "FirstStep") {
        outId = AchievementId::FirstStep;
        return true;
    }
    if (name == "FlawlessFive") {
        outId = AchievementId::FlawlessFive;
        return true;
    }
    if (name == "StreakMaster") {
        outId = AchievementId::StreakMaster;
        return true;
    }
    if (name == "CodeWriter") {
        outId = AchievementId::CodeWriter;
        return true;
    }
    if (name == "BugHunter") {
        outId = AchievementId::BugHunter;
        return true;
    }
    if (name == "NeverGiveUp") {
        outId = AchievementId::NeverGiveUp;
        return true;
    }
    if (name == "PerfectExam") {
        outId = AchievementId::PerfectExam;
        return true;
    }
    return false;
}

std::string achievementSerializedName(AchievementId id) {
    switch (id) {
        case AchievementId::FirstStep:
            return "FirstStep";
        case AchievementId::FlawlessFive:
            return "FlawlessFive";
        case AchievementId::StreakMaster:
            return "StreakMaster";
        case AchievementId::CodeWriter:
            return "CodeWriter";
        case AchievementId::BugHunter:
            return "BugHunter";
        case AchievementId::NeverGiveUp:
            return "NeverGiveUp";
        case AchievementId::PerfectExam:
            return "PerfectExam";
    }
    return "";
}

}  // namespace

std::vector<AchievementId> allAchievementIds() {
    return {
        AchievementId::FirstStep,
        AchievementId::FlawlessFive,
        AchievementId::StreakMaster,
        AchievementId::CodeWriter,
        AchievementId::BugHunter,
        AchievementId::NeverGiveUp,
        AchievementId::PerfectExam,
    };
}

std::string achievementDisplayName(AchievementId id) {
    switch (id) {
        case AchievementId::FirstStep:
            return "İlk Adım";
        case AchievementId::FlawlessFive:
            return "Hatasız Beşli";
        case AchievementId::StreakMaster:
            return "Seri Ustası";
        case AchievementId::CodeWriter:
            return "Kod Yazarı";
        case AchievementId::BugHunter:
            return "Hata Avcısı";
        case AchievementId::NeverGiveUp:
            return "Pes Etmeyen";
        case AchievementId::PerfectExam:
            return "Mükemmel Sınav";
    }
    return "";
}

std::string achievementDescription(AchievementId id) {
    switch (id) {
        case AchievementId::FirstStep:
            return "İlk sorunu çözdün.";
        case AchievementId::FlawlessFive:
            return "Art arda 5 doğru cevap verdin.";
        case AchievementId::StreakMaster:
            return "Art arda 10 doğru cevap verdin.";
        case AchievementId::CodeWriter:
            return "10 kod yazma sorusu çözdün.";
        case AchievementId::BugHunter:
            return "25 hatalı kodu düzelttin.";
        case AchievementId::NeverGiveUp:
            return "Daha önce 5 kez yanlış yaptığın bir soruyu doğru çözdün.";
        case AchievementId::PerfectExam:
            return "Bir bölüm sınavından %100 aldın.";
    }
    return "";
}

bool AchievementTracker::unlock(AchievementId id) {
    const auto insertResult = unlockedIds_.insert(static_cast<int>(id));
    return insertResult.second;
}

bool AchievementTracker::isUnlocked(AchievementId id) const {
    return unlockedIds_.find(static_cast<int>(id)) != unlockedIds_.end();
}

std::vector<AchievementId> AchievementTracker::allUnlocked() const {
    std::vector<AchievementId> result;
    result.reserve(unlockedIds_.size());
    for (const int id : unlockedIds_) {
        result.push_back(static_cast<AchievementId>(id));
    }
    return result;
}

bool AchievementTracker::loadFromFile(const std::string& filePath, const std::string& backupPath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    std::unordered_set<int> parsedIds;
    bool corrupted = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream lineStream(line);
        std::string recordType;
        lineStream >> recordType;

        if (recordType != "achievement") {
            corrupted = true;
            break;
        }

        std::string nameText;
        lineStream >> nameText;

        AchievementId id = AchievementId::FirstStep;
        if (nameText.empty() || !parseAchievementName(nameText, id)) {
            corrupted = true;
            break;
        }
        parsedIds.insert(static_cast<int>(id));
    }

    if (corrupted) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        unlockedIds_.clear();
        return true;
    }

    unlockedIds_ = std::move(parsedIds);
    return false;
}

void AchievementTracker::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        return;
    }
    for (const int id : unlockedIds_) {
        file << "achievement " << achievementSerializedName(static_cast<AchievementId>(id)) << '\n';
    }
}
```

- [ ] **Step 3: Modify `src/MistakeTracker.h`** — add `#include <optional>` and the new method declaration, so the full file reads:

```cpp
#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

struct MistakeRecord {
    int questionId = 0;
    std::chrono::system_clock::time_point firstWrongAt;
    std::chrono::system_clock::time_point lastWrongAt;
    int wrongCount = 0;
    int correctAfterWrongCount = 0;
};

class MistakeTracker {
public:
    void recordWrong(int questionId);
    void recordCorrectRetry(int questionId);

    [[nodiscard]] bool hasMistake(int questionId) const;
    [[nodiscard]] std::optional<MistakeRecord> findMistake(int questionId) const;
    [[nodiscard]] std::vector<MistakeRecord> allMistakesOldestFirst() const;

    [[nodiscard]] bool loadFromFile(const std::string& filePath, const std::string& backupPath);
    void saveToFile(const std::string& filePath) const;

private:
    std::unordered_map<int, MistakeRecord> recordsByQuestionId_;
};
```

- [ ] **Step 4: Modify `src/MistakeTracker.cpp`** — append this method definition immediately after `hasMistake`'s definition:

```cpp
std::optional<MistakeRecord> MistakeTracker::findMistake(int questionId) const {
    const auto it = recordsByQuestionId_.find(questionId);
    if (it == recordsByQuestionId_.end()) {
        return std::nullopt;
    }
    return it->second;
}
```

- [ ] **Step 5: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <filesystem>
#include <fstream>
#include <iostream>

#include "AchievementTracker.h"
#include "MistakeTracker.h"

int main() {
    std::filesystem::create_directories("data");

    AchievementTracker achievements;
    std::cout << "Baslangicta FirstStep kilitli mi: "
              << (!achievements.isUnlocked(AchievementId::FirstStep) ? "EVET (OK)" : "HATA") << '\n';

    const bool firstUnlock = achievements.unlock(AchievementId::FirstStep);
    std::cout << "Ilk kilit acma sonucu: " << (firstUnlock ? "YENI (OK)" : "HATA") << '\n';

    const bool secondUnlock = achievements.unlock(AchievementId::FirstStep);
    std::cout << "Tekrar kilit acma sonucu: " << (!secondUnlock ? "ZATEN ACIK (OK)" : "HATA") << '\n';

    achievements.unlock(AchievementId::StreakMaster);
    std::cout << "Acik basarim sayisi: " << achievements.allUnlocked().size() << " (beklenen: 2)\n";

    const std::string testPath = "data/test_achievements.txt";
    const std::string backupPath = "data/test_achievements_corrupted_backup.txt";
    achievements.saveToFile(testPath);

    AchievementTracker loaded;
    const bool wasCorrupted = loaded.loadFromFile(testPath, backupPath);
    std::cout << "Yuklenen bozuk mu: " << (!wasCorrupted ? "HAYIR (OK)" : "HATA") << '\n';
    std::cout << "Yuklenen FirstStep acik mi: "
              << (loaded.isUnlocked(AchievementId::FirstStep) ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yuklenen StreakMaster acik mi: "
              << (loaded.isUnlocked(AchievementId::StreakMaster) ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yuklenen CodeWriter acik mi (kilitli olmali): "
              << (!loaded.isUnlocked(AchievementId::CodeWriter) ? "HAYIR (OK)" : "HATA") << '\n';

    {
        std::ofstream corruptFile(testPath, std::ios::trunc);
        corruptFile << "achievement BilinmeyenBasarim\n";
    }
    AchievementTracker corruptTracker;
    const bool detectedCorruption = corruptTracker.loadFromFile(testPath, backupPath);
    std::cout << "Bozuk dosya tespit edildi mi: " << (detectedCorruption ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yedek olusturuldu mu: " << (std::filesystem::exists(backupPath) ? "EVET (OK)" : "HATA") << '\n';

    MistakeTracker mistakes;
    std::cout << "Baslangicta soru 1 icin kayit var mi: "
              << (!mistakes.findMistake(1).has_value() ? "HAYIR (OK)" : "HATA") << '\n';
    mistakes.recordWrong(1);
    mistakes.recordWrong(1);
    const auto found = mistakes.findMistake(1);
    std::cout << "Soru 1 kaydi bulundu mu: " << (found.has_value() ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Soru 1 yanlis sayisi: " << (found.has_value() ? found->wrongCount : -1)
              << " (beklenen: 2)\n";

    return 0;
}
```

- [ ] **Step 6: Update `CMakeLists.txt`'s `add_executable` call**, inserting the two new files after `LevelSystem.h` and before `ProgressManager.h` — this is also this plan's final `add_executable` form (Tasks 4-5 don't add any new files):

```cmake
add_executable(CppMasterConsole
    src/main.cpp
    src/Enums.h
    src/UserProgress.h
    src/UserProgress.cpp
    src/Lesson.h
    src/LessonManager.h
    src/LessonManager.cpp
    src/ConsoleUI.h
    src/ConsoleUI.cpp
    src/Question.h
    src/QuestionManager.h
    src/QuestionManager.cpp
    src/QuizEngine.h
    src/QuizEngine.cpp
    src/LevelSystem.h
    src/AchievementTracker.h
    src/AchievementTracker.cpp
    src/ProgressManager.h
    src/ProgressManager.cpp
    src/MistakeTracker.h
    src/MistakeTracker.cpp
    src/Application.h
    src/Application.cpp
)
```

- [ ] **Step 7: Build and run**

Run:
```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line ends in `(OK)`. Zero compiler warnings.

- [ ] **Step 8: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/AchievementTracker.h src/AchievementTracker.cpp src/MistakeTracker.h src/MistakeTracker.cpp
git commit -m "Add AchievementTracker and MistakeTracker::findMistake"
```

---

### Task 4: Wire achievement checks into `askOneQuestion`, add "Başarımlar"

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`

Note: `CMakeLists.txt` already lists every file this task touches (Task 3 left it in final form). No `CMakeLists.txt` change is needed.

**Interfaces:**
- Consumes: `AchievementTracker`/`allAchievementIds`/`achievementDisplayName`/`achievementDescription` (Task 3), `MistakeTracker::findMistake` (Task 3), `UserProgress`'s new counters (Task 1).
- Produces: `void Application::checkAchievements(const Question& question, bool correct);`, `void Application::showAchievements();` — new private methods.

- [ ] **Step 1: Modify `src/Application.h`**

Add `#include "AchievementTracker.h"` to the include block. Add these two declarations to the private section, right after `askOneQuestion`'s declaration and before `awardXpAndCheckLevelUp`:

```cpp
    void checkAchievements(const Question& question, bool correct);
```

and, after `runDailyReview`'s declaration:

```cpp
    void showAchievements();
```

Add a new member, after `mistakes_`:

```cpp
    AchievementTracker achievements_;
```

- [ ] **Step 2: Modify `src/Application.cpp`**

Add two new file-path constants to the anonymous namespace, alongside the existing four:

```cpp
constexpr const char* kAchievementsFilePath = "data/achievements.txt";
constexpr const char* kAchievementsBackupPath = "data/achievements_corrupted_backup.txt";
```

Modify the constructor — add this block at the end, after the existing mistakes-loading block:

```cpp
    const bool achievementsCorrupted =
        achievements_.loadFromFile(kAchievementsFilePath, kAchievementsBackupPath);
    if (achievementsCorrupted) {
        ui_.printLine(
            "Uyarı: başarımlar dosyası bozuktu; yedeklendi (" +
            std::string(kAchievementsBackupPath) + ") ve sıfırlandı.");
    }
```

Modify `handleChoice`'s `case 8` — replace:
```cpp
        case 8:
            showNotYetAvailable("Başarımlar");
            break;
```
with:
```cpp
        case 8:
            showAchievements();
            break;
```

Modify `askOneQuestion` — replace this block:
```cpp
    progress_.recordAnswer(result.correct);
    if (result.correct) {
        if (mistakes_.hasMistake(question.id)) {
            mistakes_.recordCorrectRetry(question.id);
        }
    } else {
        mistakes_.recordWrong(question.id);
    }

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    progressManager_.save(progress_, kProgressFilePath, topicCount);
    mistakes_.saveToFile(kMistakesFilePath);

    return result;
```
with:
```cpp
    progress_.recordAnswer(result.correct);
    progress_.recordStreak(result.correct);
    if (result.correct) {
        progress_.recordTypedCorrectAnswer(question.type);
        if (mistakes_.hasMistake(question.id)) {
            mistakes_.recordCorrectRetry(question.id);
        }
    } else {
        mistakes_.recordWrong(question.id);
    }

    checkAchievements(question, result.correct);

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    progressManager_.save(progress_, kProgressFilePath, topicCount);
    mistakes_.saveToFile(kMistakesFilePath);

    return result;
```

Add two new methods, placed after `resetProgress`:

```cpp
void Application::checkAchievements(const Question& question, bool correct) {
    if (!correct) {
        return;
    }

    std::vector<AchievementId> newlyUnlocked;

    if (progress_.totalCorrectAnswers() == 1) {
        if (achievements_.unlock(AchievementId::FirstStep)) {
            newlyUnlocked.push_back(AchievementId::FirstStep);
        }
    }
    if (progress_.currentStreak() == 5) {
        if (achievements_.unlock(AchievementId::FlawlessFive)) {
            newlyUnlocked.push_back(AchievementId::FlawlessFive);
        }
    }
    if (progress_.currentStreak() == 10) {
        if (achievements_.unlock(AchievementId::StreakMaster)) {
            newlyUnlocked.push_back(AchievementId::StreakMaster);
        }
    }
    if (progress_.writeCodeCorrectCount() >= 10) {
        if (achievements_.unlock(AchievementId::CodeWriter)) {
            newlyUnlocked.push_back(AchievementId::CodeWriter);
        }
    }
    if (progress_.errorFixCorrectCount() >= 25) {
        if (achievements_.unlock(AchievementId::BugHunter)) {
            newlyUnlocked.push_back(AchievementId::BugHunter);
        }
    }

    const auto mistakeRecord = mistakes_.findMistake(question.id);
    if (mistakeRecord.has_value() && mistakeRecord->wrongCount >= 5) {
        if (achievements_.unlock(AchievementId::NeverGiveUp)) {
            newlyUnlocked.push_back(AchievementId::NeverGiveUp);
        }
    }

    if (newlyUnlocked.empty()) {
        return;
    }

    for (const AchievementId id : newlyUnlocked) {
        ui_.printLine("");
        ui_.printLine("Yeni başarım kazandın: " + achievementDisplayName(id));
        ui_.printLine(achievementDescription(id));
    }
    ui_.printLine("");
    achievements_.saveToFile(kAchievementsFilePath);
}
```

And, placed after `showStatistics`:

```cpp
void Application::showAchievements() {
    ui_.printLine("");
    ui_.printHeader("BAŞARIMLAR");
    for (const AchievementId id : allAchievementIds()) {
        const char marker = achievements_.isUnlocked(id) ? '+' : ' ';
        ui_.printLine(
            "[" + std::string(1, marker) + "] " + achievementDisplayName(id) + " - " +
            achievementDescription(id));
    }
    ui_.printLine("");
}
```

- [ ] **Step 3: Clean slate, then build**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt
cmake --build build
```
Expected: zero warnings.

- [ ] **Step 4: Manual verification**

```bash
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Topic 1's 8 questions, answered in order, produce a streak of 1,2,3,4,5,6,7,8 (all correct, no wrong answers to reset it). Confirm the output contains, in this order:
1. After the 1st answer (id 1, correct): `Yeni başarım kazandın: İlk Adım` / `İlk sorunu çözdün.` (first-ever correct answer).
2. After the 5th answer (id 5, correct): `Yeni başarım kazandın: Hatasız Beşli` / `Art arda 5 doğru cevap verdin.` (streak reaches 5).
3. The existing `Sonuç: 8/8 doğru (%100), kazanılan XP: 105` line, unchanged.
4. The level-up message from Task 2: `Tebrikler! Yeni seviyeye ulaştın: Değişken Ustası (Seviye 2)`.
5. The existing `Bu konu tamamlandı olarak işaretlendi.` line, unchanged.

Then, in the same run (before the final `0`), confirm the next main-menu print shows `Toplam XP: 105` and `Seviye: Değişken Ustası (Seviye 2)`.

Run a second, separate process to check "Başarımlar":
```bash
printf "8\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm the screen lists all 7 achievements; `İlk Adım` and `Hatasız Beşli` show `[+]`, the other 5 show `[ ]`.

- [ ] **Step 5: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Wire achievement checks into askOneQuestion and add Başarımlar screen"
```

---

### Task 5: Section exam ("Seviye Sınavı") with completion gate, completing phase 5

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`

**Interfaces:**
- Consumes: `askOneQuestion` (unchanged since Task 4), `awardXpAndCheckLevelUp` (Task 2), `AchievementTracker::unlock` (Task 3), `lessons_.lessonsInSection`/`progress_.statusOf` (unchanged).
- Produces: `void Application::runSectionExam();` — new private method, wired to menu option 6.

- [ ] **Step 1: Modify `src/Application.h`** — add one declaration to the private section, after `showAchievements`:

```cpp
    void runSectionExam();
```

- [ ] **Step 2: Modify `src/Application.cpp`**

Add these constants to the anonymous namespace, alongside the existing ones:

```cpp
constexpr int kExamQuestionIds[] = {
    1, 2, 3, 4, 5, 6, 19, 20, 33, 35,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 71,
};
constexpr int kExamQuestionCount = 20;
constexpr double kExamPassThreshold = 0.7;
constexpr int kExamSectionId = 1;
constexpr int kExamSectionTopicCount = 10;
constexpr double kSectionCompletionGateThreshold = 0.7;
```

Modify `handleChoice`'s `case 6` — replace:
```cpp
        case 6:
            showNotYetAvailable("Seviye Sınavı");
            break;
```
with:
```cpp
        case 6:
            runSectionExam();
            break;
```

Add the new method, placed after `runDailyReview`:

```cpp
void Application::runSectionExam() {
    int completedCount = 0;
    for (const Lesson& lesson : lessons_.lessonsInSection(kExamSectionId)) {
        const TopicStatus status = progress_.statusOf(lesson.id);
        if (status == TopicStatus::Completed || status == TopicStatus::Mastered) {
            ++completedCount;
        }
    }

    const double completionRatio =
        static_cast<double>(completedCount) / static_cast<double>(kExamSectionTopicCount);

    if (completionRatio < kSectionCompletionGateThreshold) {
        ui_.printLine("");
        ui_.printLine(
            "Bu bölümün sınavına girebilmek için konuların en az %70'ini tamamlamalısınız.");
        ui_.printLine(
            "Şu an " + std::to_string(completedCount) + "/" + std::to_string(kExamSectionTopicCount) +
            " konu tamamlanmış.");
        return;
    }

    ui_.printLine("");
    ui_.printHeader("BÖLÜM 1 SINAVI");
    ui_.printLine("20 soruluk sınav başlıyor. Geçme notu: %70.");
    ui_.printLine("");

    int correctCount = 0;
    int examXp = 0;

    for (const int questionId : kExamQuestionIds) {
        const auto question = questions_.findById(questionId);
        if (!question.has_value()) {
            continue;
        }
        const AnswerResult result = askOneQuestion(*question);
        if (result.correct) {
            ++correctCount;
            examXp += result.xpAwarded;
        }
    }

    const double scoreRatio =
        static_cast<double>(correctCount) / static_cast<double>(kExamQuestionCount);
    const int scorePercent = static_cast<int>(scoreRatio * 100.0);

    ui_.printLine(
        "Doğru: " + std::to_string(correctCount) + "/" + std::to_string(kExamQuestionCount));
    ui_.printLine("Başarı: %" + std::to_string(scorePercent));
    ui_.printLine("Kazanılan XP: " + std::to_string(examXp));
    ui_.printLine(
        std::string("Sonuç: ") + (scoreRatio >= kExamPassThreshold ? "GEÇTİN" : "KALDIN"));

    if (correctCount == kExamQuestionCount) {
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
```

- [ ] **Step 3: Clean slate, then build**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt
cmake --build build
```
Expected: zero warnings.

- [ ] **Step 4: Full manual verification (this phase's acceptance test)**

**Pass 1 — gate blocks with 0% completion:**
```bash
printf "6\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: `Bu bölümün sınavına girebilmek için konuların en az %70'ini tamamlamalısınız.` and `Şu an 0/10 konu tamamlanmış.`, no crash, no questions asked.

**Passes 2-8 — complete exactly 7 of the 10 topics (1, 3, 4, 6, 7, 8, 9, in this exact order), each as its own process, to land exactly on the 70% gate boundary. Every answer below is correct — there are no wrong answers anywhere in passes 2-9, so the correct-answer streak accumulates continuously across all of them (question counts per topic: 8, 6, 9, 9, 7, 7, 7 — running total 8, 14, 23, 32, 39, 46, 53) and the XP total accumulates continuously too (topic XP totals 105, 75, 125, 135, 95, 95, 95 — running total 105, 180, 305, 440, 535, 630, 725):**
```bash
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
printf "1\n3\nb\nb\n1\n2\nendl\nbuffer\n0\n" | ./build/Debug/CppMasterConsole.exe
printf "1\n4\nb\nd\n1\n2\ncin\n>>\nb\ncin >> yas;\n2 3 1\n0\n" | ./build/Debug/CppMasterConsole.exe
printf "1\n6\nb\nc\n2\n1\nint\n7\ntoplam + 5\n8\nint sayi;\ncin >> sayi;\ncout << sayi;\nBITIR\n0\n" | ./build/Debug/CppMasterConsole.exe
printf "1\n7\nc\nb\n1\n2\ndouble\n6\ndouble ortalama = 87.5;\n0\n" | ./build/Debug/CppMasterConsole.exe
printf "1\n8\nb\nb\n1\n2\nchar\ntek\nchar harf = 'A';\n0\n" | ./build/Debug/CppMasterConsole.exe
printf "1\n9\nb\nb\n1\n2\nbool\n0\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm each of these 7 runs ends with `Bu konu tamamlandı olarak işaretlendi.`. At this point exactly 7 of the 10 topics are `Completed` (topics 2, 5, 10 are deliberately left untouched).

Because every answer across passes 2-9 is correct, these precise, pre-computed events also occur — confirm each one at the pass/point named, not just the topic-completion lines:
- **Pass 2 (topic 1), 1st question (id 1):** this is the first-ever correct answer → `Yeni başarım kazandın: İlk Adım` / `İlk sorunu çözdün.`
- **Pass 2 (topic 1), 5th question (id 5):** streak reaches 5 → `Yeni başarım kazandın: Hatasız Beşli` / `Art arda 5 doğru cevap verdin.`
- **Pass 2, end of session:** XP reaches 105 (crosses the 50-XP level-2 threshold) → `Tebrikler! Yeni seviyeye ulaştın: Değişken Ustası (Seviye 2)`
- **Pass 3 (topic 3), 2nd question (id 14):** this is the 10th correct answer overall (8 from topic 1 + 2 from topic 3) → `Yeni başarım kazandın: Seri Ustası` / `Art arda 10 doğru cevap verdin.`
- **Pass 3, end of session:** XP reaches 180 (crosses the 120-XP level-3 threshold) → `Tebrikler! Yeni seviyeye ulaştın: Koşul Çözücü (Seviye 3)`
- **Pass 4 (topic 4), end of session:** XP reaches 305 (crosses the 220-XP level-4 threshold) → `Tebrikler! Yeni seviyeye ulaştın: Döngü Ustası (Seviye 4)`
- **Pass 5 (topic 6), end of session:** XP reaches 440 (crosses the 350-XP level-5 threshold) → `Tebrikler! Yeni seviyeye ulaştın: Dizi Kaşifi (Seviye 5)`
- **Pass 6 (topic 7), end of session:** XP reaches 535 (crosses the 500-XP level-6 threshold) → `Tebrikler! Yeni seviyeye ulaştın: Fonksiyon Geliştiricisi (Seviye 6)`
- **Pass 7 (topic 8), end of session:** XP reaches 630 — **no level-up this pass** (630 is still below the 700-XP level-7 threshold). Confirm no `Tebrikler!` line appears here.
- **Pass 8 (topic 9), end of session:** XP reaches 725 (crosses the 700-XP level-7 threshold) → `Tebrikler! Yeni seviyeye ulaştın: Pointer Öğrencisi (Seviye 7)`

No other achievement thresholds are reachable yet: `Kod Yazarı`/`Hata Avcısı` need 10/25 cumulative correct answers of their respective types and only 1-2 such questions have been answered so far; `Pes Etmeyen` never fires because there are no wrong answers anywhere in this sequence, so no `MistakeRecord` ever exists to retry.

**Pass 9 — gate now passes at exactly 70%, exam runs, all-correct:**

All 20 exam question ids' correct answers are already established from phases 2-3: `1=b, 2=c, 3=2, 4=1, 5=cout, 6=iostream, 19=b, 20=d, 33=2, 35=int, 61="toplam + 5", 62=b, 63=8, 64=0, 65="int yas = 20;", 66="char harf = 'A';", 67="double ortalama = 87.5;", 68="cin >> yas;", 69="2 3 1", 71=` a multi-line `BITIR`-terminated submission containing `cin`, `>>`, `cout`, `<<`.
```bash
printf "6\nb\nc\n2\n1\ncout\niostream\nb\nd\n2\nint\ntoplam + 5\nb\n8\n0\nint yas = 20;\nchar harf = 'A';\ndouble ortalama = 87.5;\ncin >> yas;\n2 3 1\nint sayi;\ncin >> sayi;\ncout << sayi;\nBITIR\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: no gate-blocked message this time (70% reached, exactly at the boundary since `0.7 < 0.7` is false); all 20 exam questions asked in the fixed order given in `kExamQuestionIds`; final lines read exactly `Doğru: 20/20`, `Başarı: %100`, `Kazanılan XP: 300`, `Sonuç: GEÇTİN`; immediately followed by `Yeni başarım kazandın: Mükemmel Sınav` / `Bir bölüm sınavından %100 aldın.`; and, since the pre-exam total was 725 XP (level 7) and this exam adds exactly 300 XP for a new total of 1025 (which crosses the 950-XP level-8 threshold), a final `Tebrikler! Yeni seviyeye ulaştın: Nesne Tasarımcısı (Seviye 8)` line. The next main-menu print (before the final `0` is consumed) should show `Toplam XP: 1025` and `Seviye: Nesne Tasarımcısı (Seviye 8)`.

**Pass 10 — confirm "Başarımlar" reflects everything earned:**
```bash
printf "8\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm exactly 4 of the 7 show `[+]`: `İlk Adım`, `Hatasız Beşli`, `Seri Ustası`, `Mükemmel Sınav`. The remaining 3 show `[ ]`: `Kod Yazarı`, `Hata Avcısı`, `Pes Etmeyen` (none of their conditions were reached — no wrong answers occurred anywhere in this verification, and neither `WriteCode` nor `FindError`/`FixCode` correct answers reached their 10/25 thresholds across the 1-2 such questions actually answered).

- [ ] **Step 5: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Add Bölüm 1 section exam with completion gate, completing phase 5"
```

---

## Post-plan note

This completes phase 5 (Meta Systems) within the scope recorded in the
design doc: leveling, 7 reachable achievements, and a Bölüm-1-only section
exam. Final exam, adaptive difficulty, the other 5 achievements, and exams
for sections 2-10 all require topic/question content this project hasn't
authored yet — they wait for whichever later phase adds that content
(dynamic question generation, or further hand-authored topics). Phase 6
gets its own brainstorming → spec → plan cycle before implementation
starts.

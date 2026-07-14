# CppMaster Console — Persistence + Review Loop (Phase 4) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make progress survive a restart, track wrong answers durably, and wire menu options 3 ("Günlük Tekrar"), 4 ("Hatalarımı Çöz"), 7 ("İstatistiklerim"), and 10 ("İlerlemeyi Sıfırla") to real, honest behavior.

**Architecture:** Two new stateless-ish classes (`ProgressManager` for `data/progress.txt`, `MistakeTracker` for `data/mistakes.txt`, both with corruption-safe load/save), a small `UserProgress` extension (answered/correct counters), a `QuestionManager::findById` addition, and a behavior-preserving extraction of `Application::runTopicQuiz`'s per-question loop into a shared `askOneQuestion` that every quiz-like flow reuses.

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only (`<filesystem>`, `<fstream>`, `<chrono>` — no external date/JSON library). Still no test framework.

**Spec:** `docs/superpowers/specs/2026-07-14-persistence-review-loop-design.md`

## Global Constraints

- C++20 required, same CMake settings as before.
- No external libraries — standard library only.
- Compiler warnings: MSVC `/W4 /permissive-`; GCC/Clang `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`. Zero warnings required.
- No `using namespace std;` anywhere.
- No fake/placeholder code. Menu option 2 ("Hızlı Test") stays honestly "not yet available" — out of this phase's scope.
- Dates are Unix epoch seconds via `std::chrono::system_clock::to_time_t`/`from_time_t` — no external date library, no calendar-string parsing.
- Any malformed line in `data/progress.txt` or `data/mistakes.txt` marks the *whole file* corrupt: copy it to the matching `*_corrupted_backup.txt` path (overwriting any previous backup) and continue with a fresh, empty in-memory state. A *missing* file (first run) is not corruption — just start fresh, no backup, no warning.
- **Before running any task's manual verification below, delete `data/progress.txt` and `data/mistakes.txt` if they exist**, so every task's hand-computed expected values start from a clean slate rather than depending on what earlier tasks' test runs happened to leave behind.

---

### Task 1: `UserProgress` counters + `ProgressManager`

**Files:**
- Modify: `src/UserProgress.h`
- Modify: `src/UserProgress.cpp`
- Create: `src/ProgressManager.h`
- Create: `src/ProgressManager.cpp`
- Modify: `CMakeLists.txt`
- Modify (temporarily, superseded in Task 3): `src/main.cpp`

**Interfaces:**
- Consumes: `TopicStatus` (unchanged).
- Produces:
  - `UserProgress` gains `int totalQuestionsAnswered() const`, `int totalCorrectAnswers() const`, `void recordAnswer(bool correct)`, `void setAnsweredCounters(int totalAnswered, int totalCorrect)`. Existing methods unchanged.
  - `struct ProgressLoadResult { UserProgress progress; bool wasCorrupted; };`
  - `class ProgressManager { public: ProgressLoadResult load(const std::string&, const std::string&, int) const; void save(const UserProgress&, const std::string&, int) const; };`

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

private:
    std::unordered_map<int, TopicStatus> statusByTopicId_;
    int totalXp_ = 0;
    int totalQuestionsAnswered_ = 0;
    int totalCorrectAnswers_ = 0;
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
```

- [ ] **Step 3: Create `src/ProgressManager.h`**

```cpp
#pragma once

#include <string>

#include "UserProgress.h"

struct ProgressLoadResult {
    UserProgress progress;
    bool wasCorrupted;
};

class ProgressManager {
public:
    [[nodiscard]] ProgressLoadResult load(
        const std::string& filePath, const std::string& backupPath, int topicCount) const;
    void save(const UserProgress& progress, const std::string& filePath, int topicCount) const;
};
```

- [ ] **Step 4: Create `src/ProgressManager.cpp`**

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
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        file << "topic " << topicId << ' ' << statusName(progress.statusOf(topicId)) << '\n';
    }
}
```

- [ ] **Step 5: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <filesystem>
#include <fstream>
#include <iostream>

#include "ProgressManager.h"
#include "UserProgress.h"

int main() {
    std::filesystem::create_directories("data");

    ProgressManager manager;
    const std::string testPath = "data/test_progress.txt";
    const std::string backupPath = "data/test_progress_corrupted_backup.txt";

    UserProgress original(10);
    original.addXp(150);
    original.setStatus(3, TopicStatus::Completed);
    original.setStatus(5, TopicStatus::Learning);
    original.recordAnswer(true);
    original.recordAnswer(false);
    original.recordAnswer(true);

    manager.save(original, testPath, 10);

    const auto loaded = manager.load(testPath, backupPath, 10);
    std::cout << "Yuklenen bozuk mu: " << (loaded.wasCorrupted ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Yuklenen XP: " << loaded.progress.totalXp() << " (beklenen: 150)\n";
    std::cout << "Konu 3 durumu: "
              << (loaded.progress.statusOf(3) == TopicStatus::Completed ? "Completed (OK)" : "HATA") << '\n';
    std::cout << "Konu 5 durumu: "
              << (loaded.progress.statusOf(5) == TopicStatus::Learning ? "Learning (OK)" : "HATA") << '\n';
    std::cout << "Konu 1 durumu (hic dokunulmadi): "
              << (loaded.progress.statusOf(1) == TopicStatus::NotStarted ? "NotStarted (OK)" : "HATA") << '\n';
    std::cout << "Cevaplanan: " << loaded.progress.totalQuestionsAnswered() << " (beklenen: 3)\n";
    std::cout << "Dogru: " << loaded.progress.totalCorrectAnswers() << " (beklenen: 2)\n";

    const auto missing = manager.load("data/does_not_exist.txt", backupPath, 10);
    std::cout << "Eksik dosya bozuk mu: " << (missing.wasCorrupted ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Eksik dosya XP: " << missing.progress.totalXp() << " (beklenen: 0)\n";

    {
        std::ofstream corruptFile(testPath, std::ios::trunc);
        corruptFile << "xp not_a_number\n";
    }
    const auto corrupted = manager.load(testPath, backupPath, 10);
    std::cout << "Bozuk dosya tespit edildi mi: " << (corrupted.wasCorrupted ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Bozuk sonrasi XP (taze): " << corrupted.progress.totalXp() << " (beklenen: 0)\n";
    std::cout << "Yedek dosyasi olusturuldu mu: "
              << (std::filesystem::exists(backupPath) ? "EVET (OK)" : "HATA") << '\n';

    return 0;
}
```

- [ ] **Step 6: Update `CMakeLists.txt`'s `add_executable` call**, inserting the two new files after `QuizEngine.cpp` and before `Application.h`:

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
    src/ProgressManager.h
    src/ProgressManager.cpp
    src/Application.h
    src/Application.cpp
)
```

- [ ] **Step 7: Build and run**

Run:
```bash
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line ends in `(OK)`. Zero compiler warnings.

- [ ] **Step 8: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/UserProgress.h src/UserProgress.cpp src/ProgressManager.h src/ProgressManager.cpp
git commit -m "Add UserProgress answer counters and ProgressManager persistence"
```

---

### Task 2: `MistakeTracker` + `QuestionManager::findById`

**Files:**
- Modify: `src/QuestionManager.h`
- Modify: `src/QuestionManager.cpp`
- Create: `src/MistakeTracker.h`
- Create: `src/MistakeTracker.cpp`
- Modify: `CMakeLists.txt`
- Modify (temporarily, superseded in Task 3): `src/main.cpp`

**Interfaces:**
- Consumes: `Question` (unchanged).
- Produces:
  - `QuestionManager` gains `std::optional<Question> findById(int questionId) const;`.
  - `struct MistakeRecord { int questionId; std::chrono::system_clock::time_point firstWrongAt; std::chrono::system_clock::time_point lastWrongAt; int wrongCount; int correctAfterWrongCount; };`
  - `class MistakeTracker { public: void recordWrong(int); void recordCorrectRetry(int); bool hasMistake(int) const; std::vector<MistakeRecord> allMistakesOldestFirst() const; bool loadFromFile(const std::string&, const std::string&); void saveToFile(const std::string&) const; };`

- [ ] **Step 1: Modify `src/QuestionManager.h`** — full file:

```cpp
#pragma once

#include <optional>
#include <vector>

#include "Question.h"

class QuestionManager {
public:
    QuestionManager();

    [[nodiscard]] std::vector<Question> questionsForTopic(int topicId) const;
    [[nodiscard]] std::optional<Question> findById(int questionId) const;

private:
    std::vector<Question> questions_;
};
```

- [ ] **Step 2: Modify `src/QuestionManager.cpp`**

Add `#include <algorithm>` to the top of the file's include block (alongside the existing `#include "QuestionManager.h"`), and append this method definition at the very end of the file, after `questionsForTopic`'s closing brace:

```cpp
std::optional<Question> QuestionManager::findById(int questionId) const {
    const auto it = std::ranges::find_if(
        questions_, [questionId](const Question& question) { return question.id == questionId; });
    if (it == questions_.end()) {
        return std::nullopt;
    }
    return *it;
}
```

- [ ] **Step 3: Create `src/MistakeTracker.h`**

```cpp
#pragma once

#include <chrono>
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
    [[nodiscard]] std::vector<MistakeRecord> allMistakesOldestFirst() const;

    [[nodiscard]] bool loadFromFile(const std::string& filePath, const std::string& backupPath);
    void saveToFile(const std::string& filePath) const;

private:
    std::unordered_map<int, MistakeRecord> recordsByQuestionId_;
};
```

- [ ] **Step 4: Create `src/MistakeTracker.cpp`**

```cpp
#include "MistakeTracker.h"

#include <algorithm>
#include <cstddef>
#include <ctime>
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

bool tryParseEpochSeconds(const std::string& text, std::chrono::system_clock::time_point& outTime) {
    int seconds = 0;
    if (!tryParseInt(text, seconds)) {
        return false;
    }
    outTime = std::chrono::system_clock::from_time_t(static_cast<std::time_t>(seconds));
    return true;
}

}  // namespace

void MistakeTracker::recordWrong(int questionId) {
    const auto now = std::chrono::system_clock::now();
    const auto it = recordsByQuestionId_.find(questionId);
    if (it == recordsByQuestionId_.end()) {
        MistakeRecord record;
        record.questionId = questionId;
        record.firstWrongAt = now;
        record.lastWrongAt = now;
        record.wrongCount = 1;
        record.correctAfterWrongCount = 0;
        recordsByQuestionId_[questionId] = record;
    } else {
        it->second.lastWrongAt = now;
        ++it->second.wrongCount;
    }
}

void MistakeTracker::recordCorrectRetry(int questionId) {
    const auto it = recordsByQuestionId_.find(questionId);
    if (it == recordsByQuestionId_.end()) {
        return;
    }
    ++it->second.correctAfterWrongCount;
}

bool MistakeTracker::hasMistake(int questionId) const {
    return recordsByQuestionId_.find(questionId) != recordsByQuestionId_.end();
}

std::vector<MistakeRecord> MistakeTracker::allMistakesOldestFirst() const {
    std::vector<MistakeRecord> result;
    result.reserve(recordsByQuestionId_.size());
    for (const auto& entry : recordsByQuestionId_) {
        result.push_back(entry.second);
    }
    std::ranges::sort(result, [](const MistakeRecord& left, const MistakeRecord& right) {
        return left.lastWrongAt < right.lastWrongAt;
    });
    return result;
}

bool MistakeTracker::loadFromFile(const std::string& filePath, const std::string& backupPath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    std::unordered_map<int, MistakeRecord> parsedRecords;
    bool corrupted = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream lineStream(line);
        std::string recordType;
        lineStream >> recordType;

        if (recordType != "mistake") {
            corrupted = true;
            break;
        }

        std::string questionIdText;
        std::string firstWrongText;
        std::string lastWrongText;
        std::string wrongCountText;
        std::string correctAfterWrongText;
        lineStream >> questionIdText >> firstWrongText >> lastWrongText >> wrongCountText >>
            correctAfterWrongText;

        MistakeRecord record;
        if (!tryParseInt(questionIdText, record.questionId) ||
            !tryParseEpochSeconds(firstWrongText, record.firstWrongAt) ||
            !tryParseEpochSeconds(lastWrongText, record.lastWrongAt) ||
            !tryParseInt(wrongCountText, record.wrongCount) ||
            !tryParseInt(correctAfterWrongText, record.correctAfterWrongCount)) {
            corrupted = true;
            break;
        }
        parsedRecords[record.questionId] = record;
    }

    if (corrupted) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        recordsByQuestionId_.clear();
        return true;
    }

    recordsByQuestionId_ = std::move(parsedRecords);
    return false;
}

void MistakeTracker::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        return;
    }
    for (const auto& entry : recordsByQuestionId_) {
        const MistakeRecord& record = entry.second;
        file << "mistake " << record.questionId << ' '
             << std::chrono::system_clock::to_time_t(record.firstWrongAt) << ' '
             << std::chrono::system_clock::to_time_t(record.lastWrongAt) << ' '
             << record.wrongCount << ' ' << record.correctAfterWrongCount << '\n';
    }
}
```

- [ ] **Step 5: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <filesystem>
#include <fstream>
#include <iostream>

#include "MistakeTracker.h"
#include "QuestionManager.h"

int main() {
    std::filesystem::create_directories("data");

    QuestionManager questions;
    const auto found = questions.findById(1);
    std::cout << "Soru 1 bulundu mu: " << (found.has_value() ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Soru 1 prompt dolu mu: "
              << (found.has_value() && !found->prompt.empty() ? "EVET (OK)" : "HATA") << '\n';
    const auto missingQuestion = questions.findById(9999);
    std::cout << "Soru 9999 bulundu mu: " << (missingQuestion.has_value() ? "EVET (HATA)" : "HAYIR (OK)") << '\n';

    MistakeTracker tracker;
    std::cout << "Baslangicta soru 1 yanlis mi: " << (!tracker.hasMistake(1) ? "HAYIR (OK)" : "HATA") << '\n';

    tracker.recordWrong(1);
    std::cout << "Bir kez yanlis sonrasi soru 1 yanlis mi: " << (tracker.hasMistake(1) ? "EVET (OK)" : "HATA") << '\n';

    tracker.recordWrong(1);
    tracker.recordWrong(2);

    const auto mistakesBeforeSave = tracker.allMistakesOldestFirst();
    std::cout << "Kayitli yanlis sayisi: " << mistakesBeforeSave.size() << " (beklenen: 2)\n";

    tracker.recordCorrectRetry(1);

    const std::string testPath = "data/test_mistakes.txt";
    const std::string backupPath = "data/test_mistakes_corrupted_backup.txt";
    tracker.saveToFile(testPath);

    MistakeTracker loadedTracker;
    const bool wasCorrupted = loadedTracker.loadFromFile(testPath, backupPath);
    std::cout << "Yuklenen bozuk mu: " << (!wasCorrupted ? "HAYIR (OK)" : "HATA") << '\n';

    const auto loadedMistakes = loadedTracker.allMistakesOldestFirst();
    std::cout << "Yuklenen yanlis sayisi: " << loadedMistakes.size() << " (beklenen: 2)\n";

    bool foundQuestion1 = false;
    for (const auto& record : loadedMistakes) {
        if (record.questionId == 1) {
            foundQuestion1 = true;
            std::cout << "Soru 1 yanlis sayisi: " << record.wrongCount << " (beklenen: 2)\n";
            std::cout << "Soru 1 dogru-tekrar sayisi: " << record.correctAfterWrongCount << " (beklenen: 1)\n";
        }
    }
    std::cout << "Soru 1 yuklenenler icinde bulundu mu: " << (foundQuestion1 ? "EVET (OK)" : "HATA") << '\n';

    {
        std::ofstream corruptFile(testPath, std::ios::trunc);
        corruptFile << "mistake not_a_number\n";
    }
    MistakeTracker corruptTracker;
    const bool detectedCorruption = corruptTracker.loadFromFile(testPath, backupPath);
    std::cout << "Bozuk dosya tespit edildi mi: " << (detectedCorruption ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yedek olusturuldu mu: " << (std::filesystem::exists(backupPath) ? "EVET (OK)" : "HATA") << '\n';

    return 0;
}
```

- [ ] **Step 6: Update `CMakeLists.txt`'s `add_executable` call**, inserting the two new files after `ProgressManager.cpp` and before `Application.h` — this is also this plan's final `add_executable` form (Tasks 3-6 don't add any new files):

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
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line ends in `(OK)`. Zero compiler warnings.

- [ ] **Step 8: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/QuestionManager.h src/QuestionManager.cpp src/MistakeTracker.h src/MistakeTracker.cpp
git commit -m "Add MistakeTracker persistence and QuestionManager::findById"
```

---

### Task 3: Extract `askOneQuestion`, wire per-answer tracking and saving

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`
- Modify: `src/main.cpp`

Note: `CMakeLists.txt` already lists every file this task touches (Task 2 left it in final form). No `CMakeLists.txt` change is needed.

**Before anything else in this task:** Tasks 1 and 2 each temporarily repurposed `src/main.cpp` as their own scratch verification code (per their own steps) and did not restore it — this is a known, intentional pattern in this plan (it also happened in phases 2 and 3, each time fixed by the task that next needed the real entry point). This task's own verification (Step 4) needs the real `Application` entry point to run at all, so restore `src/main.cpp` to exactly:
```cpp
#include "Application.h"

int main() {
    Application app;
    app.run();
    return 0;
}
```
before proceeding to Step 1. Commit this restoration as its own small commit, separate from the `Application.h`/`.cpp` changes below (matching the precedent from phases 2 and 3): `git add src/main.cpp && git commit -m "Restore src/main.cpp to real entry-point form before phase 4 wiring verification"`.

**Interfaces:**
- Consumes: `UserProgress::recordAnswer` (Task 1), `ProgressManager::save` (Task 1), `MistakeTracker::recordWrong`/`recordCorrectRetry`/`hasMistake`/`saveToFile` (Task 2).
- Produces: `AnswerResult Application::askOneQuestion(const Question& question);` — new private method other flows will call in later tasks. `runTopicQuiz`'s own visible behavior (prompts, options, feedback text, final score/XP/status lines) must be **byte-for-byte identical** to before this task — only its internal structure changes, plus the new (invisible) side effect of writing `data/progress.txt`/`data/mistakes.txt` after every question.

- [ ] **Step 1: Modify `src/Application.h`** — full file:

```cpp
#pragma once

#include <string>

#include "ConsoleUI.h"
#include "LessonManager.h"
#include "MistakeTracker.h"
#include "ProgressManager.h"
#include "QuestionManager.h"
#include "QuizEngine.h"
#include "UserProgress.h"

class Application {
public:
    Application();

    void run();

private:
    void showMainMenu();
    void handleChoice(int choice);
    void showTopicBrowser();
    void openTopic(int topicId);
    void showLessonContent(const Lesson& lesson);
    void runTopicQuiz(int topicId);
    AnswerResult askOneQuestion(const Question& question);
    void showNotYetAvailable(const std::string& featureName);
    void ensureDataDirectoryExists();

    ConsoleUI ui_;
    LessonManager lessons_;
    QuestionManager questions_;
    QuizEngine quizEngine_;
    UserProgress progress_;
    ProgressManager progressManager_;
    MistakeTracker mistakes_;
    bool running_ = true;
};
```

- [ ] **Step 2: Modify `src/Application.cpp`**

Add four new file-scope constants to the anonymous namespace (alongside the existing `kMinChoice`/`kMaxChoice`/etc.):

```cpp
constexpr const char* kProgressFilePath = "data/progress.txt";
constexpr const char* kProgressBackupPath = "data/progress_corrupted_backup.txt";
constexpr const char* kMistakesFilePath = "data/mistakes.txt";
constexpr const char* kMistakesBackupPath = "data/mistakes_corrupted_backup.txt";
```

Replace `runTopicQuiz` (the whole function) with this version, and add `askOneQuestion` as a new function immediately after it:

```cpp
void Application::runTopicQuiz(int topicId) {
    const auto quizQuestions = questions_.questionsForTopic(topicId);

    ui_.printLine("Konu testi başlıyor (" + std::to_string(quizQuestions.size()) + " soru).");
    ui_.printLine("");

    int correctCount = 0;
    int sessionXp = 0;

    for (const Question& question : quizQuestions) {
        const AnswerResult result = askOneQuestion(question);
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }
    }

    const auto totalQuestions = static_cast<int>(quizQuestions.size());
    const double successRatio =
        totalQuestions == 0 ? 0.0
                            : static_cast<double>(correctCount) / static_cast<double>(totalQuestions);
    const int successPercent = static_cast<int>(successRatio * 100.0);

    ui_.printLine(
        "Sonuç: " + std::to_string(correctCount) + "/" + std::to_string(totalQuestions) +
        " doğru (%" + std::to_string(successPercent) + "), kazanılan XP: " +
        std::to_string(sessionXp));

    progress_.addXp(sessionXp);

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

AnswerResult Application::askOneQuestion(const Question& question) {
    ui_.printLine(question.prompt);

    if (question.type == QuestionType::MultipleChoice) {
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            ui_.printLine(
                std::string(1, optionLetter(index)) + ") " + question.options[index]);
        }
    } else if (question.type == QuestionType::TrueFalse) {
        ui_.printLine("1. Doğru");
        ui_.printLine("2. Yanlış");
    } else if (question.type == QuestionType::OrderCode) {
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            ui_.printLine(
                std::to_string(static_cast<int>(index) + 1) + ". " + question.options[index]);
        }
    }

    std::string rawAnswer;
    if (question.type == QuestionType::WriteCode) {
        ui_.printLine(
            "Kodunuzu birden fazla satır halinde girebilirsiniz. Bitirmek için BITIR yazıp Enter'a basın.");
        rawAnswer = ui_.readMultilineCode();
    } else {
        rawAnswer = ui_.readLine("Cevabınız: ");
    }
    const AnswerResult result = quizEngine_.evaluate(question, rawAnswer);

    if (result.correct) {
        ui_.printLine("Doğru! (+" + std::to_string(result.xpAwarded) + " XP)");
    } else {
        ui_.printLine("");
        ui_.printLine("Yanlış cevap.");
        ui_.printLine("");
        ui_.printLine("Senin cevabın:");
        ui_.printLine(rawAnswer);
        ui_.printLine("");
        ui_.printLine("Doğru cevap:");
        ui_.printLine(result.correctAnswerDisplay);
        ui_.printLine("");
        ui_.printLine("Açıklama:");
        ui_.printLine(question.explanation);
    }
    ui_.printLine("");

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
}
```

No other part of `Application.cpp` changes in this task.

- [ ] **Step 3: Clean slate, then build**

```bash
rm -f data/progress.txt data/mistakes.txt
cmake --build build
```
Expected: build succeeds with zero warnings.

- [ ] **Step 4: Regression check — `runTopicQuiz`'s visible output must be unchanged**

Run the exact same topic-1 sequence used in phase 3's own acceptance test:
```bash
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm the visible output is identical to phase 3's result: all 8 questions answered correctly, final line
`Sonuç: 8/8 doğru (%100), kazanılan XP: 105`, `Bu konu tamamlandı olarak işaretlendi.`, and `Toplam XP: 105` back at the main menu. The only *new* thing (not visible in the terminal) is that `data/progress.txt` and `data/mistakes.txt` now exist:
```bash
cat data/progress.txt
```
Expected: a line `xp 105`, a line `answered 8`, a line `correct 8`, and `topic 1 Completed` among the 100 `topic` lines.
```bash
cat data/mistakes.txt
```
Expected: **empty file** (zero bytes) — every answer in this pass was correct, so no mistake was ever recorded.

- [ ] **Step 5: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Extract askOneQuestion from runTopicQuiz; record answers and save after every question"
```

---

### Task 4: Load on startup, save on exit, wire "İlerlemeyi Sıfırla"

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`

**Interfaces:**
- Consumes: `ProgressManager::load` (Task 1), `MistakeTracker::loadFromFile` (Task 2).
- Produces: `void Application::resetProgress();` (new private method, wired to menu option 10).

- [ ] **Step 1: Modify `src/Application.h`** — add one new private method declaration, so the private section reads:

```cpp
private:
    void showMainMenu();
    void handleChoice(int choice);
    void showTopicBrowser();
    void openTopic(int topicId);
    void showLessonContent(const Lesson& lesson);
    void runTopicQuiz(int topicId);
    AnswerResult askOneQuestion(const Question& question);
    void resetProgress();
    void showNotYetAvailable(const std::string& featureName);
    void ensureDataDirectoryExists();
```

- [ ] **Step 2: Modify `Application::Application()`** in `src/Application.cpp` — replace the constructor with:

```cpp
Application::Application()
    : progress_(static_cast<int>(lessons_.allLessons().size())) {
    ensureDataDirectoryExists();

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    const auto loadResult = progressManager_.load(kProgressFilePath, kProgressBackupPath, topicCount);
    progress_ = loadResult.progress;
    if (loadResult.wasCorrupted) {
        ui_.printLine(
            "Uyarı: ilerleme dosyası bozuktu; yedeklendi (" + std::string(kProgressBackupPath) +
            ") ve ilerlemeniz sıfırlandı.");
    }

    const bool mistakesCorrupted = mistakes_.loadFromFile(kMistakesFilePath, kMistakesBackupPath);
    if (mistakesCorrupted) {
        ui_.printLine(
            "Uyarı: yanlış kayıtları dosyası bozuktu; yedeklendi (" +
            std::string(kMistakesBackupPath) + ") ve sıfırlandı.");
    }
}
```

- [ ] **Step 3: Modify `handleChoice`'s `case 10`** in `src/Application.cpp` — replace:

```cpp
        case 10:
            showNotYetAvailable("İlerlemeyi Sıfırla");
            break;
```

with:

```cpp
        case 10:
            resetProgress();
            break;
```

- [ ] **Step 4: Add `resetProgress`** as a new method in `src/Application.cpp`, placed after `askOneQuestion`:

```cpp
void Application::resetProgress() {
    ui_.printLine("");
    ui_.printLine("İlerlemenizi sıfırlamak istediğinizden emin misiniz? (evet/hayır):");
    const std::string confirmation = ui_.readLine("Cevabınız: ");
    if (confirmation != "evet") {
        ui_.printLine("İptal edildi.");
        return;
    }

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    progress_ = UserProgress(topicCount);
    mistakes_ = MistakeTracker();

    progressManager_.save(progress_, kProgressFilePath, topicCount);
    mistakes_.saveToFile(kMistakesFilePath);

    ui_.printLine("İlerlemeniz sıfırlandı.");
}
```

- [ ] **Step 5: Clean slate, then build**

```bash
rm -f data/progress.txt data/mistakes.txt
cmake --build build
```
Expected: zero warnings.

- [ ] **Step 6: Full manual verification — persistence across separate process runs**

**Pass A (first run — earn XP and complete topic 1):**
```bash
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: `Sonuç: 8/8 doğru (%100), kazanılan XP: 105`, `Bu konu tamamlandı olarak işaretlendi.`, `Toplam XP: 105`. No corruption warning (first run, no pre-existing file).

**Pass B (second, separate process run — confirm it survived):**
```bash
printf "1\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: the very first main-menu print already shows `Toplam XP: 105` (loaded from disk, not recomputed); selecting `1` shows topic 1 with the `[+]` marker (not `[ ]`); `0`/`0` return to menu and exit cleanly.

**Pass C (third run — reset):**
```bash
printf "10\nevet\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: the confirmation prompt appears, `evet` triggers `İlerlemeniz sıfırlandı.`, and the main menu re-print before exiting shows `Toplam XP: 0`.

**Pass D (fourth run — confirm the reset itself persisted):**
```bash
printf "0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: `Toplam XP: 0` on the very first main-menu print (proving Pass C's reset was actually written to disk, not just held in that process's memory).

**Pass E (cancel path):**
```bash
rm -f data/progress.txt data/mistakes.txt
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n10\nhayir\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: after earning 105 XP again, selecting `10` then answering `hayir` prints `İptal edildi.` and the subsequent main-menu print still shows `Toplam XP: 105` (nothing was reset).

- [ ] **Step 7: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Load progress/mistakes on startup; wire İlerlemeyi Sıfırla"
```

---

### Task 5: Wire "Hatalarımı Çöz" and "İstatistiklerim"

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`

**Interfaces:**
- Consumes: `MistakeTracker::allMistakesOldestFirst` (Task 2), `QuestionManager::findById` (Task 2), `askOneQuestion` (Task 3).
- Produces: `void Application::showMistakeReview();`, `void Application::runMistakeQuestions(const std::vector<MistakeRecord>&);`, `void Application::showStatistics();` — all new private methods.

- [ ] **Step 1: Modify `src/Application.h`**

Add `#include <vector>` to the top include block, and these three method declarations to the private section (after `resetProgress`):

```cpp
    void showMistakeReview();
    void runMistakeQuestions(const std::vector<MistakeRecord>& mistakesToAsk);
    void showStatistics();
```

- [ ] **Step 2: Modify `handleChoice`'s `case 4` and `case 7`** in `src/Application.cpp` — replace:

```cpp
        case 4:
            showNotYetAvailable("Hatalarımı Çöz");
            break;
```
with:
```cpp
        case 4:
            showMistakeReview();
            break;
```

and replace:
```cpp
        case 7:
            showNotYetAvailable("İstatistiklerim");
            break;
```
with:
```cpp
        case 7:
            showStatistics();
            break;
```

- [ ] **Step 3: Add three new methods** in `src/Application.cpp`, placed after `resetProgress`:

```cpp
void Application::showMistakeReview() {
    const auto mistakes = mistakes_.allMistakesOldestFirst();
    if (mistakes.empty()) {
        ui_.printLine("");
        ui_.printLine("Henüz kaydedilmiş bir yanlışınız yok!");
        return;
    }

    ui_.printLine("");
    ui_.printLine("Kayıtlı yanlışlarınız (" + std::to_string(mistakes.size()) + " soru):");
    ui_.printLine("");
    runMistakeQuestions(mistakes);
}

void Application::runMistakeQuestions(const std::vector<MistakeRecord>& mistakesToAsk) {
    int correctCount = 0;
    int sessionXp = 0;

    for (const MistakeRecord& mistake : mistakesToAsk) {
        const auto question = questions_.findById(mistake.questionId);
        if (!question.has_value()) {
            continue;
        }
        const AnswerResult result = askOneQuestion(*question);
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }
    }

    progress_.addXp(sessionXp);
    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));

    ui_.printLine(
        "Tamamlandı: " + std::to_string(correctCount) + "/" + std::to_string(mistakesToAsk.size()) +
        " doğru, kazanılan XP: " + std::to_string(sessionXp));
    ui_.printLine("");
}

void Application::showStatistics() {
    ui_.printLine("");
    ui_.printHeader("İSTATİSTİKLERİM");

    const int topicCount = static_cast<int>(lessons_.allLessons().size());
    int notStarted = 0;
    int learning = 0;
    int completed = 0;
    int mastered = 0;
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        switch (progress_.statusOf(topicId)) {
            case TopicStatus::NotStarted:
                ++notStarted;
                break;
            case TopicStatus::Learning:
                ++learning;
                break;
            case TopicStatus::Completed:
                ++completed;
                break;
            case TopicStatus::Mastered:
                ++mastered;
                break;
        }
    }

    const int totalAnswered = progress_.totalQuestionsAnswered();
    const int totalCorrect = progress_.totalCorrectAnswers();
    const double successRatio =
        totalAnswered == 0 ? 0.0
                           : static_cast<double>(totalCorrect) / static_cast<double>(totalAnswered);

    ui_.printLine("Toplam XP: " + std::to_string(progress_.totalXp()));
    ui_.printLine("Toplam çözülen soru: " + std::to_string(totalAnswered));
    ui_.printLine("Toplam doğru cevap: " + std::to_string(totalCorrect));
    ui_.printLine("Toplam yanlış cevap: " + std::to_string(totalAnswered - totalCorrect));
    ui_.printLine("Genel başarı oranı: %" + std::to_string(static_cast<int>(successRatio * 100.0)));
    ui_.printLine("");
    ui_.printLine("Tamamlanan konu sayısı: " + std::to_string(completed));
    ui_.printLine("Ustalaşılan konu sayısı: " + std::to_string(mastered));
    ui_.printLine("Öğrenilmekte olan konu sayısı: " + std::to_string(learning));
    ui_.printLine("Başlanmamış konu sayısı: " + std::to_string(notStarted));
    ui_.printLine("");
    ui_.printLine("Kayıtlı yanlış sayısı: " + std::to_string(mistakes_.allMistakesOldestFirst().size()));
    ui_.printLine("");
}
```

- [ ] **Step 4: Clean slate, then build**

```bash
rm -f data/progress.txt data/mistakes.txt
cmake --build build
```
Expected: zero warnings.

- [ ] **Step 5: Full manual verification**

**Pass A — create exactly one mistake (topic 2, question id 7 answered wrong, rest correct), completing the topic:**

Topic 2's 6 questions are ids 7-12: correct answers are `b`, `b`, `1`, `2`, `n`, `\n` (a literal backslash followed by `n`, two characters). Answer id 7 wrong (`a` instead of `b`):
```bash
printf "1\n2\na\nb\n1\n2\nn\n\\n\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: `Sonuç: 5/6 doğru (%83), kazanılan XP: 65` (id 7's 10 XP not earned; 20+5+10+10+20 = 65), topic marked `Completed` (83% ≥ 70%).

**Pass B — "Hatalarımı Çöz" shows exactly that one mistake, retry it correctly:**
```bash
printf "4\nb\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: `Kayıtlı yanlışlarınız (1 soru):`, then question id 7's prompt/options are shown again, answering `b` is now correct (`Doğru! (+10 XP)`), and the summary line reads `Tamamlandı: 1/1 doğru, kazanılan XP: 10`.

**Pass C — "İstatistiklerim" reflects the accumulated totals:**
```bash
printf "7\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: `Toplam XP: 75` (65 from Pass A + 10 from Pass B), `Toplam çözülen soru: 7` (6 from Pass A + 1 retry in Pass B), `Toplam doğru cevap: 6` (5 correct in Pass A + 1 correct retry in Pass B), `Toplam yanlış cevap: 1`, `Genel başarı oranı: %85` (6/7 ≈ 85.7 → 85), `Tamamlanan konu sayısı: 1`, `Kayıtlı yanlış sayısı: 1` (the record from id 7 is retained, not deleted, even though it was answered correctly on retry — confirm this matches the spec's "don't delete on a correct retry" rule).

**Pass D — empty-state message when there are no mistakes:**
```bash
rm -f data/progress.txt data/mistakes.txt
printf "4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: `Henüz kaydedilmiş bir yanlışınız yok!` with no crash.

- [ ] **Step 6: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Wire Hatalarımı Çöz and İstatistiklerim to persisted data"
```

---

### Task 6: Wire "Günlük Tekrar", completing phase 4

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`

**Interfaces:**
- Consumes: `runMistakeQuestions` (Task 5).
- Produces: `void Application::runDailyReview();` — new private method, wired to menu option 3.

- [ ] **Step 1: Modify `src/Application.h`** — add one declaration to the private section, after `showStatistics`:

```cpp
    void runDailyReview();
```

- [ ] **Step 2: Modify `handleChoice`'s `case 3`** in `src/Application.cpp` — replace:

```cpp
        case 3:
            showNotYetAvailable("Günlük Tekrar");
            break;
```
with:
```cpp
        case 3:
            runDailyReview();
            break;
```

- [ ] **Step 3: Add `runDailyReview`** in `src/Application.cpp`, placed after `showStatistics`:

```cpp
void Application::runDailyReview() {
    auto mistakes = mistakes_.allMistakesOldestFirst();
    if (mistakes.empty()) {
        ui_.printLine("");
        ui_.printLine("Henüz tekrar edilecek bir yanlışınız yok! Önce birkaç konu testi çözmelisiniz.");
        return;
    }

    constexpr std::size_t kDailyReviewCap = 20;
    if (mistakes.size() > kDailyReviewCap) {
        mistakes.resize(kDailyReviewCap);
    }

    ui_.printLine("");
    ui_.printLine("Günlük tekrar başlıyor (" + std::to_string(mistakes.size()) + " soru):");
    ui_.printLine("");
    runMistakeQuestions(mistakes);
}
```

- [ ] **Step 4: Clean slate, then build**

```bash
rm -f data/progress.txt data/mistakes.txt
cmake --build build
```
Expected: zero warnings.

- [ ] **Step 5: Full manual verification (this phase's acceptance test)**

**Pass A — empty state:**
```bash
printf "3\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: `Henüz tekrar edilecek bir yanlışınız yok! Önce birkaç konu testi çözmelisiniz.`, no crash.

**Pass B — create two mistakes (topic 1's id 1 wrong, topic 6's id 61 wrong), then run daily review:**

Topic 1 (ids 1-6, 65, 70): answer id 1 wrong (`a` instead of `b`), rest correct:
```bash
printf "1\n1\na\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm `Sonuç: 7/8 doğru (%87), kazanılan XP: 95` (105 minus id 1's 10 XP), still `Completed`.

Topic 6 (ids 31-36, 61, 63, 71): answer id 61 wrong (submit `wrong` instead of `toplam + 5`), rest correct:
```bash
printf "1\n6\nb\nc\n2\n1\nint\n7\nwrong\n8\nint sayi;\ncin >> sayi;\ncout << sayi;\nBITIR\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm `Sonuç: 8/9 doğru (%88), kazanılan XP: 125` (135 minus id 61's 10 XP), still `Completed`.

Now run the daily review:
```bash
printf "3\nb\ntoplam + 5\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: `Günlük tekrar başlıyor (2 soru):`, both mistakes (ids 1 and 61) are asked in oldest-first order (id 1 was recorded first, so it's asked first), both answered correctly this time, and the summary reads `Tamamlandı: 2/2 doğru, kazanılan XP: 20` (10 + 10, both `Easy`-tier XP).

**Pass C — persistence still holds after all this:**
```bash
printf "7\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm `Toplam XP: 240` (95 + 125 + 20), `Kayıtlı yanlış sayısı: 2` (both retained despite being answered correctly on retry).

- [ ] **Step 6: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Wire Günlük Tekrar to recorded mistakes, completing phase 4"
```

---

## Post-plan note

This completes phase 4 (Persistence + Review Loop). The scope cuts recorded
in the design doc — a single "Hatalarımı Çöz" flow instead of the product
spec's 5-option submenu, mistake-recency-only "Günlük Tekrar" instead of
full multi-tier spaced repetition, and an MVP "İstatistiklerim" — are all
candidates for phase 5 (meta systems) to revisit once achievements and
leveling need richer underlying stats anyway. Phase 5 gets its own
brainstorming → spec → plan cycle before implementation starts.

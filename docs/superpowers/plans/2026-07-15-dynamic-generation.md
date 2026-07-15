# CppMaster Console — Dynamic Question Generation (Phase 6) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Build the real fingerprint-and-dedup mechanism the product spec's dynamic-generation section describes, with two working generators, wired into "Hızlı Test."

**Architecture:** A constexpr FNV-1a 64-bit hash (`FnvHash.h`), a `GeneratedQuestion` data struct carrying both an exact and a semantic signature, a `QuestionHistory` that persists seen hashes (same corruption-safe convention as every other data file), a small `IQuestionGenerator` interface, a `QuestionGenerationEngine` that retries until a semantically-fresh question is found or gives up honestly, and two concrete generators (`IntArithmeticPredictGenerator`, `BoolOutputPredictGenerator`). `askOneQuestion` gains one backward-compatible parameter so generated questions can be scored/tracked without creating unretrievable "ghost" mistake records.

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only (`<random>` for `std::mt19937_64` — never `rand()`/`srand()`). Still no test framework.

**Spec:** `docs/superpowers/specs/2026-07-15-dynamic-generation-design.md`

## Global Constraints

- C++20 required, same CMake settings as before.
- No external libraries — standard library only.
- Compiler warnings: MSVC `/W4 /permissive-`; GCC/Clang `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`. Zero warnings required.
- No `using namespace std;` anywhere.
- No fake/placeholder code. If both generators are exhausted for a "Hızlı Test" session, say so honestly and stop — never repeat or fabricate a question.
- Never `rand()`/`srand()` — `std::mt19937_64` only, seeded from `std::chrono` + `std::random_device` in the real application; tests construct their own fixed-seed engine directly (no special "test mode" needed anywhere in the production code).
- Any malformed line in `data/generated_question_history.txt` marks the WHOLE file corrupt (backup + fresh empty history); a missing file is not corruption — same rule as every other data file.
- **Before running any task's manual verification below, delete `data/progress.txt`, `data/mistakes.txt`, `data/achievements.txt`, and `data/generated_question_history.txt`** if they exist, so verification starts from a clean slate.
- **Task 4's manual verification is intentionally different from every prior phase's.** Because "Hızlı Test" uses a real, wall-clock-seeded random engine, its output cannot be pinned to one exact expected transcript the way every previous phase's verification was. Task 4's steps check structural/behavioral properties instead (no crash, a valid score line, history grows, two separate runs differ) — this is a deliberate exception recorded in the design doc, not a lapse in rigor.

---

### Task 1: `FnvHash.h`, `GeneratedQuestion.h`, `QuestionHistory`

**Files:**
- Create: `src/FnvHash.h`
- Create: `src/GeneratedQuestion.h`
- Create: `src/QuestionHistory.h`
- Create: `src/QuestionHistory.cpp`
- Modify: `CMakeLists.txt`
- Modify (temporarily, superseded in Task 2): `src/main.cpp`

**Interfaces:**
- Consumes: `Question` (unchanged).
- Produces:
  - `constexpr std::uint64_t fnv1a64(std::string_view text) noexcept;`
  - `struct GeneratedQuestion { Question question; std::string generatorId; std::string exactSignature; std::string semanticSignature; std::uint64_t exactHash; std::uint64_t semanticHash; };`
  - `class QuestionHistory { public: bool hasSeenExact(uint64_t) const; bool hasSeenSemantic(uint64_t) const; void record(const GeneratedQuestion&); bool loadFromFile(const std::string&, const std::string&); void saveToFile(const std::string&) const; };`

- [ ] **Step 1: Create `src/FnvHash.h`**

```cpp
#pragma once

#include <cstdint>
#include <string_view>

constexpr std::uint64_t fnv1a64(std::string_view text) noexcept {
    constexpr std::uint64_t offsetBasis = 14695981039346656037ULL;
    constexpr std::uint64_t prime = 1099511628211ULL;

    std::uint64_t hash = offsetBasis;
    for (const unsigned char character : text) {
        hash ^= character;
        hash *= prime;
    }
    return hash;
}
```

- [ ] **Step 2: Create `src/GeneratedQuestion.h`**

```cpp
#pragma once

#include <cstdint>
#include <string>

#include "Question.h"

struct GeneratedQuestion {
    Question question;
    std::string generatorId;
    std::string exactSignature;
    std::string semanticSignature;
    std::uint64_t exactHash = 0;
    std::uint64_t semanticHash = 0;
};
```

- [ ] **Step 3: Create `src/QuestionHistory.h`**

```cpp
#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

#include "GeneratedQuestion.h"

class QuestionHistory {
public:
    [[nodiscard]] bool hasSeenExact(std::uint64_t exactHash) const;
    [[nodiscard]] bool hasSeenSemantic(std::uint64_t semanticHash) const;
    void record(const GeneratedQuestion& generated);

    [[nodiscard]] bool loadFromFile(const std::string& filePath, const std::string& backupPath);
    void saveToFile(const std::string& filePath) const;

private:
    std::unordered_set<std::uint64_t> seenExactHashes_;
    std::unordered_set<std::uint64_t> seenSemanticHashes_;
};
```

- [ ] **Step 4: Create `src/QuestionHistory.cpp`**

```cpp
#include "QuestionHistory.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <system_error>
#include <utility>

namespace {

bool tryParseUint64(const std::string& text, std::uint64_t& outValue) {
    if (text.empty()) {
        return false;
    }
    try {
        std::size_t consumedChars = 0;
        const unsigned long long value = std::stoull(text, &consumedChars);
        if (consumedChars != text.size()) {
            return false;
        }
        outValue = static_cast<std::uint64_t>(value);
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

}  // namespace

bool QuestionHistory::hasSeenExact(std::uint64_t exactHash) const {
    return seenExactHashes_.find(exactHash) != seenExactHashes_.end();
}

bool QuestionHistory::hasSeenSemantic(std::uint64_t semanticHash) const {
    return seenSemanticHashes_.find(semanticHash) != seenSemanticHashes_.end();
}

void QuestionHistory::record(const GeneratedQuestion& generated) {
    seenExactHashes_.insert(generated.exactHash);
    seenSemanticHashes_.insert(generated.semanticHash);
}

bool QuestionHistory::loadFromFile(const std::string& filePath, const std::string& backupPath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    std::unordered_set<std::uint64_t> parsedExact;
    std::unordered_set<std::uint64_t> parsedSemantic;
    bool corrupted = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream lineStream(line);
        std::string recordType;
        lineStream >> recordType;

        std::string valueText;
        lineStream >> valueText;
        std::uint64_t value = 0;

        if (recordType == "exact") {
            if (!tryParseUint64(valueText, value)) {
                corrupted = true;
                break;
            }
            parsedExact.insert(value);
        } else if (recordType == "semantic") {
            if (!tryParseUint64(valueText, value)) {
                corrupted = true;
                break;
            }
            parsedSemantic.insert(value);
        } else {
            corrupted = true;
            break;
        }
    }

    if (corrupted) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        seenExactHashes_.clear();
        seenSemanticHashes_.clear();
        return true;
    }

    seenExactHashes_ = std::move(parsedExact);
    seenSemanticHashes_ = std::move(parsedSemantic);
    return false;
}

void QuestionHistory::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        return;
    }
    for (const std::uint64_t hash : seenExactHashes_) {
        file << "exact " << hash << '\n';
    }
    for (const std::uint64_t hash : seenSemanticHashes_) {
        file << "semantic " << hash << '\n';
    }
}
```

- [ ] **Step 5: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>

#include "FnvHash.h"
#include "QuestionHistory.h"

int main() {
    std::filesystem::create_directories("data");

    static_assert(fnv1a64("") == 14695981039346656037ULL, "FNV-1a of empty text must equal the offset basis");
    std::cout << "fnv1a64(bos metin) offset basis mi: "
              << (fnv1a64("") == 14695981039346656037ULL ? "EVET (OK)" : "HATA") << '\n';

    const std::uint64_t hashA = fnv1a64("merhaba");
    const std::uint64_t hashB = fnv1a64("merhaba");
    const std::uint64_t hashC = fnv1a64("Merhaba");
    std::cout << "Ayni metin ayni hash mi: " << (hashA == hashB ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Farkli metin farkli hash mi: " << (hashA != hashC ? "EVET (OK)" : "HATA") << '\n';

    QuestionHistory history;
    std::cout << "Baslangicta hash gorulmus mu: " << (!history.hasSeenExact(hashA) ? "HAYIR (OK)" : "HATA") << '\n';

    GeneratedQuestion sample;
    sample.exactHash = hashA;
    sample.semanticHash = fnv1a64("ornek-semantik");
    history.record(sample);
    std::cout << "Kayittan sonra exact gorulmus mu: " << (history.hasSeenExact(hashA) ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Kayittan sonra semantic gorulmus mu: "
              << (history.hasSeenSemantic(sample.semanticHash) ? "EVET (OK)" : "HATA") << '\n';

    const std::string testPath = "data/test_generated_history.txt";
    const std::string backupPath = "data/test_generated_history_corrupted_backup.txt";
    history.saveToFile(testPath);

    QuestionHistory loaded;
    const bool wasCorrupted = loaded.loadFromFile(testPath, backupPath);
    std::cout << "Yuklenen bozuk mu: " << (!wasCorrupted ? "HAYIR (OK)" : "HATA") << '\n';
    std::cout << "Yuklenen exact gorulmus mu: " << (loaded.hasSeenExact(hashA) ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yuklenen semantic gorulmus mu: "
              << (loaded.hasSeenSemantic(sample.semanticHash) ? "EVET (OK)" : "HATA") << '\n';

    {
        std::ofstream corruptFile(testPath, std::ios::trunc);
        corruptFile << "exact not_a_number\n";
    }
    QuestionHistory corruptHistory;
    const bool detectedCorruption = corruptHistory.loadFromFile(testPath, backupPath);
    std::cout << "Bozuk dosya tespit edildi mi: " << (detectedCorruption ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yedek olusturuldu mu: " << (std::filesystem::exists(backupPath) ? "EVET (OK)" : "HATA") << '\n';

    return 0;
}
```

- [ ] **Step 6: Update `CMakeLists.txt`'s `add_executable` call**, inserting the three new files after `MistakeTracker.cpp` and before `Application.h`:

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
    src/FnvHash.h
    src/GeneratedQuestion.h
    src/QuestionHistory.h
    src/QuestionHistory.cpp
    src/Application.h
    src/Application.cpp
)
```

- [ ] **Step 7: Build and run**

Run:
```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line ends in `(OK)`. Zero compiler warnings.

- [ ] **Step 8: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/FnvHash.h src/GeneratedQuestion.h src/QuestionHistory.h src/QuestionHistory.cpp
git commit -m "Add FNV-1a hash, GeneratedQuestion, and QuestionHistory persistence"
```

---

### Task 2: `IQuestionGenerator`, `QuestionGenerationEngine`, `IntArithmeticPredictGenerator`

**Files:**
- Create: `src/IQuestionGenerator.h`
- Create: `src/QuestionGenerationEngine.h`
- Create: `src/QuestionGenerationEngine.cpp`
- Create: `src/generators/IntArithmeticPredictGenerator.h`
- Create: `src/generators/IntArithmeticPredictGenerator.cpp`
- Modify: `CMakeLists.txt`
- Modify (temporarily, superseded in Task 3): `src/main.cpp`

**Interfaces:**
- Consumes: `GeneratedQuestion`, `QuestionHistory` (Task 1).
- Produces:
  - `class IQuestionGenerator { public: virtual ~IQuestionGenerator() = default; virtual std::string_view id() const noexcept = 0; virtual std::optional<GeneratedQuestion> generate(std::mt19937_64&) const = 0; };`
  - `class QuestionGenerationEngine { public: std::optional<GeneratedQuestion> generateUnique(const IQuestionGenerator&, std::mt19937_64&); bool loadHistory(const std::string&, const std::string&); void saveHistory(const std::string&) const; };`
  - `class IntArithmeticPredictGenerator final : public IQuestionGenerator { ... };` — produces `PredictOutput` questions for topic 6 ("int"): `int {var} = {start};\n{var} {+=|-=} {operand};\nstd::cout << {var};`, answer = `start ± operand`.

- [ ] **Step 1: Create `src/IQuestionGenerator.h`**

```cpp
#pragma once

#include <optional>
#include <random>
#include <string_view>

#include "GeneratedQuestion.h"

class IQuestionGenerator {
public:
    virtual ~IQuestionGenerator() = default;

    [[nodiscard]] virtual std::string_view id() const noexcept = 0;
    [[nodiscard]] virtual std::optional<GeneratedQuestion> generate(
        std::mt19937_64& randomEngine) const = 0;
};
```

- [ ] **Step 2: Create `src/QuestionGenerationEngine.h`**

```cpp
#pragma once

#include <optional>
#include <random>
#include <string>

#include "GeneratedQuestion.h"
#include "IQuestionGenerator.h"
#include "QuestionHistory.h"

class QuestionGenerationEngine {
public:
    QuestionGenerationEngine() = default;

    [[nodiscard]] std::optional<GeneratedQuestion> generateUnique(
        const IQuestionGenerator& generator, std::mt19937_64& randomEngine);

    [[nodiscard]] bool loadHistory(const std::string& filePath, const std::string& backupPath);
    void saveHistory(const std::string& filePath) const;

private:
    QuestionHistory history_;
};
```

- [ ] **Step 3: Create `src/QuestionGenerationEngine.cpp`**

```cpp
#include "QuestionGenerationEngine.h"

namespace {
constexpr int kMaxGenerationAttempts = 50;
}  // namespace

std::optional<GeneratedQuestion> QuestionGenerationEngine::generateUnique(
    const IQuestionGenerator& generator, std::mt19937_64& randomEngine) {
    for (int attempt = 0; attempt < kMaxGenerationAttempts; ++attempt) {
        auto candidate = generator.generate(randomEngine);
        if (!candidate.has_value()) {
            continue;
        }
        if (history_.hasSeenExact(candidate->exactHash) ||
            history_.hasSeenSemantic(candidate->semanticHash)) {
            continue;
        }
        history_.record(*candidate);
        return candidate;
    }
    return std::nullopt;
}

bool QuestionGenerationEngine::loadHistory(
    const std::string& filePath, const std::string& backupPath) {
    return history_.loadFromFile(filePath, backupPath);
}

void QuestionGenerationEngine::saveHistory(const std::string& filePath) const {
    history_.saveToFile(filePath);
}
```

- [ ] **Step 4: Create `src/generators/IntArithmeticPredictGenerator.h`**

```cpp
#pragma once

#include "IQuestionGenerator.h"

class IntArithmeticPredictGenerator final : public IQuestionGenerator {
public:
    [[nodiscard]] std::string_view id() const noexcept override;
    [[nodiscard]] std::optional<GeneratedQuestion> generate(
        std::mt19937_64& randomEngine) const override;
};
```

- [ ] **Step 5: Create `src/generators/IntArithmeticPredictGenerator.cpp`**

```cpp
#include "generators/IntArithmeticPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "sayi", "deger", "toplam", "sonuc", "x",
};

}  // namespace

std::string_view IntArithmeticPredictGenerator::id() const noexcept {
    return "IntArithmeticPredictGenerator";
}

std::optional<GeneratedQuestion> IntArithmeticPredictGenerator::generate(
    std::mt19937_64& randomEngine) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    std::uniform_int_distribution<int> startDist(-20, 50);
    std::uniform_int_distribution<int> operandDist(1, 15);
    std::uniform_int_distribution<int> opDist(0, 1);

    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const int start = startDist(randomEngine);
    const int operand = operandDist(randomEngine);
    const bool isAddition = opDist(randomEngine) == 0;
    const char* opSymbol = isAddition ? "+=" : "-=";
    const int answer = isAddition ? start + operand : start - operand;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 6;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.prompt =
        "int " + variableName + " = " + std::to_string(start) + ";\n" + variableName + " " +
        opSymbol + " " + std::to_string(operand) + ";\nstd::cout << " + variableName +
        ";\nYukarıdaki kodun ekran çıktısı nedir?";
    result.question.acceptedAnswers = {std::to_string(answer)};
    result.question.explanation =
        variableName + " değişkeni " + std::to_string(start) + " ile başlar; " +
        std::string(isAddition ? "+" : "-") + std::to_string(operand) + " işleminden sonra " +
        std::to_string(answer) + " olur.";
    result.question.baseXp = 20;

    result.generatorId = std::string(id());
    result.exactSignature = "generator=IntArithmeticPredictGenerator;var=" + variableName +
                             ";start=" + std::to_string(start) + ";op=" +
                             (isAddition ? "add" : "sub") + ";operand=" + std::to_string(operand);
    result.semanticSignature = "generator=IntArithmeticPredictGenerator;start=" +
                                std::to_string(start) + ";op=" + (isAddition ? "add" : "sub") +
                                ";operand=" + std::to_string(operand);
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}
```

- [ ] **Step 6: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>
#include <random>

#include "QuestionGenerationEngine.h"
#include "generators/IntArithmeticPredictGenerator.h"

int main() {
    IntArithmeticPredictGenerator generator;

    std::cout << "Generator id: " << generator.id() << " (beklenen: IntArithmeticPredictGenerator)\n";

    QuestionGenerationEngine genEngine;

    std::mt19937_64 engineA{123456789ULL};
    const auto first = genEngine.generateUnique(generator, engineA);
    std::cout << "Ilk uretim basarili mi: " << (first.has_value() ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Soru tipi PredictOutput mi: "
              << (first->question.type == QuestionType::PredictOutput ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Kabul edilen cevap sayisi 1 mi: "
              << (first->question.acceptedAnswers.size() == 1 ? "EVET (OK)" : "HATA") << '\n';

    // A fresh engine with the SAME seed reproduces generator.generate()'s first draw
    // exactly, which is `first` itself -- already recorded in genEngine's history.
    // generateUnique must reject that repeat and advance to the engine's next
    // random state, producing a genuinely different question.
    std::mt19937_64 engineB{123456789ULL};
    const auto second = genEngine.generateUnique(generator, engineB);
    std::cout << "Ikinci uretim basarili mi: " << (second.has_value() ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Tekrar eden aday reddedilip farkli soru mu uretildi: "
              << (second.has_value() && second->exactSignature != first->exactSignature ? "EVET (OK)"
                                                                                          : "HATA")
              << '\n';

    return 0;
}
```

- [ ] **Step 7: Update `CMakeLists.txt`'s `add_executable` call**, inserting the five new files after `QuestionHistory.cpp` and before `Application.h`:

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
    src/FnvHash.h
    src/GeneratedQuestion.h
    src/QuestionHistory.h
    src/QuestionHistory.cpp
    src/IQuestionGenerator.h
    src/QuestionGenerationEngine.h
    src/QuestionGenerationEngine.cpp
    src/generators/IntArithmeticPredictGenerator.h
    src/generators/IntArithmeticPredictGenerator.cpp
    src/Application.h
    src/Application.cpp
)
```

- [ ] **Step 8: Build and run**

Run:
```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line ends in `(OK)`. Zero compiler warnings.

- [ ] **Step 9: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/IQuestionGenerator.h src/QuestionGenerationEngine.h src/QuestionGenerationEngine.cpp src/generators/IntArithmeticPredictGenerator.h src/generators/IntArithmeticPredictGenerator.cpp
git commit -m "Add QuestionGenerationEngine and IntArithmeticPredictGenerator"
```

---

### Task 3: `BoolOutputPredictGenerator`

**Files:**
- Create: `src/generators/BoolOutputPredictGenerator.h`
- Create: `src/generators/BoolOutputPredictGenerator.cpp`
- Modify: `CMakeLists.txt`
- Modify (temporarily, superseded in Task 4): `src/main.cpp`

**Interfaces:**
- Consumes: `IQuestionGenerator`, `QuestionGenerationEngine` (Task 2).
- Produces: `class BoolOutputPredictGenerator final : public IQuestionGenerator { ... };` — produces `PredictOutput` questions for topic 9 ("bool"): `bool {var} = {true|false};\nstd::cout << {var};`, answer = `1` or `0`. Deliberately only 2 possible semantic variants ever — demonstrates exhaustion handling.

- [ ] **Step 1: Create `src/generators/BoolOutputPredictGenerator.h`**

```cpp
#pragma once

#include "IQuestionGenerator.h"

class BoolOutputPredictGenerator final : public IQuestionGenerator {
public:
    [[nodiscard]] std::string_view id() const noexcept override;
    [[nodiscard]] std::optional<GeneratedQuestion> generate(
        std::mt19937_64& randomEngine) const override;
};
```

- [ ] **Step 2: Create `src/generators/BoolOutputPredictGenerator.cpp`**

```cpp
#include "generators/BoolOutputPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "durum", "aktif", "sonuc", "bulundu", "tamam",
};

}  // namespace

std::string_view BoolOutputPredictGenerator::id() const noexcept {
    return "BoolOutputPredictGenerator";
}

std::optional<GeneratedQuestion> BoolOutputPredictGenerator::generate(
    std::mt19937_64& randomEngine) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    std::uniform_int_distribution<int> valueDist(0, 1);

    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const bool boolValue = valueDist(randomEngine) == 1;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 9;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Easy;
    result.question.prompt =
        "bool " + variableName + " = " + std::string(boolValue ? "true" : "false") +
        ";\nstd::cout << " + variableName + ";\nYukarıdaki kodun ekran çıktısı nedir?";
    result.question.acceptedAnswers = {boolValue ? "1" : "0"};
    result.question.explanation =
        std::string(
            "cout, bool değerini varsayılan olarak true için 1, false için 0 şeklinde "
            "yazdırır; burada değer ") +
        (boolValue ? "true" : "false") + " olduğu için çıktı " + (boolValue ? "1" : "0") +
        " olur.";
    result.question.baseXp = 10;

    result.generatorId = std::string(id());
    result.exactSignature = "generator=BoolOutputPredictGenerator;var=" + variableName +
                             ";value=" + (boolValue ? "true" : "false");
    result.semanticSignature =
        std::string("generator=BoolOutputPredictGenerator;value=") + (boolValue ? "true" : "false");
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}
```

- [ ] **Step 3: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>
#include <random>

#include "QuestionGenerationEngine.h"
#include "generators/BoolOutputPredictGenerator.h"

int main() {
    BoolOutputPredictGenerator generator;
    std::cout << "Generator id: " << generator.id() << " (beklenen: BoolOutputPredictGenerator)\n";

    QuestionGenerationEngine genEngine;
    std::mt19937_64 engine{42ULL};

    const auto first = genEngine.generateUnique(generator, engine);
    std::cout << "Ilk uretim basarili mi: " << (first.has_value() ? "EVET (OK)" : "HATA") << '\n';

    const auto second = genEngine.generateUnique(generator, engine);
    std::cout << "Ikinci uretim basarili mi (diger semantik deger kaldiysa): "
              << (second.has_value() ? "EVET (OK)" : "HATA") << '\n';
    if (second.has_value() && first.has_value()) {
        std::cout << "Ilk ve ikinci farkli semantik mi: "
                  << (second->semanticSignature != first->semanticSignature ? "EVET (OK)" : "HATA")
                  << '\n';
    }

    // Only 2 possible semantic variants exist for this generator (true->1, false->0).
    // Both are now recorded in genEngine's history, so a third attempt must be
    // exhausted -- this is a hard guarantee, not a probabilistic one, since every
    // possible draw from here on is one of the 2 already-seen semantic values.
    const auto third = genEngine.generateUnique(generator, engine);
    std::cout << "Ucuncu uretim tukendi mi (bos deger bekleniyor): "
              << (!third.has_value() ? "EVET (OK)" : "HATA") << '\n';

    return 0;
}
```

- [ ] **Step 4: Update `CMakeLists.txt`'s `add_executable` call**, inserting the two new files after `IntArithmeticPredictGenerator.cpp` and before `Application.h` — this is also this plan's final `add_executable` form (Task 4 doesn't add any new files):

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
    src/FnvHash.h
    src/GeneratedQuestion.h
    src/QuestionHistory.h
    src/QuestionHistory.cpp
    src/IQuestionGenerator.h
    src/QuestionGenerationEngine.h
    src/QuestionGenerationEngine.cpp
    src/generators/IntArithmeticPredictGenerator.h
    src/generators/IntArithmeticPredictGenerator.cpp
    src/generators/BoolOutputPredictGenerator.h
    src/generators/BoolOutputPredictGenerator.cpp
    src/Application.h
    src/Application.cpp
)
```

- [ ] **Step 5: Build and run**

Run:
```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line ends in `(OK)`. Zero compiler warnings.

- [ ] **Step 6: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/generators/BoolOutputPredictGenerator.h src/generators/BoolOutputPredictGenerator.cpp
git commit -m "Add BoolOutputPredictGenerator, demonstrating generation exhaustion"
```

---

### Task 4: Wire "Hızlı Test", completing phase 6

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`

Note: `CMakeLists.txt` already lists every file this task touches (Task 3 left it in final form). No `CMakeLists.txt` change is needed.

**Interfaces:**
- Consumes: `QuestionGenerationEngine`, `IntArithmeticPredictGenerator`, `BoolOutputPredictGenerator` (Tasks 1-3).
- Produces: `AnswerResult Application::askOneQuestion(const Question& question, bool trackMistakes = true);` (existing method, one new parameter with a default that preserves every existing call site's behavior exactly) and `void Application::runQuickTest();` (new, wired to menu option 2).

- [ ] **Step 1: Restore `src/main.cpp` to the real application entry point**

Tasks 1-3 each left `src/main.cpp` as a temporary verification harness. Before
touching `Application.h`/`.cpp`, restore it to exactly:

```cpp
#include "Application.h"

int main() {
    Application app;
    app.run();
    return 0;
}
```

Commit this restoration on its own, before any other change in this task:
```bash
git add src/main.cpp
git commit -m "Restore main.cpp to the real Application entry point"
```

- [ ] **Step 2: Modify `src/Application.h`**

Add `#include <random>` to the include block, plus:
```cpp
#include "QuestionGenerationEngine.h"
#include "generators/BoolOutputPredictGenerator.h"
#include "generators/IntArithmeticPredictGenerator.h"
```

Change the `askOneQuestion` declaration from:
```cpp
    AnswerResult askOneQuestion(const Question& question);
```
to:
```cpp
    AnswerResult askOneQuestion(const Question& question, bool trackMistakes = true);
```

Add `void runQuickTest();` to the private section, right after `runDailyReview`'s declaration.

Add these new members after `achievements_`:
```cpp
    QuestionGenerationEngine generationEngine_;
    IntArithmeticPredictGenerator intArithmeticGenerator_;
    BoolOutputPredictGenerator boolOutputGenerator_;
    std::mt19937_64 randomEngine_;
    int nextGeneratedQuestionId_ = 1000;
```

- [ ] **Step 3: Modify `src/Application.cpp`**

Add `#include <chrono>` and `#include <random>` to the include block (if not already present via headers).

Add two new file-path constants to the anonymous namespace, alongside the existing six:
```cpp
constexpr const char* kGeneratedHistoryFilePath = "data/generated_question_history.txt";
constexpr const char* kGeneratedHistoryBackupPath = "data/generated_question_history_corrupted_backup.txt";
```

Add this free function to the anonymous namespace (the mega-spec's own recommended seeding approach):
```cpp
std::uint64_t createSeed() {
    const auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::random_device randomDevice;
    return static_cast<std::uint64_t>(now) ^ (static_cast<std::uint64_t>(randomDevice()) << 32U) ^
           static_cast<std::uint64_t>(randomDevice());
}
```

Modify the constructor's initializer list — add `, randomEngine_(createSeed())` after the existing `progress_(...)` initializer, so it reads:
```cpp
Application::Application()
    : progress_(static_cast<int>(lessons_.allLessons().size())), randomEngine_(createSeed()) {
```

Add this block at the end of the constructor body, after the existing achievements-loading block:
```cpp
    const bool historyCorrupted =
        generationEngine_.loadHistory(kGeneratedHistoryFilePath, kGeneratedHistoryBackupPath);
    if (historyCorrupted) {
        ui_.printLine(
            "Uyarı: üretilen soru geçmişi dosyası bozuktu; yedeklendi (" +
            std::string(kGeneratedHistoryBackupPath) + ") ve sıfırlandı.");
    }
```

Modify `handleChoice`'s `case 2` — replace:
```cpp
        case 2:
            showNotYetAvailable("Hızlı Test");
            break;
```
with:
```cpp
        case 2:
            runQuickTest();
            break;
```

Modify `askOneQuestion`'s signature from `AnswerResult Application::askOneQuestion(const Question& question) {` to `AnswerResult Application::askOneQuestion(const Question& question, bool trackMistakes) {` (do not repeat the default argument in the definition — only the declaration in the header has `= true`), and replace this block inside it:
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
with:
```cpp
    progress_.recordAnswer(result.correct);
    progress_.recordStreak(result.correct);
    if (result.correct) {
        progress_.recordTypedCorrectAnswer(question.type);
        if (trackMistakes && mistakes_.hasMistake(question.id)) {
            mistakes_.recordCorrectRetry(question.id);
        }
    } else if (trackMistakes) {
        mistakes_.recordWrong(question.id);
    }

    checkAchievements(question, result.correct);

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    progressManager_.save(progress_, kProgressFilePath, topicCount);
    if (trackMistakes) {
        mistakes_.saveToFile(kMistakesFilePath);
    }

    return result;
```

No other line inside `askOneQuestion` changes — the rendering/reading/evaluating/feedback block above this stays exactly as-is.

Add the new method, placed after `runDailyReview`:
```cpp
void Application::runQuickTest() {
    ui_.printLine("");
    ui_.printHeader("HIZLI TEST");
    ui_.printLine("Sizin için 5 taze soru üretmeye çalışacağım.");
    ui_.printLine("");

    constexpr int kQuickTestQuestionCount = 5;
    int correctCount = 0;
    int sessionXp = 0;
    int askedCount = 0;

    for (int index = 0; index < kQuickTestQuestionCount; ++index) {
        std::uniform_int_distribution<int> generatorChoice(0, 1);
        const bool tryIntFirst = generatorChoice(randomEngine_) == 0;

        std::optional<GeneratedQuestion> generated;
        if (tryIntFirst) {
            generated = generationEngine_.generateUnique(intArithmeticGenerator_, randomEngine_);
            if (!generated.has_value()) {
                generated = generationEngine_.generateUnique(boolOutputGenerator_, randomEngine_);
            }
        } else {
            generated = generationEngine_.generateUnique(boolOutputGenerator_, randomEngine_);
            if (!generated.has_value()) {
                generated = generationEngine_.generateUnique(intArithmeticGenerator_, randomEngine_);
            }
        }

        if (!generated.has_value()) {
            ui_.printLine("Bu oturumda başka taze soru üretemedim; testi burada bitiriyorum.");
            break;
        }

        generated->question.id = nextGeneratedQuestionId_++;
        const AnswerResult result = askOneQuestion(generated->question, /*trackMistakes=*/false);
        ++askedCount;
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }

        generationEngine_.saveHistory(kGeneratedHistoryFilePath);
    }

    if (askedCount > 0) {
        const int successPercent = static_cast<int>(
            (static_cast<double>(correctCount) / static_cast<double>(askedCount)) * 100.0);
        ui_.printLine(
            "Hızlı test bitti: " + std::to_string(correctCount) + "/" + std::to_string(askedCount) +
            " doğru (%" + std::to_string(successPercent) +
            "), kazanılan XP: " + std::to_string(sessionXp));
    }
    ui_.printLine("");

    awardXpAndCheckLevelUp(sessionXp);
    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
}
```

- [ ] **Step 4: Clean slate, then build**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt
cmake --build build
```
Expected: zero warnings.

- [ ] **Step 5: Regression check for `askOneQuestion`'s new parameter**

Confirm every EXISTING caller (`runTopicQuiz`, `runMistakeQuestions`, `runSectionExam`) still calls `askOneQuestion(question)` with no second argument — grep for `askOneQuestion(` in `Application.cpp` and confirm none of the three pre-existing call sites were changed to pass an explicit second argument (only the brand-new call inside `runQuickTest` passes `false`). Then re-run phase 3's exact topic-1 regression sequence to confirm untouched behavior:
```bash
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm this still produces exactly the same output as every prior phase: `İlk Adım`/`Hatasız Beşli` unlocks, `Sonuç: 8/8 doğru (%100), kazanılan XP: 105`, the level-2 celebration, and `data/mistakes.txt` still empty (no wrong answers). This proves `trackMistakes`'s default value preserves every existing flow exactly.

- [ ] **Step 6: "Hızlı Test" structural verification (this phase's acceptance test — see the Global Constraints note on why this differs from every prior phase's exact-transcript style)**

Clean slate again, then run "Hızlı Test" twice, as two separate process invocations, answering every question with the same fixed dummy guess (`0`) regardless of what's actually asked (since the questions are genuinely randomized, there is no fixed correct-answer sequence to predict in advance):

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt
printf "2\n0\n0\n0\n0\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm:
1. The `HIZLI TEST` header and intro line appear.
2. No crash, no hang — the program reaches a `Hızlı test bitti: X/5 doğru (%P), kazanılan XP: N` line where `0 <= X <= 5`, `P` is `X*20`, and `N >= 0` (the exact values don't matter — internal consistency does: confirm `P` really is `round(X/5*100)` and that `N` is plausible given whichever questions were actually shown in the transcript, e.g. if you see `IntArithmeticPredictGenerator`-style prompts they're worth 20 XP each and `BoolOutputPredictGenerator`-style prompts are worth 10 XP each when correct).
3. `data/generated_question_history.txt` now exists and is non-empty (contains `exact`/`semantic` lines).

Then run a second, separate process with the identical input:
```bash
printf "2\n0\n0\n0\n0\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm:
4. No crash, a `Hızlı test bitti: ...` line again.
5. `data/generated_question_history.txt` has grown (more `exact`/`semantic` lines than after the first run) — proving the second run's questions were genuinely new relative to the first run's, not repeats.
6. At least skim the two runs' printed prompts and confirm they are not byte-for-byte identical to each other (different numbers/variable names/values) — direct evidence the feature is actually generating varied content, not a fixed script.

- [ ] **Step 7: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Wire Hızlı Test to the dynamic generation engine, completing phase 6"
```

---

## Post-plan note

This completes phase 6 within the scope recorded in the design doc: a
genuine, working fingerprint/dedup/history mechanism with two generators,
proven both in isolation (deterministic, fixed-seed component tests) and
end-to-end (a real, randomly-seeded "Hızlı Test" that never repeats itself
across restarts). Everything the mega-spec's dynamic-generation section
describes beyond this — 15 generators across every question type,
multi-tier attempt escalation, generator scoring/weighting, distractor
generation, capacity/exhaustion telemetry, cross-topic generators — is
real, valuable future work once this core mechanism has proven itself, not
a shortcut taken here. Phase 7 (polish: tests, README, remaining topics'
content) gets its own brainstorming → spec → plan cycle before
implementation starts.

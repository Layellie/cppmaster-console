# CppMaster Console — Richer Question Types (Phase 3) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add working support for six more question types (`CompleteLine`, `PredictOutput`, `FindError`, `FixCode`, `OrderCode`, `WriteCode`) with real evaluation, real rendering, and a small set of genuine new questions on topics 1-10.

**Architecture:** `QuizEngine::evaluate` is restructured around a type dispatch (while keeping MultipleChoice/TrueFalse/FillBlank byte-for-byte behaviorally identical to phase 2); `ConsoleUI` gains one new multi-line input method; `QuestionManager` gains 12 new questions; `Application`'s quiz loop gains two new rendering/input branches. No new files, no new `Question` fields.

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only. Still no test framework.

**Spec:** `docs/superpowers/specs/2026-07-14-richer-question-types-design.md`

## Global Constraints

- C++20 required, same CMake settings as before.
- No external libraries — standard library only.
- Compiler warnings: MSVC `/W4 /permissive-`; GCC/Clang `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`. Zero warnings required.
- No `using namespace std;` anywhere.
- No fake/placeholder code.
- User-facing strings are Turkish with correct diacritics; comparison strings for the four new whitespace-normalized types stay case-sensitive (real C++ syntax); `OrderCode`/`WriteCode` matching is documented in detail below — don't improvise different semantics.
- **No `CMakeLists.txt` changes anywhere in this phase** — every task modifies existing files only; no new source files are created. If a task's steps ever seem to need a `CMakeLists.txt` edit, stop and re-read this constraint before proceeding.
- `Question`/`Enums.h` are unchanged — all six new types reuse existing struct fields (see the spec's "Data model" table). Do not add new fields.

---

### Task 1: `QuizEngine` — evaluation for the six new types

**Files:**
- Modify: `src/QuizEngine.cpp`
- Modify (temporarily, superseded in Task 4): `src/main.cpp`

**Interfaces:**
- Consumes: `Question`/`QuestionType` (unchanged).
- Produces: no change to `QuizEngine`'s public surface (`AnswerResult evaluate(const Question&, const std::string&) const` — same signature as phase 2). Internal dispatch and matching logic change; MultipleChoice/TrueFalse/FillBlank must remain behaviorally identical to phase 2 (this needs explicit verification, not just a claim).

- [ ] **Step 1: Replace the full contents of `src/QuizEngine.cpp`**

```cpp
#include "QuizEngine.h"

#include <cctype>
#include <cstddef>

namespace {

std::string trimAndLower(const std::string& text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = text.find_last_not_of(" \t\r\n");
    const std::string trimmed = text.substr(first, last - first + 1);

    std::string result;
    result.reserve(trimmed.size());
    for (const char character : trimmed) {
        result.push_back(static_cast<char>(
            std::tolower(static_cast<unsigned char>(character))));
    }
    return result;
}

std::string collapseWhitespace(const std::string& text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = text.find_last_not_of(" \t\r\n");
    const std::string trimmed = text.substr(first, last - first + 1);

    std::string result;
    result.reserve(trimmed.size());
    bool previousWasSpace = false;
    for (const char character : trimmed) {
        const bool isSpace =
            character == ' ' || character == '\t' || character == '\r' || character == '\n';
        if (isSpace) {
            if (!previousWasSpace) {
                result.push_back(' ');
            }
            previousWasSpace = true;
        } else {
            result.push_back(character);
            previousWasSpace = false;
        }
    }
    return result;
}

std::string extractDigitSequence(const std::string& text) {
    std::string result;
    std::string currentToken;
    for (const char character : text) {
        if (std::isdigit(static_cast<unsigned char>(character))) {
            currentToken.push_back(character);
        } else if (!currentToken.empty()) {
            if (!result.empty()) {
                result.push_back(' ');
            }
            result += currentToken;
            currentToken.clear();
        }
    }
    if (!currentToken.empty()) {
        if (!result.empty()) {
            result.push_back(' ');
        }
        result += currentToken;
    }
    return result;
}

bool isBalanced(const std::string& code) {
    int parenDepth = 0;
    int braceDepth = 0;
    for (const char character : code) {
        switch (character) {
            case '(':
                ++parenDepth;
                break;
            case ')':
                --parenDepth;
                if (parenDepth < 0) {
                    return false;
                }
                break;
            case '{':
                ++braceDepth;
                break;
            case '}':
                --braceDepth;
                if (braceDepth < 0) {
                    return false;
                }
                break;
            default:
                break;
        }
    }
    return parenDepth == 0 && braceDepth == 0;
}

std::string multipleChoiceDisplay(const Question& question) {
    const std::string& letter = question.acceptedAnswers.front();
    const auto index = static_cast<std::size_t>(letter.front() - 'a');
    if (index >= question.options.size()) {
        return letter;
    }
    const char upperLetter =
        static_cast<char>(std::toupper(static_cast<unsigned char>(letter.front())));
    return std::string(1, upperLetter) + ") " + question.options[index];
}

std::string trueFalseDisplay(const Question& question) {
    const std::string& digit = question.acceptedAnswers.front();
    return digit + (digit == "1" ? " (Doğru)" : " (Yanlış)");
}

std::string correctAnswerDisplayFor(const Question& question) {
    switch (question.type) {
        case QuestionType::MultipleChoice:
            return multipleChoiceDisplay(question);
        case QuestionType::TrueFalse:
            return trueFalseDisplay(question);
        default:
            return question.acceptedAnswers.empty() ? "" : question.acceptedAnswers.front();
    }
}

bool matchesAnyAcceptedCaseInsensitive(const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer = trimAndLower(rawAnswer);
    for (const std::string& accepted : question.acceptedAnswers) {
        if (normalizedAnswer == trimAndLower(accepted)) {
            return true;
        }
    }
    return false;
}

bool matchesAnyAcceptedCaseSensitiveWhitespaceNormalized(
    const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer = collapseWhitespace(rawAnswer);
    for (const std::string& accepted : question.acceptedAnswers) {
        if (normalizedAnswer == collapseWhitespace(accepted)) {
            return true;
        }
    }
    return false;
}

bool matchesOrderCode(const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer = extractDigitSequence(rawAnswer);
    for (const std::string& accepted : question.acceptedAnswers) {
        if (normalizedAnswer == extractDigitSequence(accepted)) {
            return true;
        }
    }
    return false;
}

bool matchesWriteCode(const Question& question, const std::string& rawAnswer) {
    if (!isBalanced(rawAnswer)) {
        return false;
    }
    for (const std::string& required : question.acceptedAnswers) {
        if (rawAnswer.find(required) == std::string::npos) {
            return false;
        }
    }
    return true;
}

std::string writeCodeRequirementsDisplay(const Question& question) {
    std::string result = "Gerekli öğeler: ";
    for (std::size_t index = 0; index < question.acceptedAnswers.size(); ++index) {
        if (index > 0) {
            result += ", ";
        }
        result += question.acceptedAnswers[index];
    }
    return result;
}

}  // namespace

AnswerResult QuizEngine::evaluate(const Question& question, const std::string& rawAnswer) const {
    bool isCorrect = false;
    std::string display;

    switch (question.type) {
        case QuestionType::MultipleChoice:
        case QuestionType::TrueFalse:
        case QuestionType::FillBlank:
            isCorrect = matchesAnyAcceptedCaseInsensitive(question, rawAnswer);
            display = correctAnswerDisplayFor(question);
            break;
        case QuestionType::CompleteLine:
        case QuestionType::PredictOutput:
        case QuestionType::FindError:
        case QuestionType::FixCode:
            isCorrect = matchesAnyAcceptedCaseSensitiveWhitespaceNormalized(question, rawAnswer);
            display = question.acceptedAnswers.empty() ? "" : question.acceptedAnswers.front();
            break;
        case QuestionType::OrderCode:
            isCorrect = matchesOrderCode(question, rawAnswer);
            display = question.acceptedAnswers.empty() ? "" : question.acceptedAnswers.front();
            break;
        case QuestionType::WriteCode:
            isCorrect = matchesWriteCode(question, rawAnswer);
            display = writeCodeRequirementsDisplay(question);
            break;
        default:
            break;
    }

    return AnswerResult{isCorrect, isCorrect ? question.baseXp : 0, display};
}
```

- [ ] **Step 2: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>

#include "Question.h"
#include "QuizEngine.h"

int main() {
    QuizEngine engine;

    Question completeLine{
        .id = 901, .topicId = 6,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Easy,
        .prompt = "int toplam = 10;\ntoplam = ______;",
        .acceptedAnswers = {"toplam + 5", "toplam+5"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "CompleteLine 'toplam + 5': "
              << (engine.evaluate(completeLine, "toplam + 5").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "CompleteLine 'toplam+5' (bosluksuz varyant): "
              << (engine.evaluate(completeLine, "toplam+5").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "CompleteLine 'TOPLAM + 5' (buyuk harf, yanlis olmali): "
              << (!engine.evaluate(completeLine, "TOPLAM + 5").correct ? "YANLIS (OK)" : "HATA") << '\n';
    std::cout << "CompleteLine '  toplam   +   5  ' (fazla bosluk, dogru olmali): "
              << (engine.evaluate(completeLine, "  toplam   +   5  ").correct ? "DOGRU (OK)" : "HATA") << '\n';

    Question findError{
        .id = 902, .topicId = 1,
        .type = QuestionType::FindError, .difficulty = Difficulty::Easy,
        .prompt = "int yas = 20\n\ncout << yas;",
        .acceptedAnswers = {"int yas = 20;"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "FindError dogru cevap: "
              << (engine.evaluate(findError, "int yas = 20;").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "FindError yanlis cevap (noktali virgul eksik): "
              << (!engine.evaluate(findError, "int yas = 20").correct ? "YANLIS (OK)" : "HATA") << '\n';

    Question orderCode{
        .id = 903, .topicId = 4,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Easy,
        .options = {"cout << yas;", "int yas;", "cin >> yas;"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "OrderCode '2 3 1' (bosluklu): "
              << (engine.evaluate(orderCode, "2 3 1").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "OrderCode '2,3,1' (virgullu): "
              << (engine.evaluate(orderCode, "2,3,1").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "OrderCode '1 2 3' (yanlis sira): "
              << (!engine.evaluate(orderCode, "1 2 3").correct ? "YANLIS (OK)" : "HATA") << '\n';

    Question writeCode{
        .id = 904, .topicId = 6,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanicidan bir tam sayi okuyup ekrana yazdiran bir program yaz.",
        .acceptedAnswers = {"cin", ">>", "cout", "<<"},
        .explanation = "test",
        .baseXp = 40,
    };
    const std::string goodSubmission = "int sayi;\ncin >> sayi;\ncout << sayi;";
    std::cout << "WriteCode tam gereksinimler: "
              << (engine.evaluate(writeCode, goodSubmission).correct ? "DOGRU (OK)" : "HATA") << '\n';
    const std::string missingCout = "int sayi;\ncin >> sayi;";
    std::cout << "WriteCode cout eksik: "
              << (!engine.evaluate(writeCode, missingCout).correct ? "YANLIS (OK)" : "HATA") << '\n';
    const std::string unbalanced = "int sayi;\ncin >> sayi;\ncout << (sayi;";
    std::cout << "WriteCode dengesiz parantez: "
              << (!engine.evaluate(writeCode, unbalanced).correct ? "YANLIS (OK)" : "HATA") << '\n';

    Question multipleChoice{
        .id = 905, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "test",
        .options = {"cin", "cout", "endl", "return"},
        .acceptedAnswers = {"b"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "Regresyon MC 'B' (buyuk harf, case-insensitive dogru olmali): "
              << (engine.evaluate(multipleChoice, "B").correct ? "DOGRU (OK)" : "HATA") << '\n';

    Question trueFalseQuestion{
        .id = 906, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "test",
        .acceptedAnswers = {"2"},
        .explanation = "test",
        .baseXp = 5,
    };
    std::cout << "Regresyon TF '2': "
              << (engine.evaluate(trueFalseQuestion, "2").correct ? "DOGRU (OK)" : "HATA") << '\n';

    Question fillBlank{
        .id = 907, .topicId = 1,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "test",
        .acceptedAnswers = {"cout"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "Regresyon FillBlank '  COUT  ' (bosluklu, buyuk harf, dogru olmali): "
              << (engine.evaluate(fillBlank, "  COUT  ").correct ? "DOGRU (OK)" : "HATA") << '\n';

    return 0;
}
```

- [ ] **Step 3: Build and run**

Run:
```bash
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line ends in `(OK)`. Zero compiler warnings.

- [ ] **Step 4: Commit**

```bash
git add src/QuizEngine.cpp src/main.cpp
git commit -m "Add QuizEngine evaluation for CompleteLine/PredictOutput/FindError/FixCode/OrderCode/WriteCode"
```

---

### Task 2: `ConsoleUI` — multi-line code input

**Files:**
- Modify: `src/ConsoleUI.h`
- Modify: `src/ConsoleUI.cpp`
- Modify (temporarily, superseded in Task 4): `src/main.cpp`

**Interfaces:**
- Consumes: nothing new.
- Produces: `std::string ConsoleUI::readMultilineCode();` — reads lines until one equals exactly `"BITIR"` or EOF, joined with `'\n'`.

- [ ] **Step 1: Modify `src/ConsoleUI.h`** — add the new method declaration so the full file reads:

```cpp
#pragma once

#include <string>

class ConsoleUI {
public:
    ConsoleUI();

    void clearScreen() const;
    void printLine(const std::string& text) const;
    void printHeader(const std::string& title) const;

    // Re-prompts on invalid or out-of-range input. On genuine stdin EOF
    // (no more input will ever arrive), returns minValue rather than
    // looping forever — callers with minValue == 0 (an exit/back option)
    // get correct "treat EOF as exit" behavior for free; callers that use
    // a different minValue should be aware EOF and choosing minValue are
    // indistinguishable.
    int readMenuChoice(int minValue, int maxValue);
    std::string readLine(const std::string& prompt);

    // Reads multiple lines until the user types exactly "BITIR" (or EOF is
    // reached), joining the collected lines with '\n'. Used for WriteCode
    // answers, matching the product spec's multi-line code entry convention.
    std::string readMultilineCode();
};
```

- [ ] **Step 2: Modify `src/ConsoleUI.cpp`** — add the new method definition at the end of the file, so the full file reads:

```cpp
#include "ConsoleUI.h"

#include <charconv>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <system_error>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#endif

namespace {

std::string trim(const std::string& text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

}  // namespace

ConsoleUI::ConsoleUI() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

void ConsoleUI::clearScreen() const {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ConsoleUI::printLine(const std::string& text) const {
    std::cout << text << '\n';
}

void ConsoleUI::printHeader(const std::string& title) const {
    const std::string separator(40, '=');
    std::cout << separator << '\n' << title << '\n' << separator << '\n';
}

int ConsoleUI::readMenuChoice(int minValue, int maxValue) {
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            if (std::cin.eof()) {
                return minValue;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        const std::string trimmed = trim(line);
        int value = 0;
        const auto result = std::from_chars(
            trimmed.data(), trimmed.data() + trimmed.size(), value);

        const bool parsedWholeString =
            result.ec == std::errc{} && result.ptr == trimmed.data() + trimmed.size();

        if (parsedWholeString && value >= minValue && value <= maxValue) {
            return value;
        }

        std::cout << "Geçersiz seçim. Lütfen " << minValue << " ile " << maxValue
                   << " arasında bir sayı girin: ";
    }
}

std::string ConsoleUI::readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::string ConsoleUI::readMultilineCode() {
    std::string result;
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }
        if (line == "BITIR") {
            break;
        }
        if (!result.empty()) {
            result += '\n';
        }
        result += line;
    }
    return result;
}
```

- [ ] **Step 3: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include "ConsoleUI.h"

int main() {
    ConsoleUI ui;
    ui.printLine("Kodunuzu girin, bitirmek icin BITIR yazin:");
    const std::string code = ui.readMultilineCode();
    ui.printLine("--- Toplanan kod basliyor ---");
    ui.printLine(code);
    ui.printLine("--- Toplanan kod bitti ---");
    return 0;
}
```

- [ ] **Step 4: Build and verify**

Run:
```bash
cmake --build build
printf 'int x;\ncin >> x;\nBITIR\n' | ./build/Debug/CppMasterConsole.exe
```
Expected output:
```
Kodunuzu girin, bitirmek icin BITIR yazin:
--- Toplanan kod basliyor ---
int x;
cin >> x;
--- Toplanan kod bitti ---
```
(the `BITIR` line itself must NOT appear in the collected code). Zero compiler warnings.

- [ ] **Step 5: Commit**

```bash
git add src/ConsoleUI.h src/ConsoleUI.cpp src/main.cpp
git commit -m "Add ConsoleUI::readMultilineCode for WriteCode answers"
```

---

### Task 3: 12 new questions for the six new types (ids 61-72)

**Files:**
- Modify: `src/QuestionManager.cpp`
- Modify (temporarily, superseded in Task 4): `src/main.cpp`

**Interfaces:**
- Consumes: `Question`/`QuestionType`/`Difficulty` (unchanged).
- Produces: no interface change — `QuestionManager::questionsForTopic` now returns more entries for topics 1, 4, 6, 7, 8, 9, 10 (topics 2, 3, 5 are unaffected, still 6 each).

- [ ] **Step 1: Append these 12 `questions_.push_back(...)` calls** to the end of `QuestionManager`'s constructor in `src/QuestionManager.cpp`, immediately after the existing `// Topic 10: const` block's last `push_back` (id 60) and before the constructor's closing `}`

```cpp
    // Phase 3: richer question types (ids 61-72)

    questions_.push_back(Question{
        .id = 61, .topicId = 6,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Easy,
        .prompt = "int toplam = 10;\ntoplam = ______;\ncout << toplam;\nYukarıdaki kodun çalışması sonucunda toplam değişkeninin 15 olması isteniyor. Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"toplam + 5", "toplam+5"},
        .explanation = "toplam değişkenine 5 eklenirse (toplam + 5), 10 + 5 = 15 elde edilir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 62, .topicId = 4,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a;\nint b;\ncin >> a >> ______;\nİki değişkeni tek satırda okumak istiyorsunuz. Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"b"},
        .explanation = "cin >> a >> b; şeklinde birden fazla değişken art arda >> ile okunabilir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 63, .topicId = 6,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Easy,
        .prompt = "int sayi = 5;\nsayi = sayi + 3;\nstd::cout << sayi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"8"},
        .explanation = "sayi başlangıçta 5'tir; sayi + 3 işlemiyle 8 olur ve ekrana 8 yazdırılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 64, .topicId = 9,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "bool durum = false;\nstd::cout << durum;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0"},
        .explanation = "cout, bool değerlerini varsayılan olarak 1 (true) veya 0 (false) şeklinde yazdırır.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 65, .topicId = 1,
        .type = QuestionType::FindError, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint yas = 20\n\nstd::cout << yas;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int yas = 20;"},
        .explanation = "int yas = 20 satırının sonunda noktalı virgül (;) eksik; doğrusu int yas = 20; şeklindedir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 66, .topicId = 8,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nchar harf = \"A\";\nstd::cout << harf;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"char harf = 'A';"},
        .explanation = "char için çift tırnak değil tek tırnak kullanılmalıdır; doğrusu char harf = 'A'; şeklindedir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 67, .topicId = 7,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodu düzeltin:\n\ndouble ortalama = 87,5;\nstd::cout << ortalama;\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"double ortalama = 87.5;"},
        .explanation = "C++'ta ondalık ayıracı virgül değil noktadır; doğrusu double ortalama = 87.5; şeklindedir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 68, .topicId = 4,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint yas;\ncin > yas;\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"cin >> yas;"},
        .explanation = "cin ile okuma yaparken tek > değil çift >> operatörü kullanılmalıdır; doğrusu cin >> yas; şeklindedir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 69, .topicId = 4,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdaki satırları geçerli ve mantıklı bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın, örnek: 1 2 3):",
        .options = {"cout << yas;", "int yas;", "cin >> yas;"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Önce değişken tanımlanır (int yas;), sonra değer okunur (cin >> yas;), en son yazdırılır (cout << yas;): sıra 2 3 1.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 70, .topicId = 1,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları geçerli bir C++ programı oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"return 0;", "std::cout << \"Merhaba\";", "int main() {", "}"},
        .acceptedAnswers = {"3 2 1 4"},
        .explanation = "Program int main() { ile başlar, içinde yazdırma ve return 0; yer alır, } ile kapanır: sıra 3 2 1 4.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 71, .topicId = 6,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir tam sayı okuyup ekrana yazdıran bir program yazın. (Kodunuzu birden fazla satırda yazabilirsiniz.)",
        .acceptedAnswers = {"cin", ">>", "cout", "<<"},
        .explanation = "Program bir tam sayıyı cin >> ile okumalı ve cout << ile ekrana yazdırmalıdır.",
        .baseXp = 40,
    });
    questions_.push_back(Question{
        .id = 72, .topicId = 10,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "PI için 3.14 değerinde, değeri değiştirilemeyen bir sabit tanımlayıp ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"const", "cout", "<<"},
        .explanation = "Değeri değiştirilemeyen bir değişken const ile tanımlanır ve cout << ile ekrana yazdırılır.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>

#include "QuestionManager.h"

int main() {
    QuestionManager questions;

    int total = 0;
    for (int topicId = 1; topicId <= 10; ++topicId) {
        total += static_cast<int>(questions.questionsForTopic(topicId).size());
    }
    std::cout << "Toplam soru sayisi: " << total << " (beklenen: 72)\n";

    std::cout << "Konu 1 soru sayisi: " << questions.questionsForTopic(1).size()
              << " (beklenen: 8)\n";
    std::cout << "Konu 2 soru sayisi: " << questions.questionsForTopic(2).size()
              << " (beklenen: 6, degismedi)\n";
    std::cout << "Konu 4 soru sayisi: " << questions.questionsForTopic(4).size()
              << " (beklenen: 9)\n";
    std::cout << "Konu 6 soru sayisi: " << questions.questionsForTopic(6).size()
              << " (beklenen: 9)\n";
    std::cout << "Konu 7 soru sayisi: " << questions.questionsForTopic(7).size()
              << " (beklenen: 7)\n";
    std::cout << "Konu 8 soru sayisi: " << questions.questionsForTopic(8).size()
              << " (beklenen: 7)\n";
    std::cout << "Konu 9 soru sayisi: " << questions.questionsForTopic(9).size()
              << " (beklenen: 7)\n";
    std::cout << "Konu 10 soru sayisi: " << questions.questionsForTopic(10).size()
              << " (beklenen: 7)\n";

    return 0;
}
```

- [ ] **Step 3: Build and run**

Run:
```bash
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line's actual count matches its "(beklenen: N)" annotation exactly (total 72; topic 1 = 8; topic 2 = 6; topic 4 = 9; topic 6 = 9; topic 7 = 7; topic 8 = 7; topic 9 = 7; topic 10 = 7). Zero compiler warnings.

- [ ] **Step 4: Commit**

```bash
git add src/QuestionManager.cpp src/main.cpp
git commit -m "Add 12 questions for CompleteLine/PredictOutput/FindError/FixCode/OrderCode/WriteCode"
```

---

### Task 4: Wire `Application` — render and answer the six new types

**Files:**
- Modify: `src/Application.cpp`

**Interfaces:**
- Consumes: `QuizEngine::evaluate` (Task 1), `ConsoleUI::readMultilineCode` (Task 2), the 12 new questions (Task 3).
- Produces: no public interface change — `Application`'s public surface (`Application()`, `run()`) is unchanged.

- [ ] **Step 1: Modify `runTopicQuiz` in `src/Application.cpp`**

Replace this block (the per-question rendering and answer-reading section):

```cpp
        if (question.type == QuestionType::MultipleChoice) {
            for (std::size_t index = 0; index < question.options.size(); ++index) {
                ui_.printLine(
                    std::string(1, optionLetter(index)) + ") " + question.options[index]);
            }
        } else if (question.type == QuestionType::TrueFalse) {
            ui_.printLine("1. Doğru");
            ui_.printLine("2. Yanlış");
        }

        const std::string rawAnswer = ui_.readLine("Cevabınız: ");
        const AnswerResult result = quizEngine_.evaluate(question, rawAnswer);
```

with:

```cpp
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
```

No other part of `Application.cpp`/`Application.h` changes — the rest of `runTopicQuiz` (scoring, XP, status update), `showTopicBrowser`, `openTopic`, `showLessonContent`, the main menu, and everything else stays exactly as phase 2 left it.

- [ ] **Step 2: `src/main.cpp` must be restored to its real entry-point form before verifying**

Confirm `src/main.cpp` currently reads exactly:
```cpp
#include "Application.h"

int main() {
    Application app;
    app.run();
    return 0;
}
```
(Tasks 1-3 of this plan each temporarily repurposed it as scratch verification code, per their own steps — restore it to this exact form now if it isn't already. Do not leave any task's scratch code in place.)

- [ ] **Step 3: Build**

Run:
```bash
cmake --build build
```
Expected: build succeeds with zero warnings.

- [ ] **Step 4: Full manual verification (this phase's acceptance test)**

Run these piped sessions against `./build/Debug/CppMasterConsole.exe` (adjust
the executable path for your generator). Each sequence below was traced by
hand against `src/QuestionManager.cpp`'s actual question order per topic
(insertion order: phase-2's original ids first, then this phase's new ids
appended after) — use them exactly as given rather than re-deriving them.

**Pass 1 — topic 6 (int): covers CompleteLine, PredictOutput, WriteCode.**
Topic 6's 9 questions in order are ids 31, 32, 33, 34, 35, 36 (phase 2),
then 61 (CompleteLine), 63 (PredictOutput), 71 (WriteCode). All-correct
answers: `b`, `c`, `2`, `1`, `int`, `7`, `toplam + 5`, `8`, then the
multi-line submission `int sayi;` / `cin >> sayi;` / `cout << sayi;` /
`BITIR`.
```bash
printf "1\n6\nb\nc\n2\n1\nint\n7\ntoplam + 5\n8\nint sayi;\ncin >> sayi;\ncout << sayi;\nBITIR\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: all 9 answered correctly; `CompleteLine` (id 61) and
`PredictOutput` (id 63) render as a plain prompt (no lettered options, no
1/2 options) answered via a single `Cevabınız:` line; the `WriteCode`
question (id 71) prints the "Kodunuzu birden fazla satır..." / "BITIR"
instruction and accepts the 3-line submission; final line reads
`Sonuç: 9/9 doğru (%100), kazanılan XP: 135` (10+20+5+10+10+20+10+10+40 =
135), topic marked `Completed`.

**Pass 2 — topic 4 (cin): covers CompleteLine (again, different question),
FixCode, OrderCode.**
Topic 4's 9 questions in order are ids 19-24 (phase 2), then 62
(CompleteLine), 68 (FixCode), 69 (OrderCode). All-correct answers: `b`,
`d`, `1`, `2`, `cin`, `>>`, `b`, `cin >> yas;`, `2 3 1`.
```bash
printf "1\n4\nb\nd\n1\n2\ncin\n>>\nb\ncin >> yas;\n2 3 1\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: all 9 correct; the `OrderCode` question (id 69) prints its 3
shuffled lines (`cout << yas;`, `int yas;`, `cin >> yas;`) numbered `1.`,
`2.`, `3.` and accepts `2 3 1`; final line reads
`Sonuç: 9/9 doğru (%100), kazanılan XP: 125` (10+20+5+10+10+20+20+20+10 =
125).

**Pass 3 — topic 1 (cout): covers FindError, OrderCode with 4 shuffled lines.**
Topic 1's 8 questions in order are ids 1-6 (phase 2), then 65 (FindError),
70 (OrderCode). All-correct answers: `b`, `c`, `2`, `1`, `cout`,
`iostream`, `int yas = 20;`, `3 2 1 4`.
```bash
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: all 8 correct; the `OrderCode` question (id 70) numbers all 4
options `1.`-`4.` and accepts `3 2 1 4`; final line reads
`Sonuç: 8/8 doğru (%100), kazanılan XP: 105` (10+20+5+10+10+20+10+20 = 105).

**Pass 4 — deliberate wrong answers, to check feedback rendering.**
Answer topic 6's ids 31-36 correctly (6 correct), then answer `CompleteLine`
(id 61) wrong, `PredictOutput` (id 63) correctly, and `WriteCode` (id 71)
incompletely (missing `cout`/`<<`):
```bash
printf "1\n6\nb\nc\n2\n1\nint\n7\ntoplam - 1\n8\nint sayi;\ncin >> sayi;\nBITIR\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm: for id 61 (`CompleteLine`, answered `toplam - 1`), the wrong-answer
block shows `Doğru cevap:` as `toplam + 5` (the first accepted answer,
verbatim); id 63 (`PredictOutput`, answered `8`) is correct as normal; for
id 71 (`WriteCode`, submitted `int sayi;` / `cin >> sayi;` / `BITIR` —
missing `cout`/`<<`), the wrong-answer block's `Doğru cevap:` line reads
`Gerekli öğeler: cin, >>, cout, <<` (the full requirements list, not a
single literal answer, since there is no one correct `WriteCode`
submission); final line reads
`Sonuç: 7/9 doğru (%77), kazanılan XP: 85` (the 6 phase-2 questions' 75 XP
plus id 63's 10 XP; ids 61 and 71 contribute 0), topic marked `Completed`
(7/9 ≈ 78% clears the 70% threshold).

Confirm throughout all four passes: no crash, no hang, all Turkish text
renders correctly, and every `Sonuç:`/`Toplam XP:` line matches the
hand-computed values above exactly.

- [ ] **Step 5: Commit**

```bash
git add src/Application.cpp
git commit -m "Wire Application to render and evaluate the six new question types, completing phase 3"
```

---

## Post-plan note

This completes phase 3 (Richer Question Types). `Matching` and `Scenario`
remain unused `QuestionType` values — not this phase's scope. Phase 4
(persistence + review loop) gets its own brainstorming → spec → plan cycle,
since it introduces `ProgressManager` and file I/O, neither of which exist
yet.

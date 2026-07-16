# CppMaster Console — İpucu Sistemi (Hint System) Implementation Plan (Phase 10)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the five in-quiz commands the original brief requires
(`ipucu`, `konu`, `ornek`, `gec`, `cikis`) to every non-`WriteCode` question,
with three escalating, fully-computed hint levels (no new authored content),
an XP penalty for hints used, disabling help commands during the section
exam, and a clean early-exit path back to the main menu.

**Architecture:** A new pure-logic header/source pair (`src/HintProvider.h`/`.cpp`)
computes hints from a `Question`'s existing fields — no new data, no state.
`QuizEngine` exposes its existing internal "what does the correct answer
look like" logic as a public method (`correctAnswerDisplay`) so `Application`
can show it for a skipped (`gec`) question without needing a submitted
answer, and `AnswerResult` gains an `exitRequested` flag that only
`Application::askOneQuestion` ever sets. `askOneQuestion`'s single-line
answer read becomes a small command-recognizing loop; all four of its
callers (`runTopicQuiz`, `runQuickTest`, `runMistakeQuestions`,
`runSectionExam`) check the new flag and return to the main menu
immediately when set — awarding whatever XP was already earned in the
partial session first.

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only.

**Spec:** `docs/superpowers/specs/2026-07-16-hint-system-design.md`

## Global Constraints

- C++20 required, CMake ≥ 3.20, standard library only.
- Zero compiler warnings on the library, app, and test executable (`apply_strict_warnings()`).
- No `using namespace std;` anywhere.
- Tests never touch `data/`.
- The 5 commands are recognized by **exact, case-sensitive string match** on
  the trimmed-by-nothing raw input (consistent with how `ConsoleUI::readMultilineCode`
  already recognizes `BITIR` exactly) — no whitespace tolerance, no
  case-insensitivity. Document this as intentional if asked; do not add
  trimming.
- `WriteCode` questions are completely unaffected by this phase — their
  answer is still read via `ui_.readMultilineCode()` with no command
  recognition.
- `ipucu`/`konu`/`ornek` are disabled specifically during the section exam
  (`runSectionExam` passes `allowHints = false`); `gec`/`cikis` remain
  available everywhere.
- Before running any task's manual verification below, delete
  `data/progress.txt`, `data/mistakes.txt`, `data/achievements.txt`,
  `data/generated_question_history.txt`, and `data/settings.txt` if they
  exist.
- After Task 3's final commit, update `docs/superpowers/roadmap.md`'s
  Phase 10 entry and Status section to mark it COMPLETE with its commit
  range — this is now a standing requirement recorded in the roadmap
  itself after being missed at the end of both Phase 8 and Phase 9.

---

### Task 1: `HintProvider.h`/`.cpp` — pure, computed hint generation

**Files:**
- Create: `src/HintProvider.h`
- Create: `src/HintProvider.cpp`
- Create: `tests/HintProviderTests.cpp`
- Modify: `CMakeLists.txt`

**Interfaces:**
- Consumes: `Question`/`QuestionType` (`src/Question.h`, `src/Enums.h`, unchanged).
- Produces: `std::string generateHint(const Question& question, int hintLevel)`
  (`hintLevel` is 1, 2, or 3) — Task 3's `Application::askOneQuestion` calls
  this by exact name.

- [ ] **Step 1: Create `src/HintProvider.h`**

```cpp
#pragma once

#include <string>

#include "Question.h"

[[nodiscard]] std::string generateHint(const Question& question, int hintLevel);
```

- [ ] **Step 2: Create `src/HintProvider.cpp`**

```cpp
#include "HintProvider.h"

#include <cctype>
#include <cstddef>
#include <stdexcept>

namespace {

std::string genericTipFor(QuestionType type) {
    switch (type) {
        case QuestionType::MultipleChoice:
            return "Seçenekleri tek tek elemeye çalış; açıkça yanlış olanları çıkar.";
        case QuestionType::TrueFalse:
            return "İfadeyi parça parça oku; tek bir kelime bile ifadeyi yanlış yapabilir.";
        case QuestionType::FillBlank:
            return "Boşluğa gelecek kelimeyi ders anlatımındaki sözdizimini hatırlayarak düşün.";
        case QuestionType::CompleteLine:
            return "Kodun geri kalanına bakarak eksik satırın ne yapması gerektiğini düşün.";
        case QuestionType::PredictOutput:
            return "Kodu satır satır, değişkenlerin değerini takip ederek zihninde çalıştır.";
        case QuestionType::FindError:
            return "Noktalı virgül, parantez ve tırnak işaretlerini tek tek kontrol et.";
        case QuestionType::FixCode:
            return "Hatanın hangi satırda olduğunu bulduktan sonra o satırı nasıl düzelteceğini düşün.";
        case QuestionType::OrderCode:
            return "Bir C++ programının genel akışını (tanımlama, işlem, çıktı) hatırla.";
        case QuestionType::WriteCode:
        case QuestionType::Scenario:
        case QuestionType::Matching:
            return "Sorunun ne istediğini tekrar dikkatlice oku.";
    }
    return "Sorunun ne istediğini tekrar dikkatlice oku.";
}

int wordCount(const std::string& text) {
    int count = 0;
    bool inWord = false;
    for (const char character : text) {
        const bool isSpace = std::isspace(static_cast<unsigned char>(character)) != 0;
        if (!isSpace && !inWord) {
            ++count;
        }
        inWord = !isSpace;
    }
    return count;
}

std::string firstOptionNotAccepted(const Question& question) {
    for (std::size_t index = 0; index < question.options.size(); ++index) {
        const char letter = static_cast<char>('a' + static_cast<int>(index));
        bool isAccepted = false;
        for (const std::string& accepted : question.acceptedAnswers) {
            if (!accepted.empty() && accepted.front() == letter) {
                isAccepted = true;
                break;
            }
        }
        if (!isAccepted) {
            const char upperLetter = static_cast<char>('A' + static_cast<int>(index));
            return std::string(1, upperLetter) + ") " + question.options[index];
        }
    }
    return "";
}

std::string computedClueFor(const Question& question) {
    if (question.acceptedAnswers.empty()) {
        return "Sorunun ne istediğini tekrar dikkatlice oku.";
    }
    const std::string& answer = question.acceptedAnswers.front();

    switch (question.type) {
        case QuestionType::MultipleChoice: {
            const std::string wrongOption = firstOptionNotAccepted(question);
            return wrongOption.empty() ? "Seçenekleri tekrar dikkatlice karşılaştır."
                                        : wrongOption + " kesinlikle yanlış.";
        }
        case QuestionType::TrueFalse:
            return "Cevap genellikle ders anlatımındaki net ifadeyle doğrudan ilgilidir; "
                   "'her zaman/asla' gibi kesin ifadelere dikkat et.";
        case QuestionType::FillBlank:
        case QuestionType::CompleteLine:
            return "Doğru cevap " + std::to_string(wordCount(answer)) + " kelimeden oluşuyor.";
        case QuestionType::PredictOutput: {
            try {
                std::size_t consumedChars = 0;
                const int value = std::stoi(answer, &consumedChars);
                if (consumedChars == answer.size()) {
                    const std::string sign =
                        value > 0 ? "pozitif" : (value < 0 ? "negatif" : "sıfır");
                    return "Doğru cevap " + sign + " bir sayı.";
                }
            } catch (const std::exception&) {
                // Not a plain integer - fall through to the word-count clue below.
            }
            return "Doğru cevap " + std::to_string(wordCount(answer)) + " kelimeden oluşuyor.";
        }
        case QuestionType::FindError:
        case QuestionType::FixCode:
            return answer.empty() ? "Sorunun ne istediğini tekrar dikkatlice oku."
                                   : std::string("Doğru satır '") + answer.front() +
                                         "' harfiyle başlıyor.";
        case QuestionType::OrderCode:
            return "Sıralaman gereken toplam adım sayısı: " +
                   std::to_string(question.options.size()) + ".";
        case QuestionType::WriteCode:
        case QuestionType::Scenario:
        case QuestionType::Matching:
            return "Sorunun ne istediğini tekrar dikkatlice oku.";
    }
    return "Sorunun ne istediğini tekrar dikkatlice oku.";
}

}  // namespace

std::string generateHint(const Question& question, int hintLevel) {
    if (hintLevel <= 1) {
        return genericTipFor(question.type);
    }
    if (hintLevel == 2) {
        return computedClueFor(question);
    }
    return question.explanation;
}
```

- [ ] **Step 3: Create `tests/HintProviderTests.cpp`**

```cpp
#include "HintProvider.h"

#include <string>
#include <utility>
#include <vector>

#include "TestRunner.h"

namespace {

Question makeQuestion(
    QuestionType type, std::vector<std::string> acceptedAnswers,
    std::vector<std::string> options = {}, std::string explanation = "Test açıklaması.") {
    Question question;
    question.id = 1;
    question.topicId = 1;
    question.type = type;
    question.acceptedAnswers = std::move(acceptedAnswers);
    question.options = std::move(options);
    question.explanation = std::move(explanation);
    question.baseXp = 10;
    return question;
}

}  // namespace

TEST_CASE(HintProvider_Level3AlwaysReturnsExplanation) {
    const Question question = makeQuestion(QuestionType::FillBlank, {"cout"}, {}, "Açıklama metni.");
    CHECK(generateHint(question, 3) == "Açıklama metni.");
}

TEST_CASE(HintProvider_Level1And2And3AreMutuallyDistinct) {
    const Question question =
        makeQuestion(QuestionType::PredictOutput, {"8"}, {}, "Açıklama metni.");
    const std::string level1 = generateHint(question, 1);
    const std::string level2 = generateHint(question, 2);
    const std::string level3 = generateHint(question, 3);
    CHECK(level1 != level2);
    CHECK(level2 != level3);
    CHECK(level1 != level3);
}

TEST_CASE(HintProvider_MultipleChoiceLevel2NamesAWrongOption) {
    const Question question =
        makeQuestion(QuestionType::MultipleChoice, {"b"}, {"cin", "cout", "endl", "return"});
    const std::string hint = generateHint(question, 2);
    CHECK(hint.find("A)") != std::string::npos);
    CHECK(hint.find("cin") != std::string::npos);
}

TEST_CASE(HintProvider_FillBlankLevel2RevealsWordCount) {
    const Question question = makeQuestion(QuestionType::FillBlank, {"iostream kütüphanesi"});
    const std::string hint = generateHint(question, 2);
    CHECK(hint.find("2") != std::string::npos);
}

TEST_CASE(HintProvider_PredictOutputLevel2RevealsSignForNumericAnswer) {
    const Question positive = makeQuestion(QuestionType::PredictOutput, {"8"});
    CHECK(generateHint(positive, 2).find("pozitif") != std::string::npos);

    const Question negative = makeQuestion(QuestionType::PredictOutput, {"-3"});
    CHECK(generateHint(negative, 2).find("negatif") != std::string::npos);

    const Question textual = makeQuestion(QuestionType::PredictOutput, {"Merhaba"});
    CHECK(generateHint(textual, 2).find("kelime") != std::string::npos);
}

TEST_CASE(HintProvider_FindErrorLevel2RevealsFirstCharacter) {
    // Uses an accepted answer starting with 'd', a letter that does not
    // appear anywhere in the clue's fixed boilerplate ("Doğru satır '..'
    // harfiyle başlıyor.") other than inside the quotes - so this genuinely
    // pins down the first-character extraction instead of always passing.
    const Question question = makeQuestion(QuestionType::FindError, {"double x = 5.0;"});
    const std::string hint = generateHint(question, 2);
    CHECK(hint.find('d') != std::string::npos);
}

TEST_CASE(HintProvider_OrderCodeLevel2RevealsStepCount) {
    const Question question = makeQuestion(
        QuestionType::OrderCode, {"2 3 1"}, {"cout << yas;", "int yas;", "cin >> yas;"});
    const std::string hint = generateHint(question, 2);
    CHECK(hint.find("3") != std::string::npos);
}
```

- [ ] **Step 4: Add the new files to `CMakeLists.txt`**

Add `src/HintProvider.h`, `src/HintProvider.cpp` to
`add_library(CppMasterConsoleLib STATIC ...)`'s source list, and
`tests/HintProviderTests.cpp` to `add_executable(CppMasterConsoleTests ...)`'s
source list.

- [ ] **Step 5: Build and run**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
./build/Debug/CppMasterConsoleTests.exe
```
Expected: `74/74 test(s) passed.` (67 from Phase 9 + 7 new `HintProvider`
tests). Zero warnings.

- [ ] **Step 6: Commit**

```bash
git add CMakeLists.txt src/HintProvider.h src/HintProvider.cpp tests/HintProviderTests.cpp
git commit -m "Add HintProvider: computed, type-aware hint generation with no new authored content"
```

---

### Task 2: `QuizEngine` exposes `correctAnswerDisplay`; `AnswerResult` gains `exitRequested`

**Files:**
- Modify: `src/QuizEngine.h`
- Modify: `src/QuizEngine.cpp`
- Modify: `tests/QuizEngineTests.cpp`

**Interfaces:**
- Consumes: nothing new.
- Produces: `AnswerResult { bool correct; int xpAwarded; std::string correctAnswerDisplay; bool exitRequested = false; }`,
  `std::string QuizEngine::correctAnswerDisplay(const Question& question) const` —
  Task 3's `Application::askOneQuestion` uses both by exact name.

- [ ] **Step 1: Modify `src/QuizEngine.h`**

```cpp
#pragma once

#include <string>

#include "Question.h"
#include "Settings.h"

struct AnswerResult {
    bool correct;
    int xpAwarded;
    std::string correctAnswerDisplay;
    bool exitRequested = false;
};

class QuizEngine {
public:
    [[nodiscard]] AnswerResult evaluate(
        const Question& question, const std::string& rawAnswer,
        const Settings& settings = Settings{}) const;
    [[nodiscard]] std::string correctAnswerDisplay(const Question& question) const;
};
```

- [ ] **Step 2: Modify `src/QuizEngine.cpp`**

Add a new free function `computeCorrectAnswerDisplay` right after the
existing `writeCodeRequirementsDisplay` function (still inside the
anonymous namespace), then simplify `evaluate` to use it and add the new
public method. The parts of the file before `writeCodeRequirementsDisplay`
(everything from `trimAndLower` through `writeCodeRequirementsDisplay`
itself) are unchanged — only the closing of the anonymous namespace and
everything after it changes. Full new content from
`writeCodeRequirementsDisplay` to the end of the file:

```cpp
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

std::string computeCorrectAnswerDisplay(const Question& question) {
    switch (question.type) {
        case QuestionType::MultipleChoice:
        case QuestionType::TrueFalse:
        case QuestionType::FillBlank:
            return correctAnswerDisplayFor(question);
        case QuestionType::WriteCode:
            return writeCodeRequirementsDisplay(question);
        case QuestionType::CompleteLine:
        case QuestionType::PredictOutput:
        case QuestionType::FindError:
        case QuestionType::FixCode:
        case QuestionType::OrderCode:
            return question.acceptedAnswers.empty() ? "" : question.acceptedAnswers.front();
        case QuestionType::Scenario:
        case QuestionType::Matching:
            return "";
    }
    return "";
}

}  // namespace

AnswerResult QuizEngine::evaluate(
    const Question& question, const std::string& rawAnswer, const Settings& settings) const {
    bool isCorrect = false;

    switch (question.type) {
        case QuestionType::MultipleChoice:
        case QuestionType::TrueFalse:
        case QuestionType::FillBlank:
            isCorrect = matchesAnyAcceptedCaseInsensitive(question, rawAnswer);
            break;
        case QuestionType::CompleteLine:
        case QuestionType::PredictOutput:
        case QuestionType::FindError:
        case QuestionType::FixCode:
            isCorrect = matchesAnyAcceptedCaseSensitiveWhitespaceNormalized(
                question, rawAnswer, settings.strictCaseSensitivity);
            break;
        case QuestionType::OrderCode:
            isCorrect = matchesOrderCode(question, rawAnswer);
            break;
        case QuestionType::WriteCode:
            isCorrect = matchesWriteCode(question, rawAnswer, settings.lenientWriteCodeTolerance);
            break;
        default:
            break;
    }

    return AnswerResult{
        isCorrect, isCorrect ? question.baseXp : 0, computeCorrectAnswerDisplay(question), false};
}

std::string QuizEngine::correctAnswerDisplay(const Question& question) const {
    return computeCorrectAnswerDisplay(question);
}
```

(This changes `evaluate`'s `display` computation from an inline per-branch
assignment to a single shared call at the return statement — the mapping
from `QuestionType` to display string is unchanged for every type, so no
existing test's expected display output changes.)

- [ ] **Step 3: Add two tests to `tests/QuizEngineTests.cpp`**

Append at the end of the file (after the two Phase 8 settings-aware tests):

```cpp
TEST_CASE(QuizEngine_CorrectAnswerDisplayMatchesEvaluateOutput) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::FindError, {"int yas = 20;"});
    const AnswerResult wrongResult = engine.evaluate(question, "wrong answer");
    CHECK(engine.correctAnswerDisplay(question) == wrongResult.correctAnswerDisplay);
}

TEST_CASE(QuizEngine_AnswerResultExitRequestedDefaultsToFalse) {
    // Constructs AnswerResult directly, omitting exitRequested, so this
    // actually exercises the struct's default member initializer - calling
    // evaluate() instead would only prove its own hardcoded literal `false`,
    // not the default.
    const AnswerResult result{true, 10, "x"};
    CHECK(!result.exitRequested);
}
```

- [ ] **Step 4: Build and run**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
./build/Debug/CppMasterConsoleTests.exe
```
Expected: `76/76 test(s) passed.` (74 from Task 1 + 2 new). Zero warnings —
every pre-existing `QuizEngineTests.cpp` case (all 12 from Phases 7-8) must
still pass unchanged.

- [ ] **Step 5: Commit**

```bash
git add src/QuizEngine.h src/QuizEngine.cpp tests/QuizEngineTests.cpp
git commit -m "Expose QuizEngine::correctAnswerDisplay and add AnswerResult::exitRequested"
```

---

### Task 3: Wire the 5 commands into `Application`, XP penalty, early exit, manual verification

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`

**Interfaces:**
- Consumes: `generateHint` (Task 1), `QuizEngine::correctAnswerDisplay`/`AnswerResult::exitRequested` (Task 2).
- Produces: nothing consumed by later tasks — final task of this phase.

- [ ] **Step 1: Modify `src/Application.h`**

Add `#include "HintProvider.h"` to the include block (alongside
`#include "AchievementTracker.h"`), and change `askOneQuestion`'s
declaration to:
```cpp
    AnswerResult askOneQuestion(
        const Question& question, bool trackMistakes = true, bool allowHints = true);
```
(This is the only change to `Application.h` — no new members, no other new
declarations.)

- [ ] **Step 2: Replace `Application::askOneQuestion`'s body**

Replace the entire function (currently the whole body between its
signature and the closing brace before `Application::awardXpAndCheckLevelUp`)
with:

```cpp
AnswerResult Application::askOneQuestion(
    const Question& question, bool trackMistakes, bool allowHints) {
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

    int hintLevelUsed = 0;
    std::string rawAnswer;
    bool skipped = false;
    bool exitRequested = false;

    if (question.type == QuestionType::WriteCode) {
        ui_.printLine(
            "Kodunuzu birden fazla satır halinde girebilirsiniz. Bitirmek için BITIR yazıp Enter'a basın.");
        rawAnswer = ui_.readMultilineCode();
    } else {
        while (true) {
            rawAnswer = ui_.readLine("Cevabınız: ");
            if (rawAnswer == "cikis") {
                exitRequested = true;
                break;
            }
            if (rawAnswer == "gec") {
                skipped = true;
                break;
            }
            if (rawAnswer == "ipucu") {
                if (!allowHints) {
                    ui_.printLine("Sınav sırasında ipucu kullanılamaz.");
                    continue;
                }
                if (hintLevelUsed < 3) {
                    ++hintLevelUsed;
                }
                ui_.printLine(generateHint(question, hintLevelUsed));
                continue;
            }
            if (rawAnswer == "konu") {
                if (!allowHints) {
                    ui_.printLine("Sınav sırasında bu komut kullanılamaz.");
                    continue;
                }
                const auto lesson = lessons_.findById(question.topicId);
                if (lesson.has_value() && !lesson->explanation.empty()) {
                    ui_.printLine(lesson->explanation);
                } else {
                    ui_.printLine("Bu konu için ders içeriği bu sürümde henüz eklenmedi.");
                }
                continue;
            }
            if (rawAnswer == "ornek") {
                if (!allowHints) {
                    ui_.printLine("Sınav sırasında bu komut kullanılamaz.");
                    continue;
                }
                const auto lesson = lessons_.findById(question.topicId);
                if (lesson.has_value() && !lesson->exampleCode.empty()) {
                    ui_.printLine(lesson->exampleCode);
                } else {
                    ui_.printLine("Bu konu için örnek bu sürümde henüz eklenmedi.");
                }
                continue;
            }
            break;
        }
    }

    if (exitRequested) {
        return AnswerResult{false, 0, "", true};
    }

    AnswerResult result;
    if (skipped) {
        result = AnswerResult{false, 0, quizEngine_.correctAnswerDisplay(question), false};
    } else {
        result = quizEngine_.evaluate(question, rawAnswer, settings_);
        if (result.correct && hintLevelUsed > 0) {
            const double multiplier = 1.0 - (0.25 * hintLevelUsed);
            result.xpAwarded = static_cast<int>(static_cast<double>(result.xpAwarded) * multiplier);
        }
    }

    if (result.correct) {
        ui_.printLine("Doğru! (+" + std::to_string(result.xpAwarded) + " XP)");
    } else {
        ui_.printLine("");
        ui_.printLine("Yanlış cevap.");
        ui_.printLine("");
        ui_.printLine("Senin cevabın:");
        ui_.printLine(skipped ? "(soru geçildi)" : rawAnswer);
        ui_.printLine("");
        ui_.printLine("Doğru cevap:");
        ui_.printLine(result.correctAnswerDisplay);
        ui_.printLine("");
        ui_.printLine("Açıklama:");
        ui_.printLine(question.explanation);
    }
    ui_.printLine("");

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
}
```

- [ ] **Step 3: Update `runTopicQuiz` to handle early exit**

Change the loop:
```cpp
    for (const Question& question : quizQuestions) {
        const AnswerResult result = askOneQuestion(question);
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }
    }
```
to:
```cpp
    for (const Question& question : quizQuestions) {
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
        }
    }
```

- [ ] **Step 4: Update `runQuickTest` to handle early exit**

Change:
```cpp
        generated->question.id = nextGeneratedQuestionId_++;
        const AnswerResult result = askOneQuestion(generated->question, /*trackMistakes=*/false);
        ++askedCount;
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }

        generationEngine_.saveHistory(kGeneratedHistoryFilePath);
```
to:
```cpp
        generated->question.id = nextGeneratedQuestionId_++;
        const AnswerResult result = askOneQuestion(generated->question, /*trackMistakes=*/false);
        if (result.exitRequested) {
            generationEngine_.saveHistory(kGeneratedHistoryFilePath);
            awardXpAndCheckLevelUp(sessionXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
        ++askedCount;
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }

        generationEngine_.saveHistory(kGeneratedHistoryFilePath);
```

- [ ] **Step 5: Update `runMistakeQuestions` to handle early exit**

Change:
```cpp
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
```
to:
```cpp
    for (const MistakeRecord& mistake : mistakesToAsk) {
        const auto question = questions_.findById(mistake.questionId);
        if (!question.has_value()) {
            continue;
        }
        const AnswerResult result = askOneQuestion(*question);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(sessionXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }
    }
```

- [ ] **Step 6: Update `runSectionExam`** — disable hints and handle early exit

Change:
```cpp
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
```
to:
```cpp
    for (const int questionId : kExamQuestionIds) {
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
```

- [ ] **Step 7: Build**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
```
Expected: zero warnings.

- [ ] **Step 8: Run the full test suite**

```bash
./build/Debug/CppMasterConsoleTests.exe
cd build && ctest -C Debug --output-on-failure && cd ..
```
Expected: `76/76 test(s) passed.`, `ctest` 100%.

- [ ] **Step 9: Manual verification — all 5 commands in one topic-1 quiz run**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
printf "1\n1\nipucu\nipucu\nipucu\nb\ngec\nkonu\n2\nornek\n1\ncikis\n0\n" | ./build/Debug/CppMasterConsole.exe
```

This pipes: main menu → Konuları Öğren (1), topic 1 (1) — starts the
8-question topic-1 quiz (ids 1,2,3,4,5,6,65,70, all with real content).
- **Q1** (id 1, MultipleChoice, "b", baseXp 10): `ipucu` three times, then
  `b`. Confirm three **different** hint lines print, in this exact order:
  1. `Seçenekleri tek tek elemeye çalış; açıkça yanlış olanları çıkar.`
  2. `A) cin kesinlikle yanlış.`
  3. `cout, ekrana veri yazdırmak için kullanılan çıktı akışıdır; cin ise klavyeden veri okumak için kullanılır.`
  Then confirm `Doğru! (+2 XP)` (3 hints used → 25% of 10 → `static_cast<int>(10.0 * 0.25)` = 2) —
  and the `İlk Adım` achievement unlock (first-ever correct answer).
- **Q2** (id 2, MultipleChoice, "c", baseXp 20): `gec`. Confirm `Yanlış cevap.`,
  `Senin cevabın: (soru geçildi)`, `Doğru cevap: C) <iostream>`, and the
  explanation line for id 2 prints.
- **Q3** (id 3, TrueFalse, "2", baseXp 5): `konu`, then `2`. Confirm the
  `konu` command reprints topic 1's lesson explanation exactly:
  `cout, ekrana veri yazdırmak için kullanılan bir çıktı akışıdır (output stream). Kullanabilmek için <iostream> kütüphanesinin eklenmesi gerekir. << operatörü ile bir veya birden fazla değer art arda ekrana yazdırılabilir.`
  then confirm `Doğru! (+5 XP)` (no hints used on this question → full XP).
- **Q4** (id 4, TrueFalse, "1", baseXp 10): `ornek`, then `1`. Confirm the
  `ornek` command reprints topic 1's lesson example code exactly:
  ```
  #include <iostream>

  int main() {
      std::cout << "Merhaba, dünya!";
      return 0;
  }
  ```
  then confirm `Doğru! (+10 XP)`.
- **Q5** (id 5, FillBlank, "cout", baseXp 10): `cikis`. Confirm the app
  returns directly to the main menu with **no** further questions asked (ids
  6, 65, 70 never appear) and **no** "Sonuç: X/Y" summary line for this
  quiz — the very next thing printed is the main menu header.
- The trailing `0` exits the app from the main menu.

- [ ] **Step 10: Confirm accumulated state after Step 9**

```bash
grep "^xp " data/progress.txt
```
Expected: `xp 17` (2 from Q1 + 0 from Q2 + 5 from Q3 + 10 from Q4 — matches
`sessionXp` at the moment of the `cikis` early return, confirmed awarded
via `awardXpAndCheckLevelUp` before the early `return`). Then:
```bash
grep "^mistake 2" data/mistakes.txt
```
Expected: a line for question id `2` exists (recorded via `gec`).

Clean up:
```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
```

- [ ] **Step 11: Manual verification — hints disabled during the section exam**

Craft a 70%-complete Section 1 progress file (same technique as Phase 9
Task 3's Step 8) so the exam is reachable, then attempt `ipucu` on the
exam's first question:

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
{
  echo "xp 0"; echo "answered 0"; echo "correct 0"; echo "streak_current 0"
  echo "streak_longest 0"; echo "writecode_correct 0"; echo "errorfix_correct 0"
  echo "highest_section_exam_passed 0"
  for i in $(seq 1 10); do echo "topic $i Completed"; done
  for i in $(seq 11 100); do echo "topic $i NotStarted"; done
} > data/progress.txt
printf "6\nipucu\nb\nc\n2\n1\ncout\niostream\nb\nd\n2\nint\ntoplam + 5\nb\n8\n0\nint yas = 20;\nchar harf = 'A';\ndouble ortalama = 87.5;\ncin >> yas;\n2 3 1\nint sayi;\ncin >> sayi;\ncout << sayi;\nBITIR\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```

Confirm: after `6` (Seviye Sınavı, unlocked since Section 1 is
crafted-complete), the first line of input for question 1 is `ipucu`, and
the app prints exactly `Sınav sırasında ipucu kullanılamaz.` and re-prompts
`Cevabınız: ` for the **same** question (does not advance, does not treat
`ipucu` as a wrong answer) — then `b` is accepted normally as question 1's
real answer, and the exam proceeds through all 20 questions as in Phase 9's
verified transcript, ending `Doğru: 20/20`, `Sonuç: GEÇTİN`.

Clean up:
```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
```

- [ ] **Step 12: Regression check — a question answered with zero commands still earns full XP**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
printf "1\n1\nb\nc\n2\n1\ncout\niostream\nint yas = 20;\n3 2 1 4\n0\n" | ./build/Debug/CppMasterConsole.exe
```
Confirm this still produces exactly the known Phase-1-era result: `İlk
Adım`/`Hatasız Beşli` unlocks, `Sonuç: 8/8 doğru (%100), kazanılan XP: 105`,
the level-2 celebration, and empty `data/mistakes.txt` — proving that
answering every question directly (no hint/skip/exit commands used at all)
still earns exactly the same XP as every prior phase, unaffected by this
phase's changes.

Clean up all `data/*.txt` files after this step.

- [ ] **Step 13: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Wire ipucu/konu/ornek/gec/cikis commands into askOneQuestion with XP penalty and early exit"
```

- [ ] **Step 14: Update the roadmap**

Edit `docs/superpowers/roadmap.md`: change the Phase 10 entry in the phase
list to mark it **COMPLETE** with its commit range (from Task 1's first
commit through Task 3's final commit), following the exact style of the
Phase 8/Phase 9 entries already in that file, and update the Status section
to name Phase 10 as complete and Phase 11 as starting next.

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 10 complete in roadmap"
```

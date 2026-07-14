# CppMaster Console — Foundation Phase Design

## Context

CppMaster Console is a terminal-based C++ learning and exam application covering
100 C++ topics across 10 sections, ultimately including quizzes, spaced
repetition, exams, achievements, and — in a later phase — a dynamic question
generation engine. The full scope (see product spec, not reproduced here) is
too large for a single implementation pass, so it is being decomposed into
sequential sub-projects, each with its own design → plan → build cycle:

1. **Foundation** (this document)
2. Static lesson + quiz core (first ~10 topics, MC/TF/fill-blank scoring, XP)
3. Richer question types (code completion, predict-output, find-error,
   fix-code, order-code, write-code structural evaluation)
4. Persistence + review loop (progress save/load, mistakes tracking, daily
   spaced-repetition review, statistics screen)
5. Meta systems (achievements, level/section exams, final exam, adaptive
   difficulty)
6. Dynamic question-generation engine (fingerprinting, generator registry,
   ~15 initial generators)
7. Polish (unit tests, README, remaining topics' generators, platform checks)

This document specs **phase 1 only: Foundation**.

## Goal

Produce a compiling, runnable skeleton of CppMaster Console: safe menu
navigation, the full 100-topic catalog as browsable data, and the core data
model that later phases build on. No feature is faked — anything not yet
built says so honestly rather than pretending to work.

## Non-goals (explicitly deferred to later phases)

- Lesson content bodies (explanation/syntax/example code) — phase 2.
- Any question types, quiz scoring, or XP — phase 2/3.
- File persistence (`progress.txt`, `settings.txt`, `mistakes.txt` contents
  and formats) — phase 4. Foundation only ensures the `data/` directory
  exists.
- `Question`, `QuestionManager`, `QuizEngine`, `ProgressManager`,
  `StatisticsManager` classes are **not created in this phase** — they would
  be empty shells with no real behavior yet, which is the fake-placeholder
  pattern this project explicitly avoids. They are introduced in the phases
  where they have genuine work to do.

## Technology

- C++20, CMake ≥ 3.20, no external dependencies.
- Must configure and build on Windows (MSVC), Linux (GCC/Clang), and macOS
  (Clang) — verified in this phase only on the current platform (Windows);
  cross-platform build correctness for the others is a code-review concern
  (avoid platform-specific APIs outside `#ifdef` guards), not something this
  phase can test directly.
- Warnings: `/W4 /permissive-` on MSVC; `-Wall -Wextra -Wpedantic
  -Wconversion -Wshadow` on GCC/Clang.

## File layout (this phase)

```
CMakeLists.txt
src/
├── main.cpp
├── Application.h / Application.cpp
├── ConsoleUI.h / ConsoleUI.cpp
├── LessonManager.h / LessonManager.cpp
├── Lesson.h / Lesson.cpp
├── UserProgress.h / UserProgress.cpp
└── Enums.h
data/                       (created empty at startup if missing)
docs/superpowers/specs/     (this document)
```

`CMakeLists.txt` sets `project(CppMasterConsole)` and
`add_executable(CppMasterConsole ...)`. The on-disk project folder name is
unchanged.

## Data model

### `Enums.h`

```cpp
enum class QuestionType {
    MultipleChoice, TrueFalse, FillBlank, CompleteLine, PredictOutput,
    FindError, FixCode, OrderCode, WriteCode, Scenario, Matching
};

enum class Difficulty {
    VeryEasy = 1, Easy = 2, Medium = 3, Hard = 4, VeryHard = 5
};

enum class TopicStatus { NotStarted, Learning, Completed, Mastered };
```

`QuestionType` and `Difficulty` are not used by any logic in this phase —
they are defined now because `Lesson`/`UserProgress` and every later phase
depend on a stable shared enum header, and splitting them out avoids a
churny rename later. This is justified up front rather than left implicit.

### `Lesson` (`Lesson.h/.cpp`)

Represents one of the 100 topics. In this phase only the catalog fields are
populated; content fields exist on the struct (so phase 2 doesn't need a
breaking change) but are left empty.

```cpp
struct Lesson {
    int id;                 // 1..100, matches the product spec numbering
    int sectionId;          // 1..10
    std::string title;      // e.g. "vector"

    // Populated in phase 2:
    std::string explanation;
    std::string syntax;
    std::string exampleCode;
    std::vector<std::string> lineExplanations;
    std::vector<std::string> commonMistakes;
};
```

### `LessonManager` (`LessonManager.h/.cpp`)

Owns the full catalog: 10 sections, 100 topics, built once in a constructor
from a hardcoded initializer list (matching the product spec's topic list
verbatim — Bölüm 1: Giriş/çıkış/değişkenler through Bölüm 10:
Algoritmalar/dosyalar/hata yönetimi).

Public interface:

```cpp
class LessonManager {
public:
    LessonManager();

    [[nodiscard]] const std::vector<Lesson>& allLessons() const;
    [[nodiscard]] std::vector<Lesson> lessonsInSection(int sectionId) const;
    [[nodiscard]] std::optional<Lesson> findById(int topicId) const;
    [[nodiscard]] std::string sectionTitle(int sectionId) const;
    [[nodiscard]] int sectionCount() const;

private:
    std::vector<Lesson> lessons_;
    std::vector<std::string> sectionTitles_;
};
```

### `UserProgress` (`UserProgress.h/.cpp`)

In-memory only in this phase (no file I/O — that's phase 4's job).

```cpp
class UserProgress {
public:
    explicit UserProgress(int topicCount);

    [[nodiscard]] TopicStatus statusOf(int topicId) const;
    void setStatus(int topicId, TopicStatus status);

private:
    std::unordered_map<int, TopicStatus> statusByTopicId_;
};
```

All topics default to `TopicStatus::NotStarted`. `Application` constructs one
instance for the process lifetime; nothing persists it yet.

## `ConsoleUI`

Centralizes all terminal I/O so later phases don't hand-roll input parsing.

```cpp
class ConsoleUI {
public:
    ConsoleUI();  // performs UTF-8 console setup

    void clearScreen() const;         // always clears in this phase; a disable toggle arrives with settings in phase 4
    void printLine(const std::string& text) const;
    void printHeader(const std::string& title) const;

    // Re-prompts on invalid/non-numeric input; never throws, never leaves cin in a bad state.
    int readMenuChoice(int minValue, int maxValue);
    std::string readLine(const std::string& prompt);
};
```

- Windows: `main.cpp` calls `SetConsoleOutputCP(CP_UTF8)` and
  `SetConsoleCP(CP_UTF8)` inside `#ifdef _WIN32`, before any output.
- Linux/macOS: no special handling required (terminals are UTF-8 already).
- `readMenuChoice` reads a full line via `std::getline`, trims whitespace,
  parses with `std::from_chars` (no locale surprises, no exceptions), and
  re-prompts with a Turkish error message on parse failure or out-of-range
  input. It never uses `cin >> int` directly (avoids leaving a fail state or
  a stray `\n` in the buffer — the exact class of bug the product spec's
  "safe input" requirement calls out).

## `Application`

```cpp
class Application {
public:
    Application();
    void run();  // shows welcome once, then loops the main menu until exit

private:
    void showMainMenu();
    void handleChoice(int choice);
    void showTopicBrowser();          // option 1 — real in this phase
    void showNotYetAvailable(const std::string& featureName); // options 2-9

    ConsoleUI ui_;
    LessonManager lessons_;
    UserProgress progress_;
};
```

Main menu renders exactly the 11 lines from the product spec (options 1–10
plus 0 = exit). `handleChoice`:

- **1 (Konuları Öğler)**: prints all 10 sections with their topics, each
  prefixed with a status marker (`[ ]`/`[-]`/`[+]`/`[*]`) from
  `UserProgress`. Since nothing sets status yet, every marker shows `[ ]` —
  this is honest, not faked.
- **2–10** (Hızlı Test through İlerlemeyi Sıfırla): each prints its own name
  in an honest not-yet-available message, e.g. `"Hızlı Test" bu sürümde
  henüz eklenmedi. Sonraki aşamada gelecek.`, then returns to the menu. No
  fake quiz flow, no dummy questions, no fake reset.
- **0**: prints a short goodbye line and exits `run()`'s loop.

At startup, `Application`'s constructor ensures `data/` exists via
`std::filesystem::create_directories`, swallowing/reporting failure without
crashing (a real filesystem failure here — e.g. read-only parent — is
reported once via `ConsoleUI` and the app continues without persistence,
since nothing persists yet anyway).

## Testing / verification for this phase

No unit test framework is introduced yet (phase 6 owns that). Verification
is manual + build-based:

1. `cmake -S . -B build && cmake --build build` succeeds with no warnings
   under the configured warning flags.
2. Run the binary:
   - Enter an out-of-range number (e.g. `99`) at the main menu → re-prompts,
     doesn't crash.
   - Enter non-numeric input (e.g. `abc`) → re-prompts, doesn't crash.
   - Choose `1` → see all 10 sections and 100 topics listed with `[ ]`
     markers, then return to menu.
   - Choose `2` (or any of 2–10) → see the honest "not yet available"
     message, then return to menu.
   - Choose `0` → clean exit, no crash, no leaked resources.
3. Turkish characters (ş, ğ, ı, ö, ç, ü, İ) in section/topic titles render
   correctly in the Windows terminal after the UTF-8 setup.

## Open scoping notes

- The exact 100 topic titles and their section groupings are taken verbatim
  from the product spec's numbered list (1–100, Bölüm 1–10) and will be
  transcribed into `LessonManager`'s constructor exactly as given — no
  renaming or reordering.
- `settings.txt`-driven options (color toggle, screen-clear toggle, etc.)
  don't exist yet; `ConsoleUI::clearScreen()` always clears in this phase.
  The toggle is added when `ProgressManager`/settings persistence lands in
  phase 4.

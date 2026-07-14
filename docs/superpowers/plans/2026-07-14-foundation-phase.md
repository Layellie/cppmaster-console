# CppMaster Console — Foundation Phase Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Produce a compiling, runnable CppMaster Console skeleton: a safe main-menu loop, the full 100-topic catalog as browsable data, and the core data model later phases build on — with no faked features.

**Architecture:** A small set of single-responsibility classes (`ConsoleUI` for I/O, `LessonManager`/`Lesson` for the topic catalog, `UserProgress` for in-memory topic status, `Application` for the menu loop) wired together in `main.cpp`. Each class is built and manually verified in isolation before `Application` composes them in the final task.

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only. No external dependencies, no test framework (this phase; verification is build + manual run-through per the design doc).

**Spec:** `docs/superpowers/specs/2026-07-14-foundation-phase-design.md`

## Global Constraints

- C++20 required, `CMAKE_CXX_STANDARD_REQUIRED ON`, `CMAKE_CXX_EXTENSIONS OFF`, `cmake_minimum_required(VERSION 3.20)`.
- No external libraries — standard library only.
- Compiler warnings: MSVC gets `/W4 /permissive-`; GCC/Clang get `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`. Every task's build must produce zero warnings under these flags.
- CMake project and executable target name: `CppMasterConsole`.
- No `using namespace std;` anywhere.
- One class per `.h`/`.cpp` pair, except pure data-only structs with no member functions (`Lesson`, and the enums in `Enums.h`), which are header-only — this is a deliberate exception, not an oversight, because an empty `.cpp` would itself be a placeholder.
- No fake/placeholder code. A feature not yet built must say so honestly at runtime (see Task 5) rather than simulate behavior.
- User-facing strings are Turkish, written with correct diacritics (ş, ğ, ı, İ, ö, ç, ü), and rendered correctly via the UTF-8 console setup — this matters for every user-facing string added from Task 5 onward.
- `data/` directory is created if missing via `std::filesystem`; no file formats inside it are defined yet (that's a later phase).

---

### Task 1: CMake scaffolding and a minimal, buildable entry point

**Files:**
- Modify: `CMakeLists.txt`
- Delete: `main.cpp` (root — being replaced by `src/main.cpp`)
- Create: `src/main.cpp`

**Interfaces:**
- Consumes: nothing.
- Produces: a working CMake build producing the `CppMasterConsole` executable target. Later tasks add sources to the same `add_executable` call.

- [ ] **Step 1: Rewrite `CMakeLists.txt`**

```cmake
cmake_minimum_required(VERSION 3.20)

project(CppMasterConsole
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(CppMasterConsole
    src/main.cpp
)

target_include_directories(CppMasterConsole PRIVATE src)

if (MSVC)
    target_compile_options(CppMasterConsole PRIVATE /W4 /permissive-)
else()
    target_compile_options(
        CppMasterConsole
        PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
    )
endif()
```

- [ ] **Step 2: Delete the root `main.cpp` and create `src/main.cpp`**

Delete `main.cpp` at the project root. Create `src/main.cpp`:

```cpp
#include <iostream>

int main() {
    std::cout << "CppMaster Console - Foundation derleme testi basarili.\n";
    return 0;
}
```

- [ ] **Step 3: Configure and build**

Run:
```bash
cmake -S . -B build
cmake --build build
```
Expected: configure succeeds, build succeeds with **zero warnings**.

- [ ] **Step 4: Run and verify**

Run the produced executable (path depends on your generator — e.g.
`./build/CppMasterConsole` for Ninja/Makefiles, `./build/Debug/CppMasterConsole.exe`
for a Visual Studio multi-config generator).

Expected output:
```
CppMaster Console - Foundation derleme testi basarili.
```

- [ ] **Step 5: Commit**

```bash
git add CMakeLists.txt src/main.cpp
git rm main.cpp
git commit -m "Scaffold CMake project as CppMasterConsole (C++20)"
```

---

### Task 2: `Enums.h` and `UserProgress`

**Files:**
- Modify: `CMakeLists.txt` (add `src/UserProgress.cpp`, `src/UserProgress.h`, `src/Enums.h` to the executable's sources)
- Create: `src/Enums.h`
- Create: `src/UserProgress.h`
- Create: `src/UserProgress.cpp`
- Modify (temporarily, superseded in Task 5): `src/main.cpp`

**Interfaces:**
- Consumes: nothing from Task 1's code.
- Produces:
  - `enum class QuestionType { MultipleChoice, TrueFalse, FillBlank, CompleteLine, PredictOutput, FindError, FixCode, OrderCode, WriteCode, Scenario, Matching };`
  - `enum class Difficulty { VeryEasy = 1, Easy = 2, Medium = 3, Hard = 4, VeryHard = 5 };`
  - `enum class TopicStatus { NotStarted, Learning, Completed, Mastered };`
  - `class UserProgress { public: explicit UserProgress(int topicCount); TopicStatus statusOf(int topicId) const; void setStatus(int topicId, TopicStatus status); };`

- [ ] **Step 1: Create `src/Enums.h`**

```cpp
#pragma once

enum class QuestionType {
    MultipleChoice,
    TrueFalse,
    FillBlank,
    CompleteLine,
    PredictOutput,
    FindError,
    FixCode,
    OrderCode,
    WriteCode,
    Scenario,
    Matching
};

enum class Difficulty {
    VeryEasy = 1,
    Easy = 2,
    Medium = 3,
    Hard = 4,
    VeryHard = 5
};

static_assert(static_cast<int>(Difficulty::VeryEasy) == 1);
static_assert(static_cast<int>(Difficulty::Easy) == 2);
static_assert(static_cast<int>(Difficulty::Medium) == 3);
static_assert(static_cast<int>(Difficulty::Hard) == 4);
static_assert(static_cast<int>(Difficulty::VeryHard) == 5);

enum class TopicStatus {
    NotStarted,
    Learning,
    Completed,
    Mastered
};
```

- [ ] **Step 2: Create `src/UserProgress.h`**

```cpp
#pragma once

#include <unordered_map>

#include "Enums.h"

class UserProgress {
public:
    explicit UserProgress(int topicCount);

    [[nodiscard]] TopicStatus statusOf(int topicId) const;
    void setStatus(int topicId, TopicStatus status);

private:
    std::unordered_map<int, TopicStatus> statusByTopicId_;
};
```

- [ ] **Step 3: Create `src/UserProgress.cpp`**

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
```

- [ ] **Step 4: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>

#include "UserProgress.h"

int main() {
    UserProgress progress(5);

    std::cout << "Baslangic durumu (topic 1): "
              << (progress.statusOf(1) == TopicStatus::NotStarted ? "NotStarted (OK)" : "HATA")
              << '\n';

    progress.setStatus(1, TopicStatus::Completed);
    std::cout << "Guncelleme sonrasi (topic 1): "
              << (progress.statusOf(1) == TopicStatus::Completed ? "Completed (OK)" : "HATA")
              << '\n';

    std::cout << "Bilinmeyen topic (999): "
              << (progress.statusOf(999) == TopicStatus::NotStarted ? "NotStarted (OK)" : "HATA")
              << '\n';

    return 0;
}
```

- [ ] **Step 5: Update `CMakeLists.txt`'s `add_executable` call**

```cmake
add_executable(CppMasterConsole
    src/main.cpp
    src/Enums.h
    src/UserProgress.h
    src/UserProgress.cpp
)
```

- [ ] **Step 6: Build and run**

Run:
```bash
cmake --build build
./build/CppMasterConsole
```
Expected output (all three lines end in `(OK)`):
```
Baslangic durumu (topic 1): NotStarted (OK)
Guncelleme sonrasi (topic 1): Completed (OK)
Bilinmeyen topic (999): NotStarted (OK)
```
Zero compiler warnings.

- [ ] **Step 7: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/Enums.h src/UserProgress.h src/UserProgress.cpp
git commit -m "Add Enums.h and UserProgress with in-memory topic status tracking"
```

---

### Task 3: `Lesson` struct and `LessonManager` with the full 100-topic catalog

**Files:**
- Modify: `CMakeLists.txt` (add `src/Lesson.h`, `src/LessonManager.h`, `src/LessonManager.cpp`)
- Create: `src/Lesson.h`
- Create: `src/LessonManager.h`
- Create: `src/LessonManager.cpp`
- Modify (temporarily, superseded in Task 5): `src/main.cpp`

**Interfaces:**
- Consumes: nothing from Task 2's code.
- Produces:
  - `struct Lesson { int id; int sectionId; std::string title; std::string explanation; std::string syntax; std::string exampleCode; std::vector<std::string> lineExplanations; std::vector<std::string> commonMistakes; };`
  - `class LessonManager { public: LessonManager(); const std::vector<Lesson>& allLessons() const; std::vector<Lesson> lessonsInSection(int sectionId) const; std::optional<Lesson> findById(int topicId) const; std::string sectionTitle(int sectionId) const; int sectionCount() const; };`

- [ ] **Step 1: Create `src/Lesson.h`**

```cpp
#pragma once

#include <string>
#include <vector>

struct Lesson {
    int id = 0;
    int sectionId = 0;
    std::string title;

    // Populated starting in the "static lesson + quiz core" phase.
    std::string explanation;
    std::string syntax;
    std::string exampleCode;
    std::vector<std::string> lineExplanations;
    std::vector<std::string> commonMistakes;
};
```

- [ ] **Step 2: Create `src/LessonManager.h`**

```cpp
#pragma once

#include <optional>
#include <string>
#include <vector>

#include "Lesson.h"

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

- [ ] **Step 3: Create `src/LessonManager.cpp`** with the full 100-topic catalog, transcribed verbatim from the product spec

```cpp
#include "LessonManager.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <utility>

namespace {

struct TopicSeed {
    int id;
    int sectionId;
    const char* title;
};

constexpr TopicSeed kTopicSeeds[] = {
    // Bölüm 1: Giriş, çıkış ve değişkenler
    {1, 1, "cout"},
    {2, 1, "\\n"},
    {3, 1, "endl"},
    {4, 1, "cin"},
    {5, 1, "getline()"},
    {6, 1, "int"},
    {7, 1, "double"},
    {8, 1, "char"},
    {9, 1, "bool"},
    {10, 1, "const"},

    // Bölüm 2: Operatörler ve koşullar
    {11, 2, "Matematiksel operatörler"},
    {12, 2, "% mod operatörü"},
    {13, 2, "Kısaltılmış atama operatörleri"},
    {14, 2, "++ ve --"},
    {15, 2, "Karşılaştırma operatörleri"},
    {16, 2, "Mantıksal operatörler"},
    {17, 2, "if"},
    {18, 2, "if-else"},
    {19, 2, "else if"},
    {20, 2, "Üçlü koşul operatörü"},

    // Bölüm 3: Seçim ve döngüler
    {21, 3, "switch-case"},
    {22, 3, "for"},
    {23, 3, "while"},
    {24, 3, "do-while"},
    {25, 3, "break"},
    {26, 3, "continue"},
    {27, 3, "İç içe döngüler"},
    {28, 3, "Range-based for"},
    {29, 3, "1'den N'e kadar toplama"},
    {30, 3, "Faktöriyel hesaplama"},

    // Bölüm 4: Diziler, vector ve string
    {31, 4, "Normal diziler"},
    {32, 4, "Dizi elemanlarını değiştirme"},
    {33, 4, "std::array"},
    {34, 4, "vector"},
    {35, 4, "push_back() ve pop_back()"},
    {36, 4, "size(), front(), back() ve at()"},
    {37, 4, "string"},
    {38, 4, "String birleştirme"},
    {39, 4, "length() ve empty()"},
    {40, 4, "substr() ve find()"},

    // Bölüm 5: Fonksiyonlar
    {41, 5, "Parametresiz fonksiyon"},
    {42, 5, "Parametre alan fonksiyon"},
    {43, 5, "Değer döndüren fonksiyon"},
    {44, 5, "Fonksiyon prototipi"},
    {45, 5, "Varsayılan parametre"},
    {46, 5, "Fonksiyon aşırı yükleme"},
    {47, 5, "Değer ile parametre gönderme"},
    {48, 5, "Referans ile parametre gönderme"},
    {49, 5, "const referans"},
    {50, 5, "Recursion"},

    // Bölüm 6: Lambda, pointer ve bellek
    {51, 6, "Lambda fonksiyonları"},
    {52, 6, "Pointer tanımlama"},
    {53, 6, "& adres operatörü"},
    {54, 6, "* dereference operatörü"},
    {55, 6, "nullptr"},
    {56, 6, "Pointer ile dizi dolaşma"},
    {57, 6, "new"},
    {58, 6, "delete"},
    {59, 6, "Dinamik dizi"},
    {60, 6, "Referans değişkeni"},

    // Bölüm 7: Struct ve nesne yönelimli programlama
    {61, 7, "struct"},
    {62, 7, "enum"},
    {63, 7, "enum class"},
    {64, 7, "Sınıf ve nesne"},
    {65, 7, "Constructor"},
    {66, 7, "Destructor"},
    {67, 7, "private ve public"},
    {68, 7, "Getter ve setter"},
    {69, 7, "Kalıtım"},
    {70, 7, "protected"},

    // Bölüm 8: İleri nesne yönelimli özellikler
    {71, 8, "virtual"},
    {72, 8, "override"},
    {73, 8, "Soyut sınıf"},
    {74, 8, "Polimorfizm"},
    {75, 8, "this pointer'ı"},
    {76, 8, "static sınıf üyesi"},
    {77, 8, "Operatör aşırı yükleme"},
    {78, 8, "Template fonksiyon"},
    {79, 8, "namespace"},
    {80, 8, "auto"},

    // Bölüm 9: STL veri yapıları
    {81, 9, "pair"},
    {82, 9, "tuple"},
    {83, 9, "set"},
    {84, 9, "map"},
    {85, 9, "unordered_map"},
    {86, 9, "stack"},
    {87, 9, "queue"},
    {88, 9, "deque"},
    {89, 9, "priority_queue"},
    {90, 9, "Iterator"},

    // Bölüm 10: Algoritmalar, dosyalar ve hata yönetimi
    {91, 10, "sort()"},
    {92, 10, "reverse()"},
    {93, 10, "find()"},
    {94, 10, "count()"},
    {95, 10, "min(), max() ve max_element()"},
    {96, 10, "accumulate()"},
    {97, 10, "Dosyaya yazma"},
    {98, 10, "Dosyadan okuma"},
    {99, 10, "try-catch"},
    {100, 10, "unique_ptr"},
};

}  // namespace

LessonManager::LessonManager() {
    sectionTitles_ = {
        "Giriş, çıkış ve değişkenler",
        "Operatörler ve koşullar",
        "Seçim ve döngüler",
        "Diziler, vector ve string",
        "Fonksiyonlar",
        "Lambda, pointer ve bellek",
        "Struct ve nesne yönelimli programlama",
        "İleri nesne yönelimli özellikler",
        "STL veri yapıları",
        "Algoritmalar, dosyalar ve hata yönetimi",
    };

    lessons_.reserve(std::size(kTopicSeeds));
    for (const TopicSeed& seed : kTopicSeeds) {
        Lesson lesson;
        lesson.id = seed.id;
        lesson.sectionId = seed.sectionId;
        lesson.title = seed.title;
        lessons_.push_back(std::move(lesson));
    }
}

const std::vector<Lesson>& LessonManager::allLessons() const {
    return lessons_;
}

std::vector<Lesson> LessonManager::lessonsInSection(int sectionId) const {
    std::vector<Lesson> result;
    std::ranges::copy_if(
        lessons_,
        std::back_inserter(result),
        [sectionId](const Lesson& lesson) { return lesson.sectionId == sectionId; });
    return result;
}

std::optional<Lesson> LessonManager::findById(int topicId) const {
    const auto it = std::ranges::find_if(
        lessons_,
        [topicId](const Lesson& lesson) { return lesson.id == topicId; });
    if (it == lessons_.end()) {
        return std::nullopt;
    }
    return *it;
}

std::string LessonManager::sectionTitle(int sectionId) const {
    if (sectionId < 1 || static_cast<std::size_t>(sectionId) > sectionTitles_.size()) {
        return "";
    }
    return sectionTitles_[static_cast<std::size_t>(sectionId - 1)];
}

int LessonManager::sectionCount() const {
    return static_cast<int>(sectionTitles_.size());
}
```

- [ ] **Step 4: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>

#include "LessonManager.h"

int main() {
    LessonManager lessons;

    std::cout << "Toplam konu sayisi: " << lessons.allLessons().size()
              << " (beklenen: 100)\n";
    std::cout << "Bolum sayisi: " << lessons.sectionCount()
              << " (beklenen: 10)\n";

    const auto first = lessons.findById(1);
    std::cout << "Konu 1 basligi: "
              << (first.has_value() ? first->title : "BULUNAMADI")
              << " (beklenen: cout)\n";

    const auto last = lessons.findById(100);
    std::cout << "Konu 100 basligi: "
              << (last.has_value() ? last->title : "BULUNAMADI")
              << " (beklenen: unique_ptr)\n";

    const auto missing = lessons.findById(999);
    std::cout << "Konu 999: "
              << (missing.has_value() ? "BULUNDU (HATA)" : "bulunamadi (OK)")
              << '\n';

    std::cout << "Bolum 1'deki konu sayisi: "
              << lessons.lessonsInSection(1).size() << " (beklenen: 10)\n";

    return 0;
}
```

- [ ] **Step 5: Update `CMakeLists.txt`'s `add_executable` call**

```cmake
add_executable(CppMasterConsole
    src/main.cpp
    src/Enums.h
    src/UserProgress.h
    src/UserProgress.cpp
    src/Lesson.h
    src/LessonManager.h
    src/LessonManager.cpp
)
```

- [ ] **Step 6: Build and run**

Run:
```bash
cmake --build build
./build/CppMasterConsole
```
Expected output:
```
Toplam konu sayisi: 100 (beklenen: 100)
Bolum sayisi: 10 (beklenen: 10)
Konu 1 basligi: cout (beklenen: cout)
Konu 100 basligi: unique_ptr (beklenen: unique_ptr)
Konu 999: bulunamadi (OK)
Bolum 1'deki konu sayisi: 10 (beklenen: 10)
```
Zero compiler warnings.

- [ ] **Step 7: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/Lesson.h src/LessonManager.h src/LessonManager.cpp
git commit -m "Add Lesson struct and LessonManager with full 100-topic catalog"
```

---

### Task 4: `ConsoleUI`

**Files:**
- Modify: `CMakeLists.txt` (add `src/ConsoleUI.h`, `src/ConsoleUI.cpp`)
- Create: `src/ConsoleUI.h`
- Create: `src/ConsoleUI.cpp`
- Modify (temporarily, superseded in Task 5): `src/main.cpp`

**Interfaces:**
- Consumes: nothing from Tasks 2/3's code.
- Produces:
  - `class ConsoleUI { public: ConsoleUI(); void clearScreen() const; void printLine(const std::string&) const; void printHeader(const std::string&) const; int readMenuChoice(int minValue, int maxValue); std::string readLine(const std::string& prompt); };`

- [ ] **Step 1: Create `src/ConsoleUI.h`**

```cpp
#pragma once

#include <string>

class ConsoleUI {
public:
    ConsoleUI();

    void clearScreen() const;
    void printLine(const std::string& text) const;
    void printHeader(const std::string& title) const;

    int readMenuChoice(int minValue, int maxValue);
    std::string readLine(const std::string& prompt);
};
```

- [ ] **Step 2: Create `src/ConsoleUI.cpp`**

```cpp
#include "ConsoleUI.h"

#include <charconv>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <system_error>

#ifdef _WIN32
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
```

- [ ] **Step 3: Temporarily wire a manual verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>

#include "ConsoleUI.h"

int main() {
    ConsoleUI ui;

    ui.printHeader("CONSOLEUI TEST");
    ui.printLine("0 ile 5 arasinda bir sayi girin (once gecersiz bir deger deneyin):");
    const int choice = ui.readMenuChoice(0, 5);
    ui.printLine("Sectiginiz deger: " + std::to_string(choice));

    const std::string name = ui.readLine("Adiniz: ");
    ui.printLine("Merhaba, " + name + "!");

    return 0;
}
```

- [ ] **Step 4: Update `CMakeLists.txt`'s `add_executable` call**

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
)
```

- [ ] **Step 5: Build and manually verify**

Run:
```bash
cmake --build build
./build/CppMasterConsole
```
Manually:
1. Type `abc` and press Enter → expect the Turkish "Geçersiz seçim..." message, re-prompted, no crash.
2. Type `99` and press Enter → same re-prompt, no crash.
3. Type `3` and press Enter → expect `Sectiginiz deger: 3`.
4. Type a name (e.g. `Samet`) and press Enter → expect `Merhaba, Samet!`.
5. Confirm the Turkish characters in "Geçersiz seçim... Lütfen ... arasında bir sayı girin" render correctly (not as `?` or mojibake).

Zero compiler warnings on build.

- [ ] **Step 6: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/ConsoleUI.h src/ConsoleUI.cpp
git commit -m "Add ConsoleUI with UTF-8 setup and safe menu-choice input parsing"
```

---

### Task 5: `Application` — wire everything into the real main menu

**Files:**
- Modify: `CMakeLists.txt` (add `src/Application.h`, `src/Application.cpp`)
- Create: `src/Application.h`
- Create: `src/Application.cpp`
- Modify: `src/main.cpp` (final version — replaces all prior temporary verification code)

**Interfaces:**
- Consumes:
  - `ConsoleUI` (Task 4): `printHeader`, `printLine`, `readMenuChoice(int,int)`.
  - `LessonManager`/`Lesson` (Task 3): `allLessons()`, `lessonsInSection(int)`, `sectionTitle(int)`, `sectionCount()`.
  - `UserProgress`/`TopicStatus` (Task 2): `UserProgress(int)`, `statusOf(int)`.
- Produces: `class Application { public: Application(); void run(); };` — the final public surface of this phase.

- [ ] **Step 1: Create `src/Application.h`**

```cpp
#pragma once

#include <string>

#include "ConsoleUI.h"
#include "LessonManager.h"
#include "UserProgress.h"

class Application {
public:
    Application();

    void run();

private:
    void showMainMenu();
    void handleChoice(int choice);
    void showTopicBrowser();
    void showNotYetAvailable(const std::string& featureName);
    void ensureDataDirectoryExists();

    ConsoleUI ui_;
    LessonManager lessons_;
    UserProgress progress_;
    bool running_ = true;
};
```

- [ ] **Step 2: Create `src/Application.cpp`**

```cpp
#include "Application.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>

namespace {

constexpr int kMinChoice = 0;
constexpr int kMaxChoice = 10;

char statusMarker(TopicStatus status) {
    switch (status) {
        case TopicStatus::NotStarted:
            return ' ';
        case TopicStatus::Learning:
            return '-';
        case TopicStatus::Completed:
            return '+';
        case TopicStatus::Mastered:
            return '*';
    }
    return ' ';
}

}  // namespace

Application::Application()
    : progress_(static_cast<int>(lessons_.allLessons().size())) {
    ensureDataDirectoryExists();
}

void Application::ensureDataDirectoryExists() {
    std::error_code errorCode;
    std::filesystem::create_directories("data", errorCode);
    if (errorCode) {
        ui_.printLine(
            "Uyarı: data/ klasörü oluşturulamadı (" + errorCode.message() +
            "). İlerleme kaydetme özelliği bu sürümde zaten aktif değil.");
    }
}

void Application::run() {
    ui_.printHeader("CPPMASTER CONSOLE");
    ui_.printLine("CppMaster Console'a hoş geldin! (Foundation sürümü)");

    while (running_) {
        showMainMenu();
        const int choice = ui_.readMenuChoice(kMinChoice, kMaxChoice);
        handleChoice(choice);
    }
}

void Application::showMainMenu() {
    ui_.printLine("");
    ui_.printLine("========================================");
    ui_.printLine("           CPPMASTER CONSOLE");
    ui_.printLine("========================================");
    ui_.printLine("");
    ui_.printLine("1. Konuları Öğren");
    ui_.printLine("2. Hızlı Test");
    ui_.printLine("3. Günlük Tekrar");
    ui_.printLine("4. Hatalarımı Çöz");
    ui_.printLine("5. Kod Yazma Alıştırmaları");
    ui_.printLine("6. Seviye Sınavı");
    ui_.printLine("7. İstatistiklerim");
    ui_.printLine("8. Başarımlar");
    ui_.printLine("9. Ayarlar");
    ui_.printLine("10. İlerlemeyi Sıfırla");
    ui_.printLine("0. Çıkış");
    ui_.printLine("");
    ui_.printLine("Seçiminiz:");
}

void Application::handleChoice(int choice) {
    switch (choice) {
        case 1:
            showTopicBrowser();
            break;
        case 2:
            showNotYetAvailable("Hızlı Test");
            break;
        case 3:
            showNotYetAvailable("Günlük Tekrar");
            break;
        case 4:
            showNotYetAvailable("Hatalarımı Çöz");
            break;
        case 5:
            showNotYetAvailable("Kod Yazma Alıştırmaları");
            break;
        case 6:
            showNotYetAvailable("Seviye Sınavı");
            break;
        case 7:
            showNotYetAvailable("İstatistiklerim");
            break;
        case 8:
            showNotYetAvailable("Başarımlar");
            break;
        case 9:
            showNotYetAvailable("Ayarlar");
            break;
        case 10:
            showNotYetAvailable("İlerlemeyi Sıfırla");
            break;
        case 0:
            ui_.printLine("Görüşürüz!");
            running_ = false;
            break;
        default:
            break;
    }
}

void Application::showTopicBrowser() {
    ui_.printLine("");
    for (int sectionId = 1; sectionId <= lessons_.sectionCount(); ++sectionId) {
        ui_.printLine(
            "Bölüm " + std::to_string(sectionId) + ": " + lessons_.sectionTitle(sectionId));

        for (const Lesson& lesson : lessons_.lessonsInSection(sectionId)) {
            const char marker = statusMarker(progress_.statusOf(lesson.id));
            ui_.printLine(
                "  [" + std::string(1, marker) + "] " + std::to_string(lesson.id) + ". " +
                lesson.title);
        }
        ui_.printLine("");
    }
}

void Application::showNotYetAvailable(const std::string& featureName) {
    ui_.printLine("");
    ui_.printLine(
        "\"" + featureName + "\" bu sürümde henüz eklenmedi. Sonraki aşamada gelecek.");
}
```

- [ ] **Step 3: Replace `src/main.cpp` with its final Foundation-phase version**

```cpp
#include "Application.h"

int main() {
    Application app;
    app.run();
    return 0;
}
```

- [ ] **Step 4: Update `CMakeLists.txt`'s `add_executable` call to its final Foundation-phase form**

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
    src/Application.h
    src/Application.cpp
)
```

- [ ] **Step 5: Build**

Run:
```bash
cmake --build build
```
Expected: build succeeds with zero warnings.

- [ ] **Step 6: Full manual verification (this is the phase's acceptance test)**

Run `./build/CppMasterConsole` and walk through:

1. At the main menu, type `99` → re-prompted with the Turkish invalid-choice message, app does not crash.
2. Type `abc` → same re-prompt, no crash.
3. Type `1` → see all 10 section headers ("Bölüm 1: Giriş, çıkış ve değişkenler" ... "Bölüm 10: Algoritmalar, dosyalar ve hata yönetimi") each followed by their topics, every topic prefixed with `[ ]` (since nothing has set any status yet), then the main menu reappears.
4. Type `2` → see `"Hızlı Test" bu sürümde henüz eklenmedi. Sonraki aşamada gelecek.`, then the main menu reappears. Repeat for `3` through `10`, confirming each prints its own feature name.
5. Type `0` → see `Görüşürüz!` and the process exits cleanly (shell prompt returns, no crash/hang).
6. Confirm all Turkish characters (ş, ğ, ı, ö, ç, ü, İ) in the menu and topic titles render correctly in the terminal.
7. Confirm a `data/` directory now exists at the project root (e.g. `ls data` / `Test-Path data`). Run the app a second time and confirm no error/crash from the directory already existing.

- [ ] **Step 7: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/Application.h src/Application.cpp
git commit -m "Add Application main-menu loop, completing the Foundation phase"
```

---

## Post-plan note

This completes Aşama 1 (Foundation) of the decomposition in the design doc.
The next sub-project — static lesson + quiz core — gets its own
brainstorming → spec → plan cycle before implementation starts, since it
introduces `Question`, `QuestionManager`, and `QuizEngine`, none of which
exist yet.

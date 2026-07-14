# CppMaster Console — Static Lesson + Quiz Core (Phase 2) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Turn "Konuları Öğren" into a real learning loop for the first 10 topics: real lesson content, a real quiz (multiple choice, true/false, fill-blank), and XP/topic-status updates based on the result.

**Architecture:** Two new small classes (`QuestionManager` owns a hardcoded 60-question bank; `QuizEngine` is a stateless answer evaluator), `LessonManager` gains content for topics 1-10, `UserProgress` gains XP tracking, and `Application` gains the topic-open/quiz flow that composes all of them.

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only. Still no test framework (verification is build + manual/piped run-through, same as Foundation).

**Spec:** `docs/superpowers/specs/2026-07-14-static-lesson-quiz-core-design.md`

## Global Constraints

- C++20 required, same CMake settings as Foundation (`CMAKE_CXX_STANDARD_REQUIRED ON`, `CMAKE_CXX_EXTENSIONS OFF`).
- No external libraries — standard library only.
- Compiler warnings: MSVC `/W4 /permissive-`; GCC/Clang `-Wall -Wextra -Wpedantic -Wconversion -Wshadow`. Zero warnings required.
- No `using namespace std;` anywhere.
- `Question` is header-only (a pure data struct, no member functions) — same convention as `Lesson`/`Enums.h`.
- No fake/placeholder code.
- User-facing strings (prompts, options, explanations, lesson text) are Turkish with correct diacritics. The strings actually *compared* for correctness (multiple-choice letters `a`-`d`, true/false digits `1`/`2`, fill-blank keywords) are ASCII by design — see the spec's "Answer matching stays ASCII-only" section — so `QuizEngine` only ever needs ASCII case-folding, never Turkish-aware casing.
- Topics 11-100 are untouched by this phase; `Lesson::explanation.empty()` is how `Application` tells "no content yet" apart from "has content."

---

### Task 1: `Question` struct and `QuestionManager` with the 60-question bank for topics 1-10

**Files:**
- Create: `src/Question.h`
- Create: `src/QuestionManager.h`
- Create: `src/QuestionManager.cpp`
- Modify: `CMakeLists.txt` (add the three files above to `add_executable`)
- Modify (temporarily, superseded in Task 5): `src/main.cpp`

**Interfaces:**
- Consumes: `QuestionType`, `Difficulty` (from `Enums.h`, already exist).
- Produces:
  - `struct Question { int id; int topicId; QuestionType type; Difficulty difficulty; std::string prompt; std::vector<std::string> options; std::vector<std::string> acceptedAnswers; std::string explanation; int baseXp; };`
  - `class QuestionManager { public: QuestionManager(); std::vector<Question> questionsForTopic(int topicId) const; };`

- [ ] **Step 1: Create `src/Question.h`**

```cpp
#pragma once

#include <string>
#include <vector>

#include "Enums.h"

struct Question {
    int id = 0;
    int topicId = 0;
    QuestionType type = QuestionType::MultipleChoice;
    Difficulty difficulty = Difficulty::Easy;
    std::string prompt;
    std::vector<std::string> options;          // MultipleChoice only; empty for TrueFalse/FillBlank
    std::vector<std::string> acceptedAnswers;   // normalized (ASCII, lowercase-safe) accepted answer(s)
    std::string explanation;
    int baseXp = 0;
};
```

- [ ] **Step 2: Create `src/QuestionManager.h`**

```cpp
#pragma once

#include <vector>

#include "Question.h"

class QuestionManager {
public:
    QuestionManager();

    [[nodiscard]] std::vector<Question> questionsForTopic(int topicId) const;

private:
    std::vector<Question> questions_;
};
```

- [ ] **Step 3: Create `src/QuestionManager.cpp`** with the full 60-question seed (6 per topic: 2 MultipleChoice, 2 TrueFalse, 2 FillBlank, for topics 1-10), transcribed verbatim from this brief

```cpp
#include "QuestionManager.h"

QuestionManager::QuestionManager() {
    questions_.reserve(60);

    // Topic 1: cout
    questions_.push_back(Question{
        .id = 1, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdakilerden hangisi ekrana yazı yazdırmak için kullanılır?",
        .options = {"cin", "cout", "endl", "return"},
        .acceptedAnswers = {"b"},
        .explanation = "cout, ekrana veri yazdırmak için kullanılan çıktı akışıdır; cin ise klavyeden veri okumak için kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 2, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"Merhaba\"; satırı hangi kütüphane olmadan derlenemez?",
        .options = {"<string>", "<vector>", "<iostream>", "<cmath>"},
        .acceptedAnswers = {"c"},
        .explanation = "cout, <iostream> kütüphanesinde tanımlıdır; bu kütüphane eklenmeden kullanılamaz.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 3, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "cout, kullanıcıdan klavyeden veri okumak için kullanılır.",
        .acceptedAnswers = {"2"},
        .explanation = "cout çıktı (ekrana yazdırma) içindir; veri okumak için cin kullanılır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 4, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cout kullanmak için <iostream> kütüphanesinin eklenmesi gerekir.",
        .acceptedAnswers = {"1"},
        .explanation = "cout, <iostream> kütüphanesinde tanımlıdır; kullanmak için bu kütüphane eklenmelidir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 5, .topicId = 1,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::_____ << \"Merhaba\";",
        .acceptedAnswers = {"cout"},
        .explanation = "Ekrana yazdırmak için std::cout kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 6, .topicId = 1,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "cout kullanmak için eklenmesi gereken kütüphane: #include <_____>",
        .acceptedAnswers = {"iostream"},
        .explanation = "cout, <iostream> kütüphanesinde tanımlıdır.",
        .baseXp = 20,
    });

    // Topic 2: \n
    questions_.push_back(Question{
        .id = 7, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdakilerden hangisi bir sonraki satıra geçmeyi sağlayan kaçış dizisidir?",
        .options = {"\\t", "\\n", "\\\\", "\\0"},
        .acceptedAnswers = {"b"},
        .explanation = "\\n, metin içinde yeni satıra geçişi sağlayan kaçış dizisidir; \\t ise yatay sekme (tab) boşluğu ekler.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 8, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"A\\nB\"; ifadesinin ekran çıktısı nasıl görünür?",
        .options = {"A ve B aynı satırda yan yana", "Önce A, alt satırda B", "Sadece B yazılır", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "\\n, A'dan sonra imleci yeni satıra taşır, bu yüzden B bir alt satırda görünür.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 9, .topicId = 2,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "\\n ifadesi çift tırnak içinde kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "\\n bir dize (string) içinde, çift tırnaklar arasında yazılır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 10, .topicId = 2,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "\\n kullanmak için ekstra bir kütüphane eklemek gerekir.",
        .acceptedAnswers = {"2"},
        .explanation = "\\n, dil düzeyinde bir kaçış dizisidir; başlı başına ekstra bir kütüphane istemez.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 11, .topicId = 2,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Yeni satıra geçmek için kullanılan kaçış dizisinin harfi: \\_____ (ters slash zaten verilmiştir, sadece harfi yazınız)",
        .acceptedAnswers = {"n"},
        .explanation = "\\n, ters slash ve n harfinden oluşan, yeni satıra geçişi sağlayan kaçış dizisidir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 12, .topicId = 2,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"A_____B\"; kodunun çalışması sonucunda A ve B farklı satırlarda görünsün istiyorsunuz. Boşluğa (ters slash dahil, tam olarak) ne yazmalısınız?",
        .acceptedAnswers = {"\\n"},
        .explanation = "\\n, metin içinde yeni satıra geçişi sağlayan kaçış dizisidir.",
        .baseXp = 20,
    });

    // Topic 3: endl
    questions_.push_back(Question{
        .id = 13, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::endl ne işe yarar?",
        .options = {"Sadece metni büyük harfe çevirir", "Yeni satıra geçer ve çıktı tamponunu boşaltır", "Programı sonlandırır", "Bir sayıyı yuvarlar"},
        .acceptedAnswers = {"b"},
        .explanation = "endl, satırı bitirir ve ayrıca çıktı tamponunu (buffer) hemen boşaltır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 14, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "\\n ile std::endl arasındaki temel fark nedir?",
        .options = {"Aralarında fark yoktur", "endl ayrıca çıktı tamponunu boşaltır (flush)", "\\n sadece sayılarda kullanılır", "endl yalnızca dosyalarda çalışır"},
        .acceptedAnswers = {"b"},
        .explanation = "endl, satırı bitirmenin yanında çıktı tamponunu da boşaltır; \\n bunu yapmaz.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 15, .topicId = 3,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::endl kullanmak için başında std:: öneki gereklidir (using namespace std; yoksa).",
        .acceptedAnswers = {"1"},
        .explanation = "using namespace std; kullanılmıyorsa endl için std:: öneki gerekir.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 16, .topicId = 3,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::endl, \\n'den daha hızlıdır çünkü tamponu boşaltmaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Tam tersi: endl tamponu boşalttığı için \\n'den biraz daha yavaştır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 17, .topicId = 3,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::cout << \"Merhaba\" << std::_____;",
        .acceptedAnswers = {"endl"},
        .explanation = "Satırı bitirip tamponu boşaltmak için std::endl kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 18, .topicId = 3,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "endl kelimesi İngilizce 'end line' ifadesinin kısaltmasıdır ve satırı bitirmenin yanında çıktı ______'ini de boşaltır (İngilizce teknik terim).",
        .acceptedAnswers = {"buffer"},
        .explanation = "endl, çıktı tamponunu (buffer) hemen boşaltır (flush eder).",
        .baseXp = 20,
    });

    // Topic 4: cin
    questions_.push_back(Question{
        .id = 19, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "cin hangi işlem için kullanılır?",
        .options = {"Ekrana yazı yazdırmak", "Klavyeden veri okumak", "Dosya silmek", "Bir döngüyü durdurmak"},
        .acceptedAnswers = {"b"},
        .explanation = "cin, klavyeden veri okumak için kullanılan giriş akışıdır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 20, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "cin ile bir int değişkenine değer okurken hangi operatör kullanılır?",
        .options = {"<<", "+=", "==", ">>"},
        .acceptedAnswers = {"d"},
        .explanation = "cin ile okuma yaparken >> operatörü kullanılır.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 21, .topicId = 4,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "cin, kullanıcıdan klavye aracılığıyla veri almak için kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "cin, klavyeden veri okumak için kullanılan giriş akışıdır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 22, .topicId = 4,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cin, boşluk içeren tüm bir cümleyi tek seferde okuyabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "cin >> yalnızca ilk boşluğa kadar olan kısmı okur; tam bir cümle için getline() kullanılmalıdır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 23, .topicId = 4,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int yas;\nstd::_____ >> yas;",
        .acceptedAnswers = {"cin"},
        .explanation = "Klavyeden okumak için std::cin kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 24, .topicId = 4,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Klavyeden bir değeri bir değişkene aktarmak için cin ile birlikte kullanılan operatör: __ (iki karakter)",
        .acceptedAnswers = {">>"},
        .explanation = "cin ile okuma yaparken >> operatörü kullanılır.",
        .baseXp = 20,
    });

    // Topic 5: getline()
    questions_.push_back(Question{
        .id = 25, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "getline() fonksiyonu ne işe yarar?",
        .options = {"Sadece tek bir karakter okur", "Boşluk içeren tüm bir satırı okur", "Bir dosyayı siler", "Bir sayıyı yuvarlar"},
        .acceptedAnswers = {"b"},
        .explanation = "getline(), boşluklar dahil tüm bir satırı okur.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 26, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::getline(std::cin, isim); satırında isim değişkeninin türü ne olmalıdır?",
        .options = {"int", "double", "std::string", "bool"},
        .acceptedAnswers = {"c"},
        .explanation = "getline(), sonucu bir std::string değişkenine yazar.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 27, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "getline() kullanmak için <string> kütüphanesinin eklenmesi gerekir.",
        .acceptedAnswers = {"1"},
        .explanation = "getline() ve std::string, <string> kütüphanesinde tanımlıdır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 28, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cin >> ile getline() tamamen aynı şekilde çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "cin >> ilk boşluğa kadar okur, getline() ise boşluklar dahil tüm satırı okur.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 29, .topicId = 5,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string isim;\nstd::_____(std::cin, isim);",
        .acceptedAnswers = {"getline"},
        .explanation = "Boşluklu bir satırı okumak için std::getline kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 30, .topicId = 5,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "getline fonksiyonunun ilk parametresi genellikle _____ olur (giriş akışının adı).",
        .acceptedAnswers = {"cin"},
        .explanation = "getline(std::cin, degisken); şeklinde ilk parametre giriş akışıdır.",
        .baseXp = 20,
    });

    // Topic 6: int
    questions_.push_back(Question{
        .id = 31, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdakilerden hangisi tam sayı değerleri saklamak için kullanılan veri türüdür?",
        .options = {"char", "int", "bool", "string"},
        .acceptedAnswers = {"b"},
        .explanation = "int, tam sayı (ondalıksız) değerleri saklamak için kullanılan veri türüdür.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 32, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 25; satırında yas değişkenine hangi tür değer atanabilir?",
        .options = {"Sadece ondalık sayılar", "Sadece metinler", "Tam sayılar", "Sadece true/false değerleri"},
        .acceptedAnswers = {"c"},
        .explanation = "int, tam sayı değerleri saklar.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 33, .topicId = 6,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "int veri türü, ondalıklı sayıları tam olarak saklayabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "int yalnızca tam sayıları saklar; ondalıklı sayılar için double kullanılır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 34, .topicId = 6,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int sayi = 5; satırı geçerli bir C++ tanımlamasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Bu, geçerli bir int değişken tanımlama ve atama işlemidir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 35, .topicId = 6,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ sayi = 5; (tam sayı türü)",
        .acceptedAnswers = {"int"},
        .explanation = "Tam sayılar için int veri türü kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 36, .topicId = 6,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 7.9; satırı çalıştırıldığında sayi değişkeninde saklanan değer kaç olur (ondalık kısım atılarak)?",
        .acceptedAnswers = {"7"},
        .explanation = "int, ondalık kısmı saklamaz; 7.9 değeri 7 olarak kesilir.",
        .baseXp = 20,
    });

    // Topic 7: double
    questions_.push_back(Question{
        .id = 37, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Ondalıklı (kesirli) sayıları saklamak için hangi veri türü kullanılır?",
        .options = {"int", "char", "double", "bool"},
        .acceptedAnswers = {"c"},
        .explanation = "double, ondalıklı sayıları saklamak için kullanılan veri türüdür.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 38, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "double fiyat = 19.99; satırında ondalık ayıracı olarak ne kullanılmalıdır?",
        .options = {"Virgül (,)", "Nokta (.)", "İki nokta (:)", "Yıldız (*)"},
        .acceptedAnswers = {"b"},
        .explanation = "C++'ta ondalık ayıracı nokta (.) işaretidir.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 39, .topicId = 7,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "double veri türü, ondalıklı sayıları saklayabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "double, ondalıklı (kesirli) sayıları saklamak için kullanılır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 40, .topicId = 7,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "double bir değişkene tam sayı atanamaz.",
        .acceptedAnswers = {"2"},
        .explanation = "double bir değişkene tam sayı da atanabilir; sayı otomatik olarak ondalıklı forma çevrilir (örn. 5 -> 5.0).",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 41, .topicId = 7,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ fiyat = 19.99; (ondalıklı sayı türü)",
        .acceptedAnswers = {"double"},
        .explanation = "Ondalıklı sayılar için double veri türü kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 42, .topicId = 7,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "double sayi1 = 3.5;\ndouble sayi2 = 2.5;\nstd::cout << sayi1 + sayi2;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6", "6.0"},
        .explanation = "3.5 ile 2.5 toplanınca 6.0 elde edilir.",
        .baseXp = 20,
    });

    // Topic 8: char
    questions_.push_back(Question{
        .id = 43, .topicId = 8,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Tek bir karakteri saklamak için hangi veri türü kullanılır?",
        .options = {"string", "char", "int", "double"},
        .acceptedAnswers = {"b"},
        .explanation = "char, tek bir karakteri saklamak için kullanılan veri türüdür.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 44, .topicId = 8,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "char harf = 'A'; satırında 'A' değerinin etrafında hangi işaret kullanılmalıdır?",
        .options = {"Çift tırnak (\")", "Tek tırnak (')", "Köşeli parantez ([])", "Süslü parantez ({})"},
        .acceptedAnswers = {"b"},
        .explanation = "char değerleri tek tırnak (') içinde yazılır.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 45, .topicId = 8,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "char veri türü yalnızca tek bir karakter saklayabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "char, tek bir karakter saklamak için tasarlanmıştır.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 46, .topicId = 8,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "char harf = \"A\"; şeklindeki tanımlama (çift tırnaklı) doğrudur.",
        .acceptedAnswers = {"2"},
        .explanation = "char için tek tırnak ('A') kullanılmalıdır; çift tırnak string ifade eder.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 47, .topicId = 8,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ harf = 'A'; (tek karakter türü)",
        .acceptedAnswers = {"char"},
        .explanation = "Tek bir karakter için char veri türü kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 48, .topicId = 8,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir char değişkenine değer atarken kullanılması gereken tırnak türü: _____ tırnak (örnek: tek/çift)",
        .acceptedAnswers = {"tek"},
        .explanation = "char değerleri tek tırnak (') içinde yazılır; çift tırnak (\") string ifade eder.",
        .baseXp = 20,
    });

    // Topic 9: bool
    questions_.push_back(Question{
        .id = 49, .topicId = 9,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "bool veri türü hangi iki değerden birini alabilir?",
        .options = {"0 ve 100", "true ve false", "A ve B", "int ve double"},
        .acceptedAnswers = {"b"},
        .explanation = "bool, true (doğru) veya false (yanlış) değerlerinden birini saklar.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 50, .topicId = 9,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << true; ifadesi ekrana ne yazdırır?",
        .options = {"true", "1", "doğru", "evet"},
        .acceptedAnswers = {"b"},
        .explanation = "cout, varsayılan olarak true değerini 1 olarak yazdırır.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 51, .topicId = 9,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "bool veri türü yalnızca true veya false değerlerini saklar.",
        .acceptedAnswers = {"1"},
        .explanation = "bool, yalnızca true veya false değerlerinden birini saklar.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 52, .topicId = 9,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cout ile bir bool değişken yazdırıldığında ekranda \"true\" veya \"false\" kelimeleri görünür.",
        .acceptedAnswers = {"2"},
        .explanation = "Varsayılan olarak cout, bool değerlerini true için 1, false için 0 şeklinde yazdırır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 53, .topicId = 9,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ aktif = true; (mantıksal veri türü)",
        .acceptedAnswers = {"bool"},
        .explanation = "Mantıksal (true/false) değerler için bool veri türü kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 54, .topicId = 9,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << false; ifadesinin ekran çıktısı: _____ (rakam)",
        .acceptedAnswers = {"0"},
        .explanation = "cout, false değerini 0 olarak yazdırır.",
        .baseXp = 20,
    });

    // Topic 10: const
    questions_.push_back(Question{
        .id = 55, .topicId = 10,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "const anahtar kelimesi ne işe yarar?",
        .options = {"Bir döngüyü sonlandırır", "Bir değişkenin değerinin değiştirilmesini engeller", "Bir fonksiyonu siler", "Bir dosyayı açar"},
        .acceptedAnswers = {"b"},
        .explanation = "const, bir değişkenin değerinin tanımlandıktan sonra değiştirilemeyeceğini belirtir.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 56, .topicId = 10,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "const int MAKS = 100; tanımlandıktan sonra MAKS = 200; satırı çalıştırılırsa ne olur?",
        .options = {"Program çalışır, MAKS 200 olur", "Derleme hatası oluşur", "MAKS otomatik olarak 300 olur", "Hiçbir şey olmaz, satır yok sayılır"},
        .acceptedAnswers = {"b"},
        .explanation = "const bir değişkene yeniden değer atamaya çalışmak derleme hatasına yol açar.",
        .baseXp = 20,
    });
    questions_.push_back(Question{
        .id = 57, .topicId = 10,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "const olarak tanımlanan bir değişkenin değeri sonradan değiştirilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "const bir değişkenin değeri tanımlandıktan sonra değiştirilemez.",
        .baseXp = 5,
    });
    questions_.push_back(Question{
        .id = 58, .topicId = 10,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "const bir değişken tanımlanırken başlangıç değeri verilmesi gerekir.",
        .acceptedAnswers = {"1"},
        .explanation = "const değişkenler tanımlandığı anda bir başlangıç değeri almalıdır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 59, .topicId = 10,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ double PI = 3.14; (değeri değiştirilemeyen anlamına gelen anahtar kelime)",
        .acceptedAnswers = {"const"},
        .explanation = "Değeri değiştirilemeyen değişkenler için const kullanılır.",
        .baseXp = 10,
    });
    questions_.push_back(Question{
        .id = 60, .topicId = 10,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "const int X = 5;\nX = 10;\nYukarıdaki ikinci satır çalıştırılmaya çalışıldığında ne oluşur? (Türkçe kelime: hata/uyarı)",
        .acceptedAnswers = {"hata"},
        .explanation = "const olarak tanımlanmış bir değişkene yeniden değer atamaya çalışmak derleme hatasına yol açar.",
        .baseXp = 20,
    });
}

std::vector<Question> QuestionManager::questionsForTopic(int topicId) const {
    std::vector<Question> result;
    for (const Question& question : questions_) {
        if (question.topicId == topicId) {
            result.push_back(question);
        }
    }
    return result;
}
```

- [ ] **Step 4: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>

#include "QuestionManager.h"

int main() {
    QuestionManager questions;

    int total = 0;
    for (int topicId = 1; topicId <= 10; ++topicId) {
        const auto topicQuestions = questions.questionsForTopic(topicId);
        std::cout << "Konu " << topicId << ": " << topicQuestions.size()
                  << " soru (beklenen: 6)\n";
        total += static_cast<int>(topicQuestions.size());
    }
    std::cout << "Toplam soru: " << total << " (beklenen: 60)\n";

    const auto emptyTopic = questions.questionsForTopic(11);
    std::cout << "Konu 11 soru sayisi: " << emptyTopic.size() << " (beklenen: 0)\n";

    return 0;
}
```

- [ ] **Step 5: Update `CMakeLists.txt`'s `add_executable` call**, inserting the three new files after the `ConsoleUI` entries and before `Application`:

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
    src/Application.h
    src/Application.cpp
)
```

- [ ] **Step 6: Build and run**

Run:
```bash
cmake --build build
./build/Debug/CppMasterConsole.exe   # or ./build/CppMasterConsole for a single-config generator
```
Expected output: all 10 topics report "6 soru (beklenen: 6)", total is 60, topic 11 reports 0. Zero compiler warnings.

- [ ] **Step 7: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/Question.h src/QuestionManager.h src/QuestionManager.cpp
git commit -m "Add Question struct and QuestionManager with 60-question bank for topics 1-10"
```

---

### Task 2: `QuizEngine` — stateless answer evaluation and XP

**Files:**
- Create: `src/QuizEngine.h`
- Create: `src/QuizEngine.cpp`
- Modify: `CMakeLists.txt`
- Modify (temporarily, superseded in Task 5): `src/main.cpp`

**Interfaces:**
- Consumes: `Question` (Task 1).
- Produces:
  - `struct AnswerResult { bool correct; int xpAwarded; std::string correctAnswerDisplay; };`
  - `class QuizEngine { public: AnswerResult evaluate(const Question& question, const std::string& rawAnswer) const; };`

- [ ] **Step 1: Create `src/QuizEngine.h`**

```cpp
#pragma once

#include <string>

#include "Question.h"

struct AnswerResult {
    bool correct;
    int xpAwarded;
    std::string correctAnswerDisplay;
};

class QuizEngine {
public:
    [[nodiscard]] AnswerResult evaluate(const Question& question, const std::string& rawAnswer) const;
};
```

- [ ] **Step 2: Create `src/QuizEngine.cpp`**

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

}  // namespace

AnswerResult QuizEngine::evaluate(const Question& question, const std::string& rawAnswer) const {
    const std::string normalizedAnswer = trimAndLower(rawAnswer);

    bool isCorrect = false;
    for (const std::string& accepted : question.acceptedAnswers) {
        if (normalizedAnswer == trimAndLower(accepted)) {
            isCorrect = true;
            break;
        }
    }

    return AnswerResult{
        isCorrect,
        isCorrect ? question.baseXp : 0,
        correctAnswerDisplayFor(question),
    };
}
```

- [ ] **Step 3: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>

#include "QuestionManager.h"
#include "QuizEngine.h"

int main() {
    QuestionManager questions;
    QuizEngine engine;

    const auto topic1Questions = questions.questionsForTopic(1);

    // Q1 (id=1, MultipleChoice, correct="b"): try correct, wrong, and case-insensitive.
    const auto& q1 = topic1Questions.at(0);
    std::cout << "Q1 dogru cevap 'b': "
              << (engine.evaluate(q1, "b").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "Q1 dogru cevap 'B' (buyuk harf): "
              << (engine.evaluate(q1, "B").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "Q1 yanlis cevap 'a': "
              << (!engine.evaluate(q1, "a").correct ? "YANLIS (OK)" : "HATA") << '\n';
    std::cout << "Q1 XP (dogru): " << engine.evaluate(q1, "b").xpAwarded << " (beklenen: 10)\n";
    std::cout << "Q1 XP (yanlis): " << engine.evaluate(q1, "a").xpAwarded << " (beklenen: 0)\n";
    std::cout << "Q1 dogru cevap gosterimi: " << engine.evaluate(q1, "a").correctAnswerDisplay
              << " (beklenen: B) cout)\n";

    // Q3 (id=3, TrueFalse, correct="2"): try correct digit and wrong digit.
    const auto& q3 = topic1Questions.at(2);
    std::cout << "Q3 dogru cevap '2': "
              << (engine.evaluate(q3, "2").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "Q3 yanlis cevap '1': "
              << (!engine.evaluate(q3, "1").correct ? "YANLIS (OK)" : "HATA") << '\n';

    // Q5 (id=5, FillBlank, correct="cout"): try with whitespace and different case.
    const auto& q5 = topic1Questions.at(4);
    std::cout << "Q5 dogru cevap '  COUT  ' (bosluklu, buyuk harf): "
              << (engine.evaluate(q5, "  COUT  ").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "Q5 yanlis cevap 'cin': "
              << (!engine.evaluate(q5, "cin").correct ? "YANLIS (OK)" : "HATA") << '\n';

    return 0;
}
```

- [ ] **Step 4: Update `CMakeLists.txt`'s `add_executable` call**, inserting the two new files after `QuestionManager.cpp` and before `Application.h` — this is also this plan's final `add_executable` form (Tasks 3-4 don't add any new files):

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
    src/Application.h
    src/Application.cpp
)
```

- [ ] **Step 5: Build and run**

Run:
```bash
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line above ends in "(OK)" except the two XP lines (10 and 0) and the display line (`B) cout`). Zero compiler warnings.

- [ ] **Step 6: Commit**

```bash
git add CMakeLists.txt src/main.cpp src/QuizEngine.h src/QuizEngine.cpp
git commit -m "Add QuizEngine with ASCII-normalized answer evaluation and XP"
```

---

### Task 3: Populate `LessonManager` content for topics 1-10

**Files:**
- Modify: `src/LessonManager.cpp`

**Interfaces:**
- Consumes: `Lesson` (existing, unchanged shape — this task only populates already-existing fields that were left empty in Foundation).
- Produces: no interface change. `LessonManager::findById(1..10)` now returns lessons with non-empty `explanation`/`syntax`/`exampleCode`/`lineExplanations`/`commonMistakes`; ids 11-100 remain exactly as before (empty content fields).

- [ ] **Step 1: Add a content-population function and call it from the constructor**

In `src/LessonManager.cpp`, add a new function inside the existing anonymous namespace (after the `kTopicSeeds` array, before the closing `}  // namespace`):

```cpp
void applyIntroLessonContent(std::vector<Lesson>& lessons) {
    // Index 0 = topic id 1 (cout), index 9 = topic id 10 (const) — the seed
    // table above is authored in strict ascending id order starting at 1,
    // so this positional mapping is safe.

    lessons[0].explanation =
        "cout, ekrana veri yazdırmak için kullanılan bir çıktı akışıdır "
        "(output stream). Kullanabilmek için <iostream> kütüphanesinin "
        "eklenmesi gerekir. << operatörü ile bir veya birden fazla değer "
        "art arda ekrana yazdırılabilir.";
    lessons[0].syntax = "#include <iostream>\n\nstd::cout << \"Merhaba\";";
    lessons[0].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    std::cout << \"Merhaba, dünya!\";\n"
        "    return 0;\n"
        "}";
    lessons[0].lineExplanations = {
        "#include <iostream> : cout kullanabilmek için gereken kütüphaneyi ekler.",
        "std::cout << \"Merhaba, dünya!\"; : Tırnak içindeki metni olduğu gibi ekrana yazdırır.",
        "return 0; : Programın hatasız bittiğini işletim sistemine bildirir.",
    };
    lessons[0].commonMistakes = {
        "std:: önekini unutmak (using namespace std; yoksa derleme hatası oluşur).",
        "<iostream> kütüphanesini eklemeyi unutmak.",
        "<< operatörünü = (atama) operatörüyle karıştırmak.",
    };

    lessons[1].explanation =
        "\\n, metin içinde yeni satıra geçmeyi sağlayan bir kaçış (escape) "
        "dizisidir. Çift tırnak içindeki bir metnin istenilen yerine "
        "yazılarak ekran çıktısında satır atlanmasını sağlar. std::endl de "
        "aynı işi yapar, ancak \\n ekstra bir tamponu (buffer) boşaltma "
        "işlemi yapmadığı için genellikle daha hızlıdır.";
    lessons[1].syntax = "std::cout << \"Birinci satır\\n\";\nstd::cout << \"İkinci satır\\n\";";
    lessons[1].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    std::cout << \"Merhaba\\n\";\n"
        "    std::cout << \"Dünya\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[1].lineExplanations = {
        "\"Merhaba\\n\" : Merhaba yazdıktan sonra imleci bir alt satıra geçirir.",
        "\"Dünya\\n\" : Dünya yazdıktan sonra tekrar alt satıra geçer.",
        "İki ayrı cout ifadesi, \\n sayesinde iki ayrı satırda görünür.",
    };
    lessons[1].commonMistakes = {
        "\\n yerine yanlışlıkla /n yazmak (ters slash yerine düz slash kullanmak).",
        "\\n ifadesini tırnakların dışına yazmak.",
        "Satır atlamanın otomatik olduğunu sanıp \\n eklemeyi unutmak.",
    };

    lessons[2].explanation =
        "std::endl, çıktıyı yeni satıra geçirir ve ayrıca çıktı tamponunu "
        "(buffer) hemen boşaltır (flush). Bu ekstra boşaltma işlemi \\n'e "
        "göre biraz daha yavaştır; bu yüzden sık tekrarlanan yazdırmalarda "
        "genellikle \\n tercih edilir, ama endl de tamamen geçerlidir.";
    lessons[2].syntax = "std::cout << \"Merhaba\" << std::endl;";
    lessons[2].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    std::cout << \"Birinci\" << std::endl;\n"
        "    std::cout << \"İkinci\" << std::endl;\n"
        "    return 0;\n"
        "}";
    lessons[2].lineExplanations = {
        "std::cout << \"Birinci\" << std::endl; : Birinci yazar, ardından satırı bitirip tamponu boşaltır.",
        "std::cout << \"İkinci\" << std::endl; : İkinci yazar ve yine satırı bitirir.",
        "İki endl, çıktının iki ayrı satırda görünmesini sağlar.",
    };
    lessons[2].commonMistakes = {
        "endl yazarken std:: önekini unutmak.",
        "endl ile \\n'in birebir aynı hızda olduğunu sanmak (endl ekstra flush yapar).",
        "endl'i çift tırnak içine yazmak (\"endl\" gibi) — bu durumda sadece düz metin olarak yazdırılır, satır atlamaz.",
    };

    lessons[3].explanation =
        "cin, klavyeden veri okumak için kullanılan giriş akışıdır (input "
        "stream). >> operatörü ile bir değişkene değer atanır. Boşluk veya "
        "yeni satır görene kadar okuma yapar; bu yüzden boşluk içeren "
        "metinler için getline() tercih edilir.";
    lessons[3].syntax = "int yas;\nstd::cin >> yas;";
    lessons[3].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int yas;\n"
        "    std::cout << \"Yaşınız: \";\n"
        "    std::cin >> yas;\n"
        "    std::cout << \"Yaşınız: \" << yas;\n"
        "    return 0;\n"
        "}";
    lessons[3].lineExplanations = {
        "int yas; : Kullanıcının gireceği yaşı saklamak için bir tam sayı değişkeni tanımlar.",
        "std::cin >> yas; : Klavyeden girilen değeri okuyup yas değişkenine atar.",
        "std::cout << ... << yas; : Okunan değeri tekrar ekrana yazdırır.",
    };
    lessons[3].commonMistakes = {
        ">> operatörünü << ile karıştırmak (cin için >> kullanılır).",
        "cin ile boşluk içeren bir cümleyi okumaya çalışmak (yalnızca ilk kelimeyi alır).",
        "Değişken türü ile girilen verinin uyuşmamasına dikkat etmemek (örneğin sayı beklenirken harf girilmesi).",
    };

    lessons[4].explanation =
        "getline(), kullanıcıdan boşluk içeren tam bir satırı okumak için "
        "kullanılır. cin >> yalnızca ilk boşluğa kadar okurken, "
        "getline(std::cin, degisken) tüm satırı (yeni satıra kadar) okur. "
        "Kullanmak için <string> kütüphanesi ve bir std::string değişkeni gerekir.";
    lessons[4].syntax = "std::string isim;\nstd::getline(std::cin, isim);";
    lessons[4].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::string isimSoyisim;\n"
        "    std::cout << \"Adınız soyadınız: \";\n"
        "    std::getline(std::cin, isimSoyisim);\n"
        "    std::cout << \"Merhaba, \" << isimSoyisim;\n"
        "    return 0;\n"
        "}";
    lessons[4].lineExplanations = {
        "#include <string> : std::string ve getline için gerekli kütüphaneyi ekler.",
        "std::string isimSoyisim; : Boşluk içerebilecek metni saklayacak değişkeni tanımlar.",
        "std::getline(std::cin, isimSoyisim); : Kullanıcının girdiği tüm satırı (boşluklar dahil) okuyup değişkene atar.",
    };
    lessons[4].commonMistakes = {
        "<string> kütüphanesini eklemeyi unutmak.",
        "getline() öncesinde kullanılan bir cin >> ifadesinin bıraktığı yeni satır karakterini temizlememek (bu durumda getline boş okuyabilir).",
        "getline() parametrelerinin sırasını karıştırmak (önce cin, sonra değişken gelir).",
    };

    lessons[5].explanation =
        "int, tam sayı (ondalıksız) değerleri saklamak için kullanılan "
        "temel bir veri türüdür. Örneğin yaş, adet veya sayaç gibi "
        "değerler genellikle int ile tutulur.";
    lessons[5].syntax = "int sayi = 5;";
    lessons[5].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int yas = 25;\n"
        "    std::cout << yas;\n"
        "    return 0;\n"
        "}";
    lessons[5].lineExplanations = {
        "int yas = 25; : yas adında bir tam sayı değişkeni tanımlar ve 25 değerini atar.",
        "std::cout << yas; : yas değişkeninin değerini ekrana yazdırır.",
    };
    lessons[5].commonMistakes = {
        "int türüne ondalıklı bir sayı (örneğin 3.14) atamaya çalışmak (ondalık kısım kaybolur).",
        "Değişkeni tanımlarken türünü (int) yazmayı unutmak.",
        "Çok büyük sayılarda int'in sınırlarını (taşma riski) göz ardı etmek.",
    };

    lessons[6].explanation =
        "double, ondalıklı (kesirli) sayıları saklamak için kullanılan bir "
        "veri türüdür. Örneğin fiyat, ortalama veya yüzde gibi kesirli "
        "değerler double ile tutulur.";
    lessons[6].syntax = "double fiyat = 19.99;";
    lessons[6].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    double ortalama = 87.5;\n"
        "    std::cout << ortalama;\n"
        "    return 0;\n"
        "}";
    lessons[6].lineExplanations = {
        "double ortalama = 87.5; : ortalama adında ondalıklı bir değişken tanımlar ve 87.5 değerini atar.",
        "std::cout << ortalama; : ortalama değişkeninin değerini ekrana yazdırır.",
    };
    lessons[6].commonMistakes = {
        "double gereken bir yerde int kullanmak (ondalık kısmın kaybolmasına yol açar).",
        "Ondalık ayıracı olarak virgül (,) kullanmak (C++'ta nokta (.) kullanılır).",
        "double ile float'ı karıştırmak (ikisi de ondalıklıdır ama farklı hassasiyete sahiptir).",
    };

    lessons[7].explanation =
        "char, tek bir karakteri (harf, rakam veya sembol) saklamak için "
        "kullanılan bir veri türüdür. Değer tanımlarken tek tırnak (') "
        "kullanılır, örneğin 'A'.";
    lessons[7].syntax = "char harf = 'A';";
    lessons[7].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    char harf = 'B';\n"
        "    std::cout << harf;\n"
        "    return 0;\n"
        "}";
    lessons[7].lineExplanations = {
        "char harf = 'B'; : harf adında bir karakter değişkeni tanımlar ve 'B' değerini atar.",
        "std::cout << harf; : harf değişkeninin değerini ekrana yazdırır.",
    };
    lessons[7].commonMistakes = {
        "char değeri tanımlarken çift tırnak (\"A\") kullanmak (bu bir string olur, char için tek tırnak gerekir).",
        "Bir char değişkenine birden fazla karakter atamaya çalışmak (örn. 'AB' geçersizdir).",
        "char ile string'i karıştırmak (char tek karakter, string ise karakter dizisidir).",
    };

    lessons[8].explanation =
        "bool, yalnızca true (doğru) veya false (yanlış) değerlerinden "
        "birini saklayan bir veri türüdür. Genellikle bir koşulun "
        "sonucunu tutmak için kullanılır.";
    lessons[8].syntax = "bool aktif = true;";
    lessons[8].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    bool gecti = true;\n"
        "    std::cout << gecti;\n"
        "    return 0;\n"
        "}";
    lessons[8].lineExplanations = {
        "bool gecti = true; : gecti adında bir mantıksal değişken tanımlar ve true (doğru) değerini atar.",
        "std::cout << gecti; : gecti değişkenini ekrana yazdırır (true için 1, false için 0 görünür).",
    };
    lessons[8].commonMistakes = {
        "true/false yerine \"true\"/\"false\" gibi tırnaklı metin yazmak (bunlar string olur, bool değildir).",
        "cout ile bool yazdırıldığında true/false yerine 1/0 göründüğünü unutmak.",
        "bool değişkenine 0 veya 1 dışında sayılar atayıp anlamını karıştırmak.",
    };

    lessons[9].explanation =
        "const, bir değişkenin değerinin tanımlandıktan sonra "
        "değiştirilemeyeceğini belirtir. Sabit kalması gereken değerler "
        "(örneğin pi sayısı) için kullanılır. const bir değişkene ikinci "
        "kez değer atamaya çalışmak derleme hatası verir.";
    lessons[9].syntax = "const double PI = 3.14;";
    lessons[9].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    const int MAKS_PUAN = 100;\n"
        "    std::cout << MAKS_PUAN;\n"
        "    return 0;\n"
        "}";
    lessons[9].lineExplanations = {
        "const int MAKS_PUAN = 100; : MAKS_PUAN adında, değeri sonradan değiştirilemeyecek bir sabit tanımlar.",
        "std::cout << MAKS_PUAN; : Sabitin değerini ekrana yazdırır.",
    };
    lessons[9].commonMistakes = {
        "const olarak tanımlanan bir değişkene sonradan yeni bir değer atamaya çalışmak (derleme hatası oluşur).",
        "const bir değişkeni tanımlarken başlangıç değeri vermemek (const değişkenler tanımlandığı anda değer almalıdır).",
        "const kullanmanın performansı yavaşlattığını sanmak (aksine, derleyiciye ek bilgi vererek optimizasyona yardımcı olabilir).",
    };
}
```

- [ ] **Step 2: Call this function at the end of the constructor**

In `LessonManager::LessonManager()`, after the existing `for (const TopicSeed& seed : kTopicSeeds) { ... }` loop and before the closing `}` of the constructor, add:

```cpp
    applyIntroLessonContent(lessons_);
```

- [ ] **Step 3: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>

#include "LessonManager.h"

int main() {
    LessonManager lessons;

    const auto first = lessons.findById(1);
    std::cout << "Konu 1 aciklama bos mu: "
              << (first->explanation.empty() ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Konu 1 satir aciklama sayisi: " << first->lineExplanations.size()
              << " (beklenen: 3)\n";
    std::cout << "Konu 1 yaygin hata sayisi: " << first->commonMistakes.size()
              << " (beklenen: 3)\n";

    const auto tenth = lessons.findById(10);
    std::cout << "Konu 10 aciklama bos mu: "
              << (tenth->explanation.empty() ? "EVET (HATA)" : "HAYIR (OK)") << '\n';

    const auto eleventh = lessons.findById(11);
    std::cout << "Konu 11 aciklama bos mu: "
              << (eleventh->explanation.empty() ? "EVET (OK)" : "HAYIR (HATA)") << '\n';

    return 0;
}
```

- [ ] **Step 4: Build and run**

Run:
```bash
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected: every line ends in "(OK)". Zero compiler warnings.

- [ ] **Step 5: Commit**

```bash
git add src/LessonManager.cpp src/main.cpp
git commit -m "Populate LessonManager content for topics 1-10"
```

---

### Task 4: XP tracking on `UserProgress`

**Files:**
- Modify: `src/UserProgress.h`
- Modify: `src/UserProgress.cpp`
- Modify (temporarily, superseded in Task 5): `src/main.cpp`

**Interfaces:**
- Consumes: nothing new.
- Produces: `int UserProgress::totalXp() const;` and `void UserProgress::addXp(int amount);`, in addition to the existing `statusOf`/`setStatus` from Foundation (unchanged).

- [ ] **Step 1: Modify `src/UserProgress.h`**

Add these two public method declarations and one private member, so the full file reads:

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

private:
    std::unordered_map<int, TopicStatus> statusByTopicId_;
    int totalXp_ = 0;
};
```

- [ ] **Step 2: Modify `src/UserProgress.cpp`**

Add these two method definitions at the end of the file (after `setStatus`), so the full file reads:

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
```

- [ ] **Step 3: Temporarily wire a verification check into `src/main.cpp`**

Replace the contents of `src/main.cpp` with:

```cpp
#include <iostream>

#include "UserProgress.h"

int main() {
    UserProgress progress(5);

    std::cout << "Baslangic XP: " << progress.totalXp() << " (beklenen: 0)\n";

    progress.addXp(10);
    progress.addXp(20);
    std::cout << "Iki ekleme sonrasi XP: " << progress.totalXp() << " (beklenen: 30)\n";

    return 0;
}
```

- [ ] **Step 4: Build and run**

Run:
```bash
cmake --build build
./build/Debug/CppMasterConsole.exe
```
Expected:
```
Baslangic XP: 0 (beklenen: 0)
Iki ekleme sonrasi XP: 30 (beklenen: 30)
```
Zero compiler warnings.

- [ ] **Step 5: Commit**

```bash
git add src/UserProgress.h src/UserProgress.cpp src/main.cpp
git commit -m "Add XP tracking to UserProgress"
```

---

### Task 5: Wire `Application` — real topic-open and quiz flow

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`

Note: `CMakeLists.txt` already lists every file this task touches — Task 2
left it in its final phase-2 form (Tasks 3-4 added no new files). No
`CMakeLists.txt` change is needed in this task.

**Interfaces:**
- Consumes:
  - `QuestionManager::questionsForTopic(int)` (Task 1), `QuizEngine::evaluate(const Question&, const std::string&)` (Task 2), `LessonManager`'s now-populated content fields (Task 3), `UserProgress::addXp(int)`/`totalXp()` (Task 4).
  - Existing `ConsoleUI::readLine(const std::string&)`, `readMenuChoice(int,int)`, `printLine`, `printHeader` (Foundation, unchanged).
- Produces: no new public interface — `Application`'s public surface (`Application()`, `run()`) is unchanged; this task only changes what happens inside it.

- [ ] **Step 1: Modify `src/Application.h`** to add the two new members and three new private methods

```cpp
#pragma once

#include <string>

#include "ConsoleUI.h"
#include "LessonManager.h"
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
    void showNotYetAvailable(const std::string& featureName);
    void ensureDataDirectoryExists();

    ConsoleUI ui_;
    LessonManager lessons_;
    QuestionManager questions_;
    QuizEngine quizEngine_;
    UserProgress progress_;
    bool running_ = true;
};
```

- [ ] **Step 2: Modify `src/Application.cpp`**

Replace the existing `showTopicBrowser` function with a version that also prompts for a topic number, and add the three new methods (`openTopic`, `showLessonContent`, `runTopicQuiz`) plus a small local helper for multiple-choice option lettering. The full file should read:

```cpp
#include "Application.h"

#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>

namespace {

constexpr int kMinChoice = 0;
constexpr int kMaxChoice = 10;
constexpr int kMinTopicId = 0;
constexpr int kMaxTopicId = 100;
constexpr double kPassThreshold = 0.7;

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

char optionLetter(std::size_t index) {
    return static_cast<char>('A' + index);
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
    ui_.printLine("CppMaster Console'a hoş geldin! (Foundation sürümü)");

    while (running_) {
        showMainMenu();
        const int choice = ui_.readMenuChoice(kMinChoice, kMaxChoice);
        handleChoice(choice);
    }
}

void Application::showMainMenu() {
    ui_.printHeader("CPPMASTER CONSOLE");
    ui_.printLine("");
    ui_.printLine("Toplam XP: " + std::to_string(progress_.totalXp()));
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

    ui_.printLine("Görüntülemek istediğiniz konu numarasını girin (0 = ana menüye dön):");
    const int topicChoice = ui_.readMenuChoice(kMinTopicId, kMaxTopicId);
    if (topicChoice == 0) {
        return;
    }
    openTopic(topicChoice);
}

void Application::openTopic(int topicId) {
    const auto lesson = lessons_.findById(topicId);
    if (!lesson.has_value() || lesson->explanation.empty()) {
        ui_.printLine("");
        ui_.printLine("Bu konu için ders içeriği bu sürümde henüz eklenmedi.");
        return;
    }

    showLessonContent(*lesson);
    runTopicQuiz(topicId);
}

void Application::showLessonContent(const Lesson& lesson) {
    ui_.printLine("");
    ui_.printHeader(std::to_string(lesson.id) + ". " + lesson.title);
    ui_.printLine(lesson.explanation);
    ui_.printLine("");
    ui_.printLine("Sözdizimi:");
    ui_.printLine(lesson.syntax);
    ui_.printLine("");
    ui_.printLine("Örnek:");
    ui_.printLine(lesson.exampleCode);
    ui_.printLine("");
    ui_.printLine("Satır satır açıklama:");
    for (const std::string& lineExplanation : lesson.lineExplanations) {
        ui_.printLine("- " + lineExplanation);
    }
    ui_.printLine("");
    ui_.printLine("Yaygın hatalar:");
    for (const std::string& mistake : lesson.commonMistakes) {
        ui_.printLine("- " + mistake);
    }
    ui_.printLine("");
}

void Application::runTopicQuiz(int topicId) {
    const auto quizQuestions = questions_.questionsForTopic(topicId);

    ui_.printLine("Konu testi başlıyor (" + std::to_string(quizQuestions.size()) + " soru).");
    ui_.printLine("");

    int correctCount = 0;
    int sessionXp = 0;

    for (const Question& question : quizQuestions) {
        ui_.printLine(question.prompt);

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

        if (result.correct) {
            ui_.printLine("Doğru! (+" + std::to_string(result.xpAwarded) + " XP)");
            ++correctCount;
            sessionXp += result.xpAwarded;
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
}

void Application::showNotYetAvailable(const std::string& featureName) {
    ui_.printLine("");
    ui_.printLine(
        "\"" + featureName + "\" bu sürümde henüz eklenmedi. Sonraki aşamada gelecek.");
}
```

- [ ] **Step 3: Build** (no `CMakeLists.txt` change needed — see the note above)

Run:
```bash
cmake --build build
```
Expected: build succeeds with zero warnings. (`src/main.cpp` is already at its Foundation-phase final form — `Application app; app.run();` — from Task 5 of the Foundation plan; this task does not touch it.)

- [ ] **Step 4: Full manual verification (this phase's acceptance test)**

Run `./build/Debug/CppMasterConsole.exe` and pipe a full topic-1 quiz session, deliberately answering some questions wrong to exercise the wrong-answer path:

```bash
printf '1\n1\nB\nc\n2\n1\ncout\niostream\n0\n' | ./build/Debug/CppMasterConsole.exe
```

This selects: main menu option `1` (Konuları Öğren), topic number `1` (cout), then answers Q1 with `B` (correct), Q2 with `c` (correct), Q3 with `2` (correct), Q4 with `1` (correct), Q5 with `cout` (correct), Q6 with `iostream` (correct) — then `0` to return to the main menu after the browser reappears.

Confirm:
1. Selecting topic `1` prints the full lesson content for `cout` (explanation, "Sözdizimi:", "Örnek:", "Satır satır açıklama:" with 3 bullet lines, "Yaygın hatalar:" with 3 bullet lines).
2. All 6 questions are asked in order, each MultipleChoice question shows lettered options `A)`-`D)`, each TrueFalse question shows "1. Doğru" / "2. Yanlış".
3. Every answer above is accepted as correct (each prints "Doğru! (+N XP)" with the right XP for that question's difficulty: 10, 20, 5, 10, 10, 20).
4. The final summary reads `Sonuç: 6/6 doğru (%100), kazanılan XP: 75` and "Bu konu tamamlandı olarak işaretlendi."
5. Back at the main menu, "Toplam XP: 75" is shown.

Then run a second pass with a deliberate wrong answer to check that path:

```bash
printf '1\n1\nA\n0\n' | ./build/Debug/CppMasterConsole.exe
```

Confirm answering Q1 with `A` (wrong — correct is `B`) prints the full wrong-answer block: "Yanlış cevap.", "Senin cevabın:" / `A`, "Doğru cevap:" / `B) cout`, "Açıklama:" / the Q1 explanation text — and does not crash or skip remaining questions (you'll need to keep supplying answers for Q2-Q6, or accept a low/failing score and confirm the topic is marked "Learning" instead of "Completed" in that run).

Finally, confirm topics 11-100 are unaffected: `printf '1\n11\n0\n' | ./build/Debug/CppMasterConsole.exe` selects the browser, then topic `11`, which should print "Bu konu için ders içeriği bu sürümde henüz eklenmedi." and return straight to the *main menu* (not back into the browser — `showTopicBrowser` handles exactly one topic selection per call, same as Foundation), where the final `0` exits.

- [ ] **Step 5: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Wire Application to a real topic-open and quiz flow, completing phase 2"
```

---

## Post-plan note

This completes phase 2 (Static Lesson + Quiz Core) of the decomposition.
Phase 3 (richer question types: code completion, predict-output, find-error,
fix-code, order-code, write-code) gets its own brainstorming → spec → plan
cycle before implementation starts, since it introduces new `QuestionType`
handling in `Application`'s quiz loop and needs its own answer-evaluation
rules per type.

# CppMaster Console — Kod Yazma Alıştırmaları (Code Exercises) Implementation Plan (Phase 11)

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Replace the "Kod Yazma Alıştırmaları" (menu option 5) stub with a
real practice mode containing all 25 tasks the original brief asks for (7
Başlangıç, 9 Orta, 9 İleri), each with a description, expected behavior,
sample input/output, progressive hints, a sample solution (never shown
before an attempt), and an alternative-solution note — graded entirely by
the project's existing `QuizEngine` `WriteCode` logic, with zero new
evaluation code.

**Architecture:** A new `CodeExercise` data struct + `CodeExerciseManager`
(mirroring `QuestionManager`/`LessonManager`'s shape) holds all 25
hand-authored exercises. A small pure conversion function
(`toWriteCodeQuestion`) turns any `CodeExercise` into a `WriteCode`
`Question` so `QuizEngine::evaluate` — already tested, already
settings-aware — grades it with no new logic. `Application` gets a new
interactive mode (tier submenu → exercise list → description/hints →
multi-line code submission → grading → solution reveal).

**Tech Stack:** C++20, CMake ≥ 3.20, standard library only.

**Spec:** `docs/superpowers/specs/2026-07-16-code-exercises-design.md`

## Global Constraints

- C++20 required, CMake ≥ 3.20, standard library only.
- Zero compiler warnings on the library, app, and test executable (`apply_strict_warnings()`).
- No `using namespace std;` anywhere.
- **No new evaluation logic.** Every exercise's submitted code is graded by
  converting the exercise to a `WriteCode` `Question` and calling the
  existing `QuizEngine::evaluate` — do not write a parallel checker.
- Tests never touch `data/`.
- Before running any task's manual verification below, delete
  `data/progress.txt`, `data/mistakes.txt`, `data/achievements.txt`,
  `data/generated_question_history.txt`, and `data/settings.txt` if they
  exist.
- After Task 3's final commit, update `docs/superpowers/roadmap.md`'s
  Phase 11 entry and Status section to mark it COMPLETE with its commit
  range, per the standing requirement recorded in that file since Phase 9.

---

### Task 1: `CodeExercise` data model and all 25 hand-authored exercises

**Files:**
- Create: `src/CodeExercise.h`
- Create: `src/CodeExerciseManager.h`
- Create: `src/CodeExerciseManager.cpp`
- Create: `tests/CodeExerciseManagerTests.cpp`
- Modify: `CMakeLists.txt`

**Interfaces:**
- Consumes: nothing new.
- Produces: `struct CodeExercise` (fields: `id`, `tier`, `title`,
  `description`, `expectedBehavior`, `sampleInput`, `sampleOutput`,
  `hints` (`std::vector<std::string>`), `requiredKeywords`
  (`std::vector<std::string>`), `sampleSolution`,
  `alternativeSolutionNote`, `baseXp`), `class CodeExerciseManager` with
  `std::vector<CodeExercise> exercisesForTier(const std::string& tier) const`
  and `std::optional<CodeExercise> findById(int id) const` — Task 2/3 use
  these exact names.

- [ ] **Step 1: Create `src/CodeExercise.h`**

```cpp
#pragma once

#include <string>
#include <vector>

struct CodeExercise {
    int id = 0;
    std::string tier;
    std::string title;
    std::string description;
    std::string expectedBehavior;
    std::string sampleInput;
    std::string sampleOutput;
    std::vector<std::string> hints;
    std::vector<std::string> requiredKeywords;
    std::string sampleSolution;
    std::string alternativeSolutionNote;
    int baseXp = 0;
};
```

- [ ] **Step 2: Create `src/CodeExerciseManager.h`**

```cpp
#pragma once

#include <optional>
#include <string>
#include <vector>

#include "CodeExercise.h"

class CodeExerciseManager {
public:
    CodeExerciseManager();

    [[nodiscard]] std::vector<CodeExercise> exercisesForTier(const std::string& tier) const;
    [[nodiscard]] std::optional<CodeExercise> findById(int id) const;
    [[nodiscard]] const std::vector<CodeExercise>& allExercises() const;

private:
    void addBeginnerExercises();
    void addIntermediateExercises();
    void addAdvancedExercises();

    std::vector<CodeExercise> exercises_;
};
```

- [ ] **Step 3: Create `src/CodeExerciseManager.cpp`**

```cpp
#include "CodeExerciseManager.h"

namespace {
constexpr const char* kBaslangic = "Başlangıç";
constexpr const char* kOrta = "Orta";
constexpr const char* kIleri = "İleri";
constexpr int kBaslangicXp = 40;
constexpr int kOrtaXp = 60;
constexpr int kIleriXp = 100;
}  // namespace

CodeExerciseManager::CodeExerciseManager() {
    addBeginnerExercises();
    addIntermediateExercises();
    addAdvancedExercises();
}

std::vector<CodeExercise> CodeExerciseManager::exercisesForTier(const std::string& tier) const {
    std::vector<CodeExercise> result;
    for (const CodeExercise& exercise : exercises_) {
        if (exercise.tier == tier) {
            result.push_back(exercise);
        }
    }
    return result;
}

std::optional<CodeExercise> CodeExerciseManager::findById(int id) const {
    for (const CodeExercise& exercise : exercises_) {
        if (exercise.id == id) {
            return exercise;
        }
    }
    return std::nullopt;
}

const std::vector<CodeExercise>& CodeExerciseManager::allExercises() const {
    return exercises_;
}

void CodeExerciseManager::addBeginnerExercises() {
    exercises_.push_back(CodeExercise{
        .id = 1,
        .tier = kBaslangic,
        .title = "Ekrana yazı yazdırma",
        .description = "Ekrana 'Merhaba, C++!' yazan bir program yaz.",
        .expectedBehavior =
            "Program çalıştığında ekrana tam olarak 'Merhaba, C++!' yazmalı.",
        .sampleInput = "(giriş yok)",
        .sampleOutput = "Merhaba, C++!",
        .hints = {"cout kullanmayı hatırla.", "Metni çift tırnak içine al."},
        .requiredKeywords = {"cout", "Merhaba"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    std::cout << \"Merhaba, C++!\";\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "std::endl veya '\\n' ile satır sonu eklemek de kabul edilir; önemli olan "
            "cout ile doğru metni yazdırmaktır.",
        .baseXp = kBaslangicXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 2,
        .tier = kBaslangic,
        .title = "Kullanıcıdan sayı alma",
        .description = "Kullanıcıdan bir tam sayı okuyup ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "Program cin ile bir sayı okumalı ve aynı sayıyı cout ile ekrana yazdırmalı.",
        .sampleInput = "7",
        .sampleOutput = "7",
        .hints = {"cin >> ile okuma yapılır.", "Okunan değişkeni cout ile yazdır."},
        .requiredKeywords = {"cin", ">>", "cout"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int sayi;\n"
            "    std::cin >> sayi;\n"
            "    std::cout << sayi;\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Değişken adı ve tipi (int/double) farklı olabilir; önemli olan cin ile "
            "okuyup cout ile aynı değeri yazdırmaktır.",
        .baseXp = kBaslangicXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 3,
        .tier = kBaslangic,
        .title = "İki sayıyı toplama",
        .description =
            "Kullanıcıdan iki tam sayı alıp toplamlarını ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "İki sayı okunmalı, toplamları hesaplanmalı ve cout ile yazdırılmalı.",
        .sampleInput = "3 5",
        .sampleOutput = "8",
        .hints = {
            "İki değişken tanımla.",
            "cin >> a >> b; şeklinde art arda okuyabilirsin.",
            "Toplamı ayrı bir değişkende tutabilir ya da doğrudan yazdırabilirsin.",
        },
        .requiredKeywords = {"cin", "cout", "+"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int a, b;\n"
            "    std::cin >> a >> b;\n"
            "    std::cout << a + b;\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Toplamı önce bir değişkene atayıp sonra yazdırmak (int toplam = a + b; "
            "cout << toplam;) da eşit derecede doğrudur.",
        .baseXp = kBaslangicXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 4,
        .tier = kBaslangic,
        .title = "Sayının pozitif veya negatif olması",
        .description =
            "Kullanıcıdan bir tam sayı alıp sayının pozitif, negatif ya da sıfır "
            "olduğunu ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "if-else if-else yapısıyla sayının durumu belirlenmeli ve uygun mesaj "
            "yazdırılmalı.",
        .sampleInput = "-4",
        .sampleOutput = "Negatif",
        .hints = {"if, else if ve else kullan.", "Karşılaştırma operatörlerini (> , <) hatırla."},
        .requiredKeywords = {"cin", "if", "else"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int sayi;\n"
            "    std::cin >> sayi;\n"
            "    if (sayi > 0) {\n"
            "        std::cout << \"Pozitif\";\n"
            "    } else if (sayi < 0) {\n"
            "        std::cout << \"Negatif\";\n"
            "    } else {\n"
            "        std::cout << \"Sıfır\";\n"
            "    }\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Üçlü koşul operatörü (?:) ile iç içe yazmak da mümkündür, ancak if-else "
            "yapısı daha okunaklıdır.",
        .baseXp = kBaslangicXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 5,
        .tier = kBaslangic,
        .title = "Çift veya tek sayı",
        .description =
            "Kullanıcıdan bir tam sayı alıp sayının çift mi tek mi olduğunu ekrana "
            "yazdıran bir program yaz.",
        .expectedBehavior =
            "% (mod) operatörü ile sayının 2'ye bölümünden kalan bulunmalı ve sonuca "
            "göre 'Çift' ya da 'Tek' yazdırılmalı.",
        .sampleInput = "6",
        .sampleOutput = "Çift",
        .hints = {"% operatörü kalanı verir.", "sayi % 2 == 0 ise çift demektir."},
        .requiredKeywords = {"cin", "%", "if"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int sayi;\n"
            "    std::cin >> sayi;\n"
            "    if (sayi % 2 == 0) {\n"
            "        std::cout << \"Çift\";\n"
            "    } else {\n"
            "        std::cout << \"Tek\";\n"
            "    }\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Negatif sayılarda da % operatörü C++'ta işaretin sayının işaretini takip "
            "etmesi dışında aynı mantıkla çalışır; bu görev için ekstra bir kontrol "
            "gerekmez.",
        .baseXp = kBaslangicXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 6,
        .tier = kBaslangic,
        .title = "Yaş kontrolü",
        .description =
            "Kullanıcıdan yaşını alıp 18 ve üzeri ise 'Reşitsiniz', değilse 'Reşit "
            "değilsiniz' yazdıran bir program yaz.",
        .expectedBehavior = "if-else ile yaş karşılaştırılmalı ve uygun mesaj yazdırılmalı.",
        .sampleInput = "20",
        .sampleOutput = "Reşitsiniz",
        .hints = {">= operatörünü kullan.", "18 sınır değerinin dahil olduğunu unutma."},
        .requiredKeywords = {"cin", "if", ">="},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int yas;\n"
            "    std::cin >> yas;\n"
            "    if (yas >= 18) {\n"
            "        std::cout << \"Reşitsiniz\";\n"
            "    } else {\n"
            "        std::cout << \"Reşit değilsiniz\";\n"
            "    }\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "!(yas < 18) şeklinde ters bir koşul yazmak da mantıksal olarak eşdeğerdir.",
        .baseXp = kBaslangicXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 7,
        .tier = kBaslangic,
        .title = "Basit hesap makinesi",
        .description =
            "Kullanıcıdan iki sayı ve bir işlem karakteri (+, -, *, /) alıp sonucu "
            "ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "switch-case veya if-else ile işlem karakterine göre doğru işlem yapılmalı "
            "ve sonuç yazdırılmalı.",
        .sampleInput = "6 3 +",
        .sampleOutput = "9",
        .hints = {
            "char tipiyle işlemi oku.",
            "switch-case ile her işlemi ayrı ele alabilirsin.",
            "Sıfıra bölme durumunu düşünmene gerek yok, sadece temel işlemi yap.",
        },
        .requiredKeywords = {"cin", "switch", "cout"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    double a, b;\n"
            "    char islem;\n"
            "    std::cin >> a >> b >> islem;\n"
            "    double sonuc = 0;\n"
            "    switch (islem) {\n"
            "        case '+':\n"
            "            sonuc = a + b;\n"
            "            break;\n"
            "        case '-':\n"
            "            sonuc = a - b;\n"
            "            break;\n"
            "        case '*':\n"
            "            sonuc = a * b;\n"
            "            break;\n"
            "        case '/':\n"
            "            sonuc = a / b;\n"
            "            break;\n"
            "    }\n"
            "    std::cout << sonuc;\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "switch yerine if-else if zinciriyle de aynı sonuç elde edilebilir.",
        .baseXp = kBaslangicXp,
    });
}

void CodeExerciseManager::addIntermediateExercises() {
    exercises_.push_back(CodeExercise{
        .id = 8,
        .tier = kOrta,
        .title = "Not ortalaması",
        .description = "Kullanıcıdan 3 not alıp ortalamasını ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "3 not okunmalı, toplamı 3'e bölünerek ortalama hesaplanmalı ve yazdırılmalı.",
        .sampleInput = "70 80 90",
        .sampleOutput = "80",
        .hints = {"Ortalama = toplam / adet.", "Ondalıklı sonuç için double kullanmayı düşün."},
        .requiredKeywords = {"cin", "cout", "/"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    double n1, n2, n3;\n"
            "    std::cin >> n1 >> n2 >> n3;\n"
            "    double ortalama = (n1 + n2 + n3) / 3;\n"
            "    std::cout << ortalama;\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Notları bir dizide/vector'de tutup döngüyle toplamak da geçerli bir "
            "yaklaşımdır.",
        .baseXp = kOrtaXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 9,
        .tier = kOrta,
        .title = "En büyük sayıyı bulma",
        .description = "Kullanıcıdan 3 sayı alıp en büyüğünü ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "if-else karşılaştırmalarıyla üç sayı arasından en büyüğü bulunmalı ve "
            "yazdırılmalı.",
        .sampleInput = "4 9 2",
        .sampleOutput = "9",
        .hints = {
            "İlk sayıyı 'en büyük' kabul edip diğerleriyle karşılaştırabilirsin.",
            "if-else if zinciri kullanabilirsin.",
        },
        .requiredKeywords = {"cin", "if", "cout"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int a, b, c;\n"
            "    std::cin >> a >> b >> c;\n"
            "    int enBuyuk = a;\n"
            "    if (b > enBuyuk) {\n"
            "        enBuyuk = b;\n"
            "    }\n"
            "    if (c > enBuyuk) {\n"
            "        enBuyuk = c;\n"
            "    }\n"
            "    std::cout << enBuyuk;\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "std::max(a, std::max(b, c)) kullanmak da geçerlidir ancak <algorithm> "
            "eklenmesi gerekir.",
        .baseXp = kOrtaXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 10,
        .tier = kOrta,
        .title = "Faktöriyel",
        .description =
            "Kullanıcıdan bir sayı alıp faktöriyelini hesaplayıp ekrana yazdıran bir "
            "program yaz.",
        .expectedBehavior =
            "for veya while döngüsüyle 1'den sayıya kadar çarpılarak faktöriyel "
            "hesaplanmalı.",
        .sampleInput = "5",
        .sampleOutput = "120",
        .hints = {
            "Sonuç değişkenini 1 ile başlat.",
            "for (int i = 1; i <= sayi; i++) döngüsüyle çarpabilirsin.",
        },
        .requiredKeywords = {"cin", "for", "*="},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int sayi;\n"
            "    std::cin >> sayi;\n"
            "    long long sonuc = 1;\n"
            "    for (int i = 1; i <= sayi; i++) {\n"
            "        sonuc *= i;\n"
            "    }\n"
            "    std::cout << sonuc;\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "while döngüsüyle de aynı işlem yapılabilir; büyük sayılar için long long "
            "kullanmak taşmayı önler.",
        .baseXp = kOrtaXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 11,
        .tier = kOrta,
        .title = "Asal sayı kontrolü",
        .description =
            "Kullanıcıdan bir sayı alıp asal olup olmadığını ekrana yazdıran bir "
            "program yaz.",
        .expectedBehavior =
            "2'den sayının kareköküne (veya sayı-1'e) kadar bölünüp bölünmediği "
            "kontrol edilerek asallık belirlenmeli.",
        .sampleInput = "7",
        .sampleOutput = "Asal",
        .hints = {
            "Bir sayı sadece 1'e ve kendisine bölünüyorsa asaldır.",
            "for döngüsüyle 2'den sayı-1'e kadar bölünebilirliği kontrol et.",
            "% operatörüyle kalan sıfırsa bölünüyor demektir.",
        },
        .requiredKeywords = {"cin", "for", "%"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int sayi;\n"
            "    std::cin >> sayi;\n"
            "    bool asalMi = sayi > 1;\n"
            "    for (int i = 2; i < sayi; i++) {\n"
            "        if (sayi % i == 0) {\n"
            "            asalMi = false;\n"
            "            break;\n"
            "        }\n"
            "    }\n"
            "    std::cout << (asalMi ? \"Asal\" : \"Asal değil\");\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Döngüyü sayının kareköküne kadar sınırlamak (i * i <= sayi) daha "
            "verimlidir ama bu görev için gerekli değildir.",
        .baseXp = kOrtaXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 12,
        .tier = kOrta,
        .title = "Dizi toplamı",
        .description =
            "Kullanıcıdan 5 elemanlı bir tam sayı dizisi alıp elemanların toplamını "
            "ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "Dizi bir döngüyle okunmalı, toplam yine bir döngüyle hesaplanıp "
            "yazdırılmalı.",
        .sampleInput = "1 2 3 4 5",
        .sampleOutput = "15",
        .hints = {
            "int dizi[5]; şeklinde bir dizi tanımlayabilirsin.",
            "for döngüsüyle her elemanı okuyup toplamına ekleyebilirsin.",
        },
        .requiredKeywords = {"cin", "for", "+="},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int dizi[5];\n"
            "    int toplam = 0;\n"
            "    for (int i = 0; i < 5; i++) {\n"
            "        std::cin >> dizi[i];\n"
            "        toplam += dizi[i];\n"
            "    }\n"
            "    std::cout << toplam;\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "std::array veya std::vector kullanmak da geçerlidir; önemli olan "
            "döngüyle toplama mantığıdır.",
        .baseXp = kOrtaXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 13,
        .tier = kOrta,
        .title = "Dizi ortalaması",
        .description =
            "Kullanıcıdan 5 elemanlı bir dizi alıp elemanların ortalamasını ekrana "
            "yazdıran bir program yaz.",
        .expectedBehavior =
            "Dizi okunmalı, toplam bulunup 5'e bölünerek ortalama hesaplanmalı ve "
            "yazdırılmalı.",
        .sampleInput = "2 4 6 8 10",
        .sampleOutput = "6",
        .hints = {"Önce toplamı bul, sonra eleman sayısına böl.", "Ondalıklı sonuç istiyorsan double kullan."},
        .requiredKeywords = {"cin", "for", "/"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    double dizi[5];\n"
            "    double toplam = 0;\n"
            "    for (int i = 0; i < 5; i++) {\n"
            "        std::cin >> dizi[i];\n"
            "        toplam += dizi[i];\n"
            "    }\n"
            "    std::cout << toplam / 5;\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "int dizi kullanılıp sonuç hesaplanırken (double) dönüşümü yapılması da "
            "geçerlidir.",
        .baseXp = kOrtaXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 14,
        .tier = kOrta,
        .title = "String içinde karakter arama",
        .description =
            "Kullanıcıdan bir kelime alıp içinde belirli bir harfin (örneğin 'a') "
            "geçip geçmediğini ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "std::string'in find() fonksiyonuyla karakterin varlığı kontrol edilmeli "
            "ve sonuca göre mesaj yazdırılmalı.",
        .sampleInput = "kalem",
        .sampleOutput = "Bulundu",
        .hints = {"find() bulunamazsa std::string::npos döner.", "cin >> ile kelimeyi okuyabilirsin."},
        .requiredKeywords = {"cin", "find", "cout"},
        .sampleSolution =
            "#include <iostream>\n"
            "#include <string>\n\n"
            "int main() {\n"
            "    std::string kelime;\n"
            "    std::cin >> kelime;\n"
            "    if (kelime.find('a') != std::string::npos) {\n"
            "        std::cout << \"Bulundu\";\n"
            "    } else {\n"
            "        std::cout << \"Bulunamadı\";\n"
            "    }\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Harfi bir döngüyle tek tek kontrol etmek de (find() kullanmadan) geçerli "
            "bir alternatiftir.",
        .baseXp = kOrtaXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 15,
        .tier = kOrta,
        .title = "Menü uygulaması",
        .description =
            "Kullanıcıya 1) Topla 2) Çıkar 3) Çık şeklinde bir menü gösterip seçime "
            "göre iki sayı üzerinde işlem yapan bir program yaz.",
        .expectedBehavior =
            "switch veya if-else ile menü seçimine göre doğru işlem yapılmalı ve "
            "sonuç yazdırılmalı.",
        .sampleInput = "1 10 4",
        .sampleOutput = "14",
        .hints = {
            "Önce menü seçimini, sonra iki sayıyı oku.",
            "switch-case ile her seçeneği ayrı ele alabilirsin.",
        },
        .requiredKeywords = {"cin", "switch", "cout"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "int main() {\n"
            "    int secim, a, b;\n"
            "    std::cin >> secim >> a >> b;\n"
            "    switch (secim) {\n"
            "        case 1:\n"
            "            std::cout << a + b;\n"
            "            break;\n"
            "        case 2:\n"
            "            std::cout << a - b;\n"
            "            break;\n"
            "        default:\n"
            "            break;\n"
            "    }\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Menü metnini ayrıca ekrana yazdırmak isteğe bağlıdır; bu görevde asıl "
            "aranan doğru işlemi seçip sonucu yazdırmaktır.",
        .baseXp = kOrtaXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 16,
        .tier = kOrta,
        .title = "Fonksiyon kullanarak hesap makinesi",
        .description =
            "İki sayıyı ve bir işlem karakterini parametre olarak alan bir fonksiyonla "
            "hesap makinesi yaz.",
        .expectedBehavior =
            "İşlemi yapan ayrı bir fonksiyon tanımlanmalı; main içinde bu fonksiyon "
            "çağrılıp sonucu yazdırılmalı.",
        .sampleInput = "8 2 /",
        .sampleOutput = "4",
        .hints = {
            "double hesapla(double a, double b, char islem) gibi bir fonksiyon imzası "
            "düşünebilirsin.",
            "Fonksiyonun içinde switch-case veya if-else kullanabilirsin.",
        },
        .requiredKeywords = {"cin", "cout", "double"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "double hesapla(double a, double b, char islem) {\n"
            "    if (islem == '+') return a + b;\n"
            "    if (islem == '-') return a - b;\n"
            "    if (islem == '*') return a * b;\n"
            "    return a / b;\n"
            "}\n\n"
            "int main() {\n"
            "    double a, b;\n"
            "    char islem;\n"
            "    std::cin >> a >> b >> islem;\n"
            "    std::cout << hesapla(a, b, islem);\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Fonksiyonun void olup sonucu referansla döndürmesi de geçerli bir "
            "tasarımdır; önemli olan işlemin ayrı bir fonksiyonda yapılmasıdır.",
        .baseXp = kOrtaXp,
    });
}

void CodeExerciseManager::addAdvancedExercises() {
    exercises_.push_back(CodeExercise{
        .id = 17,
        .tier = kIleri,
        .title = "Öğrenci kayıt sistemi",
        .description =
            "Öğrencinin adını ve notunu tutan bir struct tanımlayıp kullanıcıdan "
            "bilgileri okuyup ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "Öğrenci bilgilerini tutan bir struct olmalı; kullanıcıdan ad ve not "
            "okunup ekrana yazdırılmalı.",
        .sampleInput = "Ayşe 85",
        .sampleOutput = "Ayşe: 85",
        .hints = {
            "struct Ogrenci { std::string ad; int notu; }; gibi bir yapı "
            "tanımlayabilirsin.",
            "cin >> ile ad ve notu oku, sonra cout ile birlikte yazdır.",
        },
        .requiredKeywords = {"struct", "cin", "cout"},
        .sampleSolution =
            "#include <iostream>\n"
            "#include <string>\n\n"
            "struct Ogrenci {\n"
            "    std::string ad;\n"
            "    int notu;\n"
            "};\n\n"
            "int main() {\n"
            "    Ogrenci ogrenci;\n"
            "    std::cin >> ogrenci.ad >> ogrenci.notu;\n"
            "    std::cout << ogrenci.ad << \": \" << ogrenci.notu;\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote = "struct yerine class kullanıp alanları public yapmak da eşdeğerdir.",
        .baseXp = kIleriXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 18,
        .tier = kIleri,
        .title = "Banka hesabı sınıfı",
        .description =
            "Bakiyeyi tutan, para yatırma ve çekme işlemlerini yapan bir BankaHesabi "
            "sınıfı yaz.",
        .expectedBehavior =
            "class içinde bakiye private olmalı; yatir() ve cek() gibi public "
            "metotlarla bakiye değiştirilip ekrana yazdırılmalı.",
        .sampleInput = "100 50 -30",
        .sampleOutput = "120",
        .hints = {
            "Bakiyeyi private yap, dışarıdan sadece metotlarla değiştirilsin.",
            "yatir(miktar) bakiyeyi artırsın, cek(miktar) azaltsın.",
        },
        .requiredKeywords = {"class", "private", "cout"},
        .sampleSolution =
            "#include <iostream>\n\n"
            "class BankaHesabi {\n"
            "public:\n"
            "    BankaHesabi(double baslangic) : bakiye(baslangic) {}\n"
            "    void yatir(double miktar) { bakiye += miktar; }\n"
            "    void cek(double miktar) { bakiye -= miktar; }\n"
            "    double bakiyeGetir() const { return bakiye; }\n\n"
            "private:\n"
            "    double bakiye;\n"
            "};\n\n"
            "int main() {\n"
            "    double baslangic, yatirilan, cekilen;\n"
            "    std::cin >> baslangic >> yatirilan >> cekilen;\n"
            "    BankaHesabi hesap(baslangic);\n"
            "    hesap.yatir(yatirilan);\n"
            "    hesap.cek(-cekilen);\n"
            "    std::cout << hesap.bakiyeGetir();\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Yetersiz bakiyede çekim yapılmasını engelleyen bir kontrol eklemek "
            "isteğe bağlı bir geliştirmedir.",
        .baseXp = kIleriXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 19,
        .tier = kIleri,
        .title = "Kalıtım kullanan çalışan sistemi",
        .description =
            "Temel bir Calisan sınıfından türeyen bir Yonetici sınıfı yaz; Yonetici ek "
            "olarak bir ekip büyüklüğü bilgisi tutsun.",
        .expectedBehavior =
            "Calisan sınıfı ad ve maaş tutmalı; Yonetici bundan public kalıtımla "
            "türemeli ve ekip büyüklüğünü de yazdırabilmeli.",
        .sampleInput = "Mehmet 15000 5",
        .sampleOutput = "Mehmet, Maaş: 15000, Ekip: 5",
        .hints = {
            "class Yonetici : public Calisan { ... }; şeklinde kalıtım kurulur.",
            "Temel sınıfın alanlarına türeyen sınıftan erişebilmek için protected "
            "kullanabilirsin.",
        },
        .requiredKeywords = {"class", ":", "public"},
        .sampleSolution =
            "#include <iostream>\n"
            "#include <string>\n\n"
            "class Calisan {\n"
            "protected:\n"
            "    std::string ad;\n"
            "    double maas;\n\n"
            "public:\n"
            "    Calisan(std::string adGiris, double maasGiris) : ad(adGiris), maas(maasGiris) {}\n"
            "};\n\n"
            "class Yonetici : public Calisan {\n"
            "public:\n"
            "    Yonetici(std::string adGiris, double maasGiris, int ekipGiris)\n"
            "        : Calisan(adGiris, maasGiris), ekipBuyuklugu(ekipGiris) {}\n\n"
            "    void yazdir() const {\n"
            "        std::cout << ad << \", Maaş: \" << maas << \", Ekip: \" << ekipBuyuklugu;\n"
            "    }\n\n"
            "private:\n"
            "    int ekipBuyuklugu;\n"
            "};\n\n"
            "int main() {\n"
            "    std::string ad;\n"
            "    double maas;\n"
            "    int ekip;\n"
            "    std::cin >> ad >> maas >> ekip;\n"
            "    Yonetici yonetici(ad, maas, ekip);\n"
            "    yonetici.yazdir();\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Temel sınıfın alanlarını private yapıp getter metotlarıyla erişmek de "
            "kabul edilebilir bir tasarımdır.",
        .baseXp = kIleriXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 20,
        .tier = kIleri,
        .title = "Polimorfik hayvan sınıfları",
        .description =
            "Ortak bir Hayvan taban sınıfından türeyen Kedi ve Kopek sınıfları yaz; "
            "her biri sanal bir ses() metodunu kendine göre uygulasın.",
        .expectedBehavior =
            "Hayvan sınıfında virtual bir ses() metodu olmalı; Kedi ve Kopek bunu "
            "override etmeli; taban sınıf pointer'ı üzerinden çağrıldığında doğru ses "
            "yazdırılmalı (polimorfizm).",
        .sampleInput = "kedi",
        .sampleOutput = "Miyav",
        .hints = {
            "virtual void ses() const; taban sınıfta tanımlanır.",
            "Türeyen sınıflarda override ile ses() yeniden yazılır.",
            "Hayvan* pointer'ı ile hangi nesneye işaret ettiğine bakılmaksızın doğru "
            "ses() çağrılır.",
        },
        .requiredKeywords = {"virtual", "override", "cout"},
        .sampleSolution =
            "#include <iostream>\n"
            "#include <string>\n\n"
            "class Hayvan {\n"
            "public:\n"
            "    virtual void ses() const { std::cout << \"...\"; }\n"
            "    virtual ~Hayvan() = default;\n"
            "};\n\n"
            "class Kedi : public Hayvan {\n"
            "public:\n"
            "    void ses() const override { std::cout << \"Miyav\"; }\n"
            "};\n\n"
            "class Kopek : public Hayvan {\n"
            "public:\n"
            "    void ses() const override { std::cout << \"Hav\"; }\n"
            "};\n\n"
            "int main() {\n"
            "    std::string tur;\n"
            "    std::cin >> tur;\n"
            "    Kedi kedi;\n"
            "    Kopek kopek;\n"
            "    Hayvan* hayvan = (tur == \"kedi\") ? static_cast<Hayvan*>(&kedi)\n"
            "                                       : static_cast<Hayvan*>(&kopek);\n"
            "    hayvan->ses();\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Nesneleri std::unique_ptr<Hayvan> ile dinamik oluşturmak da geçerli bir "
            "alternatiftir.",
        .baseXp = kIleriXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 21,
        .tier = kIleri,
        .title = "map kullanan telefon rehberi",
        .description =
            "İsim-telefon numarası eşlemesini bir std::map<std::string, std::string> "
            "içinde tutan ve verilen isme ait numarayı yazdıran bir program yaz.",
        .expectedBehavior =
            "map'e birkaç kayıt eklenmeli; kullanıcıdan okunan isme karşılık gelen "
            "numara ekrana yazdırılmalı.",
        .sampleInput = "Ali",
        .sampleOutput = "0555 111 22 33",
        .hints = {
            "std::map<std::string, std::string> rehber; ile tanımlarsın.",
            "rehber[\"Ali\"] = \"...\"; şeklinde ekleme yapılır.",
            "map'te olmayan bir isim için de bir kontrol düşünebilirsin.",
        },
        .requiredKeywords = {"map", "cin", "cout"},
        .sampleSolution =
            "#include <iostream>\n"
            "#include <map>\n"
            "#include <string>\n\n"
            "int main() {\n"
            "    std::map<std::string, std::string> rehber;\n"
            "    rehber[\"Ali\"] = \"0555 111 22 33\";\n"
            "    rehber[\"Ayşe\"] = \"0555 444 55 66\";\n\n"
            "    std::string isim;\n"
            "    std::cin >> isim;\n\n"
            "    if (rehber.find(isim) != rehber.end()) {\n"
            "        std::cout << rehber[isim];\n"
            "    } else {\n"
            "        std::cout << \"Kayıt bulunamadı\";\n"
            "    }\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "unordered_map kullanmak da işlevsel olarak eşdeğerdir; sadece sıralama "
            "garantisi olmaz.",
        .baseXp = kIleriXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 22,
        .tier = kIleri,
        .title = "vector kullanan görev listesi",
        .description =
            "Kullanıcıdan önce görev sayısını, sonra o kadar görevi satır satır "
            "okuyup bir std::vector<std::string> içinde tutan ve hepsini "
            "numaralandırarak ekrana yazdıran bir program yaz.",
        .expectedBehavior =
            "Önce görev sayısı okunmalı; sonra o kadar görev bir döngüyle vector'e "
            "eklenmeli (push_back); son olarak başka bir döngüyle numaralandırılarak "
            "yazdırılmalı.",
        .sampleInput = "2\nDers çalış\nSpor yap",
        .sampleOutput = "1. Ders çalış\n2. Spor yap",
        .hints = {
            "Önce görev sayısını oku.",
            "std::vector<std::string> gorevler; ile başlarsın.",
            "getline ile okuduğun her görevi gorevler.push_back(gorev); ile ekleyip "
            "for döngüsüyle index'i kullanarak numaralandırabilirsin.",
        },
        .requiredKeywords = {"vector", "push_back", "for"},
        .sampleSolution =
            "#include <iostream>\n"
            "#include <string>\n"
            "#include <vector>\n\n"
            "int main() {\n"
            "    int sayi;\n"
            "    std::cin >> sayi;\n"
            "    std::cin.ignore();\n\n"
            "    std::vector<std::string> gorevler;\n"
            "    for (int i = 0; i < sayi; i++) {\n"
            "        std::string gorev;\n"
            "        std::getline(std::cin, gorev);\n"
            "        gorevler.push_back(gorev);\n"
            "    }\n\n"
            "    for (std::size_t i = 0; i < gorevler.size(); i++) {\n"
            "        std::cout << (i + 1) << \". \" << gorevler[i] << \"\\n\";\n"
            "    }\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "Görev sayısını sormak yerine kullanıcı boş satır girene kadar okumak da "
            "(while (std::getline(std::cin, gorev) && !gorev.empty())) geçerli bir "
            "alternatiftir.",
        .baseXp = kIleriXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 23,
        .tier = kIleri,
        .title = "Dosyaya kayıt yapan not uygulaması",
        .description =
            "Kullanıcıdan bir not metni alıp bunu bir dosyaya (not.txt) yazan bir "
            "program yaz.",
        .expectedBehavior =
            "std::ofstream ile bir dosya açılmalı, kullanıcıdan okunan metin dosyaya "
            "yazılmalı ve dosya kapatılmalı.",
        .sampleInput = "Yarın toplantı var",
        .sampleOutput = "(not.txt dosyasına yazıldı)",
        .hints = {
            "std::ofstream dosya(\"not.txt\"); ile dosya açılır.",
            "dosya << metin; ile içerik yazılır.",
            "İşin bitince dosya.close(); çağırmayı unutma.",
        },
        .requiredKeywords = {"ofstream", "cin", "<<"},
        .sampleSolution =
            "#include <iostream>\n"
            "#include <fstream>\n"
            "#include <string>\n\n"
            "int main() {\n"
            "    std::string metin;\n"
            "    std::getline(std::cin, metin);\n\n"
            "    std::ofstream dosya(\"not.txt\");\n"
            "    dosya << metin;\n"
            "    dosya.close();\n\n"
            "    std::cout << \"Kaydedildi.\";\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "dosya.close() çağrılmasa da ofstream nesnesi kapsam dışına çıktığında "
            "dosya otomatik olarak kapanır; açıkça kapatmak sadece iyi bir "
            "alışkanlıktır.",
        .baseXp = kIleriXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 24,
        .tier = kIleri,
        .title = "try-catch kullanan güvenli giriş sistemi",
        .description =
            "Kullanıcıdan bir sayı okuyup, sayı sıfırsa bir istisna (exception) "
            "fırlatıp bunu yakalayan bir program yaz.",
        .expectedBehavior =
            "Sıfır durumunda throw ile bir istisna fırlatılmalı; main içinde try-catch "
            "ile yakalanıp uygun mesaj yazdırılmalı.",
        .sampleInput = "0",
        .sampleOutput = "Hata: sıfır olamaz",
        .hints = {
            "throw std::invalid_argument(\"...\"); ile istisna fırlatabilirsin.",
            "try { ... } catch (const std::exception& e) { ... } ile yakalarsın.",
        },
        .requiredKeywords = {"try", "catch", "throw"},
        .sampleSolution =
            "#include <iostream>\n"
            "#include <stdexcept>\n\n"
            "int main() {\n"
            "    int sayi;\n"
            "    std::cin >> sayi;\n"
            "    try {\n"
            "        if (sayi == 0) {\n"
            "            throw std::invalid_argument(\"sıfır olamaz\");\n"
            "        }\n"
            "        std::cout << 100 / sayi;\n"
            "    } catch (const std::exception& hata) {\n"
            "        std::cout << \"Hata: \" << hata.what();\n"
            "    }\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "throw ile kendi tanımladığın bir sınıf fırlatmak da geçerlidir; önemli "
            "olan try-catch ile hatanın yakalanmasıdır.",
        .baseXp = kIleriXp,
    });
    exercises_.push_back(CodeExercise{
        .id = 25,
        .tier = kIleri,
        .title = "unique_ptr kullanan nesne yönetimi",
        .description =
            "Bir sınıfın nesnesini std::unique_ptr ile dinamik olarak oluşturup "
            "kullanan, bellek yönetimini akıllı pointer'a bırakan bir program yaz.",
        .expectedBehavior =
            "new/delete yerine std::make_unique ile bir nesne oluşturulmalı, nesnenin "
            "bir metodu çağrılmalı; unique_ptr kapsam dışına çıktığında bellek "
            "otomatik serbest bırakılmalı.",
        .sampleInput = "(giriş yok)",
        .sampleOutput = "Merhaba, unique_ptr!",
        .hints = {
            "std::unique_ptr<Sinif> ptr = std::make_unique<Sinif>(...); ile "
            "oluşturursun.",
            "ptr->metot(); ile nesnenin metodunu çağırabilirsin.",
            "delete çağırmana gerek yok; unique_ptr kapsam dışına çıkınca otomatik "
            "serbest bırakır.",
        },
        .requiredKeywords = {"unique_ptr", "make_unique", "->"},
        .sampleSolution =
            "#include <iostream>\n"
            "#include <memory>\n\n"
            "class Mesaj {\n"
            "public:\n"
            "    void goster() const { std::cout << \"Merhaba, unique_ptr!\"; }\n"
            "};\n\n"
            "int main() {\n"
            "    std::unique_ptr<Mesaj> ptr = std::make_unique<Mesaj>();\n"
            "    ptr->goster();\n"
            "    return 0;\n"
            "}",
        .alternativeSolutionNote =
            "auto ptr = std::make_unique<Mesaj>(); ile tip çıkarımı kullanmak da "
            "geçerlidir.",
        .baseXp = kIleriXp,
    });
}
```

- [ ] **Step 4: Create `tests/CodeExerciseManagerTests.cpp`**

```cpp
#include "CodeExerciseManager.h"

#include "TestRunner.h"

TEST_CASE(CodeExerciseManager_HasExactlyTwentyFiveExercises) {
    CodeExerciseManager manager;
    CHECK(manager.allExercises().size() == 25);
}

TEST_CASE(CodeExerciseManager_TierCountsMatchBrief) {
    CodeExerciseManager manager;
    CHECK(manager.exercisesForTier("Başlangıç").size() == 7);
    CHECK(manager.exercisesForTier("Orta").size() == 9);
    CHECK(manager.exercisesForTier("İleri").size() == 9);
}

TEST_CASE(CodeExerciseManager_AllIdsAreUnique) {
    CodeExerciseManager manager;
    std::unordered_set<int> seenIds;
    bool foundDuplicate = false;
    for (const CodeExercise& exercise : manager.allExercises()) {
        if (!seenIds.insert(exercise.id).second) {
            foundDuplicate = true;
        }
    }
    CHECK(!foundDuplicate);
}

TEST_CASE(CodeExerciseManager_FindByIdResolvesEveryExercise) {
    CodeExerciseManager manager;
    for (int id = 1; id <= 25; ++id) {
        CHECK(manager.findById(id).has_value());
    }
    CHECK(!manager.findById(26).has_value());
    CHECK(!manager.findById(0).has_value());
}

TEST_CASE(CodeExerciseManager_EveryExerciseHasCompleteContent) {
    CodeExerciseManager manager;
    for (const CodeExercise& exercise : manager.allExercises()) {
        CHECK(!exercise.title.empty());
        CHECK(!exercise.description.empty());
        CHECK(!exercise.expectedBehavior.empty());
        CHECK(!exercise.sampleInput.empty());
        CHECK(!exercise.sampleOutput.empty());
        CHECK(!exercise.hints.empty());
        CHECK(!exercise.requiredKeywords.empty());
        CHECK(!exercise.sampleSolution.empty());
        CHECK(!exercise.alternativeSolutionNote.empty());
        CHECK(exercise.baseXp > 0);
    }
}
```

Add `#include <unordered_set>` to this file's includes (alongside
`"CodeExerciseManager.h"` and `"TestRunner.h"`).

- [ ] **Step 5: Add the new files to `CMakeLists.txt`**

Add `src/CodeExercise.h`, `src/CodeExerciseManager.h`,
`src/CodeExerciseManager.cpp` to `CppMasterConsoleLib`'s source list, and
`tests/CodeExerciseManagerTests.cpp` to `CppMasterConsoleTests`'s source
list.

- [ ] **Step 6: Build and run**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
./build/Debug/CppMasterConsoleTests.exe
```
Expected: `81/81 test(s) passed.` (76 from Phase 10 + 5 new
`CodeExerciseManager` tests). Zero warnings.

- [ ] **Step 7: Commit**

```bash
git add CMakeLists.txt src/CodeExercise.h src/CodeExerciseManager.h src/CodeExerciseManager.cpp tests/CodeExerciseManagerTests.cpp
git commit -m "Add CodeExercise data model and all 25 hand-authored exercises"
```

---

### Task 2: Convert `CodeExercise` to a gradable `WriteCode` `Question`

**Files:**
- Modify: `src/CodeExercise.h`
- Create: `tests/CodeExerciseTests.cpp`
- Modify: `CMakeLists.txt`

**Interfaces:**
- Consumes: `CodeExercise` (Task 1), `Question`/`QuestionType` (`src/Question.h`, `src/Enums.h`, unchanged), `QuizEngine::evaluate` (`src/QuizEngine.h`, unchanged).
- Produces: `Question toWriteCodeQuestion(const CodeExercise& exercise)` — Task 3's `Application` uses this exact name.

- [ ] **Step 1: Modify `src/CodeExercise.h`** — add the conversion function
  at the end of the file (after the `CodeExercise` struct definition):

```cpp
#pragma once

#include <string>
#include <vector>

#include "Question.h"

struct CodeExercise {
    int id = 0;
    std::string tier;
    std::string title;
    std::string description;
    std::string expectedBehavior;
    std::string sampleInput;
    std::string sampleOutput;
    std::vector<std::string> hints;
    std::vector<std::string> requiredKeywords;
    std::string sampleSolution;
    std::string alternativeSolutionNote;
    int baseXp = 0;
};

[[nodiscard]] inline Question toWriteCodeQuestion(const CodeExercise& exercise) {
    Question question;
    question.id = exercise.id;
    question.type = QuestionType::WriteCode;
    question.acceptedAnswers = exercise.requiredKeywords;
    question.baseXp = exercise.baseXp;
    question.explanation = exercise.alternativeSolutionNote;
    return question;
}
```

(This adds `#include "Question.h"` and the new function; the `CodeExercise`
struct itself is unchanged from Task 1.)

- [ ] **Step 2: Create `tests/CodeExerciseTests.cpp`**

```cpp
#include "CodeExercise.h"

#include "CodeExerciseManager.h"
#include "QuizEngine.h"
#include "TestRunner.h"

TEST_CASE(CodeExercise_ToWriteCodeQuestionCarriesRequiredFields) {
    CodeExerciseManager manager;
    const auto exercise = manager.findById(1);
    CHECK(exercise.has_value());

    const Question question = toWriteCodeQuestion(*exercise);
    CHECK(question.id == exercise->id);
    CHECK(question.type == QuestionType::WriteCode);
    CHECK(question.acceptedAnswers == exercise->requiredKeywords);
    CHECK(question.baseXp == exercise->baseXp);
    CHECK(question.explanation == exercise->alternativeSolutionNote);
}

TEST_CASE(CodeExercise_EverySampleSolutionPassesItsOwnRequiredKeywords) {
    CodeExerciseManager manager;
    QuizEngine engine;
    for (const CodeExercise& exercise : manager.allExercises()) {
        const Question question = toWriteCodeQuestion(exercise);
        const AnswerResult result = engine.evaluate(question, exercise.sampleSolution);
        CHECK(result.correct);
    }
}
```

- [ ] **Step 3: Add the new file to `CMakeLists.txt`**

Add `tests/CodeExerciseTests.cpp` to `CppMasterConsoleTests`'s source list.

- [ ] **Step 4: Build and run**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
./build/Debug/CppMasterConsoleTests.exe
```
Expected: `83/83 test(s) passed.` (81 from Task 1 + 2 new). Zero warnings.

**If `CodeExercise_EverySampleSolutionPassesItsOwnRequiredKeywords` fails**
for a specific exercise, the failure is a real, valuable signal: either
that exercise's `sampleSolution` has unbalanced parentheses/braces, or it's
missing one of its own `requiredKeywords` as a literal substring. Fix the
specific exercise's `sampleSolution` or `requiredKeywords` in
`src/CodeExerciseManager.cpp` (from Task 1) to make them consistent — do
not weaken this test.

- [ ] **Step 5: Commit**

```bash
git add src/CodeExercise.h tests/CodeExerciseTests.cpp CMakeLists.txt
git commit -m "Add CodeExercise-to-WriteCode-Question conversion, reusing QuizEngine's existing grading logic"
```

---

### Task 3: Wire the Code Exercises mode into `Application`, manual verification

**Files:**
- Modify: `src/Application.h`
- Modify: `src/Application.cpp`

**Interfaces:**
- Consumes: `CodeExerciseManager`/`CodeExercise`/`toWriteCodeQuestion` (Tasks 1-2).
- Produces: nothing consumed by later tasks — final task of this phase.

- [ ] **Step 1: Modify `src/Application.h`**

Add `#include "CodeExerciseManager.h"` to the include block (alongside
`#include "AchievementTracker.h"`), add a `CodeExerciseManager codeExercises_;`
member (alongside `AchievementTracker achievements_;`), and add three new
private method declarations right after `runSectionExam`:
```cpp
    void runCodeExercises();
    void runCodeExerciseTier(const std::string& tier);
    void runCodeExercise(const CodeExercise& exercise);
```

- [ ] **Step 2: Modify `src/Application.cpp` — replace the menu-5 stub**

Change (`handleChoice`, case 5):
```cpp
        case 5:
            showNotYetAvailable("Kod Yazma Alıştırmaları");
            break;
```
to:
```cpp
        case 5:
            runCodeExercises();
            break;
```

- [ ] **Step 3: Add the three new methods to `src/Application.cpp`**

Add these anywhere after `runSectionExam` and before `showSettingsMenu` (or
any other consistent location matching the header's declaration order):

```cpp
void Application::runCodeExercises() {
    bool inCodeExercisesMenu = true;
    while (inCodeExercisesMenu) {
        ui_.printLine("");
        ui_.printHeader("KOD YAZMA ALIŞTIRMALARI");
        ui_.printLine("1. Başlangıç");
        ui_.printLine("2. Orta");
        ui_.printLine("3. İleri");
        ui_.printLine("0. Geri dön");
        ui_.printLine("");
        ui_.printLine("Seçiminiz:");

        const int tierChoice = ui_.readMenuChoice(0, 3);
        std::string tier;
        switch (tierChoice) {
            case 1:
                tier = "Başlangıç";
                break;
            case 2:
                tier = "Orta";
                break;
            case 3:
                tier = "İleri";
                break;
            case 0:
                inCodeExercisesMenu = false;
                break;
            default:
                break;
        }
        if (!tier.empty()) {
            runCodeExerciseTier(tier);
        }
    }
}

void Application::runCodeExerciseTier(const std::string& tier) {
    const auto exercises = codeExercises_.exercisesForTier(tier);
    bool inTierMenu = true;
    while (inTierMenu) {
        ui_.printLine("");
        ui_.printHeader(tier + " Alıştırmaları");
        for (const CodeExercise& exercise : exercises) {
            ui_.printLine(std::to_string(exercise.id) + ". " + exercise.title);
        }
        ui_.printLine("0. Geri dön");
        ui_.printLine("");
        ui_.printLine("Alıştırma numarasını girin:");

        const int choice = ui_.readMenuChoice(0, 100);
        if (choice == 0) {
            inTierMenu = false;
            continue;
        }
        const auto exercise = codeExercises_.findById(choice);
        if (!exercise.has_value() || exercise->tier != tier) {
            ui_.printLine("Geçersiz alıştırma numarası.");
            continue;
        }
        runCodeExercise(*exercise);
    }
}

void Application::runCodeExercise(const CodeExercise& exercise) {
    ui_.printLine("");
    ui_.printHeader(std::to_string(exercise.id) + ". " + exercise.title);
    ui_.printLine(exercise.description);
    ui_.printLine("");
    ui_.printLine("Beklenen davranış:");
    ui_.printLine(exercise.expectedBehavior);
    ui_.printLine("");
    ui_.printLine("Örnek giriş: " + exercise.sampleInput);
    ui_.printLine("Örnek çıktı: " + exercise.sampleOutput);
    ui_.printLine("");

    int hintLevelUsed = 0;
    ui_.printLine("Başlamadan önce ipucu görmek ister misiniz? (E/H)");
    while (true) {
        const std::string wantsHint = ui_.readLine("Cevabınız: ");
        if (wantsHint != "E" && wantsHint != "e") {
            break;
        }
        if (hintLevelUsed < static_cast<int>(exercise.hints.size())) {
            ui_.printLine(exercise.hints[static_cast<std::size_t>(hintLevelUsed)]);
            ++hintLevelUsed;
        } else if (!exercise.hints.empty()) {
            ui_.printLine(exercise.hints.back());
        }
        ui_.printLine("Başka bir ipucu görmek ister misiniz? (E/H)");
    }

    ui_.printLine(
        "Kodunuzu birden fazla satır halinde girebilirsiniz. Bitirmek için BITIR yazıp Enter'a basın.");
    const std::string submittedCode = ui_.readMultilineCode();

    const Question question = toWriteCodeQuestion(exercise);
    const AnswerResult result = quizEngine_.evaluate(question, submittedCode, settings_);

    int xpAwarded = result.xpAwarded;
    if (result.correct && hintLevelUsed > 0) {
        const int cappedHintLevel = hintLevelUsed < 3 ? hintLevelUsed : 3;
        const double multiplier = 1.0 - (0.25 * static_cast<double>(cappedHintLevel));
        xpAwarded = static_cast<int>(static_cast<double>(xpAwarded) * multiplier);
    }

    ui_.printLine("");
    if (result.correct) {
        ui_.printLine("Doğru! (+" + std::to_string(xpAwarded) + " XP)");
        awardXpAndCheckLevelUp(xpAwarded);
    } else {
        ui_.printLine("Gönderdiğiniz kod beklenen kriterleri karşılamıyor.");
    }

    ui_.printLine("");
    ui_.printLine("Örnek çözüm:");
    ui_.printLine(exercise.sampleSolution);
    ui_.printLine("");
    ui_.printLine("Alternatif çözüm notu:");
    ui_.printLine(exercise.alternativeSolutionNote);
    ui_.printLine("");

    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
}
```

- [ ] **Step 4: Build**

```bash
"C:/Program Files/CMake/bin/cmake.exe" --build build
```
Expected: zero warnings.

- [ ] **Step 5: Run the full test suite**

```bash
./build/Debug/CppMasterConsoleTests.exe
cd build && ctest -C Debug --output-on-failure && cd ..
```
Expected: `83/83 test(s) passed.`, `ctest` 100%.

- [ ] **Step 6: Manual verification — correct submission with one hint used**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
printf "5\n1\n1\nE\nH\n#include <iostream>\n\nint main() {\n    std::cout << \"Merhaba, C++!\";\n    return 0;\n}\nBITIR\n0\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```
This pipes: main menu → Kod Yazma Alıştırmaları (5), Başlangıç tier (1),
exercise 1 "Ekrana yazı yazdırma" (1), request one hint (`E`), decline
further hints (`H`), then submit the exact sample-solution code (ending
with `BITIR`), then `0` (back to tier list), `0` (back to tier menu), `0`
(exit app).

Confirm: after `E`, the first hint prints exactly `cout kullanmayı
hatırla.`; after the code submission, `Doğru! (+30 XP)` prints (baseXp 40,
1 hint used → `static_cast<int>(40.0 * 0.75)` = 30); then the sample
solution and alternative-solution note both print (the exact text from
`src/CodeExerciseManager.cpp`'s exercise 1 entry).

- [ ] **Step 7: Manual verification — incorrect submission still reveals the sample solution**

```bash
rm -f data/progress.txt data/mistakes.txt data/achievements.txt data/generated_question_history.txt data/settings.txt
printf "5\n1\n1\nH\nint main() { return 0; }\nBITIR\n0\n0\n0\n" | ./build/Debug/CppMasterConsole.exe
```
This submits code missing both required keywords (`cout`, `Merhaba`).
Confirm: `Gönderdiğiniz kod beklenen kriterleri karşılamıyor.` prints (not
"Doğru!"), and the sample solution and alternative-solution note **still**
print immediately after — proving the "show the solution after any
attempt, not just a correct one" design.

Clean up all `data/*.txt` files after this step.

- [ ] **Step 8: Commit**

```bash
git add src/Application.h src/Application.cpp
git commit -m "Wire Kod Yazma Alıştırmaları mode into Application, reusing QuizEngine for grading"
```

- [ ] **Step 9: Update the roadmap**

Edit `docs/superpowers/roadmap.md`: mark the Phase 11 entry COMPLETE with
its commit range (Task 1's first commit through Task 3's final commit),
matching the style of the Phase 8/9/10 entries, and update the Status
section to name Phase 11 complete and Phase 12 starting next.

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 11 complete in roadmap"
```

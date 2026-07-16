# Bölüm 2 İçerik Genişletmesi Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Give topics 11-20 (Section 2, "Operatörler ve koşullar") real lesson
content and a 29-question-per-topic question bank (290 questions total),
closing the roadmap gap for the first of nine content-expansion phases.

**Architecture:** Two new per-section content files
(`src/LessonContentSection2.cpp`, `src/QuestionsSection2.cpp`) keep this
phase's large volume of hand-authored content out of the already-large
`LessonManager.cpp`/`QuestionManager.cpp`, following the same free-function
pattern `LessonManager.cpp` already uses internally
(`applyIntroLessonContent`). Two new tiny headers
(`src/LessonContent.h`, `src/QuestionContent.h`) declare each section's
entry point so future phases (14-21) can add their own
`applySectionNLessonContent`/`appendSectionNQuestions` without editing
existing section files. No `Application.cpp` changes are needed: both
`openTopic` and `runTopicQuiz` already work generically once a topic has a
non-empty `Lesson::explanation` and at least one `Question` — see the
design spec for the exact line references confirming this.

**Tech Stack:** C++20, standard library only, existing `Lesson`/`Question`
structs, existing `LessonManager`/`QuestionManager` classes (both
unmodified in shape — only their constructors gain one extra call each).

## Global Constraints

- Topics covered: 11 (Matematiksel operatörler), 12 (% mod operatörü),
  13 (Kısaltılmış atama operatörleri), 14 (++ ve --),
  15 (Karşılaştırma operatörleri), 16 (Mantıksal operatörler), 17 (if),
  18 (if-else), 19 (else if), 20 (Üçlü koşul operatörü) — sectionId 2,
  exactly as named in `src/LessonManager.cpp`'s `kTopicSeeds` table.
- Lesson content mirrors `applyIntroLessonContent`'s exact struct usage:
  `explanation`, `syntax`, `exampleCode`, `lineExplanations` (vector),
  `commonMistakes` (vector) — no new `Lesson` fields.
- Question ids are sequential starting at 73 (the existing bank ends at
  72): topic 11 = 73-101, topic 12 = 102-130, topic 13 = 131-159,
  topic 14 = 160-188, topic 15 = 189-217, topic 16 = 218-246,
  topic 17 = 247-275, topic 18 = 276-304, topic 19 = 305-333,
  topic 20 = 334-362. Each topic gets exactly 29 questions, no more, no
  fewer — the task's own review must count them.
- Per-topic type/difficulty/baseXp distribution (fixed, identical for all
  10 topics):

  | Type            | Count | Difficulty (in order authored)                                    | baseXp        |
  |-----------------|-------|--------------------------------------------------------------------|---------------|
  | MultipleChoice  | 8     | VeryEasy, Easy, Easy, Medium, Medium, Medium, Hard, Hard            | 5,10,10,20,20,20,30,30 |
  | TrueFalse       | 6     | VeryEasy, VeryEasy, Easy, Easy, Medium, Medium                      | 5,5,10,10,20,20 |
  | FillBlank       | 6     | Easy, Easy, Easy, Medium, Medium, Medium                            | 10,10,10,20,20,20 |
  | CompleteLine    | 2     | Medium, Medium                                                      | 20,20 |
  | PredictOutput   | 2     | Medium, Hard                                                        | 20,30 |
  | FindError       | 2     | Medium, Hard                                                        | 20,30 |
  | FixCode         | 1     | Hard                                                                | 30 |
  | OrderCode       | 1     | Medium                                                              | 20 |
  | WriteCode       | 1     | Hard                                                                | 40 (matches existing WriteCode/Hard precedent, ids 71-72) |

  This exact 29-question sequence and its exact ids/difficulties/baseXp are
  spelled out in full for every question in Tasks 2-4 below — no task
  needs to invent content, only transcribe it exactly as written.
- `MultipleChoice.acceptedAnswers` uses a single lowercase letter
  (`"a"`/`"b"`/`"c"`/`"d"`) matching the 0-indexed position in `options`,
  exactly like the existing bank (e.g. id 1's `.acceptedAnswers = {"b"}`
  for its 2nd option).
- `TrueFalse` has no `options` field; `acceptedAnswers = {"1"}` means the
  prompt's statement is true, `{"2"}` means false — exactly like the
  existing bank (ids 3, 4, 9, 10...).
- `OrderCode.acceptedAnswers` is a single string of 1-indexed option
  positions separated by spaces (e.g. `{"3 2 1 4"}`), exactly like the
  existing bank (ids 69, 70).
- `WriteCode.acceptedAnswers` is a list of required substrings/keywords
  (graded leniently by `QuizEngine::evaluate`, not exact match), exactly
  like the existing bank (ids 71, 72).
- Every `Question`/`Lesson` field must be filled in exactly as written in
  this plan — do not paraphrase prompts, options, accepted answers, or
  explanations.

---

### Task 1: Section 2 lesson content

**Files:**
- Create: `src/LessonContent.h`
- Create: `src/LessonContentSection2.cpp`
- Modify: `src/LessonManager.cpp` (include the new header, call the new
  function at the end of the constructor)
- Modify: `CMakeLists.txt` (add both new files to `CppMasterConsoleLib`'s
  source list, right after the existing `src/LessonManager.cpp` line)
- Modify: `tests/LessonManagerTests.cpp` (replace the now-outdated
  "topics 11-100 have no content" test)

**Interfaces:**
- Produces: `void applySection2LessonContent(std::vector<Lesson>& lessons);`
  — called with the manager's full 100-element `lessons_` vector, must
  write into indices 10-19 (topics 11-20), matching
  `applyIntroLessonContent`'s documented positional-index convention.

- [ ] **Step 1: Create the shared declaration header**

Create `src/LessonContent.h`:

```cpp
#pragma once

#include <vector>

struct Lesson;

void applySection2LessonContent(std::vector<Lesson>& lessons);
```

- [ ] **Step 2: Write the lesson content**

Create `src/LessonContentSection2.cpp`:

```cpp
#include "LessonContent.h"

#include "Lesson.h"

void applySection2LessonContent(std::vector<Lesson>& lessons) {
    // Index 10 = topic id 11 (Matematiksel operatörler), index 19 = topic
    // id 20 (Üçlü koşul operatörü) — same positional convention as
    // applyIntroLessonContent in LessonManager.cpp.

    lessons[10].explanation =
        "C++'ta temel matematiksel işlemler +, -, *, / operatörleriyle "
        "yapılır. Operatör önceliği matematikteki gibidir (* ve / önce, + "
        "ve - sonra); parantezle öncelik değiştirilebilir. İki tam sayı "
        "(int) bölündüğünde sonuç da tam sayıya yuvarlanır (ondalık kısım "
        "atılır); ondalıklı sonuç istenirse en az bir işlenenin "
        "double/float olması gerekir.";
    lessons[10].syntax = "int sonuc = a + b * c;";
    lessons[10].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int a = 7;\n"
        "    int b = 2;\n"
        "    std::cout << a + b << \"\\n\";\n"
        "    std::cout << a / b << \"\\n\";\n"
        "    std::cout << static_cast<double>(a) / b << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[10].lineExplanations = {
        "a + b : 7 + 2 = 9 sonucunu verir.",
        "a / b : İki tam sayı bölündüğü için sonuç 3 olur (3.5 değil, "
        "ondalık kısım atılır).",
        "static_cast<double>(a) / b : a önce double'a çevrildiği için "
        "bölme ondalıklı yapılır, sonuç 3.5 olur.",
    };
    lessons[10].commonMistakes = {
        "İki int'i bölüp ondalıklı sonuç beklemek (7 / 2 sonucu 3'tür, 3.5 "
        "değil).",
        "Operatör önceliğini unutup parantez kullanmadan yanlış sonuç "
        "almak (örneğin 2 + 3 * 4, 20 değil 14'tür).",
        "Negatif sayılarla bölme/mod sonucunun beklenmedik işaretli "
        "çıkabileceğini gözden kaçırmak.",
    };

    lessons[11].explanation =
        "% (mod) operatörü, bir tam sayının başka bir tam sayıya "
        "bölümünden kalanı verir. Yalnızca tam sayı (int) türleriyle "
        "kullanılır; double/float ile kullanılamaz. Bir sayının çift/tek "
        "olup olmadığını kontrol etmek (sayi % 2 == 0) gibi işlemlerde "
        "sıkça kullanılır.";
    lessons[11].syntax = "int kalan = a % b;";
    lessons[11].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int a = 17;\n"
        "    int b = 5;\n"
        "    std::cout << a % b << \"\\n\";\n"
        "    std::cout << (a % 2 == 0 ? \"cift\" : \"tek\") << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[11].lineExplanations = {
        "a % b : 17'nin 5'e bölümünden kalan 2'dir (17 = 5*3 + 2).",
        "a % 2 == 0 : a'nın 2'ye bölümünden kalan sıfır mı diye kontrol "
        "eder; 17 tek olduğu için false döner.",
    };
    lessons[11].commonMistakes = {
        "% operatörünü double/float değişkenlerle kullanmaya çalışmak "
        "(derleme hatası verir).",
        "% operatörünü bölme (/) ile karıştırmak.",
        "0'a mod almaya çalışmak (a % 0), tıpkı 0'a bölme gibi tanımsız "
        "davranışa yol açar.",
    };

    lessons[12].explanation =
        "+=, -=, *=, /=, %= operatörleri, bir değişkenin mevcut değeri "
        "üzerinde işlem yapıp sonucu yine aynı değişkene atamanın kısa "
        "yoludur. Örneğin a += 5, a = a + 5 ile aynı anlama gelir. Kod "
        "tekrarını azaltır ve okunabilirliği artırır.";
    lessons[12].syntax = "sayi += 5;  // sayi = sayi + 5; ile aynıdır";
    lessons[12].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int puan = 10;\n"
        "    puan += 5;\n"
        "    puan *= 2;\n"
        "    std::cout << puan;\n"
        "    return 0;\n"
        "}";
    lessons[12].lineExplanations = {
        "puan += 5; : puan = puan + 5; ile aynıdır, puan 15 olur.",
        "puan *= 2; : puan = puan * 2; ile aynıdır, puan 30 olur.",
    };
    lessons[12].commonMistakes = {
        "+= operatörünü yanlışlıkla =+ şeklinde yazmak (=+ de derlenir "
        "ama farklı ve yanlış bir anlam taşır).",
        "Kısaltılmış atamanın sağ tarafındaki tüm ifadenin işleme dahil "
        "olduğunu unutmak (a *= b + 1, a = a * (b + 1) anlamına gelir, "
        "a = a * b + 1 değil).",
        "Değişkenin başlangıç değeri atanmamışken += kullanmaya "
        "çalışmak.",
    };

    lessons[13].explanation =
        "++ ve -- operatörleri, bir değişkenin değerini 1 artırır veya "
        "azaltır. Önden (++sayi) kullanıldığında değişken önce "
        "güncellenir sonra kullanılır; sondan (sayi++) kullanıldığında "
        "önce mevcut değer kullanılır, değişken daha sonra güncellenir. "
        "Tek başına bir satırda kullanıldıklarında ikisi de aynı sonucu "
        "verir; bir ifadenin içinde kullanıldıklarında fark ortaya "
        "çıkar.";
    lessons[13].syntax = "sayi++;  // veya ++sayi;";
    lessons[13].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int a = 5;\n"
        "    std::cout << a++ << \"\\n\";\n"
        "    std::cout << a << \"\\n\";\n"
        "    int b = 5;\n"
        "    std::cout << ++b << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[13].lineExplanations = {
        "a++ : Önce a'nın o anki değeri (5) yazdırılır, sonra a 6 olur.",
        "a : Bir önceki satırda güncellendiği için artık 6 yazdırılır.",
        "++b : Önce b 6 olur, sonra bu güncel değer (6) yazdırılır.",
    };
    lessons[13].commonMistakes = {
        "Önden ve sondan artırmanın tek başına bir satırda fark "
        "yaratmadığını sanıp bir ifade içinde de aynı davrandığını "
        "düşünmek.",
        "a++ ifadesinin sonucunun artırma sonrası değeri gösterdiğini "
        "sanmak (aslında artırma öncesi değeri gösterir).",
        "++ operatörünü aynı ifadede bir değişken üzerinde birden fazla "
        "kez kullanmak (karışık/öngörülemeyen davranışa yol açabilir).",
    };

    lessons[14].explanation =
        "==, !=, <, >, <=, >= operatörleri iki değeri karşılaştırır ve "
        "bool (true/false) sonucu döner. == eşitlik, != eşit olmama, <, "
        ">, <=, >= sırasıyla küçük, büyük, küçük eşit, büyük eşit "
        "anlamına gelir. == ile atama operatörü olan = karıştırılmamalıdır.";
    lessons[14].syntax = "if (a == b) { ... }";
    lessons[14].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int a = 5;\n"
        "    int b = 7;\n"
        "    std::cout << (a == b) << \"\\n\";\n"
        "    std::cout << (a < b) << \"\\n\";\n"
        "    std::cout << (a != b) << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[14].lineExplanations = {
        "a == b : 5, 7'ye eşit olmadığı için false (0) döner.",
        "a < b : 5, 7'den küçük olduğu için true (1) döner.",
        "a != b : 5 ile 7 eşit olmadığı için true (1) döner.",
    };
    lessons[14].commonMistakes = {
        "Karşılaştırma için == yerine yanlışlıkla atama operatörü = "
        "kullanmak (if (a = b) gibi; bu hem hatalı hem de derlenebilir "
        "bir koddur).",
        "cout ile bool sonucunu yazdırırken true/false yerine 1/0 "
        "göründüğünü fark etmemek.",
        "Ondalıklı (double/float) sayıları == ile doğrudan karşılaştırmak "
        "(yuvarlama hataları nedeniyle güvenilmez olabilir).",
    };

    lessons[15].explanation =
        "&&, || ve ! mantıksal operatörleridir. && (VE) her iki koşul da "
        "doğruysa true döner; || (VEYA) koşullardan en az biri doğruysa "
        "true döner; ! (DEĞİL) bir bool ifadenin tersini alır. Birden "
        "fazla koşulu birleştirmek için kullanılırlar.";
    lessons[15].syntax = "if (a > 0 && b > 0) { ... }";
    lessons[15].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int yas = 20;\n"
        "    bool ehliyetVar = true;\n"
        "    std::cout << (yas >= 18 && ehliyetVar) << \"\\n\";\n"
        "    std::cout << (yas < 18 || !ehliyetVar) << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[15].lineExplanations = {
        "yas >= 18 && ehliyetVar : Her iki koşul da true olduğu için "
        "sonuç true (1) olur.",
        "yas < 18 || !ehliyetVar : yas < 18 false, !ehliyetVar de false "
        "olduğu için sonuç false (0) olur.",
    };
    lessons[15].commonMistakes = {
        "&& ve || operatörlerini birbirine karıştırmak (VE yerine VEYA "
        "mantığı kullanmak).",
        "Tek & veya tek | yazmak (bunlar bitwise operatörlerdir, "
        "mantıksal && / || ile aynı işi yapmaz).",
        "! operatörünün önceliğini yanlış varsayıp parantezsiz karmaşık "
        "ifadeler yazmak.",
    };

    lessons[16].explanation =
        "if ifadesi, parantez içindeki koşul true olduğunda süslü "
        "parantez { } içindeki kod bloğunun çalışmasını sağlar. Koşul "
        "false ise blok atlanır. Tek satırlık bloklarda süslü parantez "
        "isteğe bağlıdır, ancak okunabilirlik için genelde kullanılması "
        "önerilir.";
    lessons[16].syntax = "if (kosul) {\n    // kosul true ise calisir\n}";
    lessons[16].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int yas = 20;\n"
        "    if (yas >= 18) {\n"
        "        std::cout << \"Reşitsiniz.\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[16].lineExplanations = {
        "if (yas >= 18) : yas'ın 18'den büyük veya eşit olup olmadığını "
        "kontrol eder.",
        "std::cout << \"Reşitsiniz.\"; : Koşul true olduğu için bu satır "
        "çalışır ve ekrana yazılır.",
    };
    lessons[16].commonMistakes = {
        "if satırının sonuna yanlışlıkla noktalı virgül koymak "
        "(if (kosul);), bu durumda blok her zaman 'çalışmış' gibi "
        "davranır.",
        "Koşulu == yerine = ile yazmak (if (yas = 18) her zaman true "
        "döner ve yas'ı 18 yapar).",
        "Süslü parantezi unutup birden fazla satırı if'e bağlı sanmak "
        "(parantezsiz yalnızca ilk satır if'e bağlıdır).",
    };

    lessons[17].explanation =
        "if-else yapısı, koşul true olduğunda if bloğunu, false "
        "olduğunda else bloğunu çalıştırır. İki alternatif yoldan tam "
        "olarak birinin çalışmasını garanti eder.";
    lessons[17].syntax = "if (kosul) {\n    // true ise\n} else {\n    // false ise\n}";
    lessons[17].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int not_ = 45;\n"
        "    if (not_ >= 50) {\n"
        "        std::cout << \"Geçti\";\n"
        "    } else {\n"
        "        std::cout << \"Kaldı\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[17].lineExplanations = {
        "if (not_ >= 50) : not_'un 50'ye eşit veya büyük olup olmadığını "
        "kontrol eder.",
        "std::cout << \"Kaldı\"; : not_ 45 olduğu için koşul false'tur, "
        "bu yüzden else bloğu çalışır ve 'Kaldı' yazdırılır.",
    };
    lessons[17].commonMistakes = {
        "else'den önce noktalı virgül veya ekstra kod koymak (else, "
        "doğrudan if bloğunun kapanışından sonra gelmelidir).",
        "if ve else bloklarının her ikisinin de aynı anda "
        "çalışabileceğini sanmak (yalnızca biri çalışır).",
        "else'i gereksiz yere ayrı bir if ile taklit etmeye çalışmak "
        "(if (!kosul) tekrar yazmak yerine else kullanmak daha nettir).",
    };

    lessons[18].explanation =
        "else if, birden fazla koşulu sırayla kontrol etmeyi sağlar. "
        "Yukarıdan aşağıya doğru koşullar sırayla değerlendirilir; ilk "
        "true olan bloğun kodu çalışır ve geri kalanlar atlanır. En sona "
        "isteğe bağlı bir else eklenerek hiçbir koşul sağlanmazsa "
        "çalışacak varsayılan bir blok tanımlanabilir.";
    lessons[18].syntax =
        "if (kosul1) {\n    ...\n} else if (kosul2) {\n    ...\n} else {\n    ...\n}";
    lessons[18].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int not_ = 75;\n"
        "    if (not_ >= 85) {\n"
        "        std::cout << \"AA\";\n"
        "    } else if (not_ >= 70) {\n"
        "        std::cout << \"BA\";\n"
        "    } else {\n"
        "        std::cout << \"Diğer\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[18].lineExplanations = {
        "if (not_ >= 85) : 75 için false olduğundan bu blok atlanır.",
        "else if (not_ >= 70) : 75, 70'e eşit veya büyük olduğu için "
        "true olur ve 'BA' yazdırılır.",
        "else : Yukarıdaki koşullardan biri true olduğu için bu blok hiç "
        "çalışmaz.",
    };
    lessons[18].commonMistakes = {
        "else if koşullarının sırasını yanlış kurup her zaman ilk (en "
        "geniş) koşulun eşleşmesine izin vermek (örneğin >= 70 koşulunu "
        ">= 85'ten önce yazmak, AA notunu asla vermez).",
        "Her koşulu bağımsız ayrı if'ler olarak yazıp else if "
        "kullanmamak (bu, tüm koşulların gereksiz yere kontrol "
        "edilmesine yol açar).",
        "Zincirin sonuna else eklemeyi unutup hiçbir koşul "
        "sağlanmadığında hiçbir şey olmayacağını fark etmemek.",
    };

    lessons[19].explanation =
        "Üçlü (ternary) koşul operatörü ?:, kısa bir if-else'in tek "
        "satırda yazılmasını sağlar. kosul ? deger1 : deger2 şeklinde "
        "kullanılır; kosul true ise deger1, false ise deger2 sonucu "
        "döner. Genelde bir değişkene basit bir koşullu değer atarken "
        "tercih edilir.";
    lessons[19].syntax = "sonuc = kosul ? deger1 : deger2;";
    lessons[19].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    int yas = 16;\n"
        "    std::string durum = (yas >= 18) ? \"Reşit\" : \"Reşit değil\";\n"
        "    std::cout << durum;\n"
        "    return 0;\n"
        "}";
    lessons[19].lineExplanations = {
        "(yas >= 18) ? \"Reşit\" : \"Reşit değil\" : yas 18'den küçük "
        "olduğu için koşul false'tur, sonuç olarak 'Reşit değil' seçilir.",
        "durum : Ternary ifadenin sonucunu tutan string değişkendir.",
    };
    lessons[19].commonMistakes = {
        "Üçlü operatörü karmaşık, çok satırlı mantık için kullanmaya "
        "çalışmak (okunabilirliği bozar; böyle durumlarda if-else tercih "
        "edilmelidir).",
        ": ve ? sembollerinin yerini karıştırmak.",
        "İki taraftaki (true/false) ifadelerin farklı türde olmasına "
        "dikkat etmemek (derleyici uyarısı/hatasına yol açabilir).",
    };
}
```

- [ ] **Step 3: Wire the new function into `LessonManager`**

In `src/LessonManager.cpp`, add near the top (after the existing
`#include` lines):

```cpp
#include "LessonContent.h"
```

Then change the constructor's final line from:

```cpp
    applyIntroLessonContent(lessons_);
}
```

to:

```cpp
    applyIntroLessonContent(lessons_);
    applySection2LessonContent(lessons_);
}
```

- [ ] **Step 4: Register the new files in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/LessonManager.h
    src/LessonManager.cpp
```

to:

```cmake
    src/LessonManager.h
    src/LessonManager.cpp
    src/LessonContent.h
    src/LessonContentSection2.cpp
```

- [ ] **Step 5: Update the outdated "no content yet" test**

In `tests/LessonManagerTests.cpp`, replace this entire test:

```cpp
TEST_CASE(LessonManager_TopicsElevenToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 100; ++topicId) {
        const auto lesson = manager.findById(topicId);
        CHECK(lesson.has_value());
        CHECK(lesson->explanation.empty());
    }
}
```

with these two tests:

```cpp
TEST_CASE(LessonManager_TopicsElevenToTwentyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 20; ++topicId) {
        const auto lesson = manager.findById(topicId);
        CHECK(lesson.has_value());
        CHECK(!lesson->explanation.empty());
        CHECK(!lesson->syntax.empty());
        CHECK(!lesson->exampleCode.empty());
    }
}

TEST_CASE(LessonManager_TopicsTwentyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 21; topicId <= 100; ++topicId) {
        const auto lesson = manager.findById(topicId);
        CHECK(lesson.has_value());
        CHECK(lesson->explanation.empty());
    }
}
```

- [ ] **Step 6: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `88/88 test(s) passed.` (87 existing - 1 removed test + 2 new
tests = 88).

- [ ] **Step 7: Commit**

```bash
git add src/LessonContent.h src/LessonContentSection2.cpp src/LessonManager.cpp CMakeLists.txt tests/LessonManagerTests.cpp
git commit -m "feat(content): add Section 2 lesson content (topics 11-20)"
```

---

### Task 2: Questions for topics 11-14 (ids 73-188)

**Files:**
- Create: `src/QuestionContent.h`
- Create: `src/QuestionsSection2.cpp`
- Modify: `src/QuestionManager.cpp` (include the new header, call the new
  function at the end of the constructor, bump the `reserve()` call)
- Modify: `CMakeLists.txt` (add both new files to `CppMasterConsoleLib`'s
  source list, right after the existing `src/QuestionManager.cpp` line)

**Interfaces:**
- Produces: `void appendSection2Questions(std::vector<Question>& questions);`
  — Task 3 and Task 4 append more `questions_.push_back(...)` calls to
  this SAME function body (in this same file) for topics 15-17 and
  18-20 respectively. This task only adds topics 11-14 (ids 73-188).

- [ ] **Step 1: Create the shared declaration header**

Create `src/QuestionContent.h`:

```cpp
#pragma once

#include <vector>

struct Question;

void appendSection2Questions(std::vector<Question>& questions);
```

- [ ] **Step 2: Write topics 11-14's questions**

Create `src/QuestionsSection2.cpp`:

```cpp
#include "QuestionContent.h"

#include "Question.h"

void appendSection2Questions(std::vector<Question>& questions) {
    // Topic 11: Matematiksel operatörler
    questions.push_back(Question{
        .id = 73, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "5 + 3 işleminin sonucu kaçtır?",
        .options = {"7", "8", "9", "15"},
        .acceptedAnswers = {"b"},
        .explanation = "5 + 3 toplamı 8'e eşittir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 74, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "10 - 4 * 2 işleminin sonucu kaçtır?",
        .options = {"12", "2", "6", "20"},
        .acceptedAnswers = {"b"},
        .explanation = "Önce çarpma yapılır (4 * 2 = 8), sonra çıkarma yapılır (10 - 8 = 2).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 75, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "İki int değişken bölündüğünde (örneğin 7 / 2) sonuç ne tür olur?",
        .options = {"Ondalıklı (3.5)", "Tam sayı, ondalık atılır (3)", "Hata verir", "Her zaman 0"},
        .acceptedAnswers = {"b"},
        .explanation = "İki tam sayı bölündüğünde sonuç da tam sayıdır; ondalık kısım atılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 76, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 9; int b = 4; ifadesinde a / b işleminin sonucu kaçtır?",
        .options = {"2", "2.25", "3", "1"},
        .acceptedAnswers = {"a"},
        .explanation = "9 / 4, tam sayı bölmesiyle 2 eder (2.25 değil, ondalık kısım atılır).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 77, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "2 + 3 * 4 - 1 işleminin sonucu kaçtır?",
        .options = {"13", "19", "24", "9"},
        .acceptedAnswers = {"a"},
        .explanation = "Önce 3 * 4 = 12 hesaplanır, sonra 2 + 12 - 1 = 13 bulunur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 78, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "(2 + 3) * 4 işleminin sonucu kaçtır?",
        .options = {"14", "20", "9", "24"},
        .acceptedAnswers = {"b"},
        .explanation = "Parantez içi önce hesaplanır (2 + 3 = 5), sonra 5 * 4 = 20 bulunur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 79, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int x = 7; int y = 2; double sonuc = x / y; ifadesinden sonra sonuc değişkeninin değeri kaçtır?",
        .options = {"3.5", "3", "4", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "x / y önce int bölmesi olarak hesaplanır (3 olur), ardından double'a atanır; sonuç 3.5 değil 3'tür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 80, .topicId = 11,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = -7; int b = 2; a / b işleminin sonucu (C++11 ve sonrası standartlara göre) kaçtır?",
        .options = {"-4", "-3", "-3.5", "3"},
        .acceptedAnswers = {"b"},
        .explanation = "C++11'den itibaren tam sayı bölmesi sıfıra doğru yuvarlanır; -7 / 2 sonucu -3.5 değil -3'tür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 81, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "C++'ta * operatörü çarpma işlemi için kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "* operatörü iki sayıyı çarpar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 82, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "C++'ta iki tam sayının bölümü her zaman ondalıklı bir sonuç verir.",
        .acceptedAnswers = {"2"},
        .explanation = "İki tam sayının bölümü tam sayı sonucu verir; ondalık kısım atılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 83, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Operatör önceliğine göre çarpma ve bölme, toplama ve çıkarmadan önce yapılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Matematikteki gibi, * ve / işlemleri + ve -'den önce değerlendirilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 84, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Parantez kullanmak, operatör önceliğini değiştirebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Parantez içindeki ifadeler her zaman önce hesaplanır, bu da önceliği değiştirebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 85, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = 2; double c = a / b; ifadesinde c'nin değeri 2.5'tir.",
        .acceptedAnswers = {"2"},
        .explanation = "a / b önce int bölmesi olarak hesaplanır (2 olur), sonra double'a atanır; c'nin değeri 2.5 değil 2.0'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 86, .topicId = 11,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "C++'ta operatör önceliği matematikteki sıraya (çarpma/bölme önce, toplama/çıkarma sonra) benzer şekilde çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "C++'ın operatör önceliği kuralları matematikteki geleneksel sırayı takip eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 87, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sonuc = 6 _____ 3; ifadesinin sonucu 2 olsun istiyorsunuz. Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"/"},
        .explanation = "6 / 3 = 2 olduğu için bölme operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 88, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sonuc = 4 _____ 5; ifadesinin sonucu 20 olsun istiyorsunuz. Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "4 * 5 = 20 olduğu için çarpma operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 89, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sonuc = 10 _____ 3; ifadesinin sonucu 7 olsun istiyorsunuz. Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"-"},
        .explanation = "10 - 3 = 7 olduğu için çıkarma operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 90, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 8; int b = 3; int sonuc = a _____ b; ifadesinin sonucu 2 olsun istiyorsunuz (tam sayı bölmesiyle). Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"/"},
        .explanation = "8 / 3, tam sayı bölmesiyle 2 eder (ondalık kısım atılır).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 91, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sonuc = 2 + 3 _____ 4; ifadesinin sonucu 14 olması için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "Önce 3 * 4 = 12 hesaplanır, ardından 2 + 12 = 14 bulunur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 92, .topicId = 11,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "double sonuc = _____(7) / 2; ifadesinin sonucu 3.5 olması için boşluğa hangi tür dönüştürme (cast) yazılmalı? (örnek: static_cast<double>)",
        .acceptedAnswers = {"static_cast<double>"},
        .explanation = "7 önce double'a dönüştürülürse bölme ondalıklı yapılır ve sonuç 3.5 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 93, .topicId = 11,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 12;\nint b = 5;\nint sonuc = a _____ b;\nYukarıdaki kodun çalışması sonucunda sonuc değişkeninin 7 olması isteniyor. Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"a - b", "a-b"},
        .explanation = "12 - 5 = 7 olduğu için çıkarma işlemi yapılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 94, .topicId = 11,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int taban = 3;\nint yukseklik = 4;\nint alan = _____;\nBir üçgenin alanını (taban * yükseklik / 2) hesaplayan kodu tamamlayın.",
        .acceptedAnswers = {"taban * yukseklik / 2", "taban*yukseklik/2"},
        .explanation = "Üçgen alanı taban * yükseklik / 2 formülüyle hesaplanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 95, .topicId = 11,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 15;\nint b = 4;\nstd::cout << a / b;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "15 / 4, tam sayı bölmesiyle 3 eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 96, .topicId = 11,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 2;\nint b = 3;\nint c = 4;\nstd::cout << a + b * c - 1;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"13"},
        .explanation = "Önce b * c = 12 hesaplanır, sonra 2 + 12 - 1 = 13 bulunur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 97, .topicId = 11,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint sonuc = 10 // 3;\nstd::cout << sonuc;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int sonuc = 10 / 3;"},
        .explanation = "// bir yorum başlatır ve satırın geri kalanını yok sayar; bölme için tek / kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 98, .topicId = 11,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\ndouble sonuc = 7 / 2;\nstd::cout << sonuc;\n\nProgramcı sonuc'un 3.5 olmasını bekliyor ama kod 3 veriyor. Hatalı satırı, 3.5 sonucunu verecek şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"double sonuc = 7.0 / 2;", "double sonuc = static_cast<double>(7) / 2;"},
        .explanation = "7 / 2 önce int bölmesi olarak hesaplandığı için 3 olur; işlenenlerden birini ondalıklı yapmak (7.0) gerçek bölme sonucunu (3.5) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 99, .topicId = 11,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint sonuc = 5 x 3;\nstd::cout << sonuc;\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int sonuc = 5 * 3;"},
        .explanation = "Çarpma işlemi x harfiyle değil * operatörüyle yapılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 100, .topicId = 11,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, iki sayının ortalamasını hesaplayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın, örnek: 1 2 3):",
        .options = {"std::cout << ortalama;", "double ortalama = (a + b) / 2.0;", "int a = 4, b = 6;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce değişkenler tanımlanır (int a = 4, b = 6;), sonra ortalama hesaplanır, en son yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 101, .topicId = 11,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan iki tam sayı okuyup toplamlarını, farklarını ve çarpımlarını ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "cout", "<<", "+", "-", "*"},
        .explanation = "Program iki sayıyı cin >> ile okumalı, +, - ve * operatörleriyle işlem yapmalı ve cout << ile sonuçları yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 12: % mod operatörü
    questions.push_back(Question{
        .id = 102, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "10 % 3 işleminin sonucu kaçtır?",
        .options = {"3", "1", "0", "10"},
        .acceptedAnswers = {"b"},
        .explanation = "10'un 3'e bölümünden kalan 1'dir (10 = 3*3 + 1).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 103, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "% operatörü hangi amaçla kullanılır?",
        .options = {"Çarpma", "Bölme", "Bölümden kalanı bulma", "Üs alma"},
        .acceptedAnswers = {"c"},
        .explanation = "% operatörü, bir sayının başka bir sayıya bölümünden kalanı verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 104, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "8 % 2 işleminin sonucu kaçtır?",
        .options = {"4", "0", "2", "8"},
        .acceptedAnswers = {"b"},
        .explanation = "8, 2'ye tam bölündüğü için kalan 0'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 105, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "% operatörü hangi veri türleriyle kullanılabilir?",
        .options = {"Yalnızca double", "Yalnızca float", "Yalnızca tam sayı (int) türleri", "Her türle"},
        .acceptedAnswers = {"c"},
        .explanation = "% operatörü yalnızca tam sayı türleriyle kullanılabilir; double/float ile kullanılamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 106, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "17 % 5 işleminin sonucu kaçtır?",
        .options = {"3", "2", "17", "5"},
        .acceptedAnswers = {"b"},
        .explanation = "17'nin 5'e bölümünden kalan 2'dir (17 = 5*3 + 2).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 107, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir sayının çift olup olmadığını kontrol etmek için hangi ifade kullanılır?",
        .options = {"sayi % 2 == 1", "sayi % 2 == 0", "sayi / 2 == 0", "sayi * 2 == 0"},
        .acceptedAnswers = {"b"},
        .explanation = "Bir sayının 2'ye göre modu sıfırsa, sayı çifttir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 108, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "-7 % 2 işleminin C++'taki (C++11 ve sonrası) sonucu kaçtır?",
        .options = {"1", "-1", "3", "-3"},
        .acceptedAnswers = {"b"},
        .explanation = "C++11'den itibaren % işleminin işareti bölünenin (dividend) işaretiyle aynıdır; -7 % 2 sonucu -1'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 109, .topicId = 12,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 25; int b = 4; sonuc değişkenine a % b değerinin atanmasıyla sonuc kaç olur?",
        .options = {"6", "1", "6.25", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "25'in 4'e bölümünden kalan 1'dir (25 = 4*6 + 1).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 110, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "% operatörü, bölme işleminden kalanı verir.",
        .acceptedAnswers = {"1"},
        .explanation = "% operatörünün amacı tam olarak budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 111, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "% operatörü ondalıklı (double) sayılarla doğrudan kullanılabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "% operatörü yalnızca tam sayı türleriyle kullanılabilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 112, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "10 % 2 işleminin sonucu 0'dır.",
        .acceptedAnswers = {"1"},
        .explanation = "10, 2'ye tam bölünür, kalan 0'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 113, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "7 % 3 işleminin sonucu 2'dir.",
        .acceptedAnswers = {"2"},
        .explanation = "7'nin 3'e bölümünden kalan 1'dir (7 = 3*2 + 1), 2 değil.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 114, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir sayının 2'ye göre modu (sayi % 2), sayının çift mi tek mi olduğunu anlamak için kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Sonuç 0 ise sayı çift, 1 ise tektir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 115, .topicId = 12,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "0 % 5 işleminin sonucu 5'tir.",
        .acceptedAnswers = {"2"},
        .explanation = "0'ın 5'e bölümünden kalan 0'dır, 5 değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 116, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int kalan = 13 _____ 4; ifadesinin sonucu 1 olsun istiyorsunuz. Boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"%"},
        .explanation = "13'ün 4'e bölümünden kalan 1'dir; bu işlem % operatörüyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 117, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "9 % 3 = _____ (sonucu yazın)",
        .acceptedAnswers = {"0"},
        .explanation = "9, 3'e tam bölünür, kalan 0'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 118, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "15 % 4 = _____ (sonucu yazın)",
        .acceptedAnswers = {"3"},
        .explanation = "15'in 4'e bölümünden kalan 3'tür (15 = 4*3 + 3).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 119, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 8; bool ciftMi = (sayi % _____ == 0); ifadesinin sayi'nın çift olup olmadığını kontrol etmesi için boşluğa hangi sayı yazılmalı?",
        .acceptedAnswers = {"2"},
        .explanation = "Bir sayının 2'ye göre modu sıfırsa sayı çifttir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 120, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "23 % 5 = _____ (sonucu yazın)",
        .acceptedAnswers = {"3"},
        .explanation = "23'ün 5'e bölümünden kalan 3'tür (23 = 5*4 + 3).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 121, .topicId = 12,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 100; int b = 7; int kalan = a _____ b; ifadesinin kalan değişkenine 100'ün 7'ye bölümünden kalanı ataması için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"%"},
        .explanation = "Bölümden kalanı bulmak için % operatörü kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 122, .topicId = 12,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 9;\nbool tekMi = _____;\nsayi'nın tek olup olmadığını (sayi % 2 == 1) kontrol eden ifadeyi boşluğa yazın.",
        .acceptedAnswers = {"sayi % 2 == 1", "sayi%2==1"},
        .explanation = "Bir sayının 2'ye göre modu 1 ise sayı tektir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 123, .topicId = 12,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 29;\nint b = 6;\nint kalan = _____;\na'nın b'ye bölümünden kalanı hesaplayan ifadeyi boşluğa yazın.",
        .acceptedAnswers = {"a % b", "a%b"},
        .explanation = "Bölümden kalanı hesaplamak için % operatörü kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 124, .topicId = 12,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 22;\nint b = 6;\nstd::cout << a % b;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4"},
        .explanation = "22'nin 6'ya bölümünden kalan 4'tür (22 = 6*3 + 4).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 125, .topicId = 12,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 14;\nint b = 4;\nstd::cout << a / b << \" \" << a % b;\nYukarıdaki kodun ekran çıktısı nedir? (aralarında bir boşluk olacak şekilde yazın)",
        .acceptedAnswers = {"3 2"},
        .explanation = "14 / 4 = 3 (tam sayı bölmesi), 14 % 4 = 2 (kalan); çıktı '3 2' olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 126, .topicId = 12,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\ndouble kalan = 10.5 % 3;\nstd::cout << kalan;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int kalan = 10 % 3;"},
        .explanation = "% operatörü ondalıklı sayılarla kullanılamaz; işlenenler tam sayı olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 127, .topicId = 12,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint kalan = 8 % 0;\nstd::cout << kalan;\n\nBu kod çalışma zamanında (runtime) çökmeye neden olur. Hatalı satırı, 8'in 4'e göre modunu alacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int kalan = 8 % 4;"},
        .explanation = "0'a mod almak (tıpkı 0'a bölmek gibi) tanımsız davranışa ve çökmeye yol açar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 128, .topicId = 12,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint kalan = 20 %% 6;\nstd::cout << kalan;\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int kalan = 20 % 6;"},
        .explanation = "Mod operatörü tek bir % işaretiyle yazılır, %% ile değil.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 129, .topicId = 12,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir sayının çift olup olmadığını kontrol edip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << ciftMi;", "bool ciftMi = (sayi % 2 == 0);", "int sayi = 12;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce sayi tanımlanır, sonra çiftlik kontrolü yapılır, en son sonuç yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 130, .topicId = 12,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir tam sayı okuyup, bu sayının çift mi tek mi olduğunu (mod operatörünü kullanarak) ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "%", "cout", "<<"},
        .explanation = "Program sayıyı cin >> ile okumalı, % 2 ile çift/tek kontrolü yapmalı ve cout << ile sonucu yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 13: Kısaltılmış atama operatörleri
    questions.push_back(Question{
        .id = 131, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "int a = 5; a += 3; işleminden sonra a kaç olur?",
        .options = {"8", "3", "53", "15"},
        .acceptedAnswers = {"a"},
        .explanation = "a += 3, a = a + 3 ile aynıdır; 5 + 3 = 8.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 132, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "a += 5; ifadesi aşağıdakilerden hangisiyle aynı anlama gelir?",
        .options = {"a = 5;", "a = a + 5;", "a = a - 5;", "a += a;"},
        .acceptedAnswers = {"b"},
        .explanation = "+= operatörü, a = a + 5; ifadesinin kısaltılmış halidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 133, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int a = 10; a -= 4; işleminden sonra a kaç olur?",
        .options = {"14", "6", "-4", "40"},
        .acceptedAnswers = {"b"},
        .explanation = "a -= 4, a = a - 4 ile aynıdır; 10 - 4 = 6.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 134, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 4; a *= 3; işleminden sonra a kaç olur?",
        .options = {"7", "12", "1", "34"},
        .acceptedAnswers = {"b"},
        .explanation = "a *= 3, a = a * 3 ile aynıdır; 4 * 3 = 12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 135, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 20; a /= 4; işleminden sonra a kaç olur?",
        .options = {"5", "16", "80", "24"},
        .acceptedAnswers = {"a"},
        .explanation = "a /= 4, a = a / 4 ile aynıdır; 20 / 4 = 5.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 136, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 10; a %= 3; işleminden sonra a kaç olur?",
        .options = {"3", "1", "0", "7"},
        .acceptedAnswers = {"b"},
        .explanation = "a %= 3, a = a % 3 ile aynıdır; 10 % 3 = 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 137, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 6; a *= 2 + 1; işleminden sonra a kaç olur?",
        .options = {"13", "18", "7", "9"},
        .acceptedAnswers = {"b"},
        .explanation = "a *= 2 + 1, a = a * (2 + 1) anlamına gelir; sağ taraf tamamen hesaplanır (3), sonra 6 * 3 = 18.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 138, .topicId = 13,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 8; a /= 2; a += 3; işlemlerinden sonra a kaç olur?",
        .options = {"7", "11", "4", "8"},
        .acceptedAnswers = {"a"},
        .explanation = "Önce a /= 2 ile a = 4 olur, sonra a += 3 ile a = 7 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 139, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "a += 5; ifadesi, a = a + 5; ile aynı işi yapar.",
        .acceptedAnswers = {"1"},
        .explanation = "+= operatörü tam olarak bu anlama gelir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 140, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "*= operatörü, bir değişkeni belirtilen değere böler.",
        .acceptedAnswers = {"2"},
        .explanation = "*= operatörü böler değil, çarpar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 141, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Kısaltılmış atama operatörleri kod tekrarını azaltır.",
        .acceptedAnswers = {"1"},
        .explanation = "Değişken adını iki kez yazmak yerine kısaltılmış operatör kullanılabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 142, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; a -= 2; işleminden sonra a'nın değeri 3'tür.",
        .acceptedAnswers = {"1"},
        .explanation = "5 - 2 = 3.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 143, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int a = 9; a %= 4; işleminden sonra a'nın değeri 2'dir.",
        .acceptedAnswers = {"2"},
        .explanation = "9 % 4 = 1'dir, 2 değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 144, .topicId = 13,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "a *= b + 1; ifadesi, a = a * b + 1; ile tamamen aynı sonucu üretir.",
        .acceptedAnswers = {"2"},
        .explanation = "a *= b + 1, a = a * (b + 1) anlamına gelir; bu genellikle a * b + 1'den farklıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 145, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int puan = 10; puan _____ 5; ifadesinin puan'ı 15 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"+="},
        .explanation = "10 + 5 = 15 olduğu için += operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 146, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int puan = 10; puan _____ 4; ifadesinin puan'ı 6 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"-="},
        .explanation = "10 - 4 = 6 olduğu için -= operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 147, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int puan = 5; puan _____ 4; ifadesinin puan'ı 20 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"*="},
        .explanation = "5 * 4 = 20 olduğu için *= operatörü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 148, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 20; puan _____ 5; ifadesinin puan'ı 4 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"/="},
        .explanation = "20 / 5 = 4 olduğu için /= operatörü kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 149, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 17; puan _____ 5; ifadesinin puan'ı 2 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"%="},
        .explanation = "17 % 5 = 2 olduğu için %= operatörü kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 150, .topicId = 13,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 6; a += a; işleminden sonra a'nın yeni değeri _____ olur (sayı olarak yazın).",
        .acceptedAnswers = {"12"},
        .explanation = "a += a, a = a + a anlamına gelir; 6 + 6 = 12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 151, .topicId = 13,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int bakiye = 100;\n_____\nstd::cout << bakiye;\nKullanıcının hesabından 30 birim çekildiğini (bakiye'yi azaltarak) gösteren satırı yazın.",
        .acceptedAnswers = {"bakiye -= 30;"},
        .explanation = "Bakiyeden düşme işlemi -= operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 152, .topicId = 13,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int toplam = 0;\nfor (int i = 0; i < 3; i++) {\n    _____\n}\nHer döngüde toplam değişkenine i'nin eklenmesini sağlayan satırı yazın.",
        .acceptedAnswers = {"toplam += i;"},
        .explanation = "toplam += i, toplam = toplam + i anlamına gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 153, .topicId = 13,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5;\na += 3;\na *= 2;\nstd::cout << a;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"16"},
        .explanation = "5 + 3 = 8, ardından 8 * 2 = 16.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 154, .topicId = 13,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 10;\na -= 2;\na /= 4;\na += 1;\nstd::cout << a;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "10 - 2 = 8, 8 / 4 = 2, 2 + 1 = 3.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 155, .topicId = 13,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 10;\na =+ 5;\nstd::cout << a;\n\nProgramcı a'nın 15 olmasını istiyor ama kod farklı çalışıyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a += 5;"},
        .explanation = "=+ operatörü diye bir şey yoktur; bu aslında a = (+5) anlamına gelir ve a'yı 5 yapar. Doğrusu a += 5;'tir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 156, .topicId = 13,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 5;\na *= 2 + 3;\nstd::cout << a;\n\nProgramcı önce a'yı 2 ile çarpıp sonra 3 eklemek istiyor (sonuç 13 olsun istiyor) ama kod a'yı 5 ile çarpıyor (sonuç 25 oluyor). Hatalı satırı, programcının istediği sonucu (13) verecek şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a = a * 2 + 3;"},
        .explanation = "a *= 2 + 3 aslında a = a * (2 + 3) anlamına gelir; istenen sonuç için açıkça a = a * 2 + 3; yazılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 157, .topicId = 13,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint a = 10;\na =- 3;\nstd::cout << a;\n\nProgramcı a'nın 7 olmasını istiyor. Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"a -= 3;"},
        .explanation = "=- operatörü diye bir şey yoktur; bu a = (-3) anlamına gelir. Doğrusu a -= 3;'tür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 158, .topicId = 13,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir bakiyeye para ekleyip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << bakiye;", "bakiye += 50;", "int bakiye = 100;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce bakiye tanımlanır, sonra üzerine eklenir, en son yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 159, .topicId = 13,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir tam sayı okuyup, bu sayıya kısaltılmış atama operatörlerini (+=, *= gibi) kullanarak önce 10 ekleyen, sonra 2 ile çarpan bir program yazın; sonucu ekrana yazdırın.",
        .acceptedAnswers = {"cin", ">>", "+=", "*=", "cout", "<<"},
        .explanation = "Program sayıyı cin >> ile okumalı, += 10 ve *= 2 işlemlerini uygulamalı, sonucu cout << ile yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 14: ++ ve --
    questions.push_back(Question{
        .id = 160, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "int a = 5; a++; işleminden sonra a kaç olur?",
        .options = {"5", "6", "4", "55"},
        .acceptedAnswers = {"b"},
        .explanation = "a++, a'yı 1 artırır; 5 + 1 = 6.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 161, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "++ operatörü ne işe yarar?",
        .options = {"Değeri 1 azaltır", "Değeri 2 katına çıkarır", "Değeri 1 artırır", "Değeri sıfırlar"},
        .acceptedAnswers = {"c"},
        .explanation = "++ operatörü bir değişkenin değerini 1 artırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 162, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; --a; işleminden sonra a kaç olur?",
        .options = {"4", "5", "6", "-5"},
        .acceptedAnswers = {"a"},
        .explanation = "--a, a'yı 1 azaltır; 5 - 1 = 4.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 163, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = a++; işleminden sonra b kaç olur?",
        .options = {"5", "6", "4", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "Sondan artırma (a++), b'ye önce a'nın eski değerini (5) atar, sonra a'yı artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 164, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = ++a; işleminden sonra b kaç olur?",
        .options = {"5", "6", "4", "7"},
        .acceptedAnswers = {"b"},
        .explanation = "Önden artırma (++a), önce a'yı artırır (6 olur), sonra bu güncel değeri b'ye atar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 165, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = a++; işleminden sonra a'nın değeri kaç olur?",
        .options = {"5", "6", "4", "7"},
        .acceptedAnswers = {"b"},
        .explanation = "Sondan artırmada da a'nın kendisi 1 artar; b'nin ne aldığından bağımsız olarak a 6 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 166, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 10; a--; --a; a++; işlemlerinden sonra a kaç olur?",
        .options = {"9", "8", "10", "11"},
        .acceptedAnswers = {"a"},
        .explanation = "10 - 1 = 9 (a--), 9 - 1 = 8 (--a), 8 + 1 = 9 (a++); üç ayrı işlemden sonra a'nın son değeri 9'dur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 167, .topicId = 14,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 3;\na++;\na++;\n--a;\nstd::cout << a;\nifadesinin sonucu (a'nın son değeri) kaçtır?",
        .options = {"3", "4", "5", "6"},
        .acceptedAnswers = {"b"},
        .explanation = "3 + 1 = 4, 4 + 1 = 5, 5 - 1 = 4.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 168, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "++ operatörü bir değişkenin değerini 1 artırır.",
        .acceptedAnswers = {"1"},
        .explanation = "++ operatörünün işlevi tam olarak budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 169, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "-- operatörü bir değişkenin değerini 2 azaltır.",
        .acceptedAnswers = {"2"},
        .explanation = "-- operatörü değeri 2 değil, 1 azaltır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 170, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Önden artırma (++a) ile sondan artırma (a++), tek başına bir satırda kullanıldıklarında aynı sonucu üretir (a'nın son değeri açısından).",
        .acceptedAnswers = {"1"},
        .explanation = "Her iki durumda da a bir satırın sonunda 1 artmış olur; fark yalnızca ifadenin kendi döndürdüğü değerdedir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 171, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; int b = a++; ifadesinde b'nin değeri 6'dır.",
        .acceptedAnswers = {"2"},
        .explanation = "Sondan artırma, eski değeri (5) döndürür; b 6 değil 5 olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 172, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = ++a; ifadesinde b'nin değeri 6'dır.",
        .acceptedAnswers = {"1"},
        .explanation = "Önden artırma, güncellenmiş değeri (6) döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 173, .topicId = 14,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Sondan artırma (a++), işlemden önceki değeri döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "a++ önce mevcut değeri kullanır/döndürür, sonra a'yı artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 174, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; a_____; ifadesinin a'yı 6 yapması için boşluğa ne yazılmalı? (iki karakterlik operatör)",
        .acceptedAnswers = {"++"},
        .explanation = "a++, a'yı 1 artırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 175, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; a_____; ifadesinin a'yı 4 yapması için boşluğa ne yazılmalı? (iki karakterlik operatör)",
        .acceptedAnswers = {"--"},
        .explanation = "a--, a'yı 1 azaltır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 176, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; int b = a_____; ifadesinden sonra b'nin 5, a'nın ise 6 olması isteniyor (sondan artırma). Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "Sondan artırma (a++), eski değeri b'ye verir, sonra a'yı artırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 177, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = _____a; ifadesinden sonra hem a'nın hem de b'nin 6 olması isteniyor (önden artırma). Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "Önden artırma (++a), önce a'yı artırır, sonra bu güncel değeri b'ye de verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 178, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 0; for (int i = 0; i < 5; i_____) { a += i; } ifadesinde döngü sayacının her adımda 1 artması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "Döngü sayacı genellikle i++ ile artırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 179, .topicId = 14,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 8; a_____; a_____; işlemlerinden sonra a'nın 6 olması için boşluğa (iki kez tekrar edilecek) ne yazılmalı?",
        .acceptedAnswers = {"--"},
        .explanation = "8'i iki kez 1 azaltmak 6 verir (8 - 1 - 1 = 6); bu -- operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 180, .topicId = 14,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayac = 0;\n_____\nstd::cout << sayac;\nsayac değişkenini önden artırma operatörüyle 1 artıran satırı yazın.",
        .acceptedAnswers = {"++sayac;"},
        .explanation = "Önden artırma ++sayac; şeklinde yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 181, .topicId = 14,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int i = 10;\nwhile (i > 0) {\n    _____\n}\nHer döngüde i'yi 1 azaltan satırı yazın (sonsuz döngüyü önlemek için gerekli).",
        .acceptedAnswers = {"i--;", "--i;"},
        .explanation = "i'yi 1 azaltmak için i-- veya --i kullanılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 182, .topicId = 14,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 4;\nstd::cout << a++;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4"},
        .explanation = "Sondan artırma, ekrana yazdırmadan önceki değeri (4) verir; a daha sonra 5 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 183, .topicId = 14,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 4;\nstd::cout << ++a;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"5"},
        .explanation = "Önden artırma, önce a'yı 5 yapar, sonra bu güncel değeri yazdırır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 184, .topicId = 14,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 5;\na++\nstd::cout << a;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a++;"},
        .explanation = "a++ satırının sonunda noktalı virgül eksik.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 185, .topicId = 14,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 5;\na+;\nstd::cout << a;\n\nProgramcı a'yı 1 artırmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a++;"},
        .explanation = "a+; geçersiz bir ifadedir; artırma operatörü ++ şeklinde, tek + değil çift + ile yazılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 186, .topicId = 14,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint a = 10;\na- -;\nstd::cout << a;\n\nProgramcı a'yı 1 azaltmak istiyor. Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"a--;"},
        .explanation = "Azaltma operatörü -- şeklinde, arada boşluk olmadan yazılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 187, .topicId = 14,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir sayacı artırıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << sayac;", "sayac++;", "int sayac = 0;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce sayac tanımlanır, sonra artırılır, en son yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 188, .topicId = 14,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "1'den 5'e kadar olan sayıları, bir sayaç değişkenini artırma operatörü (++) ile kullanarak bir döngüde ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"for", "++", "cout", "<<"},
        .explanation = "Program bir for döngüsü içinde sayacı ++ ile artırmalı ve her adımda cout << ile yazdırmalıdır.",
        .baseXp = 40,
    });
}
```

- [ ] **Step 3: Wire the new function into `QuestionManager`**

In `src/QuestionManager.cpp`, add near the top (after the existing
`#include` lines):

```cpp
#include "QuestionContent.h"
```

Change the constructor's first line from:

```cpp
    questions_.reserve(60);
```

to:

```cpp
    questions_.reserve(362);
```

Then add this as the constructor's final line (after the existing 72
`questions_.push_back(...)` calls, i.e. right before the constructor's
closing `}`):

```cpp
    appendSection2Questions(questions_);
```

- [ ] **Step 4: Register the new files in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/QuestionManager.h
    src/QuestionManager.cpp
```

to:

```cmake
    src/QuestionManager.h
    src/QuestionManager.cpp
    src/QuestionContent.h
    src/QuestionsSection2.cpp
```

- [ ] **Step 5: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `88/88 test(s) passed.` (topics 11-14 now have 116 more
questions, but no existing test currently counts them, so the pass count
is unchanged from Task 1's end state).

- [ ] **Step 6: Commit**

```bash
git add src/QuestionContent.h src/QuestionsSection2.cpp src/QuestionManager.cpp CMakeLists.txt
git commit -m "feat(content): add questions for topics 11-14 (ids 73-188)"
```

---

### Task 3: Questions for topics 15-17 (ids 189-275)

**Files:**
- Modify: `src/QuestionsSection2.cpp` (append more `questions.push_back(...)`
  calls to the existing `appendSection2Questions` function body, right
  before its closing `}`)

**Interfaces:**
- Consumes: `appendSection2Questions`'s existing body from Task 2 (ends
  after topic 14's WriteCode question, id 188).
- Produces: the same function extended through id 275. Task 4 appends
  topics 18-20 after this task's content, same file, same function.

- [ ] **Step 1: Append topics 15-17's questions**

In `src/QuestionsSection2.cpp`, insert the following right before the
function's closing `}` (i.e. immediately after the `id = 188` WriteCode
question added in Task 2):

```cpp
    // Topic 15: Karşılaştırma operatörleri
    questions.push_back(Question{
        .id = 189, .topicId = 15,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "int a = 5; int b = 7; a == b ifadesinin sonucu nedir?",
        .options = {"true", "false", "5", "7"},
        .acceptedAnswers = {"b"},
        .explanation = "5, 7'ye eşit olmadığı için sonuç false'tur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 190, .topicId = 15,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "!= operatörü ne anlama gelir?",
        .options = {"Eşittir", "Eşit değildir", "Küçüktür", "Büyüktür"},
        .acceptedAnswers = {"b"},
        .explanation = "!= operatörü, iki değerin eşit olmadığını kontrol eder.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 191, .topicId = 15,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; int b = 7; a < b ifadesinin sonucu nedir?",
        .options = {"true", "false", "-2", "2"},
        .acceptedAnswers = {"a"},
        .explanation = "5, 7'den küçük olduğu için sonuç true'dur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 192, .topicId = 15,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 8; int b = 8; a >= b ifadesinin sonucu nedir?",
        .options = {"true", "false", "0", "8"},
        .acceptedAnswers = {"a"},
        .explanation = ">= operatörü eşitlik durumunda da true döner; 8, 8'e eşit olduğu için sonuç true'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 193, .topicId = 15,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Karşılaştırma için == yerine yanlışlıkla = kullanılırsa ne olur?",
        .options = {"Derleme hatası her zaman oluşur", "Bazı durumlarda atama yapılıp kod yine de derlenir", "Program her zaman çöker", "Hiçbir fark olmaz"},
        .acceptedAnswers = {"b"},
        .explanation = "if (a = b) gibi bir ifade derlenir; a'ya b'nin değerini atar ve bu atamanın sonucu koşul olarak kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 194, .topicId = 15,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 3; int b = 3; a != b ifadesinin sonucu nedir?",
        .options = {"true", "false", "3", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "a ve b eşit olduğu için != false döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 195, .topicId = 15,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "double a = 0.1 + 0.2; double b = 0.3; a == b ifadesinin sonucu genellikle nedir ve neden?",
        .options = {"true, çünkü matematiksel olarak eşitler", "false, çünkü ondalıklı sayılarda yuvarlama hataları olabilir", "Derleme hatası verir", "Her zaman true döner çünkü ikisi de double'dır"},
        .acceptedAnswers = {"b"},
        .explanation = "Kayan noktalı sayılar ikili tabanda tam temsil edilemeyebilir; bu yüzden == ile doğrudan karşılaştırmak güvenilmezdir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 196, .topicId = 15,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5; int b = 5; int c = 10; (a == b) && (c > b) ifadesinin sonucu nedir?",
        .options = {"true", "false", "5", "10"},
        .acceptedAnswers = {"a"},
        .explanation = "a == b true, c > b (10 > 5) de true olduğu için && ile birleşim true döner.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 197, .topicId = 15,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "== operatörü eşitlik kontrolü yapar.",
        .acceptedAnswers = {"1"},
        .explanation = "== operatörünün amacı budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 198, .topicId = 15,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "= operatörü ile == operatörü aynı işi yapar.",
        .acceptedAnswers = {"2"},
        .explanation = "= atama yapar, == karşılaştırma yapar; ikisi farklı işlemlerdir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 199, .topicId = 15,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "<= operatörü 'küçük veya eşittir' anlamına gelir.",
        .acceptedAnswers = {"1"},
        .explanation = "<= operatörünün anlamı tam olarak budur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 200, .topicId = 15,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; int b = 5; a > b ifadesi true döner.",
        .acceptedAnswers = {"2"},
        .explanation = "a ve b eşit olduğu için a > b false döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 201, .topicId = 15,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Karşılaştırma operatörlerinin sonucu her zaman bool (true/false) türündedir.",
        .acceptedAnswers = {"1"},
        .explanation = "==, !=, <, >, <=, >= operatörleri her zaman bool sonuç döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 202, .topicId = 15,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int a = 4; int b = 9; a >= b ifadesi true döner.",
        .acceptedAnswers = {"2"},
        .explanation = "4, 9'dan küçük olduğu için a >= b false döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 203, .topicId = 15,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; int b = 5; a _____ b ifadesinin true dönmesi (eşitlik kontrolü) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 204, .topicId = 15,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 3; int b = 5; a _____ b ifadesinin true dönmesi (a'nın b'den küçük olduğunu kontrol etmek) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"<"},
        .explanation = "Küçüktür kontrolü < operatörüyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 205, .topicId = 15,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 8; int b = 2; a _____ b ifadesinin true dönmesi (a'nın b'den büyük olduğunu kontrol etmek) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {">"},
        .explanation = "Büyüktür kontrolü > operatörüyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 206, .topicId = 15,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; int b = 5; a _____ b ifadesinin false dönmesi (eşit olmadığını kontrol etmek) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"!="},
        .explanation = "a ve b eşit olduğu için != false döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 207, .topicId = 15,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 7; int b = 7; a _____ b ifadesinin true dönmesi (küçük veya eşit kontrolü) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"<="},
        .explanation = "Eşit değerler için <= true döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 208, .topicId = 15,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 9; int b = 4; a _____ b ifadesinin true dönmesi (büyük veya eşit kontrolü) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {">="},
        .explanation = "9, 4'ten büyük olduğu için >= true döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 209, .topicId = 15,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 20;\nbool resit = _____;\nyas'ın 18'e eşit veya büyük olup olmadığını kontrol eden ifadeyi boşluğa yazın.",
        .acceptedAnswers = {"yas >= 18"},
        .explanation = ">= operatörü büyük veya eşit kontrolü yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 210, .topicId = 15,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 10;\nint b = 20;\nbool esitDegil = _____;\na ile b'nin eşit olmadığını kontrol eden ifadeyi boşluğa yazın.",
        .acceptedAnswers = {"a != b"},
        .explanation = "!= operatörü eşit olmama durumunu kontrol eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 211, .topicId = 15,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 6;\nint b = 9;\nstd::cout << (a < b);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "6, 9'dan küçük olduğu için sonuç true'dur; cout bunu 1 olarak yazdırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 212, .topicId = 15,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5;\nint b = 5;\nstd::cout << (a == b) << (a != b);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "(a == b) true olduğu için 1, (a != b) false olduğu için 0 yazdırılır; birlikte '10' olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 213, .topicId = 15,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint yas = 20;\nif (yas = 18) {\n    std::cout << \"Reşit\";\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (yas == 18) {"},
        .explanation = "Karşılaştırma için == kullanılmalıdır; = bir atamadır ve yas'ı 18 yapıp her zaman true döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 214, .topicId = 15,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 10;\nint b = 20;\nbool sonuc = a =< b;\n\nProgramcı a'nın b'ye eşit veya küçük olup olmadığını kontrol etmek istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"bool sonuc = a <= b;"},
        .explanation = "=< diye bir operatör yoktur; küçük veya eşit kontrolü <= şeklinde yazılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 215, .topicId = 15,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint a = 5;\nint b = 8;\nbool sonuc = a => b;\n\nProgramcı a'nın b'den büyük veya eşit olup olmadığını kontrol etmek istiyor. Düzeltilmiş üçüncü satırı yazın.",
        .acceptedAnswers = {"bool sonuc = a >= b;"},
        .explanation = "=> diye bir operatör yoktur; büyük veya eşit kontrolü >= şeklinde yazılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 216, .topicId = 15,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, iki sayının eşit olup olmadığını kontrol edip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << sonuc;", "bool sonuc = (a == b);", "int a = 5, b = 5;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce değişkenler tanımlanır, sonra karşılaştırma yapılır, en son sonuç yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 217, .topicId = 15,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan iki tam sayı okuyup, bunların birbirine eşit olup olmadığını (karşılaştırma operatörünü kullanarak) ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "==", "cout", "<<"},
        .explanation = "Program iki sayıyı cin >> ile okumalı, == ile karşılaştırmalı ve cout << ile sonucu yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 16: Mantıksal operatörler
    questions.push_back(Question{
        .id = 218, .topicId = 16,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "&& operatörü hangi mantıksal işlemi yapar?",
        .options = {"VEYA", "VE", "DEĞİL", "XOR"},
        .acceptedAnswers = {"b"},
        .explanation = "&& operatörü mantıksal VE işlemini yapar; her iki koşul da doğruysa true döner.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 219, .topicId = 16,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "|| operatörü hangi mantıksal işlemi yapar?",
        .options = {"VE", "VEYA", "DEĞİL", "XOR"},
        .acceptedAnswers = {"b"},
        .explanation = "|| operatörü mantıksal VEYA işlemini yapar; koşullardan en az biri doğruysa true döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 220, .topicId = 16,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "! operatörü ne işe yarar?",
        .options = {"İki koşulu birleştirir", "Bir koşulun tersini alır", "Sayıyı negatif yapar", "Karşılaştırma yapar"},
        .acceptedAnswers = {"b"},
        .explanation = "! operatörü bir bool ifadenin tersini (true ise false, false ise true) alır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 221, .topicId = 16,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "true && false ifadesinin sonucu nedir?",
        .options = {"true", "false", "1 ve 0", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "&& operatöründe her iki taraf da true olmalıdır; burada biri false olduğu için sonuç false'tur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 222, .topicId = 16,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "true || false ifadesinin sonucu nedir?",
        .options = {"true", "false", "0", "Hata"},
        .acceptedAnswers = {"a"},
        .explanation = "|| operatöründe en az biri true ise sonuç true'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 223, .topicId = 16,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "!true ifadesinin sonucu nedir?",
        .options = {"true", "false", "0 ve 1", "1"},
        .acceptedAnswers = {"b"},
        .explanation = "! operatörü true'nun tersini alır, sonuç false'tur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 224, .topicId = 16,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int yas = 20; bool ogrenci = false; (yas < 18 || ogrenci) ifadesinin sonucu nedir?",
        .options = {"true", "false", "20", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "yas < 18 false, ogrenci de false olduğu için || ile birleşim false döner.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 225, .topicId = 16,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5; int b = 10; int c = 15; (a < b && b < c) ifadesinin sonucu nedir?",
        .options = {"true", "false", "5", "15"},
        .acceptedAnswers = {"a"},
        .explanation = "a < b true (5 < 10), b < c true (10 < 15); her ikisi de true olduğu için && sonucu true'dur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 226, .topicId = 16,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "&& operatörü her iki koşul da doğruysa true döner.",
        .acceptedAnswers = {"1"},
        .explanation = "&& operatörünün tanımı budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 227, .topicId = 16,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "|| operatörü yalnızca her iki koşul da doğruysa true döner.",
        .acceptedAnswers = {"2"},
        .explanation = "|| operatörü koşullardan en az biri doğruysa true döner, ikisinin de doğru olması gerekmez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 228, .topicId = 16,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "! operatörü bir bool ifadenin tersini alır.",
        .acceptedAnswers = {"1"},
        .explanation = "! operatörünün işlevi tam olarak budur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 229, .topicId = 16,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "true && true ifadesinin sonucu false'tur.",
        .acceptedAnswers = {"2"},
        .explanation = "İki taraf da true olduğu için && sonucu true'dur, false değil.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 230, .topicId = 16,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "false || false ifadesinin sonucu false'tur.",
        .acceptedAnswers = {"1"},
        .explanation = "Her iki taraf da false olduğu için || sonucu false'tur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 231, .topicId = 16,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "&& ve || operatörleri, karşılaştırma operatörlerinin (==, <, > gibi) sonuçlarıyla birlikte kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Karşılaştırma operatörlerinin sonucu bool olduğu için, bu sonuçlar && ve || ile birleştirilebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 232, .topicId = 16,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "bool a = true; bool b = false; bool sonuc = a _____ b; ifadesinin sonucunun false olması (her ikisi de doğru olmalı mantığı) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"&&"},
        .explanation = "&& operatöründe bir taraf false ise sonuç false olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 233, .topicId = 16,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "bool a = true; bool b = false; bool sonuc = a _____ b; ifadesinin sonucunun true olması (en az biri doğru mantığı) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"||"},
        .explanation = "|| operatöründe bir taraf true ise sonuç true olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 234, .topicId = 16,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "bool a = false; bool sonuc = _____a; ifadesinin sonucunun true olması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"!"},
        .explanation = "! operatörü false'un tersini alarak true yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 235, .topicId = 16,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 25; bool sonuc = (yas >= 18 _____ yas <= 65); ifadesinin 'yas 18 ile 65 arasında (her ikisi dahil)' kontrolü yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"&&"},
        .explanation = "İki koşulun da sağlanması gerektiği için && kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 236, .topicId = 16,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 95; bool basarili = (puan >= 90 _____ puan == 100); ifadesinin '90 ve üzeri VEYA tam 100' kontrolü yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"||"},
        .explanation = "Koşullardan birinin sağlanması yeterli olduğu için || kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 237, .topicId = 16,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "bool girisYapildi = false; if (_____girisYapildi) { std::cout << \"Giriş yapılmadı\"; } ifadesinin girisYapildi false iken çalışması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"!"},
        .explanation = "! operatörü girisYapildi'nin tersini alır; false'un tersi true olduğu için blok çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 238, .topicId = 16,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 30;\nbool ehliyetVar = true;\nbool arabaKullanabilir = _____;\nyas'ın 18'den büyük veya eşit VE ehliyetVar'ın true olduğunu kontrol eden ifadeyi yazın.",
        .acceptedAnswers = {"yas >= 18 && ehliyetVar"},
        .explanation = "İki koşulun birlikte sağlanması gerektiği için && kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 239, .topicId = 16,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 40;\nbool tekrarSinavi = _____;\npuan'ın 50'den küçük olduğunu kontrol eden (ve DEĞİL operatörü kullanmadan) ifadeyi yazın.",
        .acceptedAnswers = {"puan < 50"},
        .explanation = "Doğrudan < operatörüyle küçüklük kontrolü yapılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 240, .topicId = 16,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "bool a = true;\nbool b = false;\nstd::cout << (a && b);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0"},
        .explanation = "b false olduğu için && sonucu false'tur; cout bunu 0 olarak yazdırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 241, .topicId = 16,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int yas = 16;\nbool ogrenci = true;\nstd::cout << (yas < 18 || !ogrenci);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "yas < 18 true olduğu için || ifadesinin tamamı true olur (ikinci koşul ne olursa olsun); cout bunu 1 olarak yazdırır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 242, .topicId = 16,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nbool a = true;\nbool b = false;\nbool sonuc = a & b;\n\nProgramcı mantıksal VE işlemi yapmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"bool sonuc = a && b;"},
        .explanation = "Tek & işareti bitwise (bit düzeyinde) VE anlamına gelir; mantıksal VE için çift && kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 243, .topicId = 16,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint yas = 20;\nbool sonuc = yas > 18 | yas < 65;\n\nProgramcı 'VEYA' mantığı ile kontrol yapmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"bool sonuc = yas > 18 || yas < 65;"},
        .explanation = "Tek | işareti bitwise (bit düzeyinde) VEYA anlamına gelir; mantıksal VEYA için çift || kullanılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 244, .topicId = 16,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nbool a = true;\nbool sonuc = !!a;\n\nProgramcı a'nın tersini (false) almak istiyor ama !! iki kere ters aldığı için sonuc true kalıyor. Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"bool sonuc = !a;"},
        .explanation = "Tek ! yeterlidir; iki kez ! kullanmak orijinal değere geri döner.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 245, .topicId = 16,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, iki koşulu birlikte kontrol edip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << erisimVar;", "bool erisimVar = (yasLimit && sifreDogru);", "bool yasLimit = true, sifreDogru = true;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce değişkenler tanımlanır, sonra birleşik koşul hesaplanır, en son sonuç yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 246, .topicId = 16,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir yaş okuyup, yaşın 18 ile 65 arasında (her ikisi dahil, && operatörünü kullanarak) olup olmadığını ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "&&", "cout", "<<"},
        .explanation = "Program yaşı cin >> ile okumalı, && ile iki koşulu birleştirmeli ve cout << ile sonucu yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 17: if
    questions.push_back(Question{
        .id = 247, .topicId = 17,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "if ifadesi ne zaman çalışır?",
        .options = {"Her zaman", "Koşul true olduğunda", "Koşul false olduğunda", "Program başladığında"},
        .acceptedAnswers = {"b"},
        .explanation = "if bloğu yalnızca koşul true olduğunda çalışır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 248, .topicId = 17,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "if (kosul) { ... } yapısında kosul false ise ne olur?",
        .options = {"Blok yine de çalışır", "Blok atlanır", "Program çöker", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "Koşul false ise if bloğunun içindeki kod hiç çalışmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 249, .topicId = 17,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int yas = 15; if (yas >= 18) { std::cout << \"Reşit\"; } kodu ne yazdırır?",
        .options = {"Reşit", "Hiçbir şey", "Hata", "15"},
        .acceptedAnswers = {"b"},
        .explanation = "yas 15 olduğu için koşul false'tur; blok çalışmaz, hiçbir şey yazdırılmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 250, .topicId = 17,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "if satırının sonuna yanlışlıkla ; konursa ne olur?",
        .options = {"Kod derlenmez", "Blok koşuldan bağımsız olarak (her zaman) çalışmış gibi davranır", "Hiçbir fark olmaz", "Program çöker"},
        .acceptedAnswers = {"b"},
        .explanation = "; if'in kontrol ettiği boş bir ifade olur; sonraki satır artık koşuldan bağımsız olarak her zaman çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 251, .topicId = 17,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 60; if (puan >= 50) std::cout << \"Geçti\"; kodunda süslü parantez olmadan kaç satır if'e bağlıdır?",
        .options = {"Hiçbiri", "Sadece bir sonraki satır", "Sonraki tüm satırlar", "İki satır"},
        .acceptedAnswers = {"b"},
        .explanation = "Süslü parantez olmadan if yalnızca kendinden sonraki tek bir ifadeye bağlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 252, .topicId = 17,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "if (a > 0) { b = 1; c = 2; } yapısında a <= 0 olduğunda b ve c'nin değerleri ne olur?",
        .options = {"b=1, c=2 olur", "Değişmez (blok hiç çalışmaz)", "b=0, c=0 olur", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "Koşul false olduğunda blok atlanır; b ve c'nin değerleri değişmeden kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 253, .topicId = 17,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5; if (a) { std::cout << \"Doğru\"; } kodu ne yazdırır (a bir int, bool bağlamında kullanılıyor)?",
        .options = {"Doğru", "Hiçbir şey", "Derleme hatası", "5"},
        .acceptedAnswers = {"a"},
        .explanation = "0 dışındaki her tam sayı if koşulunda true olarak değerlendirilir; a=5 sıfır olmadığı için blok çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 254, .topicId = 17,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 0; if (a) { std::cout << \"Doğru\"; } else { std::cout << \"Yanlış\"; } kodu ne yazdırır?",
        .options = {"Doğru", "Yanlış", "Hiçbir şey", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "a=0, if koşulunda false olarak değerlendirilir; bu yüzden else bloğu çalışır ve 'Yanlış' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 255, .topicId = 17,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "if ifadesi, koşul true olduğunda kod bloğunu çalıştırır.",
        .acceptedAnswers = {"1"},
        .explanation = "if ifadesinin temel işlevi budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 256, .topicId = 17,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "if ifadesinin koşulu her zaman bir sayı olmalıdır, bool olamaz.",
        .acceptedAnswers = {"2"},
        .explanation = "if koşulu bool ifadeler için tasarlanmıştır (sayılar da bool'a örtük dönüştürülerek kullanılabilir).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 257, .topicId = 17,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "if satırının sonuna noktalı virgül koymak zararsızdır ve hiçbir etkisi yoktur.",
        .acceptedAnswers = {"2"},
        .explanation = "Bu, sonraki bloğun koşuldan bağımsız her zaman çalışmasına yol açan ciddi bir hatadır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 258, .topicId = 17,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Süslü parantez kullanılmadığında if yalnızca bir sonraki satıra bağlanır.",
        .acceptedAnswers = {"1"},
        .explanation = "Süslü parantez olmadan if, kendinden sonraki tek bir ifadeyi kontrol eder.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 259, .topicId = 17,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "if (yas = 18) ifadesi bir karşılaştırma değil, bir atamadır.",
        .acceptedAnswers = {"1"},
        .explanation = "Tek = işareti atama yapar; karşılaştırma için == kullanılmalıydı.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 260, .topicId = 17,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "C++'ta 0 dışındaki her tam sayı, if koşulunda 'doğru' (true) olarak değerlendirilir.",
        .acceptedAnswers = {"1"},
        .explanation = "if koşulunda sayılar bool'a dönüştürülür; 0 false, 0 dışındaki her değer true'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 261, .topicId = 17,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ (yas >= 18) {\n    std::cout << \"Reşit\";\n}\nBir koşula bağlı kod bloğu çalıştırmak için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"if"},
        .explanation = "Koşullu blok if anahtar kelimesiyle başlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 262, .topicId = 17,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "if (puan >= 50) _____\n    std::cout << \"Geçti\";\nBloğu açan karakteri boşluğa yazın.",
        .acceptedAnswers = {"{"},
        .explanation = "Kod bloğu açılış süslü parantezi { ile başlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 263, .topicId = 17,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "if (yas >= 18) {\n    std::cout << \"Reşit\";\n_____\nBloğu kapatan karakteri boşluğa yazın.",
        .acceptedAnswers = {"}"},
        .explanation = "Kod bloğu kapanış süslü parantezi } ile biter.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 264, .topicId = 17,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "if (a _____ b) {\n    std::cout << \"Eşit\";\n}\na ile b'nin eşit olup olmadığını kontrol etmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 265, .topicId = 17,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 20;\nif (yas _____ 18) {\n    std::cout << \"Reşit\";\n}\nyas'ın 18'e eşit veya büyük olduğunu kontrol etmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {">="},
        .explanation = "Büyük veya eşit kontrolü >= operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 266, .topicId = 17,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 7;\nif (sayi % 2 _____ 1) {\n    std::cout << \"Tek\";\n}\nsayi'nın tek olduğunu kontrol etmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "sayi % 2'nin 1'e eşit olup olmadığı == ile kontrol edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 267, .topicId = 17,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 20;\n_____ {\n    std::cout << \"Reşit\";\n}\nyas'ın 18'den büyük veya eşit olduğunu kontrol eden if satırını yazın.",
        .acceptedAnswers = {"if (yas >= 18)"},
        .explanation = "if satırı koşulu parantez içinde belirtir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 268, .topicId = 17,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sifre = 1234;\nint girilen = 1234;\n_____ {\n    std::cout << \"Doğru şifre\";\n}\nsifre ile girilen'in eşit olduğunu kontrol eden if satırını yazın.",
        .acceptedAnswers = {"if (sifre == girilen)"},
        .explanation = "Eşitlik kontrolü == operatörüyle if satırında yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 269, .topicId = 17,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 40;\nif (puan >= 50) {\n    std::cout << \"Geçti\";\n}\nstd::cout << \"Bitti\";\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Bitti"},
        .explanation = "puan 50'den küçük olduğu için if bloğu çalışmaz; sadece 'Bitti' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 270, .topicId = 17,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5;\nif (a > 0)\n    std::cout << \"Pozitif\";\n    std::cout << \"İkinci satır\";\nYukarıdaki kodun ekran çıktısı nedir? (süslü parantez olmadığına dikkat edin)",
        .acceptedAnswers = {"Pozitifİkinci satır"},
        .explanation = "Süslü parantez olmadığı için if yalnızca ilk cout satırına bağlanır; ikinci cout satırı koşuldan bağımsız her zaman çalışır. a > 0 true olduğu için ikisi de yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 271, .topicId = 17,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint yas = 10;\nif (yas >= 18);\n    std::cout << \"Reşit\";\n\nProgramcı yas 18'den küçükken 'Reşit' yazdırılmamasını bekliyor ama yas 10 iken bile 'Reşit' yazdırılıyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (yas >= 18)"},
        .explanation = "if satırının sonundaki fazladan noktalı virgül, if'in kontrol ettiği ifadeyi boş bir ifade yapar; bu yüzden sonraki cout satırı koşuldan bağımsız olarak her zaman çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 272, .topicId = 17,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint puan = 80;\nif (puan = 90) {\n    std::cout << \"Mükemmel\";\n}\n\nProgramcı puan'ın 90'a eşit olup olmadığını kontrol etmek istiyor ama kod her zaman 'Mükemmel' yazdırıyor (ve puan'ı da 90 yapıyor). Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (puan == 90) {"},
        .explanation = "Tek = işareti atama yapar ve 90 sıfır olmadığı için her zaman true olur; karşılaştırma için == kullanılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 273, .topicId = 17,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint yas = 16;\nif yas >= 18 {\n    std::cout << \"Reşit\";\n}\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"if (yas >= 18) {"},
        .explanation = "if koşulu her zaman parantez içine yazılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 274, .topicId = 17,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, yaş kontrolü yapan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"}", "if (yas >= 18) {", "std::cout << \"Reşit\";", "int yas = 20;"},
        .acceptedAnswers = {"4 2 3 1"},
        .explanation = "Önce değişken tanımlanır (4), sonra if satırı (2), blok içeriği (3), en son kapanış (1): sıra 4 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 275, .topicId = 17,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir not (0-100 arası) okuyup, notun 50'den büyük veya eşit olması durumunda 'Geçti' yazdıran bir program yazın (if kullanarak).",
        .acceptedAnswers = {"cin", ">>", "if", "cout", "<<"},
        .explanation = "Program notu cin >> ile okumalı, if (not >= 50) ile kontrol etmeli ve cout << ile 'Geçti' yazdırmalıdır.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `88/88 test(s) passed.` (unchanged from Task 2 — no existing test
yet counts these topics' questions).

- [ ] **Step 3: Commit**

```bash
git add src/QuestionsSection2.cpp
git commit -m "feat(content): add questions for topics 15-17 (ids 189-275)"
```

---

### Task 4: Questions for topics 18-20 (ids 276-362), test updates, and final integration

**Files:**
- Modify: `src/QuestionsSection2.cpp` (append the final
  `questions.push_back(...)` calls, right before the function's closing
  `}`)
- Modify: `tests/QuestionManagerTests.cpp` (widen the duplicate-id check,
  add a new per-topic minimum-count test)
- Modify: `docs/superpowers/roadmap.md` (mark Phase 13 complete)

**Interfaces:**
- Consumes: `appendSection2Questions`'s body from Tasks 2-3 (ends after
  topic 17's WriteCode question, id 275).
- Produces: the complete, final `appendSection2Questions` function
  (ids 73-362, 290 questions across topics 11-20).

- [ ] **Step 1: Append topics 18-20's questions**

In `src/QuestionsSection2.cpp`, insert the following right before the
function's closing `}` (i.e. immediately after the `id = 275` WriteCode
question added in Task 3):

```cpp
    // Topic 18: if-else
    questions.push_back(Question{
        .id = 276, .topicId = 18,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "if-else yapısında koşul false olduğunda hangi blok çalışır?",
        .options = {"if bloğu", "else bloğu", "İkisi de", "Hiçbiri"},
        .acceptedAnswers = {"b"},
        .explanation = "Koşul false olduğunda if bloğu atlanır ve else bloğu çalışır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 277, .topicId = 18,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "if-else yapısında aynı anda kaç blok çalışabilir?",
        .options = {"0", "1", "2", "Koşula bağlı olarak 0,1 veya 2"},
        .acceptedAnswers = {"b"},
        .explanation = "if-else yapısında if ve else bloklarından tam olarak biri çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 278, .topicId = 18,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int not_ = 40; if (not_ >= 50) { std::cout << \"Geçti\"; } else { std::cout << \"Kaldı\"; } kodu ne yazdırır?",
        .options = {"Geçti", "Kaldı", "Hiçbir şey", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "not_ 50'den küçük olduğu için koşul false'tur; else bloğu çalışır ve 'Kaldı' yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 279, .topicId = 18,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "else bloğu if bloğundan bağımsız olarak, kendi koşuluna sahip olabilir mi?",
        .options = {"Evet, her zaman kendi koşulu vardır", "Hayır, else kendi koşulunu alamaz (koşulsuzdur)", "Sadece else if ile olur", "Sadece döngülerde olur"},
        .acceptedAnswers = {"b"},
        .explanation = "else, parantez içinde bir koşul almaz; her zaman if'in koşulu false olduğunda çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 280, .topicId = 18,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "if-else zincirinde, if koşulu true ise else bloğunda ne olur?",
        .options = {"Yine de çalışır", "Atlanır, hiç çalışmaz", "Derleme hatası oluşur", "Program çöker"},
        .acceptedAnswers = {"b"},
        .explanation = "if koşulu true olduğunda else bloğu hiç çalışmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 281, .topicId = 18,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 18; if (yas < 18) { std::cout << \"Çocuk\"; } else { std::cout << \"Yetişkin\"; } kodu ne yazdırır?",
        .options = {"Çocuk", "Yetişkin", "Hiçbir şey", "18"},
        .acceptedAnswers = {"b"},
        .explanation = "yas 18'e eşit olduğu için yas < 18 false'tur; else bloğu çalışır ve 'Yetişkin' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 282, .topicId = 18,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5; if (a > 10) { std::cout << \"Büyük\"; } else if (a > 3) { std::cout << \"Orta\"; } else { std::cout << \"Küçük\"; } kodu ne yazdırır?",
        .options = {"Büyük", "Orta", "Küçük", "Hiçbir şey"},
        .acceptedAnswers = {"b"},
        .explanation = "a > 10 false, a > 3 true olduğu için ikinci blok çalışır ve 'Orta' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 283, .topicId = 18,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "if (a > 0) { std::cout << \"A\"; } else { std::cout << \"B\"; } std::cout << \"C\"; kodunda a = -1 iken ekran çıktısı nedir?",
        .options = {"AC", "BC", "ABC", "C"},
        .acceptedAnswers = {"b"},
        .explanation = "a <= 0 olduğu için else bloğu çalışır ('B'), ardından koşuldan bağımsız 'C' her zaman yazdırılır; sonuç 'BC'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 284, .topicId = 18,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "if-else yapısında if ve else bloklarından tam olarak biri çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Koşula göre ya if ya da else bloğu çalışır, ikisi birden değil.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 285, .topicId = 18,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "else bloğunun kendi koşulu (parantez içinde) vardır.",
        .acceptedAnswers = {"2"},
        .explanation = "else koşulsuzdur; yalnızca if'in koşulu false olduğunda çalışır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 286, .topicId = 18,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "if koşulu true olduğunda else bloğu da çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "if koşulu true olduğunda yalnızca if bloğu çalışır, else bloğu atlanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 287, .topicId = 18,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "else, bir if'in hemen ardından gelmelidir (arada başka bir ifade olmamalıdır).",
        .acceptedAnswers = {"1"},
        .explanation = "else, doğrudan ilgili if bloğunun kapanışından sonra yazılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 288, .topicId = 18,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "if-else yapısı, aynı koşulu iki farklı if ile yazmaktan daha güvenlidir çünkü tam olarak bir yolun çalışmasını garanti eder.",
        .acceptedAnswers = {"1"},
        .explanation = "İki ayrı if kullanmak, ikisinin de yanlışlıkla çalışabileceği durumlara açıktır; if-else bunu engeller.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 289, .topicId = 18,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5; if (a > 0) { std::cout << \"Poz\"; } else { std::cout << \"Neg\"; } kodu hem 'Poz' hem 'Neg' yazdırır.",
        .acceptedAnswers = {"2"},
        .explanation = "if-else yapısında yalnızca bir blok çalışır; burada yalnızca 'Poz' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 290, .topicId = 18,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "if (yas >= 18) {\n    std::cout << \"Reşit\";\n} _____ {\n    std::cout << \"Reşit değil\";\n}\nAlternatif bloğu belirtmek için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"else"},
        .explanation = "Alternatif blok else anahtar kelimesiyle tanımlanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 291, .topicId = 18,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "if (not_ >= 50) {\n    std::cout << \"Geçti\";\n} else {\n    std::cout << _____;\n}\nnot_ 50'den küçükse yazdırılacak metni (tırnaklarla) boşluğa yazın (örnek metin: \"Kaldı\").",
        .acceptedAnswers = {"\"Kaldı\""},
        .explanation = "else bloğu, koşul false olduğunda çalışacak alternatif metni içerir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 292, .topicId = 18,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sayi = -3;\nif (sayi >= 0) {\n    std::cout << \"Pozitif veya sıfır\";\n} else {\n    std::cout << _____;\n}\nsayi negatifken yazdırılacak metni (tırnaklarla) boşluğa yazın (örnek metin: \"Negatif\").",
        .acceptedAnswers = {"\"Negatif\""},
        .explanation = "sayi negatif olduğu için else bloğu çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 293, .topicId = 18,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5;\nif (a _____ 0) {\n    std::cout << \"Sıfır\";\n} else {\n    std::cout << \"Sıfır değil\";\n}\na'nın sıfıra eşit olup olmadığını kontrol etmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 294, .topicId = 18,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 55;\nif (puan _____ 50) {\n    std::cout << \"Geçti\";\n} else {\n    std::cout << \"Kaldı\";\n}\npuan'ın 50'den büyük veya eşit olup olmadığını kontrol etmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {">="},
        .explanation = "Büyük veya eşit kontrolü >= operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 295, .topicId = 18,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "bool aktif = false;\nif (aktif) {\n    std::cout << \"Aktif\";\n} else {\n    std::cout << _____;\n}\naktif false iken yazdırılacak metni (tırnaklarla) boşluğa yazın (örnek metin: \"Pasif\").",
        .acceptedAnswers = {"\"Pasif\""},
        .explanation = "aktif false olduğu için else bloğu çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 296, .topicId = 18,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 15;\nif (yas >= 18) {\n    std::cout << \"Reşit\";\n} _____ {\n    std::cout << \"Reşit değil\";\n}\nAlternatif bloğu başlatan satırı yazın.",
        .acceptedAnswers = {"else"},
        .explanation = "Alternatif blok else ile başlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 297, .topicId = 18,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 8;\nif (sayi % 2 == 0) {\n    std::cout << \"Çift\";\n} else {\n    _____\n}\nsayi tek olduğunda çalışacak yazdırma satırını yazın (örnek metin: \"Tek\").",
        .acceptedAnswers = {"std::cout << \"Tek\";"},
        .explanation = "else bloğu, sayi tek olduğunda çalışacak kodu içerir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 298, .topicId = 18,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 30;\nif (puan >= 50) {\n    std::cout << \"Geçti\";\n} else {\n    std::cout << \"Kaldı\";\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Kaldı"},
        .explanation = "puan 50'den küçük olduğu için else bloğu çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 299, .topicId = 18,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 0;\nif (a) {\n    std::cout << \"Doğru\";\n} else {\n    std::cout << \"Yanlış\";\n}\nstd::cout << \"!\";\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Yanlış!"},
        .explanation = "a=0 false olarak değerlendirilir, else çalışır ('Yanlış'), ardından koşulsuz '!' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 300, .topicId = 18,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint yas = 15;\nif (yas >= 18)\n    std::cout << \"Reşit\";\nelse;\n    std::cout << \"Reşit değil\";\n\nProgramcı yas 18'den küçükken sadece 'Reşit değil' yazdırılmasını bekliyor ama else satırının sonundaki fazladan noktalı virgül yüzünden son satır koşuldan bağımsız her zaman çalışıyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"else"},
        .explanation = "else satırının sonuna noktalı virgül eklenirse, else'in kontrol ettiği ifade boş bir ifade olur; bu yüzden sonraki satır koşuldan bağımsız olarak her zaman çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 301, .topicId = 18,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint puan = 70;\nif (puan >= 50)\n    std::cout << \"Geçti\";\nelse\n    std::cout << \"Kaldı\"\n\nProgramcının kodu derlenmiyor. Hatalı satırı (else'e bağlı satırı) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << \"Kaldı\";"},
        .explanation = "Satırın sonunda noktalı virgül eksik; her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 302, .topicId = 18,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint yas = 20;\nif (yas >= 18)\n    std::cout << \"Reşit\";\nelse if\n    std::cout << \"Reşit değil\";\n\nProgramcı basit bir if-else yazmak istiyor (else if değil). Düzeltilmiş dördüncü satırı yazın.",
        .acceptedAnswers = {"else"},
        .explanation = "Basit bir alternatif blok için else if değil, sadece else yazılmalıdır (else if bir koşul bekler).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 303, .topicId = 18,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, not kontrolü yapan geçerli bir if-else programı oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"} else {", "std::cout << \"Kaldı\";", "if (not_ >= 50) {", "std::cout << \"Geçti\";", "}"},
        .acceptedAnswers = {"3 4 1 2 5"},
        .explanation = "if satırı (3), if bloğu içeriği (4), else açılışı (1), else bloğu içeriği (2), kapanış (5): sıra 3 4 1 2 5.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 304, .topicId = 18,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir not (0-100 arası) okuyup, not 50'den büyük veya eşitse 'Geçti', değilse 'Kaldı' yazdıran bir program yazın (if-else kullanarak).",
        .acceptedAnswers = {"cin", ">>", "if", "else", "cout", "<<"},
        .explanation = "Program notu cin >> ile okumalı, if-else ile kontrol etmeli ve cout << ile sonucu yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 19: else if
    questions.push_back(Question{
        .id = 305, .topicId = 19,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "else if yapısı ne işe yarar?",
        .options = {"Tek bir koşulu tekrar kontrol eder", "Birden fazla koşulu sırayla kontrol etmeyi sağlar", "Döngü oluşturur", "Fonksiyon tanımlar"},
        .acceptedAnswers = {"b"},
        .explanation = "else if, bir if-else zincirinde birden fazla koşulu sırayla kontrol etmeyi sağlar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 306, .topicId = 19,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir else if zincirinde koşullar hangi sırayla değerlendirilir?",
        .options = {"Rastgele", "Aşağıdan yukarıya", "Yukarıdan aşağıya, sırayla", "Aynı anda (paralel)"},
        .acceptedAnswers = {"c"},
        .explanation = "Koşullar kod sırasına göre, yukarıdan aşağıya doğru değerlendirilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 307, .topicId = 19,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir else if zincirinde ilk true olan koşuldan sonra ne olur?",
        .options = {"Diğer koşullar da kontrol edilmeye devam eder", "O bloğun kodu çalışır ve zincirin geri kalanı atlanır", "Program çöker", "Hiçbir şey olmaz"},
        .acceptedAnswers = {"b"},
        .explanation = "İlk true olan koşulun bloğu çalışır; zincirin geri kalanı kontrol edilmeden atlanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 308, .topicId = 19,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int not_ = 65; if (not_ >= 85) {...} else if (not_ >= 70) {...} else if (not_ >= 50) {...} else {...} zincirinde hangi blok çalışır?",
        .options = {"1. blok", "2. blok", "3. blok", "4. blok (else)"},
        .acceptedAnswers = {"c"},
        .explanation = "not_ = 65: >= 85 false, >= 70 false, >= 50 true; 3. blok çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 309, .topicId = 19,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir else if zincirinin en sonuna eklenen (koşulsuz) else ne zaman çalışır?",
        .options = {"Her zaman", "Hiçbir koşul true olmadığında", "İlk koşul true olduğunda", "Asla çalışmaz"},
        .acceptedAnswers = {"b"},
        .explanation = "Zincirdeki tüm koşullar false ise, en sondaki else çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 310, .topicId = 19,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "else if koşullarının sırası neden önemlidir?",
        .options = {"Önemli değildir, sıra fark etmez", "Daha geniş kapsamlı bir koşul başa yazılırsa dar kapsamlı koşullar hiç çalışmayabilir", "Derleyici sırayı otomatik düzeltir", "Sadece performansı etkiler, sonucu etkilemez"},
        .acceptedAnswers = {"b"},
        .explanation = "İlk eşleşen koşul kazandığı için, geniş bir koşul başa konursa sonraki dar koşullar asla değerlendirilmeyebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 311, .topicId = 19,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int not_ = 90; if (not_ >= 50) { std::cout << \"BB\"; } else if (not_ >= 85) { std::cout << \"AA\"; } zincirinde ne yazdırılır?",
        .options = {"AA", "BB", "Her ikisi de", "Hiçbiri"},
        .acceptedAnswers = {"b"},
        .explanation = "İlk koşul (>= 50) zaten true olduğu için 'BB' yazdırılır; ikinci koşul hiç kontrol edilmez, sıralama önemlidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 312, .topicId = 19,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int x = 5; if (x == 1) {...} else if (x == 2) {...} else if (x == 5) {...} else {...} zincirinde x=5 iken kaçıncı koşul kontrol edildikten sonra blok çalışır?",
        .options = {"1.", "2.", "3.", "4. (else)"},
        .acceptedAnswers = {"c"},
        .explanation = "x == 1 false, x == 2 false, x == 5 true; 3. koşuldan sonraki blok çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 313, .topicId = 19,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "else if, birden fazla koşulu sırayla kontrol etmeyi sağlar.",
        .acceptedAnswers = {"1"},
        .explanation = "else if yapısının amacı budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 314, .topicId = 19,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir else if zincirinde tüm koşullar her zaman kontrol edilir, ilk true olan bulunsa bile devam eder.",
        .acceptedAnswers = {"2"},
        .explanation = "İlk true olan koşuldan sonra zincirin geri kalanı atlanır, kontrol edilmez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 315, .topicId = 19,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir else if zincirinin sonunda else olması zorunludur.",
        .acceptedAnswers = {"2"},
        .explanation = "else isteğe bağlıdır; hiçbir koşul sağlanmazsa ve else yoksa hiçbir blok çalışmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 316, .topicId = 19,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "else if koşullarının sırası sonucu etkileyebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "İlk eşleşen koşul kazandığı için sıra önemlidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 317, .topicId = 19,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir else if zincirinde en fazla bir blok çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "İlk true olan koşulun bloğu çalışır, geri kalanı atlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 318, .topicId = 19,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "else if, aslında else bloğunun içine yazılmış yeni bir if ifadesidir.",
        .acceptedAnswers = {"1"},
        .explanation = "else if sözdizimsel olarak else { if (...) { ... } } yapısının kısaltılmış halidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 319, .topicId = 19,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "if (puan >= 85) {\n    std::cout << \"AA\";\n} _____ (puan >= 70) {\n    std::cout << \"BA\";\n}\nİkinci koşulu kontrol etmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"else if"},
        .explanation = "İkinci koşul else if ile kontrol edilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 320, .topicId = 19,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "if (not_ >= 85) {\n    ...\n} else if (not_ >= 70) {\n    ...\n} _____ {\n    std::cout << \"Kaldı\";\n}\nHiçbir koşul sağlanmadığında çalışacak bloğu belirtmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"else"},
        .explanation = "Zincirin sonundaki koşulsuz blok else ile tanımlanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 321, .topicId = 19,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "if (x == 1) {\n    ...\n} else if (x _____ 2) {\n    ...\n}\nx'in 2'ye eşit olup olmadığını kontrol etmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 322, .topicId = 19,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 72;\nif (puan >= 85) {\n    std::cout << \"AA\";\n} else if (puan _____ 70) {\n    std::cout << \"BA\";\n}\npuan'ın 70'e eşit veya büyük olduğunu kontrol etmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {">="},
        .explanation = "Büyük veya eşit kontrolü >= operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 323, .topicId = 19,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int gun = 6;\nif (gun == 7) {\n    std::cout << \"Pazar\";\n} else if (gun _____ 6) {\n    std::cout << \"Cumartesi\";\n}\ngun'un 6'ya eşit olup olmadığını kontrol etmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 324, .topicId = 19,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "if (a > 100) {\n    ...\n} else if (a > 50) {\n    ...\n} else _____ (a > 0) {\n    ...\n}\nÜçüncü koşulu tanımlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"if"},
        .explanation = "else if, else ile if'in birleşiminden oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 325, .topicId = 19,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int not_ = 65;\nif (not_ >= 85) {\n    std::cout << \"AA\";\n} _____ {\n    std::cout << \"BA\";\n}\nnot_'un 70'e eşit veya büyük olduğunu kontrol eden else if satırını yazın.",
        .acceptedAnswers = {"else if (not_ >= 70)"},
        .explanation = "İkinci koşul else if (not_ >= 70) şeklinde yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 326, .topicId = 19,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int gun = 3;\nif (gun == 1) {\n    std::cout << \"Pazartesi\";\n} _____ {\n    std::cout << \"Salı\";\n}\ngun'un 2'ye eşit olup olmadığını kontrol eden else if satırını yazın.",
        .acceptedAnswers = {"else if (gun == 2)"},
        .explanation = "İkinci koşul else if (gun == 2) şeklinde yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 327, .topicId = 19,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int not_ = 55;\nif (not_ >= 85) {\n    std::cout << \"AA\";\n} else if (not_ >= 70) {\n    std::cout << \"BA\";\n} else {\n    std::cout << \"Kaldı\";\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Kaldı"},
        .explanation = "not_ hiçbir koşulu sağlamadığı için (>= 85 ve >= 70 ikisi de false) en sondaki else çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 328, .topicId = 19,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int x = 2;\nif (x == 1) {\n    std::cout << \"Bir\";\n} else if (x == 2) {\n    std::cout << \"İki\";\n} else if (x == 2) {\n    std::cout << \"İkinci İki\";\n}\nYukarıdaki kodun ekran çıktısı nedir? (iki koşul de x==2 olsa da)",
        .acceptedAnswers = {"İki"},
        .explanation = "İlk eşleşen koşul (ikinci blok, x == 2) kazanır; üçüncü blok hiç kontrol edilmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 329, .topicId = 19,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint not_ = 75;\nif (not_ >= 85) {\n    std::cout << \"AA\";\n} else if (not_ >= 70) {\n    std::cout << \"BA\";\n} elseif (not_ >= 50) {\n    std::cout << \"CB\";\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"} else if (not_ >= 50) {"},
        .explanation = "elseif tek kelime olarak yazılamaz; else if şeklinde iki ayrı kelime olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 330, .topicId = 19,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint not_ = 40;\nif (not_ >= 85)\n    std::cout << \"AA\";\nelse if (not_ >= 70)\n    std::cout << \"BA\";\nelse\n    std::cout << \"Kaldı\"\n\nProgramcının kodu derlenmiyor. Hatalı satırı (en son satırı) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << \"Kaldı\";"},
        .explanation = "Satırın sonunda noktalı virgül eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 331, .topicId = 19,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint x = 3;\nif (x == 1) {\n    std::cout << \"Bir\";\n} else if (x = 2) {\n    std::cout << \"İki\";\n}\n\nProgramcı x'in 2'ye eşit olup olmadığını kontrol etmek istiyor. Düzeltilmiş üçüncü satırı yazın.",
        .acceptedAnswers = {"} else if (x == 2) {"},
        .explanation = "Karşılaştırma için == kullanılmalıdır; = bir atamadır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 332, .topicId = 19,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, not kontrolü yapan geçerli bir if-else if-else programı oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"} else {", "std::cout << \"Kaldı\";", "} else if (not_ >= 70) {", "std::cout << \"BA\";", "if (not_ >= 85) {", "std::cout << \"AA\";", "}"},
        .acceptedAnswers = {"5 6 3 4 1 2 7"},
        .explanation = "if satırı (5), if bloğu (6), else if satırı (3), else if bloğu (4), else satırı (1), else bloğu (2), kapanış (7): sıra 5 6 3 4 1 2 7.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 333, .topicId = 19,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir not (0-100 arası) okuyup, not 85 ve üzeriyse 'AA', 70 ve üzeriyse 'BA', 50 ve üzeriyse 'CB', altındaysa 'Kaldı' yazdıran bir program yazın (if-else if-else zinciri kullanarak).",
        .acceptedAnswers = {"cin", ">>", "if", "else if", "else", "cout", "<<"},
        .explanation = "Program notu cin >> ile okumalı, if-else if-else zinciriyle kontrol etmeli ve cout << ile sonucu yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 20: Üçlü koşul operatörü
    questions.push_back(Question{
        .id = 334, .topicId = 20,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Üçlü (ternary) operatör hangi sembollerle yazılır?",
        .options = {"&&", "?:", "||", "::"},
        .acceptedAnswers = {"b"},
        .explanation = "Üçlü operatör ? ve : sembolleriyle yazılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 335, .topicId = 20,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "kosul ? deger1 : deger2 ifadesinde kosul false ise sonuç nedir?",
        .options = {"deger1", "deger2", "kosul", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "kosul false ise ifade deger2'yi döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 336, .topicId = 20,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int a = (5 > 3) ? 10 : 20; ifadesinden sonra a kaç olur?",
        .options = {"10", "20", "5", "3"},
        .acceptedAnswers = {"a"},
        .explanation = "5 > 3 true olduğu için ifade 10'u döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 337, .topicId = 20,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Üçlü operatör, temelde hangi yapının kısa bir alternatifidir?",
        .options = {"for döngüsü", "if-else", "while döngüsü", "switch-case"},
        .acceptedAnswers = {"b"},
        .explanation = "Üçlü operatör, basit bir if-else'in tek satırda yazılmış halidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 338, .topicId = 20,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int b = (7 < 3) ? 1 : 0; ifadesinden sonra b kaç olur?",
        .options = {"1", "0", "7", "3"},
        .acceptedAnswers = {"b"},
        .explanation = "7 < 3 false olduğu için ifade 0'ı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 339, .topicId = 20,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string sonuc = (10 % 2 == 0) ? \"Çift\" : \"Tek\"; ifadesinden sonra sonuc ne olur?",
        .options = {"Çift", "Tek", "10", "Hata"},
        .acceptedAnswers = {"a"},
        .explanation = "10 % 2 == 0 true olduğu için sonuc 'Çift' olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 340, .topicId = 20,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5; int b = 10; int buyuk = (a > b) ? a : b; ifadesinden sonra buyuk kaç olur?",
        .options = {"5", "10", "15", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "a > b false olduğu için ifade b'yi (10) döndürür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 341, .topicId = 20,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int x = 0; std::cout << (x ? \"Doğru\" : \"Yanlış\"); kodu ne yazdırır?",
        .options = {"Doğru", "Yanlış", "0", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "x = 0 falsy (false) olarak değerlendirilir; ifade 'Yanlış'ı döndürür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 342, .topicId = 20,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Üçlü operatör ?: şeklinde yazılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Üçlü operatörün sembolleri ? ve :'dir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 343, .topicId = 20,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Üçlü operatör, if-else'den tamamen farklı bir mantık kullanır ve karşılaştırılamaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Üçlü operatör aslında basit bir if-else'in kısa yazılışıdır; aynı mantığı taşır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 344, .topicId = 20,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Üçlü operatör tek bir satırda koşullu bir değer döndürmek için kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Üçlü operatörün amacı budur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 345, .topicId = 20,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "kosul ? a : b ifadesinde kosul true ise sonuç b'dir.",
        .acceptedAnswers = {"2"},
        .explanation = "kosul true ise sonuç a'dır, b değil.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 346, .topicId = 20,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Üçlü operatör, çok satırlı karmaşık mantık için if-else'den daha okunaklıdır.",
        .acceptedAnswers = {"2"},
        .explanation = "Üçlü operatör basit, tek satırlık kararlar için uygundur; karmaşık mantıkta if-else daha okunaklıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 347, .topicId = 20,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Üçlü operatörün iki tarafındaki (true/false) ifadelerin türü birbiriyle uyumlu olmalıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "İki taraf farklı, uyumsuz türlerde olursa derleyici uyarısı veya hatası oluşabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 348, .topicId = 20,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; int sonuc = (a > 0) _____ 1 : -1; ifadesini tamamlamak için boşluğa hangi karakter yazılmalı?",
        .acceptedAnswers = {"?"},
        .explanation = "Üçlü operatör koşuldan sonra ? karakteriyle devam eder.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 349, .topicId = 20,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a = 5; int sonuc = (a > 0) ? 1 _____ -1; ifadesini tamamlamak için boşluğa hangi karakter yazılmalı?",
        .acceptedAnswers = {":"},
        .explanation = "true ve false değerlerini ayıran karakter :'dir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 350, .topicId = 20,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int yas = 20; std::string durum = (yas >= 18) ? \"Reşit\" : _____; ifadesinde yas 18'den küçükken kullanılacak metni (tırnaklarla) boşluğa yazın (örnek metin: \"Reşit değil\").",
        .acceptedAnswers = {"\"Reşit değil\""},
        .explanation = "kosul false olduğunda : işaretinden sonraki değer kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 351, .topicId = 20,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 8; int b = 3; int buyuk = (a _____ b) ? a : b; ifadesinin büyük olan değeri seçmesi için boşluğa ne yazılmalı?",
        .acceptedAnswers = {">"},
        .explanation = "a > b true ise a, false ise b seçilir; büyük olanı bulmak için > kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 352, .topicId = 20,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 7; std::string sonuc = (sayi % 2 _____ 0) ? \"Çift\" : \"Tek\"; ifadesinin çift/tek kontrolü yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 353, .topicId = 20,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int puan = 45; std::string sonuc = (puan _____ 50) ? \"Geçti\" : \"Kaldı\"; ifadesinin puan'ın 50'ye eşit veya büyük olduğunu kontrol etmesi için boşluğa ne yazılmalı?",
        .acceptedAnswers = {">="},
        .explanation = "Büyük veya eşit kontrolü >= operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 354, .topicId = 20,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 16;\nstd::string durum = _____;\nyas'ın 18'e eşit veya büyük olup olmadığına göre \"Reşit\" veya \"Reşit değil\" atayan üçlü operatör ifadesini yazın.",
        .acceptedAnswers = {"(yas >= 18) ? \"Reşit\" : \"Reşit değil\"", "yas >= 18 ? \"Reşit\" : \"Reşit değil\""},
        .explanation = "Üçlü operatör kosul ? deger1 : deger2 şeklinde yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 355, .topicId = 20,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 9;\nint b = 4;\nint kucuk = _____;\na ile b'den küçük olanı seçen üçlü operatör ifadesini yazın.",
        .acceptedAnswers = {"(a < b) ? a : b", "a < b ? a : b"},
        .explanation = "a < b true ise a, false ise b küçük olan değerdir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 356, .topicId = 20,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 12;\nstd::cout << ((a % 2 == 0) ? \"Çift\" : \"Tek\");\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Çift"},
        .explanation = "12 % 2 == 0 true olduğu için 'Çift' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 357, .topicId = 20,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 3;\nint b = 9;\nstd::cout << ((a > b) ? a : b);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"9"},
        .explanation = "a > b false olduğu için ifade b'yi (9) döndürür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 358, .topicId = 20,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint yas = 20;\nstd::string durum = (yas >= 18) ? \"Reşit\" ; \"Reşit değil\";\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::string durum = (yas >= 18) ? \"Reşit\" : \"Reşit değil\";"},
        .explanation = "Üçlü operatörde iki değer arasına noktalı virgül değil : konulmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 359, .topicId = 20,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a = 5;\nint b = 8;\nint buyuk = (a > b) : a ? b;\n\nProgramcı büyük olan değeri seçmek istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int buyuk = (a > b) ? a : b;"},
        .explanation = "? ve : sembollerinin yerleri yanlış; doğru sırada kosul ? deger1 : deger2 olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 360, .topicId = 20,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint puan = 60;\nstd::string sonuc = (puan >= 50) ? \"Geçti\" \"Kaldı\";\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"std::string sonuc = (puan >= 50) ? \"Geçti\" : \"Kaldı\";"},
        .explanation = "İki değer arasında : eksik; üçlü operatör kosul ? deger1 : deger2 şeklinde yazılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 361, .topicId = 20,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, üçlü operatörle yaş kontrolü yapan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << durum;", "std::string durum = (yas >= 18) ? \"Reşit\" : \"Reşit değil\";", "int yas = 20;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce yas tanımlanır, sonra üçlü operatörle durum hesaplanır, en son yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 362, .topicId = 20,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir tam sayı okuyup, sayının çift mi tek mi olduğunu üçlü koşul operatörünü (?:) kullanarak ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "?", ":", "cout", "<<"},
        .explanation = "Program sayıyı cin >> ile okumalı, ?: operatörüyle çift/tek kararı vermeli ve cout << ile sonucu yazdırmalıdır.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Widen the duplicate-id test and add a per-topic minimum-count test**

In `tests/QuestionManagerTests.cpp`, change:

```cpp
TEST_CASE(QuestionManager_NoDuplicateQuestionIds) {
    QuestionManager manager;
    std::unordered_set<int> seenIds;
    bool foundDuplicate = false;
    for (int topicId = 1; topicId <= 10; ++topicId) {
        for (const Question& question : manager.questionsForTopic(topicId)) {
            if (!seenIds.insert(question.id).second) {
                foundDuplicate = true;
            }
        }
    }
    CHECK(!foundDuplicate);
}
```

to:

```cpp
TEST_CASE(QuestionManager_NoDuplicateQuestionIds) {
    QuestionManager manager;
    std::unordered_set<int> seenIds;
    bool foundDuplicate = false;
    for (int topicId = 1; topicId <= 100; ++topicId) {
        for (const Question& question : manager.questionsForTopic(topicId)) {
            if (!seenIds.insert(question.id).second) {
                foundDuplicate = true;
            }
        }
    }
    CHECK(!foundDuplicate);
}
```

Then add this new test case right after it:

```cpp
TEST_CASE(QuestionManager_EveryTopicElevenToTwentyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 11; topicId <= 20; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
}
```

- [ ] **Step 3: Build and run the full test suite**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `89/89 test(s) passed.` (88 from Task 1 + 1 new test; the
duplicate-id test widening doesn't add a new test case, only its own
range).

Run from `build/`: `ctest -C Debug --output-on-failure`
Expected: 100% pass.

- [ ] **Step 4: Manual verification — topic 11 end-to-end**

Run the app and pipe in: open the topic browser, select Section 2,
open topic 11, answer all questions correctly, then return to the main
menu and exit.

```bash
printf "2\n2\n11\n" > /tmp/section2_start.txt
```

Since the exact question order for topic 11 depends on Phase 12's
adaptive difficulty (sorts by ascending `Difficulty`, jumps to the
hardest remaining question after 2 correct answers in a row — see
`src/AdaptiveDifficulty.h`), do not hand-trace the exact order; instead
verify structurally:

1. Run `./build/Debug/CppMasterConsole.exe`, choose the menu option for
   "Konu Anlatımı" (topic browser), choose Section 2, choose topic 11.
2. Confirm the lesson text prints (matches the `explanation`/`syntax`/
   `exampleCode` written in Task 1) — this alone proves `openTopic`'s
   `lesson->explanation.empty()` gate now passes for topic 11 with zero
   `Application.cpp` changes.
3. Confirm "Konu testi başlıyor (29 soru)." prints — proving all 29 of
   topic 11's questions (not just some) are wired into
   `questionsForTopic(11)`.
4. Answer a few questions (correct or incorrect, either is fine — this
   step is about confirming the flow works, not re-verifying Phase 12's
   already-tested adaptive logic) until confident the quiz runs
   end-to-end, then answer `cikis` to return to the main menu.
5. Confirm the app returns to the main menu without crashing, and that
   partial XP is awarded (matches the existing `exitRequested` contract
   already verified in Phase 10/12 — this step confirms topic 11
   composes correctly with that existing mechanism, not re-testing the
   mechanism itself).
6. Clean up: `rm -f data/*.txt` (remove any progress/mistake files
   created during this manual run, matching every prior phase's manual
   verification cleanup convention).

- [ ] **Step 5: Commit the question content and test changes**

```bash
git add src/QuestionsSection2.cpp tests/QuestionManagerTests.cpp
git commit -m "feat(content): add questions for topics 18-20 (ids 276-362), widen coverage tests"
```

- [ ] **Step 6: Update the roadmap**

In `docs/superpowers/roadmap.md`:

1. Change the "Phase 13-21" bullet under "Phase order" to mark Phase 13
   complete, following the exact format every prior phase entry uses
   (`**Phase N — name: COMPLETE** (commits \`X..Y\`, ...)`), with the
   commit range starting at this phase's design-spec commit and ending
   at this task's final content commit (i.e., the same convention
   Phases 8-12 all used — the base is the plan-preceding commit, not
   `HEAD~1`).
2. Update the "Status" section to say Phase 13 is complete and Phase 14
   (Section 3 content) starts next.

Then commit:

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 13 complete in roadmap"
```


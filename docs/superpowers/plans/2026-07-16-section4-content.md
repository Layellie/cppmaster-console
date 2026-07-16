# Bölüm 4 İçerik Genişletmesi Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Give topics 31-40 (Section 4, "Diziler, vector ve string") real
lesson content and a 29-question-per-topic question bank (290 questions
total), the third of nine content-expansion phases, following the exact
same architecture Phases 13-14 established and merged.

**Architecture:** Two new per-section content files
(`src/LessonContentSection4.cpp`, `src/QuestionsSection4.cpp`), declared
in the SAME shared headers Phases 13-14 created (`src/LessonContent.h`,
`src/QuestionContent.h` — this phase adds one more declaration to each,
it does not replace the existing ones). No `Application.cpp` changes
needed.

**Tech Stack:** C++20, standard library only, existing `Lesson`/`Question`
structs, existing `LessonManager`/`QuestionManager` classes.

## Global Constraints

- Topics covered: 31 (Normal diziler), 32 (Dizi elemanlarını değiştirme),
  33 (std::array), 34 (vector), 35 (push_back() ve pop_back()), 36
  (size(), front(), back() ve at()), 37 (string), 38 (String
  birleştirme), 39 (length() ve empty()), 40 (substr() ve find()) —
  sectionId 4.
- Lesson content mirrors the existing `Lesson` struct fields exactly:
  `explanation`, `syntax`, `exampleCode`, `lineExplanations`,
  `commonMistakes` — no new fields.
- Question ids sequential starting at 653 (Phase 14 ended at 652): topic
  31 = 653-681, topic 32 = 682-710, topic 33 = 711-739, topic 34 =
  740-768, topic 35 = 769-797, topic 36 = 798-826, topic 37 = 827-855,
  topic 38 = 856-884, topic 39 = 885-913, topic 40 = 914-942. Exactly 29
  per topic.
- Per-topic type/difficulty/baseXp distribution (identical to every
  topic in Phases 13-14 — fixed project-wide convention):

  | Type            | Count | Difficulty (in order)                                    | baseXp        |
  |-----------------|-------|-----------------------------------------------------------|---------------|
  | MultipleChoice  | 8     | VeryEasy, Easy, Easy, Medium, Medium, Medium, Hard, Hard   | 5,10,10,20,20,20,30,30 |
  | TrueFalse       | 6     | VeryEasy, VeryEasy, Easy, Easy, Medium, Medium             | 5,5,10,10,20,20 |
  | FillBlank       | 6     | Easy, Easy, Easy, Medium, Medium, Medium                   | 10,10,10,20,20,20 |
  | CompleteLine    | 2     | Medium, Medium                                             | 20,20 |
  | PredictOutput   | 2     | Medium, Hard                                               | 20,30 |
  | FindError       | 2     | Medium, Hard                                               | 20,30 |
  | FixCode         | 1     | Hard                                                       | 30 |
  | OrderCode       | 1     | Medium                                                     | 20 |
  | WriteCode       | 1     | Hard                                                       | 40 |

  All content is spelled out verbatim in Tasks 2-4 below — no task
  invents content, only transcribes it.
- `MultipleChoice.acceptedAnswers` = single lowercase letter (a/b/c/d)
  matching the 0-indexed `options` position.
- `TrueFalse` has no `options`; `{"1"}` = true, `{"2"}` = false.
- `OrderCode.acceptedAnswers` = 1-indexed option positions, space-separated.
- `WriteCode.acceptedAnswers` = required substrings/keywords.
- **Array/vector/string semantic constraints, verified against real C++
  before authoring (each has already caused a real, compiler-caught bug
  in a prior phase's content — verify, don't assume):**
  - `[]` (on C-style array, `std::array`, or `std::vector`) never bounds-
    checks; out-of-bounds access is undefined behavior, not an exception.
  - `.at()` (on `std::array`/`std::vector`) bounds-checks and throws
    `std::out_of_range` on an invalid index — this is the one and only
    functional difference between `.at()` and `[]` that any question may
    assert.
  - `std::array`'s size is a compile-time template parameter; it can
    never grow or shrink (no `push_back`/`pop_back` exist on it).
  - `std::vector::pop_back()` on an empty vector is undefined behavior —
    never "a safe no-op" and never something that throws.
  - `std::string::find()` returns `std::string::npos` (not `-1`) when
    the substring isn't found; any question comparing a `find()` result
    to "not found" must use `!= std::string::npos` / `== std::string::npos`,
    never `== -1`.
  - `std::string::substr(pos, len)`'s second argument is a LENGTH, not an
    end position (verify arithmetic by hand for every question using
    it: `"Merhaba".substr(2, 3)` is `"rha"`).

---

### Task 1: Section 4 lesson content

**Files:**
- Modify: `src/LessonContent.h` (add one new declaration)
- Create: `src/LessonContentSection4.cpp`
- Modify: `src/LessonManager.cpp` (call the new function)
- Modify: `CMakeLists.txt` (add the new `.cpp` to the source list)
- Modify: `tests/LessonManagerTests.cpp` (extend content-range coverage)

**Interfaces:**
- Produces: `void applySection4LessonContent(std::vector<Lesson>& lessons);`
  — writes into indices 30-39 (topics 31-40).

- [ ] **Step 1: Add the new declaration**

In `src/LessonContent.h`, add this line after the existing
`applySection3LessonContent` declaration (do not remove that one):

```cpp
void applySection4LessonContent(std::vector<Lesson>& lessons);
```

- [ ] **Step 2: Write the lesson content**

Create `src/LessonContentSection4.cpp`:

```cpp
#include "LessonContent.h"

#include "Lesson.h"

void applySection4LessonContent(std::vector<Lesson>& lessons) {
    // Index 30 = topic id 31 (Normal diziler), index 39 = topic id 40
    // (substr() ve find()) — same positional convention as
    // applyIntroLessonContent/applySection2LessonContent/applySection3LessonContent.

    lessons[30].explanation =
        "Bir dizi (array), aynı türden birden fazla değeri tek bir "
        "değişken altında saklamayı sağlar. Dizinin boyutu tanımlanırken "
        "belirtilir ve sonradan değiştirilemez. Elemanlara köşeli "
        "parantez [] içinde bir indeks (0'dan başlayan) ile erişilir; "
        "ilk eleman index 0'dadır.";
    lessons[30].syntax = "int sayilar[5];  // 5 elemanlı, tanımlanmamış int dizisi";
    lessons[30].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int sayilar[3] = {10, 20, 30};\n"
        "    std::cout << sayilar[0] << \" \" << sayilar[2];\n"
        "    return 0;\n"
        "}";
    lessons[30].lineExplanations = {
        "int sayilar[3] = {10, 20, 30}; : 3 elemanlı bir dizi tanımlanır "
        "ve başlangıç değerleri verilir.",
        "sayilar[0] : Dizinin ilk elemanına (10) erişir (indeks 0'dan "
        "başlar).",
        "sayilar[2] : Dizinin üçüncü (son) elemanına (30) erişir.",
    };
    lessons[30].commonMistakes = {
        "Dizinin ilk elemanının indeks 1 olduğunu sanmak (aslında "
        "0'dır).",
        "Dizi sınırlarının dışına (örneğin 3 elemanlı bir dizide "
        "sayilar[3]'e) erişmeye çalışmak; bu tanımsız davranışa yol "
        "açar ve derleyici bunu her zaman yakalamaz.",
        "Dizi boyutunu tanımladıktan sonra değiştirmeye çalışmak "
        "(C-style diziler sabit boyutludur).",
    };

    lessons[31].explanation =
        "Bir dizinin elemanları, tıpkı normal bir değişken gibi köşeli "
        "parantez [] ve indeks kullanılarak değiştirilebilir. "
        "dizi[indeks] = yeniDeger; şeklinde atama yapılır. Dizideki her "
        "eleman bağımsız olarak değiştirilebilir.";
    lessons[31].syntax = "dizi[indeks] = yeniDeger;";
    lessons[31].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int sayilar[3] = {10, 20, 30};\n"
        "    sayilar[1] = 99;\n"
        "    std::cout << sayilar[0] << \" \" << sayilar[1] << \" \" << sayilar[2];\n"
        "    return 0;\n"
        "}";
    lessons[31].lineExplanations = {
        "sayilar[1] = 99; : Dizinin ikinci elemanı (indeks 1) 99 olarak "
        "değiştirilir.",
        "std::cout << ... : Değişiklikten sonra dizi 10 99 30 olarak "
        "yazdırılır.",
    };
    lessons[31].commonMistakes = {
        "Değiştirilecek elemanın indeksini yanlış hesaplamak (özellikle "
        "döngü içinde).",
        "Dizi sınırlarının dışına bir değer atamaya çalışmak; bu "
        "tanımsız davranışa yol açar.",
        "Tüm diziyi tek bir atama ile değiştirmeye çalışmak "
        "(dizi = {...}; gibi); her eleman ayrı ayrı değiştirilmelidir.",
    };

    lessons[32].explanation =
        "std::array, C-style dizilere modern ve daha güvenli bir "
        "alternatiftir. <array> kütüphanesinde tanımlıdır ve boyutu "
        "C-style diziler gibi sabittir (derleme zamanında belirlenir), "
        "ancak size(), at() gibi yararlı üye fonksiyonlar sunar. at() "
        "kullanıldığında sınır dışı erişim, [] operatöründen farklı "
        "olarak bir istisna (exception) fırlatır.";
    lessons[32].syntax = "std::array<int, 3> sayilar = {10, 20, 30};";
    lessons[32].exampleCode =
        "#include <iostream>\n"
        "#include <array>\n\n"
        "int main() {\n"
        "    std::array<int, 3> sayilar = {10, 20, 30};\n"
        "    std::cout << sayilar.size() << \" \" << sayilar.at(1);\n"
        "    return 0;\n"
        "}";
    lessons[32].lineExplanations = {
        "std::array<int, 3> sayilar : 3 elemanlı, int türünde bir "
        "std::array tanımlar.",
        "sayilar.size() : Dizinin eleman sayısını (3) döndürür.",
        "sayilar.at(1) : İkinci elemana (20) güvenli erişim sağlar; "
        "sınır dışı olsaydı istisna fırlatırdı.",
    };
    lessons[32].commonMistakes = {
        "std::array'in boyutunun da (C-style diziler gibi) çalışma "
        "zamanında değiştirilebileceğini sanmak.",
        "<array> kütüphanesini eklemeyi unutmak.",
        "at() ile [] arasındaki farkı karıştırmak: [] sınır kontrolü "
        "yapmaz (tanımsız davranış), at() sınır dışı erişimde istisna "
        "fırlatır.",
    };

    lessons[33].explanation =
        "std::vector, boyutu çalışma zamanında değişebilen (büyüyüp "
        "küçülebilen) dinamik bir dizi türüdür. <vector> kütüphanesinde "
        "tanımlıdır. Elemanlara [] veya at() ile erişilebilir; eleman "
        "eklemek/çıkarmak için push_back()/pop_back() gibi üye "
        "fonksiyonlar kullanılır.";
    lessons[33].syntax = "std::vector<int> sayilar = {10, 20, 30};";
    lessons[33].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n\n"
        "int main() {\n"
        "    std::vector<int> sayilar = {10, 20};\n"
        "    sayilar.push_back(30);\n"
        "    std::cout << sayilar.size() << \" \" << sayilar[2];\n"
        "    return 0;\n"
        "}";
    lessons[33].lineExplanations = {
        "std::vector<int> sayilar = {10, 20}; : 2 elemanlı bir vector "
        "oluşturulur.",
        "sayilar.push_back(30); : Vector'ün sonuna 30 eklenir; boyut "
        "3'e çıkar.",
        "sayilar.size() : Güncel eleman sayısını (3) döndürür.",
    };
    lessons[33].commonMistakes = {
        "vector'ün boyutunun std::array veya C-style diziler gibi sabit "
        "olduğunu sanmak (aslında dinamiktir).",
        "<vector> kütüphanesini eklemeyi unutmak.",
        "Var olmayan bir indekse [] ile erişmek (örneğin boş bir "
        "vector'de sayilar[0]); bu tanımsız davranışa yol açar.",
    };

    lessons[34].explanation =
        "push_back(), bir vector'ün sonuna yeni bir eleman ekler ve "
        "boyutu 1 artırır. pop_back(), vector'ün son elemanını siler ve "
        "boyutu 1 azaltır; pop_back() elemanın değerini döndürmez, "
        "sadece siler. Boş bir vector'de pop_back() çağırmak tanımsız "
        "davranışa yol açar.";
    lessons[34].syntax = "vektor.push_back(deger);\nvektor.pop_back();";
    lessons[34].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n\n"
        "int main() {\n"
        "    std::vector<int> sayilar;\n"
        "    sayilar.push_back(1);\n"
        "    sayilar.push_back(2);\n"
        "    sayilar.pop_back();\n"
        "    std::cout << sayilar.size() << \" \" << sayilar[0];\n"
        "    return 0;\n"
        "}";
    lessons[34].lineExplanations = {
        "sayilar.push_back(1); sayilar.push_back(2); : Vector'e sırayla "
        "1 ve 2 eklenir; boyut 2 olur.",
        "sayilar.pop_back(); : Son eleman (2) silinir; boyut 1'e düşer.",
        "sayilar.size() 1, sayilar[0] hala 1'dir.",
    };
    lessons[34].commonMistakes = {
        "pop_back()'in silinen elemanın değerini döndürdüğünü sanmak "
        "(aslında bir şey döndürmez, void'dir).",
        "Boş bir vector'de pop_back() çağırmak; bu tanımsız davranışa "
        "yol açar ve derleyici/çalışma zamanı bunu her zaman yakalamaz.",
        "push_back()'in belirli bir indekse eleman eklediğini sanmak "
        "(her zaman sona ekler).",
    };

    lessons[35].explanation =
        "size(), bir vector veya std::array'in eleman sayısını "
        "döndürür. front(), ilk elemana; back(), son elemana referans "
        "döndürür. at(indeks), belirtilen indeksteki elemana güvenli "
        "(sınır kontrollü) erişim sağlar; sınır dışı bir indeks "
        "verilirse std::out_of_range istisnası fırlatır (bu, [] "
        "operatöründen temel farkıdır).";
    lessons[35].syntax = "vektor.at(indeks);  // sınır kontrollü erişim";
    lessons[35].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n\n"
        "int main() {\n"
        "    std::vector<int> sayilar = {10, 20, 30};\n"
        "    std::cout << sayilar.size() << \" \" << sayilar.front() << \" \" << sayilar.back() << \" \" << sayilar.at(1);\n"
        "    return 0;\n"
        "}";
    lessons[35].lineExplanations = {
        "sayilar.size() : Eleman sayısını (3) döndürür.",
        "sayilar.front() : İlk elemanı (10) döndürür.",
        "sayilar.back() : Son elemanı (30) döndürür.",
        "sayilar.at(1) : İkinci elemana (20) güvenli erişim sağlar.",
    };
    lessons[35].commonMistakes = {
        "at()'in [] gibi sınır kontrolü yapmadığını sanmak (aslında "
        "at() sınır dışı erişimde istisna fırlatır, [] fırlatmaz).",
        "Boş bir vector'de front() veya back() çağırmak; bu tanımsız "
        "davranışa yol açar.",
        "size()'ın dönüş türünün işaretsiz (unsigned) bir tür olduğunu "
        "(size_t) göz ardı edip negatif karşılaştırmalarda hataya "
        "düşmek.",
    };

    lessons[36].explanation =
        "std::string, metin (karakter dizisi) saklamak için kullanılan, "
        "<string> kütüphanesinde tanımlı bir sınıftır. C-style karakter "
        "dizilerine göre çok daha güvenli ve kullanışlıdır; boyutu "
        "otomatik olarak yönetilir ve birçok yararlı üye fonksiyon "
        "(length(), substr(), find() gibi) sunar.";
    lessons[36].syntax = "std::string isim = \"Merhaba\";";
    lessons[36].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::string isim = \"Merhaba\";\n"
        "    std::cout << isim << \" (\" << isim.length() << \" karakter)\";\n"
        "    return 0;\n"
        "}";
    lessons[36].lineExplanations = {
        "std::string isim = \"Merhaba\"; : isim değişkenine 'Merhaba' "
        "metni atanır.",
        "isim.length() : Metindeki karakter sayısını (7) döndürür.",
    };
    lessons[36].commonMistakes = {
        "<string> kütüphanesini eklemeyi unutmak.",
        "std::string ile C-style karakter dizisini (char[]) karıştırmak; "
        "ikisi farklı türlerdir.",
        "Bir karaktere ([] ile) erişip bunun bir std::string olduğunu "
        "sanmak (aslında tek bir char döner).",
    };

    lessons[37].explanation =
        "İki veya daha fazla std::string, + operatörü ile "
        "birleştirilebilir (concatenation). += operatörü de bir "
        "string'in sonuna başka bir string veya karakter eklemek için "
        "kullanılabilir. Birleştirme sonucunda yeni, daha uzun bir "
        "string oluşur.";
    lessons[37].syntax = "std::string tam = ad + \" \" + soyad;";
    lessons[37].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::string ad = \"Ali\";\n"
        "    std::string soyad = \"Veli\";\n"
        "    std::string tam = ad + \" \" + soyad;\n"
        "    std::cout << tam;\n"
        "    return 0;\n"
        "}";
    lessons[37].lineExplanations = {
        "std::string tam = ad + \" \" + soyad; : ad, bir boşluk ve "
        "soyad birleştirilerek 'Ali Veli' oluşturulur.",
        "std::cout << tam; : Birleştirilmiş metin ekrana yazdırılır.",
    };
    lessons[37].commonMistakes = {
        "İki string'i birleştirirken aralarına boşluk eklemeyi unutmak.",
        "+ operatörünü doğrudan iki string literal (\"a\" + \"b\") "
        "arasında kullanmaya çalışmak; en az birinin std::string olması "
        "gerekir.",
        "+= operatörünü = ve + ayrı ayrı yazmakla karıştırmak.",
    };

    lessons[38].explanation =
        "length(), bir string'in karakter sayısını döndürür (size() ile "
        "aynı işi yapar, ikisi eş anlamlıdır). empty(), string'in boş "
        "olup olmadığını (uzunluğu 0 mı) kontrol eden bir bool değer "
        "döndürür; length() == 0 kontrolüyle aynı sonucu verir ama daha "
        "okunaklıdır.";
    lessons[38].syntax = "metin.length();  // veya metin.empty()";
    lessons[38].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::string metin = \"\";\n"
        "    std::cout << metin.length() << \" \" << metin.empty();\n"
        "    return 0;\n"
        "}";
    lessons[38].lineExplanations = {
        "std::string metin = \"\"; : Boş bir string tanımlanır.",
        "metin.length() : Karakter sayısını (0) döndürür.",
        "metin.empty() : Metin boş olduğu için true (1) döndürür.",
    };
    lessons[38].commonMistakes = {
        "length() ile size()'ın farklı sonuç verdiğini sanmak (aslında "
        "ikisi de aynı değeri döndürür).",
        "empty() kontrolü yerine length() == 0 yazmanın yanlış olduğunu "
        "sanmak (ikisi de doğru çalışır, empty() sadece daha "
        "okunaklıdır).",
        "empty()'i bir metnin yalnızca boşluk karakterlerinden oluşup "
        "oluşmadığını kontrol ettiğini sanmak (aslında yalnızca "
        "uzunluğun 0 olup olmadığına bakar; \" \" gibi boşluklu bir "
        "metin empty() için false döner).",
    };

    lessons[39].explanation =
        "substr(baslangic, uzunluk), bir string'in belirtilen konumdan "
        "başlayarak belirtilen UZUNLUKTA bir alt dizisini döndürür "
        "(ikinci parametre bitiş konumu değil, uzunluktur). "
        "find(aranan), aranan alt diziyi bulursa onun başlangıç "
        "indeksini, bulamazsa std::string::npos değerini döndürür.";
    lessons[39].syntax = "metin.substr(baslangic, uzunluk);\nmetin.find(aranan);";
    lessons[39].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::string metin = \"Merhaba\";\n"
        "    std::cout << metin.substr(2, 3) << \" \";\n"
        "    std::cout << (metin.find(\"hab\") != std::string::npos);\n"
        "    return 0;\n"
        "}";
    lessons[39].lineExplanations = {
        "metin.substr(2, 3) : 2. indeksten (r) başlayarak 3 karakter "
        "alır: 'rha'.",
        "metin.find(\"hab\") : 'hab' alt dizisi bulunduğu için "
        "bulunduğu indeksi döndürür; std::string::npos'a eşit olmadığı "
        "için karşılaştırma true (1) verir.",
    };
    lessons[39].commonMistakes = {
        "substr()'ün ikinci parametresinin bitiş indeksi olduğunu "
        "sanmak (aslında uzunluktur).",
        "find() bulamadığında -1 döndürdüğünü sanmak (aslında "
        "std::string::npos adında özel bir sabit döner; == -1 ile "
        "karşılaştırmak yanlış sonuç verebilir).",
        "substr() çağrısının orijinal string'i değiştirdiğini sanmak "
        "(aslında yeni bir string döndürür, orijinali değiştirmez).",
    };
}
```

- [ ] **Step 3: Wire the new function into `LessonManager`**

`src/LessonManager.cpp` already includes `"LessonContent.h"` (from Phase
13). Change the constructor's final lines from:

```cpp
    applyIntroLessonContent(lessons_);
    applySection2LessonContent(lessons_);
    applySection3LessonContent(lessons_);
}
```

to:

```cpp
    applyIntroLessonContent(lessons_);
    applySection2LessonContent(lessons_);
    applySection3LessonContent(lessons_);
    applySection4LessonContent(lessons_);
}
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/LessonContent.h
    src/LessonContentSection2.cpp
    src/LessonContentSection3.cpp
```

to:

```cmake
    src/LessonContent.h
    src/LessonContentSection2.cpp
    src/LessonContentSection3.cpp
    src/LessonContentSection4.cpp
```

- [ ] **Step 5: Extend the content-coverage tests**

In `tests/LessonManagerTests.cpp`, replace:

```cpp
TEST_CASE(LessonManager_TopicsElevenToThirtyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 30; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsElevenToFortyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 40; ++topicId) {
```

(keep the rest of that test's body unchanged). Then replace:

```cpp
TEST_CASE(LessonManager_TopicsThirtyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 31; topicId <= 100; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsFortyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 41; topicId <= 100; ++topicId) {
```

(keep the rest of that test's body unchanged — there must be exactly
these two content-coverage tests afterward, not three).

- [ ] **Step 6: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `90/90 test(s) passed.` (same count as Phase 14's end state —
this task only renames/widens two existing tests' ranges).

- [ ] **Step 7: Commit**

```bash
git add src/LessonContent.h src/LessonContentSection4.cpp src/LessonManager.cpp CMakeLists.txt tests/LessonManagerTests.cpp
git commit -m "feat(content): add Section 4 lesson content (topics 31-40)"
```

---

### Task 2: Questions for topics 31-34 (ids 653-768)

**Files:**
- Modify: `src/QuestionContent.h` (add one new declaration)
- Create: `src/QuestionsSection4.cpp`
- Modify: `src/QuestionManager.cpp` (include, call, bump `reserve()`)
- Modify: `CMakeLists.txt` (add the new `.cpp`)

**Interfaces:**
- Produces: `void appendSection4Questions(std::vector<Question>& questions);`
  — Task 3 and Task 4 append more `questions.push_back(...)` calls to
  this SAME function body (in this same file) for topics 35-37 and
  38-40 respectively. This task only adds topics 31-34 (ids 653-768).

- [ ] **Step 1: Add the new declaration**

In `src/QuestionContent.h`, add this line after the existing
`appendSection3Questions` declaration (do not remove that one):

```cpp
void appendSection4Questions(std::vector<Question>& questions);
```

- [ ] **Step 2: Write topics 31-34's questions**

Create `src/QuestionsSection4.cpp`:

```cpp
#include "QuestionContent.h"

#include "Question.h"

void appendSection4Questions(std::vector<Question>& questions) {
    // Topic 31: Normal diziler
    questions.push_back(Question{
        .id = 653, .topicId = 31,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizinin ilk elemanının indeksi kaçtır?",
        .options = {"1", "0", "-1", "Dizinin boyutuna bağlıdır"},
        .acceptedAnswers = {"b"},
        .explanation = "Dizilerde indeksleme 0'dan başlar; ilk eleman indeks 0'dadır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 654, .topicId = 31,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int sayilar[5]; ifadesi ne oluşturur?",
        .options = {"5 elemanlı bir dizi", "1 elemanlı bir değişken", "Boş bir vector", "Bir fonksiyon"},
        .acceptedAnswers = {"a"},
        .explanation = "int sayilar[5]; ifadesi 5 elemanlı bir tam sayı dizisi tanımlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 655, .topicId = 31,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int sayilar[3] = {10, 20, 30}; ifadesinde sayilar[1] kaçtır?",
        .options = {"10", "20", "30", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "İndeks 1, dizinin ikinci elemanına (20) karşılık gelir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 656, .topicId = 31,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int sayilar[4] = {1, 2, 3, 4}; dizisinin boyutu tanımlandıktan sonra değiştirilebilir mi?",
        .options = {"Evet, her zaman", "Hayır, C-style dizilerin boyutu sabittir", "Yalnızca küçültülebilir", "Yalnızca büyütülebilir"},
        .acceptedAnswers = {"b"},
        .explanation = "C-style dizilerin boyutu tanımlandığı anda sabitlenir ve sonradan değiştirilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 657, .topicId = 31,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int sayilar[3] = {10, 20, 30}; sayilar[3] ifadesine erişmek ne anlama gelir?",
        .options = {"Dizinin son elemanına erişir", "Sınır dışı (tanımsız davranış) erişimdir", "Derleme hatası oluşur", "0 değerini döndürür"},
        .acceptedAnswers = {"b"},
        .explanation = "3 elemanlı bir dizide geçerli indeksler 0-2'dir; indeks 3 sınır dışıdır ve tanımsız davranışa yol açar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 658, .topicId = 31,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int sayilar[5] = {1, 2, 3, 4, 5}; dizisinde kaç eleman vardır?",
        .options = {"4", "5", "6", "Belirsiz"},
        .acceptedAnswers = {"b"},
        .explanation = "Dizi 5 elemanla tanımlanmıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 659, .topicId = 31,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int sayilar[3]; (başlangıç değeri verilmeden tanımlanan) yerel bir dizinin elemanlarının değeri nedir?",
        .options = {"Otomatik olarak 0 olur", "Belirsizdir (garbage/çöp değer olabilir)", "Her zaman -1 olur", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "Yerel (fonksiyon içi) bir C-style dizi başlangıç değeri verilmeden tanımlanırsa, elemanları belirsiz (initialize edilmemiş) değerler taşır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 660, .topicId = 31,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a[3] = {1, 2, 3}; int b[3] = a; ifadesi geçerli midir?",
        .options = {"Evet, b, a'nın bir kopyasını alır", "Hayır, diziler bu şekilde doğrudan başka bir diziyle başlatılamaz; derleme hatası oluşur", "Evet, ama b boş kalır", "Evet, b ve a aynı belleği paylaşır"},
        .acceptedAnswers = {"b"},
        .explanation = "C-style diziler başka bir dizi değişkeniyle doğrudan bu şekilde başlatılamaz veya atanamaz; bu satır derlenmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 661, .topicId = 31,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizinin elemanlarına köşeli parantez [] ile erişilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Dizi elemanlarına erişim [] operatörüyle yapılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 662, .topicId = 31,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizinin ilk elemanının indeksi 1'dir.",
        .acceptedAnswers = {"2"},
        .explanation = "İlk elemanın indeksi 0'dır, 1 değil.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 663, .topicId = 31,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "C-style bir dizinin boyutu tanımlandıktan sonra değiştirilemez.",
        .acceptedAnswers = {"1"},
        .explanation = "C-style dizilerin boyutu sabittir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 664, .topicId = 31,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Dizi sınırlarının dışına erişmek güvenlidir ve her zaman bir hata mesajı verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Sınır dışı erişim tanımsız davranıştır; her zaman bir hata mesajı vermez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 665, .topicId = 31,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int sayilar[3] = {10, 20, 30}; ifadesinde sayilar[2] değeri 30'dur.",
        .acceptedAnswers = {"1"},
        .explanation = "İndeks 2, dizinin üçüncü (son) elemanına karşılık gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 666, .topicId = 31,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Aynı türden birden fazla değeri tek bir değişken altında saklamak için dizi kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Dizilerin temel amacı budur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 667, .topicId = 31,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sayilar_____; ifadesinin 5 elemanlı bir tam sayı dizisi tanımlaması için boşluğa ne yazılmalı? (örnek: [5])",
        .acceptedAnswers = {"[5]"},
        .explanation = "Dizi boyutu köşeli parantez içinde belirtilir: [5].",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 668, .topicId = 31,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sayilar[3] = {10, 20, 30}; std::cout << sayilar_____; ifadesinin ilk elemanı (10) yazdırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"[0]"},
        .explanation = "İlk elemana erişmek için indeks 0 kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 669, .topicId = 31,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int sayilar[3] = {10, 20, 30}; std::cout << sayilar_____; ifadesinin son elemanı (30) yazdırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"[2]"},
        .explanation = "3 elemanlı dizide son elemanın indeksi 2'dir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 670, .topicId = 31,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayilar[4] = {1, 2, 3, 4}; int toplam = sayilar[0] _____ sayilar[1]; ifadesinin toplam'a 1+2=3 ataması için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"+"},
        .explanation = "1 + 2 = 3 olduğu için toplama operatörü kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 671, .topicId = 31,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayilar[3] = {5, 10, 15}; int ortaEleman = sayilar_____; ifadesinin ortadaki elemanı (10) alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"[1]"},
        .explanation = "3 elemanlı bir dizide ortadaki elemanın indeksi 1'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 672, .topicId = 31,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayilar[3] = {7, 8, 9}; sayilar_____ = 100; ifadesinin ilk elemanı 100 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"[0]"},
        .explanation = "İlk elemana erişmek ve atama yapmak için indeks 0 kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 673, .topicId = 31,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int puanlar[3] = {90, 85, 95};\nint ilkPuan = _____;\nDizinin ilk elemanını alan ifadeyi yazın.",
        .acceptedAnswers = {"puanlar[0]"},
        .explanation = "İlk elemana puanlar[0] ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 674, .topicId = 31,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayilar[4] = {1, 2, 3, 4};\nint sonuncu = _____;\nDizinin son (4.) elemanını alan ifadeyi yazın.",
        .acceptedAnswers = {"sayilar[3]"},
        .explanation = "4 elemanlı dizide son elemanın indeksi 3'tür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 675, .topicId = 31,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int sayilar[4] = {2, 4, 6, 8};\nstd::cout << sayilar[0] << sayilar[3];\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"28"},
        .explanation = "sayilar[0] = 2, sayilar[3] = 8; birlikte '28' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 676, .topicId = 31,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int sayilar[3] = {5, 10, 15};\nint toplam = sayilar[0] + sayilar[1] + sayilar[2];\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30"},
        .explanation = "5 + 10 + 15 = 30.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 677, .topicId = 31,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint sayilar[3] = {1, 2, 3};\nstd::cout << sayilar[1];\n\nProgramcı dizinin ilk elemanını (1) yazdırmak istiyor ama kod 2'yi yazdırıyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << sayilar[0];"},
        .explanation = "İlk elemana erişmek için indeks 0 kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 678, .topicId = 31,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint sayilar[3] = {1, 2, 3};\nstd::cout << sayilar[3];\n\nBu kod sınır dışı (tanımsız davranış) bir erişim içerir; programcı son elemanı (3) yazdırmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << sayilar[2];"},
        .explanation = "3 elemanlı dizide son elemanın indeksi 2'dir; indeks 3 sınır dışıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 679, .topicId = 31,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint sayilar[3] = {1, 2, 3}\nstd::cout << sayilar[0];\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int sayilar[3] = {1, 2, 3};"},
        .explanation = "Satırın sonunda noktalı virgül eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 680, .topicId = 31,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir dizi tanımlayıp ikinci elemanını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << sayilar[1];", "int sayilar[3] = {10, 20, 30};"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce dizi tanımlanır (2), sonra yazdırılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 681, .topicId = 31,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "3 elemanlı bir tam sayı dizisi tanımlayıp, elemanlarını başlangıç değerleriyle doldurup, tüm elemanlarını (indekslerle) ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cout", "<<", "[0]"},
        .explanation = "Program 3 elemanlı bir dizi tanımlamalı ve elemanlarına [] ile erişip yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 32: Dizi elemanlarını değiştirme
    questions.push_back(Question{
        .id = 682, .topicId = 32,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizinin bir elemanını değiştirmek için hangi söz dizimi kullanılır?",
        .options = {"dizi.set(indeks, deger)", "dizi[indeks] = deger;", "dizi = deger;", "dizi.change(deger)"},
        .acceptedAnswers = {"b"},
        .explanation = "Bir dizinin elemanı, dizi[indeks] = deger; şeklinde değiştirilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 683, .topicId = 32,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int a[3] = {1,2,3}; a[0] = 99; işleminden sonra a[0] kaç olur?",
        .options = {"1", "99", "0", "3"},
        .acceptedAnswers = {"b"},
        .explanation = "a[0]'a 99 atandığı için değeri 99 olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 684, .topicId = 32,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int a[3] = {1,2,3}; a[1] = 50; işleminden sonra a[2] kaç olur?",
        .options = {"50", "3", "1", "2"},
        .acceptedAnswers = {"b"},
        .explanation = "Yalnızca a[1] değiştirildi; a[2] hala 3'tür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 685, .topicId = 32,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a[4] = {10,20,30,40}; a[3] = a[0]; işleminden sonra a[3] kaç olur?",
        .options = {"40", "10", "30", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "a[0] değeri (10), a[3]'e atanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 686, .topicId = 32,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a[3] = {1,2,3}; for (int i = 0; i < 3; i++) { a[i] = a[i] * 2; } döngüsünden sonra a[1] kaç olur?",
        .options = {"2", "4", "6", "8"},
        .acceptedAnswers = {"b"},
        .explanation = "a[1] başlangıçta 2'dir; 2 ile çarpılınca 4 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 687, .topicId = 32,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir dizinin tüm elemanlarını tek bir atama ifadesiyle (dizi = {1,2,3};) değiştirmek mümkün müdür (dizi zaten tanımlanmışken)?",
        .options = {"Evet, her zaman mümkündür", "Hayır, C-style dizilerde bu şekilde toplu atama yapılamaz; elemanlar tek tek değiştirilmelidir", "Yalnızca boyut aynıysa mümkündür", "Yalnızca vector'de mümkün değildir, dizide mümkündür"},
        .acceptedAnswers = {"b"},
        .explanation = "C-style bir dizi zaten tanımlandıktan sonra süslü parantez listesiyle toplu olarak yeniden atanamaz; her eleman ayrı değiştirilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 688, .topicId = 32,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a[3] = {5,10,15}; a[0] = a[1] = 20; işleminden sonra a[0] ve a[1] ne olur?",
        .options = {"a[0]=20, a[1]=20", "a[0]=10, a[1]=20", "a[0]=20, a[1]=10", "Derleme hatası oluşur"},
        .acceptedAnswers = {"a"},
        .explanation = "Zincirleme atama sağdan sola değerlendirilir: önce a[1]=20 olur, sonra a[0]=a[1]=20 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 689, .topicId = 32,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a[5] = {1,2,3,4,5}; for (int i = 0; i < 5; i++) { a[i] = a[4-i]; } döngüsü tamamlandığında a[0] kaç olur?",
        .options = {"1", "5", "3", "4"},
        .acceptedAnswers = {"b"},
        .explanation = "Döngü başladığında ilk iş olarak a[0] = a[4] atanır; bu noktada a[4] hâlâ değişmemiş orijinal değeri (5) taşır, bu yüzden a[0] 5 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 690, .topicId = 32,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizinin bir elemanı, [] ve indeks kullanılarak değiştirilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Bu, dizi elemanlarını değiştirmenin standart yoludur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 691, .topicId = 32,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Dizideki her eleman bağımsız olarak değiştirilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Her eleman kendi indeksiyle bağımsız olarak değiştirilebilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 692, .topicId = 32,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int a[3] = {1,2,3}; a[0] = 5; işleminden sonra a[1] ve a[2] de değişir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yalnızca a[0] değişir; diğer elemanlar etkilenmez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 693, .topicId = 32,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir dizinin tamamı tek bir atama ifadesiyle (dizi = {...};) değiştirilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "C-style diziler zaten tanımlandıktan sonra bu şekilde toplu atanamaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 694, .topicId = 32,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int a[3] = {1,2,3}; a[2] = a[0]; işleminden sonra a[2] değeri 1'dir.",
        .acceptedAnswers = {"1"},
        .explanation = "a[0] değeri (1), a[2]'ye atanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 695, .topicId = 32,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Dizi elemanlarını değiştirirken sınır dışı bir indekse atama yapmak güvenlidir ve her zaman hata verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Sınır dışı atama tanımsız davranıştır; her zaman hata vermez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 696, .topicId = 32,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a[3] = {1,2,3}; a_____ = 100; ifadesinin ilk elemanı 100 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"[0]"},
        .explanation = "İlk eleman indeks 0'dadır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 697, .topicId = 32,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a[3] = {1,2,3}; a_____ = 100; ifadesinin son elemanı 100 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"[2]"},
        .explanation = "3 elemanlı dizide son eleman indeks 2'dedir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 698, .topicId = 32,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int a[4] = {1,2,3,4}; a[1] _____ 50; ifadesinin ikinci elemanı 50 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"="},
        .explanation = "Atama operatörü = kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 699, .topicId = 32,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a[3] = {5,10,15}; a[0] = a[0] _____ 2; ifadesinin ilk elemanı iki katına (10) çıkarması için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "5 * 2 = 10 olduğu için çarpma operatörü kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 700, .topicId = 32,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a[5]; for (int i = 0; i _____ 5; i++) { a[i] = i; } döngüsünün tüm 5 elemanı doldurması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"<"},
        .explanation = "i < 5 koşulu, i'nin 0'dan 4'e kadar (5 kez) döngüye girmesini sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 701, .topicId = 32,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a[3] = {1,2,3}; a[1] _____ a[2]; ifadesinin ikinci elemana üçüncü elemanın değerini (3) ataması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"="},
        .explanation = "Atama operatörü = kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 702, .topicId = 32,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int puanlar[3] = {60, 70, 80};\n_____\nİlk elemanı 100 yapan atama satırını yazın.",
        .acceptedAnswers = {"puanlar[0] = 100;"},
        .explanation = "İlk elemana atama puanlar[0] = 100; şeklinde yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 703, .topicId = 32,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a[4] = {1, 2, 3, 4};\nfor (int i = 0; i < 4; i++) {\n    _____\n}\nHer elemanı kendi indeksiyle çarpan atama satırını yazın.",
        .acceptedAnswers = {"a[i] = a[i] * i;", "a[i] *= i;"},
        .explanation = "Her eleman kendi indeksiyle çarpılarak güncellenir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 704, .topicId = 32,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a[3] = {1, 2, 3};\na[1] = 99;\nstd::cout << a[0] << a[1] << a[2];\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1993"},
        .explanation = "a[0]=1, a[1]=99, a[2]=3; birlikte '1993' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 705, .topicId = 32,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a[4] = {2, 4, 6, 8};\nfor (int i = 0; i < 4; i++) {\n    a[i] = a[i] + 1;\n}\nstd::cout << a[0] << a[3];\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"39"},
        .explanation = "a[0] = 2+1 = 3, a[3] = 8+1 = 9; birlikte '39' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 706, .topicId = 32,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a[3] = {1, 2, 3};\na[3] = 100;\n\nBu satır sınır dışı (tanımsız davranış) bir yazma içerir. Programcı dizinin son elemanını 100 yapmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a[2] = 100;"},
        .explanation = "3 elemanlı dizide son elemanın indeksi 2'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 707, .topicId = 32,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint a[3] = {1, 2, 3};\na = 100;\n\nProgramcı ilk elemanı 100 yapmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"a[0] = 100;"},
        .explanation = "Dizinin kendisine doğrudan atama yapılamaz; belirli bir elemana [] ile erişilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 708, .topicId = 32,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint a[3] = {1, 2, 3};\na(1) = 50;\n\nProgramcı ikinci elemanı 50 yapmak istiyor. Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"a[1] = 50;"},
        .explanation = "Dizi elemanına erişim () değil [] ile yapılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 709, .topicId = 32,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir dizi tanımlayıp ilk elemanını değiştirip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << a[0];", "a[0] = 100;", "int a[3] = {1, 2, 3};"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce dizi tanımlanır (3), sonra değiştirilir (2), en son yazdırılır (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 710, .topicId = 32,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "3 elemanlı bir tam sayı dizisi tanımlayıp, bir döngü kullanarak her elemanı kendi indeksinin karesiyle değiştiren ve sonucu yazdıran bir program yazın.",
        .acceptedAnswers = {"for", "cout", "<<", "[i]"},
        .explanation = "Program bir döngü içinde her elemanı a[i] = i * i; şeklinde güncellemeli ve yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 33: std::array
    questions.push_back(Question{
        .id = 711, .topicId = 33,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::array hangi kütüphanede tanımlıdır?",
        .options = {"<vector>", "<array>", "<string>", "<algorithm>"},
        .acceptedAnswers = {"b"},
        .explanation = "std::array, <array> kütüphanesinde tanımlıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 712, .topicId = 33,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::array<int, 3> sayilar = {1,2,3}; tanımında 3 sayısı neyi belirtir?",
        .options = {"Başlangıç değerini", "Dizinin sabit boyutunu", "Bir indeksi", "Bellek adresini"},
        .acceptedAnswers = {"b"},
        .explanation = "İkinci template parametresi, std::array'in sabit boyutunu belirtir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 713, .topicId = 33,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::array<int, 4> a = {1,2,3,4}; a.size() ifadesi kaç döner?",
        .options = {"3", "4", "5", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "a, 4 elemanlı tanımlandığı için size() 4 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 714, .topicId = 33,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::array'in boyutu çalışma zamanında (runtime) değiştirilebilir mi?",
        .options = {"Evet, push_back ile büyütülebilir", "Hayır, boyut derleme zamanında sabittir", "Yalnızca küçültülebilir", "Yalnızca ilk elemandan sonra değiştirilebilir"},
        .acceptedAnswers = {"b"},
        .explanation = "std::array'in boyutu bir template parametresidir ve derleme zamanında sabitlenir; push_back gibi bir üye fonksiyonu yoktur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 715, .topicId = 33,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::array<int, 3> a = {10,20,30}; a.at(5) çağrısı ne yapar (5, sınırların dışında)?",
        .options = {"0 döndürür", "std::out_of_range istisnası fırlatır", "Programı sessizce durdurur", "Derleme hatası verir"},
        .acceptedAnswers = {"b"},
        .explanation = "at(), sınır dışı bir indeks için std::out_of_range istisnası fırlatır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 716, .topicId = 33,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::array<int, 3> a = {10,20,30}; a[5] çağrısı (at() değil, [] kullanılarak) ne yapar?",
        .options = {"std::out_of_range istisnası fırlatır", "Tanımsız davranıştır (istisna fırlatmaz)", "0 döndürür", "Derleme hatası verir"},
        .acceptedAnswers = {"b"},
        .explanation = "[] operatörü sınır kontrolü yapmaz; sınır dışı erişim tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 717, .topicId = 33,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::array, C-style dizilere göre hangi avantajı sunar?",
        .options = {"Boyutu çalışma zamanında değiştirilebilir", "size(), at() gibi yararlı üye fonksiyonlar sunar", "Her zaman daha az bellek kullanır", "Yalnızca string'lerle çalışır"},
        .acceptedAnswers = {"b"},
        .explanation = "std::array, C-style dizilerin sunmadığı size(), at() gibi güvenli ve kullanışlı üye fonksiyonlar sunar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 718, .topicId = 33,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::array<int, 3> a = {1,2,3}; std::array<int, 3> b = a; işleminden sonra b[0]'ı değiştirmek a[0]'ı etkiler mi?",
        .options = {"Evet, aynı belleği paylaşırlar", "Hayır, b bağımsız bir kopyadır, a'yı etkilemez", "Yalnızca ilk eleman paylaşılır", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "std::array değer semantiğine sahiptir; b, a'nın bağımsız bir kopyasıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 719, .topicId = 33,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::array kullanmak için <array> kütüphanesi eklenmelidir.",
        .acceptedAnswers = {"1"},
        .explanation = "std::array, <array> kütüphanesinde tanımlıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 720, .topicId = 33,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::array'in boyutu çalışma zamanında değiştirilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "std::array'in boyutu derleme zamanında sabittir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 721, .topicId = 33,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::array, size() üye fonksiyonuyla eleman sayısını döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "size() üye fonksiyonu eleman sayısını döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 722, .topicId = 33,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::array'de push_back() ile yeni eleman eklenebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "std::array'in boyutu sabit olduğu için push_back() üye fonksiyonu yoktur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 723, .topicId = 33,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::array'de at(), sınır dışı erişimde bir istisna fırlatır.",
        .acceptedAnswers = {"1"},
        .explanation = "at(), sınır dışı erişimde std::out_of_range fırlatır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 724, .topicId = 33,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::array'de [] operatörü, at() gibi sınır kontrolü yapar.",
        .acceptedAnswers = {"2"},
        .explanation = "[] operatörü sınır kontrolü yapmaz; yalnızca at() yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 725, .topicId = 33,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::_____<int, 3> sayilar = {1, 2, 3}; ifadesinde boşluğa hangi tür yazılmalı?",
        .acceptedAnswers = {"array"},
        .explanation = "std::array türü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 726, .topicId = 33,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::array<int, 5> a = {1,2,3,4,5}; int n = a._____(); ifadesinin eleman sayısını (5) döndürmesi için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"size"},
        .explanation = "size() eleman sayısını döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 727, .topicId = 33,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::array<int, 3> a = {10,20,30}; int x = a._____(1); ifadesinin sınır kontrollü erişimle ikinci elemanı (20) alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"at"},
        .explanation = "at() sınır kontrollü erişim sağlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 728, .topicId = 33,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::array<int, _____> a = {1, 2, 3, 4}; ifadesinin 4 elemanlı bir dizi tanımlaması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"4"},
        .explanation = "İkinci template parametresi eleman sayısını belirtir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 729, .topicId = 33,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::array<int, 3> a = {5, 10, 15}; a.at(_____) çağrısının std::out_of_range fırlatması için boşluğa (sınırların dışında) hangi sayı yazılabilir? (örnek: 3)",
        .acceptedAnswers = {"3"},
        .explanation = "Geçerli indeksler 0-2'dir; 3 ve üzeri sınır dışıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 730, .topicId = 33,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::array<int, 3> a = {1, 2, 3}; a_____ = 99; ifadesinin (at() kullanmadan) ilk elemanı 99 yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"[0]"},
        .explanation = "[] operatörüyle de eleman değiştirilebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 731, .topicId = 33,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "#include <array>\n\nint main() {\n    _____\n    std::cout << sayilar.size();\n}\n3 elemanlı, 1,2,3 değerleriyle dolu bir std::array tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::array<int, 3> sayilar = {1, 2, 3};"},
        .explanation = "std::array<int, 3> ile 3 elemanlı bir dizi tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 732, .topicId = 33,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::array<int, 4> a = {10, 20, 30, 40};\nint ikinci = _____;\nat() kullanarak ikinci elemanı (20) alan ifadeyi yazın.",
        .acceptedAnswers = {"a.at(1)"},
        .explanation = "İkinci eleman indeks 1'dedir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 733, .topicId = 33,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::array<int, 3> a = {7, 8, 9};\nstd::cout << a.size();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "a, 3 elemanlı tanımlandığı için size() 3 döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 734, .topicId = 33,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::array<int, 4> a = {1, 2, 3, 4};\nstd::cout << a.at(0) << a.at(3);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"14"},
        .explanation = "a.at(0)=1, a.at(3)=4; birlikte '14' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 735, .topicId = 33,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::array<int, 3> a = {1, 2, 3};\nstd::cout << a.size;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << a.size();"},
        .explanation = "size() bir üye fonksiyon çağrısıdır ve parantez gerektirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 736, .topicId = 33,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::array<int, 3> a = {1, 2, 3};\nstd::cout << a.at(3);\n\nBu kod çalışma zamanında std::out_of_range istisnası fırlatarak çöker (3, geçerli indeks aralığının dışında). Programcı son elemanı (3) yazdırmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << a.at(2);"},
        .explanation = "3 elemanlı dizide son elemanın indeksi 2'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 737, .topicId = 33,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::array<int, 3> a = {1, 2, 3};\nstd::cout << a.at(1;\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"std::cout << a.at(1);"},
        .explanation = "Kapanış parantezi ve noktalı virgül eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 738, .topicId = 33,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir std::array tanımlayıp boyutunu yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << a.size();", "std::array<int, 3> a = {1, 2, 3};"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce dizi tanımlanır (2), sonra boyutu yazdırılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 739, .topicId = 33,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "3 elemanlı bir std::array<int, 3> tanımlayıp, size() ile eleman sayısını, at() ile ilk elemanı ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"array", "size", "at", "cout", "<<"},
        .explanation = "Program std::array tanımlamalı, size() ve at() üye fonksiyonlarını kullanmalıdır.",
        .baseXp = 40,
    });

    // Topic 34: vector
    questions.push_back(Question{
        .id = 740, .topicId = 34,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::vector hangi kütüphanede tanımlıdır?",
        .options = {"<array>", "<vector>", "<string>", "<list>"},
        .acceptedAnswers = {"b"},
        .explanation = "std::vector, <vector> kütüphanesinde tanımlıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 741, .topicId = 34,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector'ün C-style dizilere göre temel farkı nedir?",
        .options = {"Daha az bellek kullanır", "Boyutu çalışma zamanında değişebilir (dinamiktir)", "Yalnızca string saklayabilir", "Elemanlarına erişilemez"},
        .acceptedAnswers = {"b"},
        .explanation = "vector, boyutu çalışma zamanında büyüyüp küçülebilen dinamik bir dizidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 742, .topicId = 34,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1,2,3}; v.size() ifadesi kaç döner?",
        .options = {"2", "3", "4", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "v, 3 elemanla tanımlandığı için size() 3 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 743, .topicId = 34,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v; v.push_back(5); işleminden sonra v.size() kaç olur?",
        .options = {"0", "1", "5", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "Boş bir vector'e bir eleman eklendiğinde boyut 1 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 744, .topicId = 34,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1,2,3}; v[5] çağrısı (sınırların dışında) ne yapar?",
        .options = {"std::out_of_range fırlatır", "Tanımsız davranıştır", "0 döndürür", "Derleme hatası verir"},
        .acceptedAnswers = {"b"},
        .explanation = "[] operatörü sınır kontrolü yapmaz; sınır dışı erişim tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 745, .topicId = 34,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector, boş bir vector olarak (eleman sayısı belirtilmeden) tanımlanabilir mi?",
        .options = {"Hayır, mutlaka en az 1 eleman gerekir", "Evet, std::vector<int> v; şeklinde boş tanımlanabilir", "Yalnızca string vector'lerinde mümkündür", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "std::vector<int> v; boş bir vector tanımlar; elemanlar sonradan eklenebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 746, .topicId = 34,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1,2,3}; v.push_back(4); v.size() kaç olur?",
        .options = {"3", "4", "5", "1"},
        .acceptedAnswers = {"b"},
        .explanation = "3 elemanlı vector'e bir eleman daha eklendiği için boyut 4 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 747, .topicId = 34,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector, elemanlarını bellekte nasıl saklar?",
        .options = {"Rastgele, dağınık konumlarda", "Ardışık (contiguous), diziye benzer şekilde", "Yalnızca işaretçilerle bağlantılı olarak", "Sıkıştırılmış olarak"},
        .acceptedAnswers = {"b"},
        .explanation = "std::vector, elemanlarını bellekte ardışık (contiguous) olarak saklar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 748, .topicId = 34,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::vector'ün boyutu çalışma zamanında büyüyüp küçülebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "vector dinamik boyutludur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 749, .topicId = 34,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::vector kullanmak için <array> kütüphanesi eklenmelidir.",
        .acceptedAnswers = {"2"},
        .explanation = "std::vector için <vector> kütüphanesi eklenmelidir, <array> değil.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 750, .topicId = 34,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v; şeklinde boş bir vector tanımlanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Boş bir vector tanımlamak geçerlidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 751, .topicId = 34,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::vector'ün boyutu C-style diziler gibi derleme zamanında sabittir.",
        .acceptedAnswers = {"2"},
        .explanation = "vector'ün boyutu çalışma zamanında dinamik olarak değişir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 752, .topicId = 34,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1,2,3}; v[10] ifadesi tanımsız davranışa yol açar.",
        .acceptedAnswers = {"1"},
        .explanation = "10, geçerli indeks aralığının dışında olduğu için tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 753, .topicId = 34,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::vector, elemanlarını bellekte ardışık (contiguous) olarak saklar.",
        .acceptedAnswers = {"1"},
        .explanation = "vector, elemanlarını ardışık bellek bloğunda saklar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 754, .topicId = 34,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::_____<int> sayilar = {1, 2, 3}; ifadesinde boşluğa hangi tür yazılmalı?",
        .acceptedAnswers = {"vector"},
        .explanation = "std::vector türü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 755, .topicId = 34,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1,2,3}; int n = v._____(); ifadesinin eleman sayısını döndürmesi için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"size"},
        .explanation = "size() eleman sayısını döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 756, .topicId = 34,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> _____; ifadesinin boş bir int vector'ü tanımlaması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"v"},
        .explanation = "Değişken adı v olarak tanımlanabilir; boşluğa bir değişken adı yazılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 757, .topicId = 34,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1,2,3}; v._____(4); ifadesinin vector'ün sonuna 4 eklemesi için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"push_back"},
        .explanation = "push_back(), vector'ün sonuna eleman ekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 758, .topicId = 34,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v(_____, 0); ifadesinin 5 elemanlı, hepsi 0 olan bir vector oluşturması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"5"},
        .explanation = "İlk parametre eleman sayısını, ikinci parametre başlangıç değerini belirtir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 759, .topicId = 34,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {10, 20, 30}; std::cout << v_____; ifadesinin ilk elemanı (10) yazdırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"[0]"},
        .explanation = "İlk eleman indeks 0'dadır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 760, .topicId = 34,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "#include <vector>\n\nint main() {\n    _____\n    std::cout << v.size();\n}\n1, 2, 3 değerleriyle bir vector tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {1, 2, 3};"},
        .explanation = "std::vector<int> ile bir tam sayı vector'ü tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 761, .topicId = 34,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2};\n_____\nstd::cout << v.size();\nVector'e 3 değerini ekleyen satırı yazın.",
        .acceptedAnswers = {"v.push_back(3);"},
        .explanation = "push_back(3), vector'ün sonuna 3 ekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 762, .topicId = 34,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3};\nv.push_back(4);\nstd::cout << v.size();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4"},
        .explanation = "3 elemanlı vector'e bir eleman eklendiği için boyut 4 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 763, .topicId = 34,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v;\nv.push_back(10);\nv.push_back(20);\nstd::cout << v[0] << v[1] << v.size();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10202"},
        .explanation = "v[0]=10, v[1]=20, v.size()=2; birlikte '10202' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 764, .topicId = 34,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3}\nstd::cout << v.size();\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::vector<int> v = {1, 2, 3};"},
        .explanation = "Satırın sonunda noktalı virgül eksik.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 765, .topicId = 34,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nstd::cout << v[5];\n\nBu kod tanımsız davranışa yol açar (5, geçerli indeks aralığının dışında). Programcı son elemanı (3) yazdırmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << v[2];"},
        .explanation = "3 elemanlı vector'de son elemanın indeksi 2'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 766, .topicId = 34,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {1, 2, 3};\nv.pushback(4);\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"v.push_back(4);"},
        .explanation = "Fonksiyon adı pushback değil push_back'tir (alt çizgi eksik).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 767, .topicId = 34,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vector tanımlayıp eleman ekleyip boyutunu yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << v.size();", "v.push_back(4);", "std::vector<int> v = {1, 2, 3};"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce vector tanımlanır (3), sonra eleman eklenir (2), en son boyut yazdırılır (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 768, .topicId = 34,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Boş bir tam sayı vector'ü tanımlayıp, push_back ile 3 eleman ekleyip, vector'ün boyutunu ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"vector", "push_back", "size", "cout", "<<"},
        .explanation = "Program boş bir vector tanımlamalı, push_back ile 3 eleman eklemeli ve size() ile boyutu yazdırmalıdır.",
        .baseXp = 40,
    });
}
```

- [ ] **Step 3: Wire the new function into `QuestionManager`**

`src/QuestionManager.cpp` already includes `"QuestionContent.h"` (from
Phase 13). Change the constructor's `reserve` call from:

```cpp
    questions_.reserve(652);
```

to:

```cpp
    questions_.reserve(942);
```

Then change the constructor's final lines from:

```cpp
    appendSection3Questions(questions_);
}
```

to:

```cpp
    appendSection3Questions(questions_);
    appendSection4Questions(questions_);
}
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/QuestionContent.h
    src/QuestionsSection2.cpp
    src/QuestionsSection3.cpp
```

to:

```cmake
    src/QuestionContent.h
    src/QuestionsSection2.cpp
    src/QuestionsSection3.cpp
    src/QuestionsSection4.cpp
```

- [ ] **Step 5: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `90/90 test(s) passed.` (topics 31-34 now have 116 more
questions, but no existing test currently counts them individually, so
the pass count is unchanged from Task 1's end state).

- [ ] **Step 6: Commit**

```bash
git add src/QuestionContent.h src/QuestionsSection4.cpp src/QuestionManager.cpp CMakeLists.txt
git commit -m "feat(content): add questions for topics 31-34 (ids 653-768)"
```

---

### Task 3: Questions for topics 35-37 (ids 769-855)

**Files:**
- Modify: `src/QuestionsSection4.cpp` (append more
  `questions.push_back(...)` calls to the existing `appendSection4Questions`
  function body, right before its closing `}`)

**Interfaces:**
- Consumes: `appendSection4Questions`'s existing body from Task 2 (ends
  after topic 34's WriteCode question, id 768).
- Produces: the same function extended through id 855. Task 4 appends
  topics 38-40 after this task's content, same file, same function.

- [ ] **Step 1: Append topics 35-37's questions**

In `src/QuestionsSection4.cpp`, insert the following right before the
function's closing `}` (i.e. immediately after the `id = 768` WriteCode
question added in Task 2):

```cpp
    // Topic 35: push_back() ve pop_back()
    questions.push_back(Question{
        .id = 769, .topicId = 35,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "push_back() ne işe yarar?",
        .options = {"Vector'ün başına eleman ekler", "Vector'ün sonuna eleman ekler", "Vector'ü boşaltır", "Vector'ü sıralar"},
        .acceptedAnswers = {"b"},
        .explanation = "push_back(), vector'ün sonuna yeni bir eleman ekler.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 770, .topicId = 35,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "pop_back() ne işe yarar?",
        .options = {"Vector'ün ilk elemanını siler", "Vector'ün son elemanını siler", "Vector'e eleman ekler", "Vector'ü kopyalar"},
        .acceptedAnswers = {"b"},
        .explanation = "pop_back(), vector'ün son elemanını siler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 771, .topicId = 35,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1,2}; v.push_back(3); v.size() kaç olur?",
        .options = {"2", "3", "4", "1"},
        .acceptedAnswers = {"b"},
        .explanation = "2 elemanlı vector'e bir eleman eklendiği için boyut 3 olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 772, .topicId = 35,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1,2,3}; v.pop_back(); v.size() kaç olur?",
        .options = {"2", "3", "4", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "3 elemanlı vector'den bir eleman silindiği için boyut 2 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 773, .topicId = 35,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "pop_back(), silinen elemanın değerini geri döndürür mü?",
        .options = {"Evet, her zaman döndürür", "Hayır, void döner, değeri döndürmez", "Yalnızca son eleman ise döndürür", "Yalnızca vector boşsa döndürür"},
        .acceptedAnswers = {"b"},
        .explanation = "pop_back() void döner; silinen elemanın değerini geri vermez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 774, .topicId = 35,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Boş bir vector'de pop_back() çağırmak ne yapar?",
        .options = {"Güvenli bir şekilde hiçbir şey yapmaz", "Tanımsız davranıştır", "std::out_of_range fırlatır", "0 döndürür"},
        .acceptedAnswers = {"b"},
        .explanation = "Boş bir vector'de pop_back() çağırmak tanımsız davranışa yol açar; ne güvenli bir no-op'tur ne de istisna fırlatır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 775, .topicId = 35,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1,2,3}; v.push_back(4); v.pop_back(); v.size() kaç olur?",
        .options = {"2", "3", "4", "5"},
        .acceptedAnswers = {"b"},
        .explanation = "3 elemanlı vector'e bir eklenir (4 olur), sonra bir silinir (3'e döner).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 776, .topicId = 35,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v; v.push_back(10); v.push_back(20); v.pop_back(); v[0] kaç olur?",
        .options = {"10", "20", "0", "Hata"},
        .acceptedAnswers = {"a"},
        .explanation = "10 ve 20 eklendikten sonra pop_back() son elemanı (20) siler; v[0] hala 10'dur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 777, .topicId = 35,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "push_back(), vector'ün sonuna yeni bir eleman ekler.",
        .acceptedAnswers = {"1"},
        .explanation = "push_back()'in işlevi budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 778, .topicId = 35,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "pop_back(), vector'ün ilk elemanını siler.",
        .acceptedAnswers = {"2"},
        .explanation = "pop_back() son elemanı siler, ilk elemanı değil.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 779, .topicId = 35,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "push_back() her çağrıldığında vector'ün boyutu 1 artar.",
        .acceptedAnswers = {"1"},
        .explanation = "Her push_back() çağrısı boyutu 1 artırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 780, .topicId = 35,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "pop_back() silinen elemanın değerini geri döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "pop_back() void döner, değeri döndürmez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 781, .topicId = 35,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Boş bir vector'de pop_back() çağırmak tanımsız davranışa yol açar.",
        .acceptedAnswers = {"1"},
        .explanation = "Boş bir vector'de pop_back() çağırmak tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 782, .topicId = 35,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "push_back(), belirli bir indekse eleman ekler.",
        .acceptedAnswers = {"2"},
        .explanation = "push_back() her zaman sona ekler, belirli bir indekse değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 783, .topicId = 35,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2}; v._____(3); ifadesinin sona 3 eklemesi için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"push_back"},
        .explanation = "push_back(3), vector'ün sonuna 3 ekler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 784, .topicId = 35,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2, 3}; v._____(); ifadesinin son elemanı silmesi için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"pop_back"},
        .explanation = "pop_back(), son elemanı siler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 785, .topicId = 35,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2}; v.push_back(3); v._____(); (boyutu yazdırmak için) boşluğa ne yazılmalı?",
        .acceptedAnswers = {"size"},
        .explanation = "size() eleman sayısını döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 786, .topicId = 35,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v; v.push_back(1); v.push_back(2); v._____(); işleminden sonra v.size() 1 olması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"pop_back"},
        .explanation = "pop_back() bir eleman silerek boyutu 2'den 1'e düşürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 787, .topicId = 35,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3}; v.pop_back(); v.pop_back(); v.size() kaç olur? (sayı olarak yazın)",
        .acceptedAnswers = {"1"},
        .explanation = "3 elemandan 2'si silindiği için 1 eleman kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 788, .topicId = 35,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v; for (int i = 0; i < 3; i++) { v._____(i); } döngüsünün v'ye sırayla 0,1,2 eklemesi için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"push_back"},
        .explanation = "Her turda push_back(i) çağrılarak i değeri eklenir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 789, .topicId = 35,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2};\n_____\nstd::cout << v.size();\nVector'e 3 değerini ekleyen satırı yazın.",
        .acceptedAnswers = {"v.push_back(3);"},
        .explanation = "push_back(3), vector'ün sonuna 3 ekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 790, .topicId = 35,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3};\n_____\nstd::cout << v.size();\nVector'ün son elemanını silen satırı yazın.",
        .acceptedAnswers = {"v.pop_back();"},
        .explanation = "pop_back(), vector'ün son elemanını siler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 791, .topicId = 35,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2};\nv.push_back(3);\nstd::cout << v.size();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "2 elemanlı vector'e bir eleman eklendiği için boyut 3 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 792, .topicId = 35,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 3, 4};\nv.pop_back();\nv.pop_back();\nstd::cout << v.size() << v[0];\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"21"},
        .explanation = "4 elemandan 2'si silindiği için boyut 2 olur; v[0] etkilenmediği için hala 1'dir; birlikte '21'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 793, .topicId = 35,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nv.pop_back;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"v.pop_back();"},
        .explanation = "pop_back bir üye fonksiyon çağrısıdır ve parantez gerektirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 794, .topicId = 35,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v;\nv.pop_back();\n\nBu kod tanımsız davranışa yol açar çünkü v boştur. Programcı önce bir eleman eklemek istiyor. Hatalı satırı, v'ye 1 ekleyecek şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"v.push_back(1);"},
        .explanation = "Boş bir vector'de pop_back() çağırmadan önce push_back ile eleman eklenmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 795, .topicId = 35,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {1, 2, 3};\nv.pop_back(4);\n\nProgramcı son elemanı silmek istiyor (pop_back parametre almaz). Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"v.pop_back();"},
        .explanation = "pop_back() hiçbir parametre almaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 796, .topicId = 35,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vector tanımlayıp son elemanını silip boyutunu yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << v.size();", "v.pop_back();", "std::vector<int> v = {1, 2, 3};"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce vector tanımlanır (3), sonra eleman silinir (2), en son boyut yazdırılır (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 797, .topicId = 35,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Boş bir vector'e push_back ile 5 eleman ekleyip, ardından pop_back ile son elemanı silip, kalan boyutu ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"push_back", "pop_back", "size", "cout", "<<"},
        .explanation = "Program push_back ile eleman eklemeli, pop_back ile silmeli ve size() ile boyutu yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 36: size(), front(), back() ve at()
    questions.push_back(Question{
        .id = 798, .topicId = 36,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "front() hangi elemanı döndürür?",
        .options = {"Son elemanı", "İlk elemanı", "Rastgele bir elemanı", "Ortadaki elemanı"},
        .acceptedAnswers = {"b"},
        .explanation = "front(), vector'ün ilk elemanına referans döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 799, .topicId = 36,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "back() hangi elemanı döndürür?",
        .options = {"İlk elemanı", "Son elemanı", "İkinci elemanı", "Hiçbirini"},
        .acceptedAnswers = {"b"},
        .explanation = "back(), vector'ün son elemanına referans döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 800, .topicId = 36,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {10,20,30}; v.front() kaç döner?",
        .options = {"10", "20", "30", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "front(), ilk elemanı (10) döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 801, .topicId = 36,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {10,20,30}; v.back() kaç döner?",
        .options = {"10", "20", "30", "0"},
        .acceptedAnswers = {"c"},
        .explanation = "back(), son elemanı (30) döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 802, .topicId = 36,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "at() ile [] arasındaki temel fark nedir?",
        .options = {"at() daha hızlıdır", "at() sınır dışı erişimde istisna fırlatır, [] fırlatmaz", "[] yalnızca vector'de çalışır", "Aralarında fark yoktur"},
        .acceptedAnswers = {"b"},
        .explanation = "at() sınır kontrolü yapar ve istisna fırlatır; [] yapmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 803, .topicId = 36,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1,2,3}; v.at(5) çağrısı ne yapar?",
        .options = {"0 döndürür", "std::out_of_range istisnası fırlatır", "Tanımsız davranıştır, sessizce devam eder", "Derleme hatası verir"},
        .acceptedAnswers = {"b"},
        .explanation = "at(), sınır dışı erişimde std::out_of_range fırlatır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 804, .topicId = 36,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Boş bir vector'de front() çağırmak ne yapar?",
        .options = {"0 döndürür", "Tanımsız davranıştır", "std::out_of_range fırlatır", "Derleme hatası verir"},
        .acceptedAnswers = {"b"},
        .explanation = "Boş bir vector'de front() çağırmak tanımsız davranıştır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 805, .topicId = 36,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {5,10,15}; v.size() ile v.at(v.size()-1) birlikte kullanılırsa ne elde edilir?",
        .options = {"İlk eleman (5)", "Son eleman (15)", "Ortadaki eleman (10)", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "v.size()-1, son elemanın indeksidir (2); v.at(2) son elemanı (15) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 806, .topicId = 36,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "front(), bir vector'ün ilk elemanını döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "front()'un işlevi budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 807, .topicId = 36,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "back(), bir vector'ün ilk elemanını döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "back() son elemanı döndürür, ilkini değil.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 808, .topicId = 36,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "at(), sınır dışı erişimde bir istisna fırlatır.",
        .acceptedAnswers = {"1"},
        .explanation = "at(), std::out_of_range fırlatır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 809, .topicId = 36,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "[] operatörü, at() gibi sınır kontrolü yapar.",
        .acceptedAnswers = {"2"},
        .explanation = "[] sınır kontrolü yapmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 810, .topicId = 36,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Boş bir vector'de front() veya back() çağırmak tanımsız davranışa yol açar.",
        .acceptedAnswers = {"1"},
        .explanation = "İkisi de boş bir vector'de tanımsız davranışa yol açar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 811, .topicId = 36,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "size(), bir vector'ün eleman sayısını döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "size()'ın işlevi budur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 812, .topicId = 36,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2, 3}; int ilk = v._____(); ifadesinin ilk elemanı alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"front"},
        .explanation = "front() ilk elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 813, .topicId = 36,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2, 3}; int son = v._____(); ifadesinin son elemanı alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"back"},
        .explanation = "back() son elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 814, .topicId = 36,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2, 3}; int ikinci = v._____(1); ifadesinin sınır kontrollü erişimle ikinci elemanı alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"at"},
        .explanation = "at() sınır kontrollü erişim sağlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 815, .topicId = 36,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3}; int n = v._____(); ifadesinin eleman sayısını alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"size"},
        .explanation = "size() eleman sayısını döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 816, .topicId = 36,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {10, 20, 30}; int son = v.at(v._____() - 1); ifadesinin son elemanı almasını sağlayan (size ya da benzer) fonksiyon adını boşluğa yazın.",
        .acceptedAnswers = {"size"},
        .explanation = "size()-1, son elemanın indeksidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 817, .topicId = 36,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {5, 10}; v._____(3) çağrısının std::out_of_range fırlatması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"at"},
        .explanation = "at(3), 2 elemanlı bir vector için sınır dışıdır ve istisna fırlatır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 818, .topicId = 36,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {7, 8, 9};\nint ilkEleman = _____;\nfront() kullanarak ilk elemanı alan ifadeyi yazın.",
        .acceptedAnswers = {"v.front()"},
        .explanation = "front() ilk elemanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 819, .topicId = 36,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {7, 8, 9};\nint sonEleman = _____;\nback() kullanarak son elemanı alan ifadeyi yazın.",
        .acceptedAnswers = {"v.back()"},
        .explanation = "back() son elemanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 820, .topicId = 36,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 5, 6};\nstd::cout << v.front() << v.back();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"46"},
        .explanation = "front()=4, back()=6; birlikte '46' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 821, .topicId = 36,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 3, 4};\nstd::cout << v.size() << v.at(0) << v.at(v.size() - 1);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"414"},
        .explanation = "size()=4, at(0)=1, at(3)=4; birlikte '414' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 822, .topicId = 36,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nstd::cout << v.front;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << v.front();"},
        .explanation = "front bir üye fonksiyon çağrısıdır ve parantez gerektirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 823, .topicId = 36,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nstd::cout << v.at(10);\n\nBu kod çalışma zamanında std::out_of_range istisnası fırlatarak çöker. Programcı son elemanı yazdırmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << v.at(2);"},
        .explanation = "3 elemanlı vector'de son elemanın indeksi 2'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 824, .topicId = 36,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {1, 2, 3};\nstd::cout << v.bak();\n\nProgramcı son elemanı yazdırmak istiyor (fonksiyon adı yanlış yazılmış). Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"std::cout << v.back();"},
        .explanation = "Fonksiyon adı back'tir, bak değil.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 825, .topicId = 36,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vector tanımlayıp ilk ve son elemanını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << v.front() << v.back();", "std::vector<int> v = {1, 2, 3};"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce vector tanımlanır (2), sonra yazdırılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 826, .topicId = 36,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir tam sayı vector'ü tanımlayıp, front(), back() ve size() fonksiyonlarını kullanarak ilk elemanı, son elemanı ve boyutu ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"front", "back", "size", "cout", "<<"},
        .explanation = "Program front(), back() ve size() üye fonksiyonlarını kullanarak sonuçları yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 37: string
    questions.push_back(Question{
        .id = 827, .topicId = 37,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::string hangi kütüphanede tanımlıdır?",
        .options = {"<vector>", "<array>", "<string>", "<iostream>"},
        .acceptedAnswers = {"c"},
        .explanation = "std::string, <string> kütüphanesinde tanımlıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 828, .topicId = 37,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::string ne saklamak için kullanılır?",
        .options = {"Yalnızca sayılar", "Metin (karakter dizisi)", "Yalnızca tek bir karakter", "Boolean değerler"},
        .acceptedAnswers = {"b"},
        .explanation = "std::string metin (karakter dizisi) saklamak için kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 829, .topicId = 37,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::string isim = \"Ali\"; isim.length() kaç döner?",
        .options = {"2", "3", "4", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "'Ali' 3 karakterden oluşur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 830, .topicId = 37,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string, C-style karakter dizisine (char[]) göre ne avantaj sunar?",
        .options = {"Daha az bellek kullanır", "Boyutu otomatik yönetilir ve birçok yararlı üye fonksiyon sunar", "Yalnızca sayısal veri saklar", "Hiçbir avantajı yoktur"},
        .acceptedAnswers = {"b"},
        .explanation = "std::string, boyutu otomatik yöneten ve length(), substr(), find() gibi üye fonksiyonlar sunan güvenli bir sınıftır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 831, .topicId = 37,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string isim = \"Merhaba\"; isim[0] ifadesi ne döner?",
        .options = {"Bir string ('M')", "Bir char ('M')", "Bir int", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "[] operatörü tek bir karakter (char) döndürür, string değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 832, .topicId = 37,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string bos = \"\"; bos.length() kaç döner?",
        .options = {"0", "1", "Hata", "Tanımsız"},
        .acceptedAnswers = {"a"},
        .explanation = "Boş bir string'in uzunluğu 0'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 833, .topicId = 37,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string isim; (boş tanımlanan) bir string'in başlangıç değeri nedir?",
        .options = {"Tanımsız (garbage) değer", "Boş bir string (\"\")", "null", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "std::string, başlangıç değeri verilmeden tanımlansa bile otomatik olarak boş bir string olarak başlatılır (C-style dizilerin aksine).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 834, .topicId = 37,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string a = \"Merhaba\"; std::string b = a; b[0] = 'X'; işleminden sonra a[0] ne olur?",
        .options = {"'X' olur", "'M' olarak kalır", "Boş olur", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "std::string değer semantiğine sahiptir; b, a'nın bağımsız bir kopyasıdır, bu yüzden a etkilenmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 835, .topicId = 37,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::string, metin saklamak için kullanılan bir sınıftır.",
        .acceptedAnswers = {"1"},
        .explanation = "std::string'in temel amacı budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 836, .topicId = 37,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::string ile char[] (C-style karakter dizisi) aynı türdür.",
        .acceptedAnswers = {"2"},
        .explanation = "std::string ve char[] farklı türlerdir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 837, .topicId = 37,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::string kullanmak için <string> kütüphanesi eklenmelidir.",
        .acceptedAnswers = {"1"},
        .explanation = "<string> kütüphanesi eklenmelidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 838, .topicId = 37,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir std::string'e [] ile erişmek bir char döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "[] operatörü tek bir char döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 839, .topicId = 37,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Boş bir std::string tanımlamak (std::string s;) geçerlidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Boş bir string tanımlamak geçerlidir ve otomatik olarak \"\" değerini alır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 840, .topicId = 37,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki std::string birbirinin kopyası olduğunda, birini değiştirmek diğerini de değiştirir.",
        .acceptedAnswers = {"2"},
        .explanation = "std::string değer semantiğine sahiptir; kopyalar birbirinden bağımsızdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 841, .topicId = 37,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::_____ isim = \"Ali\"; ifadesinde boşluğa hangi tür yazılmalı?",
        .acceptedAnswers = {"string"},
        .explanation = "std::string türü kullanılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 842, .topicId = 37,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string isim = \"Merhaba\"; std::cout << isim._____(); ifadesinin karakter sayısını yazdırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"length"},
        .explanation = "length() karakter sayısını döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 843, .topicId = 37,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string s _____ \"Test\"; ifadesinin s'yi 'Test' değeriyle başlatması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"="},
        .explanation = "Atama operatörü = kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 844, .topicId = 37,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string isim = \"Ali\"; char ilkHarf = isim_____; ifadesinin ilk karakteri ('A') alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"[0]"},
        .explanation = "İlk karaktere indeks 0 ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 845, .topicId = 37,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string s1 = \"abc\"; std::string s2 = s1; s2 s1'in bir _____'dur (kopya/referans).",
        .acceptedAnswers = {"kopyası"},
        .explanation = "std::string değer semantiğine sahiptir; s2, s1'in bağımsız bir kopyasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 846, .topicId = 37,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string metin = \"\"; ifadesinin metin.length() değerinin _____ olması beklenir (sayı olarak yazın).",
        .acceptedAnswers = {"0"},
        .explanation = "Boş bir string'in uzunluğu 0'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 847, .topicId = 37,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "#include <string>\n\nint main() {\n    _____\n    std::cout << isim.length();\n}\n'Merhaba' değerinde bir string tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::string isim = \"Merhaba\";"},
        .explanation = "std::string ile bir metin tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 848, .topicId = 37,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::string isim = \"Ali\";\nchar ilkHarf = _____;\nisim'in ilk karakterini alan ifadeyi yazın.",
        .acceptedAnswers = {"isim[0]"},
        .explanation = "İlk karaktere isim[0] ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 849, .topicId = 37,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::string isim = \"Merhaba\";\nstd::cout << isim.length();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"7"},
        .explanation = "'Merhaba' 7 karakterden oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 850, .topicId = 37,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::string isim = \"Ali\";\nstd::cout << isim[0] << isim[2];\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Ai"},
        .explanation = "isim[0]='A', isim[2]='i'; birlikte 'Ai' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 851, .topicId = 37,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::string isim = \"Ali\"\nstd::cout << isim;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::string isim = \"Ali\";"},
        .explanation = "Satırın sonunda noktalı virgül eksik.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 852, .topicId = 37,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::string harf = 'A';\nstd::cout << harf;\n\nProgramcı 'A' metnini bir std::string'e atamak istiyor ama tek tırnak kullanmış (bu bir char, string değil). Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::string harf = \"A\";"},
        .explanation = "std::string bir metin literal'i çift tırnak ile yazılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 853, .topicId = 37,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstring isim = \"Ali\";\nstd::cout << isim;\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"std::string isim = \"Ali\";"},
        .explanation = "std:: öneki eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 854, .topicId = 37,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir string tanımlayıp uzunluğunu yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << isim.length();", "std::string isim = \"Merhaba\";"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce string tanımlanır (2), sonra uzunluğu yazdırılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 855, .topicId = 37,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir isim okuyup, ismin uzunluğunu ekrana yazdıran bir program yazın (std::string ve length() kullanarak).",
        .acceptedAnswers = {"cin", ">>", "string", "length", "cout", "<<"},
        .explanation = "Program bir isim okumalı ve length() ile uzunluğunu yazdırmalıdır.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `90/90 test(s) passed.` (unchanged — no existing test yet counts
these topics' questions).

- [ ] **Step 3: Commit**

```bash
git add src/QuestionsSection4.cpp
git commit -m "feat(content): add questions for topics 35-37 (ids 769-855)"
```

---

### Task 4: Questions for topics 38-40 (ids 856-942), test updates, and final integration

**Files:**
- Modify: `src/QuestionsSection4.cpp` (append the final
  `questions.push_back(...)` calls, right before the function's closing
  `}`)
- Modify: `tests/QuestionManagerTests.cpp` (add a per-topic minimum-count
  test for topics 31-40)
- Modify: `docs/superpowers/roadmap.md` (mark Phase 15 complete)

**Interfaces:**
- Consumes: `appendSection4Questions`'s body from Tasks 2-3 (ends after
  topic 37's WriteCode question, id 855).
- Produces: the complete, final `appendSection4Questions` function
  (ids 653-942, 290 questions across topics 31-40).

- [ ] **Step 1: Append topics 38-40's questions**

In `src/QuestionsSection4.cpp`, insert the following right before the
function's closing `}` (i.e. immediately after the `id = 855` WriteCode
question added in Task 3):

```cpp
    // Topic 38: String birleştirme
    questions.push_back(Question{
        .id = 856, .topicId = 38,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki std::string'i birleştirmek (concatenation) için hangi operatör kullanılır?",
        .options = {"*", "+", "%", "&"},
        .acceptedAnswers = {"b"},
        .explanation = "+ operatörü iki string'i birleştirir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 857, .topicId = 38,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::string a = \"Ali\"; std::string b = \"Veli\"; std::string c = a + b; c ne olur?",
        .options = {"AliVeli", "Ali Veli", "Veli Ali", "Hata"},
        .acceptedAnswers = {"a"},
        .explanation = "a + b, aralarında boşluk olmadan doğrudan birleştirir: 'AliVeli'.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 858, .topicId = 38,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::string a = \"Ali\"; a += \" Veli\"; a ne olur?",
        .options = {"Ali", "Veli", "Ali Veli", "AliVeli"},
        .acceptedAnswers = {"c"},
        .explanation = "a'nın sonuna ' Veli' eklenir: 'Ali Veli'.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 859, .topicId = 38,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "\"Merhaba\" + \"Dünya\" (iki string literal, hiçbiri std::string değişkeni değil) ifadesi geçerli midir?",
        .options = {"Evet, geçerlidir ve birleştirir", "Hayır, en az birinin std::string olması gerekir", "Yalnızca ikisi de tek karakterse geçerlidir", "Her zaman derleme hatası verir, hiçbir şekilde birleştirilemez"},
        .acceptedAnswers = {"b"},
        .explanation = "İki C-string literali doğrudan + ile birleştirilemez; en az birinin std::string olması gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 860, .topicId = 38,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string a = \"Merhaba\"; std::string b = a + \"!\"; b ne olur?",
        .options = {"Merhaba!", "Merhaba", "!Merhaba", "Hata"},
        .acceptedAnswers = {"a"},
        .explanation = "a'nın sonuna '!' eklenir: 'Merhaba!'.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 861, .topicId = 38,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "+= operatörü bir string'e ne ekleyebilir?",
        .options = {"Yalnızca başka bir string", "Yalnızca tek bir karakter", "Hem başka bir string hem de tek bir karakter", "Hiçbir şey ekleyemez"},
        .acceptedAnswers = {"c"},
        .explanation = "+= operatörü hem başka bir string'i hem de tek bir karakteri ekleyebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 862, .topicId = 38,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string a = \"Test\"; a = a + a; a ne olur?",
        .options = {"Test", "TestTest", "Test2", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "a kendisiyle birleştirilir: 'TestTest'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 863, .topicId = 38,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string ad = \"Ali\"; std::string soyad = \"Veli\"; std::string tam = ad + \" \" + soyad; tam ne olur?",
        .options = {"AliVeli", "Ali Veli", "Ali  Veli", "Veli Ali"},
        .acceptedAnswers = {"b"},
        .explanation = "ad, bir boşluk ve soyad art arda birleştirilir: 'Ali Veli'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 864, .topicId = 38,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki std::string, + operatörü ile birleştirilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "+ operatörü string birleştirme için kullanılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 865, .topicId = 38,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki C-string literal (\"a\" + \"b\") doğrudan + ile birleştirilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "En az birinin std::string olması gerekir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 866, .topicId = 38,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "+= operatörü, bir string'in sonuna başka bir string veya karakter ekler.",
        .acceptedAnswers = {"1"},
        .explanation = "+='in işlevi budur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 867, .topicId = 38,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "String birleştirme sonucunda orijinal string'lerden biri değişir, ikisi de kalıcı olarak birleşir.",
        .acceptedAnswers = {"2"},
        .explanation = "a + b yeni bir string döndürür; a ve b değişmez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 868, .topicId = 38,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::string a = \"X\"; std::string b = \"Y\"; std::string c = a + b; işleminden sonra a hala \"X\"'tir.",
        .acceptedAnswers = {"1"},
        .explanation = "+ operatörü yeni bir string oluşturur; a değişmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 869, .topicId = 38,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "String birleştirme yaparken araya boşluk otomatik olarak eklenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Boşluk otomatik eklenmez; gerekiyorsa elle (\" \") eklenmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 870, .topicId = 38,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string a = \"Ali\"; std::string b = \"Veli\"; std::string c = a _____ b; ifadesinin c'yi 'AliVeli' yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"+"},
        .explanation = "+ operatörü iki string'i birleştirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 871, .topicId = 38,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string a = \"Merhaba\"; a _____ \"!\"; ifadesinin a'yı 'Merhaba!' yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"+="},
        .explanation = "+= operatörü sona ekleme yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 872, .topicId = 38,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string ad = \"Ali\"; std::string soyad = \"Veli\"; std::string tam = ad + _____ + soyad; ifadesinin araya boşluk koyması için boşluğa (tırnakla) ne yazılmalı?",
        .acceptedAnswers = {"\" \""},
        .explanation = "Aralarına boşluk koymak için \" \" eklenmelidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 873, .topicId = 38,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string a = \"Test\"; std::string b = a _____ a; ifadesinin b'yi 'TestTest' yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"+"},
        .explanation = "+ operatörü a'yı kendisiyle birleştirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 874, .topicId = 38,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string mesaj = \"Merhaba\"; mesaj _____ \" Dünya\"; ifadesinin mesaj'ı 'Merhaba Dünya' yapması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"+="},
        .explanation = "+= operatörü sona ekleme yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 875, .topicId = 38,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string a = \"abc\"; std::string b = \"def\"; std::string c = a + b; c'nin uzunluğu _____ olur (sayı olarak yazın).",
        .acceptedAnswers = {"6"},
        .explanation = "3 + 3 = 6 karakter.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 876, .topicId = 38,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::string ad = \"Ali\";\nstd::string soyad = \"Veli\";\nstd::string tamAd = _____;\nad ve soyad'ı aralarında boşlukla birleştiren ifadeyi yazın.",
        .acceptedAnswers = {"ad + \" \" + soyad"},
        .explanation = "ad, boşluk ve soyad art arda birleştirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 877, .topicId = 38,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::string mesaj = \"Merhaba\";\n_____\nstd::cout << mesaj;\nmesaj'ın sonuna \"!\" ekleyen satırı yazın.",
        .acceptedAnswers = {"mesaj += \"!\";"},
        .explanation = "+= ile sona ekleme yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 878, .topicId = 38,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::string a = \"Ali\";\nstd::string b = \"Veli\";\nstd::cout << a + b;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"AliVeli"},
        .explanation = "a ve b aralarında boşluk olmadan birleştirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 879, .topicId = 38,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::string mesaj = \"Merhaba\";\nmesaj += \" \";\nmesaj += \"Dünya\";\nstd::cout << mesaj;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Merhaba Dünya"},
        .explanation = "Sırayla boşluk ve 'Dünya' eklenir: 'Merhaba Dünya'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 880, .topicId = 38,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::string a = \"Ali\";\nstd::string b = \"Veli\";\nstd::string c = a - b;\n\nProgramcı iki string'i birleştirmek istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::string c = a + b;"},
        .explanation = "String birleştirme için - değil + operatörü kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 881, .topicId = 38,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::string tam = \"Ali\" + \"Veli\";\n\nBu satır derlenmez çünkü iki C-string literali doğrudan + ile birleştirilemez. Hatalı satırı, en az birini std::string yaparak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::string tam = std::string(\"Ali\") + \"Veli\";"},
        .explanation = "En az bir işlenenin std::string olması gerekir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 882, .topicId = 38,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::string a = \"Merhaba\";\na =+ \"!\";\n\nProgramcı a'nın sonuna \"!\" eklemek istiyor. Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"a += \"!\";"},
        .explanation = "=+ yerine += kullanılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 883, .topicId = 38,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, iki string'i birleştirip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << c;", "std::string c = a + b;", "std::string a = \"Ali\", b = \"Veli\";"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce string'ler tanımlanır (3), sonra birleştirilir (2), en son yazdırılır (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 884, .topicId = 38,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan ad ve soyad okuyup, ikisini aralarında boşlukla birleştirip ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "string", "+", "cout", "<<"},
        .explanation = "Program ad ve soyad'ı okumalı, + operatörüyle boşlukla birleştirmeli ve yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 39: length() ve empty()
    questions.push_back(Question{
        .id = 885, .topicId = 39,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "length() ne döndürür?",
        .options = {"String'in ilk karakterini", "String'in karakter sayısını", "String'in boş olup olmadığını", "Rastgele bir değer"},
        .acceptedAnswers = {"b"},
        .explanation = "length(), string'in karakter sayısını döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 886, .topicId = 39,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "empty() ne döndürür?",
        .options = {"String'in uzunluğunu", "String'in boş olup olmadığını gösteren bir bool", "İlk karakteri", "Son karakteri"},
        .acceptedAnswers = {"b"},
        .explanation = "empty(), string'in boş olup olmadığını gösteren bir bool döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 887, .topicId = 39,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::string s = \"Merhaba\"; s.length() kaç döner?",
        .options = {"6", "7", "8", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "'Merhaba' 7 karakterden oluşur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 888, .topicId = 39,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"\"; s.empty() ne döner?",
        .options = {"true", "false", "0", "Hata"},
        .acceptedAnswers = {"a"},
        .explanation = "s boş olduğu için empty() true döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 889, .topicId = 39,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Test\"; s.empty() ne döner?",
        .options = {"true", "false", "4", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "s boş olmadığı için empty() false döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 890, .topicId = 39,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "length() ile size() arasındaki fark nedir?",
        .options = {"length() daha hızlıdır", "İkisi de aynı değeri döndürür, eş anlamlıdırlar", "size() yalnızca vector'de çalışır", "length() yalnızca boş string'lerde çalışır"},
        .acceptedAnswers = {"b"},
        .explanation = "std::string için length() ve size() tamamen eş anlamlıdır, aynı değeri döndürürler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 891, .topicId = 39,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string s = \" \"; (yalnızca bir boşluk karakteri) s.empty() ne döner?",
        .options = {"true, çünkü görsel olarak boş görünüyor", "false, çünkü uzunluğu 0 değil 1'dir", "Derleme hatası verir", "Tanımsız davranış"},
        .acceptedAnswers = {"b"},
        .explanation = "empty() yalnızca uzunluğun tam olarak 0 olup olmadığına bakar; tek bir boşluk karakteri uzunluğu 1 yapar, bu yüzden false döner.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 892, .topicId = 39,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "s.empty() kontrolü ile s.length() == 0 kontrolü arasındaki fark nedir?",
        .options = {"Farklı sonuçlar verirler", "Aynı sonucu verirler, empty() sadece daha okunaklıdır", "length() == 0 her zaman hatalıdır", "empty() yalnızca sayılarla çalışır"},
        .acceptedAnswers = {"b"},
        .explanation = "İkisi de aynı koşulu kontrol eder; empty() yalnızca daha okunaklı bir alternatiftir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 893, .topicId = 39,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "length(), bir string'in karakter sayısını döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "length()'in işlevi budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 894, .topicId = 39,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "empty(), bir string'in karakter sayısını döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "empty() bir bool döndürür, karakter sayısını değil.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 895, .topicId = 39,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "empty(), bir string'in boş olup olmadığını (bool) kontrol eder.",
        .acceptedAnswers = {"1"},
        .explanation = "empty()'in işlevi budur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 896, .topicId = 39,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "length() ve size(), bir std::string için farklı sonuçlar döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "İkisi de aynı değeri döndürür, eş anlamlıdırlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 897, .topicId = 39,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Yalnızca boşluk karakterlerinden oluşan bir string (\" \" gibi) empty() için true döner.",
        .acceptedAnswers = {"2"},
        .explanation = "empty() yalnızca uzunluğun 0 olup olmadığına bakar; boşluklu bir string uzunluğu 0 değildir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 898, .topicId = 39,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "s.empty() ile s.length() == 0 aynı sonucu verir.",
        .acceptedAnswers = {"1"},
        .explanation = "İkisi de aynı koşulu farklı şekillerde ifade eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 899, .topicId = 39,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string s = \"Merhaba\"; std::cout << s._____(); ifadesinin karakter sayısını yazdırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"length"},
        .explanation = "length() karakter sayısını döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 900, .topicId = 39,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string s = \"\"; std::cout << s._____(); ifadesinin boş olup olmadığını (true) yazdırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"empty"},
        .explanation = "empty() boş olup olmadığını kontrol eder.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 901, .topicId = 39,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string s = \"abc\"; std::cout << s.length() _____ s.size(); ifadesinin iki fonksiyonun aynı değeri döndürdüğünü göstermesi için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "== operatörüyle iki değerin eşitliği kontrol edilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 902, .topicId = 39,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string s; if (s._____()) { std::cout << \"Boş\"; } ifadesinin s boşsa 'Boş' yazdırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"empty"},
        .explanation = "empty() true dönerse if bloğu çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 903, .topicId = 39,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Test\"; if (s.length() _____ 0) { std::cout << \"Boş değil\"; } ifadesinin s boş değilken çalışması için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {">"},
        .explanation = "Uzunluk 0'dan büyükse string boş değildir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 904, .topicId = 39,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\"; int uzunluk = s.length(); uzunluk değişkeninin değeri _____ olur (sayı olarak yazın).",
        .acceptedAnswers = {"7"},
        .explanation = "'Merhaba' 7 karakterden oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 905, .topicId = 39,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Test\";\nint uzunluk = _____;\nlength() kullanarak uzunluğu alan ifadeyi yazın.",
        .acceptedAnswers = {"s.length()"},
        .explanation = "length() karakter sayısını döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 906, .topicId = 39,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"\";\nif (_____) {\n    std::cout << \"Boş bir string\";\n}\ns'nin boş olup olmadığını kontrol eden if koşulunu yazın.",
        .acceptedAnswers = {"s.empty()"},
        .explanation = "empty() boşluk kontrolü yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 907, .topicId = 39,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba Dunya\";\nstd::cout << s.length();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"13"},
        .explanation = "'Merhaba' (7) + boşluk (1) + 'Dunya' (5) = 13 bayt/karakter (tamamı ASCII harfler olduğu için bayt sayısı karakter sayısıyla aynıdır).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 908, .topicId = 39,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::string s = \"\";\nstd::cout << s.empty() << s.length();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "empty()=true(1), length()=0; birlikte '10' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 909, .topicId = 39,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::string s = \"Test\";\nstd::cout << s.lenght();\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << s.length();"},
        .explanation = "Fonksiyon adı length'tir, lenght değil (yazım hatası).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 910, .topicId = 39,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::string s = \"\";\nif (s.empty) {\n    std::cout << \"Boş\";\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (s.empty()) {"},
        .explanation = "empty bir üye fonksiyon çağrısıdır ve parantez gerektirir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 911, .topicId = 39,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::string s = \"Test\";\nstd::cout << s.length;\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"std::cout << s.length();"},
        .explanation = "length bir üye fonksiyon çağrısıdır ve parantez gerektirir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 912, .topicId = 39,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir string tanımlayıp uzunluğunu yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << s.length();", "std::string s = \"Merhaba\";"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce string tanımlanır (2), sonra uzunluğu yazdırılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 913, .topicId = 39,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir metin okuyup, metnin boş olup olmadığını (empty() ile) ve uzunluğunu (length() ile) ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "empty", "length", "cout", "<<"},
        .explanation = "Program metni okumalı, empty() ve length() ile sonuçları yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 40: substr() ve find()
    questions.push_back(Question{
        .id = 914, .topicId = 40,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "substr(baslangic, uzunluk) fonksiyonu ne yapar?",
        .options = {"String'i tersine çevirir", "Belirtilen konumdan başlayarak belirtilen uzunlukta bir alt dizi döndürür", "String'in uzunluğunu değiştirir", "İki string'i birleştirir"},
        .acceptedAnswers = {"b"},
        .explanation = "substr(), belirtilen konumdan başlayarak belirtilen uzunlukta bir alt dizi döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 915, .topicId = 40,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "find(aranan) fonksiyonu ne yapar?",
        .options = {"Aranan alt diziyi bulur ve konumunu (bulunamazsa npos) döndürür", "String'i sıralar", "Aranan karakteri siler", "Yalnızca ilk karakteri kontrol eder"},
        .acceptedAnswers = {"a"},
        .explanation = "find(), aranan alt diziyi bulur ve başlangıç konumunu döndürür; bulamazsa std::string::npos döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 916, .topicId = 40,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::string s = \"Merhaba\"; s.substr(0, 3) ne döner?",
        .options = {"Mer", "erh", "aba", "Merhaba"},
        .acceptedAnswers = {"a"},
        .explanation = "İndeks 0'dan başlayarak 3 karakter alınır: 'Mer'.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 917, .topicId = 40,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\"; s.substr(2, 3) ne döner?",
        .options = {"rha", "erh", "hab", "Mer"},
        .acceptedAnswers = {"a"},
        .explanation = "İndeks 2'den (r) başlayarak 3 karakter alınır: 'rha'.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 918, .topicId = 40,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\"; s.find(\"hab\") kaç döner (bulunduğu başlangıç indeksini yazın)?",
        .options = {"2", "3", "4", "Bulunamaz (npos)"},
        .acceptedAnswers = {"b"},
        .explanation = "'Merhaba' string'inde 'hab' alt dizisi indeks 3'te ('h' harfinde) başlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 919, .topicId = 40,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\"; s.find(\"xyz\") (bulunamayan bir alt dizi) ne döner?",
        .options = {"-1", "0", "std::string::npos", "Hata verir, programı durdurur"},
        .acceptedAnswers = {"c"},
        .explanation = "find(), bulamadığında std::string::npos özel sabitini döndürür, -1 değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 920, .topicId = 40,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "substr()'ün ikinci parametresi neyi belirtir?",
        .options = {"Bitiş indeksini", "Alınacak karakter sayısını (uzunluğu)", "Adım büyüklüğünü", "Karakterin ASCII değerini"},
        .acceptedAnswers = {"b"},
        .explanation = "İkinci parametre, alınacak karakter sayısını (uzunluğu) belirtir, bitiş indeksini değil.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 921, .topicId = 40,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string s = \"Merhaba\"; if (s.find(\"a\") != std::string::npos) { ... } ifadesi neyi kontrol eder?",
        .options = {"s'nin 'a' ile başlayıp başlamadığını", "s'nin içinde 'a' karakterinin bulunup bulunmadığını", "s'nin uzunluğunun 'a' harfi kadar olup olmadığını", "Hiçbir şeyi kontrol etmez, her zaman true'dur"},
        .acceptedAnswers = {"b"},
        .explanation = "find() != npos, aranan karakterin/alt dizinin string içinde herhangi bir yerde bulunup bulunmadığını kontrol eder.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 922, .topicId = 40,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "substr(), bir string'in belirli bir bölümünü (alt dizisini) döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "substr()'ün işlevi budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 923, .topicId = 40,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "find(), aranan alt diziyi bulamazsa -1 döner.",
        .acceptedAnswers = {"2"},
        .explanation = "find(), bulamadığında std::string::npos döner, -1 değil.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 924, .topicId = 40,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "substr()'ün ikinci parametresi, alınacak karakter sayısını (uzunluğu) belirtir, bitiş indeksini değil.",
        .acceptedAnswers = {"1"},
        .explanation = "İkinci parametre uzunluktur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 925, .topicId = 40,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "find(), aranan alt diziyi bulamazsa std::string::npos döner.",
        .acceptedAnswers = {"1"},
        .explanation = "npos, 'bulunamadı' durumunu temsil eden özel bir sabittir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 926, .topicId = 40,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "substr() çağrısı, orijinal string'i değiştirir.",
        .acceptedAnswers = {"2"},
        .explanation = "substr(), yeni bir string döndürür; orijinali değiştirmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 927, .topicId = 40,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "find() sonucunu -1 ile karşılaştırmak, npos ile karşılaştırmakla her zaman aynı doğru sonucu verir.",
        .acceptedAnswers = {"2"},
        .explanation = "find()'ın dönüş türü işaretsizdir (unsigned); == -1 karşılaştırması güvenilir değildir, std::string::npos kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 928, .topicId = 40,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string s = \"Merhaba\"; std::string parca = s._____(0, 3); ifadesinin 'Mer' alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"substr"},
        .explanation = "substr() bir alt dizi döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 929, .topicId = 40,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string s = \"Merhaba\"; if (s._____(\"hab\") != std::string::npos) { ... } ifadesinin 'hab' alt dizisini araması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"find"},
        .explanation = "find() bir alt diziyi arar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 930, .topicId = 40,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string s = \"Merhaba\"; s.find(\"xyz\") bulunamadığında std::string::_____ döner. Boşluğa ne yazılmalı?",
        .acceptedAnswers = {"npos"},
        .explanation = "std::string::npos, bulunamadı durumunu temsil eder.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 931, .topicId = 40,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\"; std::string parca = s.substr(2, _____); ifadesinin 'rha' (3 karakter) alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"3"},
        .explanation = "İkinci parametre alınacak karakter sayısıdır: 3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 932, .topicId = 40,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\"; std::string parca = s.substr(_____, 4); ifadesinin 'haba' (indeks 3'ten başlayan 4 karakter) alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"3"},
        .explanation = "'haba' indeks 3'te ('h') başlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 933, .topicId = 40,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\"; int konum = s._____(\"e\"); konum değişkeninin 'e' harfinin bulunduğu indeksi (1) alması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"find"},
        .explanation = "find() aranan karakterin/alt dizinin indeksini döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 934, .topicId = 40,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\";\nstd::string ilkUc = _____;\nİlk 3 karakteri alan ifadeyi yazın.",
        .acceptedAnswers = {"s.substr(0, 3)"},
        .explanation = "substr(0, 3), indeks 0'dan başlayarak 3 karakter alır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 935, .topicId = 40,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\";\nbool bulunduMu = _____;\n's' içinde 'hab' aranıp bulunup bulunmadığını (npos ile karşılaştırarak) kontrol eden ifadeyi yazın.",
        .acceptedAnswers = {"s.find(\"hab\") != std::string::npos"},
        .explanation = "find() != npos, alt dizinin bulunup bulunmadığını kontrol eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 936, .topicId = 40,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"Merhaba\";\nstd::cout << s.substr(0, 3);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Mer"},
        .explanation = "İndeks 0'dan 3 karakter alınır: 'Mer'.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 937, .topicId = 40,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::string s = \"Merhaba\";\nstd::cout << s.find(\"hab\");\nYukarıdaki kodun ekran çıktısı nedir? (sayı olarak yazın)",
        .acceptedAnswers = {"3"},
        .explanation = "'Merhaba' içinde 'hab' alt dizisi indeks 3'te başlar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 938, .topicId = 40,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::string s = \"Merhaba\";\nstd::cout << s.substr(0 3);\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << s.substr(0, 3);"},
        .explanation = "Parametreler arasında virgül eksik.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 939, .topicId = 40,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::string s = \"Merhaba\";\nif (s.find(\"xyz\") == -1) {\n    std::cout << \"Bulunamadı\";\n}\n\nBu kod her zaman 'Bulunamadı' yazdırmalı gibi görünse de, find()'ın dönüş türü işaretsiz (unsigned) olduğu ve bulunamama durumunda -1 değil std::string::npos döndüğü için == -1 karşılaştırması güvenilir değildir. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (s.find(\"xyz\") == std::string::npos) {"},
        .explanation = "Bulunamama durumu std::string::npos ile karşılaştırılmalıdır, -1 ile değil.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 940, .topicId = 40,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::string s = \"Merhaba\";\nstd::string parca = s.substr(2. 3);\n\nProgramcı virgül yerine nokta yazmış. Düzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"std::string parca = s.substr(2, 3);"},
        .explanation = "Parametreler arasında virgül kullanılmalıdır, nokta değil.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 941, .topicId = 40,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir string tanımlayıp ilk 3 karakterini yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << s.substr(0, 3);", "std::string s = \"Merhaba\";"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce string tanımlanır (2), sonra alt dizisi yazdırılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 942, .topicId = 40,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir metin okuyup, metnin ilk 3 karakterini (substr kullanarak) ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "substr", "cout", "<<"},
        .explanation = "Program metni okumalı ve substr(0, 3) ile ilk 3 karakteri yazdırmalıdır.",
        .baseXp = 40,
    });
}
```

- [ ] **Step 2: Add a per-topic minimum-count test**

In `tests/QuestionManagerTests.cpp`, add this new test case right after
`QuestionManager_EveryTopicTwentyOneToThirtyHasAtLeastTwentyNineQuestions`
(do not modify that existing test, and do not touch
`QuestionManager_NoDuplicateQuestionIds`, which already scans topics
1-100):

```cpp
TEST_CASE(QuestionManager_EveryTopicThirtyOneToFortyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 31; topicId <= 40; ++topicId) {
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
Expected: `91/91 test(s) passed.` (90 from Phase 14's end state + 1 new
test).

Run from `build/`: `ctest -C Debug --output-on-failure`
Expected: 100% pass.

- [ ] **Step 4: Manual verification — topic 34 end-to-end**

Run the app (`./build/Debug/CppMasterConsole.exe`), navigate to the
topic browser, choose Section 4, choose topic 34 ("vector"):

1. Confirm the lesson text prints (matches the `explanation`/`syntax`/
   `exampleCode` written in Task 1) — proving `openTopic`'s content gate
   passes for topic 34 with zero `Application.cpp` changes.
2. Confirm "Konu testi başlıyor (29 soru)." prints.
3. Answer a few questions (any answers), then use `cikis` to return to
   the main menu.
4. Confirm the app returns to the main menu without crashing, and that
   partial XP is awarded.
5. Clean up: `rm -f data/*.txt`.

- [ ] **Step 5: Commit the question content and test changes**

```bash
git add src/QuestionsSection4.cpp tests/QuestionManagerTests.cpp
git commit -m "feat(content): add questions for topics 38-40 (ids 856-942), widen coverage tests"
```

- [ ] **Step 6: Update the roadmap**

In `docs/superpowers/roadmap.md`, add a new bullet for Phase 15 under
"Phase order," immediately after the Phase 14 entry, following the
EXACT format Phases 8-14 use
(`**Phase N — name: COMPLETE** (commits \`X..Y\`, ...)`), with the
commit range starting at this phase's PLAN commit (the commit for "Add
implementation plan for Bölüm 4 İçerik Genişletmesi") and ending at this
task's final content commit (from Step 5 above). Update the "Status"
section to say Phase 15 is complete and Phase 16 (Section 5 content:
"Fonksiyonlar") starts next.

Then commit:

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 15 complete in roadmap"
```


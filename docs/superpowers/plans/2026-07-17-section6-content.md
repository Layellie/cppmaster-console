# Bölüm 6 İçerik Genişletmesi (Phase 17) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add full lesson content and a 290-question bank for Section 6
(topics 51-60, "Lambda, pointer ve bellek"), following the identical
architecture used in Phases 13-16.

**Architecture:** One new `applySection6LessonContent` function in
`src/LessonContentSection6.cpp`, one new `appendSection6Questions`
function in `src/QuestionsSection6.cpp`, both wired into the existing
`LessonManager`/`QuestionManager` constructors after the Phase 16 calls.

**Tech Stack:** C++20, CMake, the project's own minimal test framework
(`TEST_CASE`/`CHECK`).

## Global Constraints

- Ids for this phase's questions: 1233-1522 (10 topics x 29 questions
  each), continuing directly from Phase 16's last id (1232).
- Fixed per-topic type/difficulty/baseXp distribution (IDENTICAL for
  every topic in this phase): 8 MultipleChoice (VeryEasy, Easy, Easy,
  Medium, Medium, Medium, Hard, Hard -> baseXp 5, 10, 10, 20, 20, 20,
  30, 30), 6 TrueFalse (VeryEasy, VeryEasy, Easy, Easy, Medium, Medium
  -> baseXp 5, 5, 10, 10, 20, 20), 6 FillBlank (VeryEasy, Easy, Easy,
  Medium, Medium, Medium -> baseXp 10, 10, 10, 20, 20, 20), 2
  CompleteLine (Medium, Medium -> baseXp 20, 20), 2 PredictOutput
  (Medium, Hard -> baseXp 20, 30), 2 FindError (Medium, Hard -> baseXp
  20, 30), 1 FixCode (Hard -> baseXp 30), 1 OrderCode (Medium -> baseXp
  20), 1 WriteCode (Hard -> baseXp 40). Total 29 per topic.
- `MultipleChoice.acceptedAnswers` is a single lowercase letter (a/b/c/d)
  matching the 0-indexed `options` position. `TrueFalse` has no
  `options` field; `{"1"}` = true, `{"2"}` = false. `OrderCode.acceptedAnswers`
  is 1-indexed positions space-separated, and MUST be verified (by
  actually assembling and compiling the resulting program, not just
  checking it's a permutation) to produce the correct, intended runtime
  behavior — Phase 16's Task 3 had exactly one OrderCode question whose
  accepted answer was a syntactically valid permutation that still
  produced wrong output, caught only by compiling it.
- **No pointer/memory question may require an exact numeric memory
  address as its graded answer** — addresses are non-deterministic
  across runs/platforms and cannot be graded. Any lesson/question
  content showing `&x` being printed must not ask the student to state
  the printed value.
- **Undefined-behavior claims must never be phrased as an unconditional
  guarantee** (e.g. "always crashes") — use "genellikle çöker" / "erişim
  ihlaline yol açar" (usually crashes / causes an access violation), per
  this project's established discipline (already fixed once in Phase 15
  for `pop_back()` on an empty container).
- **Memory leaks must never be described as causing a crash or incorrect
  program output** — a leak just means memory is never reclaimed; the
  program keeps running normally otherwise.
- `int* p, q;` declares `p` as `int*` and `q` as a plain `int` — the `*`
  binds to the declarator, not the type. Any content touching multi-
  variable pointer declarations must get this exactly right.
- `delete`/`delete[]` must match `new`/`new[]`; mismatching them, or
  double-`delete`-ing the same pointer, is undefined behavior (phrased
  per the UB-claim rule above, not as a guaranteed crash).
- Pointer arithmetic (`ptr + 1`, `++ptr`) advances by `sizeof(element
  type)`, not by 1 byte.
- A reference variable must be initialized at declaration, can never be
  rebound afterward, can never be null, and does not support pointer
  arithmetic — contrast this explicitly against topics 52-59's pointer
  coverage (topic 60 is this section's closing synthesis topic, not a
  repeat of Phase 16's reference-*parameter* content).
- Lambda captures: `[x]` (by value) gives the lambda body a `const`
  copy of `x` unless the lambda is marked `mutable`, in which case
  modifying the lambda's internal copy still never affects the
  original `x` outside. `[&x]` (by reference) lets the lambda modify
  the original `x` directly, exactly like a reference parameter.
- No `Application.cpp` changes are needed — `openTopic`/`runTopicQuiz`
  already activate any topic generically once it has non-empty lesson
  content and >= 1 question.

---

### Task 1: Section 6 lesson content

**Files:**
- Modify: `src/LessonContent.h` (add one new declaration)
- Create: `src/LessonContentSection6.cpp`
- Modify: `src/LessonManager.cpp` (include already present; add one call)
- Modify: `CMakeLists.txt` (add the new `.cpp` to both the lib and test
  target sources, matching how `LessonContentSection5.cpp` is
  registered)
- Modify: `tests/LessonManagerTests.cpp` (widen two existing tests)

**Interfaces:**
- Produces: `void applySection6LessonContent(std::vector<Lesson>& lessons);`
  writing into `lessons[50]` through `lessons[59]` (topics 51-60).

- [ ] **Step 1: Add the new declaration**

In `src/LessonContent.h`, add this line after the existing
`applySection5LessonContent` declaration (do not remove that one):

```cpp
void applySection6LessonContent(std::vector<Lesson>& lessons);
```

- [ ] **Step 2: Write the lesson content**

Create `src/LessonContentSection6.cpp` with exactly this content:

```cpp
#include "LessonContent.h"

#include "Lesson.h"

void applySection6LessonContent(std::vector<Lesson>& lessons) {
    // Index 50 = topic id 51 (Lambda fonksiyonları), index 59 = topic
    // id 60 (Referans değişkeni) — same positional convention as
    // applyIntroLessonContent/applySection2-5LessonContent.

    lessons[50].explanation =
        "Lambda ifadeleri, isimsiz (anonim) fonksiyonlar tanımlamanın "
        "kısa bir yoludur. Genel biçimi [yakalama](parametreler) { "
        "govde } şeklindedir. Köşeli parantez içindeki yakalama listesi "
        "(capture list), lambda'nın dışındaki hangi değişkenlere ve "
        "nasıl (değer veya referans ile) erişebileceğini belirler.";
    lessons[50].syntax = "[yakalama](parametreler) { govde }";
    lessons[50].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    auto topla = [](int a, int b) {\n"
        "        return a + b;\n"
        "    };\n"
        "    std::cout << topla(3, 4);\n"
        "    return 0;\n"
        "}";
    lessons[50].lineExplanations = {
        "auto topla = [](int a, int b) { ... }; : topla değişkenine, iki "
        "int alıp toplamını döndüren bir lambda atanır.",
        "topla(3, 4) : lambda, normal bir fonksiyon gibi çağrılır (7 "
        "döner)."};
    lessons[50].commonMistakes = {
        "Boş yakalama listesi [] kullanıldığında lambda, dışındaki "
        "hiçbir değişkene erişemez; dış bir değişkene erişmek için [x] "
        "(değer ile yakalama) veya [&x] (referans ile yakalama) "
        "kullanılmalıdır.",
        "[x] ile yakalanan bir değişken, lambda gövdesi içinde "
        "varsayılan olarak sabittir (const); değiştirmek için "
        "lambda'nın mutable olarak işaretlenmesi gerekir, ve bu durumda "
        "bile yalnızca lambda'nın kendi iç kopyası değişir, dışarıdaki "
        "orijinal değişken asla etkilenmez.",
    };

    lessons[51].explanation =
        "Bir pointer (gösterici), başka bir değişkenin bellek adresini "
        "tutan özel bir değişkendir. tür* isim; şeklinde tanımlanır. "
        "Örneğin int* p; ifadesi, p'nin bir int değişkeninin adresini "
        "tutacağını belirtir. Tanımlandığında ilklendirilmezse (bir "
        "adres atanmazsa), p belirsiz (garbage) bir değer taşır ve bu "
        "haliyle dereference edilmesi tanımsız davranışa (undefined "
        "behavior) yol açar.";
    lessons[51].syntax = "tür* isim;";
    lessons[51].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int sayi = 42;\n"
        "    int* p = &sayi;\n"
        "    std::cout << *p;\n"
        "    return 0;\n"
        "}";
    lessons[51].lineExplanations = {
        "int* p = &sayi; : p, sayi değişkeninin adresini tutan bir "
        "pointer olarak tanımlanır.",
        "std::cout << *p; : *p, p'nin gösterdiği adresteki değeri (42) "
        "verir."};
    lessons[51].commonMistakes = {
        "int* p, q; ifadesinde sadece p bir pointer olur, q sıradan bir "
        "int olarak tanımlanır (yıldız işareti türe değil değişken "
        "adına bağlanır); iki pointer tanımlamak için int* p, *q; "
        "yazılmalıdır.",
    };

    lessons[52].explanation =
        "& operatörü, bir değişkenin bellekteki adresini verir. &x "
        "ifadesi \"x'in adresi\" anlamına gelir ve bir pointer değeri "
        "üretir. Bu, pointer'ları ilklendirmenin en yaygın yoludur.";
    lessons[52].syntax = "&degisken";
    lessons[52].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int x = 10;\n"
        "    int* p = &x;\n"
        "    std::cout << (p == &x);\n"
        "    return 0;\n"
        "}";
    lessons[52].lineExplanations = {
        "int* p = &x; : p, x'in adresiyle ilklendirilir.",
        "std::cout << (p == &x); : p ile &x aynı adresi tuttuğundan "
        "karşılaştırma true (1) verir."};
    lessons[52].commonMistakes = {
        "& sembolünün iki farklı kullanımı vardır: bir ifadede (&x) "
        "adres operatörüdür, ama bir tanımda (int& r = x;) referans "
        "bildirimidir — bağlama göre anlamı değişir.",
        "Bir adresin gerçek sayısal değeri her çalıştırmada farklı "
        "olabileceğinden, adresler programın davranışını test etmek "
        "için kullanılmaz, sadece pointer'ları ilklendirmek için "
        "kullanılır.",
    };

    lessons[53].explanation =
        "* operatörü bir pointer'ın önüne konduğunda, o pointer'ın "
        "gösterdiği adresteki değere erişmeyi sağlar (dereference). *p "
        "ifadesi \"p'nin gösterdiği değer\" anlamına gelir. p, geçerli "
        "bir adresi gösteriyorsa *(&x) her zaman x'in kendisine eşittir.";
    lessons[53].syntax = "*pointer";
    lessons[53].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int x = 5;\n"
        "    int* p = &x;\n"
        "    *p = 10;\n"
        "    std::cout << x;\n"
        "    return 0;\n"
        "}";
    lessons[53].lineExplanations = {
        "int* p = &x; : p, x'in adresini tutar.",
        "*p = 10; : p'nin gösterdiği adresteki değer (yani x) 10 yapılır.",
        "std::cout << x; : x artık 10'dur, çünkü *p üzerinden değiştirildi."};
    lessons[53].commonMistakes = {
        "Bir pointer tanımında * türe aittir (int* p), ama bir ifadede "
        "* dereference operatörüdür (*p) — aynı sembolün bağlama göre "
        "iki farklı anlamı vardır.",
        "nullptr veya ilklendirilmemiş bir pointer'ı dereference etmek "
        "tanımsız davranıştır ve genellikle çalışma zamanında çökmeye "
        "yol açar.",
    };

    lessons[54].explanation =
        "nullptr, \"hiçbir şeyi göstermeyen\" bir pointer'ı ifade eden, "
        "C++11 ile gelen tip-güvenli (type-safe) null pointer "
        "sabitidir. Bir pointer henüz geçerli bir adrese atanmadıysa "
        "nullptr ile ilklendirilmesi iyi bir alışkanlıktır. nullptr'ı "
        "dereference etmeye çalışmak (*p, p nullptr iken) tanımsız "
        "davranıştır ve genellikle çalışma zamanında çökmeye (erişim "
        "ihlaline) yol açar.";
    lessons[54].syntax = "tür* isim = nullptr;";
    lessons[54].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int* p = nullptr;\n"
        "    if (p == nullptr) {\n"
        "        std::cout << \"Pointer bos.\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[54].lineExplanations = {
        "int* p = nullptr; : p, hiçbir şeyi göstermeyecek şekilde "
        "ilklendirilir.",
        "if (p == nullptr) : p'nin gerçekten boş olup olmadığı güvenle "
        "kontrol edilebilir."};
    lessons[54].commonMistakes = {
        "Eski C++ kodlarında NULL veya düz 0 kullanılırdı; nullptr daha "
        "tip-güvenlidir ve modern C++'ta tercih edilir.",
        "p == nullptr kontrolü yapmadan bir pointer'ı dereference "
        "etmek, tanımsız davranışa yol açabilecek ciddi bir hatadır.",
    };

    lessons[55].explanation =
        "Bir dizi adı, kullanıldığı çoğu bağlamda ilk elemanının "
        "adresine \"decay\" olur (dönüşür). Bu sayede bir pointer, dizi "
        "elemanları üzerinde dolaşmak (traverse) için kullanılabilir. "
        "ptr++ ifadesi pointer'ı 1 byte değil, gösterdiği türün boyutu "
        "(sizeof) kadar ileri taşır.";
    lessons[55].syntax = "for (int* p = dizi; p != dizi + n; ++p) { ... }";
    lessons[55].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int sayilar[3] = {10, 20, 30};\n"
        "    int* p = sayilar;\n"
        "    for (int i = 0; i < 3; ++i) {\n"
        "        std::cout << *p << \" \";\n"
        "        ++p;\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[55].lineExplanations = {
        "int* p = sayilar; : dizi adı ilk elemanın adresine dönüştüğü "
        "için p, sayilar[0]'ı gösterir.",
        "++p; : p, bir sonraki int elemanına (4 byte ileri, 1 byte "
        "değil) taşınır."};
    lessons[55].commonMistakes = {
        "p + 1, p'yi 1 byte değil sizeof(int) (genellikle 4) byte ileri "
        "taşır; bunu \"1 byte ileri gider\" sanmak yaygın bir hatadır.",
        "Dizinin son elemanından sonrasını (dizi + n'den sonrasını) "
        "dereference etmek tanımsız davranıştır.",
    };

    lessons[56].explanation =
        "new operatörü, bellekte dinamik olarak (çalışma zamanında, "
        "heap üzerinde) yer ayırır ve o yerin adresini bir pointer "
        "olarak döndürür. new int(5) hem bellek ayırır hem de 5 "
        "değeriyle ilklendirir. Dinamik olarak ayrılan bellek, "
        "programcı tarafından delete ile serbest bırakılana kadar (ya "
        "da program sonlanana kadar) ayrılmış kalır.";
    lessons[56].syntax = "tür* isim = new tür(deger);";
    lessons[56].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int* p = new int(42);\n"
        "    std::cout << *p;\n"
        "    delete p;\n"
        "    return 0;\n"
        "}";
    lessons[56].lineExplanations = {
        "int* p = new int(42); : heap üzerinde bir int için yer "
        "ayrılır, 42 ile ilklendirilir, adresi p'ye atanır.",
        "delete p; : ayrılan bellek serbest bırakılır."};
    lessons[56].commonMistakes = {
        "new ile ayrılan bellek, karşılık gelen delete çağrılmadan "
        "unutulursa bellek sızıntısına (memory leak) yol açar — bu, "
        "programın çökmesine değil, sadece o belleğin bir daha "
        "kullanılamamasına (programın kullanabileceği belleğin "
        "azalmasına) neden olur.",
    };

    lessons[57].explanation =
        "delete operatörü, new ile ayrılmış belleği serbest bırakır. "
        "Her new çağrısının karşılığında tam olarak bir delete çağrısı "
        "olmalıdır. delete çağrıldıktan sonra pointer \"sarkan\" "
        "(dangling) hale gelir; bu pointer'ı tekrar dereference etmek "
        "veya tekrar delete etmek tanımsız davranıştır.";
    lessons[57].syntax = "delete pointer;";
    lessons[57].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int* p = new int(7);\n"
        "    std::cout << *p;\n"
        "    delete p;\n"
        "    p = nullptr;\n"
        "    return 0;\n"
        "}";
    lessons[57].lineExplanations = {
        "delete p; : p'nin gösterdiği bellek serbest bırakılır.",
        "p = nullptr; : p, artık geçersiz (dangling) olan eski adresi "
        "yanlışlıkla tekrar kullanmamak için boşa ayarlanır."};
    lessons[57].commonMistakes = {
        "Aynı pointer'ı iki kez delete etmek (double delete) tanımsız "
        "davranıştır.",
        "delete'ten sonra pointer'ı nullptr yapmak zorunlu değildir ama "
        "yanlışlıkla tekrar kullanılmasını (dangling pointer hatasını) "
        "önlemek için iyi bir alışkanlıktır.",
    };

    lessons[58].explanation =
        "new[] operatörü, çalışma zamanında boyutu belirlenen bir dizi "
        "ayırır (dinamik dizi). new[] ile ayrılan diziler, delete[] ile "
        "(köşeli parantezli haliyle) serbest bırakılmalıdır; sıradan "
        "delete kullanmak tanımsız davranıştır.";
    lessons[58].syntax = "tür* isim = new tür[boyut]; // ... delete[] isim;";
    lessons[58].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int n = 3;\n"
        "    int* dizi = new int[n];\n"
        "    for (int i = 0; i < n; ++i) {\n"
        "        dizi[i] = i * 10;\n"
        "    }\n"
        "    for (int i = 0; i < n; ++i) {\n"
        "        std::cout << dizi[i] << \" \";\n"
        "    }\n"
        "    delete[] dizi;\n"
        "    return 0;\n"
        "}";
    lessons[58].lineExplanations = {
        "int* dizi = new int[n]; : n elemanlık bir int dizisi heap "
        "üzerinde ayrılır.",
        "delete[] dizi; : new[] ile ayrılan dizi, köşeli parantezli "
        "delete[] ile serbest bırakılır."};
    lessons[58].commonMistakes = {
        "new[] ile ayrılan bir diziyi delete (köşeli parantezsiz) ile "
        "silmek tanımsız davranıştır; her zaman delete[] kullanılmalıdır.",
        "std::vector, aynı esnekliği manuel bellek yönetimi olmadan "
        "sunduğu için modern C++'ta çoğunlukla new[]/delete[] yerine "
        "tercih edilir.",
    };

    lessons[59].explanation =
        "Bir referans (&), var olan bir değişkene ikinci bir isim "
        "(takma ad) tanımlamanın yoludur. Pointer'ların aksine bir "
        "referans, tanımlandığı anda mutlaka ilklendirilmelidir ve bir "
        "kez bağlandıktan sonra başka bir değişkeni gösterecek şekilde "
        "değiştirilemez (rebind edilemez). Ayrıca bir referans asla "
        "\"boş\" (null) olamaz ve pointer aritmetiği (++, +1 gibi) "
        "desteklemez.";
    lessons[59].syntax = "tür& isim = degisken;";
    lessons[59].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int x = 5;\n"
        "    int& r = x;\n"
        "    r = 10;\n"
        "    std::cout << x;\n"
        "    return 0;\n"
        "}";
    lessons[59].lineExplanations = {
        "int& r = x; : r, x'in bir takma adı olur (aynı değişkeni "
        "gösterir).",
        "r = 10; : r üzerinden yapılan değişiklik doğrudan x'i etkiler."};
    lessons[59].commonMistakes = {
        "int& r; (ilklendirmeden) tanımlamak derleme hatasıdır — "
        "referanslar boş bırakılamaz.",
        "int& r = x; tanımından sonra r = y; yazmak, r'yi y'ye "
        "\"yeniden bağlamaz\"; bunun yerine y'nin değerini x'e (r "
        "üzerinden) kopyalar — pointer'lardan farklı olarak bir "
        "referans asla başka bir değişkeni göstermeye geçemez.",
    };
}
```

- [ ] **Step 3: Wire the new function into `LessonManager`**

`src/LessonManager.cpp` already includes `"LessonContent.h"` (from
Phase 13). Change the constructor's final lines from:

```cpp
    applyIntroLessonContent(lessons_);
    applySection2LessonContent(lessons_);
    applySection3LessonContent(lessons_);
    applySection4LessonContent(lessons_);
    applySection5LessonContent(lessons_);
}
```

to:

```cpp
    applyIntroLessonContent(lessons_);
    applySection2LessonContent(lessons_);
    applySection3LessonContent(lessons_);
    applySection4LessonContent(lessons_);
    applySection5LessonContent(lessons_);
    applySection6LessonContent(lessons_);
}
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/LessonContent.h
    src/LessonContentSection2.cpp
    src/LessonContentSection3.cpp
    src/LessonContentSection4.cpp
    src/LessonContentSection5.cpp
```

to:

```cmake
    src/LessonContent.h
    src/LessonContentSection2.cpp
    src/LessonContentSection3.cpp
    src/LessonContentSection4.cpp
    src/LessonContentSection5.cpp
    src/LessonContentSection6.cpp
```

- [ ] **Step 5: Extend the content-coverage tests**

In `tests/LessonManagerTests.cpp`, replace:

```cpp
TEST_CASE(LessonManager_TopicsElevenToFiftyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 50; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsElevenToSixtyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 60; ++topicId) {
```

(keep the rest of that test's body unchanged). Then replace:

```cpp
TEST_CASE(LessonManager_TopicsFiftyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 51; topicId <= 100; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsSixtyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 61; topicId <= 100; ++topicId) {
```

(keep the rest of that test's body unchanged — there must be exactly
these two content-coverage tests afterward, not three).

- [ ] **Step 6: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `92/92 test(s) passed.` (same count as Phase 16's end state —
this task only renames/widens two existing tests' ranges).

- [ ] **Step 7: Commit**

```bash
git add src/LessonContent.h src/LessonContentSection6.cpp src/LessonManager.cpp CMakeLists.txt tests/LessonManagerTests.cpp
git commit -m "feat(content): add Section 6 lesson content (topics 51-60)"
```

---

### Task 2: Questions for topics 51-54 (ids 1233-1348)

**Files:**
- Modify: `src/QuestionContent.h` (add one new declaration)
- Create: `src/QuestionsSection6.cpp`
- Modify: `src/QuestionManager.cpp` (include, call, bump `reserve()`)
- Modify: `CMakeLists.txt` (add the new `.cpp`)

**Interfaces:**
- Produces: `void appendSection6Questions(std::vector<Question>& questions);`
  — Task 3 and Task 4 append more `questions.push_back(...)` calls to
  this SAME function body (in this same file) for topics 55-57 and
  58-60 respectively. This task only adds topics 51-54 (ids 1233-1348).

- [ ] **Step 1: Add the new declaration**

In `src/QuestionContent.h`, add this line after the existing
`appendSection5Questions` declaration (do not remove that one):

```cpp
void appendSection6Questions(std::vector<Question>& questions);
```

- [ ] **Step 2: Write topics 51-54's questions**

Create `src/QuestionsSection6.cpp` with exactly this content:

```cpp
#include "QuestionContent.h"

#include "Question.h"

void appendSection6Questions(std::vector<Question>& questions) {
    // Topic 51: Lambda fonksiyonları
    questions.push_back(Question{
        .id = 1233, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Lambda ifadesinin genel yapısı nedir?",
        .options = {"[yakalama](parametreler) { govde }", "def parametreler: govde", "function(parametreler) { govde }", "lambda parametreler { govde }"},
        .acceptedAnswers = {"a"},
        .explanation = "Lambda ifadeleri [yakalama](parametreler) { govde } biçiminde yazılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1234, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "auto f = [](int a, int b) { return a + b; };\nf(3, 4) çağrısı ne döndürür?",
        .options = {"7", "34", "\"34\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "3 + 4 = 7.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1235, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "[] (boş yakalama listesi) olan bir lambda, dışındaki değişkenlere erişebilir mi?",
        .options = {"Hayır, hiçbir dış değişkene erişemez", "Evet, tüm dış değişkenlere otomatik erişir", "Sadece global değişkenlere erişir", "Sadece const değişkenlere erişir"},
        .acceptedAnswers = {"a"},
        .explanation = "Boş yakalama listesi, lambda'nın dışarıdaki hiçbir değişkene erişemeyeceği anlamına gelir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1236, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nauto f = [x]() { return x; };\nx = 100;\nstd::cout << f();\nEkrana ne yazdırılır?",
        .options = {"5", "100", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "[x] değer ile yakalar; x'in lambda oluşturulduğu andaki değeri (5) dondurulur, sonraki değişiklik f()'i etkilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1237, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nauto f = [&x]() { return x; };\nx = 100;\nstd::cout << f();\nEkrana ne yazdırılır?",
        .options = {"100", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "[&x] referans ile yakalar; f() her zaman x'in güncel değerini görür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1238, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nauto f = [x]() { x = 100; return x; };\nBu kod derlenir mi?",
        .options = {"Hayır, x lambda içinde varsayılan olarak sabittir (const), mutable olmadan değiştirilemez", "Evet, sorunsuz derlenir", "Evet ama x her zaman 0 olur", "Hayır, çünkü [x] geçersiz bir yakalama şeklidir"},
        .acceptedAnswers = {"a"},
        .explanation = "Değer ile yakalanan bir değişken, lambda gövdesi içinde varsayılan olarak değiştirilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1239, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nauto f = [x]() mutable { x = 100; return x; };\nstd::cout << f() << x;\nEkrana ne yazdırılır?",
        .options = {"\"1005\"", "\"100100\"", "\"55\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "mutable, sadece lambda'nın kendi iç kopyasını değiştirmeye izin verir (f()=100); dışarıdaki x hiç etkilenmez (5 kalır).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1240, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1, b = 2;\nauto f = [a, &b]() { return a + b; };\na = 10;\nb = 20;\nstd::cout << f();\nEkrana ne yazdırılır?",
        .options = {"21", "30", "3", "12"},
        .acceptedAnswers = {"a"},
        .explanation = "a değer ile yakalanmıştır (donmuş değeri 1); b referans ile yakalanmıştır (güncel değeri 20). 1 + 20 = 21.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1241, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Lambda ifadeleri, isimsiz (anonim) fonksiyonlar tanımlamanın bir yoludur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: lambda'lar isimsiz fonksiyonlardır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1242, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "[] (boş yakalama listesi) olan bir lambda, dışarıdaki herhangi bir değişkene otomatik olarak erişebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: boş yakalama listesi hiçbir dış değişkene erişim vermez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1243, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "[x] ile değer olarak yakalanan bir değişken, lambda içinde varsayılan olarak değiştirilemez (const).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: mutable eklenmeden değiştirilemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1244, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "[&x] ile referans olarak yakalayan bir lambda, dışarıdaki x değişkenini gerçekten değiştirebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: referans ile yakalama, orijinal değişkene doğrudan erişim sağlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1245, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Değer ile yakalanan (örneğin [x]) bir değişken, lambda oluşturulduktan SONRA dışarıda değiştirilirse, lambda içindeki kopyası da otomatik olarak güncellenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: değer ile yakalama, lambda oluşturulduğu andaki değeri dondurur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1246, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "mutable olarak işaretlenmiş bir lambda, değer ile yakalanan bir değişkeni kendi iç kopyasında değiştirebilir, ama bu değişiklik dışarıdaki orijinal değişkeni etkilemez.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: mutable sadece lambda'nın kendi kopyasını etkiler, orijinali değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1247, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir lambda ifadesinde köşeli parantez [] içindeki listeye _____ listesi denir (Türkçe kelime).",
        .acceptedAnswers = {"yakalama"},
        .explanation = "Köşeli parantez içindeki listeye yakalama (capture) listesi denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1248, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "auto f = [](int a) { return a * 2; };\nstd::cout << f(5);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"10"},
        .explanation = "5 * 2 = 10.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1249, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 3;\nauto f = [x]() { return x * x; };\nstd::cout << f();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"9"},
        .explanation = "3 * 3 = 9.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1250, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 3;\nauto f = [&x]() { return x * x; };\nx = 5;\nstd::cout << f();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"25"},
        .explanation = "Referans ile yakalama, güncel değeri (5) görür: 5*5=25.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1251, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Değer ile yakalanan bir değişkeni lambda gövdesi içinde değiştirebilmek için lambda'nın _____ olarak işaretlenmesi gerekir (İngilizce anahtar kelime).",
        .acceptedAnswers = {"mutable"},
        .explanation = "mutable anahtar kelimesi, değer ile yakalanan kopyaların değiştirilmesine izin verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1252, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 1;\nauto f = [x]() { return x; };\nx = 99;\nstd::cout << f();\nEkran çıktısı _____ olur (x, lambda oluşturulduğu andaki değeriyle donduğu için).",
        .acceptedAnswers = {"1"},
        .explanation = "Değer ile yakalama, x'in lambda oluşturulduğu andaki değerini (1) dondurur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1253, .topicId = 51,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int carpan = 3;\n_____\nstd::cout << carp(4);\nBir sayıyı carpan (referans ile yakalanmış) ile çarpan carp adlı bir lambda tanımlayan satırı (auto ile) tamamlayın.",
        .acceptedAnswers = {"auto carp = [&carpan](int x) { return x * carpan; };"},
        .explanation = "Lambda, carpan'ı referans ile yakalayıp parametreyle çarpar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1254, .topicId = 51,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int taban = 10;\nauto ekle = [taban](int x) {\n    _____\n}\nstd::cout << ekle(5);\nekle lambda'sının gövdesini (x ile taban'ın toplamını döndüren satırı) tamamlayın.",
        .acceptedAnswers = {"return x + taban;"},
        .explanation = "Lambda, x ile taban'ın (değer ile yakalanmış) toplamını döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1255, .topicId = 51,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "auto carp = [](int a, int b) {\n    return a * b;\n};\nint main() {\n    std::cout << carp(3, 4);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "3 * 4 = 12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1256, .topicId = 51,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int x = 2;\nauto f = [x]() mutable {\n    x = x * 10;\n    return x;\n};\nint main() {\n    std::cout << f() << x;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"202"},
        .explanation = "f() lambda'nın kendi kopyasını değiştirip 20 döndürür; dışarıdaki x hiç etkilenmez (2 kalır): '202'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1257, .topicId = 51,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint x = 5;\nauto f = [x]() {\n    x = 10;\n    return x;\n};\n\nBu kod derlenmez çünkü [x] ile değer olarak yakalanan x, lambda gövdesi içinde varsayılan olarak sabittir (const) ve mutable olmadan değiştirilemez. Hatalı lambda başlığını, mutable eklenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"auto f = [x]() mutable {"},
        .explanation = "mutable eklenmeden, değer ile yakalanan bir değişken değiştirilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1258, .topicId = 51,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nint sayi = 5;\nauto f = [sayi]() {\n    return sayi;\n};\nsayi = 100;\nstd::cout << f();\n\nProgramcı ekrana 100 yazdırılmasını bekliyor ama [sayi] değer ile yakalama yaptığından f() her zaman lambda oluşturulduğu andaki değeri (5) döndürür. Lambda tanımını, sayi'nin güncel değerini görecek şekilde (referans ile yakalayarak) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"auto f = [&sayi]() {"},
        .explanation = "Referans ile yakalama, f()'in her zaman sayi'nin güncel değerini görmesini sağlar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1259, .topicId = 51,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint carpan = 2;\nauto carp = [carpan](int x) {\n    carpan = carpan + 1;\n    return x * carpan;\n};\n\nBu kod derlenmez çünkü [carpan] değer ile yakalandığından lambda içinde değiştirilemez. Lambda başlığını, mutable eklenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"auto carp = [carpan](int x) mutable {"},
        .explanation = "mutable, değer ile yakalanan carpan'ın lambda'nın kendi kopyasında değiştirilmesine izin verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1260, .topicId = 51,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir lambda tanımlayıp çağıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << topla(3, 4);\n    return 0;\n}", "auto topla = [](int a, int b) {\n    return a + b;\n};", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), lambda tanımı (2), çağrı ve kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1261, .topicId = 51,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "İki sayıyı çarpan (parametre olarak alan) bir lambda tanımlayıp, sonucunu bir değişkene atayıp ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"auto", "=", "[", "]", "cout"},
        .explanation = "Lambda parametreleriyle çarpım yapmalı, sonuç bir değişkene atanıp yazdırılmalıdır.",
        .baseXp = 40,
    });

    // Topic 52: Pointer tanımlama
    questions.push_back(Question{
        .id = 1262, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir pointer değişkeni nasıl tanımlanır?",
        .options = {"tür* isim;", "tür isim*;", "pointer isim;", "&tür isim;"},
        .acceptedAnswers = {"a"},
        .explanation = "Pointer tanımı tür* isim; şeklinde yapılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1263, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int* p; ifadesinde p neyi tutar?",
        .options = {"Bir int değişkeninin bellek adresini", "Doğrudan bir int değerini", "Bir string'i", "Bir fonksiyon adını"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir pointer, gösterdiği değişkenin bellek adresini tutar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1264, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nBu ifadede p'nin türü nedir?",
        .options = {"int*", "int", "int&", "void*"},
        .acceptedAnswers = {"a"},
        .explanation = "p, int* türünde bir pointerdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1265, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p; (ilklendirmeden) tanımlandığında p'nin değeri nedir?",
        .options = {"Belirsiz (garbage), rastgele bir adres", "Otomatik olarak nullptr", "Her zaman 0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "İlklendirilmemiş bir pointer, belirsiz bir değer taşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1266, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p, q; ifadesinde q'nun türü nedir?",
        .options = {"int (pointer değil)", "int*", "int**", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "* işareti türe değil değişken adına bağlanır; sadece p pointer olur, q sıradan bir int'tir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1267, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p, *q; ifadesinde kaç tane pointer tanımlanmıştır?",
        .options = {"2 (p ve q ikisi de pointer)", "1 (sadece p)", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Her değişkenin önüne * konarak iki pointer da doğru şekilde tanımlanmıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1268, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p;\nstd::cout << *p;\nBu kod derlenir mi, çalışırsa ne olur?",
        .options = {"Derlenir ama p ilklendirilmediği için *p'yi okumak tanımsız davranıştır (genellikle çöker)", "Derlenir ve her zaman 0 yazdırır", "Derlenmez (derleme hatası)", "Derlenir ve her zaman rastgele ama güvenli bir sayı yazdırır"},
        .acceptedAnswers = {"a"},
        .explanation = "İlklendirilmemiş bir pointerı dereference etmek tanımsız davranıştır ve genellikle çöker.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1269, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1, b = 2;\nint* p = &a;\np = &b;\nstd::cout << *p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"2", "1", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "p, b'yi gösterecek şekilde yeniden atanmıştır (reassign); *p artık b'nin değerini (2) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1270, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir pointer, başka bir değişkenin bellek adresini tutar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: pointer, bir adresi tutan değişkendir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1271, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "int* p; ifadesi, p'yi otomatik olarak nullptr ile ilklendirir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: açıkça ilklendirilmezse p belirsiz bir değer taşır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1272, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int* p, q; ifadesinde hem p hem de q pointer olur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: sadece p pointer olur, q sıradan bir int'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1273, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir pointer, programın çalışması sırasında farklı bir değişkeni gösterecek şekilde yeniden atanabilir (reassign edilebilir).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: pointer'lar, referanslardan farklı olarak yeniden atanabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1274, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İlklendirilmemiş bir pointer'ı dereference etmek (*p ile okumak) tanımsız davranıştır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: bu, tanımsız davranışın klasik bir örneğidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1275, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int* p, *q; ifadesinde p ve q'nun ikisi de pointer olarak tanımlanır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: her ikisinin önünde de * olduğundan ikisi de pointer'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1276, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "int _____ p; ifadesi, p'yi bir int pointer'ı olarak tanımlar (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "* sembolü, p'nin bir pointer olduğunu belirtir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1277, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 7;\nint* p = &x;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "*p, p'nin gösterdiği x'in değerini (7) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1278, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int* p, q; ifadesinde q'nun türü _____ olur (bir kelime, İngilizce).",
        .acceptedAnswers = {"int"},
        .explanation = "q, pointer değil sıradan bir int olarak tanımlanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1279, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 1, b = 2;\nint* p = &a;\np = &b;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "p yeniden atanarak b'yi gösterir; *p artık b'nin değerini (2) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1280, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "İki pointer'ı tek satırda tanımlamak için int* p, _____q; yazılmalıdır (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "Her değişkenin önüne * konarak ikisi de pointer olarak tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1281, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p;\nBu satırdan sonra, p ilklendirilmeden dereference edilirse (*p okunursa) bu _____ davranıştır (İngilizce iki kelime, örn. 'undefined behavior').",
        .acceptedAnswers = {"undefined behavior"},
        .explanation = "İlklendirilmemiş bir pointer'ı dereference etmek undefined behavior'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1282, .topicId = 52,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int x = 9;\n_____\nstd::cout << *p;\nx'in adresini tutan p adlı bir pointer tanımlayan satırı tamamlayın.",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, x'in adresiyle ilklendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1283, .topicId = 52,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 3, b = 4;\nint* p = &a;\n_____\nstd::cout << *p;\np'yi b'yi gösterecek şekilde yeniden atayan satırı tamamlayın.",
        .acceptedAnswers = {"p = &b;"},
        .explanation = "p, b'nin adresine yeniden atanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1284, .topicId = 52,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int x = 8;\nint* p = &x;\n*p = 20;\nstd::cout << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"20"},
        .explanation = "*p = 20 ifadesi, p'nin gösterdiği x'i 20 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1285, .topicId = 52,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5, b = 6;\nint* p = &a;\nint* q = &b;\np = q;\n*p = 100;\nstd::cout << a << \" \" << b;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"5 100"},
        .explanation = "p = q ile p artık b'yi gösterir; *p = 100, b'yi 100 yapar. a hiç değişmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1286, .topicId = 52,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p, q;\nq = 5;\nstd::cout << q;\n\nBu kod, programcının hem p hem de q'yu pointer sanmasından kaynaklanan bir kavram yanılgısı içeriyor: q aslında sıradan bir int'tir (derleme hatası vermez, ama q bir pointer DEĞİLDİR). İki pointer birden tanımlamak isteniyorsa satırı nasıl yazmak gerekirdi? Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"int* p, *q;"},
        .explanation = "İki pointer tanımlamak için her değişkenin önüne * konmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1287, .topicId = 52,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p;\nstd::cout << *p;\n\nBu kod derlenir ama p hiçbir adrese atanmadan (ilklendirilmeden) dereference edildiği için tanımsız davranışa yol açar. p'yi geçerli bir x değişkenine bağlayan, hatalı ilk satırı düzeltilmiş haliyle yazın (x'in zaten tanımlı bir int değişkeni olduğunu varsayın).",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, geçerli bir x değişkeninin adresiyle ilklendirilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1288, .topicId = 52,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint sayi = 10;\nint *p, *r;\np = &sayi\nstd::cout << *p;\n\nProgramcı p = &sayi; satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"p = &sayi;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1289, .topicId = 52,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir pointer tanımlayıp kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* p = &x;", "std::cout << *p;\n    return 0;\n}", "int main() {\n    int x = 42;"},
        .acceptedAnswers = {"3 1 2"},
        .explanation = "main açılışı ve x tanımı (3), pointer tanımı (1), yazdırma ve kapanış (2): sıra 3 1 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1290, .topicId = 52,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int değişkeni tanımlayıp, onun adresini tutan bir pointer oluşturun; pointer üzerinden (dereference ederek) değişkenin değerini değiştirip ekrana yazdırın.",
        .acceptedAnswers = {"int*", "&", "*", "cout"},
        .explanation = "Pointer, değişkenin adresiyle ilklendirilmeli ve dereference ile değer değiştirilmelidir.",
        .baseXp = 40,
    });

    // Topic 53: & adres operatörü
    questions.push_back(Question{
        .id = 1291, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "& operatörünün bir değişkenin önünde kullanılması ne anlama gelir?",
        .options = {"O değişkenin bellek adresini almak", "O değişkeni referansa çevirmek", "O değişkeni silmek", "O değişkenin değerini iki katına çıkarmak"},
        .acceptedAnswers = {"a"},
        .explanation = "& operatörü, bir değişkenin bellek adresini verir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1292, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nBu ifadede &x ne üretir?",
        .options = {"x'in bellek adresi", "x'in değeri (5)", "x'in türü", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "&x, x'in bellek adresini veren bir pointer değeri üretir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1293, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nstd::cout << (p == &x);\nEkrana ne yazdırılır?",
        .options = {"1", "0", "5", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p, &x ile ilklendirildiğinden p == &x her zaman true (1) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1294, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "& sembolü hangi iki bağlamda farklı anlamlara gelir?",
        .options = {"Bir ifadede adres operatörü, bir tanımda referans bildirimi", "Bir ifadede toplama, bir tanımda çıkarma", "Sadece pointer tanımlarında kullanılır", "& sembolünün tek bir anlamı vardır"},
        .acceptedAnswers = {"a"},
        .explanation = "& sembolü ifadede adres operatörü, tanımda ise referans bildirimi anlamına gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1295, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 3, y = 3;\nstd::cout << (&x == &y);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"0", "1", "3", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "x ve y aynı değere sahip olsalar da farklı değişkenlerdir, dolayısıyla farklı adreslere sahiptirler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1296, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nint& r = x;\nstd::cout << (&r == &x);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"1", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir referans, bağlı olduğu değişkenle tamamen aynı adresi paylaşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1297, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1;\nint* p = &a;\nint** pp = &p;\n**pp ifadesi neyi verir?",
        .options = {"a'nın değerini (1)", "p'nin adresini", "a'nın adresini", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "*pp, p'yi verir; *p de a'nın değerini (1) verir, dolayısıyla **pp = 1.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1298, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int x = 5;\nint* p1 = &x;\nint* p2 = &x;\nstd::cout << (p1 == p2);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"1", "0", "5", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "p1 ve p2, ikisi de x'in aynı adresini tuttuğundan p1 == p2 true (1) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1299, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "& operatörü, bir değişkenin bellek adresini verir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: & operatörü adres operatörüdür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1300, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "& sembolü her zaman aynı anlama gelir, bağlama göre değişmez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: ifadede adres operatörü, tanımda referans bildirimi anlamına gelir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1301, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "İki farklı değişken, aynı değere sahip olsa bile genellikle farklı bellek adreslerine sahiptir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: her değişken kendi belleğinde ayrı bir yer kaplar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1302, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir referansın adresi (&r), bağlı olduğu değişkenin adresiyle (&x) aynıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: referans, bağlı olduğu değişkenle aynı adresi paylaşır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1303, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "&x ifadesinin sonucu, bir int* türünde bir pointer değeridir (x bir int ise).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: &x, int* türünde bir adres değeri üretir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1304, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir değişkenin adresi, program her çalıştırıldığında her zaman aynı sayısal değere sahiptir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: adresler çalıştırmadan çalıştırmaya farklı olabilir; bu yüzden adres değerleri test edilmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1305, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir x değişkeninin adresini almak için _____x yazılır (bir sembol).",
        .acceptedAnswers = {"&"},
        .explanation = "& operatörü, adres almak için kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1306, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nstd::cout << (p == &x);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "p, &x ile ilklendirildiğinden karşılaştırma true (1) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1307, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 3, y = 3;\nstd::cout << (&x == &y);\nEkran çıktısı _____ olur (aynı değere sahip olsalar da farklı değişkenler oldukları için).",
        .acceptedAnswers = {"0"},
        .explanation = "Farklı değişkenler farklı adreslere sahiptir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1308, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nint& r = x;\nstd::cout << (&r == &x);\nEkran çıktısı _____ olur (bir referans, bağlı olduğu değişkenle aynı adresi paylaştığı için).",
        .acceptedAnswers = {"1"},
        .explanation = "Referans ve orijinal değişken aynı adresi paylaşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1309, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 1;\nint* p = &a;\nint** pp = &p;\nstd::cout << **pp;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "**pp, p üzerinden a'nın değerine (1) ulaşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1310, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "& sembolü bir ifadede adres operatörüyken, bir değişken tanımında (int& r = x;) _____ bildirimi anlamına gelir (Türkçe kelime).",
        .acceptedAnswers = {"referans"},
        .explanation = "Tanımda & sembolü referans bildirimi anlamına gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1311, .topicId = 53,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 15;\n_____\nstd::cout << *adres;\nsayi'nin adresini tutan adres adlı bir pointer tanımlayan satırı yazın.",
        .acceptedAnswers = {"int* adres = &sayi;"},
        .explanation = "adres, sayi'nin bellek adresiyle ilklendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1312, .topicId = 53,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 1;\nint* p = &a;\n_____\nstd::cout << **pp;\np'nin adresini tutan pp adlı bir int** pointer tanımlayan satırı yazın.",
        .acceptedAnswers = {"int** pp = &p;"},
        .explanation = "pp, p'nin adresini tutan bir pointer'a pointer'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1313, .topicId = 53,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int x = 4;\nint* p = &x;\nstd::cout << (*p == x);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "*p, x'in kendisine eşit olduğundan karşılaştırma true (1) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1314, .topicId = 53,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 2, b = 2;\nint* p = &a;\nint* q = &b;\nstd::cout << (*p == *q) << (p == q);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "*p == *q true (1) çünkü değerler eşit (2==2); p == q false (0) çünkü farklı adresler.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1315, .topicId = 53,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint x = 5;\nint* p = x;\nstd::cout << *p;\n\nBu kod derlenmez çünkü p bir int* iken x bir int'tir (adres değil, değer atanmaya çalışılıyor); türler uyuşmuyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p'ye x'in kendisi değil, adresi (&x) atanmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1316, .topicId = 53,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint x = 5;\nint y = &x;\nstd::cout << y;\n\nBu kod derlenmez çünkü y bir int olarak tanımlanmış ama kendisine bir adres (&x, bir int* değeri) atanmaya çalışılıyor; türler uyuşmuyor. Hatalı satırı, y'yi doğru türde (bir pointer olarak) tanımlayacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int* y = &x;"},
        .explanation = "Bir adres değeri ancak bir pointer değişkende tutulabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1317, .topicId = 53,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint x = 5;\nint* p;\np = x;\nstd::cout << *p;\n\nProgramcı p'ye x'in adresini değil, doğrudan değerini atamış; türler uyuşmuyor. Düzeltilmiş atama satırını yazın.",
        .acceptedAnswers = {"p = &x;"},
        .explanation = "p'ye x'in adresi (&x) atanmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1318, .topicId = 53,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, & operatörüyle bir pointer ilklendiren geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* p = &x;\n    std::cout << *p;\n    return 0;\n}", "int x = 7;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), x tanımı (2), pointer + yazdırma + kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1319, .topicId = 53,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int değişken tanımlayın, & operatörüyle adresini bir pointer'a atayın, ardından bu adresin gerçekten o değişkenin adresi olduğunu (== ile pointer'ı &değişken ile karşılaştırarak) ekrana yazdırın.",
        .acceptedAnswers = {"&", "int*", "cout"},
        .explanation = "Pointer, & operatörüyle ilklendirilip == ile karşılaştırılmalıdır.",
        .baseXp = 40,
    });

    // Topic 54: * dereference operatörü
    questions.push_back(Question{
        .id = 1320, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "* operatörünün bir pointer'ın önünde kullanılması ne anlama gelir?",
        .options = {"Pointer'ın gösterdiği adresteki değere erişmek (dereference)", "Pointer'ı silmek", "Pointer'ın adresini almak", "İki pointer'ı çarpmak"},
        .acceptedAnswers = {"a"},
        .explanation = "* operatörü, pointer'ın gösterdiği değere erişmeyi sağlar (dereference).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1321, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nstd::cout << *p;\nEkrana ne yazdırılır?",
        .options = {"5", "x'in adresi", "Derleme hatası", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "*p, p'nin gösterdiği x'in değerini (5) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1322, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\n*p = 20;\nstd::cout << x;\nEkrana ne yazdırılır?",
        .options = {"20", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "*p üzerinden yapılan atama, doğrudan x'i değiştirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1323, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "*(&x) ifadesi neye eşittir (x geçerli bir değişkense)?",
        .options = {"x'in kendisine", "x'in adresine", "0'a", "Her zaman derleme hatasına"},
        .acceptedAnswers = {"a"},
        .explanation = "& ve * birbirinin tersi işlemlerdir: *(&x) her zaman x'e eşittir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1324, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nstd::cout << *p;\nBu satır çalıştırılırsa ne olur?",
        .options = {"Tanımsız davranış (genellikle çöker)", "0 yazdırır", "Boş bir string yazdırır", "Sessizce hiçbir şey yapmaz"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr'ı dereference etmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1325, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 1, b = 2;\nint* p = &a;\n*p = *p + b;\nstd::cout << a;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"3", "1", "2", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "*p, a'nın kendisidir; *p = *p + b ifadesi a'yı 1+2=3 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1326, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5;\nint* p = &a;\nint* q = p;\n*q = 99;\nstd::cout << a << \" \" << *p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"99 99\"", "\"5 5\"", "\"99 5\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "q = p, p'nin tuttuğu adresi (a'nın adresini) kopyalar; *q = 99, a'yı 99 yapar, *p de artık 99'dur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1327, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int x = 10;\nint* p = &x;\nint* q = &x;\n*p = *p + *q;\nstd::cout << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"20", "10", "30", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p ve q ikisi de x'i gösterir; *p+*q=10+10=20, *p=20 ataması x'i 20 yapar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1328, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "* operatörü, bir pointer'ın gösterdiği adresteki değere erişmeyi sağlar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: bu işleme dereference denir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1329, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "nullptr olan bir pointer'ı dereference etmek (*p ile) güvenlidir ve her zaman 0 döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: nullptr'ı dereference etmek tanımsız davranıştır, güvenli değildir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1330, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "*(&x) ifadesi, geçerli bir x değişkeni için her zaman x'e eşittir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: & ve * birbirinin tersidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1331, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "*p = 10; ifadesi, p'nin gösterdiği adresteki değeri 10 yapar, p'nin kendisinin adresini değiştirmez.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: *p = 10, gösterilen değeri değiştirir; p'nin tuttuğu adres aynı kalır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1332, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki farklı pointer aynı değişkeni gösteriyorsa, birini dereference ederek yapılan değişiklik diğerinden de görülür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: ikisi de aynı belleği gösterdiğinden değişiklik ortaktır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1333, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir pointer tanımındaki * (int* p) ile bir ifadedeki * (*p) her zaman aynı işlemi (dereference) ifade eder.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: tanımda * pointer türünü belirtir, ifadede ise dereference işlemi yapar — aynı sembolün iki farklı anlamı vardır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1334, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir pointer'ın gösterdiği değere erişmek için pointer'ın önüne _____ konur (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "* sembolü dereference işlemini yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1335, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "*p, x'in değerini (5) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1336, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\n*p = 30;\nstd::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"30"},
        .explanation = "*p = 30, x'i 30 yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1337, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 2;\nint* p = &a;\n*p = *p * 5;\nstd::cout << a;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"10"},
        .explanation = "*p, a'nın kendisidir; 2*5=10, a artık 10'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1338, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "nullptr olan bir pointer'ı dereference etmek _____ davranıştır (İngilizce iki kelime, örn. 'undefined behavior').",
        .acceptedAnswers = {"undefined behavior"},
        .explanation = "nullptr'ı dereference etmek undefined behavior'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1339, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nint* p = &x;\nint* q = p;\n*q = 40;\nstd::cout << x;\nEkran çıktısı _____ olur (q, p'nin adresini kopyaladığı, yani aynı x'i gösterdiği için).",
        .acceptedAnswers = {"40"},
        .explanation = "q, p'nin adresini kopyaladığından aynı x'i gösterir; *q = 40, x'i 40 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1340, .topicId = 54,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int x = 8;\nint* p = &x;\n_____\nstd::cout << x;\np üzerinden x'in değerini 50 yapan satırı yazın.",
        .acceptedAnswers = {"*p = 50;"},
        .explanation = "*p = 50, p'nin gösterdiği x'i 50 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1341, .topicId = 54,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 3;\nint b = 4;\nint* p = &a;\n_____\nstd::cout << a;\np üzerinden a'nın değerini b ile çarpan satırı yazın.",
        .acceptedAnswers = {"*p = *p * b;"},
        .explanation = "*p = *p * b, a'yı a*b yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1342, .topicId = 54,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int x = 6;\nint* p = &x;\n*p += 4;\nstd::cout << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "*p += 4, x'i 6+4=10 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1343, .topicId = 54,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1, b = 2, c = 3;\nint* p = &a;\np = &b;\n*p = c;\nstd::cout << a << \" \" << b << \" \" << c;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 3 3"},
        .explanation = "p, b'yi gösterecek şekilde yeniden atanır; *p = c, b'yi c'nin değeri (3) yapar. a ve c değişmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1344, .topicId = 54,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p;\nstd::cout << *p;\n\nBu kod derlenir ama p hiçbir geçerli adrese atanmadan (ilklendirilmeden) dereference edildiği için tanımsız davranışa yol açar. p'yi geçerli bir x adlı int değişkenine bağlayan, hatalı ilk satırı düzeltilmiş haliyle yazın (x'in zaten tanımlı olduğunu varsayarak).",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, geçerli bir değişkenin adresiyle ilklendirilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1345, .topicId = 54,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p = nullptr;\nstd::cout << *p;\n\nBu kod, nullptr olan bir pointer'ı dereference ettiği için tanımsız davranışa (genellikle çökmeye) yol açar. p'yi dereference etmeden önce nullptr olup olmadığını kontrol eden bir if satırını (başlığını) yazın.",
        .acceptedAnswers = {"if (p != nullptr) {"},
        .explanation = "Dereference etmeden önce pointer'ın nullptr olup olmadığı kontrol edilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1346, .topicId = 54,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint* p = nullptr;\n*p = 5;\nstd::cout << *p;\n\nProgramcı nullptr olan p'yi doğrudan dereference edip değer atamaya çalışmış; bu tanımsız davranıştır. p'yi önce geçerli bir x değişkenine (zaten tanımlı olduğunu varsayarak) bağlayan düzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, dereference edilmeden önce geçerli bir adrese bağlanmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1347, .topicId = 54,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, * operatörüyle bir pointer'ın gösterdiği değeri değiştiren geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"*p = 99;\n    std::cout << x;\n    return 0;\n}", "int x = 1;\n    int* p = &x;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), x ve p tanımı (2), dereference + yazdırma + kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1348, .topicId = 54,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int değişken tanımlayın, adresini bir pointer'a atayın, ardından * operatörüyle (dereference ederek) değişkenin değerini değiştirip son değerini ekrana yazdırın.",
        .acceptedAnswers = {"*", "int*", "cout"},
        .explanation = "Pointer, dereference edilerek değişkenin değeri değiştirilmelidir.",
        .baseXp = 40,
    });
```

- [ ] **Step 3: Wire the new function into `QuestionManager`**

`src/QuestionManager.cpp` already includes `"QuestionContent.h"` (from
Phase 13). Change the constructor's opening `reserve` call and its
final append-call lines from:

```cpp
    questions_.reserve(1232);
```

to:

```cpp
    questions_.reserve(1522);
```

and from:

```cpp
    appendSection2Questions(questions_);
    appendSection3Questions(questions_);
    appendSection4Questions(questions_);
    appendSection5Questions(questions_);
```

to:

```cpp
    appendSection2Questions(questions_);
    appendSection3Questions(questions_);
    appendSection4Questions(questions_);
    appendSection5Questions(questions_);
    appendSection6Questions(questions_);
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/QuestionContent.h
    src/QuestionsSection2.cpp
    src/QuestionsSection3.cpp
    src/QuestionsSection4.cpp
    src/QuestionsSection5.cpp
```

to:

```cmake
    src/QuestionContent.h
    src/QuestionsSection2.cpp
    src/QuestionsSection3.cpp
    src/QuestionsSection4.cpp
    src/QuestionsSection5.cpp
    src/QuestionsSection6.cpp
```

- [ ] **Step 5: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `92/92 test(s) passed.` (unchanged — the test that counts
questions per topic is added in Task 4, once all of topics 51-60 have
their full 29 questions each).

- [ ] **Step 6: Commit**

```bash
git add src/QuestionContent.h src/QuestionsSection6.cpp src/QuestionManager.cpp CMakeLists.txt
git commit -m "feat(content): add questions for topics 51-54 (ids 1233-1348)"
```

---

### Task 3: Questions for topics 55-57 (ids 1349-1435)

**Files:**
- Modify: `src/QuestionsSection6.cpp` (append more `push_back` calls to
  the SAME `appendSection6Questions` function body Task 2 created —
  do not redeclare the function or touch any other file)

**Interfaces:**
- Consumes: `appendSection6Questions(std::vector<Question>& questions)`
  defined in `src/QuestionsSection6.cpp` by Task 2 — append to its body,
  after the last `questions.push_back(...)` for id 1348 and before the
  function's closing `}`.
- Produces: ids 1349-1435 added to the same function. Task 4 appends
  after this task's last id (1435).

- [ ] **Step 1: Write topics 55-57's questions**

In `src/QuestionsSection6.cpp`, inside `appendSection6Questions`, add
these `push_back` calls right after the id-1348 block (before the
function's closing `}`):

```cpp
    // Topic 55: nullptr
    questions.push_back(Question{
        .id = 1349, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "nullptr neyi ifade eder?",
        .options = {"Hiçbir şeyi göstermeyen, tip-güvenli bir pointer değeri", "Sıfır değerli bir int", "Boş bir string", "Bir referans türü"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr, hiçbir şeyi göstermeyen tip-güvenli bir null pointer sabitidir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1350, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int* p = nullptr;\nif (p == nullptr) {\n    std::cout << \"bos\";\n}\nEkrana ne yazdırılır?",
        .options = {"\"bos\"", "\"\"", "Derleme hatası", "Rastgele değer"},
        .acceptedAnswers = {"a"},
        .explanation = "p, nullptr ile ilklendirildiğinden koşul true olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1351, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "nullptr, C++'ın hangi versiyonuyla birlikte geldi?",
        .options = {"C++11", "C++98", "C++20", "C++03"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr, C++11 standardıyla birlikte geldi.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1352, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nstd::cout << *p;\nBu satır çalıştırılırsa ne olur?",
        .options = {"Tanımsız davranış (genellikle çöker)", "0 yazdırır", "Boş string yazdırır", "nullptr yazdırır"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr'ı dereference etmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1353, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "nullptr yerine eski kodlarda hangi ifadeler kullanılırdı?",
        .options = {"NULL veya 0", "void veya empty", "undefined veya none", "blank veya zero"},
        .acceptedAnswers = {"a"},
        .explanation = "Eski C++ kodlarında NULL veya düz 0 kullanılırdı.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1354, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nif (p) {\n    std::cout << \"dolu\";\n} else {\n    std::cout << \"bos\";\n}\nEkrana ne yazdırılır?",
        .options = {"\"bos\"", "\"dolu\"", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr, boolean bağlamda false olarak değerlendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1355, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p = nullptr;\nint x = 5;\np = &x;\nif (p != nullptr) {\n    std::cout << *p;\n}\nEkrana ne yazdırılır?",
        .options = {"5", "Hiçbir şey", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p, x'in adresine yeniden atandığından artık nullptr değildir; *p, x'in değerini (5) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1356, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p = nullptr;\nint* q = nullptr;\nstd::cout << (p == q);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"1", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "İki nullptr değeri her zaman birbirine eşittir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1357, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "nullptr, hiçbir şeyi göstermeyen bir pointer'ı ifade eder.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: nullptr, boş bir pointer değeridir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1358, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "nullptr'ı dereference etmek (*p ile, p nullptr iken) güvenlidir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: nullptr'ı dereference etmek tanımsız davranıştır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1359, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "nullptr, C++11 ile gelen tip-güvenli bir null pointer sabitidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1360, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir pointer, nullptr ile karşılaştırılarak (p == nullptr) güvenle kontrol edilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: bu, bir pointer'ın boş olup olmadığını kontrol etmenin standart yoludur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1361, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "if (p) koşulu, p nullptr olduğunda true (doğru) olarak değerlendirilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: nullptr, boolean bağlamda false olarak değerlendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1362, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "nullptr, eski C++ kodlarında kullanılan NULL veya 0'dan daha tip-güvenlidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: nullptr, tip-güvenli bir sabittir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1363, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Hiçbir şeyi göstermeyen bir pointer, C++11'den itibaren _____ ile ilklendirilir (bir kelime, İngilizce).",
        .acceptedAnswers = {"nullptr"},
        .explanation = "nullptr, boş bir pointer için kullanılan modern sabittir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1364, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int* p = nullptr;\nif (p == nullptr) {\n    std::cout << \"bos\";\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"bos"},
        .explanation = "p nullptr olduğundan koşul true olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1365, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int* p = nullptr;\nstd::cout << (p == nullptr);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "p nullptr olduğundan karşılaştırma true (1) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1366, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nif (p) {\n    std::cout << \"dolu\";\n} else {\n    std::cout << \"bos\";\n}\nEkran çıktısı _____ olur (nullptr, boolean bağlamda false değerlendirildiği için).",
        .acceptedAnswers = {"bos"},
        .explanation = "nullptr, if koşulunda false olarak değerlendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1367, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nint x = 9;\np = &x;\nstd::cout << (p == nullptr);\nEkran çıktısı _____ olur (p artık x'i gösterdiği için).",
        .acceptedAnswers = {"0"},
        .explanation = "p artık nullptr olmadığından karşılaştırma false (0) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1368, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "nullptr'ı dereference etmeye çalışmak _____ davranıştır (İngilizce iki kelime).",
        .acceptedAnswers = {"undefined behavior"},
        .explanation = "nullptr'ı dereference etmek undefined behavior'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1369, .topicId = 55,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\n_____\nstd::cout << \"p artik gecerli.\";\np'yi geçerli bir x değişkenine (zaten tanımlı olduğunu varsayarak) bağlayan satırı yazın.",
        .acceptedAnswers = {"p = &x;"},
        .explanation = "p, x'in adresine yeniden atanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1370, .topicId = 55,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\n_____ {\n    std::cout << \"p bos.\";\n}\np'nin nullptr olup olmadığını kontrol eden if satırının başlığını yazın.",
        .acceptedAnswers = {"if (p == nullptr)"},
        .explanation = "if (p == nullptr) koşulu, p'nin boş olup olmadığını kontrol eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1371, .topicId = 55,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nstd::cout << (p == nullptr);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "p nullptr olduğundan karşılaştırma true (1) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1372, .topicId = 55,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int x = 4;\nint* p = nullptr;\np = &x;\nstd::cout << (p == nullptr) << *p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"04"},
        .explanation = "p artık nullptr olmadığından ilk karşılaştırma 0, *p ise x'in değeri (4): '04'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1373, .topicId = 55,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p = nullptr;\nstd::cout << *p;\n\nBu kod, nullptr olan bir pointer'ı dereference ettiği için tanımsız davranışa (genellikle çökmeye) yol açar. Hatayı önlemek için p'yi dereference etmeden önce kontrol eden if satırının başlığını yazın.",
        .acceptedAnswers = {"if (p != nullptr) {"},
        .explanation = "Dereference etmeden önce pointer'ın nullptr olmadığı kontrol edilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1374, .topicId = 55,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p;\nif (p == nullptr) {\n    std::cout << \"bos\";\n}\n\nBu kod derlenir ama p, nullptr ile değil ilklendirilmeden bırakılmıştır; bu yüzden p == nullptr karşılaştırması güvenilir bir sonuç vermez (p belirsiz bir değer taşıdığından tesadüfen nullptr'a eşit olmayabilir). p'yi tanımlandığı anda nullptr ile ilklendiren düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"int* p = nullptr;"},
        .explanation = "Pointer'lar tanımlandığı anda nullptr ile ilklendirilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1375, .topicId = 55,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint* p = nullptr;\nint deger = *p;\nstd::cout << deger;\n\nProgramcı p'yi hiç geçerli bir adrese bağlamadan dereference etmiş; bu tanımsız davranıştır. p'yi önce geçerli bir x değişkenine (zaten tanımlı olduğunu varsayarak) bağlayan düzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, dereference edilmeden önce geçerli bir adrese bağlanmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1376, .topicId = 55,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, nullptr kontrolü yapan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"if (p == nullptr) {\n        std::cout << \"bos\";\n    }\n    return 0;\n}", "int* p = nullptr;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), p tanımı (2), if kontrolü ve kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1377, .topicId = 55,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir pointer'ı nullptr ile ilklendirin, ardından nullptr olup olmadığını if ile kontrol edip uygun bir mesaj yazdırın.",
        .acceptedAnswers = {"nullptr", "if", "cout"},
        .explanation = "Pointer nullptr ile ilklendirilmeli ve if ile kontrol edilmelidir.",
        .baseXp = 40,
    });

    // Topic 56: Pointer ile dizi dolaşma
    questions.push_back(Question{
        .id = 1378, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizi adı, kullanıldığı çoğu bağlamda neye dönüşür (decay olur)?",
        .options = {"İlk elemanının adresine", "Son elemanının adresine", "Elemanların toplamına", "Dizinin boyutuna"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir dizi adı, ilk elemanının adresine dönüşür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1379, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int dizi[3] = {10, 20, 30};\nint* p = dizi;\nstd::cout << *p;\nEkrana ne yazdırılır?",
        .options = {"10", "20", "30", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p, dizinin ilk elemanını (10) gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1380, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int dizi[3] = {10, 20, 30};\nint* p = dizi;\n++p;\nstd::cout << *p;\nEkrana ne yazdırılır?",
        .options = {"20", "10", "30", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "++p, p'yi bir sonraki elemana (20) ilerletir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1381, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[5];\nint* p = dizi;\np + 1 ifadesi, p'yi kaç byte ileri taşır (int 4 byte varsayılırsa)?",
        .options = {"4 byte", "1 byte", "5 byte", "8 byte"},
        .acceptedAnswers = {"a"},
        .explanation = "Pointer aritmetiği, gösterilen türün boyutu (sizeof) kadar ilerler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1382, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {1, 2, 3};\nint* p = dizi;\np += 2;\nstd::cout << *p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"3", "2", "1", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p += 2, p'yi dizi[2]'ye (3) taşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1383, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {5, 10, 15};\nstd::cout << *(dizi + 1);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"10", "5", "15", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "dizi + 1, dizi[1]'i (10) gösterir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1384, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int dizi[4] = {1, 2, 3, 4};\nint* p = dizi;\nint toplam = 0;\nfor (int i = 0; i < 4; ++i) {\n    toplam += *p;\n    ++p;\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"10", "4", "24", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "1 + 2 + 3 + 4 = 10.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1385, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int dizi[3] = {7, 8, 9};\nint* p = dizi + 3;\nstd::cout << *p;\nBu kod ne yapar?",
        .options = {"Tanımsız davranış (dizinin sonunu geçen bir elemanı dereference eder)", "0 yazdırır", "9 yazdırır", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "dizi + 3, dizinin son elemanından (indeks 2) bir sonraki, geçersiz bir konumu dereference eder.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1386, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizi adı, kullanıldığı çoğu bağlamda ilk elemanının adresine dönüşür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: dizi adı, decay olarak ilk elemanının adresine dönüşür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1387, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir int pointer'ı bir artırmak (++p), p'yi her zaman 1 byte ileri taşır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: p, gösterdiği türün boyutu (genellikle 4 byte) kadar ilerler.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1388, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "ptr++ ifadesi, pointer'ı gösterdiği türün boyutu (sizeof) kadar ileri taşır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1389, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir pointer, bir dizi üzerinde döngüyle (for/while) elemanları tek tek dolaşmak için kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1390, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir dizinin son elemanından sonraki adresi (dizi + n) hesaplamak (dereference etmeden) geçerlidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: bu adresi hesaplamak geçerlidir, sadece dereference etmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1391, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Dizinin son elemanından sonraki adresi (dizi + n) dereference etmek (* ile okumak) tanımsız davranıştır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1392, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizi adı, kullanıldığı çoğu bağlamda ilk elemanının _____ dönüşür (Türkçe kelime).",
        .acceptedAnswers = {"adresine"},
        .explanation = "Dizi adı, ilk elemanının adresine dönüşür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1393, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int dizi[3] = {1, 2, 3};\nint* p = dizi;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "p, dizinin ilk elemanını gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1394, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int dizi[3] = {1, 2, 3};\nint* p = dizi;\n++p;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "++p, p'yi bir sonraki elemana ilerletir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1395, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {1, 2, 3};\nstd::cout << *(dizi + 2);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "dizi + 2, dizi[2]'yi (3) gösterir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1396, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "ptr + 1, ptr'yi 1 byte değil, gösterdiği türün _____ (sizeof) kadar ileri taşır (Türkçe kelime, İngilizce köküyle de kabul edilir).",
        .acceptedAnswers = {"boyutu", "sizeof"},
        .explanation = "Pointer aritmetiği, elemanın boyutu (sizeof) kadar ilerler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1397, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[4] = {2, 4, 6, 8};\nint* p = dizi + 3;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "dizi + 3, dizi[3]'ü (8) gösterir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1398, .topicId = 56,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {10, 20, 30};\n_____\nstd::cout << *p;\ndizi'nin ilk elemanını gösteren p adlı bir pointer tanımlayan satırı yazın.",
        .acceptedAnswers = {"int* p = dizi;"},
        .explanation = "p, dizi adının decay olduğu ilk eleman adresiyle ilklendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1399, .topicId = 56,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {1, 2, 3};\nint* p = dizi;\n_____\nstd::cout << *p;\np'yi bir sonraki elemana ilerleten satırı yazın.",
        .acceptedAnswers = {"++p;"},
        .explanation = "++p, p'yi bir sonraki elemana taşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1400, .topicId = 56,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {4, 5, 6};\nint* p = dizi;\nstd::cout << *p << *(p + 1) << *(p + 2);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"456"},
        .explanation = "Sırasıyla dizi[0], dizi[1], dizi[2]: 4, 5, 6.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1401, .topicId = 56,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int dizi[4] = {1, 2, 3, 4};\nint* p = dizi;\nfor (int i = 0; i < 4; ++i) {\n    *p = *p * 2;\n    ++p;\n}\nfor (int i = 0; i < 4; ++i) {\n    std::cout << dizi[i];\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2468"},
        .explanation = "Her eleman pointer üzerinden 2 ile çarpılır: 2, 4, 6, 8.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1402, .topicId = 56,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint dizi[3] = {1, 2, 3};\nint* p = dizi;\nfor (int i = 0; i <= 3; ++i) {\n    std::cout << *p;\n    ++p;\n}\n\nBu kod, döngü koşulunun (i <= 3) dizinin sınırını (3 eleman, indeks 0-2) bir eleman aşmasına izin verdiği için, son turda dizinin dışına taşan bir bellek konumunu dereference eder (tanımsız davranış). Hatalı döngü koşulunu düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int i = 0; i < 3; ++i) {"},
        .explanation = "Döngü, dizinin sınırını aşmayacak şekilde (i < 3) çalışmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1403, .topicId = 56,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint dizi[3] = {1, 2, 3};\nint* p = dizi + 3;\nstd::cout << *p;\n\nBu kod, dizinin son elemanından (indeks 2) bir sonraki konumu (dizi + 3, dizinin dışı) dereference ettiği için tanımsız davranışa yol açar. p'yi dizinin son geçerli elemanını (indeks 2) gösterecek şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int* p = dizi + 2;"},
        .explanation = "p, dizinin son geçerli elemanını (indeks 2) göstermelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1404, .topicId = 56,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint dizi[3] = {5, 10, 15};\nint* p = dizi;\nfor (int i = 0; i < 4; ++i) {\n    std::cout << *p << \" \";\n    ++p;\n}\n\nDöngü, dizinin 3 elemanı olmasına rağmen 4 kez çalışıyor; bu, dizinin dışına taşar. Döngü koşulunu düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int i = 0; i < 3; ++i) {"},
        .explanation = "Döngü, dizinin gerçek eleman sayısı (3) kadar çalışmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1405, .topicId = 56,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, pointer ile dizi dolaşan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* p = dizi;\n    std::cout << *p << *(p + 1);\n    return 0;\n}", "int dizi[2] = {3, 6};", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), dizi tanımı (2), pointer ve yazdırma (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1406, .topicId = 56,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int dizisi tanımlayın, bir pointer ile ilk elemanına erişip, döngüyle tüm elemanları pointer aritmetiği kullanarak (indeks yerine ++p ile) ekrana yazdırın.",
        .acceptedAnswers = {"int*", "++", "cout"},
        .explanation = "Pointer, döngü içinde ++p ile ilerletilerek tüm elemanlar yazdırılmalıdır.",
        .baseXp = 40,
    });

    // Topic 57: new
    questions.push_back(Question{
        .id = 1407, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "new operatörü ne yapar?",
        .options = {"Bellekte dinamik olarak (heap üzerinde) yer ayırır", "Bir değişkeni siler", "Bir referans oluşturur", "Bir dosya açar"},
        .acceptedAnswers = {"a"},
        .explanation = "new, çalışma zamanında heap üzerinde dinamik olarak yer ayırır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1408, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int* p = new int(5);\nstd::cout << *p;\ndelete p;\nEkrana ne yazdırılır?",
        .options = {"5", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "new int(5), ayrılan belleği 5 ile ilklendirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1409, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "new int(5) ifadesi ne döndürür?",
        .options = {"Ayrılan belleğin adresini tutan bir int*", "Doğrudan 5 değerini", "Bir referans", "Bir string"},
        .acceptedAnswers = {"a"},
        .explanation = "new, ayrılan yerin adresini bir pointer olarak döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1410, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "new ile ayrılan bellek ne zamana kadar ayrılmış kalır?",
        .options = {"delete ile serbest bırakılana ya da program sonlanana kadar", "Fonksiyon bitene kadar (otomatik olarak)", "Bir sonraki new çağrısına kadar", "1 saniye boyunca"},
        .acceptedAnswers = {"a"},
        .explanation = "Dinamik bellek, açıkça serbest bırakılana ya da program sonlanana kadar ayrılmış kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1411, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(10);\n*p = *p + 5;\nstd::cout << *p;\ndelete p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"15", "10", "5", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "10 + 5 = 15.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1412, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "new ile ayrılan bir bellek, karşılık gelen delete çağrılmadan unutulursa ne olur?",
        .options = {"Bellek sızıntısı (memory leak) oluşur, program çökmez", "Program hemen çöker", "Derleyici hata verir", "Bellek otomatik olarak serbest bırakılır"},
        .acceptedAnswers = {"a"},
        .explanation = "delete edilmeyen new belleği bir sızıntıya yol açar; program bundan dolayı çökmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1413, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p1 = new int(1);\nint* p2 = new int(2);\nstd::cout << (p1 == p2);\ndelete p1;\ndelete p2;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"0", "1", "Belirsiz", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "İki ayrı new çağrısı farklı bellek adresleri döndürür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1414, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p = new int(7);\nint* q = p;\n*q = 20;\nstd::cout << *p;\ndelete p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"20", "7", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "q = p, aynı adresi kopyalar; *q = 20 aynı belleği değiştirir, *p de artık 20'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1415, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "new operatörü, bellekte çalışma zamanında (heap üzerinde) dinamik olarak yer ayırır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1416, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "new ile ayrılan bellek, program tarafından otomatik olarak serbest bırakılır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: programcı delete ile serbest bırakmalıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1417, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "new int(5) ifadesi, ayrılan int'i 5 değeriyle ilklendirir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1418, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "new ile ayrılan bir bellek unutulursa (delete edilmezse) program hemen çöker.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: bir bellek sızıntısı oluşur ama program çalışmaya devam eder.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1419, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "new, ayrılan yerin adresini bir pointer olarak döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1420, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki ayrı new int(...) çağrısı, her zaman aynı adresi döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: her çağrı ayrı bir bellek bloğu ayırır, farklı adresler döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1421, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bellekte dinamik olarak yer ayırmak için _____ operatörü kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"new"},
        .explanation = "new operatörü dinamik bellek ayırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1422, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int* p = new int(8);\nstd::cout << *p;\ndelete p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "new int(8), ayrılan belleği 8 ile ilklendirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1423, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "new ile ayrılan bellek, delete ile serbest bırakılana kadar veya program _____ kadar ayrılmış kalır (Türkçe kelime).",
        .acceptedAnswers = {"sonlanana"},
        .explanation = "Bellek, delete edilene ya da program sonlanana kadar ayrılmış kalır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1424, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(10);\n*p = *p * 2;\nstd::cout << *p;\ndelete p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"20"},
        .explanation = "10 * 2 = 20.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1425, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "new ile ayrılan bir bellek karşılık gelen delete olmadan unutulursa buna bellek _____ denir (Türkçe kelime).",
        .acceptedAnswers = {"sızıntısı"},
        .explanation = "Bu duruma bellek sızıntısı (memory leak) denir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1426, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "new int(5) ifadesinin döndürdüğü değerin türü _____ olur (İngilizce, bir kelime + sembol).",
        .acceptedAnswers = {"int*"},
        .explanation = "new int(5), int* türünde bir değer döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1427, .topicId = 57,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << *p;\ndelete p;\n5 değeriyle ilklendirilmiş bir int için dinamik bellek ayırıp p'ye atayan satırı yazın.",
        .acceptedAnswers = {"int* p = new int(5);"},
        .explanation = "new int(5), p'ye atanan ayrılmış bir int adresi döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1428, .topicId = 57,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(3);\n_____\nstd::cout << *p;\np'nin gösterdiği değeri 3 katına çıkaran satırı yazın.",
        .acceptedAnswers = {"*p = *p * 3;"},
        .explanation = "*p = *p * 3, ayrılan belleği 3 katına çıkarır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1429, .topicId = 57,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(4);\n*p += 6;\nstd::cout << *p;\ndelete p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "4 + 6 = 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1430, .topicId = 57,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int* p = new int(2);\nint* q = new int(2);\nstd::cout << (*p == *q) << (p == q);\ndelete p;\ndelete q;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "*p == *q true (değerler eşit); p == q false (farklı bellek blokları).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1431, .topicId = 57,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nvoid fonksiyon() {\n    int* p = new int(5);\n    std::cout << *p;\n}\n\nBu fonksiyon, new ile ayrılan belleği hiçbir zaman delete etmiyor; fonksiyon her çağrıldığında bir bellek sızıntısı oluşur (program çökmez ama bellek asla geri kazanılmaz). Fonksiyonun sonuna eksik olan satırı ekleyin.",
        .acceptedAnswers = {"delete p;"},
        .explanation = "new ile ayrılan her bellek, karşılık gelen bir delete ile serbest bırakılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1432, .topicId = 57,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p = new int(5)\nstd::cout << *p;\ndelete p;\n\nBu kod derlenmez çünkü new int(5) satırının sonunda noktalı virgül eksik. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int* p = new int(5);"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1433, .topicId = 57,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint* p = new int(9)\nstd::cout << *p;\ndelete p;\n\nProgramcı new int(9) satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"int* p = new int(9);"},
        .explanation = "Eksik noktalı virgül eklenmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1434, .topicId = 57,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, new ile bellek ayırıp kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* p = new int(7);", "std::cout << *p;\n    delete p;\n    return 0;\n}", "int main() {"},
        .acceptedAnswers = {"3 1 2"},
        .explanation = "main açılışı (3), new ile ayırma (1), yazdırma+delete+kapanış (2): sıra 3 1 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1435, .topicId = 57,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "new ile bir int için dinamik bellek ayırıp bir değerle ilklendirin, değerini ekrana yazdırın, ardından belleği delete ile serbest bırakın.",
        .acceptedAnswers = {"new", "delete", "cout"},
        .explanation = "Bellek new ile ayrılmalı, kullanılmalı ve delete ile serbest bırakılmalıdır.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `92/92 test(s) passed.` (unchanged — no existing test yet counts
these topics' questions).

- [ ] **Step 3: Commit**

```bash
git add src/QuestionsSection6.cpp
git commit -m "feat(content): add questions for topics 55-57 (ids 1349-1435)"
```

---

### Task 4: Questions for topics 58-60 (ids 1436-1522), test updates, and final integration

**Files:**
- Modify: `src/QuestionsSection6.cpp` (append the final `push_back`
  calls to `appendSection6Questions`)
- Modify: `tests/QuestionManagerTests.cpp` (add one new per-section
  minimum-count test)
- Modify: `docs/superpowers/roadmap.md` (mark Phase 17 complete)

**Interfaces:**
- Consumes: `appendSection6Questions(std::vector<Question>& questions)`
  in `src/QuestionsSection6.cpp` — append after Task 3's last id (1435),
  before the function's closing `}`. After this task, ids 1233-1522 are
  all present (10 topics x 29 questions) and the function is complete.

- [ ] **Step 1: Write topics 58-60's questions**

In `src/QuestionsSection6.cpp`, inside `appendSection6Questions`, add
these `push_back` calls right after the id-1435 block (before the
function's closing `}`):

```cpp
    // Topic 58: delete
    questions.push_back(Question{
        .id = 1436, .topicId = 58,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "delete operatörü ne yapar?",
        .options = {"new ile ayrılmış belleği serbest bırakır", "Bir değişken tanımlar", "Bir dosya siler", "Bir referans oluşturur"},
        .acceptedAnswers = {"a"},
        .explanation = "delete, new ile ayrılan belleği serbest bırakır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1437, .topicId = 58,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int* p = new int(5);\ndelete p;\nBu satırdan sonra p'nin durumu nedir?",
        .options = {"p artık sarkan (dangling) bir pointerdır", "p otomatik olarak nullptr olur", "p'nin gösterdiği bellek hala geçerlidir", "Derleme hatası oluşur"},
        .acceptedAnswers = {"a"},
        .explanation = "delete'ten sonra pointer, artık geçersiz bir belleği gösteren dangling bir pointer haline gelir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1438, .topicId = 58,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Her new çağrısının karşılığında kaç tane delete çağrısı olmalıdır?",
        .options = {"Tam olarak bir tane", "İki tane", "Hiç gerekmez", "new sayısının iki katı"},
        .acceptedAnswers = {"a"},
        .explanation = "Her new'e karşılık tam olarak bir delete gerekir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1439, .topicId = 58,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(5);\ndelete p;\ndelete p;\nBu kod ne olur (ikinci delete)?",
        .options = {"Tanımsız davranış (double delete)", "Güvenle çalışır, hiçbir sorun çıkmaz", "Derleme hatası verir", "Otomatik olarak yok sayılır"},
        .acceptedAnswers = {"a"},
        .explanation = "Aynı pointer'ı iki kez delete etmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1440, .topicId = 58,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "delete p; çağrıldıktan sonra p'yi nullptr yapmak (p = nullptr;) zorunlu mudur?",
        .options = {"Zorunlu değildir ama yanlışlıkla tekrar kullanılmasını önlemek için iyi bir alışkanlıktır", "Zorunludur, aksi halde derleme hatası olur", "delete otomatik olarak p'yi nullptr yapar", "Hiçbir zaman yapılmamalıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr yapmak zorunlu değildir ama iyi bir güvenlik alışkanlığıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1441, .topicId = 58,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(3);\nint* q = p;\ndelete p;\nstd::cout << *q;\nBu kod ne olur?",
        .options = {"Tanımsız davranış (q artık sarkan bir pointerdır)", "3 yazdırır, güvenlidir", "0 yazdırır", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "q, p ile aynı belleği gösterdiğinden, p delete edildiğinde q de sarkan hale gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1442, .topicId = 58,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p = new int(5);\np = new int(10);\nstd::cout << *p;\nBu kodda bir sorun var mı?",
        .options = {"Evet, ilk ayrılan bellek (5 değerli) hiç delete edilmeden kaybedildi (bellek sızıntısı); *p yine de 10 yazdırır", "Hayır, hiçbir sorun yok", "Derleme hatası verir", "Çalışma zamanında çöker"},
        .acceptedAnswers = {"a"},
        .explanation = "p, ilk ayrılan belleği delete etmeden yeniden atanmış; bu bellek artık asla serbest bırakılamaz (sızıntı).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1443, .topicId = 58,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p = new int(1);\ndelete p;\np = new int(2);\nstd::cout << *p;\ndelete p;\nBu kod geçerli midir?",
        .options = {"Evet, geçerlidir; her new'e karşılık bir delete vardır ve p kullanılmadan önce yeniden atanmıştır", "Hayır, p ikinci new'den önce nullptr yapılmalıydı", "Hayır, bu double delete'tir", "Hayır, bellek sızıntısına yol açar"},
        .acceptedAnswers = {"a"},
        .explanation = "İlk bellek düzgünce delete edilip p yeni bir belleğe atanmış; her new'in kendi delete'i vardır, sorun yoktur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1444, .topicId = 58,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "delete operatörü, new ile ayrılmış belleği serbest bırakır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1445, .topicId = 58,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "delete çağrıldıktan sonra pointer otomatik olarak nullptr olur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: pointer, açıkça nullptr yapılmadıkça dangling kalır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1446, .topicId = 58,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Aynı pointer'ı iki kez delete etmek (double delete) tanımsız davranıştır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1447, .topicId = 58,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "delete'ten sonra pointer'ı tekrar dereference etmek güvenlidir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: delete'ten sonraki dereference tanımsız davranıştır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1448, .topicId = 58,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Her new çağrısının karşılığında tam olarak bir delete çağrısı olmalıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1449, .topicId = 58,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "delete p; çağrıldıktan sonra p'yi nullptr yapmak, yanlışlıkla tekrar kullanmayı önlemek için iyi bir alışkanlıktır (ama zorunlu değildir).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1450, .topicId = 58,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "new ile ayrılmış belleği serbest bırakmak için _____ operatörü kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"delete"},
        .explanation = "delete operatörü belleği serbest bırakır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1451, .topicId = 58,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "delete p; çağrıldıktan sonra p, _____ (dangling) bir pointer haline gelir (İngilizce kelime).",
        .acceptedAnswers = {"dangling"},
        .explanation = "Silinen belleği gösteren bir pointer'a dangling (sarkan) pointer denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1452, .topicId = 58,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Aynı pointer'ı iki kez delete etmeye _____ delete denir (İngilizce iki kelime, örn. 'double delete').",
        .acceptedAnswers = {"double delete"},
        .explanation = "Bu hataya double delete denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1453, .topicId = 58,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(4);\ndelete p;\nBu satırdan sonra p'yi tekrar dereference etmek _____ davranıştır (İngilizce iki kelime).",
        .acceptedAnswers = {"undefined behavior"},
        .explanation = "delete'ten sonraki dereference undefined behavior'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1454, .topicId = 58,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "delete'ten sonra pointer'ı _____ yapmak (bir kelime, İngilizce), yanlışlıkla tekrar kullanılmasını önler.",
        .acceptedAnswers = {"nullptr"},
        .explanation = "nullptr yapmak, yanlışlıkla tekrar kullanmayı önler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1455, .topicId = 58,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(2);\nint* q = p;\ndelete p;\nBu satırdan sonra q da _____ bir pointer haline gelir (İngilizce kelime, aynı bellek serbest bırakıldığı için).",
        .acceptedAnswers = {"dangling"},
        .explanation = "q, p ile aynı belleği gösterdiğinden o da dangling hale gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1456, .topicId = 58,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(6);\nstd::cout << *p;\n_____\np'nin gösterdiği belleği serbest bırakan satırı yazın.",
        .acceptedAnswers = {"delete p;"},
        .explanation = "delete p, ayrılan belleği serbest bırakır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1457, .topicId = 58,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(6);\ndelete p;\n_____\np'yi, silindikten sonra yanlışlıkla tekrar kullanılmasını önlemek için boşa ayarlayan satırı yazın.",
        .acceptedAnswers = {"p = nullptr;"},
        .explanation = "p, silindikten sonra nullptr yapılarak güvenli hale getirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1458, .topicId = 58,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(15);\nstd::cout << *p;\ndelete p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"15"},
        .explanation = "new int(15), belleği 15 ile ilklendirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1459, .topicId = 58,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int* p = new int(3);\np = new int(9);\nstd::cout << *p;\ndelete p;\nYukarıdaki kodun ekran çıktısı nedir? (İlk ayrılan bellek delete edilmeden yeniden atandığı için bir sızıntı oluşur, ama *p'nin değeri buna bağlı değildir.)",
        .acceptedAnswers = {"9"},
        .explanation = "p, ikinci new ile 9 değerli belleği gösterir; ilk bellek sızar ama *p 9'dur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1460, .topicId = 58,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nint* p = new int(5);\ndelete p;\ndelete p;\n\nBu kod, aynı pointer'ı iki kez delete ettiği (double delete) için tanımsız davranışa yol açar. İkinci gereksiz delete satırını kaldırarak, kalması gereken tek delete satırını yazın.",
        .acceptedAnswers = {"delete p;"},
        .explanation = "Her new'e karşılık sadece bir delete olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1461, .topicId = 58,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* dizi = new int[5];\n// ... dizi kullanılır ...\ndelete dizi;\n\nBu kod, new[] ile ayrılan bir diziyi köşeli parantezsiz delete ile sildiği için tanımsız davranışa yol açar. Hatalı satırı, doğru şekilde (delete[] ile) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"delete[] dizi;"},
        .explanation = "new[] ile ayrılan bir dizi mutlaka delete[] ile silinmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1462, .topicId = 58,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint* p = new int(7)\ndelete p;\n\nProgramcı new int(7) satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int* p = new int(7);"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1463, .topicId = 58,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, new ile ayrılan belleği delete eden geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* p = new int(5);", "std::cout << *p;\n    delete p;\n    return 0;\n}", "int main() {"},
        .acceptedAnswers = {"3 1 2"},
        .explanation = "main açılışı (3), new ile ayırma (1), yazdırma+delete+kapanış (2): sıra 3 1 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1464, .topicId = 58,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "new ile bir int için bellek ayırıp değerini yazdırın, ardından delete ile belleği serbest bırakıp p'yi nullptr yapın.",
        .acceptedAnswers = {"new", "delete", "nullptr"},
        .explanation = "Bellek ayrılmalı, kullanılmalı, delete edilmeli ve p nullptr yapılmalıdır.",
        .baseXp = 40,
    });

    // Topic 59: Dinamik dizi
    questions.push_back(Question{
        .id = 1465, .topicId = 59,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Çalışma zamanında boyutu belirlenen bir dizi ayırmak için hangi operatör kullanılır?",
        .options = {"new[]", "new", "delete[]", "array[]"},
        .acceptedAnswers = {"a"},
        .explanation = "new[], dinamik bir dizi ayırır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1466, .topicId = 59,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int* dizi = new int[5];\nBu dizi kaç elemanlıdır?",
        .options = {"5", "1", "0", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "new int[5], 5 elemanlık bir dizi ayırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1467, .topicId = 59,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "new[] ile ayrılan bir dizi nasıl serbest bırakılır?",
        .options = {"delete[] ile", "delete ile (köşeli parantezsiz)", "free() ile", "Otomatik olarak serbest bırakılır"},
        .acceptedAnswers = {"a"},
        .explanation = "new[] ile ayrılan bir dizi mutlaka delete[] ile serbest bırakılmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1468, .topicId = 59,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* dizi = new int[3];\ndelete dizi;\nBu kod ne olur (köşeli parantezsiz delete)?",
        .options = {"Tanımsız davranış", "Güvenle çalışır", "Derleme hatası", "Sadece ilk elemanı siler"},
        .acceptedAnswers = {"a"},
        .explanation = "new[] ile ayrılan bir diziyi delete (köşeli parantezsiz) ile silmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1469, .topicId = 59,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* dizi = new int[3];\ndizi[0] = 10;\ndizi[1] = 20;\ndizi[2] = 30;\nstd::cout << dizi[1];\ndelete[] dizi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"20", "10", "30", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "dizi[1] = 20.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1470, .topicId = 59,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Dinamik olarak ayrılan bir dizinin boyutu, program çalışırken (compile-time değil runtime'da) belirlenebilir mi?",
        .options = {"Evet, new[] ile boyut bir değişkenden okunabilir", "Hayır, boyut her zaman derleme zamanında sabit olmalıdır", "Sadece std::vector ile mümkündür", "Hayır, C++ dinamik diziyi desteklemez"},
        .acceptedAnswers = {"a"},
        .explanation = "new[]'in en büyük avantajı, boyutun çalışma zamanında belirlenebilmesidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1471, .topicId = 59,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int n = 4;\nint* dizi = new int[n];\nfor (int i = 0; i < n; ++i) {\n    dizi[i] = i * i;\n}\nint toplam = 0;\nfor (int i = 0; i < n; ++i) {\n    toplam += dizi[i];\n}\nstd::cout << toplam;\ndelete[] dizi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"14", "16", "10", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Kareler: 0, 1, 4, 9; toplam = 14.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1472, .topicId = 59,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* dizi = new int[3];\ndizi[0] = 1;\ndizi[1] = 2;\ndizi[2] = 3;\nint* p = dizi;\n*p = 100;\nstd::cout << dizi[0];\ndelete[] dizi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"100", "1", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p, dizi'nin ilk elemanını (decay ile) gösterir; *p = 100, dizi[0]'ı da 100 yapar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1473, .topicId = 59,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "new[] operatörü, çalışma zamanında boyutu belirlenen bir dizi ayırır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1474, .topicId = 59,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "new[] ile ayrılan bir dizi, sıradan delete (köşeli parantezsiz) ile güvenle silinebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: mutlaka delete[] kullanılmalıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1475, .topicId = 59,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "new[] ile ayrılan bir dizinin boyutu, çalışma zamanında bir değişkenden okunabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1476, .topicId = 59,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Dinamik dizinin elemanlarına, sıradan dizilerde olduğu gibi [] operatörüyle erişilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1477, .topicId = 59,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "new[] ile ayrılan bir dizi delete[] edilmezse bellek sızıntısı oluşur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1478, .topicId = 59,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::vector, çoğu durumda new[]/delete[] kullanımına göre daha güvenli bir alternatiftir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: std::vector, manuel bellek yönetimi hatalarını önler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1479, .topicId = 59,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Dinamik bir dizi ayırmak için new _____ (köşeli parantez ekleyerek) yazılır (bir sembol çifti).",
        .acceptedAnswers = {"[]"},
        .explanation = "new tür[boyut] şeklinde köşeli parantez kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1480, .topicId = 59,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int* dizi = new int[3];\ndizi[0] = 5;\nstd::cout << dizi[0];\ndelete[] dizi;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "dizi[0] = 5 atandığından çıktı 5'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1481, .topicId = 59,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "new[] ile ayrılan bir dizi, _____ ile (köşeli parantezli haliyle) serbest bırakılmalıdır (İngilizce kelime + sembol).",
        .acceptedAnswers = {"delete[]"},
        .explanation = "delete[], new[] ile eşleşen serbest bırakma operatörüdür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1482, .topicId = 59,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int n = 3;\nint* dizi = new int[n];\nfor (int i = 0; i < n; ++i) { dizi[i] = i + 1; }\nstd::cout << dizi[2];\ndelete[] dizi;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "dizi[2] = 2+1 = 3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1483, .topicId = 59,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "new[] ile ayrılan bir diziyi köşeli parantezsiz delete ile silmek _____ davranıştır (İngilizce iki kelime).",
        .acceptedAnswers = {"undefined behavior"},
        .explanation = "new[]/delete uyuşmazlığı undefined behavior'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1484, .topicId = 59,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Modern C++'ta, manuel new[]/delete[] yerine sıklıkla _____ tercih edilir (bir kelime, İngilizce, std:: olmadan).",
        .acceptedAnswers = {"vector"},
        .explanation = "std::vector, manuel bellek yönetimine daha güvenli bir alternatiftir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1485, .topicId = 59,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int n = 4;\n_____\nfor (int i = 0; i < n; ++i) { dizi[i] = 0; }\nn elemanlık dinamik bir int dizisi ayırıp dizi'ye atayan satırı yazın.",
        .acceptedAnswers = {"int* dizi = new int[n];"},
        .explanation = "new int[n], n elemanlık bir dizi ayırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1486, .topicId = 59,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int* dizi = new int[5];\n_____\nDinamik diziyi serbest bırakan satırı yazın.",
        .acceptedAnswers = {"delete[] dizi;"},
        .explanation = "delete[], dinamik diziyi serbest bırakır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1487, .topicId = 59,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int* dizi = new int[3];\ndizi[0] = 7;\ndizi[1] = 8;\ndizi[2] = 9;\nstd::cout << dizi[0] << dizi[1] << dizi[2];\ndelete[] dizi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"789"},
        .explanation = "Sırasıyla 7, 8, 9 yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1488, .topicId = 59,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int n = 3;\nint* dizi = new int[n];\nfor (int i = 0; i < n; ++i) { dizi[i] = (i + 1) * 10; }\nint toplam = 0;\nfor (int i = 0; i < n; ++i) { toplam += dizi[i]; }\nstd::cout << toplam;\ndelete[] dizi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"60"},
        .explanation = "10 + 20 + 30 = 60.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1489, .topicId = 59,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* dizi = new int[5];\n// ... dizi kullanılır ...\ndelete dizi;\n\nBu kod, new[] ile ayrılan bir diziyi köşeli parantezsiz delete ile sildiği için tanımsız davranışa yol açar. Hatalı satırı, doğru şekilde (delete[] ile) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"delete[] dizi;"},
        .explanation = "new[] ile ayrılan bir dizi delete[] ile silinmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1490, .topicId = 59,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint n = 5;\nint* dizi = new int[n];\nfor (int i = 0; i <= n; ++i) {\n    dizi[i] = i;\n}\ndelete[] dizi;\n\nBu kod, döngü koşulunun (i <= n) dizinin sınırını (n eleman, indeks 0'dan n-1'e) bir eleman aşmasına izin verdiği için, son turda dizinin dışına yazma yapar (tanımsız davranış). Hatalı döngü koşulunu düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int i = 0; i < n; ++i) {"},
        .explanation = "Döngü, dizinin sınırını aşmayacak şekilde (i < n) çalışmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1491, .topicId = 59,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint* dizi = new int[4];\nfor (int i = 0; i < 4; ++i) {\n    dizi[i] = i;\n}\ndelete dizi;\n\nProgramcı new[] ile ayrılan diziyi köşeli parantezsiz delete ile silmiş; bu tanımsız davranıştır. Düzeltilmiş delete satırını yazın.",
        .acceptedAnswers = {"delete[] dizi;"},
        .explanation = "new[] için mutlaka delete[] kullanılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1492, .topicId = 59,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, dinamik bir dizi oluşturup kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* dizi = new int[3];\n    dizi[0] = 1;", "std::cout << dizi[0];\n    delete[] dizi;\n    return 0;\n}", "int main() {"},
        .acceptedAnswers = {"3 1 2"},
        .explanation = "main açılışı (3), dizi ayırma (1), yazdırma+delete[]+kapanış (2): sıra 3 1 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1493, .topicId = 59,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Çalışma zamanında boyutu bir değişkenden okunan dinamik bir int dizisi oluşturun, elemanlarını doldurup ekrana yazdırın, ardından delete[] ile serbest bırakın.",
        .acceptedAnswers = {"new", "[]", "delete[]", "cout"},
        .explanation = "Dizi new[] ile ayrılmalı, doldurulup yazdırılmalı ve delete[] ile serbest bırakılmalıdır.",
        .baseXp = 40,
    });

    // Topic 60: Referans değişkeni
    questions.push_back(Question{
        .id = 1494, .topicId = 60,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir referans değişkeni nasıl tanımlanır?",
        .options = {"tür& isim = degisken;", "tür* isim = degisken;", "ref isim = degisken;", "tür isim = &degisken;"},
        .acceptedAnswers = {"a"},
        .explanation = "Referans tanımı tür& isim = degisken; şeklinde yapılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1495, .topicId = 60,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint& r = x;\nr = 10;\nstd::cout << x;\nEkrana ne yazdırılır?",
        .options = {"10", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "r, x'in kendisidir; r'yi değiştirmek doğrudan x'i değiştirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1496, .topicId = 60,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int& r; (ilklendirmeden) tanımlamak ne olur?",
        .options = {"Derleme hatası", "r, nullptr olur", "r, rastgele bir değeri gösterir", "Geçerlidir, r daha sonra ilklendirilebilir"},
        .acceptedAnswers = {"a"},
        .explanation = "Referanslar tanımlandığı anda ilklendirilmelidir; aksi halde derleme hatası oluşur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1497, .topicId = 60,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5, y = 10;\nint& r = x;\nr = y;\nstd::cout << x << \" \" << y;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"10 10\"", "\"5 10\"", "\"10 5\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "r = y, r'yi y'ye yeniden bağlamaz; sadece y'nin değerini x'e (r üzerinden) kopyalar. x=10, y değişmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1498, .topicId = 60,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir referans, pointer'ların aksine hangi özelliğe sahip DEĞİLDİR?",
        .options = {"Yeniden bağlanabilme (rebind edilebilme)", "Bir değişkene erişim sağlama", "Değer okuma", "Değer yazma"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir referans, tanımlandıktan sonra başka bir değişkeni gösterecek şekilde yeniden bağlanamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1499, .topicId = 60,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir pointer null olabilirken, bir referans null olabilir mi?",
        .options = {"Hayır, bir referans asla null olamaz", "Evet, nullptr ile ilklendirilebilir", "Evet ama sadece const referanslar null olabilir", "Sadece pointer referanslar null olabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir referans, her zaman geçerli bir değişkene bağlı olmalıdır; asla null olamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1500, .topicId = 60,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1;\nint& r = a;\nint b = 2;\nr = b;\nstd::cout << (&r == &a) << (&r == &b);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"10\"", "\"01\"", "\"11\"", "\"00\""},
        .acceptedAnswers = {"a"},
        .explanation = "r, hep a'ya bağlı kalır (rebind olmaz); &r her zaman &a'ya eşittir, &b'ye asla eşit olmaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1501, .topicId = 60,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int x = 5;\nint& r1 = x;\nint& r2 = r1;\nr2 = 20;\nstd::cout << x << \" \" << r1;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"20 20\"", "\"5 5\"", "\"20 5\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "r2, r1'e (dolayısıyla x'e) bağlıdır; r2 = 20, x'i de r1'i de 20 yapar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1502, .topicId = 60,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir referans, var olan bir değişkene ikinci bir isim (takma ad) tanımlamanın yoludur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1503, .topicId = 60,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir referans, tanımlandıktan sonra başka bir değişkeni gösterecek şekilde yeniden bağlanabilir (rebind edilebilir).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: bir referans, bağlandığı değişkenden asla ayrılamaz.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1504, .topicId = 60,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int& r; (ilklendirmeden) tanımlamak derleme hatasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1505, .topicId = 60,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir referans, bir pointer gibi null olabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: bir referans asla null olamaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1506, .topicId = 60,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int& r = x; tanımından sonra r = y; yazmak, r'yi y'ye yeniden bağlar (rebind eder).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: r = y, sadece y'nin değerini x'e (r üzerinden) kopyalar; rebind olmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1507, .topicId = 60,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir referans, bağlı olduğu değişkenle aynı bellek adresini paylaşır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1508, .topicId = 60,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir referans, var olan bir değişkene ikinci bir _____ tanımlamanın yoludur (Türkçe kelime).",
        .acceptedAnswers = {"ad", "isim"},
        .explanation = "Referans, değişkene ikinci bir ad (takma ad) tanımlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1509, .topicId = 60,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint& r = x;\nr = 20;\nstd::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"20"},
        .explanation = "r üzerinden yapılan değişiklik doğrudan x'i etkiler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1510, .topicId = 60,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int& r; (ilklendirmeden) tanımlamak _____ hatasıdır (Türkçe kelime).",
        .acceptedAnswers = {"derleme"},
        .explanation = "Bu bir derleme hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1511, .topicId = 60,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5, y = 10;\nint& r = x;\nr = y;\nstd::cout << x;\nEkran çıktısı _____ olur (r, y'ye yeniden bağlanmadığı, sadece y'nin değerini x'e kopyaladığı için).",
        .acceptedAnswers = {"10"},
        .explanation = "r = y, y'nin değerini x'e kopyalar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1512, .topicId = 60,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir referans, bir pointer'ın aksine asla _____ olamaz (İngilizce kelime).",
        .acceptedAnswers = {"null"},
        .explanation = "Bir referans her zaman geçerli bir değişkene bağlıdır, asla null olamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1513, .topicId = 60,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir referans, tanımlandığı andan itibaren başka bir değişkeni göstermeye asla _____ (bir kelime, Türkçe fiil, 'geçemez' anlamında).",
        .acceptedAnswers = {"geçemez", "gecemez"},
        .explanation = "Referanslar rebind edilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1514, .topicId = 60,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 25;\n_____\nr = 100;\nstd::cout << sayi;\nsayi'ye bağlı bir referans tanımlayan satırı yazın.",
        .acceptedAnswers = {"int& r = sayi;"},
        .explanation = "r, sayi'ye bağlı bir referans olarak tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1515, .topicId = 60,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 1;\nint& r = a;\n_____\nstd::cout << a;\nr üzerinden a'nın değerini 50 yapan satırı yazın.",
        .acceptedAnswers = {"r = 50;"},
        .explanation = "r üzerinden yapılan atama a'yı da değiştirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1516, .topicId = 60,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int x = 3;\nint& r = x;\nr += 7;\nstd::cout << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "3 + 7 = 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1517, .topicId = 60,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1, b = 2;\nint& r = a;\nr = b;\na = 99;\nstd::cout << a << \" \" << b << \" \" << r;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"99 2 99"},
        .explanation = "r hep a'ya bağlıdır; a = 99 sonrasında r de 99'u gösterir. b hiç değişmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1518, .topicId = 60,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint& r;\nint x = 5;\nr = x;\n\nBu kod derlenmez çünkü referanslar tanımlandığı anda ilklendirilmelidir; r, x tanımlanmadan önce (ilklendirmeden) bildirilmiş. Hatalı ilk satırı, r'yi x ile birlikte ilklendirecek şekilde düzeltilmiş haliyle yazın (x'in zaten tanımlı olduğunu varsayarak).",
        .acceptedAnswers = {"int& r = x;"},
        .explanation = "Referans, tanımlandığı anda bir değişkenle ilklendirilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1519, .topicId = 60,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint& r = 5;\nstd::cout << r;\n\nBu kod derlenmez çünkü normal (const olmayan) bir referans, bir literale (geçici bir değere) bağlanamaz. Hatalı satırı, const ekleyerek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"const int& r = 5;"},
        .explanation = "Sadece const referanslar geçici değerlere (literallere) bağlanabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1520, .topicId = 60,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint x = 10;\nint& r;\nr = x;\nstd::cout << r;\n\nProgramcı r'yi ilklendirmeden bildirmiş; referanslar tanımlandığı anda ilklendirilmelidir. Düzeltilmiş bildirim satırını yazın.",
        .acceptedAnswers = {"int& r = x;"},
        .explanation = "r, tanımlandığı anda x ile ilklendirilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1521, .topicId = 60,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir referans değişkeni tanımlayıp kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int& r = x;\n    r = 99;\n    std::cout << x;\n    return 0;\n}", "int x = 1;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), x tanımı (2), referans+atama+yazdırma+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1522, .topicId = 60,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int değişken tanımlayın, ona bağlı bir referans oluşturun, referans üzerinden değerini değiştirip orijinal değişkenin de değiştiğini ekrana yazdırarak gösterin.",
        .acceptedAnswers = {"int&", "cout"},
        .explanation = "Referans üzerinden yapılan değişiklik orijinal değişkeni de etkilemelidir.",
        .baseXp = 40,
    });
}
```

- [ ] **Step 2: Add a per-topic minimum-count test**

In `tests/QuestionManagerTests.cpp`, add this new test case right after
`QuestionManager_EveryTopicFortyOneToFiftyHasAtLeastTwentyNineQuestions`
(do not modify that existing test, and do not touch
`QuestionManager_NoDuplicateQuestionIds`, which already scans topics
1-100):

```cpp
TEST_CASE(QuestionManager_EveryTopicFiftyOneToSixtyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 51; topicId <= 60; ++topicId) {
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
Expected: `93/93 test(s) passed.` (92 from Task 1's end state + 1 new
test).

Run from `build/`: `ctest -C Debug --output-on-failure`
Expected: 100% pass.

- [ ] **Step 4: Manual verification — topic 57 end-to-end**

Run the app (`./build/Debug/CppMasterConsole.exe`), navigate to the
topic browser, choose Section 6, choose topic 57 ("new"):

1. Confirm the lesson text prints (matches the `explanation`/`syntax`/
   `exampleCode` written in Task 1) — proving `openTopic`'s content gate
   passes for topic 57 with zero `Application.cpp` changes.
2. Confirm "Konu testi başlıyor (29 soru)." prints.
3. Answer a few questions (any answers), then use `cikis` to return to
   the main menu.
4. Confirm the app returns to the main menu without crashing, and that
   partial XP is awarded.
5. Clean up: `rm -f data/*.txt`.

- [ ] **Step 5: Commit the question content and test changes**

```bash
git add src/QuestionsSection6.cpp tests/QuestionManagerTests.cpp
git commit -m "feat(content): add questions for topics 58-60 (ids 1436-1522), widen coverage tests"
```

- [ ] **Step 6: Update the roadmap**

In `docs/superpowers/roadmap.md`, add a new bullet for Phase 17 under
"Phase order," immediately after the Phase 16 entry, following the
EXACT format Phases 8-16 use
(`**Phase N — name: COMPLETE** (commits \`X..Y\`, ...)`), with the
commit range starting at this phase's spec commit (the commit for "Add
design spec for Bölüm 6 İçerik Genişletmesi (phase 17)") and ending at
this task's final content commit (from Step 5 above). Update the
"Status" section to say Phase 17 is complete and Phase 18 (Section 7
content) starts next.

Then commit:

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 17 complete in roadmap"
```

---

# Bölüm 9 İçerik Genişletmesi (Phase 20) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add full lesson content and a 290-question bank for Section 9
(topics 81-90, "STL konteynerleri"), following the identical
architecture used in Phases 13-19.

**Architecture:** One new `applySection9LessonContent` function in
`src/LessonContentSection9.cpp`, one new `appendSection9Questions`
function in `src/QuestionsSection9.cpp`, both wired into the existing
`LessonManager`/`QuestionManager` constructors after the Phase 19
calls.

**Tech Stack:** C++20, CMake, the project's own minimal test framework
(`TEST_CASE`/`CHECK`).

## Global Constraints

- Ids for this phase's questions: 2103-2392 (10 topics x 29 questions
  each), continuing directly from Phase 19's last id (2102).
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
  matching the 0-indexed `options` position — for THIS phase, unlike
  Sections 6-8, the correct option's position MUST be varied across
  a/b/c/d rather than always "a" (see the note on this below). `TrueFalse`
  has no `options` field; `{"1"}` = true, `{"2"}` = false.
  `OrderCode.acceptedAnswers` is 1-indexed positions space-separated,
  and MUST be verified (by actually assembling and compiling — and for
  any case involving execution order, running — the resulting program)
  to produce the correct, intended runtime behavior.
- **Known issue from Phases 17-19 (recorded in the ledger, not to be
  repeated here):** every MultipleChoice question in Sections 6, 7, and
  8 has `acceptedAnswers={"a"}` — the correct option is always listed
  first, making those 240 questions guessable without knowledge. This
  phase's MultipleChoice questions MUST vary the correct option's
  position across a/b/c/d (roughly evenly) so this phase does not add
  to that defect. This does not retroactively fix Sections 6-8 (out of
  scope for this phase; a rendering-layer shuffle fix or later targeted
  rewrite is the right remedy for those, tracked separately in the
  ledger).
- **`std::pair<T1,T2>`** exposes `.first`/`.second` only — there is no
  `operator[]` (a genuine compile error, confirmed: MSVC `C2676`).
- **`std::tuple<...>`** is accessed via `std::get<Index>(t)` where
  `Index` MUST be a compile-time constant — using a runtime variable as
  the index is a genuine compile error (confirmed: MSVC `C2672`).
- **`std::set<T>`** stores unique elements in SORTED (ascending) order
  regardless of insertion order; inserting a duplicate is a silent
  no-op. Any question tracing set iteration order MUST be compiled and
  RUN to confirm the printed order.
- **`std::map<K,V>`**: `operator[]` on a missing key INSERTS a new
  default-constructed entry as a side effect (this is the single most
  common real `std::map` bug); `.find(key)` does NOT insert. Keys are
  stored sorted. Any question tracing `.size()` before/after an
  `operator[]` read MUST be compiled and RUN to confirm the count.
- **`std::unordered_map<K,V>`** gives NO ordering guarantee (hash-table
  based) — the opposite of `map`'s sorted guarantee. No question may
  assert a SPECIFIC iteration order for `unordered_map` (implementation-
  defined); only deterministic operations (lookup by key, `.size()`)
  may be used as the traced/predicted value.
- **`std::stack<T>`** and **`std::queue<T>`** are container ADAPTORS
  with NO `begin()`/`end()` — a range-for over either is a genuine
  compile error (confirmed: MSVC `C3312`). `stack` is LIFO (`top()`,
  `push()`, `pop()`); `queue` is FIFO (`front()`, `back()`, `push()`,
  `pop()`).
- **`std::deque<T>`** supports `push_front`/`push_back`/`pop_front`/
  `pop_back`, random access, AND full `begin()`/`end()` iteration —
  contrast explicitly with `stack`/`queue`'s lack of iteration.
- **`std::priority_queue<T>`** is a max-heap BY DEFAULT: `top()` returns
  the LARGEST element, not the smallest (a common misconception). No
  iteration support (same adaptor family as `stack`/`queue`).
- **Iterators**: `begin()`/`end()` provide uniform traversal; a
  range-for loop is syntactic sugar for the equivalent explicit
  iterator loop and produces identical output. `end()` marks a
  past-the-end position and must never be dereferenced (undefined
  behavior, not a compile error).
- No `Application.cpp` changes are needed — `openTopic`/`runTopicQuiz`
  already activate any topic generically once it has non-empty lesson
  content and >= 1 question.

---

### Task 1: Section 9 lesson content

**Files:**
- Modify: `src/LessonContent.h` (add one new declaration)
- Create: `src/LessonContentSection9.cpp`
- Modify: `src/LessonManager.cpp` (include already present; add one call)
- Modify: `CMakeLists.txt` (add the new `.cpp` to the lib target sources,
  matching how `LessonContentSection8.cpp` is registered)
- Modify: `tests/LessonManagerTests.cpp` (widen two existing tests)

**Interfaces:**
- Produces: `void applySection9LessonContent(std::vector<Lesson>& lessons);`
  writing into `lessons[80]` through `lessons[89]` (topics 81-90).

- [ ] **Step 1: Add the new declaration**

In `src/LessonContent.h`, add this line after the existing
`applySection8LessonContent` declaration (do not remove that one):

```cpp
void applySection9LessonContent(std::vector<Lesson>& lessons);
```

- [ ] **Step 2: Write the lesson content**

Create `src/LessonContentSection9.cpp` with exactly this content:

```cpp
#include "LessonContent.h"

#include "Lesson.h"

void applySection9LessonContent(std::vector<Lesson>& lessons) {
    // Index 80 = topic id 81 (pair), index 89 = topic id 90 (Iterator)
    // — same positional convention as
    // applyIntroLessonContent/applySection2-8LessonContent.

    lessons[80].explanation =
        "std::pair<Tur1, Tur2>, iki farklı (veya aynı) türden değeri "
        "TEK bir nesnede birlikte tutan bir şablon (template) yapıdır. "
        "Elemanlarına .first ve .second üye değişkenleriyle erişilir "
        "(index ile DEĞİL — std::pair'in operator[] tanımı yoktur). "
        "std::make_pair(deger1, deger2) fonksiyonu, türleri argümanlardan "
        "otomatik çıkararak bir pair oluşturur.";
    lessons[80].syntax = "std::pair<Tur1, Tur2> degisken(deger1, deger2);";
    lessons[80].exampleCode =
        "#include <iostream>\n"
        "#include <utility>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::pair<std::string, int> ogrenci(\"Ali\", 20);\n"
        "    std::cout << ogrenci.first << \" \" << ogrenci.second;\n"
        "    return 0;\n"
        "}";
    lessons[80].lineExplanations = {
        "std::pair<std::string, int> ogrenci(\"Ali\", 20); : ogrenci, "
        "bir std::string ve bir int'i birlikte tutan bir pair nesnesidir.",
        "ogrenci.first : pair'in ilk elemanına (\"Ali\") erişir.",
        "ogrenci.second : pair'in ikinci elemanına (20) erişir."};
    lessons[80].commonMistakes = {
        "pair elemanlarına .first ve .second ile erişilir; ogrenci[0] "
        "gibi index ile erişim YOKTUR — std::pair'in operator[] tanımı "
        "olmadığından bu bir derleme hatasıdır."};

    lessons[81].explanation =
        "std::tuple<Tur1, Tur2, ...>, std::pair'in İKİDEN FAZLA elemana "
        "genelleştirilmiş halidir; N farklı türden değeri tek bir "
        "nesnede tutar. Elemanlarına std::get<Index>(t) ile erişilir; "
        "Index, DERLEME ZAMANINDA bilinen bir sabit olmalıdır — çalışma "
        "zamanında değişen bir değişkeni index olarak kullanmak "
        "(std::get<i>(t) gibi, i bir değişkense) bir derleme hatasıdır.";
    lessons[81].syntax = "std::tuple<Tur1, Tur2, Tur3> degisken(deger1, deger2, deger3);";
    lessons[81].exampleCode =
        "#include <iostream>\n"
        "#include <tuple>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::tuple<std::string, int, double> kayit(\"Ayse\", 21, 3.5);\n"
        "    std::cout << std::get<0>(kayit) << \" \" << std::get<1>(kayit)\n"
        "              << \" \" << std::get<2>(kayit);\n"
        "    return 0;\n"
        "}";
    lessons[81].lineExplanations = {
        "std::tuple<std::string, int, double> kayit(...) : kayit, üç "
        "farklı türde değeri (isim, yaş, not ortalaması) birlikte "
        "tutan bir tuple nesnesidir.",
        "std::get<0>(kayit) : tuple'ın 0. (ilk) elemanına erişir.",
        "std::get<1>(kayit), std::get<2>(kayit) : sırasıyla ikinci ve "
        "üçüncü elemanlara erişir; <> içindeki index HER ZAMAN "
        "derleme zamanında bilinen bir sabit olmalıdır."};
    lessons[81].commonMistakes = {
        "std::get<i>(kayit) çağrısında i, çalışma zamanında değişen "
        "bir değişken (örneğin bir for döngüsü sayacı) OLAMAZ; index "
        "derleme zamanı sabiti olmalıdır, aksi halde derleme hatası "
        "oluşur."};

    lessons[82].explanation =
        "std::set<Tur>, TEKRARSIZ (unique) elemanları OTOMATIK OLARAK "
        "SIRALI (artan, operator< ile) sırada tutan bir konteynerdir. "
        "Elemanlar hangi sırayla eklenirse eklensin, set üzerinde gezinmek "
        "her zaman artan sırada sonuç verir. Zaten sette bulunan bir "
        "değeri tekrar insert() etmek sessizce hiçbir şey yapmaz "
        "(set'in boyutu değişmez).";
    lessons[82].syntax = "std::set<Tur> degisken;\ndegisken.insert(deger);";
    lessons[82].exampleCode =
        "#include <iostream>\n"
        "#include <set>\n\n"
        "int main() {\n"
        "    std::set<int> sayilar;\n"
        "    sayilar.insert(5);\n"
        "    sayilar.insert(1);\n"
        "    sayilar.insert(3);\n"
        "    sayilar.insert(1);\n"
        "    for (int s : sayilar) {\n"
        "        std::cout << s << \" \";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[82].lineExplanations = {
        "sayilar.insert(5); insert(1); insert(3); insert(1); : "
        "elemanlar sırasız eklenir; ikinci insert(1) çağrısı, 1 zaten "
        "sette olduğundan yok sayılır (set TEKRARSIZ elemanlar tutar).",
        "for (int s : sayilar) : set üzerinde döngü, elemanları HER "
        "ZAMAN artan sırada verir: 1 3 5, ekleme sırasına (5 1 3) "
        "bakılmaksızın."};
    lessons[82].commonMistakes = {
        "set'teki elemanların sırası ekleme sırasına göre DEĞİL, her "
        "zaman sıralı (artan) sırada olur; bu örnekte çıktı her zaman "
        "\"1 3 5 \" olur, \"5 1 3 \" değil."};

    lessons[83].explanation =
        "std::map<AnahtarTur, DegerTur>, TEKRARSIZ anahtarları (sıralı, "
        "artan) bir değerle eşleştiren bir konteynerdir. operator[] ile "
        "OLMAYAN bir anahtarı OKUMAK bile, bu anahtarı varsayılan "
        "değerle (örneğin int için 0) map'e OTOMATIK OLARAK EKLER — bu, "
        "en yaygın gerçek std::map hatasıdır. Bir anahtarın var olup "
        "olmadığını EKLEME YAPMADAN kontrol etmek için .find(anahtar) == "
        ".end() kullanılmalıdır, operator[] değil.";
    lessons[83].syntax = "std::map<AnahtarTur, DegerTur> degisken;\ndegisken[anahtar] = deger;";
    lessons[83].exampleCode =
        "#include <iostream>\n"
        "#include <map>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::map<std::string, int> yaslar;\n"
        "    yaslar[\"Ali\"] = 20;\n"
        "    yaslar[\"Zeynep\"] = 22;\n"
        "    std::cout << yaslar.size() << \" \";\n"
        "    std::cout << yaslar[\"Mehmet\"];\n"
        "    std::cout << \" \" << yaslar.size();\n"
        "    return 0;\n"
        "}";
    lessons[83].lineExplanations = {
        "yaslar[\"Ali\"] = 20; yaslar[\"Zeynep\"] = 22; : yeni anahtar-"
        "değer çiftleri ekler; şu an 2 eleman var.",
        "yaslar.size() : 2 (Ali ve Zeynep).",
        "yaslar[\"Mehmet\"] : \"Mehmet\" anahtarı YOKKEN operator[] ile "
        "okumak, bu anahtarı 0 (int'in varsayılan değeri) ile OTOMATIK "
        "OLARAK EKLER — bu bir yan etkidir (side effect); ifade 0 "
        "değerini döndürür.",
        "yaslar.size() (ikinci kez) : \"Mehmet\" eklendiği için artık 3."};
    lessons[83].commonMistakes = {
        "operator[] ile var olmayan bir anahtarı OKUMAK bile o anahtarı "
        "varsayılan değerle map'e EKLER; sadece anahtarın var olup "
        "olmadığını kontrol etmek için .find(anahtar) == .end() "
        "kullanılmalıdır, operator[] DEĞİL."};

    lessons[84].explanation =
        "std::unordered_map<AnahtarTur, DegerTur>, std::map ile aynı "
        "anahtar-değer eşleşmesini sağlar ama İÇTE BİR HASH TABLOSU "
        "kullanır — bu yüzden std::map'in aksine anahtarlar SIRALI "
        "tutulmaz; iterasyon sırası TANIMSIZDIR (implementation-defined) "
        "ve ekleme sırasıyla veya sıralı düzenle EŞLEŞECEĞİ "
        "VARSAYILAMAZ. Buna karşılık, anahtar bazlı erişim (operator[], "
        ".find()) ortalama O(1) sürede çalışır, std::map'in O(log n) "
        "süresinden genellikle daha hızlıdır.";
    lessons[84].syntax = "std::unordered_map<AnahtarTur, DegerTur> degisken;\ndegisken[anahtar] = deger;";
    lessons[84].exampleCode =
        "#include <iostream>\n"
        "#include <unordered_map>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::unordered_map<std::string, int> stoklar;\n"
        "    stoklar[\"Elma\"] = 10;\n"
        "    stoklar[\"Armut\"] = 5;\n"
        "    std::cout << stoklar[\"Elma\"] << \" \" << stoklar.size();\n"
        "    return 0;\n"
        "}";
    lessons[84].lineExplanations = {
        "std::unordered_map<std::string, int> stoklar; : stoklar, "
        "anahtarları bir HASH TABLOSU ile saklar; std::map gibi sıralı "
        "DEĞİLDİR.",
        "stoklar[\"Elma\"] = 10; stoklar[\"Armut\"] = 5; : anahtar-değer "
        "çiftleri ekler; iç sıralama (iterasyon sırası) tanımlı/"
        "garantili DEĞİLDİR.",
        "stoklar[\"Elma\"] : \"Elma\" anahtarının değerine (10) erişir; "
        "bu erişim, sıralamadan bağımsız olarak ortalama O(1) sürede "
        "çalışır."};
    lessons[84].commonMistakes = {
        "unordered_map üzerinde döngü yaparken elemanların ekleme "
        "sırasında veya std::map gibi sıralı çıkacağı VARSAYILMAMALIDIR; "
        "iterasyon sırası tanımsızdır (implementation-defined). Sıralı "
        "gezinme gerekiyorsa std::map kullanılmalıdır."};

    lessons[85].explanation =
        "std::stack<Tur>, LIFO (Last In, First Out — son giren ilk "
        "çıkar) mantığıyla çalışan bir KONTEYNER ADAPTÖRÜDÜR; sadece "
        "push() (üste ekler), pop() (üstteki elemanı kaldırır), top() "
        "(üstteki elemana bakar) işlemlerini sunar. std::stack'in "
        "begin()/end() TANIMI YOKTUR — bu yüzden bir range-for "
        "döngüsüyle (for (int x : yigin)) DOĞRUDAN gezilemez; bunu "
        "denemek bir derleme hatasıdır.";
    lessons[85].syntax = "std::stack<Tur> degisken;\ndegisken.push(deger);";
    lessons[85].exampleCode =
        "#include <iostream>\n"
        "#include <stack>\n\n"
        "int main() {\n"
        "    std::stack<int> yigin;\n"
        "    yigin.push(1);\n"
        "    yigin.push(2);\n"
        "    yigin.push(3);\n"
        "    std::cout << yigin.top();\n"
        "    yigin.pop();\n"
        "    std::cout << \" \" << yigin.top();\n"
        "    return 0;\n"
        "}";
    lessons[85].lineExplanations = {
        "yigin.push(1); push(2); push(3); : elemanlar yığının ÜSTÜNE "
        "eklenir; son eklenen (3), en üstte olur.",
        "yigin.top() : yığının en üstündeki elemanı (3) döndürür, "
        "kaldırmaz.",
        "yigin.pop(); : en üstteki elemanı (3) kaldırır; yeni tepe "
        "artık 2 olur."};
    lessons[85].commonMistakes = {
        "std::stack, bir konteyner ADAPTÖRÜDÜR ve begin()/end() SUNMAZ; "
        "bu yüzden for (int x : yigin) gibi bir döngüyle DOĞRUDAN "
        "gezilemez — bu bir derleme hatasıdır. Elemanlara sadece "
        "top()/pop() ile sırayla erişilebilir."};

    lessons[86].explanation =
        "std::queue<Tur>, FIFO (First In, First Out — ilk giren ilk "
        "çıkar) mantığıyla çalışan bir KONTEYNER ADAPTÖRÜDÜR; push() "
        "(sona ekler), pop() (öndeki elemanı kaldırır), front() (en "
        "öndeki elemana bakar), back() (en sondaki elemana bakar) "
        "işlemlerini sunar. std::stack gibi std::queue'nun da begin()/"
        "end() TANIMI YOKTUR — range-for ile DOĞRUDAN gezilemez.";
    lessons[86].syntax = "std::queue<Tur> degisken;\ndegisken.push(deger);";
    lessons[86].exampleCode =
        "#include <iostream>\n"
        "#include <queue>\n\n"
        "int main() {\n"
        "    std::queue<int> kuyruk;\n"
        "    kuyruk.push(1);\n"
        "    kuyruk.push(2);\n"
        "    kuyruk.push(3);\n"
        "    std::cout << kuyruk.front();\n"
        "    kuyruk.pop();\n"
        "    std::cout << \" \" << kuyruk.front();\n"
        "    return 0;\n"
        "}";
    lessons[86].lineExplanations = {
        "kuyruk.push(1); push(2); push(3); : elemanlar kuyruğun "
        "SONUNA eklenir (FIFO: ilk giren ilk çıkar).",
        "kuyruk.front() : kuyruğun EN ÖNÜNDEKİ (ilk eklenen, 1) "
        "elemanı döndürür.",
        "kuyruk.pop(); : en öndeki elemanı (1) kaldırır; yeni ön "
        "artık 2 olur."};
    lessons[86].commonMistakes = {
        "std::queue, std::stack gibi bir konteyner ADAPTÖRÜDÜR ve "
        "begin()/end() SUNMAZ; for döngüsüyle doğrudan gezilemez — bu "
        "bir derleme hatasıdır."};

    lessons[87].explanation =
        "std::deque<Tur> (double-ended queue), hem BAŞA hem SONA "
        "ekleme/çıkarma yapılabilen bir konteynerdir: push_front() "
        "(başa ekler), push_back() (sona ekler), pop_front(), "
        "pop_back(). std::stack/std::queue'nun aksine, std::deque "
        "begin()/end() SUNAR ve range-for ile TAM gezilebilir, ayrıca "
        "operator[] ile rastgele erişime (random access) de izin "
        "verir.";
    lessons[87].syntax = "std::deque<Tur> degisken;\ndegisken.push_back(deger);\ndegisken.push_front(deger);";
    lessons[87].exampleCode =
        "#include <iostream>\n"
        "#include <deque>\n\n"
        "int main() {\n"
        "    std::deque<int> d;\n"
        "    d.push_back(2);\n"
        "    d.push_back(3);\n"
        "    d.push_front(1);\n"
        "    for (int x : d) {\n"
        "        std::cout << x << \" \";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[87].lineExplanations = {
        "d.push_back(2); d.push_back(3); : elemanları deque'nin "
        "SONUNA ekler: [2, 3].",
        "d.push_front(1); : 1'i deque'nin BAŞINA ekler: [1, 2, 3].",
        "for (int x : d) : deque begin()/end() sunduğundan TAM "
        "iterasyon desteklenir; çıktı: 1 2 3."};
    lessons[87].commonMistakes = {
        "stack/queue'nun aksine, deque begin()/end() sunar ve for "
        "döngüsüyle doğrudan gezilebilir; ayrıca hem başa hem sona "
        "ekleme/çıkarma yapılabilir (push_front/push_back), std::vector "
        "ise sadece sona ekleme (push_back) destekler."};

    lessons[88].explanation =
        "std::priority_queue<Tur>, VARSAYILAN olarak bir MAX-HEAP "
        "şeklinde çalışan bir KONTEYNER ADAPTÖRÜDÜR: top(), eklenme "
        "sırasına BAKILMAKSIZIN her zaman EN BÜYÜK elemanı döndürür "
        "(EN KÜÇÜĞÜ DEĞİL — bu yaygın bir yanlış anlamadır). push() ile "
        "eleman eklenir, pop() ile en büyük eleman kaldırılır. Min-heap "
        "istenirse std::priority_queue<Tur, std::vector<Tur>, "
        "std::greater<Tur>> kullanılmalıdır. std::stack/std::queue gibi "
        "iterasyon desteği YOKTUR.";
    lessons[88].syntax = "std::priority_queue<Tur> degisken;\ndegisken.push(deger);";
    lessons[88].exampleCode =
        "#include <iostream>\n"
        "#include <queue>\n\n"
        "int main() {\n"
        "    std::priority_queue<int> pq;\n"
        "    pq.push(3);\n"
        "    pq.push(7);\n"
        "    pq.push(1);\n"
        "    std::cout << pq.top();\n"
        "    pq.pop();\n"
        "    std::cout << \" \" << pq.top();\n"
        "    return 0;\n"
        "}";
    lessons[88].lineExplanations = {
        "pq.push(3); push(7); push(1); : elemanlar öncelik sırasına "
        "göre iç düzenlenir (max-heap).",
        "pq.top() : VARSAYILAN olarak EN BÜYÜK elemanı (7) döndürür, "
        "eklenme sırasına bakılmaksızın.",
        "pq.pop(); : en büyük elemanı (7) kaldırır; yeni en büyük "
        "artık 3'tür."};
    lessons[88].commonMistakes = {
        "std::priority_queue, VARSAYILAN olarak bir MAX-heap'tir; "
        "top(), en KÜÇÜK değil en BÜYÜK elemanı verir. Min-heap için "
        "üçüncü şablon argümanı olarak std::greater<Tur> "
        "belirtilmelidir; aksi halde top() her zaman en büyüğü verir."};

    lessons[89].explanation =
        "Iterator'lar (begin()/end()), herhangi bir STL konteynerini "
        "TEK TİP bir şekilde gezmenin yoludur. begin(), ilk elemanı "
        "gösteren bir iterator; end() ise SON ELEMANDAN SONRAKİ "
        "(gerçekte var OLMAYAN) konumu gösteren bir iterator döndürür — "
        "end() ASLA dereference edilmemelidir (*end() tanımsız "
        "davranıştır/UB, derleme hatası DEĞİLDİR). Bir range-for "
        "döngüsü (for (T x : konteyner)), açık bir iterator döngüsünün "
        "(for (auto it = konteyner.begin(); it != konteyner.end(); "
        "++it)) KISA yazımıdır (syntactic sugar) ve TAMAMEN AYNI çıktıyı "
        "üretir.";
    lessons[89].syntax = "for (auto it = konteyner.begin(); it != konteyner.end(); ++it) { ... }";
    lessons[89].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n\n"
        "int main() {\n"
        "    std::vector<int> v = {10, 20, 30};\n"
        "    for (auto it = v.begin(); it != v.end(); ++it) {\n"
        "        std::cout << *it << \" \";\n"
        "    }\n"
        "    for (int x : v) {\n"
        "        std::cout << x << \" \";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[89].lineExplanations = {
        "auto it = v.begin(); : it, vektörün ilk elemanını gösteren "
        "bir iterator'dur.",
        "it != v.end(); ++it : v.end(), SON elemandan SONRAKİ (var "
        "olmayan) konumu gösterir; döngü it, end()'e ulaşana kadar "
        "devam eder.",
        "*it : iterator'ın gösterdiği elemana erişir (dereferencing); "
        "for (int x : v) döngüsü, bu iterator döngüsünün KISA "
        "yazımıdır (syntactic sugar) ve aynı çıktıyı (10 20 30) "
        "üretir."};
    lessons[89].commonMistakes = {
        "v.end(), gerçek bir elemanı GÖSTERMEZ (son elemandan bir "
        "sonraki konumdur); *v.end() ile bu konumu okumaya çalışmak "
        "TANIMSIZ DAVRANIŞTIR (undefined behavior) — bu bir derleme "
        "hatası DEĞİLDİR, programın çökmesine veya öngörülemeyen "
        "sonuçlara yol açabilir."};
}
```

- [ ] **Step 3: Wire the new function into `LessonManager`**

`src/LessonManager.cpp` already includes `"LessonContent.h"` (from
Phase 13). Change the constructor's final lines from:

```cpp
    applySection7LessonContent(lessons_);
    applySection8LessonContent(lessons_);
}
```

to:

```cpp
    applySection7LessonContent(lessons_);
    applySection8LessonContent(lessons_);
    applySection9LessonContent(lessons_);
}
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/LessonContentSection7.cpp
    src/LessonContentSection8.cpp
```

to:

```cmake
    src/LessonContentSection7.cpp
    src/LessonContentSection8.cpp
    src/LessonContentSection9.cpp
```

- [ ] **Step 5: Extend the content-coverage tests**

In `tests/LessonManagerTests.cpp`, replace:

```cpp
TEST_CASE(LessonManager_TopicsElevenToEightyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 80; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsElevenToNinetyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 90; ++topicId) {
```

(keep the rest of that test's body unchanged). Then replace:

```cpp
TEST_CASE(LessonManager_TopicsEightyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 81; topicId <= 100; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsNinetyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 91; topicId <= 100; ++topicId) {
```

(keep the rest of that test's body unchanged — there must be exactly
these two content-coverage tests afterward, not three).

- [ ] **Step 6: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `95/95 test(s) passed.` (same count as Phase 19's end state —
this task only renames/widens two existing tests' ranges).

- [ ] **Step 7: Commit**

```bash
git add src/LessonContent.h src/LessonContentSection9.cpp src/LessonManager.cpp CMakeLists.txt tests/LessonManagerTests.cpp
git commit -m "feat(content): add Section 9 lesson content (topics 81-90)"
```

---

### Task 2: Questions for topics 81-84 (ids 2103-2218)

**Files:**
- Modify: `src/QuestionContent.h` (add one new declaration)
- Create: `src/QuestionsSection9.cpp`
- Modify: `src/QuestionManager.cpp` (include, call, bump `reserve()`)
- Modify: `CMakeLists.txt` (add the new `.cpp`)

**Interfaces:**
- Produces: `void appendSection9Questions(std::vector<Question>& questions);`
  — Task 3 and Task 4 append more `questions.push_back(...)` calls to
  this SAME function body (in this same file) for topics 85-87 and
  88-90 respectively. This task only adds topics 81-84 (ids 2103-2218).

- [ ] **Step 1: Add the new declaration**

In `src/QuestionContent.h`, add this line after the existing
`appendSection8Questions` declaration (do not remove that one):

```cpp
void appendSection9Questions(std::vector<Question>& questions);
```

- [ ] **Step 2: Write topics 81-84's questions**

Create `src/QuestionsSection9.cpp` with exactly this content:

```cpp
#include "QuestionContent.h"

#include "Question.h"

void appendSection9Questions(std::vector<Question>& questions) {
    // Topic 81: pair
    questions.push_back(Question{
        .id = 2103, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::pair<T1,T2>'nin amacı nedir?",
        .options = {"Bir konteynerin boyutunu değiştirmek", "İki farklı (veya aynı) türden değeri tek bir nesnede birlikte tutmak", "Bir fonksiyonu virtual yapmak", "Bir döngüyü sonlandırmak"},
        .acceptedAnswers = {"b"},
        .explanation = "std::pair, iki değeri tek bir nesnede birlikte tutar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2104, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::pair<std::string, int> p(\"Ali\", 20); p'nin elemanlarına nasıl erişilir?",
        .options = {"p[0], p[1]", "p.get(0), p.get(1)", "p.first, p.second", "p.a, p.b"},
        .acceptedAnswers = {"c"},
        .explanation = "pair elemanlarına .first ve .second ile erişilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2105, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::pair<std::string, int> p(\"Ali\", 20);\nstd::cout << p.first << p.second;\nEkran çıktısı nedir?",
        .options = {"Ali20", "20Ali", "Derleme hatası", "AliInt"},
        .acceptedAnswers = {"a"},
        .explanation = "p.first (\"Ali\") ve p.second (20) sırayla yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2106, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::make_pair(a, b) fonksiyonu ne yapar?",
        .options = {"Bir pair'i siler", "İki pair'i karşılaştırır", "Bir pair'i sıralar", "Türleri argümanlardan otomatik çıkararak bir pair oluşturur"},
        .acceptedAnswers = {"d"},
        .explanation = "make_pair, argümanların türlerini otomatik çıkarır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2107, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int,int> p(3,4);\np[0] = 5;\nBu kod derlenir mi?",
        .options = {"Evet, p.first 5 olur", "Hayır, pair'in operator[] tanımı yoktur, derleme hatası oluşur", "Evet, yeni bir eleman eklenir", "Evet ama çalışma zamanı hatası verir"},
        .acceptedAnswers = {"b"},
        .explanation = "std::pair'in operator[] tanımı yoktur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2108, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int, double> p(3, 4.5);\nstd::cout << p.first + p.second;\nEkran çıktısı nedir?",
        .options = {"34.5", "7", "7.5", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "3 + 4.5 = 7.5.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2109, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::pair<int,int> p1(1,2);\nstd::pair<int,int> p2(1,2);\nstd::cout << (p1 == p2);\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, pair karşılaştırılamaz, derleme hatası", "Evet, çıktı 0'dır", "Evet ama çıktı \"true\" yazısıdır", "Evet, derlenir; çıktı 1'dir (p1 ve p2'nin elemanları eşit)"},
        .acceptedAnswers = {"d"},
        .explanation = "std::pair operator== ile elemanları karşılaştırır; p1 ve p2'nin elemanları eşit olduğundan çıktı 1'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2110, .topicId = 81,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::pair<int, std::string> p(5, \"be\");\np.second += \"ş\";\nstd::cout << p.second;\nEkran çıktısı nedir?",
        .options = {"beş", "be", "Derleme hatası", "5be"},
        .acceptedAnswers = {"a"},
        .explanation = "p.second bir std::string'tir; += ile \"ş\" eklenir, sonuç \"beş\".",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2111, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::pair, iki farklı türden değeri tek bir nesnede birlikte tutabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2112, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "pair elemanlarına .first ve .second ile erişilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2113, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::pair, operator[] ile index kullanarak elemanlarına erişime izin verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: pair'in operator[] tanımı yoktur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2114, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::make_pair, türleri argümanlardan otomatik çıkarır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2115, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki pair, elemanları eşitse operator== ile karşılaştırılabilir (elemanların türleri karşılaştırmayı destekliyorsa).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2116, .topicId = 81,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "pair'in .first elemanı her zaman bir sayı türünde olmalıdır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: .first herhangi bir türde olabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2117, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki farklı türden değeri tek bir nesnede birlikte tutan şablon yapıya _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"pair"},
        .explanation = "Bu yapıya pair denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2118, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::pair<std::string,int> p(\"Ayşe\",30);\nstd::cout << p.first;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"Ayşe"},
        .explanation = "p.first, \"Ayşe\" değerini tutar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2119, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "pair'in ikinci elemanına erişmek için _____ üye değişkeni kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"second"},
        .explanation = "second üye değişkeni kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2120, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int,int> p(4,6);\nstd::cout << p.first + p.second;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"10"},
        .explanation = "4 + 6 = 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2121, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Türleri argümanlardan otomatik çıkararak bir pair oluşturan fonksiyon std::_____'dur (İngilizce kelime).",
        .acceptedAnswers = {"make_pair"},
        .explanation = "std::make_pair kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2122, .topicId = 81,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "pair'in .first elemanına erişmek için kullanılan üye değişken _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"first"},
        .explanation = "first üye değişkeni kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2123, .topicId = 81,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << ogrenci.first << \" \" << ogrenci.second;\nogrenci adlı bir pair'i \"Can\" ve 18 değerleriyle tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::pair<std::string, int> ogrenci(\"Can\", 18);"},
        .explanation = "pair, iki değeri birlikte tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2124, .topicId = 81,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int,int> p(2, 3);\n_____\np'nin iki elemanının toplamını ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << p.first + p.second;"},
        .explanation = "İki eleman toplanıp yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2125, .topicId = 81,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::pair<int,int> p(7, 3);\nstd::cout << p.first - p.second;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4"},
        .explanation = "7 - 3 = 4.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2126, .topicId = 81,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::pair<int,int> p1(2,3);\nstd::pair<int,int> p2(2,3);\np1.first = 10;\nstd::cout << p1.first << \" \" << p2.first;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10 2"},
        .explanation = "p1 ve p2 bağımsız kopyalardır; p1'in değişmesi p2'yi etkilemez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2127, .topicId = 81,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::pair<int,int> p(3,4);\nstd::cout << p[0];\n\nBu kod derlenmez çünkü pair'in operator[] tanımı yoktur. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << p.first;"},
        .explanation = "pair elemanlarına .first/.second ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2128, .topicId = 81,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::pair<std::string,int> p(\"Ali\", 20);\nstd::cout << p.First;\n\nBu kod derlenmez çünkü üye değişken adı 'first' küçük harfle yazılır, 'First' değil (C++ büyük/küçük harfe duyarlıdır). Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << p.first;"},
        .explanation = "C++ büyük/küçük harfe duyarlıdır; doğru üye adı first'tür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2129, .topicId = 81,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::pair<int,int> p(3, 4)\nstd::cout << p.first;\n\nProgramcı p tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::pair<int,int> p(3, 4);"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2130, .topicId = 81,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir pair tanımlayıp elemanlarını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << p.first << p.second;\n    return 0;\n}", "std::pair<int,int> p(5, 6);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), pair tanımı (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2131, .topicId = 81,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir std::string ve bir int değeri birlikte tutan bir pair tanımlayın; main() içinde .first ve .second elemanlarını ekrana yazdırın.",
        .acceptedAnswers = {"pair", "first", "second"},
        .explanation = "pair, .first/.second ile erişilen iki elemanı tutar.",
        .baseXp = 40,
    });

    // Topic 82: tuple
    questions.push_back(Question{
        .id = 2132, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::tuple<...>'ın amacı nedir?",
        .options = {"Bir konteynerin sırasını değiştirmek", "Sadece iki elemanı bir arada tutmak", "İkiden fazla farklı türden değeri tek bir nesnede birlikte tutmak", "Bir sınıfı soyut yapmak"},
        .acceptedAnswers = {"c"},
        .explanation = "tuple, pair'in ikiden fazla elemana genelleştirilmiş halidir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2133, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::tuple<int,int,int> t(1,2,3); t'nin ilk elemanına nasıl erişilir?",
        .options = {"t.first", "t[0]", "t.get(0)", "std::get<0>(t)"},
        .acceptedAnswers = {"d"},
        .explanation = "tuple elemanlarına std::get<Index>(t) ile erişilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2134, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::tuple<std::string,int,double> t(\"Can\", 18, 2.5);\nstd::cout << std::get<0>(t);\nEkran çıktısı nedir?",
        .options = {"Can", "18", "2.5", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "std::get<0>(t), tuple'ın ilk elemanına (\"Can\") erişir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2135, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::get<Index>(t) çağrısında Index nasıl olmalıdır?",
        .options = {"Çalışma zamanında hesaplanan bir değişken", "Derleme zamanında bilinen bir sabit", "Her zaman 0", "Bir std::string"},
        .acceptedAnswers = {"b"},
        .explanation = "Index, derleme zamanında bilinen bir sabit olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2136, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int> t(3,4);\nint i = 0;\nstd::cout << std::get<i>(t);\nBu kod derlenir mi?",
        .options = {"Evet, çıktı 3'tür", "Evet, çıktı 4'tür", "Hayır, index derleme zamanı sabiti olmalıdır, derleme hatası oluşur", "Evet ama çalışma zamanı hatası verir"},
        .acceptedAnswers = {"c"},
        .explanation = "std::get<...> çalışma zamanı değişkeniyle kullanılamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2137, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,double> t(5, 2.5);\nstd::cout << std::get<0>(t) + std::get<1>(t);\nEkran çıktısı nedir?",
        .options = {"52.5", "5", "2.5", "7.5"},
        .acceptedAnswers = {"d"},
        .explanation = "5 + 2.5 = 7.5.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2138, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::tuple<int,int,int> t1(1,2,3);\nstd::tuple<int,int,int> t2(1,2,3);\nstd::cout << (t1 == t2);\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Evet, derlenir; çıktı 1'dir (tüm elemanlar eşit)", "Hayır, tuple karşılaştırılamaz", "Evet, çıktı 0'dır", "Evet ama çıktı \"true\" yazısıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "std::tuple operator== ile tüm elemanları sırayla karşılaştırır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2139, .topicId = 82,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::tuple<int,std::string> t(3, \"ba\");\nstd::get<1>(t) += \"lık\";\nstd::cout << std::get<1>(t);\nEkran çıktısı nedir?",
        .options = {"ba", "balık", "Derleme hatası", "3balık"},
        .acceptedAnswers = {"b"},
        .explanation = "std::get<1>(t) bir std::string referansı döndürür; += ile \"lık\" eklenir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2140, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::tuple, ikiden fazla farklı türden değeri tek bir nesnede tutabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2141, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "tuple elemanlarına std::get<Index> ile erişilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2142, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::get<i>(t) çağrısında i, çalışma zamanında değişebilen bir değişken olabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: i, derleme zamanı sabiti olmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2143, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::tuple, pair'in ikiden fazla elemana genelleştirilmiş halidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2144, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki tuple, tüm elemanları eşitse operator== ile karşılaştırılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2145, .topicId = 82,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::get<0>(t), her zaman t'nin SON elemanına erişir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::get<0> her zaman İLK elemana erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2146, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "İkiden fazla farklı türden değeri tek bir nesnede tutan şablon yapıya _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"tuple"},
        .explanation = "Bu yapıya tuple denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2147, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::tuple<int,int> t(4,5);\nstd::cout << std::get<0>(t);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"4"},
        .explanation = "std::get<0>(t) ilk elemana (4) erişir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2148, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "tuple elemanlarına erişmek için kullanılan fonksiyon std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"get"},
        .explanation = "std::get kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2149, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int,int> t(1,2,3);\nstd::cout << std::get<2>(t);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "std::get<2>(t) üçüncü elemana (3) erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2150, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::get<Index>(t) çağrısındaki Index, derleme _____ bilinmelidir (Türkçe kelime).",
        .acceptedAnswers = {"zamanında"},
        .explanation = "Index, derleme zamanında bilinmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2151, .topicId = 82,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int> t(2,2);\nstd::cout << std::get<0>(t) * std::get<1>(t);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"4"},
        .explanation = "2 * 2 = 4.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2152, .topicId = 82,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << std::get<0>(kayit) << std::get<1>(kayit);\nkayit adlı bir tuple'ı 5 ve 10 değerleriyle tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::tuple<int, int> kayit(5, 10);"},
        .explanation = "tuple, iki değeri birlikte tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2153, .topicId = 82,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int,int> t(1,2,3);\n_____\nt'nin üçüncü elemanını ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << std::get<2>(t);"},
        .explanation = "std::get<2>(t) üçüncü elemana erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2154, .topicId = 82,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::tuple<int,int,int> t(10, 20, 30);\nstd::cout << std::get<0>(t) + std::get<1>(t) + std::get<2>(t);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"60"},
        .explanation = "10 + 20 + 30 = 60.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2155, .topicId = 82,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::tuple<int,double,std::string> t(1, 2.5, \"x\");\nstd::cout << std::get<0>(t) << \" \" << std::get<1>(t) << \" \" << std::get<2>(t);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 2.5 x"},
        .explanation = "Her eleman sırasıyla yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2156, .topicId = 82,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::tuple<int,int> t(3,4);\nstd::cout << t.first;\n\nBu kod derlenmez çünkü tuple'ın .first üye değişkeni yoktur (bu pair'e özgüdür); tuple elemanlarına std::get<Index>(t) ile erişilir. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << std::get<0>(t);"},
        .explanation = "tuple elemanlarına std::get ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2157, .topicId = 82,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::tuple<int,int,int> t(1,2,3);\nint i = 1;\nstd::cout << std::get<i>(t);\n\nBu kod derlenmez çünkü std::get<...> içindeki index, çalışma zamanında değişen bir değişken (i) olamaz; derleme zamanı sabiti olmalıdır. Hatalı satırı, sabit bir index kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << std::get<1>(t);"},
        .explanation = "Index, derleme zamanı sabiti olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2158, .topicId = 82,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::tuple<int,int> t(3, 4)\nstd::cout << std::get<0>(t);\n\nProgramcı t tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::tuple<int,int> t(3, 4);"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2159, .topicId = 82,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir tuple tanımlayıp bir elemanını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << std::get<1>(t);\n    return 0;\n}", "std::tuple<int,int> t(7, 9);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tuple tanımı (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2160, .topicId = 82,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int, bir double ve bir std::string değerini birlikte tutan bir tuple tanımlayın; main() içinde std::get ile üçünü de ekrana yazdırın.",
        .acceptedAnswers = {"tuple", "get"},
        .explanation = "tuple elemanlarına std::get ile erişilir.",
        .baseXp = 40,
    });

    // Topic 83: set
    questions.push_back(Question{
        .id = 2161, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::set<T>'nin temel özelliği nedir?",
        .options = {"Elemanları ekleme sırasına göre saklar", "Elemanların tekrarına izin verir", "Sadece sayısal türleri destekler", "Tekrarsız elemanları otomatik olarak sıralı (artan) sırada saklar"},
        .acceptedAnswers = {"d"},
        .explanation = "set, tekrarsız elemanları otomatik olarak sıralı tutar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2162, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::set<int> s;\ns.insert(5);\ns.insert(2);\ns.insert(8);\nfor (int x : s) { std::cout << x << \" \"; }\nEkran çıktısı nedir?",
        .options = {"2 5 8", "5 2 8", "8 5 2", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "set, elemanları her zaman artan sırada verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2163, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::set<int> s;\ns.insert(3);\ns.insert(3);\nstd::cout << s.size();\nEkran çıktısı nedir?",
        .options = {"2", "1", "0", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "İkinci insert(3), zaten var olan bir değeri eklemeye çalıştığından yok sayılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2164, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::set elemanlarının sırası neye göre belirlenir?",
        .options = {"Ekleme sırasına göre", "Rastgele", "Otomatik olarak artan (sıralı) sıraya göre", "Hash değerine göre"},
        .acceptedAnswers = {"c"},
        .explanation = "set elemanları otomatik olarak sıralıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2165, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::set<int> s = {5, 1, 3};\ns.insert(1);\nstd::cout << s.size();\nEkran çıktısı nedir?",
        .options = {"4", "2", "0", "3"},
        .acceptedAnswers = {"d"},
        .explanation = "1 zaten sette olduğundan tekrar eklenmez; size 3 kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2166, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = ".insert() ile zaten sette bulunan bir değer tekrar eklenirse ne olur?",
        .options = {"Sessizce yok sayılır, set değişmez", "Değer iki kez eklenir", "Derleme hatası oluşur", "Çalışma zamanı hatası (exception) oluşur"},
        .acceptedAnswers = {"a"},
        .explanation = "Tekrar eklenen değer sessizce yok sayılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2167, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::set<int> s;\ns.insert(10);\ns.insert(5);\ns.insert(20);\ns.insert(5);\nfor (int x : s) { std::cout << x << \" \"; }\nEkran çıktısı nedir?",
        .options = {"10 5 20", "5 10 20", "20 10 5", "5 5 10 20"},
        .acceptedAnswers = {"b"},
        .explanation = "set, tekrarsız elemanları sıralı verir: 5 10 20.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2168, .topicId = 83,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::set<int> s = {4, 2, 6};\nauto it = s.find(2);\nstd::cout << (it != s.end());\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, set'te find() yoktur", "Evet, çıktı 0'dır", "Evet, çıktı 1'dir (2 sette bulunduğundan)", "Evet ama derleme hatası verir"},
        .acceptedAnswers = {"c"},
        .explanation = "find(2), 2 sette olduğundan onu gösteren bir iterator döndürür; it != end() true (1).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2169, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::set, tekrarsız elemanları otomatik olarak sıralı sırada tutar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2170, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::set'e aynı değeri iki kez insert() etmek, setin boyutunu ikiye katlar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: tekrar eklenen değer yok sayılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2171, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "set üzerinde bir for döngüsüyle gezinmek, elemanları her zaman artan sırada verir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2172, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::set elemanları, ekleme sırasına göre saklanır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: elemanlar sıralı (artan) sırada saklanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2173, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = ".find() ile bir elemanın sette olup olmadığı kontrol edilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2174, .topicId = 83,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::set, aynı değeri birden fazla kez tutabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: set tekrarsız elemanlar tutar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2175, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Tekrarsız elemanları otomatik olarak sıralı tutan STL konteynerine _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"set"},
        .explanation = "Bu konteynere set denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2176, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::set<int> s;\ns.insert(9);\ns.insert(2);\nfor (int x : s) std::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"29"},
        .explanation = "set sıralı verir: 2 sonra 9.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2177, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "set'e eleman eklemek için kullanılan üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"insert"},
        .explanation = "insert() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2178, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::set<int> s = {1,2,3};\ns.insert(2);\nstd::cout << s.size();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "2 zaten sette olduğundan tekrar eklenmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2179, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::set elemanları, hangi operatöre göre sıralanır (bir sembol)?",
        .acceptedAnswers = {"<", "operator<"},
        .explanation = "set elemanları operator< kullanılarak sıralanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2180, .topicId = 83,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir elemanın sette olup olmadığını EKLEME YAPMADAN kontrol etmek için _____ üye fonksiyonu kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"find"},
        .explanation = "find() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2181, .topicId = 83,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\ns.insert(7);\ns adlı bir int set'i tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::set<int> s;"},
        .explanation = "std::set<int> ile bir int set'i tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2182, .topicId = 83,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::set<int> s = {5, 1, 3};\n_____\ns'nin tüm elemanlarını sırayla ekrana yazdıran döngüyü yazın.",
        .acceptedAnswers = {"for (int x : s) { std::cout << x << \" \"; }"},
        .explanation = "range-for ile set elemanları sıralı gezilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2183, .topicId = 83,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::set<int> s;\ns.insert(3);\ns.insert(1);\ns.insert(2);\nfor (int x : s) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"123"},
        .explanation = "set, elemanları artan sırada verir: 1 2 3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2184, .topicId = 83,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::set<int> s = {5, 3, 8, 3, 1};\nstd::cout << s.size() << \" \";\nfor (int x : s) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4 1358"},
        .explanation = "Tekrarlı 3 bir kez sayılır (size 4); sıralı çıktı: 1 3 5 8.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2185, .topicId = 83,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::set<int> s;\ns.insert(4);\nstd::cout << s[0];\n\nBu kod derlenmez çünkü std::set'in operator[] tanımı yoktur. Hatalı satırı, elemanlara erişmenin doğru yolunu kullanarak (bir for döngüsüyle) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int x : s) { std::cout << x; }"},
        .explanation = "set elemanlarına iterasyonla erişilir, index ile değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2186, .topicId = 83,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::set<int> s = {3, 1, 2};\nstd::cout << s.at(0);\n\nBu kod derlenmez çünkü std::set'in .at() üye fonksiyonu yoktur (bu vector/map'e özgüdür). Hatalı satırı, elemanları bir for döngüsüyle yazdıracak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int x : s) { std::cout << x; }"},
        .explanation = "set'in .at() tanımı yoktur; elemanlara iterasyonla erişilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2187, .topicId = 83,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::set<int> s\ns.insert(5);\n\nProgramcı s tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::set<int> s;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2188, .topicId = 83,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir set tanımlayıp elemanlarını sıralı şekilde yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"for (int x : s) { std::cout << x; }\n    return 0;\n}", "std::set<int> s = {3, 1, 2};", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), set tanımı (2), döngü+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2189, .topicId = 83,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int set'i tanımlayın; sırasız 3 değer ekleyin (biri tekrar eden) ve for döngüsüyle tüm elemanları sıralı şekilde ekrana yazdırın.",
        .acceptedAnswers = {"set", "insert"},
        .explanation = "set, tekrarsız elemanları sıralı olarak tutar.",
        .baseXp = 40,
    });

    // Topic 84: map
    questions.push_back(Question{
        .id = 2190, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::map<K,V>'nin temel özelliği nedir?",
        .options = {"Tekrarsız anahtarları bir değerle sıralı şekilde eşleştirir", "Elemanları LIFO sırayla tutar", "Sadece sayısal anahtarları destekler", "Anahtarları hash tablosunda sırasız tutar"},
        .acceptedAnswers = {"a"},
        .explanation = "map, anahtar-değer çiftlerini sıralı şekilde tutar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2191, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::map<std::string,int> m;\nm[\"x\"] = 5;\nstd::cout << m[\"x\"];\nEkran çıktısı nedir?",
        .options = {"0", "5", "Derleme hatası", "x"},
        .acceptedAnswers = {"b"},
        .explanation = "m[\"x\"], 5 değerini döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2192, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"]=1; m[\"b\"]=2;\nstd::cout << m.size();\nEkran çıktısı nedir?",
        .options = {"0", "1", "2", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "İki anahtar eklendi, size 2.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2193, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"]=1;\nstd::cout << m[\"z\"];\nstd::cout << \" \" << m.size();\nEkran çıktısı nedir?",
        .options = {"1 1", "0 1", "Derleme hatası", "0 2"},
        .acceptedAnswers = {"d"},
        .explanation = "m[\"z\"] okuması \"z\"'yi 0 ile ekler (side effect); size 2 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2194, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Var olmayan bir anahtarı EKLEME YAPMADAN kontrol etmek için ne kullanılmalıdır?",
        .options = {"m.find(anahtar) == m.end()", "m[anahtar] == 0", "m.size() == 0", "m.at(anahtar) her zaman"},
        .acceptedAnswers = {"a"},
        .explanation = ".find(), anahtarı eklemeden arar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2195, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"]=3; m[\"b\"]=1;\nfor (auto& kv : m) { std::cout << kv.first; }\nEkran çıktısı nedir?",
        .options = {"ba", "ab", "Sırasız, tanımsız", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "map anahtarları alfabetik sıralıdır: \"a\" önce \"b\" sonra.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2196, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::map<std::string,int> m;\nm[\"x\"] = 1;\nif (m[\"y\"] > 0) { std::cout << \"var\"; } else { std::cout << \"yok\"; }\nstd::cout << \" \" << m.size();\nEkran çıktısı nedir?",
        .options = {"var 1", "var 2", "yok 2", "yok 1"},
        .acceptedAnswers = {"c"},
        .explanation = "m[\"y\"] okuması \"y\"'yi 0 ile ekler; 0 > 0 yanlış, \"yok\" yazdırılır; size 2 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2197, .topicId = 84,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::map<std::string,int> m = {{\"b\",2},{\"a\",1},{\"c\",3}};\nfor (auto& kv : m) { std::cout << kv.first; }\nEkran çıktısı nedir?",
        .options = {"bac", "cba", "Sırasız, tanımsız", "abc"},
        .acceptedAnswers = {"d"},
        .explanation = "map anahtarları her zaman sıralıdır: a, b, c.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2198, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::map, anahtarları otomatik olarak sıralı (artan) sırada tutar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2199, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "operator[] ile olmayan bir anahtarı okumak, o anahtarı map'e otomatik olarak ekler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2200, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = ".find() ile bir anahtarı aramak, o anahtarı map'e ekler.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: .find() anahtarı eklemeden arar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2201, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::map, aynı anahtarı birden fazla kez tutabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: map anahtarları tekrarsızdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2202, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::map üzerinde bir for döngüsüyle gezinmek, anahtarları her zaman sıralı (artan) sırada verir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2203, .topicId = 84,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::map'in operator[]'i, sadece OKUMA yapar, asla yeni bir eleman EKLEMEZ.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: olmayan bir anahtarı okumak yeni bir eleman ekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2204, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Anahtarları sıralı şekilde bir değerle eşleştiren STL konteynerine _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"map"},
        .explanation = "Bu konteynere map denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2205, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::map<std::string,int> m;\nm[\"k\"] = 7;\nstd::cout << m[\"k\"];\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "m[\"k\"], 7 değerini döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2206, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Var olmayan bir anahtarı EKLEME YAPMADAN aramak için kullanılan üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"find"},
        .explanation = "find() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2207, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"]=1;\nm[\"b\"];\nstd::cout << m.size();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "m[\"b\"] okuması \"b\"'yi ekler; size 2 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2208, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "operator[] ile olmayan bir anahtarı okumak, o anahtarı varsayılan değerle map'e otomatik olarak _____ (Türkçe kelime).",
        .acceptedAnswers = {"ekler"},
        .explanation = "Bu bir yan etkidir (side effect).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2209, .topicId = 84,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m = {{\"z\",1},{\"a\",2}};\nauto it = m.begin();\nstd::cout << it->first;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"a"},
        .explanation = "map sıralı olduğundan begin(), alfabetik olarak en küçük anahtarı (\"a\") gösterir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2210, .topicId = 84,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nm[\"x\"] = 5;\nm adlı bir std::string-int map'i tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::map<std::string, int> m;"},
        .explanation = "std::map<std::string,int> ile tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2211, .topicId = 84,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"] = 1;\n_____\n\"a\" anahtarının map'te olup olmadığını EKLEME YAPMADAN kontrol eden if satırını yazın.",
        .acceptedAnswers = {"if (m.find(\"a\") != m.end()) {"},
        .explanation = ".find() ile eklemeden kontrol edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2212, .topicId = 84,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::map<std::string,int> m;\nm[\"x\"] = 10;\nm[\"y\"] = 20;\nstd::cout << m[\"x\"] + m[\"y\"];\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30"},
        .explanation = "10 + 20 = 30.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2213, .topicId = 84,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::map<std::string,int> m;\nm[\"a\"] = 5;\nstd::cout << m.size() << \" \";\nm[\"b\"];\nstd::cout << m.size();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 2"},
        .explanation = "İlk size 1; m[\"b\"] okuması \"b\"'yi ekler, size 2 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2214, .topicId = 84,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::map<std::string,int> m;\nm[\"a\"] = 1;\nstd::cout << m.first;\n\nBu kod derlenmez çünkü std::map'in .first üye değişkeni yoktur (bu pair'e özgüdür, map'in kendisine değil). Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << m[\"a\"];"},
        .explanation = "map'in kendisinin .first üyesi yoktur; anahtar ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2215, .topicId = 84,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::map<std::string,int> m;\nm[\"a\"] = 1;\nif (m[\"b\"] == 1) { std::cout << \"var\"; }\n\nBu kod \"b\" anahtarının var olup olmadığını YANLIŞ kontrol eder çünkü m[\"b\"] okuması \"b\"'yi 0 değeriyle map'e EKLER (side effect); doğru kontrol .find() ile yapılmalıdır. Hatalı if satırını düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (m.find(\"b\") != m.end()) {"},
        .explanation = ".find() ile eklemeden kontrol edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2216, .topicId = 84,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::map<std::string,int> m\nm[\"a\"] = 1;\n\nProgramcı m tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::map<std::string, int> m;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2217, .topicId = 84,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir map tanımlayıp bir değeri yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << m[\"k\"];\n    return 0;\n}", "std::map<std::string,int> m;\n    m[\"k\"] = 42;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), map tanımı+atama (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2218, .topicId = 84,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir std::string anahtar ve int değer tutan bir map tanımlayın; iki anahtar-değer çifti ekleyin ve for döngüsüyle tüm anahtar-değer çiftlerini ekrana yazdırın.",
        .acceptedAnswers = {"map", "first", "second"},
        .explanation = "map elemanları for döngüsünde .first/.second ile erişilen pair'lerdir.",
        .baseXp = 40,
    });
}
```

- [ ] **Step 3: Wire the new function into `QuestionManager`**

`src/QuestionManager.cpp` already includes `"QuestionContent.h"` (from
Phase 13). Change the constructor's final lines from:

```cpp
    appendSection7Questions(questions_);
    appendSection8Questions(questions_);
```

to:

```cpp
    appendSection7Questions(questions_);
    appendSection8Questions(questions_);
    appendSection9Questions(questions_);
```

Also change `questions_.reserve(2102);` to `questions_.reserve(2392);`.

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/QuestionsSection7.cpp
    src/QuestionsSection8.cpp
```

to:

```cmake
    src/QuestionsSection7.cpp
    src/QuestionsSection8.cpp
    src/QuestionsSection9.cpp
```

- [ ] **Step 5: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `95/95 test(s) passed.` (unchanged — the test that counts
questions per topic is added in Task 4, once all of topics 81-90 have
their full 29 questions each).

- [ ] **Step 6: Commit**

```bash
git add src/QuestionContent.h src/QuestionsSection9.cpp src/QuestionManager.cpp CMakeLists.txt
git commit -m "feat(content): add questions for topics 81-84 (ids 2103-2218)"
```

---

### Task 3: Questions for topics 85-87 (ids 2219-2305)

**Files:**
- Modify: `src/QuestionsSection9.cpp` (append more `push_back` calls to
  the SAME `appendSection9Questions` function Task 2 created)

**Interfaces:**
- Consumes: `appendSection9Questions(std::vector<Question>& questions)`
  defined in `src/QuestionsSection9.cpp` by Task 2 — append to its body,
  after the last `questions.push_back(...)` for id 2218 and before the
  function's closing `}`.
- Produces: ids 2219-2305 added to the same function. Task 4 appends
  after this task's last id (2305).

- [ ] **Step 1: Write topics 85-87's questions**

Open `src/QuestionsSection9.cpp` as it exists on disk (Task 2's
committed state) and insert the following `push_back` calls right
after the id-2218 block, before the function's closing `}`:

```cpp
    // Topic 85: unordered_map
    questions.push_back(Question{
        .id = 2219, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::unordered_map<K,V> ile std::map<K,V> arasındaki temel fark nedir?",
        .options = {"unordered_map anahtarları sıralı tutar, map tutmaz", "unordered_map anahtarları hash tablosunda sırasız tutar, map ise sıralı tutar", "unordered_map sadece int anahtarları destekler", "İkisi arasında fark yoktur"},
        .acceptedAnswers = {"b"},
        .explanation = "unordered_map hash tabanlıdır ve sıralama garantisi vermez; map sıralıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2220, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"a\"] = 5;\nstd::cout << m[\"a\"];\nEkran çıktısı nedir?",
        .options = {"0", "a", "5", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "m[\"a\"], 5 değerini döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2221, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map, iç yapı olarak neyi kullanır?",
        .options = {"Sıralı bir ağaç (sorted tree)", "Bağlı liste (linked list)", "Dizi (array), sıralı tutar", "Hash tablosu (hash table)"},
        .acceptedAnswers = {"d"},
        .explanation = "unordered_map bir hash tablosu kullanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2222, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"x\"]=1; m[\"y\"]=2; m[\"z\"]=3;\nfor (auto& kv : m) { ... }\nBu döngünün elemanları gezme sırası hakkında ne söylenebilir?",
        .options = {"Sıra tanımsızdır (implementation-defined); ekleme sırasıyla veya alfabetik sırayla eşleşeceği varsayılamaz", "Her zaman ekleme sırasıyla aynıdır", "Her zaman alfabetik sıradadır", "Her zaman ekleme sırasının tersidir"},
        .acceptedAnswers = {"a"},
        .explanation = "unordered_map iterasyon sırası implementation-defined'dır, hiçbir sıra varsayılamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2223, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map ile anahtar bazlı arama (.find()/operator[]) ortalama hangi sürede çalışır?",
        .options = {"O(n)", "O(1)", "O(log n)", "O(n^2)"},
        .acceptedAnswers = {"b"},
        .explanation = "Hash tabanlı arama ortalama O(1) sürer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2224, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::map ile anahtar bazlı arama ortalama hangi sürede çalışır?",
        .options = {"O(1)", "O(n)", "O(log n)", "O(n^2)"},
        .acceptedAnswers = {"c"},
        .explanation = "map, dengeli bir ağaç kullandığından arama O(log n) sürer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2225, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"a\"] = 1;\nstd::cout << m[\"b\"];\nstd::cout << \" \" << m.size();\nEkran çıktısı nedir?",
        .options = {"1 1", "Derleme hatası", "0 1", "0 2"},
        .acceptedAnswers = {"d"},
        .explanation = "m[\"b\"] okuması, map'teki ile aynı şekilde \"b\"'yi 0 ile ekler; size 2 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2226, .topicId = 85,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Sıralı gezinme (alfabetik/artan sırayla) gerektiren bir program için hangi konteyner tercih edilmelidir?",
        .options = {"std::map (sıralı garanti verir)", "std::unordered_map (daha hızlı olduğundan her zaman tercih edilir)", "İkisi de aynıdır, fark etmez", "std::unordered_map (sıralı garanti verir)"},
        .acceptedAnswers = {"a"},
        .explanation = "Sıralı gezinme garantisi gereken durumlarda std::map tercih edilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2227, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::unordered_map, anahtarları bir hash tablosunda tutar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2228, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::unordered_map, std::map gibi anahtarları sıralı (artan) tutar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: unordered_map sıralama garantisi vermez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2229, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map üzerinde iterasyon sırası tanımsızdır (implementation-defined).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2230, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map'te anahtar bazlı erişim (operator[]/.find()), ortalama olarak std::map'ten daha YAVAŞTIR.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: unordered_map ortalama O(1), map ise O(log n) sürer; unordered_map genellikle daha hızlıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2231, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map'in operator[]'i de, std::map gibi, olmayan bir anahtarı okurken onu otomatik olarak ekler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2232, .topicId = 85,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Sıralı gezinme gerektiren bir uygulamada std::unordered_map, std::map'ten daha uygun bir seçimdir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: sıralama garantisi olmadığından std::map daha uygundur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2233, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Anahtarları bir hash tablosunda sırasız tutan STL konteynerine _____ denir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"unordered_map"},
        .explanation = "Bu konteynere unordered_map denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2234, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"p\"] = 9;\nstd::cout << m[\"p\"];\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"9"},
        .explanation = "m[\"p\"], 9 değerini döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2235, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "unordered_map'in iç yapısı bir _____ tablosudur (İngilizce kelime).",
        .acceptedAnswers = {"hash"},
        .explanation = "unordered_map bir hash tablosu kullanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2236, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "unordered_map'te anahtar bazlı erişim ortalama _____ sürede çalışır (Büyük O gösterimi, örn. O(1)).",
        .acceptedAnswers = {"O(1)"},
        .explanation = "Hash tabanlı erişim ortalama O(1) sürer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2237, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::map'te anahtar bazlı erişim ortalama _____ sürede çalışır (Büyük O gösterimi).",
        .acceptedAnswers = {"O(log n)"},
        .explanation = "Ağaç tabanlı erişim O(log n) sürer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2238, .topicId = 85,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "unordered_map üzerinde iterasyon sırası _____ (Türkçe kelime, 'belirsiz/tanımsız' anlamında).",
        .acceptedAnswers = {"tanımsızdır", "tanımsız"},
        .explanation = "İterasyon sırası implementation-defined'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2239, .topicId = 85,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nm[\"kalem\"] = 3;\nm adlı bir std::string-int unordered_map tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::unordered_map<std::string, int> m;"},
        .explanation = "unordered_map, hash tabanlı bir anahtar-değer konteyneridir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2240, .topicId = 85,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"a\"] = 1;\n_____\n\"a\" anahtarının değerini ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << m[\"a\"];"},
        .explanation = "operator[] ile anahtarın değerine erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2241, .topicId = 85,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"x\"] = 4;\nm[\"y\"] = 6;\nstd::cout << m[\"x\"] + m[\"y\"];\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "4 + 6 = 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2242, .topicId = 85,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::unordered_map<std::string,int> m;\nm[\"a\"] = 2;\nstd::cout << m.size() << \" \";\nm[\"b\"];\nstd::cout << m.size();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 2"},
        .explanation = "İlk size 1; m[\"b\"] okuması \"b\"'yi ekler, size 2 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2243, .topicId = 85,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::unordered_map<std::string,int> m;\nm[\"a\"] = 1;\nstd::cout << m.first;\n\nBu kod derlenmez çünkü std::unordered_map'in .first üye değişkeni yoktur (bu pair'e özgüdür, konteynerin kendisine değil). Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << m[\"a\"];"},
        .explanation = "unordered_map'in kendisinin .first üyesi yoktur; anahtar ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2244, .topicId = 85,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::unordered_map<std::string,int> m;\nm[\"a\"] = 1;\nif (m[\"b\"] == 1) { std::cout << \"var\"; }\n\nBu kod \"b\" anahtarının var olup olmadığını YANLIŞ kontrol eder çünkü m[\"b\"] okuması \"b\"'yi 0 değeriyle map'e EKLER (side effect, std::map'teki ile aynı davranış); doğru kontrol .find() ile yapılmalıdır. Hatalı if satırını düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (m.find(\"b\") != m.end()) {"},
        .explanation = ".find() ile eklemeden kontrol edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2245, .topicId = 85,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::unordered_map<std::string,int> m\nm[\"a\"] = 1;\n\nProgramcı m tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::unordered_map<std::string, int> m;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2246, .topicId = 85,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir unordered_map tanımlayıp bir değeri yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << m[\"k\"];\n    return 0;\n}", "std::unordered_map<std::string,int> m;\n    m[\"k\"] = 8;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+atama (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2247, .topicId = 85,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir std::string anahtar ve int değer tutan bir unordered_map tanımlayın; bir anahtar-değer çifti ekleyin ve o anahtarın değerini ekrana yazdırın.",
        .acceptedAnswers = {"unordered_map"},
        .explanation = "unordered_map, hash tabanlı bir anahtar-değer konteyneridir.",
        .baseXp = 40,
    });

    // Topic 86: stack
    questions.push_back(Question{
        .id = 2248, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::stack<T>'nin çalışma mantığı nedir?",
        .options = {"FIFO (ilk giren ilk çıkar)", "Elemanları sıralı (artan) tutar", "LIFO (son giren ilk çıkar)", "Elemanları hash tablosunda tutar"},
        .acceptedAnswers = {"c"},
        .explanation = "std::stack LIFO mantığıyla çalışır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2249, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::stack<int> s;\ns.push(1);\ns.push(2);\nstd::cout << s.top();\nEkran çıktısı nedir?",
        .options = {"1", "0", "Derleme hatası", "2"},
        .acceptedAnswers = {"d"},
        .explanation = "top(), en son eklenen (2) elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2250, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::stack<int> s;\ns.push(1);\ns.push(2);\ns.pop();\nstd::cout << s.top();\nEkran çıktısı nedir?",
        .options = {"1", "2", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "pop(), en üstteki (2) elemanı kaldırır; yeni tepe 1 olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2251, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(5);\nfor (int x : s) { std::cout << x; }\nBu kod derlenir mi?",
        .options = {"Evet, çıktı 5'tir", "Hayır, std::stack'in begin()/end() tanımı yoktur, derleme hatası oluşur", "Evet ama çıktı boştur", "Evet, çıktı 0'dır"},
        .acceptedAnswers = {"b"},
        .explanation = "std::stack begin()/end() sunmaz, range-for derlenmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2252, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(3); s.push(6); s.push(9);\nstd::cout << s.top();\ns.pop();\nstd::cout << \" \" << s.top();\ns.pop();\nstd::cout << \" \" << s.top();\nEkran çıktısı nedir?",
        .options = {"3 6 9", "9 9 9", "9 6 3", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "LIFO sırayla en son eklenenden başlanarak: 9, 6, 3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2253, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::stack, hangi konteyner tarafından desteklenen (varsayılan olarak) bir adaptördür?",
        .options = {"std::vector", "std::set", "std::map", "std::deque"},
        .acceptedAnswers = {"d"},
        .explanation = "std::stack'in varsayılan alttaki konteyneri std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2254, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::stack<int> s;\nstd::cout << s.empty();\ns.push(1);\nstd::cout << \" \" << s.empty();\nEkran çıktısı nedir?",
        .options = {"1 0", "0 1", "true false", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "İlk empty() true (1); push sonrası empty() false (0).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2255, .topicId = 86,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::stack<int> s1;\ns1.push(1);\ns1.push(2);\nstd::stack<int> s2 = s1;\ns2.pop();\nstd::cout << s1.top() << \" \" << s2.top();\nEkran çıktısı nedir?",
        .options = {"1 2", "2 1", "2 2", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "s2, s1'in bağımsız bir kopyasıdır; s2.pop() s1'i etkilemez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2256, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::stack, LIFO (son giren ilk çıkar) mantığıyla çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2257, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::stack, begin()/end() sunar ve for döngüsüyle doğrudan gezilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::stack begin()/end() sunmaz.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2258, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::stack'te top(), en üstteki elemanı kaldırmadan döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2259, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::stack'te pop(), en üstteki elemanı döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: pop() void döndürür, sadece elemanı kaldırır; değere bakmak için top() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2260, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::stack kopyalandığında, kopya bağımsız bir yığındır; birini değiştirmek diğerini etkilemez.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2261, .topicId = 86,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::stack, varsayılan olarak std::vector tarafından desteklenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan alttaki konteyner std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2262, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "LIFO (son giren ilk çıkar) mantığıyla çalışan konteyner adaptörüne _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"stack"},
        .explanation = "Bu adaptöre stack denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2263, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::stack<int> s;\ns.push(7);\nstd::cout << s.top();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "top(), en üstteki (7) elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2264, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "stack'in en üstteki elemanını kaldıran (ama döndürmeyen) üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"pop"},
        .explanation = "pop() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2265, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(1); s.push(2); s.push(3);\ns.pop();\nstd::cout << s.top();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "pop(), en üstteki (3) elemanı kaldırır; yeni tepe 2 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2266, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::stack'in begin()/end() tanımı olmadığından, elemanlarına sadece top()/pop() ile _____ erişilebilir (Türkçe kelime, 'teker teker/sırayla' anlamında).",
        .acceptedAnswers = {"sırayla"},
        .explanation = "Elemanlara sadece sırayla erişilebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2267, .topicId = 86,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::stack, varsayılan olarak std::_____ tarafından desteklenir (İngilizce kelime).",
        .acceptedAnswers = {"deque"},
        .explanation = "Varsayılan alttaki konteyner std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2268, .topicId = 86,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\ns.push(4);\ns adlı bir int stack'i tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::stack<int> s;"},
        .explanation = "std::stack<int> ile bir int stack'i tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2269, .topicId = 86,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(1);\ns.push(2);\n_____\nyığının en üstteki elemanını ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << s.top();"},
        .explanation = "top(), en üstteki elemanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2270, .topicId = 86,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::stack<int> s;\ns.push(2);\ns.push(4);\ns.push(6);\nstd::cout << s.top();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6"},
        .explanation = "En son eklenen (6), en üstte olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2271, .topicId = 86,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::stack<int> s;\ns.push(1);\ns.push(2);\ns.push(3);\nint toplam = 0;\nwhile (!s.empty()) {\n    toplam += s.top();\n    s.pop();\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6"},
        .explanation = "1 + 2 + 3 = 6 (sıra LIFO olsa da toplam aynıdır).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2272, .topicId = 86,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::stack<int> s;\ns.push(5);\nfor (int x : s) { std::cout << x; }\n\nBu kod derlenmez çünkü std::stack'in begin()/end() tanımı yoktur. Hatalı satırı, top()/pop() kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << s.top();"},
        .explanation = "stack elemanlarına top()/pop() ile erişilir, iterasyonla değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2273, .topicId = 86,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::stack<int> s;\ns.push(3);\nint deger = s.pop();\n\nBu kod derlenmez çünkü std::stack::pop(), void döndürür (bir değer döndürmez); önce top() ile değere bakılıp SONRA pop() çağrılmalıdır. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int deger = s.top();"},
        .explanation = "pop() void döndürür; değere top() ile bakılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2274, .topicId = 86,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::stack<int> s\ns.push(1);\n\nProgramcı s tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::stack<int> s;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2275, .topicId = 86,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir stack tanımlayıp en üstteki elemanı yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << s.top();\n    return 0;\n}", "std::stack<int> s;\n    s.push(11);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+push (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2276, .topicId = 86,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int stack'i tanımlayın; üç değer push edin ve top()/pop() kullanarak elemanları LIFO sırayla (son eklenen ilk) ekrana yazdırın.",
        .acceptedAnswers = {"stack", "push", "pop"},
        .explanation = "stack, LIFO sırayla erişim sağlar.",
        .baseXp = 40,
    });

    // Topic 87: queue
    questions.push_back(Question{
        .id = 2277, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::queue<T>'nin çalışma mantığı nedir?",
        .options = {"LIFO (son giren ilk çıkar)", "Elemanları sıralı (artan) tutar", "Elemanları hash tablosunda tutar", "FIFO (ilk giren ilk çıkar)"},
        .acceptedAnswers = {"d"},
        .explanation = "std::queue FIFO mantığıyla çalışır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2278, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::queue<int> q;\nq.push(1);\nq.push(2);\nstd::cout << q.front();\nEkran çıktısı nedir?",
        .options = {"1", "2", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "front(), en önce eklenen (1) elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2279, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::queue<int> q;\nq.push(1);\nq.push(2);\nstd::cout << q.back();\nEkran çıktısı nedir?",
        .options = {"1", "2", "0", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "back(), en son eklenen (2) elemanı döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2280, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(5);\nfor (int x : q) { std::cout << x; }\nBu kod derlenir mi?",
        .options = {"Evet, çıktı 5'tir", "Evet ama çıktı boştur", "Hayır, std::queue'nun begin()/end() tanımı yoktur, derleme hatası oluşur", "Evet, çıktı 0'dır"},
        .acceptedAnswers = {"c"},
        .explanation = "std::queue begin()/end() sunmaz, range-for derlenmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2281, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(1); q.push(2); q.push(3);\nq.pop();\nstd::cout << q.front();\nEkran çıktısı nedir?",
        .options = {"1", "3", "0", "2"},
        .acceptedAnswers = {"d"},
        .explanation = "pop(), en öndeki (1) elemanı kaldırır; yeni ön 2 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2282, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::queue, hangi konteyner tarafından desteklenen (varsayılan olarak) bir adaptördür?",
        .options = {"std::deque", "std::vector", "std::set", "std::list"},
        .acceptedAnswers = {"a"},
        .explanation = "std::queue'nun varsayılan alttaki konteyneri std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2283, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::queue<int> q;\nq.push(1); q.push(2); q.push(3);\nstd::cout << q.front() << \" \" << q.back();\nEkran çıktısı nedir?",
        .options = {"3 1", "1 3", "1 1", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "front() ilk eklenen (1), back() son eklenen (3) elemanı döndürür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2284, .topicId = 87,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::queue<int> q1;\nq1.push(1);\nq1.push(2);\nstd::queue<int> q2 = q1;\nq2.pop();\nstd::cout << q1.front() << \" \" << q2.front();\nEkran çıktısı nedir?",
        .options = {"2 2", "1 1", "1 2", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "q2, q1'in bağımsız bir kopyasıdır; q2.pop() q1'i etkilemez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2285, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::queue, FIFO (ilk giren ilk çıkar) mantığıyla çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2286, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::queue, begin()/end() sunar ve for döngüsüyle doğrudan gezilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::queue begin()/end() sunmaz.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2287, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::queue'da front(), en öndeki elemana bakar (kaldırmaz).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2288, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::queue'da back(), en öndeki elemana bakar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: back(), en SONDAKİ elemana bakar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2289, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::queue kopyalandığında, kopya bağımsız bir kuyruktur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2290, .topicId = 87,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::queue, varsayılan olarak std::vector tarafından desteklenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan alttaki konteyner std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2291, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "FIFO (ilk giren ilk çıkar) mantığıyla çalışan konteyner adaptörüne _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"queue"},
        .explanation = "Bu adaptöre queue denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2292, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::queue<int> q;\nq.push(8);\nstd::cout << q.front();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "front(), tek eleman olan 8'i döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2293, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "kuyruğun en öndeki elemanını kaldıran (ama döndürmeyen) üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"pop"},
        .explanation = "pop() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2294, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(1); q.push(2); q.push(3);\nq.pop();\nq.pop();\nstd::cout << q.front();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "İki pop, 1 ve 2'yi sırayla kaldırır; kalan front 3'tür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2295, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "kuyruğun en sondaki elemanına bakmak için kullanılan üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"back"},
        .explanation = "back() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2296, .topicId = 87,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::queue, varsayılan olarak std::_____ tarafından desteklenir (İngilizce kelime).",
        .acceptedAnswers = {"deque"},
        .explanation = "Varsayılan alttaki konteyner std::deque'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2297, .topicId = 87,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nq.push(5);\nq adlı bir int kuyruğu tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::queue<int> q;"},
        .explanation = "std::queue<int> ile bir int kuyruğu tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2298, .topicId = 87,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(1);\nq.push(2);\n_____\nkuyruğun en öndeki elemanını ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << q.front();"},
        .explanation = "front(), en öndeki elemanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2299, .topicId = 87,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::queue<int> q;\nq.push(3);\nq.push(6);\nq.push(9);\nstd::cout << q.front();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "En önce eklenen (3), front olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2300, .topicId = 87,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::queue<int> q;\nq.push(1);\nq.push(2);\nq.push(3);\nint toplam = 0;\nwhile (!q.empty()) {\n    toplam += q.front();\n    q.pop();\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6"},
        .explanation = "1 + 2 + 3 = 6.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2301, .topicId = 87,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::queue<int> q;\nq.push(5);\nfor (int x : q) { std::cout << x; }\n\nBu kod derlenmez çünkü std::queue'nun begin()/end() tanımı yoktur. Hatalı satırı, front() kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << q.front();"},
        .explanation = "queue elemanlarına front()/pop() ile erişilir, iterasyonla değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2302, .topicId = 87,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::queue<int> q;\nq.push(3);\nint deger = q.pop();\n\nBu kod derlenmez çünkü std::queue::pop(), void döndürür (bir değer döndürmez); önce front() ile değere bakılıp SONRA pop() çağrılmalıdır. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int deger = q.front();"},
        .explanation = "pop() void döndürür; değere front() ile bakılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2303, .topicId = 87,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::queue<int> q\nq.push(1);\n\nProgramcı q tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::queue<int> q;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2304, .topicId = 87,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir kuyruk tanımlayıp en öndeki elemanı yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << q.front();\n    return 0;\n}", "std::queue<int> q;\n    q.push(13);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+push (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2305, .topicId = 87,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int kuyruğu tanımlayın; üç değer push edin ve front()/pop() kullanarak elemanları FIFO sırayla (ilk eklenen ilk) ekrana yazdırın.",
        .acceptedAnswers = {"queue", "push", "pop"},
        .explanation = "queue, FIFO sırayla erişim sağlar.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Build and run the full test suite**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `95/95 test(s) passed.` (unchanged — the test that counts
questions per topic is added in Task 4, once all of topics 81-90 have
their full 29 questions each).

- [ ] **Step 3: Commit**

```bash
git add src/QuestionsSection9.cpp
git commit -m "feat(content): add questions for topics 85-87 (ids 2219-2305)"
```

---

### Task 4: Questions for topics 88-90 (ids 2306-2392), test updates, and final integration

**Files:**
- Modify: `src/QuestionsSection9.cpp` (append the final `push_back`
  calls to `appendSection9Questions`)
- Modify: `tests/QuestionManagerTests.cpp` (add one new per-section
  minimum-count test)
- Modify: `docs/superpowers/roadmap.md` (mark Phase 20 complete)

**Interfaces:**
- Consumes: `appendSection9Questions(std::vector<Question>& questions)`
  in `src/QuestionsSection9.cpp` — append after Task 3's last id (2305),
  before the function's closing `}`. After this task, ids 2103-2392 are
  all present (10 topics x 29 questions) and the function is complete.

- [ ] **Step 1: Write topics 88-90's questions**

Open `src/QuestionsSection9.cpp` as it exists on disk (Task 3's
committed state) and insert the following `push_back` calls right
after the id-2305 block, before the function's closing `}`:

```cpp
    // Topic 88: deque
    questions.push_back(Question{
        .id = 2306, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::deque<T>'nin (double-ended queue) temel özelliği nedir?",
        .options = {"Hem başa hem sona ekleme/çıkarma yapılabilir, ayrıca tam iterasyon desteklenir", "Sadece sona ekleme yapılabilir", "Elemanları sıralı (artan) tutar", "Sadece başa ekleme yapılabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "deque hem çift yönlü ekleme/çıkarma hem de tam iterasyon destekler.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2307, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::deque<int> d;\nd.push_back(1);\nd.push_back(2);\nd.push_front(0);\nfor (int x : d) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"120", "012", "210", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "push_back(1), push_back(2), push_front(0) sırasıyla [1],[1,2],[0,1,2] durumlarını üretir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2308, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::deque, begin()/end() sunar mı?",
        .options = {"Hayır, sadece stack/queue gibi push/pop sunar", "Sadece begin() sunar, end() sunmaz", "Evet, tam iterasyon desteklenir", "Sadece belirli koşullarda sunar"},
        .acceptedAnswers = {"c"},
        .explanation = "deque, begin()/end() ile tam iterasyon destekler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2309, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d = {1,2,3};\nstd::cout << d[1];\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, derleme hatası", "Evet, çıktı 1'dir", "Evet, çıktı 3'tür", "Evet, çıktı 2'dir"},
        .acceptedAnswers = {"d"},
        .explanation = "deque operator[] ile rastgele erişimi destekler; d[1] ikinci elemandır (2).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2310, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d;\nd.push_back(5);\nd.push_back(10);\nd.pop_front();\nstd::cout << d.size();\nEkran çıktısı nedir?",
        .options = {"1", "2", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "pop_front(), 5'i kaldırır; kalan tek eleman (10) size 1 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2311, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::deque ile std::stack/std::queue arasındaki temel fark nedir?",
        .options = {"deque sadece tek yönlü ekleme yapar, stack/queue çift yönlü yapar", "deque hem çift yönlü ekleme/çıkarma yapar hem de iterasyona izin verir; stack/queue sadece belirli uçlara erişim sunar ve iterasyona izin vermez", "Aralarında fark yoktur", "stack/queue rastgele erişime izin verir, deque vermez"},
        .acceptedAnswers = {"b"},
        .explanation = "deque, stack/queue'nun aksine hem çift yönlü erişim hem de iterasyon sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2312, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::deque<int> d;\nd.push_back(1);\nd.push_front(2);\nd.push_back(3);\nd.push_front(4);\nfor (int x : d) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"1234", "4321", "4213", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "Sırasıyla [1],[2,1],[2,1,3],[4,2,1,3] durumları oluşur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2313, .topicId = 88,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::deque<int> d = {10,20,30};\nd.pop_back();\nd.pop_front();\nstd::cout << d.size() << \" \" << d[0];\nEkran çıktısı nedir?",
        .options = {"2 10", "2 20", "1 10", "1 20"},
        .acceptedAnswers = {"d"},
        .explanation = "pop_back() 30'u, pop_front() 10'u kaldırır; kalan {20}, size 1, d[0]=20.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2314, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::deque, hem başa hem sona ekleme/çıkarma destekler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2315, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::deque, std::stack gibi begin()/end() sunmaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: deque begin()/end() sunar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2316, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::deque, operator[] ile rastgele erişime (random access) izin verir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2317, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::deque, sadece sona ekleme (push_back) destekler, başa ekleme desteklemez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: deque push_front() ile başa eklemeyi de destekler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2318, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::deque üzerinde range-for döngüsüyle gezinmek mümkündür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2319, .topicId = 88,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::deque, elemanları otomatik olarak sıralı (artan) tutar (std::set gibi).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: deque elemanları ekleme sırasına göre tutar, otomatik sıralamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2320, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Hem başa hem sona ekleme/çıkarma yapılabilen çift uçlu kuyruğa _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"deque"},
        .explanation = "Bu yapıya deque denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2321, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::deque<int> d;\nd.push_back(5);\nstd::cout << d[0];\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "d[0], tek eleman olan 5'e erişir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2322, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "deque'nin başına eleman eklemek için kullanılan üye fonksiyon _____ dir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"push_front"},
        .explanation = "push_front() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2323, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d;\nd.push_back(1);\nd.push_front(2);\nstd::cout << d[0] << d[1];\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"21"},
        .explanation = "push_front(2) sonrası deque [2,1] olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2324, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "deque'nin sonundan eleman çıkarmak için kullanılan üye fonksiyon _____ dir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"pop_back"},
        .explanation = "pop_back() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2325, .topicId = 88,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::deque, hem push_back/push_front hem de operator[] ile _____ erişime izin verir (İngilizce iki kelime).",
        .acceptedAnswers = {"random access"},
        .explanation = "deque, random access destekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2326, .topicId = 88,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nd.push_back(1);\nd adlı bir int deque'si tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::deque<int> d;"},
        .explanation = "std::deque<int> ile bir int deque'si tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2327, .topicId = 88,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d;\nd.push_back(2);\n_____\nd'nin başına 1 ekleyen satırı yazın.",
        .acceptedAnswers = {"d.push_front(1);"},
        .explanation = "push_front(1), 1'i başa ekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2328, .topicId = 88,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::deque<int> d;\nd.push_back(7);\nd.push_back(8);\nd.push_front(6);\nfor (int x : d) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"678"},
        .explanation = "push_front(6), 6'yı başa ekler: [6,7,8].",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2329, .topicId = 88,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::deque<int> d = {1,2,3,4};\nd.pop_front();\nd.push_back(5);\nfor (int x : d) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2345"},
        .explanation = "pop_front() 1'i kaldırır, push_back(5) 5'i ekler: [2,3,4,5].",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2330, .topicId = 88,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::deque<int> d;\nd.push_back(1);\nd.push_front(2);\nstd::cout << d.first;\n\nBu kod derlenmez çünkü std::deque'nin .first üye değişkeni yoktur (bu pair'e özgüdür). Hatalı satırı, deque'nin ilk elemanına doğru şekilde erişerek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << d[0];"},
        .explanation = "deque elemanlarına operator[] ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2331, .topicId = 88,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::deque<int> d;\nd.push_back(1);\nd.push(2);\n\nBu kod derlenmez çünkü std::deque'nin push() üye fonksiyonu yoktur (bu stack/queue'ya özgüdür); deque'de push_back()/push_front() kullanılır. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"d.push_back(2);"},
        .explanation = "deque'de push_back()/push_front() kullanılır, push() değil.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2332, .topicId = 88,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::deque<int> d\nd.push_back(1);\n\nProgramcı d tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::deque<int> d;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2333, .topicId = 88,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir deque tanımlayıp elemanlarını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"for (int x : d) { std::cout << x; }\n    return 0;\n}", "std::deque<int> d;\n    d.push_back(2);\n    d.push_front(1);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+ekleme (2), döngü+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2334, .topicId = 88,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int deque'si tanımlayın; başa ve sona birer değer ekleyin (push_front/push_back) ve for döngüsüyle tüm elemanları ekrana yazdırın.",
        .acceptedAnswers = {"deque", "push_front", "push_back"},
        .explanation = "deque, hem başa hem sona ekleme ve tam iterasyon destekler.",
        .baseXp = 40,
    });

    // Topic 89: priority_queue
    questions.push_back(Question{
        .id = 2335, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::priority_queue<T>, varsayılan olarak nasıl davranır?",
        .options = {"Min-heap gibi davranır, en küçük elemanı verir", "Max-heap gibi davranır, en büyük elemanı verir", "FIFO sırayla davranır", "Elemanları ekleme sırasıyla verir"},
        .acceptedAnswers = {"b"},
        .explanation = "priority_queue varsayılan olarak max-heap gibi davranır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2336, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::priority_queue<int> pq;\npq.push(4);\npq.push(9);\npq.push(1);\nstd::cout << pq.top();\nEkran çıktısı nedir?",
        .options = {"4", "1", "9", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "top(), varsayılan olarak en büyük elemanı (9) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2337, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::priority_queue'da top(), hangi elemanı verir?",
        .options = {"İlk eklenen elemanı", "Son eklenen elemanı", "En küçük elemanı (varsayılan olarak)", "En büyük elemanı (varsayılan olarak)"},
        .acceptedAnswers = {"d"},
        .explanation = "top(), varsayılan olarak en büyük elemanı verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2338, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue<int> pq;\npq.push(5);\npq.push(2);\npq.push(8);\npq.pop();\nstd::cout << pq.top();\nEkran çıktısı nedir?",
        .options = {"5", "2", "8", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "pop(), en büyük elemanı (8) kaldırır; kalan en büyük 5 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2339, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Min-heap davranışı (en küçük elemanı top() ile almak) için ne kullanılmalıdır?",
        .options = {"std::priority_queue<T> (varsayılan haliyle)", "std::priority_queue<T, std::vector<T>, std::greater<T>>", "std::priority_queue<T, std::vector<T>, std::less<T>>", "std::stack<T>"},
        .acceptedAnswers = {"b"},
        .explanation = "std::greater<T> üçüncü şablon argümanı min-heap davranışı sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2340, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue, begin()/end() sunar mı?",
        .options = {"Evet, tam iterasyon desteklenir", "Sadece begin() sunar", "Hayır, stack/queue gibi iterasyon desteklemez", "Sadece end() sunar"},
        .acceptedAnswers = {"c"},
        .explanation = "priority_queue, diğer konteyner adaptörleri gibi iterasyon desteklemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2341, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::priority_queue<int> pq;\npq.push(3);\npq.push(7);\npq.push(1);\npq.push(9);\nstd::cout << pq.top();\npq.pop();\nstd::cout << \" \" << pq.top();\npq.pop();\nstd::cout << \" \" << pq.top();\nEkran çıktısı nedir?",
        .options = {"3 7 9", "1 3 7", "9 1 3", "9 7 3"},
        .acceptedAnswers = {"d"},
        .explanation = "top()/pop() sırasıyla en büyükten küçüğe doğru verir: 9, 7, 3.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2342, .topicId = 89,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::priority_queue<int, std::vector<int>, std::greater<int>> pq;\npq.push(5);\npq.push(1);\npq.push(9);\nstd::cout << pq.top();\nEkran çıktısı nedir?",
        .options = {"1", "9", "5", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "std::greater<int> ile min-heap davranışı: top() en küçüğü (1) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2343, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::priority_queue, varsayılan olarak bir max-heap gibi davranır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2344, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::priority_queue'da top(), varsayılan olarak en küçük elemanı verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan olarak en büyük elemanı verir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2345, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Min-heap davranışı için std::greater<T> üçüncü şablon argümanı olarak verilmelidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2346, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::priority_queue, begin()/end() sunar ve iterasyona izin verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: priority_queue iterasyon desteklemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2347, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue'da pop(), en yüksek öncelikli (varsayılan olarak en büyük) elemanı kaldırır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2348, .topicId = 89,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue, elemanları ekleme sırasında tutar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: elemanlar öncelik sırasına (varsayılan olarak büyükten küçüğe) göre tutulur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2349, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Varsayılan olarak max-heap gibi davranan konteyner adaptörüne _____ denir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"priority_queue"},
        .explanation = "Bu adaptöre priority_queue denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2350, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::priority_queue<int> pq;\npq.push(3);\npq.push(8);\nstd::cout << pq.top();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "top(), en büyük elemanı (8) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2351, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "priority_queue'da en yüksek öncelikli elemanı (kaldırmadan) döndüren üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"top"},
        .explanation = "top() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2352, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Min-heap davranışı için üçüncü şablon argümanı olarak std::_____ kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"greater"},
        .explanation = "std::greater<T> kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2353, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue<int> pq;\npq.push(2); pq.push(7); pq.push(4);\npq.pop();\nstd::cout << pq.top();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"4"},
        .explanation = "pop(), en büyük (7) elemanı kaldırır; kalan en büyük 4 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2354, .topicId = 89,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "priority_queue, std::stack/std::queue gibi begin()/end() _____ (Türkçe kelime, 'sunmaz' anlamında).",
        .acceptedAnswers = {"sunmaz"},
        .explanation = "priority_queue iterasyon desteklemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2355, .topicId = 89,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\npq.push(5);\npq adlı bir int priority_queue'su tanımlayan satırı yazın.",
        .acceptedAnswers = {"std::priority_queue<int> pq;"},
        .explanation = "std::priority_queue<int> ile tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2356, .topicId = 89,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue<int> pq;\npq.push(3);\npq.push(9);\n_____\nen büyük elemanı ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << pq.top();"},
        .explanation = "top(), en büyük elemanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2357, .topicId = 89,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::priority_queue<int> pq;\npq.push(6);\npq.push(2);\npq.push(10);\nstd::cout << pq.top();\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "top(), en büyük elemanı (10) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2358, .topicId = 89,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::priority_queue<int> pq;\npq.push(4);\npq.push(1);\npq.push(7);\nint toplam = 0;\nwhile (!pq.empty()) {\n    toplam += pq.top();\n    pq.pop();\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "4 + 1 + 7 = 12.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2359, .topicId = 89,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::priority_queue<int> pq;\npq.push(3);\nfor (int x : pq) { std::cout << x; }\n\nBu kod derlenmez çünkü std::priority_queue'nun begin()/end() tanımı yoktur. Hatalı satırı, top() kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << pq.top();"},
        .explanation = "priority_queue elemanlarına top()/pop() ile erişilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2360, .topicId = 89,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::priority_queue<int> pq;\npq.push(5);\npq.push(1);\npq.push(9);\nstd::cout << pq.top();\n// Beklenen: en küçük eleman (1)\n\nBu kod, en küçük elemanı DEĞİL en büyük elemanı (9) verir çünkü std::priority_queue VARSAYILAN olarak max-heap'tir; min-heap için üçüncü şablon argümanı olarak std::greater<int> belirtilmelidir. Hatalı tanım satırını düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::priority_queue<int, std::vector<int>, std::greater<int>> pq;"},
        .explanation = "std::greater<int> ile min-heap davranışı elde edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2361, .topicId = 89,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::priority_queue<int> pq\npq.push(5);\n\nProgramcı pq tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::priority_queue<int> pq;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2362, .topicId = 89,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir priority_queue tanımlayıp en büyük elemanı yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << pq.top();\n    return 0;\n}", "std::priority_queue<int> pq;\n    pq.push(4);\n    pq.push(12);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+ekleme (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2363, .topicId = 89,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int priority_queue'su tanımlayın; üç değer push edin ve top()/pop() kullanarak elemanları büyükten küçüğe ekrana yazdırın.",
        .acceptedAnswers = {"priority_queue", "push", "pop"},
        .explanation = "priority_queue, varsayılan olarak büyükten küçüğe erişim sağlar.",
        .baseXp = 40,
    });

    // Topic 90: Iterator
    questions.push_back(Question{
        .id = 2364, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Iterator (begin()/end()) kavramının amacı nedir?",
        .options = {"Bir konteyneri sıralamak", "Bir konteynerin boyutunu değiştirmek", "Herhangi bir STL konteynerini tek tip bir şekilde gezmenin (traverse etmenin) yolunu sağlamak", "Bir fonksiyonu virtual yapmak"},
        .acceptedAnswers = {"c"},
        .explanation = "Iterator'lar, konteynerleri tek tip bir şekilde gezmeyi sağlar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2365, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1,2,3};\nauto it = v.begin();\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"3", "0", "Derleme hatası", "1"},
        .acceptedAnswers = {"d"},
        .explanation = "begin(), ilk elemanı (1) gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2366, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "v.end(), neyi gösterir?",
        .options = {"Son elemandan SONRAKİ (var olmayan) konumu", "Son elemanın kendisini", "İlk elemanı", "v'nin boyutunu"},
        .acceptedAnswers = {"a"},
        .explanation = "end(), son elemandan sonraki (var olmayan) konumu gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2367, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "for (int x : v) döngüsü ile for (auto it = v.begin(); it != v.end(); ++it) döngüsü arasındaki ilişki nedir?",
        .options = {"Birbirinden tamamen farklı, farklı sonuçlar üretirler", "range-for, açık iterator döngüsünün kısa yazımıdır (syntactic sugar), aynı çıktıyı üretir", "range-for daha yavaş çalışır", "Sadece range-for derlenir, diğeri derlenmez"},
        .acceptedAnswers = {"b"},
        .explanation = "range-for, iterator döngüsünün syntactic sugar'ıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2368, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {5, 10, 15};\nauto it = v.begin();\n++it;\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"5", "15", "10", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "begin() ilk elemanı (5) gösterir; ++it ikinci elemana (10) ilerler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2369, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "*v.end() ifadesini okumaya çalışmak ne tür bir sorundur?",
        .options = {"Derleme hatasıdır", "Her zaman 0 döndürür", "Otomatik olarak son elemanı döndürür", "Tanımsız davranıştır (undefined behavior); derleme hatası DEĞİLDİR"},
        .acceptedAnswers = {"d"},
        .explanation = "*v.end(), tanımsız davranıştır; derleme hatası değildir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2370, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1,2,3,4};\nint toplam = 0;\nfor (auto it = v.begin(); it != v.end(); ++it) {\n    toplam += *it;\n}\nstd::cout << toplam;\nEkran çıktısı nedir?",
        .options = {"10", "4", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "1 + 2 + 3 + 4 = 10.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2371, .topicId = 90,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {2,4,6};\nfor (auto it = v.begin(); it != v.end(); ++it) { std::cout << *it; }\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"246642", "246246", "642642", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Her iki döngü de aynı sırayla aynı elemanları yazdırır: 246246.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2372, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Iterator'lar, STL konteynerlerini tek tip bir şekilde gezmenin yoludur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2373, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "v.end(), konteynerin gerçek son elemanını gösterir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: end(), son elemandan sonraki (var olmayan) konumu gösterir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2374, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "range-for döngüsü, açık bir iterator döngüsünün kısa yazımıdır (syntactic sugar).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2375, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "*v.end() ifadesini okumak bir derleme hatasıdır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: derleme hatası değil, tanımsız davranıştır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2376, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir iterator'a ++ uygulamak, onu bir sonraki elemana ilerletir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2377, .topicId = 90,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "range-for döngüsü ve açık iterator döngüsü, aynı konteyner üzerinde FARKLI sırayla gezinir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: ikisi de aynı sırayla gezinir, çıktıları aynıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2378, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir konteynerin ilk elemanını gösteren iterator'ı döndüren üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"begin"},
        .explanation = "begin() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2379, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {7,8,9};\nauto it = v.begin();\nstd::cout << *it;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "begin(), ilk elemanı (7) gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2380, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir iterator'ın gösterdiği elemana erişmek için kullanılan operatör _____ dir (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "Dereference operatörü (*) kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2381, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Son elemandan SONRAKİ (var olmayan) konumu gösteren iterator'ı döndüren üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"end"},
        .explanation = "end() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2382, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "*v.end() ile bu konumu okumaya çalışmak _____ davranıştır (Türkçe iki kelime, 'tanımsız davranış' anlamında).",
        .acceptedAnswers = {"tanımsız davranış", "tanımsız"},
        .explanation = "Bu, tanımsız davranıştır (UB).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2383, .topicId = 90,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {3,6,9};\nauto it = v.begin();\n++it;\n++it;\nstd::cout << *it;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"9"},
        .explanation = "begin() -> 3, ++it -> 6, ++it -> 9.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2384, .topicId = 90,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << *it;\nv adlı bir vektörün ilk elemanını gösteren it adlı bir iterator tanımlayan satırı yazın.",
        .acceptedAnswers = {"auto it = v.begin();"},
        .explanation = "begin(), ilk elemanı gösteren iterator'ı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2385, .topicId = 90,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1,2,3};\nfor (auto it = v.begin(); it != v.end(); ++it) {\n_____\n}\nit'nin gösterdiği elemanı ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << *it;"},
        .explanation = "*it, iterator'ın gösterdiği elemana erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2386, .topicId = 90,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4,8,12};\nfor (auto it = v.begin(); it != v.end(); ++it) {\n    std::cout << *it << \" \";\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4 8 12 "},
        .explanation = "Her eleman sırasıyla yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2387, .topicId = 90,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1,2,3};\nint carpim = 1;\nfor (auto it = v.begin(); it != v.end(); ++it) {\n    carpim *= *it;\n}\nstd::cout << carpim;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6"},
        .explanation = "1 * 2 * 3 = 6.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2388, .topicId = 90,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1,2,3};\nstd::cout << *v.end();\n\nBu kod derlenir AMA tanımsız davranışa (undefined behavior) yol açar çünkü v.end(), gerçek bir elemanı göstermez (son elemandan bir sonraki konumdur); bu konumu dereference etmek TANIMSIZDIR. v'nin GERÇEK son elemanına erişen doğru satırı yazın.",
        .acceptedAnswers = {"std::cout << v.back();"},
        .explanation = "v.back(), konteynerin gerçek son elemanına erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2389, .topicId = 90,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1,2,3};\nfor (auto it = v.begin(); it != v.end(); it) {\n    std::cout << *it;\n}\n\nBu kod SONSUZ DÖNGÜYE girer çünkü it, döngü içinde HİÇBİR ZAMAN artırılmıyor (++it eksik); it != v.end() koşulu hep doğru kalır. Hatalı for satırını düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (auto it = v.begin(); it != v.end(); ++it) {"},
        .explanation = "++it eklenmeden döngü asla sonlanmaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2390, .topicId = 90,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {1,2,3};\nauto it = v.begin()\nstd::cout << *it;\n\nProgramcı it tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"auto it = v.begin();"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2391, .topicId = 90,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektör tanımlayıp iterator ile ilk elemanını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"auto it = v.begin();\n    std::cout << *it;\n    return 0;\n}", "std::vector<int> v = {5, 10, 15};", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), vektör tanımı (2), iterator+yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2392, .topicId = 90,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın; hem açık bir iterator döngüsüyle (begin()/end()) hem de bir range-for döngüsüyle tüm elemanlarını ekrana yazdırın.",
        .acceptedAnswers = {"begin", "end", "for"},
        .explanation = "İki döngü de aynı elemanları aynı sırayla yazdırır.",
        .baseXp = 40,
    });
}
```

- [ ] **Step 2: Add a per-topic minimum-count test**

In `tests/QuestionManagerTests.cpp`, add this new test case right after
`QuestionManager_EveryTopicSeventyOneToEightyHasAtLeastTwentyNineQuestions`
(do not modify that existing test, and do not touch
`QuestionManager_NoDuplicateQuestionIds`, which already scans topics
1-100):

```cpp
TEST_CASE(QuestionManager_EveryTopicEightyOneToNinetyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 81; topicId <= 90; ++topicId) {
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
Expected: `96/96 test(s) passed.` (95 from Task 1's end state + 1 new
test).

Run from `build/`: `ctest -C Debug --output-on-failure`
Expected: 100% pass.

- [ ] **Step 4: Manual verification — topic 84 end-to-end**

Run the app (`./build/Debug/CppMasterConsole.exe`), navigate to the
topic browser, choose Section 9, choose topic 84 ("map"):

1. Confirm the lesson text prints (matches the `explanation`/`syntax`/
   `exampleCode` written in Task 1) — proving `openTopic`'s content gate
   passes for topic 84 with zero `Application.cpp` changes.
2. Confirm "Konu testi başlıyor (29 soru)." prints.
3. Answer a few questions, then use `cikis` to return to the main menu.
4. Confirm the app returns to the main menu without crashing, and that
   partial XP is awarded.
5. Clean up: `rm -f data/*.txt`.

- [ ] **Step 5: Commit the question content and test changes**

```bash
git add src/QuestionsSection9.cpp tests/QuestionManagerTests.cpp
git commit -m "feat(content): add questions for topics 88-90 (ids 2306-2392), widen coverage tests"
```

- [ ] **Step 6: Update the roadmap**

In `docs/superpowers/roadmap.md`, add a new bullet for Phase 20 under
"Phase order," immediately after the Phase 19 entry, following the
EXACT format Phases 8-19 use
(`**Phase N — name: COMPLETE** (commits \`X..Y\`, ...)`), with the
commit range starting at this phase's spec commit (the commit for "Add
design spec for Bölüm 9 İçerik Genişletmesi (phase 20)") and ending at
this task's final content commit (from Step 5 above). Update the
"Status" section to say Phase 20 is complete and Phase 21 (Section 10
content, the final content-expansion phase) starts next.

Then commit:

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 20 complete in roadmap"
```

---

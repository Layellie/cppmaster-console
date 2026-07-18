# Bölüm 10 İçerik Genişletmesi (Phase 21) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add full lesson content and a 290-question bank for Section 10
(topics 91-100, "STL algoritmaları, dosya işlemleri, istisna yönetimi
ve akıllı işaretçiler"), following the identical architecture used in
Phases 13-20. This is the LAST of nine content-expansion phases — once
it lands, all 100 topics have real lesson content and >= 29 questions
each.

**Architecture:** One new `applySection10LessonContent` function in
`src/LessonContentSection10.cpp`, one new `appendSection10Questions`
function in `src/QuestionsSection10.cpp`, both wired into the existing
`LessonManager`/`QuestionManager` constructors after the Phase 20
calls.

**Tech Stack:** C++20, CMake, the project's own minimal test framework
(`TEST_CASE`/`CHECK`).

## Global Constraints

- Ids for this phase's questions: 2393-2682 (10 topics x 29 questions
  each), continuing directly from Phase 20's last id (2392). This is
  the FINAL id range for the 100-topic bank.
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
  matching the 0-indexed `options` position — continuing Phase 20's
  fix, the correct option's position MUST be varied across a/b/c/d
  (roughly evenly), NOT always "a" (the Sections 6-8 defect). `TrueFalse`
  has no `options` field; `{"1"}` = true, `{"2"}` = false.
  `OrderCode.acceptedAnswers` is 1-indexed positions space-separated,
  and MUST be verified (by actually assembling and compiling — and for
  any case involving execution order, running — the resulting program)
  to produce the correct, intended runtime behavior.
- **`std::sort(first, last)`** sorts ascending by default (`operator<`);
  a third comparator argument (function/lambda/`std::greater<T>`)
  changes the order (e.g. descending).
- **`std::reverse(first, last)`** reverses a range IN PLACE and returns
  `void` — no return value to capture.
- **`std::find(first, last, value)`** returns an iterator to the first
  match, or `last` if not found; dereferencing the result without
  first checking it against `end()` is undefined behavior when the
  value is absent.
- **`std::count(first, last, value)`** returns the NUMBER of matches
  (0 if none) — not an iterator, not a bool.
- **`std::max_element`/`std::min_element` return an ITERATOR** to the
  largest/smallest element in a range — NOT the value; must be
  dereferenced (`*std::max_element(...)`). By contrast, the two-value
  overloads **`std::max(a, b)`/`std::min(a, b)` return a value
  directly**, not an iterator.
- **`std::accumulate(first, last, init)`** (from `<numeric>`) sums a
  range starting from `init`; **the TYPE of `init` determines the
  accumulation's working type** — an `int` init (e.g. `0`) accumulating
  a `double` range truncates every partial sum to `int`, producing a
  silently WRONG total; a `double` init (e.g. `0.0`) is correct.
- **`std::ofstream`** opens a file for writing and, by default,
  TRUNCATES any existing content unless opened with `std::ios::app`.
  Always check `.is_open()` before writing — a failed open makes
  writes silently do nothing (no exception by default).
- **`std::ifstream`** opens a file for reading; `std::getline(stream,
  line)` reads a full line, `stream >> variable` reads one
  whitespace-delimited token. Reading past EOF puts the stream in a
  fail state (checkable, e.g. `if (stream)`), it does not throw.
- **`try`/`catch`**: catch by `const&` to avoid object slicing; catch
  blocks are tried in the WRITTEN order, so a more general `catch(...)`
  placed before a more specific type silently intercepts everything
  after it. Uncaught exceptions propagate up the call stack.
- **`std::unique_ptr<T>`** has exclusive ownership: it CANNOT be
  copied (copy ctor/assignment deleted — genuine compile error), only
  MOVED (`std::move`, leaving the source null). It auto-deletes its
  owned object on scope exit (RAII). `.get()` returns the raw pointer
  without transferring ownership.
- No `Application.cpp` changes are needed — `openTopic`/`runTopicQuiz`
  already activate any topic generically once it has non-empty lesson
  content and >= 1 question.
- This phase's Task 1 REMOVES the "topics without content" test
  entirely (not narrows its range to empty) — see Task 1 Step 5 for
  the exact reasoning and diff.

---

### Task 1: Section 10 lesson content

**Files:**
- Modify: `src/LessonContent.h` (add one new declaration)
- Create: `src/LessonContentSection10.cpp`
- Modify: `src/LessonManager.cpp` (include already present; add one call)
- Modify: `CMakeLists.txt` (add the new `.cpp` to the lib target sources,
  matching how `LessonContentSection9.cpp` is registered)
- Modify: `tests/LessonManagerTests.cpp` (widen one test, REMOVE the other)

**Interfaces:**
- Produces: `void applySection10LessonContent(std::vector<Lesson>& lessons);`
  writing into `lessons[90]` through `lessons[99]` (topics 91-100).

- [ ] **Step 1: Add the new declaration**

In `src/LessonContent.h`, add this line after the existing
`applySection9LessonContent` declaration (do not remove that one):

```cpp
void applySection10LessonContent(std::vector<Lesson>& lessons);
```

- [ ] **Step 2: Write the lesson content**

Create `src/LessonContentSection10.cpp` with exactly this content:

```cpp
#include "LessonContent.h"

#include "Lesson.h"

void applySection10LessonContent(std::vector<Lesson>& lessons) {
    // Index 90 = topic id 91 (sort()), index 99 = topic id 100
    // (unique_ptr) — same positional convention as
    // applyIntroLessonContent/applySection2-9LessonContent.

    lessons[90].explanation =
        "std::sort(first, last), bir aralığı VARSAYILAN olarak ARTAN "
        "sırada (operator< kullanarak) sıralar. Üçüncü bir argüman "
        "olarak özel bir karşılaştırma fonksiyonu, lambda ya da "
        "std::greater<T>() verilirse, sıralama o kritere göre (örneğin "
        "AZALAN sırada) yapılır.";
    lessons[90].syntax = "std::sort(konteyner.begin(), konteyner.end());";
    lessons[90].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n"
        "#include <algorithm>\n\n"
        "int main() {\n"
        "    std::vector<int> v = {5, 2, 8, 1};\n"
        "    std::sort(v.begin(), v.end());\n"
        "    for (int x : v) {\n"
        "        std::cout << x << \" \";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[90].lineExplanations = {
        "std::vector<int> v = {5, 2, 8, 1}; : v, sırasız bir int "
        "listesidir.",
        "std::sort(v.begin(), v.end()); : v'yi, varsayılan olarak "
        "artan sırada (operator< kullanarak) SIRALAR (in-place).",
        "for (int x : v) : sıralanmış hali yazdırılır: 1 2 5 8."};
    lessons[90].commonMistakes = {
        "std::sort, VARSAYILAN olarak ARTAN sırada sıralar; AZALAN "
        "(büyükten küçüğe) sıralama için üçüncü argüman olarak "
        "std::greater<int>() ya da özel bir karşılaştırma fonksiyonu/"
        "lambda verilmelidir."};

    lessons[91].explanation =
        "std::reverse(first, last), bir aralığın elemanlarının "
        "sırasını YERİNDE (in-place) TERSİNE ÇEVİRİR ve bir değer "
        "DÖNDÜRMEZ (void). Fonksiyon çağrısından sonra, orijinal "
        "konteynerin kendisi değişmiş olur.";
    lessons[91].syntax = "std::reverse(konteyner.begin(), konteyner.end());";
    lessons[91].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n"
        "#include <algorithm>\n\n"
        "int main() {\n"
        "    std::vector<int> v = {1, 2, 3};\n"
        "    std::reverse(v.begin(), v.end());\n"
        "    for (int x : v) {\n"
        "        std::cout << x << \" \";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[91].lineExplanations = {
        "std::vector<int> v = {1, 2, 3}; : v, başlangıçta 1,2,3 "
        "sırasındadır.",
        "std::reverse(v.begin(), v.end()); : v'nin elemanlarının "
        "sırasını YERİNDE (in-place) TERSİNE ÇEVİRİR; bir değer "
        "DÖNDÜRMEZ (void).",
        "for (int x : v) : ters çevrilmiş hali yazdırılır: 3 2 1."};
    lessons[91].commonMistakes = {
        "std::reverse void döndürür; dönüş değerini bir değişkene "
        "atamaya çalışmak (örn. auto sonuc = std::reverse(...);) "
        "derleme hatasıdır. v'nin KENDİSİ değiştirilir, yeni bir "
        "konteyner oluşturulmaz."};

    lessons[92].explanation =
        "std::find(first, last, deger), bir aralıkta deger'i arar; "
        "bulursa o elemanı gösteren bir ITERATOR, bulamazsa last "
        "(genellikle konteynerin end()'i) döndürür. Sonucun last'a "
        "(end()'e) eşit olup olmadığını kontrol etmek, bulunup "
        "bulunmadığını anlamanın DOĞRU yoludur.";
    lessons[92].syntax = "auto it = std::find(konteyner.begin(), konteyner.end(), deger);";
    lessons[92].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n"
        "#include <algorithm>\n\n"
        "int main() {\n"
        "    std::vector<int> v = {4, 7, 2, 9};\n"
        "    auto it = std::find(v.begin(), v.end(), 7);\n"
        "    if (it != v.end()) {\n"
        "        std::cout << \"bulundu: \" << *it;\n"
        "    } else {\n"
        "        std::cout << \"bulunamadi\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[92].lineExplanations = {
        "auto it = std::find(v.begin(), v.end(), 7); : v içinde 7 "
        "değerini arar; bulursa o elemanı gösteren bir iterator, "
        "bulamazsa v.end() döndürür.",
        "if (it != v.end()) : bulunup bulunmadığını kontrol etmenin "
        "doğru yoludur.",
        "*it : bulunan elemanın değerine (7) erişir; SADECE it != "
        "v.end() DOĞRUYSA güvenlidir."};
    lessons[92].commonMistakes = {
        "std::find sonucunu it != v.end() ile kontrol ETMEDEN *it ile "
        "dereference etmek, değer bulunamadığında (it == v.end() "
        "olduğunda) TANIMSIZ DAVRANIŞTIR (undefined behavior)."};

    lessons[93].explanation =
        "std::count(first, last, deger), bir aralıkta deger'e eşit "
        "elemanların SAYISINI döndürür — bir iterator ya da true/false "
        "DEĞİL, bir tam sayıdır. Hiç eşleşme yoksa 0 döner, hata "
        "vermez.";
    lessons[93].syntax = "int sayi = std::count(konteyner.begin(), konteyner.end(), deger);";
    lessons[93].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n"
        "#include <algorithm>\n\n"
        "int main() {\n"
        "    std::vector<int> v = {3, 5, 3, 3, 8};\n"
        "    int sayi = std::count(v.begin(), v.end(), 3);\n"
        "    std::cout << sayi;\n"
        "    return 0;\n"
        "}";
    lessons[93].lineExplanations = {
        "std::vector<int> v = {3, 5, 3, 3, 8}; : v içinde 3 değeri "
        "ÜÇ kez geçiyor.",
        "std::count(v.begin(), v.end(), 3); : v içindeki 3 değerine "
        "eşit elemanların SAYISINI (3) döndürür — bir iterator ya da "
        "bool DEĞİL.",
        "std::cout << sayi; : 3 yazdırılır."};
    lessons[93].commonMistakes = {
        "std::count, bir iterator ya da true/false DEĞİL, eşleşen "
        "eleman SAYISINI (bir tam sayı) döndürür; hiç eşleşme yoksa 0 "
        "döner (hata vermez)."};

    lessons[94].explanation =
        "İki değer arasından büyük/küçük olanı almak için std::max(a, "
        "b)/std::min(a, b) kullanılır ve bunlar DOĞRUDAN BİR DEĞER "
        "döndürür. Bir ARALIKTAKİ en büyük/en küçük elemanı bulmak "
        "için ise std::max_element(first, last)/std::min_element(first, "
        "last) kullanılır — ANCAK bunlar değerin kendisini DEĞİL, o "
        "elemanı gösteren bir ITERATOR döndürür; gerçek değere erişmek "
        "için * ile dereference edilmelidir.";
    lessons[94].syntax = "std::max(a, b); // deger dondurur\nstd::max_element(konteyner.begin(), konteyner.end()); // iterator dondurur";
    lessons[94].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n"
        "#include <algorithm>\n\n"
        "int main() {\n"
        "    std::cout << std::max(3, 7) << \" \";\n"
        "    std::vector<int> v = {4, 9, 2, 6};\n"
        "    auto it = std::max_element(v.begin(), v.end());\n"
        "    std::cout << *it;\n"
        "    return 0;\n"
        "}";
    lessons[94].lineExplanations = {
        "std::max(3, 7) : iki DEĞERDEN büyük olanı (7) doğrudan "
        "DÖNDÜRÜR (bir iterator değil).",
        "auto it = std::max_element(v.begin(), v.end()); : v "
        "aralığındaki EN BÜYÜK elemanı gösteren bir ITERATOR döndürür "
        "— değerin kendisini değil.",
        "*it : max_element'in döndürdüğü iterator'ı dereference "
        "ederek gerçek değere (9) erişir."};
    lessons[94].commonMistakes = {
        "std::max_element/std::min_element bir ITERATOR döndürür, "
        "değerin kendisini DEĞİL; sonucu doğrudan yazdırmaya çalışmak "
        "(std::cout << std::max_element(...);) bir DERLEME HATASIDIR "
        "(vector iterator'ı için operator<< tanımlı değildir) — "
        "mutlaka * ile dereference edilmelidir. Buna karşılık iki "
        "argümanlı std::max(a, b)/std::min(a, b) DOĞRUDAN bir değer "
        "döndürür."};

    lessons[95].explanation =
        "std::accumulate(first, last, baslangicDegeri) (<numeric> "
        "başlığından), bir aralığı baslangicDegeri'nden başlayarak "
        "TOPLAR. baslangicDegeri'nin TÜRÜ, toplama işleminin çalışma "
        "türünü BELİRLER: bir double listesine int (örn. 0) "
        "başlangıç değeri vermek, ARA TOPLAMLARIN HER ADIMDA int'e "
        "KIRPILMASINA (truncate) ve YANLIŞ bir sonuca yol açar; "
        "doğrusu, konteynerin eleman türüyle EŞLEŞEN bir başlangıç "
        "değeri (örn. 0.0) kullanmaktır.";
    lessons[95].syntax = "#include <numeric>\nauto toplam = std::accumulate(konteyner.begin(), konteyner.end(), baslangicDegeri);";
    lessons[95].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n"
        "#include <numeric>\n\n"
        "int main() {\n"
        "    std::vector<double> v = {1.5, 2.5, 3.0};\n"
        "    auto toplamYanlis = std::accumulate(v.begin(), v.end(), 0);\n"
        "    auto toplamDogru = std::accumulate(v.begin(), v.end(), 0.0);\n"
        "    std::cout << toplamYanlis << \" \" << toplamDogru;\n"
        "    return 0;\n"
        "}";
    lessons[95].lineExplanations = {
        "auto toplamYanlis = std::accumulate(v.begin(), v.end(), 0); : "
        "başlangıç değeri 0 bir int OLDUĞUNDAN, toplama işlemi HER "
        "ADIMDA int'e KIRPILIR (truncate); sonuç YANLIŞ çıkar (6, "
        "gerçek toplam 7 iken).",
        "auto toplamDogru = std::accumulate(v.begin(), v.end(), 0.0); : "
        "başlangıç değeri 0.0 bir double OLDUĞUNDAN, toplama doğru "
        "şekilde double olarak yapılır; sonuç DOĞRU (7) çıkar.",
        "std::cout << toplamYanlis << \" \" << toplamDogru; : yanlış "
        "(6) ve doğru (7) sonuçlar karşılaştırmalı olarak yazdırılır."};
    lessons[95].commonMistakes = {
        "std::accumulate'in üçüncü argümanının (başlangıç değeri) "
        "TÜRÜ, toplama işleminin türünü belirler; bir double listesine "
        "int (0 gibi) başlangıç değeri vermek, ARA TOPLAMLARIN her "
        "adımda int'e kırpılmasına ve YANLIŞ bir sonuca yol açar. "
        "Doğrusu, konteynerin eleman türüyle EŞLEŞEN bir başlangıç "
        "değeri (örn. 0.0) kullanmaktır."};

    lessons[96].explanation =
        "std::ofstream (<fstream> başlığından), bir dosyayı YAZMA "
        "modunda açar. Dosya ZATEN VARSA, VARSAYILAN olarak İÇERİĞİNİ "
        "SİLER (truncate); var olan içeriğin SONUNA eklemek için "
        "std::ios::app modu belirtilmelidir. Yazmadan ÖNCE .is_open() "
        "ile dosyanın gerçekten açılıp açılamadığı kontrol edilmelidir "
        "— açma başarısız olursa yazma SESSİZCE hiçbir şey yapmaz "
        "(istisna FIRLATMAZ).";
    lessons[96].syntax = "#include <fstream>\nstd::ofstream dosya(\"dosyaAdi.txt\");\ndosya << \"metin\";\ndosya.close();";
    lessons[96].exampleCode =
        "#include <iostream>\n"
        "#include <fstream>\n\n"
        "int main() {\n"
        "    std::ofstream dosya(\"cikti.txt\");\n"
        "    if (dosya.is_open()) {\n"
        "        dosya << \"Merhaba Dunya\";\n"
        "        dosya.close();\n"
        "        std::cout << \"yazildi\";\n"
        "    } else {\n"
        "        std::cout << \"acilamadi\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[96].lineExplanations = {
        "std::ofstream dosya(\"cikti.txt\"); : \"cikti.txt\" dosyasını "
        "YAZMA modunda açar; dosya zaten varsa İÇERİĞİNİ SİLER "
        "(varsayılan olarak KIRPAR/truncate).",
        "if (dosya.is_open()) : dosyanın GERÇEKTEN açılıp açılamadığını "
        "kontrol eder; açma başarısız olursa is_open() false döner ve "
        "dosyaya yazmak SESSİZCE hiçbir şey yapmaz (istisna FIRLATMAZ).",
        "dosya << \"Merhaba Dunya\"; dosya.close(); : metni dosyaya "
        "yazar ve dosyayı kapatır (kaynakları serbest bırakır)."};
    lessons[96].commonMistakes = {
        "std::ofstream ile bir dosya açmak, dosya ZATEN VARSA "
        "içeriğini VARSAYILAN OLARAK SİLER (truncate); var olan "
        "içeriğin SONUNA eklemek için std::ofstream dosya(\"ad.txt\", "
        "std::ios::app); kullanılmalıdır."};

    lessons[97].explanation =
        "std::ifstream (<fstream> başlığından), bir dosyayı OKUMA "
        "modunda açar. std::getline(dosya, satir), dosyadan TAM BİR "
        "SATIRI (boşluklar dahil) okur; dosya >> degisken ise SADECE "
        "bir sonraki BOŞLUKLA AYRILMIŞ TOKEN'ı okur. Dosyanın SONUNA "
        "(EOF) ulaşıldıktan sonra okumaya devam etmeye çalışmak, "
        "akışı BAŞARISIZ (fail) duruma sokar — bu bir istisna "
        "FIRLATMAZ, sadece akışın durumu değişir (if (dosya) ya da "
        ".fail() ile kontrol edilebilir).";
    lessons[97].syntax = "#include <fstream>\nstd::ifstream dosya(\"dosyaAdi.txt\");\nstd::string satir;\nstd::getline(dosya, satir);";
    lessons[97].exampleCode =
        "#include <iostream>\n"
        "#include <fstream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::ifstream dosya(\"cikti.txt\");\n"
        "    if (dosya.is_open()) {\n"
        "        std::string satir;\n"
        "        std::getline(dosya, satir);\n"
        "        std::cout << satir;\n"
        "        dosya.close();\n"
        "    } else {\n"
        "        std::cout << \"acilamadi\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[97].lineExplanations = {
        "std::ifstream dosya(\"cikti.txt\"); : \"cikti.txt\" dosyasını "
        "OKUMA modunda açar.",
        "if (dosya.is_open()) : dosyanın başarıyla açılıp açılmadığını "
        "kontrol eder (dosya yoksa açma başarısız olur).",
        "std::getline(dosya, satir); : dosyadan TAM BİR SATIRI satir "
        "değişkenine okur (>> operatörünün aksine, boşlukları da "
        "içerir)."};
    lessons[97].commonMistakes = {
        "Dosyanın SONUNA (EOF) ulaşıldıktan sonra okumaya devam "
        "etmeye çalışmak, akışı BAŞARISIZ (fail) duruma sokar (if "
        "(dosya) ya da .fail() ile kontrol edilebilir); bu bir "
        "istisna (exception) FIRLATMAZ, sadece akışın durumunu "
        "değiştirir."};

    lessons[98].explanation =
        "try/catch, çalışma zamanında oluşabilecek hataları YÖNETMEK "
        "için kullanılır. throw ifadesi bir istisna FIRLATIR; kontrol, "
        "EN YAKIN eşleşen catch bloğuna aktarılır (yığın bu sırada "
        "geri sarılır/unwind edilir). İstisnalar REFERANS (const&) "
        "ile yakalanmalıdır (catch (const std::exception& e)) — "
        "DEĞER ile yakalamak OBJECT SLICING'e yol açabilir. Birden "
        "fazla catch bloğu varsa, YAZILDIKLARI SIRAYLA denenir; genel "
        "bir catch(...) bloğu, ondan sonra gelen daha SPESİFİK bir "
        "catch bloğunu ULAŞILAMAZ (unreachable) hale getireceğinden, "
        "catch(...) HER ZAMAN EN SONA yazılmalıdır — aksi halde bu bir "
        "DERLEME HATASIDIR (sessiz bir çalışma zamanı sorunu değil). "
        "Yakalanmayan bir istisna çağrı yığınında YUKARI doğru "
        "yayılır.";
    lessons[98].syntax = "try {\n    // riskli kod\n} catch (const std::exception& e) {\n    // hata isleme\n}";
    lessons[98].exampleCode =
        "#include <iostream>\n"
        "#include <stdexcept>\n\n"
        "int main() {\n"
        "    try {\n"
        "        throw std::runtime_error(\"bir hata olustu\");\n"
        "    } catch (const std::exception& e) {\n"
        "        std::cout << \"yakalandi: \" << e.what();\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[98].lineExplanations = {
        "throw std::runtime_error(\"bir hata olustu\"); : bir istisna "
        "(exception) FIRLATIR; kontrol, en yakın eşleşen catch "
        "bloguna aktarılır.",
        "catch (const std::exception& e) : istisnayı REFERANS (&) "
        "ile yakalar (slicing'i önlemek için); std::runtime_error, "
        "std::exception'ın bir türetilmiş sınıfıdır.",
        "e.what() : istisnanın açıklama mesajını (\"bir hata olustu\") "
        "döndürür."};
    lessons[98].commonMistakes = {
        "İstisnayı DEĞER olarak yakalamak (catch (std::exception e), "
        "referans olmadan) OBJECT SLICING'e yol açabilir (türetilmiş "
        "sınıfın ek bilgisi kaybolur); bu yüzden catch (const "
        "std::exception& e) gibi REFERANS ile yakalamak tercih "
        "edilmelidir. Ayrıca genel bir catch(...) bloğu, daha "
        "spesifik bir catch bloğundan ÖNCE yazılırsa bir DERLEME "
        "HATASIDIR (sonraki bloğu ulaşılamaz/unreachable kıldığı "
        "için); catch(...) HER ZAMAN EN SONA yazılmalıdır."};

    lessons[99].explanation =
        "std::unique_ptr<Tur> (<memory> başlığından), dinamik olarak "
        "ayrılmış bir nesneyi TEK BAŞINA (exclusive/non-shared) "
        "sahiplenen bir RAII akıllı işaretçisidir. KOPYALANAMAZ — "
        "kopya oluşturucusu ve kopya ataması SİLİNMİŞTİR (deleted), "
        "bu yüzden kopyalamaya çalışmak bir DERLEME HATASIDIR; sadece "
        "std::move ile TAŞINABİLİR (taşındığında kaynak nullptr olur). "
        "Kapsam dışına çıktığında (istisna fırlatılsa BİLE) sahip "
        "olduğu nesneyi OTOMATİK OLARAK SİLER. .get(), sahipliği "
        "DEVRETMEDEN ham pointer'ı döndürür.";
    lessons[99].syntax = "#include <memory>\nstd::unique_ptr<Tur> ptr = std::make_unique<Tur>(argumanlar);";
    lessons[99].exampleCode =
        "#include <iostream>\n"
        "#include <memory>\n\n"
        "int main() {\n"
        "    std::unique_ptr<int> p1 = std::make_unique<int>(42);\n"
        "    std::cout << *p1 << \" \";\n"
        "    std::unique_ptr<int> p2 = std::move(p1);\n"
        "    std::cout << (p1 == nullptr) << \" \" << *p2;\n"
        "    return 0;\n"
        "}";
    lessons[99].lineExplanations = {
        "std::unique_ptr<int> p1 = std::make_unique<int>(42); : p1, "
        "dinamik olarak ayrılmış bir int'i (42) TEK BAŞINA (exclusive) "
        "sahiplenir.",
        "std::unique_ptr<int> p2 = std::move(p1); : sahiplik p1'DEN "
        "p2'YE TAŞINIR (move); p1 artık nullptr'dır, kopyalama "
        "YAPILAMAZ (unique_ptr kopyalanamaz).",
        "std::cout << (p1 == nullptr) << \" \" << *p2; : p1 artık boş "
        "(1/true), p2 ise değeri (42) sahiplenmiştir."};
    lessons[99].commonMistakes = {
        "std::unique_ptr KOPYALANAMAZ; std::unique_ptr<int> p3 = p2; "
        "(move olmadan) gibi bir atama DERLEME HATASIDIR (kopya "
        "oluşturucusu silinmiştir/deleted); sadece std::move ile "
        "TAŞINABİLİR."};
}
```

- [ ] **Step 3: Wire the new function into `LessonManager`**

`src/LessonManager.cpp` already includes `"LessonContent.h"` (from
Phase 13). Change the constructor's final lines from:

```cpp
    applySection8LessonContent(lessons_);
    applySection9LessonContent(lessons_);
}
```

to:

```cpp
    applySection8LessonContent(lessons_);
    applySection9LessonContent(lessons_);
    applySection10LessonContent(lessons_);
}
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/LessonContentSection8.cpp
    src/LessonContentSection9.cpp
```

to:

```cmake
    src/LessonContentSection8.cpp
    src/LessonContentSection9.cpp
    src/LessonContentSection10.cpp
```

- [ ] **Step 5: Update the content-coverage tests (widen one, REMOVE the other)**

This phase is different from Phases 13-20 here: after this phase,
EVERY topic 1-100 has real lesson content (topics 1-10 already had
content from the original "static lesson + quiz core" phase; topics
11-90 got content in Phases 13-20; topics 91-100 get it now). There is
no longer any topic in the 11-100 range without content, so the
"topics without content" test would have an empty, meaningless loop
range if merely narrowed — it must be REMOVED entirely instead.

In `tests/LessonManagerTests.cpp`, replace:

```cpp
TEST_CASE(LessonManager_TopicsElevenToNinetyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 90; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsElevenToHundredHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 100; ++topicId) {
```

(keep the rest of that test's body unchanged). Then DELETE the entire
`LessonManager_TopicsNinetyOneToHundredHaveNoContentYet` test case
(its whole `TEST_CASE(...) { ... }` block) — do not leave an empty or
narrowed version of it, remove it completely, since there is no longer
any topic in 1-100 without content.

- [ ] **Step 6: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `95/95 test(s) passed.` (Phase 20 ended at 96/96; this task
renames one test — net 0 — and DELETES the other entirely — net -1 —
so the new total is 95).

- [ ] **Step 7: Commit**

```bash
git add src/LessonContent.h src/LessonContentSection10.cpp src/LessonManager.cpp CMakeLists.txt tests/LessonManagerTests.cpp
git commit -m "feat(content): add Section 10 lesson content (topics 91-100)"
```

---

### Task 2: Questions for topics 91-94 (ids 2393-2508)

**Files:**
- Modify: `src/QuestionContent.h` (add one new declaration)
- Create: `src/QuestionsSection10.cpp`
- Modify: `src/QuestionManager.cpp` (include, call, bump `reserve()`)
- Modify: `CMakeLists.txt` (add the new `.cpp`)

**Interfaces:**
- Produces: `void appendSection10Questions(std::vector<Question>& questions);`
  — Task 3 and Task 4 append more `questions.push_back(...)` calls to
  this SAME function body (in this same file) for topics 95-97 and
  98-100 respectively. This task only adds topics 91-94 (ids 2393-2508).

- [ ] **Step 1: Add the new declaration**

In `src/QuestionContent.h`, add this line after the existing
`appendSection9Questions` declaration (do not remove that one):

```cpp
void appendSection10Questions(std::vector<Question>& questions);
```

- [ ] **Step 2: Write topics 91-94's questions**

Create `src/QuestionsSection10.cpp` with exactly this content:

```cpp
#include "QuestionContent.h"

#include "Question.h"

void appendSection10Questions(std::vector<Question>& questions) {
    // Topic 91: sort()
    questions.push_back(Question{
        .id = 2393, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::sort(first, last)'ın varsayılan sıralama düzeni nedir?",
        .options = {"Artan (küçükten büyüğe)", "Azalan (büyükten küçüğe)", "Ekleme sırası korunur", "Rastgele"},
        .acceptedAnswers = {"a"},
        .explanation = "std::sort varsayılan olarak artan sırada sıralar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2394, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {5, 2, 8, 1};\nstd::sort(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"5281", "1258", "8521", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Artan sıralama: 1,2,5,8.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2395, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Azalan (büyükten küçüğe) sıralama yapmak için std::sort'a ne verilmelidir?",
        .options = {"Hiçbir şey, varsayılan davranıştır", "İkinci bir vektör", "Üçüncü argüman olarak std::greater<int>()", "std::reverse çağrısı, std::sort'tan önce"},
        .acceptedAnswers = {"c"},
        .explanation = "std::greater<int>() üçüncü argüman olarak verilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2396, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {3, 1, 2};\nstd::sort(v.begin(), v.end(), std::greater<int>());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"123", "213", "132", "321"},
        .acceptedAnswers = {"d"},
        .explanation = "std::greater<int>() ile azalan sıralama: 3,2,1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2397, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::sort, hangi başlığı (header) gerektirir?",
        .options = {"<algorithm>", "<numeric>", "<memory>", "<fstream>"},
        .acceptedAnswers = {"a"},
        .explanation = "std::sort <algorithm> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2398, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 4, 2, 2, 3};\nstd::sort(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"44322", "22344", "23244", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Artan sıralama: 2,2,3,4,4.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2399, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {9, 1, 5};\nstd::sort(v.begin(), v.begin() + 2);\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"159", "915", "195", "519"},
        .acceptedAnswers = {"c"},
        .explanation = "Sadece ilk 2 eleman [9,1] sıralanır -> [1,9]; 3. eleman (5) değişmez: 1,9,5.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2400, .topicId = 91,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {6, 3, 9, 1};\nstd::sort(v.begin(), v.end());\nstd::sort(v.begin(), v.end(), std::greater<int>());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"1369", "6391", "1963", "9631"},
        .acceptedAnswers = {"d"},
        .explanation = "İlk sort artan (1,3,6,9); ikinci sort azalan (9,6,3,1) yapar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2401, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::sort, varsayılan olarak artan (küçükten büyüğe) sıralar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2402, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::sort, azalan sıralama için otomatik olarak ters çevirir, ek argüman gerekmez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: azalan sıralama için üçüncü argüman (örn. std::greater<int>()) gerekir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2403, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::sort için <algorithm> başlığı gereklidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2404, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::sort, konteynerin sadece bir KISMINI (örneğin ilk N elemanını) sıralayacak şekilde de çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2405, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::sort, üçüncü bir argüman olarak özel bir karşılaştırma fonksiyonu/lambda kabul edebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2406, .topicId = 91,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::sort çağrıldıktan sonra orijinal (sıralanmamış) sıra korunur, ayrı bir kopya oluşturulur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::sort yerinde (in-place) çalışır, orijinal sıra kaybolur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2407, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralığı sıralayan STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"sort"},
        .explanation = "std::sort kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2408, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {3, 1, 2};\nstd::sort(v.begin(), v.end());\nfor (int x : v) std::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"123"},
        .explanation = "Artan sıralama: 1,2,3.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2409, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Azalan sıralama için üçüncü argüman olarak std::_____<int>() verilir (İngilizce kelime).",
        .acceptedAnswers = {"greater"},
        .explanation = "std::greater<int>() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2410, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::sort'un gerektirdiği başlık dosyası <_____> dir (İngilizce kelime).",
        .acceptedAnswers = {"algorithm"},
        .explanation = "<algorithm> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2411, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {7, 2, 5};\nstd::sort(v.begin(), v.end(), std::greater<int>());\nfor (int x : v) std::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"752"},
        .explanation = "Azalan sıralama: 7,5,2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2412, .topicId = 91,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::sort, varsayılan olarak operator_____ kullanarak karşılaştırma yapar (bir sembol).",
        .acceptedAnswers = {"<"},
        .explanation = "operator< kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2413, .topicId = 91,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {8, 3, 5};\n_____\nfor (int x : v) { std::cout << x; }\nv'yi artan sırada sıralayan satırı yazın.",
        .acceptedAnswers = {"std::sort(v.begin(), v.end());"},
        .explanation = "std::sort varsayılan olarak artan sıralar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2414, .topicId = 91,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {8, 3, 5};\n_____\nfor (int x : v) { std::cout << x; }\nv'yi azalan sırada sıralayan satırı yazın.",
        .acceptedAnswers = {"std::sort(v.begin(), v.end(), std::greater<int>());"},
        .explanation = "std::greater<int>() ile azalan sıralama.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2415, .topicId = 91,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {10, 4, 7};\nstd::sort(v.begin(), v.end());\nfor (int x : v) { std::cout << x << \" \"; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4 7 10 "},
        .explanation = "Artan sıralama: 4, 7, 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2416, .topicId = 91,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {5, 5, 1, 3, 1};\nstd::sort(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"11355"},
        .explanation = "Artan sıralama: 1,1,3,5,5.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2417, .topicId = 91,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 1, 2};\nsort(v.begin(), v.end());\n\nBu kod derlenmez çünkü sort, std:: öneki olmadan (using namespace std olmadan) çağrılamaz; std::sort olarak nitelenmelidir. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::sort(v.begin(), v.end());"},
        .explanation = "std::sort öneki gereklidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2418, .topicId = 91,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {5, 2, 8};\nstd::sort(v.begin(), v.end());\nstd::cout << v;\n\nBu kod derlenmez çünkü std::vector<int> için operator<< tanımlı değildir; bir vektörü yazdırmak için elemanları TEK TEK (bir döngüyle) yazdırmak gerekir. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int x : v) { std::cout << x; }"},
        .explanation = "vector'ün operator<< tanımı yoktur; döngüyle yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2419, .topicId = 91,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {3, 1, 2}\nstd::sort(v.begin(), v.end());\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {3, 1, 2};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2420, .topicId = 91,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörü sıralayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"for (int x : v) { std::cout << x; }\n    return 0;\n}", "std::vector<int> v = {9, 3, 6};\n    std::sort(v.begin(), v.end());", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+sıralama (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2421, .topicId = 91,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (sırasız en az 3 değer); std::sort ile artan sırada sıralayın ve tüm elemanları ekrana yazdırın.",
        .acceptedAnswers = {"sort", "algorithm"},
        .explanation = "std::sort ile artan sıralama yapılır.",
        .baseXp = 40,
    });

    // Topic 92: reverse()
    questions.push_back(Question{
        .id = 2422, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::reverse(first, last) ne yapar?",
        .options = {"Aralığı sıralar", "Aralığın elemanlarının sırasını YERİNDE tersine çevirir", "Aralığın bir kopyasını oluşturur", "Aralıktaki en büyük elemanı bulur"},
        .acceptedAnswers = {"b"},
        .explanation = "std::reverse elemanları yerinde tersine çevirir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2423, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2, 3};\nstd::reverse(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"123", "213", "321", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "Tersine çevrilmiş hali: 3,2,1.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2424, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::reverse'ün dönüş türü nedir?",
        .options = {"int", "Yeni bir vektör", "bool", "void"},
        .acceptedAnswers = {"d"},
        .explanation = "std::reverse void döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2425, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "auto sonuc = std::reverse(v.begin(), v.end());\nBu kod derlenir mi?",
        .options = {"Hayır, std::reverse void döndürür; bir değişkene atanamaz, derleme hatası oluşur", "Evet, sonuc yeni bir vektör olur", "Evet, sonuc bir bool olur", "Evet, sonuc bir iterator olur"},
        .acceptedAnswers = {"a"},
        .explanation = "void bir değişkene atanamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2426, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3, 4};\nstd::reverse(v.begin(), v.begin() + 2);\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"4321", "2134", "1234", "1243"},
        .acceptedAnswers = {"b"},
        .explanation = "Sadece ilk 2 eleman [1,2] tersine çevrilir -> [2,1]; kalan [3,4] değişmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2427, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse, hangi başlığı gerektirir?",
        .options = {"<numeric>", "<memory>", "<algorithm>", "<fstream>"},
        .acceptedAnswers = {"c"},
        .explanation = "std::reverse <algorithm> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2428, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {5, 3, 8};\nstd::sort(v.begin(), v.end());\nstd::reverse(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nEkran çıktısı nedir?",
        .options = {"358", "583", "385", "853"},
        .acceptedAnswers = {"d"},
        .explanation = "sort artan (3,5,8) yapar; reverse bunu (8,5,3) yapar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2429, .topicId = 92,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string s = \"merhaba\";\nstd::reverse(s.begin(), s.end());\nstd::cout << s;\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Evet, derlenir; çıktı \"abahrem\"dir", "Hayır, std::reverse sadece std::vector ile çalışır", "Evet, çıktı \"merhaba\" olarak kalır", "Evet ama çalışma zamanı hatası verir"},
        .acceptedAnswers = {"a"},
        .explanation = "std::reverse herhangi bir bidirectional iterator aralığıyla (std::string dahil) çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2430, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::reverse, bir aralığın elemanlarının sırasını yerinde (in-place) tersine çevirir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2431, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::reverse, yeni bir konteyner oluşturup orijinali değiştirmeden bırakır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: orijinal konteynerin kendisi değişir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2432, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::reverse'ün dönüş türü void'dir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2433, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::reverse, sadece std::vector ile çalışır, std::string ile çalışmaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::reverse std::string ile de çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2434, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse, bir konteynerin sadece bir KISMINI (örneğin ilk N elemanını) tersine çevirecek şekilde de çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2435, .topicId = 92,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse'ün dönüş değerini bir değişkene atamak geçerli bir C++ kodudur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: void bir değişkene atanamaz, derleme hatası oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2436, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralığın elemanlarının sırasını yerinde tersine çeviren STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"reverse"},
        .explanation = "std::reverse kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2437, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {4, 5, 6};\nstd::reverse(v.begin(), v.end());\nfor (int x : v) std::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"654"},
        .explanation = "Tersine çevrilmiş hali: 6,5,4.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2438, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::reverse'ün dönüş türü _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"void"},
        .explanation = "void döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2439, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse, hangi başlığı (header) gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"algorithm"},
        .explanation = "<algorithm> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2440, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::string s = \"abc\";\nstd::reverse(s.begin(), s.end());\nstd::cout << s;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"cba"},
        .explanation = "Tersine çevrilmiş hali: cba.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2441, .topicId = 92,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::reverse çağrıldıktan sonra, orijinal konteynerin _____ değişir (Türkçe kelime, 'kendisi' anlamında).",
        .acceptedAnswers = {"kendisi"},
        .explanation = "Konteynerin kendisi değişir, kopya değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2442, .topicId = 92,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {7, 8, 9};\n_____\nfor (int x : v) { std::cout << x; }\nv'yi yerinde tersine çeviren satırı yazın.",
        .acceptedAnswers = {"std::reverse(v.begin(), v.end());"},
        .explanation = "std::reverse yerinde tersine çevirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2443, .topicId = 92,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3};\nstd::reverse(v.begin(), v.end());\n_____\nv'nin tersine çevrilmiş halini ekrana yazdıran döngüyü yazın.",
        .acceptedAnswers = {"for (int x : v) { std::cout << x; }"},
        .explanation = "range-for ile elemanlar yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2444, .topicId = 92,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {2, 4, 6};\nstd::reverse(v.begin(), v.end());\nfor (int x : v) { std::cout << x << \" \"; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6 4 2 "},
        .explanation = "Tersine çevrilmiş hali: 6, 4, 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2445, .topicId = 92,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 3, 4, 5};\nstd::reverse(v.begin(), v.end());\nstd::reverse(v.begin(), v.end());\nfor (int x : v) { std::cout << x; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12345"},
        .explanation = "İki kez tersine çevirmek orijinal sırayı geri getirir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2446, .topicId = 92,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nauto sonuc = std::reverse(v.begin(), v.end());\n\nBu kod derlenmez çünkü std::reverse void döndürür; dönüş değeri bir değişkene ATANAMAZ. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::reverse(v.begin(), v.end());"},
        .explanation = "void bir değişkene atanamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2447, .topicId = 92,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nreverse(v.begin(), v.end());\n\nBu kod derlenmez çünkü reverse, std:: öneki olmadan (using namespace std olmadan) çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::reverse(v.begin(), v.end());"},
        .explanation = "std::reverse öneki gereklidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2448, .topicId = 92,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {1, 2, 3}\nstd::reverse(v.begin(), v.end());\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {1, 2, 3};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2449, .topicId = 92,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörü tersine çevirip yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"for (int x : v) { std::cout << x; }\n    return 0;\n}", "std::vector<int> v = {2, 4, 6};\n    std::reverse(v.begin(), v.end());", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+tersine çevirme (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2450, .topicId = 92,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (en az 3 değer); std::reverse ile tersine çevirin ve tüm elemanları ekrana yazdırın.",
        .acceptedAnswers = {"reverse", "algorithm"},
        .explanation = "std::reverse ile elemanların sırası tersine çevrilir.",
        .baseXp = 40,
    });

    // Topic 93: find()
    questions.push_back(Question{
        .id = 2451, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::find(first, last, deger) ne döndürür?",
        .options = {"Bir bool", "Elemanların sayısı", "Bulunan elemanı gösteren bir iterator (ya da bulunamazsa last)", "Elemanın index'i (bir int)"},
        .acceptedAnswers = {"c"},
        .explanation = "std::find bir iterator döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2452, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {4, 7, 2};\nauto it = std::find(v.begin(), v.end(), 7);\nstd::cout << (it != v.end());\nEkran çıktısı nedir?",
        .options = {"7", "0", "Derleme hatası", "1"},
        .acceptedAnswers = {"d"},
        .explanation = "7 bulunduğundan it != v.end() true (1).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2453, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::find, bir değer BULUNAMAZSA ne döndürür?",
        .options = {"last (genellikle konteynerin end()'i)", "nullptr", "-1", "Bir istisna (exception) fırlatır"},
        .acceptedAnswers = {"a"},
        .explanation = "Bulunamazsa last (end()) döndürülür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2454, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 7, 2};\nauto it = std::find(v.begin(), v.end(), 100);\nstd::cout << (it == v.end());\nEkran çıktısı nedir?",
        .options = {"0", "1", "100", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "100 bulunamadığından it == v.end() true (1).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2455, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::find sonucunu it != v.end() ile kontrol ETMEDEN *it ile dereference etmek ne anlama gelir?",
        .options = {"Her zaman güvenlidir", "Derleme hatası oluşur", "Değer bulunamadıysa tanımsız davranıştır (undefined behavior)", "Otomatik olarak 0 döner"},
        .acceptedAnswers = {"c"},
        .explanation = "Kontrol edilmeden dereference etmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2456, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {5, 5, 5};\nauto it = std::find(v.begin(), v.end(), 5);\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"3", "15", "555", "5"},
        .acceptedAnswers = {"d"},
        .explanation = "std::find ilk eşleşmeyi bulur; değeri 5'tir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2457, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 3, 2, 1};\nauto it = std::find(v.begin(), v.end(), 2);\nstd::cout << (it - v.begin());\nEkran çıktısı nedir?",
        .options = {"1", "3", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "2'nin İLK geçtiği index 1'dir (0-indexed).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2458, .topicId = 93,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::find, hangi başlığı gerektirir?",
        .options = {"<numeric>", "<algorithm>", "<memory>", "<fstream>"},
        .acceptedAnswers = {"b"},
        .explanation = "std::find <algorithm> başlığında tanımlıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2459, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::find, bir değeri bir aralıkta arar ve bulursa bir iterator döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2460, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::find, bulunamazsa bir istisna (exception) fırlatır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: istisna fırlatmaz, last (end()) döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2461, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::find sonucunu end() ile karşılaştırmak, değerin bulunup bulunmadığını kontrol etmenin doğru yoludur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2462, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::find, birden fazla eşleşme varsa SON eşleşmeyi döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: ilk eşleşmeyi döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2463, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::find'ın sonucunu kontrol etmeden dereference etmek tanımsız davranışa yol açabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2464, .topicId = 93,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::find, elemanların sayısını değil, bir iterator döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2465, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralıkta bir değeri arayan STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"find"},
        .explanation = "std::find kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2466, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::find bir değeri bulamazsa _____ döndürür (İngilizce kelime).",
        .acceptedAnswers = {"last"},
        .explanation = "last (genellikle end()) döndürülür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2467, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::find'ın bulup bulmadığını kontrol etmek için sonucu konteynerin _____ üye fonksiyonunun sonucuyla karşılaştırmak gerekir (İngilizce kelime).",
        .acceptedAnswers = {"end"},
        .explanation = "end() ile karşılaştırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2468, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {9, 3, 6};\nauto it = std::find(v.begin(), v.end(), 3);\nstd::cout << *it;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "Bulunan elemanın değeri 3'tür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2469, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::find, hangi başlığı gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"algorithm"},
        .explanation = "<algorithm> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2470, .topicId = 93,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::find sonucunu kontrol etmeden dereference etmek _____ davranıştır (Türkçe iki kelime).",
        .acceptedAnswers = {"tanımsız davranış", "tanımsız"},
        .explanation = "Bu, tanımsız davranıştır (UB).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2471, .topicId = 93,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {2, 5, 8};\n_____\nif (it != v.end()) { std::cout << *it; }\nv içinde 5 değerini arayan satırı yazın.",
        .acceptedAnswers = {"auto it = std::find(v.begin(), v.end(), 5);"},
        .explanation = "std::find ile arama yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2472, .topicId = 93,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {2, 5, 8};\nauto it = std::find(v.begin(), v.end(), 100);\n_____\nit'nin bulunup bulunmadığını kontrol eden if satırını yazın.",
        .acceptedAnswers = {"if (it != v.end()) {"},
        .explanation = "end() ile karşılaştırılarak kontrol edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2473, .topicId = 93,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {6, 1, 9};\nauto it = std::find(v.begin(), v.end(), 1);\nstd::cout << (it != v.end());\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "1 bulunduğundan sonuç true (1).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2474, .topicId = 93,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {3, 6, 9};\nauto it = std::find(v.begin(), v.end(), 100);\nif (it == v.end()) { std::cout << \"yok\"; } else { std::cout << *it; }\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"yok"},
        .explanation = "100 bulunamadığından \"yok\" yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2475, .topicId = 93,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 6, 9};\nauto it = std::find(v.begin(), v.end(), 100);\nstd::cout << *it;\n\nBu kod derlenir AMA tanımsız davranışa (undefined behavior) yol açar çünkü 100 v içinde bulunamadığından it, v.end()'e eşittir; *it ile bu konum okunmaya çalışılıyor. Hatalı satırı, kontrol ekleyerek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (it != v.end()) { std::cout << *it; }"},
        .explanation = "Kontrol eklenmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2476, .topicId = 93,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 6, 9};\nauto it = find(v.begin(), v.end(), 6);\n\nBu kod derlenmez çünkü find, std:: öneki olmadan çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"auto it = std::find(v.begin(), v.end(), 6);"},
        .explanation = "std::find öneki gereklidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2477, .topicId = 93,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {3, 6, 9}\nauto it = std::find(v.begin(), v.end(), 6);\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {3, 6, 9};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2478, .topicId = 93,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörde bir değer arayıp sonucunu yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"if (it != v.end()) { std::cout << *it; }\n    return 0;\n}", "std::vector<int> v = {4, 8, 12};\n    auto it = std::find(v.begin(), v.end(), 8);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+arama (2), kontrol+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2479, .topicId = 93,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (en az 3 değer); std::find ile bir değeri arayın ve bulunup bulunmadığını (varsa değerini) ekrana yazdırın.",
        .acceptedAnswers = {"find", "end"},
        .explanation = "std::find sonucu end() ile kontrol edilerek kullanılır.",
        .baseXp = 40,
    });

    // Topic 94: count()
    questions.push_back(Question{
        .id = 2480, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::count(first, last, deger) ne döndürür?",
        .options = {"Bir iterator", "Bir bool", "deger'in index'i", "deger'e eşit elemanların sayısı"},
        .acceptedAnswers = {"d"},
        .explanation = "std::count eşleşen eleman sayısını döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2481, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {2, 5, 2, 8};\nint sayi = std::count(v.begin(), v.end(), 2);\nstd::cout << sayi;\nEkran çıktısı nedir?",
        .options = {"2", "1", "4", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "2 değeri iki kez geçiyor.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2482, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::count, bir değer HİÇ bulunamazsa ne döndürür?",
        .options = {"-1", "0", "Bir istisna fırlatır", "nullptr"},
        .acceptedAnswers = {"b"},
        .explanation = "Eşleşme yoksa 0 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2483, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {7, 7, 7};\nint sayi = std::count(v.begin(), v.end(), 7);\nstd::cout << sayi;\nEkran çıktısı nedir?",
        .options = {"1", "0", "3", "7"},
        .acceptedAnswers = {"c"},
        .explanation = "7 değeri üç kez geçiyor.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2484, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::count'un dönüş türü hakkında ne söylenebilir?",
        .options = {"Her zaman bir iterator döner", "Her zaman true/false döner", "Her zaman bir string döner", "Bir tam sayı (integral) türü döner"},
        .acceptedAnswers = {"d"},
        .explanation = "std::count bir tam sayı döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2485, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::count, hangi başlığı gerektirir?",
        .options = {"<algorithm>", "<numeric>", "<memory>", "<fstream>"},
        .acceptedAnswers = {"a"},
        .explanation = "std::count <algorithm> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2486, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 1, 3, 1, 2};\nint sayi1 = std::count(v.begin(), v.end(), 1);\nint sayi2 = std::count(v.begin(), v.end(), 2);\nstd::cout << sayi1 << \" \" << sayi2;\nEkran çıktısı nedir?",
        .options = {"2 3", "3 2", "1 1", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "1 üç kez, 2 iki kez geçiyor.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2487, .topicId = 94,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string s = \"banana\";\nint sayi = std::count(s.begin(), s.end(), 'a');\nstd::cout << sayi;\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, derleme hatası", "1", "3", "6"},
        .acceptedAnswers = {"c"},
        .explanation = "\"banana\" içinde 'a' harfi üç kez geçer.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2488, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::count, eşleşen elemanların SAYISINI döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2489, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::count, eşleşme yoksa bir istisna fırlatır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: istisna fırlatmaz, 0 döner.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2490, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::count'un dönüş türü bir tam sayıdır (iterator ya da bool değil).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2491, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::count, sadece std::vector<int> ile çalışır, std::string ile çalışmaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: std::count std::string ile de çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2492, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::count, eşleşme sayısını bulmak için tüm aralığı gezer.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2493, .topicId = 94,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::count, ilk eşleşmeyi bulduğunda aramayı durdurur ve 1 döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: tüm aralığı gezip toplam eşleşme sayısını döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2494, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralıkta bir değerin kaç kez geçtiğini sayan STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"count"},
        .explanation = "std::count kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2495, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {4, 4, 9};\nint sayi = std::count(v.begin(), v.end(), 4);\nstd::cout << sayi;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "4 değeri iki kez geçiyor.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2496, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::count, eşleşme yoksa _____ döndürür (bir rakam).",
        .acceptedAnswers = {"0"},
        .explanation = "Eşleşme yoksa 0 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2497, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::count, hangi başlığı gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"algorithm"},
        .explanation = "<algorithm> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2498, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {5, 5, 5, 5};\nint sayi = std::count(v.begin(), v.end(), 5);\nstd::cout << sayi;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"4"},
        .explanation = "5 değeri dört kez geçiyor.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2499, .topicId = 94,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::count'un dönüş türü bir _____ dir (Türkçe kelime, 'tam sayı' anlamında).",
        .acceptedAnswers = {"tam sayı", "tamsayi", "tam sayi"},
        .explanation = "Dönüş türü bir tam sayıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2500, .topicId = 94,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {6, 6, 3, 6};\n_____\nstd::cout << sayi;\nv içinde 6 değerinin kaç kez geçtiğini sayan satırı yazın.",
        .acceptedAnswers = {"int sayi = std::count(v.begin(), v.end(), 6);"},
        .explanation = "std::count ile sayım yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2501, .topicId = 94,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 2, 3};\nint sayi = std::count(v.begin(), v.end(), 5);\n_____\nsayi'yi ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << sayi;"},
        .explanation = "sayi değişkeni yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2502, .topicId = 94,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {8, 3, 8, 8};\nint sayi = std::count(v.begin(), v.end(), 8);\nstd::cout << sayi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "8 değeri üç kez geçiyor.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2503, .topicId = 94,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {2, 4, 6, 8};\nint ciftSayisi = std::count(v.begin(), v.end(), 4) + std::count(v.begin(), v.end(), 8);\nstd::cout << ciftSayisi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2"},
        .explanation = "count(4)=1, count(8)=1, toplam 2.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2504, .topicId = 94,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 3, 5};\nbool bulundu = std::count(v.begin(), v.end(), 3);\n\nBu kod TEKNİK OLARAK derlenir (int, bool'a örtük dönüştürülür) ama YANILTICIDIR çünkü std::count bir SAYI döndürür, bool değil; doğrusu sonucu bir int değişkende tutmaktır. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int sayi = std::count(v.begin(), v.end(), 3);"},
        .explanation = "std::count sonucu bir int'te tutulmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2505, .topicId = 94,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 3, 5};\nint sayi = count(v.begin(), v.end(), 3);\n\nBu kod derlenmez çünkü count, std:: öneki olmadan çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int sayi = std::count(v.begin(), v.end(), 3);"},
        .explanation = "std::count öneki gereklidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2506, .topicId = 94,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {3, 3, 5}\nint sayi = std::count(v.begin(), v.end(), 3);\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {3, 3, 5};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2507, .topicId = 94,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörde bir değerin kaç kez geçtiğini sayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << sayi;\n    return 0;\n}", "std::vector<int> v = {2, 2, 5};\n    int sayi = std::count(v.begin(), v.end(), 2);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+sayım (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2508, .topicId = 94,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (en az bir değer tekrar etmeli); std::count ile bir değerin kaç kez geçtiğini sayın ve ekrana yazdırın.",
        .acceptedAnswers = {"count", "algorithm"},
        .explanation = "std::count ile eşleşme sayısı bulunur.",
        .baseXp = 40,
    });
}
```

- [ ] **Step 3: Wire the new function into `QuestionManager`**

`src/QuestionManager.cpp` already includes `"QuestionContent.h"` (from
Phase 13). Change the constructor's final lines from:

```cpp
    appendSection8Questions(questions_);
    appendSection9Questions(questions_);
```

to:

```cpp
    appendSection8Questions(questions_);
    appendSection9Questions(questions_);
    appendSection10Questions(questions_);
```

Also change `questions_.reserve(2392);` to `questions_.reserve(2682);`.

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/QuestionsSection8.cpp
    src/QuestionsSection9.cpp
```

to:

```cmake
    src/QuestionsSection8.cpp
    src/QuestionsSection9.cpp
    src/QuestionsSection10.cpp
```

- [ ] **Step 5: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `95/95 test(s) passed.` (unchanged from Task 1's end state —
the test that counts questions per topic is added in Task 4, once all
of topics 91-100 have their full 29 questions each).

- [ ] **Step 6: Commit**

```bash
git add src/QuestionContent.h src/QuestionsSection10.cpp src/QuestionManager.cpp CMakeLists.txt
git commit -m "feat(content): add questions for topics 91-94 (ids 2393-2508)"
```

---

### Task 3: Questions for topics 95-97 (ids 2509-2595)

**Files:**
- Modify: `src/QuestionsSection10.cpp` (append more `push_back` calls to
  the SAME `appendSection10Questions` function Task 2 created)

**Interfaces:**
- Consumes: `appendSection10Questions(std::vector<Question>& questions)`
  defined in `src/QuestionsSection10.cpp` by Task 2 — append to its
  body, after the last `questions.push_back(...)` for id 2508 and
  before the function's closing `}`.
- Produces: ids 2509-2595 added to the same function. Task 4 appends
  after this task's last id (2595).

- [ ] **Step 1: Write topics 95-97's questions**

Open `src/QuestionsSection10.cpp` as it exists on disk (Task 2's
committed state) and insert the following `push_back` calls right
after the id-2508 block, before the function's closing `}`:

```cpp
    // Topic 95: min(), max() ve max_element()
    questions.push_back(Question{
        .id = 2509, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::max(a, b) ne döndürür?",
        .options = {"İki DEĞERDEN büyük olanı, doğrudan bir değer olarak", "Bir iterator", "Her zaman a'yı", "Her zaman b'yi"},
        .acceptedAnswers = {"a"},
        .explanation = "std::max iki değerden büyük olanı doğrudan döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2510, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::cout << std::max(3, 9);\nEkran çıktısı nedir?",
        .options = {"3", "9", "Derleme hatası", "12"},
        .acceptedAnswers = {"b"},
        .explanation = "9, 3'ten büyük olduğundan 9 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2511, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::max_element(first, last) ne döndürür?",
        .options = {"Aralıktaki en büyük değeri, doğrudan", "Bir bool", "Aralıktaki en büyük elemanı gösteren bir ITERATOR", "Elemanların sayısı"},
        .acceptedAnswers = {"c"},
        .explanation = "std::max_element bir iterator döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2512, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 9, 2};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << it;\nBu kod derlenir mi?",
        .options = {"Evet, çıktı 9'dur", "Evet, çıktı bir adres olur", "Evet, çıktı 0 olur", "Hayır, vector iterator'ı için operator<< tanımlı değildir, derleme hatası oluşur"},
        .acceptedAnswers = {"d"},
        .explanation = "Iterator'ı dereference etmeden yazdırmak derleme hatasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2513, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 9, 2};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"9", "4", "2", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Dereference edilen değer en büyük elemandır: 9.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2514, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::min(a, b) ile std::min_element(first, last) arasındaki fark nedir?",
        .options = {"Aralarında fark yoktur", "std::min iki DEĞERİ karşılaştırıp birini döndürür; std::min_element bir ARALIKTAKİ en küçük elemanı gösteren bir ITERATOR döndürür", "std::min_element her zaman std::min'den daha hızlıdır", "std::min sadece int ile çalışır, std::min_element her türle çalışır"},
        .acceptedAnswers = {"b"},
        .explanation = "min değer döndürür, min_element iterator döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2515, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {3, 7, 1, 9, 4};\nauto it = std::min_element(v.begin(), v.end());\nstd::cout << *it;\nEkran çıktısı nedir?",
        .options = {"9", "3", "1", "4"},
        .acceptedAnswers = {"c"},
        .explanation = "En küçük eleman 1'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2516, .topicId = 95,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::cout << std::max(std::max(3, 7), std::max(2, 9));\nEkran çıktısı nedir?",
        .options = {"7", "3", "2", "9"},
        .acceptedAnswers = {"d"},
        .explanation = "max(3,7)=7, max(2,9)=9, max(7,9)=9.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2517, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::max(a, b), iki değerden büyük olanı doğrudan döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2518, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::max_element, bir aralıktaki en büyük DEĞERİ doğrudan döndürür, iterator değil.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: max_element bir iterator döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2519, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::max_element'in sonucunu * ile dereference etmeden yazdırmaya çalışmak bir derleme hatasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2520, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::min_element, bir aralıktaki en küçük elemanı gösteren bir iterator döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2521, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::max ve std::min, sadece iki argüman alabilir, üç ya da daha fazla değer karşılaştırmak için iç içe (nested) çağrılabilirler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2522, .topicId = 95,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::max_element, boş bir aralık üzerinde çağrılırsa nullptr döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: end() döndürür, nullptr değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2523, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki değerden büyük olanı doğrudan döndüren fonksiyon std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"max"},
        .explanation = "std::max kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2524, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::cout << std::min(5, 2);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "2, 5'ten küçük olduğundan 2 döner.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2525, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir aralıktaki en büyük elemanı gösteren bir ITERATOR döndüren fonksiyon std::_____ dir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"max_element"},
        .explanation = "std::max_element kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2526, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {6, 2, 8};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << *it;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "En büyük eleman 8'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2527, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::max_element'in sonucuna gerçek DEĞERE erişmek için _____ operatörü kullanılmalıdır (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "Dereference operatörü (*) kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2528, .topicId = 95,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir aralıktaki en küçük elemanı gösteren bir iterator döndüren fonksiyon std::_____ dir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"min_element"},
        .explanation = "std::min_element kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2529, .topicId = 95,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {5, 9, 2};\n_____\nstd::cout << *it;\nv'nin en büyük elemanını gösteren bir iterator tanımlayan satırı yazın.",
        .acceptedAnswers = {"auto it = std::max_element(v.begin(), v.end());"},
        .explanation = "std::max_element ile bir iterator elde edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2530, .topicId = 95,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << std::max(4, 8);\n_____\n7 ve 3'ten küçük olanı ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << std::min(7, 3);"},
        .explanation = "std::min iki değerden küçük olanı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2531, .topicId = 95,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {1, 8, 3};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << *it;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"8"},
        .explanation = "En büyük eleman 8'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2532, .topicId = 95,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {7, 2, 9, 4};\nauto en_kucuk = std::min_element(v.begin(), v.end());\nauto en_buyuk = std::max_element(v.begin(), v.end());\nstd::cout << *en_kucuk << \" \" << *en_buyuk;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2 9"},
        .explanation = "En küçük 2, en büyük 9'dur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2533, .topicId = 95,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 7, 1};\nauto it = std::max_element(v.begin(), v.end());\nstd::cout << it;\n\nBu kod derlenmez çünkü it bir ITERATOR'dır ve vector iterator'ı için operator<< tanımlı değildir; gerçek değere erişmek için * ile dereference edilmelidir. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << *it;"},
        .explanation = "Iterator dereference edilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2534, .topicId = 95,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {3, 7, 1};\nint en_buyuk = std::max_element(v.begin(), v.end());\n\nBu kod derlenmez çünkü std::max_element bir ITERATOR döndürür, bir int DEĞİL; bir int değişkene doğrudan atanamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int en_buyuk = *std::max_element(v.begin(), v.end());"},
        .explanation = "Iterator dereference edilip int'e atanmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2535, .topicId = 95,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {3, 7, 1}\nauto it = std::max_element(v.begin(), v.end());\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {3, 7, 1};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2536, .topicId = 95,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörün en büyük elemanını bulup yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << *it;\n    return 0;\n}", "std::vector<int> v = {5, 9, 2};\n    auto it = std::max_element(v.begin(), v.end());", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+bulma (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2537, .topicId = 95,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int vektörü tanımlayın (en az 3 değer); std::max_element ile en büyük elemanı bulun ve dereference ederek ekrana yazdırın.",
        .acceptedAnswers = {"max_element", "algorithm"},
        .explanation = "max_element sonucu dereference edilerek kullanılır.",
        .baseXp = 40,
    });

    // Topic 96: accumulate()
    questions.push_back(Question{
        .id = 2538, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::accumulate(first, last, init) ne yapar?",
        .options = {"Bir aralığı sıralar", "Bir aralığı init'ten başlayarak TOPLAR", "Bir aralıktaki en büyük elemanı bulur", "Bir aralığı tersine çevirir"},
        .acceptedAnswers = {"b"},
        .explanation = "std::accumulate bir aralığı toplar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2539, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {1, 2, 3};\nint toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nEkran çıktısı nedir?",
        .options = {"0", "3", "6", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "1+2+3=6.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2540, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::accumulate, hangi başlığı gerektirir?",
        .options = {"<algorithm>", "<memory>", "<fstream>", "<numeric>"},
        .acceptedAnswers = {"d"},
        .explanation = "std::accumulate <numeric> başlığında tanımlıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2541, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate'in üçüncü argümanının (başlangıç değeri) TÜRÜ neyi etkiler?",
        .options = {"Toplama işleminin ÇALIŞMA TÜRÜNÜ (ve dolayısıyla ara sonuçların nasıl kırpılacağını)", "Sadece çıktının biçimini, sonucu etkilemez", "Hiçbir şeyi, her zaman double olarak hesaplanır", "Sadece konteynerin boyutunu"},
        .acceptedAnswers = {"a"},
        .explanation = "Başlangıç değerinin türü, toplama türünü belirler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2542, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<double> v = {1.5, 2.5, 3.0};\nauto toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nEkran çıktısı nedir?",
        .options = {"7", "6", "7.0", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "int başlangıç değeri (0), ara toplamları her adımda int'e kırpar: 6.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2543, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<double> v = {1.5, 2.5, 3.0};\nauto toplam = std::accumulate(v.begin(), v.end(), 0.0);\nstd::cout << toplam;\nEkran çıktısı nedir?",
        .options = {"6", "6.0", "7", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "double başlangıç değeri (0.0) doğru toplamı verir: 7.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2544, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<double> v = {2.5, 2.5};\nauto toplamYanlis = std::accumulate(v.begin(), v.end(), 0);\nauto toplamDogru = std::accumulate(v.begin(), v.end(), 0.0);\nstd::cout << toplamYanlis << \" \" << toplamDogru;\nEkran çıktısı nedir?",
        .options = {"5 5", "5 4", "4 4", "4 5"},
        .acceptedAnswers = {"d"},
        .explanation = "int başlangıçla: 0+2.5=2(kırpılır); 2+2.5=4(kırpılır). double başlangıçla: 0.0+2.5+2.5=5.0.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2545, .topicId = 96,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<int> v = {1, 2, 3, 4};\nint carpim = std::accumulate(v.begin(), v.end(), 1, std::multiplies<int>());\nstd::cout << carpim;\nEkran çıktısı nedir?",
        .options = {"24", "10", "4", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "accumulate, dördüncü argüman olarak std::multiplies<int>() ile çarpma yapar: 1*1*2*3*4=24.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2546, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::accumulate, bir aralığı başlangıç değerinden başlayarak toplar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2547, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::accumulate'in başlangıç değerinin türü, toplama sonucunu ETKİLEMEZ.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: başlangıç değerinin türü toplama sonucunu doğrudan etkiler.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2548, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::accumulate, <numeric> başlığını gerektirir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2549, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir double listesine int (0 gibi) başlangıç değeri vermek, her zaman doğru sonuç verir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: ara toplamlar int'e kırpılabilir, yanlış sonuç verebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2550, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate, dördüncü bir argüman olarak özel bir ikili işlem (örneğin çarpma) kabul edebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2551, .topicId = 96,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate'in varsayılan işlemi çıkarmadır (subtraction).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan işlem toplamadır (addition).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2552, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir aralığı toplayan STL algoritması std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"accumulate"},
        .explanation = "std::accumulate kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2553, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::vector<int> v = {2, 3, 5};\nint toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"10"},
        .explanation = "2+3+5=10.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2554, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::accumulate'in gerektirdiği başlık dosyası <_____> dir (İngilizce kelime).",
        .acceptedAnswers = {"numeric"},
        .explanation = "<numeric> başlığı gerekir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2555, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate'in başlangıç değeri bir double listesi için _____ (İngilizce kelime, 'int' değil) olmalıdır ki sonuç kırpılmasın.",
        .acceptedAnswers = {"double"},
        .explanation = "double başlangıç değeri kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2556, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<double> v = {1.0, 1.0, 1.0};\nauto toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "1.0+1.0+1.0=3 (tam sayı değerler olduğundan kırpılma sonucu etkilemez).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2557, .topicId = 96,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::accumulate'in dördüncü argümanı, varsayılan toplama yerine özel bir _____ belirtir (Türkçe kelime, 'işlem' anlamında).",
        .acceptedAnswers = {"işlem"},
        .explanation = "Özel bir ikili işlem belirtilebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2558, .topicId = 96,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {4, 5, 6};\n_____\nstd::cout << toplam;\nv'nin elemanlarını 0'dan başlayarak toplayan satırı yazın.",
        .acceptedAnswers = {"int toplam = std::accumulate(v.begin(), v.end(), 0);"},
        .explanation = "std::accumulate ile toplama yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2559, .topicId = 96,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<double> v = {1.1, 2.2};\n_____\nstd::cout << toplam;\nv'nin elemanlarını DOĞRU şekilde (double başlangıç değeriyle) toplayan satırı yazın.",
        .acceptedAnswers = {"auto toplam = std::accumulate(v.begin(), v.end(), 0.0);"},
        .explanation = "double başlangıç değeri doğru toplamı sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2560, .topicId = 96,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::vector<int> v = {10, 20, 30};\nint toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"60"},
        .explanation = "10+20+30=60.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2561, .topicId = 96,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::vector<double> v = {0.5, 0.5, 0.5};\nauto toplamYanlis = std::accumulate(v.begin(), v.end(), 0);\nauto toplamDogru = std::accumulate(v.begin(), v.end(), 0.0);\nstd::cout << toplamYanlis << \" \" << toplamDogru;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0 1.5"},
        .explanation = "int başlangıçla her adımda 0.5 kırpılıp 0 kalır, sonuç 0; double başlangıçla doğru toplam 1.5.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2562, .topicId = 96,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<double> v = {1.5, 2.5, 3.0};\nauto toplam = std::accumulate(v.begin(), v.end(), 0);\nstd::cout << toplam;\n// Beklenen: 7 (dogru toplam)\n\nBu kod, DOĞRU toplamı (7) DEĞİL YANLIŞ bir sonucu (6) verir çünkü başlangıç değeri (0) bir int'tir ve ara toplamlar her adımda int'e kırpılır. Hatalı satırı, başlangıç değerini 0.0 yaparak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"auto toplam = std::accumulate(v.begin(), v.end(), 0.0);"},
        .explanation = "double başlangıç değeri kırpılmayı önler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2563, .topicId = 96,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::vector<int> v = {1, 2, 3};\nint toplam = accumulate(v.begin(), v.end(), 0);\n\nBu kod derlenmez çünkü accumulate, std:: öneki olmadan çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int toplam = std::accumulate(v.begin(), v.end(), 0);"},
        .explanation = "std::accumulate öneki gereklidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2564, .topicId = 96,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::vector<int> v = {1, 2, 3}\nint toplam = std::accumulate(v.begin(), v.end(), 0);\n\nProgramcı v tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::vector<int> v = {1, 2, 3};"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2565, .topicId = 96,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir vektörün elemanlarını toplayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << toplam;\n    return 0;\n}", "std::vector<int> v = {3, 4, 5};\n    int toplam = std::accumulate(v.begin(), v.end(), 0);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+toplama (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2566, .topicId = 96,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir double vektörü tanımlayın (en az 3 değer); std::accumulate ile elemanları DOĞRU şekilde (uygun başlangıç değeriyle) toplayın ve ekrana yazdırın.",
        .acceptedAnswers = {"accumulate", "numeric"},
        .explanation = "double başlangıç değeriyle doğru toplam elde edilir.",
        .baseXp = 40,
    });

    // Topic 97: Dosyaya yazma
    questions.push_back(Question{
        .id = 2567, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::ofstream ne için kullanılır?",
        .options = {"Bir dosyayı silmek", "Bir dosyanın adını değiştirmek", "Bir dosyaya YAZMAK", "Bir dosyayı okumak"},
        .acceptedAnswers = {"c"},
        .explanation = "std::ofstream dosyaya yazmak için kullanılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2568, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::ofstream dosya(\"ad.txt\");\nDosya zaten VARSA ne olur (VARSAYILAN davranış)?",
        .options = {"Yeni içerik dosyanın SONUNA eklenir", "Açma başarısız olur, hata verir", "Dosya yeniden adlandırılır", "Dosyanın mevcut içeriği SİLİNİR (truncate)"},
        .acceptedAnswers = {"d"},
        .explanation = "Varsayılan olarak dosya truncate edilir (içeriği silinir).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2569, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Var olan bir dosyanın SONUNA eklemek (dosyayı silmeden) için ne kullanılmalıdır?",
        .options = {"std::ofstream dosya(\"ad.txt\", std::ios::app);", "std::ofstream dosya(\"ad.txt\"); (varsayılan)", "std::ifstream dosya(\"ad.txt\");", "Bu C++'ta mümkün değildir"},
        .acceptedAnswers = {"a"},
        .explanation = "std::ios::app modu sonuna ekleme yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2570, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir dosyaya yazmadan ÖNCE ne kontrol edilmelidir?",
        .options = {"Dosyanın boyutu", "dosya.is_open() (dosyanın gerçekten açılıp açılamadığı)", "Dosyanın oluşturulma tarihi", "Hiçbir şey, C++ otomatik kontrol eder"},
        .acceptedAnswers = {"b"},
        .explanation = "is_open() ile açılıp açılmadığı kontrol edilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2571, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream dosya(\"gecersiz/yol/ad.txt\");\nif (!dosya.is_open()) {\n    dosya << \"veri\";\n}\nBu kod (açma başarısız olduğunda dosyaya yazmaya çalışmak) ne olur?",
        .options = {"Program çöker", "Bir istisna (exception) fırlatılır", "Yazma SESSİZCE hiçbir şey yapmaz, program normal devam eder", "Derleme hatası oluşur"},
        .acceptedAnswers = {"c"},
        .explanation = "Açılamayan bir akışa yazmak sessizce hiçbir şey yapmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2572, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream, hangi başlığı gerektirir?",
        .options = {"<iostream>", "<sstream>", "<memory>", "<fstream>"},
        .acceptedAnswers = {"d"},
        .explanation = "std::ofstream <fstream> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2573, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::ofstream dosya1(\"ornek.txt\");\ndosya1 << \"Birinci\";\ndosya1.close();\nstd::ofstream dosya2(\"ornek.txt\");\ndosya2 << \"Ikinci\";\ndosya2.close();\nBu kodlar çalıştırıldıktan sonra ornek.txt dosyasının içeriği nedir?",
        .options = {"Ikinci", "BirinciIkinci", "Birinci", "Dosya boş kalır"},
        .acceptedAnswers = {"a"},
        .explanation = "İkinci açma dosyayı truncate eder; sadece \"Ikinci\" kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2574, .topicId = 97,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::ofstream dosya1(\"ornek2.txt\");\ndosya1 << \"Birinci\";\ndosya1.close();\nstd::ofstream dosya2(\"ornek2.txt\", std::ios::app);\ndosya2 << \"Ikinci\";\ndosya2.close();\nBu kodlar çalıştırıldıktan sonra ornek2.txt dosyasının içeriği nedir?",
        .options = {"Ikinci", "BirinciIkinci", "Birinci", "Dosya boş kalır"},
        .acceptedAnswers = {"b"},
        .explanation = "std::ios::app ile ikinci yazma sonuna eklenir; içerik \"BirinciIkinci\" olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2575, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::ofstream, bir dosyaya yazmak için kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2576, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::ofstream ile bir dosya açmak, dosya zaten VARSA içeriğinin SONUNA otomatik olarak ekler.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan olarak içerik silinir (truncate).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2577, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Var olan bir dosyanın sonuna eklemek için std::ios::app modu kullanılmalıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2578, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir dosyaya yazmadan önce .is_open() ile kontrol yapmak iyi bir uygulamadır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2579, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Açılamayan bir dosyaya yazmaya çalışmak, bir istisna (exception) fırlatır (varsayılan olarak).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: istisna fırlatmaz, sessizce hiçbir şey yapmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2580, .topicId = 97,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream, <fstream> başlığını gerektirir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2581, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dosyaya yazmak için kullanılan sınıf std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"ofstream"},
        .explanation = "std::ofstream kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2582, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::ofstream ile bir dosya açmak, dosya zaten varsa içeriğini VARSAYILAN olarak _____ (Türkçe kelime, 'siler' anlamında).",
        .acceptedAnswers = {"siler"},
        .explanation = "Varsayılan olarak içerik silinir (truncate).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2583, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Var olan bir dosyanın sonuna eklemek için std::ios::_____ modu kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"app"},
        .explanation = "std::ios::app kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2584, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir dosyanın başarıyla açılıp açılmadığını kontrol eden üye fonksiyon _____ dir (İngilizce, kelimeler birleşik, alt çizgili).",
        .acceptedAnswers = {"is_open"},
        .explanation = "is_open() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2585, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream, hangi başlığı gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"fstream"},
        .explanation = "<fstream> başlığı gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2586, .topicId = 97,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Açılamayan bir dosyaya yazmak, bir istisna FIRLATMAZ; yazma sessizce hiçbir şey _____ (Türkçe kelime, 'yapmaz' anlamında).",
        .acceptedAnswers = {"yapmaz"},
        .explanation = "Sessizce hiçbir şey yapmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2587, .topicId = 97,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\ndosya << \"veri\";\ndosya.close();\ndosya adlı bir std::ofstream'i \"cikti.txt\" dosyasıyla açan satırı yazın.",
        .acceptedAnswers = {"std::ofstream dosya(\"cikti.txt\");"},
        .explanation = "std::ofstream ile dosya açılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2588, .topicId = 97,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream dosya(\"cikti.txt\");\n_____\ndosya << \"veri\";\ndosya'nın gerçekten açılıp açılmadığını kontrol eden if satırını yazın.",
        .acceptedAnswers = {"if (dosya.is_open()) {"},
        .explanation = "is_open() ile kontrol edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2589, .topicId = 97,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream dosya(\"test1.txt\");\nstd::cout << dosya.is_open();\nYukarıdaki kodun ekran çıktısı nedir (dosyanın başarıyla açıldığı varsayılarak)?",
        .acceptedAnswers = {"1"},
        .explanation = "Başarıyla açıldığında is_open() true (1) döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2590, .topicId = 97,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::ofstream dosya1(\"test2.txt\");\ndosya1 << \"A\";\ndosya1.close();\nstd::ofstream dosya2(\"test2.txt\");\ndosya2 << \"B\";\ndosya2.close();\nstd::ifstream okuyucu(\"test2.txt\");\nstd::string icerik;\nstd::getline(okuyucu, icerik);\nstd::cout << icerik;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"B"},
        .explanation = "İkinci ofstream açması dosyayı truncate eder; sadece \"B\" kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2591, .topicId = 97,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::ofstream dosya(\"cikti.txt\");\ndosya << \"veri\";\n\nBu kod ÇALIŞIR ama YANLIŞTIR çünkü dosya.is_open() KONTROL EDİLMEDEN yazılıyor; açma başarısız olursa yazma sessizce hiçbir şey yapmaz ve fark edilmez. Kontrol ekleyerek düzeltilmiş kodu yazın.",
        .acceptedAnswers = {"if (dosya.is_open()) { dosya << \"veri\"; }"},
        .explanation = "is_open() kontrolü eklenmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2592, .topicId = 97,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::ofstream dosya1(\"gunluk.txt\");\ndosya1 << \"Ilk kayit\";\ndosya1.close();\nstd::ofstream dosya2(\"gunluk.txt\");\ndosya2 << \"Ikinci kayit\";\ndosya2.close();\n// Beklenen: dosyada hem \"Ilk kayit\" hem \"Ikinci kayit\" olsun\n\nBu kod, İKİNCİ açmanın VARSAYILAN olarak dosyayı KIRPMASI (truncate) nedeniyle \"Ilk kayit\"i SİLER; sadece \"Ikinci kayit\" kalır. İkinci açma satırını, std::ios::app kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::ofstream dosya2(\"gunluk.txt\", std::ios::app);"},
        .explanation = "std::ios::app ile içerik silinmez, sonuna eklenir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2593, .topicId = 97,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::ofstream dosya(\"cikti.txt\")\ndosya << \"veri\";\n\nProgramcı dosya tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::ofstream dosya(\"cikti.txt\");"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2594, .topicId = 97,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir dosyaya yazan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"dosya.close();\n    return 0;\n}", "std::ofstream dosya(\"cikti.txt\");\n    dosya << \"veri\";", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+yazma (2), kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2595, .topicId = 97,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir dosyaya yazan bir program yazın: dosyayı is_open() ile kontrol edin, \"Merhaba\" yazın ve dosyayı kapatın.",
        .acceptedAnswers = {"ofstream", "is_open"},
        .explanation = "Dosya açılıp kontrol edildikten sonra yazılır.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Build and run the full test suite**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `95/95 test(s) passed.` (unchanged from Task 1's end state —
the test that counts questions per topic is added in Task 4, once all
of topics 91-100 have their full 29 questions each).

- [ ] **Step 3: Commit**

```bash
git add src/QuestionsSection10.cpp
git commit -m "feat(content): add questions for topics 95-97 (ids 2509-2595)"
```

---

### Task 4: Questions for topics 98-100 (ids 2596-2682), test updates, and final integration

**Files:**
- Modify: `src/QuestionsSection10.cpp` (append the final `push_back`
  calls to `appendSection10Questions`)
- Modify: `tests/QuestionManagerTests.cpp` (add one new per-section
  minimum-count test)
- Modify: `docs/superpowers/roadmap.md` (mark Phase 21 complete AND
  update the top "Confirmed gaps" section — see Step 6)

**Interfaces:**
- Consumes: `appendSection10Questions(std::vector<Question>& questions)`
  in `src/QuestionsSection10.cpp` — append after Task 3's last id
  (2595), before the function's closing `}`. After this task, ids
  2393-2682 are all present (10 topics x 29 questions) and the function
  is complete. **This completes the FULL 100-topic question bank
  (ids 1-2682, all topics 1-100 with >= 29 questions each).**

- [ ] **Step 1: Write topics 98-100's questions**

Open `src/QuestionsSection10.cpp` as it exists on disk (Task 3's
committed state) and insert the following `push_back` calls right
after the id-2595 block, before the function's closing `}`:

```cpp
    // Topic 98: Dosyadan okuma
    questions.push_back(Question{
        .id = 2596, .topicId = 98,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::ifstream ne için kullanılır?",
        .options = {"Bir dosyayı silmek", "Bir dosyaya yazmak", "Bir dosyanın adını değiştirmek", "Bir dosyadan okumak"},
        .acceptedAnswers = {"d"},
        .explanation = "std::ifstream dosyadan okumak için kullanılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2597, .topicId = 98,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::getline(dosya, satir) ne yapar?",
        .options = {"Dosyadan TAM BİR SATIRI (boşluklar dahil) satir'e okur", "Dosyadan sadece bir karakter okur", "Dosyanın tamamını siler", "Dosyaya bir satır yazar"},
        .acceptedAnswers = {"a"},
        .explanation = "std::getline tam bir satırı okur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2598, .topicId = 98,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "dosya >> degisken ifadesi ne okur?",
        .options = {"Dosyanın tamamını", "Sadece bir sonraki BOŞLUKLA AYRILMIŞ TOKEN'ı", "Tam bir satırı (boşluklar dahil)", "Dosyanın son satırını"},
        .acceptedAnswers = {"b"},
        .explanation = ">> operatörü boşlukla ayrılmış bir token okur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2599, .topicId = 98,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Dosyanın SONUNA (EOF) ulaşıldıktan sonra okumaya devam etmeye çalışmak ne yapar?",
        .options = {"Program çöker", "Bir istisna (exception) fırlatılır", "Akış BAŞARISIZ (fail) duruma girer (istisna fırlatmadan)", "Otomatik olarak dosyanın başına döner"},
        .acceptedAnswers = {"c"},
        .explanation = "EOF sonrası okuma akışı fail durumuna sokar, istisna fırlatmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2600, .topicId = 98,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::ifstream'in başarıyla açılıp açılmadığını kontrol etmek için ne kullanılır?",
        .options = {".size()", ".length()", ".exists()", ".is_open()"},
        .acceptedAnswers = {"d"},
        .explanation = ".is_open() ile kontrol edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2601, .topicId = 98,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::ifstream, hangi başlığı gerektirir?",
        .options = {"<fstream>", "<iostream>", "<sstream>", "<memory>"},
        .acceptedAnswers = {"a"},
        .explanation = "std::ifstream <fstream> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2602, .topicId = 98,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Var olmayan bir dosya için std::ifstream dosya(\"olmayan.txt\");\nBu kod derlenir mi ve is_open() ne döner?",
        .options = {"Derleme hatası oluşur", "Derlenir; is_open() false döner", "Derlenir; is_open() true döner", "Derlenir ama çalışma zamanında çöker"},
        .acceptedAnswers = {"b"},
        .explanation = "Var olmayan bir dosya açma başarısız olur; is_open() false döner, çökme/istisna olmaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2603, .topicId = 98,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::ifstream dosya(\"veri.txt\");\nstd::string satir1, satir2;\nstd::getline(dosya, satir1);\nstd::getline(dosya, satir2);\nBu kod, dosyanın kaç SATIRINI okur (dosyada en az 2 satır olduğu varsayılarak)?",
        .options = {"Sadece 1 satır", "Dosyanın tamamını tek seferde", "İki AYRI satırı sırayla", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "Her getline çağrısı bir sonraki satırı okur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2604, .topicId = 98,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::ifstream, bir dosyadan okumak için kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2605, .topicId = 98,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::getline, sadece boşlukla ayrılmış tek bir kelime okur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: getline tam bir satırı okur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2606, .topicId = 98,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Dosyanın sonuna ulaşıldıktan sonra okumaya devam etmek bir istisna fırlatır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: istisna fırlatmaz, akışı fail durumuna sokar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2607, .topicId = 98,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::ifstream'in başarıyla açılıp açılmadığı .is_open() ile kontrol edilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2608, .topicId = 98,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "dosya >> degisken, tam bir satırı (boşluklar dahil) okur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: >> sadece bir token okur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2609, .topicId = 98,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Var olmayan bir dosya için std::ifstream açmak derleme hatası vermez, sadece is_open() false döner.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2610, .topicId = 98,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dosyadan okumak için kullanılan sınıf std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"ifstream"},
        .explanation = "std::ifstream kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2611, .topicId = 98,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Tam bir satırı okuyan fonksiyon std::_____ dir (İngilizce kelime).",
        .acceptedAnswers = {"getline"},
        .explanation = "std::getline kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2612, .topicId = 98,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::ifstream, hangi başlığı gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"fstream"},
        .explanation = "<fstream> başlığı gerekir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2613, .topicId = 98,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Dosyanın sonuna ulaşıldıktan sonra okuma, akışı _____ (Türkçe kelime, 'başarısız' anlamında) duruma sokar.",
        .acceptedAnswers = {"başarısız"},
        .explanation = "Akış başarısız (fail) durumuna girer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2614, .topicId = 98,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "dosya >> degisken, sadece boşlukla ayrılmış bir _____ okur (İngilizce kelime).",
        .acceptedAnswers = {"token"},
        .explanation = "Bir token okunur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2615, .topicId = 98,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir dosyanın başarıyla açılıp açılmadığını kontrol eden üye fonksiyon _____ dir (İngilizce, kelimeler birleşik, alt çizgili).",
        .acceptedAnswers = {"is_open"},
        .explanation = "is_open() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2616, .topicId = 98,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::string satir;\nstd::getline(dosya, satir);\ndosya adlı bir std::ifstream'i \"veri.txt\" dosyasıyla açan satırı yazın.",
        .acceptedAnswers = {"std::ifstream dosya(\"veri.txt\");"},
        .explanation = "std::ifstream ile dosya açılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2617, .topicId = 98,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::ifstream dosya(\"veri.txt\");\nstd::string satir;\n_____\ndosyadan tam bir satırı satir'e okuyan satırı yazın.",
        .acceptedAnswers = {"std::getline(dosya, satir);"},
        .explanation = "std::getline ile satır okunur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2618, .topicId = 98,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::ofstream yazici(\"gecici.txt\");\nyazici << \"Merhaba\";\nyazici.close();\nstd::ifstream okuyucu(\"gecici.txt\");\nstd::string satir;\nstd::getline(okuyucu, satir);\nstd::cout << satir;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Merhaba"},
        .explanation = "Yazılan içerik geri okunur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2619, .topicId = 98,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::ofstream yazici(\"gecici2.txt\");\nyazici << \"Bir\\nIki\";\nyazici.close();\nstd::ifstream okuyucu(\"gecici2.txt\");\nstd::string s1, s2;\nstd::getline(okuyucu, s1);\nstd::getline(okuyucu, s2);\nstd::cout << s1 << \" \" << s2;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Bir Iki"},
        .explanation = "İki ayrı satır sırayla okunur: Bir, Iki.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2620, .topicId = 98,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::ifstream dosya(\"veri.txt\");\nstd::string satir;\ngetline(dosya, satir);\n\nBu kod derlenmez çünkü getline, std:: öneki olmadan çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::getline(dosya, satir);"},
        .explanation = "std::getline öneki gereklidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2621, .topicId = 98,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::ifstream dosya(\"veri.txt\");\ndosya << \"yeni veri\";\n\nBu kod derlenmez çünkü std::ifstream sadece OKUMA yapabilir; << operatörü (yazma) bir std::ofstream ya da std::fstream gerektirir. Hatalı satırı, dosyadan okuyacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::string satir; std::getline(dosya, satir);"},
        .explanation = "ifstream sadece okuma yapabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2622, .topicId = 98,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::ifstream dosya(\"veri.txt\")\nstd::string satir;\nstd::getline(dosya, satir);\n\nProgramcı dosya tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::ifstream dosya(\"veri.txt\");"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2623, .topicId = 98,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir dosyadan okuyup yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << satir;\n    return 0;\n}", "std::ifstream dosya(\"veri.txt\");\n    std::string satir;\n    std::getline(dosya, satir);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım+okuma (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2624, .topicId = 98,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir dosyadan okuyan bir program yazın: dosyayı is_open() ile kontrol edin, bir satırı getline ile okuyun ve ekrana yazdırın.",
        .acceptedAnswers = {"ifstream", "getline"},
        .explanation = "Dosya kontrol edilip okunmalıdır.",
        .baseXp = 40,
    });

    // Topic 99: try-catch
    questions.push_back(Question{
        .id = 2625, .topicId = 99,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "throw ifadesi ne yapar?",
        .options = {"Bir istisna (exception) fırlatır", "Bir döngüyü sonlandırır", "Bir dosyayı kapatır", "Bir değişkeni siler"},
        .acceptedAnswers = {"a"},
        .explanation = "throw bir istisna fırlatır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2626, .topicId = 99,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "try {\n    throw std::runtime_error(\"hata\");\n} catch (const std::exception& e) {\n    std::cout << e.what();\n}\nEkran çıktısı nedir?",
        .options = {"throw", "hata", "Derleme hatası", "Program çöker"},
        .acceptedAnswers = {"b"},
        .explanation = "e.what() \"hata\" mesajını döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2627, .topicId = 99,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "İstisnaları neden REFERANS (const&) ile yakalamak tercih edilir?",
        .options = {"Daha az bellek kullanır", "Daha hızlı çalışır", "OBJECT SLICING'i önler", "Zorunludur, değer ile yakalamak derleme hatasıdır"},
        .acceptedAnswers = {"c"},
        .explanation = "Referans ile yakalamak slicing'i önler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2628, .topicId = 99,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "try {\n    // hata olusturmayan kod\n} catch (...) {\n    std::cout << \"hata\";\n}\nstd::cout << \"devam\";\nHiçbir istisna fırlatılmazsa çıktı nedir?",
        .options = {"hata", "hatadevam", "Derleme hatası", "devam"},
        .acceptedAnswers = {"d"},
        .explanation = "İstisna fırlatılmadığından catch bloğu çalışmaz, sadece \"devam\" yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2629, .topicId = 99,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Birden fazla catch bloğu (aralarında taban/türetilmiş sınıf ilişkisi olmadığında), hangi sırayla denenir?",
        .options = {"YAZILDIKLARI sırayla, ilk eşleşen çalışır", "En spesifikten en genele doğru, yazım sırasından bağımsız", "Rastgele", "Sadece SON catch bloğu denenir"},
        .acceptedAnswers = {"a"},
        .explanation = "catch blokları yazıldıkları sırayla denenir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2630, .topicId = 99,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "catch(...) bloğu ne yakalar?",
        .options = {"Sadece std::exception türevlerini", "HER TÜRLÜ istisnayı", "Sadece int türündeki istisnaları", "Hiçbir şeyi, sözdizimi hatasıdır"},
        .acceptedAnswers = {"b"},
        .explanation = "catch(...) her türlü istisnayı yakalar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2631, .topicId = 99,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Yakalanmayan (uncaught) bir istisna ne olur?",
        .options = {"Sessizce yok sayılır", "Otomatik olarak main()'e dönüştürülür", "Çağrı yığınında yukarı doğru yayılır (main'e kadar ulaşırsa program sonlanır)", "Bir uyarı (warning) olarak loglanır ama program devam eder"},
        .acceptedAnswers = {"c"},
        .explanation = "Yakalanmayan istisna çağrı yığınında yukarı yayılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2632, .topicId = 99,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "try {\n    throw 5;\n} catch (const std::string& e) {\n    std::cout << \"string yakalandi\";\n} catch (int e) {\n    std::cout << \"int yakalandi: \" << e;\n}\nEkran çıktısı nedir?",
        .options = {"string yakalandi", "Derleme hatası", "Program çöker (yakalanmayan istisna)", "int yakalandi: 5"},
        .acceptedAnswers = {"d"},
        .explanation = "throw 5 bir int'tir; ilk catch (std::string) eşleşmez, ikinci catch (int) eşleşir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2633, .topicId = 99,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "throw, bir istisna fırlatır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2634, .topicId = 99,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "catch(...) bloğu sadece std::exception türevi istisnaları yakalar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: catch(...) her türlü istisnayı yakalar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2635, .topicId = 99,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "İstisnaları değer olarak (referans olmadan) yakalamak object slicing'e yol açabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2636, .topicId = 99,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Birden fazla catch bloğu varsa, yazıldıkları sırayla denenir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2637, .topicId = 99,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Genel bir catch(...) bloğu, daha spesifik bir catch bloğundan ÖNCE yazılırsa, bu bir DERLEME HATASIDIR.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: sonraki bloğu ulaşılamaz (unreachable) kıldığından derleyici bunu hata olarak bildirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2638, .topicId = 99,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Yakalanmayan bir istisna, sessizce yok sayılır ve program normal devam eder.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: çağrı yığınında yukarı yayılır, main'e ulaşırsa program sonlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2639, .topicId = 99,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir istisna fırlatmak için kullanılan anahtar kelime _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"throw"},
        .explanation = "throw kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2640, .topicId = 99,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "İstisnayı yakalamak için kullanılan blok _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"catch"},
        .explanation = "catch kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2641, .topicId = 99,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "İstisna nesnesinin açıklama mesajını döndüren üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"what"},
        .explanation = "what() kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2642, .topicId = 99,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "İstisnaları slicing'den korumak için (const&) ile _____ edilmelidir (Türkçe kelime, 'yakalanmalı' anlamında).",
        .acceptedAnswers = {"yakalanmalı"},
        .explanation = "Referans ile yakalanmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2643, .topicId = 99,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Her türlü istisnayı yakalayan catch bloğu catch(_____) şeklinde yazılır (üç nokta).",
        .acceptedAnswers = {"..."},
        .explanation = "catch(...) her türlü istisnayı yakalar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2644, .topicId = 99,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Yakalanmayan bir istisna, çağrı yığınında _____ doğru yayılır (Türkçe kelime).",
        .acceptedAnswers = {"yukarı"},
        .explanation = "Çağrı yığınında yukarı doğru yayılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2645, .topicId = 99,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "try {\n_____\n} catch (const std::exception& e) {\n    std::cout << \"yakalandi: \" << e.what();\n}\ntry bloğu içinde \"sorun\" mesajıyla bir std::runtime_error fırlatan satırı yazın.",
        .acceptedAnswers = {"throw std::runtime_error(\"sorun\");"},
        .explanation = "throw ile istisna fırlatılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2646, .topicId = 99,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "try {\n    throw std::runtime_error(\"hata\");\n} _____ {\n    std::cout << e.what();\n}\nistisnayı const std::exception& olarak yakalayan catch satırını yazın.",
        .acceptedAnswers = {"catch (const std::exception& e)"},
        .explanation = "İstisna referans ile yakalanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2647, .topicId = 99,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "try {\n    throw std::runtime_error(\"tamam\");\n} catch (const std::exception& e) {\n    std::cout << e.what();\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"tamam"},
        .explanation = "e.what() \"tamam\" mesajını döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2648, .topicId = 99,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "try {\n    throw 3.14;\n} catch (int e) {\n    std::cout << \"int\";\n} catch (double e) {\n    std::cout << \"double: \" << e;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"double: 3.14"},
        .explanation = "throw 3.14 bir double'dır; ilk catch (int) eşleşmez, ikinci catch (double) eşleşir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2649, .topicId = 99,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\ntry {\n    throw std::runtime_error(\"sorun\");\n} catch (std::exception e) {\n    std::cout << e.what();\n}\n\nBu kod TEKNİK OLARAK derlenir ama YANLIŞTIR çünkü istisna DEĞER olarak (referans olmadan) yakalanıyor; bu OBJECT SLICING riski taşır. Hatalı catch satırını, referans kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"catch (const std::exception& e) {"},
        .explanation = "Referans ile yakalamak slicing'i önler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2650, .topicId = 99,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\ntry {\n    throw std::runtime_error(\"ozel hata\");\n} catch (...) {\n    std::cout << \"genel\";\n} catch (const std::exception& e) {\n    std::cout << \"ozel: \" << e.what();\n}\n\nBu kod derlenmez çünkü genel catch(...) bloğu, daha SPESIFIK bir catch'ten ÖNCE yazılamaz (derleyici bunu ulaşılamaz kod olarak algılayıp hata verir); catch(...) bloğu HER ZAMAN EN SONA yazılmalıdır. Hatalı sırayı, catch(...) bloğunu en sona alarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"catch (const std::exception& e) { std::cout << \"ozel: \" << e.what(); } catch (...) { std::cout << \"genel\"; }"},
        .explanation = "catch(...) her zaman en sona yazılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2651, .topicId = 99,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\ntry {\n    throw std::runtime_error(\"hata\")\n} catch (const std::exception& e) {\n    std::cout << e.what();\n}\n\nProgramcı throw satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"throw std::runtime_error(\"hata\");"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2652, .topicId = 99,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir istisna fırlatıp yakalayan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"} catch (const std::exception& e) {\n        std::cout << e.what();\n    }\n    return 0;\n}", "try {\n        throw std::runtime_error(\"deneme\");", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), try+throw (2), catch+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2653, .topicId = 99,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir try/catch bloğu yazın: try içinde bir std::runtime_error fırlatın, catch (const std::exception&) ile yakalayıp e.what()'i ekrana yazdırın.",
        .acceptedAnswers = {"try", "catch", "what"},
        .explanation = "İstisna referans ile yakalanmalıdır.",
        .baseXp = 40,
    });

    // Topic 100: unique_ptr
    questions.push_back(Question{
        .id = 2654, .topicId = 100,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::unique_ptr<T>'nin temel özelliği nedir?",
        .options = {"Birden fazla pointer aynı nesneyi paylaşabilir", "Otomatik olarak kopyalanabilir", "Bellek yönetimini elle yapmayı gerektirir", "Dinamik bir nesneyi TEK BAŞINA (exclusive) sahiplenir"},
        .acceptedAnswers = {"d"},
        .explanation = "unique_ptr, tek başına (exclusive) sahiplik sağlar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2655, .topicId = 100,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::unique_ptr<int> p = std::make_unique<int>(10);\nstd::cout << *p;\nEkran çıktısı nedir?",
        .options = {"10", "0", "Bir adres", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "*p, sahip olunan değere (10) erişir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2656, .topicId = 100,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::unique_ptr<int> p1 = std::make_unique<int>(5);\nstd::unique_ptr<int> p2 = p1;\nBu kod derlenir mi?",
        .options = {"Evet, p2 p1'in bir kopyasını alır", "Hayır, unique_ptr kopyalanamaz (kopya oluşturucusu silinmiştir), derleme hatası oluşur", "Evet ama p1 boş kalır", "Evet, ikisi de aynı nesneyi paylaşır"},
        .acceptedAnswers = {"b"},
        .explanation = "unique_ptr kopyalanamaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2657, .topicId = 100,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::unique_ptr<int> p1 = std::make_unique<int>(5);\nstd::unique_ptr<int> p2 = std::move(p1);\nstd::cout << (p1 == nullptr);\nEkran çıktısı nedir?",
        .options = {"0", "5", "1", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "std::move sonrası p1 nullptr olur; p1 == nullptr true (1).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2658, .topicId = 100,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::unique_ptr, kapsam dışına çıktığında ne olur?",
        .options = {"Hiçbir şey, elle delete çağrılmalıdır", "Bellek sızıntısı (memory leak) oluşur", "Program çöker", "Sahip olduğu nesne OTOMATİK OLARAK silinir (RAII)"},
        .acceptedAnswers = {"d"},
        .explanation = "unique_ptr RAII ile otomatik temizlik yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2659, .topicId = 100,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::unique_ptr, hangi başlığı gerektirir?",
        .options = {"<memory>", "<fstream>", "<numeric>", "<algorithm>"},
        .acceptedAnswers = {"a"},
        .explanation = "std::unique_ptr <memory> başlığında tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2660, .topicId = 100,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::unique_ptr<int> p1 = std::make_unique<int>(7);\nint* ham = p1.get();\nstd::cout << *ham;\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, derleme hatası", "Evet, çıktı 7'dir", "Evet, çıktı bir adres olur", "Evet ama çalışma zamanı hatası verir"},
        .acceptedAnswers = {"b"},
        .explanation = ".get(), sahipliği devretmeden ham pointer'ı döndürür; *ham aynı nesneye (7) erişir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2661, .topicId = 100,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::unique_ptr<int> yarat() {\n    return std::make_unique<int>(99);\n}\nint main() {\n    std::unique_ptr<int> p = yarat();\n    std::cout << *p;\n    return 0;\n}\nBu kod derlenir mi ve çıktısı nedir?",
        .options = {"Hayır, unique_ptr fonksiyondan döndürülemez", "Evet ama çalışma zamanı hatası verir", "Evet, derlenir; çıktı 99'dur", "Derleme hatası, kopya oluşturucusu silinmiştir"},
        .acceptedAnswers = {"c"},
        .explanation = "unique_ptr, taşıma semantiği sayesinde bir fonksiyondan değer olarak döndürülebilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2662, .topicId = 100,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::unique_ptr, dinamik bir nesneyi tek başına (exclusive) sahiplenir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2663, .topicId = 100,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "std::unique_ptr kopyalanabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: unique_ptr kopyalanamaz.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2664, .topicId = 100,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::unique_ptr, std::move ile taşınabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2665, .topicId = 100,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "std::unique_ptr, kapsam dışına çıktığında sahip olduğu nesneyi otomatik olarak siler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2666, .topicId = 100,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = ".get(), unique_ptr'ın sahipliğini ham pointer'a DEVREDER.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: .get() sahipliği devretmez, sadece ham pointer'ı döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2667, .topicId = 100,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::unique_ptr, bir fonksiyondan değer olarak (by value) döndürülebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2668, .topicId = 100,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Dinamik bir nesneyi tek başına sahiplenen akıllı işaretçi std::_____ dir (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"unique_ptr"},
        .explanation = "std::unique_ptr kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2669, .topicId = 100,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "unique_ptr oluşturmanın önerilen yolu std::_____ fonksiyonudur (İngilizce iki kelime, alt çizgiyle).",
        .acceptedAnswers = {"make_unique"},
        .explanation = "std::make_unique kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2670, .topicId = 100,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "unique_ptr, hangi başlığı gerektirir (İngilizce kelime)?",
        .acceptedAnswers = {"memory"},
        .explanation = "<memory> başlığı gerekir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2671, .topicId = 100,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "unique_ptr'ın sahipliğini bir başka unique_ptr'a aktarmak için std::_____ kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"move"},
        .explanation = "std::move kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2672, .topicId = 100,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "unique_ptr'ın sahip olduğu ham pointer'ı, sahipliği devretmeden döndüren üye fonksiyon _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"get"},
        .explanation = "get() kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2673, .topicId = 100,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "unique_ptr'ın kapsam dışına çıktığında sahip olduğu nesneyi otomatik silmesi prensibine _____ denir (İngilizce kısaltma, üç harf).",
        .acceptedAnswers = {"RAII"},
        .explanation = "Bu prensibe RAII denir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2674, .topicId = 100,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << *p;\np adlı bir unique_ptr<int>'i 15 değeriyle oluşturan satırı yazın.",
        .acceptedAnswers = {"std::unique_ptr<int> p = std::make_unique<int>(15);"},
        .explanation = "std::make_unique ile oluşturulur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2675, .topicId = 100,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::unique_ptr<int> p1 = std::make_unique<int>(20);\n_____\nstd::cout << *p2;\nsahipliği p1'den p2'ye taşıyan satırı yazın.",
        .acceptedAnswers = {"std::unique_ptr<int> p2 = std::move(p1);"},
        .explanation = "std::move ile sahiplik taşınır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2676, .topicId = 100,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::unique_ptr<int> p = std::make_unique<int>(33);\nstd::cout << *p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"33"},
        .explanation = "*p, sahip olunan değere (33) erişir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2677, .topicId = 100,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::unique_ptr<int> p1 = std::make_unique<int>(8);\nstd::unique_ptr<int> p2 = std::move(p1);\n*p2 = 100;\nstd::cout << (p1 == nullptr) << \" \" << *p2;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 100"},
        .explanation = "p1 taşındıktan sonra nullptr olur (1); p2 üzerinden değer 100 olarak değiştirilmiştir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2678, .topicId = 100,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::unique_ptr<int> p1 = std::make_unique<int>(5);\nstd::unique_ptr<int> p2 = p1;\n\nBu kod derlenmez çünkü unique_ptr KOPYALANAMAZ (kopya oluşturucusu silinmiştir). Hatalı satırı, std::move kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::unique_ptr<int> p2 = std::move(p1);"},
        .explanation = "std::move ile taşıma yapılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2679, .topicId = 100,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid fonksiyon(std::unique_ptr<int> p) { std::cout << *p; }\nint main() {\n    std::unique_ptr<int> p1 = std::make_unique<int>(9);\n    fonksiyon(p1);\n    return 0;\n}\n\nBu kod derlenmez çünkü fonksiyon, unique_ptr'ı DEĞER olarak alıyor ve p1'i fonksiyona geçirmek bir KOPYALAMA gerektiriyor (unique_ptr kopyalanamaz). Hatalı çağrı satırını, std::move kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"fonksiyon(std::move(p1));"},
        .explanation = "std::move ile fonksiyona taşınmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2680, .topicId = 100,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::unique_ptr<int> p = std::make_unique<int>(5)\nstd::cout << *p;\n\nProgramcı p tanımının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::unique_ptr<int> p = std::make_unique<int>(5);"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2681, .topicId = 100,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir unique_ptr oluşturup değerini yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << *p;\n    return 0;\n}", "std::unique_ptr<int> p = std::make_unique<int>(42);", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), tanım (2), yazdır+kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2682, .topicId = 100,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir unique_ptr<int> oluşturun (std::make_unique ile); değerini yazdırın, sonra std::move ile başka bir unique_ptr'a taşıyın ve yeni pointer'ın değerini de yazdırın.",
        .acceptedAnswers = {"unique_ptr", "make_unique", "move"},
        .explanation = "unique_ptr, std::move ile taşınarak kullanılır.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Add a per-topic minimum-count test**

In `tests/QuestionManagerTests.cpp`, add this new test case right after
`QuestionManager_EveryTopicEightyOneToNinetyHasAtLeastTwentyNineQuestions`
(do not modify that existing test, and do not touch
`QuestionManager_NoDuplicateQuestionIds`, which already scans topics
1-100):

```cpp
TEST_CASE(QuestionManager_EveryTopicNinetyOneToHundredHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 91; topicId <= 100; ++topicId) {
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

- [ ] **Step 4: Manual verification — topic 100 end-to-end**

Run the app (`./build/Debug/CppMasterConsole.exe`), navigate to the
topic browser, choose Section 10, choose topic 100 ("unique_ptr"):

1. Confirm the lesson text prints (matches the `explanation`/`syntax`/
   `exampleCode` written in Task 1) — proving `openTopic`'s content
   gate passes for topic 100 with zero `Application.cpp` changes.
2. Confirm "Konu testi başlıyor (29 soru)." prints.
3. Answer a few questions, then use `cikis` to return to the main menu.
4. Confirm the app returns to the main menu without crashing, and that
   partial XP is awarded.
5. Clean up: `rm -f data/*.txt`.

- [ ] **Step 5: Commit the question content and test changes**

```bash
git add src/QuestionsSection10.cpp tests/QuestionManagerTests.cpp
git commit -m "feat(content): add questions for topics 98-100 (ids 2596-2682), widen coverage tests"
```

- [ ] **Step 6: Update the roadmap**

This step differs from Phases 13-20: this is the LAST content phase,
so in addition to the usual per-phase bullet, TWO headline items in
`docs/superpowers/roadmap.md`'s "Confirmed gaps" section (near the top
of the file) must be updated to reflect that they are now resolved.

In `docs/superpowers/roadmap.md`:

1. Add a new bullet for Phase 21 under "Phase order," immediately
   after the Phase 20 entry, following the EXACT format Phases 8-20
   use (`**Phase N — name: COMPLETE** (commits \`X..Y\`, ...)`), with
   the commit range starting at this phase's spec commit (the commit
   for "Add design spec for Bölüm 10 İçerik Genişletmesi (phase 21)")
   and ending at this task's final content commit (from Step 5 above).
   Note in this bullet's final sentence that this is the LAST of the
   nine section-by-section content phases (13-21), and that all 100
   topics now have real lesson content and a full question bank.

2. Update the "Status" section to say Phase 21 is complete and Phase
   22 (Sınavlar — remaining exams + the 100-question general final
   exam) starts next.

3. In the "Confirmed gaps" section near the top of the file, prefix
   the two bullets that are now resolved with a `~~strikethrough~~`
   (matching the existing convention already used for the "Ayarlar"
   bullet resolved in Phase 8) and a short "— **resolved in Phase 21**"
   note, for exactly these two bullets:
   - "Only topics 1-10 (Section 1) have lesson content; topics 11-100
     exist only as id/title/section entries."
   - "Only 72 hand-written questions exist (all for topics 1-10); the
     spec asked for a bank of at least 2900 (≥29 per topic × 100
     topics)." — note in the resolved annotation that the ACTUAL final
     count is 2682 (29 per topic × 100 topics, better distributed than
     the original ≥29-per-topic ask since the 10 introductory topics
     from the "static lesson + quiz core" phase already had their own
     pre-existing question set that was never reduced), not exactly
     2900, and that this is expected/correct, not a shortfall — the
     "≥29 per topic" requirement is fully met for every topic.

Then commit:

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 21 complete in roadmap, close out content-expansion gaps"
```

---

# Bölüm 5 İçerik Genişletmesi Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Give topics 41-50 (Section 5, "Fonksiyonlar") real lesson
content and a 29-question-per-topic question bank (290 questions
total), the fifth of nine content-expansion phases, following the exact
same architecture Phases 13-15 established and merged.

**Architecture:** Two new per-section content files
(`src/LessonContentSection5.cpp`, `src/QuestionsSection5.cpp`), declared
in the SAME shared headers Phases 13-15 created (`src/LessonContent.h`,
`src/QuestionContent.h` — this phase adds one more declaration to each,
it does not replace the existing ones). No `Application.cpp` changes
needed.

**Tech Stack:** C++20, standard library only, existing `Lesson`/`Question`
structs, existing `LessonManager`/`QuestionManager` classes.

## Global Constraints

- Topics covered: 41 (Parametresiz fonksiyon), 42 (Parametre alan
  fonksiyon), 43 (Değer döndüren fonksiyon), 44 (Fonksiyon prototipi),
  45 (Varsayılan parametre), 46 (Fonksiyon aşırı yükleme), 47 (Değer ile
  parametre gönderme), 48 (Referans ile parametre gönderme), 49 (const
  referans), 50 (Recursion) — sectionId 5.
- Lesson content mirrors the existing `Lesson` struct fields exactly:
  `explanation`, `syntax`, `exampleCode`, `lineExplanations`,
  `commonMistakes` — no new fields.
- Question ids sequential starting at 943 (Phase 15 ended at 942): topic
  41 = 943-971, topic 42 = 972-1000, topic 43 = 1001-1029, topic 44 =
  1030-1058, topic 45 = 1059-1087, topic 46 = 1088-1116, topic 47 =
  1117-1145, topic 48 = 1146-1174, topic 49 = 1175-1203, topic 50 =
  1204-1232. Exactly 29 per topic.
- Per-topic type/difficulty/baseXp distribution (identical to every
  topic in Phases 13-15 — fixed project-wide convention):

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
- **Function semantic constraints, verified against real C++ before
  authoring (every prior content phase needed at least one compiler-
  verified fix — verify, don't assume):**
  - Function overloading is resolved by the parameter list (types
    and/or count) alone. Two functions with identical parameter lists
    but different return types are NOT valid overloads — any question
    claiming otherwise is wrong.
  - Default parameters must be trailing: once a parameter has a default
    value, every parameter after it must also have one.
  - Pass by value creates an independent copy; changes inside the
    function never affect the caller's original argument.
  - Pass by reference (`T&`) lets the function modify the caller's
    original variable directly; a non-const reference cannot bind to a
    literal/temporary.
  - `const T&` combines no-copy efficiency with immutability — the
    function cannot modify the parameter, but a `const` reference CAN
    bind to a literal/temporary (unlike a non-const reference).
  - Recursion needs a reachable base case; missing/unreachable base
    cases cause unbounded recursion and stack overflow, not a clean
    infinite loop. Each call has its own independent locals/parameters.

---

### Task 1: Section 5 lesson content

**Files:**
- Modify: `src/LessonContent.h` (add one new declaration)
- Create: `src/LessonContentSection5.cpp`
- Modify: `src/LessonManager.cpp` (call the new function)
- Modify: `CMakeLists.txt` (add the new `.cpp` to the source list)
- Modify: `tests/LessonManagerTests.cpp` (extend content-range coverage)

**Interfaces:**
- Produces: `void applySection5LessonContent(std::vector<Lesson>& lessons);`
  — writes into indices 40-49 (topics 41-50).

- [ ] **Step 1: Add the new declaration**

In `src/LessonContent.h`, add this line after the existing
`applySection4LessonContent` declaration (do not remove that one):

```cpp
void applySection5LessonContent(std::vector<Lesson>& lessons);
```

- [ ] **Step 2: Write the lesson content**

Create `src/LessonContentSection5.cpp`:

```cpp
#include "LessonContent.h"

#include "Lesson.h"

void applySection5LessonContent(std::vector<Lesson>& lessons) {
    // Index 40 = topic id 41 (Parametresiz fonksiyon), index 49 = topic
    // id 50 (Recursion) — same positional convention as
    // applyIntroLessonContent/applySection2-4LessonContent.

    lessons[40].explanation =
        "Parametresiz bir fonksiyon, herhangi bir girdi (parametre) "
        "almadan çalışan bir fonksiyondur. Fonksiyon tanımı, dönüş "
        "türü, fonksiyon adı ve boş parantezlerden oluşur. Çağrıldığında "
        "her seferinde aynı işi yapar (parametreye bağlı olarak "
        "davranış değişmez).";
    lessons[40].syntax = "void fonksiyonAdi() {\n    // kod\n}";
    lessons[40].exampleCode =
        "#include <iostream>\n\n"
        "void selamVer() {\n"
        "    std::cout << \"Merhaba!\";\n"
        "}\n\n"
        "int main() {\n"
        "    selamVer();\n"
        "    return 0;\n"
        "}";
    lessons[40].lineExplanations = {
        "void selamVer() { ... } : Parametre almayan, geriye değer "
        "döndürmeyen (void) bir fonksiyon tanımlanır.",
        "selamVer(); : Fonksiyon, adının yanına boş parantez konularak "
        "çağrılır.",
    };
    lessons[40].commonMistakes = {
        "Fonksiyonu çağırırken parantezleri unutmak (selamVer; yerine "
        "selamVer();).",
        "void dönüş türüne sahip bir fonksiyondan değer döndürmeye "
        "çalışmak (return bir değerle kullanılamaz).",
        "Fonksiyonu tanımlamadan veya prototipini vermeden önce "
        "çağırmaya çalışmak.",
    };

    lessons[41].explanation =
        "Bir fonksiyon, parantez içinde bir veya daha fazla parametre "
        "tanımlayarak dışarıdan veri alabilir. Fonksiyon çağrılırken bu "
        "parametrelere karşılık gelen değerler (argümanlar) verilir. "
        "Parametre sayısı ve türleri, fonksiyon tanımıyla çağrı arasında "
        "eşleşmelidir.";
    lessons[41].syntax = "void fonksiyonAdi(int parametre) {\n    // kod\n}";
    lessons[41].exampleCode =
        "#include <iostream>\n\n"
        "void sayiYazdir(int sayi) {\n"
        "    std::cout << \"Sayı: \" << sayi;\n"
        "}\n\n"
        "int main() {\n"
        "    sayiYazdir(5);\n"
        "    return 0;\n"
        "}";
    lessons[41].lineExplanations = {
        "void sayiYazdir(int sayi) { ... } : int türünde bir parametre "
        "alan fonksiyon tanımlanır.",
        "sayiYazdir(5); : Fonksiyon çağrılırken 5 argümanı, sayi "
        "parametresine atanır.",
    };
    lessons[41].commonMistakes = {
        "Fonksiyonu çağırırken parametre sayısını veya türünü yanlış "
        "vermek.",
        "Parametrenin yalnızca fonksiyon içinde geçerli (yerel) bir "
        "değişken olduğunu unutmak.",
        "Birden fazla parametreyi virgülle ayırmayı unutmak.",
    };

    lessons[42].explanation =
        "Bir fonksiyon, void yerine bir tür (int, double, vb.) "
        "belirterek çağırana bir değer döndürebilir. return ifadesi, "
        "hem fonksiyonu sonlandırır hem de belirtilen değeri geri "
        "verir. Dönüş türü ile return ifadesindeki değerin türü uyumlu "
        "olmalıdır.";
    lessons[42].syntax = "int fonksiyonAdi() {\n    return deger;\n}";
    lessons[42].exampleCode =
        "#include <iostream>\n\n"
        "int kareAl(int sayi) {\n"
        "    return sayi * sayi;\n"
        "}\n\n"
        "int main() {\n"
        "    int sonuc = kareAl(4);\n"
        "    std::cout << sonuc;\n"
        "    return 0;\n"
        "}";
    lessons[42].lineExplanations = {
        "int kareAl(int sayi) { ... } : int değer döndüren bir fonksiyon "
        "tanımlanır.",
        "return sayi * sayi; : sayi'nın karesini hesaplayıp çağırana "
        "geri döndürür.",
        "int sonuc = kareAl(4); : Fonksiyonun döndürdüğü değer (16) "
        "sonuc değişkenine atanır.",
    };
    lessons[42].commonMistakes = {
        "Dönüş türü belirtilen bir fonksiyonda return ifadesini unutmak "
        "(bu bazı derleyicilerde uyarı/hataya yol açar).",
        "return ifadesinden sonraki kodun çalışacağını sanmak (return, "
        "fonksiyonu anında sonlandırır).",
        "Fonksiyonun döndürdüğü değeri kullanmayı (bir değişkene "
        "atamayı veya yazdırmayı) unutmak.",
    };

    lessons[43].explanation =
        "Fonksiyon prototipi (ileri bildirim), bir fonksiyonun gövdesi "
        "olmadan yalnızca imzasını (dönüş türü, adı, parametre "
        "türleri) tanımlamaktır. Bu sayede bir fonksiyon, gerçek tanımı "
        "dosyanın daha sonrasında (örneğin main()'den sonra) yer alsa "
        "bile main() içinde veya başka bir yerde önceden çağrılabilir.";
    lessons[43].syntax = "int topla(int a, int b);  // prototip, noktalı virgülle biter";
    lessons[43].exampleCode =
        "#include <iostream>\n\n"
        "int topla(int a, int b);\n\n"
        "int main() {\n"
        "    std::cout << topla(3, 4);\n"
        "    return 0;\n"
        "}\n\n"
        "int topla(int a, int b) {\n"
        "    return a + b;\n"
        "}";
    lessons[43].lineExplanations = {
        "int topla(int a, int b); : Fonksiyonun prototipi; gövdesi yok, "
        "noktalı virgülle biter.",
        "topla(3, 4) : main() içinde, gerçek tanım henüz görünmeden "
        "önce fonksiyon çağrılabilir.",
        "int topla(int a, int b) { ... } : Fonksiyonun gerçek tanımı "
        "(gövdesi) dosyanın devamında yer alır.",
    };
    lessons[43].commonMistakes = {
        "Prototipin sonuna noktalı virgül koymayı unutmak (bu onu bir "
        "tanım gibi göstermeye çalışır ve hataya yol açar).",
        "Prototip ile gerçek tanımın parametre türlerini/sayısını "
        "farklı yazmak.",
        "Prototibi hiç yazmadan bir fonksiyonu, tanımından önce "
        "çağırmaya çalışmak (derleme hatası oluşur).",
    };

    lessons[44].explanation =
        "Bir fonksiyon parametresine varsayılan bir değer atanabilir; "
        "çağrı sırasında o parametre için argüman verilmezse varsayılan "
        "değer kullanılır. Varsayılan değerli parametreler, parametre "
        "listesinin SONUNDA (sağ tarafında) olmalıdır; varsayılanı "
        "olmayan bir parametre, varsayılanı olan bir parametreden sonra "
        "gelemez.";
    lessons[44].syntax = "void selamla(std::string isim = \"Misafir\") {\n    // ...\n}";
    lessons[44].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "void selamla(std::string isim = \"Misafir\") {\n"
        "    std::cout << \"Merhaba, \" << isim;\n"
        "}\n\n"
        "int main() {\n"
        "    selamla();\n"
        "    selamla(\"Ali\");\n"
        "    return 0;\n"
        "}";
    lessons[44].lineExplanations = {
        "void selamla(std::string isim = \"Misafir\") { ... } : isim "
        "parametresinin varsayılan değeri 'Misafir' olarak belirlenir.",
        "selamla(); : Argüman verilmediği için isim, varsayılan değeri "
        "('Misafir') alır.",
        "selamla(\"Ali\"); : Argüman verildiği için isim, 'Ali' olur; "
        "varsayılan değer kullanılmaz.",
    };
    lessons[44].commonMistakes = {
        "Varsayılan değeri olmayan bir parametreyi, varsayılan değeri "
        "olan bir parametreden SONRA yazmak (bu derleme hatasıdır; "
        "varsayılanlar sonda olmalıdır).",
        "Varsayılan parametreli bir fonksiyonu her zaman argümansız "
        "çağırmak gerektiğini sanmak (argüman verilirse varsayılan "
        "değer geçersiz kılınır).",
        "Birden fazla parametreye varsayılan değer verirken sıralamayı "
        "(sağdan sola, en sağdakinden başlayarak) karıştırmak.",
    };

    lessons[45].explanation =
        "Fonksiyon aşırı yükleme (overloading), aynı isimde ama farklı "
        "parametre listelerine (farklı tür ve/veya sayıda parametre) "
        "sahip birden fazla fonksiyon tanımlamaya olanak tanır. "
        "Derleyici, çağrı sırasında verilen argümanlara bakarak hangi "
        "fonksiyonun çağrılacağına karar verir. YALNIZCA dönüş türü "
        "farklı olan, ama parametre listesi aynı olan iki fonksiyon "
        "aşırı yükleme SAYILMAZ; bu bir derleme hatasıdır.";
    lessons[45].syntax = "int topla(int a, int b);\ndouble topla(double a, double b);";
    lessons[45].exampleCode =
        "#include <iostream>\n\n"
        "int topla(int a, int b) {\n"
        "    return a + b;\n"
        "}\n\n"
        "double topla(double a, double b) {\n"
        "    return a + b;\n"
        "}\n\n"
        "int main() {\n"
        "    std::cout << topla(2, 3) << \" \" << topla(2.5, 3.5);\n"
        "    return 0;\n"
        "}";
    lessons[45].lineExplanations = {
        "int topla(int a, int b) { ... } : int parametreli bir topla "
        "fonksiyonu.",
        "double topla(double a, double b) { ... } : Aynı isimde ama "
        "double parametreli farklı bir topla fonksiyonu; bu geçerli "
        "bir aşırı yüklemedir.",
        "topla(2, 3) int sürümünü, topla(2.5, 3.5) double sürümünü "
        "çağırır; derleyici argüman türlerine göre doğru fonksiyonu "
        "seçer.",
    };
    lessons[45].commonMistakes = {
        "Yalnızca dönüş türünü değiştirip parametre listesini aynı "
        "bırakarak aşırı yükleme yapmaya çalışmak (bu derleme "
        "hatasıdır; parametre listesi de farklı olmalıdır).",
        "Aşırı yüklenmiş fonksiyonları çağırırken hangi sürümün "
        "seçileceğini belirsiz argümanlarla (örneğin örtük dönüşüme "
        "açık türlerle) karıştırmak.",
        "Aşırı yükleme ile varsayılan parametreleri karıştırıp aynı "
        "fonksiyonu iki farklı şekilde tanımlamaya çalışmak.",
    };

    lessons[46].explanation =
        "Değer ile parametre gönderme (pass by value), bir argümanın "
        "fonksiyona bir KOPYA olarak gönderilmesidir. Fonksiyon içinde "
        "parametre üzerinde yapılan değişiklikler, çağıran taraftaki "
        "orijinal değişkeni etkilemez; çünkü fonksiyon kendi bağımsız "
        "kopyası üzerinde çalışır.";
    lessons[46].syntax = "void fonksiyon(int sayi) {\n    sayi = sayi + 1;  // yalnızca kopyayı değiştirir\n}";
    lessons[46].exampleCode =
        "#include <iostream>\n\n"
        "void birArtir(int sayi) {\n"
        "    sayi = sayi + 1;\n"
        "}\n\n"
        "int main() {\n"
        "    int x = 5;\n"
        "    birArtir(x);\n"
        "    std::cout << x;\n"
        "    return 0;\n"
        "}";
    lessons[46].lineExplanations = {
        "void birArtir(int sayi) { sayi = sayi + 1; } : Parametre sayi, "
        "x'in bir kopyasıdır; sayi = sayi + 1 yalnızca bu kopyayı "
        "değiştirir.",
        "birArtir(x); : x'in değeri kopyalanarak fonksiyona gönderilir.",
        "std::cout << x; : x hala 5'tir; fonksiyon içindeki değişiklik "
        "orijinali etkilemedi.",
    };
    lessons[46].commonMistakes = {
        "Değer ile gönderilen bir parametreyi değiştirmenin, çağırandaki "
        "orijinal değişkeni de değiştireceğini sanmak.",
        "Büyük nesneleri (örneğin uzun bir string veya vector) her "
        "zaman değer ile göndermenin performans maliyetini göz ardı "
        "etmek (her çağrıda kopyalama yapılır).",
        "Parametrenin fonksiyon dışında da (fonksiyon bittikten sonra) "
        "var olacağını sanmak (yerel bir değişken gibi fonksiyon "
        "bitince yok olur).",
    };

    lessons[47].explanation =
        "Referans ile parametre gönderme (pass by reference), parametre "
        "türünün yanına & işareti eklenerek yapılır. Bu durumda "
        "parametre, çağırandaki orijinal değişkenin kendisine (bir "
        "takma ada) bağlanır; fonksiyon içindeki değişiklikler doğrudan "
        "orijinal değişkeni etkiler. Kopyalama yapılmadığı için büyük "
        "nesnelerde daha verimlidir.";
    lessons[47].syntax = "void fonksiyon(int& sayi) {\n    sayi = sayi + 1;  // orijinali değiştirir\n}";
    lessons[47].exampleCode =
        "#include <iostream>\n\n"
        "void birArtir(int& sayi) {\n"
        "    sayi = sayi + 1;\n"
        "}\n\n"
        "int main() {\n"
        "    int x = 5;\n"
        "    birArtir(x);\n"
        "    std::cout << x;\n"
        "    return 0;\n"
        "}";
    lessons[47].lineExplanations = {
        "void birArtir(int& sayi) { sayi = sayi + 1; } : & işareti, "
        "sayi'nin x'in kendisine bağlı bir referans olmasını sağlar.",
        "birArtir(x); : x, referans olarak fonksiyona gönderilir; "
        "kopyalanmaz.",
        "std::cout << x; : x artık 6'dır; fonksiyon içindeki değişiklik "
        "orijinali doğrudan etkiledi.",
    };
    lessons[47].commonMistakes = {
        "Referans parametrenin de bir kopya olduğunu sanmak (aslında "
        "orijinal değişkenin kendisidir).",
        "Fonksiyona bir referans parametre için bir değişken yerine "
        "sabit bir değer (literal) göndermeye çalışmak (int& "
        "parametresine 5 gibi bir literal geçilemez; bu bir hataya yol "
        "açar).",
        "Her parametreyi gereksiz yere referans yapmak (yalnızca "
        "değişmesi istenen veya büyük nesneler için anlamlıdır).",
    };

    lessons[48].explanation =
        "const referans (const T&), bir parametreyi referans olarak "
        "(kopyalamadan) alırken, fonksiyonun o parametreyi "
        "değiştirmesini derleme zamanında engeller. Büyük nesneleri "
        "(string, vector gibi) hem verimli (kopyasız) hem de güvenli "
        "(değiştirilemez) şekilde fonksiyona göndermenin standart "
        "yoludur.";
    lessons[48].syntax = "void yazdir(const std::string& metin) {\n    std::cout << metin;\n}";
    lessons[48].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "void yazdir(const std::string& metin) {\n"
        "    std::cout << metin;\n"
        "}\n\n"
        "int main() {\n"
        "    std::string s = \"Merhaba\";\n"
        "    yazdir(s);\n"
        "    return 0;\n"
        "}";
    lessons[48].lineExplanations = {
        "void yazdir(const std::string& metin) { ... } : metin, s'ye "
        "bağlı bir referanstır ama const olduğu için değiştirilemez.",
        "yazdir(s); : s kopyalanmadan, referans olarak gönderilir; "
        "büyük bir string için bu verimlidir.",
    };
    lessons[48].commonMistakes = {
        "const referans parametresini fonksiyon içinde değiştirmeye "
        "çalışmak (bu bir derleme hatasıdır).",
        "const referansın, değer ile göndermeden daha yavaş olduğunu "
        "sanmak (aslında büyük nesnelerde kopyalamadan kaçındığı için "
        "genellikle daha hızlıdır).",
        "const referansı, değeri değiştirilebilir bir referans (T&) ile "
        "karıştırmak.",
    };

    lessons[49].explanation =
        "Recursion (özyineleme), bir fonksiyonun kendi kendini "
        "çağırmasıdır. Her recursive fonksiyonun, özyinelemeyi durduran "
        "bir taban durumu (base case) olmalıdır; taban durumu olmazsa "
        "veya hiç ulaşılamazsa, fonksiyon sonsuza kadar kendini çağırır "
        "ve çağrı yığını (call stack) taşar (stack overflow). Her "
        "çağrı, kendi bağımsız parametre ve yerel değişken kopyasına "
        "sahiptir.";
    lessons[49].syntax = "int faktoriyel(int n) {\n    if (n <= 1) return 1;  // taban durumu\n    return n * faktoriyel(n - 1);  // özyinelemeli çağrı\n}";
    lessons[49].exampleCode =
        "#include <iostream>\n\n"
        "int faktoriyel(int n) {\n"
        "    if (n <= 1) {\n"
        "        return 1;\n"
        "    }\n"
        "    return n * faktoriyel(n - 1);\n"
        "}\n\n"
        "int main() {\n"
        "    std::cout << faktoriyel(4);\n"
        "    return 0;\n"
        "}";
    lessons[49].lineExplanations = {
        "if (n <= 1) { return 1; } : Taban durumu; n 1 veya daha küçük "
        "olduğunda özyineleme durur.",
        "return n * faktoriyel(n - 1); : Fonksiyon kendi kendini, bir "
        "küçük değerle (n-1) çağırır.",
        "faktoriyel(4) : 4 * faktoriyel(3) = 4 * (3 * faktoriyel(2)) = "
        "... sonunda 4*3*2*1 = 24 sonucunu verir.",
    };
    lessons[49].commonMistakes = {
        "Taban durumunu (base case) unutmak veya hiçbir zaman "
        "ulaşılamayacak şekilde yazmak; bu sonsuz özyinelemeye ve "
        "çağrı yığını taşmasına (stack overflow) yol açar.",
        "Recursive çağrının, önceki çağrıların yerel değişkenlerini "
        "paylaştığını sanmak (aslında her çağrının kendi bağımsız "
        "kopyası vardır).",
        "Basit bir problemi (örneğin toplam veya faktöriyel) her zaman "
        "recursion ile çözmek gerektiğini sanmak; birçok durumda bir "
        "döngü de aynı işi yapar ve genellikle daha az bellek kullanır.",
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
    applySection4LessonContent(lessons_);
}
```

to:

```cpp
    applyIntroLessonContent(lessons_);
    applySection2LessonContent(lessons_);
    applySection3LessonContent(lessons_);
    applySection4LessonContent(lessons_);
    applySection5LessonContent(lessons_);
}
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/LessonContent.h
    src/LessonContentSection2.cpp
    src/LessonContentSection3.cpp
    src/LessonContentSection4.cpp
```

to:

```cmake
    src/LessonContent.h
    src/LessonContentSection2.cpp
    src/LessonContentSection3.cpp
    src/LessonContentSection4.cpp
    src/LessonContentSection5.cpp
```

- [ ] **Step 5: Extend the content-coverage tests**

In `tests/LessonManagerTests.cpp`, replace:

```cpp
TEST_CASE(LessonManager_TopicsElevenToFortyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 40; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsElevenToFiftyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 50; ++topicId) {
```

(keep the rest of that test's body unchanged). Then replace:

```cpp
TEST_CASE(LessonManager_TopicsFortyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 41; topicId <= 100; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsFiftyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 51; topicId <= 100; ++topicId) {
```

(keep the rest of that test's body unchanged — there must be exactly
these two content-coverage tests afterward, not three).

- [ ] **Step 6: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `91/91 test(s) passed.` (same count as Phase 15's end state —
this task only renames/widens two existing tests' ranges).

- [ ] **Step 7: Commit**

```bash
git add src/LessonContent.h src/LessonContentSection5.cpp src/LessonManager.cpp CMakeLists.txt tests/LessonManagerTests.cpp
git commit -m "feat(content): add Section 5 lesson content (topics 41-50)"
```

---

### Task 2: Questions for topics 41-44 (ids 943-1058)

**Files:**
- Modify: `src/QuestionContent.h` (add one new declaration)
- Create: `src/QuestionsSection5.cpp`
- Modify: `src/QuestionManager.cpp` (include, call, bump `reserve()`)
- Modify: `CMakeLists.txt` (add the new `.cpp`)

**Interfaces:**
- Produces: `void appendSection5Questions(std::vector<Question>& questions);`
  — Task 3 and Task 4 append more `questions.push_back(...)` calls to
  this SAME function body (in this same file) for topics 45-47 and
  48-50 respectively. This task only adds topics 41-44 (ids 943-1058).

- [ ] **Step 1: Add the new declaration**

In `src/QuestionContent.h`, add this line after the existing
`appendSection4Questions` declaration (do not remove that one):

```cpp
void appendSection5Questions(std::vector<Question>& questions);
```

- [ ] **Step 2: Write topics 41-44's questions**

Create `src/QuestionsSection5.cpp`:

```cpp
#include "QuestionContent.h"

#include "Question.h"

void appendSection5Questions(std::vector<Question>& questions) {
    // Topic 41: Parametresiz fonksiyon
    questions.push_back(Question{
        .id = 943, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Parametresiz bir fonksiyon çağrılırken parantez içine ne yazılır?",
        .options = {"Bir sayı", "Bir metin", "Hiçbir şey (boş bırakılır)", "Fonksiyonun adı tekrar"},
        .acceptedAnswers = {"c"},
        .explanation = "Parametresiz bir fonksiyon çağrılırken parantezler boş bırakılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 944, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void selamVer() { std::cout << \"Merhaba\"; } fonksiyonu nasıl çağrılır?",
        .options = {"selamVer;", "selamVer();", "call selamVer();", "selamVer[];"},
        .acceptedAnswers = {"b"},
        .explanation = "Fonksiyonlar adının yanına parantez konularak çağrılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 945, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Parametresiz bir fonksiyon her çağrıldığında davranışı değişir mi?",
        .options = {"Evet, her zaman farklı davranır", "Hayır, her çağrıda aynı işi yapar (parametreye bağlı değişkenlik yoktur)", "Yalnızca ilk çağrıda farklı davranır", "Rastgele değişir"},
        .acceptedAnswers = {"b"},
        .explanation = "Parametresiz bir fonksiyon her çağrıldığında aynı işi yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 946, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void mesaj() { std::cout << \"Selam\"; } int main() { mesaj(); mesaj(); return 0; } kodu ne yazdırır?",
        .options = {"Selam", "SelamSelam", "Selam Selam", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "mesaj() iki kez çağrıldığı için 'Selam' iki kez art arda yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 947, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f() { std::cout << \"A\"; } fonksiyonunun dönüş türü nedir?",
        .options = {"int", "void (değer döndürmez)", "string", "Belirtilmemiş"},
        .acceptedAnswers = {"b"},
        .explanation = "void dönüş türü, fonksiyonun hiçbir değer döndürmediğini belirtir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 948, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Parametresiz bir fonksiyon, fonksiyon gövdesi içinde başka değişkenler tanımlayabilir mi?",
        .options = {"Hayır, hiçbir değişken tanımlanamaz", "Evet, fonksiyon içinde yerel değişkenler tanımlanabilir", "Yalnızca parametre varsa değişken tanımlanabilir", "Yalnızca global değişkenler kullanılabilir"},
        .acceptedAnswers = {"b"},
        .explanation = "Parametre olmasa bile fonksiyon içinde yerel değişkenler tanımlanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 949, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void yazdir() { return 5; } kodu geçerli midir?",
        .options = {"Evet, 5 döndürülür", "Hayır, void bir fonksiyon değer döndüremez; derleme hatası oluşur", "Evet, ama 5 yok sayılır", "Yalnızca int'e dönüştürülebilirse geçerlidir"},
        .acceptedAnswers = {"b"},
        .explanation = "void bir fonksiyon return ile bir değer döndüremez; bu bir derleme hatasıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 950, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int main() { yazdir(); return 0; } void yazdir() { std::cout << \"Test\"; } kodu neden derlenmez (yazdir main'den SONRA tanımlanmış, önceden prototip de verilmemiş)?",
        .options = {"main() her zaman ilk fonksiyon olmalıdır", "Derleyici, yazdir() çağrısına ulaştığında onun ne olduğunu (tanımını/prototipini) henüz bilmiyor", "void fonksiyonlar main() içinde çağrılamaz", "Fonksiyon isimleri en fazla 5 harf olabilir"},
        .acceptedAnswers = {"b"},
        .explanation = "Derleyici dosyayı yukarıdan aşağıya işler; bir fonksiyonun tanımı veya prototipi olmadan çağrılması derleme hatasına yol açar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 951, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Parametresiz bir fonksiyon hiçbir girdi almadan çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Parametresiz fonksiyonların tanımı budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 952, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Parametresiz bir fonksiyon çağrılırken parantezler atlanabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Parantezler her zaman yazılmalıdır, boş olsalar bile.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 953, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void selamVer() { ... } fonksiyonu bir değer döndürebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "void fonksiyonlar değer döndüremez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 954, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Parametresiz bir fonksiyon, içinde yerel değişkenler kullanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Fonksiyonun parametresi olmaması, yerel değişken tanımlamasını engellemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 955, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyon, tanımından önce (ve prototipi olmadan) çağrılırsa derleme hatası oluşur.",
        .acceptedAnswers = {"1"},
        .explanation = "Derleyici, önceden tanımlanmamış veya bildirilmemiş bir fonksiyonu tanıyamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 956, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Parametresiz bir fonksiyon birden fazla kez çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Herhangi bir fonksiyon istenildiği kadar çağrılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 957, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void selamVer_____ {\n    std::cout << \"Merhaba\";\n}\nParametresiz bir fonksiyon tanımlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"()"},
        .explanation = "Boş parantez (), fonksiyonun parametre almadığını gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 958, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void selamVer() {\n    std::cout << \"Merhaba\";\n}\nint main() {\n    selamVer_____;\n    return 0;\n}\nFonksiyonu çağırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"()"},
        .explanation = "Fonksiyon çağrısı boş parantezle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 959, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ selamVer() {\n    std::cout << \"Merhaba\";\n}\nDeğer döndürmeyen bir fonksiyon tanımlamak için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"void"},
        .explanation = "void anahtar kelimesi, fonksiyonun değer döndürmediğini belirtir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 960, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir() {\n    std::cout << \"Bir\";\n}\nint main() {\n    yazdir();\n    yazdir_____;\n    return 0;\n}\nFonksiyonu ikinci kez çağırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"()"},
        .explanation = "Aynı fonksiyon tekrar çağrılırken de boş parantez kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 961, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f() {\n    int x _____ 10;\n    std::cout << x;\n}\nFonksiyon içinde yerel bir değişken tanımlayıp 10 değerini atamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"="},
        .explanation = "Atama operatörü = kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 962, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void bosFonksiyon()_____\nBoş bir fonksiyon gövdesi (hiçbir kod içermeyen) tanımlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"{}"},
        .explanation = "Boş süslü parantezler {}, hiçbir kod içermeyen bir gövde tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 963, .topicId = 41,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\n    std::cout << \"Merhaba, Dünya!\";\n}\nselamVer adında, parametre almayan bir fonksiyon başlatan satırı yazın.",
        .acceptedAnswers = {"void selamVer() {"},
        .explanation = "void selamVer() {, parametresiz bir fonksiyon tanımının başlangıcıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 964, .topicId = 41,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void selamVer() {\n    std::cout << \"Merhaba\";\n}\nint main() {\n    _____\n    return 0;\n}\nselamVer fonksiyonunu çağıran satırı yazın.",
        .acceptedAnswers = {"selamVer();"},
        .explanation = "Fonksiyon adının yanına boş parantez konularak çağrılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 965, .topicId = 41,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void mesajYaz() {\n    std::cout << \"Merhaba\";\n}\nint main() {\n    mesajYaz();\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Merhaba"},
        .explanation = "mesajYaz() çağrıldığında 'Merhaba' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 966, .topicId = 41,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void yaz() {\n    std::cout << \"X\";\n}\nint main() {\n    yaz();\n    yaz();\n    yaz();\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"XXX"},
        .explanation = "yaz() üç kez çağrıldığı için 'X' üç kez art arda yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 967, .topicId = 41,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid selamVer() {\n    std::cout << \"Merhaba\";\n}\nint main() {\n    selamVer;\n    return 0;\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"selamVer();"},
        .explanation = "Fonksiyon çağrısında parantezler eksik.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 968, .topicId = 41,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid yazdir() {\n    return \"Merhaba\";\n}\n\nBu kod derlenmez çünkü void bir fonksiyon değer döndüremez. Programcı yalnızca ekrana yazdırmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << \"Merhaba\";"},
        .explanation = "void fonksiyon değer döndüremeyeceği için doğrudan ekrana yazdırma kullanılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 969, .topicId = 41,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid selamVer( {\n    std::cout << \"Merhaba\";\n}\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"void selamVer() {"},
        .explanation = "Parametre listesinin kapanış parantezi eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 970, .topicId = 41,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir fonksiyon tanımlayıp çağıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"selamVer();", "void selamVer() {\n    std::cout << \"Merhaba\";\n}"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce fonksiyon tanımlanır (2), sonra çağrılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 971, .topicId = 41,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Parametre almayan ve ekrana 'Merhaba, C++!' yazan bir fonksiyon tanımlayıp, main() içinden çağıran bir program yazın.",
        .acceptedAnswers = {"void", "cout", "<<"},
        .explanation = "Program parametresiz bir fonksiyon tanımlamalı ve onu main() içinden çağırmalıdır.",
        .baseXp = 40,
    });

    // Topic 42: Parametre alan fonksiyon
    questions.push_back(Question{
        .id = 972, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyona dışarıdan veri göndermek için ne kullanılır?",
        .options = {"Global değişken", "Parametre", "Yorum satırı", "Makro"},
        .acceptedAnswers = {"b"},
        .explanation = "Parametreler, bir fonksiyona dışarıdan veri göndermenin standart yoludur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 973, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void sayiYazdir(int sayi) fonksiyonu kaç parametre alır?",
        .options = {"0", "1", "2", "Belirsiz"},
        .acceptedAnswers = {"b"},
        .explanation = "Fonksiyon yalnızca bir parametre (sayi) alır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 974, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void sayiYazdir(int sayi) { std::cout << sayi; } sayiYazdir(7); çağrısı ne yazdırır?",
        .options = {"0", "7", "sayi", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "sayi parametresi 7 değerini alır ve yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 975, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void topla(int a, int b) fonksiyonu kaç parametre alır?",
        .options = {"1", "2", "3", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "Fonksiyon iki parametre (a ve b) alır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 976, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void carp(int a, int b) { std::cout << a * b; } carp(3, 4); çağrısı ne yazdırır?",
        .options = {"7", "12", "34", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "3 * 4 = 12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 977, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyon çağrılırken verilen değerlere ne denir?",
        .options = {"Parametre", "Argüman", "Değişken", "Sabit"},
        .acceptedAnswers = {"b"},
        .explanation = "Çağrı sırasında verilen değerlere argüman denir; parametre ise fonksiyon tanımındaki isimdir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 978, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int a, int b) { ... } f(1); şeklinde çağrılırsa ne olur (yalnızca 1 argüman verildi ama fonksiyon 2 parametre bekliyor, varsayılan değer de yok)?",
        .options = {"b otomatik olarak 0 olur", "Derleme hatası oluşur (yetersiz argüman)", "b, a ile aynı değeri alır", "Program çalışır ama b tanımsız kalır"},
        .acceptedAnswers = {"b"},
        .explanation = "Varsayılan değeri olmayan bir parametre için argüman verilmezse derleme hatası oluşur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 979, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int a, int b, int c) { std::cout << a + b + c; } f(1, 2, 3); çağrısının çıktısı nedir?",
        .options = {"123", "6", "Hata", "1 2 3"},
        .acceptedAnswers = {"b"},
        .explanation = "1 + 2 + 3 = 6.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 980, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyon, parametreler aracılığıyla dışarıdan veri alabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Parametrelerin amacı budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 981, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Parametre sayısı, fonksiyon çağrısında verilen argüman sayısıyla eşleşmek zorunda değildir.",
        .acceptedAnswers = {"2"},
        .explanation = "Varsayılan değerler yoksa parametre sayısı ile argüman sayısı eşleşmelidir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 982, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Parametreler, yalnızca fonksiyon içinde geçerli olan yerel değişkenler gibi davranır.",
        .acceptedAnswers = {"1"},
        .explanation = "Parametreler fonksiyonun kapsamı içinde yerel değişken gibi davranır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 983, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b) fonksiyonu tek bir argümanla çağrılabilir (varsayılan değer olmadan).",
        .acceptedAnswers = {"2"},
        .explanation = "Varsayılan değer yoksa her parametre için bir argüman verilmelidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 984, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyonun birden fazla parametresi virgülle ayrılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Parametreler virgülle ayrılarak listelenir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 985, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Parametre türü ile çağrıda verilen argümanın türü hiçbir zaman uyuşmak zorunda değildir.",
        .acceptedAnswers = {"2"},
        .explanation = "Argüman türü parametre türüyle uyumlu olmalıdır (ya da örtük dönüşüme uygun olmalıdır).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 986, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void sayiYazdir(int _____) {\n    std::cout << sayi;\n}\nBir parametre tanımlamak için boşluğa ne yazılmalı? (örnek: sayi)",
        .acceptedAnswers = {"sayi"},
        .explanation = "Parametre adı, gövdede kullanılan isimle eşleşmelidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 987, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void sayiYazdir(int sayi) {\n    std::cout << sayi;\n}\nint main() {\n    sayiYazdir_____;\n    return 0;\n}\nFonksiyonu 5 argümanıyla çağırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"(5)"},
        .explanation = "Argüman parantez içinde verilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 988, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void topla(int a_____ int b) {\n    std::cout << a + b;\n}\nİki parametreyi ayırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {","},
        .explanation = "Parametreler virgülle ayrılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 989, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void carp(int a, int b) {\n    std::cout << a _____ b;\n}\nİki parametreyi çarpmak için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "Çarpma operatörü * kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 990, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b, int c) { ... } f(1, 2, _____); çağrısının 3 argüman içermesi için boşluğa (herhangi bir tam sayı) ne yazılabilir? (örnek: 3)",
        .acceptedAnswers = {"3"},
        .explanation = "Üçüncü parametreye karşılık gelen argüman verilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 991, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir(std::string _____) {\n    std::cout << metin;\n}\nstd::string türünde bir parametre tanımlamak için boşluğa ne yazılmalı? (örnek: metin)",
        .acceptedAnswers = {"metin"},
        .explanation = "Parametre adı, gövdede kullanılan isimle eşleşmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 992, .topicId = 42,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\n    std::cout << sayi;\n}\nsayi adında int parametre alan yazdir fonksiyonunu başlatan satırı yazın.",
        .acceptedAnswers = {"void yazdir(int sayi) {"},
        .explanation = "Fonksiyon tanımı, dönüş türü, ad ve parametre listesinden oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 993, .topicId = 42,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void carp(int a, int b) {\n    std::cout << a * b;\n}\nint main() {\n    _____\n    return 0;\n}\ncarp fonksiyonunu 3 ve 4 argümanlarıyla çağıran satırı yazın.",
        .acceptedAnswers = {"carp(3, 4);"},
        .explanation = "Argümanlar parantez içinde virgülle ayrılarak verilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 994, .topicId = 42,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir(int sayi) {\n    std::cout << sayi;\n}\nint main() {\n    yazdir(42);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"42"},
        .explanation = "sayi parametresi 42 değerini alır ve yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 995, .topicId = 42,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void topla(int a, int b) {\n    std::cout << a + b;\n}\nint main() {\n    topla(10, 20);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30"},
        .explanation = "10 + 20 = 30.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 996, .topicId = 42,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid yazdir(int sayi) {\n    std::cout << sayi;\n}\nint main() {\n    yazdir();\n    return 0;\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"yazdir(5);"},
        .explanation = "Fonksiyon bir parametre beklediği için çağrıda bir argüman verilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 997, .topicId = 42,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid topla(int a, int b) {\n    std::cout << a + b;\n}\nint main() {\n    topla(5);\n    return 0;\n}\n\nBu kod derlenmez çünkü topla iki parametre bekliyor ama yalnızca bir argüman verilmiş. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"topla(5, 3);"},
        .explanation = "İki parametreli fonksiyon için iki argüman verilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 998, .topicId = 42,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid yazdir(int sayi) {\n    std::cout << sayi;\n}\nint main() {\n    yazdir(5;\n    return 0;\n}\n\nDüzeltilmiş üçüncü satırı yazın.",
        .acceptedAnswers = {"yazdir(5);"},
        .explanation = "Fonksiyon çağrısında kapanış parantezi eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 999, .topicId = 42,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, iki sayıyı çarpan bir fonksiyon tanımlayıp çağıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"topla(3, 4);", "void topla(int a, int b) {\n    std::cout << a + b;\n}"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce fonksiyon tanımlanır (2), sonra çağrılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1000, .topicId = 42,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "İki tam sayı parametre alan ve bunların çarpımını ekrana yazdıran bir fonksiyon tanımlayıp, main() içinden çağıran bir program yazın.",
        .acceptedAnswers = {"void", "cout", "<<", "*"},
        .explanation = "Program iki parametreli bir fonksiyon tanımlamalı ve çarpımı yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 43: Değer döndüren fonksiyon
    questions.push_back(Question{
        .id = 1001, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyonun değer döndürmesi için hangi anahtar kelime kullanılır?",
        .options = {"void", "return", "break", "exit"},
        .acceptedAnswers = {"b"},
        .explanation = "return ifadesi bir fonksiyondan değer döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1002, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int kareAl(int sayi) { return sayi * sayi; } kareAl(3) çağrısı ne döner?",
        .options = {"3", "6", "9", "Hata"},
        .acceptedAnswers = {"c"},
        .explanation = "3 * 3 = 9.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1003, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir fonksiyonun dönüş türü int ise, return ifadesinde hangi türde bir değer olmalıdır?",
        .options = {"Yalnızca string", "int (veya int'e dönüştürülebilir bir tür)", "void", "Herhangi bir tür olabilir, fark etmez"},
        .acceptedAnswers = {"b"},
        .explanation = "Dönüş türü ile return ifadesindeki değerin türü uyumlu olmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1004, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int f() { return 5; std::cout << \"Merhaba\"; } fonksiyonu çağrıldığında 'Merhaba' yazdırılır mı?",
        .options = {"Evet, her zaman yazdırılır", "Hayır, return ifadesinden sonraki kod hiç çalışmaz", "Yalnızca sayi 0 ise yazdırılır", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "return, fonksiyonu anında sonlandırır; sonrasındaki kod hiç çalışmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1005, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b) { return a * b; } int sonuc = carp(4, 5); sonuc kaç olur?",
        .options = {"9", "20", "45", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "4 * 5 = 20.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1006, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Dönüş türü int olan bir fonksiyonda return ifadesi hiç yazılmazsa ne olur?",
        .options = {"0 döner otomatik olarak", "Tanımsız davranış / derleyici uyarısı (bazı durumlarda hata)", "void olarak davranır", "Sonsuz döngüye girer"},
        .acceptedAnswers = {"b"},
        .explanation = "int dönüş türlü bir fonksiyonda return eksikse, derleyici uyarır ve davranış tanımsızdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1007, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "double bol(int a, int b) { return a / b; } bol(7, 2) çağrısı ne döner (dikkat: a ve b int)?",
        .options = {"3.5", "3", "4", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "a / b önce int bölmesi olarak hesaplanır (3 olur), sonra double'a dönüştürülür; sonuç 3.5 değil 3'tür (cout 3.0'ı '3' olarak gösterir).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1008, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a) { if (a > 0) return 1; return -1; } f(-5) çağrısı ne döner?",
        .options = {"1", "-1", "0", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "a=-5, a > 0 false olduğu için ilk return atlanır; son satırdaki return -1 çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1009, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "return ifadesi bir fonksiyondan değer döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "return'ün işlevi budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1010, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "void bir fonksiyon return ile bir değer döndürebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "void fonksiyonlar değer döndüremez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1011, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "return ifadesinden sonraki kod, fonksiyon içinde çalışmaya devam eder.",
        .acceptedAnswers = {"2"},
        .explanation = "return, fonksiyonu anında sonlandırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1012, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int kareAl(int x) { return x * x; } kareAl(5) çağrısı 25 döner.",
        .acceptedAnswers = {"1"},
        .explanation = "5 * 5 = 25.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1013, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyonun döndürdüğü değer bir değişkene atanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "int sonuc = f(); gibi bir atama geçerlidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1014, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Dönüş türü int olan bir fonksiyon, her zaman bir tam sayı literal'i (örneğin sadece 5) döndürmelidir; bir ifade (örneğin a+b) döndüremez.",
        .acceptedAnswers = {"2"},
        .explanation = "return, herhangi bir int türünde ifade döndürebilir, yalnızca literal değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1015, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int kareAl(int x) {\n    _____ x * x;\n}\nBir değer döndürmek için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"return"},
        .explanation = "return anahtar kelimesi değeri döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1016, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ kareAl(int x) {\n    return x * x;\n}\nBir int değer döndüren fonksiyonun dönüş türünü belirtmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"int"},
        .explanation = "Dönüş türü fonksiyon adından önce belirtilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1017, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int carp(int a, int b) {\n    return a _____ b;\n}\nİki sayıyı çarpıp döndürmek için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "Çarpma operatörü * kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1018, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int f(int x) {\n    return x _____ 2;\n}\nint sonuc = f(10); ifadesinin sonuc'u 20 yapması için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "10 * 2 = 20.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1019, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int topla(int a, int b) {\n    return a + b;\n}\nint sonuc = _____;\ntopla fonksiyonunu 3 ve 4 argümanlarıyla çağırıp sonucu sonuc'a atayan ifadeyi yazın.",
        .acceptedAnswers = {"topla(3, 4)"},
        .explanation = "Fonksiyon çağrısının döndürdüğü değer bir değişkene atanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1020, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "bool tekMi(int sayi) {\n    return sayi % 2 _____ 1;\n}\nsayi'nın tek olup olmadığını kontrol eden ifadeyi tamamlamak için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1021, .topicId = 43,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int kareAl(int x) {\n    _____\n}\nx'in karesini döndüren satırı yazın.",
        .acceptedAnswers = {"return x * x;"},
        .explanation = "return x * x; ifadesi x'in karesini döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1022, .topicId = 43,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b) {\n    return a * b;\n}\nint main() {\n    int sonuc = _____;\n    std::cout << sonuc;\n}\ncarp fonksiyonunu 6 ve 7 argümanlarıyla çağırıp sonucu alan ifadeyi yazın.",
        .acceptedAnswers = {"carp(6, 7)"},
        .explanation = "Fonksiyon çağrısının sonucu bir değişkene atanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1023, .topicId = 43,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int kareAl(int x) {\n    return x * x;\n}\nint main() {\n    std::cout << kareAl(5);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"25"},
        .explanation = "5 * 5 = 25.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1024, .topicId = 43,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a, int b) {\n    return a - b;\n}\nint main() {\n    std::cout << f(10, 3) << f(3, 10);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"7-7"},
        .explanation = "f(10,3) = 10-3 = 7, f(3,10) = 3-10 = -7; birlikte '7-7' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1025, .topicId = 43,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint kareAl(int x) {\n    x * x;\n}\n\nProgramcı x'in karesini döndürmek istiyor ama return ifadesini yazmayı unutmuş. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"return x * x;"},
        .explanation = "Değeri döndürmek için return kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1026, .topicId = 43,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid kareAl(int x) {\n    return x * x;\n}\n\nBu kod derlenmez çünkü void bir fonksiyon değer döndüremez. Programcı x'in karesini döndürmek istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int kareAl(int x) {"},
        .explanation = "Değer döndüren fonksiyonun dönüş türü void değil, uygun bir tür (int) olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1027, .topicId = 43,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint topla(int a, int b) {\n    retrun a + b;\n}\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"return a + b;"},
        .explanation = "'retrun' yazım hatasıdır; doğrusu 'return'dür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1028, .topicId = 43,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir sayının karesini hesaplayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << sonuc;", "int sonuc = kareAl(5);", "int kareAl(int x) {\n    return x * x;\n}"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce fonksiyon tanımlanır (3), sonra çağrılıp sonuç alınır (2), en son yazdırılır (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1029, .topicId = 43,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "İki tam sayı parametre alan ve toplamlarını döndüren bir fonksiyon yazıp, döndürülen değeri main() içinde ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"return", "cout", "<<", "+"},
        .explanation = "Program iki sayıyı toplayıp döndüren bir fonksiyon tanımlamalı ve sonucu yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 44: Fonksiyon prototipi
    questions.push_back(Question{
        .id = 1030, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Fonksiyon prototipi neyi içerir?",
        .options = {"Fonksiyonun tam gövdesini", "Yalnızca fonksiyonun imzasını (dönüş türü, adı, parametreleri)", "Yalnızca fonksiyonun adını", "Fonksiyonun çağrıldığı yeri"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip yalnızca fonksiyonun imzasını içerir, gövdesini içermez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1031, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir fonksiyon prototipi hangi karakterle biter?",
        .options = {"{ (süslü parantez)", "; (noktalı virgül)", ": (iki nokta)", ", (virgül)"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip, gövdesi olmadığı için noktalı virgülle biter.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1032, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int topla(int a, int b); ifadesi bir fonksiyon prototipi midir?",
        .options = {"Evet", "Hayır, bu bir fonksiyon tanımıdır", "Hayır, bu bir değişken tanımıdır", "Hayır, bu bir fonksiyon çağrısıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "Gövdesi olmadan noktalı virgülle biten bu ifade bir prototiptir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1033, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Fonksiyon prototipi neden kullanılır?",
        .options = {"Fonksiyonu hızlandırmak için", "Bir fonksiyonun, gerçek tanımından önce (örneğin main() içinde) çağrılabilmesini sağlamak için", "Bellek tasarrufu sağlamak için", "Yalnızca stil tercihi, işlevsel bir amacı yoktur"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip, derleyiciye fonksiyonun imzasını önceden bildirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1034, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int f(int x); int main() { f(5); return 0; } int f(int x) { return x; } yapısında f'nin prototipi olmasaydı ne olurdu?",
        .options = {"Hiçbir fark olmazdı", "Derleme hatası oluşurdu (main, f'yi henüz tanımadığı için)", "f otomatik olarak void olurdu", "main() çalışmazdı ama derlenirdi"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip olmadan, tanımından önce çağrılan bir fonksiyon derleme hatasına yol açar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1035, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyonun prototipindeki parametre türleri, gerçek tanımındakilerle uyuşmalı mıdır?",
        .options = {"Hayır, farklı olabilir", "Evet, uyuşmalıdır", "Yalnızca parametre sayısı uyuşmalı, türler önemli değil", "Yalnızca dönüş türü uyuşmalı"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip ile tanım aynı imzaya (dönüş türü, parametre türleri) sahip olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1036, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int topla(int a, int b); ... double topla(int a, int b) { return a + b; } yapısı geçerli midir (prototip int, tanım double dönüyor)?",
        .options = {"Evet, derleyici otomatik dönüştürür", "Hayır, prototip ile tanımın dönüş türü uyuşmuyor; derleme hatası oluşur", "Evet, ama yalnızca int değerler döner", "Yalnızca 64-bit sistemlerde çalışır"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip ile gerçek tanımın dönüş türü de birebir uyuşmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1037, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Bir fonksiyon prototipi ile aynı fonksiyonun tam tanımı aynı dosyada birden fazla kez (aynı imzayla, tekrar tekrar) tanım olarak yazılabilir mi?",
        .options = {"Evet, sınırsız sayıda tanımlanabilir", "Hayır, aynı fonksiyon yalnızca bir kez tanımlanabilir (yeniden tanım hatası oluşur); prototip ise birden fazla kez yazılabilir", "Yalnızca 2 kez tanımlanabilir", "Tanım sayısı önemli değildir"},
        .acceptedAnswers = {"b"},
        .explanation = "Bir fonksiyon yalnızca bir kez tanımlanabilir; prototip (bildirim) ise tekrarlanabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1038, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyon prototipi, fonksiyonun gövdesini içermez.",
        .acceptedAnswers = {"1"},
        .explanation = "Prototip yalnızca imzayı içerir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1039, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Fonksiyon prototipi bir süslü parantez { } bloğuyla biter.",
        .acceptedAnswers = {"2"},
        .explanation = "Prototip noktalı virgülle biter, süslü parantezle değil.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1040, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Prototip sayesinde bir fonksiyon, gerçek tanımından önce çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Prototipin temel amacı budur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1041, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Prototip ile gerçek tanımın parametre türleri farklı olabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Parametre türleri prototip ile tanımda uyuşmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1042, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyon aynı dosyada yalnızca bir kez tanımlanabilir (birden fazla tanım hataya yol açar).",
        .acceptedAnswers = {"1"},
        .explanation = "Aynı imzaya sahip bir fonksiyon yalnızca bir kez tanımlanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1043, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Fonksiyon prototipi, fonksiyonun parametre adlarını mutlaka içermelidir (yalnızca türler yetersizdir).",
        .acceptedAnswers = {"2"},
        .explanation = "Prototipte yalnızca parametre türleri yeterlidir; adlar isteğe bağlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1044, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int topla(int a, int b)_____\nBir fonksiyon prototipini tamamlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {";"},
        .explanation = "Prototip noktalı virgülle biter.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1045, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int topla(int a, int b);\nint main() {\n    std::cout << topla(2, 3);\n    return 0;\n}\nint topla(int a, int b) {\n    _____ a + b;\n}\nDeğer döndürmek için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"return"},
        .explanation = "return, değeri döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1046, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ topla(int a, int b);\nint değer döndüren bir fonksiyon prototipi tanımlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"int"},
        .explanation = "Dönüş türü prototipin başında belirtilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1047, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "double bol(double a, double b);\nBu prototipe uygun tanımın dönüş türü _____ olmalıdır.",
        .acceptedAnswers = {"double"},
        .explanation = "Tanımın dönüş türü prototipiyle uyuşmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1048, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b);\nint main() {\n    std::cout << carp(4, 5);\n}\nint carp(int a, int _____) {\n    return a * b;\n}\nİkinci parametrenin adını (prototiple aynı sayıda parametre olacak şekilde) boşluğa yazın.",
        .acceptedAnswers = {"b"},
        .explanation = "Gövdede kullanılan parametre adı, tanımdaki adla eşleşmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1049, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(int x);\nProtipin sonunda gövde yerine _____ karakteri bulunur.",
        .acceptedAnswers = {";"},
        .explanation = "Prototip noktalı virgülle biter.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1050, .topicId = 44,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nint main() {\n    std::cout << topla(3, 4);\n    return 0;\n}\nint topla(int a, int b) {\n    return a + b;\n}\ntopla fonksiyonunun prototipini yazın.",
        .acceptedAnswers = {"int topla(int a, int b);"},
        .explanation = "Prototip, dönüş türü, ad ve parametre listesinden oluşur, noktalı virgülle biter.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1051, .topicId = 44,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b);\nint main() {\n    std::cout << carp(2, 5);\n    return 0;\n}\n_____\ncarp fonksiyonunun gerçek tanımını (gövdesiyle) yazın.",
        .acceptedAnswers = {"int carp(int a, int b) { return a * b; }"},
        .explanation = "Gerçek tanım, prototiple uyumlu imzaya ve bir gövdeye sahip olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1052, .topicId = 44,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int topla(int a, int b);\nint main() {\n    std::cout << topla(3, 4);\n    return 0;\n}\nint topla(int a, int b) {\n    return a + b;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"7"},
        .explanation = "3 + 4 = 7.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1053, .topicId = 44,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int carp(int a, int b);\nint main() {\n    std::cout << carp(2, 3) << carp(4, 5);\n    return 0;\n}\nint carp(int a, int b) {\n    return a * b;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"620"},
        .explanation = "carp(2,3) = 6, carp(4,5) = 20; birlikte '620' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1054, .topicId = 44,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint topla(int a, int b)\nint main() {\n    std::cout << topla(2, 3);\n    return 0;\n}\nint topla(int a, int b) {\n    return a + b;\n}\n\nBu kod derlenmez çünkü prototipin sonunda noktalı virgül eksik. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int topla(int a, int b);"},
        .explanation = "Prototip noktalı virgülle bitmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1055, .topicId = 44,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint topla(int a, int b);\nint main() {\n    std::cout << topla(2, 3);\n    return 0;\n}\ndouble topla(int a, int b) {\n    return a + b;\n}\n\nBu kod derlenmez çünkü prototipte dönüş türü int iken gerçek tanımda double kullanılmış. Hatalı satırı, prototiple uyumlu olacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int topla(int a, int b) {"},
        .explanation = "Tanımın dönüş türü prototipiyle aynı (int) olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1056, .topicId = 44,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint topla(int a, int b);\nint main() {\n    std::cout << topla(2, 3);\n    return 0;\n}\nint topla(int a, int c) {\n    return a + b;\n}\n\nProgramcı ikinci parametrenin adını prototiple tutarsız yazmış (tanımda c, kullanımda b). Düzeltilmiş dördüncü satırı yazın.",
        .acceptedAnswers = {"int topla(int a, int b) {"},
        .explanation = "Gövdede kullanılan parametre adı (b) ile tanımdaki parametre adı eşleşmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1057, .topicId = 44,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, prototipli bir topla fonksiyonu kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int topla(int a, int b) {\n    return a + b;\n}", "std::cout << topla(2, 3);\n    return 0;\n}", "int topla(int a, int b);\nint main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Prototip ve main açılışı (3), çağrı ve main kapanışı (2), gerçek tanım (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1058, .topicId = 44,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir topla fonksiyonunun önce prototipini yazıp, main() içinde çağırıp, ardından gerçek tanımını (gövdesini) main()'den sonra veren bir program yazın.",
        .acceptedAnswers = {"int", "return", "cout", "<<"},
        .explanation = "Program prototip, main() içinde çağrı ve main()'den sonra gerçek tanım içermelidir.",
        .baseXp = 40,
    });
```

- [ ] **Step 3: Wire the new function into `QuestionManager`**

`src/QuestionManager.cpp` already includes `"QuestionContent.h"` (from
Phase 13). Change the constructor's opening `reserve` call and its
final append-call lines from:

```cpp
    questions_.reserve(942);
```

to:

```cpp
    questions_.reserve(1232);
```

and from:

```cpp
    appendSection2Questions(questions_);
    appendSection3Questions(questions_);
    appendSection4Questions(questions_);
```

to:

```cpp
    appendSection2Questions(questions_);
    appendSection3Questions(questions_);
    appendSection4Questions(questions_);
    appendSection5Questions(questions_);
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/QuestionContent.h
    src/QuestionsSection2.cpp
    src/QuestionsSection3.cpp
    src/QuestionsSection4.cpp
```

to:

```cmake
    src/QuestionContent.h
    src/QuestionsSection2.cpp
    src/QuestionsSection3.cpp
    src/QuestionsSection4.cpp
    src/QuestionsSection5.cpp
```

- [ ] **Step 5: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `91/91 test(s) passed.` (unchanged — the test that counts
questions per topic is added in Task 4, once all of topics 41-50 have
their full 29 questions each).

- [ ] **Step 6: Commit**

```bash
git add src/QuestionContent.h src/QuestionsSection5.cpp src/QuestionManager.cpp CMakeLists.txt
git commit -m "feat(content): add questions for topics 41-44 (ids 943-1058)"
```

---

### Task 3: Questions for topics 45-47 (ids 1059-1145)

**Files:**
- Modify: `src/QuestionsSection5.cpp` (append more `push_back` calls to
  the SAME `appendSection5Questions` function body Task 2 created —
  do not redeclare the function or touch any other file)

**Interfaces:**
- Consumes: `appendSection5Questions(std::vector<Question>& questions)`
  defined in `src/QuestionsSection5.cpp` by Task 2 — append to its body,
  after the last `questions.push_back(...)` for id 1058 and before the
  function's closing `}`.
- Produces: ids 1059-1145 added to the same function. Task 4 appends
  after this task's last id (1145).

- [ ] **Step 1: Write topics 45-47's questions**

In `src/QuestionsSection5.cpp`, inside `appendSection5Questions`, add
these `push_back` calls right after the id-1058 block (before the
function's closing `}`):

```cpp
    // Topic 45: Varsayılan parametre
    questions.push_back(Question{
        .id = 1059, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "void selamla(std::string isim = \"Misafir\");\nBu fonksiyon parametresiz çağrıldığında (selamla();) isim parametresi ne olur?",
        .options = {"\"Misafir\"", "Boş string", "Derleme hatası", "Rastgele değer"},
        .acceptedAnswers = {"a"},
        .explanation = "Parametre verilmezse varsayılan değer (\"Misafir\") kullanılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1060, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir parametreye varsayılan değer, fonksiyonun neresinde belirtilir?",
        .options = {"Parametre tanımının yanında (=değer)", "Fonksiyon gövdesinin içinde", "Sadece main() içinde", "Yorum satırında"},
        .acceptedAnswers = {"a"},
        .explanation = "Varsayılan değer, parametre listesinde `tür ad = değer` şeklinde belirtilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1061, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b = 10);\nf(5) çağrısında b'nin değeri nedir?",
        .options = {"10", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "b için değer verilmediğinden varsayılan 10 kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1062, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b = 10);\nf(5, 20) çağrısında b'nin değeri nedir?",
        .options = {"20", "10", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Çağrıda açıkça verilen değer (20), varsayılan değerin yerine geçer.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1063, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdakilerden hangisi geçerli bir fonksiyon tanımıdır?",
        .options = {"void f(int a, int b = 5)", "void f(int a = 5, int b)", "void f(int a = 5, int b = 10, int c)", "void f(int a, int b = 5, int c)"},
        .acceptedAnswers = {"a"},
        .explanation = "Varsayılan değerli parametreler, listenin sonunda (trailing) olmalıdır; varsayılan olmayan bir parametre varsayılandan sonra gelemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1064, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b = 5, int c = 10);\nf(1, 2) çağrısında c'nin değeri nedir?",
        .options = {"10", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "c için değer verilmediğinden varsayılan 10 kullanılır (b ise 2 olur).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1065, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a = 1, int b);\nBu tanım neden derleme hatası verir?",
        .options = {"Varsayılan değerli parametre, varsayılan olmayandan önce gelemez", "int türü varsayılan değer alamaz", "Fonksiyonlar en fazla bir parametre alabilir", "f adı geçersizdir"},
        .acceptedAnswers = {"a"},
        .explanation = "a varsayılan değer aldığı için ondan sonraki tüm parametreler (b) de varsayılan değer almalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1066, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a = 1, int b = 2) {\n    return a + b;\n}\nint main() {\n    std::cout << f() << f(10);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"312", "33", "1210", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "f() -> 1+2=3, f(10) -> 10+2=12; birlikte '312' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1067, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Varsayılan parametre değeri olan bir fonksiyon, o parametre verilmeden de çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: varsayılan değer, parametre atlandığında kullanılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1068, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir parametreye varsayılan değer atansa bile, çağrıda o parametreye farklı bir değer vermek mümkündür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: çağrıda verilen değer varsayılanın yerine geçer.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1069, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a = 1, int b); şeklindeki bir tanım geçerlidir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan değerli bir parametreden sonra varsayılansız parametre gelemez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1070, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b = 5); tanımlı fonksiyon f(1, 2) şeklinde de çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: varsayılan parametreye açıkça değer vermek serbesttir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1071, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyonun tüm parametreleri aynı anda varsayılan değere sahip olabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: tüm parametreler varsayılan değerli olabilir, bu durumda fonksiyon hiç argüman almadan da çağrılabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1072, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a = 1, int b = 2, int c); tanımı derlenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: c varsayılan değeri olmadan a ve b'den sonra gelemez; trailing kuralı ihlal edilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1073, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "void f(int a, int b _____ 5);\nb parametresine 5 varsayılan değerini atamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"="},
        .explanation = "Varsayılan değer atama `=` işaretiyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1074, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b = 5);\nf(3) çağrısında b'nin değeri _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "b verilmediğinden varsayılan 5 kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1075, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a = 1, int b = 2, int c = 3);\nf(10, 20) çağrısında c'nin değeri _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "c verilmediğinden varsayılan 3 kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1076, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b = 5, int _____);\nBu tanım derlenmez çünkü varsayılan değeri olmayan bir parametre, varsayılan değerli b'den sonra geliyor. Kuralı hatırlayarak, varsayılan değerli parametrelerin listenin neresinde olması gerektiğini (bir kelimeyle, İngilizce) yazın.",
        .acceptedAnswers = {"trailing"},
        .explanation = "Varsayılan değerli parametreler listenin sonunda (trailing) olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1077, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int f(int a = 1, int b = 2) {\n    return a + b;\n}\nint main() {\n    std::cout << f(5);\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "a=5, b varsayılan 2 olduğundan 5+2=7.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1078, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int f(int a = 1, int b = 2) {\n    return a + b;\n}\nint main() {\n    std::cout << f();\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "Her iki parametre de varsayılan değerini alır: 1+2=3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1079, .topicId = 45,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nint main() {\n    std::cout << selamla();\n    return 0;\n}\nstd::string selamla(std::string isim) {\n    return \"Merhaba \" + isim;\n}\nselamla fonksiyonunun isim parametresi için \"Dünya\" varsayılan değerini veren bildirimini (prototip olarak) yazın.",
        .acceptedAnswers = {"std::string selamla(std::string isim = \"Dünya\");"},
        .explanation = "Varsayılan değer, tanım veya bildirimde (burada bildirimde) belirtilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1080, .topicId = 45,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b = 2) {\n    return a * b;\n}\nint main() {\n    _____\n    return 0;\n}\ncarp fonksiyonunu tek argümanla (a=6) çağırıp sonucu ekrana yazdıran satırı tamamlayın.",
        .acceptedAnswers = {"std::cout << carp(6);"},
        .explanation = "b verilmezse varsayılan 2 kullanılır: 6*2=12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1081, .topicId = 45,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int f(int a, int b = 3) {\n    return a * b;\n}\nint main() {\n    std::cout << f(4);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "b varsayılan 3 kullanılır: 4*3=12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1082, .topicId = 45,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a = 2, int b = 3) {\n    return a + b;\n}\nint main() {\n    std::cout << f() << f(10) << f(10, 20);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"51330"},
        .explanation = "f()=2+3=5, f(10)=10+3=13, f(10,20)=10+20=30; birlikte '51330' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1083, .topicId = 45,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid f(int a = 1, int b) {\n    std::cout << a + b;\n}\nint main() {\n    f(5, 6);\n    return 0;\n}\n\nBu kod derlenmez çünkü varsayılan değerli a parametresinden sonra varsayılansız b geliyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void f(int a, int b = 1) {"},
        .explanation = "Varsayılan değer, listenin sonundaki parametreye (b) taşınmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1084, .topicId = 45,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid f(int a = 1, int b = 2, int c) {\n    std::cout << a + b + c;\n}\nint main() {\n    f(1, 2, 3);\n    return 0;\n}\n\nBu kod derlenmez çünkü c, varsayılan değerli a ve b'den sonra varsayılansız kalmış. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void f(int c, int a = 1, int b = 2) {"},
        .explanation = "Varsayılansız parametre (c), varsayılan değerli parametrelerden önce gelmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1085, .topicId = 45,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid selamla(std::string isim, std::string mesaj = \"Merhaba\") {\n    std::cout << mesaj << \" \" << isim;\n}\nint main() {\n    selamla(mesaj);\n    return 0;\n}\n\nProgramcı main() içinde tanımsız bir mesaj değişkenini argüman olarak kullanmış; onun yerine sadece isim argümanını (\"Ali\") vererek çağırmalı. Düzeltilmiş çağrı satırını yazın.",
        .acceptedAnswers = {"selamla(\"Ali\");"},
        .explanation = "mesaj parametresi varsayılan değerli olduğundan çağrıda atlanabilir; sadece isim verilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1086, .topicId = 45,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, varsayılan parametreli bir fonksiyon kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << topla(5);\n    return 0;\n}", "int topla(int a, int b = 10) {\n    return a + b;\n}", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Fonksiyon tanımı (2), main açılışı (3), çağrı ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1087, .topicId = 45,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "isim parametresi varsayılan olarak \"Misafir\" değerini alan bir selamla fonksiyonu yazın; main() içinde hem argümansız hem de \"Ayşe\" argümanıyla çağırın.",
        .acceptedAnswers = {"std::string", "=", "cout"},
        .explanation = "Fonksiyon varsayılan parametreli tanımlanmalı ve iki farklı şekilde çağrılmalıdır.",
        .baseXp = 40,
    });

    // Topic 46: Fonksiyon aşırı yükleme
    questions.push_back(Question{
        .id = 1088, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Aynı isimli birden fazla fonksiyonun farklı parametre listeleriyle tanımlanmasına ne denir?",
        .options = {"Fonksiyon aşırı yükleme (overloading)", "Fonksiyon devralma (inheritance)", "Fonksiyon gizleme (hiding)", "Fonksiyon şablonu (template)"},
        .acceptedAnswers = {"a"},
        .explanation = "Aynı isimli, farklı parametre listeli fonksiyonlara aşırı yükleme (overloading) denir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1089, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki fonksiyonun overload sayılabilmesi için ne farklı olmalıdır?",
        .options = {"Parametre listesi (tür ve/veya sayı)", "Sadece dönüş türü", "Sadece fonksiyon gövdesi", "Sadece yorum satırları"},
        .acceptedAnswers = {"a"},
        .explanation = "Overload, parametre listesinin (tür ve/veya sayısının) farklılığıyla belirlenir; dönüş türü tek başına yeterli değildir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1090, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int f(int a);\ndouble f(int a);\nBu iki bildirim aynı dosyada bulunursa ne olur?",
        .options = {"Derleme hatası (aynı parametre listesiyle yeniden tanım)", "Geçerli bir overload olur", "İkincisi birinciyi sessizce geçersiz kılar", "Sadece bir uyarı verir, çalışır"},
        .acceptedAnswers = {"a"},
        .explanation = "Parametre listeleri aynı olduğundan, sadece dönüş türü farklı olması overload için yetersizdir; bu bir yeniden tanım hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1091, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void yazdir(int x);\nvoid yazdir(double x);\nBu iki fonksiyon geçerli bir overload çifti midir?",
        .options = {"Evet, parametre türleri farklı (int/double)", "Hayır, isimler aynı olduğundan hata verir", "Hayır, dönüş türleri aynı olduğundan hata verir", "Evet ama sadece biri çağrılabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "Parametre türleri farklı olduğundan (int vs double) bu geçerli bir overload'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1092, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a);\nvoid f(int a, int b);\nBu iki fonksiyon geçerli bir overload çifti midir?",
        .options = {"Evet, parametre sayıları farklı (1 ve 2)", "Hayır, isimler aynı olduğundan hata verir", "Hayır, ikisi de int aldığından hata verir", "Evet ama ikincisi hiç çağrılamaz"},
        .acceptedAnswers = {"a"},
        .explanation = "Parametre sayısı farklı olduğundan (1 ve 2) bu geçerli bir overload'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1093, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a);\nvoid f(double a);\nint main() {\n    f(3.5);\n}\nHangi f çağrılır?",
        .options = {"f(double a) — argüman zaten double", "f(int a) — int'e yuvarlanır", "İkisi birden çağrılır", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "3.5 bir double literal olduğundan, tam eşleşen f(double) overload'ı seçilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1094, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a, int b);\ndouble f(int a, int b);\nBu iki bildirim neden derleme hatasıdır?",
        .options = {"Parametre listeleri aynı; sadece dönüş türü farklı, bu overload için yetersiz", "int ve double aynı fonksiyonda kullanılamaz", "Fonksiyonlar en fazla bir kez tanımlanabilir", "b parametresi geçersizdir"},
        .acceptedAnswers = {"a"},
        .explanation = "Overload çözümlemesi dönüş türüne bakmaz; parametre listesi aynı olduğundan bu geçerli bir overload değil, yeniden tanım hatasıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1095, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int a, int b);\nvoid f(int a, double b);\nint main() {\n    f(1, 2);\n}\nHangi f çağrılır?",
        .options = {"f(int, int) — her iki argüman da tam sayı, tam eşleşme", "f(int, double) — ikinci argüman double'a çevrilir", "Belirsizlik hatası (ambiguous)", "Derleme hatası, hiçbiri eşleşmez"},
        .acceptedAnswers = {"a"},
        .explanation = "f(1, 2) çağrısında her iki argüman da int olduğundan, f(int,int) overload'ı tam eşleşme sağlar ve belirsizlik olmadan çağrılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1096, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Fonksiyon overloading, aynı isimli fonksiyonların farklı parametre listeleriyle tanımlanmasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: overload, parametre listesi farklılığına dayanır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1097, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Sadece dönüş türü farklı olan iki fonksiyon, geçerli bir overload çifti oluşturur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: overload çözümlemesi dönüş türüne bakmaz, parametre listesi aynıysa bu bir yeniden tanım hatasıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1098, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int f(int a); ve int f(double a); geçerli bir overload çiftidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: parametre türleri farklı (int/double).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1099, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Overload çözümlemesi, çağrıdaki argüman sayısı ve türlerine bakarak hangi fonksiyonun çağrılacağını belirler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: derleyici, argümanların sayı ve türüne göre en uygun overload'ı seçer.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1100, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a); ve int f(int a); (parametre listeleri aynı, dönüş türleri farklı) aynı dosyada birlikte derlenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: parametre listeleri aynı olduğundan, sadece dönüş türü farkı overload sağlamaz; derleme hatası oluşur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1101, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b); ve void f(int a, int b, int c); geçerli bir overload çiftidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: parametre sayıları farklı (2 ve 3).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1102, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Aynı isimli fonksiyonların farklı parametre listeleriyle birden fazla kez tanımlanmasına fonksiyon _____ denir (İngilizce terim).",
        .acceptedAnswers = {"overloading", "overload"},
        .explanation = "Bu kavrama overloading (aşırı yükleme) denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1103, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Overload olabilmek için fonksiyonların _____ listesi farklı olmalıdır (dönüş türü değil).",
        .acceptedAnswers = {"parametre"},
        .explanation = "Overload çözümlemesi parametre listesine bakar, dönüş türüne bakmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1104, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int f(int a);\ndouble f(int a);\nBu iki bildirim aynı dosyada olursa derleyici bunu geçerli bir overload olarak KABUL ETMEZ, çünkü sadece _____ türü farklıdır (parametre listesi aynıdır).",
        .acceptedAnswers = {"dönüş"},
        .explanation = "Sadece dönüş türü farkı, overload için yeterli değildir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1105, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b);\nvoid f(int a, double b);\nint main() {\n    f(1, 2);\n}\nBu çağrıda f(int, _____) overload'ı çağrılır çünkü her iki argüman da tam sayıdır.",
        .acceptedAnswers = {"int"},
        .explanation = "f(1,2) çağrısında iki argüman da int olduğundan tam eşleşen f(int,int) seçilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1106, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir(int x);\nvoid yazdir(std::string x);\nyazdir(\"Merhaba\") çağrısı yazdir(_____) overload'ını çağırır.",
        .acceptedAnswers = {"std::string"},
        .explanation = "\"Merhaba\" bir string literal olduğundan std::string overload'ı çağrılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1107, .topicId = 46,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir(int x) {\n    std::cout << \"int: \" << x;\n}\n_____\nvoid yazdir(double x) {\n    std::cout << \"double: \" << x;\n}\nyazdir fonksiyonunun int yerine double parametre alan overload'unun bildirimini (tanım satırının başlığını) yazın.",
        .acceptedAnswers = {"void yazdir(double x) {"},
        .explanation = "Overload, farklı parametre türüyle (double) tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1108, .topicId = 46,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int topla(int a, int b) {\n    return a + b;\n}\n_____\nint main() {\n    std::cout << topla(1, 2, 3);\n    return 0;\n}\ntopla fonksiyonunun üç int parametre alan overload'unun tanımını yazın (a+b+c döndürsün).",
        .acceptedAnswers = {"int topla(int a, int b, int c) { return a + b + c; }"},
        .explanation = "Parametre sayısı farklı olduğundan bu geçerli bir overload'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1109, .topicId = 46,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a) {\n    std::cout << \"int\";\n}\nvoid f(double a) {\n    std::cout << \"double\";\n}\nint main() {\n    f(5);\n    f(5.5);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"intdouble"},
        .explanation = "f(5) int overload'ını, f(5.5) double overload'ını çağırır: 'intdouble'.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1110, .topicId = 46,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void f(int a, int b) {\n    std::cout << \"iki\";\n}\nvoid f(int a, int b, int c) {\n    std::cout << \"uc\";\n}\nint main() {\n    f(1, 2);\n    f(1, 2, 3);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"ikiuc"},
        .explanation = "f(1,2) iki parametreli overload'ı, f(1,2,3) üç parametreli overload'ı çağırır: 'ikiuc'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1111, .topicId = 46,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint f(int a) {\n    return a;\n}\ndouble f(int a) {\n    return a;\n}\nint main() {\n    std::cout << f(5);\n    return 0;\n}\n\nBu kod derlenmez çünkü iki f fonksiyonu aynı parametre listesine (int a) sahip, sadece dönüş türleri farklı. Hatalı ikinci fonksiyon tanımının başlığını, geçerli bir overload olacak şekilde (bir int parametre daha ekleyerek) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"double f(int a, int b) {"},
        .explanation = "Parametre listesi farklılaştırılarak (ikinci bir int parametre eklenerek) geçerli bir overload elde edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1112, .topicId = 46,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid yazdir(int x) {\n    std::cout << x;\n}\nvoid yazdir(int y) {\n    std::cout << y;\n}\nint main() {\n    yazdir(5);\n    return 0;\n}\n\nBu kod derlenmez çünkü iki yazdir fonksiyonu tamamen aynı parametre listesine (int) sahip; parametre adının farklı olması (x/y) yeterli değildir. İkinci fonksiyonun başlığını, double parametre alacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void yazdir(double y) {"},
        .explanation = "Parametre adları değil, parametre TÜRLERİ overload'ı belirler; türü değiştirmek (double) geçerli bir overload sağlar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1113, .topicId = 46,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint carp(int a, int b) {\n    return a * b;\n}\ndouble carp(int a, int b) {\n    return a * b;\n}\nint main() {\n    std::cout << carp(2, 3);\n    return 0;\n}\n\nİki carp fonksiyonu aynı parametre listesine sahip; ikincisi çift sayı (double) parametre alacak şekilde değiştirilmeli. Düzeltilmiş ikinci fonksiyonun başlığını yazın.",
        .acceptedAnswers = {"double carp(double a, double b) {"},
        .explanation = "Parametre türleri double yapılarak, int overload'dan farklı geçerli bir overload elde edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1114, .topicId = 46,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, overload edilmiş bir yazdir fonksiyonu kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"void yazdir(double x) {\n    std::cout << x;\n}", "yazdir(5);\n    yazdir(5.5);\n    return 0;\n}", "void yazdir(int x) {\n    std::cout << x;\n}\nint main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "int overload (3), main içeriği (2), double overload (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1115, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void yazdir(int x);\nvoid yazdir(int x, int y);\nİlk fonksiyon 1, ikincisi 2 parametre aldığından, bunlar parametre _____ farklı olduğu için geçerli bir overload'dır (Türkçe kelime).",
        .acceptedAnswers = {"sayısı", "sayisi"},
        .explanation = "Parametre sayısının farklı olması (1 ve 2) overload için yeterlidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1116, .topicId = 46,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "topla adında biri iki int, diğeri iki double parametre alan iki overload fonksiyon yazın; main() içinde her ikisini de çağırıp sonuçlarını yazdırın.",
        .acceptedAnswers = {"int", "double", "return", "cout"},
        .explanation = "İki fonksiyon aynı isimle ama farklı parametre türleriyle (int/double) tanımlanmalı ve her ikisi de çağrılmalıdır.",
        .baseXp = 40,
    });

    // Topic 47: Değer ile parametre gönderme
    questions.push_back(Question{
        .id = 1117, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyona değer ile (by value) parametre gönderildiğinde ne olur?",
        .options = {"Argümanın bağımsız bir kopyası oluşturulur", "Argümanın kendisi doğrudan değiştirilir", "Argüman hiç kopyalanmadan referans olarak kullanılır", "Argüman bellekte silinir"},
        .acceptedAnswers = {"a"},
        .explanation = "Değer ile gönderimde parametre, argümanın bağımsız bir kopyasıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1118, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "void f(int x) {\n    x = 100;\n}\nint main() {\n    int a = 5;\n    f(a);\n    std::cout << a;\n}\nEkrana ne yazdırılır?",
        .options = {"5", "100", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "x, a'nın bir kopyasıdır; x'in değişmesi a'yı etkilemez, a hâlâ 5'tir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1119, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Değer ile parametre göndermenin en belirgin dezavantajı nedir?",
        .options = {"Büyük nesnelerde kopyalama maliyeti", "Fonksiyonun hiç çalışmaması", "Derleyicinin bunu desteklememesi", "Sadece int türü için çalışması"},
        .acceptedAnswers = {"a"},
        .explanation = "Kopyalama, büyük nesneler (ör. büyük string/vector) için performans maliyeti getirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1120, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void kare(int x) {\n    x = x * x;\n}\nint main() {\n    int sayi = 4;\n    kare(sayi);\n    std::cout << sayi;\n}\nEkrana ne yazdırılır?",
        .options = {"4", "16", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "kare fonksiyonu sayi'nin kopyasını değiştirir; orijinal sayi değişmez, 4 kalır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1121, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void artir(int x) {\n    x++;\n}\nint main() {\n    int sayac = 10;\n    artir(sayac);\n    artir(sayac);\n    std::cout << sayac;\n}\nEkrana ne yazdırılır?",
        .options = {"10", "11", "12", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Her artir çağrısı sadece kendi kopyasını artırır; sayac hiç değişmeden 10 kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1122, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int f(int x) {\n    x += 5;\n    return x;\n}\nint main() {\n    int a = 10;\n    int b = f(a);\n    std::cout << a << \" \" << b;\n}\nEkrana ne yazdırılır?",
        .options = {"10 15", "15 15", "10 10", "15 10"},
        .acceptedAnswers = {"a"},
        .explanation = "a, f'ye kopyalanır ve fonksiyon içinde değişen kopya döndürülür (b=15); a orijinali değişmeden 10 kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1123, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int x, int y) {\n    x = x + y;\n    y = 0;\n}\nint main() {\n    int a = 3, b = 4;\n    f(a, b);\n    std::cout << a << \" \" << b;\n}\nEkrana ne yazdırılır?",
        .options = {"3 4", "7 0", "7 4", "3 0"},
        .acceptedAnswers = {"a"},
        .explanation = "x ve y, a ve b'nin kopyalarıdır; fonksiyon içindeki değişiklikler a ve b'yi etkilemez, ikisi de değişmeden kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1124, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Değer ile parametre gönderiminde, fonksiyon çağrılırken argüman için ne zaman kopyalama gerçekleşir?",
        .options = {"Fonksiyon çağrıldığı anda, parametre oluşturulurken", "Fonksiyon return yaptığında", "Program sonlandığında", "Hiçbir zaman, kopyalama olmaz"},
        .acceptedAnswers = {"a"},
        .explanation = "Kopyalama, çağrı anında parametrenin ilklendirilmesiyle gerçekleşir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1125, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Değer ile gönderilen bir parametre, çağıranın orijinal değişkeninin bir kopyasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: değer ile gönderim bağımsız bir kopya oluşturur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1126, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Değer ile gönderilen bir parametrenin fonksiyon içinde değiştirilmesi, çağıranın orijinal değişkenini de değiştirir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: parametre bağımsız bir kopya olduğundan, orijinal değişken etkilenmez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1127, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void f(int x) { x = 0; } int main() { int a = 5; f(a); } çağrısından sonra a hâlâ 5'tir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: x, a'nın kopyasıdır; x'in sıfırlanması a'yı etkilemez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1128, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Büyük bir std::string'i değer ile parametre olarak göndermek, referans ile göndermeye kıyasla daha fazla kopyalama maliyeti taşır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: değer ile gönderim, tüm string içeriğini kopyalarken referans hiç kopyalamaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1129, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(int x) { x++; } int main() { int a = 1; f(a); f(a); std::cout << a; } kodu ekrana 3 yazdırır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: her çağrı yalnızca kendi kopyasını artırır, a hiç değişmeden 1 kalır; ekrana 1 yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1130, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Değer ile parametre gönderimi, temel türler (int, double gibi) için genellikle ucuz bir kopyalama işlemidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: temel türlerin kopyalanması ucuzdur; maliyet asıl büyük nesnelerde (string, vector) belirginleşir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1131, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Değer ile gönderimde, parametre argümanın bağımsız bir _____ olur.",
        .acceptedAnswers = {"kopyası", "kopyasi"},
        .explanation = "Değer ile gönderim, argümanın bağımsız bir kopyasını oluşturur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1132, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(int x) {\n    x = 50;\n}\nint main() {\n    int a = 5;\n    f(a);\n    std::cout << a;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "x bağımsız bir kopya olduğundan a değişmeden 5 kalır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1133, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int f(int x) {\n    return x * 2;\n}\nint main() {\n    int a = 5;\n    int b = f(a);\n    std::cout << a << \" \" << b;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5 10"},
        .explanation = "a değişmez (5), b ise f'nin döndürdüğü değeri alır (10).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1134, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Değer ile parametre gönderiminin en büyük maliyeti, büyük nesnelerde oluşan _____ (kopyalama) işlemidir (bir kelimeyle, Türkçe).",
        .acceptedAnswers = {"kopyalama"},
        .explanation = "Büyük nesnelerin kopyalanması işlem maliyeti getirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1135, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void degistir(int x) {\n    x = x + 100;\n}\nint main() {\n    int deger = 1;\n    degistir(deger);\n    std::cout << deger;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "degistir, deger'in kopyasını değiştirir; orijinal deger değişmeden 1 kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1136, .topicId = 47,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void sifirla(int x) {\n    _____\n}\nint main() {\n    int a = 5;\n    sifirla(a);\n    std::cout << a;\n    return 0;\n}\nsifirla fonksiyonunun gövdesini (x'i 0 yapan satırı) tamamlayın. (Not: değer ile gönderim olduğu için a yine de 5 kalacaktır.)",
        .acceptedAnswers = {"x = 0;"},
        .explanation = "x, a'nın bir kopyası olduğundan x=0 yapmak a'yı etkilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1137, .topicId = 47,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int ikiKatiniAl(int x) {\n    _____\n}\nint main() {\n    std::cout << ikiKatiniAl(7);\n    return 0;\n}\nikiKatiniAl fonksiyonunun x'in iki katını döndüren gövdesini tamamlayın.",
        .acceptedAnswers = {"return x * 2;"},
        .explanation = "Fonksiyon, parametrenin kopyasını iki katına çıkarıp döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1138, .topicId = 47,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void f(int x) {\n    x = x * 10;\n    std::cout << x << \" \";\n}\nint main() {\n    int a = 3;\n    f(a);\n    std::cout << a;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30 3"},
        .explanation = "Fonksiyon içinde x=30 yazdırılır, ardından a hâlâ 3 olduğundan 3 yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1139, .topicId = 47,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void f(int x) {\n    x++;\n}\nint main() {\n    int a = 1;\n    f(a);\n    f(a);\n    f(a);\n    std::cout << a;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "Her f çağrısı yalnızca kendi kopyasını artırır; a hiçbir zaman değişmez, 1 kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1140, .topicId = 47,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nvoid ikiyeKatla(int x) {\n    x = x * 2;\n}\nint main() {\n    int sayi = 5;\n    ikiyeKatla(sayi);\n    std::cout << sayi;\n    return 0;\n}\n\nProgramcı sayi'nin 10 yazdırılmasını bekliyor ama değer ile gönderim yüzünden 5 yazdırılıyor. Fonksiyonun, çağıranın değişkenini gerçekten değiştirmesi için parametre bildirimini (referansa çevirerek) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void ikiyeKatla(int& x) {"},
        .explanation = "Çağıranın değişkenini değiştirmek için parametre referans (&) olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1141, .topicId = 47,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nvoid takasEt(int a, int b) {\n    int gecici = a;\n    a = b;\n    b = gecici;\n}\nint main() {\n    int x = 1, y = 2;\n    takasEt(x, y);\n    std::cout << x << \" \" << y;\n    return 0;\n}\n\nProgramcı x ve y'nin takas edilmesini bekliyor ama değer ile gönderim yüzünden ikisi de değişmeden kalıyor (1 2 yazdırılır). Fonksiyonun gerçekten takas yapması için parametre bildirimini (referansa çevirerek) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void takasEt(int& a, int& b) {"},
        .explanation = "Gerçek takas için parametrelerin referans (&) olması gerekir; değer ile gönderim sadece kopyaları takas eder.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1142, .topicId = 47,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid birEkle(int sayi) {\n    sayi = sayi + 1;\n}\nint main() {\n    int deger = 9;\n    birEkle(deger);\n    std::cout << deger;\n    return 0;\n}\n\nProgramcı deger'in 10 olmasını bekliyor ama değer ile gönderim yüzünden 9 kalıyor. Fonksiyon başlığını, çağıranın değişkenini değiştirecek şekilde (referans parametreyle) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void birEkle(int& sayi) {"},
        .explanation = "Çağıranın değişkenini kalıcı olarak değiştirmek için parametre referans (&) olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1143, .topicId = 47,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, değer ile parametre gönderilen bir fonksiyon kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int a = 5;\n    f(a);\n    std::cout << a;\n    return 0;\n}", "void f(int x) {\n    x = 100;\n}", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Fonksiyon tanımı (2), main açılışı (3), gövde ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1144, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(int x) {\n    x = x + 1;\n}\nDeğer ile gönderimde x, çağırandaki argümanın bir kopyası olduğundan, bu fonksiyonun çağırandaki değişken üzerinde hiçbir kalıcı _____ yoktur (bir kelimeyle, Türkçe).",
        .acceptedAnswers = {"etkisi"},
        .explanation = "Değer ile gönderim, çağırandaki orijinal değişkeni asla etkilemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1145, .topicId = 47,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir sayının karesini değer ile parametre alarak hesaplayıp döndüren bir fonksiyon yazın; main() içinde çağırıp hem orijinal değişkeni hem de dönen sonucu yazdırarak orijinalin değişmediğini gösterin.",
        .acceptedAnswers = {"int", "return", "cout"},
        .explanation = "Fonksiyon parametreyi değer ile almalı, kareyi döndürmeli; orijinal değişken değişmemelidir.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `91/91 test(s) passed.` (unchanged — no existing test yet
counts these topics' questions).

- [ ] **Step 3: Commit**

```bash
git add src/QuestionsSection5.cpp
git commit -m "feat(content): add questions for topics 45-47 (ids 1059-1145)"
```

---

### Task 4: Questions for topics 48-50 (ids 1146-1232), test updates, and final integration

**Files:**
- Modify: `src/QuestionsSection5.cpp` (append the final `push_back`
  calls to `appendSection5Questions`)
- Modify: `tests/QuestionManagerTests.cpp` (add one new per-section
  minimum-count test)
- Modify: `docs/superpowers/roadmap.md` (mark Phase 16 complete)

**Interfaces:**
- Consumes: `appendSection5Questions(std::vector<Question>& questions)`
  in `src/QuestionsSection5.cpp` — append after Task 3's last id (1145),
  before the function's closing `}`. After this task, ids 943-1232 are
  all present (10 topics x 29 questions) and the function is complete.

- [ ] **Step 1: Write topics 48-50's questions**

In `src/QuestionsSection5.cpp`, inside `appendSection5Questions`, add
these `push_back` calls right after the id-1145 block (before the
function's closing `}`):

```cpp
    // Topic 48: Referans ile parametre gönderme
    questions.push_back(Question{
        .id = 1146, .topicId = 48,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyonun parametresi int& x şeklinde tanımlanırsa, x nedir?",
        .options = {"Çağırandaki değişkenin kendisine bir referans (takma ad)", "Çağırandaki değişkenin bağımsız bir kopyası", "Bir gösterici (pointer)", "Sabit bir değer"},
        .acceptedAnswers = {"a"},
        .explanation = "Referans parametre, çağırandaki değişkenin kendisine bir takma addır; kopya oluşturulmaz.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1147, .topicId = 48,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void f(int& x) {\n    x = 100;\n}\nint main() {\n    int a = 5;\n    f(a);\n    std::cout << a;\n}\nEkrana ne yazdırılır?",
        .options = {"100", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "x, a'nın kendisine bir referanstır; x'in değişmesi doğrudan a'yı değiştirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1148, .topicId = 48,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void f(int& x) {\n    x++;\n}\nint main() {\n    int sayac = 10;\n    f(sayac);\n    f(sayac);\n    std::cout << sayac;\n}\nEkrana ne yazdırılır?",
        .options = {"12", "10", "11", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Her çağrı doğrudan sayac'ı bir artırır: 10 -> 11 -> 12.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1149, .topicId = 48,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f(int& x) {\n    x = x * 2;\n}\nint main() {\n    f(5);\n    return 0;\n}\nBu kod ne olur?",
        .options = {"Derleme hatası, çünkü int& bir literale (5) bağlanamaz", "10 yazdırır", "5 yazdırır", "Çalışma zamanı hatası verir"},
        .acceptedAnswers = {"a"},
        .explanation = "Non-const bir referans (int&) yalnızca bir değişkene (lvalue) bağlanabilir, doğrudan bir literale bağlanamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1150, .topicId = 48,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void degistir(int& x, int& y) {\n    int t = x;\n    x = y;\n    y = t;\n}\nint main() {\n    int a = 1, b = 2;\n    degistir(a, b);\n    std::cout << a << \" \" << b;\n}\nEkrana ne yazdırılır?",
        .options = {"\"2 1\"", "\"1 2\"", "\"1 1\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "x ve y referans olduğundan a ve b'nin kendileri takas edilir: a=2, b=1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1151, .topicId = 48,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Referans parametrenin (T&), değer parametresine (T) göre temel avantajı nedir?",
        .options = {"Hem kopyalamadan kaçınmak hem de çağırandaki değişkeni değiştirebilmek", "Sadece daha az bellek kullanmak, değiştirememek", "Sadece okunabilirlik", "Fonksiyonun daha hızlı derlenmesi"},
        .acceptedAnswers = {"a"},
        .explanation = "Referans, kopyalamadan kaçınırken çağırandaki değişkeni doğrudan değiştirmeye de izin verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1152, .topicId = 48,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int& x) {\n    x += 10;\n}\nint main() {\n    int a = 5;\n    int& r = a;\n    f(r);\n    std::cout << a;\n}\nEkrana ne yazdırılır?",
        .options = {"15", "5", "10", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "r, a'nın bir takma adıdır; f(r) çağrısı x'i de a'ya bağlar, dolayısıyla a doğrudan değişir: 5+10=15.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1153, .topicId = 48,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int& x, int y) {\n    x = x + y;\n    y = 0;\n}\nint main() {\n    int a = 3, b = 4;\n    f(a, b);\n    std::cout << a << \" \" << b;\n}\nEkrana ne yazdırılır?",
        .options = {"\"7 4\"", "\"7 0\"", "\"3 4\"", "\"3 0\""},
        .acceptedAnswers = {"a"},
        .explanation = "x referans olduğundan a=a+b=7 olur; y ise değer ile geldiğinden y=0 yapmak b'yi etkilemez, b 4 kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1154, .topicId = 48,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Referans parametre (T&), çağırandaki değişkenin kendisine bir takma addır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: referans, ayrı bir kopya değil, orijinal değişkenin kendisidir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1155, .topicId = 48,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Referans parametre kullanan bir fonksiyon çağrılırken, argümanın ayrı bir kopyası oluşturulur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: referans, mevcut değişkenin kendisidir; kopya oluşturulmaz.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1156, .topicId = 48,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void f(int& x) { x = 0; } int main() { int a = 5; f(a); } çağrısından sonra a artık 0'dır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: x, a'nın kendisi olduğundan x=0 yapmak a'yı da sıfırlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1157, .topicId = 48,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int& x parametreli bir fonksiyon, f(10) gibi doğrudan bir literal ile çağrılabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: non-const bir referans yalnızca bir değişkene bağlanabilir, literale bağlanamaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1158, .topicId = 48,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Referans parametreler, büyük nesnelerin (örneğin büyük bir std::string) fonksiyona kopyalanmadan geçirilmesini sağlar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: referans, nesnenin kendisine erişim sağlar, kopyalama yapmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1159, .topicId = 48,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(int& a, int& b) { int t = a; a = b; b = t; } çağrısı, çağırandaki iki değişkenin değerlerini gerçekten takas eder.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: a ve b referans olduğundan, fonksiyon içindeki değişiklikler çağırandaki orijinal değişkenlere yansır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1160, .topicId = 48,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "int& x şeklinde tanımlanan bir parametre, çağırandaki argümana bir _____ (takma ad) olur (Türkçe kelime).",
        .acceptedAnswers = {"referans"},
        .explanation = "Referans parametre, argümanın kendisine bir takma addır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1161, .topicId = 48,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(int& x) {\n    x = 20;\n}\nint main() {\n    int a = 5;\n    f(a);\n    std::cout << a;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"20"},
        .explanation = "x, a'nın kendisi olduğundan x=20 yapmak a'yı da 20 yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1162, .topicId = 48,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void carpZaman2(int& x) {\n    x = x * 2;\n}\nint main() {\n    int sayi = 6;\n    carpZaman2(sayi);\n    std::cout << sayi;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"12"},
        .explanation = "Referans parametre sayi'nin kendisini değiştirir: 6*2=12.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1163, .topicId = 48,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Referans parametreler, büyük nesnelerin kopyalanmasını önler ve aynı zamanda çağırandaki değeri _____ imkanı verir (Türkçe kelime, isim hali).",
        .acceptedAnswers = {"değiştirme", "degistirme"},
        .explanation = "Referans, hem kopyalamayı önler hem de çağırandaki değişkenin değiştirilmesine izin verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1164, .topicId = 48,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(int& a, int& b) {\n    int t = a;\n    a = b;\n    b = t;\n}\nint main() {\n    int x = 3, y = 8;\n    f(x, y);\n    std::cout << x << \" \" << y;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8 3"},
        .explanation = "a ve b referans olduğundan x ve y gerçekten takas edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1165, .topicId = 48,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int& x parametreli bir fonksiyon çağrılırken, f(5) gibi bir _____ ile çağrılamaz çünkü referans bir değişkene bağlanmalıdır (İngilizce kelime).",
        .acceptedAnswers = {"literal"},
        .explanation = "Non-const referans, geçici bir değere (literale) değil, bir değişkene bağlanmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1166, .topicId = 48,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void ikiyeBol(int& x) {\n    _____\n}\nint main() {\n    int sayi = 20;\n    ikiyeBol(sayi);\n    std::cout << sayi;\n    return 0;\n}\nikiyeBol fonksiyonunun gövdesini (x'i ikiye bölen satırı) tamamlayın.",
        .acceptedAnswers = {"x = x / 2;"},
        .explanation = "x referans olduğundan, x üzerindeki değişiklik doğrudan sayi'yi etkiler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1167, .topicId = 48,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nint main() {\n    int a = 1, b = 2;\n    takasEt(a, b);\n    std::cout << a << \" \" << b;\n    return 0;\n}\ntakasEt fonksiyonunu, iki int'i referans parametrelerle gerçekten takas edecek şekilde (gövdesiyle) yazın.",
        .acceptedAnswers = {"void takasEt(int& a, int& b) { int t = a; a = b; b = t; }"},
        .explanation = "Gerçek takas için parametrelerin referans (&) olması gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1168, .topicId = 48,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void f(int& x) {\n    x = x + 1;\n}\nint main() {\n    int a = 9;\n    f(a);\n    f(a);\n    std::cout << a;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"11"},
        .explanation = "Her çağrı a'yı doğrudan bir artırır: 9 -> 10 -> 11.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1169, .topicId = 48,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void f(int& x, int y) {\n    x = x * y;\n    y = y + 1;\n}\nint main() {\n    int a = 2, b = 3;\n    f(a, b);\n    std::cout << a << \" \" << b;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6 3"},
        .explanation = "x referans olduğundan a=a*b=6 olur; y değer ile geldiğinden y=y+1 yapmak b'yi etkilemez, b 3 kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1170, .topicId = 48,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid f(int& x) {\n    x = x + 1;\n}\nint main() {\n    f(5);\n    return 0;\n}\n\nBu kod derlenmez çünkü int& parametresi bir literale (5) bağlanamaz; referans bir değişkene ihtiyaç duyar. main() içindeki hatalı çağrı satırını, önce bir int değişken tanımlayıp onu göndererek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int a = 5; f(a);"},
        .explanation = "int& yalnızca bir değişkene (lvalue) bağlanabilir; önce bir değişken tanımlanmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1171, .topicId = 48,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nvoid takasEt(int& a, int b) {\n    int t = a;\n    a = b;\n    b = t;\n}\nint main() {\n    int x = 1, y = 2;\n    takasEt(x, y);\n    std::cout << x << \" \" << y;\n    return 0;\n}\n\nProgramcı x ve y'nin tamamen takas edilmesini bekliyor ama ikinci parametre (b) referans olmadığından sadece x güncellenir, y değişmeden kalır. Fonksiyon başlığını, her iki parametre de referans olacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void takasEt(int& a, int& b) {"},
        .explanation = "Gerçek takas için her iki parametrenin de referans (&) olması gerekir; b değer ile geldiğinden y hiç değişmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1172, .topicId = 48,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid sifirla(int a) {\n    a = 0;\n}\nint main() {\n    int deger = 42;\n    sifirla(deger);\n    std::cout << deger;\n    return 0;\n}\n\nProgramcı deger'in 0 yazdırılmasını bekliyor ama parametre değer ile gönderildiği için deger değişmeden 42 kalıyor. Fonksiyon başlığını, çağırandaki değişkeni gerçekten sıfırlayacak şekilde (referans parametreyle) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void sifirla(int& a) {"},
        .explanation = "Çağırandaki değişkeni kalıcı olarak değiştirmek için parametre referans (&) olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1173, .topicId = 48,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, referans parametreli bir fonksiyon kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"void f(int& x) {\n    x = x + 10;\n}", "int a = 5;\n    f(a);\n    std::cout << a;\n    return 0;\n}", "int main() {"},
        .acceptedAnswers = {"1 3 2"},
        .explanation = "Fonksiyon tanımı (1), main açılışı (3), gövde ve kapanış (2): sıra 1 3 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1174, .topicId = 48,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir değişkenin değerini referans (&) ile alan bir parametre üzerinden iki katına çıkaran bir fonksiyon yazın; main() içinde çağırıp orijinal değişkenin değiştiğini ekrana yazdırarak gösterin.",
        .acceptedAnswers = {"&", "cout"},
        .explanation = "Fonksiyon parametreyi referans olarak almalı ve çağırandaki değişkeni doğrudan değiştirmelidir.",
        .baseXp = 40,
    });

    // Topic 49: const referans
    questions.push_back(Question{
        .id = 1175, .topicId = 49,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "const int& x parametreli bir fonksiyon içinde x'in değerini değiştirmeye (x = ...;) çalışmak ne olur?",
        .options = {"Derleme hatası", "Çalışır, çağırandaki değişkeni değiştirir", "Çalışır ama hiçbir etkisi olmaz", "Çalışma zamanı hatası verir"},
        .acceptedAnswers = {"a"},
        .explanation = "const bir referansa atama yapılamaz; bu bir derleme hatasıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1176, .topicId = 49,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "const int& parametresinin normal int& parametresine göre temel farkı nedir?",
        .options = {"const referans, fonksiyon içinde değiştirilemez", "const referans, kopyalama yapar", "const referans, sadece global değişkenlere bağlanabilir", "Fark yoktur"},
        .acceptedAnswers = {"a"},
        .explanation = "const T&, T&'nin sağladığı erişimi verirken değiştirilmeyi engeller.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1177, .topicId = 49,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void yazdir(const std::string& s) {\n    std::cout << s;\n}\nint main() {\n    yazdir(\"Merhaba\");\n    return 0;\n}\nBu kod derlenir mi?",
        .options = {"Evet, çünkü const referans bir literale (geçici değere) bağlanabilir", "Hayır, referanslar asla literale bağlanamaz", "Hayır, std::string const alamaz", "Evet ama çalışma zamanında çöker"},
        .acceptedAnswers = {"a"},
        .explanation = "const T&, normal T&'nin aksine, geçici bir değere (literale) bağlanabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1178, .topicId = 49,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f(const int& x) {\n    x = 5;\n}\nBu kod neden derlenmez?",
        .options = {"const olarak tanımlanan x'e atama yapılamaz", "int türü const olamaz", "Fonksiyon parametreleri asla değiştirilemez", "x tanımsızdır"},
        .acceptedAnswers = {"a"},
        .explanation = "const nitelikli bir referansa değer atamak derleme hatasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1179, .topicId = 49,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "const int& parametresi kullanmanın büyük nesneler (std::string, std::vector gibi) için avantajı nedir?",
        .options = {"Kopyalama olmadan (verimli) salt-okunur erişim sağlar", "Nesneyi otomatik olarak küçültür", "Bellek sızıntısını önler", "Fonksiyonun void dönmesini sağlar"},
        .acceptedAnswers = {"a"},
        .explanation = "const T&, kopyalamadan kaçınırken değiştirilmeyi engeller — büyük nesneler için ideal bir birleşimdir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1180, .topicId = 49,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f(const int& x, int& y) {\n    y = x + 1;\n}\nint main() {\n    int a = 5, b = 0;\n    f(a, b);\n    std::cout << a << \" \" << b;\n}\nEkrana ne yazdırılır?",
        .options = {"\"5 6\"", "\"6 6\"", "\"5 0\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "x const referans olduğundan a hiç değişmez (5); y referans olduğundan b, x+1=6 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1181, .topicId = 49,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "const int& r = 10;\nstd::cout << r;\nBu kod derlenir mi?",
        .options = {"Evet, const referans geçici bir değere (10) bağlanabilir", "Hayır, referanslar sadece değişkenlere bağlanabilir", "Hayır, int literal const olamaz", "Evet ama r kullanılamaz"},
        .acceptedAnswers = {"a"},
        .explanation = "const referanslar, ömrü referansın kapsamı süresince uzatılan geçici (temporary) değerlere bağlanabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1182, .topicId = 49,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(const int& x) {\n    std::cout << \"const: \" << x;\n}\nvoid f(int& x) {\n    x = 0;\n    std::cout << \"nonconst: \" << x;\n}\nint main() {\n    int a = 7;\n    f(a);\n    return 0;\n}\nHangi f çağrılır?",
        .options = {"f(int&) çağrılır, \"nonconst: 0\" yazdırılır", "f(const int&) çağrılır, \"const: 7\" yazdırılır", "Belirsizlik hatası (ambiguous)", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "a const olmayan bir lvalue olduğundan, overload çözümlemesi tam eşleşen f(int&) overload'ını tercih eder (const'a nitelik eklemek gerektiren f(const int&)'e göre daha iyi eşleşme).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1183, .topicId = 49,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "const int& parametresi, fonksiyon içinde değiştirilemez.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: const nitelik, referans üzerinden değiştirmeyi engeller.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1184, .topicId = 49,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "const int& bir parametre, normal int& gibi kopyalama yapmadan çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: her ikisi de referans olduğundan kopyalama yapmaz; fark, değiştirilebilirliktedir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1185, .topicId = 49,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "const int& x parametreli bir fonksiyonun içinde x = 5; şeklinde bir atama yapmak geçerlidir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: const nitelikli bir referansa atama yapmak derleme hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1186, .topicId = 49,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "const T& bir parametre, bir literal (örneğin 5 veya \"Merhaba\") ile çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: const referans, geçici değerlere (literallere) bağlanabilir; non-const referans bağlanamaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1187, .topicId = 49,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "const int& parametresi, büyük nesnelerde kopyalama maliyetinden kaçınırken aynı zamanda değişkenin yanlışlıkla değiştirilmesini de engeller.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: const T&, verimlilik ve güvenliği bir arada sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1188, .topicId = 49,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(const int& x, int& y) { y = x; } çağrısında x parametresi, kendisi (a) değiştirilerek kullanılabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: x const referans olduğundan sadece okunabilir, fonksiyon içinde değiştirilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1189, .topicId = 49,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "const int& x parametresi, fonksiyon içinde değiştirilemez çünkü _____ olarak tanımlanmıştır (İngilizce anahtar kelime).",
        .acceptedAnswers = {"const"},
        .explanation = "const anahtar kelimesi, referansın salt-okunur olduğunu belirtir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1190, .topicId = 49,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(const int& x) {\n    std::cout << x;\n}\nint main() {\n    f(42);\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"42"},
        .explanation = "const referans literale bağlanabildiğinden 42 doğrudan yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1191, .topicId = 49,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "const std::string& parametresi, büyük bir string'i kopyalamadan okumayı sağlar; buradaki const anahtar kelimesi, parametrenin fonksiyon içinde _____ olduğunu belirtir (Türkçe kelime).",
        .acceptedAnswers = {"değiştirilemez", "degistirilemez"},
        .explanation = "const, parametrenin salt-okunur (değiştirilemez) olduğunu belirtir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1192, .topicId = 49,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(const int& x) {\n    x = x + 1;\n}\nBu kod derlenmez çünkü const olarak tanımlanan bir referansa _____ yapılamaz (Türkçe kelime, isim hali).",
        .acceptedAnswers = {"atama"},
        .explanation = "const bir referansa atama yapmak derleme hatasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1193, .topicId = 49,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "const int& r = 5;\nBurada r, kalıcı olmayan (geçici) bir değere bağlanabilir çünkü _____ referanslar, geçici değerlerin ömrünü referansın kapsamı boyunca uzatır (İngilizce anahtar kelime).",
        .acceptedAnswers = {"const"},
        .explanation = "const referanslar, geçici (temporary) değerlere bağlanıp onların ömrünü uzatabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1194, .topicId = 49,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(const int& x, int& y) {\n    y = x * 2;\n}\nint main() {\n    int a = 4, b = 0;\n    f(a, b);\n    std::cout << b;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "y referans olduğundan b, x*2=8 olur (a const referans olduğundan hiç değişmez).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1195, .topicId = 49,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir(const std::string& s) {\n    _____\n}\nint main() {\n    yazdir(\"Merhaba Dunya\");\n    return 0;\n}\nyazdir fonksiyonunun gövdesini (s'i ekrana yazdıran satırı) tamamlayın.",
        .acceptedAnswers = {"std::cout << s;"},
        .explanation = "const referans, sadece okumak için kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1196, .topicId = 49,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nint main() {\n    int sayi = 7;\n    std::cout << ikiKatiniGoster(sayi);\n    return 0;\n}\nint ikiKatiniGoster fonksiyonunu, parametreyi const referans olarak alıp iki katını döndürecek şekilde (gövdesiyle) yazın.",
        .acceptedAnswers = {"int ikiKatiniGoster(const int& x) { return x * 2; }"},
        .explanation = "Parametre const referans olarak alınır, sadece okunur ve iki katı döndürülür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1197, .topicId = 49,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void f(const int& x) {\n    std::cout << x * 3;\n}\nint main() {\n    f(5);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"15"},
        .explanation = "x, 5'e bağlanan const bir referanstır: 5*3=15.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1198, .topicId = 49,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void f(const int& x, int& y) {\n    y = x + y;\n}\nint main() {\n    int a = 10, b = 5;\n    f(a, b);\n    std::cout << a << \" \" << b;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10 15"},
        .explanation = "a const referans olduğundan hiç değişmez (10); y referans olduğundan b, x+y=10+5=15 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1199, .topicId = 49,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid f(const int& x) {\n    x = x + 1;\n    std::cout << x;\n}\nint main() {\n    f(5);\n    return 0;\n}\n\nBu kod derlenmez çünkü const olarak tanımlanan x referansına atama yapılamaz. Hatalı satırı, x'i değiştirmek yerine sonuc adlı yeni bir yerel değişkende x+1 değerini hesaplayan haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"int sonuc = x + 1;"},
        .explanation = "const referansa atama yapılamaz; bunun yerine ayrı bir yerel değişkende hesaplama yapılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1200, .topicId = 49,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid f(const std::string& s) {\n    s += \"!\";\n    std::cout << s;\n}\nint main() {\n    f(\"Merhaba\");\n    return 0;\n}\n\nBu kod derlenmez çünkü const std::string& referansına += ile atama yapılamaz. Hatalı satırı, s'i değiştirmek yerine yeni bir yerel değişkende (sonuc adlı) s + \"!\" değerini hesaplayan haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"std::string sonuc = s + \"!\";"},
        .explanation = "const referansa += ile atama yapmak da bir atama işlemidir ve derleme hatası verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1201, .topicId = 49,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid f(const int& x) {\n    x++;\n    std::cout << x;\n}\nint main() {\n    int a = 9;\n    f(a);\n    return 0;\n}\n\nProgramcı x'i doğrudan artırmaya (x++;) çalışmış ama x const referans olduğundan bu satır derlenmez. Hatalı x++; satırını, x'i değiştirmeden bir fazlasını (x + 1) ekrana yazdıran tek bir satırla değiştirin.",
        .acceptedAnswers = {"std::cout << x + 1;"},
        .explanation = "const referans değiştirilemez; bunun yerine x + 1 ifadesi doğrudan yazdırılabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1202, .topicId = 49,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, const referans parametreli bir fonksiyon kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"void yazdir(const std::string& s) {\n    std::cout << s;\n}", "yazdir(\"Merhaba\");\n    return 0;\n}", "int main() {"},
        .acceptedAnswers = {"1 3 2"},
        .explanation = "Fonksiyon tanımı (1), main açılışı (3), çağrı ve kapanış (2): sıra 1 3 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1203, .topicId = 49,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir std::string'i const referans parametre olarak alıp ekrana yazdıran bir fonksiyon yazın; main() içinde bir string literal ile çağırın.",
        .acceptedAnswers = {"const", "&", "cout"},
        .explanation = "Parametre const std::string& olarak tanımlanmalı ve bir literal ile çağrılabilmelidir.",
        .baseXp = 40,
    });

    // Topic 50: Recursion
    questions.push_back(Question{
        .id = 1204, .topicId = 50,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Recursion (özyineleme) nedir?",
        .options = {"Bir fonksiyonun kendi kendini çağırması", "Bir döngünün sonsuza kadar çalışması", "Bir değişkenin kendi kendini değiştirmesi", "İki fonksiyonun birbirini çağırmadan çalışması"},
        .acceptedAnswers = {"a"},
        .explanation = "Recursion, bir fonksiyonun doğrudan veya dolaylı olarak kendini çağırmasıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1205, .topicId = 50,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir recursive fonksiyonun çağrı yığınını taşırmasını (stack overflow) önlemek için ne gereklidir?",
        .options = {"Ulaşılabilir bir taban durum (base case)", "Bir for döngüsü", "Bir global değişken", "Bir sınıf tanımı"},
        .acceptedAnswers = {"a"},
        .explanation = "Taban durum, özyinelemenin sonlanmasını sağlayan koşuldur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1206, .topicId = 50,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int f(int n) {\n    if (n == 0) return 0;\n    return n + f(n - 1);\n}\nf(3) çağrısı hangi değeri döndürür?",
        .options = {"6", "3", "0", "9"},
        .acceptedAnswers = {"a"},
        .explanation = "3 + 2 + 1 + 0 = 6.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1207, .topicId = 50,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int f(int n) {\n    return n + f(n - 1);\n}\n(taban durum yok) f(3) çağrısı ne olur?",
        .options = {"Çağrı yığını taşana (stack overflow) kadar sonsuz özyinelemeye girer", "Sonsuz döngüye girer ama çökmez", "6 değerini döndürür", "Derleme hatası verir"},
        .acceptedAnswers = {"a"},
        .explanation = "Taban durumu olmadığından n hiçbir zaman durmaz ve çağrı yığını taşana kadar özyineleme sürer.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1208, .topicId = 50,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyon kendini çağırdığında (recursive çağrı), her çağrı için ne oluşturulur?",
        .options = {"Kendi parametre ve yerel değişkenlerine sahip yeni, bağımsız bir yığın çerçevesi (stack frame)", "Önceki çağrıyla paylaşılan tek bir ortak değişken kümesi", "Hiçbir şey, tüm çağrılar aynı belleği kullanır", "Yeni bir thread"},
        .acceptedAnswers = {"a"},
        .explanation = "Her çağrı, kendine özgü parametre ve yerel değişkenlere sahip bağımsız bir stack frame alır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1209, .topicId = 50,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int fib(int n) {\n    if (n <= 1) return n;\n    return fib(n - 1) + fib(n - 2);\n}\nfib(4) çağrısı hangi değeri döndürür?",
        .options = {"3", "4", "5", "2"},
        .acceptedAnswers = {"a"},
        .explanation = "fib(0)=0, fib(1)=1, fib(2)=1, fib(3)=2, fib(4)=fib(3)+fib(2)=2+1=3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1210, .topicId = 50,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int n) {\n    if (n == 5) return 0;\n    return n + f(n + 1);\n}\nf(2) çağrısı ne olur?",
        .options = {"9", "0", "Sonsuz özyineleme (taban duruma hiç ulaşılamaz)", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "n, 2'den başlayıp artarak 5'e ulaşır (taban durum): 2+3+4+0=9.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1211, .topicId = 50,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int n) {\n    if (n == 0) return 1;\n    return n * f(n - 2);\n}\nf(3) çağrısı ne olur?",
        .options = {"Stack overflow oluşur çünkü n hiçbir zaman tam olarak 0 olmaz (hep tek sayı kalır)", "3 döndürür", "1 döndürür", "Derleme hatası verir"},
        .acceptedAnswers = {"a"},
        .explanation = "n=3'ten başlayıp 2'şer azalınca 3,1,-1,-3,... hep tek sayı kalır; taban durum olan n==0'a hiçbir zaman ulaşılamaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1212, .topicId = 50,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Recursion, bir fonksiyonun doğrudan veya dolaylı olarak kendini çağırmasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: bu, recursion'ın tanımıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1213, .topicId = 50,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Taban durumu (base case) olmayan bir recursive fonksiyon, güvenli bir şekilde sonsuza kadar çalışabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: taban durumu olmayan bir fonksiyon, çağrı yığınını taşırıp (stack overflow) çöker.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1214, .topicId = 50,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Taban duruma ulaşamayan bir recursive fonksiyon, sonsuz bir while döngüsü gibi güvenle çalışmaya devam eder, sadece daha yavaştır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: her çağrı çağrı yığınında yer kapladığından, sonunda yığın taşar ve program çöker; bu bir while döngüsünden farklıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1215, .topicId = 50,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Her recursive çağrı, kendi bağımsız yerel değişken ve parametre kopyasına sahiptir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: her çağrı kendi stack frame'ine sahiptir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1216, .topicId = 50,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int f(int n) { if (n == 0) return 0; return n + f(n - 1); }\nf(-1) çağrısı taban duruma (n==0) hiçbir zaman ulaşamaz çünkü n azalarak sıfırdan uzaklaşır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: n, -1'den başlayıp azaldıkça (-2, -3, ...) hiçbir zaman 0'a ulaşmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1217, .topicId = 50,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir recursive fonksiyonun taban durumu, her zaman n == 0 şeklinde olmalıdır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: taban durum, probleme uygun herhangi bir ulaşılabilir koşul olabilir (örneğin n == 5).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1218, .topicId = 50,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyonun kendi kendini çağırmasına _____ denir (İngilizce terim).",
        .acceptedAnswers = {"recursion"},
        .explanation = "Bu kavrama recursion (özyineleme) denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1219, .topicId = 50,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Recursive bir fonksiyonun sonsuza gitmesini önleyen, ulaşılabilir durdurma koşuluna _____ _____ denir (İngilizce iki kelime).",
        .acceptedAnswers = {"base case"},
        .explanation = "Bu koşula base case (taban durum) denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1220, .topicId = 50,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int f(int n) {\n    if (n == 0) return 1;\n    return n * f(n - 1);\n}\nf(4) çağrısı _____ değerini döndürür (bu, 4 faktöriyeldir).",
        .acceptedAnswers = {"24"},
        .explanation = "4*3*2*1*1=24.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1221, .topicId = 50,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Taban durumu hiç sağlanmayan bir recursive fonksiyon, sonunda çağrı yığını (call stack) dolarak _____ _____ hatasıyla çöker (İngilizce iki kelime, örn. 'stack overflow').",
        .acceptedAnswers = {"stack overflow"},
        .explanation = "Bu hataya stack overflow (yığın taşması) denir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1222, .topicId = 50,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int f(int n) {\n    if (n == 0) return 0;\n    return f(n - 1) + n;\n}\nf(5) çağrısı _____ değerini döndürür.",
        .acceptedAnswers = {"15"},
        .explanation = "5+4+3+2+1+0=15.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1223, .topicId = 50,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Her recursive çağrı, önceki çağrılarla paylaşılmayan, kendine özgü bağımsız bir _____ _____ (stack frame) oluşturur (İngilizce iki kelime).",
        .acceptedAnswers = {"stack frame"},
        .explanation = "Her çağrı kendi stack frame'ine sahiptir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1224, .topicId = 50,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int faktoriyel(int n) {\n    _____\n}\nint main() {\n    std::cout << faktoriyel(5);\n    return 0;\n}\nfaktoriyel fonksiyonunun gövdesini (taban durum ve recursive adım dahil) tamamlayın.",
        .acceptedAnswers = {"if (n == 0) return 1; return n * faktoriyel(n - 1);"},
        .explanation = "Taban durum n==0 için 1 döner; aksi halde n * faktoriyel(n-1) hesaplanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1225, .topicId = 50,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int topla(int n) {\n    if (n == 0) return 0;\n    _____\n}\nint main() {\n    std::cout << topla(4);\n    return 0;\n}\ntopla fonksiyonunun recursive adımını (n ile topla(n-1) toplamını döndüren satırı) tamamlayın.",
        .acceptedAnswers = {"return n + topla(n - 1);"},
        .explanation = "Recursive adım, n'i topla(n-1)'in sonucuna ekler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1226, .topicId = 50,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int f(int n) {\n    if (n == 0) return 1;\n    return n * f(n - 1);\n}\nint main() {\n    std::cout << f(4);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"24"},
        .explanation = "4! = 4*3*2*1 = 24.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1227, .topicId = 50,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int f(int n) {\n    if (n <= 1) return n;\n    return f(n - 1) + f(n - 2);\n}\nint main() {\n    std::cout << f(6);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"8"},
        .explanation = "Fibonacci dizisi: 0,1,1,2,3,5,8 -> f(6)=8.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1228, .topicId = 50,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint f(int n) {\n    return n * f(n - 1);\n}\nint main() {\n    std::cout << f(5);\n    return 0;\n}\n\nBu fonksiyonun taban durumu (base case) yok, bu yüzden f(5) çağrısı sonsuz özyinelemeye girip çağrı yığınını taşırır (stack overflow). Fonksiyonun ilk satırını, n==0 olduğunda 1 döndüren bir taban durum ekleyerek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (n == 0) return 1;"},
        .explanation = "Taban durum eklenmeden özyineleme hiçbir zaman durmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1229, .topicId = 50,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint f(int n) {\n    if (n == 0) return 1;\n    return n * f(n - 2);\n}\nint main() {\n    std::cout << f(5);\n    return 0;\n}\n\nBu kod stack overflow ile çöker çünkü n tek sayılarla (5, 3, 1, -1, -3, ...) azalır ve taban durum olan n==0'a hiçbir zaman ulaşılamaz. Taban durumunu, hem çift hem tek n değerleri için çalışacak şekilde (n <= 0 koşuluyla) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (n <= 0) return 1;"},
        .explanation = "n <= 0 koşulu, n'in tek ya da çift olmasından bağımsız olarak taban duruma ulaşılmasını garanti eder.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1230, .topicId = 50,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint geriSay(int n) {\n    std::cout << n << \" \";\n    geriSay(n - 1);\n}\nint main() {\n    geriSay(3);\n    return 0;\n}\n\nBu fonksiyonun taban durumu yok, bu yüzden n eksiye giderek sonsuz özyinelemeye girip çağrı yığınını taşırır. Fonksiyonun ilk satırını, n < 0 olduğunda hemen dönen bir taban durum ekleyerek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (n < 0) return 0;"},
        .explanation = "Taban durum, n negatif olduğunda özyinelemeyi durdurur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1231, .topicId = 50,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, taban durumu olan recursive bir faktoriyel fonksiyonu kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << faktoriyel(4);\n    return 0;\n}", "int faktoriyel(int n) {\n    if (n == 0) return 1;\n    return n * faktoriyel(n - 1);\n}", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Fonksiyon tanımı (2), main açılışı (3), çağrı ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1232, .topicId = 50,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir sayının faktöriyelini, taban durumu (n==0 için 1 döndüren) olan recursive bir fonksiyonla hesaplayıp döndüren bir program yazın; main() içinde çağırıp sonucu yazdırın.",
        .acceptedAnswers = {"if", "return", "faktoriyel", "cout"},
        .explanation = "Fonksiyon bir taban durum ve bir recursive adım içermeli, main() içinde çağrılıp sonuç yazdırılmalıdır.",
        .baseXp = 40,
    });
}
```

- [ ] **Step 2: Add a per-topic minimum-count test**

In `tests/QuestionManagerTests.cpp`, add this new test case right after
`QuestionManager_EveryTopicThirtyOneToFortyHasAtLeastTwentyNineQuestions`
(do not modify that existing test, and do not touch
`QuestionManager_NoDuplicateQuestionIds`, which already scans topics
1-100):

```cpp
TEST_CASE(QuestionManager_EveryTopicFortyOneToFiftyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 41; topicId <= 50; ++topicId) {
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
Expected: `92/92 test(s) passed.` (91 from Task 1's end state + 1 new
test).

Run from `build/`: `ctest -C Debug --output-on-failure`
Expected: 100% pass.

- [ ] **Step 4: Manual verification — topic 43 end-to-end**

Run the app (`./build/Debug/CppMasterConsole.exe`), navigate to the
topic browser, choose Section 5, choose topic 43 ("Değer döndüren
fonksiyon"):

1. Confirm the lesson text prints (matches the `explanation`/`syntax`/
   `exampleCode` written in Task 1) — proving `openTopic`'s content gate
   passes for topic 43 with zero `Application.cpp` changes.
2. Confirm "Konu testi başlıyor (29 soru)." prints.
3. Answer a few questions (any answers), then use `cikis` to return to
   the main menu.
4. Confirm the app returns to the main menu without crashing, and that
   partial XP is awarded.
5. Clean up: `rm -f data/*.txt`.

- [ ] **Step 5: Commit the question content and test changes**

```bash
git add src/QuestionsSection5.cpp tests/QuestionManagerTests.cpp
git commit -m "feat(content): add questions for topics 48-50 (ids 1146-1232), widen coverage tests"
```

- [ ] **Step 6: Update the roadmap**

In `docs/superpowers/roadmap.md`, add a new bullet for Phase 16 under
"Phase order," immediately after the Phase 15 entry, following the
EXACT format Phases 8-15 use
(`**Phase N — name: COMPLETE** (commits \`X..Y\`, ...)`), with the
commit range starting at this phase's PLAN commit (the commit for "Add
design spec for Bölüm 5 İçerik Genişletmesi (phase 16)" or the plan
commit, whichever is the phase's actual first commit) and ending at
this task's final content commit (from Step 5 above). Update the
"Status" section to say Phase 16 is complete and Phase 17 (Section 6
content) starts next.

Then commit:

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 16 complete in roadmap"
```

---

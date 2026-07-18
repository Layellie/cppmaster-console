# Bölüm 8 İçerik Genişletmesi (Phase 19) Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add full lesson content and a 290-question bank for Section 8
(topics 71-80, "İleri nesne yönelimli özellikler"), following the
identical architecture used in Phases 13-18.

**Architecture:** One new `applySection8LessonContent` function in
`src/LessonContentSection8.cpp`, one new `appendSection8Questions`
function in `src/QuestionsSection8.cpp`, both wired into the existing
`LessonManager`/`QuestionManager` constructors after the Phase 18
calls.

**Tech Stack:** C++20, CMake, the project's own minimal test framework
(`TEST_CASE`/`CHECK`).

## Global Constraints

- Ids for this phase's questions: 1813-2102 (10 topics x 29 questions
  each), continuing directly from Phase 18's last id (1812).
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
  actually assembling and compiling — and for any case involving
  execution order, running — the resulting program) to produce the
  correct, intended runtime behavior.
- **Without `virtual`, calling a redefined method through a base
  pointer/reference invokes the BASE class's version (static binding),
  even for a derived object. With `virtual`, the SAME call invokes the
  DERIVED class's version (dynamic dispatch).** Any question tracing
  this MUST be compiled and RUN to confirm actual output.
- **`override` causes a compile error if the marked method's signature
  doesn't actually match any base virtual function.**
- **A class with >=1 pure virtual function (`= 0`) is abstract and
  cannot be instantiated** (compile error); **a derived class must
  override ALL pure virtuals to become concrete**, or it stays abstract
  too (also a compile error to instantiate).
- **`this` is an implicit `ClassName*` pointer to the current object**
  inside a non-static member function; `this->uye` == `uye`.
  **Returning `*this` by reference enables method chaining.**
- **A `static` data member is shared across ALL instances** (not
  per-object); changing it via one object is visible everywhere else.
  Use `static inline` (C++17) for in-class initialization. **A `static`
  member function has no `this` and cannot directly access non-static
  members** (compile error).
- **Operator overloading** lets user types use `+`, `==`, `<<` etc.;
  when a member function, the left operand is the implicit `*this`.
- **A function template's type parameter is deduced from arguments at
  compile time**; the same template can be instantiated for multiple
  different types in one program.
- **`namespace` groups names to avoid collisions**; two different
  namespaces may define the same-named function/variable without
  conflict (unlike unscoped `enum` values in the same scope).
- **`auto` deduces type from its initializer and REQUIRES one** —
  `auto x;` with no initializer is a genuine compile error.
- No `Application.cpp` changes are needed — `openTopic`/`runTopicQuiz`
  already activate any topic generically once it has non-empty lesson
  content and >= 1 question.

---

### Task 1: Section 8 lesson content

**Files:**
- Modify: `src/LessonContent.h` (add one new declaration)
- Create: `src/LessonContentSection8.cpp`
- Modify: `src/LessonManager.cpp` (include already present; add one call)
- Modify: `CMakeLists.txt` (add the new `.cpp` to both the lib and test
  target sources, matching how `LessonContentSection7.cpp` is
  registered)
- Modify: `tests/LessonManagerTests.cpp` (widen two existing tests)

**Interfaces:**
- Produces: `void applySection8LessonContent(std::vector<Lesson>& lessons);`
  writing into `lessons[70]` through `lessons[79]` (topics 71-80).

- [ ] **Step 1: Add the new declaration**

In `src/LessonContent.h`, add this line after the existing
`applySection7LessonContent` declaration (do not remove that one):

```cpp
void applySection8LessonContent(std::vector<Lesson>& lessons);
```

- [ ] **Step 2: Write the lesson content**

Create `src/LessonContentSection8.cpp` with exactly this content:

```cpp
#include "LessonContent.h"

#include "Lesson.h"

void applySection8LessonContent(std::vector<Lesson>& lessons) {
    // Index 70 = topic id 71 (virtual), index 79 = topic id 80 (auto)
    // — same positional convention as
    // applyIntroLessonContent/applySection2-7LessonContent.

    lessons[70].explanation =
        "virtual anahtar kelimesi, bir üye fonksiyonun türetilmiş "
        "sınıflarda yeniden tanımlanabileceğini (override edilebileceğini) "
        "ve çalışma zamanında (runtime) hangi versiyonun çağrılacağının, "
        "pointer'ın veya referansın GERÇEK türüne göre belirlendiğini "
        "(dinamik gönderim/dynamic dispatch) belirtir. virtual olmadan, "
        "taban sınıf pointer'ı üzerinden çağrılan bir fonksiyon her zaman "
        "taban sınıfın kendi versiyonunu çalıştırır (statik bağlama), "
        "nesnenin gerçekte türetilmiş bir tür olup olmadığına "
        "bakılmaksızın.";
    lessons[70].syntax = "virtual donusTuru fonksiyonAdi(parametreler);";
    lessons[70].exampleCode =
        "#include <iostream>\n\n"
        "class Hayvan {\npublic:\n"
        "    virtual void sesCikar() {\n"
        "        std::cout << \"...\";\n"
        "    }\n"
        "};\n\n"
        "class Kopek : public Hayvan {\npublic:\n"
        "    void sesCikar() override {\n"
        "        std::cout << \"Hav!\";\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Hayvan* h = new Kopek();\n"
        "    h->sesCikar();\n"
        "    delete h;\n"
        "    return 0;\n"
        "}";
    lessons[70].lineExplanations = {
        "virtual void sesCikar() { ... } : Hayvan sınıfındaki sesCikar, "
        "virtual olduğundan türetilmiş sınıflarda override edilebilir.",
        "Hayvan* h = new Kopek(); : h, taban sınıf türünde bir pointer "
        "ama gerçekte bir Kopek nesnesini gösteriyor.",
        "h->sesCikar(); : virtual sayesinde, h'nin GERÇEK türüne (Kopek) "
        "göre doğru versiyon (Hav!) çalışır."};
    lessons[70].commonMistakes = {
        "sesCikar() virtual olarak işaretlenmeseydi, h->sesCikar() "
        "çağrısı Hayvan'ın kendi versiyonunu (\"...\") çalıştırırdı, "
        "Kopek'in versiyonunu değil — bu, virtual'ın temel amacıdır "
        "(dinamik gönderim).",
    };

    lessons[71].explanation =
        "override anahtar kelimesi (C++11), bir türetilmiş sınıf "
        "metodunun taban sınıftaki bir virtual fonksiyonu GERÇEKTEN "
        "override ettiğini derleyiciye açıkça belirtir. Eğer override "
        "ile işaretlenen metodun imzası (isim, parametreler, const'luk) "
        "taban sınıftaki hiçbir virtual fonksiyonla TAM olarak "
        "eşleşmiyorsa (örneğin bir yazım hatası varsa), derleyici bunu "
        "bir HATA olarak bildirir — bu, override'ın asıl amacıdır: "
        "yanlışlıkla oluşan (override etmeyen, alakasız yeni bir metot "
        "yaratan) hataları erken yakalamak.";
    lessons[71].syntax = "donusTuru fonksiyonAdi(parametreler) override;";
    lessons[71].exampleCode =
        "#include <iostream>\n\n"
        "class Sekil {\npublic:\n"
        "    virtual void ciz() {\n"
        "        std::cout << \"Sekil\";\n"
        "    }\n"
        "};\n\n"
        "class Daire : public Sekil {\npublic:\n"
        "    void ciz() override {\n"
        "        std::cout << \"Daire\";\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Sekil* s = new Daire();\n"
        "    s->ciz();\n"
        "    delete s;\n"
        "    return 0;\n"
        "}";
    lessons[71].lineExplanations = {
        "void ciz() override { ... } : override, bu metodun Sekil'in "
        "virtual ciz() fonksiyonunu gerçekten override ettiğini garanti "
        "eder."};
    lessons[71].commonMistakes = {
        "Eğer Daire'de yanlışlıkla void Ciz() override { ... } (büyük C "
        "ile) yazılsaydı, bu Sekil'deki ciz() ile eşleşmediğinden "
        "override kullanımı bir DERLEME HATASI verirdi (override "
        "olmadan bu, sessizce alakasız yeni bir metot oluştururdu ve "
        "hata fark edilmezdi).",
    };

    lessons[72].explanation =
        "En az bir saf sanal (pure virtual) fonksiyon içeren bir sınıfa "
        "soyut sınıf (abstract class) denir. Saf sanal fonksiyon, "
        "gövdesi olmayan ve = 0 ile işaretlenen bir virtual "
        "fonksiyondur. Soyut bir sınıftan DOĞRUDAN nesne oluşturulamaz "
        "(derleme hatası). Türetilmiş bir sınıf, somut (instantiate "
        "edilebilir) hale gelmek için taban sınıfın TÜM saf sanal "
        "fonksiyonlarını override etmelidir; aksi halde o da soyut "
        "kalır.";
    lessons[72].syntax = "virtual donusTuru fonksiyonAdi(parametreler) = 0;";
    lessons[72].exampleCode =
        "#include <iostream>\n\n"
        "class Sekil {\npublic:\n"
        "    virtual void ciz() = 0;\n"
        "};\n\n"
        "class Kare : public Sekil {\npublic:\n"
        "    void ciz() override {\n"
        "        std::cout << \"Kare\";\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Kare k;\n"
        "    k.ciz();\n"
        "    return 0;\n"
        "}";
    lessons[72].lineExplanations = {
        "virtual void ciz() = 0; : Sekil, saf sanal bir fonksiyon "
        "içerdiği için soyuttur; doğrudan nesnesi oluşturulamaz.",
        "class Kare : public Sekil { ... } : Kare, ciz()'i override "
        "ederek somut (instantiate edilebilir) hale gelir."};
    lessons[72].commonMistakes = {
        "Sekil s; şeklinde soyut bir sınıftan doğrudan nesne "
        "oluşturmaya çalışmak derleme hatasıdır.",
        "Bir türetilmiş sınıf, taban sınıfın TÜM saf sanal "
        "fonksiyonlarını override etmezse, o da soyut kalır ve nesnesi "
        "oluşturulamaz.",
    };

    lessons[73].explanation =
        "Polimorfizm (çok biçimlilik), aynı taban sınıf pointer'ı/"
        "referansı üzerinden farklı türetilmiş sınıf nesnelerinin, "
        "çağrılan virtual fonksiyonun KENDİ (türetilmiş) versiyonunu "
        "çalıştırmasıdır. Bu, virtual fonksiyonlar ve dinamik gönderim "
        "sayesinde mümkün olur: hangi versiyonun çalışacağı, nesnenin "
        "GERÇEK türüne göre çalışma zamanında belirlenir.";
    lessons[73].syntax =
        "TabanSinif* p = new TuretilmisSinif();\np->virtualFonksiyon();";
    lessons[73].exampleCode =
        "#include <iostream>\n\n"
        "class Hayvan {\npublic:\n"
        "    virtual void sesCikar() {\n"
        "        std::cout << \"...\";\n"
        "    }\n"
        "};\n\n"
        "class Kedi : public Hayvan {\npublic:\n"
        "    void sesCikar() override {\n"
        "        std::cout << \"Miyav\";\n"
        "    }\n"
        "};\n\n"
        "class Kopek : public Hayvan {\npublic:\n"
        "    void sesCikar() override {\n"
        "        std::cout << \"Hav\";\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Hayvan* hayvanlar[2] = {new Kedi(), new Kopek()};\n"
        "    for (int i = 0; i < 2; ++i) {\n"
        "        hayvanlar[i]->sesCikar();\n"
        "    }\n"
        "    delete hayvanlar[0];\n"
        "    delete hayvanlar[1];\n"
        "    return 0;\n"
        "}";
    lessons[73].lineExplanations = {
        "Hayvan* hayvanlar[2] = { ... }; : Aynı taban sınıf pointer "
        "türünde bir dizi, farklı türetilmiş nesneleri tutabilir.",
        "hayvanlar[i]->sesCikar(); : Her çağrı, o elemanın GERÇEK "
        "türüne (Kedi veya Kopek) göre doğru versiyonu çalıştırır."};
    lessons[73].commonMistakes = {
        "sesCikar() virtual olmasaydı, dizideki her eleman için "
        "(gerçek türlerine bakılmaksızın) sadece Hayvan'ın kendi "
        "versiyonu (\"...\") çalışırdı; polimorfizmin çalışması virtual "
        "fonksiyonlara bağlıdır.",
    };

    lessons[74].explanation =
        "this, bir sınıfın (static olmayan) her üye fonksiyonu içinde "
        "örtük olarak var olan, geçerli nesnenin adresini tutan bir "
        "pointer'dır. Türü SinifAdi* şeklindedir. Fonksiyon içinde "
        "this->uye ile uye ifadeleri aynı şeyi ifade eder. *this "
        "ifadesini (referans olarak) döndürmek, metot zincirlemeye "
        "(method chaining) olanak tanır.";
    lessons[74].syntax = "this->uye  veya  return *this;";
    lessons[74].exampleCode =
        "#include <iostream>\n\n"
        "class Sayac {\npublic:\n"
        "    int deger = 0;\n"
        "    Sayac& artir(int miktar) {\n"
        "        this->deger += miktar;\n"
        "        return *this;\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Sayac s;\n"
        "    s.artir(3).artir(5);\n"
        "    std::cout << s.deger;\n"
        "    return 0;\n"
        "}";
    lessons[74].lineExplanations = {
        "this->deger += miktar; : this, geçerli nesnenin adresini "
        "tutar; this->deger, deger üyesiyle aynı şeydir.",
        "return *this; : geçerli nesnenin kendisini (referans olarak) "
        "döndürerek zincirleme çağrıya izin verir.",
        "s.artir(3).artir(5); : artir(3) çağrısı s'yi döndürür, ardından "
        "artir(5) aynı nesne üzerinde tekrar çağrılır: 0+3+5=8."};
    lessons[74].commonMistakes = {
        "this bir pointer olduğundan üyelere erişmek için this.uye "
        "değil this->uye yazılmalıdır (nokta değil ok operatörü).",
    };

    lessons[75].explanation =
        "static bir üye, sınıfın HER nesnesi tarafından değil, sınıfın "
        "KENDİSİ tarafından paylaşılan tek bir kopyaya sahiptir. Bir "
        "nesne üzerinden static üyeyi değiştirmek, o değişikliği "
        "sınıfın TÜM diğer nesneleri (ve doğrudan SinifAdi:: ile "
        "erişimler) için de görünür kılar. static üye fonksiyonları "
        "örtük this pointer'ına sahip DEĞİLDİR ve bu yüzden static "
        "olmayan (her nesneye özel) üyelere doğrudan erişemez.";
    lessons[75].syntax = "static tur uyeAdi = deger;  (sınıf içinde, C++17 static inline ile)";
    lessons[75].exampleCode =
        "#include <iostream>\n\n"
        "class Sayac {\npublic:\n"
        "    static inline int toplamNesne = 0;\n"
        "    Sayac() { toplamNesne++; }\n"
        "};\n\n"
        "int main() {\n"
        "    Sayac s1;\n"
        "    Sayac s2;\n"
        "    Sayac s3;\n"
        "    std::cout << Sayac::toplamNesne;\n"
        "    return 0;\n"
        "}";
    lessons[75].lineExplanations = {
        "static inline int toplamNesne = 0; : toplamNesne, Sayac "
        "sınıfının TÜM nesneleri arasında PAYLAŞILAN tek bir "
        "değişkendir.",
        "Sayac() { toplamNesne++; } : her yeni nesne oluşturulduğunda "
        "paylaşılan sayaç bir artar.",
        "Sayac::toplamNesne : static üyeye sınıf adıyla (nesne olmadan) "
        "da erişilebilir."};
    lessons[75].commonMistakes = {
        "static bir üyenin her nesne için ayrı bir kopyası olduğunu "
        "sanmak yanlıştır; static üye TEK bir paylaşılan kopyadır.",
        "static bir üye fonksiyonu içinden static olmayan bir üyeye "
        "doğrudan erişmeye çalışmak (this olmadığından) derleme "
        "hatasıdır.",
    };

    lessons[76].explanation =
        "C++'ta +, ==, << gibi operatörler, kullanıcı tanımlı türler "
        "(class/struct) için YENİDEN TANIMLANABİLİR (overload "
        "edilebilir). Bir operatör üye fonksiyon olarak overload "
        "edildiğinde, sol taraftaki işlenen örtük this'tir (çağrılan "
        "nesnenin kendisi).";
    lessons[76].syntax = "DonusTuru operator+(const SinifAdi& diger) const { ... }";
    lessons[76].exampleCode =
        "#include <iostream>\n\n"
        "class Nokta {\npublic:\n"
        "    int x, y;\n"
        "    Nokta(int xd, int yd) : x(xd), y(yd) {}\n"
        "    Nokta operator+(const Nokta& diger) const {\n"
        "        return Nokta(x + diger.x, y + diger.y);\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Nokta a(1, 2);\n"
        "    Nokta b(3, 4);\n"
        "    Nokta c = a + b;\n"
        "    std::cout << c.x << \" \" << c.y;\n"
        "    return 0;\n"
        "}";
    lessons[76].lineExplanations = {
        "Nokta operator+(const Nokta& diger) const { ... } : + "
        "operatörü, iki Nokta'yı toplayacak şekilde yeniden tanımlanır.",
        "Nokta c = a + b; : a + b ifadesi, a.operator+(b) çağrısına "
        "karşılık gelir; x'ler ve y'ler ayrı ayrı toplanır."};
    lessons[76].commonMistakes = {
        "operator+ içinde diger.x ve diger.y yerine yanlışlıkla x ve "
        "y'yi (kendi üyelerini) iki kez kullanmak, toplama yerine "
        "ikiye katlama gibi yanlış bir sonuç üretir; diğer nesnenin "
        "üyelerine diger. ön ekiyle erişilmelidir.",
    };

    lessons[77].explanation =
        "Bir template fonksiyon, türden bağımsız (generic) bir "
        "fonksiyon tanımlamanın yoludur; gerçek tür, fonksiyon "
        "çağrıldığında argümanlardan derleme zamanında (compile-time) "
        "otomatik olarak çıkarılır (deduce edilir) ya da açıkça "
        "belirtilebilir. Aynı template, aynı programda birden fazla "
        "farklı türle örneklenebilir (instantiate edilebilir).";
    lessons[77].syntax = "template<typename T>\nT fonksiyonAdi(T a, T b) { ... }";
    lessons[77].exampleCode =
        "#include <iostream>\n\n"
        "template<typename T>\n"
        "T topla(T a, T b) {\n"
        "    return a + b;\n"
        "}\n\n"
        "int main() {\n"
        "    std::cout << topla(3, 4) << \" \" << topla(2.5, 1.5);\n"
        "    return 0;\n"
        "}";
    lessons[77].lineExplanations = {
        "template<typename T> T topla(T a, T b) { ... } : T, çağrıya "
        "göre belirlenecek bir yer tutucu türdür.",
        "topla(3, 4) : T, int olarak çıkarılır, sonuç 7'dir.",
        "topla(2.5, 1.5) : T, double olarak çıkarılır, sonuç 4'tür "
        "(2.5+1.5=4.0, cout 4 olarak basar)."};
    lessons[77].commonMistakes = {
        "Template parametresi T, her çağrıda FARKLI bir türle "
        "örneklenebilir (aynı template kodu int için de double için de "
        "ayrı ayrı derlenir); T'nin tek bir sabit türe bağlı olduğunu "
        "sanmak yanlıştır.",
    };

    lessons[78].explanation =
        "namespace, ilgili isimleri (fonksiyon, değişken, sınıf) bir "
        "araya toplayarak isim çakışmalarını önleyen bir gruplama "
        "mekanizmasıdır. Bir namespace içindeki bir isme "
        "NamespaceAdi::isim şeklinde ya da using namespace NamespaceAdi; "
        "ile erişilebilir. İki farklı namespace, birbirinden bağımsız "
        "olarak AYNI isimde fonksiyon/değişken tanımlayabilir; bu bir "
        "çakışmaya yol açmaz çünkü her biri kendi namespace'inin "
        "kapsamındadır.";
    lessons[78].syntax = "namespace NamespaceAdi {\n    tur isim;\n}";
    lessons[78].exampleCode =
        "#include <iostream>\n\n"
        "namespace Matematik {\n"
        "    int kare(int x) {\n"
        "        return x * x;\n"
        "    }\n"
        "}\n\n"
        "namespace Metin {\n"
        "    int kare(int x) {\n"
        "        return x;\n"
        "    }\n"
        "}\n\n"
        "int main() {\n"
        "    std::cout << Matematik::kare(4) << \" \" << Metin::kare(4);\n"
        "    return 0;\n"
        "}";
    lessons[78].lineExplanations = {
        "namespace Matematik { ... } ve namespace Metin { ... } : aynı "
        "isimli (kare) iki farklı fonksiyon, farklı namespace'lerde "
        "çakışma olmadan bir arada bulunabilir.",
        "Matematik::kare(4) : Matematik namespace'indeki kare çağrılır "
        "(16).",
        "Metin::kare(4) : Metin namespace'indeki kare çağrılır (4)."};
    lessons[78].commonMistakes = {
        "İki namespace'teki aynı isimli fonksiyonlar, ikisi de using "
        "namespace ile aynı anda kapsam açılmışsa (nitelemesiz "
        "çağrıldığında) BELİRSİZLİK (ambiguous) hatasına yol açabilir; "
        "bu durumda NamespaceAdi:: ön eki ile açıkça belirtmek gerekir.",
    };

    lessons[79].explanation =
        "auto anahtar kelimesi, bir değişkenin türünün, ilklendirildiği "
        "(initialize edildiği) ifadeden derleme zamanında otomatik "
        "olarak çıkarılmasını (deduce edilmesini) sağlar. auto ile "
        "tanımlanan bir değişken MUTLAKA bir ilk değerle (initializer) "
        "tanımlanmalıdır; aksi halde derleyici türü çıkaracak hiçbir "
        "bilgiye sahip olmaz (derleme hatası).";
    lessons[79].syntax = "auto degiskenAdi = ifade;";
    lessons[79].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    auto x = 5;\n"
        "    auto y = 3.14;\n"
        "    auto isim = std::string(\"Merhaba\");\n"
        "    std::cout << x << \" \" << y << \" \" << isim;\n"
        "    return 0;\n"
        "}";
    lessons[79].lineExplanations = {
        "auto x = 5; : x'in türü, 5'ten int olarak çıkarılır.",
        "auto y = 3.14; : y'nin türü, 3.14'ten double olarak çıkarılır.",
        "auto isim = std::string(\"Merhaba\"); : isim'in türü "
        "std::string olarak çıkarılır."};
    lessons[79].commonMistakes = {
        "auto degisken; şeklinde bir ilk değer vermeden tanımlamak "
        "derleme hatasıdır; auto'nun türü çıkarabilmesi için mutlaka "
        "bir ilklendirme ifadesi gereklidir.",
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
    applySection6LessonContent(lessons_);
    applySection7LessonContent(lessons_);
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
    applySection7LessonContent(lessons_);
    applySection8LessonContent(lessons_);
}
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/LessonContentSection6.cpp
    src/LessonContentSection7.cpp
```

to:

```cmake
    src/LessonContentSection6.cpp
    src/LessonContentSection7.cpp
    src/LessonContentSection8.cpp
```

- [ ] **Step 5: Extend the content-coverage tests**

In `tests/LessonManagerTests.cpp`, replace:

```cpp
TEST_CASE(LessonManager_TopicsElevenToSeventyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 70; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsElevenToEightyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 80; ++topicId) {
```

(keep the rest of that test's body unchanged). Then replace:

```cpp
TEST_CASE(LessonManager_TopicsSeventyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 71; topicId <= 100; ++topicId) {
```

with:

```cpp
TEST_CASE(LessonManager_TopicsEightyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 81; topicId <= 100; ++topicId) {
```

(keep the rest of that test's body unchanged — there must be exactly
these two content-coverage tests afterward, not three).

- [ ] **Step 6: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `94/94 test(s) passed.` (same count as Phase 18's end state —
this task only renames/widens two existing tests' ranges).

- [ ] **Step 7: Commit**

```bash
git add src/LessonContent.h src/LessonContentSection8.cpp src/LessonManager.cpp CMakeLists.txt tests/LessonManagerTests.cpp
git commit -m "feat(content): add Section 8 lesson content (topics 71-80)"
```

---

### Task 2: Questions for topics 71-74 (ids 1813-1928)

**Files:**
- Modify: `src/QuestionContent.h` (add one new declaration)
- Create: `src/QuestionsSection8.cpp`
- Modify: `src/QuestionManager.cpp` (include, call, bump `reserve()`)
- Modify: `CMakeLists.txt` (add the new `.cpp`)

**Interfaces:**
- Produces: `void appendSection8Questions(std::vector<Question>& questions);`
  — Task 3 and Task 4 append more `questions.push_back(...)` calls to
  this SAME function body (in this same file) for topics 75-77 and
  78-80 respectively. This task only adds topics 71-74 (ids 1813-1928).

- [ ] **Step 1: Add the new declaration**

In `src/QuestionContent.h`, add this line after the existing
`appendSection7Questions` declaration (do not remove that one):

```cpp
void appendSection8Questions(std::vector<Question>& questions);
```

- [ ] **Step 2: Write topics 71-74's questions**

Create `src/QuestionsSection8.cpp` with exactly this content:

```cpp
#include "QuestionContent.h"

#include "Question.h"

void appendSection8Questions(std::vector<Question>& questions) {
    // Topic 71: virtual
    questions.push_back(Question{
        .id = 1813, .topicId = 71,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "virtual anahtar kelimesinin amacı nedir?",
        .options = {"Türetilmiş sınıfların bir fonksiyonu override edebilmesini ve çalışma zamanında doğru versiyonun çağrılmasını sağlamak", "Bir fonksiyonu silmek", "Bir değişkeni sabit yapmak", "Bir sınıfı soyut yapmak"},
        .acceptedAnswers = {"a"},
        .explanation = "virtual, dinamik gönderimi (doğru versiyonun çalışma zamanında seçilmesini) sağlar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1814, .topicId = 71,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\"; }\n};\nclass Kopek : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Hav\"; }\n};\nHayvan* h = new Kopek();\nh->sesCikar();\ndelete h;\nEkrana ne yazdırılır?",
        .options = {"\"Hav\"", "\"...\"", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "virtual sayesinde h'nin gerçek türüne (Kopek) göre doğru versiyon çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1815, .topicId = 71,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "virtual olmayan bir fonksiyon, taban sınıf pointer'ı üzerinden çağrıldığında hangi versiyonu çalıştırır?",
        .options = {"Her zaman taban sınıfın kendi versiyonunu (statik bağlama)", "Her zaman türetilmiş sınıfın versiyonunu", "Rastgele birini", "Derleme hatası verir"},
        .acceptedAnswers = {"a"},
        .explanation = "virtual olmadan statik bağlama kullanılır, her zaman taban sınıfın versiyonu çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1816, .topicId = 71,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Hayvan {\npublic:\n    void sesCikar() { std::cout << \"...\"; }\n};\nclass Kopek : public Hayvan {\npublic:\n    void sesCikar() { std::cout << \"Hav\"; }\n};\nHayvan* h = new Kopek();\nh->sesCikar();\ndelete h;\nEkrana ne yazdırılır (virtual OLMADAN)?",
        .options = {"\"...\"", "\"Hav\"", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "virtual olmadığı için statik bağlama uygulanır, Hayvan'ın kendi versiyonu çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1817, .topicId = 71,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "virtual bir fonksiyonun çalışma zamanında hangi versiyonunun çağrılacağına karar veren şey nedir?",
        .options = {"Pointer'ın/referansın GERÇEK (işaret ettiği) nesnenin türü", "Pointer'ın tanımlandığı tür (statik tür)", "Kodun yazıldığı sıra", "Fonksiyonun adı"},
        .acceptedAnswers = {"a"},
        .explanation = "Dinamik gönderim, nesnenin gerçek türüne göre çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1818, .topicId = 71,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Kopek Hayvan'dan türetilmiştir ve Hayvan::sesCikar() virtual'dır. Kopek k; Hayvan& href = k; href.sesCikar(); çağrısı hangi versiyonu çalıştırır?",
        .options = {"Kopek'in versiyonunu (href'in gerçek türü Kopek olduğundan)", "Hayvan'ın versiyonunu", "İkisini de", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Referanslar da pointer'lar gibi dinamik gönderim sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1819, .topicId = 71,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class A {\npublic:\n    virtual void f() { std::cout << \"A\"; }\n};\nclass B : public A {\npublic:\n    void f() override { std::cout << \"B\"; }\n};\nclass C : public B {\npublic:\n    void f() override { std::cout << \"C\"; }\n};\nA* p = new C();\np->f();\ndelete p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"C\"", "\"A\"", "\"B\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Çok seviyeli kalıtımda dinamik gönderim her zaman en çok türetilmiş override'ı bulur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1820, .topicId = 71,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\"; }\n};\nclass Kopek : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Hav\"; }\n};\nvoid sesCikart(Hayvan& h) {\n    h.sesCikar();\n}\nint main() {\n    Kopek k;\n    sesCikart(k);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"Hav\"", "\"...\"", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "Referans parametre de dinamik gönderim sağlar; k'nin gerçek türü Kopek'tir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1821, .topicId = 71,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "virtual bir fonksiyon, türetilmiş sınıflarda override edilebilir ve çalışma zamanında doğru versiyon çağrılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1822, .topicId = 71,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "virtual olmayan bir fonksiyon, taban sınıf pointer'ı üzerinden çağrıldığında her zaman türetilmiş sınıfın versiyonunu çalıştırır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: statik bağlama nedeniyle taban sınıfın versiyonu çalışır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1823, .topicId = 71,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Dinamik gönderim (dynamic dispatch), hangi fonksiyon versiyonunun çalışacağına çalışma zamanında karar verilmesidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1824, .topicId = 71,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "virtual fonksiyonlarda, çağrılan versiyon pointer'ın TANIMLANDIĞI türe (statik türe) göre belirlenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: gerçek (dinamik) türe göre belirlenir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1825, .topicId = 71,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir referans üzerinden virtual fonksiyon çağırmak da, pointer'da olduğu gibi dinamik gönderim sağlar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1826, .topicId = 71,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Çok seviyeli kalıtımda (A->B->C), virtual bir fonksiyon çağrıldığında her zaman EN ÇOK türetilmiş (en alttaki) override çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1827, .topicId = 71,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir üye fonksiyonun türetilmiş sınıflarda override edilebilmesini ve çalışma zamanında doğru versiyonun seçilmesini sağlamak için _____ anahtar kelimesi kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"virtual"},
        .explanation = "virtual, dinamik gönderimi mümkün kılar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1828, .topicId = 71,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "class Hayvan {\npublic:\n    virtual void f() { std::cout << \"H\"; }\n};\nclass Kopek : public Hayvan {\npublic:\n    void f() override { std::cout << \"K\"; }\n};\nHayvan* h = new Kopek();\nh->f();\ndelete h;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"K"},
        .explanation = "Dinamik gönderim Kopek'in versiyonunu çalıştırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1829, .topicId = 71,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "virtual olmayan bir fonksiyonun taban pointer'ı üzerinden çağrılmasına _____ bağlama denir (Türkçe kelime).",
        .acceptedAnswers = {"statik"},
        .explanation = "Buna statik bağlama denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1830, .topicId = 71,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "virtual fonksiyonlarda çalışma zamanında hangi versiyonun çağrılacağına karar verilmesine _____ gönderim denir (Türkçe kelime).",
        .acceptedAnswers = {"dinamik"},
        .explanation = "Buna dinamik gönderim denir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1831, .topicId = 71,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class A {\npublic:\n    virtual void f() { std::cout << \"A\"; }\n};\nclass B : public A {\npublic:\n    void f() override { std::cout << \"B\"; }\n};\nA* p = new B();\np->f();\ndelete p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"B"},
        .explanation = "Dinamik gönderim B'nin versiyonunu çalıştırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1832, .topicId = 71,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Dinamik gönderimde çağrılacak fonksiyon, pointer'ın GERÇEK (işaret ettiği nesnenin) _____ göre belirlenir (Türkçe kelime, 'tür' anlamında).",
        .acceptedAnswers = {"türüne"},
        .explanation = "Nesnenin gerçek türüne göre belirlenir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1833, .topicId = 71,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Hayvan {\npublic:\n    _____ void sesCikar() { std::cout << \"...\"; }\n};\nHayvan* h = new Kopek();\nh->sesCikar();\nsesCikar()'ın türetilmiş sınıflarda override edilebilmesi için gereken anahtar kelimeyi eklenmiş haliyle satırı tamamlayın.",
        .acceptedAnswers = {"virtual"},
        .explanation = "virtual, override edilebilirliği sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1834, .topicId = 71,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\"; }\n};\nclass Kopek : public Hayvan {\npublic:\n    _____\n};\nHayvan* h = new Kopek();\nh->sesCikar();\nKopek'in sesCikar()'ı override eden metodunu (\"Hav\" yazdıran) tanımlayan satırı yazın.",
        .acceptedAnswers = {"void sesCikar() override { std::cout << \"Hav\"; }"},
        .explanation = "override, Hayvan'ın virtual fonksiyonunu override eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1835, .topicId = 71,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\"; }\n};\nclass Kedi : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Miyav\"; }\n};\nint main() {\n    Hayvan* h = new Kedi();\n    h->sesCikar();\n    delete h;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Miyav"},
        .explanation = "Dinamik gönderim Kedi'nin versiyonunu çalıştırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1836, .topicId = 71,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class A {\npublic:\n    virtual void f() { std::cout << \"A\"; }\n};\nclass B : public A {\npublic:\n    void f() override { std::cout << \"B\"; }\n};\nint main() {\n    A* arr[2] = {new A(), new B()};\n    for (int i = 0; i < 2; ++i) {\n        arr[i]->f();\n    }\n    delete arr[0];\n    delete arr[1];\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"AB"},
        .explanation = "arr[0] bir A nesnesi (A yazdırır), arr[1] bir B nesnesi (B yazdırır).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1837, .topicId = 71,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nclass Hayvan {\npublic:\n    void sesCikar() { std::cout << \"...\"; }\n};\nclass Kopek : public Hayvan {\npublic:\n    void sesCikar() { std::cout << \"Hav\"; }\n};\nint main() {\n    Hayvan* h = new Kopek();\n    h->sesCikar();\n    delete h;\n    return 0;\n}\n\nProgramcı \"Hav\" yazdırılmasını bekliyor ama sesCikar() virtual olmadığından statik bağlama nedeniyle \"...\" yazdırılır. Hayvan sınıfındaki sesCikar() tanımını, virtual eklenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"virtual void sesCikar() { std::cout << \"...\"; }"},
        .explanation = "virtual eklenmeden dinamik gönderim çalışmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1838, .topicId = 71,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nclass A {\npublic:\n    virtual void f() { std::cout << \"A\"; }\n};\nclass B : public A {\npublic:\n    void f() { std::cout << \"B\"; }\n};\nclass C : public B {\npublic:\n    void g() { std::cout << \"C\"; }\n};\nint main() {\n    A* p = new C();\n    p->f();\n    delete p;\n    return 0;\n}\n\nBu kod C'nin gerçek örneği için B'nin f() override'ını çalıştırır (\"B\" yazdırır) çünkü C, f()'i kendi başına override etmemiş, sadece B'den devralmıştır - bu doğru davranıştır. Ancak programcı \"C\" yazdırılmasını bekliyorsa, C sınıfına eklenmesi gereken f() override'ını yazın.",
        .acceptedAnswers = {"void f() override { std::cout << \"C\"; }"},
        .explanation = "C'nin kendi f() override'ı olmadığı için B'nin versiyonu miras kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1839, .topicId = 71,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\" }\n};\n\nProgramcı std::cout << \"...\" satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"virtual void sesCikar() { std::cout << \"...\"; }"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1840, .topicId = 71,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, virtual fonksiyon kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"h->sesCikar();\n    delete h;\n    return 0;\n}", "class Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\"; }\n};\nclass Kopek : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Hav\"; }\n};", "int main() {\n    Hayvan* h = new Kopek();"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class tanımları (2), main+nesne (3), çağrı+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1841, .topicId = 71,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Hayvan adlı bir taban sınıf ve virtual bir sesCikar() metodu tanımlayın; ondan türetilen Kopek adlı bir sınıfta sesCikar()'ı override edip main() içinde taban sınıf pointer'ı üzerinden çağırarak dinamik gönderimi gösterin.",
        .acceptedAnswers = {"virtual", "override", "cout"},
        .explanation = "Taban sınıf pointer'ı üzerinden çağrı, türetilmiş sınıfın versiyonunu çalıştırmalıdır.",
        .baseXp = 40,
    });

    // Topic 72: override
    questions.push_back(Question{
        .id = 1842, .topicId = 72,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "override anahtar kelimesi ne zaman geldi?",
        .options = {"C++11", "C++98", "C++20", "C++03"},
        .acceptedAnswers = {"a"},
        .explanation = "override, C++11 ile geldi.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1843, .topicId = 72,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "override anahtar kelimesinin amacı nedir?",
        .options = {"Bir metodun taban sınıftaki bir virtual fonksiyonu gerçekten override ettiğini derleyiciye doğrulatmak", "Bir fonksiyonu virtual yapmak", "Bir sınıfı soyut yapmak", "Bir metodu silmek"},
        .acceptedAnswers = {"a"},
        .explanation = "override, gerçek bir override olduğunu derleyiciye doğrulatır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1844, .topicId = 72,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() { }\n};\nclass Daire : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Daire\"; }\n};\nBu kod derlenir mi?",
        .options = {"Evet, ciz() Sekil'deki virtual ciz()'i doğru şekilde override eder", "Hayır, override anahtar kelimesi geçersizdir", "Hayır, Sekil'de ciz() olmalı", "Evet ama sadece const olarak"},
        .acceptedAnswers = {"a"},
        .explanation = "İmza tam olarak eşleştiğinden override geçerlidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1845, .topicId = 72,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() { }\n};\nclass Daire : public Sekil {\npublic:\n    void Ciz() override { std::cout << \"Daire\"; }\n};\nBu kod derlenir mi (büyük C ile Ciz)?",
        .options = {"Hayır, Ciz(), Sekil'deki hiçbir virtual fonksiyonla eşleşmediğinden derleme hatası oluşur", "Evet, büyük/küçük harf önemli değildir", "Evet, override her zaman geçerlidir", "Hayır, Sekil sınıfı hatalıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "C++ büyük/küçük harf duyarlıdır; Ciz != ciz, override başarısız olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1846, .topicId = 72,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "override kullanmadan yanlışlıkla farklı bir imzayla \"override etmeye çalışmak\" (örneğin yazım hatası) ne olur?",
        .options = {"Sessizce alakasız yeni bir metot oluşturulur, hata fark edilmeyebilir", "Her zaman derleme hatası verir", "Program çöker", "Otomatik olarak düzeltilir"},
        .acceptedAnswers = {"a"},
        .explanation = "override olmadan, yazım hatası sessizce yeni bir metot oluşturur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1847, .topicId = 72,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "override kullanmak zorunlu mudur?",
        .options = {"Hayır, isteğe bağlıdır ama hataları erken yakalamak için önerilir", "Evet, her override eden metotta zorunludur", "Evet, aksi halde metot virtual olmaz", "Hayır, hiçbir zaman kullanılmamalıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "override isteğe bağlıdır ama iyi bir alışkanlıktır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1848, .topicId = 72,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz(int renk) { }\n};\nclass Daire : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Daire\"; }\n};\nBu kod derlenir mi (parametre sayısı farklı)?",
        .options = {"Hayır, ciz()'in imzası (parametre listesi) Sekil'deki ciz(int)'ten farklı olduğundan derleme hatası oluşur", "Evet, override parametre sayısını göz ardı eder", "Evet, Daire kendi ciz()'ini tanımlayabilir", "Hayır, Sekil sınıfı hatalıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "İmza (parametre listesi dahil) tam eşleşmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1849, .topicId = 72,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() const { }\n};\nclass Daire : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Daire\"; }\n};\nBu kod derlenir mi (const eksik)?",
        .options = {"Hayır, ciz()'in const niteliği Sekil'deki ciz() const'tan farklı olduğundan derleme hatası oluşur", "Evet, const fark etmez", "Evet, Daire const olmayan bir versiyon tanımlayabilir", "Hayır, Sekil sınıfı hatalıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "const niteliği de imzanın bir parçasıdır ve eşleşmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1850, .topicId = 72,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "override, bir metodun taban sınıftaki bir virtual fonksiyonu gerçekten override ettiğini doğrular.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1851, .topicId = 72,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "override kullanmak, C++'ta zorunludur; olmadan program derlenmez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: override isteğe bağlıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1852, .topicId = 72,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "override ile işaretlenen bir metodun imzası taban sınıftaki hiçbir virtual fonksiyonla eşleşmiyorsa derleme hatası oluşur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1853, .topicId = 72,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "override kullanılmadan yapılan bir imza hatası, derleyici tarafından her zaman fark edilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: override olmadan bu hata sessizce yeni bir metot olarak derlenir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1854, .topicId = 72,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "override, bir metodun const niteliğinin de taban sınıftaki virtual fonksiyonla eşleşmesini gerektirir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1855, .topicId = 72,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "override, parametre sayısı farklı olan bir metotta da sorunsuz çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: parametre listesi de eşleşmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1856, .topicId = 72,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir metodun taban sınıftaki bir virtual fonksiyonu gerçekten override ettiğini derleyiciye doğrulatmak için _____ anahtar kelimesi kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"override"},
        .explanation = "override anahtar kelimesi bu doğrulamayı yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1857, .topicId = 72,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "override, C++_____ standardıyla gelmiştir (bir sayı).",
        .acceptedAnswers = {"11"},
        .explanation = "override, C++11 ile geldi.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1858, .topicId = 72,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "override ile işaretlenen bir metodun imzası eşleşmiyorsa, bu bir _____ verir (Türkçe kelime).",
        .acceptedAnswers = {"hata", "derleme hatası"},
        .explanation = "Bu bir derleme hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1859, .topicId = 72,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() { }\n};\nclass Daire : public Sekil {\npublic:\n    void Ciz() override { }\n};\nBu kod _____ verir çünkü Ciz, ciz ile eşleşmiyor (Türkçe kelime).",
        .acceptedAnswers = {"hata", "derleme hatası"},
        .explanation = "İsimler tam eşleşmediğinden derleme hatası oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1860, .topicId = 72,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "override kullanmak isteğe bağlıdır ama hataları erken yakalamak için _____ bir alışkanlıktır (Türkçe kelime).",
        .acceptedAnswers = {"iyi"},
        .explanation = "override kullanmak iyi bir alışkanlıktır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1861, .topicId = 72,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "override, parametre listesi VE _____ niteliğinin de taban sınıftaki virtual fonksiyonla eşleşmesini gerektirir (İngilizce kelime).",
        .acceptedAnswers = {"const"},
        .explanation = "const niteliği de imzanın bir parçasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1862, .topicId = 72,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() { }\n};\nclass Daire : public Sekil {\npublic:\n    _____\n};\nciz()'i override eden, \"Daire\" yazdıran bir metot tanımlayan satırı yazın.",
        .acceptedAnswers = {"void ciz() override { std::cout << \"Daire\"; }"},
        .explanation = "override ile ciz() gerçekten override edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1863, .topicId = 72,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    _____\n};\nclass Daire : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Daire\"; }\n};\nDaire'nin ciz()'i override edebilmesi için Sekil'e eklenmesi gereken virtual ciz() tanımını yazın.",
        .acceptedAnswers = {"virtual void ciz() { }"},
        .explanation = "Sekil'de ciz() virtual olarak tanımlanmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1864, .topicId = 72,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() { std::cout << \"Sekil\"; }\n};\nclass Ucgen : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Ucgen\"; }\n};\nint main() {\n    Sekil* s = new Ucgen();\n    s->ciz();\n    delete s;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Ucgen"},
        .explanation = "Dinamik gönderim Ucgen'in versiyonunu çalıştırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1865, .topicId = 72,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() { std::cout << \"S\"; }\n    virtual void sil() { std::cout << \"s\"; }\n};\nclass Kare : public Sekil {\npublic:\n    void ciz() override { std::cout << \"K\"; }\n};\nint main() {\n    Sekil* s = new Kare();\n    s->ciz();\n    s->sil();\n    delete s;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Ks"},
        .explanation = "ciz() Kare tarafından override edilmiş (K); sil() override edilmediğinden Sekil'in versiyonu kalıtılır (s).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1866, .topicId = 72,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Sekil {\npublic:\n    virtual void ciz() { }\n};\nclass Daire : public Sekil {\npublic:\n    void ciz(int x) override { std::cout << x; }\n};\n\nBu kod derlenmez çünkü ciz(int x), Sekil'deki ciz() (parametresiz) ile eşleşmiyor. Daire'deki hatalı satırı, doğru imzayla (parametresiz) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void ciz() override { }"},
        .explanation = "İmza, taban sınıftaki virtual fonksiyonla tam eşleşmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1867, .topicId = 72,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Sekil {\npublic:\n    virtual void ciz() const { }\n};\nclass Daire : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Daire\"; }\n};\n\nBu kod derlenmez çünkü Daire'nin ciz()'i const değil ama Sekil'deki ciz() const'tur; const niteliği eşleşmediğinden override başarısız olur. Daire'deki hatalı satırı, const eklenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"void ciz() const override { std::cout << \"Daire\"; }"},
        .explanation = "const niteliği eşleşmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1868, .topicId = 72,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Sekil {\npublic:\n    virtual void ciz() { }\n};\nclass Daire : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Daire\" }\n};\n\nProgramcı std::cout << \"Daire\" satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"void ciz() override { std::cout << \"Daire\"; }"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1869, .topicId = 72,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, override kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"s->ciz();\n    delete s;\n    return 0;\n}", "class Sekil {\npublic:\n    virtual void ciz() { }\n};\nclass Daire : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Daire\"; }\n};", "int main() {\n    Sekil* s = new Daire();"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class tanımları (2), main+nesne (3), çağrı+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1870, .topicId = 72,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "virtual bir ciz() metodu olan Sekil adlı bir taban sınıf ve ondan türetilen, ciz()'i override anahtar kelimesiyle override eden Daire adlı bir sınıf tanımlayın; main() içinde taban sınıf pointer'ı üzerinden çağırın.",
        .acceptedAnswers = {"virtual", "override", "cout"},
        .explanation = "Daire'nin ciz() metodu override ile işaretlenmelidir.",
        .baseXp = 40,
    });

    // Topic 73: Soyut sınıf
    questions.push_back(Question{
        .id = 1871, .topicId = 73,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir sınıfı soyut (abstract) yapan şey nedir?",
        .options = {"En az bir saf sanal (pure virtual) fonksiyon içermesi", "private bir üyesi olması", "Constructor'ı olmaması", "static bir üyesi olması"},
        .acceptedAnswers = {"a"},
        .explanation = "En az bir saf sanal fonksiyon içeren sınıf soyuttur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1872, .topicId = 73,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Saf sanal fonksiyon nasıl tanımlanır?",
        .options = {"virtual donusTuru f() = 0;", "virtual donusTuru f() {}", "abstract donusTuru f();", "donusTuru f() = pure;"},
        .acceptedAnswers = {"a"},
        .explanation = "Saf sanal fonksiyon = 0 ile işaretlenir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1873, .topicId = 73,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() = 0;\n};\nSekil s;\nBu kod derlenir mi?",
        .options = {"Hayır, Sekil soyut olduğundan doğrudan nesnesi oluşturulamaz", "Evet, s bir Sekil nesnesi olur", "Evet ama ciz() çağrılamaz", "Hayır, Sekil sınıfı geçersiz tanımlanmış"},
        .acceptedAnswers = {"a"},
        .explanation = "Soyut sınıflar doğrudan instantiate edilemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1874, .topicId = 73,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() = 0;\n};\nclass Kare : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Kare\"; }\n};\nKare k;\nBu kod derlenir mi?",
        .options = {"Evet, Kare ciz()'i override ettiğinden somut (instantiate edilebilir) hale gelir", "Hayır, Kare de soyut kalır", "Hayır, Kare Sekil'den türetilemez", "Evet ama Kare de soyuttur"},
        .acceptedAnswers = {"a"},
        .explanation = "Tüm saf sanal fonksiyonlar override edildiğinden Kare somuttur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1875, .topicId = 73,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() = 0;\n    virtual void doldur() = 0;\n};\nclass Kare : public Sekil {\npublic:\n    void ciz() override { }\n};\nKare k;\nBu kod derlenir mi (doldur override edilmemiş)?",
        .options = {"Hayır, Kare doldur()'u override etmediğinden hala soyuttur", "Evet, ciz() override edildiği için yeterlidir", "Evet, doldur() otomatik atlanır", "Hayır, Sekil sınıfı geçersizdir"},
        .acceptedAnswers = {"a"},
        .explanation = "TÜM saf sanal fonksiyonlar override edilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1876, .topicId = 73,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Soyut bir sınıf, taban sınıf pointer'ı olarak kullanılabilir mi (örneğin Sekil* p = new Kare();)?",
        .options = {"Evet, soyut sınıflar pointer/referans türü olarak kullanılabilir, sadece DOĞRUDAN nesnesi oluşturulamaz", "Hayır, soyut sınıflar hiçbir şekilde kullanılamaz", "Hayır, pointer türü olarak da kullanılamaz", "Evet ama sadece const pointer olarak"},
        .acceptedAnswers = {"a"},
        .explanation = "Soyut sınıflar pointer/referans türü olarak kullanılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1877, .topicId = 73,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() = 0;\n};\nclass Sekil3D : public Sekil {\npublic:\n    virtual void derinlikGoster() = 0;\n};\nclass Kup : public Sekil3D {\npublic:\n    void ciz() override { std::cout << \"c\"; }\n    void derinlikGoster() override { std::cout << \"d\"; }\n};\nKup k;\nk.ciz();\nk.derinlikGoster();\nBu kod derlenir mi?",
        .options = {"Evet, Kup her iki saf sanal fonksiyonu da override ettiğinden somuttur", "Hayır, Kup hala soyuttur", "Hayır, çok seviyeli soyut kalıtım geçersizdir", "Evet ama sadece ciz() çağrılabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "Kup, hem ciz() hem derinlikGoster()'ı override ettiğinden somuttur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1878, .topicId = 73,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() = 0;\n    virtual ~Sekil() {}\n};\nclass Kare : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Kare\"; }\n};\nint main() {\n    Sekil* s = new Kare();\n    s->ciz();\n    delete s;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"Kare\"", "\"Sekil\"", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "Dinamik gönderim Kare'nin ciz()'ini çalıştırır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1879, .topicId = 73,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "En az bir saf sanal fonksiyon içeren bir sınıfa soyut sınıf denir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1880, .topicId = 73,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Soyut bir sınıftan doğrudan nesne oluşturulabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: soyut sınıflar doğrudan instantiate edilemez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1881, .topicId = 73,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir türetilmiş sınıf, taban sınıfın tüm saf sanal fonksiyonlarını override etmezse, o da soyut kalır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1882, .topicId = 73,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Soyut bir sınıf, taban sınıf pointer/referans türü olarak kullanılamaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: soyut sınıflar pointer/referans türü olarak kullanılabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1883, .topicId = 73,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Saf sanal fonksiyon, gövdesi olan ama = 0 ile işaretlenen bir fonksiyondur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: saf sanal fonksiyonun tipik olarak hiç gövdesi yoktur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1884, .topicId = 73,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir sınıf hiyerarşisinde soyutluk, birden fazla seviyede (çok seviyeli kalıtımda) yayılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1885, .topicId = 73,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Gövdesi olmayan ve = 0 ile işaretlenen bir virtual fonksiyona saf sanal (pure virtual) fonksiyon denir; bunu içeren sınıfa _____ sınıf denir (Türkçe kelime).",
        .acceptedAnswers = {"soyut"},
        .explanation = "Bu sınıfa soyut sınıf denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1886, .topicId = 73,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Saf sanal fonksiyon _____ ile işaretlenir (bir sembol).",
        .acceptedAnswers = {"= 0"},
        .explanation = "Saf sanal fonksiyon = 0 ile işaretlenir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1887, .topicId = 73,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Sekil s; şeklinde soyut bir sınıftan nesne oluşturmak _____ verir (Türkçe kelime).",
        .acceptedAnswers = {"hata", "derleme hatası"},
        .explanation = "Bu bir derleme hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1888, .topicId = 73,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir türetilmiş sınıf, taban sınıfın TÜM saf sanal fonksiyonlarını override ETMEZSE, o da _____ kalır (Türkçe kelime).",
        .acceptedAnswers = {"soyut"},
        .explanation = "Türetilmiş sınıf da soyut kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1889, .topicId = 73,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() = 0;\n};\nclass Kare : public Sekil {\npublic:\n    void ciz() override { std::cout << \"K\"; }\n};\nKare k;\nk.ciz();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"K"},
        .explanation = "Kare'nin override'ı çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1890, .topicId = 73,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Soyut bir sınıf, taban sınıf _____ türü olarak kullanılabilir, sadece doğrudan nesnesi oluşturulamaz (İngilizce kelime).",
        .acceptedAnswers = {"pointer"},
        .explanation = "Soyut sınıflar pointer türü olarak kullanılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1891, .topicId = 73,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    _____\n};\nclass Kare : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Kare\"; }\n};\nSekil'i soyut yapan, saf sanal ciz() tanımını yazın.",
        .acceptedAnswers = {"virtual void ciz() = 0;"},
        .explanation = "Saf sanal fonksiyon Sekil'i soyut yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1892, .topicId = 73,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() = 0;\n};\nclass Kare : public Sekil {\npublic:\n    _____\n};\nKare k;\nk.ciz();\nKare'yi somut yapan, ciz()'i override eden (\"Kare\" yazdıran) metodu yazın.",
        .acceptedAnswers = {"void ciz() override { std::cout << \"Kare\"; }"},
        .explanation = "override, Kare'yi somut hale getirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1893, .topicId = 73,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() = 0;\n};\nclass Ucgen : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Ucgen\"; }\n};\nint main() {\n    Ucgen u;\n    u.ciz();\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Ucgen"},
        .explanation = "Ucgen somut olduğundan nesnesi oluşturulup ciz() çağrılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1894, .topicId = 73,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class Sekil {\npublic:\n    virtual void ciz() = 0;\n};\nclass Kare : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Kare\"; }\n};\nclass Dikdortgen : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Dikdortgen\"; }\n};\nint main() {\n    Sekil* sekiller[2] = {new Kare(), new Dikdortgen()};\n    for (int i = 0; i < 2; ++i) {\n        sekiller[i]->ciz();\n    }\n    delete sekiller[0];\n    delete sekiller[1];\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"KareDikdortgen"},
        .explanation = "Her eleman kendi override'ını çalıştırır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1895, .topicId = 73,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Sekil {\npublic:\n    virtual void ciz() = 0;\n};\nint main() {\n    Sekil s;\n    return 0;\n}\n\nBu kod derlenmez çünkü Sekil soyut bir sınıftır (saf sanal ciz() içerir) ve doğrudan nesnesi oluşturulamaz. Sekil s; satırını, Sekil'den türetilmiş somut bir sınıf (Kare'nin zaten tanımlı olduğunu varsayarak) kullanacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"Kare s;"},
        .explanation = "Somut bir türetilmiş sınıf kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1896, .topicId = 73,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Sekil {\npublic:\n    virtual void ciz() = 0;\n    virtual void doldur() = 0;\n};\nclass Kare : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Kare\"; }\n};\nint main() {\n    Kare k;\n    return 0;\n}\n\nBu kod derlenmez çünkü Kare, Sekil'in doldur() saf sanal fonksiyonunu override etmediğinden hala soyuttur. Kare sınıfına eklenmesi gereken, doldur()'u override eden metodu yazın.",
        .acceptedAnswers = {"void doldur() override { }"},
        .explanation = "TÜM saf sanal fonksiyonlar override edilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1897, .topicId = 73,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Sekil {\npublic:\n    virtual void ciz() = 0\n};\n\nProgramcı virtual void ciz() = 0 satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"virtual void ciz() = 0;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1898, .topicId = 73,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, soyut bir sınıf kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"Kare k;\n    k.ciz();\n    return 0;\n}", "class Sekil {\npublic:\n    virtual void ciz() = 0;\n};\nclass Kare : public Sekil {\npublic:\n    void ciz() override { std::cout << \"Kare\"; }\n};", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class tanımları (2), main açılışı (3), nesne+çağrı+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1899, .topicId = 73,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "virtual bir saf sanal ciz() metodu olan Sekil adlı soyut bir taban sınıf tanımlayın; ondan türetilen, ciz()'i override eden somut bir Kare sınıfı yazıp main() içinde kullanın.",
        .acceptedAnswers = {"= 0", "override", "cout"},
        .explanation = "Kare, ciz()'i override ederek somut hale gelmelidir.",
        .baseXp = 40,
    });

    // Topic 74: Polimorfizm
    questions.push_back(Question{
        .id = 1900, .topicId = 74,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Polimorfizm (çok biçimlilik) neyi ifade eder?",
        .options = {"Aynı taban sınıf pointer'ı üzerinden farklı türetilmiş nesnelerin, çağrılan fonksiyonun KENDİ versiyonunu çalıştırması", "Bir fonksiyonun birden fazla parametre alması", "Bir değişkenin birden fazla türde olabilmesi", "Bir sınıfın birden fazla constructor'a sahip olması"},
        .acceptedAnswers = {"a"},
        .explanation = "Polimorfizm, dinamik gönderim sayesinde gerçek türe göre doğru versiyonun çalışmasıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1901, .topicId = 74,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Polimorfizm hangi C++ özelliğine dayanır?",
        .options = {"virtual fonksiyonlar ve dinamik gönderim", "static üyeler", "Template'ler", "Namespace'ler"},
        .acceptedAnswers = {"a"},
        .explanation = "Polimorfizm, virtual fonksiyonlar sayesinde çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1902, .topicId = 74,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\"; }\n};\nclass Kedi : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Miyav\"; }\n};\nHayvan* h = new Kedi();\nh->sesCikar();\ndelete h;\nBu, polimorfizmin bir örneği midir?",
        .options = {"Evet, aynı pointer türü üzerinden gerçek türe göre doğru versiyon çağrılıyor", "Hayır, bu sadece kalıtımdır", "Hayır, polimorfizm sadece template'lerle olur", "Evet ama sadece iki sınıf varsa"},
        .acceptedAnswers = {"a"},
        .explanation = "Bu, polimorfizmin klasik bir örneğidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1903, .topicId = 74,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Hayvan* hayvanlar[3] = {new Kedi(), new Kopek(), new Kus()};\nfor (...) { hayvanlar[i]->sesCikar(); }\nBu kod, hangi C++ özelliği sayesinde her elemanın KENDİ sesini çıkarmasını sağlar?",
        .options = {"Polimorfizm (virtual fonksiyonlar aracılığıyla)", "static üyeler", "Template'ler", "Operatör aşırı yükleme"},
        .acceptedAnswers = {"a"},
        .explanation = "Polimorfizm sayesinde her eleman kendi versiyonunu çalıştırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1904, .topicId = 74,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Polimorfizmin çalışması için taban sınıftaki fonksiyonun ne olması gerekir?",
        .options = {"virtual olarak işaretlenmiş olması", "private olması", "static olması", "const olması"},
        .acceptedAnswers = {"a"},
        .explanation = "Fonksiyonun virtual olması gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1905, .topicId = 74,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual double alan() { return 0; }\n};\nclass Kare : public Sekil {\npublic:\n    double kenar;\n    Kare(double k) : kenar(k) {}\n    double alan() override { return kenar * kenar; }\n};\nSekil* s = new Kare(4);\nstd::cout << s->alan();\ndelete s;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"16", "0", "Derleme hatası", "4"},
        .acceptedAnswers = {"a"},
        .explanation = "4 * 4 = 16.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1906, .topicId = 74,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Sekil {\npublic:\n    virtual double alan() { return 0; }\n};\nclass Kare : public Sekil {\npublic:\n    double kenar;\n    Kare(double k) : kenar(k) {}\n    double alan() override { return kenar * kenar; }\n};\nclass Daire : public Sekil {\npublic:\n    double yaricap;\n    Daire(double y) : yaricap(y) {}\n    double alan() override { return yaricap * yaricap * 3; }\n};\nSekil* sekiller[2] = {new Kare(2), new Daire(2)};\ndouble toplam = 0;\nfor (int i = 0; i < 2; ++i) { toplam += sekiller[i]->alan(); }\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"16", "4", "12", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Kare(2).alan()=4, Daire(2).alan()=2*2*3=12; toplam=16.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1907, .topicId = 74,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Polimorfik bir dizi (Hayvan* hayvanlar[N]) üzerinde döngüyle her elemanın sesCikar()'ını çağırmanın avantajı nedir?",
        .options = {"Her elemanın GERÇEK türüne özel kod yazmadan, tek bir döngüyle hepsini doğru şekilde işleyebilme", "Kodun daha hızlı çalışması", "Bellek kullanımının azalması", "Derleme süresinin kısalması"},
        .acceptedAnswers = {"a"},
        .explanation = "Polimorfizm, tür-özel kod yazmayı gereksiz kılar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1908, .topicId = 74,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Polimorfizm, aynı taban sınıf pointer'ı üzerinden farklı türetilmiş nesnelerin kendi versiyonlarını çalıştırmasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1909, .topicId = 74,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Polimorfizm, virtual fonksiyonlar olmadan da çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: polimorfizm virtual fonksiyonlara dayanır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1910, .topicId = 74,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir taban sınıf pointer dizisi, farklı türetilmiş sınıflardan nesneleri aynı anda tutabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1911, .topicId = 74,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Polimorfizm sayesinde, her türetilmiş sınıf için ayrı ayrı kod yazmak yerine tek bir döngü kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1912, .topicId = 74,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Polimorfizm, sadece iki sınıf (bir taban, bir türetilmiş) olduğunda çalışır; üç veya daha fazla türetilmiş sınıfla çalışmaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: polimorfizm herhangi sayıda türetilmiş sınıfla çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1913, .topicId = 74,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Polimorfik davranış, çalışma zamanında nesnenin gerçek türüne göre belirlenir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1914, .topicId = 74,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Aynı taban sınıf pointer'ı üzerinden farklı türetilmiş nesnelerin kendi versiyonlarını çalıştırmasına _____ denir (Türkçe kelime).",
        .acceptedAnswers = {"polimorfizm"},
        .explanation = "Bu kavrama polimorfizm denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1915, .topicId = 74,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Polimorfizm, _____ fonksiyonlar ve dinamik gönderim sayesinde çalışır (İngilizce kelime).",
        .acceptedAnswers = {"virtual"},
        .explanation = "virtual fonksiyonlar polimorfizmi sağlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1916, .topicId = 74,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "class Hayvan {\npublic:\n    virtual void f() { std::cout << \"H\"; }\n};\nclass Kus : public Hayvan {\npublic:\n    void f() override { std::cout << \"U\"; }\n};\nHayvan* h = new Kus();\nh->f();\ndelete h;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"U"},
        .explanation = "Dinamik gönderim Kus'un versiyonunu çalıştırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1917, .topicId = 74,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Polimorfik bir dizi kullanmanın avantajı, her eleman için ayrı kod yazmadan tek bir _____ ile hepsini işleyebilmektir (Türkçe kelime).",
        .acceptedAnswers = {"döngü", "dongu"},
        .explanation = "Tek bir döngü tüm elemanları işleyebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1918, .topicId = 74,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Polimorfik davranış, nesnenin _____ türüne göre çalışma zamanında belirlenir (Türkçe kelime).",
        .acceptedAnswers = {"gerçek"},
        .explanation = "Nesnenin gerçek türüne göre belirlenir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1919, .topicId = 74,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual double alan() { return 0; }\n};\nclass Kare : public Sekil {\npublic:\n    double kenar;\n    Kare(double k) : kenar(k) {}\n    double alan() override { return kenar * kenar; }\n};\nSekil* s = new Kare(5);\nstd::cout << s->alan();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"25"},
        .explanation = "5 * 5 = 25.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1920, .topicId = 74,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Hayvan {\npublic:\n    virtual void sesCikar() { }\n};\nclass Kedi : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Miyav\"; }\n};\nclass Kopek : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Hav\"; }\n};\n_____\nfor (int i = 0; i < 2; ++i) { hayvanlar[i]->sesCikar(); }\nHayvan* türünde, bir Kedi ve bir Kopek nesnesi tutan hayvanlar adlı bir dizi tanımlayan satırı yazın.",
        .acceptedAnswers = {"Hayvan* hayvanlar[2] = {new Kedi(), new Kopek()};"},
        .explanation = "Dizi, Hayvan* türünde farklı türetilmiş nesneler tutar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1921, .topicId = 74,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Sekil {\npublic:\n    virtual double alan() { return 0; }\n};\nclass Kare : public Sekil {\npublic:\n    double kenar;\n    Kare(double k) : kenar(k) {}\n    _____\n};\nSekil* s = new Kare(3);\nstd::cout << s->alan();\nalan()'ı override eden, kenar*kenar döndüren metodu yazın.",
        .acceptedAnswers = {"double alan() override { return kenar * kenar; }"},
        .explanation = "alan(), kenar*kenar döndürmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1922, .topicId = 74,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\"; }\n};\nclass Kedi : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Miyav\"; }\n};\nclass Kopek : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Hav\"; }\n};\nint main() {\n    Hayvan* hayvanlar[2] = {new Kedi(), new Kopek()};\n    for (int i = 0; i < 2; ++i) {\n        hayvanlar[i]->sesCikar();\n    }\n    delete hayvanlar[0];\n    delete hayvanlar[1];\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"MiyavHav"},
        .explanation = "Her eleman kendi override'ını çalıştırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1923, .topicId = 74,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class Sekil {\npublic:\n    virtual double alan() { return 0; }\n};\nclass Kare : public Sekil {\npublic:\n    double kenar;\n    Kare(double k) : kenar(k) {}\n    double alan() override { return kenar * kenar; }\n};\nclass Daire : public Sekil {\npublic:\n    double yaricap;\n    Daire(double y) : yaricap(y) {}\n    double alan() override { return yaricap * yaricap * 3; }\n};\nint main() {\n    Sekil* sekiller[2] = {new Kare(3), new Daire(1)};\n    double toplam = 0;\n    for (int i = 0; i < 2; ++i) { toplam += sekiller[i]->alan(); }\n    std::cout << toplam;\n    delete sekiller[0];\n    delete sekiller[1];\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "Kare(3).alan()=9, Daire(1).alan()=1*1*3=3; toplam=12.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1924, .topicId = 74,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nclass Hayvan {\npublic:\n    void sesCikar() { std::cout << \"...\"; }\n};\nclass Kedi : public Hayvan {\npublic:\n    void sesCikar() { std::cout << \"Miyav\"; }\n};\nint main() {\n    Hayvan* h = new Kedi();\n    h->sesCikar();\n    delete h;\n    return 0;\n}\n\nProgramcı \"Miyav\" yazdırılmasını bekliyor ama sesCikar() virtual olmadığından polimorfizm çalışmaz, \"...\" yazdırılır. Hayvan sınıfındaki sesCikar() tanımını, virtual eklenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"virtual void sesCikar() { std::cout << \"...\"; }"},
        .explanation = "virtual eklenmeden polimorfizm çalışmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1925, .topicId = 74,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Sekil {\npublic:\n    virtual double alan() { return 0; }\n};\nclass Kare : public Sekil {\npublic:\n    double kenar;\n    double alan() override { return kenar * kenar; }\n};\nint main() {\n    Sekil* s = new Kare();\n    std::cout << s->alan();\n    delete s;\n    return 0;\n}\n\nBu kod derlenir ama Kare'nin kenar üyesi hiç ilklendirilmediğinden (constructor eksik) alan() belirsiz bir sonuç verir. Kare sınıfına, kenar'ı bir parametreyle ilklendiren eksik constructor'ı ekleyin.",
        .acceptedAnswers = {"Kare(double k) : kenar(k) {}"},
        .explanation = "kenar, bir constructor ile ilklendirilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1926, .topicId = 74,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\" }\n};\n\nProgramcı std::cout << \"...\" satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"virtual void sesCikar() { std::cout << \"...\"; }"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1927, .topicId = 74,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, polimorfizm kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"h->sesCikar();\n    delete h;\n    return 0;\n}", "class Hayvan {\npublic:\n    virtual void sesCikar() { std::cout << \"...\"; }\n};\nclass Kedi : public Hayvan {\npublic:\n    void sesCikar() override { std::cout << \"Miyav\"; }\n};", "int main() {\n    Hayvan* h = new Kedi();"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class tanımları (2), main+nesne (3), çağrı+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1928, .topicId = 74,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Hayvan adlı bir taban sınıf ve virtual bir sesCikar() metodu tanımlayın; ondan türetilen iki farklı sınıf (Kedi ve Kopek) yazıp main() içinde bir taban sınıf pointer dizisiyle her ikisini de polimorfik olarak çağırın.",
        .acceptedAnswers = {"virtual", "override", "cout"},
        .explanation = "Her iki sınıf da kendi sesCikar() versiyonunu çalıştırmalıdır.",
        .baseXp = 40,
    });
```

- [ ] **Step 3: Wire the new function into `QuestionManager`**

`src/QuestionManager.cpp` already includes `"QuestionContent.h"` (from
Phase 13). Change the constructor's opening `reserve` call and its
final append-call lines from:

```cpp
    questions_.reserve(1812);
```

to:

```cpp
    questions_.reserve(2102);
```

and from:

```cpp
    appendSection2Questions(questions_);
    appendSection3Questions(questions_);
    appendSection4Questions(questions_);
    appendSection5Questions(questions_);
    appendSection6Questions(questions_);
    appendSection7Questions(questions_);
```

to:

```cpp
    appendSection2Questions(questions_);
    appendSection3Questions(questions_);
    appendSection4Questions(questions_);
    appendSection5Questions(questions_);
    appendSection6Questions(questions_);
    appendSection7Questions(questions_);
    appendSection8Questions(questions_);
```

- [ ] **Step 4: Register the new file in CMake**

In `CMakeLists.txt`, change:

```cmake
    src/QuestionsSection6.cpp
    src/QuestionsSection7.cpp
```

to:

```cmake
    src/QuestionsSection6.cpp
    src/QuestionsSection7.cpp
    src/QuestionsSection8.cpp
```

- [ ] **Step 5: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `94/94 test(s) passed.` (unchanged — the test that counts
questions per topic is added in Task 4, once all of topics 71-80 have
their full 29 questions each).

- [ ] **Step 6: Commit**

```bash
git add src/QuestionContent.h src/QuestionsSection8.cpp src/QuestionManager.cpp CMakeLists.txt
git commit -m "feat(content): add questions for topics 71-74 (ids 1813-1928)"
```

---

### Task 3: Questions for topics 75-77 (ids 1929-2015)

**Files:**
- Modify: `src/QuestionsSection8.cpp` (append more `push_back` calls to
  the SAME `appendSection8Questions` function body Task 2 created —
  do not redeclare the function or touch any other file)

**Interfaces:**
- Consumes: `appendSection8Questions(std::vector<Question>& questions)`
  defined in `src/QuestionsSection8.cpp` by Task 2 — append to its body,
  after the last `questions.push_back(...)` for id 1928 and before the
  function's closing `}`.
- Produces: ids 1929-2015 added to the same function. Task 4 appends
  after this task's last id (2015).

- [ ] **Step 1: Write topics 75-77's questions**

In `src/QuestionsSection8.cpp`, inside `appendSection8Questions`, add
these `push_back` calls right after the id-1928 block (before the
function's closing `}`):

```cpp
    // Topic 75: this pointer'ı
    questions.push_back(Question{
        .id = 1929, .topicId = 75,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "this pointer'ı neyi tutar?",
        .options = {"Geçerli nesnenin adresini", "Sınıfın adını", "İlk üyenin değerini", "Bir sonraki nesnenin adresini"},
        .acceptedAnswers = {"a"},
        .explanation = "this, geçerli nesnenin adresini tutan bir pointer'dır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1930, .topicId = 75,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "this'in türü nedir (Sayac sınıfının bir metodunda)?",
        .options = {"Sayac*", "Sayac", "Sayac&", "void*"},
        .acceptedAnswers = {"a"},
        .explanation = "this, SinifAdi* türünde bir pointer'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1931, .topicId = 75,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Sayac {\npublic:\n    int deger;\n    void ata(int d) { this->deger = d; }\n};\nSayac s;\ns.ata(7);\nstd::cout << s.deger;\nEkrana ne yazdırılır?",
        .options = {"7", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "this->deger = d, deger üyesini 7 yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1932, .topicId = 75,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "this->uye ile uye ifadeleri bir üye fonksiyon içinde ne ilişkidedir?",
        .options = {"Aynı şeyi ifade ederler", "Farklı değişkenlerdir", "this->uye her zaman 0'dır", "uye, this->uye'den farklı bir tür döndürür"},
        .acceptedAnswers = {"a"},
        .explanation = "this->uye ve uye aynı şeyi ifade eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1933, .topicId = 75,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "*this ifadesini (referans olarak) döndürmenin amacı nedir?",
        .options = {"Metot zincirleme (method chaining) yapabilmek", "Nesneyi silmek", "Bellek sızıntısını önlemek", "Nesneyi kopyalamak"},
        .acceptedAnswers = {"a"},
        .explanation = "*this döndürmek, zincirleme çağrılara izin verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1934, .topicId = 75,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n    Sayac& artir(int m) { deger += m; return *this; }\n};\nSayac s;\ns.artir(2).artir(3);\nstd::cout << s.deger;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"5", "3", "2", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "0 + 2 + 3 = 5.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1935, .topicId = 75,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n    Sayac& artir(int m) { this->deger += m; return *this; }\n};\nSayac s;\ns.artir(1).artir(2).artir(3);\nstd::cout << s.deger;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"6", "3", "1", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "0 + 1 + 2 + 3 = 6.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1936, .topicId = 75,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int x) {\n        this->x = x;\n    }\n};\nNokta p(5);\nstd::cout << p.x;\nBu kodda parametre adı (x) ile üye adı (x) AYNI olduğunda this->x ne anlama gelir?",
        .options = {"Üye x'i (this->x), parametre x'ten ayırt eder", "Parametre x'i ifade eder", "Derleme hatası oluşur", "İkisi de aynı anda değişir"},
        .acceptedAnswers = {"a"},
        .explanation = "this->x açıkça üyeyi ifade eder; bare x, parametreyi gölgeler (shadow).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1937, .topicId = 75,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "this, geçerli nesnenin adresini tutan bir pointer'dır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1938, .topicId = 75,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "this, static bir üye fonksiyonu içinde de kullanılabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: static fonksiyonların örtük this'i yoktur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1939, .topicId = 75,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "this->uye ile uye, bir üye fonksiyon içinde aynı şeyi ifade eder.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1940, .topicId = 75,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "*this ifadesi, geçerli nesnenin kendisini (dereference edilmiş) ifade eder.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1941, .topicId = 75,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir metot *this'i referans olarak döndürürse, ardışık metot çağrıları (zincirleme) yapılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1942, .topicId = 75,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "this, üyelere erişmek için nokta (.) operatörüyle kullanılır (this.uye).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: this bir pointer olduğundan ok (->) operatörü kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1943, .topicId = 75,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Geçerli nesnenin adresini tutan örtük pointer'a _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"this"},
        .explanation = "Bu pointer'a this denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1944, .topicId = 75,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "class Sayac {\npublic:\n    int deger;\n    void ata(int d) { this->deger = d; }\n};\nSayac s;\ns.ata(12);\nstd::cout << s.deger;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"12"},
        .explanation = "ata(12), deger'i 12 yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1945, .topicId = 75,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "this bir pointer olduğundan üyelere erişmek için nokta değil _____ operatörü kullanılır (bir sembol).",
        .acceptedAnswers = {"->"},
        .explanation = "Ok operatörü (->) kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1946, .topicId = 75,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Metot zincirleme (chaining) yapabilmek için bir metot _____ ifadesini referans olarak döndürmelidir (İngilizce iki karakter).",
        .acceptedAnswers = {"*this"},
        .explanation = "*this döndürmek zincirlemeye izin verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1947, .topicId = 75,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n    Sayac& artir(int m) { deger += m; return *this; }\n};\nSayac s;\ns.artir(4).artir(6);\nstd::cout << s.deger;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"10"},
        .explanation = "0 + 4 + 6 = 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1948, .topicId = 75,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir constructor parametresi ile üye adı aynıysa (örneğin ikisi de x), this->x kullanmak üye x'i _____ x'ten ayırt eder (Türkçe kelime).",
        .acceptedAnswers = {"parametre"},
        .explanation = "this->x, üyeyi parametreden ayırt eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1949, .topicId = 75,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n    _____\n};\nSayac s;\ns.artir(5).artir(2);\nstd::cout << s.deger;\nartir(int) metodunu, deger'i artırıp *this döndürecek şekilde tanımlayan satırı yazın.",
        .acceptedAnswers = {"Sayac& artir(int m) { deger += m; return *this; }"},
        .explanation = "*this döndürmek zincirlemeye izin verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1950, .topicId = 75,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int x) {\n        _____\n    }\n};\nNokta p(9);\nstd::cout << p.x;\nconstructor gövdesinde, parametre x'i üye x'e (this-> ile) atayan satırı yazın.",
        .acceptedAnswers = {"this->x = x;"},
        .explanation = "this->x, üye x'i ifade eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1951, .topicId = 75,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n    Sayac& artir(int m) { this->deger += m; return *this; }\n};\nint main() {\n    Sayac s;\n    s.artir(10).artir(20);\n    std::cout << s.deger;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30"},
        .explanation = "0 + 10 + 20 = 30.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1952, .topicId = 75,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class Nokta {\npublic:\n    int x, y;\n    Nokta(int x, int y) {\n        this->x = x;\n        this->y = y;\n    }\n};\nint main() {\n    Nokta p(3, 4);\n    std::cout << p.x + p.y;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"7"},
        .explanation = "3 + 4 = 7.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1953, .topicId = 75,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nclass Nokta {\npublic:\n    int x;\n    Nokta(int x) {\n        x = x;\n    }\n};\nint main() {\n    Nokta p(5);\n    std::cout << p.x;\n    return 0;\n}\n\nBu kod derlenir ama x = x; ifadesi parametre x'i kendisine atar (üye x'e değil), üye x hiçbir zaman ilklendirilmez. Constructor gövdesindeki hatalı satırı, this-> ile üyeyi doğru ilklendirecek haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"this->x = x;"},
        .explanation = "this->x, üyeyi parametreden ayırt ederek doğru ilklendirmeyi sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1954, .topicId = 75,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Sayac {\npublic:\n    int deger = 0;\n    void artir(int m) { deger += m; return *this; }\n};\n\nBu kod derlenmez çünkü artir(int)'in dönüş türü void'dir ama gövde *this döndürmeye çalışıyor. Fonksiyon başlığını, Sayac& dönüş türüyle düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"Sayac& artir(int m) { deger += m; return *this; }"},
        .explanation = "Dönüş türü, *this'in türüne (Sayac&) uygun olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1955, .topicId = 75,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Sayac {\npublic:\n    int deger = 0;\n    Sayac& artir(int m) { this->deger += m; return *this }\n};\n\nProgramcı return *this satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"Sayac& artir(int m) { this->deger += m; return *this; }"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1956, .topicId = 75,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, this pointer'ı ve metot zincirleme kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"s.artir(2).artir(3);\n    std::cout << s.deger;\n    return 0;\n}", "class Sayac {\npublic:\n    int deger = 0;\n    Sayac& artir(int m) { this->deger += m; return *this; }\n};", "int main() {\n    Sayac s;"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class tanımı (2), main+nesne (3), zincirleme çağrı+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1957, .topicId = 75,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "deger adlı bir int üyesi olan Sayac adlı bir sınıf tanımlayın; this->deger kullanan ve *this döndüren bir artir(int) metodu ekleyip main() içinde zincirleme çağırın.",
        .acceptedAnswers = {"this->", "*this", "cout"},
        .explanation = "artir metodu this->deger'i güncelleyip *this döndürmelidir.",
        .baseXp = 40,
    });

    // Topic 76: static sınıf üyesi
    questions.push_back(Question{
        .id = 1958, .topicId = 76,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "static bir sınıf üyesi neyi ifade eder?",
        .options = {"Sınıfın TÜM nesneleri arasında paylaşılan tek bir kopya", "Her nesnenin kendine özel bir kopyası", "Sadece const olabilen bir üye", "Silinmesi mümkün olmayan bir üye"},
        .acceptedAnswers = {"a"},
        .explanation = "static üye, sınıfın tüm nesneleri arasında paylaşılan tek bir kopyadır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1959, .topicId = 76,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Sayac {\npublic:\n    static inline int toplam = 0;\n    Sayac() { toplam++; }\n};\nSayac a, b, c;\nstd::cout << Sayac::toplam;\nEkrana ne yazdırılır?",
        .options = {"3", "1", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Üç nesne oluşturulduğunda paylaşılan toplam 3 olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1960, .topicId = 76,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "static bir üyeye sınıf adıyla (nesne olmadan) nasıl erişilir?",
        .options = {"SinifAdi::uye", "SinifAdi->uye", "SinifAdi.uye", "SinifAdi(uye)"},
        .acceptedAnswers = {"a"},
        .explanation = "static üyeye SinifAdi:: ile erişilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1961, .topicId = 76,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    static inline int toplam = 0;\n};\nSayac a;\na.toplam = 5;\nstd::cout << Sayac::toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"5", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "static üye paylaşılan tek kopya olduğundan nesne üzerinden değiştirme, sınıf adıyla erişimi de etkiler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1962, .topicId = 76,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    static inline int toplam = 0;\n};\nSayac a, b;\na.toplam = 10;\nstd::cout << b.toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"10", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "toplam paylaşılan tek kopya olduğundan a üzerinden değişiklik b üzerinden de görünür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1963, .topicId = 76,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "static bir üye fonksiyonu, static olmayan bir üyeye doğrudan erişmeye çalışırsa ne olur?",
        .options = {"Derleme hatası (static fonksiyonun örtük this'i yoktur)", "Sorunsuz çalışır", "Değer her zaman 0 olur", "Çalışma zamanı hatası verir"},
        .acceptedAnswers = {"a"},
        .explanation = "static fonksiyonların örtük this'i olmadığından static olmayan üyelere erişemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1964, .topicId = 76,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Hesap {\npublic:\n    static inline int toplamHesap = 0;\n    Hesap() { toplamHesap++; }\n    ~Hesap() { toplamHesap--; }\n};\nint main() {\n    Hesap h1;\n    {\n        Hesap h2;\n        std::cout << Hesap::toplamHesap << \" \";\n    }\n    std::cout << Hesap::toplamHesap;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"2 1\"", "\"1 2\"", "\"2 2\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "h1 ve h2 ile toplamHesap 2 olur (\"2 \"); h2 kapsam dışına çıkınca 1'e düşer (\"1\").",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1965, .topicId = 76,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Sayac {\npublic:\n    static int getToplam() { return toplam; }\nprivate:\n    static inline int toplam = 5;\n};\nstd::cout << Sayac::getToplam();\nBu kod derlenir mi (static metot, static üyeye erişiyor)?",
        .options = {"Evet, static bir metot başka bir static üyeye doğrudan erişebilir", "Hayır, static metotlar hiçbir üyeye erişemez", "Hayır, private static üyeye erişilemez", "Evet ama sadece const ise"},
        .acceptedAnswers = {"a"},
        .explanation = "static metotlar diğer static üyelere doğrudan erişebilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1966, .topicId = 76,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "static bir üye, sınıfın TÜM nesneleri arasında paylaşılan tek bir kopyaya sahiptir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1967, .topicId = 76,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "static bir üyenin her nesne için ayrı bir kopyası vardır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: static üye tek bir paylaşılan kopyadır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1968, .topicId = 76,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "static bir üyeye, sınıf adıyla (SinifAdi::uye) nesne oluşturmadan erişilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1969, .topicId = 76,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "static bir üye fonksiyonunun örtük bir this pointer'ı vardır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: static fonksiyonların örtük this'i yoktur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1970, .topicId = 76,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "static bir üye fonksiyonu, başka bir static üyeye doğrudan erişebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1971, .topicId = 76,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "static bir üye fonksiyonu, static olmayan bir üyeye doğrudan erişebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: örtük this olmadığından erişemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1972, .topicId = 76,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Sınıfın tüm nesneleri arasında paylaşılan tek bir kopyaya sahip üyeye _____ üye denir (İngilizce kelime).",
        .acceptedAnswers = {"static"},
        .explanation = "Bu tür üyeye static üye denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1973, .topicId = 76,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "class Sayac {\npublic:\n    static inline int toplam = 0;\n    Sayac() { toplam++; }\n};\nSayac a, b;\nstd::cout << Sayac::toplam;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "İki nesne oluşturulduğunda toplam 2 olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1974, .topicId = 76,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "static bir üyeye sınıf adıyla erişmek için _____ operatörü kullanılır (bir sembol).",
        .acceptedAnswers = {"::"},
        .explanation = "Kapsam çözümleme operatörü (::) kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1975, .topicId = 76,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "static bir üye fonksiyonu, static olmayan üyelere doğrudan erişemez çünkü örtük bir _____ pointer'ı yoktur (İngilizce kelime).",
        .acceptedAnswers = {"this"},
        .explanation = "static fonksiyonların this'i yoktur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1976, .topicId = 76,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    static inline int toplam = 0;\n};\nSayac a, b;\na.toplam = 7;\nstd::cout << b.toplam;\nEkran çıktısı _____ olur (paylaşılan tek kopya olduğu için).",
        .acceptedAnswers = {"7"},
        .explanation = "toplam paylaşılan tek kopya olduğundan b üzerinden de 7 görünür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1977, .topicId = 76,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "C++17'den itibaren, static bir üyeyi sınıf içinde ilklendirmek için static _____ anahtar kelimesi kullanılabilir (İngilizce kelime).",
        .acceptedAnswers = {"inline"},
        .explanation = "static inline, C++17'de sınıf içi ilklendirmeyi sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1978, .topicId = 76,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    _____\n    Sayac() { toplam++; }\n};\ntoplam adlı, 0 ile ilklendirilmiş static bir int üye tanımlayan satırı (static inline ile) yazın.",
        .acceptedAnswers = {"static inline int toplam = 0;"},
        .explanation = "static inline int toplam = 0; paylaşılan üyeyi tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1979, .topicId = 76,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    static inline int toplam = 0;\n    _____\n};\nSayac a, b, c;\nstd::cout << Sayac::toplam;\nHer nesne oluşturulduğunda toplam'ı bir artıran bir constructor tanımlayan satırı yazın.",
        .acceptedAnswers = {"Sayac() { toplam++; }"},
        .explanation = "Constructor, her çağrıda paylaşılan toplam'ı artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1980, .topicId = 76,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    static inline int toplam = 0;\n    Sayac() { toplam++; }\n};\nint main() {\n    Sayac a;\n    Sayac b;\n    Sayac c;\n    Sayac d;\n    std::cout << Sayac::toplam;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"4"},
        .explanation = "Dört nesne oluşturulduğunda toplam 4 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1981, .topicId = 76,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class Hesap {\npublic:\n    static inline int toplamHesap = 0;\n    Hesap() { toplamHesap++; }\n    ~Hesap() { toplamHesap--; }\n};\nint main() {\n    Hesap h1;\n    Hesap h2;\n    std::cout << Hesap::toplamHesap << \" \";\n    {\n        Hesap h3;\n        std::cout << Hesap::toplamHesap << \" \";\n    }\n    std::cout << Hesap::toplamHesap;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2 3 2"},
        .explanation = "h1,h2 ile toplamHesap=2; h3 eklenince 3; h3 kapsam dışına çıkınca tekrar 2.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1982, .topicId = 76,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Sayac {\npublic:\n    static void goster() {\n        std::cout << deger;\n    }\nprivate:\n    int deger = 0;\n};\n\nBu kod derlenmez çünkü static goster() metodu, static OLMAYAN deger üyesine doğrudan erişmeye çalışıyor (örtük this yok). deger tanımını, static yaparak (ve inline ilklendirerek) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"static inline int deger = 0;"},
        .explanation = "deger static yapılırsa static goster() metodu ona erişebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1983, .topicId = 76,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nclass Sayac {\npublic:\n    static inline int toplam = 0;\n    Sayac() { }\n};\nint main() {\n    Sayac a, b, c;\n    std::cout << Sayac::toplam;\n    return 0;\n}\n\nProgramcı toplam'ın 3 olmasını bekliyor ama constructor toplam'ı hiç artırmadığından 0 kalır. Sayac'ın constructor'ını, her nesne oluşturulduğunda toplam'ı artıracak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"Sayac() { toplam++; }"},
        .explanation = "Constructor'da toplam++ eklenmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1984, .topicId = 76,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Sayac {\npublic:\n    static inline int toplam = 0;\n    Sayac() { toplam++ }\n};\n\nProgramcı toplam++ satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"Sayac() { toplam++; }"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1985, .topicId = 76,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, static bir üye kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"Sayac a, b;\n    std::cout << Sayac::toplam;\n    return 0;\n}", "class Sayac {\npublic:\n    static inline int toplam = 0;\n    Sayac() { toplam++; }\n};", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class tanımı (2), main açılışı (3), nesneler+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1986, .topicId = 76,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "toplamNesne adlı static bir int üyesi olan Sayac adlı bir sınıf tanımlayın; her constructor çağrısında toplamNesne'yi artırıp main() içinde birkaç nesne oluşturduktan sonra Sayac::toplamNesne'yi yazdırın.",
        .acceptedAnswers = {"static", "cout"},
        .explanation = "toplamNesne, her nesne oluşturulduğunda artırılmalıdır.",
        .baseXp = 40,
    });

    // Topic 77: Operatör aşırı yükleme
    questions.push_back(Question{
        .id = 1987, .topicId = 77,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Operatör aşırı yükleme (operator overloading) neyi ifade eder?",
        .options = {"+, ==, << gibi operatörlerin kullanıcı tanımlı türler için yeniden tanımlanması", "Bir fonksiyonun birden fazla parametre alması", "Bir sınıfın birden fazla constructor'a sahip olması", "Bir değişkenin türünün değiştirilmesi"},
        .acceptedAnswers = {"a"},
        .explanation = "Operatör aşırı yükleme, operatörleri kullanıcı tanımlı türler için yeniden tanımlar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1988, .topicId = 77,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Nokta {\npublic:\n    int x, y;\n    Nokta(int xd, int yd) : x(xd), y(yd) {}\n    Nokta operator+(const Nokta& d) const { return Nokta(x + d.x, y + d.y); }\n};\nNokta a(1, 2), b(3, 4);\nNokta c = a + b;\nstd::cout << c.x << \" \" << c.y;\nEkrana ne yazdırılır?",
        .options = {"\"4 6\"", "\"1 2\"", "Derleme hatası", "\"3 4\""},
        .acceptedAnswers = {"a"},
        .explanation = "x'ler (1+3=4) ve y'ler (2+4=6) ayrı ayrı toplanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1989, .topicId = 77,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir operatör üye fonksiyon olarak overload edildiğinde, sol taraftaki işlenen neyi ifade eder?",
        .options = {"Örtük this (çağrılan nesnenin kendisi)", "Her zaman 0", "Sağ taraftaki işlenen", "Bir referans parametresi"},
        .acceptedAnswers = {"a"},
        .explanation = "Sol işlenen örtük this'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1990, .topicId = 77,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    bool operator==(const Nokta& d) const { return x == d.x; }\n};\nNokta a(5), b(5);\nstd::cout << (a == b);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"1", "0", "Derleme hatası", "5"},
        .acceptedAnswers = {"a"},
        .explanation = "a.x == b.x (5==5) true (1) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1991, .topicId = 77,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "operator+ içinde diger.x kullanmak yerine yanlışlıkla x kullanmak (kendi üyesini iki kez) ne tür bir hataya yol açar?",
        .options = {"Mantık hatası (toplama yerine ikiye katlama gibi yanlış bir sonuç)", "Derleme hatası", "Çalışma zamanı çökmesi", "Bellek sızıntısı"},
        .acceptedAnswers = {"a"},
        .explanation = "Bu, derlenen ama yanlış sonuç veren bir mantık hatasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1992, .topicId = 77,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Kesir {\npublic:\n    int pay, payda;\n    Kesir(int p, int pd) : pay(p), payda(pd) {}\n    Kesir operator+(const Kesir& d) const {\n        return Kesir(pay * d.payda + d.pay * payda, payda * d.payda);\n    }\n};\nKesir a(1, 2), b(1, 3);\nKesir c = a + b;\nstd::cout << c.pay << \"/\" << c.payda;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"5/6\"", "\"2/5\"", "\"1/2\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "pay=1*3+1*2=5, payda=2*3=6.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1993, .topicId = 77,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Nokta {\npublic:\n    int x, y;\n    Nokta(int xd, int yd) : x(xd), y(yd) {}\n    Nokta operator+(const Nokta& d) const { return Nokta(x + d.x, y + d.y); }\n};\nNokta a(1, 1), b(2, 2), c(3, 3);\nNokta sonuc = a + b + c;\nstd::cout << sonuc.x << \" \" << sonuc.y;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"6 6\"", "\"3 3\"", "Derleme hatası", "\"1 1\""},
        .acceptedAnswers = {"a"},
        .explanation = "a+b=(3,3), (a+b)+c=(6,6).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1994, .topicId = 77,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    Nokta operator+(const Nokta& d) const { return Nokta(x + x); }\n};\nNokta a(3), b(5);\nNokta c = a + b;\nstd::cout << c.x;\nBu kodda bir MANTIK hatası var; d.x yerine x kullanılmış. Ekran çıktısı ne olur?",
        .options = {"6", "8", "10", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "operator+ b'yi (d) hiç dikkate almadan x+x=3+3=6 döndürür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1995, .topicId = 77,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Operatör aşırı yükleme, kullanıcı tanımlı türler için operatörlerin yeniden tanımlanmasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1996, .topicId = 77,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "C++'ta operatörler sadece temel türler (int, double) için kullanılabilir, kullanıcı tanımlı türler için overload edilemez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: kullanıcı tanımlı türler için de overload edilebilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1997, .topicId = 77,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir operatör üye fonksiyon olarak overload edildiğinde, sol taraftaki işlenen örtük this'tir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1998, .topicId = 77,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "operator+ içinde diğer nesnenin üyelerine erişmek için diger. ön eki gereksizdir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: diğer nesnenin üyelerine diger. ön ekiyle erişilmelidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1999, .topicId = 77,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "operator== genellikle bool döndürür ve iki nesnenin eşitliğini karşılaştırır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2000, .topicId = 77,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir operatör overload edildiğinde, orijinal davranışı (örneğin int'ler için +) değişir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: yeni bir tür için overload etmek, temel türler için davranışı değiştirmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2001, .topicId = 77,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Kullanıcı tanımlı türler için operatörlerin yeniden tanımlanmasına operatör _____ denir (Türkçe kelime).",
        .acceptedAnswers = {"aşırı yükleme", "asiri yukleme"},
        .explanation = "Bu kavrama operatör aşırı yükleme denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2002, .topicId = 77,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    Nokta operator+(const Nokta& d) const { return Nokta(x + d.x); }\n};\nNokta a(3), b(4);\nNokta c = a + b;\nstd::cout << c.x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "3 + 4 = 7.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2003, .topicId = 77,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir operatör üye fonksiyon olarak overload edildiğinde sol taraftaki işlenen _____ dir (İngilizce kelime).",
        .acceptedAnswers = {"this"},
        .explanation = "Sol işlenen this'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2004, .topicId = 77,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "operator+ içinde diger.x yerine yanlışlıkla x kullanmak, toplama yerine _____ gibi yanlış bir sonuç üretir (Türkçe kelime).",
        .acceptedAnswers = {"ikiye katlama"},
        .explanation = "Kendi üyesini iki kez kullanmak ikiye katlama gibi bir sonuç verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2005, .topicId = 77,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    bool operator==(const Nokta& d) const { return x == d.x; }\n};\nNokta a(5), b(6);\nstd::cout << (a == b);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"0"},
        .explanation = "5 == 6 false (0) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2006, .topicId = 77,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir operatörü member fonksiyon olarak overload etmek için operatör_____ sözdizimi kullanılır (İngilizce kelime, örn. 'operator+').",
        .acceptedAnswers = {"operator"},
        .explanation = "operator anahtar kelimesi kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2007, .topicId = 77,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x, y;\n    Nokta(int xd, int yd) : x(xd), y(yd) {}\n    _____\n};\nNokta a(1, 2), b(3, 4);\nNokta c = a + b;\nx ve y'leri ayrı ayrı toplayan operator+ tanımını yazın.",
        .acceptedAnswers = {"Nokta operator+(const Nokta& d) const { return Nokta(x + d.x, y + d.y); }"},
        .explanation = "operator+, x ve y'leri ayrı ayrı toplar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2008, .topicId = 77,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    bool operator==(const Nokta& d) const {\n        _____\n    }\n};\nNokta a(5), b(5);\nstd::cout << (a == b);\nx'lerin eşit olup olmadığını döndüren satırı yazın.",
        .acceptedAnswers = {"return x == d.x;"},
        .explanation = "İki nesnenin x'leri karşılaştırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2009, .topicId = 77,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    Nokta operator+(const Nokta& d) const { return Nokta(x + d.x); }\n};\nint main() {\n    Nokta a(10), b(20);\n    Nokta c = a + b;\n    std::cout << c.x;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30"},
        .explanation = "10 + 20 = 30.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2010, .topicId = 77,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class Kesir {\npublic:\n    int pay, payda;\n    Kesir(int p, int pd) : pay(p), payda(pd) {}\n    Kesir operator+(const Kesir& d) const {\n        return Kesir(pay * d.payda + d.pay * payda, payda * d.payda);\n    }\n};\nint main() {\n    Kesir a(1, 4), b(1, 4);\n    Kesir c = a + b;\n    std::cout << c.pay << \"/\" << c.payda;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"8/16"},
        .explanation = "pay=1*4+1*4=8, payda=4*4=16.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2011, .topicId = 77,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nclass Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    Nokta operator+(const Nokta& d) const {\n        return Nokta(x + x);\n    }\n};\nint main() {\n    Nokta a(3), b(5);\n    Nokta c = a + b;\n    std::cout << c.x;\n    return 0;\n}\n\nBu kod derlenir ama operator+ içinde d.x yerine yanlışlıkla x kullanılmış (b'nin değeri hiç dikkate alınmıyor); c.x=6 (3+3) olur, 8 (3+5) değil. operator+ içindeki hatalı satırı, d.x kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"return Nokta(x + d.x);"},
        .explanation = "Diğer nesnenin üyesine d.x ile erişilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2012, .topicId = 77,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    Nokta operator+(const Nokta& d) { return Nokta(x + d.x); }\n};\nconst Nokta a(3);\nNokta b(4);\nNokta c = a + b;\n\nBu kod derlenmez çünkü operator+ const olarak işaretlenmemiş ama a const bir Nokta'dır; const bir nesne üzerinden const olmayan bir metot çağrılamaz. operator+ tanımını, const eklenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"Nokta operator+(const Nokta& d) const { return Nokta(x + d.x); }"},
        .explanation = "const bir nesne üzerinden sadece const metotlar çağrılabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2013, .topicId = 77,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    Nokta operator+(const Nokta& d) const { return Nokta(x + d.x) }\n};\n\nProgramcı return Nokta(x + d.x) satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"Nokta operator+(const Nokta& d) const { return Nokta(x + d.x); }"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2014, .topicId = 77,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, operatör aşırı yükleme kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"Nokta c = a + b;\n    std::cout << c.x;\n    return 0;\n}", "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) : x(xd) {}\n    Nokta operator+(const Nokta& d) const { return Nokta(x + d.x); }\n};", "int main() {\n    Nokta a(2), b(3);"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class tanımı (2), main+nesneler (3), toplama+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2015, .topicId = 77,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "x ve y adlı int üyeleri olan Nokta adlı bir sınıf tanımlayın; iki Nokta'yı toplayan bir operator+ ekleyip main() içinde iki nesneyi toplayıp sonucu yazdırın.",
        .acceptedAnswers = {"operator+", "cout"},
        .explanation = "operator+, x ve y'leri ayrı ayrı toplamalıdır.",
        .baseXp = 40,
    });
```

- [ ] **Step 2: Build and run tests**

Run: `"C:/Program Files/CMake/bin/cmake.exe" --build build`
Expected: clean build, zero warnings.

Run: `./build/Debug/CppMasterConsoleTests.exe`
Expected: `94/94 test(s) passed.` (unchanged — no existing test yet counts
these topics' questions).

- [ ] **Step 3: Commit**

```bash
git add src/QuestionsSection8.cpp
git commit -m "feat(content): add questions for topics 75-77 (ids 1929-2015)"
```

---

### Task 4: Questions for topics 78-80 (ids 2016-2102), test updates, and final integration

**Files:**
- Modify: `src/QuestionsSection8.cpp` (append the final `push_back`
  calls to `appendSection8Questions`)
- Modify: `tests/QuestionManagerTests.cpp` (add one new per-section
  minimum-count test)
- Modify: `docs/superpowers/roadmap.md` (mark Phase 19 complete)

**Interfaces:**
- Consumes: `appendSection8Questions(std::vector<Question>& questions)`
  in `src/QuestionsSection8.cpp` — append after Task 3's last id (2015),
  before the function's closing `}`. After this task, ids 1813-2102 are
  all present (10 topics x 29 questions) and the function is complete.

- [ ] **Step 1: Write topics 78-80's questions**

In `src/QuestionsSection8.cpp`, inside `appendSection8Questions`, add
these `push_back` calls right after the id-2015 block (before the
function's closing `}`):

```cpp
    // Topic 78: Template fonksiyon
    questions.push_back(Question{
        .id = 2016, .topicId = 78,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir template fonksiyonun amacı nedir?",
        .options = {"Türden bağımsız (generic), birden fazla türle çalışabilen bir fonksiyon tanımlamak", "Bir fonksiyonu virtual yapmak", "Bir sınıfı soyut yapmak", "Bir değişkeni sabit yapmak"},
        .acceptedAnswers = {"a"},
        .explanation = "Template fonksiyonlar türden bağımsız, generic kod yazmayı sağlar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2017, .topicId = 78,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "template<typename T>\nT topla(T a, T b) { return a + b; }\ntopla(3, 4) çağrısında T hangi türe çıkarılır?",
        .options = {"int", "double", "void", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "Argümanlar int olduğundan T de int olarak çıkarılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2018, .topicId = 78,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "template<typename T>\nT topla(T a, T b) { return a + b; }\nstd::cout << topla(3, 4);\nEkrana ne yazdırılır?",
        .options = {"7", "34", "Derleme hatası", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "3 + 4 = 7.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2019, .topicId = 78,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "template<typename T>\nT topla(T a, T b) { return a + b; }\nstd::cout << topla(2.5, 1.5);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"4", "4.0", "Derleme hatası", "3"},
        .acceptedAnswers = {"a"},
        .explanation = "2.5+1.5=4.0; cout varsayılan biçimde tam sayı değerli double'ı '4' olarak yazdırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2020, .topicId = 78,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Aynı template fonksiyon, aynı programda kaç farklı türle örneklenebilir (instantiate edilebilir)?",
        .options = {"Sınırsız sayıda farklı türle", "Sadece bir türle", "En fazla iki türle", "Hiçbiriyle, sadece bir kez derlenir"},
        .acceptedAnswers = {"a"},
        .explanation = "Aynı template, farklı türlerle birden fazla kez örneklenebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2021, .topicId = 78,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "template<typename T>\nT topla(T a, T b) { return a + b; }\ntopla<int>(3, 4) çağrısında <int> ne işe yarar?",
        .options = {"T türünü açıkça int olarak belirtir", "Fonksiyonu silmek için kullanılır", "Bir hata mesajıdır", "Derleyici tarafından yok sayılır"},
        .acceptedAnswers = {"a"},
        .explanation = "<int>, T'yi açıkça belirtmek için kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2022, .topicId = 78,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "template<typename T>\nT buyukOlan(T a, T b) {\n    if (a > b) return a;\n    return b;\n}\nstd::cout << buyukOlan(3, 7) << \" \" << buyukOlan(2.5, 1.1);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"7 2.5\"", "\"3 1.1\"", "Derleme hatası", "\"7 2\""},
        .acceptedAnswers = {"a"},
        .explanation = "buyukOlan(3,7)=7 (int); buyukOlan(2.5,1.1)=2.5 (double).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2023, .topicId = 78,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "template<typename T>\nT topla(T a, T b) { return a + b; }\nstd::cout << topla(3, 4.5);\nBu kod derlenir mi (int ve double karışık argümanlar)?",
        .options = {"Hayır, T için int ve double çakıştığından derleme hatası oluşur (deduction başarısız)", "Evet, T otomatik olarak double olur", "Evet, T otomatik olarak int olur", "Evet, ikisi de kullanılır"},
        .acceptedAnswers = {"a"},
        .explanation = "T, tüm argümanlardan AYNI türe çıkarılmalıdır; farklı türler çakışma hatası verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2024, .topicId = 78,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir template fonksiyon, türden bağımsız (generic) bir fonksiyon tanımlamanın yoludur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2025, .topicId = 78,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir template fonksiyon, sadece TEK bir türle çalışabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: birden fazla farklı türle çalışabilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2026, .topicId = 78,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Template'in gerçek türü, fonksiyon çağrıldığında argümanlardan derleme zamanında çıkarılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2027, .topicId = 78,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Template türü, her zaman açıkça belirtilmelidir (örn. topla<int>(...)); derleyici asla çıkarım yapamaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: derleyici genellikle türü argümanlardan çıkarabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2028, .topicId = 78,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Aynı template fonksiyon aynı programda hem int hem double ile ayrı ayrı çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2029, .topicId = 78,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "template<typename T> T f(T a, T b) fonksiyonu, a ve b farklı türlerde (biri int biri double) verildiğinde ve tür açıkça belirtilmediğinde her zaman sorunsuz derlenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: T için çıkarım çakışır, derleme hatası oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2030, .topicId = 78,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Türden bağımsız bir fonksiyon tanımlamak için _____ anahtar kelimesi kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"template"},
        .explanation = "template anahtar kelimesi kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2031, .topicId = 78,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "template<typename T>\nT topla(T a, T b) { return a + b; }\nstd::cout << topla(5, 6);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"11"},
        .explanation = "5 + 6 = 11.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2032, .topicId = 78,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "template<typename T> ifadesindeki T, bir _____ türüdür (Türkçe iki kelime).",
        .acceptedAnswers = {"yer tutucu"},
        .explanation = "T, çağrıya göre belirlenecek bir yer tutucu türdür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2033, .topicId = 78,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "template<typename T>\nT topla(T a, T b) { return a + b; }\nstd::cout << topla(1.5, 2.5);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"4"},
        .explanation = "1.5+2.5=4.0, cout '4' yazdırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2034, .topicId = 78,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Template fonksiyonda gerçek tür, çağrıdaki argümanlardan derleme zamanında otomatik olarak _____ (Türkçe kelime, 'belirlenir/çıkarılır' anlamında).",
        .acceptedAnswers = {"çıkarılır", "cikarilir"},
        .explanation = "Tür, argümanlardan çıkarılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2035, .topicId = 78,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "topla<int>(3, 4) çağrısındaki <int>, T türünü _____ olarak belirtir (İngilizce kelime).",
        .acceptedAnswers = {"int"},
        .explanation = "T açıkça int olarak belirtilmiştir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2036, .topicId = 78,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nT topla(T a, T b) {\n    return a + b;\n}\nstd::cout << topla(3, 4);\ntopla fonksiyonunu template olarak tanımlayan (template<typename T>) satırı yazın.",
        .acceptedAnswers = {"template<typename T>"},
        .explanation = "template<typename T>, T'yi bir yer tutucu tür olarak tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2037, .topicId = 78,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "template<typename T>\nT buyukOlan(T a, T b) {\n    _____\n}\nstd::cout << buyukOlan(3, 7);\na ve b'den büyük olanı döndüren gövdeyi (if ile) yazın.",
        .acceptedAnswers = {"if (a > b) return a; return b;"},
        .explanation = "Büyük olan değer döndürülür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2038, .topicId = 78,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "template<typename T>\nT carp(T a, T b) {\n    return a * b;\n}\nint main() {\n    std::cout << carp(3, 4);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "3 * 4 = 12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2039, .topicId = 78,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "template<typename T>\nT carp(T a, T b) {\n    return a * b;\n}\nint main() {\n    std::cout << carp(3, 4) << \" \" << carp(2.0, 5.0);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12 10"},
        .explanation = "carp(3,4)=12 (int); carp(2.0,5.0)=10.0 (double, '10' yazdırılır).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2040, .topicId = 78,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\ntypename T\nT topla(T a, T b) {\n    return a + b;\n}\n\nBu kod derlenmez çünkü template<...> öneki eksik. Hatalı ilk satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"template<typename T>"},
        .explanation = "template<typename T> önekiyle T bir template parametresi olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2041, .topicId = 78,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\ntemplate<typename T>\nT topla(T a, T b) {\n    return a + b;\n}\nint main() {\n    std::cout << topla(3, 4.5);\n    return 0;\n}\n\nBu kod derlenmez çünkü argümanlar farklı türde (int ve double); T için çıkarım çakışıyor. Çağrıyı, T'yi açıkça double olarak belirterek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"topla<double>(3, 4.5);"},
        .explanation = "T'yi açıkça belirtmek çakışmayı çözer.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2042, .topicId = 78,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\ntemplate<typename T>\nT topla(T a, T b) {\n    return a + b\n}\n\nProgramcı return a + b satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"return a + b;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2043, .topicId = 78,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir template fonksiyon tanımlayıp kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << topla(3, 4);\n    return 0;\n}", "template<typename T>\nT topla(T a, T b) {\n    return a + b;\n}", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "template tanımı (2), main açılışı (3), kullanım+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2044, .topicId = 78,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "İki değeri toplayıp döndüren bir template fonksiyon tanımlayın; main() içinde hem int hem double türleriyle çağırıp sonuçlarını yazdırın.",
        .acceptedAnswers = {"template", "typename", "cout"},
        .explanation = "Aynı template fonksiyon hem int hem double ile çağrılabilmelidir.",
        .baseXp = 40,
    });

    // Topic 79: namespace
    questions.push_back(Question{
        .id = 2045, .topicId = 79,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "namespace'in amacı nedir?",
        .options = {"İlgili isimleri gruplandırıp isim çakışmalarını önlemek", "Bir sınıfı soyut yapmak", "Bir fonksiyonu virtual yapmak", "Bellek ayırmak"},
        .acceptedAnswers = {"a"},
        .explanation = "namespace, isim çakışmalarını önleyen bir gruplama mekanizmasıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2046, .topicId = 79,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "namespace Matematik { int kare(int x) { return x*x; } }\nMatematik::kare(4) çağrısı ne döndürür?",
        .options = {"16", "4", "8", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "4 * 4 = 16.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2047, .topicId = 79,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir namespace içindeki bir isme erişmenin iki yolu nedir?",
        .options = {"NamespaceAdi::isim ya da using namespace NamespaceAdi;", "Sadece isim yazarak", "NamespaceAdi.isim", "NamespaceAdi->isim"},
        .acceptedAnswers = {"a"},
        .explanation = "Nitelenmiş erişim veya using namespace ile erişilebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2048, .topicId = 79,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "namespace A { int x = 1; }\nnamespace B { int x = 2; }\nstd::cout << A::x << B::x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"12\"", "\"11\"", "Derleme hatası", "\"21\""},
        .acceptedAnswers = {"a"},
        .explanation = "A::x=1, B::x=2: '12'.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2049, .topicId = 79,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "İki farklı namespace, aynı isimde bir fonksiyon/değişken tanımlarsa ne olur?",
        .options = {"Çakışma olmaz, her biri kendi namespace'inin kapsamındadır", "Derleme hatası oluşur", "İkincisi birincisini geçersiz kılar", "Sadece ilki kullanılabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "Farklı namespace'lerdeki aynı isimli tanımlar çakışmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2050, .topicId = 79,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "using namespace Matematik; kullanıldıktan sonra kare(4) (önek olmadan) çağrılabilir mi?",
        .options = {"Evet, using namespace, isimleri önek olmadan kullanılabilir hale getirir", "Hayır, hiçbir zaman önek olmadan çağrılamaz", "Hayır, using namespace geçersiz bir sözdizimidir", "Evet ama sadece Matematik::kare olarak"},
        .acceptedAnswers = {"a"},
        .explanation = "using namespace, isimleri önek olmadan kullanılabilir hale getirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2051, .topicId = 79,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "namespace Matematik { int kare(int x) { return x*x; } }\nnamespace Metin { int kare(int x) { return x; } }\nusing namespace Matematik;\nusing namespace Metin;\nstd::cout << kare(4);\nBu kod (her iki namespace de açılmışken önek olmadan kare çağırmak) derlenir mi?",
        .options = {"Hayır, iki namespace'te de kare olduğundan belirsizlik (ambiguous) hatası oluşur", "Evet, Matematik::kare çağrılır", "Evet, Metin::kare çağrılır", "Evet, ikisi de çağrılır"},
        .acceptedAnswers = {"a"},
        .explanation = "Her iki namespace de açık olduğundan çağrı belirsizdir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2052, .topicId = 79,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "namespace Sekiller {\n    namespace Ikili {\n        int cizgiSayisi = 2;\n    }\n}\nstd::cout << Sekiller::Ikili::cizgiSayisi;\nBu, iç içe (nested) namespace kullanımı mıdır ve derlenir mi?",
        .options = {"Evet, iç içe namespace'ler geçerlidir ve Dış::İç::isim şeklinde erişilir", "Hayır, namespace'ler iç içe olamaz", "Hayır, en fazla bir seviye namespace kullanılabilir", "Evet ama farklı bir sözdizimi gerekir"},
        .acceptedAnswers = {"a"},
        .explanation = "İç içe namespace'ler geçerlidir, zincirleme :: ile erişilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2053, .topicId = 79,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "namespace, ilgili isimleri gruplandırıp isim çakışmalarını önler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2054, .topicId = 79,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki farklı namespace, aynı isimde bir fonksiyon tanımlayamaz; bu her zaman derleme hatasıdır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: farklı namespace'ler aynı isimli tanımlara sahip olabilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2055, .topicId = 79,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir namespace içindeki isme NamespaceAdi:: öneki ile erişilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2056, .topicId = 79,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "using namespace ile bir namespace açıldıktan sonra, o namespace'teki isimlere önek olmadan erişilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2057, .topicId = 79,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki farklı namespace aynı anda using namespace ile açılırsa ve ikisinde de aynı isimli bir fonksiyon varsa, önek olmadan çağırmak her zaman sorunsuz çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: bu durumda çağrı belirsiz (ambiguous) olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2058, .topicId = 79,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Namespace'ler iç içe (nested) tanımlanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2059, .topicId = 79,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "İlgili isimleri gruplandırıp isim çakışmalarını önleyen mekanizmaya _____ denir (İngilizce kelime).",
        .acceptedAnswers = {"namespace"},
        .explanation = "Bu mekanizmaya namespace denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2060, .topicId = 79,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "namespace Matematik { int kare(int x) { return x*x; } }\nstd::cout << Matematik::kare(5);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"25"},
        .explanation = "5 * 5 = 25.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2061, .topicId = 79,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir namespace içindeki isme erişmek için kullanılan operatör _____ dir (bir sembol).",
        .acceptedAnswers = {"::"},
        .explanation = "Kapsam çözümleme operatörü (::) kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2062, .topicId = 79,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "İki namespace aynı isimli bir isim tanımlarsa, bunlara nitelenmemiş (önek olmadan) erişmek ve ikisi de using namespace ile açıksa _____ hatası oluşur (İngilizce kelime).",
        .acceptedAnswers = {"ambiguous", "belirsizlik"},
        .explanation = "Bu duruma ambiguous (belirsiz) hata denir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2063, .topicId = 79,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "namespace A { int x = 5; } namespace B { int x = 10; } std::cout << A::x + B::x; Ekran çıktısı _____ olur.",
        .acceptedAnswers = {"15"},
        .explanation = "5 + 10 = 15.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2064, .topicId = 79,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir namespace'in içine başka bir namespace tanımlamaya _____ namespace denir (İngilizce kelime).",
        .acceptedAnswers = {"nested"},
        .explanation = "Bu tür namespace'lere nested (iç içe) denir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2065, .topicId = 79,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << Matematik::kare(6);\nkare(int x) fonksiyonunu x*x döndürecek şekilde, Matematik adlı bir namespace içinde tanımlayan satırları yazın.",
        .acceptedAnswers = {"namespace Matematik { int kare(int x) { return x * x; } }"},
        .explanation = "Fonksiyon, Matematik namespace'i içinde tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2066, .topicId = 79,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "namespace Matematik {\n    int kare(int x) { return x * x; }\n}\n_____\nstd::cout << kare(5);\nMatematik namespace'ini önek olmadan kullanılabilir hale getiren satırı yazın.",
        .acceptedAnswers = {"using namespace Matematik;"},
        .explanation = "using namespace, önek gereksinimini kaldırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2067, .topicId = 79,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "namespace Matematik {\n    int kare(int x) { return x * x; }\n}\nint main() {\n    std::cout << Matematik::kare(7);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"49"},
        .explanation = "7 * 7 = 49.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2068, .topicId = 79,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "namespace A {\n    int deger() { return 10; }\n}\nnamespace B {\n    int deger() { return 20; }\n}\nint main() {\n    std::cout << A::deger() + B::deger();\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30"},
        .explanation = "10 + 20 = 30.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2069, .topicId = 79,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nnamespace Matematik {\n    int kare(int x) { return x * x; }\n}\nint main() {\n    std::cout << kare(4);\n    return 0;\n}\n\nBu kod derlenmez çünkü kare, Matematik:: öneki olmadan ya da using namespace olmadan çağrılamaz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << Matematik::kare(4);"},
        .explanation = "kare, Matematik:: öneki ile nitelenmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2070, .topicId = 79,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nnamespace Matematik {\n    int kare(int x) { return x * x; }\n}\nnamespace Metin {\n    int kare(int x) { return x; }\n}\nusing namespace Matematik;\nusing namespace Metin;\nint main() {\n    std::cout << kare(4);\n    return 0;\n}\n\nBu kod derlenmez çünkü her iki namespace de açık olduğundan kare(4) çağrısı belirsizdir (ambiguous). Hatalı satırı, Matematik::kare kullanarak açıkça nitelenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"std::cout << Matematik::kare(4);"},
        .explanation = "Açık nitelendirme belirsizliği çözer.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2071, .topicId = 79,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nnamespace Matematik {\n    int kare(int x) { return x * x }\n}\n\nProgramcı return x * x satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"int kare(int x) { return x * x; }"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2072, .topicId = 79,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, namespace kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << Matematik::kare(3);\n    return 0;\n}", "namespace Matematik {\n    int kare(int x) { return x * x; }\n}", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "namespace tanımı (2), main açılışı (3), kullanım+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2073, .topicId = 79,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Matematik adlı bir namespace içinde kare(int) adlı bir fonksiyon tanımlayın; main() içinde Matematik:: öneki ile çağırıp sonucu yazdırın.",
        .acceptedAnswers = {"namespace", "Matematik::", "cout"},
        .explanation = "Fonksiyon namespace içinde tanımlanmalı ve nitelenerek çağrılmalıdır.",
        .baseXp = 40,
    });

    // Topic 80: auto
    questions.push_back(Question{
        .id = 2074, .topicId = 80,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "auto anahtar kelimesinin amacı nedir?",
        .options = {"Bir değişkenin türünü, ilklendirildiği ifadeden otomatik olarak çıkarmak", "Bir değişkeni sabit yapmak", "Bir değişkeni silmek", "Bir fonksiyonu virtual yapmak"},
        .acceptedAnswers = {"a"},
        .explanation = "auto, türü ilklendirme ifadesinden çıkarır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2075, .topicId = 80,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "auto x = 5;\nx'in türü nedir?",
        .options = {"int", "double", "auto", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "5 bir int literal olduğundan x'in türü int'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2076, .topicId = 80,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "auto degisken;\nBu kod derlenir mi (ilk değer olmadan)?",
        .options = {"Hayır, auto'nun türü çıkarabilmesi için mutlaka bir ilklendirme gereklidir", "Evet, degisken varsayılan olarak int olur", "Evet, degisken varsayılan olarak 0 olur", "Evet, auto her zaman void olur"},
        .acceptedAnswers = {"a"},
        .explanation = "auto, ilklendirme olmadan türü çıkaramaz; bu bir derleme hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2077, .topicId = 80,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "auto y = 3.14;\ny'nin türü nedir?",
        .options = {"double", "float", "int", "auto"},
        .acceptedAnswers = {"a"},
        .explanation = "3.14 bir double literal olduğundan y'nin türü double'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2078, .topicId = 80,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "auto isim = std::string(\"Merhaba\");\nisim'in türü nedir?",
        .options = {"std::string", "const char*", "auto", "int"},
        .acceptedAnswers = {"a"},
        .explanation = "isim, std::string türünden çıkarılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2079, .topicId = 80,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "auto a = 5;\nauto b = 5.0;\na ve b aynı türde midir?",
        .options = {"Hayır, a int, b double türündedir", "Evet, ikisi de auto türündedir", "Evet, ikisi de double'dır", "Evet, ikisi de int'tir"},
        .acceptedAnswers = {"a"},
        .explanation = "5 int, 5.0 double literal olduğundan a ve b farklı türdedir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2080, .topicId = 80,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "auto x = 10;\nx = 3.14;\nBu kod derlenir mi (x'in türü int iken ona 3.14 atamak)?",
        .options = {"Evet, derlenir ama x'in türü int olduğundan 3.14, 3'e kesilir (truncate)", "Hayır, derleme hatası verir", "Evet, x'in türü otomatik olarak double'a değişir", "Evet, x 3.14 olarak kalır"},
        .acceptedAnswers = {"a"},
        .explanation = "auto ile bir kez belirlenen tür (int) sabittir; sonraki atamalar o türe dönüştürülür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2081, .topicId = 80,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "auto listele() {\n    return 5;\n}\nauto x = listele();\nx'in türü nedir?",
        .options = {"int", "auto", "void", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "C++14'ten itibaren fonksiyonun dönüş türü de auto ile çıkarılabilir; 5 int olduğundan listele()'nin dönüş türü ve x'in türü int'tir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2082, .topicId = 80,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "auto, bir değişkenin türünü ilklendirildiği ifadeden otomatik olarak çıkarır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2083, .topicId = 80,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "auto ile tanımlanan bir değişken, ilk değer olmadan tanımlanabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: auto mutlaka bir ilklendirme gerektirir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 2084, .topicId = 80,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "auto x = 5; ifadesinde x'in türü int olarak çıkarılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2085, .topicId = 80,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "auto kullanmak, değişkenin türünün çalışma zamanında (runtime) belirlenmesi anlamına gelir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: tür derleme zamanında (compile-time) belirlenir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2086, .topicId = 80,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "auto a = 5; auto b = 5.0; a ve b aynı türdedir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: a int, b double'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2087, .topicId = 80,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyonun dönüş türü de auto ile otomatik olarak çıkarılabilir (C++14 itibarıyla).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2088, .topicId = 80,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir değişkenin türünü ilklendirildiği ifadeden çıkarmak için _____ anahtar kelimesi kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"auto"},
        .explanation = "auto anahtar kelimesi kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2089, .topicId = 80,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "auto x = 7;\nx'in türü _____ olarak çıkarılır (İngilizce kelime).",
        .acceptedAnswers = {"int"},
        .explanation = "7 bir int literal olduğundan x int'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2090, .topicId = 80,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "auto degisken; şeklinde ilk değer vermeden tanımlamak _____ verir (Türkçe kelime).",
        .acceptedAnswers = {"hata", "derleme hatası"},
        .explanation = "Bu bir derleme hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2091, .topicId = 80,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "auto y = 2.71;\ny'nin türü _____ olarak çıkarılır (İngilizce kelime).",
        .acceptedAnswers = {"double"},
        .explanation = "2.71 bir double literal olduğundan y double'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2092, .topicId = 80,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "auto'nun türü çıkarabilmesi için bir değişken mutlaka bir _____ ile tanımlanmalıdır (İngilizce kelime).",
        .acceptedAnswers = {"initializer"},
        .explanation = "Bir initializer (ilklendirici) gereklidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2093, .topicId = 80,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "auto türü, derleme _____ (compile-time) belirlenir, çalışma zamanında değil (Türkçe kelime).",
        .acceptedAnswers = {"zamanında"},
        .explanation = "Tür derleme zamanında belirlenir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2094, .topicId = 80,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << x;\nx adlı bir değişkeni 42 değeriyle, türünü auto ile çıkararak tanımlayan satırı yazın.",
        .acceptedAnswers = {"auto x = 42;"},
        .explanation = "x'in türü 42'den int olarak çıkarılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2095, .topicId = 80,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "auto isim = std::string(\"Merhaba\");\n_____\nisim değişkenini ekrana yazdıran satırı yazın.",
        .acceptedAnswers = {"std::cout << isim;"},
        .explanation = "isim değişkeni doğrudan yazdırılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2096, .topicId = 80,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int main() {\n    auto x = 100;\n    auto y = 2.5;\n    std::cout << x << \" \" << y;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"100 2.5"},
        .explanation = "x=100 (int), y=2.5 (double).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2097, .topicId = 80,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int main() {\n    auto a = 3;\n    auto b = 4.0;\n    std::cout << a + b;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"7"},
        .explanation = "a (int) + b (double) işlemi double'a yükseltilir: 3+4.0=7.0, cout '7' yazdırır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2098, .topicId = 80,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint main() {\n    auto x;\n    x = 5;\n    return 0;\n}\n\nBu kod derlenmez çünkü auto ile tanımlanan bir değişken mutlaka bir ilk değerle tanımlanmalıdır. Hatalı satırı, ilk değer eklenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"auto x = 5;"},
        .explanation = "auto, ilklendirme olmadan türü çıkaramaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2099, .topicId = 80,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint main() {\n    auto x = 5;\n    auto x = 10;\n    return 0;\n}\n\nBu kod derlenmez çünkü aynı kapsamda x adlı bir değişken iki kez tanımlanmış (yeniden tanımlama). İkinci satırı, x'e sadece yeni bir değer atayan (yeniden tanımlamadan) haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"x = 10;"},
        .explanation = "Aynı değişken tekrar tanımlanamaz, sadece değer atanabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2100, .topicId = 80,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint main() {\n    auto x = 5\n    return 0;\n}\n\nProgramcı auto x = 5 satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"auto x = 5;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2101, .topicId = 80,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, auto kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"auto x = 15;", "std::cout << x;\n    return 0;\n}", "int main() {"},
        .acceptedAnswers = {"3 1 2"},
        .explanation = "main açılışı (3), auto tanımı (1), yazdırma+kapanış (2): sıra 3 1 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2102, .topicId = 80,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "auto kullanarak bir int, bir double ve bir std::string değişkeni tanımlayın; main() içinde üçünü de ekrana yazdırın.",
        .acceptedAnswers = {"auto", "cout"},
        .explanation = "Her üç değişken de auto ile tanımlanıp yazdırılmalıdır.",
        .baseXp = 40,
    });
}
```

- [ ] **Step 2: Add a per-topic minimum-count test**

In `tests/QuestionManagerTests.cpp`, add this new test case right after
`QuestionManager_EveryTopicSixtyOneToSeventyHasAtLeastTwentyNineQuestions`
(do not modify that existing test, and do not touch
`QuestionManager_NoDuplicateQuestionIds`, which already scans topics
1-100):

```cpp
TEST_CASE(QuestionManager_EveryTopicSeventyOneToEightyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 71; topicId <= 80; ++topicId) {
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
Expected: `95/95 test(s) passed.` (94 from Task 1's end state + 1 new
test).

Run from `build/`: `ctest -C Debug --output-on-failure`
Expected: 100% pass.

- [ ] **Step 4: Manual verification — topic 74 end-to-end**

Run the app (`./build/Debug/CppMasterConsole.exe`), navigate to the
topic browser, choose Section 8, choose topic 74 ("Polimorfizm"):

1. Confirm the lesson text prints (matches the `explanation`/`syntax`/
   `exampleCode` written in Task 1) — proving `openTopic`'s content gate
   passes for topic 74 with zero `Application.cpp` changes.
2. Confirm "Konu testi başlıyor (29 soru)." prints.
3. Answer a few questions (any answers), then use `cikis` to return to
   the main menu.
4. Confirm the app returns to the main menu without crashing, and that
   partial XP is awarded.
5. Clean up: `rm -f data/*.txt`.

- [ ] **Step 5: Commit the question content and test changes**

```bash
git add src/QuestionsSection8.cpp tests/QuestionManagerTests.cpp
git commit -m "feat(content): add questions for topics 78-80 (ids 2016-2102), widen coverage tests"
```

- [ ] **Step 6: Update the roadmap**

In `docs/superpowers/roadmap.md`, add a new bullet for Phase 19 under
"Phase order," immediately after the Phase 18 entry, following the
EXACT format Phases 8-18 use
(`**Phase N — name: COMPLETE** (commits \`X..Y\`, ...)`), with the
commit range starting at this phase's spec commit (the commit for "Add
design spec for Bölüm 8 İçerik Genişletmesi (phase 19)") and ending at
this task's final content commit (from Step 5 above). Update the
"Status" section to say Phase 19 is complete and Phase 20 (Section 9
content) starts next.

Then commit:

```bash
git add docs/superpowers/roadmap.md
git commit -m "docs: mark Phase 19 complete in roadmap"
```

---

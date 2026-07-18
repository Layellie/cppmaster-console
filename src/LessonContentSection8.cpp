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

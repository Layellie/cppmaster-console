#include "LessonContent.h"

#include "Lesson.h"

void applySection7LessonContent(std::vector<Lesson>& lessons) {
    // Index 60 = topic id 61 (struct), index 69 = topic id 70
    // (protected) — same positional convention as
    // applyIntroLessonContent/applySection2-6LessonContent.

    lessons[60].explanation =
        "struct anahtar kelimesi, C++'ta bir sınıf (class) tanımlamanın "
        "başka bir yoludur. class'tan tek farkı, üyelerinin (fields/"
        "methods) varsayılan erişim belirleyicisidir: struct üyeleri "
        "varsayılan olarak public'tir (class'ta ise private'tir). "
        "struct da tıpkı class gibi constructor, destructor, metot ve "
        "kalıtım içerebilir.";
    lessons[60].syntax = "struct YapiAdi {\n    tur uye1;\n    tur uye2;\n};";
    lessons[60].exampleCode =
        "#include <iostream>\n\n"
        "struct Nokta {\n"
        "    int x;\n"
        "    int y;\n"
        "};\n\n"
        "int main() {\n"
        "    Nokta p;\n"
        "    p.x = 3;\n"
        "    p.y = 4;\n"
        "    std::cout << p.x << \" \" << p.y;\n"
        "    return 0;\n"
        "}";
    lessons[60].lineExplanations = {
        "struct Nokta { ... }; : x ve y üyeleri varsayılan olarak "
        "public'tir, dışarıdan doğrudan erişilebilir.",
        "p.x = 3; : struct üyesine noktalı erişimle doğrudan atama "
        "yapılabilir (public olduğu için)."};
    lessons[60].commonMistakes = {
        "struct'ın sadece veri (data) tutabileceğini, metot veya "
        "constructor içeremeyeceğini sanmak yaygın bir yanılgıdır — "
        "C++'ta struct, class ile aynı yeteneklere sahiptir, tek fark "
        "varsayılan erişim belirleyicisidir.",
    };

    lessons[61].explanation =
        "enum (enumeration), adlandırılmış tam sayı sabitlerinden oluşan "
        "bir küme tanımlar. Varsayılan olarak ilk değer 0'dır, "
        "sonrakiler birer birer artar (aksi belirtilmedikçe). Bir enum "
        "değeri, int'e örtük olarak (implicit) dönüştürülebilir ve enum "
        "içindeki isimler, kapsayan (enclosing) kapsamda doğrudan "
        "görünür olur.";
    lessons[61].syntax = "enum EnumAdi { Deger1, Deger2, Deger3 };";
    lessons[61].exampleCode =
        "#include <iostream>\n\n"
        "enum Renk { Kirmizi, Yesil, Mavi };\n\n"
        "int main() {\n"
        "    Renk r = Yesil;\n"
        "    std::cout << r;\n"
        "    return 0;\n"
        "}";
    lessons[61].lineExplanations = {
        "enum Renk { ... }; : Kirmizi=0, Yesil=1, Mavi=2 olarak otomatik "
        "numaralandırılır.",
        "std::cout << r; : enum değeri int'e örtük dönüştüğü için "
        "sayısal değeri (1) yazdırılır."};
    lessons[61].commonMistakes = {
        "Farklı iki enum'da aynı isimli bir değer (örneğin ikisinde de "
        "Kirmizi) tanımlamak, aynı kapsamda isim çakışmasına (derleme "
        "hatasına) yol açar — bu, enum class'ın (bir sonraki konu) "
        "çözdüğü problemdir.",
    };

    lessons[62].explanation =
        "enum class (scoped enum), C++11 ile gelen, enum'ın isim "
        "çakışması sorununu çözen bir versiyondur. Değerlerine her "
        "zaman enum adıyla nitelenerek (EnumAdi::Deger şeklinde) "
        "erişilir ve int'e örtük olarak dönüşmez (gerekiyorsa "
        "static_cast<int> ile açıkça dönüştürülmelidir).";
    lessons[62].syntax = "enum class EnumAdi { Deger1, Deger2, Deger3 };";
    lessons[62].exampleCode =
        "#include <iostream>\n\n"
        "enum class Renk { Kirmizi, Yesil, Mavi };\n\n"
        "int main() {\n"
        "    Renk r = Renk::Yesil;\n"
        "    std::cout << static_cast<int>(r);\n"
        "    return 0;\n"
        "}";
    lessons[62].lineExplanations = {
        "Renk r = Renk::Yesil; : değere mutlaka Renk:: öneki ile "
        "erişilir.",
        "static_cast<int>(r) : enum class değerleri int'e örtük "
        "dönüşmediği için açık dönüştürme (static_cast) gerekir."};
    lessons[62].commonMistakes = {
        "enum class bir değere Renk:: öneki olmadan (sadece Yesil "
        "yazarak) erişmeye çalışmak derleme hatasıdır.",
        "enum class değerini örtük olarak int'e atamaya çalışmak (int "
        "x = r;, static_cast olmadan) da derleme hatasıdır.",
    };

    lessons[63].explanation =
        "Bir sınıf (class), bir nesnenin (object) sahip olacağı veri ve "
        "davranışları tanımlayan bir şablondur (blueprint). Bir nesne, "
        "o sınıfın somut bir örneğidir (instance). class üyeleri "
        "varsayılan olarak private'tir (struct'ın aksine).";
    lessons[63].syntax =
        "class SinifAdi {\nprivate:\n    tur uye;\npublic:\n    "
        "metotlar\n};";
    lessons[63].exampleCode =
        "#include <iostream>\n\n"
        "class Araba {\npublic:\n"
        "    int hiz;\n\n"
        "    void hizlan() {\n"
        "        hiz = hiz + 10;\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Araba a;\n"
        "    a.hiz = 0;\n"
        "    a.hizlan();\n"
        "    std::cout << a.hiz;\n"
        "    return 0;\n"
        "}";
    lessons[63].lineExplanations = {
        "class Araba { ... }; : Araba sınıfı bir hiz üyesi ve bir "
        "hizlan() metodu tanımlar.",
        "Araba a; : a, Araba sınıfının somut bir nesnesidir (instance)."};
    lessons[63].commonMistakes = {
        "class üyelerinin varsayılan olarak public olduğunu sanmak "
        "yaygın bir hatadır; class'ta varsayılan erişim private'tir "
        "(struct'ta ise public'tir).",
    };

    lessons[64].explanation =
        "Constructor (yapıcı), bir sınıfın nesnesi oluşturulduğunda "
        "otomatik olarak çağrılan, sınıfla aynı isme sahip özel bir "
        "metottur. Dönüş türü yoktur (void bile yazılmaz). Bir sınıfta "
        "birden fazla constructor (farklı parametre listeleriyle, "
        "overload edilmiş) olabilir. Eğer programcı hiçbir constructor "
        "tanımlamazsa derleyici parametre almayan bir varsayılan "
        "constructor otomatik oluşturur; ama programcı EN AZ BİR "
        "constructor tanımlarsa (parametreli olsun), derleyici artık "
        "varsayılan constructor'ı otomatik oluşturmaz.";
    lessons[64].syntax = "SinifAdi(parametreler) {\n    ilklendirme;\n}";
    lessons[64].exampleCode =
        "#include <iostream>\n\n"
        "class Nokta {\npublic:\n"
        "    int x;\n"
        "    int y;\n\n"
        "    Nokta(int xDeger, int yDeger) {\n"
        "        x = xDeger;\n"
        "        y = yDeger;\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Nokta p(3, 4);\n"
        "    std::cout << p.x << \" \" << p.y;\n"
        "    return 0;\n"
        "}";
    lessons[64].lineExplanations = {
        "Nokta(int xDeger, int yDeger) { ... } : Nokta sınıfıyla aynı "
        "isimli, dönüş türü olmayan constructor.",
        "Nokta p(3, 4); : nesne oluşturulurken constructor otomatik "
        "çağrılır, x ve y ilklendirilir."};
    lessons[64].commonMistakes = {
        "Bir sınıfta sadece parametreli bir constructor tanımlanırsa "
        "(Nokta(int,int) gibi), Nokta p; (parametresiz) şeklinde bir "
        "nesne oluşturmak artık derleme hatası verir — çünkü derleyici, "
        "programcı en az bir constructor tanımladığı için varsayılan "
        "constructor'ı otomatik oluşturmaz; parametresiz oluşturma da "
        "isteniyorsa ayrıca bir varsayılan constructor tanımlanmalıdır.",
    };

    lessons[65].explanation =
        "Destructor (yıkıcı), bir nesne kapsamından çıktığında (scope "
        "sonunda) ya da delete ile silindiğinde otomatik olarak "
        "çağrılan, sınıf adının başına ~ konularak yazılan özel bir "
        "metottur. Parametre almaz ve dönüş türü yoktur. Bir sınıfın "
        "sadece BİR destructor'ı olabilir; constructor'ların aksine "
        "overload edilemez (parametre alamadığı için farklı bir imzaya "
        "sahip olamaz).";
    lessons[65].syntax = "~SinifAdi() {\n    temizlik;\n}";
    lessons[65].exampleCode =
        "#include <iostream>\n\n"
        "class Kaynak {\npublic:\n"
        "    Kaynak() {\n"
        "        std::cout << \"Olusturuldu \";\n"
        "    }\n"
        "    ~Kaynak() {\n"
        "        std::cout << \"Yok edildi \";\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Kaynak k;\n"
        "    std::cout << \"Ana govde \";\n"
        "    return 0;\n"
        "}";
    lessons[65].lineExplanations = {
        "Kaynak k; : constructor çağrılır, \"Olusturuldu\" yazdırılır.",
        "main() sonlanırken k kapsamdan çıkar, destructor otomatik "
        "çağrılır, \"Yok edildi\" yazdırılır (main gövdesindeki diğer "
        "kodlardan SONRA)."};
    lessons[65].commonMistakes = {
        "new ile heap'te oluşturulan bir nesnenin pointer'ı delete "
        "edilmezse, o nesnenin destructor'ı hiç çağrılmaz (bellek "
        "sızıntısına ek olarak, destructor'ın yapması gereken temizlik "
        "de hiç yapılmamış olur).",
        "Destructor'ın overload edilebileceğini (parametre alan farklı "
        "versiyonları olabileceğini) sanmak yanlıştır; bir sınıfın "
        "sadece bir destructor'ı olabilir.",
    };

    lessons[66].explanation =
        "private erişim belirleyicisiyle işaretlenen üyelere sadece "
        "sınıfın kendi metotları içinden erişilebilir; sınıf dışından "
        "(örneğin main() içinden) erişmeye çalışmak derleme hatasıdır. "
        "public erişim belirleyicisiyle işaretlenen üyelere ise her "
        "yerden erişilebilir.";
    lessons[66].syntax =
        "class SinifAdi {\nprivate:\n    tur ozelUye;\npublic:\n    tur "
        "herkeseAcikUye;\n};";
    lessons[66].exampleCode =
        "#include <iostream>\n\n"
        "class Hesap {\nprivate:\n"
        "    int bakiye;\n\n"
        "public:\n"
        "    void bakiyeAta(int deger) {\n"
        "        bakiye = deger;\n"
        "    }\n"
        "    int bakiyeGetir() {\n"
        "        return bakiye;\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Hesap h;\n"
        "    h.bakiyeAta(100);\n"
        "    std::cout << h.bakiyeGetir();\n"
        "    return 0;\n"
        "}";
    lessons[66].lineExplanations = {
        "private: int bakiye; : bakiye sadece Hesap sınıfının kendi "
        "metotları içinden erişilebilir.",
        "h.bakiyeAta(100); : bakiye'ye dışarıdan doğrudan değil, public "
        "bir metot üzerinden erişilir."};
    lessons[66].commonMistakes = {
        "h.bakiye = 100; şeklinde private bir üyeye sınıf dışından "
        "doğrudan erişmeye çalışmak derleme hatasıdır; bunun yerine "
        "public bir metot (setter) üzerinden erişilmelidir.",
    };

    lessons[67].explanation =
        "Getter ve setter, private bir üyeye kontrollü erişim sağlamak "
        "için yazılan public metotlardır. Bir getter, private üyenin "
        "değerini okuyup döndürür; bir setter, private üyeye (genellikle "
        "geçerlilik kontrolüyle) yeni bir değer atar. Bu, üyeyi "
        "doğrudan public yapmak yerine, üyeye nasıl erişileceği "
        "üzerinde kontrol sağlar.";
    lessons[67].syntax =
        "int getUye() { return uye; }\nvoid setUye(int deger) { uye = "
        "deger; }";
    lessons[67].exampleCode =
        "#include <iostream>\n\n"
        "class Ogrenci {\nprivate:\n"
        "    int yas;\n\n"
        "public:\n"
        "    int getYas() {\n"
        "        return yas;\n"
        "    }\n"
        "    void setYas(int deger) {\n"
        "        if (deger > 0) {\n"
        "            yas = deger;\n"
        "        }\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Ogrenci o;\n"
        "    o.setYas(20);\n"
        "    std::cout << o.getYas();\n"
        "    return 0;\n"
        "}";
    lessons[67].lineExplanations = {
        "setYas(int deger) { ... } : yeni değer atanmadan önce "
        "geçerlilik kontrolü (deger > 0) yapılabilir.",
        "getYas() : private yas üyesinin değerini dışarıya güvenle "
        "sunar."};
    lessons[67].commonMistakes = {
        "Bir setter'da geçerlilik kontrolü yapmadan doğrudan atama "
        "yapmak (if kontrolünü atlamak), private üyeyi public yapmaktan "
        "farksız hale getirir; setter'ların asıl amacı bu tür "
        "kontrolleri uygulayabilmektir.",
    };

    lessons[68].explanation =
        "Kalıtım (inheritance), bir sınıfın (türetilmiş/derived sınıf) "
        "başka bir sınıfın (taban/base sınıf) üyelerini devralmasını "
        "sağlar. class Turetilmis : public Taban { ... } şeklinde "
        "tanımlanır. Bir nesne oluşturulduğunda önce taban sınıfın "
        "constructor'ı, sonra türetilmiş sınıfın constructor'ı çalışır; "
        "nesne yok edilirken bu sıra tam tersine döner (önce türetilmiş "
        "sınıfın destructor'ı, sonra taban sınıfın destructor'ı çalışır).";
    lessons[68].syntax = "class Turetilmis : public Taban {\n    ek uyeler;\n};";
    lessons[68].exampleCode =
        "#include <iostream>\n\n"
        "class Hayvan {\npublic:\n"
        "    Hayvan() {\n"
        "        std::cout << \"Hayvan \";\n"
        "    }\n"
        "};\n\n"
        "class Kopek : public Hayvan {\npublic:\n"
        "    Kopek() {\n"
        "        std::cout << \"Kopek \";\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Kopek k;\n"
        "    return 0;\n"
        "}";
    lessons[68].lineExplanations = {
        "class Kopek : public Hayvan { ... } : Kopek, Hayvan'dan "
        "türetilir.",
        "Kopek k; : önce Hayvan'ın constructor'ı (\"Hayvan \"), sonra "
        "Kopek'in kendi constructor'ı (\"Kopek \") çalışır."};
    lessons[68].commonMistakes = {
        "Taban sınıfın private üyelerinin türetilmiş sınıf tarafından "
        "doğrudan erişilebileceğini sanmak yanlıştır; private üyeler "
        "türetilmiş sınıfta bile doğrudan erişilemez (bunun için "
        "protected kullanılmalıdır).",
    };

    lessons[69].explanation =
        "protected erişim belirleyicisiyle işaretlenen üyeler, sınıfın "
        "dışından private gibi erişilemez, ama türetilmiş (derived) "
        "sınıfların kendi metotları içinden doğrudan erişilebilir. Bu, "
        "private (hiçbir yerden, türetilmiş sınıflar dahil, dışarıdan "
        "erişilemez) ile public (her yerden erişilebilir) arasında bir "
        "orta yoldur.";
    lessons[69].syntax = "class Taban {\nprotected:\n    tur korunanUye;\n};";
    lessons[69].exampleCode =
        "#include <iostream>\n\n"
        "class Hayvan {\nprotected:\n"
        "    int yas;\n\n"
        "public:\n"
        "    void yasAta(int deger) {\n"
        "        yas = deger;\n"
        "    }\n"
        "};\n\n"
        "class Kopek : public Hayvan {\npublic:\n"
        "    void yasGoster() {\n"
        "        std::cout << yas;\n"
        "    }\n"
        "};\n\n"
        "int main() {\n"
        "    Kopek k;\n"
        "    k.yasAta(3);\n"
        "    k.yasGoster();\n"
        "    return 0;\n"
        "}";
    lessons[69].lineExplanations = {
        "protected: int yas; : yas, Hayvan dışından erişilemez ama "
        "Kopek (türetilmiş sınıf) içinden erişilebilir.",
        "void yasGoster() { std::cout << yas; } : Kopek, taban sınıfın "
        "protected üyesine doğrudan erişebilir."};
    lessons[69].commonMistakes = {
        "main() içinden k.yas şeklinde doğrudan erişmeye çalışmak "
        "(protected bir üyeye sınıf dışından erişim) derleme hatasıdır; "
        "protected sadece türetilmiş sınıflara izin verir, dış koda "
        "değil.",
    };
}

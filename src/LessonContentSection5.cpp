#include "LessonContent.h"

#include "Lesson.h"

void applySection5LessonContent(std::vector<Lesson>& lessons) {
    // Index 40 = topic id 41 (Parametresiz fonksiyon), index 49 = topic
    // id 50 (Recursion) — same positional convention as
    // applyIntroLessonContent/applySection2-4LessonContent.

    lessons[40].explanation =
        "Parametresiz bir fonksiyon, herhangi bir girdi (parametre) "
        "almayan bir fonksiyondur. Fonksiyon tanımı, dönüş "
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

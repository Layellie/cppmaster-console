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
        "std::array'in boyutunun da std::vector gibi çalışma zamanında "
        "değiştirilebileceğini sanmak (std::array'in boyutu, C-style "
        "diziler gibi, derleme zamanında sabittir).",
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
        "sayilar.size() ve sayilar[0] : sayilar.size() 1, sayilar[0] "
        "hala 1'dir.",
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

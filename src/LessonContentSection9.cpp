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

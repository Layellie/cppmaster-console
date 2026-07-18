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

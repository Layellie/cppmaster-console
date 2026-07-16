#include "LessonContent.h"

#include "Lesson.h"

void applySection3LessonContent(std::vector<Lesson>& lessons) {
    // Index 20 = topic id 21 (switch-case), index 29 = topic id 30
    // (Faktöriyel hesaplama) — same positional convention as
    // applyIntroLessonContent/applySection2LessonContent.

    lessons[20].explanation =
        "switch-case yapısı, bir değişkenin farklı değerlerine göre "
        "farklı kod bloklarının çalışmasını sağlar. Uzun bir if-else if "
        "zincirine göre, tek bir değişkenin sabit değerlerle "
        "karşılaştırıldığı durumlarda daha okunaklıdır. Her case "
        "bloğunun sonuna break konulmazsa, kod bir sonraki case'e "
        "\"düşer\" (fall-through) ve o blok da çalışır.";
    lessons[20].syntax =
        "switch (deger) {\n    case 1:\n        // ...\n        break;\n    default:\n        // ...\n}";
    lessons[20].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int gun = 3;\n"
        "    switch (gun) {\n"
        "        case 1:\n"
        "            std::cout << \"Pazartesi\";\n"
        "            break;\n"
        "        case 2:\n"
        "            std::cout << \"Salı\";\n"
        "            break;\n"
        "        case 3:\n"
        "            std::cout << \"Çarşamba\";\n"
        "            break;\n"
        "        default:\n"
        "            std::cout << \"Bilinmeyen gün\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[20].lineExplanations = {
        "switch (gun) : gun değişkeninin değerine göre uygun case'e "
        "atlar.",
        "case 3: : gun 3 olduğu için bu blok çalışır ve 'Çarşamba' "
        "yazdırılır.",
        "break; : Eşleşen case'in kodu çalıştıktan sonra switch "
        "bloğundan çıkılmasını sağlar.",
    };
    lessons[20].commonMistakes = {
        "case bloklarının sonuna break koymayı unutmak (bu, istenmeyen "
        "fall-through'a yol açar).",
        "switch'in yalnızca tam sayı ve karakter gibi ayrık (discrete) "
        "değerlerle çalıştığını, aralık (örneğin 1-10) kontrolü "
        "yapamayacağını unutmak.",
        "default bloğunu eklemeyi unutmak (hiçbir case eşleşmezse "
        "hiçbir şey çalışmaz).",
    };

    lessons[21].explanation =
        "for döngüsü, belirli bir sayıda tekrar yapılacağı bilinen "
        "durumlarda kullanılır. Üç bölümden oluşur: başlangıç (bir kez "
        "çalışır), koşul (her turda kontrol edilir) ve artırma/azaltma "
        "(her turun sonunda çalışır). Koşul false olduğunda döngü sona "
        "erer.";
    lessons[21].syntax = "for (int i = 0; i < n; i++) {\n    // ...\n}";
    lessons[21].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    for (int i = 1; i <= 5; i++) {\n"
        "        std::cout << i << \" \";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[21].lineExplanations = {
        "int i = 1 : Sayaç 1 değeriyle başlatılır (yalnızca bir kez "
        "çalışır).",
        "i <= 5 : Her turdan önce kontrol edilir; true olduğu sürece "
        "döngü devam eder.",
        "i++ : Her turun sonunda sayaç 1 artırılır.",
    };
    lessons[21].commonMistakes = {
        "Koşulu yanlış kurup bir fazla veya bir eksik tur çalıştırmak "
        "(off-by-one hatası).",
        "Döngü içinde sayacı değiştirip beklenmedik davranışa yol "
        "açmak.",
        "Noktalı virgülleri unutmak (for döngüsünün üç bölümü ; ile "
        "ayrılır).",
    };

    lessons[22].explanation =
        "while döngüsü, koşul true olduğu sürece tekrar eden bir "
        "döngüdür; tekrar sayısı önceden bilinmeyebilir. Koşul döngüye "
        "girmeden önce kontrol edilir; başlangıçta false ise döngü hiç "
        "çalışmaz.";
    lessons[22].syntax = "while (kosul) {\n    // ...\n}";
    lessons[22].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int sayac = 1;\n"
        "    while (sayac <= 3) {\n"
        "        std::cout << sayac << \" \";\n"
        "        sayac++;\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[22].lineExplanations = {
        "while (sayac <= 3) : sayac 3'ten büyük olana kadar döngü "
        "devam eder.",
        "sayac++; : Döngünün sonsuza gitmemesi için sayacın her turda "
        "artırılması gerekir.",
    };
    lessons[22].commonMistakes = {
        "Döngü içinde koşulu değiştiren kodu (örneğin sayac++) "
        "eklemeyi unutup sonsuz döngüye girmek.",
        "Koşulun başlangıçta false olabileceğini (ve döngünün hiç "
        "çalışmayabileceğini) gözden kaçırmak.",
        "while ile do-while'ı karıştırmak (while koşulu önce kontrol "
        "eder, do-while sonra).",
    };

    lessons[23].explanation =
        "do-while döngüsü, while'a benzer ancak koşulu döngü gövdesi "
        "çalıştıktan SONRA kontrol eder. Bu yüzden gövde, koşul "
        "başlangıçta false olsa bile en az bir kez çalışır. "
        "Kullanıcıdan en az bir kez giriş almak istendiğinde (örneğin "
        "bir menü) sıkça kullanılır.";
    lessons[23].syntax = "do {\n    // en az bir kez calisir\n} while (kosul);";
    lessons[23].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int sayi;\n"
        "    do {\n"
        "        std::cout << \"Pozitif bir sayı girin: \";\n"
        "        std::cin >> sayi;\n"
        "    } while (sayi <= 0);\n"
        "    return 0;\n"
        "}";
    lessons[23].lineExplanations = {
        "do { ... } : Bu blok, koşul kontrol edilmeden önce en az bir "
        "kez çalışır.",
        "while (sayi <= 0); : Kullanıcı pozitif bir sayı girene kadar "
        "döngü tekrar eder; sonunda noktalı virgül gerekir.",
    };
    lessons[23].commonMistakes = {
        "while (kosul) satırının sonuna noktalı virgül koymayı unutmak "
        "(do-while'da bu zorunludur, normal while'da yoktur).",
        "do-while'ın da while gibi koşulu önce kontrol ettiğini "
        "sanmak (aslında sonra kontrol eder).",
        "Gövde içinde koşulu güncelleyen kodu unutup sonsuz döngüye "
        "girmek.",
    };

    lessons[24].explanation =
        "break ifadesi, içinde bulunduğu en yakın (innermost) döngüyü "
        "veya switch bloğunu anında sonlandırır. Döngünün geri kalan "
        "turları hiç çalışmaz; kontrol döngüden hemen sonraki koda "
        "geçer. İç içe döngülerde break yalnızca içinde bulunduğu en "
        "yakın döngüyü etkiler, dıştaki döngüyü etkilemez.";
    lessons[24].syntax = "for (...) {\n    if (kosul) {\n        break;\n    }\n}";
    lessons[24].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    for (int i = 1; i <= 10; i++) {\n"
        "        if (i == 4) {\n"
        "            break;\n"
        "        }\n"
        "        std::cout << i << \" \";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[24].lineExplanations = {
        "if (i == 4) : i 4'e ulaştığında bu koşul true olur.",
        "break; : Döngü anında sonlanır; 4 ve sonrasındaki sayılar "
        "hiç yazdırılmaz (çıktı: 1 2 3).",
    };
    lessons[24].commonMistakes = {
        "break'in tüm iç içe döngüleri birden sonlandıracağını sanmak "
        "(yalnızca en yakın döngüyü sonlandırır).",
        "break'i switch dışında bir if bloğunda kullanıp döngüyü "
        "değil de yanlışlıkla switch'i sonlandırmayı beklemek.",
        "break kullanmanın döngü sayacını da sıfırladığını sanmak "
        "(yalnızca döngüden çıkar, değişken değerleri korunur).",
    };

    lessons[25].explanation =
        "continue ifadesi, döngünün geri kalan kısmını atlayıp "
        "doğrudan bir sonraki tura geçmeyi sağlar (for döngüsünde "
        "artırma adımı yine de çalışır). break'ten farklı olarak "
        "döngüyü tamamen sonlandırmaz, sadece o turun geri kalanını "
        "atlar.";
    lessons[25].syntax = "for (...) {\n    if (kosul) {\n        continue;\n    }\n}";
    lessons[25].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    for (int i = 1; i <= 5; i++) {\n"
        "        if (i % 2 == 0) {\n"
        "            continue;\n"
        "        }\n"
        "        std::cout << i << \" \";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[25].lineExplanations = {
        "if (i % 2 == 0) : i çift olduğunda bu koşul true olur.",
        "continue; : O turun geri kalanı atlanır; cout satırı "
        "çalışmaz. Çıktı yalnızca tek sayıları içerir: 1 3 5.",
    };
    lessons[25].commonMistakes = {
        "continue'nun döngüyü tamamen sonlandırdığını sanmak (break "
        "ile karıştırmak); aslında sadece o turu atlar.",
        "continue'dan sonra artırma adımının (i++) çalışmayacağını "
        "sanmak (for döngüsünde artırma adımı continue'dan sonra da "
        "çalışır).",
        "while döngüsünde continue kullanırken koşulu güncelleyen "
        "satırı continue'dan önce yazmayı unutup sonsuz döngüye "
        "girmek.",
    };

    lessons[26].explanation =
        "Bir döngünün içine başka bir döngü yazılmasına iç içe "
        "(nested) döngü denir. Dıştaki döngü her bir turunda, içteki "
        "döngü baştan sona kadar tamamen çalışır. Örneğin bir tablo "
        "veya matris üzerinde satır/sütun dolaşırken sıkça kullanılır.";
    lessons[26].syntax =
        "for (int i = 0; i < n; i++) {\n    for (int j = 0; j < m; j++) {\n        // ...\n    }\n}";
    lessons[26].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    for (int i = 1; i <= 2; i++) {\n"
        "        for (int j = 1; j <= 3; j++) {\n"
        "            std::cout << i << \"-\" << j << \" \";\n"
        "        }\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[26].lineExplanations = {
        "for (int i = 1; i <= 2; i++) : Dış döngü 2 kez çalışır "
        "(i = 1, i = 2).",
        "for (int j = 1; j <= 3; j++) : Her dış tur için iç döngü "
        "baştan sona (3 kez) çalışır.",
        "Toplamda 2 * 3 = 6 çıktı üretilir: 1-1 1-2 1-3 2-1 2-2 2-3.",
    };
    lessons[26].commonMistakes = {
        "İç ve dış döngülerin sayaç değişkenlerini (i, j) karıştırmak.",
        "İç içe döngülerin toplam tekrar sayısını (dış * iç) "
        "hesaplarken yanlış çarpmak.",
        "break/continue'nun yalnızca içinde bulunduğu en yakın "
        "döngüyü etkilediğini unutup dış döngüyü de etkileyeceğini "
        "sanmak.",
    };

    lessons[27].explanation =
        "Range-based for (aralık tabanlı for), bir dizi, vector veya "
        "string gibi bir koleksiyonun her elemanını sırayla dolaşmak "
        "için kullanılan sadeleştirilmiş bir for söz dizimidir. "
        "for (tur : koleksiyon) şeklinde yazılır. Eleman bir kopya "
        "olarak alınır; koleksiyonu değiştirmek isteniyorsa referans "
        "(&) kullanılmalıdır.";
    lessons[27].syntax = "for (int deger : vektor) {\n    // ...\n}";
    lessons[27].exampleCode =
        "#include <iostream>\n"
        "#include <vector>\n\n"
        "int main() {\n"
        "    std::vector<int> sayilar = {1, 2, 3};\n"
        "    for (int sayi : sayilar) {\n"
        "        std::cout << sayi << \" \";\n"
        "    }\n"
        "    for (int& sayi : sayilar) {\n"
        "        sayi *= 2;\n"
        "    }\n"
        "    std::cout << sayilar[0];\n"
        "    return 0;\n"
        "}";
    lessons[27].lineExplanations = {
        "for (int sayi : sayilar) : Her elemanı bir KOPYA olarak "
        "sayi değişkenine alır; sayilar değişmez.",
        "for (int& sayi : sayilar) : & ile referans alındığı için "
        "sayi üzerindeki değişiklik (sayi *= 2) gerçek elemanı da "
        "değiştirir.",
        "sayilar[0] artık 2'dir çünkü referanslı döngü her elemanı 2 "
        "ile çarptı.",
    };
    lessons[27].commonMistakes = {
        "Koleksiyonu değiştirmek isterken & (referans) kullanmayı "
        "unutup değişikliklerin bir kopya üzerinde kaybolduğunu fark "
        "etmemek.",
        "Range-based for içinde geleneksel bir index (i) değişkeni "
        "olmadığını unutup elemanın konumuna erişmeye çalışmak.",
        "Döngü sırasında koleksiyonun boyutunu değiştirmek (örneğin "
        "eleman eklemek/silmek), bu tanımsız davranışa yol açabilir.",
    };

    lessons[28].explanation =
        "1'den N'e kadar olan sayıların toplamı, genellikle bir döngü "
        "(for veya while) içinde bir toplam değişkeni sürekli "
        "güncellenerek hesaplanır. Alternatif olarak N * (N + 1) / 2 "
        "kapalı-form (closed-form) formülüyle döngü kullanmadan da "
        "hesaplanabilir.";
    lessons[28].syntax = "int toplam = 0;\nfor (int i = 1; i <= n; i++) {\n    toplam += i;\n}";
    lessons[28].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int n = 5;\n"
        "    int toplam = 0;\n"
        "    for (int i = 1; i <= n; i++) {\n"
        "        toplam += i;\n"
        "    }\n"
        "    std::cout << toplam;\n"
        "    return 0;\n"
        "}";
    lessons[28].lineExplanations = {
        "int toplam = 0; : Toplamı tutacak değişken sıfırla "
        "başlatılır.",
        "toplam += i; : Her turda o anki i değeri toplama eklenir.",
        "n = 5 için toplam 1+2+3+4+5 = 15 olur.",
    };
    lessons[28].commonMistakes = {
        "toplam değişkenini 0 yerine 1 ile başlatmak (bu, sonuca "
        "fazladan 1 ekler).",
        "Döngü sınırını yanlış kurup (örneğin i < n) son sayıyı (n) "
        "toplamaya dahil etmemek.",
        "toplam += i; satırını döngü dışına yazıp yalnızca son i "
        "değerinin eklenmesine yol açmak.",
    };

    lessons[29].explanation =
        "Bir sayının faktöriyeli (n!), 1'den n'e kadar olan tüm "
        "sayıların çarpımıdır (örneğin 5! = 1*2*3*4*5 = 120). 0! tanım "
        "gereği 1'dir. Genellikle bir çarpım değişkeni 1 ile "
        "başlatılıp bir döngüde güncellenerek hesaplanır.";
    lessons[29].syntax = "int sonuc = 1;\nfor (int i = 1; i <= n; i++) {\n    sonuc *= i;\n}";
    lessons[29].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int n = 4;\n"
        "    int sonuc = 1;\n"
        "    for (int i = 1; i <= n; i++) {\n"
        "        sonuc *= i;\n"
        "    }\n"
        "    std::cout << sonuc;\n"
        "    return 0;\n"
        "}";
    lessons[29].lineExplanations = {
        "int sonuc = 1; : Çarpım değişkeni 0 değil 1 ile "
        "başlatılmalıdır (0 ile başlarsa sonuç her zaman 0 olur).",
        "sonuc *= i; : Her turda o anki i değeri çarpıma dahil edilir.",
        "n = 4 için sonuc 1*2*3*4 = 24 olur.",
    };
    lessons[29].commonMistakes = {
        "Çarpım değişkenini toplamada olduğu gibi 0 ile başlatmak "
        "(çarpımda başlangıç değeri 1 olmalıdır).",
        "0! değerinin 1 olduğunu unutup n=0 durumunu yanlış ele "
        "almak.",
        "Büyük n değerleri için int'in taşabileceğini (overflow) "
        "gözden kaçırmak (örneğin 13! zaten int'in sınırlarını "
        "zorlar).",
    };
}

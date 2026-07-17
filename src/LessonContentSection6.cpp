#include "LessonContent.h"

#include "Lesson.h"

void applySection6LessonContent(std::vector<Lesson>& lessons) {
    // Index 50 = topic id 51 (Lambda fonksiyonları), index 59 = topic
    // id 60 (Referans değişkeni) — same positional convention as
    // applyIntroLessonContent/applySection2-5LessonContent.

    lessons[50].explanation =
        "Lambda ifadeleri, isimsiz (anonim) fonksiyonlar tanımlamanın "
        "kısa bir yoludur. Genel biçimi [yakalama](parametreler) { "
        "govde } şeklindedir. Köşeli parantez içindeki yakalama listesi "
        "(capture list), lambda'nın dışındaki hangi değişkenlere ve "
        "nasıl (değer veya referans ile) erişebileceğini belirler.";
    lessons[50].syntax = "[yakalama](parametreler) { govde }";
    lessons[50].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    auto topla = [](int a, int b) {\n"
        "        return a + b;\n"
        "    };\n"
        "    std::cout << topla(3, 4);\n"
        "    return 0;\n"
        "}";
    lessons[50].lineExplanations = {
        "auto topla = [](int a, int b) { ... }; : topla değişkenine, iki "
        "int alıp toplamını döndüren bir lambda atanır.",
        "topla(3, 4) : lambda, normal bir fonksiyon gibi çağrılır (7 "
        "döner)."};
    lessons[50].commonMistakes = {
        "Boş yakalama listesi [] kullanıldığında lambda, dışındaki "
        "hiçbir değişkene erişemez; dış bir değişkene erişmek için [x] "
        "(değer ile yakalama) veya [&x] (referans ile yakalama) "
        "kullanılmalıdır.",
        "[x] ile yakalanan bir değişken, lambda gövdesi içinde "
        "varsayılan olarak sabittir (const); değiştirmek için "
        "lambda'nın mutable olarak işaretlenmesi gerekir, ve bu durumda "
        "bile yalnızca lambda'nın kendi iç kopyası değişir, dışarıdaki "
        "orijinal değişken asla etkilenmez.",
    };

    lessons[51].explanation =
        "Bir pointer (gösterici), başka bir değişkenin bellek adresini "
        "tutan özel bir değişkendir. tür* isim; şeklinde tanımlanır. "
        "Örneğin int* p; ifadesi, p'nin bir int değişkeninin adresini "
        "tutacağını belirtir. Tanımlandığında ilklendirilmezse (bir "
        "adres atanmazsa), p belirsiz (garbage) bir değer taşır ve bu "
        "haliyle dereference edilmesi tanımsız davranışa (undefined "
        "behavior) yol açar.";
    lessons[51].syntax = "tür* isim;";
    lessons[51].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int sayi = 42;\n"
        "    int* p = &sayi;\n"
        "    std::cout << *p;\n"
        "    return 0;\n"
        "}";
    lessons[51].lineExplanations = {
        "int* p = &sayi; : p, sayi değişkeninin adresini tutan bir "
        "pointer olarak tanımlanır.",
        "std::cout << *p; : *p, p'nin gösterdiği adresteki değeri (42) "
        "verir."};
    lessons[51].commonMistakes = {
        "int* p, q; ifadesinde sadece p bir pointer olur, q sıradan bir "
        "int olarak tanımlanır (yıldız işareti türe değil değişken "
        "adına bağlanır); iki pointer tanımlamak için int* p, *q; "
        "yazılmalıdır.",
    };

    lessons[52].explanation =
        "& operatörü, bir değişkenin bellekteki adresini verir. &x "
        "ifadesi \"x'in adresi\" anlamına gelir ve bir pointer değeri "
        "üretir. Bu, pointer'ları ilklendirmenin en yaygın yoludur.";
    lessons[52].syntax = "&degisken";
    lessons[52].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int x = 10;\n"
        "    int* p = &x;\n"
        "    std::cout << (p == &x);\n"
        "    return 0;\n"
        "}";
    lessons[52].lineExplanations = {
        "int* p = &x; : p, x'in adresiyle ilklendirilir.",
        "std::cout << (p == &x); : p ile &x aynı adresi tuttuğundan "
        "karşılaştırma true (1) verir."};
    lessons[52].commonMistakes = {
        "& sembolünün iki farklı kullanımı vardır: bir ifadede (&x) "
        "adres operatörüdür, ama bir tanımda (int& r = x;) referans "
        "bildirimidir — bağlama göre anlamı değişir.",
        "Bir adresin gerçek sayısal değeri her çalıştırmada farklı "
        "olabileceğinden, adresler programın davranışını test etmek "
        "için kullanılmaz, sadece pointer'ları ilklendirmek için "
        "kullanılır.",
    };

    lessons[53].explanation =
        "* operatörü bir pointer'ın önüne konduğunda, o pointer'ın "
        "gösterdiği adresteki değere erişmeyi sağlar (dereference). *p "
        "ifadesi \"p'nin gösterdiği değer\" anlamına gelir. p, geçerli "
        "bir adresi gösteriyorsa *(&x) her zaman x'in kendisine eşittir.";
    lessons[53].syntax = "*pointer";
    lessons[53].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int x = 5;\n"
        "    int* p = &x;\n"
        "    *p = 10;\n"
        "    std::cout << x;\n"
        "    return 0;\n"
        "}";
    lessons[53].lineExplanations = {
        "int* p = &x; : p, x'in adresini tutar.",
        "*p = 10; : p'nin gösterdiği adresteki değer (yani x) 10 yapılır.",
        "std::cout << x; : x artık 10'dur, çünkü *p üzerinden değiştirildi."};
    lessons[53].commonMistakes = {
        "Bir pointer tanımında * türe aittir (int* p), ama bir ifadede "
        "* dereference operatörüdür (*p) — aynı sembolün bağlama göre "
        "iki farklı anlamı vardır.",
        "nullptr veya ilklendirilmemiş bir pointer'ı dereference etmek "
        "tanımsız davranıştır ve genellikle çalışma zamanında çökmeye "
        "yol açar.",
    };

    lessons[54].explanation =
        "nullptr, \"hiçbir şeyi göstermeyen\" bir pointer'ı ifade eden, "
        "C++11 ile gelen tip-güvenli (type-safe) null pointer "
        "sabitidir. Bir pointer henüz geçerli bir adrese atanmadıysa "
        "nullptr ile ilklendirilmesi iyi bir alışkanlıktır. nullptr'ı "
        "dereference etmeye çalışmak (*p, p nullptr iken) tanımsız "
        "davranıştır ve genellikle çalışma zamanında çökmeye (erişim "
        "ihlaline) yol açar.";
    lessons[54].syntax = "tür* isim = nullptr;";
    lessons[54].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int* p = nullptr;\n"
        "    if (p == nullptr) {\n"
        "        std::cout << \"Pointer bos.\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[54].lineExplanations = {
        "int* p = nullptr; : p, hiçbir şeyi göstermeyecek şekilde "
        "ilklendirilir.",
        "if (p == nullptr) : p'nin gerçekten boş olup olmadığı güvenle "
        "kontrol edilebilir."};
    lessons[54].commonMistakes = {
        "Eski C++ kodlarında NULL veya düz 0 kullanılırdı; nullptr daha "
        "tip-güvenlidir ve modern C++'ta tercih edilir.",
        "p == nullptr kontrolü yapmadan bir pointer'ı dereference "
        "etmek, tanımsız davranışa yol açabilecek ciddi bir hatadır.",
    };

    lessons[55].explanation =
        "Bir dizi adı, kullanıldığı çoğu bağlamda ilk elemanının "
        "adresine \"decay\" olur (dönüşür). Bu sayede bir pointer, dizi "
        "elemanları üzerinde dolaşmak (traverse) için kullanılabilir. "
        "ptr++ ifadesi pointer'ı 1 byte değil, gösterdiği türün boyutu "
        "(sizeof) kadar ileri taşır.";
    lessons[55].syntax = "for (int* p = dizi; p != dizi + n; ++p) { ... }";
    lessons[55].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int sayilar[3] = {10, 20, 30};\n"
        "    int* p = sayilar;\n"
        "    for (int i = 0; i < 3; ++i) {\n"
        "        std::cout << *p << \" \";\n"
        "        ++p;\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[55].lineExplanations = {
        "int* p = sayilar; : dizi adı ilk elemanın adresine dönüştüğü "
        "için p, sayilar[0]'ı gösterir.",
        "++p; : p, bir sonraki int elemanına (4 byte ileri, 1 byte "
        "değil) taşınır."};
    lessons[55].commonMistakes = {
        "p + 1, p'yi 1 byte değil sizeof(int) (genellikle 4) byte ileri "
        "taşır; bunu \"1 byte ileri gider\" sanmak yaygın bir hatadır.",
        "Dizinin son elemanından sonrasını (dizi + n'den sonrasını) "
        "dereference etmek tanımsız davranıştır.",
    };

    lessons[56].explanation =
        "new operatörü, bellekte dinamik olarak (çalışma zamanında, "
        "heap üzerinde) yer ayırır ve o yerin adresini bir pointer "
        "olarak döndürür. new int(5) hem bellek ayırır hem de 5 "
        "değeriyle ilklendirir. Dinamik olarak ayrılan bellek, "
        "programcı tarafından delete ile serbest bırakılana kadar (ya "
        "da program sonlanana kadar) ayrılmış kalır.";
    lessons[56].syntax = "tür* isim = new tür(deger);";
    lessons[56].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int* p = new int(42);\n"
        "    std::cout << *p;\n"
        "    delete p;\n"
        "    return 0;\n"
        "}";
    lessons[56].lineExplanations = {
        "int* p = new int(42); : heap üzerinde bir int için yer "
        "ayrılır, 42 ile ilklendirilir, adresi p'ye atanır.",
        "delete p; : ayrılan bellek serbest bırakılır."};
    lessons[56].commonMistakes = {
        "new ile ayrılan bellek, karşılık gelen delete çağrılmadan "
        "unutulursa bellek sızıntısına (memory leak) yol açar — bu, "
        "programın çökmesine değil, sadece o belleğin bir daha "
        "kullanılamamasına (programın kullanabileceği belleğin "
        "azalmasına) neden olur.",
    };

    lessons[57].explanation =
        "delete operatörü, new ile ayrılmış belleği serbest bırakır. "
        "Her new çağrısının karşılığında tam olarak bir delete çağrısı "
        "olmalıdır. delete çağrıldıktan sonra pointer \"sarkan\" "
        "(dangling) hale gelir; bu pointer'ı tekrar dereference etmek "
        "veya tekrar delete etmek tanımsız davranıştır.";
    lessons[57].syntax = "delete pointer;";
    lessons[57].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int* p = new int(7);\n"
        "    std::cout << *p;\n"
        "    delete p;\n"
        "    p = nullptr;\n"
        "    return 0;\n"
        "}";
    lessons[57].lineExplanations = {
        "delete p; : p'nin gösterdiği bellek serbest bırakılır.",
        "p = nullptr; : p, artık geçersiz (dangling) olan eski adresi "
        "yanlışlıkla tekrar kullanmamak için boşa ayarlanır."};
    lessons[57].commonMistakes = {
        "Aynı pointer'ı iki kez delete etmek (double delete) tanımsız "
        "davranıştır.",
        "delete'ten sonra pointer'ı nullptr yapmak zorunlu değildir ama "
        "yanlışlıkla tekrar kullanılmasını (dangling pointer hatasını) "
        "önlemek için iyi bir alışkanlıktır.",
    };

    lessons[58].explanation =
        "new[] operatörü, çalışma zamanında boyutu belirlenen bir dizi "
        "ayırır (dinamik dizi). new[] ile ayrılan diziler, delete[] ile "
        "(köşeli parantezli haliyle) serbest bırakılmalıdır; sıradan "
        "delete kullanmak tanımsız davranıştır.";
    lessons[58].syntax = "tür* isim = new tür[boyut]; // ... delete[] isim;";
    lessons[58].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int n = 3;\n"
        "    int* dizi = new int[n];\n"
        "    for (int i = 0; i < n; ++i) {\n"
        "        dizi[i] = i * 10;\n"
        "    }\n"
        "    for (int i = 0; i < n; ++i) {\n"
        "        std::cout << dizi[i] << \" \";\n"
        "    }\n"
        "    delete[] dizi;\n"
        "    return 0;\n"
        "}";
    lessons[58].lineExplanations = {
        "int* dizi = new int[n]; : n elemanlık bir int dizisi heap "
        "üzerinde ayrılır.",
        "delete[] dizi; : new[] ile ayrılan dizi, köşeli parantezli "
        "delete[] ile serbest bırakılır."};
    lessons[58].commonMistakes = {
        "new[] ile ayrılan bir diziyi delete (köşeli parantezsiz) ile "
        "silmek tanımsız davranıştır; her zaman delete[] kullanılmalıdır.",
        "std::vector, aynı esnekliği manuel bellek yönetimi olmadan "
        "sunduğu için modern C++'ta çoğunlukla new[]/delete[] yerine "
        "tercih edilir.",
    };

    lessons[59].explanation =
        "Bir referans (&), var olan bir değişkene ikinci bir isim "
        "(takma ad) tanımlamanın yoludur. Pointer'ların aksine bir "
        "referans, tanımlandığı anda mutlaka ilklendirilmelidir ve bir "
        "kez bağlandıktan sonra başka bir değişkeni gösterecek şekilde "
        "değiştirilemez (rebind edilemez). Ayrıca bir referans asla "
        "\"boş\" (null) olamaz ve pointer aritmetiği (++, +1 gibi) "
        "desteklemez.";
    lessons[59].syntax = "tür& isim = degisken;";
    lessons[59].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int x = 5;\n"
        "    int& r = x;\n"
        "    r = 10;\n"
        "    std::cout << x;\n"
        "    return 0;\n"
        "}";
    lessons[59].lineExplanations = {
        "int& r = x; : r, x'in bir takma adı olur (aynı değişkeni "
        "gösterir).",
        "r = 10; : r üzerinden yapılan değişiklik doğrudan x'i etkiler."};
    lessons[59].commonMistakes = {
        "int& r; (ilklendirmeden) tanımlamak derleme hatasıdır — "
        "referanslar boş bırakılamaz.",
        "int& r = x; tanımından sonra r = y; yazmak, r'yi y'ye "
        "\"yeniden bağlamaz\"; bunun yerine y'nin değerini x'e (r "
        "üzerinden) kopyalar — pointer'lardan farklı olarak bir "
        "referans asla başka bir değişkeni göstermeye geçemez.",
    };
}

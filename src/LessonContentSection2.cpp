#include "LessonContent.h"

#include "Lesson.h"

void applySection2LessonContent(std::vector<Lesson>& lessons) {
    // Index 10 = topic id 11 (Matematiksel operatörler), index 19 = topic
    // id 20 (Üçlü koşul operatörü) — same positional convention as
    // applyIntroLessonContent in LessonManager.cpp.

    lessons[10].explanation =
        "C++'ta temel matematiksel işlemler +, -, *, / operatörleriyle "
        "yapılır. Operatör önceliği matematikteki gibidir (* ve / önce, + "
        "ve - sonra); parantezle öncelik değiştirilebilir. İki tam sayı "
        "(int) bölündüğünde sonuç da tam sayıya yuvarlanır (ondalık kısım "
        "atılır); ondalıklı sonuç istenirse en az bir işlenenin "
        "double/float olması gerekir.";
    lessons[10].syntax = "int sonuc = a + b * c;";
    lessons[10].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int a = 7;\n"
        "    int b = 2;\n"
        "    std::cout << a + b << \"\\n\";\n"
        "    std::cout << a / b << \"\\n\";\n"
        "    std::cout << static_cast<double>(a) / b << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[10].lineExplanations = {
        "a + b : 7 + 2 = 9 sonucunu verir.",
        "a / b : İki tam sayı bölündüğü için sonuç 3 olur (3.5 değil, "
        "ondalık kısım atılır).",
        "static_cast<double>(a) / b : a önce double'a çevrildiği için "
        "bölme ondalıklı yapılır, sonuç 3.5 olur.",
    };
    lessons[10].commonMistakes = {
        "İki int'i bölüp ondalıklı sonuç beklemek (7 / 2 sonucu 3'tür, 3.5 "
        "değil).",
        "Operatör önceliğini unutup parantez kullanmadan yanlış sonuç "
        "almak (örneğin 2 + 3 * 4, 20 değil 14'tür).",
        "Negatif sayılarla bölme/mod sonucunun beklenmedik işaretli "
        "çıkabileceğini gözden kaçırmak.",
    };

    lessons[11].explanation =
        "% (mod) operatörü, bir tam sayının başka bir tam sayıya "
        "bölümünden kalanı verir. Yalnızca tam sayı (int) türleriyle "
        "kullanılır; double/float ile kullanılamaz. Bir sayının çift/tek "
        "olup olmadığını kontrol etmek (sayi % 2 == 0) gibi işlemlerde "
        "sıkça kullanılır.";
    lessons[11].syntax = "int kalan = a % b;";
    lessons[11].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int a = 17;\n"
        "    int b = 5;\n"
        "    std::cout << a % b << \"\\n\";\n"
        "    std::cout << (a % 2 == 0 ? \"cift\" : \"tek\") << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[11].lineExplanations = {
        "a % b : 17'nin 5'e bölümünden kalan 2'dir (17 = 5*3 + 2).",
        "a % 2 == 0 : a'nın 2'ye bölümünden kalan sıfır mı diye kontrol "
        "eder; 17 tek olduğu için false döner.",
    };
    lessons[11].commonMistakes = {
        "% operatörünü double/float değişkenlerle kullanmaya çalışmak "
        "(derleme hatası verir).",
        "% operatörünü bölme (/) ile karıştırmak.",
        "0'a mod almaya çalışmak (a % 0), tıpkı 0'a bölme gibi tanımsız "
        "davranışa yol açar.",
    };

    lessons[12].explanation =
        "+=, -=, *=, /=, %= operatörleri, bir değişkenin mevcut değeri "
        "üzerinde işlem yapıp sonucu yine aynı değişkene atamanın kısa "
        "yoludur. Örneğin a += 5, a = a + 5 ile aynı anlama gelir. Kod "
        "tekrarını azaltır ve okunabilirliği artırır.";
    lessons[12].syntax = "sayi += 5;  // sayi = sayi + 5; ile aynıdır";
    lessons[12].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int puan = 10;\n"
        "    puan += 5;\n"
        "    puan *= 2;\n"
        "    std::cout << puan;\n"
        "    return 0;\n"
        "}";
    lessons[12].lineExplanations = {
        "puan += 5; : puan = puan + 5; ile aynıdır, puan 15 olur.",
        "puan *= 2; : puan = puan * 2; ile aynıdır, puan 30 olur.",
    };
    lessons[12].commonMistakes = {
        "+= operatörünü yanlışlıkla =+ şeklinde yazmak (=+ de derlenir "
        "ama farklı ve yanlış bir anlam taşır).",
        "Kısaltılmış atamanın sağ tarafındaki tüm ifadenin işleme dahil "
        "olduğunu unutmak (a *= b + 1, a = a * (b + 1) anlamına gelir, "
        "a = a * b + 1 değil).",
        "Değişkenin başlangıç değeri atanmamışken += kullanmaya "
        "çalışmak.",
    };

    lessons[13].explanation =
        "++ ve -- operatörleri, bir değişkenin değerini 1 artırır veya "
        "azaltır. Önden (++sayi) kullanıldığında değişken önce "
        "güncellenir sonra kullanılır; sondan (sayi++) kullanıldığında "
        "önce mevcut değer kullanılır, değişken daha sonra güncellenir. "
        "Tek başına bir satırda kullanıldıklarında ikisi de aynı sonucu "
        "verir; bir ifadenin içinde kullanıldıklarında fark ortaya "
        "çıkar.";
    lessons[13].syntax = "sayi++;  // veya ++sayi;";
    lessons[13].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int a = 5;\n"
        "    std::cout << a++ << \"\\n\";\n"
        "    std::cout << a << \"\\n\";\n"
        "    int b = 5;\n"
        "    std::cout << ++b << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[13].lineExplanations = {
        "a++ : Önce a'nın o anki değeri (5) yazdırılır, sonra a 6 olur.",
        "a : Bir önceki satırda güncellendiği için artık 6 yazdırılır.",
        "++b : Önce b 6 olur, sonra bu güncel değer (6) yazdırılır.",
    };
    lessons[13].commonMistakes = {
        "Önden ve sondan artırmanın tek başına bir satırda fark "
        "yaratmadığını sanıp bir ifade içinde de aynı davrandığını "
        "düşünmek.",
        "a++ ifadesinin sonucunun artırma sonrası değeri gösterdiğini "
        "sanmak (aslında artırma öncesi değeri gösterir).",
        "++ operatörünü aynı ifadede bir değişken üzerinde birden fazla "
        "kez kullanmak (karışık/öngörülemeyen davranışa yol açabilir).",
    };

    lessons[14].explanation =
        "==, !=, <, >, <=, >= operatörleri iki değeri karşılaştırır ve "
        "bool (true/false) sonucu döner. == eşitlik, != eşit olmama, <, "
        ">, <=, >= sırasıyla küçük, büyük, küçük eşit, büyük eşit "
        "anlamına gelir. == ile atama operatörü olan = karıştırılmamalıdır.";
    lessons[14].syntax = "if (a == b) { ... }";
    lessons[14].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int a = 5;\n"
        "    int b = 7;\n"
        "    std::cout << (a == b) << \"\\n\";\n"
        "    std::cout << (a < b) << \"\\n\";\n"
        "    std::cout << (a != b) << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[14].lineExplanations = {
        "a == b : 5, 7'ye eşit olmadığı için false (0) döner.",
        "a < b : 5, 7'den küçük olduğu için true (1) döner.",
        "a != b : 5 ile 7 eşit olmadığı için true (1) döner.",
    };
    lessons[14].commonMistakes = {
        "Karşılaştırma için == yerine yanlışlıkla atama operatörü = "
        "kullanmak (if (a = b) gibi; bu hem hatalı hem de derlenebilir "
        "bir koddur).",
        "cout ile bool sonucunu yazdırırken true/false yerine 1/0 "
        "göründüğünü fark etmemek.",
        "Ondalıklı (double/float) sayıları == ile doğrudan karşılaştırmak "
        "(yuvarlama hataları nedeniyle güvenilmez olabilir).",
    };

    lessons[15].explanation =
        "&&, || ve ! mantıksal operatörleridir. && (VE) her iki koşul da "
        "doğruysa true döner; || (VEYA) koşullardan en az biri doğruysa "
        "true döner; ! (DEĞİL) bir bool ifadenin tersini alır. Birden "
        "fazla koşulu birleştirmek için kullanılırlar.";
    lessons[15].syntax = "if (a > 0 && b > 0) { ... }";
    lessons[15].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int yas = 20;\n"
        "    bool ehliyetVar = true;\n"
        "    std::cout << (yas >= 18 && ehliyetVar) << \"\\n\";\n"
        "    std::cout << (yas < 18 || !ehliyetVar) << \"\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[15].lineExplanations = {
        "yas >= 18 && ehliyetVar : Her iki koşul da true olduğu için "
        "sonuç true (1) olur.",
        "yas < 18 || !ehliyetVar : yas < 18 false, !ehliyetVar de false "
        "olduğu için sonuç false (0) olur.",
    };
    lessons[15].commonMistakes = {
        "&& ve || operatörlerini birbirine karıştırmak (VE yerine VEYA "
        "mantığı kullanmak).",
        "Tek & veya tek | yazmak (bunlar bitwise operatörlerdir, "
        "mantıksal && / || ile aynı işi yapmaz).",
        "! operatörünün önceliğini yanlış varsayıp parantezsiz karmaşık "
        "ifadeler yazmak.",
    };

    lessons[16].explanation =
        "if ifadesi, parantez içindeki koşul true olduğunda süslü "
        "parantez { } içindeki kod bloğunun çalışmasını sağlar. Koşul "
        "false ise blok atlanır. Tek satırlık bloklarda süslü parantez "
        "isteğe bağlıdır, ancak okunabilirlik için genelde kullanılması "
        "önerilir.";
    lessons[16].syntax = "if (kosul) {\n    // kosul true ise calisir\n}";
    lessons[16].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int yas = 20;\n"
        "    if (yas >= 18) {\n"
        "        std::cout << \"Reşitsiniz.\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[16].lineExplanations = {
        "if (yas >= 18) : yas'ın 18'den büyük veya eşit olup olmadığını "
        "kontrol eder.",
        "std::cout << \"Reşitsiniz.\"; : Koşul true olduğu için bu satır "
        "çalışır ve ekrana yazılır.",
    };
    lessons[16].commonMistakes = {
        "if satırının sonuna yanlışlıkla noktalı virgül koymak "
        "(if (kosul);), bu durumda blok her zaman 'çalışmış' gibi "
        "davranır.",
        "Koşulu == yerine = ile yazmak (if (yas = 18) her zaman true "
        "döner ve yas'ı 18 yapar).",
        "Süslü parantezi unutup birden fazla satırı if'e bağlı sanmak "
        "(parantezsiz yalnızca ilk satır if'e bağlıdır).",
    };

    lessons[17].explanation =
        "if-else yapısı, koşul true olduğunda if bloğunu, false "
        "olduğunda else bloğunu çalıştırır. İki alternatif yoldan tam "
        "olarak birinin çalışmasını garanti eder.";
    lessons[17].syntax = "if (kosul) {\n    // true ise\n} else {\n    // false ise\n}";
    lessons[17].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int not_ = 45;\n"
        "    if (not_ >= 50) {\n"
        "        std::cout << \"Geçti\";\n"
        "    } else {\n"
        "        std::cout << \"Kaldı\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[17].lineExplanations = {
        "if (not_ >= 50) : not_'un 50'ye eşit veya büyük olup olmadığını "
        "kontrol eder.",
        "std::cout << \"Kaldı\"; : not_ 45 olduğu için koşul false'tur, "
        "bu yüzden else bloğu çalışır ve 'Kaldı' yazdırılır.",
    };
    lessons[17].commonMistakes = {
        "else'den önce noktalı virgül veya ekstra kod koymak (else, "
        "doğrudan if bloğunun kapanışından sonra gelmelidir).",
        "if ve else bloklarının her ikisinin de aynı anda "
        "çalışabileceğini sanmak (yalnızca biri çalışır).",
        "else'i gereksiz yere ayrı bir if ile taklit etmeye çalışmak "
        "(if (!kosul) tekrar yazmak yerine else kullanmak daha nettir).",
    };

    lessons[18].explanation =
        "else if, birden fazla koşulu sırayla kontrol etmeyi sağlar. "
        "Yukarıdan aşağıya doğru koşullar sırayla değerlendirilir; ilk "
        "true olan bloğun kodu çalışır ve geri kalanlar atlanır. En sona "
        "isteğe bağlı bir else eklenerek hiçbir koşul sağlanmazsa "
        "çalışacak varsayılan bir blok tanımlanabilir.";
    lessons[18].syntax =
        "if (kosul1) {\n    ...\n} else if (kosul2) {\n    ...\n} else {\n    ...\n}";
    lessons[18].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int not_ = 75;\n"
        "    if (not_ >= 85) {\n"
        "        std::cout << \"AA\";\n"
        "    } else if (not_ >= 70) {\n"
        "        std::cout << \"BA\";\n"
        "    } else {\n"
        "        std::cout << \"Diğer\";\n"
        "    }\n"
        "    return 0;\n"
        "}";
    lessons[18].lineExplanations = {
        "if (not_ >= 85) : 75 için false olduğundan bu blok atlanır.",
        "else if (not_ >= 70) : 75, 70'e eşit veya büyük olduğu için "
        "true olur ve 'BA' yazdırılır.",
        "else : Yukarıdaki koşullardan biri true olduğu için bu blok hiç "
        "çalışmaz.",
    };
    lessons[18].commonMistakes = {
        "else if koşullarının sırasını yanlış kurup her zaman ilk (en "
        "geniş) koşulun eşleşmesine izin vermek (örneğin >= 70 koşulunu "
        ">= 85'ten önce yazmak, AA notunu asla vermez).",
        "Her koşulu bağımsız ayrı if'ler olarak yazıp else if "
        "kullanmamak (bu, tüm koşulların gereksiz yere kontrol "
        "edilmesine yol açar).",
        "Zincirin sonuna else eklemeyi unutup hiçbir koşul "
        "sağlanmadığında hiçbir şey olmayacağını fark etmemek.",
    };

    lessons[19].explanation =
        "Üçlü (ternary) koşul operatörü ?:, kısa bir if-else'in tek "
        "satırda yazılmasını sağlar. kosul ? deger1 : deger2 şeklinde "
        "kullanılır; kosul true ise deger1, false ise deger2 sonucu "
        "döner. Genelde bir değişkene basit bir koşullu değer atarken "
        "tercih edilir.";
    lessons[19].syntax = "sonuc = kosul ? deger1 : deger2;";
    lessons[19].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    int yas = 16;\n"
        "    std::string durum = (yas >= 18) ? \"Reşit\" : \"Reşit değil\";\n"
        "    std::cout << durum;\n"
        "    return 0;\n"
        "}";
    lessons[19].lineExplanations = {
        "(yas >= 18) ? \"Reşit\" : \"Reşit değil\" : yas 18'den küçük "
        "olduğu için koşul false'tur, sonuç olarak 'Reşit değil' seçilir.",
        "durum : Ternary ifadenin sonucunu tutan string değişkendir.",
    };
    lessons[19].commonMistakes = {
        "Üçlü operatörü karmaşık, çok satırlı mantık için kullanmaya "
        "çalışmak (okunabilirliği bozar; böyle durumlarda if-else tercih "
        "edilmelidir).",
        ": ve ? sembollerinin yerini karıştırmak.",
        "İki taraftaki (true/false) ifadelerin farklı türde olmasına "
        "dikkat etmemek (derleyici uyarısı/hatasına yol açabilir).",
    };
}

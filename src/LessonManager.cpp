#include "LessonManager.h"

#include "LessonContent.h"

#include <algorithm>
#include <cstddef>
#include <iterator>
#include <utility>

namespace {

struct TopicSeed {
    int id;
    int sectionId;
    const char* title;
};

constexpr TopicSeed kTopicSeeds[] = {
    // Bölüm 1: Giriş, çıkış ve değişkenler
    {1, 1, "cout"},
    {2, 1, "\\n"},
    {3, 1, "endl"},
    {4, 1, "cin"},
    {5, 1, "getline()"},
    {6, 1, "int"},
    {7, 1, "double"},
    {8, 1, "char"},
    {9, 1, "bool"},
    {10, 1, "const"},

    // Bölüm 2: Operatörler ve koşullar
    {11, 2, "Matematiksel operatörler"},
    {12, 2, "% mod operatörü"},
    {13, 2, "Kısaltılmış atama operatörleri"},
    {14, 2, "++ ve --"},
    {15, 2, "Karşılaştırma operatörleri"},
    {16, 2, "Mantıksal operatörler"},
    {17, 2, "if"},
    {18, 2, "if-else"},
    {19, 2, "else if"},
    {20, 2, "Üçlü koşul operatörü"},

    // Bölüm 3: Seçim ve döngüler
    {21, 3, "switch-case"},
    {22, 3, "for"},
    {23, 3, "while"},
    {24, 3, "do-while"},
    {25, 3, "break"},
    {26, 3, "continue"},
    {27, 3, "İç içe döngüler"},
    {28, 3, "Range-based for"},
    {29, 3, "1'den N'e kadar toplama"},
    {30, 3, "Faktöriyel hesaplama"},

    // Bölüm 4: Diziler, vector ve string
    {31, 4, "Normal diziler"},
    {32, 4, "Dizi elemanlarını değiştirme"},
    {33, 4, "std::array"},
    {34, 4, "vector"},
    {35, 4, "push_back() ve pop_back()"},
    {36, 4, "size(), front(), back() ve at()"},
    {37, 4, "string"},
    {38, 4, "String birleştirme"},
    {39, 4, "length() ve empty()"},
    {40, 4, "substr() ve find()"},

    // Bölüm 5: Fonksiyonlar
    {41, 5, "Parametresiz fonksiyon"},
    {42, 5, "Parametre alan fonksiyon"},
    {43, 5, "Değer döndüren fonksiyon"},
    {44, 5, "Fonksiyon prototipi"},
    {45, 5, "Varsayılan parametre"},
    {46, 5, "Fonksiyon aşırı yükleme"},
    {47, 5, "Değer ile parametre gönderme"},
    {48, 5, "Referans ile parametre gönderme"},
    {49, 5, "const referans"},
    {50, 5, "Recursion"},

    // Bölüm 6: Lambda, pointer ve bellek
    {51, 6, "Lambda fonksiyonları"},
    {52, 6, "Pointer tanımlama"},
    {53, 6, "& adres operatörü"},
    {54, 6, "* dereference operatörü"},
    {55, 6, "nullptr"},
    {56, 6, "Pointer ile dizi dolaşma"},
    {57, 6, "new"},
    {58, 6, "delete"},
    {59, 6, "Dinamik dizi"},
    {60, 6, "Referans değişkeni"},

    // Bölüm 7: Struct ve nesne yönelimli programlama
    {61, 7, "struct"},
    {62, 7, "enum"},
    {63, 7, "enum class"},
    {64, 7, "Sınıf ve nesne"},
    {65, 7, "Constructor"},
    {66, 7, "Destructor"},
    {67, 7, "private ve public"},
    {68, 7, "Getter ve setter"},
    {69, 7, "Kalıtım"},
    {70, 7, "protected"},

    // Bölüm 8: İleri nesne yönelimli özellikler
    {71, 8, "virtual"},
    {72, 8, "override"},
    {73, 8, "Soyut sınıf"},
    {74, 8, "Polimorfizm"},
    {75, 8, "this pointer'ı"},
    {76, 8, "static sınıf üyesi"},
    {77, 8, "Operatör aşırı yükleme"},
    {78, 8, "Template fonksiyon"},
    {79, 8, "namespace"},
    {80, 8, "auto"},

    // Bölüm 9: STL veri yapıları
    {81, 9, "pair"},
    {82, 9, "tuple"},
    {83, 9, "set"},
    {84, 9, "map"},
    {85, 9, "unordered_map"},
    {86, 9, "stack"},
    {87, 9, "queue"},
    {88, 9, "deque"},
    {89, 9, "priority_queue"},
    {90, 9, "Iterator"},

    // Bölüm 10: Algoritmalar, dosyalar ve hata yönetimi
    {91, 10, "sort()"},
    {92, 10, "reverse()"},
    {93, 10, "find()"},
    {94, 10, "count()"},
    {95, 10, "min(), max() ve max_element()"},
    {96, 10, "accumulate()"},
    {97, 10, "Dosyaya yazma"},
    {98, 10, "Dosyadan okuma"},
    {99, 10, "try-catch"},
    {100, 10, "unique_ptr"},
};

void applyIntroLessonContent(std::vector<Lesson>& lessons) {
    // Index 0 = topic id 1 (cout), index 9 = topic id 10 (const) — the seed
    // table above is authored in strict ascending id order starting at 1,
    // so this positional mapping is safe.

    lessons[0].explanation =
        "cout, ekrana veri yazdırmak için kullanılan bir çıktı akışıdır "
        "(output stream). Kullanabilmek için <iostream> kütüphanesinin "
        "eklenmesi gerekir. << operatörü ile bir veya birden fazla değer "
        "art arda ekrana yazdırılabilir.";
    lessons[0].syntax = "#include <iostream>\n\nstd::cout << \"Merhaba\";";
    lessons[0].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    std::cout << \"Merhaba, dünya!\";\n"
        "    return 0;\n"
        "}";
    lessons[0].lineExplanations = {
        "#include <iostream> : cout kullanabilmek için gereken kütüphaneyi ekler.",
        "std::cout << \"Merhaba, dünya!\"; : Tırnak içindeki metni olduğu gibi ekrana yazdırır.",
        "return 0; : Programın hatasız bittiğini işletim sistemine bildirir.",
    };
    lessons[0].commonMistakes = {
        "std:: önekini unutmak (using namespace std; yoksa derleme hatası oluşur).",
        "<iostream> kütüphanesini eklemeyi unutmak.",
        "<< operatörünü = (atama) operatörüyle karıştırmak.",
    };

    lessons[1].explanation =
        "\\n, metin içinde yeni satıra geçmeyi sağlayan bir kaçış (escape) "
        "dizisidir. Çift tırnak içindeki bir metnin istenilen yerine "
        "yazılarak ekran çıktısında satır atlanmasını sağlar. std::endl de "
        "aynı işi yapar, ancak \\n ekstra bir tamponu (buffer) boşaltma "
        "işlemi yapmadığı için genellikle daha hızlıdır.";
    lessons[1].syntax = "std::cout << \"Birinci satır\\n\";\nstd::cout << \"İkinci satır\\n\";";
    lessons[1].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    std::cout << \"Merhaba\\n\";\n"
        "    std::cout << \"Dünya\\n\";\n"
        "    return 0;\n"
        "}";
    lessons[1].lineExplanations = {
        "\"Merhaba\\n\" : Merhaba yazdıktan sonra imleci bir alt satıra geçirir.",
        "\"Dünya\\n\" : Dünya yazdıktan sonra tekrar alt satıra geçer.",
        "İki ayrı cout ifadesi, \\n sayesinde iki ayrı satırda görünür.",
    };
    lessons[1].commonMistakes = {
        "\\n yerine yanlışlıkla /n yazmak (ters slash yerine düz slash kullanmak).",
        "\\n ifadesini tırnakların dışına yazmak.",
        "Satır atlamanın otomatik olduğunu sanıp \\n eklemeyi unutmak.",
    };

    lessons[2].explanation =
        "std::endl, çıktıyı yeni satıra geçirir ve ayrıca çıktı tamponunu "
        "(buffer) hemen boşaltır (flush). Bu ekstra boşaltma işlemi \\n'e "
        "göre biraz daha yavaştır; bu yüzden sık tekrarlanan yazdırmalarda "
        "genellikle \\n tercih edilir, ama endl de tamamen geçerlidir.";
    lessons[2].syntax = "std::cout << \"Merhaba\" << std::endl;";
    lessons[2].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    std::cout << \"Birinci\" << std::endl;\n"
        "    std::cout << \"İkinci\" << std::endl;\n"
        "    return 0;\n"
        "}";
    lessons[2].lineExplanations = {
        "std::cout << \"Birinci\" << std::endl; : Birinci yazar, ardından satırı bitirip tamponu boşaltır.",
        "std::cout << \"İkinci\" << std::endl; : İkinci yazar ve yine satırı bitirir.",
        "İki endl, çıktının iki ayrı satırda görünmesini sağlar.",
    };
    lessons[2].commonMistakes = {
        "endl yazarken std:: önekini unutmak.",
        "endl ile \\n'in birebir aynı hızda olduğunu sanmak (endl ekstra flush yapar).",
        "endl'i çift tırnak içine yazmak (\"endl\" gibi) — bu durumda sadece düz metin olarak yazdırılır, satır atlamaz.",
    };

    lessons[3].explanation =
        "cin, klavyeden veri okumak için kullanılan giriş akışıdır (input "
        "stream). >> operatörü ile bir değişkene değer atanır. Boşluk veya "
        "yeni satır görene kadar okuma yapar; bu yüzden boşluk içeren "
        "metinler için getline() tercih edilir.";
    lessons[3].syntax = "int yas;\nstd::cin >> yas;";
    lessons[3].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int yas;\n"
        "    std::cout << \"Yaşınız: \";\n"
        "    std::cin >> yas;\n"
        "    std::cout << \"Yaşınız: \" << yas;\n"
        "    return 0;\n"
        "}";
    lessons[3].lineExplanations = {
        "int yas; : Kullanıcının gireceği yaşı saklamak için bir tam sayı değişkeni tanımlar.",
        "std::cin >> yas; : Klavyeden girilen değeri okuyup yas değişkenine atar.",
        "std::cout << ... << yas; : Okunan değeri tekrar ekrana yazdırır.",
    };
    lessons[3].commonMistakes = {
        ">> operatörünü << ile karıştırmak (cin için >> kullanılır).",
        "cin ile boşluk içeren bir cümleyi okumaya çalışmak (yalnızca ilk kelimeyi alır).",
        "Değişken türü ile girilen verinin uyuşmamasına dikkat etmemek (örneğin sayı beklenirken harf girilmesi).",
    };

    lessons[4].explanation =
        "getline(), kullanıcıdan boşluk içeren tam bir satırı okumak için "
        "kullanılır. cin >> yalnızca ilk boşluğa kadar okurken, "
        "getline(std::cin, degisken) tüm satırı (yeni satıra kadar) okur. "
        "Kullanmak için <string> kütüphanesi ve bir std::string değişkeni gerekir.";
    lessons[4].syntax = "std::string isim;\nstd::getline(std::cin, isim);";
    lessons[4].exampleCode =
        "#include <iostream>\n"
        "#include <string>\n\n"
        "int main() {\n"
        "    std::string isimSoyisim;\n"
        "    std::cout << \"Adınız soyadınız: \";\n"
        "    std::getline(std::cin, isimSoyisim);\n"
        "    std::cout << \"Merhaba, \" << isimSoyisim;\n"
        "    return 0;\n"
        "}";
    lessons[4].lineExplanations = {
        "#include <string> : std::string ve getline için gerekli kütüphaneyi ekler.",
        "std::string isimSoyisim; : Boşluk içerebilecek metni saklayacak değişkeni tanımlar.",
        "std::getline(std::cin, isimSoyisim); : Kullanıcının girdiği tüm satırı (boşluklar dahil) okuyup değişkene atar.",
    };
    lessons[4].commonMistakes = {
        "<string> kütüphanesini eklemeyi unutmak.",
        "getline() öncesinde kullanılan bir cin >> ifadesinin bıraktığı yeni satır karakterini temizlememek (bu durumda getline boş okuyabilir).",
        "getline() parametrelerinin sırasını karıştırmak (önce cin, sonra değişken gelir).",
    };

    lessons[5].explanation =
        "int, tam sayı (ondalıksız) değerleri saklamak için kullanılan "
        "temel bir veri türüdür. Örneğin yaş, adet veya sayaç gibi "
        "değerler genellikle int ile tutulur.";
    lessons[5].syntax = "int sayi = 5;";
    lessons[5].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    int yas = 25;\n"
        "    std::cout << yas;\n"
        "    return 0;\n"
        "}";
    lessons[5].lineExplanations = {
        "int yas = 25; : yas adında bir tam sayı değişkeni tanımlar ve 25 değerini atar.",
        "std::cout << yas; : yas değişkeninin değerini ekrana yazdırır.",
    };
    lessons[5].commonMistakes = {
        "int türüne ondalıklı bir sayı (örneğin 3.14) atamaya çalışmak (ondalık kısım kaybolur).",
        "Değişkeni tanımlarken türünü (int) yazmayı unutmak.",
        "Çok büyük sayılarda int'in sınırlarını (taşma riski) göz ardı etmek.",
    };

    lessons[6].explanation =
        "double, ondalıklı (kesirli) sayıları saklamak için kullanılan bir "
        "veri türüdür. Örneğin fiyat, ortalama veya yüzde gibi kesirli "
        "değerler double ile tutulur.";
    lessons[6].syntax = "double fiyat = 19.99;";
    lessons[6].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    double ortalama = 87.5;\n"
        "    std::cout << ortalama;\n"
        "    return 0;\n"
        "}";
    lessons[6].lineExplanations = {
        "double ortalama = 87.5; : ortalama adında ondalıklı bir değişken tanımlar ve 87.5 değerini atar.",
        "std::cout << ortalama; : ortalama değişkeninin değerini ekrana yazdırır.",
    };
    lessons[6].commonMistakes = {
        "double gereken bir yerde int kullanmak (ondalık kısmın kaybolmasına yol açar).",
        "Ondalık ayıracı olarak virgül (,) kullanmak (C++'ta nokta (.) kullanılır).",
        "double ile float'ı karıştırmak (ikisi de ondalıklıdır ama farklı hassasiyete sahiptir).",
    };

    lessons[7].explanation =
        "char, tek bir karakteri (harf, rakam veya sembol) saklamak için "
        "kullanılan bir veri türüdür. Değer tanımlarken tek tırnak (') "
        "kullanılır, örneğin 'A'.";
    lessons[7].syntax = "char harf = 'A';";
    lessons[7].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    char harf = 'B';\n"
        "    std::cout << harf;\n"
        "    return 0;\n"
        "}";
    lessons[7].lineExplanations = {
        "char harf = 'B'; : harf adında bir karakter değişkeni tanımlar ve 'B' değerini atar.",
        "std::cout << harf; : harf değişkeninin değerini ekrana yazdırır.",
    };
    lessons[7].commonMistakes = {
        "char değeri tanımlarken çift tırnak (\"A\") kullanmak (bu bir string olur, char için tek tırnak gerekir).",
        "Bir char değişkenine birden fazla karakter atamaya çalışmak (örn. 'AB' geçersizdir).",
        "char ile string'i karıştırmak (char tek karakter, string ise karakter dizisidir).",
    };

    lessons[8].explanation =
        "bool, yalnızca true (doğru) veya false (yanlış) değerlerinden "
        "birini saklayan bir veri türüdür. Genellikle bir koşulun "
        "sonucunu tutmak için kullanılır.";
    lessons[8].syntax = "bool aktif = true;";
    lessons[8].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    bool gecti = true;\n"
        "    std::cout << gecti;\n"
        "    return 0;\n"
        "}";
    lessons[8].lineExplanations = {
        "bool gecti = true; : gecti adında bir mantıksal değişken tanımlar ve true (doğru) değerini atar.",
        "std::cout << gecti; : gecti değişkenini ekrana yazdırır (true için 1, false için 0 görünür).",
    };
    lessons[8].commonMistakes = {
        "true/false yerine \"true\"/\"false\" gibi tırnaklı metin yazmak (bunlar string olur, bool değildir).",
        "cout ile bool yazdırıldığında true/false yerine 1/0 göründüğünü unutmak.",
        "bool değişkenine 0 veya 1 dışında sayılar atayıp anlamını karıştırmak.",
    };

    lessons[9].explanation =
        "const, bir değişkenin değerinin tanımlandıktan sonra "
        "değiştirilemeyeceğini belirtir. Sabit kalması gereken değerler "
        "(örneğin pi sayısı) için kullanılır. const bir değişkene ikinci "
        "kez değer atamaya çalışmak derleme hatası verir.";
    lessons[9].syntax = "const double PI = 3.14;";
    lessons[9].exampleCode =
        "#include <iostream>\n\n"
        "int main() {\n"
        "    const int MAKS_PUAN = 100;\n"
        "    std::cout << MAKS_PUAN;\n"
        "    return 0;\n"
        "}";
    lessons[9].lineExplanations = {
        "const int MAKS_PUAN = 100; : MAKS_PUAN adında, değeri sonradan değiştirilemeyecek bir sabit tanımlar.",
        "std::cout << MAKS_PUAN; : Sabitin değerini ekrana yazdırır.",
    };
    lessons[9].commonMistakes = {
        "const olarak tanımlanan bir değişkene sonradan yeni bir değer atamaya çalışmak (derleme hatası oluşur).",
        "const bir değişkeni tanımlarken başlangıç değeri vermemek (const değişkenler tanımlandığı anda değer almalıdır).",
        "const kullanmanın performansı yavaşlattığını sanmak (aksine, derleyiciye ek bilgi vererek optimizasyona yardımcı olabilir).",
    };
}

}  // namespace

LessonManager::LessonManager() {
    sectionTitles_ = {
        "Giriş, çıkış ve değişkenler",
        "Operatörler ve koşullar",
        "Seçim ve döngüler",
        "Diziler, vector ve string",
        "Fonksiyonlar",
        "Lambda, pointer ve bellek",
        "Struct ve nesne yönelimli programlama",
        "İleri nesne yönelimli özellikler",
        "STL veri yapıları",
        "Algoritmalar, dosyalar ve hata yönetimi",
    };

    lessons_.reserve(std::size(kTopicSeeds));
    for (const TopicSeed& seed : kTopicSeeds) {
        Lesson lesson;
        lesson.id = seed.id;
        lesson.sectionId = seed.sectionId;
        lesson.title = seed.title;
        lessons_.push_back(std::move(lesson));
    }

    applyIntroLessonContent(lessons_);
    applySection2LessonContent(lessons_);
    applySection3LessonContent(lessons_);
    applySection4LessonContent(lessons_);
    applySection5LessonContent(lessons_);
    applySection6LessonContent(lessons_);
    applySection7LessonContent(lessons_);
    applySection8LessonContent(lessons_);
    applySection9LessonContent(lessons_);
}

const std::vector<Lesson>& LessonManager::allLessons() const {
    return lessons_;
}

std::vector<Lesson> LessonManager::lessonsInSection(int sectionId) const {
    std::vector<Lesson> result;
    std::ranges::copy_if(
        lessons_,
        std::back_inserter(result),
        [sectionId](const Lesson& lesson) { return lesson.sectionId == sectionId; });
    return result;
}

std::optional<Lesson> LessonManager::findById(int topicId) const {
    const auto it = std::ranges::find_if(
        lessons_,
        [topicId](const Lesson& lesson) { return lesson.id == topicId; });
    if (it == lessons_.end()) {
        return std::nullopt;
    }
    return *it;
}

std::string LessonManager::sectionTitle(int sectionId) const {
    if (sectionId < 1 || static_cast<std::size_t>(sectionId) > sectionTitles_.size()) {
        return "";
    }
    return sectionTitles_[static_cast<std::size_t>(sectionId - 1)];
}

int LessonManager::sectionCount() const {
    return static_cast<int>(sectionTitles_.size());
}

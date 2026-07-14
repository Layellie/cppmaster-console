#include "LessonManager.h"

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

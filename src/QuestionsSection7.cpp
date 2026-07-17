#include "QuestionContent.h"

#include "Question.h"

void appendSection7Questions(std::vector<Question>& questions) {
    // Topic 61: struct
    questions.push_back(Question{
        .id = 1523, .topicId = 61,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "struct anahtar kelimesiyle tanımlanan üyelerin varsayılan erişim belirleyicisi nedir?",
        .options = {"public", "private", "protected", "Erişim belirleyicisi yoktur"},
        .acceptedAnswers = {"a"},
        .explanation = "struct üyeleri varsayılan olarak public'tir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1524, .topicId = 61,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "struct Nokta { int x; int y; };\nNokta p;\np.x = 5;\nBu kod derlenir mi?",
        .options = {"Evet, x varsayılan olarak public olduğundan doğrudan erişilebilir", "Hayır, x private olduğundan erişilemez", "Hayır, struct üyelerine asla doğrudan erişilemez", "Evet ama sadece const olarak"},
        .acceptedAnswers = {"a"},
        .explanation = "struct üyeleri varsayılan olarak public olduğundan doğrudan erişilebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1525, .topicId = 61,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "struct ile class arasındaki TEK fonksiyonel fark nedir?",
        .options = {"Varsayılan erişim belirleyicisi (struct: public, class: private)", "struct constructor içeremez", "class kalıtım içeremez", "struct sadece veri tutabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "struct ve class arasındaki tek fark varsayılan erişim belirleyicisidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1526, .topicId = 61,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "struct Sayac {\nprivate:\n    int deger;\npublic:\n    void artir() { deger++; }\n    int getir() { return deger; }\n};\nBu kod geçerli midir (struct içinde private kullanmak)?",
        .options = {"Evet, struct içinde de private/public açıkça belirtilebilir", "Hayır, struct'ta private kullanılamaz", "Hayır, struct sadece public üye alabilir", "Evet ama sadece bir tane private üye olabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "struct'ta da tıpkı class'ta olduğu gibi erişim belirleyicileri açıkça kullanılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1527, .topicId = 61,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "struct Nokta {\n    int x;\n    Nokta(int xd) { x = xd; }\n};\nBu struct bir constructor içerebilir mi?",
        .options = {"Evet, struct da class gibi constructor içerebilir", "Hayır, struct constructor içeremez", "Sadece parametresiz constructor içerebilir", "Sadece class'lar constructor içerebilir"},
        .acceptedAnswers = {"a"},
        .explanation = "struct, class ile aynı yeteneklere sahiptir; constructor içerebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1528, .topicId = 61,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "struct Kutu {\n    int deger = 10;\n};\nKutu k;\nstd::cout << k.deger;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"10", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "deger, varsayılan değeri 10 ile ilklendirilmiştir ve public olduğundan doğrudan okunabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1529, .topicId = 61,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "struct A {\n    int x;\n};\nstruct B {\nprivate:\n    int y;\n};\nint main() {\n    A a;\n    B b;\n    a.x = 1;\n    b.y = 2;\n    return 0;\n}\nBu kod derlenir mi?",
        .options = {"Hayır, b.y satırı derleme hatası verir (y private olarak belirtilmiş)", "Evet, ikisi de derlenir", "Hayır, a.x satırı derleme hatası verir", "Hayır, hiçbiri derlenmez"},
        .acceptedAnswers = {"a"},
        .explanation = "y açıkça private yapıldığından dışarıdan erişilemez; x ise varsayılan public olduğundan sorunsuzdur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1530, .topicId = 61,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "struct Nokta {\n    int x, y;\n    Nokta(int a, int b) : x(a), y(b) {}\n};\nNokta p(3, 4);\nstd::cout << p.x + p.y;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"7", "34", "Derleme hatası", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "Constructor initializer list ile x=3, y=4 olur; toplamları 7'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1531, .topicId = 61,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "struct üyeleri varsayılan olarak public'tir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1532, .topicId = 61,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "struct, class'ın aksine constructor veya metot içeremez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: struct, class ile aynı yeteneklere sahiptir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1533, .topicId = 61,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "struct içinde private veya protected anahtar kelimeleri açıkça kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1534, .topicId = 61,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "struct ve class arasındaki tek fark, struct'ın kalıtımı desteklememesidir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: struct de kalıtımı destekler; tek fark varsayılan erişimdir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1535, .topicId = 61,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "struct Ornek { int x; }; Ornek o; o.x = 5; şeklindeki bir kod, x public olduğu için sorunsuz derlenir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1536, .topicId = 61,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir struct, class gibi birden fazla constructor'a (overload edilmiş) sahip olabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1537, .topicId = 61,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "struct üyelerinin varsayılan erişim belirleyicisi _____ tir (İngilizce kelime).",
        .acceptedAnswers = {"public"},
        .explanation = "struct üyeleri varsayılan olarak public'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1538, .topicId = 61,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "struct Nokta { int x; };\nNokta p;\np.x = 8;\nstd::cout << p.x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "x public olduğundan doğrudan atanıp okunabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1539, .topicId = 61,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "struct ile class'ın davranışlarının farklı olmasının TEK nedeni farklı bir varsayılan erişim _____ olmasıdır (Türkçe kelime).",
        .acceptedAnswers = {"belirleyicisi"},
        .explanation = "Fark, varsayılan erişim belirleyicisidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1540, .topicId = 61,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "struct Kutu {\nprivate:\n    int deger;\npublic:\n    void ata(int d) { deger = d; }\n    int getir() { return deger; }\n};\nKutu k;\nk.ata(15);\nstd::cout << k.getir();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"15"},
        .explanation = "ata(15) deger'i 15 yapar, getir() bu değeri döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1541, .topicId = 61,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "struct Nokta {\n    int x;\n    Nokta(int xd) { x = xd; }\n};\nBu struct, tıpkı bir class gibi bir _____ içerebilir (İngilizce kelime).",
        .acceptedAnswers = {"constructor"},
        .explanation = "struct, class gibi constructor içerebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1542, .topicId = 61,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "struct A { int x; }; struct B { private: int y; }; İkisi de _____ olarak tanımlanabilir çünkü struct, erişim belirleyicilerinin açıkça değiştirilmesine izin verir (Türkçe kelime, 'geçerli' anlamında).",
        .acceptedAnswers = {"geçerli"},
        .explanation = "struct, erişim belirleyicilerinin açıkça belirtilmesine izin verdiğinden ikisi de geçerlidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1543, .topicId = 61,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nNokta p;\np.x = 3;\np.y = 4;\nx ve y adında iki int üyesi olan Nokta adlı bir struct tanımlayan satırları yazın.",
        .acceptedAnswers = {"struct Nokta { int x; int y; };"},
        .explanation = "struct, iki public int üyesiyle tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1544, .topicId = 61,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "struct Sayac {\nprivate:\n    int deger;\npublic:\n    _____\n};\nSayac s;\ns adlı nesnenin deger'ini dışarıdan artırmak için deger'i bir artıran bir artir() metodu tanımlayan satırı yazın.",
        .acceptedAnswers = {"void artir() { deger++; }"},
        .explanation = "artir() metodu, private deger üyesini bir artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1545, .topicId = 61,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "struct Nokta {\n    int x;\n    int y;\n};\nint main() {\n    Nokta p;\n    p.x = 10;\n    p.y = 20;\n    std::cout << p.x + p.y;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30"},
        .explanation = "10 + 20 = 30.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1546, .topicId = 61,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "struct Kutu {\nprivate:\n    int deger;\npublic:\n    Kutu(int d) { deger = d; }\n    int getir() { return deger; }\n};\nint main() {\n    Kutu k(7);\n    std::cout << k.getir() * 2;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"14"},
        .explanation = "getir() 7 döndürür, 7*2=14.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1547, .topicId = 61,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstruct Hesap {\nprivate:\n    int bakiye;\n};\nint main() {\n    Hesap h;\n    h.bakiye = 100;\n    return 0;\n}\n\nBu kod derlenmez çünkü bakiye açıkça private olarak belirtilmiş; struct'ta varsayılan public olsa da, açıkça private yazılan bir üyeye dışarıdan erişilemez. bakiye'yi ayarlayan, Hesap struct'ına eklenmesi gereken public metodu yazın.",
        .acceptedAnswers = {"void bakiyeAta(int d) { bakiye = d; }"},
        .explanation = "private bir üyeye dışarıdan erişmek için public bir metot (setter) gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1548, .topicId = 61,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstruct Nokta {\n    int x;\n    Nokta(int xd) { x = xd; }\n};\nint main() {\n    Nokta p;\n    return 0;\n}\n\nBu kod derlenmez çünkü Nokta'da sadece parametreli bir constructor tanımlanmış; derleyici artık varsayılan (parametresiz) constructor'ı otomatik oluşturmaz. Nokta p; satırını, mevcut constructor'a uygun bir argümanla (örneğin 0) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"Nokta p(0);"},
        .explanation = "Varsayılan constructor olmadığından, nesne mevcut constructor'a uygun bir argümanla oluşturulmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1549, .topicId = 61,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstruct Nokta {\n    int x\n    int y;\n};\n\nProgramcı x üyesinin sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"int x;"},
        .explanation = "Her üye tanımı noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1550, .topicId = 61,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir struct tanımlayıp kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"Nokta p;\n    p.x = 5;\n    std::cout << p.x;\n    return 0;\n}", "struct Nokta {\n    int x;\n};", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "struct tanımı (2), main açılışı (3), kullanım ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1551, .topicId = 61,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "x ve y adında iki int üyesi olan Nokta adlı bir struct tanımlayın; main() içinde bir nesne oluşturup üyelerine değer atayıp toplamlarını yazdırın.",
        .acceptedAnswers = {"struct", "int", "cout"},
        .explanation = "struct iki int üyeyle tanımlanmalı, bir nesne oluşturulup üyeleri toplanıp yazdırılmalıdır.",
        .baseXp = 40,
    });

    // Topic 62: enum
    questions.push_back(Question{
        .id = 1552, .topicId = 62,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "enum Renk { Kirmizi, Yesil, Mavi }; tanımında Kirmizi'nin varsayılan değeri kaçtır?",
        .options = {"0", "1", "-1", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir enum'un ilk değeri varsayılan olarak 0'dır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1553, .topicId = 62,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "enum Renk { Kirmizi, Yesil, Mavi };\nRenk r = Mavi;\nstd::cout << r;\nEkrana ne yazdırılır?",
        .options = {"2", "Mavi", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Mavi, üçüncü değer olduğundan 2'dir; enum değeri int'e örtük dönüşür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1554, .topicId = 62,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir enum değeri, hangi türe örtük olarak (implicit) dönüştürülebilir?",
        .options = {"int", "std::string", "bool", "double (sadece)"},
        .acceptedAnswers = {"a"},
        .explanation = "enum değerleri int'e örtük olarak dönüşür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1555, .topicId = 62,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "enum Boyut { Kucuk, Orta, Buyuk = 10, CokBuyuk };\nCokBuyuk'ün değeri kaçtır?",
        .options = {"11", "3", "10", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "Buyuk = 10 olarak belirtilmiş; CokBuyuk bir sonraki değer olduğundan 11'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1556, .topicId = 62,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "enum Gun { Pazartesi = 1, Sali, Carsamba };\nCarsamba'nın değeri kaçtır?",
        .options = {"3", "2", "0", "1"},
        .acceptedAnswers = {"a"},
        .explanation = "Pazartesi=1, Sali=2, Carsamba=3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1557, .topicId = 62,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "enum A { Deger1 };\nenum B { Deger1 };\nBu iki enum aynı kapsamda (örneğin ikisi de global) tanımlanırsa ne olur?",
        .options = {"Derleme hatası (isim çakışması)", "Sorunsuz derlenir, ikisi bağımsızdır", "B'nin Deger1'i A'nınkini gizler", "Otomatik olarak farklı isimlere dönüştürülür"},
        .acceptedAnswers = {"a"},
        .explanation = "Unscoped enum isimleri kapsayan kapsamda doğrudan görünür olduğundan isim çakışması oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1558, .topicId = 62,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "enum Renk { Kirmizi, Yesil, Mavi };\nint x = Yesil + 1;\nstd::cout << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"2", "1", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "Yesil=1, örtük int dönüşümüyle 1+1=2.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1559, .topicId = 62,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "enum Renk { Kirmizi, Yesil, Mavi };\nRenk r = Kirmizi;\nr = static_cast<Renk>(2);\nstd::cout << r;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"2", "0", "Derleme hatası", "1"},
        .acceptedAnswers = {"a"},
        .explanation = "static_cast<Renk>(2), Mavi değerine (2) karşılık gelir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1560, .topicId = 62,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir enum'un ilk değeri varsayılan olarak 0'dır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1561, .topicId = 62,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir enum değeri, int'e örtük olarak dönüştürülemez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: unscoped enum değerleri int'e örtük dönüşür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1562, .topicId = 62,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "İki farklı enum'da aynı isimli bir değer tanımlamak, aynı kapsamda isim çakışmasına yol açabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1563, .topicId = 62,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir enum'daki değerlere özel bir sayı atanmazsa, her biri bir öncekinden 1 fazla olur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1564, .topicId = 62,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "enum Renk { Kirmizi, Yesil, Mavi }; tanımında Yesil'in değeri 1'dir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1565, .topicId = 62,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "enum içindeki isimler (örneğin Kirmizi), kapsayan kapsamda değil sadece enum adıyla nitelenerek erişilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: unscoped enum isimleri kapsayan kapsamda doğrudan görünür olur; bu, enum class'tan farkıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1566, .topicId = 62,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "enum Renk { Kirmizi, Yesil, Mavi }; tanımında Kirmizi'nin değeri _____ tir (bir sayı).",
        .acceptedAnswers = {"0"},
        .explanation = "İlk değer varsayılan olarak 0'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1567, .topicId = 62,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "enum Renk { Kirmizi, Yesil, Mavi };\nRenk r = Mavi;\nstd::cout << r;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "Mavi=2.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1568, .topicId = 62,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir enum değeri, _____ türüne örtük olarak dönüştürülebilir (İngilizce kelime).",
        .acceptedAnswers = {"int"},
        .explanation = "enum değerleri int'e örtük dönüşür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1569, .topicId = 62,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "enum Boyut { Kucuk, Orta = 5, Buyuk };\nBuyuk'ün değeri _____ olur.",
        .acceptedAnswers = {"6"},
        .explanation = "Orta=5, Buyuk bir sonraki değer olduğundan 6'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1570, .topicId = 62,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "İki farklı enum'da aynı isimli bir değer tanımlamak, aynı kapsamda isim _____ na yol açar (Türkçe kelime).",
        .acceptedAnswers = {"çakışması"},
        .explanation = "Bu duruma isim çakışması denir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1571, .topicId = 62,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "enum Gun { Pazartesi = 1, Sali, Carsamba };\nstd::cout << Sali;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "Pazartesi=1, Sali=2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1572, .topicId = 62,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nRenk r = Yesil;\nstd::cout << r;\nKirmizi, Yesil, Mavi değerlerine sahip Renk adlı bir enum tanımlayan satırı yazın.",
        .acceptedAnswers = {"enum Renk { Kirmizi, Yesil, Mavi };"},
        .explanation = "enum, üç değerle tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1573, .topicId = 62,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "enum Boyut { Kucuk, Orta, Buyuk };\n_____\nstd::cout << b;\nb adlı bir Boyut değişkenini Buyuk değeriyle ilklendiren satırı yazın.",
        .acceptedAnswers = {"Boyut b = Buyuk;"},
        .explanation = "b, Buyuk değeriyle ilklendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1574, .topicId = 62,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "enum Renk { Kirmizi, Yesil, Mavi };\nint main() {\n    Renk r = Kirmizi;\n    std::cout << r;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0"},
        .explanation = "Kirmizi=0.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1575, .topicId = 62,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "enum Boyut { Kucuk, Orta = 3, Buyuk };\nint main() {\n    std::cout << Kucuk << Orta << Buyuk;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"034"},
        .explanation = "Kucuk=0, Orta=3, Buyuk=4 (Orta'dan bir sonraki): '034'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1576, .topicId = 62,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nenum Renk { Kirmizi, Yesil, Mavi };\nenum Meyve { Kirmizi, Yesil, Sari };\n\nBu kod derlenmez çünkü Kirmizi ve Yesil isimleri hem Renk hem de Meyve enum'ında aynı kapsamda tanımlanmış, isim çakışmasına yol açıyor. Bu sorunu çözen (isim çakışmasını önleyen), bir sonraki konuda öğrenilecek C++11 özelliğinin adını (iki kelime, İngilizce) yazın.",
        .acceptedAnswers = {"enum class"},
        .explanation = "enum class, değerleri kendi kapsamına hapsederek isim çakışmasını önler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1577, .topicId = 62,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nenum Boyut { Kucuk, Orta, Buyuk };\nBoyut b = 1;\nstd::cout << b;\n\nBu kod derlenmez çünkü bir int literali (1), bir enum değişkenine örtük olarak atanamaz (tersi - enum'dan int'e - geçerlidir, ama int'ten enum'a değil). Hatalı satırı, static_cast ile düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"Boyut b = static_cast<Boyut>(1);"},
        .explanation = "int'ten enum'a dönüşüm için static_cast gerekir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1578, .topicId = 62,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nenum Renk { Kirmizi Yesil Mavi };\n\nProgramcı değerler arasına virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"enum Renk { Kirmizi, Yesil, Mavi };"},
        .explanation = "enum değerleri virgülle ayrılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1579, .topicId = 62,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir enum tanımlayıp kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"Renk r = Mavi;\n    std::cout << r;\n    return 0;\n}", "enum Renk { Kirmizi, Yesil, Mavi };", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "enum tanımı (2), main açılışı (3), kullanım ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1580, .topicId = 62,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "En az üç değer içeren bir enum tanımlayın; main() içinde bir değişken oluşturup bir değerle ilklendirip ekrana yazdırın.",
        .acceptedAnswers = {"enum", "cout"},
        .explanation = "enum en az üç değerle tanımlanmalı ve bir değişken üzerinden kullanılmalıdır.",
        .baseXp = 40,
    });

    // Topic 63: enum class
    questions.push_back(Question{
        .id = 1581, .topicId = 63,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "enum class'ın enum'a göre temel farkı nedir?",
        .options = {"Değerlerine mutlaka enum adıyla nitelenerek erişilir ve int'e örtük dönüşmez", "enum class daha az değer alabilir", "enum class sadece string değer alabilir", "Fark yoktur, ikisi aynıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "enum class değerleri nitelenmiş erişim gerektirir ve int'e örtük dönüşmez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1582, .topicId = 63,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "enum class Renk { Kirmizi, Yesil, Mavi };\nRenk r = Renk::Yesil;\nBu satır derlenir mi?",
        .options = {"Evet, Renk:: öneki ile doğru erişim yapılmış", "Hayır, enum class hiç kullanılamaz", "Hayır, önek yanlış", "Evet ama sadece Kirmizi için"},
        .acceptedAnswers = {"a"},
        .explanation = "Renk::Yesil, doğru nitelenmiş erişimdir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1583, .topicId = 63,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "enum class Renk { Kirmizi, Yesil, Mavi };\nRenk r = Yesil;\nBu satır (Renk:: öneki olmadan) derlenir mi?",
        .options = {"Hayır, enum class değerlerine mutlaka EnumAdi:: ile erişilmelidir", "Evet, enum class da unscoped enum gibi davranır", "Evet ama sadece ilk değer için", "Hayır, Renk türü geçersizdir"},
        .acceptedAnswers = {"a"},
        .explanation = "enum class değerlerine önek olmadan erişmek derleme hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1584, .topicId = 63,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "enum class Renk { Kirmizi, Yesil, Mavi };\nint x = Renk::Yesil;\nBu satır (static_cast olmadan) derlenir mi?",
        .options = {"Hayır, enum class değerleri int'e örtük dönüşmez", "Evet, enum class da örtük dönüşür", "Evet ama sadece Kirmizi için", "Hayır, Renk::Yesil geçersiz bir değerdir"},
        .acceptedAnswers = {"a"},
        .explanation = "enum class değerleri int'e örtük dönüşmez, static_cast gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1585, .topicId = 63,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "enum class Renk { Kirmizi, Yesil, Mavi };\nint x = static_cast<int>(Renk::Mavi);\nstd::cout << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"2", "1", "Derleme hatası", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "Mavi, üçüncü değer olduğundan 2'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1586, .topicId = 63,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "enum class bir class veya struct DEĞİLDİR ama isim çakışmasını class/struct'a benzer şekilde nasıl önler?",
        .options = {"Değerleri kendi enum adının kapsamına (scope) hapsederek", "Otomatik olarak private yaparak", "Değerleri string'e çevirerek", "Sadece bir değer tanımlanmasına izin vererek"},
        .acceptedAnswers = {"a"},
        .explanation = "enum class, değerleri kendi adının kapsamına hapseder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1587, .topicId = 63,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "enum class A { X };\nenum class B { X };\nBu iki enum class aynı kapsamda tanımlanırsa ne olur?",
        .options = {"Sorunsuz derlenir, çünkü A::X ve B::X birbirinden bağımsız ve nitelenmiş isimlerdir", "Derleme hatası (isim çakışması)", "Sadece biri kullanılabilir", "B'nin X'i A'nınkini gizler"},
        .acceptedAnswers = {"a"},
        .explanation = "enum class değerleri kendi enum adının kapsamına hapsedildiğinden çakışma olmaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1588, .topicId = 63,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "enum class Renk { Kirmizi, Yesil, Mavi };\nRenk r = Renk::Yesil;\nRenk r2 = static_cast<Renk>(static_cast<int>(r) + 1);\nstd::cout << static_cast<int>(r2);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"2", "1", "Derleme hatası", "3"},
        .acceptedAnswers = {"a"},
        .explanation = "r=Yesil(1); r2 = static_cast<Renk>(1+1) = Mavi(2).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1589, .topicId = 63,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "enum class değerlerine her zaman EnumAdi:: öneki ile erişilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1590, .topicId = 63,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "enum class değerleri, enum'daki gibi int'e örtük olarak dönüşür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: enum class değerleri int'e örtük dönüşmez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1591, .topicId = 63,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "enum class, C++11 ile gelmiştir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1592, .topicId = 63,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "İki farklı enum class'ta aynı isimli bir değer (örneğin ikisinde de X) tanımlamak isim çakışmasına yol açar.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: her enum class kendi kapsamına sahip olduğundan çakışma olmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1593, .topicId = 63,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "enum class bir değeri int'e dönüştürmek için static_cast<int> kullanılması gerekir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1594, .topicId = 63,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "enum class, enum'ın isim çakışması problemini çözer.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1595, .topicId = 63,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "enum class Renk { Kirmizi, Yesil };\nYesil değerine erişmek için _____::Yesil yazılmalıdır (enum adı).",
        .acceptedAnswers = {"Renk"},
        .explanation = "Değere Renk:: öneki ile erişilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1596, .topicId = 63,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "enum class Renk { Kirmizi, Yesil, Mavi };\nRenk r = Renk::Mavi;\nstd::cout << static_cast<int>(r);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "Mavi=2.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1597, .topicId = 63,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "enum class değerini int'e dönüştürmek için _____<int> kullanılır (İngilizce, bir kelime).",
        .acceptedAnswers = {"static_cast"},
        .explanation = "static_cast<int> ile açık dönüşüm yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1598, .topicId = 63,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "enum class Renk { Kirmizi, Yesil, Mavi };\nint main() {\n    Renk r = Kirmizi;\n}\nBu kod derlenmez çünkü Kirmizi'nin başına _____:: öneki eksik (enum adı).",
        .acceptedAnswers = {"Renk"},
        .explanation = "Renk:: öneki eklenmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1599, .topicId = 63,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "enum class, iki farklı enum'da aynı isimli değerler kullanıldığında oluşan isim _____ nı önler (Türkçe kelime).",
        .acceptedAnswers = {"çakışmasını"},
        .explanation = "enum class isim çakışmasını önler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1600, .topicId = 63,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "enum class Renk { Kirmizi, Yesil, Mavi };\nint x = Renk::Kirmizi;\nBu satır _____ verir çünkü örtük dönüşüm yoktur (Türkçe kelime).",
        .acceptedAnswers = {"hata", "derleme hatası"},
        .explanation = "enum class değerleri örtük olarak int'e dönüşmediğinden bu bir derleme hatasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1601, .topicId = 63,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nRenk r = Renk::Mavi;\nstd::cout << static_cast<int>(r);\nKirmizi, Yesil, Mavi değerlerine sahip bir enum class Renk tanımlayan satırı yazın.",
        .acceptedAnswers = {"enum class Renk { Kirmizi, Yesil, Mavi };"},
        .explanation = "enum class, üç değerle tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1602, .topicId = 63,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "enum class Boyut { Kucuk, Orta, Buyuk };\n_____\nstd::cout << static_cast<int>(b);\nb adlı bir Boyut değişkenini Boyut::Buyuk değeriyle ilklendiren satırı yazın.",
        .acceptedAnswers = {"Boyut b = Boyut::Buyuk;"},
        .explanation = "b, Boyut::Buyuk değeriyle ilklendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1603, .topicId = 63,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "enum class Renk { Kirmizi, Yesil, Mavi };\nint main() {\n    Renk r = Renk::Kirmizi;\n    std::cout << static_cast<int>(r);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0"},
        .explanation = "Kirmizi=0.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1604, .topicId = 63,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "enum class Boyut { Kucuk, Orta, Buyuk };\nint main() {\n    Boyut b1 = Boyut::Orta;\n    Boyut b2 = Boyut::Buyuk;\n    std::cout << static_cast<int>(b1) << static_cast<int>(b2);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "Orta=1, Buyuk=2: '12'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1605, .topicId = 63,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nenum class Renk { Kirmizi, Yesil, Mavi };\nint main() {\n    Renk r = Yesil;\n    return 0;\n}\n\nBu kod derlenmez çünkü Yesil, Renk:: öneki olmadan kullanılmış. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"Renk r = Renk::Yesil;"},
        .explanation = "enum class değerlerine mutlaka nitelenmiş erişilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1606, .topicId = 63,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nenum class Renk { Kirmizi, Yesil, Mavi };\nint main() {\n    int x = Renk::Mavi;\n    return 0;\n}\n\nBu kod derlenmez çünkü enum class değeri int'e örtük olarak dönüştürülemez. Hatalı satırı, static_cast ile düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int x = static_cast<int>(Renk::Mavi);"},
        .explanation = "int'e dönüşüm için static_cast gerekir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1607, .topicId = 63,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nenum class Renk { Kirmizi, Yesil, Mavi };\nint main() {\n    Renk r = Renk::Yesil;\n    if (r == 1) {\n        std::cout << \"yesil\";\n    }\n    return 0;\n}\n\nProgramcı r'yi doğrudan bir int (1) ile karşılaştırmaya çalışmış; enum class örtük dönüşmediği için bu derlenmez. Karşılaştırma satırını, doğru enum class değeriyle düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (r == Renk::Yesil) {"},
        .explanation = "Karşılaştırma, aynı türden bir enum class değeriyle yapılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1608, .topicId = 63,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir enum class tanımlayıp kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"Renk r = Renk::Mavi;\n    std::cout << static_cast<int>(r);\n    return 0;\n}", "enum class Renk { Kirmizi, Yesil, Mavi };", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "enum class tanımı (2), main açılışı (3), kullanım ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1609, .topicId = 63,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "En az üç değer içeren bir enum class tanımlayın; main() içinde bir değişken oluşturup bir değerle (EnumAdi:: öneki ile) ilklendirip static_cast<int> ile ekrana yazdırın.",
        .acceptedAnswers = {"enum class", "static_cast", "cout"},
        .explanation = "enum class değeri nitelenmiş erişimle ilklendirilip static_cast ile yazdırılmalıdır.",
        .baseXp = 40,
    });

    // Topic 64: Sınıf ve nesne
    questions.push_back(Question{
        .id = 1610, .topicId = 64,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "class anahtar kelimesiyle tanımlanan üyelerin varsayılan erişim belirleyicisi nedir?",
        .options = {"private", "public", "protected", "Erişim belirleyicisi yoktur"},
        .acceptedAnswers = {"a"},
        .explanation = "class üyeleri varsayılan olarak private'tir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1611, .topicId = 64,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir sınıf (class) ile bir nesne (object) arasındaki ilişki nedir?",
        .options = {"Sınıf bir şablondur, nesne o şablonun somut bir örneğidir", "İkisi aynı şeydir", "Nesne şablondur, sınıf örnektir", "Aralarında bir ilişki yoktur"},
        .acceptedAnswers = {"a"},
        .explanation = "Sınıf bir şablon, nesne o şablonun somut bir örneğidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1612, .topicId = 64,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Araba {\npublic:\n    int hiz;\n};\nAraba a;\na.hiz = 50;\nBu kod derlenir mi?",
        .options = {"Evet, hiz public olarak belirtilmiş", "Hayır, class üyelerine asla erişilemez", "Hayır, hiz varsayılan olarak private'tir ve public denmemiş sayılır", "Evet ama sadece const olarak"},
        .acceptedAnswers = {"a"},
        .explanation = "hiz açıkça public yapıldığından dışarıdan erişilebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1613, .topicId = 64,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Araba {\n    int hiz;\n};\nAraba a;\na.hiz = 50;\nBu kod derlenir mi (public yazılmadan)?",
        .options = {"Hayır, hiz varsayılan olarak private'tir, dışarıdan erişilemez", "Evet, class üyeleri varsayılan olarak public'tir", "Evet, int türü her zaman public'tir", "Hayır, Araba sınıfı geçersizdir"},
        .acceptedAnswers = {"a"},
        .explanation = "class üyeleri varsayılan olarak private'tir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1614, .topicId = 64,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n    void artir() { deger++; }\n};\nSayac s;\ns.artir();\ns.artir();\nstd::cout << s.deger;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"2", "0", "1", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "İki artir() çağrısı deger'i 0'dan 2'ye çıkarır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1615, .topicId = 64,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Aynı sınıftan kaç tane BAĞIMSIZ nesne oluşturulabilir?",
        .options = {"Sınırsız (bellek izin verdiği sürece)", "Sadece bir tane", "En fazla iki tane", "Sınıf başına sabit bir sayı"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir sınıftan bellek izin verdiği sürece sınırsız sayıda bağımsız nesne oluşturulabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1616, .topicId = 64,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n};\nSayac s1;\nSayac s2;\ns1.deger = 5;\nstd::cout << s1.deger << \" \" << s2.deger;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"5 0\"", "\"5 5\"", "\"0 0\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Her nesnenin kendi bağımsız deger'i vardır; s2.deger varsayılan 0'da kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1617, .topicId = 64,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Nokta {\npublic:\n    int x;\n};\nNokta p1;\np1.x = 10;\nNokta p2 = p1;\np2.x = 20;\nstd::cout << p1.x << \" \" << p2.x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"10 20\"", "\"20 20\"", "\"10 10\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p2 = p1, üyeleri kopyalar; p2.x'in sonradan değişmesi p1.x'i etkilemez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1618, .topicId = 64,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "class üyeleri varsayılan olarak private'tir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1619, .topicId = 64,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir sınıf (class), bir nesnenin somut bir örneğidir; nesne ise şablondur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: durum tam tersidir - sınıf şablon, nesne örnektir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1620, .topicId = 64,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Aynı sınıftan birden fazla bağımsız nesne oluşturulabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1621, .topicId = 64,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "class üyelerinin varsayılan erişimi, struct ile aynıdır (ikisi de public).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: class private, struct public'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1622, .topicId = 64,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir nesnenin bir üyesi değiştirildiğinde, aynı sınıftan oluşturulmuş başka bir nesnenin aynı üyesi de otomatik olarak değişir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: her nesnenin üyeleri bağımsızdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1623, .topicId = 64,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir nesne başka bir nesneye (aynı türden) atandığında (p2 = p1;), üyeler tek tek kopyalanır ve iki nesne birbirinden bağımsız hale gelir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1624, .topicId = 64,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "class üyelerinin varsayılan erişim belirleyicisi _____ tir (İngilizce kelime).",
        .acceptedAnswers = {"private"},
        .explanation = "class üyeleri varsayılan olarak private'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1625, .topicId = 64,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "class Araba {\npublic:\n    int hiz;\n};\nAraba a;\na.hiz = 40;\nstd::cout << a.hiz;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"40"},
        .explanation = "hiz public olduğundan doğrudan atanıp okunabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1626, .topicId = 64,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir sınıfın somut bir örneğine _____ denir (Türkçe kelime).",
        .acceptedAnswers = {"nesne"},
        .explanation = "Bir sınıfın somut örneğine nesne (object) denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1627, .topicId = 64,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n    void artir() { deger++; }\n};\nSayac s;\ns.artir();\ns.artir();\ns.artir();\nstd::cout << s.deger;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "Üç artir() çağrısı deger'i 3 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1628, .topicId = 64,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\n    int x;\n};\nNokta p;\np.x = 5;\nBu kod _____ verir çünkü x varsayılan olarak private'tir (Türkçe kelime).",
        .acceptedAnswers = {"hata", "derleme hatası"},
        .explanation = "x varsayılan private olduğundan dışarıdan erişim derleme hatasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1629, .topicId = 64,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Aynı sınıftan oluşturulan her nesne, kendi üyelerinin _____ bir kopyasına sahiptir (Türkçe kelime).",
        .acceptedAnswers = {"bağımsız"},
        .explanation = "Her nesnenin üyeleri bağımsızdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1630, .topicId = 64,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nAraba a;\na.hiz = 60;\nstd::cout << a.hiz;\nhiz adlı public bir int üyesi olan Araba adlı bir class tanımlayan satırları yazın.",
        .acceptedAnswers = {"class Araba { public: int hiz; };"},
        .explanation = "class, public bir int üyeyle tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1631, .topicId = 64,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n    _____\n};\nSayac s;\ns.artir();\nstd::cout << s.deger;\ndeger'i bir artıran artir() metodunu tanımlayan satırı yazın.",
        .acceptedAnswers = {"void artir() { deger++; }"},
        .explanation = "artir() metodu deger'i bir artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1632, .topicId = 64,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    int deger = 0;\n    void artir() { deger++; }\n};\nint main() {\n    Sayac s;\n    s.artir();\n    s.artir();\n    std::cout << s.deger;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2"},
        .explanation = "İki artir() çağrısı deger'i 2 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1633, .topicId = 64,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class Nokta {\npublic:\n    int x;\n};\nint main() {\n    Nokta p1;\n    p1.x = 5;\n    Nokta p2 = p1;\n    p1.x = 99;\n    std::cout << p1.x << \" \" << p2.x;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"99 5"},
        .explanation = "p2 = p1 anında x'in kopyasını (5) alır; p1.x'in sonradan değişmesi (99) p2.x'i etkilemez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1634, .topicId = 64,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Nokta {\n    int x;\n};\nint main() {\n    Nokta p;\n    p.x = 5;\n    return 0;\n}\n\nBu kod derlenmez çünkü x, class içinde varsayılan olarak private'tir. x'i public yapan, class tanımının düzeltilmiş halini (üye tanımından önceki kısmı) yazın.",
        .acceptedAnswers = {"class Nokta { public:"},
        .explanation = "x'in dışarıdan erişilebilmesi için public yapılması gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1635, .topicId = 64,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nclass Sayac {\npublic:\n    int deger = 0;\n};\nint main() {\n    Sayac s1;\n    Sayac s2;\n    s1.deger = 10;\n    if (s2.deger == 10) {\n        std::cout << \"esit\";\n    } else {\n        std::cout << \"farkli\";\n    }\n    return 0;\n}\n\nBu kod derleme hatası vermez ama s2.deger hala 0 olduğundan çıktı 'farkli' olur. Programcının BEKLEDİĞİ ('esit') çıktıyı elde etmesi için s2.deger'in de 10 yapıldığı ekstra bir atama satırı ekleyin.",
        .acceptedAnswers = {"s2.deger = 10;"},
        .explanation = "s1 ve s2 bağımsız nesneler olduğundan s2.deger'in de ayrıca 10 yapılması gerekir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1636, .topicId = 64,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Nokta {\n    int x;\n    int y;\n};\nint main() {\n    Nokta p;\n    p.x = 1;\n    p.y = 2;\n    return 0;\n}\n\nBu kod derlenmez çünkü x ve y varsayılan olarak private'tir. class tanımını, üyeleri public yaparak düzeltilmiş haliyle (class başlığından üye tanımlarına kadar olan kısmı) yazın.",
        .acceptedAnswers = {"class Nokta { public: int x; int y; };"},
        .explanation = "Üyelerin dışarıdan erişilebilmesi için public yapılması gerekir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1637, .topicId = 64,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir class tanımlayıp nesne oluşturan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"Araba a;\n    a.hiz = 30;\n    std::cout << a.hiz;\n    return 0;\n}", "class Araba {\npublic:\n    int hiz;\n};", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class tanımı (2), main açılışı (3), kullanım ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1638, .topicId = 64,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "hiz adlı public bir int üyesi olan Araba adlı bir class tanımlayın; main() içinde iki bağımsız nesne oluşturup farklı hiz değerleri atayıp ikisini de yazdırın.",
        .acceptedAnswers = {"class", "public", "cout"},
        .explanation = "İki bağımsız Araba nesnesi oluşturulup farklı hiz değerleri atanmalı ve yazdırılmalıdır.",
        .baseXp = 40,
    });
}

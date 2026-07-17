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

    // Topic 65: Constructor
    questions.push_back(Question{
        .id = 1639, .topicId = 65,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir constructor'ın adı ne olmalıdır?",
        .options = {"Sınıfın adıyla aynı", "init", "new", "Herhangi bir isim olabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "Constructor, sınıfla aynı isme sahiptir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1640, .topicId = 65,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir constructor'ın dönüş türü nedir?",
        .options = {"Dönüş türü yoktur (void bile yazılmaz)", "void", "int", "Sınıfın kendi türü"},
        .acceptedAnswers = {"a"},
        .explanation = "Constructor'ların hiçbir dönüş türü yoktur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1641, .topicId = 65,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) { x = xd; }\n};\nNokta p(5);\nstd::cout << p.x;\nEkrana ne yazdırılır?",
        .options = {"5", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "Constructor, x'i 5 ile ilklendirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1642, .topicId = 65,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir sınıfta hiçbir constructor tanımlanmazsa ne olur?",
        .options = {"Derleyici parametresiz bir varsayılan constructor otomatik oluşturur", "Nesne asla oluşturulamaz", "Derleme hatası oluşur", "Tüm üyeler otomatik olarak public olur"},
        .acceptedAnswers = {"a"},
        .explanation = "Hiç constructor tanımlanmazsa derleyici varsayılan bir constructor oluşturur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1643, .topicId = 65,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) { x = xd; }\n};\nNokta p;\nBu satır derlenir mi?",
        .options = {"Hayır, çünkü sadece parametreli bir constructor tanımlanmış ve varsayılan constructor otomatik oluşturulmaz", "Evet, x otomatik olarak 0 olur", "Evet, her zaman bir varsayılan constructor vardır", "Hayır, Nokta sınıfı hatalı tanımlanmış"},
        .acceptedAnswers = {"a"},
        .explanation = "En az bir constructor tanımlandığından derleyici varsayılan constructor'ı otomatik oluşturmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1644, .topicId = 65,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x, y;\n    Nokta() { x = 0; y = 0; }\n    Nokta(int xd, int yd) { x = xd; y = yd; }\n};\nNokta p1;\nNokta p2(3, 4);\nstd::cout << p1.x << p2.x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"03\"", "\"00\"", "\"33\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p1 varsayılan constructor ile x=0 olur; p2 parametreli constructor ile x=3 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1645, .topicId = 65,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Kutu {\npublic:\n    int deger;\n    Kutu() { deger = 100; }\n    Kutu(int d) { deger = d; }\n};\nKutu k1;\nKutu k2(5);\nstd::cout << k1.deger << \" \" << k2.deger;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"100 5\"", "\"100 100\"", "\"5 5\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "k1 varsayılan constructor ile 100 olur; k2 parametreli constructor ile 5 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1646, .topicId = 65,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Sayac {\npublic:\n    int deger;\n    Sayac(int baslangic = 0) { deger = baslangic; }\n};\nSayac s1;\nSayac s2(10);\nstd::cout << s1.deger << \" \" << s2.deger;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"0 10\"", "\"10 10\"", "Derleme hatası", "\"0 0\""},
        .acceptedAnswers = {"a"},
        .explanation = "Varsayılan parametreli constructor, s1 için varsayılan (0), s2 için verilen (10) değeri kullanır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1647, .topicId = 65,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir constructor'ın adı, sınıfın adıyla aynı olmalıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1648, .topicId = 65,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir constructor'ın bir dönüş türü vardır (örneğin void).",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: constructor'ların hiçbir dönüş türü yoktur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1649, .topicId = 65,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir sınıfta birden fazla constructor (overload edilmiş) tanımlanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1650, .topicId = 65,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Eğer bir sınıfta sadece parametreli bir constructor tanımlanırsa, derleyici yine de parametresiz bir varsayılan constructor otomatik oluşturur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: en az bir constructor tanımlanınca derleyici varsayılan constructor oluşturmayı bırakır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1651, .topicId = 65,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Varsayılan parametre değerine sahip bir constructor (örneğin Sayac(int x = 0)), hem parametresiz hem de parametreli çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1652, .topicId = 65,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir sınıfta hiç constructor tanımlanmazsa, o sınıftan asla nesne oluşturulamaz.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: derleyici bu durumda varsayılan bir constructor otomatik oluşturur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1653, .topicId = 65,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir constructor'ın adı, ait olduğu _____ ile aynı olmalıdır (Türkçe kelime, örn. 'sınıf').",
        .acceptedAnswers = {"sınıf"},
        .explanation = "Constructor adı sınıf adıyla aynı olmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1654, .topicId = 65,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) { x = xd; }\n};\nNokta p(9);\nstd::cout << p.x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"9"},
        .explanation = "Constructor x'i 9 ile ilklendirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1655, .topicId = 65,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir constructor'ın dönüş türü _____ tir (Türkçe kelime, 'hiç yok' anlamında).",
        .acceptedAnswers = {"yok"},
        .explanation = "Constructor'ların dönüş türü yoktur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1656, .topicId = 65,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Kutu {\npublic:\n    int deger;\n    Kutu() { deger = 5; }\n};\nKutu k;\nstd::cout << k.deger;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "Varsayılan constructor deger'i 5 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1657, .topicId = 65,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir sınıfta EN AZ BİR constructor tanımlanırsa, derleyici artık _____ constructor'ı otomatik oluşturmaz (Türkçe kelime).",
        .acceptedAnswers = {"varsayılan"},
        .explanation = "Bu durumda derleyici varsayılan constructor'ı oluşturmayı bırakır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1658, .topicId = 65,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Sayac {\npublic:\n    int deger;\n    Sayac(int b = 0) { deger = b; }\n};\nSayac s;\nstd::cout << s.deger;\nEkran çıktısı _____ olur (varsayılan parametre değeri kullanıldığı için).",
        .acceptedAnswers = {"0"},
        .explanation = "Varsayılan parametre değeri (0) kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1659, .topicId = 65,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x;\n    _____\n};\nNokta p(7);\nstd::cout << p.x;\nx'i parametre olarak alan bir constructor tanımlayan satırı yazın.",
        .acceptedAnswers = {"Nokta(int xd) { x = xd; }"},
        .explanation = "Constructor, parametreyle x'i ilklendirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1660, .topicId = 65,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Kutu {\npublic:\n    int deger;\n    Kutu(int d) { deger = d; }\n};\nint main() {\n    _____\n    std::cout << k.deger;\n    return 0;\n}\nKutu türünde, 42 değeriyle ilklendirilmiş bir k nesnesi oluşturan satırı yazın.",
        .acceptedAnswers = {"Kutu k(42);"},
        .explanation = "k, constructor'a 42 argümanıyla oluşturulur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1661, .topicId = 65,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Nokta {\npublic:\n    int x, y;\n    Nokta(int xd, int yd) { x = xd; y = yd; }\n};\nint main() {\n    Nokta p(6, 9);\n    std::cout << p.x + p.y;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"15"},
        .explanation = "6 + 9 = 15.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1662, .topicId = 65,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class Kutu {\npublic:\n    int deger;\n    Kutu() { deger = 1; }\n    Kutu(int d) { deger = d * 2; }\n};\nint main() {\n    Kutu k1;\n    Kutu k2(5);\n    std::cout << k1.deger << \" \" << k2.deger;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 10"},
        .explanation = "k1 varsayılan constructor ile 1 olur; k2 parametreli constructor ile 5*2=10 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1663, .topicId = 65,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Nokta {\npublic:\n    int x;\n    Nokta(int xd) { x = xd; }\n};\nint main() {\n    Nokta p;\n    return 0;\n}\n\nBu kod derlenmez çünkü Nokta'da sadece parametreli bir constructor var; derleyici varsayılan constructor'ı otomatik oluşturmaz. Nokta p; satırını, mevcut constructor'a bir argüman (örneğin 0) vererek düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"Nokta p(0);"},
        .explanation = "Mevcut parametreli constructor'a uygun bir argüman verilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1664, .topicId = 65,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Kutu {\npublic:\n    int deger;\n    void Kutu(int d) { deger = d; }\n};\n\nBu kod derlenmez çünkü constructor'ların dönüş türü yoktur (void bile yazılmaz); void yazmak Kutu'yu sıradan bir metot yapar, gerçek bir constructor olmaktan çıkarır. Hatalı satırı, dönüş türü olmadan (gerçek bir constructor olarak) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"Kutu(int d) { deger = d; }"},
        .explanation = "Constructor'ların dönüş türü (void dahil) olmamalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1665, .topicId = 65,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Nokta {\npublic:\n    int x;\n    Nokta(int xd) { x = xd }\n};\n\nProgramcı x = xd; satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"x = xd;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1666, .topicId = 65,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir constructor tanımlayıp nesne oluşturan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"Nokta p(5);\n    std::cout << p.x;\n    return 0;\n}", "class Nokta {\npublic:\n    int x;\n    Nokta(int xd) { x = xd; }\n};", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class+constructor tanımı (2), main açılışı (3), kullanım ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1667, .topicId = 65,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "x adlı bir int üyesi ve bunu parametre olarak alan bir constructor içeren Nokta adlı bir class tanımlayın; main() içinde bir nesne oluşturup x'i yazdırın.",
        .acceptedAnswers = {"class", "Nokta", "cout"},
        .explanation = "Constructor parametreyle x'i ilklendirmeli, main() içinde kullanılmalıdır.",
        .baseXp = 40,
    });

    // Topic 66: Destructor
    questions.push_back(Question{
        .id = 1668, .topicId = 66,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir destructor'ın adı nasıl yazılır?",
        .options = {"Sınıf adının başına ~ konarak", "Sınıf adının sonuna ~ konarak", "destructor anahtar kelimesiyle", "del anahtar kelimesiyle"},
        .acceptedAnswers = {"a"},
        .explanation = "Destructor, sınıf adının başına ~ konularak yazılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1669, .topicId = 66,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir destructor parametre alabilir mi?",
        .options = {"Hayır, destructor parametre alamaz", "Evet, istenildiği kadar parametre alabilir", "Sadece bir parametre alabilir", "Sadece const parametre alabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "Destructor hiçbir parametre alamaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1670, .topicId = 66,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir sınıfın kaç tane destructor'ı olabilir?",
        .options = {"Tam olarak bir tane", "Overload edilerek birden fazla", "Hiç olmayabilir, hiçbir zaman çağrılmaz", "Sınırsız sayıda"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir sınıfın sadece bir destructor'ı olabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1671, .topicId = 66,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Stack üzerinde (otomatik/local) oluşturulan bir nesnenin destructor'ı ne zaman çağrılır?",
        .options = {"Nesne kapsamdan (scope) çıktığında otomatik olarak", "Sadece programcı açıkça çağırırsa", "Program tamamen bittiğinde", "Hiçbir zaman otomatik çağrılmaz"},
        .acceptedAnswers = {"a"},
        .explanation = "Stack nesnesi kapsamdan çıktığında destructor otomatik çağrılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1672, .topicId = 66,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "new ile heap'te oluşturulan bir nesnenin destructor'ı ne zaman çağrılır?",
        .options = {"delete çağrıldığında", "Otomatik olarak, pointer kapsamdan çıktığında", "Hiçbir zaman çağrılmaz", "new çağrıldığı anda"},
        .acceptedAnswers = {"a"},
        .explanation = "Heap nesnesinin destructor'ı sadece delete çağrıldığında çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1673, .topicId = 66,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Kaynak {\npublic:\n    ~Kaynak() { std::cout << \"Yok edildi\"; }\n};\nint main() {\n    Kaynak* p = new Kaynak();\n    return 0;\n}\n(delete p; hiç çağrılmıyor) Bu programda \"Yok edildi\" yazdırılır mı?",
        .options = {"Hayır, delete hiç çağrılmadığından destructor çalışmaz", "Evet, program bitince otomatik çağrılır", "Evet, new çağrıldığı anda çağrılır", "Derleme hatası verir"},
        .acceptedAnswers = {"a"},
        .explanation = "delete çağrılmadığından destructor hiçbir zaman çalışmaz (bellek sızıntısı).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1674, .topicId = 66,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Kaynak {\npublic:\n    Kaynak() { std::cout << \"Ac \"; }\n    ~Kaynak() { std::cout << \"Kapa \"; }\n};\nint main() {\n    {\n        Kaynak k;\n    }\n    std::cout << \"Devam \";\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"Ac Kapa Devam \"", "\"Ac Devam Kapa \"", "\"Devam Ac Kapa \"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "k, iç blok bitiminde (Devam'dan ÖNCE) kapsamdan çıkar ve destructor çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1675, .topicId = 66,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class A {\npublic:\n    ~A() { std::cout << \"~A \"; }\n};\nclass B {\npublic:\n    ~B() { std::cout << \"~B \"; }\n};\nint main() {\n    A a;\n    B b;\n    return 0;\n}\nmain sonlanırken a ve b hangi sırayla yok edilir (ekran çıktısı nedir)?",
        .options = {"\"~B ~A \"", "\"~A ~B \"", "Sıra belirsizdir", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Yerel nesneler, tanımlanma sırasının tersine yok edilir; b sonra tanımlandığından önce yok edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1676, .topicId = 66,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir destructor'ın adı, sınıf adının başına ~ konularak yazılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1677, .topicId = 66,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir destructor parametre alabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: destructor parametre alamaz.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1678, .topicId = 66,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir sınıfın sadece bir destructor'ı olabilir; overload edilemez.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1679, .topicId = 66,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Stack üzerinde oluşturulan bir nesnenin destructor'ı, nesne kapsamdan çıktığında otomatik çağrılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1680, .topicId = 66,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "new ile oluşturulan bir nesnenin pointer'ı hiç delete edilmezse, o nesnenin destructor'ı yine de bir noktada otomatik çağrılır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: delete çağrılmadıkça destructor hiçbir zaman çalışmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1681, .topicId = 66,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Aynı kapsamda art arda tanımlanan yerel nesneler, tanımlanma sırasının TERSİNE (son tanımlanan ilk yok edilir) yok edilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1682, .topicId = 66,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir destructor'ın adı sınıf adının başına _____ konularak yazılır (bir sembol).",
        .acceptedAnswers = {"~"},
        .explanation = "~ sembolü destructor'ı belirtir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1683, .topicId = 66,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir destructor, tıpkı bir constructor gibi _____ almaz (Türkçe kelime, çoğul).",
        .acceptedAnswers = {"parametre"},
        .explanation = "Destructor parametre almaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1684, .topicId = 66,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Bir sınıfın kaç tane destructor'ı olabilir? _____ (bir sayı, rakamla).",
        .acceptedAnswers = {"1"},
        .explanation = "Bir sınıfın sadece bir destructor'ı olabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1685, .topicId = 66,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "class Kaynak {\npublic:\n    ~Kaynak() { std::cout << \"Bitti\"; }\n};\nint main() {\n    Kaynak k;\n    return 0;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"Bitti"},
        .explanation = "k, main sonlanırken kapsamdan çıkar ve destructor çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1686, .topicId = 66,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "new ile heap'te oluşturulan bir nesnenin destructor'ı ancak _____ çağrıldığında çalışır (İngilizce kelime).",
        .acceptedAnswers = {"delete"},
        .explanation = "Heap nesnesinin destructor'ı sadece delete ile çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1687, .topicId = 66,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Aynı kapsamda art arda tanımlanan yerel nesneler, tanımlanma sırasının _____ yok edilir (Türkçe kelime).",
        .acceptedAnswers = {"tersine"},
        .explanation = "Yerel nesneler tanımlanma sırasının tersine yok edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1688, .topicId = 66,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Kaynak {\npublic:\n    _____\n};\nKaynak k;\nk kapsamdan çıkarken \"Temizlendi\" yazdıran destructor'ı tanımlayan satırı yazın.",
        .acceptedAnswers = {"~Kaynak() { std::cout << \"Temizlendi\"; }"},
        .explanation = "Destructor, kapsamdan çıkışta \"Temizlendi\" yazdırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1689, .topicId = 66,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class A {\npublic:\n    ~A() { std::cout << \"Yok edildi\"; }\n};\nint main() {\n    _____\n    return 0;\n}\nA türünde bir nesne oluşturan satırı yazın (destructor'ın main sonunda otomatik çalışması için).",
        .acceptedAnswers = {"A a;"},
        .explanation = "a, main sonlanırken kapsamdan çıkıp destructor'ı tetikler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1690, .topicId = 66,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Kaynak {\npublic:\n    Kaynak() { std::cout << \"Ac \"; }\n    ~Kaynak() { std::cout << \"Kapa \"; }\n};\nint main() {\n    Kaynak k;\n    std::cout << \"Orta \";\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Ac Orta Kapa "},
        .explanation = "Constructor önce, sonra \"Orta \", sonra main sonunda destructor çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1691, .topicId = 66,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class A {\npublic:\n    ~A() { std::cout << \"~A \"; }\n};\nclass B {\npublic:\n    ~B() { std::cout << \"~B \"; }\n};\nint main() {\n    A a;\n    B b;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"~B ~A "},
        .explanation = "b sonra tanımlandığından önce yok edilir (tersine sıra).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1692, .topicId = 66,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Kaynak {\npublic:\n    void ~Kaynak() { std::cout << \"Bitti\"; }\n};\n\nBu kod derlenmez çünkü destructor'ların (constructor'lar gibi) dönüş türü yoktur; void yazmak geçersizdir. Hatalı satırı, dönüş türü olmadan düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"~Kaynak() { std::cout << \"Bitti\"; }"},
        .explanation = "Destructor'ın dönüş türü (void dahil) olmamalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1693, .topicId = 66,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Kaynak {\npublic:\n    ~Kaynak(int kod) { std::cout << kod; }\n};\n\nBu kod derlenmez çünkü bir destructor parametre alamaz. Hatalı satırı, parametresiz düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"~Kaynak() {"},
        .explanation = "Destructor hiçbir parametre alamaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1694, .topicId = 66,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Kaynak {\npublic:\n    ~Kaynak() { std::cout << \"Bitti\" }\n};\n\nProgramcı std::cout << \"Bitti\" satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"~Kaynak() { std::cout << \"Bitti\"; }"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1695, .topicId = 66,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir destructor tanımlayıp gözlemleyen geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"Kaynak k;\n    return 0;\n}", "class Kaynak {\npublic:\n    ~Kaynak() { std::cout << \"Bitti\"; }\n};", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class+destructor tanımı (2), main açılışı (3), nesne+kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1696, .topicId = 66,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Constructor'ında \"Acildi\" ve destructor'ında \"Kapandi\" yazdıran Kaynak adlı bir class tanımlayın; main() içinde bir nesne oluşturup her ikisinin de doğru sırayla çalıştığını gösterin.",
        .acceptedAnswers = {"~Kaynak", "cout"},
        .explanation = "Constructor önce, destructor kapsam sonunda çalışmalıdır.",
        .baseXp = 40,
    });

    // Topic 67: private ve public
    questions.push_back(Question{
        .id = 1697, .topicId = 67,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "private bir üyeye nereden erişilebilir?",
        .options = {"Sadece sınıfın kendi metotları içinden", "Her yerden", "Sadece main() içinden", "Sadece türetilmiş sınıflardan"},
        .acceptedAnswers = {"a"},
        .explanation = "private üyelere sadece sınıfın kendi metotları içinden erişilebilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1698, .topicId = 67,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "public bir üyeye nereden erişilebilir?",
        .options = {"Her yerden", "Sadece sınıfın kendi metotları içinden", "Hiçbir yerden", "Sadece türetilmiş sınıflardan"},
        .acceptedAnswers = {"a"},
        .explanation = "public üyelere her yerden erişilebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1699, .topicId = 67,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "class Hesap {\nprivate:\n    int bakiye;\n};\nHesap h;\nh.bakiye = 100;\nBu kod derlenir mi?",
        .options = {"Hayır, bakiye private olduğundan dışarıdan erişilemez", "Evet, her üyeye her zaman erişilebilir", "Evet ama sadece okumak için", "Hayır, Hesap sınıfı geçersizdir"},
        .acceptedAnswers = {"a"},
        .explanation = "private bir üyeye dışarıdan erişmek derleme hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1700, .topicId = 67,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class Hesap {\nprivate:\n    int bakiye;\npublic:\n    void ata(int d) { bakiye = d; }\n    int getir() { return bakiye; }\n};\nHesap h;\nh.ata(50);\nstd::cout << h.getir();\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"50", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "ata(50), bakiye'yi 50 yapar; getir() bu değeri döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1701, .topicId = 67,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir sınıfın kendi metodu içinden (örneğin ata()), o sınıfın private üyelerine erişilebilir mi?",
        .options = {"Evet, sınıfın kendi metotları private üyelere her zaman erişebilir", "Hayır, private üyelere hiçbir yerden erişilemez", "Sadece const metotlar erişebilir", "Sadece static metotlar erişebilir"},
        .acceptedAnswers = {"a"},
        .explanation = "Sınıfın kendi metotları private üyelerine her zaman erişebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1702, .topicId = 67,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "class A {\nprivate:\n    int x;\npublic:\n    void ayarla(int deger) { x = deger; }\n};\nBu kod (ayarla metodu içinde x'e erişim) derlenir mi?",
        .options = {"Evet, sınıfın kendi metodu private üyeye erişebilir", "Hayır, x'e hiçbir metot erişemez", "Hayır, ayarla de x gibi private olmalıydı", "Evet ama sadece const olarak"},
        .acceptedAnswers = {"a"},
        .explanation = "ayarla, A sınıfının kendi metodu olduğundan private x'e erişebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1703, .topicId = 67,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class Hesap {\nprivate:\n    int bakiye = 0;\npublic:\n    void yatir(int miktar) {\n        if (miktar > 0) {\n            bakiye += miktar;\n        }\n    }\n    int getirBakiye() { return bakiye; }\n};\nint main() {\n    Hesap h;\n    h.yatir(100);\n    h.yatir(-50);\n    std::cout << h.getirBakiye();\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"100", "50", "150", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "yatir(100) bakiye'yi 100 yapar; yatir(-50), miktar>0 kontrolünü geçemediği için hiçbir şey değiştirmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1704, .topicId = 67,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "class A {\nprivate:\n    int x;\npublic:\n    void kopyala(A& diger) {\n        x = diger.x;\n    }\n};\nBu kod (bir metodun BAŞKA bir A nesnesinin private x'ine erişmesi) derlenir mi?",
        .options = {"Evet, aynı sınıfın bir metodu, o sınıftan başka bir nesnenin private üyesine de erişebilir", "Hayır, sadece kendi nesnesinin private üyelerine erişebilir", "Hayır, bu bir derleme hatasıdır", "Evet ama sadece diger de const ise"},
        .acceptedAnswers = {"a"},
        .explanation = "C++'ta erişim denetimi nesne bazlı değil sınıf bazlıdır; aynı sınıfın metodu başka bir örneğin private üyesine de erişebilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1705, .topicId = 67,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "private bir üyeye sadece sınıfın kendi metotları içinden erişilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1706, .topicId = 67,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "public bir üyeye sadece sınıf içinden erişilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: public üyelere her yerden erişilebilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1707, .topicId = 67,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "private bir üyeye sınıf dışından (örneğin main() içinden) doğrudan erişmek derleme hatasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1708, .topicId = 67,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir sınıfın metotları kendi private üyelerine erişemez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: sınıfın kendi metotları private üyelere her zaman erişebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1709, .topicId = 67,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir sınıfın bir metodu, aynı sınıftan BAŞKA bir nesnenin private üyesine de erişebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: erişim denetimi sınıf bazlıdır, nesne bazlı değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1710, .topicId = 67,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Getter ve setter metotları genellikle public olarak tanımlanır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1711, .topicId = 67,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "private bir üyeye sadece sınıfın kendi _____ içinden erişilebilir (Türkçe kelime).",
        .acceptedAnswers = {"metotları"},
        .explanation = "Sadece sınıfın kendi metotları içinden erişilebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1712, .topicId = 67,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "class Hesap {\nprivate:\n    int bakiye;\npublic:\n    void ata(int d) { bakiye = d; }\n    int getir() { return bakiye; }\n};\nHesap h;\nh.ata(30);\nstd::cout << h.getir();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"30"},
        .explanation = "ata(30), bakiye'yi 30 yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1713, .topicId = 67,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "public bir üyeye erişim kısıtlaması _____ (Türkçe kelime, 'yoktur' anlamında).",
        .acceptedAnswers = {"yoktur"},
        .explanation = "public üyelere her yerden erişilebilir, kısıtlama yoktur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1714, .topicId = 67,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "h.bakiye = 100; şeklinde private bir üyeye sınıf dışından erişmek _____ verir (Türkçe kelime).",
        .acceptedAnswers = {"hata", "derleme hatası"},
        .explanation = "Bu bir derleme hatasıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1715, .topicId = 67,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "private bir üyeye kontrollü dışarıdan erişim sağlamak için genellikle _____ ve setter metotları yazılır (İngilizce kelime).",
        .acceptedAnswers = {"getter"},
        .explanation = "getter ve setter, kontrollü erişim sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1716, .topicId = 67,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir sınıfın bir metodu, aynı sınıftan başka bir nesnenin private üyesine erişebilir çünkü erişim denetimi nesne bazlı değil, _____ bazlıdır (Türkçe kelime).",
        .acceptedAnswers = {"sınıf"},
        .explanation = "Erişim denetimi sınıf bazlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1717, .topicId = 67,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Hesap {\nprivate:\n    int bakiye;\npublic:\n    _____\n};\nHesap h;\nh.ata(75);\nbakiye'yi ayarlayan bir ata(int) metodu tanımlayan satırı yazın.",
        .acceptedAnswers = {"void ata(int d) { bakiye = d; }"},
        .explanation = "ata metodu, private bakiye'yi ayarlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1718, .topicId = 67,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "class Hesap {\nprivate:\n    int bakiye;\npublic:\n    void ata(int d) { bakiye = d; }\n};\nint main() {\n    Hesap h;\n    _____\n    return 0;\n}\nh nesnesinin bakiye'sini 200 yapan (public metot üzerinden) satırı yazın.",
        .acceptedAnswers = {"h.ata(200);"},
        .explanation = "ata metodu üzerinden bakiye 200 yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1719, .topicId = 67,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "class Hesap {\nprivate:\n    int bakiye = 0;\npublic:\n    void yatir(int m) { bakiye += m; }\n    int getir() { return bakiye; }\n};\nint main() {\n    Hesap h;\n    h.yatir(30);\n    h.yatir(20);\n    std::cout << h.getir();\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"50"},
        .explanation = "30 + 20 = 50.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1720, .topicId = 67,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "class Ornek {\nprivate:\n    int x;\npublic:\n    void kopyala(Ornek& diger) { x = diger.x; }\n    void ata(int d) { x = d; }\n    int getir() { return x; }\n};\nint main() {\n    Ornek a, b;\n    a.ata(10);\n    b.kopyala(a);\n    std::cout << b.getir();\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "kopyala metodu, aynı sınıftan başka bir nesnenin (a'nın) private x'ine erişip b'ye kopyalar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1721, .topicId = 67,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Hesap {\nprivate:\n    int bakiye;\n};\nint main() {\n    Hesap h;\n    h.bakiye = 500;\n    return 0;\n}\n\nBu kod derlenmez çünkü bakiye private olduğundan sınıf dışından (main() içinden) doğrudan erişilemez. bakiye'yi ayarlayan, Hesap sınıfına eklenmesi gereken public metodu yazın.",
        .acceptedAnswers = {"void bakiyeAta(int d) { bakiye = d; }"},
        .explanation = "private bir üyeye dışarıdan erişmek için public bir metot (setter) gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1722, .topicId = 67,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nclass Ornek {\nprivate:\n    int x;\npublic:\n    void kopyala(Ornek diger) { x = diger.y; }\n};\n\nBu kod derlenmez çünkü Ornek sınıfının hiç y üyesi yok (sadece x var); diger.y bilinmeyen bir üyeye erişmeye çalışıyor. Hatalı satırı, diger.x kullanarak düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void kopyala(Ornek diger) { x = diger.x; }"},
        .explanation = "Ornek sınıfında sadece x üyesi tanımlı olduğundan diger.x kullanılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1723, .topicId = 67,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nclass Hesap {\nprivate:\n    int bakiye;\npublic:\n    void ata(int d) { bakiye = d }\n};\n\nProgramcı bakiye = d; satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"void ata(int d) { bakiye = d; }"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1724, .topicId = 67,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, private bir üyeye public bir metotla erişen geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"h.ata(80);\n    std::cout << h.getir();\n    return 0;\n}", "class Hesap {\nprivate:\n    int bakiye;\npublic:\n    void ata(int d) { bakiye = d; }\n    int getir() { return bakiye; }\n};", "int main() {\n    Hesap h;"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "class tanımı (2), main+nesne (3), kullanım ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1725, .topicId = 67,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "bakiye adlı private bir int üyesi olan Hesap adlı bir class tanımlayın; public bir ata() ve bir getir() metodu ekleyip main() içinde kullanın.",
        .acceptedAnswers = {"private", "public", "cout"},
        .explanation = "private üyeye public metotlarla erişilmelidir.",
        .baseXp = 40,
    });
}

#include "QuestionContent.h"

#include "Question.h"

void appendSection6Questions(std::vector<Question>& questions) {
    // Topic 51: Lambda fonksiyonları
    questions.push_back(Question{
        .id = 1233, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Lambda ifadesinin genel yapısı nedir?",
        .options = {"[yakalama](parametreler) { govde }", "def parametreler: govde", "function(parametreler) { govde }", "lambda parametreler { govde }"},
        .acceptedAnswers = {"a"},
        .explanation = "Lambda ifadeleri [yakalama](parametreler) { govde } biçiminde yazılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1234, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "auto f = [](int a, int b) { return a + b; };\nf(3, 4) çağrısı ne döndürür?",
        .options = {"7", "34", "\"34\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "3 + 4 = 7.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1235, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "[] (boş yakalama listesi) olan bir lambda, dışındaki değişkenlere erişebilir mi?",
        .options = {"Hayır, hiçbir dış değişkene erişemez", "Evet, tüm dış değişkenlere otomatik erişir", "Sadece global değişkenlere erişir", "Sadece const değişkenlere erişir"},
        .acceptedAnswers = {"a"},
        .explanation = "Boş yakalama listesi, lambda'nın dışarıdaki hiçbir değişkene erişemeyeceği anlamına gelir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1236, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nauto f = [x]() { return x; };\nx = 100;\nstd::cout << f();\nEkrana ne yazdırılır?",
        .options = {"5", "100", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "[x] değer ile yakalar; x'in lambda oluşturulduğu andaki değeri (5) dondurulur, sonraki değişiklik f()'i etkilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1237, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nauto f = [&x]() { return x; };\nx = 100;\nstd::cout << f();\nEkrana ne yazdırılır?",
        .options = {"100", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "[&x] referans ile yakalar; f() her zaman x'in güncel değerini görür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1238, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nauto f = [x]() { x = 100; return x; };\nBu kod derlenir mi?",
        .options = {"Hayır, x lambda içinde varsayılan olarak sabittir (const), mutable olmadan değiştirilemez", "Evet, sorunsuz derlenir", "Evet ama x her zaman 0 olur", "Hayır, çünkü [x] geçersiz bir yakalama şeklidir"},
        .acceptedAnswers = {"a"},
        .explanation = "Değer ile yakalanan bir değişken, lambda gövdesi içinde varsayılan olarak değiştirilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1239, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nauto f = [x]() mutable { x = 100; return x; };\nstd::cout << f() << x;\nEkrana ne yazdırılır?",
        .options = {"\"1005\"", "\"100100\"", "\"55\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "mutable, sadece lambda'nın kendi iç kopyasını değiştirmeye izin verir (f()=100); dışarıdaki x hiç etkilenmez (5 kalır).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1240, .topicId = 51,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1, b = 2;\nauto f = [a, &b]() { return a + b; };\na = 10;\nb = 20;\nstd::cout << f();\nEkrana ne yazdırılır?",
        .options = {"21", "30", "3", "12"},
        .acceptedAnswers = {"a"},
        .explanation = "a değer ile yakalanmıştır (donmuş değeri 1); b referans ile yakalanmıştır (güncel değeri 20). 1 + 20 = 21.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1241, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Lambda ifadeleri, isimsiz (anonim) fonksiyonlar tanımlamanın bir yoludur.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: lambda'lar isimsiz fonksiyonlardır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1242, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "[] (boş yakalama listesi) olan bir lambda, dışarıdaki herhangi bir değişkene otomatik olarak erişebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: boş yakalama listesi hiçbir dış değişkene erişim vermez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1243, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "[x] ile değer olarak yakalanan bir değişken, lambda içinde varsayılan olarak değiştirilemez (const).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: mutable eklenmeden değiştirilemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1244, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "[&x] ile referans olarak yakalayan bir lambda, dışarıdaki x değişkenini gerçekten değiştirebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: referans ile yakalama, orijinal değişkene doğrudan erişim sağlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1245, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Değer ile yakalanan (örneğin [x]) bir değişken, lambda oluşturulduktan SONRA dışarıda değiştirilirse, lambda içindeki kopyası da otomatik olarak güncellenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: değer ile yakalama, lambda oluşturulduğu andaki değeri dondurur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1246, .topicId = 51,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "mutable olarak işaretlenmiş bir lambda, değer ile yakalanan bir değişkeni kendi iç kopyasında değiştirebilir, ama bu değişiklik dışarıdaki orijinal değişkeni etkilemez.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: mutable sadece lambda'nın kendi kopyasını etkiler, orijinali değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1247, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir lambda ifadesinde köşeli parantez [] içindeki listeye _____ listesi denir (Türkçe kelime).",
        .acceptedAnswers = {"yakalama"},
        .explanation = "Köşeli parantez içindeki listeye yakalama (capture) listesi denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1248, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "auto f = [](int a) { return a * 2; };\nstd::cout << f(5);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"10"},
        .explanation = "5 * 2 = 10.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1249, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 3;\nauto f = [x]() { return x * x; };\nstd::cout << f();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"9"},
        .explanation = "3 * 3 = 9.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1250, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 3;\nauto f = [&x]() { return x * x; };\nx = 5;\nstd::cout << f();\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"25"},
        .explanation = "Referans ile yakalama, güncel değeri (5) görür: 5*5=25.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1251, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Değer ile yakalanan bir değişkeni lambda gövdesi içinde değiştirebilmek için lambda'nın _____ olarak işaretlenmesi gerekir (İngilizce anahtar kelime).",
        .acceptedAnswers = {"mutable"},
        .explanation = "mutable anahtar kelimesi, değer ile yakalanan kopyaların değiştirilmesine izin verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1252, .topicId = 51,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 1;\nauto f = [x]() { return x; };\nx = 99;\nstd::cout << f();\nEkran çıktısı _____ olur (x, lambda oluşturulduğu andaki değeriyle donduğu için).",
        .acceptedAnswers = {"1"},
        .explanation = "Değer ile yakalama, x'in lambda oluşturulduğu andaki değerini (1) dondurur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1253, .topicId = 51,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int carpan = 3;\n_____\nstd::cout << carp(4);\nBir sayıyı carpan (referans ile yakalanmış) ile çarpan carp adlı bir lambda tanımlayan satırı (auto ile) tamamlayın.",
        .acceptedAnswers = {"auto carp = [&carpan](int x) { return x * carpan; };"},
        .explanation = "Lambda, carpan'ı referans ile yakalayıp parametreyle çarpar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1254, .topicId = 51,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int taban = 10;\nauto ekle = [taban](int x) {\n    _____\n}\nstd::cout << ekle(5);\nekle lambda'sının gövdesini (x ile taban'ın toplamını döndüren satırı) tamamlayın.",
        .acceptedAnswers = {"return x + taban;"},
        .explanation = "Lambda, x ile taban'ın (değer ile yakalanmış) toplamını döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1255, .topicId = 51,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "auto carp = [](int a, int b) {\n    return a * b;\n};\nint main() {\n    std::cout << carp(3, 4);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "3 * 4 = 12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1256, .topicId = 51,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int x = 2;\nauto f = [x]() mutable {\n    x = x * 10;\n    return x;\n};\nint main() {\n    std::cout << f() << x;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"202"},
        .explanation = "f() lambda'nın kendi kopyasını değiştirip 20 döndürür; dışarıdaki x hiç etkilenmez (2 kalır): '202'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1257, .topicId = 51,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint x = 5;\nauto f = [x]() {\n    x = 10;\n    return x;\n};\n\nBu kod derlenmez çünkü [x] ile değer olarak yakalanan x, lambda gövdesi içinde varsayılan olarak sabittir (const) ve mutable olmadan değiştirilemez. Hatalı lambda başlığını, mutable eklenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"auto f = [x]() mutable {"},
        .explanation = "mutable eklenmeden, değer ile yakalanan bir değişken değiştirilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1258, .topicId = 51,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nint sayi = 5;\nauto f = [sayi]() {\n    return sayi;\n};\nsayi = 100;\nstd::cout << f();\n\nProgramcı ekrana 100 yazdırılmasını bekliyor ama [sayi] değer ile yakalama yaptığından f() her zaman lambda oluşturulduğu andaki değeri (5) döndürür. Lambda tanımını, sayi'nin güncel değerini görecek şekilde (referans ile yakalayarak) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"auto f = [&sayi]() {"},
        .explanation = "Referans ile yakalama, f()'in her zaman sayi'nin güncel değerini görmesini sağlar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1259, .topicId = 51,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint carpan = 2;\nauto carp = [carpan](int x) {\n    carpan = carpan + 1;\n    return x * carpan;\n};\n\nBu kod derlenmez çünkü [carpan] değer ile yakalandığından lambda içinde değiştirilemez. Lambda başlığını, mutable eklenmiş haliyle düzeltilmiş olarak yazın.",
        .acceptedAnswers = {"auto carp = [carpan](int x) mutable {"},
        .explanation = "mutable, değer ile yakalanan carpan'ın lambda'nın kendi kopyasında değiştirilmesine izin verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1260, .topicId = 51,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir lambda tanımlayıp çağıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << topla(3, 4);\n    return 0;\n}", "auto topla = [](int a, int b) {\n    return a + b;\n};", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), lambda tanımı (2), çağrı ve kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1261, .topicId = 51,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "İki sayıyı çarpan (parametre olarak alan) bir lambda tanımlayıp, sonucunu bir değişkene atayıp ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"auto", "=", "[", "]", "cout"},
        .explanation = "Lambda parametreleriyle çarpım yapmalı, sonuç bir değişkene atanıp yazdırılmalıdır.",
        .baseXp = 40,
    });

    // Topic 52: Pointer tanımlama
    questions.push_back(Question{
        .id = 1262, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir pointer değişkeni nasıl tanımlanır?",
        .options = {"tür* isim;", "tür isim*;", "pointer isim;", "&tür isim;"},
        .acceptedAnswers = {"a"},
        .explanation = "Pointer tanımı tür* isim; şeklinde yapılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1263, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int* p; ifadesinde p neyi tutar?",
        .options = {"Bir int değişkeninin bellek adresini", "Doğrudan bir int değerini", "Bir string'i", "Bir fonksiyon adını"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir pointer, gösterdiği değişkenin bellek adresini tutar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1264, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nBu ifadede p'nin türü nedir?",
        .options = {"int*", "int", "int&", "void*"},
        .acceptedAnswers = {"a"},
        .explanation = "p, int* türünde bir pointerdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1265, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p; (ilklendirmeden) tanımlandığında p'nin değeri nedir?",
        .options = {"Belirsiz (garbage), rastgele bir adres", "Otomatik olarak nullptr", "Her zaman 0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "İlklendirilmemiş bir pointer, belirsiz bir değer taşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1266, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p, q; ifadesinde q'nun türü nedir?",
        .options = {"int (pointer değil)", "int*", "int**", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "* işareti türe değil değişken adına bağlanır; sadece p pointer olur, q sıradan bir int'tir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1267, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p, *q; ifadesinde kaç tane pointer tanımlanmıştır?",
        .options = {"2 (p ve q ikisi de pointer)", "1 (sadece p)", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Her değişkenin önüne * konarak iki pointer da doğru şekilde tanımlanmıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1268, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p;\nstd::cout << *p;\nBu kod derlenir mi, çalışırsa ne olur?",
        .options = {"Derlenir ama p ilklendirilmediği için *p'yi okumak tanımsız davranıştır (genellikle çöker)", "Derlenir ve her zaman 0 yazdırır", "Derlenmez (derleme hatası)", "Derlenir ve her zaman rastgele ama güvenli bir sayı yazdırır"},
        .acceptedAnswers = {"a"},
        .explanation = "İlklendirilmemiş bir pointerı dereference etmek tanımsız davranıştır ve genellikle çöker.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1269, .topicId = 52,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1, b = 2;\nint* p = &a;\np = &b;\nstd::cout << *p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"2", "1", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "p, b'yi gösterecek şekilde yeniden atanmıştır (reassign); *p artık b'nin değerini (2) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1270, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir pointer, başka bir değişkenin bellek adresini tutar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: pointer, bir adresi tutan değişkendir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1271, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "int* p; ifadesi, p'yi otomatik olarak nullptr ile ilklendirir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: açıkça ilklendirilmezse p belirsiz bir değer taşır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1272, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int* p, q; ifadesinde hem p hem de q pointer olur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: sadece p pointer olur, q sıradan bir int'tir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1273, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir pointer, programın çalışması sırasında farklı bir değişkeni gösterecek şekilde yeniden atanabilir (reassign edilebilir).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: pointer'lar, referanslardan farklı olarak yeniden atanabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1274, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İlklendirilmemiş bir pointer'ı dereference etmek (*p ile okumak) tanımsız davranıştır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: bu, tanımsız davranışın klasik bir örneğidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1275, .topicId = 52,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int* p, *q; ifadesinde p ve q'nun ikisi de pointer olarak tanımlanır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: her ikisinin önünde de * olduğundan ikisi de pointer'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1276, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "int _____ p; ifadesi, p'yi bir int pointer'ı olarak tanımlar (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "* sembolü, p'nin bir pointer olduğunu belirtir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1277, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 7;\nint* p = &x;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "*p, p'nin gösterdiği x'in değerini (7) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1278, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int* p, q; ifadesinde q'nun türü _____ olur (bir kelime, İngilizce).",
        .acceptedAnswers = {"int"},
        .explanation = "q, pointer değil sıradan bir int olarak tanımlanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1279, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 1, b = 2;\nint* p = &a;\np = &b;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "p yeniden atanarak b'yi gösterir; *p artık b'nin değerini (2) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1280, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "İki pointer'ı tek satırda tanımlamak için int* p, _____q; yazılmalıdır (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "Her değişkenin önüne * konarak ikisi de pointer olarak tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1281, .topicId = 52,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p;\nBu satırdan sonra, p ilklendirilmeden dereference edilirse (*p okunursa) bu _____ davranıştır (İngilizce iki kelime, örn. 'undefined behavior').",
        .acceptedAnswers = {"undefined behavior"},
        .explanation = "İlklendirilmemiş bir pointer'ı dereference etmek undefined behavior'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1282, .topicId = 52,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int x = 9;\n_____\nstd::cout << *p;\nx'in adresini tutan p adlı bir pointer tanımlayan satırı tamamlayın.",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, x'in adresiyle ilklendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1283, .topicId = 52,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 3, b = 4;\nint* p = &a;\n_____\nstd::cout << *p;\np'yi b'yi gösterecek şekilde yeniden atayan satırı tamamlayın.",
        .acceptedAnswers = {"p = &b;"},
        .explanation = "p, b'nin adresine yeniden atanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1284, .topicId = 52,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int x = 8;\nint* p = &x;\n*p = 20;\nstd::cout << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"20"},
        .explanation = "*p = 20 ifadesi, p'nin gösterdiği x'i 20 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1285, .topicId = 52,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5, b = 6;\nint* p = &a;\nint* q = &b;\np = q;\n*p = 100;\nstd::cout << a << \" \" << b;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"5 100"},
        .explanation = "p = q ile p artık b'yi gösterir; *p = 100, b'yi 100 yapar. a hiç değişmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1286, .topicId = 52,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p, q;\nq = 5;\nstd::cout << q;\n\nBu kod, programcının hem p hem de q'yu pointer sanmasından kaynaklanan bir kavram yanılgısı içeriyor: q aslında sıradan bir int'tir (derleme hatası vermez, ama q bir pointer DEĞİLDİR). İki pointer birden tanımlamak isteniyorsa satırı nasıl yazmak gerekirdi? Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"int* p, *q;"},
        .explanation = "İki pointer tanımlamak için her değişkenin önüne * konmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1287, .topicId = 52,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p;\nstd::cout << *p;\n\nBu kod derlenir ama p hiçbir adrese atanmadan (ilklendirilmeden) dereference edildiği için tanımsız davranışa yol açar. p'yi geçerli bir x değişkenine bağlayan, hatalı ilk satırı düzeltilmiş haliyle yazın (x'in zaten tanımlı bir int değişkeni olduğunu varsayın).",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, geçerli bir x değişkeninin adresiyle ilklendirilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1288, .topicId = 52,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint sayi = 10;\nint *p, *r;\np = &sayi\nstd::cout << *p;\n\nProgramcı p = &sayi; satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"p = &sayi;"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1289, .topicId = 52,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir pointer tanımlayıp kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* p = &x;", "std::cout << *p;\n    return 0;\n}", "int main() {\n    int x = 42;"},
        .acceptedAnswers = {"3 1 2"},
        .explanation = "main açılışı ve x tanımı (3), pointer tanımı (1), yazdırma ve kapanış (2): sıra 3 1 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1290, .topicId = 52,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int değişkeni tanımlayıp, onun adresini tutan bir pointer oluşturun; pointer üzerinden (dereference ederek) değişkenin değerini değiştirip ekrana yazdırın.",
        .acceptedAnswers = {"int*", "&", "*", "cout"},
        .explanation = "Pointer, değişkenin adresiyle ilklendirilmeli ve dereference ile değer değiştirilmelidir.",
        .baseXp = 40,
    });

    // Topic 53: & adres operatörü
    questions.push_back(Question{
        .id = 1291, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "& operatörünün bir değişkenin önünde kullanılması ne anlama gelir?",
        .options = {"O değişkenin bellek adresini almak", "O değişkeni referansa çevirmek", "O değişkeni silmek", "O değişkenin değerini iki katına çıkarmak"},
        .acceptedAnswers = {"a"},
        .explanation = "& operatörü, bir değişkenin bellek adresini verir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1292, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nBu ifadede &x ne üretir?",
        .options = {"x'in bellek adresi", "x'in değeri (5)", "x'in türü", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "&x, x'in bellek adresini veren bir pointer değeri üretir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1293, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nstd::cout << (p == &x);\nEkrana ne yazdırılır?",
        .options = {"1", "0", "5", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p, &x ile ilklendirildiğinden p == &x her zaman true (1) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1294, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "& sembolü hangi iki bağlamda farklı anlamlara gelir?",
        .options = {"Bir ifadede adres operatörü, bir tanımda referans bildirimi", "Bir ifadede toplama, bir tanımda çıkarma", "Sadece pointer tanımlarında kullanılır", "& sembolünün tek bir anlamı vardır"},
        .acceptedAnswers = {"a"},
        .explanation = "& sembolü ifadede adres operatörü, tanımda ise referans bildirimi anlamına gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1295, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 3, y = 3;\nstd::cout << (&x == &y);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"0", "1", "3", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "x ve y aynı değere sahip olsalar da farklı değişkenlerdir, dolayısıyla farklı adreslere sahiptirler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1296, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nint& r = x;\nstd::cout << (&r == &x);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"1", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir referans, bağlı olduğu değişkenle tamamen aynı adresi paylaşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1297, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1;\nint* p = &a;\nint** pp = &p;\n**pp ifadesi neyi verir?",
        .options = {"a'nın değerini (1)", "p'nin adresini", "a'nın adresini", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "*pp, p'yi verir; *p de a'nın değerini (1) verir, dolayısıyla **pp = 1.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1298, .topicId = 53,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int x = 5;\nint* p1 = &x;\nint* p2 = &x;\nstd::cout << (p1 == p2);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"1", "0", "5", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "p1 ve p2, ikisi de x'in aynı adresini tuttuğundan p1 == p2 true (1) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1299, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "& operatörü, bir değişkenin bellek adresini verir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: & operatörü adres operatörüdür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1300, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "& sembolü her zaman aynı anlama gelir, bağlama göre değişmez.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: ifadede adres operatörü, tanımda referans bildirimi anlamına gelir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1301, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "İki farklı değişken, aynı değere sahip olsa bile genellikle farklı bellek adreslerine sahiptir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: her değişken kendi belleğinde ayrı bir yer kaplar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1302, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir referansın adresi (&r), bağlı olduğu değişkenin adresiyle (&x) aynıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: referans, bağlı olduğu değişkenle aynı adresi paylaşır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1303, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "&x ifadesinin sonucu, bir int* türünde bir pointer değeridir (x bir int ise).",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: &x, int* türünde bir adres değeri üretir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1304, .topicId = 53,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir değişkenin adresi, program her çalıştırıldığında her zaman aynı sayısal değere sahiptir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: adresler çalıştırmadan çalıştırmaya farklı olabilir; bu yüzden adres değerleri test edilmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1305, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir x değişkeninin adresini almak için _____x yazılır (bir sembol).",
        .acceptedAnswers = {"&"},
        .explanation = "& operatörü, adres almak için kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1306, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nstd::cout << (p == &x);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "p, &x ile ilklendirildiğinden karşılaştırma true (1) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1307, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 3, y = 3;\nstd::cout << (&x == &y);\nEkran çıktısı _____ olur (aynı değere sahip olsalar da farklı değişkenler oldukları için).",
        .acceptedAnswers = {"0"},
        .explanation = "Farklı değişkenler farklı adreslere sahiptir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1308, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nint& r = x;\nstd::cout << (&r == &x);\nEkran çıktısı _____ olur (bir referans, bağlı olduğu değişkenle aynı adresi paylaştığı için).",
        .acceptedAnswers = {"1"},
        .explanation = "Referans ve orijinal değişken aynı adresi paylaşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1309, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 1;\nint* p = &a;\nint** pp = &p;\nstd::cout << **pp;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "**pp, p üzerinden a'nın değerine (1) ulaşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1310, .topicId = 53,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "& sembolü bir ifadede adres operatörüyken, bir değişken tanımında (int& r = x;) _____ bildirimi anlamına gelir (Türkçe kelime).",
        .acceptedAnswers = {"referans"},
        .explanation = "Tanımda & sembolü referans bildirimi anlamına gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1311, .topicId = 53,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 15;\n_____\nstd::cout << *adres;\nsayi'nin adresini tutan adres adlı bir pointer tanımlayan satırı yazın.",
        .acceptedAnswers = {"int* adres = &sayi;"},
        .explanation = "adres, sayi'nin bellek adresiyle ilklendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1312, .topicId = 53,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 1;\nint* p = &a;\n_____\nstd::cout << **pp;\np'nin adresini tutan pp adlı bir int** pointer tanımlayan satırı yazın.",
        .acceptedAnswers = {"int** pp = &p;"},
        .explanation = "pp, p'nin adresini tutan bir pointer'a pointer'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1313, .topicId = 53,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int x = 4;\nint* p = &x;\nstd::cout << (*p == x);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "*p, x'in kendisine eşit olduğundan karşılaştırma true (1) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1314, .topicId = 53,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 2, b = 2;\nint* p = &a;\nint* q = &b;\nstd::cout << (*p == *q) << (p == q);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "*p == *q true (1) çünkü değerler eşit (2==2); p == q false (0) çünkü farklı adresler.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1315, .topicId = 53,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint x = 5;\nint* p = x;\nstd::cout << *p;\n\nBu kod derlenmez çünkü p bir int* iken x bir int'tir (adres değil, değer atanmaya çalışılıyor); türler uyuşmuyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p'ye x'in kendisi değil, adresi (&x) atanmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1316, .topicId = 53,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint x = 5;\nint y = &x;\nstd::cout << y;\n\nBu kod derlenmez çünkü y bir int olarak tanımlanmış ama kendisine bir adres (&x, bir int* değeri) atanmaya çalışılıyor; türler uyuşmuyor. Hatalı satırı, y'yi doğru türde (bir pointer olarak) tanımlayacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int* y = &x;"},
        .explanation = "Bir adres değeri ancak bir pointer değişkende tutulabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1317, .topicId = 53,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint x = 5;\nint* p;\np = x;\nstd::cout << *p;\n\nProgramcı p'ye x'in adresini değil, doğrudan değerini atamış; türler uyuşmuyor. Düzeltilmiş atama satırını yazın.",
        .acceptedAnswers = {"p = &x;"},
        .explanation = "p'ye x'in adresi (&x) atanmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1318, .topicId = 53,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, & operatörüyle bir pointer ilklendiren geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* p = &x;\n    std::cout << *p;\n    return 0;\n}", "int x = 7;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), x tanımı (2), pointer + yazdırma + kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1319, .topicId = 53,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int değişken tanımlayın, & operatörüyle adresini bir pointer'a atayın, ardından bu adresin gerçekten o değişkenin adresi olduğunu (== ile pointer'ı &değişken ile karşılaştırarak) ekrana yazdırın.",
        .acceptedAnswers = {"&", "int*", "cout"},
        .explanation = "Pointer, & operatörüyle ilklendirilip == ile karşılaştırılmalıdır.",
        .baseXp = 40,
    });

    // Topic 54: * dereference operatörü
    questions.push_back(Question{
        .id = 1320, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "* operatörünün bir pointer'ın önünde kullanılması ne anlama gelir?",
        .options = {"Pointer'ın gösterdiği adresteki değere erişmek (dereference)", "Pointer'ı silmek", "Pointer'ın adresini almak", "İki pointer'ı çarpmak"},
        .acceptedAnswers = {"a"},
        .explanation = "* operatörü, pointer'ın gösterdiği değere erişmeyi sağlar (dereference).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1321, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nstd::cout << *p;\nEkrana ne yazdırılır?",
        .options = {"5", "x'in adresi", "Derleme hatası", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "*p, p'nin gösterdiği x'in değerini (5) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1322, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\n*p = 20;\nstd::cout << x;\nEkrana ne yazdırılır?",
        .options = {"20", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "*p üzerinden yapılan atama, doğrudan x'i değiştirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1323, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "*(&x) ifadesi neye eşittir (x geçerli bir değişkense)?",
        .options = {"x'in kendisine", "x'in adresine", "0'a", "Her zaman derleme hatasına"},
        .acceptedAnswers = {"a"},
        .explanation = "& ve * birbirinin tersi işlemlerdir: *(&x) her zaman x'e eşittir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1324, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nstd::cout << *p;\nBu satır çalıştırılırsa ne olur?",
        .options = {"Tanımsız davranış (genellikle çöker)", "0 yazdırır", "Boş bir string yazdırır", "Sessizce hiçbir şey yapmaz"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr'ı dereference etmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1325, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int a = 1, b = 2;\nint* p = &a;\n*p = *p + b;\nstd::cout << a;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"3", "1", "2", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "*p, a'nın kendisidir; *p = *p + b ifadesi a'yı 1+2=3 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1326, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 5;\nint* p = &a;\nint* q = p;\n*q = 99;\nstd::cout << a << \" \" << *p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"\"99 99\"", "\"5 5\"", "\"99 5\"", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "q = p, p'nin tuttuğu adresi (a'nın adresini) kopyalar; *q = 99, a'yı 99 yapar, *p de artık 99'dur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1327, .topicId = 54,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int x = 10;\nint* p = &x;\nint* q = &x;\n*p = *p + *q;\nstd::cout << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"20", "10", "30", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p ve q ikisi de x'i gösterir; *p+*q=10+10=20, *p=20 ataması x'i 20 yapar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1328, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "* operatörü, bir pointer'ın gösterdiği adresteki değere erişmeyi sağlar.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: bu işleme dereference denir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1329, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "nullptr olan bir pointer'ı dereference etmek (*p ile) güvenlidir ve her zaman 0 döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: nullptr'ı dereference etmek tanımsız davranıştır, güvenli değildir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1330, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "*(&x) ifadesi, geçerli bir x değişkeni için her zaman x'e eşittir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: & ve * birbirinin tersidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1331, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "*p = 10; ifadesi, p'nin gösterdiği adresteki değeri 10 yapar, p'nin kendisinin adresini değiştirmez.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: *p = 10, gösterilen değeri değiştirir; p'nin tuttuğu adres aynı kalır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1332, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki farklı pointer aynı değişkeni gösteriyorsa, birini dereference ederek yapılan değişiklik diğerinden de görülür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: ikisi de aynı belleği gösterdiğünden değişiklik ortaktır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1333, .topicId = 54,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir pointer tanımındaki * (int* p) ile bir ifadedeki * (*p) her zaman aynı işlemi (dereference) ifade eder.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: tanımda * pointer türünü belirtir, ifadede ise dereference işlemi yapar — aynı sembolün iki farklı anlamı vardır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1334, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir pointer'ın gösterdiği değere erişmek için pointer'ın önüne _____ konur (bir sembol).",
        .acceptedAnswers = {"*"},
        .explanation = "* sembolü dereference işlemini yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1335, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "*p, x'in değerini (5) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1336, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int x = 5;\nint* p = &x;\n*p = 30;\nstd::cout << x;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"30"},
        .explanation = "*p = 30, x'i 30 yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1337, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int a = 2;\nint* p = &a;\n*p = *p * 5;\nstd::cout << a;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"10"},
        .explanation = "*p, a'nın kendisidir; 2*5=10, a artık 10'dur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1338, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "nullptr olan bir pointer'ı dereference etmek _____ davranıştır (İngilizce iki kelime, örn. 'undefined behavior').",
        .acceptedAnswers = {"undefined behavior"},
        .explanation = "nullptr'ı dereference etmek undefined behavior'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1339, .topicId = 54,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 5;\nint* p = &x;\nint* q = p;\n*q = 40;\nstd::cout << x;\nEkran çıktısı _____ olur (q, p'nin adresini kopyaladığı, yani aynı x'i gösterdiği için).",
        .acceptedAnswers = {"40"},
        .explanation = "q, p'nin adresini kopyaladığından aynı x'i gösterir; *q = 40, x'i 40 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1340, .topicId = 54,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int x = 8;\nint* p = &x;\n_____\nstd::cout << x;\np üzerinden x'in değerini 50 yapan satırı yazın.",
        .acceptedAnswers = {"*p = 50;"},
        .explanation = "*p = 50, p'nin gösterdiği x'i 50 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1341, .topicId = 54,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 3;\nint b = 4;\nint* p = &a;\n_____\nstd::cout << a;\np üzerinden a'nın değerini b ile çarpan satırı yazın.",
        .acceptedAnswers = {"*p = *p * b;"},
        .explanation = "*p = *p * b, a'yı a*b yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1342, .topicId = 54,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int x = 6;\nint* p = &x;\n*p += 4;\nstd::cout << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "*p += 4, x'i 6+4=10 yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1343, .topicId = 54,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a = 1, b = 2, c = 3;\nint* p = &a;\np = &b;\n*p = c;\nstd::cout << a << \" \" << b << \" \" << c;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1 3 3"},
        .explanation = "p, b'yi gösterecek şekilde yeniden atanır; *p = c, b'yi c'nin değeri (3) yapar. a ve c değişmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1344, .topicId = 54,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p;\nstd::cout << *p;\n\nBu kod derlenir ama p hiçbir geçerli adrese atanmadan (ilklendirilmeden) dereference edildiği için tanımsız davranışa yol açar. p'yi geçerli bir x adlı int değişkenine bağlayan, hatalı ilk satırı düzeltilmiş haliyle yazın (x'in zaten tanımlı olduğunu varsayarak).",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, geçerli bir değişkenin adresiyle ilklendirilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1345, .topicId = 54,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p = nullptr;\nstd::cout << *p;\n\nBu kod, nullptr olan bir pointer'ı dereference ettiği için tanımsız davranışa (genellikle çökmeye) yol açar. p'yi dereference etmeden önce nullptr olup olmadığını kontrol eden bir if satırını (başlığını) yazın.",
        .acceptedAnswers = {"if (p != nullptr) {"},
        .explanation = "Dereference etmeden önce pointer'ın nullptr olup olmadığı kontrol edilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1346, .topicId = 54,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint* p = nullptr;\n*p = 5;\nstd::cout << *p;\n\nProgramcı nullptr olan p'yi doğrudan dereference edip değer atamaya çalışmış; bu tanımsız davranıştır. p'yi önce geçerli bir x değişkenine (zaten tanımlı olduğunu varsayarak) bağlayan düzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, dereference edilmeden önce geçerli bir adrese bağlanmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1347, .topicId = 54,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, * operatörüyle bir pointer'ın gösterdiği değeri değiştiren geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"*p = 99;\n    std::cout << x;\n    return 0;\n}", "int x = 1;\n    int* p = &x;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), x ve p tanımı (2), dereference + yazdırma + kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1348, .topicId = 54,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int değişken tanımlayın, adresini bir pointer'a atayın, ardından * operatörüyle (dereference ederek) değişkenin değerini değiştirip son değerini ekrana yazdırın.",
        .acceptedAnswers = {"*", "int*", "cout"},
        .explanation = "Pointer, dereference edilerek değişkenin değeri değiştirilmelidir.",
        .baseXp = 40,
    });
}

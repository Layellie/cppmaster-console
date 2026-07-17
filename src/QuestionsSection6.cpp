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
        .explanation = "Doğru: ikisi de aynı belleği gösterdiğinden değişiklik ortaktır.",
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

    // Topic 55: nullptr
    questions.push_back(Question{
        .id = 1349, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "nullptr neyi ifade eder?",
        .options = {"Hiçbir şeyi göstermeyen, tip-güvenli bir pointer değeri", "Sıfır değerli bir int", "Boş bir string", "Bir referans türü"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr, hiçbir şeyi göstermeyen tip-güvenli bir null pointer sabitidir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1350, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int* p = nullptr;\nif (p == nullptr) {\n    std::cout << \"bos\";\n}\nEkrana ne yazdırılır?",
        .options = {"\"bos\"", "\"\"", "Derleme hatası", "Rastgele değer"},
        .acceptedAnswers = {"a"},
        .explanation = "p, nullptr ile ilklendirildiğinden koşul true olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1351, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "nullptr, C++'ın hangi versiyonuyla birlikte geldi?",
        .options = {"C++11", "C++98", "C++20", "C++03"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr, C++11 standardıyla birlikte geldi.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1352, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nstd::cout << *p;\nBu satır çalıştırılırsa ne olur?",
        .options = {"Tanımsız davranış (genellikle çöker)", "0 yazdırır", "Boş string yazdırır", "nullptr yazdırır"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr'ı dereference etmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1353, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "nullptr yerine eski kodlarda hangi ifadeler kullanılırdı?",
        .options = {"NULL veya 0", "void veya empty", "undefined veya none", "blank veya zero"},
        .acceptedAnswers = {"a"},
        .explanation = "Eski C++ kodlarında NULL veya düz 0 kullanılırdı.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1354, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nif (p) {\n    std::cout << \"dolu\";\n} else {\n    std::cout << \"bos\";\n}\nEkrana ne yazdırılır?",
        .options = {"\"bos\"", "\"dolu\"", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "nullptr, boolean bağlamda false olarak değerlendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1355, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p = nullptr;\nint x = 5;\np = &x;\nif (p != nullptr) {\n    std::cout << *p;\n}\nEkrana ne yazdırılır?",
        .options = {"5", "Hiçbir şey", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p, x'in adresine yeniden atandığından artık nullptr değildir; *p, x'in değerini (5) verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1356, .topicId = 55,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p = nullptr;\nint* q = nullptr;\nstd::cout << (p == q);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"1", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "İki nullptr değeri her zaman birbirine eşittir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1357, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "nullptr, hiçbir şeyi göstermeyen bir pointer'ı ifade eder.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: nullptr, boş bir pointer değeridir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1358, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "nullptr'ı dereference etmek (*p ile, p nullptr iken) güvenlidir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: nullptr'ı dereference etmek tanımsız davranıştır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1359, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "nullptr, C++11 ile gelen tip-güvenli bir null pointer sabitidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1360, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir pointer, nullptr ile karşılaştırılarak (p == nullptr) güvenle kontrol edilebilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: bu, bir pointer'ın boş olup olmadığını kontrol etmenin standart yoludur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1361, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "if (p) koşulu, p nullptr olduğunda true (doğru) olarak değerlendirilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: nullptr, boolean bağlamda false olarak değerlendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1362, .topicId = 55,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "nullptr, eski C++ kodlarında kullanılan NULL veya 0'dan daha tip-güvenlidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: nullptr, tip-güvenli bir sabittir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1363, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Hiçbir şeyi göstermeyen bir pointer, C++11'den itibaren _____ ile ilklendirilir (bir kelime, İngilizce).",
        .acceptedAnswers = {"nullptr"},
        .explanation = "nullptr, boş bir pointer için kullanılan modern sabittir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1364, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int* p = nullptr;\nif (p == nullptr) {\n    std::cout << \"bos\";\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"bos"},
        .explanation = "p nullptr olduğundan koşul true olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1365, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int* p = nullptr;\nstd::cout << (p == nullptr);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "p nullptr olduğundan karşılaştırma true (1) verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1366, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nif (p) {\n    std::cout << \"dolu\";\n} else {\n    std::cout << \"bos\";\n}\nEkran çıktısı _____ olur (nullptr, boolean bağlamda false değerlendirildiği için).",
        .acceptedAnswers = {"bos"},
        .explanation = "nullptr, if koşulunda false olarak değerlendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1367, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nint x = 9;\np = &x;\nstd::cout << (p == nullptr);\nEkran çıktısı _____ olur (p artık x'i gösterdiği için).",
        .acceptedAnswers = {"0"},
        .explanation = "p artık nullptr olmadığından karşılaştırma false (0) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1368, .topicId = 55,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "nullptr'ı dereference etmeye çalışmak _____ davranıştır (İngilizce iki kelime).",
        .acceptedAnswers = {"undefined behavior"},
        .explanation = "nullptr'ı dereference etmek undefined behavior'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1369, .topicId = 55,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\n_____\nstd::cout << \"p artik gecerli.\";\np'yi geçerli bir x değişkenine (zaten tanımlı olduğunu varsayarak) bağlayan satırı yazın.",
        .acceptedAnswers = {"p = &x;"},
        .explanation = "p, x'in adresine yeniden atanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1370, .topicId = 55,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\n_____ {\n    std::cout << \"p bos.\";\n}\np'nin nullptr olup olmadığını kontrol eden if satırının başlığını yazın.",
        .acceptedAnswers = {"if (p == nullptr)"},
        .explanation = "if (p == nullptr) koşulu, p'nin boş olup olmadığını kontrol eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1371, .topicId = 55,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int* p = nullptr;\nstd::cout << (p == nullptr);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "p nullptr olduğundan karşılaştırma true (1) verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1372, .topicId = 55,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int x = 4;\nint* p = nullptr;\np = &x;\nstd::cout << (p == nullptr) << *p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"04"},
        .explanation = "p artık nullptr olmadığından ilk karşılaştırma 0, *p ise x'in değeri (4): '04'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1373, .topicId = 55,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p = nullptr;\nstd::cout << *p;\n\nBu kod, nullptr olan bir pointer'ı dereference ettiği için tanımsız davranışa (genellikle çökmeye) yol açar. Hatayı önlemek için p'yi dereference etmeden önce kontrol eden if satırının başlığını yazın.",
        .acceptedAnswers = {"if (p != nullptr) {"},
        .explanation = "Dereference etmeden önce pointer'ın nullptr olmadığı kontrol edilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1374, .topicId = 55,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p;\nif (p == nullptr) {\n    std::cout << \"bos\";\n}\n\nBu kod derlenir ama p, nullptr ile değil ilklendirilmeden bırakılmıştır; bu yüzden p == nullptr karşılaştırması güvenilir bir sonuç vermez (p belirsiz bir değer taşıdığından tesadüfen nullptr'a eşit olmayabilir). p'yi tanımlandığı anda nullptr ile ilklendiren düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"int* p = nullptr;"},
        .explanation = "Pointer'lar tanımlandığı anda nullptr ile ilklendirilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1375, .topicId = 55,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint* p = nullptr;\nint deger = *p;\nstd::cout << deger;\n\nProgramcı p'yi hiç geçerli bir adrese bağlamadan dereference etmiş; bu tanımsız davranıştır. p'yi önce geçerli bir x değişkenine (zaten tanımlı olduğunu varsayarak) bağlayan düzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"int* p = &x;"},
        .explanation = "p, dereference edilmeden önce geçerli bir adrese bağlanmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1376, .topicId = 55,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, nullptr kontrolü yapan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"if (p == nullptr) {\n        std::cout << \"bos\";\n    }\n    return 0;\n}", "int* p = nullptr;", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), p tanımı (2), if kontrolü ve kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1377, .topicId = 55,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir pointer'ı nullptr ile ilklendirin, ardından nullptr olup olmadığını if ile kontrol edip uygun bir mesaj yazdırın.",
        .acceptedAnswers = {"nullptr", "if", "cout"},
        .explanation = "Pointer nullptr ile ilklendirilmeli ve if ile kontrol edilmelidir.",
        .baseXp = 40,
    });

    // Topic 56: Pointer ile dizi dolaşma
    questions.push_back(Question{
        .id = 1378, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizi adı, kullanıldığı çoğu bağlamda neye dönüşür (decay olur)?",
        .options = {"İlk elemanının adresine", "Son elemanının adresine", "Elemanların toplamına", "Dizinin boyutuna"},
        .acceptedAnswers = {"a"},
        .explanation = "Bir dizi adı, ilk elemanının adresine dönüşür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1379, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int dizi[3] = {10, 20, 30};\nint* p = dizi;\nstd::cout << *p;\nEkrana ne yazdırılır?",
        .options = {"10", "20", "30", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p, dizinin ilk elemanını (10) gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1380, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int dizi[3] = {10, 20, 30};\nint* p = dizi;\n++p;\nstd::cout << *p;\nEkrana ne yazdırılır?",
        .options = {"20", "10", "30", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "++p, p'yi bir sonraki elemana (20) ilerletir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1381, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[5];\nint* p = dizi;\np + 1 ifadesi, p'yi kaç byte ileri taşır (int 4 byte varsayılırsa)?",
        .options = {"4 byte", "1 byte", "5 byte", "8 byte"},
        .acceptedAnswers = {"a"},
        .explanation = "Pointer aritmetiği, gösterilen türün boyutu (sizeof) kadar ilerler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1382, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {1, 2, 3};\nint* p = dizi;\np += 2;\nstd::cout << *p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"3", "2", "1", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "p += 2, p'yi dizi[2]'ye (3) taşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1383, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {5, 10, 15};\nstd::cout << *(dizi + 1);\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"10", "5", "15", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "dizi + 1, dizi[1]'i (10) gösterir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1384, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int dizi[4] = {1, 2, 3, 4};\nint* p = dizi;\nint toplam = 0;\nfor (int i = 0; i < 4; ++i) {\n    toplam += *p;\n    ++p;\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"10", "4", "24", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "1 + 2 + 3 + 4 = 10.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1385, .topicId = 56,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int dizi[3] = {7, 8, 9};\nint* p = dizi + 3;\nstd::cout << *p;\nBu kod ne yapar?",
        .options = {"Tanımsız davranış (dizinin sonunu geçen bir elemanı dereference eder)", "0 yazdırır", "9 yazdırır", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "dizi + 3, dizinin son elemanından (indeks 2) bir sonraki, geçersiz bir konumu dereference eder.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1386, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizi adı, kullanıldığı çoğu bağlamda ilk elemanının adresine dönüşür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: dizi adı, decay olarak ilk elemanının adresine dönüşür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1387, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir int pointer'ı bir artırmak (++p), p'yi her zaman 1 byte ileri taşır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: p, gösterdiği türün boyutu (genellikle 4 byte) kadar ilerler.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1388, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "ptr++ ifadesi, pointer'ı gösterdiği türün boyutu (sizeof) kadar ileri taşır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1389, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir pointer, bir dizi üzerinde döngüyle (for/while) elemanları tek tek dolaşmak için kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1390, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir dizinin son elemanından sonraki adresi (dizi + n) hesaplamak (dereference etmeden) geçerlidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: bu adresi hesaplamak geçerlidir, sadece dereference etmek tanımsız davranıştır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1391, .topicId = 56,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Dizinin son elemanından sonraki adresi (dizi + n) dereference etmek (* ile okumak) tanımsız davranıştır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1392, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir dizi adı, kullanıldığı çoğu bağlamda ilk elemanının _____ dönüşür (Türkçe kelime).",
        .acceptedAnswers = {"adresine"},
        .explanation = "Dizi adı, ilk elemanının adresine dönüşür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1393, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int dizi[3] = {1, 2, 3};\nint* p = dizi;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "p, dizinin ilk elemanını gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1394, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int dizi[3] = {1, 2, 3};\nint* p = dizi;\n++p;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"2"},
        .explanation = "++p, p'yi bir sonraki elemana ilerletir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1395, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {1, 2, 3};\nstd::cout << *(dizi + 2);\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "dizi + 2, dizi[2]'yi (3) gösterir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1396, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "ptr + 1, ptr'yi 1 byte değil, gösterdiği türün _____ (sizeof) kadar ileri taşır (Türkçe kelime, İngilizce köküyle de kabul edilir).",
        .acceptedAnswers = {"boyutu", "sizeof"},
        .explanation = "Pointer aritmetiği, elemanın boyutu (sizeof) kadar ilerler.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1397, .topicId = 56,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[4] = {2, 4, 6, 8};\nint* p = dizi + 3;\nstd::cout << *p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "dizi + 3, dizi[3]'ü (8) gösterir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1398, .topicId = 56,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {10, 20, 30};\n_____\nstd::cout << *p;\ndizi'nin ilk elemanını gösteren p adlı bir pointer tanımlayan satırı yazın.",
        .acceptedAnswers = {"int* p = dizi;"},
        .explanation = "p, dizi adının decay olduğu ilk eleman adresiyle ilklendirilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1399, .topicId = 56,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {1, 2, 3};\nint* p = dizi;\n_____\nstd::cout << *p;\np'yi bir sonraki elemana ilerleten satırı yazın.",
        .acceptedAnswers = {"++p;"},
        .explanation = "++p, p'yi bir sonraki elemana taşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1400, .topicId = 56,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int dizi[3] = {4, 5, 6};\nint* p = dizi;\nstd::cout << *p << *(p + 1) << *(p + 2);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"456"},
        .explanation = "Sırasıyla dizi[0], dizi[1], dizi[2]: 4, 5, 6.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1401, .topicId = 56,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int dizi[4] = {1, 2, 3, 4};\nint* p = dizi;\nfor (int i = 0; i < 4; ++i) {\n    *p = *p * 2;\n    ++p;\n}\nfor (int i = 0; i < 4; ++i) {\n    std::cout << dizi[i];\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2468"},
        .explanation = "Her eleman pointer üzerinden 2 ile çarpılır: 2, 4, 6, 8.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1402, .topicId = 56,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint dizi[3] = {1, 2, 3};\nint* p = dizi;\nfor (int i = 0; i <= 3; ++i) {\n    std::cout << *p;\n    ++p;\n}\n\nBu kod, döngü koşulunun (i <= 3) dizinin sınırını (3 eleman, indeks 0-2) bir eleman aşmasına izin verdiği için, son turda dizinin dışına taşan bir bellek konumunu dereference eder (tanımsız davranış). Hatalı döngü koşulunu düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int i = 0; i < 3; ++i) {"},
        .explanation = "Döngü, dizinin sınırını aşmayacak şekilde (i < 3) çalışmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1403, .topicId = 56,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint dizi[3] = {1, 2, 3};\nint* p = dizi + 3;\nstd::cout << *p;\n\nBu kod, dizinin son elemanından (indeks 2) bir sonraki konumu (dizi + 3, dizinin dışı) dereference ettiği için tanımsız davranışa yol açar. p'yi dizinin son geçerli elemanını (indeks 2) gösterecek şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int* p = dizi + 2;"},
        .explanation = "p, dizinin son geçerli elemanını (indeks 2) göstermelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1404, .topicId = 56,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint dizi[3] = {5, 10, 15};\nint* p = dizi;\nfor (int i = 0; i < 4; ++i) {\n    std::cout << *p << \" \";\n    ++p;\n}\n\nDöngü, dizinin 3 elemanı olmasına rağmen 4 kez çalışıyor; bu, dizinin dışına taşar. Döngü koşulunu düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int i = 0; i < 3; ++i) {"},
        .explanation = "Döngü, dizinin gerçek eleman sayısı (3) kadar çalışmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1405, .topicId = 56,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, pointer ile dizi dolaşan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* p = dizi;\n    std::cout << *p << *(p + 1);\n    return 0;\n}", "int dizi[2] = {3, 6};", "int main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "main açılışı (3), dizi tanımı (2), pointer ve yazdırma (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1406, .topicId = 56,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir int dizisi tanımlayın, bir pointer ile ilk elemanına erişip, döngüyle tüm elemanları pointer aritmetiği kullanarak (indeks yerine ++p ile) ekrana yazdırın.",
        .acceptedAnswers = {"int*", "++", "cout"},
        .explanation = "Pointer, döngü içinde ++p ile ilerletilerek tüm elemanlar yazdırılmalıdır.",
        .baseXp = 40,
    });

    // Topic 57: new
    questions.push_back(Question{
        .id = 1407, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "new operatörü ne yapar?",
        .options = {"Bellekte dinamik olarak (heap üzerinde) yer ayırır", "Bir değişkeni siler", "Bir referans oluşturur", "Bir dosya açar"},
        .acceptedAnswers = {"a"},
        .explanation = "new, çalışma zamanında heap üzerinde dinamik olarak yer ayırır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1408, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int* p = new int(5);\nstd::cout << *p;\ndelete p;\nEkrana ne yazdırılır?",
        .options = {"5", "0", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "new int(5), ayrılan belleği 5 ile ilklendirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1409, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "new int(5) ifadesi ne döndürür?",
        .options = {"Ayrılan belleğin adresini tutan bir int*", "Doğrudan 5 değerini", "Bir referans", "Bir string"},
        .acceptedAnswers = {"a"},
        .explanation = "new, ayrılan yerin adresini bir pointer olarak döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1410, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "new ile ayrılan bellek ne zamana kadar ayrılmış kalır?",
        .options = {"delete ile serbest bırakılana ya da program sonlanana kadar", "Fonksiyon bitene kadar (otomatik olarak)", "Bir sonraki new çağrısına kadar", "1 saniye boyunca"},
        .acceptedAnswers = {"a"},
        .explanation = "Dinamik bellek, açıkça serbest bırakılana ya da program sonlanana kadar ayrılmış kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1411, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(10);\n*p = *p + 5;\nstd::cout << *p;\ndelete p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"15", "10", "5", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "10 + 5 = 15.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1412, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "new ile ayrılan bir bellek, karşılık gelen delete çağrılmadan unutulursa ne olur?",
        .options = {"Bellek sızıntısı (memory leak) oluşur, program çökmez", "Program hemen çöker", "Derleyici hata verir", "Bellek otomatik olarak serbest bırakılır"},
        .acceptedAnswers = {"a"},
        .explanation = "delete edilmeyen new belleği bir sızıntıya yol açar; program bundan dolayı çökmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1413, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p1 = new int(1);\nint* p2 = new int(2);\nstd::cout << (p1 == p2);\ndelete p1;\ndelete p2;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"0", "1", "Belirsiz", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "İki ayrı new çağrısı farklı bellek adresleri döndürür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1414, .topicId = 57,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int* p = new int(7);\nint* q = p;\n*q = 20;\nstd::cout << *p;\ndelete p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"20", "7", "Derleme hatası", "Belirsiz"},
        .acceptedAnswers = {"a"},
        .explanation = "q = p, aynı adresi kopyalar; *q = 20 aynı belleği değiştirir, *p de artık 20'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1415, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "new operatörü, bellekte çalışma zamanında (heap üzerinde) dinamik olarak yer ayırır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1416, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "new ile ayrılan bellek, program tarafından otomatik olarak serbest bırakılır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: programcı delete ile serbest bırakmalıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1417, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "new int(5) ifadesi, ayrılan int'i 5 değeriyle ilklendirir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1418, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "new ile ayrılan bir bellek unutulursa (delete edilmezse) program hemen çöker.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: bir bellek sızıntısı oluşur ama program çalışmaya devam eder.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1419, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "new, ayrılan yerin adresini bir pointer olarak döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1420, .topicId = 57,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İki ayrı new int(...) çağrısı, her zaman aynı adresi döndürür.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: her çağrı ayrı bir bellek bloğu ayırır, farklı adresler döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1421, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bellekte dinamik olarak yer ayırmak için _____ operatörü kullanılır (İngilizce kelime).",
        .acceptedAnswers = {"new"},
        .explanation = "new operatörü dinamik bellek ayırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1422, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int* p = new int(8);\nstd::cout << *p;\ndelete p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"8"},
        .explanation = "new int(8), ayrılan belleği 8 ile ilklendirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1423, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "new ile ayrılan bellek, delete ile serbest bırakılana kadar veya program _____ kadar ayrılmış kalır (Türkçe kelime).",
        .acceptedAnswers = {"sonlanana"},
        .explanation = "Bellek, delete edilene ya da program sonlanana kadar ayrılmış kalır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1424, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(10);\n*p = *p * 2;\nstd::cout << *p;\ndelete p;\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"20"},
        .explanation = "10 * 2 = 20.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1425, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "new ile ayrılan bir bellek karşılık gelen delete olmadan unutulursa buna bellek _____ denir (Türkçe kelime).",
        .acceptedAnswers = {"sızıntısı"},
        .explanation = "Bu duruma bellek sızıntısı (memory leak) denir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1426, .topicId = 57,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "new int(5) ifadesinin döndürdüğü değerin türü _____ olur (İngilizce, bir kelime + sembol).",
        .acceptedAnswers = {"int*"},
        .explanation = "new int(5), int* türünde bir değer döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1427, .topicId = 57,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nstd::cout << *p;\ndelete p;\n5 değeriyle ilklendirilmiş bir int için dinamik bellek ayırıp p'ye atayan satırı yazın.",
        .acceptedAnswers = {"int* p = new int(5);"},
        .explanation = "new int(5), p'ye atanan ayrılmış bir int adresi döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1428, .topicId = 57,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(3);\n_____\nstd::cout << *p;\np'nin gösterdiği değeri 3 katına çıkaran satırı yazın.",
        .acceptedAnswers = {"*p = *p * 3;"},
        .explanation = "*p = *p * 3, ayrılan belleği 3 katına çıkarır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1429, .topicId = 57,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int* p = new int(4);\n*p += 6;\nstd::cout << *p;\ndelete p;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "4 + 6 = 10.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1430, .topicId = 57,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int* p = new int(2);\nint* q = new int(2);\nstd::cout << (*p == *q) << (p == q);\ndelete p;\ndelete q;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "*p == *q true (değerler eşit); p == q false (farklı bellek blokları).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1431, .topicId = 57,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nvoid fonksiyon() {\n    int* p = new int(5);\n    std::cout << *p;\n}\n\nBu fonksiyon, new ile ayrılan belleği hiçbir zaman delete etmiyor; fonksiyon her çağrıldığında bir bellek sızıntısı oluşur (program çökmez ama bellek asla geri kazanılmaz). Fonksiyonun sonuna eksik olan satırı ekleyin.",
        .acceptedAnswers = {"delete p;"},
        .explanation = "new ile ayrılan her bellek, karşılık gelen bir delete ile serbest bırakılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1432, .topicId = 57,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint* p = new int(5)\nstd::cout << *p;\ndelete p;\n\nBu kod derlenmez çünkü new int(5) satırının sonunda noktalı virgül eksik. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int* p = new int(5);"},
        .explanation = "Her ifade noktalı virgülle bitmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1433, .topicId = 57,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint* p = new int(9)\nstd::cout << *p;\ndelete p;\n\nProgramcı new int(9) satırının sonuna noktalı virgül koymayı unutmuş. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"int* p = new int(9);"},
        .explanation = "Eksik noktalı virgül eklenmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1434, .topicId = 57,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, new ile bellek ayırıp kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int* p = new int(7);", "std::cout << *p;\n    delete p;\n    return 0;\n}", "int main() {"},
        .acceptedAnswers = {"3 1 2"},
        .explanation = "main açılışı (3), new ile ayırma (1), yazdırma+delete+kapanış (2): sıra 3 1 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1435, .topicId = 57,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "new ile bir int için dinamik bellek ayırıp bir değerle ilklendirin, değerini ekrana yazdırın, ardından belleği delete ile serbest bırakın.",
        .acceptedAnswers = {"new", "delete", "cout"},
        .explanation = "Bellek new ile ayrılmalı, kullanılmalı ve delete ile serbest bırakılmalıdır.",
        .baseXp = 40,
    });
}

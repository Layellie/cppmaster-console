#include "QuestionContent.h"

#include "Question.h"

void appendSection5Questions(std::vector<Question>& questions) {
    // Topic 41: Parametresiz fonksiyon
    questions.push_back(Question{
        .id = 943, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Parametresiz bir fonksiyon çağrılırken parantez içine ne yazılır?",
        .options = {"Bir sayı", "Bir metin", "Hiçbir şey (boş bırakılır)", "Fonksiyonun adı tekrar"},
        .acceptedAnswers = {"c"},
        .explanation = "Parametresiz bir fonksiyon çağrılırken parantezler boş bırakılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 944, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void selamVer() { std::cout << \"Merhaba\"; } fonksiyonu nasıl çağrılır?",
        .options = {"selamVer;", "selamVer();", "call selamVer();", "selamVer[];"},
        .acceptedAnswers = {"b"},
        .explanation = "Fonksiyonlar adının yanına parantez konularak çağrılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 945, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Parametresiz bir fonksiyon her çağrıldığında davranışı değişir mi?",
        .options = {"Evet, her zaman farklı davranır", "Hayır, her çağrıda aynı işi yapar (parametreye bağlı değişkenlik yoktur)", "Yalnızca ilk çağrıda farklı davranır", "Rastgele değişir"},
        .acceptedAnswers = {"b"},
        .explanation = "Parametresiz bir fonksiyon her çağrıldığında aynı işi yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 946, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void mesaj() { std::cout << \"Selam\"; } int main() { mesaj(); mesaj(); return 0; } kodu ne yazdırır?",
        .options = {"Selam", "SelamSelam", "Selam Selam", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "mesaj() iki kez çağrıldığı için 'Selam' iki kez art arda yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 947, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f() { std::cout << \"A\"; } fonksiyonunun dönüş türü nedir?",
        .options = {"int", "void (değer döndürmez)", "string", "Belirtilmemiş"},
        .acceptedAnswers = {"b"},
        .explanation = "void dönüş türü, fonksiyonun hiçbir değer döndürmediğini belirtir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 948, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Parametresiz bir fonksiyon, fonksiyon gövdesi içinde başka değişkenler tanımlayabilir mi?",
        .options = {"Hayır, hiçbir değişken tanımlanamaz", "Evet, fonksiyon içinde yerel değişkenler tanımlanabilir", "Yalnızca parametre varsa değişken tanımlanabilir", "Yalnızca global değişkenler kullanılabilir"},
        .acceptedAnswers = {"b"},
        .explanation = "Parametre olmasa bile fonksiyon içinde yerel değişkenler tanımlanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 949, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void yazdir() { return 5; } kodu geçerli midir?",
        .options = {"Evet, 5 döndürülür", "Hayır, void bir fonksiyon değer döndüremez; derleme hatası oluşur", "Evet, ama 5 yok sayılır", "Yalnızca int'e dönüştürülebilirse geçerlidir"},
        .acceptedAnswers = {"b"},
        .explanation = "void bir fonksiyon return ile bir değer döndüremez; bu bir derleme hatasıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 950, .topicId = 41,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int main() { yazdir(); return 0; } void yazdir() { std::cout << \"Test\"; } kodu neden derlenmez (yazdir main'den SONRA tanımlanmış, önceden prototip de verilmemiş)?",
        .options = {"main() her zaman ilk fonksiyon olmalıdır", "Derleyici, yazdir() çağrısına ulaştığında onun ne olduğunu (tanımını/prototipini) henüz bilmiyor", "void fonksiyonlar main() içinde çağrılamaz", "Fonksiyon isimleri en fazla 5 harf olabilir"},
        .acceptedAnswers = {"b"},
        .explanation = "Derleyici dosyayı yukarıdan aşağıya işler; bir fonksiyonun tanımı veya prototipi olmadan çağrılması derleme hatasına yol açar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 951, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Parametresiz bir fonksiyon hiçbir girdi almadan çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Parametresiz fonksiyonların tanımı budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 952, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Parametresiz bir fonksiyon çağrılırken parantezler atlanabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Parantezler her zaman yazılmalıdır, boş olsalar bile.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 953, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void selamVer() { ... } fonksiyonu bir değer döndürebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "void fonksiyonlar değer döndüremez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 954, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Parametresiz bir fonksiyon, içinde yerel değişkenler kullanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Fonksiyonun parametresi olmaması, yerel değişken tanımlamasını engellemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 955, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyon, tanımından önce (ve prototipi olmadan) çağrılırsa derleme hatası oluşur.",
        .acceptedAnswers = {"1"},
        .explanation = "Derleyici, önceden tanımlanmamış veya bildirilmemiş bir fonksiyonu tanıyamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 956, .topicId = 41,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Parametresiz bir fonksiyon birden fazla kez çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Herhangi bir fonksiyon istenildiği kadar çağrılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 957, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void selamVer_____ {\n    std::cout << \"Merhaba\";\n}\nParametresiz bir fonksiyon tanımlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"()"},
        .explanation = "Boş parantez (), fonksiyonun parametre almadığını gösterir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 958, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void selamVer() {\n    std::cout << \"Merhaba\";\n}\nint main() {\n    selamVer_____;\n    return 0;\n}\nFonksiyonu çağırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"()"},
        .explanation = "Fonksiyon çağrısı boş parantezle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 959, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ selamVer() {\n    std::cout << \"Merhaba\";\n}\nDeğer döndürmeyen bir fonksiyon tanımlamak için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"void"},
        .explanation = "void anahtar kelimesi, fonksiyonun değer döndürmediğini belirtir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 960, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir() {\n    std::cout << \"Bir\";\n}\nint main() {\n    yazdir();\n    yazdir_____;\n    return 0;\n}\nFonksiyonu ikinci kez çağırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"()"},
        .explanation = "Aynı fonksiyon tekrar çağrılırken de boş parantez kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 961, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f() {\n    int x _____ 10;\n    std::cout << x;\n}\nFonksiyon içinde yerel bir değişken tanımlayıp 10 değerini atamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"="},
        .explanation = "Atama operatörü = kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 962, .topicId = 41,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void bosFonksiyon()_____\nBoş bir fonksiyon gövdesi (hiçbir kod içermeyen) tanımlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"{}"},
        .explanation = "Boş süslü parantezler {}, hiçbir kod içermeyen bir gövde tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 963, .topicId = 41,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\n    std::cout << \"Merhaba, Dünya!\";\n}\nselamVer adında, parametre almayan bir fonksiyon başlatan satırı yazın.",
        .acceptedAnswers = {"void selamVer() {"},
        .explanation = "void selamVer() {, parametresiz bir fonksiyon tanımının başlangıcıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 964, .topicId = 41,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void selamVer() {\n    std::cout << \"Merhaba\";\n}\nint main() {\n    _____\n    return 0;\n}\nselamVer fonksiyonunu çağıran satırı yazın.",
        .acceptedAnswers = {"selamVer();"},
        .explanation = "Fonksiyon adının yanına boş parantez konularak çağrılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 965, .topicId = 41,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void mesajYaz() {\n    std::cout << \"Merhaba\";\n}\nint main() {\n    mesajYaz();\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Merhaba"},
        .explanation = "mesajYaz() çağrıldığında 'Merhaba' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 966, .topicId = 41,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void yaz() {\n    std::cout << \"X\";\n}\nint main() {\n    yaz();\n    yaz();\n    yaz();\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"XXX"},
        .explanation = "yaz() üç kez çağrıldığı için 'X' üç kez art arda yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 967, .topicId = 41,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid selamVer() {\n    std::cout << \"Merhaba\";\n}\nint main() {\n    selamVer;\n    return 0;\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"selamVer();"},
        .explanation = "Fonksiyon çağrısında parantezler eksik.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 968, .topicId = 41,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid yazdir() {\n    return \"Merhaba\";\n}\n\nBu kod derlenmez çünkü void bir fonksiyon değer döndüremez. Programcı yalnızca ekrana yazdırmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << \"Merhaba\";"},
        .explanation = "void fonksiyon değer döndüremeyeceği için doğrudan ekrana yazdırma kullanılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 969, .topicId = 41,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid selamVer( {\n    std::cout << \"Merhaba\";\n}\n\nDüzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"void selamVer() {"},
        .explanation = "Parametre listesinin kapanış parantezi eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 970, .topicId = 41,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir fonksiyon tanımlayıp çağıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"selamVer();", "void selamVer() {\n    std::cout << \"Merhaba\";\n}"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce fonksiyon tanımlanır (2), sonra çağrılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 971, .topicId = 41,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Parametre almayan ve ekrana 'Merhaba, C++!' yazan bir fonksiyon tanımlayıp, main() içinden çağıran bir program yazın.",
        .acceptedAnswers = {"void", "cout", "<<"},
        .explanation = "Program parametresiz bir fonksiyon tanımlamalı ve onu main() içinden çağırmalıdır.",
        .baseXp = 40,
    });

    // Topic 42: Parametre alan fonksiyon
    questions.push_back(Question{
        .id = 972, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyona dışarıdan veri göndermek için ne kullanılır?",
        .options = {"Global değişken", "Parametre", "Yorum satırı", "Makro"},
        .acceptedAnswers = {"b"},
        .explanation = "Parametreler, bir fonksiyona dışarıdan veri göndermenin standart yoludur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 973, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void sayiYazdir(int sayi) fonksiyonu kaç parametre alır?",
        .options = {"0", "1", "2", "Belirsiz"},
        .acceptedAnswers = {"b"},
        .explanation = "Fonksiyon yalnızca bir parametre (sayi) alır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 974, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void sayiYazdir(int sayi) { std::cout << sayi; } sayiYazdir(7); çağrısı ne yazdırır?",
        .options = {"0", "7", "sayi", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "sayi parametresi 7 değerini alır ve yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 975, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void topla(int a, int b) fonksiyonu kaç parametre alır?",
        .options = {"1", "2", "3", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "Fonksiyon iki parametre (a ve b) alır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 976, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void carp(int a, int b) { std::cout << a * b; } carp(3, 4); çağrısı ne yazdırır?",
        .options = {"7", "12", "34", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "3 * 4 = 12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 977, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyon çağrılırken verilen değerlere ne denir?",
        .options = {"Parametre", "Argüman", "Değişken", "Sabit"},
        .acceptedAnswers = {"b"},
        .explanation = "Çağrı sırasında verilen değerlere argüman denir; parametre ise fonksiyon tanımındaki isimdir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 978, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int a, int b) { ... } f(1); şeklinde çağrılırsa ne olur (yalnızca 1 argüman verildi ama fonksiyon 2 parametre bekliyor, varsayılan değer de yok)?",
        .options = {"b otomatik olarak 0 olur", "Derleme hatası oluşur (yetersiz argüman)", "b, a ile aynı değeri alır", "Program çalışır ama b tanımsız kalır"},
        .acceptedAnswers = {"b"},
        .explanation = "Varsayılan değeri olmayan bir parametre için argüman verilmezse derleme hatası oluşur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 979, .topicId = 42,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int a, int b, int c) { std::cout << a + b + c; } f(1, 2, 3); çağrısının çıktısı nedir?",
        .options = {"123", "6", "Hata", "1 2 3"},
        .acceptedAnswers = {"b"},
        .explanation = "1 + 2 + 3 = 6.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 980, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyon, parametreler aracılığıyla dışarıdan veri alabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Parametrelerin amacı budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 981, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Parametre sayısı, fonksiyon çağrısında verilen argüman sayısıyla eşleşmek zorunda değildir.",
        .acceptedAnswers = {"2"},
        .explanation = "Varsayılan değerler yoksa parametre sayısı ile argüman sayısı eşleşmelidir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 982, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Parametreler, yalnızca fonksiyon içinde geçerli olan yerel değişkenler gibi davranır.",
        .acceptedAnswers = {"1"},
        .explanation = "Parametreler fonksiyonun kapsamı içinde yerel değişken gibi davranır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 983, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b) fonksiyonu tek bir argümanla çağrılabilir (varsayılan değer olmadan).",
        .acceptedAnswers = {"2"},
        .explanation = "Varsayılan değer yoksa her parametre için bir argüman verilmelidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 984, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyonun birden fazla parametresi virgülle ayrılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Parametreler virgülle ayrılarak listelenir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 985, .topicId = 42,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Parametre türü ile çağrıda verilen argümanın türü hiçbir zaman uyuşmak zorunda değildir.",
        .acceptedAnswers = {"2"},
        .explanation = "Argüman türü parametre türüyle uyumlu olmalıdır (ya da örtük dönüşüme uygun olmalıdır).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 986, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void sayiYazdir(int _____) {\n    std::cout << sayi;\n}\nBir parametre tanımlamak için boşluğa ne yazılmalı? (örnek: sayi)",
        .acceptedAnswers = {"sayi"},
        .explanation = "Parametre adı, gövdede kullanılan isimle eşleşmelidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 987, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void sayiYazdir(int sayi) {\n    std::cout << sayi;\n}\nint main() {\n    sayiYazdir_____;\n    return 0;\n}\nFonksiyonu 5 argümanıyla çağırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"(5)"},
        .explanation = "Argüman parantez içinde verilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 988, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void topla(int a_____ int b) {\n    std::cout << a + b;\n}\nİki parametreyi ayırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {","},
        .explanation = "Parametreler virgülle ayrılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 989, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void carp(int a, int b) {\n    std::cout << a _____ b;\n}\nİki parametreyi çarpmak için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "Çarpma operatörü * kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 990, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b, int c) { ... } f(1, 2, _____); çağrısının 3 argüman içermesi için boşluğa (herhangi bir tam sayı) ne yazılabilir? (örnek: 3)",
        .acceptedAnswers = {"3"},
        .explanation = "Üçüncü parametreye karşılık gelen argüman verilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 991, .topicId = 42,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir(std::string _____) {\n    std::cout << metin;\n}\nstd::string türünde bir parametre tanımlamak için boşluğa ne yazılmalı? (örnek: metin)",
        .acceptedAnswers = {"metin"},
        .explanation = "Parametre adı, gövdede kullanılan isimle eşleşmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 992, .topicId = 42,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\n    std::cout << sayi;\n}\nsayi adında int parametre alan yazdir fonksiyonunu başlatan satırı yazın.",
        .acceptedAnswers = {"void yazdir(int sayi) {"},
        .explanation = "Fonksiyon tanımı, dönüş türü, ad ve parametre listesinden oluşur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 993, .topicId = 42,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void carp(int a, int b) {\n    std::cout << a * b;\n}\nint main() {\n    _____\n    return 0;\n}\ncarp fonksiyonunu 3 ve 4 argümanlarıyla çağıran satırı yazın.",
        .acceptedAnswers = {"carp(3, 4);"},
        .explanation = "Argümanlar parantez içinde virgülle ayrılarak verilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 994, .topicId = 42,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir(int sayi) {\n    std::cout << sayi;\n}\nint main() {\n    yazdir(42);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"42"},
        .explanation = "sayi parametresi 42 değerini alır ve yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 995, .topicId = 42,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void topla(int a, int b) {\n    std::cout << a + b;\n}\nint main() {\n    topla(10, 20);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30"},
        .explanation = "10 + 20 = 30.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 996, .topicId = 42,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid yazdir(int sayi) {\n    std::cout << sayi;\n}\nint main() {\n    yazdir();\n    return 0;\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"yazdir(5);"},
        .explanation = "Fonksiyon bir parametre beklediği için çağrıda bir argüman verilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 997, .topicId = 42,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid topla(int a, int b) {\n    std::cout << a + b;\n}\nint main() {\n    topla(5);\n    return 0;\n}\n\nBu kod derlenmez çünkü topla iki parametre bekliyor ama yalnızca bir argüman verilmiş. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"topla(5, 3);"},
        .explanation = "İki parametreli fonksiyon için iki argüman verilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 998, .topicId = 42,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid yazdir(int sayi) {\n    std::cout << sayi;\n}\nint main() {\n    yazdir(5;\n    return 0;\n}\n\nDüzeltilmiş üçüncü satırı yazın.",
        .acceptedAnswers = {"yazdir(5);"},
        .explanation = "Fonksiyon çağrısında kapanış parantezi eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 999, .topicId = 42,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, iki sayıyı çarpan bir fonksiyon tanımlayıp çağıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"topla(3, 4);", "void topla(int a, int b) {\n    std::cout << a + b;\n}"},
        .acceptedAnswers = {"2 1"},
        .explanation = "Önce fonksiyon tanımlanır (2), sonra çağrılır (1): sıra 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1000, .topicId = 42,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "İki tam sayı parametre alan ve bunların çarpımını ekrana yazdıran bir fonksiyon tanımlayıp, main() içinden çağıran bir program yazın.",
        .acceptedAnswers = {"void", "cout", "<<", "*"},
        .explanation = "Program iki parametreli bir fonksiyon tanımlamalı ve çarpımı yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 43: Değer döndüren fonksiyon
    questions.push_back(Question{
        .id = 1001, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyonun değer döndürmesi için hangi anahtar kelime kullanılır?",
        .options = {"void", "return", "break", "exit"},
        .acceptedAnswers = {"b"},
        .explanation = "return ifadesi bir fonksiyondan değer döndürür.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1002, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int kareAl(int sayi) { return sayi * sayi; } kareAl(3) çağrısı ne döner?",
        .options = {"3", "6", "9", "Hata"},
        .acceptedAnswers = {"c"},
        .explanation = "3 * 3 = 9.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1003, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir fonksiyonun dönüş türü int ise, return ifadesinde hangi türde bir değer olmalıdır?",
        .options = {"Yalnızca string", "int (veya int'e dönüştürülebilir bir tür)", "void", "Herhangi bir tür olabilir, fark etmez"},
        .acceptedAnswers = {"b"},
        .explanation = "Dönüş türü ile return ifadesindeki değerin türü uyumlu olmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1004, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int f() { return 5; std::cout << \"Merhaba\"; } fonksiyonu çağrıldığında 'Merhaba' yazdırılır mı?",
        .options = {"Evet, her zaman yazdırılır", "Hayır, return ifadesinden sonraki kod hiç çalışmaz", "Yalnızca sayi 0 ise yazdırılır", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "return, fonksiyonu anında sonlandırır; sonrasındaki kod hiç çalışmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1005, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b) { return a * b; } int sonuc = carp(4, 5); sonuc kaç olur?",
        .options = {"9", "20", "45", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "4 * 5 = 20.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1006, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Dönüş türü int olan bir fonksiyonda return ifadesi hiç yazılmazsa ne olur?",
        .options = {"0 döner otomatik olarak", "Tanımsız davranış / derleyici uyarısı (bazı durumlarda hata)", "void olarak davranır", "Sonsuz döngüye girer"},
        .acceptedAnswers = {"b"},
        .explanation = "int dönüş türlü bir fonksiyonda return eksikse, derleyici uyarır ve davranış tanımsızdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1007, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "double bol(int a, int b) { return a / b; } bol(7, 2) çağrısı ne döner (dikkat: a ve b int)?",
        .options = {"3.5", "3", "4", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "a / b önce int bölmesi olarak hesaplanır (3 olur), sonra double'a dönüştürülür; sonuç 3.5 değil 3'tür (cout 3.0'ı '3' olarak gösterir).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1008, .topicId = 43,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a) { if (a > 0) return 1; return -1; } f(-5) çağrısı ne döner?",
        .options = {"1", "-1", "0", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "a=-5, a > 0 false olduğu için ilk return atlanır; son satırdaki return -1 çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1009, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "return ifadesi bir fonksiyondan değer döndürür.",
        .acceptedAnswers = {"1"},
        .explanation = "return'ün işlevi budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1010, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "void bir fonksiyon return ile bir değer döndürebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "void fonksiyonlar değer döndüremez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1011, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "return ifadesinden sonraki kod, fonksiyon içinde çalışmaya devam eder.",
        .acceptedAnswers = {"2"},
        .explanation = "return, fonksiyonu anında sonlandırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1012, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int kareAl(int x) { return x * x; } kareAl(5) çağrısı 25 döner.",
        .acceptedAnswers = {"1"},
        .explanation = "5 * 5 = 25.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1013, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyonun döndürdüğü değer bir değişkene atanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "int sonuc = f(); gibi bir atama geçerlidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1014, .topicId = 43,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Dönüş türü int olan bir fonksiyon, her zaman bir tam sayı literal'i (örneğin sadece 5) döndürmelidir; bir ifade (örneğin a+b) döndüremez.",
        .acceptedAnswers = {"2"},
        .explanation = "return, herhangi bir int türünde ifade döndürebilir, yalnızca literal değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1015, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int kareAl(int x) {\n    _____ x * x;\n}\nBir değer döndürmek için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"return"},
        .explanation = "return anahtar kelimesi değeri döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1016, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ kareAl(int x) {\n    return x * x;\n}\nBir int değer döndüren fonksiyonun dönüş türünü belirtmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"int"},
        .explanation = "Dönüş türü fonksiyon adından önce belirtilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1017, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int carp(int a, int b) {\n    return a _____ b;\n}\nİki sayıyı çarpıp döndürmek için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "Çarpma operatörü * kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1018, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int f(int x) {\n    return x _____ 2;\n}\nint sonuc = f(10); ifadesinin sonuc'u 20 yapması için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "10 * 2 = 20.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1019, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int topla(int a, int b) {\n    return a + b;\n}\nint sonuc = _____;\ntopla fonksiyonunu 3 ve 4 argümanlarıyla çağırıp sonucu sonuc'a atayan ifadeyi yazın.",
        .acceptedAnswers = {"topla(3, 4)"},
        .explanation = "Fonksiyon çağrısının döndürdüğü değer bir değişkene atanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1020, .topicId = 43,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "bool tekMi(int sayi) {\n    return sayi % 2 _____ 1;\n}\nsayi'nın tek olup olmadığını kontrol eden ifadeyi tamamlamak için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1021, .topicId = 43,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int kareAl(int x) {\n    _____\n}\nx'in karesini döndüren satırı yazın.",
        .acceptedAnswers = {"return x * x;"},
        .explanation = "return x * x; ifadesi x'in karesini döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1022, .topicId = 43,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b) {\n    return a * b;\n}\nint main() {\n    int sonuc = _____;\n    std::cout << sonuc;\n}\ncarp fonksiyonunu 6 ve 7 argümanlarıyla çağırıp sonucu alan ifadeyi yazın.",
        .acceptedAnswers = {"carp(6, 7)"},
        .explanation = "Fonksiyon çağrısının sonucu bir değişkene atanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1023, .topicId = 43,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int kareAl(int x) {\n    return x * x;\n}\nint main() {\n    std::cout << kareAl(5);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"25"},
        .explanation = "5 * 5 = 25.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1024, .topicId = 43,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a, int b) {\n    return a - b;\n}\nint main() {\n    std::cout << f(10, 3) << f(3, 10);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"7-7"},
        .explanation = "f(10,3) = 10-3 = 7, f(3,10) = 3-10 = -7; birlikte '7-7' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1025, .topicId = 43,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint kareAl(int x) {\n    x * x;\n}\n\nProgramcı x'in karesini döndürmek istiyor ama return ifadesini yazmayı unutmuş. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"return x * x;"},
        .explanation = "Değeri döndürmek için return kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1026, .topicId = 43,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid kareAl(int x) {\n    return x * x;\n}\n\nBu kod derlenmez çünkü void bir fonksiyon değer döndüremez. Programcı x'in karesini döndürmek istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int kareAl(int x) {"},
        .explanation = "Değer döndüren fonksiyonun dönüş türü void değil, uygun bir tür (int) olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1027, .topicId = 43,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint topla(int a, int b) {\n    retrun a + b;\n}\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"return a + b;"},
        .explanation = "'retrun' yazım hatasıdır; doğrusu 'return'dür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1028, .topicId = 43,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir sayının karesini hesaplayıp yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << sonuc;", "int sonuc = kareAl(5);", "int kareAl(int x) {\n    return x * x;\n}"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce fonksiyon tanımlanır (3), sonra çağrılıp sonuç alınır (2), en son yazdırılır (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1029, .topicId = 43,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "İki tam sayı parametre alan ve toplamlarını döndüren bir fonksiyon yazıp, döndürülen değeri main() içinde ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"return", "cout", "<<", "+"},
        .explanation = "Program iki sayıyı toplayıp döndüren bir fonksiyon tanımlamalı ve sonucu yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 44: Fonksiyon prototipi
    questions.push_back(Question{
        .id = 1030, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Fonksiyon prototipi neyi içerir?",
        .options = {"Fonksiyonun tam gövdesini", "Yalnızca fonksiyonun imzasını (dönüş türü, adı, parametreleri)", "Yalnızca fonksiyonun adını", "Fonksiyonun çağrıldığı yeri"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip yalnızca fonksiyonun imzasını içerir, gövdesini içermez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1031, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Bir fonksiyon prototipi hangi karakterle biter?",
        .options = {"{ (süslü parantez)", "; (noktalı virgül)", ": (iki nokta)", ", (virgül)"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip, gövdesi olmadığı için noktalı virgülle biter.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1032, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int topla(int a, int b); ifadesi bir fonksiyon prototipi midir?",
        .options = {"Evet", "Hayır, bu bir fonksiyon tanımıdır", "Hayır, bu bir değişken tanımıdır", "Hayır, bu bir fonksiyon çağrısıdır"},
        .acceptedAnswers = {"a"},
        .explanation = "Gövdesi olmadan noktalı virgülle biten bu ifade bir prototiptir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1033, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Fonksiyon prototipi neden kullanılır?",
        .options = {"Fonksiyonu hızlandırmak için", "Bir fonksiyonun, gerçek tanımından önce (örneğin main() içinde) çağrılabilmesini sağlamak için", "Bellek tasarrufu sağlamak için", "Yalnızca stil tercihi, işlevsel bir amacı yoktur"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip, derleyiciye fonksiyonun imzasını önceden bildirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1034, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int f(int x); int main() { f(5); return 0; } int f(int x) { return x; } yapısında f'nin prototipi olmasaydı ne olurdu?",
        .options = {"Hiçbir fark olmazdı", "Derleme hatası oluşurdu (main, f'yi henüz tanımadığı için)", "f otomatik olarak void olurdu", "main() çalışmazdı ama derlenirdi"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip olmadan, tanımından önce çağrılan bir fonksiyon derleme hatasına yol açar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1035, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyonun prototipindeki parametre türleri, gerçek tanımındakilerle uyuşmalı mıdır?",
        .options = {"Hayır, farklı olabilir", "Evet, uyuşmalıdır", "Yalnızca parametre sayısı uyuşmalı, türler önemli değil", "Yalnızca dönüş türü uyuşmalı"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip ile tanım aynı imzaya (dönüş türü, parametre türleri) sahip olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1036, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int topla(int a, int b); ... double topla(int a, int b) { return a + b; } yapısı geçerli midir (prototip int, tanım double dönüyor)?",
        .options = {"Evet, derleyici otomatik dönüştürür", "Hayır, prototip ile tanımın dönüş türü uyuşmuyor; derleme hatası oluşur", "Evet, ama yalnızca int değerler döner", "Yalnızca 64-bit sistemlerde çalışır"},
        .acceptedAnswers = {"b"},
        .explanation = "Prototip ile gerçek tanımın dönüş türü de birebir uyuşmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1037, .topicId = 44,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Bir fonksiyon prototipi ile aynı fonksiyonun tam tanımı aynı dosyada birden fazla kez (aynı imzayla, tekrar tekrar) tanım olarak yazılabilir mi?",
        .options = {"Evet, sınırsız sayıda tanımlanabilir", "Hayır, aynı fonksiyon yalnızca bir kez tanımlanabilir (yeniden tanım hatası oluşur); prototip ise birden fazla kez yazılabilir", "Yalnızca 2 kez tanımlanabilir", "Tanım sayısı önemli değildir"},
        .acceptedAnswers = {"b"},
        .explanation = "Bir fonksiyon yalnızca bir kez tanımlanabilir; prototip (bildirim) ise tekrarlanabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1038, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyon prototipi, fonksiyonun gövdesini içermez.",
        .acceptedAnswers = {"1"},
        .explanation = "Prototip yalnızca imzayı içerir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1039, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Fonksiyon prototipi bir süslü parantez { } bloğuyla biter.",
        .acceptedAnswers = {"2"},
        .explanation = "Prototip noktalı virgülle biter, süslü parantezle değil.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1040, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Prototip sayesinde bir fonksiyon, gerçek tanımından önce çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Prototipin temel amacı budur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1041, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Prototip ile gerçek tanımın parametre türleri farklı olabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Parametre türleri prototip ile tanımda uyuşmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1042, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyon aynı dosyada yalnızca bir kez tanımlanabilir (birden fazla tanım hataya yol açar).",
        .acceptedAnswers = {"1"},
        .explanation = "Aynı imzaya sahip bir fonksiyon yalnızca bir kez tanımlanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1043, .topicId = 44,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Fonksiyon prototipi, fonksiyonun parametre adlarını mutlaka içermelidir (yalnızca türler yetersizdir).",
        .acceptedAnswers = {"2"},
        .explanation = "Prototipte yalnızca parametre türleri yeterlidir; adlar isteğe bağlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1044, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int topla(int a, int b)_____\nBir fonksiyon prototipini tamamlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {";"},
        .explanation = "Prototip noktalı virgülle biter.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1045, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int topla(int a, int b);\nint main() {\n    std::cout << topla(2, 3);\n    return 0;\n}\nint topla(int a, int b) {\n    _____ a + b;\n}\nDeğer döndürmek için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"return"},
        .explanation = "return, değeri döndürür.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1046, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ topla(int a, int b);\nint değer döndüren bir fonksiyon prototipi tanımlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"int"},
        .explanation = "Dönüş türü prototipin başında belirtilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1047, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "double bol(double a, double b);\nBu prototipe uygun tanımın dönüş türü _____ olmalıdır.",
        .acceptedAnswers = {"double"},
        .explanation = "Tanımın dönüş türü prototipiyle uyuşmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1048, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b);\nint main() {\n    std::cout << carp(4, 5);\n}\nint carp(int a, int _____) {\n    return a * b;\n}\nİkinci parametrenin adını (prototiple aynı sayıda parametre olacak şekilde) boşluğa yazın.",
        .acceptedAnswers = {"b"},
        .explanation = "Gövdede kullanılan parametre adı, tanımdaki adla eşleşmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1049, .topicId = 44,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(int x);\nProtipin sonunda gövde yerine _____ karakteri bulunur.",
        .acceptedAnswers = {";"},
        .explanation = "Prototip noktalı virgülle biter.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1050, .topicId = 44,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nint main() {\n    std::cout << topla(3, 4);\n    return 0;\n}\nint topla(int a, int b) {\n    return a + b;\n}\ntopla fonksiyonunun prototipini yazın.",
        .acceptedAnswers = {"int topla(int a, int b);"},
        .explanation = "Prototip, dönüş türü, ad ve parametre listesinden oluşur, noktalı virgülle biter.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1051, .topicId = 44,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b);\nint main() {\n    std::cout << carp(2, 5);\n    return 0;\n}\n_____\ncarp fonksiyonunun gerçek tanımını (gövdesiyle) yazın.",
        .acceptedAnswers = {"int carp(int a, int b) { return a * b; }"},
        .explanation = "Gerçek tanım, prototiple uyumlu imzaya ve bir gövdeye sahip olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1052, .topicId = 44,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int topla(int a, int b);\nint main() {\n    std::cout << topla(3, 4);\n    return 0;\n}\nint topla(int a, int b) {\n    return a + b;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"7"},
        .explanation = "3 + 4 = 7.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1053, .topicId = 44,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int carp(int a, int b);\nint main() {\n    std::cout << carp(2, 3) << carp(4, 5);\n    return 0;\n}\nint carp(int a, int b) {\n    return a * b;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"620"},
        .explanation = "carp(2,3) = 6, carp(4,5) = 20; birlikte '620' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1054, .topicId = 44,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint topla(int a, int b)\nint main() {\n    std::cout << topla(2, 3);\n    return 0;\n}\nint topla(int a, int b) {\n    return a + b;\n}\n\nBu kod derlenmez çünkü prototipin sonunda noktalı virgül eksik. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int topla(int a, int b);"},
        .explanation = "Prototip noktalı virgülle bitmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1055, .topicId = 44,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint topla(int a, int b);\nint main() {\n    std::cout << topla(2, 3);\n    return 0;\n}\ndouble topla(int a, int b) {\n    return a + b;\n}\n\nBu kod derlenmez çünkü prototipte dönüş türü int iken gerçek tanımda double kullanılmış. Hatalı satırı, prototiple uyumlu olacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int topla(int a, int b) {"},
        .explanation = "Tanımın dönüş türü prototipiyle aynı (int) olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1056, .topicId = 44,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint topla(int a, int b);\nint main() {\n    std::cout << topla(2, 3);\n    return 0;\n}\nint topla(int a, int c) {\n    return a + b;\n}\n\nProgramcı ikinci parametrenin adını prototiple tutarsız yazmış (tanımda c, kullanımda b). Düzeltilmiş dördüncü satırı yazın.",
        .acceptedAnswers = {"int topla(int a, int b) {"},
        .explanation = "Gövdede kullanılan parametre adı (b) ile tanımdaki parametre adı eşleşmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1057, .topicId = 44,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, prototipli bir topla fonksiyonu kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int topla(int a, int b) {\n    return a + b;\n}", "std::cout << topla(2, 3);\n    return 0;\n}", "int topla(int a, int b);\nint main() {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Prototip ve main açılışı (3), çağrı ve main kapanışı (2), gerçek tanım (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1058, .topicId = 44,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir topla fonksiyonunun önce prototipini yazıp, main() içinde çağırıp, ardından gerçek tanımını (gövdesini) main()'den sonra veren bir program yazın.",
        .acceptedAnswers = {"int", "return", "cout", "<<"},
        .explanation = "Program prototip, main() içinde çağrı ve main()'den sonra gerçek tanım içermelidir.",
        .baseXp = 40,
    });

    // Topic 45: Varsayılan parametre
    questions.push_back(Question{
        .id = 1059, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "void selamla(std::string isim = \"Misafir\");\nBu fonksiyon parametresiz çağrıldığında (selamla();) isim parametresi ne olur?",
        .options = {"\"Misafir\"", "Boş string", "Derleme hatası", "Rastgele değer"},
        .acceptedAnswers = {"a"},
        .explanation = "Parametre verilmezse varsayılan değer (\"Misafir\") kullanılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1060, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir parametreye varsayılan değer, fonksiyonun neresinde belirtilir?",
        .options = {"Parametre tanımının yanında (=değer)", "Fonksiyon gövdesinin içinde", "Sadece main() içinde", "Yorum satırında"},
        .acceptedAnswers = {"a"},
        .explanation = "Varsayılan değer, parametre listesinde `tür ad = değer` şeklinde belirtilir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1061, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b = 10);\nf(5) çağrısında b'nin değeri nedir?",
        .options = {"10", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "b için değer verilmediğinden varsayılan 10 kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1062, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b = 10);\nf(5, 20) çağrısında b'nin değeri nedir?",
        .options = {"20", "10", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Çağrıda açıkça verilen değer (20), varsayılan değerin yerine geçer.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1063, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdakilerden hangisi geçerli bir fonksiyon tanımıdır?",
        .options = {"void f(int a, int b = 5)", "void f(int a = 5, int b)", "void f(int a = 5, int b = 10, int c)", "void f(int a, int b = 5, int c)"},
        .acceptedAnswers = {"a"},
        .explanation = "Varsayılan değerli parametreler, listenin sonunda (trailing) olmalıdır; varsayılan olmayan bir parametre varsayılandan sonra gelemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1064, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b = 5, int c = 10);\nf(1, 2) çağrısında c'nin değeri nedir?",
        .options = {"10", "5", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "c için değer verilmediğinden varsayılan 10 kullanılır (b ise 2 olur).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1065, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a = 1, int b);\nBu tanım neden derleme hatası verir?",
        .options = {"Varsayılan değerli parametre, varsayılan olmayandan önce gelemez", "int türü varsayılan değer alamaz", "Fonksiyonlar en fazla bir parametre alabilir", "f adı geçersizdir"},
        .acceptedAnswers = {"a"},
        .explanation = "a varsayılan değer aldığı için ondan sonraki tüm parametreler (b) de varsayılan değer almalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1066, .topicId = 45,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a = 1, int b = 2) {\n    return a + b;\n}\nint main() {\n    std::cout << f() << f(10);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"312", "33", "1210", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "f() -> 1+2=3, f(10) -> 10+2=12; birlikte '312' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1067, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Varsayılan parametre değeri olan bir fonksiyon, o parametre verilmeden de çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: varsayılan değer, parametre atlandığında kullanılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1068, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir parametreye varsayılan değer atansa bile, çağrıda o parametreye farklı bir değer vermek mümkündür.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: çağrıda verilen değer varsayılanın yerine geçer.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1069, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a = 1, int b); şeklindeki bir tanım geçerlidir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: varsayılan değerli bir parametreden sonra varsayılansız parametre gelemez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1070, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b = 5); tanımlı fonksiyon f(1, 2) şeklinde de çağrılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: varsayılan parametreye açıkça değer vermek serbesttir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1071, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir fonksiyonun tüm parametreleri aynı anda varsayılan değere sahip olabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: tüm parametreler varsayılan değerli olabilir, bu durumda fonksiyon hiç argüman almadan da çağrılabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1072, .topicId = 45,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a = 1, int b = 2, int c); tanımı derlenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: c varsayılan değeri olmadan a ve b'den sonra gelemez; trailing kuralı ihlal edilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1073, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "void f(int a, int b _____ 5);\nb parametresine 5 varsayılan değerini atamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"="},
        .explanation = "Varsayılan değer atama `=` işaretiyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1074, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a, int b = 5);\nf(3) çağrısında b'nin değeri _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "b verilmediğinden varsayılan 5 kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1075, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(int a = 1, int b = 2, int c = 3);\nf(10, 20) çağrısında c'nin değeri _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "c verilmediğinden varsayılan 3 kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1076, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b = 5, int _____);\nBu tanım derlenmez çünkü varsayılan değeri olmayan bir parametre, varsayılan değerli b'den sonra geliyor. Kuralı hatırlayarak, varsayılan değerli parametrelerin listenin neresinde olması gerektiğini (bir kelimeyle, İngilizce) yazın.",
        .acceptedAnswers = {"trailing"},
        .explanation = "Varsayılan değerli parametreler listenin sonunda (trailing) olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1077, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int f(int a = 1, int b = 2) {\n    return a + b;\n}\nint main() {\n    std::cout << f(5);\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"7"},
        .explanation = "a=5, b varsayılan 2 olduğundan 5+2=7.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1078, .topicId = 45,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int f(int a = 1, int b = 2) {\n    return a + b;\n}\nint main() {\n    std::cout << f();\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"3"},
        .explanation = "Her iki parametre de varsayılan değerini alır: 1+2=3.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1079, .topicId = 45,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\nint main() {\n    std::cout << selamla();\n    return 0;\n}\nstd::string selamla(std::string isim) {\n    return \"Merhaba \" + isim;\n}\nselamla fonksiyonunun isim parametresi için \"Dünya\" varsayılan değerini veren bildirimini (prototip olarak) yazın.",
        .acceptedAnswers = {"std::string selamla(std::string isim = \"Dünya\");"},
        .explanation = "Varsayılan değer, tanım veya bildirimde (burada bildirimde) belirtilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1080, .topicId = 45,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int carp(int a, int b = 2) {\n    return a * b;\n}\nint main() {\n    _____\n    return 0;\n}\ncarp fonksiyonunu tek argümanla (a=6) çağırıp sonucu ekrana yazdıran satırı tamamlayın.",
        .acceptedAnswers = {"std::cout << carp(6);"},
        .explanation = "b verilmezse varsayılan 2 kullanılır: 6*2=12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1081, .topicId = 45,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int f(int a, int b = 3) {\n    return a * b;\n}\nint main() {\n    std::cout << f(4);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "b varsayılan 3 kullanılır: 4*3=12.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1082, .topicId = 45,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a = 2, int b = 3) {\n    return a + b;\n}\nint main() {\n    std::cout << f() << f(10) << f(10, 20);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"51330"},
        .explanation = "f()=2+3=5, f(10)=10+3=13, f(10,20)=10+20=30; birlikte '51330' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1083, .topicId = 45,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid f(int a = 1, int b) {\n    std::cout << a + b;\n}\nint main() {\n    f(5, 6);\n    return 0;\n}\n\nBu kod derlenmez çünkü varsayılan değerli a parametresinden sonra varsayılansız b geliyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void f(int a, int b = 1) {"},
        .explanation = "Varsayılan değer, listenin sonundaki parametreye (b) taşınmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1084, .topicId = 45,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid f(int a = 1, int b = 2, int c) {\n    std::cout << a + b + c;\n}\nint main() {\n    f(1, 2, 3);\n    return 0;\n}\n\nBu kod derlenmez çünkü c, varsayılan değerli a ve b'den sonra varsayılansız kalmış. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void f(int c, int a = 1, int b = 2) {"},
        .explanation = "Varsayılansız parametre (c), varsayılan değerli parametrelerden önce gelmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1085, .topicId = 45,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid selamla(std::string isim, std::string mesaj = \"Merhaba\") {\n    std::cout << mesaj << \" \" << isim;\n}\nint main() {\n    selamla(mesaj);\n    return 0;\n}\n\nProgramcı main() içinde tanımsız bir mesaj değişkenini argüman olarak kullanmış; onun yerine sadece isim argümanını (\"Ali\") vererek çağırmalı. Düzeltilmiş çağrı satırını yazın.",
        .acceptedAnswers = {"selamla(\"Ali\");"},
        .explanation = "mesaj parametresi varsayılan değerli olduğundan çağrıda atlanabilir; sadece isim verilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1086, .topicId = 45,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, varsayılan parametreli bir fonksiyon kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"std::cout << topla(5);\n    return 0;\n}", "int topla(int a, int b = 10) {\n    return a + b;\n}", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Fonksiyon tanımı (2), main açılışı (3), çağrı ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1087, .topicId = 45,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "isim parametresi varsayılan olarak \"Misafir\" değerini alan bir selamla fonksiyonu yazın; main() içinde hem argümansız hem de \"Ayşe\" argümanıyla çağırın.",
        .acceptedAnswers = {"std::string", "=", "cout"},
        .explanation = "Fonksiyon varsayılan parametreli tanımlanmalı ve iki farklı şekilde çağrılmalıdır.",
        .baseXp = 40,
    });

    // Topic 46: Fonksiyon aşırı yükleme
    questions.push_back(Question{
        .id = 1088, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Aynı isimli birden fazla fonksiyonun farklı parametre listeleriyle tanımlanmasına ne denir?",
        .options = {"Fonksiyon aşırı yükleme (overloading)", "Fonksiyon devralma (inheritance)", "Fonksiyon gizleme (hiding)", "Fonksiyon şablonu (template)"},
        .acceptedAnswers = {"a"},
        .explanation = "Aynı isimli, farklı parametre listeli fonksiyonlara aşırı yükleme (overloading) denir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1089, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "İki fonksiyonun overload sayılabilmesi için ne farklı olmalıdır?",
        .options = {"Parametre listesi (tür ve/veya sayı)", "Sadece dönüş türü", "Sadece fonksiyon gövdesi", "Sadece yorum satırları"},
        .acceptedAnswers = {"a"},
        .explanation = "Overload, parametre listesinin (tür ve/veya sayısının) farklılığıyla belirlenir; dönüş türü tek başına yeterli değildir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1090, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int f(int a);\ndouble f(int a);\nBu iki bildirim aynı dosyada bulunursa ne olur?",
        .options = {"Derleme hatası (aynı parametre listesiyle yeniden tanım)", "Geçerli bir overload olur", "İkincisi birinciyi sessizce geçersiz kılar", "Sadece bir uyarı verir, çalışır"},
        .acceptedAnswers = {"a"},
        .explanation = "Parametre listeleri aynı olduğundan, sadece dönüş türü farklı olması overload için yetersizdir; bu bir yeniden tanım hatasıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1091, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void yazdir(int x);\nvoid yazdir(double x);\nBu iki fonksiyon geçerli bir overload çifti midir?",
        .options = {"Evet, parametre türleri farklı (int/double)", "Hayır, isimler aynı olduğundan hata verir", "Hayır, dönüş türleri aynı olduğundan hata verir", "Evet ama sadece biri çağrılabilir"},
        .acceptedAnswers = {"a"},
        .explanation = "Parametre türleri farklı olduğundan (int vs double) bu geçerli bir overload'dır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1092, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a);\nvoid f(int a, int b);\nBu iki fonksiyon geçerli bir overload çifti midir?",
        .options = {"Evet, parametre sayıları farklı (1 ve 2)", "Hayır, isimler aynı olduğundan hata verir", "Hayır, ikisi de int aldığından hata verir", "Evet ama ikincisi hiç çağrılamaz"},
        .acceptedAnswers = {"a"},
        .explanation = "Parametre sayısı farklı olduğundan (1 ve 2) bu geçerli bir overload'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1093, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a);\nvoid f(double a);\nint main() {\n    f(3.5);\n}\nHangi f çağrılır?",
        .options = {"f(double a) — argüman zaten double", "f(int a) — int'e yuvarlanır", "İkisi birden çağrılır", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "3.5 bir double literal olduğundan, tam eşleşen f(double) overload'ı seçilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1094, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int f(int a, int b);\ndouble f(int a, int b);\nBu iki bildirim neden derleme hatasıdır?",
        .options = {"Parametre listeleri aynı; sadece dönüş türü farklı, bu overload için yetersiz", "int ve double aynı fonksiyonda kullanılamaz", "Fonksiyonlar en fazla bir kez tanımlanabilir", "b parametresi geçersizdir"},
        .acceptedAnswers = {"a"},
        .explanation = "Overload çözümlemesi dönüş türüne bakmaz; parametre listesi aynı olduğundan bu geçerli bir overload değil, yeniden tanım hatasıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1095, .topicId = 46,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int a, int b);\nvoid f(int a, double b);\nint main() {\n    f(1, 2);\n}\nHangi f çağrılır?",
        .options = {"f(int, int) — her iki argüman da tam sayı, tam eşleşme", "f(int, double) — ikinci argüman double'a çevrilir", "Belirsizlik hatası (ambiguous)", "Derleme hatası, hiçbiri eşleşmez"},
        .acceptedAnswers = {"a"},
        .explanation = "f(1, 2) çağrısında her iki argüman da int olduğundan, f(int,int) overload'ı tam eşleşme sağlar ve belirsizlik olmadan çağrılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1096, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Fonksiyon overloading, aynı isimli fonksiyonların farklı parametre listeleriyle tanımlanmasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: overload, parametre listesi farklılığına dayanır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1097, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Sadece dönüş türü farklı olan iki fonksiyon, geçerli bir overload çifti oluşturur.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: overload çözümlemesi dönüş türüne bakmaz, parametre listesi aynıysa bu bir yeniden tanım hatasıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1098, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int f(int a); ve int f(double a); geçerli bir overload çiftidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: parametre türleri farklı (int/double).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1099, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Overload çözümlemesi, çağrıdaki argüman sayısı ve türlerine bakarak hangi fonksiyonun çağrılacağını belirler.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: derleyici, argümanların sayı ve türüne göre en uygun overload'ı seçer.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1100, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a); ve int f(int a); (parametre listeleri aynı, dönüş türleri farklı) aynı dosyada birlikte derlenir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: parametre listeleri aynı olduğundan, sadece dönüş türü farkı overload sağlamaz; derleme hatası oluşur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1101, .topicId = 46,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b); ve void f(int a, int b, int c); geçerli bir overload çiftidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: parametre sayıları farklı (2 ve 3).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1102, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Aynı isimli fonksiyonların farklı parametre listeleriyle birden fazla kez tanımlanmasına fonksiyon _____ denir (İngilizce terim).",
        .acceptedAnswers = {"overloading", "overload"},
        .explanation = "Bu kavrama overloading (aşırı yükleme) denir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1103, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Overload olabilmek için fonksiyonların _____ listesi farklı olmalıdır (dönüş türü değil).",
        .acceptedAnswers = {"parametre"},
        .explanation = "Overload çözümlemesi parametre listesine bakar, dönüş türüne bakmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1104, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int f(int a);\ndouble f(int a);\nBu iki bildirim aynı dosyada olursa derleyici bunu geçerli bir overload olarak KABUL ETMEZ, çünkü sadece _____ türü farklıdır (parametre listesi aynıdır).",
        .acceptedAnswers = {"dönüş"},
        .explanation = "Sadece dönüş türü farkı, overload için yeterli değildir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1105, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a, int b);\nvoid f(int a, double b);\nint main() {\n    f(1, 2);\n}\nBu çağrıda f(int, _____) overload'ı çağrılır çünkü her iki argüman da tam sayıdır.",
        .acceptedAnswers = {"int"},
        .explanation = "f(1,2) çağrısında iki argüman da int olduğundan tam eşleşen f(int,int) seçilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1106, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir(int x);\nvoid yazdir(std::string x);\nyazdir(\"Merhaba\") çağrısı yazdir(_____) overload'ını çağırır.",
        .acceptedAnswers = {"std::string"},
        .explanation = "\"Merhaba\" bir string literal olduğundan std::string overload'ı çağrılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1107, .topicId = 46,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void yazdir(int x) {\n    std::cout << \"int: \" << x;\n}\n_____\nvoid yazdir(double x) {\n    std::cout << \"double: \" << x;\n}\nyazdir fonksiyonunun int yerine double parametre alan overload'unun bildirimini (tanım satırının başlığını) yazın.",
        .acceptedAnswers = {"void yazdir(double x) {"},
        .explanation = "Overload, farklı parametre türüyle (double) tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1108, .topicId = 46,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int topla(int a, int b) {\n    return a + b;\n}\n_____\nint main() {\n    std::cout << topla(1, 2, 3);\n    return 0;\n}\ntopla fonksiyonunun üç int parametre alan overload'unun tanımını yazın (a+b+c döndürsün).",
        .acceptedAnswers = {"int topla(int a, int b, int c) { return a + b + c; }"},
        .explanation = "Parametre sayısı farklı olduğundan bu geçerli bir overload'dır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1109, .topicId = 46,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void f(int a) {\n    std::cout << \"int\";\n}\nvoid f(double a) {\n    std::cout << \"double\";\n}\nint main() {\n    f(5);\n    f(5.5);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"intdouble"},
        .explanation = "f(5) int overload'ını, f(5.5) double overload'ını çağırır: 'intdouble'.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1110, .topicId = 46,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void f(int a, int b) {\n    std::cout << \"iki\";\n}\nvoid f(int a, int b, int c) {\n    std::cout << \"uc\";\n}\nint main() {\n    f(1, 2);\n    f(1, 2, 3);\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"ikiuc"},
        .explanation = "f(1,2) iki parametreli overload'ı, f(1,2,3) üç parametreli overload'ı çağırır: 'ikiuc'.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1111, .topicId = 46,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint f(int a) {\n    return a;\n}\ndouble f(int a) {\n    return a;\n}\nint main() {\n    std::cout << f(5);\n    return 0;\n}\n\nBu kod derlenmez çünkü iki f fonksiyonu aynı parametre listesine (int a) sahip, sadece dönüş türleri farklı. Hatalı ikinci fonksiyon tanımının başlığını, geçerli bir overload olacak şekilde (bir int parametre daha ekleyerek) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"double f(int a, int b) {"},
        .explanation = "Parametre listesi farklılaştırılarak (ikinci bir int parametre eklenerek) geçerli bir overload elde edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1112, .topicId = 46,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nvoid yazdir(int x) {\n    std::cout << x;\n}\nvoid yazdir(int y) {\n    std::cout << y;\n}\nint main() {\n    yazdir(5);\n    return 0;\n}\n\nBu kod derlenmez çünkü iki yazdir fonksiyonu tamamen aynı parametre listesine (int) sahip; parametre adının farklı olması (x/y) yeterli değildir. İkinci fonksiyonun başlığını, double parametre alacak şekilde düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void yazdir(double y) {"},
        .explanation = "Parametre adları değil, parametre TÜRLERİ overload'ı belirler; türü değiştirmek (double) geçerli bir overload sağlar.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1113, .topicId = 46,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint carp(int a, int b) {\n    return a * b;\n}\ndouble carp(int a, int b) {\n    return a * b;\n}\nint main() {\n    std::cout << carp(2, 3);\n    return 0;\n}\n\nİki carp fonksiyonu aynı parametre listesine sahip; ikincisi çift sayı (double) parametre alacak şekilde değiştirilmeli. Düzeltilmiş ikinci fonksiyonun başlığını yazın.",
        .acceptedAnswers = {"double carp(double a, double b) {"},
        .explanation = "Parametre türleri double yapılarak, int overload'dan farklı geçerli bir overload elde edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1114, .topicId = 46,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, overload edilmiş bir yazdir fonksiyonu kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"void yazdir(double x) {\n    std::cout << x;\n}", "yazdir(5);\n    yazdir(5.5);\n    return 0;\n}", "void yazdir(int x) {\n    std::cout << x;\n}\nint main() {"},
        .acceptedAnswers = {"1 3 2"},
        .explanation = "Her iki overload'ın da main()'den önce tanımlanmış olması gerekir ki çağrılar doğru overload'a gitsin: double overload (1), int overload + main açılışı (3), gövde ve kapanış (2): sıra 1 3 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1115, .topicId = 46,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void yazdir(int x);\nvoid yazdir(int x, int y);\nİlk fonksiyon 1, ikincisi 2 parametre aldığından, bunlar parametre _____ farklı olduğu için geçerli bir overload'dır (Türkçe kelime).",
        .acceptedAnswers = {"sayısı", "sayisi"},
        .explanation = "Parametre sayısının farklı olması (1 ve 2) overload için yeterlidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1116, .topicId = 46,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "topla adında biri iki int, diğeri iki double parametre alan iki overload fonksiyon yazın; main() içinde her ikisini de çağırıp sonuçlarını yazdırın.",
        .acceptedAnswers = {"int", "double", "return", "cout"},
        .explanation = "İki fonksiyon aynı isimle ama farklı parametre türleriyle (int/double) tanımlanmalı ve her ikisi de çağrılmalıdır.",
        .baseXp = 40,
    });

    // Topic 47: Değer ile parametre gönderme
    questions.push_back(Question{
        .id = 1117, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "Bir fonksiyona değer ile (by value) parametre gönderildiğinde ne olur?",
        .options = {"Argümanın bağımsız bir kopyası oluşturulur", "Argümanın kendisi doğrudan değiştirilir", "Argüman hiç kopyalanmadan referans olarak kullanılır", "Argüman bellekte silinir"},
        .acceptedAnswers = {"a"},
        .explanation = "Değer ile gönderimde parametre, argümanın bağımsız bir kopyasıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1118, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "void f(int x) {\n    x = 100;\n}\nint main() {\n    int a = 5;\n    f(a);\n    std::cout << a;\n}\nEkrana ne yazdırılır?",
        .options = {"5", "100", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "x, a'nın bir kopyasıdır; x'in değişmesi a'yı etkilemez, a hâlâ 5'tir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1119, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Değer ile parametre göndermenin en belirgin dezavantajı nedir?",
        .options = {"Büyük nesnelerde kopyalama maliyeti", "Fonksiyonun hiç çalışmaması", "Derleyicinin bunu desteklememesi", "Sadece int türü için çalışması"},
        .acceptedAnswers = {"a"},
        .explanation = "Kopyalama, büyük nesneler (ör. büyük string/vector) için performans maliyeti getirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1120, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "void kare(int x) {\n    x = x * x;\n}\nint main() {\n    int sayi = 4;\n    kare(sayi);\n    std::cout << sayi;\n}\nEkrana ne yazdırılır?",
        .options = {"4", "16", "0", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "kare fonksiyonu sayi'nin kopyasını değiştirir; orijinal sayi değişmez, 4 kalır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1121, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "void artir(int x) {\n    x++;\n}\nint main() {\n    int sayac = 10;\n    artir(sayac);\n    artir(sayac);\n    std::cout << sayac;\n}\nEkrana ne yazdırılır?",
        .options = {"10", "11", "12", "Derleme hatası"},
        .acceptedAnswers = {"a"},
        .explanation = "Her artir çağrısı sadece kendi kopyasını artırır; sayac hiç değişmeden 10 kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1122, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int f(int x) {\n    x += 5;\n    return x;\n}\nint main() {\n    int a = 10;\n    int b = f(a);\n    std::cout << a << \" \" << b;\n}\nEkrana ne yazdırılır?",
        .options = {"10 15", "15 15", "10 10", "15 10"},
        .acceptedAnswers = {"a"},
        .explanation = "a, f'ye kopyalanır ve fonksiyon içinde değişen kopya döndürülür (b=15); a orijinali değişmeden 10 kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1123, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "void f(int x, int y) {\n    x = x + y;\n    y = 0;\n}\nint main() {\n    int a = 3, b = 4;\n    f(a, b);\n    std::cout << a << \" \" << b;\n}\nEkrana ne yazdırılır?",
        .options = {"3 4", "7 0", "7 4", "3 0"},
        .acceptedAnswers = {"a"},
        .explanation = "x ve y, a ve b'nin kopyalarıdır; fonksiyon içindeki değişiklikler a ve b'yi etkilemez, ikisi de değişmeden kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1124, .topicId = 47,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Değer ile parametre gönderiminde, fonksiyon çağrılırken argüman için ne zaman kopyalama gerçekleşir?",
        .options = {"Fonksiyon çağrıldığı anda, parametre oluşturulurken", "Fonksiyon return yaptığında", "Program sonlandığında", "Hiçbir zaman, kopyalama olmaz"},
        .acceptedAnswers = {"a"},
        .explanation = "Kopyalama, çağrı anında parametrenin ilklendirilmesiyle gerçekleşir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1125, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Değer ile gönderilen bir parametre, çağıranın orijinal değişkeninin bir kopyasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: değer ile gönderim bağımsız bir kopya oluşturur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1126, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "Değer ile gönderilen bir parametrenin fonksiyon içinde değiştirilmesi, çağıranın orijinal değişkenini de değiştirir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: parametre bağımsız bir kopya olduğundan, orijinal değişken etkilenmez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1127, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "void f(int x) { x = 0; } int main() { int a = 5; f(a); } çağrısından sonra a hâlâ 5'tir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: x, a'nın kopyasıdır; x'in sıfırlanması a'yı etkilemez.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 1128, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Büyük bir std::string'i değer ile parametre olarak göndermek, referans ile göndermeye kıyasla daha fazla kopyalama maliyeti taşır.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: değer ile gönderim, tüm string içeriğini kopyalarken referans hiç kopyalamaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1129, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "void f(int x) { x++; } int main() { int a = 1; f(a); f(a); std::cout << a; } kodu ekrana 3 yazdırır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yanlış: her çağrı yalnızca kendi kopyasını artırır, a hiç değişmeden 1 kalır; ekrana 1 yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1130, .topicId = 47,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Değer ile parametre gönderimi, temel türler (int, double gibi) için genellikle ucuz bir kopyalama işlemidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Doğru: temel türlerin kopyalanması ucuzdur; maliyet asıl büyük nesnelerde (string, vector) belirginleşir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1131, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryEasy,
        .prompt = "Değer ile gönderimde, parametre argümanın bağımsız bir _____ olur.",
        .acceptedAnswers = {"kopyası", "kopyasi"},
        .explanation = "Değer ile gönderim, argümanın bağımsız bir kopyasını oluşturur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1132, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(int x) {\n    x = 50;\n}\nint main() {\n    int a = 5;\n    f(a);\n    std::cout << a;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5"},
        .explanation = "x bağımsız bir kopya olduğundan a değişmeden 5 kalır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1133, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int f(int x) {\n    return x * 2;\n}\nint main() {\n    int a = 5;\n    int b = f(a);\n    std::cout << a << \" \" << b;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"5 10"},
        .explanation = "a değişmez (5), b ise f'nin döndürdüğü değeri alır (10).",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1134, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Değer ile parametre gönderiminin en büyük maliyeti, büyük nesnelerde oluşan _____ (kopyalama) işlemidir (bir kelimeyle, Türkçe).",
        .acceptedAnswers = {"kopyalama"},
        .explanation = "Büyük nesnelerin kopyalanması işlem maliyeti getirir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1135, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "void degistir(int x) {\n    x = x + 100;\n}\nint main() {\n    int deger = 1;\n    degistir(deger);\n    std::cout << deger;\n}\nEkran çıktısı _____ olur.",
        .acceptedAnswers = {"1"},
        .explanation = "degistir, deger'in kopyasını değiştirir; orijinal deger değişmeden 1 kalır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1136, .topicId = 47,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "void sifirla(int x) {\n    _____\n}\nint main() {\n    int a = 5;\n    sifirla(a);\n    std::cout << a;\n    return 0;\n}\nsifirla fonksiyonunun gövdesini (x'i 0 yapan satırı) tamamlayın. (Not: değer ile gönderim olduğu için a yine de 5 kalacaktır.)",
        .acceptedAnswers = {"x = 0;"},
        .explanation = "x, a'nın bir kopyası olduğundan x=0 yapmak a'yı etkilemez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1137, .topicId = 47,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int ikiKatiniAl(int x) {\n    _____\n}\nint main() {\n    std::cout << ikiKatiniAl(7);\n    return 0;\n}\nikiKatiniAl fonksiyonunun x'in iki katını döndüren gövdesini tamamlayın.",
        .acceptedAnswers = {"return x * 2;"},
        .explanation = "Fonksiyon, parametrenin kopyasını iki katına çıkarıp döndürür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1138, .topicId = 47,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "void f(int x) {\n    x = x * 10;\n    std::cout << x << \" \";\n}\nint main() {\n    int a = 3;\n    f(a);\n    std::cout << a;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"30 3"},
        .explanation = "Fonksiyon içinde x=30 yazdırılır, ardından a hâlâ 3 olduğundan 3 yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1139, .topicId = 47,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "void f(int x) {\n    x++;\n}\nint main() {\n    int a = 1;\n    f(a);\n    f(a);\n    f(a);\n    std::cout << a;\n    return 0;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1"},
        .explanation = "Her f çağrısı yalnızca kendi kopyasını artırır; a hiçbir zaman değişmez, 1 kalır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1140, .topicId = 47,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nvoid ikiyeKatla(int x) {\n    x = x * 2;\n}\nint main() {\n    int sayi = 5;\n    ikiyeKatla(sayi);\n    std::cout << sayi;\n    return 0;\n}\n\nProgramcı sayi'nin 10 yazdırılmasını bekliyor ama değer ile gönderim yüzünden 5 yazdırılıyor. Fonksiyonun, çağıranın değişkenini gerçekten değiştirmesi için parametre bildirimini (referansa çevirerek) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void ikiyeKatla(int& x) {"},
        .explanation = "Çağılanın değişkenini değiştirmek için parametre referans (&) olmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1141, .topicId = 47,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda mantık hatası var (derleme hatası değil):\n\nvoid takasEt(int a, int b) {\n    int gecici = a;\n    a = b;\n    b = gecici;\n}\nint main() {\n    int x = 1, y = 2;\n    takasEt(x, y);\n    std::cout << x << \" \" << y;\n    return 0;\n}\n\nProgramcı x ve y'nin takas edilmesini bekliyor ama değer ile gönderim yüzünden ikisi de değişmeden kalıyor (1 2 yazdırılır). Fonksiyonun gerçekten takas yapması için parametre bildirimini (referansa çevirerek) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void takasEt(int& a, int& b) {"},
        .explanation = "Gerçek takas için parametrelerin referans (&) olması gerekir; değer ile gönderim sadece kopyaları takas eder.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1142, .topicId = 47,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nvoid birEkle(int sayi) {\n    sayi = sayi + 1;\n}\nint main() {\n    int deger = 9;\n    birEkle(deger);\n    std::cout << deger;\n    return 0;\n}\n\nProgramcı deger'in 10 olmasını bekliyor ama değer ile gönderim yüzünden 9 kalıyor. Fonksiyon başlığını, çağıranın değişkenini değiştirecek şekilde (referans parametreyle) düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"void birEkle(int& sayi) {"},
        .explanation = "Çağılanın değişkenini kalıcı olarak değiştirmek için parametre referans (&) olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 1143, .topicId = 47,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, değer ile parametre gönderilen bir fonksiyon kullanan geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"int a = 5;\n    f(a);\n    std::cout << a;\n    return 0;\n}", "void f(int x) {\n    x = 100;\n}", "int main() {"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Fonksiyon tanımı (2), main açılışı (3), gövde ve kapanış (1): sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 1144, .topicId = 47,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "void f(int x) {\n    x = x + 1;\n}\nDeğer ile gönderimde x, çağırandaki argümanın bir kopyası olduğundan, bu fonksiyonun çağırandaki değişken üzerinde hiçbir kalıcı _____ yoktur (bir kelimeyle, Türkçe).",
        .acceptedAnswers = {"etkisi"},
        .explanation = "Değer ile gönderim, çağırandaki orijinal değişkeni asla etkilemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 1145, .topicId = 47,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Bir sayının karesini değer ile parametre alarak hesaplayıp döndüren bir fonksiyon yazın; main() içinde çağırıp hem orijinal değişkeni hem de dönen sonucu yazdırarak orijinalin değişmediğini gösterin.",
        .acceptedAnswers = {"int", "return", "cout"},
        .explanation = "Fonksiyon parametreyi değer ile almalı, kareyi döndürmeli; orijinal değişken değişmemelidir.",
        .baseXp = 40,
    });
}

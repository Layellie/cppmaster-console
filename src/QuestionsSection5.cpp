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
        .prompt = "int f(int x); void main() { f(5); } int f(int x) { return x; } yapısında f'nin prototipi olmasaydı ne olurdu?",
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
}

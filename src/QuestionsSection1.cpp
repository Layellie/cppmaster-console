#include "QuestionContent.h"

#include "Question.h"

// Section 1 (topics 1-10) shipped with only 6-9 questions per topic, while
// every later section carries 29. Because topics unlock in order, this is
// the material a learner sees most, and the small pool meant a retake
// replayed nearly the same questions — so these additions are deliberately
// spread across different facts of each topic rather than restating the
// headline one, and lean slightly harder than the originals.
//
// Ids start at 2690, continuing after the Scenario/Matching block (2689).
// The original 73 questions stay in QuestionManager.cpp.
void appendSection1Questions(std::vector<Question>& questions) {
    // --- Topic 1: cout ---
    questions.push_back(Question{
        .id = 2690, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << 5 + 3; satırının ekran çıktısı nedir?",
        .options = {"5 + 3", "8", "53", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Tırnak içinde olmayan 5 + 3 ifadesi önce hesaplanır, sonra sonucu (8) yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2691, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"5 + 3\"; satırının ekran çıktısı nedir?",
        .options = {"8", "5 + 3", "53", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Çift tırnak içindeki her şey metin olarak, olduğu gibi yazdırılır; hesaplama yapılmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2692, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "Programın başına using namespace std; yazılırsa cout nasıl kullanılır?",
        .options = {"std::cout", "cout", "using cout", "namespace::cout"},
        .acceptedAnswers = {"b"},
        .explanation = "using namespace std; yazıldığında std:: öneki gerekmez, doğrudan cout yazılabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2693, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::cout << \"A\" << \"B\"; satırının ekran çıktısı nedir?",
        .options = {"A B", "AB", "Önce A, alt satırda B", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "<< operatörü art arda kullanılabilir; değerler aralarında boşluk olmadan yan yana yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2694, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout ile birlikte kullanıldığında << operatörünün görevi nedir?",
        .options = {
            "İki sayıyı çarpar",
            "Soldaki çıktı akışına sağdaki veriyi ekler",
            "Değişkene değer atar",
            "İki değeri karşılaştırır",
        },
        .acceptedAnswers = {"b"},
        .explanation = "cout ile kullanıldığında << akışa ekleme operatörüdür; sağındaki veriyi çıktı akışına gönderir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2695, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "bool durum = true;\nstd::cout << durum;\nYukarıdaki kodun ekran çıktısı nedir?",
        .options = {"true", "1", "evet", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "bool değerler varsayılan olarak sayıya çevrilerek yazdırılır: true için 1, false için 0.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2696, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cout, yazdırma işleminden sonra otomatik olarak alt satıra geçer.",
        .acceptedAnswers = {"2"},
        .explanation = "cout kendiliğinden satır atlamaz; alt satıra geçmek için \\n veya std::endl eklenmelidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2697, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cout ile ondalıklı (double) sayılar da yazdırılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "cout sayı, metin, karakter ve mantıksal değerler dahil pek çok türü yazdırabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2698, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Tek bir cout satırında birden fazla değer yazdırılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "<< operatörü zincirlenebilir: std::cout << a << \" \" << b; tek satırda birden fazla değer yazdırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2699, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "cout kullanabilmek için programda mutlaka using namespace std; satırı bulunmalıdır.",
        .acceptedAnswers = {"2"},
        .explanation = "Zorunlu değildir; std::cout şeklinde tam adıyla yazmak da geçerlidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2700, .topicId = 1,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "İki metni tek satırda yazdırmak için boşluğa hangi operatör gelmeli?\n\nstd::cout << \"Merhaba\" _____ \"Dunya\";",
        .acceptedAnswers = {"<<"},
        .explanation = "Her yeni değer, akışa yine << operatörüyle eklenir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2701, .topicId = 1,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "char harf = 'A';\nstd::cout << _____;\nDeğişkenin değerini yazdırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"harf"},
        .explanation = "Değişkenin değerini yazdırmak için adı tırnaksız yazılır; tırnak içinde yazılsaydı 'harf' kelimesi basılırdı.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2702, .topicId = 1,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Ekrana yazdırılacak metinler _____ tırnak içine alınır. (tek / çift)",
        .acceptedAnswers = {"çift", "cift"},
        .explanation = "Metinler (string) çift tırnak, tek karakterler (char) tek tırnak içine yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2703, .topicId = 1,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 20;\nstd::cout << _____;\nEkrana 20 yazdırmak için boşluğa ne gelmeli?",
        .acceptedAnswers = {"yas"},
        .explanation = "Değişken adı tırnaksız yazıldığında içindeki değer (20) yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2704, .topicId = 1,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "int a = 3, b = 4;\nstd::cout << \"Toplam: \" << _____;\nEkrana \"Toplam: 7\" yazdıran kodu tamamlayın.",
        .acceptedAnswers = {"a + b", "a+b"},
        .explanation = "Toplama ifadesi akışa eklendiğinde önce hesaplanır, sonra sonucu yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2705, .topicId = 1,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::cout << 7 / 2;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "İki tam sayının bölümü yine tam sayıdır; ondalık kısım atılır, 3.5 değil 3 yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2706, .topicId = 1,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"Ali\" << 5;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Ali5"},
        .explanation = "Metin ve sayı aralarında boşluk bırakılmadan art arda yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2707, .topicId = 1,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int x = 4;\nstd::cout << x << x;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"44"},
        .explanation = "Aynı değişken iki kez akışa eklendiği için değeri iki kez yan yana yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2708, .topicId = 1,
        .type = QuestionType::FindError, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::cout << \"Merhaba\"\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << \"Merhaba\";"},
        .explanation = "C++'ta her deyim noktalı virgülle biter; eksik noktalı virgül derleme hatası verir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2709, .topicId = 1,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::cout >> \"Merhaba\";\n\nDüzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::cout << \"Merhaba\";"},
        .explanation = ">> operatörü okuma (cin) için kullanılır; ekrana yazdırırken << kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2710, .topicId = 1,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Medium,
        .prompt = "Ekrana kendi adınızı yazdıran bir program yazın.",
        .acceptedAnswers = {"cout", "<<"},
        .explanation = "std::cout << \"Ad\"; şeklinde bir satır yeterlidir; << ile metin çıktı akışına eklenir.",
        .baseXp = 20,
    });

    // --- Topic 2: \n ---
    questions.push_back(Question{
        .id = 2711, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "\\t kaçış dizisi ne işe yarar?",
        .options = {"Yeni satıra geçer", "Yatay sekme (tab) boşluğu ekler", "Metni siler", "Programı durdurur"},
        .acceptedAnswers = {"b"},
        .explanation = "\\t sekme karakteridir; çıktıda hizalama amacıyla boşluk bırakır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2712, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Ekrana tek bir ters slash (\\) yazdırmak için metin içinde ne yazılmalıdır?",
        .options = {"\\", "\\\\", "//", "/\\"},
        .acceptedAnswers = {"b"},
        .explanation = "Ters slash kaçış karakteri olduğu için, kendisini yazdırmak isteyince iki kez yazılır: \\\\",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2713, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::cout << \"A\\nB\\nC\"; satırı ekranda kaç satır oluşturur?",
        .options = {"1", "2", "3", "4"},
        .acceptedAnswers = {"c"},
        .explanation = "İki adet \\n, metni üç parçaya bölerek üç satır oluşturur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2714, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "'\\n' ifadesi (tek tırnak içinde) hangi türdendir?",
        .options = {"std::string", "char", "int", "bool"},
        .acceptedAnswers = {"b"},
        .explanation = "Tek tırnak içindeki kaçış dizisi tek bir karakteri temsil eder; türü char'dır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2715, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir metnin içinde çift tırnak karakteri yazdırmak için ne kullanılır?",
        .options = {"\"\"", "\\\"", "''", "\\'"},
        .acceptedAnswers = {"b"},
        .explanation = "Çift tırnak metni bitirdiği için, karakter olarak yazdırmak isteyince önüne ters slash konur: \\\"",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2716, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "\"\\n\" ifadesi bellekte kaç karakter yer kaplar?",
        .options = {"1", "2", "3", "Değişkendir"},
        .acceptedAnswers = {"a"},
        .explanation = "Kaynak kodda iki simgeyle (\\ ve n) yazılsa da tek bir satır sonu karakterini temsil eder.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2717, .topicId = 2,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdakilerden hangisi geçerli bir kaçış dizisi DEĞİLDİR?",
        .options = {"\\n", "\\t", "\\q", "\\\\"},
        .acceptedAnswers = {"c"},
        .explanation = "\\q tanımlı bir kaçış dizisi değildir; \\n satır sonu, \\t sekme, \\\\ ters slash anlamına gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2718, .topicId = 2,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "\\n ifadesi bellekte iki ayrı karakter olarak saklanır.",
        .acceptedAnswers = {"2"},
        .explanation = "Kaynak kodda iki simge yazılır ama tek bir satır sonu karakterine karşılık gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2719, .topicId = 2,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "'\\n' şeklinde tek tırnak içinde de kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Tek karakter olduğu için char değişkenlerde ve tek tırnak içinde kullanılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2720, .topicId = 2,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "/n ifadesi de \\n gibi alt satıra geçirir.",
        .acceptedAnswers = {"2"},
        .explanation = "Kaçış dizileri ters slash (\\) ile başlar; /n sadece iki normal karakter olarak yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2721, .topicId = 2,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "\\n, alt satıra geçmenin yanında çıktı tamponunu da boşaltır.",
        .acceptedAnswers = {"2"},
        .explanation = "Tamponu boşaltan std::endl'dir; \\n yalnızca satır sonu karakterini ekler.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2722, .topicId = 2,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir metin içinde birden fazla \\n kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "İstenildiği kadar kullanılabilir; her biri yeni bir satır başlatır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2723, .topicId = 2,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "Çıktıda sekme (tab) boşluğu bırakan kaçış dizisi: _____",
        .acceptedAnswers = {"\\t"},
        .explanation = "\\t yatay sekme karakteridir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2724, .topicId = 2,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Ekrana tek bir ters slash yazdırmak için metin içine yazılması gereken ifade: _____",
        .acceptedAnswers = {"\\\\"},
        .explanation = "İki ters slash, çıktıda tek bir ters slash olarak görünür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2725, .topicId = 2,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"Satir1_____Satir2\";\nİki kelimenin alt alta yazılması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"\\n"},
        .explanation = "\\n, kendisinden sonrasını yeni satıra taşır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2726, .topicId = 2,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Hard,
        .prompt = "char yeniSatir = '_____';\nSatır sonu karakterini tutan bir char tanımlamak için boşluğa ne gelmeli?",
        .acceptedAnswers = {"\\n"},
        .explanation = "Satır sonu tek bir karakter olduğu için char değişkende tek tırnakla saklanabilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2727, .topicId = 2,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"A\" << _____ << \"B\";\nA ve B'nin alt alta yazılması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"\"\\n\""},
        .explanation = "Satır sonu, ayrı bir metin olarak da akışa eklenebilir: << \"\\n\"",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2728, .topicId = 2,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "std::cout << \"Ad_____Soyad\";\nÇıktıda Ad ve Soyad arasında sekme boşluğu olması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"\\t"},
        .explanation = "\\t sekme karakteriyle iki değer arasında hizalı boşluk bırakılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2729, .topicId = 2,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::cout << \"Hata\\\\Uyari\";\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"Hata\\Uyari"},
        .explanation = "İki ters slash, çıktıda tek bir ters slash olarak görünür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2730, .topicId = 2,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::VeryHard,
        .prompt = "std::cout << \"C++\\\\n\";\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"C++\\n"},
        .explanation = "\\\\ tek ters slash üretir, ardından gelen n normal bir harftir; bu yüzden satır atlanmaz, ekrana C++\\n yazılır.",
        .baseXp = 40,
    });
    questions.push_back(Question{
        .id = 2731, .topicId = 2,
        .type = QuestionType::FindError, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::cout << \"Merhaba/n\";\n\nAmaç alt satıra geçmek. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << \"Merhaba\\n\";"},
        .explanation = "Kaçış dizisi ters slash ile yazılır: \\n. Düz slash (/n) sıradan iki karakterdir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2732, .topicId = 2,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::cout << \"Satir1\" \\n \"Satir2\";\n\nDüzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::cout << \"Satir1\\nSatir2\";"},
        .explanation = "\\n bir metnin içinde yer almalıdır; tırnakların dışında tek başına yazılamaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2733, .topicId = 2,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, ekrana önce adı sonra alt satırda soyadı yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın, örnek: 1 2 3):",
        .options = {"std::cout << \"Soyad\";", "#include <iostream>", "std::cout << \"Ad\\n\";"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Önce kütüphane eklenir, sonra ad ve satır sonu, en son soyad yazdırılır: sıra 2 3 1.",
        .baseXp = 20,
    });

    // --- Topic 3: endl ---
    questions.push_back(Question{
        .id = 2734, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::endl aslında nedir?",
        .options = {
            "Bir metin (string) sabiti",
            "Akışa uygulanan bir manipülatör (fonksiyon)",
            "Bir tam sayı değişkeni",
            "Bir anahtar kelime",
        },
        .acceptedAnswers = {"b"},
        .explanation = "endl, akışa uygulandığında satır sonu ekleyip tamponu boşaltan bir manipülatördür; metin değildir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2735, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"endl\"; satırı ne yapar?",
        .options = {
            "Alt satıra geçer",
            "Ekrana endl yazısını yazdırır",
            "Derleme hatası verir",
            "Tamponu boşaltır",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Tırnak içine alındığında endl bir manipülatör değil sıradan bir metindir ve olduğu gibi yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2736, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Çok sayıda satır yazdıran bir döngüde hangisi genellikle daha hızlıdır?",
        .options = {"std::endl", "\\n", "İkisi de aynıdır", "Duruma göre endl daha hızlıdır"},
        .acceptedAnswers = {"b"},
        .explanation = "endl her seferinde tamponu boşalttığı için ek maliyet getirir; \\n yalnızca karakter ekler.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2737, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::endl hangi kütüphanede tanımlıdır?",
        .options = {"<string>", "<iostream>", "<vector>", "<cmath>"},
        .acceptedAnswers = {"b"},
        .explanation = "cout gibi endl de <iostream> kütüphanesinde tanımlıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2738, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "\"Tamponu boşaltmak (flush)\" ne anlama gelir?",
        .options = {
            "Ekranı temizler",
            "Bekleyen çıktının hemen ekrana yazılmasını sağlar",
            "Değişkenleri sıfırlar",
            "Programı sonlandırır",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Çıktı önce bir tamponda birikir; flush işlemi birikeni hemen hedefe (ekrana) gönderir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2739, .topicId = 3,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"A\" << std::endl << \"B\"; kodu ekranda ne oluşturur?",
        .options = {"Tek satırda AB", "A ve altında B", "Sadece A", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "endl araya satır sonu koyduğu için B bir alt satıra yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2740, .topicId = 3,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::endl kullanmak için <iostream> kütüphanesi yeterlidir.",
        .acceptedAnswers = {"1"},
        .explanation = "endl de cout gibi <iostream> içinde tanımlıdır; ek bir kütüphane gerekmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2741, .topicId = 3,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::endl tırnak içine alınarak kullanılır: std::cout << \"std::endl\";",
        .acceptedAnswers = {"2"},
        .explanation = "Tırnak içine alınırsa metin olarak yazdırılır; manipülatör olarak çalışması için tırnaksız yazılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2742, .topicId = 3,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir cout satırında birden fazla std::endl kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Her endl bir satır sonu ekler; art arda kullanılırsa boş satırlar oluşur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2743, .topicId = 3,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "std::endl ile \\n arasındaki tek fark, endl'in tamponu da boşaltmasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "Görünen çıktı aynıdır; fark tampon boşaltma davranışı ve dolayısıyla performanstır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2744, .topicId = 3,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::endl bir değişkendir ve içine değer atanabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "endl bir manipülatördür (fonksiyondur); değer atanabilen bir değişken değildir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2745, .topicId = 3,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::cout << \"Merhaba\" << std::_____;\nSatırı bitirip tamponu boşaltmak için boşluğa ne gelmeli?",
        .acceptedAnswers = {"endl"},
        .explanation = "std::endl satır sonu ekler ve çıktı tamponunu boşaltır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2746, .topicId = 3,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "endl'in yaptığı iki işten biri satır sonu eklemek, diğeri _____ boşaltmaktır.",
        .acceptedAnswers = {"tamponu", "tampon", "buffer"},
        .explanation = "endl hem satırı bitirir hem de çıktı tamponunu boşaltır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2747, .topicId = 3,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Hard,
        .prompt = "using namespace std; yazılmadığında endl'in başına _____ öneki gelmelidir.",
        .acceptedAnswers = {"std::", "std"},
        .explanation = "endl std isim alanında tanımlıdır; using olmadan std::endl şeklinde yazılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2748, .topicId = 3,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << \"Satir1\" << std::endl << \"Satir2\" << _____;\nSon satırdan sonra da alt satıra geçmek için boşluğa ne gelmeli?",
        .acceptedAnswers = {"std::endl"},
        .explanation = "Son değerden sonra bir endl daha eklenirse imleç yeni satıra iner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2749, .topicId = 3,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "int sayi = 42;\nstd::cout << sayi << _____;\nDeğeri yazdırdıktan sonra satırı bitirip tamponu boşaltmak için boşluğa ne gelmeli?",
        .acceptedAnswers = {"std::endl"},
        .explanation = "Değerden sonra std::endl eklenince satır biter ve tampon boşaltılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2750, .topicId = 3,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "std::cout << 2 << std::endl << 3;\nYukarıdaki kodun ilk satırındaki çıktı nedir?",
        .acceptedAnswers = {"2"},
        .explanation = "endl'den önceki değer ilk satırı oluşturur; 3 bir alt satıra yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2751, .topicId = 3,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::cout << \"endl\" << 5;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"endl5"},
        .explanation = "Tırnak içindeki endl metin olarak yazdırılır, ardından 5 eklenir; satır atlanmaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2752, .topicId = 3,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::cout << \"Merhaba\" << endl;\n\nusing namespace std; satırı YOK. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << \"Merhaba\" << std::endl;"},
        .explanation = "using namespace std; yoksa endl de std:: önekiyle yazılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2753, .topicId = 3,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nstd::cout << \"Merhaba\" << \"std::endl\";\n\nAmaç gerçekten alt satıra geçmek. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::cout << \"Merhaba\" << std::endl;"},
        .explanation = "Tırnaklar kaldırılmalıdır; aksi halde endl metin olarak yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2754, .topicId = 3,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, ekrana iki değeri alt alta yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın, örnek: 1 2 3):",
        .options = {"std::cout << b << std::endl;", "int a = 1, b = 2;", "std::cout << a << std::endl;"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Önce değişkenler tanımlanır, sonra sırasıyla a ve b yazdırılır: sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2755, .topicId = 3,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Medium,
        .prompt = "Ekrana iki farklı kelimeyi alt alta yazdıran bir program yazın (satır sonu için std::endl kullanın).",
        .acceptedAnswers = {"cout", "<<", "endl"},
        .explanation = "İki cout satırı ya da tek satırda << std::endl << kullanımı yeterlidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2756, .topicId = 3,
        .type = QuestionType::Scenario, .difficulty = Difficulty::Hard,
        .prompt = "Uzun süren bir hesaplama sırasında ilerleme mesajları yazdıran bir program yazdın, ama mesajlar ekranda tek tek değil ancak program bitince toplu halde beliriyor. Bunu düzeltmek için ne yapmalısın?",
        .options = {
            "Mesaj sayısını azaltmak",
            "Satır sonlarında std::endl kullanmak",
            "cout yerine cin kullanmak",
            "Her mesajı tırnak içine almak",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Çıktı önce tamponda birikir; std::endl her satırda tamponu boşalttığı için mesajlar anında görünür.",
        .baseXp = 30,
    });

    // --- Topic 4: cin ---
    questions.push_back(Question{
        .id = 2757, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "cin ile veri okurken hangi operatör kullanılır?",
        .options = {"<<", ">>", "->", "=="},
        .acceptedAnswers = {"b"},
        .explanation = "cin ile okuma yapılırken >> (akıştan çıkarma) operatörü kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2758, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::string ad;\nstd::cin >> ad;\nKullanıcı \"Ali Veli\" yazıp Enter'a basarsa ad değişkeninde ne olur?",
        .options = {"Ali Veli", "Ali", "Veli", "Boş kalır"},
        .acceptedAnswers = {"b"},
        .explanation = "cin >> ilk boşluğa kadar okur; \"Veli\" akışta bekler. Tüm satırı almak için std::getline gerekir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2759, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "İki sayıyı okumak için aşağıdakilerden hangisi doğrudur?",
        .options = {
            "std::cin >> a, b;",
            "std::cin >> a >> b;",
            "std::cin << a << b;",
            "std::cin.read(a, b);",
        },
        .acceptedAnswers = {"b"},
        .explanation = ">> operatörü zincirlenebilir; her değişken için tekrar yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2760, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int sayi;\nstd::cin >> sayi;\nKullanıcı sayı yerine \"abc\" yazarsa ne olur?",
        .options = {
            "sayi 0 olur ve program sorunsuz devam eder",
            "Okuma başarısız olur ve cin hata durumuna geçer",
            "Program çöker",
            "Derleme hatası oluşur",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Tür uyuşmadığında akış fail durumuna geçer; temizlenmeden yapılan sonraki okumalar da çalışmaz.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2761, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "cin hangi kütüphanede tanımlıdır?",
        .options = {"<string>", "<iostream>", "<fstream>", "<vector>"},
        .acceptedAnswers = {"b"},
        .explanation = "cin de cout gibi <iostream> kütüphanesinde tanımlıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2762, .topicId = 4,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "cin >> ile okuma yapılırken girdinin başındaki boşluklara ne olur?",
        .options = {
            "Hata verir",
            "Atlanır, ilk anlamlı veriden itibaren okunur",
            "Değişkene boşluk olarak yazılır",
            "Program durur",
        },
        .acceptedAnswers = {"b"},
        .explanation = ">> operatörü baştaki boşluk ve satır sonlarını atlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2763, .topicId = 4,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cin ile okunacak değişkenin önceden tanımlanmış olması gerekir.",
        .acceptedAnswers = {"1"},
        .explanation = "Okunan değer bir değişkene yazılır; o değişken önce tanımlanmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2764, .topicId = 4,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "std::cin >> ad; ifadesi boşluk içeren tam bir cümleyi okuyabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "cin >> ilk boşlukta durur; boşluklu metin için std::getline kullanılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2765, .topicId = 4,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "cin ve cout aynı programda birlikte kullanılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Genellikle birlikte kullanılır: cout ile soru sorulur, cin ile cevap okunur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2766, .topicId = 4,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "std::cin >> a >> b; yazıldığında kullanıcı iki değeri ayrı satırlara da girebilir.",
        .acceptedAnswers = {"1"},
        .explanation = ">> hem boşluğu hem satır sonunu ayırıcı sayar; iki değer aynı ya da ayrı satırlarda girilebilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2767, .topicId = 4,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "cin, okuduğu değerin türünü değişkenin türüne bakarak belirler.",
        .acceptedAnswers = {"1"},
        .explanation = "int bir değişkene okurken sayı, std::string bir değişkene okurken metin beklenir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2768, .topicId = 4,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int yas;\nstd::cin _____ yas;\nKlavyeden okuma yapmak için boşluğa hangi operatör gelmeli?",
        .acceptedAnswers = {">>"},
        .explanation = "cin ile okuma >> operatörüyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2769, .topicId = 4,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Klavyeden veri okumak için kullanılan standart giriş akışı: std::_____",
        .acceptedAnswers = {"cin"},
        .explanation = "std::cin standart giriş akışıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2770, .topicId = 4,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Hard,
        .prompt = "double fiyat;\nstd::cin >> _____;\nOkunan değerin fiyat değişkenine yazılması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"fiyat"},
        .explanation = "Okunan değerin yazılacağı değişkenin adı yazılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2771, .topicId = 4,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a, b;\nstd::cin >> a _____ b;\nİki sayıyı okumak için boşluğa ne gelmeli?",
        .acceptedAnswers = {">>"},
        .explanation = "Her yeni değişken için >> operatörü tekrarlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2772, .topicId = 4,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "int sayi;\nstd::cout << \"Sayi girin: \";\n_____;\nKullanıcıdan sayı okuyan satırı tamamlayın.",
        .acceptedAnswers = {"std::cin >> sayi"},
        .explanation = "Mesajdan sonra std::cin >> sayi; ile değer okunur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2773, .topicId = 4,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int a, b;\nstd::cin >> a >> b;\nstd::cout << a + b;\nKullanıcı \"3 4\" yazarsa ekran çıktısı nedir?",
        .acceptedAnswers = {"7"},
        .explanation = "a = 3 ve b = 4 okunur, toplamları 7 yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2774, .topicId = 4,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::VeryHard,
        .prompt = "int sayi;\nstd::cin >> sayi;\nstd::cout << sayi * 2;\nKullanıcı \"5 9\" yazarsa ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "Tek okuma yapıldığı için yalnızca 5 alınır, 9 akışta kalır: 5 * 2 = 10.",
        .baseXp = 40,
    });
    questions.push_back(Question{
        .id = 2775, .topicId = 4,
        .type = QuestionType::FindError, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint yas;\nstd::cin << yas;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cin >> yas;"},
        .explanation = "cin ile okuma yapılırken << değil >> operatörü kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2776, .topicId = 4,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda yas değişkeni hiç tanımlanmamış:\n\nstd::cin >> yas;\n\nEksik olan tanım satırını yazın (tam sayı olacak).",
        .acceptedAnswers = {"int yas;"},
        .explanation = "Okuma yapılmadan önce değişken tanımlanmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2777, .topicId = 4,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, kullanıcıdan bir sayı alıp iki katını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın, örnek: 1 2 3):",
        .options = {"std::cin >> sayi;", "std::cout << sayi * 2;", "int sayi;"},
        .acceptedAnswers = {"3 1 2"},
        .explanation = "Önce değişken tanımlanır, sonra okunur, en son sonuç yazdırılır: sıra 3 1 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2778, .topicId = 4,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan iki tam sayı okuyup toplamlarını ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "cout", "<<", "+"},
        .explanation = "İki değer cin >> ile okunur, + ile toplanır ve cout << ile yazdırılır.",
        .baseXp = 40,
    });

    // --- Topic 5: getline() ---
    questions.push_back(Question{
        .id = 2779, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "std::getline'ın cin >> ile karşılaştırıldığında temel farkı nedir?",
        .options = {
            "Sadece sayı okur",
            "Boşluklar dahil satırın tamamını okur",
            "Daha hızlıdır",
            "Ekrana yazdırır",
        },
        .acceptedAnswers = {"b"},
        .explanation = "getline satır sonuna kadar okur; boşluklar okumayı kesmez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2780, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::getline doğru kullanımı hangisidir?",
        .options = {
            "std::getline(ad);",
            "std::getline(std::cin, ad);",
            "std::cin.getline(ad);",
            "ad = std::getline();",
        },
        .acceptedAnswers = {"b"},
        .explanation = "getline iki argüman alır: okunacak akış ve sonucun yazılacağı string.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2781, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "std::getline ile std::string kullanabilmek için hangi kütüphane gerekir?",
        .options = {"<vector>", "<string>", "<cmath>", "<array>"},
        .acceptedAnswers = {"b"},
        .explanation = "std::string ve onunla çalışan getline aşırı yüklemesi <string> kütüphanesinde tanımlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2782, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "getline okuduğu satırın sonundaki Enter (satır sonu) karakterini ne yapar?",
        .options = {
            "String'in sonuna ekler",
            "Akıştan siler ama string'e eklemez",
            "Akışta bırakır",
            "Boşluğa çevirir",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Satır sonu karakteri okunup atılır; string'e dahil edilmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2783, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryHard,
        .prompt = "int yas;\nstd::string ad;\nstd::cin >> yas;\nstd::getline(std::cin, ad);\nBu kodda getline neden boş bir satır okur?",
        .options = {
            "getline sayıdan sonra çalışmaz",
            "cin >> sonrası akışta kalan satır sonu karakterini getline hemen okur",
            "ad değişkeni yanlış tanımlanmış",
            "getline iki kez çağrılmalıdır",
        },
        .acceptedAnswers = {"b"},
        .explanation = "cin >> satır sonunu akışta bırakır; getline bunu boş satır olarak okur. std::cin.ignore() ile temizlenir.",
        .baseXp = 40,
    });
    questions.push_back(Question{
        .id = 2784, .topicId = 5,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "std::getline(std::cin, veri, ',') çağrısındaki üçüncü argüman ne işe yarar?",
        .options = {
            "Okunacak karakter sayısı",
            "Okumayı bitirecek ayırıcı karakter",
            "Varsayılan değer",
            "Hata kodu",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Üçüncü argüman ayırıcıdır; verilmezse satır sonu kullanılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2785, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "getline, içinde boşluk olan isimleri tek seferde okuyabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "getline satır sonuna kadar okuduğu için \"Ali Veli\" tek seferde alınır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2786, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "getline yalnızca std::cin ile kullanılabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Dosya akışları (ifstream) gibi başka giriş akışlarıyla da kullanılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2787, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "getline okunan satırı ikinci argüman olarak verilen değişkene yazar.",
        .acceptedAnswers = {"1"},
        .explanation = "İkinci argüman referansla alınır ve okunan satır oraya yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2788, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcı hiçbir şey yazmadan Enter'a basarsa getline boş bir string okur.",
        .acceptedAnswers = {"1"},
        .explanation = "Satırda karakter yoksa string boş kalır; bu geçerli bir okumadır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2789, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "getline ile okunan değer bir std::string değişkeninde saklanır.",
        .acceptedAnswers = {"1"},
        .explanation = "En yaygın kullanımı std::string ile birliktedir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2790, .topicId = 5,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "getline'ın okuduğu satır sonu karakteri string'in sonunda yer alır.",
        .acceptedAnswers = {"2"},
        .explanation = "Satır sonu akıştan çıkarılır ama string'e eklenmez.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2791, .topicId = 5,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "std::string ad;\nstd::_____(std::cin, ad);\nSatırın tamamını okumak için boşluğa ne gelmeli?",
        .acceptedAnswers = {"getline"},
        .explanation = "std::getline satırın tamamını okur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2792, .topicId = 5,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "std::getline(_____, satir);\nKlavyeden okumak için boşluğa hangi akış gelmeli?",
        .acceptedAnswers = {"std::cin", "cin"},
        .explanation = "İlk argüman okunacak akıştır; klavye için std::cin kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2793, .topicId = 5,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "getline ile birlikte std::string kullanabilmek için eklenmesi gereken kütüphane: #include <_____>",
        .acceptedAnswers = {"string"},
        .explanation = "std::string ve ilgili getline aşırı yüklemesi <string> içindedir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2794, .topicId = 5,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::VeryHard,
        .prompt = "cin >> sonrası getline'ın boş satır okumasını önlemek için araya eklenen çağrı: std::cin._____();",
        .acceptedAnswers = {"ignore"},
        .explanation = "std::cin.ignore(); akışta kalan satır sonu karakterini atarak sorunu çözer.",
        .baseXp = 40,
    });
    questions.push_back(Question{
        .id = 2795, .topicId = 5,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "std::string sehir;\n_____;\nKullanıcıdan boşluk içerebilen bir şehir adı okuyan satırı tamamlayın.",
        .acceptedAnswers = {"std::getline(std::cin, sehir)"},
        .explanation = "std::getline(std::cin, sehir); satırın tamamını okur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2796, .topicId = 5,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "std::string veri;\nstd::getline(std::cin, veri, _____);\nVirgüle kadar okumak için boşluğa ne gelmeli?",
        .acceptedAnswers = {"','"},
        .explanation = "Ayırıcı bir karakter olduğu için tek tırnak içinde yazılır: ','",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2797, .topicId = 5,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::string ad;\nstd::getline(std::cin, ad);\nstd::cout << ad;\nKullanıcı \"Ali Veli\" yazarsa ekran çıktısı nedir?",
        .acceptedAnswers = {"Ali Veli"},
        .explanation = "getline boşluk dahil satırın tamamını okur, bu yüzden iki kelime de yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2798, .topicId = 5,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::VeryHard,
        .prompt = "std::string veri;\nstd::getline(std::cin, veri, ',');\nstd::cout << veri;\nKullanıcı \"elma,armut\" yazarsa ekran çıktısı nedir?",
        .acceptedAnswers = {"elma"},
        .explanation = "Ayırıcı virgül olduğu için okuma ilk virgülde durur; \"armut\" akışta kalır.",
        .baseXp = 40,
    });
    questions.push_back(Question{
        .id = 2799, .topicId = 5,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nstd::string ad;\nstd::getline(ad);\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::getline(std::cin, ad);"},
        .explanation = "getline'ın ilk argümanı okunacak akıştır; std::cin eksik yazılmış.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2800, .topicId = 5,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kod boşluk içeren adı okuyamıyor:\n\nstd::string ad;\nstd::cin >> ad;\n\nSatırın tamamını okuyacak şekilde düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"std::getline(std::cin, ad);"},
        .explanation = "cin >> ilk boşlukta durur; tüm satır için std::getline kullanılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2801, .topicId = 5,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan boşluk içerebilen tam adını okuyup ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"getline", "cin", "cout", "<<"},
        .explanation = "std::getline(std::cin, ad); ile satır okunur, cout << ad; ile yazdırılır.",
        .baseXp = 40,
    });

    // --- Topic 6: int ---
    questions.push_back(Question{
        .id = 2802, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int sayi = 7 / 2;\nsayi değişkeninin değeri ne olur?",
        .options = {"3.5", "3", "4", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "İki tam sayının bölümü tam sayıdır; ondalık kısım atılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2803, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int sayi = 3.9;\nsayi değişkeninin değeri ne olur?",
        .options = {"4", "3", "3.9", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "int'e atanırken ondalık kısım yuvarlanmaz, doğrudan atılır: 3.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2804, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int türü hangi değerleri saklayabilir?",
        .options = {
            "Sadece pozitif tam sayıları",
            "Negatif ve pozitif tam sayıları",
            "Sadece ondalıklı sayıları",
            "Sadece metinleri",
        },
        .acceptedAnswers = {"b"},
        .explanation = "int işaretli bir türdür; negatif ve pozitif tam sayıları saklar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2805, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Çoğu sistemde int kaç bayt yer kaplar?",
        .options = {"1", "2", "4", "8"},
        .acceptedAnswers = {"c"},
        .explanation = "Yaygın olarak 4 bayttır, ancak standart bunu garanti etmez; sizeof(int) ile öğrenilebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2806, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdakilerden hangisi geçerli bir int tanımlamasıdır?",
        .options = {"int 1sayi = 5;", "int sayi_1 = 5;", "int sayi-1 = 5;", "int int = 5;"},
        .acceptedAnswers = {"b"},
        .explanation = "Değişken adı rakamla başlayamaz, tire içeremez ve anahtar kelime olamaz; alt çizgi geçerlidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2807, .topicId = 6,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int a = 10 % 3;\na değişkeninin değeri ne olur?",
        .options = {"3", "1", "0", "3.33"},
        .acceptedAnswers = {"b"},
        .explanation = "% operatörü bölümden kalanı verir: 10 = 3*3 + 1, kalan 1'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2808, .topicId = 6,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int değişkende ondalıklı sayı saklanamaz.",
        .acceptedAnswers = {"1"},
        .explanation = "int yalnızca tam sayı tutar; ondalıklı değerler için double kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2809, .topicId = 6,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Bir satırda birden fazla int değişken tanımlanabilir: int a = 1, b = 2;",
        .acceptedAnswers = {"1"},
        .explanation = "Virgülle ayırarak aynı satırda birden fazla değişken tanımlanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2810, .topicId = 6,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "Tanımlanıp değer verilmeyen yerel bir int değişkenin değeri her zaman 0'dır.",
        .acceptedAnswers = {"2"},
        .explanation = "Yerel değişkenler otomatik sıfırlanmaz; içeriği belirsizdir ve okunması tanımsız davranıştır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2811, .topicId = 6,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "int değişkene negatif değer atanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "int işaretli bir türdür; int borc = -500; geçerlidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2812, .topicId = 6,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "int'in saklayabileceği en büyük değeri aşan bir işlem taşmaya (overflow) yol açar.",
        .acceptedAnswers = {"1"},
        .explanation = "Sınır aşıldığında işaretli tam sayılarda taşma oluşur; bu tanımsız davranıştır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2813, .topicId = 6,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ yas = 25;\nTam sayı değişken tanımlamak için boşluğa hangi tür gelmeli?",
        .acceptedAnswers = {"int"},
        .explanation = "Tam sayılar için int türü kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2814, .topicId = 6,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "Bir türün bellekte kaç bayt yer kapladığını öğrenmek için kullanılan operatör: _____",
        .acceptedAnswers = {"sizeof"},
        .explanation = "sizeof(int) ifadesi int'in bayt cinsinden boyutunu verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2815, .topicId = 6,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Hard,
        .prompt = "int kalan = 17 _____ 5;\nkalan değişkeninin 2 olması için boşluğa hangi operatör gelmeli?",
        .acceptedAnswers = {"%"},
        .explanation = "17'nin 5'e bölümünden kalan 2'dir; kalan için % operatörü kullanılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2816, .topicId = 6,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int a = 5;\nint b = 3;\nint fark = _____;\nfark değişkeninin 2 olması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"a - b", "a-b"},
        .explanation = "5 - 3 = 2 olduğu için çıkarma yapılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2817, .topicId = 6,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "int toplam = 0;\ntoplam = toplam _____ 5;\ntoplam değişkeninin 5 olması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"+"},
        .explanation = "0 + 5 = 5; mevcut değere ekleme yapılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2818, .topicId = 6,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int a = 9;\nint b = 4;\nstd::cout << a / b;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2"},
        .explanation = "Tam sayı bölmesinde ondalık kısım atılır: 9 / 4 = 2.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2819, .topicId = 6,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int sayi = 10;\nsayi = sayi + 5;\nsayi = sayi - 3;\nstd::cout << sayi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "10 + 5 = 15, ardından 15 - 3 = 12.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2820, .topicId = 6,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint 2sayi = 10;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"int sayi2 = 10;"},
        .explanation = "Değişken adı rakamla başlayamaz; rakam sona alınabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2821, .topicId = 6,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Medium,
        .prompt = "İki tam sayı değişken tanımlayıp çarpımlarını ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"int", "cout", "<<", "*"},
        .explanation = "İki int tanımlanır, * ile çarpılır ve cout << ile yazdırılır.",
        .baseXp = 20,
    });

    // --- Topic 7: double ---
    questions.push_back(Question{
        .id = 2822, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "double sonuc = 7 / 2;\nsonuc değişkeninin değeri ne olur?",
        .options = {"3.5", "3", "3.0", "Derleme hatası"},
        .acceptedAnswers = {"c"},
        .explanation = "Bölme iki int arasında yapıldığı için önce 3 elde edilir; sonra double'a çevrilir: 3.0.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2823, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "7 / 2 işleminin sonucunun 3.5 olması için ne yapılmalıdır?",
        .options = {
            "Sonucu double değişkene atamak yeterlidir",
            "En az bir işleneni ondalıklı yazmak (7.0 / 2)",
            "Parantez kullanmak",
            "int yerine long kullanmak",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Bölmenin kendisi ondalıklı yapılmalıdır; işlenenlerden biri double olursa sonuç da double olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2824, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Çoğu sistemde double kaç bayt yer kaplar?",
        .options = {"2", "4", "8", "16"},
        .acceptedAnswers = {"c"},
        .explanation = "double genellikle 8 bayttır ve float'tan (4 bayt) daha hassastır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2825, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "C++'ta ondalık ayırıcı olarak ne kullanılır?",
        .options = {"Virgül (3,14)", "Nokta (3.14)", "İkisi de olur", "Tire (3-14)"},
        .acceptedAnswers = {"b"},
        .explanation = "Kaynak kodda ondalık ayırıcı noktadır; virgül farklı bir anlama gelir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2826, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "double ile float arasındaki temel fark nedir?",
        .options = {
            "float negatif sayı tutamaz",
            "double daha fazla bellek kullanır ve daha hassastır",
            "float daha hassastır",
            "Aralarında fark yoktur",
        },
        .acceptedAnswers = {"b"},
        .explanation = "double çift duyarlıklıdır; daha fazla bit kullandığı için daha hassas sonuç verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2827, .topicId = 7,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryHard,
        .prompt = "double a = 0.1 + 0.2;\nstd::cout << (a == 0.3);\nBu kod genellikle ne yazdırır?",
        .options = {"1", "0", "0.3", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Ondalıklı sayılar ikilik sistemde tam saklanamaz; 0.1 + 0.2 tam olarak 0.3 etmez, karşılaştırma false (0) döner.",
        .baseXp = 40,
    });
    questions.push_back(Question{
        .id = 2828, .topicId = 7,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "double türü tam sayı değerleri de saklayabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "double bir tam sayıyı da tutabilir; örneğin double x = 5; geçerlidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2829, .topicId = 7,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "double bir değeri int değişkene atarken ondalık kısım kaybolur.",
        .acceptedAnswers = {"1"},
        .explanation = "int'e atarken ondalık kısım atılır; bu bir veri kaybıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2830, .topicId = 7,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "İki double değeri == ile karşılaştırmak her zaman güvenlidir.",
        .acceptedAnswers = {"2"},
        .explanation = "Yuvarlama hataları nedeniyle beklenen eşitlik sağlanmayabilir; fark bir eşikle karşılaştırılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2831, .topicId = 7,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "double değişkene negatif ondalıklı değer atanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "double sicaklik = -12.5; geçerli bir tanımlamadır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2832, .topicId = 7,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "double kullanmak için ayrı bir kütüphane eklemek gerekir.",
        .acceptedAnswers = {"2"},
        .explanation = "double bir temel dil türüdür; kütüphane gerektirmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2833, .topicId = 7,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ pi = 3.14;\nOndalıklı sayı saklamak için boşluğa hangi tür gelmeli?",
        .acceptedAnswers = {"double"},
        .explanation = "Ondalıklı sayılar için double kullanılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2834, .topicId = 7,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Hard,
        .prompt = "double yarim = 1 / 2._____;\nyarim değişkeninin 0.5 olması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"0"},
        .explanation = "2.0 yazıldığında bölme ondalıklı yapılır ve sonuç 0.5 olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2835, .topicId = 7,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "C++'ta 3.14 sayısındaki ondalık ayırıcı karakter: _____",
        .acceptedAnswers = {"."},
        .explanation = "Kaynak kodda ondalık ayırıcı noktadır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2836, .topicId = 7,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "double a = 5.0;\ndouble b = 2.0;\ndouble sonuc = _____;\nsonuc değişkeninin 2.5 olması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"a / b", "a/b"},
        .explanation = "5.0 / 2.0 = 2.5; her iki işlenen de double olduğu için bölme ondalıklı yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2837, .topicId = 7,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "int toplam = 7;\nint adet = 2;\ndouble ortalama = _____ / adet;\nortalama değerinin 3.5 olması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"toplam * 1.0", "(double)toplam", "static_cast<double>(toplam)", "1.0 * toplam"},
        .explanation = "Bölmeden önce bir işlenen double'a çevrilmelidir; aksi halde tam sayı bölmesi yapılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2838, .topicId = 7,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "double sonuc = 10 / 4;\nstd::cout << sonuc;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2"},
        .explanation = "Bölme iki int arasında yapılır (10/4 = 2), sonra 2.0 olarak saklanır ve 2 yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2839, .topicId = 7,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "double sonuc = 10.0 / 4;\nstd::cout << sonuc;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"2.5"},
        .explanation = "İşlenenlerden biri double olduğu için bölme ondalıklı yapılır: 2.5.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2840, .topicId = 7,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int sayi = 9.99;\nstd::cout << sayi;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"9"},
        .explanation = "int'e atarken ondalık kısım yuvarlanmadan atılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2841, .topicId = 7,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\ndouble fiyat = 19,90;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"double fiyat = 19.90;", "double fiyat = 19.9;"},
        .explanation = "C++'ta ondalık ayırıcı virgül değil noktadır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2842, .topicId = 7,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kod 2.5 yerine 2 yazdırıyor:\n\ndouble ortalama = 5 / 2;\n\n2.5 sonucunu verecek şekilde düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"double ortalama = 5.0 / 2;", "double ortalama = 5 / 2.0;", "double ortalama = 5.0 / 2.0;"},
        .explanation = "Bölmenin ondalıklı yapılması için en az bir işlenen double olmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2843, .topicId = 7,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan iki ondalıklı sayı okuyup ortalamalarını ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"double", "cin", ">>", "cout", "<<"},
        .explanation = "İki double okunur, toplamları 2.0'a bölünür ve sonuç yazdırılır.",
        .baseXp = 40,
    });

    // --- Topic 8: char ---
    questions.push_back(Question{
        .id = 2844, .topicId = 8,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "char değişkene değer atarken hangi tırnak kullanılır?",
        .options = {"Çift tırnak (\"A\")", "Tek tırnak ('A')", "Tırnak kullanılmaz", "Ters tırnak"},
        .acceptedAnswers = {"b"},
        .explanation = "Tek karakterler tek tırnak, metinler çift tırnak içine yazılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2845, .topicId = 8,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "char türü kaç bayt yer kaplar?",
        .options = {"1", "2", "4", "8"},
        .acceptedAnswers = {"a"},
        .explanation = "char standarda göre her zaman 1 bayttır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2846, .topicId = 8,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "char harf = 65;\nstd::cout << harf;\nBu kod ne yazdırır?",
        .options = {"65", "A", "Derleme hatası", "Hiçbir şey"},
        .acceptedAnswers = {"b"},
        .explanation = "char sayısal bir türdür; 65 ASCII değeri 'A' karakterine karşılık gelir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2847, .topicId = 8,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "'A' ve \"A\" arasındaki fark nedir?",
        .options = {
            "Fark yoktur",
            "'A' bir karakter, \"A\" bir metindir",
            "'A' bir metin, \"A\" bir karakterdir",
            "İkisi de geçersizdir",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Tek tırnak char, çift tırnak string (sonunda gizli bir bitiş karakteriyle) oluşturur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2848, .topicId = 8,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "char birden fazla karakter saklayabilir mi?",
        .options = {
            "Evet, istenilen kadar",
            "Hayır, yalnızca tek bir karakter saklar",
            "Evet, en fazla 4 karakter",
            "Sadece rakamlar için evet",
        },
        .acceptedAnswers = {"b"},
        .explanation = "char tek bir karakter tutar; birden fazlası için std::string kullanılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2849, .topicId = 8,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "char değişkende rakam karakteri ('7') saklanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "'7' bir karakterdir; sayı olan 7'den farklıdır ama char'da saklanabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2850, .topicId = 8,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "'7' karakteri ile 7 sayısı bellekte aynı değeri taşır.",
        .acceptedAnswers = {"2"},
        .explanation = "'7' karakterinin ASCII değeri 55'tir; sayı olan 7'den farklıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2851, .topicId = 8,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "char değişkenler karşılaştırma operatörleriyle karşılaştırılabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Sayısal karşılıkları üzerinden karşılaştırılır; 'a' < 'b' doğrudur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2852, .topicId = 8,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "char kullanmak için <string> kütüphanesi gerekir.",
        .acceptedAnswers = {"2"},
        .explanation = "char temel bir dil türüdür; kütüphane gerektirmez. <string> std::string içindir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2853, .topicId = 8,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "char bir değişkene tam sayı değeri atanabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "char sayısal bir türdür; char c = 65; geçerlidir ve 'A' anlamına gelir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2854, .topicId = 8,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ harf = 'B';\nTek karakter saklamak için boşluğa hangi tür gelmeli?",
        .acceptedAnswers = {"char"},
        .explanation = "Tek karakterler char türünde saklanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2855, .topicId = 8,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "char c = _____A_____;\nGeçerli bir char ataması için boşluklara hangi tırnak gelmeli? (karakteri yazın)",
        .acceptedAnswers = {"'"},
        .explanation = "char değerleri tek tırnak içine alınır: 'A'.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2856, .topicId = 8,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Hard,
        .prompt = "Karakterlerin sayısal karşılıklarını tanımlayan standart tablonun adı: _____",
        .acceptedAnswers = {"ASCII", "ascii"},
        .explanation = "ASCII tablosu karakterleri sayısal değerlerle eşleştirir; 'A' için 65.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2857, .topicId = 8,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "char harf = 'x';\nstd::cout << _____;\nEkrana x yazdırmak için boşluğa ne gelmeli?",
        .acceptedAnswers = {"harf"},
        .explanation = "Değişken adı tırnaksız yazıldığında içindeki karakter yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2858, .topicId = 8,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "char harf = 'a';\nchar buyuk = harf _____ 32;\nbuyuk değişkeninin 'A' olması için boşluğa hangi operatör gelmeli?",
        .acceptedAnswers = {"-"},
        .explanation = "'a' 97, 'A' 65'tir; aradaki 32 fark çıkarılırsa büyük harf elde edilir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2859, .topicId = 8,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "char a = 'C';\nchar b = '+';\nstd::cout << a << b << b;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"C++"},
        .explanation = "Üç karakter sırayla yan yana yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2860, .topicId = 8,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::VeryHard,
        .prompt = "char harf = 'A';\nstd::cout << static_cast<int>(harf);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"65"},
        .explanation = "int'e çevrildiğinde karakterin ASCII değeri yazdırılır; 'A' için 65.",
        .baseXp = 40,
    });
    questions.push_back(Question{
        .id = 2861, .topicId = 8,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "char harf = 'a';\nharf = harf + 1;\nstd::cout << harf;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"b"},
        .explanation = "'a' değerinin bir fazlası 'b' karakterine karşılık gelir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2862, .topicId = 8,
        .type = QuestionType::FindError, .difficulty = Difficulty::Easy,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nchar harf = \"A\";\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"char harf = 'A';"},
        .explanation = "char için tek tırnak kullanılır; çift tırnak bir metin oluşturur ve char'a atanamaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2863, .topicId = 8,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nchar kelime = 'abc';\n\nDeğişken tek bir karakter tutmalı. Düzeltilmiş satırı yazın.",
        .acceptedAnswers = {"char kelime = 'a';"},
        .explanation = "char yalnızca tek karakter tutar; birden fazlası için std::string gerekir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2864, .topicId = 8,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Medium,
        .prompt = "Bir char değişken tanımlayıp değerini ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"char", "cout", "<<"},
        .explanation = "char c = 'A'; ardından std::cout << c; yeterlidir.",
        .baseXp = 20,
    });

    // --- Topic 9: bool ---
    questions.push_back(Question{
        .id = 2865, .topicId = 9,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "bool türü hangi değerleri alabilir?",
        .options = {"0-255 arası sayılar", "true ve false", "Sadece metinler", "Ondalıklı sayılar"},
        .acceptedAnswers = {"b"},
        .explanation = "bool mantıksal bir türdür; yalnızca true veya false değeri alır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2866, .topicId = 9,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "bool durum = true;\nstd::cout << durum;\nEkranda ne görünür?",
        .options = {"true", "1", "evet", "T"},
        .acceptedAnswers = {"b"},
        .explanation = "Varsayılan olarak bool sayıya çevrilerek yazdırılır: true için 1, false için 0.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2867, .topicId = 9,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "bool değerlerin ekranda true/false olarak yazılması için hangi manipülatör kullanılır?",
        .options = {"std::showbool", "std::boolalpha", "std::truefalse", "std::setbool"},
        .acceptedAnswers = {"b"},
        .explanation = "std::cout << std::boolalpha; sonrasında bool değerler true/false olarak yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2868, .topicId = 9,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "bool sonuc = (5 > 3);\nsonuc değişkeninin değeri nedir?",
        .options = {"false", "true", "5", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Karşılaştırma operatörleri bool üretir; 5 > 3 doğru olduğu için true.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2869, .topicId = 9,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryHard,
        .prompt = "bool b = 42;\nb değişkeninin değeri ne olur?",
        .options = {"42", "true", "false", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "Sıfır dışındaki her sayı true'ya, yalnızca 0 false'a dönüşür.",
        .baseXp = 40,
    });
    questions.push_back(Question{
        .id = 2870, .topicId = 9,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "bool türü koşul ifadelerinde (if) kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "if koşulu bool bir değer bekler; karşılaştırmalar bool üretir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2871, .topicId = 9,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "true ve false C++'ta anahtar kelimedir.",
        .acceptedAnswers = {"1"},
        .explanation = "İkisi de dilin anahtar kelimeleridir; tırnak içine alınmazlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2872, .topicId = 9,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "bool değişkene 0 atanırsa değeri false olur.",
        .acceptedAnswers = {"1"},
        .explanation = "0 false'a, sıfırdan farklı her değer true'ya dönüşür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2873, .topicId = 9,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "bool bir değişken \"true\" şeklinde tırnak içinde yazılarak tanımlanır.",
        .acceptedAnswers = {"2"},
        .explanation = "Tırnak içine alınırsa metin olur; bool için tırnaksız true/false yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2874, .topicId = 9,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "! operatörü bir bool değerin tersini alır.",
        .acceptedAnswers = {"1"},
        .explanation = "! mantıksal değilleme operatörüdür; !true false, !false true verir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2875, .topicId = 9,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ aktif = true;\nMantıksal değer saklamak için boşluğa hangi tür gelmeli?",
        .acceptedAnswers = {"bool"},
        .explanation = "Doğru/yanlış değerleri bool türünde saklanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2876, .topicId = 9,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "bool sonuc = _____;\nsonuc'un yanlış olması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"false"},
        .explanation = "Yanlış değeri false anahtar kelimesiyle yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2877, .topicId = 9,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Hard,
        .prompt = "std::cout << std::_____ << true;\nEkranda 1 yerine true yazması için boşluğa ne gelmeli?",
        .acceptedAnswers = {"boolalpha"},
        .explanation = "std::boolalpha manipülatörü bool değerleri true/false olarak yazdırır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2878, .topicId = 9,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int yas = 20;\nbool resit = _____;\nyas 18 veya daha büyükse resit true olmalı. Boşluğa ne gelmeli?",
        .acceptedAnswers = {"yas >= 18", "yas>=18"},
        .explanation = "Karşılaştırma bir bool değer üretir ve doğrudan atanabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2879, .topicId = 9,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "bool acik = true;\nbool kapali = _____acik;\nkapali'nın acik'in tersi olması için boşluğa hangi operatör gelmeli?",
        .acceptedAnswers = {"!"},
        .explanation = "! operatörü mantıksal değeri tersine çevirir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2880, .topicId = 9,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "bool durum = false;\nstd::cout << durum;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0"},
        .explanation = "false varsayılan olarak 0 şeklinde yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2881, .topicId = 9,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "std::cout << (10 > 20);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0"},
        .explanation = "10 > 20 yanlıştır; false değeri 0 olarak yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2882, .topicId = 9,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::VeryHard,
        .prompt = "bool a = true;\nstd::cout << !a;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"0"},
        .explanation = "!true false'tur ve 0 olarak yazdırılır.",
        .baseXp = 40,
    });
    questions.push_back(Question{
        .id = 2883, .topicId = 9,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nbool aktif = \"true\";\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"bool aktif = true;"},
        .explanation = "true bir anahtar kelimedir; tırnak içine alınırsa metin olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2884, .topicId = 9,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nbool sonuc = True;\n\nDüzeltilmiş satırı yazın.",
        .acceptedAnswers = {"bool sonuc = true;"},
        .explanation = "C++ büyük-küçük harfe duyarlıdır; anahtar kelime küçük harfle true şeklinde yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2885, .topicId = 9,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, bir sayının pozitif olup olmadığını bool değişkende tutup yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın, örnek: 1 2 3):",
        .options = {"std::cout << pozitifMi;", "bool pozitifMi = sayi > 0;", "int sayi = 5;"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce sayı tanımlanır, sonra karşılaştırma sonucu bool'a atanır, en son yazdırılır: sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2886, .topicId = 9,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Medium,
        .prompt = "Bir bool değişken tanımlayıp değerini ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"bool", "cout", "<<"},
        .explanation = "bool durum = true; ardından std::cout << durum; yeterlidir.",
        .baseXp = 20,
    });

    // --- Topic 10: const ---
    questions.push_back(Question{
        .id = 2887, .topicId = 10,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "const anahtar kelimesi ne işe yarar?",
        .options = {
            "Değişkeni siler",
            "Değişkenin değerinin sonradan değiştirilmesini engeller",
            "Değişkeni global yapar",
            "Değişkeni hızlandırır",
        },
        .acceptedAnswers = {"b"},
        .explanation = "const ile tanımlanan bir değişkenin değeri tanımlandıktan sonra değiştirilemez.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2888, .topicId = 10,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "const int PI_YAKLASIK = 3;\nPI_YAKLASIK = 4;\nİkinci satır ne yapar?",
        .options = {
            "Değeri 4 yapar",
            "Derleme hatası verir",
            "Çalışma zamanında hata verir",
            "Sessizce yok sayılır",
        },
        .acceptedAnswers = {"b"},
        .explanation = "const bir değişkene atama yapmak derleme zamanında hata verir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2889, .topicId = 10,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "const bir değişken tanımlanırken neden ilk değer verilmelidir?",
        .options = {
            "Derleyici hızlansın diye",
            "Sonradan değer atanamayacağı için",
            "Bellek tasarrufu için",
            "Zorunlu değildir",
        },
        .acceptedAnswers = {"b"},
        .explanation = "const değişkene sonradan atama yapılamaz; bu yüzden değeri tanımlandığı anda verilmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2890, .topicId = 10,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Sabit isimlendirmede yaygın olarak kullanılan yazım biçimi hangisidir?",
        .options = {"camelCase", "BUYUK_HARF", "kebab-case", "Rakamla başlamak"},
        .acceptedAnswers = {"b"},
        .explanation = "Sabitler geleneksel olarak büyük harf ve alt çizgiyle yazılır; zorunlu değil ama yaygın bir alışkanlıktır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2891, .topicId = 10,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "const kullanmanın temel faydası nedir?",
        .options = {
            "Programı hızlandırır",
            "Yanlışlıkla değiştirilmemesi gereken değerleri derleyici korumasına alır",
            "Belleği azaltır",
            "Kodu kısaltır",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Niyet kodda görünür hale gelir ve hatalı bir atama çalışmadan önce derlemede yakalanır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2892, .topicId = 10,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "const bir değişkenin değeri program çalışırken değiştirilebilir.",
        .acceptedAnswers = {"2"},
        .explanation = "const değişkenler değiştirilemez; denenirse derleme hatası oluşur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2893, .topicId = 10,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "const bir değişken tanımlanırken ilk değeri verilmelidir.",
        .acceptedAnswers = {"1"},
        .explanation = "Sonradan atama yapılamayacağı için değer tanımlama anında verilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2894, .topicId = 10,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "const yalnızca int türüyle kullanılabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "const her türle kullanılabilir: const double, const char, const std::string gibi.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2895, .topicId = 10,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Hard,
        .prompt = "const bir değişken okunabilir ama yazılamaz.",
        .acceptedAnswers = {"1"},
        .explanation = "Değeri istenildiği kadar okunabilir; yalnızca değiştirilmesi engellenir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2896, .topicId = 10,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Sabitlerin büyük harfle yazılması derleyici tarafından zorunlu tutulur.",
        .acceptedAnswers = {"2"},
        .explanation = "Bu yalnızca bir yazım geleneğidir; derleyici için fark etmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2897, .topicId = 10,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ int MAX = 100;\nDeğiştirilemez bir değişken tanımlamak için boşluğa ne gelmeli?",
        .acceptedAnswers = {"const"},
        .explanation = "const anahtar kelimesi değişkeni sabit hale getirir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 2898, .topicId = 10,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "const double PI = _____;\nPi sayısının yaklaşık değerini yazın (iki ondalık basamak).",
        .acceptedAnswers = {"3.14"},
        .explanation = "const double PI = 3.14; sabit bir ondalıklı değer tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2899, .topicId = 10,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Hard,
        .prompt = "const bir değişkene sonradan atama yapılırsa _____ zamanında hata alınır. (derleme / çalışma)",
        .acceptedAnswers = {"derleme"},
        .explanation = "Hata program çalışmadan önce, derleme sırasında yakalanır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2900, .topicId = 10,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____ int GUN_SAYISI = 7;\nHaftadaki gün sayısını sabit olarak tanımlayan satırı tamamlayın.",
        .acceptedAnswers = {"const"},
        .explanation = "Değişmeyecek değerler const ile tanımlanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2901, .topicId = 10,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Hard,
        .prompt = "const int KENAR = 5;\nint alan = _____;\nKarenin alanını hesaplayan satırı tamamlayın.",
        .acceptedAnswers = {"KENAR * KENAR", "KENAR*KENAR"},
        .explanation = "const değişkenler okunabilir; hesaplamada serbestçe kullanılabilirler.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2902, .topicId = 10,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "const int SAYI = 10;\nstd::cout << SAYI * 2;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"20"},
        .explanation = "const değişkenin değeri okunabilir; 10 * 2 = 20.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2903, .topicId = 10,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "const double KDV = 0.2;\ndouble fiyat = 100;\nstd::cout << fiyat * KDV;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"20"},
        .explanation = "100 * 0.2 = 20; sonuç tam sayı olduğu için 20 şeklinde yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2904, .topicId = 10,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nconst int MAX;\n\nHatalı satırı düzeltilmiş haliyle yazın (değer olarak 100 kullanın).",
        .acceptedAnswers = {"const int MAX = 100;"},
        .explanation = "const değişkene sonradan atama yapılamaz; ilk değeri tanımlanırken verilmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2905, .topicId = 10,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kod derlenmiyor:\n\nconst int SINIR = 10;\nSINIR = 20;\n\nSINIR'ın değişebilmesi isteniyorsa ilk satır nasıl yazılmalı?",
        .acceptedAnswers = {"int SINIR = 10;"},
        .explanation = "Değer değişecekse const kullanılmamalıdır; const kaldırılınca atama geçerli olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2906, .topicId = 10,
        .type = QuestionType::Scenario, .difficulty = Difficulty::Hard,
        .prompt = "Bir programda vergi oranını tutan bir değer var ve bu değerin program boyunca yanlışlıkla değiştirilmemesi gerekiyor. Nasıl tanımlamalısın?",
        .options = {
            "Normal bir double olarak",
            "const double olarak",
            "int olarak",
            "Her fonksiyonda yeniden tanımlayarak",
        },
        .acceptedAnswers = {"b"},
        .explanation = "const, değerin değiştirilmeye çalışılmasını derleme zamanında engeller ve niyeti kodda açıkça gösterir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2907, .topicId = 10,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, sabit bir kenar uzunluğuyla karenin alanını yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın, örnek: 1 2 3):",
        .options = {"std::cout << alan;", "const int KENAR = 4;", "int alan = KENAR * KENAR;"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "Önce sabit tanımlanır, sonra alan hesaplanır, en son yazdırılır: sıra 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2908, .topicId = 10,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Medium,
        .prompt = "Bir sabit tanımlayıp değerini ekrana yazdıran bir program yazın (const kullanın).",
        .acceptedAnswers = {"const", "cout", "<<"},
        .explanation = "const int SAYI = 10; ardından std::cout << SAYI; yeterlidir.",
        .baseXp = 20,
    });
}

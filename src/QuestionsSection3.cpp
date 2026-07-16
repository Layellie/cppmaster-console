#include "QuestionContent.h"

#include "Question.h"

void appendSection3Questions(std::vector<Question>& questions) {
    // Topic 21: switch-case
    questions.push_back(Question{
        .id = 363, .topicId = 21,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "switch-case yapısı ne amaçla kullanılır?",
        .options = {"Döngü oluşturmak", "Bir değişkenin farklı değerlerine göre farklı kod bloklarını çalıştırmak", "Fonksiyon tanımlamak", "Hata yakalamak"},
        .acceptedAnswers = {"b"},
        .explanation = "switch-case, bir değişkenin değerine göre farklı kod bloklarını çalıştırmayı sağlar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 364, .topicId = 21,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "switch bloğunda bir case'in sonuna break konulmazsa ne olur?",
        .options = {"Program çöker", "Derleme hatası oluşur", "Kod bir sonraki case'e düşer (fall-through)", "Hiçbir fark olmaz"},
        .acceptedAnswers = {"c"},
        .explanation = "break olmadığında kod bir sonraki case'e düşer (fall-through) ve o blok da çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 365, .topicId = 21,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "default etiketi switch bloğunda ne zaman çalışır?",
        .options = {"Her zaman", "Hiçbir case eşleşmediğinde", "Yalnızca ilk case'de", "Asla çalışmaz"},
        .acceptedAnswers = {"b"},
        .explanation = "default, hiçbir case değeriyle eşleşme olmadığında çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 366, .topicId = 21,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int gun = 2; switch (gun) { case 1: std::cout << \"Pazartesi\"; break; case 2: std::cout << \"Salı\"; break; default: std::cout << \"Diğer\"; } kodu ne yazdırır?",
        .options = {"Pazartesi", "Salı", "Diğer", "Hiçbir şey"},
        .acceptedAnswers = {"b"},
        .explanation = "gun 2 olduğu için case 2 eşleşir ve 'Salı' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 367, .topicId = 21,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "switch bloğu hangi türdeki değerlerle çalışabilir?",
        .options = {"Yalnızca string", "Yalnızca double", "Tam sayı ve karakter gibi ayrık değerler", "Herhangi bir türle"},
        .acceptedAnswers = {"c"},
        .explanation = "switch yalnızca tam sayı, karakter, enum gibi ayrık (discrete) değerlerle çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 368, .topicId = 21,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int x = 1; switch (x) { case 1: std::cout << \"A\"; case 2: std::cout << \"B\"; break; case 3: std::cout << \"C\"; } kodu ne yazdırır (case 1'de break olmadığına dikkat edin)?",
        .options = {"A", "AB", "ABC", "B"},
        .acceptedAnswers = {"b"},
        .explanation = "case 1 eşleşir, break olmadığı için case 2'ye düşer (fall-through); break case 2'de olduğu için çıktı 'AB'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 369, .topicId = 21,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "switch bir if-else zincirine göre ne zaman daha uygundur?",
        .options = {"Aralık (>, < gibi) kontrolleri gerektiğinde", "Tek bir değişkenin birden çok sabit değeriyle karşılaştırıldığı durumlarda", "Hiçbir zaman, if-else her zaman daha iyidir", "Yalnızca döngüler içinde"},
        .acceptedAnswers = {"b"},
        .explanation = "switch, tek bir değişkenin birden çok sabit değerle karşılaştırıldığı durumlarda if-else zincirinden daha okunaklıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 370, .topicId = 21,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int puan = 5; switch (puan) { case 1: case 2: std::cout << \"Düşük\"; break; case 5: case 6: std::cout << \"Yüksek\"; break; } kodu ne yazdırır?",
        .options = {"Düşük", "Yüksek", "Hiçbir şey", "Hata"},
        .acceptedAnswers = {"b"},
        .explanation = "puan 5 olduğu için case 5 eşleşir; case 5 ve case 6 aynı bloğu paylaştığı için 'Yüksek' yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 371, .topicId = 21,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "switch-case, bir değişkenin farklı sabit değerlerine göre dallanma sağlar.",
        .acceptedAnswers = {"1"},
        .explanation = "switch-case'in amacı tam olarak budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 372, .topicId = 21,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "switch bloğunda break kullanmak zorunludur, aksi halde derleme hatası oluşur.",
        .acceptedAnswers = {"2"},
        .explanation = "break isteğe bağlıdır; olmadığında derleme hatası değil, fall-through davranışı oluşur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 373, .topicId = 21,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "Bir case bloğunun sonuna break konulmazsa, kod bir sonraki case'e devam eder (fall-through).",
        .acceptedAnswers = {"1"},
        .explanation = "break olmadan kod sıradaki case'e düşmeye devam eder.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 374, .topicId = 21,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "default etiketi switch bloğunda zorunludur.",
        .acceptedAnswers = {"2"},
        .explanation = "default isteğe bağlıdır; olmadan da switch derlenir ve çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 375, .topicId = 21,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "switch, aralık (örneğin 1 ile 10 arası) kontrolü yapmak için uygun değildir.",
        .acceptedAnswers = {"1"},
        .explanation = "switch yalnızca tam eşleşen ayrık değerlerle çalışır, aralık kontrolü için if-else daha uygundur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 376, .topicId = 21,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "Birden fazla case etiketi (örneğin case 1: case 2:) aynı kod bloğunu paylaşabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Ardışık case etiketleri arasında kod olmazsa, aynı bloğu paylaşırlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 377, .topicId = 21,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ (gun) {\n    case 1:\n        std::cout << \"Pazartesi\";\n        break;\n}\nBir değişkenin değerine göre dallanma yapmak için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"switch"},
        .explanation = "switch anahtar kelimesi, değişkenin değerine göre dallanma yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 378, .topicId = 21,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "switch (gun) {\n    _____ 1:\n        std::cout << \"Pazartesi\";\n        break;\n}\nBir değeri belirtmek için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"case"},
        .explanation = "case anahtar kelimesi belirli bir değeri tanımlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 379, .topicId = 21,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "switch (gun) {\n    case 1:\n        std::cout << \"Pazartesi\";\n        _____;\n}\nSonraki case'e düşmeyi (fall-through) önlemek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"break"},
        .explanation = "break, switch bloğundan çıkışı sağlar ve fall-through'u önler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 380, .topicId = 21,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "switch (puan) {\n    case 1:\n        std::cout << \"Düşük\";\n        break;\n    _____:\n        std::cout << \"Tanımsız puan\";\n}\nHiçbir case eşleşmediğinde çalışacak etiketi boşluğa yazın.",
        .acceptedAnswers = {"default"},
        .explanation = "default etiketi hiçbir case eşleşmediğinde çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 381, .topicId = 21,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int x = 3; switch (x) { case 3: std::cout << _____; break; } kodunun 'Üç' yazdırması için boşluğa ne yazılmalı (tırnaklarla)?",
        .acceptedAnswers = {"\"Üç\""},
        .explanation = "cout ile bir metin yazdırmak için çift tırnak içinde yazılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 382, .topicId = 21,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "switch (harf) {\n    case 'a':\n    case _____:\n        std::cout << \"Sesli harf (a veya e)\";\n        break;\n}\nİkinci sesli harfi (e) temsil eden case etiketini boşluğa yazın (tırnakla).",
        .acceptedAnswers = {"'e'"},
        .explanation = "Karakter sabitleri tek tırnak içinde yazılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 383, .topicId = 21,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int gun = 6;\nswitch (gun) {\n    _____\n        std::cout << \"Hafta sonu\";\n        break;\n}\ngun'un 6 olduğu durumu kontrol eden case satırını yazın.",
        .acceptedAnswers = {"case 6:"},
        .explanation = "case 6:, gun'un 6'ya eşit olduğu durumu tanımlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 384, .topicId = 21,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "switch (renk) {\n    case 1:\n        std::cout << \"Kırmızı\";\n        break;\n    _____\n        std::cout << \"Bilinmeyen renk\";\n}\nHiçbir case eşleşmediğinde çalışacak satırı yazın.",
        .acceptedAnswers = {"default:"},
        .explanation = "default:, hiçbir case eşleşmediğinde çalışacak bloğu başlatır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 385, .topicId = 21,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int x = 2;\nswitch (x) {\n    case 1:\n        std::cout << \"Bir\";\n        break;\n    case 2:\n        std::cout << \"İki\";\n        break;\n    default:\n        std::cout << \"Diğer\";\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"İki"},
        .explanation = "x 2 olduğu için case 2 eşleşir ve 'İki' yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 386, .topicId = 21,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int x = 1;\nswitch (x) {\n    case 1:\n        std::cout << \"A\";\n    case 2:\n        std::cout << \"B\";\n        break;\n    case 3:\n        std::cout << \"C\";\n}\nYukarıdaki kodun ekran çıktısı nedir? (case 1'de break olmadığına dikkat edin)",
        .acceptedAnswers = {"AB"},
        .explanation = "case 1 eşleşir, break olmadığı için case 2'ye düşer; break case 2'de olduğu için çıktı 'AB'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 387, .topicId = 21,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint gun = 1;\nswitch (gun)\n    case 1:\n        std::cout << \"Pazartesi\";\n        break;\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"switch (gun) {"},
        .explanation = "switch bloğunun gövdesi süslü parantez içine alınmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 388, .topicId = 21,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint puan = 1;\nswitch (puan) {\n    case 1\n        std::cout << \"Düşük\";\n        break;\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"case 1:"},
        .explanation = "case etiketinden sonra iki nokta (:) gelmelidir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 389, .topicId = 21,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint x = 2;\nswitch (x) {\n    case 2:\n        std::cout << \"İki\";\n    break\n}\n\nDüzeltilmiş dördüncü satırı yazın.",
        .acceptedAnswers = {"break;"},
        .explanation = "break ifadesinin sonunda noktalı virgül eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 390, .topicId = 21,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, gun değişkenine göre gün adı yazdıran geçerli bir switch programı oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"}", "case 1:", "std::cout << \"Pazartesi\";", "switch (gun) {", "int gun = 1;", "break;"},
        .acceptedAnswers = {"5 4 2 3 6 1"},
        .explanation = "Önce değişken tanımlanır (5), switch açılır (4), case etiketi (2), yazdırma (3), break (6), en son kapanış (1): sıra 5 4 2 3 6 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 391, .topicId = 21,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan 1-3 arası bir gün numarası okuyup, switch-case kullanarak günün adını (1=Pazartesi, 2=Salı, 3=Çarşamba) ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"cin", ">>", "switch", "case", "break", "cout", "<<"},
        .explanation = "Program gün numarasını cin >> ile okumalı, switch-case ile uygun günü seçmeli ve cout << ile yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 22: for
    questions.push_back(Question{
        .id = 392, .topicId = 22,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "for döngüsü ne zaman tercih edilir?",
        .options = {"Tekrar sayısı belirsizken", "Tekrar sayısı önceden biliniyorken", "Yalnızca bir kez çalıştırmak için", "Hiçbir zaman"},
        .acceptedAnswers = {"b"},
        .explanation = "for döngüsü, tekrar sayısının önceden bilindiği durumlar için uygundur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 393, .topicId = 22,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i < 5; i++) döngüsü kaç kez çalışır?",
        .options = {"4", "5", "6", "Sonsuz"},
        .acceptedAnswers = {"b"},
        .explanation = "i, 0'dan 4'e kadar (0,1,2,3,4) 5 değer alır; döngü 5 kez çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 394, .topicId = 22,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "for döngüsünün üç bölümü hangi karakterle ayrılır?",
        .options = {",", ";", ":", "."},
        .acceptedAnswers = {"b"},
        .explanation = "for döngüsünün başlangıç, koşul ve artırma bölümleri noktalı virgülle (;) ayrılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 395, .topicId = 22,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 3; i++) { std::cout << i; } kodunun çıktısı nedir?",
        .options = {"123", "012", "1 2 3", "012 3"},
        .acceptedAnswers = {"a"},
        .explanation = "i 1'den 3'e kadar sırayla yazdırılır, aralarında boşluk olmadığı için '123' çıkar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 396, .topicId = 22,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "for döngüsünün başlangıç bölümü kaç kez çalışır?",
        .options = {"Her turda bir kez", "Yalnızca bir kez, döngü başlamadan önce", "Hiç çalışmaz", "Döngü bitince bir kez"},
        .acceptedAnswers = {"b"},
        .explanation = "Başlangıç bölümü (örneğin int i = 0) yalnızca döngü başlamadan önce bir kez çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 397, .topicId = 22,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 5; i > 0; i--) döngüsü kaç kez çalışır?",
        .options = {"4", "5", "6", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "i, 5'ten 1'e kadar (5,4,3,2,1) 5 değer alır; döngü 5 kez çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 398, .topicId = 22,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "for (int i = 0; i < 10; i += 2) döngüsü kaç kez çalışır?",
        .options = {"5", "10", "4", "6"},
        .acceptedAnswers = {"a"},
        .explanation = "i sırasıyla 0,2,4,6,8 değerlerini alır (10 dahil değil); döngü 5 kez çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 399, .topicId = 22,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "for (int i = 0; i <= 10; i++) döngüsü kaç kez çalışır (i < 10 değil, i <= 10 olduğuna dikkat edin)?",
        .options = {"10", "11", "9", "12"},
        .acceptedAnswers = {"b"},
        .explanation = "i, 0'dan 10'a kadar (10 dahil) 11 değer alır; döngü 11 kez çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 400, .topicId = 22,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "for döngüsü, tekrar sayısı önceden bilindiğinde kullanışlıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "for döngüsü, bilinen sayıda tekrar için idealdir.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 401, .topicId = 22,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "for döngüsünün üç bölümü virgülle ayrılır.",
        .acceptedAnswers = {"2"},
        .explanation = "Üç bölüm virgülle değil, noktalı virgülle (;) ayrılır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 402, .topicId = 22,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i < 5; i++) döngüsü 5 kez çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "i, 0'dan 4'e kadar 5 değer alır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 403, .topicId = 22,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "for döngüsünde artırma/azaltma bölümü her turdan önce, koşuldan da önce çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "Sıralama: koşul kontrol edilir, gövde çalışır, sonra artırma/azaltma çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 404, .topicId = 22,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 10; i > 0; i--) döngüsü 10 kez çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "i, 10'dan 1'e kadar (10,9,...,1) 10 değer alır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 405, .topicId = 22,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "for döngüsünde sayaç değişkeni yalnızca int türünde olabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "Sayaç double, char gibi başka türlerde de olabilir; int en yaygın olanıdır ama zorunlu değildir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 406, .topicId = 22,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ (int i = 0; i < 5; i++) {\n    std::cout << i;\n}\nBelirli sayıda tekrar yapmak için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"for"},
        .explanation = "for anahtar kelimesi, belirli sayıda tekrar yapan döngüyü başlatır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 407, .topicId = 22,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i _____ 5; i++) ifadesinin döngüyü i 5'ten küçük olduğu sürece çalıştırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"<"},
        .explanation = "< operatörü küçüklük kontrolü yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 408, .topicId = 22,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i < 5; i_____) ifadesinin sayacı her turda 1 artırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "++ operatörü sayacı 1 artırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 409, .topicId = 22,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = _____; i <= 10; i++) ifadesinin 1'den 10'a kadar saymaya başlaması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"1"},
        .explanation = "Sayaç 1 değeriyle başlatılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 410, .topicId = 22,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 10; i _____ 0; i--) ifadesinin i sıfıra ulaşana kadar (dahil) çalışması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {">="},
        .explanation = ">= operatörü büyük veya eşit kontrolü yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 411, .topicId = 22,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 0; i < 20; i _____ 5) ifadesinin sayacı her turda 5 artırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"+="},
        .explanation = "+= operatörü sayacı belirtilen miktarda artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 412, .topicId = 22,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "_____\n    std::cout << i << \" \";\n1'den 5'e kadar sayıları yazdıran for satırını yazın.",
        .acceptedAnswers = {"for (int i = 1; i <= 5; i++) {"},
        .explanation = "1'den 5'e kadar saymak için i 1'den başlar ve i <= 5 koşuluyla artırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 413, .topicId = 22,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int toplam = 0;\n_____\n    toplam += i;\n0'dan 9'a kadar (9 dahil) sayıları toplam'a ekleyen for satırını yazın.",
        .acceptedAnswers = {"for (int i = 0; i <= 9; i++) {"},
        .explanation = "0'dan 9'a kadar (9 dahil) saymak için i <= 9 koşulu kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 414, .topicId = 22,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 4; i++) {\n    std::cout << i;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1234"},
        .explanation = "i 1'den 4'e kadar sırayla yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 415, .topicId = 22,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int toplam = 0;\nfor (int i = 1; i <= 4; i++) {\n    toplam += i;\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"10"},
        .explanation = "1 + 2 + 3 + 4 = 10.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 416, .topicId = 22,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nfor (int i = 0; i < 5; i++)\n    std::cout << i\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << i;"},
        .explanation = "Satırın sonunda noktalı virgül eksik.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 417, .topicId = 22,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nfor (int i = 0, i < 5, i++) {\n    std::cout << i;\n}\n\nProgramcı for döngüsünün üç bölümünü virgülle ayırmış ama bu geçersiz. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int i = 0; i < 5; i++) {"},
        .explanation = "for döngüsünün üç bölümü virgülle değil, noktalı virgülle ayrılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 418, .topicId = 22,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nfor (int i = 0; i < 5; i++);\n{\n    std::cout << i;\n}\n\nBu kod, döngü sayacı i'nin kapsamı (scope) for satırıyla birlikte bittiği için 'i': tanımsız tanımlayıcı hatasıyla derlenmiyor. Programcı 0'dan 4'e kadar yazdırmak istiyor. Düzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"for (int i = 0; i < 5; i++)"},
        .explanation = "for satırının sonundaki fazladan noktalı virgül, for'un gövdesini boş bir ifade yapar; bu durumda i'nin kapsamı yalnızca bu boş ifadeyle sınırlı kalır ve sonraki blok i'yi göremediği için derleme hatası oluşur. Noktalı virgülü kaldırmak, süslü parantezli bloğu gerçek döngü gövdesi yapar ve i'nin kapsamını genişletir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 419, .topicId = 22,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, 1'den 3'e kadar sayıları yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"}", "std::cout << i << \" \";", "for (int i = 1; i <= 3; i++) {"},
        .acceptedAnswers = {"3 2 1"},
        .explanation = "Önce for satırı (3), sonra yazdırma (2), en son kapanış (1): sıra 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 420, .topicId = 22,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "1'den 10'a kadar olan sayıları bir for döngüsü kullanarak ekrana yazdıran bir program yazın.",
        .acceptedAnswers = {"for", "cout", "<<"},
        .explanation = "Program bir for döngüsüyle 1'den 10'a kadar saymalı ve her sayıyı cout << ile yazdırmalıdır.",
        .baseXp = 40,
    });

    // Topic 23: while
    questions.push_back(Question{
        .id = 421, .topicId = 23,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "while döngüsü koşulu ne zaman kontrol eder?",
        .options = {"Her turdan sonra", "Her turdan önce", "Yalnızca ilk turdan önce", "Hiçbir zaman"},
        .acceptedAnswers = {"b"},
        .explanation = "while, koşulu her turdan önce kontrol eder.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 422, .topicId = 23,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "while (kosul) döngüsünde kosul başlangıçta false ise ne olur?",
        .options = {"Döngü bir kez çalışır, sonra durur", "Döngü hiç çalışmaz", "Sonsuz döngü oluşur", "Derleme hatası oluşur"},
        .acceptedAnswers = {"b"},
        .explanation = "Koşul başlangıçta false ise while döngüsü gövdesi hiç çalışmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 423, .topicId = 23,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "int i = 0; while (i < 3) { std::cout << i; i++; } kodunun çıktısı nedir?",
        .options = {"012", "123", "0123", "Sonsuz döngü"},
        .acceptedAnswers = {"a"},
        .explanation = "i sırasıyla 0, 1, 2 değerlerini alır ve yazdırılır; i=3 olduğunda koşul false olur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 424, .topicId = 23,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "while döngüsünde sayaç güncellemesi (örneğin i++) nerede yazılmalıdır?",
        .options = {"Döngü koşulunun içinde otomatik olarak yapılır", "Döngü gövdesi içinde, programcı tarafından elle yazılmalıdır", "Döngüden önce, bir kez", "Gerekli değildir"},
        .acceptedAnswers = {"b"},
        .explanation = "while'da (for'un aksine) sayaç güncellemesi otomatik değildir; gövde içinde elle yazılmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 425, .topicId = 23,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int i = 5; while (i > 0) { i--; } döngüsü kaç kez çalışır?",
        .options = {"4", "5", "6", "0"},
        .acceptedAnswers = {"b"},
        .explanation = "i sırasıyla 5,4,3,2,1 değerleriyle koşulu (i>0) sağlar ve her seferinde azalır; toplam 5 kez çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 426, .topicId = 23,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "while (true) { ... } yapısı ne anlama gelir?",
        .options = {"Hiç çalışmayan bir döngü", "Koşul hiçbir zaman true olamayan bir döngü", "Elle break veya benzeri bir çıkış olmadıkça sonsuza kadar çalışan bir döngü", "Yalnızca bir kez çalışan bir döngü"},
        .acceptedAnswers = {"c"},
        .explanation = "Koşul her zaman true olduğu için döngü, içeriden bir break olmadıkça sonsuza kadar çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 427, .topicId = 23,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int i = 10; while (i > 0) { std::cout << i; i -= 3; } döngüsünde kaç değer yazdırılır?",
        .options = {"3", "4", "5", "10"},
        .acceptedAnswers = {"b"},
        .explanation = "i sırasıyla 10, 7, 4, 1 değerleriyle yazdırılır (her biri i>0 iken); i=-2 olduğunda döngü durur. 4 değer yazdırılır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 428, .topicId = 23,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int i = 0; while (i < 5) { std::cout << i; } döngüsü hakkında ne söylenebilir (i'nin döngü içinde güncellenmediğine dikkat edin)?",
        .options = {"5 kez çalışır ve durur", "Hiç çalışmaz", "Sonsuza kadar çalışır (sonsuz döngü)", "Derleme hatası verir"},
        .acceptedAnswers = {"c"},
        .explanation = "i hiçbir zaman güncellenmediği için koşul (i<5) hep true kalır ve döngü sonsuza kadar çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 429, .topicId = 23,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "while döngüsü koşulu döngü gövdesinden önce kontrol eder.",
        .acceptedAnswers = {"1"},
        .explanation = "while, koşulu gövdeden önce kontrol eder.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 430, .topicId = 23,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "while döngüsü, koşul başlangıçta false ise en az bir kez çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "Koşul başlangıçta false ise while gövdesi hiç çalışmaz (bu do-while'dan farkıdır).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 431, .topicId = 23,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "while döngüsünde sayaç güncellemesini unutmak sonsuz döngüye yol açabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Koşul hiç değişmediği için döngü sonsuza kadar devam edebilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 432, .topicId = 23,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "int i = 0; while (i < 0) { std::cout << i; } döngüsü en az bir kez çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "i < 0 başlangıçta false olduğu için (0 < 0 false) döngü hiç çalışmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 433, .topicId = 23,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "while (true) yapısı, elle bir çıkış (break gibi) olmadıkça sonsuza kadar çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "Koşul her zaman true olduğu için elle bir çıkış olmadan döngü asla durmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 434, .topicId = 23,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "while döngüsü yalnızca sayısal koşullarla kullanılabilir, bool değişkenlerle kullanılamaz.",
        .acceptedAnswers = {"2"},
        .explanation = "while, bool değişkenlerle (örneğin while (devam)) de kullanılabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 435, .topicId = 23,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ (i < 5) {\n    std::cout << i;\n    i++;\n}\nKoşul true olduğu sürece tekrar etmek için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"while"},
        .explanation = "while anahtar kelimesi, koşul true olduğu sürece tekrar eder.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 436, .topicId = 23,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int i = 0; while (i _____ 5) { i++; } ifadesinin i 5'ten küçük olduğu sürece çalışması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"<"},
        .explanation = "< operatörü küçüklük kontrolü yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 437, .topicId = 23,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "int i = 0; while (i < 5) { std::cout << i; i_____; } ifadesinin sonsuz döngüye girmemesi için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "i++ olmadan koşul hiç değişmez ve döngü sonsuza kadar sürer.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 438, .topicId = 23,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int i = 10; while (i _____ 0) { i--; } ifadesinin i sıfırdan büyük olduğu sürece çalışması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {">"},
        .explanation = "> operatörü büyüklük kontrolü yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 439, .topicId = 23,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int tekrar = 0; while (tekrar < 3) {\n    std::cout << \"Merhaba\";\n    tekrar _____;\n}\ntekrar değişkenini her turda 1 artırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "tekrar++, tekrar'ı 1 artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 440, .topicId = 23,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "bool devam = _____; while (devam) { devam = false; } ifadesinin döngünün en az bir kez çalışması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"true"},
        .explanation = "devam true olmalı ki while koşulu ilk kontrolde sağlansın.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 441, .topicId = 23,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int i = 0;\n_____\n    std::cout << i;\n    i++;\n}\ni 5'ten küçük olduğu sürece çalışan while satırını yazın.",
        .acceptedAnswers = {"while (i < 5) {"},
        .explanation = "while (i < 5), i 5'ten küçük olduğu sürece döngüyü çalıştırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 442, .topicId = 23,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayac = 5;\nwhile (sayac > 0) {\n    std::cout << sayac;\n    _____\n}\nsayac'ı her turda 1 azaltan satırı yazın.",
        .acceptedAnswers = {"sayac--;"},
        .explanation = "sayac--, sayac'ı 1 azaltır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 443, .topicId = 23,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int i = 0;\nwhile (i < 3) {\n    std::cout << i;\n    i++;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"012"},
        .explanation = "i sırasıyla 0, 1, 2 değerleriyle yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 444, .topicId = 23,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int i = 5;\nwhile (i > 0) {\n    i -= 2;\n}\nstd::cout << i;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"-1"},
        .explanation = "i sırasıyla 5,3,1,-1 olur; i=-1 olduğunda koşul (i>0) false olur ve döngü durur. Son değer -1'dir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 445, .topicId = 23,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint i = 0;\nwhile (i < 5)\n    std::cout << i;\n    i++;\n\nProgramcı 0'dan 4'e kadar yazdırmak istiyor ama kod sonsuz döngüye giriyor (süslü parantez olmadığına dikkat edin). Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"while (i < 5) {"},
        .explanation = "Süslü parantez olmadan while yalnızca bir sonraki satırı kapsar; i++ döngü dışında kalır ve hiç çalışmaz, bu da sonsuz döngüye yol açar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 446, .topicId = 23,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint i = 10;\nwhile (i > 0)\n    i++;\n\nProgramcı i'yi azaltarak döngüyü bitirmek istiyor ama kod sonsuz döngüye giriyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"i--;"},
        .explanation = "i artırılırsa (i++) koşul (i>0) hiçbir zaman false olmaz; i azaltılmalıdır (i--).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 447, .topicId = 23,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint i = 0;\nwhile i < 5 {\n    std::cout << i;\n    i++;\n}\n\nDüzeltilmiş ikinci satırı yazın.",
        .acceptedAnswers = {"while (i < 5) {"},
        .explanation = "while koşulu parantez içine alınmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 448, .topicId = 23,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, 0'dan 2'ye kadar sayıları yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"}", "std::cout << i;\n    i++;", "while (i < 3) {", "int i = 0;"},
        .acceptedAnswers = {"4 3 2 1"},
        .explanation = "Önce değişken (4), sonra while satırı (3), gövde (2), en son kapanış (1): sıra 4 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 449, .topicId = 23,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan sıfırdan büyük bir sayı girene kadar tekrar tekrar sayı isteyen bir program yazın (while döngüsü kullanarak).",
        .acceptedAnswers = {"while", "cin", ">>", "cout", "<<"},
        .explanation = "Program while döngüsüyle kullanıcıdan tekrar tekrar sayı istemeli, sıfırdan büyük bir değer girilene kadar devam etmelidir.",
        .baseXp = 40,
    });

    // Topic 24: do-while
    questions.push_back(Question{
        .id = 450, .topicId = 24,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "do-while döngüsü koşulu ne zaman kontrol eder?",
        .options = {"Gövdeden önce", "Gövdeden sonra", "Hiçbir zaman", "Gövdeyle aynı anda"},
        .acceptedAnswers = {"b"},
        .explanation = "do-while, koşulu gövde çalıştıktan SONRA kontrol eder.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 451, .topicId = 24,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "do-while döngüsü en az kaç kez çalışır?",
        .options = {"0", "1", "2", "Koşula bağlı, 0 da olabilir"},
        .acceptedAnswers = {"b"},
        .explanation = "do-while gövdesi, koşul kontrol edilmeden önce en az bir kez çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 452, .topicId = 24,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "do { std::cout << \"Merhaba\"; } while (false); kodu kaç kez 'Merhaba' yazdırır?",
        .options = {"0", "1", "Sonsuz", "Derleme hatası"},
        .acceptedAnswers = {"b"},
        .explanation = "do-while gövdesi koşuldan bağımsız olarak en az bir kez çalışır; koşul false olduğu için ikinci tur olmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 453, .topicId = 24,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "do-while ile while arasındaki temel fark nedir?",
        .options = {"do-while asla çalışmaz", "do-while gövdeyi en az bir kez çalıştırır, while ise koşul false ise hiç çalıştırmayabilir", "İkisi arasında hiçbir fark yoktur", "while her zaman daha hızlıdır"},
        .acceptedAnswers = {"b"},
        .explanation = "do-while koşulu sonradan kontrol eder, bu yüzden gövde en az bir kez çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 454, .topicId = 24,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "int i = 0; do { std::cout << i; i++; } while (i < 3); kodunun çıktısı nedir?",
        .options = {"012", "0123", "123", "Sonsuz döngü"},
        .acceptedAnswers = {"a"},
        .explanation = "i sırasıyla 0, 1, 2 değerleriyle yazdırılır; i=3 olduğunda koşul false olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 455, .topicId = 24,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "do-while döngüsünün sözdiziminde while (kosul) satırının sonunda ne olmalıdır?",
        .options = {"Hiçbir şey", "Noktalı virgül (;)", "Süslü parantez ({})", "İki nokta (:)"},
        .acceptedAnswers = {"b"},
        .explanation = "do-while söz diziminde while (kosul)'un sonuna noktalı virgül konulmalıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 456, .topicId = 24,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int i = 10; do { std::cout << i; } while (i < 5); kodu kaç kez çalışır (i başlangıçta koşulu sağlamıyor)?",
        .options = {"0", "1", "5", "Sonsuz"},
        .acceptedAnswers = {"b"},
        .explanation = "Gövde önce çalışır (10 yazdırılır), sonra koşul (10<5) kontrol edilir; false olduğu için döngü durur. Toplam 1 kez çalışır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 457, .topicId = 24,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "Bir menü programında kullanıcıdan en az bir kez seçim almak isteniyor. Bu senaryo için hangi döngü en uygun tercihtir?",
        .options = {"for", "while", "do-while", "Hiçbiri, döngü gerekmez"},
        .acceptedAnswers = {"c"},
        .explanation = "do-while, gövdeyi en az bir kez çalıştırdığı için bu tür senaryolarda en uygun tercihtir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 458, .topicId = 24,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "do-while döngüsü, gövdesini en az bir kez çalıştırır.",
        .acceptedAnswers = {"1"},
        .explanation = "Koşul gövdeden sonra kontrol edildiği için gövde en az bir kez çalışır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 459, .topicId = 24,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "do-while döngüsü koşulu gövdeden önce kontrol eder.",
        .acceptedAnswers = {"2"},
        .explanation = "do-while koşulu gövdeden SONRA kontrol eder; bu while'dan farkıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 460, .topicId = 24,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "while (kosul); satırının sonunda noktalı virgül gereklidir (do-while'da).",
        .acceptedAnswers = {"1"},
        .explanation = "do-while söz diziminde while (kosul);'in sonunda noktalı virgül zorunludur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 461, .topicId = 24,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "do-while ile while, tamamen aynı şekilde çalışır ve aralarında hiçbir fark yoktur.",
        .acceptedAnswers = {"2"},
        .explanation = "do-while gövdeyi en az bir kez çalıştırırken, while koşul başlangıçta false ise hiç çalıştırmaz.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 462, .topicId = 24,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "do { ... } while (false); yapısı, gövdeyi tam olarak bir kez çalıştırır.",
        .acceptedAnswers = {"1"},
        .explanation = "Gövde önce çalışır, sonra koşul (false) kontrol edilip döngü durur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 463, .topicId = 24,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "do-while döngüsü, kullanıcıdan geçerli bir giriş alınana kadar tekrar sormak için uygundur.",
        .acceptedAnswers = {"1"},
        .explanation = "Kullanıcıdan en az bir kez giriş alınması gerektiği için do-while uygundur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 464, .topicId = 24,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "_____ {\n    std::cout << \"Merhaba\";\n} while (devam);\nGövdeyi en az bir kez çalıştıran döngü için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"do"},
        .explanation = "do anahtar kelimesi, do-while döngüsünün gövdesini başlatır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 465, .topicId = 24,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "do {\n    std::cout << i;\n    i++;\n} _____ (i < 5);\nKoşulu belirtmek için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"while"},
        .explanation = "while anahtar kelimesi, do-while döngüsünün koşulunu belirtir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 466, .topicId = 24,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "do {\n    std::cout << i;\n} while (i < 5)_____\nSatırı doğru bitirmek için boşluğa ne yazılmalı?",
        .acceptedAnswers = {";"},
        .explanation = "do-while'ın while (kosul) satırı noktalı virgülle bitmelidir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 467, .topicId = 24,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int i = 0; do { i++; } while (i _____ 3); ifadesinin döngüyü i 3'e ulaşana kadar çalıştırması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"<"},
        .explanation = "< operatörü küçüklük kontrolü yapar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 468, .topicId = 24,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int sayi;\ndo {\n    std::cout << \"Sayı girin: \";\n    std::cin >> sayi;\n} while (sayi _____ 0);\nKullanıcı pozitif bir sayı girene kadar tekrar sorması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"<="},
        .explanation = "sayi <= 0 iken tekrar sorulmalı; sayi pozitif olduğunda koşul false olur ve döngü durur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 469, .topicId = 24,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int i = 0;\ndo {\n    std::cout << i;\n    i_____;\n} while (i < 3);\ni'yi her turda 1 artırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"++"},
        .explanation = "i++, i'yi 1 artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 470, .topicId = 24,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int i = 0;\ndo {\n    std::cout << i;\n    i++;\n_____\ni 3'ten küçük olduğu sürece devam eden satırı yazın.",
        .acceptedAnswers = {"} while (i < 3);"},
        .explanation = "} while (i < 3);, gövdeyi kapatır ve koşulu belirtir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 471, .topicId = 24,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayi;\n_____\n    std::cout << \"Sayı girin: \";\n    std::cin >> sayi;\n} while (sayi <= 0);\nGövdeyi başlatan do satırını yazın.",
        .acceptedAnswers = {"do {"},
        .explanation = "do {, do-while döngüsünün gövdesini başlatır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 472, .topicId = 24,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "int i = 0;\ndo {\n    std::cout << i;\n    i++;\n} while (i < 3);\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"012"},
        .explanation = "i sırasıyla 0, 1, 2 değerleriyle yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 473, .topicId = 24,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int i = 5;\ndo {\n    std::cout << i;\n} while (i < 3);\nYukarıdaki kodun ekran çıktısı nedir? (i başlangıçta koşulu sağlamıyor)",
        .acceptedAnswers = {"5"},
        .explanation = "Gövde koşuldan bağımsız bir kez çalışır (5 yazdırılır); sonra koşul (5<3) false olduğu için döngü durur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 474, .topicId = 24,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint i = 0;\ndo {\n    std::cout << i;\n    i++;\n} while (i < 3)\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"} while (i < 3);"},
        .explanation = "do-while'ın while satırının sonunda noktalı virgül eksik.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 475, .topicId = 24,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nwhile {\n    std::cout << i;\n    i++;\n} do (i < 3);\n\nProgramcı bir do-while döngüsü yazmak istiyor ama do ve while'ın yerini karıştırmış. Gövdeyi başlatması gereken satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"do {"},
        .explanation = "do-while söz diziminde önce do { ... } gövdesi, sonra while (kosul); koşulu gelmelidir; sıra ters yazılmıştır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 476, .topicId = 24,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nint i = 0;\ndo {\n    std::cout << i;\n    i++;\n} while (i < 3)\n\nDüzeltilmiş son satırı yazın.",
        .acceptedAnswers = {"} while (i < 3);"},
        .explanation = "Satırın sonunda noktalı virgül eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 477, .topicId = 24,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, 0'dan 2'ye kadar sayıları yazdıran geçerli bir do-while programı oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"} while (i < 3);", "std::cout << i;\n    i++;", "do {", "int i = 0;"},
        .acceptedAnswers = {"4 3 2 1"},
        .explanation = "Önce değişken (4), sonra do satırı (3), gövde (2), en son while koşulu (1): sıra 4 3 2 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 478, .topicId = 24,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanıcıdan bir şifre okuyup, doğru şifre (örneğin 1234) girilene kadar tekrar tekrar soran bir program yazın (do-while döngüsü kullanarak, en az bir kez sorması gerektiğine dikkat edin).",
        .acceptedAnswers = {"do", "while", "cin", ">>", "cout", "<<"},
        .explanation = "Program do-while ile kullanıcıdan en az bir kez şifre istemeli, doğru şifre girilene kadar tekrar sormalıdır.",
        .baseXp = 40,
    });

    // Topic 25: break
    questions.push_back(Question{
        .id = 479, .topicId = 25,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "break ifadesi ne işe yarar?",
        .options = {"Döngüyü/switch'i anında sonlandırır", "Döngüyü bir tur atlar", "Fonksiyonu çağırır", "Değişken tanımlar"},
        .acceptedAnswers = {"a"},
        .explanation = "break, içinde bulunduğu döngüyü veya switch bloğunu anında sonlandırır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 480, .topicId = 25,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "break, iç içe döngülerde hangi döngüyü etkiler?",
        .options = {"Tüm döngüleri birden", "Yalnızca en dıştaki döngüyü", "Yalnızca içinde bulunduğu en yakın (innermost) döngüyü", "Hiçbirini"},
        .acceptedAnswers = {"c"},
        .explanation = "break yalnızca içinde bulunduğu en yakın döngüyü veya switch'i etkiler.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 481, .topicId = 25,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 1; i <= 10; i++) { if (i == 3) break; std::cout << i; } kodunun çıktısı nedir?",
        .options = {"12", "123", "1234567890", "3"},
        .acceptedAnswers = {"a"},
        .explanation = "i 1 ve 2 için yazdırılır; i=3 olduğunda break tetiklenir ve döngü yazdırmadan önce durur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 482, .topicId = 25,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "break kullanıldığında döngünün geri kalan turları çalışır mı?",
        .options = {"Evet, hepsi çalışır", "Hayır, döngü anında sonlanır", "Yalnızca bir tur daha çalışır", "Değişkene bağlıdır"},
        .acceptedAnswers = {"b"},
        .explanation = "break tetiklendiğinde döngü anında sonlanır, kalan turlar hiç çalışmaz.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 483, .topicId = 25,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "break, switch bloğunda ne işe yarar?",
        .options = {"Bir sonraki case'e atlar", "switch bloğundan çıkar", "Döngüyü başlatır", "Hiçbir işe yaramaz"},
        .acceptedAnswers = {"b"},
        .explanation = "break, switch bloğundan çıkışı sağlar (fall-through'u önler).",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 484, .topicId = 25,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 0; i < 5; i++) { if (i == 0) break; } döngüsü kaç kez tam olarak çalışır (break'in ilk turda tetiklendiğine dikkat edin)?",
        .options = {"0", "1", "5", "Sonsuz"},
        .acceptedAnswers = {"b"},
        .explanation = "Döngü ilk turda başlar (i=0), if koşulu hemen true olur ve break tetiklenir; toplamda 1 tur denenmiş olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 485, .topicId = 25,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "for (int i = 0; i < 3; i++) {\n    for (int j = 0; j < 3; j++) {\n        if (j == 1) break;\n        std::cout << i << j;\n    }\n}\nkodunun çıktısı nedir (break'in yalnızca iç döngüyü etkilediğine dikkat edin)?",
        .options = {"001020", "0", "000000", "012"},
        .acceptedAnswers = {"a"},
        .explanation = "Her dış tur (i=0,1,2) için iç döngü j=0'da bir kez yazdırır (i0), j=1'de break tetiklenir; sonuç '001020' olur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 486, .topicId = 25,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int sayi = 0; while (true) { sayi++; if (sayi == 5) break; } döngüsünden sonra sayi kaç olur?",
        .options = {"4", "5", "6", "Sonsuz döngü, program asla durmaz"},
        .acceptedAnswers = {"b"},
        .explanation = "sayi 1'den 5'e kadar artar; sayi 5 olduğunda break tetiklenir ve döngü durur. Son değer 5'tir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 487, .topicId = 25,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "break, içinde bulunduğu döngüyü veya switch'i anında sonlandırır.",
        .acceptedAnswers = {"1"},
        .explanation = "break'in işlevi tam olarak budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 488, .topicId = 25,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "break, tüm iç içe döngüleri birden sonlandırır.",
        .acceptedAnswers = {"2"},
        .explanation = "break yalnızca en yakın (innermost) döngüyü sonlandırır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 489, .topicId = 25,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "break kullanıldıktan sonra döngünün kalan turları çalışmaz.",
        .acceptedAnswers = {"1"},
        .explanation = "break, döngüyü anında sonlandırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 490, .topicId = 25,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "break yalnızca for döngülerinde kullanılabilir, while'da kullanılamaz.",
        .acceptedAnswers = {"2"},
        .explanation = "break, for, while, do-while ve switch bloklarının hepsinde kullanılabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 491, .topicId = 25,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İç içe döngülerde break, yalnızca en yakın (içteki) döngüyü sonlandırır.",
        .acceptedAnswers = {"1"},
        .explanation = "break, kapsamı yalnızca içinde bulunduğu en yakın döngüyle sınırlıdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 492, .topicId = 25,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "break, döngü sayacının (örneğin i) değerini sıfırlar.",
        .acceptedAnswers = {"2"},
        .explanation = "break yalnızca döngüden çıkışı sağlar; sayacın değerini değiştirmez.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 493, .topicId = 25,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i < 10; i++) {\n    if (i == 5) {\n        _____;\n    }\n    std::cout << i;\n}\ni 5 olduğunda döngüyü sonlandırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"break"},
        .explanation = "break, döngüyü anında sonlandırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 494, .topicId = 25,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "switch (x) {\n    case 1:\n        std::cout << \"Bir\";\n        _____;\n}\nswitch bloğundan çıkmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"break"},
        .explanation = "break, switch bloğundan çıkışı sağlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 495, .topicId = 25,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "while (true) {\n    sayac++;\n    if (sayac == 10) _____;\n}\nsayac 10 olduğunda sonsuz döngüyü sonlandırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"break"},
        .explanation = "break, sonsuz döngüyü sonlandırmanın standart yoludur.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 496, .topicId = 25,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 0; i < 100; i++) {\n    if (i _____ 20) {\n        break;\n    }\n}\ni 20'ye ulaştığında döngünün durması için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 497, .topicId = 25,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 100; i++) {\n    if (i * i > 50) {\n        _____;\n    }\n    std::cout << i;\n}\ni'nin karesi 50'yi geçtiğinde döngüyü durdurmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"break"},
        .explanation = "break, koşul sağlandığında döngüyü hemen sonlandırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 498, .topicId = 25,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int hedef = 7;\nfor (int i = 1; i <= 10; i++) {\n    if (i == hedef) {\n        std::cout << \"Bulundu\";\n        _____;\n    }\n}\nhedef bulunduğunda döngüyü sonlandırmak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"break"},
        .explanation = "hedef bulunduktan sonra döngüye devam etmenin bir anlamı olmadığı için break kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 499, .topicId = 25,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 0; i < 10; i++) {\n    _____\n    std::cout << i;\n}\ni 4'e ulaştığında döngüyü sonlandıran if+break satırlarını (tek satırda) yazın.",
        .acceptedAnswers = {"if (i == 4) break;"},
        .explanation = "if (i == 4) break;, i 4 olduğunda döngüyü sonlandırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 500, .topicId = 25,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int sayi;\nwhile (true) {\n    std::cin >> sayi;\n    _____\n}\nsayi 0 olduğunda sonsuz döngüyü sonlandıran if+break satırlarını (tek satırda) yazın.",
        .acceptedAnswers = {"if (sayi == 0) break;"},
        .explanation = "if (sayi == 0) break;, sayi 0 olduğunda döngüyü sonlandırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 501, .topicId = 25,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 10; i++) {\n    if (i == 4) {\n        break;\n    }\n    std::cout << i;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"123"},
        .explanation = "i 1, 2, 3 için yazdırılır; i=4 olduğunda break tetiklenir ve döngü durur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 502, .topicId = 25,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int i = 0;\nwhile (i < 10) {\n    i++;\n    if (i == 3) {\n        break;\n    }\n}\nstd::cout << i;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"3"},
        .explanation = "i sırasıyla 1, 2, 3 olur; i=3 olduğunda break tetiklenir. Son değer 3'tür.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 503, .topicId = 25,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nfor (int i = 0; i < 10; i++) {\n    if (i == 5)\n        breakk;\n    std::cout << i;\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"break;"},
        .explanation = "breakk geçerli bir anahtar kelime değildir; doğrusu break;'tir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 504, .topicId = 25,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint i = 0;\nfor (; i < 10; i++) {\n    if (i = 5) {\n        break;\n    }\n}\n\nProgramcı i'nin 5'e eşit olup olmadığını kontrol etmek istiyor ama kod her zaman döngüyü ilk turda sonlandırıyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"if (i == 5) {"},
        .explanation = "if (i = 5) bir atamadır; i'ye 5 atanır ve bu her zaman doğru (sıfır olmayan) sayıldığı için break hemen tetiklenir. Karşılaştırma için == kullanılmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 505, .topicId = 25,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nfor (int i = 0; i < 10; i++) {\n    if (i == 5)\n        brake;\n}\n\nDüzeltilmiş üçüncü satırı yazın.",
        .acceptedAnswers = {"break;"},
        .explanation = "brake geçerli bir anahtar kelime değildir; doğrusu break;'tir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 506, .topicId = 25,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, i 3'e ulaştığında break ile durup önceki sayıları yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"}", "if (i == 3) {\n        break;\n    }", "std::cout << i;", "for (int i = 0; i < 10; i++) {"},
        .acceptedAnswers = {"4 2 3 1"},
        .explanation = "Önce for satırı (4), if+break (2), yazdırma (3), en son kapanış (1): sıra 4 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 507, .topicId = 25,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "1'den 100'e kadar sayıları döngüyle yazdıran, ancak 10'a ulaştığında break ile döngüyü sonlandıran bir program yazın.",
        .acceptedAnswers = {"for", "break", "cout", "<<"},
        .explanation = "Program bir döngüde sayıları yazdırmalı ve 10'a ulaşıldığında break ile durmalıdır.",
        .baseXp = 40,
    });

    // Topic 26: continue
    questions.push_back(Question{
        .id = 508, .topicId = 26,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "continue ifadesi ne işe yarar?",
        .options = {"Döngüyü tamamen sonlandırır", "O turun geri kalanını atlayıp bir sonraki tura geçer", "Fonksiyonu çağırır", "Değişken tanımlar"},
        .acceptedAnswers = {"b"},
        .explanation = "continue, o turun geri kalanını atlayıp döngünün bir sonraki turuna geçer.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 509, .topicId = 26,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "continue ile break arasındaki temel fark nedir?",
        .options = {"Aralarında fark yoktur", "continue döngüyü sonlandırır, break bir sonraki tura geçer", "continue o turu atlar ve döngüye devam eder, break döngüyü tamamen sonlandırır", "continue yalnızca switch'te kullanılır"},
        .acceptedAnswers = {"c"},
        .explanation = "continue yalnızca o turu atlar, break ise döngüyü tamamen sonlandırır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 510, .topicId = 26,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 1; i <= 5; i++) { if (i == 3) continue; std::cout << i; } kodunun çıktısı nedir?",
        .options = {"1245", "12345", "12", "345"},
        .acceptedAnswers = {"a"},
        .explanation = "i=3 olduğunda continue tetiklenir ve yazdırma atlanır; diğer değerler (1,2,4,5) yazdırılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 511, .topicId = 26,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "for döngüsünde continue kullanıldığında artırma adımı (örneğin i++) çalışır mı?",
        .options = {"Evet, continue'dan sonra yine de çalışır", "Hayır, hiç çalışmaz", "Yalnızca son turda çalışır", "Sadece break ile birlikte çalışır"},
        .acceptedAnswers = {"a"},
        .explanation = "for döngüsünde continue tetiklendiğinde bile artırma adımı yine çalışır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 512, .topicId = 26,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 6; i++) { if (i % 2 == 0) continue; std::cout << i; } kodunun çıktısı nedir (çift sayılar atlanıyor)?",
        .options = {"135", "246", "123456", "135246"},
        .acceptedAnswers = {"a"},
        .explanation = "Çift sayılarda (2,4,6) continue tetiklenir; yalnızca tek sayılar (1,3,5) yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 513, .topicId = 26,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "while döngüsünde continue kullanırken nelere dikkat edilmelidir?",
        .options = {"Hiçbir şeye dikkat edilmesi gerekmez", "Koşulu güncelleyen kodun continue'dan önce çalıştığından emin olunmalı (aksi halde sonsuz döngü oluşabilir)", "continue while'da kullanılamaz", "continue otomatik olarak koşulu günceller"},
        .acceptedAnswers = {"b"},
        .explanation = "while'da (for'un aksine) artırma otomatik olmadığı için, güncelleme kodu continue'dan önce yazılmazsa sonsuz döngü oluşabilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 514, .topicId = 26,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "for (int i = 0; i < 5; i++) {\n    for (int j = 0; j < 3; j++) {\n        if (j == 1) continue;\n        std::cout << j;\n    }\n}\nkodunun her bir dış turda ürettiği çıktı nedir (j==1 atlanıyor)?",
        .options = {"02", "012", "0", "2"},
        .acceptedAnswers = {"a"},
        .explanation = "j=0 yazdırılır, j=1'de continue tetiklenir (atlanır), j=2 yazdırılır; her iç döngü turu '02' üretir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 515, .topicId = 26,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "int toplam = 0;\nfor (int i = 1; i <= 5; i++) {\n    if (i == 3) continue;\n    toplam += i;\n}\ntoplam kaç olur (3 atlandığı için)?",
        .options = {"12", "15", "9", "3"},
        .acceptedAnswers = {"a"},
        .explanation = "1+2+4+5 = 12 (3, continue ile atlandığı için toplama dahil edilmez).",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 516, .topicId = 26,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "continue, o turun geri kalanını atlayıp bir sonraki tura geçer.",
        .acceptedAnswers = {"1"},
        .explanation = "continue'nun işlevi tam olarak budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 517, .topicId = 26,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "continue, döngüyü tamamen sonlandırır (break gibi davranır).",
        .acceptedAnswers = {"2"},
        .explanation = "continue döngüyü sonlandırmaz, yalnızca o turu atlar.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 518, .topicId = 26,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "for döngüsünde continue'dan sonra artırma adımı (i++) yine de çalışır.",
        .acceptedAnswers = {"1"},
        .explanation = "for döngüsünde continue tetiklense bile artırma adımı çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 519, .topicId = 26,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "continue yalnızca for döngülerinde kullanılabilir.",
        .acceptedAnswers = {"2"},
        .explanation = "continue, while ve do-while döngülerinde de kullanılabilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 520, .topicId = 26,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "while döngüsünde continue'dan önce koşulu güncelleyen kod yazılmazsa sonsuz döngü oluşabilir.",
        .acceptedAnswers = {"1"},
        .explanation = "Güncelleme kodu continue tarafından atlanırsa koşul hiç değişmeyebilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 521, .topicId = 26,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "continue, switch bloğundan çıkmak için kullanılır.",
        .acceptedAnswers = {"2"},
        .explanation = "switch bloğundan çıkmak için break kullanılır, continue değil.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 522, .topicId = 26,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 1; i <= 10; i++) {\n    if (i % 2 == 0) {\n        _____;\n    }\n    std::cout << i;\n}\nçift sayıları atlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"continue"},
        .explanation = "continue, çift sayılarda o turu atlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 523, .topicId = 26,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i < 5; i++) {\n    if (i == 2) _____;\n    std::cout << i;\n}\ni 2 olduğunda o turu atlamak (yazdırmadan geçmek) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"continue"},
        .explanation = "continue, i=2 turunu atlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 524, .topicId = 26,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 1; i <= 5; i++) {\n    if (i _____ 3) continue;\n    std::cout << i;\n}\ni 3'e eşit olduğunda o turu atlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 525, .topicId = 26,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "int i = 0;\nwhile (i < 5) {\n    i++;\n    if (i == 2) continue;\n    std::cout << i;\n_____\nBoşluğa döngüyü kapatan karakteri yazın (i++ satırının sonsuz döngüye girmemek için continue'dan ÖNCE yazıldığına dikkat edin).",
        .acceptedAnswers = {"}"},
        .explanation = "i++ satırı continue'dan önce çalıştığı için sonsuz döngüye girilmez; döngü } ile kapanır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 526, .topicId = 26,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 20; i++) {\n    if (i _____ 5 == 0) continue;\n    std::cout << i;\n}\n5'in katlarını atlamak için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"%"},
        .explanation = "i % 5 == 0, i'nin 5'in katı olup olmadığını kontrol eder.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 527, .topicId = 26,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 10; i++) {\n    if (i == 1 _____ i == 10) continue;\n    std::cout << i;\n}\ni'nin 1 VEYA 10 olduğunda o turları atlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"||"},
        .explanation = "|| operatörü, iki koşuldan en az biri true olduğunda true döner.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 528, .topicId = 26,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 10; i++) {\n    _____\n    std::cout << i;\n}\ni tek sayıyken (yazdırmadan) o turu atlayan if+continue satırlarını (tek satırda) yazın.",
        .acceptedAnswers = {"if (i % 2 != 0) continue;"},
        .explanation = "if (i % 2 != 0) continue;, i tek olduğunda o turu atlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 529, .topicId = 26,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int toplam = 0;\nfor (int i = 1; i <= 10; i++) {\n    _____\n    toplam += i;\n}\ni 5'e eşitken o turu atlayan if+continue satırlarını (tek satırda) yazın.",
        .acceptedAnswers = {"if (i == 5) continue;"},
        .explanation = "if (i == 5) continue;, i 5 olduğunda toplama eklemeden o turu atlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 530, .topicId = 26,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 5; i++) {\n    if (i == 2) {\n        continue;\n    }\n    std::cout << i;\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"1345"},
        .explanation = "i=2'de continue tetiklenir ve yazdırma atlanır; diğer değerler (1,3,4,5) yazdırılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 531, .topicId = 26,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int toplam = 0;\nfor (int i = 1; i <= 6; i++) {\n    if (i % 3 == 0) {\n        continue;\n    }\n    toplam += i;\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"12"},
        .explanation = "3'ün katları (3, 6) atlanır; 1+2+4+5 = 12 toplanır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 532, .topicId = 26,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nfor (int i = 1; i <= 5; i++) {\n    if (i == 3)\n        continuee;\n    std::cout << i;\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"continue;"},
        .explanation = "continuee geçerli bir anahtar kelime değildir; doğrusu continue;'dir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 533, .topicId = 26,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nint i = 0;\nwhile (i < 5) {\n    if (i == 2) {\n        continue;\n    }\n    std::cout << i;\n    i++;\n}\n\nProgramcı i==2 olduğunda o turu atlamak istiyor ama kod i==2'de sonsuz döngüye giriyor çünkü i++ satırı continue'dan sonra yazılmış ve hiç çalışmıyor. i++ satırının çalışması için if bloğundan önceki hangi konuma taşınması gerekir? (taşınacak satırı yazın)",
        .acceptedAnswers = {"i++;"},
        .explanation = "i++, continue'dan önce (if kontrolünden önce) çalışmalıdır; aksi halde i==2 durumunda i hiç güncellenmeyip sonsuz döngü oluşur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 534, .topicId = 26,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nfor (int i = 1; i <= 5; i++) {\n    if (i == 3)\n        continue\n    std::cout << i;\n}\n\nDüzeltilmiş üçüncü satırı yazın.",
        .acceptedAnswers = {"continue;"},
        .explanation = "continue ifadesinin sonunda noktalı virgül eksik.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 535, .topicId = 26,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, i 2'ye eşitken atlayarak diğer sayıları yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"}", "if (i == 2) {\n        continue;\n    }", "std::cout << i;", "for (int i = 1; i <= 5; i++) {"},
        .acceptedAnswers = {"4 2 3 1"},
        .explanation = "Önce for satırı (4), if+continue (2), yazdırma (3), en son kapanış (1): sıra 4 2 3 1.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 536, .topicId = 26,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "1'den 20'ye kadar sayıları yazdıran, ancak 3'ün katı olan sayıları continue ile atlayan bir program yazın.",
        .acceptedAnswers = {"for", "continue", "%", "cout", "<<"},
        .explanation = "Program bir döngüde sayıları yazdırmalı, 3'ün katlarında continue ile o turu atlamalıdır.",
        .baseXp = 40,
    });

    // Topic 27: İç içe döngüler
    questions.push_back(Question{
        .id = 537, .topicId = 27,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::VeryEasy,
        .prompt = "İç içe döngü ne demektir?",
        .options = {"Bir döngünün içinde başka bir döngü olması", "İki döngünün art arda (sırayla) yazılması", "Bir döngünün iki kez çağrılması", "Bir fonksiyonun kendisini çağırması"},
        .acceptedAnswers = {"a"},
        .explanation = "İç içe döngü, bir döngünün gövdesine başka bir döngü yazılmasıdır.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 538, .topicId = 27,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i < 2; i++) { for (int j = 0; j < 3; j++) { ... } } yapısında iç döngü toplamda kaç kez çalışır?",
        .options = {"2", "3", "5", "6"},
        .acceptedAnswers = {"d"},
        .explanation = "Dış döngü 2 kez çalışır, her seferinde iç döngü 3 kez çalışır: 2*3 = 6.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 539, .topicId = 27,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "İç içe döngülerde dış döngünün her bir turunda ne olur?",
        .options = {"İç döngü baştan sona kadar tamamen çalışır", "İç döngü yalnızca bir kez çalışır", "İç döngü hiç çalışmaz", "Dış döngü durur"},
        .acceptedAnswers = {"a"},
        .explanation = "Dış döngünün her turunda, iç döngü baştan sona kadar tamamen çalışır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 540, .topicId = 27,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 3; i++) { for (int j = 1; j <= 2; j++) { std::cout << \"*\"; } } kodu kaç tane * yazdırır?",
        .options = {"3", "2", "5", "6"},
        .acceptedAnswers = {"d"},
        .explanation = "Dış döngü 3 kez, her seferinde iç döngü 2 kez çalışır: 3*2 = 6 yıldız.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 541, .topicId = 27,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "İç içe döngülerde iç döngünün sayaç değişkeni (örneğin i), dış döngünün sayaç değişkeniyle aynı isimde olursa ne olur?",
        .options = {"Derleme hatası oluşur, aynı isim hiçbir zaman kullanılamaz", "Yasaldır ama iç değişken dıştakini gölgeler (shadowing) ve karıştırılabilir; genelde farklı isimler (i, j) tercih edilir", "Derleyici otomatik olarak farklı isimlendirir", "Yalnızca while döngülerinde izin verilir"},
        .acceptedAnswers = {"b"},
        .explanation = "Aynı isimde iç içe değişken tanımlamak C++'ta yasaldır (iç değişken dıştakini 'gölgeler'), ancak karışıklığa yol açabileceği için genellikle farklı isimler (i, j gibi) tercih edilir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 542, .topicId = 27,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Medium,
        .prompt = "Bir matrisin (2 boyutlu dizi) tüm elemanlarını dolaşmak için genellikle kaç döngü gerekir?",
        .options = {"1", "2", "3", "Döngüye gerek yok"},
        .acceptedAnswers = {"b"},
        .explanation = "Bir matrisin satır ve sütunlarını dolaşmak için genellikle iç içe iki döngü kullanılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 543, .topicId = 27,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "for (int i = 0; i < 3; i++) {\n    for (int j = 0; j < 3; j++) {\n        if (j == i) break;\n        std::cout << \"*\";\n    }\n}\nkodu toplam kaç tane * yazdırır (break yalnızca iç döngüyü etkiler)?",
        .options = {"3", "6", "9", "0"},
        .acceptedAnswers = {"a"},
        .explanation = "i=0: j=0'da hemen break (0 yıldız). i=1: j=0'da yıldız, j=1'de break (1 yıldız). i=2: j=0,1'de yıldız, j=2'de break (2 yıldız). Toplam 0+1+2=3.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 544, .topicId = 27,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Hard,
        .prompt = "for (int i = 1; i <= 2; i++) {\n    for (int j = 1; j <= 2; j++) {\n        std::cout << i * j << \" \";\n    }\n}\nkodunun ekran çıktısı nedir?",
        .options = {"1 2 2 4 ", "1 2 3 4 ", "1 4 ", "2 4 "},
        .acceptedAnswers = {"a"},
        .explanation = "i=1: j=1(1*1=1), j=2(1*2=2). i=2: j=1(2*1=2), j=2(2*2=4). Çıktı: '1 2 2 4 '.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 545, .topicId = 27,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "İç içe döngü, bir döngünün içine başka bir döngü yazılmasıdır.",
        .acceptedAnswers = {"1"},
        .explanation = "İç içe döngünün tanımı budur.",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 546, .topicId = 27,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "İç içe döngülerde dış döngü her turunda iç döngü yalnızca bir kez çalışır.",
        .acceptedAnswers = {"2"},
        .explanation = "Dış döngünün her turunda iç döngü baştan sona kadar tamamen çalışır (bir kez değil).",
        .baseXp = 5,
    });
    questions.push_back(Question{
        .id = 547, .topicId = 27,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "İç içe döngülerin toplam tekrar sayısı, dış döngü tekrar sayısı ile iç döngü tekrar sayısının çarpımıdır (basit durumlarda).",
        .acceptedAnswers = {"1"},
        .explanation = "Basit (koşulsuz) iç içe döngülerde toplam tekrar sayısı dış*iç şeklinde hesaplanır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 548, .topicId = 27,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Easy,
        .prompt = "İç ve dış döngülerin sayaç değişkenleri aynı isimde (iç değişkenin dıştakini gölgelemesiyle) tanımlanabilir, ancak bu genellikle önerilmez.",
        .acceptedAnswers = {"1"},
        .explanation = "Bu yasal bir C++ kodudur (iç değişken dıştakini gölgeler), ancak okunabilirlik açısından farklı isimler (i, j gibi) kullanmak tercih edilir.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 549, .topicId = 27,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "İç içe döngüler, bir matrisin (2 boyutlu verinin) satır ve sütunlarını dolaşmak için sıkça kullanılır.",
        .acceptedAnswers = {"1"},
        .explanation = "Dış döngü satırları, iç döngü sütunları dolaşmak için tipik bir kullanımdır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 550, .topicId = 27,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::Medium,
        .prompt = "break, iç içe döngülerde hem iç hem dış döngüyü aynı anda sonlandırır.",
        .acceptedAnswers = {"2"},
        .explanation = "break yalnızca içinde bulunduğu en yakın (iç) döngüyü sonlandırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 551, .topicId = 27,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i < 2; i++) {\n    for (int _____ = 0; j < 3; j++) {\n        std::cout << \"*\";\n    }\n}\nİç döngünün sayaç değişkenini tanımlamak için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"j"},
        .explanation = "İç döngünün sayacı, koşulda kullanılan j ismiyle tanımlanmalıdır.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 552, .topicId = 27,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i < 3; i++) {\n    _____ (int j = 0; j < 3; j++) {\n        std::cout << i << j;\n    }\n}\nİkinci (iç) döngüyü başlatmak için boşluğa hangi anahtar kelime yazılmalı?",
        .acceptedAnswers = {"for"},
        .explanation = "İç döngü de bir for döngüsü olduğu için for anahtar kelimesiyle başlar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 553, .topicId = 27,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "for (int i = 0; i < 2; i++) {\n    for (int j = 0; j < 2; j++) {\n        std::cout << i _____ j;\n    }\n}\ni ile j'yi çarpmak için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"*"},
        .explanation = "* operatörü çarpma işlemi yapar.",
        .baseXp = 10,
    });
    questions.push_back(Question{
        .id = 554, .topicId = 27,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= _____; i++) {\n    for (int j = 1; j <= 3; j++) {\n        std::cout << \"*\";\n    }\n}\nDış döngünün 4 kez çalışması (toplam 4*3=12 yıldız) için boşluğa ne yazılmalı?",
        .acceptedAnswers = {"4"},
        .explanation = "Dış döngü 4 kez çalışırsa toplam yıldız sayısı 4*3=12 olur.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 555, .topicId = 27,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 0; i < 3; i++) {\n    for (int j = 0; j < 3; j++) {\n        if (i _____ j) {\n            std::cout << \"Köşegen\";\n        }\n    }\n}\nMatrisin köşegen elemanlarını (i ve j eşit olduğunda) bulmak için boşluğa hangi operatör yazılmalı?",
        .acceptedAnswers = {"=="},
        .explanation = "Eşitlik kontrolü == operatörüyle yapılır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 556, .topicId = 27,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 0; i < 2; i++) {\n    for (int j = 0; j < 2; j++) {\n        std::cout << \"(\" << i << \",\" << j << \")\";\n    }\n    std::cout << _____;\n}\nHer dış turdan sonra yeni bir satıra geçmek için boşluğa (tırnakla) ne yazılmalı?",
        .acceptedAnswers = {"\"\\n\""},
        .explanation = "\"\\n\" yeni satıra geçişi sağlar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 557, .topicId = 27,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 2; i++) {\n    _____\n        std::cout << \"*\";\n    }\n}\nİç döngüyü (1'den 3'e kadar) başlatan for satırını yazın.",
        .acceptedAnswers = {"for (int j = 1; j <= 3; j++) {"},
        .explanation = "İç döngü, 1'den 3'e kadar sayan bir for döngüsüdür.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 558, .topicId = 27,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Medium,
        .prompt = "int toplam = 0;\nfor (int i = 1; i <= 2; i++) {\n    for (int j = 1; j <= 2; j++) {\n        _____\n    }\n}\ntoplam değişkenine her adımda 1 ekleyen satırı yazın.",
        .acceptedAnswers = {"toplam += 1;", "toplam++;"},
        .explanation = "toplam += 1; veya toplam++; her adımda toplamı 1 artırır.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 559, .topicId = 27,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Medium,
        .prompt = "for (int i = 1; i <= 2; i++) {\n    for (int j = 1; j <= 2; j++) {\n        std::cout << \"*\";\n    }\n}\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"****"},
        .explanation = "Dış döngü 2 kez, iç döngü her seferinde 2 kez çalışır: 2*2=4 yıldız.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 560, .topicId = 27,
        .type = QuestionType::PredictOutput, .difficulty = Difficulty::Hard,
        .prompt = "int toplam = 0;\nfor (int i = 1; i <= 3; i++) {\n    for (int j = 1; j <= 2; j++) {\n        toplam++;\n    }\n}\nstd::cout << toplam;\nYukarıdaki kodun ekran çıktısı nedir?",
        .acceptedAnswers = {"6"},
        .explanation = "Dış döngü 3 kez, iç döngü her seferinde 2 kez çalışır: 3*2=6.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 561, .topicId = 27,
        .type = QuestionType::FindError, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nfor (int i = 0; i < 3; i++) {\n    for (int j = 0; j < 3; j++)\n        std::cout << i << j\n}\n\nHatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"std::cout << i << j;"},
        .explanation = "Satırın sonunda noktalı virgül eksik; her ifade noktalı virgülle bitmelidir.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 562, .topicId = 27,
        .type = QuestionType::FindError, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodda bir hata var:\n\nfor (int i = 0; i < 3; i++) {\n    for (int j = 0; j < 3; j++);\n        std::cout << i << j;\n}\n\nBu kod, iç döngünün sayacı j'nin kapsamı iç for satırıyla birlikte bittiği için 'j': tanımsız tanımlayıcı hatasıyla derlenmiyor. Programcı 9 çift (i,j) yazdırmak istiyor. Hatalı satırı düzeltilmiş haliyle yazın.",
        .acceptedAnswers = {"for (int j = 0; j < 3; j++)"},
        .explanation = "İç for satırının sonundaki fazladan noktalı virgül, döngünün gövdesini boş bir ifade yapar; bu durumda j'nin kapsamı yalnızca bu boş ifadeyle sınırlı kalır ve sonraki satır j'yi göremediği için derleme hatası oluşur.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 563, .topicId = 27,
        .type = QuestionType::FixCode, .difficulty = Difficulty::Hard,
        .prompt = "Aşağıdaki kodu düzeltin:\n\nfor (int i = 0; i < 2; i++)\n    for (int j = 0; j < 2; j++)\n        std::cout << i j;\n\nProgramcı i ve j'yi yan yana yazdırmak istiyor. Düzeltilmiş üçüncü satırı yazın.",
        .acceptedAnswers = {"std::cout << i << j;"},
        .explanation = "İki değeri art arda yazdırmak için aralarına << operatörü konulmalıdır.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 564, .topicId = 27,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Medium,
        .prompt = "Aşağıdaki satırları, iç içe döngüyle 2x3 yıldız yazdıran geçerli bir program oluşturacak şekilde sıralayın (numaraları boşlukla ayırarak yazın):",
        .options = {"for (int i = 0; i < 2; i++) {", "for (int j = 0; j < 3; j++) {", "std::cout << \"*\";", "    }\n}"},
        .acceptedAnswers = {"1 2 3 4"},
        .explanation = "Dış döngü (1), iç döngü (2), yıldız yazdırma (3), en son her iki döngünün kapanışı (4): sıra 1 2 3 4.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 565, .topicId = 27,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "İç içe iki döngü kullanarak 3x3'lük bir yıldız (*) karesi yazdıran bir program yazın (3 satır, her satırda 3 yıldız).",
        .acceptedAnswers = {"for", "cout", "<<"},
        .explanation = "Program iç içe iki for döngüsüyle 3 satır, her satırda 3 yıldız yazdırmalıdır.",
        .baseXp = 40,
    });
}

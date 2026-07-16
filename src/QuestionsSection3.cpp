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
        .prompt = "Aşağıdaki kodu düzeltin:\n\nfor (int i = 0; i < 5; i++);\n{\n    std::cout << i;\n}\n\nProgramcı 0'dan 4'e kadar yazdırmak istiyor ama kod hiçbir sayıyı doğru yazdırmıyor (i her zaman 5 olarak yazdırılıyor, bir kez). Düzeltilmiş ilk satırı yazın.",
        .acceptedAnswers = {"for (int i = 0; i < 5; i++)"},
        .explanation = "for satırının sonundaki fazladan noktalı virgül, döngünün gövdesini boş bir ifade yapar; asıl blok koşuldan bağımsız, döngü bittikten sonra (i=5 iken) bir kez çalışır.",
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
        .baseXp = 20,
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
}

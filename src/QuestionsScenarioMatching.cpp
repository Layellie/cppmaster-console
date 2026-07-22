#include "QuestionContent.h"

#include "Question.h"

// Scenario questions present a realistic situation and ask which tool fits;
// Matching questions pair concepts with their descriptions. Both are graded
// like their simpler cousins (Scenario as lettered multiple choice, Matching
// as an order-sensitive pair list), so nothing here needs new grading logic.
//
// Ids start at 2683, continuing after Section 10's last question (2682).
void appendScenarioAndMatchingQuestions(std::vector<Question>& questions) {
    // --- Scenario: choosing the right container / construct ---
    questions.push_back(Question{
        .id = 2683, .topicId = 34,
        .type = QuestionType::Scenario, .difficulty = Difficulty::Medium,
        .prompt = "Bir programda kullanıcıdan kaç sayı gireceğini önceden bilmiyorsun; "
                  "kullanıcı istediği kadar sayı girip bitirebiliyor. Bu sayıları saklamak "
                  "için aşağıdakilerden hangisi en uygundur?",
        .options = {
            "int dizi[100]; (sabit boyutlu dizi)",
            "std::vector<int>",
            "int tekSayi; (tek değişken)",
            "std::string",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Eleman sayısı çalışma zamanında belli olduğunda std::vector uygundur; "
                       "push_back ile büyür, sabit boyutlu dizide ise ya yer israfı olur ya da "
                       "taşma riski doğar.",
        .baseXp = 25,
    });
    questions.push_back(Question{
        .id = 2684, .topicId = 84,
        .type = QuestionType::Scenario, .difficulty = Difficulty::Medium,
        .prompt = "Öğrenci numarasına göre öğrenci adını hızlıca bulman gereken bir program "
                  "yazıyorsun. Numaralar sıralı olmak zorunda değil ve tekrar etmiyor. "
                  "Hangi veri yapısı bu iş için tasarlanmıştır?",
        .options = {
            "std::vector<std::string>",
            "std::map<int, std::string>",
            "std::stack<int>",
            "int dizisi",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Anahtar (numara) ile değere (ad) erişim gerektiğinde map kullanılır; "
                       "vector'de aramak için tüm elemanları gezmen gerekirdi.",
        .baseXp = 25,
    });
    questions.push_back(Question{
        .id = 2685, .topicId = 50,
        .type = QuestionType::Scenario, .difficulty = Difficulty::Hard,
        .prompt = "Bir klasör yapısını dolaşan bir fonksiyon yazıyorsun: her klasörün içinde "
                  "yine klasörler olabiliyor ve derinliğin ne kadar olduğu önceden belli "
                  "değil. Bu yapıyı işlemek için en doğal yaklaşım hangisidir?",
        .options = {
            "Tek bir for döngüsü",
            "Fonksiyonun kendini çağırması (recursion)",
            "switch-case yapısı",
            "Global değişken kullanmak",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Derinliği önceden bilinmeyen, kendi içinde tekrar eden (özyinelemeli) "
                       "yapılar recursion ile doğal biçimde işlenir.",
        .baseXp = 30,
    });
    questions.push_back(Question{
        .id = 2686, .topicId = 99,
        .type = QuestionType::Scenario, .difficulty = Difficulty::Medium,
        .prompt = "Kullanıcının girdiği metni sayıya çevirmen gerekiyor, ama kullanıcı harf de "
                  "girebilir ve bu durumda programın çökmemesi gerekiyor. Nasıl bir yapı "
                  "kullanmalısın?",
        .options = {
            "Hiçbir şey; hata olmaz",
            "try-catch bloğu ile dönüşümü sarmalamak",
            "Programı en başta sonlandırmak",
            "Değişkeni const yapmak",
        },
        .acceptedAnswers = {"b"},
        .explanation = "Çalışma zamanında oluşabilecek dönüşüm hataları istisna fırlatır; "
                       "try-catch ile yakalanınca program çökmek yerine kontrollü davranır.",
        .baseXp = 25,
    });

    // --- Matching: pairing concepts with what they actually do ---
    questions.push_back(Question{
        .id = 2687, .topicId = 34,
        .type = QuestionType::Matching, .difficulty = Difficulty::Medium,
        .prompt = "Soldaki vector fonksiyonlarını sağdaki açıklamalarla eşleştir.\n"
                  "a) Sona yeni eleman ekler\n"
                  "b) Eleman sayısını verir\n"
                  "c) Sondaki elemanı siler",
        .options = {"push_back()", "size()", "pop_back()"},
        .acceptedAnswers = {"1-a, 2-b, 3-c"},
        .explanation = "push_back sona ekler, size eleman sayısını döndürür, pop_back sondaki "
                       "elemanı çıkarır.",
        .baseXp = 25,
    });
    questions.push_back(Question{
        .id = 2688, .topicId = 8,
        .type = QuestionType::Matching, .difficulty = Difficulty::Easy,
        .prompt = "Soldaki veri tiplerini sağdaki örnek değerlerle eşleştir.\n"
                  "a) 'A'\n"
                  "b) 3.14\n"
                  "c) true\n"
                  "d) 42",
        .options = {"char", "double", "bool", "int"},
        .acceptedAnswers = {"1-a, 2-b, 3-c, 4-d"},
        .explanation = "char tek karakter ('A'), double ondalıklı sayı (3.14), bool mantıksal "
                       "değer (true), int tam sayı (42) tutar.",
        .baseXp = 20,
    });
    questions.push_back(Question{
        .id = 2689, .topicId = 91,
        .type = QuestionType::Matching, .difficulty = Difficulty::Hard,
        .prompt = "Soldaki STL algoritmalarını sağdaki görevleriyle eşleştir.\n"
                  "a) Elemanları sıralar\n"
                  "b) Elemanların sırasını tersine çevirir\n"
                  "c) Bir değeri arar\n"
                  "d) Elemanları toplar",
        .options = {"std::sort", "std::reverse", "std::find", "std::accumulate"},
        .acceptedAnswers = {"1-a, 2-b, 3-c, 4-d"},
        .explanation = "sort sıralar, reverse ters çevirir, find arar, accumulate toplama gibi "
                       "birikimli işlemler yapar.",
        .baseXp = 30,
    });
}

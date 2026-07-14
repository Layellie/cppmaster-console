#include <iostream>

#include "Question.h"
#include "QuizEngine.h"

int main() {
    QuizEngine engine;

    Question completeLine{
        .id = 901, .topicId = 6,
        .type = QuestionType::CompleteLine, .difficulty = Difficulty::Easy,
        .prompt = "int toplam = 10;\ntoplam = ______;",
        .acceptedAnswers = {"toplam + 5", "toplam+5"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "CompleteLine 'toplam + 5': "
              << (engine.evaluate(completeLine, "toplam + 5").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "CompleteLine 'toplam+5' (bosluksuz varyant): "
              << (engine.evaluate(completeLine, "toplam+5").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "CompleteLine 'TOPLAM + 5' (buyuk harf, yanlis olmali): "
              << (!engine.evaluate(completeLine, "TOPLAM + 5").correct ? "YANLIS (OK)" : "HATA") << '\n';
    std::cout << "CompleteLine '  toplam   +   5  ' (fazla bosluk, dogru olmali): "
              << (engine.evaluate(completeLine, "  toplam   +   5  ").correct ? "DOGRU (OK)" : "HATA") << '\n';

    Question findError{
        .id = 902, .topicId = 1,
        .type = QuestionType::FindError, .difficulty = Difficulty::Easy,
        .prompt = "int yas = 20\n\ncout << yas;",
        .acceptedAnswers = {"int yas = 20;"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "FindError dogru cevap: "
              << (engine.evaluate(findError, "int yas = 20;").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "FindError yanlis cevap (noktali virgul eksik): "
              << (!engine.evaluate(findError, "int yas = 20").correct ? "YANLIS (OK)" : "HATA") << '\n';

    Question orderCode{
        .id = 903, .topicId = 4,
        .type = QuestionType::OrderCode, .difficulty = Difficulty::Easy,
        .options = {"cout << yas;", "int yas;", "cin >> yas;"},
        .acceptedAnswers = {"2 3 1"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "OrderCode '2 3 1' (bosluklu): "
              << (engine.evaluate(orderCode, "2 3 1").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "OrderCode '2,3,1' (virgullu): "
              << (engine.evaluate(orderCode, "2,3,1").correct ? "DOGRU (OK)" : "HATA") << '\n';
    std::cout << "OrderCode '1 2 3' (yanlis sira): "
              << (!engine.evaluate(orderCode, "1 2 3").correct ? "YANLIS (OK)" : "HATA") << '\n';

    Question writeCode{
        .id = 904, .topicId = 6,
        .type = QuestionType::WriteCode, .difficulty = Difficulty::Hard,
        .prompt = "Kullanicidan bir tam sayi okuyup ekrana yazdiran bir program yaz.",
        .acceptedAnswers = {"cin", ">>", "cout", "<<"},
        .explanation = "test",
        .baseXp = 40,
    };
    const std::string goodSubmission = "int sayi;\ncin >> sayi;\ncout << sayi;";
    std::cout << "WriteCode tam gereksinimler: "
              << (engine.evaluate(writeCode, goodSubmission).correct ? "DOGRU (OK)" : "HATA") << '\n';
    const std::string missingCout = "int sayi;\ncin >> sayi;";
    std::cout << "WriteCode cout eksik: "
              << (!engine.evaluate(writeCode, missingCout).correct ? "YANLIS (OK)" : "HATA") << '\n';
    const std::string unbalanced = "int sayi;\ncin >> sayi;\ncout << (sayi;";
    std::cout << "WriteCode dengesiz parantez: "
              << (!engine.evaluate(writeCode, unbalanced).correct ? "YANLIS (OK)" : "HATA") << '\n';

    Question multipleChoice{
        .id = 905, .topicId = 1,
        .type = QuestionType::MultipleChoice, .difficulty = Difficulty::Easy,
        .prompt = "test",
        .options = {"cin", "cout", "endl", "return"},
        .acceptedAnswers = {"b"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "Regresyon MC 'B' (buyuk harf, case-insensitive dogru olmali): "
              << (engine.evaluate(multipleChoice, "B").correct ? "DOGRU (OK)" : "HATA") << '\n';

    Question trueFalseQuestion{
        .id = 906, .topicId = 1,
        .type = QuestionType::TrueFalse, .difficulty = Difficulty::VeryEasy,
        .prompt = "test",
        .acceptedAnswers = {"2"},
        .explanation = "test",
        .baseXp = 5,
    };
    std::cout << "Regresyon TF '2': "
              << (engine.evaluate(trueFalseQuestion, "2").correct ? "DOGRU (OK)" : "HATA") << '\n';

    Question fillBlank{
        .id = 907, .topicId = 1,
        .type = QuestionType::FillBlank, .difficulty = Difficulty::Easy,
        .prompt = "test",
        .acceptedAnswers = {"cout"},
        .explanation = "test",
        .baseXp = 10,
    };
    std::cout << "Regresyon FillBlank '  COUT  ' (bosluklu, buyuk harf, dogru olmali): "
              << (engine.evaluate(fillBlank, "  COUT  ").correct ? "DOGRU (OK)" : "HATA") << '\n';

    return 0;
}

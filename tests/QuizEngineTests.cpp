#include "QuizEngine.h"

#include <string>
#include <utility>
#include <vector>

#include "Settings.h"
#include "TestRunner.h"

namespace {

Question makeQuestion(
    QuestionType type, std::vector<std::string> acceptedAnswers, int baseXp = 10) {
    Question question;
    question.id = 1;
    question.topicId = 1;
    question.type = type;
    question.acceptedAnswers = std::move(acceptedAnswers);
    question.baseXp = baseXp;
    return question;
}

}  // namespace

TEST_CASE(QuizEngine_MultipleChoice_CaseInsensitiveMatch) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::MultipleChoice, {"b"});
    const AnswerResult result = engine.evaluate(question, "B");
    CHECK(result.correct);
    CHECK(result.xpAwarded == 10);
}

TEST_CASE(QuizEngine_MultipleChoice_WrongAnswerFails) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::MultipleChoice, {"b"});
    const AnswerResult result = engine.evaluate(question, "a");
    CHECK(!result.correct);
    CHECK(result.xpAwarded == 0);
}

TEST_CASE(QuizEngine_TrueFalse_CaseInsensitiveMatch) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::TrueFalse, {"1"});
    CHECK(engine.evaluate(question, " 1 ").correct);
}

TEST_CASE(QuizEngine_FillBlank_CaseInsensitiveMatch) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::FillBlank, {"cout"});
    CHECK(engine.evaluate(question, "COUT").correct);
}

TEST_CASE(QuizEngine_CompleteLine_CaseSensitiveWhitespaceCollapsed) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::CompleteLine, {"toplam + 5"});
    CHECK(engine.evaluate(question, "toplam   +   5").correct);
    CHECK(!engine.evaluate(question, "TOPLAM + 5").correct);
}

TEST_CASE(QuizEngine_PredictOutput_CaseSensitiveMatch) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::PredictOutput, {"8"});
    CHECK(engine.evaluate(question, "8").correct);
    CHECK(!engine.evaluate(question, "9").correct);
}

TEST_CASE(QuizEngine_FindError_CaseSensitiveMatch) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::FindError, {"int yas = 20;"});
    CHECK(engine.evaluate(question, "int yas = 20;").correct);
    CHECK(!engine.evaluate(question, "int Yas = 20;").correct);
}

TEST_CASE(QuizEngine_FixCode_CaseSensitiveMatch) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::FixCode, {"cin >> yas;"});
    CHECK(engine.evaluate(question, "cin >> yas;").correct);
}

TEST_CASE(QuizEngine_OrderCode_DigitSequenceToleratesSeparators) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::OrderCode, {"2 3 1"});
    CHECK(engine.evaluate(question, "2,3,1").correct);
    CHECK(engine.evaluate(question, "2 3 1").correct);
    CHECK(!engine.evaluate(question, "1 2 3").correct);
}

TEST_CASE(QuizEngine_WriteCode_RequiresAllSubstringsAndBalancedBrackets) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::WriteCode, {"cin", ">>", "cout", "<<"});
    CHECK(engine.evaluate(question, "int sayi;\ncin >> sayi;\ncout << sayi;").correct);
    CHECK(!engine.evaluate(question, "int sayi;\ncin >> sayi;").correct);

    const Question bracketQuestion = makeQuestion(QuestionType::WriteCode, {"cin"});
    CHECK(!engine.evaluate(bracketQuestion, "if (true) { cin >> x; cout << x;").correct);
}

TEST_CASE(QuizEngine_LenientCaseSensitivitySettingAcceptsDifferentCase) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::FindError, {"int yas = 20;"});
    Settings lenientSettings;
    lenientSettings.strictCaseSensitivity = false;
    CHECK(engine.evaluate(question, "int Yas = 20;", lenientSettings).correct);

    Settings strictSettings;
    CHECK(!engine.evaluate(question, "int Yas = 20;", strictSettings).correct);
}

TEST_CASE(QuizEngine_LenientWriteCodeToleranceAllowsOneMissingRequirement) {
    QuizEngine engine;
    const Question question =
        makeQuestion(QuestionType::WriteCode, {"cin", ">>", "cout", "<<"});
    Settings lenientSettings;
    lenientSettings.lenientWriteCodeTolerance = true;
    CHECK(engine.evaluate(question, "int sayi;\ncin >> sayi;\ncout << sayi;", lenientSettings)
              .correct);
    CHECK(engine.evaluate(question, "int sayi;\ncin >> sayi;\ncout sayi;", lenientSettings)
              .correct);
    CHECK(!engine.evaluate(question, "int sayi;", lenientSettings).correct);

    Settings strictSettings;
    CHECK(!engine.evaluate(question, "int sayi;\ncin >> sayi;", strictSettings).correct);
}

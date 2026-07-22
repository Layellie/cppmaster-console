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

TEST_CASE(QuizEngine_CorrectAnswerDisplayMatchesEvaluateOutput) {
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::FindError, {"int yas = 20;"});
    const AnswerResult wrongResult = engine.evaluate(question, "wrong answer");
    CHECK(engine.correctAnswerDisplay(question) == wrongResult.correctAnswerDisplay);
}

TEST_CASE(QuizEngine_AnswerResultExitRequestedDefaultsToFalse) {
    // Constructs AnswerResult directly, omitting exitRequested, so this
    // actually exercises the struct's default member initializer - calling
    // evaluate() instead would only prove its own hardcoded literal `false`,
    // not the default.
    const AnswerResult result{true, 10, "x"};
    CHECK(!result.exitRequested);
}

TEST_CASE(QuizEngine_Scenario_BehavesLikeMultipleChoice) {
    QuizEngine engine;
    Question question = makeQuestion(QuestionType::Scenario, {"c"});
    question.options = {"vector kullan", "dizi kullan", "map kullan", "set kullan"};

    CHECK(engine.evaluate(question, "c").correct);
    CHECK(engine.evaluate(question, "C").correct);
    CHECK(engine.evaluate(question, " c ").correct);
    CHECK(!engine.evaluate(question, "a").correct);

    // Scenario carries options, so the reveal names the option rather than
    // showing a bare letter.
    CHECK(engine.correctAnswerDisplay(question).find("map kullan") != std::string::npos);
}

TEST_CASE(QuizEngine_Matching_IgnoresPunctuationAndSpacingButNotOrder) {
    QuizEngine engine;
    Question question = makeQuestion(QuestionType::Matching, {"1-c, 2-a, 3-b"});
    question.options = {"vector", "int", "bool"};

    // Same pairs, different punctuation/spacing/case: all accepted.
    CHECK(engine.evaluate(question, "1-c, 2-a, 3-b").correct);
    CHECK(engine.evaluate(question, "1c2a3b").correct);
    CHECK(engine.evaluate(question, "1 - C ; 2 - A ; 3 - B").correct);

    // Wrong pairing rejected.
    CHECK(!engine.evaluate(question, "1-a, 2-c, 3-b").correct);
    // Reordered pairs are a different answer, not an equivalent one.
    CHECK(!engine.evaluate(question, "2-a, 1-c, 3-b").correct);
    // Empty input must never count as a match.
    CHECK(!engine.evaluate(question, "").correct);
    CHECK(!engine.evaluate(question, "   ").correct);
}

TEST_CASE(QuizEngine_ScenarioAndMatchingWereSilentlyAlwaysWrongBefore) {
    // Both types existed in the enum but fell through evaluate()'s default
    // branch, so a question of either type could never be answered
    // correctly. These assertions are the regression guard for that.
    QuizEngine engine;

    Question scenario = makeQuestion(QuestionType::Scenario, {"a"});
    scenario.options = {"evet", "hayır", "belki", "bilmiyorum"};
    CHECK(engine.evaluate(scenario, "a").correct);

    Question matching = makeQuestion(QuestionType::Matching, {"1-a"});
    matching.options = {"int"};
    CHECK(engine.evaluate(matching, "1-a").correct);
}

TEST_CASE(QuizEngine_MultipleChoice_AcceptsOptionNumberAsWellAsLetter) {
    QuizEngine engine;
    Question question = makeQuestion(QuestionType::MultipleChoice, {"b"});
    question.options = {"cin", "cout", "endl", "return"};

    // The letter it was authored with.
    CHECK(engine.evaluate(question, "b").correct);
    CHECK(engine.evaluate(question, "B").correct);
    // The option's position, which is what many learners type.
    CHECK(engine.evaluate(question, "2").correct);
    CHECK(engine.evaluate(question, " 2 ").correct);

    // Still wrong when it is the wrong option, in either notation.
    CHECK(!engine.evaluate(question, "a").correct);
    CHECK(!engine.evaluate(question, "1").correct);
    CHECK(!engine.evaluate(question, "3").correct);
    // Out of range digits must not be silently mapped onto some option.
    CHECK(!engine.evaluate(question, "5").correct);
    CHECK(!engine.evaluate(question, "0").correct);
}

TEST_CASE(QuizEngine_Scenario_AlsoAcceptsOptionNumber) {
    QuizEngine engine;
    Question question = makeQuestion(QuestionType::Scenario, {"c"});
    question.options = {"vector", "dizi", "map", "set"};
    CHECK(engine.evaluate(question, "c").correct);
    CHECK(engine.evaluate(question, "3").correct);
    CHECK(!engine.evaluate(question, "2").correct);
}

TEST_CASE(QuizEngine_TrueFalseDigitsKeepTheirOwnMeaning) {
    // TrueFalse is authored with "1"/"2" as the answers themselves, so the
    // option-number shortcut must not reinterpret them as letters.
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::TrueFalse, {"2"});
    CHECK(engine.evaluate(question, "2").correct);
    CHECK(!engine.evaluate(question, "1").correct);
}

TEST_CASE(QuizEngine_OrderCode_AcceptsDigitsWithOrWithoutSeparators) {
    QuizEngine engine;
    Question question = makeQuestion(QuestionType::OrderCode, {"3 2 1 4"});
    question.options = {"a", "b", "c", "d"};

    CHECK(engine.evaluate(question, "3 2 1 4").correct);
    // The same order typed without separators, which reads identically
    // while every step number is a single digit.
    CHECK(engine.evaluate(question, "3214").correct);
    CHECK(engine.evaluate(question, "3-2-1-4").correct);
    CHECK(engine.evaluate(question, "3,2,1,4").correct);
    CHECK(engine.evaluate(question, " 3 2 1 4 ").correct);

    // A genuinely different order is still wrong.
    CHECK(!engine.evaluate(question, "1234").correct);
    CHECK(!engine.evaluate(question, "3241").correct);
    CHECK(!engine.evaluate(question, "").correct);
}

TEST_CASE(QuizEngine_OrderCode_MultiDigitStepsStillNeedSeparators) {
    // Guards the collapse rule above: once a step number is two digits,
    // "1 12" and "11 2" are different answers that would both flatten to
    // "112", so the loose comparison must not apply.
    QuizEngine engine;
    const Question question = makeQuestion(QuestionType::OrderCode, {"1 12 3"});

    CHECK(engine.evaluate(question, "1 12 3").correct);
    CHECK(!engine.evaluate(question, "11 2 3").correct);
}

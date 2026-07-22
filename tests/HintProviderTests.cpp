#include "HintProvider.h"

#include <string>
#include <utility>
#include <vector>

#include "TestRunner.h"

namespace {

Question makeQuestion(
    QuestionType type, std::vector<std::string> acceptedAnswers,
    std::vector<std::string> options = {}, std::string explanation = "Test açıklaması.") {
    Question question;
    question.id = 1;
    question.topicId = 1;
    question.type = type;
    question.acceptedAnswers = std::move(acceptedAnswers);
    question.options = std::move(options);
    question.explanation = std::move(explanation);
    question.baseXp = 10;
    return question;
}

}  // namespace

TEST_CASE(HintProvider_Level3AlwaysReturnsExplanation) {
    const Question question = makeQuestion(QuestionType::FillBlank, {"cout"}, {}, "Açıklama metni.");
    CHECK(generateHint(question, 3) == "Açıklama metni.");
}

TEST_CASE(HintProvider_Level1And2And3AreMutuallyDistinct) {
    const Question question =
        makeQuestion(QuestionType::PredictOutput, {"8"}, {}, "Açıklama metni.");
    const std::string level1 = generateHint(question, 1);
    const std::string level2 = generateHint(question, 2);
    const std::string level3 = generateHint(question, 3);
    CHECK(level1 != level2);
    CHECK(level2 != level3);
    CHECK(level1 != level3);
}

TEST_CASE(HintProvider_MultipleChoiceLevel2NamesAWrongOption) {
    const Question question =
        makeQuestion(QuestionType::MultipleChoice, {"b"}, {"cin", "cout", "endl", "return"});
    const std::string hint = generateHint(question, 2);
    CHECK(hint.find("A)") != std::string::npos);
    CHECK(hint.find("cin") != std::string::npos);
}

TEST_CASE(HintProvider_FillBlankLevel2RevealsWordCount) {
    const Question question = makeQuestion(QuestionType::FillBlank, {"iostream kütüphanesi"});
    const std::string hint = generateHint(question, 2);
    CHECK(hint.find('2') != std::string::npos);
}

TEST_CASE(HintProvider_PredictOutputLevel2RevealsSignForNumericAnswer) {
    const Question positive = makeQuestion(QuestionType::PredictOutput, {"8"});
    CHECK(generateHint(positive, 2).find("pozitif") != std::string::npos);

    const Question negative = makeQuestion(QuestionType::PredictOutput, {"-3"});
    CHECK(generateHint(negative, 2).find("negatif") != std::string::npos);

    const Question textual = makeQuestion(QuestionType::PredictOutput, {"Merhaba"});
    CHECK(generateHint(textual, 2).find("kelime") != std::string::npos);
}

TEST_CASE(HintProvider_FindErrorLevel2RevealsFirstCharacter) {
    // Uses an accepted answer starting with 'd', a letter that does not
    // appear anywhere in the clue's fixed boilerplate ("Doğru satır '..'
    // harfiyle başlıyor.") other than inside the quotes - so this genuinely
    // pins down the first-character extraction instead of always passing.
    const Question question = makeQuestion(QuestionType::FindError, {"double x = 5.0;"});
    const std::string hint = generateHint(question, 2);
    CHECK(hint.find('d') != std::string::npos);
}

TEST_CASE(HintProvider_OrderCodeLevel2RevealsStepCount) {
    const Question question = makeQuestion(
        QuestionType::OrderCode, {"2 3 1"}, {"cout << yas;", "int yas;", "cin >> yas;"});
    const std::string hint = generateHint(question, 2);
    CHECK(hint.find('3') != std::string::npos);
}

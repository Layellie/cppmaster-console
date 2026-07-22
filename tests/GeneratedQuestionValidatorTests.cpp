#include "GeneratedQuestionValidator.h"

#include "TestRunner.h"

namespace {

GeneratedQuestion makeValidMultipleChoice() {
    GeneratedQuestion candidate;
    candidate.question.topicId = 6;
    candidate.question.type = QuestionType::MultipleChoice;
    candidate.question.prompt = "2 + 2 kactir?";
    candidate.question.options = {"3", "4", "5", "6"};
    candidate.question.acceptedAnswers = {"b"};
    candidate.question.baseXp = 20;
    return candidate;
}

GeneratedQuestion makeValidTrueFalse() {
    GeneratedQuestion candidate;
    candidate.question.topicId = 9;
    candidate.question.type = QuestionType::TrueFalse;
    candidate.question.prompt = "bool degeri true veya false olabilir.";
    candidate.question.acceptedAnswers = {"1"};
    candidate.question.baseXp = 10;
    return candidate;
}

}  // namespace

TEST_CASE(GeneratedQuestionValidator_ValidMultipleChoicePasses) {
    GeneratedQuestionValidator validator;
    CHECK(validator.isValid(makeValidMultipleChoice()));
}

TEST_CASE(GeneratedQuestionValidator_MultipleChoiceWrongOptionCountFails) {
    GeneratedQuestionValidator validator;
    auto candidate = makeValidMultipleChoice();
    candidate.question.options = {"3", "4", "5"};
    CHECK(!validator.isValid(candidate));
}

TEST_CASE(GeneratedQuestionValidator_MultipleChoiceOutOfRangeLetterFails) {
    GeneratedQuestionValidator validator;
    auto candidate = makeValidMultipleChoice();
    candidate.question.acceptedAnswers = {"e"};
    CHECK(!validator.isValid(candidate));
}

TEST_CASE(GeneratedQuestionValidator_ValidTrueFalsePasses) {
    GeneratedQuestionValidator validator;
    CHECK(validator.isValid(makeValidTrueFalse()));
}

TEST_CASE(GeneratedQuestionValidator_TrueFalseWithOptionsFails) {
    GeneratedQuestionValidator validator;
    auto candidate = makeValidTrueFalse();
    candidate.question.options = {"evet", "hayir"};
    CHECK(!validator.isValid(candidate));
}

TEST_CASE(GeneratedQuestionValidator_TrueFalseWithBadAnswerFails) {
    GeneratedQuestionValidator validator;
    auto candidate = makeValidTrueFalse();
    candidate.question.acceptedAnswers = {"3"};
    CHECK(!validator.isValid(candidate));
}

TEST_CASE(GeneratedQuestionValidator_EmptyPromptFails) {
    GeneratedQuestionValidator validator;
    auto candidate = makeValidMultipleChoice();
    candidate.question.prompt = "";
    CHECK(!validator.isValid(candidate));
}

TEST_CASE(GeneratedQuestionValidator_TopicIdZeroFails) {
    GeneratedQuestionValidator validator;
    auto candidate = makeValidMultipleChoice();
    candidate.question.topicId = 0;
    CHECK(!validator.isValid(candidate));
}

TEST_CASE(GeneratedQuestionValidator_TopicIdOneHundredOneFails) {
    GeneratedQuestionValidator validator;
    auto candidate = makeValidMultipleChoice();
    candidate.question.topicId = 101;
    CHECK(!validator.isValid(candidate));
}

TEST_CASE(GeneratedQuestionValidator_ZeroBaseXpFails) {
    GeneratedQuestionValidator validator;
    auto candidate = makeValidMultipleChoice();
    candidate.question.baseXp = 0;
    CHECK(!validator.isValid(candidate));
}

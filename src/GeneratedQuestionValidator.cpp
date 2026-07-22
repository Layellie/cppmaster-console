#include "GeneratedQuestionValidator.h"

#include "Enums.h"

bool GeneratedQuestionValidator::isValid(const GeneratedQuestion& candidate) const {
    const Question& question = candidate.question;

    if (question.prompt.empty()) {
        return false;
    }
    if (question.topicId < 1 || question.topicId > 100) {
        return false;
    }
    if (question.baseXp <= 0) {
        return false;
    }

    if (question.type == QuestionType::MultipleChoice) {
        if (question.options.size() != 4) {
            return false;
        }
        if (question.acceptedAnswers.size() != 1) {
            return false;
        }
        const std::string& answer = question.acceptedAnswers.front();
        return answer.size() == 1 && answer[0] >= 'a' && answer[0] <= 'd';
    }

    if (question.type == QuestionType::TrueFalse) {
        if (!question.options.empty()) {
            return false;
        }
        if (question.acceptedAnswers.size() != 1) {
            return false;
        }
        const std::string& answer = question.acceptedAnswers.front();
        return answer == "1" || answer == "2";
    }

    return !question.acceptedAnswers.empty();
}

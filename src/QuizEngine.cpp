#include "QuizEngine.h"

#include <cctype>
#include <cstddef>

namespace {

std::string trimAndLower(const std::string& text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = text.find_last_not_of(" \t\r\n");
    const std::string trimmed = text.substr(first, last - first + 1);

    std::string result;
    result.reserve(trimmed.size());
    for (const char character : trimmed) {
        result.push_back(static_cast<char>(
            std::tolower(static_cast<unsigned char>(character))));
    }
    return result;
}

std::string multipleChoiceDisplay(const Question& question) {
    const std::string& letter = question.acceptedAnswers.front();
    const auto index = static_cast<std::size_t>(letter.front() - 'a');
    if (index >= question.options.size()) {
        return letter;
    }
    const char upperLetter =
        static_cast<char>(std::toupper(static_cast<unsigned char>(letter.front())));
    return std::string(1, upperLetter) + ") " + question.options[index];
}

std::string trueFalseDisplay(const Question& question) {
    const std::string& digit = question.acceptedAnswers.front();
    return digit + (digit == "1" ? " (Doğru)" : " (Yanlış)");
}

std::string correctAnswerDisplayFor(const Question& question) {
    switch (question.type) {
        case QuestionType::MultipleChoice:
            return multipleChoiceDisplay(question);
        case QuestionType::TrueFalse:
            return trueFalseDisplay(question);
        default:
            return question.acceptedAnswers.empty() ? "" : question.acceptedAnswers.front();
    }
}

}  // namespace

AnswerResult QuizEngine::evaluate(const Question& question, const std::string& rawAnswer) const {
    const std::string normalizedAnswer = trimAndLower(rawAnswer);

    bool isCorrect = false;
    for (const std::string& accepted : question.acceptedAnswers) {
        if (normalizedAnswer == trimAndLower(accepted)) {
            isCorrect = true;
            break;
        }
    }

    return AnswerResult{
        isCorrect,
        isCorrect ? question.baseXp : 0,
        correctAnswerDisplayFor(question),
    };
}

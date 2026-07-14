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

std::string collapseWhitespace(const std::string& text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = text.find_last_not_of(" \t\r\n");
    const std::string trimmed = text.substr(first, last - first + 1);

    std::string result;
    result.reserve(trimmed.size());
    bool previousWasSpace = false;
    for (const char character : trimmed) {
        const bool isSpace =
            character == ' ' || character == '\t' || character == '\r' || character == '\n';
        if (isSpace) {
            if (!previousWasSpace) {
                result.push_back(' ');
            }
            previousWasSpace = true;
        } else {
            result.push_back(character);
            previousWasSpace = false;
        }
    }
    return result;
}

std::string extractDigitSequence(const std::string& text) {
    std::string result;
    std::string currentToken;
    for (const char character : text) {
        if (std::isdigit(static_cast<unsigned char>(character))) {
            currentToken.push_back(character);
        } else if (!currentToken.empty()) {
            if (!result.empty()) {
                result.push_back(' ');
            }
            result += currentToken;
            currentToken.clear();
        }
    }
    if (!currentToken.empty()) {
        if (!result.empty()) {
            result.push_back(' ');
        }
        result += currentToken;
    }
    return result;
}

bool isBalanced(const std::string& code) {
    int parenDepth = 0;
    int braceDepth = 0;
    for (const char character : code) {
        switch (character) {
            case '(':
                ++parenDepth;
                break;
            case ')':
                --parenDepth;
                if (parenDepth < 0) {
                    return false;
                }
                break;
            case '{':
                ++braceDepth;
                break;
            case '}':
                --braceDepth;
                if (braceDepth < 0) {
                    return false;
                }
                break;
            default:
                break;
        }
    }
    return parenDepth == 0 && braceDepth == 0;
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

bool matchesAnyAcceptedCaseInsensitive(const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer = trimAndLower(rawAnswer);
    for (const std::string& accepted : question.acceptedAnswers) {
        if (normalizedAnswer == trimAndLower(accepted)) {
            return true;
        }
    }
    return false;
}

bool matchesAnyAcceptedCaseSensitiveWhitespaceNormalized(
    const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer = collapseWhitespace(rawAnswer);
    for (const std::string& accepted : question.acceptedAnswers) {
        if (normalizedAnswer == collapseWhitespace(accepted)) {
            return true;
        }
    }
    return false;
}

bool matchesOrderCode(const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer = extractDigitSequence(rawAnswer);
    for (const std::string& accepted : question.acceptedAnswers) {
        if (normalizedAnswer == extractDigitSequence(accepted)) {
            return true;
        }
    }
    return false;
}

bool matchesWriteCode(const Question& question, const std::string& rawAnswer) {
    if (!isBalanced(rawAnswer)) {
        return false;
    }
    for (const std::string& required : question.acceptedAnswers) {
        if (rawAnswer.find(required) == std::string::npos) {
            return false;
        }
    }
    return true;
}

std::string writeCodeRequirementsDisplay(const Question& question) {
    std::string result = "Gerekli öğeler: ";
    for (std::size_t index = 0; index < question.acceptedAnswers.size(); ++index) {
        if (index > 0) {
            result += ", ";
        }
        result += question.acceptedAnswers[index];
    }
    return result;
}

}  // namespace

AnswerResult QuizEngine::evaluate(const Question& question, const std::string& rawAnswer) const {
    bool isCorrect = false;
    std::string display;

    switch (question.type) {
        case QuestionType::MultipleChoice:
        case QuestionType::TrueFalse:
        case QuestionType::FillBlank:
            isCorrect = matchesAnyAcceptedCaseInsensitive(question, rawAnswer);
            display = correctAnswerDisplayFor(question);
            break;
        case QuestionType::CompleteLine:
        case QuestionType::PredictOutput:
        case QuestionType::FindError:
        case QuestionType::FixCode:
            isCorrect = matchesAnyAcceptedCaseSensitiveWhitespaceNormalized(question, rawAnswer);
            display = question.acceptedAnswers.empty() ? "" : question.acceptedAnswers.front();
            break;
        case QuestionType::OrderCode:
            isCorrect = matchesOrderCode(question, rawAnswer);
            display = question.acceptedAnswers.empty() ? "" : question.acceptedAnswers.front();
            break;
        case QuestionType::WriteCode:
            isCorrect = matchesWriteCode(question, rawAnswer);
            display = writeCodeRequirementsDisplay(question);
            break;
        default:
            break;
    }

    return AnswerResult{isCorrect, isCorrect ? question.baseXp : 0, display};
}

#include "QuizEngine.h"

#include <algorithm>
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

std::string lowerAscii(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    for (const char character : text) {
        result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(character))));
    }
    return result;
}

std::string extractDigitSequence(const std::string& text) {
    std::string result;
    std::string currentToken;
    for (const char character : text) {
        if (std::isdigit(static_cast<unsigned char>(character)) != 0) {
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
        // Scenario carries the same lettered options, so it gets the same
        // "b) <option text>" display rather than a bare letter.
        case QuestionType::Scenario:
            return multipleChoiceDisplay(question);
        case QuestionType::TrueFalse:
            return trueFalseDisplay(question);
        default:
            return question.acceptedAnswers.empty() ? "" : question.acceptedAnswers.front();
    }
}

bool matchesAnyAcceptedCaseInsensitive(const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer = trimAndLower(rawAnswer);
    return std::ranges::any_of(question.acceptedAnswers, [&](const std::string& accepted) {
        return normalizedAnswer == trimAndLower(accepted);
    });
}

// Lettered questions are authored with "a".."d", but learners routinely
// answer with the option's position instead ("2" for B) — the two notations
// mean the same thing and the screen shows both a letter and an ordered
// list. Digits outside the option range are left alone so they simply stay
// wrong rather than being mapped onto some unrelated option.
std::string letterForOptionNumber(const Question& question, const std::string& normalizedAnswer) {
    if (normalizedAnswer.size() != 1) {
        return normalizedAnswer;
    }
    const char character = normalizedAnswer.front();
    if (character < '1' || character > '9') {
        return normalizedAnswer;
    }
    const auto index = static_cast<std::size_t>(character - '1');
    if (index >= question.options.size()) {
        return normalizedAnswer;
    }
    const char letter = static_cast<char>('a' + static_cast<int>(index));
    // NOLINTNEXTLINE(modernize-return-braced-init-list): the braced form is
    // wrong here — std::string{1, 'b'} selects the initializer_list<char>
    // constructor and yields the two-character string "\x01b", not "b".
    return std::string(1, letter);
}

// Used for MultipleChoice and Scenario only. TrueFalse deliberately keeps
// the plain comparison: its accepted answers *are* "1" and "2", so treating
// those digits as option numbers would change their meaning.
bool matchesLetteredChoice(const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer =
        letterForOptionNumber(question, trimAndLower(rawAnswer));
    return std::ranges::any_of(question.acceptedAnswers, [&](const std::string& accepted) {
        return normalizedAnswer == trimAndLower(accepted);
    });
}

bool matchesAnyAcceptedCaseSensitiveWhitespaceNormalized(
    const Question& question, const std::string& rawAnswer, bool strictCaseSensitivity) {
    std::string normalizedAnswer = collapseWhitespace(rawAnswer);
    if (!strictCaseSensitivity) {
        normalizedAnswer = lowerAscii(normalizedAnswer);
    }
    for (const std::string& accepted : question.acceptedAnswers) {
        std::string normalizedAccepted = collapseWhitespace(accepted);
        if (!strictCaseSensitivity) {
            normalizedAccepted = lowerAscii(normalizedAccepted);
        }
        if (normalizedAnswer == normalizedAccepted) {
            return true;
        }
    }
    return false;
}

// Matching answers pair a numbered left-hand item with a lettered
// right-hand one, e.g. "1-c, 2-a, 3-b". Learners write these many
// different ways ("1c 2a 3b", "1 - C; 2 - A"), and none of that
// punctuation carries meaning, so everything except the alphanumerics is
// dropped and the rest is lowercased before comparing. Order is preserved
// deliberately: the pairs are read in the order the left column is
// presented, so "1-c,2-a" and "2-a,1-c" are not treated as the same
// answer.
std::string normalizeMatchingPairs(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    for (const char character : text) {
        if (std::isalnum(static_cast<unsigned char>(character)) != 0) {
            result.push_back(
                static_cast<char>(std::tolower(static_cast<unsigned char>(character))));
        }
    }
    return result;
}

bool matchesMatching(const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer = normalizeMatchingPairs(rawAnswer);
    if (normalizedAnswer.empty()) {
        return false;
    }
    return std::ranges::any_of(question.acceptedAnswers, [&](const std::string& accepted) {
        return normalizedAnswer == normalizeMatchingPairs(accepted);
    });
}

// True when a tokenised sequence is entirely single-digit steps, e.g.
// "3 2 1 4". Only then can separators be dropped without ambiguity: with a
// two-digit step, "1 12" and "11 2" would both flatten to "112".
bool allStepsAreSingleDigit(const std::string& tokenized) {
    std::size_t runLength = 0;
    for (const char character : tokenized) {
        if (character == ' ') {
            runLength = 0;
            continue;
        }
        ++runLength;
        if (runLength > 1) {
            return false;
        }
    }
    return true;
}

std::string withoutSeparators(const std::string& tokenized) {
    std::string result;
    result.reserve(tokenized.size());
    for (const char character : tokenized) {
        if (character != ' ') {
            result.push_back(character);
        }
    }
    return result;
}

bool matchesOrderCode(const Question& question, const std::string& rawAnswer) {
    const std::string normalizedAnswer = extractDigitSequence(rawAnswer);
    if (normalizedAnswer.empty()) {
        return false;
    }
    return std::ranges::any_of(question.acceptedAnswers, [&](const std::string& accepted) {
        const std::string normalizedAccepted = extractDigitSequence(accepted);
        if (normalizedAnswer == normalizedAccepted) {
            return true;
        }
        // "3214" should be accepted for "3 2 1 4" — the separators carry no
        // meaning while every step is a single digit.
        if (allStepsAreSingleDigit(normalizedAccepted)) {
            return withoutSeparators(normalizedAnswer) == withoutSeparators(normalizedAccepted);
        }
        return false;
    });
}

bool matchesWriteCode(
    const Question& question, const std::string& rawAnswer, bool lenientWriteCodeTolerance) {
    if (!isBalanced(rawAnswer)) {
        return false;
    }
    int missingCount = 0;
    for (const std::string& required : question.acceptedAnswers) {
        if (rawAnswer.find(required) == std::string::npos) {
            ++missingCount;
        }
    }
    const int allowedMissing = lenientWriteCodeTolerance ? 1 : 0;
    return missingCount <= allowedMissing;
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

std::string computeCorrectAnswerDisplay(const Question& question) {
    switch (question.type) {
        case QuestionType::MultipleChoice:
        case QuestionType::TrueFalse:
        case QuestionType::FillBlank:
        case QuestionType::Scenario:
            return correctAnswerDisplayFor(question);
        case QuestionType::WriteCode:
            return writeCodeRequirementsDisplay(question);
        case QuestionType::CompleteLine:
        case QuestionType::PredictOutput:
        case QuestionType::FindError:
        case QuestionType::FixCode:
        case QuestionType::OrderCode:
        case QuestionType::Matching:
            return question.acceptedAnswers.empty() ? "" : question.acceptedAnswers.front();
    }
    return "";
}

}  // namespace

AnswerResult QuizEngine::evaluate(
    const Question& question, const std::string& rawAnswer, const Settings& settings) const {
    bool isCorrect = false;

    switch (question.type) {
        // Scenario is a situational multiple-choice question: the prompt
        // sets up a real-world case, but the answer is still a letter.
        case QuestionType::MultipleChoice:
        case QuestionType::Scenario:
            isCorrect = matchesLetteredChoice(question, rawAnswer);
            break;
        case QuestionType::TrueFalse:
        case QuestionType::FillBlank:
            isCorrect = matchesAnyAcceptedCaseInsensitive(question, rawAnswer);
            break;
        case QuestionType::Matching:
            isCorrect = matchesMatching(question, rawAnswer);
            break;
        case QuestionType::CompleteLine:
        case QuestionType::PredictOutput:
        case QuestionType::FindError:
        case QuestionType::FixCode:
            isCorrect = matchesAnyAcceptedCaseSensitiveWhitespaceNormalized(
                question, rawAnswer, settings.strictCaseSensitivity);
            break;
        case QuestionType::OrderCode:
            isCorrect = matchesOrderCode(question, rawAnswer);
            break;
        case QuestionType::WriteCode:
            isCorrect = matchesWriteCode(question, rawAnswer, settings.lenientWriteCodeTolerance);
            break;
        default:
            break;
    }

    return AnswerResult{
        isCorrect, isCorrect ? question.baseXp : 0, computeCorrectAnswerDisplay(question), false};
}

std::string QuizEngine::correctAnswerDisplay(const Question& question) const {
    return computeCorrectAnswerDisplay(question);
}

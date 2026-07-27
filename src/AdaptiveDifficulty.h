#pragma once

#include <cctype>
#include <cstddef>
#include <string>
#include <vector>

#include "Question.h"

namespace adaptive_detail {

[[nodiscard]] inline std::string lowerCopy(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    for (const char character : text) {
        result.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(character))));
    }
    return result;
}

// Reduces an answer to just its lowercase alphanumerics, so that the same
// subject written differently still compares equal — "<iostream>" and
// "iostream", for instance.
[[nodiscard]] inline std::string answerKey(const std::string& text) {
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

// What a question is really *about*, for the purpose of spotting a repeat.
//
// For lettered questions the stored answer is a bare "b", which says nothing
// about the subject; the option text is what the learner reads and recalls,
// so that is what gets compared.
[[nodiscard]] inline std::string primaryAnswerOf(const Question& question) {
    if (question.acceptedAnswers.empty()) {
        return {};
    }
    const std::string& answer = question.acceptedAnswers.front();
    const bool isLettered =
        question.type == QuestionType::MultipleChoice || question.type == QuestionType::Scenario;
    if (isLettered && answer.size() == 1 && answer.front() >= 'a' && answer.front() <= 'z') {
        const auto index = static_cast<std::size_t>(answer.front() - 'a');
        if (index < question.options.size()) {
            return answerKey(question.options[index]);
        }
    }
    return answerKey(answer);
}

// True when two answers cover the same ground. Containment counts, not just
// equality, so "int" and "int yas = 20;" are recognised as the same subject;
// the length floor keeps one- or two-letter answers from matching everything.
[[nodiscard]] inline bool answersOverlap(const std::string& left, const std::string& right) {
    if (left.empty() || right.empty()) {
        return false;
    }
    if (left == right) {
        return true;
    }
    const std::string& shorter = left.size() <= right.size() ? left : right;
    const std::string& longer = left.size() <= right.size() ? right : left;
    constexpr std::size_t kMinimumMeaningfulLength = 3;
    return shorter.size() >= kMinimumMeaningfulLength &&
           longer.find(shorter) != std::string::npos;
}

// How undesirable it is to ask `candidate` right after `previous`.
//
// A repeated answer is weighted heaviest on purpose: a topic often carries
// several questions about the same fact in different forms (a multiple
// choice whose answer is "cout" and a fill-in-the-blank whose answer is
// also "cout"). Asked back to back they teach nothing — the second is
// answered by copying the line above — even though their *types* differ,
// which is why type alone is not a sufficient signal.
[[nodiscard]] inline int repetitionPenalty(const Question& candidate, const Question& previous) {
    int penalty = 0;
    if (candidate.type == previous.type) {
        penalty += 1;
    }
    if (answersOverlap(primaryAnswerOf(candidate), primaryAnswerOf(previous))) {
        penalty += 2;
    }
    return penalty;
}

}  // namespace adaptive_detail

// `remaining` must already be sorted ascending by `difficulty` (the
// caller's responsibility, done once at quiz start). Returns the index
// (into `remaining`) of which question to ask next.
//
// When `lastAsked` is supplied, the choice is refined *within the same
// difficulty* as the question that would have been picked anyway, so
// avoiding a repetitive pairing can never override the adaptive difficulty
// decision — it only breaks ties among equally hard questions.
[[nodiscard]] inline std::size_t selectNextQuestionIndex(
    const std::vector<Question>& remaining, int correctStreak, int wrongStreak,
    const Question* lastAsked = nullptr) {
    (void)wrongStreak;
    if (remaining.empty()) {
        return 0;
    }

    const bool takeHardest = correctStreak >= 2 && remaining.size() > 1;
    const std::size_t naturalIndex = takeHardest ? remaining.size() - 1 : 0;
    if (lastAsked == nullptr) {
        return naturalIndex;
    }

    const Difficulty targetDifficulty = remaining[naturalIndex].difficulty;
    std::size_t bestIndex = naturalIndex;
    int bestPenalty = adaptive_detail::repetitionPenalty(remaining[naturalIndex], *lastAsked);

    // Walk outward from the natural pick across its difficulty band only.
    // Ties keep the natural pick, since only a strictly lower penalty wins.
    for (std::size_t step = 0; step < remaining.size() && bestPenalty > 0; ++step) {
        const std::size_t index = takeHardest ? remaining.size() - 1 - step : step;
        if (remaining[index].difficulty != targetDifficulty) {
            break;
        }
        const int penalty = adaptive_detail::repetitionPenalty(remaining[index], *lastAsked);
        if (penalty < bestPenalty) {
            bestPenalty = penalty;
            bestIndex = index;
        }
    }

    return bestIndex;
}

[[nodiscard]] inline bool shouldShowExtraHelp(int wrongStreak) {
    return wrongStreak >= 2;
}

#pragma once

#include <algorithm>
#include <cstddef>
#include <functional>
#include <vector>

#include "Question.h"

// Chooses which questions a single topic-quiz session asks.
//
// `pool` is expected to be pre-shuffled by the caller (Application owns the
// random engine); this function only decides *which* of them to keep, so it
// stays pure and testable.
//
// Two goals pull against each other here:
//   - Variety: asking every question a topic has made retakes identical.
//   - Revision: questions answered wrongly before are the ones most worth
//     seeing again.
//
// Letting revision win outright turned out to defeat variety entirely — a
// learner who got 15 questions wrong then saw exactly those 15 again on the
// next attempt, with no new material at all. So previously-wrong questions
// are capped at half the session, leaving the rest for fresh ones. If there
// are not enough fresh questions to fill the quiz, the remainder is topped
// up from the leftover mistakes rather than returning a short session.
[[nodiscard]] inline std::vector<Question> selectQuizQuestionsFrom(
    const std::vector<Question>& pool, std::size_t quizSize,
    const std::function<bool(const Question&)>& wasAnsweredWrongBefore) {
    if (pool.size() <= quizSize) {
        return pool;
    }

    std::vector<Question> mistakes;
    std::vector<Question> fresh;
    mistakes.reserve(pool.size());
    fresh.reserve(pool.size());
    for (const Question& question : pool) {
        if (wasAnsweredWrongBefore(question)) {
            mistakes.push_back(question);
        } else {
            fresh.push_back(question);
        }
    }

    // At least one, so a small quiz still revisits something; at most half,
    // so new material always has room.
    const std::size_t mistakeBudget = std::max<std::size_t>(1, quizSize / 2);

    std::vector<Question> selected;
    selected.reserve(quizSize);
    for (std::size_t i = 0; i < mistakes.size() && selected.size() < mistakeBudget; ++i) {
        selected.push_back(mistakes[i]);
    }
    const std::size_t usedMistakes = selected.size();
    for (std::size_t i = 0; i < fresh.size() && selected.size() < quizSize; ++i) {
        selected.push_back(fresh[i]);
    }
    for (std::size_t i = usedMistakes; i < mistakes.size() && selected.size() < quizSize; ++i) {
        selected.push_back(mistakes[i]);
    }

    return selected;
}

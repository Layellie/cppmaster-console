#pragma once

#include <cstddef>
#include <vector>

#include "Question.h"

// `remaining` must already be sorted ascending by `difficulty` (the
// caller's responsibility, done once at quiz start). Returns the index
// (into `remaining`) of which question to ask next.
[[nodiscard]] inline std::size_t selectNextQuestionIndex(
    const std::vector<Question>& remaining, int correctStreak, int wrongStreak) {
    (void)wrongStreak;
    if (correctStreak >= 2 && remaining.size() > 1) {
        return remaining.size() - 1;
    }
    return 0;
}

[[nodiscard]] inline bool shouldShowExtraHelp(int wrongStreak) {
    return wrongStreak >= 2;
}

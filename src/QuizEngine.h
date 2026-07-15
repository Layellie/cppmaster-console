#pragma once

#include <string>

#include "Question.h"
#include "Settings.h"

struct AnswerResult {
    bool correct;
    int xpAwarded;
    std::string correctAnswerDisplay;
};

class QuizEngine {
public:
    [[nodiscard]] AnswerResult evaluate(
        const Question& question, const std::string& rawAnswer,
        const Settings& settings = Settings{}) const;
};

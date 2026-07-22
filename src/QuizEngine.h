#pragma once

#include <string>

#include "Question.h"
#include "Settings.h"

struct AnswerResult {
    bool correct = false;
    int xpAwarded = 0;
    std::string correctAnswerDisplay;
    bool exitRequested = false;
};

class QuizEngine {
public:
    [[nodiscard]] AnswerResult evaluate(
        const Question& question, const std::string& rawAnswer,
        const Settings& settings = Settings{}) const;
    [[nodiscard]] std::string correctAnswerDisplay(const Question& question) const;
};

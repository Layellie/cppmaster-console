#pragma once

#include <string>
#include <vector>

#include "Enums.h"

struct Question {
    int id = 0;
    int topicId = 0;
    QuestionType type = QuestionType::MultipleChoice;
    Difficulty difficulty = Difficulty::Easy;
    std::string prompt;
    std::vector<std::string> options;          // MultipleChoice only; empty for TrueFalse/FillBlank
    std::vector<std::string> acceptedAnswers;   // normalized (ASCII, lowercase-safe) accepted answer(s)
    std::string explanation;
    int baseXp = 0;
};

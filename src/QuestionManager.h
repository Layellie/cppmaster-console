#pragma once

#include <vector>

#include "Question.h"

class QuestionManager {
public:
    QuestionManager();

    [[nodiscard]] std::vector<Question> questionsForTopic(int topicId) const;

private:
    std::vector<Question> questions_;
};

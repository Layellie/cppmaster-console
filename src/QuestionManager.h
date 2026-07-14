#pragma once

#include <optional>
#include <vector>

#include "Question.h"

class QuestionManager {
public:
    QuestionManager();

    [[nodiscard]] std::vector<Question> questionsForTopic(int topicId) const;
    [[nodiscard]] std::optional<Question> findById(int questionId) const;

private:
    std::vector<Question> questions_;
};

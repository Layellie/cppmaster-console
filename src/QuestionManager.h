#pragma once

#include <optional>
#include <unordered_map>
#include <vector>

#include "Question.h"

class QuestionManager {
public:
    QuestionManager();

    [[nodiscard]] std::vector<Question> questionsForTopic(int topicId) const;
    [[nodiscard]] std::optional<Question> findById(int questionId) const;

private:
    // Built once in the constructor so lookups are O(1) instead of scanning
    // all ~2700 questions on every call — exams alone do 100 lookups each.
    // Values are indices into questions_, not pointers/iterators, so the
    // indexes stay valid regardless of how the vector was built.
    void buildIndexes();

    std::vector<Question> questions_;
    std::unordered_map<int, std::size_t> indexById_;
    std::unordered_map<int, std::vector<std::size_t>> indicesByTopicId_;
};

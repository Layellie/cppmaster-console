#pragma once

#include <cstddef>
#include <optional>
#include <span>
#include <unordered_map>
#include <vector>

#include "Question.h"

class QuestionManager {
public:
    QuestionManager();

    [[nodiscard]] std::vector<Question> questionsForTopic(int topicId) const;
    [[nodiscard]] std::span<const Question> questionViewForTopic(int topicId) const noexcept;
    [[nodiscard]] std::optional<Question> findById(int questionId) const;
    [[nodiscard]] const Question* findPtrById(int questionId) const noexcept;

private:
    struct TopicRange {
        std::size_t offset = 0;
        std::size_t count = 0;
    };

    // Built once in the constructor so lookups are O(1) instead of scanning
    // all ~2900 questions on every call — exams alone do 100 lookups each.
    // Questions are grouped contiguously by topicId so each topic can be
    // exposed as a zero-copy std::span<const Question>.
    void buildIndexes();

    std::vector<Question> questions_;
    std::unordered_map<int, std::size_t> indexById_;
    std::unordered_map<int, TopicRange> rangeByTopicId_;
};

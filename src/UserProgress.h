#pragma once

#include <unordered_map>

#include "Enums.h"

class UserProgress {
public:
    explicit UserProgress(int topicCount);

    [[nodiscard]] TopicStatus statusOf(int topicId) const;
    void setStatus(int topicId, TopicStatus status);

    [[nodiscard]] int totalXp() const;
    void addXp(int amount);

    [[nodiscard]] int totalQuestionsAnswered() const;
    [[nodiscard]] int totalCorrectAnswers() const;
    void recordAnswer(bool correct);
    void setAnsweredCounters(int totalAnswered, int totalCorrect);

private:
    std::unordered_map<int, TopicStatus> statusByTopicId_;
    int totalXp_ = 0;
    int totalQuestionsAnswered_ = 0;
    int totalCorrectAnswers_ = 0;
};

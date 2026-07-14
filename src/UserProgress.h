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

private:
    std::unordered_map<int, TopicStatus> statusByTopicId_;
    int totalXp_ = 0;
};

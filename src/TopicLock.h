#pragma once

#include "Enums.h"

[[nodiscard]] inline bool isSectionRecommended(int sectionId, int highestSectionExamPassed) {
    return sectionId <= highestSectionExamPassed + 1;
}

[[nodiscard]] inline bool sectionExamIsUnlocked(
    bool topicLockEnabled, double completionRatio, double gateThreshold) {
    return !topicLockEnabled || completionRatio >= gateThreshold;
}

// A topic is reachable if lock enforcement is off, if it falls within the
// user's initial skill-based unlock frontier (set once at first launch),
// or if the immediately preceding topic has actually been completed —
// topics never unlock out of order beyond that initial frontier.
[[nodiscard]] inline bool topicIsUnlocked(
    bool topicLockEnabled, int topicId, int unlockedUpToTopicId, TopicStatus previousTopicStatus) {
    if (!topicLockEnabled || topicId <= unlockedUpToTopicId) {
        return true;
    }
    return previousTopicStatus == TopicStatus::Completed ||
           previousTopicStatus == TopicStatus::Mastered;
}

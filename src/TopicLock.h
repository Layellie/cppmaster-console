#pragma once

[[nodiscard]] inline bool isSectionRecommended(int sectionId, int highestSectionExamPassed) {
    return sectionId <= highestSectionExamPassed + 1;
}

[[nodiscard]] inline bool sectionExamIsUnlocked(
    bool topicLockEnabled, double completionRatio, double gateThreshold) {
    return !topicLockEnabled || completionRatio >= gateThreshold;
}

#pragma once

#include <string>
#include <unordered_set>
#include <vector>

enum class AchievementId {
    FirstStep,
    FlawlessFive,
    StreakMaster,
    CodeWriter,
    BugHunter,
    NeverGiveUp,
    PerfectExam,
};

[[nodiscard]] std::vector<AchievementId> allAchievementIds();
[[nodiscard]] std::string achievementDisplayName(AchievementId id);
[[nodiscard]] std::string achievementDescription(AchievementId id);

class AchievementTracker {
public:
    bool unlock(AchievementId id);
    [[nodiscard]] bool isUnlocked(AchievementId id) const;
    [[nodiscard]] std::vector<AchievementId> allUnlocked() const;

    [[nodiscard]] bool loadFromFile(const std::string& filePath, const std::string& backupPath);
    void saveToFile(const std::string& filePath) const;

private:
    std::unordered_set<int> unlockedIds_;
};

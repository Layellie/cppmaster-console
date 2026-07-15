#include "AchievementTracker.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "TestRunner.h"

TEST_CASE(AchievementTracker_UnlockOnceSemantics) {
    AchievementTracker tracker;
    CHECK(!tracker.isUnlocked(AchievementId::FirstStep));
    CHECK(tracker.unlock(AchievementId::FirstStep));
    CHECK(tracker.isUnlocked(AchievementId::FirstStep));
    CHECK(!tracker.unlock(AchievementId::FirstStep));
}

TEST_CASE(AchievementTracker_SaveThenLoadRoundTrips) {
    const std::string path = "tests/test_data/achievements_roundtrip.txt";
    const std::string backup = "tests/test_data/achievements_roundtrip_backup.txt";

    AchievementTracker tracker;
    tracker.unlock(AchievementId::FirstStep);
    tracker.unlock(AchievementId::PerfectExam);
    tracker.saveToFile(path);

    AchievementTracker loaded;
    const bool corrupted = loaded.loadFromFile(path, backup);
    CHECK(!corrupted);
    CHECK(loaded.isUnlocked(AchievementId::FirstStep));
    CHECK(loaded.isUnlocked(AchievementId::PerfectExam));
    CHECK(!loaded.isUnlocked(AchievementId::BugHunter));

    std::filesystem::remove(path);
}

TEST_CASE(AchievementTracker_CorruptedFileIsBackedUpAndResets) {
    const std::string path = "tests/test_data/achievements_corrupt.txt";
    const std::string backup = "tests/test_data/achievements_corrupt_backup.txt";
    std::filesystem::remove(backup);
    {
        std::ofstream file(path, std::ios::trunc);
        file << "achievement NotARealAchievement\n";
    }

    AchievementTracker tracker;
    const bool corrupted = tracker.loadFromFile(path, backup);
    CHECK(corrupted);
    CHECK(tracker.allUnlocked().empty());
    CHECK(std::filesystem::exists(backup));

    std::filesystem::remove(path);
    std::filesystem::remove(backup);
}

TEST_CASE(AchievementTracker_AllAchievementIdsHasSevenEntriesWithNonEmptyText) {
    const auto ids = allAchievementIds();
    CHECK(ids.size() == 7);
    for (const AchievementId id : ids) {
        CHECK(!achievementDisplayName(id).empty());
        CHECK(!achievementDescription(id).empty());
    }
}

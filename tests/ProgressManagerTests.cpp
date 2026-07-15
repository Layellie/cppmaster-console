#include "ProgressManager.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "TestRunner.h"

namespace {
constexpr int kTopicCount = 10;
}  // namespace

TEST_CASE(ProgressManager_MissingFileLoadsFreshNotCorrupted) {
    const std::string path = "tests/test_data/progress_missing.txt";
    const std::string backup = "tests/test_data/progress_missing_backup.txt";
    std::filesystem::remove(path);

    ProgressManager manager;
    const ProgressLoadResult result = manager.load(path, backup, kTopicCount);
    CHECK(!result.wasCorrupted);
    CHECK(result.progress.totalXp() == 0);
}

TEST_CASE(ProgressManager_SaveThenLoadRoundTripsAllFields) {
    const std::string path = "tests/test_data/progress_roundtrip.txt";
    const std::string backup = "tests/test_data/progress_roundtrip_backup.txt";

    UserProgress progress(kTopicCount);
    progress.addXp(150);
    progress.recordAnswer(true);
    progress.recordAnswer(false);
    progress.recordStreak(true);
    progress.recordTypedCorrectAnswer(QuestionType::WriteCode);
    progress.setStatus(3, TopicStatus::Completed);

    ProgressManager manager;
    manager.save(progress, path, kTopicCount);

    const ProgressLoadResult result = manager.load(path, backup, kTopicCount);
    CHECK(!result.wasCorrupted);
    CHECK(result.progress.totalXp() == 150);
    CHECK(result.progress.totalQuestionsAnswered() == 2);
    CHECK(result.progress.totalCorrectAnswers() == 1);
    CHECK(result.progress.currentStreak() == 1);
    CHECK(result.progress.writeCodeCorrectCount() == 1);
    CHECK(result.progress.statusOf(3) == TopicStatus::Completed);

    std::filesystem::remove(path);
}

TEST_CASE(ProgressManager_CorruptedFileIsBackedUpAndResets) {
    const std::string path = "tests/test_data/progress_corrupt.txt";
    const std::string backup = "tests/test_data/progress_corrupt_backup.txt";
    std::filesystem::remove(backup);
    {
        std::ofstream file(path, std::ios::trunc);
        file << "xp not_a_number\n";
    }

    ProgressManager manager;
    const ProgressLoadResult result = manager.load(path, backup, kTopicCount);
    CHECK(result.wasCorrupted);
    CHECK(result.progress.totalXp() == 0);
    CHECK(std::filesystem::exists(backup));

    std::filesystem::remove(path);
    std::filesystem::remove(backup);
}

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
    CHECK(result.progress.highestSectionExamPassed() == 0);
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
    progress.recordSectionExamPassed(1);
    progress.setUnlockedUpToTopicId(4);

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
    CHECK(result.progress.highestSectionExamPassed() == 1);
    CHECK(result.progress.unlockedUpToTopicId() == 4);

    std::filesystem::remove(path);
}

TEST_CASE(ProgressManager_OldFormatFileWithoutUnlockedUpToDefaultsToFullyUnlocked) {
    // Simulates a progress.txt written before the topic-lock feature
    // existed: no "unlocked_up_to" line at all. It must load as not
    // corrupted, and default to topicCount (fully unlocked) rather than
    // the fresh-UserProgress default of 1 — an existing user should never
    // be retroactively locked out of topics they could already reach.
    const std::string path = "tests/test_data/progress_old_format.txt";
    const std::string backup = "tests/test_data/progress_old_format_backup.txt";
    {
        std::ofstream file(path, std::ios::trunc);
        file << "xp 200\n";
        file << "answered 10\n";
        file << "correct 8\n";
        file << "streak_current 2\n";
        file << "streak_longest 5\n";
        file << "writecode_correct 1\n";
        file << "errorfix_correct 0\n";
        file << "highest_section_exam_passed 2\n";
        file << "topic 3 Completed\n";
    }

    ProgressManager manager;
    const ProgressLoadResult result = manager.load(path, backup, kTopicCount);
    CHECK(!result.wasCorrupted);
    CHECK(result.progress.totalXp() == 200);
    CHECK(result.progress.unlockedUpToTopicId() == kTopicCount);

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

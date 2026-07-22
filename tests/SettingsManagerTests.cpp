#include "SettingsManager.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "TestRunner.h"

TEST_CASE(SettingsManager_MissingFileLoadsDefaultsNotCorrupted) {
    const std::string path = "tests/test_data/settings_missing.txt";
    std::filesystem::remove(path);

    SettingsManager manager;
    const SettingsLoadResult result = manager.load(path, "tests/test_data/settings_missing_backup.txt");
    CHECK(!result.wasCorrupted);
    CHECK(result.settings.topicLockEnabled == true);
    CHECK(result.settings.strictCaseSensitivity == true);
    CHECK(result.settings.lenientWriteCodeTolerance == false);
    CHECK(result.settings.fullExplanationDetail == true);
    CHECK(result.settings.dailyReviewQuestionCap == 20);
    CHECK(result.settings.colorEnabled == true);
    CHECK(result.settings.audioAlertEnabled == false);
    CHECK(result.settings.quickTestQuestionCount == 10);
    CHECK(result.settings.topicQuizQuestionCount == 15);
}

TEST_CASE(SettingsManager_SaveThenLoadRoundTripsAllFields) {
    const std::string path = "tests/test_data/settings_roundtrip.txt";
    const std::string backup = "tests/test_data/settings_roundtrip_backup.txt";

    Settings settings;
    settings.topicLockEnabled = false;
    settings.strictCaseSensitivity = false;
    settings.lenientWriteCodeTolerance = true;
    settings.fullExplanationDetail = false;
    settings.dailyReviewQuestionCap = 35;
    settings.colorEnabled = false;
    settings.audioAlertEnabled = true;
    settings.quickTestQuestionCount = 12;
    settings.topicQuizQuestionCount = 22;

    SettingsManager manager;
    manager.save(settings, path);

    const SettingsLoadResult result = manager.load(path, backup);
    CHECK(!result.wasCorrupted);
    CHECK(result.settings.topicLockEnabled == false);
    CHECK(result.settings.strictCaseSensitivity == false);
    CHECK(result.settings.lenientWriteCodeTolerance == true);
    CHECK(result.settings.fullExplanationDetail == false);
    CHECK(result.settings.dailyReviewQuestionCap == 35);
    CHECK(result.settings.colorEnabled == false);
    CHECK(result.settings.audioAlertEnabled == true);
    CHECK(result.settings.quickTestQuestionCount == 12);
    CHECK(result.settings.topicQuizQuestionCount == 22);

    std::filesystem::remove(path);
}

TEST_CASE(SettingsManager_OldFormatFileWithoutNewFieldsLoadsNewFieldDefaults) {
    // Simulates a settings.txt written by a pre-Phase-25 build: only the
    // original 5 keys are present. Loading it must not be treated as
    // corrupted, and every field added since must come out at its default.
    const std::string path = "tests/test_data/settings_old_format.txt";
    const std::string backup = "tests/test_data/settings_old_format_backup.txt";
    {
        std::ofstream file(path, std::ios::trunc);
        file << "topic_lock 0\n";
        file << "strict_case 1\n";
        file << "lenient_writecode 0\n";
        file << "full_explanation 1\n";
        file << "daily_cap 15\n";
    }

    SettingsManager manager;
    const SettingsLoadResult result = manager.load(path, backup);
    CHECK(!result.wasCorrupted);
    CHECK(result.settings.topicLockEnabled == false);
    CHECK(result.settings.dailyReviewQuestionCap == 15);
    CHECK(result.settings.colorEnabled == true);
    CHECK(result.settings.audioAlertEnabled == false);
    CHECK(result.settings.quickTestQuestionCount == 10);
    CHECK(result.settings.topicQuizQuestionCount == 15);

    std::filesystem::remove(path);
}

TEST_CASE(SettingsManager_CorruptedFileIsBackedUpAndResetsToDefaults) {
    const std::string path = "tests/test_data/settings_corrupt.txt";
    const std::string backup = "tests/test_data/settings_corrupt_backup.txt";
    std::filesystem::remove(backup);
    {
        std::ofstream file(path, std::ios::trunc);
        file << "daily_cap not_a_number\n";
    }

    SettingsManager manager;
    const SettingsLoadResult result = manager.load(path, backup);
    CHECK(result.wasCorrupted);
    CHECK(result.settings.dailyReviewQuestionCap == 20);
    CHECK(std::filesystem::exists(backup));

    std::filesystem::remove(path);
    std::filesystem::remove(backup);
}

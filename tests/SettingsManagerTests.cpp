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

    SettingsManager manager;
    manager.save(settings, path);

    const SettingsLoadResult result = manager.load(path, backup);
    CHECK(!result.wasCorrupted);
    CHECK(result.settings.topicLockEnabled == false);
    CHECK(result.settings.strictCaseSensitivity == false);
    CHECK(result.settings.lenientWriteCodeTolerance == true);
    CHECK(result.settings.fullExplanationDetail == false);
    CHECK(result.settings.dailyReviewQuestionCap == 35);

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

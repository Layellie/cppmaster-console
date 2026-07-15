#include "MistakeTracker.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "TestRunner.h"

TEST_CASE(MistakeTracker_RecordWrongCreatesAndIncrementsCount) {
    MistakeTracker tracker;
    CHECK(!tracker.hasMistake(1));
    tracker.recordWrong(1);
    CHECK(tracker.hasMistake(1));
    const auto first = tracker.findMistake(1);
    CHECK(first.has_value());
    CHECK(first->wrongCount == 1);
    tracker.recordWrong(1);
    const auto second = tracker.findMistake(1);
    CHECK(second->wrongCount == 2);
}

TEST_CASE(MistakeTracker_RecordCorrectRetryIsNoOpWithoutExistingRecord) {
    MistakeTracker tracker;
    tracker.recordCorrectRetry(99);
    CHECK(!tracker.hasMistake(99));
}

TEST_CASE(MistakeTracker_RecordCorrectRetryIncrementsExistingRecord) {
    MistakeTracker tracker;
    tracker.recordWrong(1);
    tracker.recordCorrectRetry(1);
    const auto record = tracker.findMistake(1);
    CHECK(record->correctAfterWrongCount == 1);
}

TEST_CASE(MistakeTracker_SaveThenLoadRoundTrips) {
    const std::string path = "tests/test_data/mistakes_roundtrip.txt";
    const std::string backup = "tests/test_data/mistakes_roundtrip_backup.txt";

    MistakeTracker tracker;
    tracker.recordWrong(5);
    tracker.recordWrong(5);
    tracker.recordCorrectRetry(5);
    tracker.saveToFile(path);

    MistakeTracker loaded;
    const bool corrupted = loaded.loadFromFile(path, backup);
    CHECK(!corrupted);
    const auto record = loaded.findMistake(5);
    CHECK(record.has_value());
    CHECK(record->wrongCount == 2);
    CHECK(record->correctAfterWrongCount == 1);

    std::filesystem::remove(path);
}

TEST_CASE(MistakeTracker_CorruptedFileIsBackedUpAndResets) {
    const std::string path = "tests/test_data/mistakes_corrupt.txt";
    const std::string backup = "tests/test_data/mistakes_corrupt_backup.txt";
    std::filesystem::remove(backup);
    {
        std::ofstream file(path, std::ios::trunc);
        file << "mistake not_an_id 0 0 0 0\n";
    }

    MistakeTracker tracker;
    const bool corrupted = tracker.loadFromFile(path, backup);
    CHECK(corrupted);
    CHECK(!tracker.hasMistake(0));
    CHECK(std::filesystem::exists(backup));

    std::filesystem::remove(path);
    std::filesystem::remove(backup);
}

TEST_CASE(MistakeTracker_AllMistakesOldestFirstIsSortedByLastWrongAt) {
    MistakeTracker tracker;
    tracker.recordWrong(1);
    tracker.recordWrong(2);
    const auto mistakes = tracker.allMistakesOldestFirst();
    CHECK(mistakes.size() == 2);
    CHECK(mistakes.front().lastWrongAt <= mistakes.back().lastWrongAt);
}

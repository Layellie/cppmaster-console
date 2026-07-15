#include "QuestionHistory.h"

#include <filesystem>
#include <fstream>
#include <string>

#include "FnvHash.h"
#include "TestRunner.h"

TEST_CASE(QuestionHistory_RecordThenHasSeenExactAndSemantic) {
    QuestionHistory history;
    GeneratedQuestion sample;
    sample.exactHash = fnv1a64("exact-sample");
    sample.semanticHash = fnv1a64("semantic-sample");
    CHECK(!history.hasSeenExact(sample.exactHash));
    history.record(sample);
    CHECK(history.hasSeenExact(sample.exactHash));
    CHECK(history.hasSeenSemantic(sample.semanticHash));
}

TEST_CASE(QuestionHistory_MissingFileLoadsFreshNotCorrupted) {
    const std::string path = "tests/test_data/history_missing.txt";
    const std::string backup = "tests/test_data/history_missing_backup.txt";
    std::filesystem::remove(path);

    QuestionHistory history;
    const bool corrupted = history.loadFromFile(path, backup);
    CHECK(!corrupted);
}

TEST_CASE(QuestionHistory_SaveThenLoadRoundTrips) {
    const std::string path = "tests/test_data/history_roundtrip.txt";
    const std::string backup = "tests/test_data/history_roundtrip_backup.txt";

    QuestionHistory history;
    GeneratedQuestion sample;
    sample.exactHash = fnv1a64("exact-roundtrip");
    sample.semanticHash = fnv1a64("semantic-roundtrip");
    history.record(sample);
    history.saveToFile(path);

    QuestionHistory loaded;
    const bool corrupted = loaded.loadFromFile(path, backup);
    CHECK(!corrupted);
    CHECK(loaded.hasSeenExact(sample.exactHash));
    CHECK(loaded.hasSeenSemantic(sample.semanticHash));

    std::filesystem::remove(path);
}

TEST_CASE(QuestionHistory_CorruptedFileIsBackedUpAndResets) {
    const std::string path = "tests/test_data/history_corrupt.txt";
    const std::string backup = "tests/test_data/history_corrupt_backup.txt";
    std::filesystem::remove(backup);
    {
        std::ofstream file(path, std::ios::trunc);
        file << "exact not_a_number\n";
    }

    QuestionHistory history;
    const bool corrupted = history.loadFromFile(path, backup);
    CHECK(corrupted);
    CHECK(std::filesystem::exists(backup));

    std::filesystem::remove(path);
    std::filesystem::remove(backup);
}

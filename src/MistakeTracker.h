#pragma once

#include <chrono>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

struct MistakeRecord {
    int questionId = 0;
    std::chrono::system_clock::time_point firstWrongAt;
    std::chrono::system_clock::time_point lastWrongAt;
    int wrongCount = 0;
    int correctAfterWrongCount = 0;
};

class MistakeTracker {
public:
    void recordWrong(int questionId);
    void recordCorrectRetry(int questionId);

    [[nodiscard]] bool hasMistake(int questionId) const;
    [[nodiscard]] std::optional<MistakeRecord> findMistake(int questionId) const;
    [[nodiscard]] std::vector<MistakeRecord> allMistakesOldestFirst() const;

    [[nodiscard]] bool loadFromFile(const std::string& filePath, const std::string& backupPath);
    void saveToFile(const std::string& filePath) const;

private:
    std::unordered_map<int, MistakeRecord> recordsByQuestionId_;
};

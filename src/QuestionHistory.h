#pragma once

#include <cstdint>
#include <string>
#include <unordered_set>

#include "GeneratedQuestion.h"

class QuestionHistory {
public:
    [[nodiscard]] bool hasSeenExact(std::uint64_t exactHash) const;
    [[nodiscard]] bool hasSeenSemantic(std::uint64_t semanticHash) const;
    void record(const GeneratedQuestion& generated);

    [[nodiscard]] bool loadFromFile(const std::string& filePath, const std::string& backupPath);
    void saveToFile(const std::string& filePath) const;

private:
    std::unordered_set<std::uint64_t> seenExactHashes_;
    std::unordered_set<std::uint64_t> seenSemanticHashes_;
};

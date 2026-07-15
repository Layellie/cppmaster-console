#pragma once

#include <optional>
#include <random>
#include <string>

#include "GeneratedQuestion.h"
#include "IQuestionGenerator.h"
#include "QuestionHistory.h"

class QuestionGenerationEngine {
public:
    QuestionGenerationEngine() = default;

    [[nodiscard]] std::optional<GeneratedQuestion> generateUnique(
        const IQuestionGenerator& generator, std::mt19937_64& randomEngine);

    [[nodiscard]] bool loadHistory(const std::string& filePath, const std::string& backupPath);
    void saveHistory(const std::string& filePath) const;

private:
    QuestionHistory history_;
};

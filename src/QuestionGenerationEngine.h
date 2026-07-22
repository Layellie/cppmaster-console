#pragma once

#include <optional>
#include <random>
#include <string>

#include "GeneratedQuestion.h"
#include "GeneratedQuestionValidator.h"
#include "GeneratorRegistry.h"
#include "GeneratorScoring.h"
#include "QuestionHistory.h"

class QuestionGenerationEngine {
public:
    explicit QuestionGenerationEngine(std::string logFilePath);

    [[nodiscard]] std::optional<GeneratedQuestion> generateUniqueForTopic(
        int topicId, const GeneratorRegistry& registry, GeneratorScoring& scoring,
        const GeneratedQuestionValidator& validator, std::mt19937_64& randomEngine);

    [[nodiscard]] bool loadHistory(const std::string& filePath, const std::string& backupPath);
    void saveHistory(const std::string& filePath) const;

private:
    QuestionHistory history_;
    std::string logFilePath_;
};

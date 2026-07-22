#include "QuestionGenerationEngine.h"

#include <algorithm>
#include <chrono>
#include <fstream>
#include <utility>
#include <vector>

namespace {

constexpr int kAttemptsPerStage = 20;

std::string stageName(GenerationStage stage) {
    switch (stage) {
        case GenerationStage::Normal:
            return "Normal";
        case GenerationStage::ExpandedParameters:
            return "ExpandedParameters";
        case GenerationStage::StructuralVariation:
            return "StructuralVariation";
    }
    return "Unknown";
}

std::string currentTimestamp() {
    const auto now = std::chrono::system_clock::now();
    return std::to_string(
        std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch()).count());
}

void appendLogLine(
    const std::string& logFilePath, int topicId, const std::string& stageLabel,
    const std::string& generatorId, const std::string& result, int attempts) {
    std::ofstream logFile(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        return;
    }
    logFile << "[" << currentTimestamp() << "] topic=" << topicId << " stage=" << stageLabel
            << " generator=" << (generatorId.empty() ? "-" : generatorId) << " result=" << result
            << " attempts=" << attempts << "\n";
}

std::optional<GeneratedQuestion> tryStage(
    QuestionHistory& history, GeneratorScoring& scoring, const GeneratedQuestionValidator& validator,
    const std::vector<const IQuestionGenerator*>& generators, GenerationStage stage,
    std::mt19937_64& randomEngine, const std::string& logFilePath, int topicId) {
    const std::string stageLabel = stageName(stage);
    for (const IQuestionGenerator* generator : generators) {
        int attempts = 0;
        for (int attempt = 0; attempt < kAttemptsPerStage; ++attempt) {
            ++attempts;
            const auto candidate = generator->generate(randomEngine, stage);
            if (!candidate.has_value()) {
                scoring.recordAttempt(generator->id(), false);
                continue;
            }
            if (!validator.isValid(*candidate)) {
                scoring.recordAttempt(generator->id(), false);
                continue;
            }
            if (history.hasSeenExact(candidate->exactHash) ||
                history.hasSeenSemantic(candidate->semanticHash)) {
                scoring.recordAttempt(generator->id(), false);
                continue;
            }
            history.record(*candidate);
            scoring.recordAttempt(generator->id(), true);
            appendLogLine(
                logFilePath, topicId, stageLabel, std::string(generator->id()), "success", attempts);
            return candidate;
        }
        appendLogLine(
            logFilePath, topicId, stageLabel, std::string(generator->id()), "exhausted", attempts);
    }
    return std::nullopt;
}

}  // namespace

QuestionGenerationEngine::QuestionGenerationEngine(std::string logFilePath)
    : logFilePath_(std::move(logFilePath)) {}

std::optional<GeneratedQuestion> QuestionGenerationEngine::generateUniqueForTopic(
    int topicId, const GeneratorRegistry& registry, GeneratorScoring& scoring,
    const GeneratedQuestionValidator& validator, std::mt19937_64& randomEngine) {
    const std::vector<const IQuestionGenerator*> ownGenerators = registry.generatorsForTopic(topicId);

    for (const GenerationStage stage :
         {GenerationStage::Normal, GenerationStage::ExpandedParameters,
          GenerationStage::StructuralVariation}) {
        if (const auto result = tryStage(
                history_, scoring, validator, ownGenerators, stage, randomEngine, logFilePath_,
                topicId);
            result.has_value()) {
            return result;
        }
    }

    std::vector<const IQuestionGenerator*> otherGenerators;
    for (const IQuestionGenerator* generator : registry.allGenerators()) {
        if (generator->topicId() != topicId) {
            otherGenerators.push_back(generator);
        }
    }
    std::sort(
        otherGenerators.begin(), otherGenerators.end(),
        [&scoring](const IQuestionGenerator* a, const IQuestionGenerator* b) {
            return scoring.successRate(a->id()) > scoring.successRate(b->id());
        });

    if (const auto result = tryStage(
            history_, scoring, validator, otherGenerators, GenerationStage::Normal, randomEngine,
            logFilePath_, topicId);
        result.has_value()) {
        return result;
    }

    appendLogLine(logFilePath_, topicId, "CrossTopic", "", "exhausted", 0);
    return std::nullopt;
}

bool QuestionGenerationEngine::loadHistory(const std::string& filePath, const std::string& backupPath) {
    return history_.loadFromFile(filePath, backupPath);
}

void QuestionGenerationEngine::saveHistory(const std::string& filePath) const {
    history_.saveToFile(filePath);
}

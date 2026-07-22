#include "QuestionGenerationEngine.h"

namespace {
constexpr int kMaxGenerationAttempts = 50;
}  // namespace

std::optional<GeneratedQuestion> QuestionGenerationEngine::generateUnique(
    const IQuestionGenerator& generator, std::mt19937_64& randomEngine) {
    for (int attempt = 0; attempt < kMaxGenerationAttempts; ++attempt) {
        auto candidate = generator.generate(randomEngine, GenerationStage::Normal);
        if (!candidate.has_value()) {
            continue;
        }
        if (history_.hasSeenExact(candidate->exactHash) ||
            history_.hasSeenSemantic(candidate->semanticHash)) {
            continue;
        }
        history_.record(*candidate);
        return candidate;
    }
    return std::nullopt;
}

bool QuestionGenerationEngine::loadHistory(
    const std::string& filePath, const std::string& backupPath) {
    return history_.loadFromFile(filePath, backupPath);
}

void QuestionGenerationEngine::saveHistory(const std::string& filePath) const {
    history_.saveToFile(filePath);
}

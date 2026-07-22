#include "GeneratorScoring.h"

void GeneratorScoring::recordAttempt(std::string_view generatorId, bool succeeded) {
    Stats& stats = statsByGeneratorId_[std::string(generatorId)];
    ++stats.attempts;
    if (succeeded) {
        ++stats.successes;
    }
}

double GeneratorScoring::successRate(std::string_view generatorId) const {
    const auto it = statsByGeneratorId_.find(std::string(generatorId));
    if (it == statsByGeneratorId_.end() || it->second.attempts == 0) {
        return 0.5;
    }
    return static_cast<double>(it->second.successes) / static_cast<double>(it->second.attempts);
}

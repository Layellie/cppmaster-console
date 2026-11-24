#include "GeneratorScoring.h"

void GeneratorScoring::recordAttempt(std::string_view generatorId, bool succeeded) {
    auto it = statsByGeneratorId_.find(generatorId);
    if (it == statsByGeneratorId_.end()) {
        it = statsByGeneratorId_.emplace(std::string(generatorId), Stats{}).first;
    }
    ++it->second.attempts;
    if (succeeded) {
        ++it->second.successes;
    }
}

double GeneratorScoring::successRate(std::string_view generatorId) const {
    const auto it = statsByGeneratorId_.find(generatorId);
    if (it == statsByGeneratorId_.end() || it->second.attempts == 0) {
        return 0.5;
    }
    return static_cast<double>(it->second.successes) / static_cast<double>(it->second.attempts);
}

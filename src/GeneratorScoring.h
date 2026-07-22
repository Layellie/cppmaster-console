#pragma once

#include <string>
#include <string_view>
#include <unordered_map>

class GeneratorScoring {
public:
    void recordAttempt(std::string_view generatorId, bool succeeded);
    [[nodiscard]] double successRate(std::string_view generatorId) const;

private:
    struct Stats {
        int successes = 0;
        int attempts = 0;
    };
    std::unordered_map<std::string, Stats> statsByGeneratorId_;
};

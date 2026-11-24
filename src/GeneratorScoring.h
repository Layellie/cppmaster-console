#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include <string_view>
#include <unordered_map>

class GeneratorScoring {
public:
    void recordAttempt(std::string_view generatorId, bool succeeded);
    [[nodiscard]] double successRate(std::string_view generatorId) const;

private:
    struct StringHash {
        using is_transparent = void;

        [[nodiscard]] std::size_t operator()(std::string_view value) const noexcept {
            return std::hash<std::string_view>{}(value);
        }
        [[nodiscard]] std::size_t operator()(const std::string& value) const noexcept {
            return std::hash<std::string_view>{}(value);
        }
    };

    struct Stats {
        int successes = 0;
        int attempts = 0;
    };

    std::unordered_map<std::string, Stats, StringHash, std::equal_to<>> statsByGeneratorId_;
};

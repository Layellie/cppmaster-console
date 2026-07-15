#pragma once

#include <optional>
#include <random>
#include <string_view>

#include "GeneratedQuestion.h"

class IQuestionGenerator {
public:
    virtual ~IQuestionGenerator() = default;

    [[nodiscard]] virtual std::string_view id() const noexcept = 0;
    [[nodiscard]] virtual std::optional<GeneratedQuestion> generate(
        std::mt19937_64& randomEngine) const = 0;
};

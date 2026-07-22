#pragma once

#include "IQuestionGenerator.h"

class FunctionReturnPredictGenerator final : public IQuestionGenerator {
public:
    [[nodiscard]] std::string_view id() const noexcept override;
    [[nodiscard]] int topicId() const noexcept override;
    [[nodiscard]] std::optional<GeneratedQuestion> generate(
        std::mt19937_64& randomEngine, GenerationStage stage) const override;
};

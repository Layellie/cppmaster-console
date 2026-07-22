#pragma once

#include <optional>
#include <random>
#include <string_view>

#include "GeneratedQuestion.h"

enum class GenerationStage { Normal, ExpandedParameters, StructuralVariation };

class IQuestionGenerator {
public:
    // Explicit because declaring any of the members below would otherwise
    // suppress the implicit default constructor derived generators rely on.
    IQuestionGenerator() = default;
    virtual ~IQuestionGenerator() = default;

    // Declaring the destructor suppresses the implicit move operations and
    // leaves copying available, which is exactly the combination that lets
    // a derived generator be sliced into a base. Generators are always used
    // through pointers held by GeneratorCatalog, so copying one is never
    // intended; spelling that out makes an accidental slice a compile
    // error instead of silent data loss.
    IQuestionGenerator(const IQuestionGenerator&) = delete;
    IQuestionGenerator& operator=(const IQuestionGenerator&) = delete;
    IQuestionGenerator(IQuestionGenerator&&) = delete;
    IQuestionGenerator& operator=(IQuestionGenerator&&) = delete;

    [[nodiscard]] virtual std::string_view id() const noexcept = 0;
    [[nodiscard]] virtual int topicId() const noexcept = 0;
    [[nodiscard]] virtual std::optional<GeneratedQuestion> generate(
        std::mt19937_64& randomEngine, GenerationStage stage) const = 0;
};

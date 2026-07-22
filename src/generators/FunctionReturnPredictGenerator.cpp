#include "generators/FunctionReturnPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

// Cosmetic function-name choice, kept separate from the semantic signature
// (same role as the variable-name arrays in the other generators).
constexpr std::array<const char*, 5> kFunctionNames = {
    "topla", "hesapla", "islem", "fonksiyon", "f",
};

constexpr ParameterDomain kADomain{1, 30};
constexpr ParameterDomain kBDomain{1, 30};
constexpr ParameterDomain kDefaultDomain{2, 10};

}  // namespace

std::string_view FunctionReturnPredictGenerator::id() const noexcept {
    return "FunctionReturnPredictGenerator";
}

int FunctionReturnPredictGenerator::topicId() const noexcept {
    return 43;
}

std::optional<GeneratedQuestion> FunctionReturnPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kFunctionNames.size() - 1);
    const std::string functionName = kFunctionNames[nameDist(randomEngine)];

    const bool defaultParamShape = stage == GenerationStage::StructuralVariation;

    const ParameterDomain aDomain =
        stage == GenerationStage::Normal ? kADomain : kADomain.expanded();
    const int a = aDomain.draw(randomEngine);

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 43;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;

    if (defaultParamShape) {
        const int defaultValue = kDefaultDomain.draw(randomEngine);
        const int answer = a * defaultValue;

        result.question.prompt = "int " + functionName + "(int a, int b = " +
                                  std::to_string(defaultValue) + ") {\n    return a * b;\n}\n" +
                                  "std::cout << " + functionName + "(" + std::to_string(a) +
                                  ");\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(answer)};
        result.question.explanation = "b parametresi verilmediği için varsayılan değeri " +
                                       std::to_string(defaultValue) + " kullanılır: " +
                                       std::to_string(a) + " * " + std::to_string(defaultValue) +
                                       " = " + std::to_string(answer) + ".";

        result.exactSignature = "generator=FunctionReturnPredictGenerator;var=" + functionName +
                                 ";shape=default;a=" + std::to_string(a) + ";defaultB=" +
                                 std::to_string(defaultValue);
        result.semanticSignature = "generator=FunctionReturnPredictGenerator;shape=default;a=" +
                                    std::to_string(a) + ";defaultB=" + std::to_string(defaultValue);
    } else {
        const ParameterDomain bDomain =
            stage == GenerationStage::Normal ? kBDomain : kBDomain.expanded();
        const int b = bDomain.draw(randomEngine);
        const int answer = a + b;

        result.question.prompt = "int " + functionName + "(int a, int b) {\n    return a + b;\n}\n" +
                                  "std::cout << " + functionName + "(" + std::to_string(a) + ", " +
                                  std::to_string(b) + ");\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(answer)};
        result.question.explanation = std::to_string(a) + " + " + std::to_string(b) + " = " +
                                       std::to_string(answer) + ".";

        result.exactSignature = "generator=FunctionReturnPredictGenerator;var=" + functionName +
                                 ";shape=add;a=" + std::to_string(a) + ";b=" + std::to_string(b);
        result.semanticSignature = "generator=FunctionReturnPredictGenerator;shape=add;a=" +
                                    std::to_string(a) + ";b=" + std::to_string(b);
    }

    result.generatorId = std::string(id());
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

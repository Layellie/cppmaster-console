#include "generators/IntArithmeticPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "sayi", "deger", "toplam", "sonuc", "x",
};

constexpr ParameterDomain kStartDomain{-20, 50};
constexpr ParameterDomain kOperandDomain{1, 15};

}  // namespace

std::string_view IntArithmeticPredictGenerator::id() const noexcept {
    return "IntArithmeticPredictGenerator";
}

int IntArithmeticPredictGenerator::topicId() const noexcept {
    return 6;
}

std::optional<GeneratedQuestion> IntArithmeticPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    // No second natural code shape exists for this generator, so
    // StructuralVariation honestly reuses the ExpandedParameters domain
    // rather than inventing an artificial structural change.
    const ParameterDomain startDomain =
        stage == GenerationStage::Normal ? kStartDomain : kStartDomain.expanded();
    const ParameterDomain operandDomain =
        stage == GenerationStage::Normal ? kOperandDomain : kOperandDomain.expanded();

    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    std::uniform_int_distribution<int> opDist(0, 1);

    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const int start = startDomain.draw(randomEngine);
    const int operand = operandDomain.draw(randomEngine);
    const bool isAddition = opDist(randomEngine) == 0;
    const char* opSymbol = isAddition ? "+=" : "-=";
    const int answer = isAddition ? start + operand : start - operand;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 6;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.prompt =
        "int " + variableName + " = " + std::to_string(start) + ";\n" + variableName + " " +
        opSymbol + " " + std::to_string(operand) + ";\nstd::cout << " + variableName +
        ";\nYukarıdaki kodun ekran çıktısı nedir?";
    result.question.acceptedAnswers = {std::to_string(answer)};
    result.question.explanation =
        variableName + " değişkeni " + std::to_string(start) + " ile başlar; " +
        std::string(isAddition ? "+" : "-") + std::to_string(operand) + " işleminden sonra " +
        std::to_string(answer) + " olur.";
    result.question.baseXp = 20;

    result.generatorId = std::string(id());
    result.exactSignature = "generator=IntArithmeticPredictGenerator;var=" + variableName +
                             ";start=" + std::to_string(start) + ";op=" +
                             (isAddition ? "add" : "sub") + ";operand=" + std::to_string(operand);
    result.semanticSignature = "generator=IntArithmeticPredictGenerator;start=" +
                                std::to_string(start) + ";op=" + (isAddition ? "add" : "sub") +
                                ";operand=" + std::to_string(operand);
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

#include "generators/IntArithmeticPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "sayi", "deger", "toplam", "sonuc", "x",
};

}  // namespace

std::string_view IntArithmeticPredictGenerator::id() const noexcept {
    return "IntArithmeticPredictGenerator";
}

std::optional<GeneratedQuestion> IntArithmeticPredictGenerator::generate(
    std::mt19937_64& randomEngine) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    std::uniform_int_distribution<int> startDist(-20, 50);
    std::uniform_int_distribution<int> operandDist(1, 15);
    std::uniform_int_distribution<int> opDist(0, 1);

    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const int start = startDist(randomEngine);
    const int operand = operandDist(randomEngine);
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

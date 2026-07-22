#include "generators/ArithmeticOperatorPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "a", "sayi1", "birinci", "deger1", "ilk",
};

constexpr ParameterDomain kADomain{1, 50};
constexpr ParameterDomain kBDomain{1, 20};

struct OpInfo {
    const char* symbol;
    const char* name;
};

constexpr std::array<OpInfo, 4> kOps = {
    OpInfo{"+", "add"}, OpInfo{"-", "sub"}, OpInfo{"*", "mul"}, OpInfo{"/", "div"},
};

int computeAnswer(int a, int b, int opIndex) {
    switch (opIndex) {
        case 0:
            return a + b;
        case 1:
            return a - b;
        case 2:
            return a * b;
        default:
            return a / b;
    }
}

}  // namespace

std::string_view ArithmeticOperatorPredictGenerator::id() const noexcept {
    return "ArithmeticOperatorPredictGenerator";
}

int ArithmeticOperatorPredictGenerator::topicId() const noexcept {
    return 11;
}

std::optional<GeneratedQuestion> ArithmeticOperatorPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    const ParameterDomain aDomain =
        stage == GenerationStage::Normal ? kADomain : kADomain.expanded();
    const ParameterDomain bDomain =
        stage == GenerationStage::Normal ? kBDomain : kBDomain.expanded();
    // Division is only offered at StructuralVariation - it is a genuinely
    // different operator category (integer truncation) worth a distinct
    // stage rather than folding it into the ordinary +/-/* rotation.
    const int opChoiceMax = stage == GenerationStage::StructuralVariation ? 3 : 2;

    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    std::uniform_int_distribution<int> opDist(0, opChoiceMax);

    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const int a = aDomain.draw(randomEngine);
    int b = bDomain.draw(randomEngine);  // may be nudged off zero below
    const int opIndex = opDist(randomEngine);
    if (opIndex == 3 && b == 0) {
        b = 1;
    }
    const int answer = computeAnswer(a, b, opIndex);
    const OpInfo& op = kOps[static_cast<std::size_t>(opIndex)];

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 11;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Easy;
    result.question.prompt = "int " + variableName + " = " + std::to_string(a) + ";\nint b2 = " +
                              std::to_string(b) + ";\nstd::cout << (" + variableName + " " +
                              op.symbol + " b2);\nYukarıdaki kodun ekran çıktısı nedir?";
    result.question.acceptedAnswers = {std::to_string(answer)};
    result.question.explanation = std::to_string(a) + " " + op.symbol + " " + std::to_string(b) +
                                   " = " + std::to_string(answer) + ".";
    result.question.baseXp = 10;

    result.generatorId = std::string(id());
    result.exactSignature = "generator=ArithmeticOperatorPredictGenerator;var=" + variableName +
                             ";a=" + std::to_string(a) + ";b=" + std::to_string(b) + ";op=" + op.name;
    result.semanticSignature = "generator=ArithmeticOperatorPredictGenerator;a=" +
                                std::to_string(a) + ";b=" + std::to_string(b) + ";op=" + op.name;
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

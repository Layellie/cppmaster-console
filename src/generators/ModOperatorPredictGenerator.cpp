#include "generators/ModOperatorPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "sayi", "deger", "kalan", "n", "x",
};

constexpr ParameterDomain kPositiveADomain{10, 99};
constexpr ParameterDomain kNegativeADomain{-99, -10};
constexpr ParameterDomain kBDomain{2, 9};

}  // namespace

std::string_view ModOperatorPredictGenerator::id() const noexcept {
    return "ModOperatorPredictGenerator";
}

int ModOperatorPredictGenerator::topicId() const noexcept {
    return 12;
}

std::optional<GeneratedQuestion> ModOperatorPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    // StructuralVariation exercises a negative dividend (a genuinely
    // different, commonly-surprising case for %'s sign behavior);
    // ExpandedParameters just widens the ordinary positive-a range.
    const bool useNegativeA = stage == GenerationStage::StructuralVariation;
    const ParameterDomain aDomain =
        useNegativeA          ? kNegativeADomain
        : stage == GenerationStage::Normal ? kPositiveADomain
                                            : kPositiveADomain.expanded();
    const ParameterDomain bDomain =
        stage == GenerationStage::Normal ? kBDomain : kBDomain.expanded();

    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);

    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const int a = aDomain.draw(randomEngine);
    int b = bDomain.draw(randomEngine);
    if (b == 0) {
        b = 1;
    }
    const int answer = a % b;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 12;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Easy;
    result.question.prompt = "int " + variableName + " = " + std::to_string(a) + ";\nstd::cout << (" +
                              variableName + " % " + std::to_string(b) +
                              ");\nYukarıdaki kodun ekran çıktısı nedir?";
    result.question.acceptedAnswers = {std::to_string(answer)};
    result.question.explanation =
        std::to_string(a) + " % " + std::to_string(b) + " = " + std::to_string(answer) + ".";
    result.question.baseXp = 10;

    result.generatorId = std::string(id());
    result.exactSignature = "generator=ModOperatorPredictGenerator;var=" + variableName + ";a=" +
                             std::to_string(a) + ";b=" + std::to_string(b);
    result.semanticSignature =
        "generator=ModOperatorPredictGenerator;a=" + std::to_string(a) + ";b=" + std::to_string(b);
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

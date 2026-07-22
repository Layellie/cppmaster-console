#include "generators/ForLoopSumPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "toplam", "sonuc", "sum", "birikim", "s",
};

constexpr ParameterDomain kNDomain{3, 10};

}  // namespace

std::string_view ForLoopSumPredictGenerator::id() const noexcept {
    return "ForLoopSumPredictGenerator";
}

int ForLoopSumPredictGenerator::topicId() const noexcept {
    return 22;
}

std::optional<GeneratedQuestion> ForLoopSumPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    const ParameterDomain nDomain =
        stage == GenerationStage::Normal ? kNDomain : kNDomain.expanded();
    const bool evensOnly = stage == GenerationStage::StructuralVariation;

    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    int n = nDomain.draw(randomEngine);
    if (n < 1) {
        n = 1;
    }

    int sum = 0;
    std::string prompt;
    if (evensOnly) {
        for (int i = 2; i <= n; i += 2) {
            sum += i;
        }
        prompt = "int " + variableName + " = 0;\nfor (int i = 2; i <= " + std::to_string(n) +
                  "; i += 2) {\n    " + variableName + " += i;\n}\nstd::cout << " + variableName +
                  ";\nYukarıdaki kodun ekran çıktısı nedir?";
    } else {
        for (int i = 1; i <= n; ++i) {
            sum += i;
        }
        prompt = "int " + variableName + " = 0;\nfor (int i = 1; i <= " + std::to_string(n) +
                  "; ++i) {\n    " + variableName + " += i;\n}\nstd::cout << " + variableName +
                  ";\nYukarıdaki kodun ekran çıktısı nedir?";
    }

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 22;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.prompt = prompt;
    result.question.acceptedAnswers = {std::to_string(sum)};
    result.question.explanation =
        (evensOnly ? std::string("2'den ") + std::to_string(n) + "'e kadar çift sayılar toplanır: "
                   : std::string("1'den ") + std::to_string(n) + "'e kadar sayılar toplanır: ") +
        std::to_string(sum) + ".";
    result.question.baseXp = 20;

    result.generatorId = std::string(id());
    result.exactSignature = "generator=ForLoopSumPredictGenerator;var=" + variableName + ";n=" +
                             std::to_string(n) + ";evens=" + (evensOnly ? "yes" : "no");
    result.semanticSignature = "generator=ForLoopSumPredictGenerator;n=" + std::to_string(n) +
                                ";evens=" + (evensOnly ? "yes" : "no");
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

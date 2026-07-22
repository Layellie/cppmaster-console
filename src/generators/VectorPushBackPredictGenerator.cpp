#include "generators/VectorPushBackPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>
#include <vector>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "v", "vektor", "sayilar", "liste", "veriler",
};

constexpr ParameterDomain kBaseDomain{1, 20};
constexpr ParameterDomain kCountDomain{2, 6};

}  // namespace

std::string_view VectorPushBackPredictGenerator::id() const noexcept {
    return "VectorPushBackPredictGenerator";
}

int VectorPushBackPredictGenerator::topicId() const noexcept {
    return 34;
}

std::optional<GeneratedQuestion> VectorPushBackPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    const std::string variableName = kVariableNames[nameDist(randomEngine)];

    const bool popShape = stage == GenerationStage::StructuralVariation;

    const ParameterDomain baseDomain =
        stage == GenerationStage::Normal ? kBaseDomain : kBaseDomain.expanded();
    const ParameterDomain countDomain =
        stage == GenerationStage::Normal ? kCountDomain : kCountDomain.expanded();

    const int base = baseDomain.draw(randomEngine);
    int count = countDomain.draw(randomEngine);
    // popShape pops one element before querying .back(), so it needs at
    // least 2 pushes to leave a non-empty vector; the non-pop shapes only
    // need 1 to keep .back() safe.
    const int minCount = popShape ? 2 : 1;
    if (count < minCount) {
        count = minCount;
    }

    std::uniform_int_distribution<int> queryDist(0, 1);
    const bool queryBack = queryDist(randomEngine) == 1;

    std::vector<int> values;
    std::string pushLines;
    for (int i = 0; i < count; ++i) {
        const int element = base + i;
        values.push_back(element);
        pushLines += variableName + ".push_back(" + std::to_string(element) + ");\n";
    }

    std::string popLine;
    if (popShape) {
        values.pop_back();
        popLine = variableName + ".pop_back();\n";
    }

    const int answer =
        queryBack ? values.back() : static_cast<int>(values.size());
    const std::string queryExpr = queryBack ? ".back()" : ".size()";

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 34;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;
    result.question.prompt = "std::vector<int> " + variableName + ";\n" + pushLines + popLine +
                              "std::cout << " + variableName + queryExpr +
                              ";\nYukarıdaki kodun ekran çıktısı nedir?";
    result.question.acceptedAnswers = {std::to_string(answer)};
    result.question.explanation =
        (popShape ? std::string("Son eleman pop_back() ile çıkarıldıktan sonra, ")
                  : std::string("Sırayla eklenen elemanlardan sonra, ")) +
        variableName + queryExpr + " değeri " + std::to_string(answer) + " olur.";

    result.generatorId = std::string(id());
    result.exactSignature = "generator=VectorPushBackPredictGenerator;var=" + variableName +
                             ";base=" + std::to_string(base) + ";count=" + std::to_string(count) +
                             ";pop=" + (popShape ? "yes" : "no") + ";query=" +
                             (queryBack ? "back" : "size");
    result.semanticSignature = "generator=VectorPushBackPredictGenerator;base=" +
                                std::to_string(base) + ";count=" + std::to_string(count) +
                                ";pop=" + (popShape ? "yes" : "no") + ";query=" +
                                (queryBack ? "back" : "size");
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

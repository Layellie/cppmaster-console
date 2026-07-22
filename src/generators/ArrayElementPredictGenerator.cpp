#include "generators/ArrayElementPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "arr", "dizi", "sayilar", "veriler", "d",
};

constexpr ParameterDomain kValueDomain{0, 99};
constexpr int kArraySize = 5;
// The array always has exactly kArraySize elements, so the index domain is
// never widened via ParameterDomain::expanded() — doing so would produce
// out-of-bounds indices. Only the element-value domain expands.
constexpr ParameterDomain kIndexDomain{0, kArraySize - 1};

std::string joinValues(const std::array<int, kArraySize>& values) {
    std::string joined;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            joined += ",";
        }
        joined += std::to_string(values[i]);
    }
    return joined;
}

}  // namespace

std::string_view ArrayElementPredictGenerator::id() const noexcept {
    return "ArrayElementPredictGenerator";
}

int ArrayElementPredictGenerator::topicId() const noexcept {
    return 31;
}

std::optional<GeneratedQuestion> ArrayElementPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    const std::string variableName = kVariableNames[nameDist(randomEngine)];

    const ParameterDomain valueDomain =
        stage == GenerationStage::Normal ? kValueDomain : kValueDomain.expanded();
    std::array<int, kArraySize> values{};
    for (int& value : values) {
        value = valueDomain.draw(randomEngine);
    }
    const std::string valuesList = joinValues(values);

    const bool sumShape = stage == GenerationStage::StructuralVariation;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 31;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;

    if (sumShape) {
        const int answer = values.front() + values.back();
        result.question.prompt = "int " + variableName + "[] = {" + valuesList +
                                  "};\nstd::cout << " + variableName + "[0] + " + variableName +
                                  "[4];\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(answer)};
        result.question.explanation = variableName + "[0] (" + std::to_string(values.front()) +
                                       ") ile " + variableName + "[4] (" +
                                       std::to_string(values.back()) + ") toplanır: " +
                                       std::to_string(answer) + ".";

        result.exactSignature = "generator=ArrayElementPredictGenerator;var=" + variableName +
                                 ";shape=sum;values=" + valuesList;
        result.semanticSignature =
            "generator=ArrayElementPredictGenerator;shape=sum;values=" + valuesList;
    } else {
        const int index = kIndexDomain.draw(randomEngine);
        const int answer = values[static_cast<std::size_t>(index)];
        result.question.prompt = "int " + variableName + "[] = {" + valuesList +
                                  "};\nstd::cout << " + variableName + "[" + std::to_string(index) +
                                  "];\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(answer)};
        result.question.explanation = variableName + "[" + std::to_string(index) +
                                       "] indeksindeki eleman " + std::to_string(answer) + "'dir.";

        result.exactSignature = "generator=ArrayElementPredictGenerator;var=" + variableName +
                                 ";shape=index;values=" + valuesList +
                                 ";index=" + std::to_string(index);
        result.semanticSignature = "generator=ArrayElementPredictGenerator;shape=index;values=" +
                                    valuesList + ";index=" + std::to_string(index);
    }

    result.generatorId = std::string(id());
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

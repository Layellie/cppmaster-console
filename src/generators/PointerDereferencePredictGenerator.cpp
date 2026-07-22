#include "generators/PointerDereferencePredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "x", "deger", "sayi", "n", "veri",
};
constexpr std::array<const char*, 5> kPointerNames = {
    "p", "ptr", "adres", "p1", "gosterici",
};

constexpr ParameterDomain kValueDomain{1, 100};
constexpr ParameterDomain kNewValueDomain{1, 100};

}  // namespace

std::string_view PointerDereferencePredictGenerator::id() const noexcept {
    return "PointerDereferencePredictGenerator";
}

int PointerDereferencePredictGenerator::topicId() const noexcept {
    return 52;
}

std::optional<GeneratedQuestion> PointerDereferencePredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const std::string pointerName = kPointerNames[nameDist(randomEngine)];

    const bool mutateShape = stage == GenerationStage::StructuralVariation;

    const ParameterDomain valueDomain =
        stage == GenerationStage::Normal ? kValueDomain : kValueDomain.expanded();
    const int value = valueDomain.draw(randomEngine);

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 52;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;

    if (mutateShape) {
        const int newValue = kNewValueDomain.draw(randomEngine);

        result.question.prompt = "int " + variableName + " = " + std::to_string(value) +
                                  ";\nint* " + pointerName + " = &" + variableName + ";\n*" +
                                  pointerName + " = " + std::to_string(newValue) + ";\nstd::cout << " +
                                  variableName + ";\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(newValue)};
        result.question.explanation = "*" + pointerName + " = " + std::to_string(newValue) +
                                       " ifadesi, " + pointerName + "'nin gösterdiği " +
                                       variableName + " değişkenini doğrudan değiştirir; bu yüzden " +
                                       variableName + " artık " + std::to_string(newValue) + "'dir.";

        result.exactSignature = "generator=PointerDereferencePredictGenerator;var=" +
                                 variableName + ":" + pointerName + ";shape=mutate;value=" +
                                 std::to_string(value) + ";newValue=" + std::to_string(newValue);
        result.semanticSignature = "generator=PointerDereferencePredictGenerator;shape=mutate;value=" +
                                    std::to_string(value) + ";newValue=" + std::to_string(newValue);
    } else {
        result.question.prompt = "int " + variableName + " = " + std::to_string(value) +
                                  ";\nint* " + pointerName + " = &" + variableName + ";\nstd::cout << *" +
                                  pointerName + ";\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(value)};
        result.question.explanation = "*" + pointerName + ", " + pointerName + "'nin gösterdiği " +
                                       variableName + " değişkeninin değerini okur: " +
                                       std::to_string(value) + ".";

        result.exactSignature = "generator=PointerDereferencePredictGenerator;var=" +
                                 variableName + ":" + pointerName + ";shape=read;value=" +
                                 std::to_string(value);
        result.semanticSignature = "generator=PointerDereferencePredictGenerator;shape=read;value=" +
                                    std::to_string(value);
    }

    result.generatorId = std::string(id());
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

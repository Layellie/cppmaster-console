#include "generators/IfElsePredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "x", "sayi", "deger", "n", "girdi",
};

constexpr ParameterDomain kXDomain{-50, 50};

}  // namespace

std::string_view IfElsePredictGenerator::id() const noexcept {
    return "IfElsePredictGenerator";
}

int IfElsePredictGenerator::topicId() const noexcept {
    return 18;
}

std::optional<GeneratedQuestion> IfElsePredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    const ParameterDomain xDomain =
        stage == GenerationStage::Normal ? kXDomain : kXDomain.expanded();
    const bool threeWay = stage == GenerationStage::StructuralVariation;

    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const int x = xDomain.draw(randomEngine);

    std::string prompt;
    std::string answer;
    std::string explanation;

    if (threeWay) {
        prompt = "int " + variableName + " = " + std::to_string(x) + ";\nif (" + variableName +
                  " > 0) {\n    std::cout << \"pozitif\";\n} else if (" + variableName +
                  " < 0) {\n    std::cout << \"negatif\";\n} else {\n    std::cout << \"sifir\";\n}\n"
                  "Yukarıdaki kodun ekran çıktısı nedir?";
        if (x > 0) {
            answer = "pozitif";
        } else if (x < 0) {
            answer = "negatif";
        } else {
            answer = "sifir";
        }
        explanation = variableName + " = " + std::to_string(x) + " olduğundan çıktı \"" + answer + "\" olur.";
    } else {
        prompt = "int " + variableName + " = " + std::to_string(x) + ";\nif (" + variableName +
                  " > 0) {\n    std::cout << \"pozitif\";\n} else {\n    std::cout << \"negatif ya da sifir\";\n}\n"
                  "Yukarıdaki kodun ekran çıktısı nedir?";
        answer = x > 0 ? "pozitif" : "negatif ya da sifir";
        explanation = variableName + " = " + std::to_string(x) + " olduğundan çıktı \"" + answer + "\" olur.";
    }

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 18;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Easy;
    result.question.prompt = prompt;
    result.question.acceptedAnswers = {answer};
    result.question.explanation = explanation;
    result.question.baseXp = 10;

    result.generatorId = std::string(id());
    result.exactSignature = "generator=IfElsePredictGenerator;var=" + variableName + ";x=" +
                             std::to_string(x) + ";shape=" + (threeWay ? "three" : "two");
    result.semanticSignature = "generator=IfElsePredictGenerator;x=" + std::to_string(x) +
                                ";shape=" + (threeWay ? "three" : "two");
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

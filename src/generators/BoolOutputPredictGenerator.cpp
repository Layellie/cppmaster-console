#include "generators/BoolOutputPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "durum", "aktif", "sonuc", "bulundu", "tamam",
};

}  // namespace

std::string_view BoolOutputPredictGenerator::id() const noexcept {
    return "BoolOutputPredictGenerator";
}

std::optional<GeneratedQuestion> BoolOutputPredictGenerator::generate(
    std::mt19937_64& randomEngine) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    std::uniform_int_distribution<int> valueDist(0, 1);

    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const bool boolValue = valueDist(randomEngine) == 1;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 9;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Easy;
    result.question.prompt =
        "bool " + variableName + " = " + std::string(boolValue ? "true" : "false") +
        ";\nstd::cout << " + variableName + ";\nYukarıdaki kodun ekran çıktısı nedir?";
    result.question.acceptedAnswers = {boolValue ? "1" : "0"};
    result.question.explanation =
        std::string(
            "cout, bool değerini varsayılan olarak true için 1, false için 0 şeklinde "
            "yazdırır; burada değer ") +
        (boolValue ? "true" : "false") + " olduğu için çıktı " + (boolValue ? "1" : "0") +
        " olur.";
    result.question.baseXp = 10;

    result.generatorId = std::string(id());
    result.exactSignature = "generator=BoolOutputPredictGenerator;var=" + variableName +
                             ";value=" + (boolValue ? "true" : "false");
    result.semanticSignature =
        std::string("generator=BoolOutputPredictGenerator;value=") + (boolValue ? "true" : "false");
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

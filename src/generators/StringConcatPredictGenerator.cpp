#include "generators/StringConcatPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "s", "metin", "sonuc", "birlesim", "str",
};

// Short Turkish word fragments; picked from small fixed lists rather than a
// numeric ParameterDomain since there is no meaningful "expanded range" for
// a word choice (mirrors BoolOutputPredictGenerator's rationale for not
// having a distinct ExpandedParameters shape).
constexpr std::array<const char*, 5> kWordsA = {
    "kod", "veri", "dizi", "sinif", "islev",
};
constexpr std::array<const char*, 5> kWordsB = {
    "lama", "tabani", "yapisi", "cagrisi", "tanimi",
};

}  // namespace

std::string_view StringConcatPredictGenerator::id() const noexcept {
    return "StringConcatPredictGenerator";
}

int StringConcatPredictGenerator::topicId() const noexcept {
    return 37;
}

std::optional<GeneratedQuestion> StringConcatPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    std::uniform_int_distribution<std::size_t> wordADist(0, kWordsA.size() - 1);
    std::uniform_int_distribution<std::size_t> wordBDist(0, kWordsB.size() - 1);

    const std::string variableName = kVariableNames[nameDist(randomEngine)];
    const std::string wordA = kWordsA[wordADist(randomEngine)];
    const std::string wordB = kWordsB[wordBDist(randomEngine)];
    const std::string concatenated = wordA + wordB;

    const bool lengthShape = stage == GenerationStage::StructuralVariation;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 37;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;

    if (lengthShape) {
        const int length = static_cast<int>(concatenated.size());
        result.question.prompt = "std::string " + variableName + " = \"" + wordA + "\" + \"" +
                                  wordB + "\";\nstd::cout << " + variableName +
                                  ".length();\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {std::to_string(length)};
        result.question.explanation = "\"" + wordA + "\" ve \"" + wordB +
                                       "\" birleştirilince \"" + concatenated + "\" oluşur; bu " +
                                       std::to_string(length) + " karakterdir.";
    } else {
        result.question.prompt = "std::string " + variableName + " = \"" + wordA + "\" + \"" +
                                  wordB + "\";\nstd::cout << " + variableName +
                                  ";\nYukarıdaki kodun ekran çıktısı nedir?";
        result.question.acceptedAnswers = {concatenated};
        result.question.explanation = "\"" + wordA + "\" ve \"" + wordB +
                                       "\" string birleştirme operatörü ile \"" + concatenated +
                                       "\" olur.";
    }

    result.generatorId = std::string(id());
    result.exactSignature = "generator=StringConcatPredictGenerator;var=" + variableName +
                             ";wordA=" + wordA + ";wordB=" + wordB + ";length=" +
                             (lengthShape ? "yes" : "no");
    result.semanticSignature = "generator=StringConcatPredictGenerator;wordA=" + wordA +
                                ";wordB=" + wordB + ";length=" + (lengthShape ? "yes" : "no");
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

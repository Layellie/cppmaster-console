#include "generators/MapLookupPredictGenerator.h"

#include <array>
#include <cstddef>
#include <string>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "m", "harita", "sozluk", "veriler", "kayitlar",
};

constexpr ParameterDomain kBaseKeyDomain{1, 20};
constexpr ParameterDomain kValueDomain{1, 100};

}  // namespace

std::string_view MapLookupPredictGenerator::id() const noexcept {
    return "MapLookupPredictGenerator";
}

int MapLookupPredictGenerator::topicId() const noexcept {
    return 84;
}

std::optional<GeneratedQuestion> MapLookupPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    const std::string variableName = kVariableNames[nameDist(randomEngine)];

    const ParameterDomain baseKeyDomain =
        stage == GenerationStage::Normal ? kBaseKeyDomain : kBaseKeyDomain.expanded();
    const ParameterDomain valueDomain =
        stage == GenerationStage::Normal ? kValueDomain : kValueDomain.expanded();

    const int baseKey = baseKeyDomain.draw(randomEngine);
    const std::array<int, 3> keys = {baseKey, baseKey + 1, baseKey + 2};
    const int missingKey = baseKey + 3;
    const std::array<int, 3> values = {
        valueDomain.draw(randomEngine), valueDomain.draw(randomEngine), valueDomain.draw(randomEngine)};

    // slot 0-2 queries one of the three inserted keys; slot 3 queries a key
    // guaranteed absent from the map (baseKey+3 is never one of keys[0..2]).
    std::uniform_int_distribution<int> slotDist(0, 3);
    const int slot = slotDist(randomEngine);
    const bool found = slot != 3;
    const int queriedKey = found ? keys[static_cast<std::size_t>(slot)] : missingKey;

    const bool findShape = stage == GenerationStage::StructuralVariation;

    std::string insertLines;
    for (std::size_t i = 0; i < keys.size(); ++i) {
        insertLines += variableName + "[" + std::to_string(keys[i]) + "] = " +
                       std::to_string(values[i]) + ";\n";
    }
    const std::string mapDeclaration = "std::map<int, int> " + variableName + ";\n" + insertLines;

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 84;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;

    if (findShape) {
        result.question.prompt = mapDeclaration + "if (" + variableName + ".find(" +
                                  std::to_string(queriedKey) + ") != " + variableName +
                                  ".end()) {\n    std::cout << \"bulundu\";\n} else {\n    "
                                  "std::cout << \"bulunamadi\";\n}\nYukarıdaki kodun ekran çıktısı "
                                  "nedir?";
        result.question.acceptedAnswers = {found ? "bulundu" : "bulunamadi"};
        result.question.explanation = std::to_string(queriedKey) + " anahtarı " + variableName +
                                       " içinde " + (found ? std::string("bulunduğu için \"bulundu\" ")
                                                           : std::string("bulunmadığı için "
                                                                          "\"bulunamadi\" ")) +
                                       "yazdırılır.";

        result.exactSignature = "generator=MapLookupPredictGenerator;var=" + variableName +
                                 ";shape=find;baseKey=" + std::to_string(baseKey) + ";v0=" +
                                 std::to_string(values[0]) + ";v1=" + std::to_string(values[1]) +
                                 ";v2=" + std::to_string(values[2]) + ";slot=" + std::to_string(slot);
        result.semanticSignature = "generator=MapLookupPredictGenerator;shape=find;baseKey=" +
                                    std::to_string(baseKey) + ";v0=" + std::to_string(values[0]) +
                                    ";v1=" + std::to_string(values[1]) + ";v2=" +
                                    std::to_string(values[2]) + ";slot=" + std::to_string(slot);
    } else {
        const int answer = found ? values[static_cast<std::size_t>(slot)] : 0;

        result.question.prompt = mapDeclaration + "std::cout << " + variableName + "[" +
                                  std::to_string(queriedKey) + "];\nYukarıdaki kodun ekran çıktısı "
                                  "nedir?";
        result.question.acceptedAnswers = {std::to_string(answer)};
        result.question.explanation =
            found ? (std::to_string(queriedKey) + " anahtarının değeri " + std::to_string(answer) +
                     "'dir.")
                  : (variableName + " içinde " + std::to_string(queriedKey) +
                     " anahtarı yok; operator[] bu anahtarı otomatik olarak 0 değeriyle "
                     "oluşturur.");

        result.exactSignature = "generator=MapLookupPredictGenerator;var=" + variableName +
                                 ";shape=index;baseKey=" + std::to_string(baseKey) + ";v0=" +
                                 std::to_string(values[0]) + ";v1=" + std::to_string(values[1]) +
                                 ";v2=" + std::to_string(values[2]) + ";slot=" + std::to_string(slot);
        result.semanticSignature = "generator=MapLookupPredictGenerator;shape=index;baseKey=" +
                                    std::to_string(baseKey) + ";v0=" + std::to_string(values[0]) +
                                    ";v1=" + std::to_string(values[1]) + ";v2=" +
                                    std::to_string(values[2]) + ";slot=" + std::to_string(slot);
    }

    result.generatorId = std::string(id());
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

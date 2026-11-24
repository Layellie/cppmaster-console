#include "generators/SortWithLambdaPredictGenerator.h"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdlib>
#include <string>
#include <vector>

#include "FnvHash.h"
#include "ParameterDomain.h"

namespace {

constexpr std::array<const char*, 5> kVariableNames = {
    "v", "dizi", "liste", "sayilar", "veri",
};

constexpr ParameterDomain kCountDomain{4, 5};
constexpr ParameterDomain kValueDomain{1, 99};
constexpr ParameterDomain kPivotDomain{1, 99};

std::string joinValues(const std::vector<int>& values, const std::string& separator) {
    std::string joined;
    for (std::size_t i = 0; i < values.size(); ++i) {
        if (i > 0) {
            joined += separator;
        }
        joined += std::to_string(values[i]);
    }
    return joined;
}

}  // namespace

std::string_view SortWithLambdaPredictGenerator::id() const noexcept {
    return "SortWithLambdaPredictGenerator";
}

int SortWithLambdaPredictGenerator::topicId() const noexcept {
    return 91;
}

std::optional<GeneratedQuestion> SortWithLambdaPredictGenerator::generate(
    std::mt19937_64& randomEngine, GenerationStage stage) const {
    std::uniform_int_distribution<std::size_t> nameDist(0, kVariableNames.size() - 1);
    const std::string variableName = kVariableNames[nameDist(randomEngine)];

    const ParameterDomain countDomain =
        stage == GenerationStage::Normal ? kCountDomain : kCountDomain.expanded();
    const ParameterDomain valueDomain =
        stage == GenerationStage::Normal ? kValueDomain : kValueDomain.expanded();

    const int count = std::max(1, countDomain.draw(randomEngine));

    const bool distanceShape = stage == GenerationStage::StructuralVariation;
    const int pivot = distanceShape ? kPivotDomain.draw(randomEngine) : 0;

    std::vector<int> values;
    values.reserve(static_cast<std::size_t>(count));
    for (int i = 0; i < count; ++i) {
        int drawn = 0;
        bool accepted = false;
        for (int retry = 0; retry < 32; ++retry) {
            drawn = valueDomain.draw(randomEngine);
            if (!distanceShape) {
                accepted = true;
                break;
            }
            const int distance = std::abs(drawn - pivot);
            const bool collides = std::ranges::any_of(values, [&](int existing) {
                return existing != drawn && std::abs(existing - pivot) == distance;
            });
            if (!collides) {
                accepted = true;
                break;
            }
        }
        if (!accepted) {
            return std::nullopt;
        }
        values.push_back(drawn);
    }
    const std::string initializerList = joinValues(values, ", ");

    std::vector<int> sorted = values;
    std::string comparatorText;
    std::string pivotLine;
    if (distanceShape) {
        std::ranges::sort(sorted, [pivot](int a, int b) {
            return std::abs(a - pivot) < std::abs(b - pivot);
        });
        pivotLine = "int pivot = " + std::to_string(pivot) + ";\n";
        comparatorText = "[pivot](int a, int b) { return std::abs(a - pivot) < std::abs(b - "
                          "pivot); }";
    } else {
        std::ranges::sort(sorted, [](int a, int b) { return a > b; });
        comparatorText = "[](int a, int b) { return a > b; }";
    }
    const std::string answer = joinValues(sorted, " ");

    GeneratedQuestion result;
    result.question.id = 0;
    result.question.topicId = 91;
    result.question.type = QuestionType::PredictOutput;
    result.question.difficulty = Difficulty::Medium;
    result.question.baseXp = 20;
    result.question.prompt = pivotLine + "std::vector<int> " + variableName + " = {" +
                              initializerList + "};\nstd::sort(" + variableName + ".begin(), " +
                              variableName + ".end(), " + comparatorText + ");\nfor (int x : " +
                              variableName + ") std::cout << x << \" \";\nYukarıdaki kodun ekran "
                              "çıktısı nedir?";
    result.question.acceptedAnswers = {answer};
    result.question.explanation =
        distanceShape
            ? ("Eleman " + std::to_string(pivot) + " pivot değerine olan mutlak farkına göre "
               "artan sırayla dizilir: " + answer + ".")
            : ("Elemanlar büyükten küçüğe (azalan) sıralanır: " + answer + ".");

    result.generatorId = std::string(id());
    result.exactSignature = "generator=SortWithLambdaPredictGenerator;var=" + variableName +
                             ";shape=" + (distanceShape ? "distance" : "descending") + ";values=" +
                             joinValues(values, ",") + (distanceShape ? ";pivot=" + std::to_string(pivot)
                                                                       : std::string());
    result.semanticSignature = "generator=SortWithLambdaPredictGenerator;shape=" +
                                (distanceShape ? std::string("distance") : std::string("descending")) +
                                ";values=" + joinValues(values, ",") +
                                (distanceShape ? ";pivot=" + std::to_string(pivot) : std::string());
    result.exactHash = fnv1a64(result.exactSignature);
    result.semanticHash = fnv1a64(result.semanticSignature);

    return result;
}

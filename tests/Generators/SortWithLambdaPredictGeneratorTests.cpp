#include "generators/SortWithLambdaPredictGenerator.h"

#include <algorithm>
#include <cstdlib>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "TestRunner.h"

namespace {

std::vector<int> parseValues(const std::string& signature) {
    const std::string marker = "values=";
    const std::size_t start = signature.find(marker) + marker.size();
    const std::size_t end = signature.find(';', start);
    const std::string list =
        end == std::string::npos ? signature.substr(start) : signature.substr(start, end - start);

    std::vector<int> values;
    std::stringstream stream(list);
    std::string token;
    while (std::getline(stream, token, ',')) {
        values.push_back(std::stoi(token));
    }
    return values;
}

std::vector<int> parseAnswer(const std::string& answer) {
    std::vector<int> values;
    std::stringstream stream(answer);
    int value = 0;
    while (stream >> value) {
        values.push_back(value);
    }
    return values;
}

}  // namespace

TEST_CASE(SortWithLambdaPredictGenerator_TopicIdIsNinetyOne) {
    SortWithLambdaPredictGenerator generator;
    CHECK(generator.topicId() == 91);
}

TEST_CASE(SortWithLambdaPredictGenerator_FixedSeedIsDeterministic) {
    SortWithLambdaPredictGenerator generator;
    std::mt19937_64 engineA{15151ULL};
    std::mt19937_64 engineB{15151ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(SortWithLambdaPredictGenerator_NormalStageAnswerIsDescendingSort) {
    SortWithLambdaPredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 91);
        CHECK(candidate->exactSignature.find(";shape=descending;") != std::string::npos);

        std::vector<int> expected = parseValues(candidate->exactSignature);
        std::sort(expected.begin(), expected.end(), [](int a, int b) { return a > b; });
        const std::vector<int> answer = parseAnswer(candidate->question.acceptedAnswers.front());
        CHECK(answer == expected);
    }
}

TEST_CASE(SortWithLambdaPredictGenerator_StructuralVariationSortsByDistanceToPivot) {
    SortWithLambdaPredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";shape=distance;") != std::string::npos);

        const std::string marker = "pivot=";
        const std::size_t start = candidate->exactSignature.find(marker) + marker.size();
        const int pivot = std::stoi(candidate->exactSignature.substr(start));

        std::vector<int> expected = parseValues(candidate->exactSignature);
        std::sort(expected.begin(), expected.end(), [pivot](int a, int b) {
            return std::abs(a - pivot) < std::abs(b - pivot);
        });
        const std::vector<int> answer = parseAnswer(candidate->question.acceptedAnswers.front());
        CHECK(answer == expected);
    }
}

TEST_CASE(SortWithLambdaPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    SortWithLambdaPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

TEST_CASE(SortWithLambdaPredictGenerator_DistanceShapeHasNoAmbiguousTies) {
    SortWithLambdaPredictGenerator generator;
    std::mt19937_64 engine{12345ULL};
    for (int iteration = 0; iteration < 500; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());

        const std::string marker = "pivot=";
        const std::size_t start = candidate->exactSignature.find(marker) + marker.size();
        const int pivot = std::stoi(candidate->exactSignature.substr(start));
        const std::vector<int> values = parseValues(candidate->exactSignature);

        bool hasAmbiguousTie = false;
        for (std::size_t i = 0; i < values.size(); ++i) {
            for (std::size_t j = i + 1; j < values.size(); ++j) {
                if (values[i] != values[j] &&
                    std::abs(values[i] - pivot) == std::abs(values[j] - pivot)) {
                    hasAmbiguousTie = true;
                }
            }
        }
        CHECK(!hasAmbiguousTie);
    }
}

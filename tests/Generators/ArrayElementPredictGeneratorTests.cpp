#include "generators/ArrayElementPredictGenerator.h"

#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "TestRunner.h"

namespace {

// Parses the comma-separated "values=v0,v1,v2,v3,v4" segment out of a
// signature string produced by ArrayElementPredictGenerator.
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

int parseIndex(const std::string& signature) {
    const std::string marker = "index=";
    const std::size_t start = signature.find(marker) + marker.size();
    return std::stoi(signature.substr(start));
}

}  // namespace

TEST_CASE(ArrayElementPredictGenerator_TopicIdIsThirtyOne) {
    ArrayElementPredictGenerator generator;
    CHECK(generator.topicId() == 31);
}

TEST_CASE(ArrayElementPredictGenerator_FixedSeedIsDeterministic) {
    ArrayElementPredictGenerator generator;
    std::mt19937_64 engineA{33333ULL};
    std::mt19937_64 engineB{33333ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(ArrayElementPredictGenerator_NormalStageAnswerMatchesIndexedElement) {
    ArrayElementPredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 31);
        CHECK(candidate->exactSignature.find(";shape=index;") != std::string::npos);

        const std::vector<int> values = parseValues(candidate->exactSignature);
        const int index = parseIndex(candidate->exactSignature);
        CHECK(index >= 0);
        CHECK(index <= 4);
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        CHECK(answer == values[static_cast<std::size_t>(index)]);
    }
}

TEST_CASE(ArrayElementPredictGenerator_StructuralVariationAnswerIsFirstPlusLast) {
    ArrayElementPredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";shape=sum;") != std::string::npos);
        CHECK(candidate->exactSignature.find(";shape=index;") == std::string::npos);

        const std::vector<int> values = parseValues(candidate->exactSignature);
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        CHECK(answer == values.front() + values.back());
    }
}

TEST_CASE(ArrayElementPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    ArrayElementPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

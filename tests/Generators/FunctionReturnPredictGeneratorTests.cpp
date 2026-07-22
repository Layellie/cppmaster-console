#include "generators/FunctionReturnPredictGenerator.h"

#include <random>
#include <string>

#include "TestRunner.h"

namespace {

std::string parseToken(const std::string& signature, const std::string& field) {
    const std::string marker = field + "=";
    const std::size_t start = signature.find(marker) + marker.size();
    const std::size_t end = signature.find(';', start);
    return end == std::string::npos ? signature.substr(start) : signature.substr(start, end - start);
}

int parseField(const std::string& signature, const std::string& field) {
    return std::stoi(parseToken(signature, field));
}

}  // namespace

TEST_CASE(FunctionReturnPredictGenerator_TopicIdIsFortyThree) {
    FunctionReturnPredictGenerator generator;
    CHECK(generator.topicId() == 43);
}

TEST_CASE(FunctionReturnPredictGenerator_FixedSeedIsDeterministic) {
    FunctionReturnPredictGenerator generator;
    std::mt19937_64 engineA{66666ULL};
    std::mt19937_64 engineB{66666ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(FunctionReturnPredictGenerator_NormalStageAnswerIsSumOfAAndB) {
    FunctionReturnPredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 43);
        CHECK(candidate->exactSignature.find(";shape=add;") != std::string::npos);

        const int a = parseField(candidate->exactSignature, "a");
        const int b = parseField(candidate->exactSignature, "b");
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        CHECK(answer == a + b);
    }
}

TEST_CASE(FunctionReturnPredictGenerator_StructuralVariationUsesDefaultParameter) {
    FunctionReturnPredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";shape=default;") != std::string::npos);

        const std::string functionName = parseToken(candidate->exactSignature, "var");
        const int a = parseField(candidate->exactSignature, "a");
        // The call site passes only one argument in this shape.
        CHECK(candidate->question.prompt.find(functionName + "(" + std::to_string(a) + ");") !=
              std::string::npos);
        const int defaultB = parseField(candidate->exactSignature, "defaultB");
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        CHECK(answer == a * defaultB);
    }
}

TEST_CASE(FunctionReturnPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    FunctionReturnPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

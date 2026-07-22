#include "generators/PointerDereferencePredictGenerator.h"

#include <random>
#include <string>

#include "TestRunner.h"

namespace {

int parseField(const std::string& signature, const std::string& field) {
    const std::string marker = field + "=";
    const std::size_t start = signature.find(marker) + marker.size();
    const std::size_t end = signature.find(';', start);
    const std::string token =
        end == std::string::npos ? signature.substr(start) : signature.substr(start, end - start);
    return std::stoi(token);
}

}  // namespace

TEST_CASE(PointerDereferencePredictGenerator_TopicIdIsFiftyTwo) {
    PointerDereferencePredictGenerator generator;
    CHECK(generator.topicId() == 52);
}

TEST_CASE(PointerDereferencePredictGenerator_FixedSeedIsDeterministic) {
    PointerDereferencePredictGenerator generator;
    std::mt19937_64 engineA{77777ULL};
    std::mt19937_64 engineB{77777ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(PointerDereferencePredictGenerator_NormalStageAnswerIsOriginalValue) {
    PointerDereferencePredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 52);
        CHECK(candidate->exactSignature.find(";shape=read;") != std::string::npos);

        const int value = parseField(candidate->exactSignature, "value");
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        CHECK(answer == value);
    }
}

TEST_CASE(PointerDereferencePredictGenerator_StructuralVariationMutatesThroughPointer) {
    PointerDereferencePredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";shape=mutate;") != std::string::npos);

        const int newValue = parseField(candidate->exactSignature, "newValue");
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        // Mutating through the pointer changes the original variable, so
        // the printed value is the new value, not the original one.
        CHECK(answer == newValue);
    }
}

TEST_CASE(PointerDereferencePredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    PointerDereferencePredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

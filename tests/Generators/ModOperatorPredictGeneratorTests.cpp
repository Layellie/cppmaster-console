#include "generators/ModOperatorPredictGenerator.h"

#include <random>
#include <stdexcept>
#include <string>

#include "TestRunner.h"

TEST_CASE(ModOperatorPredictGenerator_TopicIdIsTwelve) {
    ModOperatorPredictGenerator generator;
    CHECK(generator.topicId() == 12);
}

TEST_CASE(ModOperatorPredictGenerator_FixedSeedIsDeterministic) {
    ModOperatorPredictGenerator generator;
    std::mt19937_64 engineA{5555ULL};
    std::mt19937_64 engineB{5555ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(ModOperatorPredictGenerator_NormalStageAIsAlwaysPositive) {
    ModOperatorPredictGenerator generator;
    std::mt19937_64 engine{3ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 12);
        try {
            const int answer = std::stoi(candidate->question.acceptedAnswers.front());
            CHECK(answer >= 0);
        } catch (const std::exception&) {
            CHECK(false);
        }
    }
}

TEST_CASE(ModOperatorPredictGenerator_StructuralVariationCanProduceNegativeAnswer) {
    ModOperatorPredictGenerator generator;
    std::mt19937_64 engine{77ULL};
    bool sawNegative = false;
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        if (answer < 0) {
            sawNegative = true;
        }
    }
    CHECK(sawNegative);
}

TEST_CASE(ModOperatorPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    ModOperatorPredictGenerator generator;
    std::mt19937_64 engine{4ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

#include "generators/ArithmeticOperatorPredictGenerator.h"

#include <random>
#include <stdexcept>
#include <string>

#include "TestRunner.h"

TEST_CASE(ArithmeticOperatorPredictGenerator_TopicIdIsEleven) {
    ArithmeticOperatorPredictGenerator generator;
    CHECK(generator.topicId() == 11);
}

TEST_CASE(ArithmeticOperatorPredictGenerator_FixedSeedIsDeterministic) {
    ArithmeticOperatorPredictGenerator generator;
    std::mt19937_64 engineA{321ULL};
    std::mt19937_64 engineB{321ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(ArithmeticOperatorPredictGenerator_NormalStageAnswerIsAlwaysParseableAsInt) {
    ArithmeticOperatorPredictGenerator generator;
    std::mt19937_64 engine{11ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 11);
        try {
            static_cast<void>(std::stoi(candidate->question.acceptedAnswers.front()));
        } catch (const std::exception&) {
            CHECK(false);
        }
    }
}

TEST_CASE(ArithmeticOperatorPredictGenerator_StructuralVariationCanProduceDivision) {
    ArithmeticOperatorPredictGenerator generator;
    std::mt19937_64 engine{2222ULL};
    bool sawDivision = false;
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        if (candidate->exactSignature.find("op=div") != std::string::npos) {
            sawDivision = true;
        }
    }
    CHECK(sawDivision);
}

TEST_CASE(ArithmeticOperatorPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    ArithmeticOperatorPredictGenerator generator;
    std::mt19937_64 engine{9ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

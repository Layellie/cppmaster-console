#include "generators/ForLoopSumPredictGenerator.h"

#include <random>
#include <stdexcept>
#include <string>

#include "TestRunner.h"

TEST_CASE(ForLoopSumPredictGenerator_TopicIdIsTwentyTwo) {
    ForLoopSumPredictGenerator generator;
    CHECK(generator.topicId() == 22);
}

TEST_CASE(ForLoopSumPredictGenerator_FixedSeedIsDeterministic) {
    ForLoopSumPredictGenerator generator;
    std::mt19937_64 engineA{11111ULL};
    std::mt19937_64 engineB{11111ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(ForLoopSumPredictGenerator_NormalStageAnswerIsAlwaysNonNegative) {
    ForLoopSumPredictGenerator generator;
    std::mt19937_64 engine{6ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 22);
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        CHECK(answer >= 1);
    }
}

TEST_CASE(ForLoopSumPredictGenerator_NAtThreeSumsToSix) {
    // Cross-check one concrete value directly (n=3: 1+2+3=6) rather than
    // relying only on the generator's own internal simulation being
    // self-consistent.
    ForLoopSumPredictGenerator generator;
    bool foundNThree = false;
    std::mt19937_64 engine{123ULL};
    for (int iteration = 0; iteration < 500 && !foundNThree; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        if (candidate->exactSignature.find(";n=3;") != std::string::npos) {
            foundNThree = true;
            CHECK(candidate->question.acceptedAnswers.front() == "6");
        }
    }
    CHECK(foundNThree);
}

TEST_CASE(ForLoopSumPredictGenerator_StructuralVariationSumsOnlyEvens) {
    ForLoopSumPredictGenerator generator;
    bool foundNTen = false;
    std::mt19937_64 engine{321ULL};
    for (int iteration = 0; iteration < 2000 && !foundNTen; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        if (candidate->exactSignature.find(";n=10;evens=yes") != std::string::npos) {
            foundNTen = true;
            // 2+4+6+8+10 = 30
            CHECK(candidate->question.acceptedAnswers.front() == "30");
        }
    }
    CHECK(foundNTen);
}

TEST_CASE(ForLoopSumPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    ForLoopSumPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

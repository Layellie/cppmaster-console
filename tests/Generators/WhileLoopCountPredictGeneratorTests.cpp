#include "generators/WhileLoopCountPredictGenerator.h"

#include <random>
#include <stdexcept>
#include <string>

#include "TestRunner.h"

TEST_CASE(WhileLoopCountPredictGenerator_TopicIdIsTwentyThree) {
    WhileLoopCountPredictGenerator generator;
    CHECK(generator.topicId() == 23);
}

TEST_CASE(WhileLoopCountPredictGenerator_FixedSeedIsDeterministic) {
    WhileLoopCountPredictGenerator generator;
    std::mt19937_64 engineA{22222ULL};
    std::mt19937_64 engineB{22222ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(WhileLoopCountPredictGenerator_NormalStageAnswerIsAlwaysNonNegative) {
    WhileLoopCountPredictGenerator generator;
    std::mt19937_64 engine{9ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 23);
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        CHECK(answer >= 0);
    }
}

TEST_CASE(WhileLoopCountPredictGenerator_DivideShapeStartTwentyDivisorTwoCountsFour) {
    // Cross-check one concrete value directly (20 -> 10 -> 5 -> 2 -> 1,
    // four divisions) rather than relying only on the generator's own
    // internal simulation being self-consistent.
    WhileLoopCountPredictGenerator generator;
    bool found = false;
    std::mt19937_64 engine{123ULL};
    for (int iteration = 0; iteration < 1000 && !found; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        if (candidate->exactSignature.find(";shape=divide;start=20;divisor=2") !=
            std::string::npos) {
            found = true;
            CHECK(candidate->question.acceptedAnswers.front() == "4");
        }
    }
    CHECK(found);
}

TEST_CASE(WhileLoopCountPredictGenerator_StructuralVariationUsesDoublingShape) {
    // Structural variation swaps the divide-until-1 loop for a
    // double-until-limit loop; prove that shape actually shows up and
    // produces a directly-checkable answer (1 -> 2 -> 4 -> ... -> 128,
    // seven doublings to reach/exceed a limit of 100).
    WhileLoopCountPredictGenerator generator;
    bool found = false;
    std::mt19937_64 engine{321ULL};
    for (int iteration = 0; iteration < 2000 && !found; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";shape=double;") != std::string::npos);
        if (candidate->exactSignature.find(";shape=double;start=1;limit=100") !=
            std::string::npos) {
            found = true;
            CHECK(candidate->question.acceptedAnswers.front() == "7");
        }
    }
    CHECK(found);
}

TEST_CASE(WhileLoopCountPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    WhileLoopCountPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

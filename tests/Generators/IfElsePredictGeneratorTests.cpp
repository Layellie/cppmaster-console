#include "generators/IfElsePredictGenerator.h"

#include <random>

#include "TestRunner.h"

TEST_CASE(IfElsePredictGenerator_TopicIdIsEighteen) {
    IfElsePredictGenerator generator;
    CHECK(generator.topicId() == 18);
}

TEST_CASE(IfElsePredictGenerator_FixedSeedIsDeterministic) {
    IfElsePredictGenerator generator;
    std::mt19937_64 engineA{909ULL};
    std::mt19937_64 engineB{909ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(IfElsePredictGenerator_NormalStageAnswerIsOneOfTwoOptions) {
    IfElsePredictGenerator generator;
    std::mt19937_64 engine{1ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 18);
        const std::string& answer = candidate->question.acceptedAnswers.front();
        CHECK(answer == "pozitif" || answer == "negatif ya da sifir");
    }
}

TEST_CASE(IfElsePredictGenerator_StructuralVariationCanProduceAllThreeAnswers) {
    IfElsePredictGenerator generator;
    std::mt19937_64 engine{2ULL};
    bool sawPositive = false;
    bool sawNegative = false;
    bool sawZero = false;
    // The expanded domain for this stage spans 301 integers, so hitting
    // exactly 0 has roughly 1/301 odds per draw; 5000 iterations makes
    // missing it across the whole run astronomically unlikely rather than
    // merely "probably fine" at a smaller sample size.
    for (int iteration = 0; iteration < 5000; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        const std::string& answer = candidate->question.acceptedAnswers.front();
        if (answer == "pozitif") sawPositive = true;
        if (answer == "negatif") sawNegative = true;
        if (answer == "sifir") sawZero = true;
    }
    CHECK(sawPositive);
    CHECK(sawNegative);
    CHECK(sawZero);
}

TEST_CASE(IfElsePredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    IfElsePredictGenerator generator;
    std::mt19937_64 engine{3ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

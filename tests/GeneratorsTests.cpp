#include <cstddef>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

#include "TestRunner.h"
#include "generators/BoolOutputPredictGenerator.h"
#include "generators/IntArithmeticPredictGenerator.h"

TEST_CASE(IntArithmeticPredictGenerator_TopicIdIsSix) {
    IntArithmeticPredictGenerator generator;
    CHECK(generator.topicId() == 6);
}

TEST_CASE(IntArithmeticPredictGenerator_FixedSeedIsDeterministic) {
    IntArithmeticPredictGenerator generator;
    std::mt19937_64 engineA{123456789ULL};
    std::mt19937_64 engineB{123456789ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(IntArithmeticPredictGenerator_ComputedAnswerIsAlwaysParseableAsInt) {
    IntArithmeticPredictGenerator generator;
    std::mt19937_64 engine{42ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 6);
        CHECK(candidate->question.type == QuestionType::PredictOutput);
        CHECK(candidate->question.acceptedAnswers.size() == 1);

        const std::string& answerText = candidate->question.acceptedAnswers.front();
        std::size_t consumedChars = 0;
        try {
            static_cast<void>(std::stoi(answerText, &consumedChars));
            CHECK(consumedChars == answerText.size());
        } catch (const std::exception&) {
            CHECK(false);
        }
    }
}

TEST_CASE(IntArithmeticPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    IntArithmeticPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature != candidate->semanticSignature);
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

TEST_CASE(IntArithmeticPredictGenerator_ExpandedParametersStageProducesValidCandidates) {
    IntArithmeticPredictGenerator generator;
    std::mt19937_64 engine{2024ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::ExpandedParameters);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 6);
        CHECK(candidate->question.acceptedAnswers.size() == 1);
        std::size_t consumedChars = 0;
        try {
            static_cast<void>(std::stoi(candidate->question.acceptedAnswers.front(), &consumedChars));
            CHECK(consumedChars == candidate->question.acceptedAnswers.front().size());
        } catch (const std::exception&) {
            CHECK(false);
        }
    }
}

TEST_CASE(BoolOutputPredictGenerator_TopicIdIsNine) {
    BoolOutputPredictGenerator generator;
    CHECK(generator.topicId() == 9);
}

TEST_CASE(BoolOutputPredictGenerator_FixedSeedIsDeterministic) {
    BoolOutputPredictGenerator generator;
    std::mt19937_64 engineA{55ULL};
    std::mt19937_64 engineB{55ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(BoolOutputPredictGenerator_AcceptedAnswerIsAlwaysZeroOrOne) {
    BoolOutputPredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 9);
        const std::string& answer = candidate->question.acceptedAnswers.front();
        CHECK(answer == "0" || answer == "1");
    }
}

TEST_CASE(BoolOutputPredictGenerator_SemanticSignatureDependsOnlyOnBooleanValue) {
    BoolOutputPredictGenerator generator;
    std::mt19937_64 engine{13ULL};

    std::vector<std::string> observedSemanticSignatures;
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        bool alreadySeen = false;
        for (const std::string& seen : observedSemanticSignatures) {
            if (seen == candidate->semanticSignature) {
                alreadySeen = true;
                break;
            }
        }
        if (!alreadySeen) {
            observedSemanticSignatures.push_back(candidate->semanticSignature);
        }
    }
    // 200 draws over 5 variable names x 2 boolean values makes it
    // overwhelmingly certain every combination is drawn at least once
    // (pigeonhole). If semanticSignature depended on variableName too, we'd
    // see far more than 2 distinct values here. Seeing exactly 2 proves it
    // depends only on the boolean value, i.e. the generator's whole
    // semantic space really is exactly 2 variants.
    CHECK(observedSemanticSignatures.size() == 2);
}

TEST_CASE(BoolOutputPredictGenerator_ExpandedParametersStageStillValid) {
    BoolOutputPredictGenerator generator;
    std::mt19937_64 engine{2024ULL};
    for (int iteration = 0; iteration < 50; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::ExpandedParameters);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 9);
        const std::string& answer = candidate->question.acceptedAnswers.front();
        CHECK(answer == "0" || answer == "1");
    }
}

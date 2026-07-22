#include "generators/StringConcatPredictGenerator.h"

#include <random>
#include <string>

#include "TestRunner.h"

namespace {

std::string parseField(const std::string& signature, const std::string& field) {
    const std::string marker = field + "=";
    const std::size_t start = signature.find(marker) + marker.size();
    const std::size_t end = signature.find(';', start);
    return end == std::string::npos ? signature.substr(start) : signature.substr(start, end - start);
}

}  // namespace

TEST_CASE(StringConcatPredictGenerator_TopicIdIsThirtySeven) {
    StringConcatPredictGenerator generator;
    CHECK(generator.topicId() == 37);
}

TEST_CASE(StringConcatPredictGenerator_FixedSeedIsDeterministic) {
    StringConcatPredictGenerator generator;
    std::mt19937_64 engineA{55555ULL};
    std::mt19937_64 engineB{55555ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(StringConcatPredictGenerator_NormalStageAnswerIsConcatenation) {
    StringConcatPredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 37);
        CHECK(candidate->exactSignature.find(";length=no") != std::string::npos);

        const std::string wordA = parseField(candidate->exactSignature, "wordA");
        const std::string wordB = parseField(candidate->exactSignature, "wordB");
        CHECK(candidate->question.acceptedAnswers.front() == wordA + wordB);
    }
}

TEST_CASE(StringConcatPredictGenerator_StructuralVariationAnswerIsLength) {
    StringConcatPredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";length=yes") != std::string::npos);

        const std::string wordA = parseField(candidate->exactSignature, "wordA");
        const std::string wordB = parseField(candidate->exactSignature, "wordB");
        const int expectedLength = static_cast<int>(wordA.size() + wordB.size());
        CHECK(std::stoi(candidate->question.acceptedAnswers.front()) == expectedLength);
    }
}

TEST_CASE(StringConcatPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    StringConcatPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

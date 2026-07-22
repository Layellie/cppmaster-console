#include "generators/TryCatchPredictGenerator.h"

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

int parseInt(const std::string& signature, const std::string& field) {
    return std::stoi(parseToken(signature, field));
}

bool parseBool(const std::string& signature, const std::string& field) {
    return parseToken(signature, field) == "1";
}

}  // namespace

TEST_CASE(TryCatchPredictGenerator_TopicIdIsNinetyNine) {
    TryCatchPredictGenerator generator;
    CHECK(generator.topicId() == 99);
}

TEST_CASE(TryCatchPredictGenerator_FixedSeedIsDeterministic) {
    TryCatchPredictGenerator generator;
    std::mt19937_64 engineA{16161ULL};
    std::mt19937_64 engineB{16161ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(TryCatchPredictGenerator_NormalStageAnswerMatchesThrowsFlag) {
    TryCatchPredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    bool sawThrow = false;
    bool sawReturn = false;
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 99);
        CHECK(candidate->exactSignature.find(";shape=one;") != std::string::npos);

        const bool throwsFlag = parseBool(candidate->exactSignature, "throws");
        const int value = parseInt(candidate->exactSignature, "value");
        const std::string& answer = candidate->question.acceptedAnswers.front();
        if (throwsFlag) {
            CHECK(answer == "Yakalandi");
            sawThrow = true;
        } else {
            CHECK(answer == std::to_string(value));
            sawReturn = true;
        }
    }
    CHECK(sawThrow);
    CHECK(sawReturn);
}

TEST_CASE(TryCatchPredictGenerator_StructuralVariationAnswerCombinesBothIndependentBlocks) {
    TryCatchPredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";shape=two;") != std::string::npos);

        const bool flag1 = parseBool(candidate->exactSignature, "flag1");
        const bool flag2 = parseBool(candidate->exactSignature, "flag2");
        const int value1 = parseInt(candidate->exactSignature, "value1");
        const int value2 = parseInt(candidate->exactSignature, "value2");

        const std::string expectedPart1 = flag1 ? "Yakalandi1" : std::to_string(value1);
        const std::string expectedPart2 = flag2 ? "Yakalandi2" : std::to_string(value2);
        CHECK(candidate->question.acceptedAnswers.front() == expectedPart1 + expectedPart2);
    }
}

TEST_CASE(TryCatchPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    TryCatchPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

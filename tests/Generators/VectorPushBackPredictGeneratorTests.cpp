#include "generators/VectorPushBackPredictGenerator.h"

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

bool parseFlag(const std::string& signature, const std::string& field, const std::string& yesValue) {
    const std::string marker = field + "=";
    const std::size_t start = signature.find(marker) + marker.size();
    const std::size_t end = signature.find(';', start);
    const std::string token =
        end == std::string::npos ? signature.substr(start) : signature.substr(start, end - start);
    return token == yesValue;
}

}  // namespace

TEST_CASE(VectorPushBackPredictGenerator_TopicIdIsThirtyFour) {
    VectorPushBackPredictGenerator generator;
    CHECK(generator.topicId() == 34);
}

TEST_CASE(VectorPushBackPredictGenerator_FixedSeedIsDeterministic) {
    VectorPushBackPredictGenerator generator;
    std::mt19937_64 engineA{44444ULL};
    std::mt19937_64 engineB{44444ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(VectorPushBackPredictGenerator_NormalStageAnswerMatchesQuery) {
    VectorPushBackPredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 34);
        CHECK(candidate->exactSignature.find(";pop=no;") != std::string::npos);

        const int base = parseField(candidate->exactSignature, "base");
        const int count = parseField(candidate->exactSignature, "count");
        const bool queryBack = parseFlag(candidate->exactSignature, "query", "back");
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        if (queryBack) {
            CHECK(answer == base + count - 1);
        } else {
            CHECK(answer == count);
        }
    }
}

TEST_CASE(VectorPushBackPredictGenerator_StructuralVariationPopsBeforeQuery) {
    VectorPushBackPredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";pop=yes;") != std::string::npos);

        const int base = parseField(candidate->exactSignature, "base");
        const int count = parseField(candidate->exactSignature, "count");
        CHECK(count >= 2);
        const bool queryBack = parseFlag(candidate->exactSignature, "query", "back");
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        // After one pop_back(), the effective size is count - 1 and the
        // last remaining element is base + count - 2.
        if (queryBack) {
            CHECK(answer == base + count - 2);
        } else {
            CHECK(answer == count - 1);
        }
    }
}

TEST_CASE(VectorPushBackPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    VectorPushBackPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

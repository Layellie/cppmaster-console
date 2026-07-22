#include "generators/ClassMemberPredictGenerator.h"

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

TEST_CASE(ClassMemberPredictGenerator_TopicIdIsSixtyFour) {
    ClassMemberPredictGenerator generator;
    CHECK(generator.topicId() == 64);
}

TEST_CASE(ClassMemberPredictGenerator_FixedSeedIsDeterministic) {
    ClassMemberPredictGenerator generator;
    std::mt19937_64 engineA{88888ULL};
    std::mt19937_64 engineB{88888ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(ClassMemberPredictGenerator_NormalStageAnswerIsAssignedValue) {
    ClassMemberPredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 64);
        CHECK(candidate->exactSignature.find(";shape=one;") != std::string::npos);

        const int value = parseField(candidate->exactSignature, "value");
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        CHECK(answer == value);
    }
}

TEST_CASE(ClassMemberPredictGenerator_StructuralVariationUsesSecondInstanceValue) {
    ClassMemberPredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";shape=two;") != std::string::npos);

        const int valueA = parseField(candidate->exactSignature, "valueA");
        const int valueB = parseField(candidate->exactSignature, "valueB");
        const int answer = std::stoi(candidate->question.acceptedAnswers.front());
        CHECK(answer == valueB);
        // valueA is drawn independently and only exists to prove the two
        // instances hold separate state; it should not leak into the
        // printed answer.
        (void)valueA;
    }
}

TEST_CASE(ClassMemberPredictGenerator_TwoInstanceNamesAreAlwaysDistinct) {
    ClassMemberPredictGenerator generator;
    std::mt19937_64 engine{321ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        // var=<class>:<member>:<instanceA>:<instanceB> — the two instance
        // names must differ or the generated code would redeclare the same
        // identifier twice.
        const std::string marker = "var=";
        const std::size_t start = candidate->exactSignature.find(marker) + marker.size();
        const std::size_t end = candidate->exactSignature.find(';', start);
        const std::string varField = candidate->exactSignature.substr(start, end - start);
        const std::size_t firstColon = varField.find(':');
        const std::size_t secondColon = varField.find(':', firstColon + 1);
        const std::size_t thirdColon = varField.find(':', secondColon + 1);
        const std::string instanceA = varField.substr(secondColon + 1, thirdColon - secondColon - 1);
        const std::string instanceB = varField.substr(thirdColon + 1);
        CHECK(instanceA != instanceB);
    }
}

TEST_CASE(ClassMemberPredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    ClassMemberPredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

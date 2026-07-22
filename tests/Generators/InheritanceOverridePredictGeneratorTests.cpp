#include "generators/InheritanceOverridePredictGenerator.h"

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

}  // namespace

TEST_CASE(InheritanceOverridePredictGenerator_TopicIdIsSixtyNine) {
    InheritanceOverridePredictGenerator generator;
    CHECK(generator.topicId() == 69);
}

TEST_CASE(InheritanceOverridePredictGenerator_FixedSeedIsDeterministic) {
    InheritanceOverridePredictGenerator generator;
    std::mt19937_64 engineA{13131ULL};
    std::mt19937_64 engineB{13131ULL};
    const auto first = generator.generate(engineA, GenerationStage::Normal);
    const auto second = generator.generate(engineB, GenerationStage::Normal);
    CHECK(first.has_value());
    CHECK(second.has_value());
    CHECK(first->exactSignature == second->exactSignature);
}

TEST_CASE(InheritanceOverridePredictGenerator_NormalStageAnswerIsDerivedText) {
    InheritanceOverridePredictGenerator generator;
    std::mt19937_64 engine{5ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::Normal);
        CHECK(candidate.has_value());
        CHECK(candidate->question.topicId == 69);
        CHECK(candidate->exactSignature.find(";shape=direct;") != std::string::npos);

        const std::string derivedText = parseToken(candidate->exactSignature, "derivedText");
        CHECK(candidate->question.acceptedAnswers.front() == derivedText);
    }
}

TEST_CASE(InheritanceOverridePredictGenerator_StructuralVariationAnswerIsBaseTextNotDerivedText) {
    // The non-virtual method call through a base pointer resolves via the
    // pointer's static type, so the printed text is the BASE class's text
    // even though the pointer points at a derived instance — a genuinely
    // different (and commonly mis-predicted) answer from the direct-call
    // shape above. Verified against a standalone compile before writing
    // this generator.
    InheritanceOverridePredictGenerator generator;
    std::mt19937_64 engine{99ULL};
    for (int iteration = 0; iteration < 200; ++iteration) {
        const auto candidate = generator.generate(engine, GenerationStage::StructuralVariation);
        CHECK(candidate.has_value());
        CHECK(candidate->exactSignature.find(";shape=basePointer;") != std::string::npos);

        const std::string baseText = parseToken(candidate->exactSignature, "baseText");
        const std::string derivedText = parseToken(candidate->exactSignature, "derivedText");
        CHECK(candidate->question.acceptedAnswers.front() == baseText);
        CHECK(candidate->question.acceptedAnswers.front() != derivedText);
    }
}

TEST_CASE(InheritanceOverridePredictGenerator_SemanticSignatureExcludesVariableNameOnly) {
    InheritanceOverridePredictGenerator generator;
    std::mt19937_64 engine{7ULL};
    const auto candidate = generator.generate(engine, GenerationStage::Normal);
    CHECK(candidate.has_value());
    CHECK(candidate->exactSignature.find("var=") != std::string::npos);
    CHECK(candidate->semanticSignature.find("var=") == std::string::npos);
}

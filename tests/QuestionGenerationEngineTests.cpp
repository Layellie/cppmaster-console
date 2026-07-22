#include "QuestionGenerationEngine.h"

#include <filesystem>
#include <optional>
#include <random>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "FnvHash.h"
#include "GeneratedQuestionValidator.h"
#include "GeneratorRegistry.h"
#include "GeneratorScoring.h"
#include "IQuestionGenerator.h"
#include "TestRunner.h"

namespace {

constexpr const char* kTestLogPath = "tests/test_data/question_generation_test.log";

class FixedSequenceGenerator final : public IQuestionGenerator {
public:
    FixedSequenceGenerator(int topicId, std::vector<std::optional<GeneratedQuestion>> sequence)
        : topicId_(topicId), sequence_(std::move(sequence)) {}

    [[nodiscard]] std::string_view id() const noexcept override { return "FixedSequenceGenerator"; }

    [[nodiscard]] int topicId() const noexcept override { return topicId_; }

    [[nodiscard]] std::optional<GeneratedQuestion> generate(
        std::mt19937_64& /*randomEngine*/, GenerationStage /*stage*/) const override {
        if (callIndex_ >= sequence_.size()) {
            return sequence_.empty() ? std::nullopt : sequence_.back();
        }
        return sequence_[callIndex_++];
    }

private:
    int topicId_;
    std::vector<std::optional<GeneratedQuestion>> sequence_;
    mutable std::size_t callIndex_ = 0;
};

GeneratedQuestion makeCandidate(const std::string& exactSeed, const std::string& semanticSeed) {
    GeneratedQuestion candidate;
    candidate.question.topicId = 1;
    candidate.question.type = QuestionType::PredictOutput;
    candidate.question.prompt = "test prompt";
    candidate.question.acceptedAnswers = {"42"};
    candidate.question.baseXp = 10;
    candidate.exactSignature = exactSeed;
    candidate.semanticSignature = semanticSeed;
    candidate.exactHash = fnv1a64(exactSeed);
    candidate.semanticHash = fnv1a64(semanticSeed);
    return candidate;
}

}  // namespace

TEST_CASE(QuestionGenerationEngine_AcceptsFirstFreshCandidateAtNormalStage) {
    std::filesystem::remove(kTestLogPath);
    FixedSequenceGenerator generator(1, {makeCandidate("exact-1", "semantic-1")});
    GeneratorRegistry registry;
    registry.registerGenerator(generator);
    GeneratorScoring scoring;
    GeneratedQuestionValidator validator;
    QuestionGenerationEngine engine(kTestLogPath);
    std::mt19937_64 randomEngine{1ULL};

    const auto result = engine.generateUniqueForTopic(1, registry, scoring, validator, randomEngine);
    CHECK(result.has_value());
    CHECK(result->exactSignature == "exact-1");
}

TEST_CASE(QuestionGenerationEngine_EscalatesToExpandedParametersAfterNormalExhausts) {
    std::filesystem::remove(kTestLogPath);
    // First call records "exact-A" into history via a one-shot generator.
    FixedSequenceGenerator seedGenerator(1, {makeCandidate("exact-A", "semantic-A")});
    GeneratorRegistry seedRegistry;
    seedRegistry.registerGenerator(seedGenerator);
    GeneratorScoring scoring;
    GeneratedQuestionValidator validator;
    QuestionGenerationEngine engine(kTestLogPath);
    std::mt19937_64 randomEngine{1ULL};
    const auto seeded =
        engine.generateUniqueForTopic(1, seedRegistry, scoring, validator, randomEngine);
    CHECK(seeded.has_value());

    // Second call: 20 duplicate replies (exhausting Normal's attempt budget),
    // then a fresh candidate that can only be reached once the engine has
    // escalated to ExpandedParameters.
    std::vector<std::optional<GeneratedQuestion>> sequence;
    sequence.reserve(21);
    for (int i = 0; i < 20; ++i) {
        sequence.emplace_back(makeCandidate("exact-A", "semantic-A"));
    }
    sequence.emplace_back(makeCandidate("exact-fresh", "semantic-fresh"));
    FixedSequenceGenerator escalatingGenerator(1, sequence);
    GeneratorRegistry registry;
    registry.registerGenerator(escalatingGenerator);

    const auto result = engine.generateUniqueForTopic(1, registry, scoring, validator, randomEngine);
    CHECK(result.has_value());
    CHECK(result->exactSignature == "exact-fresh");
}

TEST_CASE(QuestionGenerationEngine_FallsBackToCrossTopicWhenOwnTopicExhaustsAllStages) {
    std::filesystem::remove(kTestLogPath);
    // Topic 1's generator only ever produces the same (eventually-duplicate)
    // candidate, so it will exhaust Normal, ExpandedParameters, and
    // StructuralVariation. Topic 2's generator has a fresh candidate ready.
    FixedSequenceGenerator seedGenerator(1, {makeCandidate("exact-seed", "semantic-seed")});
    GeneratorScoring scoring;
    GeneratedQuestionValidator validator;
    QuestionGenerationEngine engine(kTestLogPath);
    std::mt19937_64 randomEngine{1ULL};
    GeneratorRegistry seedRegistry;
    seedRegistry.registerGenerator(seedGenerator);
    const auto seeded =
        engine.generateUniqueForTopic(1, seedRegistry, scoring, validator, randomEngine);
    CHECK(seeded.has_value());

    FixedSequenceGenerator ownTopicGenerator(1, {makeCandidate("exact-seed", "semantic-seed")});
    FixedSequenceGenerator otherTopicGenerator(2, {makeCandidate("exact-other", "semantic-other")});
    GeneratorRegistry registry;
    registry.registerGenerator(ownTopicGenerator);
    registry.registerGenerator(otherTopicGenerator);

    const auto result = engine.generateUniqueForTopic(1, registry, scoring, validator, randomEngine);
    CHECK(result.has_value());
    CHECK(result->exactSignature == "exact-other");
}

TEST_CASE(QuestionGenerationEngine_ReturnsNulloptWhenEveryStageAndCrossTopicExhaust) {
    std::filesystem::remove(kTestLogPath);
    FixedSequenceGenerator seedGenerator(1, {makeCandidate("exact-seed2", "semantic-seed2")});
    GeneratorScoring scoring;
    GeneratedQuestionValidator validator;
    QuestionGenerationEngine engine(kTestLogPath);
    std::mt19937_64 randomEngine{1ULL};
    GeneratorRegistry seedRegistry;
    seedRegistry.registerGenerator(seedGenerator);
    const auto seeded =
        engine.generateUniqueForTopic(1, seedRegistry, scoring, validator, randomEngine);
    CHECK(seeded.has_value());

    FixedSequenceGenerator ownTopicGenerator(1, {makeCandidate("exact-seed2", "semantic-seed2")});
    GeneratorRegistry registry;
    registry.registerGenerator(ownTopicGenerator);

    const auto result = engine.generateUniqueForTopic(1, registry, scoring, validator, randomEngine);
    CHECK(!result.has_value());
}

TEST_CASE(QuestionGenerationEngine_ContinuesPastGeneratorNulloptToFindFreshCandidate) {
    std::filesystem::remove(kTestLogPath);
    FixedSequenceGenerator generator(
        1, {std::nullopt, std::nullopt, makeCandidate("exact-after-nullopts", "semantic-after-nullopts")});
    GeneratorRegistry registry;
    registry.registerGenerator(generator);
    GeneratorScoring scoring;
    GeneratedQuestionValidator validator;
    QuestionGenerationEngine engine(kTestLogPath);
    std::mt19937_64 randomEngine{1ULL};

    const auto result = engine.generateUniqueForTopic(1, registry, scoring, validator, randomEngine);
    CHECK(result.has_value());
    CHECK(result->exactSignature == "exact-after-nullopts");
}

TEST_CASE(QuestionGenerationEngine_RejectsInvalidCandidateWithoutRecordingIt) {
    std::filesystem::remove(kTestLogPath);
    GeneratedQuestion invalidCandidate = makeCandidate("exact-invalid", "semantic-invalid");
    invalidCandidate.question.prompt = "";  // fails GeneratedQuestionValidator

    GeneratedQuestion validCandidate = makeCandidate("exact-invalid", "semantic-invalid");
    // Same signature as invalidCandidate: if the invalid one had been
    // recorded, this would be rejected as a duplicate instead of accepted.

    FixedSequenceGenerator generator(1, {invalidCandidate, validCandidate});
    GeneratorRegistry registry;
    registry.registerGenerator(generator);
    GeneratorScoring scoring;
    GeneratedQuestionValidator validator;
    QuestionGenerationEngine engine(kTestLogPath);
    std::mt19937_64 randomEngine{1ULL};

    const auto result = engine.generateUniqueForTopic(1, registry, scoring, validator, randomEngine);
    CHECK(result.has_value());
    // The invalid candidate (empty prompt) must have been skipped without
    // being recorded into history - otherwise this identical-signature valid
    // candidate would have been rejected as a duplicate instead of accepted.
    CHECK(!result->question.prompt.empty());
}

#include "QuestionGenerationEngine.h"

#include <optional>
#include <random>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "FnvHash.h"
#include "IQuestionGenerator.h"
#include "TestRunner.h"

namespace {

class FixedSequenceGenerator final : public IQuestionGenerator {
public:
    explicit FixedSequenceGenerator(std::vector<std::optional<GeneratedQuestion>> sequence)
        : sequence_(std::move(sequence)) {}

    [[nodiscard]] std::string_view id() const noexcept override {
        return "FixedSequenceGenerator";
    }

    [[nodiscard]] int topicId() const noexcept override { return 1; }

    [[nodiscard]] std::optional<GeneratedQuestion> generate(
        std::mt19937_64&, GenerationStage) const override {
        if (callIndex_ >= sequence_.size()) {
            return sequence_.empty() ? std::nullopt : sequence_.back();
        }
        return sequence_[callIndex_++];
    }

private:
    std::vector<std::optional<GeneratedQuestion>> sequence_;
    mutable std::size_t callIndex_ = 0;
};

GeneratedQuestion makeCandidate(const std::string& exactSeed, const std::string& semanticSeed) {
    GeneratedQuestion candidate;
    candidate.exactSignature = exactSeed;
    candidate.semanticSignature = semanticSeed;
    candidate.exactHash = fnv1a64(exactSeed);
    candidate.semanticHash = fnv1a64(semanticSeed);
    return candidate;
}

}  // namespace

TEST_CASE(QuestionGenerationEngine_AcceptsFirstFreshCandidate) {
    FixedSequenceGenerator generator({makeCandidate("exact-1", "semantic-1")});
    QuestionGenerationEngine engine;
    std::mt19937_64 randomEngine{1ULL};
    const auto result = engine.generateUnique(generator, randomEngine);
    CHECK(result.has_value());
    CHECK(result->exactSignature == "exact-1");
}

TEST_CASE(QuestionGenerationEngine_RejectsExactDuplicateThenAcceptsNext) {
    FixedSequenceGenerator generator({
        makeCandidate("exact-A", "semantic-A"),
        makeCandidate("exact-A", "semantic-A"),
        makeCandidate("exact-B", "semantic-B"),
    });
    QuestionGenerationEngine engine;
    std::mt19937_64 randomEngine{1ULL};
    const auto first = engine.generateUnique(generator, randomEngine);
    CHECK(first.has_value());
    CHECK(first->exactSignature == "exact-A");
    const auto second = engine.generateUnique(generator, randomEngine);
    CHECK(second.has_value());
    CHECK(second->exactSignature == "exact-B");
}

TEST_CASE(QuestionGenerationEngine_RejectsSemanticDuplicateEvenWithDifferentExact) {
    FixedSequenceGenerator generator({
        makeCandidate("exact-1", "semantic-shared"),
        makeCandidate("exact-2", "semantic-shared"),
        makeCandidate("exact-3", "semantic-different"),
    });
    QuestionGenerationEngine engine;
    std::mt19937_64 randomEngine{1ULL};
    const auto first = engine.generateUnique(generator, randomEngine);
    CHECK(first.has_value());
    CHECK(first->exactSignature == "exact-1");
    const auto second = engine.generateUnique(generator, randomEngine);
    CHECK(second.has_value());
    CHECK(second->exactSignature == "exact-3");
}

TEST_CASE(QuestionGenerationEngine_ExhaustsAfterFiftyRejectedAttempts) {
    FixedSequenceGenerator generator({makeCandidate("exact-only", "semantic-only")});
    QuestionGenerationEngine engine;
    std::mt19937_64 randomEngine{1ULL};
    const auto first = engine.generateUnique(generator, randomEngine);
    CHECK(first.has_value());
    const auto second = engine.generateUnique(generator, randomEngine);
    CHECK(!second.has_value());
}

TEST_CASE(QuestionGenerationEngine_ContinuesPastGeneratorNulloptToFindFreshCandidate) {
    FixedSequenceGenerator generator({
        std::nullopt,
        std::nullopt,
        makeCandidate("exact-after-nullopts", "semantic-after-nullopts"),
    });
    QuestionGenerationEngine engine;
    std::mt19937_64 randomEngine{1ULL};
    const auto result = engine.generateUnique(generator, randomEngine);
    CHECK(result.has_value());
    CHECK(result->exactSignature == "exact-after-nullopts");
}

#include <chrono>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <random>
#include <string>
#include <unordered_set>
#include <vector>

#include "GeneratedQuestionValidator.h"
#include "GeneratorCatalog.h"
#include "GeneratorRegistry.h"
#include "GeneratorScoring.h"
#include "QuestionGenerationEngine.h"
#include "TestRunner.h"

namespace {

constexpr const char* kStressLogPath = "tests/test_data/generation_stress_test.log";

struct RealGeneratorSet {
    // Deliberately built from the real makeAllGenerators() catalog rather
    // than a hand-maintained list: a locally duplicated list would keep
    // passing while silently ignoring any generator added to the app.
    std::vector<std::unique_ptr<IQuestionGenerator>> owned = makeAllGenerators();
    GeneratorRegistry registry;

    RealGeneratorSet() {
        for (const auto& generator : owned) {
            registry.registerGenerator(*generator);
        }
    }
};

}  // namespace

TEST_CASE(GenerationStress_TenThousandMixedTopicIterationsAllUniqueAndValid) {
    std::filesystem::remove(kStressLogPath);

    RealGeneratorSet generators;
    GeneratorScoring scoring;
    GeneratedQuestionValidator validator;
    QuestionGenerationEngine engine(kStressLogPath);

    std::mt19937_64 randomEngine{20260722ULL};
    const auto& allGenerators = generators.registry.allGenerators();
    CHECK(allGenerators.size() == 17);
    std::uniform_int_distribution<std::size_t> topicPickDist(0, allGenerators.size() - 1);

    std::unordered_set<int> registeredTopicIds;
    for (const IQuestionGenerator* generator : allGenerators) {
        registeredTopicIds.insert(generator->topicId());
    }

    std::unordered_set<std::uint64_t> seenExactHashes;
    int successCount = 0;
    constexpr int kIterations = 10000;

    const auto startTime = std::chrono::steady_clock::now();
    for (int i = 0; i < kIterations; ++i) {
        const int pickedTopicId = allGenerators[topicPickDist(randomEngine)]->topicId();
        const auto generated = engine.generateUniqueForTopic(
            pickedTopicId, generators.registry, scoring, validator, randomEngine);

        CHECK(generated.has_value());
        if (!generated.has_value()) {
            continue;
        }
        ++successCount;

        CHECK(validator.isValid(*generated));
        CHECK(registeredTopicIds.count(generated->question.topicId) == 1);
        CHECK(seenExactHashes.insert(generated->exactHash).second);
    }
    const auto endTime = std::chrono::steady_clock::now();
    const auto elapsedMs =
        std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    CHECK(successCount == kIterations);
    CHECK(elapsedMs < 30000);

    std::filesystem::remove(kStressLogPath);
}

TEST_CASE(GenerationStress_FiveHundredSingleTopicExhaustionIterationsAllSucceed) {
    std::filesystem::remove(kStressLogPath);

    RealGeneratorSet generators;
    GeneratorScoring scoring;
    GeneratedQuestionValidator validator;
    QuestionGenerationEngine engine(kStressLogPath);

    std::mt19937_64 randomEngine{13579ULL};
    constexpr int kBoolOutputTopicId = 9;
    constexpr int kIterations = 500;

    std::unordered_set<std::uint64_t> seenExactHashes;
    int successCount = 0;

    for (int i = 0; i < kIterations; ++i) {
        const auto generated = engine.generateUniqueForTopic(
            kBoolOutputTopicId, generators.registry, scoring, validator, randomEngine);

        CHECK(generated.has_value());
        if (!generated.has_value()) {
            continue;
        }
        ++successCount;
        CHECK(validator.isValid(*generated));
        CHECK(seenExactHashes.insert(generated->exactHash).second);
    }

    CHECK(successCount == kIterations);

    std::filesystem::remove(kStressLogPath);
}

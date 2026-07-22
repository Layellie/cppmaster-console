#include <chrono>
#include <cstdint>
#include <filesystem>
#include <random>
#include <string>
#include <unordered_set>

#include "GeneratedQuestionValidator.h"
#include "GeneratorRegistry.h"
#include "GeneratorScoring.h"
#include "QuestionGenerationEngine.h"
#include "TestRunner.h"
#include "generators/ArithmeticOperatorPredictGenerator.h"
#include "generators/ArrayElementPredictGenerator.h"
#include "generators/BoolOutputPredictGenerator.h"
#include "generators/ClassMemberPredictGenerator.h"
#include "generators/ForLoopSumPredictGenerator.h"
#include "generators/FunctionReturnPredictGenerator.h"
#include "generators/IfElsePredictGenerator.h"
#include "generators/InheritanceOverridePredictGenerator.h"
#include "generators/IntArithmeticPredictGenerator.h"
#include "generators/MapLookupPredictGenerator.h"
#include "generators/ModOperatorPredictGenerator.h"
#include "generators/PointerDereferencePredictGenerator.h"
#include "generators/SortWithLambdaPredictGenerator.h"
#include "generators/StringConcatPredictGenerator.h"
#include "generators/TryCatchPredictGenerator.h"
#include "generators/VectorPushBackPredictGenerator.h"
#include "generators/WhileLoopCountPredictGenerator.h"

namespace {

constexpr const char* kStressLogPath = "tests/test_data/generation_stress_test.log";

struct RealGeneratorSet {
    IntArithmeticPredictGenerator intArithmetic;
    BoolOutputPredictGenerator boolOutput;
    ArithmeticOperatorPredictGenerator arithmeticOperator;
    ModOperatorPredictGenerator modOperator;
    IfElsePredictGenerator ifElse;
    ForLoopSumPredictGenerator forLoopSum;
    WhileLoopCountPredictGenerator whileLoopCount;
    ArrayElementPredictGenerator arrayElement;
    VectorPushBackPredictGenerator vectorPushBack;
    StringConcatPredictGenerator stringConcat;
    FunctionReturnPredictGenerator functionReturn;
    PointerDereferencePredictGenerator pointerDereference;
    ClassMemberPredictGenerator classMember;
    InheritanceOverridePredictGenerator inheritanceOverride;
    MapLookupPredictGenerator mapLookup;
    SortWithLambdaPredictGenerator sortWithLambda;
    TryCatchPredictGenerator tryCatch;

    GeneratorRegistry registry;

    RealGeneratorSet() {
        registry.registerGenerator(intArithmetic);
        registry.registerGenerator(boolOutput);
        registry.registerGenerator(arithmeticOperator);
        registry.registerGenerator(modOperator);
        registry.registerGenerator(ifElse);
        registry.registerGenerator(forLoopSum);
        registry.registerGenerator(whileLoopCount);
        registry.registerGenerator(arrayElement);
        registry.registerGenerator(vectorPushBack);
        registry.registerGenerator(stringConcat);
        registry.registerGenerator(functionReturn);
        registry.registerGenerator(pointerDereference);
        registry.registerGenerator(classMember);
        registry.registerGenerator(inheritanceOverride);
        registry.registerGenerator(mapLookup);
        registry.registerGenerator(sortWithLambda);
        registry.registerGenerator(tryCatch);
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

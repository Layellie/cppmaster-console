#include "GeneratorRegistry.h"

#include "TestRunner.h"
#include "generators/BoolOutputPredictGenerator.h"
#include "generators/IntArithmeticPredictGenerator.h"

TEST_CASE(GeneratorRegistry_UnregisteredTopicReturnsEmpty) {
    GeneratorRegistry registry;
    IntArithmeticPredictGenerator arithmeticGenerator;
    registry.registerGenerator(arithmeticGenerator);
    CHECK(registry.generatorsForTopic(50).empty());
}

TEST_CASE(GeneratorRegistry_GeneratorsForTopicReturnsOnlyMatchingGenerator) {
    GeneratorRegistry registry;
    IntArithmeticPredictGenerator arithmeticGenerator;
    BoolOutputPredictGenerator boolGenerator;
    registry.registerGenerator(arithmeticGenerator);
    registry.registerGenerator(boolGenerator);

    const auto forTopicSix = registry.generatorsForTopic(6);
    CHECK(forTopicSix.size() == 1);
    CHECK(forTopicSix.front()->id() == "IntArithmeticPredictGenerator");

    const auto forTopicNine = registry.generatorsForTopic(9);
    CHECK(forTopicNine.size() == 1);
    CHECK(forTopicNine.front()->id() == "BoolOutputPredictGenerator");
}

TEST_CASE(GeneratorRegistry_AllGeneratorsReturnsEveryRegisteredGeneratorInOrder) {
    GeneratorRegistry registry;
    IntArithmeticPredictGenerator arithmeticGenerator;
    BoolOutputPredictGenerator boolGenerator;
    registry.registerGenerator(arithmeticGenerator);
    registry.registerGenerator(boolGenerator);

    const auto& all = registry.allGenerators();
    CHECK(all.size() == 2);
    CHECK(all[0]->id() == "IntArithmeticPredictGenerator");
    CHECK(all[1]->id() == "BoolOutputPredictGenerator");
}

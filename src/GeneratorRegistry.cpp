#include "GeneratorRegistry.h"

void GeneratorRegistry::registerGenerator(const IQuestionGenerator& generator) {
    generators_.push_back(&generator);
}

std::vector<const IQuestionGenerator*> GeneratorRegistry::generatorsForTopic(int topicId) const {
    std::vector<const IQuestionGenerator*> result;
    for (const IQuestionGenerator* generator : generators_) {
        if (generator->topicId() == topicId) {
            result.push_back(generator);
        }
    }
    return result;
}

const std::vector<const IQuestionGenerator*>& GeneratorRegistry::allGenerators() const {
    return generators_;
}

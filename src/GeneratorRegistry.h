#pragma once

#include <vector>

#include "IQuestionGenerator.h"

class GeneratorRegistry {
public:
    void registerGenerator(const IQuestionGenerator& generator);
    [[nodiscard]] std::vector<const IQuestionGenerator*> generatorsForTopic(int topicId) const;
    [[nodiscard]] const std::vector<const IQuestionGenerator*>& allGenerators() const;

private:
    std::vector<const IQuestionGenerator*> generators_;
};

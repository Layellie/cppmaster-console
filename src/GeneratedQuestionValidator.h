#pragma once

#include "GeneratedQuestion.h"

class GeneratedQuestionValidator {
public:
    [[nodiscard]] bool isValid(const GeneratedQuestion& candidate) const;
};

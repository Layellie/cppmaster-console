#pragma once

#include <cstdint>
#include <string>

#include "Question.h"

struct GeneratedQuestion {
    Question question;
    std::string generatorId;
    std::string exactSignature;
    std::string semanticSignature;
    std::uint64_t exactHash = 0;
    std::uint64_t semanticHash = 0;
};

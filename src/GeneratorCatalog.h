#pragma once

#include <memory>
#include <vector>

#include "IQuestionGenerator.h"

// The single place that knows which question generators exist.
//
// Application used to declare all 17 generators as by-value members, which
// forced its header to include all 17 generator headers and made adding one
// a five-file change. Owning them here behind the IQuestionGenerator
// interface keeps that knowledge in one translation unit: adding a
// generator now means writing it and adding one line to
// makeAllGenerators().
[[nodiscard]] std::vector<std::unique_ptr<IQuestionGenerator>> makeAllGenerators();

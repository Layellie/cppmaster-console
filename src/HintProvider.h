#pragma once

#include <string>

#include "Question.h"

[[nodiscard]] std::string generateHint(const Question& question, int hintLevel);

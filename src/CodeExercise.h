#pragma once

#include <string>
#include <vector>

struct CodeExercise {
    int id = 0;
    std::string tier;
    std::string title;
    std::string description;
    std::string expectedBehavior;
    std::string sampleInput;
    std::string sampleOutput;
    std::vector<std::string> hints;
    std::vector<std::string> requiredKeywords;
    std::string sampleSolution;
    std::string alternativeSolutionNote;
    int baseXp = 0;
};

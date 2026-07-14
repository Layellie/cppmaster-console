#pragma once

#include <string>
#include <vector>

struct Lesson {
    int id = 0;
    int sectionId = 0;
    std::string title;

    // Populated starting in the "static lesson + quiz core" phase.
    std::string explanation;
    std::string syntax;
    std::string exampleCode;
    std::vector<std::string> lineExplanations;
    std::vector<std::string> commonMistakes;
};

#pragma once

#include <vector>

struct Question;

void appendSection2Questions(std::vector<Question>& questions);
void appendSection3Questions(std::vector<Question>& questions);
void appendSection4Questions(std::vector<Question>& questions);
void appendSection5Questions(std::vector<Question>& questions);
void appendSection6Questions(std::vector<Question>& questions);
void appendSection7Questions(std::vector<Question>& questions);
void appendSection8Questions(std::vector<Question>& questions);
void appendSection9Questions(std::vector<Question>& questions);
void appendSection10Questions(std::vector<Question>& questions);

// Scenario and Matching questions, which the other section files don't use.
// They live apart from the per-section files because they deliberately span
// topics: a scenario question asks which of several tools fits a situation,
// which is only interesting once the learner has met more than one of them.
void appendScenarioAndMatchingQuestions(std::vector<Question>& questions);

// Section 1 expansion (topics 1-10), ids 2690+. Separate from the original
// Section 1 questions, which predate the per-section files and still live in
// QuestionManager.cpp.
void appendSection1Questions(std::vector<Question>& questions);

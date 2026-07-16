#pragma once

#include <string>
#include <vector>

#include "Question.h"

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

[[nodiscard]] inline Question toWriteCodeQuestion(const CodeExercise& exercise) {
    Question question;
    question.id = exercise.id;
    question.type = QuestionType::WriteCode;
    question.acceptedAnswers = exercise.requiredKeywords;
    question.baseXp = exercise.baseXp;
    question.explanation = exercise.alternativeSolutionNote;
    return question;
}

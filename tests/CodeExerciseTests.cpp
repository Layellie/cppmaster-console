#include "CodeExercise.h"

#include "CodeExerciseManager.h"
#include "QuizEngine.h"
#include "TestRunner.h"

TEST_CASE(CodeExercise_ToWriteCodeQuestionCarriesRequiredFields) {
    CodeExerciseManager manager;
    const auto exercise = manager.findById(1);
    CHECK(exercise.has_value());

    const Question question = toWriteCodeQuestion(*exercise);
    CHECK(question.id == exercise->id);
    CHECK(question.type == QuestionType::WriteCode);
    CHECK(question.acceptedAnswers == exercise->requiredKeywords);
    CHECK(question.baseXp == exercise->baseXp);
}

TEST_CASE(CodeExercise_EverySampleSolutionPassesItsOwnRequiredKeywords) {
    CodeExerciseManager manager;
    QuizEngine engine;
    for (const CodeExercise& exercise : manager.allExercises()) {
        const Question question = toWriteCodeQuestion(exercise);
        const AnswerResult result = engine.evaluate(question, exercise.sampleSolution);
        CHECK(result.correct);
    }
}

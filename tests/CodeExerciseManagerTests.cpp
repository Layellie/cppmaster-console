#include "CodeExerciseManager.h"

#include <unordered_set>

#include "TestRunner.h"

TEST_CASE(CodeExerciseManager_HasExactlyTwentyFiveExercises) {
    CodeExerciseManager manager;
    CHECK(manager.allExercises().size() == 25);
}

TEST_CASE(CodeExerciseManager_TierCountsMatchBrief) {
    CodeExerciseManager manager;
    CHECK(manager.exercisesForTier("Başlangıç").size() == 7);
    CHECK(manager.exercisesForTier("Orta").size() == 9);
    CHECK(manager.exercisesForTier("İleri").size() == 9);
}

TEST_CASE(CodeExerciseManager_AllIdsAreUnique) {
    CodeExerciseManager manager;
    std::unordered_set<int> seenIds;
    bool foundDuplicate = false;
    for (const CodeExercise& exercise : manager.allExercises()) {
        if (!seenIds.insert(exercise.id).second) {
            foundDuplicate = true;
        }
    }
    CHECK(!foundDuplicate);
}

TEST_CASE(CodeExerciseManager_FindByIdResolvesEveryExercise) {
    CodeExerciseManager manager;
    for (int id = 1; id <= 25; ++id) {
        CHECK(manager.findById(id).has_value());
    }
    CHECK(!manager.findById(26).has_value());
    CHECK(!manager.findById(0).has_value());
}

TEST_CASE(CodeExerciseManager_EveryExerciseHasCompleteContent) {
    CodeExerciseManager manager;
    for (const CodeExercise& exercise : manager.allExercises()) {
        CHECK(!exercise.title.empty());
        CHECK(!exercise.description.empty());
        CHECK(!exercise.expectedBehavior.empty());
        CHECK(!exercise.sampleInput.empty());
        CHECK(!exercise.sampleOutput.empty());
        CHECK(!exercise.hints.empty());
        CHECK(!exercise.requiredKeywords.empty());
        CHECK(!exercise.sampleSolution.empty());
        CHECK(!exercise.alternativeSolutionNote.empty());
        CHECK(exercise.baseXp > 0);
    }
}

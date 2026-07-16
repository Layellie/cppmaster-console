#include "AdaptiveDifficulty.h"

#include "TestRunner.h"

namespace {

Question makeQuestionWithDifficulty(int id, Difficulty difficulty) {
    Question question;
    question.id = id;
    question.difficulty = difficulty;
    return question;
}

}  // namespace

TEST_CASE(AdaptiveDifficulty_BelowTwoCorrectStreakStaysAtEasiestRemaining) {
    const std::vector<Question> remaining = {
        makeQuestionWithDifficulty(1, Difficulty::Easy),
        makeQuestionWithDifficulty(2, Difficulty::Medium),
        makeQuestionWithDifficulty(3, Difficulty::Hard),
    };
    CHECK(selectNextQuestionIndex(remaining, 0, 0) == 0);
    CHECK(selectNextQuestionIndex(remaining, 1, 0) == 0);
}

TEST_CASE(AdaptiveDifficulty_TwoPlusCorrectStreakJumpsToHardestRemaining) {
    const std::vector<Question> remaining = {
        makeQuestionWithDifficulty(1, Difficulty::Easy),
        makeQuestionWithDifficulty(2, Difficulty::Medium),
        makeQuestionWithDifficulty(3, Difficulty::Hard),
    };
    CHECK(selectNextQuestionIndex(remaining, 2, 0) == 2);
    CHECK(selectNextQuestionIndex(remaining, 5, 0) == 2);
}

TEST_CASE(AdaptiveDifficulty_TwoPlusCorrectStreakWithOneRemainingStaysAtZero) {
    const std::vector<Question> remaining = {makeQuestionWithDifficulty(1, Difficulty::Easy)};
    CHECK(selectNextQuestionIndex(remaining, 2, 0) == 0);
}

TEST_CASE(AdaptiveDifficulty_ShouldShowExtraHelpOnlyAtTwoOrMoreWrongInARow) {
    CHECK(!shouldShowExtraHelp(0));
    CHECK(!shouldShowExtraHelp(1));
    CHECK(shouldShowExtraHelp(2));
    CHECK(shouldShowExtraHelp(3));
}

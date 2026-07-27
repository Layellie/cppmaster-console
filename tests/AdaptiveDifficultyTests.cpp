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

namespace {

Question makeDetailedQuestion(
    int id, Difficulty difficulty, QuestionType type, std::string answer) {
    Question question;
    question.id = id;
    question.difficulty = difficulty;
    question.type = type;
    question.acceptedAnswers = {std::move(answer)};
    return question;
}

}  // namespace

TEST_CASE(AdaptiveDifficulty_AvoidsRepeatingThePreviousAnswerWithinTheSameDifficulty) {
    // The real pattern this fixes: a topic holds a multiple choice answered
    // "cout" and a fill-in-the-blank also answered "cout". Both are Easy, so
    // they sit next to each other and the second is answered by copying the
    // line above.
    const std::vector<Question> remaining = {
        makeDetailedQuestion(1, Difficulty::Easy, QuestionType::FillBlank, "cout"),
        makeDetailedQuestion(2, Difficulty::Easy, QuestionType::FillBlank, "iostream"),
        makeDetailedQuestion(3, Difficulty::Hard, QuestionType::TrueFalse, "1"),
    };
    const Question previous =
        makeDetailedQuestion(9, Difficulty::Easy, QuestionType::MultipleChoice, "cout");

    // Without the hint it takes the natural pick, which repeats "cout".
    CHECK(selectNextQuestionIndex(remaining, 0, 0) == 0);
    // With it, it steps to the other Easy question instead.
    CHECK(selectNextQuestionIndex(remaining, 0, 0, &previous) == 1);
}

TEST_CASE(AdaptiveDifficulty_RepetitionAvoidanceNeverLeavesTheChosenDifficulty) {
    // Both Easy questions repeat something about the previous one, and the
    // only clean question is Hard. Difficulty must still win: the selector
    // is not allowed to jump bands just to avoid a repeat.
    const std::vector<Question> remaining = {
        makeDetailedQuestion(1, Difficulty::Easy, QuestionType::FillBlank, "cout"),
        makeDetailedQuestion(2, Difficulty::Easy, QuestionType::FillBlank, "cout"),
        makeDetailedQuestion(3, Difficulty::Hard, QuestionType::TrueFalse, "1"),
    };
    const Question previous =
        makeDetailedQuestion(9, Difficulty::Easy, QuestionType::FillBlank, "cout");

    const std::size_t chosen = selectNextQuestionIndex(remaining, 0, 0, &previous);
    CHECK(chosen == 0 || chosen == 1);
    CHECK(remaining[chosen].difficulty == Difficulty::Easy);
}

TEST_CASE(AdaptiveDifficulty_RepetitionAvoidanceAlsoAppliesOnAStreak) {
    // On a 2+ correct streak the selector takes the hardest remaining; the
    // same tie-breaking must apply at that end of the range.
    const std::vector<Question> remaining = {
        makeDetailedQuestion(1, Difficulty::Easy, QuestionType::TrueFalse, "1"),
        makeDetailedQuestion(2, Difficulty::Hard, QuestionType::FillBlank, "vector"),
        makeDetailedQuestion(3, Difficulty::Hard, QuestionType::FillBlank, "dizi"),
    };
    const Question previous =
        makeDetailedQuestion(9, Difficulty::Hard, QuestionType::FillBlank, "dizi");

    CHECK(selectNextQuestionIndex(remaining, 2, 0) == 2);
    CHECK(selectNextQuestionIndex(remaining, 2, 0, &previous) == 1);
}

TEST_CASE(AdaptiveDifficulty_PrefersDifferentTypeWhenAnswersAlreadyDiffer) {
    const std::vector<Question> remaining = {
        makeDetailedQuestion(1, Difficulty::Easy, QuestionType::TrueFalse, "1"),
        makeDetailedQuestion(2, Difficulty::Easy, QuestionType::MultipleChoice, "b"),
    };
    const Question previous =
        makeDetailedQuestion(9, Difficulty::Easy, QuestionType::TrueFalse, "2");

    CHECK(selectNextQuestionIndex(remaining, 0, 0, &previous) == 1);
}

TEST_CASE(AdaptiveDifficulty_LetteredAnswersCompareByOptionTextNotTheLetter) {
    // The bug this covers: a multiple choice stores "b", so comparing the
    // raw accepted answers made it look unrelated to a fill-in-the-blank
    // answered "cout" — even though both are asking about cout.
    std::vector<Question> remaining = {
        makeDetailedQuestion(1, Difficulty::Easy, QuestionType::FillBlank, "cout"),
        makeDetailedQuestion(2, Difficulty::Easy, QuestionType::FillBlank, "endl"),
    };
    Question previous =
        makeDetailedQuestion(9, Difficulty::Easy, QuestionType::MultipleChoice, "b");
    previous.options = {"cin", "cout", "endl", "return"};

    CHECK(selectNextQuestionIndex(remaining, 0, 0, &previous) == 1);
}

TEST_CASE(AdaptiveDifficulty_AnswerComparisonIgnoresSurroundingPunctuation) {
    // "<iostream>" and "iostream" are the same subject written two ways.
    std::vector<Question> remaining = {
        makeDetailedQuestion(1, Difficulty::Easy, QuestionType::FillBlank, "iostream"),
        makeDetailedQuestion(2, Difficulty::Easy, QuestionType::FillBlank, "string"),
    };
    Question previous =
        makeDetailedQuestion(9, Difficulty::Easy, QuestionType::MultipleChoice, "c");
    previous.options = {"<string>", "<vector>", "<iostream>", "<cmath>"};

    CHECK(selectNextQuestionIndex(remaining, 0, 0, &previous) == 1);
}

TEST_CASE(AdaptiveDifficulty_ShortAnswersDoNotMatchEverything) {
    // A one-character answer like "n" must not be treated as contained in
    // every other answer, or the penalty would fire constantly.
    const Question previous =
        makeDetailedQuestion(9, Difficulty::Easy, QuestionType::FillBlank, "n");
    const Question candidate =
        makeDetailedQuestion(1, Difficulty::Easy, QuestionType::MultipleChoice, "a");
    CHECK(adaptive_detail::repetitionPenalty(candidate, previous) == 0);
}

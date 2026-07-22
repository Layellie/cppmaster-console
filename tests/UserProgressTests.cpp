#include "UserProgress.h"

#include "TestRunner.h"

TEST_CASE(UserProgress_StreakIncrementsAndResetsOnWrong) {
    UserProgress progress(5);
    progress.recordStreak(true);
    progress.recordStreak(true);
    progress.recordStreak(true);
    CHECK(progress.currentStreak() == 3);
    CHECK(progress.longestStreak() == 3);
    progress.recordStreak(false);
    CHECK(progress.currentStreak() == 0);
    CHECK(progress.longestStreak() == 3);
    progress.recordStreak(true);
    CHECK(progress.currentStreak() == 1);
    CHECK(progress.longestStreak() == 3);
}

TEST_CASE(UserProgress_TypedCorrectAnswerCounters) {
    UserProgress progress(5);
    progress.recordTypedCorrectAnswer(QuestionType::WriteCode);
    progress.recordTypedCorrectAnswer(QuestionType::WriteCode);
    progress.recordTypedCorrectAnswer(QuestionType::FindError);
    progress.recordTypedCorrectAnswer(QuestionType::FixCode);
    progress.recordTypedCorrectAnswer(QuestionType::MultipleChoice);
    CHECK(progress.writeCodeCorrectCount() == 2);
    CHECK(progress.errorFixCorrectCount() == 2);
}

TEST_CASE(UserProgress_AddXpAccumulates) {
    UserProgress progress(5);
    progress.addXp(10);
    progress.addXp(25);
    CHECK(progress.totalXp() == 35);
}

TEST_CASE(UserProgress_StatusDefaultsToNotStartedThenSettable) {
    UserProgress progress(5);
    CHECK(progress.statusOf(1) == TopicStatus::NotStarted);
    progress.setStatus(1, TopicStatus::Completed);
    CHECK(progress.statusOf(1) == TopicStatus::Completed);
}

TEST_CASE(UserProgress_RecordAnswerCounters) {
    UserProgress progress(5);
    progress.recordAnswer(true);
    progress.recordAnswer(false);
    progress.recordAnswer(true);
    CHECK(progress.totalQuestionsAnswered() == 3);
    CHECK(progress.totalCorrectAnswers() == 2);
}

TEST_CASE(UserProgress_UnlockedUpToTopicIdDefaultsToOneThenSettable) {
    UserProgress progress(5);
    CHECK(progress.unlockedUpToTopicId() == 1);
    progress.setUnlockedUpToTopicId(20);
    CHECK(progress.unlockedUpToTopicId() == 20);
}

TEST_CASE(UserProgress_CodeExerciseCompletionIsTrackedAndIdempotent) {
    UserProgress progress(5);
    CHECK(!progress.isCodeExerciseCompleted(3));
    progress.markCodeExerciseCompleted(3);
    CHECK(progress.isCodeExerciseCompleted(3));
    CHECK(!progress.isCodeExerciseCompleted(4));

    // Re-completing an exercise must not double-count it.
    progress.markCodeExerciseCompleted(3);
    CHECK(progress.completedCodeExerciseIds().size() == 1);
}

TEST_CASE(UserProgress_RecordSectionExamPassedOnlyIncreases) {
    UserProgress progress(5);
    CHECK(progress.highestSectionExamPassed() == 0);
    progress.recordSectionExamPassed(1);
    CHECK(progress.highestSectionExamPassed() == 1);
    progress.recordSectionExamPassed(1);
    CHECK(progress.highestSectionExamPassed() == 1);
    progress.recordSectionExamPassed(3);
    CHECK(progress.highestSectionExamPassed() == 3);
    progress.recordSectionExamPassed(2);
    CHECK(progress.highestSectionExamPassed() == 3);
}

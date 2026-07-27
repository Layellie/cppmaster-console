#include "QuizSelection.h"

#include <algorithm>
#include <set>
#include <vector>

#include "TestRunner.h"

namespace {

std::vector<Question> makePool(int count) {
    std::vector<Question> pool;
    pool.reserve(static_cast<std::size_t>(count));
    for (int id = 1; id <= count; ++id) {
        Question question;
        question.id = id;
        question.topicId = 1;
        pool.push_back(question);
    }
    return pool;
}

bool never(const Question& /*question*/) {
    return false;
}

}  // namespace

TEST_CASE(QuizSelection_SmallPoolIsReturnedWhole) {
    const auto pool = makePool(6);
    const auto selected = selectQuizQuestionsFrom(pool, 15, never);
    CHECK(selected.size() == 6);
}

TEST_CASE(QuizSelection_LargePoolIsCutToTheRequestedSize) {
    const auto pool = makePool(29);
    const auto selected = selectQuizQuestionsFrom(pool, 15, never);
    CHECK(selected.size() == 15);
}

TEST_CASE(QuizSelection_MistakesNeverFillMoreThanHalfTheQuiz) {
    // The bug this pins down: when every question had been answered wrongly
    // before, mistake-priority filled the whole session, so a retake asked
    // exactly the same set again and no new material ever appeared.
    const auto pool = makePool(29);
    const auto selected = selectQuizQuestionsFrom(pool, 15, [](const Question&) { return true; });

    CHECK(selected.size() == 15);

    // All 29 are "mistakes" here, so the cap cannot be satisfied by fresh
    // questions — the quiz is still filled, just no longer forced to be the
    // same half every time.
    const auto pastMistakes = makePool(29);
    const std::set<int> firstEight = {1, 2, 3, 4, 5, 6, 7, 8};
    const auto mixed = selectQuizQuestionsFrom(
        pool, 15, [&](const Question& q) { return firstEight.count(q.id) == 1; });
    CHECK(mixed.size() == 15);

    const auto mistakeCount = static_cast<std::size_t>(
        std::count_if(mixed.begin(), mixed.end(), [&](const Question& q) {
            return firstEight.count(q.id) == 1;
        }));
    CHECK(mistakeCount <= 15 / 2);
}

TEST_CASE(QuizSelection_LeavesRoomForFreshQuestions) {
    const auto pool = makePool(29);
    const std::set<int> wrongBefore = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    const auto selected = selectQuizQuestionsFrom(
        pool, 10, [&](const Question& q) { return wrongBefore.count(q.id) == 1; });

    CHECK(selected.size() == 10);
    const auto freshCount = static_cast<std::size_t>(
        std::count_if(selected.begin(), selected.end(), [&](const Question& q) {
            return !wrongBefore.contains(q.id);
        }));
    // Half the session is reserved for material the learner has not already
    // been drilled on.
    CHECK(freshCount >= 5);
}

TEST_CASE(QuizSelection_StillRevisitsAtLeastOneMistakeInATinyQuiz) {
    const auto pool = makePool(29);
    const std::set<int> wrongBefore = {7};
    const auto selected = selectQuizQuestionsFrom(
        pool, 1, [&](const Question& q) { return wrongBefore.count(q.id) == 1; });

    CHECK(selected.size() == 1);
    CHECK(selected.front().id == 7);
}

TEST_CASE(QuizSelection_TopsUpFromMistakesWhenFreshQuestionsRunOut) {
    // 20 of 22 were answered wrongly, so fresh questions alone cannot fill a
    // 15-question quiz; the rest must come from the mistakes rather than the
    // session being short.
    const auto pool = makePool(22);
    const auto selected = selectQuizQuestionsFrom(
        pool, 15, [](const Question& q) { return q.id <= 20; });
    CHECK(selected.size() == 15);
}

TEST_CASE(QuizSelection_ReturnsNoDuplicates) {
    const auto pool = makePool(29);
    const auto selected = selectQuizQuestionsFrom(
        pool, 15, [](const Question& q) { return q.id % 3 == 0; });

    std::set<int> ids;
    for (const Question& question : selected) {
        CHECK(ids.insert(question.id).second);
    }
    CHECK(ids.size() == selected.size());
}

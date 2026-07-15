#include "QuestionManager.h"

#include <unordered_set>

#include "TestRunner.h"

namespace {
// The Section 1 exam's fixed question set, as defined in Application.cpp's
// kExamQuestionIds — duplicated here deliberately so this test fails loudly
// if that list and the question catalog ever drift apart.
constexpr int kExamQuestionIds[] = {
    1, 2, 3, 4, 5, 6, 19, 20, 33, 35,
    61, 62, 63, 64, 65, 66, 67, 68, 69, 71,
};
}  // namespace

TEST_CASE(QuestionManager_EveryExamQuestionIdResolves) {
    QuestionManager manager;
    for (const int questionId : kExamQuestionIds) {
        CHECK(manager.findById(questionId).has_value());
    }
}

TEST_CASE(QuestionManager_NoDuplicateQuestionIds) {
    QuestionManager manager;
    std::unordered_set<int> seenIds;
    bool foundDuplicate = false;
    for (int topicId = 1; topicId <= 10; ++topicId) {
        for (const Question& question : manager.questionsForTopic(topicId)) {
            if (!seenIds.insert(question.id).second) {
                foundDuplicate = true;
            }
        }
    }
    CHECK(!foundDuplicate);
}

TEST_CASE(QuestionManager_FindByIdReturnsNulloptForUnknownId) {
    QuestionManager manager;
    CHECK(!manager.findById(999999).has_value());
}

TEST_CASE(QuestionManager_QuestionsForTopicReturnsOnlyMatchingTopic) {
    QuestionManager manager;
    const auto topic1Questions = manager.questionsForTopic(1);
    CHECK(!topic1Questions.empty());
    for (const Question& question : topic1Questions) {
        CHECK(question.topicId == 1);
    }
}

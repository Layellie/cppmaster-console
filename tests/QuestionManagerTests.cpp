#include "QuestionManager.h"

#include <unordered_set>

#include "ExamContent.h"
#include "TestRunner.h"

TEST_CASE(QuestionManager_EveryExamQuestionIdResolves) {
    QuestionManager manager;
    for (const int questionId : examQuestionIdsForSection(1)) {
        CHECK(manager.findById(questionId).has_value());
    }
}

TEST_CASE(QuestionManager_NoDuplicateQuestionIds) {
    QuestionManager manager;
    std::unordered_set<int> seenIds;
    bool foundDuplicate = false;
    for (int topicId = 1; topicId <= 100; ++topicId) {
        for (const Question& question : manager.questionsForTopic(topicId)) {
            if (!seenIds.insert(question.id).second) {
                foundDuplicate = true;
            }
        }
    }
    CHECK(!foundDuplicate);
}

TEST_CASE(QuestionManager_EveryTopicElevenToTwentyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 11; topicId <= 20; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
}

TEST_CASE(QuestionManager_EveryTopicTwentyOneToThirtyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 21; topicId <= 30; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
}

TEST_CASE(QuestionManager_EveryTopicThirtyOneToFortyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 31; topicId <= 40; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
}

TEST_CASE(QuestionManager_EveryTopicFortyOneToFiftyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 41; topicId <= 50; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
}

TEST_CASE(QuestionManager_EveryTopicFiftyOneToSixtyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 51; topicId <= 60; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
}

TEST_CASE(QuestionManager_EveryTopicSixtyOneToSeventyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 61; topicId <= 70; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
}

TEST_CASE(QuestionManager_EveryTopicSeventyOneToEightyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 71; topicId <= 80; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
}

TEST_CASE(QuestionManager_EveryTopicEightyOneToNinetyHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 81; topicId <= 90; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
}

TEST_CASE(QuestionManager_EveryTopicNinetyOneToHundredHasAtLeastTwentyNineQuestions) {
    QuestionManager manager;
    for (int topicId = 91; topicId <= 100; ++topicId) {
        const auto questions = manager.questionsForTopic(topicId);
        CHECK(questions.size() >= 29);
        for (const Question& question : questions) {
            CHECK(question.topicId == topicId);
        }
    }
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

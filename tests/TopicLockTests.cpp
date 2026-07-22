#include "TopicLock.h"

#include "TestRunner.h"

TEST_CASE(TopicLock_SectionOneIsAlwaysRecommendedWithNoExamsPassed) {
    CHECK(isSectionRecommended(1, 0));
    CHECK(!isSectionRecommended(2, 0));
    CHECK(!isSectionRecommended(10, 0));
}

TEST_CASE(TopicLock_SectionRecommendedExactlyAtHighestPlusOne) {
    CHECK(isSectionRecommended(3, 2));
    CHECK(!isSectionRecommended(4, 2));
    CHECK(isSectionRecommended(1, 2));
    CHECK(isSectionRecommended(2, 2));
}

TEST_CASE(TopicLock_ExamUnlockedWhenLockDisabledRegardlessOfRatio) {
    CHECK(sectionExamIsUnlocked(false, 0.0, 0.7));
    CHECK(sectionExamIsUnlocked(false, 1.0, 0.7));
}

TEST_CASE(TopicLock_ExamGateRespectsThresholdWhenLockEnabled) {
    CHECK(!sectionExamIsUnlocked(true, 0.69, 0.7));
    CHECK(sectionExamIsUnlocked(true, 0.7, 0.7));
    CHECK(sectionExamIsUnlocked(true, 1.0, 0.7));
}

TEST_CASE(TopicLock_TopicUnlockedWhenLockDisabledRegardlessOfEverything) {
    CHECK(topicIsUnlocked(false, 100, 1, TopicStatus::NotStarted));
}

TEST_CASE(TopicLock_TopicWithinInitialFrontierIsAlwaysUnlocked) {
    // A fresh skill-based frontier of 20 unlocks topics 1-20 regardless of
    // any prior topic's completion status.
    CHECK(topicIsUnlocked(true, 1, 20, TopicStatus::NotStarted));
    CHECK(topicIsUnlocked(true, 20, 20, TopicStatus::NotStarted));
}

TEST_CASE(TopicLock_TopicBeyondFrontierRequiresPreviousTopicCompleted) {
    CHECK(!topicIsUnlocked(true, 21, 20, TopicStatus::NotStarted));
    CHECK(!topicIsUnlocked(true, 21, 20, TopicStatus::Learning));
    CHECK(topicIsUnlocked(true, 21, 20, TopicStatus::Completed));
    CHECK(topicIsUnlocked(true, 21, 20, TopicStatus::Mastered));
}

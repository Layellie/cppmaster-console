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

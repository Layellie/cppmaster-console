#include "LessonManager.h"

#include "TestRunner.h"

TEST_CASE(LessonManager_HasOneHundredTopicsAcrossTenSections) {
    LessonManager manager;
    CHECK(manager.allLessons().size() == 100);
    CHECK(manager.sectionCount() == 10);
}

TEST_CASE(LessonManager_TopicsOneToTenHaveRealContent) {
    LessonManager manager;
    for (int topicId = 1; topicId <= 10; ++topicId) {
        const auto lesson = manager.findById(topicId);
        CHECK(lesson.has_value());
        CHECK(!lesson->explanation.empty());
        CHECK(!lesson->syntax.empty());
        CHECK(!lesson->exampleCode.empty());
    }
}

TEST_CASE(LessonManager_TopicsElevenToFiftyHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 50; ++topicId) {
        const auto lesson = manager.findById(topicId);
        CHECK(lesson.has_value());
        CHECK(!lesson->explanation.empty());
        CHECK(!lesson->syntax.empty());
        CHECK(!lesson->exampleCode.empty());
    }
}

TEST_CASE(LessonManager_TopicsFiftyOneToHundredHaveNoContentYet) {
    LessonManager manager;
    for (int topicId = 51; topicId <= 100; ++topicId) {
        const auto lesson = manager.findById(topicId);
        CHECK(lesson.has_value());
        CHECK(lesson->explanation.empty());
    }
}

TEST_CASE(LessonManager_FindByIdReturnsNulloptForUnknownId) {
    LessonManager manager;
    CHECK(!manager.findById(0).has_value());
    CHECK(!manager.findById(101).has_value());
}

TEST_CASE(LessonManager_SectionTitleAndLessonsInSectionAreConsistent) {
    LessonManager manager;
    CHECK(manager.sectionTitle(1) == "Giriş, çıkış ve değişkenler");
    const auto section1Lessons = manager.lessonsInSection(1);
    CHECK(section1Lessons.size() == 10);
    for (const Lesson& lesson : section1Lessons) {
        CHECK(lesson.sectionId == 1);
    }
}

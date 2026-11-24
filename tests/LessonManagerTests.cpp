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

TEST_CASE(LessonManager_TopicsElevenToHundredHaveRealContent) {
    LessonManager manager;
    for (int topicId = 11; topicId <= 100; ++topicId) {
        const auto lesson = manager.findById(topicId);
        CHECK(lesson.has_value());
        CHECK(!lesson->explanation.empty());
        CHECK(!lesson->syntax.empty());
        CHECK(!lesson->exampleCode.empty());
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

TEST_CASE(LessonManager_ZeroCopyViewsMatchCopyingAccessors) {
    LessonManager manager;
    const auto view = manager.lessonsViewInSection(2);
    const auto copied = manager.lessonsInSection(2);
    CHECK(view.size() == copied.size());
    for (std::size_t i = 0; i < view.size(); ++i) {
        CHECK(view[i].id == copied[i].id);
    }
    CHECK(manager.lessonsViewInSection(99).empty());

    const Lesson* const found = manager.findPtrById(15);
    CHECK(found != nullptr);
    CHECK(found->id == 15);
    CHECK(manager.findPtrById(999) == nullptr);
}

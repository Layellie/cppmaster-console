#include "ExamContent.h"

#include <map>
#include <unordered_set>

#include "QuestionManager.h"
#include "TestRunner.h"

TEST_CASE(ExamContent_SectionOneExamMatchesExistingCuratedSet) {
    const auto ids = examQuestionIdsForSection(1);
    const std::vector<int> expected = {1, 2, 3, 4, 5, 6, 19, 20, 33, 35,
                                        61, 62, 63, 64, 65, 66, 67, 68, 69, 71};
    CHECK(ids == expected);
}

TEST_CASE(ExamContent_EverySectionExamHasTwentyUniqueResolvableIds) {
    QuestionManager manager;
    for (int sectionId = 1; sectionId <= 10; ++sectionId) {
        const auto ids = examQuestionIdsForSection(sectionId);
        CHECK(ids.size() == 20);
        std::unordered_set<int> seen;
        for (int id : ids) {
            CHECK(seen.insert(id).second);
            CHECK(manager.findById(id).has_value());
        }
    }
}

TEST_CASE(ExamContent_SectionsTwoToTenCoverEveryTopicTwice) {
    QuestionManager manager;
    for (int sectionId = 2; sectionId <= 10; ++sectionId) {
        const auto ids = examQuestionIdsForSection(sectionId);
        std::map<int, int> countPerTopic;
        for (int id : ids) {
            const auto question = manager.findById(id);
            CHECK(question.has_value());
            if (question.has_value()) {
                ++countPerTopic[question->topicId];
            }
        }
        const int firstTopic = (sectionId - 1) * 10 + 1;
        for (int topic = firstTopic; topic < firstTopic + 10; ++topic) {
            CHECK(countPerTopic[topic] == 2);
        }
    }
}

TEST_CASE(ExamContent_FinalExamHasOneHundredUniqueResolvableIdsCoveringEveryTopic) {
    QuestionManager manager;
    const auto ids = finalExamQuestionIds();
    CHECK(ids.size() == 100);
    std::unordered_set<int> seen;
    std::map<int, int> countPerTopic;
    for (int id : ids) {
        CHECK(seen.insert(id).second);
        const auto question = manager.findById(id);
        CHECK(question.has_value());
        if (question.has_value()) {
            ++countPerTopic[question->topicId];
        }
    }
    for (int topic = 1; topic <= 100; ++topic) {
        CHECK(countPerTopic[topic] == 1);
    }
}

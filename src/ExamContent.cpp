#include "ExamContent.h"

namespace {

constexpr int kFirstFormulaTopic = 11;
constexpr int kFirstFormulaTopicBaseId = 73;
constexpr int kQuestionsPerTopic = 29;
constexpr int kMediumMultipleChoiceOffset = 3;
constexpr int kMediumTrueFalseOffset = 12;
constexpr int kTopicsPerSection = 10;

int baseIdForTopic(int topicId) {
    return kFirstFormulaTopicBaseId + (topicId - kFirstFormulaTopic) * kQuestionsPerTopic;
}

}  // namespace

std::vector<int> examQuestionIdsForSection(int sectionId) {
    if (sectionId == 1) {
        return {1, 2, 3, 4, 5, 6, 19, 20, 33, 35, 61, 62, 63, 64, 65, 66, 67, 68, 69, 71};
    }

    std::vector<int> ids;
    const int firstTopic = (sectionId - 1) * kTopicsPerSection + 1;
    for (int topic = firstTopic; topic < firstTopic + kTopicsPerSection; ++topic) {
        const int base = baseIdForTopic(topic);
        ids.push_back(base + kMediumMultipleChoiceOffset);
        ids.push_back(base + kMediumTrueFalseOffset);
    }
    return ids;
}

std::vector<int> finalExamQuestionIds() {
    std::vector<int> ids = {1, 7, 13, 19, 25, 31, 37, 43, 49, 55};
    for (int topic = kFirstFormulaTopic; topic <= 100; ++topic) {
        ids.push_back(baseIdForTopic(topic) + kMediumMultipleChoiceOffset);
    }
    return ids;
}

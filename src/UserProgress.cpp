#include "UserProgress.h"

UserProgress::UserProgress(int topicCount) {
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        statusByTopicId_[topicId] = TopicStatus::NotStarted;
    }
}

TopicStatus UserProgress::statusOf(int topicId) const {
    const auto it = statusByTopicId_.find(topicId);
    if (it == statusByTopicId_.end()) {
        return TopicStatus::NotStarted;
    }
    return it->second;
}

void UserProgress::setStatus(int topicId, TopicStatus status) {
    statusByTopicId_[topicId] = status;
}

int UserProgress::totalXp() const {
    return totalXp_;
}

void UserProgress::addXp(int amount) {
    totalXp_ += amount;
}

int UserProgress::totalQuestionsAnswered() const {
    return totalQuestionsAnswered_;
}

int UserProgress::totalCorrectAnswers() const {
    return totalCorrectAnswers_;
}

void UserProgress::recordAnswer(bool correct) {
    ++totalQuestionsAnswered_;
    if (correct) {
        ++totalCorrectAnswers_;
    }
}

void UserProgress::setAnsweredCounters(int totalAnswered, int totalCorrect) {
    totalQuestionsAnswered_ = totalAnswered;
    totalCorrectAnswers_ = totalCorrect;
}

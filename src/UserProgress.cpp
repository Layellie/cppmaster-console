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

int UserProgress::currentStreak() const {
    return currentStreak_;
}

int UserProgress::longestStreak() const {
    return longestStreak_;
}

void UserProgress::recordStreak(bool correct) {
    if (correct) {
        ++currentStreak_;
        if (currentStreak_ > longestStreak_) {
            longestStreak_ = currentStreak_;
        }
    } else {
        currentStreak_ = 0;
    }
}

void UserProgress::setStreakCounters(int current, int longest) {
    currentStreak_ = current;
    longestStreak_ = longest;
}

int UserProgress::writeCodeCorrectCount() const {
    return writeCodeCorrectCount_;
}

int UserProgress::errorFixCorrectCount() const {
    return errorFixCorrectCount_;
}

void UserProgress::recordTypedCorrectAnswer(QuestionType type) {
    if (type == QuestionType::WriteCode) {
        ++writeCodeCorrectCount_;
    } else if (type == QuestionType::FindError || type == QuestionType::FixCode) {
        ++errorFixCorrectCount_;
    }
}

void UserProgress::setTypedCorrectCounters(int writeCode, int errorFix) {
    writeCodeCorrectCount_ = writeCode;
    errorFixCorrectCount_ = errorFix;
}

int UserProgress::highestSectionExamPassed() const {
    return highestSectionExamPassed_;
}

void UserProgress::recordSectionExamPassed(int sectionId) {
    if (sectionId > highestSectionExamPassed_) {
        highestSectionExamPassed_ = sectionId;
    }
}

void UserProgress::setHighestSectionExamPassed(int value) {
    highestSectionExamPassed_ = value;
}

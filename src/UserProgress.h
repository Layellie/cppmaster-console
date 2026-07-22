#pragma once

#include <unordered_map>

#include "Enums.h"

class UserProgress {
public:
    explicit UserProgress(int topicCount);

    [[nodiscard]] TopicStatus statusOf(int topicId) const;
    void setStatus(int topicId, TopicStatus status);

    [[nodiscard]] int totalXp() const;
    void addXp(int amount);

    [[nodiscard]] int totalQuestionsAnswered() const;
    [[nodiscard]] int totalCorrectAnswers() const;
    void recordAnswer(bool correct);
    void setAnsweredCounters(int totalAnswered, int totalCorrect);

    [[nodiscard]] int currentStreak() const;
    [[nodiscard]] int longestStreak() const;
    void recordStreak(bool correct);
    void setStreakCounters(int current, int longest);

    [[nodiscard]] int writeCodeCorrectCount() const;
    [[nodiscard]] int errorFixCorrectCount() const;
    void recordTypedCorrectAnswer(QuestionType type);
    void setTypedCorrectCounters(int writeCode, int errorFix);

    [[nodiscard]] int highestSectionExamPassed() const;
    void recordSectionExamPassed(int sectionId);
    void setHighestSectionExamPassed(int value);

    // Topics with id <= this are reachable regardless of completion order
    // (set once at first launch based on the user's self-assessed skill
    // level); topics beyond it still unlock one at a time as the previous
    // topic is completed. Defaults to 1 (only the very first topic) for
    // brand-new progress.
    [[nodiscard]] int unlockedUpToTopicId() const;
    void setUnlockedUpToTopicId(int topicId);

private:
    std::unordered_map<int, TopicStatus> statusByTopicId_;
    int totalXp_ = 0;
    int totalQuestionsAnswered_ = 0;
    int totalCorrectAnswers_ = 0;
    int currentStreak_ = 0;
    int longestStreak_ = 0;
    int writeCodeCorrectCount_ = 0;
    int errorFixCorrectCount_ = 0;
    int highestSectionExamPassed_ = 0;
    int unlockedUpToTopicId_ = 1;
};

#pragma once

#include <random>
#include <string>
#include <vector>

#include "AchievementTracker.h"
#include "ConsoleUI.h"
#include "LessonManager.h"
#include "LevelSystem.h"
#include "MistakeTracker.h"
#include "ProgressManager.h"
#include "QuestionGenerationEngine.h"
#include "QuestionManager.h"
#include "QuizEngine.h"
#include "UserProgress.h"
#include "generators/BoolOutputPredictGenerator.h"
#include "generators/IntArithmeticPredictGenerator.h"

class Application {
public:
    Application();

    void run();

private:
    void showMainMenu();
    void handleChoice(int choice);
    void showTopicBrowser();
    void openTopic(int topicId);
    void showLessonContent(const Lesson& lesson);
    void runTopicQuiz(int topicId);
    AnswerResult askOneQuestion(const Question& question, bool trackMistakes = true);
    void checkAchievements(const Question& question, bool correct);
    void awardXpAndCheckLevelUp(int amount);
    void resetProgress();
    void showMistakeReview();
    void runMistakeQuestions(const std::vector<MistakeRecord>& mistakesToAsk);
    void showStatistics();
    void runDailyReview();
    void runQuickTest();
    void showAchievements();
    void runSectionExam();
    void showNotYetAvailable(const std::string& featureName);
    void ensureDataDirectoryExists();

    ConsoleUI ui_;
    LessonManager lessons_;
    QuestionManager questions_;
    QuizEngine quizEngine_;
    UserProgress progress_;
    ProgressManager progressManager_;
    MistakeTracker mistakes_;
    AchievementTracker achievements_;
    QuestionGenerationEngine generationEngine_;
    IntArithmeticPredictGenerator intArithmeticGenerator_;
    BoolOutputPredictGenerator boolOutputGenerator_;
    std::mt19937_64 randomEngine_;
    int nextGeneratedQuestionId_ = 1000;
    bool running_ = true;
};

#pragma once

#include <random>
#include <string>
#include <vector>

#include "AchievementTracker.h"
#include "CodeExerciseManager.h"
#include "ConsoleUI.h"
#include "GeneratedQuestionValidator.h"
#include "GeneratorRegistry.h"
#include "GeneratorScoring.h"
#include "HintProvider.h"
#include "LessonManager.h"
#include "LevelSystem.h"
#include "MistakeTracker.h"
#include "ProgressManager.h"
#include "QuestionGenerationEngine.h"
#include "QuestionManager.h"
#include "QuizEngine.h"
#include "Settings.h"
#include "SettingsManager.h"
#include "UserProgress.h"
#include "generators/ArithmeticOperatorPredictGenerator.h"
#include "generators/BoolOutputPredictGenerator.h"
#include "generators/ForLoopSumPredictGenerator.h"
#include "generators/IfElsePredictGenerator.h"
#include "generators/IntArithmeticPredictGenerator.h"
#include "generators/ModOperatorPredictGenerator.h"

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
    AnswerResult askOneQuestion(
        const Question& question, bool trackMistakes = true, bool allowHints = true);
    void checkAchievements(const Question& question, bool correct);
    void awardXpAndCheckLevelUp(int amount);
    void resetProgress();
    void showMistakeReview();
    void runMistakeQuestions(const std::vector<MistakeRecord>& mistakesToAsk);
    void showStatistics();
    void runDailyReview();
    void runQuickTest();
    void showAchievements();
    void runSectionExam(int sectionId);
    void runFinalExam();
    void showExamMenu();
    void runCodeExercises();
    void runCodeExerciseTier(const std::string& tier);
    void runCodeExercise(const CodeExercise& exercise);
    void showSettingsMenu();
    void exportProgress();
    void importProgress();
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
    CodeExerciseManager codeExercises_;
    QuestionGenerationEngine generationEngine_;
    IntArithmeticPredictGenerator intArithmeticGenerator_;
    BoolOutputPredictGenerator boolOutputGenerator_;
    ArithmeticOperatorPredictGenerator arithmeticOperatorGenerator_;
    ModOperatorPredictGenerator modOperatorGenerator_;
    IfElsePredictGenerator ifElseGenerator_;
    ForLoopSumPredictGenerator forLoopSumGenerator_;
    GeneratorRegistry generatorRegistry_;
    GeneratorScoring generatorScoring_;
    GeneratedQuestionValidator generatedQuestionValidator_;
    Settings settings_;
    SettingsManager settingsManager_;
    std::mt19937_64 randomEngine_;
    int nextGeneratedQuestionId_ = 1000;
    bool running_ = true;
};

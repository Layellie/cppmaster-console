#pragma once

#include <memory>
#include <random>
#include <string>
#include <vector>

#include "AchievementTracker.h"
#include "CodeExerciseManager.h"
#include "ConsoleUI.h"
#include "GeneratedQuestionValidator.h"
#include "GeneratorCatalog.h"
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

class Application {
public:
    Application();

    void run();

private:
    void runFirstLaunchSkillSelection();
    void showMainMenu();
    void handleChoice(int choice);
    void showTopicBrowser();
    void openTopic(int topicId);
    void showLessonContent(const Lesson& lesson);
    // Picks the questions a single topic-quiz session asks. Kept separate
    // from runTopicQuiz so the selection policy (sampling, mistake
    // priority) is readable on its own.
    [[nodiscard]] std::vector<Question> selectQuizQuestions(int topicId);
    void runTopicQuiz(int topicId);
    AnswerResult askOneQuestion(
        const Question& question, bool trackMistakes = true, bool allowHints = true);
    void checkAchievements(const Question& question, bool correct);
    void awardXpAndCheckLevelUp(int amount);
    void saveProgress();
    void resetProgress();
    void showMistakeReview();
    void runMistakeQuestions(const std::vector<MistakeRecord>& mistakesToAsk);
    void showStatistics();
    void runDailyReview();
    void runQuickTest();
    void showAchievements();
    // Section exams and the general final exam differ only in which topics
    // gate them, which questions they ask, their heading, and whether
    // passing records a section milestone — everything else (the gate
    // check, the ask loop, scoring, the perfect-score achievement) is
    // identical, so both funnel through runExam.
    struct ExamPlan {
        std::string heading;
        std::string lockedMessage;
        // Ids only, not Lesson copies: the gate just counts completed
        // topics, and the final exam would otherwise deep-copy all 100
        // lessons (each carrying its explanation, example code and
        // explanation/mistake vectors) to read one status per topic.
        std::vector<int> gatingTopicIds;
        std::vector<int> questionIds;
        int sectionIdToRecordOnPass = 0;  // 0 = don't record (final exam)
    };
    void runExam(const ExamPlan& plan);
    void runSectionExam(int sectionId);
    void runFinalExam();
    void showExamMenu();
    void runCodeExercises();
    void runCodeExerciseTier(const std::string& tier);
    void runCodeExercise(const CodeExercise& exercise);
    void showSettingsMenu();
    void exportProgress();
    void importProgress();
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
    // Owns every generator; GeneratorRegistry below stores non-owning
    // pointers into these, so this must be declared first and outlive it.
    std::vector<std::unique_ptr<IQuestionGenerator>> generators_;
    GeneratorRegistry generatorRegistry_;
    GeneratorScoring generatorScoring_;
    GeneratedQuestionValidator generatedQuestionValidator_;
    Settings settings_;
    SettingsManager settingsManager_;
    std::mt19937_64 randomEngine_;
    int nextGeneratedQuestionId_ = 1000;
    bool running_ = true;
    bool isFirstLaunch_ = false;
};

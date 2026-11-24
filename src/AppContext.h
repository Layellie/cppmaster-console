#pragma once

#include <random>

#include "AchievementTracker.h"
#include "CodeExerciseManager.h"
#include "ConsoleUI.h"
#include "GeneratedQuestionValidator.h"
#include "GeneratorRegistry.h"
#include "GeneratorScoring.h"
#include "LessonManager.h"
#include "MistakeTracker.h"
#include "ProgressManager.h"
#include "QuestionGenerationEngine.h"
#include "QuestionManager.h"
#include "QuizEngine.h"
#include "Settings.h"
#include "SettingsManager.h"
#include "UserProgress.h"

inline constexpr const char* kProgressFilePath = "data/progress.txt";
inline constexpr const char* kProgressBackupPath = "data/progress_corrupted_backup.txt";
inline constexpr const char* kMistakesFilePath = "data/mistakes.txt";
inline constexpr const char* kMistakesBackupPath = "data/mistakes_corrupted_backup.txt";
inline constexpr const char* kAchievementsFilePath = "data/achievements.txt";
inline constexpr const char* kAchievementsBackupPath = "data/achievements_corrupted_backup.txt";
inline constexpr const char* kGeneratedHistoryFilePath = "data/generated_question_history.txt";
inline constexpr const char* kGeneratedHistoryBackupPath =
    "data/generated_question_history_corrupted_backup.txt";
inline constexpr const char* kGenerationLogFilePath = "data/question_generation.log";
inline constexpr const char* kSettingsFilePath = "data/settings.txt";
inline constexpr const char* kSettingsBackupPath = "data/settings_corrupted_backup.txt";

struct AppContext {
    ConsoleUI& ui;
    const LessonManager& lessons;
    const QuestionManager& questions;
    const QuizEngine& quizEngine;
    UserProgress& progress;
    const ProgressManager& progressManager;
    MistakeTracker& mistakes;
    AchievementTracker& achievements;
    const CodeExerciseManager& codeExercises;
    QuestionGenerationEngine& generationEngine;
    const GeneratorRegistry& generatorRegistry;
    GeneratorScoring& generatorScoring;
    const GeneratedQuestionValidator& generatedQuestionValidator;
    Settings& settings;
    const SettingsManager& settingsManager;
    std::mt19937_64& randomEngine;
    int& nextGeneratedQuestionId;
};

void ensureDataDirectoryExists(const ConsoleUI& ui);
void saveProgress(AppContext& context);
void awardXpAndCheckLevelUp(AppContext& context, int amount);

cmake_minimum_required(VERSION 3.20)

project(CppMasterConsole
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(apply_strict_warnings target)
    if (MSVC)
        target_compile_options(${target} PRIVATE /W4 /permissive-)
    else()
        target_compile_options(
            ${target}
            PRIVATE
            -Wall
            -Wextra
            -Wpedantic
            -Wconversion
            -Wshadow
        )
    endif()
endfunction()

add_library(CppMasterConsoleLib STATIC
    src/Enums.h
    src/UserProgress.h
    src/UserProgress.cpp
    src/Lesson.h
    src/LessonManager.h
    src/LessonManager.cpp
    src/LessonContent.h
    src/LessonContentSection2.cpp
    src/LessonContentSection3.cpp
    src/LessonContentSection4.cpp
    src/LessonContentSection5.cpp
    src/LessonContentSection6.cpp
    src/LessonContentSection7.cpp
    src/LessonContentSection8.cpp
    src/LessonContentSection9.cpp
    src/LessonContentSection10.cpp
    src/ConsoleUI.h
    src/ConsoleUI.cpp
    src/Question.h
    src/QuestionManager.h
    src/QuestionManager.cpp
    src/QuestionContent.h
    src/QuestionsSection2.cpp
    src/QuestionsSection3.cpp
    src/QuestionsSection4.cpp
    src/QuestionsSection5.cpp
    src/QuestionsSection6.cpp
    src/QuestionsSection7.cpp
    src/QuestionsSection8.cpp
    src/QuestionsSection9.cpp
    src/QuestionsSection10.cpp
    src/QuizEngine.h
    src/QuizEngine.cpp
    src/LevelSystem.h
    src/TopicLock.h
    src/AchievementTracker.h
    src/AchievementTracker.cpp
    src/ProgressManager.h
    src/ProgressManager.cpp
    src/Settings.h
    src/SettingsManager.h
    src/SettingsManager.cpp
    src/MistakeTracker.h
    src/MistakeTracker.cpp
    src/FnvHash.h
    src/GeneratedQuestion.h
    src/QuestionHistory.h
    src/QuestionHistory.cpp
    src/IQuestionGenerator.h
    src/QuestionGenerationEngine.h
    src/QuestionGenerationEngine.cpp
    src/generators/IntArithmeticPredictGenerator.h
    src/generators/IntArithmeticPredictGenerator.cpp
    src/generators/BoolOutputPredictGenerator.h
    src/generators/BoolOutputPredictGenerator.cpp
    src/Application.h
    src/Application.cpp
    src/HintProvider.h
    src/HintProvider.cpp
    src/AdaptiveDifficulty.h
    src/CodeExercise.h
    src/CodeExerciseManager.h
    src/CodeExerciseManager.cpp
    src/ExamContent.h
    src/ExamContent.cpp
    src/ParameterDomain.h
    src/GeneratedQuestionValidator.h
    src/GeneratedQuestionValidator.cpp
    src/GeneratorRegistry.h
    src/GeneratorRegistry.cpp
    src/GeneratorScoring.h
    src/GeneratorScoring.cpp
)

target_include_directories(CppMasterConsoleLib PUBLIC src)
apply_strict_warnings(CppMasterConsoleLib)

add_executable(CppMasterConsole src/main.cpp)
target_link_libraries(CppMasterConsole PRIVATE CppMasterConsoleLib)
apply_strict_warnings(CppMasterConsole)

enable_testing()

add_executable(CppMasterConsoleTests
    tests/TestRunner.h
    tests/main.cpp
    tests/FnvHashTests.cpp
    tests/LevelSystemTests.cpp
    tests/TopicLockTests.cpp
    tests/UserProgressTests.cpp
    tests/QuizEngineTests.cpp
    tests/ProgressManagerTests.cpp
    tests/MistakeTrackerTests.cpp
    tests/AchievementTrackerTests.cpp
    tests/QuestionHistoryTests.cpp
    tests/QuestionGenerationEngineTests.cpp
    tests/GeneratorsTests.cpp
    tests/QuestionManagerTests.cpp
    tests/LessonManagerTests.cpp
    tests/SettingsManagerTests.cpp
    tests/HintProviderTests.cpp
    tests/CodeExerciseManagerTests.cpp
    tests/CodeExerciseTests.cpp
    tests/AdaptiveDifficultyTests.cpp
    tests/ExamContentTests.cpp
    tests/ParameterDomainTests.cpp
    tests/GeneratedQuestionValidatorTests.cpp
    tests/GeneratorRegistryTests.cpp
    tests/GeneratorScoringTests.cpp
)
target_link_libraries(CppMasterConsoleTests PRIVATE CppMasterConsoleLib)
target_include_directories(CppMasterConsoleTests PRIVATE tests)
apply_strict_warnings(CppMasterConsoleTests)

add_test(NAME CppMasterConsoleTests COMMAND CppMasterConsoleTests)

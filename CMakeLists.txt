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
    src/ConsoleUI.h
    src/ConsoleUI.cpp
    src/Question.h
    src/QuestionManager.h
    src/QuestionManager.cpp
    src/QuizEngine.h
    src/QuizEngine.cpp
    src/LevelSystem.h
    src/AchievementTracker.h
    src/AchievementTracker.cpp
    src/ProgressManager.h
    src/ProgressManager.cpp
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
    tests/UserProgressTests.cpp
    tests/QuizEngineTests.cpp
)
target_link_libraries(CppMasterConsoleTests PRIVATE CppMasterConsoleLib)
target_include_directories(CppMasterConsoleTests PRIVATE tests)
apply_strict_warnings(CppMasterConsoleTests)

add_test(NAME CppMasterConsoleTests COMMAND CppMasterConsoleTests)

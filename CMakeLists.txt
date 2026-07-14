cmake_minimum_required(VERSION 3.20)

project(CppMasterConsole
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(CppMasterConsole
    src/main.cpp
    src/Enums.h
    src/UserProgress.h
    src/UserProgress.cpp
    src/Lesson.h
    src/LessonManager.h
    src/LessonManager.cpp
)

target_include_directories(CppMasterConsole PRIVATE src)

if (MSVC)
    target_compile_options(CppMasterConsole PRIVATE /W4 /permissive-)
else()
    target_compile_options(
        CppMasterConsole
        PRIVATE
        -Wall
        -Wextra
        -Wpedantic
        -Wconversion
        -Wshadow
    )
endif()

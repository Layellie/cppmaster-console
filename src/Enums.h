#pragma once

enum class QuestionType {
    MultipleChoice,
    TrueFalse,
    FillBlank,
    CompleteLine,
    PredictOutput,
    FindError,
    FixCode,
    OrderCode,
    WriteCode,
    Scenario,
    Matching
};

enum class Difficulty {
    VeryEasy = 1,
    Easy = 2,
    Medium = 3,
    Hard = 4,
    VeryHard = 5
};

static_assert(static_cast<int>(Difficulty::VeryEasy) == 1);
static_assert(static_cast<int>(Difficulty::Easy) == 2);
static_assert(static_cast<int>(Difficulty::Medium) == 3);
static_assert(static_cast<int>(Difficulty::Hard) == 4);
static_assert(static_cast<int>(Difficulty::VeryHard) == 5);

enum class TopicStatus {
    NotStarted,
    Learning,
    Completed,
    Mastered
};

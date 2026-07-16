#pragma once

#include <optional>
#include <string>
#include <vector>

#include "CodeExercise.h"

class CodeExerciseManager {
public:
    CodeExerciseManager();

    [[nodiscard]] std::vector<CodeExercise> exercisesForTier(const std::string& tier) const;
    [[nodiscard]] std::optional<CodeExercise> findById(int id) const;
    [[nodiscard]] const std::vector<CodeExercise>& allExercises() const;

private:
    void addBeginnerExercises();
    void addIntermediateExercises();
    void addAdvancedExercises();

    std::vector<CodeExercise> exercises_;
};

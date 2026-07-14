#pragma once

#include <string>

#include "UserProgress.h"

struct ProgressLoadResult {
    UserProgress progress;
    bool wasCorrupted;
};

class ProgressManager {
public:
    [[nodiscard]] ProgressLoadResult load(
        const std::string& filePath, const std::string& backupPath, int topicCount) const;
    void save(const UserProgress& progress, const std::string& filePath, int topicCount) const;
};

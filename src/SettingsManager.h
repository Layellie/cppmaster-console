#pragma once

#include <string>

#include "Settings.h"

struct SettingsLoadResult {
    Settings settings;
    bool wasCorrupted;
};

class SettingsManager {
public:
    [[nodiscard]] SettingsLoadResult load(
        const std::string& filePath, const std::string& backupPath) const;
    void save(const Settings& settings, const std::string& filePath) const;
};

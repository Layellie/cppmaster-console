#include "SettingsManager.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <system_error>

namespace {

bool tryParseInt(const std::string& text, int& outValue) {
    if (text.empty()) {
        return false;
    }
    try {
        std::size_t consumedChars = 0;
        const int value = std::stoi(text, &consumedChars);
        if (consumedChars != text.size()) {
            return false;
        }
        outValue = value;
        return true;
    } catch (const std::exception&) {
        return false;
    }
}

bool tryParseBool(const std::string& text, bool& outValue) {
    if (text == "1") {
        outValue = true;
        return true;
    }
    if (text == "0") {
        outValue = false;
        return true;
    }
    return false;
}

}  // namespace

SettingsLoadResult SettingsManager::load(
    const std::string& filePath, const std::string& backupPath) const {
    Settings settings;

    std::ifstream file(filePath);
    if (!file.is_open()) {
        return SettingsLoadResult{settings, false};
    }

    bool topicLock = settings.topicLockEnabled;
    bool strictCase = settings.strictCaseSensitivity;
    bool lenientWriteCode = settings.lenientWriteCodeTolerance;
    bool fullExplanation = settings.fullExplanationDetail;
    int dailyCap = settings.dailyReviewQuestionCap;
    bool colorEnabled = settings.colorEnabled;
    bool audioAlert = settings.audioAlertEnabled;
    int quickTestCount = settings.quickTestQuestionCount;
    int topicQuizCount = settings.topicQuizQuestionCount;
    bool corrupted = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream lineStream(line);
        std::string recordType;
        lineStream >> recordType;
        std::string valueText;
        lineStream >> valueText;

        if (recordType == "topic_lock") {
            if (!tryParseBool(valueText, topicLock)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "strict_case") {
            if (!tryParseBool(valueText, strictCase)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "lenient_writecode") {
            if (!tryParseBool(valueText, lenientWriteCode)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "full_explanation") {
            if (!tryParseBool(valueText, fullExplanation)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "daily_cap") {
            if (!tryParseInt(valueText, dailyCap)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "color_enabled") {
            if (!tryParseBool(valueText, colorEnabled)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "audio_alert") {
            if (!tryParseBool(valueText, audioAlert)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "quick_test_count") {
            if (!tryParseInt(valueText, quickTestCount)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "topic_quiz_count") {
            if (!tryParseInt(valueText, topicQuizCount)) {
                corrupted = true;
                break;
            }
        } else {
            corrupted = true;
            break;
        }
    }

    if (corrupted) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        return SettingsLoadResult{Settings{}, true};
    }

    settings.topicLockEnabled = topicLock;
    settings.strictCaseSensitivity = strictCase;
    settings.lenientWriteCodeTolerance = lenientWriteCode;
    settings.fullExplanationDetail = fullExplanation;
    settings.dailyReviewQuestionCap = dailyCap;
    settings.colorEnabled = colorEnabled;
    settings.audioAlertEnabled = audioAlert;
    settings.quickTestQuestionCount = quickTestCount;
    settings.topicQuizQuestionCount = topicQuizCount;
    return SettingsLoadResult{settings, false};
}

void SettingsManager::save(const Settings& settings, const std::string& filePath) const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        return;
    }
    file << "topic_lock " << (settings.topicLockEnabled ? 1 : 0) << '\n';
    file << "strict_case " << (settings.strictCaseSensitivity ? 1 : 0) << '\n';
    file << "lenient_writecode " << (settings.lenientWriteCodeTolerance ? 1 : 0) << '\n';
    file << "full_explanation " << (settings.fullExplanationDetail ? 1 : 0) << '\n';
    file << "daily_cap " << settings.dailyReviewQuestionCap << '\n';
    file << "color_enabled " << (settings.colorEnabled ? 1 : 0) << '\n';
    file << "audio_alert " << (settings.audioAlertEnabled ? 1 : 0) << '\n';
    file << "quick_test_count " << settings.quickTestQuestionCount << '\n';
    file << "topic_quiz_count " << settings.topicQuizQuestionCount << '\n';
}

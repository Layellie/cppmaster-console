#include "SettingsManager.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string_view>
#include <system_error>

#include "AtomicFileWrite.h"
#include "ParseUtil.h"

namespace {

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

    struct BoolFieldBinding {
        std::string_view key;
        bool* target;
    };
    struct IntFieldBinding {
        std::string_view key;
        int* target;
    };

    const std::array<BoolFieldBinding, 6> boolFields = {{
        {"topic_lock", &topicLock},
        {"strict_case", &strictCase},
        {"lenient_writecode", &lenientWriteCode},
        {"full_explanation", &fullExplanation},
        {"color_enabled", &colorEnabled},
        {"audio_alert", &audioAlert},
    }};
    const std::array<IntFieldBinding, 3> intFields = {{
        {"daily_cap", &dailyCap},
        {"quick_test_count", &quickTestCount},
        {"topic_quiz_count", &topicQuizCount},
    }};

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string recordType;
        if (!(lineStream >> recordType)) {
            continue;
        }
        std::string valueText;
        lineStream >> valueText;

        const auto boolIt = std::ranges::find_if(
            boolFields, [&](const BoolFieldBinding& field) { return field.key == recordType; });
        if (boolIt != boolFields.end()) {
            if (!tryParseBool(valueText, *boolIt->target)) {
                corrupted = true;
                break;
            }
            continue;
        }

        const auto intIt = std::ranges::find_if(
            intFields, [&](const IntFieldBinding& field) { return field.key == recordType; });
        if (intIt != intFields.end()) {
            if (!tryParseInt(valueText, *intIt->target)) {
                corrupted = true;
                break;
            }
            continue;
        }

        corrupted = true;
        break;
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

bool SettingsManager::save(const Settings& settings, const std::string& filePath) const {
    std::ostringstream buffer;
    buffer << "topic_lock " << (settings.topicLockEnabled ? 1 : 0) << '\n';
    buffer << "strict_case " << (settings.strictCaseSensitivity ? 1 : 0) << '\n';
    buffer << "lenient_writecode " << (settings.lenientWriteCodeTolerance ? 1 : 0) << '\n';
    buffer << "full_explanation " << (settings.fullExplanationDetail ? 1 : 0) << '\n';
    buffer << "daily_cap " << settings.dailyReviewQuestionCap << '\n';
    buffer << "color_enabled " << (settings.colorEnabled ? 1 : 0) << '\n';
    buffer << "audio_alert " << (settings.audioAlertEnabled ? 1 : 0) << '\n';
    buffer << "quick_test_count " << settings.quickTestQuestionCount << '\n';
    buffer << "topic_quiz_count " << settings.topicQuizQuestionCount << '\n';
    return atomicWriteTextFile(filePath, buffer.str());
}

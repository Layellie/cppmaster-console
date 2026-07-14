#include "ProgressManager.h"

#include <cstddef>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <system_error>
#include <utility>

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

bool parseStatusName(const std::string& name, TopicStatus& outStatus) {
    if (name == "NotStarted") {
        outStatus = TopicStatus::NotStarted;
        return true;
    }
    if (name == "Learning") {
        outStatus = TopicStatus::Learning;
        return true;
    }
    if (name == "Completed") {
        outStatus = TopicStatus::Completed;
        return true;
    }
    if (name == "Mastered") {
        outStatus = TopicStatus::Mastered;
        return true;
    }
    return false;
}

std::string statusName(TopicStatus status) {
    switch (status) {
        case TopicStatus::NotStarted:
            return "NotStarted";
        case TopicStatus::Learning:
            return "Learning";
        case TopicStatus::Completed:
            return "Completed";
        case TopicStatus::Mastered:
            return "Mastered";
    }
    return "NotStarted";
}

}  // namespace

ProgressLoadResult ProgressManager::load(
    const std::string& filePath, const std::string& backupPath, int topicCount) const {
    UserProgress progress(topicCount);

    std::ifstream file(filePath);
    if (!file.is_open()) {
        return ProgressLoadResult{std::move(progress), false};
    }

    int xp = 0;
    int answered = 0;
    int correct = 0;
    int streakCurrent = 0;
    int streakLongest = 0;
    int writeCodeCorrect = 0;
    int errorFixCorrect = 0;
    bool corrupted = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream lineStream(line);
        std::string recordType;
        lineStream >> recordType;

        if (recordType == "xp") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, xp)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "answered") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, answered)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "correct") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, correct)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "streak_current") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, streakCurrent)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "streak_longest") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, streakLongest)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "writecode_correct") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, writeCodeCorrect)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "errorfix_correct") {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, errorFixCorrect)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "topic") {
            std::string topicIdText;
            std::string statusText;
            lineStream >> topicIdText >> statusText;
            int topicId = 0;
            TopicStatus status = TopicStatus::NotStarted;
            if (!tryParseInt(topicIdText, topicId) || !parseStatusName(statusText, status)) {
                corrupted = true;
                break;
            }
            progress.setStatus(topicId, status);
        } else {
            corrupted = true;
            break;
        }
    }

    if (corrupted) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        return ProgressLoadResult{UserProgress(topicCount), true};
    }

    progress.addXp(xp);
    progress.setAnsweredCounters(answered, correct);
    progress.setStreakCounters(streakCurrent, streakLongest);
    progress.setTypedCorrectCounters(writeCodeCorrect, errorFixCorrect);
    return ProgressLoadResult{std::move(progress), false};
}

void ProgressManager::save(
    const UserProgress& progress, const std::string& filePath, int topicCount) const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        return;
    }
    file << "xp " << progress.totalXp() << '\n';
    file << "answered " << progress.totalQuestionsAnswered() << '\n';
    file << "correct " << progress.totalCorrectAnswers() << '\n';
    file << "streak_current " << progress.currentStreak() << '\n';
    file << "streak_longest " << progress.longestStreak() << '\n';
    file << "writecode_correct " << progress.writeCodeCorrectCount() << '\n';
    file << "errorfix_correct " << progress.errorFixCorrectCount() << '\n';
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        file << "topic " << topicId << ' ' << statusName(progress.statusOf(topicId)) << '\n';
    }
}

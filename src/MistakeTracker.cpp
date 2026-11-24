#include "MistakeTracker.h"

#include <algorithm>
#include <cstdint>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <system_error>
#include <utility>

#include "AtomicFileWrite.h"
#include "ParseUtil.h"

namespace {

bool tryParseEpochSeconds(const std::string& text, std::chrono::system_clock::time_point& outTime) {
    std::int64_t seconds = 0;
    if (!tryParseInt64(text, seconds)) {
        return false;
    }
    outTime = std::chrono::system_clock::from_time_t(static_cast<std::time_t>(seconds));
    return true;
}

}  // namespace

void MistakeTracker::recordWrong(int questionId) {
    const auto now = std::chrono::system_clock::now();
    const auto it = recordsByQuestionId_.find(questionId);
    if (it == recordsByQuestionId_.end()) {
        MistakeRecord record;
        record.questionId = questionId;
        record.firstWrongAt = now;
        record.lastWrongAt = now;
        record.wrongCount = 1;
        record.correctAfterWrongCount = 0;
        recordsByQuestionId_[questionId] = record;
    } else {
        it->second.lastWrongAt = now;
        ++it->second.wrongCount;
    }
}

void MistakeTracker::recordCorrectRetry(int questionId) {
    const auto it = recordsByQuestionId_.find(questionId);
    if (it == recordsByQuestionId_.end()) {
        return;
    }
    ++it->second.correctAfterWrongCount;
}

bool MistakeTracker::hasMistake(int questionId) const {
    return recordsByQuestionId_.contains(questionId);
}

std::size_t MistakeTracker::count() const noexcept {
    return recordsByQuestionId_.size();
}

std::optional<MistakeRecord> MistakeTracker::findMistake(int questionId) const {
    const auto it = recordsByQuestionId_.find(questionId);
    if (it == recordsByQuestionId_.end()) {
        return std::nullopt;
    }
    return it->second;
}

std::vector<MistakeRecord> MistakeTracker::allMistakesOldestFirst() const {
    std::vector<MistakeRecord> result;
    result.reserve(recordsByQuestionId_.size());
    for (const auto& entry : recordsByQuestionId_) {
        result.push_back(entry.second);
    }
    std::ranges::sort(result, [](const MistakeRecord& left, const MistakeRecord& right) {
        return left.lastWrongAt < right.lastWrongAt;
    });
    return result;
}

bool MistakeTracker::loadFromFile(const std::string& filePath, const std::string& backupPath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    std::unordered_map<int, MistakeRecord> parsedRecords;
    bool corrupted = false;

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string recordType;
        if (!(lineStream >> recordType)) {
            continue;
        }

        if (recordType != "mistake") {
            corrupted = true;
            break;
        }

        std::string questionIdText;
        std::string firstWrongText;
        std::string lastWrongText;
        std::string wrongCountText;
        std::string correctAfterWrongText;
        lineStream >> questionIdText >> firstWrongText >> lastWrongText >> wrongCountText >>
            correctAfterWrongText;

        MistakeRecord record;
        if (!tryParseInt(questionIdText, record.questionId) ||
            !tryParseEpochSeconds(firstWrongText, record.firstWrongAt) ||
            !tryParseEpochSeconds(lastWrongText, record.lastWrongAt) ||
            !tryParseInt(wrongCountText, record.wrongCount) ||
            !tryParseInt(correctAfterWrongText, record.correctAfterWrongCount)) {
            corrupted = true;
            break;
        }
        parsedRecords[record.questionId] = record;
    }

    if (corrupted) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        recordsByQuestionId_.clear();
        return true;
    }

    recordsByQuestionId_ = std::move(parsedRecords);
    return false;
}

bool MistakeTracker::saveToFile(const std::string& filePath) const {
    std::ostringstream buffer;
    for (const auto& entry : recordsByQuestionId_) {
        const MistakeRecord& record = entry.second;
        buffer << "mistake " << record.questionId << ' '
               << std::chrono::system_clock::to_time_t(record.firstWrongAt) << ' '
               << std::chrono::system_clock::to_time_t(record.lastWrongAt) << ' '
               << record.wrongCount << ' ' << record.correctAfterWrongCount << '\n';
    }
    return atomicWriteTextFile(filePath, buffer.str());
}

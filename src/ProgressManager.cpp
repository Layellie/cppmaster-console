#include "ProgressManager.h"

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <string_view>
#include <system_error>
#include <utility>
#include <vector>

#include "AtomicFileWrite.h"
#include "ParseUtil.h"

namespace {

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
    int highestSectionExamPassed = 0;
    // Old save files predating the topic-lock feature don't have this key;
    // defaulting to topicCount (fully unlocked) rather than the
    // fresh-UserProgress default of 1 preserves existing users' access to
    // topics they could already reach under the old advisory-only lock.
    int unlockedUpToTopicId = topicCount;
    bool corrupted = false;

    struct IntFieldBinding {
        std::string_view key;
        int* target;
    };

    const std::array<IntFieldBinding, 9> intFields = {{
        {"xp", &xp},
        {"answered", &answered},
        {"correct", &correct},
        {"streak_current", &streakCurrent},
        {"streak_longest", &streakLongest},
        {"writecode_correct", &writeCodeCorrect},
        {"errorfix_correct", &errorFixCorrect},
        {"highest_section_exam_passed", &highestSectionExamPassed},
        {"unlocked_up_to", &unlockedUpToTopicId},
    }};

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream lineStream(line);
        std::string recordType;
        if (!(lineStream >> recordType)) {
            continue;
        }

        const auto fieldIt = std::ranges::find_if(
            intFields, [&](const IntFieldBinding& field) { return field.key == recordType; });
        if (fieldIt != intFields.end()) {
            std::string valueText;
            lineStream >> valueText;
            if (!tryParseInt(valueText, *fieldIt->target)) {
                corrupted = true;
                break;
            }
        } else if (recordType == "exercise_done") {
            std::string valueText;
            lineStream >> valueText;
            int exerciseId = 0;
            if (!tryParseInt(valueText, exerciseId)) {
                corrupted = true;
                break;
            }
            progress.markCodeExerciseCompleted(exerciseId);
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

    const bool countersInvalid = xp < 0 || answered < 0 || correct < 0 || correct > answered ||
                                 streakCurrent < 0 || streakLongest < 0 ||
                                 streakCurrent > streakLongest || writeCodeCorrect < 0 ||
                                 errorFixCorrect < 0 || highestSectionExamPassed < 0 ||
                                 unlockedUpToTopicId < 0;
    if (corrupted || countersInvalid) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        return ProgressLoadResult{UserProgress(topicCount), true};
    }

    progress.addXp(xp);
    progress.setAnsweredCounters(answered, correct);
    progress.setStreakCounters(streakCurrent, streakLongest);
    progress.setTypedCorrectCounters(writeCodeCorrect, errorFixCorrect);
    progress.setHighestSectionExamPassed(highestSectionExamPassed);
    progress.setUnlockedUpToTopicId(unlockedUpToTopicId);
    return ProgressLoadResult{std::move(progress), false};
}

bool ProgressManager::save(
    const UserProgress& progress, const std::string& filePath, int topicCount) const {
    std::ostringstream buffer;
    buffer << "xp " << progress.totalXp() << '\n';
    buffer << "answered " << progress.totalQuestionsAnswered() << '\n';
    buffer << "correct " << progress.totalCorrectAnswers() << '\n';
    buffer << "streak_current " << progress.currentStreak() << '\n';
    buffer << "streak_longest " << progress.longestStreak() << '\n';
    buffer << "writecode_correct " << progress.writeCodeCorrectCount() << '\n';
    buffer << "errorfix_correct " << progress.errorFixCorrectCount() << '\n';
    buffer << "highest_section_exam_passed " << progress.highestSectionExamPassed() << '\n';
    buffer << "unlocked_up_to " << progress.unlockedUpToTopicId() << '\n';
    // Sorted so the file is stable across runs (the set's iteration order
    // isn't), which keeps diffs and manual inspection sane.
    std::vector<int> completedExercises(
        progress.completedCodeExerciseIds().begin(), progress.completedCodeExerciseIds().end());
    std::sort(completedExercises.begin(), completedExercises.end());
    for (const int exerciseId : completedExercises) {
        buffer << "exercise_done " << exerciseId << '\n';
    }
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        buffer << "topic " << topicId << ' ' << statusName(progress.statusOf(topicId)) << '\n';
    }
    return atomicWriteTextFile(filePath, buffer.str());
}

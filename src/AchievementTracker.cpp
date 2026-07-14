#include "AchievementTracker.h"

#include <filesystem>
#include <fstream>
#include <sstream>
#include <system_error>
#include <utility>

namespace {

bool parseAchievementName(const std::string& name, AchievementId& outId) {
    if (name == "FirstStep") {
        outId = AchievementId::FirstStep;
        return true;
    }
    if (name == "FlawlessFive") {
        outId = AchievementId::FlawlessFive;
        return true;
    }
    if (name == "StreakMaster") {
        outId = AchievementId::StreakMaster;
        return true;
    }
    if (name == "CodeWriter") {
        outId = AchievementId::CodeWriter;
        return true;
    }
    if (name == "BugHunter") {
        outId = AchievementId::BugHunter;
        return true;
    }
    if (name == "NeverGiveUp") {
        outId = AchievementId::NeverGiveUp;
        return true;
    }
    if (name == "PerfectExam") {
        outId = AchievementId::PerfectExam;
        return true;
    }
    return false;
}

std::string achievementSerializedName(AchievementId id) {
    switch (id) {
        case AchievementId::FirstStep:
            return "FirstStep";
        case AchievementId::FlawlessFive:
            return "FlawlessFive";
        case AchievementId::StreakMaster:
            return "StreakMaster";
        case AchievementId::CodeWriter:
            return "CodeWriter";
        case AchievementId::BugHunter:
            return "BugHunter";
        case AchievementId::NeverGiveUp:
            return "NeverGiveUp";
        case AchievementId::PerfectExam:
            return "PerfectExam";
    }
    return "";
}

}  // namespace

std::vector<AchievementId> allAchievementIds() {
    return {
        AchievementId::FirstStep,
        AchievementId::FlawlessFive,
        AchievementId::StreakMaster,
        AchievementId::CodeWriter,
        AchievementId::BugHunter,
        AchievementId::NeverGiveUp,
        AchievementId::PerfectExam,
    };
}

std::string achievementDisplayName(AchievementId id) {
    switch (id) {
        case AchievementId::FirstStep:
            return "İlk Adım";
        case AchievementId::FlawlessFive:
            return "Hatasız Beşli";
        case AchievementId::StreakMaster:
            return "Seri Ustası";
        case AchievementId::CodeWriter:
            return "Kod Yazarı";
        case AchievementId::BugHunter:
            return "Hata Avcısı";
        case AchievementId::NeverGiveUp:
            return "Pes Etmeyen";
        case AchievementId::PerfectExam:
            return "Mükemmel Sınav";
    }
    return "";
}

std::string achievementDescription(AchievementId id) {
    switch (id) {
        case AchievementId::FirstStep:
            return "İlk sorunu çözdün.";
        case AchievementId::FlawlessFive:
            return "Art arda 5 doğru cevap verdin.";
        case AchievementId::StreakMaster:
            return "Art arda 10 doğru cevap verdin.";
        case AchievementId::CodeWriter:
            return "10 kod yazma sorusu çözdün.";
        case AchievementId::BugHunter:
            return "25 hatalı kodu düzelttin.";
        case AchievementId::NeverGiveUp:
            return "Daha önce 5 kez yanlış yaptığın bir soruyu doğru çözdün.";
        case AchievementId::PerfectExam:
            return "Bir bölüm sınavından %100 aldın.";
    }
    return "";
}

bool AchievementTracker::unlock(AchievementId id) {
    const auto insertResult = unlockedIds_.insert(static_cast<int>(id));
    return insertResult.second;
}

bool AchievementTracker::isUnlocked(AchievementId id) const {
    return unlockedIds_.find(static_cast<int>(id)) != unlockedIds_.end();
}

std::vector<AchievementId> AchievementTracker::allUnlocked() const {
    std::vector<AchievementId> result;
    result.reserve(unlockedIds_.size());
    for (const int id : unlockedIds_) {
        result.push_back(static_cast<AchievementId>(id));
    }
    return result;
}

bool AchievementTracker::loadFromFile(const std::string& filePath, const std::string& backupPath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        return false;
    }

    std::unordered_set<int> parsedIds;
    bool corrupted = false;

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream lineStream(line);
        std::string recordType;
        lineStream >> recordType;

        if (recordType != "achievement") {
            corrupted = true;
            break;
        }

        std::string nameText;
        lineStream >> nameText;

        AchievementId id = AchievementId::FirstStep;
        if (nameText.empty() || !parseAchievementName(nameText, id)) {
            corrupted = true;
            break;
        }
        parsedIds.insert(static_cast<int>(id));
    }

    if (corrupted) {
        std::error_code errorCode;
        std::filesystem::copy_file(
            filePath, backupPath, std::filesystem::copy_options::overwrite_existing, errorCode);
        unlockedIds_.clear();
        return true;
    }

    unlockedIds_ = std::move(parsedIds);
    return false;
}

void AchievementTracker::saveToFile(const std::string& filePath) const {
    std::ofstream file(filePath, std::ios::trunc);
    if (!file.is_open()) {
        return;
    }
    for (const int id : unlockedIds_) {
        file << "achievement " << achievementSerializedName(static_cast<AchievementId>(id)) << '\n';
    }
}

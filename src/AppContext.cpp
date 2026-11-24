#include "AppContext.h"

#include <filesystem>
#include <string>
#include <system_error>

#include "LevelSystem.h"

void ensureDataDirectoryExists(const ConsoleUI& ui) {
    std::error_code errorCode;
    std::filesystem::create_directories("data", errorCode);
    if (errorCode) {
        // Stale message alert: this used to say saving "isn't active in
        // this version anyway", which stopped being true once persistence
        // landed — it would have reassured the user while their progress
        // silently failed to save.
        ui.printLine(
            "Uyarı: data/ klasörü oluşturulamadı (" + errorCode.message() +
            "). İlerlemen bu oturumda kaydedilemeyecek.");
    }
}

void saveProgress(AppContext& context) {
    if (!context.progressManager.save(
            context.progress, kProgressFilePath,
            static_cast<int>(context.lessons.allLessons().size()))) {
        context.ui.printError("Uyarı: ilerleme dosyası kaydedilemedi.");
    }
}

void awardXpAndCheckLevelUp(AppContext& context, int amount) {
    const LevelInfo levelBefore = levelForXp(context.progress.totalXp());
    context.progress.addXp(amount);
    const LevelInfo levelAfter = levelForXp(context.progress.totalXp());
    if (levelAfter.level > levelBefore.level) {
        context.ui.printLine("");
        context.ui.printHighlight(
            "Tebrikler! Yeni seviyeye ulaştın: " + levelAfter.name + " (Seviye " +
            std::to_string(levelAfter.level) + ")");
        context.ui.printLine("");
    }
}

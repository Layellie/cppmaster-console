#include <filesystem>
#include <fstream>
#include <iostream>

#include "AchievementTracker.h"
#include "MistakeTracker.h"

int main() {
    std::filesystem::create_directories("data");

    AchievementTracker achievements;
    std::cout << "Baslangicta FirstStep kilitli mi: "
              << (!achievements.isUnlocked(AchievementId::FirstStep) ? "EVET (OK)" : "HATA") << '\n';

    const bool firstUnlock = achievements.unlock(AchievementId::FirstStep);
    std::cout << "Ilk kilit acma sonucu: " << (firstUnlock ? "YENI (OK)" : "HATA") << '\n';

    const bool secondUnlock = achievements.unlock(AchievementId::FirstStep);
    std::cout << "Tekrar kilit acma sonucu: " << (!secondUnlock ? "ZATEN ACIK (OK)" : "HATA") << '\n';

    achievements.unlock(AchievementId::StreakMaster);
    std::cout << "Acik basarim sayisi: " << achievements.allUnlocked().size() << " (beklenen: 2)\n";

    const std::string testPath = "data/test_achievements.txt";
    const std::string backupPath = "data/test_achievements_corrupted_backup.txt";
    achievements.saveToFile(testPath);

    AchievementTracker loaded;
    const bool wasCorrupted = loaded.loadFromFile(testPath, backupPath);
    std::cout << "Yuklenen bozuk mu: " << (!wasCorrupted ? "HAYIR (OK)" : "HATA") << '\n';
    std::cout << "Yuklenen FirstStep acik mi: "
              << (loaded.isUnlocked(AchievementId::FirstStep) ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yuklenen StreakMaster acik mi: "
              << (loaded.isUnlocked(AchievementId::StreakMaster) ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yuklenen CodeWriter acik mi (kilitli olmali): "
              << (!loaded.isUnlocked(AchievementId::CodeWriter) ? "HAYIR (OK)" : "HATA") << '\n';

    {
        std::ofstream corruptFile(testPath, std::ios::trunc);
        corruptFile << "achievement BilinmeyenBasarim\n";
    }
    AchievementTracker corruptTracker;
    const bool detectedCorruption = corruptTracker.loadFromFile(testPath, backupPath);
    std::cout << "Bozuk dosya tespit edildi mi: " << (detectedCorruption ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yedek olusturuldu mu: " << (std::filesystem::exists(backupPath) ? "EVET (OK)" : "HATA") << '\n';

    MistakeTracker mistakes;
    std::cout << "Baslangicta soru 1 icin kayit var mi: "
              << (!mistakes.findMistake(1).has_value() ? "HAYIR (OK)" : "HATA") << '\n';
    mistakes.recordWrong(1);
    mistakes.recordWrong(1);
    const auto found = mistakes.findMistake(1);
    std::cout << "Soru 1 kaydi bulundu mu: " << (found.has_value() ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Soru 1 yanlis sayisi: " << (found.has_value() ? found->wrongCount : -1)
              << " (beklenen: 2)\n";

    return 0;
}

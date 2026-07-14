#include <filesystem>
#include <fstream>
#include <iostream>

#include "ProgressManager.h"
#include "UserProgress.h"

int main() {
    std::filesystem::create_directories("data");

    ProgressManager manager;
    const std::string testPath = "data/test_progress.txt";
    const std::string backupPath = "data/test_progress_corrupted_backup.txt";

    UserProgress original(10);
    original.addXp(150);
    original.setStatus(3, TopicStatus::Completed);
    original.setStatus(5, TopicStatus::Learning);
    original.recordAnswer(true);
    original.recordAnswer(false);
    original.recordAnswer(true);

    manager.save(original, testPath, 10);

    const auto loaded = manager.load(testPath, backupPath, 10);
    std::cout << "Yuklenen bozuk mu: " << (loaded.wasCorrupted ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Yuklenen XP: " << loaded.progress.totalXp() << " (beklenen: 150)\n";
    std::cout << "Konu 3 durumu: "
              << (loaded.progress.statusOf(3) == TopicStatus::Completed ? "Completed (OK)" : "HATA") << '\n';
    std::cout << "Konu 5 durumu: "
              << (loaded.progress.statusOf(5) == TopicStatus::Learning ? "Learning (OK)" : "HATA") << '\n';
    std::cout << "Konu 1 durumu (hic dokunulmadi): "
              << (loaded.progress.statusOf(1) == TopicStatus::NotStarted ? "NotStarted (OK)" : "HATA") << '\n';
    std::cout << "Cevaplanan: " << loaded.progress.totalQuestionsAnswered() << " (beklenen: 3)\n";
    std::cout << "Dogru: " << loaded.progress.totalCorrectAnswers() << " (beklenen: 2)\n";

    const auto missing = manager.load("data/does_not_exist.txt", backupPath, 10);
    std::cout << "Eksik dosya bozuk mu: " << (missing.wasCorrupted ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Eksik dosya XP: " << missing.progress.totalXp() << " (beklenen: 0)\n";

    {
        std::ofstream corruptFile(testPath, std::ios::trunc);
        corruptFile << "xp not_a_number\n";
    }
    const auto corrupted = manager.load(testPath, backupPath, 10);
    std::cout << "Bozuk dosya tespit edildi mi: " << (corrupted.wasCorrupted ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Bozuk sonrasi XP (taze): " << corrupted.progress.totalXp() << " (beklenen: 0)\n";
    std::cout << "Yedek dosyasi olusturuldu mu: "
              << (std::filesystem::exists(backupPath) ? "EVET (OK)" : "HATA") << '\n';

    return 0;
}

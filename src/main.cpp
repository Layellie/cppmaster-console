#include <filesystem>
#include <fstream>
#include <iostream>

#include "ProgressManager.h"
#include "UserProgress.h"

int main() {
    std::filesystem::create_directories("data");

    UserProgress progress(10);
    std::cout << "Baslangic streak: " << progress.currentStreak() << " (beklenen: 0)\n";

    progress.recordStreak(true);
    progress.recordStreak(true);
    progress.recordStreak(true);
    std::cout << "3 dogru sonrasi streak: " << progress.currentStreak() << " (beklenen: 3)\n";
    std::cout << "En uzun streak: " << progress.longestStreak() << " (beklenen: 3)\n";

    progress.recordStreak(false);
    std::cout << "Yanlis sonrasi streak: " << progress.currentStreak() << " (beklenen: 0)\n";
    std::cout << "En uzun streak (degismemeli): " << progress.longestStreak() << " (beklenen: 3)\n";

    progress.recordTypedCorrectAnswer(QuestionType::WriteCode);
    progress.recordTypedCorrectAnswer(QuestionType::WriteCode);
    progress.recordTypedCorrectAnswer(QuestionType::FindError);
    progress.recordTypedCorrectAnswer(QuestionType::FixCode);
    progress.recordTypedCorrectAnswer(QuestionType::MultipleChoice);
    std::cout << "WriteCode dogru sayisi: " << progress.writeCodeCorrectCount() << " (beklenen: 2)\n";
    std::cout << "ErrorFix dogru sayisi: " << progress.errorFixCorrectCount() << " (beklenen: 2)\n";

    ProgressManager manager;
    const std::string testPath = "data/test_progress_p5.txt";
    const std::string backupPath = "data/test_progress_p5_corrupted_backup.txt";
    manager.save(progress, testPath, 10);

    const auto loaded = manager.load(testPath, backupPath, 10);
    std::cout << "Yuklenen bozuk mu: " << (loaded.wasCorrupted ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Yuklenen streak: " << loaded.progress.currentStreak() << " (beklenen: 0)\n";
    std::cout << "Yuklenen en uzun streak: " << loaded.progress.longestStreak() << " (beklenen: 3)\n";
    std::cout << "Yuklenen WriteCode dogru: " << loaded.progress.writeCodeCorrectCount() << " (beklenen: 2)\n";
    std::cout << "Yuklenen ErrorFix dogru: " << loaded.progress.errorFixCorrectCount() << " (beklenen: 2)\n";

    {
        std::ofstream oldFormatFile(testPath, std::ios::trunc);
        oldFormatFile << "xp 50\n";
        oldFormatFile << "answered 5\n";
        oldFormatFile << "correct 4\n";
        oldFormatFile << "topic 1 Completed\n";
    }
    const auto oldFormatLoaded = manager.load(testPath, backupPath, 10);
    std::cout << "Eski format bozuk mu: " << (oldFormatLoaded.wasCorrupted ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Eski format XP: " << oldFormatLoaded.progress.totalXp() << " (beklenen: 50)\n";
    std::cout << "Eski format streak (yok, 0 olmali): " << oldFormatLoaded.progress.currentStreak()
              << " (beklenen: 0)\n";

    return 0;
}

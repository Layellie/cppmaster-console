#include <filesystem>
#include <fstream>
#include <iostream>

#include "MistakeTracker.h"
#include "QuestionManager.h"

int main() {
    std::filesystem::create_directories("data");

    QuestionManager questions;
    const auto found = questions.findById(1);
    std::cout << "Soru 1 bulundu mu: " << (found.has_value() ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Soru 1 prompt dolu mu: "
              << (found.has_value() && !found->prompt.empty() ? "EVET (OK)" : "HATA") << '\n';
    const auto missingQuestion = questions.findById(9999);
    std::cout << "Soru 9999 bulundu mu: " << (missingQuestion.has_value() ? "EVET (HATA)" : "HAYIR (OK)") << '\n';

    MistakeTracker tracker;
    std::cout << "Baslangicta soru 1 yanlis mi: " << (!tracker.hasMistake(1) ? "HAYIR (OK)" : "HATA") << '\n';

    tracker.recordWrong(1);
    std::cout << "Bir kez yanlis sonrasi soru 1 yanlis mi: " << (tracker.hasMistake(1) ? "EVET (OK)" : "HATA") << '\n';

    tracker.recordWrong(1);
    tracker.recordWrong(2);

    const auto mistakesBeforeSave = tracker.allMistakesOldestFirst();
    std::cout << "Kayitli yanlis sayisi: " << mistakesBeforeSave.size() << " (beklenen: 2)\n";

    tracker.recordCorrectRetry(1);

    const std::string testPath = "data/test_mistakes.txt";
    const std::string backupPath = "data/test_mistakes_corrupted_backup.txt";
    tracker.saveToFile(testPath);

    MistakeTracker loadedTracker;
    const bool wasCorrupted = loadedTracker.loadFromFile(testPath, backupPath);
    std::cout << "Yuklenen bozuk mu: " << (!wasCorrupted ? "HAYIR (OK)" : "HATA") << '\n';

    const auto loadedMistakes = loadedTracker.allMistakesOldestFirst();
    std::cout << "Yuklenen yanlis sayisi: " << loadedMistakes.size() << " (beklenen: 2)\n";

    bool foundQuestion1 = false;
    for (const auto& record : loadedMistakes) {
        if (record.questionId == 1) {
            foundQuestion1 = true;
            std::cout << "Soru 1 yanlis sayisi: " << record.wrongCount << " (beklenen: 2)\n";
            std::cout << "Soru 1 dogru-tekrar sayisi: " << record.correctAfterWrongCount << " (beklenen: 1)\n";
        }
    }
    std::cout << "Soru 1 yuklenenler icinde bulundu mu: " << (foundQuestion1 ? "EVET (OK)" : "HATA") << '\n';

    {
        std::ofstream corruptFile(testPath, std::ios::trunc);
        corruptFile << "mistake not_a_number\n";
    }
    MistakeTracker corruptTracker;
    const bool detectedCorruption = corruptTracker.loadFromFile(testPath, backupPath);
    std::cout << "Bozuk dosya tespit edildi mi: " << (detectedCorruption ? "EVET (OK)" : "HATA") << '\n';
    std::cout << "Yedek olusturuldu mu: " << (std::filesystem::exists(backupPath) ? "EVET (OK)" : "HATA") << '\n';

    return 0;
}

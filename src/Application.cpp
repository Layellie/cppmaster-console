#include "Application.h"

#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>

#include "LevelSystem.h"

namespace {

constexpr int kMinChoice = 0;
constexpr int kMaxChoice = 10;
constexpr int kMinTopicId = 0;
constexpr int kMaxTopicId = 100;
constexpr double kPassThreshold = 0.7;
constexpr const char* kProgressFilePath = "data/progress.txt";
constexpr const char* kProgressBackupPath = "data/progress_corrupted_backup.txt";
constexpr const char* kMistakesFilePath = "data/mistakes.txt";
constexpr const char* kMistakesBackupPath = "data/mistakes_corrupted_backup.txt";

char statusMarker(TopicStatus status) {
    switch (status) {
        case TopicStatus::NotStarted:
            return ' ';
        case TopicStatus::Learning:
            return '-';
        case TopicStatus::Completed:
            return '+';
        case TopicStatus::Mastered:
            return '*';
    }
    return ' ';
}

char optionLetter(std::size_t index) {
    return static_cast<char>('A' + index);
}

}  // namespace

Application::Application()
    : progress_(static_cast<int>(lessons_.allLessons().size())) {
    ensureDataDirectoryExists();

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    const auto loadResult = progressManager_.load(kProgressFilePath, kProgressBackupPath, topicCount);
    progress_ = loadResult.progress;
    if (loadResult.wasCorrupted) {
        ui_.printLine(
            "Uyarı: ilerleme dosyası bozuktu; yedeklendi (" + std::string(kProgressBackupPath) +
            ") ve ilerlemeniz sıfırlandı.");
    }

    const bool mistakesCorrupted = mistakes_.loadFromFile(kMistakesFilePath, kMistakesBackupPath);
    if (mistakesCorrupted) {
        ui_.printLine(
            "Uyarı: yanlış kayıtları dosyası bozuktu; yedeklendi (" +
            std::string(kMistakesBackupPath) + ") ve sıfırlandı.");
    }
}

void Application::ensureDataDirectoryExists() {
    std::error_code errorCode;
    std::filesystem::create_directories("data", errorCode);
    if (errorCode) {
        ui_.printLine(
            "Uyarı: data/ klasörü oluşturulamadı (" + errorCode.message() +
            "). İlerleme kaydetme özelliği bu sürümde zaten aktif değil.");
    }
}

void Application::run() {
    ui_.printLine("CppMaster Console'a hoş geldin! (Foundation sürümü)");

    while (running_) {
        showMainMenu();
        const int choice = ui_.readMenuChoice(kMinChoice, kMaxChoice);
        handleChoice(choice);
    }
}

void Application::showMainMenu() {
    ui_.printHeader("CPPMASTER CONSOLE");
    ui_.printLine("");
    ui_.printLine("Toplam XP: " + std::to_string(progress_.totalXp()));
    const LevelInfo level = levelForXp(progress_.totalXp());
    ui_.printLine("Seviye: " + level.name + " (Seviye " + std::to_string(level.level) + ")");
    ui_.printLine("");
    ui_.printLine("1. Konuları Öğren");
    ui_.printLine("2. Hızlı Test");
    ui_.printLine("3. Günlük Tekrar");
    ui_.printLine("4. Hatalarımı Çöz");
    ui_.printLine("5. Kod Yazma Alıştırmaları");
    ui_.printLine("6. Seviye Sınavı");
    ui_.printLine("7. İstatistiklerim");
    ui_.printLine("8. Başarımlar");
    ui_.printLine("9. Ayarlar");
    ui_.printLine("10. İlerlemeyi Sıfırla");
    ui_.printLine("0. Çıkış");
    ui_.printLine("");
    ui_.printLine("Seçiminiz:");
}

void Application::handleChoice(int choice) {
    switch (choice) {
        case 1:
            showTopicBrowser();
            break;
        case 2:
            showNotYetAvailable("Hızlı Test");
            break;
        case 3:
            runDailyReview();
            break;
        case 4:
            showMistakeReview();
            break;
        case 5:
            showNotYetAvailable("Kod Yazma Alıştırmaları");
            break;
        case 6:
            showNotYetAvailable("Seviye Sınavı");
            break;
        case 7:
            showStatistics();
            break;
        case 8:
            showNotYetAvailable("Başarımlar");
            break;
        case 9:
            showNotYetAvailable("Ayarlar");
            break;
        case 10:
            resetProgress();
            break;
        case 0:
            ui_.printLine("Görüşürüz!");
            running_ = false;
            break;
        default:
            break;
    }
}

void Application::showTopicBrowser() {
    ui_.printLine("");
    for (int sectionId = 1; sectionId <= lessons_.sectionCount(); ++sectionId) {
        ui_.printLine(
            "Bölüm " + std::to_string(sectionId) + ": " + lessons_.sectionTitle(sectionId));

        for (const Lesson& lesson : lessons_.lessonsInSection(sectionId)) {
            const char marker = statusMarker(progress_.statusOf(lesson.id));
            ui_.printLine(
                "  [" + std::string(1, marker) + "] " + std::to_string(lesson.id) + ". " +
                lesson.title);
        }
        ui_.printLine("");
    }

    ui_.printLine("Görüntülemek istediğiniz konu numarasını girin (0 = ana menüye dön):");
    const int topicChoice = ui_.readMenuChoice(kMinTopicId, kMaxTopicId);
    if (topicChoice == 0) {
        return;
    }
    openTopic(topicChoice);
}

void Application::openTopic(int topicId) {
    const auto lesson = lessons_.findById(topicId);
    if (!lesson.has_value() || lesson->explanation.empty()) {
        ui_.printLine("");
        ui_.printLine("Bu konu için ders içeriği bu sürümde henüz eklenmedi.");
        return;
    }

    showLessonContent(*lesson);
    runTopicQuiz(topicId);
}

void Application::showLessonContent(const Lesson& lesson) {
    ui_.printLine("");
    ui_.printHeader(std::to_string(lesson.id) + ". " + lesson.title);
    ui_.printLine(lesson.explanation);
    ui_.printLine("");
    ui_.printLine("Sözdizimi:");
    ui_.printLine(lesson.syntax);
    ui_.printLine("");
    ui_.printLine("Örnek:");
    ui_.printLine(lesson.exampleCode);
    ui_.printLine("");
    ui_.printLine("Satır satır açıklama:");
    for (const std::string& lineExplanation : lesson.lineExplanations) {
        ui_.printLine("- " + lineExplanation);
    }
    ui_.printLine("");
    ui_.printLine("Yaygın hatalar:");
    for (const std::string& mistake : lesson.commonMistakes) {
        ui_.printLine("- " + mistake);
    }
    ui_.printLine("");
}

void Application::runTopicQuiz(int topicId) {
    const auto quizQuestions = questions_.questionsForTopic(topicId);

    ui_.printLine("Konu testi başlıyor (" + std::to_string(quizQuestions.size()) + " soru).");
    ui_.printLine("");

    int correctCount = 0;
    int sessionXp = 0;

    for (const Question& question : quizQuestions) {
        const AnswerResult result = askOneQuestion(question);
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }
    }

    const auto totalQuestions = static_cast<int>(quizQuestions.size());
    const double successRatio =
        totalQuestions == 0 ? 0.0
                            : static_cast<double>(correctCount) / static_cast<double>(totalQuestions);
    const int successPercent = static_cast<int>(successRatio * 100.0);

    ui_.printLine(
        "Sonuç: " + std::to_string(correctCount) + "/" + std::to_string(totalQuestions) +
        " doğru (%" + std::to_string(successPercent) + "), kazanılan XP: " +
        std::to_string(sessionXp));

    awardXpAndCheckLevelUp(sessionXp);

    if (successRatio >= kPassThreshold) {
        progress_.setStatus(topicId, TopicStatus::Completed);
        ui_.printLine("Bu konu tamamlandı olarak işaretlendi.");
    } else {
        progress_.setStatus(topicId, TopicStatus::Learning);
        ui_.printLine("Bu konuyu öğrenmeye devam ediyorsun; tekrar denemek için tekrar açabilirsin.");
    }
    ui_.printLine("");

    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
}

AnswerResult Application::askOneQuestion(const Question& question) {
    ui_.printLine(question.prompt);

    if (question.type == QuestionType::MultipleChoice) {
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            ui_.printLine(
                std::string(1, optionLetter(index)) + ") " + question.options[index]);
        }
    } else if (question.type == QuestionType::TrueFalse) {
        ui_.printLine("1. Doğru");
        ui_.printLine("2. Yanlış");
    } else if (question.type == QuestionType::OrderCode) {
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            ui_.printLine(
                std::to_string(static_cast<int>(index) + 1) + ". " + question.options[index]);
        }
    }

    std::string rawAnswer;
    if (question.type == QuestionType::WriteCode) {
        ui_.printLine(
            "Kodunuzu birden fazla satır halinde girebilirsiniz. Bitirmek için BITIR yazıp Enter'a basın.");
        rawAnswer = ui_.readMultilineCode();
    } else {
        rawAnswer = ui_.readLine("Cevabınız: ");
    }
    const AnswerResult result = quizEngine_.evaluate(question, rawAnswer);

    if (result.correct) {
        ui_.printLine("Doğru! (+" + std::to_string(result.xpAwarded) + " XP)");
    } else {
        ui_.printLine("");
        ui_.printLine("Yanlış cevap.");
        ui_.printLine("");
        ui_.printLine("Senin cevabın:");
        ui_.printLine(rawAnswer);
        ui_.printLine("");
        ui_.printLine("Doğru cevap:");
        ui_.printLine(result.correctAnswerDisplay);
        ui_.printLine("");
        ui_.printLine("Açıklama:");
        ui_.printLine(question.explanation);
    }
    ui_.printLine("");

    progress_.recordAnswer(result.correct);
    if (result.correct) {
        if (mistakes_.hasMistake(question.id)) {
            mistakes_.recordCorrectRetry(question.id);
        }
    } else {
        mistakes_.recordWrong(question.id);
    }

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    progressManager_.save(progress_, kProgressFilePath, topicCount);
    mistakes_.saveToFile(kMistakesFilePath);

    return result;
}

void Application::awardXpAndCheckLevelUp(int amount) {
    const LevelInfo levelBefore = levelForXp(progress_.totalXp());
    progress_.addXp(amount);
    const LevelInfo levelAfter = levelForXp(progress_.totalXp());
    if (levelAfter.level > levelBefore.level) {
        ui_.printLine("");
        ui_.printLine(
            "Tebrikler! Yeni seviyeye ulaştın: " + levelAfter.name + " (Seviye " +
            std::to_string(levelAfter.level) + ")");
        ui_.printLine("");
    }
}

void Application::resetProgress() {
    ui_.printLine("");
    ui_.printLine("İlerlemenizi sıfırlamak istediğinizden emin misiniz? (evet/hayır):");
    const std::string confirmation = ui_.readLine("Cevabınız: ");
    if (confirmation != "evet") {
        ui_.printLine("İptal edildi.");
        return;
    }

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    progress_ = UserProgress(topicCount);
    mistakes_ = MistakeTracker();

    progressManager_.save(progress_, kProgressFilePath, topicCount);
    mistakes_.saveToFile(kMistakesFilePath);

    ui_.printLine("İlerlemeniz sıfırlandı.");
}

void Application::showMistakeReview() {
    const auto mistakes = mistakes_.allMistakesOldestFirst();
    if (mistakes.empty()) {
        ui_.printLine("");
        ui_.printLine("Henüz kaydedilmiş bir yanlışınız yok!");
        return;
    }

    ui_.printLine("");
    ui_.printLine("Kayıtlı yanlışlarınız (" + std::to_string(mistakes.size()) + " soru):");
    ui_.printLine("");
    runMistakeQuestions(mistakes);
}

void Application::runMistakeQuestions(const std::vector<MistakeRecord>& mistakesToAsk) {
    int correctCount = 0;
    int sessionXp = 0;

    for (const MistakeRecord& mistake : mistakesToAsk) {
        const auto question = questions_.findById(mistake.questionId);
        if (!question.has_value()) {
            continue;
        }
        const AnswerResult result = askOneQuestion(*question);
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }
    }

    awardXpAndCheckLevelUp(sessionXp);
    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));

    ui_.printLine(
        "Tamamlandı: " + std::to_string(correctCount) + "/" + std::to_string(mistakesToAsk.size()) +
        " doğru, kazanılan XP: " + std::to_string(sessionXp));
    ui_.printLine("");
}

void Application::showStatistics() {
    ui_.printLine("");
    ui_.printHeader("İSTATİSTİKLERİM");

    const int topicCount = static_cast<int>(lessons_.allLessons().size());
    int notStarted = 0;
    int learning = 0;
    int completed = 0;
    int mastered = 0;
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        switch (progress_.statusOf(topicId)) {
            case TopicStatus::NotStarted:
                ++notStarted;
                break;
            case TopicStatus::Learning:
                ++learning;
                break;
            case TopicStatus::Completed:
                ++completed;
                break;
            case TopicStatus::Mastered:
                ++mastered;
                break;
        }
    }

    const int totalAnswered = progress_.totalQuestionsAnswered();
    const int totalCorrect = progress_.totalCorrectAnswers();
    const double successRatio =
        totalAnswered == 0 ? 0.0
                           : static_cast<double>(totalCorrect) / static_cast<double>(totalAnswered);

    ui_.printLine("Toplam XP: " + std::to_string(progress_.totalXp()));
    ui_.printLine("Toplam çözülen soru: " + std::to_string(totalAnswered));
    ui_.printLine("Toplam doğru cevap: " + std::to_string(totalCorrect));
    ui_.printLine("Toplam yanlış cevap: " + std::to_string(totalAnswered - totalCorrect));
    ui_.printLine("Genel başarı oranı: %" + std::to_string(static_cast<int>(successRatio * 100.0)));
    ui_.printLine("");
    ui_.printLine("Tamamlanan konu sayısı: " + std::to_string(completed));
    ui_.printLine("Ustalaşılan konu sayısı: " + std::to_string(mastered));
    ui_.printLine("Öğrenilmekte olan konu sayısı: " + std::to_string(learning));
    ui_.printLine("Başlanmamış konu sayısı: " + std::to_string(notStarted));
    ui_.printLine("");
    ui_.printLine("Kayıtlı yanlış sayısı: " + std::to_string(mistakes_.allMistakesOldestFirst().size()));
    ui_.printLine("");
}

void Application::runDailyReview() {
    auto mistakes = mistakes_.allMistakesOldestFirst();
    if (mistakes.empty()) {
        ui_.printLine("");
        ui_.printLine("Henüz tekrar edilecek bir yanlışınız yok! Önce birkaç konu testi çözmelisiniz.");
        return;
    }

    constexpr std::size_t kDailyReviewCap = 20;
    if (mistakes.size() > kDailyReviewCap) {
        mistakes.resize(kDailyReviewCap);
    }

    ui_.printLine("");
    ui_.printLine("Günlük tekrar başlıyor (" + std::to_string(mistakes.size()) + " soru):");
    ui_.printLine("");
    runMistakeQuestions(mistakes);
}

void Application::showNotYetAvailable(const std::string& featureName) {
    ui_.printLine("");
    ui_.printLine(
        "\"" + featureName + "\" bu sürümde henüz eklenmedi. Sonraki aşamada gelecek.");
}

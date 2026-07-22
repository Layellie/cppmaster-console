#include "Application.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <system_error>

#include "AdaptiveDifficulty.h"
#include "ExamContent.h"
#include "LevelSystem.h"
#include "TopicLock.h"

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
constexpr const char* kAchievementsFilePath = "data/achievements.txt";
constexpr const char* kAchievementsBackupPath = "data/achievements_corrupted_backup.txt";
constexpr const char* kGeneratedHistoryFilePath = "data/generated_question_history.txt";
constexpr const char* kGeneratedHistoryBackupPath = "data/generated_question_history_corrupted_backup.txt";
constexpr const char* kGenerationLogFilePath = "data/question_generation.log";
constexpr const char* kSettingsFilePath = "data/settings.txt";
constexpr const char* kSettingsBackupPath = "data/settings_corrupted_backup.txt";
constexpr double kExamPassThreshold = 0.7;
constexpr double kSectionCompletionGateThreshold = 0.7;

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

std::uint64_t createSeed() {
    const auto now = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::random_device randomDevice;
    return static_cast<std::uint64_t>(now) ^ (static_cast<std::uint64_t>(randomDevice()) << 32U) ^
           static_cast<std::uint64_t>(randomDevice());
}

}  // namespace

Application::Application()
    : progress_(static_cast<int>(lessons_.allLessons().size())),
      generationEngine_(kGenerationLogFilePath),
      randomEngine_(createSeed()) {
    ensureDataDirectoryExists();
    isFirstLaunch_ = !std::filesystem::exists(kProgressFilePath);

    generatorRegistry_.registerGenerator(intArithmeticGenerator_);
    generatorRegistry_.registerGenerator(boolOutputGenerator_);
    generatorRegistry_.registerGenerator(arithmeticOperatorGenerator_);
    generatorRegistry_.registerGenerator(modOperatorGenerator_);
    generatorRegistry_.registerGenerator(ifElseGenerator_);
    generatorRegistry_.registerGenerator(forLoopSumGenerator_);
    generatorRegistry_.registerGenerator(whileLoopCountGenerator_);
    generatorRegistry_.registerGenerator(arrayElementGenerator_);
    generatorRegistry_.registerGenerator(vectorPushBackGenerator_);
    generatorRegistry_.registerGenerator(stringConcatGenerator_);
    generatorRegistry_.registerGenerator(functionReturnGenerator_);
    generatorRegistry_.registerGenerator(pointerDereferenceGenerator_);
    generatorRegistry_.registerGenerator(classMemberGenerator_);
    generatorRegistry_.registerGenerator(inheritanceOverrideGenerator_);
    generatorRegistry_.registerGenerator(mapLookupGenerator_);
    generatorRegistry_.registerGenerator(sortWithLambdaGenerator_);
    generatorRegistry_.registerGenerator(tryCatchGenerator_);

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

    const bool achievementsCorrupted =
        achievements_.loadFromFile(kAchievementsFilePath, kAchievementsBackupPath);
    if (achievementsCorrupted) {
        ui_.printLine(
            "Uyarı: başarımlar dosyası bozuktu; yedeklendi (" +
            std::string(kAchievementsBackupPath) + ") ve sıfırlandı.");
    }

    const bool historyCorrupted =
        generationEngine_.loadHistory(kGeneratedHistoryFilePath, kGeneratedHistoryBackupPath);
    if (historyCorrupted) {
        ui_.printLine(
            "Uyarı: üretilen soru geçmişi dosyası bozuktu; yedeklendi (" +
            std::string(kGeneratedHistoryBackupPath) + ") ve sıfırlandı.");
    }

    const auto settingsLoadResult = settingsManager_.load(kSettingsFilePath, kSettingsBackupPath);
    settings_ = settingsLoadResult.settings;
    if (settingsLoadResult.wasCorrupted) {
        ui_.printLine(
            "Uyarı: ayarlar dosyası bozuktu; yedeklendi (" + std::string(kSettingsBackupPath) +
            ") ve varsayılanlara sıfırlandı.");
    }
    ui_.setColorEnabled(settings_.colorEnabled);
    ui_.setAudioAlertEnabled(settings_.audioAlertEnabled);
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

    if (isFirstLaunch_) {
        runFirstLaunchSkillSelection();
    }

    while (running_) {
        showMainMenu();
        const int choice = ui_.readMenuChoice(kMinChoice, kMaxChoice);
        handleChoice(choice);
    }
}

void Application::runFirstLaunchSkillSelection() {
    ui_.printLine("");
    ui_.printHeader("HOŞ GELDİN!");
    ui_.printLine("Başlamadan önce, C++ deneyimini kısaca öğrenelim.");
    ui_.printLine("1. Yeni başlıyorum (hiç programlama bilmiyorum)");
    ui_.printLine("2. Biraz bilgim var (temel kavramlara aşinayım)");
    ui_.printLine("3. Deneyimliyim (başka bir dilde veya C++'ta tecrübem var)");
    ui_.printLine("");
    ui_.printLine("Seçiminiz:");
    const int choice = ui_.readMenuChoice(1, 3);

    int startingXp = 0;
    int unlockedUpToTopicId = 1;
    switch (choice) {
        case 2:
            startingXp = 120;          // Level 3 ("Koşul Çözücü") threshold
            unlockedUpToTopicId = 20;  // Bölüm 1-2 baştan açık
            break;
        case 3:
            startingXp = 350;          // Level 5 ("Dizi Kaşifi") threshold
            unlockedUpToTopicId = 40;  // Bölüm 1-4 baştan açık
            break;
        default:
            break;
    }
    progress_.setUnlockedUpToTopicId(unlockedUpToTopicId);

    if (startingXp > 0) {
        progress_.addXp(startingXp);
        const LevelInfo level = levelForXp(progress_.totalXp());
        ui_.printLine("");
        ui_.printLine(
            "Harika! Başlangıç seviyen: " + level.name + " (Seviye " +
            std::to_string(level.level) + ")");
    }
    ui_.printLine("");
    if (unlockedUpToTopicId > 1) {
        ui_.printLine(
            "Seviyene göre ilk " + std::to_string(unlockedUpToTopicId) +
            " konu baştan açık; sonrasında her konu, bir öncekini tamamladıkça sırayla "
            "açılacak.");
    } else {
        ui_.printLine(
            "Konular sırayla açılacak: bir konuyu tamamladıkça bir sonraki konu açılır.");
    }
    ui_.printLine("");

    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
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
            runQuickTest();
            break;
        case 3:
            runDailyReview();
            break;
        case 4:
            showMistakeReview();
            break;
        case 5:
            runCodeExercises();
            break;
        case 6:
            showExamMenu();
            break;
        case 7:
            showStatistics();
            break;
        case 8:
            showAchievements();
            break;
        case 9:
            showSettingsMenu();
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
    while (true) {
        ui_.printLine("");
        int lastPrintedSection = 0;
        bool reachedLockedTopic = false;
        for (const Lesson& lesson : lessons_.allLessons()) {
            const TopicStatus previousStatus = progress_.statusOf(lesson.id - 1);
            if (!topicIsUnlocked(
                    settings_.topicLockEnabled, lesson.id, progress_.unlockedUpToTopicId(),
                    previousStatus)) {
                reachedLockedTopic = true;
                break;
            }

            if (lesson.sectionId != lastPrintedSection) {
                if (lastPrintedSection != 0) {
                    ui_.printLine("");
                }
                ui_.printLine(
                    "Bölüm " + std::to_string(lesson.sectionId) + ": " +
                    lessons_.sectionTitle(lesson.sectionId));
                lastPrintedSection = lesson.sectionId;
            }

            const char marker = statusMarker(progress_.statusOf(lesson.id));
            ui_.printLine(
                "  [" + std::string(1, marker) + "] " + std::to_string(lesson.id) + ". " +
                lesson.title);
        }
        ui_.printLine("");
        if (reachedLockedTopic) {
            ui_.printLine("(Devamı, önceki konuları tamamladıkça açılacak.)");
            ui_.printLine("");
        }

        ui_.printLine("Görüntülemek istediğiniz konu numarasını girin (0 = ana menüye dön):");
        const int topicChoice = ui_.readMenuChoice(kMinTopicId, kMaxTopicId);
        if (topicChoice == 0) {
            return;
        }
        openTopic(topicChoice);
    }
}

void Application::openTopic(int topicId) {
    const auto lesson = lessons_.findById(topicId);
    if (!lesson.has_value() || lesson->explanation.empty()) {
        ui_.printLine("");
        ui_.printLine("Bu konu için ders içeriği bu sürümde henüz eklenmedi.");
        return;
    }

    const TopicStatus previousStatus = progress_.statusOf(topicId - 1);
    if (!topicIsUnlocked(
            settings_.topicLockEnabled, topicId, progress_.unlockedUpToTopicId(), previousStatus)) {
        ui_.printLine("");
        ui_.printLine(
            "Bu konuya henüz erişemezsin. Önce sıradaki önceki konuları tamamlaman gerekiyor.");
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
    if (settings_.fullExplanationDetail) {
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
}

void Application::runTopicQuiz(int topicId) {
    auto remaining = questions_.questionsForTopic(topicId);
    std::stable_sort(remaining.begin(), remaining.end(), [](const Question& a, const Question& b) {
        return a.difficulty < b.difficulty;
    });
    const auto totalQuestions = static_cast<int>(remaining.size());

    ui_.printLine("Konu testi başlıyor (" + std::to_string(totalQuestions) + " soru).");
    ui_.printLine("");

    const auto lesson = lessons_.findById(topicId);

    int correctCount = 0;
    int sessionXp = 0;
    int correctStreak = 0;
    int wrongStreak = 0;

    while (!remaining.empty()) {
        const std::size_t nextIndex = selectNextQuestionIndex(remaining, correctStreak, wrongStreak);
        const Question question = remaining[nextIndex];

        if (shouldShowExtraHelp(wrongStreak)) {
            if (lesson.has_value() && !lesson->explanation.empty()) {
                ui_.printLine("");
                ui_.printLine("Bu konuyu tekrar hatırlayalım:");
                ui_.printLine(lesson->explanation);
            }
            if (question.type != QuestionType::WriteCode) {
                ui_.printLine(generateHint(question, 1));
            }
            wrongStreak = 0;
        }

        remaining.erase(remaining.begin() + static_cast<std::ptrdiff_t>(nextIndex));

        const AnswerResult result = askOneQuestion(question);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(sessionXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
            ++correctStreak;
            wrongStreak = 0;
        } else {
            ++wrongStreak;
            correctStreak = 0;
        }
    }

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

AnswerResult Application::askOneQuestion(
    const Question& question, bool trackMistakes, bool allowHints) {
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

    int hintLevelUsed = 0;
    std::string rawAnswer;
    bool skipped = false;
    bool exitRequested = false;

    if (question.type == QuestionType::WriteCode) {
        ui_.printLine(
            "Kodunuzu birden fazla satır halinde girebilirsiniz. Bitirmek için BITIR yazıp Enter'a basın.");
        rawAnswer = ui_.readMultilineCode();
    } else {
        while (true) {
            rawAnswer = ui_.readLine("Cevabınız: ");
            if (rawAnswer == "cikis") {
                exitRequested = true;
                break;
            }
            if (rawAnswer == "gec") {
                skipped = true;
                break;
            }
            if (rawAnswer == "ipucu") {
                if (!allowHints) {
                    ui_.printLine("Sınav sırasında ipucu kullanılamaz.");
                    continue;
                }
                if (hintLevelUsed < 3) {
                    ++hintLevelUsed;
                }
                ui_.printLine(generateHint(question, hintLevelUsed));
                continue;
            }
            if (rawAnswer == "konu") {
                if (!allowHints) {
                    ui_.printLine("Sınav sırasında bu komut kullanılamaz.");
                    continue;
                }
                const auto lesson = lessons_.findById(question.topicId);
                if (lesson.has_value() && !lesson->explanation.empty()) {
                    ui_.printLine(lesson->explanation);
                } else {
                    ui_.printLine("Bu konu için ders içeriği bu sürümde henüz eklenmedi.");
                }
                continue;
            }
            if (rawAnswer == "ornek") {
                if (!allowHints) {
                    ui_.printLine("Sınav sırasında bu komut kullanılamaz.");
                    continue;
                }
                const auto lesson = lessons_.findById(question.topicId);
                if (lesson.has_value() && !lesson->exampleCode.empty()) {
                    ui_.printLine(lesson->exampleCode);
                } else {
                    ui_.printLine("Bu konu için örnek bu sürümde henüz eklenmedi.");
                }
                continue;
            }
            break;
        }
    }

    if (exitRequested) {
        return AnswerResult{false, 0, "", true};
    }

    AnswerResult result;
    if (skipped) {
        result = AnswerResult{false, 0, quizEngine_.correctAnswerDisplay(question), false};
    } else {
        result = quizEngine_.evaluate(question, rawAnswer, settings_);
        if (result.correct && hintLevelUsed > 0) {
            const double multiplier = 1.0 - (0.25 * hintLevelUsed);
            result.xpAwarded = static_cast<int>(static_cast<double>(result.xpAwarded) * multiplier);
        }
    }

    if (result.correct) {
        ui_.printSuccess("Doğru! (+" + std::to_string(result.xpAwarded) + " XP)");
    } else {
        ui_.playAlertSound();
        ui_.printLine("");
        ui_.printError("Yanlış cevap.");
        ui_.printLine("");
        ui_.printLine("Senin cevabın:");
        ui_.printLine(skipped ? "(soru geçildi)" : rawAnswer);
        ui_.printLine("");
        ui_.printLine("Doğru cevap:");
        ui_.printLine(result.correctAnswerDisplay);
        ui_.printLine("");
        ui_.printLine("Açıklama:");
        ui_.printLine(question.explanation);
    }
    ui_.printLine("");

    progress_.recordAnswer(result.correct);
    progress_.recordStreak(result.correct);
    if (result.correct) {
        progress_.recordTypedCorrectAnswer(question.type);
        if (trackMistakes && mistakes_.hasMistake(question.id)) {
            mistakes_.recordCorrectRetry(question.id);
        }
    } else if (trackMistakes) {
        mistakes_.recordWrong(question.id);
    }

    checkAchievements(question, result.correct);

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    progressManager_.save(progress_, kProgressFilePath, topicCount);
    if (trackMistakes) {
        mistakes_.saveToFile(kMistakesFilePath);
    }

    return result;
}

void Application::awardXpAndCheckLevelUp(int amount) {
    const LevelInfo levelBefore = levelForXp(progress_.totalXp());
    progress_.addXp(amount);
    const LevelInfo levelAfter = levelForXp(progress_.totalXp());
    if (levelAfter.level > levelBefore.level) {
        ui_.printLine("");
        ui_.printHighlight(
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
    achievements_ = AchievementTracker();

    progressManager_.save(progress_, kProgressFilePath, topicCount);
    mistakes_.saveToFile(kMistakesFilePath);
    achievements_.saveToFile(kAchievementsFilePath);

    ui_.printLine("İlerlemeniz sıfırlandı.");
}

void Application::checkAchievements(const Question& question, bool correct) {
    if (!correct) {
        return;
    }

    std::vector<AchievementId> newlyUnlocked;

    if (progress_.totalCorrectAnswers() == 1) {
        if (achievements_.unlock(AchievementId::FirstStep)) {
            newlyUnlocked.push_back(AchievementId::FirstStep);
        }
    }
    if (progress_.currentStreak() == 5) {
        if (achievements_.unlock(AchievementId::FlawlessFive)) {
            newlyUnlocked.push_back(AchievementId::FlawlessFive);
        }
    }
    if (progress_.currentStreak() == 10) {
        if (achievements_.unlock(AchievementId::StreakMaster)) {
            newlyUnlocked.push_back(AchievementId::StreakMaster);
        }
    }
    if (progress_.writeCodeCorrectCount() >= 10) {
        if (achievements_.unlock(AchievementId::CodeWriter)) {
            newlyUnlocked.push_back(AchievementId::CodeWriter);
        }
    }
    if (progress_.errorFixCorrectCount() >= 25) {
        if (achievements_.unlock(AchievementId::BugHunter)) {
            newlyUnlocked.push_back(AchievementId::BugHunter);
        }
    }

    const auto mistakeRecord = mistakes_.findMistake(question.id);
    if (mistakeRecord.has_value() && mistakeRecord->wrongCount >= 5) {
        if (achievements_.unlock(AchievementId::NeverGiveUp)) {
            newlyUnlocked.push_back(AchievementId::NeverGiveUp);
        }
    }

    if (newlyUnlocked.empty()) {
        return;
    }

    for (const AchievementId id : newlyUnlocked) {
        ui_.printLine("");
        ui_.printHighlight("Yeni başarım kazandın: " + achievementDisplayName(id));
        ui_.printLine(achievementDescription(id));
    }
    ui_.printLine("");
    achievements_.saveToFile(kAchievementsFilePath);
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
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(sessionXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
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

void Application::showAchievements() {
    ui_.printLine("");
    ui_.printHeader("BAŞARIMLAR");
    for (const AchievementId id : allAchievementIds()) {
        const char marker = achievements_.isUnlocked(id) ? '+' : ' ';
        ui_.printLine(
            "[" + std::string(1, marker) + "] " + achievementDisplayName(id) + " - " +
            achievementDescription(id));
    }
    ui_.printLine("");
}

void Application::runDailyReview() {
    auto mistakes = mistakes_.allMistakesOldestFirst();
    if (mistakes.empty()) {
        ui_.printLine("");
        ui_.printLine("Henüz tekrar edilecek bir yanlışınız yok! Önce birkaç konu testi çözmelisiniz.");
        return;
    }

    const auto dailyReviewCap = static_cast<std::size_t>(settings_.dailyReviewQuestionCap);
    if (mistakes.size() > dailyReviewCap) {
        mistakes.resize(dailyReviewCap);
    }

    ui_.printLine("");
    ui_.printLine("Günlük tekrar başlıyor (" + std::to_string(mistakes.size()) + " soru):");
    ui_.printLine("");
    runMistakeQuestions(mistakes);
}

void Application::runQuickTest() {
    ui_.printLine("");
    ui_.printHeader("HIZLI TEST");
    ui_.printLine("Sizin için 5 taze soru üretmeye çalışacağım.");
    ui_.printLine("");

    const int kQuickTestQuestionCount = settings_.quickTestQuestionCount;
    int correctCount = 0;
    int sessionXp = 0;
    int askedCount = 0;

    for (int index = 0; index < kQuickTestQuestionCount; ++index) {
        const auto& allGenerators = generatorRegistry_.allGenerators();
        std::uniform_int_distribution<std::size_t> topicPickDist(0, allGenerators.size() - 1);
        const int pickedTopicId = allGenerators[topicPickDist(randomEngine_)]->topicId();

        std::optional<GeneratedQuestion> generated = generationEngine_.generateUniqueForTopic(
            pickedTopicId, generatorRegistry_, generatorScoring_, generatedQuestionValidator_,
            randomEngine_);

        if (!generated.has_value()) {
            ui_.printLine("Bu oturumda başka taze soru üretemedim; testi burada bitiriyorum.");
            break;
        }

        generated->question.id = nextGeneratedQuestionId_++;
        const AnswerResult result = askOneQuestion(generated->question, /*trackMistakes=*/false);
        if (result.exitRequested) {
            generationEngine_.saveHistory(kGeneratedHistoryFilePath);
            awardXpAndCheckLevelUp(sessionXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
        ++askedCount;
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }

        generationEngine_.saveHistory(kGeneratedHistoryFilePath);
    }

    if (askedCount > 0) {
        const int successPercent = static_cast<int>(
            (static_cast<double>(correctCount) / static_cast<double>(askedCount)) * 100.0);
        ui_.printLine(
            "Hızlı test bitti: " + std::to_string(correctCount) + "/" + std::to_string(askedCount) +
            " doğru (%" + std::to_string(successPercent) +
            "), kazanılan XP: " + std::to_string(sessionXp));
    }
    ui_.printLine("");

    awardXpAndCheckLevelUp(sessionXp);
    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
}

void Application::runSectionExam(int sectionId) {
    int completedCount = 0;
    const auto topicsInSection = lessons_.lessonsInSection(sectionId);
    for (const Lesson& lesson : topicsInSection) {
        const TopicStatus status = progress_.statusOf(lesson.id);
        if (status == TopicStatus::Completed || status == TopicStatus::Mastered) {
            ++completedCount;
        }
    }
    const int topicCount = static_cast<int>(topicsInSection.size());

    const double completionRatio =
        static_cast<double>(completedCount) / static_cast<double>(topicCount);

    if (!sectionExamIsUnlocked(
            settings_.topicLockEnabled, completionRatio, kSectionCompletionGateThreshold)) {
        ui_.printLine("");
        ui_.printLine(
            "Bu bölümün sınavına girebilmek için konuların en az %70'ini tamamlamalısınız.");
        ui_.printLine(
            "Şu an " + std::to_string(completedCount) + "/" + std::to_string(topicCount) +
            " konu tamamlanmış.");
        return;
    }

    const std::vector<int> examQuestionIds = examQuestionIdsForSection(sectionId);
    const int examQuestionCount = static_cast<int>(examQuestionIds.size());

    ui_.printLine("");
    ui_.printHeader("BÖLÜM " + std::to_string(sectionId) + " SINAVI");
    ui_.printLine(
        std::to_string(examQuestionCount) + " soruluk sınav başlıyor. Geçme notu: %70.");
    ui_.printLine("");

    int correctCount = 0;
    int examXp = 0;

    for (const int questionId : examQuestionIds) {
        const auto question = questions_.findById(questionId);
        if (!question.has_value()) {
            continue;
        }
        const AnswerResult result = askOneQuestion(*question, /*trackMistakes=*/true, /*allowHints=*/false);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(examXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
        if (result.correct) {
            ++correctCount;
            examXp += result.xpAwarded;
        }
    }

    const double scoreRatio =
        static_cast<double>(correctCount) / static_cast<double>(examQuestionCount);
    const int scorePercent = static_cast<int>(scoreRatio * 100.0);

    ui_.printLine(
        "Doğru: " + std::to_string(correctCount) + "/" + std::to_string(examQuestionCount));
    ui_.printLine("Başarı: %" + std::to_string(scorePercent));
    ui_.printLine("Kazanılan XP: " + std::to_string(examXp));
    ui_.printLine(
        std::string("Sonuç: ") + (scoreRatio >= kExamPassThreshold ? "GEÇTİN" : "KALDIN"));

    if (scoreRatio >= kExamPassThreshold) {
        progress_.recordSectionExamPassed(sectionId);
    }

    if (correctCount == examQuestionCount) {
        if (achievements_.unlock(AchievementId::PerfectExam)) {
            ui_.printLine("");
            ui_.printHighlight(
                "Yeni başarım kazandın: " + achievementDisplayName(AchievementId::PerfectExam));
            ui_.printLine(achievementDescription(AchievementId::PerfectExam));
            achievements_.saveToFile(kAchievementsFilePath);
        }
    }

    awardXpAndCheckLevelUp(examXp);
    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));

    ui_.printLine("");
}

void Application::runFinalExam() {
    int completedCount = 0;
    const auto allTopics = lessons_.allLessons();
    for (const Lesson& lesson : allTopics) {
        const TopicStatus status = progress_.statusOf(lesson.id);
        if (status == TopicStatus::Completed || status == TopicStatus::Mastered) {
            ++completedCount;
        }
    }
    const int totalTopicCount = static_cast<int>(allTopics.size());

    const double completionRatio =
        static_cast<double>(completedCount) / static_cast<double>(totalTopicCount);

    if (!sectionExamIsUnlocked(
            settings_.topicLockEnabled, completionRatio, kSectionCompletionGateThreshold)) {
        ui_.printLine("");
        ui_.printLine(
            "Genel final sınavına girebilmek için tüm konuların en az %70'ini "
            "tamamlamalısınız.");
        ui_.printLine(
            "Şu an " + std::to_string(completedCount) + "/" + std::to_string(totalTopicCount) +
            " konu tamamlanmış.");
        return;
    }

    const std::vector<int> examQuestionIds = finalExamQuestionIds();
    const int examQuestionCount = static_cast<int>(examQuestionIds.size());

    ui_.printLine("");
    ui_.printHeader("GENEL FİNAL SINAVI");
    ui_.printLine(
        std::to_string(examQuestionCount) + " soruluk sınav başlıyor. Geçme notu: %70.");
    ui_.printLine("");

    int correctCount = 0;
    int examXp = 0;

    for (const int questionId : examQuestionIds) {
        const auto question = questions_.findById(questionId);
        if (!question.has_value()) {
            continue;
        }
        const AnswerResult result = askOneQuestion(*question, /*trackMistakes=*/true, /*allowHints=*/false);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(examXp);
            progressManager_.save(
                progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
            return;
        }
        if (result.correct) {
            ++correctCount;
            examXp += result.xpAwarded;
        }
    }

    const double scoreRatio =
        static_cast<double>(correctCount) / static_cast<double>(examQuestionCount);
    const int scorePercent = static_cast<int>(scoreRatio * 100.0);

    ui_.printLine(
        "Doğru: " + std::to_string(correctCount) + "/" + std::to_string(examQuestionCount));
    ui_.printLine("Başarı: %" + std::to_string(scorePercent));
    ui_.printLine("Kazanılan XP: " + std::to_string(examXp));
    ui_.printLine(
        std::string("Sonuç: ") + (scoreRatio >= kExamPassThreshold ? "GEÇTİN" : "KALDIN"));

    if (correctCount == examQuestionCount) {
        if (achievements_.unlock(AchievementId::PerfectExam)) {
            ui_.printLine("");
            ui_.printHighlight(
                "Yeni başarım kazandın: " + achievementDisplayName(AchievementId::PerfectExam));
            ui_.printLine(achievementDescription(AchievementId::PerfectExam));
            achievements_.saveToFile(kAchievementsFilePath);
        }
    }

    awardXpAndCheckLevelUp(examXp);
    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));

    ui_.printLine("");
}

void Application::showExamMenu() {
    ui_.printLine("");
    ui_.printLine("Hangi sınava girmek istiyorsunuz?");
    for (int sectionId = 1; sectionId <= lessons_.sectionCount(); ++sectionId) {
        ui_.printLine(
            std::to_string(sectionId) + ". Bölüm " + std::to_string(sectionId) + " Sınavı: " +
            lessons_.sectionTitle(sectionId));
    }
    const int finalExamChoice = lessons_.sectionCount() + 1;
    ui_.printLine(std::to_string(finalExamChoice) + ". Genel Final Sınavı");
    ui_.printLine("0. Geri dön");
    const int choice = ui_.readMenuChoice(0, finalExamChoice);
    if (choice == 0) {
        return;
    }
    if (choice == finalExamChoice) {
        runFinalExam();
        return;
    }
    runSectionExam(choice);
}

void Application::runCodeExercises() {
    bool inCodeExercisesMenu = true;
    while (inCodeExercisesMenu) {
        ui_.printLine("");
        ui_.printHeader("KOD YAZMA ALIŞTIRMALARI");
        ui_.printLine("1. Başlangıç");
        ui_.printLine("2. Orta");
        ui_.printLine("3. İleri");
        ui_.printLine("0. Geri dön");
        ui_.printLine("");
        ui_.printLine("Seçiminiz:");

        const int tierChoice = ui_.readMenuChoice(0, 3);
        std::string tier;
        switch (tierChoice) {
            case 1:
                tier = "Başlangıç";
                break;
            case 2:
                tier = "Orta";
                break;
            case 3:
                tier = "İleri";
                break;
            case 0:
                inCodeExercisesMenu = false;
                break;
            default:
                break;
        }
        if (!tier.empty()) {
            runCodeExerciseTier(tier);
        }
    }
}

void Application::runCodeExerciseTier(const std::string& tier) {
    const auto exercises = codeExercises_.exercisesForTier(tier);
    bool inTierMenu = true;
    while (inTierMenu) {
        ui_.printLine("");
        ui_.printHeader(tier + " Alıştırmaları");
        for (const CodeExercise& exercise : exercises) {
            ui_.printLine(std::to_string(exercise.id) + ". " + exercise.title);
        }
        ui_.printLine("0. Geri dön");
        ui_.printLine("");
        ui_.printLine("Alıştırma numarasını girin:");

        const int choice = ui_.readMenuChoice(0, 100);
        if (choice == 0) {
            inTierMenu = false;
            continue;
        }
        const auto exercise = codeExercises_.findById(choice);
        if (!exercise.has_value() || exercise->tier != tier) {
            ui_.printLine("Geçersiz alıştırma numarası.");
            continue;
        }
        runCodeExercise(*exercise);
    }
}

void Application::runCodeExercise(const CodeExercise& exercise) {
    ui_.printLine("");
    ui_.printHeader(std::to_string(exercise.id) + ". " + exercise.title);
    ui_.printLine(exercise.description);
    ui_.printLine("");
    ui_.printLine("Beklenen davranış:");
    ui_.printLine(exercise.expectedBehavior);
    ui_.printLine("");
    ui_.printLine("Örnek giriş: " + exercise.sampleInput);
    ui_.printLine("Örnek çıktı: " + exercise.sampleOutput);
    ui_.printLine("");

    int hintLevelUsed = 0;
    ui_.printLine("Başlamadan önce ipucu görmek ister misiniz? (E/H)");
    while (true) {
        const std::string wantsHint = ui_.readLine("Cevabınız: ");
        if (wantsHint != "E" && wantsHint != "e") {
            break;
        }
        if (hintLevelUsed < static_cast<int>(exercise.hints.size())) {
            ui_.printLine(exercise.hints[static_cast<std::size_t>(hintLevelUsed)]);
            ++hintLevelUsed;
        } else if (!exercise.hints.empty()) {
            ui_.printLine(exercise.hints.back());
        }
        ui_.printLine("Başka bir ipucu görmek ister misiniz? (E/H)");
    }

    ui_.printLine(
        "Kodunuzu birden fazla satır halinde girebilirsiniz. Bitirmek için BITIR yazıp Enter'a basın.");
    const std::string submittedCode = ui_.readMultilineCode();

    const Question question = toWriteCodeQuestion(exercise);
    const AnswerResult result = quizEngine_.evaluate(question, submittedCode, settings_);

    int xpAwarded = result.xpAwarded;
    if (result.correct && hintLevelUsed > 0) {
        const int cappedHintLevel = hintLevelUsed < 3 ? hintLevelUsed : 3;
        const double multiplier = 1.0 - (0.25 * static_cast<double>(cappedHintLevel));
        xpAwarded = static_cast<int>(static_cast<double>(xpAwarded) * multiplier);
    }

    ui_.printLine("");
    if (result.correct) {
        ui_.printSuccess("Doğru! (+" + std::to_string(xpAwarded) + " XP)");
        awardXpAndCheckLevelUp(xpAwarded);
    } else {
        ui_.playAlertSound();
        ui_.printError("Gönderdiğiniz kod beklenen kriterleri karşılamıyor.");
    }

    ui_.printLine("");
    ui_.printLine("Örnek çözüm:");
    ui_.printLine(exercise.sampleSolution);
    ui_.printLine("");
    ui_.printLine("Alternatif çözüm notu:");
    ui_.printLine(exercise.alternativeSolutionNote);
    ui_.printLine("");

    progressManager_.save(
        progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()));
}

void Application::showSettingsMenu() {
    bool inSettingsMenu = true;
    while (inSettingsMenu) {
        ui_.printLine("");
        ui_.printHeader("AYARLAR");
        ui_.printLine(
            "1. Konu kilidini aç/kapat (şu an: " +
            std::string(settings_.topicLockEnabled ? "Açık" : "Kapalı") + ")");
        ui_.printLine(
            "2. Büyük-küçük harf duyarlılığını aç/kapat (şu an: " +
            std::string(settings_.strictCaseSensitivity ? "Açık" : "Kapalı") + ")");
        ui_.printLine(
            "3. Kod cevabı toleransını aç/kapat (şu an: " +
            std::string(settings_.lenientWriteCodeTolerance ? "Esnek" : "Sıkı") + ")");
        ui_.printLine(
            "4. Açıklama detay seviyesini değiştir (şu an: " +
            std::string(settings_.fullExplanationDetail ? "Tam" : "Kısa") + ")");
        ui_.printLine(
            "5. Günlük soru hedefini değiştir (şu an: " +
            std::to_string(settings_.dailyReviewQuestionCap) + ")");
        ui_.printLine("6. İlerlemeyi dışa aktar");
        ui_.printLine("7. İlerlemeyi içe aktar");
        ui_.printLine(
            "8. Renkli çıktıyı aç/kapat (şu an: " +
            std::string(settings_.colorEnabled ? "Açık" : "Kapalı") + ")");
        ui_.printLine(
            "9. Sesli uyarıyı aç/kapat (şu an: " +
            std::string(settings_.audioAlertEnabled ? "Açık" : "Kapalı") + ")");
        ui_.printLine(
            "10. Hızlı Test soru sayısını değiştir (şu an: " +
            std::to_string(settings_.quickTestQuestionCount) + ")");
        ui_.printLine("0. Geri dön");
        ui_.printLine("");
        ui_.printLine("Seçiminiz:");

        const int choice = ui_.readMenuChoice(0, 10);
        switch (choice) {
            case 1:
                settings_.topicLockEnabled = !settings_.topicLockEnabled;
                settingsManager_.save(settings_, kSettingsFilePath);
                break;
            case 2:
                settings_.strictCaseSensitivity = !settings_.strictCaseSensitivity;
                settingsManager_.save(settings_, kSettingsFilePath);
                break;
            case 3:
                settings_.lenientWriteCodeTolerance = !settings_.lenientWriteCodeTolerance;
                settingsManager_.save(settings_, kSettingsFilePath);
                break;
            case 4:
                settings_.fullExplanationDetail = !settings_.fullExplanationDetail;
                settingsManager_.save(settings_, kSettingsFilePath);
                break;
            case 5: {
                ui_.printLine("Yeni günlük soru hedefini girin (1-100):");
                const int newCap = ui_.readMenuChoice(1, 100);
                settings_.dailyReviewQuestionCap = newCap;
                settingsManager_.save(settings_, kSettingsFilePath);
                break;
            }
            case 6:
                exportProgress();
                break;
            case 7:
                importProgress();
                break;
            case 8:
                settings_.colorEnabled = !settings_.colorEnabled;
                ui_.setColorEnabled(settings_.colorEnabled);
                settingsManager_.save(settings_, kSettingsFilePath);
                break;
            case 9:
                settings_.audioAlertEnabled = !settings_.audioAlertEnabled;
                ui_.setAudioAlertEnabled(settings_.audioAlertEnabled);
                settingsManager_.save(settings_, kSettingsFilePath);
                break;
            case 10: {
                ui_.printLine("Yeni Hızlı Test soru sayısını girin (1-20):");
                const int newCount = ui_.readMenuChoice(1, 20);
                settings_.quickTestQuestionCount = newCount;
                settingsManager_.save(settings_, kSettingsFilePath);
                break;
            }
            case 0:
                inSettingsMenu = false;
                break;
            default:
                break;
        }
    }
}

void Application::exportProgress() {
    const std::string targetDirectory = ui_.readLine("Hedef klasör yolunu girin: ");
    std::error_code errorCode;
    std::filesystem::create_directories(targetDirectory, errorCode);
    if (errorCode) {
        ui_.printLine("Hata: hedef klasör oluşturulamadı (" + errorCode.message() + ").");
        return;
    }

    const std::string sourcePaths[] = {
        kProgressFilePath, kMistakesFilePath, kAchievementsFilePath, kGeneratedHistoryFilePath,
        kSettingsFilePath,
    };
    int copiedCount = 0;
    for (const std::string& sourcePath : sourcePaths) {
        if (!std::filesystem::exists(sourcePath)) {
            continue;
        }
        const std::filesystem::path destination =
            std::filesystem::path(targetDirectory) / std::filesystem::path(sourcePath).filename();
        std::filesystem::copy_file(
            sourcePath, destination, std::filesystem::copy_options::overwrite_existing, errorCode);
        if (!errorCode) {
            ++copiedCount;
        }
    }
    ui_.printLine(std::to_string(copiedCount) + " dosya dışa aktarıldı: " + targetDirectory);
}

void Application::importProgress() {
    const std::string sourceDirectory = ui_.readLine("İçe aktarılacak klasör yolunu girin: ");
    const std::string fileNames[] = {
        "progress.txt",
        "mistakes.txt",
        "achievements.txt",
        "generated_question_history.txt",
        "settings.txt",
    };
    int copiedCount = 0;
    std::error_code errorCode;
    for (const std::string& fileName : fileNames) {
        const std::filesystem::path source = std::filesystem::path(sourceDirectory) / fileName;
        if (!std::filesystem::exists(source)) {
            continue;
        }
        const std::filesystem::path destination = std::filesystem::path("data") / fileName;
        std::filesystem::copy_file(
            source, destination, std::filesystem::copy_options::overwrite_existing, errorCode);
        if (!errorCode) {
            ++copiedCount;
        }
    }
    ui_.printLine(
        std::to_string(copiedCount) +
        " dosya içe aktarıldı. Değişikliklerin etkili olması için uygulamayı yeniden başlatın.");
}


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
#include <vector>

#include "CodeExerciseSession.h"
#include "ExamContent.h"
#include "LevelSystem.h"
#include "MenuFormatting.h"
#include "QuizSession.h"
#include "SettingsScreen.h"
#include "TopicLock.h"

namespace {

constexpr int kMinChoice = 0;
constexpr int kMaxChoice = 10;
constexpr int kMinTopicId = 0;
constexpr double kExamPassThreshold = 0.7;
constexpr double kSectionCompletionGateThreshold = 0.7;

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
    std::error_code existsError;
    isFirstLaunch_ = !std::filesystem::exists(kProgressFilePath, existsError);

    generators_ = makeAllGenerators();
    for (const auto& generator : generators_) {
        generatorRegistry_.registerGenerator(*generator);
    }

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    auto loadResult = progressManager_.load(kProgressFilePath, kProgressBackupPath, topicCount);
    progress_ = std::move(loadResult.progress);
    if (loadResult.wasCorrupted) {
        ui_.printLine(
            "Uyarı: ilerleme dosyası bozuktu; yedeklendi (" + std::string(kProgressBackupPath) +
            ") ve ilerlemen sıfırlandı.");
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

AppContext Application::makeContext() noexcept {
    return AppContext{
        .ui = ui_,
        .lessons = lessons_,
        .questions = questions_,
        .quizEngine = quizEngine_,
        .progress = progress_,
        .progressManager = progressManager_,
        .mistakes = mistakes_,
        .achievements = achievements_,
        .codeExercises = codeExercises_,
        .generationEngine = generationEngine_,
        .generatorRegistry = generatorRegistry_,
        .generatorScoring = generatorScoring_,
        .generatedQuestionValidator = generatedQuestionValidator_,
        .settings = settings_,
        .settingsManager = settingsManager_,
        .randomEngine = randomEngine_,
        .nextGeneratedQuestionId = nextGeneratedQuestionId_,
    };
}

void Application::ensureDataDirectoryExists() {
    ::ensureDataDirectoryExists(ui_);
}

void Application::run() {
    // CPPMASTER_VERSION comes from the CMake project() version, so the
    // banner can't drift from the actual build the way the old hardcoded
    // "(Foundation sürümü)" phase label did.
#ifdef CPPMASTER_VERSION
    ui_.printLine("CppMaster Console'a hoş geldin! (sürüm " CPPMASTER_VERSION ")");
#else
    ui_.printLine("CppMaster Console'a hoş geldin!");
#endif

    if (isFirstLaunch_) {
        runFirstLaunchSkillSelection();
    }

    while (running_ && !ui_.isInputClosed()) {
        showMainMenu();
        const int choice = ui_.readMenuChoice(kMinChoice, kMaxChoice);
        if (ui_.isInputClosed()) {
            break;
        }
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
    ui_.printLine("Seçimin:");
    const int choice = ui_.readMenuChoice(1, 3);
    if (ui_.isInputClosed()) {
        return;
    }

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

    saveProgress();
}

void Application::showMainMenu() {
    const std::vector<std::vector<MenuEntry>> columns = {
        {{1, "Konuları Öğren"},
         {2, "Hızlı Test"},
         {3, "Günlük Tekrar"},
         {4, "Hatalarımı Çöz"}},
        {{5, "Kod Yazma Alıştırmaları"},
         {6, "Seviye Sınavı"},
         {7, "İstatistiklerim"},
         {8, "Başarımlar"}},
        {{9, "Ayarlar"}, {10, "İlerlemeyi Sıfırla"}, {0, "Çıkış"}},
    };
    const MenuLayout menu = layOutMenuColumns(ui_, columns);

    // Widen the rules to the menu so the title bar doesn't end mid-way
    // across the options, but never shrink below the width every other
    // screen uses.
    ui_.printHeader("CPPMASTER CONSOLE", std::max<std::size_t>(40, menu.width));
    ui_.printLine("");
    ui_.printLine("Toplam XP: " + ui_.colorize(std::to_string(progress_.totalXp()), TextColor::Yellow));
    const LevelInfo level = levelForXp(progress_.totalXp());
    ui_.printLine(
        "Seviye: " +
        ui_.colorize(level.name + " (Seviye " + std::to_string(level.level) + ")", TextColor::Magenta));
    ui_.printLine("");
    for (const std::string& line : menu.lines) {
        ui_.printLine(line);
    }
    ui_.printLine("");
    ui_.printLine(ui_.colorize("Seçimin:", TextColor::Green));
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
                ui_.printLine(ui_.colorize(
                    "Bölüm " + std::to_string(lesson.sectionId) + ": " +
                        lessons_.sectionTitle(lesson.sectionId),
                    TextColor::Cyan));
                lastPrintedSection = lesson.sectionId;
            }

            const TopicStatus status = progress_.statusOf(lesson.id);
            ui_.printLine(
                "  " + statusBadge(ui_, status) + " " +
                ui_.colorize(std::to_string(lesson.id) + ".", TextColor::Green) + " " +
                lesson.title);
        }
        ui_.printLine("");
        if (reachedLockedTopic) {
            ui_.printLine(ui_.colorize(
                "(Devamı, önceki konuları tamamladıkça açılacak.)", TextColor::Dim));
            ui_.printLine("");
        }
        // The markers were previously unexplained — a user had no way to
        // learn what [-] or [*] meant. Each entry is built from the same
        // badge helper the list above uses, so the colours match by
        // construction rather than by someone remembering to update both.
        ui_.printLine(
            legendEntry(ui_, TopicStatus::NotStarted, "başlanmadı") + "   " +
            legendEntry(ui_, TopicStatus::Learning, "öğreniliyor") + "   " +
            legendEntry(ui_, TopicStatus::Completed, "tamamlandı") + "   " +
            legendEntry(ui_, TopicStatus::Mastered, "ustalaşıldı"));
        ui_.printLine("");

        ui_.printLine(
            "Görüntülemek istediğin konu numarasını gir " +
            ui_.colorize("(0 = ana menüye dön)", TextColor::Dim) + ":");
        const int maxTopicId = static_cast<int>(lessons_.allLessons().size());
        const int topicChoice = ui_.readMenuChoice(kMinTopicId, maxTopicId);
        if (ui_.isInputClosed() || topicChoice == 0) {
            return;
        }
        openTopic(topicChoice);
    }
}

void Application::openTopic(int topicId) {
    const Lesson* const lesson = lessons_.findPtrById(topicId);
    if (lesson == nullptr || lesson->explanation.empty()) {
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
    AppContext context = makeContext();
    runTopicQuizSession(context, topicId);
}

void Application::saveProgress() {
    AppContext context = makeContext();
    ::saveProgress(context);
}

void Application::resetProgress() {
    ui_.printLine("");
    ui_.printLine("İlerlemeni sıfırlamak istediğinden emin misin? (evet/hayır):");
    const std::string confirmation = ui_.readLine("Cevabın: ");
    if (confirmation != "evet") {
        ui_.printLine("İptal edildi.");
        return;
    }

    const auto topicCount = static_cast<int>(lessons_.allLessons().size());
    progress_ = UserProgress(topicCount);
    mistakes_ = MistakeTracker();
    achievements_ = AchievementTracker();

    saveProgress();
    if (!mistakes_.saveToFile(kMistakesFilePath)) {
        ui_.printError("Uyarı: yanlış kayıtları dosyası kaydedilemedi.");
    }
    if (!achievements_.saveToFile(kAchievementsFilePath)) {
        ui_.printError("Uyarı: başarımlar dosyası kaydedilemedi.");
    }

    ui_.printLine("İlerlemen sıfırlandı.");
}

void Application::showMistakeReview() {
    AppContext context = makeContext();
    runMistakeReviewSession(context);
}

void Application::showStatistics() {
    showStatisticsScreen(makeContext());
}

void Application::showAchievements() {
    showAchievementsScreen(makeContext());
}

void Application::runDailyReview() {
    AppContext context = makeContext();
    runDailyReviewSession(context);
}

void Application::runQuickTest() {
    AppContext context = makeContext();
    runQuickTestSession(context);
}

void Application::runExam(const ExamPlan& plan) {
    const int topicCount = static_cast<int>(plan.gatingTopicIds.size());
    if (topicCount == 0 || plan.questionIds.empty()) {
        // Defensive: every caller passes a non-empty plan today, but an
        // empty one would otherwise divide by zero when scoring.
        ui_.printLine("");
        ui_.printLine("Bu sınav şu anda kullanılamıyor.");
        return;
    }

    int completedCount = 0;
    for (const int topicId : plan.gatingTopicIds) {
        const TopicStatus status = progress_.statusOf(topicId);
        if (status == TopicStatus::Completed || status == TopicStatus::Mastered) {
            ++completedCount;
        }
    }

    const double completionRatio =
        static_cast<double>(completedCount) / static_cast<double>(topicCount);

    if (!sectionExamIsUnlocked(
            settings_.topicLockEnabled, completionRatio, kSectionCompletionGateThreshold)) {
        ui_.printLine("");
        ui_.printLine(plan.lockedMessage);
        ui_.printLine(
            "Şu an " + std::to_string(completedCount) + "/" + std::to_string(topicCount) +
            " konu tamamlanmış.");
        return;
    }

    const int examQuestionCount = static_cast<int>(plan.questionIds.size());

    ui_.printLine("");
    ui_.printHeader(plan.heading);
    ui_.printLine(
        std::to_string(examQuestionCount) + " soruluk sınav başlıyor. Geçme notu: %70.");
    ui_.printLine("");

    int correctCount = 0;
    int examXp = 0;

    AppContext context = makeContext();
    for (const int questionId : plan.questionIds) {
        const Question* const question = questions_.findPtrById(questionId);
        if (question == nullptr) {
            continue;
        }
        const AnswerResult result =
            askOneQuestion(context, *question, /*trackMistakes=*/true, /*allowHints=*/false);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(context, examXp);
            saveProgress();
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
    ui_.printLine("Kazanılan XP: " + ui_.colorize(std::to_string(examXp), TextColor::Yellow));
    const bool passed = scoreRatio >= kExamPassThreshold;
    if (passed) {
        ui_.printSuccess("Sonuç: GEÇTİN");
    } else {
        ui_.printError("Sonuç: KALDIN");
    }

    if (passed && plan.sectionIdToRecordOnPass > 0) {
        progress_.recordSectionExamPassed(plan.sectionIdToRecordOnPass);
    }

    if (correctCount == examQuestionCount && achievements_.unlock(AchievementId::PerfectExam)) {
        ui_.printLine("");
        ui_.printHighlight(
            "Yeni başarım kazandın: " + achievementDisplayName(AchievementId::PerfectExam));
        ui_.printLine(achievementDescription(AchievementId::PerfectExam));
        if (!achievements_.saveToFile(kAchievementsFilePath)) {
            ui_.printError("Uyarı: başarımlar dosyası kaydedilemedi.");
        }
    }

    awardXpAndCheckLevelUp(context, examXp);
    saveProgress();

    ui_.printLine("");
}

void Application::runSectionExam(int sectionId) {
    ExamPlan plan;
    plan.heading = "BÖLÜM " + std::to_string(sectionId) + " SINAVI";
    plan.lockedMessage =
        "Bu bölümün sınavına girebilmek için konuların en az %70'ini tamamlamalısın.";
    const auto sectionLessons = lessons_.lessonsViewInSection(sectionId);
    plan.gatingTopicIds.reserve(sectionLessons.size());
    for (const Lesson& lesson : sectionLessons) {
        plan.gatingTopicIds.push_back(lesson.id);
    }
    plan.questionIds = examQuestionIdsForSection(sectionId);
    plan.sectionIdToRecordOnPass = sectionId;
    runExam(plan);
}

void Application::runFinalExam() {
    ExamPlan plan;
    plan.heading = "GENEL FİNAL SINAVI";
    plan.lockedMessage =
        "Genel final sınavına girebilmek için tüm konuların en az %70'ini tamamlamalısın.";
    // allLessons() returns a reference, so this reads ids without copying
    // the lessons themselves.
    plan.gatingTopicIds.reserve(lessons_.allLessons().size());
    for (const Lesson& lesson : lessons_.allLessons()) {
        plan.gatingTopicIds.push_back(lesson.id);
    }
    plan.questionIds = finalExamQuestionIds();
    // Deliberately 0: there is no "section 11" milestone to record for the
    // general final exam.
    plan.sectionIdToRecordOnPass = 0;
    runExam(plan);
}

void Application::showExamMenu() {
    ui_.printLine("");
    ui_.printLine("Hangi sınava girmek istiyorsun?");
    for (int sectionId = 1; sectionId <= lessons_.sectionCount(); ++sectionId) {
        ui_.printMenuItem(
            sectionId, "Bölüm " + std::to_string(sectionId) + " Sınavı: " +
                           ui_.colorize(lessons_.sectionTitle(sectionId), TextColor::Cyan));
    }
    const int finalExamChoice = lessons_.sectionCount() + 1;
    ui_.printMenuItem(finalExamChoice, ui_.colorize("Genel Final Sınavı", TextColor::Yellow));
    ui_.printMenuItem(0, "Geri dön");
    const int choice = ui_.readMenuChoice(0, finalExamChoice);
    if (ui_.isInputClosed() || choice == 0) {
        return;
    }
    if (choice == finalExamChoice) {
        runFinalExam();
        return;
    }
    runSectionExam(choice);
}

void Application::runCodeExercises() {
    AppContext context = makeContext();
    runCodeExercisesSession(context);
}

void Application::showSettingsMenu() {
    AppContext context = makeContext();
    showSettingsScreen(context);
}


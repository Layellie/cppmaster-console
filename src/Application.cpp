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

#include "AdaptiveDifficulty.h"
#include "ExamContent.h"
#include "LevelSystem.h"
#include "TextLayout.h"
#include "TopicLock.h"

namespace {

constexpr int kMinChoice = 0;
constexpr int kMaxChoice = 10;
constexpr int kMinTopicId = 0;
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

TextColor colorForStatus(TopicStatus status) {
    switch (status) {
        case TopicStatus::NotStarted:
            return TextColor::Dim;
        case TopicStatus::Learning:
            return TextColor::Yellow;
        case TopicStatus::Completed:
            return TextColor::Green;
        case TopicStatus::Mastered:
            return TextColor::Magenta;
    }
    return TextColor::Dim;
}

// The "[+]" style badge in front of a topic, coloured by its status.
// The topic list and the legend below it both go through here, so the two
// can never disagree about what a marker looks like or what colour it is.
std::string statusBadge(const ConsoleUI& ui, TopicStatus status) {
    std::string badge = "[";
    badge.push_back(statusMarker(status));
    badge += "]";
    return ui.colorize(badge, colorForStatus(status));
}

std::string legendEntry(const ConsoleUI& ui, TopicStatus status, const std::string& label) {
    return statusBadge(ui, status) + " " + ui.colorize(label, TextColor::Dim);
}

// Traffic-light for the overall success rate: a 40% pass rate should not
// read the same as a 95% one.
TextColor colorForSuccessPercent(int percent) {
    if (percent >= 70) {
        return TextColor::Green;
    }
    if (percent >= 40) {
        return TextColor::Yellow;
    }
    return TextColor::Red;
}

// The "(şu an: X)" suffix in the settings menu. The label recedes and the
// value carries the colour, so the current state of every toggle is
// scannable down the column instead of buried in a sentence.
std::string settingState(const ConsoleUI& ui, const std::string& value, TextColor valueColor) {
    return ui.colorize(" (şu an: ", TextColor::Dim) + ui.colorize(value, valueColor) +
           ui.colorize(")", TextColor::Dim);
}

std::string toggleState(const ConsoleUI& ui, bool on, const char* onText, const char* offText) {
    return settingState(ui, on ? onText : offText, on ? TextColor::Green : TextColor::Dim);
}

struct MenuEntry {
    int number;
    std::string label;
};

struct MenuLayout {
    std::vector<std::string> lines;  // ready to print; may contain escape codes
    std::size_t width = 0;           // widest line, in terminal columns
};

// Lays the main menu out side by side instead of as one 11-item list, so the
// XP line, every option and the prompt stay on screen together.
//
// Widths are measured on the plain text: the escape codes around a number
// cost bytes but occupy no columns, so padding against the coloured string
// would indent every column by the length of an escape sequence.
MenuLayout layOutMenuColumns(
    const ConsoleUI& ui, const std::vector<std::vector<MenuEntry>>& columns) {
    constexpr std::size_t kColumnGap = 3;

    std::vector<std::size_t> numberWidths;
    std::vector<std::size_t> columnWidths;
    numberWidths.reserve(columns.size());
    columnWidths.reserve(columns.size());
    std::size_t rowCount = 0;
    for (const std::vector<MenuEntry>& column : columns) {
        std::size_t numberWidth = 1;
        std::size_t labelWidth = 0;
        for (const MenuEntry& entry : column) {
            numberWidth = std::max(numberWidth, std::to_string(entry.number).size());
            labelWidth = std::max(labelWidth, displayWidth(entry.label));
        }
        numberWidths.push_back(numberWidth);
        // "NN" + ". " + label
        columnWidths.push_back(numberWidth + 2 + labelWidth);
        rowCount = std::max(rowCount, column.size());
    }

    // Where each column starts, so a short column (9/10/0) leaves a clean gap
    // rather than pulling the next one left on its empty rows.
    std::vector<std::size_t> columnStarts;
    columnStarts.reserve(columnWidths.size());
    std::size_t offset = 0;
    for (const std::size_t width : columnWidths) {
        columnStarts.push_back(offset);
        offset += width + kColumnGap;
    }

    MenuLayout layout;
    layout.lines.reserve(rowCount);
    for (std::size_t row = 0; row < rowCount; ++row) {
        std::string line;
        std::size_t cursor = 0;  // columns already consumed by `line`
        for (std::size_t column = 0; column < columns.size(); ++column) {
            if (row >= columns[column].size()) {
                continue;
            }
            const MenuEntry& entry = columns[column][row];

            // Right-aligned so the dots line up when "10." meets "9.".
            std::string number = std::to_string(entry.number);
            if (number.size() < numberWidths[column]) {
                number.insert(0, numberWidths[column] - number.size(), ' ');
            }

            line += std::string(columnStarts[column] - cursor, ' ');
            line += ui.colorize(number + ".", TextColor::Green) + " " + entry.label;
            cursor = columnStarts[column] + numberWidths[column] + 2 + displayWidth(entry.label);
        }
        // No trailing padding: it would only invite the terminal to wrap.
        layout.width = std::max(layout.width, cursor);
        layout.lines.push_back(std::move(line));
    }
    return layout;
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

std::string trimPathInput(const std::string& rawPath) {
    const auto first = rawPath.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = rawPath.find_last_not_of(" \t\r\n");
    std::string trimmed = rawPath.substr(first, last - first + 1);
    if (trimmed.size() >= 2 && trimmed.front() == '"' && trimmed.back() == '"') {
        trimmed = trimmed.substr(1, trimmed.size() - 2);
    }
    return trimmed;
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

void Application::ensureDataDirectoryExists() {
    std::error_code errorCode;
    std::filesystem::create_directories("data", errorCode);
    if (errorCode) {
        // Stale message alert: this used to say saving "isn't active in
        // this version anyway", which stopped being true once persistence
        // landed — it would have reassured the user while their progress
        // silently failed to save.
        ui_.printLine(
            "Uyarı: data/ klasörü oluşturulamadı (" + errorCode.message() +
            "). İlerlemen bu oturumda kaydedilemeyecek.");
    }
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

std::vector<Question> Application::selectQuizQuestions(int topicId) {
    const auto view = questions_.questionViewForTopic(topicId);
    std::vector<std::size_t> shuffledIndices(view.size());
    for (std::size_t i = 0; i < view.size(); ++i) {
        shuffledIndices[i] = i;
    }
    // Shuffled here because Application owns the random engine; the policy
    // for *which* of them to keep lives in selectQuizQuestionsFrom, which is
    // pure and unit-tested.
    std::shuffle(shuffledIndices.begin(), shuffledIndices.end(), randomEngine_);
    std::vector<Question> pool;
    pool.reserve(view.size());
    for (const std::size_t index : shuffledIndices) {
        pool.push_back(view[index]);
    }
    return selectQuizQuestionsFrom(
        pool, static_cast<std::size_t>(settings_.topicQuizQuestionCount),
        [this](const Question& question) { return mistakes_.hasMistake(question.id); });
}

void Application::runTopicQuiz(int topicId) {
    auto remaining = selectQuizQuestions(topicId);
    std::stable_sort(remaining.begin(), remaining.end(), [](const Question& a, const Question& b) {
        return a.difficulty < b.difficulty;
    });
    const auto totalQuestions = static_cast<int>(remaining.size());

    ui_.printLine("Konu testi başlıyor (" + std::to_string(totalQuestions) + " soru).");
    ui_.printLine("");

    const Lesson* const lesson = lessons_.findPtrById(topicId);

    int correctCount = 0;
    int sessionXp = 0;
    int correctStreak = 0;
    int wrongStreak = 0;
    // Fed back into the selector so two questions about the same fact don't
    // land back to back; empty until the first question has been asked.
    std::optional<Question> lastAsked;

    while (!remaining.empty()) {
        const std::size_t nextIndex = selectNextQuestionIndex(
            remaining, correctStreak, wrongStreak, lastAsked ? &*lastAsked : nullptr);
        lastAsked = std::move(remaining[nextIndex]);
        remaining.erase(remaining.begin() + static_cast<std::ptrdiff_t>(nextIndex));
        const Question& question = *lastAsked;

        if (shouldShowExtraHelp(wrongStreak)) {
            if (lesson != nullptr && !lesson->explanation.empty()) {
                ui_.printLine("");
                ui_.printLine("Bu konuyu tekrar hatırlayalım:");
                ui_.printLine(lesson->explanation);
            }
            if (question.type != QuestionType::WriteCode) {
                ui_.printLine(generateHint(question, 1));
            }
            wrongStreak = 0;
        }

        const AnswerResult result = askOneQuestion(question);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(sessionXp);
            saveProgress();
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

    const bool passed = successRatio >= kPassThreshold;
    ui_.printLine(
        "Sonuç: " +
        ui_.colorize(
            std::to_string(correctCount) + "/" + std::to_string(totalQuestions) + " doğru (%" +
                std::to_string(successPercent) + ")",
            passed ? TextColor::Green : TextColor::Yellow) +
        ", kazanılan XP: " + ui_.colorize(std::to_string(sessionXp), TextColor::Yellow));

    awardXpAndCheckLevelUp(sessionXp);

    const TopicStatus updatedStatus =
        nextTopicStatusAfterQuiz(progress_.statusOf(topicId), passed);
    progress_.setStatus(topicId, updatedStatus);
    if (passed) {
        ui_.printSuccess("Bu konu tamamlandı olarak işaretlendi.");
    } else {
        ui_.printHighlight(
            "Bu konuyu öğrenmeye devam ediyorsun; tekrar denemek için tekrar açabilirsin.");
    }
    ui_.printLine("");

    saveProgress();
}

AnswerResult Application::askOneQuestion(
    const Question& question, bool trackMistakes, bool allowHints) {
    ui_.printLine(question.prompt);

    // Whatever the learner is expected to type — a letter or a number — is
    // green, the same signal the menus use.
    if (question.type == QuestionType::MultipleChoice ||
        question.type == QuestionType::Scenario) {
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            std::string marker;
            marker.push_back(optionLetter(index));
            marker += ")";
            ui_.printLine(
                ui_.colorize(marker, TextColor::Green) + " " + question.options[index]);
        }
    } else if (question.type == QuestionType::Matching) {
        // Options hold the numbered left column; the prompt itself lists
        // the lettered right column, so the learner replies with pairs.
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            ui_.printMenuItem(static_cast<int>(index) + 1, question.options[index]);
        }
        ui_.printLine("");
        ui_.printLine(
            ui_.colorize("Eşleştirmeleri \"1-c, 2-a, 3-b\" biçiminde yaz.", TextColor::Dim));
    } else if (question.type == QuestionType::TrueFalse) {
        ui_.printMenuItem(1, "Doğru");
        ui_.printMenuItem(2, "Yanlış");
    } else if (question.type == QuestionType::OrderCode) {
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            ui_.printMenuItem(static_cast<int>(index) + 1, question.options[index]);
        }
    }

    int hintLevelUsed = 0;
    std::string rawAnswer;
    bool skipped = false;
    bool exitRequested = false;

    if (question.type == QuestionType::WriteCode) {
        ui_.printLine(
            "Kodunu birden fazla satır halinde girebilirsin. Bitirmek için BITIR yazıp Enter'a bas.");
        rawAnswer = ui_.readMultilineCode();
        if (ui_.isInputClosed() && rawAnswer.empty()) {
            exitRequested = true;
        }
    } else {
        while (true) {
            rawAnswer = ui_.readLine("Cevabın: ");
            if (ui_.isInputClosed() || rawAnswer == "cikis") {
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
                const Lesson* const lesson = lessons_.findPtrById(question.topicId);
                if (lesson != nullptr && !lesson->explanation.empty()) {
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
                const Lesson* const lesson = lessons_.findPtrById(question.topicId);
                if (lesson != nullptr && !lesson->exampleCode.empty()) {
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

    checkAchievements(question, result.correct, trackMistakes);

    saveProgress();
    if (trackMistakes && !mistakes_.saveToFile(kMistakesFilePath)) {
        ui_.printError("Uyarı: yanlış kayıtları dosyası kaydedilemedi.");
    }

    return result;
}

void Application::saveProgress() {
    if (!progressManager_.save(
            progress_, kProgressFilePath, static_cast<int>(lessons_.allLessons().size()))) {
        ui_.printError("Uyarı: ilerleme dosyası kaydedilemedi.");
    }
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

void Application::checkAchievements(const Question& question, bool correct, bool trackMistakes) {
    if (!correct) {
        return;
    }

    std::vector<AchievementId> newlyUnlocked;

    if (progress_.totalCorrectAnswers() >= 1) {
        if (achievements_.unlock(AchievementId::FirstStep)) {
            newlyUnlocked.push_back(AchievementId::FirstStep);
        }
    }
    if (progress_.currentStreak() >= 5) {
        if (achievements_.unlock(AchievementId::FlawlessFive)) {
            newlyUnlocked.push_back(AchievementId::FlawlessFive);
        }
    }
    if (progress_.currentStreak() >= 10) {
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

    if (trackMistakes) {
        const auto mistakeRecord = mistakes_.findMistake(question.id);
        if (mistakeRecord.has_value() && mistakeRecord->wrongCount >= 5) {
            if (achievements_.unlock(AchievementId::NeverGiveUp)) {
                newlyUnlocked.push_back(AchievementId::NeverGiveUp);
            }
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
    if (!achievements_.saveToFile(kAchievementsFilePath)) {
        ui_.printError("Uyarı: başarımlar dosyası kaydedilemedi.");
    }
}

void Application::showMistakeReview() {
    const auto mistakes = mistakes_.allMistakesOldestFirst();
    if (mistakes.empty()) {
        ui_.printLine("");
        ui_.printLine("Henüz kaydedilmiş bir yanlışın yok!");
        return;
    }

    ui_.printLine("");
    ui_.printLine("Kayıtlı yanlışların (" + std::to_string(mistakes.size()) + " soru):");
    ui_.printLine("");
    runMistakeQuestions(mistakes);
}

void Application::runMistakeQuestions(const std::vector<MistakeRecord>& mistakesToAsk) {
    int correctCount = 0;
    int sessionXp = 0;

    for (const MistakeRecord& mistake : mistakesToAsk) {
        const Question* const question = questions_.findPtrById(mistake.questionId);
        if (question == nullptr) {
            continue;
        }
        const AnswerResult result = askOneQuestion(*question);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(sessionXp);
            saveProgress();
            return;
        }
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }
    }

    awardXpAndCheckLevelUp(sessionXp);
    saveProgress();

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

    ui_.printLine(
        "Toplam XP: " + ui_.colorize(std::to_string(progress_.totalXp()), TextColor::Yellow));
    ui_.printLine("Toplam çözülen soru: " + std::to_string(totalAnswered));
    ui_.printLine(
        "Toplam doğru cevap: " + ui_.colorize(std::to_string(totalCorrect), TextColor::Green));
    ui_.printLine(
        "Toplam yanlış cevap: " +
        ui_.colorize(std::to_string(totalAnswered - totalCorrect), TextColor::Red));
    const int successPercent = static_cast<int>(successRatio * 100.0);
    const TextColor successColor = colorForSuccessPercent(successPercent);
    ui_.printLine(
        "Genel başarı oranı: " + ui_.colorize("%" + std::to_string(successPercent), successColor));
    ui_.printLine("");
    // Same colours as the topic list markers, so a glance at either screen
    // means the same thing.
    ui_.printLine(
        "Tamamlanan konu sayısı: " +
        ui_.colorize(std::to_string(completed), colorForStatus(TopicStatus::Completed)));
    ui_.printLine(
        "Ustalaşılan konu sayısı: " +
        ui_.colorize(std::to_string(mastered), colorForStatus(TopicStatus::Mastered)));
    ui_.printLine(
        "Öğrenilmekte olan konu sayısı: " +
        ui_.colorize(std::to_string(learning), colorForStatus(TopicStatus::Learning)));
    ui_.printLine(
        "Başlanmamış konu sayısı: " +
        ui_.colorize(std::to_string(notStarted), colorForStatus(TopicStatus::NotStarted)));
    ui_.printLine("");
    const std::size_t mistakeCount = mistakes_.count();
    ui_.printLine(
        "Kayıtlı yanlış sayısı: " +
        ui_.colorize(
            std::to_string(mistakeCount),
            mistakeCount == 0 ? TextColor::Green : TextColor::Red));
    ui_.printLine("");
}

void Application::showAchievements() {
    ui_.printLine("");
    ui_.printHeader("BAŞARIMLAR");
    for (const AchievementId id : allAchievementIds()) {
        const bool unlocked = achievements_.isUnlocked(id);
        // Unlocked ones are the reward, so they get the colour and the
        // locked ones recede instead of competing for attention.
        const std::string badge =
            ui_.colorize(unlocked ? "[+]" : "[ ]", unlocked ? TextColor::Yellow : TextColor::Dim);
        const std::string name = unlocked
                                     ? achievementDisplayName(id)
                                     : ui_.colorize(achievementDisplayName(id), TextColor::Dim);
        std::string line = badge;
        line += " ";
        line += name;
        line += " ";
        line += ui_.colorize("- " + achievementDescription(id), TextColor::Dim);
        ui_.printLine(line);
    }
    ui_.printLine("");
}

void Application::runDailyReview() {
    auto mistakes = mistakes_.allMistakesOldestFirst();
    if (mistakes.empty()) {
        ui_.printLine("");
        ui_.printLine("Henüz tekrar edilecek bir yanlışın yok! Önce birkaç konu testi çözmelisin.");
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

    const int kQuickTestQuestionCount = settings_.quickTestQuestionCount;
    // Read from settings, not hardcoded: the count became configurable
    // (1-20) but this line still promised "5" regardless.
    ui_.printLine(
        "Senin için " + std::to_string(kQuickTestQuestionCount) +
        " taze soru üretmeye çalışacağım.");
    ui_.printLine("");

    int correctCount = 0;
    int sessionXp = 0;
    int askedCount = 0;

    const auto& allGenerators = generatorRegistry_.allGenerators();
    if (allGenerators.empty()) {
        ui_.printLine("Bu oturumda soru üretici bulunamadı.");
        ui_.printLine("");
        return;
    }

    for (int index = 0; index < kQuickTestQuestionCount; ++index) {
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
            if (!generationEngine_.saveHistory(kGeneratedHistoryFilePath)) {
                ui_.printError("Uyarı: üretilen soru geçmişi kaydedilemedi.");
            }
            awardXpAndCheckLevelUp(sessionXp);
            saveProgress();
            return;
        }
        ++askedCount;
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }

        if (!generationEngine_.saveHistory(kGeneratedHistoryFilePath)) {
            ui_.printError("Uyarı: üretilen soru geçmişi kaydedilemedi.");
        }
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
    saveProgress();
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

    for (const int questionId : plan.questionIds) {
        const Question* const question = questions_.findPtrById(questionId);
        if (question == nullptr) {
            continue;
        }
        const AnswerResult result =
            askOneQuestion(*question, /*trackMistakes=*/true, /*allowHints=*/false);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(examXp);
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

    awardXpAndCheckLevelUp(examXp);
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
    bool inCodeExercisesMenu = true;
    while (inCodeExercisesMenu) {
        ui_.printLine("");
        ui_.printHeader("KOD YAZMA ALIŞTIRMALARI");
        ui_.printLine("1. Başlangıç");
        ui_.printLine("2. Orta");
        ui_.printLine("3. İleri");
        ui_.printLine("0. Geri dön");
        ui_.printLine("");
        ui_.printLine("Seçimin:");

        const int tierChoice = ui_.readMenuChoice(0, 3);
        if (ui_.isInputClosed()) {
            break;
        }
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
        int completedInTier = 0;
        for (const CodeExercise& exercise : exercises) {
            const bool done = progress_.isCodeExerciseCompleted(exercise.id);
            if (done) {
                ++completedInTier;
            }
            ui_.printLine(
                std::string("  [") + (done ? '+' : ' ') + "] " + std::to_string(exercise.id) +
                ". " + exercise.title);
        }
        ui_.printLine("");
        ui_.printLine(
            "Tamamlanan: " + std::to_string(completedInTier) + "/" +
            std::to_string(exercises.size()));
        ui_.printLine("");
        ui_.printLine("0. Geri dön");
        ui_.printLine("");
        ui_.printLine("Alıştırma numarasını gir:");

        int maxExerciseId = 0;
        for (const CodeExercise& allExercise : codeExercises_.allExercises()) {
            maxExerciseId = std::max(maxExerciseId, allExercise.id);
        }
        const int choice = ui_.readMenuChoice(0, maxExerciseId);
        if (ui_.isInputClosed() || choice == 0) {
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
    ui_.printLine("Başlamadan önce ipucu görmek ister misin? (E/H)");
    while (true) {
        const std::string wantsHint = ui_.readLine("Cevabın: ");
        if (ui_.isInputClosed()) {
            return;
        }
        if (wantsHint != "E" && wantsHint != "e") {
            break;
        }
        if (hintLevelUsed < static_cast<int>(exercise.hints.size())) {
            ui_.printLine(exercise.hints[static_cast<std::size_t>(hintLevelUsed)]);
            ++hintLevelUsed;
        } else if (!exercise.hints.empty()) {
            ui_.printLine(exercise.hints.back());
        }
        ui_.printLine("Başka bir ipucu görmek ister misin? (E/H)");
    }

    ui_.printLine(
        "Kodunu birden fazla satır halinde girebilirsin. Bitirmek için BITIR yazıp Enter'a bas.");
    const std::string submittedCode = ui_.readMultilineCode();
    if (ui_.isInputClosed() && submittedCode.empty()) {
        return;
    }

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
        progress_.markCodeExerciseCompleted(exercise.id);
        awardXpAndCheckLevelUp(xpAwarded);
    } else {
        ui_.playAlertSound();
        ui_.printError("Gönderdiğin kod beklenen kriterleri karşılamıyor.");
    }

    ui_.printLine("");
    ui_.printLine("Örnek çözüm:");
    ui_.printLine(exercise.sampleSolution);
    ui_.printLine("");
    ui_.printLine("Alternatif çözüm notu:");
    ui_.printLine(exercise.alternativeSolutionNote);
    ui_.printLine("");

    saveProgress();
}

void Application::showSettingsMenu() {
    bool inSettingsMenu = true;
    while (inSettingsMenu) {
        ui_.printLine("");
        ui_.printHeader("AYARLAR");
        ui_.printMenuItem(
            1, "Konu kilidini aç/kapat" +
                   toggleState(ui_, settings_.topicLockEnabled, "Açık", "Kapalı"));
        ui_.printMenuItem(
            2, "Büyük-küçük harf duyarlılığını aç/kapat" +
                   toggleState(ui_, settings_.strictCaseSensitivity, "Açık", "Kapalı"));
        ui_.printMenuItem(
            3, "Kod cevabı toleransını aç/kapat" +
                   toggleState(ui_, settings_.lenientWriteCodeTolerance, "Esnek", "Sıkı"));
        ui_.printMenuItem(
            4, "Açıklama detay seviyesini değiştir" +
                   toggleState(ui_, settings_.fullExplanationDetail, "Tam", "Kısa"));
        ui_.printMenuItem(
            5, "Günlük soru hedefini değiştir" +
                   settingState(
                       ui_, std::to_string(settings_.dailyReviewQuestionCap), TextColor::Yellow));
        ui_.printMenuItem(6, "İlerlemeyi dışa aktar");
        ui_.printMenuItem(7, "İlerlemeyi içe aktar");
        ui_.printMenuItem(
            8, "Renkli çıktıyı aç/kapat" +
                   toggleState(ui_, settings_.colorEnabled, "Açık", "Kapalı"));
        ui_.printMenuItem(
            9, "Sesli uyarıyı aç/kapat" +
                   toggleState(ui_, settings_.audioAlertEnabled, "Açık", "Kapalı"));
        ui_.printMenuItem(
            10, "Hızlı Test soru sayısını değiştir" +
                    settingState(
                        ui_, std::to_string(settings_.quickTestQuestionCount), TextColor::Yellow));
        ui_.printMenuItem(
            11, "Konu testi soru sayısını değiştir" +
                    settingState(
                        ui_, std::to_string(settings_.topicQuizQuestionCount), TextColor::Yellow));
        ui_.printMenuItem(0, "Geri dön");
        ui_.printLine("");
        ui_.printLine(ui_.colorize("Seçimin:", TextColor::Green));

        auto saveSettings = [&]() {
            if (!settingsManager_.save(settings_, kSettingsFilePath)) {
                ui_.printError("Uyarı: ayarlar dosyası kaydedilemedi.");
            }
        };

        const int choice = ui_.readMenuChoice(0, 11);
        if (ui_.isInputClosed()) {
            break;
        }
        switch (choice) {
            case 1:
                settings_.topicLockEnabled = !settings_.topicLockEnabled;
                saveSettings();
                break;
            case 2:
                settings_.strictCaseSensitivity = !settings_.strictCaseSensitivity;
                saveSettings();
                break;
            case 3:
                settings_.lenientWriteCodeTolerance = !settings_.lenientWriteCodeTolerance;
                saveSettings();
                break;
            case 4:
                settings_.fullExplanationDetail = !settings_.fullExplanationDetail;
                saveSettings();
                break;
            case 5: {
                ui_.printLine("Yeni günlük soru hedefini gir (1-100):");
                const int newCap = ui_.readMenuChoice(1, 100);
                if (ui_.isInputClosed()) {
                    inSettingsMenu = false;
                    break;
                }
                settings_.dailyReviewQuestionCap = newCap;
                saveSettings();
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
                saveSettings();
                break;
            case 9:
                settings_.audioAlertEnabled = !settings_.audioAlertEnabled;
                ui_.setAudioAlertEnabled(settings_.audioAlertEnabled);
                saveSettings();
                break;
            case 10: {
                ui_.printLine("Yeni Hızlı Test soru sayısını gir (1-20):");
                const int newCount = ui_.readMenuChoice(1, 20);
                if (ui_.isInputClosed()) {
                    inSettingsMenu = false;
                    break;
                }
                settings_.quickTestQuestionCount = newCount;
                saveSettings();
                break;
            }
            case 11: {
                // Capped at 30 because a topic holds at most 31 questions;
                // asking nearly all of them is what made retakes repetitive
                // in the first place, so the ceiling stays just below.
                ui_.printLine("Yeni konu testi soru sayısını gir (5-30):");
                const int newCount = ui_.readMenuChoice(5, 30);
                if (ui_.isInputClosed()) {
                    inSettingsMenu = false;
                    break;
                }
                settings_.topicQuizQuestionCount = newCount;
                saveSettings();
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
    const std::string targetDirectory = trimPathInput(ui_.readLine("Hedef klasör yolunu gir: "));
    if (ui_.isInputClosed() || targetDirectory.empty()) {
        ui_.printLine("İptal edildi.");
        return;
    }
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
        std::error_code existsError;
        if (!std::filesystem::exists(sourcePath, existsError) || existsError) {
            continue;
        }
        const std::filesystem::path destination =
            std::filesystem::path(targetDirectory) / std::filesystem::path(sourcePath).filename();
        std::error_code equivalentError;
        if (std::filesystem::equivalent(sourcePath, destination, equivalentError) &&
            !equivalentError) {
            continue;
        }
        std::filesystem::copy_file(
            sourcePath, destination, std::filesystem::copy_options::overwrite_existing, errorCode);
        if (!errorCode) {
            ++copiedCount;
        }
    }
    ui_.printLine(std::to_string(copiedCount) + " dosya dışa aktarıldı: " + targetDirectory);
}

void Application::importProgress() {
    const std::string sourceDirectory =
        trimPathInput(ui_.readLine("İçe aktarılacak klasör yolunu gir: "));
    if (ui_.isInputClosed() || sourceDirectory.empty()) {
        ui_.printLine("İptal edildi.");
        return;
    }
    ensureDataDirectoryExists();
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
        std::error_code existsError;
        if (!std::filesystem::exists(source, existsError) || existsError) {
            continue;
        }
        const std::filesystem::path destination = std::filesystem::path("data") / fileName;
        std::error_code equivalentError;
        if (std::filesystem::equivalent(source, destination, equivalentError) && !equivalentError) {
            continue;
        }
        std::filesystem::copy_file(
            source, destination, std::filesystem::copy_options::overwrite_existing, errorCode);
        if (!errorCode) {
            ++copiedCount;
        }
    }
    ui_.printLine(
        std::to_string(copiedCount) +
        " dosya içe aktarıldı. Değişikliklerin etkili olması için uygulamayı yeniden başlat.");
}


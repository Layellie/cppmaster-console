#include "SettingsScreen.h"

#include <filesystem>
#include <string>
#include <system_error>

#include "MenuFormatting.h"

namespace {

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

void exportProgress(AppContext& context) {
    const std::string targetDirectory =
        trimPathInput(context.ui.readLine("Hedef klasör yolunu gir: "));
    if (context.ui.isInputClosed() || targetDirectory.empty()) {
        context.ui.printLine("İptal edildi.");
        return;
    }
    std::error_code errorCode;
    std::filesystem::create_directories(targetDirectory, errorCode);
    if (errorCode) {
        context.ui.printLine("Hata: hedef klasör oluşturulamadı (" + errorCode.message() + ").");
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
    context.ui.printLine(std::to_string(copiedCount) + " dosya dışa aktarıldı: " + targetDirectory);
}

void importProgress(AppContext& context) {
    const std::string sourceDirectory =
        trimPathInput(context.ui.readLine("İçe aktarılacak klasör yolunu gir: "));
    if (context.ui.isInputClosed() || sourceDirectory.empty()) {
        context.ui.printLine("İptal edildi.");
        return;
    }
    ensureDataDirectoryExists(context.ui);
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
    context.ui.printLine(
        std::to_string(copiedCount) +
        " dosya içe aktarıldı. Değişikliklerin etkili olması için uygulamayı yeniden başlat.");
}

}  // namespace

void showSettingsScreen(AppContext& context) {
    bool inSettingsMenu = true;
    while (inSettingsMenu) {
        context.ui.printLine("");
        context.ui.printHeader("AYARLAR");
        context.ui.printMenuItem(
            1, "Konu kilidini aç/kapat" +
                   toggleState(context.ui, context.settings.topicLockEnabled, "Açık", "Kapalı"));
        context.ui.printMenuItem(
            2,
            "Büyük-küçük harf duyarlılığını aç/kapat" +
                toggleState(context.ui, context.settings.strictCaseSensitivity, "Açık", "Kapalı"));
        context.ui.printMenuItem(
            3, "Kod cevabı toleransını aç/kapat" +
                   toggleState(
                       context.ui, context.settings.lenientWriteCodeTolerance, "Esnek", "Sıkı"));
        context.ui.printMenuItem(
            4, "Açıklama detay seviyesini değiştir" +
                   toggleState(context.ui, context.settings.fullExplanationDetail, "Tam", "Kısa"));
        context.ui.printMenuItem(
            5, "Günlük soru hedefini değiştir" +
                   settingState(
                       context.ui, std::to_string(context.settings.dailyReviewQuestionCap),
                       TextColor::Yellow));
        context.ui.printMenuItem(6, "İlerlemeyi dışa aktar");
        context.ui.printMenuItem(7, "İlerlemeyi içe aktar");
        context.ui.printMenuItem(
            8, "Renkli çıktıyı aç/kapat" +
                   toggleState(context.ui, context.settings.colorEnabled, "Açık", "Kapalı"));
        context.ui.printMenuItem(
            9, "Sesli uyarıyı aç/kapat" +
                   toggleState(context.ui, context.settings.audioAlertEnabled, "Açık", "Kapalı"));
        context.ui.printMenuItem(
            10, "Hızlı Test soru sayısını değiştir" +
                    settingState(
                        context.ui, std::to_string(context.settings.quickTestQuestionCount),
                        TextColor::Yellow));
        context.ui.printMenuItem(
            11, "Konu testi soru sayısını değiştir" +
                    settingState(
                        context.ui, std::to_string(context.settings.topicQuizQuestionCount),
                        TextColor::Yellow));
        context.ui.printMenuItem(0, "Geri dön");
        context.ui.printLine("");
        context.ui.printLine(context.ui.colorize("Seçimin:", TextColor::Green));

        auto saveSettings = [&]() {
            if (!context.settingsManager.save(context.settings, kSettingsFilePath)) {
                context.ui.printError("Uyarı: ayarlar dosyası kaydedilemedi.");
            }
        };

        const int choice = context.ui.readMenuChoice(0, 11);
        if (context.ui.isInputClosed()) {
            break;
        }
        switch (choice) {
            case 1:
                context.settings.topicLockEnabled = !context.settings.topicLockEnabled;
                saveSettings();
                break;
            case 2:
                context.settings.strictCaseSensitivity = !context.settings.strictCaseSensitivity;
                saveSettings();
                break;
            case 3:
                context.settings.lenientWriteCodeTolerance =
                    !context.settings.lenientWriteCodeTolerance;
                saveSettings();
                break;
            case 4:
                context.settings.fullExplanationDetail = !context.settings.fullExplanationDetail;
                saveSettings();
                break;
            case 5: {
                context.ui.printLine("Yeni günlük soru hedefini gir (1-100):");
                const int newCap = context.ui.readMenuChoice(1, 100);
                if (context.ui.isInputClosed()) {
                    inSettingsMenu = false;
                    break;
                }
                context.settings.dailyReviewQuestionCap = newCap;
                saveSettings();
                break;
            }
            case 6:
                exportProgress(context);
                break;
            case 7:
                importProgress(context);
                break;
            case 8:
                context.settings.colorEnabled = !context.settings.colorEnabled;
                context.ui.setColorEnabled(context.settings.colorEnabled);
                saveSettings();
                break;
            case 9:
                context.settings.audioAlertEnabled = !context.settings.audioAlertEnabled;
                context.ui.setAudioAlertEnabled(context.settings.audioAlertEnabled);
                saveSettings();
                break;
            case 10: {
                context.ui.printLine("Yeni Hızlı Test soru sayısını gir (1-20):");
                const int newCount = context.ui.readMenuChoice(1, 20);
                if (context.ui.isInputClosed()) {
                    inSettingsMenu = false;
                    break;
                }
                context.settings.quickTestQuestionCount = newCount;
                saveSettings();
                break;
            }
            case 11: {
                // Capped at 30 because a topic holds at most 31 questions;
                // asking nearly all of them is what made retakes repetitive
                // in the first place, so the ceiling stays just below.
                context.ui.printLine("Yeni konu testi soru sayısını gir (5-30):");
                const int newCount = context.ui.readMenuChoice(5, 30);
                if (context.ui.isInputClosed()) {
                    inSettingsMenu = false;
                    break;
                }
                context.settings.topicQuizQuestionCount = newCount;
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

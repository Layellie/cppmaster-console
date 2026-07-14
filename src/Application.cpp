#include "Application.h"

#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>

namespace {

constexpr int kMinChoice = 0;
constexpr int kMaxChoice = 10;

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

}  // namespace

Application::Application()
    : progress_(static_cast<int>(lessons_.allLessons().size())) {
    ensureDataDirectoryExists();
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
            showNotYetAvailable("Günlük Tekrar");
            break;
        case 4:
            showNotYetAvailable("Hatalarımı Çöz");
            break;
        case 5:
            showNotYetAvailable("Kod Yazma Alıştırmaları");
            break;
        case 6:
            showNotYetAvailable("Seviye Sınavı");
            break;
        case 7:
            showNotYetAvailable("İstatistiklerim");
            break;
        case 8:
            showNotYetAvailable("Başarımlar");
            break;
        case 9:
            showNotYetAvailable("Ayarlar");
            break;
        case 10:
            showNotYetAvailable("İlerlemeyi Sıfırla");
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
}

void Application::showNotYetAvailable(const std::string& featureName) {
    ui_.printLine("");
    ui_.printLine(
        "\"" + featureName + "\" bu sürümde henüz eklenmedi. Sonraki aşamada gelecek.");
}

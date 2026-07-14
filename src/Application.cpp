#include "Application.h"

#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
#include <system_error>

namespace {

constexpr int kMinChoice = 0;
constexpr int kMaxChoice = 10;
constexpr int kMinTopicId = 0;
constexpr int kMaxTopicId = 100;
constexpr double kPassThreshold = 0.7;

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
            ++correctCount;
            sessionXp += result.xpAwarded;
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

    progress_.addXp(sessionXp);

    if (successRatio >= kPassThreshold) {
        progress_.setStatus(topicId, TopicStatus::Completed);
        ui_.printLine("Bu konu tamamlandı olarak işaretlendi.");
    } else {
        progress_.setStatus(topicId, TopicStatus::Learning);
        ui_.printLine("Bu konuyu öğrenmeye devam ediyorsun; tekrar denemek için tekrar açabilirsin.");
    }
    ui_.printLine("");
}

void Application::showNotYetAvailable(const std::string& featureName) {
    ui_.printLine("");
    ui_.printLine(
        "\"" + featureName + "\" bu sürümde henüz eklenmedi. Sonraki aşamada gelecek.");
}

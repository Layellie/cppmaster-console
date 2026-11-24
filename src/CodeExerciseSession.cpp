#include "CodeExerciseSession.h"

#include <algorithm>
#include <cstddef>
#include <string>
#include <utility>

#include "CodeExercise.h"

namespace {

void runCodeExercise(AppContext& context, const CodeExercise& exercise) {
    context.ui.printLine("");
    context.ui.printHeader(std::to_string(exercise.id) + ". " + exercise.title);
    context.ui.printLine(exercise.description);
    context.ui.printLine("");
    context.ui.printLine("Beklenen davranış:");
    context.ui.printLine(exercise.expectedBehavior);
    context.ui.printLine("");
    context.ui.printLine("Örnek giriş: " + exercise.sampleInput);
    context.ui.printLine("Örnek çıktı: " + exercise.sampleOutput);
    context.ui.printLine("");

    int hintLevelUsed = 0;
    context.ui.printLine("Başlamadan önce ipucu görmek ister misin? (E/H)");
    while (true) {
        const std::string wantsHint = context.ui.readLine("Cevabın: ");
        if (context.ui.isInputClosed()) {
            return;
        }
        if (wantsHint != "E" && wantsHint != "e") {
            break;
        }
        if (std::cmp_less(hintLevelUsed, exercise.hints.size())) {
            context.ui.printLine(exercise.hints[static_cast<std::size_t>(hintLevelUsed)]);
            ++hintLevelUsed;
        } else if (!exercise.hints.empty()) {
            context.ui.printLine(exercise.hints.back());
        }
        context.ui.printLine("Başka bir ipucu görmek ister misin? (E/H)");
    }

    context.ui.printLine(
        "Kodunu birden fazla satır halinde girebilirsin. Bitirmek için BITIR yazıp Enter'a bas.");
    const std::string submittedCode = context.ui.readMultilineCode();
    if (context.ui.isInputClosed() && submittedCode.empty()) {
        return;
    }

    const Question question = toWriteCodeQuestion(exercise);
    const AnswerResult result =
        context.quizEngine.evaluate(question, submittedCode, context.settings);

    int xpAwarded = result.xpAwarded;
    if (result.correct && hintLevelUsed > 0) {
        const int cappedHintLevel = std::min(hintLevelUsed, 3);
        const double multiplier = 1.0 - (0.25 * static_cast<double>(cappedHintLevel));
        xpAwarded = static_cast<int>(static_cast<double>(xpAwarded) * multiplier);
    }

    context.ui.printLine("");
    if (result.correct) {
        context.ui.printSuccess("Doğru! (+" + std::to_string(xpAwarded) + " XP)");
        context.progress.markCodeExerciseCompleted(exercise.id);
        awardXpAndCheckLevelUp(context, xpAwarded);
    } else {
        context.ui.playAlertSound();
        context.ui.printError("Gönderdiğin kod beklenen kriterleri karşılamıyor.");
    }

    context.ui.printLine("");
    context.ui.printLine("Örnek çözüm:");
    context.ui.printLine(exercise.sampleSolution);
    context.ui.printLine("");
    context.ui.printLine("Alternatif çözüm notu:");
    context.ui.printLine(exercise.alternativeSolutionNote);
    context.ui.printLine("");

    saveProgress(context);
}

void runCodeExerciseTier(AppContext& context, const std::string& tier) {
    const auto exercises = context.codeExercises.exercisesForTier(tier);
    bool inTierMenu = true;
    while (inTierMenu) {
        context.ui.printLine("");
        context.ui.printHeader(tier + " Alıştırmaları");
        int completedInTier = 0;
        for (const CodeExercise& exercise : exercises) {
            const bool done = context.progress.isCodeExerciseCompleted(exercise.id);
            if (done) {
                ++completedInTier;
            }
            context.ui.printLine(
                std::string("  [") + (done ? '+' : ' ') + "] " + std::to_string(exercise.id) +
                ". " + exercise.title);
        }
        context.ui.printLine("");
        context.ui.printLine(
            "Tamamlanan: " + std::to_string(completedInTier) + "/" +
            std::to_string(exercises.size()));
        context.ui.printLine("");
        context.ui.printLine("0. Geri dön");
        context.ui.printLine("");
        context.ui.printLine("Alıştırma numarasını gir:");

        int maxExerciseId = 0;
        for (const CodeExercise& allExercise : context.codeExercises.allExercises()) {
            maxExerciseId = std::max(maxExerciseId, allExercise.id);
        }
        const int choice = context.ui.readMenuChoice(0, maxExerciseId);
        if (context.ui.isInputClosed() || choice == 0) {
            inTierMenu = false;
            continue;
        }
        const auto exercise = context.codeExercises.findById(choice);
        if (!exercise.has_value() || exercise->tier != tier) {
            context.ui.printLine("Geçersiz alıştırma numarası.");
            continue;
        }
        runCodeExercise(context, *exercise);
    }
}

}  // namespace

void runCodeExercisesSession(AppContext& context) {
    bool inCodeExercisesMenu = true;
    while (inCodeExercisesMenu) {
        context.ui.printLine("");
        context.ui.printHeader("KOD YAZMA ALIŞTIRMALARI");
        context.ui.printLine("1. Başlangıç");
        context.ui.printLine("2. Orta");
        context.ui.printLine("3. İleri");
        context.ui.printLine("0. Geri dön");
        context.ui.printLine("");
        context.ui.printLine("Seçimin:");

        const int tierChoice = context.ui.readMenuChoice(0, 3);
        if (context.ui.isInputClosed()) {
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
            runCodeExerciseTier(context, tier);
        }
    }
}

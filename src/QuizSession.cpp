#include "QuizSession.h"

#include <algorithm>
#include <cstddef>
#include <optional>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "AdaptiveDifficulty.h"
#include "HintProvider.h"
#include "QuizSelection.h"
#include "TopicLock.h"

namespace {

constexpr double kPassThreshold = 0.7;

char optionLetter(std::size_t index) {
    return static_cast<char>('A' + index);
}

void checkAchievements(
    AppContext& context, const Question& question, bool correct, bool trackMistakes) {
    if (!correct) {
        return;
    }

    std::vector<AchievementId> newlyUnlocked;

    if (context.progress.totalCorrectAnswers() >= 1) {
        if (context.achievements.unlock(AchievementId::FirstStep)) {
            newlyUnlocked.push_back(AchievementId::FirstStep);
        }
    }
    if (context.progress.currentStreak() >= 5) {
        if (context.achievements.unlock(AchievementId::FlawlessFive)) {
            newlyUnlocked.push_back(AchievementId::FlawlessFive);
        }
    }
    if (context.progress.currentStreak() >= 10) {
        if (context.achievements.unlock(AchievementId::StreakMaster)) {
            newlyUnlocked.push_back(AchievementId::StreakMaster);
        }
    }
    if (context.progress.writeCodeCorrectCount() >= 10) {
        if (context.achievements.unlock(AchievementId::CodeWriter)) {
            newlyUnlocked.push_back(AchievementId::CodeWriter);
        }
    }
    if (context.progress.errorFixCorrectCount() >= 25) {
        if (context.achievements.unlock(AchievementId::BugHunter)) {
            newlyUnlocked.push_back(AchievementId::BugHunter);
        }
    }

    if (trackMistakes) {
        const auto mistakeRecord = context.mistakes.findMistake(question.id);
        if (mistakeRecord.has_value() && mistakeRecord->wrongCount >= 5) {
            if (context.achievements.unlock(AchievementId::NeverGiveUp)) {
                newlyUnlocked.push_back(AchievementId::NeverGiveUp);
            }
        }
    }

    if (newlyUnlocked.empty()) {
        return;
    }

    for (const AchievementId id : newlyUnlocked) {
        context.ui.printLine("");
        context.ui.printHighlight("Yeni başarım kazandın: " + achievementDisplayName(id));
        context.ui.printLine(achievementDescription(id));
    }
    context.ui.printLine("");
    if (!context.achievements.saveToFile(kAchievementsFilePath)) {
        context.ui.printError("Uyarı: başarımlar dosyası kaydedilemedi.");
    }
}

std::vector<Question> selectQuizQuestions(AppContext& context, int topicId) {
    const auto view = context.questions.questionViewForTopic(topicId);
    std::vector<std::size_t> shuffledIndices(view.size());
    for (std::size_t i = 0; i < view.size(); ++i) {
        shuffledIndices[i] = i;
    }
    // Shuffled here because Application owns the random engine; the policy
    // for *which* of them to keep lives in selectQuizQuestionsFrom, which is
    // pure and unit-tested.
    std::shuffle(shuffledIndices.begin(), shuffledIndices.end(), context.randomEngine);
    std::vector<Question> pool;
    pool.reserve(view.size());
    for (const std::size_t index : shuffledIndices) {
        pool.push_back(view[index]);
    }
    return selectQuizQuestionsFrom(
        pool, static_cast<std::size_t>(context.settings.topicQuizQuestionCount),
        [&context](const Question& question) { return context.mistakes.hasMistake(question.id); });
}

void runMistakeQuestions(AppContext& context, const std::vector<MistakeRecord>& mistakesToAsk) {
    int correctCount = 0;
    int sessionXp = 0;

    for (const MistakeRecord& mistake : mistakesToAsk) {
        const Question* const question = context.questions.findPtrById(mistake.questionId);
        if (question == nullptr) {
            continue;
        }
        const AnswerResult result = askOneQuestion(context, *question);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(context, sessionXp);
            saveProgress(context);
            return;
        }
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }
    }

    awardXpAndCheckLevelUp(context, sessionXp);
    saveProgress(context);

    context.ui.printLine(
        "Tamamlandı: " + std::to_string(correctCount) + "/" + std::to_string(mistakesToAsk.size()) +
        " doğru, kazanılan XP: " + std::to_string(sessionXp));
    context.ui.printLine("");
}

}  // namespace

AnswerResult askOneQuestion(
    AppContext& context, const Question& question, bool trackMistakes, bool allowHints) {
    context.ui.printLine(question.prompt);

    // Whatever the learner is expected to type — a letter or a number — is
    // green, the same signal the menus use.
    if (question.type == QuestionType::MultipleChoice ||
        question.type == QuestionType::Scenario) {
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            std::string marker;
            marker.push_back(optionLetter(index));
            marker += ")";
            context.ui.printLine(
                context.ui.colorize(marker, TextColor::Green) + " " + question.options[index]);
        }
    } else if (question.type == QuestionType::Matching) {
        // Options hold the numbered left column; the prompt itself lists
        // the lettered right column, so the learner replies with pairs.
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            context.ui.printMenuItem(static_cast<int>(index) + 1, question.options[index]);
        }
        context.ui.printLine("");
        context.ui.printLine(
            context.ui.colorize("Eşleştirmeleri \"1-c, 2-a, 3-b\" biçiminde yaz.", TextColor::Dim));
    } else if (question.type == QuestionType::TrueFalse) {
        context.ui.printMenuItem(1, "Doğru");
        context.ui.printMenuItem(2, "Yanlış");
    } else if (question.type == QuestionType::OrderCode) {
        for (std::size_t index = 0; index < question.options.size(); ++index) {
            context.ui.printMenuItem(static_cast<int>(index) + 1, question.options[index]);
        }
    }

    int hintLevelUsed = 0;
    std::string rawAnswer;
    bool skipped = false;
    bool exitRequested = false;

    if (question.type == QuestionType::WriteCode) {
        context.ui.printLine(
            "Kodunu birden fazla satır halinde girebilirsin. Bitirmek için BITIR yazıp Enter'a "
            "bas.");
        rawAnswer = context.ui.readMultilineCode();
        if (context.ui.isInputClosed() && rawAnswer.empty()) {
            exitRequested = true;
        }
    } else {
        while (true) {
            rawAnswer = context.ui.readLine("Cevabın: ");
            if (context.ui.isInputClosed() || rawAnswer == "cikis") {
                exitRequested = true;
                break;
            }
            if (rawAnswer == "gec") {
                skipped = true;
                break;
            }
            if (rawAnswer == "ipucu") {
                if (!allowHints) {
                    context.ui.printLine("Sınav sırasında ipucu kullanılamaz.");
                    continue;
                }
                if (hintLevelUsed < 3) {
                    ++hintLevelUsed;
                }
                context.ui.printLine(generateHint(question, hintLevelUsed));
                continue;
            }
            if (rawAnswer == "konu") {
                if (!allowHints) {
                    context.ui.printLine("Sınav sırasında bu komut kullanılamaz.");
                    continue;
                }
                const Lesson* const lesson = context.lessons.findPtrById(question.topicId);
                if (lesson != nullptr && !lesson->explanation.empty()) {
                    context.ui.printLine(lesson->explanation);
                } else {
                    context.ui.printLine("Bu konu için ders içeriği bu sürümde henüz eklenmedi.");
                }
                continue;
            }
            if (rawAnswer == "ornek") {
                if (!allowHints) {
                    context.ui.printLine("Sınav sırasında bu komut kullanılamaz.");
                    continue;
                }
                const Lesson* const lesson = context.lessons.findPtrById(question.topicId);
                if (lesson != nullptr && !lesson->exampleCode.empty()) {
                    context.ui.printLine(lesson->exampleCode);
                } else {
                    context.ui.printLine("Bu konu için örnek bu sürümde henüz eklenmedi.");
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
        result = AnswerResult{false, 0, context.quizEngine.correctAnswerDisplay(question), false};
    } else {
        result = context.quizEngine.evaluate(question, rawAnswer, context.settings);
        if (result.correct && hintLevelUsed > 0) {
            const double multiplier = 1.0 - (0.25 * static_cast<double>(hintLevelUsed));
            result.xpAwarded = static_cast<int>(static_cast<double>(result.xpAwarded) * multiplier);
        }
    }

    if (result.correct) {
        context.ui.printSuccess("Doğru! (+" + std::to_string(result.xpAwarded) + " XP)");
    } else {
        context.ui.playAlertSound();
        context.ui.printLine("");
        context.ui.printError("Yanlış cevap.");
        context.ui.printLine("");
        context.ui.printLine("Senin cevabın:");
        context.ui.printLine(skipped ? "(soru geçildi)" : rawAnswer);
        context.ui.printLine("");
        context.ui.printLine("Doğru cevap:");
        context.ui.printLine(result.correctAnswerDisplay);
        context.ui.printLine("");
        context.ui.printLine("Açıklama:");
        context.ui.printLine(question.explanation);
    }
    context.ui.printLine("");

    context.progress.recordAnswer(result.correct);
    context.progress.recordStreak(result.correct);
    if (result.correct) {
        context.progress.recordTypedCorrectAnswer(question.type);
        if (trackMistakes && context.mistakes.hasMistake(question.id)) {
            context.mistakes.recordCorrectRetry(question.id);
        }
    } else if (trackMistakes) {
        context.mistakes.recordWrong(question.id);
    }

    checkAchievements(context, question, result.correct, trackMistakes);

    saveProgress(context);
    if (trackMistakes && !context.mistakes.saveToFile(kMistakesFilePath)) {
        context.ui.printError("Uyarı: yanlış kayıtları dosyası kaydedilemedi.");
    }

    return result;
}

void runTopicQuizSession(AppContext& context, int topicId) {
    auto remaining = selectQuizQuestions(context, topicId);
    std::ranges::stable_sort(remaining, {}, &Question::difficulty);
    const auto totalQuestions = static_cast<int>(remaining.size());

    context.ui.printLine("Konu testi başlıyor (" + std::to_string(totalQuestions) + " soru).");
    context.ui.printLine("");

    const Lesson* const lesson = context.lessons.findPtrById(topicId);

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
                context.ui.printLine("");
                context.ui.printLine("Bu konuyu tekrar hatırlayalım:");
                context.ui.printLine(lesson->explanation);
            }
            if (question.type != QuestionType::WriteCode) {
                context.ui.printLine(generateHint(question, 1));
            }
            wrongStreak = 0;
        }

        const AnswerResult result = askOneQuestion(context, question);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(context, sessionXp);
            saveProgress(context);
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
    context.ui.printLine(
        "Sonuç: " +
        context.ui.colorize(
            std::to_string(correctCount) + "/" + std::to_string(totalQuestions) + " doğru (%" +
                std::to_string(successPercent) + ")",
            passed ? TextColor::Green : TextColor::Yellow) +
        ", kazanılan XP: " + context.ui.colorize(std::to_string(sessionXp), TextColor::Yellow));

    awardXpAndCheckLevelUp(context, sessionXp);

    const TopicStatus updatedStatus =
        nextTopicStatusAfterQuiz(context.progress.statusOf(topicId), passed);
    context.progress.setStatus(topicId, updatedStatus);
    if (passed) {
        context.ui.printSuccess("Bu konu tamamlandı olarak işaretlendi.");
    } else {
        context.ui.printHighlight(
            "Bu konuyu öğrenmeye devam ediyorsun; tekrar denemek için tekrar açabilirsin.");
    }
    context.ui.printLine("");

    saveProgress(context);
}

void runMistakeReviewSession(AppContext& context) {
    const auto mistakes = context.mistakes.allMistakesOldestFirst();
    if (mistakes.empty()) {
        context.ui.printLine("");
        context.ui.printLine("Henüz kaydedilmiş bir yanlışın yok!");
        return;
    }

    context.ui.printLine("");
    context.ui.printLine("Kayıtlı yanlışların (" + std::to_string(mistakes.size()) + " soru):");
    context.ui.printLine("");
    runMistakeQuestions(context, mistakes);
}

void runDailyReviewSession(AppContext& context) {
    auto mistakes = context.mistakes.allMistakesOldestFirst();
    if (mistakes.empty()) {
        context.ui.printLine("");
        context.ui.printLine(
            "Henüz tekrar edilecek bir yanlışın yok! Önce birkaç konu testi çözmelisin.");
        return;
    }

    const auto dailyReviewCap = static_cast<std::size_t>(context.settings.dailyReviewQuestionCap);
    if (mistakes.size() > dailyReviewCap) {
        mistakes.resize(dailyReviewCap);
    }

    context.ui.printLine("");
    context.ui.printLine("Günlük tekrar başlıyor (" + std::to_string(mistakes.size()) + " soru):");
    context.ui.printLine("");
    runMistakeQuestions(context, mistakes);
}

void runQuickTestSession(AppContext& context) {
    context.ui.printLine("");
    context.ui.printHeader("HIZLI TEST");

    const int kQuickTestQuestionCount = context.settings.quickTestQuestionCount;
    // Read from settings, not hardcoded: the count became configurable
    // (1-20) but this line still promised "5" regardless.
    context.ui.printLine(
        "Senin için " + std::to_string(kQuickTestQuestionCount) +
        " taze soru üretmeye çalışacağım.");
    context.ui.printLine("");

    int correctCount = 0;
    int sessionXp = 0;
    int askedCount = 0;

    const auto& allGenerators = context.generatorRegistry.allGenerators();
    if (allGenerators.empty()) {
        context.ui.printLine("Bu oturumda soru üretici bulunamadı.");
        context.ui.printLine("");
        return;
    }

    for (int index = 0; index < kQuickTestQuestionCount; ++index) {
        std::uniform_int_distribution<std::size_t> topicPickDist(0, allGenerators.size() - 1);
        const int pickedTopicId = allGenerators[topicPickDist(context.randomEngine)]->topicId();

        std::optional<GeneratedQuestion> generated =
            context.generationEngine.generateUniqueForTopic(
                pickedTopicId, context.generatorRegistry, context.generatorScoring,
                context.generatedQuestionValidator, context.randomEngine);

        if (!generated.has_value()) {
            context.ui.printLine(
                "Bu oturumda başka taze soru üretemedim; testi burada bitiriyorum.");
            break;
        }

        generated->question.id = context.nextGeneratedQuestionId++;
        const AnswerResult result =
            askOneQuestion(context, generated->question, /*trackMistakes=*/false);
        if (result.exitRequested) {
            if (!context.generationEngine.saveHistory(kGeneratedHistoryFilePath)) {
                context.ui.printError("Uyarı: üretilen soru geçmişi kaydedilemedi.");
            }
            awardXpAndCheckLevelUp(context, sessionXp);
            saveProgress(context);
            return;
        }
        ++askedCount;
        if (result.correct) {
            ++correctCount;
            sessionXp += result.xpAwarded;
        }

        if (!context.generationEngine.saveHistory(kGeneratedHistoryFilePath)) {
            context.ui.printError("Uyarı: üretilen soru geçmişi kaydedilemedi.");
        }
    }

    if (askedCount > 0) {
        const int successPercent = static_cast<int>(
            (static_cast<double>(correctCount) / static_cast<double>(askedCount)) * 100.0);
        context.ui.printLine(
            "Hızlı test bitti: " + std::to_string(correctCount) + "/" + std::to_string(askedCount) +
            " doğru (%" + std::to_string(successPercent) +
            "), kazanılan XP: " + std::to_string(sessionXp));
    }
    context.ui.printLine("");

    awardXpAndCheckLevelUp(context, sessionXp);
    saveProgress(context);
}

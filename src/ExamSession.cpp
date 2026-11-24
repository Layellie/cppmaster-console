#include "ExamSession.h"

#include <string>
#include <vector>

#include "ExamContent.h"
#include "QuizSession.h"
#include "TopicLock.h"

namespace {

constexpr double kExamPassThreshold = 0.7;
constexpr double kSectionCompletionGateThreshold = 0.7;

// Section exams and the general final exam differ only in which topics
// gate them, which questions they ask, their heading, and whether
// passing records a section milestone — everything else (the gate
// check, the ask loop, scoring, the perfect-score achievement) is
// identical, so both funnel through runExam.
struct ExamPlan {
    std::string heading;
    std::string lockedMessage;
    // Ids only, not Lesson copies: the gate just counts completed
    // topics, and the final exam would otherwise deep-copy all 100
    // lessons (each carrying its explanation, example code and
    // explanation/mistake vectors) to read one status per topic.
    std::vector<int> gatingTopicIds;
    std::vector<int> questionIds;
    int sectionIdToRecordOnPass = 0;  // 0 = don't record (final exam)
};

void runExam(AppContext& context, const ExamPlan& plan) {
    const int topicCount = static_cast<int>(plan.gatingTopicIds.size());
    if (topicCount == 0 || plan.questionIds.empty()) {
        // Defensive: every caller passes a non-empty plan today, but an
        // empty one would otherwise divide by zero when scoring.
        context.ui.printLine("");
        context.ui.printLine("Bu sınav şu anda kullanılamıyor.");
        return;
    }

    int completedCount = 0;
    for (const int topicId : plan.gatingTopicIds) {
        const TopicStatus status = context.progress.statusOf(topicId);
        if (status == TopicStatus::Completed || status == TopicStatus::Mastered) {
            ++completedCount;
        }
    }

    const double completionRatio =
        static_cast<double>(completedCount) / static_cast<double>(topicCount);

    if (!sectionExamIsUnlocked(
            context.settings.topicLockEnabled, completionRatio, kSectionCompletionGateThreshold)) {
        context.ui.printLine("");
        context.ui.printLine(plan.lockedMessage);
        context.ui.printLine(
            "Şu an " + std::to_string(completedCount) + "/" + std::to_string(topicCount) +
            " konu tamamlanmış.");
        return;
    }

    const int examQuestionCount = static_cast<int>(plan.questionIds.size());

    context.ui.printLine("");
    context.ui.printHeader(plan.heading);
    context.ui.printLine(
        std::to_string(examQuestionCount) + " soruluk sınav başlıyor. Geçme notu: %70.");
    context.ui.printLine("");

    int correctCount = 0;
    int examXp = 0;

    for (const int questionId : plan.questionIds) {
        const Question* const question = context.questions.findPtrById(questionId);
        if (question == nullptr) {
            continue;
        }
        const AnswerResult result =
            askOneQuestion(context, *question, /*trackMistakes=*/true, /*allowHints=*/false);
        if (result.exitRequested) {
            awardXpAndCheckLevelUp(context, examXp);
            saveProgress(context);
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

    context.ui.printLine(
        "Doğru: " + std::to_string(correctCount) + "/" + std::to_string(examQuestionCount));
    context.ui.printLine("Başarı: %" + std::to_string(scorePercent));
    context.ui.printLine(
        "Kazanılan XP: " + context.ui.colorize(std::to_string(examXp), TextColor::Yellow));
    const bool passed = scoreRatio >= kExamPassThreshold;
    if (passed) {
        context.ui.printSuccess("Sonuç: GEÇTİN");
    } else {
        context.ui.printError("Sonuç: KALDIN");
    }

    if (passed && plan.sectionIdToRecordOnPass > 0) {
        context.progress.recordSectionExamPassed(plan.sectionIdToRecordOnPass);
    }

    if (correctCount == examQuestionCount &&
        context.achievements.unlock(AchievementId::PerfectExam)) {
        context.ui.printLine("");
        context.ui.printHighlight(
            "Yeni başarım kazandın: " + achievementDisplayName(AchievementId::PerfectExam));
        context.ui.printLine(achievementDescription(AchievementId::PerfectExam));
        if (!context.achievements.saveToFile(kAchievementsFilePath)) {
            context.ui.printError("Uyarı: başarımlar dosyası kaydedilemedi.");
        }
    }

    awardXpAndCheckLevelUp(context, examXp);
    saveProgress(context);

    context.ui.printLine("");
}

void runSectionExam(AppContext& context, int sectionId) {
    ExamPlan plan;
    plan.heading = "BÖLÜM " + std::to_string(sectionId) + " SINAVI";
    plan.lockedMessage =
        "Bu bölümün sınavına girebilmek için konuların en az %70'ini tamamlamalısın.";
    const auto sectionLessons = context.lessons.lessonsViewInSection(sectionId);
    plan.gatingTopicIds.reserve(sectionLessons.size());
    for (const Lesson& lesson : sectionLessons) {
        plan.gatingTopicIds.push_back(lesson.id);
    }
    plan.questionIds = examQuestionIdsForSection(sectionId);
    plan.sectionIdToRecordOnPass = sectionId;
    runExam(context, plan);
}

void runFinalExam(AppContext& context) {
    ExamPlan plan;
    plan.heading = "GENEL FİNAL SINAVI";
    plan.lockedMessage =
        "Genel final sınavına girebilmek için tüm konuların en az %70'ini tamamlamalısın.";
    // allLessons() returns a reference, so this reads ids without copying
    // the lessons themselves.
    plan.gatingTopicIds.reserve(context.lessons.allLessons().size());
    for (const Lesson& lesson : context.lessons.allLessons()) {
        plan.gatingTopicIds.push_back(lesson.id);
    }
    plan.questionIds = finalExamQuestionIds();
    // Deliberately 0: there is no "section 11" milestone to record for the
    // general final exam.
    plan.sectionIdToRecordOnPass = 0;
    runExam(context, plan);
}

}  // namespace

void showExamMenuSession(AppContext& context) {
    context.ui.printLine("");
    context.ui.printLine("Hangi sınava girmek istiyorsun?");
    for (int sectionId = 1; sectionId <= context.lessons.sectionCount(); ++sectionId) {
        context.ui.printMenuItem(
            sectionId, "Bölüm " + std::to_string(sectionId) + " Sınavı: " +
                           context.ui.colorize(
                               context.lessons.sectionTitle(sectionId), TextColor::Cyan));
    }
    const int finalExamChoice = context.lessons.sectionCount() + 1;
    context.ui.printMenuItem(
        finalExamChoice, context.ui.colorize("Genel Final Sınavı", TextColor::Yellow));
    context.ui.printMenuItem(0, "Geri dön");
    const int choice = context.ui.readMenuChoice(0, finalExamChoice);
    if (context.ui.isInputClosed() || choice == 0) {
        return;
    }
    if (choice == finalExamChoice) {
        runFinalExam(context);
        return;
    }
    runSectionExam(context, choice);
}

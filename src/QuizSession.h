#pragma once

#include "AppContext.h"
#include "Question.h"
#include "QuizEngine.h"

AnswerResult askOneQuestion(
    AppContext& context, const Question& question, bool trackMistakes = true,
    bool allowHints = true);
void runTopicQuizSession(AppContext& context, int topicId);
void runMistakeReviewSession(AppContext& context);
void runDailyReviewSession(AppContext& context);
void runQuickTestSession(AppContext& context);

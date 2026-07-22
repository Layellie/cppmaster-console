#pragma once

struct Settings {
    bool topicLockEnabled = true;
    bool strictCaseSensitivity = true;
    bool lenientWriteCodeTolerance = false;
    bool fullExplanationDetail = true;
    int dailyReviewQuestionCap = 20;
    bool colorEnabled = true;
    bool audioAlertEnabled = false;
    int quickTestQuestionCount = 10;
    // Topics hold up to 31 questions. Asking a subset is what makes a
    // retake ask different ones, so this stays well below the pool size —
    // raise it for longer sessions, at the cost of that variety.
    int topicQuizQuestionCount = 15;
};

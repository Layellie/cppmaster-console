#pragma once

struct Settings {
    bool topicLockEnabled = true;
    bool strictCaseSensitivity = true;
    bool lenientWriteCodeTolerance = false;
    bool fullExplanationDetail = true;
    int dailyReviewQuestionCap = 20;
    bool colorEnabled = true;
    bool audioAlertEnabled = false;
    int quickTestQuestionCount = 5;
};

#pragma once

#include <string>

#include "ConsoleUI.h"
#include "LessonManager.h"
#include "UserProgress.h"

class Application {
public:
    Application();

    void run();

private:
    void showMainMenu();
    void handleChoice(int choice);
    void showTopicBrowser();
    void showNotYetAvailable(const std::string& featureName);
    void ensureDataDirectoryExists();

    ConsoleUI ui_;
    LessonManager lessons_;
    UserProgress progress_;
    bool running_ = true;
};

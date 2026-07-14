#pragma once

#include <string>

class ConsoleUI {
public:
    ConsoleUI();

    void clearScreen() const;
    void printLine(const std::string& text) const;
    void printHeader(const std::string& title) const;

    int readMenuChoice(int minValue, int maxValue);
    std::string readLine(const std::string& prompt);
};

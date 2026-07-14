#pragma once

#include <string>

class ConsoleUI {
public:
    ConsoleUI();

    void clearScreen() const;
    void printLine(const std::string& text) const;
    void printHeader(const std::string& title) const;

    // Re-prompts on invalid or out-of-range input. On genuine stdin EOF
    // (no more input will ever arrive), returns minValue rather than
    // looping forever — callers with minValue == 0 (an exit/back option)
    // get correct "treat EOF as exit" behavior for free; callers that use
    // a different minValue should be aware EOF and choosing minValue are
    // indistinguishable.
    int readMenuChoice(int minValue, int maxValue);
    std::string readLine(const std::string& prompt);
};

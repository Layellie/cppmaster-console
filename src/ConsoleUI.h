#pragma once

#include <cstddef>
#include <string>

// Palette shared with the project banner, so the running app and the
// README image look like the same product. Each entry has one job; reusing
// a colour for an unrelated meaning is what makes a terminal UI noisy.
enum class TextColor {
    Green,    // menu numbers, prompts, correct answers, completed topics
    Red,      // wrong answers
    Yellow,   // XP, achievements, topics still being learned
    Magenta,  // level names, mastered topics
    Cyan,     // section headings in the topic list
    Heading,  // bold screen titles
    Dim,      // separators, hints, not-started topics
};

class ConsoleUI {
public:
    ConsoleUI();

    void clearScreen() const;
    void printLine(const std::string& text) const;

    // `ruleWidth` lets a screen widen the ==== rules to match content that is
    // wider than the default — the column menu would otherwise sit under a
    // header noticeably narrower than itself.
    void printHeader(const std::string& title, std::size_t ruleWidth = 40) const;

    // Wraps `text` in the escape codes for `color`, or returns it unchanged
    // when colour is off. Returning a string rather than printing lets
    // callers colour one part of a line — "Toplam XP: " plus a yellow value.
    [[nodiscard]] std::string colorize(const std::string& text, TextColor color) const;

    // Renders "N. Label" with the number in green, matching the banner.
    void printMenuItem(int number, const std::string& label) const;

    // Colored output for correct/wrong/celebratory feedback. Falls back to
    // plain output when color is disabled via setColorEnabled, or when the
    // terminal doesn't support ANSI escape codes (colorSupported_ is false
    // if enabling VT processing failed on Windows).
    void setColorEnabled(bool enabled);
    void printSuccess(const std::string& text) const;
    void printError(const std::string& text) const;
    void printHighlight(const std::string& text) const;

    // Console bell character, only emitted when enabled. No-op otherwise.
    void setAudioAlertEnabled(bool enabled);
    void playAlertSound() const;

    // Re-prompts on invalid or out-of-range input. On genuine stdin EOF
    // (no more input will ever arrive), returns minValue rather than
    // looping forever — callers with minValue == 0 (an exit/back option)
    // get correct "treat EOF as exit" behavior for free; callers that use
    // a different minValue should be aware EOF and choosing minValue are
    // indistinguishable.
    int readMenuChoice(int minValue, int maxValue);
    std::string readLine(const std::string& prompt);

    // Reads multiple lines until the user types exactly "BITIR" (or EOF is
    // reached), joining the collected lines with '\n'. Used for WriteCode
    // answers, matching the product spec's multi-line code entry convention.
    std::string readMultilineCode();

private:
    bool colorEnabled_ = false;
    bool colorSupported_ = false;
    bool audioAlertEnabled_ = false;
};

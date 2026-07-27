#include "ConsoleUI.h"

#include <charconv>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <system_error>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace {

std::string trim(const std::string& text) {
    const auto first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return "";
    }
    const auto last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

void printColored(const std::string& text, const char* colorCode, bool active) {
    if (active) {
        std::cout << "\x1b[" << colorCode << "m" << text << "\x1b[0m\n";
    } else {
        std::cout << text << '\n';
    }
}

const char* escapeCodeFor(TextColor color) {
    switch (color) {
        case TextColor::Green:
            return "32";
        case TextColor::Red:
            return "31";
        case TextColor::Yellow:
            return "33";
        case TextColor::Blue:
            // Bright blue: plain blue is close to unreadable on the dark
            // backgrounds these terminals default to.
            return "94";
        case TextColor::Dim:
            return "90";
    }
    return "0";
}

// Colour is only safe when stdout is a terminal that can render it.
// Redirected output (a pipe or a file) must stay plain, or the user opening
// that file finds raw escape sequences in it.
//
// Windows additionally needs virtual-terminal processing switched on before
// it renders escape codes at all, and that call can fail on older consoles.
// It also happens to fail for a pipe, which is why the redirect case was
// handled there — POSIX needs an explicit isatty check to match.
bool enableAnsiColorSupport() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    const HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (outputHandle == INVALID_HANDLE_VALUE) {
        return false;
    }
    DWORD consoleMode = 0;
    if (GetConsoleMode(outputHandle, &consoleMode) == 0) {
        return false;
    }
    return SetConsoleMode(outputHandle, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
#else
    return isatty(STDOUT_FILENO) != 0;
#endif
}

}  // namespace

ConsoleUI::ConsoleUI() : colorSupported_(enableAnsiColorSupport()) {}

void ConsoleUI::clearScreen() const {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ConsoleUI::printLine(const std::string& text) const {
    std::cout << text << '\n';
}

void ConsoleUI::printHeader(const std::string& title) const {
    const std::string separator(40, '=');
    const std::string rule = colorize(separator, TextColor::Green);
    std::cout << rule << '\n' << title << '\n' << rule << '\n';
}

std::string ConsoleUI::colorize(const std::string& text, TextColor color) const {
    if (!colorEnabled_ || !colorSupported_) {
        return text;
    }
    return std::string("\x1b[") + escapeCodeFor(color) + "m" + text + "\x1b[0m";
}

void ConsoleUI::printMenuItem(int number, const std::string& label) const {
    printLine(colorize(std::to_string(number) + ".", TextColor::Green) + " " + label);
}

void ConsoleUI::setColorEnabled(bool enabled) {
    colorEnabled_ = enabled;
}

void ConsoleUI::printSuccess(const std::string& text) const {
    printColored(text, "32", colorEnabled_ && colorSupported_);
}

void ConsoleUI::printError(const std::string& text) const {
    printColored(text, "31", colorEnabled_ && colorSupported_);
}

void ConsoleUI::printHighlight(const std::string& text) const {
    printColored(text, "33", colorEnabled_ && colorSupported_);
}

void ConsoleUI::setAudioAlertEnabled(bool enabled) {
    audioAlertEnabled_ = enabled;
}

void ConsoleUI::playAlertSound() const {
    if (audioAlertEnabled_) {
        std::cout << '\a' << std::flush;
    }
}

int ConsoleUI::readMenuChoice(int minValue, int maxValue) {
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            if (std::cin.eof()) {
                return minValue;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        const std::string trimmed = trim(line);
        int value = 0;
        const auto result = std::from_chars(
            trimmed.data(), trimmed.data() + trimmed.size(), value);

        const bool parsedWholeString =
            result.ec == std::errc{} && result.ptr == trimmed.data() + trimmed.size();

        if (parsedWholeString && value >= minValue && value <= maxValue) {
            return value;
        }

        std::cout << "Geçersiz seçim. Lütfen " << minValue << " ile " << maxValue
                   << " arasında bir sayı gir: ";
    }
}

std::string ConsoleUI::readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::string ConsoleUI::readMultilineCode() {
    std::string result;
    while (true) {
        std::string line;
        if (!std::getline(std::cin, line)) {
            break;
        }
        if (line == "BITIR") {
            break;
        }
        if (!result.empty()) {
            result += '\n';
        }
        result += line;
    }
    return result;
}

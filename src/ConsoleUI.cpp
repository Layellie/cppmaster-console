#include "ConsoleUI.h"

#include <charconv>
#include <iostream>
#include <limits>
#include <string>
#include <system_error>

#ifdef _WIN32
#include <array>
#include <sstream>
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
        case TextColor::Magenta:
            // Deliberately not blue. Plain blue (34) is unreadable on the
            // dark backgrounds terminals default to, and the bright slot
            // (94) is the one custom colour schemes repaint most often — on
            // this project's own development machine the scheme maps 34 to
            // red and 94 to yellow, so "level name" and "mastered" came out
            // colliding with two other meanings. Magenta survives that.
            return "95";
        case TextColor::Cyan:
            return "96";
        case TextColor::Heading:
            // Bold bright white — a title, not a colour accent.
            return "1;97";
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
    HANDLE const outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (outputHandle == INVALID_HANDLE_VALUE || outputHandle == nullptr) {
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

#ifdef _WIN32
bool readUtf8LineFromWindowsConsole(std::string& outLine, bool& outWasConsole) {
    outWasConsole = false;
    // Unit tests redirect std::cin to a std::istringstream even when launched
    // from an interactive terminal; honour that redirection rather than
    // reading directly from the underlying console handle.
    if (dynamic_cast<std::stringbuf*>(std::cin.rdbuf()) != nullptr) {
        return false;
    }

    HANDLE const inputHandle = GetStdHandle(STD_INPUT_HANDLE);
    if (inputHandle == INVALID_HANDLE_VALUE || inputHandle == nullptr) {
        return false;
    }
    DWORD consoleMode = 0;
    if (GetConsoleMode(inputHandle, &consoleMode) == 0) {
        return false;
    }

    outWasConsole = true;
    std::wstring wideLine;
    std::array<wchar_t, 256> buffer{};
    while (true) {
        DWORD charsRead = 0;
        if (ReadConsoleW(
                inputHandle, buffer.data(), static_cast<DWORD>(buffer.size()), &charsRead,
                nullptr) == 0) {
            return false;
        }
        if (charsRead == 0) {
            return !wideLine.empty();
        }
        bool reachedEnd = false;
        for (DWORD i = 0; i < charsRead; ++i) {
            const wchar_t ch = buffer[i];
            if (ch == L'\x1a') {
                return !wideLine.empty();
            }
            if (ch == L'\n') {
                reachedEnd = true;
                break;
            }
            if (ch != L'\r') {
                wideLine.push_back(ch);
            }
        }
        if (reachedEnd) {
            break;
        }
    }

    if (wideLine.empty()) {
        outLine.clear();
        return true;
    }

    const int utf8Size = WideCharToMultiByte(
        CP_UTF8, 0, wideLine.data(), static_cast<int>(wideLine.size()), nullptr, 0, nullptr,
        nullptr);
    if (utf8Size <= 0) {
        outLine.clear();
        return false;
    }
    outLine.resize(static_cast<std::size_t>(utf8Size));
    const int converted = WideCharToMultiByte(
        CP_UTF8, 0, wideLine.data(), static_cast<int>(wideLine.size()), outLine.data(), utf8Size,
        nullptr, nullptr);
    if (converted <= 0) {
        outLine.clear();
        return false;
    }
    return true;
}
#endif

bool readInputLine(std::string& outLine) {
#ifdef _WIN32
    bool wasConsole = false;
    const bool consoleReadOk = readUtf8LineFromWindowsConsole(outLine, wasConsole);
    if (wasConsole) {
        if (!consoleReadOk) {
            std::cin.setstate(std::ios::eofbit);
        }
        return consoleReadOk;
    }
#endif
    return static_cast<bool>(std::getline(std::cin, outLine));
}

}  // namespace

ConsoleUI::ConsoleUI() {
#ifdef _WIN32
    originalOutputCodePage_ = static_cast<std::uint32_t>(GetConsoleOutputCP());
    originalInputCodePage_ = static_cast<std::uint32_t>(GetConsoleCP());
    restoreCodePages_ = true;
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    colorSupported_ = enableAnsiColorSupport();
}

ConsoleUI::~ConsoleUI() {
#ifdef _WIN32
    if (restoreCodePages_) {
        if (originalOutputCodePage_ != 0) {
            SetConsoleOutputCP(originalOutputCodePage_);
        }
        if (originalInputCodePage_ != 0) {
            SetConsoleCP(originalInputCodePage_);
        }
    }
#endif
}

void ConsoleUI::clearScreen() const {
    if (colorSupported_) {
        std::cout << "\x1b[2J\x1b[3J\x1b[H" << std::flush;
        return;
    }
#ifdef _WIN32
    HANDLE const outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (outputHandle == INVALID_HANDLE_VALUE || outputHandle == nullptr) {
        return;
    }
    CONSOLE_SCREEN_BUFFER_INFO screenInfo{};
    if (GetConsoleScreenBufferInfo(outputHandle, &screenInfo) == 0) {
        return;
    }
    const DWORD cellCount =
        static_cast<DWORD>(screenInfo.dwSize.X) * static_cast<DWORD>(screenInfo.dwSize.Y);
    const COORD homeCoord{0, 0};
    DWORD written = 0;
    FillConsoleOutputCharacterA(outputHandle, ' ', cellCount, homeCoord, &written);
    FillConsoleOutputAttribute(
        outputHandle, screenInfo.wAttributes, cellCount, homeCoord, &written);
    SetConsoleCursorPosition(outputHandle, homeCoord);
#endif
}

void ConsoleUI::printLine(const std::string& text) const {
    std::cout << text << '\n';
}

void ConsoleUI::printHeader(const std::string& title, std::size_t ruleWidth) const {
    const std::string separator(ruleWidth, '=');
    const std::string rule = colorize(separator, TextColor::Green);
    std::cout << rule << '\n'
              << colorize(title, TextColor::Heading) << '\n'
              << rule << '\n';
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
    if (inputClosed_) {
        return minValue;
    }
    while (true) {
        std::string line;
        if (!readInputLine(line)) {
            if (std::cin.eof() || std::cin.bad()) {
                inputClosed_ = true;
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
    if (inputClosed_) {
        return "";
    }
    std::cout << prompt << std::flush;
    std::string line;
    if (!readInputLine(line)) {
        inputClosed_ = true;
        return "";
    }
    return line;
}

std::string ConsoleUI::readMultilineCode() {
    if (inputClosed_) {
        return "";
    }
    std::string result;
    while (true) {
        std::string line;
        if (!readInputLine(line)) {
            inputClosed_ = true;
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

bool ConsoleUI::isInputClosed() const noexcept {
    return inputClosed_;
}

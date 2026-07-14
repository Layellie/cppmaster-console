#include "ConsoleUI.h"

#include <charconv>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <system_error>

#ifdef _WIN32
#define NOMINMAX
#include <windows.h>
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

}  // namespace

ConsoleUI::ConsoleUI() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
}

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
    std::cout << separator << '\n' << title << '\n' << separator << '\n';
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
                   << " arasında bir sayı girin: ";
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

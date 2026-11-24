#include "ConsoleUI.h"

#include <iostream>
#include <sstream>
#include <string>

#include "TestRunner.h"

// ConsoleUI is otherwise left to manual end-to-end checks, since it is bound
// to real console I/O. This one property is worth pinning down in code: when
// colour is unavailable or switched off, the text must come back untouched.
// Getting it wrong writes raw escape sequences into redirected output, which
// is exactly what a user piping the app to a file would see.

TEST_CASE(ConsoleUI_ColorizeLeavesTextUntouchedWhenColorIsDisabled) {
    ConsoleUI ui;
    ui.setColorEnabled(false);

    const std::string text = "Toplam XP: 75";
    CHECK(ui.colorize(text, TextColor::Green) == text);
    CHECK(ui.colorize(text, TextColor::Yellow) == text);
    CHECK(ui.colorize(text, TextColor::Magenta) == text);
    CHECK(ui.colorize("", TextColor::Red).empty());
}

TEST_CASE(ConsoleUI_ColorizeNeverEmitsEscapeCodesIntoRedirectedOutput) {
    // The test binary's stdout is redirected, so colour support is off and
    // enabling the setting must still not introduce escape codes.
    ConsoleUI ui;
    ui.setColorEnabled(true);

    const std::string colored = ui.colorize("merhaba", TextColor::Green);
    CHECK(colored.find('\x1b') == std::string::npos);
    CHECK(colored == "merhaba");
}

TEST_CASE(ConsoleUI_ClearScreenDoesNotEmitEscapeCodesToRedirectedOutput) {
    ConsoleUI ui;
    ui.setColorEnabled(true);

    std::ostringstream captured;
    std::streambuf* const previousOut = std::cout.rdbuf(captured.rdbuf());
    ui.clearScreen();
    std::cout.rdbuf(previousOut);

    CHECK(captured.str().empty());
}

TEST_CASE(ConsoleUI_ReadLinePreservesTurkishUtf8Text) {
    ConsoleUI ui;
    std::istringstream fakeInput("ğüşiöçİĞÜŞÖÇ\n");
    std::ostringstream capturedOut;
    std::streambuf* const previousIn = std::cin.rdbuf(fakeInput.rdbuf());
    std::streambuf* const previousOut = std::cout.rdbuf(capturedOut.rdbuf());
    std::cin.clear();

    const std::string line = ui.readLine("Girdi: ");

    std::cin.rdbuf(previousIn);
    std::cout.rdbuf(previousOut);
    std::cin.clear();

    CHECK(line == "ğüşiöçİĞÜŞÖÇ");
}

TEST_CASE(ConsoleUI_ReadMenuChoiceHandlesInvalidEmptyLongLinesAndEof) {
    ConsoleUI ui;
    const std::string longGarbage(4096, 'x');
    std::istringstream fakeInput("\nabc\n" + longGarbage + "\n999\n3\n");
    std::ostringstream capturedOut;
    std::streambuf* const previousIn = std::cin.rdbuf(fakeInput.rdbuf());
    std::streambuf* const previousOut = std::cout.rdbuf(capturedOut.rdbuf());
    std::cin.clear();

    const int validChoice = ui.readMenuChoice(1, 5);
    CHECK(validChoice == 3);
    CHECK(!ui.isInputClosed());

    const int eofChoice = ui.readMenuChoice(1, 5);
    CHECK(eofChoice == 1);
    CHECK(ui.isInputClosed());

    std::cin.rdbuf(previousIn);
    std::cout.rdbuf(previousOut);
    std::cin.clear();
}

TEST_CASE(ConsoleUI_ReadLineAndMultilineMarkInputClosedOnEof) {
    ConsoleUI ui;
    std::istringstream fakeInput("int x = 1;\n");
    std::ostringstream capturedOut;
    std::streambuf* const previousIn = std::cin.rdbuf(fakeInput.rdbuf());
    std::streambuf* const previousOut = std::cout.rdbuf(capturedOut.rdbuf());
    std::cin.clear();

    const std::string code = ui.readMultilineCode();
    CHECK(code == "int x = 1;");
    CHECK(ui.isInputClosed());
    CHECK(ui.readLine("Prompt: ").empty());

    std::cin.rdbuf(previousIn);
    std::cout.rdbuf(previousOut);
    std::cin.clear();
}

TEST_CASE(ConsoleUI_ReadMenuChoiceExitsCleanlyOnBadbit) {
    ConsoleUI ui;
    std::istringstream fakeInput("2\n");
    std::ostringstream capturedOut;
    std::streambuf* const previousIn = std::cin.rdbuf(fakeInput.rdbuf());
    std::streambuf* const previousOut = std::cout.rdbuf(capturedOut.rdbuf());
    std::cin.clear();
    std::cin.setstate(std::ios::badbit);

    const int choice = ui.readMenuChoice(0, 5);
    CHECK(choice == 0);
    CHECK(ui.isInputClosed());

    std::cin.rdbuf(previousIn);
    std::cout.rdbuf(previousOut);
    std::cin.clear();
}

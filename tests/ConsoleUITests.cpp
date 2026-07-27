#include "ConsoleUI.h"

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

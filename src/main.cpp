#include "ConsoleUI.h"

int main() {
    ConsoleUI ui;
    ui.printLine("Kodunuzu girin, bitirmek icin BITIR yazin:");
    const std::string code = ui.readMultilineCode();
    ui.printLine("--- Toplanan kod basliyor ---");
    ui.printLine(code);
    ui.printLine("--- Toplanan kod bitti ---");
    return 0;
}

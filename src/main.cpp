#include <iostream>

#include "ConsoleUI.h"

int main() {
    ConsoleUI ui;

    ui.printHeader("CONSOLEUI TEST");
    ui.printLine("0 ile 5 arasinda bir sayi girin (once gecersiz bir deger deneyin):");
    const int choice = ui.readMenuChoice(0, 5);
    ui.printLine("Sectiginiz deger: " + std::to_string(choice));

    const std::string name = ui.readLine("Adiniz: ");
    ui.printLine("Merhaba, " + name + "!");

    return 0;
}

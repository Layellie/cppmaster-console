#include <iostream>

#include "UserProgress.h"

int main() {
    UserProgress progress(5);

    std::cout << "Baslangic XP: " << progress.totalXp() << " (beklenen: 0)\n";

    progress.addXp(10);
    progress.addXp(20);
    std::cout << "Iki ekleme sonrasi XP: " << progress.totalXp() << " (beklenen: 30)\n";

    return 0;
}

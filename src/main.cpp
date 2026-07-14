#include <iostream>

#include "UserProgress.h"

int main() {
    UserProgress progress(5);

    std::cout << "Baslangic durumu (topic 1): "
              << (progress.statusOf(1) == TopicStatus::NotStarted ? "NotStarted (OK)" : "HATA")
              << '\n';

    progress.setStatus(1, TopicStatus::Completed);
    std::cout << "Guncelleme sonrasi (topic 1): "
              << (progress.statusOf(1) == TopicStatus::Completed ? "Completed (OK)" : "HATA")
              << '\n';

    std::cout << "Bilinmeyen topic (999): "
              << (progress.statusOf(999) == TopicStatus::NotStarted ? "NotStarted (OK)" : "HATA")
              << '\n';

    return 0;
}

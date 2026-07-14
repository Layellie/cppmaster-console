#include <iostream>

#include "LessonManager.h"

int main() {
    LessonManager lessons;

    const auto first = lessons.findById(1);
    std::cout << "Konu 1 aciklama bos mu: "
              << (first->explanation.empty() ? "EVET (HATA)" : "HAYIR (OK)") << '\n';
    std::cout << "Konu 1 satir aciklama sayisi: " << first->lineExplanations.size()
              << " (beklenen: 3)\n";
    std::cout << "Konu 1 yaygin hata sayisi: " << first->commonMistakes.size()
              << " (beklenen: 3)\n";

    const auto tenth = lessons.findById(10);
    std::cout << "Konu 10 aciklama bos mu: "
              << (tenth->explanation.empty() ? "EVET (HATA)" : "HAYIR (OK)") << '\n';

    const auto eleventh = lessons.findById(11);
    std::cout << "Konu 11 aciklama bos mu: "
              << (eleventh->explanation.empty() ? "EVET (OK)" : "HAYIR (HATA)") << '\n';

    return 0;
}

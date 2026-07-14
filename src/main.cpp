#include <iostream>

#include "LessonManager.h"

int main() {
    LessonManager lessons;

    std::cout << "Toplam konu sayisi: " << lessons.allLessons().size()
              << " (beklenen: 100)\n";
    std::cout << "Bolum sayisi: " << lessons.sectionCount()
              << " (beklenen: 10)\n";

    const auto first = lessons.findById(1);
    std::cout << "Konu 1 basligi: "
              << (first.has_value() ? first->title : "BULUNAMADI")
              << " (beklenen: cout)\n";

    const auto last = lessons.findById(100);
    std::cout << "Konu 100 basligi: "
              << (last.has_value() ? last->title : "BULUNAMADI")
              << " (beklenen: unique_ptr)\n";

    const auto missing = lessons.findById(999);
    std::cout << "Konu 999: "
              << (missing.has_value() ? "BULUNDU (HATA)" : "bulunamadi (OK)")
              << '\n';

    std::cout << "Bolum 1'deki konu sayisi: "
              << lessons.lessonsInSection(1).size() << " (beklenen: 10)\n";

    return 0;
}

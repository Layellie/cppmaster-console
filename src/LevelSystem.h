#pragma once

#include <string>

struct LevelInfo {
    int level;
    std::string name;
};

[[nodiscard]] inline LevelInfo levelForXp(int xp) {
    struct LevelThreshold {
        int level;
        int xpThreshold;
        const char* name;
    };

    constexpr LevelThreshold kLevels[] = {
        {1, 0, "Başlangıç"},
        {2, 50, "Değişken Ustası"},
        {3, 120, "Koşul Çözücü"},
        {4, 220, "Döngü Ustası"},
        {5, 350, "Dizi Kaşifi"},
        {6, 500, "Fonksiyon Geliştiricisi"},
        {7, 700, "Pointer Öğrencisi"},
        {8, 950, "Nesne Tasarımcısı"},
        {9, 1250, "STL Kullanıcısı"},
        {10, 1600, "C++ Geliştiricisi"},
    };

    LevelInfo result{1, "Başlangıç"};
    for (const LevelThreshold& threshold : kLevels) {
        if (xp >= threshold.xpThreshold) {
            result.level = threshold.level;
            result.name = threshold.name;
        } else {
            break;
        }
    }
    return result;
}

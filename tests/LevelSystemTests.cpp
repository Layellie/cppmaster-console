#include "LevelSystem.h"

#include "TestRunner.h"

TEST_CASE(LevelSystem_AllTenThresholdsAndBoundaries) {
    struct Expected {
        int xp;
        int level;
    };
    constexpr Expected kExpectations[] = {
        {0, 1},    {49, 1},   {50, 2},   {119, 2},  {120, 3},  {219, 3},
        {220, 4},  {349, 4},  {350, 5},  {499, 5},  {500, 6},  {699, 6},
        {700, 7},  {949, 7},  {950, 8},  {1249, 8}, {1250, 9}, {1599, 9},
        {1600, 10}, {5000, 10},
    };
    for (const Expected& expected : kExpectations) {
        CHECK(levelForXp(expected.xp).level == expected.level);
    }
}

TEST_CASE(LevelSystem_NamesMatchKnownValues) {
    CHECK(levelForXp(0).name == "Başlangıç");
    CHECK(levelForXp(50).name == "Değişken Ustası");
    CHECK(levelForXp(1600).name == "C++ Geliştiricisi");
}

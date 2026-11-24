#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "AppContext.h"
#include "ConsoleUI.h"
#include "Enums.h"

struct MenuEntry {
    int number;
    std::string label;
};

struct MenuLayout {
    std::vector<std::string> lines;  // ready to print; may contain escape codes
    std::size_t width = 0;           // widest line, in terminal columns
};

[[nodiscard]] char statusMarker(TopicStatus status);
[[nodiscard]] TextColor colorForStatus(TopicStatus status);
[[nodiscard]] std::string statusBadge(const ConsoleUI& ui, TopicStatus status);
[[nodiscard]] std::string legendEntry(
    const ConsoleUI& ui, TopicStatus status, const std::string& label);
[[nodiscard]] TextColor colorForSuccessPercent(int percent);
[[nodiscard]] std::string settingState(
    const ConsoleUI& ui, const std::string& value, TextColor valueColor);
[[nodiscard]] std::string toggleState(
    const ConsoleUI& ui, bool on, const char* onText, const char* offText);
[[nodiscard]] MenuLayout layOutMenuColumns(
    const ConsoleUI& ui, const std::vector<std::vector<MenuEntry>>& columns);

void showStatisticsScreen(const AppContext& context);
void showAchievementsScreen(const AppContext& context);

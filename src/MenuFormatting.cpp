#include "MenuFormatting.h"

#include <algorithm>
#include <utility>

#include "TextLayout.h"

char statusMarker(TopicStatus status) {
    switch (status) {
        case TopicStatus::NotStarted:
            return ' ';
        case TopicStatus::Learning:
            return '-';
        case TopicStatus::Completed:
            return '+';
        case TopicStatus::Mastered:
            return '*';
    }
    return ' ';
}

TextColor colorForStatus(TopicStatus status) {
    switch (status) {
        case TopicStatus::NotStarted:
            return TextColor::Dim;
        case TopicStatus::Learning:
            return TextColor::Yellow;
        case TopicStatus::Completed:
            return TextColor::Green;
        case TopicStatus::Mastered:
            return TextColor::Magenta;
    }
    return TextColor::Dim;
}

// The "[+]" style badge in front of a topic, coloured by its status.
// The topic list and the legend below it both go through here, so the two
// can never disagree about what a marker looks like or what colour it is.
std::string statusBadge(const ConsoleUI& ui, TopicStatus status) {
    std::string badge = "[";
    badge.push_back(statusMarker(status));
    badge += "]";
    return ui.colorize(badge, colorForStatus(status));
}

std::string legendEntry(const ConsoleUI& ui, TopicStatus status, const std::string& label) {
    return statusBadge(ui, status) + " " + ui.colorize(label, TextColor::Dim);
}

// Traffic-light for the overall success rate: a 40% pass rate should not
// read the same as a 95% one.
TextColor colorForSuccessPercent(int percent) {
    if (percent >= 70) {
        return TextColor::Green;
    }
    if (percent >= 40) {
        return TextColor::Yellow;
    }
    return TextColor::Red;
}

// The "(şu an: X)" suffix in the settings menu. The label recedes and the
// value carries the colour, so the current state of every toggle is
// scannable down the column instead of buried in a sentence.
std::string settingState(const ConsoleUI& ui, const std::string& value, TextColor valueColor) {
    return ui.colorize(" (şu an: ", TextColor::Dim) + ui.colorize(value, valueColor) +
           ui.colorize(")", TextColor::Dim);
}

std::string toggleState(const ConsoleUI& ui, bool on, const char* onText, const char* offText) {
    return settingState(ui, on ? onText : offText, on ? TextColor::Green : TextColor::Dim);
}

// Lays the main menu out side by side instead of as one 11-item list, so the
// XP line, every option and the prompt stay on screen together.
//
// Widths are measured on the plain text: the escape codes around a number
// cost bytes but occupy no columns, so padding against the coloured string
// would indent every column by the length of an escape sequence.
MenuLayout layOutMenuColumns(
    const ConsoleUI& ui, const std::vector<std::vector<MenuEntry>>& columns) {
    constexpr std::size_t kColumnGap = 3;

    std::vector<std::size_t> numberWidths;
    std::vector<std::size_t> columnWidths;
    numberWidths.reserve(columns.size());
    columnWidths.reserve(columns.size());
    std::size_t rowCount = 0;
    for (const std::vector<MenuEntry>& column : columns) {
        std::size_t numberWidth = 1;
        std::size_t labelWidth = 0;
        for (const MenuEntry& entry : column) {
            numberWidth = std::max(numberWidth, std::to_string(entry.number).size());
            labelWidth = std::max(labelWidth, displayWidth(entry.label));
        }
        numberWidths.push_back(numberWidth);
        // "NN" + ". " + label
        columnWidths.push_back(numberWidth + 2 + labelWidth);
        rowCount = std::max(rowCount, column.size());
    }

    // Where each column starts, so a short column (9/10/0) leaves a clean gap
    // rather than pulling the next one left on its empty rows.
    std::vector<std::size_t> columnStarts;
    columnStarts.reserve(columnWidths.size());
    std::size_t offset = 0;
    for (const std::size_t width : columnWidths) {
        columnStarts.push_back(offset);
        offset += width + kColumnGap;
    }

    MenuLayout layout;
    layout.lines.reserve(rowCount);
    for (std::size_t row = 0; row < rowCount; ++row) {
        std::string line;
        std::size_t cursor = 0;  // columns already consumed by `line`
        for (std::size_t column = 0; column < columns.size(); ++column) {
            if (row >= columns[column].size()) {
                continue;
            }
            const MenuEntry& entry = columns[column][row];

            // Right-aligned so the dots line up when "10." meets "9.".
            std::string number = std::to_string(entry.number);
            if (number.size() < numberWidths[column]) {
                number.insert(0, numberWidths[column] - number.size(), ' ');
            }

            line += std::string(columnStarts[column] - cursor, ' ');
            line += ui.colorize(number + ".", TextColor::Green) + " " + entry.label;
            cursor = columnStarts[column] + numberWidths[column] + 2 + displayWidth(entry.label);
        }
        // No trailing padding: it would only invite the terminal to wrap.
        layout.width = std::max(layout.width, cursor);
        layout.lines.push_back(std::move(line));
    }
    return layout;
}

void showStatisticsScreen(const AppContext& context) {
    context.ui.printLine("");
    context.ui.printHeader("İSTATİSTİKLERİM");

    const int topicCount = static_cast<int>(context.lessons.allLessons().size());
    int notStarted = 0;
    int learning = 0;
    int completed = 0;
    int mastered = 0;
    for (int topicId = 1; topicId <= topicCount; ++topicId) {
        switch (context.progress.statusOf(topicId)) {
            case TopicStatus::NotStarted:
                ++notStarted;
                break;
            case TopicStatus::Learning:
                ++learning;
                break;
            case TopicStatus::Completed:
                ++completed;
                break;
            case TopicStatus::Mastered:
                ++mastered;
                break;
        }
    }

    const int totalAnswered = context.progress.totalQuestionsAnswered();
    const int totalCorrect = context.progress.totalCorrectAnswers();
    const double successRatio =
        totalAnswered == 0 ? 0.0
                           : static_cast<double>(totalCorrect) / static_cast<double>(totalAnswered);

    context.ui.printLine(
        "Toplam XP: " +
        context.ui.colorize(std::to_string(context.progress.totalXp()), TextColor::Yellow));
    context.ui.printLine("Toplam çözülen soru: " + std::to_string(totalAnswered));
    context.ui.printLine(
        "Toplam doğru cevap: " +
        context.ui.colorize(std::to_string(totalCorrect), TextColor::Green));
    context.ui.printLine(
        "Toplam yanlış cevap: " +
        context.ui.colorize(std::to_string(totalAnswered - totalCorrect), TextColor::Red));
    const int successPercent = static_cast<int>(successRatio * 100.0);
    const TextColor successColor = colorForSuccessPercent(successPercent);
    context.ui.printLine(
        "Genel başarı oranı: " +
        context.ui.colorize("%" + std::to_string(successPercent), successColor));
    context.ui.printLine("");
    // Same colours as the topic list markers, so a glance at either screen
    // means the same thing.
    context.ui.printLine(
        "Tamamlanan konu sayısı: " +
        context.ui.colorize(std::to_string(completed), colorForStatus(TopicStatus::Completed)));
    context.ui.printLine(
        "Ustalaşılan konu sayısı: " +
        context.ui.colorize(std::to_string(mastered), colorForStatus(TopicStatus::Mastered)));
    context.ui.printLine(
        "Öğrenilmekte olan konu sayısı: " +
        context.ui.colorize(std::to_string(learning), colorForStatus(TopicStatus::Learning)));
    context.ui.printLine(
        "Başlanmamış konu sayısı: " +
        context.ui.colorize(std::to_string(notStarted), colorForStatus(TopicStatus::NotStarted)));
    context.ui.printLine("");
    const std::size_t mistakeCount = context.mistakes.count();
    context.ui.printLine(
        "Kayıtlı yanlış sayısı: " +
        context.ui.colorize(
            std::to_string(mistakeCount), mistakeCount == 0 ? TextColor::Green : TextColor::Red));
    context.ui.printLine("");
}

void showAchievementsScreen(const AppContext& context) {
    context.ui.printLine("");
    context.ui.printHeader("BAŞARIMLAR");
    for (const AchievementId id : allAchievementIds()) {
        const bool unlocked = context.achievements.isUnlocked(id);
        // Unlocked ones are the reward, so they get the colour and the
        // locked ones recede instead of competing for attention.
        const std::string badge = context.ui.colorize(
            unlocked ? "[+]" : "[ ]", unlocked ? TextColor::Yellow : TextColor::Dim);
        const std::string name =
            unlocked ? achievementDisplayName(id)
                     : context.ui.colorize(achievementDisplayName(id), TextColor::Dim);
        std::string line = badge;
        line += " ";
        line += name;
        line += " ";
        line += context.ui.colorize("- " + achievementDescription(id), TextColor::Dim);
        context.ui.printLine(line);
    }
    context.ui.printLine("");
}

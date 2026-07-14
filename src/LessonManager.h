#pragma once

#include <optional>
#include <string>
#include <vector>

#include "Lesson.h"

class LessonManager {
public:
    LessonManager();

    [[nodiscard]] const std::vector<Lesson>& allLessons() const;
    [[nodiscard]] std::vector<Lesson> lessonsInSection(int sectionId) const;
    [[nodiscard]] std::optional<Lesson> findById(int topicId) const;
    [[nodiscard]] std::string sectionTitle(int sectionId) const;
    [[nodiscard]] int sectionCount() const;

private:
    std::vector<Lesson> lessons_;
    std::vector<std::string> sectionTitles_;
};

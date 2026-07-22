#pragma once

#include <optional>
#include <string>
#include <unordered_map>
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
    // Same rationale as QuestionManager's indexes: findById is called on
    // every quiz question (for the `konu`/`ornek` hint commands) and the
    // topic browser walks every lesson, so a linear scan per lookup is
    // avoidable work. Values are indices into lessons_, not iterators.
    void buildIndexes();

    std::vector<Lesson> lessons_;
    std::vector<std::string> sectionTitles_;
    std::unordered_map<int, std::size_t> indexByTopicId_;
    std::unordered_map<int, std::vector<std::size_t>> indicesBySectionId_;
};

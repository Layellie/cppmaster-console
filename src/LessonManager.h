#pragma once

#include <cstddef>
#include <optional>
#include <span>
#include <string>
#include <unordered_map>
#include <vector>

#include "Lesson.h"

class LessonManager {
public:
    LessonManager();

    [[nodiscard]] const std::vector<Lesson>& allLessons() const;
    [[nodiscard]] std::vector<Lesson> lessonsInSection(int sectionId) const;
    [[nodiscard]] std::span<const Lesson> lessonsViewInSection(int sectionId) const noexcept;
    [[nodiscard]] std::optional<Lesson> findById(int topicId) const;
    [[nodiscard]] const Lesson* findPtrById(int topicId) const noexcept;
    [[nodiscard]] std::string sectionTitle(int sectionId) const;
    [[nodiscard]] int sectionCount() const;

private:
    struct SectionRange {
        std::size_t offset = 0;
        std::size_t count = 0;
    };

    // Same rationale as QuestionManager's indexes: findById is called on
    // every quiz question (for the `konu`/`ornek` hint commands) and the
    // topic browser walks every lesson, so a linear scan per lookup is
    // avoidable work. Lessons are authored contiguously by sectionId, so
    // each section is exposed as a zero-copy std::span<const Lesson>.
    void buildIndexes();

    std::vector<Lesson> lessons_;
    std::vector<std::string> sectionTitles_;
    std::unordered_map<int, std::size_t> indexByTopicId_;
    std::unordered_map<int, SectionRange> rangeBySectionId_;
};

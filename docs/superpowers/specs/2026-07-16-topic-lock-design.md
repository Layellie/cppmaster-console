# CppMaster Console — Konu Kilidi Sistemi (Topic Lock) Design (Phase 9)

## Context

Phase 8 added a real Settings system, including a `topicLockEnabled` toggle
stored but never consumed (Phase 9 was always meant to read it). The
original brief's section 12 ("Konu kilidi sistemi") actually asks for two
things, not a hard lock:

> Kullanıcı bütün konulara doğrudan ulaşabilsin fakat önerilen ilerleme
> sırası korunsun. Bir bölümün final sınavını açmak için o bölümdeki
> konuların en az %70 oranında tamamlanması gereksin. Bir sonraki bölüm
> önerilen olarak açılmak için önceki bölüm sınavından en az %70 alınmalıdır.
> Kullanıcı isterse kilit sistemini ayarlardan kapatabilsin.

So: topics are never actually blocked — only (a) a section's own exam is
gated behind 70% topic completion within that section, and (b) the *next*
section is marked "recommended" only once the current section's exam has
been passed at ≥70%. Item (a) is **already implemented** for Section 1
(`kSectionCompletionGateThreshold` in `Application.cpp`) — discovered during
Phase 8's final review. Item (b) has never existed.

## Why this phase is scoped the way it is

Only Section 1 has real lesson content today (Sections 2-10 exist as
id/title/section skeleton entries — Phase 7's own `LessonManagerTests.cpp`
already asserts topics 11-100 have empty `explanation`). A full
cross-section unlock cannot be *exercised end-to-end with real content*
until Section 2's content exists (a later, much larger content-expansion
phase). But the "recommended" advisory marker itself is section-agnostic —
it can be built and verified today by checking whether Section 2's header
line in the topic browser correctly shows/hides an advisory tag, entirely
independent of whether Section 2 has lesson content yet. This phase builds
that general mechanism now, so content-expansion phases don't need to
revisit this code.

## Goal

1. Make the existing Section 1 exam completion-gate obey
   `settings_.topicLockEnabled` (when off, the exam is always accessible
   regardless of completion percentage — restores the pre-lock behavior).
2. Track which section exams have been passed (≥70%), persisted alongside
   the rest of `UserProgress`.
3. In the topic browser, mark any section beyond "the next recommended one"
   with a visible advisory tag — only topics remain always directly
   selectable (per the brief: no hard block), this is purely informational.
4. `settings_.topicLockEnabled = false` disables the advisory tags entirely
   (every section shows as fully recommended) in addition to disabling the
   exam gate.

## Important, deliberate behavior change vs. every prior phase

Phase 8 kept every setting's default reproducing pre-Phase-8 hardcoded
behavior exactly, so no visible output changed unless a user opened
Settings. **This phase cannot do that** — showing the "not yet recommended"
advisory tag on Sections 2-10 by default (since `topicLockEnabled` defaults
to `true`) is the feature itself, not a side effect of a toggle. The topic
browser's default printed output changes starting this phase: Sections 2-10
gain a `(henüz önerilmiyor)` suffix on their header line until Section 1's
exam is passed at ≥70%. This is intentional and must be reflected in this
phase's manual verification transcripts, not treated as a regression to
avoid.

## Data model

New pure-logic header, unit-testable independent of `Application`
(matches the project's existing `LevelSystem.h` header-only-inline-function
pattern):

```cpp
// src/TopicLock.h
#pragma once

[[nodiscard]] inline bool isSectionRecommended(int sectionId, int highestSectionExamPassed) {
    return sectionId <= highestSectionExamPassed + 1;
}

[[nodiscard]] inline bool sectionExamIsUnlocked(
    bool topicLockEnabled, double completionRatio, double gateThreshold) {
    return !topicLockEnabled || completionRatio >= gateThreshold;
}
```

`UserProgress` gains one new field, following the exact existing pattern
(a `record*` mutator for gameplay-time updates, a raw `set*` for
`ProgressManager`'s load path — matching `recordStreak`/`setStreakCounters`):

```cpp
[[nodiscard]] int highestSectionExamPassed() const;
void recordSectionExamPassed(int sectionId);  // no-op if sectionId <= current value
void setHighestSectionExamPassed(int value);  // raw setter, used only by ProgressManager::load
```

`ProgressManager` gains one new persisted line, `highest_section_exam_passed N`,
parsed with the same `tryParseInt`/corrupt-on-failure contract as every
other field.

## Wiring into `Application`

- `runSectionExam()`: the existing gate check
  `if (completionRatio < kSectionCompletionGateThreshold)` becomes
  `if (!sectionExamIsUnlocked(settings_.topicLockEnabled, completionRatio, kSectionCompletionGateThreshold))`.
  When the exam is passed (`scoreRatio >= kExamPassThreshold`), call
  `progress_.recordSectionExamPassed(kExamSectionId)` before saving progress.
  Passing/failing is recorded regardless of whether `topicLockEnabled` is
  currently on — the toggle only affects the gate and the advisory display,
  not whether the underlying fact gets tracked.
- `showTopicBrowser()`: each section's header line gets
  `" (henüz önerilmiyor)"` appended when
  `settings_.topicLockEnabled && !isSectionRecommended(sectionId, progress_.highestSectionExamPassed())`.
  Topic selection itself is completely unchanged — every topic remains
  selectable via the same numeric prompt, matching the brief's "no hard
  block" requirement.

## Testing / verification for this phase

- `tests/TopicLockTests.cpp`: `isSectionRecommended` boundary cases (section
  1 is always recommended at `highestSectionExamPassed == 0`; section ==
  highest+1 is recommended; section > highest+1 is not); `sectionExamIsUnlocked`
  cases (disabled lock is always unlocked regardless of ratio; enabled lock
  respects the threshold, including the exact boundary value).
- `tests/UserProgressTests.cpp`: `recordSectionExamPassed` only increases the
  stored value (recording a lower or equal section id is a no-op).
- `tests/ProgressManagerTests.cpp`: extend the existing round-trip test to
  cover `highestSectionExamPassed`; missing-file test confirms default `0`.
- Manual piped-transcript verification (`Application`/`ConsoleUI` stay out
  of unit-test scope): a fresh-progress topic browser view showing the new
  `(henüz önerilmiyor)` tag on Sections 2-10; passing Section 1's exam and
  re-opening the topic browser to confirm Section 2's tag disappears;
  toggling `topicLockEnabled` off via Settings and confirming the tags
  disappear immediately (before any exam is passed) and the exam gate no
  longer blocks a below-70%-completion attempt.

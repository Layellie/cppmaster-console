# CppMaster Console — Persistence + Review Loop (Phase 4) Design

## Context

Sub-project 4 of the decomposition: Foundation → Static lesson + quiz core →
Richer question types → **Persistence + review loop** → meta systems →
dynamic generation → polish. Phases 1-3 are complete, reviewed, and merged.
Right now `UserProgress` is in-memory only — every restart loses all XP and
topic status, and menu options 3 ("Günlük Tekrar"), 4 ("Hatalarımı Çöz"), 7
("İstatistiklerim"), and 10 ("İlerlemeyi Sıfırla") still show Foundation's
honest "not yet available" message.

Scoped autonomously per the user's standing instruction; recorded here for
transparency, same as phases 2-3.

## Goal

Make progress survive a restart, track wrong answers durably, and give the
four still-placeholder menu options real, honest behavior built on that
persisted data.

## Scope cuts (deliberate, not oversights)

- **"Hatalarımı Çöz" is one flow, not the product spec's 5-option submenu.**
  The spec envisions "Son yanlışlarım / En çok hata yaptığım konular /
  Sadece kod soruları / Sadece boşluk doldurma / Tüm yanlışları çöz." This
  phase implements the equivalent of "Tüm yanlışları çöz" only — every
  recorded mistake, oldest-last-wrong-first. The other four filters are
  presentation variants over the same underlying data; adding a submenu for
  them is a cheap follow-up once the core mechanism (this phase) exists, not
  something worth blocking this phase on.
- **"Günlük Tekrar" has no interval/priority scheduling.** The spec's full
  design (5-tier priority: recent mistakes → stale topics → weak topics →
  new topics → random reinforcement, with doubling/shortening review
  intervals) needs per-topic recency and success-rate tracking this phase
  doesn't build. Instead: up to 20 recorded mistakes, oldest-last-wrong
  first — the single highest-value tier of the spec's priority list,
  honestly presented as exactly that (if there are no mistakes yet, the
  screen says so rather than inventing filler questions).
- **"İstatistiklerim" is an MVP subset**, not the spec's full ~17-line
  report. This phase shows: total XP, total questions answered, total
  correct/wrong, overall success rate, per-status topic counts, and the
  mistake count. Streaks, 7-day activity, strongest/weakest-5 topics, and
  per-question-type breakdowns are meta-systems-phase material — they need
  data this phase doesn't track yet (a longest-streak counter, daily
  timestamps, per-topic success rates).
- **No achievements, no leveling, no session-length tracking.** Explicitly
  the meta-systems phase's job per the original decomposition.
- **Corruption recovery matches the spec's literal naming**: a malformed
  `data/progress.txt` is copied to `data/progress_corrupted_backup.txt`
  (mistakes: `data/mistakes_corrupted_backup.txt`) and the app continues
  with a fresh, empty state — no attempt at partial recovery or line-level
  repair. Each new corruption event overwrites the previous backup; the
  spec names one backup file, not a versioned history.
- **Dates are Unix epoch seconds, not calendar strings.** `std::chrono`
  internally (`system_clock::time_point`), serialized via
  `to_time_t`/`from_time_t` — this sidesteps timezone/locale/date-parsing
  entirely while still meeting the spec's "use chrono, not an external date
  library" instruction.

## New classes

### `ProgressManager` (stateless — no member data, just load/save)

```cpp
struct ProgressLoadResult {
    UserProgress progress;
    bool wasCorrupted;
};

class ProgressManager {
public:
    ProgressLoadResult load(
        const std::string& filePath, const std::string& backupPath, int topicCount) const;
    void save(const UserProgress& progress, const std::string& filePath, int topicCount) const;
};
```

File format (`data/progress.txt`), one record per line, whitespace-separated:
```
xp 135
answered 42
correct 30
topic 1 Completed
topic 2 NotStarted
...
```
`topic` lines only need to appear for topics that aren't `NotStarted`
(the default) — but `save` writes all `topicCount` of them for simplicity
and human-readability; `load` doesn't require every topic to be present
(missing ones stay `NotStarted`, matching `UserProgress`'s existing
default). Any line that doesn't parse (wrong field count, non-numeric where
a number is expected, an unrecognized status name, an unrecognized first
token) marks the whole file corrupt.

### `UserProgress` additions

```cpp
[[nodiscard]] int totalQuestionsAnswered() const;
[[nodiscard]] int totalCorrectAnswers() const;
void recordAnswer(bool correct);  // always increments answered; increments correct too if true
void setAnsweredCounters(int totalAnswered, int totalCorrect);  // load-time only
```
(`statusOf`/`setStatus`/`totalXp`/`addXp` unchanged from phases 1-2.)

### `MistakeRecord` / `MistakeTracker`

```cpp
struct MistakeRecord {
    int questionId;
    std::chrono::system_clock::time_point firstWrongAt;
    std::chrono::system_clock::time_point lastWrongAt;
    int wrongCount;
    int correctAfterWrongCount;
};

class MistakeTracker {
public:
    void recordWrong(int questionId);
    void recordCorrectRetry(int questionId);  // no-op if no record exists for this id
    [[nodiscard]] bool hasMistake(int questionId) const;
    [[nodiscard]] std::vector<MistakeRecord> allMistakesOldestFirst() const;

    bool loadFromFile(const std::string& filePath, const std::string& backupPath);  // returns wasCorrupted
    void saveToFile(const std::string& filePath) const;
};
```

A record, once created by `recordWrong`, is never deleted — per the
product spec ("bir yanlış soru daha sonra doğru cevaplanırsa tamamen
silinmesin"), `recordCorrectRetry` only increments
`correctAfterWrongCount` and leaves the rest of the record (including its
continued presence in "Hatalarımı Çöz") intact. There is no
"resolved, stop showing this" state in this phase — that filtering is one
of the submenu options explicitly deferred above.

File format (`data/mistakes.txt`), one record per line:
```
mistake <questionId> <firstWrongEpochSeconds> <lastWrongEpochSeconds> <wrongCount> <correctAfterWrongCount>
```

### `QuestionManager` addition

```cpp
[[nodiscard]] std::optional<Question> findById(int questionId) const;
```
Needed so "Hatalarımı Çöz"/"Günlük Tekrar" can turn a `MistakeRecord`
(which only stores a `questionId`) back into a full `Question` to re-ask.
Mirrors `LessonManager::findById`'s existing pattern exactly.

## `Application` refactor: a shared `askOneQuestion`

Phases 2-3 built one place that asks a question and shows feedback:
`runTopicQuiz`'s loop body. This phase needs that same logic from three
call sites (`runTopicQuiz`, the mistake-review flow, the daily-review flow),
so it's extracted into:

```cpp
AnswerResult Application::askOneQuestion(const Question& question);
```

This performs exactly what `runTopicQuiz`'s loop body already did (render
per type, read the answer, evaluate, print correct/wrong feedback) **plus**
three new side effects every phase-4 question needs regardless of which
flow asked it: `progress_.recordAnswer(result.correct)`, mistake-tracking
(`mistakes_.recordWrong`/`recordCorrectRetry` as appropriate), and an
immediate save of both `data/progress.txt` and `data/mistakes.txt` — this
directly satisfies the product spec's "her doğru veya yanlış cevap
sonrasında önemli ilerleme bilgileri kaydedilsin" (save after every answer,
not just at session end), and costs nothing noticeable for a local text
file this small.

This is a genuine behavior-preserving refactor of already-shipped,
already-reviewed code (the same category of risk phase 3's `QuizEngine`
restructuring was) and needs the same explicit reviewer attention: does
`runTopicQuiz`'s visible output (prompts, options, feedback, scoring)
change at all for a caller who never triggers a mistake? It must not.

## New `Application` methods

- `showMistakeReview()` — menu option 4. Empty state: honest "no mistakes
  yet" message. Otherwise: lists the count, then asks every recorded
  mistake via the shared `runMistakeQuestions` helper (below), ending in a
  session summary (correct/total, XP earned).
- `runDailyReview()` — menu option 3. Same empty-state message (tailored
  wording), same mechanism, capped at 20 via `std::vector::resize`.
- `runMistakeQuestions(const std::vector<MistakeRecord>&)` — shared helper
  behind both of the above: looks up each mistake's `Question` via
  `QuestionManager::findById` (skipping — not crashing on — an id that
  somehow isn't found, a defensive check against future content changes
  outliving old mistake records), asks it via `askOneQuestion`, accumulates
  XP/correct count, and prints the summary.
- `showStatistics()` — menu option 7. The MVP metrics listed above.
- `resetProgress()` — menu option 10. Prompts for an exact `evet`
  confirmation (anything else cancels, printed as "İptal edildi."); on
  confirmation, replaces `progress_`/`mistakes_` with fresh empty instances
  and immediately persists both.

Menu option 2 ("Hızlı Test") is untouched — still honestly "not yet
available"; it isn't in this phase's scope.

## Testing / verification for this phase

Same approach as phases 1-3 — no test framework yet. New pure-logic pieces
(`ProgressManager`, `MistakeTracker`, the `UserProgress` additions) are
verified via temporary `main.cpp` harnesses, same technique as every prior
phase. The refactor of `runTopicQuiz` needs explicit before/after output
comparison, not just "it still runs." The actual persistence claim —
"progress survives a restart" — can only be verified by running the built
executable **twice** as two separate process invocations (do a topic quiz
in the first run, exit, then start a second run and confirm the topic
browser shows the earned status marker and the main menu shows the correct
`Toplam XP`), which the final task's manual verification does explicitly.

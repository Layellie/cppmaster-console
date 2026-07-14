# CppMaster Console — Meta Systems (Phase 5) Design

## Context

Sub-project 5 of the decomposition: Foundation → Static lesson + quiz core
→ Richer question types → Persistence + review loop → **Meta systems** →
dynamic generation → polish. Phases 1-4 are complete, reviewed, and merged.
Menu options 6 ("Seviye Sınavı") and 8 ("Başarımlar") still show the
honest "not yet available" message; XP has no levels attached to it yet.

Scoped autonomously per the user's standing instruction; recorded here for
transparency, same as phases 2-4.

## Goal

Add a 10-level XP ladder with celebration messages, a reachable subset of
achievements, and a real section exam for Bölüm 1 (the only section with
authored content) gated behind a completion threshold.

## Scope cuts (deliberate, not oversights)

- **No final exam.** The product spec's "100-question, every-topic" final
  exam is impossible to build honestly: only topics 1-10 (Bölüm 1) have any
  lesson content or questions. Topics 11-100 are still empty. A final exam
  is meaningless until later phases add content for the other 9 sections —
  this phase does not fake one.
- **No adaptive difficulty.** True adaptive question selection (easier on a
  wrong streak, harder on a right streak) needs a large-enough question
  pool to select *from* per topic. Most topics have exactly 6-9 hand-authored
  questions; there's nothing meaningful to adapt into. This is explicitly
  the dynamic-question-generation phase's job (phase 6 in the roadmap),
  once a much larger pool exists — not this one's.
- **Section exam covers only Bölüm 1**, because Bölüm 1 = topics 1-10 is the
  *only* section with any authored questions (72 of them, spanning all 9
  built question types). Selecting "Seviye Sınavı" for any other section
  honestly says there's nothing to examine yet.
- **The exam's 20 questions are a fixed, deterministic list — not randomly
  sampled.** True randomization would break this project's established
  verification method (exact piped-input sequences with hand-computed
  expected output). Introducing a seeded RNG, testing it deterministically,
  and building the infrastructure to vary exam content is real scope that
  belongs with the dynamic-generation phase, where randomization is already
  a first-class concern. For now: the same 20 questions, every time,
  chosen to exercise all 9 question types without exhausting the scarcest
  ones (only 2 questions exist for `CompleteLine`/`PredictOutput`/
  `FindError`/`FixCode`/`OrderCode`/`WriteCode` each).
- **The exam's type distribution isn't the product spec's literal
  "5/3/3/3/2/2/2" split**, because that split assumes 3 `PredictOutput`
  questions exist and only 2 do (among other mismatches against a 9-type
  question bank the spec's original 7-type list didn't anticipate). This
  phase uses 4 MultipleChoice + 3 TrueFalse + 3 FillBlank + 2 each of
  CompleteLine/PredictOutput/FindError/FixCode + 1 each of OrderCode/
  WriteCode = 20, chosen to showcase every type that exists without
  requiring content this project hasn't authored yet.
- **No per-topic strongest/weakest breakdown or timing in the exam
  report** — the spec's fuller report (section-based, per-topic, timed)
  needs data (per-topic accuracy during a single exam pass, elapsed time)
  this phase doesn't track. The report here is: score, percentage, XP,
  pass/fail — matching this project's established "MVP subset first"
  pattern from `İstatistiklerim` in phase 4.
- **Achievements are a reachable 7 of the product spec's 12.** The other 5
  (`Döngü Ustası`, `Pointer Cesuru`, `STL Kaşifi`, `Dosya Ustası`,
  `C++ Geliştiricisi`) require topic content (loops, pointers, STL, file
  I/O) or full 100-topic completion that doesn't exist yet — they cannot be
  unlocked honestly and are deferred until the relevant content lands. The
  7 built here: `İlk Adım`, `Hatasız Beşli`, `Seri Ustası`, `Kod Yazarı`,
  `Hata Avcısı`, `Pes Etmeyen`, `Mükemmel Sınav`.
- **`Kod Yazarı` ("10 kod yazma sorusu çözdün") and `Hata Avcısı` ("25
  hatalı kodu düzelttin") count cumulative correct answers, not distinct
  questions.** Only 2 `WriteCode` questions and 4 `FindError`/`FixCode`
  questions exist total — reaching the spec's literal thresholds by
  solving *distinct* questions is impossible. Counting every correct
  answer (including repeat correct answers to the same question on
  retry, e.g. via "Hatalarımı Çöz") makes both achievements genuinely
  reachable through normal engaged use, which matches the achievements'
  evident intent (reward volume of practice) better than a literal,
  currently-unsatisfiable reading would.
- **Level XP thresholds are invented, not specified.** The product spec
  names 10 level titles but never gives XP thresholds. Chosen here to be
  reachable through normal engaged play against the current ~990 XP
  available from all 72 questions once each, plus ~300 more from a
  perfect exam, plus additional XP from retries: 0, 50, 120, 220, 350,
  500, 700, 950, 1250, 1600.

## New/changed files

```
src/UserProgress.h / .cpp       (modified — streak + typed correct-answer counters)
src/ProgressManager.cpp         (modified — persist the new counters)
src/LevelSystem.h               (new — pure functions, no class/state/persistence)
src/AchievementTracker.h / .cpp (new — unlock-set tracking + persistence)
src/MistakeTracker.h / .cpp     (modified — add findMistake, needed by achievement checks)
src/Application.h / .cpp        (modified — leveling, achievements, exam wiring)
```

## `UserProgress` additions

```cpp
[[nodiscard]] int currentStreak() const;
[[nodiscard]] int longestStreak() const;
void recordStreak(bool correct);  // increments/resets current; longest is a running max

[[nodiscard]] int writeCodeCorrectCount() const;
[[nodiscard]] int errorFixCorrectCount() const;  // FindError + FixCode combined
void recordTypedCorrectAnswer(QuestionType type);  // no-op for any other type

void setStreakCounters(int current, int longest);           // load-time only
void setTypedCorrectCounters(int writeCode, int errorFix);   // load-time only
```

`recordStreak`/`recordTypedCorrectAnswer` are both called once per question
from `askOneQuestion`, alongside the existing `recordAnswer` call — same
pattern as phase 4 established.

`progress.txt` gains four new lines (`streak_current`, `streak_longest`,
`writecode_correct`, `errorfix_correct`), following the exact same
`ProgressManager` parsing/corruption rules already in place: any of these
missing from an old file just default to 0 (not corruption) since they're
read the same way `xp`/`answered`/`correct` already are — a file written by
phase 4's `ProgressManager` (with none of these lines) loads cleanly under
phase 5's parser with all four defaulting to 0.

## `LevelSystem.h` (stateless, header-only)

```cpp
struct LevelInfo {
    int level;
    std::string name;
};

[[nodiscard]] LevelInfo levelForXp(int xp);
```

Ten fixed level/threshold pairs (0 Başlangıç, 50 Değişken Ustası, 120 Koşul
Çözücü, 220 Döngü Ustası, 350 Dizi Kaşifi, 500 Fonksiyon Geliştiricisi, 700
Pointer Öğrencisi, 950 Nesne Tasarımcısı, 1250 STL Kullanıcısı, 1600 C++
Geliştiricisi) — the highest threshold not exceeding `xp` wins.

## `Application` leveling wiring

A new private helper:
```cpp
void awardXpAndCheckLevelUp(int amount);
```
replaces the three existing `progress_.addXp(sessionXp);` call sites
(`runTopicQuiz`, `runMistakeQuestions`, and the new exam flow): it captures
`levelForXp` before and after the add, and if the level number increased,
prints a celebration line naming the new level. This is the same class of
small, deliberate change to already-shipped code phases 3-4 made (adding a
new call site, not altering what already exists) and needs the same
regression discipline: existing XP/score text must not change, only gain
one new optional trailing line when a level threshold is crossed.

The main menu's `"Toplam XP: N"` line gains a second line: `"Seviye: <name>
(Seviye <n>)"`.

## `AchievementTracker`

```cpp
enum class AchievementId {
    FirstStep, FlawlessFive, StreakMaster, CodeWriter, BugHunter, NeverGiveUp, PerfectExam,
};

class AchievementTracker {
public:
    bool unlock(AchievementId id);  // returns true only the first time this id is unlocked
    [[nodiscard]] bool isUnlocked(AchievementId id) const;
    [[nodiscard]] std::vector<AchievementId> allUnlocked() const;

    bool loadFromFile(const std::string& filePath, const std::string& backupPath);
    void saveToFile(const std::string& filePath) const;

private:
    std::unordered_set<int> unlockedIds_;
};
```

`data/achievements.txt`: one `achievement <Name>` line per unlocked id
(name-based, matching the readable-text convention `progress.txt`/
`mistakes.txt` already use), same corruption-safe load/save pattern as
every other data file in this project (an unrecognized line marks the
whole file corrupt → backup → fresh empty state; a missing file is not
corruption).

## `Application` achievement wiring

A new private method, called from `askOneQuestion` right after the
existing mistake-tracking block:
```cpp
void checkAchievements(const Question& question, bool correct);
```
Checks (in order, all reachable from state `askOneQuestion` already has or
that `UserProgress`/`MistakeTracker` already expose after this phase's
additions):
- `FirstStep`: `progress_.totalCorrectAnswers() == 1` (first-ever correct
  answer, checked *after* this question's `recordAnswer` call).
- `FlawlessFive` / `StreakMaster`: `progress_.currentStreak() == 5` / `== 10`
  (checked at the exact moment the streak reaches that count, not "≥", so
  it fires once per streak run rather than every question after).
- `CodeWriter`: `progress_.writeCodeCorrectCount() >= 10`.
- `BugHunter`: `progress_.errorFixCorrectCount() >= 25`.
- `NeverGiveUp`: only when `correct` and this question was a recorded
  mistake being retried — look up the record via the new
  `MistakeTracker::findMistake(question.id)` (added to `MistakeTracker` in
  this phase) and check `wrongCount >= 5`.

Any newly-unlocked id (an `unlock()` call that returns `true`) prints a
notification block naming the achievement and its description, then saves
`data/achievements.txt` immediately (same "save after every meaningful
event" discipline as everything else in this project).

`Mükemmel Sınav`/`PerfectExam` is **not** checked here — it's a session-level
condition (100% on the whole exam), checked once at the end of the exam
flow, not per-question.

Menu option 8 ("Başarımlar") lists all 7 achievements with a
`[+]`/`[ ]` marker (reusing the topic browser's existing bracket-marker
visual language rather than introducing a new symbol) and its description.

## Section exam ("Seviye Sınavı")

A fixed, hardcoded list of 20 question ids (see the plan for the exact
ids) drawn entirely from the already-existing 72-question bank for topics
1-10 — no new question content is authored this phase.

**Prerequisite gate:** before running the exam, count how many of topics
1-10 are `Completed` or `Mastered` via `progress_.statusOf`; if fewer than
70% (7 of 10), print an honest message stating the current completion
count and refuse to start the exam — matching the product spec's
completion-gate requirement.

**Exam flow:** reuses `askOneQuestion` question-by-question (so exam
answers feed the same mistake-tracking, streak, and achievement logic as
every other quiz flow — no parallel bookkeeping path to keep in sync),
accumulates correct count/XP, then reports `Doğru: X/20`, `Başarı: %P`,
`Kazanılan XP: N`, and `Sonuç: GEÇTİN` (≥70%) or `KALDIN` (<70%) — mirroring
the product spec's report format at the fields this phase actually tracks.
On a perfect (100%) score, unlocks `PerfectExam` before the report prints.
XP is added via `awardXpAndCheckLevelUp` at the end, same as every other
flow.

## Testing / verification for this phase

Same approach as phases 1-4 — no test framework yet. `UserProgress`/
`LevelSystem`/`AchievementTracker` are verified via temporary `main.cpp`
harnesses. The exam and achievement flows are verified via piped-input
sessions with hand-computed expected scores (all 20 exam question ids'
correct answers are already known from phases 2-3's own verification
work, so the exact expected exam report can be computed in advance, not
guessed).

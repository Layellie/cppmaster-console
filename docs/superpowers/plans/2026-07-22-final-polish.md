# Plan — Phase 25: Kalan Cila (Final Polish)

Spec: `docs/superpowers/specs/2026-07-22-final-polish-design.md`

Base commit (before Task 1): `e1e8d38` (Phase 24 close-out, roadmap range fix)

## Task 1 — Settings fields

- `src/Settings.h`: add `bool colorEnabled = true;`,
  `bool audioAlertEnabled = false;`, `int quickTestQuestionCount = 5;`.
- `src/SettingsManager.cpp`: `load()` gains 3 new `else if` branches
  (`color_enabled`, `audio_alert` parsed as bool; `quick_test_count`
  parsed as int, same `tryParseBool`/`tryParseInt` helpers already used);
  `save()` gains 3 new corresponding lines.
- `tests/SettingsManagerTests.cpp`: extend
  `SettingsManager_MissingFileLoadsDefaultsNotCorrupted` and
  `SettingsManager_SaveThenLoadRoundTripsAllFields` to cover the 3 new
  fields; add a new
  `SettingsManager_OldFormatFileWithoutNewFieldsLoadsNewFieldDefaults`
  test that hand-writes a file containing only the original 5 keys and
  confirms it loads as not-corrupted with the 3 new fields at their
  defaults.
- Build, run full suite, confirm the new/extended tests pass, commit.

## Task 2 — ConsoleUI color and audio-alert support

- `src/ConsoleUI.h`: add `setColorEnabled(bool)`,
  `setAudioAlertEnabled(bool)`, `printSuccess(const std::string&) const`,
  `printError(const std::string&) const`, `printHighlight(const std::string&) const`,
  `playAlertSound() const`. Two new private bool members
  (`colorEnabled_`, `audioAlertEnabled_`, both default `false` until
  `Application` sets them from `Settings` after load) plus a
  `colorSupported_` member set in the constructor.
- `src/ConsoleUI.cpp`: constructor attempts
  `SetConsoleMode(..., ENABLE_VIRTUAL_TERMINAL_PROCESSING)` on the stdout
  handle (Windows only, guarded by `#ifdef _WIN32` like the existing
  UTF-8 code page calls); sets `colorSupported_` from the call's success.
  On non-Windows, `colorSupported_ = true` unconditionally. The 3 print
  methods emit `\x1b[32m`/`\x1b[31m`/`\x1b[33m` + text + `\x1b[0m` only
  when both `colorEnabled_ && colorSupported_`, otherwise fall back to
  plain `printLine`-equivalent output. `playAlertSound()` writes `'\a'`
  and flushes, only when `audioAlertEnabled_`.
- Build, run full suite (no new tests for this class, per the spec's
  established-precedent decision), commit.

## Task 3 — Application wiring: settings menu, color/beep call sites, Quick Test count

- Constructor: after `settingsManager_.load(...)`, call
  `ui_.setColorEnabled(settings_.colorEnabled)` and
  `ui_.setAudioAlertEnabled(settings_.audioAlertEnabled)`.
- `runQuickTest()`: `constexpr int kQuickTestQuestionCount = 5;` becomes
  `const int kQuickTestQuestionCount = settings_.quickTestQuestionCount;`.
- `askOneQuestion()`: correct branch uses `ui_.printSuccess(...)` instead
  of `ui_.printLine(...)` for the "Doğru!" line; wrong branch uses
  `ui_.printError(...)` for "Yanlış cevap." and calls
  `ui_.playAlertSound()`.
- `runCodeExercise()`: same `printSuccess` swap for its "Doğru!" line
  (mirrors `askOneQuestion`'s correct-answer feedback).
- `checkAchievements()` (both call sites in `runSectionExam`/`runFinalExam`
  too) and `awardXpAndCheckLevelUp()`: "Yeni başarım kazandın: ..." and
  "Tebrikler! Yeni seviyeye ulaştın: ..." lines use `ui_.printHighlight(...)`.
- `showSettingsMenu()`: add menu entries 8 (color toggle), 9 (audio alert
  toggle), 10 (Quick Test question count, prompts 1-20 via
  `ui_.readMenuChoice(1, 20)`); extend `ui_.readMenuChoice(0, 7)` to
  `(0, 10)`; each toggle also calls the corresponding `ui_.set*Enabled`
  so the change takes effect immediately without restart.
- Build, run full suite, confirm no regressions, commit.

## Task 4 — First-launch skill-level selection

- `Application.h`: new private method `runFirstLaunchSkillSelection()`;
  new private member `bool isFirstLaunch_ = false;`.
- Constructor: before calling `progressManager_.load(...)`, set
  `isFirstLaunch_ = !std::filesystem::exists(kProgressFilePath);`.
- `run()`: if `isFirstLaunch_`, call `runFirstLaunchSkillSelection()`
  once before entering the main menu loop.
- `runFirstLaunchSkillSelection()`: prints a welcome header, offers 3
  choices, adds 0/120/350 XP via `progress_.addXp(...)` per the spec,
  prints the resulting level via `levelForXp`, explicitly states that
  topic/section state is unaffected, saves progress.
- Build, run full suite, manually verify end-to-end: back up
  `data/progress.txt` if present, delete it, run `CppMasterConsole.exe`,
  confirm the skill-selection screen appears and setting XP works,
  confirm a second run does **not** show it again, restore the backed-up
  progress file afterward (do not leave the developer's own progress
  reset).
- Commit.

## Task 5 — Roadmap close-out (this is the LAST phase)

- `docs/superpowers/roadmap.md`: strike through the "Ayarlar" gap bullet's
  remaining deferred fields (renk aç/kapa, sesli uyarı, varsayılan sınav
  soru sayısı) and the "No first-launch skill-level selection screen, no
  ANSI color system" gap bullet, both with resolution notes. Add the
  Phase 25 COMPLETE summary bullet. Update the Status section to state
  the roadmap is now fully complete (all 25 phases done) — this is the
  final phase, so there is no "next phase" to point at.
- Update `.superpowers/sdd/progress.md` (ledger) with Task 1-5 entries and
  a phase-close entry, plus a final "roadmap complete" note.

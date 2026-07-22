# Design Spec — Phase 25: Kalan Cila (Final Polish)

## Problem

This is the last phase in the roadmap. Three items remain from the original
spec, all deferred from earlier phases since they were out of scope there:

1. No first-launch skill-level selection screen.
2. No ANSI color system.
3. Three settings fields were deferred from Phase 8's settings menu: renk
   aç/kapa (color on/off), sesli uyarı (audio alert), and varsayılan sınav
   soru sayısı (default "exam" question count).

## Scoping decisions (judgment calls made explicit, since the roadmap only
## states these items tersely and there is no further user-supplied detail)

- **"Varsayılan sınav soru sayısı"**: read literally this would mean the
  section/final exam question counts, but those are structurally fixed by
  Phase 22's design — each section exam covers all of that section's topics
  exactly twice (20 questions), and the final exam covers all 100 topics
  exactly once (100 questions); making these arbitrarily resizable would
  break that "covers every topic" invariant and require touching
  well-tested Phase 22 code for a cosmetic settings field. The Ayarlar menu
  already has a distinct, separate "günlük soru hedefi" (daily review
  count) setting, confirming "sınav" here is used loosely for "test/quiz",
  not strictly the formal exam. This spec implements it as the **Quick
  Test** (`Application::runQuickTest`) question count instead — currently
  a hardcoded `constexpr int kQuickTestQuestionCount = 5`, becoming a
  configurable `Settings::quickTestQuestionCount` (default 5, unchanged
  behavior until a user opts to change it). Section/final exam sizes are
  untouched.
- **Audio alert**: implemented as the console bell character (`'\a'`),
  played on a wrong answer only (the clearest reading of "uyarı" =
  warning/alert — a notification that something needs attention, not a
  celebratory sound). Default **off** (an unsolicited beep on every mistake
  would be an annoying default for a learning app).
- **Color**: default **on**. Windows requires
  `ENABLE_VIRTUAL_TERMINAL_PROCESSING` to render ANSI escape codes; if
  enabling that mode fails (older terminal), color output is silently
  suppressed regardless of the setting, rather than printing garbled
  escape sequences. Applied to: correct-answer feedback (green), wrong-
  answer feedback (red), achievement/level-up messages (yellow). Existing
  headers/menus stay plain — recoloring the entire UI is a much larger,
  riskier surface change than this phase's actual ask.
- **Skill-level selection**: triggers once, on the very first launch
  (detected by `data/progress.txt` not existing yet, checked *before* the
  constructor's normal load call). Offers 3 choices (yeni başlıyorum / biraz
  bilgim var / deneyimliyim) that set a **starting XP** value only (0 / 120
  / 350 — the level-3 and level-5 thresholds from `LevelSystem.h`).
  Deliberately does **not** touch topic completion status or section locks
  — fabricating "completed" topics the user never studied would corrupt
  their real progress tracking and interact unpredictably with
  achievements. The screen explicitly tells the user this, so the scope
  limitation is visible, not silently surprising.

## Scope

1. `Settings.h` / `SettingsManager.{h,cpp}`: add `colorEnabled` (default
   `true`), `audioAlertEnabled` (default `false`),
   `quickTestQuestionCount` (default `5`) — new record types
   `color_enabled` / `audio_alert` / `quick_test_count` in the save/load
   format. Old settings files without these keys must continue to load
   as **not corrupted**, with the new fields at their defaults (the
   existing load loop's structure already gives this for free — verified
   by a new explicit test, not just assumed).
2. `ConsoleUI.{h,cpp}`: `setColorEnabled(bool)`, `setAudioAlertEnabled(bool)`,
   `printSuccess(text)` (green), `printError(text)` (red),
   `printHighlight(text)` (yellow), `playAlertSound()` (bell character,
   no-op if disabled). Constructor attempts to enable
   `ENABLE_VIRTUAL_TERMINAL_PROCESSING` on Windows; success/failure gates
   whether color output is ever emitted, independent of the setting.
3. `Application.{h,cpp}`:
   - Constructor: detect first launch before loading progress; call
     `ui_.setColorEnabled(settings_.colorEnabled)` and
     `ui_.setAudioAlertEnabled(settings_.audioAlertEnabled)` after settings
     load.
   - New `runFirstLaunchSkillSelection()`, called from `run()` before the
     main loop, only when this is the first launch.
   - `runQuickTest()`: replace the hardcoded question count with
     `settings_.quickTestQuestionCount`.
   - Recolor the existing correct/wrong feedback in `askOneQuestion` and
     `runCodeExercise`, and the achievement/level-up messages in
     `checkAchievements` (both call sites) and `awardXpAndCheckLevelUp`.
     Play the alert sound on wrong answers in `askOneQuestion`.
   - `showSettingsMenu()`: three new menu entries (8: color, 9: audio
     alert, 10: Quick Test question count 1-20), extending the choice
     range from `(0,7)` to `(0,10)`.
4. Tests: extend `SettingsManagerTests.cpp` for the 3 new fields
   (defaults, round-trip, and a new explicit backward-compatibility test
   using a hand-written old-format file). No new tests for `ConsoleUI` or
   `Application` — neither has ever had unit tests in this codebase (both
   are console-I/O-bound orchestration code, verified via manual
   end-to-end runs in every prior phase's ledger entry, not unit tests);
   this phase follows that same established precedent. Manual end-to-end
   verification: delete `data/progress.txt` and run the real console app
   to confirm the first-launch screen appears once and not again, confirm
   colored/beeped feedback, confirm the 3 new settings entries work and
   persist.
5. `docs/superpowers/roadmap.md`: mark Phase 25 (and, since it's the last
   phase, the roadmap as a whole) complete.

## Out of scope

- Recoloring the entire UI (menus, headers, lesson content) — only the
  three feedback categories named above.
- Any change to section/final exam question counts.
- Any change to topic completion/lock state as part of skill-level
  selection.
- A settings-driven choice of *which* sound plays, sound duration/volume,
  or platform-specific `Beep()` APIs — the bell character is the simplest
  correct implementation and this is explicitly the project's last
  "polish" phase, not a place to add new abstraction surface.

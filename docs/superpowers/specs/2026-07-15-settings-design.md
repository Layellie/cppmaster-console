# CppMaster Console — Ayarlar (Settings) Design (Phase 8)

## Context

Phases 1-7 built a solid, fully-tested core but never implemented menu
option 9 ("Ayarlar") — it is currently a `showNotYetAvailable("Ayarlar")`
stub (`Application.cpp:173`). The original project brief asked for a
10-item settings menu. This phase implements it, scoped honestly: only
settings that have a real, verifiable effect on current app behavior are
built now. Two spec items (color toggle, sound) are deferred to a later
"polish" phase because no color/sound system exists yet to toggle — adding
a setting with no effect would be exactly the "fake feature" the project's
own brief explicitly forbids. A third (default exam question count) is
deferred because only one fixed-20-question exam exists today; the setting
has nowhere real to plug in until the multi-section exam work (a later
phase) exists.

## Goal

Add a real `data/settings.txt`-backed `Settings` menu with 6 items, each
wired into the exact place in the existing codebase it changes behavior,
with defaults that reproduce today's hardcoded behavior exactly — so every
prior phase's regression transcript still passes unchanged unless the user
actively changes a setting.

## Settings and their real hooks

1. **Konu kilidi aç/kapa** (bool, default `true`). No consumer yet in this
   phase — Phase 9 (topic lock) reads it. Stored now so Phase 9 doesn't need
   to touch this phase's persistence code again.
2. **Cevaplarda büyük-küçük harf duyarlılığı** (bool `strictCaseSensitivity`,
   default `true` = today's behavior). When `false`, the five
   case-sensitive-whitespace-normalized question types
   (`CompleteLine`/`PredictOutput`/`FindError`/`FixCode`/`OrderCode` — the
   `OrderCode` case-fold has no visible effect since its answers are digit
   sequences, but the setting applies uniformly rather than special-casing
   it) are matched case-insensitively too, on top of whitespace collapsing.
   `MultipleChoice`/`TrueFalse`/`FillBlank` are unaffected — they are always
   case-insensitive per the original brief, not something this setting
   should be able to make stricter.
3. **Kod cevaplarında tolerans seviyesi** (bool `lenientWriteCodeTolerance`,
   default `false` = today's behavior, all required substrings mandatory).
   When `true`, `WriteCode` questions accept an answer missing at most one
   required substring (still must be bracket-balanced).
4. **Günlük soru hedefi** (int `dailyReviewQuestionCap`, default `20` =
   today's hardcoded `kDailyReviewCap` in `Application.cpp:549`). Replaces
   that constant with a value read from settings.
5. **Açıklama detay seviyesi** (bool `fullExplanationDetail`, default `true`
   = today's behavior). When `false`, `showLessonContent` skips the "Satır
   satır açıklama" and "Yaygın hatalar" sections (still shows explanation,
   syntax, example).
6. **İlerlemeyi dışa aktar / içe aktar**: copies all five `data/*.txt` files
   (progress, mistakes, achievements, generated question history, and this
   phase's own settings file) to/from a user-supplied directory path via
   `std::filesystem::copy_file`. Missing
   source files during export are skipped (not an error — a fresh install
   has no mistakes/achievements file yet); missing destination directory is
   created.

Deferred, not built this phase (documented so nobody re-discovers this as
a bug later):
- Renkleri aç/kapat, sesli uyarı — no color/sound system exists to toggle.
- Varsayılan sınav soru sayısı — only one fixed 20-question exam exists;
  meaningful once multi-section exams exist.

## Data model and persistence

```cpp
// src/Settings.h
struct Settings {
    bool topicLockEnabled = true;
    bool strictCaseSensitivity = true;
    bool lenientWriteCodeTolerance = false;
    bool fullExplanationDetail = true;
    int dailyReviewQuestionCap = 20;
};
```

`SettingsManager` mirrors `ProgressManager`'s exact shape (a `load` that
returns a value + corruption flag, a `save` that writes unconditionally),
so the corruption-safe contract (malformed line → whole file treated as
corrupt → backup + reset to defaults) matches every other persistence class
in the project:

```cpp
struct SettingsLoadResult {
    Settings settings;
    bool wasCorrupted;
};

class SettingsManager {
public:
    [[nodiscard]] SettingsLoadResult load(
        const std::string& filePath, const std::string& backupPath) const;
    void save(const Settings& settings, const std::string& filePath) const;
};
```

File format matches the existing `key value` line convention (see
`ProgressManager`'s `xp 150` style):
```
topic_lock 1
strict_case 1
lenient_writecode 0
full_explanation 1
daily_cap 20
```

## Wiring into existing code

- `QuizEngine::evaluate` gains a new parameter:
  `AnswerResult evaluate(const Question& question, const std::string& rawAnswer, const Settings& settings = Settings{}) const;`
  The default argument means every existing call site and every existing
  `QuizEngineTests.cpp` test compiles unchanged (they get strict/default
  behavior). `Application::askOneQuestion` is updated to pass `settings_`
  explicitly.
- `Application` gains a `Settings settings_;` member, loaded in the
  constructor (mirroring how `progress_`/`mistakes_`/`achievements_` are
  loaded today) and saved after every settings-menu edit (mirroring how
  `progress_` is saved after every quiz).
- `Application::runDailyReview`'s `constexpr std::size_t kDailyReviewCap = 20;`
  becomes `const std::size_t dailyReviewCap = static_cast<std::size_t>(settings_.dailyReviewQuestionCap);`.
- `Application::showLessonContent` wraps the line-explanations/common-mistakes
  block in `if (settings_.fullExplanationDetail) { ... }`.
- Menu option 9 becomes a real `showSettingsMenu()` (replacing the
  `showNotYetAvailable("Ayarlar")` call at `Application.cpp:173`) offering:
  ```
  1. Konu kilidini aç/kapat (şu an: Açık/Kapalı)
  2. Büyük-küçük harf duyarlılığını aç/kapat (şu an: Açık/Kapalı)
  3. Kod cevabı toleransını aç/kapat (şu an: Sıkı/Esnek)
  4. Açıklama detay seviyesini değiştir (şu an: Tam/Kısa)
  5. Günlük soru hedefini değiştir (şu an: N)
  6. İlerlemeyi dışa aktar
  7. İlerlemeyi içe aktar
  0. Geri dön
  ```
  Each toggle/edit saves immediately via `SettingsManager::save`.

## Testing / verification for this phase

- Unit tests (`tests/SettingsManagerTests.cpp`, following the exact
  `tests/test_data/` isolation convention from Phase 7): missing-file loads
  defaults not-corrupted, save-then-load round-trips all 5 fields, corrupted
  file backs up and resets to defaults.
- `tests/QuizEngineTests.cpp` gains new cases for the two settings-aware
  branches (lenient case-insensitivity on a case-sensitive type; lenient
  WriteCode missing-one-substring), verifying the *default* `Settings{}`
  still produces every existing test's original behavior (regression-safe).
- Manual piped-transcript verification (this project's established method
  for `Application`/`ConsoleUI`, since those remain out of unit-test scope):
  one transcript exercising the new settings menu end-to-end (toggle each
  setting, confirm the printed "şu an: ..." state flips, confirm
  `data/settings.txt` contains the expected lines after each change, confirm
  export/import round-trips the four data files), and a re-run of an
  existing known-exact Phase-1-era transcript with all settings left at
  their defaults to prove nothing observable changed for a user who never
  opens the settings menu.

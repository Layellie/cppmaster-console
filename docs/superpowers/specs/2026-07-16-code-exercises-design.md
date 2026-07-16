# CppMaster Console — Kod Yazma Alıştırmaları (Code Exercises) Design (Phase 11)

## Context

The original brief (section 16) asks for a dedicated code-writing-practice
mode with 25 tasks across three tiers (7 Başlangıç, 9 Orta, 9 İleri), each
with a description, expected behavior, sample input/output, hints,
evaluation criteria, a sample solution (not shown until the user attempts
the task), and an alternative-solution note. This has been a
`showNotYetAvailable("Kod Yazma Alıştırmaları")` stub since Phase 1
(`Application.cpp:161`).

## Reusing `QuizEngine`'s WriteCode evaluation instead of building new logic

The roadmap already calls for this: "yapısal değerlendirme (mevcut
WriteCode kontrol mantığını yeniden kullanarak)." Every code exercise is
represented internally as a `Question` with `type = QuestionType::WriteCode`
and its evaluation criteria stored as `acceptedAnswers` (required
substrings) — exactly the structure `QuizEngine::evaluate` already knows
how to grade (bracket-balance check + all-required-substrings-present, with
`settings_.lenientWriteCodeTolerance` already wired to allow one miss).
This means Phase 11 adds **zero new evaluation logic** — it adds a new data
model for the richer per-exercise content (description, sample I/O, hints,
sample solution) and a new interactive mode, and hands the actual grading
straight to the existing, already-tested `QuizEngine`.

## Data model

```cpp
// src/CodeExercise.h
struct CodeExercise {
    int id = 0;
    std::string tier;              // "Başlangıç" | "Orta" | "İleri"
    std::string title;
    std::string description;       // Görev açıklaması
    std::string expectedBehavior;  // Beklenen davranış
    std::string sampleInput;       // Örnek giriş
    std::string sampleOutput;      // Örnek çıkış
    std::vector<std::string> hints;              // İpuçları (shown progressively, like ipucu)
    std::vector<std::string> requiredKeywords;   // Değerlendirme kriterleri - reused as a WriteCode Question's acceptedAnswers
    std::string sampleSolution;                  // Örnek çözüm - never shown before an attempt
    std::string alternativeSolutionNote;         // Alternatif çözüm açıklaması
    int baseXp = 0;
};
```

`CodeExerciseManager` mirrors `QuestionManager`/`LessonManager`'s exact
shape: a constructor that hand-populates all 25 exercises,
`exercisesForTier(tier)`, `findById(id)`.

## XP

Matching the original brief's guidance ("Kod yazma sorusu: +40 XP, Tam
program sorusu: +100 XP"), scaled by tier: Başlangıç = 40, Orta = 60, İleri
= 100.

## Evaluation via `QuizEngine`

```cpp
Question toWriteCodeQuestion(const CodeExercise& exercise) {
    Question question;
    question.id = exercise.id;
    question.type = QuestionType::WriteCode;
    question.acceptedAnswers = exercise.requiredKeywords;
    question.baseXp = exercise.baseXp;
    question.explanation = exercise.alternativeSolutionNote;
    return question;
}
```
`Application` builds this on the fly and calls
`quizEngine_.evaluate(question, submittedCode, settings_)` — the existing
bracket-balance + required-substring logic (with the existing lenient-
tolerance setting) grades it exactly like any other `WriteCode` question,
with no new grading code.

## Interactive flow (`Application::runCodeExercises`)

1. Replace the menu-5 stub with a tier submenu: Başlangıç / Orta / İleri /
   Geri.
2. List that tier's exercises (id + title); let the user pick one or go
   back.
3. Show description, expected behavior, sample input, sample output.
4. Let the user type `ipucu` (progressive hints, reusing the exact
   `hintLevelUsed`/escalation convention from Phase 10 — up to
   `exercise.hints.size()` levels) or submit code via
   `ui_.readMultilineCode()` (terminated by `BITIR`, same convention as
   every other `WriteCode` answer in the app).
5. Grade via `QuizEngine::evaluate`. **Only after this first submission
   attempt**, show the sample solution and the alternative-solution note —
   matching the brief's "Örnek çözüm, kullanıcı denemeden doğrudan
   gösterilmemeli." A wrong submission still reveals the sample solution
   afterward (the brief only forbids showing it *before* an attempt, not
   after a failed one — showing it after any attempt, right or wrong, is
   the standard "here's how you could have done it" teaching moment every
   other question type in this app already provides via its explanation).
6. Award XP on a correct submission (respecting the same hint-based
   penalty formula from Phase 10, since the same `ipucu` mechanic is
   reused), save progress, return to the tier's exercise list.

## Scope cuts (deliberate)

- **No new "structural evaluation" beyond what `QuizEngine::evaluate`
  already does for `WriteCode`.** The brief's evaluation-criteria list per
  exercise ("Gerekli anahtar kelimeler var mı? Parantezler dengeli mi?
  Süslü parantezler dengeli mi?") is exactly what `matchesWriteCode` already
  checks. No AST parsing, no compilation, no execution of user code —
  consistent with the project's existing, explicitly-stated stance
  ("Kullanıcının yazdığı kodu uygulama içinde otomatik şekilde çalıştırma").
- **`konu`/`ornek`/`gec`/`cikis` are not wired into code exercises.** Those
  commands are specific to `askOneQuestion`'s single-line-and-multiline
  quiz flow (Phase 10); code exercises are a different interaction shape
  (description → hints-on-request → one multi-line submission → solution
  reveal) where `gec`/`cikis`-equivalents are just the tier menu's own
  "Geri" option. Only `ipucu`'s progressive-hint mechanic is reused, applied
  directly by `runCodeExercises` rather than by routing through
  `askOneQuestion` (which isn't used for `WriteCode`'s command loop even in
  Phase 10 — see that phase's scope cuts).

## Testing / verification for this phase

- `tests/CodeExerciseManagerTests.cpp`: exactly 25 exercises exist (7+9+9);
  every id is unique; `exercisesForTier("Başlangıç")` returns exactly 7,
  `"Orta"` exactly 9, `"İleri"` exactly 9; every exercise has non-empty
  `description`/`expectedBehavior`/`sampleInput`/`sampleOutput`/
  `sampleSolution`/at least one hint/at least one required keyword.
- `tests/CodeExerciseTests.cpp` (the `toWriteCodeQuestion` conversion, plus
  a "does the exercise's own sample solution actually pass its own
  requiredKeywords check" test for a handful of representative exercises
  from each tier — this is the single highest-value test in this phase,
  since it directly proves the hand-authored requirements and hand-authored
  solution agree with each other, verified against the real, unmodified
  `QuizEngine::evaluate`).
- Manual piped-transcript verification: the tier submenu, viewing an
  exercise's description/sample I/O, requesting a hint, submitting a
  correct solution and confirming XP awarded plus the sample solution
  reveal, and submitting an incorrect solution and confirming the sample
  solution still reveals afterward (per the "not before an attempt" rule).

# CppMaster Console — Remaining Scope Roadmap (post Phase 7)

## Why this file exists

The original project brief (first user message of this project, 2 concatenated
documents: the base C++17/C++20 app spec, and the "C++20 ve Tekrarsız Dinamik
Soru Üretim Sistemi Güncellemesi" dynamic-generation addendum) asked for far
more than what the first 7 phases delivered. Phases 1-7 built a solid,
fully-tested core (100-topic skeleton, 10 real topics with content, 72
questions, 11 question types, XP/levels, achievements, mistake review, daily
review, one section exam, a small 2-generator dynamic system, and a full unit
test suite). This file tracks everything from the original spec that is
still missing, decomposed into phases using the same
brainstorm → spec → plan → subagent-driven-development discipline as
Phases 1-7. Each phase below gets its own
`docs/superpowers/specs/<date>-<name>-design.md` and
`docs/superpowers/plans/<date>-<name>.md` when it starts.

## Confirmed gaps (verified against current code, not assumed)

- `Application.cpp:161` — "Kod Yazma Alıştırmaları" (menu option 5) is a
  `showNotYetAvailable(...)` stub. Not implemented at all.
- ~~"Ayarlar" (menu option 9) stub~~ — **resolved in Phase 8**: a real
  settings menu now exists (topic-lock toggle, case-sensitivity, WriteCode
  tolerance, explanation detail, daily review cap, export/import). Renk
  aç/kapa and sesli uyarı remain deferred to Phase 25 (no color/sound system
  exists yet); varsayılan sınav soru sayısı remains deferred to Phase 22
  (only one fixed exam exists today).
- Only topics 1-10 (Section 1) have lesson content; topics 11-100 exist only
  as id/title/section entries.
- Only 72 hand-written questions exist (all for topics 1-10); the spec asked
  for a bank of at least 2900 (≥29 per topic × 100 topics).
- Only one section exam exists (Section 1's fixed 20-question exam); the spec
  asked for one per section (10 total) plus a 100-question general final exam
  covering all topics.
- Only 2 dynamic generators exist (`IntArithmeticPredictGenerator`,
  `BoolOutputPredictGenerator`); the spec asked for at least 15 across major
  topic areas (arithmetic, mod, if-else, for, while, arrays, vector, string,
  functions, pointer, class, inheritance, map, sort+lambda, try-catch).
- The generation engine is a single flat 50-attempt retry loop; the spec
  asked for a 3-stage escalation (Normal → ExpandedParameters →
  StructuralVariation, then CrossTopic fallback) plus dedicated
  `GeneratedQuestionValidator`, `GeneratorRegistry`, `GeneratorScoring`,
  `ParameterDomain` classes and a developer log
  (`data/question_generation.log`).
- No hint system (`ipucu`/`konu`/`ornek`/`gec`/`cikis` in-quiz commands).
- No topic lock system (70%-completion gate between sections, togglable in
  settings).
- No adaptive difficulty (question difficulty shifting based on streaks).
- No first-launch skill-level selection screen, no ANSI color system.
- No large-scale generation tests (10,000-iteration uniqueness/correctness/
  performance stress tests the spec asked for) — the current suite is
  correctness-focused at small scale, not stress-scale.

## Phase order (decided by the controller, not yet individually brainstormed)

Ordered by dependency and value; each is still a full phase in its own right
(design doc + plan + subagent-driven-development + final review), same rigor
as Phases 1-7.

- **Phase 8 — Ayarlar (Settings): COMPLETE** (commits `cdc769b..1466130`,
  final review "Ready to merge: Yes"). 6 real settings implemented (topic
  lock toggle stored for Phase 9, case sensitivity, WriteCode tolerance,
  explanation detail, daily review cap, export/import); renk/ses/sınav-soru-
  sayısı deliberately deferred (see note above). Defaults reproduce every
  pre-Phase-8 hardcoded behavior exactly.
- **Phase 9 — Konu kilidi sistemi: COMPLETE** (commits `ad5d4e2..4841703`,
  final review "Ready to merge: With fixes" — one doc-only fix, this
  roadmap entry, applied directly). `settings_.topicLockEnabled` now gates
  Section 1's pre-existing 70%-completion exam threshold
  (`sectionExamIsUnlocked` in `src/TopicLock.h`), a passed exam is recorded
  via `UserProgress::recordSectionExamPassed`/persisted via
  `ProgressManager`, and the topic browser shows a `(henüz önerilmiyor)`
  advisory tag (`isSectionRecommended`) on any section beyond the highest
  one whose exam has been passed — purely advisory, no topic access is
  ever blocked, matching the brief's actual wording. The general
  next-section mechanism is built and unit-verified now; it can only
  currently move past Section 2 once Section 2's exam exists (a later
  content-expansion phase, 13+), since only Section 1 has content today.
- **Phase 10 — İpucu sistemi: COMPLETE** (commits `212cdbb..e03f7b9`, 76/76
  tests + ctest 100%). `ipucu`/`konu`/`ornek`/`gec`/`cikis` are now
  recognized as exact, case-sensitive commands inside
  `Application::askOneQuestion`'s answer-reading loop: `ipucu` reveals one
  of three escalating computed hints (`generateHint` in
  `src/HintProvider.h`/`.cpp`) and reduces awarded XP by 25% per hint level
  used (up to 75% off at level 3); `konu`/`ornek` re-display the current
  question's lesson explanation/example code; `gec` records the question as
  a miss (correct answer shown via `QuizEngine::correctAnswerDisplay`)
  without ending the session; `cikis` returns to the main menu immediately
  via the new `AnswerResult::exitRequested` flag, with any XP already
  earned in the partial session awarded and saved first (`runTopicQuiz`,
  `runQuickTest`, `runMistakeQuestions`, `runSectionExam` all check this
  flag before returning). The section exam passes `allowHints = false`,
  disabling `ipucu`/`konu`/`ornek` specifically during Bölüm 1 Sınavı.
- **Phase 11 — Kod Yazma Alıştırmaları modu: COMPLETE** (commits
  `867f22f..4a49e44`, 83/83 tests + ctest 100%). 25 hand-authored
  code-writing exercises (7 Başlangıç + 9 Orta + 9 İleri) live in
  `CodeExerciseManager`/`CodeExercise` (`src/CodeExerciseManager.h/.cpp`,
  `src/CodeExercise.h`), graded by reusing the existing
  `QuizEngine::evaluate` WriteCode logic via `toWriteCodeQuestion` — no new
  grading logic was written. `Application::runCodeExercises`/
  `runCodeExerciseTier`/`runCodeExercise` wire menu option 5 into a tier
  submenu → per-tier exercise list → description/expected-behavior/
  sample-I-O display → an optional pre-code hint request loop (E/H prompt,
  same escalating-penalty idea as Phase 10's `ipucu` but requested *before*
  code entry, since `readMultilineCode()` can't be interleaved with
  single-line commands the way Phase 10's answer loop could) → multi-line
  code submission → grading → sample-solution/alternative-solution-note
  reveal after any submission attempt, correct or not.
- **Phase 12 — Adaptif zorluk sistemi: COMPLETE** (commits `ca3e026..18c265e`,
  87/87 tests + ctest 100%). `src/AdaptiveDifficulty.h` adds two pure
  functions: `selectNextQuestionIndex` (jumps to the hardest remaining
  question after 2+ correct answers in a row, otherwise picks the
  next-easiest remaining) and `shouldShowExtraHelp` (true at 2+ wrong
  answers in a row). `Application::runTopicQuiz` now sorts a topic's
  questions once, ascending by `Difficulty`, then uses both functions on
  every loop iteration to pick the next question and to decide when to
  re-show the topic's lesson explanation plus an automatic level-1 hint
  (reusing Phase 10's `generateHint`). This deliberately changes the order
  topic 1's 8 questions are asked in versus every prior phase's transcript
  (old order `1,2,3,4,5,6,65,70`; new canonical order `3,1,70,6,2,65,5,4`
  when every answer is correct) — the old order was never actually
  difficulty-sorted, so this is a correction, not a regression.
- **Phases 13-21 — İçerik genişletme (en büyük parça):** kalan 90 konunun ders
  içeriği + soru bankasının ~2900'e çıkarılması. Bölüm bölüm (Section 2
  through Section 10, 9 phases), her biri o bölümün 10 konusu + ~290 soru.
- **Phase 22 — Sınavlar:** kalan 9 bölüm sınavı + 100 soruluk genel final
  sınavı (içerik tamamlandıktan sonra mümkün).
- **Phase 23 — Üretici kütüphanesini genişletme:** en az 15 üretici,
  `GeneratedQuestionValidator`/`GeneratorRegistry`/`GeneratorScoring`/
  `ParameterDomain`, 3 aşamalı üretim algoritması, geliştirici log dosyası.
- **Phase 24 — Büyük ölçekli üretim testleri:** 10.000 iterasyonluk
  benzersizlik/doğruluk/performans testleri.
- **Phase 25 — Kalan cila:** ilk açılış seviye seçim ekranı, ANSI renk
  sistemi (Ayarlar'dan kapatılabilir).

## Status

Phase 12 complete (2026-07-16). Phase 13 starting next — the first of the
large content-expansion phases (Phases 13-21). Update this file's
phase list as each phase completes (mirror `.superpowers/sdd/progress.md`'s
per-phase headers).

**Recurring gap, now fixed twice (Phase 8's and Phase 9's final reviews
both flagged this file as stale):** from Phase 10 onward, each phase's plan
should include an explicit last step — "update `docs/superpowers/roadmap.md`'s
phase-order entry and Status section to mark the phase COMPLETE with its
commit range" — as part of the final task, not left as an after-the-fact
fix following the final review.

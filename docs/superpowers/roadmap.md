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

- ~~`Application.cpp:161` — "Kod Yazma Alıştırmaları" (menu option 5) is a
  `showNotYetAvailable(...)` stub. Not implemented at all.~~ — **resolved
  in Phase 11** (this bullet itself had gone stale — Phase 11 shipped 25
  hand-authored code-writing exercises across 3 tiers, reusing
  `QuizEngine::evaluate`'s WriteCode grading; the `showNotYetAvailable`
  stub had zero remaining call sites and was removed in Phase 25's final
  review).
- ~~"Ayarlar" (menu option 9) stub~~ — **resolved in Phase 8**, deferred
  fields **resolved in Phase 25**: a real settings menu now exists
  (topic-lock toggle, case-sensitivity, WriteCode tolerance, explanation
  detail, daily review cap, export/import, plus Phase 25's color toggle,
  audio alert toggle, and Quick Test question count).
- ~~Only topics 1-10 (Section 1) have lesson content; topics 11-100 exist
  only as id/title/section entries.~~ — **resolved in Phase 21**: all 100
  topics now have full lesson content (`src/LessonContentSection2.cpp`
  through `src/LessonContentSection10.cpp`, plus the original Section 1
  content), delivered across nine section-by-section content phases
  (13-21).
- ~~Only 72 hand-written questions exist (all for topics 1-10); the spec
  asked for a bank of at least 2900 (≥29 per topic × 100 topics).~~ —
  **resolved in Phase 21**: the full question bank now spans ids 1-2682
  (29 per topic × 100 topics, plus the original 72 for topics 1-10 which
  were never reduced). The final count (2682) is not exactly 2900 — that
  was a rough estimate in the original spec — but the actual requirement
  ("≥29 per topic × 100 topics") is met exactly for every one of the 100
  topics; this is the correct, expected outcome, not a shortfall.
- ~~Only one section exam exists (Section 1's fixed 20-question exam);
  the spec asked for one per section (10 total) plus a 100-question
  general final exam covering all topics.~~ — **resolved in Phase 22**:
  all 10 sections now have a 20-question exam (Section 1's original
  curated set preserved byte-for-byte; Sections 2-10 computed
  algorithmically, 2 questions per topic, via
  `examQuestionIdsForSection` in `src/ExamContent.cpp`), plus a new
  100-question general final exam (`finalExamQuestionIds`, 1 question
  per topic across all 100 topics) reachable via a new exam-picker
  submenu under "6. Seviye Sınavı".
- ~~Only 2 dynamic generators exist (`IntArithmeticPredictGenerator`,
  `BoolOutputPredictGenerator`); the spec asked for at least 15 across major
  topic areas (arithmetic, mod, if-else, for, while, arrays, vector, string,
  functions, pointer, class, inheritance, map, sort+lambda, try-catch).~~ —
  **resolved in Phase 23**: 15 new generators were added (topics 11, 12, 18,
  22, 23, 31, 34, 37, 43, 52, 64, 69, 84, 91, 99), bringing the total to 17
  registered generators, all wired into `Application`'s constructor and
  exercised by `runQuickTest`.
- ~~The generation engine is a single flat 50-attempt retry loop; the spec
  asked for a 3-stage escalation (Normal → ExpandedParameters →
  StructuralVariation, then CrossTopic fallback) plus dedicated
  `GeneratedQuestionValidator`, `GeneratorRegistry`, `GeneratorScoring`,
  `ParameterDomain` classes and a developer log
  (`data/question_generation.log`).~~ — **resolved in Phase 23**:
  `QuestionGenerationEngine::generateUniqueForTopic` now implements the
  full 4-stage escalation (20 attempts/stage against the topic's own
  generator(s), then a CrossTopic fallback tried against every other
  generator ordered by `GeneratorScoring::successRate`), backed by new
  `GeneratedQuestionValidator`, `GeneratorRegistry`, `GeneratorScoring`, and
  `ParameterDomain` classes, and logging every attempt's terminal outcome
  to `data/question_generation.log`.
- ~~No hint system (`ipucu`/`konu`/`ornek`/`gec`/`cikis` in-quiz commands).~~
  — **resolved in Phase 10** (this bullet had also gone stale): all 5
  commands are implemented in `Application::askOneQuestion`'s answer-
  reading loop, backed by `src/HintProvider.h`/`.cpp`.
- ~~No topic lock system (70%-completion gate between sections, togglable
  in settings).~~ — **resolved in Phase 9**: `settings_.topicLockEnabled`
  gates the completion threshold via `sectionExamIsUnlocked` in
  `src/TopicLock.h`.
- ~~No adaptive difficulty (question difficulty shifting based on
  streaks).~~ — **resolved in Phase 12**: `src/AdaptiveDifficulty.h`'s
  `selectNextQuestionIndex`/`shouldShowExtraHelp` drive question ordering
  and extra-help triggers in `Application::runTopicQuiz`.
- ~~No first-launch skill-level selection screen, no ANSI color system.~~
  — **resolved in Phase 25**: a one-time skill-level screen (detected via
  `data/progress.txt` not existing yet) sets a starting XP of 0/120/350
  for the 3 self-assessed levels; `ConsoleUI` gained
  `printSuccess`/`printError`/`printHighlight` (ANSI green/red/yellow,
  gated by both the new `Settings::colorEnabled` toggle and a Windows
  `ENABLE_VIRTUAL_TERMINAL_PROCESSING` capability check) plus a
  `playAlertSound` console-bell alert (gated by `Settings::audioAlertEnabled`).
- ~~No large-scale generation tests (10,000-iteration uniqueness/correctness/
  performance stress tests the spec asked for) — the current suite is
  correctness-focused at small scale, not stress-scale.~~ — **resolved in
  Phase 24**: a new `CppMasterConsoleStressTests` executable runs 10,000
  mixed-topic iterations plus 500 single-topic exhaustion iterations
  against the real 17-generator system, asserting 100% success, global
  `exactHash` uniqueness, and independent `GeneratedQuestionValidator`
  agreement on every result. Kept out of the default `ctest` suite
  (~13s vs ~0.6s) since it's a manually-run stress tool, not an inner-loop
  test.

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
- **Phase 13 — Bölüm 2 İçerik Genişletmesi: COMPLETE** (commits
  `6df525f..cf6b6f1`, 89/89 tests + ctest 100%). Topics 11-20 (Section 2:
  "Operatörler ve koşullar") now have full lesson content
  (`src/LessonContentSection2.cpp`) and a 290-question bank (ids 73-362, 29
  per topic, `src/QuestionsSection2.cpp`) spanning 9 of the 11 question
  types (`Scenario`/`Matching` deliberately unused, matching Section 1's
  own dormant-type precedent).
  `LessonManager_TopicsElevenToTwentyHaveRealContent` and the widened
  `QuestionManager_NoDuplicateQuestionIds` (now scans topics 1-100 instead
  of 1-10) plus the new
  `QuestionManager_EveryTopicElevenToTwentyHasAtLeastTwentyNineQuestions`
  test cover the whole bank; a manual end-to-end run additionally confirmed
  `openTopic`'s content gate now passes for topic 11 with zero
  `Application.cpp` changes, the quiz reports "Konu testi başlıyor (29
  soru).", a correct answer awards XP, and mid-quiz `cikis` exits cleanly
  back to the main menu with partial XP saved. First of nine section-by-
  section content phases (13-21) closing the roadmap's lesson-content and
  question-bank gaps for topics 11-100.
- **Phase 14 — Bölüm 3 İçerik Genişletmesi: COMPLETE** (commits
  `7987f8c..f62ea67`, 90/90 tests + ctest 100%). Topics 21-30 (Section 3:
  "Seçim ve döngüler") now have full lesson content
  (`src/LessonContentSection3.cpp`) and a 290-question bank (ids 363-652, 29
  per topic, `src/QuestionsSection3.cpp`) spanning the same 9 of 11 question
  types as Section 2 (`Scenario`/`Matching` still deliberately unused). The
  existing `LessonManager_TopicsElevenToThirtyHaveRealContent` test was
  widened in-place (11-20 -> 11-30) and a new
  `QuestionManager_EveryTopicTwentyOneToThirtyHasAtLeastTwentyNineQuestions`
  test was added; `QuestionManager_NoDuplicateQuestionIds` already scanned
  topics 1-100 from Phase 13 and needed no change. A manual end-to-end run
  additionally confirmed `openTopic`'s content gate passes for topic 22 with
  zero `Application.cpp` changes, the quiz reports "Konu testi başlıyor (29
  soru).", correct answers award XP, and mid-quiz `cikis` exits cleanly back
  to the main menu with partial XP saved. Second of nine section-by-section
  content phases (13-21) closing the roadmap's lesson-content and
  question-bank gaps for topics 11-100.
- **Phase 15 — Bölüm 4 İçerik Genişletmesi: COMPLETE** (commits
  `23d1628..3d230f9`, 91/91 tests + ctest 100%). Topics 31-40 (Section 4:
  "Diziler, vector ve string") now have full lesson content
  (`src/LessonContentSection4.cpp`) and a 290-question bank (ids 653-942, 29
  per topic, `src/QuestionsSection4.cpp`) spanning the same 9 of 11 question
  types as Sections 2-3 (`Scenario`/`Matching` still deliberately unused). The
  existing `LessonManager_TopicsElevenToThirtyHaveRealContent` test was
  widened in-place (11-30 -> 11-40, now
  `LessonManager_TopicsElevenToFortyHaveRealContent`) and a new
  `QuestionManager_EveryTopicThirtyOneToFortyHasAtLeastTwentyNineQuestions`
  test was added; `QuestionManager_NoDuplicateQuestionIds` already scanned
  topics 1-100 and needed no change. A manual end-to-end run additionally
  confirmed `openTopic`'s content gate passes for topic 34 ("vector") with
  zero `Application.cpp` changes, the quiz reports "Konu testi başlıyor (29
  soru).", a correct answer awards XP (and unlocks the "İlk Adım"
  achievement), and mid-quiz `cikis` exits cleanly back to the main menu with
  partial XP (5) saved. Third of nine section-by-section content phases
  (13-21) closing the roadmap's lesson-content and question-bank gaps for
  topics 11-100.
- **Phase 16 — Bölüm 5 İçerik Genişletmesi: COMPLETE** (commits `4955846..f53d6c0`, 92/92 tests + ctest 100%). Topics 41-50 (Section 5: "Fonksiyonlar") now have full lesson content (`src/LessonContentSection5.cpp`) and a 290-question bank (ids 943-1232, 29 per topic, `src/QuestionsSection5.cpp`) spanning the same 9 of 11 question types as Sections 2-4 (`Scenario`/`Matching` still deliberately unused). A new `QuestionManager_EveryTopicFortyOneToFiftyHasAtLeastTwentyNineQuestions` test was added; `QuestionManager_NoDuplicateQuestionIds` already scanned topics 1-100 and needed no change. A manual end-to-end run additionally confirmed `openTopic`'s content gate passes for topic 43 ("Değer döndüren fonksiyon") with zero `Application.cpp` changes, the quiz reports "Konu testi başlıyor (29 soru).", correct answers award XP, and mid-quiz `cikis` exits cleanly back to the main menu with partial XP saved. Fourth of nine section-by-section content phases (13-21) closing the roadmap's lesson-content and question-bank gaps for topics 11-100.
- **Phase 17 — Bölüm 6 İçerik Genişletmesi: COMPLETE** (commits `bcdfbba..b5fbe3d`, 93/93 tests + ctest 100%). Topics 51-60 (Section 6: "Lambda, pointer ve bellek") now have full lesson content (`src/LessonContentSection6.cpp`) and a 290-question bank (ids 1233-1522, 29 per topic, `src/QuestionsSection6.cpp`) spanning the same 9 of 11 question types as Sections 2-5 (`Scenario`/`Matching` still deliberately unused). A new `QuestionManager_EveryTopicFiftyOneToSixtyHasAtLeastTwentyNineQuestions` test was added; `QuestionManager_NoDuplicateQuestionIds` already scanned topics 1-100 and needed no change. A manual end-to-end run additionally confirmed `openTopic`'s content gate passes for topic 57 ("new") with zero `Application.cpp` changes, the quiz reports "Konu testi başlıyor (29 soru).", correct answers award XP, and mid-quiz `cikis` exits cleanly back to the main menu with partial XP saved. Fifth of nine section-by-section content phases (13-21) closing the roadmap's lesson-content and question-bank gaps for topics 11-100.
- **Phase 18 — Bölüm 7 İçerik Genişletmesi: COMPLETE** (commits `f5c69af..0f80e2e`, 94/94 tests + ctest 100%). Topics 61-70 (Section 7: "Struct ve nesne yönelimli programlama") now have full lesson content (`src/LessonContentSection7.cpp`) and a 290-question bank (ids 1523-1812, 29 per topic, `src/QuestionsSection7.cpp`) spanning the same 9 of 11 question types as Sections 2-6 (`Scenario`/`Matching` still deliberately unused). A new `QuestionManager_EveryTopicSixtyOneToSeventyHasAtLeastTwentyNineQuestions` test was added; `QuestionManager_NoDuplicateQuestionIds` already scanned topics 1-100 and needed no change. A manual end-to-end run additionally confirmed `openTopic`'s content gate passes for topic 65 ("Constructor") with zero `Application.cpp` changes, the quiz reports "Konu testi başlıyor (29 soru).", correct answers award XP, and mid-quiz `cikis` exits cleanly back to the main menu with partial XP saved. Sixth of nine section-by-section content phases (13-21) closing the roadmap's lesson-content and question-bank gaps for topics 11-100.
- **Phase 19 — Bölüm 8 İçerik Genişletmesi: COMPLETE** (commits `a7794da..5089325`, 95/95 tests + ctest 100%). Topics 71-80 (Section 8: "İleri nesne yönelimli özellikler") now have full lesson content (`src/LessonContentSection8.cpp`) and a 290-question bank (ids 1813-2102, 29 per topic, `src/QuestionsSection8.cpp`) spanning the same 9 of 11 question types as Sections 2-7 (`Scenario`/`Matching` still deliberately unused). A new `QuestionManager_EveryTopicSeventyOneToEightyHasAtLeastTwentyNineQuestions` test was added; `QuestionManager_NoDuplicateQuestionIds` already scanned topics 1-100 and needed no change. A manual end-to-end run additionally confirmed `openTopic`'s content gate passes for topic 74 ("Polimorfizm") with zero `Application.cpp` changes, the quiz reports "Konu testi başlıyor (29 soru).", correct answers award XP, and mid-quiz `cikis` exits cleanly back to the main menu with partial XP saved. Seventh of nine section-by-section content phases (13-21) closing the roadmap's lesson-content and question-bank gaps for topics 11-100.
- **Phase 20 — Bölüm 9 İçerik Genişletmesi: COMPLETE** (commits `c75308a..4793f79`, 96/96 tests + ctest 100%). Topics 81-90 (Section 9: "STL veri yapıları") now have full lesson content (`src/LessonContentSection9.cpp`) and a 290-question bank (ids 2103-2392, 29 per topic, `src/QuestionsSection9.cpp`) spanning the same 9 of 11 question types as Sections 2-8 (`Scenario`/`Matching` still deliberately unused). A new `QuestionManager_EveryTopicEightyOneToNinetyHasAtLeastTwentyNineQuestions` test was added; `QuestionManager_NoDuplicateQuestionIds` already scanned topics 1-100 and needed no change. A manual end-to-end run additionally confirmed `openTopic`'s content gate passes for topic 84 ("map") with zero `Application.cpp` changes, the quiz reports "Konu testi başlıyor (29 soru).", correct answers award XP, and mid-quiz `cikis` exits cleanly back to the main menu with partial XP saved. Eighth of nine section-by-section content phases (13-21) closing the roadmap's lesson-content and question-bank gaps for topics 11-100.
- **Phase 21 — Bölüm 10 İçerik Genişletmesi: COMPLETE** (commits `17a4448..b0fc567`, 96/96 tests + ctest 100%). Topics 91-100 (Section 10: "Algoritmalar, dosyalar ve hata yönetimi") now have full lesson content (`src/LessonContentSection10.cpp`) and a 290-question bank (ids 2393-2682, 29 per topic, `src/QuestionsSection10.cpp`) spanning the same 9 of 11 question types as Sections 2-9 (`Scenario`/`Matching` still deliberately unused). A new `QuestionManager_EveryTopicNinetyOneToHundredHasAtLeastTwentyNineQuestions` test was added; `QuestionManager_NoDuplicateQuestionIds` already scanned topics 1-100 and needed no change. Unlike every prior content phase, the "topics without content" test (`LessonManager_TopicsNinetyOneToHundredHaveNoContentYet`) was REMOVED entirely rather than narrowed, since after this phase every topic 1-100 has real content. A manual end-to-end run additionally confirmed `openTopic`'s content gate passes for topic 100 ("unique_ptr") with zero `Application.cpp` changes, the quiz reports "Konu testi başlıyor (29 soru).", correct answers award XP, and mid-quiz `cikis` exits cleanly back to the main menu with partial XP saved. **This is the LAST of nine section-by-section content phases (13-21)** — the full 100-topic bank (lesson content + ≥29 questions per topic) is now complete, closing out the two headline "Confirmed gaps" bullets above.
- **Phase 22 — Sınavlar: COMPLETE** (commits `7f3b8f7..7c34595`, 100/100 tests). Generalized the previously Section-1-only exam mechanism to all 10 sections plus a new 100-question general final exam. New `src/ExamContent.h`/`.cpp` (`examQuestionIdsForSection`, `finalExamQuestionIds`) computes exam question ids algorithmically for Sections 2-10 and the final exam (2 questions/topic for section exams, 1/topic for the final exam, using the fixed per-topic layout established across Phases 13-21: `baseId(topic) = 73 + (topic-11)*29`, offset +3 = first Medium MultipleChoice, offset +12 = first Medium TrueFalse) while preserving Section 1's original curated 20-question exam byte-for-byte. `Application::runSectionExam` gained a `sectionId` parameter; new `runFinalExam`/`showExamMenu` complete the flow, reachable via a new exam-picker submenu under "6. Seviye Sınavı" (main menu structure otherwise unchanged). 4 new `ExamContentTests.cpp` tests confirm every section exam has 20 unique resolvable ids, Sections 2-10 cover every one of their 10 topics exactly twice, and the final exam covers all 100 topics exactly once. `AchievementId::PerfectExam`'s description was generalized ("Bir sınavdan %100 aldın.") to correctly cover both exam kinds; `tests/QuestionManagerTests.cpp`'s stale duplicated exam-id array (flagged by its own comment as a staleness risk) was replaced with a direct call to `examQuestionIdsForSection(1)`. `UserProgress`'s per-section-exam-passed data model (a single "highest" int) was deliberately left unchanged — the final exam does not call `recordSectionExamPassed` since there is no "section 11". A manual end-to-end run confirmed the exam-picker menu lists all 10 sections plus "Genel Final Sınavı", the 70%-completion gate correctly blocks an unearned Section 2 exam, a full Section 2 exam run reports correct/score/XP/pass-fail, and the final exam's "100 soruluk sınav başlıyor." header plus a mid-exam `cikis` exit both work correctly.
- **Phase 23 — Üretici kütüphanesini genişletme: COMPLETE** (commits
  `48d7e9f..c7b0ff1`, 202/202 tests + ctest 100%). Rewrote `IQuestionGenerator`
  to require `topicId()` and a `GenerationStage` parameter (`Normal` /
  `ExpandedParameters` / `StructuralVariation`); added `ParameterDomain`
  (`draw`/`expanded`), `GeneratedQuestionValidator` (real content checks per
  question type), `GeneratorRegistry` (non-owning, `generatorsForTopic`/
  `allGenerators`), and `GeneratorScoring` (per-generator success-rate
  tracking with a neutral prior). `QuestionGenerationEngine::generateUniqueForTopic`
  replaces the old flat-retry `generateUnique`, implementing the full 4-stage
  escalation (own-topic Normal → ExpandedParameters → StructuralVariation,
  20 attempts each, then a CrossTopic fallback ordered by success rate) and
  logging every attempt's terminal outcome to `data/question_generation.log`
  (path injected via constructor so tests can redirect it). 15 new
  generators were added one per commit — `ArithmeticOperatorPredictGenerator`
  (11), `ModOperatorPredictGenerator` (12), `IfElsePredictGenerator` (18),
  `ForLoopSumPredictGenerator` (22), `WhileLoopCountPredictGenerator` (23),
  `ArrayElementPredictGenerator` (31), `VectorPushBackPredictGenerator` (34),
  `StringConcatPredictGenerator` (37), `FunctionReturnPredictGenerator` (43),
  `PointerDereferencePredictGenerator` (52), `ClassMemberPredictGenerator`
  (64), `InheritanceOverridePredictGenerator` (69), `MapLookupPredictGenerator`
  (84), `SortWithLambdaPredictGenerator` (91), `TryCatchPredictGenerator` (99)
  — each with its own `tests/Generators/*Tests.cpp` file, bringing the total
  to 17 registered generators (up from 2). Two real correctness risks were
  caught and fixed before committing: `WhileLoopCountPredictGenerator`'s
  divisor is clamped away from 0 and 1 (division-by-zero and infinite-loop
  risks once `ParameterDomain::expanded()` widens the domain), and
  `InheritanceOverridePredictGenerator`'s non-virtual-method-hiding answer
  was verified against a standalone MSVC compile before being assumed
  correct. A standalone 200-iteration integration harness (registry + engine
  + scoring + validator, outside the test suite) confirmed all 17 generators
  successfully produce valid questions and that the engine's cross-topic
  fallback correctly engages when a small-domain generator (`BoolOutputPredictGenerator`)
  exhausts its own uniqueness space. Deviated from the original Task 4/Task 6
  split: since removing the old `generateUnique` broke existing call sites
  immediately, Task 4 absorbed the minimal `Application.cpp` wiring needed
  to keep the build green, rather than leaving it fully separate for Task 6.
  Due to a multi-day subagent weekly-quota outage discovered mid-Phase 21
  (see that phase's ledger entry), all of Phase 23 was implemented and
  self-reviewed directly by the controller rather than via subagent
  dispatch — compile/runtime verification rigor (standalone `cl.exe`
  checks, full test suite reruns per commit) was preserved throughout.
- **Phase 24 — Büyük ölçekli üretim testleri: COMPLETE** (commits
  `6486c8e..e7ffe8f`; new suite 2/2, existing suite 202/202 + ctest 100%
  unaffected). A calibration run (10,000 iterations
  against the real 17-generator system, done before writing the spec
  rather than guessing) found that total exhaustion essentially never
  happens once `ArrayElementPredictGenerator` (a practically inexhaustible
  ~5×10^11-combination domain) is reachable via CrossTopic fallback, and
  that the ~10s runtime is dominated by the developer log's per-exhaustion
  file writes. New `tests/StressTests/GenerationStressTests.cpp` (own
  executable, `CppMasterConsoleStressTests`, deliberately not registered
  via `add_test()`) runs 10,000 mixed-topic iterations (100% success,
  0 duplicate `exactHash` values, 0 independent-validator disagreements,
  under a 30s budget) plus 500 iterations hammering a single small-domain
  topic (`BoolOutputPredictGenerator`, topic 9) alone, proving the
  CrossTopic fallback sustains a fully exhausted topic indefinitely. No
  production code changed — purely additive testing, per the phase's scope.
- **Phase 25 — Kalan cila: COMPLETE** (commits `860f74f..349cdcc`,
  203/203 tests + ctest 100%; new stress suite 2/2 unaffected). **This is
  the LAST phase in the roadmap.** `Settings` gained `colorEnabled`
  (default true), `audioAlertEnabled` (default false), and
  `quickTestQuestionCount` (default 5, replacing a hardcoded constant),
  with a new explicit backward-compatibility test proving a pre-Phase-25
  `settings.txt` still loads correctly with the 3 new fields at their
  defaults. `ConsoleUI` gained ANSI color output
  (`printSuccess`/`printError`/`printHighlight`, gated by the setting AND
  a Windows VT-processing capability check so an unsupported terminal
  never sees garbled escape codes) and a console-bell audio alert
  (`playAlertSound`, fires on wrong answers only). `Application` wires
  both into existing correct/wrong/achievement/level-up feedback, adds 3
  new Ayarlar menu entries, and adds a one-time first-launch skill-level
  screen (0/120/350 starting XP for 3 self-assessed levels, deliberately
  never touching topic completion or section-lock state, which the
  screen states explicitly). Three scoping judgment calls were made
  explicit in the spec before implementation, since the roadmap only
  named these items tersely: "varsayılan sınav soru sayısı" targets Quick
  Test's count rather than the structurally-fixed section/final exam
  sizes; the audio alert defaults off and fires only on mistakes; the
  first-launch screen never fabricates progress. A final documentation
  review additionally caught and fixed 4 stale "Confirmed gaps" bullets
  above (Kod Yazma Alıştırmaları, hint system, topic lock, adaptive
  difficulty) that had already been resolved in Phases 9-12 but were
  never struck through, plus removed the now-dead `showNotYetAvailable`
  stub those bullets referenced. Manually verified end-to-end: settings
  menu toggles persist and take effect immediately; a fresh run (no
  `data/progress.txt`) shows the skill-selection screen exactly once and
  sets XP/level correctly for each choice, a second run does not repeat
  it.

## Status

**Phase 25 complete (2026-07-22). This roadmap is now fully complete —
all 25 phases done, every "Confirmed gaps" bullet above resolved (the
4 that had gone stale were caught and fixed in this same final pass).**
The app now has: a full 100-topic lesson/question bank, hint/topic-lock/
adaptive-difficulty systems, code-writing exercises, per-section and
final exams, a 17-generator dynamic question system with a 4-stage
escalation engine verified at 10,000-iteration scale, and — as of this
phase — a first-launch skill screen plus color/audio settings closing
out the original spec's last deferred items. There is no Phase 26; any
further work on this project is genuinely new scope, not a gap this
roadmap was tracking, and should start its own brainstorm from scratch
rather than assume this file's phase-numbering convention continues.

**Recurring gap, now fixed twice (Phase 8's and Phase 9's final reviews
both flagged this file as stale):** from Phase 10 onward, each phase's plan
should include an explicit last step — "update `docs/superpowers/roadmap.md`'s
phase-order entry and Status section to mark the phase COMPLETE with its
commit range" — as part of the final task, not left as an after-the-fact
fix following the final review.

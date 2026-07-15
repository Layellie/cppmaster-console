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
- **Phase 9 — Konu kilidi sistemi:** %70 tamamlama eşiği, Ayarlar'dan
  kapatılabilir. Note discovered during Phase 8: `Application.cpp` already
  gates *Section 1's exam* behind a 70%-topic-completion ratio
  (`kSectionCompletionGateThreshold`) — that part of the original "Bölüm
  kilidi" spec item is done. What's still missing is gating a *section's
  topics* behind the *previous* section's exam score, which has nowhere
  real to plug in until Section 2 exists (a content-expansion phase, 13+).
  Scope Phase 9 to: consuming `settings_.topicLockEnabled` to let the
  existing Section-1 exam gate be disabled, plus building the general
  next-section-unlock mechanism ready for when Section 2 lands — not to
  producing an end-to-end-testable-today cross-section lock, since only one
  section currently has content.
- **Phase 10 — İpucu sistemi:** ipucu/konu/ornek/gec/cikis komutları, kademeli
  ipucu, XP azaltma.
- **Phase 11 — Kod Yazma Alıştırmaları modu:** 25 görev (7 başlangıç + 9 orta +
  9 ileri), yapısal değerlendirme (mevcut WriteCode kontrol mantığını
  yeniden kullanarak).
- **Phase 12 — Adaptif zorluk sistemi.**
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

Phase 8 complete (2026-07-16). Phase 9 starting next. Update this file's
phase list as each phase completes (mirror `.superpowers/sdd/progress.md`'s
per-phase headers).

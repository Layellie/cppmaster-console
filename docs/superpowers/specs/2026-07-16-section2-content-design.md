# CppMaster Console — Bölüm 2 İçerik Genişletmesi Design (Phase 13)

## Context

The roadmap's confirmed gap: "Only topics 1-10 (Section 1) have lesson
content; topics 11-100 exist only as id/title/section entries" and "Only 72
hand-written questions exist (all for topics 1-10); the spec asked for a
bank of at least 2900 (≥29 per topic × 100 topics)." Phase 13 is the first
of nine section-by-section content phases (13-21) that close this gap,
covering Section 2 (topics 11-20: "Operatörler ve koşullar").

## Scope decision (deliberate, documented)

The original spec's "≥29 per topic × 100 topics" reads as a per-topic
minimum applied uniformly. The roadmap's own phase breakdown, written when
the gap was first catalogued, already narrowed this to "kalan 90 konunun
ders içeriği + soru bankasının ~2900'e çıkarılması" — i.e., bring the
**remaining 90 topics** (11-100) up to real content, growing the overall
bank toward ~2900, without mandating that Section 1's already-shipped,
already-tested 72 questions (avg. 7.2/topic) also be expanded to 29/topic.
This phase honors that existing scoping: **Section 1's question count is
untouched**. Topics 11-100 each get exactly 29 new questions. Across the
9 remaining content phases this adds 90 × 29 = 2610 questions to the
existing 72, for a final bank of 2682 — the spirit of "~2900" for the
project as a whole, with Section 1 deliberately left alone as a
lower-density but already-verified section (revisiting it would be
unrequested scope creep into working, reviewed content).

## Topics covered (Section 2, sectionId 2, from `LessonManager.cpp`'s
`kTopicSeeds`)

11. Matematiksel operatörler
12. % mod operatörü
13. Kısaltılmış atama operatörleri
14. ++ ve --
15. Karşılaştırma operatörleri
16. Mantıksal operatörler
17. if
18. if-else
19. else if
20. Üçlü koşul operatörü

## Design

### Lesson content

Each of the 10 topics gets a `Lesson` populated exactly like topics 1-10 in
`LessonManager.cpp::applyIntroLessonContent` (same struct: `explanation`,
`syntax`, `exampleCode`, `lineExplanations`, `commonMistakes`). A new
function, `applySection2LessonContent(std::vector<Lesson>& lessons)`,
mirrors `applyIntroLessonContent`'s positional-index pattern (topics 11-20
sit at `lessons[10..19]`, since the seed table is authored in strict
ascending id order) and is called from the same place `applyIntroLessonContent`
is called today (`LessonManager`'s constructor/load path).

### Question content

Each of the 10 topics gets exactly 29 hand-written `Question` entries,
appended to `QuestionManager`'s constructor after the existing 72, using
sequential ids 73-362 (10 × 29 = 290; topic 11 gets ids 73-101, topic 12
gets 102-130, ... topic 20 gets 334-362). Per-topic type/difficulty
distribution (fixed across all 10 topics for consistency, matching the
existing question bank's type vocabulary from `Enums.h`):

| Type            | Count | Difficulty spread            |
|-----------------|-------|-------------------------------|
| MultipleChoice  | 8     | 3 VeryEasy/Easy, 3 Medium, 2 Hard |
| TrueFalse       | 6     | 2 VeryEasy, 2 Easy, 2 Medium  |
| FillBlank       | 6     | 3 Easy, 3 Medium              |
| CompleteLine    | 2     | Medium                        |
| PredictOutput   | 2     | Medium, Hard                  |
| FindError       | 2     | Medium, Hard                  |
| FixCode         | 1     | Hard                          |
| OrderCode       | 1     | Medium                        |
| WriteCode       | 1     | Hard                          |
| **Total**       | **29**|                               |

`baseXp` follows the existing convention already visible in topics 1-10
(`VeryEasy=5, Easy=10, Medium=20`) and extends it with `Hard=30` — topics
1-10 never used non-`WriteCode` `Hard` questions, so this phase establishes
`Hard=30` for every type except `WriteCode`, which keeps the existing
precedent of `baseXp=40` for `Hard`-difficulty `WriteCode` questions
(ids 71/72 already use this exact value).

Every question is graded by the existing, unmodified `QuizEngine::evaluate`
and `computeCorrectAnswerDisplay` — no new question types or grading logic.
`acceptedAnswers` for `MultipleChoice` uses the same lowercase
`"a"/"b"/"c"/"d"` letter convention as the existing bank; `TrueFalse` uses
`"1"` (true) / `"2"` (false) exactly as topics 1-10 do.

### No `Application.cpp` changes needed

`Application::openTopic` already gates on `lesson->explanation.empty()`
(`src/Application.cpp:230`) and `runTopicQuiz` already works generically
for any topic id with any nonzero question count (`src/Application.cpp:265`,
sorts by difficulty and applies Phase 12's adaptive selection already).
Adding real lesson + question content to topics 11-20 is sufficient to
"activate" them everywhere in the app — topic browser, quiz flow, mistake
tracking, XP/leveling, adaptive difficulty, hints — with zero code changes
outside `LessonManager.cpp` and `QuestionManager.cpp`.

## Testing / verification for this phase

- `tests/LessonManagerTests.cpp`: `LessonManager_TopicsElevenToHundredHaveNoContentYet`
  is replaced by two tests — `LessonManager_TopicsElevenToTwentyHaveRealContent`
  (mirrors the existing topics-1-10 test) and
  `LessonManager_TopicsTwentyOneToHundredHaveNoContentYet` (narrows the
  empty-content range to what's still actually true after this phase).
- `tests/QuestionManagerTests.cpp`: `QuestionManager_NoDuplicateQuestionIds`'s
  topic-range loop widens from `1..10` to `1..20`; a new test,
  `QuestionManager_EveryTopicElevenToTwentyHasAtLeastTwentyNineQuestions`,
  asserts `questionsForTopic(id).size() >= 29` for topics 11-20.
- Manual verification: open topic 11 end-to-end (lesson displays, quiz runs
  to completion with adaptive difficulty engaging identically to topic 1's
  established behavior, XP/level update, topic status marked), confirming
  no special-casing was needed — content-only activation works as designed.

## Scope cuts (deliberate)

- **No dynamic-generator wiring for these topics.** Dynamic generation
  (`Hızlı Test`) remains scoped to its existing 2 generators
  (`IntArithmeticPredictGenerator`, `BoolOutputPredictGenerator`); expanding
  the generator library is Phase 23's job, not this content phase's.
- **No Section 2 exam.** Per-section exams are Phase 22's job, once all
  content phases (13-21) are done — a Section 2 exam today would need to
  pick from a stable, complete question set, which this phase provides but
  does not itself consume.
- **Section 1's question density is not revisited** (see Scope decision
  above).

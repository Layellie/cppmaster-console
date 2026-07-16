# CppMaster Console — Bölüm 4 İçerik Genişletmesi Design (Phase 15)

## Context

Third of nine section-by-section content phases (13-21) closing the
roadmap's lesson-content and question-bank gaps for topics 11-100.
This phase covers Section 4 (topics 31-40: "Diziler, vector ve string"),
following the exact same architecture, scope decisions, and testing
approach established and merged in Phases 13-14 (commits
`6df525f..cf6b6f1` and `7987f8c..f62ea67`), which this document does not
repeat in full.

## Topics covered (Section 4, sectionId 4, from `LessonManager.cpp`'s
`kTopicSeeds`)

31. Normal diziler
32. Dizi elemanlarını değiştirme
33. std::array
34. vector
35. push_back() ve pop_back()
36. size(), front(), back() ve at()
37. string
38. String birleştirme
39. length() ve empty()
40. substr() ve find()

## Design (identical architecture to Phases 13-14)

- **Lesson content**: `applySection4LessonContent(std::vector<Lesson>&)`
  in a new file `src/LessonContentSection4.cpp`, declared in
  `src/LessonContent.h` alongside the existing Phase 13/14 declarations,
  called from `LessonManager`'s constructor after the Phase 14 call.
  Writes into `lessons[30]` through `lessons[39]` (topics 31-40).
- **Question content**: `appendSection4Questions(std::vector<Question>&)`
  in a new file `src/QuestionsSection4.cpp`, declared in
  `src/QuestionContent.h` alongside the existing declarations, called
  from `QuestionManager`'s constructor after the Phase 14 call. Ids
  653-942 (10 topics × 29 questions), continuing directly from Phase 14's
  last id (652).
- **Same fixed per-topic type/difficulty/baseXp distribution table** as
  Phases 13-14 (8 MultipleChoice, 6 TrueFalse, 6 FillBlank, 2
  CompleteLine, 2 PredictOutput, 2 FindError, 1 FixCode, 1 OrderCode, 1
  WriteCode; baseXp 5/10/20/30/40 for VeryEasy/Easy/Medium/Hard/Hard-
  WriteCode).
- **No `Application.cpp` changes needed** — same reasoning as prior
  phases.
- **`questions_.reserve(652)` becomes `questions_.reserve(942)`**.

## Content-accuracy notes specific to this section (lessons learned from
Phases 13-14's fix cycles — every content phase so far has needed at
least one fix-and-re-review round for a claim that looked right but
wasn't when actually compiled; this section has its own sharp edges)

- **Array/vector indexing is 0-based, and out-of-bounds access via `[]`
  is undefined behavior, not a caught error** — `.at()` throws
  (`std::out_of_range`), `[]` does not check bounds. Any question
  claiming `[]` "throws" or "is safely checked" would be factually wrong;
  the plan's authored content must get this distinction right and,
  where relevant, correctly attribute bounds-checking only to `.at()`.
- **`std::array`'s size is fixed at compile time (template parameter)**,
  unlike `std::vector`, which can grow/shrink at runtime via
  `push_back`/`pop_back`. A question implying `std::array` can be resized
  would be wrong.
- **`pop_back()` on an empty vector is undefined behavior** (it does not
  throw, and does not "do nothing safely") — must not be described as
  a safe no-op.
- **`std::string`'s `find()` returns `std::string::npos` (not `-1`) when
  not found** — a comparison question must use `== std::string::npos`,
  not `== -1`, or explicitly explain the `npos` sentinel if a numeric
  comparison is shown for illustration only.
- **`substr(pos, len)`'s second argument is a LENGTH, not an end
  position** — unlike some other languages' slice conventions; a
  question computing `substr` results must get this arithmetic right
  (e.g. `"Merhaba".substr(2, 3)` is `"rha"`, not up to index 3).
- Given three real, compiler-verified bugs slipped through in Phases
  13-14 despite careful authoring, the plan author will hand-verify
  every `.at()`/`[]`/`push_back`/`pop_back`/`find`/`substr` claim against
  actual C++ semantics before finalizing the plan, and task reviewers are
  expected to continue independently compiling any content whose
  correctness is not immediately obvious from inspection — this has
  consistently been the check that actually catches real errors in this
  project, not a formality.

## Testing / verification for this phase

Same pattern as Phases 13-14:
- `tests/LessonManagerTests.cpp`: extend the topics-with-content range to
  11-40 and narrow the no-content range to 41-100 (renaming, not
  duplicating, Phase 14's own two tests).
- `tests/QuestionManagerTests.cpp`: add
  `QuestionManager_EveryTopicThirtyOneToFortyHasAtLeastTwentyNineQuestions`.
- Manual verification: open topic 34 ("vector") end-to-end.

## Scope cuts (deliberate, same as prior phases)

- No dynamic-generator wiring, no Section 4 exam, earlier sections'
  question density is not revisited.

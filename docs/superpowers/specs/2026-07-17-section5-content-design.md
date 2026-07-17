# CppMaster Console — Bölüm 5 İçerik Genişletmesi Design (Phase 16)

## Context

Fourth of nine section-by-section content phases (13-21) closing the
roadmap's lesson-content and question-bank gaps for topics 11-100.
This phase covers Section 5 (topics 41-50: "Fonksiyonlar"), following
the exact same architecture, scope decisions, and testing approach
established and merged in Phases 13-15 (commits `6df525f..cf6b6f1`,
`7987f8c..f62ea67`, `23d1628..3d230f9`), which this document does not
repeat in full.

## Topics covered (Section 5, sectionId 5, from `LessonManager.cpp`'s
`kTopicSeeds`)

41. Parametresiz fonksiyon
42. Parametre alan fonksiyon
43. Değer döndüren fonksiyon
44. Fonksiyon prototipi
45. Varsayılan parametre
46. Fonksiyon aşırı yükleme
47. Değer ile parametre gönderme
48. Referans ile parametre gönderme
49. const referans
50. Recursion

## Design (identical architecture to Phases 13-15)

- **Lesson content**: `applySection5LessonContent(std::vector<Lesson>&)`
  in a new file `src/LessonContentSection5.cpp`, declared in
  `src/LessonContent.h` alongside the existing Phase 13-15 declarations,
  called from `LessonManager`'s constructor after the Phase 15 call.
  Writes into `lessons[40]` through `lessons[49]` (topics 41-50).
- **Question content**: `appendSection5Questions(std::vector<Question>&)`
  in a new file `src/QuestionsSection5.cpp`, declared in
  `src/QuestionContent.h` alongside the existing declarations, called
  from `QuestionManager`'s constructor after the Phase 15 call. Ids
  943-1232 (10 topics × 29 questions), continuing directly from Phase
  15's last id (942).
- **Same fixed per-topic type/difficulty/baseXp distribution table** as
  Phases 13-15 (8 MultipleChoice, 6 TrueFalse, 6 FillBlank, 2
  CompleteLine, 2 PredictOutput, 2 FindError, 1 FixCode, 1 OrderCode, 1
  WriteCode; baseXp 5/10/20/30/40 for VeryEasy/Easy/Medium/Hard/Hard-
  WriteCode).
- **No `Application.cpp` changes needed** — same reasoning as prior
  phases.
- **`questions_.reserve(942)` becomes `questions_.reserve(1232)`**.

## Content-accuracy notes specific to this section (every prior content
phase needed at least one compiler-verified fix for a claim that looked
right but wasn't — functions have their own well-known sharp edges)

- **Function overloading is resolved by the parameter list (types and/or
  count), never by return type alone.** Two functions with identical
  parameter lists but different return types are NOT valid overloads —
  this is a genuine compile error, and a very common misconception. Any
  question about overloading must get this exactly right.
- **Default parameters must be trailing.** In a single declaration, once
  a parameter has a default value, every parameter after it must also
  have one. `void f(int a, int b = 5)` is valid; `void f(int a = 5, int b)`
  is a compile error. If a function has both a prototype (declaration)
  and a separate definition, the default value is specified in exactly
  one of them (conventionally the declaration) — the plan's authored
  content will not test this exact multi-declaration nuance to keep
  scope aligned with the brief's single-file lesson intent, but must
  never claim defaults can be specified in the middle of a parameter list.
- **Pass by value creates an independent copy** — modifying the
  parameter inside the function never affects the caller's original
  argument. **Pass by reference (`&`)** lets the function modify the
  caller's original variable directly. **`const` reference** combines
  the efficiency of not copying with the safety of not allowing
  modification — the function still cannot change the caller's value.
- **Recursion requires a base case** to terminate; every call gets its
  own independent set of local variables/parameters (a new stack frame).
  Missing or unreachable base cases cause unbounded recursion, which
  exhausts the call stack (stack overflow) rather than looping forever
  cleanly like an infinite `while` loop would.
- **A function prototype (forward declaration) lets a function be called
  before its full definition appears later in the same file** — the
  compiler only needs the signature to check call sites; the body can
  come after `main()` or anywhere else later in the translation unit.
- Given three real, compiler-verified bugs have already slipped through
  careful authoring in each of Phases 13-15, the plan author will
  hand-verify every overloading/default-parameter/pass-by-X/recursion
  claim against actual C++ semantics before finalizing the plan, and
  task reviewers are expected to continue independently compiling any
  content whose correctness is not immediately obvious — this remains
  the check that actually catches real errors in this project.

## Testing / verification for this phase

Same pattern as Phases 13-15:
- `tests/LessonManagerTests.cpp`: extend the topics-with-content range to
  11-50 and narrow the no-content range to 51-100 (renaming, not
  duplicating, Phase 15's own two tests).
- `tests/QuestionManagerTests.cpp`: add
  `QuestionManager_EveryTopicFortyOneToFiftyHasAtLeastTwentyNineQuestions`.
- Manual verification: open topic 43 ("Değer döndüren fonksiyon")
  end-to-end.

## Scope cuts (deliberate, same as prior phases)

- No dynamic-generator wiring, no Section 5 exam, earlier sections'
  question density is not revisited.

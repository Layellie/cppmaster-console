# CppMaster Console — Bölüm 8 İçerik Genişletmesi Design (Phase 19)

## Context

Seventh of nine section-by-section content phases (13-21) closing the
roadmap's lesson-content and question-bank gaps for topics 11-100.
This phase covers Section 8 (topics 71-80: "İleri nesne yönelimli
özellikler"), following the exact same architecture, scope decisions,
and testing approach established and merged in Phases 13-18 (commits
`6df525f..cf6b6f1`, `7987f8c..f62ea67`, `23d1628..3d230f9`,
`4955846..f53d6c0`, `bcdfbba..b5fbe3d`, `f5c69af..0f80e2e`), which this
document does not repeat in full.

## Topics covered (Section 8, sectionId 8, from `LessonManager.cpp`'s
`kTopicSeeds`)

71. virtual
72. override
73. Soyut sınıf
74. Polimorfizm
75. this pointer'ı
76. static sınıf üyesi
77. Operatör aşırı yükleme
78. Template fonksiyon
79. namespace
80. auto

## Design (identical architecture to Phases 13-18)

- **Lesson content**: `applySection8LessonContent(std::vector<Lesson>&)`
  in a new file `src/LessonContentSection8.cpp`, declared in
  `src/LessonContent.h` alongside the existing Phase 13-18
  declarations, called from `LessonManager`'s constructor after the
  Phase 18 call. Writes into `lessons[70]` through `lessons[79]`
  (topics 71-80).
- **Question content**: `appendSection8Questions(std::vector<Question>&)`
  in a new file `src/QuestionsSection8.cpp`, declared in
  `src/QuestionContent.h` alongside the existing declarations, called
  from `QuestionManager`'s constructor after the Phase 18 call. Ids
  1813-2102 (10 topics x 29 questions), continuing directly from Phase
  18's last id (1812).
- **Same fixed per-topic type/difficulty/baseXp distribution table** as
  Phases 13-18 (8 MultipleChoice, 6 TrueFalse, 6 FillBlank, 2
  CompleteLine, 2 PredictOutput, 2 FindError, 1 FixCode, 1 OrderCode, 1
  WriteCode; baseXp 5/10/20/30/40 for VeryEasy/Easy/Medium/Hard/Hard-
  WriteCode).
- **No `Application.cpp` changes needed** — same reasoning as prior
  phases.
- **`questions_.reserve(1812)` becomes `questions_.reserve(2102)`**.

## Content-accuracy notes specific to this section (every prior content
phase needed at least one compiler-verified fix for a claim that looked
right but wasn't — this section covers the most conceptually dense
material yet: runtime polymorphism, abstract classes, static members,
operator overloading, templates, and namespaces — every claim below is
directly compile- and/or run-testable and MUST be verified that way,
not just asserted)

- **Without `virtual`, calling a "redefined" base-class method through
  a base-class pointer/reference to a derived object calls the BASE
  class's version** (static/compile-time binding), even though the
  object is actually a derived instance. **With `virtual`, the SAME
  call invokes the DERIVED class's version instead** (dynamic/runtime
  dispatch) — this is the entire point of `virtual` and must be
  demonstrated by actually compiling and RUNNING both versions side by
  side to show the different printed output, not just asserted.
- **`override` (C++11) explicitly marks a derived method as overriding
  a base `virtual` method.** If the marked method's signature does NOT
  actually match any virtual function in the base class (e.g. a typo in
  the name, or a mismatched parameter/const-ness), using `override`
  causes a **compile error** — this is `override`'s entire purpose (to
  catch accidental non-overrides that would otherwise silently compile
  as an unrelated new method). Verify this compile error directly.
- **A class with at least one pure virtual function
  (`virtual void f() = 0;`) is abstract and CANNOT be instantiated
  directly** — `AbstractClass a;` is a genuine compile error. **A
  derived class must override ALL of the base's pure virtual functions
  to become concrete (instantiable)**; if any pure virtual is left
  un-overridden, the derived class remains abstract too, and
  instantiating it is also a compile error. Verify both compile errors.
- **`this` is an implicit pointer to the current object inside a
  non-static member function**, with type `ClassName*`. `this->uye` and
  bare `uye` refer to the same thing inside a member function.
  **Returning `*this` by reference from a method enables method
  chaining** (`obj.setA(1).setB(2)`) — verify this compiles and runs
  with the expected chained result.
- **A `static` data member is shared across ALL instances of the
  class — it is not per-object.** Changing it through one object's
  method is visible through every other instance/access of the same
  class. This project will use `static inline` (C++17) member
  initialization inside the class body to avoid needing a separate
  out-of-class definition, keeping the lesson's syntax minimal. Verify
  the sharing behavior by compiling and running a program that
  modifies the static member via one object and reads it via another.
- **A `static` member FUNCTION has no implicit `this` and therefore
  cannot directly access the class's non-static (per-object) members**
  — attempting to do so is a genuine compile error. Verify this.
- **Operator overloading** lets user-defined types use operators like
  `+`, `==`, `<<`. When overloaded as a member function, the left-hand
  operand is the implicit `*this`. Verify any traced arithmetic/
  comparison result by actually compiling and running the operator.
- **A function template's type parameter is deduced from the
  arguments at compile time** (or can be explicitly specified,
  `topla<int>(3, 4)`); a single template can be instantiated for
  multiple different types in the same program. Verify by compiling
  and running the SAME template function called with two different
  types (e.g. `int` and `double`) and confirming both produce correct,
  type-appropriate output.
- **`namespace` groups related names to avoid naming collisions**;
  names inside a namespace are accessed via `NamespaceName::name` or
  brought into scope with `using namespace NamespaceName;`. Two
  different namespaces may each define a same-named function/variable
  without conflict, unlike two same-scope unscoped-enum values (a
  contrast worth drawing since Phase 18 covered that exact enum
  gotcha) — verify by compiling two namespaces with a colliding name
  and confirming qualified access to each independently compiles and
  runs correctly.
- **`auto` deduces a variable's type from its initializer at compile
  time and therefore REQUIRES an initializer** — `auto x;` (no
  initializer) is a genuine compile error, since there is nothing to
  deduce the type from. Verify this compile error directly.
- Given real, compiler-verified bugs have already slipped through
  careful authoring in every phase so far (13-18), and this section's
  virtual-dispatch/abstract-class/static-member/template content is
  the most conceptually dense yet, the plan author will hand-verify
  every claim above by actually compiling (and, for dispatch/sharing/
  chaining/template claims, RUNNING) the relevant snippet before
  finalizing the plan — matching the discipline already applied in
  Phases 17-18 — and task reviewers are expected to continue doing the
  same for anything not immediately obvious.

## Testing / verification for this phase

Same pattern as Phases 13-18:
- `tests/LessonManagerTests.cpp`: extend the topics-with-content range to
  11-80 and narrow the no-content range to 81-100 (renaming, not
  duplicating, Phase 18's own two tests).
- `tests/QuestionManagerTests.cpp`: add
  `QuestionManager_EveryTopicSeventyOneToEightyHasAtLeastTwentyNineQuestions`.
- Manual verification: open topic 74 ("Polimorfizm") end-to-end.

## Scope cuts (deliberate, same as prior phases)

- No dynamic-generator wiring, no Section 8 exam, earlier sections'
  question density is not revisited.
- No multiple inheritance, no virtual destructors as a separate deep
  dive (mentioned only in passing if relevant to a polymorphism
  example), no template classes (only function templates), no
  operator overloading beyond simple arithmetic/comparison/stream
  examples, no `constexpr`/`decltype` — these are reasonable candidates
  for later, deeper phases but out of scope for this Foundation-tier
  "advanced OOP features" introduction.

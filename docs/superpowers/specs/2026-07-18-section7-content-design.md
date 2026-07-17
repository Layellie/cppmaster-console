# CppMaster Console — Bölüm 7 İçerik Genişletmesi Design (Phase 18)

## Context

Sixth of nine section-by-section content phases (13-21) closing the
roadmap's lesson-content and question-bank gaps for topics 11-100.
This phase covers Section 7 (topics 61-70: "Struct ve nesne yönelimli
programlama"), following the exact same architecture, scope decisions,
and testing approach established and merged in Phases 13-17 (commits
`6df525f..cf6b6f1`, `7987f8c..f62ea67`, `23d1628..3d230f9`,
`4955846..f53d6c0`, `bcdfbba..b5fbe3d`), which this document does not
repeat in full.

## Topics covered (Section 7, sectionId 7, from `LessonManager.cpp`'s
`kTopicSeeds`)

61. struct
62. enum
63. enum class
64. Sınıf ve nesne
65. Constructor
66. Destructor
67. private ve public
68. Getter ve setter
69. Kalıtım
70. protected

## Design (identical architecture to Phases 13-17)

- **Lesson content**: `applySection7LessonContent(std::vector<Lesson>&)`
  in a new file `src/LessonContentSection7.cpp`, declared in
  `src/LessonContent.h` alongside the existing Phase 13-17
  declarations, called from `LessonManager`'s constructor after the
  Phase 17 call. Writes into `lessons[60]` through `lessons[69]`
  (topics 61-70).
- **Question content**: `appendSection7Questions(std::vector<Question>&)`
  in a new file `src/QuestionsSection7.cpp`, declared in
  `src/QuestionContent.h` alongside the existing declarations, called
  from `QuestionManager`'s constructor after the Phase 17 call. Ids
  1523-1812 (10 topics x 29 questions), continuing directly from Phase
  17's last id (1522).
- **Same fixed per-topic type/difficulty/baseXp distribution table** as
  Phases 13-17 (8 MultipleChoice, 6 TrueFalse, 6 FillBlank, 2
  CompleteLine, 2 PredictOutput, 2 FindError, 1 FixCode, 1 OrderCode, 1
  WriteCode; baseXp 5/10/20/30/40 for VeryEasy/Easy/Medium/Hard/Hard-
  WriteCode).
- **No `Application.cpp` changes needed** — same reasoning as prior
  phases.
- **`questions_.reserve(1522)` becomes `questions_.reserve(1812)`**.

## Content-accuracy notes specific to this section (every prior content
phase needed at least one compiler-verified fix for a claim that looked
right but wasn't — introductory OOP has its own well-known sharp edges,
mostly around default access and constructor/destructor lifecycle
rules, which are precisely testable by compiling and running short
programs)

- **`struct` members are `public` by default; `class` members are
  `private` by default.** This is the ONLY functional difference
  between `struct` and `class` in C++ (both can have constructors,
  destructors, methods, inheritance, etc.) — content must state this
  exactly, never implying `struct` cannot have methods/constructors or
  that `class` is somehow more "capable."
- **Unscoped `enum` values implicitly convert to `int`** and are
  visible directly in the enclosing scope (risking name collisions
  between two enums that reuse a value name in the same scope).
  **`enum class` (scoped enum) values do NOT implicitly convert to
  `int`** (a `static_cast<int>` is required) **and must always be
  qualified with the enum's name** (`Renk::Kirmizi`, never bare
  `Kirmizi`) — this scoping is the entire reason `enum class` exists
  and prevents the unscoped enum's name-collision problem.
- **If a class/struct defines ANY user-provided constructor, the
  compiler no longer auto-generates a default (no-argument)
  constructor.** Attempting `ClassName nesne;` after only a
  parameterized constructor was defined is a genuine compile error —
  a default constructor must be explicitly provided too if
  no-argument construction is still needed. This is the single most
  common constructor-related gotcha and must be verified by actually
  compiling both the failing and the fixed version.
- **A class/struct has exactly one destructor, which takes no
  parameters and cannot be overloaded** — unlike constructors, which
  can be overloaded by parameter list.
- **Destructors run automatically when an object goes out of scope**
  (for a stack-allocated/automatic object) **or when `delete` is
  called** (for a heap-allocated object via `new`, connecting back to
  Phase 17's `new`/`delete` content) — a heap object whose pointer is
  never `delete`d never has its destructor run (this is part of why
  forgetting `delete` is a leak, not just of raw memory but of any
  cleanup the destructor would have performed).
- **`private` members are accessible only from within the class's own
  member functions** (this app's scope does not need to cover
  `friend`). **`public` members are accessible from anywhere.**
  **`protected` members behave like `private` to outside code, but ARE
  accessible from a derived class's own member functions** — this is
  the one genuinely new rule `protected` adds beyond `private`/`public`,
  and the natural reason topic 70 (`protected`) is sequenced right
  after topic 69 (`Kalıtım`/inheritance): protected only makes sense to
  teach once inheritance already exists conceptually.
  ALL THREE of these accessibility claims are directly compile-testable
  (accessing a private/protected member from outside the class is a
  genuine compile error; accessing a protected member from a derived
  class's own method compiles fine) and must be verified by compiling
  both the failing and succeeding snippets, not just asserted.
- **A derived class does not gain direct access to its base class's
  `private` members** (even though those members still physically
  exist in every derived object) — only `protected`/`public` base
  members are directly usable in derived-class code. This is a genuine,
  compile-verifiable distinction from `protected`, and content must not
  conflate "derived class inherits the members" (true, they exist) with
  "derived class can directly access them" (false for `private` base
  members).
- **Construction order in inheritance: the base class's constructor
  runs to completion BEFORE the derived class's own constructor body
  runs.** **Destruction order is the exact reverse: the derived class's
  destructor runs BEFORE the base class's destructor.** Both claims are
  directly verifiable by compiling and running a program with
  print statements in each constructor/destructor and observing the
  actual printed order — this project's established discipline
  requires exactly this kind of execution-based verification for any
  claim about program output, and construction/destruction ordering is
  exactly the kind of subtle-but-checkable claim that has tripped up
  prior phases' initial authoring.
- **Getter/setter naming in this app's own generated content will use
  a clear, consistent Turkish-flavored convention** (e.g. `getYas()` /
  `setYas(int)` for a member `yas`) — this is a convention, not a
  language rule, and content must present it as such (a common pattern
  for controlled access), not as something the compiler enforces.
- Given real, compiler-verified bugs have already slipped through
  careful authoring in every phase so far (13-17), and this section's
  constructor/destructor-lifecycle and access-control content is
  exactly the kind of thing that is easy to get subtly wrong (e.g.
  misremembering construction/destruction order, or whether `struct`
  can have constructors), the plan author will hand-verify every such
  claim by actually compiling (and, for ordering claims, running) the
  relevant snippet before finalizing the plan — matching the discipline
  already applied in Phase 17 (where ~20 of the trickiest runtime
  claims were compiled and executed standalone before dispatch) — and
  task reviewers are expected to continue doing the same for anything
  not immediately obvious.

## Testing / verification for this phase

Same pattern as Phases 13-17:
- `tests/LessonManagerTests.cpp`: extend the topics-with-content range to
  11-70 and narrow the no-content range to 71-100 (renaming, not
  duplicating, Phase 17's own two tests).
- `tests/QuestionManagerTests.cpp`: add
  `QuestionManager_EveryTopicSixtyOneToSeventyHasAtLeastTwentyNineQuestions`.
- Manual verification: open topic 65 ("Constructor") end-to-end.

## Scope cuts (deliberate, same as prior phases)

- No dynamic-generator wiring, no Section 7 exam, earlier sections'
  question density is not revisited.
- No `friend`, no virtual functions/polymorphism, no operator
  overloading, no copy/move constructors, no static members — these
  are reasonable candidates for a later, deeper OOP section but are out
  of scope for this Foundation-tier introduction to structs/classes/
  single-level inheritance/access control.

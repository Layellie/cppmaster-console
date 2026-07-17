# CppMaster Console — Bölüm 6 İçerik Genişletmesi Design (Phase 17)

## Context

Fifth of nine section-by-section content phases (13-21) closing the
roadmap's lesson-content and question-bank gaps for topics 11-100.
This phase covers Section 6 (topics 51-60: "Lambda, pointer ve
bellek"), following the exact same architecture, scope decisions, and
testing approach established and merged in Phases 13-16 (commits
`6df525f..cf6b6f1`, `7987f8c..f62ea67`, `23d1628..3d230f9`,
`4955846..f53d6c0`), which this document does not repeat in full.

## Topics covered (Section 6, sectionId 6, from `LessonManager.cpp`'s
`kTopicSeeds`)

51. Lambda fonksiyonları
52. Pointer tanımlama
53. & adres operatörü
54. * dereference operatörü
55. nullptr
56. Pointer ile dizi dolaşma
57. new
58. delete
59. Dinamik dizi
60. Referans değişkeni

## Design (identical architecture to Phases 13-16)

- **Lesson content**: `applySection6LessonContent(std::vector<Lesson>&)`
  in a new file `src/LessonContentSection6.cpp`, declared in
  `src/LessonContent.h` alongside the existing Phase 13-16
  declarations, called from `LessonManager`'s constructor after the
  Phase 16 call. Writes into `lessons[50]` through `lessons[59]`
  (topics 51-60).
- **Question content**: `appendSection6Questions(std::vector<Question>&)`
  in a new file `src/QuestionsSection6.cpp`, declared in
  `src/QuestionContent.h` alongside the existing declarations, called
  from `QuestionManager`'s constructor after the Phase 16 call. Ids
  1233-1522 (10 topics x 29 questions), continuing directly from Phase
  16's last id (1232).
- **Same fixed per-topic type/difficulty/baseXp distribution table** as
  Phases 13-16 (8 MultipleChoice, 6 TrueFalse, 6 FillBlank, 2
  CompleteLine, 2 PredictOutput, 2 FindError, 1 FixCode, 1 OrderCode, 1
  WriteCode; baseXp 5/10/20/30/40 for VeryEasy/Easy/Medium/Hard/Hard-
  WriteCode).
- **No `Application.cpp` changes needed** — same reasoning as prior
  phases.
- **`questions_.reserve(1232)` becomes `questions_.reserve(1522)`**.

## Content-accuracy notes specific to this section (every prior content
phase needed at least one compiler-verified fix for a claim that looked
right but wasn't — raw pointers and manual memory management are the
single riskiest topic area in the whole curriculum for exactly this
failure mode, so this phase requires even more care than usual)

- **`int* p, q;` declares `p` as `int*` but `q` as a plain `int`, NOT a
  second pointer.** The `*` binds to the declarator (the variable name),
  not to the base type — this is a well-known, genuine C++ gotcha and
  must be described exactly this way, never as "both p and q become
  pointers."
- **Dereferencing a null, uninitialized, or dangling pointer is
  undefined behavior, not a guaranteed crash.** On the platforms this
  app's questions describe, it usually manifests as a crash (access
  violation / segfault), so it is acceptable to say a snippet "genellikle
  çöker" (usually crashes) or "erişim ihlaline (access violation) yol
  açar", but content must never claim UB "always" or "guaranteed"
  crashes, matching this project's established discipline around UB
  claims (the same class of imprecision already caught and fixed in
  Phase 15 for `pop_back()` on an empty container).
- **`delete` must match `new`, and `delete[]` must match `new[]`.**
  Using the wrong form (`delete` on an array from `new[]`, or vice
  versa) is undefined behavior — a genuine bug class, but (per the point
  above) must not be described as an unconditional crash.
- **Forgetting `delete`/`delete[]` after `new`/`new[]` is a memory
  leak, not a crash.** The program keeps running normally; it simply
  never reclaims that memory. Leak questions must not claim the program
  crashes or behaves incorrectly at that point — only that memory is
  wasted for the rest of the program's lifetime.
- **Double-`delete`-ing the same pointer is undefined behavior.** After
  a `delete`, the pointer is dangling — using or deleting it again is a
  genuine bug, but again must not be phrased as a guaranteed crash.
- **Pointer arithmetic advances by `sizeof(element type)` bytes, not by
  1 byte** — `ptr + 1` on an `int*` moves 4 bytes (typically), not 1.
  Any question tracing pointer arithmetic must get this right.
- **References vs. pointers (this section's natural closing contrast,
  topic 60 following directly after topics 52-59's pointer coverage):**
  a reference must be initialized at declaration and can never be
  rebound to refer to something else afterward (unlike a pointer, which
  can be reassigned and can be null). This project already covered
  reference *parameters* in Phase 16 (topics 48-49) — topic 60's content
  is about references as a general variable concept and should
  emphasize the contrast with pointers (no null state, no rebinding, no
  arithmetic) rather than repeating Phase 16's parameter-passing content
  verbatim.
- **`&` on a variable gives its address; `*` on a pointer gives the
  value it points to** — these are inverse operations
  (`*(&x) == x` and `&(*p) == p` when `p` is valid), and content should
  reinforce this relationship directly since it is the conceptual core
  of topics 53-54.
- **Lambda capture-by-value copies are `const` inside the lambda body
  by default** — modifying a by-value-captured variable inside the
  lambda requires the `mutable` keyword, and even then only affects the
  lambda's own internal copy, never the original variable outside
  (mirroring the pass-by-value semantics already covered in Phase 16,
  which the lesson content should draw the parallel to explicitly).
  Capture-by-reference (`[&x]` or `[&]`) does let the lambda modify the
  original variable, exactly like a reference parameter.
- Given real, compiler-verified bugs have already slipped through
  careful authoring in every phase so far (13-16), and this section's
  raw-pointer/memory content is inherently higher-risk than any
  previous section, the plan author will hand-verify every
  pointer-declaration/dereference/new-delete/lambda-capture claim
  against actual C++ semantics before finalizing the plan, and task
  reviewers are expected to continue independently compiling (and, for
  UB cases, running) any content whose correctness or runtime behavior
  is not immediately obvious — this remains the check that actually
  catches real errors in this project. Questions probing *undefined*
  behavior (dereferencing freed/null pointers) will be phrased as
  compile-time-safe code whose exact runtime output is not itself the
  graded answer — e.g. FindError/FixCode questions will target the
  *bug's identification and fix* (matching this project's own
  established FixCode/FindError answer-format convention), not a
  specific crash output, since UB's actual manifestation is not portably
  predictable and must not be asserted as a fixed graded value.

## Testing / verification for this phase

Same pattern as Phases 13-16:
- `tests/LessonManagerTests.cpp`: extend the topics-with-content range to
  11-60 and narrow the no-content range to 61-100 (renaming, not
  duplicating, Phase 16's own two tests).
- `tests/QuestionManagerTests.cpp`: add
  `QuestionManager_EveryTopicFiftyOneToSixtyHasAtLeastTwentyNineQuestions`.
- Manual verification: open topic 57 ("new") end-to-end.

## Scope cuts (deliberate, same as prior phases)

- No dynamic-generator wiring, no Section 6 exam, earlier sections'
  question density is not revisited.
- No actual pointer-dereference-of-invalid-memory is ever executed by
  any question's *graded* answer — all pointer/memory questions are
  static-analysis style (predict output of well-defined code, identify
  the bug in visibly-wrong code, fix the bug) so that grading remains
  deterministic; the app never compiles or runs student-submitted code.

# CppMaster Console — Bölüm 10 İçerik Genişletmesi Design (Phase 21)

## Context

Last of nine section-by-section content phases (13-21) closing the
roadmap's lesson-content and question-bank gaps for topics 11-100.
This phase covers Section 10 (topics 91-100: "STL algoritmaları, dosya
işlemleri, istisna yönetimi ve akıllı işaretçiler"), following the
exact same architecture, scope decisions, and testing approach
established and merged in Phases 13-20 (commits `6df525f..cf6b6f1`,
`7987f8c..f62ea67`, `23d1628..3d230f9`, `4955846..f53d6c0`,
`bcdfbba..b5fbe3d`, `f5c69af..0f80e2e`, `a7794da..5089325`,
`c75308a..4793f79`), which this document does not repeat in full.

## Topics covered (Section 10, sectionId 10, from `LessonManager.cpp`'s
`kTopicSeeds`)

91. sort()
92. reverse()
93. find()
94. count()
95. min(), max() ve max_element()
96. accumulate()
97. Dosyaya yazma
98. Dosyadan okuma
99. try-catch
100. unique_ptr

## Design (identical architecture to Phases 13-20)

- **Lesson content**: `applySection10LessonContent(std::vector<Lesson>&)`
  in a new file `src/LessonContentSection10.cpp`, declared in
  `src/LessonContent.h` alongside the existing Phase 13-20
  declarations, called from `LessonManager`'s constructor after the
  Phase 20 call. Writes into `lessons[90]` through `lessons[99]`
  (topics 91-100).
- **Question content**: `appendSection10Questions(std::vector<Question>&)`
  in a new file `src/QuestionsSection10.cpp`, declared in
  `src/QuestionContent.h` alongside the existing declarations, called
  from `QuestionManager`'s constructor after the Phase 20 call. Ids
  2393-2682 (10 topics x 29 questions), continuing directly from Phase
  20's last id (2392). **This is the last id range needed to reach the
  full 100-topic bank** (final id 2682, meaning all topics 1-100 will
  have >= 29 questions once this phase lands).
- **Same fixed per-topic type/difficulty/baseXp distribution table** as
  Phases 13-20 (8 MultipleChoice, 6 TrueFalse, 6 FillBlank, 2
  CompleteLine, 2 PredictOutput, 2 FindError, 1 FixCode, 1 OrderCode, 1
  WriteCode; baseXp 5/10/20/30/40 for VeryEasy/Easy/Medium/Hard/Hard-
  WriteCode).
- **Continuing Phase 20's fix**: MultipleChoice questions vary the
  correct answer's position roughly evenly across a/b/c/d (NOT always
  "a", the defect recorded for Sections 6-8).
- **No `Application.cpp` changes needed** — same reasoning as prior
  phases.
- **`questions_.reserve(2392)` becomes `questions_.reserve(2682)`**.
- File-I/O exampleCode (topics 97-98) writes to and reads from a
  throwaway path under the OS temp directory conceptually described in
  the lesson text — but since lesson `exampleCode` is illustrative text
  shown to the learner (not executed by the app), the actual
  compile/run verification during planning will use a real temp file
  path and delete it afterward, matching how this project already
  handles any filesystem-touching example.

## Content-accuracy notes specific to this section (every prior content
phase needed at least one compiler-verified fix for a claim that looked
right but wasn't — this section covers STL algorithms, file I/O,
exceptions, and smart pointers — every claim below is directly compile-
and/or run-testable and MUST be verified that way, not just asserted)

- **`std::sort(first, last)`** sorts a range in ascending order by
  default (using `operator<`); a custom comparator (a function, lambda,
  or `std::greater<T>`) as a third argument produces a different order
  (e.g. descending). Verify by compiling and running both the default
  and custom-comparator forms on the same unsorted data and confirming
  the two different outputs.
- **`std::reverse(first, last)`** reverses a range IN PLACE and returns
  `void` — it does not return a new container. Verify by compiling and
  running a reverse on a vector and printing the original variable
  afterward (not a return value) to confirm it mutated.
- **`std::find(first, last, value)`** returns an iterator to the first
  matching element, or `last` (the range's `end()`) if not found —
  comparing the result against `end()` is the correct way to check
  membership; dereferencing the result without that check when the
  value is absent is undefined behavior. Verify both the found and
  not-found paths by compiling and running.
- **`std::count(first, last, value)`** returns the NUMBER of matching
  elements (0 if none), not an iterator and not a boolean. Verify with
  a range containing 0, 1, and multiple matches.
- **`std::max_element(first, last)` / `std::min_element(first, last)`
  return an ITERATOR to the largest/smallest element, NOT the value
  itself** — a common real bug is printing the iterator or forgetting
  to dereference it (`*std::max_element(...)`). Also, `std::max(a, b)`
  / `std::min(a, b)` (the two-argument, non-iterator overloads) DO
  return values directly, not iterators — this contrast (element-wise
  `min`/`max` returning values vs. range-wise `min_element`/
  `max_element` returning iterators) is worth testing explicitly.
  Verify by compiling and running both forms and confirming the
  dereferenced iterator's value matches the expected maximum/minimum.
- **`std::accumulate(first, last, init)`** (from `<numeric>`) sums a
  range starting from `init`. **The type of `init` determines the
  accumulation's working type** — passing an `int` initial value (e.g.
  `0`) to accumulate a range of `double`s silently truncates every
  partial sum to `int`, producing a wrong (truncated) total; passing
  `0.0` instead fixes it. This is a classic, genuinely surprising
  `accumulate` bug and MUST be demonstrated by compiling and running
  both the buggy (`int` init) and correct (`double` init) versions on
  identical double data, showing the different (wrong vs. right)
  numeric outputs.
- **`std::ofstream`** opens a file for writing; **by default it
  TRUNCATES (erases) any existing file content** unless opened with
  `std::ios::app` (append mode). Always check `.is_open()` (or the
  stream's boolean conversion) before writing — writing to a
  never-successfully-opened stream silently does nothing (no exception
  by default) rather than crashing or throwing. Verify by actually
  creating a real temporary file, writing to it, reading it back, and
  confirming both the default-truncate and append-mode behaviors with
  real file operations (cleaning up the temp file afterward).
- **`std::ifstream`** opens a file for reading; `std::getline(stream,
  line)` reads one full line into a `std::string`, while `stream >>
  variable` reads one whitespace-delimited token. Reading past
  end-of-file makes the stream enter a fail state (checkable via `if
  (stream)` or `.fail()`), it does not throw by default. Verify with a
  real temporary file containing known content.
- **`try`/`catch`**: a `throw` transfers control to the nearest
  enclosing matching `catch` block, unwinding the stack along the way;
  **exceptions should be caught by (const) reference
  (`catch (const std::exception& e)`) to avoid object slicing**; when
  multiple `catch` blocks follow one `try`, they are tried in the order
  written and the FIRST type-matching one runs (a more general
  `catch (...)` placed before a more specific type would silently
  intercept everything after it — order matters). An uncaught
  exception propagates up the call stack (and terminates the program
  if it reaches `main` uncaught). Verify by compiling and running
  programs that throw/catch by value vs. reference, and that
  demonstrate catch-block ordering mattering.
- **`std::unique_ptr<T>`** is a RAII smart pointer with EXCLUSIVE
  (non-shared) ownership: **it cannot be copied — the copy constructor
  and copy-assignment are deleted, so copying one is a genuine compile
  error** — it can only be MOVED (`std::move`), which transfers
  ownership and leaves the source null. It automatically calls
  `delete` on its owned object when it goes out of scope, even if an
  exception is thrown (this is `unique_ptr`'s core value — automatic,
  exception-safe cleanup). `.get()` returns the raw pointer WITHOUT
  transferring or sharing ownership; `operator->` / `operator*` behave
  like the underlying raw pointer. Verify the copy-is-a-compile-error
  claim directly, and verify move-transfers-ownership (source becomes
  null, destination now owns the object) by compiling and running.
- Given real, compiler-verified bugs have already slipped through
  careful authoring in every phase so far (13-20), and this section's
  `accumulate` truncation gotcha, `max_element`/`min_element`
  iterator-vs-value distinction, file-I/O truncate-by-default behavior,
  and `unique_ptr` copy-is-a-compile-error claims are exactly the kind
  of subtle points prior phases have gotten wrong elsewhere, the plan
  author will hand-verify every claim above by actually compiling (and,
  for behavior/side-effect/ordering claims, RUNNING — including real
  temporary-file I/O for topics 97-98) the relevant snippet before
  finalizing the plan — matching the discipline already applied in
  Phases 17-20 — and task reviewers are expected to continue doing the
  same for anything not immediately obvious.

## Testing / verification for this phase

Same pattern as Phases 13-20:
- `tests/LessonManagerTests.cpp`: extend the topics-with-content range to
  11-100 and REMOVE the "topics without content" test entirely (there
  is no longer any topic 11-100 without content — topics 1-10 already
  had content from the original "static lesson + quiz core" phase, so
  after this phase ALL 100 topics have lesson content; the "no content
  yet" test range would otherwise be empty and meaningless).
- `tests/QuestionManagerTests.cpp`: add
  `QuestionManager_EveryTopicNinetyOneToHundredHasAtLeastTwentyNineQuestions`.
  `QuestionManager_NoDuplicateQuestionIds` already scans topics 1-100
  and needs no change.
- Manual verification: open topic 100 ("unique_ptr") end-to-end.
- Since this is the final content phase, additionally confirm (as part
  of the final whole-branch review) that every topic 1-100 now has
  real lesson content and >= 29 questions — closing out the two
  headline "confirmed gaps" from the top of `roadmap.md`
  ("Only topics 1-10 ... have lesson content" and "Only 72 hand-written
  questions exist") for the first time since the roadmap was written.

## Scope cuts (deliberate, same as prior phases)

- No dynamic-generator wiring, no Section 10 exam (that's Phase 22), no
  100-question general final exam (also Phase 22), earlier sections'
  question density is not revisited.
- No other STL algorithms beyond sort/reverse/find/count/min/max/
  max_element/accumulate (no `std::for_each`, `std::transform`,
  `std::remove`, `std::unique`, `std::binary_search`, etc.), no custom
  exception classes (only `std::exception`/`std::runtime_error`-style
  usage), no `shared_ptr`/`weak_ptr` (only `unique_ptr`, matching the
  roadmap's topic list), no binary file I/O (only text mode), no
  `std::filesystem` — these are reasonable candidates for later, deeper
  phases but out of scope for this Foundation-tier "STL algorithms,
  file I/O, exceptions, smart pointers" introduction.

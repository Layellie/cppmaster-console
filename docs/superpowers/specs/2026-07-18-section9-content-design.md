# CppMaster Console — Bölüm 9 İçerik Genişletmesi Design (Phase 20)

## Context

Eighth of nine section-by-section content phases (13-21) closing the
roadmap's lesson-content and question-bank gaps for topics 11-100.
This phase covers Section 9 (topics 81-90: "STL konteynerleri"),
following the exact same architecture, scope decisions, and testing
approach established and merged in Phases 13-19 (commits
`6df525f..cf6b6f1`, `7987f8c..f62ea67`, `23d1628..3d230f9`,
`4955846..f53d6c0`, `bcdfbba..b5fbe3d`, `f5c69af..0f80e2e`,
`a7794da..5089325`), which this document does not repeat in full.

## Topics covered (Section 9, sectionId 9, from `LessonManager.cpp`'s
`kTopicSeeds`)

81. pair
82. tuple
83. set
84. map
85. unordered_map
86. stack
87. queue
88. deque
89. priority_queue
90. Iterator

## Design (identical architecture to Phases 13-19)

- **Lesson content**: `applySection9LessonContent(std::vector<Lesson>&)`
  in a new file `src/LessonContentSection9.cpp`, declared in
  `src/LessonContent.h` alongside the existing Phase 13-19
  declarations, called from `LessonManager`'s constructor after the
  Phase 19 call. Writes into `lessons[80]` through `lessons[89]`
  (topics 81-90).
- **Question content**: `appendSection9Questions(std::vector<Question>&)`
  in a new file `src/QuestionsSection9.cpp`, declared in
  `src/QuestionContent.h` alongside the existing declarations, called
  from `QuestionManager`'s constructor after the Phase 19 call. Ids
  2103-2392 (10 topics x 29 questions), continuing directly from Phase
  19's last id (2102).
- **Same fixed per-topic type/difficulty/baseXp distribution table** as
  Phases 13-19 (8 MultipleChoice, 6 TrueFalse, 6 FillBlank, 2
  CompleteLine, 2 PredictOutput, 2 FindError, 1 FixCode, 1 OrderCode, 1
  WriteCode; baseXp 5/10/20/30/40 for VeryEasy/Easy/Medium/Hard/Hard-
  WriteCode).
- **No `Application.cpp` changes needed** — same reasoning as prior
  phases.
- **`questions_.reserve(2102)` becomes `questions_.reserve(2392)`**.
- All exampleCode uses `#include <iostream>` plus the specific STL
  header for the topic (`<utility>` for pair, `<tuple>`, `<set>`,
  `<map>`, `<unordered_map>`, `<stack>`, `<queue>` for both queue and
  priority_queue, `<deque>`), matching the one-topic-per-file
  compile-verification pattern already used for every prior section.

## Content-accuracy notes specific to this section (every prior content
phase needed at least one compiler-verified fix for a claim that looked
right but wasn't — this section covers STL containers, where the most
common real-world misconceptions are about ordering, complexity-driven
behavior, and which containers expose which operations — every claim
below is directly compile- and/or run-testable and MUST be verified
that way, not just asserted)

- **`std::pair<T1, T2>`** groups two values of possibly-different types
  accessed via `.first`/`.second` (not indices). `std::make_pair(a, b)`
  deduces the types. Verify by compiling and running a program that
  constructs a pair and prints both members.
- **`std::tuple<...>`** generalizes `pair` to N elements, accessed via
  `std::get<Index>(t)` (a compile-time index, not a runtime variable —
  `std::get<i>(t)` with a non-constant `i` is a genuine compile error).
  Verify both the successful `std::get<0>`/`std::get<1>` access and the
  compile error from a non-constant index.
- **`std::set<T>`** stores unique elements in SORTED order automatically
  (by `operator<`) — inserting in any order and then iterating with a
  range-for always yields ascending order. Duplicate `insert()` calls
  are silently no-ops (the return is a `pair<iterator,bool>` where
  `.second` is `false` on a duplicate). Verify both facts by compiling
  and running a program that inserts out-of-order values (including one
  duplicate) and prints the iteration order.
- **`std::map<K, V>`** stores unique keys in SORTED order (by key,
  `operator<`), each mapped to a value. **`operator[]` on a
  non-existent key INSERTS a new default-constructed entry as a side
  effect** — this is the single most common real `std::map` bug
  (checking existence via `if (m[key] ...)` silently creates entries).
  `.find(key)` does NOT insert and returns `end()` if absent. Verify by
  compiling and running a program that reads `m[missing_key]` and then
  checks `m.size()` grew, and contrasts it with `m.find(missing_key) ==
  m.end()` not growing the container.
- **`std::unordered_map<K, V>`** stores unique keys with NO ordering
  guarantee (hash-table-based) — the exact opposite of `map`'s sorted
  guarantee, a contrast worth drawing explicitly since it's the most
  common map-vs-unordered_map confusion. Verify by compiling and
  running a program that inserts keys in a specific order and shows the
  iteration order is not required to match insertion or sorted order
  (or, more simply, contrast that `map`'s iteration IS always sorted
  while `unordered_map` offers no such guarantee — testable by
  confirming `map`'s output is sorted across a run, which is a stable,
  compiler/library-independent guarantee, unlike asserting a specific
  unordered_map iteration order which is implementation-defined and
  must NOT be asserted as a specific sequence in any question).
- **`std::stack<T>`** is a container ADAPTOR (LIFO) exposing only
  `push`/`pop`/`top`/`empty`/`size` — **it has NO `begin()`/`end()` and
  cannot be iterated with a range-for loop; attempting to do so is a
  genuine compile error.** Verify this compile error directly.
- **`std::queue<T>`** is a container adaptor (FIFO) exposing
  `push`/`pop`/`front`/`back`/`empty`/`size` — also has **no iteration
  support**, same compile-error verification as `stack`.
- **`std::deque<T>`** (double-ended queue) supports `push_front`,
  `push_back`, `pop_front`, `pop_back`, AND random access via `[]`/
  `.at()`, AND full iteration with `begin()`/`end()` — the contrast
  with `stack`/`queue`'s lack of iteration is worth drawing explicitly.
  Verify by compiling and running a program that pushes to both ends
  and iterates the result.
- **`std::priority_queue<T>`** is a container adaptor implemented as a
  max-heap BY DEFAULT — `top()` returns the LARGEST element, not the
  smallest (a very common misconception; a min-heap requires
  `std::greater<T>` as the third template argument). It also has no
  iteration support. Verify by compiling and running a program that
  pushes several values in arbitrary order and confirms `top()` is the
  maximum, and `pop()` repeatedly yields descending order.
- **Iterators** (`begin()`/`end()`) provide a uniform way to traverse
  any STL container; a range-for loop is sugar for
  `for (auto it = c.begin(); it != c.end(); ++it)`. `end()` is a
  past-the-end marker and must never be dereferenced. Verify by
  compiling and running both an explicit iterator loop and an
  equivalent range-for loop over the same container and confirming
  identical output.
- Given real, compiler-verified bugs have already slipped through
  careful authoring in every phase so far (13-19), and this section's
  container-adaptor-vs-iterable-container distinctions
  (stack/queue/priority_queue lack iteration; deque/set/map/
  unordered_map have it) are exactly the kind of subtle claim prior
  phases have gotten wrong, the plan author will hand-verify every
  claim above by actually compiling (and, for ordering/side-effect/
  iteration claims, RUNNING) the relevant snippet before finalizing the
  plan — matching the discipline already applied in Phases 17-19 — and
  task reviewers are expected to continue doing the same for anything
  not immediately obvious.

## Testing / verification for this phase

Same pattern as Phases 13-19:
- `tests/LessonManagerTests.cpp`: extend the topics-with-content range to
  11-90 and narrow the no-content range to 91-100 (renaming, not
  duplicating, Phase 19's own two tests).
- `tests/QuestionManagerTests.cpp`: add
  `QuestionManager_EveryTopicEightyOneToNinetyHasAtLeastTwentyNineQuestions`.
- Manual verification: open topic 84 ("map") end-to-end.

## Scope cuts (deliberate, same as prior phases)

- No dynamic-generator wiring, no Section 9 exam, earlier sections'
  question density is not revisited.
- No `multiset`/`multimap`, no custom comparators/hash functions, no
  `std::list`/`std::forward_list`, no iterator invalidation deep dive
  (mentioned only if directly relevant to a specific example, e.g.
  `map`'s stable iterators vs `vector`'s), no `std::array` (already
  covered in an earlier section per the roadmap's topic list), no
  structured bindings for `pair`/`tuple` (mentioned only in passing if
  natural, not a dedicated topic) — these are reasonable candidates for
  later, deeper phases but out of scope for this Foundation-tier "STL
  containers" introduction.

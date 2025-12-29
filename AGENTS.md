# AGENTS.md

This repo is a competitive programming reference library (ICPC, CF, BOJ, etc).
When adding or editing code here, optimize for contest usage first.

## Core goals (in priority order)
1. **Quick to type and paste**: short, practical APIs and file structure.
2. **Fast and memory efficient**: proven time complexity, low constants, minimal allocations.
3. **Readable under pressure**: simple control flow, obvious invariants, and friendly comments.
4. **Consistent style**: match the rules in this file and existing patterns in this repo.
5. **Template-friendly**: easy to reuse across problems with minimal edits.

## Repo standard code style (required)

### Naming
- **Constants** (e.g., `constexpr`, global `const`, fixed parameters): `UPPER_SNAKE_CASE`.
  - Examples: `constexpr int MOD = 1e9 + 7;`, `const int INF = 1e9;`
- **All other identifiers** use **lowercase `snake_case`** (STL style):
  - structs, classes, namespaces, functions, variables, file names
  - Examples: `struct fenwick_tree`, `namespace fast_io`, `solve_case`, `add_edge`
- **Concise yet descriptive**: names must be short for typing speed but clear enough to read under pressure.
  - **Good**: `cnt`, `idx`, `res`, `nxt`, `vis`, `dist`.
  - **Bad**: `number_of_elements`, `adjacency_list`, `calculated_distance`.

### Types
- Prefer `ll` by default to reduce overflow debugging.
- Use `int` only when clearly safe and beneficial (memory, bitset indexing, array indices, tight constraints).
- Avoid implicit narrowing conversions. Cast explicitly at boundaries when mixing types.
- Prefer aliases from `common.hpp` (e.g., `pll`, `pii`) when they match exactly to reduce typing.

## Coding rules
- Prefer straightforward implementations over heavy abstractions.
- Avoid unnecessary dynamic polymorphism, complex metaprogramming, and over-engineered designs.
- Public-facing helpers should be easy to understand without reading 5 other files.
- Template common patterns (I/O, loops, small utilities), but keep templates minimal.

## Comments and documentation (required)
Write friendly, high-signal documentation in a consistent format.

### 1) Module header (for each reusable component)
Add a header comment near the top:
- What it does: add comments so that even content encountered after a long time serves as a reminder.
- Complexity (time, memory)
- Constraints / gotchas (short)
- Optional: where it was verified (contest / problem ID)

### 2) Inline comments (throughout the code)
Comment generously with short, consistent one-liners:
- intent (`// goal: ...`)
- invariants (`// invariant: ...` = must stay true throughout the loop/algorithm)
- edge cases (`// edge: ...`)
- tricky reasoning (`// why: ...`)
- usage (`// usage: ...`)

Prefer many small comments over a few long paragraphs.

## Formatting (required)
After any change, run:
- `scripts/format.sh`

Do not commit unformatted code.

## Consistency checklist
Before finishing a change:
- Style matches the rules above (naming, layout, aliases).
- The API is minimal and pasteable.
- Complexity and constraints are stated.
- Comments explain intent/invariants/edges without being verbose.
- The code is not longer than it needs to be.

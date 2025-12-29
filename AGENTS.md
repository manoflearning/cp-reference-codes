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
- **Struct names**: `PascalCase` (capitalized).
  - Example: `struct FenwickTree { ... };`
- **Constants** (e.g., `constexpr`, global `const`, fixed parameters): `UPPER_SNAKE_CASE`.
  - Examples: `constexpr int MOD = 1e9 + 7;`, `const int INF = 1e9;`
- **Everything else** uses **lowercase `snake_case`**:
  - namespaces, functions, variables, file names
  - Examples: `namespace fast_io`, `add_edge`, `max_flow`, `solve_case`, `pref_sum`

### Types
- Prefer `ll` by default to reduce overflow debugging.
- Use `int` only when clearly safe and beneficial (memory, bitset indexing, array indices, tight constraints).
- Avoid implicit narrowing conversions. Cast explicitly at boundaries when mixing types.

## Coding rules
- Prefer straightforward implementations over heavy abstractions.
- Avoid unnecessary dynamic polymorphism, complex metaprogramming, and over-engineered designs.
- Public-facing helpers should be easy to understand without reading 5 other files.
- Template common patterns (I/O, loops, small utilities), but keep templates minimal.

## Comments and documentation (required)
Write friendly, high-signal documentation in a consistent format.

### 1) Module header (for each reusable component)
Add a short header comment near the top:
- What it does
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
- No extra dependencies unless clearly worth it.
- Complexity and constraints are stated.
- Comments explain intent/invariants/edges without being verbose.
- The code is not longer than it needs to be.

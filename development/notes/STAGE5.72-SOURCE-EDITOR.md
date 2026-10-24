# SIDBOX CoderGirl IDE Stage 5.72.241026 - Source Editor

Only these existing IDE source files were changed:

- `codeeditor.cpp`
- `codeeditor.h`
- `splashscreenwidget.cpp` (splash build version)

## Source code context menu

Right-click **inside** an editable source-code editor. The existing Qt
Undo, Redo, Cut, Copy, Paste, Delete and Select All actions are preserved.
`Format Sourcecode` is added after a separator. It is disabled for read-only
and resource-mode tabs.

## Source formatting

- Replaces indentation based on 4-column visual stops with literal `\t`.
- Reindents normal C/C++ brace blocks, `case` / `default` and simple
  unbraced single statements.
- Leaves characters after the leading whitespace **untouched**. This
  includes strings, character literals, existing code, comments, etc.
- Preserves visual alignment on multiline parenthesised/bracketed continuations.
- Preprocessor directives are column-zero; macro continuation lines are
  protected from structural reindentation.
- Multi-line comments and raw/multiline literals are protected from
  structural reindentation.
- Normalising indentation on Enter makes new lines use tabs even when the
  preceding line came from an old space-indented file.
- Tab display width follows editor font changes and stays four columns.
- Changes are a **single undo action**, marked as an unsaved editor edit.
  No disk writes happen until the user saves as normal.

This is an indentation formatter, not a full clang-format replacement:
source tokens, statement placement, and spacing inside expressions are not
rewritten. Very complex C/C++ continuation syntax may still need manual
alignment. If a layout is undesirable, press Ctrl+Z once.

## Matching braces and brackets

When the caret is on or just after `(`, `)`, `[`, `]`, `{`, or `}`, both members
of the matching pair are highlighted using the active theme accent colour.
Strings, comments, and preprocessor directives are ignored for pair matching.
Unmatched brackets are not falsely highlighted. The overlay does not alter
the document or the regular syntax-colouring rules.

## Manual acceptance checklist

1. Open a normal `.c` or `.cpp` source tab.
2. Right-click in the editor and verify Qt's standard editing actions and
   **Format Sourcecode** appear.
3. Insert a function indented with 4/8 spaces, including a nested `if`,
   plus a string literal like `"{ [ ] }"` and a `// { not a brace` comment.
4. Format; verify the leading whitespace becomes tabs, real nesting aligns,
   and the literal and comment content do not change.
5. Press Ctrl+Z once; verify original indentation is restored. Press Ctrl+Y
   to redo if desired; save normally.
6. Place the caret on or immediately after braces/brackets and verify
   both real partners light up; false pairs in strings/comments do not.
7. Verify right-click formatting is disabled on read-only/resource tabs.
8. Change the editor font size; verify a literal tab still spans 4 spaces.
9. In a source tab with a function split over lines, verify continuation
   alignment is preserved. Verify the game/firmware files are unchanged
   until you explicitly save them.

## Build status

Qt6 development packages are unavailable in the generation environment, so a
Qt6 compilation was **not** possible here. Please rebuild on your Qt6-enabled
Fedora installation before treating this stage as hardware/IDE accepted.

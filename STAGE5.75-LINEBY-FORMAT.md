# CoderGirl IDE Stage 5.75.241026: Format SourceCode LineBy

## Where

In the normal C/C++ source tab editor, right-click and choose:

- **Format Sourcecode**: Existing tab/brace formatting (Stage 5.72–5.74).
- **Format SourceCode LineBy**: New, separate one-line expression formatter.

LineBy removes line breaks within clear expressions, including calls and control
conditions with parentheses/brackets, and operators broken across lines.
It **does not** reindent the blocks around those statements. Each joined line
retains the indentation already present on its first source line.

Examples:

```c
const uint32_t remaining = (uint32_t)animation->frame_count - 1u
- animation->current_frame;
```

becomes:

```c
const uint32_t remaining = (uint32_t)animation->frame_count - 1u - animation->current_frame;
```

and:

```c
if (a == b &&
    c == d) {
    fish();
}
```

becomes:

```c
if (a == b && c == d) {
    fish();
}
```

A multiline `if` condition whose opening `{` was moved onto a standalone line
can also be brought back to the joined condition line. A standalone brace for
an **already single-line** condition will not be moved.

## Safeguards

- Comments, preprocessor directives, continued macro lines, multiline string
  literals, and raw string bodies are not joined across.
- Ordinary standalone statements, blocks, and unbraced control bodies are not
  combined.
- Joined line breaks are replaced with a single space, not four literal spaces.
- Formatting is one Undo step. It does not save or modify game sources on disk.
- Completion popups are dismissed while formatting.
- Running LineBy again on already joined code makes no additional changes in
  the supplied examples.
- LineBy is deliberately conservative. This is **not** a full C/C++ parser or
  clang-format replacement: ambiguous line breaks may remain as they are.

## Changed files

- `codeeditor.cpp`: Source right-click action and standalone LineBy implementation.
- `codeeditor.h`: Method declaration.
- `splashscreenwidget.cpp`: Build `5.75.241026`.

The IDE compiler/build pipeline, `mainwindow.cpp` (2048 KB syntax limit),
source generator, game runtime, and user-maintained `main.c` remain untouched.
Stage 5.74 IntelliSense Tab behaviour and Stage 5.73.1 warning fix are kept.

## Fedora test

1. Drop in the three files above and rebuild the IDE.
2. Right-click a source tab and confirm both formatting actions appear.
3. Run **Format SourceCode LineBy** on the subtraction and multiline `if`
   examples, and confirm their surrounding indentation is unchanged.
4. Run it again: no further changes.
5. Press Ctrl+Z once: the original line breaks should return.
6. Test macro continuations, `//` comments, and strings: no unsafe joining.

**Build status:** Source-level checks and executable behavioural model tests pass.
Qt6 development libraries are unavailable in this container; the C++ change
has **not** been compiled or tested in the GUI here. Your Fedora build is the
acceptance test.

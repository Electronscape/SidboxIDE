# Stage 5.109 (25 October 2026) - Code Editor input and folding

This release changes **only CodeEditor** and the splash build label. No game engine,
UI designer, project, generator or `main.c` files are changed.

## Fixes

1. **Enter / indent drift**: auto-indent copies indentation only from the text
   before the caret, never whitespace after it. Repeated Enter at column zero
   on an already indented line no longer keeps inserting an extra prefix.
2. **IntelliSense**: suggestions are permitted after 600 ms of inactivity
   following actual typing/paste, not in response to Enter, Space, Delete,
   Backspace, caret motion or programmatic formatting. Further keypresses stop
   the pending idle timer. Plain Enter inserts a line rather than choosing
   the first suggestion. Click a suggestion to accept it or use Ctrl+Enter.
3. **Fold hints**: collapsed `if`, function, array, switch, etc. regions paint
   `[...]` on the fold header after the code. This is a view-only overlay, not
   literal characters inserted in your C source; expand to hide it.

## Install and verify

Extract the ZIP into the Stage 5.108 IDE source root and rebuild with Qt6.
Open a C file, place the caret at column zero on an indented line and press
Enter repeatedly: the original code should not walk to the right. Type an
identifier quickly, hit Enter/Space/Delete before 600ms, and verify no
completion replaces your code. Wait 600ms after a valid identifier to open
suggestions; use Ctrl+Enter to choose one. Collapse several nested regions and
check `[...]` appears on each visible collapsed header and disappears on expand.

No Update Game Project or firmware rebuild required.

## Verification

`python3 development/tests/test_stage5109_codeeditor_contract.py` verifies
source wiring. The Stage 5.108 spotlight-action regression passes. Full Qt6
compilation and interactive GUI tests are not available in this environment;
please perform final verification in Fedora.

SIDBOX CoderGirl IDE - Build 5.166.113.1.291026
29 October 2026 - Visual Nodes Qt keyword compile hotfix

Base: exact full Stage 5.166.113.291026 source archive.

What was wrong:
  gamevisualnodes.cpp::syncGraphCardSockets() declared a variable named
  `slots`, which Qt defines as a macro for its signal/slot syntax.
  The preprocessor removed the name, causing the compiler errors at
  lines 4829, 4840 and 4844.

Fix:
  Rename all four references within syncGraphCardSockets() from `slots`
  to `inputSocketCount`. Also explicitly cast the input array size to int
  before qMax() to satisfy Qt 6 template type deduction.
  This does not change the numbered-socket layout,
  AND/OR/NOT/BOOLEAN logic, saved graphs, generated C, or game saves.
  Splash-screen build string updated to 5.166.113.1.291026.

Changed source files:
  gamevisualnodes.cpp
  splashscreenwidget.cpp

Tests:
  development/tests/test_stage5166_113_1_qt_keyword.py (new)
  development/tests/test_stage5166_113_logic_input_sockets.py (version updated)

Fedora instructions: replace these files in your IDE source, then rebuild.
Full Qt build and SIDBOX hardware test must still be done on Fedora.

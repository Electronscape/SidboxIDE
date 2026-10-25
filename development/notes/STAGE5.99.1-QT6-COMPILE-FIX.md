# CoderGirl Stage 5.99.1, Qt6 preview compile fix

Replace `gameadventureeditor.cpp` and `splashscreenwidget.cpp` at the CoderGirl IDE source root, then rebuild the IDE.

In `gameadventureeditor.cpp`, line 3197, convert `thoughtLines.size()` (qsizetype) to `int` before calling `std::max` so the integer arguments have matching types. This is safe because `adventurePreviewRows(..., 16)` returns at most 16 rows.

Unchanged: dialogue/thought glyph scaling, thought/dialogue z-order, runtime, world files, generated code and user-owned `main.c`.

1x1 glyph scaling = 8x8 pixels per character; row step = 8 px without outline, 12 px with outline (the latter includes extra spacing for the outline). Dialogues and thoughts may each choose their own scale.

Static source verification passed. Qt6 IDE compilation and SIDBOX hardware checks have not been performed in this environment.

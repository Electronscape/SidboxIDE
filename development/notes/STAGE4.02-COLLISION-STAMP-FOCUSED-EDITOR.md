# Stage 4.02 — Full-size Collision Stamp editor

**Baseline:** Stage 4.01 complete IDE source.

## User-facing change

The **Collision Stamps** tab now has two views, instead of an always-visible vertical 50/50 splitter:

1. **Stamp Bank** — full-height list of collision stamps; single-click still picks the stamp as the map painting brush.
2. **Collision Stamp Editor** — double-click a stamp to open its **full-height editable** surface with the stamp's name, dimensions, passive sliding/damping, editable control points, Bezier curve generator and point tools. The grid is three times the previous on-screen size (96 instead of 32 screen pixels per stamp tile), and larger stamps scroll naturally.

Use **Close Editor** or **Esc** to return to the bank. Closing does not discard edits: the editor continues to edit the same in-memory stamp definition, and existing Undo/Redo and Save / Apply to Design remain available. Shift-clicking a placed slope on the map opens its stamp in the same editor.

No PPB, tilemap model, saved `.sbgm` format, generated C, or physics code is changed.

## Installation

Replace **`gametilemap.cpp` and `gametilemap.h`** in the Qt6 IDE source root, then rebuild in Qt Creator. No F5 game regeneration required.

## Suggested Fedora UI test

1. In the Tilemap Editor open **Collision Stamps**. The bank should occupy the entire right-hand pane; a single click still selects a paint brush.
2. Double-click a stamp. The bank should disappear and a larger point editor should replace it. Drag a point and verify movement matches the cursor at the 96-pixel cell scale.
3. Use **Close Editor**. Verify the selected stamp remains highlighted, the map brush is still set, and reopening retains the edits.
4. Check **Undo / Redo**, editing point X/Y values, width/height resize, Insert / Delete, and Bezier curve generation.
5. Check **Shift-click placed slope** jumps directly into editing; test Escape returns to bank rather than closing the whole Tilemap Editor.
6. Try the narrow right pane and a large stamp; it should scroll rather than widen the sidebar.
7. Test both light and dark themes; the existing selection-card styling should remain unchanged.

## Verification

Source checks pass, including Stage 4.00 selection cards and Stage 4.01 theme controls. Qt6 headers are unavailable in this build container, so a real Qt compilation / visual test is still required.

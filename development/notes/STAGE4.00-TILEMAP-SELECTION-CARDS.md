# Stage 4.00 — Tilemap Editor themed selection cards

**Baseline:** Complete IDE source from Stage 3.99 (exact `gametilemap.cpp` hash verified against the Stage 3.99 archive).

## What changed

The three selection lists in **Tilemap Editor → Tile Stamps, Collision Stamps, and Loop Tracks** now match the bordered item-card styling of **Game Object Properties**:

- Square borders around every selectable entry, with a stronger accent border and accent strip at left on the selected entry.
- Selection background derived from the current theme accent; foreground automatically changes between white and black to maintain contrast.
- Theme-aware normal and hover backgrounds, labels, and container borders.
- Original thumbnail/icon sizes, selection handlers, stamping behaviour, collision placement, and loop editing are unchanged.
- Loop rows have a little more vertical space to prevent the border from crowding the label.

## Production files changed

Only `gametilemap.cpp`. No changes to saved `.sbgm` format, generated C, physics helpers, render engine or other IDE interfaces.

## Install

Replace the single `gametilemap.cpp` file in your Qt IDE source, then rebuild the IDE. No game-project update or regeneration needed.

## Fedora visual test

1. Open Game Designer → Tilemap Editor. Choose **Tile Stamps** and click entries; verify card outlines, active accent and readable text with your usual theme.
2. Repeat for **Collision Stamps** and **Loop Tracks** (including newly added loops).
3. Switch to **light theme** and repeat; selected text should contrast against the dark accent selection background.
4. Verify selecting and painting a stamp, editing collision stamps, and changing loop properties still operate as before.

`development/tests/test_stage400_tilemap_selection_cards.py` validates the source wiring; a Qt6 build and actual UI checks must still be performed on Fedora because Qt6 development files are not available in this container.

## Verification note

The new Stage 4.00 test, the Stage 3.99 canvas test, and the selected older IDE/physics integration tests pass. The old Stage 3.84 animation structure test still expects a hard-coded dark palette, and fails **unchanged on the Stage 3.99 baseline** after the later theme-aware animation refactor; this is unrelated to this patch.

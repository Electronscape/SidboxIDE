# Stage 5.49.1 (23 October 2026): HUD bar generator hotfix

## Symptom

After saving or regenerating a HUD containing an animated PPB progress bar,
`gamehelpers/gamehud.c` could contain invalid, unsubstituted QString template
markers, for example:

```c
tile.drawy=(int16_t)(y+%13); gfx_drawbob(&tile);
```

The problem is **in the IDE's C generator**, not the selected PPB, frame index,
HUD layout or the user's game code.

## Fix

`gamehudeditor.cpp`, function `exportHud()`: generate the progress bar's C
statements in five independently formatted fragments, each using only
`%1`, `%2`, `%3`. The animation modulo operator now has its own literal `%`
with whitespace around it and cannot be confused with Qt placeholders.

Existing HUD files and configuration are unchanged. Existing PPB colour
indices remain intact. No new graphics or TFCard files are produced.

Splash build version: **5.49.1.231026**.

## How to apply

1. Extract the Stage 5.49.1 drop-in over Stage 5.49 IDE source, and rebuild
   the IDE.
2. Reopen the HUD editor and Save, or run **Update Game Project**, to rewrite
   `gamehelpers/gamehud.c` from the corrected generator.
3. Rebuild the game. Do **not** permanently edit the generated `gamehud.c`:
   the next regeneration would overwrite such changes.

## Validation

`development/tests/test_stage549_hud_progress.py` now parses the actual five
new `QStringLiteral` C fragments, checks the placeholders, compiles the
expanded C with GCC, and executes tests for live Health, Fear and collectable
counts with 8x8/16x16 tiles, fractional clipping and animation frames.
Earlier source-level and native C regressions run separately. Complete Qt6
IDE compilation and STM32 hardware behaviour still require local testing.

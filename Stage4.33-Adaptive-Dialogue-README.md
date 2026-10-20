# GamerGirl Stage 4.33 — Adaptive Dialogue Size and Two-Choice Navigation

**Based on Stage 4.32.** Back up both the IDE and the working platformer before installing. SIDBOX hardware and Fedora Qt6 build have not been tested here.

## What changes

- **Dialogue Position > Height** is now **Minimum height**. X, Y, and Width remain editable and draggable. The runtime measures the name, all wrapped NPC dialogue text, and the tallest pair of adjacent answers to choose an actual height for each conversation node. It grows automatically, but never beyond the 480×320 LCD. When necessary, it shifts the displayed dialogue frame upward so the frame stays on-screen. The size stays stable while navigating between responses.
- **Only two answers at once**, with `v` in the right gutter if answers exist below and `^` if there are answers above. Up/Down still move through *all* defined choices, and the same requires/give/take/action/next-node logic is preserved.
- **Dialogue Position preview** offers a dropdown of your actual conversation nodes and a previewed selected response. It uses the 8×16 font's wrapping limits, shows the name/text/two answer choices, draws a dashed content guide, reports needed vs actual height, and turns red with a warning if the content requires more than 320 pixels. The Qt glyph drawing is an approximation; the line-count measurements match the runtime's intended 8×16 model.
- Old `.sbgm` projects keep their saved `dialogHeight` as their **minimum**. New designs default to 96 pixels minimum; you can reduce an older project's saved minimum to 96 in the editor to eliminate unused blank space.
- Inventory, NPC animation, palette, springs, slopes, SPC music and existing dialogue puzzle events are unchanged.

## Install the IDE patch

1. Back up the Stage 4.32 IDE source and game project.
2. Extract `GamerGirl-Stage4.33-Changed-Files.zip` at the **IDE source root** preserving directories. The changed production files are `gameadventureeditor.cpp`, `idelibs/codehelpers/game/adventureruntime.c` and `idelibs/codehelpers/game/adventureruntime.h`. Tests are included.
3. Rebuild GamerGirl, then open Adventure Editor > Dialogue Position. Choose a real dialogue node, set X/Y/Width and **Minimum height**, and check the preview. Save your design and select Update Game Project.

## Update your existing game runtime — REQUIRED

**Update Game Project does NOT overwrite existing `gamehelpers/gameadventureruntime.c/.h`.** This is intentional protection for user files. Without updating those helpers, the old fixed-height/two-plus answers drawing remains.

1. Back up the two existing helper files in your game's `gamehelpers/` directory if you have customized them.
2. Extract `GamerGirl-Stage4.33-Game-Helper-Update.zip` into your **game project root**, preserving the `gamehelpers/` folder. It contains `gamehelpers/gameadventureruntime.c` and `.h` with the correct include names, ready to replace the existing versions.
3. Recompile the game and test on SIDBOX.

**No changes to your hand-edited `main.c`** are required if it already calls `gameadventure_setup()`, `game_adventure_draw_npcs()` and `game_adventure_draw()` from the earlier adventure stages.

## Screen limit

The LCD is only 320 pixels tall. If text plus two long answers exceeds 320 pixels even after widening, the preview shows a **red warning**. The runtime prioritizes choices in the remaining available space; it does *not* implement text-page scrolling or arbitrary clipping. Shorten the dialogue or split it into multiple nodes for a conversation that cannot fit.

## Verification

- Compiled C11 Stage 4.29/4.30/4.31/4.32 runtime tests: PASS.
- New compiled Stage 4.33 runtime test: growing frame, y adjustment, two visible choices with arrows, stable height and oversized-content bounds: PASS.
- Stage 4.26 SPC, 4.27 auto-music, 4.28–4.33 generator/IDE source regression checks: PASS.
- **Qt6 build not run** (Qt6 development headers not installed in this environment); **SIDBOX hardware acceptance pending**.

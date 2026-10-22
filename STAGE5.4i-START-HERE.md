# Stage 5.4i — Per-world Adventure / Inventory Skin Hotfix

Base: working Stage 5.4h (Adventure copy settings).

## Why forest was still green

Stage 5.4h successfully copied dialogue box settings into each `.sbgm`, but the
**shared** `gameadventureruntime.c` still used colours/position/tile size taken
from just one world. Also, a world with only copied dialogue appearance/position
(no NPCs or dialogue yet) was incorrectly classified as 'no Adventure', and
received a no-op `gameadventure_setup()` stub. In the shared Adventure renderer,
the unskinned frame fallback is a green-filled rectangle (palette index 2).

## Fix

* `gamedesigner.cpp` — a saved atlas or dialogue position counts as Adventure
  setup even when NPC, dialogue and inventory arrays are empty.
* `gameadventuregen.cpp` — passes validated per-world colours, text outline,
  box X/Y/width/height, tile size and text speed into `gameadventure.rulec`.
* `idelibs/codehelpers/game/gameadventure.rulec` — each world's
  `gameadventure_setup()` sets the style and position **after** starting the
  shared Adventure renderer, and uses that world's tile size/typing speed.
  Also supports a fully empty story under strict GCC warning checks.

The SDK's common `adventureruntime.rulec` remains shared, as intended.

## Install / test

1. Back up your working IDE and game project.
2. Replace the **three files** from the changed-files ZIP, preserving paths.
3. Rebuild the IDE.
4. Open `forest.sbgm` and check under Adventure Editor > Dialogue Box Atlas
   that a valid Tile Atlas is selected (if not, import the same PPB Tile Atlas
   resource into forest and use Copy from Another World again). Click OK and
   save the design.
5. Use **Update Game Project** for the whole project (or F5 updating all worlds)
   to regenerate `worlds/forest/gamehelpers/gameadventure.c` as well as world1.
6. Verify generated `forest` gameadventure.c contains
   `game_adventure_text_style(...)` and `game_adventure_dialogue_box(...)` and
   points to the expected atlas PPB path.
7. Compile and test the forest inventory on SIDBOX. Make sure that PPB file is
   available at the referenced path on the TFCard. Without a valid skin PPB,
   the runtime's green fallback rectangle is expected.

**No `main.c` changes needed**, and no change to collected/hidden-item behaviour.
The V2 GUI Designer is untouched.

## Checks performed in this environment

* GCC -std=c11 -Wall -Wextra -Werror mock build / execution with two namespaced
  world Adventure modules sharing a runtime; styles/positions restored when
  switching world1 -> forest -> world1 — PASS.
* Stage 5.4h copy settings contract — PASS.
* Stage 5.4g inventory reveal and Stage 5.4f NPC visibility tests — PASS.
* Stage 5.2 mixed world manager and Stage 5.4f player registration tests — PASS.
* Full Qt6 build and SIDBOX hardware execution are **not** available here.

# Stage 5.34.2 | SIDBOX Adventure & Inventory polish

Based on **Stage 5.34.1**. This stage makes no changes to user-owned `main.c` and does not modify saved `.sbgm` format.

## Behaviour

1. NPC GIVE now displays `FIRE1: CONFIRM  FIRE2: BACK` along the lower-right edge of the inventory box.
2. The redundant **Still missing items** dialogue and partial action controls are removed from the NPC GIVE editor. The generator suppresses legacy partial responses/actions too. For **ALL** requirements, incomplete exchanges re-display the current NPC dialogue; incremental deliveries are still consumed as configured and remembered across world changes. Correct success and wrong-item responses work as before.
3. The bottom of inventory and dialogue frames is shortened by **8 px** without moving the title, item rows or text insets relative to their frame's upper edge. The Adventure dialogue preview uses the same shorter height and lower content boundary. Frame skins are not changed.
4. **FIRE1 jump leak fix:** After a modal accepts FIRE1 (USE, DROP, DESTROY, GIVE), the Adventure runtime latches the input until FIRE1 is released, even if the inventory immediately closes. The tilemap physics helper uses an optional weak link to `game_adventure_gameplay_buttons()` to mask that press from physics. Plain platformers with no Adventure runtime remain compatible.

## Installation (IMPORTANT for the jump fix)

- Apply the changed-file archive over **Stage 5.34.1 IDE source** preserving folder structure, then rebuild CoderGirl.
- Back up the game project, open your `.sbgm`, save your settings and run **Update Game Project**.
- Because the jump fix is at the tilemap physics input boundary, an existing `gamehelpers/gametilemap.c` must be upgraded. CoderGirl now detects this missing guard when an Adventure world uses tilemaps, offers an automatic update, and backs up the old helper using a timestamped `.bak`. **Accept that update**. A project retaining its old `gametilemap.c` will retain the old jump bug even if `gameadventureruntime.c` is regenerated.
- Build the game again and test on SIDBOX.
- Your hand-edited `main.c` is **not replaced**. The default `maingame` starter now filters Adventure FIRE1 as a secondary safeguard.

## Suggested SIDBOX acceptance

- Open inventory, USE a valid item with FIRE1: closes, health/stat effect applies, **no jump**. Hold FIRE1 for several frames: still no jump. Release then press FIRE1 on the ground: normal jump.
- Repeat for DROP and confirm YES for DESTROY. Cancel NO: inventory stays open, no jump.
- Offer a gift to NPC: bottom-right `FIRE1: CONFIRM  FIRE2: BACK` is visible; wrong-item response works. Partial incremental items are accepted silently and still count when returning to the NPC later.
- Check the bottom edge on inventory (1, 10, 11 items) and dialogue boxes with 0px and 8px padding, including 8/16/32-pixel frame skins.

## Validation

Ten focused host test suites passed (generated C under GCC `-std=c11 -Wall -Wextra -Werror`): Stage 5.34.2 FIRE1 hand-off, GIVE exchanges, Stage 5.33 inventory, Stage 5.32 frame padding, Stage 5.31 inventory, Stage 5.32 item USE, Stage 5.28 FIRE2 priority, Stage 5.27 secret choices, Stage 5.25 missing-item dialogue, and Stage 5.26 door persistence. Full Fedora Qt6 compilation and physical SIDBOX verification are still outstanding.

Splash: `Build: 5.34.2.221026`.

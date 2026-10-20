# GamerGirl Stage 4.31 — Adventure usability, NPC flip & animation timeline

Stage 4.31 builds on the complete Stage 4.30 source. The Advanced Platformer adventure system is optional. Existing music auto-start, physics, spline, spring and tile rendering code is not changed.

## What is new

- Inventory editor headings and on-screen guide now explain that each row defines an **item type**, not one physical placed sprite. The drop-down explicitly identifies existing collectable kinds: Coin=1, Health=2, Key=3, Gem=4. It lists the names of matching **placed** game objects. Kind 0 means *only acquired manually or via NPC dialogue*.
- Inventory icon: double-click **Icon artwork** on the item row to select a cell visually from the **Dialogue Box Tile Atlas**. Select an atlas on that tab first. There is no requirement to add an icon; new items default to **No icon**. Existing items retain their current icon index. The inventory runtime now supports atlas indices larger than 255 (16-bit); it rebases the pixel source just as the dialogue frame does.
- NPC **Start node** now selects a named dialogue node from a drop-down. Edits/additions refresh NPC options; deleted nodes remap references.
- NPCs respect the X Flip/Y Flip flags on their placed **Sprite** resource. Flip changes are regenerated when you use **Update Game Project**. `game_adventure_draw_npcs()` still draws all NPCs once.
- Nine-piece Dialogue Box Atlas has individual X Flip/Y Flip checkboxes and mirrored preview. Tile size is unchanged. The atlas indices remain 16-bit.
- NPC Animations now has **Idle** and **Talking** frame lists. Add individual atlas frames, remove them, move them Up/Down, set individual delays (1–255 frames, 50 FPS), and Play/Stop a looping preview. Legacy contiguous animations are imported as a list with the old speed.
- New Adventure-enabled **generated** main code passes player input to tile physics with `BTN_UP` masked off. Fire 1 still jumps; Up remains available for inventory/dialogue selection. Basic Platformer without Adventure retains its original controls.

## Why your pickup did not increase inventory

From the earlier uploaded game project, `main.c` has this callback, which **only increases score**:

```c
static void on_pickup(game_collectable_t *item, void *user)
{
    uint32_t *points = (uint32_t *)user;
    if (!item || !points) return;
    *points += item->value;
}
```

Because your `main.c` is hand-edited and protected, **Update Game Project will not silently overwrite it**. Add the Adventure bridge yourself **inside** `on_pickup()`:

```c
static void on_pickup(game_collectable_t *item, void *user)
{
    uint32_t *points = (uint32_t *)user;
    if (!item || !points) return;
    *points += item->value;
    game_adventure_collect(item->kind); /* NEW: adds one to each matching inventory definition. */
}
```

This matches by **kind**, not physical sprite name. Your placed `Kim`, `Kim_copy[1]`, etc. may be kind 2 (Health). If you configure an inventory row with kind 2, collecting any of those adds one of that row's item, up to **Max owned**. Selecting **Start with = 1** with a maximum of 1 makes the item appear full from the beginning, so use **Start with = 0** for a one-at-a-time pickup test. With several pickups of the same kind but distinct desired inventory items, you'll eventually want an **object-specific pickup mapping** instead of kind mapping; Stage 4.31 preserves the existing type-level model.

## Your second one-time custom `main.c` edit — Up must not jump

On your *hand-edited* platformer, find the call to `game_tile_player_run()` (or the appropriate tilemap `game_tile_player_step` input, if you have changed the input path). If it currently says:

```c
game_tile_player_run(&player_physics, player_buttons, 1);
```

change **only that line** to:

```c
game_tile_player_run(&player_physics, player_buttons & (uint8_t)~BTN_UP, 1);
```

If your code calls `game_tile_player_run(&player_physics, getjoyport(), 1);` directly, change it to:

```c
game_tile_player_run(&player_physics, getjoyport() & (uint8_t)~BTN_UP, 1);
```

**Do not mask Up when passing input to `game_adventure_input()`** — the Adventure system still needs the real Up button for menu choices and the inventory shortcut. This masking is only for the *physics* call and does not affect Basic Platformer projects. Note: Your hand-edited main may also have special space/water physics logic; apply the same Up masking to its actual physics-input path, not to other game systems.

## Installation

1. Back up the working Stage 4.30 IDE and platformer project.
2. Replace the IDE source with the changed-files archive, or install the complete Stage 4.31 source tree. Rebuild the IDE on Fedora.
3. Open your existing `.sbgm` design. Adventure Editor > Inventory Items gives the new guide; NPCs > NPC Animations... opens the editable frame lists. Dialogue Box Atlas shows nine X/Y flips.
4. Save Design; **Update Game Project**. GamerGirl refreshes `gamehelpers/gameadventureruntime.c/.h` from the bundled helper templates and regenerates `gameadventure.c/.h`. `main.c` stays protected.
5. Make the two manual `main.c` adjustments above (pickup bridge and Up masking) if not already present. Recompile and run SIDBOX.
6. Test a zero-quantity item mapped to an already placed kind-2 pickup, an X-flipped Guardian, nine-tile dialogue border flips, and a short nonconsecutive Idle/Talking animation.

## Checks

- Stage 4.28/4.28a/4.29/4.30 source and C runtime checks pass.
- New Stage 4.31 host C test exercises ordered per-frame Idle/Talking animation, live NPC flips, dialogue atlas flips, atlas cell 300 icon rendering, and kind-2 inventory pickup.
- New Stage 4.31 source checks exercise editor UI/serialization vs generator/runtime and keep the music startup path intact. Stage 4.27 music startup regression passes.
- **Qt6 GUI compilation on Fedora and SIDBOX hardware testing have not been done here.** This is a hardware-test candidate, not a proven hardware release.

No firmware changes are required.

# GamerGirl Stage 4.40 — Visual Death Animation Frame Picker

Based on the **working Stage 4.39 IDE source**. This is an **IDE-only** edit: one replacement `gamedesigner.cpp` at the IDE source root. The existing red/green enemy hitbox preview, death animation runtime, game helper `.c/.h`, generated C, `.sbgm` design format, SNES audio, Adventure and protected `main.c` are unchanged.

## What's new

Open **World Designer → Game Object Properties → Stompable Enemy → Death Animation**.

The **Death starting atlas frame** number now has a **Choose from atlas...** button beside it. The button also displays a thumbnail of the currently selected starting frame.

Clicking it opens a resizable **Choose Death Animation Start Frame** window:

- See the current enemy sprite's atlas as a scrolling grid of enlarged, crisp, numbered frame thumbnails. The selected frame is highlighted using the IDE's accent colour, with sharp corners.
- Click a frame, then **OK**; or double-click a valid frame to select it immediately.
- A preview strip shows up to the first eight frames of the selected death sequence, using the currently configured **Number of death frames**. Additional frames are summarized as a count.
- The picker prevents selecting a starting frame without enough following atlas cells for the configured death-animation length. Reduce **Number of death frames** in the Properties editor first if necessary.
- **No death animation** sets start frame to `-1`, making the enemy disappear immediately on defeat. **Cancel** does not modify the field.
- The original numeric field remains editable for precise changes.
- Switching to another Game Object using the editor's Previous/Next buttons refreshes the picker thumbnail and atlas to match that sprite.

The atlas numbering uses the **same zero-based, left-to-right, top-to-bottom, sprite cell width/height** as the runtime. Existing frame-count and per-frame delay remain unchanged.

## Installation

1. Back up your working Stage 4.39 IDE source.
2. Extract `GamerGirl-Stage4.40-IDE-Death-Picker.zip` to the IDE source root, overwriting `gamedesigner.cpp`.
3. Rebuild GamerGirl on Fedora using your usual Qt6 build process.
4. Open a Stompable Enemy, choose a death start frame visually, then save the world design. **Update Game Project** only if you changed game data — installing this GUI change alone does not require regeneration.

**Do not replace any `gamehelpers/` files or `main.c`** for this stage.

## Checks performed

- Stage 4.40 source wiring / row-major frame indexing / sequence-end constraints: PASS.
- Stage 4.39 red and green collision preview source/geometry tests: PASS.
- Stage 4.38 death animation / persistence / generator source tests: PASS.
- Compared the new source against Stage 4.39: only `gamedesigner.cpp` changes; old helper/runtime files are unchanged.

Qt6 development packages are **not available** in this environment. Fedora Qt6 compilation and live GUI testing are **not yet verified**.

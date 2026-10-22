# Stage 5.4h — Copy Adventure Atlas / Dialogue Position From Another World

Base: Stage 5.4g. No changes to game rules, world manager, runtime, or user-owned `main.c`.

## Install changed-files ZIP

Replace these files at the *root of your SIDBOX IDE source tree*:

- `gameadventureeditor.cpp`
- `gameadventureeditor.h`
- `gamedesigner.cpp`

Rebuild the Qt6 IDE as normal. Existing `.sbgm` files do not need conversion.

## Using the two copy buttons

1. Save the world whose dialogue appearance you want to reuse.
2. Open the *destination* `.sbgm`, then **Adventure Editor**.
3. On **Dialogue Box Atlas**, click **Copy from Another World...** and choose the saved source `.sbgm`. This copies the atlas selection, nine tile indices, per-cell X/Y flips, tile size, foreground text and outline colours, text outline, and typing speed. The destination world must already have a matching **Tile Atlas resource** (the same PPB path is preferred). If the atlas is absent, import it into the destination Game Resources first and repeat. When only a matching name exists but the path differs, the IDE explicitly requests confirmation.
4. On **Dialogue Position**, a separate **Copy from Another World...** copies only X, Y, width and minimum height. The drag-preview and position spinboxes update immediately.
5. Click **OK** in Adventure Editor, then **Save** your destination world (`.sbgm`). Clicking Cancel discards these copied settings.

Both pickers scan other saved `.sbgm` files under the game project folder, excluding generated/build directories. The source world is read-only; **NPCs, dialogue text, answers, triggers, inventory and quest events are never copied**.

## Tests and scope

`python3 stage54h_tests/test_stage54h_copy.py` checks editor-call wiring, source filtering, atlas ID remapping, field-group isolation and cancel/commit boundaries.

**Qt6 IDE compilation and interactive GUI verification must still be performed on your Fedora system.** Qt6 headers/libraries are not installed in the build environment used to prepare this patch.

V2 GUI Designer and all game runtime / `.rulec` / `.ruleh` files are unchanged. This is entirely a design-time IDE feature.

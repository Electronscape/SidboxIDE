# Stage 5.7: Shared Tile Stamp Banks per Tile Atlas

Source baseline: **CoderGirl Stage 5.6**. This changes **IDE design-time assets only**.
The SIDBOX runtime `.map` collision/graphic cell format and helper engine have **not changed**.

## What changed

* A tile stamp bank belongs to its PPB Tile Atlas path, not an individual `.sbgm` world.
* The project's `.proj` now contains `gameTileStampBanks`, a JSON object mapping project-relative atlas paths to arrays of tile stamp definitions (name, size, graphic IDs, collision IDs, X/Y flip flags).
* Each world still stores `tilemap.atlasPath`, but `tilemap.stamps` is no longer written to new world `.sbgm` saves.
* A map opened with the same atlas path reads the same bank from `.proj`. A different atlas gets a separate bank.
* Changing the selected atlas inside the editor swaps the active tile stamp bank. Unsaved edits to either atlas bank remain in the editor until Save / Apply, including Undo / Redo.
* The Tile Stamp Remove button asks for confirmation; **No** is the default. Removing a definition does NOT erase already-painted map cells.
* Tile Stamp rename commits with Enter as well as editingFinished. Enter doesn't close the editor.
* Stamp banks saved by another open world will not silently be overwritten by a stale editor. Close/reopen the stale world when warned.

## Migration

A world with older inline `tilemap.stamps` will seed the project's atlas bank if no bank exists yet for that atlas. Once a project bank exists, the project bank takes priority. The first imported bank wins when multiple demo worlds previously had *different* local stamps but use the same atlas.

The demo platformer is disposable, so any older per-world stamp layouts that don't match the first imported bank may simply be recreated. Painted map tiles don't disappear because stamp painting had already expanded graphics/collisions/flips into normal cells.

## Test on the IDE

1. Compile the new IDE and open a demo world (e.g. forest), choose Atlas A, create a tile stamp, rename with Enter, then Save.
2. Close the editor, open another world (e.g. world1), choose the **same exact PPB** as Atlas A. The same stamp bank should appear immediately. Paint a stamp and Save.
3. Choose a different PPB, Atlas B: its stamp bank should initially be independent. Add a stamp, then switch back to A. A's original stamps should reappear. Switch to B again; its newly created stamp should still be there.
4. Click Remove on a selected stamp. Test **No** (stamp remains), then **Yes** (stamp is removed). Existing painted tiles must not change.
5. Save, reopen the two worlds, verify Atlas A and B retain separate banks.
6. Rebuild and run on SIDBOX. No new helper engine is required; the runtime works with regular painted map cells.

## Source files changed

* `gametilemap.h` / `gametilemapmodel.cpp`: cached atlas banks and stamp encode/decode validation.
* `gameglobalstamps.h`: project storage and world JSON projection.
* `gamedesigner.h` / `gamedesigner_project.cpp`: load, migration, save and conflict checks.
* `gametilemap.cpp`: atlas switching, undo restoration, delete confirmation, Enter rename.
* `gamedesigner.cpp`: refresh editor's bank cache after a successful Save.
* `development/tests/test_stage57_atlas_stamp_banks.py`: source-level regression.

## Verification here

PASS: Stage 5.7 source contracts, Stage 5.6 slope/loop source regression, Stage 5.2 world manager, Stage 5.2 world feature integration, Stage 5.4f player/world registration.

Not verified: compiled Qt6 IDE, live GUI editing, real SIDBOX hardware. **Build and test on the user's system.**

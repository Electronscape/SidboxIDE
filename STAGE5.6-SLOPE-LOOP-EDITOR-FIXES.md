# CoderGirl Stage 5.6: Global Slope + Loop Editor Fixes (22 October 2026)

This builds directly on **Stage 5.5**, not the original 08:34 IDE archive. Source-only; no Qt6 executable was compiled here.

## Fixed

1. **Remove slope** in the Collision Stamps bank is enabled on selection. Clicking Remove deletes the shared definition from the working bank, removes its placements in the current map, clears their reserved collision cells, and shifts surviving indexes in the current map. On **Save / Apply+Yes**, other saved `.sbgm` worlds in the same project directory are rewritten to use the new global indexes. Deleted placements are dropped and their collision cells cleared in those other worlds.
2. **Rename slope with Enter** now explicitly commits on `returnPressed` as well as losing focus, without letting the parent dialog treat that Enter as Apply. Clicking the tick still confirms the slope edit. Empty names are not saved.
3. **Global loops visible**: The Loop Tracks tab now has a clearly labelled `Global Loop Stamp Bank (all worlds)` list, and a separate `Placed Loops (this world only)` list. Choosing a global definition and clicking **Place Stamp** adds it to the current level. The project `.proj` remains the sole owner of loop definitions.
4. Original-bank identity is tracked only in editor memory, so **Undo/Redo before Save** and deleting any stamp (not just the last) reindex correctly. After Save, the editor rebases indexes and clears old undo snapshots, so a second Save cannot shift them again.

## Deliberate constraints

- All worlds affected by a deletion should be **closed in other editor tabs**, or reopened after the deletion. Stage 5.5's stale shared-bank protection still blocks overwriting global changes from an older open tab.
- All worlds should be saved/migrated through Stage 5.5 first. If a legacy `.sbgm` contains a private slope definition not yet present in `.proj`, deletion is refused with a clear message. Save that world first, then retry.
- If another world was already exported to `gamelevels/*.c`, **republish/rebuild all worlds** (F5 or Update Game Project) after deletion, because its previously generated C will still contain the old numeric indexes until refreshed.
- Stage 5.6 does **not** change loop physics, add a global loop deletion button, or globalise graphical tile stamps.
- Preflight checks world JSON before writing the other worlds. File commits are atomic one by one, not an all-files transactional rollback; backing up a project remains sensible when changing a global bank.
- The user's `Platformer3Testing` worlds are disposable demo data. The source still aims to avoid unrelated level corruption rather than depending on that assumption.

## Files changed from Stage 5.5

- `gametilemap.h`: in-memory original global slope identity and Delete UI state
- `gametilemap.cpp`: slope delete/rename; explicit global loops list; Save/undo rebasing
- `gamedesigner_project.cpp`: original-bank map setup; remap/save shared bank
- `gamedesigner.cpp`: Save callback rebase
- `gameglobalstamps.h`: remap other `.sbgm` references and remove deleted collision cells
- `development/tests/test_stage56_global_stamp_editor.py`: source regression

## Recommended test

1. **Close other world tabs**, open `forest`, open the tile editor's **Collision Stamps** tab. Select a slope and click Remove. Save. Check it has vanished from `.proj`, and its placements are gone.
2. Open `world1` afresh, check remaining slopes still have their intended geometry/positions and the deleted slope's collision cells are empty. Undo before Save can restore a removed stamp; after Save its removal is a new baseline.
3. Double-click a slope, type a new name and **press Enter**. Confirm the name stays changed; click the tick, Save, reopen both worlds, check it persisted.
4. In `forest`, choose the **Loop Tracks** tab. The global list should show *all* definitions even if this world has no placements. Select one, choose **Place Stamp**, and confirm a new placement appears in the lower list. Save and check `world1` sees the same global bank after reopening.
5. **F5 / Update Game Project** to regenerate the world C before testing SIDBOX gameplay.

## Checks run here

- Stage 5.6 source contracts: PASS
- Stage 5.5 shared loop C runtime test (`cc -std=c11 -Wall -Wextra -Werror`): PASS
- Stage 5.2d, Stage 5.3/5.4, Stage 5.4f, Stage 5.4i integration/source tests: PASS
- Qt6 IDE compilation, interactive editor, ARM gameplay and physical SIDBOX: **not tested** (Qt6 development headers unavailable here).

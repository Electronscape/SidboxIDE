# Stage 5.85 | Optional Inventory Rules World Sync

**Baseline:** CoderGirl IDE Stage 5.84 (24 Oct 2026)

## What's new

Open **Adventure Editor → Inventory Items** and toggle **Can Drop** or **Can Discard** on an item. If exactly one item with the same name (case-insensitive) is found in another saved `.sbgm` world, a prompt lists those worlds and asks whether to apply that rule to them too.

Choose **Yes** to queue that exact rule for the listed worlds; **No** means only the current world is changed. For other inventory rules, select the row and click **Sync Selected Item Rules...**. That explicit button offers to copy Can Drop, Can Discard, Max Owned and the USE stat/delta/consume settings together.

Changes to other worlds are committed *only if* you press **OK** in the Adventure Editor, using `QSaveFile` for atomic writes. **Cancel** discards all queued sync changes. Once you leave the editor, save the current world and select **Update Game Project** to regenerate code.

## Guardrails

- Matches only exact case-insensitive **Adventure inventory item names**, not placed-world-object names or local pickup type numbers.
- Never creates items in other worlds, never overwrites their PPB/icon, starting quantity, pickup kind, NPC dialogue, or world geometry.
- Ambiguous duplicate names in either world are skipped.
- Does not enable discarding NPC-required items.
- Only syncs saved `.sbgm` files in the project, excluding generated output and hidden editor folders.
- If a target file changed on disk after its approval prompt, the sync skips it rather than overwriting newer changes.
- The user must approve the change; default prompt button is **No**.

## Changed source files

- `gameadventureeditor.cpp`: offers rule sync and safely commits approved updates.
- `splashscreenwidget.cpp`: `Build: 5.85.241026`.

All other Stage 5.84 files remain as-is; no generated game code or user-owned `main.c` is changed.

## Quick Fedora acceptance test

1. Back up your game project and build the updated Qt IDE.
2. Open Forest's Adventure Editor → Inventory Items → Flower, toggle **Can Drop**. Confirm that World1 appears and choose **Yes**.
3. Press **Cancel** in the Adventure Editor. Reopen World1 and confirm there was no change.
4. Repeat, choose **Yes**, then press **OK**, save Forest, and reopen World1. Flower's **Can Drop** should now match.
5. Repeat with **No** and confirm only Forest changes. Verify artwork and NPC choice data remain unchanged.
6. Check **Sync Selected Item Rules...** with a normal item, and test a deliberately duplicated item name. No ambiguous matches should be copied.
7. Use **Update Game Project** to regenerate before testing on hardware.

**Verification:** Source/static checks and a test using copied Forest/World1 JSON passed. Qt6 compilation and GUI interaction tests were not available in the container.

# Stage 5.86 | Inventory world sync clarity and queue fix

**Baseline:** Stage 5.85 (24 October 2026).

The Adventure Editor's Stage 5.85 world-sync confirmation could be misleading. It offered a sync just because item names matched, even when the requested rule values were identical. Worse, if you approved a change and later changed your mind, choosing **No** on a subsequent prompt did not cancel an earlier approval. An unchanged world could also produce no completion message.

## Changes

- The prompt now identifies the **exact inventory rule differences** in each saved world: e.g. `world1.sbgm | Can Drop: No -> Yes`. Only those differing fields are queued on Yes.
- When another world already has the same values, the editor reports **no applicable differences** rather than offering to sync an unchanged value.
- **No** clears any earlier queued approval for those rules. Toggling a checkbox back so it matches the saved other world also cancels stale queued changes.
- Quest/NPC-required item **Can Discard** remains protected, and the prompt explicitly tells you if that rule was omitted.
- The final message distinguishes worlds actually written, worlds where nothing needed writing, and fields/files that could not be updated. It reminds you to save the current world and Update Game Project.
- When using **Sync Selected Item Rules...** without a selected item or another uniquely named match, the editor explains why it cannot sync.

Only matching Adventure **inventory item names** identify shared items (case-insensitive). World object names, type IDs, artwork, initial quantities, object placement, and NPC dialogue are never changed by syncing.

## Installation

Replace `gameadventureeditor.cpp` and `splashscreenwidget.cpp` in your IDE source tree. Rebuild the IDE. Splash version: `Build: 5.86.241026`.

No game runtime files, exported worlds, or user-owned `main.c` have changed.

## Suggested Fedora GUI test

1. Open Forest Adventure Editor, select Flower, turn Can Drop on. If World1 differs, the confirmation must say `Can Drop: No -> Yes`.
2. Choose Yes. Without closing the Adventure Editor, switch Can Drop back off. The IDE should state there is no difference and clear the old queued approval. Click OK. Check World1 did not unexpectedly change.
3. Try Yes, then toggle again and choose No. Check World1 remains unchanged.
4. Finally approve a real change and click OK. The completed dialog must report the number of other world files actually saved. Save Forest and use Update Game Project.
5. With Can Drop identical in both worlds, click Sync Selected Item Rules. It should say nothing applicable needs copying (unless some of the other rule values differ).
6. Try a quest item with protected Can Discard: it should not be offered as a writable setting in a target world where an NPC requires the item.

**Validation:** read-only source assertions and matching checks against the supplied Forest and World1 data passed. Qt6 is not installed here, so a full IDE build and GUI interaction remain to be tested on Fedora.

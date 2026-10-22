# CoderGirl / GamerGirl Stage 5.31 — FIRE2 Door Priority and Adventure Inventory Polish

Base: Stage 5.30. Date: 22 October 2026.

## 1. FIRE2 priority: NPC → Door → Inventory

The world-object door test now reads the **same live player hitbox** used by `gameworlditems_after()`, including `offset_x`, `offset_y`, width, height, and the current 100ths-of-a-pixel position. Previously the inventory check could use the unadjusted sprite rectangle and steal FIRE2 from a narrow Goto World trigger.

`gameworlditems_before()` registers the current adapter and `gameworlditems_init()` clears its pointer. The readonly query does not activate or modify any triggers. NPC conversation continues to have first priority, and FIRE2 opens the inventory only when no NPC/door action owns the press. Existing `main.c` doesn't need modifying.

## 2. Dialogue box padding

In Adventure Editor → Dialogue Position, the existing per-world setting is now labelled **Dialogue box padding (0 / 8 px)**. It affects speaker, dialogue text, answer choices, and player's reply bubble inside the box. **Inventory** is intentionally independent and always uses an 8px inset.

## 3. Inventory UI

- Heading is simply `Inventory:`.
- Removed UP/DOWN/FIRE command banner, all asterisk markers and PROTECTED footnote.
- Only footer hint is `FIRE2: CLOSE`, aligned to the right within the frame.
- Selector and icon/name are moved right, within the 8px inset.
- Only items marked **Can discard?** display two actions: `DROP` and `DESTROY`.
- LEFT selects `[DROP]`; RIGHT selects `[DESTROY]`; FIRE1 executes the chosen action.
- `DESTROY` has a safe NO/YES confirmation, defaulting to NO; FIRE1 accepts, FIRE2 cancels.
- `DROP` places one recoverable icon in the **current world**. It is not destroyed. The player must leave the dropped icon and touch it again to pick it up, preventing an instant re-pickup. A visible 16×16 fallback marker is drawn if no valid icon atlas is available.
- NPC puzzle/required items remain non-discardable via the existing generator's protection rule.
- Inventory auto-resizes in height for 0 to 10 owned item types. At 11+ types it shows ten rows and scrolls with UP/DOWN.
- 2×2 composite atlas icons remain supported, drawn into a 16×16 slot.

## 4. World-local drops

The runtime reserves 16 drop slots per world (no heap allocations), and the generated world Adventure source snapshots/restores these through the existing Stage 5.21 world-progress hooks. Inventory counts still use the shared world manager by item name. Dropped items are drawn through the existing `game_adventure_draw_npcs()` call, so user-owned `main.c` stays untouched.

Drop snapshots persist during the **running game** when changing worlds, not through reboot/power loss. Attempting to drop into a full 16-slot pool leaves the item in the inventory. Drops remain at their original coordinates; they don't use extra falling/physics simulation.

## Install / test

Replace the six production files in the Stage 5.30 IDE source while preserving paths. Rebuild CoderGirl, **Update Game Project** (important: gameworlditems, gameadventure, and common runtime are regenerated), then compile the game. No changes to custom `main.c`.

Suggested SIDBOX checks:

1. Stand just inside a narrow Goto World FIRE2 door; press FIRE2. Door must work, and inventory must stay closed.
2. Away from doors/NPCs, press FIRE2. Inventory opens. Near NPC, conversation wins.
3. Try 0, 1, 3, 10 and 11 inventory item types; window grows for up to 10 and scrolls after that.
4. Give a disposable item two copies; choose DROP with LEFT then FIRE1, close with FIRE2, walk away, walk back: the icon reappears in the inventory.
5. Drop one item, go to another world, return; the world-local drop should still be there.
6. Choose DESTROY with RIGHT then FIRE1. Confirm defaults to NO, and FIRE2 cancels. Confirm YES with FIRE1 only after selecting it.
7. Verify NPC-required puzzle items cannot be dropped or destroyed.
8. Switch dialogue padding Off/8px, save design, Update Game Project and test both NPC and reply box placement.

## Checks completed here

- Strict host GCC build `-std=c11 -Wall -Wextra -Werror` and new inventory/drop persistence tests PASSED.
- 10/11-row geometry test PASSED.
- Actual generated FIRE2 door query function tested with offset hitbox under host GCC PASSED.
- Two-world namespaced generated Adventure integration PASSED.
- Stage 5.28 FIRE2 priority, Stage 5.27 secret dialogue and Stage 5.25 missing-item tests PASSED.
- Qt6 IDE GUI compilation and physical SIDBOX execution are **not verified here**.

Splash: `Build: 5.31.221026`.

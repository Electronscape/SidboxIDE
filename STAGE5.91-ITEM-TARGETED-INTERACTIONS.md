# Stage 5.91 (24 October 2026): Proximity inventory-item interactions

This release adds a reusable **item-locked Trigger** interaction to the CoderGirl V1 game engine. It is not game-specific.

## Configuring a key-operated door

1. In Adventure Editor → Inventory Items, define the item by its **exact name** (e.g. `Brass Key`). Ensure the player can acquire it. Inventory is shared by item name between worlds.
2. In the Game Designer, place a `Door` Game Object (normally active) and a `Trigger` Game Object (the interactive region, with its own sprite or overlay).
3. Edit the Trigger's **Trigger / Activate** properties: choose `Brass Key` under **Interact with inventory item**. Set **Interaction reach (px)** (e.g. 32) and optionally **Consume one item on successful USE**.
4. Set **Activate/deactivate object** to the Door and **Linked action** to `Disable target`. Optionally enable **Remove switch after activation (one-shot)** to remember an unlocked door when returning to the world.
5. Save the world, run **Update Game Project** for all worlds and rebuild the game. Your user-owned `main.c` stays untouched.
6. In game: press FIRE2 near the trigger, select an item with UP/DOWN, press FIRE1 to try it. FIRE2 closes. An incorrect item does nothing and is not consumed. On success the linked action fires; item consumption is optional.

## Other objects

The same Trigger can look like a chest, statue or rock. Link it to another Game Object to reveal/hide/enable something. A **talking rock** can already use an NPC design/dialogue with rock artwork. This stage does *not* add a new trigger-to-dialogue-node editor control or a reward-picker: NPC dialogue and existing linked-object/music actions remain the available outcomes.

## Details and safety

- The player-to-object distance uses the nearest edges of the two hitboxes, allowing interactions next to solid doors. Reach is 0–128 pixels.
- When multiple item-locked triggers are near, the closest one is selected. This is a read-only probe until FIRE1 confirms a correct item.
- Ordinary touch/FIRE2 triggers are unchanged. Item-locked triggers skip the normal touch/FIRE2 activation path, so they cannot unlock accidentally.
- Interaction item IDs are stored by **inventory name**, not world-local pickup type or table slot. A missing name causes an export error rather than a nonfunctional lock.
- A one-shot interaction deactivates its world object. Existing per-world object snapshots preserve that state across world changes in the running game; this does not introduce permanent TFCard save slots.
- The normal inventory USE effect (e.g. a Health potion) remains separate from target USE: on a locked object the selected item targets the object, not the player's stat.
- Logic Flow shows a named incoming `FIRE2 nearby → USE` edge from the inventory item to the Trigger, then existing linked-object edges to its target.
- No new firmware calls, allocations or per-frame asset loads. No modifications to game project `main.c`.

## Modified source files

- `gamedesigner.h`, `gamedesigner.cpp`, `gamedesigner_project.cpp`, `gamedesigner_export.cpp`
- `gamefloweditor.cpp`
- `idelibs/codehelpers/game/adventureruntime.ruleh`, `.rulec`
- `idelibs/codehelpers/game/gameadventure.rulec`
- `idelibs/codehelpers/game/gameworlditems.ruleh`, `.rulec`
- `idelibs/codehelpers/game/worldobjects.ruleh`, `.rulec`
- `splashscreenwidget.cpp`

## Testing status

Native GCC tests passed for the item-select modal, wrong/correct items, consume/retain, ordinary inventory fallback; range-based closest target, one-shot and reusable actions; existing ordinary FIRE2 triggers not firing item-locked triggers. Qt6 development headers are unavailable in this environment; the IDE and actual STM32 firmware have **not** been compiled or hardware-tested here. Always keep a backup before applying the drop-in.

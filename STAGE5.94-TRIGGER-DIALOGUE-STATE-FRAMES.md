# CoderGirl Stage 5.94: Trigger Outcomes and Static State Frames

Build: `5.94.241026`

## Installation

Unpack the ZIP into the IDE source root, preserving the paths. Rebuild the Qt6 IDE.
In the Game Designer, configure the object and trigger, save the world, run **Update Game Project**, then rebuild your SIDBOX game. This regenerates the shared Adventure and Game World Items helpers. **Do not overwrite your hand-maintained `main.c`.**

## New settings (Game Object Properties)

**All non-collectable Game Objects, including Door / Solid blocker:**
- **ACTIVE state frame (-1 = default)**. Sprite atlas index displayed while active/solid.
- **INACTIVE state frame (-1 = hidden)**. Sprite atlas index displayed after disabling the object. This frame remains visible **without restoring collision**. Use 0 for locked and 1 for unlocked, for example.
- Both indices must exist in this object's PPB atlas. Static state frames cannot be combined with a looping object animation or a multi-cell sprite stamp. The exporter shows an actionable error if configured incorrectly.

**Trigger / Switch with a required inventory item:**
- **On success: dialogue**. Choose an existing node in **Adventure Editor → Dialogue**. The selected node opens with the existing Adventure dialogue skin, text and choice/actions. A node with no choices displays a simple "The door is now open" message; press FIRE2 to close it.
- **On success: give item**, and **Reward quantity**. Uses the Adventure inventory definition by NAME, not a world-local ID; inventory capacity is checked **before** consuming the required key or opening the linked object. If the key frees a slot, the reward can use that slot. If there isn't enough room, the interaction remains pending and the USE selector says **Inventory full! Drop something.**
- **On success: player stat**, and **Stat change (+ / -)**. Reuses `gameadventure_apply_item_stat()` and shared player stats. Stat changes happen only upon successful USE.

The existing target enable/disable/toggle, music action, sound events and one-shot option still work. Dialogue nodes can supply their own existing choices and quest/event actions. There is **no new standalone global quest-flag storage system** in this stage.

## Example

1. In Adventure Editor, create a dialogue node named **Door**, with text **The key fits. The door is now open.** and no choices.
2. Make a door with two PPB atlas frames. In the door's Game Object Properties select **Door / Solid blocker**, set ACTIVE frame **0** and INACTIVE frame **1**. Leave its **Animated** checkbox off.
3. Create a Trigger on or beside the door. Set **Interact with inventory item** to your key, **Activate/deactivate object** to that door and **Linked action** to **Disable target**.
4. Set **On success: dialogue** to your new Door node. Optionally set **Consume one item on successful USE**, a sound, reward, or player stat change. **Remove switch after activation** makes it one-shot.
5. Save, Update Game Project, build and test. The unlocked door is non-solid but its opened frame remains visible when leaving and revisiting the world during the game.

## Scope and compatibility

- Generic project rules and generated C. No special-case game name, item name, character or world.
- Runtime's world snapshot already persists the object's active state and sprite state **across world transitions within a running game**. This is not yet a TFCard power-off save-game system.
- Legacy objects without state frames retain their original hide-on-disable and animation behaviour.
- The interaction outcome controls are enabled for **item-required Triggers**. Ordinary touch/FIRE2 triggers retain their earlier action and music behaviour.
- No change to `main.c`, editor syntax highlighting threshold (2048 KB), game assets or `.sbgm` world files.
- Existing animation remains available; this adds *static state frames*, not a new animation sequencing feature.

## Verification

- `development/tests/test_stage594_trigger_outcomes.py`: native GCC Adventure runtime test, including one freed inventory slot, reward and dialogue modal.
- `development/tests/test_stage594_worlditem_interaction.py`: compiles and runs the actual item-interaction function extracted from `gameworlditems.rulec` with generated Stage 5.94 actions, testing wrong item, full inventory and success.
- Structural checks for JSON round-trip fields, exporter markers and state-frame painter.
- **Not yet verified:** Qt6 compilation (Qt6 headers unavailable here), Fedora GUI interactions and real STM32 hardware.

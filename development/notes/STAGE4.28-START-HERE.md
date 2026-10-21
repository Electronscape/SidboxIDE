# GamerGirl Stage 4.28 — Advanced Platformer Adventure (first integrated version)

New **Adventure Editor...** button lives below the Game Resources tree.
This is **optional** and does not change Basic Platformer projects.

## Adventure Editor

- **Inventory Items:** name, collectable kind (0=manual, 1 coin, 2 health,
  3 key, 4 gem), capacity, starting amount, icon tile index. The generated
  callback adds **one** matching inventory entry per collected object.
- **NPCs:** choose a placed **foreground decoration Sprite**, dialogue start
  node, and talk radius. NPCs are drawn through the existing sprite path.
- **Dialogues & Choices:** speaker, long wrapped dialogue text, up to three
  answers, typed player response, jump to another node, require/give/take
  inventory item, custom event number, or no-code activate/deactivate/toggle
  of an existing Game Object (for instance, deactivate a locked door).
- **Dialogue Box Atlas:** select any indexed foreground Tile Atlas PPB,
  assign 9 cell indices (3 x 3; corners, sides, centre), choose cell size,
  and use the live editor preview. Atlas is loaded by gameassets and the
  box tiles are drawn over gameplay. Defaults to plain box without an atlas.

All this metadata saves in the existing `.sbgm` under `adventure` (no new
version or firmware format). Only IDs are stored for resource links.

## Update Game Project

Automatically installs the optional `gameadventureruntime.c/.h` from the
SDK templates, exports `gameadventure.c/.h` with static tables, includes
the skin atlas in `gameassets`, regenerates `maingame.c.txt`, and refreshes
`main.c` **only if IDE-owned and still unedited**.

Existing update backups/rollback include the generated files and helpers.
No firmware changes, no changes to .pal/.ppb/.map and no new dynamic memory.

## SIDBOX controls

- **FIRE2** near an NPC: talk.
- **UP / DOWN**: choose a response.
- **FIRE2**: complete typing/select response/continue dialogue.
- **UP + FIRE2** away from an NPC: open inventory.
- **FIRE2** in inventory: close.
- Game movement and moving world objects pause during dialogue/inventory.
- Music and colour cycling continue normally.

Dialogue appears as a tile-atlas-framed panel with wrapped NPC text.
The chosen response types above the player's head.

## Inventory, puzzle logic, and existing Collectables

The generated IDE-owned main calls `game_adventure_collect(item->kind)` from
the normal collectable callback. Repeated pickups increase quantity by one
(up to capacity). Use `game_adventure_quantity`, `game_adventure_add`, and
`game_adventure_remove` from your own code if desired.

Dialogue choice prerequisites check the item quantities before applying
an action. A choice can take/grant an item and disable a linked door.
To add custom puzzle logic, implement a strong
`void gameadventure_on_event(uint16_t event_id)` in a **user-owned source
file**. The generated weak default is otherwise harmless.

## IMPORTANT: hand-owned `main.c`

If you've edited `main.c`, the IDE does NOT overwrite it. This is intentional.
Use the regenerated `maingame.c.txt` as a reference to add:

- include `gamehelpers/gameadventure.h`;
- `gameadventure_setup()` after `gameassets_init()`;
- `game_adventure_input()` after VBlank, before normal physics;
- pause normal physics when `game_adventure_open()` is true;
- `game_adventure_collect()` in the pickup callback;
- `game_adventure_draw()` after foreground tiles, before buffer display.

Without those calls in your hand-edited main, resources will generate but
adventure controls will not activate.

## Important practical limitations in this first integrated version

- Only one conversation/inventory overlay at a time.
- 64 item types, 256 dialogue nodes, up to 3 choices per node.
- Stationary NPCs reference **placed decoration sprites**; moving/spline
  NPC logic is not yet part of this version.
- Inventory state is RAM-only; saving across game sessions is future work.
- Dialogue uses SIDBOX's current font (ASCII is safest for now).
- The nine-tile box renderer draws repeated atlas cells each frame; try a
  small atlas and test hardware frame/audio performance.
- An Adventure-generated update and a complete Qt6 build still need
  verification on your Fedora machine. Host-side C logic checks passed.

## Suggested hardware test

1. Back up your game. Open the Advanced Platformer design.
2. Place a 100%-scale stationary Sprite named `Guardian` (not `player`).
3. Add item `Brass Key` with collectable kind `3`, capacity `1`.
4. Add a Dialogue Node: "Where is the key?" and choices. Make one require
   Brass Key, take it and **deactivate** your Door Game Object.
5. Add an NPC linked to `Guardian` and start Dialogue Node 0.
6. Choose a Tile Atlas for the dialogue border, starting with 9 8x8 cells.
7. Save Design, **Update Game Project**, compile, test.
8. If your main.c is hand-owned, apply the generated example integration.
9. Check talking, missing-key choice, collecting key, opening door, inventory,
   animation/audio smoothness, and loading older game designs.

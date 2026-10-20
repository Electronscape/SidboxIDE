# SIDBOX GamerGirl — Stage 4.07: Draggable Player Size Reference

Base: GamerGirl Stage 4.06 full source. No firmware changes.

## Changed source files (IDE only)

- `gamedesigner.cpp` — provide the actual Game Resources sprite named `player` to the tilemap editor. It uses the same decoration-sprite selection rule as the generated player code, including a current atlas frame and world-editor scale.
- `gametilemap.h` — standalone reference position fields and a small editor API.
- `gametilemap.cpp` — on-map sprite overlay, theme-coloured outline, checkbox, open/closed hand drag cursor, pan/zoom coordination, undo support.
- `gametilemapmodel.cpp` — save/load optional `referencePlayerX`/`referencePlayerY` fields in the `.sbgm` tilemap JSON; old designs open without them.

## How to use

1. In Game Resources, have a **Sprite** named **player** (case-insensitive), with a valid image and object type **decoration**. This is how the generated platformer detects the physics player.
2. Open Tilemap Editor. An optional **Show player reference (drag to check gaps)** checkbox appears only when that sprite exists and its preview loads.
3. Left-drag the translucent, dashed-outline reference over tunnels, slopes and gaps; the pointer uses open/closed hand cursors. When zooming or panning, the reference stays in world coordinates.
4. Untick the checkbox to paint tiles beneath the reference. This toggle does not change the player location.
5. **Save** (without closing) or **Apply to Design** commits the reference position to the `.sbgm` design. Cancel discards changes since the most recent Save. Undo/Redo handles reference movements.
6. Close and reopen the editor: the reference stays where you saved it. Initially, before any reference placement is saved, it uses the player's real World Editor position as a starting point. This is only a visual reference: repositioning it **never** changes the Game Resources player's X/Y, player spawn, runtime physics or tile data.

**Important:** the reference shows the visible sprite frame/scale. If an animation defines a smaller collision hitbox, the game's physical clearance can be different. This reference is for visual sizing, not runtime collision simulation.

## Data compatibility

The only new saved values are optional JSON fields under `tilemap` in `.sbgm`. Older designs work unchanged. Exported `.map` files, level data and firmware are unchanged. Neither the image nor its location is exported into the game.

## Verification

- Run `python3 development/tests/test_stage407_player_reference.py` (focused source assertions).
- Stage 3.99 and Stage 4.00–4.06 source checks passed.
- The native Qt6 compilation, mouse interactions and actual Fedora GUI appearance still need testing on your machine; Qt6Widgets development files are not installed in this environment.

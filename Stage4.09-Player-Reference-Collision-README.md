# GamerGirl Stage 4.09 — Tilemap Player Quick-Place and Collision Clearance

Based on Stage 4.08 full IDE source. No firmware, game helpers, generated game source, or map export format changes.

## Player reference: Space to move

- Hover the mouse over the Tilemap Editor's **map canvas** (not the tile atlas, stamp editor, or toolbar).
- Press **Space**: centre the reference player's *sprite* on the pointer. Her top-left is clamped so the entire sprite fits inside the level.
- Existing left-drag movement still works. Space does not paint/erase tiles or move the real player.
- Undo/Redo treat a Space move as a single edit. Save or Apply persists the reference position separately in the .sbgm, exactly like Stage 4.07 drag.
- This shortcut acts only when the player reference is shown, the mouse is inside the canvas viewport, and there isn't a paint, paste, pan or drag in progress.

## Collision clearance overlay

A new **Show player hitbox / collision clearance** checkbox appears under Show player reference when the map's game design contains a `player` Sprite.

The scaled player image is still the same as in Stage 4.07. Inside it, the actual collision rectangle is drawn with a themed contrast-independent colour:

- GREEN — no collidable region touches the stationary reference hitbox.
- RED / BLOCKED — intersects an ordinary solid tile, a solid custom zone, or the solid interior of any ramp: standard 45-degree, v3 legacy per-pixel, or v4 multi-cell point/Bézier stamp (including mirrored stamps).
- ORANGE / HAZARD — overlaps a damaging hazard tile (which is non-blocking).
- YELLOW / ONE-WAY — overlaps a one-way platform. This is a surface indication; it is not a solid wall from below.
- BLUE / ZONE / DOOR — overlaps a pass-through custom zone or door.

Contacted map cells are tinted as well as the hitbox border, to help find the trouble spot. Priority is RED > ORANGE > YELLOW > BLUE when several types overlap.

**Hitbox selection**: GamerGirl's V1 player physics uses the **Player Animation Editor** hitbox (`hitboxX/Y/W/H`) when player animations/hitbox integration is enabled in the game code. The Game Object Properties `hitWidth/hitHeight` applies to ordinary objects, not to the player physics sprite. Stage 4.09 reads the saved `.sbanim` sidecar if its `cellWidth/cellHeight` match the player preview frame and its hitbox fits. Otherwise it uses the full player sprite frame. The tilemap preview scales that rectangle along with the displayed player. If your own `main.c` has animation integration disabled (`GAMERGIRL_PLAYER_ANIMATIONS 0`) or has custom physics, the real game can use different hitbox geometry; this preview is a geometry reference, not a 50 FPS physics/movement simulation.

Changing the overlay checkbox is presentation-only. It writes no flags into the game or saved .map. The existing reference position in the .sbgm continues to save as before.

## Installation

Changed-files package: replace these **three** files in the IDE source root:

- gametilemap.cpp
- gametilemap.h
- gamedesigner.cpp

Rebuild the IDE. The `development/tests/` scripts are optional developer checks.

## Checks completed

- All Stage 3.90–3.99 and Stage 4.02–4.09 selected Python source regression tests passed.
- Qt6 development headers/tools are not available in this sandbox; Qt6 native build and interactive UI checks still require the Fedora IDE environment.

## Suggested Fedora test

1. Open a game containing the `player` Sprite, then open Tilemap Editor.
2. Hover a location and press Space; check it jumps, centres, clamps at all four edges, and Undo/Redo work.
3. Save, close, reopen; the reference should be in the saved location, while the real World Editor spawn remains unchanged.
4. Toggle the hitbox indicator and move over empty space, solids, hazards, one-way platforms, 45-degree slopes and v4 Bézier stamps.
5. Set a narrower hitbox in Player Animations, save the .sbanim sidecar, reopen the Tilemap Editor; verify it displays the smaller physical rectangle. Verify your runtime code actually enables that hitbox before treating its preview as exact.

# Stage 3.89 — Breakable Game Objects + World Canvas Previews

Baseline: Stage 3.88 full IDE package, which includes the Stage 3.87 gravity/cliff fix.

## Features

### Game Objects: Breakable Object
- Configure any placed PPB Sprite as **Breakable Object** in Game Object Properties.
- **Hits to break:** 1–4. Per **placed** object; a second instance never shares the first one's counter.
- **Break on touch** checked: contact from any side; leave the hitbox and re-enter for each subsequent hit. Sensor, not solid standing surface.
- **Break on touch** unchecked: landing/stomping from above (one-way solid platform) counts once, and remains solid until the final hit. Standing on it doesn't repeatedly damage it; a jump out and another landing rearms it.
- **Bounce on each stomp** checked: directional impulse on each stomp, including final destruction; default vertical-up (11 px/frame) and 0 horizontal, adjustable -40..40 px/frame side momentum and 1..100 vertical. Applies to stomp mode only.
- Final hit deactivates the object: no further collision or drawing. No automatic respawn. `break_triggered` is exposed in the world-object struct for optional hand-written custom shatter sound/effects; it lasts until `game_world_objects_update` of the next frame.
- Saved in `.sbgm` under each Sprite's `gameObject` JSON. Old documents default to non-breakable.
- Exported in generated `gamehelpers/gameworlditems.c` and the new `gamehelpers/gameworldobjects.h/c` helper code.

### World Canvas Game Object Animation Preview
- Placed Sprites with **Animate sprite frames** enabled preview the selected **First frame**, **Number of frames**, **Frames per picture** and **Animation mode** (Loop, Once, Ping-pong) directly in the main Game Designer world canvas.
- 50 Hz editor-only timer uses elapsed time to avoid cumulative timer drift.
- Does not edit assets or affect the game's runtime animation.

### Loop Track Preview
- Game Designer **Show Tilemap** overlays dashed blue circle guides for saved Loop Tracks, labeled `LOOP 1`, etc., plus yellow entry points.
- Overlays ignore mouse input; placing and dragging game sprites stays possible. Loop geometry is edited in Tilemap Editor, not the main canvas.
- Guides draw even if the tile atlas is absent; show tilemap must be enabled.

## Installation / compatibility
1. Back up your working project.
2. Replace IDE source files from the patch and recompile GamerGirl in Qt Creator.
3. Select **F5 → Update and Compile**, confirm updated game helper installation, and ensure generated C and helper headers are refreshed together.
4. Open your `.sbgm` file in the Game Designer and set up a new Breakable Object. Test 1, 2, 3, 4 hits and bounce on hardware.
5. Confirm existing Springs, Moving Platforms, loops and cliff launch continue working.

**Important:** new `GAME_OBJECT_BREAKABLE` requires recompiling the V1 project with both `gameworldobjects.c` and `gameworldobjects.h` updated. User-owned `main.c` remains untouched; if it has custom world-player bindings, link `spring_force_vx100` for external X bounce as you already do for slidy springs.

## Tests
- `development/tests/test_stage389_breakable_objects.c`: contact latch, 4 stomps, independent counts, touch mode, bounce directions.
- `development/tests/test_stage389_editor_integration.py`: persistence/export wiring + preview/overlay source checks.
- Existing world-object, loop coast, spring, animation and splash tests passed in native/headless tests.

Qt6 is not installed in the tool container: Qt Designer GUI interactivity cannot be marked passed here. Confirm rendering and dialogue flow in Qt Creator/Fedora. Hardware acceptance is pending.

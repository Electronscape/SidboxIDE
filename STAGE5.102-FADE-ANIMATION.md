# CoderGirl Stage 5.102: Animated patterned BOB fades (25 October 2026)

Build: `5.102.251026`

## Game Designer controls

Open any placed Sprite / Game Object -> **Visual & Movements**. Below the existing BOB patterned fade percentage is an optional **Animate patterned fade** switch, with:

* **Lowest fade**: 0 to 100 percent (inclusive).
* **Highest fade**: 0 to 100 percent (inclusive).
* **Fade step**: positive percentage points per advance, 1 to 100.
* **Frames per fade step**: 1 to 65535 game frames (the SIDBOX renders at 50 Hz).
* **Ping-pong**: go from low to high and back to low without repeating the endpoint. Unchecked: jump from high to low and repeat.

When enabled, the sprite starts at **Lowest fade** each time its world/game assets initialise. The old percentage slider remains the **static fallback** if animation is disabled. For a fixed fade, disable Animate patterned fade.

**Example:** low 20, high 80, step 5, delay 2, ping-pong on: fades 20, 25, 30, ..., 80, 75, ..., 25, then 20. Each step lasts 2 frames (~40 ms). Full pulse is 48 frames (~0.96 seconds).

When step does not divide the range, the highest percentage is still reached exactly. A single fixed percentage (low equals high) is supported. Frame animation and BOB fade animation are independent; mirroring, state frames, stamps, sound and collisions are unaffected.

The Game Designer canvas previews the fade on its existing 50 Hz tick. The Game Object Properties preview and canvas update live while adjusting controls. This is still a **4x4 Bayer-pattern simulation**, since the firmware's exact dithering pattern has not been provided. The *runtime* calls the hardware BOB fade API (`BLIT_FLAG_ALPHABLEND` + `flagval[BLIT_FLAG_TYPE_FADE_VALUE]`).

## Installation and game regeneration

1. Back up your IDE and game.
2. Extract the drop-in ZIP to the root of the **Stage 5.101 IDE source**, preserving paths.
3. Rebuild the IDE.
4. In the Game Designer, choose a sprite, enable Animate patterned fade and set its range, step, frames and direction. Save the world.
5. Run **Update Game Project**, then rebuild the game.
6. Test on SIDBOX. `main.c` is user-owned and not overwritten or changed by this patch.

Unlike Stage 5.101, this stage changes generated game assets and world update code, so **regeneration is required**. Call `gameworlds_update(frames)` once per game tick as before: its generated world-items update calls `gameassets_fade_update(frames)` automatically, including scenery-only worlds. Do **not** call the fade update separately if you already call the world update.

## Runtime implementation

`gameassets.c` creates a small generated array only for fade-animated BOBs. The tick function advances each in O(1) per object even when several game frames are passed at once. No palette rewriting or software blending is performed on SIDBOX. All BOB flags other than `BLIT_FLAG_ALPHABLEND` are preserved. Animation is local to the current world's assets and restarts on world reinitialisation. No firmware changes.

## Verification

Automated GCC test runs the exact generated animation logic for ping-pong, wrap-around, non-divisible 7-point steps, frame delays and large frame jumps. Related Stage 5.100 alpha fade, 5.98 thought bubble, 5.97 dialogue, 5.94 inactive-state frame, 5.99.2 reply scaling and 5.42 sprite stamp regression tests passed.

The Qt6 desktop IDE build is unavailable in this environment, and the physical STM32H743 hardware is not available for testing. The final real-world acceptance test remains yours.

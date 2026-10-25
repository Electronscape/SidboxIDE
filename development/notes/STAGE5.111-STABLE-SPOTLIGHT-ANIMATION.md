# CoderGirl Stage 5.111.251026: Stable Spotlight + Cached Feather Animation

Based on **Stage 5.110**. This is an IDE / game-engine helper update; **no firmware changes** and **no edits to user-owned main.c**.

## What was causing the unwanted movement flicker?

Stage 5.110 already creates one feather BOB **when the world loads**; it does **not** regenerate it every frame. The visual shimmer comes from its 4×4 ordered-dither pattern moving relative to the screen when the BOB moves by 1 pixel.

New **Stable 4×4 dither** checkbox (enabled by default) aligns the whole mask and cached BOB position to the nearest 4-pixel screen grid. The dither cells therefore remain screen-stable when walking. This produces subtle **4-pixel positional steps** in the light, a tradeoff the artist can opt out of for intentionally flickering movement.

The feather BOB uses **integer-only math at world-load time**. Per-frame rendering selects an existing BOB, fills the outside via the existing rows, and does not rebuild the feather texture.

## Player Start → Spotlight

- **Feather animation**: Off / Random flicker / Pulse (ping-pong)
- **Animation feather minimum / maximum**: 0–96 pixels
- **Random time minimum / maximum**: 1–600 *game frames* between random jumps
- **Pulse frames per step**: 1–600 game frames per precached frame
- **Stable 4×4 dither**: checked by default in new worlds
- Position preview shows the minimum and maximum feather reach.

The existing **Spotlight feather** value remains the static width used when animation is off, and the fallback width if only one cached frame fits.

## Runtime strategy / memory

At world activation, generate **up to 8** different feather BOBs from minimum to maximum width, using integer arithmetic. Generate no duplicate widths when the range contains fewer than eight unique integer thicknesses. Their **combined pixel allocation is capped at 768 KiB**, with fewer cached widths automatically selected for very large lights. When only one can fit, disable the animation for that world and keep a cached static light instead. On allocation failure, fall back to the legacy non-cached renderer.

At 50 Hz, random mode chooses another cached width after a random interval; pulse visits cached widths in order and reverses without doubling the extreme values. World changes release the old cache and build the new world's settings. No changes to the existing spotlight action API or player/camera update calls are required.

**Performance note:** outside darkness under 100% still uses the existing patterned segment renderer and may cost more CPU than full black. Enlarging the radius/feather or using animated frames has not yet been measured on real SIDBOX hardware.

## Install and verify

1. Apply the Stage 5.111 ZIP to the **Stage 5.110 source tree**; rebuild the Qt6 IDE.
2. Set the new options under **Player Start → Local darkness/spotlight**; save your world.
3. Run **Update Game Project** and rebuild the SIDBOX game. Your authored `main.c` should keep its existing 3 spotlight calls unchanged.
4. Try the stable checkbox while moving, then test a 12–32 px pulse at 3 frames per step and a 2–16 px random flicker at 3–12 frames between jumps.
5. Confirm 50 FPS at the largest desired settings. Compare 100% vs 50% outside opacity if you use partial darkness.

## Test status

Stage 5.111 native GCC animation/cache tests pass; Stage 5.110 cached BOB test, Stage 5.108 spotlight actions, Stage 5.107 palette handoff, Stage 5.106 player anchoring and Stage 5.48 transitions pass. Native tests do not replace Qt6 desktop compilation or physical SIDBOX rendering/performance tests.

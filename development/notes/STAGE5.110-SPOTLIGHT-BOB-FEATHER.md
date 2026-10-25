# Stage 5.110.251026: candle-facing offsets, darkness and cached feather

Based on Stage 5.109 with all Stage 5.108 gameplay features retained.

## What changed

- Code editor IntelliSense inactivity timer: 600 -> **400 ms**.
- Game Designer > Player Start dialog now opens maximised. The main IDE is unchanged.
- Spotlight settings:
  - Mirror X offset when the player BOB has `BLIT_FLAG_FLIP_X`.
  - Mirror Y offset when the BOB has `BLIT_FLAG_FLIP_Y`.
  - Outside darkness opacity 0 to 100% (100% retains the existing solid mask).
- Settings saved to `playerStart` of `.sbgm`, exported to the generated world registry and set per loaded world.
- On world load, build a *single indexed feather BOB*, using index 0 for transparency and the reserved darkness index for visible dither pixels. Its pixel data is reused each frame, not recalculated. The BOB is freed when leaving the world or on shutdown.
- At 100% outside opacity the outer screen uses solid `gfx_rectf` spans, and the cached feather BOB is drawn once per frame. This replaces the earlier `gfx_plot` loop that recalculated the feather on every frame.
- Below 100% opacity, outer darkness uses 4x4 patterned coverage. **This optional mode can be more expensive** on physical hardware. It is deliberately opt-in; default is 100%.
- If the cached BOB cannot be allocated, a CPU feather fallback remains so game loading is not blocked.

## Memory & speed

Typical radius 96 + feather 24 requires **58,081 bytes** of RAM for the cached BOB. The largest available settings, radius 240 + feather 96, require **452,929 bytes**, once per loaded world. It does not allocate or rebuild this ring every frame. One world is active at a time.

**Do not claim physical 50 FPS yet.** Test on real SIDBOX with music and scrolling. Choose opacity 100% when optimising maximum frame rate. If the feather seems offset by a few pixels, compare firmware's `gfx_drawbob` origin/transparent-pixel rules.

## Integration and compatibility

Install the source replacements, rebuild the Qt6 IDE, save Player Start, select Update Game Project, and rebuild the game. No edits to user-owned `main.c` are needed; its three `gameworlds_spotlight_*()` calls remain the same.

The generator internally stores opacity+1 so older C world records with a zero-initialised new field default to the original 100% opacity. The world-data JSON still stores a conventional 0-100 percentage.

The existing palette-ID reservation warning still applies. NPC/Trigger spotlight toggles are unchanged.

## Tests

- Native C cached BOB + X/Y mirrored offset + 100/50/0% opacity + world switching: PASS
- Native Stage 5.106/5.107/5.108 spotlight, Stage 5.48 transition regressions: PASS
- Stage 5.102 old source check retains its fixed Build 5.102 expectation and is not a Stage 5.110 failure. The Stage 5.102 native fade logic was not changed.
- Qt6 build and physical hardware test: **not run in this environment**.

# Stage 5.46.231026: Player Start world transitions

## How to use

Double-click **Player Starts → Default start** or any named Player Start in
**Game Resources**. In its Properties dialog configure:

- **Transition IN**: None (default), Fade In, Swipe Left/Right/Up/Down, Circle Open.
- **Transition OUT**: None (default), Fade Out, Swipe Left/Right/Up/Down, Circle Close.
- **Transition duration**: 1–150 frames at the generated starter's 50 FPS;
  30 frames = 0.6 seconds.

A **Goto World** object already chooses a destination world + named Player Start.
When the player reaches it, the world manager uses the active Player Start's
OUT setting, queues the safe world switch, and then uses the destination Player
Start's IN setting. This means a world's different entrances can have different
transition effects. Defaults are instant cuts so pre-existing designs behave
as before. Editing the Player Start does not add graphics resources or PPBs.

## Palette/graphics details

- Fades are performed on temporary 256-entry front/back CLUT copies using
  `gfx_usefpalette()` / `gfx_usebpalette()`. Source CLUTs, graphics and PPB
  colour indices never change. Index 0's transparency is preserved.
- Wipes and circle close/open use a fullscreen indexed-black mask AFTER the
  HUD/dialogue frame is drawn. For the duration of a **spatial** transition,
  foreground CLUT **entry 255** is temporarily overridden to opaque black;
  it is restored afterwards. Existing pixels using index 255 may momentarily
  appear black during a wipe. Reserve index 255 if you want perfect wipes.
- Circle masking uses integer arithmetic, no floating-point/sqrt library.
  It draws scanline rectangles: check actual SIDBOX frame pacing on hardware.
- Only the active world's assets stay resident. Camera, objects, inventory,
  and player ownership are managed by the existing world manager. Input/physics
  and world-object updates pause during the animation; music_update and the
  normal 50 FPS screen presentation continue.
- If a world has no selected front/back CLUT, the corresponding palette cannot
  be dimmed/masked automatically. Select the correct palette in Game Resources
  for reliable transitions. Worlds with background planes need a back CLUT too
  for a fully black fade.
- Existing palette cycling may affect the display during a transition;
  verify those combinations on SIDBOX hardware before shipping a game.

## Build/update steps

1. Update IDE source to Stage 5.46 and rebuild Qt6 CoderGirl.
2. Open EACH world design (`.sbgm`), adjust its Player Start properties,
   Save, and select **Update Game Project**. Refresh all worlds to add the
   namespaced palette accessor exports.
3. Build the game. The IDE-owned `main.c` includes transition integration
   automatically. If you edited `main.c`, it is **user-owned** and will not
   be overwritten. Open regenerated `maingame.c.txt` and copy the three
   transition integration locations into **your** `main.c`:
   - after startup player/buffer setup, `gameworlds_transitions_enable(1);`
   - gate per-frame gameplay updates with `if (!gameworlds_transition_busy())`
   - after all drawing and before `gfx_dispfbuffer`, call
     `gameworlds_transition_frame(VIEW_W, VIEW_H);`
4. Test going through a Goto World object in both directions (including a
   named destination entrance), then test inventory and graphics still render.

**Compatibility:** Without `gameworlds_transitions_enable(1)`, a previously
user-owned `main.c` keeps instant cuts. Crucially, it will never get stuck
waiting for a transition frame callback that doesn't exist. The project
registry tolerates older published world bundles with no palette accessors
until each world is regenerated; effects require current world bundles.

## Verification

`python development/tests/test_stage546_transitions.py` compiles the actual
world-manager C template with native GCC and exercises fade timing, both
palettes, a named entrance circle effect, a swipe, safe world switches and
shutdown. Previous Stage 5.41 cross-world and Stage 5.45 portable inventory
native regressions also pass. Complete Qt6 GUI build and physical STM32H743
transition rendering have **not** been tested in this environment.

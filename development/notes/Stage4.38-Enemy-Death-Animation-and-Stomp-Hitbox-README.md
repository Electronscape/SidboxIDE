# GamerGirl Stage 4.38 — Death Animation and Separate Stomp Hitbox

Based on the **Stage 4.37a** full IDE source. No changes to protected game `main.c`, Adventure, music, tilemap or existing collision types. Generated platformer code and new helpers must match.

## New Stompable Enemy properties

**Death animation (one-shot):**
- **Death starting atlas frame:** `-1` = no death image (enemy vanishes instantly); otherwise 0–255.
- **Number of death frames:** number of *consecutive* atlas frames to play, beginning at the start frame.
- **Delay per frame (50 FPS):** how many game ticks each frame is displayed. 3 ticks = 60 ms per frame.
- When the final stomp lands, enemy movement, animation and collision stop immediately. The death frames are shown in order **once**, then disappear. The collectable drop and linked action still fire on the final stomp.
- The generator validates that the entire death sequence fits in the sprite atlas and within the 256 frame index limit.

**Stomp / vulnerable hitbox:** independent of the ordinary body hitbox (which is still the damaging zone).
- **X offset:** vulnerable-box left edge relative to the body. Negative extends left.
- **Y offset:** vulnerable-box top relative to the body. Negative moves it above the head.
- **Width:** 0 = use the full body width. Set a larger width for a forgiving landing area.
- **Height:** vertical tolerance for descending feet within the vulnerable zone, in pixels.
- Valid stomps require landing *from above* with downward relative motion. Ordinary side/underside contact with the **body** still damages the player, and successful stomps suppress same-impact damage.
- Example for a **16 × 16 px** enemy body: X=-4, Y=-6, width=24, height=6. Tune per enemy until it feels fair.

### Quick example

A sprite atlas has frames 0–15. Set starting death frame=8, number of death frames=4 and delay per frame=3. The enemy displays frames **8, 9, 10, 11**, each for 3/50 of a second; then vanishes after 12 game ticks.

## Install (back up first)

1. Extract **GamerGirl-Stage4.38-IDE-Changes.zip** over your **Stage 4.37a IDE SOURCE ROOT**, preserving the paths within the ZIP.
2. Rebuild GamerGirl with your usual Fedora Qt6 build script.
3. For an **existing game project**, extract **GamerGirl-Stage4.38-Game-Helper-Update.zip** over your **platformer PROJECT ROOT**, replacing **both** `gamehelpers/gameworldobjects.c` and `gamehelpers/gameworldobjects.h`. Do not install one without the other: `game_world_object_t` has new fields.
4. Open Game Designer > Game Object Properties > Stompable Enemy. Configure death frames, delay and stomp box. Save Design, then **Update Game Project**, then build your game.
5. For a brand new project, the IDE includes updated helper templates. There should be no need to hand-edit C.

**Compatibility:** old `.sbgm` designs load with one death frame and their original display duration, plus an unchanged top stomp hitbox by default. Updated `.sbgm` files persist the additional properties. Runtime behavior for Breakables, Murder Objects, patrol and splines is preserved.

## Test checklist on SIDBOX

- Two successful stomps count as two hits (not multiple per landing).
- A landing just outside the enemy body, inside a widened stomp box, counts as a stomp.
- Walking into the enemy's main body from the side still hurts and kicks the player away.
- The death animation plays once, at the chosen delay, then disappears; no contact damage during it.
- Drop on defeat and linked-object action still fire once on the final hit.
- An older single-frame enemy still displays its defeated pose as before.
- Roving enemies still move smoothly over slopes and reverse at walls.

## Checks completed

Native C tests passed: Stage 4.36 stomp, Stage 4.37 tile patrol, Stage 4.37a moving-enemy knockback, new Stage 4.38 dual-hitbox and frame stepping, plus Stage 3.89, 3.90, 3.91, 3.92 and 3.96 Breakable/Hazard regressions. Source-level generator/persistence checks passed.

**This environment does not have Qt6 development libraries or SIDBOX hardware**; Fedora Qt compilation and real hardware behaviour remain to be tested by you.

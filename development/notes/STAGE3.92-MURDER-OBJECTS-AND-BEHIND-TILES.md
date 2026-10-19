# Stage 3.92 — Hazard / Murder Objects and behind-tile drawing

Built on **the exact complete Stage 3.91 source** (`IDE-GamerGirl-Stage3.91-Breakable-Audio-Events.tar.gz`).

## New placed-object settings

In **Game Designer → Game Resources → Sprite → Configure Game Object**:

- Behaviour: **Hazard / Murder Object (touch hurts)**. These are NON-SOLID sensors, unlike breakable platforms. Configure **Collision width/height** independently of the artwork. They follow an attached **Movement spline** and optional sprite-frame animation just like existing world objects.
- **Damage (0–65535)** on contact: damage is reported to YOUR game's health system. The generated starter has `player_health = 3`, a commented decrement, and a TODO to implement death/respawn. Damage does **not** silently kill the player.
- **Knock player back**: enable/disable, signed **X (-40..40)** (left/right), **Y (-40..40)** (up negative, down positive); default (0,-11) is upward. Vertical kick *sets* vertical velocity; horizontal kick *adds* to the existing force velocity with the usual ±32 px/frame clamp. Leave disabled to make a hazard that hurts without moving the player.
- **Use player Hurt animation**: when checked, the generated `maingame.c.txt` selects `PLAYER_ANIM_STATE_HURT` for the injury window if that state is present. The player animation editor can define that state. A missing state leaves normal animations working.
- **Flash using solid-colour BOB**: uses existing `BLIT_FLAG_SOLIDCOLOUR` and `flagval[BLIT_FLAG_TYPE_TINT_VALUE]` from the SIDBOX graphics API (no firmware change). Choose **foreground palette index** via an indexed swatch list (active `.pal`, or the object's PPB palette). Index 0 is generally transparent; prefer an opaque entry. The game draws a temporary BOB copy, so ordinary sprite flags are preserved.
- **Number of flashes (1..32)** and **frames between flashes (1..255)**: `N` flashes are N ON periods, each followed by an equal OFF period, at 50Hz. Default 4 flashes × 3 frames ON/3 OFF = 24 frames (480ms). When flashing is disabled, the 20-frame safety grace period still prevents rapid repeated damage.
- Sound (optional): **Hazard — hit**, **Hazard — knockback**, and **Hazard — ambient (loopable)**. Sounds use the existing sound-resource IDs, channels, stereo placement, radius and fades. Enable **Loop** on the selected ambient Sound resource. Distinct channels are needed for simultaneous effects.
- **Draw behind tilemap** is available for each placed sprite, including decorations and collectables. The tilemap is rendered between the `gameworlditems_draw_behind()` and existing `gameworlditems_draw()` passes. Ordinary and front-priority tilemap tiles still obey their established ordering. The world canvas uses Z=1.9 (below the tile overlay's Z=2) for behind-tile objects.

## Collision and sound rules

- Swept relative AABB detects contact when **either the player or a spline-driven hazard moves** across the other between frames.
- Non-solid: the collision itself does **not** teleport or ground the player. A knockback (if enabled) changes velocities, cancels grounded/coyote status, and launches the player.
- On a successful impact, one `hurt_triggered` pulse and `hurt_damage_this_frame` are set in `game_world_player_t`. One-frame `hazard_hit_triggered`/`hazard_bounce_triggered` flags drive SFX. `game_world_objects_before()` clears the player event at each frame, and `game_world_objects_update()` clears object sound events.
- A grace window blocks rapid repeat injury on overlapping objects; a touched hazard needs to separate before another hit from that same instance. If multiple hazards overlap, the shared player grace time also prevents repeated injury in the same interval.
- Per-object disabled/active state and optional spline motion are respected. Existing player physics, breakables, loops and springs aren't rewritten.

## Build and integration

1. Replace changed production files preserving their directories, rebuild the IDE in **Qt Creator**.
2. Save your `.sbgm` and use **F5 → Update and Compile**. That refreshes `gamehelpers/worldobjects.[ch]`, `gamehelpers/collectables.[ch]`, generated `gameworlditems.[ch]` and `maingame.c.txt`.
3. If you've already taken ownership of `main.c`, it is **NOT overwritten**. Inspect `maingame.c.txt` and copy the new Hurt animation selection, damage handling, flash rendering, and **draw-behind before the tilemap** calls into your `main.c`. Retain the existing `gameworlditems_before/after` call order.
4. Assign actual Sound resources and their intended channels; each channel can play one sample at once.
5. Test on real SIDBOX. No Qt6 SDK, firmware, or J-Link was available in this execution environment, so this patch has not been Qt6-compiled or hardware-tested here.

**Tween caveat:** World objects already support attached **splines** in Game Designer. There isn't a separately configured per-object tween attachment in this dialog. Handwritten tween code can reposition the object via `game_world_object_set_position()`; if adding a full visual tween attachment is desired, that's a separate editor feature.

## Tests run

Native C: `test_stage392_hazard_damage.c`, `test_stage391_breakable_sound_events.c`, `test_stage390_breakable_jump_intent.c`, `test_stage389_breakable_objects.c`, `test_stage368_worldobjects.c`.

Python source integration: `test_stage392_hazard_integration.py`, earlier Stage 3.89/3.90/3.91 integration, Stage 3.81 platform animation, Stage 3.80 loop export, Stage 3.79 build reminder. Source tests do **not** replace a Qt6 GUI build or SIDBOX test.

# GamerGirl Stage 4.36 — Stompable Enemies (first hardware-test release)

## What it adds

Game Designer → select a placed PPB Sprite → Game Object Properties → **Stompable Enemy**.

- **Stomps to defeat (1–20)**: every separate landing from above while descending removes one enemy hit.
- **Bounce after every stomp**: optional independent vertical impulse plus signed horizontal impulse. No variable-height-jump boost is involved.
- **Hurt from sides / underside**: optional damage through the existing `game_world_player_t.hurt_triggered` / `hurt_damage_this_frame` mechanism. Existing invulnerability grace prevents repeated damage from one touch.
- **Defeated atlas frame**: optional static frame displayed for a configurable number of 50 FPS ticks before the sprite disappears. Set to **None** for immediate removal.
- **Linked Object**: choose a target and Enable, Disable or Toggle it **once**, on the final stomp (door, bridge, etc.).
- **Drop collectable on defeat**: select an existing Collectable sprite configured *Hidden until activated*. It spawns at the defeated enemy and follows existing prize drop physics. Requires a tilemap and an unsplined collectable, just as Breakable rewards do.
- **Existing Animation Frames, Spline movement, and three Breakable hit/bounce/finish sound slots** can be reused for enemy visuals, movement and audio.

## Setup (first test)

1. **Make a backup** of your IDE and game project first.
2. Replace the files from `GamerGirl-Stage4.36-IDE-Changes.zip` in the IDE source tree and rebuild GamerGirl.
3. **Important:** existing game helper files are *protected* and are **not overwritten by Update Game Project**. Extract `GamerGirl-Stage4.36-Game-Helper-Update.zip` into the existing game project's root to update `gamehelpers/gameworldobjects.c` and `.h`. This is essential: the new object type is `GAME_OBJECT_ENEMY` and older runtimes reject it.
4. In World Designer, place a PPB sprite at 100% scale, open Game Object Properties, choose **Stompable Enemy** and set its 1–20 hits, bounce and damage. Start with **1 hit**, **bounce ON**, **side damage OFF**, and **defeated frame None** to test safely.
5. Save the design, **Update Game Project**, compile, and run on SIDBOX. Generated `gameworlditems.c` configures the new type, automatically handles hit counts, drawing, damage notifications, optional reward and one-time linked object action.
6. Once top stomps work, switch on side damage and test again. An existing hand-edited `main.c` must already check `world_player.hurt_triggered` and reduce player health if you want that to affect health/lives. Generated starter games include this handling when damaging objects exist; the IDE continues to protect user-owned `main.c`.

## Technical notes

- Purely additive runtime object type **9**; existing Spring (3), Breakable (7), Hazard (8) behaviour remains unchanged.
- Defeated enemies become non-colliding immediately. With the defeat frame option, their sprite remains visible until its display timer expires.
- Multiple hits require the player to separate from the enemy between landings. Horizontal hitbox overlap and swept crossing are checked using the existing platformer player physics.
- Enemies on splines move and animate with existing helpers; **this is not an autonomous AI patrol system**. A looping spline can act as a patrol path.
- Damage uses the same grace timer as Murder Objects. Player health/lives remain owned by the game, not this helper.
- This first version does **not** include a multi-frame defeat animation timeline: the defeated look is one chosen atlas frame displayed for N frames.
- Basic Platformer source and existing firmware are unchanged.

## Validation

- Compiled and ran native Stage 4.36 enemy test: multi-hit stomp, bounce, grace-latched side damage, optional disable of side damage, defeated frame timer.
- Compiled and ran original Stage 3.89, 3.90, 3.91 and 3.92 breakable/hazard tests.
- Stage 4.27 SPC auto-start and Stage 4.34 adventure quest-memory tests passed.
- Qt6 SDK is not installed in this environment: Fedora IDE compilation and physical SIDBOX hardware remain to be tested.

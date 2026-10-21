# GamerGirl Stage 4.37 — Enemy Hurt Settings and Tilemap Patrol

This update builds on Stage 4.36, which has already passed a real SIDBOX test for single-hit stomps and hurt animations.

## Install BOTH ZIPs

1. Back up the IDE and game project.
2. Extract `GamerGirl-Stage4.37-IDE-Changes.zip` over the Stage 4.36 IDE SOURCE ROOT, rebuild GamerGirl.
3. Extract `GamerGirl-Stage4.37-Game-Helper-Update.zip` over the actual PLATFORMER PROJECT ROOT, replacing `gamehelpers/gameworldobjects.c` and `.h`. These two files are essential: the runtime object's structure has expanded. Do not compile new generated `gameworlditems.c` with old helper files.
4. Open World Designer, edit your enemy's Game Object Properties, Save Design, **Update Game Project**, and recompile the platformer. Your protected `main.c` is unchanged.

## Configuring an enemy

Select the enemy PPB sprite -> **Game Object Properties -> Stompable Enemy**.

- **Hits before enemy dies (1–20)**: one accepted downward stomp per separated contact. A three-hit enemy needs three landings. Defaults to 1 from existing projects.
- **Bounce player after every stomp**: same safe fixed impulse as Stage 4.36, independent of holding Jump.
- **Item dropped when defeated**: choose a **placed Collectable**, configured as **Hidden until activated**. The generator spawns it on the enemy's final defeat and uses the existing reward-gravity logic. One unique drop resource per breakable/enemy is still required.
- **Linked Object**: enable/disable/toggle a door/switch only on the **last hit**.
- **Hurt player on side / underside contact**: checkbox in Stompable Enemy. The **Damage / Knockback / Hurt Effects** card appears immediately below the enemy card. These are the same familiar settings as Murder Object: amount per contact; enable knockback, X magnitude and signed Y; hurt animation; solid-colour flashing; foreground palette colour; number of flashes and on/off frames.
- **Enemy horizontal knockback** automatically pushes AWAY from the enemy regardless of which side the player touched. Enter a magnitude such as 8 for X and a negative Y such as -7 for an upward kick. For an existing Stage 4.36 enemy with X=0, set X manually to 8; new enemies converted from decorations get an 8 default. Murder Objects preserve their old absolute signed kick direction.

### Enemy movement

The same enemy card contains **Walk on tilemap (patrol and turn at walls)**. The option is OFF in existing projects.

- If OFF, existing spline motion remains available (or stationary if no spline).
- If ON, the enemy ignores its spline and uses collision-map roaming. Select walking speed **1–8 whole pixels per 50 FPS frame**, maximum slope-step height **1–12 pixels**, and optionally **Start walking left**.
- It climbs/recedes over gentle slopes via the existing `game_tilemap_actor_blocked()` tile and slope logic, reverses on impassable walls or unsupported ledges, and updates the sprite's X flip to face its direction. It preserves the sprite's original Flip-X as the baseline.
- **Place the enemy with its feet directly on solid terrain.** This is a light ground-patrol helper, not a general gravity/AI engine. It doesn't chase the player, jump gaps, ride moving platforms, or support one-way surfaces not recognised as solid by the shared actor collision query. Splines are still recommended for flying enemies.

## Safety / compatibility

- Basic Platformer, music, NPC/adventure code, springs, and ordinary Murder Objects are untouched.
- `worldobjects.h` and `.c` (in the IDE helper template) and `gameworldobjects.h` and `.c` (in the generated game) must MATCH this version. Old generated game assets need regeneration.
- Existing enemy hits, drops and defeats continue to work; enemy roaming is opt-in.
- No firmware changes.
- Tests run here: C native Stage 4.36 Stomp enemy test, new Stage 4.37 tile-roam and two-way knockback test, Stage 3.89–3.92 breakable/hazard C tests, and Stage 4.37 source persistence/generator consistency. **Qt6 is not installed here; Fedora IDE compilation and SIDBOX hardware verification remain to be done.**

## Suggested first hardware test

1. Place a small ground enemy on **flat** terrain. Set 3 hits, Bounce ON. Enable side hurt, 2 damage, Knockback ON, X=8, Y=-7, flash ON. Set tile walking speed 1 and slope step 4.
2. Approach from either side and confirm a horizontal push away + upward motion + flash/hurt animation.
3. Stomp three *separate* times; confirm the enemy only dies on the third.
4. Assign a hidden Collectable as the defeat reward and confirm it appears at the final hit.
5. Move the enemy onto a gentle slope, wall, and ledge and check it follows/reverses without passing through tiles.

Compiled C passing does not guarantee identical results on the STM32; test on your backed-up level first.

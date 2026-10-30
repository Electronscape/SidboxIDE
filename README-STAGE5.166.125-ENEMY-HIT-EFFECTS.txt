CoderGirl IDE / SIDBOX Game Designer
Stage 5.166.125.301026 (30 October 2026)
OPTIONAL ENEMY HIT EFFECTS: flashing + frame reaction

BASED ON: Stage 5.166.124.1 source, hardware-accepted player melee foundation.

Where to find it:
  Game Designer -> Game Objects -> edit a Stompable Enemy
  -> Damage / Knockback / Hurt Effects

The existing PLAYER HIT EFFECTS group retains exactly its previous player-damage
controls: knockback, Hurt animation selection and solid-colour flash. The new
ENEMY HIT EFFECTS group is completely independent and only enabled for enemies.

New optional enemy settings:
  - Flash enemy using solid-colour BOB (OFF by default)
  - Enemy flash CLUT colour (foreground palette index, default 15)
  - Enemy number of flashes (default 2)
  - Enemy frames between flashes (default 3)
  - Hit animation starting atlas frame (None / -1 by default)
  - Number of consecutive hit animation frames (default 1)
  - Hit animation delay per frame, 50 Hz ticks (default 3)
  - Visual frame selector using the same atlas dialog as the defeat animation

The effect starts only after an ACCEPTED NONLETHAL enemy hit, including player
melee, head stomp and underside attack. Each subsequent accepted hit restarts
it. The final hit does not play the hit reaction; it immediately follows the
existing ON DEFEAT / death animation / loot / quest path, unchanged.

Effects are draw-only; enemy movement, normal sprite animation and sprite state
are NOT overwritten. A flash can overlay a hit animation at the same time.
Transient feedback is dropped on world save restore (no save-format change).

NOTE: Tile stamps support solid-colour enemy flashing, but not hit-frame atlas
animation. Export validation will give an explicit explanation for that case.
Hit animations must fit the chosen sprite's frame atlas (max index 255).

TO TEST on SIDBOX:
  1. Backup the project, build this IDE, and open an existing Stompable Enemy.
  2. Enable Enemy Flash (choose a bright CLUT index); optionally select a
     2-3-frame hit animation from that enemy's PPB atlas.
  3. Use an enemy with 4 required hits. Generate the game, rebuild .app.
  4. Attack with FIRE1. On hits 1-3, see flash/pose; on hit 4, the existing
     death animation, drop, and ON DEFEAT events remain authoritative.
  5. Try stomping too, plus player-hurt effects on enemy body contact.

NO CHANGES NEEDED TO YOUR OWN main.c beyond the already required Stage124
combat button setup. YOUR GAME PROJECT IS NOT MODIFIED BY THE SOURCE ARCHIVE.

FILES CHANGED:
  gamedesigner.h             - optional enemy hit feedback resource fields
  gamedesigner_project.cpp   - persist/read enemy-hit configuration
  gamedesigner.cpp           - separate Player/Enemy groups + controls/pickers
  gamedesigner_export.cpp    - validation and runtime export values
  idelibs/codehelpers/game/worldobjects.ruleh / .rulec - runtime effects
  idelibs/codehelpers/game/gameworlditems.rulec       - generated setup/render
  splashscreenwidget.cpp     - Build: 5.166.125.301026
  development/tests/test_stage5166_125_enemy_hit.py + native C test
  Historic version-only tests for Stages 120/121/124 allow later versions.

VALIDATION:
  PASS: gcc -std=c11 -Wall -Wextra -Werror native hit/flash/pose/defeat test
  PASS: Stage124 native 4-hit melee defeat test
  PASS: Stage125 + Stage120/121/122/124 focused tests (16 passing)
  PASS: source scan of .cpp/.h for invalid auto* lambda declarations (none)
  BLOCKER: full CMake Qt IDE build cannot be run here; Qt6 >= 6.5 SDK is not
           installed in the build container. CMake failure is missing Qt6,
           not an observed source compiler error. Desktop build and STM32
           gameplay verification remain outstanding.

SCOPE: Hit feedback only. Enemy physics knockback, player sword/attack animation,
projectiles, and new Visual Nodes ON ATTACK are not part of Stage125.

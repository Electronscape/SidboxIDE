CODERGIRL IDE Stage 5.166.124.1.301026
HOTFIX: compile correction only: `auto *updateCombatControls` -> `auto updateCombatControls` in gamedesigner.cpp:1438.
No player combat or generated runtime changes.

OPTIONAL PLAYER PROFILE MELEE COMBAT -- SOURCE TEST CANDIDATE
30 October 2026

Built on Stage 5.166.123 Flow Debugger Virtual Actions. All game test data and
user-owned main.c files are unchanged.

WHAT IS IMPLEMENTED
- Create / Edit Player -> Movement & Physics -> select any physics profile.
- Optional checkbox: Enable melee combat for this profile (OFF by default).
- Damage per enemy in existing stomp-hit units (1..20); reach 1..128 pixels;
  cooldown 1..250 gameplay frames (50-Hz nominal; no real-time timers).
- FIRE1 attacks ON NEW PRESS; UP jumps in combat-enabled profiles.
- The attack is a single instant, horizontal hitbox projected from the live
  player hitbox, facing left/right based on directional input. No new sprites.
- All intersected active Stompable Enemies take damage once per accepted press.
  Their existing hit counter, death animation, drops, save/load, and
  ON DEFEAT actions are reused; dead enemies cannot be struck again.
- Switching physics profiles with gameplayer_apply_physics() changes combat
  mode/settings immediately. Held FIRE1 on entering battle mode is ignored
  until released once, preventing attack on load/switch.
- The existing gameworlds_after() call initiates attack and sends damage before
  the game's existing object-event dispatcher: no additional attack calls
  required in the generated main loop. Worlds without enemies have null
  attack callbacks. Persistent saves are unchanged; attack cooldown is transient.
- Read-only runtime observation APIs:
  gameplayer_combat_enabled(), gameplayer_attack_started(),
  gameplayer_attack_hits(), gameplayer_attack_total(),
  gameplayer_attack_hit_total().

USER-OWNED main.c -- CRITICAL OPTIONAL INPUT INTEGRATION
If your project owns main.c, it is intentionally NOT overwritten.
Without the following change FIRE1 may still jump while also attacking, and
UP may remain masked by the old Adventure input path.

FILE: <your game project>/main.c
LOCATION: gameplay frame update, in the existing `game_tile_player_run(...)`
line(s), BEFORE the existing `gameworlds_after(&world_player);`.

If you currently have:
    game_tile_player_run(&player_physics,
        game_adventure_gameplay_buttons(player_buttons & (uint8_t)~BTN_UP), 1);
REPLACE THAT STATEMENT WITH:
    game_tile_player_run(&player_physics,
        gameplayer_movement_buttons(game_adventure_gameplay_buttons(
            player_buttons & (gameplayer_combat_enabled() ? 0xFFu : (uint8_t)~BTN_UP))), 1);

If your main.c instead passes raw `player_buttons` without Adventure:
    game_tile_player_run(&player_physics,
        gameplayer_movement_buttons(player_buttons), 1);

Keep FIRE2 interaction / inventory priority unchanged. In complex custom
movement loops with branches for space/water, apply the same button mapping to
the movement/jump branch or explicitly retain your own jump policy.

NEW GENERATED maingame.c.txt INCLUDES THIS MAPPING AUTOMATICALLY.

DO NOT EXPECT YET
- This is the MELEE FOUNDATION, not the entire requested combat roadmap.
- No projectile/bullet/fireball sprites, ranged enemy AI, attack animations,
  melee hitbox overlay, knockback, or per-weapon inventory switching.
- Visual Nodes ON ATTACK / ON HIT cards and actions are NOT yet implemented.
  The runtime counters are the groundwork for those next.
- Existing world assets and PPB files remain untouched.

FILES MODIFIED
- gameplayerprofile.h
- gamedesigner.cpp
- gameworldsnapshot.h
- idelibs/codehelpers/game/gameplayer.rulec + gameplayer.ruleh
- idelibs/codehelpers/game/worldobjects.rulec + worldobjects.ruleh
- idelibs/codehelpers/game/gameworlditems.rulec + gameworlditems.ruleh
- idelibs/codehelpers/game/gameworlds.rulec
- idelibs/codehelpers/game/maingame.rulec
- splashscreenwidget.cpp
- development/tests/test_stage536_shared_player.py (updated mock to new profile shape)
- development/tests/test_stage5166_124_player_combat_sources.py
- development/_stage124_native/* (host native C regression harness)

TEST STATUS
- PASS: native player profile test (combat mode, FIRE1 edge, direction,
  cooldown, no repeat while held, runtime counters, disabled default).
- PASS: native world enemy melee test (hit rectangles, hit counters, multiple
  required hits, final defeat flag/death animation, dead enemy immunity).
- PASS: Stage 5.166.121 ordered/unordered objective and save/load native tests.
- PASS: Stage 5.166.122 journal renderer/input native tests.
- PASS: Stage 5.3 shared player native smoke test (updated field shape).
- PASS: Stage 5.166.124 source contract checks.
- Historical fixed splash-version assertions in tests for Stages 120/123 are
  stale and fail their *version assertion* by design; not engine regressions.
- Full Qt build, end-to-end generated-world build, and STM32 hardware test
  NOT performed here. BACK UP your IDE and game project before upgrading.

TYPICAL TEST
1. Duplicate existing Normal physics profile, rename it Battle, and enable
   optional melee combat. Damage=1, reach=32, cooldown=12 frames is a start.
2. Assign Battle as starting physics for a TEST world or call
   gameplayer_apply_physics(&player_physics, battleProfileId) in owned C.
3. Regenerate all world sources and the shared Player profile; compile .app.
4. Walk beside an enemy, press FIRE1 (release between swings), verify attack
   only while facing that enemy. Stomp should still work and count hits.
5. Check that final melee hit triggers the existing ON DEFEAT / loot path.
6. Disable combat and verify legacy FIRE1 jump + FIRE2 interactions.

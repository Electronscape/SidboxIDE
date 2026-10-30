NOTE: Stage 5.166.127.2 supersedes the main.c integration/reset advice below.
Keep the original player_anim_step() call and do not reference melee_ticks_left from main.c.

NOTE: SUPERSEDED BY README-STAGE5.166.127.1-PLAYER-ANIM-API-CORRECTION.txt
The main.c replacement in this older document is no longer required.

SIDBOX / CoderGirl Stage 5.166.127 - Player Toolkit Melee Animation
Date 30 October 2026
Status: source candidate (desktop Qt6 compile and SIDBOX hardware pending)

WHAT CHANGED
The Player Animation Toolkit exports HAS_MELEE_STATE (case-insensitive state name
'Melee') and player_anim_step_combat(). This animation-only override runs once
per accepted FIRE1 attack and uses the clip's own per-frame timing. Repeated
attacks restart at first frame. Hurt animation has priority. A profile without
combat enabled remains on Idle/Walk/Jump/Fall as before. No event, damage, or
enemy-handling changes. No need to alter player.sbpi; the profile already has
optional combat enabled from Stage124.

HOW TO TEST (hand-owned main.c)
1. In Player Animation Toolkit save the Melee clip, then click YES to update
   gameanimations/player_anim.h. The header MUST contain:
      #define PLAYER_ANIM_HAS_MELEE_STATE 1
2. Rebuild the IDE and export game sources; DO NOT overwrite hand-owned main.c.
3. In your GAME PROJECT, main.c, main() gameplay loop, locate the animation
   step AFTER gameworlds_after(&world_player). Replace ONLY the existing call:

      player_anim_step(&player_anim, active_player_sprite,
          player_anim_state, player_anim_facing, 1);

   with this complete replacement:

      player_anim_step_combat(&player_anim, active_player_sprite,
          player_anim_state, player_anim_facing, 1u,
          gameplayer_combat_enabled(), gameplayer_attack_started(),
          world_player.hurt_anim_active && world_player.hurt_ticks_remaining);

   If your main.c uses &GAMERGIRL_PLAYER_BOB rather than active_player_sprite,
   preserve that second argument when replacing the call.
4. Regenerate your game project as usual; rebuild the .app. Test FIRE1 against
   an enemy and away from enemies. The clip should play once per swing and
   return to the appropriate movement animation.

IMPORTANT
- Only the GAMEPLAY animation step uses step_combat; leave initial Idle setup
  calls to player_anim_step unchanged.
- Older player_anim.h files will not contain this function. Save and update
  the player animation header with the new IDE BEFORE editing hand-owned main.c.
- The generated starter clears the attack animation on world transitions.
  A user-owned main.c may also clear player_anim.melee_ticks_left = 0u
  next to player_anim.started = 0u on world reload.
- Animation duration and attack cooldown are deliberately separate. The hit
  still happens when the attack starts (Stage124), not on a later PPB frame.
- Missing Melee state or missing directional frames falls back to regular
  movement, without errors. A mirrored Left clip uses existing Toolkit mirror.
- The generated maingame.c.txt automatically uses the new helper if present
  in the updated header; it preserves compatibility with legacy headers.
- Source release, not hardware verified. No Qt6 SDK in build container.

CHANGED FILES
- gameanimationeditor.cpp: export named Melee availability macro
- idelibs/codehelpers/game/playeranim.ruleh: clip-duration melee overlay
- idelibs/codehelpers/game/maingame.rulec: generated starter wiring
- splashscreenwidget.cpp: version 5.166.127.301026
- development/tests/test_stage5166_127_player_melee_animation.py
- Stage126 test version assertion generalized for subsequent stages
- README.md and this release guide

SIDBOX IDE 5.166.127.1 - Player melee animation API correction (30 October 2026)

This corrects Stage127's unnecessary public player_anim_step_combat API.

YOUR GAME main.c: KEEP your original animation call exactly:
    player_anim_step(&player_anim, active_player_sprite,
                     player_anim_state, player_anim_facing, 1);

No extra C function or main.c edit is needed for animation. The exported
`gameanimations/player_anim.h` now selects MELEE automatically from the active
shared Player Profile's gameplayer_attack_started / combat_enabled signals.
It handles full clip timing, Hurt interruption, no-loop completion and
returns to Idle/Walk/Jump/Fall normally. Standalone animations without a
shared player keep the same old step behaviour.

To use it: Rebuild this IDE, open Player Animation Toolkit, save your existing
Melee animation and choose YES to regenerate the game's
`gameanimations/player_anim.h`. Regenerate normal project sources if needed.

The existing `main.c` already includes `gamehelpers/gameplayer.h` before
`gameanimations/player_anim.h` in the user's test project. This matters
because the header's auto-melee code is conditional on
CODERGIRL_SHARED_PLAYER_H (set by the gameplayer.h include).

If you had switched to player_anim_step_combat(...) while testing Stage127,
restore the ORIGINAL player_anim_step(...) call: the extra function is gone.

The UI Player Profile combat enable/cooldown and melee damage engine are
unchanged. This is solely exported animation selection + starter cleanup.
The user project files were NOT modified.

Checks: native gcc Werror compile/harness (shared and standalone)
         source-level regression tests
         Qt6 compile not available on this container, desktop test needed.

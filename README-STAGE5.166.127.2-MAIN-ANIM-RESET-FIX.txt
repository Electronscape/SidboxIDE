SIDBOX IDE 5.166.127.2 - Player animation main.c compatibility correction (30 October 2026)

IMPORTANT: Keep user-owned game main.c independent of the animation toolkit's
internal playback structure. The 127 and 127.1 generated maingame.c.txt
incorrectly offered two direct accesses to player_anim.melee_ticks_left;
old exported player_anim.h structs do not have that member. Those generated
lines have been REMOVED. No gameplay logic or exported header API change.

EXISTING GAME FIX:
  In /home/kbox/AcoderGameTests/Platformer3/main.c (main function), DELETE
  the two lines of this form, at approx. lines 202 and 241:
    player_anim.melee_ticks_left=0u; /* No attack carries across worlds/saves. */
  Keep the existing player_anim.started=0u and the ordinary call:
    player_anim_step(&player_anim,active_player_sprite,
                     player_anim_state,player_anim_facing,1);
  Do not put any melee-specific structure/member access in main.c.

For the automatic melee animation, export the Player Animation Toolkit's
animations again with this IDE and choose YES to update
  gameanimations/player_anim.h
This is separate from the main.c compile fix: older headers can compile once
the invalid lines are removed, but won't have automatic melee support.

In the updated player_anim_step() function, a->started==0 or a zero-frame
step clears the old melee transient state on world activation/load.
No additional main.c reset is necessary. Old projects remain compatible.

Tests: native unchanged five-argument player_anim_step() timing, combat opt-in,
Hurt interruption, world reset and standalone no-combat header, plus source
assertion that generated maingame.rulec never accesses melee_ticks_left.
Qt6 full build and SIDBOX hardware not executable in this container.

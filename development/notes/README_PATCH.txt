SIDBOX IDE 5.139.3.021126 - Automatic Downstairs animation
BASE: Apply over IDE 5.139.2.021126 (correct millisecond runtime).

ONLY CHANGED IDE SOURCE FILES:
- gameanimationeditor.cpp
- idelibs/codehelpers/game/playeranim.ruleh
- idelibs/codehelpers/game/maingame.rulec
- splashscreenwidget.cpp (version only)

WHAT IT DOES:
- Exports HAS_DOWNSTAIRS_STATE=1 when a state named "Downstairs" exists,
  case-insensitive, and uses its actual exported enum number (no fixed 12).
- If the player walks DOWN a >30-degree slope, uses DOWNSTAIRS when frames exist.
- Retains Up/Down four-frame debounce on pixel-stepped slopes.
- Walk remains the fallback for missing Downstairs clips, flat/slight slopes.
- Animation is never selected during airborne motion or standing still.
- No physics/collision/world/map changes.
- The 5.139.2 millisecond playback implementation is UNCHANGED.

FOR IDE-OWNED GAME main.c:
1. Install these source files and rebuild IDE.
2. Open Player Animation Editor, save the .sbanim and re-export
   gameanimations/player_anim.h. This supplies DOWNSTAIRS enum and macro.
3. Update Game Project; verify maingame.c.txt has Downstairs selection.
4. If main.c is IDE-owned, follow the normal IDE regeneration workflow.

FOR USER-OWNED GAME main.c:
- Update Game Project does NOT replace your main.c. Use the separate
  USER-OWNED-GAME-main-c patch provided alongside this IDE patch.
- Regenerating player_anim.h is necessary before compiling that game's patch.

CHECKS:
- Host GCC C99 tests passed for generated rule selector combinations with
  both states, Downstairs-only, Upstairs-only and no added states.
- Tests passed with state IDs 11/12 and reordered 7/3.
- Timing runtime rule diff against 5.139.2 contains only new Downstairs macro.
- Qt6 full rebuild could not be verified in this environment; test on Fedora.

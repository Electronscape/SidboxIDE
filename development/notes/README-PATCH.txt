SIDBOX CoderGirl IDE 5.134.3.311026 — TIMER action operation UX correction
Apply on top of 5.134.2.311026 (which includes the 5.134.1 compiler hotfix).

UPDATED SOURCE FILES ONLY:
  gamevisualnodes.cpp
  splashscreenwidget.cpp

What changed:
- When new TIMER TRUE/FINISHED wire targets a Game Object it defaults to DISABLE.
- When new TIMER FALSE/RUNNING wire targets a Game Object it defaults to ENABLE.
- Ordinary BOOLEAN/AND/OR/etc. existing TRUE=ENABLE, FALSE=DISABLE defaults unchanged.
- Existing saved wires keep their explicitly authored .sbgm action (no auto-migration).
- Right-click a graph action wire: ENABLE/DISABLE/TOGGLE shows the current selection checked.
- Action wires are now coloured by operation, consistent with existing state-action wires:
  green ENABLE, red DISABLE, yellow TOGGLE.
- Wire hover tooltips, inspector, and status text show saved action.
- All changes still save to .sbgm logicNodes trueActions/falseActions; no .vsgm gameplay data.
- No changes to exporter, runtime, save schema or user main.c.

TEST SETUP:
  Set HUGEHealth initially disabled.
  UnlockHealth ON ACTIVATE -> TIMER START.
  TIMER FALSE/RUNNING -> HUGEHealth ENABLE (wire green).
  TIMER TRUE/FINISHED -> HUGEHealth DISABLE (wire red).
  Save Graph + World, close/reopen graph, confirm both operations persisted.
  Regenerate game, rebuild .app and check 5-second visibility window.
  Remove any unrelated direct trigger-to-collectable ENABLE action if it causes a conflicting result.
  Note: any old TIMER TRUE->target link defaulted to ENABLE will remain ENABLE until right-click Set DISABLE.

VERIFICATION: targeted source contract PASS, existing native GCC timer action tests PASS (-Wall -Wextra -Werror), ZIP CRC verified.
FULL Qt6 DESKTOP BUILD AND STM32 HARDWARE NOT TESTED in this container (no Qt6 SDK).

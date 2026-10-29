SIDBOX CoderGirl IDE Stage 5.166.62.281026
========================================

Fix: independent logic does not re-evaluate when a different Trigger changes
one of its source Game Objects. This was exposed by two independent Trigger
switches toggling two managed Decoration objects feeding an AND node.

Generation now runs all normal Trigger actions first, captures all independent
logic-node values, then runs TRUE/FALSE branch actions. A Trigger-owned graph
also listens to other local Triggers that enable/disable/toggle any Game Object
used as a direct state input in that graph. Each graph is evaluated only once
per activation batch. Existing owning Trigger activation is still supported.

Game Object Properties -> Trigger / Logic Connections now shows independent
logic when the inspected object is an action target, as well as a state input.
This is editable against the same Trigger-owned .sbgm logic records.

Files modified:
  gamedesigner_export.cpp
  gamedesigner.cpp
  idelibs/codehelpers/game/gameworlditems.rulec
  splashscreenwidget.cpp

No .map, .sbgm, .vsgm or saved-game format changes. No changes to the
user-owned main.c, title flow or reset code.

Install: apply hotfix over 5.166.61, rebuild IDE, save the existing graph,
run Update ALL Worlds / Update Game Project, rebuild V1 .app.

Test your three decorations:
  - Trigger 0 toggles decoration 0; Trigger 1 toggles decoration 1.
  - Both feed AND; TRUE enables decoration 2, FALSE disables it.
  - Check off/off, on/off, on/on, off/on and off/off; particularly
    toggling the second Trigger after the first was already toggled.
  - Reopen the Game Object Properties for decoration 2 and inspect
    its Trigger / Logic Connections panel.

Testing:
  - New Stage 5.166.62 GCC C11 event/branch regression passed.
  - 5.166.58/59/60/61 schema/native regressions passed.
  - 5.166.35/36/38 title and persistence regressions passed.
  - Full Qt6 build not available here; real SIDBOX hardware test pending.

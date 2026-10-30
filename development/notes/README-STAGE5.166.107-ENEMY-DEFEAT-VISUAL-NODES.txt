SIDBOX CoderGirl IDE - Stage 5.166.107.291026
STOMPABLE ENEMY - VISUAL NODE ACTION OUTPUT

WHAT CHANGED
1. Stompable Enemy cards now have two different right-side outputs:
   - Teal STATE output (the existing Boolean/logic state reader)
   - Gold ON DEFEAT output (new event-action connector)
2. Drag the GOLD socket onto an existing Game Object to add an Enable action,
   or onto empty canvas to choose an available target from the object tree.
   Player weather, time, spotlight and world action targets are also offered.
3. A defeated enemy can run multiple Enable/Disable/Toggle actions (up to 64),
   in user-defined order. Right-click a gold connection to change its action
   or remove that exact connection.
4. Enemy-linked actions appear and remain editable as an ordered list inside
   the existing Game Object Properties dialog. Both editors save to .sbgm.
5. An enemy's old single targetObjectId/targetAction pair still works. Further
   actions use the new enemyDefeatExtraActions array. Existing worlds need no
   conversion. A separate .vsgm continues to hold only graph layout.
6. Enemy-driven plain Decorations are promoted to valid switchable objects
   on save when their sprite supports the same PPB/100% contract as Triggers.
7. The world exporter now validates extra defeat targets and emits all actions
   together inside the existing ON DEFEAT event block, keeping normal loot and
   unique quest-reward ownership independent and unchanged.
8. The read-only Flow Debugger also reads extra enemy defeat connections.
9. Enemy STATE outputs can still feed Boolean logic. The ON DEFEAT socket is
   an event for game-object/PLAYER actions, NOT a Boolean state or NPC dialogue.

IMPORTANT
- The emitted event is the established break_triggered enemy-defeat event.
- No change to engine-facing drop ownership or loot eligibility.
- Compatibility: former single-target enemies are loaded unchanged.
- This change does not implement runtime death-triggered evaluation of
  arbitrary independent Boolean graphs; direct defeat actions are supported.

FILES CHANGED
  gamevisualnodes.cpp
  gamedesigner.cpp
  gamedesigner.h
  gamedesigner_project.cpp
  gamedesigner_export.cpp
  gamefloweditor.cpp
  splashscreenwidget.cpp

VALIDATION
- New stage regression tests: 8 passed.
- Stage 5.166.105 enemy loot regression tests: 4 passed.
- All changed C++ sources: no unescaped literal newlines; braces balanced.
- Qt source build / actual GUI / generated game on SIDBOX NOT run here;
  Qt6 development libraries are unavailable in the container.
- Several historical tests assert their old splash build numbers and should
  not be interpreted as feature regressions when the release version changes.

MANUAL ACCEPTANCE
1. Build the IDE on Fedora, open a game world with a Stompable Enemy.
2. Open Visual Nodes, add/select that enemy. Confirm gold ON DEFEAT appears
   below teal STATE; drag gold to a Door or Decoration.
3. Right-click the new link to set Toggle or Disable, then add a second
   ON DEFEAT link to another object.
4. Save, close/reopen Visual Nodes: verify both links remain.
5. Open that enemy's Game Object Properties: verify both linked actions and
   their order remain visible and editable. Save without losing actions.
6. Export/build the game. Defeat enemy on SIDBOX and confirm both actions run.
7. Verify teal STATE still works as a Boolean input and random + unique loot
   still behave as before.

SIDBOX / CoderGirl IDE - Stage 5.166.108.291026
STOMPABLE ENEMY STATE -> INDEPENDENT VISUAL LOGIC

WHAT CHANGED
- Stompable Enemy teal STATE sockets can create an independent Boolean,
  AND, OR or NOT node WITHOUT connecting any Trigger action first.
- The selected Stompable owns that graph in .sbgm. A second Stompable
  can connect its teal STATE to the first enemy's AND/OR node.
- Logic nodes remain distinct from the gold ON DEFEAT action socket.
  TRUE = enemy active; FALSE = defeated or disabled. Use NOT for "defeated".
- Existing graph RESULT and TRUE/FALSE actions and dialogue branches are
  supported for enemy-owned graphs, with the same local-object validations.
- The generated game evaluates affected graphs when a Stompable is defeated,
  including graphs reading the other defeated enemy and graphs reading
  a lift/switch changed by an ordered ON DEFEAT action.
- The generator suppresses duplicate defeat-event dispatch when an ordinary
  Trigger activates later in the same frame.
- Visual Node save/reopen, Game Object Properties, and normal world .sbgm
  save/load preserve enemy-owned graphs. .vsgm still stores layout only.
- Existing Trigger-owned graphs, ON DEFEAT actions, loot/drop and quest-item
  uniqueness remain unchanged.

SIMPLE MANUAL ACCEPTANCE
1. Build IDE on Fedora, launch latest world.
2. Visual Nodes: drag Enemy A's TEAL STATE socket into empty space and
   choose Logic > OR. Connect Enemy B's TEAL STATE to the second OR input.
3. Drag the OR RESULT to empty space and choose Logic > NOT. The NOT result
   means BOTH enemies have been defeated (neither is still active).
   Link NOT RESULT to a decoration or NOT TRUE to an Enable action on a lift.
4. Save, close and reopen Visual Nodes. Ensure the new nodes and their wires
   persist. Open Game Object Properties on the owning Enemy A to check the graph.
5. Export/build and stomp A: NOT should still be FALSE. Stomp B: NOT becomes
   TRUE and the bound decoration/door/lift responds (both defeated).
6. Check that the GOLD ON DEFEAT socket still runs the ordered enemy actions,
   and repeatable loot / unique quest rewards still work.

VALIDATION (IN THIS ENVIRONMENT)
- Stage 108 regression: 6/6 passed (including native C Boolean truth table).
- Stage 105 enemy-loot: 4/4 passed.
- Stage 60 independent logic regression: passed, including its native C table.
- Source-wide literal-newline and brace scans: passed for 5 modified C++ files.
- Historical stage 107 test has one outdated version-pin assertion; other
  seven checks pass. An unrelated stage 67 weather regression test fails on
  both the old stage 107 baseline and this release (undeclared weather burst
  variables in its isolated C fixture).
- Full Qt IDE compilation and real SIDBOX hardware execution NOT possible
  here; these still require checking on Fedora / SIDBOX.

FILES MODIFIED
 gamevisualnodes.cpp
 gamedesigner.cpp
 gamedesigner_project.cpp
 gamedesigner_export.cpp
 idelibs/codehelpers/game/gameworlditems.rulec
 splashscreenwidget.cpp
 development/tests/test_stage5166_108_enemy_state_logic.py (new)

SIDBOX CoderGirl IDE Stage 5.166.92 (29 October 2026)
Direct GIVE Exchange Editing from Visual Nodes

INSTALL
1. Back up your Stage 5.166.91 IDE source and .sbgm/.vsgm game project.
2. Extract this complete source package over Stage 5.166.91.
3. Rebuild CoderGirl. Check splash Build: 5.166.92.291026.
4. Open World1 -> Visual Nodes -> Future Kim's Conversation Flow.
5. On the teal GIVE card, choose Edit full GIVE exchange in Adventure Editor.
6. The original NPC Item Exchange / Quest Requirements dialog opens immediately
   over Visual Nodes, with the exact answer's existing settings.
7. Change a response, requested item, or repeated wrong-item setting, and click OK.
   The .sbgm Adventure exchange is saved, and the GIVE card and flow refresh.
8. Click Cancel instead: no changes are applied.

WHAT CHANGED
* Reuses the actual Adventure Editor exchange dialog; no duplicate GIVE controls.
* Opens directly for the dialogue ID and answer index owning the teal GIVE card.
* Visual Nodes remains open and retains node layout, pan and zoom.
* OK updates choice.exchange in the same adventure.nodes in the .sbgm world.
* All response wires and repeated-offer socket counts refresh after changing settings.
* Disabling an exchange removes its teal preview card without deleting the dialogue.
* The card's right-click Edit GIVE exchange command uses the same direct editor.
* UI refresh is deferred until after the clicked signal to avoid deleting the
  embedded button while Qt is still handling its click.
* The ordinary Open this dialogue in Adventure Editor path is unchanged.

SAFETY
* Cancel leaves the original exchange unchanged.
* Existing .sbgm write and conflict checks, including backups, remain in force.
* The Visual Nodes main dialog stays open; the game designer tab reloads when
  Visual Nodes is eventually closed through its existing integration.
* No generator/runtime changes, no save format changes, no user main.c edits.

VERIFICATION
* The Stage 5.166.92 source contract passes.
* 29 selected Stage 5.166.65-92 regression scripts passed.
* A full Qt build and interactive Qt popup test are still required on desktop
  (Qt 6 development headers are unavailable in this tool environment).

FILES
 gameadventureeditor.cpp / .h
 gamevisualnodes.cpp
 splashscreenwidget.cpp
 development/tests/test_stage5166_92_give_exchange_direct_edit.py
 additional regression checks updated for this release's splash version

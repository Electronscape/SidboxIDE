SIDBOX CoderGirl IDE — Stage 5.166.53.281026
VISUAL NODES — READ TOGGLE STATE / TRUE-FALSE DIALOGUE BRANCH

INSTALL
Apply hotfix over Stage 5.166.52, then rebuild the Qt IDE.
Regenerate ALL worlds / Update Game Project, then rebuild the V1 game before
hardware testing. This stage includes generated-runtime changes.
Your hand-owned main.c does not need modification.
Existing .map files and save slot formats are unchanged.

HOW TO TEST
1. Open a world .vsgm and select an existing Trigger (FIRE2 or touch).
2. Click '+ Read Toggle State' (or right-click Trigger > Add Read Toggle State).
3. Right-click the new teal card > Choose Game Object state source.
   Pick a same-world Game Object, e.g. Lifty.
4. Connect your Trigger to Lifty with a Toggle action, as before.
5. Drag the condition's green TRUE or red FALSE port into empty canvas.
   Choose an existing dialogue using the same folder tree as the Dialogue
   Editor, or choose Create New Dialogue. Both produce purple branch cards.
6. Save Graph + World, regenerate ALL worlds, rebuild V1.
7. Activate the Trigger twice: the selected object's new active state is
   tested AFTER all normal Trigger actions, so TRUE and FALSE choose
   different single-message dialogues on alternating toggles.
8. Save and reopen .vsgm, then edit the Trigger in Game Object Properties;
   save that editor, reopen .vsgm. The TRUE/FALSE settings must persist.
9. Right-click a branch wire to remove that connection. Deleting a condition
   node unlinks its TRUE/FALSE dialogues, not the underlying Adventure nodes.

DATA MODEL / SCOPE
.sbgm remains authoritative. Only three optional fields per Trigger were
added: toggleStateTargetId, toggleTrueDialogueNode, toggleFalseDialogueNode.
.vsgm stores card positions/camera but no gameplay connection copies.
The condition reads the active bit of a local Game Object, NOT transient
trigger_fired. Remote/NPC targets are deliberately not offered.
TRUE and FALSE dialogue is displayed in single-message/no-actions mode for
this first pass, so it doesn't execute accidental quest/dialogue actions.
Unconditional Show Dialogue remains independently configurable.

VERIFICATION
Selected Visual Nodes regression checks and native GCC branch-behaviour
check passed. Full Qt6 IDE compilation and SIDBOX hardware behaviour have
NOT been verified in this environment. Test with the backed-up game first.

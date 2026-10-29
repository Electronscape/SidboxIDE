SIDBOX CoderGirl IDE — Stage 5.166.54.281026
VISUAL NODES: REAL TRUE/FALSE ACTION CONNECTIONS

BASE: Apply this hotfix over Stage 5.166.53 (or use the complete source archive).

WHAT CHANGED
- The Trigger -> Read Toggle State wire is shown whenever the condition card is present.
- Drag either TRUE / FALSE output to an existing Game Object or into empty space.
- The empty-space picker now presents compatible Game Objects/NPCs and the
  existing nested Dialogue Actions tree, including Create New Dialogue.
- Game Object links default to Enable; right-click a branch wire to choose
  Enable, Disable, Toggle or Remove Connection. Parallel actions are supported.
- Show Dialogue remains supported on either branch (one dialogue per branch),
  with existing dialogue folder names and stable numeric IDs.
- The condition card's right-hand action list also supports Edit/Remove.
- TRUE and FALSE actions are authored in .sbgm alongside the earlier
  toggle-state and branch-dialogue fields. .vsgm remains layout/camera only.
- The ordinary Game Object editor's project loader/saver preserves these fields.
- Generated V1 C runs normal Trigger actions, THEN tests the configured
  object's current active state, THEN performs the matching branch's actions
  and optional single-message dialogue.
- Deleting a node or a branch wire clears affected actions, never the
  underlying Game Object or Adventure Dialogue definition.

TEST
1. Start from a Trigger with Toggle Lifty.
2. Add Read Toggle State and select Lifty as its state source.
3. Confirm the Trigger -> condition wire appears.
4. Drag TRUE output to a Door; set the wire action to Enable.
5. Drag FALSE output to the Door; set that wire to Disable.
6. Optionally connect a dialogue from either output.
7. Save Graph + World; close/reopen and check the same wires appear.
8. Edit the Trigger in traditional Game Object Properties, save it,
   reopen .vsgm, and check the TRUE/FALSE actions remain.
9. Update ALL Worlds / Update Game Project, rebuild the V1 .app.
10. On hardware, alternate the Trigger; the Door should follow Lifty's
    NEW active state. Then test removing one wire and regenerating.

SCOPE / LIMITATIONS
- One toggle-state condition per Trigger, with max 64 Game Object actions
  on TRUE and max 64 on FALSE. The dialogue selection remains one per branch.
- Both outputs are evaluated from the live local Game Object active bit,
  AFTER normal Trigger actions. They are not separate runtime objects.
- Existing .sbgm worlds and saved games remain compatible; new fields
  are optional and default to empty. Neither .map nor hand-owned main.c
  changes are required.
- No entire Qt6 GUI build can be performed in this environment. Source
  contract tests and a native C condition/action regression passed, but
  Qt compile, GUI mouse interactions and SIDBOX hardware remain unverified.

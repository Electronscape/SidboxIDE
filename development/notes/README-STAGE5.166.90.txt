SIDBOX / CoderGirl IDE Stage 5.166.90 (29 October 2026)
=======================================================
Visual Nodes: reconnect existing Show Dialogue cards + fade unrelated nodes

INSTALL
-------
1. Back up your Stage 5.166.89 IDE source and game project.
2. Extract the complete Stage 5.166.90 archive over the IDE source.
3. Rebuild the IDE, confirming the splash build 5.166.90.291026.
4. No generated gameplay changes; no ALL Worlds export is required for these
   visual-editor changes alone. Existing main.c is not modified.

WHAT CHANGED
------------
- Drag an independent AND/OR/Boolean TRUE or FALSE output directly to the
  matching existing SHOW DIALOGUE card's square input to reconnect its action.
  The card's current dialogue selection is reused when possible; if there is
  no selected dialogue, the existing dialogue-folder chooser opens instead.
- Similar reattachment support for legacy Boolean branch dialogue cards and
  Trigger Show Dialogue cards (instead of forcing recreation).
- Reject dropping a branch wire onto another branch's Show Dialogue action
  card: they are separate .sbgm event owners, not generic dialogue definitions.
- Clicking a node fades unrelated cards to 24% opacity while retaining the
  selected card and its directly connected cards at full opacity. Selecting
  a wire preserves its endpoints similarly. All dimmed cards remain clickable.
- Starting a wire drag now focuses its owning card, not the synthetic socket
  ID. Unselecting/clearing focus restores full card and wire opacity.
- Existing live wire dragging, context-menu disconnection, wire highlighting,
  Undo/Redo and saved .sbgm/.vsgm formats are unchanged.

TEST
----
1. In your AND | logic1 graph, disconnect the green TRUE -> SHOW DIALOGUE |
   TRUE wire, leaving the dialogue card on the canvas.
2. Drag the logic node's TRUE output to the existing SHOW DIALOGUE | TRUE
   input square. Confirm it reconnects without deleting or recreating the card.
3. Repeat for the FALSE branch, and with a card whose dialogue is set to None:
   the folder chooser should open.
4. Click logic1: only that node and its immediate wired neighbours remain
   fully opaque; others fade. Click a wire and then empty space to verify focus.
5. Move cards and confirm connected wires remain attached as in Stage 5.166.88.

VERIFICATION
------------
23 Visual Nodes focused Python source regression tests passed.
Qt desktop build and mouse/paint verification could not be run in this
container; test these interactions in the locally compiled IDE.

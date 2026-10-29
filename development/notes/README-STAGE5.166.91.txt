SIDBOX CoderGirl IDE Stage 5.166.91 (29 October 2026)
Dialogue Socket Order + Direct Adventure Dialogue Editing

INSTALL
1. Back up your IDE source and game project.
2. Extract this complete source archive over Stage 5.166.90.
3. Rebuild the IDE and confirm splash Build: 5.166.91.291026.
4. Open Visual Nodes in your game world and expand/collapse dialogue cards.
5. Click Open this dialogue in Adventure Editor on any conversation card.
   The exact numbered Dialogue Node editing dialog opens immediately.
   Save or cancel that dialog to return automatically to Visual Nodes.

FIXES
* Dialogue outputs now have the same priority in both views:
    Teal GIVE, amber missing required item, purple normal answer routes.
* Compact outputs use a stable role/answer ordering, preserving each wire's
  exact socket identity. Expanded socket rows use the same priority.
* Adventure dialogue deep-link directly opens the numbered dialogue editor.
* On Save/Cancel of the dialogue editor, Visual Nodes automatically reopens.
* Graph layout, pan and zoom are saved before the hand-off.
* Accepted dialogue edits are committed to the .sbgm before the graph reloads.
* Cancelling the dialogue editor does not write edited dialogue content.

NOT CHANGED
* Adventure dialogue IDs or branch semantics.
* Game runtime or generator, world-save format, hand-maintained main.c.

VERIFICATION
Source-level regression tests are included. Qt development headers are not
installed in this environment, so the full Qt desktop build and graphical
interaction need verification on your workstation.

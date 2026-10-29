SIDBOX / CoderGirl IDE Stage 5.166.83 (28 October 2026)
VISUAL NODES: GIVE PULL-OUT + SOCKET EDGE / SPACING / HOLLOW FIXES

INSTALL
1. Back up your Stage 5.166.82 IDE source and game project.
2. Extract this full-source archive OVER Stage 5.166.82.
3. Rebuild the IDE and verify Build: 5.166.83.281026 on the splash screen.
4. No regeneration of the game is required: this stage changes UI only.
   Your hand-maintained main.c is unchanged.

WHAT CHANGED
- The turquoise GIVE output is now centred precisely on the dialogue
  card's RIGHT BORDER and can be dragged onto empty canvas. Dragging it
  MOVES the existing matching GIVE card to the drop location; it NEVER
  creates a second exchange, changes required items, or rewires dialogues.
- Dropping that turquoise wire onto its own GIVE card selects the card.
  Dropping onto an unrelated card is rejected, leaving all gameplay unchanged.
- Normal purple / missing-item amber / GIVE turquoise sockets are grouped
  beside their respective answer text, in a consistent 17-pixel fan.
  Previously some unused ports appeared beside the bottom card border.
- GIVE response outputs are also centred on their card's right border.
- When collapsed, output sockets stack vertically at 17-pixel intervals
  along the edge, with card height increased to contain them if needed.
- Hollow input and output sockets use an OPAQUE dark canvas-colour core
  (#1a1f29), keeping node borders and wires from showing through.
- The underlying Adventure dialogue IDs and .sbgm exchange fields have
  not changed, nor have the game generator or runtime sources.

QUICK DESKTOP CHECK
1. Open World1 > Visual Nodes > Future Kim's opening conversation flow.
2. Find the answer with GIVE enabled, 'Can I get past?'.
3. Drag its turquoise socket to empty canvas. The ONE existing GIVE card
   should move to the drop point; its dashed turquoise connection follows.
4. Collapse and expand the dialogue and GIVE cards. Every socket should
   remain on the border, not hang below the card or show lines through it.
5. Press Ctrl+Z to undo the pull-out, Ctrl+Y to redo; save and reopen
   to verify the final layout persists without changing Adventure data.
6. Verify a purple Next path and an amber missing-item path still lead
   to the exact dialogues that were already configured.

VERIFICATION
The new Stage 5.166.83 source-contract checks and the previous targeted
Visual Nodes checks pass. This environment has no Qt6 development headers;
full desktop compilation and pointer/drag testing must be verified locally.

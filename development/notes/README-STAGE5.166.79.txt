SIDBOX / CoderGirl IDE Stage 5.166.79 (28 October 2026)
Visual Nodes canvas navigation, socket states, insertion, tidy and conversation curves

WHAT CHANGED
- gamevisualnodes.cpp / NodeCanvas: hold the MIDDLE mouse button to pan the
  graphics viewport. Existing LEFT-drag pan on empty space, LEFT-drag card
  movement/connection wiring, RIGHT-click menus and wheel zoom are retained.
- Node ports: smaller square INPUTS and round OUTPUTS display as a hollow
  outline while unwired/unused; an attached connection fills the port with
  its original colour. Applies to NPC, Game Object, PLAYER, logic, dialogue
  and read-only Adventure conversation preview sockets. This is a visual
  indication only, not a change to port eligibility or gameplay.
- New graph cards added by graph actions and popup operations are positioned
  relative to the CURRENT visible canvas center, looking for a nearby free
  space. Existing card coordinates in .vsgm are never reset on opening.
- A newly imported Adventure conversation flow starts near the current canvas
  view instead of the fixed top-right coordinates used before, with enough
  row spacing for full-size conversation cards.
- New Tidy toolbar button: confirms before rearranging, groups cards using
  existing visible wires, arranges connected components in columns and
  stacks groups separately. Tidy changes graph card positions ONLY. Save
  Graph + World to persist layout; cancel does nothing.
- Conversation flow preview curves now use the same bounded cubic calculation
  as gameplay dialogue wires. Required-item alternate routes stay amber dashed.
- Splash screen: Build: 5.166.79.281026.

INSTALL
1. Back up your Stage 5.166.78 source tree and .sbgm/.vsgm game project.
2. Extract this FULL source archive over Stage 5.166.78.
3. Rebuild the IDE; verify splash version 5.166.79.281026.
4. Open Forest > Visual Nodes; middle-drag over empty space and over card bodies.
5. Observe hollow disconnected ports and filled connected ports. Expand/collapse
   an NPC and a conversation card and verify sockets stay aligned with wires.
6. Pan to a distant location, then add a NEW node or show a fresh conversation
   flow: it should appear in the area being viewed, not at fixed (950,85).
7. Click Tidy and Cancel: nothing should move. Click Tidy and Yes: connected
   groups should arrange in columns. Save Graph + World, close and reopen to
   confirm placement. Test an existing Boolean/weather/NPC graph afterwards.

VERIFICATION / BOUNDARIES
- 17 targeted historical + new canvas source/native tests passed (see
  development/tests/test_stage5166_79_canvas_navigation_tidy.py).
- The Qt IDE could not be compiled here: Qt 6.5 development package is not
  installed in this execution environment. Please compile/test on desktop.
- No generated gameplay/runtime exporter files changed. No game regenerate
  or user-owned main.c edits are required for this editor-only change.
- Tidy currently provides a one-shot layout, not a complete graph-layout
  optimiser or an Undo command. If you dislike the arrangement, close without
  saving and choose Discard when prompted to restore the prior saved layout.

SIDBOX / CoderGirl IDE Stage 5.166.77 (28 October 2026)
Conversation Flow: readable destination selectors

Source changes:
- gamevisualnodes.cpp, VisualNodesDialog::makeConversationCard():
  Each answer now gets its own full-width Next dropdown beneath the answer.
  Destination options show "#ID | Speaker: dialogue preview" instead of "#ID".
  The wider popup and entry tooltips reveal more/full text, including multiline lines.
  'Close conversation' and missing targets remain explicitly visible.
  Item-gated cards grow to fit the new controls; answer wires stay aligned.
- splashscreenwidget.cpp: Build: 5.166.77.281026.
- development/tests/test_stage5166_77_readable_dialogue_destinations.py:
  Static contract checks for readable entries and stable numeric destination IDs.

The saved value for every answer's 'next' stays the same integer dialogue ID
in adventure.nodes in the .sbgm. No .vsgm format change, no game code generator
change, no modification to user-owned main.c.

INSTALL:
1. Back up your IDE source and your .sbgm game project.
2. Extract the full archive over IDE Stage 5.166.76.
3. Rebuild the desktop IDE and verify splash build 5.166.77.281026.
4. Open Forest -> Visual Nodes -> Big Steve's conversation flow.
5. Check a Next selector now reads e.g. '#2 | Big Steve: Hello again...'.
6. Change an answer's destination, save Graph + World, reopen and confirm the
   correct ID and flow connection are still there.
7. Try Close conversation, a long dialogue label, and a missing legacy ID.

Validation:
- Source-contract and previous relevant regression tests passed.
- No Qt development headers in this environment: the desktop Qt build and
  mouse interaction still require local validation.
- No game regeneration required for the selector-only UI update.

SIDBOX / CoderGirl IDE Stage 5.166.86 (28 October 2026)
Dialogue Self-Link Safety and Wire Disconnect

INSTALL
  Back up your Stage 5.166.85 source and game project.
  Extract this complete source archive over Stage 5.166.85.
  Rebuild the IDE. Splash build: 5.166.86.281026.
  You do not need to regenerate your game for the editor-only changes.
  If you modify a dialogue route, Save Graph + World and regenerate the game
  before testing that new route on hardware.

CHANGES
  1. Connecting a conversation answer to its own dialogue now asks first.
     No is the default. Valid intentional loops remain supported.
  2. Existing and new self-loop wires are routed visibly around the card,
     rather than turning into tiny, nearly invisible eyes by the sockets.
  3. Right-click a normal purple or missing-item amber conversation wire
     to disconnect just that answer route (changes next/missingNext to -1).
  4. Right-click a dialogue card's header and select Disconnect answer route
     as a fallback, even when the wire is obscured by another card.
  5. Right-click a GIVE response wire to disconnect that exchange response.
     -1 means no special response, not a forced close.
  6. Ctrl+Z/Ctrl+Y can restore pending edits; Save Graph + World persists them.

DATA AND SAFETY
  No .sbgm schema changes and no dialogue ID renumbering.
  No exporter, generated runtime, or user-maintained main.c changes.
  Existing looping dialogues are preserved until you explicitly disconnect.

VERIFICATION
  21 focused Visual Nodes source regression scripts passed, including a new
  self-loop test. Qt desktop build/interaction remains to be tested by user.

FILES
  gamevisualnodes.cpp
  splashscreenwidget.cpp
  development/tests/test_stage5166_86_conversation_self_links.py
  Current-stage expectations in earlier Visual Nodes source tests

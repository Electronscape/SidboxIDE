Stage 5.166.56.281026 - Visual Nodes: Game Object state -> Boolean

Visual flow: Trigger -> action on Game Object -> Boolean -> TRUE/FALSE actions.
- Normal Game Objects (Lift, Door, etc.) now expose a teal state-output port.
- Drag the teal output from Lifty into empty space, expand Logic, then
  double-click Boolean (TRUE / FALSE). Or select Lifty then use + Boolean.
- The Boolean automatically reads Lifty's enabled/disabled active state.
  There is no duplicate source dropdown inside the Boolean.
- The incoming teal Boolean wire now starts at the actual Game Object,
  not at the Trigger. TRUE / FALSE sockets still connect to existing
  Game Object actions (Enable/Disable/Toggle) or Show Dialogue cards.
- The .sbgm continues to be the single source for the Trigger's real
  conditional execution; .vsgm stores only layout/camera/placed cards.
- The IDE only allows new Booleans for Game Objects already controlled
  by a Trigger action. If several Triggers control the same object, choose
  which Trigger activation owns the Boolean branch.
- Old .sbgm Boolean definitions load without conversion and are displayed
  using the new source-object wire. Existing TRUE/FALSE actions are kept.

IDE-only release. No .sbgm or .vsgm schema, generated runtime, .map,
user-owned main.c or read-only Logic Flow changes.
Qt GUI compilation unavailable in this environment. The focused tests
and native GCC boolean semantics test passed; desktop mouse interaction
still requires testing.

Read development/notes/INSTALL-STAGE5.166.56.txt for details.

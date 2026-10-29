SIDBOX / CoderGirl IDE Stage 5.166.84 (28 October 2026)
VISUAL NODES: GIVE RESPONSE SOCKETS ALIGNED TO DROPDOWNS

INSTALL
1. Back up your Stage 5.166.83 source and your game project.
2. Extract this FULL-SOURCE archive OVER Stage 5.166.83.
3. Rebuild the IDE; the splash should display Build: 5.166.84.281026.
4. Open World1 > Visual Nodes > Future Kim's conversation GIVE card.
5. No game regeneration and no main.c edits are required for this UI-only fix.

FIX
The five GIVE outputs were positioned before Qt had embedded and finally laid
out their destination dropdown widgets. Their screen positions subsequently
changed while the sockets stayed at provisional coordinates. The result was
increasing vertical separation in expanded cards and apparent misalignment.

Socket centres now use the QGraphicsProxyWidget's final subWidgetRect for the
matching dropdown, after Qt styling and layout activation. Each output has a
stable GIVE route-index property so it cannot accidentally align to another
combo box if more controls are added later. The wiring pass rechecks the actual
positions after window show and when scene links are redrawn.

The five output socket centres should now sit directly across from their five
response dropdowns in an expanded GIVE card, and collapsed cards continue to
use the compact vertical stack. No data format or game logic was changed.

DESKTOP ACCEPTANCE
- Open Future Kim's GIVE card and visually compare all FIVE output circles to
  their corresponding dropdown centreline.
- Collapse/expand the card and repeat.
- Save the graph, close/reopen, and verify the socket positions and wires.
- Check all five destinations still match Adventure Editor and work as before.
- Change an exchange response and test undo/redo and wire rerouting.

VERIFICATION
- Targeted source contract and regression checks passed. The current
  environment lacks Qt6 development headers, so a full GUI build and visual
  testing on the desktop were not performed here.

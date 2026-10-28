SIDBOX CoderGirl IDE — Stage 5.166.50.281026
VISUAL NODES — Smooth Show Dialogue Wire Routing

INSTALL
Apply this hotfix over Stage 5.166.49 sources and rebuild the Qt IDE.
This is a purely visual IDE change. No .sbgm/.vsgm format change,
no game-world regeneration, no runtime changes, and no changes to main.c.

FIX
Stage 5.166.49 still generated a rectangular, above-the-cards path for
purple dialogue wires when the dialogue card was left of its Trigger.
The wire renderer now uses cubic Bezier curves in both directions.

When a dialogue card is to the right, the wire enters the left edge like an
ordinary action link. When the card is left, the wire enters the RIGHT edge,
so the curve does not need to travel over the top of the graph or through the
card. Ordinary red/green/yellow action wires are unchanged.

The existing generous right-click target and Remove Connection handling for
purple wires are unchanged; no gameplay actions are modified by this patch.

TESTED HERE
Stage 5.166.50 cubic-geometry source/numeric regression passed, including
layouts modelled on the WellDrop screenshot. Stage 5.166.40-49 Visual Nodes
source/schema tests passed (9 suites), plus native C title, save and New Game
reset regressions (3 suites). Qt6 GUI compilation and live desktop rendering
are still unverified here; visual confirmation on your machine is needed.

QUICK TEST
Open the .vsgm, move a purple Show Dialogue card above and LEFT of its
Trigger, then move it to the RIGHT. Both should show a single smooth curved
wire, with no square route over the top. Right-click either wire to verify
Remove Connection is still available. Close/reopen to check layout persists.

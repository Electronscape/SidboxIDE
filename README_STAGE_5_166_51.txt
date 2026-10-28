SIDBOX CoderGirl IDE — Stage 5.166.51.281026
VISUAL NODES — 8PX SNAP + DIALOGUES IN VISIBLE NODES

INSTALL
Apply the hotfix over Stage 5.166.50 and rebuild the Qt IDE.
This is an IDE-only change. No regeneration of worlds or .app, no .map
conversion and no modification to your game-owned main.c is needed.

CHANGES
1. Card movement snaps to an 8-pixel grid on both X and Y axes. Applies
   to standard Game Object/NPC cards and purple Show Dialogue cards.
   Existing saved .vsgm card positions are preserved when the graph opens;
   they snap once you move a card. Moving a card marks the graph as changed,
   and Save Graph + World stores the snapped scene position in .vsgm.

2. Purple Show Dialogue cards now appear in the left VISIBLE NODES list,
   distinguished by purple text and labelled with the originating Trigger
   and selected dialogue ID (or 'unlinked'). Clicking selects them,
   double-clicking centres the view, and Delete/removal also clears their
   sidebar entries. Changing dialogue selection updates the displayed ID.

NO CHANGES TO
The old read-only Logic Flow editor; .sbgm data schema, gameplay links,
trigger behaviour, dialogue playback, .vsgm JSON format, wire routing,
world map, title/death/save/load or SIDBOX runtime rules.

TESTING HERE
12 Stage 5.166.40 through Stage 5.166.51 Visual Nodes source/schema
checks and 2 native reset/title source tests passed. Full Qt6 GUI build
not available here: actual desktop dragging/list interaction remains for
local confirmation.

QUICK CHECK
Open a .vsgm with a purple Show Dialogue card and a Trigger. Verify both
appear in VISIBLE NODES. Move each card a small distance, save, close and
reopen. Their X/Y positions should be multiples of 8 after dragging;
existing cards you never moved should retain their exact positions.
Double-click the purple list entry to centre its card; remove the card
and verify its list entry disappears without deleting the .sbgm dialogue.

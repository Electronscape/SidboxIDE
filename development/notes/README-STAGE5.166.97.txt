SIDBOX CoderGirl IDE Stage 5.166.97 (29 October 2026)

Stage 5.166.97 contains two Visual Nodes editor fixes:

1. Left-drag an empty area of the canvas to rubber-band-select several nodes;
   drag a selected node to move them as one selection. Middle-drag still pans.
   Ctrl-click adds/removes cards to/from the selected set. The focus display
   highlights all selected cards and their connected wires. Multi-select
   never automatically deletes several gameplay resources.

2. Independent logic TRUE / FALSE can reconnect to an existing Show Dialogue
   card, even if its Adventure dialogue is also used by another logic branch.
   This reuses the original numbered dialogue, not a second definition.
   A different branch gets its own Show Dialogue action card to preserve
   TRUE/FALSE behaviour. Drops preferentially hit actual cards/sockets rather
   than nearby overlapping wire hitboxes.

No changes to game exporter, hardware runtime or world file format.
The IDE build label is 5.166.97.291026.

INSTALL: Extract this full source package over Stage 5.166.96 and rebuild IDE.
Test Ctrl+drag selection, move/undo, then disconnect/reconnect FALSE to an
existing dialogue card. Changes to graph logic require Save Graph + World.
The source regression suite passed; Qt desktop compilation / GUI acceptance
still needs confirmation on the user's machine.

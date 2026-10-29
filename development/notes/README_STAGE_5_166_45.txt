SIDBOX CoderGirl IDE - Build 5.166.45.271026
Visual Nodes: On-demand graph and compatible-node picker

Visual Nodes now starts with only real connected world objects and dialogues.
It reads all objects and actions from the matching .sbgm each time it opens.
Objects not connected to anything are not dumped onto the canvas. Nodes
explicitly placed by the user remain visible while assembling a new flow.

Right-click empty canvas to see a searchable tree of world-defined object
categories. Double-click an entry to place it at the clicked position.
Adventure NPC resources are included if referenced by this world's NPC list.

Drag from a Trigger's output socket into empty canvas to open the compatible
node picker. Choose an existing Game Object/NPC: it is placed and linked with
the default Enable action. Right-click the wire, or use the right connection
panel, to change to Disable/Toggle or remove it.
Choose Show Dialogue: a dialogue card is placed, with its own editable default
message if the Trigger had none. Existing dialogue is preserved otherwise.

.vsgm holds only graph presentation: placed node IDs, positions, dialogue
card display and camera. Gameplay links are NOT duplicated into .vsgm;
.sbgm remains the sole authority. Old .vsgm documents still load.
Game Object Properties and the read-only Logic Flow have not been changed.

No game project regeneration and no main.c changes required.

TESTING: source/schema regression checks passed; full Qt6 GUI build and
interactive mouse testing must still be performed on a Qt6 desktop.

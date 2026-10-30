CoderGirl IDE - Build 5.128.1.301026
Quest Line ON COMPLETED -> Show Dialogue connection hotfix
30 October 2026

ROOT CAUSE
Stage 5.128.0 allowed the Quest completion source to drop onto a Show
Dialogue card only if that card already referenced an existing Adventure
dialogue ID. Newly placed Show Dialogue cards contain -1 (None / not
connected), so dropping the wire silently did nothing. The card was
visually present, but no gameplay action was authored or saved.

FIXES
1. Dragging a Quest ON COMPLETED gold output onto an unlinked purple Show
   Dialogue card now opens the normal Adventure dialogue folder selector.
   Select an existing dialogue or + Create New. Cancel leaves the graph
   unchanged. Valid selections commit a real link.
2. + Show Dialogue for a selected Quest completion card now asks for a
   dialogue immediately. No more accidental visually-present, unlinked
   placeholders. Existing empty placeholders can still be connected.
3. Real Quest completion dialogue links now count as connected, not as
   orphans, in both linkedObjectIds() and connectedCardIds(). The graph
   remains visible even without .vsgm layout hints and Remove Orphans
   cannot erase a valid quest dialogue display as if it were disconnected.
4. The status line confirms the selected Adventure dialogue ID and
   reminds the user to Save Graph + World.

PERSISTENCE AND RUNTIME
- Real quest completion links still persist to world .sbgm in
  questCompletionDialogues[questId] = {dialogueNode,mode}.
- .vsgm keeps layout only, as before.
- No changes to gameplay generator, quest manager, save format, queue,
  animation, combat, or user-owned main.c.

HOW TO TEST
1. Build the IDE. Open Visual Nodes and select a Quest Line ON COMPLETED
   card. Click + Show Dialogue, choose an existing Adventure dialogue.
   Alternatively, drag the gold ON COMPLETED output onto an existing
   unconnected Show Dialogue card and choose the dialogue in the picker.
2. A solid purple wire must appear, and the card selector must show
   the chosen dialogue ID (not None).
3. Save Graph + World, close Visual Nodes, reopen. The dialogue connection
   must survive. Try Remove Orphans; the linked card must be preserved.
4. Regenerate the world and rebuild the game. Completing the quest should
   enqueue the dialogue once. Reloading completed quest saves should not
   repeat it.

VALIDATION
- 28 focused source/native regression tests passed.
- 139 C++ sources/headers scanned; no invalid auto* lambda declarations.
- Full Qt 6.5 build unavailable here (Qt6Config.cmake not installed).
- SIDBOX hardware test still needed.

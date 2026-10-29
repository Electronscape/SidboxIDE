SIDBOX / CoderGirl IDE Stage 5.166.82 (28 October 2026)
=====================================================
GIVE Exchange conversation-flow nodes

Base: Stage 5.166.81. Extract this full-source archive over your Stage
5.166.81 IDE source and rebuild the IDE. Splash build: 5.166.82.281026.

New in Visual Nodes:
* Showing an NPC's conversation flow now imports existing enabled GIVE
  exchanges as separate teal GIVE cards connected to their originating
  dialogue answer. Exchanges never become duplicate .sbgm definitions.
* Requested item names, AND/OR mode, incremental hand-ins and consume
  settings are displayed for context. Advanced requirements and event
  actions are still edited in Adventure Editor.
* Distinct editable destinations and draggable output ports for:
  general wrong item, first/second/third/fourth-or-later offers of the
  tracked wrong item (only if repeated-offer replies are enabled).
* The destination selector uses the Adventure folder tree in a separate
  modal dialog, with readable dialogue titles and tooltips.
* -1 destinations say 'Keep current NPC dialogue' rather than suggesting
  that a conversation would close.
* Changing a GIVE route writes ONLY that named key into the existing
  choice.exchange object. No item requirements, counters, actions or
  other routes are modified. The game exporter and runtime are unchanged.
* The GIVE card's position and collapsed state live in .vsgm.
  Undo/Redo includes the nested .sbgm exchange field changes.
* Right-click a GIVE card for Adventure Editor handoff or to hide its
  parent conversation preview. Deleting a preview does not delete a
  dialogue or exchange from the game.

Suggested test on your existing World1 Future Kim conversation:
1. Open World1 > Visual Nodes > Future Kim opening conversation flow.
2. On Dialogue #0 Answer 1, follow the teal dashed link to the GIVE card.
3. Confirm Flower is requested and Feather is the tracked wrong item.
4. Confirm general wrong item -> #5, tracked repeats -> #6/#7/#8/#9.
5. Drag a response port to an existing dialogue; save and check Adventure
   Editor shows the same destination. Undo/Redo and Refresh from World.
6. To test changed gameplay responses, regenerate ALL Worlds and rebuild
   your game. Your user-owned main.c is not changed.

Verification:
* New 5.166.82 GIVE exchange source/data contract test passes.
* 16 current regression checks for 5.166.67 through 5.166.81 pass.
* The Stage 5.34 native exchange harness already aborts on unmodified
  Stage 5.166.81; this is not caused by this patch.
* Qt desktop rebuild and GUI interaction not available in this environment.

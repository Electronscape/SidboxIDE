SIDBOX CoderGirl IDE - Stage 5.166.128 (30 October 2026)
Quest Line ON COMPLETED -> Adventure Show Dialogue
===================================================

PURPOSE
  A quest's one-shot ON COMPLETED event can now play an Adventure dialogue
  directly, alongside its existing Game Object and QUEST EVENT/SIGNAL actions.
  This closes the Stage 121 dialogue-action gap without adding an unowned
  independent Boolean logic gate or changing existing quest progression.

HOW TO USE
  1. Open Visual Nodes in the world where the quest will complete.
  2. Add (or select) the desired card under Quest Lines / Completion Events.
  3. Drag its gold EVENT: ON COMPLETED socket to empty canvas.
  4. Choose Dialogue Actions -> an existing Adventure dialogue, or
     '+ Create New Dialogue'. A purple SHOW DIALOGUE card is connected.
  5. On the SHOW DIALOGUE card choose playback mode: Single message,
     Message sequence, or Full conversation (actions). Its speaker and text
     edit the same Adventure dialogue ID, not a copy.
  6. Save Graph + World, regenerate that WORLD's gamehelpers, and compile
     the applet. For a two-world game, regenerate affected worlds as usual.

  Alternative: select the Quest Line card, then click '+ Show Dialogue',
  and pick an Adventure dialogue on the created card.
  Dragging an ON COMPLETED socket onto an existing visible Dialogue card also
  uses its Adventure dialogue ID, creating an independently editable action
  card for that Quest Line. Each Quest Line completion has one directly
  selected dialogue; use Adventure dialogue branching/sequence for more.

BEHAVIOUR
  - The dialogue is enqueued via the existing Stage 119 FIFO, following
    that Quest Line's ordinary completion actions; game_adventure serialises
    modal dialogues exactly as for Trigger/Logic action dialogues.
  - It executes only when the quest changes to COMPLETED in the current world.
    Restoring a save, opening the Journal or revisiting a finished quest
    does not replay the completed event.
  - An old world without this feature exports exactly as before.
  - The existing quest prerequisite unlock/lock system is unchanged.
  - World .sbgm owns the gameplay reference under:
        "questCompletionDialogues": {
          "quest_id": {"dialogueNode": 17, "mode": "conversation"}
        }
    alongside the original "questCompletionActions" action links.
    The .vsgm continues to own canvas layout only, not gameplay events.
  - Missing dialogue IDs and invalid modes fail export with explanations.
  - Empty worlds without any managed Game Object still cannot export active
    quest completion actions/dialogues because their stub runtime has no
    quest completion dispatcher. Add a Trigger or another object first.

WHAT WAS NOT CHANGED
  No change to Quest objective evaluation, ordered/unordered progression,
  save payload, ACTION queue capacity, Stompable Enemy damage, melee/player
  animation, World Map, or user-owned main.c. No project was edited.

TESTING
  - Focused source-contract and native quest/combat/journal tests pass.
  - Full Qt6 IDE build unavailable in this environment (Qt 6.5 SDK missing).
  - Full game export and real SIDBOX hardware behaviour require testing.

RECOMMENDED HARDWARE TEST
  1. Make two objectives in one quest, set ANY ORDER, connect each to its
     own Quest Event/SIGNAL as already tested.
  2. Connect the Quest Line's ON COMPLETED to a SHOW DIALOGUE card.
  3. Verify objective 1 does not show that dialogue. Finish objective 2.
  4. The completion dialogue should show once, after any earlier queued
     actions. Reopen Journal and load a completed save: it should not repeat.

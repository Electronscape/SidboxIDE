SIDBOX CoderGirl IDE - Stage 5.166.81 (28 October 2026)
CONVERSATION FLOW: AMBER MISSING-ITEM OUTPUT SOCKETS + WIRE HINTS

BASE
  Full source based on Stage 5.166.80.
  Extract over Stage 5.166.80, then rebuild the desktop IDE.
  Splash: Build: 5.166.81.281026

ADVENTURE DIALOGUE FLOW
  * Hover normal PURPLE dialogue wires / sockets to see their meaning:
      the chosen answer proceeds to its `next` dialogue.
  * An answer with a `requires` inventory item now exposes a separate AMBER
    output socket. The orange dashed line starts there and represents the
    original `missingNext` destination when the player lacks that item.
  * The amber output is HOLLOW if no alternate dialogue is configured.
  * Item-gated answers have a `No item ->` destination selector alongside
    their existing normal `Next ->` selector. Both use the real Adventure
    Dialogue folder browser (in a separate top-level window).
  * Drag a PURPLE or AMBER socket to an existing conversation card to connect
    it. Drop onto empty canvas to pick an existing destination from the
    Adventure Dialogue folder tree. Self-looping dialogue is supported.
  * Neither action invents new dialogue IDs. New dialogue creation still
    belongs to the Adventure Editor.
  * Selecting 'No alternate dialogue' writes missingNext=-1, preserving
    Adventure's existing no-alternate behaviour. A branch only runs when
    the answer is nonblank AND a required item is configured.
  * Socket placement tracks the actual row position as item-gated answers
    grow taller; collapsed cards retain both ports.
  * Undo / Redo is available for these pending destination changes until
    Save Graph + World. Save still creates the world .vsgm-backup.

DATA / COMPATIBILITY
  * Editing normal branches changes ONLY adventure.nodes[].choices[].next.
  * Editing amber branches changes ONLY adventure.nodes[].choices[].missingNext.
  * The required item remains adventure.nodes[].choices[].requires.
  * The .sbgm remains the single source for gameplay logic. .vsgm only saves
    canvas view/layout state. No new JSON schema, no exporter/runtime change.
  * Existing .sbgm/.vsgm files remain compatible. main.c untouched.

VERIFY
  1. Open Forest -> Visual Nodes -> Show Conversation Flow for Future Kim.
  2. On her 'Can I get past?' answer, purple and amber outputs should be
     distinct. Hover both to read their explanations.
  3. Change the amber destination to another existing dialogue using
     'No item ->', or drag the amber socket to its input square.
  4. Check the normal purple destination is unchanged.
  5. Ctrl+Z and Ctrl+Y to test Undo/Redo before saving.
  6. Save Graph + World, reopen Adventure Editor and verify the 'If missing
     required item' dropdown matches. Test both inventory paths in game.

TESTING
  Source-contract and representative Adventure schema tests pass; the
  actual Qt desktop build, drag/drop UI and SIDBOX runtime need user testing.

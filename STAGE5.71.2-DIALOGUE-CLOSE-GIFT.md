# Stage 5.71.2.241026: Dialogue-close rewards + clearer NPC action selectors

## What was wrong

- A terminal dialogue (no answer text) could run on-close **Hide/Show/Toggle NPC** actions, but **NPC gives** was attached to successful selectable dialogue answers. Closing Future Kim's fourth+ feather response therefore hid her without giving the promised inventory reward.
- For answerless nodes, Stage 5.71.1 moved the legacy action on an **empty choice** to the **When this dialogue closes** fields. The original empty-choice selector then reset to "No NPC change," looking like a lost selection. It was relocated, not discarded.
- `Guardian[0]` is an ordinary sprite display name. The project stores its stable UUID as the NPC target, and literal square brackets do not change how the engine resolves it. This was not an array indexing bug.

## Changes

**Editor:** Dialogue Node > **When this dialogue closes (no answers)** now includes **Give item when dialogue closes**. Select a named inventory item or `No item`.

- Closing the final dialogue awards **one item**, then runs the existing two NPC visibility actions, with no selectable answer required.
- A closing reward is granted **once per dialogue node per world**, including after transitions away and back. No TFCard access is added.
- The editor and generator migrate old `NPC gives` values placed on empty answer slots. Opening the node preselects the gift in the new on-close control. The generator also accepts old unedited world JSON, even if the editor was never opened.
- Choice-only NPC and inventory controls are disabled when their answer field is blank. This explains where the real control lives instead of accepting a choice that cannot fire.
- Existing answer-choice gifts and existing visible NPC target selectors continue to work as before. Unchanged generated structures retain their original ABI.

**Runtime:** Adds a compact optional terminal-dialogue reward table, one 32-byte claimed-gift bitset per loaded world, and world-transition save/restore support. If an inventory item is at its maximum capacity, the reward is not granted and remains unclaimed. Avoid configuring the NPC to disappear irreversibly while the player's inventory for that item is already full.

**No new per-frame game work**, no extra TFCard access, no change to MP3/mixer, no change to handwritten `main.c`.

## Configure Future Kim

1. Open **Adventure Editor > Dialogues & Choices** and locate the final **"NOT THE FEATHER AGAIN!!!"** terminal response.
2. Scroll below the three choice panels to **When this dialogue closes (no answers)**.
3. Set **Give item when dialogue closes** to `Dildo`.
4. Set **On close action 1** to `Guardian[0]` > `Hide NPC` (or whichever placed NPC sprite represents Future Kim).
5. Save the dialogue and Adventure Editor, then use **Update Game Project** to regenerate `gameadventure.c` and `gameadventureruntime.c/.h`, and rebuild the SIDBOX game.
6. Offer the feather until the fourth+ dialogue and close it. Confirm the inventory count increased by one and Future Kim vanished. Leave the world and return to confirm the gift is not duplicated and the NPC stays hidden.

`Guardian[0]` is a name only, and is matched by underlying sprite ID. If the old `NPC action 1` on a **blank answer** now reads "No NPC change," check the dedicated **On close action 1** control immediately below the choices. That's the control which actually runs when the dialogue closes.

## Verification

- Native GCC `-std=c11 -Wall -Wextra -Werror` runtime test: grant on terminal close; immediate Hide NPC; no duplicate reward after repeat; one-time claimed bitset survives world transition; a fresh session resets it. PASS.
- Stage 5.71.1 terminal-dialogue NPC close + original per-choice hide/show tests. PASS.
- Stage 5.71 NPC visibility tests, Stage 5.69 repeated wrong-item tests, Stage 5.70.1 high-value event ID tests, Stage 5.70 dialogue-tree picker source checks. PASS.
- Qt6 IDE compilation and real SIDBOX hardware verification: **not performed here**.

Splash screen: **Build: 5.71.2.241026**.

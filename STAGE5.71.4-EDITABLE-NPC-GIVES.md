# Stage 5.71.4.241026 — NPC gives dropdown hotfix

## Problem

Stage 5.71.3 restored **NPC action 1/2** Hide/Show/Toggle controls on answerless dialogues, but it still called `f.give->setEnabled(hasAnswer)` for the **NPC gives** dropdown in each blank Choice panel. The final Future Kim feather response has no selectable answers, so the control stayed greyed out and the user couldn't select an inventory gift from that familiar field.

The underlying Stage 5.71.2 runtime already supports a **one-time gift when a final dialogue closes**, using the node-level `closeGiveItem` property. Its dedicated **Give item when dialogue closes** selector was available above the Choices, but the original dropdown was disabled and disconnected.

## What this hotfix changes

- On a node with **no answers in any of the three Choice slots**, every **NPC gives** dropdown is enabled and acts as a live alias for **Give item when dialogue closes**.
- Changing a choice's **NPC gives** immediately updates the on-close selector and the other two choice dropdowns. Changing the on-close selector updates all three choice dropdowns.
- Mirrors use `QSignalBlocker` and a recursion guard; they do **not** create duplicate rewards.
- On dialogue nodes with actual answers, **NPC gives** retains the previous per-choice semantics: it is enabled only on a choice with a nonblank Answer, and the on-close gift is not mirrored.
- On saving an answerless dialogue, the gift is stored **only** in `closeGiveItem`. The three unreachable empty-choice `give` fields are set to `-1`, preventing duplicate or resurrected gifts.
- `NPC action 1/2` mirrors, Hide/Show/Toggle, dialogue folder-tree selectors, sprite IDs such as literal `Guardian[0]`, and all runtime/helper files stay unchanged.
- Splash: `Build: 5.71.4.241026`.

## Test with Future Kim

1. Open Adventure Editor → Dialogues & Choices → Future Kim's **fourth+ feather** response (the final node **without answers**).
2. Under **When this dialogue closes (no answers)**, pick **Give item when dialogue closes → Dildo**. Alternatively, scroll to the familiar **NPC gives** dropdown in any blank Choice and pick the item there. Both ways select the same setting.
3. Set **On close action 1 → Guardian[0] → Hide NPC**.
4. Save and reopen the dialogue. Confirm that **NPC gives**, **Give item when dialogue closes** and **Hide NPC** remain selected.
5. Save the Adventure Editor, **Update Game Project**, and rebuild SIDBOX. Future Kim should hand over the gift once and vanish when you close her dialogue, and stay gone after world transitions.

**Note:** The item is granted at the moment the terminal dialogue closes, not when the last line first appears. A reused final dialogue or a transition that bypasses dialogue close won't issue the gift.

## Testing / limitations

- Targeted editor-source signal/mirroring/serialization checks: PASS.
- Previous Stage 5.71.3 NPC action mirroring regression: PASS.
- Native GCC runtime tests for terminal-close gifts, one-time grants, NPC visibility, world progress, repeated wrong items, event ID 33000+, and dialogue chooser: PASS.
- **No Qt6 development libraries are installed in this environment**, so the Qt GUI was not compiled or interactively tested here. The user's Fedora build and actual SIDBOX hardware test remain necessary.

This is an **IDE-only hotfix** over Stage 5.71.3. No generated runtime changes and no alterations to user-owned `main.c` are required. Re-export only to apply new gift selections to the game.

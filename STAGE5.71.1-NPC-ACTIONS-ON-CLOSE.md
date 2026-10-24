# Stage 5.71.1.241026: NPC action layout and dialogue-close fix

## What went wrong

Stage 5.71 accidentally placed "NPC action 1" and "NPC item exchange" into the same QGridLayout row (row 9) in each dialogue choice. The widgets overlapped; NPC action 2 was in row 10. Those are now three separate rows: exchange row 9, NPC action 1 row 10, NPC action 2 row 11.

A separate functional problem affected **terminal dialogue nodes with no selectable answers**. Earlier example: Big Steve's last line, "I hope so! I just need to find them! See ya!", had no choices. NPC actions in Stage 5.71 execute ONLY on a successfully selected answer, so adding "NPC action 2 -> BigSteve -> Hide NPC" to a blank answer slot could never fire when closing that final line. The action itself and target were valid.

## Editor changes

The Dialogue Node editor has a new **When this dialogue closes (no answers)** section underneath the ordinary choice editors. It has two optional independent NPC actions (Hide/Show/Toggle) and the existing NPC selector. When the player finishes reading an answerless node and presses FIRE2, both configured actions run. Ordinary successful choices still use their own NPC action fields, which are now below the exchange row and no longer overlap.

**Automatic compatibility:** When opening an existing answerless dialogue with NPC actions accidentally configured on blank answer slots, the on-close controls initially display those old settings. Pressing OK migrates them to the new on-close properties and retires the unreachable blank-answer action. In addition, **Update Game Project** automatically recognises these legacy settings even if that dialogue has not been reopened in the IDE. Existing .sbgm data is preserved and old projects remain loadable.

A configured on-close action has effect only if the dialogue currently has no visible answers. This is intentionally distinct from per-choice actions. Deleting an Adventure NPC clears references from both kinds of actions.

## Runtime changes

There is no extra per-frame work. Stage 5.71 already generates a compact NPC action table; this patch reuses it, with non-overlapping IDs:

- Choice action: `node_id * 3 + choice_index`.
- Terminal node close: `node_count * 3 + node_id`.

The shared runner applies either kind of action immediately when the corresponding interaction succeeds. The 256-NPC visibility byte array, existing world-transition in-memory persistence, NPC draw/talk guards, and six-field NPC ABI are retained. No Game Object, inventory, audio or handwritten main.c changes.

## Big Steve setup

1. In **Adventure Editor → Dialogues & Choices**, open Big Steve's final **"See ya!"** dialogue node.
2. Scroll past the three choice panels to **When this dialogue closes (no answers)**.
3. Select `BigSteve` and `Hide NPC` under on-close action 1 or 2. If it was already set in a blank answer, the new controls should prepopulate from the old setting.
4. Save; use **Update Game Project**; rebuild SIDBOX game. Big Steve should vanish **immediately after the player closes the final dialogue**. No world reload is needed.
5. If his sprite remains but the conversation no longer opens, check for a duplicate copy drawn separately by custom main.c or a Game Object.

## Verification

- GCC host runtime compiled with `-std=c11 -Wall -Wextra -Werror` and passed Stage 5.71.1 tests for initial visibility, hide/show, world restore, **only the second choice action**, and **the no-answer close action**.
- Previous Stage 5.69 repeated wrong-item (feather) tests passed.
- Stage 5.70.1 high-ID Game Object reveal tests passed.
- Stage 5.70 folder-tree picker and Stage 5.71 NPC visibility regression source checks passed.
- The Qt6 GUI build and real SIDBOX hardware run remain untested in this environment.

Splash label: **Build: 5.71.1.241026**.

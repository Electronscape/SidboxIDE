# Stage 5.71.3.241026: Editable NPC actions hotfix

## What broke

Stage 5.71.2 disabled the **NPC action 1 / NPC action 2** target and Hide/Show/Toggle dropdowns whenever a dialogue choice's **Answer** was blank. That includes terminal dialogues such as Future Kim's final feather response and Big Steve's final goodbye. Although the new dedicated **When this dialogue closes** actions worked at runtime, their original in-choice controls were greyed out, making the editor look broken.

## Changes

- The **NPC action 1** and **NPC action 2** target and Hide/Show/Toggle dropdowns are now **always editable**, even on blank answers.
- When **all three answers are blank**, these old familiar dropdowns are **live aliases** of the real **When this dialogue closes** NPC actions. Change either a blank choice's dropdown or the dedicated on-close dropdown and all the other copies immediately reflect it. They save to the existing node-level `closeNpcAction1/2SpriteId` and `Mode` properties.
- The **When this dialogue closes (no answers)** controls are moved **above the choice panels**, together with **Give item when dialogue closes**. This avoids scrolling past unused Choice 1–3 panels to configure a final speech.
- On dialogues with one or more written answers, each choice retains independent NPC action settings as before. Blank choice actions are editable for later use when an answer is entered, but do not execute until then.
- Saving an answerless dialogue always removes old hidden/unreachable action references from its empty choices, including after setting the new on-close target to **No NPC change**. This prevents old settings from being silently re-imported on reopen.
- Empty-choice **NPC gives** and GIVE-exchange actions remain disabled because those **cannot execute** without an answer. Set gifts in the prominent **Give item when dialogue closes** control instead.
- Saved dialogue IDs, sprite names (including literal `Guardian[0]`), NPC IDs, the runtime ABI, and generated game output formats are unchanged. No runtime code needs patching from 5.71.2.

## Future Kim example

1. Open **Adventure Editor → Dialogues & Choices** and open the final **NOT THE FEATHER AGAIN!** dialogue.
2. Near the top, under **When this dialogue closes**, choose **Give item when dialogue closes → Dildo**.
3. Set **On close action 1 → Guardian[0] → Hide NPC**. You can also edit **NPC action 1** on any blank choice; all mirror the same on-close setting.
4. Save the dialogue, save the Adventure Editor. Reopen the node and confirm Hide NPC and the gift remain selected.
5. Use **Update Game Project** and rebuild the SIDBOX game **only if you changed the actual dialogue settings**. The IDE UI hotfix itself doesn't require a game runtime rebuild.

## Verification

- New Stage 5.71.3 source regression checks: enabled NPC controls, two-way mirroring, recursion suppression, data migration and on-close layout placement: PASS.
- Existing Stage 5.71.2 native C reward + hide + world transition tests: PASS.
- Existing Stage 5.71.1 terminal-close, Stage 5.71 NPC visibility, Stage 5.70.1 event-ID, Stage 5.69 feather repeat and Stage 5.70 dialogue-tree tests: PASS.
- Qt6 GUI compilation and real SIDBOX test: not available in this environment. Confirm combo interactivity on your Fedora build.

**Build:** `5.71.3.241026`.

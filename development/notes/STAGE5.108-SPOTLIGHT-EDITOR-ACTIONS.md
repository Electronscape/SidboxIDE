# CoderGirl Stage 5.108.251026: Palette picker, light preview, Trigger/NPC spotlight actions

Based on Stage 5.107, preserving 5.107 palette/title handoff and 5.106 hardware spotlight.

## Designer / Player Start

- **Reserved mask palette ID → Pick from palette...** opens the selected world's **active foreground** .pal as a 16 x 16 colour grid. Hover a cell for its exact index/colour; yellow outline marks reserved index. Entry 0 is unavailable because it is transparent. Click another swatch to change the **index**, not the author's palette bytes. The current palette colour at that index is shown separately from the **Mask colour** (the runtime replacement colour).
- **Live spotlight placement preview** on the right displays the real shared-player Idle PPB frame, if installed, with the player-origin marker (yellow), spotlight centre (purple), radius (purple circle) and feather extent (dashed circle). Updating Anchor/Offset X/Offset Y/Radius/Feather updates the preview. The preview is a positioning aid, not a simulated game frame or hardware dither pattern.
- Existing 0-255 range and colour settings are preserved; no changes to .pal or PPB files.

## Trigger game-object Linked Actions

In **Game Object → Linked Actions → + Add Linked Action**, select **Player Spotlight (world lighting)** as the target, then **Enable**, **Disable** or **Toggle**. This can appear anywhere in the same ordered list as object actions. Both ordinary touch/FIRE2 and item-interaction success paths run the list. Trigger music/dialogue follows the existing action sequence.

## NPC dialogue actions

Adventure Editor → Dialogues & Choices → Edit Node:

- In each **Choice**, set **Player Spotlight → No change / Switch ON / Switch OFF / Toggle**. This fires only on a successful selected choice, including NPC inventory requirements.
- Under **When this dialogue closes (no answers)**, choose **Player Spotlight on close** for a terminal NPC speech. This fires when the player closes the final message, not merely when it appears.
- Text-only **Single Message / Message Sequence** Triggers suppress NPC/gameplay actions on purpose; use Full Conversation to apply a dialogue choice action.

## Runtime and persistence

`gameworlds_spotlight_action(uint8_t mode)` uses `0=off`, `1=on`, `2=toggle`. It restores the foreground CLUT when switching while idle. Overrides survive leaving and revisiting a world during one game session; `gameworlds_shutdown()` resets them for a fresh game. The action changes only the existing spotlight enabled state, not radius, position, palette ID, HUD or renderer algorithm. No code is added to the normal per-frame game loop.

**No handwritten main.c edits.** The original three 5.105 calls stay unchanged. Update Game Project is required to regenerate `gameworlds.c/.h`, `gameadventure.c`, `adventureruntime.c/.h`, and `gameworlditems.c`. Verify regenerated `maingame.c.txt` if integrating any older game manually, but do not replace user-owned main.c.

## Tests

Native GCC tests PASS: 5.108 NPC choice/on-close action, 5.108 cross-world spotlight toggles and palette restore, 5.107 mask/title/CLUT, 5.106 scaled sprite anchor, 5.103 Trigger list action order, 5.97 Trigger narration/wrong items, 5.98 thought-bubble, 5.99.2 reply fonts, and 5.48 transitions.

Qt6 development libraries are not available in this runner, so desktop compilation and on-device acceptance remain for the user.

# GamerGirl Stage 4.32 — Dialogue Layout and NPC Editor Refinements

**Based on the fixed Stage 4.31a source.** First-pass testing version: host C/runtime and source integration checks passed. Qt6 compilation and real SIDBOX hardware acceptance **not** run in this container.

## Installation

1. BACK UP your current IDE source and your working platformer project.
2. Apply the changed-files ZIP over the IDE root (preserve the directory tree) or use the complete source archive.
3. Rebuild GamerGirl on Fedora.
4. Open your existing Advanced Platformer Game Designer. Adventure Editor → **Dialogue Position** is the new placement tab. Select a placement preset, drag the yellow dialogue rectangle on the 480×320 preview, and optionally adjust X/Y/Width/Height.
5. Save the design and select **Update Game Project**. The generated `gamehelpers/gameadventure.c` will call the new `game_adventure_dialogue_box()` API and the latest `adventureruntime.c/.h` must be copied into the game project.
6. Rebuild and run on SIDBOX. The hand-edited `main.c` is intentionally protected; if it already contains `gameadventure_setup()`, `game_adventure_draw()` and `game_adventure_draw_npcs()`, **no new manual C calls are needed**.

## Changes

- New draggable dialogue placement preview with top/bottom/left/right presets, plus pixel X/Y and Width/Height. Runtime clamps boxes to the real 480×320 LCD. Old designs retain the Stage 4.31 default (20,148,440,162).
- Dialogue choices now use a multiline editor, storing up to 180 characters each. The C runtime wraps choice labels at **8 pixels per character** and uses available box height; if the list won't fit, the active choice stays visible. Up to 8 rows per choice can render if the window is tall enough.
- Player speech is now multiline (150 characters in data) and its speech bubble adjusts to its text, up to 5 wrapped lines.
- Adventure Editor starts larger, as does Dialogue Node editor; the NPC Animation Designer starts much larger and lays out a thumbnail-frame timeline next to its live preview and delay controls. Same existing Idle/Talking frame data.
- The Dialogue Box Atlas 3×3 part selectors now place X/Y flip checkboxes beside each part instead of below it, and text / outline colour pickers share a row.
- **Delete NPC** asks for confirmation and explains that it only removes the NPC registration, not the placed sprite or dialogue nodes.
- No changes to platformer physics, inventory actions, SPC playback or SIDBOX firmware.

## Known constraints

- The dialogue window is **shared by all NPCs** within the current Adventure design; this version does not provide unique box positions per NPC or per node.
- Small dialogue boxes cannot display unlimited text; use a wider and/or taller box for longer answers. The active answer is prioritised when choices overflow. Main NPC dialogue remains limited to 1–3 displayed lines, depending on box height.
- The player-speech bubble placement still follows the player, independently of the configurable NPC dialogue box.
- Fedora Qt6 compilation and hardware playback must be verified by you.

## Test results

- Host-side `test_stage432_dialogue_layout.py` (compiles runtime as ISO C11): passed custom layout, wrapped long choices, reply bubble and screen clamping.
- Host-side Stage 4.29, 4.30 and 4.31 adventure runtime tests: passed.
- Targeted source integration checks, including Stage 4.31 generator/music/physics and Stage 4.32 UI/codegen checks: passed.
- Qt6 headers not installed in the test environment; no local Qt compile claimed.

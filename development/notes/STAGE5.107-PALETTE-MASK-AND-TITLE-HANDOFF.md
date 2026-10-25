# CoderGirl Stage 5.107.251026: Reserved spotlight mask colour and title palette handoff

## What changes

The **Player Start > Local darkness / spotlight** settings now include:

- **Reserved mask palette ID** (1 through 255, default 255). This is a **foreground** palette index. Index zero is excluded because it is transparent.
- **Mask colour** (default `#000000`). Choose a colour using the standard colour picker.

The spotlight and circle wipe use this fixed CLUT slot, with the configured colour, **without rewriting the authored palette assets**. The generated world manager keeps the slot stable when restoring a CLUT, fading in/out and swapping worlds. Worlds without local darkness still use the legacy temporary index-255 wipe.

Stage 5.106 incorrectly allowed the fading palette to overwrite the spotlight's black entry. As a result a title/game transition could show a tinted dark overlay. Stage 5.107 makes the mask colour constant during fades. It also clears **both** title-screen foreground buffers on exit; formerly the title cleared only one, leaving old title pixels visible while world colours were loaded.

## IMPORTANT: Reserve the index in your artwork

The slot is overwritten in the **temporary runtime CLUT**, not the original palette asset. If your tiles, sprites, GUI or other foreground artwork use that index, those pixels will also take on your chosen mask colour while the spotlight is enabled. Choose a slot unused by normal foreground graphics. For consistent results across your game's worlds, use the same reserved index and colour everywhere. Foreground index 0 remains untouched.

The effect is still a black/coloured aperture overlay with a 4x4 feather pattern, not full per-pixel lighting. It uses the existing draw routine. Real STM32 performance after this change is unverified.

## Install/test

1. Back up the project, then apply the Stage 5.107 drop-in to Stage 5.106 IDE source.
2. Rebuild the IDE. Open your world, **Player Start**, enable the spotlight, and choose the mask ID and colour.
3. Save, then **Update Game Project**, then compile the game.
4. Existing `main.c` spotlight calls are unchanged. **Do not overwrite handwritten `main.c`.**
5. Test title -> game with Fade IN; test a world transition; compare with mask on/off, and confirm important artwork is not using the reserved index.

## Verification

- Native GCC 5.107 test: stable reserved slot across title handoff, Fade IN, world switches, original CLUT untouched: PASS.
- Existing Stage 5.106 anchor/offset native test: PASS.
- Stage 5.48 and 5.46 transition native tests: PASS.
- Stage 5.100 BOB alpha native test: PASS.
- Qt6 desktop build: NOT performed in this environment (Qt6 not installed).
- Real SIDBOX: requires user hardware test.

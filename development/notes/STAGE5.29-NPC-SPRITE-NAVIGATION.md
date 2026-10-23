# CoderGirl Stage 5.29: NPC and Game Object navigation

Based on Stage 5.28; splash: `Build: 5.29.221026`.

## New World Designer shortcuts

- Sprite resources used as Adventure NPCs show **[NPC]** after the name.
  This is derived from the world `.sbgm` Adventure `npcs[]` list via the
  persistent `spriteId`, so renamed sprites retain their tag.
- Double-click an NPC-tagged entry under **Sprites** to open **Adventure Editor**
  already on its **NPCs** tab, with the corresponding NPC table row selected.
- Hold **Shift** and double-click a sprite that has a Game Object type to
  expand **Game Objects**, select the corresponding entry, and centre/select
  that sprite on the world canvas via the existing tree-selection handler.
- Plain double-click on non-NPC, non-Game-Object sprites keeps its existing
  centre-on-canvas behaviour; plain double-click on a Game Object alias keeps
  opening its Game Object properties.
- Adding/removing an NPC inside Adventure Editor refreshes tree labels as soon
  as the editor is accepted. Editing the sprite name doesn't strip the NPC tag.

Neither navigation shortcut changes a world object, nor does it require new
runtime code or updating the game project. The existing `main.c` is untouched.

## Installation

Extract changed files into your Stage 5.28 IDE source tree with paths intact;
rebuild the IDE. Or apply the patch to an unmodified Stage 5.28 checkout.

## Test checklist in Qt6 IDE

1. Open Adventure Editor, assign an ordinary Sprite as an NPC, click OK.
2. Confirm the Sprites tree displays `[NPC]` for the sprite immediately.
3. Double-click it, and confirm Adventure Editor opens at **NPCs**, with that
   particular row highlighted, even if several NPCs exist.
4. Rename the sprite and repeat to verify that the stable ID is used.
5. Remove that NPC and confirm its `[NPC]` tag disappears after OK.
6. Shift+double-click a configured Game Object sprite under Sprites. Verify
   the Game Objects category expands and the matching alias is selected.
7. Confirm normal double-click on a non-NPC sprite still centres it in canvas.

## Verification

The Stage 5.29 source integration regression and existing Stage 5.15,
5.25, and 5.27 Adventure regressions pass in the host environment.
The full Qt6 application cannot be compiled here because Qt6 >=6.5 headers
and CMake configuration files are unavailable. Test the actual UI after
building on your Fedora machine.

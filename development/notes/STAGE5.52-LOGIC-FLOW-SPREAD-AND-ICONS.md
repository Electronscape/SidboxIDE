# Stage 5.52.231026 — Logic Flow: Spread Left to Right and 16×16 Icons

This release updates the **design-time-only** Logic Flow editor. No generated game code, TFCard PPBs, `.sbgm` files, world resources or SIDBOX firmware are changed.

## New toolbar action

**Spread Left to Right** sits next to the original **Clean Layout** button.

- **Clean Layout** retains Stage 5.51's original six-column arrangement and clears saved manual card positions.
- **Spread Left to Right** groups connected logic into independent vertical chains and distributes the steps of each chain horizontally using the actual directed links. NPC dialogue, choices, actions and other connected gameplay nodes can progress across the canvas rather than sharing one dense column.
- World-to-world connections remain visible, but do not influence either world's local card positions.
- Cycles are handled with bounded breadth-first traversal instead of endlessly increasing the layout depth.
- Both actions replace the saved card arrangement. You can still drag any card to adjust it afterwards, and those positions remain saved in the same `.sidbox-flow-layout.json` file.
- Spread restores a readable 90% zoom (particularly useful after Fit Graph), and centres on the chosen world's World card.

## Card icons

Small, self-contained 16×16 pictograms now appear on the top line of the cards. Icons distinguish worlds, player starts, NPCs, dialogue, choices, inventory/collectables, statistics, paths, doors, exits, breakables and broken references. Unrecognised kinds get a neutral object icon.

They are drawn directly with Qt; **no additional PNGs, assets, or resource packs** are required. The sharp-corner card design is retained.

## Other layout change

World background bands are sized from the card bounds after arranging, including for horizontally spread or previously saved positions. The edge-routing behaviour from Stage 5.51.1 is preserved, including connector anchors and arrows that follow moved cards.

## Changed source files

- `gamefloweditor.cpp`: connected-chain layout, new button and shortcuts, vector-drawn 16×16 icons, scene-band sizing.
- `splashscreenwidget.cpp`: splash version `Build: 5.52.231026`.
- `README.md`, this note.

## Testing and integration

- Source checks passed for the toolbar wiring, icon dimensions, saved positions and cleanup connections.
- The layout was exercised against the supplied GameTest3 design data (2 worlds, 60 cards, 40 links), plus a cycle-safety smoke test.
- A complete **Qt6 IDE compile has not been performed** here because Qt6 development libraries are not installed in this container. The first full build/interactive verification is on Fedora.
- No **Update Game Project** operation is required for this design-only editor change.

**Install:** extract the drop-in archive into the Stage 5.51.1 IDE source directory, overwriting files, then rebuild the IDE.

# SIDBOX / CoderGirl Stage 5.56.231026

## Scope
Only **gamefloweditor.cpp**, the splash version, documentation, and an IDE-only regression test changed. No firmware, runtime, PPB, HUD, world `.sbgm` files, or generated game C changed.

## Fixes

1. **F2 rename:** select a *manual* Logic Flow group, or one of its mini-cards, then press F2. The existing group title becomes editable in place. Enter saves to `.sidbox-flow-layout.json`; Escape cancels. Double-clicking the title also works more reliably because its first mouse press is explicitly accepted. Automatic array-group names remain derived from resources.
2. **Immediate world-background sizing:** backplane rectangles are recomputed from the current top-level card/group geometry during dragging, on drop, and after rebuilding/filtering the graph. Headers follow the resized background and the viewport is explicitly refreshed; updating the scrollable scene area is deferred until drop/redraw for drag performance. Switching the selected world recentres on its visible background.
3. **Real PPB thumbnails:** a 16×16 image appears at the bottom-right of regular cards and expanded group mini-cards when their actual source art is available. The preview comes from the original indexed PPB, using the saved sprite frame, cell dimensions, Sprite Stamp arrangement and per-cell flips. Inventory items use their explicit PPB and 2×2 artwork when configured; an older item can fall back to its associated collectable. NPC cards use their linked sprite's artwork. Missing PPBs simply produce no thumbnail.
4. **No artwork generation or palette-index conversion:** PPBs are decoded strictly for a preview. Index 0 is transparent in the temporary display CLUT; indexes 1–255 retain their colours and numerical IDs. No extra PPBs are made.

The existing red-to-green gradient arrows, clickable lines, saved positions, movable manual mini-graphs, automatic array groups, grouping shortcuts, and 8-pixel snap remain unchanged.

## Checks

- `python3 development/tests/test_stage556_flow_navigation.py` passes source-level checks.
- The GameTest3 design and asset archive was inspected: nine valid existing PPBs, 28 resolvable game-object artwork references, eight stamp-backed objects, and four explicit inventory-atlas references.
- **Qt6 development headers are unavailable here**; no full Qt build or interactive Fedora GUI test has been performed. Build and interaction still require user verification.

## Install / acceptance

1. Apply **Stage 5.56 drop-in over Stage 5.55** and rebuild the IDE.
2. Open Logic Flow; select a manual group and press F2, rename and press Enter. Reopen to verify persistence. Test double-click on the name too.
3. Move groups beyond their current world background, including left/up. The background should follow *without* zooming. Switch World1 / Forest and verify the current background displays immediately.
4. Inspect sprite, NPC, collectable, and inventory cards. Where saved art resolves to a project PPB, the right-bottom artwork should match the assigned frame or stamp, not the atlas's top-left tile.
5. Test arrays, mini-card movement, link clicks and 8px snapping for regressions.

No **Update Game Project** required.

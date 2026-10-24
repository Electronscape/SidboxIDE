# Stage 5.59.231026 — Title Screen Designer, Pass 2

This is an **IDE design-time update** built on Stage 5.58. The existing game runtime, world files, PPBs, CLUTs and code generation are unchanged.

## Editor changes

- **Enable project title screen** remains available.
- Game Title and Subtitle can each be **text or an existing PPB graphic**.
- Every visible element has editable X/Y coordinates and can be dragged on an actual **480 × 320** Qt graphics preview.
- PPB selection supports an entire image or a cell from an **8×8, 16×16 or 32×32 grid** with a cell index. Graphics are decoded with the existing `SidboxPpb::read` function. No new PPB files, palette reordering or recolouring.
- **Title music** selects a file from the project `music/` or `audio/` tree. Existing project-relative paths remain saved.
- Designer Notes are retained.
- **Menu Items** now use an editable four-column table: Option Name | Action | Destination World | Player Start. Option Name is directly editable; Action/World/Start are dropdowns.
- The Player Start dropdown is refreshed from the selected world's saved `.sbgm` **Default** and `playerStarts` entries. It shows names while saving stable IDs, matching the existing world-transition system.
- Each menu item also supports Text/PPB artwork and placement via the element selector in the properties panel.
- Add, Remove, Up, Down preserve menu order.
- Default menu: Start Game / Start / blank world / Default; Load Game / Load / null / null; Options / Options / null / null; Quit / Quit / null / null.
- A future **Load Game** runtime can use ten fixed slots. `saveSlots: 10` is recorded as design intent, not implemented game persistence.

## File format

The existing project-root `.sidbox-title-screen.json` remains compatible with Stage 5.58. The new version `2` adds `titleArt`, `subtitleArt`, and an optional `display` object for each `menuItems` entry. The older fields `title`, `subtitle`, `music`, `notes`, `enabled`, `label`, `action`, `world`, and `playerStart` remain.

Artwork entries store mode (`text`/`ppb`), project-relative PPB path, `cellSize`, `frame`, `x`, and `y`. Menu actions that do not use a destination write JSON `null` for both `world` and `playerStart`.

## Install and test

1. Apply the Stage 5.59 drop-in over Stage 5.58 and rebuild the IDE.
2. Open Game Designer → Title Screen. Ensure the window maximizes and the central preview shows a 480×320 black display area.
3. Choose title/subtitle Text or PPB, drag each on the preview, and verify X/Y updates. Repeat with a menu item.
4. Pick `audio/music1.spc` (in GameTest3), set a Goto World row to Forest and pick its named `Door 1 start`.
5. Save, close, reopen and confirm menu edits, PPB paths, positions, music and player-start ID persist.
6. Verify the game still launches normally; this stage does **not yet** create SIDBOX title-screen UI, a Save/Load implementation, or 10 physical save files.

## Source / verification

Changed `gametitlescreeneditor.cpp` and `splashscreenwidget.cpp`. Full Qt6 compilation is unavailable in this environment; the project data and saved field handling were inspected, but the window needs a real Fedora GUI test.

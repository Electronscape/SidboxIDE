# GamerGirl Stage 4.13 — GUI polish, optional icon overrides and preview backgrounds

Base: Stage 4.12 IDE source archive.

## Changes

1. Tilemap front-render F markers (main map and stamp editor): smaller black
   outline (1.6 px, or 1 px in small cells), DemiBold rather than Black fill.
   World Editor Object names are UNCHANGED (remain thick, bright, black-edged).
2. Game Object Properties: previous arrow, compact name, next arrow now stay
   TOGETHER at the start of the title row. Extra whitespace is placed after >.
   Long names use a tooltip and a max width of 285px.
3. Optional icons/ PNG overrides. The IDE looks beside its executable first,
   then ../icons, ../../icons, ./icons and ./SidboxIDE/icons. Missing files
   preserve original resource icons and theme-aware custom glyphs.
   Artwork is loaded when the relevant UI is created; restart the IDE after
   replacing toolbar icons. Users can make their own outlined PNGs.
4. Themed checkboxes now have a visible outlined white tick on the accent
   square, in the shared Game Editor UI, Player Animation Editor, Game Object
   Properties and main IDE controls. Square corners retained.
5. Player Animation Editor Live Preview has Palette 0 / Theme / Custom
   background modes and a Colour... picker, with QSettings persistence.
   PPB palette entry 0 is sampled BEFORE making sprite index 0 transparent.
   Indexed PNGs also supply palette 0. Truecolour sources without index 0
   fall back to the selected theme background. The choice only affects the
   visual preview, not image assets, saved animation or generated gameplay.

## Replaceable icon filenames

Place custom PNGs in icons/ adjacent to the IDE executable (or one of the
other searched folders). No PNG needs to be added unless you want to override
its built-in appearance. Existing icons/ file names also work for resource
icons: e.g. compile.png, open_project.png, save_project.png,
new_project.png, toolbar_gamedesigner.png, tree_file_c.png,
close_tab.png, gr_icon_object.png, gadget_button.png etc.

Game Object navigation (16x16):
- game_object_previous.png
- game_object_next.png

Tilemap 24x24 icons:
- tilemap_flags_apply.png / tilemap_flags_keep.png
- tilemap_cell_flip_x.png / tilemap_cell_flip_y.png
- tilemap_stamp_flip_x.png / tilemap_stamp_flip_y.png
- tilemap_draw_front.png / tilemap_stamp_front.png
- tilemap_collision_keep.png / tilemap_collision_empty.png
- tilemap_player_reference.png / tilemap_player_hitbox.png

Tilemap Tile Atlas 16x16 icons:
- tilemap_graphic_keep.png
- tilemap_graphic_empty.png
- tilemap_graphic_atlas.png

Other:
- checkbox_tick.png (16x16; black-keylined white tick, provided as fallback)
- animation_state_idle.png / animation_state_walk.png /
  animation_state_run.png / animation_state_jump.png etc. (20x20)

Custom button icons intentionally show the PNG colour without recolouring.
If a custom PNG is missing, the original theme-aware vector glyph is drawn.

## Installation (changed files package)

Copy ALL entries in the changed-files archive into the corresponding paths
in your Stage 4.12 IDE source directory, including new
`gameeditoricons.h`, `icons/checkbox_tick.png`, and `CMakeLists.txt`.
Then rerun CMake configuration (to register the new PNG Qt resource) and build.
The full archive is ready as an alternative.

## Changed files

CMakeLists.txt
main.cpp
mainwindow.cpp
mainwindow_uiicons.cpp
guidesigner.cpp
gamedesigner.cpp
gametilemap.cpp
gameanimationeditor.cpp
gameanimationeditor.h
gameeditorcontrolstyle.h
gameeditoricons.h (new)
icons/checkbox_tick.png (new)
development/tests/test_stage401_shared_control_theme.py (updated test)
development/tests/test_stage412_contrast_and_flag_modes.py (updated test)
development/tests/test_stage413_gui_polish.py (new test)

## Verification

All Stage 4.00–4.13 selected Python source-structure regression checks pass
(15 passes, 0 failures). These are NOT a compiled Qt6 UI test.
Qt6 development headers and libraries are unavailable in this environment;
please compile and inspect on Fedora to confirm the visuals.

No firmware, engine, .sbgm, .map, PPB or .sbanim file changes.

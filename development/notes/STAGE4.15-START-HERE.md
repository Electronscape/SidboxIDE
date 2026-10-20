# GamerGirl / CoderGirl Stage 4.15 — Central Theme Polish

Base: Stage 4.14 full IDE source.

## Fixes

1. **Checked checkboxes disappearing:** The Stage 4.14 generated 16x16
   indicator is now loaded from a native local path (rather than a file:// URL)
   and rendered with the Qt stylesheet `image:` property. The checked state
   has a transparent background and no border that could cover the bitmap.
   The custom icons/checkbox_tick.png artwork still works; a drawn tick remains
   the fallback when no icon can be decoded. Checked disabled boxes also retain
   the indicator. Generated icons are cached in the IDE's user cache.
2. **Smaller sliders:** 4px grooves, 10px handles, square corners. Both
   horizontal and vertical sliders are governed by ideglobaltheme.h.
3. **Alternating tree/list rows:** IDETheme.alternateBackground is now applied
   in the application palette (AlternateBase role) AND the shared stylesheet.
   Views which have alternatingRowColors enabled should show their chosen
   theme colour rather than the KDE default. The custom home-project list
   and stamp list continue using their existing dedicated styles.
4. **Dropdown menus:** The application palette now covers native popup
   list views, and the central stylesheet also targets combo popup containers,
   their lists and selected items. Old duplicated per-dialog popup styling
   has been removed from World Editor / Game Object Properties and Tilemap
   Editor, so late-created controls follow the current IDE theme too.

## Installation

Changed-file replacement paths are all relative to the IDE source root:
- ideglobaltheme.h
- mainwindow.cpp
- gamedesigner.cpp
- gametilemap.cpp
- development/tests/test_stage413_gui_polish.py (updated expectation)
- development/tests/test_stage414_global_theme.py (updated expectation)
- development/tests/test_stage415_global_theme_polish.py (new test)

Extract Stage 4.15 changed files over your Stage 4.14 IDE source, keeping
relative paths intact. Rebuild. No CMake file changes, although reconfiguring
is fine. Alternatively use the complete Stage 4.15 archive.

## Suggested Fedora visual test

- Check both checked/unchecked controls in Options, Tilemap and Animation;
  confirm a visible tick in light and dark IDE themes, including hover.
- Move a slider in Tilemap/Animation and verify the track is slimmer.
- Change the alternate tree background colour in IDE theme options and
  inspect Files in Project and Find/Replace results (alternate rows on).
- Open World Editor > Planes > Foreground + Background and compare the
  popup background, text and selected row to IDE theme; also check Game
  Object Properties, and Tilemap collision-mode combo.

Selected 17 Stage 4.00–4.15 source regression tests pass. The Qt6 SDK is not
available in this build environment, so compilation and visual behaviour on
Fedora/KDE are still unverified here.

No changes to firmware, platformer physics, generated game code, binary map
formats, or .sbgm project contents. The mainwindow.cpp 2048 KB syntax
highlight threshold is preserved.

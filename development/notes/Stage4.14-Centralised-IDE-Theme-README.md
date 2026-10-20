# GamerGirl / CoderGirl Stage 4.14 — Centralised IDE Theme

Base: IDE-GamerGirl-Stage4.13-Full.tar.gz.

## The central theme

`ideglobaltheme.h` is now the single common stylesheet for Qt controls. It
builds colours from the existing `IDETheme` struct (`idetheme.h`).

`MainWindow::applyTheme()` in `mainwindow.cpp` installs that one style with
`qApp->setStyleSheet(ideGlobalControlStyle(m_theme));`. This makes existing
widgets, modeless windows, top-level dialogs, and newly opened dialogs inherit
the current theme. Saving a theme in Options invokes the same application-wide
style update.

For future work: change a shared button, checkbox, combo, slider, scrollbar,
menu, tab, tree, tooltip, etc. in `ideglobaltheme.h`, rather than copying a
stylesheet into each editor. Keep unique art/canvas styles scoped by objectName.
`gameeditorcontrolstyle.h` remains as a compatibility wrapper for existing
integrations and delegates to the global rules.

Removed duplications:
- `MainWindow::setupInterface()` no longer installs the startup hard-coded
  black/blue style on all main-window descendants.
- World Editor and Tilemap Editor no longer reapply a separate control theme.
- Player Animation Editor no longer redefines standard checkboxes and controls.
- Game Object Properties retains only its special named cards, headings and
  object-list layout; its standard controls use the global stylesheet.
- GUI Designer retains only the intentionally grey gadget artwork palette.
- Game Palette Editor inherits shared controls, not palette-dependent local CSS.

## Checkboxes: no more solid checked squares

A checked 16x16 checkbox is now a COMPLETE, rendered indicator — accent colour
and border with a visible tick. It is constructed once per theme/icon identity
and cached under the IDE's normal user cache directory. The global Qt stylesheet
uses the completed image via `border-image`, avoiding Qt stylesheet layering
that could produce a solid checkbox with the tick hidden.

The tick artwork still comes from `icons/checkbox_tick.png` if the user supplies
an override; otherwise the bundled resource icon is used. A simple painted
checkmark is a fallback if the artwork cannot be decoded.

Unchecked boxes remain empty, with square corners. Light and dark IDE themes
use the same rules. The cache is a rendering implementation detail, not a game
asset and not a project file.

## Combo boxes

Normal Qt dropdowns keep their arrows. Only the World/Tilemap custom-painted
combo boxes set `customChevron=true` to hide the native chevron under their
custom drawing, avoiding double-arrow artefacts.

## Changed files

- `ideglobaltheme.h` **NEW — central Qt theme**
- `gameeditorcontrolstyle.h` (compatibility wrapper)
- `mainwindow.cpp` (global theme installation; remove startup style copy)
- `gamedesigner.cpp` (World Editor and object-property styling)
- `gametilemap.cpp` (Tilemap Editor theme; custom combo)
- `gameanimationeditor.cpp` (inherit global control theme)
- `guidesigner.cpp` (retain only special gadget palette styling)
- `gamepaletteeditor.cpp` (inherit global control theme)
- `CMakeLists.txt` (list new header)
- `development/tests/test_stage401_shared_control_theme.py`
- `development/tests/test_stage410_tilemap_flag_toolbar.py`
- `development/tests/test_stage413_gui_polish.py`
- `development/tests/test_stage414_global_theme.py` **NEW**

Install the changed files preserving their paths, or use the full source archive.
Re-run CMake configure, then rebuild the IDE. No firmware, runtime physics,
project export format, `.map`, `.sbgm`, PPB or animation format changes.

## Verification

The 16 selected Stage 4.00–4.14 structural source regression checks pass.
These checks do NOT compile or visually exercise Qt. Qt6 development headers are
not available in this container: please perform the Fedora Qt6 build and check
checkboxes in Options, Player Animation, Tilemap, Game Object Properties,
Palette, and GUI Designer, plus light/dark theme switching.

The existing large source highlighting threshold in `mainwindow.cpp` remains
2048 KB.

# GamerGirl Stage 4.17 — Theme-aware dropdown popups

Base: Stage 4.16. No firmware, collision data, engine, or project-file format changes.

## Changed production files (IDE source root)
- ideglobaltheme.h
- mainwindow.cpp

## Installation
Replace these two files in your current Stage 4.16 IDE source directory, preserving names, then rebuild with your normal Qt6/CMake process. No new Qt modules or icons.

## What changed
- Set the standard QComboBox dropdown to a Qt-managed (rather than native platform-menu) list.
- Central theme manager now directly styles QComboBox popup QListView / QTreeView and its top-level popup frame. This supplies menu background, normal text, alternating-row background, highlighted item background/foreground, and the 10px scrollbar.
- The shared theme is reapplied to existing combobox popups whenever the IDE theme changes.
- A single QApplication event filter themes comboboxes in newly opened dialogs when they are shown. It does not run on each mouse movement or paint.
- Existing view-specific style rules are retained before the central popup rules, avoiding accumulating theme layers.
- Checkbox, scrollbar, tree-row and other Stage 4.16 settings are otherwise unchanged.

## Please test on Fedora / KDE
1. Rebuild Stage 4.17.
2. Open Tilemap Editor and expand the collision brush type dropdown (the one in your screenshot). It should show the IDE's dark/light selected menu background and text, NOT the KDE white list.
3. Check World Editor's Planes combo (foreground/background), Game Object Properties combos, and a newly opened dialog's combo.
4. Change IDE theme with an editor already open, reopen the dropdown, check changed colours.
5. Confirm the 10px vertical scrollbar and 16px checked/unchecked boxes are still correct.

## Verification
19 selected Stage 4.00–4.17 source regression tests passed in this workspace.
Actual Qt6 compilation and KDE popup rendering were not available in this environment; please verify on your Fedora machine.

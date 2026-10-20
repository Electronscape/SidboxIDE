# GamerGirl Stage 4.18 — Compact numeric fields / KDE dropdown theme

Base: Stage 4.17 full IDE source.

## Changed production files (IDE source root)
- `main.cpp`
- `ideglobaltheme.h`

## Installation
Replace these two files in the IDE source directory. Reconfigure CMake if needed, then rebuild normally on Fedora. No new Qt libraries, assets, or firmware changes.

## Changes
1. Numeric steppers (`QSpinBox` and `QDoubleSpinBox`) now use smaller padding and a 16px minimum content height instead of inheriting the bulkier 22px + 4px vertical padding of other text inputs. Their ranges, stepping, arrows, and data values are untouched.
2. Select Qt's cross-platform Fusion QWidget style in `main.cpp`, before the main IDE window is created. This avoids the desktop's KDE-specific native combo/menu painting, while the IDE palette and central stylesheet still define colours and shapes.
3. The central theme manager now gives every `QComboBox` the same local, IDE-coloured popup rules, based on the pre-centralisation version that styled dropdowns at their parent. This is done centrally via the existing theme filter, NOT by adding window-specific stylesheets.
4. Also restyle the popup when the `QComboBoxPrivateContainer` actually shows, to account for popups initialised lazily by Qt.
5. Previous Stage 4.16 checkbox 16px indicators and 10px scrollbars remain unchanged.

## Fedora visual checks requested
1. Open Tilemap Editor. The `Tiles X / Y` QSpinBox fields should be visibly shorter while still working.
2. Open collision type dropdown. Both its closed selector AND its popup should have the selected IDE theme background and text rather than KDE white.
3. Test Game Designer foreground/background plane selectors, Game Object Properties combos, and other dialogs opened later.
4. Switch IDE themes, reopen the dropdown, verify selection and background update.
5. Confirm checked/unchecked boxes, 10px scrollbars, and keyboard/arrow interaction still work.

## Verification
20 Stage 4.00–4.18 source regression tests passed. Qt6 build and Fedora KDE visual rendering cannot be checked in this environment and still require local testing.

No project format, runtime, or firmware changes.

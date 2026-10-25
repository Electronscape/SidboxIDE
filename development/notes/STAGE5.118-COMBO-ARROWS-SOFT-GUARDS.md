# Stage 5.118: visible dropdown chevrons and softer guard indicators

## Root cause

The KDE popup combo filter (`IDEComboPopupThemeFilter::styleCombo`) applies a
local stylesheet to each dropdown. That local sheet overrode Stage 5.117's
app-wide `adventureGuard` enabled/disabled styling. Separately, `::drop-down`
styling suppressed Qt's native chevron in some KDE configurations.

## Changes

- `ideglobaltheme.h`: `ideComboDownArrowImageUrl()` generates a 12x9 themed
  PNG using QPainter and caches it with the existing UI icon cache directory.
  Enabled/disabled arrows use appropriate text tones and are specified in both
  global QSS and per-combo local QSS; `customChevron=true` still hides them.
- `ideglobaltheme.h`: dependency-controlled combos have explicit local enabled
  and disabled selectors to avoid the stylesheet cascade issue.
- `ideglobaltheme.h`: all dependency guard outlines are now thin (1px) and
  use blended green/red hues. Guard background tints also reduced.
- `splashscreenwidget.cpp`: build string Stage 5.118.251026.

No changes to Adventure editor settings, persistence, generated runtime or applet C files.

## Test

`python3 development/tests/test_stage5118_combo_guards.py`
`python3 development/tests/test_stage417_combo_popups.py`

Runtime thought C tests were run under the Stage 5.116 guard test with its
build-version assertion adjusted to 5.118 (historical tests pin older stages).
Qt6 headers are not installed in the preparation environment, so visual Qt
verification is outstanding.

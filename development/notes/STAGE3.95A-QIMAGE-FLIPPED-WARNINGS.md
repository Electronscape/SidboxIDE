# Stage 3.95a — Qt6 QImage::mirrored deprecation warnings

**Baseline:** Full Stage 3.95 source. This is a source-only Qt warning cleanup.

## Why Qt Creator warned

The two Game Object previews in `gamedesigner.cpp` used the deprecated
`QImage::mirrored(bool horizontal, bool vertical)`. Recent Qt6 prefers
`QImage::flipped(Qt::Orientations)`.

## Changes

- Canvas sprite preview: translate the saved `objectFlipX` / `objectFlipY`
  booleans into `Qt::Horizontal` / `Qt::Vertical`, and call `flipped()`.
- Game Object Properties live preview: make the same conversion based on
  Flip X / Flip Y checkboxes.
- No changes to data, export, actual SIDBOX BOB flags, game physics, or
  generated project source.
- Existing source and new test checks can run without Qt6; compiling the Qt6
  IDE and confirming the warnings disappear requires Fedora/Qt Creator.

## Install

Replace only `gamedesigner.cpp` in the IDE source root and rebuild in Qt Creator.
No F5 Update Project required.

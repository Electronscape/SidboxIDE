# Stage 5.61 — Title Screen Designer Font Size X/Y

Date: 2026-10-23

## Summary

Adds separate **Font Size X** and **Font Size Y** controls to the Title Screen
Designer for text-based title, subtitle and menu items. This follows the
SIDBOX-style text draw API direction where X and Y scaling are provided
independently.

## User-visible changes

- Replaces the single `Font size` selector with side-by-side `X` and `Y` size
  selectors in the Selected Element Artwork / Position panel.
- The preview now scales title-screen text independently on each axis.
- Existing Stage 5.60 / 5.60.1 title-screen JSON files still load correctly.
  If only the legacy `fontSize` field is present, both X and Y sizes inherit
  that same value.

## Persistence

Saved `.sidbox-title-screen.json` artwork objects now include:

- `fontSizeX`
- `fontSizeY`

For backward tolerance, the save still also writes `fontSize` using the X value.

## Files changed

- `gametitlescreeneditor.cpp`
- `splashscreenwidget.cpp`
- `README.md`

## Notes

This is still design-time/editor data only. The future runtime title-screen
generator will need to map these values onto the final SIDBOX draw-text API.

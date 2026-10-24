# Stage 5.66.241026: Title Screen Options Designer Pass 2

## UI

From Title Screen Designer, click **Edit Options Screen...**.

- **Elements table:** Show checkbox, fixed option identity, editable label for
  Music, Music Volume, Sound Effects, SFX Volume, Screen Shake, Text Speed,
  Difficulty and Back. Hidden rows are omitted from the designer display and
  generated runtime navigation. Even with Back hidden, FIRE2 returns.
- **Element properties:** title heading and each option label have independent
  foreground CLUT index, Enable outline checkbox and outline CLUT index picker.
  Values are used by both IDE preview and generated SIDBOX C.
- **Independent draggable sliders:** selecting Music Volume Bar, SFX Volume Bar
  or Text Speed Bar in the element picker, or clicking its bar in the canvas,
  gives it its own X/Y position and CLUT fill colour. New projects default to
  the old appearance (175px right, 2px down from their respective labels).
- **Undo/redo:** buttons and Ctrl+Z/Ctrl+Y/Ctrl+Shift+Z. Tracks edits to
  labels, visibility, artwork colour/outline, element positions, dragged bars,
  default settings, font scaling and PPB background. Up to 256 snapshots for
  this editing session. Cancel discards changes.
- **Previously available:** optional separate PPB background, zoom, middle
  mouse panning, snap grid and SIDBOX glyph preview.

## Runtime

Generated `gamehelpers/gametitle.c` now includes:

- `title_options_visible[8]`: controls visibility, drawing and navigation,
  not merely hiding text while retaining an invisible selectable item.
- `title_options_bar_pos[3][2]` and `title_options_bar_colour[3]`: independent
  slider coordinates and palette indices.
- Independent heading and row foreground, outline colour and enable flags.

Settings continue to be session-only. **Music Volume is exposed but is not
connected to a master MP3 volume mixer**, because the present SDK has no such
API. Text Speed, Screen Shake and Difficulty still require the game logic to
consume their values. The TFCard subsystem and user `main.c` are untouched.

## Compatibility and regeneration

Stage 5.65 projects reopen with all rows visible, their existing labels and
positions, no outlines, and the original hardcoded bar placement as initial
independent coordinates. Saved JSON adds row-level `visible`, `foreground`,
`outline`, `outlineEnabled`, and for slider rows `barX`, `barY`, `barColour`;
heading adds `titleForeground`, `titleOutline`, `titleOutlineEnabled`.
The project title JSON `version` is 7. Older data is normalised on open.

After saving, use **Update Game Project** to regenerate `gamehelpers/gametitle.c`
and rebuild your game. Existing handwritten `main.c` remains unchanged.

## Validation

- Stage 5.66 source contract test: passed.
- Stage 5.65 mock C runtime joystick regression: passed.
- Stage 5.66 mock C runtime with alternate hidden rows and independent
  slider origins: passed.
- Stage 5.65 options generator and earlier title selection/align regressions:
  passed.
- Full Qt6 IDE compile and live 480x320 hardware tests: **not run here**.

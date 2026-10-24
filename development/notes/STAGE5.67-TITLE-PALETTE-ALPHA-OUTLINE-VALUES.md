# CoderGirl IDE Stage 5.67.241026

## Title Screen / Options pass: palette, alpha, outline thickness, value spacing

This release builds on Stage 5.66.1 and leaves your existing world/gameplay runtime, audio mixer, PPBs, and handwritten `main.c` unchanged.

### Title selection rectangles

The main menu and Options screen use one runtime function, `title_draw_selector()`, with the exact geometry:

```c
const int x=art->x, y=art->y;
const int w=title_width(art), h=title_height(art);
gfx_rectf(x-8,y-8,w+16,h+16);
```

For text, `title_width()` is `strlen(text) * 8 * title_scale(size_x)` and `title_height()` is `8 * title_scale(size_y)`. The same 8-pixel padding is used by both editor previews. **Update Game Project and rebuild the game** to ensure the actual firmware runs the newly generated `gamehelpers/gametitle.c` rather than an older copy.

### Options value placement

The fixed `label X + 175` value position is replaced by:

```c
v.x = art.x + title_width(&art) + 16;
```

Music `ON/OFF`, SFX `ON/OFF`, Screen Shake `ON/OFF` and difficulty now sit just after their labels. The editor preview draws these values at the same calculated position, separately from the selectable label. Independently positioned volume/text-speed slider bars are not moved.

### Title RGBA palette editor and rectangle blending

The Title Screen Designer has **Edit 256 RGBA colours...** next to its palette source. Each CLUT index can be edited using a colour dialog with an alpha channel. The project's `.sidbox-title-screen.json` stores a private optional `titleClut` array of 256 `AARRGGBB` strings. Source PPBs, pixel indices, and imported `.pal` files are not modified. If no custom palette is saved, the previous palette selection and fallback behavior remain.

The selector's **Rectangle alpha / blend** control changes the alpha for the selected CLUT index. Runtime generation installs that CLUT via `gfx_usefpalette()`. There is no added CPU-side per-pixel blending. The actual alpha appearance depends on SIDBOX's foreground layer compositing, so verify this on physical hardware.

**Important palette constraint:** all foreground graphics using a CLUT index necessarily share its RGBA colour/opacity. Choose an index not already used by your other title artwork for the rectangle colour. Index 0 retains transparent alpha so the foreground can clear safely.

The Options screen uses the same title foreground CLUT, so it also sees edited palette colours, and its selector draws using the same index.

### Outlines

Both designers now offer **Outline thickness (px)**, 1 to 4 physical screen pixels, for the heading, text labels, and main menu entries. Preview and generated C draw the same Manhattan-radius outline using SIDBOX's glyphs. Older JSON defaults to 1px. Larger outlines require more text draw calls per frame; use judiciously if your game is already close to its 50 Hz budget.

### Regression and compatibility

- Existing title-screen JSON versions are still accepted.
- Palette changes and outline thickness participate in existing Undo / Redo via the design-state snapshots.
- No changes to the audio mixer or TFCard streaming.
- The previous QGraphicsItem selection-lifetime crash safeguard is retained.
- Generated C passes GCC `-fsyntax-only` against the SIDBOX SDK `apis.h`.
- Twelve targeted source compatibility checks pass (see local test results).
- Qt6 GUI compilation and physical SIDBOX graphics/alpha verification were **not** available here.

### Files updated

- `gametitlescreeneditor.cpp`
- `gametitleruntime.cpp`
- `idelibs/codehelpers/game/gametitle-runtime.rulec`
- `splashscreenwidget.cpp` (`Build: 5.67.241026`)
- `README.md`

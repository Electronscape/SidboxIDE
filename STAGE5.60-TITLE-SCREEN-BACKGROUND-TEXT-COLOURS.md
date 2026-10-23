# Stage 5.60.231026: Title Screen Designer, Pass 3

Based on Stage 5.59.231026. This is **design-time only**. It does not add game save/load or a title-screen renderer to the SIDBOX runtime.

## Title-screen background

Under **Title Screen → Background (480 × 320)** select an existing project `.ppb` and one of the same three background modes used by Game Designer:

- **Sprite / blit**: ordinary PPB sprite rendering.
- **Direct — prepared PPB**: a column-major PPB intended for a direct background buffer. For the preview, the stored image is transposed exactly as it is in `SidboxGameDesigner::resourcePreview()`.
- **Direct — convert PPB**: an upright, ordinary PPB to be converted on load by future runtime support.

The preview uses actual pixel dimensions, clips to the 480 × 320 design window and does not scale, recolour or export any PPB. The chosen path/mode are saved in `.sidbox-title-screen.json` as `background.path` and `background.mode`.

## Text colours, outline and size

Select **Game Title**, **Subtitle**, or a menu row in the Artwork/Position panel. In **Text** display mode you can set:

- Foreground CLUT index (0–255), with a 16×16 swatch picker.
- Enable outline checkbox.
- Outline CLUT index (0–255) with its own picker.
- Font size options **1 → 1×**, **2 → 2×**, **3 → 4×**, **4 → 8×** in the editor preview.

Both colours reference a configurable source in **Text foreground CLUT**. Pick an existing `.pal`, `.act` or `.ppb` to preview the exact 8-bit CLUT colours, not arbitrary RGB replacements. Leaving it on **Use a project PPB palette** uses the first usable 256-colour PPB palette as a preview fallback. No stored palette indices are rewritten.

The SDK exposes `gfx_drawtextf(x,y,text,sizex,sizey)` and `gfx_drawtextfc(...)`, but does not document the hardware size parameter mapping in the included header. The 1×/2×/4×/8× choices are therefore stored as size **levels 1–4**, with editor-preview magnifications; verify the level-to-runtime mapping when the title-screen runtime is implemented.

The Qt preview uses an approximated fixed 8×16 glyph grid. The final glyph bitmaps will be SIDBOX's native font when the runtime is generated.

Each Title/Subtitle/Menu Entry `display` JSON now contains `foreground`, `outline`, `outlineEnabled` and `fontSize`. Older Stage 5.59 files load with foreground 15, outline 0, outline disabled and size level 1.

## Load Game

**Load Game** is not a world-selection action. Its Destination World and Player Start cells show **(Not used)** and are disabled. In the saved file both fields are JSON `null`. The previous `saveSlots: 10` reservation remains for a future ten-slot game-progress loader. **Start Game** and **Goto World** keep destination selection, including the Default Player Start.

## Files changed

- `gametitlescreeneditor.cpp`
- `splashscreenwidget.cpp` (Build 5.60.231026)
- `development/tests/test_stage559_title_designer.py` (updated stage assertion)
- `development/tests/test_stage560_title_screen_styling.py` (new)

## Verification

Stage 5.60 design-time source/data tests pass, as does the updated Stage 5.59 compatibility test against GameTest3. Full Qt6 compilation and actual Qt canvas interaction remain **unverified** because Qt6 development headers are unavailable here. No game project regeneration is required. Runtime save/load and title-screen rendering remain future stages.

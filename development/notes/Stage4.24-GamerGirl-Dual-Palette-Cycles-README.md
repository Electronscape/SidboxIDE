# GamerGirl Stage 4.24 — Dual palette cycling

Based on the **Stage 4.23 full IDE** source; no firmware files have been modified in this release.

## What changed

- The Palette Editor's existing **Bank** selector now chooses which colour-cycle settings you edit. **Foreground** and **Background** each have their own **Enabled**, **Start**, **Length**, and **Frames/step** values, and each gets a live swatch preview.
- The foreground range excludes palette index 0 (transparent); background allows index 0, which is opaque.
- The World Designer **Colour cycles** checkbox previews both banks independently on indexed artwork; the tilemap overlay uses the foreground CLUT. Cycling only alters editor preview colour tables, never PPB pixel indices or `.pal` files.
- `.sbgm` (version 1) now stores `foregroundColourCycle` and `backgroundColourCycle`. Previous Stage 4.22 `colourCycle` entries migrate to foreground only; background defaults disabled. `showColourCycles` stays an editor-preview preference.
- The bundled V1 graphics SDK `idelibs/api/graphics/graphics.h` now matches the *append-only* firmware hardware API, exposing `gfx_palcycleonb`, `gfx_palcycleoffb`, `gfx_palcyclesetb`, `gfx_palcyclerangeb`, `gfx_palcyclerateb`. Existing function-pointer offsets remain unchanged. The SDK cheat sheet documents these calls.
- Regenerating game assets adds **automatic cycle setup in generated `gameassets.c`**, after the CLUTs are installed and before gameplay. Enabled cycles are disabled by `gameassets_shutdown()`. Background setup is emitted only for dual-plane designs. User-owned `main.c` remains protected.

## Frames versus milliseconds

The SIDBOX firmware advances each palette cycle once per `lcd_update_palette_cycle()` invocation, counting LCD update frames. In GamerGirl's default **50 FPS** preview, `QElapsedTimer` supplies *elapsed milliseconds* which are converted to virtual frames (`elapsed / 20`); a `QTimer` requests redraws every 20 ms. No dependency on a 144 Hz monitor or the computer's render-loop FPS.

| Frames/step | At 50 FPS |
| ---: | ---: |
| 1 | 20 ms |
| 2 | 40 ms |
| 4 | 80 ms |
| 5 | 100 ms |
| 10 | 200 ms |

If your game actually calls `gfx_setlcd()` at **25 or 60 FPS**, its cycle will correspond to those LCD frames; the editor uses a 50 FPS approximation. `Start` + `Length` is converted to the firmware's **inclusive** `fromcol`/`tocol` range. For example Start=80, Length=8 emits `(80, 87)`.

## Suggested test

1. Open a `.sbgm`, edit a palette resource. Select **Foreground**, enable Start=80, Length=8, Frames/step=4. Select **Background**, enable Start=120, Length=16, Frames/step=2. Their settings should stay independent as you switch between banks.
2. Enable **Colour cycles** in the World Designer. Foreground indexed artwork and the tilemap should update every ~80 ms; background indexed artwork ~40 ms. Toggle preview off and verify original colours return.
3. **Save Design**, close/reopen `.sbgm`, confirm both settings persist.
4. Use **Update Game Project** (which protects hand-edited main.c). Inspect `gameassets/gameassets.c` for the corresponding `gfx_palcyclerange`, `gfx_palcyclerate`, `gfx_palcycleon` and background `...b` calls. This is generated source, not firmware code.
5. Build and run on your updated SIDBOX firmware. Old firmware lacking the appended background API entries **must not** run games with background cycling enabled.

## Changed production files

- `gamepalette.h`, `gamepalette.cpp`
- `gamepaletteeditor.h`, `gamepaletteeditor.cpp`
- `gamedesigner.h`, `gamedesigner.cpp`, `gamedesigner_project.cpp`, `gamedesigner_export.cpp`
- `gamecodegen.h`, `gamecodegen.cpp`
- `idelibs/api/graphics/graphics.h`
- `idelibs/docs/cheatsheet.json`

## Validation

- 26 selected Stage 4.00–4.24 Python/source-level regression checks passed (including updated 4.22/4.23 compatibility checks).
- Compared all **35 API function-pointer field positions** in the shipped SDK against the updated firmware's graphics-hardware API table. Positions and order match. Existing differing field names predate this change; function-pointer slots are identical.
- Existing host-side foreground/background firmware-cycle tests pass, including different speeds/ranges and restoring palettes.
- **Not verified here:** native Qt6 build (Qt6 development packages not installed), actual visual behaviour on Fedora, or a compiled/running V1 game on SIDBOX. Those require local tests.

No modifications to SIDBOX firmware, CLUT file format, game physics, `.map` format, or your hand-owned game code.

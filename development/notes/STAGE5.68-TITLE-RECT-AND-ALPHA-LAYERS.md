# Stage 5.68 (24 October 2026) — Title runtime rectangle and real LCD layers

## What was wrong

Stage 5.67 generated title-screen C drawing **both the PPB background and all foreground text/selector graphics into the foreground indexed framebuffer**. Thus, although it installed a title ARGB foreground CLUT, the selector's alpha had no separately rendered background plane to blend against. Changing a palette alpha entry alone did not solve this layering problem.

The title selector width/height calculations also used an exponential approximation for the gfx_drawtextf size parameters, while the requested rectangle geometry is the literal size-X/Y multiple of the native 8-by-8 character cell.

## Stage 5.68 changes

- The generated runtime now draws the title or Options background on the SIDBOX **hardware BACK layer**, using its own PPB-derived background CLUT. That CLUT is made opaque for backgrounds, including index 0.
- Title text, title/logo artwork, Options text, sliders and menu selector remain on the **FRONT layer**, with the editable title foreground ARGB CLUT.
- Foreground CLUT entry 0 is forcibly transparent (clear colour) to reveal the back layer; any alpha set on other indices remains in the generated CLUT.
- The main and Options backgrounds have independent CLUTs. When an Options background is not specified, it reuses the main background and palette.
- Backgrounds are repainted and presented when the title screen first opens and when entering/leaving Options. No additional background redraw or TFCard access is introduced per frame.
- Filled-selector geometry for both main and Options uses the text origin and character dimensions: `w = strlen(text) * 8 * size_x; h = 8 * size_y; gfx_rectf(x - 8, y - 8, w + 16, h + 16);` PPB artwork selections still use actual image bounds.
- Both title and Options editor previews now display the background with its own original **opaque** PPB palette, rather than applying the foreground title palette to background pixels. No source PPB bytes or pixel indices are changed.

## Important hardware limitation

Real ARGB blending requires the game's `gfx_mode` to have a working dual-layer configuration, and the SIDBOX LCD compositing path to honour intermediate foreground CLUT alpha. The available API header declares the front and back palette/buffer functions, but does not itself prove that 1..254 alpha values will blend rather than be treated as binary transparency. **This needs a real SIDBOX hardware test.** On a single-layer setup, the generator still draws the background in the foreground buffer as a compatibility fallback, but this cannot provide true blended transparency.

The alpha value is associated with a **foreground palette index**, not an individual rectangle: other graphics with the same foreground index share that colour and opacity. Choose a dedicated index for the selector rectangle. The dedicated background CLUT avoids accidental changes to the PPB background colour when editing title foreground colours.

## What to do

1. Apply the Stage 5.68 drop-in over Stage 5.67 and rebuild the Qt IDE.
2. Open Title Screen Designer and set your rectangle's selected palette entry alpha (try 128) while keeping foreground index 0 transparent.
3. Save the title design, then **Update Game Project** to regenerate `gamehelpers/gametitle.c`.
4. Rebuild the game and test on real SIDBOX hardware in dual-layer display mode.
5. Compare main-menu selector alignment and its blending with the Options selector. Check returning from Options restores the background correctly.

No changes to user-owned `main.c`, `.sbgm`, existing PPBs, or audio mixing code are required.

## Validation

- Generated C host mock compiles with `cc -std=c11 -O0 -Wall -Wextra -Werror`, exercises Start → Options → return → Start, skips hidden rows, and checks main and Options selector rectangles at different X/Y font sizes.
- The mock verifies the separate foreground and background palettes are installed and the background palette switches when entering and leaving Options.
- Nine targeted source regression checks pass, including the historical scene-item selection crash guard.
- Qt6 IDE GUI and actual STM32H743 alpha compositing were **not** tested in this environment.

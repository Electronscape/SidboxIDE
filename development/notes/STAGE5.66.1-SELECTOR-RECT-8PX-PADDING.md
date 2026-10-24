# Stage 5.66.1: title/Options selector rectangle geometry

Date: 24 October 2026

## Fix

The filled selector in the generated `gamehelpers/gametitle.c` now uses the same origin as the text/artwork:

```c
if (behind) gfx_rectf(x-8, y-8, w+16, h+16);
```

For text, `w = strlen(text) * 8 * title_scale(size_x)` and `h = 8 * title_scale(size_y)`. These are the actual pixel multipliers used by `gfx_drawtextf`: font size levels 1/2/3/4 correspond to scales 1/2/4/8. The 8-pixel padding is in screen pixels, not scaled pixels. For PPB artwork the same padding is added around the image's native dimensions. This helper is shared by the main title menu and the Options menu.

Both Qt editor previews now use the same 8-pixel padding; the Options editor measures *only the option label* (not the adjacent ON/OFF/difficulty readout), matching the runtime. Selecting an editor-only independent slider no longer paints a misleading runtime selector around it.

## Integration

- Apply over Stage 5.66, rebuild the Qt IDE.
- Use **Update Game Project** to regenerate `gamehelpers/gametitle.c` from the modified `.rulec`.
- Rebuild the V1 game and transfer it to the SIDBOX.
- No changes to `.sidbox-title-screen.json`, PPB data or the user's `main.c`.
- The earlier hardware-calibrated rectangle offsets have been replaced, per user request.

The source/mocked C tests exercise the intended coordinates but do not replace a real hardware pixel-alignment test.

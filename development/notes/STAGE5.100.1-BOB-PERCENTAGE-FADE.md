# Stage 5.100.1 (25 Oct 2026): BOB percentage fade correction

Stage 5.100 incorrectly exposed only `BLIT_FLAG_ALPHABLEND` as a checkbox.
SIDBOX's BOB renderer also reads the firmware fade percentage from
`gfxbob_t.flagval[BLIT_FLAG_TYPE_FADE_VALUE]` (flagval[1]), ranging from 0 to 100.
The effect is hardware-style 4x4 ordered dithering, not per-channel RGB blending.

## Updated editor

**Game Object Properties > Visual & Movements > BOB patterned fade**:
- A 0-100% slider with numeric spin box; either control updates the other.
- 0% means normal opaque rendering; it removes the blend flag.
- 1-100% enables `BLIT_FLAG_ALPHABLEND` and stores that percentage in flagval[1].
- At 100%, the patterned fade is complete (no drawn sprite pixels).
- Applies per placed sprite or configured Game Object.
- The preview still shows the original artwork because the exact firmware
  blitter algorithm itself is not in the uploaded IDE archive. Preview it on SIDBOX.

## Saved worlds and compatibility

- The percentage is stored as `objectAlphaFadePercent` in `.sbgm`.
- All previous worlds without this setting start at 0% (unchanged appearance).
- Worlds saved with Stage 5.100's ON/OFF `objectAlphaBlend=true` checkbox
  load with 50% fading. The old flag could not preserve a chosen percentage.
- Stage 5.100's disabled checkbox loads as 0%.
- Save a world in this version to write the new percentage format.

## Exported C code

The sprite BOB initializer now sets *both* fields:

```c
bob.flags = (uint8_t)((bob.flags & (uint8_t)~BLIT_FLAG_ALPHABLEND) |
                      BLIT_FLAG_ALPHABLEND); // only when percentage > 0
bob.flagval[BLIT_FLAG_TYPE_FADE_VALUE] = (uint8_t)50; // example
```

No per-frame calls, firmware edits or `main.c` modifications are required.
Flip flags, sprite animation and Game Object sprite copies preserve the setting.

## Testing

- Native GCC tests verified 0, 1, 25, 50, 75, 99 and 100 percent.
- World Canvas and world-object regression checks passed.
- Stage 5.97, 5.98, 5.99 and 5.99.2 native dialogue/reply regressions passed.
- A Stage 5.97 editor test checks its own older splash version and is
  therefore not a valid version assertion for Stage 5.100.1.
- This environment has no Qt6 development headers; Fedora IDE compilation
  and SIDBOX hardware fade rendering still need confirmation.

## Installation

Unzip into the IDE source root preserving paths, rebuild IDE, select a sprite,
configure BOB patterned fade, save the world, Update Game Project, rebuild game.
`main.c` is untouched.

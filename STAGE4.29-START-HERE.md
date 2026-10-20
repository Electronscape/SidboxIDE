# GamerGirl Stage 4.29 — Dialogue Colours, Outlines and NPC Animation

This builds on the **Stage 4.28a real-hardware NPC dialogue success**.
No game physics, SPC playback or existing world-object helpers were changed.

## Using the dialogue style

1. World Designer → **Adventure Editor...** → **Dialogue Box Atlas**.
2. Set **Text colour (foreground palette index)** (default 15).
3. Check **Outline dialogue text (four directions)** if wanted.
4. Set **Outline colour (foreground palette index)** (default 1).
5. Press OK, save design and **Update Game Project** to regenerate C.

Text is drawn at the four one-pixel offsets and then again in its normal
position. Outlined wrapped dialogue has 20px line spacing; otherwise 16px.
Answers have 20px separation and a blank gap from NPC dialogue. To fit this,
the box is taller and begins higher on the 480x320 display (y=148).
The text style also applies to player replies and inventory listings.
Foreground palette index 0 is transparent; use visible colour entries.

## NPC animation

1. **Game Resources → Sprites**: your NPC must already be an ordinary, placed
   foreground sprite; its image atlas must have multiple correctly-sized cells.
2. **Adventure Editor... → NPCs**: select its row.
3. Press **NPC Animations...**.
4. Choose a contiguous Idle first atlas cell, number of frames and speed.
5. Optionally set separate Talking first cell, count and speed.
6. Press OK, **Save Design**, **Update Game Project**, then build and test.

Rates are in 50 FPS displayed game frames per picture, just like other
GamerGirl animations. A count of zero disables that state. All fields save in
`world1.sbgm` under the NPC's `animation` property.

The runtime updates the *existing* exported sprite BOB frame from
`game_adventure_input()`, without modifying position or drawing a duplicate.
When a dialogue starts, Talking frames are used; afterwards, Idle frames
resume. If Idle has zero frames, the resource's original frame is restored.
This is a **simple two-state loop editor**, not the full complex Player
Animations state machine (the separate .sbanim editor remains available).

## Important for the user-owned platformer's main.c

The previous Stage 4.28a fix registered adventure startup, input, drawing and
`Guardian[0]` in the user's customised `main.c`. This Stage 4.29 update needs
**no new main.c calls**. Do not overwrite the customised game `main.c`.
Update Game Project regenerates `gameadventure.c` and installs the revised
`gameadventureruntime.c/.h`. Confirm the game project's file list still builds
these files; the earlier project fix added them.

## Testing performed here

- Earlier Stage 4.20 through Stage 4.28a focused static regression scripts pass.
- Stage 4.29 editor/generator static assertions pass.
- Host GCC C compilation with `-Wall -Wextra -Werror` passes.
- Host runtime test verifies four-pass text outline with foreground colour,
  idle animation timing and switching to talking frames.
- **Qt6 IDE build and SIDBOX hardware tests are pending.**

Please test on a backup project, and check any manually maintained NPC draw
calls (Guardian currently uses an ordinary decoration sprite).

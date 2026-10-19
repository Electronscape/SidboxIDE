# GamerGirl Stage 3.66 — Downhill Sliding and Cliff-Edge Contact

Based on **Stage 3.65 (the user-updated IDE from 18 October, 15:24)**. The only production source changed is:

`idelibs/codehelpers/game/tilemap.c`

## The two defects

1. **2% damping could be effectively 100% on gentle ramps.** The passive slope force is measured in hundredths of a pixel/frame. Low gradients produced less than one unit and were truncated to zero; even a one-unit force was truncated away during the 2%-damping multiplication. That made the character stand still indefinitely.
2. **A downhill ramp could tug the player while still standing on the adjacent flat ledge.** The previous centre-foot contact test was necessary, but insufficient: the centre could enter the ramp while the rear foot was still supported by solid flat collision. The ramp was allowed to accelerate the player anyway.

## Physics changes

- Rounds gravity's horizontal tangent projection to the nearest hundredth and retains a minimal representable downhill impulse on a non-horizontal segment.
- On an active passive surface, rounds the drag calculation instead of truncating it, and does not erase valid subpixel momentum below 0.02 px/frame. Ordinary external-force behaviour **off** the stamp is unchanged.
- Refuses passive acceleration while the character's feet are still physically supported at that height by an adjacent solid/one-way/blocking-zone flat surface. Regular full-foot collision detection is untouched.
- Maintains the prior centre-foot gate to avoid activating distant shapes with just a toe, and maintains mirrored and Bezier tangent directions.
- No changes to stamped level format, state variables, game APIs, loops, springs, or Player Animation Editor.

## Installing

1. Back up the existing IDE/game sources.
2. With changed-files archive, replace **`idelibs/codehelpers/game/tilemap.c`** in the IDE source tree.
3. Use **Update Game Project** in the rebuilt/current IDE (it refreshes the V1 copy at `gamehelpers/gametilemap.c`).
4. Recompile the V1 game and test on SIDBOX.

**No** map re-export, `main.c` edits, animation-header update, or new physics settings are required. Existing passive stamps set to 2% retain that exact value.

## Validated

With the real compiled C solver (`-std=c11 -Wall -Wextra -Werror`):

- Regression (prior Stage 3.65): on a 1px descent over 63px at 2% damping, player moved **0px in 120 frames**.
- After fix: **27px in 120 frames without joystick input** (x=40 to x=67).
- With half the feet on the ramp but flat ledge support still present, player remained stationary for 80 frames.
- Continued downhill after walking fully beyond the flat ledge and releasing the joystick.
- Mirrored downhill ramp, 20px-wide player, 100%-sticky, disabled passive surface, all earlier centre-foot/cliff/bowl tests pass.
- Undefined-behaviour-sanitizer regression passes.
- Stage 3.62 C playback, Stage 3.64 generated C animation integration, Stage 3.65 animation-autosave source checks pass.

**Still untested:** actual Qt6 IDE compilation and SIDBOX device behaviour. If a particular level still sticks, send the actual `.map`, the slope shape, and the player's collision-box width so it can be reproduced precisely.

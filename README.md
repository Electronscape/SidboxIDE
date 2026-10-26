# CoderGirl IDE Stage 5.151.261026: Swirling Fireflies ✨

## New Particle Spawner movement mode

Game Designer → select a **Particle Spawner** → **Game Object Properties** → **Scenery Particle Spawner** → **Particle behaviour**:

- **Falling leaves** (unchanged)
- **Drifting clouds** (unchanged)
- **Floating dust / motes** (unchanged)
- **Swirling fireflies** (new)

When you choose the new preset, the controls are initialized for gentle, free-floating fireflies:

| Property | Firefly default |
| --- | ---: |
| Wind X | 2 |
| Drift Y | -1 |
| Gravity | 0 |
| Flutter | 0 (orbital movement replaces flutter) |
| Lifetime | 500 frames |
| Max active particles | 20 (you may increase to 32) |
| Birth interval | 12 frames |
| **Swirl radius** | 24 pixels |
| **Swirl speed** | 2 |

The **Swirl radius** and **Swirl speed** controls only appear when **Swirling fireflies** is selected. Each particle has its own random starting phase and varied orbit radius, from roughly half to the full configured radius. The orbit centre still drifts with Wind X and Drift Y, and Gravity remains available if desired. Speed 1 is about 5.12 s per orbit at 50 Hz; speed 2 about 2.56 s; speed 4 about 1.28 s. Existing fade in/out is compatible. Selecting the firefly preset enables the fade checkbox for a soft entry/exit; you can turn it off.

## Live preview and runtime

- All spawners animate in the **World Canvas**, not just the selected one.
- The little **Game Object Properties** preview also updates while adjusting swirl radius and speed.
- **Pre-populate on world load** works with fireflies, so the scene starts already alive when enabled.
- Each emitter still has a fixed 32-particle pool. No heap allocations or per-frame floating-point trigonometry: firmware uses a small 64-value signed sine lookup.
- Fireflies respect fade, behind-tile draw order, optional over-player particle split and map FRONT cells.
- Saved `.sbgm` worlds store the firefly preset, swirl radius and swirl speed; older worlds default to their previous modes.
- The user-owned `main.c` does **not** require any new code. Its existing world drawing and overlay calls are reused.

### A visual tip

Use a tiny bright PPB sprite (for example a small pale-yellow dot or a 2–4 pixel glow). Larger sprites work but will make the fireflies look like floating lanterns! The runtime draws the chosen sprite; it does not create light sources or cast dynamic illumination.

## Install

Unpack the Stage 5.151 drop-in **over Stage 5.150**, retaining the paths, or use the complete source archive.

1. Rebuild CoderGirl Qt6.
2. Open the world and choose **Swirling fireflies** for a Particle Spawner.
3. Set radius/speed and watch the live preview; optionally enable **Pre-populate**.
4. **Save Design → Update Game Project → rebuild and upload your SIDBOX game**.

No `main.c` edits or firmware changes required.

## Changed files

`gamedesigner.cpp`, `gamedesigner.h`, `gamedesigner_project.cpp`, `gamedesigner_export.cpp`, `idelibs/codehelpers/game/gameworlditems.rulec`, `splashscreenwidget.cpp`, plus regression fixtures and Stage 5.151 native test.

## Verification

Native GCC tests pass with `-Wall -Wextra -Werror` for the orbit period, legacy leaf physics, save/load/export fields and matching Qt/runtime movement tables. Previous native particle regressions pass after updating their emitter fixture records to include the new fields. The graphical Qt6 build and real SIDBOX 50 Hz performance still need your Fedora/SIDBOX test.

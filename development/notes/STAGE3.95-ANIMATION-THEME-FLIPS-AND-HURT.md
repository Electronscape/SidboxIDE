# Stage 3.95 — Animation Toolkit theme, Game Object flips, Hurt animation

**Base:** Complete Stage 3.94 IDE source. **Qt6 build:** NOT available in this environment; test in Qt Creator / Fedora.

## Player Animation Toolkit

- Receives the **active IDETheme** from Game Designer on opening.
- Keeps its dark professional square-corner interface and existing animation / timeline behaviour.
- Uses `m_theme.accent` for selected animation-state rows, checkboxes, button focus/hover, the atlas-cell selection rectangle, timeline-card selection and the drag insertion line. No fixed red accent remains.
- Does not edit `.sbanim` format or animation timings.

## Game Object Properties

- Persist whether this dialog was maximized in `QSettings("Sidbox", "SidboxIDE")` under `GameObjectProperties/maximized`. Restores at next opening (including after the IDE restarts). Saves state on OK or Cancel.
- Renamed section to **Visual & Movements**.
- **Flip X / Flip Y** checkboxes share a row directly after `Animate sprite frames`, and are available for placed sprites including decorations. They flip visible artwork; they do NOT move the hitbox, modify the path or rewrite PPBs.
- `Movement spline` entries use the **existing** `gr_icon_spline.png` icon, the same as the resource tree, with the spline's actual name and stable ID.
- Live object preview and designer canvas use the mirroring flags.

## Exported game data

- `.sbgm`: asset fields `objectFlipX`, `objectFlipY` default to `false` for older projects.
- `gameworlditems_init()` applies `BLIT_FLAG_FLIP_X / Y` to managed sprite BOBs. Decoration draw code applies the same flags. Existing unrelated `gfxbob_t.flags` are preserved. Generic sprite animations only change the atlas-cell index, so flip flags remain in effect.
- F5 **Update and Compile** is required after changing flips.

## Hurt animation was not appearing

**Root cause:** The Stage 3.92 starter used `#ifdef PLAYER_ANIM_STATE_HURT`; but the animation generator declared `PLAYER_ANIM_STATE_HURT` in a C `enum`, not with `#define`. The preprocessor skipped that `#ifdef` branch even when a valid Hurt state existed.

- The animation header exporter now emits `#define PLAYER_ANIM_HAS_HURT_STATE 1` if `Hurt` exists in the state list (otherwise 0).
- `maingame.c.txt` now uses `#if defined(PLAYER_ANIM_HAS_HURT_STATE) && PLAYER_ANIM_HAS_HURT_STATE` before assigning the Hurt enum. This compiles for projects without Hurt as well.
- **Important for existing projects:** Open **Player Animation Toolkit**, ensure the Hurt state contains frames for your chosen direction, and **Save Animations / regenerate player_anim.h**. Then F5 **Update and Compile** to refresh `maingame.c.txt`. If your `main.c` is hand-owned, copy the corrected Hurt-selection block from the generated tutorial file into `main.c`; F5 does not overwrite owner code.
- No world-object physics or hardware flashing function was changed. The previously working solid-colour flash continues as before.

## Validation

- Source checks: `test_stage395_object_flip_theme_hurt.py` + prior Stage 3.90–3.94, animation and loading tests.
- Native C: `test_stage395_hurt_and_flip.c` verifies existing BOB flags and enum-based preprocessor guard.
- Native legacy hazard / breakable tests passed.
- **Qt6 compilation and SIDBOX hardware confirmation still required.**

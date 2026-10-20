# GamerGirl Stage 3.98 — Animation theme, staggered spline start, tilemap pan

Based directly on Stage 3.97 (the SIDBOX head-butt / launched-collectable release).

## 1. Player Animation Toolkit — whole-window IDE theme

The existing layout and per-frame editing are unchanged. The editor's previously
hard-coded dark styling (widgets, popup lists, section border, scrollbars,
buttons, state/direction icons, timeline cards, atlas grid and sprite preview)
now uses the selected `IDETheme` palette. The selected highlight uses the
user's accent colour with contrasting foreground text, in light AND dark themes.

## 2. Start delay for attached splines (per placed object)

Open Game Object Properties -> **Visual & Movements** -> choose a **Movement
spline** -> **Spline start delay**. Set **0–65535 game frames**. At 50 Hz,
50 frames is one second, 100 frames is two seconds. Zero preserves the old
behaviour. Different placed objects may share one reusable spline, each with
an independent start delay. Once elapsed, normal path movement and looping
continue; the delay does NOT recur on every lap. Knot pauses set in the spline
path itself still work after the start delay.

Saved `.sbgm` field: resource's `gameObject.splineStartDelay`. The generator
writes `pickups[i].spline_start_delay` or `platforms[i].spline_start_delay`.
`gamecollectables` and `gameworldobjects` count down only while the object is
active, before running the attached spline. Sprite-frame animation still runs
while waiting, and the waiting object stays collidable. Multi-frame updates
consume the countdown and advance only leftover movement frames.

**Deployment:** Rebuild the Qt IDE, **Save Design**, then **F5 -> Update and
Compile** to replace both generated `gameworlditems.c` and the installed
`gamecollectables.c/.h` and `gameworldobjects.c/.h` helper pairs. No direct
`main.c` edit is required for the start delay.

## 3. Tilemap editor pan saved in the project

The `tilemap` JSON object in `.sbgm` now records `viewPanX` / `viewPanY` as
WORLD-pixel coordinates (not zoomed scrollbar coordinates). Clicking the
Tilemap Editor **Save** button stores the current position in the design;
**Apply to Design** records the pan in memory and the usual Save Design saves
it to disk. Old `.sbgm` files default to pan (0,0). **Cancel** does not save
new movement. The editor's zoom and other preferences continue to use local
QSettings. The obsolete machine-local pan key is not used going forward.

## Tested here

- Native C spline test compiled against the REAL SIDBOX helper C files:
  independent delays for two objects following the same spline, 50-frame
  wait, split multi-frame update, collectable delay and inactive pickup.
- Native C regression tests: Stage 3.68 platform/spring, Stage 3.90
  jump-only breakable, Stage 3.96 head-butt and Stage 3.95 Hurt/flip.
- Source integrations: stage 3.98, 3.97, 3.96, 3.95, 3.90, 3.81,
  3.80, 3.79, 3.78 and 3.77a.

**Not tested here:** Qt6 GUI build or real SIDBOX display/hardware. Qt6 is
not installed in this environment. Compile/test the light theme, save/reopen
pan and staggered spline start on the user's Fedora SIDBOX setup.

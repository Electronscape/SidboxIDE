# CoderGirl IDE Stage 5.158.261026

## Player Start / World Entry Point: friendly timing sliders

This stage changes **four frame-count spin boxes** into horizontal **draggable sliders**, each with a live readout showing seconds and underlying 50 Hz frames:

| Player Start section | Control | Range | Keyboard arrow step |
| --- | --- | --- | --- |
| Weather | Lightning average interval | 100–2000 frames (2–40 seconds) | 25 frames (0.5 s) |
| Day & Night / Palette Tint | Day duration | 50–30000 frames (1–600 seconds) | 50 frames (1 s) |
| Day & Night / Palette Tint | Night duration | 50–30000 frames (1–600 seconds) | 50 frames (1 s) |
| Day & Night / Palette Tint | Dusk / dawn duration | 25–10000 frames (0.5–200 seconds) | 25 frames (0.5 s) |

The tooltip and current readout are visible while editing. Drag a slider, use the keyboard arrow keys for smaller adjustments or Page Up/Down for larger adjustments. Inactive controls, including readouts, are dimmed when the applicable weather or day/night mode is off.

### Compatibility

The sliders preserve the **exact integer frame count** of previously saved `.sbgm` designs. Saved field names, ranges, defaults, exported C code and timing calculations are **unchanged**. The UI no longer requires users to type those four values into small number boxes.

## Installation

1. Make a backup of the current CoderGirl source before replacing files.
2. Extract `CoderGirl-Stage5.158-261026-DROPIN.zip` into the CoderGirl IDE source folder over Stage 5.157, preserving file paths.
3. Rebuild and launch CoderGirl on Fedora.
4. Open **Game Designer → Player Start / World Entry Point** and expand **Weather** or **Day & Night / Palette Tint**.
5. Tune the durations using their sliders, then save the world.
6. When a duration has been changed and you want to update SIDBOX, use **Save Design → Update Game Project**, then rebuild/upload the game normally.

This stage is **IDE-only**, with no additional `main.c` integration or game runtime changes. You don't need a new SIDBOX build merely to install the sliders.

## Testing

- All 13 focused Python and native-GCC regression suites pass (the Stage 5.146 through 5.158 tests).
- New regression checks verify four sliders, original bounds, live seconds/frame readout, accessible names, saved field compatibility and correct disabled-state behaviour.
- **Qt6 GUI build was unavailable in this environment**, so the final graphical build and drag interaction need testing on Fedora.

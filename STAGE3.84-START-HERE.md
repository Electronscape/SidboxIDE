# Stage 3.84 — Player Animation Toolkit Improvements

Based on Stage 3.83, with **only two production source files changed**:
- `gameanimationeditor.cpp`
- `gameanimationeditor.h`

## Install
Copy these two files into the root of your CoderGirl/SIDBOX IDE source tree and rebuild in Qt Creator.
Or use the full IDE archive.

## Editor improvements
1. **Atlas cell numbers:** Each cell shows its zero-based row-major BOB index, on a dark label.
2. **Double-click inserts:** Single-click highlights a cell; double-click appends it to the current animation. Shift+double-click appends a range starting from the last added cell.
3. **Drag timeline frames:** Internal drag/drop now reorders the actual sequence, rather than merely changing item positions. Each frame carries its own duration when moved.
4. **Per-frame duration:** Select a timeline frame and use **Selected frame** to change its duration between 1 and 250 VBlank ticks. **New frame duration** specifies the default applied to subsequently added frames. SIDBOX V1 animates at 50 Hz, so each tick = 20 ms.
5. **UI:** Three-column, darker workstation style inspired by the supplied reference screenshot, numbered timeline thumbnails, small state pictograms, preview floor grid, red selection accents and exclusively square corners.

## Save/export
- `.sbanim` format version 2 writes optional `frameTicks` arrays, aligned 1:1 with the `frames` array, without changing the atlas PNG/PPB.
- Old `.sbanim` files without `frameTicks` remain loadable and each frame takes the previous clip `ticks` duration.
- **Save Animations**, then answer **Yes** when prompted to update your generated `player_anim.h`.
- The generated V1 C code now uses per-frame tick arrays only when necessary. Uniform-timing animations retain the legacy fast path.
- Existing game `main.c` remains user owned; no automatic overwriting.

## Test status
- Native C per-frame loop/stop/legacy timing test: PASS.
- Generated C runtime template compiled and exercised with gcc: PASS.
- Stage 3.84 structural regression: PASS.
- Existing Stage 3.81 moving-platform order, Stage 3.80 loop boost export, Stage 3.83 project finish, Stage 3.79 build reminder and Stage 3.77a PNG cursor checks: PASS.
- Qt6 compilation and UI mouse/drag testing: **not available in the tool environment**; requires Fedora Qt Creator.

## Suggested GUI test
Open a saved animation. Confirm old timing still plays; double-click three atlas cells; select each timeline frame and set e.g. 5 / 15 / 2 ticks; drag the last frame to the first position; Save and export; close and reopen the .sbanim; verify cell IDs and tick values stay together and match playback on SIDBOX.

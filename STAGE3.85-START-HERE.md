# Stage 3.85 — Animation Direction Modes, Timeline Cards and Drag/Drop Fix

Based on the complete Stage 3.84 IDE. The only **production** files changed are:
- `gameanimationeditor.cpp`
- `gameanimationeditor.h`

## Installation
Use the complete IDE archive, or copy those two files from the changed-files archive into your Qt6 IDE source folder and rebuild in Qt Creator.

## Changes
1. **Direction Mode** has moved from the top toolbar into the **left column, directly below Animation States**. The old combo box is replaced by three radio buttons for 2/4/8 directions, each with a compact 16–20px mapping icon, as in the reference screenshot. The separate direction picker remains below for choosing Right, Left, etc.
2. **Frame Timeline** uses fixed, square-edged thumbnail cards. Each card has three bordered sections: the **atlas cell index on top**, a sprite thumbnail in the middle and the **individual frame time in milliseconds beneath**. The selected card has a red border.
3. **Drag-and-drop reorder** no longer depends on QListWidget's icon-layout movement. It now uses a custom internal MIME drag and explicitly accepts the drop. A red vertical insertion marker shows where the frame will land. On drop, the animation's actual `frames` **and** `frameTicks` arrays are moved together, then the timeline is rebuilt. Duplicated atlas cells retain their separate timings.
4. The **Move left** and **Move right** buttons remain available as a fallback.

## Test the drag fix
1. Open your `.sbanim` in Player Animation Editor.
2. Select the Idle animation with three or more frames.
3. Set the first frame to 100ms, the second to 300ms and the third to 40ms.
4. Drag the third thumbnail to the start; look for the thin red insertion marker; release.
5. Check the new order, and that the **40ms pause moved with the third frame**.
6. Save Animations, reopen the file, and check the order/timings persist.
7. Export `player_anim.h` and test in your game if desired.

## Compatibility
- No format changes. `.sbanim` and generated C timing logic remain Stage 3.84-compatible.
- Existing Stage 3.83 project loading window, Stage 3.81 moving platform Idle fix, and Stage 3.80 loop momentum are preserved.
- Existing sharp-corner styling is kept; there are no rounded panels/buttons/cards.

## Validation
- Stage 3.84 per-frame native C timing test: PASS.
- Stage 3.84 source regression updated for the explicit reorder path: PASS.
- Stage 3.85 source checks for direction modes, card painting, drag/drop and paired data reorder: PASS.
- Existing project loading, moving platform animation, loop momentum, full-update reminder, PNG picker and tile atlas source checks: PASS.
- Qt6 is absent in this environment. **Qt Creator compilation and actual mouse drag/drop testing are not verified here** and must be tested on Fedora.

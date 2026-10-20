# Stage 4.26 — SPC project discovery

Based on GamerGirl Stage 4.25.

## Changes
- `mainwindow.cpp`: `.spc` added to recursive project-folder scans and the matching explorer extension check. Rescan Project Files adds the file to the project manifest, including `.SPC` case variants.
- `mainwindow.cpp`: classify `.spc` as a binary game asset (do not open it as source text), and use the existing music/resource icon fallback in the tree.
- `gamedesigner.cpp`: `.spc` appears in the existing Game Designer Music file picker.
- `development/tests/test_stage426_spc_project_rescan.py`: source checks.

## How to use
1. Replace `mainwindow.cpp` and `gamedesigner.cpp`, or extract the Changed-Files archive over your Stage 4.25 source directory.
2. Rebuild the IDE.
3. Copy `track.spc` into your game project folder.
4. In the project tree choose **Rescan Project Files**. It should appear in Files in Project.
5. Optionally select it from the Game Designer Music picker.

Only the `.spc` suffix is recognised (the `.psc` spelling in the request was assumed to be a typo).

**Important:** this does not add an SPC decoder, host preview, or SIDBOX firmware playback support. A music resource can be referenced in the design, but successful playback depends on a separately implemented compatible player.

## Tests
Stage 4.26 source check passed. Earlier Stage 4.00–4.25 source checks passed when run in batches. Full Qt6 build and actual GUI verification require the user's Fedora setup. No firmware or generated game playback code was modified.

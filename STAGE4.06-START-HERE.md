# SIDBOX GamerGirl — Stage 4.06: Movable Bézier Endpoints

Base: Complete GamerGirl Stage 4.05 IDE. No firmware or runtime files changed.

## Changed file

`gametilemap.cpp` — the `Generate Bezier Curve...` popup in the Collision Stamps / slope editor.

## New behaviour

- Blue **L** and **R** endpoints are now proper interactive handles (same size as the orange A and pink B handles).
- Drag either blue endpoint **up or down** to change that end's Y coordinate, independently of A/B. The cursor changes from open to closed hand when dragging.
- Two slider+number controls — **Left endpoint Y** and **Right endpoint Y** — allow exact vertical placement from 0 (top) to `stamp height * tile size` (bottom).
- The preview updates live when dragging or changing any numeric control.
- Orange A/B handles retain their free X/Y dragging, with the original A.X <= B.X restriction.
- Blue endpoint X positions remain pinned to 0 and full width. This is deliberate: point-defined collision stamps must cover the full stamp width to stay valid on SIDBOX; moving their X positions would create gaps and break existing map validation.
- Accept/OK bakes the new geometry to the **same ordinary v4 point-defined collision data** as before, with the existing undo history. Cancel leaves the stamp unchanged.
- Existing stamps still open using their previously saved endpoint Y values. The initial midpoint default for newly created stamps has not changed.

## Install and verify

Replace `gametilemap.cpp` in the IDE source root, then rebuild your Qt6 IDE normally. You do **not** need to rebuild the game project or firmware.

To test: open a Collision Stamp, select Edit, click **Generate Bezier Curve...**; drag blue L to the very top and blue R to the bottom, reshape orange A and pink B, and click OK. Confirm the normal collision editor shows the new surface, and that reopening the stamp retains those generated points. Also test Cancel and Undo.

Portable source assertions were run with:

`python3 development/tests/test_stage406_bezier_endpoints.py`

Stage 3.99 and Stage 4.00–4.05 targeted compatibility checks pass. A native Qt6 build and physical SIDBOX run are not available here, so they require testing on your machine.

## Archive contents

- `IDE-GamerGirl-Stage4.06-Full.tar.gz`: all complete IDE sources and bundled project content, based on Stage 4.05.
- `IDE-GamerGirl-Stage4.06-Changed-Files.tar.gz`: `gametilemap.cpp`, the new test, and this note.

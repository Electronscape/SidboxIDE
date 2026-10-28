SIDBOX CoderGirl IDE — Stage 5.166.52.281026
VISUAL NODES — SAVED PAN/CAMERA RESTORATION

INSTALL
Apply Stage 5.166.52 hotfix over 5.166.51 and rebuild the Qt IDE.
No game regeneration, .sbgm/.map conversion, or main.c changes are needed.

FIX
The Visual Nodes camera previously saved only a floating-point scene centre.
On reopening a maximised window, Qt's splitter and scrollbar geometry could
shift the visible pan even if the zoom was restored. This update stores the
scrollbar offsets and viewport pixel dimensions alongside the existing zoom
and scene centre in .vsgm's optional `view` object.

When reopening on the same viewport dimensions, the exact scrollbar offsets
are restored. If the window or screen size changed, the old scene centre is
used instead. The view's resize anchor is kept at its centre so splitter
resizes do not move the map unexpectedly. The saved camera also restores
when the graph is empty.

Camera is saved with Save Graph + World and on closing even when no nodes were
edited. .sbgm connections, .vsgm card placement, 8px snap and purple wire
routing are unchanged. Older .vsgm files with no camera or only zoom/centre
remain compatible.

TEST
1. Open a .vsgm, drag the canvas far left/right and up/down, and change zoom.
2. Save Graph + World; close; reopen. Check exact zoom and viewport location.
3. Pan again without touching cards, close (no Save), reopen. Check location.
4. Resize the editor (if possible), close/reopen. Check same scene region is
   visible even if the viewport size changed.
5. Confirm purple dialogue and Trigger card positions remain unchanged.

TESTING HERE
Source/schema regression and older Visual Nodes source regressions passed.
Full Qt6 GUI compilation and interactive behaviour still need desktop testing.

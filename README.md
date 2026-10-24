# CoderGirl IDE Stage 5.78 | 24 October 2026

**Drop-in update for Stage 5.77.1**

Replace exactly `gamefloweditor.cpp` and `splashscreenwidget.cpp` in your IDE source tree, then rebuild. No source-generation steps and no changes to your game files are necessary.

The Flow Debugger now detaches an embedded ARRAY GROUP when its header is dragged and released beyond its parent LOGIC GROUP frame. It remains intact, and can be dragged back into the parent.

See `STAGE5.78-DRAG-OUT-ARRAY-GROUP.md` for tests and limitations.

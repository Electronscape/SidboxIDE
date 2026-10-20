# Stage 3.95 — Start here

Complete archive: extract to a NEW source folder and rebuild in Qt Creator.

Changed-files archive: overwrite these six files in the IDE source root:

1. `gameanimationeditor.cpp`
2. `gameanimationeditor.h`
3. `gamedesigner.cpp`
4. `gamedesigner.h`
5. `gamedesigner_export.cpp`
6. `gamedesigner_project.cpp`

No firmware changes. This version was prepared from the complete Stage 3.94 package; the Qt6 GUI must still be compiled/tested on Fedora.

To use flip settings: Save the design, then F5 **Update and Compile**.

To fix Hurt animations in an existing game: Save the animation from **Player Animation Toolkit** to regenerate `player_anim.h`, then F5 **Update and Compile** to regenerate `maingame.c.txt`. If you own `main.c`, copy the corrected Hurt conditional from `maingame.c.txt` into your `main.c` (just like other manual generated example updates).

More details: `development/notes/STAGE3.95-ANIMATION-THEME-FLIPS-AND-HURT.md`.

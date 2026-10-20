Stage 4.16 - Checkbox and scrollbar sizing hotfix

Base: Stage 4.15.
Only production change: ideglobaltheme.h.
Checked and unchecked checkbox states render using identically sized 16x16 cached bitmaps.
Qt scrollbars now explicitly use 10px width/height, including dropdown popup lists.
See Stage4.16-Checkbox-and-Scrollbar-README.md for details.

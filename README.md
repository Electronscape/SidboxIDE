# CoderGirl IDE Stage 5.125.251026

Qt6 compilation hotfix for Stage 5.124 Trigger / Switch row controls:
three `connect()` calls now use the linked-action table as context, avoiding
an accidental capture-by-copy of the noncopyable `QDialog`.

Only `gamedesigner.cpp` and `splashscreenwidget.cpp` change. See
`INSTALL-STAGE5.125.txt` for exact instructions.

# Stage 5.24 — Adventure Editor Button on Top Toolbar

Based on Stage 5.23 (includes the Player Starts icon and Adventure missing-item reply).

## UI change

In `gamedesigner.cpp`, `SidboxGameDesigner::buildUi()`, the **Adventure Editor...**
button is now on the Game Designer action bar, immediately after **Create / Edit Player...**.
It was removed from the Game Resources sidebar. The existing click handler still
calls `openAdventureEditor()`.

Button sequence:

`Centre View on LCD` | `Tilemap Editor...` | `Create / Edit Player...` | `Adventure Editor...`

`Generate V1 Game Code...` and `Save Design` remain on that row to the right.

The splash build label in `splashscreenwidget.cpp` is now `5.24.221026`.

## Test

1. Build the IDE and open a world in Game Designer.
2. Confirm the Adventure Editor button follows Create / Edit Player on the top action row.
3. Confirm there is no Adventure Editor button below Game Resources.
4. Click the top button and verify it opens the same Adventure Editor.
5. Check the IDE tab does not change window size unexpectedly when switching between Game Designer and C code.

No game code generation or SIDBOX rebuild is needed for this change.

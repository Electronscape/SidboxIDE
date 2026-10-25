# Stage 5.92: Clarify item-locked Trigger FIRE2 control (24 October 2026)

**IDE-only change.** The actual game runtime and object serialization are unchanged.

In **Game Object Properties → Trigger / Switch**, choosing a required inventory item now disables the checkbox **Require FIRE2 while touching (otherwise activate on touch)**. A tooltip explains that inventory-item interactions already use FIRE2 nearby to open the item selector.

Selecting **No required item (ordinary trigger)** enables the checkbox again. Its previous checked/unchecked value is preserved even while disabled. Switching the object type away from Trigger disables it as before. This applies both when opening a saved object and while changing settings in the dialog.

Modified: `gamedesigner.cpp`, `splashscreenwidget.cpp`.
Build: `5.92.241026`.

**Test in IDE:**
1. Open a Trigger's Game Object Properties with **No required item**. Check/uncheck Require FIRE2: it should remain enabled.
2. Choose an inventory item. Require FIRE2 should turn grey, tooltip should explain why, Interaction reach and Consume should enable.
3. Switch back to No required item. Require FIRE2 should enable with its original check state intact.
4. Switch the object type away from Trigger and back; confirm enabled states update correctly.
5. Open an already configured item-locked Trigger: Require FIRE2 must start disabled.

No `.sbgm` regeneration or game rebuild is needed, since only the IDE dialog changes. Rebuild the Qt6 IDE to test it. No Qt6 development headers were available in this environment, so compilation is not claimed.

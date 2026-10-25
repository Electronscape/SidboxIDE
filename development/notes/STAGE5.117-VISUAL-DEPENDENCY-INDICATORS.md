# Stage 5.117.251026: Adventure Editor guard indicators

The Stage 5.116 validation layer now has a **visible state**: green border means an optional/conditional field can be edited; red border with faded tint means an unmet prerequisite. The original hints and warnings remain.

All controls that previously called `setEnabled()` in `gameadventureeditor.cpp` are tagged when they first encounter the enabled/disabled decision. This includes nested modal editors. The tag is `adventureGuard=true` and is never written to a `.sbgm`. The QApplication global theme has **property-scoped** CSS selectors, keeping buttons outside this editor unchanged. The property is set once with style repolish to ensure dynamic creation also displays its state. Subsequent enabled-state changes use ordinary Qt stylesheet pseudo-states, with constant border widths to avoid layout shifts. Qt-native checkbox artwork stays intact.

Dark and light styles choose different status border hues and mildly tint the backing colour using the active theme palette. Not every available IDE control turns green, only dependency-controlled fields. The top of the main Adventure Editor, dialogue editor and GIVE dialog explains the status colours.

No runtime changes or world migration. Tested native thought bubble C cases, object/NPC crossworld, dialogue sequence and dialogue modes. Qt6 graphical build remains for developer machine.

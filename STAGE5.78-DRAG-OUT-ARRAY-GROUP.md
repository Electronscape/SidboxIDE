# Stage 5.78 (24 October 2026): Drag array groups out of logic groups

## What changed

- Drag an **ARRAY GROUP nested inside a LOGIC GROUP** beyond the parent's border and release the mouse. It automatically becomes its own top-level array group in the same world.
- Release inside the parent and the array remains nested at its new position.
- A 12-pixel release tolerance avoids unintentional unnesting exactly at the border.
- Array group contents, links, expansion state, and screen position remain intact.
- Drag the detached array back onto a LOGIC GROUP to nest it again, using the existing Stage 5.77 behaviour.
- Only nested array groups can cross the parent boundary. Manual group mini cards retain their existing constraints.
- The saved parent relationship and offsets are updated in `<project>/.sidbox-flow-layout.json` only. No game data or `.sbgm` files are edited.

## Modified files

- `gamefloweditor.cpp`: nested group drag-out, release hit-testing, deferred detach and save, help text.
- `splashscreenwidget.cpp`: `Build: 5.78.241026`.

Based on Stage 5.77.1 (includes the `QJsonObject::constBegin()/constEnd()` compilation fix).

## Fedora test

1. Replace `gamefloweditor.cpp` and `splashscreenwidget.cpp`, rebuild your IDE.
2. Open the Game Flow Debugger and expand a LOGIC GROUP containing a nested ARRAY GROUP.
3. Move the ARRAY GROUP's header within the logic frame, release: it should stay inside.
4. Drag the same header beyond the frame edge, release: the array becomes an independent group at that position.
5. Expand/collapse it, close and reopen the diagram, verify it remains independent and its contents are present.
6. Drag that array back onto the logic frame: it should join again.
7. Check that regular mini cards still cannot be pulled outside and the two opposite-direction wires remain separate.

## Verification / limitations

30 static/model regression checks passed, including saved-layout scenarios using existing Tiny Red Riot group IDs, geometry boundaries and code preservation checks. This environment does not have Qt6 developer libraries, so an actual Fedora Qt6 compilation and mouse-interaction test still need to be performed.

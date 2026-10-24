# CoderGirl Stage 5.89 (24 Oct 2026)

## Flow debugger: wires behind cards, plus Dialogue Choice inspector

### Connection stacking

- Scene-level links, including **links between different groups**, now stay underneath all top-level cards. Previously a cross-group link was sometimes parented to one group and came forward when its group came forward.
- A link wholly inside a group is parented to the **closest common group**, so it stays visible over that group's background but below its member cards.
- Group headers have an opaque themed 70-pixel header strip above internal wiring, so even when a connection passes behind the header the title stays readable.
- Nested array groups have the same protected headers. Their internal mini cards stay above their own wires.
- Red→green directed links, reciprocal lanes, click-to-front, drag into/out of a group, and selected-link highlighting are preserved.

### Dialogue Choice double-click flow

Double-click a **Dialogue Choice** card in the main Logic Flow debugger. This works for standalone cards and cards inside expanded groups.

A separate read-only window displays:
- Incoming saved links (parent dialogue, required/taken items, exchange requirements) on the left.
- The selected choice, full stored description, player choice text, NPC reply and saved flags in the centre.
- Outgoing saved links (next/missing/wrong/partial/repeated-wrong dialogue, gifts, NPC appearance and object actions) on the right.

Every relationship is shown from the **actual graph built from saved `.sbgm` data**, with the original edge label on its destination/source card. A choice with several conditional outcomes shows separate branches; the window does not imply which branch will execute. Cards grow vertically with content to avoid overlap.

Mouse wheel zooms; Alt+drag or middle-drag pans; Fit Flow restores the overview. The inspector does **not** edit dialogue or persist its layout.

### Files changed

- `gamefloweditor.cpp`: scene layer correction and dialogue choice inspector.
- `splashscreenwidget.cpp`: `Build: 5.89.241026`.

No changes to game runtimes, world files, `main.c`, assets, generator output, or `.sidbox-flow-layout.json` format.

### Validation

19 static/model checks passed against Stage 5.88 and the real saved Future Kim wrong-offering chain (four separate repeat destinations). This environment lacks Qt6 development headers, so the GUI hasn't been compiled or tested interactively here. Rebuild on Fedora and try a cross-group link, expanded group and a Dialogue Choice double-click.

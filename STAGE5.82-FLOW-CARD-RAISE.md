# Stage 5.82: Flow Debugger card stacking

**Build:** `5.82.241026`

## Behaviour

- Left-click any flow card to bring it in front of overlapping cards.
- Clicking its text, artwork, editable group title, or expand/collapse header also raises the card.
- For cards/array groups embedded inside a logic group, bring both the clicked child and its containing groups forward. Nested cards remain inside their original parent.
- Does not change grouping membership, positions, connections, game files, or saved flow layout.
- Z-order is transient in the current debugger session and resets on redraw/reopen. Clicking brings the chosen card forward again.
- Right-click, blank-area rubber-band selection, pan, drag-out, two-way links, and group editing are left unchanged.

## Files

- `gamefloweditor.cpp`
- `splashscreenwidget.cpp`

## Test on Fedora

1. Open Flow Debugger and overlap two free cards. Click the visible portion of the lower card. It should come to the front.
2. Overlap two expanded logic groups. Click a member inside the lower group. The whole containing group should rise, and the selected member should rise within it.
3. Click on a group title and an array's +/- control. Selection/title editing/expand-collapse should still work.
4. Drag an array into a logic group, then back out. Check both operations still work, and that wires remain behind cards.

**Verification limitation:** Qt6 development libraries are unavailable in this environment, so the source change has not been compiled here. Build and interactively test in Fedora.

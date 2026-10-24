# Stage 5.51.231026 — Logic Flow navigation, layout and stability

## What's changed

- In **Game Designer → Logic Flow**, scroll the **mouse wheel** to zoom in/out at the cursor. Wheel zoom is available even after pressing **Fit Graph**. Zoom is bounded between 4% and 500%, preventing extreme transformations.
- **Left-drag a card** to move it. Edges and arrowheads follow the card in real time. **Drag empty canvas** to pan; middle-drag pans as well.
- Card positions are saved automatically **after each drag** in `<game project>/.sidbox-flow-layout.json`. Positions are keyed by stable node IDs. Reopening the editor, reloading designs or changing world filters restores them. The `.sbgm` files remain completely untouched.
- **Clean Layout** clears all saved manual positions, restores the now more spacious six-column automatic layout and saves the reset. **100%** resets zoom; **Fit Graph** shows all nodes.
- Fixed a **potential crash on closing the Logic Flow window**: the old code kept a scene selection callback alive while its captured local graph and UI state were being destroyed. The new code explicitly disconnects all dialog callbacks and clears the scene before local state goes out of scope. This is a source-confirmed lifetime hazard, though no stack trace was supplied to establish whether it caused the specific reported crash.
- Improved scene handling: no item index rebuild while dragging, bounded zoom, no scene-rect recalculation during every pointer movement, and `SmartViewportUpdate` for more efficient redraws.
- The editor opens maximized, still uses sharp-corner cards and text stripes rather than big icons. No graphics assets/PPBs or generated game C are modified.

## Test on Fedora

1. Apply Stage 5.51 over Stage 5.50 and rebuild the IDE.
2. Open Game Designer → Logic Flow; click **Fit Graph**, then rotate the wheel *up* a few notches. Use **100%** if needed.
3. Left-drag a card, check the line and arrow move with it; close and reopen Logic Flow. The layout should persist.
4. Pick **World1** only, then **All Worlds**: previous card positions should be retained.
5. Click **Clean Layout**: cards return to automatic positions and remain there after reopening.
6. Try multiple cycles of Fit Graph, wheel zoom, card drag, filtering and reloading.

If the IDE still crashes, a GDB stack trace is needed to identify the exact cause. The portal warning `Could not register app ID: App info not found for 'SidboxIDE'` is generally separate from a process crash and should not be taken as its cause by itself.

## Notes

- The layout file is intentionally separate from the world files and safe to delete; doing so resets all custom card positions.
- Saving a card arrangement does not alter any gameplay data or the generated runtime.
- Qt6 GUI build and interactive crash reproduction are not possible in this environment because Qt6 development headers are unavailable. Source-level verification is included with this stage; full validation is on Fedora.

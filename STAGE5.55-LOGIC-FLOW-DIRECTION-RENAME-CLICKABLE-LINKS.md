# SIDBOX / CoderGirl Stage 5.55.231026

## Scope

This release modifies **only the design-time Logic Flow editor** and splash build label. No SIDBOX runtime, `.sbgm` format, HUD code, PPBs, or firmware components are changed.

## Logic Flow changes

1. **Expanded manual-group external connections**: links to other dialogue cards, inventory items, and other graph nodes now attach to the actual card inside an expanded manual group. Wires are parented to the manual group so they draw over its background and under its mini cards. Collapsed groups and automatic array groups keep aggregated connections.
2. **Direction colours**: each wire starts red at its saved `from` endpoint and ends green at its saved `to` endpoint. The arrowhead is green. Direction comes from the saved logic relation, not horizontal position: a prerequisite link can point backwards in screen space.
3. **Green trace (no dim)**: toolbar checkbox colours links related to the selected card(s) solid green while leaving other cards and wires at normal opacity. The existing **Highlight selected links** (with dimming) remains and takes precedence when selected.
4. **Click a connector**: the 12-pixel invisible hit area makes lines easier to click. Clicking selects BOTH endpoint cards and shows the relationship in the details panel. Connector art is not included in rubber-band selection, preserving Ctrl+G grouping.
5. **In-place rename**: double-click the text of a **manual** group to edit its name in the group header. Enter commits; Escape cancels; focus loss commits. Renamed titles persist in `.sidbox-flow-layout.json`, with no change to `.sbgm`. Automatic array group names are derived from source resources and remain fixed.

## Verification

- Source-level structural checks pass for external manual-group connection routing, link direction gradient and non-dimming highlighting, clickable connectors, inline group-title persistence, unchanged array-group handling, and splash version.
- GameTest3 dialogue data was used to sanity-check the available references.
- The Qt6 IDE **was not compiled or exercised interactively** here because Qt6 headers/libraries are unavailable in this environment. Fedora GUI compilation and clicking/dragging are the acceptance tests.

## Install and test

1. Apply the drop-in over **Stage 5.54** (or use the full source) and rebuild the Qt IDE.
2. Open Logic Flow, expand a manual group containing a dialogue or inventory card linked to an external node. The link should reach the inner card.
3. Double-click the manual group's name, rename it, press Enter, then close/reopen to verify persistence.
4. Click a wire. Both endpoint cards should select. Try **Green trace (no dim)** and the original **Highlight selected links** separately.
5. Rubber-band several cards and Ctrl+G to verify grouping is unchanged; expand an automatic array group and confirm its simpler presentation remains.

No game-world regeneration is required.

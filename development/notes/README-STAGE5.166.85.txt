SIDBOX / CoderGirl IDE Stage 5.166.85 (28 October 2026)
Visual Nodes: Bring Selected Card to Front + Standardised Socket Alignment

WHAT CHANGED

1. Left-click or right-click a node card, its socket, its fold button, or an
   embedded editable control: the WHOLE card and its children are raised above
   other cards. Existing paths/wires remain behind the cards.
2. Dialogue answer sockets now follow their REAL text-control rows AFTER the
   Qt form is embedded. This removes the orphaned outputs along the bottom
   edge when expanded cards are laid out differently from their initial size.
3. Normal (purple), missing-item (amber) and GIVE (teal) answer outputs share
   consistent right-border alignment and compact 15 px spacing per answer.
4. GIVE wrong-item and repeated-offer outputs still align to their respective
   destination dropdowns, after Qt's final layout.
5. NPC opening/after-helped square inputs align to their corresponding
   conversation selectors. All other square inputs and circular outputs sit
   on the respective left/right card borders. Connection lines land at the
   visible sockets, instead of provisional fixed offsets.
6. Collapsed card sockets retain the existing stacked layout and opaque
   hollow-socket appearance. All graph gameplay relationships remain intact.

INSTALL
1. Back up your 5.166.84.1 IDE source and current game projects.
2. Extract this FULL-SOURCE archive over Stage 5.166.84.1.
3. Rebuild CoderGirl and check splash Build: 5.166.85.281026.
4. In Forest/World1 Visual Nodes, overlap two dialogue cards. Click the lower
   exposed card and verify it comes to the front.
5. Expand Dialogue #0 (Future Kim) and verify purple/amber/teal outputs sit
   beside Answer 1. Open the GIVE card: all five outputs should align to their
   own dropdowns, including after collapse/expand and Tidy.
6. Try Ctrl+Z/Ctrl+Y, moving/collapsing cards and saving/reopening .vsgm.

VERIFICATION
Source-contract and relevant regression tests passed (22/22).
No Qt desktop build or graphical mouse test was possible in this environment.
The actual Qt desktop rebuild/visual acceptance remains necessary.

No game exporter, runtime C generation, world-data schema, or main.c changes.
There is no need to regenerate the game for this visual-only update.

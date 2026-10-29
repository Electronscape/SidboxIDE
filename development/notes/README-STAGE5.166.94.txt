SIDBOX CoderGirl Stage 5.166.94 - Conversation group resizing and dragging (29 Oct 2026)

Visual Nodes fixes:
- Collapsed flow group becomes a compact header at the SAME origin, with [+] visible.
- Drag a group by its header to move the real dialogue and GIVE cards together.
- Internal node moves, individual expand/collapse and GIVE editor changes update group frame bounds.
- Nested interactive dialogue widgets remain independently movable/editable.
- Live drag maintains previously implemented immediate wire endpoint updates.
- Group state remains view-only in .vsgm; Adventure and game code generation untouched.

IMPORTANT: A dialogue shared by two conversation roots remains one real editable card;
              moving either group will also move shared cards.

Desktop Qt build and user verification required.

Stage 5.166.49.281026: Visual Nodes connected-card deletion and wire consistency.

- Delete a selected object, Trigger, NPC or purple Show Dialogue card (keyboard,
  right-click, or right-hand Delete Selected button).
- Automatically disconnect the affected Trigger actions. Underlying .sbgm
  objects and dialogue entries remain intact. Connected deletions require a
  confirmation; disconnected graph-only cards do not.
- Delete from the VISIBLE NODES list too, while keeping normal Delete text
  editing in Show Dialogue's embedded input widgets.
- Right-click purple dialogue links to Remove Connection just as with normal
  object-action links. Route their curves smoothly without vertical hairpins.
- Preserve remaining newly orphaned cards as explicitly placed .vsgm cards.
- Read-only Logic Flow and runtime code unchanged.

See development/notes/INSTALL-STAGE5.166.49.txt.

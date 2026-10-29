CoderGirl IDE Stage 5.166.98 - 29 Oct 2026

Fixes direct TRUE/FALSE logic reconnection to an existing Show Dialogue card.
Two authored independent logic actions can now visibly share the same editor card,
using graphDialogueRoutes as a .vsgm-only hint. Actual target dialogue IDs remain
in .sbgm. Undo/redo retains the hint; stale targets fall back to an owned card.

Project file icons: .vsgm uses tree_vsgm.png from the external icons/ directory
(if provided by the user); falls back to toolbar_gamedesigner.png otherwise.
No generated runtime changes.

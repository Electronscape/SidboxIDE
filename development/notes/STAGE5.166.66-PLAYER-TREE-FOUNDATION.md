# Stage 5.166.66 - PLAYER tree foundation (28 October 2026)

Implemented in gamevisualnodes.cpp, GraphDialog::showInsertTree:
- Existing `goto_world` resources now appear under `PLAYER / World Transitions` when adding an unconnected world node.
- Goto World resources are omitted from action-target linking menus. `goto_world` is an interaction transition, not a valid `enable`/`disable`/`toggle` Game Object action target.
- Existing resource IDs, graph documents, and gameplay runtime code have not been rewritten.
- Updated splash-screen build string.

Important limits: this is only a first UI tree foundation. It does NOT add PLAYER Boolean inputs or graph TRUE/FALSE world-change actions. Existing Goto World sprites continue working through their existing interaction semantics. No claim of hardware validation.

Next implementation: add typed PLAYER action nodes with explicit world name/start marker, validate against the project's exact world registry, serialize separately from Game Object actions, generate `gameworlds_request_at(world, start)` for graph branches, and render proper independent graph cards/wires. Add player-state Boolean inputs separately and ensure evaluation occurs on player state changes rather than only Trigger firings. Preserve working Stage 5.166.65 graphs without altering their stored schemas.

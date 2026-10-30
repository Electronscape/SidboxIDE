CoderGirl IDE Stage 5.166.123.301026
Flow Debugger: correctly display runtime PLAYER and QUEST EVENT actions.

The Flow Debugger previously interpreted a valid saved action such as
stopLift -> @player_time:0 (ENABLE) as a missing placed Game Object.

Changed file: gamefloweditor.cpp, loadGraph()
- Recognize virtual PLAYER/Spotlight, PLAYER/Weather 0..3,
  PLAYER/Time 0..2, PLAYER/World (existing exact world only), and
  QUEST EVENT (authored event objectives only).
- Resolve primary and extra action targets to read-only named nodes.
- Display meaningful Trigger action labels, not "Missing object".
- Link virtual quest-event commands to the project-wide Quest Event card.
- Continue warning for nonexistent IDs and forbidden actions, including
  TIME, WORLD, and QUEST EVENT operations other than ENABLE.

No save format or generated world/runtime code changes.
Existing user's project does not need alteration or re-export.

Validation:
- Stage 123 source/fixture test passed (actual saved stopLift ID confirmed).
- Stage 121 native quest save/progression test passed.
- Stage 122 native Journal D-pad renderer test passed.
- Qt6 development libraries missing in this environment: full IDE build
  and screen-level checking must be performed on user's Fedora installation.

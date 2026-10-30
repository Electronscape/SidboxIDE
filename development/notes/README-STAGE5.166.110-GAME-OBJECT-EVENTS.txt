SIDBOX CoderGirl IDE — Stage 5.166.110.291026
Game Object named event outputs for Visual Nodes
29 October 2026

BASELINE
Stage 5.166.109 save-identity-protection source. Copy source files from
this release into that source tree or use the complete source archive.

NEW VISUAL NODE OUTPUTS
  Breakable       ON HIT and ON DESTROY (separate event sockets)
  Collectable     ON PICKUP
  Hazard          ON PLAYER HIT
  Goto World Door ON ENTER
  Save Checkpoint ON SAVE
  Moving Platform ON ARRIVAL (spline waypoint/segment event)
  Stompable Enemy ON HIT; existing ON DEFEAT retained

Drag gold named-event outputs onto compatible Game Objects or PLAYER
commands for the existing Enable/Disable/Toggle action semantics. Multiple
actions are stored in order, limited to 64 per named event. Edit or remove
links through Visual Nodes. The corresponding read-only linked-event summaries
appear in Game Object Properties. Normal .sbgm world saves preserve links.

GENERATION / EXECUTION
- Uses the existing generated target-action dispatcher. Does NOT introduce
  a second gameplay logic engine.
- Independent AND/OR/NOT logic is re-evaluated when named event actions
  actually change a graph input, with per-event pulses (HIT and DESTROY
  cannot trigger one another accidentally).
- The saved-game payload and Stage 5.166.109 save-layout identity scheme
  remain unchanged.
- ON SAVE runs only after the TFCard world save completes successfully, not
  when a checkpoint is touched or a player cancels the save picker.
- ON ARRIVAL observes spline waypoint / segment transitions while moving.
- ON ENTER dispatches before the requested world change is applied.

KNOWN BOUNDARIES / NOTES
- Named-event outputs currently target Game Objects and supported PLAYER
  actions. There is not yet a direct event-output-to-Dialogue connection;
  existing Trigger and logic dialogue branches are still available.
- ON SAVE actions occur AFTER the save write; those side effects are not in
  that same saved snapshot, unless a subsequent save captures them.
- An event link to an invalid target fails export with an explanation rather
  than producing a silent no-op.
- Source regression tests and generated-rule combination checks passed.
  Native C microtests passed. Qt GUI compilation and actual STM32H743/TFCard
  runtime acceptance were NOT available in the build container.

SUGGESTED HARDWARE TESTS
1. Compile IDE on Fedora. Create breakable with 2 hits to destroy and connect
   ON HIT -> disable Decoration A; ON DESTROY -> enable Decoration B. Hit once,
   verify A only; hit final time, verify B. Save/reopen .sbgm and retest.
2. Connect Collectable ON PICKUP -> enable a Decoration, then collect it.
3. Connect Hazard ON PLAYER HIT -> change a switch; test collision with player.
4. Connect Moving Platform ON ARRIVAL -> toggle a visible Decoration; traverse
   the spline and verify it fires at knot boundaries.
5. Connect Goto World Door ON ENTER -> alter global/player state; enter door.
6. Connect Save Checkpoint ON SAVE -> toggle Decoration; cancel once then
   save successfully, confirming only the successful save fires it.
7. Connect Stompable ON HIT -> alter Decoration and retain ON DEFEAT action;
   verify distinct events across nonfatal/final stomps.
8. Verify earlier Trigger/Enemy state/loot logic and Stage109 save identity.

FILES CHANGED
  gamedesigner.cpp, gamedesigner.h, gamedesigner_export.cpp,
  gamedesigner_project.cpp, gamevisualnodes.cpp, gameworldsnapshot.h,
  splashscreenwidget.cpp,
  idelibs/codehelpers/game/gameworlditems.rulec,
  idelibs/codehelpers/game/gameworlditems.ruleh,
  idelibs/codehelpers/game/gameworlds.rulec,
  idelibs/codehelpers/game/worldobjects.rulec,
  idelibs/codehelpers/game/worldobjects.ruleh.
  development/tests/test_stage5166_110_gameobject_events.py,
  development/tests/test_stage5166_110_template_render.py.

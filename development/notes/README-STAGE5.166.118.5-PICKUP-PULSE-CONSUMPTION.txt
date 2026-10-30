SIDBOX IDE Stage 5.166.118.5.301026
ON PICKUP event pulse consumption hotfix

Based on full Stage 5.166.118.4.

Symptoms:
  kim[2] ON PICKUP + stopLift STATE ON -> AND TRUE -> Dialogue
  can display the dialogue twice for one collectable pickup.

Root cause:
  gameworlditems_check() sets cg_named_pickup_sources and calls
  cg_run_trigger_actions(), but leaves the pickup pulse set when returning.
  Subsequent gameworlditems_trigger() or other dispatcher calls can see that
  stale pulse and repeat event-dependent actions.

Fix:
  idelibs/codehelpers/game/gameworlditems.rulec
    Consume/clear cg_named_pickup_sources immediately after ON PICKUP
    graph evaluation, before returning from gameworlditems_check().
    The second dispatcher invocation cannot replay the same event.
  splashscreenwidget.cpp
    Bump splash build ID.

This is a narrow fix, NOT a global event/action/dialogue queue.
It does not alter saved .sbgm graphs, UUIDs, save-game payload, game object
settings, the graph UI, or the action semantics of genuine new events.

Regression test:
  development/tests/test_stage5166_118_5_pickup_pulse_once.py
    Native C compilation of the same pickup-dispatch and pulse-clear fragment:
    one pickup -> one action, a subsequent Trigger dispatch -> no replay,
    a second genuine pickup -> exactly one new action.

Suggested hardware test:
  Enable stopLift virtual switch, then collect kim[2].
  The AND TRUE dialogue should appear once. Re-enter/leave the Trigger area;
  it should not replay the pickup-only dialogue without another pickup.

Future recommendation (NOT included):
  Central event queue -> deterministic logic evaluation -> action queue,
  plus a separate dialogue queue. Keep the existing gate UI and schemas.

Full Qt IDE build and SIDBOX hardware validation were not available here.

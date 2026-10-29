SIDBOX CoderGirl IDE Stage 5.166.63.281026
========================================
Independent Visual Logic: live Game Object state change detection

Why:
  The independent graph is stored on its owning Trigger. The Stage 5.166.62
  generator predicted which other Triggers might change that graph's inputs
  from configured target links. This is brittle for multi-Trigger puzzles.

What changes:
  - At the start of cg_run_trigger_actions(), snapshot the 'active' state of
    each Game Object directly read by an independent graph.
  - Run all ordinary Trigger actions.
  - Evaluate an independent graph when its owning Trigger fires OR when any
    of its watched Game Object states actually changed in this invocation.
  - Capture all graph node results before running TRUE/FALSE branch actions.
  - The watched objects are deduplicated and emitted in stable ID order.
  - Game Object Properties labels the older separate state condition as
    'Legacy Trigger state condition (optional)' so it cannot be mistaken for
    a missing input tick box in the independent graph.

Important:
  - Your 'logic1 [AND]' independent graph already had logictest[0] and [1]
    ticked in the supplied screenshot. The empty legacy panel is unrelated.
  - No .sbgm or .vsgm format changes, no graph reconstruction needed.
  - This update changes the generated world C, not the game-owned main.c.
  - Existing New Game, title/death and save/reset logic is untouched.
  - This fix targets state changes caused by ordinary Trigger actions in the
    same update. It is not yet a general continuously evaluated graph system.

Apply over:
  Stage 5.166.62.

Build/test:
  1. Rebuild the IDE (splash should read 5.166.63.281026).
  2. Open your existing world, do NOT tick the empty legacy condition pane.
  3. Save the Visual Nodes graph if you made any unsaved edits.
  4. Update ALL Worlds / Update Game Project; rebuild the V1 .app.
  5. On SIDBOX, trigger switch A then B: AND TRUE should enable object 2.
     Turn either A or B off: AND FALSE should disable object 2.
  6. If the output still doesn't change, supply the CURRENT .sbgm plus
     regenerated gamehelpers/gameworlditems.c. They will show whether the
     expected branch/action C was actually emitted for your puzzle.

Validation:
  Native GCC C11 live-state regression passed (both switch orders, off/on,
  no idle event repetition); selected legacy Boolean/graph/Decoration and
  title/save reset tests passed. Full Qt6 GUI compilation and actual SIDBOX
  hardware behaviour remain unverified in this environment.

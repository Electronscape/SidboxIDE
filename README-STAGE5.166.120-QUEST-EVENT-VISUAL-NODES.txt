SIDBOX / CoderGirl IDE Stage 5.166.120 (30 October 2026)
=====================================================
BASELINE: IDE 30-10-2026 - 1633.tar.gz (5.166.119.1.301026)
SCOPE: Quest Editor "Event signal" objectives callable directly from Visual Nodes.

EDITED:
  gamevisualnodes.cpp
  gamedesigner_export.cpp
  splashscreenwidget.cpp
ADDED:
  development/tests/test_stage5166_120_quest_event_nodes.py
  this changelog

WORKFLOW
  1. In Quest Designer, add an objective whose Condition is "Event signal".
     Give the signal a stable ID, e.g. guardian_defeated; save Quests.
  2. Reopen Visual Nodes to refresh the project-wide quest target catalog.
  3. Drag a GOLD action output such as Enemy ON DEFEAT, Breakable ON DESTROY,
     Trigger ON ACTIVATE, or BOOLEAN/AND/OR TRUE/FALSE to empty canvas.
  4. Choose "Quest Events" > "Quest: ... / ..." (the real quest objective).
     The new green QUEST EVENT / SIGNAL card has one INPUT and no OUTPUT.
  5. Save Graph + World, regenerate the game and test on SIDBOX hardware.

DATA & RUNTIME
  - Objective definitions and signal IDs remain only in .codergirl/quests.json.
  - Real action links are persisted in the source world's .sbgm, existing
    Linked Actions, eventActions or logicNodes fields. .vsgm is layout only.
  - Target representation: @quest_event:<exact authored Event signal target>.
  - Target supports only the one-shot 'enable' command (UI: Signal), never
    Disable/Toggle or RESULT state bindings.
  - Exporter validates the signal against authored quest event objectives.
    Deleting/renaming an objective target invalidates old graph wires at build.
  - The existing bounded action FIFO calls gameworlds_quest_event(signal).
    The quest manager handles current step, active-quest gating, journal and
    persistent quest state, including game save/load across worlds.
  - Quest signals are excluded from graph initial-state synchronisation.
    Entering a world/restoring a checkpoint must NOT complete quest steps.
  - No Game Object sprite, memory allocation, save format, or new quest
    runtime API was added; existing non-quest node behaviour is unchanged.

VALIDATION IN THIS ENVIRONMENT
  - New 5-case source contract regression: PASS.
  - Existing Stage 119 action/event FIFO native C tests: PASS (4 action tests).
  - Existing native quest/save world-manager regression: PASS, compiled C.
  - Previous trigger socket geometry regression: PASS (4 geometry tests).
  - Some historical suites contain hard-coded older SPLASH version checks;
    those assertions must be updated for newer releases.
  - Full Qt IDE compilation and real STM32 hardware execution NOT available
    in this environment. Please test those before treating this as accepted.

NOTE: This stage adds "Event signal" objective support. Legacy Adventure
numeric event IDs and automatic dialogue choice objectives remain separate;
no change is made to how those objective kinds work.

STAGE 4.47 — World Items rule function layouts

Baseline: Stage 4.46 (21 Oct 2026). No additional .inc files.

Files changed:
  gamedesigner_export.cpp
  idelibs/codehelpers/game/gameworlditems.rulec

The rulec now declares the generated World Items functions for:
  init, update, before/after player hooks, pickup checks,
  triggers, drawing, and optional audio positioning.
The Qt generator still creates game-specific code for the function bodies.
Optional before/after, pickup and trigger definitions are controlled by
HAS_WORLDS / HAS_PICKUPS / HAS_TRIGGERS compile-time #if flags.

The existing World Items API and function implementation bodies are preserved.
The generated file may have different blank lines and #if directives.

Installation:
  Use the complete archive, or copy the two changed files to the
  corresponding paths in your IDE source tree.
  Rebuild IDE, regenerate World Items, compile the game and test on SIDBOX.

Checks here: rule placeholder map completeness (16/16); no function
signatures emitted by Qt; no GENERATED_RUNTIME mega-placeholder.
NOT VERIFIED: Qt IDE compilation, generated game compilation, SIDBOX hardware.
Make a backup before trying this on your working project.

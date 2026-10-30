SIDBOX CoderGirl IDE - Stage 5.166.119.301026
EXPERIMENTAL: EVENT / LOGIC / ACTION / DIALOGUE QUEUES
=======================================================
BASE: Stage 5.166.118.5.301026

WHAT CHANGED
- The generated world object runtime uses a fixed-size (128 entries)
  source/type/sequence-tagged event FIFO. Fired bits are collected and consumed
  once, rather than being treated as an enduring shared event state.
- The generator allocates fixed command IDs for generated target actions and
  linked logic TRUE/FALSE actions; these execute via an ordered fixed-size
  128-command FIFO (Enable, Disable, Toggle, travel, spotlight and other
  existing target actions keep their previous semantics).
- The established Boolean / AND / OR / NOT evaluator continues to evaluate
  the saved logic nodes. Event-dependent paths are evaluated against the
  current one-frame event. Numbered sockets and Visual Nodes appearance stay.
- Generated dialogue calls enter the command queue and the Adventure runtime
  also maintains a separate 16-entry FIFO so overlapping messages are shown
  one after the previous conversation closes, rather than interrupting it.
- Event/action queues are transient, reset when the generated world is
  initialized or remotely reset, and are never included in TFCard snapshots.
- Capacity/cycle guards report counts through the new *_overflow_count APIs.
  Overflow intentionally rejects/drops commands; do not ignore a nonzero count.
- World snapshot symbol namespacing covers the new public queue diagnostics.
- The IDE splash version is updated; existing .sbgm graphs are not migrated.

FILES CHANGED
  gamedesigner_export.cpp
  gameworldsnapshot.h
  idelibs/codehelpers/game/gameworlditems.rulec
  idelibs/codehelpers/game/gameworlditems.ruleh
  idelibs/codehelpers/game/adventureruntime.rulec
  idelibs/codehelpers/game/adventureruntime.ruleh
  splashscreenwidget.cpp
  development/tests/test_stage5166_119_queued_runtime.py (new)

KNOWN LIMITS / SAFETY
- This is a source-level test build. Full Fedora/Qt build, generated game
  compilation, dual-world link, real TFCard save/load and SIDBOX hardware
  have NOT been run here.
- Some Adventure quest progress notifications and older non-visual dialogue
  paths retain their established synchronous callbacks. They are not all
  global queued commands yet. The quest system itself is preserved.
- Logic DAGs still have the existing per-Game-Object ownership rules. This
  patch does NOT introduce arbitrary node-to-node links across owners.
- The new queue machinery may initially INCREASE code/RAM size. No binary
  reduction is promised. Each world has a 128x16-bit command ring, a
  128-record event ring, and dialogue FIFO state.
- Queue capacity overflow is observable in C but has no IDE warning panel.
- Existing save-layout identity checks remain; queues are NOT serialized.
  Back up previous TFCard slots before trying a newly generated multiworld game.

VERIFY ON FEDORA + SIDBOX
1. Build IDE in a clean build directory; splash must say 5.166.119.301026.
2. Open a COPY of the Stage 118.5 project. Regenerate every .sbgm world,
   generate all runtime sources, compile/link the complete game.
3. Confirm ON PICKUP + virtual Trigger STATE ON -> AND -> dialogue runs once.
4. Fire two distinct dialogue requests in the same update. Confirm the first
   remains visible until dismissed, then the second opens.
5. Verify enemy HIT/DEFEAT, breakable HIT/DESTROY, lift ARRIVAL, checkpoint
   SAVE and door ENTER events, including multiple events in one frame.
6. Test TRUE/FALSE Enable/Disable/Toggle and a quest objective update.
7. Save, reload, transition between two worlds, reload again. Verify there
   are no stale events/dialogues carried over to the destination world.
8. Compare generated ELF/BSS size and 50Hz rendering against Stage 118.5.

TESTS RUN IN SOURCE ENVIRONMENT
- New Stage 119 native C tests: action FIFO, event FIFO, pickup-only world,
  dialogue FIFO, and generator/serialization guards: 5 passed.
- 19 of 20 selected existing+new tests passed. The remaining assertion is
  an old Stage 114 test hard-coded to accept only Stage 114/116 splash versions.
- The Qt IDE and actual generated multi-world game were not fully compiled.

Rollback: keep the original Stage 118.5 full ZIP and your copied .sbgm project.

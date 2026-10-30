SIDBOX CoderGirl IDE Stage 5.166.118.1.301026
EXPORTER COMPILER HOTFIX

Issue: gamedesigner_export.cpp ~1727: `else` without a previous `if`.
Cause: the Stage118 Trigger-state graph watcher loop was inserted in between
       the existing `if(owner.objectType=="trigger")` and its corresponding
       `else if(owner.objectType=="enemy")`.

Fix: restore the Trigger/enemy `if` / `else if` consecutively, then run the
     virtual Trigger-state watcher loop. No runtime templates, save format,
     .sbgm graph data, wiring or gameplay semantics have been changed.

Changed files:
  gamedesigner_export.cpp
  splashscreenwidget.cpp (Build: 5.166.118.1.301026)

New regression:
  development/tests/test_stage5166_118_1_exporter_compiler.py
  Compiles and executes the actual activation-event control-flow block
  with simple stand-in QString types, guarding this exact syntax regression.

Full Qt compilation is not available here. Please build on Fedora and retain
your working Stage117 backup pending hardware validation of virtual Trigger states.

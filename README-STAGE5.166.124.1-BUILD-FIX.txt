SIDBOX CODERGIRL IDE: STAGE 5.166.124.1.301026
30 October 2026

Desktop Qt compilation hotfix for Stage 5.166.124.

File: gamedesigner.cpp, Player Profile editor (near line 1438)
Old: auto *updateCombatControls = [=] {
New: auto updateCombatControls = [=] {

This was a C++ type deduction error: a lambda expression is a callable object, not a pointer.
It does not change the body of the lambda, combat mechanics, runtime, input mapping or game project.
The splash build version was advanced; the focused Stage124 source-contract assertion was updated.

Stage124 combat test notes still apply. Full Qt6 IDE compilation and hardware
execution cannot be verified in this environment.

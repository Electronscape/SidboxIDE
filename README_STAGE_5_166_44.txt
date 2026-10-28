SIDBOX CoderGirl IDE Stage 5.166.44.271026

Visual Nodes Phase 2A Qt compilation hotfix.

FIX: gamevisualnodes.cpp, Visual Nodes Show Dialogue picker handler
(QComboBox::currentData().toInt(-1) incorrectly passed int to QVariant::toInt(bool *)).
The code now checks QVariant::isValid() and calls QVariant::toInt() without
arguments. The intentional -1 "None" and -2 "Create new" values still work.

Only gamevisualnodes.cpp and splashscreenwidget.cpp are changed in production.
No project, .sbgm, .vsgm, runtime rules, generated worlds, or main.c changes.
No game regeneration necessary. Apply hotfix over Stage 5.166.43 and rebuild
CoderGirl IDE.

Tested: Stage 5.166.44 QVariant signature C++17 check, Phase 2A contract,
Phase 1 graph/link/view checks. Full Qt6 GUI compile unavailable here.

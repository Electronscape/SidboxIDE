SIDBOX IDE Stage 5.166.106.2.291026 (29 October 2026)

Stompable Enemy / Random loot pool list order

FILE: gamedesigner.cpp
FUNCTION: GameDesigner::editGameObject(), refillEnemyLoot lambda

The selectable loot list is now ordered as follows:
  1. Eligible collectables, sorted alphabetically (case-insensitive, natural number ordering).
  2. Unavailable collectables, also sorted alphabetically.

Existing disabled-state warning icons, explanatory tooltips, unselectable
ineligible options, previously selected invalid references, and missing
reference warnings remain intact. No change to exported game logic.

FILE: splashscreenwidget.cpp
FUNCTION: SplashScreenWidget::buildUi()
Build string incremented to 5.166.106.2.291026.

TESTS:
  development/tests/test_stage5166_106_2_loot_order.py
  development/tests/test_stage5166_106_object_dependency_audit.py
  development/tests/test_stage5166_105_enemy_loot.py

12 source and native C regression tests passed, plus malformed C++
string/character literal scan. Qt6 toolchain is not installed in this
container: full Fedora GUI compilation still needs testing.

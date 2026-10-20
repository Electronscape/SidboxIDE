#!/usr/bin/env python3
"""Static boundary checks; runtime behaviour is tested by test_stage428_adventure.c."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
def text(p): return (root/p).read_text()
ui = text('gameadventureeditor.cpp')
assert 'QTabWidget' in ui and 'Dialogue Box Atlas' in ui
assert 'double-click' in ui.lower() and 'targetObjectId' in ui
assert 'Item name' in ui and 'NPCs' in ui and 'player' not in ui[:300]
project = text('gamedesigner_project.cpp')
assert 'm_adventure = obj.value' in project and 'obj.insert(QStringLiteral("adventure"), m_adventure)' in project
export = text('gamedesigner_export.cpp')
for term in ['gameadventure_setup()', 'game_adventure_input(', 'game_adventure_collect(item->kind)', 'game_adventure_draw(', 'gameworlditems_set_active', 'adventureruntime']:
    assert term in export, term
assert export.index('gameadventure_setup()') < export.index('game_adventure_input(')
assert export.index('game_adventure_input(') < export.index('game_adventure_draw(')
update = text('gamedesigner_update.cpp')
for term in ['hasAdventure()', 'gamehelpers/gameadventure.c', 'gamehelpers/gameadventure.h', 'adventureruntime']:
    assert term in update or term in export, term
assert 'main.c' in update and 'backup' in update.lower()
assert 'set(CMAKE_CXX_STANDARD 17)' in text('CMakeLists.txt')
assert 'gameadventureeditor.cpp' in text('CMakeLists.txt') and 'gameadventuregen.cpp' in text('CMakeLists.txt')
gen = text('gameadventuregen.cpp')
for term in ['gameworlditems_set_active', 'skin_cells', 'gameassets_find_ppb', 'on_event', 'QSaveFile']:
    assert term in gen, term
print('Stage 4.28 static integration checks passed')

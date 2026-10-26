#!/usr/bin/env python3
"""Stage 5.136 contracts: UI-only standardisation. Qt6 rendering needs Fedora."""
from pathlib import Path
import hashlib
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime
root = Path(__file__).resolve().parents[2]
base = Path('/mnt/data/ide_251026_stage5135')
read = lambda name: (root/name).read_text()
world = read('gamedesigner.cpp')
adv = read('gameadventureeditor.cpp')
anim = read('gameanimationeditor.cpp')
# Main editors and PPB preserve independent geometry and maximize-on-first-open.
for name,key in [
    ('gameadventureeditor.cpp','GameAdventureEditor/geometry'),
    ('gamefloweditor.cpp','GameFlowEditor/geometry'),
    ('gamehudeditor.cpp','GameHudEditor/geometry'),
    ('gametitlescreeneditor.cpp','GameTitleScreenEditor/geometry'),
    ('gameanimationeditor.cpp','PlayerAnimationEditor/geometry'),
    ('gamedesigner.cpp','GameObjectProperties/geometry'),
    ('mainwindow.cpp','PpbViewer/geometry'),
]:
    s=read(name)
    assert key in s and 'restoreGeometry(' in s and 'saveGeometry(' in s, (name,key)
assert '~SidboxPlayerAnimationEditor() override;' in read('gameanimationeditor.h')
assert 'saveGeometry());' in anim
# Save/Cancel: navigating explicitly saves, and the warning precedes commit.
object_editor=world[world.index('void SidboxGameDesigner::configureGameObject'):world.index('void SidboxGameDesigner::refreshObjectHitbox')]
assert 'QDialogButtonBox::Save | QDialogButtonBox::Cancel' in object_editor
assert 'confirmSaveNavigation() && commitObject()' in object_editor
assert 'Cancel later discards only edits made after your last save.' in object_editor
assert object_editor.index('confirmSaveNavigation() && commitObject()') < object_editor.index('if (auto *ok = buttons->button(QDialogButtonBox::Save))')
# Existing red/green styling used outside Adventure; requirements yield tooltips.
for name in ('gamedesigner.cpp','gamehudeditor.cpp','gametitlescreeneditor.cpp'):
    assert 'setProperty("adventureGuard", true)' in read(name)
    assert 'style()->polish(' in read(name)
assert 'Disabled: select the required inventory item first.' in world
assert 'Disabled: enable Text outline first.' in read('gametitlescreeneditor.cpp')
assert 'Available only when HUD dock is set to Overlay.' in read('gamehudeditor.cpp')
# Row-specific actions search for the button's CURRENT row and use existing
# confirmation/remapping routines, rather than duplicating potentially stale state.
assert 'new QTableWidget(0,9,itemsPage)' in adv
assert 'new QTableWidget(0,6,npcPage)' in adv
for v,col,old_button in [('items',8,'itemDel'),('npcs',5,'npcDel')]:
    assert f'{v}->cellWidget(current,{col}) != clicked.data()' in adv
    assert f'{old_button}->click();' in adv
assert adv.count('QTimer::singleShot(0,&dialog,[&,clicked]') == 2
assert 'for (const char *field : {"requires","give","take"})' in adv
assert 'if(!stillExists) for(int n=0;n<nodes.size();++n)' in adv
assert 'QMessageBox::question(this, tr("Delete animation frame?")' in anim
# Strict no-output-contract mutation: .pal editors, generated code and runtime untouched.
for file in ('gamepaletteeditor.cpp','gamepaletteeditor.h','gameadventuregen.cpp','gamedesigner_export.cpp',
             'gamedesigner.h','idelibs/codehelpers/game/adventureruntime.rulec',
             'idelibs/codehelpers/game/gameadventure.rulec','gamefloweditor.h'):
    assert hashlib.sha256((root/file).read_bytes()).digest() == hashlib.sha256((base/file).read_bytes()).digest(),file
assert 'Build: 5.136.251026' in read('splashscreenwidget.cpp')
with tempfile.TemporaryDirectory(prefix='stage5136-') as tmp:
    out=render_adventure_runtime(root,Path(tmp),items=1)
    tests=root/'development/tests'
    for name in ('stage5133_npc_foot_range','stage5114_current_thought','stage5115_answerless_thought'):
        exe=out/name
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0','-DBTN_FIRE=8',
            '-I',str(tests/'stage429_mock_api'),'-I',str(out),
            str(out/'adventureruntime.c'),str(tests/f'test_{name}.c'),'-o',str(exe)], check=True)
        subprocess.run([str(exe)], check=True)
print('Stage 5.136: window, save/cancel, dependency, per-row tests and native C PASS')

#!/usr/bin/env python3
"""Stage 5.124: Trigger / Switch per-row controls and unchanged generated runtime.

These are source-contract and native C regression tests. The Qt GUI must still
be compiled and exercised with the Fedora Qt6 SDK.
"""
from pathlib import Path
import hashlib
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root = Path(__file__).resolve().parents[2]
previous = Path('/mnt/data/ide_251026_stage5123')
designer = (root / 'gamedesigner.cpp').read_text()
version = (root / 'splashscreenwidget.cpp').read_text()
assert 'Build: 5.124.251026' in version
section = designer[designer.index('auto *linkedActionRows = new QTableWidget'):designer.index('form = generalCard.form; // State artwork belongs')]

# Three columns: target, action, row-specific controls. Up/down arrow icons
# are Qt-drawn arrows, not fragile text glyphs.
for token in (
    'new QTableWidget(0, 3, &dialog)',
    'tr("Game Object / NPC"), tr("Action"), tr("This row")',
    'resizeSection(2,150)',
    'linkedActionRows->setCellWidget(row,2,rowControls);',
    'setArrowType(Qt::UpArrow)', 'setArrowType(Qt::DownArrow)',
    'auto *rowDelete=new QPushButton(tr("Delete"),rowControls);',
    'refreshLinkedRowButtons();',
    'up->setEnabled(i>0);',
    'down->setEnabled(i+1<linkedActionRows->rowCount());',
    'tr("Delete linked action?")',
    'tr("Remove linked action #%1?',
    'Target: %2\\nAction: %3',
    'QMessageBox::Yes|QMessageBox::No,QMessageBox::No',
    'linkedActionRows->removeRow(row);',
    'linkedActionRows->selectRow(qMin(row,linkedActionRows->rowCount()-1));',
    'auto *object=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row,0));',
    'auto *action=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row,1));',
    'auto moveLink = [=](int row, int direction)',
    'moveLink(i,-1);', 'moveLink(i,1);',
    'deleteLink(i);',
    'linkedActionRows->cellWidget(i,2)==rowControls',
    'if (linkedActionRows->rowCount()>=64)',
    'insertLink(linkedActionRows->rowCount(),{QString(),QStringLiteral("enable")});',
):
    assert token in section, token

# No earlier unconfirmed "Remove selected row" path can bypass confirmation.
assert 'removeLinkedAction' not in section
assert 'upLinkedAction' not in section
assert 'downLinkedAction' not in section
assert section.index('QMessageBox::question(') < section.index('linkedActionRows->removeRow(row)')
assert section.index('setCellWidget(row,2,rowControls)') < section.index('connect(rowDelete,')
assert 'return links;' in section
assert 'r.targetObjectId=actions.isEmpty() ? QString() : actions.first().objectId;' in designer
assert 'for (int i=1;i<actions.size();++i) r.triggerExtraActions.append(actions.at(i));' in designer

# This feature must change neither world formats nor firmware-facing code.
for name in (
    'gamedesigner.h', 'gamedesigner_project.cpp', 'gamedesigner_export.cpp',
    'gameadventureeditor.cpp', 'gamefloweditor.cpp', 'gamecodegen.cpp',
    'ideglobaltheme.h',
):
    assert hashlib.sha256((root/name).read_bytes()).digest() == hashlib.sha256((previous/name).read_bytes()).digest(), name

with tempfile.TemporaryDirectory(prefix='stage5124-') as temp:
    out = render_adventure_runtime(root, Path(temp))
    tests = root/'development/tests'
    for stem in ('stage5114_current_thought', 'stage5115_answerless_thought'):
        exe = out/stem
        subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
            '-DBTN_FIRE=8','-I',str(tests/'stage429_mock_api'),'-I',str(out),
            str(out/'adventureruntime.c'),str(tests/f'test_{stem}.c'),'-o',str(exe)],check=True)
        subprocess.run([str(exe)],check=True)
print('Stage 5.124: per-row Trigger controls, unchanged export and native runtime PASS')

#!/usr/bin/env python3
"""Stage 5.166.70 source contracts for visual-node editing. Qt UI requires manual test."""
from pathlib import Path
import re
R=Path(__file__).resolve().parents[2]
ui=(R/'gamevisualnodes.cpp').read_text()
project=(R/'gamedesigner_project.cpp').read_text()
version=(R/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.166.99.291026' in version  # This stage advances the splash build.
# Hotkeys must not erase text from an editable purple card; confirmed delete for all cards.
assert 'auto *deleteShortcut=new QShortcut(QKeySequence(Qt::Key_Delete),this)' in ui
assert 'qobject_cast<QLineEdit*>(focus)' in ui
assert 'tr("Delete Visual Node")' in ui
assert 'if (!m_cards.contains(id) || (!force && connectedCardIds().contains(id)))return 0;' in ui
assert 'const int removed=removeOrphanCard(id,true);' in ui
# Deletion doesn't stop at legacy links; all independent graph references are removed.
segment=ui[ui.index('void removeSelectedNode()'):ui.index('void removeAllOrphans()')]
for text in ('QStringLiteral("inputs")','QStringLiteral("resultTargets")',
             'QStringLiteral("trueActions")','QStringLiteral("falseActions")',
             'removeOrphanCard(key,true)','node.links.removeAt(i)','m_touched.insert(source)'):
    assert text in segment,text
assert 'm_dialogues.removeAt(' not in segment
# Narrow fixed scene and inaccurate itemsBoundingRect Fit All have been replaced.
assert 'left->setMaximumWidth(270);' in ui
assert 'void fitAllCards()' in ui and 'fitInView(visible.adjusted(-110,-110,110,110)' in ui
assert 'm_scene->setSceneRect(visible.adjusted(-900,-700,900,700))' in ui
# Collapse is per-node, persists only in visual layout and preserves socket identity.
assert ui.count('addFoldButton(card,')>=6
assert 'm_collapsedCards.insert(id)' in ui and 'collapsedCards' in ui
layout=ui[ui.index('QJsonObject graphJson() const'):ui.index('bool saveLayout()')]
assert 'collapsedCards' in layout and 'logicNodes' not in layout
assert 'QPointF wirePoint(const QPointF &original)' in ui
assert 'port->sceneBoundingRect().center()' in ui
# Real trigger properties, also loaded/saved by Game Object Properties; no parallel schema.
for key in ('triggerPress','triggerOneShot','interactItemName'):
    assert f'data.value(QStringLiteral("{key}"))' in ui
    assert f'object.insert(QStringLiteral("{key}"),node.{key})' in ui
    assert f'object.insert(QStringLiteral("{key}"), r.{key})' in project
assert 'new QCheckBox(tr("Require FIRE2")' in ui
assert 'new QCheckBox(tr("Remove after switch")' in ui
assert 'new QLabel(tr("USE inventory:")' in ui
assert 'operation->currentData().toString()' in ui
assert 'opCombo->currentData().toString()' in ui
print('PASS Stage 5.166.70 node delete/cleanup, fold persistence, trigger field parity, dynamic Fit All source contracts')

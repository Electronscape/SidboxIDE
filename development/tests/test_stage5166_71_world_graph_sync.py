#!/usr/bin/env python3
"""Stage 5.166.71 source contracts: import existing .sbgm gameplay links without copying rules to .vsgm.
Qt desktop runtime requires a real Qt6 build for final interaction acceptance.
"""
from pathlib import Path
r=Path(__file__).resolve().parents[2]
s=(r/'gamevisualnodes.cpp').read_text()
exporter=(r/'gamedesigner_export.cpp').read_text()
assert 'Build: 5.166.99.291026' in (r/'splashscreenwidget.cpp').read_text()
# Use exactly the same active source types as the established generator.
assert 'node.type==QStringLiteral("enemy")' in s
assert '(node.type==QStringLiteral("collectable") && node.pickupKind==3)' in s
assert 'node.pickupKind=data.value(QStringLiteral("pickupKind")).toInt(1)' in s
assert 'r->pickupKind == 3' in exporter
assert 'r->objectType == QStringLiteral("enemy")' in exporter
for method,next_method in [('linkedObjectIds() const','connectedCardIds() const'),
                           ('void redrawLinks()','void showDetails('),
                           ('void removeConnection(','void linkContextMenu('),
                           ('void linkContextMenu(','QJsonObject graphJson() const')]:
    body=s[s.index(method):s.index(next_method)]
    assert 'isActionSource(' in body,method
# Prevent enemy and key event actions from inheriting/overwriting Trigger-only fields.
save=s[s.index('for (const QString &id:m_touched) {\n                const NodeObject node=m_objects.value(id);\n                if (!isActionSource(node)'):s.index('object.insert(QStringLiteral("triggerExtraActions"),extras);')]
assert 'if (node.type!=QStringLiteral("trigger")) {' in save
assert 'continue; // Never write Trigger fields into an enemy/key.' in save
assert 'resources.replace(node.resourceIndex,resource)' in save
# Preserve stable, encoded IDs for remote targets and report unavailable destination assets.
assert '#include "gamecrossworldlinks.h"' in s
assert 'cgDecodeCrossWorldLink(id,&world,&spriteId)' in s
assert 'reference.id=id' in s
assert 'cgCrossWorldObjectSlot(design,spriteId)>=0' in s
assert 'QStringLiteral("npc_reference")' in s
assert 'QStringLiteral("world_reference")' in s
assert 'MISSING: %1 / %2' in s
# World-file refresh must refuse to drop dirty edits without choice; and reload
# by re-reading the original files, NOT by merging stale graph objects.
assert 'tr("Refresh from World")' in s
assert 'if(answer==QMessageBox::Cancel)return;' in s
assert 'if(answer==QMessageBox::Yes && !saveAll())return;' in s
assert 'done(2)' in s
assert 'if (!dialog.initialise())return worldChanged;' in s
assert 'if(result!=2)break;' in s
# The graph file remains strictly visual. Never export an independently stored action array.
layout=s[s.index('QJsonObject graphJson() const'):s.index('bool saveLayout()')]
assert 'targetObjectId' not in layout and 'logicNodes' not in layout
print('PASS Stage 5.166.71 import enemy/key actions, cross-world/NPC aliases, non-destructive refresh and .sbgm authority')

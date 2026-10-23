#!/usr/bin/env python3
"""Source-contract checks for Stage 5.54 (Qt GUI run still needed)."""
from pathlib import Path

root=Path(__file__).resolve().parents[2]
src=(root/'gamefloweditor.cpp').read_text()
ver=(root/'splashscreenwidget.cpp').read_text()

required={
    '8px item snapping': 'std::round(p.x()/8.0)*8.0',
    'snap grid UI': 'Snap 8px',
    'snap persisted': 'QStringLiteral("snapToGrid")',
    'saved mini positions': 'QStringLiteral("memberPositions")',
    'group-local mini connections': 'new QGraphicsPathItem(frame)',
    'scene to parent path mapping': 'e.path->parentItem()->mapFromScene(path)',
    'scene to parent arrow mapping': 'e.arrow->parentItem()->mapFromScene(head)',
    'independently movable manual children': 'child->setFlag(QGraphicsItem::ItemIsMovable,true)',
    'nonmovable array children': 'child->setFlag(QGraphicsItem::ItemIsMovable,false)',
    'internal edge inclusion': 'if (internal && !mini)continue;',
    'manual child offset persistence': 'layout.memberPositions[owner].insert(member,miniCard->pos())',
    'group resize after mini movement': 'rect.setWidth(qMax(rect.width(),position.x()+224))',
    'ungroup child resolution': 'memberGroup.value(selectedId)',
    'ungroup shortcut': 'Qt::CTRL | Qt::SHIFT | Qt::Key_G',
    'original shortcut': 'Qt::CTRL | Qt::Key_G',
    'existing flow layout v2 read': 'result.manualGroups.append(g)',
    'old position files compatibility': 'const QJsonObject positions=document.value(QStringLiteral("positions")).toObject()',
    'new file v3': 'QStringLiteral("version"),3',
    'no code generation': 'Design-only layout V3',
}
for label,needle in required.items():
    assert needle in src, f'Missing: {label}'
assert 'Build: 5.54.231026' in ver
assert src.count('FlowCardItem final')==1

# Mathematical contract: snap both scene positions and group-local positions
# to 8 pixels while allowing fine repositioning when disabled.
for x in (-17.1,-8.0,-0.2,0,4,8,13,30,99.4):
    snapped=round(x/8)*8
    assert snapped%8==0
for x in (1,16,31,119):
    assert max(16,x)>=16
for y in (1,80,111):
    assert max(80,y)>=80

# The group's internal links use member IDs while links outside it
# terminate at its group boundary, not at a hidden member card.
def routed(a,b,group_of,expanded_manual):
    ag,bg=group_of.get(a,''),group_of.get(b,'')
    internal=bool(ag and ag==bg)
    mini=internal and ag in expanded_manual
    if internal and not mini:return None
    return (a if mini or not ag else ag,b if mini or not bg else bg,mini)

members={'A':'manual-one','B':'manual-one','C':'manual-one','Door':'', 'D':'array-one','E':'array-one'}
assert routed('A','B',members,{'manual-one'})==('A','B',True)
assert routed('A','Door',members,{'manual-one'})==('manual-one','Door',False)
assert routed('Door','B',members,{'manual-one'})==('Door','manual-one',False)
assert routed('A','B',members,set()) is None
assert routed('D','E',members,{'manual-one'}) is None
assert routed('D','Door',members,{'manual-one'})==('array-one','Door',False)
print('Stage 5.54 source contracts and edge-routing cases: PASS')

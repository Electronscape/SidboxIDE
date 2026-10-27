#!/usr/bin/env python3
"""Stage 5.166.16 source contracts for the Qt design-only Logic Flow debugger.
No Qt6 GUI is available in this test environment; validate the geometry
invariants independently and require their actual C++ implementations.
"""
from pathlib import Path
from collections import deque
root=Path(__file__).resolve().parents[2]
s=(root/'gamefloweditor.cpp').read_text()
assert 'Build: 5.166.17.271026' in (root/'splashscreenwidget.cpp').read_text()

assert 'Clean Logic Flow layout?' in s and 'QMessageBox::Cancel' in s
assert 'rememberLayout();' in s and 'undoHistory.append(layout)' in s
assert 'redoHistory.clear()' in s and 'from.takeLast()' in s
assert 'layout.viewports=currentViewports;' in s
assert 'QShortcut(QKeySequence::Undo' in s
assert 'QShortcut(QKeySequence::Redo' in s
assert 'Qt::CTRL | Qt::Key_Y' in s
assert 'layout.memberPositions.clear()' in s
assert 'flowLeftToRightPositions(visibleGraph,measuredCardSizes())' in s
assert 'flowLeftToRightPositions(internal,internalSizes)' in s
assert 'internalSizes.insert(id,QSizeF(' in s
assert 'backward[b].append(a)' in s and 'indegree[b]' in s
assert 'ranks.insert(next,ranks.value(from)+1)' in s
assert 'widths[rank]=qMax(widths[rank],sizeOf(i).width())' in s and 'widths[col-1]+columnGap' in s
assert 'sizeOf(i).height()+rowGap' in s
assert 'worldTop=align8(qMax(worldTop+160,componentTop+worldGap))' in s
assert 'card->setBrush(isGroup ? QBrush(g.automatic ? arrayBackground : groupBackground)' in s
assert 'sub->setBrush(nestedBackground);' in s
assert 'groupBackdrops' not in s, 'detached negative-z group panels cause background bleed'
assert 'line->setZValue(wireParent ? 0.5 : -2)' in s
assert 'QSaveFile file(filename);' in s

# Run the ranking and bounding-box invariants on synthetic graphs. This is a
# Python model, NOT a Qt execution test. It catches planning regressions that
# would lead to overlap or backtracking even with wide, tall group containers.
def arrange(world_nodes, edges, sizes):
    results={}
    world_top=72
    for world, ordered in world_nodes.items():
        outgoing={node:[] for node in ordered}; incoming={node:[] for node in ordered}
        adjacent={node:set() for node in ordered}
        for a,b in edges:
            if a not in outgoing or b not in incoming or a==b:continue
            outgoing[a].append(b);incoming[b].append(a)
            adjacent[a].add(b);adjacent[b].add(a)
        seen=set(); components=[]
        for root in ordered:
            if root in seen:continue
            component=[root];seen.add(root)
            for here in component:
                for there in sorted(adjacent[here]):
                    if there not in seen:seen.add(there);component.append(there)
            components.append(component)
        ranks={}
        for component in components:
            starts=[a for a in component if not incoming[a] or a.endswith('/world')]
            if not starts:starts=[component[0]]
            queue=deque(starts)
            for start in starts:ranks[start]=0
            while queue:
                here=queue.popleft()
                for there in outgoing[here]:
                    if there not in ranks:
                        ranks[there]=ranks[here]+1;queue.append(there)
                if not queue:
                    for item in component:
                        if item not in ranks:
                            ranks[item]=0;queue.append(item);break
        widest={}
        for node in ordered:
            rank=ranks[node];widest[rank]=max(widest.get(rank,250),sizes[node][0])
        columns={0:32}
        for rank in range(1,max(widest)+1):
            columns[rank]=columns[rank-1]+widest[rank-1]+104
        component_top=world_top
        for component in components:
            ys={};total=0
            for rank in range(max(widest)+1):
                items=[n for n in component if ranks[n]==rank]
                if rank>0:
                    items.sort(key=lambda item:(sum(ys[a] for a in incoming[item] if a in ys)/
                        max(1,sum(1 for a in incoming[item] if a in ys))) if any(a in ys for a in incoming[item]) else 1e12+ordered.index(item))
                y=component_top
                for item in items:
                    results[item]=(columns[rank],y)
                    ys[item]=y+sizes[item][1]/2
                    y+=sizes[item][1]+44
                if items:total=max(total,y-component_top-44)
            component_top+=max(70,total)+104
        world_top=max(world_top+230,component_top+48)
    return results

worlds={
    'World1':['w1/world','small','group','wide','last','cycle'],
    'World2':['w2/world','other','tall'],
}
sizes={
    'w1/world':(250,70), 'small':(250,70), 'group':(1160,640),
    'wide':(375,190), 'last':(250,70), 'cycle':(250,250),
    'w2/world':(250,70), 'other':(320,100), 'tall':(650,800),
}
edges=[('w1/world','small'),('small','group'),('small','wide'),('wide','last'),
       ('group','last'),('last','cycle'),('cycle','small'),
       ('w2/world','other'),('other','tall'),('group','tall')]
positions=arrange(worlds,edges,sizes)
for name,p in positions.items():
    for other,q in positions.items():
        if name>=other:continue
        a=(p[0],p[1],p[0]+sizes[name][0],p[1]+sizes[name][1])
        b=(q[0],q[1],q[0]+sizes[other][0],q[1]+sizes[other][1])
        assert a[2]<=b[0] or b[2]<=a[0] or a[3]<=b[1] or b[3]<=a[1], (name,other,a,b)
assert positions['w1/world'][0] < positions['small'][0] < positions['group'][0]
assert positions['w2/world'][1] > positions['cycle'][1]
print('Stage 5.166.16 flow source/geometry/undo contracts: PASS')

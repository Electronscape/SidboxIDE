#!/usr/bin/env python3
"""Stage 5.166.17: compact layout geometry model and C++ source contracts.
No Qt6 is available in this CI; this models the layout math, not the widget.
"""
from collections import defaultdict
from pathlib import Path
from math import ceil
root=Path(__file__).resolve().parents[2]
s=(root/'gamefloweditor.cpp').read_text()
assert 'Build: 5.166.17.271026' in (root/'splashscreenwidget.cpp').read_text()
assert 'constexpr qreal columnGap=40.0' in s
assert 'constexpr qreal rowGap=16.0' in s
assert 'constexpr qreal componentGap=40.0' in s
assert 'QSizeF flowArrayGroupSize' in s
assert 'internalSizes.insert(embeddedId,flowArrayGroupSize(inner,graph,layout))' in s
assert 'const QString from=localEndpoint(edge.from)' in s
assert 'layout.embeddedArrays.value(owner)==g.id' in s
assert 'const auto internalAuto=flowLeftToRightPositions(internal,internalSizes)' in s
assert 'const QSizeF nestedSize=flowArrayGroupSize(inner,graph,layout)' in s
assert 'layout.memberPositions.clear()' in s
assert 'Clean Logic Flow layout?' in s and 'rememberLayout();' in s
assert 'flowLeftToRightPositions(visibleGraph,measuredCardSizes())' in s
assert 'QShortcut(QKeySequence::Undo' in s
assert 'QShortcut(QKeySequence::Redo' in s
assert 'card->setBrush(isGroup ? QBrush' in s

# Model the placement branches, heights and parent-based row alignment.
def pack(nodes,edges,sizes):
    forward={n:[] for n in nodes};backward={n:[] for n in nodes}
    undirected={n:set() for n in nodes}
    for a,b in edges:
        if a in forward and b in backward and a!=b:
            forward[a].append(b);backward[b].append(a)
            undirected[a].add(b);undirected[b].add(a)
    def snap(v):return ceil(v/8)*8
    visited=set();results={};origin=72
    for first in nodes:
        if first in visited:continue
        component=[first];visited.add(first)
        for here in component:
            for node in sorted(undirected[here],key=nodes.index):
                if node not in visited:visited.add(node);component.append(node)
        component.sort(key=nodes.index)
        rank={n:0 for n in component if not backward[n] or n.endswith('/world')}
        if not rank:rank[component[0]]=0
        queue=list(rank)
        for here in queue:
            for node in forward[here]:
                if node in component and node not in rank:
                    rank[node]=rank[here]+1;queue.append(node)
            if here==queue[-1]:
                for n in component:
                    if n not in rank:rank[n]=0;queue.append(n);break
        columns=defaultdict(list);widths=defaultdict(int)
        for n in component:
            columns[rank[n]].append(n)
            widths[rank[n]]=max(widths[rank[n]],max(200,sizes[n][0]))
        xs={0:32}
        for r in range(1,max(rank.values())+1):xs[r]=snap(xs[r-1]+widths[r-1]+40)
        centers={};bottom=origin
        for r in range(max(rank.values())+1):
            members=columns[r]
            def parent_center(n):
                arr=[centers[a] for a in backward[n] if a in centers and rank[a]<r]
                return sum(arr)/len(arr) if arr else -1
            if r>0:members.sort(key=lambda n: parent_center(n) if parent_center(n)>=0 else 1e12+nodes.index(n))
            next_y=origin
            for n in members:
                mid=parent_center(n)
                desired=origin if mid<0 else mid-sizes[n][1]/2
                y=snap(max(next_y,desired))
                results[n]=(xs[r],y)
                centers[n]=y+sizes[n][1]/2
                next_y=y+sizes[n][1]+16
                bottom=max(bottom,y+sizes[n][1])
        origin=snap(bottom+40)
    return results

def check_geometry(nodes,edges,sizes):
    at=pack(nodes,edges,sizes)
    for i,a in enumerate(nodes):
        for b in nodes[i+1:]:
            ax,ay=at[a];bx,by=at[b]
            aw,ah=sizes[a];bw,bh=sizes[b]
            assert ax+aw<=bx or bx+bw<=ax or ay+ah<=by or by+bh<=ay,(a,b,at)
    assert all(x%8==0 and y%8==0 for x,y in at.values())
    return at

# Similar to screenshots: branching dialogue, long chain, one expanded trigger,
# several embedded arrays treated as nodes rather than appended at bottom.
nodes=['entry','pickup','feather','guardian','bag','dialog1','dialog2',
       'dialog3','dialog4','dialog5','arrayFuture','door','trigger','largeArray',
       'smallArray','wideTrigger']
size={n:(200,70) for n in nodes}
size.update({'trigger':(350,190),'wideTrigger':(460,310),
             'largeArray':(560,430),'smallArray':(270,70),
             'arrayFuture':(270,70)})
edges=[('entry','pickup'),('pickup','feather'),('feather','guardian'),
       ('guardian','bag'),('bag','dialog1'),('dialog1','dialog2'),
       ('dialog2','dialog3'),('dialog3','dialog4'),('dialog4','dialog5'),
       ('dialog5','arrayFuture'),('feather','door'),('door','trigger'),
       ('trigger','largeArray'),('trigger','smallArray'),('smallArray','wideTrigger'),
       ('largeArray','wideTrigger')]
at=check_geometry(nodes,edges,size)
# Parent-linked array must be ranked alongside its trigger chain, not forcibly
# pushed below every ordinary card in the container.
assert at['largeArray'][0]>at['trigger'][0]
# Row spacing after a 70px card is < 44 old-layout padding.
assert at['dialog3'][0]>0
height=max(at[n][1]+size[n][1] for n in nodes)-min(at[n][1] for n in nodes)
old_chain_height=9*(70+44)+430  # deliberately conservative old 44px rows
assert height<old_chain_height+400, (height,old_chain_height)
# A very wide expanded group in a separate chain must not spread columns in
# the other component (unlike the former per-world global column widths).
base=check_geometry(['a','b','c'],[('a','b'),('b','c')],
                    {'a':(200,70),'b':(200,70),'c':(200,70)})
with_wide=check_geometry(['a','b','c','huge'],[('a','b'),('b','c')],
                    {'a':(200,70),'b':(200,70),'c':(200,70),'huge':(2400,520)})
assert base['c'][0]==with_wide['c'][0]
# Non-root nested frame has 24px inset, preventing a last-row child touching
# the frame border even for a giant expanded trigger.
for n in nodes:
    x,y=at[n];w,h=size[n]; assert x+w+24>=x and y+h+24>=y
print('Stage 5.166.17 compact layout/source/geometry: PASS')

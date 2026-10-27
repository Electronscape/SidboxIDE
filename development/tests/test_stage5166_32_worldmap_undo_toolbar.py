#!/usr/bin/env python3
"""Stage 5.166.32: bottom controls and bounded, stroke-grouped World Map history."""
from pathlib import Path
import subprocess
import tempfile

root=Path(__file__).resolve().parents[2]
ui=(root/'gamerpguieditors.h').read_text()
section=ui[ui.index('inline bool editGameWorldMap('):ui.index('\n#endif',ui.index('inline bool editGameWorldMap('))]
canvas=ui[ui.index('class CgRpgMapCanvas'):ui.index('struct CgRpgMapAnimation')]
assert 'LEFT CLICK to paint with' not in section
assert section.index('root->addLayout(colourSettings)') < section.index('root->addLayout(split,1)')
assert section.index('root->addLayout(settings)') > section.index('resizeMap(initialCell);updateSelection();')
assert section.index('root->addLayout(settings)') > section.index('settings->addWidget(buttons)')
assert 'settings->addWidget(undoButton);settings->addWidget(redoButton);' in section
assert 'QKeySequence::Undo' in section
assert 'Qt::CTRL|Qt::Key_Y' in section
assert 'Qt::CTRL|Qt::SHIFT|Qt::Key_Z' in section
assert 'undoHistory.size()>=64' in section
assert 'redoHistory.clear();' in section
assert 'view->onStrokeFinished=recordEdit;' in section
assert 'onStrokeFinished();' in canvas
assert 'recordEdit();' not in section[section.index('auto paintCells='):section.index('view->onPaint=paintCells;')]
assert 'QVector<int> tiles;' in ui
assert 'QMap<QString,QPointF> positions;' in ui
assert 'QMap<int,CgRpgMapAnimation> animations;' in ui
assert 'resizeMap(state.tileSize);' in section
assert 'painted=state.tiles;' in section
assert 'loadAtlas(); /* Also refreshes CLUT' in section
for name in ('fillEmpty','setAnimation','removeAnimation','flagCell','flagLarge','w','h','size',
             'atlasEdit','paletteChoice','borderColour','flagFlashColour'):
    assert f'QObject::connect({name},' in section

# The value snapshots must be deep-copyable, comparable and restore equality,
# independent of Qt's GUI event loop. Compile their *actual* C++ definitions.
start=ui.index('struct CgRpgMapAnimation {')
end=ui.index('inline int cgRpgMapAnimationFrame',start)
source=ui[start:end]
with tempfile.TemporaryDirectory(prefix='cg516632_') as td:
    p=Path(td)
    (p/'history.cpp').write_text('''#include <string>
#include <vector>
#include <map>
#include <utility>
#include <cassert>
using QString=std::string;
using QPointF=std::pair<double,double>;
template<class T> using QVector=std::vector<T>;
template<class K,class V> using QMap=std::map<K,V>;
'''+source+'''
int main(){
    CgRpgMapEditState fresh;
    fresh.tiles={1,2,65535};fresh.animations[1]=CgRpgMapAnimation{1,4,5,true,false};
    fresh.positions["Forest"]={32.,64.};fresh.flags["Forest"]=19;
    CgRpgMapEditState other=fresh;
    assert(other==fresh);
    other.tiles[0]=3;assert(!(other==fresh));
    other=fresh;other.positions["Forest"]={20.,40.};assert(!(other==fresh));
    other=fresh;other.animations[1].bounce=true;assert(!(other==fresh));
    other=fresh;other.border=44;assert(!(other==fresh));
    return 0;
}
''')
    subprocess.run(['g++','-std=c++17','-Wall','-Wextra','-Werror',str(p/'history.cpp'),'-o',str(p/'history')],check=True)
    subprocess.run([str(p/'history')],check=True)
print('PASS Stage 5.166.32 World Map footer and snapshots (C++17)')

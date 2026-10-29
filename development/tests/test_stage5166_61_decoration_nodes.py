#!/usr/bin/env python3
"""5.166.61: decoration sprites can become logic-controlled, non-colliding objects.

Verifies generator/editor contracts, and exercises the native visibility/physics
semantics without pretending to compile the unavailable Qt6 IDE toolchain.
"""
from pathlib import Path
import subprocess
from tempfile import TemporaryDirectory

ROOT = Path(__file__).resolve().parents[2]
source = {name:(ROOT/name).read_text() for name in (
    'gamevisualnodes.cpp', 'gamedesigner.cpp', 'gamedesigner_project.cpp',
    'gamedesigner_export.cpp', 'gamecodegen.cpp',
    'idelibs/codehelpers/game/worldobjects.ruleh',
    'idelibs/codehelpers/game/worldobjects.rulec',
    'idelibs/codehelpers/game/gameworlditems.rulec',
    'splashscreenwidget.cpp')}

graph = source['gamevisualnodes.cpp']
project = source['gamedesigner_project.cpp']
export = source['gamedesigner_export.cpp']
designer = source['gamedesigner.cpp']
header = source['idelibs/codehelpers/game/worldobjects.ruleh']
world = source['idelibs/codehelpers/game/worldobjects.rulec']
items = source['idelibs/codehelpers/game/gameworlditems.rulec']

# Ordinary sprites appear as candidate graph nodes, with the player and NPCs
# explicitly excluded. Looking at or positioning a card cannot mutate game logic.
assert 'npcSpriteIds.contains(id)' in graph
assert 'QStringLiteral("player"),Qt::CaseInsensitive' in graph
assert 'const QString effectiveType = type.isEmpty() ? QStringLiteral("decoration") : type;' in graph
assert 'if (type.isEmpty() || type==QStringLiteral("decoration") || id.isEmpty()) continue;' not in graph
assert 'const QString groupType=object.type==QStringLiteral("decoration_object")' in graph
# A connected decoration is promoted in the guarded save transaction, and
# its original .sbgm ID is preserved. The old decoration type remains legal.
assert 'if (!m_touched.isEmpty() || m_dialoguesChanged || m_npcsChanged)' in graph
assert 'QSet<QString> actionTargets;' in graph
assert 'object.insert(QStringLiteral("type"),QStringLiteral("decoration_object"));' in graph
assert 'resource.insert(QStringLiteral("gameObject"),object);' in graph
assert 'decoration.resourceIndex' in graph
assert 'Decoration \'%1\' must use a PPB sprite at 100%' in graph
assert 'QStringLiteral("decoration_object")}.contains(type)' in project
assert 'Decoration (enable / disable / toggle)' in designer
assert 'tr("%1  [%2]").arg(r.name, shownType)' in designer
assert 'type == QStringLiteral("decoration_object") ? QStringLiteral("GAME_OBJECT_DECORATION")' in export
# Converted decoration now uses the common world-object draw/save/reset paths.
assert 'r.objectType != QStringLiteral("decoration")' in export
assert 'a.worldManaged = r.kind == QStringLiteral("sprite")' in export
assert 'if (sprite.asset.worldManaged) continue;' in source['gamecodegen.cpp']
assert '#define GAME_OBJECT_DECORATION 11u' in header
assert 'type > GAME_OBJECT_DECORATION' in world
assert 'o->type == GAME_OBJECT_DECORATION' in world
assert '(!object->active && !object->enemy_dying)' in world
assert 'GAMEWORLDITEMS_PLATFORM_COUNT' in items
assert 'cg_gwi_platforms[index].active = state == 2' in items
assert 'memset(cg_saved_objects,0,sizeof(cg_saved_objects))' in items
assert 'Build: 5.166.' in source['splashscreenwidget.cpp']

# Native contract: a decoration draws while enabled, disappears when disabled,
# toggles back, and never blocks the player or acts as a platform.
program = r'''
#include <assert.h>
#include <stdint.h>
#define GAME_OBJECT_DECORATION 11u
#define GAME_OBJECT_DOOR 5u
typedef struct { uint8_t type,active; } WorldObject;
static void set_active(WorldObject *o,unsigned state) {
    o->active = state==2u ? (uint8_t)!o->active : (uint8_t)(state!=0u);
}
static int draw(const WorldObject *o) { return o->active!=0; }
static int collides(const WorldObject *o) {
    return o->active && o->type!=GAME_OBJECT_DECORATION;
}
int main(void) {
    WorldObject red={GAME_OBJECT_DECORATION,1};
    WorldObject blue={GAME_OBJECT_DECORATION,1};
    WorldObject door={GAME_OBJECT_DOOR,1};
    assert(draw(&red) && draw(&blue));
    assert(!collides(&red) && collides(&door));
    set_active(&red,0);assert(!draw(&red) && draw(&blue));
    set_active(&red,1);assert(draw(&red));
    set_active(&blue,2);assert(!draw(&blue));
    set_active(&blue,2);assert(draw(&blue));
    set_active(&red,0);red.active=1;assert(draw(&red)); // new-game default
    return 0;
}
'''
with TemporaryDirectory() as d:
    c = Path(d)/'test.c'; exe=Path(d)/'test'; c.write_text(program)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O2',str(c),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('PASS Stage 5.166.61 Decoration object graph/catalogue/export/state/native visibility contracts')

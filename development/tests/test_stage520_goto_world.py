#!/usr/bin/env python3
"""Stage 5.20: Goto World object persistence, editor, deferred request and rebinding."""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
editor=(root/'gamedesigner.cpp').read_text()
header=(root/'gamedesigner.h').read_text()
persistence=(root/'gamedesigner_project.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
items=(root/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()
main=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
manager=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
splash=(root/'splashscreenwidget.cpp').read_text()
assert 'Build: 5.20.221026' in splash
assert 'QString gotoWorldName' in header and 'bool gotoPress' in header
for token in ('r.gotoWorldName = object.value', 'r.gotoPress = object.value',
              'object.insert(QStringLiteral("gotoWorldName")',
              'object.insert(QStringLiteral("gotoPress")'):
    assert token in persistence,token
assert editor.index('Stompable Enemy (jump on to defeat)') < editor.index('type->addItem(tr("Goto World")')
assert 'QStringLiteral("goto_world")' in editor
assert 'gotoCard.panel->setVisible(isGoto);' in editor
assert 'gotoWorld->setCurrentIndex' in editor
assert 'gotoActivation->setCurrentIndex' in editor
assert 'Press FIRE2 while touching' in editor
assert 'sidboxTilemapWorldBaseName(world.absoluteFilePath())' in editor
assert 'gotoWorld->currentData().toString().isEmpty()' in editor
assert 'gotoWorldName' in export and 'validWorlds' in export
assert 'QStringLiteral("GAME_OBJECT_TRIGGER")' in export
assert 'type == QStringLiteral("goto_world") ? r.gotoPress' in export
assert 'type == QStringLiteral("goto_world") ? false : r.triggerOneShot' in export
assert 'gameworlds_request(\\"%1\\");' in export
assert 'uint8_t gameworlds_request(const char *name);' in items
assert 'game_world_objects_trigger(platforms' in items
assert 'if (platforms[@IDE{INDEX}].trigger_fired)' in items
assert 'gameworlds_request("forest")' in (root/'idelibs/codehelpers/game/gameworlds.ruletxt').read_text()
assert 'pending_world = target;' in manager
assert 'if (!gameworlds_apply_pending())' in main
assert 'strcmp(running_world, now_world)' in main
assert 'game_tile_player_start(&player_physics' in main
assert 'gameworlds_bind_player_physics(&player_physics)' in main
assert 'gameworlds_player_start(&arrival)' in main
assert 'gameworlds_show_background();' in main
assert 'world_player.offset_x = player_physics.hitbox_x;' in main
assert 'result = 9; goto cleanup; /* Rebind' not in main
# Main template must remain renderable for mapped, unmapped, and physics setups.
flags=set(re.findall(r'@IDE_IF\{([A-Z_][A-Z0-9_]*)\}',main))
for selected in ({'PART_MAIN'},{'PART_MAIN','HAS_MAP','HAS_PHYSICS','HAS_SHARED_PLAYER','HAS_WORLD_PLAYER','HAS_OBJECTS'},
                 {'PART_MAIN','HAS_MAP','HAS_PHYSICS','HAS_PLAYER_ANIMATION','HAS_WORLD_PLAYER','HAS_ADVENTURE'}):
    nesting=[];active=True;output=[]
    for line in main.splitlines():
        m=re.fullmatch(r'@IDE_IF\{([A-Z_][A-Z0-9_]*)\}',line)
        if m:
            nesting.append((active,m.group(1) in selected));active=active and m.group(1) in selected
        elif line=='@IDE_ELSE':
            parent,condition=nesting[-1];active=parent and not condition
        elif line=='@IDE_END':
            active=nesting.pop()[0]
        elif active: output.append(line)
    assert not nesting
    rendered='\n'.join(output)
    assert 'strcmp(running_world, now_world)' in rendered
    if 'HAS_PHYSICS' in selected:
        assert 'gameworlds_player_start(&arrival)' in rendered
        assert 'game_tile_player_start(&player_physics,' in rendered
    else:
        assert 'gameworlds_player_start(&arrival)' not in rendered
print('PASS Stage 5.20: editor, persistence, trigger generation, deferred request and world-rebind source contracts')

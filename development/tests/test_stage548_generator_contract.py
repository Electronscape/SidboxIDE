#!/usr/bin/env python3
"""Source-level checks for C++ generator and Game Designer, Qt headers not installed here."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
gd=(root/'gamedesigner.cpp').read_text()
project=(root/'gamedesigner_project.cpp').read_text()
snapshot=(root/'gameworldsnapshot.h').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
main=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
world=(root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
checks={
 'UI both Player Start dialogs': gd.count('circleOrigin->addItem(tr("Door / Player Start")')==2,
 'project persists default/named circle origin': 'm_playerCircleOrigin' in project and 'location.circleOrigin' in project,
 'metadata exports circle origin for all starts': 'defaultCircleOrigin.at(i)' in snapshot and '"circleOrigin"' in snapshot,
 'door generated code uses the exit object centre': 'gameworlds_request_at_from(' in export and 'cg_gwi_platforms[%3].width / 2' in export,
 'world manager uses selected target before OUT': 'transition_entry(target, pending_spawn_id' in world and 'transition_entry(active_world, active_spawn_id, &in, &out, &frames, &origin, &x, &y)' in world,
 'generated game loop provides camera': 'gameworlds_transition_camera(camera_x, camera_y);' in main,
 'splash build': 'Build: 5.57.231026' in (root/'splashscreenwidget.cpp').read_text(),
}
for key,passed in checks.items(): print(('PASS' if passed else 'FAIL'),key)
assert all(checks.values())

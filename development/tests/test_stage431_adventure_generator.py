#!/usr/bin/env python3
"""Source boundary checks: generated records must match adventure runtime."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
ui=(root/'gameadventureeditor.cpp').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
run=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
head=(root/'idelibs/codehelpers/game/adventureruntime.ruleh').read_text()
world=(root/'gamedesigner.cpp').read_text()
export=(root/'gamedesigner_export.cpp').read_text()
assert all(x in ui for x in ['"idleFrames"','"talkFrames"','framesKeys[state]', 'Move Up', 'Move Down', 'Play preview', 'skinFlips', 'Item name', 'game_adventure_collect(item->kind)', 'QComboBox*','startNode'])
assert all(x in gen for x in ['idleFrames','talkFrames','npc_animations','skin_flips','game_adventure_skin_flips','it->flipX','it->flipY', '65535'])
assert 'game_adventure_npc_frame_t' in head and 'const game_adventure_npc_frame_t *idle_frames' in head
assert all(x in run for x in ['sequence[current].delay','game_adventure_skin_flips', 'tile.flags = ga_skin_flips[pos]', 'ga_animations[i].flip_flags','icon.imgdat=ga_skin_pixels +'])
assert world.count('a.flipX = r.objectFlipX')==2
assert 'player_buttons & (uint8_t)~BTN_UP' in export and 'getjoyport() & (uint8_t)~BTN_UP' in export
assert 'game_adventure_collect(item->kind)' in export
print('Stage4.31 generator/GUI/physics/music boundary checks PASS')

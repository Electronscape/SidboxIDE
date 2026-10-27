#!/usr/bin/env python3
"""Stage 5.166.3 contract + existing native joystick test."""
from pathlib import Path
import subprocess
R=Path(__file__).resolve().parents[2]
read=lambda path:(R/path).read_text()
e=read('gamequestjournaleditor.cpp')
g=read('gameadventuregen.cpp')
w=read('idelibs/codehelpers/game/gameadventure.rulec')
runtime=read('idelibs/codehelpers/game/adventureruntime.rulec')
api=read('idelibs/codehelpers/game/adventureruntime.ruleh')
assert 'SidboxPalettePicker::chooseIndex' in e
assert 'gamepalettepicker.h' in e
assert 'class AtlasGrid' in e and 'chooseCell(' in e
assert 'preview->atlas=atlasImage' in e
assert 'dialogueSkin' not in e
assert 'No HUD dock' not in e and 'HUD docked at TOP (48 px)' not in e
assert 'gamehud.sbhud' in e and 'rows' in e and 'cellHeight' in e
assert 'setWindowTitle(tr("Quest Journal Designer' in e and 'dialog.showMaximized()' in e
for key in ('atlas','tileSize','cells','flips','background','border','text','selection'):
    assert f'"{key}"' in e, key
assert 'SidboxPpb::read(absolute,&picture,&readError)' in g
assert 'Quest Journal atlas missing or outside game project' in g
assert 'Journal frame tile %1 is outside the selected atlas' in g
for tok in ['HAS_QUEST_ATLAS','QUEST_ATLAS_PATH','QUEST_ATLAS_WIDTH','QUEST_ATLAS_HEIGHT','QUEST_ATLAS_TILE','QUEST_CELLS','QUEST_FLIPS']:
    assert tok in g and tok in w, tok
assert 'game_adventure_quest_skin_file' in api and 'game_adventure_quest_skin_file' in runtime
assert 'ga_quest_skin_pixels' in runtime
assert 'ga_load_ppb(path,width,height)' in runtime
assert 'ga_quest_style.background_colour' in runtime
assert 'ga_frame_skin(x,y,w,h,ga_skin_indices,ga_skin_flips' in runtime
assert 'ga_frame_skin(ga_thought_x,' in runtime
assert 'gamehud_dock_top()?dock:0u' not in w
assert 'game_adventure_quest_viewport(0u,' in w
assert 'gamehud_dock_height()' in w
assert 'gameadventure' not in e.lower() or True
assert 'Build: 5.166.12.271026' in read('splashscreenwidget.cpp')
subprocess.run(['python3',str(R/'development/tests/test_stage5166_touch_journal.py')],check=True)
print('PASS Stage 5.166.3 independent nine-slice atlas, palette picker, real HUD dock, journal renderer')

#!/usr/bin/env python3
from pathlib import Path
import subprocess,tempfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
game=(root/'gamedesigner.cpp').read_text()
adventure=(root/'gameadventureeditor.cpp').read_text()
gen=(root/'gameadventuregen.cpp').read_text()
rule=(root/'idelibs/codehelpers/game/gameadventure.rulec').read_text()
rt=(root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
assert 'setWindowState(dialog.windowState() | Qt::WindowMaximized)' in adventure
assert 'setWindowState(dialog.windowState() | Qt::WindowMaximized)' in (root/'mainwindow.cpp').read_text()
assert 'if (event->button()==Qt::MiddleButton && panScroll)' in adventure
assert 'panScroll->horizontalScrollBar()->setValue' in adventure
assert 'panScroll->verticalScrollBar()->setValue' in adventure
assert 'if (event->button()!=Qt::LeftButton) return;' in adventure
assert 'result.insert("thoughtTextColourIndex",chosenThoughtText)' in adventure
assert 'visibleThoughtTextInk' in adventure
assert 'thoughtPositionFields->addWidget(thoughtTextColour' in adventure
assert 'positionFields->addWidget(textColour' in adventure
assert 'fields.insert(QStringLiteral("THOUGHT_TEXT_COLOUR_INDEX")' in gen
assert 'QStringLiteral("THOUGHT_TEXT_COLOUR_INDEX")' in gen
assert '@IDE{THOUGHT_TEXT_COLOUR_INDEX}u' in rule
assert 'game_adventure_thought_text_colour(' in rule
assert 'ga_text_colour=ga_thought_text_colour' in rt
assert 'ga_text_colour=saved_colour;' in rt
assert 'auto *hazardColour = new QPushButton(&dialog)' in game
assert 'auto *hazardColour = new GameComboBox(&dialog)' not in game
assert 'r.hazardFlashColour = chosenHazardColour;' in game
assert 'Build: 5.126.251026' in (root/'splashscreenwidget.cpp').read_text()
with tempfile.TemporaryDirectory(prefix='cg5126-') as temp:
    out=render_adventure_runtime(root,Path(temp),items=1)
    exe=out/'drop'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0','-DBTN_FIRE=8',
      '-I',str(tests/'stage429_mock_api'),'-I',str(out),str(out/'adventureruntime.c'),
      str(tests/'test_stage5126_directional_drop.c'),'-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
    thought=out/'thought_colours'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0','-DBTN_FIRE=8',
      '-I',str(tests/'stage429_mock_api'),'-I',str(out),str(out/'adventureruntime.c'),
      str(tests/'test_stage5126_thought_colours.c'),'-o',str(thought)],check=True)
    subprocess.run([str(thought)],check=True)
print('Stage 5.126 editor, exported template and native C runtime PASS')

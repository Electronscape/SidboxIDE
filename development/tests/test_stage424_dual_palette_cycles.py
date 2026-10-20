#!/usr/bin/env python3
"""Stage 4.24 dual CLUT cycles: editor, design persistence, V1 SDK/API integration."""
from pathlib import Path
import re
r=Path(__file__).resolve().parents[2]
def read(name): return (r/name).read_text()
pal=read('gamepalette.cpp'); pe=read('gamepaletteeditor.cpp'); ph=read('gamepaletteeditor.h')
world=read('gamedesigner.cpp'); wh=read('gamedesigner.h'); project=read('gamedesigner_project.cpp')
api=read('idelibs/api/graphics/graphics.h'); code=read('gamecodegen.cpp'); genh=read('gamecodegen.h'); exp=read('gamedesigner_export.cpp')
# Preview: FG never cycles alpha index 0; BG may cycle index 0.
assert 'int steps, bool backgroundBank)' in pal
assert 'qBound(backgroundBank ? 0 : 1, cycle.start, 254)' in pal
assert 'out[first + (i + shift) % length] = palette.at(first + i);' in pal
# Saved independent records, legacy Stage4.22 support
for k in ['foregroundColourCycle','backgroundColourCycle','colourCycle','showColourCycles']:
    assert k in project, k
assert 'm_frontColourCycle = readCycle(' in project and 'm_backColourCycle = readCycle(' in project
assert 'cycle.value' not in project[project.index('const auto readCycle'):project.index('m_backPalette->setEnabled')]
assert 'm_frontColourCycle' in wh and 'm_backColourCycle' in wh
assert 'm_frontCyclePhase' in wh and 'm_backCyclePhase' in wh
assert 'frontPhase != m_lastFrontCyclePhase || backPhase != m_lastBackCyclePhase' in world
assert 'resourcePlane(r) == QStringLiteral("background")' in world
assert 'm_frontColourCycle, m_frontCyclePhase' in world # Atlas always front
# Editor bank selection retains separate values
for phrase in ['void SidboxGamePaletteEditor::setColourCycles(',
               'm_bank->currentIndex() == 1 ? m_backCycle : m_frontCycle',
               'currentCycle().enabled = checked','currentCycle().start = start',
               'currentCycle().length = length','currentCycle().speed = speed',
               'm_cycleStart->setMinimum(currentBankIsBackground() ? 0 : 1)',
               'm_cycleClock.elapsed() / 20']:
    # actual conditional is via currentBankIsBackground
    if phrase == 'm_bank->currentIndex() == 1 ? m_backCycle : m_frontCycle':
        assert 'currentBankIsBackground() ? m_backCycle : m_frontCycle' in pe
    else: assert phrase in pe,phrase
assert 'foregroundColourCycle() const' in ph and 'backgroundColourCycle() const' in ph
# SDK: new background five appended after old popSprites, original offsets unchanged
api_struct=api.split('API_GFX_HARDWARE;',1)[0]
assert api_struct.index('(*popSprites)') < api_struct.index('(*palcycleonb)')
for name in ['palcycleonb','palcycleoffb','palcyclesetb','palcyclerangeb','palcyclerateb']:
    assert f'(*{name})' in api_struct
    assert f'#define gfx_{name}(' in api
# Game generator independently persists and enables both, AFTER CLUT installed
assert 'CycleSettings foregroundCycle;' in genh and 'CycleSettings backgroundCycle;' in genh
assert 'request.foregroundCycle' in exp and 'request.backgroundCycle' in exp
assert 'request.backgroundCycle.enabled' in code and 'request.foregroundCycle.enabled' in code
assert code.index('gfx_usefpalette(gameassets_front_clut)') < code.index('gfx_palcycleon()')
assert code.index('gfx_usebpalette(gameassets_back_clut)') < code.index('gfx_palcycleonb()')
assert 'from + length - 1' in code # .sbgm LENGTH converted to firmware inclusive END
assert 'source << "    gfx_palcycleoff();\\n"' in code
assert 'source << "    gfx_palcycleoffb();\\n"' in code
assert not any('gfx_palcycle' in read(s) for s in ['gamepaletteeditor.cpp','gamedesigner_project.cpp'])
print('PASS Stage4.24: independent CLUT cycles, design migration, timer, SDK append ABI, generated code')

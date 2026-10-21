#!/usr/bin/env python3
from pathlib import Path
root=Path(__file__).resolve().parents[2]
def read(n):return (root/n).read_text()
ui=read('gameadventureeditor.cpp')
rt=read('idelibs/codehelpers/game/adventureruntime.rulec')
h=read('idelibs/codehelpers/game/adventureruntime.ruleh')
gen=read('gameadventuregen.cpp')
for s in ['textColourIndex','textOutline','outlineColourIndex','NPC Animations...','idleFirst','idleCount','idleSpeed','talkFirst','talkCount','talkSpeed']:
    assert s in ui, s
    if s not in ['NPC Animations...','textColourIndex','textOutline','outlineColourIndex']: assert s in gen, s
assert 'ga_text(x-1,y,text)' not in rt # gfx draws through raw gfx_drawtext
for s in ['gfx_drawtext(x-1,y,text)','gfx_drawtext(x+1,y,text)',
          'gfx_drawtext(x,y-1,text)','gfx_drawtext(x,y+1,text)',
          'ga_outline_enabled ? 20 : 16',
          'ga_tick_animations(frames);','ga_active_npc = i;']:
    assert s in rt,s
assert 'ga_wrapped(c->label,' in rt or 'ga_wrapped(node->choices[i].label,' in rt
for s in ['game_adventure_npc_animations(',
          'static const game_adventure_npc_animation_t npc_animations[]']:
    assert s in gen,s
assert 'game_adventure_npc_animation_t' in h
assert '@IDE{TEXT_COLOUR_INDEX}' in rt and '@IDE{TEXT_OUTLINE_ENABLED}' in rt
assert 'a.symbol = spriteSymbol(r);' in read('gamedesigner.cpp')
print('Stage4.29 editor, generator, runtime integration checks passed')

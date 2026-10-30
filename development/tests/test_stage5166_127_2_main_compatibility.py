"""Stage127.2: starter and user-owned main never depend on animation internals."""
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]

def test_no_generated_main_struct_member_dependency():
    starter = (ROOT/'idelibs/codehelpers/game/maingame.rulec').read_text()
    assert 'player_anim.melee_ticks_left' not in starter
    assert 'player_anim.started=0u;' in starter
    assert 'player_anim_step(&player_anim' in starter
    assert 'player_anim_step_combat(' not in starter

def test_melee_transient_reset_remains_inside_animation_step():
    header = (ROOT/'idelibs/codehelpers/game/playeranim.ruleh').read_text()
    assert 'if (frame_step == 0u || !a->started || !gameplayer_combat_enabled())' in header
    assert 'a->melee_ticks_left = 0u;' in header
    assert '@IDE{PREFIX}_step(' in header

def test_splash_version():
    splash=(ROOT/'splashscreenwidget.cpp').read_text()
    assert 'Build: 5.128.1.301026' in splash

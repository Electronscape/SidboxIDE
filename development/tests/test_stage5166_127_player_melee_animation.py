"""Stage 127 compatibility: original single-step animation API is the supported API as of Stage 127.1."""
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
source = (ROOT/'idelibs/codehelpers/game/playeranim.ruleh').read_text()
starter = (ROOT/'idelibs/codehelpers/game/maingame.rulec').read_text()
assert 'HAS_MELEE_STATE' in source
assert '@IDE{PREFIX}_step_combat(' not in source
assert 'player_anim_step_combat(' not in starter
assert 'player_anim_step(&player_anim, &GAMERGIRL_PLAYER_BOB,' in starter

def test_stage127_compatibility():
    assert 'melee_ticks_left' in source

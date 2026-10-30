"""Stage 125 source contract + native C verification of enemy-hit effects."""
from pathlib import Path
import re
import shutil
import subprocess
import tempfile

ROOT=Path(__file__).resolve().parents[2]
MODEL=(ROOT/'gamedesigner.h').read_text()
EDITOR=(ROOT/'gamedesigner.cpp').read_text()
PROJECT=(ROOT/'gamedesigner_project.cpp').read_text()
EXPORT=(ROOT/'gamedesigner_export.cpp').read_text()
WORLD_H=(ROOT/'idelibs/codehelpers/game/worldobjects.ruleh').read_text()
WORLD_C=(ROOT/'idelibs/codehelpers/game/worldobjects.rulec').read_text()
ITEMS=(ROOT/'idelibs/codehelpers/game/gameworlditems.rulec').read_text()


def test_independent_player_enemy_controls_and_project_roundtrip():
    assert 'PLAYER HIT EFFECTS' in EDITOR
    assert 'ENEMY HIT EFFECTS' in EDITOR
    assert 'chosenEnemyHitColour' in EDITOR and 'chosenHazardColour' in EDITOR
    assert 'enemyHitPicker' in EDITOR and 'refreshEnemyHitStartButton()' in EDITOR
    for name in ('enemyHitFlash','enemyHitFlashColour','enemyHitFlashCount',
                 'enemyHitFlashFrames','enemyHitFrame','enemyHitCount','enemyHitDelay'):
        assert name in MODEL and f'"{name}"' in PROJECT
        assert f'r.{name} =' in EDITOR
    assert 'toBool(false)' in PROJECT


def test_all_generator_paths_and_anim_validation():
    for key in ('ENEMY_HIT_FLASH','ENEMY_HIT_FLASH_COLOUR',
                'ENEMY_HIT_FLASH_COUNT','ENEMY_HIT_FLASH_FRAMES',
                'ENEMY_HIT_FRAME','ENEMY_HIT_COUNT','ENEMY_HIT_DELAY'):
        assert f'"{key}"' in EXPORT
        assert f'@IDE{{{key}}}' in ITEMS
    assert 'r.enemyHitFrame + r.enemyHitCount' in EXPORT
    assert 'if (r.spriteStamp.active())' in EXPORT
    assert 'game_world_enemy_hit_visual(o, &visible);' in ITEMS
    assert 'game_world_enemy_hit_visual(object, &visible);' in WORLD_C
    assert 'enemy_take_damage(o, 1u);' in WORLD_C
    assert 'enemy_take_damage(o, damage);' in WORLD_C
    assert 'enemy_hit_ticks_remaining = 0u; /* Death animation takes precedence.' in WORLD_C
    assert 'enemy_hit_ticks_remaining' in WORLD_H
    assert 'BLIT_FLAG_SOLIDCOLOUR' in WORLD_C


def test_qt6_common_lambda_regression():
    for p in list(ROOT.glob('*.cpp')) + list(ROOT.glob('*.h')):
        assert not re.search(r'\bauto\s*\*\s*\w+\s*=\s*\[',p.read_text(errors='replace')),p
    assert 'auto updateCombatControls = [=]' in EDITOR
    assert re.search(r'Build: 5\.166\.\d+(?:\.\d+)?\.301026', (ROOT/'splashscreenwidget.cpp').read_text())


def test_native_enemy_flash_and_animation():
    compiler=shutil.which('gcc') or shutil.which('cc')
    assert compiler, 'C compiler required'
    source=ROOT/'idelibs/codehelpers/game'
    values={'WORLD_OBJECT_FIRST_TYPE':'1','SPRING_STRENGTH_DEFAULT':'11',
            'BREAK_STRENGTH_DEFAULT':'11','ENEMY_DEFEAT_FRAMES_DEFAULT':'20',
            'ENEMY_ROAM_SPEED_DEFAULT':'1','ENEMY_STEP_HEIGHT_DEFAULT':'4',
            'HAZARD_DAMAGE_DEFAULT':'1','HAZARD_FLASH_COLOUR_DEFAULT':'15',
            'HAZARD_FLASH_COUNT_DEFAULT':'4','HAZARD_FLASH_FRAMES_DEFAULT':'3'}
    with tempfile.TemporaryDirectory(prefix='stage125_') as tmp:
        target=Path(tmp)
        for fname,dname in [('worldobjects.rulec','gameworldobjects.c'),('worldobjects.ruleh','gameworldobjects.h')]:
            data=(source/fname).read_text()
            for key,value in values.items():
                data=data.replace('@IDE{'+key+'}',value)
            data=data.replace('@IDE_END','')
            assert '@IDE{' not in data
            (target/dname).write_text(data)
        (target/'worldobjects.h').symlink_to('gameworldobjects.h')
        for name in ('gameanimation.h','gamespline.h'):
            shutil.copy(ROOT/'development/_stage124_native'/name,target/name)
        shutil.copy(ROOT/'development/tests/stage125_enemy_hit_native.c',target/'test.c')
        exe=target/'test'
        cmd=[compiler,'-std=c11','-Wall','-Wextra','-Werror','-Wno-unused-function',
             '-ffunction-sections','-fdata-sections','-Wl,--gc-sections',
             '-I',str(target),'-I',str(ROOT/'idelibs/api'),str(target/'test.c'),'-o',str(exe)]
        subprocess.run(cmd,check=True,capture_output=True,text=True)
        result=subprocess.run([str(exe)],check=True,capture_output=True,text=True)
        assert 'Stage125 hit effects native runtime PASS' in result.stdout

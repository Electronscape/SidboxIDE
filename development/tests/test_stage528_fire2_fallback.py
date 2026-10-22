#!/usr/bin/env python3
"""Test the shipped runtime and compile the read-only door priority query."""
from pathlib import Path
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

root=Path(__file__).resolve().parents[2]
tests=root/'development/tests'
base=root/'idelibs/codehelpers/game'
with tempfile.TemporaryDirectory() as temp:
    out=Path(temp)
    render_adventure_runtime(root,out,items=1)
    exe=out/'fire2test'
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror','-O0',
        '-I',str(tests/'stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),
        str(tests/'test_stage528_fire2_fallback.c'),'-o',str(exe)], check=True)
    subprocess.run([str(exe)],check=True)

    # Use the actual function from the shipping object runtime template,
    # rather than reimplementing the overlap calculation in a test.
    source=(base/'worldobjects.rulec').read_text()
    begin=source.index('uint8_t game_world_objects_fire2_action(')
    end=source.index('uint16_t game_world_objects_trigger(',begin)
    function=source[begin:end]
    preamble='''#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#define GAME_OBJECT_TRIGGER 4
#define GAME_OBJECT_DOOR 5
typedef struct {int32_t x,y; uint16_t width,height; uint8_t active,type,trigger_press,trigger_pressed,trigger_touching;} game_world_object_t;
'''
    test='''
int main(void) {
  game_world_object_t a[2]={{.x=100,.y=100,.width=24,.height=24,.active=1,.type=GAME_OBJECT_TRIGGER,.trigger_press=1},
                            {.x=100,.y=100,.width=24,.height=24,.active=1,.type=GAME_OBJECT_TRIGGER,.trigger_press=0}};
  assert(game_world_objects_fire2_action(a,2,105,105,16,16));
  assert(!a[0].trigger_pressed && !a[0].trigger_touching);
  assert(!game_world_objects_fire2_action(a,2,150,150,16,16));
  a[0].active=0;
  assert(!game_world_objects_fire2_action(a,2,105,105,16,16));
  a[0].active=1; a[0].trigger_press=0;
  assert(!game_world_objects_fire2_action(a,2,105,105,16,16));
  a[0].trigger_press=1; a[0].type=GAME_OBJECT_DOOR;
  assert(!game_world_objects_fire2_action(a,2,105,105,16,16));
  puts("Stage 5.28 FIRE2 trigger collision/side-effect probe PASS");
  return 0;
}
'''
    (out/'trigger_probe.c').write_text(preamble+function+test)
    subprocess.run(['gcc','-std=c11','-Wall','-Wextra','-Werror',
                    str(out/'trigger_probe.c'),'-o',str(out/'trigger_probe')],check=True)
    subprocess.run([str(out/'trigger_probe')],check=True)

    worlditems_h=(base/'gameworlditems.ruleh').read_text()
    worlditems_c=(base/'gameworlditems.rulec').read_text()
    worldadventure=(base/'gameadventure.rulec').read_text()
    assert 'uint8_t gameworlditems_fire2_action(' in worlditems_h
    assert 'game_world_objects_fire2_action(platforms,' in worlditems_c
    assert 'game_adventure_set_fire2_action(gameworlditems_fire2_action);' in worldadventure
    assert 'game_adventure_set_fire2_action' in (base/'adventureruntime.ruleh').read_text()
    assert 'UP+FIRE2 away from NPC' not in (base/'maingame.rulec').read_text()
print('Stage 5.28 source wiring and runtime tests PASS')

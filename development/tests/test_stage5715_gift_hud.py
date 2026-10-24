#!/usr/bin/env python3
"""Gift-first HUD linkage regression using the existing compiled Stage 5.37 test harness."""
from pathlib import Path
import subprocess, tempfile
root = Path(__file__).resolve().parents[2]
adventure = (root/'idelibs/codehelpers/game/adventureruntime.rulec').read_text()
world = (root/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
assert adventure.count('game_adventure_inventory_kind_changed(ga_items[i].pickup_kind);') == 2
assert 'void game_adventure_inventory_kind_changed(uint16_t pickup_kind)' in world
old_test = (root/'development/tests/test_stage537_pickup_tracker.py').read_text()
# Add a tiny independent inventory type: a dialogue gift before any physical pickup.
old_test=old_test.replace('static int collected=0, called=0, scope=0;',
                          'static int gift=0; static int collected=0, called=0, scope=0;')
old_test=old_test.replace('''  if(kind!=1) return 0;
  *owned=(uint32_t)collected;''', '''  if(kind==6){*owned=(uint32_t)gift;return 1;}
  if(kind!=1) return 0;
  *owned=(uint32_t)collected;''')
old_test=old_test.replace('''  assert(gameworlds_start("world1"));
  pickup.kind=1;''', '''  assert(gameworlds_start("world1"));
  game_adventure_inventory_kind_changed(6); /* gift can register HUD source */
  assert(gameworlds_hud_total(6)==0);
  gift=1; /* Future Kim gives an item before the first floor pickup */
  assert(gameworlds_hud_total(6)==1);
  gift=2;assert(gameworlds_hud_total(6)==2);
  pickup.kind=1;''')
old_test=old_test.replace('''uint16_t game_adventure_collect_amount(uint16_t,uint16_t);''', '''uint16_t game_adventure_collect_amount(uint16_t,uint16_t);
void game_adventure_inventory_kind_changed(uint16_t);''')
assert 'gift=1;' in old_test
with tempfile.TemporaryDirectory(prefix='stage5715-testrun-') as temp:
    # The old harness refers to parents[2], and expects an SDK tree here.
    d=Path(temp)
    (d/'development/tests').mkdir(parents=True)
    (d/'idelibs').mkdir(parents=True)
    (d/'idelibs/codehelpers').symlink_to(root/'idelibs/codehelpers', target_is_directory=True)
    (d/'gamedesigner.cpp').symlink_to(root/'gamedesigner.cpp')
    (d/'gamedesigner_project.cpp').symlink_to(root/'gamedesigner_project.cpp')
    (d/'development/tests/check.py').write_text(old_test)
    proc=subprocess.run(['python3',str(d/'development/tests/check.py')],capture_output=True,text=True)
    assert proc.returncode==0,proc.stderr+proc.stdout
    print(proc.stdout.strip())
print('PASS: Stage 5.71.5 HUD gift-first regression')

#!/usr/bin/env python3
"""Native generated-template regression for Stage 5.164 persistent saves."""
EMPTY_QUEST_DATA = "#define GW_QUEST_COUNT 0u\n#define GW_OBJECTIVE_COUNT 0u\ntypedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;uint8_t initially_hidden;} gw_quest_def_t;\ntypedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;\nstatic const gw_quest_def_t gw_quest_defs[]={{0,0,0,0,0,0,0}};\nstatic const gw_objective_def_t gw_objective_defs[]={{0,0,0,0,0}};\n"

from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0,str(ROOT/'development/tests'))
from test_stage5163_rules_flow_audit import render

folder=ROOT/'idelibs/codehelpers/game'
flags={'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,
       'HAS_SHARED_PLAYER':False,'HAS_WORLD_PHYSICS':False,
       'HAS_PLAYER_VISIBILITY':False, 'HAS_TITLE':False,'HAS_MAP':False}
declarations='''static void fake_save(void (*)(const void*,uint32_t,void*),void*);
static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);
'''
record='''{.name="world1",.start_x=10,.start_y=20,.start_facing=1,
.object_disk_export=fake_save,.story_disk_export=fake_save,
.object_disk_import=fake_import,.story_disk_import=fake_import}'''
source=render((folder/'gameworlds.rulec').read_text(),flags)
source=(source.replace('@IDE{WORLD_DECLARATIONS}',declarations)
    .replace('@IDE{WORLD_RECORDS}',record).replace('@IDE{SAVE_KEY}','123').replace('@IDE{SAVE_IDENTITY}', '0x0123456789abcdef').replace('@IDE{QUEST_DATA}',EMPTY_QUEST_DATA))
header=render((folder/'gameworlds.ruleh').read_text(),flags)
assert '@IDE' not in source and '@IDE' not in header
flow=(ROOT/'gamefloweditor.cpp').read_text()
assert 'Save Game checkpoint' in flow
assert 'QStringLiteral("FIRE2 → Save Game")' in flow
assert 'QStringLiteral("Touch → Save Game")' in flow
assert 'gameworlds_checkpoint_request(%1u)' in (ROOT/'gamedesigner_export.cpp').read_text()
assert 'object.insert(QStringLiteral("checkpointSlot")' in (ROOT/'gamedesigner_project.cpp').read_text()
assert 'gametitle_load_slot(void)' in (folder/'gametitle-runtime.rulec').read_text()
with tempfile.TemporaryDirectory(prefix='stage5164_') as td:
    path=Path(td)
    (path/'gameworlds.c').write_text(source)
    (path/'gameworlds.h').write_text(header)
    output=path/'test'
    compile=['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections',
        '-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
        '-I',str(path),'-I',str(ROOT/'idelibs/api'),'-I',str(folder),
        f'-DTEST_FS_ROOT="{path}/fs"',
        str(ROOT/'development/tests/test_stage5164_save_load_native.c'),'-o',str(output)]
    subprocess.run(compile,check=True)
    subprocess.run([str(output)],check=True)

#!/usr/bin/env python3
"""Regression for Stage 5.164.3: two-world save callbacks must be public.

This exercises the published C API signatures in the actual generated-world
registry template with host GCC. If a callback is missing, the same eight
'undeclared here' errors as the reported ARM compilation are reproduced.
"""
EMPTY_QUEST_DATA = "#define GW_QUEST_COUNT 0u\n#define GW_OBJECTIVE_COUNT 0u\ntypedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;uint8_t initially_hidden;} gw_quest_def_t;\ntypedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;\nstatic const gw_quest_def_t gw_quest_defs[]={{0,0,0,0,0,0,0}};\nstatic const gw_objective_def_t gw_objective_defs[]={{0,0,0,0,0}};\n"

from pathlib import Path
import re
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / 'development/tests'))
from test_stage5163_rules_flow_audit import render

snapshot = (ROOT / 'gameworldsnapshot.h').read_text()
start = snapshot.index('QByteArray api = ', snapshot.index('inline bool publishBuildTree('))
end = snapshot.index('    {\n        QFile objectsHeader', start)
api_builder = snapshot[start:end]

# Pull the C prototypes from the C++ source that actually publishes world_api.h,
# not from a separately maintained test copy of those function declarations.
prototypes = {}
for name, return_type in (
    ('gameworlditems_disk_export', 'void'),
    ('gameworlditems_disk_import', 'uint8_t'),
    ('gameadventure_disk_export', 'void'),
    ('gameadventure_disk_import', 'uint8_t'),
):
    match = re.search(
        r'"' + re.escape(return_type) + r' " \+ id \+ "(_' + name + r'\([^"\n]*?\);\\n)"',
        api_builder,
    )
    assert match is not None, f'{name} must be declared by publishBuildTree()'
    prototypes[name] = f'{return_type} WORLD{match.group(1).replace(chr(92) + "n", "")}'

assert 'worlds/%1/world_api.h' in snapshot, 'registry must include published world headers'
source = ROOT / 'idelibs/codehelpers/game/gameworlds.rulec'
flags = {
    'HAS_ADVENTURE_RUNTIME': False,
    'HAS_PICKUPS': False,
    'HAS_SHARED_PLAYER': False,
    'HAS_WORLD_PHYSICS': False,
    'HAS_PLAYER_VISIBILITY': False,
 'HAS_TITLE':False,'HAS_MAP':False}
text = render(source.read_text(), flags)
rows = []
for world in ('world1', 'forest'):
    rows.append('{' + f'.name="{world}",' + ','.join(
        f'.{field}={world}_{name}' for field, name in (
            ('object_disk_export', 'gameworlditems_disk_export'),
            ('object_disk_import', 'gameworlditems_disk_import'),
            ('story_disk_export', 'gameadventure_disk_export'),
            ('story_disk_import', 'gameadventure_disk_import'),
        )
    ) + '}')
text = text.replace('@IDE{WORLD_DECLARATIONS}',
    '#include "../worlds/world1/world_api.h"\n#include "../worlds/forest/world_api.h"')
text = text.replace('@IDE{WORLD_RECORDS}', ',\n'.join(rows)).replace('@IDE{SAVE_KEY}', '123').replace('@IDE{SAVE_IDENTITY}', '0x0123456789abcdef').replace('@IDE{QUEST_DATA}', EMPTY_QUEST_DATA)
assert '@IDE' not in text

with tempfile.TemporaryDirectory(prefix='cg_stage5164_3_') as temp:
    project = Path(temp)
    (project / 'gamehelpers').mkdir()
    (project / 'gamehelpers/gameworlds.c').write_text(text)
    for world in ('world1', 'forest'):
        directory = project / 'worlds' / world
        directory.mkdir(parents=True)
        declarations = '\n'.join(
            prototypes[name].replace('WORLD', world) for name in prototypes
        )
        (directory / 'world_api.h').write_text(
            '#include <stdint.h>\n#include "../../gamehelpers/gameworlds.h"\n'
            + declarations + '\n'
        )
    header = render((ROOT / 'idelibs/codehelpers/game/gameworlds.ruleh').read_text(), flags)
    (project / 'gamehelpers/gameworlds.h').write_text(header)
    command = ['gcc', '-std=gnu11', '-fsyntax-only', '-Werror=implicit-function-declaration',
        '-I', str(project / 'gamehelpers'),
        '-I', str(ROOT / 'idelibs/api'),
        '-I', str(ROOT / 'idelibs/codehelpers/game'),
        str(project / 'gamehelpers/gameworlds.c')]
    subprocess.run(command, check=True)
    # The test must detect the original regression. Remove precisely one export
    # and assert that the manager now fails to compile.
    first = project / 'worlds/world1/world_api.h'
    first.write_text(first.read_text().replace(
        prototypes['gameworlditems_disk_export'].replace('WORLD','world1')+'\n', ''))
    bad = subprocess.run(command, capture_output=True, text=True)
    assert bad.returncode != 0 and 'world1_gameworlditems_disk_export' in bad.stderr

print('PASS Stage 5.164.3: two-world registry C compiles with generated public save callbacks; missing declaration fails')

#!/usr/bin/env python3
"""Stage 5.166.25: verify world-manager title conditions and both C runtime paths.

Uses the actual template, and fails for unknown/unrendered conditional flags.
No Qt installation or SIDBOX hardware is needed for this regression.
"""
from pathlib import Path
import re
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
MANAGER = (ROOT / 'gameworldsnapshot.h').read_text()
SOURCE = (ROOT / 'idelibs/codehelpers/game/gameworlds.rulec').read_text()
HEADER = (ROOT / 'idelibs/codehelpers/game/gameworlds.ruleh').read_text()

assert '#include "gametitleruntime.h"' in MANAGER
assert 'GameTitleRuntime::enabled(project.absolutePath())' in MANAGER
assert '{QStringLiteral("HAS_TITLE"),' in MANAGER
assert '@IDE{WORLD_BASE}' not in SOURCE
assert 'const char *title_world=worlds[0].name;' in SOURCE
assert 'gw_reset_title_session();' in SOURCE
assert 'if (success && !gw_initial_world) gw_initial_world=target->name;' in SOURCE
assert 'gw_initial_world=0;' in SOURCE


def render(source, flags):
    lines, frames, active = [], [], True
    for number, line in enumerate(source.split('\n'), 1):
        m = re.fullmatch(r'\s*@IDE_IF\{([A-Z_][A-Z0-9_]*)\}\s*', line)
        if m:
            assert m[1] in flags, f'unknown condition {m[1]} at {number}'
            frames.append((active, flags[m[1]], False))
            active = active and flags[m[1]]
        elif line.strip() == '@IDE_ELSE':
            assert frames and not frames[-1][2], number
            parent, condition, _ = frames[-1]
            frames[-1] = (parent, condition, True)
            active = parent and not condition
        elif line.strip() == '@IDE_END':
            assert frames, number
            active = frames.pop()[0]
        else:
            assert not line.strip().startswith(('@IDE_IF', '@IDE_ELSE', '@IDE_END')), number
            if active:
                lines.append(line)
    assert not frames, 'unclosed condition'
    return '\n'.join(lines)


QUEST_DATA = '''#define GW_QUEST_COUNT 0u
#define GW_OBJECTIVE_COUNT 0u
typedef struct {const char *id,*title,*description,*requires,*excludes;uint16_t first,count;uint8_t initially_hidden;} gw_quest_def_t;
typedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;
static const gw_quest_def_t gw_quest_defs[]={{0}};
static const gw_objective_def_t gw_objective_defs[]={{0}};'''
DECLARATIONS = '''static unsigned background_shows;
static void show_background(void){++background_shows;}
static int init(void){return 1;}
static void shutdown(void){}
static uint8_t objects_init(void){return 1;}
static void fake_save(void (*)(const void*,uint32_t,void*),void*);
static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);'''
RECORDS = ',\n'.join(
    '{.name="%s",.assets_init=init,.assets_shutdown=shutdown,.objects_init=objects_init,'
    '.start_x=%d,.start_y=20,.start_facing=1,.assets_show_background=show_background,.object_disk_export=fake_save,'
    '.story_disk_export=fake_save,.object_disk_import=fake_import,.story_disk_import=fake_import}'
    % (world, x) for world, x in [('world1', 10), ('forest', 40)]
)
NATIVE = (ROOT / 'development/tests/test_stage5164_save_load_native.c').read_text()
NATIVE = NATIVE[:NATIVE.index('int main(void)')].replace(
    '#include "gameworlds.c"',
    '#undef music_stop\n#define music_stop() ((void)0)\n#include "gameworlds.c"',
)

for title in (False, True):
    flags = {
        'HAS_ADVENTURE_RUNTIME': False,
        'HAS_WORLD_PHYSICS': False,
        'HAS_PICKUPS': False,
        'HAS_SHARED_PLAYER': False,
        'HAS_PLAYER_VISIBILITY': False,
        'HAS_TITLE': title,
    }
    generated = render(SOURCE, flags)
    for key, value in (
        ('WORLD_DECLARATIONS', DECLARATIONS),
        ('WORLD_RECORDS', RECORDS),
        ('SAVE_KEY', '123'),
        ('SAVE_IDENTITY', '0x0123456789abcdef'),
        ('QUEST_DATA', QUEST_DATA),
    ):
        generated = generated.replace('@IDE{' + key + '}', value)
    assert '@IDE{' not in generated
    generated_header = render(HEADER, flags)
    assert '@IDE{' not in generated_header
    assert ('#include "gametitle.h"' in generated) == title
    assert ('gametitle_run(&title_world,&title_start)' in generated) == title
    with tempfile.TemporaryDirectory(prefix=f'cg516625_{int(title)}_') as td:
        dest = Path(td)
        (dest / 'gameworlds.c').write_text(generated)
        (dest / 'gameworlds.h').write_text(generated_header)
        (dest / 'gametitle.h').write_text(
            '#include <stdint.h>\n'
            'uint8_t gametitle_run(const char **world,const char **start);\n'
            'int8_t gametitle_load_slot(void);\n'
        )
        test = NATIVE + r'''
static unsigned title_runs;
static char title_default[64];
uint8_t gametitle_run(const char **world, const char **start){
    ++title_runs;
    strncpy(title_default,*world,sizeof(title_default)-1u);
    (void)start;
    return 1u;
}
int8_t gametitle_load_slot(void){return -1;}
int main(void){
    mock_api.system=&systems;
    (void)mkdir(TEST_FS_ROOT,0700);(void)mkdir(TEST_FS_ROOT "/game",0700);
    gameworlds_fresh_start_enable(1u);
    assert(gameworlds_start("world1"));
    assert(strcmp(gw_initial_world,"world1")==0);
    persistent.health=5u;fake_data=15;
    gameworlds_update_gameplay(1u);
    assert(gw_fresh_bytes && gw_fresh_length);
    assert(gameworlds_start("forest"));
    assert(strcmp(gw_initial_world,"world1")==0);
    persistent.health=0;fake_data=999;
    assert(gameworlds_title_request());
    assert(gameworlds_apply_pending());
    assert(strcmp(gameworlds_active(),"world1")==0);
    if(TITLE_ENABLED)assert(persistent.health==0u);
    else assert(persistent.health==5u && fake_data==15);
    assert(title_runs == TITLE_ENABLED);
    assert(background_shows == TITLE_ENABLED); /* title-to-world restores direct background */
    if(TITLE_ENABLED)assert(strcmp(title_default,"world1")==0);
    assert(gameworlds_save_slot(4u));
    assert(gameworlds_session_can_reload());
    if (TITLE_ENABLED) {
        assert(gameworlds_title_request());
        assert(gameworlds_apply_pending());
        assert(title_runs==2u);
        assert(!gameworlds_session_can_reload());
    } else assert(!gameworlds_title_request());
    gameworlds_shutdown();
    assert(!gw_initial_world);
    puts("PASS title flag, clean New Game, saved slot policy");
    return 0;
}
'''
        # The simulated IDE compiler does not auto-define this; only the test needs it.
        test = '#define TITLE_ENABLED %du\n' % int(title) + test
        (dest / 'native.c').write_text(test)
        command = [
            'gcc', '-std=gnu11', '-O0', '-ffunction-sections', '-fdata-sections',
            '-Wl,--gc-sections', '-Wno-unused-function', '-Wno-unused-variable',
            '-I', str(dest), '-I', str(ROOT / 'idelibs/api'),
            '-I', str(ROOT / 'idelibs/codehelpers/game'),
            f'-DTEST_FS_ROOT="{dest}/fs"', str(dest / 'native.c'),
            '-o', str(dest / 'native'),
        ]
        subprocess.run(command, check=True)
        subprocess.run([str(dest / 'native')], check=True)

print('PASS Stage 5.166.25: compiler title conditions ON/OFF, clean template expansion, C runtime')

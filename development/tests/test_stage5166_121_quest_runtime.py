#!/usr/bin/env python3
"""Native C checks for unordered quest progression, completion edge, save and v3 migration."""
from pathlib import Path
import re,subprocess,tempfile
ROOT=Path(__file__).resolve().parents[2]
RULE=ROOT/'idelibs/codehelpers/game'
FLAGS={'HAS_ADVENTURE_RUNTIME':False,'HAS_PICKUPS':False,'HAS_SHARED_PLAYER':False,
       'HAS_WORLD_PHYSICS':False,'HAS_PLAYER_VISIBILITY':False,'HAS_TITLE':False,'HAS_MAP':False}
def render(src):
    stack=[];active=True;out=[]
    for line in src.split('\n'):
        m=re.fullmatch(r'\s*@IDE_IF\{([A-Z_][A-Z0-9_]*)\}\s*',line)
        if m:
            stack.append((active,FLAGS[m.group(1)]));active=active and FLAGS[m.group(1)]
        elif line.strip()=='@IDE_ELSE':
            parent,value=stack[-1];active=parent and not value
        elif line.strip()=='@IDE_END':
            parent,_=stack.pop();active=parent
        elif active:out.append(line)
    assert not stack
    return '\n'.join(out)
quest_data='''#define GW_QUEST_COUNT 4u
#define GW_OBJECTIVE_COUNT 7u
typedef struct {const char *id,*title,*description,*requires,*excludes; uint16_t first,count; uint8_t initially_hidden,unordered;} gw_quest_def_t;
typedef struct {const char *id,*title,*kind,*target,*hint;} gw_objective_def_t;
static const gw_quest_def_t gw_quest_defs[]={
{"ordered","Ordered","","","",0,2,0,0},
{"parts","Parts","","ordered","",2,3,0,1},
{"after","After","","parts","",5,1,0,0},
{"exclude","Exclude","","","parts",6,1,0,0}};
static const gw_objective_def_t gw_objective_defs[]={
{"o0","Tap first","event","tap",""},
{"o1","Tap second","event","tap",""},
{"p0","A","event","part_a",""},
{"p1","B","event","part_b",""},
{"p2","C","event","part_c",""},
{"a0","Next","world","forest",""},
{"x0","Nope","event","other",""}};
'''
source=render((RULE/'gameworlds.rulec').read_text())
source=(source.replace('@IDE{WORLD_DECLARATIONS}',
       'static void fake_save(void (*)(const void*,uint32_t,void*),void*);\n'
       'static uint8_t fake_import(uint8_t (*)(void*,uint32_t,void*),void*);\n'
       'static void quest_complete(const char *);\n')
    .replace('@IDE{WORLD_RECORDS}',
        '{.name="world1",.start_x=10,.start_y=20,.start_facing=1,'
        '.object_disk_export=fake_save,.story_disk_export=fake_save,'
        '.object_disk_import=fake_import,.story_disk_import=fake_import,'
        '.quest_completed=quest_complete}')
    .replace('@IDE{SAVE_KEY}','123').replace('@IDE{SAVE_IDENTITY}', '0x0123456789abcdef')
    .replace('@IDE{QUEST_DATA}',quest_data))
header=render((RULE/'gameworlds.ruleh').read_text())
assert '@IDE' not in source and '@IDE' not in header
native=r'''#define main old_save_suite
#include "test_stage5164_save_load_native.c"
#undef main
static int completed;
static const char *last_complete;
static void quest_complete(const char *id) { completed++;last_complete=id; }
int main(void) {
  assert(old_save_suite()==0);
  active_world=&worlds[0];gw_quest_reset();completed=0;
  assert(gameworlds_quest_count()==4);
  assert(gameworlds_quest_status(0)==1);
  assert(gameworlds_quest_status(1)==0);
  assert(gameworlds_quest_event("tap")==1);
  assert(gameworlds_quest_current_step(0)==1); /* ordered: only one tap */
  assert(completed==0);
  assert(gameworlds_quest_event("tap")==1);
  assert(gameworlds_quest_status(0)==2 && completed==1);
  assert(strcmp(last_complete,"ordered")==0);
  assert(gameworlds_quest_status(1)==1);
  assert(gameworlds_quest_event("part_c")==1);
  assert(gameworlds_quest_current_step(1)==1);
  assert(gameworlds_quest_event("part_c")==0); /* no duplicate */
  assert(strcmp(gameworlds_quest_objective(1),"A")==0);
  assert(gameworlds_save_slot(6));
  active_world=NULL;gw_quest_reset();completed=0;
  assert(gameworlds_load_slot(6));
  active_world=&worlds[0];
  assert(gameworlds_quest_status(1)==1 && gameworlds_quest_current_step(1)==1);
  assert(gameworlds_quest_event("part_c")==0); /* saved bit */
  assert(gameworlds_quest_event("part_b")==1);
  assert(gameworlds_quest_current_step(1)==2);
  assert(gameworlds_quest_event("part_a")==1);
  assert(gameworlds_quest_status(1)==2);
  assert(gameworlds_quest_status(2)==1);
  assert(gameworlds_quest_status(3)==3);
  assert(completed==1 && strcmp(last_complete,"parts")==0);
  /* Quest completion dispatches once, not on repeated refresh. */
  for(int i=0;i<3;i++)gameworlds_quest_status(1);
  assert(completed==1);
  /* v3 compatible payload (ordered quest steps, no bitset): use a fresh state. */
  gw_quest_reset();completed=0;assert(gameworlds_save_slot(7));
  char name[40];gw_save_filename(name,7,'A');
  FILE *f=fopen(pathmap(name),"r+b");assert(f);
  gw_save_header_t head;assert(fread(&head,sizeof(head),1,f)==1);
  uint8_t *bytes=(uint8_t*)malloc(head.length);assert(bytes);
  assert(fread(bytes,head.length,1,f)==1);
  head.version=3;head.length-=sizeof(((gw_save_quests_t*)0)->done);
  head.checksum=gw_save_checksum(bytes,head.length);
  rewind(f);assert(fwrite(&head,sizeof(head),1,f)==1);
  assert(fwrite(bytes,head.length,1,f)==1);
  fflush(f);assert(ftruncate(fileno(f),sizeof(head)+head.length)==0);
  fclose(f);free(bytes);
  active_world=NULL;gw_quest_reset();
  assert(gameworlds_slot_exists(7) && gameworlds_load_slot(7));
  active_world=&worlds[0];assert(gameworlds_quest_status(0)==1);
  puts("PASS Stage 5.166.121: ordered/unordered, save/restore, v3 migration and one-shot completion");
  return 0;
}
'''
with tempfile.TemporaryDirectory(prefix='stage121_') as temp:
    path=Path(temp)
    (path/'gameworlds.c').write_text(source)
    (path/'gameworlds.h').write_text(header)
    (path/'native.c').write_text(native)
    args=['gcc','-std=gnu11','-O0','-ffunction-sections','-fdata-sections',
          '-Wl,--gc-sections','-Wno-unused-function','-Wno-unused-variable',
          '-I',str(path),'-I',str(ROOT/'idelibs/api'),'-I',str(RULE),
          '-I',str(ROOT/'development/tests'),f'-DTEST_FS_ROOT="{path}/fs"',
          str(path/'native.c'),'-o',str(path/'native')]
    subprocess.run(args,check=True)
    subprocess.run([str(path/'native')],check=True)

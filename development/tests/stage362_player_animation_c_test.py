import ast, re, subprocess, tempfile
from pathlib import Path
source = (Path(__file__).resolve().parents[2] / 'gameanimationeditor.cpp').read_text()
out = Path(tempfile.mkdtemp(prefix='stage362_playeranim_'))

def cppstr(start, end):
    chunk = source[source.index(start):source.index(end, source.index(start))]
    return ''.join(ast.literal_eval(q) for q in re.findall(r'"(?:\\.|[^"\\])*"', chunk))

step = cppstr('    s += QString("static inline void %1_step(', '            .arg(prefix).arg(m_states.size()).arg(dirs.size())')
auto = cppstr('        s += QString(\n            "/* Optional automatic state selection.', '            .arg(prefix).arg(m_states.size()).arg(idle)')

def subst(pattern,vals):
    return re.sub(r'%([1-9][0-9]*)',lambda m: str(vals[int(m.group(1))-1]),pattern).replace('%%','%')

prefix='ggtest'
steps=subst(step,[prefix,10,2,0]); chooser=subst(auto,[prefix,10,0,1,2,3,4,5,7,8,6])
header = '''#ifndef GG_TEST_H\n#define GG_TEST_H\n#include "apis.h"\n#include <stdint.h>\ntypedef struct { const uint8_t *frames; uint16_t count; uint16_t ticks; uint8_t loop; uint8_t flip_x; } ggtest_clip_t;\ntypedef struct { uint16_t elapsed, position; uint8_t state, direction, started; } ggtest_playeranim_t;\nstatic const uint8_t idle[] = {3,8,1};\nstatic const uint8_t walk[] = {4,6};\nstatic const uint8_t jump[] = {7,9};\nstatic const ggtest_clip_t ggtest_clips[20] = {\n    {idle,3,2,1,0},{idle,3,2,1,1},\n    {walk,2,3,1,0},{walk,2,3,1,1},\n    {0,0,1,1,0},{0,0,1,1,0},\n    {0,0,1,1,0},{0,0,1,1,0},\n    {jump,2,1,0,0},{jump,2,1,0,1},\n    {0,0,1,1,0},{0,0,1,1,0},\n    {0,0,1,1,0},{0,0,1,1,0},\n    {0,0,1,1,0},{0,0,1,1,0},\n    {0,0,1,1,0},{0,0,1,1,0},\n    {0,0,1,1,0},{0,0,1,1,0},\n};\n'''
header += steps.replace('\n#endif\n','\n')
header += chooser
(out/'ggtest.h').write_text(header)
(out/'apis.h').write_text('''#include <stdint.h>\n#define BLIT_FLAG_FLIP_X 0x04u\n#define BLIT_FLAG_FLIP_Y 0x08u\ntypedef struct { const uint8_t *imgdat; uint8_t flags, index; } gfxbob_t;\n''')
(out/'test.c').write_text('''#include <assert.h>\n#include "ggtest.h"\nint main(void) {\n  static const uint8_t pixels[] = {1};\n  gfxbob_t bob={ pixels,BLIT_FLAG_FLIP_Y,0 };\n  ggtest_playeranim_t a={0};\n  ggtest_step(&a,&bob,0,0,1); assert(bob.index==3 && bob.flags==BLIT_FLAG_FLIP_Y);\n  ggtest_step(&a,&bob,0,0,1); assert(bob.index==3);\n  ggtest_step(&a,&bob,0,0,1); assert(bob.index==8);\n  ggtest_step(&a,&bob,0,0,2); assert(bob.index==1);\n  ggtest_step(&a,&bob,0,0,2); assert(bob.index==3);\n  ggtest_step(&a,&bob,0,1,1); assert(bob.index==3 && (bob.flags & BLIT_FLAG_FLIP_X));\n  ggtest_step(&a,&bob,1,0,1); assert(bob.index==4 && !(bob.flags & BLIT_FLAG_FLIP_X));\n  ggtest_step(&a,&bob,4,1,1); assert(bob.index==7 && (bob.flags & BLIT_FLAG_FLIP_X));\n  ggtest_step(&a,&bob,4,1,20); assert(bob.index==9);\n  ggtest_step(&a,&bob,4,1,40); assert(bob.index==9);\n  ggtest_step(&a,&bob,8,0,1); assert(bob.index==3 && !(bob.flags & BLIT_FLAG_FLIP_X)); /* fallback Idle */\n  assert(ggtest_auto_state(1,0,0,0,0,0,0,0)==0);\n  assert(ggtest_auto_state(1,0,1,0,0,0,0,0)==1);\n  assert(ggtest_auto_state(1,0,1,1,0,0,0,0)==2);\n  assert(ggtest_auto_state(0,-25,0,0,0,0,0,0)==4);\n  assert(ggtest_auto_state(0,25,0,0,0,0,0,0)==5);\n  assert(ggtest_auto_state(1,0,0,0,0,1,0,0)==6);\n  assert(ggtest_auto_state(1,0,0,0,0,0,1,0)==7);\n  assert(ggtest_auto_state(1,0,0,0,0,0,0,1)==8);\n  return 0;\n}\n''')
subprocess.run(['cc','-std=c99','-Wall','-Wextra','-Werror','-pedantic','-I',str(out),str(out/'test.c'),'-o',str(out/'test')], check=True)
subprocess.run([str(out/'test')],check=True)
print('PASS: exported C step + auto selector compiled -std=c99 -Wall -Wextra -Werror; 19 assertions passed')

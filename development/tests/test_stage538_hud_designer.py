#!/usr/bin/env python3
"""Stage 5.38 source contracts, project-wide HUD drawing and pickup semantics."""
from pathlib import Path
import subprocess
import tempfile
r=Path(__file__).resolve().parents[2]
ui=(r/'gamedesigner.cpp').read_text()
gui=(r/'gamehudeditor.cpp').read_text()
up=(r/'gamedesigner_update.cpp').read_text()
exp=(r/'gamedesigner_export.cpp').read_text()
rule=(r/'idelibs/codehelpers/game/maingame.rulec').read_text()
world=(r/'idelibs/codehelpers/game/gameworlds.rulec').read_text()
assert 'HUD Editor...' in ui and 'openAdventureEditor();' in ui
for name in ('"*.sbgm"','pickupShowHud','kMime','QDrag','dragEnterEvent','dropEvent','flipX','flipY',
             'Mirror whole X','Mirror whole Y','gamehud.sbhud','gamehelpers','gamehud.c','gamehud.h',
             'void game_show_hud(int32_t x, int32_t y)','gfx_drawbob(&background)','gfx_drawtext',
             'Not seeing anything in the list?', 'void mouseDoubleClickEvent', 'registerHudFiles'):
    assert name in gui,name
assert 'regenerateGameHud(project.absolutePath(), &error)' in up
assert 'mainFlag("HAS_HUD"' in exp
assert '@IDE_IF{HAS_HUD}' in rule and 'game_show_hud(0, 0);' in rule
assert 'QDir(projectRoot).filePath("main.c")' not in gui, 'HUD editor must not overwrite game source'
assert 'game_adventure_collect_amount(item->kind, 1u)' in world
assert '*count + 1u' in world
assert '*count + item->value' not in world
assert 'ctx->cb(item, ctx->user)' in world, 'callback still owns reward value'
assert 'Build: ' in (r/'splashscreenwidget.cpp').read_text()
# Validate representative ARM-facing generated C without requiring Qt in CI.
with tempfile.TemporaryDirectory(prefix='stage538-runtime-') as tmp:
    p=Path(tmp)
    (p/'apis.h').write_text('''#ifndef API_MOCK\n#define API_MOCK\n#include <stdint.h>\ntypedef struct {const uint8_t *imgdat;uint16_t atlas_stride,atlas_height,width,height;int32_t drawx,drawy;uint16_t scale;} gfxbob_t;\nvoid gfx_drawbob(gfxbob_t*);void gfx_setcolour(unsigned);void gfx_drawtext(int,int,char*);\n#endif\n''')
    (p/'gameworlds.h').write_text('#include <stdint.h>\nuint32_t gameworlds_hud_total(uint16_t kind);\n')
    (p/'gamehud.h').write_text('#include <stdint.h>\nvoid game_show_hud(int32_t x,int32_t y);\n')
    (p/'gamehud.c').write_text('''#include "gamehud.h"\n#include "gameworlds.h"\n#include "apis.h"\n#include <stdio.h>\nstatic const unsigned char icon_0[4] __attribute__((aligned(32))) = {1,2,3,4};\nstatic const unsigned char hud_pixels[4] __attribute__((aligned(32))) = {1,2,3,4};\nvoid game_show_hud(int32_t x, int32_t y) {\n    gfxbob_t background = {0};\n    background.imgdat=(uint8_t *)hud_pixels; background.atlas_stride=2u;\n    background.atlas_height=2u; background.width=2u; background.height=2u;\n    background.scale=100u; background.drawx=x; background.drawy=y;\n    gfx_drawbob(&background);\n    gfx_setcolour(15u); gfx_drawtext(x+4,y+6,(char *)"Coins:");\n    { gfxbob_t icon={0}; icon.imgdat=(uint8_t *)icon_0;\n      icon.atlas_stride=2u;icon.atlas_height=2u;icon.width=2u;icon.height=2u;\n      icon.scale=100u;icon.drawx=x+18;icon.drawy=y+4;gfx_drawbob(&icon);\n      char count[16];snprintf(count,sizeof(count),"%lu",(unsigned long)gameworlds_hud_total(3u));\n      gfx_setcolour(15u);gfx_drawtext(x+22,y+6,count);}\n}\n''')
    (p/'mock.c').write_text('''#include "apis.h"\n#include <string.h>\n#include <assert.h>\n#include "gamehud.h"\nstatic int draws,texts;\nvoid gfx_drawbob(gfxbob_t *b){assert(b && b->imgdat && b->scale==100u);draws++;}\nvoid gfx_setcolour(unsigned colour){assert(colour<=255u);}\nvoid gfx_drawtext(int x,int y,char *s){(void)x;(void)y;assert(s);texts++;}\nuint32_t gameworlds_hud_total(uint16_t kind){assert(kind==3u);return 123u;}\nint main(void){game_show_hud(2,4);assert(draws==2 && texts==2);return 0;}\n''')
    cc=['gcc','-std=c11','-Wall','-Wextra','-Werror','-I',str(p),str(p/'gamehud.c'),str(p/'mock.c'),'-o',str(p/'test')]
    run=subprocess.run(cc,capture_output=True,text=True)
    assert run.returncode==0,run.stderr
    run=subprocess.run([str(p/'test')],capture_output=True,text=True)
    assert run.returncode==0,run.stderr
print('PASS Stage 5.38: project-wide HUD contracts and strict-C runtime draw example')

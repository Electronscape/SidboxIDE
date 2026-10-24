#!/usr/bin/env python3
"""Stage 5.64 V1 runtime integration contracts (Qt6 GUI acceptance separate)."""
from pathlib import Path
root=Path(__file__).resolve().parents[2]
ide=(root/'gamedesigner_export.cpp').read_text()
main=(root/'idelibs/codehelpers/game/maingame.rulec').read_text()
runtime=(root/'idelibs/codehelpers/game/gametitle-runtime.rulec').read_text()
generator=(root/'gametitleruntime.cpp').read_text()
compilefile=(root/'mainwindow.cpp').read_text()
backup=(root/'gamedesigner_update.cpp').read_text()
assert 'Build: 5.64.231026' in (root/'splashscreenwidget.cpp').read_text()
assert 'gametitleruntime.cpp' in (root/'CMakeLists.txt').read_text()
assert 'mainFlag("HAS_TITLE", GameTitleRuntime::enabled(' in ide
assert 'GameTitleRuntime::generate(' in ide
assert ide.index('GameTitleRuntime::generate(')<ide.index('if (!exportExampleMain(&integrationError))')
assert 'gamehelpers/gametitle.c' in backup and 'gamehelpers/gametitle.h' in backup
assert '@IDE_IF{HAS_TITLE}' in main
assert 'gametitle_run(&title_world, &title_start)' in main
assert 'gameworlds_request_at(title_world, title_start)' in main
assert 'gameworlds_apply_pending()' in main
assert 'gameworlds_start("@IDE{WORLD_BASE}")' in main
assert 'TITLE_SELECTOR' in runtime and 'TITLE_SELECTOR_COLOUR' in runtime
assert 'gfx_drawtextf(' in runtime and 'gfx_drawbob(' in runtime
assert 'gfx_rectf(' in runtime
assert 'gfx_usefpalette(' in runtime
assert 'gfx_dispfbuffer(' in runtime and 'gfx_displaynow()' in runtime
assert 'BTN_UP' in runtime and 'BTN_DOWN' in runtime and 'BTN_FIRE' in runtime
assert 'if (item->action==1 || item->action==2)' in runtime
assert 'if (item->action==5)' in runtime
assert 'Load Game / Options intentionally do nothing' in runtime
assert 'FIRE2 reserved as Back' in runtime
assert 'sfopen(' in runtime and 'sfread(' in runtime and 'sflseek(' in runtime
assert 'title_release_images()' in runtime
assert 'memcpy(target->bitmap+x*320u' in runtime
assert 'target->bitmap[x*320u+y]' in runtime
assert 'titleConfig.lastModified()>titleC.lastModified()' in compilefile
assert 'gameworlds_request_at' in compilefile
assert 'if (title.value(QStringLiteral("enabled")).toBool())' in compilefile
assert 'QSaveFile out(' in generator
assert 'safeRelative(' in generator
assert 'imageIndex(' in generator
assert 'qBound(' in generator
assert 'toLatin1()' in generator
assert 'fontSizeX' in generator and 'fontSizeY' in generator
assert 'textPalette' in generator and 'menuSelector' in generator
assert 'SidboxPpb::read(' in generator
print('Stage 5.64 title runtime generator, startup and safety source regression: PASS')

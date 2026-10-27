#!/usr/bin/env python3
"""Stage 5.166.26 native/structural checks: cached painter + title background."""
from pathlib import Path
import subprocess
import sys
import re

root = Path(__file__).resolve().parents[2]
ui = (root / 'gamerpguieditors.h').read_text()
manager = (root / 'idelibs/codehelpers/game/gameworlds.rulec').read_text()
generator = (root / 'gameadventuregen.cpp').read_text()
splash = (root / 'splashscreenwidget.cpp').read_text()

assert (m := re.search(r'Build: 5\.166\.(\d+)\.271026', splash)) and int(m.group(1)) >= 26
assert 'QVector<QImage> chunkImages;' in ui
assert 'QVector<QGraphicsPixmapItem *> chunkItems;' in ui
assert 'constexpr int chunkPixels=256;' in ui
assert 'QVector<uint8_t> dirty(chunkItems.size(),0);' in ui
assert 'if(dirty[section])repaintSection(section);' in ui
assert 'repaintAllSections();' in ui
assert 'for(int n=0;n<painted.size();++n)updateTile(n);' not in ui
assert 'images[n]' not in ui
assert 'currentBank=cgRpgPalette' in ui
assert 'if(relative!=loadedAtlas || sourceSheet.isNull())' in ui
assert 'sheet.setColorTable(currentBank)' in ui
assert 'view->boundaryPreview=cgRpgColour(currentBank,borderColour->value());' in ui
assert 'World Map outer boundary' in ui
assert 'Pick boundary colour...' in ui
assert 'Pick flash colour...' in ui
assert 'WORLD_MAP_BORDER_COLOUR' in generator
assert 'WORLD_MAP_FLAG_FLASH_COLOUR' in generator
assert 'if(active_world && active_world->assets_show_background)\n            gameworlds_show_background();' in manager
assert manager.index('gameworlds_show_background();',manager.index('if(pending_title_return)')) < manager.index('++gw_reload_revision;',manager.index('if(pending_title_return)'))

subprocess.run([sys.executable, str(root/'development/tests/test_stage5166_25_title_registry.py')],check=True)
print('PASS Stage 5.166.26 chunk batching, palette cache, boundary picker + title return background')

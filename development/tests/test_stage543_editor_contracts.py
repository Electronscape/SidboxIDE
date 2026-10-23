#!/usr/bin/env python3
"""Stage 5.43 source-level contracts + native C inventory-drop regression."""
from pathlib import Path
import subprocess, tempfile, json, tarfile
from stage442_render_test_helpers import render_adventure_runtime
root=Path(__file__).resolve().parents[2]
ui=(root/'gameadventureeditor.cpp').read_text()
export=(root/'gameadventuregen.cpp').read_text()
assets=(root/'gamedesigner_export.cpp').read_text()
designer=(root/'gamedesigner.cpp').read_text()
hud=(root/'gamehudeditor.cpp').read_text()
assert 'Icon PPB atlas:' in ui
assert 'atlasSelect->addItem' in ui and 'QFileInfo(resource.path).fileName()' in ui
assert 'iconEntry->setData(Qt::UserRole+3,selected)' in ui
assert 'iconEntry->setData(Qt::UserRole+4,size)' in ui
assert 'item.insert("iconAtlasId"' in ui
assert 'game_adventure_item_atlas(' in export
assert 'adventureIconAtlases.contains(r.id)' in assets
assert 'if (m_syncSelection || m_loading || !m_scene || !m_resourceTree) return;' in designer
assert 'Keep the edited object under Game Objects' in designer
assert 'm_resourceTree->setCurrentItem(entry)' in designer
assert 'hudColourMap(' not in hud
assert 'char(atlas.pixelIndex(px,py))' in hud
assert 'char(icon.pixelIndex(xx,yy))' in hud
assert 'result.setColorTable(target); // preview palette ONLY' in hud
# The current splash version is checked by the latest-stage contract test.
with tempfile.TemporaryDirectory(prefix='cg-stage543-') as temp:
    out=Path(temp)
    render_adventure_runtime(root,out)
    exe=out/'test'
    subprocess.run(['cc','-std=c11','-Wall','-Wextra','-Werror',
        '-DBTN_FIRE=0x08u','-I',str(root/'development/tests/stage429_mock_api'),'-I',str(out),
        str(out/'adventureruntime.c'),str(root/'development/tests/test_stage543_icon_drop.c'),
        '-o',str(exe)],check=True)
    subprocess.run([str(exe)],check=True)
print('Stage 5.43 editor & HUD palette/index contracts: PASS')

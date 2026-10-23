#!/usr/bin/env python3
"""HUD PPB-index/artwork regression contracts (Qt6 GUI compile done separately)."""
from pathlib import Path
import re
root=Path(__file__).resolve().parents[2]
s=(root/'gamehudeditor.cpp').read_text()
checks={
    'all saved world definitions': 'entryList({"*.sbgm"}' in s,
    'resolves selected PPB UUID': 'candidate.value("id").toString()==atlasId' in s,
    'portable original atlas path': 'item.value("iconPpbPath")' in s,
    'single cell index': 'item.value("icon").toInt(65535)' in s,
    '2x2 four independent cells': 'is2x2 && cells.size()==4' in s,
    'Game Object frame': 'r.value("frame").toInt(0)' in s,
    'Game Object flipped sprite stamp': 'sprite.compose(atlas)' in s,
    'pixel-index copy': 'std::copy_n(src,tile,dst)' in s,
    'no old top-left sampling': 'firstIcon(' not in s,
    'no runtime new PPBs': 'stamp_*.ppb' not in s,
    'HUD C is exported from resolved art': 'const QImage icon=pickupIcon(root,cnt);' in s,
    'HUD preview is resolved': 'hudPreview(pickupIcon(root,c),textColors)' in s,
    'old HUD placements refreshed': 'updateCounterArtwork(doc,pickups)' in s,
    'HUD regeneration refreshed': 'updateCounterArtwork(d,discover(projectRoot))' in s,
    'HUD v1 compatibility': '{"format", "SIDBOX-SHARED-HUD"}, {"version",1}' in s,
    'no palette index remapping': 'char(icon.pixelIndex(xx,yy))' in s and 'iconRemap' not in s,
    'splash version': 'Build: 5.48.231026' in (root/'splashscreenwidget.cpp').read_text()
}
for desc, ok in checks.items():
    print(('PASS' if ok else 'FAIL'), desc)
assert all(checks.values())
print('Stage 5.47 HUD icon lookup contracts PASS')

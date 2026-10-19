"""Stage 3.71: mechanical source extraction checks (Qt6 GUI build still needed)."""
from pathlib import Path
import hashlib
import json
import re

root = Path(__file__).resolve().parents[2]
manifest = json.loads((root/'development/tests/stage371_refactor_manifest.json').read_text())
cmake=(root/'CMakeLists.txt').read_text()
main=(root/'guidesigner.cpp').read_text()
detail=(root/'guidesigner_detail.h').read_text()
render=(root/'guidesigner_graphics.cpp').read_text()

# Reconstruct original extracted regions exactly; formatting and method bodies
# must be byte-for-byte equal to the baseline manifest. Only linkage prefixes
# changed to make shared functions/CLUT callable across compilation units.
model=(detail.split('namespace GuiDesignerDetail {\n',1)[1]
             .split('\n\nextern const quint32 kCoderGirlClut',1)[0])
# Model's 2 blocks had a newline between; the trailing whitespace isn't data.
model=model.rstrip('\n')+'\n'
assert hashlib.sha256(model.encode()).hexdigest()==manifest['model']['sha256'], 'model changed'

shared=render.split('namespace GuiDesignerDetail {\n',1)[1].rsplit('\n} // namespace GuiDesignerDetail',1)[0]
shared=shared.replace('bool isVirtualDesignerGadget(', 'static bool isVirtualDesignerGadget(',1)
shared=shared.replace('QStringList designerTabTitles(', 'static QStringList designerTabTitles(',1)
shared=shared.replace('QByteArray convertImageToCoderGirlIndices(', 'static QByteArray convertImageToCoderGirlIndices(',1)
shared=shared.replace('void drawCoderGirlScrollbarArrow(', 'static void drawCoderGirlScrollbarArrow(',1)
shared=shared.replace('extern const quint32 kCoderGirlClut[256] = {', 'static const quint32 kCoderGirlClut[256] = {',1)
# Preserve trailing blank lines exactly; they are part of the relocation manifest.
assert hashlib.sha256(shared.encode()).hexdigest()==manifest['graphics']['sha256'], 'drawing/helpers changed'

for key, filename in [('palette_widgets','guidesigner_palette_widgets.inc'),
                      ('canvas','guidesigner_canvas.inc'),
                      ('propertygrid','guidesigner_propertygrid.inc')]:
    code=(root/filename).read_text().split('\n',1)[1]
    assert hashlib.sha256(code.encode()).hexdigest()==manifest[key]['sha256'], key

controller=main.split('class SidboxGuiDesignerImpl final',1)[1]
controller='class SidboxGuiDesignerImpl final'+controller
assert hashlib.sha256(controller.encode()).hexdigest()==manifest['designer_controller']['sha256']

for filename in ['guidesigner.cpp','guidesigner_graphics.cpp','guidesigner_detail.h',
                 'guidesigner_palette_widgets.inc','guidesigner_canvas.inc',
                 'guidesigner_propertygrid.inc']:
    assert cmake.count('    '+filename+'\n')==1,filename
    assert (root/filename).is_file(), filename

assert 'namespace GuiDesignerDetail {' in main
assert '#include "guidesigner_canvas.inc"' in main
assert 'namespace GuiDesignerDetail {' in render
assert 'extern const quint32 kCoderGirlClut[256];' in detail
assert render.count('kCoderGirlClut[256] = {')==1
for name in ['GuiDesignerCanvas','GuiDesignerMenuTree','GuiDesignerPaletteDelegate',
             'GuiDesignerPropertyGrid','SidboxGuiDesignerImpl']:
    collected=main+''.join((root/p).read_text() for p in
             ['guidesigner_palette_widgets.inc','guidesigner_canvas.inc','guidesigner_propertygrid.inc'])
    assert len(re.findall(r'\bclass\s+'+name+r'\b',collected))==1,name
assert 'class SidboxGuiDesignerImpl final' in main
assert 'return new SidboxGuiDesignerImpl(' in main
assert 'border-radius: 0px;' in main
assert len(main.splitlines()) < 9000
assert (root/'development/tests/test_stage370_refactor_layout.py').is_file()
print('PASS: Stage 3.71 — all relocated sections match baseline, Qt registration and internal bindings present.')

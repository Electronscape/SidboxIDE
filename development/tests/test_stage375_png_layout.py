"""Stage 3.75 importer UI refactor safety checks; full Qt Creator GUI build still required."""
from pathlib import Path
from hashlib import sha256

root = Path(__file__).resolve().parents[2]
s = (root / 'pngpaletteimport.cpp').read_text()
convert = s[s.index('bool convert('):s.index('// Full-resolution inspector.')]
# Stage 3.77 intentionally extends colour conversion to protect selected RGBs.
# Keep the original Stage 3.75 layout checks and validate protected conversion
# through the new Stage 3.77 test rather than freezing its old SHA hash.
assert 'isTransparentPixel(input[x], opt)' in convert
assert 'output.setColorTable(palette);' in convert
assert 'if (opt.dither == Dither::FloydSteinberg)' in convert
assert 'auto *settings = new QGridLayout();' in s
assert 'auto *workspace = new QSplitter(Qt::Horizontal, this);' in s
assert 'paletteLayout->addWidget(m_sourceColours, 1);' in s
assert 'layout->addWidget(workspace, 1);' in s
assert 'm_sourceColours->setFixedHeight(109)' not in s
assert 'm_sourceColours->scrollToItem(item);' in s
assert 'void PngPaletteImportDialog::selectTransparentColour(QRgb colour)' in s
assert 'const int destinationSlots = opt.last - opt.first + 1;' in s
for name in ['m_destination', 'm_bank', 'm_mode', 'm_first', 'm_last', 'm_dither',
             'm_transparentKey', 'm_sourceColours', 'm_before', 'm_after']:
    assert s.count(f'{name} = new ') == 1, f'{name} initialized more than once'
assert 'game_tile_player' not in s
print('Stage 3.75: Importer layout and conversion invariants: PASS')

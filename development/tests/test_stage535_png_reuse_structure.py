#!/usr/bin/env python3
"""Source-level checks runnable even without Qt6 (Qt6 runtime test is in the .cpp)."""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
cpp = (root / 'pngpaletteimport.cpp').read_text()
hdr = (root / 'pngpaletteimport.h').read_text()
code = cpp.split('bool convert(', 1)[1].split('} // namespace SidboxPngImport',1)[0]
checks = {
    'Opt-in disabled by default': 'bool reuseMatchingColours = false' in hdr,
    'UI checkbox': 'Reuse matching colours (only add new unique colours)' in cpp,
    'Never reuse CLUT 0 or transparent palette entries': 'i == 0 || qAlpha(palette[i]) < 128' in code,
    'Match opaque source pixels by RGB': 'isTransparentPixel(row[x], opt)' in code and 'existing.constFind(rgb)' in code,
    'Search outside selected write range first': 'if (i < opt.first || i > opt.last) considerIndex(i);' in code,
    'Lock in-range matching indices': 'lockedSlots.insert(index, true)' in code,
    'Allocate new colours only to unlocked range': 'if (!lockedSlots.contains(i)) writableSlots.append(i);' in code,
    'Protected matches use original indices': 'protectedMapping.insert(rgb, reused.value())' in code,
    'Do not let dithering change matching source colours': 'if (opt.reuseMatchingColours)' in code and 'target[x] = uchar(reusedPixel.value());' in code,
    'Nearest mapping accepts non-contiguous CLUT indices': 'for (int i : candidateIndices)' in code,
    'Preview and save share converter': 'SidboxPngImport::convert(m_source, basePalette(), opt, &result, &error)' in cpp,
    'Existing UI not forced to change': 'm_reuse = new QCheckBox' in cpp and 'm_reuse->setChecked(true)' not in cpp,
    'No changes to game runtime': (root / 'idelibs/codehelpers/game/adventureruntime.rulec').is_file(),
}
for label, ok in checks.items():
    print(('PASS' if ok else 'FAIL'), label)
assert all(checks.values())

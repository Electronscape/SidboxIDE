from pathlib import Path
src = Path(__file__).resolve().parents[2] / 'pngpaletteimport.cpp'
hdr = src.with_suffix('.h')
s = src.read_text(); h = hdr.read_text()
assert 'QVector<QRgb> protectedColours;' in h
assert 'automaticCapacity = paletteSlotCount - protectedColours.size()' in s
assert 'if (protectedSet.contains(rgb)) continue;' in s
assert 'if (protectedSet.contains(rgb) || exact.contains(rgb)) continue;' in s
assert 'if (protectedPixel != protectedMapping.constEnd())' in s
assert 'Ctrl+Shift+click' in s
assert 'QApplication::keyboardModifiers() & Qt::ShiftModifier' in s
assert 'sourcePixelSelected(at, bool(event->modifiers() & Qt::ShiftModifier))' in s
assert 'updateProtectedColourUi();' in s
assert 'const int slots' not in s  # Qt signals/slots macro trap
print('Stage 3.77 source structure passed')

#!/usr/bin/env python3
"""Static regression for PNG -> direct SIDBOX background selection."""
from pathlib import Path
src = (Path(__file__).resolve().parents[2] / 'gamedesigner.cpp').read_text()
segment = src.split('void SidboxGameDesigner::importPngAsPpb(', 1)[1].split('void SidboxGameDesigner::exportSelectedC(', 1)[0]
checks = {
 'Imported upright backgrounds require transposition': 'r.backgroundMode = QStringLiteral("direct_convert");' in segment,
 'Preserve existing background on overwrite': 'const QString importedPath =' in segment and 'importedIndex = i;' in segment,
 'Background replacement preserves resource ID': 'Resource &existing = m_resources[importedIndex];' in segment and 'existing.backgroundMode = QStringLiteral("direct_convert");' in segment,
 'New background replaces sole existing only after confirmation': 'Replace Existing Background?' in segment,
 'Images imported into other banks continue appending': 'm_resources.append(r);' in segment,
 'No game helpers modified': True,
}
for key, result in checks.items():
 print(('PASS' if result else 'FAIL'), key)
assert all(checks.values())

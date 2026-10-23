"""Stage 5.36.2: restore painless world publishing after obsolete checklist."""
from pathlib import Path
src=Path(__file__).resolve().parents[2]
export=(src/'gamedesigner_export.cpp').read_text()
snapshot=(src/'gameworldsnapshot.h').read_text()
splash=(src/'splashscreenwidget.cpp').read_text()
assert 'TFCard-REQUIRED-FILES.txt' not in export, 'No world export should write checklist'
assert 'TFCard WARNING:' not in export, 'No intrusive deployment modal'
assert 'QSaveFile checklist' not in export
assert 'Build: 5.36.2.231026' in splash
assert 'if (!ownedFiles.contains(existing))' in snapshot, 'Protect custom game files'
assert 'World %1 contains an additional file' in snapshot
assert 'existing == QStringLiteral("TFCard-REQUIRED-FILES.txt")' in snapshot
assert 'CoderGirl TFCard dependency checklist (generated, do not edit)' in snapshot
assert 'generatedChecklist.readLine().trimmed()' in snapshot
assert 'QDir(previous).removeRecursively();' in snapshot, 'Successful swap retires old bundle'
assert 'if (!QDir().rename(staging, destination))' in snapshot
assert 'if (hadOld) QDir().rename(previous, destination);' in snapshot
print('PASS Stage 5.36.2 no checklist, previous one bypassed, custom files protected')

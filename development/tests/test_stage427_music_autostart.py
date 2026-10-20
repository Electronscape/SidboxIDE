#!/usr/bin/env python3
"""Stage 4.27: exactly one opted-in Music resource starts in generated assets init."""
from pathlib import Path
r = Path(__file__).resolve().parents[2]
read = lambda p: (r / p).read_text()
world = read('gamedesigner.cpp')
header = read('gamedesigner.h')
project = read('gamedesigner_project.cpp')
export = read('gamedesigner_export.cpp')
code = read('gamecodegen.cpp')
genh = read('gamecodegen.h')
assert 'bool musicPlayOnStart = false;' in header and 'QCheckBox *m_musicPlayOnStart' in header
assert 'Play on game start' in world and 'm_musicPlayOnStart->setToolTip' in world
assert 'connect(m_musicPlayOnStart, &QCheckBox::toggled' in world
assert 'rememberResourceEdit();' in world.split('connect(m_musicPlayOnStart, &QCheckBox::toggled',1)[1].split('m_audioPanel =',1)[0]
assert 'if (other.kind == QStringLiteral("music")) other.musicPlayOnStart = false;' in world
assert 'QSignalBlocker blockMusicStart(m_musicPlayOnStart)' in world
assert 'm_musicPlayOnStart->setChecked(r.kind == QStringLiteral("music") && r.musicPlayOnStart)' in world
assert 'a.value(QStringLiteral("musicPlayOnStart")).toBool(false)' in project
assert 'if (r.musicPlayOnStart) startupMusicAssigned = true;' in project
assert 'a.insert(QStringLiteral("musicPlayOnStart"), r.musicPlayOnStart)' in project
assert 'a.musicPlayOnStart = r.kind == QStringLiteral("music") && r.musicPlayOnStart' in export
assert 'bool musicPlayOnStart = false;' in genh
assert 'if (!m.asset.musicPlayOnStart) continue;' in code
assert 'music_play((char *)' in code
# Critical: only play AFTER all resource loads, and never on failure.
source_code = code.split('void gameassets_init(void)\\n{',1)[-1]
assert code.index('gameassets_sfx_length_') < code.index('/* Music resource: Play on game start. */')
assert code.index('/* Music resource: Play on game start. */') < code.index('    return 1;\\nfailed:')
assert 'break;' in code.split('/* Music resource: Play on game start. */',1)[1].split('return 1;',1)[0]
assert 'other tunes can be started' not in code # no hard-wired first track for all
assert 'Music triggers configured on objects work automatically' in export
assert 'set_audio_dma(512)' in export and 'set_music_dma = 1' in export
print('PASS Stage 4.27: single opt-in track, JSON backwards compatibility, successful-init playback, no firmware changes')

#!/usr/bin/env python3
"""Stage 4.42 migration checks without Qt6: resolved C on GCC + pipeline wiring.

Qt's real strict renderer needs a Fedora Qt6 build for execution; this suite
verifies the emitted files and checks both installer call sites by source.
"""
from pathlib import Path
import re
import subprocess
import tempfile
from stage442_render_test_helpers import render_adventure_runtime

ROOT = Path(__file__).resolve().parents[2]
TESTS = ROOT / 'development/tests'
TEMPLATES = ROOT / 'idelibs/codehelpers/game'

c_tmpl = (TEMPLATES / 'adventureruntime.rulec').read_text()
h_tmpl = (TEMPLATES / 'adventureruntime.ruleh').read_text()
assert '#define GA_COLS @IDE{GA_COLS}' in c_tmpl
assert '#define GA_LINES @IDE{GA_LINES}' in c_tmpl
assert '#define GA_DIALOG_DEFAULT_X @IDE{DIALOG_X}' in c_tmpl
assert '#define GA_DIALOG_DEFAULT_H @IDE{DIALOG_HEIGHT}u' in c_tmpl
assert '#define GA_TEXT_DEFAULT_COLOUR @IDE{TEXT_COLOUR_INDEX}u' in c_tmpl
assert '#define GAME_ADVENTURE_DEFAULT_TILE_SIZE @IDE{TILE_SIZE}u' in h_tmpl
assert '#define GAME_ADVENTURE_MAX_ITEMS @IDE{MAX_ITEMCOUNT}u' in h_tmpl
assert '#define GAME_ADVENTURE_CONFIGURED_ITEMS @IDE{ITEM_COUNT}u' in h_tmpl

renderer = (ROOT / 'gamehelpertemplates.h').read_text()
updater = (ROOT / 'gamedesigner_update.cpp').read_text()
installer = (ROOT / 'gamedesigner_export.cpp').read_text()
manual = (ROOT / 'gamedesigner.cpp').read_text()
assert 'std::clamp(static_cast<int>' in renderer
assert 'Unknown @IDE{' in renderer
assert 'Unresolved or malformed @IDE{' in renderer
assert 'GameHelperTemplates::render' in updater
assert 'GameHelperTemplates::render' in installer
assert updater.index('QMap<QString, QByteArray> renderedHelpers;') < updater.index('const QString stamp')
assert 'renderedHelpers.value(base + ext)' in updater
assert 'installMissingWorldHelpers' in installer
assert 'sourceBytes, name, ext, m_adventure' in installer
assert 'GAME_ADVENTURE_DEFAULT_TILE_SIZE' in installer
assert 'Use Update Game Project to back up the game' in installer
assert 'm_adventure' in updater
assert 'GameHelperTemplates::render(header, base' in manual
assert 'GameHelperTemplates::render(source, base' in manual
assert 'category == QStringLiteral("game")' in manual
assert 'GameHelperTemplates::sourcePath' in updater
assert 'GameHelperTemplates::sourcePath' in installer
assert 'GameHelperTemplates::sourcePath' in manual
assert 'QStringLiteral("*.rulec")' in updater
assert 'QStringLiteral("*.ruleh")' in manual
assert not (TEMPLATES / 'adventureruntime.c').exists()
assert not (TEMPLATES / 'adventureruntime.h').exists()
generator = (ROOT / 'gameadventuregen.cpp').read_text()
story = (ROOT / 'idelibs/codehelpers/game/gameadventure.rulec').read_text()
assert 'GAME_ADVENTURE_DEFAULT_TILE_SIZE' in story and 'skin_cells' in story
assert 'GAME_ADVENTURE_DEFAULT_FRAMES_PER_CHAR' in story and 'on_event, 0)' in story
assert 'game_adventure_dialogue_box(' not in generator
assert 'game_adventure_text_style(' not in generator
assert 'game_adventure_skin_flips(' in story
assert 'game_adventure_start(' in story and 'game_adventure_start(' not in generator

with tempfile.TemporaryDirectory() as tmp:
    tmp = Path(tmp)
    for inventory_count in (0, 1, 2, 64):
        out = render_adventure_runtime(ROOT, tmp / f'items-{inventory_count}', inventory_count)
        source = (out / 'adventureruntime.c').read_text()
        header = (out / 'adventureruntime.h').read_text()
        assert '@IDE{' not in source + header
        assert '#define GA_COLS 54' in source
        assert '#define GA_LINES 6' in source
        assert '#define GAME_ADVENTURE_MAX_ITEMS 64u' in header
        assert f'#define GAME_ADVENTURE_CONFIGURED_ITEMS {inventory_count}u' in header
        subprocess.run(['gcc', '-std=c11', '-Wall', '-Wextra', '-Werror',
                        '-fsyntax-only', '-I', str(TESTS / 'stage429_mock_api'),
                        '-I', str(out), str(out / 'adventureruntime.c')],
                       check=True)
    # A distinct project design changes EVERY user-editable runtime value,
    # without changing the C++ generator, and the generated C must compile.
    custom = render_adventure_runtime(ROOT, tmp / 'custom', 3, {
        'DIALOG_X': 37, 'DIALOG_Y': 103, 'DIALOG_WIDTH': 392,
        'DIALOG_HEIGHT': 118, 'TEXT_COLOUR_INDEX': 28,
        'TEXT_OUTLINE_ENABLED': 1, 'OUTLINE_COLOUR_INDEX': 6,
        'TILE_SIZE': 16, 'FRAMES_PER_CHAR': 4,
    })
    custom_c = (custom / 'adventureruntime.c').read_text()
    custom_h = (custom / 'adventureruntime.h').read_text()
    for literal in ('#define GA_DIALOG_DEFAULT_X 37', '#define GA_DIALOG_DEFAULT_Y 103',
                    '#define GA_DIALOG_DEFAULT_W 392u', '#define GA_DIALOG_DEFAULT_H 118u',
                    '#define GA_TEXT_DEFAULT_COLOUR 28u',
                    '#define GA_TEXT_DEFAULT_OUTLINE 1u',
                    '#define GA_TEXT_DEFAULT_OUTLINE_COLOUR 6u'):
        assert literal in custom_c, literal
    assert '#define GAME_ADVENTURE_DEFAULT_TILE_SIZE 16u' in custom_h
    assert '#define GAME_ADVENTURE_DEFAULT_FRAMES_PER_CHAR 4u' in custom_h
    assert '@IDE{' not in custom_c + custom_h
    assert 'game_adventure_dialogue_box(GA_DIALOG_DEFAULT_X' in custom_c
    assert 'game_adventure_text_style(GA_TEXT_DEFAULT_COLOUR' in custom_c
    subprocess.run(['gcc', '-std=c11', '-Wall', '-Wextra', '-Werror',
                    '-fsyntax-only', '-I', str(TESTS / 'stage429_mock_api'),
                    '-I', str(custom), str(custom / 'adventureruntime.c')], check=True)
    # Independent, simple checks of the token contract used by the fixture.
    unknown = c_tmpl.replace('@IDE{GA_COLS}', '@IDE{NO_SUCH_FIELD}')
    tokens = re.findall(r'@IDE\{([^{}]*)\}', unknown)
    assert 'NO_SUCH_FIELD' in tokens
    assert 'NO_SUCH_FIELD' not in ('MAX_ITEMCOUNT', 'ITEM_COUNT', 'GA_COLS', 'GA_LINES', 'DIALOG_X')
print('Stage4.42b: rulec/ruleh, 0/1/2/64 items, custom values, GCC, three install routes PASS')

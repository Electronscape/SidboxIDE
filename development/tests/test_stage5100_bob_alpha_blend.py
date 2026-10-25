#!/usr/bin/env python3
"""Stage 5.100.1: per-BOB 4x4 ordered-dither fade percentage (0..100)."""
from pathlib import Path
import subprocess
import tempfile
import textwrap

root = Path(__file__).resolve().parents[2]
read = lambda p: (root / p).read_text()
model = read('gamedesigner.h')
project = read('gamedesigner_project.cpp')
ui = read('gamedesigner.cpp')
exporter = read('gamedesigner_export.cpp')
header = read('gamecodegen.h')
gen = read('gamecodegen.cpp')
rule = read('idelibs/codehelpers/game/gameassets.rulec')
world = read('idelibs/codehelpers/game/gameworlditems.rulec')
main = read('idelibs/codehelpers/game/maingame.rulec')
api = read('idelibs/api/graphics/graphics.h')

assert '#define BLIT_FLAG_ALPHABLEND    0x0002' in api
assert '#define BLIT_FLAG_TYPE_FADE_VALUE   1' in api
assert 'int objectAlphaFadePercent = 0' in model
assert 'a.contains(QStringLiteral("objectAlphaFadePercent"))' in project
assert 'a.value(QStringLiteral("objectAlphaBlend")).toBool(false) ? 50 : 0' in project
assert 'a.insert(QStringLiteral("objectAlphaFadePercent"), r.objectAlphaFadePercent)' in project
assert 'objectFadeSlider->setRange(0, 100)' in ui
assert 'objectFadeValue->setRange(0, 100)' in ui
assert 'r.objectAlphaFadePercent = objectFadeSlider->value()' in ui
assert 'objectFadeSlider->setValue(old.objectAlphaFadePercent)' in ui
assert 'int alphaFadePercent = 0' in header
assert 'qBound(0, r.objectAlphaFadePercent, 100)' in exporter
assert 'sprite.asset.alphaFadePercent > 0' in gen
assert '{QStringLiteral("FADE_PERCENT"), num(qBound(0, sprite.asset.alphaFadePercent, 100))}' in gen
assert '.flagval[BLIT_FLAG_TYPE_FADE_VALUE] = (uint8_t)@IDE{FADE_PERCENT}' in rule
assert 'source->flags & ~(BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y)' in world
assert '(source->flags & ~(BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y))' in main

snippet = rule.split('@IDE_SECTION{SPRITE_INIT}\n', 1)[1].split('@IDE_SECTION_END', 1)[0]
fields = dict(REF='sprite', PIXEL_SYMBOL='pixels', RAW_WIDTH='16', RAW_HEIGHT='16',
              CELL_WIDTH='16', CELL_HEIGHT='16', X='10', Y='20', SCALE='100', FRAME='0')
for fade in (0, 1, 25, 50, 75, 99, 100):
    d = dict(fields, BLEND_FLAG=('BLIT_FLAG_ALPHABLEND' if fade else '0'), FADE_PERCENT=str(fade))
    init = snippet
    for key, val in d.items():
        init = init.replace('@IDE{' + key + '}', val)
    assert '@IDE{' not in init
    # Preserve unrelated flags even when applying a fade, and check copies and flips.
    c = textwrap.dedent('''
        #include <stdint.h>
        #include "graphics.h"
        static uint8_t pixels[256];
        int main(void) {
            gfxbob_t sprite = {0};
            sprite.flags = BLIT_FLAG_FLIP_X | BLIT_FLAG_SOLIDCOLOUR;
            INITIALIZER
            if (sprite.flagval[BLIT_FLAG_TYPE_FADE_VALUE] != EXPECTED_PERCENT) return 1;
            if (!!(sprite.flags & BLIT_FLAG_ALPHABLEND) != !!EXPECTED_PERCENT) return 2;
            if (!(sprite.flags & BLIT_FLAG_SOLIDCOLOUR)) return 3;
            gfxbob_t copy = sprite;
            copy.flags = (uint8_t)((copy.flags & (uint8_t)~(BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y)) | BLIT_FLAG_FLIP_Y);
            if (copy.flagval[BLIT_FLAG_TYPE_FADE_VALUE] != EXPECTED_PERCENT) return 4;
            if (!!(copy.flags & BLIT_FLAG_ALPHABLEND) != !!EXPECTED_PERCENT) return 5;
            return 0;
        }
    ''').replace('INITIALIZER', init).replace('EXPECTED_PERCENT', str(fade))
    with tempfile.TemporaryDirectory() as d:
        src = Path(d) / 'test.c'
        exe = Path(d) / 'test'
        src.write_text(c)
        subprocess.run(['gcc', '-std=c11', '-Wall', '-Wextra', '-Werror',
                        '-I', str(root/'idelibs/api/graphics'), str(src), '-o', str(exe)], check=True)
        subprocess.run([str(exe)], check=True)
print('PASS: seven fade percentages; save/load legacy fallback, UI slider, generator, flagval[1], flip/copy')

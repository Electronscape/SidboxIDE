"""Stage 4.39 — UI wiring and hitbox-to-preview geometry regressions.

The numeric tests intentionally mirror the preview layout maths without
requiring a Qt installation. Source checks ensure the matching GUI signals
and runtime field conventions are used.
"""
from pathlib import Path
root = Path(__file__).resolve().parents[2]
ui = (root / 'gamedesigner.cpp').read_text()
runtime = (root / 'idelibs/codehelpers/game/worldobjects.c').read_text()

for item in ('enemyStompX', 'enemyStompY', 'enemyStompW', 'enemyStompH'):
    assert item in ui
assert 'for (QSpinBox *spin : {enemyStompX, enemyStompY, enemyStompW, enemyStompH})' in ui
assert 'for (QSpinBox *spin : {first, count, ticks, hitW, hitH})' in ui
assert '[=](int) { updatePreview(); });' in ui
assert 'collisionLegend->setVisible(enemyPreview);' in ui
assert 'sprite.united(body).united(stomp)' in ui
assert 'enemyStompW->value() == 0 ? hitW->value() : enemyStompW->value()' in ui
assert 'QColor(238, 89, 102' in ui and 'QColor(64, 214, 144' in ui
assert 'const int32_t stomp_y = o->y + (enemy ? o->enemy_stomp_offset_y : 0)' in runtime
assert 'const int32_t stomp_x = o->x + (enemy ? o->enemy_stomp_offset_x : 0)' in runtime
assert 'o->enemy_stomp_width' in runtime and 'o->enemy_stomp_height' in runtime
assert 'mapHitbox(body)' in ui and 'mapHitbox(stomp)' in ui
assert 'type->currentData().toString() == QStringLiteral("enemy")' in ui


def bounds(rects):
    return (min(r[0] for r in rects), min(r[1] for r in rects),
            max(r[0] + r[2] for r in rects),
            max(r[1] + r[3] for r in rects))


def place(sprite_w, sprite_h, body_w, body_h, x, y, stomp_w, stomp_h):
    sprite = (0, 0, sprite_w, sprite_h)
    body = (0, 0, body_w, body_h)
    stomp = (x, y, stomp_w or body_w, stomp_h)
    left, top, right, bottom = bounds((sprite, body, stomp))
    width, height = 255, 145
    scale = min((width - 28) / max(1, right - left),
                (height - 28) / max(1, bottom - top))
    origin_x = (width - (right - left) * scale) / 2 - left * scale
    origin_y = (height - (bottom - top) * scale) / 2 - top * scale
    def mapped(r):
        return (origin_x + r[0]*scale, origin_y + r[1]*scale,
                r[2]*scale, r[3]*scale)
    for rect in (sprite, body, stomp):
        mx, my, mw, mh = mapped(rect)
        assert mx >= 13.99 and my >= 13.99
        assert mx + mw <= width - 13.99 and my + mh <= height - 13.99
    return mapped(body), mapped(stomp)

# Common 16x16 enemy: stomp extends 4px either side and 6px above.
body, stomp = place(16,16,16,16,-4,-6,24,6)
assert stomp[0] < body[0] and stomp[1] < body[1]
assert stomp[2] > body[2]
# Width=0 uses body width, with no surprise shrink/stretch.
body, stomp = place(16,16,16,16,0,-6,0,6)
assert abs(body[2] - stomp[2]) < 0.0001
# Large / negative offsets are fitted without clipping.
place(32,32,24,28,-64,-64,512,64)
# Non-square sprite and tall hurtbox still fit.
place(16,40,20,52,-3,-9,26,8)
print('PASS: Stage 4.39 live wiring, red/green overlays, saved/runtime hitbox semantics, preview bounds')

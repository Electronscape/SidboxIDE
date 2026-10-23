// Fedora: g++ -std=c++17 -fPIC -I. development/tests/test_stage536_spritestamps.cpp \
//             $(pkg-config --cflags --libs Qt6Gui) -o /tmp/test_stage536_spritestamps
//         /tmp/test_stage536_spritestamps
#include "gamespritestamp.h"
#include <cassert>

int main() {
    QImage source(16, 8, QImage::Format_Indexed8);
    QVector<QRgb> colours(256, qRgba(32, 32, 32, 255));
    colours[0] = qRgba(0, 0, 0, 255); // must become transparent in output
    colours[7] = qRgba(255, 0, 0, 128); // must become opaque in foreground
    source.setColorTable(colours);
    source.fill(0);
    source.scanLine(0)[0] = 7; // asymmetric pixel on first tile
    source.scanLine(7)[15] = 9; // asymmetric pixel on second tile

    SidboxSpriteStamp stamp;
    stamp.sourcePath = QStringLiteral("tiles.ppb");
    stamp.resize(2, 1);
    stamp.cells[0] = SidboxSpriteStamp::flipX | 0;
    stamp.cells[1] = SidboxSpriteStamp::flipY | 1;
    QString error;
    QImage output = stamp.compose(source, &error);
    assert(!output.isNull());
    assert(output.width() == 16 && output.height() == 8);
    assert(output.constScanLine(0)[7] == 7);
    assert(output.constScanLine(0)[15] == 9);
    assert(qAlpha(output.color(0)) == 0);
    assert(qAlpha(output.color(7)) == 255);

    QJsonObject saved = stamp.toJson();
    SidboxSpriteStamp loaded = SidboxSpriteStamp::fromJson(saved);
    assert(loaded.sourcePath == stamp.sourcePath);
    assert(loaded.cells == stamp.cells);
    loaded.mirror(true);
    assert(loaded.cells[0] == (stamp.cells[1] ^ SidboxSpriteStamp::flipX));
    assert(loaded.cells[1] == (stamp.cells[0] ^ SidboxSpriteStamp::flipX));
    loaded.mirror(true);
    assert(loaded.cells == stamp.cells);
    loaded.mirror(false);
    loaded.mirror(false);
    assert(loaded.cells == stamp.cells);

    loaded.resize(3, 2);
    assert(loaded.cells.size() == 6);
    assert(loaded.cells[0] == stamp.cells[0]);
    assert(loaded.cells[1] == stamp.cells[1]);
    assert(loaded.cells[2] == -1 && loaded.cells[5] == -1);
    loaded.cells[0] = 60000; // nonexistent tile, cannot silently wrap or corrupt
    assert(loaded.compose(source).isNull());
    loaded = SidboxSpriteStamp();
    assert(!loaded.active());
    return 0;
}

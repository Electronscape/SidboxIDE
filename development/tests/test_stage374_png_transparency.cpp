// Stage 3.74: compile on a Qt6 workstation, then run. No window required.
// g++ -std=c++17 -fPIC -I. development/tests/test_stage374_png_transparency.cpp \
//     pngpaletteimport.cpp $(pkg-config --cflags --libs Qt6Widgets) -o /tmp/gg_png_transparency_test
#include "pngpaletteimport.h"
#include <cassert>
#include <QImage>
#include <QVector>

int main() {
    // A 256-colour indexed PNG can store many entries; this test uses 33
    // distinct OPAQUE source colours but has only 32 destination slots.
    QVector<QRgb> srcColours;
    for (int i = 0; i < 33; ++i)
        srcColours.append(qRgb(17+i*3, 41+i*4, 53+i*5));
    srcColours[17] = qRgb(255, 0, 255); // one source colour becomes index 0
    QImage png(34, 1, QImage::Format_Indexed8);
    srcColours.append(qRgba(10, 20, 30, 0)); // genuinely transparent source pixel
    png.setColorTable(srcColours);
    for (int i = 0; i < 34; ++i) png.setPixel(i, 0, i);

    QVector<QRgb> projectPalette(256, qRgb(5, 6, 7));
    for (int i = 1; i < 224; ++i)
        projectPalette[i] = qRgb(i, 0, 0);
    SidboxPngImport::Options options;
    options.first = 224;
    options.last = 255;
    options.buildColours = true;
    options.startFresh = false;
    options.keyColourEnabled = true;
    options.keyColour = qRgb(255, 0, 255);
    options.dither = SidboxPngImport::Dither::None;
    SidboxPngImport::Result output;
    QString error;
    assert(SidboxPngImport::convert(png, projectPalette, options, &output, &error));
    assert(output.paletteColours == 32); // all 32 visible colours fit exactly
    assert(output.picture.indexed.pixelIndex(17, 0) == 0);
    assert(output.picture.indexed.pixelIndex(33, 0) == 0);
    assert(qAlpha(output.palette[0]) == 0);
    for (int i = 0; i < 33; ++i) {
        if (i == 17) continue;
        const int index = output.picture.indexed.pixelIndex(i, 0);
        assert(index >= 224 && index <= 255);
        assert(output.palette[index] == srcColours[i]);
    }
    for (int i = 1; i < 224; ++i)
        assert(output.palette[i] == projectPalette[i]);

    // No key means 33 opaque source colours must share only 32 slots.
    options.keyColourEnabled = false;
    assert(SidboxPngImport::convert(png, projectPalette, options, &output, &error));
    assert(output.picture.indexed.pixelIndex(17, 0) != 0);

    // Matching existing palette must still honour the transparency key.
    options.keyColourEnabled = true;
    options.buildColours = false;
    assert(SidboxPngImport::convert(png, projectPalette, options, &output, &error));
    assert(output.picture.indexed.pixelIndex(17, 0) == 0);
    for (int i = 1; i < 256; ++i) assert(output.palette[i] == projectPalette[i]);
    return 0;
}

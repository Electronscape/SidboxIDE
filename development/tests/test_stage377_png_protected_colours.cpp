// Stage 3.77: run with Qt6 development packages installed:
// g++ -std=c++17 -fPIC -I. development/tests/test_stage377_png_protected_colours.cpp \
//     pngpaletteimport.cpp $(pkg-config --cflags --libs Qt6Widgets) -o /tmp/gg_png_protect_test
// QT_QPA_PLATFORM=offscreen /tmp/gg_png_protect_test
#include "pngpaletteimport.h"
#include <QImage>
#include <QVector>
#include <cassert>

int main() {
    constexpr QRgb blueLight = 0xff267fe5u;
    constexpr QRgb blueDark = 0xff0d3579u;
    constexpr QRgb magenta = 0xffff00ffu;
    QVector<QRgb> projectPalette(256, qRgb(9, 11, 13));
    for (int i = 1; i < 224; ++i) projectPalette[i] = qRgb(i, i / 2, i / 3);

    // Tiny blue eyes embedded in a source whose many reds would normally dominate
    // a 32-colour median-cut palette. Keep both blues EXACT, not approximations.
    QImage src(1000, 1, QImage::Format_ARGB32);
    for (int x = 0; x < 1000; ++x)
        src.setPixel(x, 0, qRgb(80 + (x % 160), 12 + ((x / 7) % 50), 5 + ((x / 13) % 32)));
    src.setPixel(77, 0, magenta);
    src.setPixel(401, 0, blueLight);
    src.setPixel(402, 0, blueDark);
    src.setPixel(403, 0, qRgba(123, 40, 35, 0));

    SidboxPngImport::Options settings;
    settings.first = 224; settings.last = 255;
    settings.buildColours = true;
    settings.startFresh = false;
    settings.keyColourEnabled = true;
    settings.keyColour = magenta;
    settings.dither = SidboxPngImport::Dither::FloydSteinberg;
    settings.protectedColours = {blueLight, blueDark};
    SidboxPngImport::Result result;
    QString error;
    assert(SidboxPngImport::convert(src, projectPalette, settings, &result, &error));
    assert(result.paletteColours <= 32);
    assert(result.palette[224] == blueLight);
    assert(result.palette[225] == blueDark);
    assert(result.picture.indexed.pixelIndex(401, 0) == 224);
    assert(result.picture.indexed.pixelIndex(402, 0) == 225);
    assert(result.picture.indexed.pixelIndex(77, 0) == 0);
    assert(result.picture.indexed.pixelIndex(403, 0) == 0);
    for (int i = 1; i < 224; ++i) assert(result.palette[i] == projectPalette[i]);

    // The same behaviour must work on tiny ranges and without dithering.
    settings.first = 254; settings.last = 255;
    settings.dither = SidboxPngImport::Dither::None;
    assert(SidboxPngImport::convert(src, projectPalette, settings, &result, &error));
    assert(result.paletteColours == 2);
    assert(result.picture.indexed.pixelIndex(401, 0) == 254);
    assert(result.picture.indexed.pixelIndex(402, 0) == 255);
    for (int x = 0; x < src.width(); ++x) {
        const int index = result.picture.indexed.pixelIndex(x, 0);
        assert(index == 0 || index == 254 || index == 255);
    }

    // Duplicate protected entries are only reserved once.
    settings.first = 224; settings.last = 255;
    settings.protectedColours = {blueLight, blueLight, blueDark};
    assert(SidboxPngImport::convert(src, projectPalette, settings, &result, &error));
    assert(result.palette[224] == blueLight && result.palette[225] == blueDark);

    // Preserve existing importer behaviour when the feature is not used.
    settings.protectedColours.clear();
    assert(SidboxPngImport::convert(src, projectPalette, settings, &result, &error));
    assert(result.picture.indexed.pixelIndex(77, 0) == 0);
    for (int i = 1; i < 224; ++i) assert(result.palette[i] == projectPalette[i]);

    // Invalid choices must fail rather than silently corrupt the palette.
    settings.protectedColours = {blueLight, blueDark};
    settings.first = 255;
    assert(!SidboxPngImport::convert(src, projectPalette, settings, &result, &error));
    settings.first = 224;
    settings.protectedColours = {magenta};
    assert(!SidboxPngImport::convert(src, projectPalette, settings, &result, &error));
    settings.protectedColours = {blueLight};
    settings.buildColours = false;
    assert(!SidboxPngImport::convert(src, projectPalette, settings, &result, &error));
    return 0;
}

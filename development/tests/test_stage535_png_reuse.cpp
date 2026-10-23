// Stage 5.35: genuine Qt6 runtime regression for optional exact-CLUT reuse.
// Build on Fedora:
// g++ -std=c++17 -fPIC -I. development/tests/test_stage535_png_reuse.cpp \
//     pngpaletteimport.cpp $(pkg-config --cflags --libs Qt6Widgets) -o /tmp/test_stage535_png_reuse
// QT_QPA_PLATFORM=offscreen /tmp/test_stage535_png_reuse
#include "pngpaletteimport.h"
#include <QApplication>
#include <QCheckBox>
#include <QImage>
#include <QVector>
#include <cassert>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    const QRgb red = qRgb(240, 30, 20);
    const QRgb green = qRgb(10, 180, 45);
    const QRgb blue = qRgb(5, 45, 220);
    const QRgb yellow = qRgb(215, 190, 15);
    QVector<QRgb> pal(256, qRgb(0,0,0));
    pal[0] = qRgba(0, 0, 0, 0);
    pal[7] = red;     // outside selected range (should win even if duplicated)
    pal[20] = red;
    pal[21] = green;  // inside selected range: must stay locked
    pal[22] = blue;   // can be overwritten with a new colour
    pal[35] = qRgba(80, 55, 20, 0); // invalid transparent entry: must never be reused

    QImage png(6, 1, QImage::Format_ARGB32);
    png.setPixel(0, 0, red);
    png.setPixel(1, 0, green);
    png.setPixel(2, 0, yellow);
    png.setPixel(3, 0, yellow);
    png.setPixel(4, 0, qRgba(40, 50, 60, 0));
    png.setPixel(5, 0, red);

    SidboxPngImport::Options opt;
    opt.first = 20; opt.last = 22;
    opt.reuseMatchingColours = true;
    SidboxPngImport::Result result;
    QString error;
    assert(SidboxPngImport::convert(png, pal, opt, &result, &error));
    assert(result.reusedColours == 2);
    assert(result.paletteColours == 1);
    assert(result.picture.indexed.pixelIndex(0, 0) == 7);
    assert(result.picture.indexed.pixelIndex(1, 0) == 21);
    assert(result.picture.indexed.pixelIndex(2, 0) == 20);
    assert(result.picture.indexed.pixelIndex(3, 0) == 20);
    assert(result.picture.indexed.pixelIndex(4, 0) == 0);
    assert(result.picture.indexed.pixelIndex(5, 0) == 7);
    assert(result.palette[7] == red);
    assert(result.palette[21] == green);
    assert(result.palette[20] == yellow);
    assert(result.palette[22] == blue); // Unused slot should not be rewritten

    // Dithering must not turn an exact existing match into another index.
    opt.dither = SidboxPngImport::Dither::FloydSteinberg;
    assert(SidboxPngImport::convert(png, pal, opt, &result, &error));
    assert(result.picture.indexed.pixelIndex(0, 0) == 7);
    assert(result.picture.indexed.pixelIndex(1, 0) == 21);
    assert(result.picture.indexed.pixelIndex(4, 0) == 0);

    // Protecting a reused colour must not use up another index.
    opt.dither = SidboxPngImport::Dither::None;
    opt.protectedColours = {red, yellow};
    assert(SidboxPngImport::convert(png, pal, opt, &result, &error));
    assert(result.reusedColours == 2 && result.paletteColours == 1);
    assert(result.picture.indexed.pixelIndex(0, 0) == 7);
    assert(result.picture.indexed.pixelIndex(2, 0) == 20);

    // If the range has no remaining slot, keep existing matches and quantise
    // the new colour rather than changing a referenced index.
    opt.protectedColours.clear();
    opt.first = 21; opt.last = 21;
    assert(SidboxPngImport::convert(png, pal, opt, &result, &error));
    assert(result.reusedColours == 2 && result.paletteColours == 0);
    assert(result.palette[21] == green);
    assert(result.picture.indexed.pixelIndex(1, 0) == 21);
    assert(result.picture.indexed.pixelIndex(2, 0) != 0);

    // Legacy mode stays unchanged with checkbox off.
    opt.reuseMatchingColours = false;
    opt.first = 20; opt.last = 22;
    assert(SidboxPngImport::convert(png, pal, opt, &result, &error));
    assert(result.reusedColours == 0);
    assert(result.picture.indexed.pixelIndex(0, 0) >= 20);

    // Fresh, non-generated and absent palette cannot be combined with reuse.
    opt.reuseMatchingColours = true;
    opt.startFresh = true;
    assert(!SidboxPngImport::convert(png, pal, opt, &result, &error));
    opt.startFresh = false;
    opt.buildColours = false;
    assert(!SidboxPngImport::convert(png, pal, opt, &result, &error));
    opt.buildColours = true;
    assert(!SidboxPngImport::convert(png, {}, opt, &result, &error));

    PngPaletteImportDialog dialog(png, pal, pal, QStringLiteral("tileatlas"), false);
    auto *reuse = dialog.findChild<QCheckBox*>(QStringLiteral("pngReuseMatchingColours"));
    assert(reuse && !reuse->isChecked() && reuse->isEnabled());
    reuse->setChecked(true);
    assert(dialog.options().reuseMatchingColours);
    return 0;
}

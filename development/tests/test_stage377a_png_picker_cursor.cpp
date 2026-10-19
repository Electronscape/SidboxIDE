// Stage 3.77a: run from the source root with Qt6 development files installed:
// g++ -std=c++17 -fPIC -I. development/tests/test_stage377a_png_picker_cursor.cpp \
//     pngpaletteimport.cpp $(pkg-config --cflags --libs Qt6Widgets) \
//     -o /tmp/gg_png_cursor_test
// QT_QPA_PLATFORM=offscreen /tmp/gg_png_cursor_test
#include "pngpaletteimport.h"
#include <QApplication>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QWidget>
#include <cassert>

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QImage png(16, 16, QImage::Format_ARGB32);
    png.fill(qRgb(10, 80, 200));
    QVector<QRgb> palette(256, qRgb(0, 0, 0));
    PngPaletteImportDialog dialog(png, palette, palette, QStringLiteral("tileatlas"), false);

    auto *original = dialog.findChild<QGraphicsView *>(QStringLiteral("pngOriginalPreview"));
    assert(original && original->viewport());
    auto views = dialog.findChildren<QGraphicsView *>();
    assert(views.size() == 2);
    auto *converted = views[0] == original ? views[1] : views[0];
    const auto convertedCursor = converted->viewport()->cursor().shape();

    assert(original->viewport()->cursor().shape() == Qt::OpenHandCursor);
    QKeyEvent ctrlDown(QEvent::KeyPress, Qt::Key_Control, Qt::ControlModifier);
    QApplication::sendEvent(&dialog, &ctrlDown);
    assert(original->viewport()->cursor().shape() == Qt::CrossCursor);

    QKeyEvent shiftDown(QEvent::KeyPress, Qt::Key_Shift, Qt::ControlModifier | Qt::ShiftModifier);
    QApplication::sendEvent(&dialog, &shiftDown);
    assert(original->viewport()->cursor().shape() == Qt::CrossCursor);

    QKeyEvent shiftUp(QEvent::KeyRelease, Qt::Key_Shift, Qt::ControlModifier);
    QApplication::sendEvent(&dialog, &shiftUp);
    assert(original->viewport()->cursor().shape() == Qt::CrossCursor);

    QKeyEvent ctrlUp(QEvent::KeyRelease, Qt::Key_Control, Qt::NoModifier);
    QApplication::sendEvent(&dialog, &ctrlUp);
    assert(original->viewport()->cursor().shape() == Qt::OpenHandCursor);
    assert(converted->viewport()->cursor().shape() == convertedCursor);
    return 0;
}

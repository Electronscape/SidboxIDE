#include "pngpaletteimport.h"

#include <QApplication>
#include <QCheckBox>
#include <QColor>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGridLayout>
#include <QFont>
#include <QSplitter>
#include <QSizePolicy>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QListView>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHash>
#include <QIcon>
#include <QKeyEvent>
#include <QVariant>
#include <QFrame>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QResizeEvent>
#include <QScrollBar>
#include <QTimer>
#include <QWheelEvent>
#include <QVector>
#include <QtGlobal>
#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <limits>

namespace SidboxPngImport {
namespace {
struct Bin {
    quint32 count = 0;
    quint64 red = 0, green = 0, blue = 0;
};
struct Box { QVector<int> bins; quint64 total = 0; int lo[3] = {31, 31, 31}; int hi[3] = {0, 0, 0}; };
int component(int id, int channel) {
    return channel == 0 ? ((id >> 10) & 31) : channel == 1 ? ((id >> 5) & 31) : (id & 31);
}
int binOf(QRgb c) {
    return ((qRed(c) >> 3) << 10) | ((qGreen(c) >> 3) << 5) | (qBlue(c) >> 3);
}
void measure(Box &b, const QVector<Bin> &hist) {
    b.total = 0;
    for (int c = 0; c < 3; ++c) { b.lo[c] = 31; b.hi[c] = 0; }
    for (int id : b.bins) {
        b.total += hist[id].count;
        for (int c = 0; c < 3; ++c) {
            b.lo[c] = std::min(b.lo[c], component(id, c));
            b.hi[c] = std::max(b.hi[c], component(id, c));
        }
    }
}
int clampByte(int v) { return std::max(0, std::min(255, v)); }
bool isTransparentPixel(QRgb pixel, const Options &opt) {
    if (qAlpha(pixel) < 128) return true;
    if (!opt.keyColourEnabled) return false;
    return qRed(pixel) == qRed(opt.keyColour)
        && qGreen(pixel) == qGreen(opt.keyColour)
        && qBlue(pixel) == qBlue(opt.keyColour);
}
int colourDistance(QRgb a, int r, int g, int b) {
    const int dr = r - qRed(a), dg = g - qGreen(a), db = b - qBlue(a);
    return 3 * dr * dr + 6 * dg * dg + 2 * db * db;
}
QVector<QRgb> palette256(const QVector<QRgb> &base) {
    QVector<QRgb> palette(256, qRgba(0, 0, 0, 255));
    for (int i = 0; i < std::min(256, int(base.size())); ++i) palette[i] = base[i];
    palette[0] = qRgba(0, 0, 0, 0);
    return palette;
}
}

bool convert(const QImage &source, const QVector<QRgb> &current,
             const Options &opt, Result *result, QString *error)
{
    if (!result || source.isNull() || opt.first < 1 || opt.last > 255 || opt.first > opt.last
        || source.width() < 1 || source.height() < 1 || source.width() > 65535
        || source.height() > 65535 || qint64(source.width()) * source.height() > 16LL*1024*1024) {
        if (error) *error = QStringLiteral("Invalid PNG, palette range or image size (16M pixels maximum).");
        return false;
    }
    if (opt.reuseMatchingColours && (!opt.buildColours || opt.startFresh || current.size() != 256)) {
        if (error) *error = QStringLiteral("Reuse matching colours requires Generate mode and an existing 256-entry palette (not Start Fresh).");
        return false;
    }
    if (!opt.buildColours && (opt.startFresh || current.size() != 256)) {
        if (error) *error = QStringLiteral("Mapping to existing colours requires a selected 256-entry project palette.");
        return false;
    }
    const QImage img = source.convertToFormat(QImage::Format_ARGB32);
    const int paletteSlotCount = opt.last - opt.first + 1;
    // Reserve exact source colours before automatic quantisation. Small accents
    // (such as blue eyes) must not be averaged away by weighted median cut.
    QVector<QRgb> protectedColours;
    QHash<QRgb, bool> protectedSet;
    for (QRgb raw : opt.protectedColours) {
        const QRgb rgb = qRgb(qRed(raw), qGreen(raw), qBlue(raw));
        if (protectedSet.contains(rgb)) continue;
        if (opt.keyColourEnabled && isTransparentPixel(rgb, opt)) {
            if (error) *error = QStringLiteral("A colour cannot be protected and transparent simultaneously.");
            return false;
        }
        protectedSet.insert(rgb, true);
        protectedColours.append(rgb);
    }
    if (!opt.buildColours && !protectedColours.isEmpty()) {
        if (error) *error = QStringLiteral("Protected colours require Generate mode.");
        return false;
    }
    QVector<QRgb> palette = palette256(opt.startFresh ? QVector<QRgb>() : current);
    int builtColours = 0;
    int reusedColours = 0;
    QHash<QRgb, int> exactMapping;
    QHash<QRgb, int> protectedMapping;
    QVector<int> candidateIndices; // Only colours belonging to this imported image.
    QVector<int> writableSlots;
    QVector<QRgb> newProtectedColours;

    if (opt.buildColours && opt.reuseMatchingColours) {
        // A matching colour can live anywhere in the existing CLUT, not just
        // inside the selected writable range. Prefer an index OUTSIDE that
        // range, because importing must never need to rewrite it.
        QHash<QRgb, int> existing;
        auto considerIndex = [&](int i) {
            if (i == 0 || qAlpha(palette[i]) < 128) return;
            const QRgb rgb = qRgb(qRed(palette[i]), qGreen(palette[i]), qBlue(palette[i]));
            if (!existing.contains(rgb)) existing.insert(rgb, i);
        };
        for (int i = 1; i < 256; ++i)
            if (i < opt.first || i > opt.last) considerIndex(i);
        for (int i = opt.first; i <= opt.last; ++i) considerIndex(i);

        QHash<int, bool> lockedSlots;
        for (int y = 0; y < img.height(); ++y) {
            const QRgb *row = reinterpret_cast<const QRgb *>(img.constScanLine(y));
            for (int x = 0; x < img.width(); ++x) {
                if (isTransparentPixel(row[x], opt)) continue;
                const QRgb rgb = qRgb(qRed(row[x]), qGreen(row[x]), qBlue(row[x]));
                if (exactMapping.contains(rgb)) continue;
                const auto matched = existing.constFind(rgb);
                if (matched == existing.constEnd()) continue;
                const int index = matched.value();
                exactMapping.insert(rgb, index);
                candidateIndices.append(index);
                ++reusedColours;
                if (index >= opt.first && index <= opt.last) lockedSlots.insert(index, true);
            }
        }
        // Respect existing protected RGBs too, without consuming a second slot.
        for (QRgb rgb : protectedColours) {
            const auto reused = exactMapping.constFind(rgb);
            if (reused != exactMapping.constEnd()) protectedMapping.insert(rgb, reused.value());
            else newProtectedColours.append(rgb);
        }
        for (int i = opt.first; i <= opt.last; ++i)
            if (!lockedSlots.contains(i)) writableSlots.append(i);
    } else {
        for (int i = opt.first; i <= opt.last; ++i) writableSlots.append(i);
        newProtectedColours = protectedColours;
    }
    if (newProtectedColours.size() > writableSlots.size()) {
        if (error) *error = QStringLiteral("Protected colours require more unreserved indices in the selected palette range.");
        return false;
    }
    const int automaticCapacity = writableSlots.size() - newProtectedColours.size();
    if (opt.buildColours) {
        // Protected new colours occupy the first available writable slots.
        for (QRgb rgb : newProtectedColours) {
            const int index = writableSlots[builtColours++];
            palette[index] = rgb;
            exactMapping.insert(rgb, index);
            protectedMapping.insert(rgb, index);
            candidateIndices.append(index);
        }
        // Lossless when new PNG colours fit; otherwise median-cut only the
        // as-yet-unmatched colours. Exact existing CLUT colours stay untouched.
        QHash<QRgb, int> exact;
        QVector<QRgb> order;
        bool tooMany = false;
        for (int y = 0; y < img.height() && !tooMany; ++y) {
            const QRgb *row = reinterpret_cast<const QRgb *>(img.constScanLine(y));
            for (int x = 0; x < img.width(); ++x) {
                if (isTransparentPixel(row[x], opt)) continue;
                const QRgb rgb = qRgb(qRed(row[x]), qGreen(row[x]), qBlue(row[x]));
                if (exactMapping.contains(rgb) || protectedSet.contains(rgb) || exact.contains(rgb)) continue;
                if (order.size() == automaticCapacity) { tooMany = true; break; }
                exact.insert(rgb, order.size());
                order.append(rgb);
            }
        }
        if (!tooMany) {
            const int offset = builtColours;
            for (int i = 0; i < order.size(); ++i) {
                const int index = writableSlots[offset + i];
                palette[index] = order[i];
                exactMapping.insert(order[i], index);
                candidateIndices.append(index);
            }
            builtColours += order.size();
        } else {
            QVector<Bin> histogram(32768);
            for (int y = 0; y < img.height(); ++y) {
                const QRgb *row = reinterpret_cast<const QRgb *>(img.constScanLine(y));
                for (int x = 0; x < img.width(); ++x) {
                    if (isTransparentPixel(row[x], opt)) continue;
                    const QRgb rgb = qRgb(qRed(row[x]), qGreen(row[x]), qBlue(row[x]));
                    if (exactMapping.contains(rgb) || protectedSet.contains(rgb)) continue;
                    Bin &b = histogram[binOf(row[x])];
                    ++b.count;
                    b.red += qRed(row[x]); b.green += qGreen(row[x]); b.blue += qBlue(row[x]);
                }
            }
            Box initial;
            for (int i = 0; i < 32768; ++i) if (histogram[i].count) initial.bins.append(i);
            if (initial.bins.isEmpty() || automaticCapacity == 0) { /* nearest match uses existing/reused palette */ }
            else {
                measure(initial, histogram);
                QVector<Box> boxes{initial};
                while (boxes.size() < automaticCapacity) {
                    int best = -1, axis = 0;
                    quint64 score = 0;
                    for (int i = 0; i < boxes.size(); ++i) {
                        const Box &box = boxes[i];
                        if (box.bins.size() < 2) continue;
                        for (int c = 0; c < 3; ++c) {
                            const quint64 s = quint64(box.hi[c] - box.lo[c]) * box.total;
                            if (s > score) { best = i; axis = c; score = s; }
                        }
                    }
                    if (best < 0) break;
                    Box &target = boxes[best];
                    std::sort(target.bins.begin(), target.bins.end(), [axis](int a, int b) {
                        return component(a, axis) < component(b, axis);
                    });
                    quint64 accumulated = 0;
                    int split = 1;
                    for (int j = 0; j < target.bins.size() - 1; ++j) {
                        accumulated += histogram[target.bins[j]].count;
                        if (accumulated >= target.total / 2) { split = j + 1; break; }
                    }
                    Box second;
                    second.bins = target.bins.mid(split);
                    target.bins.resize(split);
                    measure(target, histogram);
                    measure(second, histogram);
                    boxes.append(second);
                }
                const int offset = builtColours;
                for (int i = 0; i < boxes.size(); ++i) {
                    quint64 count = 0, r = 0, g = 0, b = 0;
                    for (int id : boxes[i].bins) {
                        const Bin &bin = histogram[id];
                        count += bin.count;
                        r += bin.red; g += bin.green; b += bin.blue;
                    }
                    const int index = writableSlots[offset + i];
                    if (count) palette[index] = qRgb(int(r / count), int(g / count), int(b / count));
                    candidateIndices.append(index);
                }
                builtColours += boxes.size();
            }
        }
    } else {
        builtColours = paletteSlotCount;
        candidateIndices = writableSlots;
    }
    // In reuse mode, the candidates include existing indices anywhere in the
    // CLUT and newly generated entries, which need not be contiguous.
    // Never add index 0, and never treat unused CLUT entries as pixel colours.
    QImage output(img.size(), QImage::Format_Indexed8);
    if (output.isNull()) { if (error) *error = QStringLiteral("Not enough memory for indexed image."); return false; }
    output.setColorTable(palette);
    if (!candidateIndices.isEmpty()) {
        // Cache nearest entries per 15-bit bin for large images. Exact RGB
        // colours are preserved by the palette when the source fits the range.
        std::array<short, 32768> nearest;
        nearest.fill(-1);
        auto choose = [&](int red, int green, int blue) -> int {
            red = clampByte(red); green = clampByte(green); blue = clampByte(blue);
            const int key = ((red >> 3) << 10) | ((green >> 3) << 5) | (blue >> 3);
            if (nearest[key] >= 0) return nearest[key];
            int choice = candidateIndices.first(), best = std::numeric_limits<int>::max();
            for (int i : candidateIndices) {
                const int dist = colourDistance(palette[i], red, green, blue);
                if (dist < best) { best = dist; choice = i; }
            }
            nearest[key] = short(choice);
            return choice;
        };
        struct Err { float r = 0, g = 0, b = 0; };
        QVector<Err> currentError(img.width() + 2), nextError(img.width() + 2);
        constexpr int bayer[4][4] = {{0,8,2,10},{12,4,14,6},{3,11,1,9},{15,7,13,5}};
        for (int y = 0; y < img.height(); ++y) {
            const QRgb *input = reinterpret_cast<const QRgb *>(img.constScanLine(y));
            uchar *target = output.scanLine(y);
            for (int x = 0; x < img.width(); ++x) {
                if (isTransparentPixel(input[x], opt)) { target[x] = 0; continue; }
                // Existing exact CLUT matches and protected colours survive dithering unchanged.
                const QRgb original = qRgb(qRed(input[x]), qGreen(input[x]), qBlue(input[x]));
                const auto protectedPixel = protectedMapping.constFind(original);
                if (protectedPixel != protectedMapping.constEnd()) {
                    target[x] = uchar(protectedPixel.value());
                    continue;
                }
                if (opt.reuseMatchingColours) {
                    const auto reusedPixel = exactMapping.constFind(original);
                    if (reusedPixel != exactMapping.constEnd()) {
                        target[x] = uchar(reusedPixel.value());
                        continue;
                    }
                }
                int r = qRed(input[x]), g = qGreen(input[x]), b = qBlue(input[x]);
                if (opt.dither == Dither::Ordered) {
                    const int delta = (bayer[y & 3][x & 3] * 2 - 15) * 2;
                    r = clampByte(r + delta); g = clampByte(g + delta); b = clampByte(b + delta);
                } else if (opt.dither == Dither::Noise) {
                    // Reproducible per-pixel noise, no RNG/global seed state.
                    quint32 n = (quint32(x) * 0x9e3779b9U) ^ (quint32(y) * 0x85ebca6bU) ^ 0x7f4a7c15U;
                    n ^= n >> 16; n *= 0x7feb352dU; n ^= n >> 15;
                    const int delta = int(n % 49) - 24;
                    r = clampByte(r + delta); g = clampByte(g + delta); b = clampByte(b + delta);
                } else if (opt.dither == Dither::FloydSteinberg) {
                    r = clampByte(qRound(r + currentError[x + 1].r));
                    g = clampByte(qRound(g + currentError[x + 1].g));
                    b = clampByte(qRound(b + currentError[x + 1].b));
                }
                const int at = (opt.dither == Dither::None && exactMapping.contains(qRgb(r,g,b)))
                    ? exactMapping.value(qRgb(r,g,b)) : choose(r, g, b);
                target[x] = uchar(at);
                if (opt.dither == Dither::FloydSteinberg) {
                    const QRgb colour = palette[at];
                    const float er = float(r - qRed(colour)), eg = float(g - qGreen(colour)), eb = float(b - qBlue(colour));
                    auto add = [&](Err &err, float fraction) {
                        err.r += er * fraction; err.g += eg * fraction; err.b += eb * fraction;
                    };
                    if (x + 1 < img.width()) add(currentError[x + 2], 7.0f/16.0f);
                    if (y + 1 < img.height()) {
                        if (x > 0) add(nextError[x], 3.0f/16.0f);
                        add(nextError[x + 1], 5.0f/16.0f);
                        if (x + 1 < img.width()) add(nextError[x + 2], 1.0f/16.0f);
                    }
                }
            }
            if (opt.dither == Dither::FloydSteinberg) {
                currentError.swap(nextError);
                std::fill(nextError.begin(), nextError.end(), Err{});
            }
        }
    } else {
        output.fill(0); // all pixels were transparent
    }
    result->picture.indexed = output;
    result->palette = palette;
    result->paletteColours = builtColours;
    result->reusedColours = reusedColours;
    return true;
}
} // namespace SidboxPngImport

// Full-resolution inspector. QGraphicsView handles huge pictures without
// generating a second enlarged image when zooming. Pixels stay crisp.
// These are host UI controls only; PPB conversion and palette handling remain
// in SidboxPngImport::convert(), unchanged.
class PngPreviewView : public QGraphicsView {
public:
    explicit PngPreviewView(QWidget *parent = nullptr)
        : QGraphicsView(parent), m_scene(new QGraphicsScene(this)) {
        setScene(m_scene);
        m_image = m_scene->addPixmap(QPixmap());
        m_image->setTransformationMode(Qt::FastTransformation);
        setAlignment(Qt::AlignCenter);
        setRenderHint(QPainter::SmoothPixmapTransform, false);
        setDragMode(QGraphicsView::ScrollHandDrag);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setFrameShape(QFrame::Box);
        setStyleSheet(QStringLiteral("QGraphicsView { border: 1px solid palette(mid); border-radius: 0px; }"));
        setMinimumSize(240, 190);
        setBackgroundBrush(QColor(66, 66, 66));
    }

    void setImage(const QImage &image) {
        m_image->setPixmap(image.isNull() ? QPixmap() : QPixmap::fromImage(image));
        m_scene->setSceneRect(QRectF(QPointF(0, 0), QSizeF(image.size())));
        if (m_fitting) refit();
    }
    void setFit(bool fit) {
        m_fitting = fit;
        if (fit) refit();
    }
    void setZoom(double factor) {
        m_fitting = false;
        const QPointF center = mapToScene(viewport()->rect().center());
        resetTransform();
        scale(factor, factor);
        centerOn(center);
    }
    double currentZoom() const { return transform().m11(); }
    std::function<void(double)> zoomRequested;
    std::function<void()> fittedScaleChanged;
    std::function<void(QPoint, bool)> sourcePixelSelected;

    // The original PNG is a pixel picker. Show a crosshair whenever Ctrl is
    // held (Ctrl+click = transparency; Ctrl+Shift+click = protected colour).
    // The output preview remains the normal hand/pan view.
    void enableSourcePickCursor() {
        m_sourcePickCursor = true;
        setMouseTracking(true);
        viewport()->setMouseTracking(true);
        qApp->installEventFilter(this); // keyboard focus may be on another control
        updateSourcePickCursor(QApplication::keyboardModifiers());
    }

protected:
    bool eventFilter(QObject *watched, QEvent *event) override {
        if (m_sourcePickCursor) {
            if (event->type() == QEvent::KeyPress || event->type() == QEvent::KeyRelease)
                updateSourcePickCursor(static_cast<QKeyEvent *>(event)->modifiers());
            else if (event->type() == QEvent::ApplicationDeactivate
                     || event->type() == QEvent::WindowDeactivate)
                updateSourcePickCursor(Qt::NoModifier);
            else if (watched == viewport() && event->type() == QEvent::Enter)
                updateSourcePickCursor(QApplication::keyboardModifiers());
        }
        return QGraphicsView::eventFilter(watched, event);
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        QGraphicsView::mouseMoveEvent(event);
        if (m_sourcePickCursor) updateSourcePickCursor(event->modifiers());
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        QGraphicsView::mouseReleaseEvent(event);
        if (m_sourcePickCursor) updateSourcePickCursor(event->modifiers());
    }
    void mousePressEvent(QMouseEvent *event) override {
        // Ctrl+click picks a precise source PNG RGB value; ordinary drag-to-pan remains intact.
        if (sourcePixelSelected && event->button() == Qt::LeftButton
            && (event->modifiers() & Qt::ControlModifier)) {
            const QPoint at = mapToScene(event->position().toPoint()).toPoint();
            if (sceneRect().contains(QPointF(at))) {
                sourcePixelSelected(at, bool(event->modifiers() & Qt::ShiftModifier));
                event->accept();
                return;
            }
        }
        QGraphicsView::mousePressEvent(event);
    }
    void resizeEvent(QResizeEvent *event) override {
        QGraphicsView::resizeEvent(event);
        if (m_fitting) refit();
    }
    void wheelEvent(QWheelEvent *event) override {
        const int delta = event->angleDelta().y();
        if (delta && zoomRequested) {
            zoomRequested(std::pow(1.25, double(delta) / 120.0));
            event->accept();
        } else {
            QGraphicsView::wheelEvent(event);
        }
    }
    void drawBackground(QPainter *painter, const QRectF &rect) override {
        painter->fillRect(rect, QColor(66, 66, 66));
        const QRectF inside = rect.intersected(sceneRect());
        if (inside.isEmpty()) return;
        // Eight *source-image* pixels per square, so the checkerboard zooms
        // alongside the transparent pixels rather than disguising edges.
        static const QPixmap checker = []() {
            QPixmap tile(16, 16);
            tile.fill(QColor(221, 221, 221));
            QPainter p(&tile);
            p.fillRect(QRect(0, 0, 8, 8), QColor(175, 175, 175));
            p.fillRect(QRect(8, 8, 8, 8), QColor(175, 175, 175));
            return tile;
        }();
        painter->fillRect(inside, QBrush(checker));
    }
private:
    void updateSourcePickCursor(Qt::KeyboardModifiers modifiers) {
        if (!m_sourcePickCursor) return;
        // QGraphicsView uses an open/closed hand for panning. Preserve that
        // feedback until Ctrl activates precise pixel picking.
        const Qt::CursorShape shape = (modifiers & Qt::ControlModifier)
            ? Qt::CrossCursor
            : (QApplication::mouseButtons() & Qt::LeftButton)
                ? Qt::ClosedHandCursor : Qt::OpenHandCursor;
        if (viewport()->cursor().shape() != shape)
            viewport()->setCursor(shape);
    }
    void refit() {
        resetTransform();
        if (!m_image->pixmap().isNull())
            fitInView(m_image, Qt::KeepAspectRatio);
        if (fittedScaleChanged) fittedScaleChanged();
    }
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_image;
    bool m_fitting = true;
    bool m_sourcePickCursor = false;
};

PngPaletteImportDialog::PngPaletteImportDialog(const QImage &source,
                                               const QVector<QRgb> &foreground,
                                               const QVector<QRgb> &background,
                                               const QString &initialKind, bool dualPlane, QWidget *parent)
    : QDialog(parent), m_source(source), m_dualPlane(dualPlane), m_front(foreground), m_back(background)
{
    setWindowTitle(tr("Import PNG → SIDBOX Indexed PPB"));
    setMinimumWidth(800);
    resize(1180, 820);
    setStyleSheet(QStringLiteral("QDialog { border-radius: 0px; } QGroupBox, QPushButton, QComboBox, QSpinBox, QLabel { border-radius: 0px; }"));
    auto *layout = new QVBoxLayout(this);
    // Compact three-column settings: give the image previews the height instead
    // of stacking seven form rows in the upper-left corner of a wide dialog.
    auto *settings = new QGridLayout();
    settings->setContentsMargins(0, 0, 0, 0);
    settings->setHorizontalSpacing(16);
    settings->setVerticalSpacing(5);
    settings->setColumnStretch(0, 1);
    settings->setColumnStretch(1, 1);
    settings->setColumnStretch(2, 2);

    m_destination = new QComboBox(this);
    m_destination->addItem(tr("Tile Atlases (resource only)"), QStringLiteral("tileatlas"));
    m_destination->addItem(tr("Sprites (on game canvas)"), QStringLiteral("sprite"));
    m_destination->addItem(tr("Backgrounds"), QStringLiteral("background"));
    const int initial = m_destination->findData(initialKind);
    if (initial >= 0) m_destination->setCurrentIndex(initial);
    settings->addWidget(new QLabel(tr("Import into:"), this), 0, 0);
    settings->addWidget(m_destination, 1, 0);

    m_bank = new QComboBox(this);
    m_bank->addItem(tr("Foreground CLUT"), QStringLiteral("foreground"));
    m_bank->addItem(tr("Background CLUT"), QStringLiteral("background"));
    settings->addWidget(new QLabel(tr("Palette bank:"), this), 0, 1);
    settings->addWidget(m_bank, 1, 1);

    m_mode = new QComboBox(this);
    m_mode->addItem(tr("Generate colours in selected range"), true);
    m_mode->addItem(tr("Match existing palette colours (do not modify)"), false);
    settings->addWidget(new QLabel(tr("Palette mode:"), this), 0, 2);
    settings->addWidget(m_mode, 1, 2);

    auto *range = new QWidget(this);
    auto *rangeLayout = new QHBoxLayout(range);
    rangeLayout->setContentsMargins(0, 0, 0, 0);
    m_first = new QSpinBox(this); m_first->setRange(1, 255); m_first->setValue(1);
    m_last = new QSpinBox(this); m_last->setRange(1, 255); m_last->setValue(255);
    rangeLayout->addWidget(m_first);
    rangeLayout->addWidget(new QLabel(tr("to"), this));
    rangeLayout->addWidget(m_last);
    rangeLayout->addStretch(1);
    settings->addWidget(new QLabel(tr("Palette indices (0 is transparent):"), this), 2, 0);
    settings->addWidget(range, 3, 0);

    m_dither = new QComboBox(this);
    m_dither->addItem(tr("None (pixel art / exact colours)"), int(SidboxPngImport::Dither::None));
    m_dither->addItem(tr("Floyd–Steinberg error diffusion"), int(SidboxPngImport::Dither::FloydSteinberg));
    m_dither->addItem(tr("Ordered 4×4 dither"), int(SidboxPngImport::Dither::Ordered));
    m_dither->addItem(tr("Noise dither (reproducible)"), int(SidboxPngImport::Dither::Noise));
    settings->addWidget(new QLabel(tr("Dithering:"), this), 2, 1);
    settings->addWidget(m_dither, 3, 1);

    auto *transparentRow = new QWidget(this);
    auto *transparentLayout = new QHBoxLayout(transparentRow);
    transparentLayout->setContentsMargins(0, 0, 0, 0);
    m_transparentKey = new QCheckBox(tr("Map one PNG colour to index 0"), this);
    m_transparentColourPreview = new QLabel(this);
    m_transparentColourPreview->setMinimumWidth(100);
    transparentLayout->addWidget(m_transparentKey);
    transparentLayout->addStretch(1);
    transparentLayout->addWidget(m_transparentColourPreview);
    settings->addWidget(new QLabel(tr("Transparency key (choose from PNG colours):"), this), 2, 2);
    settings->addWidget(transparentRow, 3, 2);

    m_fresh = new QCheckBox(tr("Start with a blank palette (otherwise preserve existing colours)"), this);
    settings->addWidget(m_fresh, 4, 0, 1, 3);
    m_reuse = new QCheckBox(tr("Reuse matching colours (only add new unique colours)"), this);
    m_reuse->setObjectName(QStringLiteral("pngReuseMatchingColours"));
    m_reuse->setToolTip(tr("Reuse exact opaque RGB matches from the existing palette, even outside the selected range. "
        "Only new colours use writable indices in the selected range. Index 0 is never reused."));
    settings->addWidget(m_reuse, 5, 0, 1, 3);
    layout->addLayout(settings);
    // Both inspectors display actual source pixels, at any zoom. Drag one
    // picture to pan; the other follows for an exact before/after comparison.
    auto *viewTools = new QHBoxLayout();
    auto *fitButton = new QPushButton(tr("Fit to Window"), this);
    auto *oneToOne = new QPushButton(tr("1:1 (100%)"), this);
    auto *zoomOut = new QPushButton(tr("−"), this);
    auto *zoomIn = new QPushButton(tr("+"), this);
    zoomOut->setToolTip(tr("Zoom out (also available with the mouse wheel)"));
    zoomIn->setToolTip(tr("Zoom in (also available with the mouse wheel)"));
    m_zoomReadout = new QLabel(this);
    m_zoomReadout->setMinimumWidth(88);
    viewTools->addWidget(fitButton);
    viewTools->addWidget(oneToOne);
    viewTools->addWidget(zoomOut);
    viewTools->addWidget(zoomIn);
    viewTools->addWidget(m_zoomReadout);
    viewTools->addStretch(1);
    viewTools->addWidget(new QLabel(tr("Drag: pan  •  Wheel: zoom  •  Ctrl+click: key  •  Ctrl+Shift+click: protect"), this));
    layout->addLayout(viewTools);

    // Resizable workspace: two large previews plus a source-colour inspector.
    // A splitter lets the user choose how much room the palette receives.
    auto *workspace = new QSplitter(Qt::Horizontal, this);
    workspace->setChildrenCollapsible(false);
    auto *previewArea = new QWidget(workspace);
    auto *previews = new QHBoxLayout(previewArea);
    previews->setContentsMargins(0, 0, 0, 0);
    auto *origColumn = new QVBoxLayout();
    auto *newColumn = new QVBoxLayout();
    origColumn->addWidget(new QLabel(tr("Original PNG (%1 × %2)").arg(source.width()).arg(source.height()), this));
    newColumn->addWidget(new QLabel(tr("Indexed PPB — actual pixels"), this));
    m_before = new PngPreviewView(this);
    m_after = new PngPreviewView(this);
    m_before->fittedScaleChanged = [this]() { updateZoomLabel(); };
    origColumn->addWidget(m_before, 1);
    newColumn->addWidget(m_after, 1);
    previews->addLayout(origColumn, 1);
    previews->addLayout(newColumn, 1);
    workspace->addWidget(previewArea);

    auto *paletteArea = new QFrame(workspace);
    paletteArea->setFrameShape(QFrame::StyledPanel);
    paletteArea->setMinimumWidth(245);
    auto *paletteLayout = new QVBoxLayout(paletteArea);
    paletteLayout->setContentsMargins(7, 7, 7, 7);
    paletteLayout->setSpacing(6);
    auto *sourceTitle = new QLabel(tr("Source PNG colours"), paletteArea);
    QFont titleFont = sourceTitle->font();
    titleFont.setBold(true);
    sourceTitle->setFont(titleFont);
    paletteLayout->addWidget(sourceTitle);
    auto *sourceHelp = new QLabel(tr("Click: transparent (index 0). Shift+click: protect that exact colour from reduction; Shift+click again to release. Ctrl+Shift+click the original PNG works too."), paletteArea);
    sourceHelp->setWordWrap(true);
    paletteLayout->addWidget(sourceHelp);
    m_sourceColours = new QListWidget(paletteArea);
    m_sourceColours->setViewMode(QListView::IconMode);
    m_sourceColours->setFlow(QListView::LeftToRight);
    m_sourceColours->setWrapping(true);
    m_sourceColours->setMovement(QListView::Static);
    m_sourceColours->setResizeMode(QListView::Adjust);
    m_sourceColours->setIconSize(QSize(26, 26));
    m_sourceColours->setGridSize(QSize(76, 51));
    m_sourceColours->setUniformItemSizes(true);
    m_sourceColours->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_sourceColours->setStyleSheet(QStringLiteral("QListWidget { border-radius: 0px; }"));
    paletteLayout->addWidget(m_sourceColours, 1);
    m_sourceColourNote = new QLabel(paletteArea);
    m_sourceColourNote->setWordWrap(true);
    paletteLayout->addWidget(m_sourceColourNote);
    workspace->addWidget(paletteArea);
    workspace->setStretchFactor(0, 1);
    workspace->setStretchFactor(1, 0);
    workspace->setSizes({800, 325});
    layout->addWidget(workspace, 1);

    connect(fitButton, &QPushButton::clicked, this, [this]() { fitPreviews(); });
    connect(oneToOne, &QPushButton::clicked, this, [this]() { setPreviewZoom(1.0); });
    connect(zoomOut, &QPushButton::clicked, this, [this]() {
        setPreviewZoom(m_before->currentZoom() / 1.25);
    });
    connect(zoomIn, &QPushButton::clicked, this, [this]() {
        setPreviewZoom(m_before->currentZoom() * 1.25);
    });
    for (auto *view : {m_before, m_after}) {
        view->zoomRequested = [this, view](double multiplier) {
            setPreviewZoom(view->currentZoom() * multiplier);
        };
    }
    connect(m_before->horizontalScrollBar(), &QScrollBar::valueChanged,
            m_after->horizontalScrollBar(), &QScrollBar::setValue);
    connect(m_after->horizontalScrollBar(), &QScrollBar::valueChanged,
            m_before->horizontalScrollBar(), &QScrollBar::setValue);
    connect(m_before->verticalScrollBar(), &QScrollBar::valueChanged,
            m_after->verticalScrollBar(), &QScrollBar::setValue);
    connect(m_after->verticalScrollBar(), &QScrollBar::valueChanged,
            m_before->verticalScrollBar(), &QScrollBar::setValue);

    // Compact output summary and the exact 32/256-entry destination CLUT strip.
    m_status = new QLabel(this);
    m_status->setWordWrap(true);
    layout->addWidget(m_status);
    auto *outputRow = new QHBoxLayout();
    outputRow->addWidget(new QLabel(tr("Output CLUT:"), this));
    m_swatch = new QLabel(this);
    m_swatch->setMinimumHeight(26);
    outputRow->addWidget(m_swatch);
    outputRow->addStretch(1);
    layout->addLayout(outputRow);
    auto *note = new QLabel(tr("Exact pixels, no smoothing. The selected transparency colour becomes index 0 and does not use a palette slot. "
        "Changing an occupied CLUT range can recolour existing resources."), this);
    note->setWordWrap(true);
    layout->addWidget(note);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);
    m_accept = buttons->button(QDialogButtonBox::Ok);
    m_accept->setText(tr("Continue to Save..."));
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);
    m_previewTimer = new QTimer(this);
    m_previewTimer->setSingleShot(true);
    m_previewTimer->setInterval(140);
    connect(m_previewTimer, &QTimer::timeout, this, &PngPaletteImportDialog::updatePreview);
    connect(m_destination, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { updateControls(); });
    connect(m_bank, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { queuePreview(); });
    connect(m_mode, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { updateControls(); });
    connect(m_dither, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this]() { queuePreview(); });
    connect(m_first, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]() { queuePreview(); });
    connect(m_last, QOverload<int>::of(&QSpinBox::valueChanged), this, [this]() { queuePreview(); });
    connect(m_fresh, &QCheckBox::toggled, this, [this]() { updateControls(); });
    connect(m_reuse, &QCheckBox::toggled, this, [this]() { queuePreview(); });
    connect(m_transparentKey, &QCheckBox::toggled, this, [this](bool enabled) {
        if (enabled && m_protectedColours.removeAll(m_keyColour) > 0) updateProtectedColourUi();
        updateTransparentColourUi();
        queuePreview();
    });
    connect(m_sourceColours, &QListWidget::itemClicked, this, [this](QListWidgetItem *item) {
        const QRgb colour = item->data(Qt::UserRole).value<QRgb>();
        if (QApplication::keyboardModifiers() & Qt::ShiftModifier) toggleProtectedColour(colour);
        else selectTransparentColour(colour);
    });
    m_before->setObjectName(QStringLiteral("pngOriginalPreview"));
    m_before->sourcePixelSelected = [this](QPoint at, bool protect) {
        if (!m_source.valid(at)) return;
        const QRgb pixel = m_source.pixel(at);
        if (qAlpha(pixel) < 128) return; // already transparent from source alpha
        if (protect) toggleProtectedColour(pixel);
        else selectTransparentColour(pixel);
    };
    m_before->enableSourcePickCursor();
    m_before->setImage(m_source);
    // Display USED colours from the original PNG, not approximations from the
    // output CLUT. Indexed PNGs retain their source palette indices here.
    if (m_source.format() == QImage::Format_Indexed8) {
        const auto table = m_source.colorTable();
        QVector<quint32> counts(table.size(), 0);
        for (int y = 0; y < m_source.height(); ++y) {
            const uchar *row = m_source.constScanLine(y);
            for (int x = 0; x < m_source.width(); ++x)
                if (row[x] < counts.size()) ++counts[row[x]];
        }
        for (int i = 0; i < table.size(); ++i) {
            if (!counts[i] || qAlpha(table[i]) < 128) continue;
            const QRgb colour = qRgb(qRed(table[i]), qGreen(table[i]), qBlue(table[i]));
            QPixmap swatch(26, 26); swatch.fill(QColor::fromRgb(colour));
            auto *item = new QListWidgetItem(QIcon(swatch), QStringLiteral("PNG %1").arg(i), m_sourceColours);
            item->setData(Qt::UserRole, QVariant::fromValue(colour));
            item->setData(Qt::UserRole + 1, item->text());
            item->setToolTip(tr("Source PNG index %1\nRGB %2\n%3 pixels")
                .arg(i).arg(QColor::fromRgb(colour).name(QColor::HexRgb).toUpper()).arg(counts[i]));
        }
        // Index-based swatches are complete: only used opaque PNG entries are listed.
    } else {
        const QImage rgba = m_source.convertToFormat(QImage::Format_ARGB32);
        QHash<QRgb, int> positions;
        struct Found { QRgb colour; quint32 count; };
        QVector<Found> found;
        bool limited = false;
        for (int y = 0; y < rgba.height(); ++y) {
            const QRgb *row = reinterpret_cast<const QRgb *>(rgba.constScanLine(y));
            for (int x = 0; x < rgba.width(); ++x) {
                const QRgb px = row[x];
                if (qAlpha(px) < 128) continue;
                const QRgb colour = qRgb(qRed(px), qGreen(px), qBlue(px));
                const auto it = positions.constFind(colour);
                if (it != positions.constEnd()) { ++found[it.value()].count; continue; }
                if (found.size() >= 512) { limited = true; continue; }
                positions.insert(colour, found.size());
                found.append({colour, 1});
            }
        }
        for (const Found &entry : found) {
            const QColor c = QColor::fromRgb(entry.colour);
            QPixmap swatch(26, 26); swatch.fill(c);
            auto *item = new QListWidgetItem(QIcon(swatch), c.name(QColor::HexRgb).toUpper(), m_sourceColours);
            item->setData(Qt::UserRole, QVariant::fromValue(entry.colour));
            item->setData(Qt::UserRole + 1, item->text());
            item->setToolTip(tr("Source RGB %1\n%2 pixels").arg(c.name(QColor::HexRgb).toUpper()).arg(entry.count));
        }
        m_sourceColoursLimited = limited;
    }
    updateTransparentColourUi();
    updateProtectedColourUi();
    updateControls();
    updatePreview();
    fitPreviews();
}

void PngPaletteImportDialog::fitPreviews() {
    m_fitPreview = true;
    m_before->setFit(true);
    m_after->setFit(true);
    updateZoomLabel();
}

void PngPaletteImportDialog::setPreviewZoom(double factor) {
    m_fitPreview = false;
    m_zoomFactor = std::max(0.125, std::min(32.0, factor));
    m_before->setZoom(m_zoomFactor);
    m_after->setZoom(m_zoomFactor);
    updateZoomLabel();
}

void PngPaletteImportDialog::updateZoomLabel() {
    if (!m_zoomReadout) return;
    const double factor = m_before ? m_before->currentZoom() : 1.0;
    m_zoomReadout->setText(m_fitPreview
        ? tr("Fit (%1%)").arg(qRound(factor * 100))
        : tr("%1%").arg(qRound(factor * 100)));
}

void PngPaletteImportDialog::queuePreview() {
    m_accept->setEnabled(false);
    m_status->setText(tr("Updating full-resolution palette preview..."));
    m_previewTimer->start();
}

SidboxPngImport::Options PngPaletteImportDialog::options() const {
    SidboxPngImport::Options opt;
    opt.first = m_first->value(); opt.last = m_last->value();
    opt.buildColours = m_mode->currentData().toBool();
    opt.startFresh = m_fresh->isChecked();
    opt.reuseMatchingColours = m_reuse->isChecked();
    opt.keyColourEnabled = m_transparentKey && m_transparentKey->isChecked();
    opt.keyColour = m_keyColour;
    if (opt.buildColours) opt.protectedColours = m_protectedColours;
    opt.dither = SidboxPngImport::Dither(m_dither->currentData().toInt());
    return opt;
}
QVector<QRgb> PngPaletteImportDialog::basePalette() const {
    return palettePlane() == QStringLiteral("background") ? m_back : m_front;
}
QString PngPaletteImportDialog::destinationKind() const { return m_destination->currentData().toString(); }
QString PngPaletteImportDialog::palettePlane() const { return m_bank->currentData().toString(); }

void PngPaletteImportDialog::selectTransparentColour(QRgb colour) {
    m_keyColour = qRgb(qRed(colour), qGreen(colour), qBlue(colour));
    // A selected transparent colour must never also reserve an opaque slot.
    m_protectedColours.removeAll(m_keyColour);
    // Also highlight the swatch when the colour was picked from the preview.
    if (m_sourceColours) {
        for (int i = 0; i < m_sourceColours->count(); ++i) {
            auto *item = m_sourceColours->item(i);
            const QRgb source = item->data(Qt::UserRole).value<QRgb>();
            if (qRed(source) == qRed(m_keyColour) && qGreen(source) == qGreen(m_keyColour)
                && qBlue(source) == qBlue(m_keyColour)) {
                m_sourceColours->setCurrentItem(item);
                m_sourceColours->scrollToItem(item);
                break;
            }
        }
    }
    // A source-swatch click enables the option immediately, no second step.
    if (!m_transparentKey->isChecked()) m_transparentKey->setChecked(true);
    updateTransparentColourUi();
    updateProtectedColourUi();
    queuePreview();
}

void PngPaletteImportDialog::toggleProtectedColour(QRgb colour) {
    if (!m_mode->currentData().toBool()) {
        QMessageBox::information(this, tr("Generate palette colours"),
            tr("Switch Palette mode to Generate colours in selected range to protect exact source colours."));
        return;
    }
    const QRgb rgb = qRgb(qRed(colour), qGreen(colour), qBlue(colour));
    if (m_transparentKey->isChecked() && rgb == m_keyColour) {
        QMessageBox::information(this, tr("Colour is transparent"),
            tr("This colour is currently mapped to transparent index 0. Disable transparency or choose another key colour before protecting it."));
        return;
    }
    const int at = m_protectedColours.indexOf(rgb);
    if (at >= 0) m_protectedColours.removeAt(at);
    else {
        const int capacity = std::max(0, m_last->value() - m_first->value() + 1);
        if (m_protectedColours.size() >= capacity) {
            QMessageBox::information(this, tr("Palette range is full"),
                tr("This destination range has only %1 entries. Release an existing protected colour or expand the range.").arg(capacity));
            return;
        }
        m_protectedColours.append(rgb);
    }
    updateProtectedColourUi();
    queuePreview();
}

void PngPaletteImportDialog::updateProtectedColourUi() {
    if (!m_sourceColours) return;
    for (int i = 0; i < m_sourceColours->count(); ++i) {
        auto *item = m_sourceColours->item(i);
        const QRgb rgb = item->data(Qt::UserRole).value<QRgb>();
        const bool held = m_protectedColours.contains(rgb);
        const QString basic = item->data(Qt::UserRole + 1).toString();
        item->setText(held ? QStringLiteral("★ ") + basic : basic);
    }
}

void PngPaletteImportDialog::updateTransparentColourUi() {
    const QColor effective = QColor::fromRgb(m_keyColour);
    if (m_transparentColourPreview) {
        m_transparentColourPreview->setText(effective.name(QColor::HexRgb).toUpper());
        m_transparentColourPreview->setAlignment(Qt::AlignCenter);
        m_transparentColourPreview->setStyleSheet(QStringLiteral("QLabel { border: 1px solid palette(mid); border-radius: 0px; background: %1; color: %2; padding: 2px 6px; }")
            .arg(effective.name(QColor::HexRgb), effective.lightness() < 128 ? QStringLiteral("white") : QStringLiteral("black")));
    }
}

void PngPaletteImportDialog::updateControls() {
    const QString kind = destinationKind();
    const bool fixedBank = !m_dualPlane || kind == QStringLiteral("tileatlas")
                           || kind == QStringLiteral("background");
    if (fixedBank) m_bank->setCurrentIndex(m_dualPlane && kind == QStringLiteral("background") ? 1 : 0);
    m_bank->setEnabled(!fixedBank);
    m_fresh->setEnabled(m_mode->currentData().toBool());
    if (!m_fresh->isEnabled()) m_fresh->setChecked(false);
    m_reuse->setEnabled(m_mode->currentData().toBool() && !m_fresh->isChecked());
    if (!m_reuse->isEnabled()) m_reuse->setChecked(false);
    updateTransparentColourUi();
    updateProtectedColourUi();
    queuePreview();
}
void PngPaletteImportDialog::updatePreview() {
    if (m_previewTimer) m_previewTimer->stop();
    const SidboxPngImport::Options opt = options();
    QString error;
    SidboxPngImport::Result result;
    const bool ok = SidboxPngImport::convert(m_source, basePalette(), opt, &result, &error);
    m_accept->setEnabled(ok);
    m_after->setImage(ok ? result.picture.indexed : QImage());
    updateZoomLabel();
    const QString paletteNote = !opt.buildColours ? tr("Existing CLUT will not be changed.")
        : opt.startFresh ? tr("Starting with a blank CLUT; other entries reset.")
        : tr("All other palette indices are preserved from the selected CLUT.");
    const QString keyNote = opt.keyColourEnabled
        ? tr("The source colour %1 is mapped to transparent index 0 and excluded from the generated palette.")
            .arg(QColor::fromRgb(opt.keyColour).name(QColor::HexRgb).toUpper())
        : tr("Only source alpha controls transparency.");
    const QString protectedNote = opt.buildColours
        ? tr("%1 exact colours protected; up to %2 other palette entries available.")
            .arg(opt.protectedColours.size()).arg(std::max(0, opt.last - opt.first + 1 - int(opt.protectedColours.size())))
        : tr("Colour protection is inactive in Match existing mode.");
    m_status->setText(ok ? (opt.reuseMatchingColours
        ? tr("Palette: %1 existing colours reused, %2 new entries generated in indices %3–%4. %5 %6 %7")
            .arg(result.reusedColours).arg(result.paletteColours).arg(opt.first).arg(opt.last)
            .arg(paletteNote, keyNote, protectedNote)
        : tr("Output indices %1–%2: %3 palette entries generated. %4 %5 %6")
            .arg(opt.first).arg(opt.last).arg(result.paletteColours)
            .arg(paletteNote, keyNote, protectedNote)) : error);
    if (m_sourceColourNote && m_sourceColours) {
        int removed = 0;
        if (opt.keyColourEnabled) {
            for (int i = 0; i < m_sourceColours->count(); ++i) {
                const QRgb c = m_sourceColours->item(i)->data(Qt::UserRole).value<QRgb>();
                if (qRed(c) == qRed(opt.keyColour) && qGreen(c) == qGreen(opt.keyColour)
                    && qBlue(c) == qBlue(opt.keyColour)) ++removed;
            }
        }
        const int shown = m_sourceColours->count();
        const int destinationSlots = opt.last - opt.first + 1;
        m_sourceColourNote->setText(m_sourceColoursLimited
            ? tr("First 512 source colours shown. %1 exact colours protected; %2 destination entries. Ctrl+Shift+click the PNG to protect any hidden colour.")
                .arg(m_protectedColours.size()).arg(destinationSlots)
            : tr("Source entries: %1  •  transparency: %2  •  protected exact: %3  •  other colours: %4  •  output slots: %5")
                .arg(shown).arg(removed).arg(m_protectedColours.size())
                .arg(std::max(0, shown - removed - int(m_protectedColours.size()))).arg(destinationSlots));
    }
    QPixmap strip(512, 22);
    strip.fill(Qt::transparent);
    if (ok) {
        QPainter painter(&strip);
        const int count = opt.last - opt.first + 1;
        for (int i = 0; i < count; ++i) {
            const int x0 = int(qint64(i) * strip.width() / count);
            const int x1 = int(qint64(i+1) * strip.width() / count);
            painter.fillRect(x0, 0, x1-x0, 22, QColor::fromRgba(result.palette[opt.first+i]));
        }
    }
    m_swatch->setPixmap(strip);
}

#include "pngpaletteimport.h"

#include <QCheckBox>
#include <QColor>
#include <QComboBox>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPixmap>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHash>
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
    if (!opt.buildColours && (opt.startFresh || current.size() != 256)) {
        if (error) *error = QStringLiteral("Mapping to existing colours requires a selected 256-entry project palette.");
        return false;
    }
    const QImage img = source.convertToFormat(QImage::Format_ARGB32);
    const int paletteSlotCount = opt.last - opt.first + 1;
    QVector<QRgb> palette = palette256(opt.startFresh ? QVector<QRgb>() : current);
    int builtColours = 0;
    QHash<QRgb, int> exactMapping;
    if (opt.buildColours) {
        // Lossless when the PNG fits in the requested slot count, otherwise
        // weighted median cut on a bounded RGB555 histogram (32K bins).
        QHash<QRgb, int> exact;
        QVector<QRgb> order;
        bool tooMany = false;
        for (int y = 0; y < img.height() && !tooMany; ++y) {
            const QRgb *row = reinterpret_cast<const QRgb *>(img.constScanLine(y));
            for (int x = 0; x < img.width(); ++x) {
                if (qAlpha(row[x]) < 128) continue;
                const QRgb rgb = qRgb(qRed(row[x]), qGreen(row[x]), qBlue(row[x]));
                if (exact.contains(rgb)) continue;
                if (order.size() == paletteSlotCount) { tooMany = true; break; }
                exact.insert(rgb, order.size());
                order.append(rgb);
            }
        }
        if (!tooMany) {
            builtColours = order.size();
            for (int i = 0; i < builtColours; ++i) {
                palette[opt.first + i] = order[i];
                exactMapping.insert(order[i], opt.first + i);
            }
        } else {
            QVector<Bin> histogram(32768);
            for (int y = 0; y < img.height(); ++y) {
                const QRgb *row = reinterpret_cast<const QRgb *>(img.constScanLine(y));
                for (int x = 0; x < img.width(); ++x) {
                    if (qAlpha(row[x]) < 128) continue;
                    Bin &b = histogram[binOf(row[x])];
                    ++b.count;
                    b.red += qRed(row[x]); b.green += qGreen(row[x]); b.blue += qBlue(row[x]);
                }
            }
            Box initial;
            for (int i = 0; i < 32768; ++i) if (histogram[i].count) initial.bins.append(i);
            if (initial.bins.isEmpty()) { /* all transparent */ }
            else {
                measure(initial, histogram);
                QVector<Box> boxes{initial};
                while (boxes.size() < paletteSlotCount) {
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
                builtColours = boxes.size();
                for (int i = 0; i < boxes.size(); ++i) {
                    quint64 count = 0, r = 0, g = 0, b = 0;
                    for (int id : boxes[i].bins) {
                        const Bin &bin = histogram[id];
                        count += bin.count;
                        r += bin.red; g += bin.green; b += bin.blue;
                    }
                    if (count) palette[opt.first + i] = qRgb(int(r / count), int(g / count), int(b / count));
                }
            }
        }
    } else {
        builtColours = paletteSlotCount;
    }
    QImage output(img.size(), QImage::Format_Indexed8);
    if (output.isNull()) { if (error) *error = QStringLiteral("Not enough memory for indexed image."); return false; }
    output.setColorTable(palette);
    if (builtColours > 0) {
        // Cache nearest entries per 15-bit bin for large images. Exact RGB
        // colours are preserved by the palette when the source fits the range.
        std::array<short, 32768> nearest;
        nearest.fill(-1);
        auto choose = [&](int red, int green, int blue) -> int {
            red = clampByte(red); green = clampByte(green); blue = clampByte(blue);
            const int key = ((red >> 3) << 10) | ((green >> 3) << 5) | (blue >> 3);
            if (nearest[key] >= 0) return nearest[key];
            int choice = opt.first, best = std::numeric_limits<int>::max();
            for (int i = opt.first; i < opt.first + builtColours; ++i) {
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
                if (qAlpha(input[x]) < 128) { target[x] = 0; continue; }
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

protected:
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
    void refit() {
        resetTransform();
        if (!m_image->pixmap().isNull())
            fitInView(m_image, Qt::KeepAspectRatio);
        if (fittedScaleChanged) fittedScaleChanged();
    }
    QGraphicsScene *m_scene;
    QGraphicsPixmapItem *m_image;
    bool m_fitting = true;
};

PngPaletteImportDialog::PngPaletteImportDialog(const QImage &source,
                                               const QVector<QRgb> &foreground,
                                               const QVector<QRgb> &background,
                                               const QString &initialKind, bool dualPlane, QWidget *parent)
    : QDialog(parent), m_source(source), m_dualPlane(dualPlane), m_front(foreground), m_back(background)
{
    setWindowTitle(tr("Import PNG → SIDBOX Indexed PPB"));
    setMinimumWidth(720);
    resize(1060, 760);
    setStyleSheet(QStringLiteral("QDialog { border-radius: 0px; } QGroupBox, QPushButton, QComboBox, QSpinBox, QLabel { border-radius: 0px; }"));
    auto *layout = new QVBoxLayout(this);
    auto *form = new QFormLayout();
    m_destination = new QComboBox(this);
    m_destination->addItem(tr("Tile Atlases (resource only)"), QStringLiteral("tileatlas"));
    m_destination->addItem(tr("Sprites (on game canvas)"), QStringLiteral("sprite"));
    m_destination->addItem(tr("Backgrounds"), QStringLiteral("background"));
    const int initial = m_destination->findData(initialKind);
    if (initial >= 0) m_destination->setCurrentIndex(initial);
    form->addRow(tr("Import into:"), m_destination);
    m_bank = new QComboBox(this);
    m_bank->addItem(tr("Foreground CLUT"), QStringLiteral("foreground"));
    m_bank->addItem(tr("Background CLUT"), QStringLiteral("background"));
    form->addRow(tr("Palette bank:"), m_bank);
    m_mode = new QComboBox(this);
    m_mode->addItem(tr("Generate colours in selected range"), true);
    m_mode->addItem(tr("Match existing palette colours (do not modify)"), false);
    form->addRow(tr("Palette mode:"), m_mode);
    auto *range = new QWidget(this);
    auto *rangeLayout = new QHBoxLayout(range);
    rangeLayout->setContentsMargins(0,0,0,0);
    m_first = new QSpinBox(this); m_first->setRange(1,255); m_first->setValue(1);
    m_last = new QSpinBox(this); m_last->setRange(1,255); m_last->setValue(255);
    rangeLayout->addWidget(m_first);
    rangeLayout->addWidget(new QLabel(tr("through"), this));
    rangeLayout->addWidget(m_last);
    rangeLayout->addWidget(new QLabel(tr("(0 is always transparent)"), this));
    form->addRow(tr("Palette index range:"), range);
    m_fresh = new QCheckBox(tr("Start with a blank palette (otherwise preserve existing colours)"), this);
    form->addRow(QString(), m_fresh);
    m_dither = new QComboBox(this);
    m_dither->addItem(tr("None (pixel art / exact colours)"), int(SidboxPngImport::Dither::None));
    m_dither->addItem(tr("Floyd–Steinberg error diffusion"), int(SidboxPngImport::Dither::FloydSteinberg));
    m_dither->addItem(tr("Ordered 4×4 dither"), int(SidboxPngImport::Dither::Ordered));
    m_dither->addItem(tr("Noise dither (reproducible)"), int(SidboxPngImport::Dither::Noise));
    form->addRow(tr("Dithering:"), m_dither);
    layout->addLayout(form);
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
    viewTools->addWidget(new QLabel(tr("Drag to pan  •  Wheel to zoom"), this));
    layout->addLayout(viewTools);

    auto *previews = new QHBoxLayout();
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
    layout->addLayout(previews, 1);

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

    m_status = new QLabel(this);
    m_status->setWordWrap(true);
    layout->addWidget(m_status);
    m_swatch = new QLabel(this);
    m_swatch->setMinimumHeight(26);
    layout->addWidget(m_swatch);
    auto *note = new QLabel(tr("Both previews show full-resolution pixels; changing palette settings may take longer for large PNGs. "
        "Alpha below 50% becomes index 0; other pixels are opaque. "
        "Saving a palette over a used range may recolour older graphics using those indices."), this);
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
    connect(m_fresh, &QCheckBox::toggled, this, [this]() { queuePreview(); });
    m_before->setImage(m_source);
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
    opt.dither = SidboxPngImport::Dither(m_dither->currentData().toInt());
    return opt;
}
QVector<QRgb> PngPaletteImportDialog::basePalette() const {
    return palettePlane() == QStringLiteral("background") ? m_back : m_front;
}
QString PngPaletteImportDialog::destinationKind() const { return m_destination->currentData().toString(); }
QString PngPaletteImportDialog::palettePlane() const { return m_bank->currentData().toString(); }

void PngPaletteImportDialog::updateControls() {
    const QString kind = destinationKind();
    const bool fixedBank = !m_dualPlane || kind == QStringLiteral("tileatlas")
                           || kind == QStringLiteral("background");
    if (fixedBank) m_bank->setCurrentIndex(m_dualPlane && kind == QStringLiteral("background") ? 1 : 0);
    m_bank->setEnabled(!fixedBank);
    m_fresh->setEnabled(m_mode->currentData().toBool());
    if (!m_fresh->isEnabled()) m_fresh->setChecked(false);
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
    m_status->setText(ok ? tr("Indices %1–%2: %3 available colours. %4")
                        .arg(opt.first).arg(opt.last).arg(result.paletteColours)
                        .arg(!opt.buildColours ? tr("Existing CLUT will not be changed.")
                              : opt.startFresh ? tr("Starting with a blank CLUT; other entries reset.")
                              : tr("All other palette indices are preserved from the selected CLUT.")) : error);
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

#include "gamepixarteditor.h"

#include "gamepalette.h"
#include "gamepalettepicker.h"
#include "ppbcodec.h"

#include <QCheckBox>
#include <QColor>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QDir>
#include <QDirIterator>
#include <QFileDialog>
#include <QFileInfo>
#include <QFormLayout>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QRegularExpression>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QIcon>
#include <QImage>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QPoint>
#include <QPushButton>
#include <QRandomGenerator>
#include <QSaveFile>
#include <QSettings>
#include <QSizePolicy>
#include <QSpinBox>
#include <QSplitter>
#include <QScrollBar>
#include <QStandardPaths>
#include <QStringList>
#include <QToolButton>
#include <QVBoxLayout>
#include <QWheelEvent>
#include <QtMath>

#include <algorithm>
#include <cmath>

namespace {

class PixArtView final : public QGraphicsView
{
public:
    explicit PixArtView(QWidget *parent = nullptr)
        : QGraphicsView(parent), m_scene(new QGraphicsScene(this)), m_item(new QGraphicsPixmapItem)
    {
        m_scene->addItem(m_item);
        setScene(m_scene);
        setDragMode(QGraphicsView::NoDrag);
        setRenderHint(QPainter::SmoothPixmapTransform, false);
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        setResizeAnchor(QGraphicsView::AnchorViewCenter);
        setBackgroundBrush(QColor(26, 28, 34));
        setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    }

    void setImage(const QImage &image)
    {
        m_image = image;
        m_item->setPixmap(QPixmap::fromImage(image));
        m_item->setTransformationMode(Qt::FastTransformation);
        m_scene->setSceneRect(m_item->boundingRect());
        fitImage();
    }

    void fitImage()
    {
        if (m_image.isNull()) return;
        resetTransform();
        fitInView(m_item, Qt::KeepAspectRatio);
        m_zoom = transform().m11();
    }

    void zoomIn() { applyZoom(1.25); }
    void zoomOut() { applyZoom(0.8); }

protected:
    void wheelEvent(QWheelEvent *event) override
    {
        if (event->angleDelta().y() == 0) return;
        applyZoom(event->angleDelta().y() > 0 ? 1.12 : (1.0 / 1.12));
        event->accept();
    }

    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::MiddleButton) {
            m_panning = true;
            m_lastPanPos = event->pos();
            setCursor(Qt::ClosedHandCursor);
            event->accept();
            return;
        }
        QGraphicsView::mousePressEvent(event);
    }

    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (m_panning) {
            const QPoint delta = event->pos() - m_lastPanPos;
            m_lastPanPos = event->pos();
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
            event->accept();
            return;
        }
        QGraphicsView::mouseMoveEvent(event);
    }

    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (event->button() == Qt::MiddleButton && m_panning) {
            m_panning = false;
            unsetCursor();
            event->accept();
            return;
        }
        QGraphicsView::mouseReleaseEvent(event);
    }

private:
    void applyZoom(double factor)
    {
        if (m_image.isNull()) return;
        const qreal current = transform().m11();
        const qreal next = current * factor;
        if (next < 0.5 || next > 64.0) return;
        scale(factor, factor);
        m_zoom = next;
    }

    QGraphicsScene *m_scene = nullptr;
    QGraphicsPixmapItem *m_item = nullptr;
    QImage m_image;
    bool m_panning = false;
    QPoint m_lastPanPos;
    qreal m_zoom = 1.0;
};

struct PaletteChoice {
    QString path;
    QString label;
};

struct GeneratorContext {
    int width = 320;
    int height = 180;
    int seed = 1;
    int detail = 50;
    int density = 50;
    int horizon = 60;
    bool tileX = true;
    bool tileY = false;
    int background = 0;
    int base = 1;
    int shadow = 2;
    int highlight = 3;
    int accent = 4;
    QVector<QRgb> palette;
};

static quint32 mixBits(quint32 x)
{
    x ^= x >> 16;
    x *= 0x7feb352dU;
    x ^= x >> 15;
    x *= 0x846ca68bU;
    x ^= x >> 16;
    return x;
}

static double hashUnit(int seed, int x, int y)
{
    const quint32 h = mixBits(static_cast<quint32>(seed) ^
                              (static_cast<quint32>(x) * 0x1f123bb5U) ^
                              (static_cast<quint32>(y) * 0x94d049bbU));
    return static_cast<double>(h & 0x00ffffffU) / static_cast<double>(0x01000000U);
}

static int wrapIndex(int value, int wrap)
{
    if (wrap <= 0) return value;
    const int mod = value % wrap;
    return mod < 0 ? mod + wrap : mod;
}

static double smoothStep(double t)
{
    return t * t * (3.0 - 2.0 * t);
}

static double lerp(double a, double b, double t)
{
    return a + (b - a) * t;
}

static double valueNoise2D(double x, double y, int seed, int wrapX, int wrapY)
{
    const int ix = static_cast<int>(std::floor(x));
    const int iy = static_cast<int>(std::floor(y));
    const double fx = x - ix;
    const double fy = y - iy;

    const int x0 = wrapIndex(ix, wrapX);
    const int y0 = wrapIndex(iy, wrapY);
    const int x1 = wrapIndex(ix + 1, wrapX);
    const int y1 = wrapIndex(iy + 1, wrapY);

    const double v00 = hashUnit(seed, x0, y0);
    const double v10 = hashUnit(seed, x1, y0);
    const double v01 = hashUnit(seed, x0, y1);
    const double v11 = hashUnit(seed, x1, y1);

    const double sx = smoothStep(fx);
    const double sy = smoothStep(fy);
    return lerp(lerp(v00, v10, sx), lerp(v01, v11, sx), sy);
}

static double fractalNoise2D(double x, double y, int seed, int wrapX, int wrapY,
                             int octaves, double persistence)
{
    double amplitude = 1.0;
    double frequency = 1.0;
    double total = 0.0;
    double norm = 0.0;
    for (int i = 0; i < octaves; ++i) {
        const int scaledWrapX = wrapX > 0 ? qMax(1, static_cast<int>(wrapX * frequency)) : 0;
        const int scaledWrapY = wrapY > 0 ? qMax(1, static_cast<int>(wrapY * frequency)) : 0;
        total += valueNoise2D(x * frequency, y * frequency, seed + i * 17, scaledWrapX, scaledWrapY) * amplitude;
        norm += amplitude;
        amplitude *= persistence;
        frequency *= 2.0;
    }
    return norm > 0.0 ? total / norm : 0.0;
}

static double fractalNoise1D(double x, int seed, int wrap, int octaves, double persistence)
{
    return fractalNoise2D(x, 0.37, seed, wrap, 1, octaves, persistence);
}

static QImage makeIndexedImage(int width, int height, const QVector<QRgb> &palette, int fillIndex)
{
    QImage image(width, height, QImage::Format_Indexed8);
    QVector<QRgb> table = palette;
    while (table.size() < 256) table.push_back(qRgba(0, 0, 0, 255));
    image.setColorTable(table);
    image.fill(qBound(0, fillIndex, 255));
    return image;
}

static inline void putPixel(QImage &image, int x, int y, int index)
{
    if (x < 0 || y < 0 || x >= image.width() || y >= image.height()) return;
    image.setPixel(x, y, qBound(0, index, 255));
}

static void generateChecker(QImage &image, const GeneratorContext &ctx)
{
    const int cell = qMax(2, 4 + ctx.detail / 8);
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            const bool a = ((x / cell) + (y / cell)) % 2 == 0;
            int idx = a ? ctx.base : ctx.highlight;
            const double n = fractalNoise2D(x / 6.0, y / 6.0, ctx.seed, ctx.tileX ? image.width() : 0,
                                            ctx.tileY ? image.height() : 0, 3, 0.5);
            if (n < 0.28) idx = ctx.shadow;
            if (n > 0.82) idx = ctx.accent;
            putPixel(image, x, y, idx);
        }
    }
}

static void generateBrick(QImage &image, const GeneratorContext &ctx)
{
    const int brickW = qMax(8, 12 + ctx.detail / 2);
    const int brickH = qMax(4, 6 + ctx.detail / 6);
    const int mortar = qMax(1, 1 + ctx.density / 40);
    image.fill(ctx.highlight);
    for (int y = 0; y < image.height(); ++y) {
        const int row = y / brickH;
        const int rowOffset = (row % 2) ? brickW / 2 : 0;
        for (int x = 0; x < image.width(); ++x) {
            const int localX = wrapIndex(x + rowOffset, brickW);
            const int localY = y % brickH;
            if (localX < mortar || localY < mortar) {
                putPixel(image, x, y, ctx.highlight);
                continue;
            }
            int idx = ctx.base;
            const double n = fractalNoise2D(x / 9.0, y / 7.0, ctx.seed + 3,
                                            ctx.tileX ? image.width() : 0,
                                            ctx.tileY ? image.height() : 0, 4, 0.55);
            if (n < 0.33) idx = ctx.shadow;
            else if (n > 0.73) idx = ctx.accent;
            if ((x + y) % 7 == 0 && n > 0.62) idx = ctx.highlight;
            putPixel(image, x, y, idx);
        }
    }
}

static void generateGrass(QImage &image, const GeneratorContext &ctx)
{
    image.fill(ctx.background);
    const int ground = qBound(4, image.height() * (35 + ctx.horizon / 2) / 100, image.height() - 2);
    for (int y = ground; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            const double n = fractalNoise2D(x / 12.0, y / 12.0, ctx.seed + 11,
                                            ctx.tileX ? image.width() : 0,
                                            ctx.tileY ? image.height() : 0, 4, 0.5);
            int idx = ctx.base;
            if (n < 0.28) idx = ctx.shadow;
            else if (n > 0.74) idx = ctx.highlight;
            putPixel(image, x, y, idx);
        }
    }
    for (int x = 0; x < image.width(); ++x) {
        const double bladeNoise = fractalNoise1D(x / 7.0, ctx.seed + 21, ctx.tileX ? image.width() : 0, 3, 0.6);
        const int bladeHeight = qMax(3, 4 + static_cast<int>(bladeNoise * (6 + ctx.detail / 8)));
        for (int i = 0; i < bladeHeight; ++i) {
            const int y = ground - i;
            const int dx = (i % 3 == 0) ? 0 : ((hashUnit(ctx.seed + 33, x, i) > 0.5) ? 1 : -1);
            int idx = (i < bladeHeight / 3) ? ctx.highlight : ctx.base;
            if (i > bladeHeight * 2 / 3) idx = ctx.shadow;
            putPixel(image, x + dx, y, idx);
        }
        if ((x + ctx.seed) % qMax(6, 24 - ctx.density / 5) == 0)
            putPixel(image, x, ground - bladeHeight, ctx.accent);
    }
}

static void generateWater(QImage &image, const GeneratorContext &ctx)
{
    image.fill(ctx.base);
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            const double wave = std::sin((x / qMax(6.0, 18.0 - ctx.detail / 6.0)) + y * 0.25 + ctx.seed * 0.1);
            const double n = fractalNoise2D(x / 16.0, y / 10.0, ctx.seed + 41,
                                            ctx.tileX ? image.width() : 0,
                                            ctx.tileY ? image.height() : 0, 4, 0.5);
            int idx = ctx.base;
            const double v = 0.55 * n + 0.45 * ((wave + 1.0) * 0.5);
            if (v < 0.36) idx = ctx.shadow;
            else if (v > 0.7) idx = ctx.highlight;
            if (std::fabs(wave) > 0.96 && n > 0.6) idx = ctx.accent;
            putPixel(image, x, y, idx);
        }
    }
}

static void generateClouds(QImage &image, const GeneratorContext &ctx)
{
    image.fill(ctx.background);
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            const double n = fractalNoise2D(x / qMax(20.0, 56.0 - ctx.detail / 2.0),
                                            y / qMax(12.0, 32.0 - ctx.detail / 3.0),
                                            ctx.seed + 55,
                                            ctx.tileX ? image.width() : 0,
                                            ctx.tileY ? image.height() : 0, 5, 0.58);
            if (n > 0.78) putPixel(image, x, y, ctx.highlight);
            else if (n > 0.67) putPixel(image, x, y, ctx.base);
            else if (n > 0.59) putPixel(image, x, y, ctx.shadow);
            if ((y + x) % 31 == 0 && n > 0.82) putPixel(image, x, y, ctx.accent);
        }
    }
}

static void generateMountain(QImage &image, const GeneratorContext &ctx)
{
    image.fill(ctx.background);
    const int baseLine = qBound(8, image.height() * ctx.horizon / 100, image.height() - 4);

    auto paintLayer = [&](int layerSeed, int topIndex, int sideIndex, int ridgeIndex, int heightRange, int yOffset) {
        QVector<int> heights(image.width());
        for (int x = 0; x < image.width(); ++x) {
            const double n = fractalNoise1D(x / qMax(18.0, 60.0 - ctx.detail / 2.0),
                                            ctx.seed + layerSeed,
                                            ctx.tileX ? image.width() : 0,
                                            4, 0.56);
            heights[x] = qBound(0, baseLine - static_cast<int>(n * heightRange) + yOffset, image.height() - 1);
        }
        for (int x = 0; x < image.width(); ++x) {
            const int h = heights[x];
            const int next = heights[(x + 1) % image.width()];
            for (int y = h; y < image.height(); ++y) {
                int idx = topIndex;
                if (y < h + 2) idx = ridgeIndex;
                else if (next < h) idx = sideIndex;
                putPixel(image, x, y, idx);
            }
        }
    };

    paintLayer(71, ctx.shadow, ctx.base, ctx.highlight, qMax(10, image.height() / 4), image.height() / 6);
    paintLayer(83, ctx.base, ctx.shadow, ctx.accent, qMax(12, image.height() / 3), image.height() / 12);
}

static void generateStarfield(QImage &image, const GeneratorContext &ctx)
{
    image.fill(ctx.background);
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            const double nebula = fractalNoise2D(x / 22.0, y / 18.0, ctx.seed + 99,
                                                 ctx.tileX ? image.width() : 0,
                                                 ctx.tileY ? image.height() : 0, 4, 0.55);
            if (nebula > 0.72) putPixel(image, x, y, ctx.shadow);
            if (nebula > 0.86) putPixel(image, x, y, ctx.base);
            const quint32 h = mixBits(static_cast<quint32>(ctx.seed * 131 + x * 37 + y * 151));
            if ((h % qMax(20, 120 - ctx.density)) == 0) putPixel(image, x, y, ctx.highlight);
            if ((h % qMax(64, 220 - ctx.density)) == 1) putPixel(image, x, y, ctx.accent);
        }
    }
}

static void generateRock(QImage &image, const GeneratorContext &ctx)
{
    image.fill(ctx.base);
    for (int y = 0; y < image.height(); ++y) {
        for (int x = 0; x < image.width(); ++x) {
            const double n = fractalNoise2D(x / qMax(5.0, 16.0 - ctx.detail / 8.0),
                                            y / qMax(5.0, 16.0 - ctx.detail / 8.0),
                                            ctx.seed + 121,
                                            ctx.tileX ? image.width() : 0,
                                            ctx.tileY ? image.height() : 0, 5, 0.58);
            int idx = ctx.base;
            if (n < 0.32) idx = ctx.shadow;
            else if (n > 0.74) idx = ctx.highlight;
            if (std::fabs(n - 0.5) < 0.03) idx = ctx.accent;
            putPixel(image, x, y, idx);
        }
    }
}

static void generateGradient(QImage &image, const GeneratorContext &ctx)
{
    for (int y = 0; y < image.height(); ++y) {
        const double t = image.height() > 1 ? static_cast<double>(y) / static_cast<double>(image.height() - 1) : 0.0;
        const int band = (t < 0.22) ? ctx.highlight
                       : (t < 0.5) ? ctx.base
                       : (t < 0.8) ? ctx.shadow
                                   : ctx.accent;
        for (int x = 0; x < image.width(); ++x) {
            int idx = band;
            if (((x + y + ctx.seed) & 3) == 0 && t > 0.18 && t < 0.82)
                idx = (idx == ctx.base) ? ctx.highlight : idx;
            putPixel(image, x, y, idx);
        }
    }
}

static QString generatorDescription(const QString &name)
{
    if (name == QStringLiteral("Checker / Fabric"))
        return QObject::tr("Loopable patterned texture useful for cloth, floors and decorative panels.");
    if (name == QStringLiteral("Brick Wall"))
        return QObject::tr("Procedural masonry blocks with mortar seams for walls, houses and ruins.");
    if (name == QStringLiteral("Grass Texture"))
        return QObject::tr("Ground texture with blade highlights and optional accent flowers or tufts.");
    if (name == QStringLiteral("Water Texture"))
        return QObject::tr("Animated-looking wave pattern suitable for lakes, rivers and magical pools.");
    if (name == QStringLiteral("Cloud Background"))
        return QObject::tr("Soft noise-based sky clouds. Horizontal tiling makes it suitable for scrolling backgrounds.");
    if (name == QStringLiteral("Mountain Landscape"))
        return QObject::tr("Layered horizon silhouettes for loopable parallax-style landscape backdrops.");
    if (name == QStringLiteral("Starfield / Space"))
        return QObject::tr("Dark sky, nebula hints and stars for night scenes and space backgrounds.");
    if (name == QStringLiteral("Rock / Cave"))
        return QObject::tr("Rocky texture with crack-like veins for cave walls, stone surfaces and dungeon tiles.");
    if (name == QStringLiteral("Dithered Gradient"))
        return QObject::tr("Simple layered gradient background for skies, menu backdrops and overlays.");
    return QObject::tr("Procedural pixel-art generator.");
}

static QImage generateImage(const QString &generatorName, const GeneratorContext &ctx)
{
    QImage image = makeIndexedImage(ctx.width, ctx.height, ctx.palette, ctx.background);
    if (generatorName == QStringLiteral("Checker / Fabric")) generateChecker(image, ctx);
    else if (generatorName == QStringLiteral("Brick Wall")) generateBrick(image, ctx);
    else if (generatorName == QStringLiteral("Grass Texture")) generateGrass(image, ctx);
    else if (generatorName == QStringLiteral("Water Texture")) generateWater(image, ctx);
    else if (generatorName == QStringLiteral("Cloud Background")) generateClouds(image, ctx);
    else if (generatorName == QStringLiteral("Mountain Landscape")) generateMountain(image, ctx);
    else if (generatorName == QStringLiteral("Starfield / Space")) generateStarfield(image, ctx);
    else if (generatorName == QStringLiteral("Rock / Cave")) generateRock(image, ctx);
    else generateGradient(image, ctx);
    return image;
}

static QString savePngAtomically(const QString &path, const QImage &image)
{
    QSaveFile file(path);
    if (!file.open(QIODevice::WriteOnly))
        return QObject::tr("Could not open %1 for writing.").arg(QDir::toNativeSeparators(path));
    if (!image.save(&file, "PNG"))
        return QObject::tr("Failed to encode PNG for %1.").arg(QDir::toNativeSeparators(path));
    if (!file.commit())
        return QObject::tr("Could not finalise PNG export to %1.").arg(QDir::toNativeSeparators(path));
    return QString();
}

static void updatePaletteButton(QPushButton *button, const QString &label,
                                int index, const QVector<QRgb> &palette)
{
    const QColor colour = QColor::fromRgba(index >= 0 && index < palette.size()
                                               ? palette.at(index)
                                               : qRgba(0,0,0,255));
    QPixmap swatch(22, 22);
    swatch.fill(colour);
    button->setIcon(QIcon(swatch));
    button->setIconSize(QSize(22,22));
    button->setText(QObject::tr("%1: %2").arg(label).arg(index));
    button->setToolTip(QObject::tr("Palette index %1 (%2)").arg(index)
                           .arg(colour.name(QColor::HexArgb).toUpper()));
}

static QVector<PaletteChoice> findPalettes(const QString &projectRoot)
{
    QVector<PaletteChoice> out;
    QDirIterator it(projectRoot, QStringList() << QStringLiteral("*.pal"), QDir::Files,
                    QDirIterator::Subdirectories);
    while (it.hasNext()) {
        const QString path = it.next();
        const QString rel = QDir(projectRoot).relativeFilePath(path);
        out.push_back({ path, rel });
    }
    std::sort(out.begin(), out.end(), [](const PaletteChoice &a, const PaletteChoice &b) {
        return a.label.compare(b.label, Qt::CaseInsensitive) < 0;
    });
    return out;
}

} // namespace

bool openGamePixArtEditor(QWidget *parent, const QString &projectRoot, QString *errorOut)
{
    const QVector<PaletteChoice> palettes = findPalettes(projectRoot);
    if (palettes.isEmpty()) {
        if (errorOut) *errorOut = QObject::tr("No .pal files were found in this project. Create or import a palette first, then open PixArt again.");
        return false;
    }

    QDialog dialog(parent);
    dialog.setWindowTitle(QObject::tr("PixArt Generator"));
    dialog.setModal(true);

    auto *root = new QVBoxLayout(&dialog);
    auto *splitter = new QSplitter(Qt::Horizontal, &dialog);
    splitter->setChildrenCollapsible(false);
    root->addWidget(splitter, 1);

    auto *leftHost = new QWidget(splitter);
    leftHost->setMinimumWidth(360);
    auto *left = new QVBoxLayout(leftHost);
    left->setContentsMargins(6,6,6,6);

    auto *intro = new QLabel(QObject::tr(
        "Generate palette-aware pixel-art textures, loopable landscapes and backgrounds using the .pal files already in this project. "
        "Choose a palette, pick the key indices, generate a preview, then export the result as PNG or PPB."), leftHost);
    intro->setWordWrap(true);
    left->addWidget(intro);

    auto *presetBox = new QGroupBox(QObject::tr("Generator"), leftHost);
    auto *presetLayout = new QFormLayout(presetBox);
    auto *generator = new QComboBox(presetBox);
    generator->addItems({
        QObject::tr("Checker / Fabric"),
        QObject::tr("Brick Wall"),
        QObject::tr("Grass Texture"),
        QObject::tr("Water Texture"),
        QObject::tr("Cloud Background"),
        QObject::tr("Mountain Landscape"),
        QObject::tr("Starfield / Space"),
        QObject::tr("Rock / Cave"),
        QObject::tr("Dithered Gradient")
    });
    auto *description = new QLabel(generatorDescription(generator->currentText()), presetBox);
    description->setWordWrap(true);
    auto *seed = new QSpinBox(presetBox);
    seed->setRange(0, 999999);
    seed->setValue(static_cast<int>(QRandomGenerator::global()->bounded(100000)));
    auto *randomSeed = new QToolButton(presetBox);
    randomSeed->setText(QObject::tr("Randomise"));
    auto *seedRow = new QWidget(presetBox);
    auto *seedRowLayout = new QHBoxLayout(seedRow);
    seedRowLayout->setContentsMargins(0,0,0,0);
    seedRowLayout->addWidget(seed, 1);
    seedRowLayout->addWidget(randomSeed);
    auto *width = new QSpinBox(presetBox);
    auto *height = new QSpinBox(presetBox);
    for (auto *spin : {width, height}) {
        spin->setRange(8, 2048);
        spin->setSingleStep(8);
    }
    width->setValue(320);
    height->setValue(180);
    auto *detail = new QSpinBox(presetBox);
    auto *density = new QSpinBox(presetBox);
    auto *horizon = new QSpinBox(presetBox);
    detail->setRange(1, 100);
    density->setRange(1, 100);
    horizon->setRange(1, 100);
    detail->setValue(50);
    density->setValue(50);
    horizon->setValue(60);
    auto *tileX = new QCheckBox(QObject::tr("Tile seamlessly in X"), presetBox);
    auto *tileY = new QCheckBox(QObject::tr("Tile seamlessly in Y"), presetBox);
    tileX->setChecked(true);
    presetLayout->addRow(QObject::tr("Preset"), generator);
    presetLayout->addRow(QObject::tr("Description"), description);
    presetLayout->addRow(QObject::tr("Width"), width);
    presetLayout->addRow(QObject::tr("Height"), height);
    presetLayout->addRow(QObject::tr("Seed"), seedRow);
    presetLayout->addRow(QObject::tr("Detail"), detail);
    presetLayout->addRow(QObject::tr("Density"), density);
    presetLayout->addRow(QObject::tr("Horizon"), horizon);
    presetLayout->addRow(tileX);
    presetLayout->addRow(tileY);
    left->addWidget(presetBox);

    auto *paletteBox = new QGroupBox(QObject::tr("Palette"), leftHost);
    auto *paletteLayout = new QFormLayout(paletteBox);
    auto *paletteFile = new QComboBox(paletteBox);
    for (const PaletteChoice &choice : palettes)
        paletteFile->addItem(choice.label, choice.path);
    auto *bank = new QComboBox(paletteBox);
    bank->addItem(QObject::tr("Foreground bank"), false);
    bank->addItem(QObject::tr("Background bank"), true);
    paletteLayout->addRow(QObject::tr(".pal file"), paletteFile);
    paletteLayout->addRow(QObject::tr("Bank"), bank);
    left->addWidget(paletteBox);

    auto *colourBox = new QGroupBox(QObject::tr("Generator Colours"), leftHost);
    auto *colourLayout = new QVBoxLayout(colourBox);
    auto *colourNote = new QLabel(QObject::tr(
        "Choose the palette indices the generator should use. This does not edit the palette file; it only selects indices from the chosen CLUT."), colourBox);
    colourNote->setWordWrap(true);
    colourLayout->addWidget(colourNote);
    auto *backgroundButton = new QPushButton(colourBox);
    auto *baseButton = new QPushButton(colourBox);
    auto *shadowButton = new QPushButton(colourBox);
    auto *highlightButton = new QPushButton(colourBox);
    auto *accentButton = new QPushButton(colourBox);
    for (auto *button : {backgroundButton, baseButton, shadowButton, highlightButton, accentButton})
        button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    colourLayout->addWidget(backgroundButton);
    colourLayout->addWidget(baseButton);
    colourLayout->addWidget(shadowButton);
    colourLayout->addWidget(highlightButton);
    colourLayout->addWidget(accentButton);
    left->addWidget(colourBox);

    auto *actions = new QWidget(leftHost);
    auto *actionsLayout = new QHBoxLayout(actions);
    actionsLayout->setContentsMargins(0,0,0,0);
    auto *generate = new QPushButton(QObject::tr("Generate Preview"), actions);
    auto *fit = new QPushButton(QObject::tr("Fit View"), actions);
    auto *exportPng = new QPushButton(QObject::tr("Export PNG..."), actions);
    auto *exportPpb = new QPushButton(QObject::tr("Export PPB..."), actions);
    actionsLayout->addWidget(generate);
    actionsLayout->addWidget(fit);
    actionsLayout->addStretch(1);
    actionsLayout->addWidget(exportPng);
    actionsLayout->addWidget(exportPpb);
    left->addWidget(actions);
    left->addStretch(1);

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Close, leftHost);
    left->addWidget(buttons);

    auto *rightHost = new QWidget(splitter);
    auto *right = new QVBoxLayout(rightHost);
    right->setContentsMargins(6,6,6,6);
    auto *previewLabel = new QLabel(QObject::tr("Preview"), rightHost);
    right->addWidget(previewLabel);
    auto *view = new PixArtView(rightHost);
    view->setMinimumSize(520, 420);
    right->addWidget(view, 1);
    auto *previewNote = new QLabel(QObject::tr(
        "Mouse wheel: zoom  •  Middle-drag: pan  •  Export as PNG or PPB when the result looks right."), rightHost);
    previewNote->setWordWrap(true);
    right->addWidget(previewNote);

    splitter->addWidget(leftHost);
    splitter->addWidget(rightHost);
    splitter->setStretchFactor(1, 1);

    QImage currentImage;
    QVector<QRgb> currentPalette;
    bool exportedSomething = false;

    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    const QString savedPalette = settings.value(QStringLiteral("PixArtEditor/lastPalette")).toString();
    if (!savedPalette.isEmpty()) {
        const int idx = paletteFile->findData(savedPalette);
        if (idx >= 0) paletteFile->setCurrentIndex(idx);
    }
    bank->setCurrentIndex(settings.value(QStringLiteral("PixArtEditor/backgroundBank"), 1).toInt() ? 1 : 0);
    width->setValue(settings.value(QStringLiteral("PixArtEditor/width"), width->value()).toInt());
    height->setValue(settings.value(QStringLiteral("PixArtEditor/height"), height->value()).toInt());
    generator->setCurrentIndex(settings.value(QStringLiteral("PixArtEditor/generator"), 0).toInt());
    tileX->setChecked(settings.value(QStringLiteral("PixArtEditor/tileX"), true).toBool());
    tileY->setChecked(settings.value(QStringLiteral("PixArtEditor/tileY"), false).toBool());

    auto reloadPalette = [&]() -> bool {
        const QString path = paletteFile->currentData().toString();
        QString error;
        currentPalette = SidboxGamePalette::readPalette(path, bank->currentData().toBool(), &error);
        if (currentPalette.size() != 256) {
            QMessageBox::warning(&dialog, QObject::tr("PixArt"),
                                 error.isEmpty()
                                 ? QObject::tr("Failed to read a usable 256-colour palette from %1.").arg(path)
                                 : error);
            return false;
        }
        return true;
    };

    int selectedBackground = 0;
    int selectedBase = 1;
    int selectedShadow = 2;
    int selectedHighlight = 3;
    int selectedAccent = 4;
    auto resetDefaultIndices = [&]() {
        if (bank->currentData().toBool()) {
            selectedBackground = 0;
            selectedBase = 1;
            selectedShadow = 2;
            selectedHighlight = 3;
            selectedAccent = 4;
        } else {
            selectedBackground = 1;
            selectedBase = 2;
            selectedShadow = 3;
            selectedHighlight = 4;
            selectedAccent = 5;
        }
    };

    auto refreshColourButtons = [&]() {
        updatePaletteButton(backgroundButton, QObject::tr("Background"), selectedBackground, currentPalette);
        updatePaletteButton(baseButton, QObject::tr("Base"), selectedBase, currentPalette);
        updatePaletteButton(shadowButton, QObject::tr("Shadow"), selectedShadow, currentPalette);
        updatePaletteButton(highlightButton, QObject::tr("Highlight"), selectedHighlight, currentPalette);
        updatePaletteButton(accentButton, QObject::tr("Accent"), selectedAccent, currentPalette);
    };

    auto doGenerate = [&]() {
        if (!reloadPalette()) return;
        GeneratorContext ctx;
        ctx.width = width->value();
        ctx.height = height->value();
        ctx.seed = seed->value();
        ctx.detail = detail->value();
        ctx.density = density->value();
        ctx.horizon = horizon->value();
        ctx.tileX = tileX->isChecked();
        ctx.tileY = tileY->isChecked();
        ctx.background = selectedBackground;
        ctx.base = selectedBase;
        ctx.shadow = selectedShadow;
        ctx.highlight = selectedHighlight;
        ctx.accent = selectedAccent;
        ctx.palette = currentPalette;
        currentImage = generateImage(generator->currentText(), ctx);
        view->setImage(currentImage);
        description->setText(generatorDescription(generator->currentText()));
    };

    auto chooseIndex = [&](const QString &title, int current, bool allowZero) -> int {
        return SidboxPalettePicker::chooseIndex(&dialog, currentPalette, current, title,
                                                QObject::tr("Select a palette index from the currently chosen .pal file."),
                                                allowZero, false);
    };

    QObject::connect(backgroundButton, &QPushButton::clicked, &dialog, [&]() {
        if (currentPalette.isEmpty() && !reloadPalette()) return;
        const int chosen = chooseIndex(QObject::tr("PixArt Background Colour"), selectedBackground, true);
        if (chosen >= 0) { selectedBackground = chosen; refreshColourButtons(); }
    });
    QObject::connect(baseButton, &QPushButton::clicked, &dialog, [&]() {
        if (currentPalette.isEmpty() && !reloadPalette()) return;
        const int chosen = chooseIndex(QObject::tr("PixArt Base Colour"), selectedBase, true);
        if (chosen >= 0) { selectedBase = chosen; refreshColourButtons(); }
    });
    QObject::connect(shadowButton, &QPushButton::clicked, &dialog, [&]() {
        if (currentPalette.isEmpty() && !reloadPalette()) return;
        const int chosen = chooseIndex(QObject::tr("PixArt Shadow Colour"), selectedShadow, true);
        if (chosen >= 0) { selectedShadow = chosen; refreshColourButtons(); }
    });
    QObject::connect(highlightButton, &QPushButton::clicked, &dialog, [&]() {
        if (currentPalette.isEmpty() && !reloadPalette()) return;
        const int chosen = chooseIndex(QObject::tr("PixArt Highlight Colour"), selectedHighlight, true);
        if (chosen >= 0) { selectedHighlight = chosen; refreshColourButtons(); }
    });
    QObject::connect(accentButton, &QPushButton::clicked, &dialog, [&]() {
        if (currentPalette.isEmpty() && !reloadPalette()) return;
        const int chosen = chooseIndex(QObject::tr("PixArt Accent Colour"), selectedAccent, true);
        if (chosen >= 0) { selectedAccent = chosen; refreshColourButtons(); }
    });

    QObject::connect(randomSeed, &QToolButton::clicked, &dialog, [seed, &doGenerate]() {
        seed->setValue(static_cast<int>(QRandomGenerator::global()->bounded(1000000)));
        doGenerate();
    });
    QObject::connect(generate, &QPushButton::clicked, &dialog, doGenerate);
    QObject::connect(fit, &QPushButton::clicked, view, [view]() { view->fitImage(); });
    QObject::connect(generator, &QComboBox::currentTextChanged, &dialog, [description](const QString &text) {
        description->setText(generatorDescription(text));
    });
    QObject::connect(paletteFile, &QComboBox::currentIndexChanged, &dialog, [&](int) {
        if (reloadPalette()) refreshColourButtons();
    });
    QObject::connect(bank, &QComboBox::currentIndexChanged, &dialog, [&](int) {
        if (reloadPalette()) {
            resetDefaultIndices();
            refreshColourButtons();
            doGenerate();
        }
    });

    QObject::connect(exportPng, &QPushButton::clicked, &dialog, [&]() {
        if (currentImage.isNull()) doGenerate();
        if (currentImage.isNull()) return;
        const QString startDir = settings.value(QStringLiteral("PixArtEditor/exportPngDir"), projectRoot).toString();
        const QString suggested = QStringLiteral("pixart_%1_%2x%3.png")
                                      .arg(generator->currentText().toLower().replace(QRegularExpression(QStringLiteral("[^a-z0-9]+")), QStringLiteral("_")))
                                      .arg(currentImage.width()).arg(currentImage.height());
        const QString path = QFileDialog::getSaveFileName(&dialog, QObject::tr("Export PixArt PNG"),
                                                          QDir(startDir).filePath(suggested),
                                                          QObject::tr("PNG image (*.png)"));
        if (path.isEmpty()) return;
        const QString err = savePngAtomically(path, currentImage);
        if (!err.isEmpty()) {
            QMessageBox::warning(&dialog, QObject::tr("Export PixArt PNG"), err);
            return;
        }
        settings.setValue(QStringLiteral("PixArtEditor/exportPngDir"), QFileInfo(path).absolutePath());
        exportedSomething = true;
        QMessageBox::information(&dialog, QObject::tr("Export PixArt PNG"),
                                 QObject::tr("Saved %1").arg(QDir::toNativeSeparators(path)));
    });

    QObject::connect(exportPpb, &QPushButton::clicked, &dialog, [&]() {
        if (currentImage.isNull()) doGenerate();
        if (currentImage.isNull()) return;
        const QString startDir = settings.value(QStringLiteral("PixArtEditor/exportPpbDir"), projectRoot).toString();
        const QString suggested = QStringLiteral("pixart_%1_%2x%3.ppb")
                                      .arg(generator->currentText().toLower().replace(QRegularExpression(QStringLiteral("[^a-z0-9]+")), QStringLiteral("_")))
                                      .arg(currentImage.width()).arg(currentImage.height());
        const QString path = QFileDialog::getSaveFileName(&dialog, QObject::tr("Export PixArt PPB"),
                                                          QDir(startDir).filePath(suggested),
                                                          QObject::tr("SIDBOX picture (*.ppb)"));
        if (path.isEmpty()) return;
        SidboxPpb::Picture picture;
        picture.indexed = currentImage;
        QString err;
        if (!SidboxPpb::write(path, picture, &err)) {
            QMessageBox::warning(&dialog, QObject::tr("Export PixArt PPB"),
                                 err.isEmpty() ? QObject::tr("Failed to save %1").arg(QDir::toNativeSeparators(path)) : err);
            return;
        }
        settings.setValue(QStringLiteral("PixArtEditor/exportPpbDir"), QFileInfo(path).absolutePath());
        exportedSomething = true;
        QMessageBox::information(&dialog, QObject::tr("Export PixArt PPB"),
                                 QObject::tr("Saved %1").arg(QDir::toNativeSeparators(path)));
    });

    QObject::connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (!reloadPalette()) {
        if (errorOut) *errorOut = QObject::tr("Could not load the selected palette.");
        return false;
    }
    resetDefaultIndices();
    refreshColourButtons();
    doGenerate();

    QSettings windowSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    if (!dialog.restoreGeometry(windowSettings.value(QStringLiteral("GamePixArtEditor/geometry")).toByteArray()))
        dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized);
    dialog.exec();
    windowSettings.setValue(QStringLiteral("GamePixArtEditor/geometry"), dialog.saveGeometry());

    settings.setValue(QStringLiteral("PixArtEditor/lastPalette"), paletteFile->currentData().toString());
    settings.setValue(QStringLiteral("PixArtEditor/backgroundBank"), bank->currentData().toBool() ? 1 : 0);
    settings.setValue(QStringLiteral("PixArtEditor/width"), width->value());
    settings.setValue(QStringLiteral("PixArtEditor/height"), height->value());
    settings.setValue(QStringLiteral("PixArtEditor/generator"), generator->currentIndex());
    settings.setValue(QStringLiteral("PixArtEditor/tileX"), tileX->isChecked());
    settings.setValue(QStringLiteral("PixArtEditor/tileY"), tileY->isChecked());

    return exportedSomething;
}

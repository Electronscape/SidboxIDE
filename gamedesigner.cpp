#include "gamedesigner.h"
#include "gamepalettepicker.h"
#include "gameglobalstamps.h"
#include "gameworldsnapshot.h"
#include "gamecrossworldlinks.h"
#include "gameplayerprofile.h"
#include "gamenpcitemindex.h"
#include "gamedesigner_limits.h"
#include "ppbcodec.h"
#include "pngpaletteimport.h"
#include "gamepalette.h"
#include "gamepaletteeditor.h"
#include "gamecodegen.h"
#include "gamehelpertemplates.h"
#include "gameadventureeditor.h"
#include "gamehudeditor.h"
#include "gamefloweditor.h"
#include "gamequesteditor.h"
#include "gametitlescreeneditor.h"
#include "gamepixarteditor.h"
#include "gameadventuregen.h"
#include "gameanimationeditor.h"
#include "gamemainownership.h"
#include "gameeditorcontrolstyle.h"
#include "gameeditoricons.h"

#include <QCheckBox>
#include <QColorDialog>
#include <QComboBox>
#include <QPaintEvent>
#include <QDir>
#include <QDirIterator>
#include <QEvent>
#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QContextMenuEvent>
#include <QMimeData>
#include <QUrl>
#include <QAbstractItemView>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QIcon>
#include <QDateTime>
#include <QFont>
#include <QFontMetrics>
#include <QFormLayout>
#include <QFrame>
#include <QGroupBox>
#include <QGraphicsItem>
#include <QApplication>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsPathItem>
#include <QPainterPath>
#include <QCoreApplication>
#include <QDialog>
#include <QDialogButtonBox>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSimpleTextItem>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QImage>
#include <QImageReader>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QLabel>
#include <QLineEdit>
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>
#include <QAction>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QPixmap>
#include <QPolygon>
#include <QPalette>
#include <QPushButton>
#include <QProgressDialog>
#include <QThread>
#include <QTimer>
#include <memory>
#include <algorithm>
#include <QSaveFile>
#include <zlib.h>
#include <limits>
#include <QScrollArea>
#include <QTabWidget>
#include <QPlainTextEdit>
#include <QScrollBar>
#include <QShowEvent>
#include <QSettings>
#include <QStyle>
#include <QSizePolicy>
#include <QListView>
#include <QListWidget>
#include <QSlider>
#include <QStringList>
#include <QSignalBlocker>
#include <QTextStream>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QSplitter>
#include <QToolButton>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QTableWidget>
#include <QHeaderView>
#include <QSet>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QUuid>
#include <QtMath>

namespace {
// Game Resource icons are compiled into the executable with Qt's resource
// system. Artists can replace icons/gr_icon_*.png in the source tree and
// rebuild; there are no runtime file lookups or external icon dependencies.
QIcon gameResourceIcon(const QString &fileName)
{
    return gameEditorIcon(fileName);
}

using SidboxGameDesignerLimits::LCD_WIDTH;
using SidboxGameDesignerLimits::LCD_HEIGHT;
using SidboxGameDesignerLimits::MAX_WORLD;


// Flat, theme-aware dropdown with a visible chevron. Drawing the arrow in
// foreground avoids losing it to platform-specific Qt style-sheet rendering.
class GameComboBox final : public QComboBox
{
public:
    explicit GameComboBox(QWidget *parent = nullptr) : QComboBox(parent)
    {
        setProperty("customChevron", true);
    }
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QComboBox::paintEvent(event);
        QPainter p(this);
        QPen pen(palette().color(isEnabled() ? QPalette::Active : QPalette::Disabled, QPalette::Text));
        pen.setWidth(2);
        p.setPen(pen);
        const int cx = width() - 12;
        const int cy = height() / 2;
        p.drawLine(cx - 4, cy - 2, cx, cy + 2);
        p.drawLine(cx, cy + 2, cx + 4, cy - 2);
    }
};

// Pick a death animation's FIRST frame visually. This is intentionally an
// editor-only dialog: the stored numeric frame ID and generated runtime data
// stay exactly the same. Cancel returns -2; -1 means explicitly no animation.
static int chooseDeathAtlasStart(QWidget *parent, const QImage &atlas,
                                 int cellW, int cellH, int previous,
                                 int sequenceLength, const QColor &accent)
{
    if (atlas.isNull() || cellW <= 0 || cellH <= 0) {
        QMessageBox::information(parent, QObject::tr("Death animation atlas"),
            QObject::tr("This sprite has no readable atlas. Check its PPB resource first."));
        return -2;
    }
    const int cols = atlas.width() / cellW;
    const int rows = atlas.height() / cellH;
    const int frames = qMin(256, cols * rows); // existing runtime index is 8-bit
    if (cols < 1 || rows < 1 || frames < 1) {
        QMessageBox::information(parent, QObject::tr("Death animation atlas"),
            QObject::tr("No complete sprite cells were found in this atlas."));
        return -2;
    }

    QDialog picker(parent);
    picker.setWindowTitle(QObject::tr("Choose Death Animation Start Frame"));
    picker.resize(750, 585);
    auto *layout = new QVBoxLayout(&picker);
    auto *instructions = new QLabel(QObject::tr(
        "Choose the FIRST death frame. Frames are numbered from 0, left to right, top to bottom.\n"
        "Double-click a frame to accept it. The following frames play once."), &picker);
    instructions->setWordWrap(true);
    layout->addWidget(instructions);
    auto *grid = new QListWidget(&picker);
    grid->setObjectName(QStringLiteral("GGDeathAtlasFramePicker"));
    grid->setViewMode(QListView::IconMode);
    grid->setResizeMode(QListView::Adjust);
    grid->setMovement(QListView::Static);
    grid->setWrapping(true);
    grid->setSpacing(5);
    grid->setIconSize(QSize(64, 64));
    grid->setGridSize(QSize(88, 94));
    grid->setUniformItemSizes(true);
    grid->setSelectionMode(QAbstractItemView::SingleSelection);
    layout->addWidget(grid, 1);

    // Keep pixels crisp, even when the game's sprite cell is tiny.
    auto pictureFor = [&](int index, int iconSize) -> QPixmap {
        const QImage cell = atlas.copy((index % cols) * cellW,
                                       (index / cols) * cellH, cellW, cellH);
        QPixmap image(iconSize, iconSize);
        image.fill(Qt::transparent);
        QPainter painter(&image);
        const QColor light(81, 81, 81), dark(57, 57, 57);
        const int check = 8;
        for (int y = 0; y < iconSize; y += check)
            for (int x = 0; x < iconSize; x += check)
                painter.fillRect(QRect(x, y, check, check),
                                 ((x + y) / check) % 2 ? light : dark);
        const QImage scaled = cell.scaled(iconSize - 6, iconSize - 6,
            Qt::KeepAspectRatio, Qt::FastTransformation);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
        painter.drawImage((iconSize - scaled.width()) / 2,
                          (iconSize - scaled.height()) / 2, scaled);
        return image;
    };
    for (int frame = 0; frame < frames; ++frame) {
        auto *item = new QListWidgetItem(QIcon(pictureFor(frame, 64)),
                                          QObject::tr("Frame %1").arg(frame));
        item->setData(Qt::UserRole, frame);
        item->setToolTip(QObject::tr("Frame %1 — atlas column %2, row %3")
            .arg(frame).arg(frame % cols).arg(frame / cols));
        item->setTextAlignment(Qt::AlignHCenter);
        grid->addItem(item);
    }
    const int initial = qBound(0, previous, frames - 1);
    grid->setCurrentRow(initial);
    grid->scrollToItem(grid->item(initial), QAbstractItemView::PositionAtCenter);

    auto *summary = new QLabel(&picker);
    summary->setWordWrap(true);
    layout->addWidget(summary);
    auto *strip = new QWidget(&picker);
    auto *stripLayout = new QHBoxLayout(strip);
    stripLayout->setContentsMargins(0, 0, 0, 0);
    stripLayout->setSpacing(5);
    layout->addWidget(strip);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &picker);
    auto *clear = buttons->addButton(QObject::tr("No death animation"), QDialogButtonBox::ResetRole);
    layout->addWidget(buttons);
    int chosen = -2;
    const int length = qMax(1, sequenceLength);
    const auto refresh = [&]() {
        const int selected = grid->currentRow();
        const bool valid = selected >= 0 && selected + length <= frames;
        buttons->button(QDialogButtonBox::Ok)->setEnabled(valid);
        summary->setText(valid
            ? QObject::tr("Death sequence: frames %1 to %2 (%3 frames).")
                .arg(selected).arg(selected + length - 1).arg(length)
            : QObject::tr("Not enough atlas frames after this start for %1 death frames. "
                           "Pick an earlier cell or reduce Number of death frames.")
                .arg(length));
        while (QLayoutItem *child = stripLayout->takeAt(0)) {
            delete child->widget();
            delete child;
        }
        if (selected < 0) return;
        for (int i = 0; i < qMin(length, 8) && selected + i < frames; ++i) {
            auto *label = new QLabel(strip);
            label->setFixedSize(54, 62);
            label->setAlignment(Qt::AlignCenter);
            label->setPixmap(pictureFor(selected + i, 48));
            label->setToolTip(QObject::tr("Death frame %1").arg(selected + i));
            stripLayout->addWidget(label);
        }
        if (length > 8) stripLayout->addWidget(new QLabel(QObject::tr("+ %1 more").arg(length - 8), strip));
        stripLayout->addStretch(1);
    };
    // Use the IDE's theme accent only for the visual selection indicator.
    grid->setStyleSheet(QStringLiteral("QListWidget#GGDeathAtlasFramePicker::item:selected {"
                                       " border:2px solid %1; border-radius:0px; }")
                            .arg(accent.name()));
    QObject::connect(grid, &QListWidget::currentRowChanged, &picker,
                     [&refresh](int) { refresh(); });
    QObject::connect(grid, &QListWidget::itemDoubleClicked, &picker,
                     [&](QListWidgetItem *item) {
        if (item && item->data(Qt::UserRole).toInt() + length <= frames) {
            chosen = item->data(Qt::UserRole).toInt();
            picker.accept();
        }
    });
    QObject::connect(buttons, &QDialogButtonBox::accepted, &picker, [&]() {
        chosen = grid->currentRow();
        picker.accept();
    });
    QObject::connect(buttons, &QDialogButtonBox::rejected, &picker, &QDialog::reject);
    QObject::connect(clear, &QPushButton::clicked, &picker, [&]() {
        chosen = -1;
        picker.accept();
    });
    refresh();
    return picker.exec() == QDialog::Accepted ? chosen : -2;
}

// World Editor names are editor overlays, not theme-coloured UI text.
// Render the dark keyline FIRST, then the thick, bright lettering over it:
// the dark stroke must never swallow the glyph on a busy background.
class WorldObjectTag final : public QGraphicsSimpleTextItem
{
public:
    explicit WorldObjectTag(const QString &name, QGraphicsItem *parent,
                            int fontPixels = 14,
                            const QColor &fill = QColor(255, 255, 225))
        : QGraphicsSimpleTextItem(name, parent), m_fill(fill)
    {
        QFont tagFont = font();
        tagFont.setWeight(QFont::Black);
        tagFont.setPixelSize(fontPixels);
        setFont(tagFont);
        // Reserve paint bounds for the outline even though paint() draws it itself.
        setPen(QPen(Qt::black, 3.4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    }
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing, true);
        const QFontMetricsF fm(font());
        QPainterPath glyph;
        glyph.addText(QPointF(0, fm.ascent()), font(), text());
        painter->setBrush(Qt::NoBrush);
        painter->setPen(QPen(Qt::black, 3.4, Qt::SolidLine,
                             Qt::RoundCap, Qt::RoundJoin));
        painter->drawPath(glyph);
        painter->setPen(Qt::NoPen);
        painter->setBrush(m_fill); // stable label colour, independent of UI theme
        painter->drawPath(glyph);
        painter->restore();
    }
private:
    QColor m_fill;
};

class GameScene final : public QGraphicsScene
{
public:
    explicit GameScene(QObject *parent = nullptr) : QGraphicsScene(parent) {}
    bool drawGrid = true;
    QColor gridColour = QColor(88, 105, 125, 65);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override
    {
        QGraphicsScene::drawBackground(painter, rect);
        if (!drawGrid) return;
        const int spacing = 32;
        const int firstX = qFloor(rect.left() / spacing) * spacing;
        const int firstY = qFloor(rect.top() / spacing) * spacing;
        QPen pen(gridColour, 0);
        painter->setPen(pen);
        for (int x = firstX; x <= rect.right(); x += spacing)
            painter->drawLine(QPointF(x, rect.top()), QPointF(x, rect.bottom()));
        for (int y = firstY; y <= rect.bottom(); y += spacing)
            painter->drawLine(QPointF(rect.left(), y), QPointF(rect.right(), y));
    }
};

// Visual-only tilemap overlay for the main world canvas. Painting happens in
// world coordinates, and Qt handles zooming/panning with the rest of the scene.
// Draw only the exposed tiles: even a 256x256 map needs no giant preview image.
class GameTilemapOverlay final : public QGraphicsItem
{
public:
    GameTilemapOverlay(const SidboxTilemap *map, const QImage &atlas)
        : m_map(map), m_atlas(atlas), m_baseColours(atlas.colorTable())
    {
        setZValue(2); // Above background references, below movable sprites.
        setAcceptedMouseButtons(Qt::NoButton);
        setFlag(QGraphicsItem::ItemUsesExtendedStyleOption, true);
    }

    void setColourCycle(const SidboxGamePalette::ColourCycle &cycle, int phase, bool preview)
    {
        if (m_atlas.format() != QImage::Format_Indexed8 || m_baseColours.isEmpty()) return;
        m_atlas.setColorTable(preview
            ? SidboxGamePalette::cyclePreview(m_baseColours, cycle, phase)
            : m_baseColours);
        update(); // Repaint visible tiles; never reload atlas files during playback.
    }

    QRectF boundingRect() const override
    {
        if (!m_map) return {};
        return QRectF(0, 0, qreal(m_map->width) * m_map->tileSize,
                      qreal(m_map->height) * m_map->tileSize);
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *) override
    {
        if (!m_map || m_atlas.isNull() || !option) return;
        const int tileSize = m_map->tileSize;
        if (tileSize <= 0 || m_map->graphics.size() < m_map->width * m_map->height * 2)
            return;
        const int cols = m_atlas.width() / tileSize;
        const int rows = m_atlas.height() / tileSize;
        if (cols <= 0 || rows <= 0) return;

        const QRectF visible = option->exposedRect.intersected(boundingRect());
        if (visible.isEmpty()) return;
        const int firstX = qBound(0, qFloor(visible.left() / tileSize), m_map->width);
        const int firstY = qBound(0, qFloor(visible.top() / tileSize), m_map->height);
        const int lastX = qBound(0, qCeil(visible.right() / tileSize), m_map->width);
        const int lastY = qBound(0, qCeil(visible.bottom() / tileSize), m_map->height);
        const int atlasTiles = cols * rows;
        painter->setRenderHint(QPainter::SmoothPixmapTransform, false);
        for (int y = firstY; y < lastY; ++y) {
            for (int x = firstX; x < lastX; ++x) {
                const int offset = (y * m_map->width + x) * 2;
                const auto *bytes = reinterpret_cast<const uchar *>(m_map->graphics.constData());
                const int id = int(bytes[offset]) | (int(bytes[offset + 1]) << 8);
                // Tile 0 is empty. Animated tiles show their first atlas frame
                // here; only the V1 runtime advances them with VBlank.
                if (id <= 0 || id > atlasTiles) continue;
                const int n = id - 1;
                const QImage tileImage = m_atlas.copy((n % cols) * tileSize,
                    (n / cols) * tileSize, tileSize, tileSize);
                const int cell = y * m_map->width + x;
                const quint8 flags = cell < m_map->flips.size() ? quint8(m_map->flips.at(cell)) : 0;
                painter->drawImage(QRectF(x * tileSize, y * tileSize, tileSize, tileSize),
                    (flags & 3) ? tileImage.flipped(Qt::Orientations(static_cast<Qt::Orientation>(flags & 3))) : tileImage);
            }
        }
    }

private:
    const SidboxTilemap *m_map = nullptr;
    QImage m_atlas;
    QVector<QRgb> m_baseColours;
};

// QGraphicsPixmapItem can be dragged in the scene. Notify the document after
// the move; never touch another item's data while rebuilding the scene.
class PlacedImage final : public QGraphicsPixmapItem
{
public:
    std::function<void(QGraphicsItem *)> moved;
    std::function<QPointF(const QPointF &)> snapped;
    explicit PlacedImage(const QPixmap &pixmap)
        : QGraphicsPixmapItem(pixmap)
    {
        setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges);
        setTransformationMode(Qt::FastTransformation); // crisp retro pixels
        setZValue(10);
    }
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override
    {
        if (change == ItemPositionChange && snapped && scene())
            return snapped(value.toPointF());
        const QVariant result = QGraphicsPixmapItem::itemChange(change, value);
        if (change == ItemPositionHasChanged && moved) moved(this);
        return result;
    }
};


// The editor control points are separate from sprites. They affect only the
// saved path geometry; a game sprite moves when run_spline() is called in C.
class SplineHandle final : public QGraphicsEllipseItem
{
public:
    std::function<void(const QPointF &)> moved;
    std::function<QPointF(const QPointF &)> bounded;
    explicit SplineHandle() : QGraphicsEllipseItem(-6, -6, 12, 12)
    {
        setFlags(ItemIsMovable | ItemSendsGeometryChanges);
        setZValue(11000);
        setPen(QPen(QColor(35, 32, 52), 2));
        setBrush(QColor(115, 245, 231));
        setCursor(Qt::SizeAllCursor);
    }
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override
    {
        if (change == ItemPositionChange && bounded && scene())
            return bounded(value.toPointF());
        const QVariant result = QGraphicsEllipseItem::itemChange(change, value);
        if (change == ItemPositionHasChanged && moved) moved(pos());
        return result;
    }
};

// Accept URL drags from the project explorer (and the OS file manager) without
// moving or copying files. Group roots determine the target asset category.
class GameResourceTree final : public QTreeWidget
{
public:
    using QTreeWidget::QTreeWidget;
    std::function<void(const QStringList &, const QString &, const QString &)> filesDropped;
protected:
    void dragEnterEvent(QDragEnterEvent *event) override
    {
        if (event->mimeData()->hasUrls()) event->acceptProposedAction();
        else QTreeWidget::dragEnterEvent(event);
    }
    void dragMoveEvent(QDragMoveEvent *event) override
    {
        if (event->mimeData()->hasUrls()) event->acceptProposedAction();
        else QTreeWidget::dragMoveEvent(event);
    }
    void dropEvent(QDropEvent *event) override
    {
        if (!event->mimeData()->hasUrls()) { QTreeWidget::dropEvent(event); return; }
        QStringList paths;
        for (const QUrl &url : event->mimeData()->urls())
            if (url.isLocalFile() && QFileInfo(url.toLocalFile()).isFile())
                paths.append(QFileInfo(url.toLocalFile()).absoluteFilePath());
        if (paths.isEmpty()) { event->ignore(); return; }
        QTreeWidgetItem *target = itemAt(event->position().toPoint());
        while (target && !target->data(0, Qt::UserRole + 1).isValid())
            target = target->parent();
        const QString kind = target ? target->data(0, Qt::UserRole + 1).toString() : QString();
        const QString plane = target ? target->data(0, Qt::UserRole + 2).toString() : QString();
        // Defer rebuilding: Qt is still using the current tree items during
        // QTreeWidget::dropEvent. Refreshing them synchronously risks a crash.
        const auto callback = filesDropped;
        QTimer::singleShot(0, this, [callback, paths, kind, plane]() {
            if (callback) callback(paths, kind, plane);
        });
        event->setDropAction(Qt::CopyAction); // never move disk files
        event->accept();
    }
};

QString assetKindForFile(const QString &path)
{
    const QString ext = QFileInfo(path).suffix().toLower();
    if (QStringList{QStringLiteral("ppb"),QStringLiteral("png"),QStringLiteral("bmp"),
        QStringLiteral("jpg"),QStringLiteral("jpeg"),QStringLiteral("gif")}.contains(ext))
        return QStringLiteral("sprite");
    if (QStringList{QStringLiteral("pal"),QStringLiteral("act")}.contains(ext))
        return QStringLiteral("palette");
    if (ext == QStringLiteral("wav")) return QStringLiteral("sound");
    if (QStringList{QStringLiteral("mod"),QStringLiteral("med"),QStringLiteral("s3m"),
        QStringLiteral("xm"),QStringLiteral("tfmx"),QStringLiteral("sid"),
        QStringLiteral("sba")}.contains(ext)) return QStringLiteral("music");
    return QString();
}

QString kindTitle(const QString &kind)
{
    if (kind == QStringLiteral("sprite")) return QObject::tr("Sprites");
    if (kind == QStringLiteral("tileatlas")) return QObject::tr("Tile Atlases");
    if (kind == QStringLiteral("background")) return QObject::tr("Backgrounds");
    if (kind == QStringLiteral("palette")) return QObject::tr("Palettes");
    if (kind == QStringLiteral("sound")) return QObject::tr("Sounds");
    return QObject::tr("Music");
}

bool visualKind(const QString &kind)
{
    return kind == QStringLiteral("sprite") || kind == QStringLiteral("background");
}

// Editor-only approximation of SIDBOX's 4x4 patterned BOB fade.
// The firmware's precise threshold pattern is not distributed with the IDE.
// Unlike QPainter opacity, this removes whole pixels, leaving the scene
// behind them visible. Always apply the mask at the final DRAWN resolution
// so zoomed BOBs retain a 4x4 SCREEN-pixel pattern.
/* Exact fade steps are shared conceptually with the generated gameassets code.
 * Sequence visits both endpoints; ping-pong doesn't double-pause at the ends. */
static int bobAnimatedFade(int low, int high, int step, int delay,
                           bool pingpong, qint64 frames)
{
    const int boundedLow = qBound(0, low, 100);
    const int boundedHigh = qBound(0, high, 100);
    low = qMin(boundedLow, boundedHigh);
    high = qMax(boundedLow, boundedHigh);
    step = qBound(1, step, 100);
    delay = qMax(1, delay);
    if (low == high) return low;
    const int steps = (high - low + step - 1) / step;
    const int period = pingpong ? 2 * steps : steps + 1;
    const int phase = int((qMax(qint64(0), frames) / delay) % period);
    const int position = pingpong && phase > steps ? 2 * steps - phase : phase;
    return qMin(high, low + position * step);
}

static QImage patternedBobPreview(const QImage &source, int fadePercent,
                                  int spriteScale, int screenX, int screenY)
{
    if (source.isNull() || fadePercent <= 0) return source;
    const int percent = qBound(0, fadePercent, 100);
    const double factor = qBound(1, spriteScale, 800) / 100.0;
    QImage image = source;
    const int width = qMax(1, qRound(source.width() * factor));
    const int height = qMax(1, qRound(source.height() * factor));
    if (width != source.width() || height != source.height())
        image = source.scaled(width, height, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    image = image.convertToFormat(QImage::Format_ARGB32);
    // Bayer ordering is an approximation pending the actual Core routine.
    static const int pattern[4][4] = {
        { 0, 8, 2, 10 }, { 12, 4, 14, 6 },
        { 3, 11, 1, 9 }, { 15, 7, 13, 5 }
    };
    for (int y = 0; y < image.height(); ++y) {
        QRgb *pixels = reinterpret_cast<QRgb *>(image.scanLine(y));
        for (int x = 0; x < image.width(); ++x) {
            const int rank = pattern[(y + screenY) & 3][(x + screenX) & 3];
            if ((2 * rank + 1) * 100 <= percent * 32) pixels[x] = 0;
        }
    }
    return image;
}

QPixmap paletteSwatches(const QVector<QRgb> &table)
{
    QImage image(128, 128, QImage::Format_RGB32);
    image.fill(QColor(45, 50, 60));
    QPainter painter(&image);
    painter.setPen(Qt::NoPen);
    for (int i = 0; i < qMin(256, table.size()); ++i) {
        const QRgb colour = table.at(i);
        painter.setBrush(QColor(qRed(colour), qGreen(colour), qBlue(colour)));
        painter.drawRect((i % 16) * 8, (i / 16) * 8, 8, 8);
    }
    return QPixmap::fromImage(image);
}

// Forced-CLUT previews leave the original palette and indexed pixel bytes
// untouched. The default RGB-only preview keeps nonzero indices visible even
// when an imported foreground .pal has accidental zero-alpha entries. An
// opt-in ARGB preview reproduces the foreground alpha from the actual CLUT.
// Index 0 remains transparent by convention; background is always opaque.
QVector<QRgb> colourPreviewBank(const QVector<QRgb> &bank, bool foreground, bool previewAlpha)
{
    QVector<QRgb> display = bank;
    for (int i = 0; i < display.size(); ++i) {
        const QRgb colour = display.at(i);
        const int alpha = foreground && i == 0 ? 0
            : foreground && previewAlpha ? qAlpha(colour) : 255;
        display[i] = qRgba(qRed(colour), qGreen(colour), qBlue(colour), alpha);
    }
    return display;
}

bool extraPaletteTransparency(const QVector<QRgb> &bank, bool foreground)
{
    for (int i = foreground ? 1 : 0; i < bank.size(); ++i)
        if (qAlpha(bank.at(i)) != 255) return true;
    return false;
}

QPixmap missingImage(const QString &kind)
{
    QPixmap result(64, 64);
    result.fill(Qt::transparent);
    QPainter p(&result);
    p.fillRect(result.rect(), QColor(55, 62, 82));
    for (int y = 0; y < 64; y += 16)
        for (int x = 0; x < 64; x += 16)
            if ((x / 16 + y / 16) % 2)
                p.fillRect(x, y, 16, 16, QColor(77, 88, 111));
    p.setPen(QPen(QColor(245, 188, 94), 2));
    p.drawRect(1, 1, 61, 61);
    p.setPen(Qt::white);
    p.drawText(result.rect(), Qt::AlignCenter,
               kind == QStringLiteral("background") ? QStringLiteral("BG") : QStringLiteral("SPR"));
    return result;
}
}

// Shared between open Game Designer tabs. Clipboard owns value snapshots, so
// closing the source tab cannot invalidate a pending paste.
SidboxGameDesigner::Resource SidboxGameDesigner::s_copiedWorldObject;
QVector<SidboxGameDesigner::Resource> SidboxGameDesigner::s_copiedWorldResources;
QVector<SidboxGameDesigner::SplinePath> SidboxGameDesigner::s_copiedWorldSplines;
QJsonObject SidboxGameDesigner::s_copiedWorldAdventure;
QString SidboxGameDesigner::s_copiedWorldSource;
bool SidboxGameDesigner::s_hasCopiedWorldObject = false;

SidboxGameDesigner::SidboxGameDesigner(const QString &designFilePath, QWidget *parent)
    : QWidget(parent), m_filePath(QFileInfo(designFilePath).absoluteFilePath())
{
    buildUi();
    if (QFileInfo::exists(m_filePath)) {
        if (!loadDesign()) m_valid = false;
    } else rebuildScene();
    refreshColours();
    // Animate only editor previews; gameplay uses its own 50 Hz VBlank clock.
    m_objectPreviewClock.start();
    m_objectPreviewTimer = new QTimer(this);
    m_objectPreviewTimer->setInterval(20);
    connect(m_objectPreviewTimer, &QTimer::timeout, this, [this]() {
        if (!m_scene || m_loading || !isVisible()) return;
        const qint64 ticks = m_objectPreviewClock.elapsed() / 20;
        if (m_showColourCycles && m_showColourCycles->isChecked()) {
            const auto &front = m_frontColourCycle;
            const auto &back = m_backColourCycle;
            const int frontPhase = front.enabled
                ? int((ticks / qMax(1, front.speed)) % qMax(2, front.length)) : 0;
            const int backPhase = back.enabled
                ? int((ticks / qMax(1, back.speed)) % qMax(2, back.length)) : 0;
            if (frontPhase != m_lastFrontCyclePhase || backPhase != m_lastBackCyclePhase) {
                m_frontCyclePhase = frontPhase;
                m_backCyclePhase = backPhase;
                m_lastFrontCyclePhase = frontPhase;
                m_lastBackCyclePhase = backPhase;
                refreshColourCyclePreview();
            }
        }
        updateParticlePreview();
        updateWeatherPreview();
        for (int i = 0; i < m_resources.size() && i < m_sceneItems.size(); ++i) {
            const Resource &r = m_resources.at(i);
            if (r.kind != QStringLiteral("sprite") ||
                ((!r.objectAnimated || r.animCount <= 1) && !r.objectFadeAnimated))
                continue;
            auto *image = dynamic_cast<QGraphicsPixmapItem *>(m_sceneItems.at(i));
            if (!image) continue;
            const qint64 step = ticks / qMax(1, r.animTicks);
            int frameInClip = 0;
            if (r.animMode == QStringLiteral("once"))
                frameInClip = int(qMin(step, qint64(r.animCount - 1)));
            else if (r.animMode == QStringLiteral("pingpong") && r.animCount > 1) {
                const int cycle = 2 * r.animCount - 2;
                const int phase = int(step % cycle);
                frameInClip = phase < r.animCount ? phase : cycle - phase;
            } else frameInClip = int(step % r.animCount);
            const int index = r.animFirst + frameInClip;
            const int fade = r.objectFadeAnimated
                ? bobAnimatedFade(r.objectFadeLow, r.objectFadeHigh,
                    r.objectFadeStep, r.objectFadeDelay, r.objectFadePingpong, ticks)
                : r.objectAlphaFadePercent;
            if (image->data(1).toInt() == index && image->data(3).toInt() == fade) continue;
            Resource frame = r;
            frame.frame = index;
            const QImage preview = resourcePreview(frame);
            if (!preview.isNull()) {
                image->setPixmap(QPixmap::fromImage(patternedBobPreview(
                    preview, fade, r.scale, r.x, r.y)));
                image->setScale(fade > 0 ? 1.0 : r.scale / 100.0);
                image->setShapeMode(fade > 0
                    ? QGraphicsPixmapItem::BoundingRectShape
                    : QGraphicsPixmapItem::MaskShape);
                image->setData(1, index);
                image->setData(3, fade);
            }
        }
    });
    m_objectPreviewTimer->start();
}

SidboxGameDesigner::~SidboxGameDesigner()
{
    // Qt destroys child QObjects in QWidget::~QWidget(), AFTER this derived
    // destructor has finished. Scene item removal during that teardown emits
    // selectionChanged(), but the resource tree may already be destroyed.
    // Disconnect callbacks into this Designer before either child is deleted.
    // See crash on closing a .sbgm tab: selectionChanged -> syncCanvasSelection
    // -> selectedIndex -> QTreeWidget::currentItem (dangling tree pointer).
    if (m_scene)
        QObject::disconnect(m_scene, nullptr, this, nullptr);
    if (m_resourceTree)
        QObject::disconnect(m_resourceTree, nullptr, this, nullptr);
}

void SidboxGameDesigner::setTheme(const IDETheme &theme)
{
    m_theme = theme;
    // The marquee is painted in world coordinates, with a cosmetic (constant
    // screen-width) border. Update it if a theme changes during a drag.
    if (m_marqueeRect) {
        QPen accentPen(theme.accent, 1);
        accentPen.setCosmetic(true);
        accentPen.setJoinStyle(Qt::MiterJoin);
        m_marqueeRect->setPen(accentPen);
        QColor fill = theme.accent;
        fill.setAlpha(38);
        m_marqueeRect->setBrush(fill);
    }
    // The application-wide IDE palette and stylesheet now colour all normal
    // controls and their popup lists. Keep only world-canvas art local.
    setStyleSheet(QString());
    refreshColours();
    refreshObjectHitbox();
}

QString SidboxGameDesigner::filePath() const { return m_filePath; }
void SidboxGameDesigner::setFilePath(const QString &path)
{
    // Retarget paths if the designer file moves to a different directory.
    // Existing asset references must keep resolving to the SAME physical files.
    QStringList absoluteResources, absoluteAnimations;
    for (const auto &r : m_resources) {
        absoluteResources.append(r.path.isEmpty() ? QString() : resolvedPath(r.path));
        absoluteAnimations.append(r.animationFile.isEmpty() ? QString() : resolvedPath(r.animationFile));
    }
    const QString previousDir = QFileInfo(m_filePath).absolutePath();
    m_filePath = QFileInfo(path).absoluteFilePath();
    for (int i = 0; i < m_resources.size(); ++i) {
        if (!absoluteResources.at(i).isEmpty())
            m_resources[i].path = storedPath(absoluteResources.at(i));
        if (!absoluteAnimations.at(i).isEmpty())
            m_resources[i].animationFile = storedPath(absoluteAnimations.at(i));
    }
    if (QFileInfo(m_filePath).absolutePath() != previousDir) setDirty();
    if (tabTitleChanged) tabTitleChanged();
}
QString SidboxGameDesigner::displayName() const
{
    return QFileInfo(m_filePath).fileName() + (m_dirty ? QStringLiteral(" *") : QString());
}
bool SidboxGameDesigner::isModified() const { return m_dirty; }
bool SidboxGameDesigner::isValid() const { return m_valid; }
void SidboxGameDesigner::setDirty(bool value)
{
    if (m_loading || m_dirty == value) return;
    m_dirty = value;
    if (tabTitleChanged) tabTitleChanged();
}

void SidboxGameDesigner::openPaletteEditor(int resourceIndex)
{
    QString palettePath;
    QString plane = QStringLiteral("foreground");
    if (resourceIndex >= 0 && resourceIndex < m_resources.size()
        && m_resources.at(resourceIndex).kind == QStringLiteral("palette")) {
        const Resource &resource = m_resources.at(resourceIndex);
        plane = resource.plane;
        palettePath = resolvedPath(resource.path);
    }
    SidboxGamePaletteEditor dialog(this);
    dialog.setBank(plane == QStringLiteral("background"));
    dialog.setColourCycles(m_frontColourCycle, m_backColourCycle);
    if (!palettePath.isEmpty() && QFileInfo(palettePath).suffix().compare(
        QStringLiteral("pal"), Qt::CaseInsensitive) == 0) {
        // Respect Cancel (and failed imports) rather than opening an empty editor.
        if (!dialog.loadFromFile(palettePath)) return;
    }
    dialog.exec();
    const auto foreground = dialog.foregroundColourCycle();
    const auto background = dialog.backgroundColourCycle();
    const auto changed = [](const SidboxGamePalette::ColourCycle &a,
                            const SidboxGamePalette::ColourCycle &b) {
        return a.enabled != b.enabled || a.start != b.start || a.length != b.length
               || a.speed != b.speed;
    };
    if (changed(m_frontColourCycle, foreground) || changed(m_backColourCycle, background)) {
        m_frontColourCycle = foreground;
        m_backColourCycle = background;
        m_frontCyclePhase = m_backCyclePhase = 0;
        m_lastFrontCyclePhase = m_lastBackCyclePhase = -1;
        setDirty();
        refreshPlanePreview();
    }
    const QString saved = dialog.savedPath();
    if (saved.isEmpty()) return;
    m_paletteCache.clear();
    refreshPlanePreview();
    if (assetFilesChanged) assetFilesChanged();
    // Editing an existing .pal changes that resource in place. Do not add a duplicate.
    if (!palettePath.isEmpty() && QDir::cleanPath(QFileInfo(saved).absoluteFilePath())
        == QDir::cleanPath(QFileInfo(palettePath).absoluteFilePath())) {
        refreshProperties();
        return;
    }
    if (QMessageBox::question(this, tr("Add Palette Resource"),
        tr("Add the newly saved palette to Game Resources as a %1 palette?\n%2")
            .arg(dialog.currentBankIsBackground() ? tr("Background") : tr("Foreground"), saved),
        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) != QMessageBox::Yes) return;
    Resource r;
    r.name = QFileInfo(saved).completeBaseName();
    r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    r.kind = QStringLiteral("palette");
    r.plane = dialog.currentBankIsBackground() ? QStringLiteral("background")
                                               : QStringLiteral("foreground");
    r.path = storedPath(saved);
    rememberResourceEdit();
    m_resources.append(r);
    refreshResources();
    selectResource(m_resources.size() - 1);
    setDirty();
    if (assetFilesChanged) assetFilesChanged();
}

QString SidboxGameDesigner::helperTemplatesRoot() const
{
    // Look alongside the executable first, just like the IDE SDK lookup.
    const QDir app(QCoreApplication::applicationDirPath());
    QStringList candidates;
    if (qEnvironmentVariableIsSet("SIDBOX_SDK"))
        candidates << qEnvironmentVariable("SIDBOX_SDK");
    candidates << app.filePath(QStringLiteral("idelibs"))
               << app.filePath(QStringLiteral("../idelibs"))
               << app.filePath(QStringLiteral("../../idelibs"))
               << app.filePath(QStringLiteral("../SidboxIDE/idelibs"))
               << QDir::current().filePath(QStringLiteral("idelibs"))
               << QDir::current().filePath(QStringLiteral("SidboxIDE/idelibs"));
    for (const QString &candidate : candidates) {
        const QString path = QDir(candidate).filePath(QStringLiteral("codehelpers"));
        if (QFileInfo(path).isDir()) return QFileInfo(path).absoluteFilePath();
    }
    return QString();
}

void SidboxGameDesigner::addCodeHelper(const QString &category, const QString &base)
{
    if ((category != QStringLiteral("game") && category != QStringLiteral("gui"))
        || base.isEmpty() || base.contains(QLatin1Char('/')) || base.contains(QLatin1Char('\\'))
        || base == QStringLiteral(".") || base == QStringLiteral("..")
        || (category == QStringLiteral("game") && (base == QStringLiteral("gameadventure")
            || base == QStringLiteral("gameassets") || base == QStringLiteral("gameworlditems")
            || base == QStringLiteral("gameadventureempty")
            || base == QStringLiteral("maingame") || base == QStringLiteral("splinepaths")
            || base == QStringLiteral("level1") || base == QStringLiteral("worldmap")
            || base == QStringLiteral("embeddedresource") || base == QStringLiteral("gameplayer") || base == QStringLiteral("gameworlds")))) return;
    const QDir templateFolder(QDir(helperTemplatesRoot()).filePath(category));
    const QString sourceH = category == QStringLiteral("game")
        ? GameHelperTemplates::sourcePath(templateFolder, base, QStringLiteral(".h"))
        : templateFolder.filePath(base + QStringLiteral(".h"));
    const QString sourceC = category == QStringLiteral("game")
        ? GameHelperTemplates::sourcePath(templateFolder, base, QStringLiteral(".c"))
        : templateFolder.filePath(base + QStringLiteral(".c"));
    QFile hTemplate(sourceH), cTemplate(sourceC);
    if (!hTemplate.open(QIODevice::ReadOnly) || !cTemplate.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Add Helper Code"),
            tr("Cannot read helper template files:\n%1\n%2").arg(sourceH, sourceC));
        return;
    }
    QByteArray header = hTemplate.readAll(), source = cTemplate.readAll();
    // All Game helper entry points must render @IDE fields before installing.
    // GUI helpers are intentionally NOT migrated in Stage 4.42.
    if (category == QStringLiteral("game")) {
        QByteArray renderedH, renderedC;
        QString renderError;
        if (!GameHelperTemplates::render(header, base, QStringLiteral(".h"), m_adventure,
                                         &renderedH, &renderError)
            || !GameHelperTemplates::render(source, base, QStringLiteral(".c"), m_adventure,
                                             &renderedC, &renderError)) {
            QMessageBox::warning(this, tr("Add Helper Code"), renderError);
            return;
        }
        header = renderedH;
        source = renderedC;
    }
    // Installed game helper names retain the existing game-prefix convention.
    const QString installedBase = category + base;
    source.replace((QStringLiteral("\"%1.h\"").arg(base)).toUtf8(),
                   (QStringLiteral("\"%1.h\"").arg(installedBase)).toUtf8());
    const QString folder = QDir(QFileInfo(m_filePath).absolutePath()).filePath(QStringLiteral("gamehelpers"));
    const QString hPath = QDir(folder).filePath(installedBase + QStringLiteral(".h"));
    const QString cPath = QDir(folder).filePath(installedBase + QStringLiteral(".c"));
    const bool headerExists = QFileInfo::exists(hPath);
    const bool sourceExists = QFileInfo::exists(cPath);
    bool keepExistingCode = false;
    if (headerExists || sourceExists) {
        const auto answer = QMessageBox::question(this, tr("Helper Already Installed"),
            tr("This game's helper files already exist:\n%1\n%2\n\n"
               "Yes: Replace the C and H files with the current templates.\n"
               "No: Keep existing code and add any missing beginner guide "
               "(or missing C/H files).\n"
               "Cancel: Do nothing.")
                .arg(hPath, cPath),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
            QMessageBox::No);
        if (answer == QMessageBox::Cancel || answer == QMessageBox::NoButton) return;
        keepExistingCode = (answer == QMessageBox::No);
    }
    if (!QDir().mkpath(folder)) {
        QMessageBox::warning(this, tr("Add Helper Code"), tr("Cannot create directory:\n%1").arg(folder));
        return;
    }
    const bool writeHeader = !keepExistingCode || !headerExists;
    const bool writeSource = !keepExistingCode || !sourceExists;
    if (writeHeader) {
        QSaveFile file(hPath);
        if (!file.open(QIODevice::WriteOnly)
            || file.write(header) != header.size() || !file.commit()) {
            file.cancelWriting();
            QMessageBox::warning(this, tr("Add Helper Code"),
                tr("Cannot save helper header:\n%1").arg(hPath));
            return;
        }
    }
    if (writeSource) {
        QSaveFile file(cPath);
        if (!file.open(QIODevice::WriteOnly)
            || file.write(source) != source.size() || !file.commit()) {
            file.cancelWriting();
            QMessageBox::warning(this, tr("Add Helper Code"),
                tr("Cannot save helper source:\n%1").arg(cPath));
            return;
        }
    }
    // A helper can optionally carry a plain-text beginner guide. The Project
    // Tree already displays *.txt and opens them in the source editor.
    // Never overwrite a guide that the programmer has personalised.
    bool addedGuide = false;
    bool keptGuide = false;
    const QString guideSource = templateFolder.filePath(base + QStringLiteral(".txt"));
    const QString guidePath = QDir(folder).filePath(installedBase + QStringLiteral(".txt"));
    if (QFileInfo(guideSource).isFile()) {
        if (QFileInfo::exists(guidePath)) {
            keptGuide = true;
        } else {
            QFile guideTemplate(guideSource);
            if (!guideTemplate.open(QIODevice::ReadOnly)) {
                QMessageBox::warning(this, tr("Add Helper Code"),
                    tr("Helper installed, but cannot read guide:\n%1").arg(guideSource));
            } else {
                const QByteArray guide = guideTemplate.readAll();
                QSaveFile guideFile(guidePath);
                if (!guideFile.open(QIODevice::WriteOnly)
                    || guideFile.write(guide) != guide.size()
                    || !guideFile.commit()) {
                    guideFile.cancelWriting();
                    QMessageBox::warning(this, tr("Add Helper Code"),
                        tr("Helper installed, but cannot save guide:\n%1").arg(guidePath));
                } else {
                    addedGuide = true;
                }
            }
        }
    }
    if (assetFilesChanged) assetFilesChanged();
    QString message = keepExistingCode
        ? tr("Existing helper code preserved.\n"
             "Any missing C/H files and beginner guide were installed.")
        : tr("Installed gamehelpers/%1.h and %1.c.\n\n"
             "Include \"gamehelpers/%1.h\" in your main.c.\n"
             "Gameassets generation will not overwrite this code.").arg(installedBase);
    // Every helper can supply its own beginner instructions, without hardcoding
    // helper names or recompiling the IDE. The .ini file is optional.
    QSettings helperInfo(templateFolder.filePath(base + QStringLiteral(".ini")),
                         QSettings::IniFormat);
    const QString afterInstall = helperInfo.value(QStringLiteral("Helper/after_install"))
                                     .toString().trimmed();
    if (addedGuide) message += tr("\n\nBeginner guide: gamehelpers/%1.txt (double-click in Project Tree).")
                                  .arg(installedBase);
    else if (keptGuide) message += tr("\n\nYour existing guide gamehelpers/%1.txt was preserved.")
                                      .arg(installedBase);
    if (!afterInstall.isEmpty()) message += QStringLiteral("\n\n") + afterInstall;
    QMessageBox::information(this, tr("Helper Code Added"), message);
}

void SidboxGameDesigner::updateSplineCurve()
{
    if (!m_splineCurveItem) return;
    QPainterPath curve;
    if (m_activeSpline < 0 || m_activeSpline >= m_splinePaths.size()) {
        m_splineCurveItem->setPath(curve);
        return;
    }
    const SplinePath &spline = m_splinePaths.at(m_activeSpline);
    const int n = spline.points.size();
    if (n < 2) { m_splineCurveItem->setPath(curve); return; }
    curve.moveTo(spline.points.at(0));
    const int segments = spline.loop ? n : n - 1;
    // Preview uses the same Catmull-Rom curve that the V1 helper follows.
    for (int i = 0; i < segments; ++i) {
        const QPointF p0 = spline.points.at(i == 0 ? (spline.loop ? n - 1 : 0) : i - 1);
        const QPointF p1 = spline.points.at(i);
        const QPointF p2 = spline.points.at((i + 1) % n);
        const QPointF p3 = spline.points.at(i + 2 < n ? i + 2 :
            (spline.loop ? (i + 2) % n : n - 1));
        curve.cubicTo(p1 + (p2 - p0) / 6.0, p2 - (p3 - p1) / 6.0, p2);
    }
    m_splineCurveItem->setPath(curve);
}

void SidboxGameDesigner::rebuildSplineOverlay()
{
    if (!m_scene) return;
    for (QGraphicsItem *item : m_splineHandleItems) {
        m_scene->removeItem(item);
        delete item;
    }
    m_splineHandleItems.clear();
    if (m_splineCurveItem) {
        m_scene->removeItem(m_splineCurveItem);
        delete m_splineCurveItem;
    }
    m_splineCurveItem = new QGraphicsPathItem;
    m_splineCurveItem->setZValue(10050);
    m_splineCurveItem->setPen(QPen(QColor(105, 245, 225), 2.5));
    m_splineCurveItem->setBrush(Qt::NoBrush);
    m_splineCurveItem->setAcceptedMouseButtons(Qt::NoButton);
    m_scene->addItem(m_splineCurveItem);
    updateSplineCurve();
    if (m_activeSpline < 0 || m_activeSpline >= m_splinePaths.size()) return;
    const auto &path = m_splinePaths.at(m_activeSpline);
    for (int i = 0; i < path.points.size(); ++i) {
        auto *node = new SplineHandle;
        node->setData(1, m_activeSpline);
        node->setData(2, i);
        node->bounded = [this](const QPointF &p) {
            const int step = m_snap->isChecked()
                ? m_snapStep->currentText().section(QLatin1Char(' '), 0, 0).toInt() : 0;
            const qreal x = step > 0 ? qRound(p.x() / step) * step : qRound(p.x());
            const qreal y = step > 0 ? qRound(p.y() / step) * step : qRound(p.y());
            return QPointF(qBound(0.0, x, (qreal)m_worldWidth->value()),
                           qBound(0.0, y, (qreal)m_worldHeight->value()));
        };
        node->setPos(path.points.at(i));
        node->moved = [this, i](const QPointF &point) {
            if (m_loading || m_activeSpline < 0 || m_activeSpline >= m_splinePaths.size()) return;
            auto &points = m_splinePaths[m_activeSpline].points;
            if (i >= points.size()) return;
            const QPoint newPoint(qRound(point.x()), qRound(point.y()));
            if (points.at(i) == newPoint) return;
            points[i] = newPoint;
            updateSplineCurve();
            setDirty();
        };
        node->setToolTip(tr("Spline point %1 - drag to move; right-click to insert or delete points")
                         .arg(i + 1));
        m_scene->addItem(node);
        auto *label = new QGraphicsSimpleTextItem(QString::number(i + 1), node);
        label->setBrush(QColor(255, 238, 125));
        label->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
        label->setPos(9, -13);
        label->setAcceptedMouseButtons(Qt::NoButton);
        m_splineHandleItems.append(node);
    }
}

void SidboxGameDesigner::rebuildTilemapOverlay()
{
    if (!m_scene) return;
    if (m_tilemapOverlayItem) {
        delete m_tilemapOverlayItem;
        m_tilemapOverlayItem = nullptr;
    }
    for (QGraphicsItem *item : m_loopOverlayItems) delete item;
    m_loopOverlayItems.clear();
    if (m_showTilemap) {
        m_showTilemap->setEnabled(m_tilemapEnabled);
        if (!m_tilemapEnabled || !m_showTilemap->isChecked()) return;
    } else return;

    // Loop tracks are level geometry, not atlas tiles. Display the outline
    // in the main file/world editor as a noninteractive placement guide.
    // Their circles stay behind draggable Game Objects (Z=10).
    for (int i = 0; i < m_tilemap.loops.size(); ++i) {
        const SidboxLoopTrack &loop = m_tilemap.loops.at(i);
        if (loop.radius <= 0) continue;
        const QRectF circle(loop.centerX - loop.radius, loop.centerY - loop.radius,
                            loop.radius * 2, loop.radius * 2);
        QPen edge(QColor(117, 138, 255, 220), 2, Qt::DashLine);
        edge.setCosmetic(true);
        auto *ring = m_scene->addEllipse(circle, edge, Qt::NoBrush);
        ring->setZValue(3);
        ring->setAcceptedMouseButtons(Qt::NoButton);
        m_loopOverlayItems.append(ring);
        auto *caption = new QGraphicsSimpleTextItem(tr("LOOP %1").arg(i + 1), ring);
        caption->setBrush(QColor(255, 206, 67));
        caption->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
        caption->setAcceptedMouseButtons(Qt::NoButton);
        caption->setPos(loop.centerX + 8, loop.centerY + loop.radius - 20);
        auto *entry = new QGraphicsEllipseItem(-4, -4, 8, 8, ring);
        entry->setPos(loop.centerX, loop.centerY + loop.radius);
        entry->setPen(QPen(QColor(255, 206, 67), 2));
        entry->setBrush(QColor(255, 206, 67));
        entry->setAcceptedMouseButtons(Qt::NoButton);
    }
    if (m_tilemap.atlasPath.isEmpty()) return;
    const QString atlasPath = QDir(QFileInfo(m_filePath).absolutePath())
                                  .absoluteFilePath(m_tilemap.atlasPath);
    SidboxPpb::Picture picture;
    if (!SidboxPpb::read(atlasPath, &picture)) return;
    QImage atlas = picture.indexed;
    if (m_forcePalette && m_forcePalette->isChecked()) {
        const QVector<QRgb> palette = activePalette(QStringLiteral("foreground"));
        if (palette.size() == 256)
            atlas.setColorTable(colourPreviewBank(palette, true, m_previewPaletteAlpha && m_previewPaletteAlpha->isChecked()));
    }
    // Foreground palette index 0 is transparent on SIDBOX. Do this only
    // for the preview; the PPB file and palette assets are never modified.
    QVector<QRgb> displayPalette = atlas.colorTable();
    if (!displayPalette.isEmpty()) {
        const QRgb zero = displayPalette.at(0);
        displayPalette[0] = qRgba(qRed(zero), qGreen(zero), qBlue(zero), 0);
        atlas.setColorTable(displayPalette);
    }
    auto *overlay = new GameTilemapOverlay(&m_tilemap, atlas);
    m_tilemapOverlayItem = overlay;
    m_scene->addItem(overlay);
    overlay->setColourCycle(m_frontColourCycle, m_frontCyclePhase,
                            m_showColourCycles && m_showColourCycles->isChecked()
                            && m_frontColourCycle.enabled);
}

void SidboxGameDesigner::openPlayerAnimationEditor(int resourceIndex)
{
    int index = resourceIndex >= 0 ? resourceIndex : selectedIndex();
    if (index < 0 || index >= m_resources.size() ||
        m_resources.at(index).kind != QStringLiteral("sprite")) {
        QMessageBox::information(this, tr("Sprite Animations"),
            tr("Select a Sprite under Game Resources first.\n\n"
               "Animation states belong to the selected Sprite atlas."));
        return;
    }
    const Resource &resource = m_resources.at(index);
    const QString atlas = resolvedPath(resource.path);
    if (!QFileInfo::exists(atlas)) {
        QMessageBox::warning(this, tr("Sprite Animations"),
            tr("The selected Sprite needs an existing PPB or PNG atlas.\n%1").arg(atlas));
        return;
    }
    QString animationFile = resource.animationFile;
    if (animationFile.isEmpty()) {
        // Stable by resource ID; renaming an asset never loses its animation.
        animationFile = QStringLiteral("gameanimations/%1.sbanim").arg(resource.id);
    }
    const QString absoluteAnimationFile = resolvedPath(animationFile);
    // The generated main.c includes gameanimations/player_anim.h for the
    // sprite named "player". Never overwrite that player header when editing
    // animations belonging to a different Sprite resource.
    const QString headerFile = resolvedPath(
        resource.name.trimmed().compare(QStringLiteral("player"), Qt::CaseInsensitive) == 0
            ? QStringLiteral("gameanimations/player_anim.h")
            : QStringLiteral("gameanimations/%1_anim.h").arg(resource.id));
    SidboxPlayerAnimationEditor editor(atlas, absoluteAnimationFile, headerFile,
        resource.cellWidth > 0 ? resource.cellWidth : 32,
        resource.cellHeight > 0 ? resource.cellHeight : 32, this, m_theme);
    if (!editor.isUsable()) return;
    if (editor.exec() != QDialog::Accepted) return;
    // The atlas is never converted or modified by this editor. Store only
    // the relative animation definition path in the .sbgm design document.
    m_resources[index].animationFile = storedPath(editor.animationFile());
    // The BOB's atlas-cell geometry MUST match the saved animation grid;
    // otherwise gfxbob_t.index would select the wrong image on hardware.
    const bool resizedCells = m_resources[index].cellWidth != editor.cellWidth()
                           || m_resources[index].cellHeight != editor.cellHeight();
    m_resources[index].cellWidth = editor.cellWidth();
    m_resources[index].cellHeight = editor.cellHeight();
    if (resizedCells) {
        rebuildScene();
        refreshResources();
        selectResource(index);
    }
    setDirty();
    if (assetFilesChanged) assetFilesChanged();
}


// Stage 5.3: ONE project player profile, with the existing animation editor
// kept intact. The .sbpi is design metadata, never rewritten from a world.
void SidboxGameDesigner::openPlayerEditor()
{
    const QDir project(QFileInfo(m_filePath).absolutePath());
    QJsonObject profile = GamePlayerProfile::defaults();
    const bool hasProfile = QFileInfo::exists(GamePlayerProfile::profilePath(project));
    if (hasProfile) {
        QString error;
        if (!GamePlayerProfile::read(project, &profile, &error)) {
            QMessageBox::warning(this, tr("Create / Edit Player"), error); return;
        }
    } else {
        // Non-destructive migration: borrow the existing 'player' sprite's
        // atlas geometry and animation sidecar. Do NOT remove that resource.
        for (const Resource &r : m_resources) {
            if (r.kind == QStringLiteral("sprite")
                && r.name.compare(QStringLiteral("player"), Qt::CaseInsensitive) == 0) {
                profile.insert(QStringLiteral("atlasPath"), r.path);
                profile.insert(QStringLiteral("animationFile"), r.animationFile.isEmpty()
                    ? QStringLiteral("gameanimations/player_anim.sbanim") : r.animationFile);
                if (r.cellWidth > 0) profile.insert(QStringLiteral("cellWidth"), r.cellWidth);
                if (r.cellHeight > 0) profile.insert(QStringLiteral("cellHeight"), r.cellHeight);
                m_playerStartX = r.x; m_playerStartY = r.y;
                break;
            }
        }
    }
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Create / Edit Player — Shared Across All Worlds"));
    dialog.setMinimumWidth(760);
    dialog.setMinimumHeight(560);
    dialog.setStyleSheet(QStringLiteral("QDialog, QWidget, QPushButton, QLineEdit, QSpinBox, QTabWidget, QTabBar, QPlainTextEdit, QTableWidget, QListWidget, QComboBox, QHeaderView { border-radius: 0px; }"));
    auto *layout = new QVBoxLayout(&dialog);
    auto *tabs = new QTabWidget(&dialog); layout->addWidget(tabs);
    auto *appearance = new QWidget(tabs); auto *af = new QFormLayout(appearance);
    auto *atlas = new QLineEdit(profile.value(QStringLiteral("atlasPath")).toString(), appearance);
    auto *browse = new QPushButton(tr("Browse PPB..."), appearance);
    af->addRow(tr("Sprite atlas (project-relative)"), atlas);
    af->addRow(browse);
    connect(browse, &QPushButton::clicked, &dialog, [&,this] {
        const QString path=QFileDialog::getOpenFileName(&dialog, tr("Player PPB"), project.absolutePath(), tr("SIDBOX PPB (*.ppb)"));
        if (!path.isEmpty()) atlas->setText(project.relativeFilePath(path));
    });
    auto *anim = new QLineEdit(profile.value(QStringLiteral("animationFile")).toString(), appearance);
    if (anim->text().trimmed().isEmpty())
        anim->setText(QStringLiteral("gameanimations/player_anim.sbanim"));
    af->addRow(tr("Animation definition (.sbanim)"), anim);
    auto *browseAnim = new QPushButton(tr("Choose Existing .sbanim..."), appearance);
    af->addRow(browseAnim);
    connect(browseAnim, &QPushButton::clicked, &dialog, [&,this] {
        const QString path = QFileDialog::getOpenFileName(&dialog, tr("Player Animations"),
            project.absolutePath(), tr("SIDBOX Player Animations (*.sbanim)"));
        if (!path.isEmpty()) anim->setText(project.relativeFilePath(path));
    });
    auto *cw=new QSpinBox(appearance), *ch=new QSpinBox(appearance);
    for (QSpinBox *spin : {cw,ch}) spin->setRange(1,2048);
    cw->setValue(profile.value(QStringLiteral("cellWidth")).toInt(32));
    ch->setValue(profile.value(QStringLiteral("cellHeight")).toInt(32));
    af->addRow(tr("Atlas cell width"),cw); af->addRow(tr("Atlas cell height"),ch);
    auto *editAnim = new QPushButton(tr("Create / Edit Animations..."), appearance);
    af->addRow(editAnim);
    auto *animNote = new QLabel(tr("Animations belong to this shared player, not a world Sprite. "
        "When saving animations, choose Yes to generate gameanimations/player_anim.h "
        "for your game's C code."), appearance);
    animNote->setWordWrap(true);
    af->addRow(animNote);
    connect(editAnim, &QPushButton::clicked, &dialog, [&,this] {
        const QFileInfo art(project.filePath(atlas->text().trimmed()));
        if (!art.isFile() || art.suffix().compare(QStringLiteral("ppb"),Qt::CaseInsensitive)
            || !art.absoluteFilePath().startsWith(project.absolutePath()+QLatin1Char('/'))) {
            QMessageBox::warning(&dialog, tr("Player Animations"),
                tr("Choose an existing PPB inside this game project first."));
            return;
        }
        QString relativeAnimation = QDir::cleanPath(anim->text().trimmed());
        if (relativeAnimation == QStringLiteral(".") || relativeAnimation.isEmpty())
            relativeAnimation = QStringLiteral("gameanimations/player_anim.sbanim");
        const QFileInfo animationPath(project.filePath(relativeAnimation));
        if (animationPath.suffix().compare(QStringLiteral("sbanim"), Qt::CaseInsensitive)
            || !animationPath.absoluteFilePath().startsWith(project.absolutePath()+QLatin1Char('/'))) {
            QMessageBox::warning(&dialog, tr("Player Animations"),
                tr("The .sbanim definition must be stored inside this game project."));
            return;
        }
        SidboxPlayerAnimationEditor editor(art.absoluteFilePath(),
            animationPath.absoluteFilePath(),
            project.filePath(QStringLiteral("gameanimations/player_anim.h")),
            cw->value(), ch->value(), &dialog, m_theme);
        if (!editor.isUsable() || editor.exec()!=QDialog::Accepted) return;
        anim->setText(project.relativeFilePath(editor.animationFile()));
        cw->setValue(editor.cellWidth());
        ch->setValue(editor.cellHeight());
    });
    tabs->addTab(appearance,tr("Appearance & Animations"));
    auto *hitboxPage=new QWidget(tabs);auto *hf=new QFormLayout(hitboxPage);
    auto *customHitbox=new QCheckBox(tr("Override animation hitbox"),hitboxPage);
    customHitbox->setChecked(profile.value(QStringLiteral("customHitbox")).toBool());hf->addRow(customHitbox);
    auto *hx=new QSpinBox(hitboxPage),*hy=new QSpinBox(hitboxPage);
    auto *hw=new QSpinBox(hitboxPage),*hh=new QSpinBox(hitboxPage);
    for(QSpinBox *spin:{hx,hy})spin->setRange(-1024,1024);
    for(QSpinBox *spin:{hw,hh})spin->setRange(1,2048);
    hx->setValue(profile.value(QStringLiteral("hitboxX")).toInt());
    hy->setValue(profile.value(QStringLiteral("hitboxY")).toInt());
    hw->setValue(profile.value(QStringLiteral("hitboxW")).toInt(32));
    hh->setValue(profile.value(QStringLiteral("hitboxH")).toInt(32));
    hf->addRow(tr("Offset X"),hx);hf->addRow(tr("Offset Y"),hy);
    hf->addRow(tr("Width"),hw);hf->addRow(tr("Height"),hh);
    tabs->addTab(hitboxPage,tr("Hitbox"));
    // Stage 5.18: Shared, editable physics bank. Runtime modes retain their
    // existing collision/ICE/jetpack behaviour; numbers are per-profile.
    auto *movement = new QWidget(tabs);
    auto *physicsPage = new QVBoxLayout(movement);
    auto *startPhysicsRow = new QFormLayout();
    auto *preset = new QComboBox(movement);
    startPhysicsRow->addRow(tr("Default physics (unassigned worlds)"), preset);
    auto *worldPicker = new QComboBox(movement);
    auto *worldStartProfile = new QComboBox(movement);
    for (const QFileInfo &worldFile : project.entryInfoList(
             {QStringLiteral("*.sbgm")}, QDir::Files, QDir::Name)) {
        const QString worldName = sidboxTilemapWorldBaseName(worldFile.absoluteFilePath());
        if (worldPicker->findData(worldName) < 0)
            worldPicker->addItem(worldName, worldName);
    }
    startPhysicsRow->addRow(tr("World"), worldPicker);
    startPhysicsRow->addRow(tr("Starting physics for this world"), worldStartProfile);
    physicsPage->addLayout(startPhysicsRow);
    auto *physicsColumns = new QHBoxLayout();
    physicsPage->addLayout(physicsColumns);
    auto *physicsLeft = new QVBoxLayout();
    physicsColumns->addLayout(physicsLeft, 1);
    auto *physicsList = new QListWidget(movement);
    physicsList->setMinimumWidth(165);
    physicsLeft->addWidget(physicsList);
    auto *physicsButtons = new QHBoxLayout();
    physicsLeft->addLayout(physicsButtons);
    auto *addPhysics = new QPushButton(tr("Add"), movement);
    auto *removePhysics = new QPushButton(tr("Remove"), movement);
    physicsButtons->addWidget(addPhysics); physicsButtons->addWidget(removePhysics);
    auto *physicsForm = new QFormLayout();
    physicsColumns->addLayout(physicsForm, 2);
    auto *physicsIdLabel = new QLabel(movement);
    physicsForm->addRow(tr("Profile ID (for C code)"), physicsIdLabel);
    auto *physicsName = new QLineEdit(movement);
    physicsName->setMaxLength(64);
    physicsForm->addRow(tr("Name"), physicsName);
    auto *physicsMode = new QComboBox(movement);
    const QStringList modeLabels = {tr("Normal"), tr("Ice (sliding)"), tr("Water"),
        tr("Slow"), tr("Space"), tr("Floating"), tr("Jetpack")};
    for (int i = 0; i < modeLabels.size(); ++i)
        physicsMode->addItem(modeLabels.at(i), i);
    physicsForm->addRow(tr("Movement behaviour"), physicsMode);
    auto *physicsWalk = new QSpinBox(movement);
    physicsWalk->setRange(0, 16); physicsWalk->setSuffix(tr(" px/frame"));
    auto *physicsJump = new QSpinBox(movement);
    physicsJump->setRange(0, 32); physicsJump->setSuffix(tr(" px/frame"));
    auto *physicsGravity = new QSpinBox(movement);
    physicsGravity->setRange(0, 1000); physicsGravity->setSuffix(tr(" /100 px/frame²"));
    auto *physicsFall = new QSpinBox(movement);
    physicsFall->setRange(1, 32); physicsFall->setSuffix(tr(" px/frame"));
    auto *physicsDrag = new QSpinBox(movement);
    physicsDrag->setRange(0, 100); physicsDrag->setSuffix(QStringLiteral("%"));
    physicsForm->addRow(tr("Walk speed"), physicsWalk);
    physicsForm->addRow(tr("Jump speed"), physicsJump);
    physicsForm->addRow(tr("Gravity"), physicsGravity);
    physicsForm->addRow(tr("Maximum falling speed"), physicsFall);
    physicsForm->addRow(tr("External momentum drag"), physicsDrag);
    auto *physicsNotice = new QLabel(tr("These profiles belong to the shared player. "
        "Choose a default starting profile and optionally override it for each world. "
        "The world manager applies the selected profile on entry; "
        "gameplayer_apply_physics(player, profileID) can still change physics in custom zones. "
        "ICE sliding and JETPACK thrust follow the selected behaviour mode."), movement);
    physicsNotice->setWordWrap(true);
    physicsPage->addWidget(physicsNotice);
    QJsonArray physicsDefs = GamePlayerProfile::physicsProfiles(profile);
    int currentPhysicsId = GamePlayerProfile::startingPhysicsId(profile);
    QJsonObject worldPhysics = GamePlayerProfile::worldPhysicsOverrides(profile);
    const auto refreshWorldPhysicsChoices = [&] {
        QSignalBlocker blocker(worldStartProfile);
        worldStartProfile->clear();
        worldStartProfile->addItem(tr("Use default physics"), -1);
        for (const QJsonValue &value : physicsDefs) {
            const QJsonObject entry = value.toObject();
            worldStartProfile->addItem(entry.value(QStringLiteral("name")).toString(),
                                       entry.value(QStringLiteral("id")).toInt());
        }
        const QString name = worldPicker->currentData().toString();
        const bool hasWorld = !name.isEmpty();
        worldStartProfile->setEnabled(hasWorld);
        if (!hasWorld) return;
        const int id = worldPhysics.value(name).toInt(-1);
        const int index = worldStartProfile->findData(id);
        // An obsolete ID is treated as inherited, never remapped to a different profile.
        if (id >= 0 && index < 0) worldPhysics.remove(name);
        worldStartProfile->setCurrentIndex(qMax(0, index));
    };
    connect(worldPicker, QOverload<int>::of(&QComboBox::currentIndexChanged),
            &dialog, [&](int) { refreshWorldPhysicsChoices(); });
    connect(worldStartProfile, QOverload<int>::of(&QComboBox::currentIndexChanged),
            &dialog, [&](int index) {
        const QString name = worldPicker->currentData().toString();
        if (name.isEmpty() || index < 0) return;
        const int id = worldStartProfile->itemData(index).toInt();
        if (id < 0) worldPhysics.remove(name);
        else worldPhysics.insert(name, id);
    });
    const auto refreshPhysicsChoices = [&] {
        // Removing a global profile must also clear ALL world references to
        // its stable ID, including worlds not currently selected in the UI.
        QSet<int> availableIds;
        for (const QJsonValue &value : physicsDefs)
            availableIds.insert(value.toObject().value(QStringLiteral("id")).toInt(-1));
        for (auto it = worldPhysics.begin(); it != worldPhysics.end();) {
            if (!availableIds.contains(it.value().toInt(-1)))
                it = worldPhysics.erase(it);
            else ++it;
        }
        QSignalBlocker blocker(preset);
        preset->clear();
        for (const QJsonValue &value : physicsDefs) {
            const QJsonObject item = value.toObject();
            preset->addItem(item.value(QStringLiteral("name")).toString(),
                            item.value(QStringLiteral("id")).toInt());
        }
        int selected = preset->findData(currentPhysicsId);
        if (selected < 0 && preset->count()) {
            selected = 0;
            currentPhysicsId = preset->itemData(0).toInt();
        }
        preset->setCurrentIndex(selected);
        refreshWorldPhysicsChoices();
    };
    const auto showPhysics = [&] {
        const int row = physicsList->currentRow();
        const bool valid = row >= 0 && row < physicsDefs.size();
        for (QWidget *control : {static_cast<QWidget*>(physicsName), static_cast<QWidget*>(physicsMode),
                                  static_cast<QWidget*>(physicsWalk), static_cast<QWidget*>(physicsJump),
                                  static_cast<QWidget*>(physicsGravity), static_cast<QWidget*>(physicsFall),
                                  static_cast<QWidget*>(physicsDrag)})
            control->setEnabled(valid);
        removePhysics->setEnabled(valid && physicsDefs.size() > 1);
        if (!valid) return;
        const QJsonObject item = physicsDefs.at(row).toObject();
        physicsIdLabel->setText(QString::number(item.value(QStringLiteral("id")).toInt()));
        const QSignalBlocker bn(physicsName), bm(physicsMode), bw(physicsWalk),
            bj(physicsJump), bg(physicsGravity), bf(physicsFall), bd(physicsDrag);
        physicsName->setText(item.value(QStringLiteral("name")).toString());
        physicsMode->setCurrentIndex(physicsMode->findData(item.value(QStringLiteral("mode")).toInt()));
        physicsWalk->setValue(item.value(QStringLiteral("walkSpeed")).toInt());
        physicsJump->setValue(item.value(QStringLiteral("jumpSpeed")).toInt());
        physicsGravity->setValue(item.value(QStringLiteral("gravity")).toInt());
        physicsFall->setValue(item.value(QStringLiteral("maxFallSpeed")).toInt(1));
        physicsDrag->setValue(item.value(QStringLiteral("forceDrag")).toInt());
    };
    const auto storePhysics = [&] {
        const int row = physicsList->currentRow();
        if (row < 0 || row >= physicsDefs.size()) return;
        QJsonObject item = physicsDefs.at(row).toObject();
        item.insert(QStringLiteral("name"), physicsName->text());
        item.insert(QStringLiteral("mode"), physicsMode->currentData().toInt());
        item.insert(QStringLiteral("walkSpeed"), physicsWalk->value());
        item.insert(QStringLiteral("jumpSpeed"), physicsJump->value());
        item.insert(QStringLiteral("gravity"), physicsGravity->value());
        item.insert(QStringLiteral("maxFallSpeed"), physicsFall->value());
        item.insert(QStringLiteral("forceDrag"), physicsDrag->value());
        physicsDefs.replace(row, item);
        physicsList->item(row)->setText(physicsName->text());
        refreshPhysicsChoices();
    };
    connect(physicsList, &QListWidget::currentRowChanged, &dialog,
        [&](int) { showPhysics(); });
    connect(preset, QOverload<int>::of(&QComboBox::currentIndexChanged), &dialog,
        [&](int index) { if (index >= 0) currentPhysicsId = preset->itemData(index).toInt(); });
    connect(physicsName, &QLineEdit::textChanged, &dialog, [&](const QString &) { storePhysics(); });
    connect(physicsMode, QOverload<int>::of(&QComboBox::currentIndexChanged), &dialog,
        [&](int) { storePhysics(); });
    for (QSpinBox *spin : {physicsWalk,physicsJump,physicsGravity,physicsFall,physicsDrag})
        connect(spin, QOverload<int>::of(&QSpinBox::valueChanged), &dialog,
            [&](int) { storePhysics(); });
    connect(addPhysics, &QPushButton::clicked, &dialog, [&] {
        if (physicsDefs.size() >= 64) {
            QMessageBox::warning(&dialog, tr("Movement Physics"), tr("Maximum 64 physics profiles."));
            return;
        }
        QSet<int> used;
        QSet<QString> names;
        for (const QJsonValue &value : physicsDefs) {
            const QJsonObject item = value.toObject();
            used.insert(item.value(QStringLiteral("id")).toInt());
            names.insert(item.value(QStringLiteral("name")).toString().toCaseFolded());
        }
        int nextId = 7; // Existing runtime modes retain reserved stable IDs 0-6.
        while (nextId <= 255 && used.contains(nextId)) ++nextId;
        if (nextId > 255) return;
        const int selected = physicsList->currentRow();
        QJsonObject item = selected >= 0 ? physicsDefs.at(selected).toObject()
            : GamePlayerProfile::defaultPhysicsProfiles().first().toObject();
        QString name = tr("New Physics");
        int suffix = 2;
        while (names.contains(name.toCaseFolded())) name = tr("New Physics %1").arg(suffix++);
        item.insert(QStringLiteral("id"), nextId);
        item.insert(QStringLiteral("name"), name);
        physicsDefs.append(item);
        physicsList->addItem(name);
        physicsList->setCurrentRow(physicsDefs.size()-1);
        refreshPhysicsChoices();
        physicsName->setFocus(); physicsName->selectAll();
    });
    connect(removePhysics, &QPushButton::clicked, &dialog, [&] {
        const int row = physicsList->currentRow();
        if (row < 0 || physicsDefs.size() <= 1) return;
        const QString name = physicsDefs.at(row).toObject().value(QStringLiteral("name")).toString();
        if (QMessageBox::question(&dialog, tr("Remove Movement Physics"),
                tr("Remove '%1' from this game's physics profiles?").arg(name),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No) != QMessageBox::Yes) return;
        physicsDefs.removeAt(row);
        delete physicsList->takeItem(row);
        refreshPhysicsChoices();
        physicsList->setCurrentRow(qMin(row, int(physicsDefs.size())-1));
    });
    for (const QJsonValue &value : physicsDefs)
        physicsList->addItem(value.toObject().value(QStringLiteral("name")).toString());
    refreshPhysicsChoices();
    physicsList->setCurrentRow(qMax(0, preset->currentIndex()));
    tabs->addTab(movement, tr("Movement & Physics"));
    // Project-wide player stats: the three engine defaults remain fixed fields.
    // Other stats (Mana, Fear, Magic...) are named runtime variables, not world objects.
    auto *stats = new QWidget(tabs);
    auto *statsLayout = new QVBoxLayout(stats);
    auto *sf = new QFormLayout();
    statsLayout->addLayout(sf);
    auto *health = new QSpinBox(stats), *lives = new QSpinBox(stats), *score = new QSpinBox(stats);
    health->setRange(0,65535); lives->setRange(0,65535); score->setRange(0,1000000000);
    health->setValue(profile.value(QStringLiteral("health")).toInt(100));
    lives->setValue(profile.value(QStringLiteral("lives")).toInt(3));
    score->setValue(profile.value(QStringLiteral("score")).toInt());
    sf->addRow(tr("Starting health"), health);
    sf->addRow(tr("Starting lives"), lives);
    sf->addRow(tr("Starting score"), score);
    statsLayout->addWidget(new QLabel(tr("Custom starting stats (e.g. Mana, Magic, Fear). "
        "These values remain with your shared player across worlds."),stats));
    auto *customStats = new QTableWidget(0, 2, stats);
    customStats->setHorizontalHeaderLabels({tr("Stat name"), tr("Starting value")});
    customStats->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    customStats->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    customStats->verticalHeader()->setVisible(false);
    customStats->setSelectionBehavior(QAbstractItemView::SelectRows);
    customStats->setSelectionMode(QAbstractItemView::SingleSelection);
    customStats->setAlternatingRowColors(true);
    customStats->setMinimumHeight(125);
    statsLayout->addWidget(customStats);
    auto *statsButtons = new QHBoxLayout();
    auto *addStat = new QPushButton(tr("Add Stat"),stats);
    auto *removeStat = new QPushButton(tr("Remove Selected"),stats);
    statsButtons->addWidget(addStat); statsButtons->addWidget(removeStat); statsButtons->addStretch();
    statsLayout->addLayout(statsButtons);
    tabs->addTab(stats,tr("Initial Stats"));

    // Inventory entries are kept as structured {name,initial} JSON as before.
    // Editing them in a table avoids the old error-prone "name=quantity" syntax.
    auto *inventoryPage = new QWidget(tabs);
    auto *iv = new QVBoxLayout(inventoryPage);
    auto *inventoryNote = new QLabel(tr("Give each starting item a unique name and quantity. "
        "Use Add Item for NPC to find items requested in any world's dialogue. "
        "Items with quantity 0 never appear in the backpack. Secret/quest items "
        "appear as soon as the player owns one; NPCs can still request, give and take "
        "them. World changes preserve quantities."),inventoryPage);
    inventoryNote->setWordWrap(true);
    iv->addWidget(inventoryNote);
    auto *inventory = new QTableWidget(0, 3, inventoryPage);
    inventory->setHorizontalHeaderLabels({tr("Item name"), tr("Starting quantity"),
        tr("Secret / quest item")});
    inventory->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    inventory->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    inventory->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    inventory->verticalHeader()->setVisible(false);
    inventory->setSelectionBehavior(QAbstractItemView::SelectRows);
    inventory->setSelectionMode(QAbstractItemView::SingleSelection);
    inventory->setAlternatingRowColors(true);
    iv->addWidget(inventory);
    auto *inventoryButtons = new QHBoxLayout();
    auto *addItem = new QPushButton(tr("Add Item"),inventoryPage);
    auto *addNpcItem = new QPushButton(tr("Add Item for NPC..."),inventoryPage);
    addNpcItem->setToolTip(tr("Find items required by reachable NPC dialogue in every .sbgm world."));
    auto *removeItem = new QPushButton(tr("Remove Selected"),inventoryPage);
    inventoryButtons->addWidget(addItem); inventoryButtons->addWidget(addNpcItem);
    inventoryButtons->addWidget(removeItem);
    inventoryButtons->addStretch(); iv->addLayout(inventoryButtons);
    tabs->addTab(inventoryPage,tr("Inventory"));

    // The same row mechanics and maximum-item checks for both editor pages.
    const auto appendNamedRow = [](QTableWidget *table, const QString &name,
                                   int value, int minimum, int maximum) {
        const int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(name));
        auto *spin = new QSpinBox(table);
        spin->setRange(minimum,maximum);
        spin->setValue(value);
        table->setCellWidget(row, 1, spin);
        if (table->columnCount() == 3) {
            auto *hiddenCell = new QTableWidgetItem();
            hiddenCell->setFlags((hiddenCell->flags() | Qt::ItemIsUserCheckable) & ~Qt::ItemIsEditable);
            hiddenCell->setCheckState(Qt::Unchecked);
            hiddenCell->setToolTip(QObject::tr("Mark this as a secret/quest item. All zero-quantity items are hidden; once owned, this item appears in the backpack and remains usable by NPCs."));
            table->setItem(row, 2, hiddenCell);
        }
        return row;
    };
    for (const QJsonValue &v : profile.value(QStringLiteral("customStats")).toArray()) {
        const QJsonObject stat = v.toObject();
        appendNamedRow(customStats, stat.value(QStringLiteral("name")).toString(),
                       stat.value(QStringLiteral("initial")).toInt(), -1000000000, 1000000000);
    }
    for (const QJsonValue &v : profile.value(QStringLiteral("inventory")).toArray()) {
        const QJsonObject item = v.toObject();
        const int row = appendNamedRow(inventory, item.value(QStringLiteral("name")).toString(),
                       item.value(QStringLiteral("initial")).toInt(), 0, 65535);
        inventory->item(row, 2)->setCheckState(
            item.value(QStringLiteral("hidden")).toBool(false) ? Qt::Checked : Qt::Unchecked);
    }
    connect(addStat, &QPushButton::clicked, &dialog, [=, &dialog] {
        if (customStats->rowCount() >= 64) {
            QMessageBox::warning(&dialog,tr("Custom Stats"),tr("Maximum 64 custom stats.")); return;
        }
        const int row=appendNamedRow(customStats,QString(),0,-1000000000,1000000000);
        customStats->setCurrentCell(row,0);
        customStats->editItem(customStats->item(row,0));
    });
    connect(addItem, &QPushButton::clicked, &dialog, [=, &dialog] {
        if (inventory->rowCount() >= 64) {
            QMessageBox::warning(&dialog,tr("Inventory"),tr("Maximum 64 item types.")); return;
        }
        const int row=appendNamedRow(inventory,QString(),0,0,65535);
        inventory->setCurrentCell(row,0);
        inventory->editItem(inventory->item(row,0));
    });
    connect(addNpcItem, &QPushButton::clicked, &dialog, [=, &dialog] {
        const QVector<GameNpcItemIndex::Entry> choices = GameNpcItemIndex::requestedItems(project);
        if (choices.isEmpty()) {
            QMessageBox::information(&dialog,tr("NPC Inventory"),
                tr("No NPC dialogue currently requests an item in any saved .sbgm world. "
                   "Save your worlds after editing their Adventure dialogue, then try again."));
            return;
        }
        QDialog picker(&dialog);
        picker.setWindowTitle(tr("Add Item Requested by NPC"));
        picker.setMinimumWidth(500);
        picker.setStyleSheet(QStringLiteral("QDialog, QPushButton, QListWidget { border-radius: 0px; }"));
        auto *vertical = new QVBoxLayout(&picker);
        auto *hint = new QLabel(tr("These item names come from NPC 'Requires this item' choices "
                                   "in your saved worlds. Select one to give the player a starting quantity."),&picker);
        hint->setWordWrap(true);
        vertical->addWidget(hint);
        auto *list = new QListWidget(&picker);
        for (const auto &entry : choices) {
            auto *row = new QListWidgetItem(entry.name + QStringLiteral(" — ")
                + entry.requestedBy.join(QStringLiteral(", ")), list);
            row->setData(Qt::UserRole,entry.name);
        }
        list->setCurrentRow(0);
        vertical->addWidget(list);
        auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,&picker);
        vertical->addWidget(buttons);
        QObject::connect(buttons,&QDialogButtonBox::accepted,&picker,&QDialog::accept);
        QObject::connect(buttons,&QDialogButtonBox::rejected,&picker,&QDialog::reject);
        QObject::connect(list,&QListWidget::itemDoubleClicked,&picker,[&](QListWidgetItem *) { picker.accept(); });
        if (picker.exec() != QDialog::Accepted || !list->currentItem()) return;
        const QString chosen = list->currentItem()->data(Qt::UserRole).toString();
        for (int row=0; row<inventory->rowCount(); ++row) {
            const QTableWidgetItem *existing = inventory->item(row,0);
            if (existing && existing->text().trimmed().compare(chosen,Qt::CaseInsensitive) == 0) {
                inventory->setCurrentCell(row,1);
                QMessageBox::information(&dialog,tr("Already in Inventory"),
                    tr("'%1' is already listed. Change its starting quantity or visibility in that row.").arg(chosen));
                return;
            }
        }
        if (inventory->rowCount() >= 64) {
            QMessageBox::warning(&dialog,tr("Inventory"),tr("Maximum 64 item types.")); return;
        }
        const int row=appendNamedRow(inventory,chosen,0,0,65535);
        inventory->setCurrentCell(row,1);
        if (QSpinBox *amount = qobject_cast<QSpinBox*>(inventory->cellWidget(row,1)))
            amount->setFocus();
    });
    connect(removeStat, &QPushButton::clicked, &dialog, [=] {
        const int row=customStats->currentRow(); if(row>=0) customStats->removeRow(row);
    });
    connect(removeItem, &QPushButton::clicked, &dialog, [=] {
        const int row=inventory->currentRow(); if(row>=0) inventory->removeRow(row);
    });
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel,&dialog);
    layout->addWidget(buttons);
    connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    connect(buttons,&QDialogButtonBox::accepted,&dialog,[&,this] {
        const QFileInfo art(project.filePath(atlas->text().trimmed()));
        if (!art.isFile() || art.suffix().compare(QStringLiteral("ppb"),Qt::CaseInsensitive)!=0
            || !art.absoluteFilePath().startsWith(project.absolutePath()+QLatin1Char('/'))) {
            QMessageBox::warning(&dialog,tr("Player"),tr("Select an existing PPB INSIDE this game project."));return;
        }
        const QString relativeAnim = QDir::cleanPath(anim->text().trimmed());
        if (!relativeAnim.isEmpty() && relativeAnim != QStringLiteral(".")) {
            const QFileInfo animationPath(project.filePath(relativeAnim));
            if (animationPath.suffix().compare(QStringLiteral("sbanim"),Qt::CaseInsensitive)
                || !animationPath.absoluteFilePath().startsWith(project.absolutePath()+QLatin1Char('/'))) {
                QMessageBox::warning(&dialog,tr("Player"),
                    tr("The animation .sbanim must be inside this game project."));
                return;
            }
        }
        // Commit in-progress name edits before validating their table cells.
        customStats->setFocus();
        inventory->setFocus();
        buttons->setFocus();
        const auto readNamedRows = [&](QTableWidget *table, const QString &title,
                                       QJsonArray *rows) -> bool {
            QSet<QString> seen;
            if (table->rowCount() > 64) {
                QMessageBox::warning(&dialog,title,tr("Maximum 64 entries."));return false;
            }
            for (int row=0; row<table->rowCount(); ++row) {
                QTableWidgetItem *nameCell=table->item(row,0);
                QSpinBox *amount=qobject_cast<QSpinBox*>(table->cellWidget(row,1));
                const QString name=nameCell ? nameCell->text().trimmed() : QString();
                const QString key=name.toCaseFolded();
                if (name.isEmpty() || name.contains(QLatin1Char('\n')) || seen.contains(key)
                    || !amount) {
                    QMessageBox::warning(&dialog,title,
                        tr("Each row needs a unique, non-empty name. Please check row %1.").arg(row+1));
                    return false;
                }
                seen.insert(key);
                QJsonObject entry;
                entry.insert(QStringLiteral("name"),name);
                entry.insert(QStringLiteral("initial"),amount->value());
                if (table->columnCount() == 3) {
                    const QTableWidgetItem *hide = table->item(row,2);
                    entry.insert(QStringLiteral("hidden"),
                        hide && hide->checkState() == Qt::Checked);
                }
                rows->append(entry);
            }
            return true;
        };
        QJsonArray items, customValues;
        if (!readNamedRows(inventory,tr("Inventory"),&items)
            || !readNamedRows(customStats,tr("Custom Stats"),&customValues)) return;
        QJsonObject data=GamePlayerProfile::defaults();
        data.insert(QStringLiteral("atlasPath"),QDir::fromNativeSeparators(atlas->text().trimmed()));
        data.insert(QStringLiteral("animationFile"),anim->text().trimmed());
        data.insert(QStringLiteral("cellWidth"),cw->value());
        data.insert(QStringLiteral("cellHeight"),ch->value());
        data.insert(QStringLiteral("health"),health->value());
        data.insert(QStringLiteral("lives"),lives->value());
        data.insert(QStringLiteral("score"),score->value());
        data.insert(QStringLiteral("customHitbox"),customHitbox->isChecked());
        data.insert(QStringLiteral("hitboxX"),hx->value());
        data.insert(QStringLiteral("hitboxY"),hy->value());
        data.insert(QStringLiteral("hitboxW"),hw->value());
        data.insert(QStringLiteral("hitboxH"),hh->value());
        // Stable IDs ensure renamed and reordered profiles keep their meaning.
        if (physicsDefs.isEmpty()) {
            QMessageBox::warning(&dialog, tr("Movement Physics"),
                tr("Add at least one physics profile.")); return;
        }
        QSet<QString> usedPhysicsNames;
        QSet<int> usedPhysicsIds;
        bool hasStartingPhysics = false;
        for (const QJsonValue &value : physicsDefs) {
            const QJsonObject item = value.toObject();
            const QString name = item.value(QStringLiteral("name")).toString().trimmed();
            const int id = item.value(QStringLiteral("id")).toInt(-1);
            if (name.isEmpty() || name.contains(QLatin1Char('\n'))
                || usedPhysicsNames.contains(name.toCaseFolded()) || usedPhysicsIds.contains(id)) {
                QMessageBox::warning(&dialog, tr("Movement Physics"),
                    tr("Physics profiles must have unique, non-empty names.")); return;
            }
            usedPhysicsNames.insert(name.toCaseFolded());
            usedPhysicsIds.insert(id);
            if (id == currentPhysicsId) hasStartingPhysics = true;
        }
        if (!hasStartingPhysics) {
            QMessageBox::warning(&dialog, tr("Movement Physics"),
                tr("Choose a valid starting physics profile.")); return;
        }
        data.insert(QStringLiteral("physicsPresetId"),currentPhysicsId);
        data.insert(QStringLiteral("physicsProfiles"),physicsDefs);
        for (auto it = worldPhysics.begin(); it != worldPhysics.end(); ++it) {
            if (!usedPhysicsIds.contains(it.value().toInt(-1))) {
                QMessageBox::warning(&dialog, tr("Movement Physics"),
                    tr("A world references a removed physics profile. Select a valid profile."));
                return;
            }
        }
        data.insert(QStringLiteral("worldPhysics"),worldPhysics);
        // Keep the old string for older tools that only know built-in presets.
        const QStringList legacyNames = {QStringLiteral("normal"),QStringLiteral("ice"),
            QStringLiteral("water"),QStringLiteral("slow"),QStringLiteral("space"),
            QStringLiteral("floating"),QStringLiteral("jetpack")};
        data.insert(QStringLiteral("physicsPreset"), currentPhysicsId >= 0
            && currentPhysicsId < legacyNames.size() ? legacyNames.at(currentPhysicsId)
            : QStringLiteral("normal"));
        data.insert(QStringLiteral("inventory"),items);
        data.insert(QStringLiteral("customStats"),customValues);
        QString error;
        if (!GamePlayerProfile::write(project,data,&error)) {
            QMessageBox::warning(&dialog,tr("Player"),error); return;
        }
        dialog.accept();
    });
    if (dialog.exec()!=QDialog::Accepted) return;
    m_playerProfile=QStringLiteral("players/player.sbpi");
    setDirty(); refreshResources(); rebuildScene();
    if (assetFilesChanged) assetFilesChanged();
}

void SidboxGameDesigner::editPlayerStart()
{
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Player Start — World Entry Point"));
    dialog.setStyleSheet(QStringLiteral("QDialog, QPushButton, QLineEdit, QSpinBox, QComboBox { border-radius: 0px; }"));
    dialog.resize(1050, 720);
    auto *layout = new QVBoxLayout(&dialog);
    auto *contentRow = new QHBoxLayout();
    layout->addLayout(contentRow, 1);
    auto *settingsPanel = new QWidget(&dialog);
    auto *settingsLayout = new QVBoxLayout(settingsPanel);
    settingsLayout->setContentsMargins(8, 8, 8, 8);
    settingsLayout->setSpacing(6);
    auto makeSection = [&](const QString &title) -> QFormLayout * {
        auto *toggle = new QToolButton(settingsPanel);
        toggle->setText(title);
        toggle->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toggle->setArrowType(Qt::DownArrow);
        toggle->setCheckable(true);
        toggle->setChecked(true);
        toggle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        toggle->setStyleSheet(QStringLiteral("QToolButton { font-weight: bold; padding: 8px; text-align: left; border: 1px solid palette(mid); }"));
        auto *body = new QWidget(settingsPanel);
        auto *section = new QFormLayout(body);
        section->setRowWrapPolicy(QFormLayout::WrapLongRows);
        section->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        settingsLayout->addWidget(toggle);
        settingsLayout->addWidget(body);
        connect(toggle, &QToolButton::toggled, body, &QWidget::setVisible);
        connect(toggle, &QToolButton::toggled, toggle, [toggle](bool expanded) {
            toggle->setArrowType(expanded ? Qt::DownArrow : Qt::RightArrow);
        });
        return section;
    };
    auto *form = makeSection(tr("Player Start"));
    auto *settingsScroll = new QScrollArea(&dialog);
    settingsScroll->setWidgetResizable(true);
    settingsScroll->setWidget(settingsPanel);
    contentRow->addWidget(settingsScroll, 1);
    auto *previewPanel = new QWidget(&dialog);
    auto *previewLayout = new QVBoxLayout(previewPanel);
    previewLayout->addWidget(new QLabel(tr("Player light position (live preview)"),previewPanel));
    auto *lightPreview = new QLabel(previewPanel);
    lightPreview->setFixedSize(320, 320);
    lightPreview->setToolTip(tr("Uses your shared player's Idle frame. The light ring is a placement guide, not a simulated SIDBOX framebuffer."));
    previewLayout->addWidget(lightPreview);
    auto *previewHint = new QLabel(tr("Purple cross = light centre\nYellow cross = sprite origin\nThe aperture is a preview, not real lighting."),previewPanel);
    previewHint->setWordWrap(true);
    previewLayout->addWidget(previewHint);
    previewLayout->addStretch(1);
    contentRow->addWidget(previewPanel, 0, Qt::AlignTop);
    auto *profile=new QLineEdit(m_playerProfile,&dialog);
    profile->setReadOnly(true);
    form->addRow(tr("Shared player"),profile);
    auto *edit=new QPushButton(tr("Create / Edit Player..."),&dialog);
    form->addRow(edit);
    connect(edit,&QPushButton::clicked,&dialog,[this,profile] {
        openPlayerEditor(); profile->setText(m_playerProfile);
    });
    auto *entry=new QLineEdit(m_playerEntry,&dialog);form->addRow(tr("Entry name"),entry);
    auto *x=new QSpinBox(&dialog),*y=new QSpinBox(&dialog);
    for (QSpinBox *spin:{x,y}) spin->setRange(0,32767);
    x->setValue(m_playerStartX);y->setValue(m_playerStartY);
    form->addRow(tr("World X (pixels)"),x);form->addRow(tr("World Y (pixels)"),y);
    auto *face=new QComboBox(&dialog);
    face->addItem(tr("Left"),0);face->addItem(tr("Right"),1);
    face->setCurrentIndex(m_playerFacing);form->addRow(tr("Initial facing"),face);
    auto addTransitionOptions = [](QComboBox *combo, bool entering) {
        combo->addItem(QObject::tr("None (instant cut)"), QStringLiteral("none"));
        combo->addItem(entering ? QObject::tr("Fade in") : QObject::tr("Fade out"), QStringLiteral("fade"));
        combo->addItem(QObject::tr("Swipe left"), QStringLiteral("left"));
        combo->addItem(QObject::tr("Swipe right"), QStringLiteral("right"));
        combo->addItem(QObject::tr("Swipe up"), QStringLiteral("up"));
        combo->addItem(QObject::tr("Swipe down"), QStringLiteral("down"));
        combo->addItem(entering ? QObject::tr("Circle open") : QObject::tr("Circle close"), QStringLiteral("circle"));
    };
    auto *transitionIn = new QComboBox(&dialog);
    auto *transitionOut = new QComboBox(&dialog);
    addTransitionOptions(transitionIn, true);
    addTransitionOptions(transitionOut, false);
    transitionIn->setCurrentIndex(qMax(0, transitionIn->findData(m_playerTransitionIn)));
    transitionOut->setCurrentIndex(qMax(0, transitionOut->findData(m_playerTransitionOut)));
    form->addRow(tr("Transition IN"), transitionIn);
    form->addRow(tr("Transition OUT"), transitionOut);
    auto *circleOrigin = new QComboBox(&dialog);
    circleOrigin->addItem(tr("Screen centre"), QStringLiteral("center"));
    circleOrigin->addItem(tr("Door / Player Start"), QStringLiteral("location"));
    circleOrigin->setToolTip(tr("For Circle Close: centre on the departing Goto World doorway. "
        "For Circle Open: centre on the destination Player Start. "
        "Screen centre retains the original behaviour."));
    form->addRow(tr("Circle centre"), circleOrigin);
    auto *transitionFrames = new QSpinBox(&dialog);
    transitionFrames->setRange(1, 150);
    transitionFrames->setSuffix(tr(" frames at 50 FPS"));
    circleOrigin->setCurrentIndex(qMax(0, circleOrigin->findData(m_playerCircleOrigin)));
    transitionFrames->setValue(m_playerTransitionFrames);
    form->addRow(tr("Transition duration"), transitionFrames);
    // Sliders are easier to tune than typing frame counts, but each slider
    // retains the exact underlying frame value so old designs round-trip
    // without changing their weather or day/night timing.
    auto addFrameTimingSlider = [&dialog, &form](const QString &title,
        int minimum, int maximum, int current, int singleStep, int pageStep,
        const QString &tooltip) -> QSlider * {
        auto *row = new QWidget(&dialog);
        auto *rowLayout = new QHBoxLayout(row);
        rowLayout->setContentsMargins(0, 0, 0, 0);
        rowLayout->setSpacing(10);
        auto *slider = new QSlider(Qt::Horizontal, row);
        slider->setRange(minimum, maximum);
        slider->setSingleStep(singleStep);
        slider->setPageStep(pageStep);
        slider->setTracking(true);
        slider->setToolTip(tooltip);
        slider->setAccessibleName(title);
        slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        auto *readout = new QLabel(row);
        readout->setMinimumWidth(156);
        readout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        readout->setToolTip(tooltip);
        const auto updateReadout = [readout](int frames) {
            readout->setText(QObject::tr("%1 s (%2 frames)")
                .arg(QString::number(frames / 50.0, 'f', 1))
                .arg(frames));
        };
        QObject::connect(slider, &QSlider::valueChanged, row, updateReadout);
        rowLayout->addWidget(slider, 1);
        rowLayout->addWidget(readout);
        form->addRow(title, row);
        slider->setValue(qBound(minimum, current, maximum));
        updateReadout(slider->value());
        return slider;
    };
    // Collapsible per-world sections keep this busy editor readable.
    form = makeSection(tr("Weather"));
    auto *weatherMode = new QComboBox(&dialog);
    weatherMode->addItem(tr("None / clear"), 0);
    weatherMode->addItem(tr("Rain"), 1);
    weatherMode->addItem(tr("Snow"), 2);
    weatherMode->addItem(tr("Thunderstorm (rain + lightning)"), 3);
    weatherMode->setCurrentIndex(qBound(0, m_weatherMode, 3));
    form->addRow(tr("Weather"), weatherMode);
    auto *weatherDensity = new QSpinBox(&dialog);
    weatherDensity->setRange(1, 64);
    weatherDensity->setValue(m_weatherDensity);
    weatherDensity->setToolTip(tr("Maximum simultaneous rain streaks or snowflakes in the LCD view. Fixed pool; no heap allocations."));
    form->addRow(tr("Weather particles"), weatherDensity);
    auto *weatherWind = new QSpinBox(&dialog);
    weatherWind->setRange(-8, 8);
    weatherWind->setSuffix(tr(" px / frame"));
    weatherWind->setValue(m_weatherWind);
    form->addRow(tr("Weather wind X"), weatherWind);
    auto *weatherColour = new QSpinBox(&dialog);
    weatherColour->setRange(1, 254);
    weatherColour->setValue(m_weatherPaletteIndex);
    weatherColour->setToolTip(tr("Uses this existing FRONT .pal index for rain, snow and lightning. "
        "Choose a pale blue or white palette entry. Index 0 and 255 are deliberately excluded."));
    auto *weatherColourPickerRow = new QWidget(&dialog);
    auto *weatherColourLayout = new QHBoxLayout(weatherColourPickerRow);
    weatherColourLayout->setContentsMargins(0, 0, 0, 0);
    auto *weatherPickColour = new QPushButton(tr("Choose from .pal..."), weatherColourPickerRow);
    weatherColourLayout->addWidget(weatherColour);
    weatherColourLayout->addWidget(weatherPickColour);
    form->addRow(tr("Weather colour palette index"), weatherColourPickerRow);
    connect(weatherPickColour, &QPushButton::clicked, &dialog, [this,&dialog,weatherColour]() {
        const QVector<QRgb> bank = activePalette(QStringLiteral("foreground"));
        if (bank.size() != 256) {
            QMessageBox::information(&dialog, tr("Weather palette"),
                tr("Select a foreground .pal palette first, or enter a palette index manually."));
            return;
        }
        const int selected = SidboxPalettePicker::chooseIndex(&dialog, bank,
            weatherColour->value(), tr("Choose weather / lightning colour"),
            tr("Choose a pale rain, snow or lightning colour. Index 0 is transparent; avoid 255 for spotlight."), false);
        if (selected >= 1 && selected <= 254) weatherColour->setValue(selected);
    });
    auto *weatherInterval = addFrameTimingSlider(tr("Lightning average interval"),
        100, 2000, m_weatherLightningInterval, 25, 100,
        tr("Thunderstorms only: average time between lightning bursts, from 2 to 40 seconds. "
           "The runtime adds random variation. Drag the slider or use the arrow keys to fine-tune."));
    auto *weatherOverlay = new QCheckBox(tr("Enable lightning screen overlay"), &dialog);
    weatherOverlay->setChecked(m_weatherLightningOverlay);
    weatherOverlay->setToolTip(tr("Draw the brief patterned flash across the world. Untick for palette-only lightning; "
        "lightning timing, rain, palette flashes and the optional spotlight suspension still work."));
    form->addRow(weatherOverlay);
    auto *weatherStrength = new QSpinBox(&dialog);
    weatherStrength->setRange(10, 100);
    weatherStrength->setSuffix(tr(" %"));
    weatherStrength->setValue(m_weatherLightningStrength);
    weatherStrength->setToolTip(tr("Strength of the optional patterned screen overlay only. "
        "The palette flash has its own independent 0-100% strength. "
        "Overlay pixels are drawn before the HUD and dialogue."));
    form->addRow(tr("Overlay flash strength"), weatherStrength);
    // The slider controls the lightning pulse LENGTH, not its peak brightness.
    auto *weatherCurveRow = new QWidget(&dialog);
    auto *weatherCurveLayout = new QHBoxLayout(weatherCurveRow);
    weatherCurveLayout->setContentsMargins(0, 0, 0, 0);
    auto *weatherCurve = new QSlider(Qt::Horizontal, weatherCurveRow);
    weatherCurve->setRange(0, 100);
    weatherCurve->setValue(m_weatherLightningCurve);
    weatherCurve->setSingleStep(1);
    weatherCurve->setPageStep(10);
    weatherCurve->setToolTip(tr("Controls the length of the entire lightning flash: "
        "0% = 6 frames (0.12 s), 12% = about 14 frames (0.28 s), "
        "100% = 80 frames (1.6 s). Peak brightness stays unchanged. "
        "This is not a photosensitive-seizure safety guarantee."));
    auto *weatherCurveReadout = new QLabel(weatherCurveRow);
    weatherCurveReadout->setMinimumWidth(70);
    weatherCurveReadout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    const auto updateFlashDurationLabel = [weatherCurveReadout](int value) {
        const int frames = 6 + (value * 74) / 100;
        weatherCurveReadout->setText(QStringLiteral("%1% · %2 f / %3 s")
            .arg(value).arg(frames).arg(QString::number(frames / 50.0, 'f', 2)));
    };
    weatherCurveReadout->setMinimumWidth(152);
    connect(weatherCurve, &QSlider::valueChanged, weatherCurveReadout, updateFlashDurationLabel);
    updateFlashDurationLabel(weatherCurve->value());
    weatherCurveLayout->addWidget(weatherCurve, 1);
    weatherCurveLayout->addWidget(weatherCurveReadout);
    form->addRow(tr("Lightning flash duration"), weatherCurveRow);
    // True indexed-colour lightning: BRIGHTEN temporary FRONT and BACK CLUTs
    // with a bias toward the chosen lightning hue. Keep separate from screen
    // overlay strength, and off by default for saved older worlds.
    auto *weatherPaletteRow = new QWidget(&dialog);
    auto *weatherPaletteLayout = new QHBoxLayout(weatherPaletteRow);
    weatherPaletteLayout->setContentsMargins(0, 0, 0, 0);
    auto *weatherPaletteSlider = new QSlider(Qt::Horizontal, weatherPaletteRow);
    weatherPaletteSlider->setRange(0, 100);
    weatherPaletteSlider->setValue(m_weatherPaletteFlashStrength);
    auto *weatherPaletteStrength = new QSpinBox(weatherPaletteRow);
    weatherPaletteStrength->setRange(0, 100);
    weatherPaletteStrength->setSuffix(tr(" %"));
    weatherPaletteStrength->setValue(m_weatherPaletteFlashStrength);
    weatherPaletteSlider->setToolTip(tr("Brighten both screen palettes with a hint of the selected lightning colour. "
        "0% leaves palettes untouched; independent of overlay strength. Because the CLUT is global, HUD/dialogue "
        "colours also tint briefly while the flash is active."));
    weatherPaletteStrength->setToolTip(weatherPaletteSlider->toolTip());
    connect(weatherPaletteSlider, &QSlider::valueChanged, weatherPaletteStrength, &QSpinBox::setValue);
    connect(weatherPaletteStrength, QOverload<int>::of(&QSpinBox::valueChanged),
        weatherPaletteSlider, &QSlider::setValue);
    weatherPaletteLayout->addWidget(weatherPaletteSlider, 1);
    weatherPaletteLayout->addWidget(weatherPaletteStrength);
    form->addRow(tr("Palette flash strength"), weatherPaletteRow);
    auto *weatherSuspendSpotlight = new QCheckBox(tr("Suspend spotlight during lightning flashes"), &dialog);
    weatherSuspendSpotlight->setChecked(m_weatherSuspendSpotlight);
    weatherSuspendSpotlight->setToolTip(tr("Gradually lighten the player's darkness spotlight as lightning brightens, "
        "then restore it along the same smooth curve. Does not alter the spotlight's saved On/Off state "
        "or your existing main.c rendering calls."));
    form->addRow(weatherSuspendSpotlight);
    auto updateWeatherInputs = [=]() {
        const int mode = weatherMode->currentData().toInt();
        for (QWidget *w : {static_cast<QWidget *>(weatherDensity), static_cast<QWidget *>(weatherWind),
                           static_cast<QWidget *>(weatherColour), static_cast<QWidget *>(weatherPickColour)})
            w->setEnabled(mode != 0);
        weatherInterval->parentWidget()->setEnabled(mode == 3);
        weatherOverlay->setEnabled(mode == 3);
        weatherStrength->setEnabled(mode == 3 && weatherOverlay->isChecked());
        weatherCurveRow->setEnabled(mode == 3);
        weatherPaletteSlider->setEnabled(mode == 3);
        weatherPaletteStrength->setEnabled(mode == 3);
        weatherSuspendSpotlight->setEnabled(mode == 3);
    };
    connect(weatherMode, QOverload<int>::of(&QComboBox::currentIndexChanged),
        &dialog, [updateWeatherInputs](int) { updateWeatherInputs(); });
    connect(weatherOverlay, &QCheckBox::toggled, &dialog,
        [updateWeatherInputs](bool) { updateWeatherInputs(); });
    updateWeatherInputs();
    form = makeSection(tr("Day & Night / Palette Tint"));
    auto *dayNightMode = new QComboBox(&dialog);
    dayNightMode->addItem(tr("Off (original colours)"), 0);
    dayNightMode->addItem(tr("Fixed tint (night, fog, atmosphere)"), 1);
    dayNightMode->addItem(tr("Automatic day and night cycle"), 2);
    dayNightMode->setCurrentIndex(qBound(0, m_dayNightMode, 2));
    form->addRow(tr("Lighting mode"), dayNightMode);
    QColor chosenDayNight(m_dayNightColour);
    if (!chosenDayNight.isValid()) chosenDayNight = QColor(QStringLiteral("#233b68"));
    auto *dayNightColour = new QPushButton(&dialog);
    auto updateDayNightButton = [&chosenDayNight, dayNightColour]() {
        dayNightColour->setText(QObject::tr("Target colour: %1").arg(chosenDayNight.name().toUpper()));
        dayNightColour->setStyleSheet(QStringLiteral("QPushButton { background: %1; color: %2; padding: 6px; }")
            .arg(chosenDayNight.name(), chosenDayNight.lightness() > 128
                ? QStringLiteral("black") : QStringLiteral("white")));
    };
    updateDayNightButton();
    connect(dayNightColour, &QPushButton::clicked, &dialog,
        [&dialog, &chosenDayNight, updateDayNightButton]() {
            const QColor colour = QColorDialog::getColor(chosenDayNight, &dialog,
                QObject::tr("Choose nighttime, fog or atmosphere tint"));
            if (colour.isValid()) { chosenDayNight = colour; updateDayNightButton(); }
        });
    form->addRow(tr("Palette blend target"), dayNightColour);
    auto *dayNightStrengthRow = new QWidget(&dialog);
    auto *dayNightStrengthLayout = new QHBoxLayout(dayNightStrengthRow);
    dayNightStrengthLayout->setContentsMargins(0, 0, 0, 0);
    auto *dayNightSlider = new QSlider(Qt::Horizontal, dayNightStrengthRow);
    dayNightSlider->setRange(0, 100);
    dayNightSlider->setValue(m_dayNightStrength);
    auto *dayNightStrength = new QSpinBox(dayNightStrengthRow);
    dayNightStrength->setRange(0, 100);
    dayNightStrength->setValue(m_dayNightStrength);
    dayNightStrength->setSuffix(tr(" %"));
    connect(dayNightSlider, &QSlider::valueChanged, dayNightStrength, &QSpinBox::setValue);
    connect(dayNightStrength, QOverload<int>::of(&QSpinBox::valueChanged),
        dayNightSlider, &QSlider::setValue);
    dayNightStrengthLayout->addWidget(dayNightSlider, 1);
    dayNightStrengthLayout->addWidget(dayNightStrength);
    form->addRow(tr("Maximum tint strength"), dayNightStrengthRow);
    auto *dayNightDayFrames = addFrameTimingSlider(tr("Day duration"),
        50, 30000, m_dayNightDayFrames, 50, 500,
        tr("How long the daylight portion lasts, from 1 second to 10 minutes at 50 FPS."));
    auto *dayNightNightFrames = addFrameTimingSlider(tr("Night duration"),
        50, 30000, m_dayNightNightFrames, 50, 500,
        tr("How long the full nighttime portion lasts, from 1 second to 10 minutes at 50 FPS."));
    auto *dayNightFadeFrames = addFrameTimingSlider(tr("Dusk / dawn duration"),
        25, 10000, m_dayNightFadeFrames, 25, 250,
        tr("Length of EACH smooth dusk and dawn colour blend, from 0.5 to 200 seconds. "
           "No gameplay physics changes."));
    auto *dayNightStartNight = new QCheckBox(tr("Begin world at night"), &dialog);
    dayNightStartNight->setChecked(m_dayNightStartAtNight);
    form->addRow(dayNightStartNight);
    auto *dayNightHint = new QLabel(tr("Day uses your original .pal colours. Night blends FRONT and BACK palette copies toward the chosen colour. "
        "Fixed tint is useful for fog. Your actual .pal files are never modified. "
        "The same palette tables can also tint HUD and dialogue colours."), &dialog);
    dayNightHint->setWordWrap(true);
    form->addRow(dayNightHint);
    auto updateDayNightWidgets = [=]() {
        const int mode = dayNightMode->currentData().toInt();
        dayNightColour->setEnabled(mode != 0);
        dayNightStrengthRow->setEnabled(mode != 0);
        // Dim the entire slider row, including the seconds/frame readout.
        for (QSlider *slider : {dayNightDayFrames, dayNightNightFrames, dayNightFadeFrames})
            slider->parentWidget()->setEnabled(mode == 2);
        dayNightStartNight->setEnabled(mode == 2);
    };
    connect(dayNightMode, QOverload<int>::of(&QComboBox::currentIndexChanged),
        &dialog, [updateDayNightWidgets](int) { updateDayNightWidgets(); });
    updateDayNightWidgets();
    form = makeSection(tr("Spotlight"));
    auto *spotlightEnabled = new QCheckBox(tr("Enable local darkness with player spotlight"), &dialog);
    spotlightEnabled->setChecked(m_playerSpotlightEnabled);
    spotlightEnabled->setToolTip(tr("Draw a black overlay across the playfield and cut out a circular viewing area around the player. Useful for dark houses, caves and mystery scenes."));
    form->addRow(QString(), spotlightEnabled);
    auto *spotlightRadius = new QSpinBox(&dialog);
    spotlightRadius->setRange(16, 240);
    spotlightRadius->setSuffix(tr(" px clear radius"));
    spotlightRadius->setValue(m_playerSpotlightRadius);
    auto *spotlightFeather = new QSpinBox(&dialog);
    spotlightFeather->setRange(0, 96);
    spotlightFeather->setSuffix(tr(" px feather"));
    spotlightFeather->setValue(m_playerSpotlightFeather);
    form->addRow(tr("Spotlight radius"), spotlightRadius);
    form->addRow(tr("Spotlight feather"), spotlightFeather);
    auto *spotlightAnchor = new QComboBox(&dialog);
    spotlightAnchor->addItem(tr("Centre of player sprite"), true);
    spotlightAnchor->addItem(tr("Player sprite origin (top-left)"), false);
    spotlightAnchor->setCurrentIndex(m_playerSpotlightCenter ? 0 : 1);
    spotlightAnchor->setToolTip(tr("Normally centres the light on the visible player sprite, not the physics origin. "
        "Choose Origin for deliberately offset lights."));
    form->addRow(tr("Spotlight anchor"), spotlightAnchor);
    auto *spotlightOffsetX = new QSpinBox(&dialog);
    auto *spotlightOffsetY = new QSpinBox(&dialog);
    for (QSpinBox *spin : {spotlightOffsetX, spotlightOffsetY}) {
        spin->setRange(-240, 240);
        spin->setSuffix(tr(" px"));
    }
    spotlightOffsetX->setValue(m_playerSpotlightOffsetX);
    spotlightOffsetY->setValue(m_playerSpotlightOffsetY);
    spotlightOffsetX->setToolTip(tr("Positive = right, negative = left of the chosen anchor."));
    spotlightOffsetY->setToolTip(tr("Positive = down, negative = up from the chosen anchor."));
    form->addRow(tr("Light offset X"), spotlightOffsetX);
    form->addRow(tr("Light offset Y"), spotlightOffsetY);
    auto *spotlightFlipX = new QCheckBox(tr("Mirror X offset when player faces left"), &dialog);
    spotlightFlipX->setChecked(m_playerSpotlightFlipX);
    form->addRow(QString(), spotlightFlipX);
    auto *spotlightFlipY = new QCheckBox(tr("Mirror Y offset when player sprite flips vertically"), &dialog);
    spotlightFlipY->setChecked(m_playerSpotlightFlipY);
    form->addRow(QString(), spotlightFlipY);
    auto *spotlightOpacity = new QSpinBox(&dialog);
    spotlightOpacity->setRange(0, 100);
    spotlightOpacity->setSuffix(tr("% darkness"));
    spotlightOpacity->setValue(m_playerSpotlightOpacity);
    spotlightOpacity->setToolTip(tr("100% = normal opaque darkness, fastest. Smaller percentages use a patterned dark overlay and may reduce FPS."));
    form->addRow(tr("Outside darkness opacity"), spotlightOpacity);
    auto *stablePattern = new QCheckBox(tr("Stable 4x4 dither (avoids moving sparkle)"), &dialog);
    stablePattern->setChecked(m_playerSpotlightStableDither);
    stablePattern->setToolTip(tr("Align the light to a 4-pixel grid. This stabilises the ordered-dither dots as the player moves. The light position changes in small 4-pixel steps."));
    form->addRow(QString(), stablePattern);
    auto *animMode = new QComboBox(&dialog);
    animMode->addItem(tr("Off (static feather)"), 0);
    animMode->addItem(tr("Random flicker"), 1);
    animMode->addItem(tr("Pulse (ping-pong)"), 2);
    animMode->setCurrentIndex(qBound(0, m_playerSpotlightAnimMode, 2));
    form->addRow(tr("Feather animation"), animMode);
    auto *animMin = new QSpinBox(&dialog);
    auto *animMax = new QSpinBox(&dialog);
    for (auto *spin : {animMin, animMax}) { spin->setRange(0, 96); spin->setSuffix(tr(" px")); }
    animMin->setValue(m_playerSpotlightAnimMin);
    animMax->setValue(m_playerSpotlightAnimMax);
    form->addRow(tr("Animation feather minimum"), animMin);
    form->addRow(tr("Animation feather maximum"), animMax);
    auto *randomMin = new QSpinBox(&dialog);
    auto *randomMax = new QSpinBox(&dialog);
    auto *pulseDelay = new QSpinBox(&dialog);
    for (auto *spin : {randomMin, randomMax, pulseDelay}) { spin->setRange(1, 600); spin->setSuffix(tr(" frames")); }
    randomMin->setValue(m_playerSpotlightAnimDelayMin);
    randomMax->setValue(m_playerSpotlightAnimDelayMax);
    pulseDelay->setValue(m_playerSpotlightAnimPulseDelay);
    form->addRow(tr("Random time minimum"), randomMin);
    form->addRow(tr("Random time maximum"), randomMax);
    form->addRow(tr("Pulse frames per step"), pulseDelay);
    QObject::connect(animMin, QOverload<int>::of(&QSpinBox::valueChanged), animMax,
                     [animMax](int v) { animMax->setMinimum(v); });
    QObject::connect(randomMin, QOverload<int>::of(&QSpinBox::valueChanged), randomMax,
                     [randomMax](int v) { randomMax->setMinimum(v); });
    animMax->setMinimum(animMin->value());
    randomMax->setMinimum(randomMin->value());
    auto updateAnimationWidgets = [=]() {
        const bool on = spotlightEnabled->isChecked();
        const int mode = animMode->currentData().toInt();
        animMode->setEnabled(on);
        animMin->setEnabled(on && mode != 0);
        animMax->setEnabled(on && mode != 0);
        randomMin->setEnabled(on && mode == 1);
        randomMax->setEnabled(on && mode == 1);
        pulseDelay->setEnabled(on && mode == 2);
        stablePattern->setEnabled(on);
    };
    QObject::connect(animMode, QOverload<int>::of(&QComboBox::currentIndexChanged), &dialog, updateAnimationWidgets);
    QObject::connect(spotlightEnabled, &QCheckBox::toggled, &dialog, updateAnimationWidgets);
    updateAnimationWidgets();
    const QImage playerIdle = GamePlayerProfile::idlePreview(
        QDir(QFileInfo(m_filePath).absolutePath()), m_playerFacing);
    auto updateLightPreview = [=]() {
        QImage preview(320, 320, QImage::Format_ARGB32_Premultiplied);
        QPainter painter(&preview);
        painter.fillRect(preview.rect(), QColor(27, 30, 39));
        for (int y=0; y<320; y+=16) for (int x=0; x<320; x+=16)
            if (((x+y)/16)&1) painter.fillRect(x,y,16,16,QColor(41,45,55));
        painter.setRenderHint(QPainter::Antialiasing, true);
        const qreal magnify = 1.5;
        const qreal spriteW = playerIdle.isNull() ? 32.0 : playerIdle.width();
        const qreal spriteH = playerIdle.isNull() ? 48.0 : playerIdle.height();
        const QPointF origin(160.0-spriteW*magnify/2.0,160.0-spriteH*magnify/2.0);
        const int offsetX = (spotlightFlipX->isChecked() && face->currentData().toInt()==0)
            ? -spotlightOffsetX->value() : spotlightOffsetX->value();
        const int offsetY = spotlightOffsetY->value(); // Idle preview has no vertical facing control.
        const QPointF light = origin + QPointF(
            (spotlightAnchor->currentData().toBool() ? spriteW/2.0 : 0.0) + offsetX,
            (spotlightAnchor->currentData().toBool() ? spriteH/2.0 : 0.0) + offsetY) * magnify;
        if (spotlightEnabled->isChecked()) {
            painter.setPen(QPen(QColor(210,215,225),1.0));
            painter.drawText(QRect(5,5,307,22), Qt::AlignLeft,
                QObject::tr("Outside darkness: %1%").arg(spotlightOpacity->value()));
            painter.setPen(QPen(QColor(176,91,247),2.0));
            painter.setBrush(Qt::NoBrush);
            const qreal radius=spotlightRadius->value()*magnify;
            painter.drawEllipse(light,radius,radius);
            if (spotlightFeather->value()>0) {
                painter.setPen(QPen(QColor(176,91,247,90),1.0,Qt::DashLine));
                const qreal feather=(spotlightRadius->value()+spotlightFeather->value())*magnify;
                painter.drawEllipse(light,feather,feather);
            }
            if (animMode->currentData().toInt() != 0) {
                /* Editor previews the animation envelope, without allocating BOBs. */
                const qreal rMin = (spotlightRadius->value()+animMin->value())*magnify;
                const qreal rMax = (spotlightRadius->value()+animMax->value())*magnify;
                painter.setPen(QPen(QColor(90,230,188,180),1.0,Qt::DashLine));
                painter.drawEllipse(light,rMin,rMin);
                painter.setPen(QPen(QColor(245,171,85,180),1.0,Qt::DashLine));
                painter.drawEllipse(light,rMax,rMax);
                painter.setPen(QPen(QColor(210,215,225),1.0));
                painter.drawText(QRect(5,295,309,21), Qt::AlignLeft,
                    QObject::tr("Cached feather: %1–%2 px").arg(animMin->value()).arg(animMax->value()));
            }
        }
        painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
        if (!playerIdle.isNull())
            painter.drawImage(QRectF(origin,QSizeF(spriteW*magnify,spriteH*magnify)),playerIdle,playerIdle.rect());
        else {
            painter.setPen(QPen(QColor(140,160,180),1));
            painter.setBrush(QColor(65,78,100));
            painter.drawRect(QRectF(origin,QSizeF(spriteW*magnify,spriteH*magnify)));
        }
        painter.setPen(QPen(QColor(255,213,93),2));
        painter.drawLine(QPointF(origin.x()-6,origin.y()),QPointF(origin.x()+6,origin.y()));
        painter.drawLine(QPointF(origin.x(),origin.y()-6),QPointF(origin.x(),origin.y()+6));
        painter.setPen(QPen(QColor(183,102,255),2));
        painter.drawLine(QPointF(light.x()-7,light.y()),QPointF(light.x()+7,light.y()));
        painter.drawLine(QPointF(light.x(),light.y()-7),QPointF(light.x(),light.y()+7));
        painter.end();
        lightPreview->setPixmap(QPixmap::fromImage(preview));
    };
    QObject::connect(spotlightEnabled, &QCheckBox::toggled, &dialog, updateLightPreview);
    QObject::connect(spotlightAnchor, QOverload<int>::of(&QComboBox::currentIndexChanged), &dialog, updateLightPreview);
    QObject::connect(spotlightFlipX, &QCheckBox::toggled, &dialog, updateLightPreview);
    QObject::connect(spotlightFlipY, &QCheckBox::toggled, &dialog, updateLightPreview);
    QObject::connect(face, QOverload<int>::of(&QComboBox::currentIndexChanged), &dialog, updateLightPreview);
    for (QSpinBox *spin: {spotlightOffsetX, spotlightOffsetY, spotlightRadius, spotlightFeather, spotlightOpacity, animMin, animMax})
        QObject::connect(spin, QOverload<int>::of(&QSpinBox::valueChanged), &dialog, updateLightPreview);
    QObject::connect(animMode, QOverload<int>::of(&QComboBox::currentIndexChanged), &dialog, updateLightPreview);
    updateLightPreview();
    auto *maskIndex = new QSpinBox(&dialog);
    maskIndex->setRange(1, 255); // index 0 must stay transparent
    maskIndex->setValue(m_playerSpotlightMaskIndex);
    maskIndex->setToolTip(tr("Reserve this foreground palette index for the spotlight mask and circle transitions. Do not use it in your artwork."));
    auto *maskIndexChooser = new QWidget(&dialog);
    auto *maskIndexRow = new QHBoxLayout(maskIndexChooser);
    maskIndexRow->setContentsMargins(0,0,0,0);
    auto *paletteChoose = new QPushButton(tr("Pick from palette..."), maskIndexChooser);
    paletteChoose->setToolTip(tr("Choose the reserved index visually from your active foreground palette."));
    maskIndexRow->addWidget(maskIndex);
    maskIndexRow->addWidget(paletteChoose);
    form->addRow(tr("Reserved mask palette ID"), maskIndexChooser);
    const QVector<QRgb> foregroundSwatches = activePalette(QStringLiteral("foreground"));
    auto *currentPaletteColour = new QLabel(&dialog);
    const auto updateIndexSwatch = [maskIndex,currentPaletteColour,foregroundSwatches]() {
        const int index = maskIndex->value();
        if (foregroundSwatches.size()!=256) {
            currentPaletteColour->setText(QObject::tr("No active foreground palette selected"));
            currentPaletteColour->setStyleSheet(QString());
            return;
        }
        const QColor colour = QColor::fromRgb(foregroundSwatches.at(index));
        currentPaletteColour->setText(QObject::tr("Current palette[%1]: %2  → overwritten by mask colour")
            .arg(index).arg(colour.name().toUpper()));
        currentPaletteColour->setStyleSheet(QStringLiteral("QLabel { border-radius:0px; padding:4px; background:%1; color:%2; }")
            .arg(colour.name(),colour.lightness()>128?QStringLiteral("black"):QStringLiteral("white")));
    };
    QObject::connect(maskIndex,QOverload<int>::of(&QSpinBox::valueChanged),&dialog,updateIndexSwatch);
    updateIndexSwatch();
    form->addRow(tr("Existing palette colour"),currentPaletteColour);
    QObject::connect(paletteChoose,&QPushButton::clicked,&dialog,[&dialog,maskIndex,foregroundSwatches]() {
        if (foregroundSwatches.size()!=256) {
            QMessageBox::information(&dialog,QObject::tr("Choose mask palette index"),
                QObject::tr("Select an active foreground .pal resource first. You can still enter a palette index manually."));
            return;
        }
        const int selected = SidboxPalettePicker::chooseIndex(&dialog, foregroundSwatches,
            maskIndex->value(), QObject::tr("Choose reserved foreground palette index"),
            QObject::tr("Click the palette cell to RESERVE. Index 0 is transparent and cannot be used."), false);
        if (selected >= 0) maskIndex->setValue(selected);
    });

    QColor chosenMaskColour(m_playerSpotlightMaskColour);
    if (!chosenMaskColour.isValid()) chosenMaskColour = QColor(Qt::black);
    auto *maskColourButton = new QPushButton(&dialog);
    auto updateMaskColourButton = [maskColourButton, &chosenMaskColour]() {
        maskColourButton->setText(QObject::tr("Mask colour: %1").arg(chosenMaskColour.name().toUpper()));
        maskColourButton->setStyleSheet(QStringLiteral("QPushButton { border-radius: 0px; background: %1; color: %2; }")
            .arg(chosenMaskColour.name(), chosenMaskColour.lightness() > 128 ? QStringLiteral("black") : QStringLiteral("white")));
    };
    updateMaskColourButton();
    QObject::connect(maskColourButton, &QPushButton::clicked, &dialog,
        [&dialog, &chosenMaskColour, updateMaskColourButton]() {
            const QColor colour = QColorDialog::getColor(chosenMaskColour, &dialog,
                QObject::tr("Choose reserved mask colour"));
            if (!colour.isValid()) return;
            chosenMaskColour = colour;
            updateMaskColourButton();
        });
    form->addRow(tr("Mask colour"), maskColourButton);
    auto *maskWarning = new QLabel(tr("The chosen foreground palette ID is reserved for darkness and circle wipes. "
                                     "Any artwork using that index will also change colour. "
                                     "Set it to the same colour in every world's palette for consistency."), &dialog);
    maskWarning->setWordWrap(true);
    form->addRow(QString(), maskWarning);
    auto updateSpotlightWidgets = [spotlightEnabled, spotlightRadius, spotlightFeather,
                                   spotlightAnchor, spotlightOffsetX, spotlightOffsetY,
                                   spotlightFlipX, spotlightFlipY, spotlightOpacity,
                                   maskIndex, maskIndexChooser, maskColourButton, maskWarning]() {
        const bool on = spotlightEnabled->isChecked();
        spotlightRadius->setEnabled(on);
        spotlightFeather->setEnabled(on);
        spotlightAnchor->setEnabled(on);
        spotlightOffsetX->setEnabled(on);
        spotlightOffsetY->setEnabled(on);
        spotlightFlipX->setEnabled(on);
        spotlightFlipY->setEnabled(on);
        spotlightOpacity->setEnabled(on);
        maskIndexChooser->setEnabled(on);
        maskIndex->setEnabled(on);
        maskColourButton->setEnabled(on);
        maskWarning->setEnabled(on);
    };
    QObject::connect(spotlightEnabled, &QCheckBox::toggled, &dialog, updateSpotlightWidgets);
    updateSpotlightWidgets();
    auto *buttons=new QDialogButtonBox(QDialogButtonBox::Ok|QDialogButtonBox::Cancel,&dialog);
    layout->addWidget(buttons);
    connect(buttons,&QDialogButtonBox::accepted,&dialog,&QDialog::accept);
    connect(buttons,&QDialogButtonBox::rejected,&dialog,&QDialog::reject);
    dialog.showMaximized();
    if (dialog.exec()!=QDialog::Accepted) return;
    m_playerStartX=x->value();m_playerStartY=y->value();
    m_playerFacing=face->currentData().toInt();
    m_playerTransitionIn=transitionIn->currentData().toString();
    m_playerTransitionOut=transitionOut->currentData().toString();
    m_playerCircleOrigin=circleOrigin->currentData().toString();
    m_playerTransitionFrames=transitionFrames->value();
    m_weatherMode = weatherMode->currentData().toInt();
    m_weatherDensity = weatherDensity->value();
    m_weatherWind = weatherWind->value();
    m_weatherPaletteIndex = weatherColour->value();
    m_weatherLightningInterval = weatherInterval->value();
    m_weatherLightningStrength = weatherStrength->value();
    m_weatherLightningCurve = weatherCurve->value();
    m_weatherLightningOverlay = weatherOverlay->isChecked();
    m_weatherPaletteFlashStrength = weatherPaletteStrength->value();
    m_weatherSuspendSpotlight = weatherSuspendSpotlight->isChecked();
    m_dayNightMode = dayNightMode->currentData().toInt();
    m_dayNightColour = chosenDayNight.name();
    m_dayNightStrength = dayNightStrength->value();
    m_dayNightDayFrames = dayNightDayFrames->value();
    m_dayNightNightFrames = dayNightNightFrames->value();
    m_dayNightFadeFrames = dayNightFadeFrames->value();
    m_dayNightStartAtNight = dayNightStartNight->isChecked();
    m_playerSpotlightEnabled=spotlightEnabled->isChecked();
    m_playerSpotlightRadius=spotlightRadius->value();
    m_playerSpotlightFeather=spotlightFeather->value();
    m_playerSpotlightCenter=spotlightAnchor->currentData().toBool();
    m_playerSpotlightOffsetX=spotlightOffsetX->value();
    m_playerSpotlightOffsetY=spotlightOffsetY->value();
    m_playerSpotlightFlipX=spotlightFlipX->isChecked();
    m_playerSpotlightFlipY=spotlightFlipY->isChecked();
    m_playerSpotlightOpacity=spotlightOpacity->value();
    m_playerSpotlightStableDither=stablePattern->isChecked();
    m_playerSpotlightAnimMode=animMode->currentData().toInt();
    m_playerSpotlightAnimMin=animMin->value();
    m_playerSpotlightAnimMax=animMax->value();
    m_playerSpotlightAnimDelayMin=randomMin->value();
    m_playerSpotlightAnimDelayMax=randomMax->value();
    m_playerSpotlightAnimPulseDelay=pulseDelay->value();
    m_playerSpotlightMaskIndex=maskIndex->value();
    m_playerSpotlightMaskColour=chosenMaskColour.name();
    m_playerEntry=entry->text().trimmed().isEmpty()?QStringLiteral("default"):entry->text().trimmed();
    setDirty();refreshResources();rebuildScene();
}

// Edit a named entrance, or the non-removable default. IDs never depend on names.
void SidboxGameDesigner::editPlayerStartLocation(const QString &id)
{
    if (id == QStringLiteral("default")) { editPlayerStart(); return; }
    int index = -1;
    for (int i = 0; i < m_otherPlayerStarts.size(); ++i)
        if (m_otherPlayerStarts.at(i).id == id) { index = i; break; }
    if (index < 0) return;
    const PlayerStartLocation old = m_otherPlayerStarts.at(index);
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Edit Player Start"));
    dialog.setStyleSheet(QStringLiteral("QDialog, QPushButton, QLineEdit, QSpinBox, QComboBox { border-radius: 0px; }"));
    auto *layout = new QVBoxLayout(&dialog);
    auto *form = new QFormLayout;
    layout->addLayout(form);
    auto *name = new QLineEdit(old.name, &dialog);
    form->addRow(tr("Name"), name);
    auto *x = new QSpinBox(&dialog), *y = new QSpinBox(&dialog);
    for (QSpinBox *spin : {x, y}) spin->setRange(0, 32767);
    x->setValue(old.x); y->setValue(old.y);
    form->addRow(tr("World X (pixels)"), x);
    form->addRow(tr("World Y (pixels)"), y);
    auto *facing = new QComboBox(&dialog);
    facing->addItem(tr("Left"), 0); facing->addItem(tr("Right"), 1);
    facing->setCurrentIndex(old.facing);
    form->addRow(tr("Facing"), facing);
    auto addTransitionOptions = [](QComboBox *combo, bool entering) {
        combo->addItem(QObject::tr("None (instant cut)"), QStringLiteral("none"));
        combo->addItem(entering ? QObject::tr("Fade in") : QObject::tr("Fade out"), QStringLiteral("fade"));
        combo->addItem(QObject::tr("Swipe left"), QStringLiteral("left"));
        combo->addItem(QObject::tr("Swipe right"), QStringLiteral("right"));
        combo->addItem(QObject::tr("Swipe up"), QStringLiteral("up"));
        combo->addItem(QObject::tr("Swipe down"), QStringLiteral("down"));
        combo->addItem(entering ? QObject::tr("Circle open") : QObject::tr("Circle close"), QStringLiteral("circle"));
    };
    auto *transitionIn = new QComboBox(&dialog);
    auto *transitionOut = new QComboBox(&dialog);
    addTransitionOptions(transitionIn, true);
    addTransitionOptions(transitionOut, false);
    transitionIn->setCurrentIndex(qMax(0, transitionIn->findData(old.transitionIn)));
    transitionOut->setCurrentIndex(qMax(0, transitionOut->findData(old.transitionOut)));
    form->addRow(tr("Transition IN"), transitionIn);
    form->addRow(tr("Transition OUT"), transitionOut);
    auto *circleOrigin = new QComboBox(&dialog);
    circleOrigin->addItem(tr("Screen centre"), QStringLiteral("center"));
    circleOrigin->addItem(tr("Door / Player Start"), QStringLiteral("location"));
    circleOrigin->setToolTip(tr("For Circle Close: centre on the departing Goto World doorway. "
        "For Circle Open: centre on the destination Player Start. "
        "Screen centre retains the original behaviour."));
    form->addRow(tr("Circle centre"), circleOrigin);
    auto *transitionFrames = new QSpinBox(&dialog);
    transitionFrames->setRange(1, 150);
    transitionFrames->setSuffix(tr(" frames at 50 FPS"));
    circleOrigin->setCurrentIndex(qMax(0, circleOrigin->findData(old.circleOrigin)));
    transitionFrames->setValue(old.transitionFrames);
    form->addRow(tr("Transition duration"), transitionFrames);
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() != QDialog::Accepted) return;
    const QString label = name->text().trimmed();
    if (label.isEmpty()) { QMessageBox::warning(this, tr("Player Starts"), tr("Name cannot be empty.")); return; }
    PlayerStartLocation &location = m_otherPlayerStarts[index];
    location.name = label; location.x = x->value(); location.y = y->value();
    location.facing = facing->currentData().toInt();
    location.transitionIn = transitionIn->currentData().toString();
    location.transitionOut = transitionOut->currentData().toString();
    location.circleOrigin = circleOrigin->currentData().toString();
    location.transitionFrames = transitionFrames->value();
    setDirty(); refreshResources(); rebuildScene();
}

void SidboxGameDesigner::openTilemapEditor()
{
    // Refresh project-owned stamp definitions when a tab opens its tilemap.
    // This also picks up saves from another running IDE instance.
    GameGlobalStamps::Bank liveBank;
    QString liveBankError;
    if (!liveBank.open(m_filePath, &liveBankError)) {
        QMessageBox::warning(this, tr("Tile Stamps"), liveBankError);
        return;
    }
    syncProjectTileStampBanks(liveBank.tileStampBanks);
    QVector<QPair<QString, QString>> atlases;
    for (const Resource &r : m_resources) {
        // Show ONLY Game Resources -> Tile Atlases here. Previously, a legacy
        // Sprite using the map's PPB path could win the de-duplication check,
        // hiding the real Tile Atlas name when both pointed at the same file.
        // The editor itself handles old map references without inventing an
        // extra Sprite entry in this resource list.
        if (r.kind != QStringLiteral("tileatlas") || r.path.isEmpty()) continue;
        const QString path = resolvedPath(r.path);
        if (QFileInfo(path).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) != 0)
            continue;
        // Each Tile Atlases resource should appear under its own friendly
        // name, even if multiple resources reference the same PPB file.
        atlases.append({r.name, QDir::cleanPath(path)});
    }
    const QString directory = QFileInfo(m_filePath).absolutePath();
    SidboxTilemapEditor editor(m_tilemap, atlases, directory, this);
    editor.setTheme(m_theme);
    // For old projects without .sbpi, retain the legacy reference preview.
    // Once a shared player exists the project profile (not a world sprite)
    // supplies the tile editor's player art and hitbox below.
    const QDir gameProject(QFileInfo(m_filePath).absolutePath());
    if (!QFileInfo::exists(GamePlayerProfile::profilePath(gameProject))) {
    // Mirror the generator's definition of "player": last decoration Sprite
    // named player (case-insensitive). This is a design-only copy, not an
    // additional world object and not the live character's spawn position.
    for (const Resource &r : m_resources) {
        if (r.kind == QStringLiteral("sprite") && !r.path.isEmpty() &&
            r.objectType == QStringLiteral("decoration") &&
            r.name.trimmed().compare(QStringLiteral("player"), Qt::CaseInsensitive) == 0) {
            const QImage sprite = resourcePreview(r);
            if (!sprite.isNull()) {
                QRect playerHitbox; // empty means full sprite; NOT Game Object hitWidth/Height
                if (!r.animationFile.isEmpty()) {
                    const QFileInfo animationPath(resolvedPath(r.animationFile));
                    QFile animation(animationPath.absoluteFilePath());
                    if (animation.open(QIODevice::ReadOnly)) {
                        QJsonParseError parseError;
                        const QJsonDocument data = QJsonDocument::fromJson(animation.readAll(), &parseError);
                        if (parseError.error == QJsonParseError::NoError && data.isObject()) {
                            const QJsonObject root = data.object();
                            // The V1 player physics reads these SAME hitbox fields
                            // from the generated animation header when animation is enabled.
                            if (root.value(QStringLiteral("format")).toString() ==
                                    QStringLiteral("SIDBOX-PLAYER-ANIM") &&
                                root.value(QStringLiteral("cellWidth")).toInt() == sprite.width() &&
                                root.value(QStringLiteral("cellHeight")).toInt() == sprite.height()) {
                                const QRect proposed(root.value(QStringLiteral("hitboxX")).toInt(0),
                                    root.value(QStringLiteral("hitboxY")).toInt(0),
                                    root.value(QStringLiteral("hitboxW")).toInt(sprite.width()),
                                    root.value(QStringLiteral("hitboxH")).toInt(sprite.height()));
                                if (proposed.x() >= 0 && proposed.y() >= 0 &&
                                    proposed.width() > 0 && proposed.height() > 0 &&
                                    proposed.right() < sprite.width() &&
                                    proposed.bottom() < sprite.height())
                                    playerHitbox = proposed;
                            }
                        }
                    }
                }
                editor.setPlayerReference(sprite, r.scale, QPoint(r.x, r.y), playerHitbox);
            }
        }
    }
    }
    // Both Save and Apply persist the shared atlas stamp bank directly into
    // .proj, refreshing all world tabs. No Update Game Project is required.
    // Save keeps this editor open; Apply closes it and optionally offers to
    // generate MISSING runtime files (stamp-brush edits alone need no rebuild).
    const auto applyChanges = [this, &editor](const SidboxTilemap &map, bool fromSaveButton) -> bool {
        // GameTilemapOverlay::boundingRect() reads dimensions from m_tilemap.
        // Remove it from QGraphicsScene *before* changing the map geometry;
        // otherwise the scene's spatial index may hold an invalid old rect.
        if (m_tilemapOverlayItem) {
            delete m_tilemapOverlayItem;
            m_tilemapOverlayItem = nullptr;
        }
        m_tilemap = map;
        m_tilemapEnabled = true;
        rebuildTilemapOverlay();
        refreshFrame();
        setDirty();
        const bool needsExport = !fromSaveButton && tilemapBuildFilesMissing();
        // saveDesign writes .sbgm and .proj and refreshes existing exports.
        if (!saveDesign()) return false;
        if (needsExport && QMessageBox::question(&editor, tr("Publish Game World"),
                tr("This world's generated runtime files are missing. Publish the "
                   "complete world now?\n\n"
                   "This is not needed to share Tile Stamp Banks in the IDE."),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes
            && !regenerateBuildFiles()) return false;
        return true;
    };
    editor.setSaveCallback([this, &applyChanges, &editor](const SidboxTilemap &map) {
        if (!applyChanges(map, true)) return false;
        editor.acknowledgeGlobalStampSave();
        editor.syncCommittedTileStampBanks(m_tilemap.tileStampBanks);
        return true;
    });
    // The preview uses the configured Idle animation frame and initial
    // facing. No world-owned duplicate player resource is required.
    QRect playerHitbox;
    const QImage sharedSprite = GamePlayerProfile::idlePreview(gameProject, m_playerFacing, &playerHitbox);
    if (!sharedSprite.isNull())
        editor.setPlayerReference(sharedSprite, 100,
                                  QPoint(m_playerStartX,m_playerStartY), playerHitbox);
    if (editor.exec() != QDialog::Accepted) return;
    applyChanges(editor.result(), false);
}

bool SidboxGameDesigner::tilemapBuildFilesMissing() const
{
    if (!m_tilemapEnabled) return false;
    const QDir dir(QFileInfo(m_filePath).absolutePath());
    const QString worldBase = sidboxTilemapWorldBaseName(m_filePath);
    const QString levelPath = QStringLiteral("worlds/") + worldBase
        + QStringLiteral("/gamelevels/") + worldBase;
    return !QFileInfo::exists(dir.filePath(levelPath + QStringLiteral(".c")))
        || !QFileInfo::exists(dir.filePath(levelPath + QStringLiteral(".h")))
        || !QFileInfo::exists(dir.filePath(QStringLiteral("gamehelpers/gametilemap.c")))
        || !QFileInfo::exists(dir.filePath(QStringLiteral("gamehelpers/gametilemap.h")))
        || !QFileInfo::exists(dir.filePath(QStringLiteral("gamehelpers/gameglobalstamps.c")));
}

bool SidboxGameDesigner::exportTilemapForCompile()
{
    return exportTilemap(false, true);
}

bool SidboxGameDesigner::exportTilemap(bool showMessage, bool includeMissingHelper)
{
    if (!m_tilemapEnabled) return false;
    QString nameError;
    if (!GameWorldSnapshot::validateUniqueName(m_filePath, &nameError)) {
        QMessageBox::warning(this, tr("World Naming Conflict"), nameError);
        return false;
    }
    const QString directory = QFileInfo(m_filePath).absolutePath();
    // Mode is per .sbgm and persists for automatic saves/Update Project.
    // No mode choice during auto-export, so rebuilding stays deterministic.
    bool includeHelper = includeMissingHelper;
    if (showMessage) {
        QMessageBox choice(this);
        choice.setWindowTitle(tr("Export Platformer Tilemap"));
        choice.setText(tr("Choose where the tilemap graphics and collision data live."));
        choice.setInformativeText(tr("Embedded .c: map bytes become part of the .app.\n"
            "SD .map: map bytes load from gamelevels/<world>.map at runtime.\n"
            "Both publish worlds/<world>/gamelevels/<world>.c/.h using the .sbgm world name.\n"
            "The .map stores tile data and animations; placed game objects stay compiled."));
        choice.setStyleSheet(QStringLiteral("QMessageBox, QPushButton { border-radius:0px; }"));
        auto *embedded = choice.addButton(tr("Export embedded .c"), QMessageBox::AcceptRole);
        auto *sd = choice.addButton(tr("Export SD .map"), QMessageBox::AcceptRole);
        choice.addButton(QMessageBox::Cancel);
        choice.setDefaultButton(m_tilemapExternal ? sd : embedded);
        choice.exec();
        if (choice.clickedButton() != embedded && choice.clickedButton() != sd) return false;
        m_tilemapExternal = choice.clickedButton() == sd;
        setDirty();
        includeHelper = true;
    }
    if (includeHelper) {
        const QDir sourceDir(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
        const QString destination = QDir(directory).filePath(QStringLiteral("gamehelpers"));
        if (!QDir().mkpath(destination)) {
            QMessageBox::warning(this, tr("Tilemap Export"), tr("Cannot create gamehelpers folder."));
            return false;
        }
        for (const QString &ext : {QStringLiteral("h"), QStringLiteral("c")}) {
            const QString path = QDir(destination).filePath(QStringLiteral("gametilemap.") + ext);
            if (QFileInfo::exists(path)) continue;
            QFile templateFile(sourceDir.filePath(QStringLiteral("tilemap.") + ext));
            if (!templateFile.open(QIODevice::ReadOnly)) {
                QMessageBox::warning(this, tr("Tilemap Export"),
                    tr("Missing code helper template: %1").arg(templateFile.fileName()));
                return false;
            }
            QByteArray code = templateFile.readAll();
            if (ext == QStringLiteral("c")) code.replace("\"tilemap.h\"", "\"gametilemap.h\"");
            QSaveFile file(path);
            if (!file.open(QIODevice::WriteOnly) || file.write(code) != code.size() || !file.commit()) {
                QMessageBox::warning(this, tr("Tilemap Export"), tr("Could not write %1").arg(path));
                return false;
            }
        }
        // Exporting helpers should also make their copyable instructions available.
        const QString guidePath = QDir(destination).filePath(QStringLiteral("gametilemap.txt"));
        if (!QFileInfo::exists(guidePath)) {
            QFile input(sourceDir.filePath(QStringLiteral("tilemap.txt")));
            if (input.exists() && input.open(QIODevice::ReadOnly)) {
                const QByteArray guide = input.readAll();
                QSaveFile output(guidePath);
                if (!output.open(QIODevice::WriteOnly)
                    || output.write(guide) != guide.size()
                    || !output.commit()) {
                    output.cancelWriting();
                    QMessageBox::warning(this, tr("Tilemap Export"),
                        tr("Cannot save beginner guide:\n%1").arg(guidePath));
                }
            }
        }
    }
    // Existing project helpers are never replaced silently. Prevent a
    // confusing linker failure if they predate the SD-atlas loader API.
    if (!m_tilemap.atlasPath.isEmpty()) {
        const QString helperC = QDir(directory).filePath(QStringLiteral("gamehelpers/gametilemap.c"));
        const QString helperH = QDir(directory).filePath(QStringLiteral("gamehelpers/gametilemap.h"));
        QFile cFile(helperC), hFile(helperH);
        if (QFileInfo::exists(helperC) && QFileInfo::exists(helperH)) {
            const bool readable = cFile.open(QIODevice::ReadOnly) && hFile.open(QIODevice::ReadOnly);
            const bool current = readable
                && cFile.readAll().contains("GAME_TILEMAP_BOB_SD_ATLAS_V1")
                && hFile.readAll().contains("GAME_TILEMAP_BOB_SD_ATLAS_V1");
            if (!current) {
                QMessageBox::warning(this, tr("Tilemap Helper Update Required"),
                    tr("This project still has an older gametilemap.c/.h.\n\n"
                       "The new level uses an SD-loaded atlas and needs the updated "
                       "gfx_drawbob() tile atlas helper.\n\n"
                       "Back up any edited helpers, replace both files with the new "
                       "CoderGirl tilemap helper, then export again.\n"
                       "Your existing helper files have NOT been overwritten."));
                return false;
            }
        }
    }
    // Every generated level now uses the global loop-placement fields in
    // game_tilemap_t, even when this particular map places no loops. Require
    // the new helper ABI and offer a backup before any helper replacement.
    const bool needsFrontTiles = std::any_of(m_tilemap.flips.cbegin(), m_tilemap.flips.cend(),
        [](char flags) { return (quint8(flags) & 4u) != 0; });
    const bool needsCustomZones = std::any_of(m_tilemap.collisions.cbegin(), m_tilemap.collisions.cend(),
        [](char type) { return quint8(type) >= 9 && quint8(type) <= 24; });
    if (m_tilemapEnabled) {
        const QDir helperSourceDir(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
        const QString helperFolder = QDir(directory).filePath(QStringLiteral("gamehelpers"));
        if (!QDir().mkpath(helperFolder)) {
            QMessageBox::warning(this, tr("Custom Slopes"), tr("Cannot create the gamehelpers folder."));
            return false;
        }
        const QString helperHeader = QDir(helperFolder).filePath(QStringLiteral("gametilemap.h"));
        const QString helperSource = QDir(helperFolder).filePath(QStringLiteral("gametilemap.c"));
        QFile cCheck(helperSource), hCheck(helperHeader);
        bool current = cCheck.open(QIODevice::ReadOnly) && hCheck.open(QIODevice::ReadOnly);
        if (current) {
            const QByteArray existingC = cCheck.readAll();
            const QByteArray existingH = hCheck.readAll();
            current = existingC.contains("cg_map_load_v4") &&
                existingH.contains("GAME_TILE_POINT_SLOPE") &&
                existingH.contains("game_tile_loop_placement_t") &&
                existingC.contains("loop_placements") &&
                existingC.contains("GAME_TILEMAP_RUNTIME_HEADER_ONLY_V1") &&
                (!needsFrontTiles || (existingC.contains("game_tilemap_blit_view_front") &&
                                       existingH.contains("GAME_TILE_DRAW_FRONT"))) &&
                (!needsCustomZones || (existingC.contains("game_zone_at_player") &&
                                        existingH.contains("GAME_ZONE_ENTERED"))) &&
                (!hasAdventure() || existingC.contains("GAME_ADVENTURE_FIRE1_INPUT_GUARD_V1")) &&
                existingC.contains("game_tile_player_current(void)") &&
                existingH.contains("game_tile_player_current(void)");
        }
        cCheck.close(); hCheck.close();
        if (!current) {
            if (QMessageBox::question(this, tr("Upgrade Tilemap Helpers"),
                    tr("This project's tilemap helper is missing current runtime support, "
                       "including live player-position capture for accurate checkpoint saves. "
                       "Update its gamehelpers/gametilemap.c/.h now?\n\n"
                       "Back up the existing helper files and install the new "
                       "versions from the IDE? Your edited helpers will be "
                       "preserved in timestamped .bak files."),
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes) != QMessageBox::Yes)
                return false;
            const QString timestamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd-HHmmss-zzz"));
            for (const QString &ext : {QStringLiteral("c"), QStringLiteral("h")}) {
                const QString destinationPath = QDir(helperFolder).filePath(QStringLiteral("gametilemap.") + ext);
                if (QFileInfo::exists(destinationPath) &&
                    !QFile::copy(destinationPath, destinationPath + QStringLiteral(".bak-") + timestamp)) {
                    QMessageBox::warning(this, tr("Custom Slopes"),
                        tr("Cannot back up %1. No existing helper has been overwritten.").arg(destinationPath));
                    return false;
                }
            }
            for (const QString &ext : {QStringLiteral("c"), QStringLiteral("h")}) {
                QFile sourceFile(helperSourceDir.filePath(QStringLiteral("tilemap.") + ext));
                if (!sourceFile.open(QIODevice::ReadOnly)) {
                    QMessageBox::warning(this, tr("Custom Slopes"), tr("Missing template: %1").arg(sourceFile.fileName()));
                    return false;
                }
                QByteArray text = sourceFile.readAll();
                if (ext == QStringLiteral("c")) text.replace("\"tilemap.h\"", "\"gametilemap.h\"");
                QSaveFile output(QDir(helperFolder).filePath(QStringLiteral("gametilemap.") + ext));
                if (!output.open(QIODevice::WriteOnly) || output.write(text) != text.size() || !output.commit()) {
                    QMessageBox::warning(this, tr("Custom Slopes"),
                        tr("Could not install %1. Restore the .bak files if necessary.").arg(output.fileName()));
                    return false;
                }
            }
        }
    }
    QString error;
    // Export into a hidden per-world staging folder, never project/gamelevels/.
    // GameWorldSnapshot::publish consumes this staging after generating assets.
    const QString worldBase = sidboxTilemapWorldBaseName(m_filePath);
    const QString staging = QDir(directory).filePath(
        QStringLiteral(".codergirl/tilemap-staging/") + worldBase);
    if (!sidboxExportTilemap(m_tilemap, directory, &error, m_tilemapExternal,
                             m_filePath, QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")),
                             staging)) {
        QMessageBox::warning(this, tr("Tilemap Export"), error);
        return false;
    }
    if (assetFilesChanged) assetFilesChanged();
    if (showMessage) {
        const QString worldSymbol = QStringLiteral("game_") + worldBase;
        QMessageBox::information(this, tr("Tilemap Exported"),
            m_tilemapExternal
                ? tr("Staged %1.map plus its C/H files for publication.\n"
                     "After Update Game Project, copy worlds/%1/gamelevels/%1.map "
                     "to gamelevels/%1.map on the TFCard.\n"
                     "Call %2_load_map(\"gamelevels/%1.map\") after initMalloc(), BEFORE %2_load_atlas().\n"
                     "Object/sprite placement remains part of generated C.\n"
                     "Use Update Project to refresh older installed tilemap helpers.")
                      .arg(worldBase, worldSymbol)
                : tr("Staged tilemap %1.c/.h for worlds/%1/gamelevels/.\n"
                     "Update Game Project to publish these files.\n"
                     "Call %2_load_atlas() once after initMalloc().\n"
                     "Copyable instructions: gamehelpers/gametilemap.txt.")
                      .arg(worldBase, worldSymbol));
    }
    return true;
}

// One spline editor is shared by the canvas context menu and the Game Resources
// tree. All edits are staged in widgets until OK; Cancel never changes the path.
void SidboxGameDesigner::editSplineProperties(int index)
{
    if (index < 0 || index >= m_splinePaths.size()) return;
    if (m_activeSpline != index) {
        m_activeSpline = index;
        rebuildSplineOverlay();
    }
    const SplinePath original = m_splinePaths.at(index);

    QDialog dialog(this);
    dialog.setWindowTitle(tr("Spline Properties - %1").arg(original.name));
    dialog.resize(630, 550);
    // Follow the IDE theme, and never introduce rounded Qt controls.
    const auto C = [](const QColor &colour) { return ideThemeColorName(colour); };
    dialog.setStyleSheet(styleSheet() + QStringLiteral(
        "QDialog, QTableWidget, QHeaderView, QSpinBox, QLineEdit, "
        "QPushButton, QCheckBox { border-radius:0px; } "
        "QTableWidget { background:%1; alternate-background-color:%2; color:%3; "
        "gridline-color:%4; selection-background-color:%5; selection-color:%6; "
        "border:1px solid %4; } "
        "QHeaderView::section { background:%2; color:%3; border:1px solid %4; "
        "padding:3px; border-radius:0px; }")
        .arg(C(m_theme.inputBackground), C(m_theme.panelBackground), C(m_theme.text),
             C(m_theme.border), C(m_theme.accent), C(m_theme.brightText)));
    auto *layout = new QVBoxLayout(&dialog);
    auto *form = new QFormLayout;
    auto *name = new QLineEdit(original.name, &dialog);
    auto *frames = new QSpinBox(&dialog);
    frames->setRange(1, 65535);
    frames->setValue(original.durationFrames);
    frames->setSuffix(tr(" frames"));
    auto *loop = new QCheckBox(tr("Loop smoothly from last point to first"), &dialog);
    loop->setChecked(original.loop);
    form->addRow(tr("Name"), name);
    form->addRow(tr("Journey time"), frames);
    form->addRow(QString(), loop);
    layout->addLayout(form);

    auto *help = new QLabel(tr("Edit the exact world coordinates below. "
                               "Point 1 is the start; values are in pixels. "
                               "Pause holds the sprite at that point for extra game frames "
                               "(0 means no delay). For looping paths, the last point's "
                               "pause applies before travelling back to the start. "
                               "Select a numbered row before removing a point. "
                               "Click OK to update the canvas and exported path."), &dialog);
    help->setWordWrap(true);
    layout->addWidget(help);

    auto *table = new QTableWidget(0, 3, &dialog);
    table->setHorizontalHeaderLabels({tr("X (world)"), tr("Y (world)"), tr("Pause (frames)")});
    table->verticalHeader()->setDefaultSectionSize(31);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setAlternatingRowColors(true);
    table->setMinimumHeight(170);
    layout->addWidget(table, 1);

    // The spinboxes accept integer world pixels with no grid snapping, so the
    // programmer can place a control point precisely even if Snap is enabled.
    auto appendPoint = [this, table, &dialog](const QPoint &point, int pauseFrames) {
        const int row = table->rowCount();
        table->insertRow(row);
        for (int column = 0; column < 3; ++column) {
            auto *coordinate = new QSpinBox(&dialog);
            coordinate->setRange(0, column == 0 ? m_worldWidth->value()
                                  : column == 1 ? m_worldHeight->value() : 65535);
            coordinate->setValue(column == 0 ? point.x() : column == 1 ? point.y() : pauseFrames);
            coordinate->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
            table->setCellWidget(row, column, coordinate);
        }
        table->setVerticalHeaderItem(row, new QTableWidgetItem(tr("Point %1").arg(row + 1)));
    };
    for (int i = 0; i < original.points.size(); ++i)
        appendPoint(original.points.at(i), original.pointPauses.value(i, 0));
    if (table->rowCount()) table->selectRow(0);

    auto *pointControls = new QHBoxLayout;
    auto *addPoint = new QPushButton(tr("Add Point"), &dialog);
    auto *removePoint = new QPushButton(tr("Remove Selected Point"), &dialog);
    addPoint->setToolTip(tr("Insert a new point after the selected one (maximum 128)."));
    removePoint->setToolTip(tr("At least two control points are required."));
    pointControls->addWidget(addPoint);
    pointControls->addWidget(removePoint);
    pointControls->addStretch();
    layout->addLayout(pointControls);

    const auto updateButtons = [table, addPoint, removePoint]() {
        addPoint->setEnabled(table->rowCount() < 128);
        removePoint->setEnabled(table->rowCount() > 2 && table->currentRow() >= 0);
    };
    connect(table, &QTableWidget::itemSelectionChanged, &dialog, updateButtons);
    connect(addPoint, &QPushButton::clicked, &dialog, [=]() {
        if (table->rowCount() >= 128) return;
        const int row = table->currentRow();
        const int insertAt = row < 0 ? table->rowCount() : row + 1;
        QPoint point(0, 0);
        // A newly inserted point defaults to no pause, even when its
        // coordinates are copied from the selected point.
        QVector<QPoint> points;
        QVector<int> pauses;
        for (int i = 0; i < table->rowCount(); ++i) {
            auto *x = qobject_cast<QSpinBox *>(table->cellWidget(i, 0));
            auto *y = qobject_cast<QSpinBox *>(table->cellWidget(i, 1));
            auto *pause = qobject_cast<QSpinBox *>(table->cellWidget(i, 2));
            points.append(QPoint(x->value(), y->value()));
            pauses.append(pause->value());
        }
        if (row >= 0) point = points.at(row);
        points.insert(insertAt, point);
        pauses.insert(insertAt, 0);
        table->setRowCount(0);
        for (int i = 0; i < points.size(); ++i) appendPoint(points.at(i), pauses.at(i));
        table->selectRow(insertAt);
        updateButtons();
    });
    connect(removePoint, &QPushButton::clicked, &dialog, [=]() {
        const int row = table->currentRow();
        if (row < 0 || table->rowCount() <= 2) return;
        table->removeRow(row);
        for (int i = 0; i < table->rowCount(); ++i)
            table->verticalHeaderItem(i)->setText(tr("Point %1").arg(i + 1));
        table->selectRow(qMin(row, table->rowCount() - 1));
        updateButtons();
    });
    updateButtons();

    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                         Qt::Horizontal, &dialog);
    layout->addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, [&]() {
        if (name->text().trimmed().isEmpty()) {
            QMessageBox::warning(&dialog, tr("Spline Properties"),
                                 tr("Please enter a spline name."));
            return;
        }
        dialog.accept();
    });
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() != QDialog::Accepted) return;

    SplinePath updated = original;
    updated.name = name->text().trimmed();
    updated.durationFrames = frames->value();
    updated.loop = loop->isChecked();
    updated.points.clear();
    updated.pointPauses.clear();
    for (int row = 0; row < table->rowCount(); ++row) {
        auto *x = qobject_cast<QSpinBox *>(table->cellWidget(row, 0));
        auto *y = qobject_cast<QSpinBox *>(table->cellWidget(row, 1));
        auto *pause = qobject_cast<QSpinBox *>(table->cellWidget(row, 2));
        if (x && y && pause) {
            updated.points.append(QPoint(x->value(), y->value()));
            updated.pointPauses.append(pause->value());
        }
    }
    bool pausesChanged = false;
    for (int i = 0; i < updated.points.size(); ++i)
        if (updated.pointPauses.value(i, 0) != original.pointPauses.value(i, 0))
            pausesChanged = true;
    if (updated.name == original.name && updated.durationFrames == original.durationFrames
        && updated.loop == original.loop && updated.points == original.points
        && !pausesChanged) return;
    m_splinePaths[index] = updated; // Keep persistent ID for attached game objects.
    refreshResources();
    rebuildSplineOverlay();
    setDirty();
}

void SidboxGameDesigner::showSplineMenu(const QPoint &viewPos)
{
    const QPointF worldPos = m_view->mapToScene(viewPos);
    const QPoint point(qBound(0, qRound(worldPos.x()), m_worldWidth->value()),
                       qBound(0, qRound(worldPos.y()), m_worldHeight->value()));
    int clickedNode = -1;
    for (QGraphicsItem *item = m_view->itemAt(viewPos); item; item = item->parentItem()) {
        if (item->data(1).isValid() && item->data(2).isValid()) {
            clickedNode = item->data(2).toInt();
            break;
        }
    }
    QMenu menu(this);
    QAction *create = menu.addAction(tr("Create Spline Path Here..."));
    QMenu *selectMenu = menu.addMenu(tr("Select Spline Path"));
    for (int i = 0; i < m_splinePaths.size(); ++i) {
        QAction *action = selectMenu->addAction(m_splinePaths.at(i).name);
        action->setCheckable(true);
        action->setChecked(i == m_activeSpline);
        action->setData(i);
    }
    selectMenu->setEnabled(!m_splinePaths.isEmpty());
    menu.addSeparator();
    QAction *insert = menu.addAction(tr("Insert Point Here"));
    QAction *removePoint = menu.addAction(tr("Delete This Point"));
    QAction *settings = menu.addAction(tr("Spline Properties (Points / Pauses / Time)..."));
    QAction *removePath = menu.addAction(tr("Delete Spline Path..."));
    const bool hasPath = m_activeSpline >= 0 && m_activeSpline < m_splinePaths.size();
    insert->setEnabled(hasPath && m_splinePaths.at(m_activeSpline).points.size() < 128);
    removePoint->setEnabled(hasPath && clickedNode >= 0
        && m_splinePaths.at(m_activeSpline).points.size() > 2);
    settings->setEnabled(hasPath);
    removePath->setEnabled(hasPath);
    menu.addSeparator();
    QAction *editTiles = menu.addAction(tr("Tilemap Editor (Graphics + Collisions)..."));
    QAction *exportTiles = menu.addAction(tr("Export Tilemap (.c / .map)..."));
    exportTiles->setEnabled(m_tilemapEnabled);
    menu.addSeparator();
    QAction *exportCode = menu.addAction(tr("Export Spline Paths to C..."));
    exportCode->setEnabled(!m_splinePaths.isEmpty());
    menu.addAction(tr("Spline Help: drag numbered dots; loop joins last to first"))->setEnabled(false);
    QAction *chosen = menu.exec(m_view->viewport()->mapToGlobal(viewPos));
    if (!chosen) return;
    if (chosen == editTiles) { openTilemapEditor(); return; }
    if (chosen == exportTiles) { exportTilemap(true); return; }
    if (chosen == create) {
        if (m_splinePaths.size() >= 128) {
            QMessageBox::warning(this, tr("Spline Editor"), tr("A maximum of 128 paths is supported."));
            return;
        }
        bool ok = false;
        const QString name = QInputDialog::getText(this, tr("New Spline Path"),
            tr("Path name:"), QLineEdit::Normal,
            QStringLiteral("flight_%1").arg(m_splinePaths.size() + 1), &ok).trimmed();
        if (!ok || name.isEmpty()) return;
        SplinePath path;
        path.name = name;
        path.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        // Four starter nodes near the click; all can be moved or removed.
        for (const QPoint &offset : {QPoint(0, 0), QPoint(60, -40),
                                    QPoint(120, 35), QPoint(180, 0)}) {
            path.points.append(QPoint(qBound(0, point.x() + offset.x(), m_worldWidth->value()),
                                      qBound(0, point.y() + offset.y(), m_worldHeight->value())));
        }
        path.pointPauses.fill(0, path.points.size());
        m_splinePaths.append(path);
        m_activeSpline = m_splinePaths.size() - 1;
        refreshResources();
        rebuildSplineOverlay();
        setDirty();
    } else if (chosen == insert) {
        SplinePath &path = m_splinePaths[m_activeSpline];
        const int n = path.points.size();
        const int segments = path.loop ? n : n - 1;
        qreal best = 1e30;
        int at = n;
        for (int i = 0; i < segments; ++i) {
            const QPointF a = path.points.at(i);
            const QPointF b = path.points.at((i + 1) % n);
            const QPointF ab = b - a;
            const qreal len = QPointF::dotProduct(ab, ab);
            const qreal t = len > 0 ? qBound(0.0,
                QPointF::dotProduct(QPointF(point) - a, ab) / len, 1.0) : 0.0;
            const QPointF d = QPointF(point) - (a + ab * t);
            const qreal distance = QPointF::dotProduct(d, d);
            if (distance < best) { best = distance; at = i + 1; }
        }
        while (path.pointPauses.size() < n) path.pointPauses.append(0);
        path.points.insert(at, point);
        path.pointPauses.insert(at, 0);
        rebuildSplineOverlay();
        setDirty();
    } else if (chosen == removePoint) {
        SplinePath &path = m_splinePaths[m_activeSpline];
        path.points.removeAt(clickedNode);
        if (clickedNode < path.pointPauses.size()) path.pointPauses.removeAt(clickedNode);
        rebuildSplineOverlay();
        setDirty();
    } else if (chosen == settings) {
        editSplineProperties(m_activeSpline);
    } else if (chosen == removePath) {
        if (QMessageBox::question(this, tr("Delete Spline Path?"),
            tr("Remove the path '%1' from this design?\n"
               "Exported C files will update the next time you save.")
                .arg(m_splinePaths.at(m_activeSpline).name),
            QMessageBox::Yes | QMessageBox::Cancel,
            QMessageBox::Cancel) != QMessageBox::Yes) return;
        m_splinePaths.removeAt(m_activeSpline);
        m_activeSpline = m_splinePaths.isEmpty() ? -1 : qMin(m_activeSpline, m_splinePaths.size() - 1);
        refreshResources();
        rebuildSplineOverlay();
        setDirty();
    } else if (chosen == exportCode) {
        exportSplinePaths(true);
    } else if (chosen->parent() == selectMenu) {
        const int index = chosen->data().toInt();
        if (index >= 0 && index < m_splinePaths.size()) {
            m_activeSpline = index;
            rebuildSplineOverlay();
            setDirty();
        }
    }
}

bool SidboxGameDesigner::exportSplinePaths(bool showMessage)
{
    // A manual export offers to include the movement implementation as well
    // as the point data. Saving an already-exported design does not ask again.
    bool copyHelper = false;
    if (showMessage) {
        const QMessageBox::StandardButton answer = QMessageBox::question(
            this, tr("Export Spline Paths"),
            tr("Do you want gamespline.c and gamespline.h copied into your game?\n"
               "Without these helper files, your spline cannot move sprites.\n\n"
               "Yes: Copy any missing helper files and export the spline paths.\n"
               "No: Export the spline paths without copying helpers.\n"
               "Cancel: Do not export anything.\n\n"
               "Existing helper files will not be overwritten."),
            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
            QMessageBox::Yes);
        if (answer == QMessageBox::Cancel || answer == QMessageBox::NoButton)
            return false;
        copyHelper = (answer == QMessageBox::Yes);
    }

    const QString folder = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gamehelpers"));
    const QString helperHeaderPath = QDir(folder).filePath(QStringLiteral("gamespline.h"));
    const QString helperSourcePath = QDir(folder).filePath(QStringLiteral("gamespline.c"));
    const bool needHelperHeader = copyHelper && !QFileInfo::exists(helperHeaderPath);
    const bool needHelperSource = copyHelper && !QFileInfo::exists(helperSourcePath);
    QByteArray helperHeader, helperSource;

    // Read the SDK templates before touching the project's output files.
    if (needHelperHeader || needHelperSource) {
        const QDir templates(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
        if (needHelperHeader) {
            const QString path = templates.filePath(QStringLiteral("spline.h"));
            QFile input(path);
            if (!input.open(QIODevice::ReadOnly)) {
                QMessageBox::warning(this, tr("Export Spline Paths"),
                    tr("Cannot read helper template:\n%1").arg(path));
                return false;
            }
            helperHeader = input.readAll();
        }
        if (needHelperSource) {
            const QString path = templates.filePath(QStringLiteral("spline.c"));
            QFile input(path);
            if (!input.open(QIODevice::ReadOnly)) {
                QMessageBox::warning(this, tr("Export Spline Paths"),
                    tr("Cannot read helper template:\n%1").arg(path));
                return false;
            }
            helperSource = input.readAll();
            // Match the installed helper name, just like Add Helper Code.
            helperSource.replace("\"spline.h\"", "\"gamespline.h\"");
        }
    }

    if (!QDir().mkpath(folder)) {
        QMessageBox::warning(this, tr("Export Spline Paths"),
            tr("Cannot create folder:\n%1").arg(folder));
        return false;
    }
    // Stage 4.51: splinepaths.rulec/.ruleh own the C declarations and arrays;
    // the IDE supplies only validated path names, points, pauses and settings.
    const QDir pathRuleFolder(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
    QMap<QString, QByteArray> mainTemplates, pathTemplates;
    const QRegularExpression pathSectionRe(QStringLiteral(
        R"((?ms)^@IDE_SECTION\{PATH\}[ \t]*\r?\n(.*?)^@IDE_SECTION_END[ \t]*\r?\n?)"));
    for (const QString &ext : {QStringLiteral(".rulec"), QStringLiteral(".ruleh")}) {
        QFile input(pathRuleFolder.filePath(QStringLiteral("splinepaths") + ext));
        if (!input.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Export Spline Paths"),
                tr("Cannot read spline-path rule: %1").arg(input.fileName()));
            return false;
        }
        QString raw = QString::fromUtf8(input.readAll());
        const auto match = pathSectionRe.match(raw);
        if (raw.count(QStringLiteral("@IDE_SECTION{PATH}")) != 1 ||
            !match.hasMatch()) {
            QMessageBox::warning(this, tr("Export Spline Paths"),
                tr("Malformed PATH section in %1").arg(input.fileName()));
            return false;
        }
        pathTemplates.insert(ext, match.captured(1).toUtf8());
        raw.remove(pathSectionRe);
        if (raw.contains(QStringLiteral("@IDE_SECTION"))) {
            QMessageBox::warning(this, tr("Export Spline Paths"),
                tr("Unclosed rule section in %1").arg(input.fileName()));
            return false;
        }
        mainTemplates.insert(ext, raw.toUtf8());
    }
    if (!mainTemplates.value(QStringLiteral(".rulec")).contains("@IDE{PATH_DEFINITIONS}") ||
        !mainTemplates.value(QStringLiteral(".ruleh")).contains("@IDE{PATH_DECLARATIONS}")) {
        QMessageBox::warning(this, tr("Export Spline Paths"),
            tr("Spline-path rule is missing its required path collection marker."));
        return false;
    }
    QString definitions, declarations;
    QSet<QString> identifiers;
    for (int i = 0; i < m_splinePaths.size(); ++i) {
        const SplinePath &path = m_splinePaths.at(i);
        if (path.points.size() < 2) continue;
        QString name = path.name.toLower();
        name.replace(QRegularExpression(QStringLiteral("[^a-z0-9_]")), QStringLiteral("_"));
        if (name.isEmpty() || name.at(0).isDigit()) name.prepend(QLatin1Char('_'));
        QString identifier = QStringLiteral("spline_") + name;
        const QString unsuffixed = identifier;
        int suffix = 2;
        while (identifiers.contains(identifier))
            identifier = unsuffixed + QStringLiteral("_%1").arg(suffix++);
        identifiers.insert(identifier);
        QString pointRows;
        for (int n = 0; n < path.points.size(); ++n) {
            const QPoint &point = path.points.at(n);
            pointRows += QStringLiteral("    {%1, %2, %3},\n")
                .arg(point.x()).arg(point.y()).arg(path.pointPauses.value(n, 0));
        }
        const QMap<QString, QString> fields = {
            {QStringLiteral("SYMBOL"), identifier},
            {QStringLiteral("POINT_COUNT"), QString::number(path.points.size())},
            {QStringLiteral("POINT_ROWS"), pointRows},
            {QStringLiteral("DURATION_FRAMES"), QString::number(path.durationFrames)},
            {QStringLiteral("LOOP"), path.loop ? QStringLiteral("1") : QStringLiteral("0")}
        };
        QByteArray out;
        QString err;
        if (!GameHelperTemplates::renderFields(pathTemplates.value(QStringLiteral(".rulec")),
                                                fields, QStringLiteral("splinepaths.rulec/PATH"),
                                                &out, &err)) {
            QMessageBox::warning(this, tr("Export Spline Paths"), err);
            return false;
        }
        definitions += QString::fromUtf8(out);
        if (!GameHelperTemplates::renderFields(pathTemplates.value(QStringLiteral(".ruleh")),
                                                fields, QStringLiteral("splinepaths.ruleh/PATH"),
                                                &out, &err)) {
            QMessageBox::warning(this, tr("Export Spline Paths"), err);
            return false;
        }
        declarations += QString::fromUtf8(out);
    }
    QByteArray header, source;
    QString err;
    if (!GameHelperTemplates::renderFields(mainTemplates.value(QStringLiteral(".rulec")),
            {{QStringLiteral("PATH_DEFINITIONS"), definitions}},
            QStringLiteral("splinepaths.rulec"), &source, &err) ||
        !GameHelperTemplates::renderFields(mainTemplates.value(QStringLiteral(".ruleh")),
            {{QStringLiteral("PATH_DECLARATIONS"), declarations}},
            QStringLiteral("splinepaths.ruleh"), &header, &err)) {
        QMessageBox::warning(this, tr("Export Spline Paths"), err);
        return false;
    }

    // Install only missing helper files. Never replace custom game code.
    // Copy helpers first, so an incomplete helper copy never produces new
    // splinepaths files which look ready to compile.
    if (needHelperHeader) {
        QSaveFile output(helperHeaderPath);
        if (!output.open(QIODevice::WriteOnly)
            || output.write(helperHeader) != helperHeader.size()
            || !output.commit()) {
            output.cancelWriting();
            QMessageBox::warning(this, tr("Export Spline Paths"),
                tr("Could not copy gamespline.h into:\n%1").arg(folder));
            return false;
        }
    }
    if (needHelperSource) {
        QSaveFile output(helperSourcePath);
        if (!output.open(QIODevice::WriteOnly)
            || output.write(helperSource) != helperSource.size()
            || !output.commit()) {
            output.cancelWriting();
            QMessageBox::warning(this, tr("Export Spline Paths"),
                tr("Could not copy gamespline.c into:\n%1").arg(folder));
            return false;
        }
    }

    if (copyHelper || (QFileInfo::exists(helperHeaderPath)
                       && QFileInfo::exists(helperSourcePath))) {
        const QString guidePath = QDir(folder).filePath(QStringLiteral("gamespline.txt"));
        if (!QFileInfo::exists(guidePath)) {
            QFile input(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game/spline.txt")));
            if (input.exists() && input.open(QIODevice::ReadOnly)) {
                const QByteArray guide = input.readAll();
                QSaveFile output(guidePath);
                if (!output.open(QIODevice::WriteOnly)
                    || output.write(guide) != guide.size()
                    || !output.commit()) {
                    output.cancelWriting();
                    QMessageBox::warning(this, tr("Export Spline Paths"),
                        tr("Could not save optional beginner guide:\n%1").arg(guidePath));
                }
            }
        }
    }

    const QString hp = QDir(folder).filePath(QStringLiteral("splinepaths.h"));
    const QString cp = QDir(folder).filePath(QStringLiteral("splinepaths.c"));
    QSaveFile hFile(hp), cFile(cp);
    if (!hFile.open(QIODevice::WriteOnly) || !cFile.open(QIODevice::WriteOnly)
        || hFile.write(header) != header.size() || cFile.write(source) != source.size()) {
        hFile.cancelWriting(); cFile.cancelWriting();
        QMessageBox::warning(this, tr("Export Spline Paths"),
            tr("Cannot write splinepaths.c/.h in:\n%1").arg(folder));
        return false;
    }
    if (!hFile.commit() || !cFile.commit()) {
        QMessageBox::warning(this, tr("Export Spline Paths"),
            tr("Could not finish writing splinepaths.c/.h in:\n%1").arg(folder));
        return false;
    }
    if (assetFilesChanged) assetFilesChanged();
    if (showMessage)
        QMessageBox::information(this, tr("Spline Paths Exported"),
            tr("Please review splinepaths.c on how to use this spline."));
    return true;
}

void SidboxGameDesigner::buildUi()
{
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(3, 3, 3, 3);
    layout->setSpacing(5);

    auto *top = new QHBoxLayout;
    auto *caption = new QLabel(tr("Game Designer  |  V1 Gaming"), this);
    QFont titleFont = caption->font();
    titleFont.setBold(true);
    caption->setFont(titleFont);
    top->addWidget(caption);
    top->addSpacing(12);
    top->addWidget(new QLabel(tr("Planes:"), this));
    m_planeMode = new GameComboBox(this);
    m_planeMode->addItem(tr("Foreground only"), QStringLiteral("single"));
    m_planeMode->addItem(tr("Foreground + Background"), QStringLiteral("dual"));
    m_planeMode->setToolTip(tr("Controls the SIDBOX graphics model, not the 480×320 viewport."));
    top->addWidget(m_planeMode);
    top->addSpacing(12);
    top->addWidget(new QLabel(tr("World:"), this));
    m_worldWidth = new QSpinBox(this);
    m_worldHeight = new QSpinBox(this);
    for (auto *spin : {m_worldWidth, m_worldHeight}) {
        spin->setRange(LCD_WIDTH, MAX_WORLD);
        spin->setSingleStep(32);
        spin->setMaximumWidth(90);
    }
    m_worldHeight->setMinimum(LCD_HEIGHT);
    m_worldWidth->setToolTip(tr("Virtual level size in pixels. 100 tiles x 16 px = 1600 px.\n"
                                "This is NOT the physical 960x320 foreground ring buffer."));
    m_worldHeight->setToolTip(m_worldWidth->toolTip());
    m_worldWidth->setValue(960);
    m_worldHeight->setValue(640);
    top->addWidget(m_worldWidth);
    top->addWidget(new QLabel(QStringLiteral("×"), this));
    top->addWidget(m_worldHeight);
    top->addStretch(1);
    layout->addLayout(top);

    // Keep the long action buttons off the world-controls row. Previously
    // this single unbreakable row became a huge minimum width for QTabWidget;
    // Qt could then grow the maximised IDE when the source-code pane reopened.
    auto *topActions = new QHBoxLayout;
    topActions->setSpacing(6);
    topActions->addWidget(new QLabel(tr("Camera:"), this));
    m_cameraX = new QSpinBox(this);
    m_cameraY = new QSpinBox(this);
    for (auto *spin : {m_cameraX, m_cameraY}) {
        spin->setRange(0, MAX_WORLD);
        spin->setMaximumWidth(78);
    }
    topActions->addWidget(m_cameraX);
    topActions->addWidget(new QLabel(QStringLiteral(","), this));
    topActions->addWidget(m_cameraY);
    auto *focusCamera = new QPushButton(tr("Centre View on LCD"), this);
    focusCamera->setToolTip(tr("Centre the editor view on the yellow LCD frame. The game camera X/Y do not change."));
    topActions->addWidget(focusCamera);
    auto *editTilemap = new QPushButton(tr("Tilemap Editor..."), this);
    editTilemap->setToolTip(tr("Edit the attached tilemap artwork, collision and tile animations."));
    topActions->addWidget(editTilemap);
    auto *editPlayerAnimation = new QPushButton(tr("Create / Edit Player..."), this);
    editPlayerAnimation->setToolTip(tr("Configure the shared player atlas, Idle animations, hitbox, physics and inventory."));
    topActions->addWidget(editPlayerAnimation);
    connect(editPlayerAnimation, &QPushButton::clicked, this, [this] { openPlayerEditor(); });
    auto *adventureButton = new QPushButton(tr("Adventure Editor..."), this);
    adventureButton->setToolTip(tr("Advanced Platformer: design inventory, NPC dialogue, choices and a nine-tile box frame."));
    topActions->addWidget(adventureButton);
    connect(adventureButton, &QPushButton::clicked, this, [this] { openAdventureEditor(); });
    auto *hudButton = new QPushButton(tr("HUD Editor..."), this);
    hudButton->setToolTip(tr("Design a project-wide HUD with atlas tiles, labels and collectible counters."));
    topActions->addWidget(hudButton);
    connect(hudButton, &QPushButton::clicked, this, [this] {
        const QString root = QFileInfo(m_filePath).absolutePath();
        QString error;
        if (editGameHud(this, root, &error)) {
            if (assetFilesChanged) assetFilesChanged();
        } else if (!error.isEmpty()) {
            QMessageBox::warning(this, tr("HUD Editor"), error);
        }
    });
    auto *questButton = new QPushButton(tr("Quests..."), this);
    questButton->setToolTip(tr("Project-wide quest lines, objectives and persistent journal progress."));
    questButton->setMaximumWidth(96);
    topActions->addWidget(questButton);
    connect(questButton, &QPushButton::clicked, this, [this] {
        QString error;
        if (editGameQuests(this,QFileInfo(m_filePath).absolutePath(),&error)) {
            if (assetFilesChanged) assetFilesChanged();
        } else if (!error.isEmpty()) QMessageBox::warning(this,tr("Quest Designer"),error);
    });
    auto *flowButton = new QPushButton(tr("Logic Flow..."), this);
    flowButton->setToolTip(tr("Read-only logic map of all saved worlds, inventory, NPC dialogue and links."));
    flowButton->setMaximumWidth(108);
    topActions->addWidget(flowButton);
    connect(flowButton, &QPushButton::clicked, this, [this] {
        openGameFlowEditor(this, QFileInfo(m_filePath).absolutePath(), m_theme);
    });
    auto *titleScreenButton = new QPushButton(tr("Title Screen..."), this);
    titleScreenButton->setToolTip(tr("Design an optional project-wide title/menu screen with menu actions such as Start Game, Load Game and Goto World."));
    titleScreenButton->setMaximumWidth(116);
    topActions->addWidget(titleScreenButton);
    connect(titleScreenButton, &QPushButton::clicked, this, [this] {
        QString error;
        if (editGameTitleScreen(this, QFileInfo(m_filePath).absolutePath(), &error)) {
            if (assetFilesChanged) assetFilesChanged();
        } else if (!error.isEmpty()) {
            QMessageBox::warning(this, tr("Title Screen Designer"), error);
        }
    });
    auto *pixArtButton = new QPushButton(tr("PixArt..."), this);
    pixArtButton->setToolTip(tr("Generate palette-aware pixel-art textures, loopable landscapes and backgrounds, then export them as PNG or PPB."));
    pixArtButton->setMaximumWidth(96);
    topActions->addWidget(pixArtButton);
    connect(pixArtButton, &QPushButton::clicked, this, [this] {
        QString error;
        if (openGamePixArtEditor(this, QFileInfo(m_filePath).absolutePath(), &error)) {
            if (assetFilesChanged) assetFilesChanged();
        } else if (!error.isEmpty()) {
            QMessageBox::warning(this, tr("PixArt"), error);
        }
    });
    topActions->addStretch(1);
    auto *generate = new QPushButton(tr("Generate V1 Game Code..."), this);
    generate->setToolTip(tr("Generate gameassets/gameassets.c and .h without modifying main.c, game logic or original assets."));
    topActions->addWidget(generate);
    auto *save = new QPushButton(tr("Save Design"), this);
    topActions->addWidget(save);
    layout->addLayout(topActions);

    auto *splitter = new QSplitter(Qt::Horizontal, this);
    splitter->setChildrenCollapsible(false);
    layout->addWidget(splitter, 1);

    auto *resourcesPanel = new QWidget(splitter);
    // Keep the left resource pane narrow without letting combo contents or
    // long checkbox text enlarge the whole IDE's minimum width.
    resourcesPanel->setMinimumWidth(125);
    auto *resourcesLayout = new QVBoxLayout(resourcesPanel);
    resourcesLayout->setContentsMargins(4, 4, 4, 4);
    resourcesLayout->addWidget(new QLabel(tr("GAME RESOURCES"), resourcesPanel));
    auto *resourceTree = new GameResourceTree(resourcesPanel);
    m_resourceTree = resourceTree;
    resourceTree->setMinimumWidth(0);
    resourceTree->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    resourceTree->installEventFilter(this);
    resourceTree->viewport()->installEventFilter(this);
    resourceTree->setDragDropMode(QAbstractItemView::DropOnly);
    resourceTree->setDefaultDropAction(Qt::CopyAction);
    resourceTree->setAcceptDrops(true);
    resourceTree->viewport()->setAcceptDrops(true);
    resourceTree->filesDropped = [this](const QStringList &paths, const QString &kind, const QString &plane) {
        importDroppedFiles(paths, kind, plane);
    };
    m_resourceTree->setHeaderHidden(true);
    m_resourceTree->setIconSize(QSize(20, 20));
    m_resourceTree->setSelectionMode(QAbstractItemView::SingleSelection);
    // Never sort the whole tree: the nine top-level categories have a fixed order.
    m_resourceTree->setSortingEnabled(false);
    resourcesLayout->addWidget(m_resourceTree, 1);
    auto *frontClutLabel = new QLabel(tr("Preview foreground CLUT"), resourcesPanel);
    frontClutLabel->setWordWrap(true);
    resourcesLayout->addWidget(frontClutLabel);
    m_frontPalette = new GameComboBox(resourcesPanel);
    m_frontPalette->setMinimumWidth(0);
    m_frontPalette->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    m_frontPalette->setMinimumContentsLength(9);
    m_frontPalette->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    m_frontPalette->setToolTip(tr("Choose the foreground .pal / indexed PPB used by Forced Preview. "
                                  "Pixel indices in the source images are never changed."));
    auto *frontChoices = new QListView(m_frontPalette);
    frontChoices->setFrameShape(QFrame::NoFrame);
    frontChoices->setStyleSheet(QStringLiteral("QListView { border-radius: 0px; }"));
    m_frontPalette->setView(frontChoices);
    resourcesLayout->addWidget(m_frontPalette);
    auto *backClutLabel = new QLabel(tr("Preview background CLUT"), resourcesPanel);
    backClutLabel->setWordWrap(true);
    resourcesLayout->addWidget(backClutLabel);
    m_backPalette = new GameComboBox(resourcesPanel);
    m_backPalette->setMinimumWidth(0);
    m_backPalette->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    m_backPalette->setMinimumContentsLength(9);
    m_backPalette->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    m_backPalette->setToolTip(tr("Choose the background .pal / indexed PPB used by Forced Preview. "
                                 "This is independent of the foreground CLUT."));
    auto *backChoices = new QListView(m_backPalette);
    backChoices->setFrameShape(QFrame::NoFrame);
    backChoices->setStyleSheet(QStringLiteral("QListView { border-radius: 0px; }"));
    m_backPalette->setView(backChoices);
    resourcesLayout->addWidget(m_backPalette);
    m_forcePalette = new QCheckBox(tr("Force preview CLUTs"), resourcesPanel);
    m_forcePalette->setToolTip(tr("Indexed PPBs keep their original pixel bytes. This RGB colour preview "
                                  "shows nonzero foreground indices opaque (index 0 stays transparent). "
                                  "Original CLUT alpha is unchanged and may affect real SIDBOX blending."));
    resourcesLayout->addWidget(m_forcePalette);
    m_previewPaletteAlpha = new QCheckBox(tr("Preview palette alpha"), resourcesPanel);
    m_previewPaletteAlpha->setChecked(false); // Preserve old opaque RGB preview by default.
    m_previewPaletteAlpha->setToolTip(tr("Show actual foreground palette transparency in indexed previews. "
        "Requires Force preview CLUTs. Background remains fully opaque; index 0 stays transparent. "
        "This does not change .pal, PPB or game graphics."));
    resourcesLayout->addWidget(m_previewPaletteAlpha);
    m_buildPaletteButton = new QPushButton(tr("Build Shared CLUT..."), resourcesPanel);
    m_buildPaletteButton->setToolTip(tr("Generates palette files only in gamepalettes/. "
        "Does not create or modify PPB images or change any resource paths."));
    resourcesLayout->addWidget(m_buildPaletteButton);
    // Project preparation belongs next to Game Resources, not on the world
    // canvas toolbar. The narrow resource column can still resize freely.
    auto *updateProject = new QPushButton(tr("Update Project..."), resourcesPanel);
    updateProject->setMinimumWidth(0);
    updateProject->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    updateProject->setToolTip(tr("Back up and refresh installed game helpers, export splines/tiles, "
                                 "and regenerate V1 code plus maingame.c.txt in one operation."));
    resourcesLayout->addWidget(updateProject);
    connect(updateProject, &QPushButton::clicked, this, [this]() {
        if (updateAllProjectWorlds) updateAllProjectWorlds();
        else updateGameProject(); // standalone Designer fallback
    });
    m_resourceTree->setToolTip(tr("Drag files from Project Files here, or right-click to add resources. "
        "Tile Atlases holds PPB tile sheets without placing a sprite on the canvas. "
        "Double-click a palette to open its editor. "
        "Select a Game Object or Spline to centre it on the world canvas."));
    m_resourceTree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_resourceTree, &QWidget::customContextMenuRequested, this, [this](const QPoint &pos) {
        QTreeWidgetItem *hit = m_resourceTree->itemAt(pos);
        const int resourceIndex = hit ? hit->data(0, Qt::UserRole).toInt() : -1;
        const bool hasResource = hit && hit->data(0, Qt::UserRole).isValid()
            && resourceIndex >= 0 && resourceIndex < m_resources.size();
        QTreeWidgetItem *target = hit;
        while (target && !target->data(0, Qt::UserRole + 1).isValid())
            target = target->parent();
        const QString category = target ? target->data(0, Qt::UserRole + 1).toString() : QString();
        const QString plane = target ? target->data(0, Qt::UserRole + 2).toString() : QString();
        if (category == QStringLiteral("playerstarts") || category == QStringLiteral("playerstart")) {
            const QString startId = hit ? hit->data(0, Qt::UserRole + 3).toString() : QString();
            QMenu startsMenu(this);
            QAction *add = startsMenu.addAction(tr("Add Player Start..."));
            QAction *change = nullptr, *removeStart = nullptr;
            if (!startId.isEmpty()) {
                change = startsMenu.addAction(tr("Edit Player Start..."));
                if (startId != QStringLiteral("default"))
                    removeStart = startsMenu.addAction(tr("Remove Player Start..."));
            }
            QAction *selected = startsMenu.exec(m_resourceTree->viewport()->mapToGlobal(pos));
            if (selected == add) {
                PlayerStartLocation created;
                created.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
                created.name = tr("Door %1 start").arg(m_otherPlayerStarts.size() + 1);
                created.x = m_playerStartX; created.y = m_playerStartY;
                created.facing = m_playerFacing;
                m_otherPlayerStarts.push_back(created);
                setDirty(); refreshResources(); rebuildScene();
                editPlayerStartLocation(created.id);
            } else if (selected == change) {
                editPlayerStartLocation(startId);
            } else if (removeStart && selected == removeStart) {
                if (QMessageBox::question(this, tr("Remove Player Start"),
                    tr("Remove this entrance? Doors targeting it will need another arrival location."),
                    QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes) {
                    for (int i = 0; i < m_otherPlayerStarts.size(); ++i)
                        if (m_otherPlayerStarts.at(i).id == startId) {
                            m_otherPlayerStarts.removeAt(i); break;
                        }
                    setDirty(); refreshResources(); rebuildScene();
                }
            }
            return;
        }
        QMenu menu(this);
        QAction *addSprite = menu.addAction(tr("Add Sprite..."));
        QAction *addAtlas = menu.addAction(tr("Add Tile Atlas..."));
        QAction *addEmpty = menu.addAction(tr("Add Empty Sprite"));
        QAction *addBackground = menu.addAction(tr("Add Background..."));
        QAction *addFrontPalette = menu.addAction(tr("Add Foreground Palette..."));
        QAction *addBackPalette = menu.addAction(tr("Add Background Palette..."));
        QAction *addSound = menu.addAction(tr("Add WAV Sound..."));
        QAction *addMusic = menu.addAction(tr("Add Music..."));
        menu.addSeparator();
        QAction *convertPng = menu.addAction(tr("Convert PNG → PPB..."));
        QAction *exportPng = nullptr;
        if (hasResource && QFileInfo(m_resources.at(resourceIndex).path).suffix().compare(
                QStringLiteral("ppb"), Qt::CaseInsensitive) == 0) {
            exportPng = menu.addAction(tr("Export This PPB as PNG..."));
            exportPng->setToolTip(tr("Export the selected PPB resource to PNG, preserving the embedded "
                "palette and alpha. Leaves the PPB and the resource reference unchanged."));
        }
        QAction *buildClut = menu.addAction(tr("Build Shared CLUT..."));
        QAction *useAsPreview = nullptr;
        QAction *editPalette = menu.addAction(tr("Palette Editor (Import / Export)..."));
        QAction *editTiles = menu.addAction(tr("Tilemap Editor (Graphics + Collisions)..."));
        QAction *exportTiles = menu.addAction(tr("Export Tilemap (.c / .map)..."));
        exportTiles->setEnabled(m_tilemapEnabled);
        QMenu *helpers = menu.addMenu(tr("Add Helper Code..."));
        const QString templateRoot = helperTemplatesRoot();
        for (const QString &folderName : {QStringLiteral("game"), QStringLiteral("gui")}) {
            QMenu *group = helpers->addMenu(folderName == QStringLiteral("game") ? tr("Game") : tr("GUI"));
            const QDir folder(templateRoot.isEmpty() ? QStringLiteral("__unavailable_codehelpers__")
                                                      : QDir(templateRoot).filePath(folderName));
            int count = 0;
            QStringList headers = folder.entryList({QStringLiteral("*.h")}, QDir::Files, QDir::Name);
            if (folderName == QStringLiteral("game"))
                headers.append(folder.entryList({QStringLiteral("*.ruleh")}, QDir::Files, QDir::Name));
            QSet<QString> offered;
            for (const QString &header : headers) {
                const QString base = QFileInfo(header).completeBaseName();
                if (offered.contains(base) || (folderName == QStringLiteral("game")
                     && (base == QStringLiteral("gameadventure") || base == QStringLiteral("gameworlditems") || base == QStringLiteral("maingame")
                         || base == QStringLiteral("gameassets") || base == QStringLiteral("splinepaths")
            || base == QStringLiteral("gameadventureempty")
                         || base == QStringLiteral("level1") || base == QStringLiteral("worldmap")
                         || base == QStringLiteral("embeddedresource")))) continue;
                const QString src = folderName == QStringLiteral("game")
                    ? GameHelperTemplates::sourcePath(folder, base, QStringLiteral(".c"))
                    : folder.filePath(base + QStringLiteral(".c"));
                if (!QFileInfo::exists(src)) continue;
                offered.insert(base);
                // Discover new helpers on every right-click. Optional <name>.ini
                // gives the menu a friendly title and tooltip for beginners.
                QSettings helperInfo(folder.filePath(base + QStringLiteral(".ini")),
                                     QSettings::IniFormat);
                QString label = helperInfo.value(QStringLiteral("Helper/name"))
                                    .toString().trimmed();
                if (label.isEmpty()) {
                    label = base;
                    label.replace(QLatin1Char('_'), QLatin1Char(' '));
                    label.replace(QLatin1Char('-'), QLatin1Char(' '));
                    if (!label.isEmpty()) label[0] = label.at(0).toUpper();
                }
                QAction *action = group->addAction(label + QStringLiteral("..."));
                const QString description = helperInfo.value(QStringLiteral("Helper/description"))
                                                .toString().trimmed();
                if (!description.isEmpty()) {
                    action->setToolTip(description);
                    action->setStatusTip(description);
                }
                action->setData(QStringLiteral("codehelper:%1/%2").arg(folderName, base));
                ++count;
            }
            if (!count) group->addAction(tr("No templates found"))->setEnabled(false);
        }
        helpers->setToolTip(templateRoot.isEmpty() ? tr("Could not find idelibs/codehelpers") : templateRoot);
        QAction *editThisPalette = nullptr;
        if (hasResource && m_resources.at(resourceIndex).kind == QStringLiteral("palette")) {
            menu.addSeparator();
            editThisPalette = menu.addAction(tr("Edit This Palette..."));
            const QString chosenPlane = m_resources.at(resourceIndex).plane;
            useAsPreview = menu.addAction(chosenPlane == QStringLiteral("background")
                ? tr("Use as Background Preview CLUT")
                : tr("Use as Foreground Preview CLUT"));
        }
        QAction *editSpriteAnimations = nullptr;
        QAction *configureObject = nullptr;
        QAction *moveToAtlas = nullptr;
        QAction *moveToSprite = nullptr;
        if (hasResource && m_resources.at(resourceIndex).kind == QStringLiteral("sprite")
            && m_resources.at(resourceIndex).objectType == QStringLiteral("decoration")
            && QFileInfo(m_resources.at(resourceIndex).path).suffix().compare(
                   QStringLiteral("ppb"), Qt::CaseInsensitive) == 0) {
            menu.addSeparator();
            moveToAtlas = menu.addAction(tr("Move to Tile Atlases (stop drawing)..."));
            moveToAtlas->setToolTip(tr("Keep the same PPB path and atlas references; remove only its canvas sprite."));
        }
        if (hasResource && m_resources.at(resourceIndex).kind == QStringLiteral("tileatlas")) {
            menu.addSeparator();
            moveToSprite = menu.addAction(tr("Move to Sprites (place on canvas)..."));
        }
        if (hasResource && m_resources.at(resourceIndex).kind == QStringLiteral("sprite")) {
            menu.addSeparator();
            editSpriteAnimations = menu.addAction(tr("Edit Sprite Animations..."));
            configureObject = menu.addAction(tr("Configure Game Object..."));
            configureObject->setToolTip(tr("Choose collectable, moving lift, conveyor or spring, plus animation and spline."));
        }
        QAction *copyWorldObject = nullptr;
        if (hasResource && m_resources.at(resourceIndex).kind == QStringLiteral("sprite")
            && m_resources.at(resourceIndex).objectType != QStringLiteral("decoration")) {
            copyWorldObject = menu.addAction(tr("Copy Game Object"));
            copyWorldObject->setToolTip(tr("Copy this object's behaviour and linked assets for another world."));
        }
        QAction *pasteWorldObject = menu.addAction(tr("Paste Game Object"));
        pasteWorldObject->setEnabled(s_hasCopiedWorldObject);
        pasteWorldObject->setToolTip(tr("Paste the copied object and import its linked sounds, music and spline."));
        QAction *editThisSpline = nullptr;
        const QString hitSplineId = hit ? hit->data(0, Qt::UserRole + 3).toString() : QString();
        if (category == QStringLiteral("spline") && !hitSplineId.isEmpty()) {
            menu.addSeparator();
            editThisSpline = menu.addAction(tr("Edit Spline Properties..."));
        }
        QAction *remove = nullptr;
        if (hasResource) {
            menu.addSeparator();
            remove = menu.addAction(tr("Remove Resource (file stays on disk)"));
        }
        // Put the likely action first through default highlighting.
        if (category == QStringLiteral("background")) menu.setDefaultAction(addBackground);
        else if (category == QStringLiteral("tileatlas")) menu.setDefaultAction(addAtlas);
        else if (category == QStringLiteral("sprite")) menu.setDefaultAction(addSprite);
        else if (category == QStringLiteral("palette"))
            menu.setDefaultAction(plane == QStringLiteral("background") ? addBackPalette : addFrontPalette);
        else if (category == QStringLiteral("sound")) menu.setDefaultAction(addSound);
        else if (category == QStringLiteral("music")) menu.setDefaultAction(addMusic);
        QAction *chosen = menu.exec(m_resourceTree->viewport()->mapToGlobal(pos));
        if (!chosen) return;
        if (chosen == addSprite) addResource(QStringLiteral("sprite"));
        else if (chosen == addAtlas) addResource(QStringLiteral("tileatlas"));
        else if (chosen == addEmpty) addPlaceholder();
        else if (chosen == addBackground) addResource(QStringLiteral("background"));
        else if (chosen == addFrontPalette) addResource(QStringLiteral("palette"), QStringLiteral("foreground"));
        else if (chosen == addBackPalette) addResource(QStringLiteral("palette"), QStringLiteral("background"));
        else if (chosen == addSound) addResource(QStringLiteral("sound"));
        else if (chosen == addMusic) addResource(QStringLiteral("music"));
        else if (chosen == convertPng) importPngAsPpb(category);
        else if (exportPng && chosen == exportPng) {
            const QString source = resolvedPath(m_resources.at(resourceIndex).path);
            SidboxPpb::Picture picture;
            QString issue;
            if (!SidboxPpb::read(source, &picture, &issue)) {
                QMessageBox::warning(this, tr("PPB → PNG failed"),
                    tr("Could not read the selected PPB resource:\n%1\n\n%2")
                        .arg(QDir::toNativeSeparators(source), issue));
            } else {
                QSettings preferences(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
                QString directory = preferences.value(QStringLiteral("files/ppbPngExportLastDirectory"),
                    QFileInfo(source).absolutePath()).toString();
                if (!QDir(directory).exists()) directory = QFileInfo(source).absolutePath();
                QString destination = QFileDialog::getSaveFileName(this, tr("Export PPB as PNG"),
                    QDir(directory).filePath(QFileInfo(source).completeBaseName() + QStringLiteral(".png")),
                    tr("PNG Images (*.png)"));
                if (!destination.isEmpty()) {
                    if (QFileInfo(destination).suffix().isEmpty()) destination += QStringLiteral(".png");
                    if (QFileInfo(destination).suffix().compare(QStringLiteral("png"), Qt::CaseInsensitive) != 0) {
                        QMessageBox::warning(this, tr("PPB → PNG"),
                            tr("Choose a .png filename. This export creates PNG images only."));
                    } else if (!SidboxPpb::exportPng(destination, picture, &issue)) {
                        QMessageBox::warning(this, tr("PPB → PNG failed"),
                            tr("The PPB was not modified.\n%1").arg(issue));
                    } else {
                        preferences.setValue(QStringLiteral("files/ppbPngExportLastDirectory"),
                            QFileInfo(destination).absolutePath());
                        QMessageBox::information(this, tr("PNG exported"),
                            tr("Saved %1 × %2 PNG with the embedded palette:\n%3")
                                .arg(picture.indexed.width()).arg(picture.indexed.height())
                                .arg(QDir::toNativeSeparators(destination)));
                    }
                }
            }
        }
        else if (chosen == buildClut) buildSharedPalette();
        else if (chosen == editPalette) openPaletteEditor(-1);
        else if (chosen == editTiles) openTilemapEditor();
        else if (chosen == exportTiles) exportTilemap(true);
        else if (chosen->data().toString().startsWith(QStringLiteral("codehelper:"))) {
            const QString ref = chosen->data().toString().mid(11);
            addCodeHelper(ref.section(QLatin1Char('/'), 0, 0), ref.section(QLatin1Char('/'), 1));
        }
        else if (copyWorldObject && chosen == copyWorldObject) copySelectedSprite(resourceIndex);
        else if (chosen == pasteWorldObject) pasteCopiedSprite();
        else if (configureObject && chosen == configureObject) configureGameObject(resourceIndex);
        else if (moveToAtlas && chosen == moveToAtlas) {
            if (QMessageBox::question(this, tr("Move Sprite to Tile Atlases"),
                tr("Move '%1' out of the game canvas and into Tile Atlases?\n\n"
                   "Its PPB file and the map's atlas reference are retained. "
                   "It will no longer be drawn as a sprite.\n\n"
                   "Any game code referring to its former sprite variable must be updated.")
                   .arg(m_resources.at(resourceIndex).name),
                QMessageBox::Yes | QMessageBox::No, QMessageBox::No) == QMessageBox::Yes) {
                rememberResourceEdit();
                m_resources[resourceIndex].kind = QStringLiteral("tileatlas");
                rebuildScene(); refreshResources(); selectResource(resourceIndex); setDirty();
            }
        }
        else if (moveToSprite && chosen == moveToSprite) {
            rememberResourceEdit();
            m_resources[resourceIndex].kind = QStringLiteral("sprite");
            rebuildScene(); refreshResources(); selectResource(resourceIndex); setDirty();
        }
        else if (editSpriteAnimations && chosen == editSpriteAnimations) openPlayerAnimationEditor(resourceIndex);
        else if (editThisSpline && chosen == editThisSpline) {
            for (int i = 0; i < m_splinePaths.size(); ++i) {
                if (m_splinePaths.at(i).id == hitSplineId) {
                    editSplineProperties(i);
                    break;
                }
            }
        }
        else if (editThisPalette && chosen == editThisPalette) openPaletteEditor(resourceIndex);
        else if (useAsPreview && chosen == useAsPreview) {
            const Resource &resource = m_resources.at(resourceIndex);
            if (resource.plane == QStringLiteral("background"))
                m_activeBackgroundPalette = resource.id;
            else m_activeForegroundPalette = resource.id;
            {
                QSignalBlocker block(m_forcePalette);
                m_forcePalette->setChecked(true);
            }
            m_previewPaletteAlpha->setEnabled(true);
            refreshResources();
            refreshPlanePreview();
            setDirty();
        }
        else if (remove) { selectResource(resourceIndex); deleteSelectedResource(); }
    });

    // Double-click opens the same editors as the context menus (including palettes).
    // Use persistent spline IDs: a refreshed tree can reorder its entries.
    connect(m_resourceTree, &QTreeWidget::itemDoubleClicked, this,
            [this](QTreeWidgetItem *item, int) {
        if (!item) return;
        const QString group = item->data(0, Qt::UserRole + 1).toString();
        if (group == QStringLiteral("playerstart")) {
            editPlayerStartLocation(item->data(0, Qt::UserRole + 3).toString()); return;
        }
        if (group == QStringLiteral("sprite") && item->data(0, Qt::UserRole).isValid()) {
            const int index = item->data(0, Qt::UserRole).toInt();
            if (index < 0 || index >= m_resources.size()) return;
            const Resource &sprite = m_resources.at(index);
            if (sprite.kind != QStringLiteral("sprite")) return;

            // Shift+double-click jumps to this sprite's existing Game Objects
            // alias. Do not create another object or modify the world data.
            if (QApplication::keyboardModifiers() & Qt::ShiftModifier) {
                if (sprite.objectType != QStringLiteral("decoration")) {
                    for (QTreeWidgetItemIterator it(m_resourceTree); *it; ++it) {
                        QTreeWidgetItem *alias = *it;
                        if (alias->data(0, Qt::UserRole + 1).toString() != QStringLiteral("gameobject")
                            || !alias->data(0, Qt::UserRole).isValid()
                            || alias->data(0, Qt::UserRole).toInt() != index) continue;
                        if (alias->parent()) alias->parent()->setExpanded(true);
                        m_resourceTree->setCurrentItem(alias);
                        m_resourceTree->scrollToItem(alias);
                        return;
                    }
                }
                return; // Shift on an ordinary sprite must not open Adventure.
            }

            // NPCs are referenced by a persistent sprite ID in the saved
            // Adventure definitions, independent of position or display name.
            for (const QJsonValue &value : m_adventure.value(QStringLiteral("npcs")).toArray()) {
                if (value.toObject().value(QStringLiteral("spriteId")).toString() == sprite.id) {
                    openAdventureEditor(sprite.id);
                    return;
                }
            }
            if (index < m_sceneItems.size() && m_sceneItems.at(index) && m_view) {
                m_view->centerOn(m_sceneItems.at(index)->sceneBoundingRect().center());
                // Editor navigation only: actual game camera and sprite coordinates unchanged.
                setDirty(); // World viewport centre is persisted in .sbgm.
            }
        } else if (group == QStringLiteral("gameobject") && item->data(0, Qt::UserRole).isValid()) {
            const int index = item->data(0, Qt::UserRole).toInt();
            if (index >= 0 && index < m_resources.size()
                && m_resources.at(index).kind == QStringLiteral("sprite"))
                configureGameObject(index);
        } else if (group == QStringLiteral("palette") && item->data(0, Qt::UserRole).isValid()) {
            // Only resource leaves have an index; double-clicking the Palette,
            // Foreground or Background headings must not open an empty editor.
            const int index = item->data(0, Qt::UserRole).toInt();
            if (index >= 0 && index < m_resources.size()
                && m_resources.at(index).kind == QStringLiteral("palette"))
                openPaletteEditor(index);
        } else if (group == QStringLiteral("spline")) {
            const QString splineId = item->data(0, Qt::UserRole + 3).toString();
            if (splineId.isEmpty()) return; // group header, not an actual spline
            for (int index = 0; index < m_splinePaths.size(); ++index) {
                if (m_splinePaths.at(index).id == splineId) {
                    editSplineProperties(index);
                    break;
                }
            }
        }
    });

    auto *previewPanel = new QWidget(splitter);
    auto *previewLayout = new QVBoxLayout(previewPanel);
    previewLayout->setContentsMargins(0, 4, 0, 0);
    auto *previewControls = new QHBoxLayout;
    auto *worldCanvasTitle = new QLabel(tr("WORLD CANVAS"), previewPanel);
    worldCanvasTitle->setToolTip(tr("The dashed frame shows the LCD viewport."));
    previewControls->addWidget(worldCanvasTitle);
    previewControls->addStretch();
    m_showLabels = new QCheckBox(tr("Asset tags"), previewPanel);
    m_showLabels->setChecked(true);
    previewControls->addWidget(m_showLabels);
    m_showWeatherPreview = new QCheckBox(tr("Weather"), previewPanel);
    m_showWeatherPreview->setChecked(true);
    m_showWeatherPreview->setToolTip(tr("Preview this world's rain, snow or thunderstorm on the LCD camera frame. "
        "Configure it under Player Start → WORLD WEATHER."));
    previewControls->addWidget(m_showWeatherPreview);
    connect(m_showWeatherPreview, &QCheckBox::toggled, this,
        [this](bool) { updateWeatherPreview(); });
    m_showParticlePreview = new QCheckBox(tr("Particles"), previewPanel);
    m_showParticlePreview->setChecked(true);
    m_showParticlePreview->setToolTip(tr("Animate ALL placed Particle Spawners together on the World Canvas at 50 Hz, "
        "even when another object is selected. Selection only changes the resize handles. "
        "Editor-only preview; no game rebuild or saved-world changes."));
    previewControls->addWidget(m_showParticlePreview);
    connect(m_showParticlePreview, &QCheckBox::toggled, this, [this](bool) {
        resetParticlePreview();
        updateParticlePreview();
    });
    m_showTilemap = new QCheckBox(tr("Show Tilemap"), previewPanel);
    m_showTilemap->setToolTip(tr("Show the attached tilemap artwork in world coordinates. "
                                 "The preview follows world zoom and panning; "
                                 "it does not change the exported game."));
    m_showTilemap->setChecked(false);
    m_showTilemap->setEnabled(false);
    previewControls->addWidget(m_showTilemap);
    m_showColourCycles = new QCheckBox(tr("Colour cycles"), previewPanel);
    m_showColourCycles->setToolTip(tr("Preview independent foreground/background palette cycles in the World Designer only. "
                                      "Requires indexed graphics; the palette editor configures the range and speed. "
                                      "Does not alter palette files or start cycling on SIDBOX."));
    previewControls->addWidget(m_showColourCycles);
    m_grid = new QCheckBox(tr("Grid 32"), previewPanel);
    m_grid->setChecked(true);
    previewControls->addWidget(m_grid);
    m_snap = new QCheckBox(tr("Snap"), previewPanel);
    m_snap->setChecked(true); // New designs default to 4-pixel snapping.
    m_snap->setToolTip(tr("Snap moved sprites/backgrounds to the selected world grid."));
    previewControls->addWidget(m_snap);
    m_snapStep = new GameComboBox(previewPanel);
    m_snapStep->addItems({QStringLiteral("4 px"),QStringLiteral("8 px"),
        QStringLiteral("16 px"),QStringLiteral("32 px"),QStringLiteral("64 px")});
    m_snapStep->setCurrentText(QStringLiteral("4 px"));
    previewControls->addWidget(m_snapStep);
    previewControls->addWidget(new QLabel(tr("Zoom:"), previewPanel));
    m_zoom = new GameComboBox(previewPanel);
    m_zoom->addItems({QStringLiteral("25%"), QStringLiteral("50%"),
                      QStringLiteral("75%"), QStringLiteral("100%"), QStringLiteral("200%"),
                      QStringLiteral("400%")});
    m_zoom->setCurrentText(QStringLiteral("100%"));
    previewControls->addWidget(m_zoom);
    previewLayout->addLayout(previewControls);
    m_scene = new GameScene(this);
    m_view = new QGraphicsView(m_scene, previewPanel);
    // A custom accent-coloured marquee handles selection from empty space.
    // Qt still handles dragging groups of selected QGraphicsPixmapItems.
    m_view->setDragMode(QGraphicsView::NoDrag);
    // Keep the user's world pan when splitter/tab resizing changes the viewport.
    m_view->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    m_view->setToolTip(tr("Middle-drag pans the view; mouse wheel changes zoom. "
                           "Left-drag empty space selects sprites; drag a selected sprite "
                           "to move the group. Right-click to create or edit splines."));
    m_view->setFocusPolicy(Qt::StrongFocus);
    m_view->installEventFilter(this);
    m_view->viewport()->installEventFilter(this);
    m_view->setRenderHint(QPainter::Antialiasing, false);
    m_view->setRenderHint(QPainter::SmoothPixmapTransform, false);
    m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    // Scrollbar thumb drags are another way to pan; mark the design modified
    // only for actual user slider moves, not scene rebuild/restore changes.
    connect(m_view->horizontalScrollBar(), &QScrollBar::sliderMoved,
            this, [this](int) { setDirty(); });
    connect(m_view->verticalScrollBar(), &QScrollBar::sliderMoved,
            this, [this](int) { setDirty(); });
    previewLayout->addWidget(m_view, 1);
    auto *instruction = new QLabel(tr("Middle-drag pans view. Left-drag empty space selects a group; "
        "drag selected sprites to move together. Ctrl/Shift adds selection; "
        "SPACE + left-drag moves camera. Ctrl+Z/Y undo/redo. "
        "Right-click edits splines."), previewPanel);
    instruction->setWordWrap(true);
    previewLayout->addWidget(instruction);

    // Audio settings are taller than graphics properties. Keep every control
    // accessible even at smaller screen sizes instead of clipping the bottom.
    auto *propertiesScroll = new QScrollArea(splitter);
    propertiesScroll->setWidgetResizable(true);
    propertiesScroll->setFrameShape(QFrame::NoFrame);
    // Return the right-hand properties pane to its pre-55B minimum.
    // The requested 50px reduction belongs to Game Resources on the LEFT.
    propertiesScroll->setMinimumWidth(225);
    auto *propertiesPanel = new QWidget(propertiesScroll);
    auto *propertiesLayout = new QVBoxLayout(propertiesPanel);
    propertiesLayout->setContentsMargins(5, 4, 5, 4);
    propertiesLayout->addWidget(new QLabel(tr("RESOURCE PROPERTIES"), propertiesPanel));
    auto *form = new QFormLayout;
    m_propertiesForm = form;
    // Match GUI Designer: every label sits ABOVE its control.
    // WrapAllRows also prevents long labels forcing the IDE to widen.
    form->setRowWrapPolicy(QFormLayout::WrapAllRows);
    form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    form->setVerticalSpacing(5);
    m_propName = new QLineEdit(propertiesPanel);
    m_propFile = new QLabel(propertiesPanel);
    m_propFile->setWordWrap(true);
    m_propFile->setTextInteractionFlags(Qt::TextSelectableByMouse);
    m_propX = new QSpinBox(propertiesPanel);
    m_propY = new QSpinBox(propertiesPanel);
    for (auto *spin : {m_propX, m_propY}) spin->setRange(-MAX_WORLD, MAX_WORLD);
    m_propScale = new QSpinBox(propertiesPanel);
    m_propScale->setRange(1, 800);
    m_propScale->setSuffix(QStringLiteral("%"));
    m_propCellWidth = new QSpinBox(propertiesPanel);
    m_propCellHeight = new QSpinBox(propertiesPanel);
    for (auto *spin : {m_propCellWidth, m_propCellHeight}) {
        spin->setRange(0, 16384);
        spin->setSpecialValueText(tr("Full atlas"));
    }
    m_propFrame = new QSpinBox(propertiesPanel);
    m_propFrame->setRange(0, 0);
    m_propLocked = new QCheckBox(tr("Lock position (no dragging)"), propertiesPanel);
    m_musicPlayOnStart = new QCheckBox(tr("Play on game start"), propertiesPanel);
    m_musicPlayOnStart->setToolTip(tr("Start this music automatically after gameassets_init() finishes loading. "
                                    "Only one Music resource can be selected. "
                                    "For another level, call its generated playmusic...() function when that level loads."));
    m_propPlane = new GameComboBox(propertiesPanel);
    m_propPlane->addItem(tr("Foreground"), QStringLiteral("foreground"));
    m_propPlane->addItem(tr("Background"), QStringLiteral("background"));
    m_propBackgroundMode = new GameComboBox(propertiesPanel);
    m_propBackgroundMode->addItem(tr("Sprite / blit (legacy)"), QStringLiteral("sprite"));
    m_propBackgroundMode->addItem(tr("Direct — prepared PPB"), QStringLiteral("direct_ready"));
    m_propBackgroundMode->addItem(tr("Direct — convert PPB"), QStringLiteral("direct_convert"));
    m_propBackgroundMode->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
    m_propBackgroundMode->setMinimumContentsLength(12);
    m_propBackgroundMode->setMinimumWidth(0);
    m_propBackgroundMode->setToolTip(tr("Direct buffer uses gfx_showbbuffer(). Column-major PPBs are already\n"
        "prepared for SIDBOX's x*height+y layout. Ordinary row-major PPBs need a\n"
        "transposition at runtime. This mode requires Dual-plane graphics."));
    m_imageInfo = new QLabel(propertiesPanel);
    m_imageInfo->setWordWrap(true);
    form->addRow(tr("Name"), m_propName);
    form->addRow(tr("Plane / palette bank"), m_propPlane);
    form->addRow(tr("Background rendering"), m_propBackgroundMode);
    form->addRow(tr("File"), m_propFile);
    // X and Y are one property row with labels above each spinbox.
    m_positionFields = new QWidget(propertiesPanel);
    auto *positionRow = new QHBoxLayout(m_positionFields);
    positionRow->setContentsMargins(0, 0, 0, 0);
    positionRow->setSpacing(6);
    auto addCoordinate = [propertiesPanel, positionRow](const QString &name, QSpinBox *spin) {
        auto *column = new QVBoxLayout;
        column->setContentsMargins(0, 0, 0, 0);
        column->setSpacing(2);
        column->addWidget(new QLabel(name, propertiesPanel));
        column->addWidget(spin);
        positionRow->addLayout(column, 1);
    };
    addCoordinate(tr("X"), m_propX);
    addCoordinate(tr("Y"), m_propY);
    form->addRow(m_positionFields);
    form->addRow(tr("Scale"), m_propScale);
    form->addRow(tr("Cell width"), m_propCellWidth);
    form->addRow(tr("Cell height"), m_propCellHeight);
    form->addRow(tr("Frame"), m_propFrame);
    form->addRow(QString(), m_propLocked);
    form->addRow(QString(), m_musicPlayOnStart);
    propertiesLayout->addLayout(form);
    propertiesLayout->addWidget(m_imageInfo);
    m_palettePreview = new QLabel(propertiesPanel);
    m_palettePreview->setFixedSize(128, 128);
    m_palettePreview->setToolTip(tr("Indexed colour palette: 16 × 16 entries, index 0 top-left"));
    m_palettePreview->hide();
    propertiesLayout->addWidget(m_palettePreview, 0, Qt::AlignLeft);
    m_editPaletteButton = new QPushButton(tr("Edit / Export Palette..."), propertiesPanel);
    m_editPaletteButton->setToolTip(tr("Open the selected .pal in the two-bank palette editor. "
        "Save As creates a new file; original sprites remain unchanged."));
    propertiesLayout->addWidget(m_editPaletteButton);
    connect(m_editPaletteButton, &QPushButton::clicked, this, [this]() {
        openPaletteEditor(selectedIndex());
    });
    connect(m_musicPlayOnStart, &QCheckBox::toggled, this, [this](bool enabled) {
        const int index = selectedIndex();
        if (m_loading || index < 0 || m_resources.at(index).kind != QStringLiteral("music")) return;
        if (m_resources.at(index).musicPlayOnStart == enabled) return;
        rememberResourceEdit();
        if (enabled) {
            for (Resource &other : m_resources)
                if (other.kind == QStringLiteral("music")) other.musicPlayOnStart = false;
        }
        m_resources[index].musicPlayOnStart = enabled;
        setDirty();
    });
    m_audioPanel = new SidboxGameAudioPanel(propertiesPanel);
    propertiesLayout->addWidget(m_audioPanel);
    m_audioPanel->settingsChanged = [this](const SidboxAudioSettings &settings) {
        const int index = selectedIndex();
        if (index < 0 || m_loading) return;
        Resource &r = m_resources[index];
        if (r.kind != QStringLiteral("sound") && r.kind != QStringLiteral("music")) return;
        rememberResourceEdit();
        r.audio = settings;
        setDirty();
    };
    auto *changeFile = new QPushButton(tr("Change File..."), propertiesPanel);
    propertiesLayout->addWidget(changeFile);
    auto *exportC = new QPushButton(tr("Export Embedded C..."), propertiesPanel);
    m_exportCButton = exportC;
    propertiesLayout->addWidget(exportC);
    m_deleteButton = new QPushButton(tr("Remove Resource"), propertiesPanel);
    propertiesLayout->addWidget(m_deleteButton);
    auto *limitations = new QLabel(tr("Embedded graphics export is optional. Audio settings are saved in the design; generated gamecode/ files are planned for Stage 55."), propertiesPanel);
    limitations->setWordWrap(true);
    propertiesLayout->addWidget(limitations);
    propertiesLayout->addStretch();
    splitter->addWidget(resourcesPanel);
    splitter->addWidget(previewPanel);
    // QScrollArea requires its child layout to exist before setWidget().
    propertiesScroll->setWidget(propertiesPanel);
    splitter->addWidget(propertiesScroll);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setStretchFactor(2, 0);
    splitter->setSizes({145, 760, 225});
    // V2 remembers the NEW narrower left pane. On first run, migrate the old
    // saved layout by borrowing 50px from the left; keep the right-hand pane
    // at its original minimum. Do not modify the parent IDE splitter.
    QTimer::singleShot(0, splitter, [splitter]() {
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        const QByteArray saved = settings.value(QStringLiteral("GameDesigner/mainSplitterStateV2")).toByteArray();
        if (!saved.isEmpty() && splitter->restoreState(saved)) return;
        const QByteArray previous = settings.value(QStringLiteral("GameDesigner/mainSplitterState")).toByteArray();
        if (!previous.isEmpty() && splitter->restoreState(previous)) {
            const QList<int> sizes = splitter->sizes();
            if (sizes.size() == 3) {
                const int total = sizes[0] + sizes[1] + sizes[2];
                const int left = qMax(125, sizes[0] - 50);
                const int right = qMax(225, sizes[2]);
                splitter->setSizes({left, qMax(200, total - left - right), right});
            }
        } else {
            splitter->setSizes({145, 760, 225});
        }
        settings.setValue(QStringLiteral("GameDesigner/mainSplitterStateV2"), splitter->saveState());
    });
    connect(splitter, &QSplitter::splitterMoved, this, [splitter](int, int) {
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        settings.setValue(QStringLiteral("GameDesigner/mainSplitterStateV2"), splitter->saveState());
    });

    connect(save, &QPushButton::clicked, this, [this]() { saveDesign(); });
    connect(generate, &QPushButton::clicked, this, [this]() { generateGameCode(); });
    connect(m_showLabels, &QCheckBox::toggled, this, [this](bool visible) {
        for (auto *item : m_sceneItems)
            if (item)
                for (auto *child : item->childItems())
                    if (auto *text = dynamic_cast<QGraphicsSimpleTextItem *>(child)) text->setVisible(visible);
        setDirty();
    });
    connect(m_planeMode, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int) {
        m_backPalette->setEnabled(m_planeMode->currentIndex() == 1);
        refreshPlanePreview(); setDirty();
    });
    for (QComboBox *combo : {m_frontPalette, m_backPalette}) {
        connect(combo, qOverload<int>(&QComboBox::currentIndexChanged), this, [this, combo](int) {
            if (m_loading) return;
            if (combo == m_frontPalette) m_activeForegroundPalette = combo->currentData().toString();
            else m_activeBackgroundPalette = combo->currentData().toString();
            refreshResources();
            refreshPlanePreview(); setDirty();
        });
    }
    connect(m_forcePalette, &QCheckBox::toggled, this, [this](bool checked) {
        m_previewPaletteAlpha->setEnabled(checked);
        refreshPlanePreview(); setDirty();
    });
    m_previewPaletteAlpha->setEnabled(m_forcePalette->isChecked());
    connect(m_previewPaletteAlpha, &QCheckBox::toggled, this, [this](bool) {
        refreshPlanePreview(); setDirty();
    });
    connect(m_buildPaletteButton, &QPushButton::clicked, this, [this]() { buildSharedPalette(); });
    connect(m_propPlane, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int) {
        if (m_loading) return;
        const int index = selectedIndex();
        if (index < 0) return;
        const QString plane = m_propPlane->currentData().toString();
        if (m_resources[index].plane == plane) return;
        rememberResourceEdit();
        m_resources[index].plane = plane;
        refreshResources(); selectResource(index);
        refreshPlanePreview(); setDirty();
    });
    connect(focusCamera, &QPushButton::clicked, this, [this]() {
        m_view->centerOn(m_cameraX->value() + LCD_WIDTH / 2,
                         m_cameraY->value() + LCD_HEIGHT / 2);
    });
    connect(editTilemap, &QPushButton::clicked, this, [this]() { openTilemapEditor(); });
    connect(exportC, &QPushButton::clicked, this, [this]() { exportSelectedC(); });
    connect(m_deleteButton, &QPushButton::clicked, this, [this]() { deleteSelectedResource(); });
    connect(m_propBackgroundMode, qOverload<int>(&QComboBox::currentIndexChanged), this, [this](int) {
        if (m_loading) return;
        const int index = selectedIndex();
        if (index < 0 || m_resources.at(index).kind != QStringLiteral("background")) return;
        const QString mode = m_propBackgroundMode->currentData().toString();
        if (m_resources.at(index).backgroundMode == mode) return;
        rememberResourceEdit();
        m_resources[index].backgroundMode = mode;
        updateSelectedPixmap();
        setDirty();
    });
    connect(m_propLocked, &QCheckBox::toggled, this, [this](bool locked) {
        const int index = selectedIndex();
        if (index < 0 || m_loading || !visualKind(m_resources[index].kind)) return;
        rememberResourceEdit();
        m_resources[index].locked = locked;
        if (index < m_sceneItems.size() && m_sceneItems[index])
            m_sceneItems[index]->setFlag(QGraphicsItem::ItemIsMovable, !locked);
        setDirty();
        refreshProperties();
    });
    connect(m_snap, &QCheckBox::toggled, this, [this](bool) { setDirty(); });
    connect(m_snapStep, &QComboBox::currentTextChanged, this, [this](const QString &) { setDirty(); });
    connect(changeFile, &QPushButton::clicked, this, [this]() { pickResourceFile(); });
    connect(m_worldWidth, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
        refreshFrame(); setDirty();
    });
    connect(m_worldHeight, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
        refreshFrame(); setDirty();
    });
    connect(m_cameraX, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
        refreshFrame(); setDirty();
    });
    connect(m_cameraY, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
        refreshFrame(); setDirty();
    });
    connect(m_showTilemap, &QCheckBox::toggled, this, [this](bool) {
        rebuildTilemapOverlay();
        refreshFrame();
        setDirty();
    });
    connect(m_showColourCycles, &QCheckBox::toggled, this, [this](bool) {
        m_frontCyclePhase = m_backCyclePhase = 0;
        m_lastFrontCyclePhase = m_lastBackCyclePhase = -1;
        refreshPlanePreview();
        setDirty();
    });
    connect(m_grid, &QCheckBox::toggled, this, [this](bool checked) {
        static_cast<GameScene *>(m_scene)->drawGrid = checked;
        m_scene->update();
    });
    connect(m_zoom, &QComboBox::currentTextChanged, this, [this](const QString &value) {
        bool ok = false;
        const int percent = value.left(value.size() - 1).toInt(&ok);
        if (ok) {
            m_view->resetTransform();
            m_view->scale(percent / 100.0, percent / 100.0);
            setDirty(); // Zoom is persisted in the .sbgm, like the view centre.
        }
    });
    // Initial 100%: one world pixel = one screen pixel.
    m_view->resetTransform();
    connect(m_resourceTree, &QTreeWidget::itemSelectionChanged, this, [this]() {
        if (m_syncSelection) return;
        QTreeWidgetItem *item = m_resourceTree->currentItem();
        if (item && item->data(0, Qt::UserRole + 1).toString() == QStringLiteral("spline")
            && item->data(0, Qt::UserRole + 3).isValid()) {
            const QString splineId = item->data(0, Qt::UserRole + 3).toString();
            for (int i = 0; i < m_splinePaths.size(); ++i) {
                if (m_splinePaths.at(i).id != splineId) continue;
                if (m_activeSpline != i) {
                    m_activeSpline = i;
                    rebuildSplineOverlay();
                    setDirty(); // Active spline is persisted in the design.
                }
                QRectF bounds;
                for (const QPoint &point : m_splinePaths.at(i).points)
                    bounds |= QRectF(QPointF(point), QSizeF(1, 1));
                m_scene->clearSelection();
                refreshProperties();
                refreshObjectHitbox();
                if (m_view && bounds.isValid()) m_view->centerOn(bounds.center());
                return;
            }
        }
        if (!item || !item->data(0, Qt::UserRole).isValid()) {
            refreshObjectHitbox();
            return;
        }
        const bool focusObject = item->data(0, Qt::UserRole + 1).toString()
            == QStringLiteral("gameobject");
        const int index = item->data(0, Qt::UserRole).toInt();
        if (index >= 0 && index < m_sceneItems.size() && m_sceneItems.at(index)) {
            m_syncSelection = true;
            m_scene->clearSelection();
            m_sceneItems.at(index)->setSelected(true);
            m_syncSelection = false;
        }
        refreshProperties();
        refreshObjectHitbox();
        if (focusObject && m_view && index >= 0 && index < m_sceneItems.size()
            && m_sceneItems.at(index))
            m_view->centerOn(m_sceneItems.at(index)->sceneBoundingRect().center());
    });
    connect(m_scene, &QGraphicsScene::selectionChanged, this, [this]() {
        // Do NOT call selectResource() here: it clears all other selected
        // QGraphicsItems and makes marquee/group dragging impossible.
        syncCanvasSelection();
    });
    connect(m_propName, &QLineEdit::textEdited, this, [this](const QString &text) {
        const int index = selectedIndex();
        if (index < 0) return;
        rememberResourceEdit();
        m_resources[index].name = text;
        // The same configured sprite is visible under Sprites and Game Objects.
        // Rename both entries without rebuilding the tree on each keystroke.
        // Resort only the affected child groups after the iterator finishes.
        QSet<QTreeWidgetItem *> renamedParents;
        for (QTreeWidgetItemIterator it(m_resourceTree); *it; ++it) {
            QTreeWidgetItem *item = *it;
            const QVariant resource = item->data(0, Qt::UserRole);
            if (!resource.isValid() || resource.toInt() != index) continue;
            const QString group = item->data(0, Qt::UserRole + 1).toString();
            if (group == QStringLiteral("sprite") || group == QStringLiteral("gameobject")) {
                const Resource &r = m_resources.at(index);
                QString title = text;
                if (r.kind == QStringLiteral("sprite") && r.objectType != QStringLiteral("decoration"))
                    title += QStringLiteral("  [%1]").arg(r.objectType);
                if (group == QStringLiteral("sprite")) {
                    for (const QJsonValue &value : m_adventure.value(QStringLiteral("npcs")).toArray()) {
                        if (value.toObject().value(QStringLiteral("spriteId")).toString() == r.id) {
                            title += QStringLiteral("  [NPC]");
                            break;
                        }
                    }
                }
                item->setText(0, title);
            } else if (group != QStringLiteral("spline")) {
                item->setText(0, text);
            }
            if (item->parent()) renamedParents.insert(item->parent());
        }
        // Do not let visual row moves trigger a canvas/tree selection sync.
        QSignalBlocker blockTreeWhileSorting(m_resourceTree);
        for (QTreeWidgetItem *parent : renamedParents)
            parent->sortChildren(0, Qt::AscendingOrder);
        if (index < m_sceneItems.size() && m_sceneItems.at(index)) {
            for (auto *child : m_sceneItems.at(index)->childItems())
                if (auto *label = dynamic_cast<QGraphicsSimpleTextItem *>(child))
                    label->setText(text);
        }
        // Keep the cursor position while the developer edits the name.
        setDirty();
    });
    for (QSpinBox *spin : {m_propX, m_propY, m_propScale}) {
        connect(spin, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
            const int index = selectedIndex();
            if (index < 0 || m_loading) return;
            rememberResourceEdit();
            auto &r = m_resources[index];
            r.x = m_propX->value(); r.y = m_propY->value(); r.scale = m_propScale->value();
            updateSelectedItem();
            setDirty();
        });
    }
    for (QSpinBox *spin : {m_propCellWidth, m_propCellHeight, m_propFrame}) {
        connect(spin, qOverload<int>(&QSpinBox::valueChanged), this, [this](int) {
            const int index = selectedIndex();
            if (index < 0 || m_loading) return;
            rememberResourceEdit();
            auto &r = m_resources[index];
            r.cellWidth = m_propCellWidth->value();
            r.cellHeight = m_propCellHeight->value();
            r.frame = m_propFrame->value();
            updateSelectedPixmap();
            setDirty();
            refreshProperties();
        });
    }
    refreshResources();
    refreshProperties();
}

QString SidboxGameDesigner::resolvedPath(const QString &path) const
{
    if (path.isEmpty()) return {};
    return QFileInfo(QDir(QFileInfo(m_filePath).absolutePath()).filePath(path)).absoluteFilePath();
}
QString SidboxGameDesigner::storedPath(const QString &path) const
{
    return QDir(QFileInfo(m_filePath).absolutePath()).relativeFilePath(QFileInfo(path).absoluteFilePath());
}

int SidboxGameDesigner::selectedIndex() const
{
    if (!m_resourceTree || !m_resourceTree->currentItem()) return -1;
    const QVariant value = m_resourceTree->currentItem()->data(0, Qt::UserRole);
    if (!value.isValid()) return -1;
    const int index = value.toInt();
    return index >= 0 && index < m_resources.size() ? index : -1;
}

// Keep the properties/tree focused on one of the selected sprites WITHOUT
// collapsing the QGraphicsScene multi-selection. Selection is editor state,
// not a change to the exported game or the undo history.
void SidboxGameDesigner::syncCanvasSelection()
{
    if (m_syncSelection || m_loading || !m_scene || !m_resourceTree) return;
    const QList<QGraphicsItem *> selected = m_scene->selectedItems();
    const int preferred = selectedIndex();
    int primary = -1;
    for (QGraphicsItem *item : selected) {
        if (!item || !item->data(0).isValid()) continue;
        const int id = item->data(0).toInt();
        if (id < 0 || id >= m_resources.size()) continue;
        if (id == preferred) { primary = id; break; }
        if (primary < 0) primary = id;
    }
    {
        QSignalBlocker block(m_resourceTree);
        m_syncSelection = true;
        if (primary < 0) {
            m_resourceTree->setCurrentItem(nullptr);
            m_resourceTree->clearSelection();
        } else {
            // Canvas picks a configured sprite's Game Objects alias, not its
            // Sprites alias. Both remain independently selectable in the tree.
            const QString desiredGroup = (m_resources.at(primary).kind == QStringLiteral("sprite")
                && m_resources.at(primary).objectType != QStringLiteral("decoration"))
                ? QStringLiteral("gameobject") : m_resources.at(primary).kind;
            const QString currentGroup = m_resourceTree->currentItem()
                ? m_resourceTree->currentItem()->data(0, Qt::UserRole + 1).toString() : QString();
            if (primary != preferred || currentGroup != desiredGroup) {
                for (QTreeWidgetItemIterator it(m_resourceTree); *it; ++it) {
                    QTreeWidgetItem *row = *it;
                    if (row->data(0, Qt::UserRole).isValid()
                        && row->data(0, Qt::UserRole).toInt() == primary
                        && row->data(0, Qt::UserRole + 1).toString() == desiredGroup) {
                        if (row->parent()) row->parent()->setExpanded(true);
                        m_resourceTree->setCurrentItem(row);
                        m_resourceTree->scrollToItem(row);
                        break;
                    }
                }
            }
        }
        m_syncSelection = false;
    }
    refreshProperties();
    refreshObjectHitbox();
}

void SidboxGameDesigner::selectResource(int index)
{
    if (index < 0 || index >= m_resources.size()) return;
    m_syncSelection = true;
    if (selectedIndex() != index) {
        for (QTreeWidgetItemIterator iterator(m_resourceTree); *iterator; ++iterator) {
            auto *child = *iterator;
            const QVariant value = child->data(0, Qt::UserRole);
            if (value.isValid() && value.toInt() == index) {
                m_resourceTree->setCurrentItem(child);
                break;
            }
        }
    }
    m_scene->clearSelection();
    if (index < m_sceneItems.size() && m_sceneItems.at(index))
        m_sceneItems.at(index)->setSelected(true);
    m_syncSelection = false;
    refreshProperties();
    refreshObjectHitbox();
}

QString SidboxGameDesigner::resourcePlane(const Resource &resource) const
{
    if (m_planeMode->currentIndex() == 0) return QStringLiteral("foreground");
    return resource.plane == QStringLiteral("background")
        ? QStringLiteral("background") : QStringLiteral("foreground");
}

QVector<QRgb> SidboxGameDesigner::activePalette(const QString &plane) const
{
    if (plane == QStringLiteral("background") && m_planeMode->currentIndex() == 0)
        return {};
    const QString id = plane == QStringLiteral("background")
        ? m_activeBackgroundPalette : m_activeForegroundPalette;
    if (id.isEmpty()) return {};
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("palette") || r.id != id || r.plane != plane) continue;
        const QString absolute = resolvedPath(r.path);
        const QFileInfo info(absolute);
        if (!info.isFile()) return {};
        const QString key = absolute + QLatin1Char('|') + plane;
        const auto found = m_paletteCache.constFind(key);
        if (found != m_paletteCache.constEnd()
            && found->modified == info.lastModified() && found->diskSize == info.size())
            return found->colours;
        const QVector<QRgb> bank = SidboxGamePalette::readPalette(
            absolute, plane == QStringLiteral("background"));
        if (m_paletteCache.size() > 32) m_paletteCache.clear();
        m_paletteCache.insert(key, CachedPalette{bank, info.lastModified(), info.size()});
        return bank;
    }
    return {};
}

void SidboxGameDesigner::refreshPaletteSelectors()
{
    QSignalBlocker blockFront(m_frontPalette), blockBack(m_backPalette);
    for (auto *combo : {m_frontPalette, m_backPalette}) {
        combo->clear();
        combo->addItem(tr("None — individual PPB palettes"), QString());
    }
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("palette")) continue;
        QComboBox *target = r.plane == QStringLiteral("background") ? m_backPalette : m_frontPalette;
        const QString sourceName = QFileInfo(r.path).fileName();
        target->addItem(sourceName.isEmpty() || sourceName == r.name
                            ? r.name : tr("%1  (%2)").arg(r.name, sourceName), r.id);
        target->setItemData(target->count() - 1, resolvedPath(r.path), Qt::ToolTipRole);
    }
    auto selectId = [](QComboBox *combo, QString &id) {
        const int found = combo->findData(id);
        if (found >= 0) combo->setCurrentIndex(found);
        else { id.clear(); combo->setCurrentIndex(0); }
    };
    selectId(m_frontPalette, m_activeForegroundPalette);
    selectId(m_backPalette, m_activeBackgroundPalette);
    m_backPalette->setEnabled(m_planeMode->currentIndex() == 1);
}

void SidboxGameDesigner::refreshPlanePreview()
{
    if (m_loading || !m_scene) return;
    const int index = selectedIndex();
    rebuildScene();
    if (index >= 0) selectResource(index);
    else refreshProperties();
}

void SidboxGameDesigner::refreshResources()
{
    const int preserve = selectedIndex();
    const QString selectedGroup = m_resourceTree->currentItem()
        ? m_resourceTree->currentItem()->data(0, Qt::UserRole + 1).toString() : QString();
    const QString selectedSpline = (selectedGroup == QStringLiteral("spline"))
        ? m_resourceTree->currentItem()->data(0, Qt::UserRole + 3).toString() : QString();
    // Start every group closed, but remember the user's current expansion
    // across updates (e.g. when adding, renaming or configuring resources).
    // Palette's Foreground/Background subgroups have their own state.
    QHash<QString, bool> expandedGroups;
    for (int i = 0; i < m_resourceTree->topLevelItemCount(); ++i) {
        const QTreeWidgetItem *oldRoot = m_resourceTree->topLevelItem(i);
        const QString key = oldRoot->data(0, Qt::UserRole + 1).toString();
        if (key.isEmpty()) continue;
        expandedGroups.insert(key, oldRoot->isExpanded());
        if (key == QStringLiteral("palette")) {
            for (int n = 0; n < oldRoot->childCount(); ++n) {
                const QTreeWidgetItem *sub = oldRoot->child(n);
                const QString plane = sub->data(0, Qt::UserRole + 2).toString();
                if (!plane.isEmpty())
                    expandedGroups.insert(QStringLiteral("palette/") + plane,
                                          sub->isExpanded());
            }
        }
    }
    const auto treeIcon = [](const QString &kind) -> QIcon {
        if (kind == QStringLiteral("sprite") || kind == QStringLiteral("tileatlas"))
            return gameResourceIcon(QStringLiteral("gr_icon_sprite.png"));
        if (kind == QStringLiteral("background")) return gameResourceIcon(QStringLiteral("gr_icon_background.png"));
        if (kind == QStringLiteral("palette")) return gameResourceIcon(QStringLiteral("gr_icon_palette.png"));
        if (kind == QStringLiteral("sound") || kind == QStringLiteral("music"))
            return gameResourceIcon(QStringLiteral("gr_icon_audio.png"));
        if (kind == QStringLiteral("gameobject")) return gameResourceIcon(QStringLiteral("gr_icon_object.png"));
        if (kind == QStringLiteral("spline")) return gameResourceIcon(QStringLiteral("gr_icon_spline.png"));
        if (kind == QStringLiteral("playerstart")) return gameResourceIcon(QStringLiteral("gr_icon_playerstart.png"));
        return QIcon();
    };
    QSignalBlocker block(m_resourceTree);
    m_resourceTree->clear();
    auto *startsRoot = new QTreeWidgetItem(m_resourceTree, QStringList{tr("Player Starts")});
    startsRoot->setData(0, Qt::UserRole + 1, QStringLiteral("playerstarts"));
    startsRoot->setToolTip(0, tr("Right-click to add another entrance position."));
    startsRoot->setExpanded(expandedGroups.value(QStringLiteral("playerstarts"), true));
    startsRoot->setIcon(0, treeIcon(QStringLiteral("playerstart")));
    auto *playerStart = new QTreeWidgetItem(startsRoot, QStringList{
        tr("Default start (%1, %2)").arg(m_playerStartX).arg(m_playerStartY)});
    playerStart->setData(0, Qt::UserRole + 1, QStringLiteral("playerstart"));
    playerStart->setData(0, Qt::UserRole + 3, QStringLiteral("default"));
    playerStart->setToolTip(0, tr("Required default entrance; cannot be removed. Double-click to edit."));
    playerStart->setIcon(0, treeIcon(QStringLiteral("playerstart")));
    for (const PlayerStartLocation &location : m_otherPlayerStarts) {
        auto *entry = new QTreeWidgetItem(startsRoot, QStringList{
            QStringLiteral("%1 (%2, %3)").arg(location.name).arg(location.x).arg(location.y)});
        entry->setData(0, Qt::UserRole + 1, QStringLiteral("playerstart"));
        entry->setData(0, Qt::UserRole + 3, location.id);
        entry->setIcon(0, treeIcon(QStringLiteral("playerstart")));
        entry->setToolTip(0, tr("Double-click to edit. Right-click to remove with confirmation."));
    }
    startsRoot->sortChildren(0, Qt::AscendingOrder);
    for (const QString &kind : {QStringLiteral("sprite"), QStringLiteral("tileatlas"),
                                 QStringLiteral("background"), QStringLiteral("palette"),
                                 QStringLiteral("sound"), QStringLiteral("music")}) {
        auto *root = new QTreeWidgetItem(m_resourceTree, QStringList{kindTitle(kind)});
        root->setIcon(0, treeIcon(kind));
        root->setFlags(root->flags() & ~Qt::ItemIsSelectable);
        root->setData(0, Qt::UserRole + 1, kind);
        QTreeWidgetItem *frontRoot = nullptr;
        QTreeWidgetItem *backRoot = nullptr;
        if (kind == QStringLiteral("palette")) {
            frontRoot = new QTreeWidgetItem(root, QStringList{tr("Foreground")});
            frontRoot->setFlags(frontRoot->flags() & ~Qt::ItemIsSelectable);
            frontRoot->setData(0, Qt::UserRole + 1, kind);
            frontRoot->setData(0, Qt::UserRole + 2, QStringLiteral("foreground"));
            backRoot = new QTreeWidgetItem(root, QStringList{tr("Background")});
            backRoot->setFlags(backRoot->flags() & ~Qt::ItemIsSelectable);
            backRoot->setData(0, Qt::UserRole + 1, kind);
            backRoot->setData(0, Qt::UserRole + 2, QStringLiteral("background"));
            frontRoot->setIcon(0, treeIcon(kind));
            backRoot->setIcon(0, treeIcon(kind));
            frontRoot->setExpanded(expandedGroups.value(QStringLiteral("palette/foreground"), false));
            backRoot->setExpanded(expandedGroups.value(QStringLiteral("palette/background"), false));
        }
        for (int index = 0; index < m_resources.size(); ++index) {
            const Resource &r = m_resources.at(index);
            if (r.kind != kind) continue;
            QTreeWidgetItem *parent = kind == QStringLiteral("palette")
                ? (r.plane == QStringLiteral("background") ? backRoot : frontRoot) : root;
            const bool isActiveClut = kind == QStringLiteral("palette") &&
                (r.plane == QStringLiteral("background")
                     ? r.id == m_activeBackgroundPalette
                     : r.id == m_activeForegroundPalette);
            auto *child = new QTreeWidgetItem(parent, QStringList{
                isActiveClut ? tr("%1  [preview]").arg(r.name) : r.name});
            child->setData(0, Qt::UserRole, index);
            child->setIcon(0, treeIcon(kind));
            child->setToolTip(0, r.path);
            if (kind == QStringLiteral("sprite")) {
                bool isNpc = false;
                for (const QJsonValue &value : m_adventure.value(QStringLiteral("npcs")).toArray()) {
                    if (value.toObject().value(QStringLiteral("spriteId")).toString() == r.id) {
                        isNpc = true;
                        break;
                    }
                }
                QString title = r.name;
                if (r.objectType != QStringLiteral("decoration"))
                    title += QStringLiteral("  [%1]").arg(r.objectType);
                if (isNpc) title += QStringLiteral("  [NPC]");
                child->setText(0, title);
                if (r.objectType != QStringLiteral("decoration"))
                    child->setToolTip(0, tr("Game object: %1\n%2").arg(r.objectType, r.path));
                if (isNpc)
                    child->setToolTip(0, child->toolTip(0) + tr("\nNPC: Double-click to open Adventure Editor on this NPC."));
            }
            child->setData(0, Qt::UserRole + 1, kind);
            child->setData(0, Qt::UserRole + 2, r.plane);
        }
        // Alphabetise children, not the nine fixed top-level categories.
        // Under Palettes, sort the two plane groups and their own resources.
        if (frontRoot) {
            frontRoot->sortChildren(0, Qt::AscendingOrder);
            backRoot->sortChildren(0, Qt::AscendingOrder);
        }
        root->sortChildren(0, Qt::AscendingOrder);
        if (kind == QStringLiteral("music")) {
            qint64 largest = 0;
            int count = 0;
            for (const Resource &r : m_resources) {
                if (r.kind != kind) continue;
                const QFileInfo info(resolvedPath(r.path));
                if (!info.isFile()) continue;
                largest = qMax(largest, info.size());
                ++count;
            }
            root->setText(0, tr("Music (%1; largest %2 KiB)")
                .arg(count).arg((largest + 1023) / 1024));
            root->setToolTip(0, tr("Project Settings → MOD size can reserve space for the largest module."));
        }
        root->setExpanded(expandedGroups.value(kind, false));
    }
    // Navigation aliases: the same sprite instance also remains under Sprites.
    // No extra resource is created and nothing changes in the saved .sbgm.
    auto *objectsRoot = new QTreeWidgetItem(m_resourceTree, QStringList{tr("Game Objects")});
    objectsRoot->setIcon(0, treeIcon(QStringLiteral("gameobject")));
    objectsRoot->setFlags(objectsRoot->flags() & ~Qt::ItemIsSelectable);
    objectsRoot->setData(0, Qt::UserRole + 1, QStringLiteral("gameobject"));
    for (int i = 0; i < m_resources.size(); ++i) {
        const Resource &r = m_resources.at(i);
        if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")) continue;
        auto *item = new QTreeWidgetItem(objectsRoot,
            QStringList{tr("%1  [%2]").arg(r.name, r.objectType)});
        item->setData(0, Qt::UserRole, i);
        item->setIcon(0, treeIcon(QStringLiteral("gameobject")));
        item->setData(0, Qt::UserRole + 1, QStringLiteral("gameobject"));
        item->setToolTip(0, tr("Select and centre the canvas on %1").arg(r.name));
    }
    objectsRoot->sortChildren(0, Qt::AscendingOrder);
    objectsRoot->setExpanded(expandedGroups.value(QStringLiteral("gameobject"), false));

    auto *splinesRoot = new QTreeWidgetItem(m_resourceTree, QStringList{tr("Splines")});
    splinesRoot->setIcon(0, treeIcon(QStringLiteral("spline")));
    splinesRoot->setFlags(splinesRoot->flags() & ~Qt::ItemIsSelectable);
    splinesRoot->setData(0, Qt::UserRole + 1, QStringLiteral("spline"));
    for (const SplinePath &path : m_splinePaths) {
        auto *item = new QTreeWidgetItem(splinesRoot, QStringList{path.name});
        item->setData(0, Qt::UserRole + 1, QStringLiteral("spline"));
        item->setData(0, Qt::UserRole + 3, path.id);
        item->setIcon(0, treeIcon(QStringLiteral("spline")));
        item->setToolTip(0, tr("Select this spline and centre its points in the canvas"));
    }
    splinesRoot->sortChildren(0, Qt::AscendingOrder);
    splinesRoot->setExpanded(expandedGroups.value(QStringLiteral("spline"), false));

    refreshPaletteSelectors();
    if (!selectedSpline.isEmpty()) {
        for (int i = 0; i < splinesRoot->childCount(); ++i) {
            QTreeWidgetItem *item = splinesRoot->child(i);
            if (item->data(0, Qt::UserRole + 3).toString() == selectedSpline) {
                m_resourceTree->setCurrentItem(item);
                return;
            }
        }
    }
    if (preserve >= 0 && preserve < m_resources.size()) {
        if (selectedGroup == QStringLiteral("gameobject")) {
            for (int i = 0; i < objectsRoot->childCount(); ++i) {
                QTreeWidgetItem *item = objectsRoot->child(i);
                if (item->data(0, Qt::UserRole).toInt() == preserve) {
                    m_resourceTree->setCurrentItem(item);
                    return;
                }
            }
        }
        selectResource(preserve);
    }
}

QImage SidboxGameDesigner::cachedImage(const QString &path, QString *error) const
{
    if (path.isEmpty()) { if (error) *error = tr("No image file selected"); return {}; }
    const QFileInfo info(path);
    if (!info.isFile()) { if (error) *error = tr("Image file not found"); return {}; }
    const auto found = m_imageCache.constFind(path);
    if (found != m_imageCache.constEnd()
        && found->diskSize == info.size() && found->modified == info.lastModified()) {
        // Reused immutable Qt image data: no disk read, PPB parsing or PNG decode.
        return found->image;
    }
    if (found != m_imageCache.constEnd()) {
        m_imageCacheBytes -= found->memoryBytes;
        m_imageCache.remove(path);
        m_imageCacheOrder.removeAll(path);
    }
    QImage image;
    if (info.suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) == 0) {
        SidboxPpb::Picture ppb;
        QString loadError;
        if (!SidboxPpb::read(path, &ppb, &loadError)) {
            if (error) *error = tr("PPB: %1").arg(loadError);
            return {};
        }
        image = ppb.indexed;
    } else {
        QImageReader reader(path);
        reader.setAutoTransform(true);
        image = reader.read();
        if (image.isNull()) {
            if (error) *error = tr("Cannot preview: %1").arg(reader.errorString());
            return {};
        }
    }
    constexpr qint64 MaxCacheBytes = 64LL * 1024 * 1024;
    const qint64 bytes = qint64(image.sizeInBytes());
    if (bytes <= MaxCacheBytes) {
        while (!m_imageCacheOrder.isEmpty()
               && (m_imageCacheBytes + bytes > MaxCacheBytes || m_imageCache.size() >= 32)) {
            const QString oldest = m_imageCacheOrder.takeFirst();
            const auto existing = m_imageCache.constFind(oldest);
            if (existing != m_imageCache.constEnd()) {
                m_imageCacheBytes -= existing->memoryBytes;
                m_imageCache.remove(oldest);
            }
        }
        m_imageCache.insert(path, CachedImage{image, info.lastModified(), info.size(), bytes});
        m_imageCacheOrder.append(path);
        m_imageCacheBytes += bytes;
    }
    return image;
}

QImage SidboxGameDesigner::resourcePreview(const Resource &r, QString *details) const
{
    QString error;
    const QImage source = cachedImage(resolvedPath(r.path), &error);
    if (source.isNull()) { if (details) *details = error; return {}; }
    // Editor PREVIEW ONLY for pre-oriented background data: mirror X, then
    // rotate 90 degrees anticlockwise (transpose the displayed pixel matrix).
    // The Stage 55B stride-based reinterpretation kept the old width/height,
    // interleaving rows and making the image look broken in the designer.
    // A geometric transformation swaps the preview dimensions and leaves the
    // PPB bytes, palette indices, and generated V1 framebuffer code untouched.
    // The direct_convert mode already starts from an upright source and must
    // NOT receive this display transform.
    QImage visible = source;
    if (r.kind == QStringLiteral("sprite") && r.spriteStamp.active()) {
        visible = r.spriteStamp.compose(source, &error);
        if (visible.isNull()) { if (details) *details = error; return {}; }
    }
    if (r.kind == QStringLiteral("background") && r.backgroundMode == QStringLiteral("direct_ready")
        && source.format() == QImage::Format_Indexed8) {
        QImage upright(source.height(), source.width(), QImage::Format_Indexed8);
        if (!upright.isNull()) {
            upright.setColorTable(source.colorTable());
            for (int y = 0; y < source.height(); ++y) {
                const uchar *input = source.constScanLine(y);
                for (int x = 0; x < source.width(); ++x)
                    upright.scanLine(x)[y] = input[x];
            }
            visible = upright;
        }
    }
    const int cw = r.spriteStamp.active() ? visible.width()
        : (r.cellWidth > 0 ? qMin(r.cellWidth, visible.width()) : visible.width());
    const int ch = r.spriteStamp.active() ? visible.height()
        : (r.cellHeight > 0 ? qMin(r.cellHeight, visible.height()) : visible.height());
    const int cols = qMax(1, visible.width() / cw);
    const int rows = qMax(1, visible.height() / ch);
    const int frames = cols * rows;
    const int frame = qBound(0, r.frame, frames - 1);
    if (details) {
        *details = tr("%1 × %2 pixels  |  %3 frame(s)  |  %4 bytes indexed")
                       .arg(visible.width()).arg(visible.height()).arg(frames)
                       .arg(qint64(source.width()) * source.height());
    }
    QImage frameImage = visible.copy((frame % cols) * cw, (frame / cols) * ch, cw, ch);
    // FORCE = replace lookup table ONLY. Absolutely no pixel-index remapping.
    if (m_forcePalette && m_forcePalette->isChecked()
        && frameImage.format() == QImage::Format_Indexed8) {
        const QString plane = resourcePlane(r);
        const QVector<QRgb> bank = activePalette(plane);
        if (bank.size() == 256)
            frameImage.setColorTable(colourPreviewBank(bank,
                plane == QStringLiteral("foreground"),
                m_previewPaletteAlpha && m_previewPaletteAlpha->isChecked()));
    }
    if (m_showColourCycles && m_showColourCycles->isChecked()
        && frameImage.format() == QImage::Format_Indexed8) {
        const bool background = resourcePlane(r) == QStringLiteral("background");
        const auto &cycle = background ? m_backColourCycle : m_frontColourCycle;
        const int phase = background ? m_backCyclePhase : m_frontCyclePhase;
        if (cycle.enabled)
            frameImage.setColorTable(SidboxGamePalette::cyclePreview(
                frameImage.colorTable(), cycle, phase, background));
    }
    // Preview matches BLIT_FLAG_FLIP_X / Y without changing the source PPB.
    if (r.kind == QStringLiteral("sprite") && (r.objectFlipX || r.objectFlipY)) {
        Qt::Orientations flipDirections;
        if (r.objectFlipX) flipDirections |= Qt::Horizontal;
        if (r.objectFlipY) flipDirections |= Qt::Vertical;
        frameImage = frameImage.flipped(flipDirections);
    }
    return frameImage;
}

void SidboxGameDesigner::refreshColourCyclePreview()
{
    // Update pixmaps IN PLACE to avoid disturbing selection, dragging or world panning.
    if (m_loading || !m_scene) return;
    for (int i = 0; i < m_resources.size() && i < m_sceneItems.size(); ++i) {
        const Resource &resource = m_resources.at(i);
        if (!visualKind(resource.kind)) continue;
        auto *item = dynamic_cast<QGraphicsPixmapItem *>(m_sceneItems.at(i));
        if (!item) continue;
        Resource frame = resource;
        frame.frame = item->data(1).toInt();
        const QImage preview = resourcePreview(frame);
        if (!preview.isNull()) {
            item->setPixmap(QPixmap::fromImage(patternedBobPreview(
                preview, resource.objectAlphaFadePercent, resource.scale,
                resource.x, resource.y)));
            item->setScale(resource.objectAlphaFadePercent > 0 ? 1.0
                : resource.scale / 100.0);
            item->setShapeMode(resource.objectAlphaFadePercent > 0
                ? QGraphicsPixmapItem::BoundingRectShape
                : QGraphicsPixmapItem::MaskShape);
        }
    }
    if (m_tilemapOverlayItem) {
        static_cast<GameTilemapOverlay *>(m_tilemapOverlayItem)->setColourCycle(
            m_frontColourCycle, m_frontCyclePhase,
            m_showColourCycles && m_showColourCycles->isChecked() && m_frontColourCycle.enabled);
    }
}

// Stage 5.149: independent editor-only particle pools for ALL placed emitters.
// The Particles checkbox controls visibility, never the resource selection.
// These items belong only to QGraphicsScene, not to the saved .sbgm world.
void SidboxGameDesigner::resetParticlePreview()
{
    for (ParticlePreviewEmitter &emitter : m_particlePreviewEmitters) {
        if (emitter.resourceIndex >= 0 && emitter.resourceIndex < m_sceneItems.size() &&
            emitter.resourceIndex < m_resources.size() &&
            m_resources.at(emitter.resourceIndex).id == emitter.resourceId) {
            if (QGraphicsItem *source = m_sceneItems.at(emitter.resourceIndex))
                source->setOpacity(1.0);
        }
        for (QGraphicsPixmapItem *item : emitter.items) {
            if (!item) continue;
            if (m_scene) m_scene->removeItem(item);
            delete item;
        }
    }
    m_particlePreviewEmitters.clear();
}

void SidboxGameDesigner::setParticlePreviewDraft(int resourceIndex, const Resource &draft)
{
    // Only this emitter uses temporary values; all other pools keep moving.
    m_particlePreviewDraftActive = true;
    m_particlePreviewDraftIndex = resourceIndex;
    m_particlePreviewDraft = draft;
}

void SidboxGameDesigner::clearParticlePreviewDraft()
{
    const int edited = m_particlePreviewDraftIndex;
    m_particlePreviewDraftActive = false;
    m_particlePreviewDraftIndex = -1;
    // Rebuild only the edited emitter after Save/Cancel, not every spawner.
    for (int i = m_particlePreviewEmitters.size() - 1; i >= 0; --i) {
        ParticlePreviewEmitter &emitter = m_particlePreviewEmitters[i];
        if (emitter.resourceIndex != edited) continue;
        if (edited >= 0 && edited < m_sceneItems.size() && m_sceneItems.at(edited))
            m_sceneItems.at(edited)->setOpacity(1.0);
        for (QGraphicsPixmapItem *item : emitter.items) {
            m_scene->removeItem(item);
            delete item;
        }
        m_particlePreviewEmitters.removeAt(i);
    }
    updateParticlePreview();
}

void SidboxGameDesigner::updateParticlePreview()
{
    if (!m_scene || m_loading) return;
    if (!m_showParticlePreview || !m_showParticlePreview->isChecked()) {
        if (!m_particlePreviewEmitters.isEmpty()) resetParticlePreview();
        return;
    }

    // Remove a missing/changed resource's pool without resetting the others.
    const auto discardEmitter = [this](int pos) {
        ParticlePreviewEmitter &emitter = m_particlePreviewEmitters[pos];
        if (emitter.resourceIndex >= 0 && emitter.resourceIndex < m_resources.size() &&
            emitter.resourceIndex < m_sceneItems.size() &&
            m_resources.at(emitter.resourceIndex).id == emitter.resourceId) {
            if (QGraphicsItem *source = m_sceneItems.at(emitter.resourceIndex))
                source->setOpacity(1.0);
        }
        for (QGraphicsPixmapItem *item : emitter.items) {
            if (!item) continue;
            m_scene->removeItem(item);
            delete item;
        }
        m_particlePreviewEmitters.removeAt(pos);
    };

    // The Properties dialog temporarily replaces ONE resource with its draft.
    // Everything else continues animating, even while another object is
    // selected, or while its Properties window is maximised.
    for (int index = 0; index < m_resources.size(); ++index) {
        const Resource &r = m_particlePreviewDraftActive && m_particlePreviewDraftIndex == index
            ? m_particlePreviewDraft : m_resources.at(index);
        if (r.kind != QStringLiteral("sprite") ||
            r.objectType != QStringLiteral("particle_emitter")) continue;

        int emitterPos = -1;
        bool newlyCreated = false;
        for (int j = 0; j < m_particlePreviewEmitters.size(); ++j) {
            if (m_particlePreviewEmitters.at(j).resourceIndex == index) {
                emitterPos = j;
                break;
            }
        }
        if (emitterPos >= 0) {
            const ParticlePreviewEmitter &old = m_particlePreviewEmitters.at(emitterPos);
            if (old.resourceId != r.id || old.path != r.path ||
                old.scale != r.scale || old.frame != r.frame ||
                old.prepopulate != r.particlePrepopulate ||
                old.preset != r.particlePreset ||
                (r.particlePreset == QStringLiteral("fireflies") &&
                 old.swirlRadius != r.particleSwirlRadius) ||
                old.particles.size() != 32) {
                discardEmitter(emitterPos);
                emitterPos = -1;
            }
        }
        if (emitterPos < 0) {
            const QImage source = resourcePreview(r);
            if (source.isNull()) continue;
            ParticlePreviewEmitter created;
            created.resourceIndex = index;
            created.resourceId = r.id;
            created.path = r.path;
            created.scale = r.scale;
            created.frame = r.frame;
            created.prepopulate = r.particlePrepopulate;
            created.preset = r.particlePreset;
            created.swirlRadius = r.particleSwirlRadius;
            created.particles.resize(32);
            created.random = 0xA8E5B173u ^
                (quint32(index + 1) * 0x9E3779B9u) ^ quint32(r.x);
            if (!created.random) created.random = 1u;
            const QPixmap pixmap = QPixmap::fromImage(source);
            for (int particleIndex = 0; particleIndex < 32; ++particleIndex) {
                auto *item = new QGraphicsPixmapItem();
                item->setAcceptedMouseButtons(Qt::NoButton);
                item->setFlag(QGraphicsItem::ItemIsSelectable, false);
                item->setTransformationMode(Qt::FastTransformation);
                item->setPixmap(pixmap);
                item->setScale(r.scale / 100.0);
                item->setVisible(false);
                m_scene->addItem(item);
                created.items.append(item);
            }
            m_particlePreviewEmitters.append(created);
            emitterPos = m_particlePreviewEmitters.size() - 1;
            newlyCreated = true;
            // The real emitter does not display its stationary source sprite.
            // Retain a faint, clickable placement handle in the editor.
            if (index < m_sceneItems.size() && m_sceneItems.at(index))
                m_sceneItems.at(index)->setOpacity(0.22);
        }

        ParticlePreviewEmitter &emitter = m_particlePreviewEmitters[emitterPos];
        const auto randomValue = [&emitter]() -> quint32 {
            quint32 value = emitter.random;
            value ^= value << 13;
            value ^= value >> 17;
            value ^= value << 5;
            emitter.random = value ? value : 1u;
            return value;
        };
        const int limit = qBound(1, r.particleCount, 32);
        const int lifetime = qBound(30, r.particleLifetime, 2000);
        const int interval = qBound(1, r.particleInterval, 255);
        // Use exactly the same 50 Hz simulation for ordinary preview ticks
        // and for the one-time prewarm. Do not touch QGraphicsScene items
        // during the warmup: this avoids thousands of needless Qt repaints.
        const auto stepParticles = [&]() {
            if (++emitter.step >= interval) {
                emitter.step = 0;
                for (int i = 0; i < limit; ++i) {
                    auto &particle = emitter.particles[i];
                    if (particle.active) continue;
                    const quint32 rx = randomValue();
                    const quint32 ry = randomValue();
                    particle.x100 = (qint64(r.x) + rx % quint32(qMax(8, r.particleAreaW))) * 100;
                    particle.y100 = (qint64(r.y) + ry % quint32(qMax(8, r.particleAreaH))) * 100;
                    particle.vy100 = r.particleFall;
                    particle.centreX100 = particle.x100;
                    particle.centreY100 = particle.y100;
                    particle.swirlPhase = int((rx >> 8) ^ ry) & 255;
                    const int halfRadius = qBound(8, r.particleSwirlRadius, 96) / 2;
                    particle.swirlRadius = halfRadius + int(ry % quint32(halfRadius + 1));
                    particle.age = 0;
                    particle.fade = (r.particleFadeEnabled && r.particleFadeIn) ? 100 : 0;
                    particle.overPlayer = !r.drawBehindTiles && r.particlePlayerLayerMix &&
                        ((rx ^ ry) & 1u);
                    particle.active = true;
                    break;
                }
            }
            for (int i = 0; i < emitter.particles.size(); ++i) {
                auto &particle = emitter.particles[i];
                if (i >= limit || !particle.active) {
                    if (i >= limit) particle.active = false;
                    continue;
                }
                if (++particle.age >= lifetime) {
                    particle.active = false;
                    continue;
                }
                if (r.particleFadeEnabled) {
                    int target = 0;
                    const int inFrames = lifetime * qBound(0, r.particleFadeIn, 100) / 100;
                    const int outFrames = lifetime * qBound(0, r.particleFadeOut, 100) / 100;
                    if (inFrames > 0 && particle.age < inFrames)
                        target = 100 - particle.age * 100 / inFrames;
                    if (outFrames > 0 && particle.age > lifetime - outFrames)
                        target = qMax(target, (particle.age - (lifetime - outFrames)) * 100 / outFrames);
                    const int step = qBound(1, r.particleFadeSpeed, 100);
                    particle.fade += qBound(-step, target - particle.fade, step);
                } else particle.fade = 0;
                if (r.particlePreset == QStringLiteral("fireflies")) {
                    // Matches the generated 64-value table and 256-phase orbit.
                    static const qint8 swirlSine[64] = {
                        0, 12, 25, 37, 49, 60, 71, 81,
                        90, 98, 106, 112, 117, 122, 125, 126,
                        127, 126, 125, 122, 117, 112, 106, 98,
                        90, 81, 71, 60, 49, 37, 25, 12,
                        0, -12, -25, -37, -49, -60, -71, -81,
                        -90, -98, -106, -112, -117, -122, -125, -126,
                        -127, -126, -125, -122, -117, -112, -106, -98,
                        -90, -81, -71, -60, -49, -37, -25, -12,
                    };
                    particle.centreX100 += r.particleWind;
                    particle.vy100 = qMin(1200, particle.vy100 + r.particleGravity);
                    particle.centreY100 += particle.vy100;
                    particle.swirlPhase = (particle.swirlPhase + qBound(1, r.particleSwirlSpeed, 12)) & 255;
                    const int phase = particle.swirlPhase >> 2;
                    const int radius100 = particle.swirlRadius * 100;
                    particle.x100 = particle.centreX100 + radius100 * swirlSine[(phase + 16) & 63] / 127;
                    particle.y100 = particle.centreY100 + radius100 * swirlSine[phase] / 127;
                } else {
                    const int phase = (particle.age + i * 9) & 31;
                    const int triangle = phase < 16 ? phase - 8 : 24 - phase;
                    const int gust = triangle * r.particleFlutter / 8;
                    particle.x100 += r.particleWind + gust;
                    particle.vy100 = qMin(1200, particle.vy100 + r.particleGravity);
                    particle.y100 += particle.vy100;
                }
            }
        };
        if (newlyCreated && r.particlePrepopulate) {
            const int warmFrames = qMin(lifetime - 1, limit * interval);
            for (int frame = 0; frame < warmFrames; ++frame) stepParticles();
        }
        stepParticles();
        for (int i = 0; i < emitter.particles.size(); ++i) {
            const auto &particle = emitter.particles.at(i);
            QGraphicsPixmapItem *item = emitter.items[i];
            if (!particle.active || i >= limit) {
                item->setVisible(false);
                continue;
            }
            item->setPos(particle.x100 / 100, particle.y100 / 100);
            item->setZValue(r.drawBehindTiles ? 1.95 : (particle.overPlayer ? 10501 : 10490));
            item->setOpacity(1.0 - qBound(0, particle.fade, 100) / 100.0);
            item->setVisible(particle.fade < 100);
        }

    }

    // Removed spawners and objects temporarily changed away from the emitter
    // type must not leave orphan leaf sprites behind on the world canvas.
    for (int i = m_particlePreviewEmitters.size() - 1; i >= 0; --i) {
        const ParticlePreviewEmitter &emitter = m_particlePreviewEmitters.at(i);
        const int index = emitter.resourceIndex;
        if (index < 0 || index >= m_resources.size()) {
            discardEmitter(i);
            continue;
        }
        const Resource &r = m_particlePreviewDraftActive && m_particlePreviewDraftIndex == index
            ? m_particlePreviewDraft : m_resources.at(index);
        if (r.kind != QStringLiteral("sprite") ||
            r.objectType != QStringLiteral("particle_emitter") || r.id != emitter.resourceId)
            discardEmitter(i);
    }
}

// Lightweight screen-space weather preview. The generated C renderer uses
// the same deterministic spawn scatter and travel speeds; this is editor-only.
void SidboxGameDesigner::updateWeatherPreview()
{
    if (!m_scene || !m_cameraX || !m_cameraY) return;
    if (!m_weatherPreviewDrops) {
        m_weatherPreviewDrops = m_scene->addPath(QPainterPath(), QPen(QColor(180, 225, 255), 1.2));
        m_weatherPreviewDrops->setZValue(10505);
        m_weatherPreviewDrops->setAcceptedMouseButtons(Qt::NoButton);
    }
    if (!m_weatherPreviewFlash) {
        m_weatherPreviewFlash = m_scene->addRect(QRectF(0, 0, 480, 320), Qt::NoPen,
            QBrush(QColor(205, 230, 255)));
        m_weatherPreviewFlash->setZValue(10506);
        m_weatherPreviewFlash->setAcceptedMouseButtons(Qt::NoButton);
    }
    if (!m_weatherPreviewPaletteFlash) {
        // Qt scene-colour approximation: hardware instead blends the actual
        // FRONT/BACK 256-entry CLUTs from their original source on each pulse.
        m_weatherPreviewPaletteFlash = m_scene->addRect(QRectF(0, 0, 480, 320),
            Qt::NoPen, QBrush(QColor(205, 230, 255)));
        m_weatherPreviewPaletteFlash->setZValue(10507);
        m_weatherPreviewPaletteFlash->setAcceptedMouseButtons(Qt::NoButton);
    }
    if (!m_weatherPreviewDayNightTint) {
        // Approximate the indexed FRONT/BACK palette blending in the Qt view.
        m_weatherPreviewDayNightTint = m_scene->addRect(QRectF(0, 0, 480, 320),
            Qt::NoPen, QBrush(QColor(QStringLiteral("#233b68"))));
        m_weatherPreviewDayNightTint->setZValue(10504);
        m_weatherPreviewDayNightTint->setAcceptedMouseButtons(Qt::NoButton);
    }
    const bool enabled = m_showWeatherPreview && m_showWeatherPreview->isChecked();
    const bool show = enabled && m_weatherMode > 0;
    m_weatherPreviewDrops->setVisible(show);
    m_weatherPreviewFlash->setVisible(show && m_weatherMode == 3 && m_weatherLightningOverlay);
    m_weatherPreviewPaletteFlash->setVisible(show && m_weatherMode == 3 && m_weatherPaletteFlashStrength > 0);
    m_weatherPreviewDayNightTint->setVisible(enabled && m_dayNightMode != 0 && m_dayNightStrength > 0);
    if (!enabled) return;
    const int cameraX = m_cameraX->value(), cameraY = m_cameraY->value();
    const int width = 480, height = 320;
    const qint64 ticks = m_objectPreviewClock.isValid() ? m_objectPreviewClock.elapsed() / 20 : 0;
    // Approximate the same cubic 0-100% tint envelope as SIDBOX. Even a
    // clear world can have night/fog tint if Weather preview is checked.
    int nightMix = m_dayNightMode == 1 ? m_dayNightStrength : 0;
    if (m_dayNightMode == 2) {
        const qint64 day = m_dayNightDayFrames, night = m_dayNightNightFrames;
        const qint64 fade = m_dayNightFadeFrames;
        const qint64 span = day + night + 2 * fade;
        const qint64 phase = (ticks + (m_dayNightStartAtNight ? day + fade : 0)) % span;
        int progress = 0;
        if (phase < day) progress = 0;
        else if (phase < day + fade) progress = int((phase - day) * 100 / fade);
        else if (phase < day + fade + night) progress = 100;
        else progress = int((day + 2 * fade + night - phase) * 100 / fade);
        const int eased = progress * progress * (300 - 2 * progress) / 10000;
        nightMix = eased * m_dayNightStrength / 100;
    }
    QColor nightColour(m_dayNightColour);
    if (!nightColour.isValid()) nightColour = QColor(QStringLiteral("#233b68"));
    m_weatherPreviewDayNightTint->setRect(cameraX, cameraY, width, height);
    m_weatherPreviewDayNightTint->setBrush(QBrush(nightColour));
    m_weatherPreviewDayNightTint->setOpacity(nightMix / 100.0);
    m_weatherPreviewDayNightTint->setVisible(m_dayNightMode != 0 && nightMix > 0);
    if (!show) return;
    QPainterPath drops;
    const int rain = m_weatherMode == 1 || m_weatherMode == 3;
    // Keep the world preview's scatter identical to the SIDBOX rain renderer.
    const auto scatterHash = [](quint32 v) -> quint32 {
        v ^= v >> 16;
        v *= 0x7feb352du;
        v ^= v >> 15;
        v *= 0x846ca68bu;
        return v ^ (v >> 16);
    };
    const quint32 scatterSeed = scatterHash(0x7beab187u ^
        (quint32(m_playerStartX) * 0x9e3779b9u) ^
        (quint32(m_playerStartY) * 0x85ebca6bu));
    for (int i = 0; i < m_weatherDensity; ++i) {
        const quint32 seed = scatterHash(scatterSeed ^
            (quint32(i + 1) * 0x9e3779b9u));
        const int layer = int((seed >> 23) % 3u);
        const int speed = rain
            ? (layer == 0 ? 4 : layer == 1 ? 7 : 11) +
                int((seed >> 16) % (layer == 0 ? 3u : layer == 1 ? 4u : 5u))
            : 1 + int((seed >> 16) % 3u);
        const int len = rain
            ? (layer == 0 ? 3 : layer == 1 ? 5 : 7) +
                int((seed >> 12) % (layer == 2 ? 4u : 3u)) : 1;
        const quint64 travel = quint64(seed % quint32(height)) + quint64(ticks) * speed;
        const int y = int(travel % quint64(height));
        const quint32 wrap = quint32(travel / quint64(height));
        int x = int(scatterHash(seed ^ (wrap * 0x85ebca6bu)) % quint32(width));
        x = (x + int(ticks % width) * m_weatherWind) % width;
        if (x < 0) x += width;
        if (rain) {
            drops.moveTo(cameraX + x, cameraY + y);
            drops.lineTo(cameraX + x, cameraY + y + qMin(len, height - y));
        } else {
            drops.addEllipse(cameraX + x, cameraY + y, qMin(2, width - x), 1);
        }
    }
    m_weatherPreviewDrops->setPath(drops);
    const QVector<QRgb> palette = activePalette(QStringLiteral("foreground"));
    const QColor colour = palette.size() == 256
        ? QColor::fromRgb(palette.at(m_weatherPaletteIndex)) : QColor(192, 230, 255);
    m_weatherPreviewDrops->setPen(QPen(colour, rain ? 1.1 : 1.4));
    m_weatherPreviewFlash->setRect(cameraX, cameraY, width, height);
    m_weatherPreviewFlash->setBrush(QBrush(colour));
    // Match SIDBOX's variable-length rounded lightning pulse. Both the
    // screen overlay and palette flash use identical timing and peak.
    const int interval = qMax(175, m_weatherLightningInterval);
    const int duration = 6 + (m_weatherLightningCurve * 74) / 100;
    const int phase = int(ticks % (interval + duration));
    const int position = phase - interval;
    int envelope = 0;
    if (position >= 0 && position < duration - 1) {
        const int rise = qMax(2, ((duration - 1) * 35 + 50) / 100);
        const int progress = position <= rise
            ? position * 100 / rise
            : (duration - 1 - position) * 100 / (duration - 1 - rise);
        envelope = progress * progress * (300 - 2 * progress) / 10000;
    }
    const int pulse = envelope * 85 / 100;
    m_weatherPreviewFlash->setOpacity(pulse * m_weatherLightningStrength / 10000.0);
    m_weatherPreviewFlash->setVisible(m_weatherMode == 3 && m_weatherLightningOverlay && pulse != 0);
    m_weatherPreviewPaletteFlash->setRect(cameraX, cameraY, width, height);
    // Preview the palette's additive brightening instead of tint replacement.
    m_weatherPreviewPaletteFlash->setBrush(QBrush(QColor(
        (255 + colour.red()) / 2, (255 + colour.green()) / 2, (255 + colour.blue()) / 2)));
    m_weatherPreviewPaletteFlash->setOpacity(pulse * m_weatherPaletteFlashStrength / 10000.0);
    m_weatherPreviewPaletteFlash->setVisible(m_weatherMode == 3 && pulse != 0 &&
        m_weatherPaletteFlashStrength > 0);
}

void SidboxGameDesigner::rebuildScene()
{
    m_loading = true;
    // Scene::clear() deletes any editor-only marquee item.
    m_marqueeRect = nullptr;
    m_marqueeSelecting = false;
    m_groupDragActive = false;
    m_groupDragStarts.clear();
    m_splineHandleItems.clear();
    m_splineCurveItem = nullptr;
    m_objectHitbox = nullptr;
    m_particleResizeHandles.clear();
    m_particleResizeHandle = -1;
    m_particleResizeIndex = -1;
    m_particlePreviewEmitters.clear(); // Scene owns and deletes every preview sprite.
    m_weatherPreviewDrops = nullptr;
    m_weatherPreviewFlash = nullptr;
    m_weatherPreviewPaletteFlash = nullptr;
    m_weatherPreviewDayNightTint = nullptr;
    m_scene->clear();
    m_tilemapOverlayItem = nullptr;
    m_loopOverlayItems.clear(); // QGraphicsScene deleted the children above.
    m_sceneItems.clear();
    m_sceneItems.resize(m_resources.size());
    m_worldFrame = nullptr;
    m_cameraFrame = nullptr;
    m_playerStartMarker = nullptr;
    m_scene->setSceneRect(0, 0, m_worldWidth->value(), m_worldHeight->value());
    m_worldFrame = m_scene->addRect(m_scene->sceneRect().adjusted(0, 0, -1, -1),
                                     QPen(QColor(130, 160, 194), 2));
    m_worldFrame->setZValue(10000);
    m_worldFrame->setAcceptedMouseButtons(Qt::NoButton);

    for (int i = 0; i < m_resources.size(); ++i) {
        const Resource &r = m_resources.at(i);
        if (!visualKind(r.kind)) continue;
        const QImage preview = resourcePreview(r);
        const QPixmap pixmap = preview.isNull() ? missingImage(r.kind)
            : QPixmap::fromImage(r.kind == QStringLiteral("sprite")
                ? patternedBobPreview(preview, r.objectAlphaFadePercent,
                                      r.scale, r.x, r.y) : preview);
        auto *item = new PlacedImage(pixmap);
        item->setData(0, i);
        item->setData(1, r.frame); // Atlas index currently displayed.
        item->setFlag(QGraphicsItem::ItemIsMovable, !r.locked);
        item->snapped = [this, i](const QPointF &p) -> QPointF {
            if (m_loading || m_groupDragActive || !m_snap->isChecked()
                || m_resources.at(i).locked) return p;
            const int step = m_snapStep->currentText().section(QLatin1Char(' '), 0, 0).toInt();
            if (step <= 0) return p;
            return QPointF(qRound(p.x() / step) * step, qRound(p.y() / step) * step);
        };
        item->setPos(r.x, r.y);
        item->setScale(r.kind == QStringLiteral("sprite") && r.objectAlphaFadePercent > 0
            ? 1.0 : r.scale / 100.0);
        if (r.kind == QStringLiteral("sprite") && r.objectAlphaFadePercent > 0)
            item->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
        if (r.kind == QStringLiteral("background")) item->setZValue(1);
        else if (r.kind == QStringLiteral("sprite") && r.drawBehindTiles)
            item->setZValue(1.9); // Behind Tilemap Overlay (Z=2), still draggable.
        item->moved = [this](QGraphicsItem *which) { syncFromSceneItem(which); };
        m_scene->addItem(item);
        auto *title = new WorldObjectTag(r.name, item);
        title->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
        title->setPos(0, -18);
        title->setVisible(m_showLabels->isChecked());
        title->setAcceptedMouseButtons(Qt::NoButton);
        m_sceneItems[i] = item;
    }
    // The start marker shows the *shared* player's Idle frame, with the
    // world's initial facing. It is a designer preview only (no SIDBOX BOB).
    // Yellow fallback is shown until an actual .sbpi + PPB are configured.
    const QDir playerProject(QFileInfo(m_filePath).absolutePath());
    const QImage idleSprite = GamePlayerProfile::idlePreview(playerProject, m_playerFacing);
    QPixmap spawnIcon;
    if (!idleSprite.isNull()) {
        spawnIcon = QPixmap::fromImage(idleSprite);
    } else {
        spawnIcon = QPixmap(20,28); spawnIcon.fill(Qt::transparent);
        QPainter painter(&spawnIcon); painter.setPen(QPen(QColor(22,22,22),2));
        painter.setBrush(QColor(255,207,75));
        painter.drawEllipse(QRect(2,2,16,16));
        painter.drawLine(10,18,10,27); painter.drawLine(4,22,16,22);
    }
    auto *spawn = new PlacedImage(spawnIcon);
    spawn->setZValue(10500);
    spawn->setFlag(QGraphicsItem::ItemIsMovable,true);
    spawn->setFlag(QGraphicsItem::ItemIsSelectable,true);
    spawn->setToolTip(tr("Player Start — drag to place, or double-click Player Start in Game Resources"));
    spawn->setData(0,-1);
    spawn->snapped=[this](const QPointF &point) {
        const int step=m_snap && m_snap->isChecked()
            ? m_snapStep->currentText().section(QLatin1Char(' '),0,0).toInt() : 1;
        return QPointF(qBound(0,qRound(point.x()/qMax(1,step))*qMax(1,step),m_worldWidth->value()),
                       qBound(0,qRound(point.y()/qMax(1,step))*qMax(1,step),m_worldHeight->value()));
    };
    spawn->moved=[this](QGraphicsItem *item) {
        if (m_loading) return;
        m_playerStartX=qRound(item->pos().x());m_playerStartY=qRound(item->pos().y());
        setDirty();refreshResources();
    };
    m_scene->addItem(spawn);
    spawn->setPos(m_playerStartX,m_playerStartY);
    // Compact magenta label, centred ABOVE the actual player position.
    // Keep the WorldObjectTag dark keyline exactly as before.
    auto *startTag = new WorldObjectTag(tr("PLAYER START"), spawn,
                                        11, QColor(255, 62, 206));
    const QRectF labelBounds = startTag->boundingRect();
    startTag->setPos((spawnIcon.width() - labelBounds.width()) / 2.0,
                     -labelBounds.height() - 3.0);
    startTag->setAcceptedMouseButtons(Qt::NoButton);
    m_playerStartMarker=spawn;
    // Named entrances have their own drag handles. No player sprite allocation.
    for (const PlayerStartLocation &location : m_otherPlayerStarts) {
        auto *marker = new PlacedImage(spawnIcon);
        marker->setZValue(10499);
        marker->setFlag(QGraphicsItem::ItemIsMovable, true);
        marker->setFlag(QGraphicsItem::ItemIsSelectable, true);
        marker->setData(0, -2);
        marker->setToolTip(tr("%1 — drag to position this entrance").arg(location.name));
        marker->snapped = spawn->snapped;
        const QString id = location.id;
        marker->moved = [this, id](QGraphicsItem *item) {
            if (m_loading) return;
            for (PlayerStartLocation &entry : m_otherPlayerStarts)
                if (entry.id == id) {
                    entry.x = qRound(item->pos().x());
                    entry.y = qRound(item->pos().y());
                    setDirty(); refreshResources(); break;
                }
        };
        m_scene->addItem(marker);
        marker->setPos(location.x, location.y);
        auto *tag = new WorldObjectTag(location.name, marker, 11, QColor(80, 235, 255));
        tag->setPos(0, -tag->boundingRect().height() - 3);
        tag->setAcceptedMouseButtons(Qt::NoButton);
    }
    rebuildTilemapOverlay();
    m_cameraFrame = m_scene->addRect(QRectF(0, 0, LCD_WIDTH, LCD_HEIGHT),
                 QPen(QColor(255, 207, 75), 2, Qt::DashLine));
    m_cameraFrame->setZValue(10001);
    m_cameraFrame->setAcceptedMouseButtons(Qt::NoButton);
    auto *lcdLabel = new QGraphicsSimpleTextItem(QStringLiteral("LCD 480 × 320"), m_cameraFrame);
    lcdLabel->setBrush(QColor(255, 207, 75));
    lcdLabel->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
    lcdLabel->setPos(3, 3);
    lcdLabel->setAcceptedMouseButtons(Qt::NoButton);
    refreshFrame();
    rebuildSplineOverlay();
    m_loading = false;
    refreshObjectHitbox();
}

void SidboxGameDesigner::refreshFrame()
{
    if (!m_scene) return;
    const int width = m_worldWidth->value();
    const int height = m_worldHeight->value();
    m_cameraX->setMaximum(qMax(0, width - LCD_WIDTH));
    m_cameraY->setMaximum(qMax(0, height - LCD_HEIGHT));
    // Previewing a larger tilemap extends the scrollable canvas, not the
    // configured game world or its independent LCD camera limits.
    const bool showMap = m_tilemapEnabled && m_showTilemap && m_showTilemap->isChecked();
    const int canvasWidth = showMap ? qMax(width, m_tilemap.width * m_tilemap.tileSize) : width;
    const int canvasHeight = showMap ? qMax(height, m_tilemap.height * m_tilemap.tileSize) : height;
    m_scene->setSceneRect(0, 0, canvasWidth, canvasHeight);
    if (m_worldFrame) m_worldFrame->setRect(0, 0, width - 1, height - 1);
    if (m_cameraFrame) m_cameraFrame->setPos(m_cameraX->value(), m_cameraY->value());
}

void SidboxGameDesigner::syncFromSceneItem(QGraphicsItem *item)
{
    if (m_loading || !item) return;
    const int index = item->data(0).toInt();
    if (index < 0 || index >= m_resources.size()) return;
    if (m_resources[index].locked) return;
    m_resources[index].x = qRound(item->pos().x());
    m_resources[index].y = qRound(item->pos().y());
    if (m_resources.at(index).kind == QStringLiteral("sprite") &&
        m_resources.at(index).objectAlphaFadePercent > 0) {
        auto *image = dynamic_cast<QGraphicsPixmapItem *>(item);
        if (image) {
            Resource frame = m_resources.at(index);
            frame.frame = image->data(1).toInt();
            const QImage base = resourcePreview(frame);
            if (!base.isNull())
                image->setPixmap(QPixmap::fromImage(patternedBobPreview(base,
                    frame.objectAlphaFadePercent, frame.scale, frame.x, frame.y)));
        }
    }
    setDirty();
    if (selectedIndex() == index) { refreshProperties(); refreshObjectHitbox(); }
}

void SidboxGameDesigner::updateSelectedItem()
{
    const int index = selectedIndex();
    if (index < 0 || index >= m_sceneItems.size()) return;
    auto *item = m_sceneItems.at(index);
    if (!item) return;
    const Resource &r = m_resources.at(index);
    m_loading = true;
    item->setPos(r.x, r.y);
    item->setScale(r.kind == QStringLiteral("sprite") && r.objectAlphaFadePercent > 0
        ? 1.0 : r.scale / 100.0);
    if (auto *image = dynamic_cast<QGraphicsPixmapItem *>(item)) {
        image->setShapeMode(r.kind == QStringLiteral("sprite") && r.objectAlphaFadePercent > 0
            ? QGraphicsPixmapItem::BoundingRectShape
            : QGraphicsPixmapItem::MaskShape);
        if (r.kind == QStringLiteral("sprite") && r.objectAlphaFadePercent > 0) {
            Resource frame = r;
            frame.frame = image->data(1).toInt();
            const QImage base = resourcePreview(frame);
            if (!base.isNull())
                image->setPixmap(QPixmap::fromImage(patternedBobPreview(base,
                    r.objectAlphaFadePercent, r.scale, r.x, r.y)));
        }
    }
    item->setZValue(r.kind == QStringLiteral("background") ? 1.0 :
                    (r.kind == QStringLiteral("sprite") && r.drawBehindTiles) ? 1.9 : 10.0);
    m_loading = false;
    refreshObjectHitbox();
}

void SidboxGameDesigner::updateSelectedPixmap()
{
    const int index = selectedIndex();
    if (index < 0 || index >= m_sceneItems.size() || !m_sceneItems.at(index)) return;
    auto *item = dynamic_cast<QGraphicsPixmapItem *>(m_sceneItems.at(index));
    if (!item) return;
    const Resource &r = m_resources.at(index);
    const QImage preview = resourcePreview(r);
    item->setPixmap(preview.isNull() ? missingImage(r.kind)
        : QPixmap::fromImage(r.kind == QStringLiteral("sprite")
            ? patternedBobPreview(preview, r.objectAlphaFadePercent, r.scale, r.x, r.y)
            : preview));
    item->setScale(r.kind == QStringLiteral("sprite") && r.objectAlphaFadePercent > 0
        ? 1.0 : r.scale / 100.0);
    item->setShapeMode(r.kind == QStringLiteral("sprite") && r.objectAlphaFadePercent > 0
        ? QGraphicsPixmapItem::BoundingRectShape
        : QGraphicsPixmapItem::MaskShape);
    item->setData(1, r.frame);
}

void SidboxGameDesigner::refreshProperties()
{
    const int index = selectedIndex();
    const bool enabled = index >= 0;
    // Hide graphics-only properties for palettes/audio; disabled grey rows
    // would waste most of the audio editor's limited horizontal space.
    const bool visualSelection = enabled && visualKind(m_resources.at(index).kind);
    for (QWidget *field : {static_cast<QWidget *>(m_propX), static_cast<QWidget *>(m_propY),
                           static_cast<QWidget *>(m_propScale), static_cast<QWidget *>(m_propCellWidth),
                           static_cast<QWidget *>(m_propCellHeight), static_cast<QWidget *>(m_propFrame)}) {
        field->setVisible(visualSelection);
        if (QWidget *label = m_propertiesForm->labelForField(field)) label->setVisible(visualSelection);
    }
    m_positionFields->setVisible(visualSelection);
    m_exportCButton->setVisible(visualSelection);
    m_propPlane->setVisible(enabled && (visualSelection || m_resources.at(index).kind == QStringLiteral("palette")));
    if (QWidget *label = m_propertiesForm->labelForField(m_propPlane)) label->setVisible(m_propPlane->isVisible());
    m_propBackgroundMode->setVisible(enabled && m_resources.at(index).kind == QStringLiteral("background"));
    if (QWidget *label = m_propertiesForm->labelForField(m_propBackgroundMode))
        label->setVisible(m_propBackgroundMode->isVisible());
    m_propLocked->setVisible(visualSelection);
    m_musicPlayOnStart->setVisible(enabled && m_resources.at(index).kind == QStringLiteral("music"));
    if (QWidget *label = m_propertiesForm->labelForField(m_propLocked))
        label->setVisible(visualSelection);
    for (QWidget *widget : {static_cast<QWidget *>(m_propName), static_cast<QWidget *>(m_propX),
                            static_cast<QWidget *>(m_propY), static_cast<QWidget *>(m_propScale),
                            static_cast<QWidget *>(m_propCellWidth), static_cast<QWidget *>(m_propCellHeight),
                            static_cast<QWidget *>(m_propFrame), static_cast<QWidget *>(m_deleteButton)})
        widget->setEnabled(enabled);
    QSignalBlocker block1(m_propName), block2(m_propX), block3(m_propY), block4(m_propScale);
    QSignalBlocker block5(m_propCellWidth), block6(m_propCellHeight), block7(m_propFrame);
    QSignalBlocker block8(m_propLocked), block9(m_propPlane), block10(m_propBackgroundMode);
    QSignalBlocker blockMusicStart(m_musicPlayOnStart);
    if (!enabled) {
        m_propName->clear(); m_propFile->clear(); m_imageInfo->clear(); m_palettePreview->hide();
        m_editPaletteButton->hide();
        m_audioPanel->clearAudio();
        m_exportCButton->setEnabled(false);
        m_propX->setValue(0); m_propY->setValue(0); m_propScale->setValue(100);
        m_propCellWidth->setValue(0); m_propCellHeight->setValue(0);
        m_propFrame->setRange(0, 0);
        m_propLocked->setChecked(false);
        m_musicPlayOnStart->setChecked(false);
        return;
    }
    const Resource &r = m_resources.at(index);
    m_musicPlayOnStart->setChecked(r.kind == QStringLiteral("music") && r.musicPlayOnStart);
    if (r.kind == QStringLiteral("sound") || r.kind == QStringLiteral("music"))
        m_audioPanel->showAudio(r.kind, resolvedPath(r.path), r.audio);
    else m_audioPanel->clearAudio();
    m_palettePreview->hide();
    m_editPaletteButton->setVisible(r.kind == QStringLiteral("palette"));
    if (r.kind == QStringLiteral("palette")) {
        QString error;
        const QVector<QRgb> bank = SidboxGamePalette::readPalette(
            resolvedPath(r.path), r.plane == QStringLiteral("background"), &error);
        if (!bank.isEmpty()) {
            m_palettePreview->setPixmap(paletteSwatches(bank));
            m_palettePreview->show();
            m_imageInfo->setText(tr("%1 CLUT: 256 indexed entries (preview only)")
                .arg(r.plane == QStringLiteral("background") ? tr("Background") : tr("Foreground")));
        } else m_imageInfo->setText(error);
    }
    m_propName->setText(r.name);
    m_propPlane->setCurrentIndex(r.plane == QStringLiteral("background") ? 1 : 0);
    const int backgroundModeIndex = m_propBackgroundMode->findData(r.backgroundMode);
    m_propBackgroundMode->setCurrentIndex(backgroundModeIndex >= 0 ? backgroundModeIndex : 0);
    m_propPlane->setEnabled(m_planeMode->currentIndex() == 1 || r.kind == QStringLiteral("palette"));
    m_propLocked->setChecked(r.locked);
    m_propLocked->setEnabled(visualSelection);
    m_propFile->setText(r.path.isEmpty() ? tr("(placeholder)") : r.path);
    m_propX->setValue(r.x);
    m_propY->setValue(r.y);
    m_propScale->setValue(r.scale);
    m_propCellWidth->setValue(r.cellWidth);
    m_propCellHeight->setValue(r.cellHeight);
    const bool visual = visualKind(r.kind);
    m_exportCButton->setEnabled(visual);
    for (QSpinBox *spin : {m_propX, m_propY})
        spin->setEnabled(visual && !r.locked);
    for (QSpinBox *spin : {m_propScale, m_propCellWidth, m_propCellHeight, m_propFrame})
        spin->setEnabled(visual && (!r.spriteStamp.active() || spin == m_propScale));
    // Sprite Stamp controls its own 8x8 source cells; these raw BOB fields
    // must not accidentally override the lookup layout.
    if (!visual) {
        m_propFrame->setRange(0, 0);
        if (r.kind == QStringLiteral("tileatlas")) {
            const QImage atlas = cachedImage(resolvedPath(r.path));
            if (atlas.isNull()) m_imageInfo->setText(tr("Tile atlas PPB is unavailable"));
            else m_imageInfo->setText(tr("Tile atlas: %1 x %2 pixels. Resource-only; no game canvas sprite.")
                                      .arg(atlas.width()).arg(atlas.height()));
        } else if (r.kind != QStringLiteral("palette")) m_imageInfo->clear();
        return;
    }
    const QImage image = cachedImage(resolvedPath(r.path));
    const QVector<QRgb> shownPalette = m_forcePalette->isChecked()
        && image.format() == QImage::Format_Indexed8
        ? activePalette(resourcePlane(r)) : QVector<QRgb>();
    if (!image.isNull() && (!shownPalette.isEmpty() || !image.colorTable().isEmpty())) {
        m_palettePreview->setPixmap(paletteSwatches(shownPalette.isEmpty()
            ? image.colorTable() : shownPalette));
        m_palettePreview->show();
    }
    if (image.isNull()) {
        m_propFrame->setRange(0, 0);
        m_imageInfo->setText(r.path.isEmpty() ? tr("Placeholder sprite") : tr("Image not available"));
        return;
    }
    const int cw = r.cellWidth > 0 ? qMin(r.cellWidth, image.width()) : image.width();
    const int ch = r.cellHeight > 0 ? qMin(r.cellHeight, image.height()) : image.height();
    const int frames = qMax(1, image.width() / cw) * qMax(1, image.height() / ch);
    m_propFrame->setRange(0, frames - 1);
    m_propFrame->setValue(qMin(r.frame, frames - 1));
    QString paletteNote;
    if (!shownPalette.isEmpty()) {
        const QString plane = resourcePlane(r);
        paletteNote = tr("  |  Forced %1 CLUT (indices unchanged)").arg(plane);
        if (plane == QStringLiteral("foreground") && m_previewPaletteAlpha->isChecked())
            paletteNote += tr("  |  Previewing foreground CLUT alpha");
        else if (extraPaletteTransparency(shownPalette, plane == QStringLiteral("foreground")))
            paletteNote += tr("  |  WARNING: CLUT alpha differs from colour preview; check on SIDBOX");
    } else if (m_forcePalette->isChecked() && image.format() != QImage::Format_Indexed8) {
        paletteNote = tr("  |  Convert to PPB to use indexed palettes");
    }
    m_imageInfo->setText(tr("Atlas: %1 × %2  |  %3 frames  |  Index 0 = foreground transparency%4")
        .arg(image.width()).arg(image.height()).arg(frames).arg(paletteNote));
}

// A bounded, lightweight history of RESOURCE METADATA, not images or files.
// This intentionally leaves world dimensions and camera navigation out of the
// history until those settings get their own transaction model.
void SidboxGameDesigner::rememberResourceEdit()
{
    if (m_loading) return;
    if (m_undoResources.size() >= 64) {
        m_undoResources.removeFirst();
        m_undoResourceSplines.removeFirst();
        m_undoResourceAdventures.removeFirst();
    }
    m_undoResources.append(m_resources);
    m_undoResourceSplines.append(m_splinePaths);
    m_undoResourceAdventures.append(m_adventure);
    m_redoResources.clear();
    m_redoResourceSplines.clear();
    m_redoResourceAdventures.clear();
}

void SidboxGameDesigner::restoreResourceSnapshot(const QVector<Resource> &snapshot)
{
    const int previousIndex = selectedIndex();
    m_resources = snapshot;
    rebuildScene();
    refreshResources();
    if (previousIndex >= 0 && previousIndex < m_resources.size())
        selectResource(previousIndex);
    else {
        m_resourceTree->clearSelection();
        m_resourceTree->setCurrentItem(nullptr);
        refreshProperties();
    }
    setDirty();
}

void SidboxGameDesigner::undoResourceEdit()
{
    if (m_undoResources.isEmpty()) return;
    if (m_redoResources.size() >= 64) {
        m_redoResources.removeFirst();
        m_redoResourceSplines.removeFirst();
        m_redoResourceAdventures.removeFirst();
    }
    m_redoResources.append(m_resources);
    m_redoResourceSplines.append(m_splinePaths);
    m_redoResourceAdventures.append(m_adventure);
    const QVector<Resource> snapshot = m_undoResources.takeLast();
    m_splinePaths = m_undoResourceSplines.takeLast();
    m_adventure = m_undoResourceAdventures.takeLast();
    restoreResourceSnapshot(snapshot);
}

void SidboxGameDesigner::redoResourceEdit()
{
    if (m_redoResources.isEmpty()) return;
    if (m_undoResources.size() >= 64) {
        m_undoResources.removeFirst();
        m_undoResourceSplines.removeFirst();
        m_undoResourceAdventures.removeFirst();
    }
    m_undoResources.append(m_resources);
    m_undoResourceSplines.append(m_splinePaths);
    m_undoResourceAdventures.append(m_adventure);
    const QVector<Resource> snapshot = m_redoResources.takeLast();
    m_splinePaths = m_redoResourceSplines.takeLast();
    m_adventure = m_redoResourceAdventures.takeLast();
    restoreResourceSnapshot(snapshot);
}

void SidboxGameDesigner::copySelectedSprite(int resourceIndex)
{
    const int index = resourceIndex >= 0 ? resourceIndex : selectedIndex();
    if (index < 0 || index >= m_resources.size()
        || m_resources.at(index).kind != QStringLiteral("sprite")) return;

    // Value copies: source tab can be closed, edited or deleted after copying.
    s_copiedWorldObject = m_resources.at(index);
    s_copiedWorldResources = m_resources;
    s_copiedWorldSplines = m_splinePaths;
    s_copiedWorldAdventure = m_adventure;
    s_copiedWorldSource = m_filePath;
    s_hasCopiedWorldObject = true;
}

void SidboxGameDesigner::pasteCopiedSprite()
{
    if (!s_hasCopiedWorldObject || m_resources.size() >= 8192) return;
    const bool crossWorld = QDir::cleanPath(s_copiedWorldSource)
        != QDir::cleanPath(m_filePath);
    Resource copy = s_copiedWorldObject;
    copy.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    // Treat names already ending in [index] as an authored array. A copy of
    // Fright[0] becomes Fright[1], not Fright[0]_copy[0]. Search the
    // destination world for the highest occupied index to avoid collisions.
    const QRegularExpression numbered(QStringLiteral("^(.*)\\[(\\d+)\\]$"));
    const auto numberedName = numbered.match(copy.name);
    if (numberedName.hasMatch()) {
        const QString base = numberedName.captured(1);
        int next = numberedName.captured(2).toInt() + 1;
        const QRegularExpression series(QStringLiteral("^%1\\[(\\d+)\\]$")
            .arg(QRegularExpression::escape(base)));
        for (const Resource &existing : m_resources) {
            const auto match = series.match(existing.name);
            if (match.hasMatch()) next = qMax(next, match.captured(1).toInt() + 1);
        }
        copy.name = QStringLiteral("%1[%2]").arg(base).arg(next);
    } else {
        QString base = copy.name;
        base.remove(QRegularExpression(QStringLiteral("_copy\\[\\d+\\]$")));
        int next = 0;
        const QRegularExpression series(QStringLiteral("^%1_copy\\[(\\d+)\\]$")
            .arg(QRegularExpression::escape(base)));
        for (const Resource &existing : m_resources) {
            const auto match = series.match(existing.name);
            if (match.hasMatch()) next = qMax(next, match.captured(1).toInt() + 1);
        }
        copy.name = QStringLiteral("%1_copy[%2]").arg(base).arg(next);
    }
    copy.x = qBound(-MAX_WORLD, copy.x + 8, MAX_WORLD);
    copy.y = qBound(-MAX_WORLD, copy.y + 8, MAX_WORLD);
    copy.locked = false;
    // Reward metadata is prepared before the undo boundary, then committed
    // alongside the imported resources in one transaction.
    int rewardSourceKind = 0;
    int rewardDestinationKind = 0;
    bool registerReward = false;
    bool addPickupDefinition = false;
    QJsonObject importedPickupDefinition;
    QJsonObject importedInventoryItem;

    if (crossWorld) {
        // Keep cross-world paste visible: World 1 may be thousands of pixels
        // wide while Forest is only 800 px. Otherwise the new object can be
        // placed beyond the target world and appear to have vanished.
        const QPointF centre = m_view->mapToScene(m_view->viewport()->rect().center());
        const int right = qMax(0, m_worldWidth->value() - qMax(1, copy.hitWidth));
        const int bottom = qMax(0, m_worldHeight->value() - qMax(1, copy.hitHeight));
        const QRectF viewport = m_view->mapToScene(m_view->viewport()->rect()).boundingRect();
        if (copy.x < 0 || copy.x > right || !viewport.contains(QPointF(copy.x, copy.y)))
            copy.x = qBound(0, qRound(centre.x()), right);
        if (copy.y < 0 || copy.y > bottom)
            copy.y = qBound(0, qRound(centre.y()), bottom);
        // Apply the same translation to any imported spline/linked object.
        const int deltaX = copy.x - s_copiedWorldObject.x;
        const int deltaY = copy.y - s_copiedWorldObject.y;

        // World designs for this IDE live beside their common .proj file.
        // Never turn a copied object into a silent link to a foreign project.
        if (QFileInfo(s_copiedWorldSource).absolutePath() !=
            QFileInfo(m_filePath).absolutePath()) {
            QMessageBox::warning(this, tr("Paste Game Object"),
                tr("Copying objects is supported between worlds of the same game project."));
            return;
        }
        // Both .sbgm worlds share a project resource directory, but paths are
        // RELATIVE TO THE DESIGN FILE. Rebase every referenced file path.
        const QDir sourceDir(QFileInfo(s_copiedWorldSource).absolutePath());
        const auto sourceFile = [&](const QString &path) -> QString {
            return path.isEmpty() ? QString() :
                QFileInfo(sourceDir.absoluteFilePath(path)).absoluteFilePath();
        };
        const auto rebase = [&](Resource &r) {
            if (!r.path.isEmpty()) r.path = storedPath(sourceFile(r.path));
            if (!r.animationFile.isEmpty())
                r.animationFile = storedPath(sourceFile(r.animationFile));
            if (r.spriteStamp.active())
                r.spriteStamp.sourcePath = storedPath(sourceFile(r.spriteStamp.sourcePath));
        };

        // Copying a sprite also copies its implicit animation sidecar if one
        // was saved under the default ID-based name.
        const auto attachAnimation = [&](Resource &r, const QString &originalId) {
            if (!r.animationFile.isEmpty()) return;
            const QString implicit = sourceDir.filePath(
                QStringLiteral("gameanimations/%1.sbanim").arg(originalId));
            if (QFileInfo(implicit).isFile()) r.animationFile = sourceDir.relativeFilePath(implicit);
        };

        // Validate all reachable references before changing the destination.
        // Sounds/music, triggered objects and breakable rewards are part of
        // the object; a missing required file must not produce a broken paste.
        QStringList missingFiles;
        QSet<QString> visited;
        const auto sourceById = [&](const QString &id) -> const Resource * {
            for (const Resource &r : s_copiedWorldResources)
                if (r.id == id) return &r;
            return nullptr;
        };
        QString Resource::* soundFields[] = {
            &Resource::sfxPickup, &Resource::sfxRespawn, &Resource::sfxStart,
            &Resource::sfxMove, &Resource::sfxStop, &Resource::sfxReverse,
            &Resource::sfxSpring, &Resource::sfxAmbient,
            &Resource::sfxBreakHit, &Resource::sfxBreakBounce,
            &Resource::sfxBreakFinish, &Resource::sfxHazardHit,
            &Resource::sfxHazardBounce, &Resource::sfxHazardAmbient
        };
        std::function<void(const Resource &)> checkDependencies;
        checkDependencies = [&](const Resource &r) {
            if (visited.contains(r.id)) return;
            visited.insert(r.id);
            const QString file = sourceFile(r.path);
            if (!file.isEmpty() && !QFileInfo(file).isFile())
                missingFiles.append(file);
            if (!r.animationFile.isEmpty() && !QFileInfo(sourceFile(r.animationFile)).isFile())
                missingFiles.append(sourceFile(r.animationFile));
            if (r.spriteStamp.active() && !QFileInfo(sourceFile(r.spriteStamp.sourcePath)).isFile())
                missingFiles.append(sourceFile(r.spriteStamp.sourcePath));
            const auto checkId = [&](const QString &id) {
                if (id.isEmpty() || id == QStringLiteral("@player_spotlight") ||
                    id.startsWith(QStringLiteral("@world/"))) return;
                const Resource *dep = sourceById(id);
                if (dep) checkDependencies(*dep);
                else missingFiles.append(tr("Missing linked resource ID: %1").arg(id));
            };
            for (const auto field : soundFields) checkId(r.*field);
            checkId(r.triggerMusicId);
            checkId(r.targetObjectId);
            for (const Resource::LinkedAction &link : r.triggerExtraActions)
                checkId(link.objectId);
            checkId(r.breakDropCollectableId);
            if (!r.objectSplineId.isEmpty()) {
                bool foundSpline = false;
                for (const SplinePath &path : s_copiedWorldSplines)
                    if (path.id == r.objectSplineId) { foundSpline = true; break; }
                if (!foundSpline)
                    missingFiles.append(tr("Missing spline ID: %1").arg(r.objectSplineId));
            }
        };
        checkDependencies(copy);
        missingFiles.removeDuplicates();
        if (!missingFiles.isEmpty()) {
            QMessageBox::warning(this, tr("Paste Game Object"),
                tr("Cannot import the object because required assets are missing:\n\n%1")
                    .arg(missingFiles.join(QLatin1Char('\n'))));
            return;
        }
        if (m_resources.size() + visited.size() > 8192) {
            QMessageBox::warning(this, tr("Paste Game Object"),
                tr("This object and its linked assets exceed the world resource limit."));
            return;
        }

        // Stage 5.14: An enemy/breakable may drop a collectable whose pickup
        // type is not registered in this world's Adventure Inventory. Capture
        // the source Adventure metadata at COPY time, not when its tab closes.
        // Only an explicit linked collectable reward triggers the question.
        if ((copy.objectType == QStringLiteral("enemy") ||
             copy.objectType == QStringLiteral("breakable")) &&
            !copy.breakDropCollectableId.isEmpty()) {
            const Resource *reward = sourceById(copy.breakDropCollectableId);
            if (reward && reward->kind == QStringLiteral("sprite") &&
                reward->objectType == QStringLiteral("collectable") &&
                reward->pickupKind >= 1 && reward->pickupKind <= 255) {
                rewardSourceKind = reward->pickupKind;
                rewardDestinationKind = rewardSourceKind;
                const QJsonArray sourceItems = s_copiedWorldAdventure.value(
                    QStringLiteral("items")).toArray();
                const QJsonArray targetItems = m_adventure.value(
                    QStringLiteral("items")).toArray();
                const QJsonArray targetTypes = m_adventure.value(
                    QStringLiteral("pickupTypes")).toArray();
                QJsonObject sourceItem;
                for (const QJsonValue &entry : sourceItems) {
                    const QJsonObject item = entry.toObject();
                    if (item.value(QStringLiteral("pickupKind")).toInt() == rewardSourceKind) {
                        sourceItem = item;
                        break;
                    }
                }
                QString kindName;
                if (rewardSourceKind > 4) {
                    for (const QJsonValue &entry : s_copiedWorldAdventure.value(
                             QStringLiteral("pickupTypes")).toArray()) {
                        const QJsonObject def = entry.toObject();
                        if (def.value(QStringLiteral("id")).toInt() == rewardSourceKind) {
                            kindName = def.value(QStringLiteral("name")).toString().trimmed();
                            break;
                        }
                    }
                    if (kindName.isEmpty())
                        kindName = sourceItem.value(QStringLiteral("name")).toString().trimmed();
                    if (kindName.isEmpty()) kindName = reward->name;
                    kindName = kindName.left(36);

                    // Reuse an existing named custom type even if its numeric
                    // ID differs from the source world. Never change a type
                    // that another object or inventory entry already uses.
                    bool foundNamedType = false;
                    for (const QJsonValue &entry : targetTypes) {
                        const QJsonObject def = entry.toObject();
                        if (def.value(QStringLiteral("name")).toString().trimmed().compare(
                                kindName, Qt::CaseInsensitive) == 0 &&
                            def.value(QStringLiteral("id")).toInt() >= 5 &&
                            def.value(QStringLiteral("id")).toInt() <= 255) {
                            rewardDestinationKind = def.value(QStringLiteral("id")).toInt();
                            foundNamedType = true;
                            break;
                        }
                    }
                    if (!foundNamedType) {
                        // An existing inventory item with the exact same name
                        // is already the user's item: link to its custom type.
                        const QString sourceName = sourceItem.value(
                            QStringLiteral("name")).toString().trimmed();
                        if (!sourceName.isEmpty()) {
                            for (const QJsonValue &entry : targetItems) {
                                const QJsonObject item = entry.toObject();
                                if (item.value(QStringLiteral("name")).toString().trimmed().compare(
                                        sourceName, Qt::CaseInsensitive) == 0 &&
                                    item.value(QStringLiteral("pickupKind")).toInt() >= 5 &&
                                    item.value(QStringLiteral("pickupKind")).toInt() <= 255) {
                                    rewardDestinationKind = item.value(QStringLiteral("pickupKind")).toInt();
                                    foundNamedType = true;
                                    break;
                                }
                            }
                        }
                    }
                    if (foundNamedType) {
                        // A legacy world may have an inventory item with a
                        // custom pickup number but no matching named type yet.
                        // Restore its definition so the Adventure editor can
                        // show the correct name instead of "missing type".
                        bool hasDefinition = false;
                        for (const QJsonValue &entry : targetTypes)
                            if (entry.toObject().value(QStringLiteral("id")).toInt() ==
                                rewardDestinationKind) hasDefinition = true;
                        if (!hasDefinition) {
                            addPickupDefinition = true;
                            importedPickupDefinition.insert(QStringLiteral("id"), rewardDestinationKind);
                            importedPickupDefinition.insert(QStringLiteral("name"), kindName);
                        }
                    }
                    if (!foundNamedType) {
                        QSet<int> used;
                        for (const QJsonValue &entry : targetTypes)
                            used.insert(entry.toObject().value(QStringLiteral("id")).toInt());
                        for (const QJsonValue &entry : targetItems)
                            used.insert(entry.toObject().value(QStringLiteral("pickupKind")).toInt());
                        for (const Resource &existing : m_resources)
                            if (existing.kind == QStringLiteral("sprite") &&
                                existing.objectType == QStringLiteral("collectable"))
                                used.insert(existing.pickupKind);
                        if (used.contains(rewardDestinationKind)) {
                            rewardDestinationKind = 5;
                            while (rewardDestinationKind <= 255 && used.contains(rewardDestinationKind))
                                ++rewardDestinationKind;
                        }
                        if (rewardDestinationKind > 255) {
                            QMessageBox::warning(this, tr("Paste Game Object"),
                                tr("There are no free custom pickup types (5-255) in this world."));
                            return;
                        }
                        addPickupDefinition = true;
                        importedPickupDefinition.insert(QStringLiteral("id"), rewardDestinationKind);
                        importedPickupDefinition.insert(QStringLiteral("name"), kindName);
                    }
                }

                bool inventoryExists = false;
                for (const QJsonValue &entry : targetItems) {
                    const QJsonObject item = entry.toObject();
                    if (item.value(QStringLiteral("pickupKind")).toInt() == rewardDestinationKind) {
                        inventoryExists = true;
                        break;
                    }
                }
                if (!inventoryExists) {
                    QString itemName = sourceItem.value(QStringLiteral("name")).toString().trimmed();
                    if (itemName.isEmpty()) itemName = kindName.isEmpty() ? reward->name : kindName;
                    itemName = itemName.left(36);
                    // For unnamed classic types, copy the Adventure editor's
                    // familiar labels. Names are editable after paste.
                    if (itemName.isEmpty()) itemName = tr("Reward %1").arg(rewardDestinationKind);
                    // A name collision with a different pickup type isn't
                    // the same registered item. Keep both distinguishable;
                    // never silently hijack the existing inventory row.
                    QSet<QString> occupiedNames;
                    for (const QJsonValue &entry : targetItems)
                        occupiedNames.insert(entry.toObject().value(QStringLiteral("name"))
                            .toString().trimmed().toCaseFolded());
                    if (occupiedNames.contains(itemName.toCaseFolded())) {
                        const QString baseName = itemName.left(22);
                        int suffix = 1;
                        do {
                            itemName = tr("%1 (import %2)").arg(baseName).arg(suffix++);
                        } while (occupiedNames.contains(itemName.toCaseFolded()));
                    }
                    if (targetItems.size() >= 64) {
                        QMessageBox::information(this, tr("Adventure Inventory Full"),
                            tr("The destination world already has 64 inventory items. "
                               "The reward will be pasted, but cannot be added to inventory."));
                    } else {
                        const QMessageBox::StandardButton choice = QMessageBox::question(
                            this, tr("Import Collectable into Inventory?"),
                            tr("'%1' drops the collectable '%2'.\n\n"
                               "Add '%3' to this world's Adventure Inventory?\n"
                               "The reward will still be pasted if you choose No.")
                                .arg(s_copiedWorldObject.name, reward->name, itemName),
                            QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
                            QMessageBox::Yes);
                        if (choice == QMessageBox::Cancel) return;
                        registerReward = (choice == QMessageBox::Yes);
                        if (registerReward) {
                            importedInventoryItem.insert(QStringLiteral("name"), itemName);
                            importedInventoryItem.insert(QStringLiteral("pickupKind"), rewardDestinationKind);
                            importedInventoryItem.insert(QStringLiteral("capacity"),
                                qBound(1, sourceItem.value(QStringLiteral("capacity")).toInt(1), 65535));
                            importedInventoryItem.insert(QStringLiteral("initial"), 0);
                            // Icon indices belong to the destination dialogue
                            // atlas; copying the source index would show garbage.
                            importedInventoryItem.insert(QStringLiteral("icon"), 65535);
                        }
                    }
                }
            }
        }

        // Remap all stable references, including dependency-to-dependency
        // links. Insert the map entry FIRST, so cycles cannot recurse forever.
        QHash<QString, QString> remapped;
        remapped.insert(s_copiedWorldObject.id, copy.id);
        // Save one undo boundary before changing resources or splines.
        rememberResourceEdit();
        // All new dependency resources are appended after this position.
        const int importedBegin = m_resources.size();
        std::function<QString(const QString &)> importById;
        importById = [&](const QString &id) -> QString {
            if (id.isEmpty()) return {};
            if (id == QStringLiteral("@player_spotlight")) return id;
            if (remapped.contains(id)) return remapped.value(id);
            const Resource *original = sourceById(id);
            if (!original) return {}; // already validated above

            // Reuse an existing identical audio resource instead of adding
            // a second reference to the same sound in every copied enemy.
            if (original->kind == QStringLiteral("sound") ||
                original->kind == QStringLiteral("music")) {
                const QString absolute = sourceFile(original->path);
                for (const Resource &existing : m_resources) {
                    if (absolute.isEmpty() || existing.kind != original->kind ||
                        QDir::cleanPath(resolvedPath(existing.path)) != QDir::cleanPath(absolute))
                        continue;
                    const SidboxAudioSettings &a = original->audio;
                    const SidboxAudioSettings &b = existing.audio;
                    if (a.channel == b.channel && a.frequency == b.frequency &&
                        a.volume == b.volume && a.pan == b.pan && a.loop == b.loop &&
                        a.loopStart == b.loopStart && a.loopLength == b.loopLength &&
                        a.subsong == b.subsong) {
                        remapped.insert(id, existing.id);
                        return existing.id;
                    }
                }
            }
            Resource dep = *original;
            dep.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
            if (dep.kind == QStringLiteral("sprite")) {
                dep.x = qBound(-MAX_WORLD, dep.x + deltaX, MAX_WORLD);
                dep.y = qBound(-MAX_WORLD, dep.y + deltaY, MAX_WORLD);
            }
            if (dep.kind == QStringLiteral("sprite") &&
                dep.objectType == QStringLiteral("collectable") &&
                rewardSourceKind != 0 && dep.pickupKind == rewardSourceKind)
                dep.pickupKind = rewardDestinationKind;
            dep.musicPlayOnStart = false; // never create a surprise second autoplay
            remapped.insert(id, dep.id);
            attachAnimation(dep, original->id);
            rebase(dep);
            const auto remapFields = [&](Resource &r) {
                for (const auto field : soundFields)
                    r.*field = importById(r.*field);
                r.triggerMusicId = importById(r.triggerMusicId);
                if (!r.targetObjectId.startsWith(QStringLiteral("@world/")))
                    r.targetObjectId = importById(r.targetObjectId);
                for (Resource::LinkedAction &link : r.triggerExtraActions)
                    if (!link.objectId.startsWith(QStringLiteral("@world/")))
                        link.objectId = importById(link.objectId);
                r.breakDropCollectableId = importById(r.breakDropCollectableId);
            };
            remapFields(dep);
            m_resources.append(dep);
            return dep.id;
        };

        const auto remapRootFields = [&](Resource &r) {
            for (const auto field : soundFields)
                r.*field = importById(r.*field);
            r.triggerMusicId = importById(r.triggerMusicId);
            if (!r.targetObjectId.startsWith(QStringLiteral("@world/")))
                    r.targetObjectId = importById(r.targetObjectId);
            for (Resource::LinkedAction &link : r.triggerExtraActions)
                if (!link.objectId.startsWith(QStringLiteral("@world/")))
                        link.objectId = importById(link.objectId);
            r.breakDropCollectableId = importById(r.breakDropCollectableId);
        };
        attachAnimation(copy, s_copiedWorldObject.id);
        rebase(copy);
        remapRootFields(copy);

        // Spline definitions are local to a world. Import a referenced one
        // once; keep existing identical paths rather than multiplying copies.
        QHash<QString, QString> splineRemap;
        for (int dependencyIndex = importedBegin; dependencyIndex < m_resources.size(); ++dependencyIndex) {
            Resource &r = m_resources[dependencyIndex];
            if (!r.objectSplineId.isEmpty()) {
                const QString oldId = r.objectSplineId;
                if (!splineRemap.contains(oldId)) {
                    for (const SplinePath &path : s_copiedWorldSplines) {
                        if (path.id != oldId) continue;
                        SplinePath shifted = path;
                        for (QPoint &point : shifted.points)
                            point += QPoint(deltaX, deltaY);
                        QString destinationId;
                        for (const SplinePath &existing : m_splinePaths)
                            if (existing.name == shifted.name && existing.points == shifted.points &&
                                existing.pointPauses == shifted.pointPauses &&
                                existing.durationFrames == shifted.durationFrames &&
                                existing.loop == shifted.loop) {
                                destinationId = existing.id;
                                break;
                            }
                        if (destinationId.isEmpty()) {
                            SplinePath cloned = shifted;
                            cloned.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
                            destinationId = cloned.id;
                            m_splinePaths.append(cloned);
                        }
                        splineRemap.insert(oldId, destinationId);
                        break;
                    }
                }
                if (splineRemap.contains(oldId)) r.objectSplineId = splineRemap.value(oldId);
            }
        }
        if (!copy.objectSplineId.isEmpty()) {
            const QString oldId = copy.objectSplineId;
            if (!splineRemap.contains(oldId)) {
                for (const SplinePath &path : s_copiedWorldSplines) {
                    if (path.id != oldId) continue;
                    SplinePath shifted = path;
                    for (QPoint &point : shifted.points)
                        point += QPoint(deltaX, deltaY);
                    QString destinationId;
                    for (const SplinePath &existing : m_splinePaths)
                        if (existing.name == shifted.name && existing.points == shifted.points &&
                            existing.pointPauses == shifted.pointPauses &&
                            existing.durationFrames == shifted.durationFrames &&
                            existing.loop == shifted.loop) { destinationId = existing.id; break; }
                    if (destinationId.isEmpty()) {
                        SplinePath cloned = shifted;
                        cloned.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
                        destinationId = cloned.id;
                        m_splinePaths.append(cloned);
                    }
                    splineRemap.insert(oldId, destinationId);
                    break;
                }
            }
            copy.objectSplineId = splineRemap.value(oldId);
        }
    } else {
        rememberResourceEdit();
    }

    const int previousHorizontalScroll = m_view->horizontalScrollBar()->value();
    const int previousVerticalScroll = m_view->verticalScrollBar()->value();
    m_resources.append(copy);
    if (crossWorld && rewardSourceKind != 0) {
        if (addPickupDefinition) {
            QJsonArray types = m_adventure.value(QStringLiteral("pickupTypes")).toArray();
            types.append(importedPickupDefinition);
            m_adventure.insert(QStringLiteral("pickupTypes"), types);
        }
        if (registerReward) {
            QJsonArray items = m_adventure.value(QStringLiteral("items")).toArray();
            items.append(importedInventoryItem);
            m_adventure.insert(QStringLiteral("items"), items);
        }
    }
    rebuildScene();
    refreshResources();
    selectResource(m_resources.size() - 1);
    m_view->horizontalScrollBar()->setValue(previousHorizontalScroll);
    m_view->verticalScrollBar()->setValue(previousVerticalScroll);
    setDirty();
    if (assetFilesChanged) assetFilesChanged();
}

// PPB stores atlas dimensions and palette, NOT sprite cell metadata. A 64x64
// tiling guess is useful for conventional sprite sheets, but never guess it
// for backgrounds. Unknown sprites show the whole atlas until edited manually.
void SidboxGameDesigner::suggestSpriteCells(Resource &resource)
{
    if (resource.kind != QStringLiteral("sprite") || resource.path.isEmpty()) return;
    const QImage image = cachedImage(resolvedPath(resource.path));
    if (image.isNull()) return;
    resource.cellWidth = image.width();
    resource.cellHeight = image.height();
    if (image.width() % 64 == 0 && image.height() % 64 == 0
        && (image.width() > 64 || image.height() > 64)
        && image.width() / 64 <= 16 && image.height() / 64 <= 16) {
        resource.cellWidth = 64;
        resource.cellHeight = 64;
    }
}

void SidboxGameDesigner::addResource(const QString &kind, const QString &plane)
{
    if (!QFileInfo(m_filePath).absoluteDir().exists()) return;
    QSettings importPreferences(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    QString sourceDirectory = importPreferences.value(QStringLiteral("files/gameResourceImportLastDirectory"),
        QFileInfo(m_filePath).absolutePath()).toString();
    if (!QDir(sourceDirectory).exists()) sourceDirectory = QFileInfo(m_filePath).absolutePath();
    const QString path = QFileDialog::getOpenFileName(this, tr("Choose %1 resource").arg(kindTitle(kind)),
        sourceDirectory,
        kind == QStringLiteral("tileatlas")
            ? tr("SIDBOX Tile Atlas (*.ppb)")
            : kind == QStringLiteral("sprite") || kind == QStringLiteral("background")
            ? tr("Graphics (*.ppb *.png *.bmp *.jpg *.jpeg *.gif);;All Files (*)")
            : kind == QStringLiteral("sound") ? tr("Sound (*.wav);;All Files (*)")
            : kind == QStringLiteral("music") ? tr("Music (*.mod *.s3m *.xm *.med *.tfmx *.sid *.sba *.spc);;All Files (*)")
            : tr("Palettes / Graphics (*.ppb *.pal *.act *.png *.bmp);;All Files (*)"));
    if (path.isEmpty()) return;
    if (kind == QStringLiteral("tileatlas") &&
        QFileInfo(path).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(this, tr("Tile Atlas"),
            tr("Tile atlases must use a .ppb file.\n"
               "Use Game Resources → Convert PNG → PPB first, then import the resulting .ppb."));
        return;
    }
    importPreferences.setValue(QStringLiteral("files/gameResourceImportLastDirectory"),
        QFileInfo(path).absolutePath());
    Resource r;
    r.kind = kind;
    r.plane = kind == QStringLiteral("background") ? QStringLiteral("background")
        : (kind == QStringLiteral("palette") && plane == QStringLiteral("background")
          ? QStringLiteral("background") : QStringLiteral("foreground"));
    r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    r.name = QFileInfo(path).completeBaseName();
    r.path = storedPath(path);
    // Imported graphics appear where the editor is currently looking,
    // irrespective of the running game's camera position.
    const QPointF centre = m_view
        ? m_view->mapToScene(m_view->viewport()->rect().center())
        : QPointF(m_cameraX->value() + 40, m_cameraY->value() + 40);
    r.x = qBound(0, qRound(centre.x()), qMax(0, m_worldWidth->value()-1));
    r.y = qBound(0, qRound(centre.y()), qMax(0, m_worldHeight->value()-1));
    suggestSpriteCells(r);
    rememberResourceEdit();
    m_resources.append(r);
    const int addedIndex = m_resources.size() - 1;
    if (r.kind == QStringLiteral("palette")) {
        QString &active = r.plane == QStringLiteral("background")
            ? m_activeBackgroundPalette : m_activeForegroundPalette;
        if (active.isEmpty()) active = r.id;
    } else if (r.kind == QStringLiteral("background")) suggestFirstBackgroundPalette(r);
    rebuildScene();
    refreshResources();
    selectResource(addedIndex);
    setDirty();
}

// If no background CLUT is configured yet, the first indexed background
// provides a useful starting palette. Its PPB remains completely unchanged.
// A palette tree resource can reference a PPB directly (readPalette supports it).
void SidboxGameDesigner::suggestFirstBackgroundPalette(const Resource &background)
{
    if (background.kind != QStringLiteral("background")
        || !m_activeBackgroundPalette.isEmpty() || background.path.isEmpty()) return;
    for (const Resource &r : m_resources)
        if (r.kind == QStringLiteral("palette") && r.plane == QStringLiteral("background")) return;
    const QString absolute = resolvedPath(background.path);
    if (QFileInfo(absolute).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) != 0)
        return; // PNG doesn't necessarily have meaningful absolute indices.
    QString error;
    const QVector<QRgb> bank = SidboxGamePalette::readPalette(absolute, true, &error);
    if (bank.size() != 256) return;
    Resource palette;
    palette.kind = QStringLiteral("palette");
    palette.plane = QStringLiteral("background");
    palette.name = background.name + QStringLiteral("_background_CLUT");
    palette.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    palette.path = background.path; // Reference only — never write a duplicate.
    m_activeBackgroundPalette = palette.id;
    m_resources.append(palette);
}

void SidboxGameDesigner::importDroppedFiles(const QStringList &paths, const QString &targetKind,
                                            const QString &targetPlane)
{
    QStringList warnings;
    int added = 0;
    int lastImportedIndex = -1;
    bool recorded = false;
    for (const QString &path : paths) {
        const QFileInfo info(path);
        if (!info.isFile()) continue;
        if (info.suffix().compare(QStringLiteral("sbpi"), Qt::CaseInsensitive) == 0) {
            const QDir project(QFileInfo(m_filePath).absolutePath());
            if (QFileInfo(info.absoluteFilePath()).absoluteFilePath() !=
                QFileInfo(GamePlayerProfile::profilePath(project)).absoluteFilePath()) {
                warnings << tr("Shared player must be stored at players/player.sbpi in this project.");
                continue;
            }
            QJsonObject check;
            QString error;
            if (!GamePlayerProfile::read(project, &check, &error)) {
                warnings << error; continue;
            }
            m_playerProfile = QStringLiteral("players/player.sbpi");
            setDirty(); refreshResources(); ++added;
            continue;
        }
        const QString guessed = assetKindForFile(path);
        const QString category = targetKind.isEmpty()
            ? (guessed.isEmpty() ? QStringLiteral("sprite") : guessed) : targetKind;
        if (category == QStringLiteral("tileatlas")) {
            if (info.suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) != 0) {
                warnings << tr("%1: Tile Atlases accepts PPB files only").arg(info.fileName());
                continue;
            }
        } else if (guessed != category) {
            warnings << tr("%1: %2 dropped into %3")
                .arg(info.fileName(), guessed.isEmpty() ? tr("unknown type") : guessed, category);
        }
        Resource r;
        r.kind = category;
        r.plane = category == QStringLiteral("background") ? QStringLiteral("background")
            : (category == QStringLiteral("palette") && targetPlane == QStringLiteral("background")
               ? QStringLiteral("background") : QStringLiteral("foreground"));
        r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        r.name = info.completeBaseName();
        r.path = storedPath(info.absoluteFilePath());
        const QPointF visibleCentre = m_view
            ? m_view->mapToScene(m_view->viewport()->rect().center())
            : QPointF(m_cameraX->value() + 40, m_cameraY->value() + 40);
        r.x = qBound(0, qRound(visibleCentre.x()), qMax(0, m_worldWidth->value()-1));
        r.y = qBound(0, qRound(visibleCentre.y()), qMax(0, m_worldHeight->value()-1));
        suggestSpriteCells(r);
        if (!recorded) { rememberResourceEdit(); recorded = true; }
        m_resources.append(r);
        lastImportedIndex = m_resources.size() - 1;
        if (r.kind == QStringLiteral("palette")) {
            QString &active = r.plane == QStringLiteral("background")
                ? m_activeBackgroundPalette : m_activeForegroundPalette;
            if (active.isEmpty()) active = r.id;
        } else if (r.kind == QStringLiteral("background")) suggestFirstBackgroundPalette(r);
        ++added;
        if (added >= 128) break;
    }
    if (!added) {
        if (!warnings.isEmpty()) QMessageBox::warning(this, tr("Resource import"), warnings.join(QLatin1Char('\n')));
        return;
    }
    rebuildScene();
    refreshResources();
    if (lastImportedIndex >= 0) selectResource(lastImportedIndex);
    setDirty();
    if (!warnings.isEmpty()) QMessageBox::warning(this, tr("Resource type mismatch"),
        tr("The files were added as requested, but check their type:\n%1")
            .arg(warnings.mid(0, 10).join(QLatin1Char('\n'))));
}

void SidboxGameDesigner::addPlaceholder()
{
    Resource r;
    r.kind = QStringLiteral("sprite");
    r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    r.name = QStringLiteral("sprite_%1").arg(m_resources.size() + 1);
    // Imported graphics appear where the editor is currently looking,
    // irrespective of the running game's camera position.
    const QPointF centre = m_view
        ? m_view->mapToScene(m_view->viewport()->rect().center())
        : QPointF(m_cameraX->value() + 40, m_cameraY->value() + 40);
    r.x = qBound(0, qRound(centre.x()), qMax(0, m_worldWidth->value()-1));
    r.y = qBound(0, qRound(centre.y()), qMax(0, m_worldHeight->value()-1));
    rememberResourceEdit();
    m_resources.append(r);
    rebuildScene();
    refreshResources();
    selectResource(m_resources.size() - 1);
    setDirty();
}

void SidboxGameDesigner::deleteSelectedResource()
{
    const int index = selectedIndex();
    if (index < 0) return;
    rememberResourceEdit();
    m_resources.removeAt(index);  // only reference is removed; source file untouched
    rebuildScene();
    refreshResources();
    m_resourceTree->clearSelection();
    m_resourceTree->setCurrentItem(nullptr);
    refreshProperties();
    setDirty();
}

void SidboxGameDesigner::pickResourceFile()
{
    const int index = selectedIndex();
    if (index < 0) return;
    const bool atlasResource = m_resources.at(index).kind == QStringLiteral("tileatlas");
    const QString path = QFileDialog::getOpenFileName(this, tr("Choose resource file"),
        QFileInfo(m_filePath).absolutePath(), atlasResource
            ? tr("SIDBOX Tile Atlas (*.ppb)") : tr("All Files (*)"));
    if (path.isEmpty()) return;
    if (atlasResource && QFileInfo(path).suffix().compare(
            QStringLiteral("ppb"), Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(this, tr("Tile Atlas"), tr("Tile atlases must be PPB files."));
        return;
    }
    // Replacing the PPB referenced by this resource should not leave the
    // tilemap silently pointing at the old location. This does not rewrite
    // the graphics/collision arrays; check the replacement's tile layout.
    const bool replaceActiveAtlas = atlasResource && m_tilemapEnabled
        && !m_tilemap.atlasPath.isEmpty() && !m_resources.at(index).path.isEmpty()
        && QDir::cleanPath(resolvedPath(m_tilemap.atlasPath)) ==
           QDir::cleanPath(resolvedPath(m_resources.at(index).path));
    rememberResourceEdit();
    m_resources[index].path = storedPath(path);
    if (replaceActiveAtlas) m_tilemap.atlasPath = storedPath(path);
    suggestSpriteCells(m_resources[index]);
    rebuildScene();
    refreshResources();
    selectResource(index);
    setDirty();
}

void SidboxGameDesigner::importPngAsPpb(const QString &suggestedKind)
{
    if (m_pngConversionRunning) return;
    // Intentionally PNG-only: keep the alpha channel and reserve palette index 0.
    QSettings pngPreferences(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    QString pngDirectory = pngPreferences.value(QStringLiteral("files/pngImportLastDirectory"),
        QFileInfo(m_filePath).absolutePath()).toString();
    if (!QDir(pngDirectory).exists()) pngDirectory = QFileInfo(m_filePath).absolutePath();
    const QString pngPath = QFileDialog::getOpenFileName(this, tr("Import PNG Image"),
        pngDirectory, tr("PNG Images (*.png)"));
    if (pngPath.isEmpty()) return;
    pngPreferences.setValue(QStringLiteral("files/pngImportLastDirectory"),
        QFileInfo(pngPath).absolutePath());
    if (QFileInfo(pngPath).suffix().compare(QStringLiteral("png"), Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(this, tr("PNG Import"), tr("Only PNG images are supported by this importer."));
        return;
    }
    QImageReader reader(pngPath);
    reader.setAutoTransform(true);
    const QSize nativeSize = reader.size();
    if (nativeSize.isValid() && (nativeSize.width() > 65535 || nativeSize.height() > 65535
        || qint64(nativeSize.width()) * nativeSize.height() > 16LL * 1024 * 1024)) {
        QMessageBox::warning(this, tr("PNG Import"), tr("PNG exceeds the 16-million-pixel PPB safety limit."));
        return;
    }
    const QImage image = reader.read();
    if (image.isNull() || qint64(image.width()) * image.height() > 16LL * 1024 * 1024) {
        QMessageBox::warning(this, tr("PNG Import"),
            image.isNull() ? reader.errorString() : tr("Image exceeds 16 million pixels."));
        return;
    }
    const QString initialKind = (suggestedKind == QStringLiteral("sprite")
        || suggestedKind == QStringLiteral("tileatlas")
        || suggestedKind == QStringLiteral("background"))
        ? suggestedKind : QStringLiteral("tileatlas");
    PngPaletteImportDialog dialog(image, activePalette(QStringLiteral("foreground")),
                                  activePalette(QStringLiteral("background")), initialKind,
                                  m_planeMode->currentIndex() == 1, this);
    if (dialog.exec() != QDialog::Accepted) return;
    const auto options = dialog.options();
    const QString kind = dialog.destinationKind();
    const QString plane = dialog.palettePlane();
    const QVector<QRgb> startingPalette = dialog.basePalette();
    const QString projectFolder = QFileInfo(m_filePath).absolutePath();
    const QString suggestedPpb = QDir(projectFolder).filePath(
        QFileInfo(pngPath).completeBaseName() + QStringLiteral(".ppb"));
    const QString selectedPpb = QFileDialog::getSaveFileName(this, tr("Save Converted PPB"),
        suggestedPpb, tr("SIDBOX PPB (*.ppb)"));
    if (selectedPpb.isEmpty()) return;
    const QString destination = selectedPpb.endsWith(QStringLiteral(".ppb"), Qt::CaseInsensitive)
        ? selectedPpb : selectedPpb + QStringLiteral(".ppb");
    if (QFileInfo::exists(destination) && QMessageBox::question(this, tr("Overwrite PPB?"),
        tr("This replaces an existing PPB and could affect resources referencing it.\n%1\nContinue?")
            .arg(destination)) != QMessageBox::Yes) return;

    QString paletteDestination;
    if (options.buildColours) {
        QDir(projectFolder).mkpath(QStringLiteral("gamepalettes"));
        QString paletteSuggestion = QDir(projectFolder).filePath(
            QStringLiteral("gamepalettes/png_import_%1.pal").arg(plane));
        const QString activeId = plane == QStringLiteral("background")
            ? m_activeBackgroundPalette : m_activeForegroundPalette;
        for (const Resource &r : m_resources) {
            if (r.kind == QStringLiteral("palette") && r.plane == plane && r.id == activeId) {
                const QString currentPath = resolvedPath(r.path);
                if (QFileInfo(currentPath).suffix().compare(QStringLiteral("pal"), Qt::CaseInsensitive) == 0)
                    paletteSuggestion = currentPath;
                break;
            }
        }
        const QString chosen = QFileDialog::getSaveFileName(this, tr("Save Shared Palette (CLUT)"),
            paletteSuggestion, tr("SIDBOX Palette (*.pal)"));
        if (chosen.isEmpty()) return;
        paletteDestination = chosen.endsWith(QStringLiteral(".pal"), Qt::CaseInsensitive)
            ? chosen : chosen + QStringLiteral(".pal");
        if (!QDir().mkpath(QFileInfo(paletteDestination).absolutePath())) {
            QMessageBox::warning(this, tr("PNG Import"), tr("Could not create the palette directory."));
            return;
        }
        if (QFileInfo::exists(paletteDestination)) {
            const QString warning = tr(
                "The palette file already exists. Only indices %1–%2 in the %3 bank will "
                "receive new colours; indices outside this range come from the palette "
                "selected in the importer. Existing PPBs using the changed indices may "
                "change appearance. This cannot be undone with Game Resources Undo.\n\nOverwrite bank in:\n%4?")
                .arg(options.first).arg(options.last).arg(plane).arg(paletteDestination);
            if (QMessageBox::warning(this, tr("Modify Shared Palette?"), warning,
                QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Cancel) != QMessageBox::Yes) return;
        }
    }
    struct ConversionResult { bool succeeded = false; QString error; int colours = 0; };
    const auto result = std::make_shared<ConversionResult>();
    auto *progress = new QProgressDialog(tr("Converting PNG and preparing indexed palette..."),
                                         QString(), 0, 0, this);
    progress->setWindowTitle(tr("PNG → PPB"));
    progress->setCancelButton(nullptr);
    progress->setMinimumDuration(0);
    progress->setWindowModality(Qt::WindowModal);
    progress->show();
    m_pngConversionRunning = true;
    QThread *thread = QThread::create([image, options, startingPalette, destination,
                                        paletteDestination, plane, result]() {
        SidboxPngImport::Result converted;
        if (!SidboxPngImport::convert(image, startingPalette, options, &converted, &result->error)) return;
        // Both formats use QSaveFile inside their writers; source PNG is never touched.
        // PPB first: do not modify a shared palette if writing the image fails.
        if (!SidboxPpb::write(destination, converted.picture, &result->error)) return;
        if (!paletteDestination.isEmpty()) {
            const QFileInfo paletteInfo(paletteDestination);
            QVector<QRgb> otherBank;
            if (paletteInfo.exists() && paletteInfo.size() == 2048) {
                otherBank = SidboxGamePalette::readPalette(
                    paletteDestination, plane != QStringLiteral("background"), &result->error);
                if (otherBank.size() != 256) return;
            }
            const bool written = otherBank.isEmpty()
                ? SidboxGamePalette::writeSinglePal(paletteDestination, converted.palette, &result->error)
                : (plane == QStringLiteral("background")
                    ? SidboxGamePalette::writePal(paletteDestination, otherBank, converted.palette, &result->error)
                    : SidboxGamePalette::writePal(paletteDestination, converted.palette, otherBank, &result->error));
            if (!written) {
                result->error += QStringLiteral("\nThe PPB file was written, but the palette could not be saved. "
                                                "Check the PPB before using it in the game.");
                return;
            }
        }
        result->colours = converted.paletteColours;
        result->succeeded = true;
    });
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, this, [this, result, destination,
                                                paletteDestination, plane, kind, image, progress]() {
        progress->close();
        progress->deleteLater();
        m_pngConversionRunning = false;
        if (!result->succeeded) {
            QMessageBox::warning(this, tr("PNG Import"), tr("Import was not completed: %1").arg(result->error));
            return;
        }
        Resource r;
        r.kind = kind;
        r.plane = kind == QStringLiteral("background") ? QStringLiteral("background") : plane;
        r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        r.name = QFileInfo(destination).completeBaseName();
        r.path = storedPath(destination);
        r.x = m_cameraX->value() + 40;
        r.y = m_cameraY->value() + 40;
        // An imported PNG is upright/row-major. The SIDBOX direct background
        // needs column-major pixels: code generation must transpose it.
        // Treating it as an ordinary sprite, or as a pre-prepared PPB,
        // produces a correct-looking editor preview but the wrong V1 output.
        if (kind == QStringLiteral("background")) {
            r.backgroundMode = QStringLiteral("direct_convert");
            r.x = 0;
            r.y = 0;
            r.scale = 100;
        }
        suggestSpriteCells(r);

        // Overwriting a PPB already used by a background must update that
        // SAME resource, rather than append a duplicate referring to the
        // same path. Preserve its ID (and any active references to it).
        int importedIndex = -1;
        if (kind == QStringLiteral("background")) {
            const QString importedPath = QDir::cleanPath(QFileInfo(destination).absoluteFilePath());
            for (int i = 0; i < m_resources.size(); ++i) {
                if (m_resources.at(i).kind == QStringLiteral("background")
                    && QDir::cleanPath(resolvedPath(m_resources.at(i).path)) == importedPath) {
                    importedIndex = i;
                    break;
                }
            }
            // A *new* PPB name is often intended to replace the sole old
            // background. Ask, since Game Designer supports only one direct
            // background and blindly adding another makes export fail.
            if (importedIndex < 0) {
                int soleBackground = -1;
                for (int i = 0; i < m_resources.size(); ++i) {
                    if (m_resources.at(i).kind != QStringLiteral("background")) continue;
                    if (soleBackground >= 0) { soleBackground = -2; break; }
                    soleBackground = i;
                }
                if (soleBackground >= 0) {
                    const auto answer = QMessageBox::question(this,
                        tr("Replace Existing Background?"),
                        tr("A background is already in this world.\n\n"
                           "Replace '%1' with the newly imported background?\n\n"
                           "Yes: update that resource without creating a duplicate.\n"
                           "No: keep both resources (only one may be direct at export).")
                            .arg(m_resources.at(soleBackground).name),
                        QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    if (answer == QMessageBox::Yes)
                        importedIndex = soleBackground;
                }
            }
        }
        rememberResourceEdit();
        if (importedIndex >= 0) {
            Resource &existing = m_resources[importedIndex];
            existing.name = r.name;
            existing.path = r.path;
            existing.plane = QStringLiteral("background");
            existing.backgroundMode = QStringLiteral("direct_convert");
            existing.x = 0;
            existing.y = 0;
            existing.scale = 100;
            existing.frame = 0;
            existing.cellWidth = r.cellWidth;
            existing.cellHeight = r.cellHeight;
        } else {
            importedIndex = m_resources.size();
            m_resources.append(r);
        }
        if (!paletteDestination.isEmpty()) {
            bool found = false;
            for (Resource &resource : m_resources) {
                if (resource.kind == QStringLiteral("palette") && resource.plane == plane
                    && resolvedPath(resource.path) == paletteDestination) {
                    if (plane == QStringLiteral("background")) m_activeBackgroundPalette = resource.id;
                    else m_activeForegroundPalette = resource.id;
                    found = true;
                    break;
                }
            }
            if (!found) {
                Resource palette;
                palette.kind = QStringLiteral("palette");
                palette.plane = plane;
                palette.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
                palette.name = QFileInfo(paletteDestination).completeBaseName();
                palette.path = storedPath(paletteDestination);
                m_resources.append(palette);
                if (plane == QStringLiteral("background")) m_activeBackgroundPalette = palette.id;
                else m_activeForegroundPalette = palette.id;
            }
            m_paletteCache.clear(); // CLUT file is fixed-size; timestamp alone may not change!
        }
        if (kind == QStringLiteral("background")) suggestFirstBackgroundPalette(r);
        // A PPB overwritten very quickly can have unchanged size and disk
        // timestamp. Drop preview copies explicitly so the editor shows the
        // freshly converted pixels instead of a stale cached image.
        m_imageCache.clear();
        m_imageCacheOrder.clear();
        m_imageCacheBytes = 0;
        rebuildScene();
        refreshResources();
        selectResource(importedIndex);
        setDirty();
        if (assetFilesChanged) assetFilesChanged();
        QMessageBox::information(this, tr("PNG → PPB"),
            tr("Created %1 (%2 × %3) using %4 palette colours.\n"
               "Index 0 is transparent. Original PNG unchanged.\n"
               "%5")
                .arg(QFileInfo(destination).fileName())
                .arg(image.width()).arg(image.height()).arg(result->colours)
                .arg(paletteDestination.isEmpty() ? tr("Used existing CLUT; no palette modified.")
                        : tr("Shared CLUT saved: %1").arg(paletteDestination)));
    });
    thread->start();
}

void SidboxGameDesigner::exportSelectedC()
{
    const int index = selectedIndex();
    if (index < 0 || !visualKind(m_resources.at(index).kind)) {
        QMessageBox::information(this, tr("Embedded C Resource"), tr("Select a sprite or background first."));
        return;
    }
    const Resource &r = m_resources.at(index);
    if (r.path.isEmpty()) {
        QMessageBox::information(this, tr("Embedded C Resource"), tr("Choose an image file first.")); return;
    }
    const QString input = resolvedPath(r.path);
    SidboxPpb::Picture picture;
    QString error;
    if (QFileInfo(input).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) == 0) {
        if (!SidboxPpb::read(input, &picture, &error)) {
            QMessageBox::warning(this, tr("Embedded C Resource"), error); return;
        }
    } else {
        QImageReader reader(input);
        reader.setAutoTransform(true);
        const QImage image = reader.read();
        if (image.isNull() || !SidboxPpb::fromImage(image, &picture, &error)) {
            QMessageBox::warning(this, tr("Embedded C Resource"),
                error.isEmpty() ? reader.errorString() : error); return;
        }
    }
    const QString suggested = QFileInfo(m_filePath).absoluteDir().filePath(
        SidboxPpb::identifier(r.name) + QStringLiteral("_resource.c"));
    const QString cName = QFileDialog::getSaveFileName(this, tr("Export Embedded V1 C Resource"),
        suggested, tr("C source (*.c)"));
    if (cName.isEmpty()) return;
    const QString cPath = cName.endsWith(QStringLiteral(".c"), Qt::CaseInsensitive)
        ? cName : cName + QStringLiteral(".c");
    const QFileInfo cInfo(cPath);
    const QString hPath = cInfo.dir().filePath(cInfo.completeBaseName() + QStringLiteral(".h"));
    if ((QFileInfo::exists(cPath) || QFileInfo::exists(hPath))
        && QMessageBox::question(this, tr("Overwrite Generated Resources?"),
           tr("One or both generated files already exist. Replace them?\n%1\n%2")
             .arg(cPath, hPath)) != QMessageBox::Yes) return;
    const qint64 bytes = qint64(picture.indexed.width()) * picture.indexed.height() + 1024;
    if (QMessageBox::question(this, tr("Export Embedded C"),
        tr("This will create a .c and .h file containing approximately %1 bytes of indexed "
           "graphics/palette data before compiler overhead. The project scanner may compile "
           "the .c file on the next F5. Continue?").arg(bytes)) != QMessageBox::Yes) return;
    if (!SidboxPpb::exportC(cPath, r.name, picture, &error,
                            QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")))) {
        QMessageBox::warning(this, tr("Embedded C Resource"), error); return;
    }
    if (assetFilesChanged) assetFilesChanged();
    QMessageBox::information(this, tr("Embedded C Resource"),
        tr("Created %1 and %2.\n"
           "Use the generated pixel array and palette from your V1 game code. "
           "No existing game logic was modified.")
          .arg(cInfo.fileName(), QFileInfo(hPath).fileName()));
}


// Sprite Stamps are lookup tables over their ORIGINAL PPB sheet. Never write
// a second PPB: generated gameworlditems.c holds the cell IDs and flip flags.
bool SidboxGameDesigner::updateSpriteStamp(Resource &resource, QString *error)
{
    if (!resource.spriteStamp.active()) return true;
    const QString sourcePath = resolvedPath(resource.spriteStamp.sourcePath);
    SidboxPpb::Picture source;
    if (!SidboxPpb::read(sourcePath, &source, error)) return false;
    // Validate every cell against the PPB now, without exporting/compressing it.
    if (resource.spriteStamp.compose(source.indexed, error).isNull()) return false;
    resource.path = storedPath(sourcePath);
    resource.cellWidth = SidboxSpriteStamp::cellPixels;
    resource.cellHeight = SidboxSpriteStamp::cellPixels;
    resource.frame = 0;
    resource.objectAnimated = false;
    return true;
}

// Game object editing deliberately lives alongside the existing sprite tree.
// The sprite remains the authoritative WORLD placement and bitmap reference.
void SidboxGameDesigner::configureGameObject(int index)
{
    if (index < 0 || index >= m_resources.size() ||
        m_resources.at(index).kind != QStringLiteral("sprite")) return;
    Resource old = m_resources.at(index);
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Game Object Properties - %1").arg(old.name));
    // Stage 3.93: three-column, theme-accented Game Object workstation.
    // All original controls and Resource fields are retained; only the editor
    // presentation changes. This dialog never creates new runtime behaviours.
    dialog.resize(1180, 710);
    dialog.setMinimumSize(930, 580);
    QSettings objectWindowSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    const QByteArray objectSavedGeometry = objectWindowSettings.value(
        QStringLiteral("GameObjectProperties/geometry")).toByteArray();
    const bool objectWindowWasMaximized = objectWindowSettings.value(
        QStringLiteral("GameObjectProperties/maximized"), false).toBool();
    const auto colour = [](const QColor &c) { return ideThemeColorName(c); };
    // Selection foreground MUST contrast with the (potentially dark)
    // theme-accent selection background, including in light IDE themes.
    const QColor objectSelectionBg = m_theme.accent.darker(230);
    const QColor objectSelectionFg = objectSelectionBg.lightnessF() < 0.52
        ? QColor(Qt::white) : QColor(Qt::black);
    dialog.setStyleSheet(styleSheet() + QStringLiteral(R"GGSTYLE(
        QDialog { background:%1; color:%2; border-radius:0px; }
        QFrame#GGObjectCard { background:%3; border:1px solid %4; border-radius:0px; }
        QWidget#GGSectionBar { background:%5; border-left:3px solid %6; }
        QToolButton#GGSectionHeader { background:transparent; color:%2; border:0px;
          padding:9px 10px; text-align:left; font-weight:bold; border-radius:0px; }
        QToolButton#GGSectionHeader:hover, QToolButton#GGSectionArrow:hover { background:%7; }
        QToolButton#GGSectionArrow { background:transparent; color:%2; border:0px;
          padding:6px; font-weight:bold; border-radius:0px; }
        QLabel#GGSideSection { background:%5; color:%2; border-left:3px solid %6;
          padding:7px 9px; font-weight:bold; }
        QListWidget#GGObjectTypes { background:%3; color:%2; border:1px solid %4;
          border-radius:0px; outline:0px; }
        QListWidget#GGObjectTypes::item { padding:8px; border:1px solid %4;
          border-radius:0px; margin-bottom:2px; }
        QListWidget#GGObjectTypes::item:selected { background:%8; color:%10;
          border:1px solid %6; border-left:3px solid %6; }
        QListWidget#GGObjectTypes::item:hover { border-color:%6; }
        QLabel#GGPreviewImage { background:%1; border:1px solid %4; }
        QLabel#GGHelper { color:%9; }
        /* Generic controls and checkboxes inherit the central IDE theme. */
    )GGSTYLE")
        .arg(colour(m_theme.windowBackground)).arg(colour(m_theme.text))
        .arg(colour(m_theme.panelBackground)).arg(colour(m_theme.border))
        .arg(colour(m_theme.alternateBackground)).arg(colour(m_theme.accent))
        .arg(colour(m_theme.hover)).arg(colour(m_theme.accent.darker(230)))
        .arg(colour(m_theme.mutedText)).arg(colour(objectSelectionFg)));

    QVBoxLayout layout(&dialog);
    layout.setContentsMargins(10, 10, 10, 10);
    layout.setSpacing(9);
    // Header: the actual Game Objects tree icon, then direct previous/next
    // navigation through the same configured sprites listed in that tree.
    auto *objectHeading = new QHBoxLayout;
    objectHeading->setSpacing(9);
    auto *objectIcon = new QLabel(&dialog);
    objectIcon->setFixedSize(44, 44);
    const QPixmap objectArt = gameResourceIcon(QStringLiteral("gr_icon_object.png")).pixmap(44, 44);
    objectIcon->setPixmap(objectArt.scaled(40, 40, Qt::KeepAspectRatio, Qt::FastTransformation));
    objectIcon->setAlignment(Qt::AlignCenter);
    objectHeading->addWidget(objectIcon);
    auto *heading = new QLabel(tr("GAME OBJECT PROPERTIES :"), &dialog);
    QFont headingFont = heading->font();
    headingFont.setBold(true);
    headingFont.setPointSize(qMax(11, headingFont.pointSize() + 2));
    heading->setFont(headingFont);
    objectHeading->addWidget(heading);
    const auto arrowIcon = [this](bool right) {
        QPixmap pix(16, 16);
        pix.fill(Qt::transparent);
        QPainter painter(&pix);
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setPen(QPen(m_theme.text, 2, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        if (right) {
            painter.drawLine(5, 3, 11, 8);
            painter.drawLine(11, 8, 5, 13);
        } else {
            painter.drawLine(11, 3, 5, 8);
            painter.drawLine(5, 8, 11, 13);
        }
        const QIcon custom = gameEditorExternalIcon(right
            ? QStringLiteral("game_object_next.png")
            : QStringLiteral("game_object_previous.png"));
        return custom.isNull() ? QIcon(pix) : custom;
    };
    auto *previousObject = new QToolButton(&dialog);
    auto *nextObject = new QToolButton(&dialog);
    previousObject->setIcon(arrowIcon(false));
    nextObject->setIcon(arrowIcon(true));
    for (auto *button : {previousObject, nextObject}) {
        button->setIconSize(QSize(16, 16));
        button->setFixedSize(30, 30);
        button->setAutoRaise(false);
    }
    previousObject->setToolTip(tr("Previous Game Object. Unchanged objects switch immediately; modified objects offer Save / No / Cancel."));
    nextObject->setToolTip(tr("Next Game Object. Unchanged objects switch immediately; modified objects offer Save / No / Cancel."));
    int previousIndex = -1, nextIndex = -1;
    for (int i = 0; i < m_resources.size(); ++i) {
        const Resource &candidate = m_resources.at(i);
        if (candidate.kind != QStringLiteral("sprite") ||
            candidate.objectType == QStringLiteral("decoration")) continue;
        if (i < index) previousIndex = i;
        if (i > index && nextIndex < 0) nextIndex = i;
    }
    previousObject->setEnabled(previousIndex >= 0);
    nextObject->setEnabled(nextIndex >= 0);
    auto *objectName = new QLabel(old.name, &dialog);
    objectName->setMinimumWidth(90);
    objectName->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);
    objectName->setMaximumWidth(285);
    objectName->setToolTip(old.name);
    objectHeading->addWidget(previousObject);
    objectHeading->addWidget(objectName);
    objectHeading->addWidget(nextObject);
    objectHeading->addStretch(1);
    layout.addLayout(objectHeading);

    // The same animated WORLD scene is shown here at a useful zoom. This
    // matters when the Properties dialog is maximised and hides the editor.
    // It is read-only, and never creates a second particle simulation.
    auto *particlePreviewDock = new QWidget(&dialog);
    particlePreviewDock->setObjectName(QStringLiteral("ParticleWorldPreviewDock"));
    auto *particlePreviewDockLayout = new QVBoxLayout(particlePreviewDock);
    particlePreviewDockLayout->setContentsMargins(4, 2, 4, 2);
    particlePreviewDockLayout->setSpacing(2);
    auto *particlePreviewCaption = new QLabel(tr(
        "LIVE WORLD CANVAS PREVIEW  •  Colours and movement are approximations of SIDBOX rendering"),
        particlePreviewDock);
    particlePreviewDockLayout->addWidget(particlePreviewCaption);
    auto *particlePreviewCanvas = new QGraphicsView(m_scene, particlePreviewDock);
    particlePreviewCanvas->setObjectName(QStringLiteral("ParticleWorldPreviewCanvas"));
    particlePreviewCanvas->setInteractive(false);
    particlePreviewCanvas->setDragMode(QGraphicsView::NoDrag);
    particlePreviewCanvas->setRenderHint(QPainter::SmoothPixmapTransform, false);
    particlePreviewCanvas->setBackgroundBrush(QColor(26, 31, 39));
    // This view shares the world's *moving* scene. Automatic scene bounds
    // grow/shrink as particle items move, which shifts Qt's scrollbars and
    // makes the little modal preview twitch at 50 Hz. Keep this VIEW's bounds
    // fixed to the selected emitter instead (never alter m_scene's bounds).
    particlePreviewCanvas->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    particlePreviewCanvas->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    particlePreviewCanvas->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    particlePreviewCanvas->setTransformationAnchor(QGraphicsView::NoAnchor);
    particlePreviewCanvas->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    particlePreviewCanvas->setMinimumHeight(140);
    particlePreviewCanvas->setMaximumHeight(205);
    particlePreviewDockLayout->addWidget(particlePreviewCanvas);
    layout.addWidget(particlePreviewDock);
    particlePreviewDock->hide();
    QRectF particlePreviewLastBounds;
    bool particlePreviewNeedsFit = true;

    // Each card can be collapsed. Hidden cards are real layouts rather than
    // disabled rows, so the editor adapts to the selected object behaviour.
    struct PropertyCard {
        QFrame *panel;
        QWidget *body;
        QFormLayout *form;
    };
    // Crisp 16x16 theme-colour symbols, drawn at runtime so custom themes work.
    const auto sectionIcon = [this](const QString &name) {
        QPixmap pix(16, 16);
        pix.fill(Qt::transparent);
        QPainter painter(&pix);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setPen(QPen(m_theme.accent, 1.7));
        painter.setBrush(Qt::NoBrush);
        if (name.contains(QStringLiteral("Audio"), Qt::CaseInsensitive)) {
            painter.drawRect(2, 6, 3, 5);
            painter.drawLine(5, 6, 9, 3);
            painter.drawLine(5, 11, 9, 13);
            painter.drawArc(QRect(6, 3, 8, 10), -65 * 16, 130 * 16);
        } else if (name.contains(QStringLiteral("Visual"), Qt::CaseInsensitive) ||
                   name.contains(QStringLiteral("Animation"), Qt::CaseInsensitive)) {
            painter.drawRect(2, 3, 12, 10);
            painter.drawEllipse(9, 5, 2, 2);
            painter.drawLine(3, 11, 7, 7);
            painter.drawLine(7, 7, 10, 11);
        } else if (name.contains(QStringLiteral("Collision"), Qt::CaseInsensitive)) {
            painter.drawRect(2, 2, 8, 8);
            painter.drawRect(6, 6, 8, 8);
        } else if (name.contains(QStringLiteral("General"), Qt::CaseInsensitive)) {
            painter.drawEllipse(2, 2, 12, 12);
            painter.drawLine(8, 5, 8, 11);
            painter.drawLine(5, 8, 11, 8);
        } else {
            painter.drawRect(3, 3, 10, 10);
            painter.drawLine(5, 8, 11, 8);
            painter.drawLine(8, 5, 8, 11);
        }
        return QIcon(pix);
    };
    auto makeCard = [&](const QString &name, bool expanded = true) -> PropertyCard {
        auto *panel = new QFrame(&dialog);
        panel->setObjectName(QStringLiteral("GGObjectCard"));
        auto *outer = new QVBoxLayout(panel);
        outer->setContentsMargins(0, 0, 0, 0);
        outer->setSpacing(0);
        auto *bar = new QWidget(panel);
        bar->setObjectName(QStringLiteral("GGSectionBar"));
        auto *barLayout = new QHBoxLayout(bar);
        barLayout->setContentsMargins(0, 0, 0, 0);
        barLayout->setSpacing(0);
        auto *toggle = new QToolButton(bar);
        toggle->setObjectName(QStringLiteral("GGSectionHeader"));
        toggle->setCheckable(true);
        toggle->setChecked(expanded);
        toggle->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        toggle->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toggle->setIcon(sectionIcon(name));
        toggle->setIconSize(QSize(16, 16));
        toggle->setText(name);
        auto *arrow = new QToolButton(bar);
        arrow->setObjectName(QStringLiteral("GGSectionArrow"));
        arrow->setFixedWidth(34);
        arrow->setText(expanded ? QStringLiteral("▾") : QStringLiteral("▸"));
        arrow->setToolTip(tr("Expand or collapse this section"));
        barLayout->addWidget(toggle, 1);
        barLayout->addWidget(arrow);
        outer->addWidget(bar);
        auto *body = new QWidget(panel);
        auto *formLayout = new QFormLayout(body);
        formLayout->setContentsMargins(12, 12, 12, 12);
        formLayout->setSpacing(8);
        formLayout->setLabelAlignment(Qt::AlignLeft | Qt::AlignVCenter);
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setRowWrapPolicy(QFormLayout::WrapLongRows);
        outer->addWidget(body);
        body->setVisible(expanded);
        connect(arrow, &QToolButton::clicked, toggle, &QToolButton::toggle);
        connect(toggle, &QToolButton::toggled, &dialog,
                [arrow, body](bool show) {
                    body->setVisible(show);
                    arrow->setText(show ? QStringLiteral("▾") : QStringLiteral("▸"));
                });
        return { panel, body, formLayout };
    };
    // General and visual settings apply to every sprite. Behaviour and sound
    // cards are shown only for the matching object type.
    const PropertyCard generalCard = makeCard(tr("General"));
    const PropertyCard visualCard = makeCard(tr("Visual & Movements"));
    SidboxSpriteStamp draftSpriteStamp = old.spriteStamp;
    auto *editSpriteStampButton = new QPushButton(tr("Arrange Sprite Stamp..."), &dialog);
    editSpriteStampButton->setToolTip(tr("Arrange 8x8 tiles from an indexed PPB sheet into one collectible or object sprite. Runtime draws the selected cells directly from that PPB; no extra PPB file is created."));
    visualCard.form->addRow(tr("Sprite Stamp"), editSpriteStampButton);
    connect(editSpriteStampButton, &QPushButton::clicked, &dialog, [&]() {
        // A source sheet can be any imported indexed PPB, not just the world's
        // collision tile atlas. The selected source is kept in the stamp data.
        QDialog editor(&dialog);
        editor.setWindowTitle(tr("Sprite Stamp - %1").arg(old.name));
        editor.setMinimumSize(900, 610);
        editor.resize(1060, 725);
        editor.setStyleSheet(dialog.styleSheet() + QStringLiteral(
            "QDialog, QTableWidget, QPushButton, QSpinBox, QComboBox { border-radius:0px; }"));
        QVBoxLayout box(&editor);
        auto *sourceRow = new QHBoxLayout;
        sourceRow->addWidget(new QLabel(tr("8 x 8 source PPB sheet:"), &editor));
        auto *sourceChoice = new QComboBox(&editor);
        sourceChoice->setMinimumWidth(280);
        QSet<QString> offered;
        const auto offer = [&](const QString &relative, const QString &caption) {
            if (relative.isEmpty() || offered.contains(relative)) return;
            const QString absolute = resolvedPath(relative);
            if (QFileInfo(absolute).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive)) return;
            offered.insert(relative);
            sourceChoice->addItem(caption, relative);
        };
        offer(draftSpriteStamp.sourcePath, tr("Current sheet: %1").arg(QFileInfo(draftSpriteStamp.sourcePath).fileName()));
        offer(old.spriteStamp.active() ? old.spriteStamp.sourcePath : old.path,
              tr("Object sprite: %1").arg(QFileInfo(old.path).fileName()));
        for (const Resource &candidate : m_resources)
            if (candidate.kind == QStringLiteral("tileatlas") || candidate.kind == QStringLiteral("sprite"))
                offer(candidate.path, candidate.name);
        sourceRow->addWidget(sourceChoice, 1);
        auto *browse = new QPushButton(tr("Choose PPB..."), &editor);
        sourceRow->addWidget(browse);
        auto *copyStamp = new QPushButton(tr("Copy stamp from..."), &editor);
        sourceRow->addWidget(copyStamp);
        box.addLayout(sourceRow);
        auto *dimensions = new QHBoxLayout;
        auto *widthSpin = new QSpinBox(&editor), *heightSpin = new QSpinBox(&editor);
        for (auto *spin : {widthSpin, heightSpin}) spin->setRange(1, 16);
        SidboxSpriteStamp working = draftSpriteStamp;
        if (!working.active()) {
            working.sourcePath = sourceChoice->currentData().toString();
            working.resize(2, 2);
        }
        widthSpin->setValue(working.width);
        heightSpin->setValue(working.height);
        dimensions->addWidget(new QLabel(tr("Width (cells)"), &editor));
        dimensions->addWidget(widthSpin);
        dimensions->addWidget(new QLabel(tr("Height (cells)"), &editor));
        dimensions->addWidget(heightSpin);
        auto *flipX = new QCheckBox(tr("Flip X on paint"), &editor);
        auto *flipY = new QCheckBox(tr("Flip Y on paint"), &editor);
        auto *erase = new QCheckBox(tr("Erase cell"), &editor);
        dimensions->addWidget(flipX); dimensions->addWidget(flipY); dimensions->addWidget(erase);
        dimensions->addStretch(1);
        box.addLayout(dimensions);
        auto *views = new QHBoxLayout;
        auto *sheetBox = new QVBoxLayout;
        sheetBox->addWidget(new QLabel(tr("1. Select source tile"), &editor));
        auto *sourceTable = new QTableWidget(&editor);
        sheetBox->addWidget(sourceTable, 1);
        views->addLayout(sheetBox, 1);
        auto *stampBox = new QVBoxLayout;
        stampBox->addWidget(new QLabel(tr("2. Click arrangement cells to paint"), &editor));
        auto *stampTable = new QTableWidget(&editor);
        stampBox->addWidget(stampTable, 1);
        auto *mirrorRow = new QHBoxLayout;
        auto *mirrorX = new QPushButton(tr("Mirror stamp X"), &editor);
        auto *mirrorY = new QPushButton(tr("Mirror stamp Y"), &editor);
        auto *clear = new QPushButton(tr("Clear all"), &editor);
        mirrorRow->addWidget(mirrorX); mirrorRow->addWidget(mirrorY); mirrorRow->addWidget(clear);
        stampBox->addLayout(mirrorRow);
        views->addLayout(stampBox, 1);
        box.addLayout(views, 1);
        auto *help = new QLabel(tr("Index 0 is transparent. Empty cells are transparent. "
            "Each placed cell keeps its own X/Y flips; whole-stamp mirrors reverse both cell positions and flips. "
            "Runtime reads the arranged 8x8 cells directly from the existing PPB sheet; no extra PPB is generated."), &editor);
        help->setWordWrap(true);
        box.addWidget(help);
        auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &editor);
        auto *remove = buttons->addButton(tr("Remove stamp"), QDialogButtonBox::ResetRole);
        box.addWidget(buttons);
        QImage source;
        int selectedTile = 0;
        auto updateCells = [&]() {
            stampTable->setRowCount(working.height);
            stampTable->setColumnCount(working.width);
            stampTable->horizontalHeader()->setVisible(false);
            stampTable->verticalHeader()->setVisible(false);
            stampTable->horizontalHeader()->setDefaultSectionSize(46);
            stampTable->verticalHeader()->setDefaultSectionSize(46);
            stampTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
            const int sourceCols = source.width() / 8;
            for (int y = 0; y < working.height; ++y)
                for (int x = 0; x < working.width; ++x) {
                    const int offset = y * working.width + x;
                    const int encoded = offset < working.cells.size() ? working.cells.at(offset) : -1;
                    auto *item = new QTableWidgetItem;
                    if (encoded >= 0 && sourceCols > 0) {
                        const int n = encoded & SidboxSpriteStamp::tileMask;
                        if (n < sourceCols * (source.height() / 8)) {
                            QImage cell = source.copy((n % sourceCols) * 8, (n / sourceCols) * 8, 8, 8);
                            Qt::Orientations flags;
                            if (encoded & SidboxSpriteStamp::flipX) flags |= Qt::Horizontal;
                            if (encoded & SidboxSpriteStamp::flipY) flags |= Qt::Vertical;
                            if (flags) cell = cell.flipped(flags);
                            item->setIcon(QIcon(QPixmap::fromImage(cell.scaled(40, 40,
                                Qt::IgnoreAspectRatio, Qt::FastTransformation))));
                        }
                        item->setToolTip(tr("Tile %1, flip X: %2, flip Y: %3")
                            .arg(n).arg(bool(encoded & SidboxSpriteStamp::flipX))
                            .arg(bool(encoded & SidboxSpriteStamp::flipY)));
                    } else item->setText(QStringLiteral("·"));
                    stampTable->setItem(y, x, item);
                }
        };
        auto selectSource = [&](const QString &path) {
            SidboxPpb::Picture picture;
            QString error;
            if (!SidboxPpb::read(resolvedPath(path), &picture, &error) ||
                picture.indexed.width() % 8 || picture.indexed.height() % 8) {
                QMessageBox::warning(&editor, tr("Sprite Stamp"),
                    error.isEmpty() ? tr("The source sheet dimensions must be divisible by 8.") : error);
                return false;
            }
            const QImage candidate = picture.indexed;
            const int tileCount = (candidate.width() / 8) * (candidate.height() / 8);
            if (tileCount > 4096) {
                QMessageBox::warning(&editor, tr("Sprite Stamp"),
                    tr("Source sheet exceeds 4096 cells. Please use a smaller 8x8 PPB sheet."));
                return false;
            }
            if (!working.sourcePath.isEmpty() && working.sourcePath != path)
                working.cells.fill(-1, working.width * working.height);
            source = candidate;
            const QVector<QRgb> bank = activePalette(QStringLiteral("foreground"));
            if (bank.size() == 256) source.setColorTable(colourPreviewBank(bank, true, true));
            working.sourcePath = path;
            const int cols = qMin(12, candidate.width() / 8);
            sourceTable->setColumnCount(cols);
            sourceTable->setRowCount((tileCount + cols - 1) / cols);
            sourceTable->horizontalHeader()->setVisible(false);
            sourceTable->verticalHeader()->setVisible(false);
            sourceTable->horizontalHeader()->setDefaultSectionSize(38);
            sourceTable->verticalHeader()->setDefaultSectionSize(38);
            sourceTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
            for (int i = 0; i < tileCount; ++i) {
                const int sourceCols = candidate.width() / 8;
                const QImage cell = source.copy((i % sourceCols) * 8, (i / sourceCols) * 8, 8, 8);
                auto *item = new QTableWidgetItem;
                item->setIcon(QIcon(QPixmap::fromImage(cell.scaled(32, 32,
                    Qt::IgnoreAspectRatio, Qt::FastTransformation))));
                item->setToolTip(tr("Source tile %1").arg(i));
                sourceTable->setItem(i / cols, i % cols, item);
            }
            selectedTile = 0;
            sourceTable->setCurrentCell(0, 0);
            updateCells();
            return true;
        };
        connect(sourceTable, &QTableWidget::cellClicked, &editor,
                [&](int row, int col) {
            const int id = row * sourceTable->columnCount() + col;
            if (id < (source.width() / 8) * (source.height() / 8)) selectedTile = id;
        });
        connect(stampTable, &QTableWidget::cellClicked, &editor,
                [&](int row, int col) {
            const int cell = row * working.width + col;
            if (cell < 0 || cell >= working.cells.size()) return;
            working.cells[cell] = erase->isChecked() ? -1
                : selectedTile | (flipX->isChecked() ? SidboxSpriteStamp::flipX : 0)
                               | (flipY->isChecked() ? SidboxSpriteStamp::flipY : 0);
            updateCells();
        });
        connect(widthSpin, qOverload<int>(&QSpinBox::valueChanged), &editor,
                [&](int value) { working.resize(value, working.height); updateCells(); });
        connect(heightSpin, qOverload<int>(&QSpinBox::valueChanged), &editor,
                [&](int value) { working.resize(working.width, value); updateCells(); });
        connect(mirrorX, &QPushButton::clicked, &editor,
                [&]() { working.mirror(true); updateCells(); });
        connect(mirrorY, &QPushButton::clicked, &editor,
                [&]() { working.mirror(false); updateCells(); });
        connect(clear, &QPushButton::clicked, &editor,
                [&]() { working.cells.fill(-1, working.width * working.height); updateCells(); });
        connect(copyStamp, &QPushButton::clicked, &editor, [&]() {
            QStringList names;
            QVector<int> indices;
            for (int i = 0; i < m_resources.size(); ++i) {
                if (m_resources.at(i).id == old.id || !m_resources.at(i).spriteStamp.active()) continue;
                names.append(m_resources.at(i).name);
                indices.append(i);
            }
            if (indices.isEmpty()) {
                QMessageBox::information(&editor, tr("Sprite Stamp"),
                    tr("No other game object has a saved sprite stamp yet."));
                return;
            }
            bool accepted = false;
            const QString selected = QInputDialog::getItem(&editor, tr("Copy Sprite Stamp"),
                tr("Choose a Game Object:"), names, 0, false, &accepted);
            if (!accepted) return;
            const int chosen = names.indexOf(selected);
            if (chosen < 0) return;
            const SidboxSpriteStamp previous = working;
            working = m_resources.at(indices.at(chosen)).spriteStamp;
            widthSpin->setValue(working.width);
            heightSpin->setValue(working.height);
            if (!selectSource(working.sourcePath)) {
                working = previous;
                widthSpin->setValue(working.width);
                heightSpin->setValue(working.height);
                selectSource(working.sourcePath);
                return;
            }
            const int option = sourceChoice->findData(working.sourcePath);
            if (option < 0) sourceChoice->addItem(QFileInfo(working.sourcePath).fileName(), working.sourcePath);
            sourceChoice->setCurrentIndex(qMax(0, sourceChoice->findData(working.sourcePath)));
            updateCells();
        });
        connect(sourceChoice, qOverload<int>(&QComboBox::currentIndexChanged), &editor,
                [&](int) { selectSource(sourceChoice->currentData().toString()); });
        connect(browse, &QPushButton::clicked, &editor, [&]() {
            const QString filename = QFileDialog::getOpenFileName(&editor, tr("Select 8x8 tile sheet"),
                QFileInfo(m_filePath).absolutePath(), tr("SIDBOX PPB (*.ppb)"));
            if (filename.isEmpty()) return;
            const QString relative = storedPath(filename);
            if (selectSource(relative)) {
                sourceChoice->addItem(QFileInfo(filename).fileName(), relative);
                sourceChoice->setCurrentIndex(sourceChoice->count() - 1);
            }
        });
        connect(buttons, &QDialogButtonBox::rejected, &editor, &QDialog::reject);
        connect(buttons, &QDialogButtonBox::accepted, &editor, [&]() {
            QString error;
            if (working.sourcePath.isEmpty() || working.compose(
                    [&]() { SidboxPpb::Picture p;
                        if (!SidboxPpb::read(resolvedPath(working.sourcePath), &p, &error)) return QImage();
                        return p.indexed; }(), &error).isNull()) {
                QMessageBox::warning(&editor, tr("Sprite Stamp"),
                    error.isEmpty() ? tr("Choose a valid 8x8 indexed PPB sheet first.") : error);
                return;
            }
            editor.accept();
        });
        bool removeStamp = false;
        connect(remove, &QPushButton::clicked, &editor, [&]() {
            removeStamp = true; editor.accept();
        });
        if (sourceChoice->count() > 0) selectSource(sourceChoice->currentData().toString());
        else help->setText(tr("Choose an 8x8-aligned PPB sheet using Choose PPB..."));
        if (editor.exec() != QDialog::Accepted) return;
        if (removeStamp) draftSpriteStamp = SidboxSpriteStamp();
        else draftSpriteStamp = working;
        editSpriteStampButton->setText(draftSpriteStamp.active()
            ? tr("Edit Sprite Stamp (%1 x %2 tiles)...")
                .arg(draftSpriteStamp.width).arg(draftSpriteStamp.height)
            : tr("Arrange Sprite Stamp..."));
    });
    const PropertyCard animationCard = makeCard(tr("Animation Frames"));
    const PropertyCard collisionCard = makeCard(tr("Physics / Collision"));
    const PropertyCard collectCard = makeCard(tr("Collectable"));
    const PropertyCard linkedCard = makeCard(tr("Linked Object"));
    const PropertyCard triggerCard = makeCard(tr("Switch, Trigger & Save Checkpoint"));
    const PropertyCard liftCard = makeCard(tr("Moving Platform"));
    const PropertyCard conveyorCard = makeCard(tr("Conveyor"));
    const PropertyCard springCard = makeCard(tr("Spring / Bouncer"));
    const PropertyCard breakCard = makeCard(tr("Breakable"));
    const PropertyCard hazardCard = makeCard(tr("Damage / Knockback / Hurt Effects"));
    const PropertyCard enemyCard = makeCard(tr("Stompable Enemy"));
    const PropertyCard particleCard = makeCard(tr("Scenery Particle Spawner"));
    const PropertyCard gotoCard = makeCard(tr("Goto World"));
    const PropertyCard audioCollectCard = makeCard(tr("Audio Events / Collectable"));
    const PropertyCard audioLiftCard = makeCard(tr("Audio Events / Moving Platform"));
    const PropertyCard audioSpringCard = makeCard(tr("Audio Events / Spring"));
    const PropertyCard audioConveyorCard = makeCard(tr("Audio Events / Conveyor"));
    const PropertyCard audioBreakCard = makeCard(tr("Audio Events / Breakable & Enemy"));
    const PropertyCard audioHazardCard = makeCard(tr("Audio Events / Hazard"));
    const PropertyCard audioOptionsCard = makeCard(tr("Audio / Range & Fade"), false);

    // Accurate number entry alongside a quick, keyboard-accessible slider.
    const auto quickValue = [&dialog](QSpinBox *box) -> QWidget * {
        auto *row = new QWidget(&dialog);
        auto *line = new QHBoxLayout(row);
        line->setContentsMargins(0, 0, 0, 0);
        line->setSpacing(7);
        auto *slider = new QSlider(Qt::Horizontal, row);
        slider->setRange(box->minimum(), box->maximum());
        slider->setValue(box->value());
        slider->setMinimumWidth(60);
        box->setMinimumWidth(78);
        box->setMaximumWidth(116);
        line->addWidget(slider, 1);
        line->addWidget(box);
        QObject::connect(slider, &QSlider::valueChanged, box, &QSpinBox::setValue);
        QObject::connect(box, qOverload<int>(&QSpinBox::valueChanged),
                         slider, &QSlider::setValue);
        return row;
    };
    // Labels sit over each of two adjacent controls. This saves height and
    // keeps the field names visible when users change object types.
    const auto pairFields = [&dialog](const QString &leftLabel, QWidget *left,
                                      const QString &rightLabel, QWidget *right) -> QWidget * {
        auto *row = new QWidget(&dialog);
        auto *horizontal = new QHBoxLayout(row);
        horizontal->setContentsMargins(0, 0, 0, 0);
        horizontal->setSpacing(10);
        auto addColumn = [row, horizontal](const QString &label, QWidget *field) {
            auto *column = new QWidget(row);
            auto *vertical = new QVBoxLayout(column);
            vertical->setContentsMargins(0, 0, 0, 0);
            vertical->setSpacing(4);
            auto *caption = new QLabel(label, column);
            vertical->addWidget(caption);
            vertical->addWidget(field);
            horizontal->addWidget(column, 1);
        };
        addColumn(leftLabel, left);
        addColumn(rightLabel, right);
        return row;
    };
    QFormLayout *form = collectCard.form;
    auto *type = new GameComboBox(&dialog);
    type->addItem(tr("Ordinary sprite / Decoration"), QStringLiteral("decoration"));
    type->addItem(tr("Collectable"), QStringLiteral("collectable"));
    type->addItem(tr("Moving platform / Lift"), QStringLiteral("lift"));
    type->addItem(tr("Conveyor"), QStringLiteral("conveyor"));
    type->addItem(tr("Spring / Bouncer"), QStringLiteral("spring"));
    type->addItem(tr("Trigger / Switch"), QStringLiteral("trigger"));
    type->addItem(tr("Door / Solid blocker"), QStringLiteral("door"));
    type->addItem(tr("Hazard Zone (touch = callback)"), QStringLiteral("deathzone"));
    type->addItem(tr("Breakable Object"), QStringLiteral("breakable"));
    type->addItem(tr("Hazard / Murder Object (touch hurts)"), QStringLiteral("hazard"));
    type->addItem(tr("Stompable Enemy (jump on to defeat)"), QStringLiteral("enemy"));
    type->addItem(tr("Goto World"), QStringLiteral("goto_world"));
    type->addItem(tr("Save Game Checkpoint"), QStringLiteral("save_checkpoint"));
    type->addItem(tr("Scenery Particle Spawner (leaves / clouds / dust)"), QStringLiteral("particle_emitter"));
    type->setCurrentIndex(qMax(0, type->findData(old.objectType)));
    // The left-hand list is the behaviour selector; keep the combo as the
    // original model for existing validation and signal connections.
    type->hide();
    auto *resourceName = new QLabel(old.name, &dialog);
    generalCard.form->addRow(tr("Name"), resourceName);
    // UUID remains in the Resource and project file, but developers don't
    // need a distracting implementation identifier in the Properties UI.
    auto *pickup = new GameComboBox(&dialog);
    // Small vector symbols stay sharp at high DPI and do not depend on sprite assets.
    const auto pickupIcon = [](int kind) {
        QPixmap pix(18, 18);
        pix.fill(Qt::transparent);
        QPainter painter(&pix);
        painter.setRenderHint(QPainter::Antialiasing, true);
        if (kind == 1) {
            painter.setPen(QPen(QColor(255, 230, 140), 1));
            painter.setBrush(QColor(228, 164, 37));
            painter.drawEllipse(3, 2, 12, 13);
            painter.drawLine(8, 5, 8, 12);
        } else if (kind == 2) {
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(234, 65, 89));
            QPainterPath heart;
            heart.moveTo(9, 15);
            heart.cubicTo(1, 10, 0, 5, 5, 4);
            heart.cubicTo(7, 3, 9, 6, 9, 6);
            heart.cubicTo(14, 0, 20, 5, 15, 11);
            heart.closeSubpath();
            painter.drawPath(heart);
        } else if (kind == 3) {
            painter.setPen(QPen(QColor(231, 206, 113), 2));
            painter.drawEllipse(2, 3, 7, 7);
            painter.drawLine(8, 9, 15, 15);
            painter.drawLine(12, 12, 15, 10);
        } else {
            painter.setPen(QPen(QColor(212, 171, 255), 1));
            painter.setBrush(QColor(127, 86, 217));
            QPolygon gem;
            gem << QPoint(9, 2) << QPoint(16, 8) << QPoint(9, 16) << QPoint(2, 8);
            painter.drawPolygon(gem);
        }
        return QIcon(pix);
    };
    pickup->addItem(pickupIcon(1), tr("Coin"), 1);
    pickup->addItem(pickupIcon(2), tr("Health"), 2);
    pickup->addItem(pickupIcon(3), tr("Key"), 3);
    pickup->addItem(pickupIcon(4), tr("Gem"), 4);
    // Project-wide named kinds, stored in Adventure .sbgm data; their numeric
    // IDs are stable even if a name is edited (and the SDK supports uint16_t).
    QJsonArray customPickupTypes=m_adventure.value(QStringLiteral("pickupTypes")).toArray();
    const auto refillPickup = [&] (int selected) {
        while(pickup->count()>4) pickup->removeItem(pickup->count()-1);
        for(const QJsonValue &v:customPickupTypes){
            const QJsonObject def=v.toObject();const int k=def.value(QStringLiteral("id")).toInt();
            if(k>=5 && k<=255)pickup->addItem(tr("%1: %2").arg(k)
                .arg(def.value(QStringLiteral("name")).toString()),k);
        }
        pickup->setCurrentIndex(qMax(0,pickup->findData(selected)));
    };
    refillPickup(old.pickupKind);
    auto *addPickupType=new QPushButton(tr("+ New type..."),&dialog);
    auto *managePickupTypes=new QPushButton(tr("Rename / Remove..."),&dialog);
    addPickupType->setToolTip(tr("Create a named project-wide pickup type (5–255). "
        "Link it to an Inventory Item in Adventure Editor → Inventory Items."));
    managePickupTypes->setToolTip(tr("Rename a custom type, or remove one only when no Game Object or Inventory Item uses it."));
    connect(addPickupType,&QPushButton::clicked,&dialog,[&]{
        int id=5;
        for(;id<=255;++id){
            bool exists=false;
            for(const QJsonValue &v:customPickupTypes)
                if(v.toObject().value(QStringLiteral("id")).toInt()==id){exists=true;break;}
            if(!exists)break;
        }
        if(id>255){QMessageBox::warning(&dialog,tr("Pickup types"),tr("All 251 custom pickup IDs are in use."));return;}
        bool ok=false;
        const QString name=QInputDialog::getText(&dialog,tr("Add pickup type"),
            tr("Name for pickup type %1:").arg(id),QLineEdit::Normal,
            tr("Puzzle item %1").arg(id),&ok).trimmed().left(36);
        if(!ok || name.isEmpty())return;
        QJsonObject def;def.insert(QStringLiteral("id"),id);def.insert(QStringLiteral("name"),name);
        customPickupTypes.append(def);refillPickup(id);
    });
    connect(managePickupTypes,&QPushButton::clicked,&dialog,[&]{
        if(customPickupTypes.isEmpty()){
            QMessageBox::information(&dialog,tr("Pickup types"),tr("No custom types yet. Use + New type to create one."));return;
        }
        QStringList labels;
        for(const QJsonValue &v:customPickupTypes){const auto d=v.toObject();
            labels<<tr("%1: %2").arg(d.value(QStringLiteral("id")).toInt())
                .arg(d.value(QStringLiteral("name")).toString());}
        bool ok=false;
        const QString chosen=QInputDialog::getItem(&dialog,tr("Manage pickup types"),
            tr("Select a named type:"),labels,0,false,&ok);
        if(!ok || chosen.isEmpty())return;
        const int row=labels.indexOf(chosen);
        if(row<0)return;
        QJsonObject def=customPickupTypes[row].toObject();
        const int id=def.value(QStringLiteral("id")).toInt();
        const auto action=QMessageBox::question(&dialog,tr("Edit pickup type"),
            tr("Rename %1? Choose Yes to rename, No to try removing it, or Cancel.").arg(chosen),
            QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel,QMessageBox::Yes);
        if(action==QMessageBox::Cancel)return;
        if(action==QMessageBox::Yes){
            bool renamed=false;
            const QString name=QInputDialog::getText(&dialog,tr("Rename pickup type"),
                tr("Name for ID %1:").arg(id),QLineEdit::Normal,
                def.value(QStringLiteral("name")).toString(),&renamed).trimmed().left(36);
            if(!renamed||name.isEmpty())return;
            def.insert(QStringLiteral("name"),name);customPickupTypes[row]=def;
            refillPickup(pickup->currentData().toInt());return;
        }
        // Deletion must never make a placed collectable or inventory entry silently
        // change its meaning. Include the currently edited, not yet saved row.
        bool referenced=(pickup->currentData().toInt()==id);
        for(const Resource &r:m_resources)
            if(r.objectType==QStringLiteral("collectable") && r.pickupKind==id)referenced=true;
        for(const QJsonValue &v:m_adventure.value(QStringLiteral("items")).toArray())
            if(v.toObject().value(QStringLiteral("pickupKind")).toInt()==id)referenced=true;
        if(referenced){QMessageBox::warning(&dialog,tr("Pickup type is in use"),
            tr("Type %1 is assigned to a placed collectable or an Adventure Inventory Item. "
               "Reassign those objects/items and save first; then remove the type.").arg(id));return;}
        if(QMessageBox::question(&dialog,tr("Remove pickup type"),
            tr("Remove type %1 (%2)?").arg(id).arg(def.value(QStringLiteral("name")).toString()),
            QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)return;
        customPickupTypes.removeAt(row);refillPickup(pickup->currentData().toInt());
    });
    auto spin = [&dialog](int lo, int hi, int val) {
        auto *s = new QSpinBox(&dialog);
        s->setRange(lo, hi); s->setValue(val); return s;
    };
    auto *value = spin(0, 65535, old.objectValue);
    value->setMaximumWidth(110);
    pickup->setMinimumWidth(120);
    value->setToolTip(tr("How many units this pickup grants (e.g. 10 coins). Your existing on_pickup callback can still use the value."));
    form->addRow(pairFields(tr("Pickup Type"), pickup, tr("Pickup Value"), value));
    auto *pickupShowInventory = new QCheckBox(tr("Show in Inventory"), &dialog);
    auto *pickupShowHud = new QCheckBox(tr("Show in HUD (track total)"), &dialog);
    auto *pickupPersistent = new QCheckBox(tr("Persistent collectible (stay collected across worlds)"), &dialog);
    pickupPersistent->setChecked(old.pickupPersistent);
    pickupPersistent->setToolTip(tr("Once collected, this PLACED OBJECT stays gone when you return to its world. This setting is independent of inventory persistence: Show in Inventory items travel between worlds whether checked or not."));
    pickupShowInventory->setChecked(old.pickupShowInventory);
    pickupShowHud->setChecked(old.pickupShowHud);
    // Opening/saving an existing object must not silently replace its custom
    // on_pickup() rules. Only opting into these controls enables auto-tracking.
    bool pickupOptionsTouched = false;
    connect(pickupShowInventory, &QCheckBox::toggled, &dialog,
            [&](bool) { pickupOptionsTouched = true; });
    connect(pickupShowHud, &QCheckBox::toggled, &dialog,
            [&](bool) { pickupOptionsTouched = true; });
    pickupShowInventory->setToolTip(tr("Store this pickup in the shared backpack instead of applying a direct player-stat effect. CoderGirl creates the Adventure Inventory definition and offers to add it to Create / Edit Player → Inventory."));
    pickupShowHud->setToolTip(tr("Count collected objects of this type for the shared HUD. One pickup = one count; Pickup Value is still available for your own game rules."));
    collectCard.form->addRow(QString(), pickupShowInventory);
    collectCard.form->addRow(QString(), pickupShowHud);
    collectCard.form->addRow(QString(), pickupPersistent);
    auto *pickupStat = new GameComboBox(&dialog);
    pickupStat->addItem(tr("None (callback only)"), QStringLiteral("none"));
    pickupStat->addItem(tr("Player Health"), QStringLiteral("health"));
    pickupStat->addItem(tr("Player Lives"), QStringLiteral("lives"));
    pickupStat->addItem(tr("Player Score"), QStringLiteral("score"));
    const QDir statRoot(QFileInfo(m_filePath).absolutePath());
    QJsonObject statProfile;
    if (GamePlayerProfile::read(statRoot, &statProfile)) {
        for (const QJsonValue &entry : statProfile.value(QStringLiteral("customStats")).toArray()) {
            const QString statName = entry.toObject().value(QStringLiteral("name")).toString();
            if (!statName.isEmpty())
                pickupStat->addItem(tr("Custom stat: %1").arg(statName), QStringLiteral("stat:") + statName);
        }
    }
    const QString initialPickupStat = old.pickupStatTarget.isEmpty()
        ? (old.pickupKind == 2 ? QStringLiteral("health") : QStringLiteral("none"))
        : old.pickupStatTarget;
    if (pickupStat->findData(initialPickupStat) < 0)
        pickupStat->addItem(initialPickupStat, initialPickupStat);
    pickupStat->setCurrentIndex(qMax(0, pickupStat->findData(initialPickupStat)));
    pickupStat->setToolTip(tr("When Show in Inventory is OFF, add Pickup Value directly to this player stat. "
        "Health pickups default to Player Health. When Show in Inventory is ON, the pickup goes "
        "to the backpack instead; this direct effect is disabled."));
    collectCard.form->addRow(tr("Apply pickup value to"), pickupStat);
    const auto updatePickupStat = [pickupStat, pickupShowInventory]() {
        pickupStat->setEnabled(!pickupShowInventory->isChecked());
    };
    connect(pickupShowInventory, &QCheckBox::toggled, &dialog, updatePickupStat);
    updatePickupStat();
    bool pickupStatTouched = false;
    connect(pickupStat, qOverload<int>(&QComboBox::activated), &dialog,
            [&](int) { pickupStatTouched = true; pickupOptionsTouched = true; });
    connect(pickup, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [&](int) {
                if (pickupStatTouched || !old.pickupStatTarget.isEmpty()) return;
                pickupStat->setCurrentIndex(qMax(0, pickupStat->findData(
                    pickup->currentData().toInt() == 2 ? QStringLiteral("health") : QStringLiteral("none"))));
            });
    auto *pickupActions=new QWidget(&dialog);auto *pickupActionsRow=new QHBoxLayout(pickupActions);
    pickupActionsRow->setContentsMargins(0,0,0,0);
    pickupActionsRow->addWidget(addPickupType);pickupActionsRow->addWidget(managePickupTypes);
    form->addRow(tr("Custom pickup types"),pickupActions);
    form = generalCard.form;
    auto *initiallyActive = new QCheckBox(tr("Active when the level starts"), &dialog);
    initiallyActive->setChecked(old.objectInitiallyActive);
    form->addRow(QString(), initiallyActive);
    // Collectables can explicitly start hidden. This reuses the established
    // initial-active flag, so no second conflicting visibility state is stored.
    auto *hiddenCollectable = new QCheckBox(tr("Hidden until activated / spawned"), &dialog);
    hiddenCollectable->setChecked(!old.objectInitiallyActive ||
        (old.objectType == QStringLiteral("collectable") &&
         std::any_of(m_resources.cbegin(), m_resources.cend(), [&](const Resource &candidate) {
             return (candidate.objectType == QStringLiteral("breakable") ||
                     candidate.objectType == QStringLiteral("enemy")) &&
                    candidate.breakDropCollectableId == old.id;
         })));
    hiddenCollectable->setToolTip(tr("Hide this collectable when the level starts. "
                                  "It can later be activated by a linked trigger or "
                                  "spawned by a Breakable or Stompable Enemy. Reward items are hidden "
                                  "automatically even when this option is off."));
    collectCard.form->addRow(QString(), hiddenCollectable);
    connect(hiddenCollectable, &QCheckBox::toggled, initiallyActive,
            [initiallyActive](bool hidden) { initiallyActive->setChecked(!hidden); });
    connect(initiallyActive, &QCheckBox::toggled, hiddenCollectable,
            [hiddenCollectable](bool active) { hiddenCollectable->setChecked(!active); });
    auto *behindTiles = new QCheckBox(tr("Draw behind tiles"), &dialog);
    behindTiles->setChecked(old.drawBehindTiles);
    behindTiles->setToolTip(tr("Draw this object's sprite or scenery particles BEFORE the tilemap. "
                              "Unchecked draws them after the regular tile pass. "
                              "Tiles explicitly marked for front overdraw remain in front."));
    form->addRow(QString(), behindTiles);
    form = particleCard.form;
    auto *particleInfo = new QLabel(tr(
        "Uses this placed sprite as a particle image. Spawn area starts at the object's X/Y. "
        "Particles are decorative, have NO player collision, and follow 'Draw behind tiles' "
        "for background/foreground order. The source sprite itself is invisible in-game. "
        "Wind, fall and gravity are in 1/100 pixel units per 50-Hz frame."), &dialog);
    particleInfo->setWordWrap(true);
    form->addRow(particleInfo);
    auto *particlePreset = new GameComboBox(&dialog);
    particlePreset->addItem(tr("Falling leaves"), QStringLiteral("leaves"));
    particlePreset->addItem(tr("Drifting clouds"), QStringLiteral("clouds"));
    particlePreset->addItem(tr("Floating dust / motes"), QStringLiteral("dust"));
    particlePreset->addItem(tr("Swirling fireflies"), QStringLiteral("fireflies"));
    particlePreset->setCurrentIndex(qMax(0, particlePreset->findData(old.particlePreset)));
    auto *particleW = spin(8, 2048, old.particleAreaW);
    auto *particleH = spin(8, 2048, old.particleAreaH);
    auto *particleCount = spin(1, 32, old.particleCount);
    auto *particleInterval = spin(1, 255, old.particleInterval);
    auto *particlePrepopulate = new QCheckBox(tr("Pre-populate on world load"), &dialog);
    particlePrepopulate->setChecked(old.particlePrepopulate);
    particlePrepopulate->setToolTip(tr("Start this spawner with an already populated field of particles. Simulates enough history for natural ages and drift before the first frame. Leave unchecked for effects that should start empty, such as triggered explosions."));
    auto *particleLifetime = spin(30, 2000, old.particleLifetime);
    auto *particleWind = spin(-400, 400, old.particleWind);
    auto *particleFall = spin(-400, 400, old.particleFall);
    auto *particleGravity = spin(0, 80, old.particleGravity);
    auto *particleFlutter = spin(0, 100, old.particleFlutter);
    auto *particleSwirlRadius = spin(8, 96, old.particleSwirlRadius);
    auto *particleSwirlSpeed = spin(1, 12, old.particleSwirlSpeed);
    particleSwirlRadius->setToolTip(tr("Fireflies: orbit radius in pixels. Each firefly uses about half to all of this radius."));
    particleSwirlSpeed->setToolTip(tr("Fireflies: speed of circular motion. At 50 FPS, 1 is a 5.12-second orbit, 2 is 2.56 seconds, 4 is 1.28 seconds."));
    particleCount->setToolTip(tr("Maximum simultaneous particles for this spawner (1-32). Keep counts modest for smooth 50-Hz performance."));
    particleInterval->setToolTip(tr("50 FPS: one new particle every N frames, until the maximum count is reached."));
    particleLifetime->setToolTip(tr("Maximum lifespan for each particle at 50 Hz. A particle may leave the visible screen sooner, but it stays alive until its lifetime expires."));
    particleWind->setToolTip(tr("Horizontal drift in hundredths of one pixel per frame; negative moves left."));
    particleFall->setToolTip(tr("Initial vertical drift in hundredths of one pixel per frame; negative rises."));
    particleGravity->setToolTip(tr("Vertical acceleration in hundredths of a pixel per frame squared. Zero is good for clouds."));
    particleFlutter->setToolTip(tr("Subtle sideways gust / flutter added as each particle moves."));
    particlePreset->setToolTip(tr("Pick a useful starting physics preset. Changing this option loads its wind, drift, gravity and flutter defaults; you can then customise them."));
    connect(particlePreset, qOverload<int>(&QComboBox::activated), &dialog,
            [particlePreset, particleWind, particleFall, particleGravity,
             particleFlutter, particleLifetime, particleSwirlRadius, particleSwirlSpeed,
             particleCount, particleInterval](int) {
        const QString preset = particlePreset->currentData().toString();
        if (preset == QStringLiteral("fireflies")) {
            particleWind->setValue(2); particleFall->setValue(-1);
            particleGravity->setValue(0); particleFlutter->setValue(0);
            particleLifetime->setValue(500); particleCount->setValue(20);
            particleInterval->setValue(12); particleSwirlRadius->setValue(24);
            particleSwirlSpeed->setValue(2);
        } else if (preset == QStringLiteral("clouds")) {
            particleWind->setValue(45); particleFall->setValue(0);
            particleGravity->setValue(0); particleFlutter->setValue(4);
            particleLifetime->setValue(600);
        } else if (preset == QStringLiteral("dust")) {
            particleWind->setValue(12); particleFall->setValue(-12);
            particleGravity->setValue(0); particleFlutter->setValue(16);
            particleLifetime->setValue(400);
        } else {
            particleWind->setValue(65); particleFall->setValue(40);
            particleGravity->setValue(2); particleFlutter->setValue(22);
            particleLifetime->setValue(250);
        }
    });
    form->addRow(tr("Particle behaviour"), particlePreset);
    form->addRow(pairFields(tr("Spawn width (px)"), particleW, tr("Spawn height (px)"), particleH));
    form->addRow(pairFields(tr("Maximum particles"), particleCount, tr("Spawn every N frames"), particleInterval));
    form->addRow(particlePrepopulate);
    form->addRow(tr("Lifetime (frames)"), particleLifetime);
    form->addRow(pairFields(tr("Wind X (×0.01 px/frame)"), particleWind,
                             tr("Drift Y (×0.01 px/frame)"), particleFall));
    form->addRow(pairFields(tr("Gravity (×0.01 px/frame²)"), particleGravity,
                             tr("Flutter strength"), particleFlutter));
    QWidget *swirlFields = pairFields(tr("Swirl radius (px)"), particleSwirlRadius,
        tr("Swirl speed"), particleSwirlSpeed);
    form->addRow(swirlFields);
    // These are firefly-only controls, never shown for existing leaf/cloud modes.
    const auto refreshSwirlFields = [=]() {
        swirlFields->setVisible(particlePreset->currentData().toString() == QStringLiteral("fireflies"));
    };
    connect(particlePreset, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
        [refreshSwirlFields](int) { refreshSwirlFields(); });
    refreshSwirlFields();
    form = linkedCard.form;
    auto *targetObject = new GameComboBox(&dialog);
    targetObject->addItem(tr("None (no linked object)"), QString());
    for (const Resource &candidate : m_resources) {
        if (candidate.kind != QStringLiteral("sprite") ||
            candidate.objectType == QStringLiteral("decoration") ||
            candidate.id == old.id) continue;
        targetObject->addItem(tr("%1 [%2]").arg(candidate.name, candidate.objectType), candidate.id);
    }
    targetObject->setCurrentIndex(qMax(0, targetObject->findData(old.targetObjectId)));
    targetObject->setToolTip(tr("Choose a placed game-object instance. Its permanent ID is saved, "
                                    "so renaming and reordering don't break the link."));
    form->addRow(tr("Activate/deactivate object"), targetObject);
    auto *targetAction = new GameComboBox(&dialog);
    targetAction->addItem(tr("No action"), QStringLiteral("none"));
    targetAction->addItem(tr("Enable target"), QStringLiteral("enable"));
    targetAction->addItem(tr("Disable target"), QStringLiteral("disable"));
    targetAction->addItem(tr("Toggle target (ON / OFF)"), QStringLiteral("toggle"));
    targetAction->setCurrentIndex(qMax(0, targetAction->findData(old.targetAction)));
    form->addRow(tr("Linked action"), targetAction);
    auto *targetVisibilityHint = new QLabel(&dialog);
    targetVisibilityHint->setWordWrap(true);
    form->addRow(QString(),targetVisibilityHint);
    const auto refreshTargetVisibilityHint=[=]() {
        targetVisibilityHint->clear();
        if (targetAction->currentData().toString()!=QStringLiteral("disable")) return;
        const QString targetId=targetObject->currentData().toString();
        for (const Resource &candidate:m_resources) {
            if (candidate.id!=targetId) continue;
            targetVisibilityHint->setText(candidate.inactiveStateFrame>=0
                ? tr("Disabling '%1' removes collision and displays its INACTIVE frame %2.")
                    .arg(candidate.name).arg(candidate.inactiveStateFrame)
                : tr("Disabling '%1' will HIDE it: its INACTIVE frame is -1. "
                     "To keep an open/unlocked picture visible, set an INACTIVE frame "
                     "in that object's own Properties first.").arg(candidate.name));
            break;
        }
    };
    connect(targetObject,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
            [refreshTargetVisibilityHint](int){refreshTargetVisibilityHint();});
    connect(targetAction,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
            [refreshTargetVisibilityHint](int){refreshTargetVisibilityHint();});
    refreshTargetVisibilityHint();
    // A Trigger owns an ordered list; keys and enemies retain the familiar
    // single linked-object controls. Legacy targetObjectId/action = first row.
    auto *linkedActionRows = new QTableWidget(0, 3, &dialog);
    linkedActionRows->setHorizontalHeaderLabels({tr("Game Object / NPC"), tr("Action"), tr("This row")});
    linkedActionRows->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    linkedActionRows->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    linkedActionRows->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);
    linkedActionRows->horizontalHeader()->resizeSection(2,150);
    linkedActionRows->verticalHeader()->hide();
    linkedActionRows->setSelectionBehavior(QAbstractItemView::SelectRows);
    linkedActionRows->setSelectionMode(QAbstractItemView::SingleSelection);
    linkedActionRows->setEditTriggers(QAbstractItemView::NoEditTriggers);
    linkedActionRows->setMinimumHeight(126);
    auto *actionRowControls = new QWidget(&dialog);
    auto *actionRowButtons = new QHBoxLayout(actionRowControls);
    actionRowButtons->setContentsMargins(0,0,0,0);
    auto *addLinkedAction = new QPushButton(tr("+ Add Linked Action"), actionRowControls);
    actionRowButtons->addWidget(addLinkedAction);
    actionRowButtons->addStretch(1);
    form->addRow(tr("Ordered linked actions"), linkedActionRows);
    form->addRow(QString(), actionRowControls);
    auto *linkedActionsHint = new QLabel(tr("Each action runs once when this Trigger activates. "
        "Actions run top-to-bottom, then music/dialogue. Use the arrows beside each row "
        "to change its order, or Delete to remove that exact action (confirmation required). "
        "Disabling an object with no INACTIVE frame hides it."),&dialog);
    linkedActionsHint->setWordWrap(true);
    form->addRow(QString(),linkedActionsHint);
    auto currentLinks = [linkedActionRows]() {
        QVector<Resource::LinkedAction> links;
        for (int row=0; row<linkedActionRows->rowCount(); ++row) {
            auto *object=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row,0));
            auto *action=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row,1));
            if (object && action && !object->currentData().toString().isEmpty() &&
                action->currentData().toString()!=QStringLiteral("none"))
                links.append({object->currentData().toString(),action->currentData().toString()});
        }
        return links;
    };
    // Row action buttons stay attached to their row even after other rows are
    // removed. Never capture a fixed row index in their click handlers.
    const auto refreshLinkedRowButtons = [=]() {
        for (int i=0; i<linkedActionRows->rowCount(); ++i) {
            QWidget *controls=linkedActionRows->cellWidget(i,2);
            if (!controls) continue;
            if (auto *up=controls->findChild<QToolButton *>(QStringLiteral("linkedRowUp")))
                up->setEnabled(i>0);
            if (auto *down=controls->findChild<QToolButton *>(QStringLiteral("linkedRowDown")))
                down->setEnabled(i+1<linkedActionRows->rowCount());
        }
    };
    const auto deleteLink = [=](int row) {
        if (row<0 || row>=linkedActionRows->rowCount()) return;
        auto *object=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row,0));
        auto *action=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row,1));
        if (!object || !action) return;
        const QString target=object->currentData().toString().isEmpty()
            ? tr("(no target selected)") : object->currentText();
        const QString behaviour=action->currentText();
        if (QMessageBox::question(linkedActionRows, tr("Delete linked action?"),
                tr("Remove linked action #%1?\n\nTarget: %2\nAction: %3\n\n"
                   "This change is saved only when you save Object Properties.")
                    .arg(row+1).arg(target,behaviour),
                QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)
            return;
        linkedActionRows->removeRow(row);
        if (linkedActionRows->rowCount()>0)
            linkedActionRows->selectRow(qMin(row,linkedActionRows->rowCount()-1));
        refreshLinkedRowButtons();
    };
    const auto moveLink = [=](int row, int direction) {
        const int next=row+direction;
        if (row<0 || next<0 || next>=linkedActionRows->rowCount()) return;
        auto *object=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row,0));
        auto *action=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row,1));
        auto *otherObject=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(next,0));
        auto *otherAction=qobject_cast<QComboBox *>(linkedActionRows->cellWidget(next,1));
        if (!object || !action || !otherObject || !otherAction) return;
        const QString id=object->currentData().toString();
        const QString act=action->currentData().toString();
        const QString otherId=otherObject->currentData().toString();
        const QString otherAct=otherAction->currentData().toString();
        // Preserve MISSING targets during reordering so export can diagnose them.
        if (!otherId.isEmpty() && object->findData(otherId)<0)
            object->addItem(tr("MISSING: %1").arg(otherId),otherId);
        if (!id.isEmpty() && otherObject->findData(id)<0)
            otherObject->addItem(tr("MISSING: %1").arg(id),id);
        object->setCurrentIndex(object->findData(otherId));
        action->setCurrentIndex(action->findData(otherAct));
        otherObject->setCurrentIndex(otherObject->findData(id));
        otherAction->setCurrentIndex(otherAction->findData(act));
        linkedActionRows->selectRow(next);
    };
    auto insertLink = [=](int row, const Resource::LinkedAction &link) {
        linkedActionRows->insertRow(row);
        auto *object = new GameComboBox(linkedActionRows);
        object->addItem(tr("Select target..."), QString());
        object->addItem(tr("Player Spotlight (world lighting)"), QStringLiteral("@player_spotlight"));
        for (const Resource &candidate : m_resources) {
            if (candidate.kind!=QStringLiteral("sprite") ||
                candidate.objectType==QStringLiteral("decoration") ||
                candidate.objectType==QStringLiteral("collectable") || candidate.id==old.id) continue;
            object->addItem(tr("%1 [%2]").arg(candidate.name,candidate.objectType),candidate.id);
        }
        /* NPCs are Adventure entries, NOT Game Objects. The same sprite may
           host an entirely different dialogue when a different NPC is shown. */
        const QJsonArray localNpcs=m_adventure.value(QStringLiteral("npcs")).toArray();
        for (int n=0; n<localNpcs.size(); ++n) {
            const QString id=localNpcs[n].toObject().value(QStringLiteral("spriteId")).toString();
            if (id.isEmpty()) continue;
            QString name=id;
            for (const Resource &candidate:m_resources)
                if (candidate.id==id) {name=candidate.name;break;}
            object->addItem(tr("NPC: %1 [%2]").arg(name).arg(n),
                            QStringLiteral("@npc:%1:%2")
                                .arg(sidboxTilemapWorldBaseName(m_filePath),id));
        }
        /* Read saved sibling designs; no other world needs opening or loading.
           Runtime indices are resolved again during export from permanent IDs. */
        const QDir siblings(QFileInfo(m_filePath).absolutePath());
        const QString thisWorld=sidboxTilemapWorldBaseName(m_filePath);
        for (const QFileInfo &worldFile : siblings.entryInfoList(
                 QStringList{QStringLiteral("*.sbgm")},QDir::Files,QDir::Name)) {
            const QString world=sidboxTilemapWorldBaseName(worldFile.absoluteFilePath());
            if (world==thisWorld) continue;
            QFile input(worldFile.absoluteFilePath());
            if (!input.open(QIODevice::ReadOnly)) continue;
            const QJsonObject design=QJsonDocument::fromJson(input.readAll()).object();
            const QJsonArray remoteNpcs=design.value(QStringLiteral("adventure")).toObject()
                .value(QStringLiteral("npcs")).toArray();
            for (int n=0; n<remoteNpcs.size(); ++n) {
                const QString id=remoteNpcs[n].toObject().value(QStringLiteral("spriteId")).toString();
                if (id.isEmpty()) continue;
                QString name=id;
                for (const QJsonValue &v : design.value(QStringLiteral("resources")).toArray()) {
                    const QJsonObject sprite=v.toObject();
                    if (sprite.value(QStringLiteral("id")).toString()==id) {
                        name=sprite.value(QStringLiteral("name")).toString(id);break;
                    }
                }
                object->addItem(tr("%1: NPC %2 [%3]").arg(world,name).arg(n),
                                QStringLiteral("@npc:%1:%2").arg(world,id));
            }
            for (const QJsonValue &entry : design.value(QStringLiteral("resources")).toArray()) {
                const QJsonObject resource=entry.toObject();
                const QString type=resource.value(QStringLiteral("gameObject")).toObject()
                    .value(QStringLiteral("type")).toString(QStringLiteral("decoration"));
                if (resource.value(QStringLiteral("kind")).toString()!=QStringLiteral("sprite") ||
                    type==QStringLiteral("decoration") || type==QStringLiteral("collectable")) continue;
                const QString id=resource.value(QStringLiteral("id")).toString();
                if (id.isEmpty()) continue;
                object->addItem(tr("%1: %2 [%3]").arg(world,
                    resource.value(QStringLiteral("name")).toString(),type),
                    cgCrossWorldLink(world,id));
            }
        }
        if (!link.objectId.isEmpty() && object->findData(link.objectId)<0)
            object->addItem(tr("MISSING: %1").arg(link.objectId),link.objectId);
        object->setCurrentIndex(qMax(0,object->findData(link.objectId)));
        auto *action = new GameComboBox(linkedActionRows);
        action->addItem(tr("Enable"),QStringLiteral("enable"));
        action->addItem(tr("Disable"),QStringLiteral("disable"));
        action->addItem(tr("Toggle"),QStringLiteral("toggle"));
        action->setCurrentIndex(qMax(0,action->findData(link.action)));
        linkedActionRows->setCellWidget(row,0,object);
        linkedActionRows->setCellWidget(row,1,action);
        auto *rowControls=new QWidget(linkedActionRows);
        auto *buttons=new QHBoxLayout(rowControls);
        buttons->setContentsMargins(2,0,2,0);
        buttons->setSpacing(3);
        auto *rowUp=new QToolButton(rowControls);
        rowUp->setObjectName(QStringLiteral("linkedRowUp"));
        rowUp->setArrowType(Qt::UpArrow);
        rowUp->setFixedSize(26,26);
        rowUp->setToolTip(tr("Move THIS linked action up one position."));
        auto *rowDown=new QToolButton(rowControls);
        rowDown->setObjectName(QStringLiteral("linkedRowDown"));
        rowDown->setArrowType(Qt::DownArrow);
        rowDown->setFixedSize(26,26);
        rowDown->setToolTip(tr("Move THIS linked action down one position."));
        auto *rowDelete=new QPushButton(tr("Delete"),rowControls);
        rowDelete->setFixedWidth(74);
        rowDelete->setToolTip(tr("Delete THIS linked action after confirmation. "));
        buttons->addWidget(rowUp);
        buttons->addWidget(rowDown);
        buttons->addWidget(rowDelete);
        linkedActionRows->setCellWidget(row,2,rowControls);
        // Resolve the current position of this row's button container at click
        // time: deleting another row must never redirect a later click.
        connect(rowUp,&QToolButton::clicked,linkedActionRows,[=]() {
            for (int i=0;i<linkedActionRows->rowCount();++i)
                if (linkedActionRows->cellWidget(i,2)==rowControls) {
                    moveLink(i,-1);
                    break;
                }
        });
        connect(rowDown,&QToolButton::clicked,linkedActionRows,[=]() {
            for (int i=0;i<linkedActionRows->rowCount();++i)
                if (linkedActionRows->cellWidget(i,2)==rowControls) {
                    moveLink(i,1);
                    break;
                }
        });
        connect(rowDelete,&QPushButton::clicked,linkedActionRows,[=]() {
            for (int i=0;i<linkedActionRows->rowCount();++i)
                if (linkedActionRows->cellWidget(i,2)==rowControls) {
                    deleteLink(i);
                    break;
                }
        });
        linkedActionRows->setRowHeight(row,32);
        linkedActionRows->selectRow(row);
        refreshLinkedRowButtons();
    };
    auto reloadLinks = [=]() {
        linkedActionRows->setRowCount(0);
        if (!old.targetObjectId.isEmpty() && old.targetAction!=QStringLiteral("none"))
            insertLink(linkedActionRows->rowCount(),{old.targetObjectId,old.targetAction});
        for (const Resource::LinkedAction &link : old.triggerExtraActions)
            insertLink(linkedActionRows->rowCount(),link);
    };
    reloadLinks();
    connect(addLinkedAction,&QPushButton::clicked,&dialog,[=]() {
        if (linkedActionRows->rowCount()>=64) {
            QMessageBox::information(linkedActionRows,tr("Linked actions"),tr("Maximum 64 actions per Trigger."));
            return;
        }
        insertLink(linkedActionRows->rowCount(),{QString(),QStringLiteral("enable")});
    });
    form = generalCard.form; // State artwork belongs on the target (e.g. Door), not only on the Trigger.
    auto *activeStateFrame = spin(-1, 255, old.activeStateFrame);
    auto *inactiveStateFrame = spin(-1, 255, old.inactiveStateFrame);
    activeStateFrame->setToolTip(tr("Sprite atlas frame shown while the object is ACTIVE (solid). -1 uses its usual frame."));
    inactiveStateFrame->setToolTip(tr("Sprite atlas frame shown while the object is INACTIVE (no collision). -1 hides it. Use this for an opened door or chest."));
    form->addRow(tr("ACTIVE state frame (-1 = default)"), activeStateFrame);
    form->addRow(tr("INACTIVE state frame (-1 = hidden)"), inactiveStateFrame);
    form = triggerCard.form;
    auto *checkpointSlot = spin(1, 10, old.checkpointSlot + 1);
    checkpointSlot->setToolTip(tr("Save Game checkpoint: select which TFCard save slot (1 to 10) to overwrite."));
    form->addRow(tr("Checkpoint save slot"), checkpointSlot);
    auto *checkpointHelp = new QLabel(tr("Checkpoint activation: no required item means touch or FIRE2; "
        "choose an inventory item below to require USE instead. Wrong-item / success / cancel "
        "options then become available."), &dialog);
    checkpointHelp->setWordWrap(true);
    form->addRow(QString(), checkpointHelp);
    auto *triggerPress = new QCheckBox(tr("Require FIRE2 while touching (otherwise activate on touch)"), &dialog);
    triggerPress->setChecked(old.triggerPress);
    triggerPress->setToolTip(tr("Ordinary trigger: require FIRE2 while overlapping the switch; "
        "otherwise the trigger activates on touch."));
    form->addRow(QString(), triggerPress);
    auto *triggerDrop = new QCheckBox(tr("Activate when matching dropped item touches switch"), &dialog);
    triggerDrop->setChecked(old.triggerDrop);
    triggerDrop->setToolTip(tr("A DROPPED inventory item activates this Trigger as soon as its 16x16 icon overlaps the sensor, even during a fall into a well. "
        "Choose the required inventory item below to select which item activates it. "
        "On success, the normal linked actions, dialogue, sound, stat changes and reward run. "
        "'Consume used / dropped item on success' also consumes the physical dropped item; "
        "otherwise it stays on the ground for pickup. FIRE2/USE remains available independently. "
        "Wrong dropped items do nothing and remain recoverable."));
    form->addRow(QString(), triggerDrop);
    auto *triggerDropHint = new QLabel(&dialog);
    triggerDropHint->setWordWrap(true);
    form->addRow(QString(), triggerDropHint);
    auto *triggerOneShot = new QCheckBox(tr("Remove switch after activation (one-shot)"), &dialog);
    triggerOneShot->setChecked(old.triggerOneShot);
    form->addRow(QString(), triggerOneShot);
    auto *interactItem = new GameComboBox(&dialog);
    interactItem->addItem(tr("No required item (touch / FIRE2 activation)"), QString());
    for (const QJsonValue &entry : m_adventure.value(QStringLiteral("items")).toArray()) {
        const QString name = entry.toObject().value(QStringLiteral("name")).toString().trimmed();
        if (!name.isEmpty() && interactItem->findData(name) < 0)
            interactItem->addItem(name, name);
    }
    if (!old.interactItemName.isEmpty() && interactItem->findData(old.interactItemName) < 0)
        interactItem->addItem(tr("Missing inventory item: %1").arg(old.interactItemName), old.interactItemName);
    interactItem->setCurrentIndex(qMax(0, interactItem->findData(old.interactItemName)));
    interactItem->setToolTip(tr("Require the player to USE this inventory item while near the trigger. "
        "Item identity follows the Adventure Inventory name across worlds. "
        "This also works for Save Game Checkpoints: the matching item saves the chosen slot, "
        "and touch alone will no longer activate it."));
    form->addRow(tr("Interact with inventory item"), interactItem);
    auto *interactRadius = spin(0, 128, old.interactRadius);
    interactRadius->setToolTip(tr("Extra distance in pixels outside this object's hitbox. "
        "Set 0 for touching only; a solid door can be operated from just outside its edges."));
    form->addRow(tr("Interaction reach (px)"), interactRadius);
    auto *interactConsume = new QCheckBox(tr("Consume used / dropped item on success"), &dialog);
    interactConsume->setChecked(old.interactConsume);
    form->addRow(QString(), interactConsume);
    // Stage 5.95: use the same searchable folder tree as the Adventure
    // Editor. Keep the numeric node IDs exactly as before for export/saves.
    // These arrays live through dialog.exec(), as required by the picker.
    const QJsonArray interactionNodes=m_adventure.value(QStringLiteral("nodes")).toArray();
    const QJsonArray interactionFolders=m_adventure.value(QStringLiteral("dialogueFolders")).toArray();
    auto *interactDialogue = createGameDialogueTreeCombo(
        &dialog, &interactionNodes, &interactionFolders);
    interactDialogue->addItem(tr("None (no dialogue)"), -1);
    for (int i=0;i<interactionNodes.size();++i) {
        const QJsonObject node=interactionNodes.at(i).toObject();
        const QString speaker=node.value(QStringLiteral("speaker")).toString().left(24);
        const QString text=node.value(QStringLiteral("text")).toString().left(35);
        interactDialogue->addItem(tr("%1: %2 — %3").arg(i).arg(speaker,text),i);
    }
    if (old.interactDialogueNode>=0 && interactDialogue->findData(old.interactDialogueNode)<0)
        interactDialogue->addItem(tr("Missing dialogue node %1").arg(old.interactDialogueNode),old.interactDialogueNode);
    interactDialogue->setCurrentIndex(qMax(0,interactDialogue->findData(old.interactDialogueNode)));
    interactDialogue->setToolTip(tr("Choose an existing Adventure dialogue using its searchable folder tree. "
        "The selected dialogue runs after a successful USE, including its choices and quest actions."));
    form->addRow(tr("On success: dialogue"),interactDialogue);
    auto *interactDialogueMode = new GameComboBox(&dialog);
    interactDialogueMode->addItem(tr("Single message (one node, no actions)"),
                                  QStringLiteral("single"));
    interactDialogueMode->addItem(tr("Message sequence (continue prompts, no actions)"),
                                  QStringLiteral("sequence"));
    interactDialogueMode->addItem(tr("Full conversation (choices and dialogue actions)"),
                                  QStringLiteral("conversation"));
    interactDialogueMode->setCurrentIndex(qMax(0,interactDialogueMode->findData(old.interactDialogueMode)));
    interactDialogueMode->setToolTip(tr("Single message shows one node only. Message sequence uses the "
        "saved choice labels (e.g. Continue... / Thank god!) as navigation buttons and follows "
        "their Next node destinations, but NEVER runs gifts, requirements or dialogue actions. "
        "Full conversation executes configured choices and actions. Trigger success always "
        "commits before the dialogue opens."));
    form->addRow(tr("Dialogue behaviour"),interactDialogueMode);
    auto *interactDialogueHint = new QLabel(&dialog);
    interactDialogueHint->setWordWrap(true);
    form->addRow(QString(),interactDialogueHint);
    const auto refreshDialogueHint = [=]() {
        interactDialogueMode->setEnabled((type->currentData().toString()==QStringLiteral("trigger") ||
             type->currentData().toString()==QStringLiteral("save_checkpoint")) &&
            !interactItem->currentData().toString().isEmpty() &&
            interactDialogue->currentData().toInt()>=0);
        const int id=interactDialogue->currentData().toInt();
        if(id<0 || id>=interactionNodes.size()) {
            interactDialogueHint->setText(tr("No dialogue on success."));return;
        }
        const QJsonObject node=interactionNodes.at(id).toObject();
        int choices=0;
        for(const QJsonValue &v:node.value(QStringLiteral("choices")).toArray())
            if(!v.toObject().value(QStringLiteral("text")).toString().trimmed().isEmpty()) ++choices;
        const QString mode=interactDialogueMode->currentData().toString();
        if(mode==QStringLiteral("single")) {
            interactDialogueHint->setText(tr("Shows just this node's text; its %1 choice(s) and all actions are ignored.").arg(choices));
        } else if(mode==QStringLiteral("sequence")) {
            interactDialogueHint->setText(tr("Shows this node and follows the Next destinations of its %1 choice(s) "
                "using their labels as prompts. No inventory, NPC, quest or dialogue actions run. "
                "A choice with Next = None closes the message sequence.").arg(choices));
        } else {
            interactDialogueHint->setText(choices
                ? tr("This node starts a %1-choice conversation. Trigger actions run BEFORE "
                     "the player answers. To make answers control the outcome, use an Adventure NPC.").arg(choices)
                : tr("Full dialogue: continues into any configured next nodes or dialogue effects."));
        }
    };
    connect(interactDialogue,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
            [refreshDialogueHint](int){refreshDialogueHint();});
    connect(interactDialogueMode,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
            [refreshDialogueHint](int){refreshDialogueHint();});
    refreshDialogueHint();
    // Wrong item: same searchable tree picker and modes, but independent
    // from the success message. Nothing is consumed or activated by a mismatch.
    auto *interactWrongDialogue = createGameDialogueTreeCombo(
        &dialog, &interactionNodes, &interactionFolders);
    interactWrongDialogue->addItem(tr("None (keep USE selector open)"), -1);
    for (int i=0;i<interactionNodes.size();++i) {
        const QJsonObject node=interactionNodes.at(i).toObject();
        interactWrongDialogue->addItem(tr("%1: %2 — %3").arg(i)
            .arg(node.value(QStringLiteral("speaker")).toString().left(24),
                 node.value(QStringLiteral("text")).toString().left(35)), i);
    }
    if (old.interactWrongDialogueNode>=0 &&
        interactWrongDialogue->findData(old.interactWrongDialogueNode)<0)
        interactWrongDialogue->addItem(tr("Missing dialogue node %1")
            .arg(old.interactWrongDialogueNode), old.interactWrongDialogueNode);
    interactWrongDialogue->setCurrentIndex(qMax(0,interactWrongDialogue->findData(old.interactWrongDialogueNode)));
    interactWrongDialogue->setToolTip(tr("Dialogue to show if a different inventory item is used. "
        "If None, show the normal 'That item does not work' hint in the USE selector."));
    form->addRow(tr("On wrong item: dialogue"),interactWrongDialogue);
    auto *interactWrongDialogueMode = new GameComboBox(&dialog);
    interactWrongDialogueMode->addItem(tr("Single message (one node, no actions)"),QStringLiteral("single"));
    interactWrongDialogueMode->addItem(tr("Message sequence (continue prompts, no actions)"),QStringLiteral("sequence"));
    interactWrongDialogueMode->addItem(tr("Full conversation (choices and dialogue actions)"),QStringLiteral("conversation"));
    interactWrongDialogueMode->setCurrentIndex(qMax(0,interactWrongDialogueMode->findData(old.interactWrongDialogueMode)));
    interactWrongDialogueMode->setToolTip(tr("Single and sequence modes have no dialogue side effects. "
        "Full conversation deliberately runs any saved dialogue-choice actions; "
        "it never activates the Trigger or consumes the attempted item automatically."));
    form->addRow(tr("Wrong item: dialogue behaviour"),interactWrongDialogueMode);
    auto *wrongDialogueHint = new QLabel(&dialog);
    wrongDialogueHint->setWordWrap(true);
    form->addRow(QString(),wrongDialogueHint);
    const auto refreshWrongDialogueHint=[=]() {
        const int id=interactWrongDialogue->currentData().toInt();
        if(id<0 || id>=interactionNodes.size()) {
            wrongDialogueHint->setText(tr("No wrong-item dialogue: sound and standard USE hint only."));
            return;
        }
        const QJsonObject node=interactionNodes.at(id).toObject();
        int choices=0;
        for(const QJsonValue &v:node.value(QStringLiteral("choices")).toArray())
            if(!v.toObject().value(QStringLiteral("text")).toString().trimmed().isEmpty()) ++choices;
        const QString mode=interactWrongDialogueMode->currentData().toString();
        wrongDialogueHint->setText(mode==QStringLiteral("single")
            ? tr("Wrong item: show one message; ignore %1 choice(s) and all actions.").arg(choices)
            : mode==QStringLiteral("sequence")
                ? tr("Wrong item: follow navigation prompts and Next nodes without executing any actions.")
                : tr("Wrong item: run full dialogue choices and their explicit actions. "
                     "The Trigger itself remains locked and the attempted item is not automatically consumed."));
    };
    connect(interactWrongDialogue,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
            [refreshWrongDialogueHint](int){refreshWrongDialogueHint();});
    connect(interactWrongDialogueMode,qOverload<int>(&QComboBox::currentIndexChanged),&dialog,
            [refreshWrongDialogueHint](int){refreshWrongDialogueHint();});
    refreshWrongDialogueHint();
    auto *interactReward = new GameComboBox(&dialog);
    interactReward->addItem(tr("None (no reward)"),QString());
    for (const QJsonValue &entry : m_adventure.value(QStringLiteral("items")).toArray()) {
        const QString name=entry.toObject().value(QStringLiteral("name")).toString().trimmed();
        if (!name.isEmpty() && interactReward->findData(name)<0) interactReward->addItem(name,name);
    }
    if (!old.interactRewardItem.isEmpty() && interactReward->findData(old.interactRewardItem)<0)
        interactReward->addItem(tr("Missing inventory item: %1").arg(old.interactRewardItem),old.interactRewardItem);
    interactReward->setCurrentIndex(qMax(0,interactReward->findData(old.interactRewardItem)));
    interactReward->setToolTip(tr("Reward is only granted after a successful USE. A full inventory prevents the interaction from activating or consuming the required item."));
    form->addRow(tr("On success: give item"),interactReward);
    auto *interactRewardCount=spin(1,64,old.interactRewardCount);
    form->addRow(tr("Reward quantity"),interactRewardCount);
    auto *interactStat=new GameComboBox(&dialog);
    interactStat->addItem(tr("None"),QStringLiteral("none"));
    for (const QString &stat : {QStringLiteral("health"),QStringLiteral("lives"),QStringLiteral("score")})
        interactStat->addItem(stat,stat);
    QJsonObject interactionProfile;
    if (GamePlayerProfile::read(QDir(QFileInfo(m_filePath).absolutePath()),&interactionProfile)) {
        for (const QJsonValue &entry:interactionProfile.value(QStringLiteral("customStats")).toArray()) {
            const QString name=entry.toObject().value(QStringLiteral("name")).toString();
            if (!name.isEmpty() && interactStat->findData(name)<0) interactStat->addItem(name,name);
        }
    }
    if (interactStat->findData(old.interactStatTarget)<0)
        interactStat->addItem(old.interactStatTarget,old.interactStatTarget);
    interactStat->setCurrentIndex(qMax(0,interactStat->findData(old.interactStatTarget)));
    form->addRow(tr("On success: player stat"),interactStat);
    auto *interactStatDelta=spin(-65535,65535,old.interactStatDelta);
    form->addRow(tr("Stat change (+ / -)"),interactStatDelta);
    const auto updateItemInteraction = [=]() {
        const QString interactionType = type->currentData().toString();
        const bool isTrigger = interactionType == QStringLiteral("trigger") ||
                               interactionType == QStringLiteral("save_checkpoint");
        const bool requiresItem = !interactItem->currentData().toString().isEmpty();
        const bool itemInteraction = isTrigger && requiresItem;
        interactRadius->setEnabled(itemInteraction);
        interactConsume->setEnabled(itemInteraction);
        const QString itemHint = tr("Disabled: choose a required inventory item on a Trigger/Switch or Save Checkpoint first.");
        interactRadius->setToolTip(itemInteraction ? tr("Interaction radius in pixels for using this item.") : itemHint);
        interactConsume->setToolTip(itemInteraction ? tr("Consume the matching item after successful activation.") : itemHint);
        // Item-required triggers already use FIRE2 to select an inventory item.
        // Keep the user's ordinary-trigger preference checked/unchecked so it
        // returns intact when "No required item" is selected again.
        triggerPress->setEnabled(isTrigger && !requiresItem);
        triggerPress->setToolTip(itemInteraction
            ? tr("Not used for inventory-item interactions: FIRE2 already opens "
                 "the item selector when the player is nearby. "
                 "Choose 'No required item' to enable this option again.")
            : tr("Require FIRE2 while touching; otherwise activate on touch. "
                 "A required inventory item overrides both options."));
        triggerDrop->setEnabled(itemInteraction);
        triggerDrop->setToolTip(itemInteraction
            ? tr("Activate when a matching dropped inventory item touches this Trigger.")
            : tr("Disabled: select the required inventory item first."));
        triggerDrop->setToolTip(itemInteraction
            ? tr("Match the selected required inventory item against falling/dropped items. "
                 "Contact with the sensor runs normal success actions and dialogue. "
                 "The consume checkbox determines whether the dropped item vanishes. "
                 "The dropped item is not required to remain in the player's bag.")
            : tr("Choose a required inventory item below first. Only Trigger / Switch and "
                 "Save Checkpoint objects with an item requirement can accept dropped objects."));
        triggerDropHint->setText(!isTrigger
            ? tr("Dropped-item activation is available for Trigger / Switch and Save Checkpoint objects only.")
            : !requiresItem
                ? tr("To use falling items: choose a Required inventory item, then tick Activate when matching dropped item touches switch.")
                : triggerDrop->isChecked()
                    ? interactionType==QStringLiteral("save_checkpoint")
                        ? tr("DROP ACTIVE: a matching dropped item requests a checkpoint save. "
                             "Configured success dialogue, rewards and sound also run. Wrong dropped items do nothing.")
                        : tr("DROP ACTIVE: a matching 16x16 item touching this sensor (even mid-fall) runs the normal success dialogue, reward, sound and linked actions. "
                             "Consume on success removes the physical item; otherwise it can still be collected. Wrong items do nothing.")
                    : tr("Dropped items will not activate this object until you tick the option above. Normal inventory USE still works."));
    };
    connect(interactItem, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [updateItemInteraction](int) { updateItemInteraction(); });
    connect(triggerDrop, &QCheckBox::toggled, &dialog,
            [updateItemInteraction](bool) { updateItemInteraction(); });
    // Only dependency-controlled controls get the soft red/green outline.
    for (QWidget *w : {static_cast<QWidget *>(triggerPress),static_cast<QWidget *>(triggerDrop),
             static_cast<QWidget *>(triggerOneShot),static_cast<QWidget *>(interactItem),
             static_cast<QWidget *>(interactConsume),static_cast<QWidget *>(interactRadius),
             static_cast<QWidget *>(interactDialogue),static_cast<QWidget *>(interactDialogueMode),
             static_cast<QWidget *>(interactReward),static_cast<QWidget *>(interactRewardCount),
             static_cast<QWidget *>(interactStat),static_cast<QWidget *>(interactStatDelta)})
        w->setProperty("adventureGuard", true);
    auto *musicAction = new GameComboBox(&dialog);
    musicAction->addItem(tr("No music action"), QStringLiteral("none"));
    musicAction->addItem(tr("Play selected tune"), QStringLiteral("play"));
    musicAction->addItem(tr("Stop current music"), QStringLiteral("stop"));
    musicAction->setCurrentIndex(qMax(0, musicAction->findData(old.triggerMusicAction)));
    form->addRow(tr("When triggered — music"), musicAction);
    auto *musicTrack = new GameComboBox(&dialog);
    musicTrack->addItem(tr("Choose a tune from Music"), QString());
    for (const Resource &candidate : m_resources)
        if (candidate.kind == QStringLiteral("music") && !candidate.path.isEmpty())
            musicTrack->addItem(candidate.name, candidate.id);
    musicTrack->setCurrentIndex(qMax(0, musicTrack->findData(old.triggerMusicId)));
    musicTrack->setToolTip(tr("Choose a music resource. The IDE uses its saved ID, not the filename."));
    form->addRow(tr("Tune"), musicTrack);

    // A Goto World is a trigger sensor, never a solid door. World names are
    // the same sanitized .sbgm basenames used by gameworlds_request().
    form = gotoCard.form;
    auto *gotoWorld = new GameComboBox(&dialog);
    gotoWorld->addItem(tr("Choose destination world"), QString());
    const QDir projectDir(QFileInfo(m_filePath).absolutePath());
    const QString thisWorld = sidboxTilemapWorldBaseName(m_filePath);
    for (const QFileInfo &world : projectDir.entryInfoList(
            QStringList{QStringLiteral("*.sbgm")}, QDir::Files, QDir::Name)) {
        const QString worldName = sidboxTilemapWorldBaseName(world.absoluteFilePath());
        if (worldName != thisWorld && gotoWorld->findData(worldName) < 0)
            gotoWorld->addItem(world.completeBaseName(), worldName);
    }
    gotoWorld->setCurrentIndex(qMax(0, gotoWorld->findData(old.gotoWorldName)));
    form->addRow(tr("Destination world"), gotoWorld);
    auto *gotoStart = new GameComboBox(&dialog);
    const auto populateGotoStarts = [this, gotoWorld, gotoStart](const QString &selectedId) {
        gotoStart->clear();
        gotoStart->addItem(tr("Default start"), QStringLiteral("default"));
        const QString target = gotoWorld->currentData().toString();
        if (!target.isEmpty()) {
            const QDir project(QFileInfo(m_filePath).absolutePath());
            QString designPath;
            for (const QFileInfo &candidate : project.entryInfoList(
                    QStringList{QStringLiteral("*.sbgm")}, QDir::Files)) {
                if (sidboxTilemapWorldBaseName(candidate.absoluteFilePath()) == target) {
                    designPath = candidate.absoluteFilePath(); break;
                }
            }
            QFile file(designPath);
            if (!designPath.isEmpty() && file.open(QIODevice::ReadOnly)) {
                const QJsonObject design = QJsonDocument::fromJson(file.readAll()).object();
                for (const QJsonValue &entry : design.value(QStringLiteral("playerStarts")).toArray()) {
                    const QJsonObject start = entry.toObject();
                    const QString id = start.value(QStringLiteral("id")).toString();
                    if (!id.isEmpty() && id != QStringLiteral("default"))
                        gotoStart->addItem(start.value(QStringLiteral("name")).toString(id), id);
                }
            }
        }
        const int found = gotoStart->findData(selectedId);
        if (found >= 0) gotoStart->setCurrentIndex(found);
        else if (!selectedId.isEmpty() && selectedId != QStringLiteral("default")) {
            // Do not silently change a saved destination if another world removed it.
            gotoStart->addItem(tr("Missing entrance: %1").arg(selectedId), selectedId);
            gotoStart->setCurrentIndex(gotoStart->count() - 1);
        }
    };
    populateGotoStarts(old.gotoStartId);
    connect(gotoWorld, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
        [populateGotoStarts](int) { populateGotoStarts(QStringLiteral("default")); });
    form->addRow(tr("Arrival location"), gotoStart);
    auto *gotoActivation = new GameComboBox(&dialog);
    gotoActivation->addItem(tr("Touch door"), false);
    gotoActivation->addItem(tr("Press FIRE2 while touching"), true);
    gotoActivation->setCurrentIndex(old.gotoPress ? 1 : 0);
    form->addRow(tr("Enter using"), gotoActivation);
    form->addRow(new QLabel(tr("The destination world owns its named player starts."), &dialog));

    form = collectCard.form;
    auto *respawn = spin(0, 65535, old.respawnFrames);
    auto *collectOnce = new QCheckBox(tr("One-time collectable (never respawn)"), &dialog);
    collectOnce->setChecked(old.respawnFrames == 0);
    collectOnce->setToolTip(tr("When collected, it stays gone until the level or game restarts. "
        "Untick to set a respawn delay in 50 FPS game frames."));
    form->addRow(QString(),collectOnce);
    form->addRow(tr("Respawn frames"), quickValue(respawn));
    connect(collectOnce,&QCheckBox::toggled,&dialog,[&](bool oneTime){
        if(!oneTime && respawn->value()==0)respawn->setValue(250);
        respawn->setEnabled(!oneTime && type->currentData().toString()==QStringLiteral("collectable"));
    });
    form = collisionCard.form;
    auto *hitW = spin(1, 1024, old.hitWidth);
    auto *hitH = spin(1, 1024, old.hitHeight);
    hitW->setToolTip(tr("Width in pixels of this object's collision rectangle."));
    hitH->setToolTip(tr("Height in pixels of this object's collision rectangle."));
    // Width and height now live directly below Collision Preview (right pane).
    // They are still the SAME spinboxes that are saved into the resource.
    form->addRow(tr("Hitbox"), new QLabel(
        tr("Adjust collision Width and Height under Collision Preview →"), &dialog));
    form = conveyorCard.form;
    auto *conveyor = spin(-100, 100, old.conveyorSpeed);
    form->addRow(tr("Conveyor px/frame"), quickValue(conveyor));
    form = springCard.form;
    auto *spring = spin(1, 100, old.springStrength);
    form->addRow(tr("Launch upward"), quickValue(spring));
    auto *springLaunchX = spin(-40, 40, old.springLaunchX);
    springLaunchX->setToolTip(tr("Horizontal spring trajectory: negative launches LEFT, "
                                 "positive launches RIGHT, and 0 launches straight up. "
                                 "Normal mode pushes constantly until landing; Slidy mode "
                                 "gradually slows down, including after landing."));
    form->addRow(tr("Launch sideways"), quickValue(springLaunchX));
    auto *springTouch = new QCheckBox(tr("Activate on touch (any side)"), &dialog);
    springTouch->setChecked(old.springTouch);
    springTouch->setToolTip(tr("Off: spring launches only when the player lands on its top. "
                                 "On: entering the spring hitbox from above, below or either side "
                                 "launches the player. Fires once per contact; leave it to rearm."));
    form->addRow(QString(), springTouch);
    auto *springSlide = new QCheckBox(tr("Slidy kickback (inertia + friction)"), &dialog);
    springSlide->setChecked(old.springSlide);
    springSlide->setToolTip(tr("Off: classic sideways kick stays at full speed until landing. "
                               "On: sideways spring impulse uses the player's current "
                               "physics friction (Ice, Water, Space, etc.) and works "
                               "with apply_force(). Joystick steering still works. "
                               "In user-owned main.c, also bind "
                               "world_player.spring_force_vx100 to player_physics.force_vx100. "
                               "Without this binding, legacy 6%/14% spring drag remains."));
    form->addRow(QString(), springSlide);
    auto *springJumpBoost = new QCheckBox(tr("Combine jump + spring launch (extra boost)"), &dialog);
    springJumpBoost->setChecked(old.springJumpBoost);
    springJumpBoost->setToolTip(tr("Off: spring launch strength alone. On: a newly pressed Jump "
                               "on contact adds the player's jump speed. "
                               "Requires the optional physics jump bindings."));
    form->addRow(QString(), springJumpBoost);

    // Each placed Breakable has an independent hit counter at runtime.
    form = breakCard.form;
    auto *breakHits = spin(1, 4, old.breakHits);
    breakHits->setToolTip(tr("The object disappears after 1 to 4 separate contacts."));
    form->addRow(tr("Hits to break"), quickValue(breakHits));
    auto *breakTouch = new QCheckBox(tr("Break on touch (leave before hitting again)"), &dialog);
    breakTouch->setChecked(old.breakTouch);
    breakTouch->setToolTip(tr("Off: count landings on the top only. On: touching from any side counts; "
                               "leave the object before another touch can count."));
    form->addRow(QString(), breakTouch);
    auto *breakFromBelow = new QCheckBox(tr("Break by jumping into underside (head-butt)"), &dialog);
    breakFromBelow->setChecked(old.breakFromBelow);
    breakFromBelow->setToolTip(tr("Only an intentional upward jump against the bottom counts as a hit. "
                                  "The block still supports standing on its top, but won't break from above."));
    form->addRow(QString(), breakFromBelow);
    auto *breakReward = new GameComboBox(&dialog);
    breakReward->addItem(tr("None — no reward"), QString());
    for (const Resource &candidate : m_resources) {
        if (candidate.id == old.id || candidate.kind != QStringLiteral("sprite") ||
            candidate.objectType != QStringLiteral("collectable")) continue;
        breakReward->addItem(candidate.name, candidate.id);
    }
    breakReward->setCurrentIndex(qMax(0, breakReward->findData(old.breakDropCollectableId)));
    breakReward->setToolTip(tr("On the final hit, activate this existing collectable "
                                "at the block's position and drop it onto the tilemap. "
                                "The selected collectable keeps its pickup value, sprite and sounds. "
                                "It stays hidden until spawned."));
    form->addRow(tr("Drop collectable on break"), breakReward);
    auto *breakRewardImpulse = new QCheckBox(tr("Launch reward when block breaks"), &dialog);
    breakRewardImpulse->setChecked(old.breakRewardImpulse);
    breakRewardImpulse->setToolTip(tr("Off: prize drops vertically as before. On: launch it in the "
                                    "chosen X/Y direction, then let gravity pull it onto the ground."));
    form->addRow(QString(), breakRewardImpulse);
    auto *breakRewardVx = spin(-20, 20, old.breakRewardVx);
    auto *breakRewardVy = spin(-20, 20, old.breakRewardVy);
    breakRewardVx->setToolTip(tr("Initial horizontal momentum in px/frame. Negative = left, positive = right."));
    breakRewardVy->setToolTip(tr("Initial vertical momentum in px/frame. Negative = up, positive = down."));
    form->addRow(pairFields(tr("Reward X speed"), quickValue(breakRewardVx),
                            tr("Reward Y speed"), quickValue(breakRewardVy)));
    auto *breakBounce = new QCheckBox(tr("Bounce on each stomp (spring launch)"), &dialog);
    breakBounce->setChecked(old.breakBounce);
    breakBounce->setToolTip(tr("When landing from above, launch the player on each hit, "
                                "including the final break. Has no effect in touch mode."));
    form->addRow(QString(), breakBounce);
    auto *breakStrength = spin(1, 100, old.breakStrength);
    form->addRow(tr("Bounce upward"), quickValue(breakStrength));
    auto *breakLaunchX = spin(-40, 40, old.breakLaunchX);
    form->addRow(tr("Bounce sideways"), quickValue(breakLaunchX));
    const auto updateBreakControls = [type, breakHits, breakTouch, breakFromBelow,
                                      breakReward, breakRewardImpulse, breakRewardVx, breakRewardVy,
                                      breakBounce, breakStrength, breakLaunchX]() {
        const bool b = type->currentData().toString() == QStringLiteral("breakable");
        breakHits->setEnabled(b);
        breakTouch->setEnabled(b && !breakFromBelow->isChecked());
        breakFromBelow->setEnabled(b && !breakTouch->isChecked());
        breakReward->setEnabled(b);
        const bool hasReward = b && !breakReward->currentData().toString().isEmpty();
        breakRewardImpulse->setEnabled(hasReward);
        breakRewardVx->setEnabled(hasReward && breakRewardImpulse->isChecked());
        breakRewardVy->setEnabled(hasReward && breakRewardImpulse->isChecked());
        breakBounce->setEnabled(b && !breakTouch->isChecked() &&
                                !breakFromBelow->isChecked());
        breakStrength->setEnabled(b && !breakTouch->isChecked() &&
                                  !breakFromBelow->isChecked() && breakBounce->isChecked());
        breakLaunchX->setEnabled(b && !breakTouch->isChecked() &&
                                 !breakFromBelow->isChecked() && breakBounce->isChecked());
    };
    connect(type, QOverload<int>::of(&QComboBox::currentIndexChanged), &dialog,
            [updateBreakControls](int) { updateBreakControls(); });
    connect(breakTouch, &QCheckBox::toggled, &dialog, updateBreakControls);
    connect(breakFromBelow, &QCheckBox::toggled, &dialog, updateBreakControls);
    connect(breakBounce, &QCheckBox::toggled, &dialog, updateBreakControls);
    connect(breakRewardImpulse, &QCheckBox::toggled, &dialog, updateBreakControls);
    connect(breakReward, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [updateBreakControls](int) { updateBreakControls(); });
    updateBreakControls();
    // A stompable enemy uses the well-tested breakable multi-hit + bounce path.
    // This separate card deliberately exposes only enemy-relevant properties.
    form = enemyCard.form;
    auto *enemyReward = new GameComboBox(&dialog);
    enemyReward->addItem(tr("None — no drop"), QString());
    for (const Resource &candidate : m_resources) {
        if (candidate.id == old.id || candidate.kind != QStringLiteral("sprite") ||
            candidate.objectType != QStringLiteral("collectable")) continue;
        enemyReward->addItem(candidate.name, candidate.id);
    }
    enemyReward->setCurrentIndex(qMax(0, enemyReward->findData(old.breakDropCollectableId)));
    enemyReward->setToolTip(tr("On defeat, spawn this hidden Collectable. Place it in the world and check Hidden until activated."));
    // Stage 4.41a: keep reward-launch controls prominent and full-width.
    // The earlier side-by-side slider row was too cramped in the scrolling
    // Game Object Properties column, making the X/Y controls hard to find.
    form->addRow(new QLabel(tr("DEFEAT REWARD — spawned when enemy dies"), &dialog));
    form->addRow(tr("Item dropped when defeated"), enemyReward);
    // Existing collectable-drop velocities (the same fields used by Breakables).
    auto *enemyRewardImpulse = new QCheckBox(tr("Launch dropped item on defeat"), &dialog);
    enemyRewardImpulse->setChecked(old.breakRewardImpulse);
    auto *enemyRewardVx = spin(-20, 20, old.breakRewardVx);
    auto *enemyRewardVy = spin(-20, 20, old.breakRewardVy);
    enemyRewardVx->setToolTip(tr("Initial X speed in px/frame. Negative = LEFT; positive = RIGHT."));
    enemyRewardVy->setToolTip(tr("Initial Y speed in px/frame. Negative = UP; positive = DOWN. Gravity takes over."));
    // Disable the slider AND the numeric spin box together, not just the box.
    QWidget *enemyRewardXField = quickValue(enemyRewardVx);
    QWidget *enemyRewardYField = quickValue(enemyRewardVy);
    form->addRow(QString(), enemyRewardImpulse);
    form->addRow(tr("Reward speed X (px/frame)"), enemyRewardXField);
    form->addRow(tr("Reward speed Y (px/frame)"), enemyRewardYField);
    const auto updateEnemyRewardControls = [enemyReward, enemyRewardImpulse,
                                           enemyRewardXField, enemyRewardYField]() {
        const bool hasDrop = !enemyReward->currentData().toString().isEmpty();
        enemyRewardImpulse->setEnabled(hasDrop);
        const bool launch = hasDrop && enemyRewardImpulse->isChecked();
        enemyRewardXField->setEnabled(launch);
        enemyRewardYField->setEnabled(launch);
    };
    connect(enemyReward, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [updateEnemyRewardControls](int){ updateEnemyRewardControls(); });
    connect(enemyRewardImpulse, &QCheckBox::toggled, &dialog, updateEnemyRewardControls);
    updateEnemyRewardControls();
    auto *enemyHits = spin(1, 20, old.breakHits);
    auto *enemyBounce = new QCheckBox(tr("Bounce player after every stomp"), &dialog);
    enemyBounce->setChecked(old.objectType == QStringLiteral("enemy") ? old.breakBounce : true);
    auto *enemyBounceY = spin(1, 40, old.breakStrength);
    auto *enemyBounceX = spin(-40, 40, old.breakLaunchX);
    auto *enemyStompSideKick = new QCheckBox(tr("Also kick player SIDEWAYS on a vulnerable hit"), &dialog);
    enemyStompSideKick->setChecked(old.enemyStompSideKick);
    enemyStompSideKick->setToolTip(tr("Normally head-stomps rebound vertically only. Turn ON to add the signed X kick; "
                                      "this does NOT affect the red body's knockback-on-damage controls."));
    auto *enemyAttackDirection = new GameComboBox(&dialog);
    enemyAttackDirection->addItem(tr("From ABOVE (fall onto head)"), 0);
    enemyAttackDirection->addItem(tr("From BELOW (jump into underside)"), 1);
    enemyAttackDirection->addItem(tr("BOTH (top or underside)"), 2);
    enemyAttackDirection->setCurrentIndex(qMax(0, enemyAttackDirection->findData(old.enemyAttackDirection)));
    enemyAttackDirection->setToolTip(tr("The GREEN hitbox is the vulnerable area for these attacks. "
                                       "From below requires a deliberate upward jump. "
                                       "A successful underside hit stops upward movement, avoiding repeated hits."));
    auto *enemyHurt = new QCheckBox(tr("Hurt player on side / underside contact"), &dialog);
    enemyHurt->setChecked(old.enemyHurtsOnTouch);
    auto *enemyDamage = spin(0, 65535, old.enemyDamage);
    auto *enemyDefeatFrame = spin(-1, 255, old.enemyDefeatFrame);
    enemyDefeatFrame->setSpecialValueText(tr("None — disappear immediately"));
    auto *enemyDefeatCount = spin(1, 255, old.enemyDefeatCount);
    auto *enemyDefeatDelay = spin(1, 255, old.enemyDefeatDelay);
    auto *enemyStompX = spin(-64, 64, old.enemyStompOffsetX);
    auto *enemyStompY = spin(-64, 64, old.enemyStompOffsetY);
    auto *enemyStompW = spin(0, 512, old.enemyStompWidth);
    enemyStompW->setSpecialValueText(tr("Match body width"));
    auto *enemyStompH = spin(1, 64, old.enemyStompHeight);
    enemyHits->setToolTip(tr("Number of distinct stomps to defeat this enemy. One landing counts once."));
    enemyBounceY->setToolTip(tr("A fixed bounce impulse, independent from held-jump boost."));
    enemyDefeatFrame->setToolTip(tr("Starting atlas frame for the death animation. -1 = vanish immediately."));
    enemyDefeatCount->setToolTip(tr("Consecutive atlas frames, starting at the death start frame. Plays ONCE."));
    enemyDefeatDelay->setToolTip(tr("Game ticks PER death frame, at 50 FPS. A one-frame pose stays for this duration."));
    enemyStompX->setToolTip(tr("Vulnerable-zone left edge relative to the enemy body. Negative extends left."));
    enemyStompY->setToolTip(tr("Vulnerable-zone top relative to body. Negative moves it ABOVE the enemy."));
    enemyStompW->setToolTip(tr("Width of the vulnerable zone. Zero automatically uses body width."));
    enemyStompH->setToolTip(tr("Green vulnerable box height, for downward stomps OR deliberate upward head-butts."));
    form->addRow(tr("Hits before enemy dies"), quickValue(enemyHits));
    form->addRow(QString(), enemyBounce);
    form->addRow(tr("Top-hit rebound (upward)"), quickValue(enemyBounceY));
    form->addRow(QString(), enemyStompSideKick);
    form->addRow(tr("Optional sideways kick X"), quickValue(enemyBounceX));
    form->addRow(tr("Green weak spot can be hit"), enemyAttackDirection);
    form->addRow(new QLabel(tr("From BELOW: the hit stops the player's ascent; with rebound ON, "
                                "Kim recoils DOWN to separate from the enemy."), &dialog));
    form->addRow(QString(), enemyHurt);
    enemyDamage->hide(); // Shared Hazard/Murder damage card owns the single damage setting.
    form->addRow(new QLabel(tr("DEATH ANIMATION — plays once, then disappears"), &dialog));
    // Keep numeric entry for exact edits, but make visual selection the easy path.
    auto *deathStartPicker = new QPushButton(tr("Choose from atlas..."), &dialog);
    deathStartPicker->setToolTip(tr("See the sprite atlas and choose the first frame visually. "
                                    "The existing frame IDs and generated C remain unchanged."));
    auto *deathStartRow = new QWidget(&dialog);
    auto *deathStartLayout = new QHBoxLayout(deathStartRow);
    deathStartLayout->setContentsMargins(0, 0, 0, 0);
    deathStartLayout->setSpacing(7);
    enemyDefeatFrame->setMinimumWidth(88);
    deathStartLayout->addWidget(enemyDefeatFrame);
    deathStartLayout->addWidget(deathStartPicker, 1);
    form->addRow(tr("Death starting atlas frame"), deathStartRow);
    form->addRow(tr("Number of death frames"), quickValue(enemyDefeatCount));
    form->addRow(tr("Delay per frame (50 FPS)"), quickValue(enemyDefeatDelay));
    form->addRow(new QLabel(tr("GREEN VULNERABLE HITBOX — independent of RED danger/body"), &dialog));
    form->addRow(tr("Stomp box X offset (px)"), quickValue(enemyStompX));
    form->addRow(tr("Stomp box Y offset (px)"), quickValue(enemyStompY));
    form->addRow(tr("Stomp box width (px)"), quickValue(enemyStompW));
    form->addRow(tr("Stomp box height (px)"), quickValue(enemyStompH));
    const auto updateDeathOptions = [enemyDefeatFrame, enemyDefeatCount, enemyDefeatDelay]() {
        const bool enabled = enemyDefeatFrame->value() >= 0;
        enemyDefeatCount->setEnabled(enabled);
        enemyDefeatDelay->setEnabled(enabled);
    };
    connect(enemyDefeatFrame, qOverload<int>(&QSpinBox::valueChanged),
            &dialog, [updateDeathOptions](int) { updateDeathOptions(); });
    updateDeathOptions();
    form->addRow(new QLabel(tr("ABOVE: place the green box over the head (e.g. Y=-6).\n"
                                "BELOW: place it under the feet (e.g. Y=body height).\n"
                                "Red remains dangerous; the weak spot works only from the chosen direction."), &dialog));
    auto *enemyRoam = new QCheckBox(tr("Walk on tilemap (patrol and turn at walls)"), &dialog);
    enemyRoam->setChecked(old.enemyRoam);
    enemyRoam->setToolTip(tr("Uses solid tiles and slopes. Overrides the Movement Spline for THIS enemy. "
                             "Place the enemy with its feet on the ground. Requires Advanced Platformer."));
    auto *enemyRoamSpeed = spin(1, 8, old.enemyRoamSpeed);
    auto *enemyStepHeight = spin(1, 12, old.enemyStepHeight);
    auto *enemyRoamLeft = new QCheckBox(tr("Start walking left"), &dialog);
    enemyRoamLeft->setChecked(old.enemyRoamLeft);
    enemyStepHeight->setToolTip(tr("Maximum rise or fall allowed for each 1-pixel patrol step. "
                                  "Lower = resists steeper slopes; higher = climbs steeper terrain. "
                                  "A wall taller than this makes the enemy turn around."));
    enemyRoamSpeed->setToolTip(tr("Pixels moved per 50 Hz game frame. Start with 1."));
    form->addRow(QString(), enemyRoam);
    form->addRow(tr("Patrol speed (px/frame)"), quickValue(enemyRoamSpeed));
    form->addRow(tr("Slope climb / descent (px)"), quickValue(enemyStepHeight));
    form->addRow(QString(), enemyRoamLeft);
    auto updateEnemyRoam = [=]() {
        const bool enabled = type->currentData().toString() == QStringLiteral("enemy") &&
            enemyRoam->isChecked();
        enemyRoamSpeed->setEnabled(enabled);
        enemyStepHeight->setEnabled(enabled);
        enemyRoamLeft->setEnabled(enabled);
    };
    connect(enemyRoam, &QCheckBox::toggled, &dialog, updateEnemyRoam);
    connect(type, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [updateEnemyRoam](int) { updateEnemyRoam(); });
    updateEnemyRoam();
    form->addRow(new QLabel(tr("Damage, knockback, hurt animation and flashing are in the\n"
                                "Damage / Knockback / Hurt Effects card directly below.\n"
                                "The drop requires a hidden Collectable; linked actions fire on final stomp."), &dialog));
    const auto updateEnemyBounceControls = [enemyBounce,enemyBounceY,enemyBounceX,enemyStompSideKick]() {
        enemyBounceY->setEnabled(enemyBounce->isChecked());
        enemyStompSideKick->setEnabled(enemyBounce->isChecked());
        enemyBounceX->setEnabled(enemyBounce->isChecked() && enemyStompSideKick->isChecked());
    };
    connect(enemyBounce, &QCheckBox::toggled, &dialog, updateEnemyBounceControls);
    connect(enemyStompSideKick, &QCheckBox::toggled, &dialog, updateEnemyBounceControls);
    updateEnemyBounceControls();
    // Damage and visual hit effects share the well-tested Murder Object settings.
    enemyDamage->setEnabled(false);
    // Hazards are intangible damage sensors. The direction values below are
    // signed; negative Y sends the player UP, positive Y pushes them DOWN.
    form = hazardCard.form;
    auto *hazardDamage = spin(0, 65535, old.objectType == QStringLiteral("enemy") ? old.enemyDamage : old.hazardDamage);
    auto *hazardKick = new QCheckBox(tr("Knock player back on hit"), &dialog);
    hazardKick->setChecked(old.hazardKick);
    auto *hazardKickX = spin(-40, 40, old.hazardKickX);
    auto *hazardKickY = spin(-40, 40, old.hazardKickY);
    hazardKickX->setToolTip(tr("Stompable Enemy: horizontal knockback STRENGTH (absolute value); "
                              "the player is pushed away from the approaching collision. "
                              "Murder Object: signed direction (- left, + right). Zero disables horizontal knockback."));
    hazardKickY->setToolTip(tr("Negative = kick up; positive = kick down; zero = no vertical kick."));
    hazardDamage->setToolTip(tr("Amount passed to your game's damage callback. Your game decides how health is used."));
    auto *hazardHurtAnim = new QCheckBox(tr("Use player Hurt animation on damage"), &dialog);
    hazardHurtAnim->setChecked(old.hazardHurtAnimation);
    auto *hazardFlash = new QCheckBox(tr("Flash player using solid-colour BOB"), &dialog);
    hazardFlash->setChecked(old.hazardFlash);
    auto *hazardColour = new QPushButton(&dialog);
    int chosenHazardColour = qBound(0, old.hazardFlashColour, 255);
    QVector<QRgb> flashBank = activePalette(QStringLiteral("foreground"));
    if (flashBank.size() != 256 && !old.path.isEmpty()) {
        SidboxPpb::Picture flashPicture;
        if (SidboxPpb::read(resolvedPath(old.path), &flashPicture))
            flashBank = flashPicture.indexed.colorTable();
    }
    const auto updateFlashSwatch = [&]() {
        hazardColour->setText(tr("Index %1  —  Pick palette colour...").arg(chosenHazardColour));
        if (flashBank.size()==256) {
            QPixmap swatch(22,22);
            swatch.fill(QColor::fromRgba(flashBank.at(chosenHazardColour)));
            hazardColour->setIcon(QIcon(swatch));
            hazardColour->setIconSize(QSize(22,22));
        } else {
            hazardColour->setIcon(QIcon());
        }
    };
    updateFlashSwatch();
    hazardColour->setToolTip(tr("Pick a foreground CLUT index from the 16×16 palette. "
                                  "Uses the active foreground palette or this PPB's palette."));
    connect(hazardColour, &QPushButton::clicked, &dialog, [&]() {
        if (flashBank.size()!=256) {
            QMessageBox::information(&dialog,tr("Flash CLUT colour"),
                tr("Select a foreground 256-colour palette or an indexed PPB first."));
            return;
        }
        const int selected = SidboxPalettePicker::chooseIndex(&dialog, flashBank,
            chosenHazardColour, tr("Pick flash foreground CLUT colour"),
            tr("Select a colour from the foreground palette (index 0 is transparent)."));
        if (selected >= 0) {
            chosenHazardColour = selected;
            updateFlashSwatch();
        }
    });
    auto *hazardFlashes = spin(1, 32, old.hazardFlashCount);
    auto *hazardFlashFrames = spin(1, 255, old.hazardFlashFrames);
    hazardDamage->hide(); // Historical magnitude retained for old runtime source only.
    auto *damageTarget = new GameComboBox(&dialog);
    damageTarget->addItem(tr("Health"), QStringLiteral("health"));
    damageTarget->addItem(tr("Lives"), QStringLiteral("lives"));
    damageTarget->addItem(tr("Score"), QStringLiteral("score"));
    damageTarget->addItem(tr("Coins (inventory pickup type 1)"), QStringLiteral("coins"));
    const QDir playerRoot(QFileInfo(m_filePath).absolutePath());
    const QStringList playerDefs = QDir(playerRoot.filePath(QStringLiteral("players")))
        .entryList({QStringLiteral("*.sbpi")}, QDir::Files, QDir::Name);
    for (const QString &playerFile:playerDefs) {
        QFile pf(playerRoot.filePath(QStringLiteral("players/")+playerFile));
        if (!pf.open(QIODevice::ReadOnly)) continue;
        const QJsonArray custom=QJsonDocument::fromJson(pf.readAll()).object().value(QStringLiteral("customStats")).toArray();
        for (const QJsonValue &entry:custom) {
            const QString name=entry.toObject().value(QStringLiteral("name")).toString();
            if (!name.isEmpty() && damageTarget->findData(QStringLiteral("stat:")+name)<0)
                damageTarget->addItem(tr("Custom stat: %1").arg(name),QStringLiteral("stat:")+name);
        }
    }
    if (damageTarget->findData(old.damageTarget)<0)
        damageTarget->addItem(old.damageTarget,old.damageTarget);
    damageTarget->setCurrentIndex(qMax(0,damageTarget->findData(old.damageTarget)));
    auto *damageDelta=spin(-65535,65535,old.damageConfigured ? old.damageDelta :
        -(old.objectType==QStringLiteral("enemy") ? old.enemyDamage : old.hazardDamage));
    damageDelta->setToolTip(tr("Signed value applied ONCE per accepted enemy/hazard hit. "
                              "Negative removes, positive rewards or heals."));
    form->addRow(tr("Damage target stat"),damageTarget);
    form->addRow(tr("Stat change (+/-)"),damageDelta);
    form->addRow(QString(), hazardKick);
    form->addRow(tr("Knockback X"), quickValue(hazardKickX));
    form->addRow(tr("Knockback Y"), quickValue(hazardKickY));
    form->addRow(QString(), hazardHurtAnim);
    form->addRow(QString(), hazardFlash);
    form->addRow(tr("Flash CLUT colour"), hazardColour);
    form->addRow(tr("Number of flashes"), quickValue(hazardFlashes));
    form->addRow(tr("Frames between flashes"), quickValue(hazardFlashFrames));
    auto updateHazardControls = [=]() {
        const bool hazard = type->currentData().toString() == QStringLiteral("hazard") ||
                            type->currentData().toString() == QStringLiteral("enemy");
        for (QWidget *w : {static_cast<QWidget *>(hazardDamage), static_cast<QWidget *>(hazardKick),
                           static_cast<QWidget *>(hazardHurtAnim), static_cast<QWidget *>(hazardFlash),
                           static_cast<QWidget *>(damageTarget), static_cast<QWidget *>(damageDelta)})
            w->setEnabled(hazard);
        hazardKickX->setEnabled(hazard && hazardKick->isChecked());
        hazardKickY->setEnabled(hazard && hazardKick->isChecked());
        hazardColour->setEnabled(hazard && hazardFlash->isChecked());
        hazardFlashes->setEnabled(hazard && hazardFlash->isChecked());
        hazardFlashFrames->setEnabled(hazard && hazardFlash->isChecked());
    };
    connect(hazardKick, &QCheckBox::toggled, &dialog, updateHazardControls);
    connect(hazardFlash, &QCheckBox::toggled, &dialog, updateHazardControls);
    connect(type, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [updateHazardControls](int) { updateHazardControls(); });
    updateHazardControls();
    /* Friendly default for a newly converted enemy: knock Kim sideways away
       from the enemy as well as upward. Existing enemy values remain intact. */
    connect(type, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [type, hazardKickX, initialType = old.objectType](int) {
        if (type->currentData().toString() == QStringLiteral("enemy") &&
            initialType != QStringLiteral("enemy") && hazardKickX->value() == 0)
            hazardKickX->setValue(8);
    });
    form = visualCard.form;
    auto *spline = new GameComboBox(&dialog);
    spline->addItem(tr("None (stationary)"), QString());
    const QIcon splineResourceIcon = gameResourceIcon(QStringLiteral("gr_icon_spline.png"));
    for (const SplinePath &path : m_splinePaths)
        spline->addItem(splineResourceIcon, path.name, path.id);
    spline->setCurrentIndex(qMax(0, spline->findData(old.objectSplineId)));
    form->addRow(tr("Movement spline"), spline);
    auto *splineDelay = spin(0, 65535, old.objectSplineStartDelay);
    splineDelay->setSuffix(tr(" frames"));
    splineDelay->setToolTip(tr("Wait this many 50 Hz game frames before this particular Game Object begins its spline. "
                              "For example, 50 frames = 1 second. Different objects can share the same spline "
                              "with different start delays. Zero starts immediately."));
    form->addRow(tr("Spline start delay"), quickValue(splineDelay));
    auto *animated = new QCheckBox(tr("Animate sprite frames"), &dialog);
    animated->setChecked(old.objectAnimated);
    form->addRow(QString(), animated);
    auto *objectFlipX = new QCheckBox(tr("Flip X"), &dialog);
    auto *objectFlipY = new QCheckBox(tr("Flip Y"), &dialog);
    objectFlipX->setChecked(old.objectFlipX);
    objectFlipY->setChecked(old.objectFlipY);
    objectFlipX->setToolTip(tr("Mirror this object's artwork horizontally. Does not change the collision rectangle or movement path."));
    objectFlipY->setToolTip(tr("Mirror this object's artwork vertically. Does not change the collision rectangle or movement path."));
    auto *flipRow = new QWidget(&dialog);
    auto *flipLayout = new QHBoxLayout(flipRow);
    flipLayout->setContentsMargins(0, 0, 0, 0);
    flipLayout->setSpacing(18);
    flipLayout->addWidget(objectFlipX);
    flipLayout->addWidget(objectFlipY);
    flipLayout->addStretch();
    form->addRow(tr("Sprite mirroring"), flipRow);
    auto *objectFadeRow = new QWidget(&dialog);
    auto *objectFadeLayout = new QHBoxLayout(objectFadeRow);
    objectFadeLayout->setContentsMargins(0, 0, 0, 0);
    objectFadeLayout->setSpacing(8);
    auto *objectFadeSlider = new QSlider(Qt::Horizontal, objectFadeRow);
    objectFadeSlider->setRange(0, 100);
    objectFadeSlider->setValue(old.objectAlphaFadePercent);
    auto *objectFadeValue = new QSpinBox(objectFadeRow);
    objectFadeValue->setRange(0, 100);
    objectFadeValue->setSuffix(tr(" %"));
    objectFadeValue->setValue(old.objectAlphaFadePercent);
    objectFadeValue->setFixedWidth(80);
    connect(objectFadeSlider, &QSlider::valueChanged,
            objectFadeValue, &QSpinBox::setValue);
    connect(objectFadeValue, qOverload<int>(&QSpinBox::valueChanged),
            objectFadeSlider, &QSlider::setValue);
    objectFadeLayout->addWidget(objectFadeSlider, 1);
    objectFadeLayout->addWidget(objectFadeValue);
    objectFadeRow->setToolTip(tr("SIDBOX 4x4 patterned fade. 0% = normal solid sprite; "
                                 "100% = fully faded. The editor shows a live 4x4 dither "
                                 "approximation, not RGB alpha. Verify the exact pattern on SIDBOX."));
    form->addRow(tr("BOB patterned fade"), objectFadeRow);
    auto *fadeAnimate = new QCheckBox(tr("Animate patterned fade"), &dialog);
    fadeAnimate->setChecked(old.objectFadeAnimated);
    auto *fadeLow = spin(0, 100, old.objectFadeLow);
    auto *fadeHigh = spin(0, 100, old.objectFadeHigh);
    auto *fadeStep = spin(1, 100, old.objectFadeStep);
    auto *fadeDelay = spin(1, 32656, old.objectFadeDelay);
    fadeDelay->setSuffix(tr(" frames"));
    auto *fadePingpong = new QCheckBox(tr("Ping-pong (reverse at ends)"), &dialog);
    fadePingpong->setChecked(old.objectFadePingpong);
    fadeAnimate->setToolTip(tr("Animate this sprite's patterned BOB fade independently of sprite-frame animation. "
                               "Animation begins at the lowest percentage when the world loads."));
    fadeStep->setToolTip(tr("Fade percentage points to advance per delay. For example 5% every 2 frames."));
    fadeDelay->setToolTip(tr("SIDBOX runs at 50 FPS. 30,000 frames is 10 minutes "
        "between fade steps; maximum 32,656 frames (~10 min 53 s)."));
    fadePingpong->setToolTip(tr("Checked: low to high to low, repeating without duplicate end frames. "
                               "Unchecked: low to high, then jump back to low and repeat."));
    form->addRow(QString(), fadeAnimate);
    form->addRow(tr("Lowest fade"), quickValue(fadeLow));
    form->addRow(tr("Highest fade"), quickValue(fadeHigh));
    form->addRow(tr("Fade step"), quickValue(fadeStep));
    form->addRow(tr("Frames per fade step"), quickValue(fadeDelay));
    form->addRow(QString(), fadePingpong);
    const auto refreshFadeControls = [=]() {
        const bool enabled = fadeAnimate->isChecked();
        for (QWidget *w : {static_cast<QWidget *>(fadeLow), static_cast<QWidget *>(fadeHigh),
                           static_cast<QWidget *>(fadeStep), static_cast<QWidget *>(fadeDelay),
                           static_cast<QWidget *>(fadePingpong)}) w->setEnabled(enabled);
        objectFadeRow->setToolTip(enabled
            ? tr("The slider is the static fade setting; animation overrides it while enabled.")
            : tr("Static patterned fade percentage."));
    };
    connect(fadeAnimate, &QCheckBox::toggled, &dialog, [=](bool) { refreshFadeControls(); });
    refreshFadeControls();
    // Only scenery particles have a lifespan-based fade. Keep this under
    // Visual Movements, immediately after the ordinary patterned BOB fade.
    auto *particleFadeNote = new QLabel(tr(
        "Particles: fade in during the first N% of lifetime, fade out during the last N%. "
        "100% patterned fade is invisible; speed limits the percentage change per 50-Hz frame."), &dialog);
    particleFadeNote->setWordWrap(true);
    auto *particleFadeEnable = new QCheckBox(tr("Enable particle fade in / out"), &dialog);
    particleFadeEnable->setChecked(old.particleFadeEnabled);
    // Choosing the firefly preset starts with a gentle appearance/disappearance.
    // This does not alter existing saved spawners; only an explicit preset
    // selection changes the editor's current fade checkbox.
    connect(particlePreset, qOverload<int>(&QComboBox::activated), &dialog,
        [particlePreset, particleFadeEnable](int) {
            if (particlePreset->currentData().toString() == QStringLiteral("fireflies"))
                particleFadeEnable->setChecked(true);
        });
    auto *particlePlayerMix = new QCheckBox(tr("Allow some particles in front of player"), &dialog);
    particlePlayerMix->setChecked(old.particlePlayerLayerMix);
    auto *particleFadeIn = spin(0, 100, old.particleFadeIn);
    auto *particleFadeOut = spin(0, 100, old.particleFadeOut);
    auto *particleFadeSpeed = spin(1, 100, old.particleFadeSpeed);
    particleFadeIn->setSuffix(tr(" % life"));
    particleFadeOut->setSuffix(tr(" % life"));
    particleFadeSpeed->setSuffix(tr(" % / frame"));
    particleFadeEnable->setToolTip(tr("Applies independent 4x4 patterned fading to each particle. "
        "Does not affect the source sprite, existing BOB fade, collisions or spawn rate."));
    particlePlayerMix->setToolTip(tr("For Particle Spawners drawn after the regular tile pass, randomly splits new particles so some stay behind the player and some draw in front. FRONT map tiles still draw over both groups. Disabled when Draw behind tiles is checked."));
    particleFadeIn->setToolTip(tr("0% = immediately visible. Otherwise fades from invisible to solid over "
        "this percentage of the particle lifetime."));
    particleFadeOut->setToolTip(tr("0% = no fade out. Otherwise fades from solid to invisible over "
        "the final percentage of the particle lifetime."));
    particleFadeSpeed->setToolTip(tr("Maximum percentage points of patterned fade adjusted each 50-Hz frame. "
        "For example 8 means the fade can change by at most 8 points per frame."));
    form->addRow(particleFadeEnable);
    form->addRow(particlePlayerMix);
    QWidget *particleFadeInRow = quickValue(particleFadeIn);
    QWidget *particleFadeOutRow = quickValue(particleFadeOut);
    QWidget *particleFadeSpeedRow = quickValue(particleFadeSpeed);
    form->addRow(tr("Particle fade in"), particleFadeInRow);
    form->addRow(tr("Particle fade out"), particleFadeOutRow);
    form->addRow(tr("Particle fade speed"), particleFadeSpeedRow);
    QLabel *particleFadeInLabel = qobject_cast<QLabel *>(form->labelForField(particleFadeInRow));
    QLabel *particleFadeOutLabel = qobject_cast<QLabel *>(form->labelForField(particleFadeOutRow));
    QLabel *particleFadeSpeedLabel = qobject_cast<QLabel *>(form->labelForField(particleFadeSpeedRow));
    form->addRow(particleFadeNote);
    auto refreshParticleFade = [=]() {
        const bool valid = particleFadeEnable->isVisible() && particleFadeEnable->isChecked();
        for (QWidget *w : {static_cast<QWidget *>(particleFadeIn),
                           static_cast<QWidget *>(particleFadeOut),
                           static_cast<QWidget *>(particleFadeSpeed)}) {
            w->setEnabled(valid);
        }
        const bool mixValid = particlePlayerMix->isVisible() && !behindTiles->isChecked();
        particlePlayerMix->setEnabled(mixValid);
        particlePlayerMix->setToolTip(mixValid
            ? tr("For Particle Spawners drawn after the regular tile pass, randomly splits new particles so some stay behind the player and some draw in front. FRONT map tiles still draw over both groups.")
            : tr("Unavailable while Draw behind tiles is checked, because those particles must stay under the world tilemap."));
    };
    connect(particleFadeEnable, &QCheckBox::toggled, &dialog,
            [refreshParticleFade](bool) { refreshParticleFade(); });
    connect(behindTiles, &QCheckBox::toggled, &dialog,
            [refreshParticleFade](bool) { refreshParticleFade(); });
    refreshParticleFade();
    form = animationCard.form;
    auto *first = spin(0, 255, old.animFirst);
    auto *count = spin(1, 256, old.animCount);
    auto *ticks = spin(1, 65535, old.animTicks);
    form->addRow(tr("First frame"), first);
    form->addRow(tr("Number of frames"), count);
    form->addRow(tr("Ticks per frame"), quickValue(ticks));
    auto *mode = new GameComboBox(&dialog);
    mode->addItem(tr("Loop"), QStringLiteral("loop"));
    mode->addItem(tr("Ping-pong"), QStringLiteral("pingpong"));
    mode->addItem(tr("Once"), QStringLiteral("once"));
    mode->setCurrentIndex(qMax(0, mode->findData(old.animMode)));
    form->addRow(tr("Animation mode"), mode);
    // Reuse actual Sound resources and their configured SIDBOX channels.
    // Store stable IDs so renaming a resource cannot break object references.
    auto soundPicker = [&](const QString &id) {
        auto *box = new GameComboBox(&dialog);
        box->addItem(tr("None"), QString());
        for (const Resource &sound : m_resources)
            if (sound.kind == QStringLiteral("sound"))
                box->addItem(sound.name + QStringLiteral("  [Ch %1]").arg(sound.audio.channel), sound.id);
        box->setCurrentIndex(qMax(0, box->findData(id)));
        return box;
    };
    auto *sfxInteractWrong = soundPicker(old.sfxInteractWrong);
    auto *sfxInteractSuccess = soundPicker(old.sfxInteractSuccess);
    auto *sfxInteractCancel = soundPicker(old.sfxInteractCancel);
    for (QComboBox *picker : {sfxInteractWrong, sfxInteractSuccess, sfxInteractCancel})
        picker->setToolTip(tr("Optional sound played for this inventory-item interaction. "
                               "Uses the selected Sound resource's audio channel and volume."));
    triggerCard.form->addRow(tr("Wrong inventory item — sound"), sfxInteractWrong);
    triggerCard.form->addRow(tr("Successful USE — sound"), sfxInteractSuccess);
    triggerCard.form->addRow(tr("Cancel USE — sound"), sfxInteractCancel);
    auto *sfxPickup = soundPicker(old.sfxPickup);
    auto *sfxRespawn = soundPicker(old.sfxRespawn);
    auto *sfxStart = soundPicker(old.sfxStart);
    auto *sfxMove = soundPicker(old.sfxMove);
    auto *sfxStop = soundPicker(old.sfxStop);
    auto *sfxReverse = soundPicker(old.sfxReverse);
    auto *sfxSpring = soundPicker(old.sfxSpring);
    auto *sfxAmbient = soundPicker(old.sfxAmbient);
    auto *sfxBreakHit = soundPicker(old.sfxBreakHit);
    auto *sfxBreakBounce = soundPicker(old.sfxBreakBounce);
    auto *sfxBreakFinish = soundPicker(old.sfxBreakFinish);
    auto *sfxHazardHit = soundPicker(old.sfxHazardHit);
    auto *sfxHazardBounce = soundPicker(old.sfxHazardBounce);
    auto *sfxHazardAmbient = soundPicker(old.sfxHazardAmbient);
    auto *radius = spin(0, 32767, old.audioRadius);
    auto *fade = spin(0, 255, old.audioFadeFrames);
    QFormLayout *audioForm = audioCollectCard.form;
    audioForm->addRow(pairFields(tr("Pickup sound"), sfxPickup,
                                  tr("Respawn sound"), sfxRespawn));
    audioForm = audioLiftCard.form;
    audioForm->addRow(tr("Mover starts"), sfxStart);
    audioForm->addRow(tr("Mover moving (loopable)"), sfxMove);
    audioForm->addRow(tr("Mover stops"), sfxStop);
    audioForm->addRow(tr("Mover reverses"), sfxReverse);
    audioForm = audioSpringCard.form;
    audioForm->addRow(tr("Spring launches"), sfxSpring);
    audioForm = audioConveyorCard.form;
    audioForm->addRow(tr("Conveyor ambience (loopable)"), sfxAmbient);
    audioForm = audioBreakCard.form;
    audioForm->addRow(tr("Breakable — hit"), sfxBreakHit);
    audioForm->addRow(tr("Breakable — bounce"), sfxBreakBounce);
    audioForm->addRow(tr("Breakable — shatter"), sfxBreakFinish);
    audioForm = audioHazardCard.form;
    audioForm->addRow(tr("Hazard — hit"), sfxHazardHit);
    audioForm->addRow(tr("Hazard — knockback"), sfxHazardBounce);
    audioForm->addRow(tr("Hazard — ambient (loopable)"), sfxHazardAmbient);
    audioForm = audioOptionsCard.form;
    audioForm->addRow(pairFields(tr("Audible radius"), radius,
                                  tr("Loop fade frames"), fade));
    // Three real editor columns. Settings scroll vertically; preview and
    // object list stay in sight while editing (like Player Animation Toolkit).
    auto *columns = new QHBoxLayout;
    columns->setSpacing(9);
    auto *selectorPanel = new QFrame(&dialog);
    selectorPanel->setObjectName(QStringLiteral("GGObjectCard"));
    selectorPanel->setFixedWidth(198);
    auto *selectorLayout = new QVBoxLayout(selectorPanel);
    selectorLayout->setContentsMargins(6, 6, 6, 6);
    auto *selectorTitle = new QLabel(tr("OBJECT TYPE"), selectorPanel);
    selectorTitle->setFont(headingFont);
    selectorLayout->addWidget(selectorTitle);
    auto *typeList = new QListWidget(selectorPanel);
    typeList->setObjectName(QStringLiteral("GGObjectTypes"));
    typeList->setSpacing(0);
    const QStringList icons = {QStringLiteral("◆"), QStringLiteral("✦"),
        QStringLiteral("▤"), QStringLiteral("⇆"), QStringLiteral("⇡"),
        QStringLiteral("⚑"), QStringLiteral("▣"), QStringLiteral("⚠"),
        QStringLiteral("▦"), QStringLiteral("✹"), QStringLiteral("♟"),
        QStringLiteral("⇥"), QStringLiteral("▣"), QStringLiteral("❀")};
    const QStringList titles = {tr("Decoration"), tr("Collectable"), tr("Moving platform"),
        tr("Conveyor"), tr("Spring"), tr("Trigger / Switch"), tr("Door / Blocker"),
        tr("Hazard zone"), tr("Breakable"), tr("Murder object"), tr("Stompable enemy"),
        tr("Goto World"), tr("Save Game Checkpoint"), tr("Particle Spawner")};
    // Both lists must match the canonical `type` combo. Use its label as a
    // release-build fallback if an object type is added without a short title.
    Q_ASSERT(icons.size() == type->count() && titles.size() == type->count());
    for (int n = 0; n < type->count(); ++n) {
        const QString icon = icons.value(n, QStringLiteral("◆"));
        const QString title = titles.value(n, type->itemText(n));
        auto *item = new QListWidgetItem(icon + QStringLiteral("   ") + title);
        item->setData(Qt::UserRole, type->itemData(n));
        item->setToolTip(type->itemText(n));
        item->setSizeHint(QSize(180, 43));
        typeList->addItem(item);
    }
    typeList->setCurrentRow(type->currentIndex());
    connect(typeList, &QListWidget::currentRowChanged, type,
            [type](int row) { if (row >= 0) type->setCurrentIndex(row); });
    connect(type, qOverload<int>(&QComboBox::currentIndexChanged), typeList,
            [typeList](int row) { if (typeList->currentRow() != row) typeList->setCurrentRow(row); });
    selectorLayout->addWidget(typeList, 1);
    auto *selectorHelp = new QLabel(tr("Only settings relevant to the selected object appear."), selectorPanel);
    selectorHelp->setObjectName(QStringLiteral("GGHelper"));
    selectorHelp->setWordWrap(true);
    selectorLayout->addWidget(selectorHelp);
    columns->addWidget(selectorPanel);

    auto *propertiesPanel = new QWidget(&dialog);
    auto *propertiesLayout = new QVBoxLayout(propertiesPanel);
    propertiesLayout->setContentsMargins(2, 2, 4, 2);
    propertiesLayout->setSpacing(7);
    for (const PropertyCard &card : {generalCard, visualCard, animationCard, collisionCard,
         collectCard, linkedCard, triggerCard, liftCard, conveyorCard, springCard, breakCard,
         enemyCard, particleCard, gotoCard, hazardCard,
         audioCollectCard, audioLiftCard, audioSpringCard, audioConveyorCard,
         audioBreakCard, audioHazardCard, audioOptionsCard}) {
        propertiesLayout->addWidget(card.panel);
    }
    propertiesLayout->addStretch(1);
    auto *propertiesScroll = new QScrollArea(&dialog);
    propertiesScroll->setWidgetResizable(true);
    propertiesScroll->setFrameShape(QFrame::NoFrame);
    propertiesScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    propertiesScroll->setWidget(propertiesPanel);
    columns->addWidget(propertiesScroll, 1);

    auto *previewPanel = new QFrame(&dialog);
    previewPanel->setObjectName(QStringLiteral("GGObjectCard"));
    previewPanel->setMinimumWidth(235);
    previewPanel->setMaximumWidth(300);
    auto *previewLayout = new QVBoxLayout(previewPanel);
    previewLayout->setContentsMargins(8, 9, 8, 9);
    previewLayout->setSpacing(9);
    auto *previewTitle = new QLabel(tr("LIVE PREVIEW"), previewPanel);
    previewTitle->setObjectName(QStringLiteral("GGSideSection"));
    previewLayout->addWidget(previewTitle);
    auto *spritePreview = new QLabel(previewPanel);
    spritePreview->setObjectName(QStringLiteral("GGPreviewImage"));
    spritePreview->setMinimumHeight(205);
    spritePreview->setAlignment(Qt::AlignCenter);
    previewLayout->addWidget(spritePreview);
    auto *playRow = new QHBoxLayout;
    playRow->setSpacing(5);
    const auto transportIcon = [this](int action) {
        QPixmap pix(16, 16);
        pix.fill(Qt::transparent);
        QPainter painter(&pix);
        painter.setPen(Qt::NoPen);
        painter.setBrush(m_theme.text);
        if (action == 0) {
            QPolygon triangle;
            triangle << QPoint(4, 2) << QPoint(13, 8) << QPoint(4, 14);
            painter.drawPolygon(triangle);
        } else if (action == 1) {
            painter.fillRect(3, 3, 4, 10, m_theme.text);
            painter.fillRect(9, 3, 4, 10, m_theme.text);
        } else {
            painter.fillRect(3, 3, 10, 10, m_theme.text);
        }
        return QIcon(pix);
    };
    auto *playButton = new QToolButton(previewPanel);
    auto *pauseButton = new QToolButton(previewPanel);
    auto *stopButton = new QToolButton(previewPanel);
    playButton->setIcon(transportIcon(0));
    pauseButton->setIcon(transportIcon(1));
    stopButton->setIcon(transportIcon(2));
    playButton->setToolTip(tr("Play animation"));
    pauseButton->setToolTip(tr("Pause on the current frame"));
    stopButton->setToolTip(tr("Stop and rewind to the first frame"));
    for (auto *button : {playButton, pauseButton, stopButton}) {
        button->setIconSize(QSize(16, 16));
        button->setFixedSize(32, 28);
    }
    playRow->addStretch();
    playRow->addWidget(playButton);
    playRow->addWidget(pauseButton);
    playRow->addWidget(stopButton);
    playRow->addStretch();
    previewLayout->addLayout(playRow);
    auto *spriteInfoTitle = new QLabel(tr("SPRITE INFO"), previewPanel);
    spriteInfoTitle->setObjectName(QStringLiteral("GGSideSection"));
    previewLayout->addWidget(spriteInfoTitle);
    auto *spriteInfo = new QLabel(previewPanel);
    spriteInfo->setObjectName(QStringLiteral("GGHelper"));
    spriteInfo->setWordWrap(true);
    previewLayout->addWidget(spriteInfo);
    auto *collisionTitle = new QLabel(tr("COLLISION PREVIEW — LIVE"), previewPanel);
    collisionTitle->setObjectName(QStringLiteral("GGSideSection"));
    previewLayout->addWidget(collisionTitle);
    auto *collisionPreview = new QLabel(previewPanel);
    collisionPreview->setObjectName(QStringLiteral("GGPreviewImage"));
    collisionPreview->setMinimumHeight(145);
    collisionPreview->setAlignment(Qt::AlignCenter);
    collisionPreview->setToolTip(tr("Stompable Enemy: red is the damaging body hitbox; "
                                   "green is the separate vulnerable hitbox for ABOVE / BELOW hits. "
                                   "Both follow the X/Y/width/height controls immediately."));
    previewLayout->addWidget(collisionPreview);
    // Visible, square-cornered key, immediately below the collision preview.
    // Only enemy objects need two differently coloured hitboxes.
    auto *collisionLegend = new QWidget(previewPanel);
    auto *legendLayout = new QHBoxLayout(collisionLegend);
    legendLayout->setContentsMargins(2, 0, 2, 0);
    legendLayout->setSpacing(10);
    auto *hurtLegend = new QLabel(tr("■ Red: danger"), collisionLegend);
    hurtLegend->setStyleSheet(QStringLiteral("QLabel { color: #ee5966; }"));
    auto *stompLegend = new QLabel(tr("■ Green: weak spot"), collisionLegend);
    stompLegend->setStyleSheet(QStringLiteral("QLabel { color: #40d690; }"));
    legendLayout->addWidget(hurtLegend);
    legendLayout->addWidget(stompLegend);
    legendLayout->addStretch(1);
    previewLayout->addWidget(collisionLegend);
    auto *collisionDimensions = new QFormLayout;
    collisionDimensions->setContentsMargins(2, 3, 2, 2);
    collisionDimensions->setSpacing(5);
    collisionDimensions->addRow(tr("Width"), quickValue(hitW));
    collisionDimensions->addRow(tr("Height"), quickValue(hitH));
    previewLayout->addLayout(collisionDimensions);
    previewLayout->addStretch(1);
    // Scroll the preview independently on shorter laptop screens.
    auto *previewScroll = new QScrollArea(&dialog);
    previewScroll->setFrameShape(QFrame::NoFrame);
    previewScroll->setWidgetResizable(true);
    previewScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    previewScroll->setMinimumWidth(288);
    previewScroll->setMaximumWidth(317);
    previewScroll->setWidget(previewPanel);
    columns->addWidget(previewScroll);
    layout.addLayout(columns, 1);

    QImage atlas = cachedImage(resolvedPath(old.path));
    if (atlas.format() == QImage::Format_Indexed8) {
        const QVector<QRgb> palette = activePalette(QStringLiteral("foreground"));
        if (palette.size() == 256)
            atlas.setColorTable(colourPreviewBank(palette, true, m_previewPaletteAlpha && m_previewPaletteAlpha->isChecked()));
    }
    // The picker uses this exact same palette-corrected sprite atlas as the
    // existing Game Object preview, including after Previous/Next object.
    const auto refreshDeathStartButton = [&, deathStartPicker, enemyDefeatFrame]() {
        const int cw = old.cellWidth > 0 ? qMin(old.cellWidth, atlas.width()) : atlas.width();
        const int ch = old.cellHeight > 0 ? qMin(old.cellHeight, atlas.height()) : atlas.height();
        const int cols = cw > 0 ? atlas.width() / cw : 0;
        const int rows = ch > 0 ? atlas.height() / ch : 0;
        const int index = enemyDefeatFrame->value();
        const bool canPreview = cols > 0 && rows > 0 && index >= 0 && index < cols * rows;
        deathStartPicker->setEnabled(cols > 0 && rows > 0);
        deathStartPicker->setText(canPreview
            ? tr("Choose... (frame %1)").arg(index)
            : tr("Choose from atlas..."));
        if (!canPreview) { deathStartPicker->setIcon(QIcon()); return; }
        const QImage frame = atlas.copy((index % cols) * cw, (index / cols) * ch, cw, ch);
        deathStartPicker->setIcon(QIcon(QPixmap::fromImage(frame.scaled(36, 36,
            Qt::KeepAspectRatio, Qt::FastTransformation))));
        deathStartPicker->setIconSize(QSize(36, 36));
    };
    connect(deathStartPicker, &QPushButton::clicked, &dialog,
            [this, &dialog, &atlas, &old, enemyDefeatFrame, enemyDefeatCount]() {
        const int cw = old.cellWidth > 0 ? qMin(old.cellWidth, atlas.width()) : atlas.width();
        const int ch = old.cellHeight > 0 ? qMin(old.cellHeight, atlas.height()) : atlas.height();
        const int selected = chooseDeathAtlasStart(&dialog, atlas, cw, ch,
            enemyDefeatFrame->value(), enemyDefeatCount->value(), m_theme.accent);
        if (selected >= -1) enemyDefeatFrame->setValue(selected); // -2 = Cancel
    });
    connect(enemyDefeatFrame, qOverload<int>(&QSpinBox::valueChanged), &dialog,
            [refreshDeathStartButton](int) { refreshDeathStartButton(); });
    refreshDeathStartButton();
    int previewFrame = 0;
    qint64 fadePreviewFrames = 0;
    int fadePreviewPercent = old.objectAlphaFadePercent;
    int fadeCanvasPercent = -1;
    QString fadeCanvasObject;
    bool previewPlaying = true;
    auto *previewTimer = new QTimer(&dialog);
    // Keep preview linked to whichever object is currently selected; the
    // dialog stays OPEN while the previous/next arrows reload its controls.
    const auto updatePreview = [this, &previewFrame, &atlas, &old, &draftSpriteStamp, animated,
                                first, count, mode, type, hitW, hitH,
                                enemyStompX, enemyStompY, enemyStompW, enemyStompH,
                                objectFlipX, objectFlipY, objectFadeSlider,
                                fadeAnimate, fadeLow, fadeHigh, fadeStep, fadeDelay, fadePingpong,
                                &fadePreviewPercent, &fadePreviewFrames,
                                spritePreview, collisionPreview,
                                collisionLegend, spriteInfo]() {
        const int cw = atlas.isNull() ? 1 :
            (old.cellWidth > 0 ? qMin(old.cellWidth, atlas.width()) : atlas.width());
        const int ch = atlas.isNull() ? 1 :
            (old.cellHeight > 0 ? qMin(old.cellHeight, atlas.height()) : atlas.height());
        const int cols = atlas.isNull() ? 1 : qMax(1, atlas.width() / qMax(1, cw));
        const int rows = atlas.isNull() ? 1 : qMax(1, atlas.height() / qMax(1, ch));
        const int available = cols * rows;
        const int from = animated->isChecked() ? first->value() : old.frame;
        const int countFrames = animated->isChecked() ? qMax(1, count->value()) : 1;
        int frameInClip = 0;
        if (animated->isChecked() && countFrames > 1) {
            const QString playMode = mode->currentData().toString();
            if (playMode == QStringLiteral("once"))
                frameInClip = qMin(previewFrame, countFrames - 1);
            else if (playMode == QStringLiteral("pingpong")) {
                const int cycle = 2 * countFrames - 2;
                const int phase = previewFrame % cycle;
                frameInClip = phase < countFrames ? phase : cycle - phase;
            } else frameInClip = previewFrame % countFrames;
        }
        const int selected = qBound(0, from + frameInClip, available - 1);
        QImage frame = atlas.isNull() ? QImage() :
            atlas.copy((selected % cols) * cw, (selected / cols) * ch, cw, ch);
        if (draftSpriteStamp.active()) {
            QString stampError;
            SidboxPpb::Picture sheet;
            if (SidboxPpb::read(resolvedPath(draftSpriteStamp.sourcePath), &sheet, &stampError))
                frame = draftSpriteStamp.compose(sheet.indexed, &stampError);
        }
        if (!frame.isNull() && (objectFlipX->isChecked() || objectFlipY->isChecked())) {
            Qt::Orientations flipDirections;
            if (objectFlipX->isChecked()) flipDirections |= Qt::Horizontal;
            if (objectFlipY->isChecked()) flipDirections |= Qt::Vertical;
            frame = frame.flipped(flipDirections);
        }
        fadePreviewPercent = fadeAnimate->isChecked()
            ? bobAnimatedFade(fadeLow->value(), fadeHigh->value(), fadeStep->value(),
                              fadeDelay->value(), fadePingpong->isChecked(), fadePreviewFrames)
            : objectFadeSlider->value();
        if (!frame.isNull() && fadePreviewPercent > 0)
            frame = patternedBobPreview(frame, fadePreviewPercent,
                                        100, old.x, old.y);
        const bool enemyPreview =
            type->currentData().toString() == QStringLiteral("enemy");
        collisionLegend->setVisible(enemyPreview);
        const auto makeCanvas = [this, frame, hitW, hitH, enemyPreview,
                                 enemyStompX, enemyStompY, enemyStompW, enemyStompH]
                                (int width, int height, bool showCollision) {
            QPixmap canvas(width, height);
            canvas.fill(m_theme.windowBackground);
            QPainter painter(&canvas);
            painter.setPen(QPen(m_theme.border, 1));
            for (int x = 0; x < width; x += 20) painter.drawLine(x, 0, x, height);
            for (int y = 0; y < height; y += 20) painter.drawLine(0, y, width, y);
            if (!frame.isNull()) {
                if (!showCollision || !enemyPreview) {
                    // Preserve the existing integer nearest-neighbour sprite
                    // preview and single-hitbox rendering for other objects.
                    const int maxW = width - 28;
                    const int maxH = height - 28;
                    const int factor = qMax(1, qMin(maxW / qMax(1, frame.width()),
                                                     maxH / qMax(1, frame.height())));
                    const int w = qMin(maxW, frame.width() * factor);
                    const int h = qMin(maxH, frame.height() * factor);
                    const QRect destination((width-w)/2, (height-h)/2, w, h);
                    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
                    painter.drawImage(destination, frame);
                    if (showCollision) {
                        const double sx = double(destination.width()) / qMax(1, frame.width());
                        const double sy = double(destination.height()) / qMax(1, frame.height());
                        painter.setPen(QPen(m_theme.accent, 2, Qt::DashLine));
                        painter.drawRect(QRectF(destination.x(), destination.y(),
                            qMin(double(destination.width()), hitW->value()*sx),
                            qMin(double(destination.height()), hitH->value()*sy)));
                    }
                } else {
                    // Stompable enemy: world-space body and vulnerable box.
                    // Negative X/Y offsets and wider boxes are not clipped.
                    const QRectF sprite(0, 0, frame.width(), frame.height());
                    const QRectF body(0, 0, hitW->value(), hitH->value());
                    // These offsets are relative to the BODY origin and DO NOT
                    // change when the enemy sprite is flipped in the runtime.
                    const QRectF stomp(enemyStompX->value(), enemyStompY->value(),
                        enemyStompW->value() == 0 ? hitW->value() : enemyStompW->value(),
                        enemyStompH->value());
                    const QRectF contents = sprite.united(body).united(stomp);
                    const double scale = qMin((width - 28.0) / qMax(1.0, contents.width()),
                                               (height - 28.0) / qMax(1.0, contents.height()));
                    const double originX = (width - contents.width() * scale) / 2.0
                                           - contents.left() * scale;
                    const double originY = (height - contents.height() * scale) / 2.0
                                           - contents.top() * scale;
                    const auto mapHitbox = [originX, originY, scale](const QRectF &r) {
                        return QRectF(originX + r.x() * scale,
                                      originY + r.y() * scale,
                                      r.width() * scale, r.height() * scale);
                    };
                    painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
                    painter.drawImage(mapHitbox(sprite), frame);
                    // RED = the damaging body. GREEN = the stompable area.
                    // Draw green last so it remains visible even where the
                    // two zones overlap. Outlines stay two screen pixels wide.
                    QPen hurtPen(QColor(238, 89, 102), 2, Qt::SolidLine);
                    hurtPen.setCosmetic(true);
                    painter.setPen(hurtPen);
                    painter.setBrush(QColor(238, 89, 102, 58));
                    painter.drawRect(mapHitbox(body));
                    QPen stompPen(QColor(64, 214, 144), 2, Qt::DashLine);
                    stompPen.setCosmetic(true);
                    painter.setPen(stompPen);
                    painter.setBrush(QColor(64, 214, 144, 68));
                    painter.drawRect(mapHitbox(stomp));
                }
            } else {
                painter.setPen(m_theme.mutedText);
                painter.drawText(canvas.rect(), Qt::AlignCenter, tr("No sprite preview"));
            }
            return canvas;
        };
        spritePreview->setPixmap(makeCanvas(255, 205, false));
        collisionPreview->setPixmap(makeCanvas(255, 145, true));
        spriteInfo->setText(tr("Sprite: %1\nCell: %2 × %3 px  |  Atlas frames: %4\nPreview frame: %5")
            .arg(QFileInfo(old.path).fileName()).arg(cw).arg(ch)
            .arg(available).arg(selected + 1)
            + (fadePreviewPercent > 0 || fadeAnimate->isChecked()
                ? tr("\n4×4 patterned fade: %1% (editor approximation)")
                    .arg(fadePreviewPercent) : QString()));
    };
    auto *fadePreviewTimer = new QTimer(&dialog);
    fadePreviewTimer->setInterval(20);
    connect(fadePreviewTimer, &QTimer::timeout, &dialog, [=, &fadePreviewFrames]() {
        ++fadePreviewFrames;
        if (fadeAnimate->isChecked() &&
            bobAnimatedFade(fadeLow->value(), fadeHigh->value(), fadeStep->value(),
                            fadeDelay->value(), fadePingpong->isChecked(), fadePreviewFrames)
                != fadePreviewPercent)
            updatePreview();
    });
    connect(previewTimer, &QTimer::timeout, &dialog, [=, &previewFrame]() {
        ++previewFrame;
        updatePreview();
    });
    const auto refreshTimer = [=, &previewPlaying]() {
        previewTimer->setInterval(qMax(1, ticks->value()) * 20);
        if (animated->isChecked() && previewPlaying) previewTimer->start();
        else previewTimer->stop();
        if (fadeAnimate->isChecked() && previewPlaying) fadePreviewTimer->start();
        else fadePreviewTimer->stop();
        updatePreview();
    };
    connect(playButton, &QToolButton::clicked, &dialog, [=, &previewPlaying]() {
        previewPlaying = true;
        refreshTimer();
    });
    connect(pauseButton, &QToolButton::clicked, &dialog, [=, &previewPlaying]() {
        previewPlaying = false;
        previewTimer->stop();
        fadePreviewTimer->stop();
    });
    connect(stopButton, &QToolButton::clicked, &dialog,
            [=, &previewPlaying, &previewFrame, &fadePreviewFrames]() {
        previewPlaying = false;
        previewTimer->stop();
        fadePreviewTimer->stop();
        previewFrame = 0;
        fadePreviewFrames = 0;
        updatePreview();
    });
    connect(animated, &QCheckBox::toggled, &dialog, [=](bool) { refreshTimer(); });
    connect(fadeAnimate, &QCheckBox::toggled, &dialog, [=](bool) { refreshTimer(); });
    for (QSpinBox *setting : {fadeLow, fadeHigh, fadeStep, fadeDelay})
        connect(setting, qOverload<int>(&QSpinBox::valueChanged), &dialog,
                [=](int) { updatePreview(); });
    connect(fadePingpong, &QCheckBox::toggled, &dialog, [=](bool) { updatePreview(); });
    connect(objectFlipX, &QCheckBox::toggled, &dialog, [=](bool) { updatePreview(); });
    connect(objectFlipY, &QCheckBox::toggled, &dialog, [=](bool) { updatePreview(); });
    // Update the modal previews AND the existing canvas item without saving.
    // Cancel restores the saved percentage, and previous/next commits retain
    // the normal per-object editing behaviour.
    const auto previewFadeOnCanvas = [this, &old, &fadePreviewPercent,
                                      &fadeCanvasPercent, &fadeCanvasObject]() {
        if (fadeCanvasPercent == fadePreviewPercent && fadeCanvasObject == old.id)
            return;
        for (int i = 0; i < m_resources.size() && i < m_sceneItems.size(); ++i) {
            if (m_resources.at(i).id != old.id) continue;
            auto *image = dynamic_cast<QGraphicsPixmapItem *>(m_sceneItems.at(i));
            if (!image) break;
            Resource draft = m_resources.at(i);
            draft.frame = image->data(1).toInt();
            draft.objectAlphaFadePercent = fadePreviewPercent;
            const QImage base = resourcePreview(draft);
            if (!base.isNull()) {
                image->setPixmap(QPixmap::fromImage(patternedBobPreview(base,
                    draft.objectAlphaFadePercent, draft.scale, draft.x, draft.y)));
                image->setScale(draft.objectAlphaFadePercent > 0 ? 1.0 : draft.scale / 100.0);
                image->setShapeMode(draft.objectAlphaFadePercent > 0
                    ? QGraphicsPixmapItem::BoundingRectShape
                    : QGraphicsPixmapItem::MaskShape);
                fadeCanvasPercent = fadePreviewPercent;
                fadeCanvasObject = old.id;
            }
            break;
        }
    };
    connect(objectFadeSlider, &QSlider::valueChanged, &dialog,
            [=](int) { updatePreview(); previewFadeOnCanvas(); });
    connect(fadePreviewTimer, &QTimer::timeout, &dialog,
            [=]() { previewFadeOnCanvas(); });
    connect(fadeAnimate, &QCheckBox::toggled, &dialog,
            [=](bool) { updatePreview(); previewFadeOnCanvas(); });
    for (QSpinBox *setting : {fadeLow, fadeHigh, fadeStep, fadeDelay})
        connect(setting, qOverload<int>(&QSpinBox::valueChanged), &dialog,
                [=](int) { updatePreview(); previewFadeOnCanvas(); });
    connect(fadePingpong, &QCheckBox::toggled, &dialog,
            [=](bool) { updatePreview(); previewFadeOnCanvas(); });
    connect(stopButton, &QToolButton::clicked, &dialog,
            [=]() { previewFadeOnCanvas(); });
    connect(mode, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [=](int) { updatePreview(); });
    for (QSpinBox *spin : {first, count, ticks, hitW, hitH})
        connect(spin, qOverload<int>(&QSpinBox::valueChanged), &dialog,
                [=](int) { refreshTimer(); });
    // The collision preview must react to *every* vulnerable hitbox slider,
    // not merely the sprite/body size. No Save, rebuild, or preview restart.
    for (QSpinBox *spin : {enemyStompX, enemyStompY, enemyStompW, enemyStompH})
        connect(spin, qOverload<int>(&QSpinBox::valueChanged), &dialog,
                [=](int) { updatePreview(); });
    connect(type, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [=](int) { updatePreview(); });
    refreshTimer();

    auto enableFields = [=]() {
        const QString behaviour = type->currentData().toString();
        const bool isObject = behaviour != QStringLiteral("decoration");
        // Hazard Zones use the Advanced Platformer tilemap event API.
        // They are intangible sensors; hitW/hitH define the lethal area.
        pickup->setEnabled(behaviour == QStringLiteral("collectable"));
        value->setEnabled(behaviour == QStringLiteral("collectable"));
        pickupShowInventory->setEnabled(behaviour == QStringLiteral("collectable"));
        pickupShowHud->setEnabled(behaviour == QStringLiteral("collectable"));
        pickupPersistent->setEnabled(behaviour == QStringLiteral("collectable"));
        const bool isTrigger = behaviour == QStringLiteral("trigger");
        const bool isGoto = behaviour == QStringLiteral("goto_world");
        gotoWorld->setEnabled(isGoto);
        gotoActivation->setEnabled(isGoto);
        gotoStart->setEnabled(isGoto);
        const bool isKey = behaviour == QStringLiteral("collectable") && pickup->currentData().toInt() == 3;
        initiallyActive->setEnabled(isObject);
        initiallyActive->setVisible(isObject && behaviour != QStringLiteral("collectable"));
        hiddenCollectable->setEnabled(behaviour == QStringLiteral("collectable"));
        targetObject->setEnabled(isKey || behaviour == QStringLiteral("enemy"));
        const bool oldStyleLinks = isKey || behaviour == QStringLiteral("enemy");
        targetObject->setVisible(oldStyleLinks);
        targetAction->setVisible(oldStyleLinks);
        targetVisibilityHint->setVisible(oldStyleLinks);
        linkedActionRows->setVisible(isTrigger);
        actionRowControls->setVisible(isTrigger);
        linkedActionsHint->setVisible(isTrigger);
        targetAction->setEnabled(oldStyleLinks);
        // Hide associated QFormLayout labels alongside the controls.
        for (QWidget *field : {static_cast<QWidget *>(targetObject),
                               static_cast<QWidget *>(targetAction),
                               static_cast<QWidget *>(targetVisibilityHint)})
            if (QWidget *label=linkedCard.form->labelForField(field))
                label->setVisible(oldStyleLinks);
        if (QWidget *label=linkedCard.form->labelForField(linkedActionRows))
            label->setVisible(isTrigger);
        // updateItemInteraction() owns triggerPress enabled state so an
        // inventory requirement cannot be accidentally overridden here.
        checkpointSlot->setVisible(behaviour == QStringLiteral("save_checkpoint"));
        checkpointHelp->setVisible(behaviour == QStringLiteral("save_checkpoint"));
        if (QWidget *slotLabel=triggerCard.form->labelForField(checkpointSlot))
            slotLabel->setVisible(behaviour == QStringLiteral("save_checkpoint"));
        triggerOneShot->setEnabled(isTrigger);
        triggerOneShot->setVisible(isTrigger);
        interactItem->setEnabled(isTrigger || behaviour == QStringLiteral("save_checkpoint"));
        // A required item disables touch/FIRE2 activation for checkpoints too.
        updateItemInteraction();
        musicAction->setEnabled(isTrigger);
        musicTrack->setEnabled(isTrigger && musicAction->currentData().toString() == QStringLiteral("play"));
        musicAction->setVisible(isTrigger);
        musicTrack->setVisible(isTrigger);
        for (QWidget *field : {static_cast<QWidget *>(musicAction), static_cast<QWidget *>(musicTrack)})
            if (QWidget *label=triggerCard.form->labelForField(field))
                label->setVisible(isTrigger);
        hitW->setEnabled(isObject); hitH->setEnabled(isObject);
        conveyor->setEnabled(behaviour == QStringLiteral("conveyor"));
        spring->setEnabled(behaviour == QStringLiteral("spring"));
        springLaunchX->setEnabled(behaviour == QStringLiteral("spring"));
        springTouch->setEnabled(behaviour == QStringLiteral("spring"));
        springSlide->setEnabled(behaviour == QStringLiteral("spring"));
        springJumpBoost->setEnabled(behaviour == QStringLiteral("spring"));
        const bool soundsForInteraction = (isTrigger || behaviour == QStringLiteral("save_checkpoint")) &&
            !interactItem->currentData().toString().isEmpty();
        sfxInteractWrong->setEnabled(soundsForInteraction);
        sfxInteractSuccess->setEnabled(soundsForInteraction);
        sfxInteractCancel->setEnabled(soundsForInteraction);
        interactDialogue->setEnabled(soundsForInteraction);
        interactDialogueMode->setEnabled(soundsForInteraction && interactDialogue->currentData().toInt()>=0);
        interactWrongDialogue->setEnabled(soundsForInteraction);
        interactWrongDialogueMode->setEnabled(soundsForInteraction && interactWrongDialogue->currentData().toInt()>=0);
        interactReward->setEnabled(soundsForInteraction);
        interactRewardCount->setEnabled(soundsForInteraction && !interactReward->currentData().toString().isEmpty());
        interactStat->setEnabled(soundsForInteraction);
        interactStatDelta->setEnabled(soundsForInteraction && interactStat->currentData().toString()!=QStringLiteral("none"));
        activeStateFrame->setEnabled(isObject && behaviour!=QStringLiteral("collectable"));
        inactiveStateFrame->setEnabled(isObject && behaviour!=QStringLiteral("collectable"));
        sfxPickup->setEnabled(behaviour == QStringLiteral("collectable"));
        sfxRespawn->setEnabled(behaviour == QStringLiteral("collectable"));
        collectOnce->setEnabled(behaviour == QStringLiteral("collectable"));
        respawn->setEnabled(behaviour == QStringLiteral("collectable") && !collectOnce->isChecked());
        sfxStart->setEnabled(behaviour == QStringLiteral("lift"));
        sfxMove->setEnabled(behaviour == QStringLiteral("lift"));
        sfxStop->setEnabled(behaviour == QStringLiteral("lift"));
        sfxReverse->setEnabled(behaviour == QStringLiteral("lift"));
        sfxSpring->setEnabled(behaviour == QStringLiteral("spring"));
        sfxAmbient->setEnabled(behaviour == QStringLiteral("conveyor"));
        sfxBreakHit->setEnabled(behaviour == QStringLiteral("breakable") || behaviour == QStringLiteral("enemy"));
        sfxBreakBounce->setEnabled((behaviour == QStringLiteral("enemy") && enemyBounce->isChecked()) ||
            (behaviour == QStringLiteral("breakable") && !breakTouch->isChecked() && breakBounce->isChecked()));
        sfxBreakFinish->setEnabled(behaviour == QStringLiteral("breakable") || behaviour == QStringLiteral("enemy"));
        sfxHazardHit->setEnabled(behaviour == QStringLiteral("hazard"));
        sfxHazardBounce->setEnabled(behaviour == QStringLiteral("hazard") && hazardKick->isChecked());
        sfxHazardAmbient->setEnabled(behaviour == QStringLiteral("hazard"));
        radius->setEnabled(isObject);
        fade->setEnabled(isObject);
        spline->setEnabled(isObject);
        splineDelay->setEnabled(isObject && !spline->currentData().toString().isEmpty());
        animated->setEnabled(isObject);
        for (QWidget *w : {static_cast<QWidget *>(first), static_cast<QWidget *>(count),
                           static_cast<QWidget *>(ticks), static_cast<QWidget *>(mode)})
            w->setEnabled(isObject && animated->isChecked());
        // Hide irrelevant cards, rather than leaving disabled controls stacked
        // in front of the user. No values are reset by these visibility rules.
        const bool isCollect = behaviour == QStringLiteral("collectable");
        const bool isLift = behaviour == QStringLiteral("lift");
        const bool isConveyor = behaviour == QStringLiteral("conveyor");
        const bool isSpring = behaviour == QStringLiteral("spring");
        const bool isBreak = behaviour == QStringLiteral("breakable");
        const bool isHazard = behaviour == QStringLiteral("hazard");
        const bool isEnemy = behaviour == QStringLiteral("enemy");
        generalCard.panel->setVisible(true);
        visualCard.panel->setVisible(true);
        animationCard.panel->setVisible(isObject && animated->isChecked());
        collisionCard.panel->setVisible(isObject && behaviour != QStringLiteral("particle_emitter"));
        collectCard.panel->setVisible(isCollect);
        linkedCard.panel->setVisible(isTrigger || isKey || isEnemy);
        triggerCard.panel->setVisible(isTrigger || behaviour == QStringLiteral("save_checkpoint"));
        liftCard.panel->setVisible(false); // sound controls are in Audio Events
        conveyorCard.panel->setVisible(isConveyor);
        springCard.panel->setVisible(isSpring);
        breakCard.panel->setVisible(isBreak);
        hazardCard.panel->setVisible(isHazard || isEnemy);
        enemyCard.panel->setVisible(isEnemy);
        const bool isParticle = behaviour == QStringLiteral("particle_emitter");
        particleCard.panel->setVisible(isParticle);
        particlePreviewDock->setVisible(isParticle && m_showParticlePreview &&
            m_showParticlePreview->isChecked());
        for (QWidget *w : {static_cast<QWidget *>(particleFadeNote),
                           static_cast<QWidget *>(particleFadeEnable),
                           static_cast<QWidget *>(particlePlayerMix),
                           static_cast<QWidget *>(particleFadeIn),
                           static_cast<QWidget *>(particleFadeOut),
                           static_cast<QWidget *>(particleFadeSpeed),
                           particleFadeInRow, particleFadeOutRow, particleFadeSpeedRow,
                           static_cast<QWidget *>(particleFadeInLabel),
                           static_cast<QWidget *>(particleFadeOutLabel),
                           static_cast<QWidget *>(particleFadeSpeedLabel)})
            if (w) w->setVisible(isParticle);
        for (QWidget *w : {static_cast<QWidget *>(particleFadeIn),
                           static_cast<QWidget *>(particleFadeOut),
                           static_cast<QWidget *>(particleFadeSpeed)})
            w->setEnabled(isParticle && particleFadeEnable->isChecked());
        particlePlayerMix->setEnabled(isParticle && !behindTiles->isChecked());
        gotoCard.panel->setVisible(isGoto);
        audioCollectCard.panel->setVisible(isCollect);
        audioLiftCard.panel->setVisible(isLift);
        audioSpringCard.panel->setVisible(isSpring);
        audioConveyorCard.panel->setVisible(isConveyor);
        audioBreakCard.panel->setVisible(isBreak || isEnemy);
        audioHazardCard.panel->setVisible(isHazard);
        audioOptionsCard.panel->setVisible(isCollect || isLift || isSpring ||
            isConveyor || isBreak || isHazard || isEnemy || isTrigger);
    };
    connect(interactReward, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    connect(interactStat, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    connect(interactItem, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    connect(type, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    connect(spline, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    connect(animated, &QCheckBox::toggled, &dialog,
            [enableFields](bool) { enableFields(); });
    connect(breakTouch, &QCheckBox::toggled, &dialog,
            [enableFields](bool) { enableFields(); });
    connect(breakBounce, &QCheckBox::toggled, &dialog,
            [enableFields](bool) { enableFields(); });
    connect(enemyBounce, &QCheckBox::toggled, &dialog,
            [enableFields](bool) { enableFields(); });
    connect(hazardKick, &QCheckBox::toggled, &dialog,
            [enableFields](bool) { enableFields(); });
    connect(pickup, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    connect(musicAction, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    enableFields();
    // Stage 5.148: the world canvas previews unsaved particle settings while
    // the Properties dialog is open. Cancel discards this temporary draft.
    const auto updateParticleDraft = [this, &old, &index,
        &particlePreviewLastBounds, &particlePreviewNeedsFit, type, behindTiles,
        particleW, particleH, particleCount, particleInterval, particlePrepopulate, particleLifetime,
        particleWind, particleFall, particleGravity, particleFlutter,
        particlePreset, particleSwirlRadius, particleSwirlSpeed, particlePlayerMix, particleFadeEnable, particleFadeIn, particleFadeOut,
        particleFadeSpeed]() {
        Resource draft = old;
        draft.objectType = type->currentData().toString();
        draft.drawBehindTiles = behindTiles->isChecked();
        draft.particleAreaW = particleW->value();
        draft.particleAreaH = particleH->value();
        draft.particleCount = particleCount->value();
        draft.particleInterval = particleInterval->value();
        draft.particlePrepopulate = particlePrepopulate->isChecked();
        draft.particleLifetime = particleLifetime->value();
        draft.particleWind = particleWind->value();
        draft.particleFall = particleFall->value();
        draft.particleGravity = particleGravity->value();
        draft.particleFlutter = particleFlutter->value();
        draft.particlePreset = particlePreset->currentData().toString();
        draft.particleSwirlRadius = particleSwirlRadius->value();
        draft.particleSwirlSpeed = particleSwirlSpeed->value();
        draft.particlePlayerLayerMix = particlePlayerMix->isChecked();
        draft.particleFadeEnabled = particleFadeEnable->isChecked();
        draft.particleFadeIn = particleFadeIn->value();
        draft.particleFadeOut = particleFadeOut->value();
        draft.particleFadeSpeed = particleFadeSpeed->value();
        setParticlePreviewDraft(index, draft);
        const QRectF bounds(qreal(draft.x) - 24, qreal(draft.y) - 24,
            qMax(240, draft.particleAreaW + 48), qMax(160, draft.particleAreaH + 48));
        if (bounds != particlePreviewLastBounds) {
            particlePreviewLastBounds = bounds;
            particlePreviewNeedsFit = true;
        }
    };
    for (QSpinBox *field : {particleW, particleH, particleCount, particleInterval,
             particleLifetime, particleWind, particleFall, particleGravity,
             particleFlutter, particleSwirlRadius, particleSwirlSpeed,
             particleFadeIn, particleFadeOut, particleFadeSpeed})
        connect(field, qOverload<int>(&QSpinBox::valueChanged), &dialog,
                [updateParticleDraft](int) { updateParticleDraft(); });
    connect(particlePreset, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
        [updateParticleDraft](int) { updateParticleDraft(); });
    for (QCheckBox *field : {behindTiles, particlePlayerMix, particleFadeEnable, particlePrepopulate})
        connect(field, &QCheckBox::toggled, &dialog,
                [updateParticleDraft](bool) { updateParticleDraft(); });
    connect(type, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [updateParticleDraft](int) { updateParticleDraft(); });
    updateParticleDraft();
    // Stage 5.136: use the Adventure Editor's existing dependency colours on
    // controls whose value can be ignored unless another setting is active.
    for (QWidget *guarded : {static_cast<QWidget *>(interactRadius),
                             static_cast<QWidget *>(interactConsume),
                             static_cast<QWidget *>(triggerPress),
                             static_cast<QWidget *>(triggerDrop),
                             static_cast<QWidget *>(interactDialogue),
                             static_cast<QWidget *>(interactDialogueMode),
                             static_cast<QWidget *>(interactWrongDialogue),
                             static_cast<QWidget *>(interactWrongDialogueMode),
                             static_cast<QWidget *>(interactReward),
                             static_cast<QWidget *>(interactRewardCount),
                             static_cast<QWidget *>(interactStat),
                             static_cast<QWidget *>(interactStatDelta),
                             static_cast<QWidget *>(breakRewardImpulse),
                             static_cast<QWidget *>(breakRewardVx),
                             static_cast<QWidget *>(breakRewardVy),
                             static_cast<QWidget *>(enemyRewardImpulse),
                             static_cast<QWidget *>(enemyRewardXField),
                             static_cast<QWidget *>(enemyRewardYField),
                             static_cast<QWidget *>(enemyRoamSpeed),
                             static_cast<QWidget *>(enemyStepHeight),
                             static_cast<QWidget *>(enemyRoamLeft)}) {
        guarded->setProperty("adventureGuard", true);
        guarded->style()->unpolish(guarded);
        guarded->style()->polish(guarded);
    }
    // These are created after the World Editor: the QApplication-wide
    // palette/QSS also styles their popup lists without per-dialog copies.
    for (QComboBox *combo : dialog.findChildren<QComboBox *>()) {
        combo->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
        combo->setMinimumContentsLength(14);
        combo->setMinimumWidth(0);
        combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    }
    const auto commitObject = [&]() -> bool {
    const QString newType = type->currentData().toString();
    if (newType == QStringLiteral("enemy") && enemyRoam->isChecked() && !m_tilemapEnabled) {
        QMessageBox::warning(this, tr("Enemy Patrol"),
            tr("Walk on tilemap requires an Advanced Platformer tilemap. "
               "Use a spline or disable tilemap roaming."));
        return false;
    }
    if (newType == QStringLiteral("deathzone") && !m_tilemapEnabled) {
        QMessageBox::warning(this, tr("Game Object"),
            tr("Hazard Zones require an Advanced Platformer tilemap. "
               "Enable a tilemap in the Game Designer before choosing this behaviour."));
        return false;
    }
    if (newType != QStringLiteral("decoration") &&
        (old.path.isEmpty() || old.scale != 100 ||
         QFileInfo(resolvedPath(old.path)).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive))) {
        QMessageBox::warning(this, tr("Game Object"),
            tr("Game objects require a PPB sprite at 100%% scale. "
               "Please assign a PPB and set the sprite scale to 100 first."));
        return false;
    }
    if (newType == QStringLiteral("goto_world") && gotoWorld->currentData().toString().isEmpty()) {
        QMessageBox::warning(this, tr("Goto World"),
            tr("Choose another world in this project before saving this door."));
        return false;
    }
    // Guard against treating a Trigger like an NPC. A Trigger's linked action
    // commits BEFORE the dialogue starts, so choices cannot veto that action.
    if (newType == QStringLiteral("trigger") &&
        !interactItem->currentData().toString().isEmpty()) {
        const int dialogueId=interactDialogue->currentData().toInt();
        if (dialogueId>=0 && dialogueId<interactionNodes.size() &&
            interactDialogueMode->currentData().toString()==QStringLiteral("conversation") &&
            (dialogueId!=old.interactDialogueNode || old.interactDialogueMode!=QStringLiteral("conversation"))) {
            int choiceCount=0;
            for(const QJsonValue &v:interactionNodes.at(dialogueId).toObject().value(QStringLiteral("choices")).toArray())
                if(!v.toObject().value(QStringLiteral("text")).toString().trimmed().isEmpty()) ++choiceCount;
            if(choiceCount && QMessageBox::question(&dialog,tr("Dialogue choices on a Trigger"),
                tr("This dialogue has %1 player choice(s). The Trigger's item check, linked object action "
                   "and any item consumption are already completed BEFORE these choices appear.\n\n"
                   "If a choice should decide whether the object moves or unlocks, configure an Adventure NPC instead. "
                   "For text-only dialogue, choose 'Single message' or 'Message sequence'.\n\n"
                   "Keep the full conversation anyway?").arg(choiceCount),
                QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)
                return false;
        }
        const int wrongDialogueId=interactWrongDialogue->currentData().toInt();
        if(wrongDialogueId>=0 && wrongDialogueId<interactionNodes.size() &&
            interactWrongDialogueMode->currentData().toString()==QStringLiteral("conversation") &&
            (wrongDialogueId!=old.interactWrongDialogueNode ||
             old.interactWrongDialogueMode!=QStringLiteral("conversation"))) {
            int choiceCount=0;
            for(const QJsonValue &v:interactionNodes.at(wrongDialogueId).toObject()
                    .value(QStringLiteral("choices")).toArray())
                if(!v.toObject().value(QStringLiteral("text")).toString().trimmed().isEmpty()) ++choiceCount;
            if(choiceCount && QMessageBox::question(&dialog,tr("Wrong-item dialogue actions"),
                tr("This wrong-item dialogue has %1 choice(s) with potentially active inventory, NPC "
                   "or quest effects. The Trigger will NOT open or consume the wrong item, but a "
                   "deliberate dialogue-choice action can still change game state.\n\n"
                   "Choose Message sequence for text-only responses. Keep full conversation?" )
                   .arg(choiceCount), QMessageBox::Yes|QMessageBox::No,QMessageBox::No)!=QMessageBox::Yes)
                return false;
        }
    }
    if (newType==QStringLiteral("trigger")) {
        // Every linked disable can conceal its target. Warn once per newly
        // configured disappearing target, including additional actions.
        for (const Resource::LinkedAction &link : currentLinks()) {
            if (link.action!=QStringLiteral("disable")) continue;
            for (const Resource &candidate : m_resources) {
                if (candidate.id!=link.objectId) continue;
                if (candidate.inactiveStateFrame>=0) break;
                bool alreadyLinked=(old.targetObjectId==link.objectId &&
                                    old.targetAction==QStringLiteral("disable"));
                for (const Resource::LinkedAction &previous : old.triggerExtraActions)
                    if (previous.objectId==link.objectId && previous.action==QStringLiteral("disable"))
                        alreadyLinked=true;
                if (!alreadyLinked && QMessageBox::question(&dialog,
                    tr("Linked object will disappear"),
                    tr("Disabling '%1' removes collision AND hides its sprite because "
                       "its INACTIVE state frame is -1. Configure an INACTIVE frame "
                       "on that object if you want it to remain visible. Keep hiding it?")
                        .arg(candidate.name),QMessageBox::Yes|QMessageBox::No,
                        QMessageBox::No)!=QMessageBox::Yes) return false;
                break;
            }
        }
    }
    // Validate the draft BEFORE adding to the undo history or mutating the
    // actual object. A missing sheet cannot partially commit an object.
    Resource stamped = old;
    stamped.spriteStamp = draftSpriteStamp;
    if (stamped.spriteStamp.active()) {
        QString stampError;
        if (!updateSpriteStamp(stamped, &stampError)) {
            QMessageBox::warning(&dialog, tr("Sprite Stamp"), stampError);
            return false;
        }
    } else if (old.spriteStamp.active()) {
        stamped.path = old.spriteStamp.sourcePath;
        stamped.cellWidth = 8; stamped.cellHeight = 8; stamped.frame = 0;
    }
    // A checked Inventory option should actually work without forcing a
    // second visit to Adventure Editor. Existing item definitions (and their
    // puzzle dependencies, capacities and icons) are NEVER modified.
    QJsonArray inventoryDefinitions = m_adventure.value(QStringLiteral("items")).toArray();
    bool createInventoryDefinition = false;
    if (newType == QStringLiteral("collectable") && pickupShowInventory->isChecked()) {
        const int selectedKind = pickup->currentData().toInt();
        bool found = false;
        for (const QJsonValue &entry : inventoryDefinitions)
            if (entry.toObject().value(QStringLiteral("pickupKind")).toInt() == selectedKind) {
                found = true; break;
            }
        if (!found) {
            if (inventoryDefinitions.size() >= 64) {
                QMessageBox::warning(&dialog, tr("Inventory full"),
                    tr("The Adventure Inventory has 64 item types already. Remove an unused type or link an existing item to this pickup type before enabling Show in Inventory."));
                return false;
            }
            createInventoryDefinition = true;
        }
    }
    // The Adventure definition and the project-owned Player Inventory are two
    // different files. Offer the second step, never silently rewrite .sbpi.
    const QDir playerProject(QFileInfo(m_filePath).absolutePath());
    QJsonObject playerProfile;
    bool appendPlayerItem = false;
    QString playerItemName;
    if (newType == QStringLiteral("collectable") && pickupShowInventory->isChecked()) {
        for (const QJsonValue &entry : inventoryDefinitions) {
            const QJsonObject item = entry.toObject();
            if (item.value(QStringLiteral("pickupKind")).toInt() == pickup->currentData().toInt()) {
                playerItemName = item.value(QStringLiteral("name")).toString().trimmed();
                break;
            }
        }
        if (playerItemName.isEmpty()) {
            if (pickup->currentData().toInt() == 1) playerItemName = tr("Coins");
            else playerItemName = pickup->currentData().toInt() < 5
                ? pickup->currentText().trimmed()
                : pickup->currentText().section(QStringLiteral(": "), 1).trimmed();
        }
        if (playerItemName.isEmpty()) playerItemName = old.name.trimmed();
        const QString profileFile = GamePlayerProfile::profilePath(playerProject);
        if (QFileInfo::exists(profileFile)) {
            QString profileError;
            if (!GamePlayerProfile::read(playerProject, &playerProfile, &profileError)) {
                QMessageBox::warning(&dialog, tr("Player Inventory"), profileError);
                return false;
            }
            bool exists = false;
            QJsonArray playerItems = playerProfile.value(QStringLiteral("inventory")).toArray();
            for (const QJsonValue &entry : playerItems)
                if (entry.toObject().value(QStringLiteral("name")).toString()
                    .compare(playerItemName, Qt::CaseInsensitive) == 0) { exists = true; break; }
            if (!exists && !playerItemName.isEmpty()) {
                if (playerItems.size() >= 64) {
                    QMessageBox::warning(&dialog, tr("Player Inventory"),
                        tr("The Player Inventory is full (64 types). Remove an unused type "
                           "in Create / Edit Player before adding '%1'.").arg(playerItemName));
                    return false;
                }
                const auto answer = QMessageBox::question(&dialog, tr("Add to Player Inventory?"),
                    tr("'%1' is shown in the backpack but isn't listed under "
                       "Create / Edit Player → Inventory.\n\n"
                       "Add it there with starting quantity 0? The item will be "
                       "available across worlds. You can edit it later.").arg(playerItemName),
                    QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::Yes);
                if (answer == QMessageBox::Cancel) return false;
                appendPlayerItem = answer == QMessageBox::Yes;
                if (appendPlayerItem) {
                    playerItems.append(QJsonObject{{QStringLiteral("name"), playerItemName},
                        {QStringLiteral("initial"), 0}, {QStringLiteral("hidden"), false}});
                    playerProfile.insert(QStringLiteral("inventory"), playerItems);
                }
            }
        } else {
            QMessageBox::information(&dialog, tr("Create a player first"),
                tr("This pickup will be registered in the Adventure Inventory. "
                   "Create the project player in Create / Edit Player if you also want "
                   "to list it under Player Inventory."));
        }
    }
    if (appendPlayerItem) {
        QString profileError;
        if (!GamePlayerProfile::write(playerProject, playerProfile, &profileError)) {
            QMessageBox::warning(&dialog, tr("Player Inventory"), profileError);
            return false;
        }
    }
    rememberResourceEdit();
    m_adventure.insert(QStringLiteral("pickupTypes"),customPickupTypes);
    if (createInventoryDefinition) {
        QString name = pickup->currentText().trimmed();
        if (pickup->currentData().toInt() >= 5 && name.contains(QStringLiteral(": ")))
            name = name.section(QStringLiteral(": "), 1);
        if (pickup->currentData().toInt() == 1) name = tr("Coins");
        if (name.isEmpty()) name = old.name.trimmed();
        if (name.isEmpty()) name = tr("Pickup");
        QJsonObject item;
        item.insert(QStringLiteral("name"), name);
        item.insert(QStringLiteral("pickupKind"), pickup->currentData().toInt());
        item.insert(QStringLiteral("capacity"), 65535);
        item.insert(QStringLiteral("initial"), 0);
        item.insert(QStringLiteral("icon"), 65535);
        inventoryDefinitions.append(item);
        m_adventure.insert(QStringLiteral("items"), inventoryDefinitions);
    }
    Resource &r = m_resources[index];
    r.spriteStamp = stamped.spriteStamp;
    r.path = stamped.path;
    r.cellWidth = stamped.cellWidth;
    r.cellHeight = stamped.cellHeight;
    r.frame = stamped.frame;
    r.objectType = newType;
    r.pickupKind = pickup->currentData().toInt();
    r.objectValue = value->value();
    r.pickupTrackingConfigured = newType == QStringLiteral("collectable") &&
        (old.pickupTrackingConfigured || pickupOptionsTouched || pickupStatTouched ||
         (!pickupShowInventory->isChecked() &&
          pickupStat->currentData().toString() != QStringLiteral("none")));
    r.pickupShowInventory = pickupShowInventory->isChecked();
    r.pickupShowHud = pickupShowHud->isChecked();
    r.pickupStatTarget = pickupStat->currentData().toString();
    r.pickupPersistent = pickupPersistent->isChecked();
    r.hitWidth = hitW->value(); r.hitHeight = hitH->value();
    r.particlePreset = particlePreset->currentData().toString();
    r.particleAreaW = particleW->value(); r.particleAreaH = particleH->value();
    r.particleCount = particleCount->value(); r.particleInterval = particleInterval->value();
    r.particlePrepopulate = particlePrepopulate->isChecked();
    r.particleLifetime = particleLifetime->value(); r.particleWind = particleWind->value();
    r.particleFall = particleFall->value(); r.particleGravity = particleGravity->value();
    r.particleFlutter = particleFlutter->value();
    r.particleSwirlRadius = particleSwirlRadius->value();
    r.particleSwirlSpeed = particleSwirlSpeed->value();
    r.particlePlayerLayerMix = particlePlayerMix->isChecked();
    r.particleFadeEnabled = particleFadeEnable->isChecked();
    r.particleFadeIn = particleFadeIn->value();
    r.particleFadeOut = particleFadeOut->value();
    r.particleFadeSpeed = particleFadeSpeed->value();
    r.conveyorSpeed = conveyor->value(); r.springStrength = spring->value();
    r.springLaunchX = springLaunchX->value();
    r.springTouch = springTouch->isChecked();
    r.springSlide = springSlide->isChecked();
    r.springJumpBoost = springJumpBoost->isChecked();
    r.breakTouch = breakTouch->isChecked();
    r.breakBounce = newType == QStringLiteral("enemy") ? enemyBounce->isChecked() : (breakBounce->isChecked() && !breakFromBelow->isChecked());
    r.breakFromBelow = breakFromBelow->isChecked();
    r.breakDropCollectableId = newType == QStringLiteral("enemy")
        ? enemyReward->currentData().toString() : breakReward->currentData().toString();
    r.breakRewardImpulse = newType == QStringLiteral("enemy")
        ? enemyRewardImpulse->isChecked() : breakRewardImpulse->isChecked();
    r.breakRewardVx = newType == QStringLiteral("enemy") ? enemyRewardVx->value() : breakRewardVx->value();
    r.breakRewardVy = newType == QStringLiteral("enemy") ? enemyRewardVy->value() : breakRewardVy->value();
    r.breakHits = newType == QStringLiteral("enemy") ? enemyHits->value() : breakHits->value();
    r.breakStrength = newType == QStringLiteral("enemy") ? enemyBounceY->value() : breakStrength->value();
    r.breakLaunchX = newType == QStringLiteral("enemy") ? enemyBounceX->value() : breakLaunchX->value();
    r.enemyStompSideKick = enemyStompSideKick->isChecked();
    r.enemyAttackDirection = enemyAttackDirection->currentData().toInt();
    r.enemyHurtsOnTouch = enemyHurt->isChecked();
    r.enemyDamage = newType == QStringLiteral("enemy") ? qAbs(damageDelta->value()) : enemyDamage->value();
    r.enemyRoam = enemyRoam->isChecked();
    r.enemyRoamSpeed = enemyRoamSpeed->value();
    r.enemyStepHeight = enemyStepHeight->value();
    r.enemyRoamLeft = enemyRoamLeft->isChecked();
    r.enemyDefeatFrame = enemyDefeatFrame->value();
    r.enemyDefeatFrames = enemyDefeatDelay->value(); // legacy read-back
    r.enemyDefeatCount = enemyDefeatCount->value();
    r.enemyDefeatDelay = enemyDefeatDelay->value();
    r.enemyStompOffsetX = enemyStompX->value();
    r.enemyStompOffsetY = enemyStompY->value();
    r.enemyStompWidth = enemyStompW->value();
    r.enemyStompHeight = enemyStompH->value();
    r.objectInitiallyActive = (newType == QStringLiteral("collectable"))
        ? !hiddenCollectable->isChecked() : initiallyActive->isChecked();
    r.drawBehindTiles = behindTiles->isChecked();
    r.objectFlipX = objectFlipX->isChecked();
    r.objectFlipY = objectFlipY->isChecked();
    r.objectAlphaFadePercent = objectFadeSlider->value();
    r.objectFadeAnimated = fadeAnimate->isChecked();
    r.objectFadeLow = qMin(fadeLow->value(), fadeHigh->value());
    r.objectFadeHigh = qMax(fadeLow->value(), fadeHigh->value());
    r.objectFadeStep = fadeStep->value();
    r.objectFadeDelay = fadeDelay->value();
    r.objectFadePingpong = fadePingpong->isChecked();
    r.hazardDamage = qAbs(damageDelta->value());
    r.damageTarget = damageTarget->currentData().toString();
    r.damageDelta = damageDelta->value();
    r.damageConfigured = true;
    r.hazardKick = hazardKick->isChecked();
    r.hazardKickX = hazardKickX->value();
    r.hazardKickY = hazardKickY->value();
    r.hazardHurtAnimation = hazardHurtAnim->isChecked();
    r.hazardFlash = hazardFlash->isChecked();
    r.hazardFlashColour = chosenHazardColour;
    r.hazardFlashCount = hazardFlashes->value();
    r.hazardFlashFrames = hazardFlashFrames->value();
    if (newType==QStringLiteral("trigger")) {
        const QVector<Resource::LinkedAction> actions=currentLinks();
        r.targetObjectId=actions.isEmpty() ? QString() : actions.first().objectId;
        r.targetAction=actions.isEmpty() ? QStringLiteral("none") : actions.first().action;
        r.triggerExtraActions.clear();
        for (int i=1;i<actions.size();++i) r.triggerExtraActions.append(actions.at(i));
    } else {
        r.targetObjectId=targetObject->currentData().toString();
        r.targetAction=targetAction->currentData().toString();
    }
    r.gotoWorldName = gotoWorld->currentData().toString();
    r.gotoPress = gotoActivation->currentData().toBool();
    r.gotoStartId = gotoStart->currentData().toString();
    r.checkpointSlot = checkpointSlot->value()-1;
    r.triggerPress = triggerPress->isChecked();
    r.triggerDrop = triggerDrop->isChecked();
    r.triggerOneShot = triggerOneShot->isChecked();
    r.interactItemName = interactItem->currentData().toString();
    r.interactRadius = interactRadius->value();
    r.interactConsume = interactConsume->isChecked();
    r.sfxInteractWrong = sfxInteractWrong->currentData().toString();
    r.sfxInteractSuccess = sfxInteractSuccess->currentData().toString();
    r.sfxInteractCancel = sfxInteractCancel->currentData().toString();
    r.interactDialogueNode = interactDialogue->currentData().toInt();
    r.interactDialogueMode = interactDialogueMode->currentData().toString();
    r.interactWrongDialogueNode = interactWrongDialogue->currentData().toInt();
    r.interactWrongDialogueMode = interactWrongDialogueMode->currentData().toString();
    r.interactRewardItem = interactReward->currentData().toString();
    r.interactRewardCount = interactRewardCount->value();
    r.interactStatTarget = interactStat->currentData().toString();
    r.interactStatDelta = interactStatDelta->value();
    r.activeStateFrame = activeStateFrame->value();
    r.inactiveStateFrame = inactiveStateFrame->value();
    r.triggerMusicId = musicTrack->currentData().toString();
    r.triggerMusicAction = musicAction->currentData().toString();
    r.sfxPickup = sfxPickup->currentData().toString();
    r.sfxRespawn = sfxRespawn->currentData().toString();
    r.sfxStart = sfxStart->currentData().toString();
    r.sfxMove = sfxMove->currentData().toString();
    r.sfxStop = sfxStop->currentData().toString();
    r.sfxReverse = sfxReverse->currentData().toString();
    r.sfxSpring = sfxSpring->currentData().toString();
    r.sfxAmbient = sfxAmbient->currentData().toString();
    r.sfxBreakHit = sfxBreakHit->currentData().toString();
    r.sfxBreakBounce = sfxBreakBounce->currentData().toString();
    r.sfxBreakFinish = sfxBreakFinish->currentData().toString();
    r.sfxHazardHit = sfxHazardHit->currentData().toString();
    r.sfxHazardBounce = sfxHazardBounce->currentData().toString();
    r.sfxHazardAmbient = sfxHazardAmbient->currentData().toString();
    r.respawnFrames = (r.pickupPersistent || collectOnce->isChecked()) ? 0 : respawn->value();
    r.audioRadius = radius->value();
    r.audioFadeFrames = fade->value();
    r.objectSplineId = spline->currentData().toString();
    r.objectSplineStartDelay = splineDelay->value();
    r.objectAnimated = !r.spriteStamp.active() && animated->isChecked();
    r.animFirst = first->value(); r.animCount = count->value();
    r.animTicks = ticks->value(); r.animMode = mode->currentData().toString();
    rebuildScene(); // Show updated mirroring on the live world canvas immediately.
    refreshResources();
    // Keep the edited object under Game Objects, never jump to its Sprites alias.
    if (r.objectType != QStringLiteral("decoration")) {
        for (QTreeWidgetItemIterator it(m_resourceTree); *it; ++it) {
            QTreeWidgetItem *entry=*it;
            if (entry->data(0,Qt::UserRole).isValid()
                && entry->data(0,Qt::UserRole).toInt()==index
                && entry->data(0,Qt::UserRole+1).toString()==QStringLiteral("gameobject")) {
                QSignalBlocker block(m_resourceTree);
                if (entry->parent()) entry->parent()->setExpanded(true);
                m_resourceTree->setCurrentItem(entry);
                m_resourceTree->scrollToItem(entry);
                break;
            }
        }
    }
    selectResource(index);
    setDirty();
    return true;
    };
    // Snapshot only editable values, not transient preview frames, selection,
    // scroll positions or other UI decoration. Compare the current draft with
    // the values recorded AFTER each object is loaded. This also catches
    // edits made in child dialogs (sprite stamps and custom pickup types).
    const auto draftSnapshot = [&]() -> QVariantList {
        QVariantList values;
        for (QWidget *widget : dialog.findChildren<QWidget *>()) {
            // Linked rows are recreated on each switch; inspect their actual
            // row order below, not widgets awaiting Qt deferred deletion.
            if (linkedActionRows->isAncestorOf(widget)) continue;
            if (auto *combo = qobject_cast<QComboBox *>(widget)) {
                values << combo->currentData() << combo->currentText();
            } else if (auto *check = qobject_cast<QCheckBox *>(widget)) {
                values << check->isChecked();
            } else if (auto *spin = qobject_cast<QSpinBox *>(widget)) {
                values << spin->value();
            } else if (auto *spin = qobject_cast<QDoubleSpinBox *>(widget)) {
                values << spin->value();
            } else if (auto *edit = qobject_cast<QLineEdit *>(widget)) {
                values << edit->text();
            } else if (auto *slider = qobject_cast<QSlider *>(widget)) {
                values << slider->value();
            }
        }
        values << linkedActionRows->rowCount();
        for (int row = 0; row < linkedActionRows->rowCount(); ++row) {
            auto *target = qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row, 0));
            auto *action = qobject_cast<QComboBox *>(linkedActionRows->cellWidget(row, 1));
            values << (target ? target->currentData() : QVariant());
            values << (action ? action->currentData() : QVariant());
        }
        values << QJsonDocument(customPickupTypes).toJson(QJsonDocument::Compact)
               << QJsonDocument(draftSpriteStamp.toJson()).toJson(QJsonDocument::Compact)
               << chosenHazardColour << pickupOptionsTouched << pickupStatTouched;
        return values;
    };
    QVariantList loadedDraft = draftSnapshot();
    // Reload *every* setting into the same live dialog. A close/reopen would
    // lose maximised/scroll state and visibly flash on each arrow press.
    const auto showObject = [&](int selectedIndex) {
        index = selectedIndex;
        old = m_resources.at(index);
        fadePreviewFrames = 0;
        fadeCanvasPercent = -1;
        draftSpriteStamp = old.spriteStamp;
        editSpriteStampButton->setText(draftSpriteStamp.active()
            ? tr("Edit Sprite Stamp (%1 x %2 tiles)...").arg(draftSpriteStamp.width).arg(draftSpriteStamp.height)
            : tr("Arrange Sprite Stamp..."));
        dialog.setUpdatesEnabled(false);
        dialog.setWindowTitle(tr("Game Object Properties - %1").arg(old.name));
        objectName->setText(old.name);
        objectName->setToolTip(old.name);
        resourceName->setText(old.name);
        type->setCurrentIndex(qMax(0, type->findData(old.objectType)));
        refillPickup(old.pickupKind);
        value->setValue(old.objectValue);
        pickupShowInventory->setChecked(old.pickupShowInventory);
        pickupShowHud->setChecked(old.pickupShowHud);
        pickupPersistent->setChecked(old.pickupPersistent);
        const QString shownStat = old.pickupStatTarget.isEmpty()
            ? (old.pickupKind == 2 ? QStringLiteral("health") : QStringLiteral("none"))
            : old.pickupStatTarget;
        if (pickupStat->findData(shownStat) < 0)
            pickupStat->addItem(shownStat, shownStat);
        pickupStat->setCurrentIndex(qMax(0, pickupStat->findData(shownStat)));
        initiallyActive->setChecked(old.objectInitiallyActive);
        hiddenCollectable->setChecked(!old.objectInitiallyActive ||
            (old.objectType == QStringLiteral("collectable") &&
             std::any_of(m_resources.cbegin(), m_resources.cend(), [&](const Resource &candidate) {
                return (candidate.objectType == QStringLiteral("breakable") ||
                        candidate.objectType == QStringLiteral("enemy")) &&
                       candidate.breakDropCollectableId == old.id;
             })));
        behindTiles->setChecked(old.drawBehindTiles);
        particlePreset->setCurrentIndex(qMax(0, particlePreset->findData(old.particlePreset)));
        particleW->setValue(old.particleAreaW);
        particleH->setValue(old.particleAreaH);
        particleCount->setValue(old.particleCount);
        particleInterval->setValue(old.particleInterval);
        particlePrepopulate->setChecked(old.particlePrepopulate);
        particleLifetime->setValue(old.particleLifetime);
        particleWind->setValue(old.particleWind);
        particleFall->setValue(old.particleFall);
        particleGravity->setValue(old.particleGravity);
        particleFlutter->setValue(old.particleFlutter);
        particleSwirlRadius->setValue(old.particleSwirlRadius);
        particleSwirlSpeed->setValue(old.particleSwirlSpeed);
        particlePlayerMix->setChecked(old.particlePlayerLayerMix);
        particleFadeEnable->setChecked(old.particleFadeEnabled);
        particleFadeIn->setValue(old.particleFadeIn);
        particleFadeOut->setValue(old.particleFadeOut);
        particleFadeSpeed->setValue(old.particleFadeSpeed);
        targetObject->clear();
        targetObject->addItem(tr("None (no linked object)"), QString());
        for (const Resource &candidate : m_resources) {
            if (candidate.kind == QStringLiteral("sprite") &&
                candidate.objectType != QStringLiteral("decoration") &&
                candidate.id != old.id)
                targetObject->addItem(tr("%1 [%2]").arg(candidate.name, candidate.objectType), candidate.id);
        }
        targetObject->setCurrentIndex(qMax(0, targetObject->findData(old.targetObjectId)));
        targetAction->setCurrentIndex(qMax(0, targetAction->findData(old.targetAction)));
        reloadLinks();
        gotoWorld->setCurrentIndex(qMax(0, gotoWorld->findData(old.gotoWorldName)));
        populateGotoStarts(old.gotoStartId);
        gotoActivation->setCurrentIndex(old.gotoPress ? 1 : 0);
        checkpointSlot->setValue(old.checkpointSlot+1);
        triggerPress->setChecked(old.triggerPress);
        triggerDrop->setChecked(old.triggerDrop);
        triggerOneShot->setChecked(old.triggerOneShot);
        interactItem->setCurrentIndex(qMax(0, interactItem->findData(old.interactItemName)));
        interactRadius->setValue(old.interactRadius);
        interactConsume->setChecked(old.interactConsume);
        sfxInteractWrong->setCurrentIndex(qMax(0, sfxInteractWrong->findData(old.sfxInteractWrong)));
        sfxInteractSuccess->setCurrentIndex(qMax(0, sfxInteractSuccess->findData(old.sfxInteractSuccess)));
        sfxInteractCancel->setCurrentIndex(qMax(0, sfxInteractCancel->findData(old.sfxInteractCancel)));
        interactDialogue->setCurrentIndex(qMax(0,interactDialogue->findData(old.interactDialogueNode)));
        interactDialogueMode->setCurrentIndex(qMax(0,interactDialogueMode->findData(old.interactDialogueMode)));
        interactWrongDialogue->setCurrentIndex(qMax(0,interactWrongDialogue->findData(old.interactWrongDialogueNode)));
        interactWrongDialogueMode->setCurrentIndex(qMax(0,interactWrongDialogueMode->findData(old.interactWrongDialogueMode)));
        interactReward->setCurrentIndex(qMax(0,interactReward->findData(old.interactRewardItem)));
        interactRewardCount->setValue(old.interactRewardCount);
        interactStat->setCurrentIndex(qMax(0,interactStat->findData(old.interactStatTarget)));
        interactStatDelta->setValue(old.interactStatDelta);
        activeStateFrame->setValue(old.activeStateFrame);
        inactiveStateFrame->setValue(old.inactiveStateFrame);
        musicAction->setCurrentIndex(qMax(0, musicAction->findData(old.triggerMusicAction)));
        musicTrack->setCurrentIndex(qMax(0, musicTrack->findData(old.triggerMusicId)));
        respawn->setValue(old.respawnFrames);
        collectOnce->setChecked(old.respawnFrames==0);
        hitW->setValue(old.hitWidth); hitH->setValue(old.hitHeight);
        conveyor->setValue(old.conveyorSpeed);
        spring->setValue(old.springStrength);
        springLaunchX->setValue(old.springLaunchX);
        springTouch->setChecked(old.springTouch);
        springSlide->setChecked(old.springSlide);
        springJumpBoost->setChecked(old.springJumpBoost);
        breakHits->setValue(old.breakHits);
        breakTouch->setChecked(old.breakTouch);
        breakFromBelow->setChecked(old.breakFromBelow);
        breakReward->clear();
        breakReward->addItem(tr("None — no reward"), QString());
        for (const Resource &candidate : m_resources) {
            if (candidate.id != old.id && candidate.kind == QStringLiteral("sprite") &&
                candidate.objectType == QStringLiteral("collectable"))
                breakReward->addItem(candidate.name, candidate.id);
        }
        breakReward->setCurrentIndex(qMax(0, breakReward->findData(old.breakDropCollectableId)));
        breakRewardImpulse->setChecked(old.breakRewardImpulse);
        breakRewardVx->setValue(old.breakRewardVx);
        breakRewardVy->setValue(old.breakRewardVy);
        breakBounce->setChecked(old.breakBounce);
        breakStrength->setValue(old.breakStrength);
        breakLaunchX->setValue(old.breakLaunchX);
        hazardDamage->setValue(old.objectType == QStringLiteral("enemy") ? old.enemyDamage : old.hazardDamage);
        enemyHits->setValue(old.breakHits);
        enemyBounce->setChecked(old.breakBounce);
        enemyBounceY->setValue(old.breakStrength);
        enemyBounceX->setValue(old.breakLaunchX);
        enemyStompSideKick->setChecked(old.enemyStompSideKick);
        enemyAttackDirection->setCurrentIndex(qMax(0, enemyAttackDirection->findData(old.enemyAttackDirection)));
        enemyRewardImpulse->setChecked(old.breakRewardImpulse);
        enemyRewardVx->setValue(old.breakRewardVx);
        enemyRewardVy->setValue(old.breakRewardVy);
        enemyHurt->setChecked(old.enemyHurtsOnTouch);
        enemyReward->setCurrentIndex(qMax(0, enemyReward->findData(old.breakDropCollectableId)));
        enemyDefeatFrame->setValue(old.enemyDefeatFrame);
        enemyDefeatCount->setValue(old.enemyDefeatCount);
        enemyDefeatDelay->setValue(old.enemyDefeatDelay);
        enemyStompX->setValue(old.enemyStompOffsetX);
        enemyStompY->setValue(old.enemyStompOffsetY);
        enemyStompW->setValue(old.enemyStompWidth);
        enemyStompH->setValue(old.enemyStompHeight);
        enemyRoam->setChecked(old.enemyRoam);
        enemyRoamSpeed->setValue(old.enemyRoamSpeed);
        enemyStepHeight->setValue(old.enemyStepHeight);
        enemyRoamLeft->setChecked(old.enemyRoamLeft);
        hazardKick->setChecked(old.hazardKick);
        hazardKickX->setValue(old.hazardKickX);
        hazardKickY->setValue(old.hazardKickY);
        hazardHurtAnim->setChecked(old.hazardHurtAnimation);
        hazardFlash->setChecked(old.hazardFlash);
        // Refresh the swatch when switching the selected object in Properties.
        flashBank = activePalette(QStringLiteral("foreground"));
        if (flashBank.size()!=256 && !old.path.isEmpty()) {
            SidboxPpb::Picture picture;
            if (SidboxPpb::read(resolvedPath(old.path), &picture))
                flashBank=picture.indexed.colorTable();
        }
        chosenHazardColour=qBound(0,old.hazardFlashColour,255);
        updateFlashSwatch();
        hazardFlashes->setValue(old.hazardFlashCount);
        hazardFlashFrames->setValue(old.hazardFlashFrames);
        spline->setCurrentIndex(qMax(0, spline->findData(old.objectSplineId)));
        splineDelay->setValue(old.objectSplineStartDelay);
        animated->setChecked(old.objectAnimated);
        objectFlipX->setChecked(old.objectFlipX);
        objectFlipY->setChecked(old.objectFlipY);
        objectFadeSlider->setValue(old.objectAlphaFadePercent);
        fadeAnimate->setChecked(old.objectFadeAnimated);
        fadeLow->setValue(old.objectFadeLow);
        fadeHigh->setValue(old.objectFadeHigh);
        fadeStep->setValue(old.objectFadeStep);
        fadeDelay->setValue(old.objectFadeDelay);
        fadePingpong->setChecked(old.objectFadePingpong);
        first->setValue(old.animFirst);
        count->setValue(old.animCount);
        ticks->setValue(old.animTicks);
        mode->setCurrentIndex(qMax(0, mode->findData(old.animMode)));
        const auto chooseSound = [](QComboBox *box, const QString &id) {
            box->setCurrentIndex(qMax(0, box->findData(id)));
        };
        chooseSound(sfxPickup, old.sfxPickup);
        chooseSound(sfxRespawn, old.sfxRespawn);
        chooseSound(sfxStart, old.sfxStart);
        chooseSound(sfxMove, old.sfxMove);
        chooseSound(sfxStop, old.sfxStop);
        chooseSound(sfxReverse, old.sfxReverse);
        chooseSound(sfxSpring, old.sfxSpring);
        chooseSound(sfxAmbient, old.sfxAmbient);
        chooseSound(sfxBreakHit, old.sfxBreakHit);
        chooseSound(sfxBreakBounce, old.sfxBreakBounce);
        chooseSound(sfxBreakFinish, old.sfxBreakFinish);
        chooseSound(sfxHazardHit, old.sfxHazardHit);
        chooseSound(sfxHazardBounce, old.sfxHazardBounce);
        chooseSound(sfxHazardAmbient, old.sfxHazardAmbient);
        radius->setValue(old.audioRadius);
        fade->setValue(old.audioFadeFrames);
        atlas = cachedImage(resolvedPath(old.path));
        if (atlas.format() == QImage::Format_Indexed8) {
            const QVector<QRgb> palette = activePalette(QStringLiteral("foreground"));
            if (palette.size() == 256)
                atlas.setColorTable(colourPreviewBank(palette, true, m_previewPaletteAlpha && m_previewPaletteAlpha->isChecked()));
        }
        refreshDeathStartButton();
        previewFrame = 0;
        previewPlaying = true;
        enableFields();
        refreshTimer();
        previousIndex = -1;
        nextIndex = -1;
        for (int i = 0; i < m_resources.size(); ++i) {
            const Resource &candidate = m_resources.at(i);
            if (candidate.kind != QStringLiteral("sprite") ||
                candidate.objectType == QStringLiteral("decoration")) continue;
            if (i < index) previousIndex = i;
            if (i > index && nextIndex < 0) nextIndex = i;
        }
        previousObject->setEnabled(previousIndex >= 0);
        nextObject->setEnabled(nextIndex >= 0);
        // Programmatic setters above fire signals too. They are NOT user edits.
        pickupOptionsTouched = false;
        pickupStatTouched = false;
        loadedDraft = draftSnapshot();
        updateParticleDraft();
        dialog.setUpdatesEnabled(true);
        dialog.update();
    };
    // Previous/Next changes the selected object WITHOUT committing unchanged
    // drafts. For edited objects: Save commits now, No discards the draft,
    // Cancel keeps editing. An earlier Save remains committed as before.
    const auto navigateObject = [&](int destination) {
        if (destination < 0 || destination >= m_resources.size()) return;
        if (draftSnapshot() != loadedDraft) {
            const QMessageBox::StandardButton answer = QMessageBox::question(
                &dialog, tr("Save changes before switching object?"),
                tr("This Game Object has unsaved changes.\n\n"
                   "Save: save this object and switch.\n"
                   "No: discard its unsaved changes and switch.\n"
                   "Cancel: stay here and continue editing.\n\n"
                   "Changes already saved on previous objects are not undone."),
                QMessageBox::Save | QMessageBox::No | QMessageBox::Cancel,
                QMessageBox::Save);
            if (answer == QMessageBox::Cancel || answer == QMessageBox::NoButton)
                return;
            if (answer == QMessageBox::Save) {
                if (!commitObject()) return; // validation failed; don't switch
            } else if (answer == QMessageBox::No) {
                // These draft changes live outside the ordinary field widgets.
                customPickupTypes = m_adventure.value(QStringLiteral("pickupTypes")).toArray();
            } else {
                return;
            }
        }
        // The patterned-fade preview can temporarily alter the world canvas
        // without saving. Restore the outgoing object's saved appearance.
        fadePreviewPercent = m_resources.at(index).objectAlphaFadePercent;
        fadeCanvasPercent = -1;
        previewFadeOnCanvas();
        showObject(destination);
    };
    connect(previousObject, &QToolButton::clicked, &dialog, [&]() {
        navigateObject(previousIndex);
    });
    connect(nextObject, &QToolButton::clicked, &dialog, [&]() {
        navigateObject(nextIndex);
    });
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel,
                                         Qt::Horizontal, &dialog);
    layout.addWidget(buttons);
    if (auto *ok = buttons->button(QDialogButtonBox::Save))
        ok->setStyleSheet(QStringLiteral("QPushButton { background:%1; color:%2; "
            "border:1px solid %1; padding:6px 30px; border-radius:0px; }")
                .arg(colour(m_theme.accent), colour(m_theme.brightText)));
    if (auto *cancel = buttons->button(QDialogButtonBox::Cancel))
        cancel->setToolTip(tr("Discard edits to this object since the last Save. Objects saved using Previous/Next cannot be rolled back here."));
    connect(buttons, &QDialogButtonBox::accepted, &dialog, [&]() {
        if (commitObject()) dialog.accept();
    });
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (!objectSavedGeometry.isEmpty()) dialog.restoreGeometry(objectSavedGeometry);
    else if (objectWindowWasMaximized)
        dialog.setWindowState(dialog.windowState() | Qt::WindowMaximized);
    // The modal fade preview owns this object's canvas pixels while open.
    // Prevent the world-canvas 50 Hz timer from repainting the saved values
    // on top of the live unsaved slider/animation preview.
    const bool restartCanvasTimer = m_objectPreviewTimer && m_objectPreviewTimer->isActive();
    if (restartCanvasTimer) m_objectPreviewTimer->stop();
    // The modal dialog stops the ordinary animation preview, but the particle
    // world-canvas simulation remains live. Its draft is NEVER saved on Cancel.
    QTimer particleDialogPreviewTimer(&dialog);
    particleDialogPreviewTimer.setInterval(20);
    connect(&particleDialogPreviewTimer, &QTimer::timeout, &dialog,
        [this, particlePreviewCanvas, &particlePreviewLastBounds, &particlePreviewNeedsFit]() {
        if (!isVisible()) return;
        updateParticlePreview();
        if (particlePreviewNeedsFit && particlePreviewCanvas->isVisible() &&
            !particlePreviewLastBounds.isNull() &&
            particlePreviewCanvas->viewport()->width() > 20) {
            // The view-specific sceneRect prevents auto-scroll recalculation
            // as leaves/fireflies drift outside the emitter's preview region.
            particlePreviewCanvas->setSceneRect(particlePreviewLastBounds);
            particlePreviewCanvas->fitInView(particlePreviewLastBounds, Qt::KeepAspectRatio);
            particlePreviewNeedsFit = false;
        }
    });
    particleDialogPreviewTimer.start();
    const int result = dialog.exec();
    particleDialogPreviewTimer.stop();
    clearParticlePreviewDraft();
    if (restartCanvasTimer && m_objectPreviewTimer) m_objectPreviewTimer->start();
    if (result != QDialog::Accepted) {
        // Only the current object has uncommitted slider changes.
        // Earlier objects visited with Next/Previous were explicitly saved.
        for (int i = 0; i < m_resources.size() && i < m_sceneItems.size(); ++i) {
            if (m_resources.at(i).id != old.id) continue;
            auto *image = dynamic_cast<QGraphicsPixmapItem *>(m_sceneItems.at(i));
            if (!image) break;
            Resource saved = m_resources.at(i);
            saved.frame = image->data(1).toInt();
            const QImage base = resourcePreview(saved);
            if (!base.isNull()) {
                image->setPixmap(QPixmap::fromImage(patternedBobPreview(base,
                    saved.objectAlphaFadePercent, saved.scale, saved.x, saved.y)));
                image->setScale(saved.objectAlphaFadePercent > 0 ? 1.0 : saved.scale / 100.0);
                image->setShapeMode(saved.objectAlphaFadePercent > 0
                    ? QGraphicsPixmapItem::BoundingRectShape
                    : QGraphicsPixmapItem::MaskShape);
            }
            break;
        }
    }
    objectWindowSettings.setValue(QStringLiteral("GameObjectProperties/geometry"), dialog.saveGeometry());
    objectWindowSettings.setValue(QStringLiteral("GameObjectProperties/maximized"), dialog.isMaximized());
}

void SidboxGameDesigner::refreshObjectHitbox()
{
    if (!m_scene || m_loading) return;
    if (m_objectHitbox) {
        m_particleResizeHandles.clear(); // The rectangle owns and deletes its child handles.
        m_scene->removeItem(m_objectHitbox);
        delete m_objectHitbox;
        m_objectHitbox = nullptr;
    }
    const int index = selectedIndex();
    if (index < 0 || index >= m_resources.size()) return;
    const Resource &r = m_resources.at(index);
    if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")) return;
    const bool emitter = r.objectType == QStringLiteral("particle_emitter");
    QPen pen(emitter ? QColor(105, 210, 150) : m_theme.accent, 1.5, Qt::DashLine);
    m_objectHitbox = m_scene->addRect(r.x, r.y,
                                     emitter ? r.particleAreaW : r.hitWidth,
                                     emitter ? r.particleAreaH : r.hitHeight,
                                     pen, Qt::NoBrush);
    if (emitter)
        m_objectHitbox->setToolTip(tr("Scenery particle spawn area: %1 x %2 pixels. Visual only; no player collision.")
                                     .arg(r.particleAreaW).arg(r.particleAreaH));
    m_objectHitbox->setZValue(9900);
    m_objectHitbox->setAcceptedMouseButtons(Qt::NoButton);
    if (emitter && !r.locked) {
        // Eight conventional selection grips; fixed view-pixel size is not
        // necessary for hit testing because eventFilter uses viewport distance.
        const qreal x = r.x, y = r.y, w = r.particleAreaW, h = r.particleAreaH;
        const QPointF grips[] = {
            {x, y}, {x + w / 2, y}, {x + w, y}, {x + w, y + h / 2},
            {x + w, y + h}, {x + w / 2, y + h}, {x, y + h}, {x, y + h / 2}
        };
        for (int side = 0; side < 8; ++side) {
            auto *grip = new QGraphicsRectItem(QRectF(grips[side].x() - 4,
                grips[side].y() - 4, 8, 8), m_objectHitbox);
            grip->setPen(QPen(QColor(21, 63, 45), 1));
            grip->setBrush(QColor(136, 244, 173));
            grip->setZValue(1);
            grip->setAcceptedMouseButtons(Qt::NoButton);
            grip->setToolTip(tr("Drag to resize particle spawn area (world pixels)."));
            m_particleResizeHandles.append(grip);
        }
        m_objectHitbox->setToolTip(tr(
            "Particle spawn area %1 × %2. Drag green handles to resize; "
            "the top-left anchor also moves the origin. Ctrl+Z undoes a resize.")
            .arg(r.particleAreaW).arg(r.particleAreaH));
    }
}

// Matches splinepaths' exported identifier de-duplication EXACTLY.
QString SidboxGameDesigner::splineSymbol(int target) const
{
    QSet<QString> used;
    for (int i = 0; i < m_splinePaths.size(); ++i) {
        const SplinePath &path = m_splinePaths.at(i);
        if (path.points.size() < 2) continue;
        QString n = path.name.toLower();
        n.replace(QRegularExpression(QStringLiteral("[^a-z0-9_]")), QStringLiteral("_"));
        if (n.isEmpty() || n.at(0).isDigit()) n.prepend(QLatin1Char('_'));
        QString sym = QStringLiteral("spline_") + n;
        const QString base = sym;
        int suffix = 2;
        while (used.contains(sym)) sym = base + QStringLiteral("_%1").arg(suffix++);
        used.insert(sym);
        if (i == target) return sym;
    }
    return QString();
}

QString SidboxGameDesigner::spriteSymbol(const Resource &r) const
{
    static const QRegularExpression arrayName(
        QStringLiteral("^([A-Za-z_][A-Za-z_0-9]*)\\[([0-9]+)\\]$"));
    const auto match = arrayName.match(r.name.trimmed());
    QString base = match.hasMatch() ? match.captured(1) : r.name.trimmed();
    if (base.isEmpty()) base = QFileInfo(resolvedPath(r.path)).completeBaseName();
    const QString symbol = SidboxPpb::identifier(base).toLower();
    return match.hasMatch() ? QStringLiteral("%1[%2]").arg(symbol, match.captured(2)) : symbol;
}

// Build separate foreground/background banks from absolute index votes.
// Do NOT create PPBs, rewrite palette tables inside PPBs, or relink assets.
// Hardware-ready shared.pal contains BOTH 256x4 banks; the optional one-bank
// palette files make it easy to select each bank independently for preview.
void SidboxGameDesigner::buildSharedPalette()
{
    struct Input { QString path; QString plane; };
    QVector<Input> inputs;
    const QRectF viewport(m_cameraX->value(), m_cameraY->value(), LCD_WIDTH, LCD_HEIGHT);
    QSet<QString> seenFiles;
    const QString activeAtlas = m_tilemapEnabled && !m_tilemap.atlasPath.isEmpty()
        ? QDir::cleanPath(resolvedPath(m_tilemap.atlasPath)) : QString();
    for (const Resource &r : m_resources) {
        // Include the selected atlas in the foreground CLUT even though it
        // has no canvas rectangle to intersect the LCD camera viewport.
        const bool selectedAtlas = r.kind == QStringLiteral("tileatlas")
            && !activeAtlas.isEmpty() && !r.path.isEmpty()
            && QDir::cleanPath(resolvedPath(r.path)) == activeAtlas;
        if ((!visualKind(r.kind) && !selectedAtlas) || r.path.isEmpty()) continue;
        const QString plane = selectedAtlas ? QStringLiteral("foreground") : resourcePlane(r);
        if (plane == QStringLiteral("background") && m_planeMode->currentIndex() == 0) continue;
        const QString absolute = resolvedPath(r.path);
        if (!QFileInfo(absolute).isFile()) continue;
        // Only indexed graphics carry stable hardware palette indices.
        const QImage image = cachedImage(absolute);
        if (image.isNull() || image.format() != QImage::Format_Indexed8) continue;
        const int cw = r.cellWidth > 0 ? qMin(r.cellWidth, image.width()) : image.width();
        const int ch = r.cellHeight > 0 ? qMin(r.cellHeight, image.height()) : image.height();
        const QRectF bounds(r.x, r.y, cw * r.scale / 100.0, ch * r.scale / 100.0);
        const QString key = absolute + QLatin1Char('|') + plane;
        if ((!selectedAtlas && !bounds.intersects(viewport)) || seenFiles.contains(key)) continue;
        seenFiles.insert(key);
        inputs.append(Input{absolute, plane});
    }
    if (inputs.isEmpty()) {
        QMessageBox::information(this, tr("Build Shared CLUT"), tr(
            "No indexed graphics intersect the yellow LCD camera frame, and no selected "
            "Tile Atlas PPB was found. Convert any truecolour images to PPB first."));
        return;
    }
    const bool dual = m_planeMode->currentIndex() == 1;
    int foregroundCount = 0, backgroundCount = 0;
    for (const Input &input : inputs) {
        if (input.plane == QStringLiteral("background")) ++backgroundCount;
        else ++foregroundCount;
    }
    const QString question = tr(
        "Build shared palette bank(s) from %1 foreground and %2 background resource(s)?\n\n"
        "Each PPB retains its existing source file and every original pixel index. "
        "NO PPB copies will be created.\n\n"
        "A 2048-byte shared.pal (foreground + background) and separate per-plane .pal "
        "files will be saved under gamepalettes/.\n\n"
        "Where two images disagree about the colour at an index, similar colours "
        "will be averaged; substantial conflicts retain the first value and are reported.\n\n"
        "Only placed graphics intersecting the LCD camera and the selected "
        "Tile Atlas are included (complete PPB sheets are analysed).\n\n"
        "You can choose either generated CLUT in the preview dropdowns. "
        "Please verify the result on SIDBOX hardware.")
        .arg(foregroundCount).arg(dual ? backgroundCount : 0);
    if (QMessageBox::question(this, tr("Build Shared CLUT"), question) != QMessageBox::Yes) return;

    const QString projectDir = QFileInfo(m_filePath).absolutePath();
    const QString outputDir = QDir(projectDir).filePath(QStringLiteral("gamepalettes/shared_")
        + QUuid::createUuid().toString(QUuid::WithoutBraces).left(10));
    const QVector<QRgb> previousForeground = activePalette(QStringLiteral("foreground"));
    const QVector<QRgb> previousBackground = activePalette(QStringLiteral("background"));
    struct Result {
        QString error;
        QString sharedPath;
        QString foregroundPath;
        QString backgroundPath;
        int fgConflicts = 0;
        int bgConflicts = 0;
        int fgSevere = 0;
        int bgSevere = 0;
        bool madeForeground = false;
        bool madeBackground = false;
        bool success = false;
    };
    const auto result = std::make_shared<Result>();
    auto *progress = new QProgressDialog(tr("Building palette files (original graphics untouched)..."),
                                        QString(), 0, 0, this);
    progress->setWindowTitle(tr("SIDBOX CLUT Builder"));
    progress->setCancelButton(nullptr);
    progress->setMinimumDuration(0);
    progress->setWindowModality(Qt::ApplicationModal);
    progress->show();
    m_buildPaletteButton->setEnabled(false);
    QThread *thread = QThread::create([inputs, dual, outputDir, previousForeground,
                                      previousBackground, result]() {
        QVector<QImage> frontImages, backImages;
        for (const Input &input : inputs) {
            QImage image;
            if (QFileInfo(input.path).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) == 0) {
                SidboxPpb::Picture picture;
                if (!SidboxPpb::read(input.path, &picture, &result->error)) return;
                image = picture.indexed;
            } else {
                QImageReader reader(input.path);
                reader.setAutoTransform(true);
                image = reader.read();
                if (image.isNull()) { result->error = reader.errorString(); return; }
            }
            if (image.format() != QImage::Format_Indexed8) {
                result->error = QStringLiteral("Resource has no absolute 8-bit indices: %1").arg(input.path);
                return;
            }
            if (input.plane == QStringLiteral("background")) backImages.append(image);
            else frontImages.append(image);
        }
        QVector<QRgb> foreground = previousForeground.size() == 256
            ? previousForeground : QVector<QRgb>(256, qRgba(0, 0, 0, 255));
        QVector<QRgb> background = previousBackground.size() == 256
            ? previousBackground : QVector<QRgb>(256, qRgba(0, 0, 0, 255));
        if (!frontImages.isEmpty()) {
            SidboxGamePalette::IndexBuildResult built;
            if (!SidboxGamePalette::buildIndexPreserving(frontImages, false, &built, &result->error)) return;
            foreground = built.colours;
            result->fgConflicts = built.collisions;
            result->fgSevere = built.severeCollisions;
            result->madeForeground = true;
        }
        if (dual && !backImages.isEmpty()) {
            SidboxGamePalette::IndexBuildResult built;
            if (!SidboxGamePalette::buildIndexPreserving(backImages, true, &built, &result->error)) return;
            background = built.colours;
            result->bgConflicts = built.collisions;
            result->bgSevere = built.severeCollisions;
            result->madeBackground = true;
        }
        QDir directory;
        if (!directory.mkpath(outputDir)) {
            result->error = QStringLiteral("Cannot create palette output directory.");
            return;
        }
        const auto failAndClean = [outputDir, result]() {
            QDir(outputDir).removeRecursively();
            if (result->error.isEmpty()) result->error = QStringLiteral("Failed to write palette outputs.");
        };
        result->sharedPath = QDir(outputDir).filePath(QStringLiteral("shared.pal"));
        if (!SidboxGamePalette::writePal(result->sharedPath, foreground, background, &result->error)) {
            failAndClean(); return;
        }
        if (result->madeForeground) {
            result->foregroundPath = QDir(outputDir).filePath(QStringLiteral("foreground.pal"));
            if (!SidboxGamePalette::writeSinglePal(result->foregroundPath, foreground, &result->error)) {
                failAndClean(); return;
            }
        }
        if (result->madeBackground) {
            result->backgroundPath = QDir(outputDir).filePath(QStringLiteral("background.pal"));
            if (!SidboxGamePalette::writeSinglePal(result->backgroundPath, background, &result->error)) {
                failAndClean(); return;
            }
        }
        result->success = true;
    });
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);
    connect(thread, &QThread::finished, this, [this, result, progress]() {
        progress->close();
        progress->deleteLater();
        m_buildPaletteButton->setEnabled(true);
        if (!result->success) {
            QMessageBox::warning(this, tr("Build Shared CLUT"),
                result->error.isEmpty() ? tr("Palette build failed.") : result->error);
            return;
        }
        rememberResourceEdit();
        int selectedPalette = -1;
        for (const QString &plane : {QStringLiteral("foreground"), QStringLiteral("background")}) {
            const QString path = plane == QStringLiteral("foreground")
                ? result->foregroundPath : result->backgroundPath;
            if (path.isEmpty()) continue;
            Resource resource;
            resource.kind = QStringLiteral("palette");
            resource.plane = plane;
            resource.name = QStringLiteral("shared_%1").arg(plane);
            resource.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
            resource.path = storedPath(path);
            m_resources.append(resource);
            selectedPalette = m_resources.size() - 1;
            if (plane == QStringLiteral("foreground")) m_activeForegroundPalette = resource.id;
            else m_activeBackgroundPalette = resource.id;
        }
        {
            QSignalBlocker block(m_forcePalette);
            m_forcePalette->setChecked(true);
        }
        m_previewPaletteAlpha->setEnabled(true);
        rebuildScene();
        refreshResources();
        if (selectedPalette >= 0) selectResource(selectedPalette);
        setDirty();
        if (assetFilesChanged) assetFilesChanged();
        QMessageBox::information(this, tr("Shared CLUT Created"), tr(
            "Created CLUT files under:\n%1\n\n"
            "shared.pal contains BOTH hardware banks. Separate foreground.pal and "
            "background.pal files contain the individual banks when built.\n\n"
            "Your original PPBs, pixel indices and design asset paths are untouched.\n\n"
            "Foreground: %2 differing indices (%3 major conflicts)\n"
            "Background: %4 differing indices (%5 major conflicts)\n\n"
            "The generated banks are selected for Forced Preview. "
            "Check the result on real SIDBOX hardware.")
            .arg(QFileInfo(result->sharedPath).absolutePath())
            .arg(result->fgConflicts).arg(result->fgSevere)
            .arg(result->bgConflicts).arg(result->bgSevere));
    });
    thread->start();
}

void SidboxGameDesigner::refreshColours()
{
    if (!m_scene) return;
    const QColor base = palette().color(QPalette::Base);
    m_scene->setBackgroundBrush(QBrush(base));
    static_cast<GameScene *>(m_scene)->gridColour = palette().color(QPalette::Mid);
    m_scene->update();
}

void SidboxGameDesigner::restoreWorldViewPosition()
{
    if (!m_restoreWorldViewCenter || !m_view) return;
    // Restoring in the parent showEvent alone is too early for tabs created
    // hidden: QGraphicsView's subsequent viewport layout can reset scrollbars
    // back to the upper left. Keep the request pending until the *viewport*
    // is visible and sized, then restore after Qt has processed that layout.
    QTimer::singleShot(0, this, [this]() {
        if (!m_restoreWorldViewCenter || !m_view || !m_view->isVisible()
            || !m_view->viewport()->isVisible()
            || m_view->viewport()->width() <= 0 || m_view->viewport()->height() <= 0)
            return;
        const QSignalBlocker horizontalBlock(m_view->horizontalScrollBar());
        const QSignalBlocker verticalBlock(m_view->verticalScrollBar());
        m_view->centerOn(m_savedWorldViewCenter);
        m_restoreWorldViewCenter = false;
    });
}

void SidboxGameDesigner::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);
    restoreWorldViewPosition();
}

void SidboxGameDesigner::changeEvent(QEvent *event)
{
    QWidget::changeEvent(event);
    if (event->type() == QEvent::PaletteChange || event->type() == QEvent::StyleChange)
        refreshColours();
}

// The Delete key removes references only. Never intercept Delete inside text
// editors/spinboxes. Space+left-drag shifts the world camera, not a sprite.
bool SidboxGameDesigner::eventFilter(QObject *watched, QEvent *event)
{
    const bool onView = m_view && (watched == m_view || watched == m_view->viewport());
    if (onView && m_restoreWorldViewCenter &&
        (event->type() == QEvent::Resize || event->type() == QEvent::Show))
        restoreWorldViewPosition();
    const bool onResources = watched == m_resourceTree ||
        (m_resourceTree && watched == m_resourceTree->viewport());
    if (onView || onResources) {
        if (event->type() == QEvent::KeyPress) {
            auto *key = static_cast<QKeyEvent *>(event);
            if ((key->modifiers() & Qt::ControlModifier) && !key->isAutoRepeat()) {
                // Shortcuts are only captured in the canvas or resource tree;
                // Ctrl+C/Z in the properties' text editors keep their normal meaning.
                switch (key->key()) {
                case Qt::Key_C: copySelectedSprite(); return true;
                case Qt::Key_V: pasteCopiedSprite(); return true;
                case Qt::Key_Z:
                    if (key->modifiers() & Qt::ShiftModifier) redoResourceEdit();
                    else undoResourceEdit();
                    return true;
                case Qt::Key_Y: redoResourceEdit(); return true;
                default: break;
                }
            }
            if (key->key() == Qt::Key_Delete && !key->isAutoRepeat()) {
                deleteSelectedResource();
                return true;
            }
            if (onView && key->key() == Qt::Key_Space && !key->isAutoRepeat()) {
                m_spaceHeld = true;
                m_view->viewport()->setCursor(Qt::OpenHandCursor);
                return true;
            }
        }
        if (onView && event->type() == QEvent::KeyRelease) {
            auto *key = static_cast<QKeyEvent *>(event);
            if (key->key() == Qt::Key_Space && !key->isAutoRepeat()) {
                m_spaceHeld = false;
                m_panningCamera = false;
                if (!m_middlePanning && !m_marqueeSelecting)
                    m_view->viewport()->unsetCursor();
                return true;
            }
        }
    }
    if (m_view && watched == m_view->viewport()) {
        if (event->type() == QEvent::Wheel) {
            auto *wheel = static_cast<QWheelEvent *>(event);
            if (m_restoreWorldViewCenter) { wheel->accept(); return true; }
            const int movement = wheel->angleDelta().y();
            const int pixelMovement = wheel->pixelDelta().y();
            const int direction = movement > 0 || (movement == 0 && pixelMovement > 0) ? 1 :
                                  movement < 0 || (movement == 0 && pixelMovement < 0) ? -1 : 0;
            if (direction && m_zoom) {
                const int previous = m_zoom->currentIndex();
                const int next = qBound(0, previous + direction, m_zoom->count() - 1);
                if (next != previous) {
                    // Keep the world point under the pointer fixed while the
                    // existing zoom ComboBox performs the scale change.
                    const QPoint at = wheel->position().toPoint();
                    const QPointF scenePoint = m_view->mapToScene(at);
                    m_zoom->setCurrentIndex(next);
                    const QPoint now = m_view->mapFromScene(scenePoint);
                    m_view->horizontalScrollBar()->setValue(
                        m_view->horizontalScrollBar()->value() + now.x() - at.x());
                    m_view->verticalScrollBar()->setValue(
                        m_view->verticalScrollBar()->value() + now.y() - at.y());
                    setDirty();
                }
            }
            wheel->accept();
            return true;
        }
        if (event->type() == QEvent::ContextMenu) {
            // Handle before QGraphicsView forwards the context menu to the
            // scene, so right-click works on both empty canvas and sprites.
            showSplineMenu(static_cast<QContextMenuEvent *>(event)->pos());
            return true;
        }
        if (event->type() == QEvent::MouseButtonPress) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            const QPoint where = mouse->position().toPoint();
            if (mouse->button() == Qt::MiddleButton) {
                // Pan the EDITOR view, not camera_x/y in the game design.
                m_middlePanning = true;
                m_worldPanMoved = false;
                m_panLastPos = where;
                m_view->viewport()->setCursor(Qt::ClosedHandCursor);
                return true;
            }
            if (m_spaceHeld && mouse->button() == Qt::LeftButton) {
                m_panningCamera = true;
                m_panLastPos = where;
                m_view->viewport()->setCursor(Qt::ClosedHandCursor);
                return true;
            }
            if (mouse->button() == Qt::LeftButton && !m_spaceHeld) {
                const int resource = selectedIndex();
                if (resource >= 0 && resource < m_resources.size() &&
                    m_resources.at(resource).kind == QStringLiteral("sprite") &&
                    m_resources.at(resource).objectType == QStringLiteral("particle_emitter") &&
                    !m_resources.at(resource).locked) {
                    for (int side = 0; side < m_particleResizeHandles.size(); ++side) {
                        QGraphicsRectItem *handle = m_particleResizeHandles.at(side);
                        if (!handle) continue;
                        const QPointF centre = handle->sceneBoundingRect().center();
                        if ((m_view->mapFromScene(centre) - where).manhattanLength() > 13) continue;
                        const Resource &r = m_resources.at(resource);
                        m_particleResizeHandle = side;
                        m_particleResizeIndex = resource;
                        m_particleResizeStart = QRect(r.x, r.y, r.particleAreaW, r.particleAreaH);
                        m_particleResizeStartMouse = m_view->mapToScene(where);
                        m_particleResizeChanged = false;
                        const Qt::CursorShape shape = (side % 4 == 0)
                            ? Qt::SizeFDiagCursor : ((side % 2 == 0)
                                ? Qt::SizeBDiagCursor : ((side == 1 || side == 5)
                                    ? Qt::SizeVerCursor : Qt::SizeHorCursor));
                        m_view->viewport()->setCursor(shape);
                        return true;
                    }
                }
            }
            if (mouse->button() == Qt::LeftButton) {
                m_dragResourceIndex = -1;
                m_dragBefore.clear();
                // itemAt() can return the huge tilemap overlay or camera
                // frame, both of which reject mouse buttons. Look for a
                // genuinely interactive sprite/handle instead.
                QGraphicsItem *clicked = nullptr;
                const QList<QGraphicsItem *> under = m_view->items(where);
                for (QGraphicsItem *candidate : under) {
                    // Locked backgrounds often cover the entire world. Treat
                    // them as empty space for beginning a sprite marquee.
                    const QVariant idData = candidate->data(0);
                    if (idData.isValid()) {
                        const int id = idData.toInt();
                        if (id >= 0 && id < m_sceneItems.size()
                            && m_sceneItems[id] == candidate
                            && m_resources[id].kind == QStringLiteral("background")
                            && m_resources[id].locked)
                            continue;
                    }
                    if ((candidate->acceptedMouseButtons() & Qt::LeftButton)
                        && (candidate->flags() & (QGraphicsItem::ItemIsMovable
                                                 | QGraphicsItem::ItemIsSelectable))) {
                        clicked = candidate;
                        break;
                    }
                }
                if (!clicked) {
                    // Empty-space marquee; do not let QGraphicsView start a
                    // competing native rubber-band selection.
                    m_marqueeSelecting = true;
                    m_marqueeAdditive = (mouse->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier)) != Qt::NoModifier;
                    m_marqueeStartView = where;
                    m_marqueeStartScene = m_view->mapToScene(where);
                    QPen border(m_theme.accent, 1);
                    border.setCosmetic(true); // same width at every zoom
                    border.setJoinStyle(Qt::MiterJoin); // square corners
                    QColor tint = m_theme.accent;
                    tint.setAlpha(38);
                    m_marqueeRect = m_scene->addRect(QRectF(m_marqueeStartScene,
                        m_marqueeStartScene), border, QBrush(tint));
                    m_marqueeRect->setZValue(20000);
                    m_marqueeRect->setAcceptedMouseButtons(Qt::NoButton);
                    m_view->viewport()->setCursor(Qt::CrossCursor);
                    return true;
                }
                // Clicking an already-selected canvas sprite may not emit
                // selectionChanged. Still reveal its correct tree alias.
                if (clicked->data(0).isValid()) {
                    const int id = clicked->data(0).toInt();
                    if (id >= 0 && id < m_resources.size()) {
                        const Resource &r = m_resources.at(id);
                        const QString group = (r.kind == QStringLiteral("sprite")
                            && r.objectType != QStringLiteral("decoration"))
                            ? QStringLiteral("gameobject") : r.kind;
                        for (QTreeWidgetItemIterator it(m_resourceTree); *it; ++it) {
                            QTreeWidgetItem *entry = *it;
                            if (entry->data(0, Qt::UserRole).isValid()
                                && entry->data(0, Qt::UserRole).toInt() == id
                                && entry->data(0, Qt::UserRole + 1).toString() == group) {
                                QSignalBlocker block(m_resourceTree);
                                if (entry->parent()) entry->parent()->setExpanded(true);
                                m_resourceTree->setCurrentItem(entry);
                                m_resourceTree->scrollToItem(entry);
                                break;
                            }
                        }
                    }
                }
                // Qt's native scene movement moves *all* selected sprites.
                // Take just one undo snapshot for the entire group drag.
                if (clicked->data(0).isValid()
                    && clicked->flags().testFlag(QGraphicsItem::ItemIsMovable)) {
                    const int index = clicked->data(0).toInt();
                    if (index >= 0 && index < m_resources.size()) {
                        m_dragResourceIndex = index;
                        m_dragResourceStart = QPoint(m_resources[index].x, m_resources[index].y);
                        m_dragBefore = m_resources;
                        // Explicit group movement avoids Qt dropping the other
                        // selected sprites when pressing the first one. Capture
                        // one world-space delta for all unlocked members.
                        if (clicked->isSelected() && m_scene->selectedItems().size() > 1) {
                            m_groupDragStarts.clear();
                            for (QGraphicsItem *member : m_scene->selectedItems()) {
                                if (member && member->data(0).isValid()
                                    && member->flags().testFlag(QGraphicsItem::ItemIsMovable)) {
                                    const int id = member->data(0).toInt();
                                    if (id >= 0 && id < m_sceneItems.size()
                                        && m_sceneItems[id] == member)
                                        m_groupDragStarts.insert(id, member->pos());
                                }
                            }
                            if (m_groupDragStarts.size() > 1) {
                                m_groupDragActive = true;
                                m_groupDragStartView = where;
                                return true; // handle press/move/release ourselves
                            }
                            m_groupDragStarts.clear();
                        }
                    }
                }
            }
        }
        if (event->type() == QEvent::MouseMove) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            const QPoint next = mouse->position().toPoint();
            if (m_particleResizeHandle >= 0 &&
                m_particleResizeIndex >= 0 && m_particleResizeIndex < m_resources.size()) {
                // Drag handles operate in WORLD coordinates, never screen pixels.
                const QPointF delta = m_view->mapToScene(next) - m_particleResizeStartMouse;
                const int step = m_snap->isChecked()
                    ? m_snapStep->currentText().section(QLatin1Char(' '), 0, 0).toInt() : 0;
                const auto snapped = [step](qreal coordinate) {
                    const int pixel = qRound(coordinate);
                    return step > 0 ? qRound(double(pixel) / step) * step : pixel;
                };
                const QRect start = m_particleResizeStart;
                int left = start.left(), top = start.top();
                int right = start.x() + start.width();
                int bottom = start.y() + start.height();
                const int side = m_particleResizeHandle;
                const bool changeLeft = side == 0 || side == 6 || side == 7;
                const bool changeRight = side == 2 || side == 3 || side == 4;
                const bool changeTop = side == 0 || side == 1 || side == 2;
                const bool changeBottom = side == 4 || side == 5 || side == 6;
                if (changeLeft) left = qBound(qMax(0, right - 2048),
                    snapped(start.left() + delta.x()), right - 8);
                if (changeRight) right = qBound(left + 8,
                    snapped(start.x() + start.width() + delta.x()),
                    qMin(left + 2048, qMax(m_worldWidth->value(), left + 8)));
                if (changeTop) top = qBound(qMax(0, bottom - 2048),
                    snapped(start.top() + delta.y()), bottom - 8);
                if (changeBottom) bottom = qBound(top + 8,
                    snapped(start.y() + start.height() + delta.y()),
                    qMin(top + 2048, qMax(m_worldHeight->value(), top + 8)));
                Resource &r = m_resources[m_particleResizeIndex];
                if (r.x == left && r.y == top && r.particleAreaW == right - left &&
                    r.particleAreaH == bottom - top) return true;
                if (!m_particleResizeChanged) {
                    rememberResourceEdit(); // One Ctrl+Z entry for the complete drag.
                    m_particleResizeChanged = true;
                }
                r.x = left; r.y = top;
                r.particleAreaW = right - left;
                r.particleAreaH = bottom - top;
                if (m_particleResizeIndex < m_sceneItems.size() && m_sceneItems[m_particleResizeIndex]) {
                    // Avoid re-entering syncFromSceneItem() while the resize
                    // drag is updating the origin and rebuilding handles.
                    const bool wasLoading = m_loading;
                    m_loading = true;
                    m_sceneItems[m_particleResizeIndex]->setPos(r.x, r.y);
                    m_loading = wasLoading;
                }
                refreshObjectHitbox();
                refreshProperties();
                setDirty();
                return true;
            }
            if (m_middlePanning) {
                const QPoint delta = next - m_panLastPos;
                if (!delta.isNull()) m_worldPanMoved = true;
                m_panLastPos = next;
                m_view->horizontalScrollBar()->setValue(
                    m_view->horizontalScrollBar()->value() - delta.x());
                m_view->verticalScrollBar()->setValue(
                    m_view->verticalScrollBar()->value() - delta.y());
                return true;
            }
            if (m_groupDragActive) {
                const QPointF offset = m_view->mapToScene(next)
                    - m_view->mapToScene(m_groupDragStartView);
                QPointF delta = offset;
                const int step = m_snap->isChecked()
                    ? m_snapStep->currentText().section(QLatin1Char(' '), 0, 0).toInt()
                    : 0;
                if (step > 0 && m_groupDragStarts.contains(m_dragResourceIndex)) {
                    const QPointF anchor = m_groupDragStarts.value(m_dragResourceIndex);
                    delta = QPointF(qRound((anchor.x() + offset.x()) / step) * step,
                                    qRound((anchor.y() + offset.y()) / step) * step) - anchor;
                }
                for (auto it = m_groupDragStarts.constBegin(); it != m_groupDragStarts.constEnd(); ++it) {
                    if (it.key() >= 0 && it.key() < m_sceneItems.size()
                        && m_sceneItems[it.key()])
                        m_sceneItems[it.key()]->setPos(it.value() + delta);
                }
                return true;
            }
            if (m_marqueeSelecting) {
                if (m_marqueeRect) {
                    const QPointF current = m_view->mapToScene(next);
                    m_marqueeRect->setRect(QRectF(m_marqueeStartScene,
                                                 current).normalized());
                }
                return true;
            }
            if (m_panningCamera) {
                const QPointF lastWorld = m_view->mapToScene(m_panLastPos);
                const QPointF nowWorld = m_view->mapToScene(next);
                const QPointF delta = nowWorld - lastWorld;
                m_panLastPos = next;
                m_cameraX->setValue(qBound(0, m_cameraX->value() + qRound(delta.x()),
                                          m_cameraX->maximum()));
                m_cameraY->setValue(qBound(0, m_cameraY->value() + qRound(delta.y()),
                                          m_cameraY->maximum()));
                return true;
            }
        }
        if (event->type() == QEvent::MouseButtonRelease) {
            auto *mouse = static_cast<QMouseEvent *>(event);
            if (mouse->button() == Qt::MiddleButton && m_middlePanning) {
                m_middlePanning = false;
                if (m_worldPanMoved) setDirty();
                m_worldPanMoved = false;
                m_view->viewport()->setCursor(m_spaceHeld ? Qt::OpenHandCursor : Qt::ArrowCursor);
                return true;
            }
            if (mouse->button() == Qt::LeftButton && m_particleResizeHandle >= 0) {
                m_particleResizeHandle = -1;
                m_particleResizeIndex = -1;
                m_particleResizeChanged = false;
                m_view->viewport()->setCursor(m_spaceHeld ? Qt::OpenHandCursor : Qt::ArrowCursor);
                return true;
            }
            if (mouse->button() == Qt::LeftButton && m_marqueeSelecting) {
                m_marqueeSelecting = false;
                const QPoint finish = mouse->position().toPoint();
                const QRectF selection = QRectF(m_marqueeStartScene,
                    m_view->mapToScene(finish)).normalized();
                if (m_marqueeRect) {
                    m_scene->removeItem(m_marqueeRect);
                    delete m_marqueeRect;
                    m_marqueeRect = nullptr;
                }
                m_view->viewport()->setCursor(m_spaceHeld ? Qt::OpenHandCursor : Qt::ArrowCursor);
                // An empty click clears selection. A drag intersects whole
                // sprite rectangles; spline handles and tilemap don't count.
                const bool dragged = (finish - m_marqueeStartView).manhattanLength()
                    >= QApplication::startDragDistance();
                {
                    QSignalBlocker block(m_scene);
                    if (!m_marqueeAdditive) m_scene->clearSelection();
                    if (dragged) {
                        for (int id = 0; id < m_sceneItems.size(); ++id) {
                            QGraphicsItem *item = m_sceneItems[id];
                            // A locked background is a visual reference, not
                            // a participant in multi-sprite group movement.
                            if (item && m_resources[id].kind == QStringLiteral("background")
                                && m_resources[id].locked) continue;
                            if (item && item->flags().testFlag(QGraphicsItem::ItemIsSelectable)
                                && item->sceneBoundingRect().intersects(selection))
                                item->setSelected(true);
                        }
                    }
                }
                syncCanvasSelection();
                return true;
            }
            if (mouse->button() == Qt::LeftButton && m_panningCamera) {
                m_panningCamera = false;
                m_view->viewport()->setCursor(m_spaceHeld ? Qt::OpenHandCursor : Qt::ArrowCursor);
                return true;
            }
            if (mouse->button() == Qt::LeftButton && m_dragResourceIndex >= 0) {
                m_groupDragActive = false;
                m_groupDragStarts.clear();
                // Include *every* moved resource, not only the sprite the
                // user grabbed. One Ctrl+Z reverses the complete group move.
                bool changed = false;
                if (m_dragBefore.size() == m_resources.size()) {
                    for (int i = 0; i < m_resources.size(); ++i) {
                        if (m_dragBefore[i].x != m_resources[i].x
                            || m_dragBefore[i].y != m_resources[i].y) {
                            changed = true;
                            break;
                        }
                    }
                }
                if (changed) {
                    if (m_undoResources.size() >= 64) {
                        m_undoResources.removeFirst();
                        m_undoResourceSplines.removeFirst();
                        m_undoResourceAdventures.removeFirst();
                    }
                    m_undoResources.append(m_dragBefore);
                    m_undoResourceSplines.append(m_splinePaths);
                    m_undoResourceAdventures.append(m_adventure);
                    m_redoResources.clear();
                    m_redoResourceSplines.clear();
                    m_redoResourceAdventures.clear();
                }
                m_dragResourceIndex = -1;
                m_dragBefore.clear();
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}


// Inventory pickup TYPES are project-wide, regardless of whether a placed
// object stays collected. A world may have no NPCs or its own Adventure items,
// yet the player still needs to see backpack items from another world.
// Read only saved source worlds; never modify any .sbgm file here.
static QJsonArray persistentItemsFromSavedWorlds(const QString &root)
{
    QMap<int,QJsonObject> byKind;
    const QDir dir(root);
    for(const QString &world:dir.entryList({QStringLiteral("*.sbgm")},QDir::Files,QDir::Name)) {
        QFile file(dir.filePath(world));
        if(!file.open(QIODevice::ReadOnly)||file.size()>16*1024*1024)continue;
        const QJsonObject design=QJsonDocument::fromJson(file.readAll()).object();
        if(design.value(QStringLiteral("format")).toString()!=QStringLiteral("SIDBOX-GAME-DESIGN"))continue;
        const QJsonArray items=design.value(QStringLiteral("adventure")).toObject().value(QStringLiteral("items")).toArray();
        for(const QJsonValue &value:design.value(QStringLiteral("resources")).toArray()) {
            const QJsonObject resource=value.toObject();
            const QJsonObject object=resource.value(QStringLiteral("gameObject")).toObject();
            if(object.value(QStringLiteral("type")).toString()!=QStringLiteral("collectable") ||
               !object.value(QStringLiteral("pickupShowInventory")).toBool(false))continue;
            const int kind=object.value(QStringLiteral("pickupKind")).toInt();
            if(kind<1 || kind>255 || byKind.contains(kind))continue;
            QJsonObject item;
            for(const QJsonValue &v:items) {
                const QJsonObject candidate=v.toObject();
                if(candidate.value(QStringLiteral("pickupKind")).toInt()==kind) {
                    item=candidate;break;
                }
            }
            if(item.isEmpty()){
                item.insert(QStringLiteral("name"),kind==1?QStringLiteral("Coins"):
                    resource.value(QStringLiteral("name")).toString(QStringLiteral("Item")));
                item.insert(QStringLiteral("pickupKind"),kind);
                item.insert(QStringLiteral("capacity"),65535);
                item.insert(QStringLiteral("initial"),0);
                item.insert(QStringLiteral("icon"),65535);
            }
            // The item's name, 8x8 cell/stamp indices and chosen PPB belong
            // to the backpack across worlds, not to any destination map.
            // Resolve world-local resource UUIDs to the ORIGINAL project PPB
            // filename while we still have the source world's .sbgm.
            item.insert(QStringLiteral("initial"),0);
            QString atlasId=item.value(QStringLiteral("iconAtlasId")).toString();
            if(atlasId.isEmpty())
                atlasId=design.value(QStringLiteral("adventure")).toObject()
                              .value(QStringLiteral("skinAtlasId")).toString();
            QString atlasPath;
            for(const QJsonValue &sourceValue:design.value(QStringLiteral("resources")).toArray()) {
                const QJsonObject source=sourceValue.toObject();
                if(source.value(QStringLiteral("id")).toString()==atlasId && !atlasId.isEmpty()) {
                    atlasPath=source.value(QStringLiteral("path")).toString();
                    break;
                }
            }
            // A pickup without a separate Inventory Items artwork selection
            // may use its own sprite sheet. Do not make the designer duplicate
            // that PPB as a Tile Atlas in every new world.
            if(atlasPath.isEmpty()) {
                atlasPath=resource.value(QStringLiteral("path")).toString();
                const int size=resource.value(QStringLiteral("cellWidth")).toInt(8);
                item.insert(QStringLiteral("iconTileSize"),qBound(4,size,64));
                item.insert(QStringLiteral("icon"),resource.value(QStringLiteral("frame")).toInt(0));
                item.insert(QStringLiteral("icon2x2"),false);
                item.remove(QStringLiteral("iconCells"));
            }
            item.remove(QStringLiteral("iconAtlasId")); // never carry source UUIDs
            if(!atlasPath.isEmpty())item.insert(QStringLiteral("iconPpbPath"),atlasPath);
            byKind.insert(kind,item);
        }
    }
    QJsonArray result;
    for(auto it=byKind.cbegin();it!=byKind.cend();++it)result.append(it.value());
    return result;
}

// Advanced Platformer adventure definitions are stored only in .sbgm.
// Ordinary placed Sprite resources become NPCs by stable resource ID.
bool SidboxGameDesigner::hasAdventure() const
{
    // Adventure presentation belongs to each WORLD, even when there are no
    // NPCs or dialogue nodes yet. A saved dialogue atlas or positioned box
    // must generate world-specific setup instead of the no-story stub;
    // otherwise the shared Adventure runtime keeps another world's style.
    return !persistentItemsFromSavedWorlds(QFileInfo(m_filePath).absolutePath()).isEmpty()
        || !m_adventure.value(QStringLiteral("items")).toArray().isEmpty()
        || !m_adventure.value(QStringLiteral("nodes")).toArray().isEmpty()
        || !m_adventure.value(QStringLiteral("npcs")).toArray().isEmpty()
        || !m_adventure.value(QStringLiteral("skinAtlasId")).toString().isEmpty()
        || m_adventure.contains(QStringLiteral("dialogX"))
        || m_adventure.contains(QStringLiteral("dialogY"))
        || m_adventure.contains(QStringLiteral("dialogWidth"))
        || m_adventure.contains(QStringLiteral("dialogHeight"));
}
void SidboxGameDesigner::openAdventureEditor(const QString &focusNpcSpriteId)
{
    QVector<GameAdventureAsset> sprites, atlases;
    for (const Resource &r : m_resources) {
        if (r.path.isEmpty()) continue;
        if (r.kind != QStringLiteral("sprite") && r.kind != QStringLiteral("tileatlas")) continue;
        GameAdventureAsset a; a.id = r.id; a.name = r.name; a.path = resolvedPath(r.path);
        a.x = r.x; a.y = r.y; a.flipX = r.objectFlipX; a.flipY = r.objectFlipY;
        const QImage image = cachedImage(a.path);
        a.width = r.cellWidth > 0 ? r.cellWidth : image.width();
        a.height = r.cellHeight > 0 ? r.cellHeight : image.height();
        a.symbol = spriteSymbol(r);
        a.atlasFrames = (a.width > 0 && a.height > 0)
            ? qBound(1, (image.width() / a.width) * (image.height() / a.height), 256) : 1;
        if (r.kind == QStringLiteral("sprite") && r.objectType == QStringLiteral("decoration")
            && r.plane == QStringLiteral("foreground") && r.name.compare(QStringLiteral("player"),Qt::CaseInsensitive))
            sprites.append(a);
        if (r.kind == QStringLiteral("tileatlas") || r.kind == QStringLiteral("sprite"))
            atlases.append(a);
    }
    QVector<GameAdventureAsset> worldObjects;
    int slot = 0;
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")
            || r.objectType == QStringLiteral("collectable")) continue;
        GameAdventureAsset object; object.id = r.id; object.name = r.name;
        object.worldSlot = slot++; worldObjects.append(object);
    }
    QJsonObject edited = m_adventure;
    QVector<GameAdventureAsset> collectables;
    for (const Resource &r : m_resources) {
        if (r.kind == QStringLiteral("sprite") && r.objectType == QStringLiteral("collectable")) {
            GameAdventureAsset a;
            a.id = r.id; a.name = r.name; a.pickupKind = r.pickupKind;
            collectables.append(a);
        }
    }
    if (!editGameAdventure(this, &edited, sprites, atlases, worldObjects, collectables,
                           activePalette(QStringLiteral("foreground")), m_filePath,
                           focusNpcSpriteId)) return;
    m_adventure = edited;
    // Refresh tree labels immediately when NPCs are added/deleted.
    refreshResources();
    setDirty(true);
}
bool SidboxGameDesigner::exportAdventure(QString *error)
{
    if (!hasAdventure()) {
        // A world without a story must not retain a previous world's generated
        // gameadventure.c/.h. Even these no-story declarations live in rules.
        const QDir templates(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
        const QString folder = QDir(QFileInfo(m_filePath).absolutePath())
                                   .filePath(QStringLiteral("gamehelpers"));
        if (!QDir().mkpath(folder)) {
            if (error) *error = tr("Cannot create Adventure output directory: %1").arg(folder);
            return false;
        }
        for (const QString &ext : {QStringLiteral(".h"), QStringLiteral(".c")}) {
            const QString destination = QDir(folder).filePath(QStringLiteral("gameadventure") + ext);
            QFile old(destination);
            if (old.exists()) {
                if (!old.open(QIODevice::ReadOnly)
                    || !old.read(150).contains("GENERATED by GamerGirl")) {
                    if (error) *error = tr("Refusing to replace a non-generated Adventure file: %1").arg(destination);
                    return false;
                }
            }
            QFile input(templates.filePath(QStringLiteral("gameadventureempty.rule")
                               + (ext == QStringLiteral(".h") ? QStringLiteral("h") : QStringLiteral("c"))));
            if (!input.open(QIODevice::ReadOnly)) {
                if (error) *error = tr("Missing no-story Adventure rule: %1").arg(input.fileName());
                return false;
            }
            const QByteArray bytes = input.readAll();
            QSaveFile output(destination);
            if (!output.open(QIODevice::WriteOnly) || output.write(bytes) != bytes.size()
                || !output.commit()) {
                output.cancelWriting();
                if (error) *error = tr("Could not write empty Adventure code: %1").arg(destination);
                return false;
            }
        }
        return true;
    }
    QVector<GameAdventureAsset> sprites, atlases;
    for (const Resource &r : m_resources) {
        if (r.path.isEmpty() || (r.kind != QStringLiteral("sprite") && r.kind != QStringLiteral("tileatlas"))) continue;
        GameAdventureAsset a; a.id = r.id; a.name = r.name; a.path = resolvedPath(r.path);
        a.x = r.x; a.y = r.y; a.flipX = r.objectFlipX; a.flipY = r.objectFlipY;
        const QImage image = cachedImage(a.path);
        a.width = r.cellWidth > 0 ? r.cellWidth : image.width();
        a.height = r.cellHeight > 0 ? r.cellHeight : image.height();
        a.symbol = spriteSymbol(r);
        a.atlasFrames = (a.width > 0 && a.height > 0)
            ? qBound(1, (image.width() / a.width) * (image.height() / a.height), 256) : 1;
        if (r.kind == QStringLiteral("sprite") && r.objectType == QStringLiteral("decoration")
            && r.plane == QStringLiteral("foreground")) sprites.append(a);
        // Inventory icons can use ANY PPB registered in this world, not just
        // the dialogue skin or a tilemap atlas.
        if (r.kind == QStringLiteral("sprite") || r.kind == QStringLiteral("tileatlas"))
            atlases.append(a);
    }
    QVector<GameAdventureAsset> worldObjects;
    int slot = 0;
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")
            || r.objectType == QStringLiteral("collectable")) continue;
        GameAdventureAsset object; object.id = r.id; object.name = r.name;
        object.worldSlot = slot++; worldObjects.append(object);
    }
    QJsonObject effectiveAdventure=m_adventure;
    QJsonArray effectiveItems=effectiveAdventure.value(QStringLiteral("items")).toArray();
    // Append only, preserving existing NPC dialogue/quest inventory indices.
    // Inventory pickup TYPES travel between worlds independently of whether
    // the placed collectible respawns when its original world is revisited.
    for(const QJsonValue &value:persistentItemsFromSavedWorlds(QFileInfo(m_filePath).absolutePath())) {
        const QJsonObject item=value.toObject();
        const int kind=item.value(QStringLiteral("pickupKind")).toInt();
        bool exists=false;
        for(const QJsonValue &v:effectiveItems)
            if(v.toObject().value(QStringLiteral("pickupKind")).toInt()==kind) {exists=true;break;}
        if(!exists)effectiveItems.append(item);
    }
    if(effectiveItems.size()>64){
        if(error)*error=tr("Project-wide persistent inventory exceeds 64 item types.");
        return false;
    }
    effectiveAdventure.insert(QStringLiteral("items"),effectiveItems);
    return generateGameAdventure(effectiveAdventure, QFileInfo(m_filePath).absolutePath(), sprites,
                                 atlases, worldObjects,
                                 QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")), error);
}

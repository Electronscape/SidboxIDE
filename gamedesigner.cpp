#include "gamedesigner.h"
#include "ppbcodec.h"
#include "pngpaletteimport.h"
#include "gamepalette.h"
#include "gamepaletteeditor.h"
#include "gamecodegen.h"
#include "gamemainownership.h"

#include <QCheckBox>
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
#include <QScrollBar>
#include <QSettings>
#include <QSizePolicy>
#include <QListView>
#include <QStringList>
#include <QSignalBlocker>
#include <QTextStream>
#include <QSpinBox>
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
    return QIcon(QStringLiteral(":/icons/") + fileName);
}

constexpr int LCD_WIDTH = 480;
constexpr int LCD_HEIGHT = 320;
constexpr int MAX_WORLD = 16384; // Editor guard only; NOT a firmware/world-size claim.

// ZIP backup writer using the zlib already linked by CoderGirl. Entries are
// streamed, not buffered in RAM, and are compatible with Ark/7-Zip/unzip.
// Standard ZIP32 intentionally rejects archives exceeding ZIP32 limits.
struct GameBackupZipEntry {
    QByteArray name;
    quint32 crc = 0;
    quint32 compressed = 0;
    quint32 original = 0;
    quint32 offset = 0;
};

bool gameBackupZip16(QIODevice *out, quint16 value)
{
    const char b[2] = {char(value & 255), char((value >> 8) & 255)};
    return out->write(b, 2) == 2;
}
bool gameBackupZip32(QIODevice *out, quint32 value)
{
    const char b[4] = {char(value & 255), char((value >> 8) & 255),
                       char((value >> 16) & 255), char((value >> 24) & 255)};
    return out->write(b, 4) == 4;
}

bool gameBackupWriteZip(const QString &backupFolder, const QString &zipPath,
                        QString *error)
{
    QDir root(backupFolder);
    QStringList files;
    QDirIterator iterator(backupFolder, QDir::Files | QDir::NoSymLinks,
                          QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        const QString relative = QDir::fromNativeSeparators(root.relativeFilePath(iterator.next()));
        if (relative == QStringLiteral("..") || relative.startsWith(QStringLiteral("../"))
            || QDir::isAbsolutePath(relative)) {
            if (error) *error = QObject::tr("Invalid file path inside backup: %1").arg(relative);
            return false;
        }
        files << relative;
    }
    files.sort();
    if (files.size() > 65535) {
        if (error) *error = QObject::tr("Too many files for ZIP backup.");
        return false;
    }
    QSaveFile output(zipPath);
    if (!output.open(QIODevice::WriteOnly)) {
        if (error) *error = QObject::tr("Cannot open ZIP archive: %1").arg(zipPath);
        return false;
    }
    QVector<GameBackupZipEntry> entries;
    char compressedBlock[65536];
    auto fail = [&](const QString &why) {
        if (error) *error = why;
        output.cancelWriting();
        return false;
    };
    for (const QString &relative : files) {
        QFile input(root.filePath(relative));
        if (!input.open(QIODevice::ReadOnly))
            return fail(QObject::tr("Cannot read backup file: %1").arg(relative));
        const QByteArray name = relative.toUtf8();
        if (name.size() > 65535 || input.size() > std::numeric_limits<quint32>::max()
            || output.pos() > std::numeric_limits<quint32>::max())
            return fail(QObject::tr("ZIP32 limits exceeded by %1").arg(relative));
        GameBackupZipEntry entry;
        entry.name = name;
        entry.offset = quint32(output.pos());
        // Local file header: UTF-8 filenames and a data descriptor after data.
        if (!gameBackupZip32(&output, 0x04034b50) || !gameBackupZip16(&output, 20)
            || !gameBackupZip16(&output, 0x0808) || !gameBackupZip16(&output, 8)
            || !gameBackupZip16(&output, 0) || !gameBackupZip16(&output, 0)
            || !gameBackupZip32(&output, 0) || !gameBackupZip32(&output, 0)
            || !gameBackupZip32(&output, 0) || !gameBackupZip16(&output, quint16(name.size()))
            || !gameBackupZip16(&output, 0) || output.write(name) != name.size())
            return fail(QObject::tr("Cannot write ZIP header for %1").arg(relative));
        z_stream stream{};
        if (deflateInit2(&stream, Z_DEFAULT_COMPRESSION, Z_DEFLATED,
                         -MAX_WBITS, 8, Z_DEFAULT_STRATEGY) != Z_OK)
            return fail(QObject::tr("ZIP compressor initialization failed."));
        quint32 crc = quint32(crc32(0L, Z_NULL, 0));
        quint64 count = 0;
        quint64 packed = 0;
        bool ok = true;
        while (!input.atEnd() && ok) {
            const QByteArray data = input.read(65536);
            if (data.isEmpty()) { ok = false; break; }
            crc = quint32(crc32(crc, reinterpret_cast<const Bytef *>(data.constData()), uInt(data.size())));
            count += quint64(data.size());
            stream.next_in = reinterpret_cast<Bytef *>(const_cast<char *>(data.constData()));
            stream.avail_in = uInt(data.size());
            do {
                stream.next_out = reinterpret_cast<Bytef *>(compressedBlock);
                stream.avail_out = sizeof(compressedBlock);
                if (deflate(&stream, Z_NO_FLUSH) != Z_OK) { ok = false; break; }
                const qint64 produced = qint64(sizeof(compressedBlock) - stream.avail_out);
                if (output.write(compressedBlock, produced) != produced) { ok = false; break; }
                packed += quint64(produced);
            } while (stream.avail_in > 0 || stream.avail_out == 0);
        }
        if (input.error() != QFile::NoError) ok = false;
        if (ok) {
            int result = Z_OK;
            do {
                stream.next_out = reinterpret_cast<Bytef *>(compressedBlock);
                stream.avail_out = sizeof(compressedBlock);
                result = deflate(&stream, Z_FINISH);
                if (result != Z_OK && result != Z_STREAM_END) { ok = false; break; }
                const qint64 produced = qint64(sizeof(compressedBlock) - stream.avail_out);
                if (output.write(compressedBlock, produced) != produced) { ok = false; break; }
                packed += quint64(produced);
            } while (result != Z_STREAM_END);
        }
        deflateEnd(&stream);
        if (!ok || count > std::numeric_limits<quint32>::max()
            || packed > std::numeric_limits<quint32>::max()
            || output.pos() > std::numeric_limits<quint32>::max())
            return fail(QObject::tr("Could not compress backup file: %1").arg(relative));
        entry.crc = crc;
        entry.compressed = quint32(packed);
        entry.original = quint32(count);
        if (!gameBackupZip32(&output, 0x08074b50) || !gameBackupZip32(&output, entry.crc)
            || !gameBackupZip32(&output, entry.compressed)
            || !gameBackupZip32(&output, entry.original))
            return fail(QObject::tr("Could not finish ZIP entry: %1").arg(relative));
        entries.append(entry);
    }
    if (output.pos() > std::numeric_limits<quint32>::max())
        return fail(QObject::tr("ZIP archive exceeds 4 GiB ZIP32 limit."));
    const quint32 centralOffset = quint32(output.pos());
    for (const GameBackupZipEntry &entry : entries) {
        if (!gameBackupZip32(&output, 0x02014b50) || !gameBackupZip16(&output, 20)
            || !gameBackupZip16(&output, 20) || !gameBackupZip16(&output, 0x0808)
            || !gameBackupZip16(&output, 8) || !gameBackupZip16(&output, 0)
            || !gameBackupZip16(&output, 0) || !gameBackupZip32(&output, entry.crc)
            || !gameBackupZip32(&output, entry.compressed)
            || !gameBackupZip32(&output, entry.original)
            || !gameBackupZip16(&output, quint16(entry.name.size()))
            || !gameBackupZip16(&output, 0) || !gameBackupZip16(&output, 0)
            || !gameBackupZip16(&output, 0) || !gameBackupZip16(&output, 0)
            || !gameBackupZip32(&output, 0) || !gameBackupZip32(&output, entry.offset)
            || output.write(entry.name) != entry.name.size())
            return fail(QObject::tr("Could not write ZIP directory."));
    }
    if (output.pos() - centralOffset > std::numeric_limits<quint32>::max())
        return fail(QObject::tr("ZIP directory exceeds ZIP32 limit."));
    const quint32 centralLength = quint32(output.pos() - centralOffset);
    if (!gameBackupZip32(&output, 0x06054b50) || !gameBackupZip16(&output, 0)
        || !gameBackupZip16(&output, 0)
        || !gameBackupZip16(&output, quint16(entries.size()))
        || !gameBackupZip16(&output, quint16(entries.size()))
        || !gameBackupZip32(&output, centralLength)
        || !gameBackupZip32(&output, centralOffset)
        || !gameBackupZip16(&output, 0))
        return fail(QObject::tr("Cannot finish ZIP archive."));
    if (!output.commit()) {
        if (error) *error = QObject::tr("Cannot save ZIP archive: %1").arg(zipPath);
        return false;
    }
    return true;
}

void gameBackupTrimArchives(const QDir &location)
{
    // Sort by timestamped filename; the .history/ backups are independent.
    // Leave legacy Stage 3.4 folder backups untouched for manual recovery.
    const QStringList archives = location.entryList({QStringLiteral("*.zip")},
        QDir::Files, QDir::Name);
    for (int i = 0; i < archives.size() - 20; ++i)
        QFile::remove(location.filePath(archives.at(i)));
}

// Flat, theme-aware dropdown with a visible chevron. Drawing the arrow in
// foreground avoids losing it to platform-specific Qt style-sheet rendering.
class GameComboBox final : public QComboBox
{
public:
    using QComboBox::QComboBox;
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
        : m_map(map), m_atlas(atlas)
    {
        setZValue(2); // Above background references, below movable sprites.
        setAcceptedMouseButtons(Qt::NoButton);
        setFlag(QGraphicsItem::ItemUsesExtendedStyleOption, true);
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

// Editor-only forced-CLUT colour preview. SIDBOX may use the ARGB alpha
// byte for DMA2D blending, but some imported .pal files leave alpha = 0 for
// many *nonzero* colour indices. Passing those bytes straight to QImage would
// make sprites vanish instead of showing the selected indexed RGB colours.
// Keep index 0 transparent on the foreground plane; show all remaining colour
// indices as opaque for this COLOUR preview. The actual .pal and PPB bytes are
// never changed. Properties warn when hardware alpha may differ.
QVector<QRgb> colourPreviewBank(const QVector<QRgb> &bank, bool foreground)
{
    QVector<QRgb> display = bank;
    for (int i = 0; i < display.size(); ++i) {
        const QRgb colour = display.at(i);
        display[i] = qRgba(qRed(colour), qGreen(colour), qBlue(colour),
                           foreground && i == 0 ? 0 : 255);
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

SidboxGameDesigner::SidboxGameDesigner(const QString &designFilePath, QWidget *parent)
    : QWidget(parent), m_filePath(QFileInfo(designFilePath).absoluteFilePath())
{
    buildUi();
    if (QFileInfo::exists(m_filePath)) {
        if (!loadDesign()) m_valid = false;
    } else rebuildScene();
    refreshColours();
}

SidboxGameDesigner::~SidboxGameDesigner() = default;
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
    const auto C = [](const QColor &colour) { return ideThemeColorName(colour); };
    setStyleSheet(QStringLiteral(
        "QPushButton, QToolButton, QLineEdit, QSpinBox, QTreeWidget, "
        "QGraphicsView, QFrame, QMenu, QAbstractItemView { border-radius:0px; } "
        "QComboBox { border:1px solid %1; border-radius:0px; "
        "background-color:%2; color:%3; padding:3px 24px 3px 5px; } "
        "QComboBox::drop-down { width:20px; border-left:1px solid %1; "
        "border-radius:0px; background-color:%2; } "
        "QComboBox::down-arrow { image:none; width:0px; height:0px; } "
        "QComboBox QAbstractItemView { border:1px solid %1; border-radius:0px; "
        "background-color:%4; color:%3; selection-background-color:%5; "
        "selection-color:%6; outline:0px; } "
        "QComboBox QAbstractItemView::item:selected { background:%5; color:%6; } "
        "QComboBox:disabled, QLineEdit:disabled, QSpinBox:disabled, "
        "QDoubleSpinBox:disabled { background:%7; color:%8; "
        "border:1px solid %9; } "
        "QComboBox::drop-down:disabled { background:%7; border-left:1px solid %9; } "
        "QPushButton:disabled, QToolButton:disabled { background:%7; color:%8; "
        "border:1px solid %9; } "
        "QCheckBox:disabled, QRadioButton:disabled, QLabel:disabled { color:%8; } "
        "QComboBox QAbstractItemView:disabled { background:%7; color:%8; } ")
        .arg(C(theme.border), C(theme.inputBackground), C(theme.text),
             C(theme.menuBackground), C(theme.accent), C(theme.brightText),
             C(theme.panelBackground),
             C(QColor::fromRgbF(theme.mutedText.redF() * 0.7 + theme.panelBackground.redF() * 0.3,
                               theme.mutedText.greenF() * 0.7 + theme.panelBackground.greenF() * 0.3,
                               theme.mutedText.blueF() * 0.7 + theme.panelBackground.blueF() * 0.3)),
             C(theme.panelBackground)));

    // QComboBox popups can be separate windows on some Qt styles. Colour their
    // view explicitly so neither the desktop theme nor a default palette wins.
    for (QComboBox *combo : findChildren<QComboBox *>()) {
        QPalette colours = combo->palette();
        colours.setColor(QPalette::Base, theme.inputBackground);
        colours.setColor(QPalette::Text, theme.text);
        colours.setColor(QPalette::Button, theme.inputBackground);
        colours.setColor(QPalette::ButtonText, theme.text);
        colours.setColor(QPalette::Highlight, theme.accent);
        colours.setColor(QPalette::HighlightedText, theme.brightText);
        const QColor disabledText = QColor::fromRgbF(
            theme.mutedText.redF() * 0.7 + theme.panelBackground.redF() * 0.3,
            theme.mutedText.greenF() * 0.7 + theme.panelBackground.greenF() * 0.3,
            theme.mutedText.blueF() * 0.7 + theme.panelBackground.blueF() * 0.3);
        colours.setColor(QPalette::Disabled, QPalette::Text, disabledText);
        colours.setColor(QPalette::Disabled, QPalette::ButtonText, disabledText);
        colours.setColor(QPalette::Disabled, QPalette::Base, theme.panelBackground);
        colours.setColor(QPalette::Disabled, QPalette::Button, theme.panelBackground);
        combo->setPalette(colours);
        if (auto *popup = combo->view()) {
            popup->setPalette(colours);
            popup->setStyleSheet(QStringLiteral(
                "QAbstractItemView { background:%1; color:%2; border:1px solid %3; "
                "border-radius:0px; selection-background-color:%4; selection-color:%5; "
                "outline:0px; } "
                "QAbstractItemView::item:selected { background:%4; color:%5; }")
                .arg(C(theme.menuBackground), C(theme.text), C(theme.border),
                     C(theme.accent), C(theme.brightText)));
        }
    }
    refreshColours();
    refreshObjectHitbox();
}

QString SidboxGameDesigner::filePath() const { return m_filePath; }
void SidboxGameDesigner::setFilePath(const QString &path)
{
    // Retarget paths if the designer file moves to a different directory.
    // Existing asset references must keep resolving to the SAME physical files.
    QStringList absoluteResources;
    for (const auto &r : m_resources)
        absoluteResources.append(r.path.isEmpty() ? QString() : resolvedPath(r.path));
    const QString previousDir = QFileInfo(m_filePath).absolutePath();
    m_filePath = QFileInfo(path).absoluteFilePath();
    for (int i = 0; i < m_resources.size(); ++i)
        if (!absoluteResources.at(i).isEmpty())
            m_resources[i].path = storedPath(absoluteResources.at(i));
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
    if (!palettePath.isEmpty() && QFileInfo(palettePath).suffix().compare(
        QStringLiteral("pal"), Qt::CaseInsensitive) == 0) {
        // Respect Cancel (and failed imports) rather than opening an empty editor.
        if (!dialog.loadFromFile(palettePath)) return;
    }
    dialog.exec();
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
        || base == QStringLiteral(".") || base == QStringLiteral("..")) return;
    const QDir templateFolder(QDir(helperTemplatesRoot()).filePath(category));
    const QString sourceH = templateFolder.filePath(base + QStringLiteral(".h"));
    const QString sourceC = templateFolder.filePath(base + QStringLiteral(".c"));
    QFile hTemplate(sourceH), cTemplate(sourceC);
    if (!hTemplate.open(QIODevice::ReadOnly) || !cTemplate.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Add Helper Code"),
            tr("Cannot read helper template files:\n%1\n%2").arg(sourceH, sourceC));
        return;
    }
    QByteArray header = hTemplate.readAll(), source = cTemplate.readAll();
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
    if (m_showTilemap) {
        m_showTilemap->setEnabled(m_tilemapEnabled);
        if (!m_tilemapEnabled || !m_showTilemap->isChecked()) return;
    } else return;

    if (m_tilemap.atlasPath.isEmpty()) return;
    const QString atlasPath = QDir(QFileInfo(m_filePath).absolutePath())
                                  .absoluteFilePath(m_tilemap.atlasPath);
    SidboxPpb::Picture picture;
    if (!SidboxPpb::read(atlasPath, &picture)) return;
    QImage atlas = picture.indexed;
    if (m_forcePalette && m_forcePalette->isChecked()) {
        const QVector<QRgb> palette = activePalette(QStringLiteral("foreground"));
        if (palette.size() == 256)
            atlas.setColorTable(colourPreviewBank(palette, true));
    }
    // Foreground palette index 0 is transparent on SIDBOX. Do this only
    // for the preview; the PPB file and palette assets are never modified.
    QVector<QRgb> displayPalette = atlas.colorTable();
    if (!displayPalette.isEmpty()) {
        const QRgb zero = displayPalette.at(0);
        displayPalette[0] = qRgba(qRed(zero), qGreen(zero), qBlue(zero), 0);
        atlas.setColorTable(displayPalette);
    }
    m_tilemapOverlayItem = new GameTilemapOverlay(&m_tilemap, atlas);
    m_scene->addItem(m_tilemapOverlayItem);
}

void SidboxGameDesigner::openTilemapEditor()
{
    QVector<QPair<QString, QString>> atlases;
    const QString chosenPath = QDir::cleanPath(resolvedPath(m_tilemap.atlasPath));
    for (const Resource &r : m_resources) {
        // Dedicated PPB-only resource bank. These images are never canvas sprites.
        // The existing atlas referenced by an older project stays selectable
        // even if it still lives under Sprites (no forced migration).
        if (r.kind != QStringLiteral("tileatlas")
            && !(r.kind == QStringLiteral("sprite") && !m_tilemap.atlasPath.isEmpty()
                 && QDir::cleanPath(resolvedPath(r.path)) == chosenPath)) continue;
        if (r.path.isEmpty()) continue;
        const QString path = resolvedPath(r.path);
        if (QFileInfo(path).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) != 0)
            continue;
        bool exists = false;
        for (const auto &atlas : atlases)
            if (QDir::cleanPath(atlas.second) == QDir::cleanPath(path)) { exists = true; break; }
        if (!exists) atlases.append({r.name, path});
    }
    const QString directory = QFileInfo(m_filePath).absolutePath();
    SidboxTilemapEditor editor(m_tilemap, atlases, directory, this);
    editor.setTheme(m_theme);
    // "Save" commits this editor's working copy immediately while keeping
    // the tile editor open. "Apply" still closes and follows the old export
    // prompt; "Cancel" discards changes since the last successful Save.
    const auto applyChanges = [this, &editor](const SidboxTilemap &map, bool saveEvenWithoutExport) -> bool {
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
        // Tilemap dimensions affect neither the designer world nor the physical viewport.
        setDirty();
        const auto answer = QMessageBox::question(
            saveEvenWithoutExport ? static_cast<QWidget *>(&editor) : this,
            tr("Apply Tilemap"),
            tr("Apply these tilemap changes and export the C level files now?\n\n"
               "Yes: Save the game design, export gamelevels/level1.c/.h, "
               "and add any missing tilemap helper files.\n"
               "No: With Save, save the .sbgm (and refresh existing exports); "
               "with Apply to Design, keep the changes in memory."),
            QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
        if (answer == QMessageBox::Yes) {
            const bool needsExport = tilemapBuildFilesMissing();
            if (!saveDesign()) return false;
            if (needsExport && !exportTilemap(false, true)) return false;
        } else if (saveEvenWithoutExport) {
            // Unlike Apply's original "No", Save must persist the .sbgm.
            if (!saveDesign()) return false;
        }
        return true;
    };
    editor.setSaveCallback([&applyChanges](const SidboxTilemap &map) {
        return applyChanges(map, true);
    });
    if (editor.exec() != QDialog::Accepted) return;
    applyChanges(editor.result(), false);
}

bool SidboxGameDesigner::tilemapBuildFilesMissing() const
{
    if (!m_tilemapEnabled) return false;
    const QDir dir(QFileInfo(m_filePath).absolutePath());
    return !QFileInfo::exists(dir.filePath(QStringLiteral("gamelevels/level1.c")))
        || !QFileInfo::exists(dir.filePath(QStringLiteral("gamelevels/level1.h")))
        || !QFileInfo::exists(dir.filePath(QStringLiteral("gamehelpers/gametilemap.c")))
        || !QFileInfo::exists(dir.filePath(QStringLiteral("gamehelpers/gametilemap.h")));
}

bool SidboxGameDesigner::exportTilemapForCompile()
{
    return exportTilemap(false, true);
}

bool SidboxGameDesigner::exportTilemap(bool showMessage, bool includeMissingHelper)
{
    if (!m_tilemapEnabled) return false;
    const QString directory = QFileInfo(m_filePath).absolutePath();
    // Mode is per .sbgm and persists for automatic saves/Update Project.
    // No mode choice during auto-export, so rebuilding stays deterministic.
    bool includeHelper = includeMissingHelper;
    if (showMessage) {
        QMessageBox choice(this);
        choice.setWindowTitle(tr("Export Platformer Tilemap"));
        choice.setText(tr("Choose where the tilemap graphics and collision data live."));
        choice.setInformativeText(tr("Embedded .c: map bytes become part of the .app.\n"
            "SD .map: map bytes load from gamelevels/level1.map at runtime.\n"
            "Both generate gamelevels/level1.c/.h for the shared game_level1 API.\n"
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
    // Custom collision stamps require the v3 SD map parser and per-pixel
    // surface sampler. Never silently replace a programmer's custom helpers.
    // Offer an explicit backup-and-upgrade when old V1 helpers are present.
    const bool needsFrontTiles = std::any_of(m_tilemap.flips.cbegin(), m_tilemap.flips.cend(),
        [](char flags) { return (quint8(flags) & 4u) != 0; });
    const bool needsCustomZones = std::any_of(m_tilemap.collisions.cbegin(), m_tilemap.collisions.cend(),
        [](char type) { return quint8(type) >= 9 && quint8(type) <= 24; });
    if (m_tilemap.collisions.contains(char(7)) ||
        !m_tilemap.collisionPlacements.isEmpty() || needsFrontTiles || needsCustomZones) {
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
                (!needsFrontTiles || (existingC.contains("game_tilemap_blit_view_front") &&
                                       existingH.contains("GAME_TILE_DRAW_FRONT"))) &&
                (!needsCustomZones || (existingC.contains("game_zone_at_player") &&
                                        existingH.contains("GAME_ZONE_ENTERED")));
        }
        cCheck.close(); hCheck.close();
        if (!current) {
            if (QMessageBox::question(this, tr("Upgrade Tilemap Helpers"),
                    tr("This level uses custom slopes, foreground tiles or programmable zones, but this "
                       "project's gametilemap.c/.h need updating.\n\n"
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
    if (!sidboxExportTilemap(m_tilemap, directory, &error, m_tilemapExternal)) {
        QMessageBox::warning(this, tr("Tilemap Export"), error);
        return false;
    }
    if (assetFilesChanged) assetFilesChanged();
    if (showMessage)
        QMessageBox::information(this, tr("Tilemap Exported"),
            m_tilemapExternal
                ? tr("Created gamelevels/level1.map plus level1.c/.h.\n"
                     "Copy gamelevels/level1.map to the same SD-card path.\n"
                     "Call game_level1_load_map(\"gamelevels/level1.map\") after initMalloc(), "
                     "BEFORE game_level1_load_atlas().\n"
                     "Object/sprite placement remains part of generated C.\n"
                     "Use Update Project to refresh older installed tilemap helpers.")
                : tr("Map exported into gamelevels/level1.c and level1.h.\n"
                     "Call game_level1_load_atlas() once after initMalloc().\n"
                     "Copyable instructions: gamehelpers/gametilemap.txt."));
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
    QByteArray header = "/* GENERATED by CoderGirl Game Designer. Edit paths and pauses in the canvas. */\n"
        "#ifndef CODERGIRL_V1_SPLINEPATHS_H\n#define CODERGIRL_V1_SPLINEPATHS_H\n"
        "#include \"gamespline.h\"\n\n";
    QByteArray source = "/* GENERATED by CoderGirl Game Designer. Do not edit this file. */\n"
        "#include \"splinepaths.h\"\n\n";
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
        header += QStringLiteral("extern const game_spline_point_t %1_path[%2];\n"
                                 "extern const uint16_t %1_count;\n"
                                 "extern const uint16_t %1_frames;\n"
                                 "extern const uint8_t %1_loop;\n\n")
                          .arg(identifier).arg(path.points.size()).toUtf8();
        source += QStringLiteral("const game_spline_point_t %1_path[%2] = {\n")
                          .arg(identifier).arg(path.points.size()).toUtf8();
        for (int p = 0; p < path.points.size(); ++p) {
            const QPoint &point = path.points.at(p);
            source += QStringLiteral("    {%1, %2, %3},\n")
                          .arg(point.x()).arg(point.y()).arg(path.pointPauses.value(p, 0)).toUtf8();
        }
        source += QStringLiteral("};\nconst uint16_t %1_count = %2;\n"
                                 "const uint16_t %1_frames = %3;\n"
                                 "const uint8_t %1_loop = %4;\n\n")
                        .arg(identifier).arg(path.points.size())
                        .arg(path.durationFrames).arg(path.loop ? 1 : 0).toUtf8();
    }
    header += "#endif\n";

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
    connect(updateProject, &QPushButton::clicked, this, [this]() { updateGameProject(); });
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
            for (const QString &header : folder.entryList({QStringLiteral("*.h")}, QDir::Files, QDir::Name)) {
                const QString base = QFileInfo(header).completeBaseName();
                if (!QFileInfo::exists(folder.filePath(base + QStringLiteral(".c")))) continue;
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
            configureObject = menu.addAction(tr("Configure Game Object..."));
            configureObject->setToolTip(tr("Choose collectable, moving lift, conveyor or spring, plus animation and spline."));
        }
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
        else if (chosen == buildClut) buildSharedPalette();
        else if (chosen == editPalette) openPaletteEditor(-1);
        else if (chosen == editTiles) openTilemapEditor();
        else if (chosen == exportTiles) exportTilemap(true);
        else if (chosen->data().toString().startsWith(QStringLiteral("codehelper:"))) {
            const QString ref = chosen->data().toString().mid(11);
            addCodeHelper(ref.section(QLatin1Char('/'), 0, 0), ref.section(QLatin1Char('/'), 1));
        }
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
        if (group == QStringLiteral("gameobject") && item->data(0, Qt::UserRole).isValid()) {
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
    m_showTilemap = new QCheckBox(tr("Show Tilemap"), previewPanel);
    m_showTilemap->setToolTip(tr("Show the attached tilemap artwork in world coordinates. "
                                 "The preview follows world zoom and panning; "
                                 "it does not change the exported game."));
    m_showTilemap->setChecked(false);
    m_showTilemap->setEnabled(false);
    previewControls->addWidget(m_showTilemap);
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
                      QStringLiteral("75%"), QStringLiteral("100%"), QStringLiteral("200%")});
    m_zoom->setCurrentText(QStringLiteral("100%"));
    previewControls->addWidget(m_zoom);
    previewLayout->addLayout(previewControls);
    m_scene = new GameScene(this);
    m_view = new QGraphicsView(m_scene, previewPanel);
    // A custom accent-coloured marquee handles selection from empty space.
    // Qt still handles dragging groups of selected QGraphicsPixmapItems.
    m_view->setDragMode(QGraphicsView::NoDrag);
    m_view->setToolTip(tr("Middle-drag pans the view. Left-drag empty space selects sprites; "
                           "drag a selected sprite to move the group. "
                           "Right-click to create or edit splines."));
    m_view->setFocusPolicy(Qt::StrongFocus);
    m_view->installEventFilter(this);
    m_view->viewport()->installEventFilter(this);
    m_view->setRenderHint(QPainter::Antialiasing, false);
    m_view->setRenderHint(QPainter::SmoothPixmapTransform, false);
    m_view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
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
    connect(m_forcePalette, &QCheckBox::toggled, this, [this](bool) {
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
        for (QTreeWidgetItemIterator it(m_resourceTree); *it; ++it) {
            QTreeWidgetItem *item = *it;
            const QVariant resource = item->data(0, Qt::UserRole);
            if (!resource.isValid() || resource.toInt() != index) continue;
            const QString group = item->data(0, Qt::UserRole + 1).toString();
            if (m_resources.at(index).kind == QStringLiteral("sprite")
                && m_resources.at(index).objectType != QStringLiteral("decoration"))
                item->setText(0, tr("%1  [%2]").arg(text, m_resources.at(index).objectType));
            else if (group != QStringLiteral("spline"))
                item->setText(0, text);
        }
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
    if (m_syncSelection || !m_scene || !m_resourceTree) return;
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
        return QIcon();
    };
    QSignalBlocker block(m_resourceTree);
    m_resourceTree->clear();
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
            if (kind == QStringLiteral("sprite") && r.objectType != QStringLiteral("decoration")) {
                child->setText(0, QStringLiteral("%1  [%2]").arg(r.name, r.objectType));
                child->setToolTip(0, tr("Game object: %1\n%2").arg(r.objectType, r.path));
            }
            child->setData(0, Qt::UserRole + 1, kind);
            child->setData(0, Qt::UserRole + 2, r.plane);
        }
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
    const int cw = r.cellWidth > 0 ? qMin(r.cellWidth, visible.width()) : visible.width();
    const int ch = r.cellHeight > 0 ? qMin(r.cellHeight, visible.height()) : visible.height();
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
                plane == QStringLiteral("foreground")));
    }
    return frameImage;
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
    m_scene->clear();
    m_tilemapOverlayItem = nullptr;
    m_sceneItems.clear();
    m_sceneItems.resize(m_resources.size());
    m_worldFrame = nullptr;
    m_cameraFrame = nullptr;
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
                                                 : QPixmap::fromImage(preview);
        auto *item = new PlacedImage(pixmap);
        item->setData(0, i);
        item->setFlag(QGraphicsItem::ItemIsMovable, !r.locked);
        item->snapped = [this, i](const QPointF &p) -> QPointF {
            if (m_loading || m_groupDragActive || !m_snap->isChecked()
                || m_resources.at(i).locked) return p;
            const int step = m_snapStep->currentText().section(QLatin1Char(' '), 0, 0).toInt();
            if (step <= 0) return p;
            return QPointF(qRound(p.x() / step) * step, qRound(p.y() / step) * step);
        };
        item->setPos(r.x, r.y);
        item->setScale(r.scale / 100.0);
        if (r.kind == QStringLiteral("background")) item->setZValue(1);
        item->moved = [this](QGraphicsItem *which) { syncFromSceneItem(which); };
        m_scene->addItem(item);
        auto *title = new QGraphicsSimpleTextItem(r.name, item);
        title->setBrush(QColor(255, 241, 160));
        title->setFlag(QGraphicsItem::ItemIgnoresTransformations, true);
        title->setPos(0, -18);
        title->setVisible(m_showLabels->isChecked());
        title->setAcceptedMouseButtons(Qt::NoButton);
        m_sceneItems[i] = item;
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
    item->setScale(r.scale / 100.0);
    m_loading = false;
    refreshObjectHitbox();
}

void SidboxGameDesigner::updateSelectedPixmap()
{
    const int index = selectedIndex();
    if (index < 0 || index >= m_sceneItems.size() || !m_sceneItems.at(index)) return;
    auto *item = dynamic_cast<QGraphicsPixmapItem *>(m_sceneItems.at(index));
    if (!item) return;
    const QImage preview = resourcePreview(m_resources.at(index));
    item->setPixmap(preview.isNull() ? missingImage(m_resources.at(index).kind)
                                     : QPixmap::fromImage(preview));
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
    if (!enabled) {
        m_propName->clear(); m_propFile->clear(); m_imageInfo->clear(); m_palettePreview->hide();
        m_editPaletteButton->hide();
        m_audioPanel->clearAudio();
        m_exportCButton->setEnabled(false);
        m_propX->setValue(0); m_propY->setValue(0); m_propScale->setValue(100);
        m_propCellWidth->setValue(0); m_propCellHeight->setValue(0);
        m_propFrame->setRange(0, 0);
        m_propLocked->setChecked(false);
        return;
    }
    const Resource &r = m_resources.at(index);
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
        spin->setEnabled(visual);
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
        if (extraPaletteTransparency(shownPalette, plane == QStringLiteral("foreground")))
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
    if (m_undoResources.size() >= 64) m_undoResources.removeFirst();
    m_undoResources.append(m_resources);
    m_redoResources.clear();
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
    if (m_redoResources.size() >= 64) m_redoResources.removeFirst();
    m_redoResources.append(m_resources);
    const QVector<Resource> snapshot = m_undoResources.takeLast();
    restoreResourceSnapshot(snapshot);
}

void SidboxGameDesigner::redoResourceEdit()
{
    if (m_redoResources.isEmpty()) return;
    if (m_undoResources.size() >= 64) m_undoResources.removeFirst();
    m_undoResources.append(m_resources);
    const QVector<Resource> snapshot = m_redoResources.takeLast();
    restoreResourceSnapshot(snapshot);
}

void SidboxGameDesigner::copySelectedSprite()
{
    const int index = selectedIndex();
    if (index < 0 || m_resources.at(index).kind != QStringLiteral("sprite")) return;
    m_copiedSprite = m_resources.at(index);
    m_hasCopiedSprite = true;
}

void SidboxGameDesigner::pasteCopiedSprite()
{
    if (!m_hasCopiedSprite || m_resources.size() >= 8192) return;
    rememberResourceEdit();
    Resource copy = m_copiedSprite;
    copy.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    QString base = copy.name;
    base.remove(QRegularExpression(QStringLiteral("_copy\\[\\d+\\]$")));
    // Keep numbered clones together, making it obvious they form instances.
    int next = 0;
    const QRegularExpression series(QStringLiteral("^%1_copy\\[(\\d+)\\]$")
        .arg(QRegularExpression::escape(base)));
    for (const Resource &existing : m_resources) {
        const auto match = series.match(existing.name);
        if (match.hasMatch()) next = qMax(next, match.captured(1).toInt() + 1);
    }
    copy.name = QStringLiteral("%1_copy[%2]").arg(base).arg(next);
    copy.x = qBound(-MAX_WORLD, copy.x + 8, MAX_WORLD);
    copy.y = qBound(-MAX_WORLD, copy.y + 8, MAX_WORLD);
    copy.locked = false; // A duplicate is immediately movable.
    // Preserve EXACT scroll-bar pixels rather than round-tripping through
    // mapToScene()/centerOn(). The latter introduces 1-2px drift on each paste.
    // Restoring after selecting avoids tree/scene updates nudging the viewport.
    const int previousHorizontalScroll = m_view->horizontalScrollBar()->value();
    const int previousVerticalScroll = m_view->verticalScrollBar()->value();
    m_resources.append(copy);
    rebuildScene();
    refreshResources();
    selectResource(m_resources.size() - 1);
    m_view->horizontalScrollBar()->setValue(previousHorizontalScroll);
    m_view->verticalScrollBar()->setValue(previousVerticalScroll);
    setDirty();
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
    const QString path = QFileDialog::getOpenFileName(this, tr("Choose %1 resource").arg(kindTitle(kind)),
        QFileInfo(m_filePath).absolutePath(),
        kind == QStringLiteral("tileatlas")
            ? tr("SIDBOX Tile Atlas (*.ppb)")
            : kind == QStringLiteral("sprite") || kind == QStringLiteral("background")
            ? tr("Graphics (*.ppb *.png *.bmp *.jpg *.jpeg *.gif);;All Files (*)")
            : kind == QStringLiteral("sound") ? tr("Sound (*.wav);;All Files (*)")
            : kind == QStringLiteral("music") ? tr("Music (*.mod *.s3m *.xm *.med *.tfmx *.sid *.sba);;All Files (*)")
            : tr("Palettes / Graphics (*.ppb *.pal *.act *.png *.bmp);;All Files (*)"));
    if (path.isEmpty()) return;
    if (kind == QStringLiteral("tileatlas") &&
        QFileInfo(path).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive) != 0) {
        QMessageBox::warning(this, tr("Tile Atlas"), tr("Tile atlases must be PPB files. Convert the image to PPB first."));
        return;
    }
    Resource r;
    r.kind = kind;
    r.plane = kind == QStringLiteral("background") ? QStringLiteral("background")
        : (kind == QStringLiteral("palette") && plane == QStringLiteral("background")
          ? QStringLiteral("background") : QStringLiteral("foreground"));
    r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    r.name = QFileInfo(path).completeBaseName();
    r.path = storedPath(path);
    r.x = m_cameraX->value() + 40;
    r.y = m_cameraY->value() + 40;
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
        r.x = m_cameraX->value() + 40;
        r.y = m_cameraY->value() + 40;
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
    r.x = m_cameraX->value() + 40;
    r.y = m_cameraY->value() + 40;
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
    const QString pngPath = QFileDialog::getOpenFileName(this, tr("Import PNG Image"),
        QFileInfo(m_filePath).absolutePath(), tr("PNG Images (*.png)"));
    if (pngPath.isEmpty()) return;
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
        suggestSpriteCells(r);
        rememberResourceEdit();
        m_resources.append(r);
        const int importedIndex = m_resources.size() - 1;
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
    if (!SidboxPpb::exportC(cPath, r.name, picture, &error)) {
        QMessageBox::warning(this, tr("Embedded C Resource"), error); return;
    }
    if (assetFilesChanged) assetFilesChanged();
    QMessageBox::information(this, tr("Embedded C Resource"),
        tr("Created %1 and %2.\n"
           "Use the generated pixel array and palette from your V1 game code. "
           "No existing game logic was modified.")
          .arg(cInfo.fileName(), QFileInfo(hPath).fileName()));
}


// Game object editing deliberately lives alongside the existing sprite tree.
// The sprite remains the authoritative WORLD placement and bitmap reference.
void SidboxGameDesigner::configureGameObject(int index)
{
    if (index < 0 || index >= m_resources.size() ||
        m_resources.at(index).kind != QStringLiteral("sprite")) return;
    const Resource &old = m_resources.at(index);
    QDialog dialog(this);
    dialog.setWindowTitle(tr("Game Object Properties - %1").arg(old.name));
    // Compact by default; both property columns scroll independently.
    // Users can resize the dialog if they prefer more room.
    dialog.resize(860, 540);
    dialog.setMinimumSize(700, 420);
    // No new rounded widgets, even when the desktop theme uses rounded popups.
    dialog.setStyleSheet(styleSheet() + QStringLiteral(
        "QDialog, QGroupBox, QSpinBox, QComboBox, QPushButton, QLineEdit { border-radius:0px; }"));
    QVBoxLayout layout(&dialog);
    auto *hint = new QLabel(tr("World coordinates come from this sprite's canvas position. "
                            "Behaviour belongs to this sprite instance, not its PPB file."), &dialog);
    hint->setWordWrap(true);
    layout.addWidget(hint);
    // QGroupBox with our custom theme can paint its title over the first row.
    // Use a plain panel with an explicit header instead. Stack each field's
    // label above the input so neither controls nor text can collide at narrow
    // sizes. Separate scroll areas keep the dialog compact on smaller screens.
    auto *objectPanel = new QWidget(&dialog);
    auto *objectLayout = new QVBoxLayout(objectPanel);
    objectLayout->setContentsMargins(10, 8, 10, 8);
    objectLayout->setSpacing(8);
    auto *objectHeading = new QLabel(tr("OBJECT / BEHAVIOUR"), objectPanel);
    QFont headingFont = objectHeading->font();
    headingFont.setBold(true);
    objectHeading->setFont(headingFont);
    objectLayout->addWidget(objectHeading);
    auto *form = new QFormLayout;
    form->setContentsMargins(0, 0, 0, 0);
    form->setRowWrapPolicy(QFormLayout::WrapAllRows);
    form->setLabelAlignment(Qt::AlignLeft);
    form->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    form->setVerticalSpacing(5);
    objectLayout->addLayout(form);
    objectLayout->addStretch(1);
    auto *type = new GameComboBox(&dialog);
    type->addItem(tr("Ordinary sprite / Decoration"), QStringLiteral("decoration"));
    type->addItem(tr("Collectable"), QStringLiteral("collectable"));
    type->addItem(tr("Moving platform / Lift"), QStringLiteral("lift"));
    type->addItem(tr("Conveyor"), QStringLiteral("conveyor"));
    type->addItem(tr("Spring / Bouncer"), QStringLiteral("spring"));
    type->addItem(tr("Trigger / Switch"), QStringLiteral("trigger"));
    type->addItem(tr("Door / Solid blocker"), QStringLiteral("door"));
    type->addItem(tr("Hazard Zone (touch = callback)"), QStringLiteral("deathzone"));
    type->setCurrentIndex(qMax(0, type->findData(old.objectType)));
    form->addRow(tr("Behaviour"), type);
    auto *pickup = new GameComboBox(&dialog);
    pickup->addItem(tr("Coin"), 1);
    pickup->addItem(tr("Health"), 2);
    pickup->addItem(tr("Key"), 3);
    pickup->addItem(tr("Gem"), 4);
    pickup->setCurrentIndex(qMax(0, pickup->findData(old.pickupKind)));
    form->addRow(tr("Pickup type"), pickup);
    auto spin = [&dialog](int lo, int hi, int val) {
        auto *s = new QSpinBox(&dialog);
        s->setRange(lo, hi); s->setValue(val); return s;
    };
    auto *value = spin(0, 65535, old.objectValue);
    form->addRow(tr("Pickup value"), value);
    auto *initiallyActive = new QCheckBox(tr("Active when the level starts"), &dialog);
    initiallyActive->setChecked(old.objectInitiallyActive);
    form->addRow(QString(), initiallyActive);
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
    auto *triggerPress = new QCheckBox(tr("Require FIRE2 while touching (otherwise activate on touch)"), &dialog);
    triggerPress->setChecked(old.triggerPress);
    triggerPress->setToolTip(tr("FIRE2 is the second fire button; unlike FIRE it does not jump. "
                                 "Press once per activation while overlapping the switch."));
    form->addRow(QString(), triggerPress);
    auto *triggerOneShot = new QCheckBox(tr("Remove switch after activation (one-shot)"), &dialog);
    triggerOneShot->setChecked(old.triggerOneShot);
    form->addRow(QString(), triggerOneShot);
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

    auto *respawn = spin(0, 65535, old.respawnFrames);
    form->addRow(tr("Respawn after frames (0 = never)"), respawn);
    auto *hitW = spin(1, 1024, old.hitWidth);
    auto *hitH = spin(1, 1024, old.hitHeight);
    form->addRow(tr("Collision width"), hitW);
    form->addRow(tr("Collision height"), hitH);
    auto *conveyor = spin(-100, 100, old.conveyorSpeed);
    form->addRow(tr("Conveyor px/frame"), conveyor);
    auto *spring = spin(1, 100, old.springStrength);
    form->addRow(tr("Spring upward launch (px/frame)"), spring);
    auto *springLaunchX = spin(-40, 40, old.springLaunchX);
    springLaunchX->setToolTip(tr("Horizontal spring trajectory: negative launches LEFT, "
                                 "positive launches RIGHT, and 0 launches straight up. "
                                 "Normal mode pushes constantly until landing; Slidy mode "
                                 "gradually slows down, including after landing."));
    form->addRow(tr("Spring sideways launch (− left / + right)"), springLaunchX);
    auto *springTouch = new QCheckBox(tr("Activate on touch (any side)"), &dialog);
    springTouch->setChecked(old.springTouch);
    springTouch->setToolTip(tr("Off: spring launches only when the player lands on its top. "
                                 "On: entering the spring hitbox from above, below or either side "
                                 "launches the player. Fires once per contact; leave it to rearm."));
    form->addRow(QString(), springTouch);
    auto *springSlide = new QCheckBox(tr("Slidy kickback (inertia + friction)"), &dialog);
    springSlide->setChecked(old.springSlide);
    springSlide->setToolTip(tr("Off: normal sideways spring launch stays at full speed "
                               "until landing. On: sideways momentum fades gradually "
                               "in the air and continues to slide with greater friction "
                               "on the ground. Joystick steering still works. "
                               "Uses the Spring sideways launch setting."));
    form->addRow(QString(), springSlide);
    auto *springJumpBoost = new QCheckBox(tr("Combine jump + spring launch (extra boost)"), &dialog);
    springJumpBoost->setChecked(old.springJumpBoost);
    springJumpBoost->setToolTip(tr("Off: spring launch strength alone. On: a newly pressed Jump "
                               "on contact adds the player's jump speed. "
                               "Requires the optional physics jump bindings."));
    form->addRow(QString(), springJumpBoost);
    auto *spline = new GameComboBox(&dialog);
    spline->addItem(tr("None (stationary)"), QString());
    for (const SplinePath &path : m_splinePaths)
        spline->addItem(path.name, path.id);
    spline->setCurrentIndex(qMax(0, spline->findData(old.objectSplineId)));
    form->addRow(tr("Movement spline"), spline);
    auto *animated = new QCheckBox(tr("Animate sprite frames"), &dialog);
    animated->setChecked(old.objectAnimated);
    form->addRow(QString(), animated);
    auto *first = spin(0, 255, old.animFirst);
    auto *count = spin(1, 256, old.animCount);
    auto *ticks = spin(1, 65535, old.animTicks);
    form->addRow(tr("First frame"), first);
    form->addRow(tr("Number of frames"), count);
    form->addRow(tr("Frames per picture"), ticks);
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
    auto *sfxPickup = soundPicker(old.sfxPickup);
    auto *sfxRespawn = soundPicker(old.sfxRespawn);
    auto *sfxStart = soundPicker(old.sfxStart);
    auto *sfxMove = soundPicker(old.sfxMove);
    auto *sfxStop = soundPicker(old.sfxStop);
    auto *sfxReverse = soundPicker(old.sfxReverse);
    auto *sfxSpring = soundPicker(old.sfxSpring);
    auto *sfxAmbient = soundPicker(old.sfxAmbient);
    auto *radius = spin(0, 32767, old.audioRadius);
    auto *fade = spin(0, 255, old.audioFadeFrames);
    auto *audioPanel = new QWidget(&dialog);
    auto *audioLayout = new QVBoxLayout(audioPanel);
    audioLayout->setContentsMargins(10, 8, 10, 8);
    audioLayout->setSpacing(8);
    auto *audioHeading = new QLabel(tr("AUDIO (OPTIONAL)"), audioPanel);
    audioHeading->setFont(headingFont);
    audioLayout->addWidget(audioHeading);
    auto *audioForm = new QFormLayout;
    audioForm->setContentsMargins(0, 0, 0, 0);
    audioForm->setRowWrapPolicy(QFormLayout::WrapAllRows);
    audioForm->setLabelAlignment(Qt::AlignLeft);
    audioForm->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
    audioForm->setVerticalSpacing(5);
    audioLayout->addLayout(audioForm);
    audioLayout->addStretch(1);
    audioForm->addRow(tr("Pickup"), sfxPickup);
    audioForm->addRow(tr("Respawn sound"), sfxRespawn);
    audioForm->addRow(tr("Mover starts"), sfxStart);
    audioForm->addRow(tr("Mover moving (loopable)"), sfxMove);
    audioForm->addRow(tr("Mover stops"), sfxStop);
    audioForm->addRow(tr("Mover reverses"), sfxReverse);
    audioForm->addRow(tr("Spring launches"), sfxSpring);
    audioForm->addRow(tr("Conveyor ambience (loopable)"), sfxAmbient);
    audioForm->addRow(tr("Audible radius (0 = non-positional)"), radius);
    audioForm->addRow(tr("Loop fade frames"), fade);
    audioPanel->setToolTip(tr("Sound channels are assigned in Game Resources > Sounds. "
        "Simultaneously playing sounds must use different channels to avoid interrupting each other. "
        "For continuous movement or conveyor ambience, enable Loop in the chosen Sound resource."));
    // Independently scrollable columns: Behaviour on the left, Audio on the
    // right. No narrowing the combo boxes and no extra canvas toolbar rows.
    auto *settingsColumns = new QHBoxLayout;
    settingsColumns->setSpacing(12);
    auto *objectScroll = new QScrollArea(&dialog);
    objectScroll->setWidgetResizable(true);
    objectScroll->setFrameShape(QFrame::NoFrame);
    objectScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    objectScroll->setWidget(objectPanel);
    settingsColumns->addWidget(objectScroll, 1);
    auto *audioScroll = new QScrollArea(&dialog);
    audioScroll->setWidgetResizable(true);
    audioScroll->setFrameShape(QFrame::NoFrame);
    audioScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    audioScroll->setWidget(audioPanel);
    settingsColumns->addWidget(audioScroll, 1);
    layout.addLayout(settingsColumns, 1);
    auto enableFields = [=]() {
        const QString behaviour = type->currentData().toString();
        const bool isObject = behaviour != QStringLiteral("decoration");
        // Hazard Zones use the Advanced Platformer tilemap event API.
        // They are intangible sensors; hitW/hitH define the lethal area.
        pickup->setEnabled(behaviour == QStringLiteral("collectable"));
        value->setEnabled(behaviour == QStringLiteral("collectable"));
        const bool isTrigger = behaviour == QStringLiteral("trigger");
        const bool isKey = behaviour == QStringLiteral("collectable") && pickup->currentData().toInt() == 3;
        initiallyActive->setEnabled(isObject);
        targetObject->setEnabled(isTrigger || isKey);
        targetAction->setEnabled(isTrigger || isKey);
        triggerPress->setEnabled(isTrigger);
        triggerOneShot->setEnabled(isTrigger);
        musicAction->setEnabled(isTrigger);
        musicTrack->setEnabled(isTrigger && musicAction->currentData().toString() == QStringLiteral("play"));
        hitW->setEnabled(isObject); hitH->setEnabled(isObject);
        conveyor->setEnabled(behaviour == QStringLiteral("conveyor"));
        spring->setEnabled(behaviour == QStringLiteral("spring"));
        springLaunchX->setEnabled(behaviour == QStringLiteral("spring"));
        springTouch->setEnabled(behaviour == QStringLiteral("spring"));
        springSlide->setEnabled(behaviour == QStringLiteral("spring"));
        springJumpBoost->setEnabled(behaviour == QStringLiteral("spring"));
        sfxPickup->setEnabled(behaviour == QStringLiteral("collectable"));
        sfxRespawn->setEnabled(behaviour == QStringLiteral("collectable"));
        respawn->setEnabled(behaviour == QStringLiteral("collectable"));
        sfxStart->setEnabled(behaviour == QStringLiteral("lift"));
        sfxMove->setEnabled(behaviour == QStringLiteral("lift"));
        sfxStop->setEnabled(behaviour == QStringLiteral("lift"));
        sfxReverse->setEnabled(behaviour == QStringLiteral("lift"));
        sfxSpring->setEnabled(behaviour == QStringLiteral("spring"));
        sfxAmbient->setEnabled(behaviour == QStringLiteral("conveyor"));
        radius->setEnabled(isObject);
        fade->setEnabled(isObject);
        spline->setEnabled(isObject);
        animated->setEnabled(isObject);
        for (QWidget *w : {static_cast<QWidget *>(first), static_cast<QWidget *>(count),
                           static_cast<QWidget *>(ticks), static_cast<QWidget *>(mode)})
            w->setEnabled(isObject && animated->isChecked());
    };
    connect(type, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    connect(animated, &QCheckBox::toggled, &dialog,
            [enableFields](bool) { enableFields(); });
    connect(pickup, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    connect(musicAction, qOverload<int>(&QComboBox::currentIndexChanged), &dialog,
            [enableFields](int) { enableFields(); });
    enableFields();
    // A late-created dialog is not part of setTheme()'s existing-combo pass.
    // Colour its popup views explicitly to match Stage 2.5 theme rules.
    const auto C = [](const QColor &colour) { return ideThemeColorName(colour); };
    for (QComboBox *combo : dialog.findChildren<QComboBox *>()) {
        combo->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLengthWithIcon);
        combo->setMinimumContentsLength(14);
        combo->setMinimumWidth(0);
        combo->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        QPalette colours = combo->palette();
        colours.setColor(QPalette::Base, m_theme.inputBackground);
        colours.setColor(QPalette::Text, m_theme.text);
        colours.setColor(QPalette::Button, m_theme.inputBackground);
        colours.setColor(QPalette::ButtonText, m_theme.text);
        colours.setColor(QPalette::Highlight, m_theme.accent);
        colours.setColor(QPalette::HighlightedText, m_theme.brightText);
        combo->setPalette(colours);
        if (auto *popup = combo->view()) {
            popup->setPalette(colours);
            popup->setStyleSheet(QStringLiteral(
                "QAbstractItemView { background:%1; color:%2; border:1px solid %3; "
                "border-radius:0px; selection-background-color:%4; selection-color:%5; "
                "outline:0px; } QAbstractItemView::item:selected { background:%4; color:%5; }")
                .arg(C(m_theme.menuBackground), C(m_theme.text), C(m_theme.border),
                     C(m_theme.accent), C(m_theme.brightText)));
        }
    }
    auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                         Qt::Horizontal, &dialog);
    layout.addWidget(buttons);
    connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() != QDialog::Accepted) return;
    const QString newType = type->currentData().toString();
    if (newType == QStringLiteral("deathzone") && !m_tilemapEnabled) {
        QMessageBox::warning(this, tr("Game Object"),
            tr("Hazard Zones require an Advanced Platformer tilemap. "
               "Enable a tilemap in the Game Designer before choosing this behaviour."));
        return;
    }
    if (newType != QStringLiteral("decoration") &&
        (old.path.isEmpty() || old.scale != 100 ||
         QFileInfo(resolvedPath(old.path)).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive))) {
        QMessageBox::warning(this, tr("Game Object"),
            tr("Game objects require a PPB sprite at 100%% scale. "
               "Please assign a PPB and set the sprite scale to 100 first."));
        return;
    }
    rememberResourceEdit();
    Resource &r = m_resources[index];
    r.objectType = newType;
    r.pickupKind = pickup->currentData().toInt();
    r.objectValue = value->value();
    r.hitWidth = hitW->value(); r.hitHeight = hitH->value();
    r.conveyorSpeed = conveyor->value(); r.springStrength = spring->value();
    r.springLaunchX = springLaunchX->value();
    r.springTouch = springTouch->isChecked();
    r.springSlide = springSlide->isChecked();
    r.springJumpBoost = springJumpBoost->isChecked();
    r.objectInitiallyActive = initiallyActive->isChecked();
    r.targetObjectId = targetObject->currentData().toString();
    r.targetAction = targetAction->currentData().toString();
    r.triggerPress = triggerPress->isChecked();
    r.triggerOneShot = triggerOneShot->isChecked();
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
    r.respawnFrames = respawn->value();
    r.audioRadius = radius->value();
    r.audioFadeFrames = fade->value();
    r.objectSplineId = spline->currentData().toString();
    r.objectAnimated = animated->isChecked();
    r.animFirst = first->value(); r.animCount = count->value();
    r.animTicks = ticks->value(); r.animMode = mode->currentData().toString();
    refreshResources();
    selectResource(index);
    setDirty();
}

void SidboxGameDesigner::refreshObjectHitbox()
{
    if (!m_scene || m_loading) return;
    if (m_objectHitbox) {
        m_scene->removeItem(m_objectHitbox);
        delete m_objectHitbox;
        m_objectHitbox = nullptr;
    }
    const int index = selectedIndex();
    if (index < 0 || index >= m_resources.size()) return;
    const Resource &r = m_resources.at(index);
    if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")) return;
    QPen pen(m_theme.accent, 1.5, Qt::DashLine);
    m_objectHitbox = m_scene->addRect(r.x, r.y, r.hitWidth, r.hitHeight,
                                     pen, Qt::NoBrush);
    m_objectHitbox->setZValue(9900);
    m_objectHitbox->setAcceptedMouseButtons(Qt::NoButton);
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

// Only offer to copy missing C/H/TXT templates; never overwrite modified helpers.
bool SidboxGameDesigner::installMissingWorldHelpers(QString *error, bool prompt)
{
    bool pickups = false, worlds = false, animations = false, splines = false;
    for (const SplinePath &path : m_splinePaths)
        if (path.points.size() >= 2) splines = true;
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")) continue;
        pickups |= r.objectType == QStringLiteral("collectable");
        worlds |= r.objectType != QStringLiteral("collectable");
        animations |= r.objectAnimated;
        splines |= !r.objectSplineId.isEmpty();
    }
    QStringList names;
    if (pickups) names << QStringLiteral("collectables");
    if (worlds) names << QStringLiteral("worldobjects");
    // Both new helpers include these headers whether attached or not.
    if (pickups || worlds) { names << QStringLiteral("animation") << QStringLiteral("spline"); }
    else if (splines) names << QStringLiteral("spline");
    Q_UNUSED(animations)
    if (names.isEmpty()) return true;
    const QString dest = QDir(QFileInfo(m_filePath).absolutePath()).filePath(QStringLiteral("gamehelpers"));
    const QDir templates(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
    struct Copy { QString from, to; QByteArray data; };
    QVector<Copy> pending;
    for (const QString &name : names) {
        const QString base = QStringLiteral("game") + name;
        for (const QString &ext : {QStringLiteral(".h"), QStringLiteral(".c"), QStringLiteral(".txt")}) {
            const QString to = QDir(dest).filePath(base + ext);
            if (QFileInfo::exists(to)) continue;
            const QString from = templates.filePath(name + ext);
            QFile file(from);
            if (!file.open(QIODevice::ReadOnly)) {
                if (error) *error = tr("Missing helper template: %1").arg(from);
                return false;
            }
            QByteArray data = file.readAll();
            if (ext == QStringLiteral(".c")) {
                data.replace((QStringLiteral("\"%1.h\"").arg(name)).toUtf8(),
                             (QStringLiteral("\"%1.h\"").arg(base)).toUtf8());
            }
            pending.append({from, to, data});
        }
    }
    if (pending.isEmpty()) return true;
    QStringList files;
    for (const Copy &c : pending) files << QDir(dest).relativeFilePath(c.to);
    if (prompt && QMessageBox::question(this, tr("Install Missing Game Helpers?"),
        tr("These helpers are needed for your configured game objects:\n\n%1\n\n"
           "Install the missing files? Existing source and guides will NOT be overwritten.")
           .arg(files.join(QStringLiteral("\n"))),
        QMessageBox::Yes | QMessageBox::Cancel, QMessageBox::Yes) != QMessageBox::Yes) {
        if (error) *error = tr("Missing helper installation was cancelled.");
        return false;
    }
    if (!QDir().mkpath(dest)) { if (error) *error = tr("Cannot create %1").arg(dest); return false; }
    for (const Copy &c : pending) {
        // Another process could have created the file after our first check.
        if (QFileInfo::exists(c.to)) continue;
        QSaveFile file(c.to);
        if (!file.open(QIODevice::WriteOnly) || file.write(c.data) != c.data.size() || !file.commit()) {
            file.cancelWriting();
            if (error) *error = tr("Cannot install missing helper %1").arg(c.to);
            return false;
        }
    }
    return true;
}

bool SidboxGameDesigner::exportWorldItems(QString *error)
{
    QVector<const Resource *> pickups, platforms;
    QVector<int> pickupPaths, platformPaths;
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")) continue;
        if (r.scale != 100 || r.path.isEmpty() ||
            QFileInfo(resolvedPath(r.path)).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive)) {
            if (error) *error = tr("Game object '%1' must use a PPB sprite at 100%% scale.").arg(r.name);
            return false;
        }
        if (r.objectAnimated) {
            const QImage bitmap = cachedImage(resolvedPath(r.path));
            const int cw = r.cellWidth > 0 ? r.cellWidth : bitmap.width();
            const int ch = r.cellHeight > 0 ? r.cellHeight : bitmap.height();
            const int available = !bitmap.isNull() && cw > 0 && ch > 0
                ? (bitmap.width() / cw) * (bitmap.height() / ch) : 0;
            if (!available || r.animFirst + r.animCount > 256 ||
                r.animFirst + r.animCount > available) {
                if (error) *error = tr("Animation for '%1' exceeds the available PPB atlas frames (%2). "
                                      "Check Start Frame and Frame Count.").arg(r.name).arg(available);
                return false;
            }
        }
        int attached = -1;
        if (!r.objectSplineId.isEmpty()) {
            for (int i = 0; i < m_splinePaths.size(); ++i)
                if (m_splinePaths.at(i).id == r.objectSplineId) { attached = i; break; }
            if (attached < 0 || m_splinePaths.at(attached).points.size() < 2) {
                if (error) *error = tr("Spline attached to '%1' no longer exists. Reassign it in Game Object Properties.").arg(r.name);
                return false;
            }
        }
        if (r.objectType == QStringLiteral("collectable")) {
            pickups.append(&r); pickupPaths.append(attached);
        } else {
            platforms.append(&r); platformPaths.append(attached);
        }
    }
    if (pickups.isEmpty() && platforms.isEmpty()) {
        // If objects were removed, replace our PREVIOUSLY GENERATED files with
        // harmless stubs so stale references never break a subsequent build.
        const QDir oldFolder(QDir(QFileInfo(m_filePath).absolutePath())
            .filePath(QStringLiteral("gamehelpers")));
        const QString generatedH = oldFolder.filePath(QStringLiteral("gameworlditems.h"));
        if (!QFileInfo::exists(generatedH)) return true;
        QFile original(generatedH);
        if (!original.open(QIODevice::ReadOnly) ||
            !original.read(128).contains("GENERATED by CoderGirl")) {
            if (error) *error = tr("Existing gameworlditems.h isn't recognised as a generated file. "
                                  "Please inspect it before regenerating.");
            return false;
        }
        struct Stub { QString file, data; };
        for (const Stub &stub : {
            Stub{QStringLiteral("gameworlditems.h"), QStringLiteral(
                "/* GENERATED by CoderGirl. All world objects removed. */\n"
                "#ifndef CODERGIRL_V1_GAMEWORLDITEMS_H\n#define CODERGIRL_V1_GAMEWORLDITEMS_H\n"
                "#include <stdint.h>\nuint8_t gameworlditems_init(void);\n"
                "void gameworlditems_update(uint16_t frames);\n"
                "void gameworlditems_draw(int32_t cx, int32_t cy);\n#endif\n")},
            Stub{QStringLiteral("gameworlditems.c"), QStringLiteral(
                "/* GENERATED by CoderGirl. No managed world objects. */\n"
                "#include \"gameworlditems.h\"\n"
                "uint8_t gameworlditems_init(void) { return 1; }\n"
                "void gameworlditems_update(uint16_t frames) { (void)frames; }\n"
                "void gameworlditems_draw(int32_t cx, int32_t cy) { (void)cx; (void)cy; }\n")},
            Stub{QStringLiteral("gameworlditems.txt"), QStringLiteral(
                "No world objects are configured in this design.\n"
                "Right-click a sprite in Game Resources to configure one.\n")}
        }) {
            QSaveFile f(oldFolder.filePath(stub.file));
            const QByteArray data = stub.data.toUtf8();
            if (!f.open(QIODevice::WriteOnly) || f.write(data) != data.size() || !f.commit()) {
                f.cancelWriting();
                if (error) *error = tr("Cannot update %1").arg(stub.file);
                return false;
            }
        }
        return true;
    }
    if (!m_tilemapEnabled) {
        for (const Resource *r : platforms) {
            if (r->objectType == QStringLiteral("deathzone")) {
                if (error) *error = tr("Hazard Zone '%1' requires an Advanced Platformer tilemap. Enable the tilemap first.").arg(r->name);
                return false;
            }
        }
    }
    const int np = pickups.size(), nw = platforms.size();
    int nt = 0;
    for (const Resource *r : platforms) if (r->objectType == QStringLiteral("trigger")) ++nt;
    QHash<QString, QString> objectSlot; // Stable object ID -> generated live runtime instance.
    for (int i = 0; i < np; ++i)
        objectSlot.insert(pickups.at(i)->id, QStringLiteral("pickups[%1]").arg(i));
    for (int i = 0; i < nw; ++i)
        objectSlot.insert(platforms.at(i)->id, QStringLiteral("platforms[%1]").arg(i));
    bool linkedKeys = false;
    for (const Resource *r : pickups) if (r->pickupKind == 3 &&
        r->targetAction != QStringLiteral("none") && !r->targetObjectId.isEmpty()) linkedKeys = true;
    for (const Resource *r : pickups) {
        if (r->pickupKind != 3 || r->targetAction == QStringLiteral("none") ||
            r->targetObjectId.isEmpty()) continue;
        if (!objectSlot.contains(r->targetObjectId)) {
            if (error) *error = tr("Key '%1' links to a missing game object. Reassign its target.").arg(r->name);
            return false;
        }
    }
    for (const Resource *r : platforms) {
        if (r->objectType != QStringLiteral("trigger") || r->targetAction == QStringLiteral("none") ||
            r->targetObjectId.isEmpty()) continue;
        if (!objectSlot.contains(r->targetObjectId)) {
            if (error) *error = tr("Trigger '%1' links to a missing game object. Reassign its target.").arg(r->name);
            return false;
        }
    }
    QHash<QString, const Resource *> musicById;
    for (const Resource &asset : m_resources)
        if (asset.kind == QStringLiteral("music") && !asset.path.isEmpty())
            musicById.insert(asset.id, &asset);
    for (const Resource *r : platforms) {
        if (r->objectType != QStringLiteral("trigger") ||
            r->triggerMusicAction != QStringLiteral("play")) continue;
        if (!musicById.contains(r->triggerMusicId)) {
            if (error) *error = tr("Trigger '%1' has no valid music track. Choose one from the Music tree.").arg(r->name);
            return false;
        }
    }
    auto musicAction = [&](const Resource &r) -> QString {
        if (r.triggerMusicAction == QStringLiteral("stop")) return QStringLiteral("music_stop();");
        if (r.triggerMusicAction != QStringLiteral("play")) return QString();
        const Resource *music = musicById.value(r.triggerMusicId, nullptr);
        if (!music) return QString();
        const QString base = music->name.trimmed().isEmpty()
            ? QFileInfo(resolvedPath(music->path)).completeBaseName() : music->name;
        return QStringLiteral("playmusic%1();")
            .arg(SidboxPpb::identifier(base).toLower());
    };
    auto linkedAction = [&](const Resource &r) -> QString {
        if (r.targetAction == QStringLiteral("none") || r.targetObjectId.isEmpty()) return QString();
        const QString target = objectSlot.value(r.targetObjectId);
        if (target.isEmpty()) return QString();
        const QString field = target + QStringLiteral(".active");
        if (r.targetAction == QStringLiteral("enable")) return field + QStringLiteral(" = 1;");
        if (r.targetAction == QStringLiteral("disable")) return field + QStringLiteral(" = 0;");
        if (r.targetAction == QStringLiteral("toggle")) return field + QStringLiteral(" = (uint8_t)!") + field + QStringLiteral(";");
        return QString();
    };
    // Every sound reference must resolve to a real Sound resource. Name changes
    // are harmless because Game Designer stores persistent resource IDs.
    QHash<QString, const Resource *> soundById;
    for (const Resource &asset : m_resources)
        if (asset.kind == QStringLiteral("sound") && !asset.path.isEmpty())
            soundById.insert(asset.id, &asset);
    QSet<QString> usedSfx;
    bool pickupSound = false;
    for (const Resource *obj : pickups) {
        if (!obj->sfxPickup.isEmpty()) pickupSound = true;
        if (!obj->sfxPickup.isEmpty()) usedSfx.insert(obj->sfxPickup);
        if (obj->respawnFrames && !obj->sfxRespawn.isEmpty())
            usedSfx.insert(obj->sfxRespawn);
    }
    for (const Resource *obj : platforms) {
        if (obj->objectType == QStringLiteral("lift")) {
            for (const QString &id : {obj->sfxStart, obj->sfxMove,
                                      obj->sfxStop, obj->sfxReverse})
                if (!id.isEmpty()) usedSfx.insert(id);
        } else if (obj->objectType == QStringLiteral("spring")) {
            if (!obj->sfxSpring.isEmpty()) usedSfx.insert(obj->sfxSpring);
        } else if (obj->objectType == QStringLiteral("conveyor")) {
            if (!obj->sfxAmbient.isEmpty()) usedSfx.insert(obj->sfxAmbient);
        }
    }
    for (const QString &id : usedSfx) {
        if (!soundById.contains(id)) {
            if (error) *error = tr("A configured game-object sound no longer exists in Game Resources. "
                                   "Open the object's properties and reassign its sound.");
            return false;
        }
    }
    auto cSoundSymbol = [&](const QString &id) -> QString {
        const Resource *audio = soundById.value(id, nullptr);
        return audio ? SidboxPpb::identifier(audio->name.trimmed().isEmpty()
                                 ? QFileInfo(resolvedPath(audio->path)).completeBaseName()
                                 : audio->name).toLower() : QString();
    };
    auto cSfxCall = [&](const QString &id, const QString &x, int radius) -> QString {
        if (id.isEmpty()) return QString();
        return QStringLiteral("cg_sound_%1(%2, %3);\n")
            .arg(cSoundSymbol(id), x).arg(radius);
    };
    QString h, c, guide;
    QTextStream H(&h), C(&c), G(&guide);
    H << "/* GENERATED by CoderGirl. Regeneration overwrites this file. */\n"
         "#ifndef CODERGIRL_V1_GAMEWORLDITEMS_H\n#define CODERGIRL_V1_GAMEWORLDITEMS_H\n"
         "#include <stdint.h>\n";
    if (np) H << "#include \"gamecollectables.h\"\n";
    if (nw) H << "#include \"gameworldobjects.h\"\n";
    H << "\n#define GAMEWORLDITEMS_PICKUP_COUNT " << np << "u\n"
      << "#define GAMEWORLDITEMS_PLATFORM_COUNT " << nw << "u\n"
         "uint8_t gameworlditems_init(void);\n"
         "void gameworlditems_update(uint16_t frames);\n"
         "void gameworlditems_draw(int32_t camera_x, int32_t camera_y);\n";
    if (np) H << "uint16_t gameworlditems_check(int32_t player_x, int32_t player_y,\n"
             "    uint16_t player_w, uint16_t player_h, game_pickup_callback_t callback, void *user);\n";
    if (nw) H << "void gameworlditems_before(game_world_player_t *player);\n"
             "void gameworlditems_after(game_world_player_t *player);\n";
    if (nt) H << "uint16_t gameworlditems_trigger(int32_t player_x, int32_t player_y,\n"
                 "    uint16_t player_w, uint16_t player_h, uint8_t fire2_pressed);\n";
    H << "#endif\n";
    C << "/* GENERATED by CoderGirl. Regeneration overwrites this file. */\n"
         "#include \"gameworlditems.h\"\n"
         "#include \"../gameassets/gameassets.h\"\n";
    bool anyPath = false;
    for (int p : pickupPaths) if (p >= 0) anyPath = true;
    for (int p : platformPaths) if (p >= 0) anyPath = true;
    if (anyPath) C << "#include \"splinepaths.h\"\n";
    if (nw && m_tilemapEnabled)
        C << "#include \"gametilemap.h\"\n"
             "#include \"../gamelevels/level1.h\"\n";
    C << "\n";
    if (!usedSfx.isEmpty()) {
        C << R"CG(
/* Automatic object audio. WAVs and channels are defined in gameassets.
   Object sounds are OPTIONAL. Each sound uses its assigned SIDBOX channel.
   For spatial audio, 480 pixels is the V1 LCD width. */
static int32_t cg_audio_camera_x;
static int32_t cg_audio_distance(int32_t x)
{
    return x - (cg_audio_camera_x + 240);
}
static int32_t cg_audio_volume(int base, int32_t x, int radius)
{
    if (radius <= 0) return base;
    int32_t distance = cg_audio_distance(x);
    if (distance < 0) distance = -distance;
    if (distance >= radius) return 0;
    return (int32_t)((int64_t)base * (radius - distance) / radius);
}
static int8_t cg_audio_pan(int base, int32_t x, int radius)
{
    if (radius <= 0) return (int8_t)base;
    int32_t pan = base + (cg_audio_distance(x) * 127) / 240;
    if (pan < -127) pan = -127;
    if (pan > 127) pan = 127;
    return (int8_t)pan;
}
)CG";
        // Generate one typed, stable wrapper per referenced Sound resource.
        // These call the existing playsound...() functions generated by
        // gamecodegen.cpp, then adjust position once per event.
        QStringList ids;
        for (const QString &id : usedSfx) ids.append(id);
        ids.sort();
        for (const QString &id : ids) {
            const Resource &sound = *soundById.value(id);
            const QString sym = cSoundSymbol(id);
            C << "static void cg_sound_" << sym << "(int32_t x, int radius)\n{\n"
              << "    playsound" << sym << "();\n"
              << "    sound_setvolume(" << sound.audio.channel << ", cg_audio_volume("
              << qBound(0, sound.audio.volume, 1024) << ", x, radius));\n"
              << "    sound_setpanning(" << sound.audio.channel << ", cg_audio_pan("
              << qBound(-127, sound.audio.pan, 127) << ", x, radius));\n"
              << "}\n";
        }
    }
    if (np) C << "static game_collectable_t pickups[" << np << "];\n";
    if (np && !usedSfx.isEmpty()) C << "static uint8_t cg_pickup_was_inactive[" << np << "];\n";
    if (nw) C << "static game_world_object_t platforms[" << nw << "];\n";
    if (nw && m_tilemapEnabled)
        C << "static uint8_t cg_hazard_zone_contact;\n";
    // Per-lift motion state for start/stop/reverse transitions and faders.
    if (nw && !usedSfx.isEmpty()) {
        C << "static uint8_t cg_was_moving[" << nw << "];\n"
             "static int8_t cg_previous_direction[" << nw << "];\n"
             "static uint8_t cg_loop_playing[" << nw << "];\n"
             "static uint16_t cg_loop_gain[" << nw << "];\n"
             "static uint16_t cg_loop_target[" << nw << "];\n";
    }
    for (int i = 0; i < np; ++i) {
        if (pickupPaths.at(i) >= 0) C << "static game_spline_t pickup_path_" << i << " = {0};\n";
        if (pickups.at(i)->objectAnimated) C << "static game_animation_t pickup_anim_" << i << " = {0};\n";
    }
    for (int i = 0; i < nw; ++i) {
        if (platformPaths.at(i) >= 0) C << "static game_spline_t platform_path_" << i << " = {0};\n";
        if (platforms.at(i)->objectAnimated) C << "static game_animation_t platform_anim_" << i << " = {0};\n";
    }
    C << "\nuint8_t gameworlditems_init(void)\n{\n";
    if (nw && m_tilemapEnabled) C << "    cg_hazard_zone_contact = 0;\n";
    if (nw && !usedSfx.isEmpty()) C << "    for (uint16_t i = 0; i < " << nw
        << "; ++i) { cg_was_moving[i] = 0; cg_previous_direction[i] = 0; "
           "cg_loop_playing[i] = 0; cg_loop_gain[i] = 0; cg_loop_target[i] = 0; }\n";
    auto animMode = [](const QString &s) -> QString {
        return s == QStringLiteral("pingpong") ? QStringLiteral("GAME_ANIM_PINGPONG") :
               s == QStringLiteral("once") ? QStringLiteral("GAME_ANIM_ONCE") :
               QStringLiteral("GAME_ANIM_LOOP");
    };
    for (int i = 0; i < np + nw; ++i) {
        const bool collect = i < np;
        const int ix = collect ? i : i - np;
        const Resource &r = *(collect ? pickups.at(ix) : platforms.at(ix));
        const int path = collect ? pickupPaths.at(ix) : platformPaths.at(ix);
        const QString bob = spriteSymbol(r);
        const QString sprite = QStringLiteral("&") + bob;
        const QString target = QStringLiteral("&") + (collect ? QStringLiteral("pickups") : QStringLiteral("platforms")) +
                               QStringLiteral("[%1]").arg(ix);
        C << "    /* " << (collect ? "Collectable" : "World Object") << " " << ix << ": "
          << QString(r.name).replace(QLatin1Char('\n'), QLatin1Char(' '))
               .replace(QStringLiteral("*/"), QStringLiteral("* /")) << " */\n";
        if (collect) {
            const QString pickConst = QStringList{QString(), QStringLiteral("GAME_PICKUP_COIN"),
                QStringLiteral("GAME_PICKUP_HEALTH"), QStringLiteral("GAME_PICKUP_KEY"),
                QStringLiteral("GAME_PICKUP_GEM")}.at(qBound(1,r.pickupKind,4));
            C << "    if (!game_collectable_start(" << target << ", " << sprite << ", "
              << pickConst << ", " << r.objectValue << ")) return 0;\n"
              << "    pickups[" << ix << "].width = " << r.hitWidth << ";\n"
              << "    pickups[" << ix << "].height = " << r.hitHeight << ";\n"
              << "    pickups[" << ix << "].respawn_frames = " << r.respawnFrames << ";\n"
              << "    pickups[" << ix << "].active = " << (r.objectInitiallyActive ? "1" : "0") << ";\n";
        } else {
            const QString kind = r.objectType == QStringLiteral("lift") ? QStringLiteral("GAME_OBJECT_LIFT") :
                r.objectType == QStringLiteral("conveyor") ? QStringLiteral("GAME_OBJECT_CONVEYOR") :
                r.objectType == QStringLiteral("trigger") ? QStringLiteral("GAME_OBJECT_TRIGGER") :
                r.objectType == QStringLiteral("door") ? QStringLiteral("GAME_OBJECT_DOOR") :
                r.objectType == QStringLiteral("deathzone") ? QStringLiteral("GAME_OBJECT_DEATH_ZONE") :
                QStringLiteral("GAME_OBJECT_SPRING");
            C << "    if (!game_world_object_start(" << target << ", " << kind << ", "
              << sprite << ", " << r.x << ", " << r.y << ", "
              << r.hitWidth << ", " << r.hitHeight << ")) return 0;\n";
            C << "    platforms[" << ix << "].active = " << (r.objectInitiallyActive ? "1" : "0") << ";\n";
            if (r.objectType == QStringLiteral("trigger")) {
                C << "    platforms[" << ix << "].trigger_press = " << (r.triggerPress ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].trigger_one_shot = " << (r.triggerOneShot ? "1" : "0") << ";\n";
            }
            if (r.objectType == QStringLiteral("conveyor"))
                C << "    platforms[" << ix << "].conveyor_speed = " << r.conveyorSpeed << ";\n";
            if (r.objectType == QStringLiteral("spring")) {
                C << "    platforms[" << ix << "].spring_strength = " << r.springStrength << ";\n";
                C << "    platforms[" << ix << "].spring_launch_x = " << r.springLaunchX << ";\n";
                C << "    platforms[" << ix << "].touch_activation = "
                  << (r.springTouch ? "1" : "0") << ";\n";
                C << "    platforms[" << ix << "].spring_slide = "
                  << (r.springSlide ? "1" : "0") << ";\n";
                C << "    platforms[" << ix << "].allow_jump_boost = "
                  << (r.springJumpBoost ? "1" : "0") << ";\n";
            }
        }
        if (path >= 0) {
            const QString sym = splineSymbol(path);
            const QString var = QStringLiteral("%1_path_%2").arg(collect ? QStringLiteral("pickup") : QStringLiteral("platform")).arg(ix);
            C << "    start_spline(&" << var << ", " << sprite << ", "
              << sym << "_path, " << sym << "_count, " << sym << "_frames, " << sym << "_loop);\n"
              << "    set_spline_pos(&" << var << ", " << r.x << ", " << r.y << ");\n"
              << "    " << (collect ? "pickups" : "platforms") << "[" << ix << "].spline = &" << var << ";\n";
        }
        if (r.objectAnimated) {
            const QString var = QStringLiteral("%1_anim_%2").arg(collect ? QStringLiteral("pickup") : QStringLiteral("platform")).arg(ix);
            C << "    if (!start_animation(&" << var << ", " << sprite << ", "
              << r.animFirst << ", " << r.animCount << ", " << r.animTicks << ", "
              << animMode(r.animMode) << ")) return 0;\n"
              << "    " << (collect ? "pickups" : "platforms") << "[" << ix << "].animation = &" << var << ";\n";
        }
    }
    // Conveyor ambient sounds begin at world-object init; enable Loop in the
    // SOUND resource to keep them playing. Gain fades in via draw().
    if (!usedSfx.isEmpty()) {
        for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            if (r.objectType == QStringLiteral("conveyor") && !r.sfxAmbient.isEmpty()) {
                C << "    if (platforms[" << i << "].active) {\n"
                  << "        " << cSfxCall(r.sfxAmbient, QStringLiteral("platforms[%1].x").arg(i), r.audioRadius);
                C << "        sound_setvolume(" << soundById.value(r.sfxAmbient)->audio.channel << ", 0);\n";
                C << "        cg_loop_playing[" << i << "] = 1;\n"
                  << "        cg_loop_gain[" << i << "] = 0;\n"
                  << "        cg_loop_target[" << i << "] = 255;\n"
                  << "    }\n";
            }
        }
    }
    C << "    return 1;\n}\n\n"
         "void gameworlditems_update(uint16_t frames)\n{\n";
    if (nw) C << "    game_world_objects_update(platforms, " << nw << ", frames);\n";
    if (np && !usedSfx.isEmpty()) C << "    for (uint16_t i = 0; i < " << np
        << "; ++i) cg_pickup_was_inactive[i] = (uint8_t)!pickups[i].active;\n";
    if (np) C << "    game_collectables_update(pickups, " << np << ", frames);\n";
    if (!usedSfx.isEmpty()) {
        for (int i = 0; i < np; ++i) {
            const Resource &r = *pickups.at(i);
            if (r.respawnFrames && !r.sfxRespawn.isEmpty()) {
                // The timer reaches zero on this frame, once. An active item
                // with respawn_frames>0 has no other way to reach that state.
                C << "    if (pickups[" << i << "].active && pickups[" << i << "].respawn_frames "
                     "&& pickups[" << i << "].respawn_left == 0 "
                     "&& frames && cg_pickup_was_inactive[" << i << "]) {\n"
                  << "        " << cSfxCall(r.sfxRespawn, QStringLiteral("pickups[%1].x").arg(i), r.audioRadius)
                  << "    }\n";
            }
        }
        for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            if (r.objectType == QStringLiteral("conveyor") && !r.sfxAmbient.isEmpty()) {
                C << "    if (platforms[" << i << "].active && !cg_loop_playing[" << i << "]) {\n"
                  << "        " << cSfxCall(r.sfxAmbient, QStringLiteral("platforms[%1].x").arg(i), r.audioRadius)
                  << "        sound_setvolume(" << soundById.value(r.sfxAmbient)->audio.channel << ", 0);\n"
                  << "        cg_loop_playing[" << i << "] = 1; cg_loop_gain[" << i << "] = 0;\n"
                  << "    }\n"
                  << "    cg_loop_target[" << i << "] = platforms[" << i << "].active ? 255 : 0;\n";
            }
            if (r.objectType != QStringLiteral("lift")) continue;
            const QString base = QStringLiteral("platforms[%1]").arg(i);
            C << "    {\n        int32_t dx = " << base << ".x - " << base << ".previous_x;\n"
              << "        int32_t dy = " << base << ".y - " << base << ".previous_y;\n"
              << "        uint8_t moving = dx != 0 || dy != 0;\n"
              << "        int8_t dir = (dx ? (dx > 0 ? 1 : -1) : (dy ? (dy > 0 ? 1 : -1) : 0));\n";
            if (!r.sfxStart.isEmpty())
                C << "        if (moving && !cg_was_moving[" << i << "]) "
                  << cSfxCall(r.sfxStart, base + QStringLiteral(".x"), r.audioRadius);
            if (!r.sfxReverse.isEmpty())
                C << "        if (moving && cg_previous_direction[" << i
                  << "] && dir != cg_previous_direction[" << i << "]) "
                  << cSfxCall(r.sfxReverse, base + QStringLiteral(".x"), r.audioRadius);
            if (!r.sfxStop.isEmpty())
                C << "        if (!moving && cg_was_moving[" << i << "]) "
                  << cSfxCall(r.sfxStop, base + QStringLiteral(".x"), r.audioRadius);
            if (!r.sfxMove.isEmpty()) {
                C << "        if (moving && !cg_was_moving[" << i << "]) {\n"
                  << "            " << cSfxCall(r.sfxMove, base + QStringLiteral(".x"), r.audioRadius)
                  << "            sound_setvolume(" << soundById.value(r.sfxMove)->audio.channel << ", 0);\n"
                  << "            cg_loop_playing[" << i << "] = 1; cg_loop_gain[" << i << "] = 0;\n"
                  << "        }\n"
                  << "        cg_loop_target[" << i << "] = moving ? 255 : 0;\n";
            }
            C << "        cg_was_moving[" << i << "] = moving;\n"
              << "        if (moving) cg_previous_direction[" << i << "] = dir;\n"
              << "    }\n";
        }
    }
    C << "}\n\n";
    if (nw) {
        if (m_tilemapEnabled) {
            C << "/* Use the same walls/slopes as game_tile_player_run() when\n"
                 "   a moving platform carries the player. Generated automatically. */\n"
                 "static uint8_t cg_world_player_blocked(int32_t x, int32_t y,\n"
                 "    uint16_t width, uint16_t height, void *context)\n"
                 "{\n"
                 "    return game_tilemap_actor_blocked((const game_tilemap_t *)context,\n"
                 "                                     x, y, width, height);\n"
                 "}\n\n";
        }
        C << "void gameworlditems_before(game_world_player_t *player)\n{\n";
        if (m_tilemapEnabled) C << "    if (game_death_is_dead()) return;\n";
        if (m_tilemapEnabled)
            C << "    if (player) {\n"
                 "        player->position_blocked = cg_world_player_blocked;\n"
                 "        player->collision_context = &game_level1;\n"
                 "    }\n";
        C << "    game_world_objects_before(platforms, " << nw << ", player);\n}\n\n"
          << "void gameworlditems_after(game_world_player_t *player)\n{\n";
        if (m_tilemapEnabled) C << "    if (game_death_is_dead()) return;\n";
        C << "    game_world_objects_after(platforms, " << nw << ", player);\n";
        if (m_tilemapEnabled) {
            C << "    /* Hazard Zone: ENTERED once, INSIDE each frame, EXITED on leaving. */\n"
                 "    uint8_t in_hazard_zone = (uint8_t)(player && player->x100 && player->y100 &&\n"
                 "        player->width && player->height &&\n"
                 "        game_world_objects_death_zone(platforms, " << nw
              << ", *player->x100 / 100, *player->y100 / 100, player->width, player->height));\n"
                 "    uint8_t was_in_hazard_zone = cg_hazard_zone_contact;\n"
                 "    cg_hazard_zone_contact = in_hazard_zone;\n"
                 "    if (player && player->x100 && player->y100) {\n"
                 "        if (in_hazard_zone && !was_in_hazard_zone)\n"
                 "            game_hazard_notify(GAME_HAZARD_ZONE_ENTERED, *player->x100 / 100, *player->y100 / 100);\n"
                 "        else if (in_hazard_zone)\n"
                 "            game_hazard_notify(GAME_HAZARD_ZONE_INSIDE, *player->x100 / 100, *player->y100 / 100);\n"
                 "        else if (was_in_hazard_zone)\n"
                 "            game_hazard_notify(GAME_HAZARD_ZONE_EXITED, *player->x100 / 100, *player->y100 / 100);\n"
                 "        /* Callback may explicitly kill or teleport the player. */\n"
                 "        if (game_death_is_dead()) return;\n"
                 "    }\n";
        }
        for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            if (r.objectType == QStringLiteral("spring") && !r.sfxSpring.isEmpty()) {
                C << "    if (platforms[" << i << "].spring_triggered) "
                  << cSfxCall(r.sfxSpring, QStringLiteral("platforms[%1].x").arg(i), r.audioRadius);
            }
        }
        if (nt) C << "    if (player && player->x100 && player->y100 && player->width && player->height)\n"
                    "        gameworlditems_trigger(*player->x100 / 100, *player->y100 / 100,\n"
                    "            player->width, player->height, (getjoyport() & BTN_FIRE2) != 0);\n";
        C << "}\n\n";
    }
    if (np) {
        C << "uint16_t gameworlditems_check(int32_t x, int32_t y, uint16_t w, uint16_t h,\n"
             "    game_pickup_callback_t callback, void *user)\n{\n";
        if (m_tilemapEnabled) C << "    if (game_death_is_dead()) return 0;\n";
        if (pickupSound || linkedKeys) {
            C << "    uint8_t was_active[" << np << "];\n"
              << "    for (uint16_t i = 0; i < " << np
              << "; ++i) was_active[i] = pickups[i].active;\n";
        }
        C << "    uint16_t count = game_collectables_check(pickups, " << np << ", x, y, w, h, callback, user);\n";
        for (int i = 0; i < np; ++i) {
            const Resource &r = *pickups.at(i);
            if (r.pickupKind != 3) continue;
            const QString action = linkedAction(r);
            if (action.isEmpty()) continue;
            C << "    if (was_active[" << i << "] && !pickups[" << i << "].active) "
              << action << "\n";
        }
        if (!usedSfx.isEmpty()) {
            for (int i = 0; i < np; ++i) {
                const Resource &r = *pickups.at(i);
                if (!r.sfxPickup.isEmpty())
                    C << "    if (was_active[" << i << "] && !pickups[" << i << "].active) "
                      << cSfxCall(r.sfxPickup, QStringLiteral("pickups[%1].x").arg(i), r.audioRadius);
            }
        }
        C << "    return count;\n}\n\n";
    }
    if (nt) {
        C << "uint16_t gameworlditems_trigger(int32_t x, int32_t y, uint16_t w, uint16_t h, uint8_t pressed)\n{\n"
          << "    uint16_t fired = game_world_objects_trigger(platforms, " << nw
          << ", x, y, w, h, pressed);\n";
        for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            if (r.objectType != QStringLiteral("trigger")) continue;
            const QString action = linkedAction(r);
            const QString audio = musicAction(r);
            if (action.isEmpty() && audio.isEmpty()) continue;
            C << "    if (platforms[" << i << "].trigger_fired) { "
              << action << " " << audio << " }\n";
        }
        C << "    return fired;\n}\n\n";
    }
    C << "void gameworlditems_draw(int32_t camera_x, int32_t camera_y)\n{\n";
    if (nw) C << "    game_world_objects_draw(platforms, " << nw << ", camera_x, camera_y);\n";
    if (np) C << "    game_collectables_draw(pickups, " << np << ", camera_x, camera_y);\n";
    if (!usedSfx.isEmpty()) {
        C << "    cg_audio_camera_x = camera_x;\n";
        for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            const QString soundId = r.objectType == QStringLiteral("conveyor")
                ? r.sfxAmbient : r.objectType == QStringLiteral("lift") ? r.sfxMove : QString();
            if (soundId.isEmpty()) continue;
            const Resource &sound = *soundById.value(soundId);
            const int step = r.audioFadeFrames <= 0 ? 255 : qMax(1, (255 + r.audioFadeFrames - 1) / r.audioFadeFrames);
            C << "    if (cg_loop_playing[" << i << "]) {\n"
              << "        if (cg_loop_gain[" << i << "] < cg_loop_target[" << i << "]) {\n"
              << "            uint16_t next = cg_loop_gain[" << i << "] + " << step << ";\n"
              << "            cg_loop_gain[" << i << "] = next > 255 ? 255 : next;\n"
              << "        } else if (cg_loop_gain[" << i << "] > cg_loop_target[" << i << "]) {\n"
              << "            cg_loop_gain[" << i << "] = cg_loop_gain[" << i << "] > " << step
              << " ? cg_loop_gain[" << i << "] - " << step << " : 0;\n"
              << "        }\n"
              << "        sound_setvolume(" << sound.audio.channel << ", (uint16_t)("
              << "cg_audio_volume(" << qBound(0,sound.audio.volume,1024) << ", platforms[" << i << "].x, "
              << r.audioRadius << ") * cg_loop_gain[" << i << "] / 255));\n"
              << "        sound_setpanning(" << sound.audio.channel << ", cg_audio_pan("
              << qBound(-127,sound.audio.pan,127) << ", platforms[" << i << "].x, "
              << r.audioRadius << "));\n"
              << "        if (cg_loop_gain[" << i << "] == 0 && cg_loop_target[" << i << "] == 0) {\n"
              << "            sound_stop(" << sound.audio.channel << "); cg_loop_playing[" << i << "] = 0;\n"
              << "        }\n    }\n";
        }
    }
    C << "}\n";
    G << "CODERGIRL — GENERATED WORLD OBJECTS GUIDE\n"
         "========================================\n\n"
         "Regeneration replaces gameworlditems.c/.h/.txt. For hand-written notes,\n"
         "use a separate filename. User-owned main.c is never overwritten.\n\n"
         "Configured objects: " << np << " collectable(s), " << nw << " world object(s) (including " << nt << " triggers).\n"
         "Each uses its own graphics instance and WORLD coordinates from Game Designer.\n\n"
         "After gameassets_init(), call gameworlditems_init().\n"
         "Each frame call gameworlditems_update(1) before player physics.\n";
    if (nw && m_tilemapEnabled)
        G << "Moving lift wall safety: CoderGirl automatically connects this\n"
             "level's solid/slope collision map. The helper carries the player\n"
             "only to the last safe pixel before a wall. You do not need to\n"
             "add a collision callback in main.c. Update Project updates BOTH\n"
             "World Objects and Tilemap helpers for this feature.\n\n";
    if (nw) G << "Bind game_world_player_t to the LIVE player physics fields,\n"
                 "then call gameworlditems_before()/after() around player physics.\n"
                 "For exact spring jump behaviour with game_tile_player_t also bind:\n"
                 "  world_player.jump_held = &player_physics.jump_held;\n"
                 "  world_player.coyote = &player_physics.coyote;\n"
                 "  world_player.jump_speed = &player_physics.jump_speed;\n"
                 "Spring touch activation is per-object. OFF requires landing on top;\n"
                 "ON launches on any hitbox contact, with no repeated bounce while overlapping.\n"
                 "Jump + spring is per-object. OFF uses spring strength alone,\n"
                 "ON adds jump speed ONLY on a new Jump press at contact.\n";
    if (m_tilemapEnabled) G << "Player death: register game_death_set_callback(on_player_death, user)\n"
        "once after game_tile_player_start(). Both hazardous tile collisions and\n"
        "configured Hazard Zones dispatch a contact callback (with cause and WORLD X/Y).\n"
        "Hazards report ENTERED, INSIDE each update, EXITED after leaving.\n"
        "Contact is nonfatal; only game_death_mark_dead() or explicit death\n"
        "stops player physics. Respawn with game_tile_player_reset().\n"
        "See gametilemap.txt for all six hazard reason constants.\n";
    if (np) G << "Call gameworlditems_check(...) after physics using player WORLD position.\n";
    if (nt) G << "Switches and buttons run AUTOMATICALLY inside gameworlditems_after().\n"
                 "It checks player contact and FIRE2, then applies the configured\n"
                 "enable/disable/toggle target action. No extra main.c call is needed\n"
                 "if your existing main.c already calls gameworlditems_after().\n"
                 "The optional gameworlditems_trigger(...) API is available for\n"
                 "custom loops that intentionally skip the normal after() step.\n"
                 "Repeatable switches fire once per contact or button press.\n"
                 "One-shot switches deactivate themselves. Targets may start disabled.\n"
             "Trigger music actions play a selected Music resource or stop playback.\n"
             "Call music_update() in the main loop (the generated example does).\n"
                 "A Door / Solid blocker is collidable while enabled and vanishes when disabled.\n"
                 "Do NOT paint a permanent tilemap solid over a door: tilemap walls\n"
                 "are separate and will continue blocking after the door disappears.\n";
    G << "Call gameworlditems_draw(camera_x,camera_y) after selecting the foreground buffer.\n"
         "Do not call offset_spline() on attached object splines: draw applies camera offset.\n"
         "Gameassets' drawworld() automatically excludes managed object sprites.\n\n"
         "Full, current example: open maingame.c.txt in the Project Tree.\n";
    if (!usedSfx.isEmpty()) {
        G << "\nSTAGE 3.12 SOUND EVENTS\n"
             "------------------------\n"
             "Sound resources are selected in the Game Object Properties window,\n"
             "and generated playsound... functions are provided by gameassets.\n"
             "Spring launches, pickups, respawns, lift start/stop/reverse and\n"
             "continuous movement / conveyor ambience play automatically.\n"
             "Enable Loop on the SOUND resource for continuous sounds.\n"
             "Loop fade and stereo panning update once per gameworlditems_draw().\n"
             "Radius 0 disables automatic distance attenuation and positional pan.\n"
             "IMPORTANT: SIDBOX has 8 sample channels. Sounds using the SAME\n"
             "channel can interrupt one another. Assign distinct channels to\n"
             "simultaneously playing sounds in Game Resources > Sounds.\n"
             "Do not free assets while a sample is playing; stop audio first.\n";
    }
    const QString folder = QDir(QFileInfo(m_filePath).absolutePath()).filePath(QStringLiteral("gamehelpers"));
    if (!QDir().mkpath(folder)) { if (error) *error = tr("Cannot create %1").arg(folder); return false; }
    struct Out { QString name, data; };
    for (const Out &out : {Out{QStringLiteral("gameworlditems.h"),h},
                           Out{QStringLiteral("gameworlditems.c"),c},
                           Out{QStringLiteral("gameworlditems.txt"),guide}}) {
        QSaveFile file(QDir(folder).filePath(out.name));
        const QByteArray bytes = out.data.toUtf8();
        if (!file.open(QIODevice::WriteOnly) || file.write(bytes) != bytes.size() || !file.commit()) {
            file.cancelWriting();
            if (error) *error = tr("Cannot write generated %1").arg(out.name);
            return false;
        }
    }
    return true;
}

// Stage 3.29: generate a real V1 starter program from the current design.
// maingame.c.txt contains valid C (including explanatory comments). It can
// safely be copied to main.c without manually assembling different snippets.
// Never overwrite the programmer's real main.c.
bool SidboxGameDesigner::exportExampleMain(QString *error)
{
    const Resource *player = nullptr;
    int pickups = 0, worldObjects = 0, spriteCount = 0;
    bool hasMusic = false, hasAudio = false, hasBackgroundSprites = false;
    bool hasHazards = m_tilemapEnabled && m_tilemap.collisions.contains(char(5));
    bool hasCustomZones = false;
    bool usedCustomZones[8] = {false};
    if (m_tilemapEnabled) {
        for (char typeChar : m_tilemap.collisions) {
            const int type = quint8(typeChar);
            const int zone = type >= 9 && type <= 16 ? type - 9
                : type >= 17 && type <= 24 ? type - 17 : -1;
            if (zone >= 0) { hasCustomZones = true; usedCustomZones[zone] = true; }
        }
    }
    QStringList attachedSplineDescriptions;
    QSet<QString> attachedSplineIds;
    int validSplineCount = 0;
    for (const SplinePath &path : m_splinePaths)
        if (path.points.size() >= 2) ++validSplineCount;
    const bool hasSplines = validSplineCount > 0;
    const bool dualPlane = m_planeMode->currentData().toString() == QStringLiteral("dual");
    for (const Resource &r : m_resources) {
        if (r.kind == QStringLiteral("music") && !r.path.isEmpty()) hasMusic = true;
        if (r.kind == QStringLiteral("sound") && !r.path.isEmpty()) hasAudio = true;
        if ((r.kind == QStringLiteral("background") && r.backgroundMode == QStringLiteral("sprite"))
            || (r.kind == QStringLiteral("sprite") && r.plane == QStringLiteral("background")))
            hasBackgroundSprites = true;
        if (r.kind != QStringLiteral("sprite") || r.path.isEmpty()) continue;
        if (r.objectType != QStringLiteral("decoration") && !r.objectSplineId.isEmpty()) {
            for (int i = 0; i < m_splinePaths.size(); ++i) {
                if (m_splinePaths.at(i).id != r.objectSplineId ||
                    m_splinePaths.at(i).points.size() < 2) continue;
                attachedSplineIds.insert(r.objectSplineId);
                // Describe exactly what the generated world-object code runs.
                QString safeName = r.name;
                safeName.replace(QLatin1Char('\n'), QLatin1Char(' '));
                safeName.replace(QStringLiteral("*/"), QStringLiteral("* /"));
                QString safePath = m_splinePaths.at(i).name;
                safePath.replace(QLatin1Char('\n'), QLatin1Char(' '));
                safePath.replace(QStringLiteral("*/"), QStringLiteral("* /"));
                attachedSplineDescriptions << QStringLiteral(" *   %1 -> %2 (%3)\n")
                    .arg(safeName).arg(safePath).arg(splineSymbol(i));
                break;
            }
        }
        if (r.objectType == QStringLiteral("deathzone")) hasHazards = true;
        ++spriteCount;
        if (r.objectType == QStringLiteral("collectable")) ++pickups;
        else if (r.objectType != QStringLiteral("decoration")) ++worldObjects;
        else if (r.name.trimmed().compare(QStringLiteral("player"), Qt::CaseInsensitive) == 0)
            player = &r;
    }
    const bool hasMap = m_tilemapEnabled;
    const bool hasPhysics = hasMap && player;
    const bool hasObjects = pickups || worldObjects;
    const bool hasMapOnly = hasMap && !player;
    const QString playerName = hasPhysics ? spriteSymbol(*player) : QString();
    QString program;
    QTextStream out(&program);
    out << R"CG(/*
 * SIDBOX IDE / GamerGirl - GENERATED V1 GAME STARTER (Stage 3.44)
 * ==============================================================
 * This is REAL C source code, not a list of pseudocode snippets.
 * It is generated from the resources in the CURRENT .sbgm design.
 *
 * START HERE:
 *  1. In Game Designer select Update Game Project to export the helpers.
 *  2. The IDE regenerates main.c only while it remains IDE-owned.
 *     Editing and saving main.c transfers ownership permanently to you.
 *  3. Put exported PPB, music and SD .map resources on the SIDBOX SD card.
 *  4. Add your game rules inside the clearly marked sections.
 *
 * After changing your Game Designer resources, regenerate this example.
 * User-owned main.c is never replaced. maingame.c.txt is always updated.
 *
 * WORLD coordinates are map positions. SCREEN coordinates subtract camera.
 * Game objects are managed by gameworlditems; do not draw them twice.
 *
 * CURRENT DESIGN:
)CG";
    out << " * Tilemap: " << (hasMap ? (m_tilemapExternal ? "SD .map" : "embedded C") : "none") << "\n"
        << " * Player sprite (must be named 'player'): "
        << (player ? spriteSymbol(*player) : QStringLiteral("not found")) << "\n"
        << " * Sprites: " << spriteCount << ", collectables: " << pickups
        << ", other game objects: " << worldObjects << "\n"
        << " * Music: " << (hasMusic ? "present" : "none")
        << ", sound: " << (hasAudio ? "present" : "none") << "\n"
        << " * Spline paths: " << validSplineCount
        << ", attached moving sprites: " << attachedSplineDescriptions.size() << "\n";
    if (hasMap && (m_tilemap.collisions.contains(char(7)) || !m_tilemap.collisionPlacements.isEmpty()))
        out << " * Custom collision surfaces are handled automatically by game_tile_player_run().\n"
               " * Point-defined stamps use shared definitions and whole placements (SBMP v4).\n"
               " * Legacy Stage 3.35 painted slopes remain available as SBMP v3 data.\n"
               " * Update gametilemap.c/.h to the new shape-aware helpers before building.\n";
    if (!hasMap) out << " * No tilemap: this starter displays placed sprites without tile physics.\n"
                       " * Add a tilemap and regenerate to enable built-in player movement.\n";
    if (hasMapOnly) out << " * No ordinary sprite named 'player' found: the map renders, but\n"
                          " * player movement is not invented. Name the player sprite 'player'\n"
                          " * (case-insensitive), attach its image, and regenerate.\n";
    if (!hasPhysics && hasObjects)
        out << " * Game objects draw/animate, but need a physics player to trigger\n"
               " * pickups, switches, lifts and springs automatically.\n";
    out << R"CG( */
#include <stdint.h>
#include <stddef.h>
#include "apis.h"
#include "main.h"
#include "gameassets/gameassets.h"
)CG";
    if (hasMap)
        out << "#include \"gamehelpers/gametilemap.h\"\n"
               "#include \"gamelevels/level1.h\"\n";
    if (hasObjects)
        out << "#include \"gamehelpers/gameworlditems.h\"\n";
    if (hasSplines)
        out << "#include \"gamehelpers/gamespline.h\"\n"
               "#include \"gamehelpers/splinepaths.h\"\n";
    out << R"CG(
#define VIEW_W 480
#define VIEW_H 320

/* Two independent foreground buffers, swapped after each frame. */
static gfx_bitmap_t *front[2];
static uint8_t draw_index = 0;
)CG";
    if (hasPhysics) {
        out << R"CG(
/* This is the ONE physical player. Position and velocity are in 1/100 px. */
static game_tile_player_t player_physics = {0};
)CG";
        if (worldObjects) {
            out << R"CG(
/* Adapter POINTS INTO player_physics, so spring/lift movement is live. */
static game_world_player_t world_player = {0};
)CG";
        }
    }
    if (hasPhysics && pickups) {
        out << R"CG(
static uint32_t score = 0;
static void on_pickup(game_collectable_t *item, void *user)
{
    uint32_t *points = (uint32_t *)user;
    if (!item || !points) return;
    *points += item->value;  /* Replace with your own key/health/score rules. */
}
)CG";
    }
    if (hasPhysics && hasHazards) {
        out << R"CG(
/* Hazard contacts NEVER kill automatically. YOUR game decides what to do. */
static void on_player_death(uint8_t reason, int32_t x, int32_t y, void *user)
{
    (void)x; (void)y; (void)user;
    if (reason == GAME_HAZARD_TILE_ENTERED || reason == GAME_HAZARD_ZONE_ENTERED) {
        /* Entered: damage once, or start an effect. */
    } else if (reason == GAME_HAZARD_TILE_INSIDE || reason == GAME_HAZARD_ZONE_INSIDE) {
        /* Inside: fired each physics update; use a timer for gradual damage. */
    } else if (reason == GAME_HAZARD_TILE_EXITED || reason == GAME_HAZARD_ZONE_EXITED) {
        /* Exited: stop the effect. */
    } else if (reason == GAME_DEATH_SCRIPT) {
        /* Deliberate scripted death. */
    }
    /* game_death_mark_dead() freezes physics. game_tile_player_reset()
       resumes at your chosen spawn point; neither is automatic. */
}
)CG";
    }
    if (hasPhysics && hasCustomZones) {
        out << "/* CUSTOM ZONES IN THIS LEVEL (names are documentation only):\n";
        for (int i = 0; i < 8; ++i) {
            if (!usedCustomZones[i]) continue;
            QString label = i < m_tilemap.customZoneNames.size()
                ? m_tilemap.customZoneNames.at(i) : QString();
            if (label.isEmpty()) label = QStringLiteral("Custom %1").arg(i+1);
            label.replace(QStringLiteral("*/"), QStringLiteral("* /"));
            label.replace(QLatin1Char('\n'), QLatin1Char(' '));
            out << " *   Zone " << (i+1) << ": " << label << " ("
                << sidboxTilemapZoneMacroName(m_tilemap, i + 1) << ")\n";
        }
        out << " */\n";
        QString zoneCallbackExample = QString::fromUtf8(R"CG(
/* OPTIONAL PROGRAMMABLE ZONES: these comments are EXAMPLES, not automatic
 * physics changes. Each custom tile zone reports 1..8 and ENTERED/INSIDE/EXITED.
 * Solid and pass-through versions share the same logical zone number.
 * Use the generated GAME_ZONE_ID_* names from gamelevels/level1.h,
 * NOT hard-coded 1..8 numbers. Re-export after renaming a zone.
 * The commented physics presets are EXAMPLES; names do not activate them.
 * Change or remove these examples to suit your game. */
static void on_custom_zone(uint8_t zone, uint8_t event,
    int32_t x, int32_t y, void *user)
{
    (void)x; (void)y;
    game_tile_player_t *p = (game_tile_player_t *)user;
    if (!p) return;
    if (event == GAME_ZONE_ENTERED) {
        switch (zone) {
            case @ZONE_1@: /* Example: slow */
                /* game_tile_player_set_physics_slow(p); */ break;
            case @ZONE_2@: /* Example: water */
                /* game_tile_player_set_physics_water(p); */ break;
            case @ZONE_3@: /* Example: ice */
                /* game_tile_player_set_physics_ice(p); */ break;
            case @ZONE_4@: /* Example: space */
                /* game_tile_player_set_physics_space(p); */ break;
            case @ZONE_5@: /* Example: floating */
                /* game_tile_player_set_physics_floating(p); */ break;
            case @ZONE_6@: /* Example: jetpack */
                /* game_tile_player_set_physics_jetpack(p); */ break;
            case @ZONE_7@: /* Example: gravity */
                /* game_tile_player_set_gravity(p, 10); */ break;
            case @ZONE_8@: /* Example: walk speed */
                /* game_tile_player_set_walk_speed(p, 2); */ break;
        }
    } else if (event == GAME_ZONE_INSIDE) {
        /* Example: count time inside for damage, sound or wind effects.
         * Updraft: apply_force(p, 0.0f, -0.40f); // optional upward thrust
         * Call the ordinary player-run OR the no-input player-step once
         * per frame to advance physics and keep collision detection active.
         */
    } else if (event == GAME_ZONE_EXITED) {
        /* Optional: restore defaults when leaving a zone.
         * game_tile_player_set_physics_normal(p);
         * If zones overlap, decide which remaining zone should take priority. */
    }
}
)CG");
        // Each game's labels produce C identifiers that match level1.h.
        for (int zone = 1; zone <= 8; ++zone)
            zoneCallbackExample.replace(QStringLiteral("@ZONE_%1@").arg(zone),
                sidboxTilemapZoneMacroName(m_tilemap, zone));
        out << zoneCallbackExample;
    }
    if (hasPhysics) {
        out << R"CG(
/* OPTIONAL: EXTERNAL FORCES / SPACE THRUSTERS
 * -------------------------------------------
 * apply_force(&player_physics, x, y) ADDS momentum in pixels/frame.
 * +X = right, -X = left; +Y = down, -Y = upward thrust.
 * It does NOT move the player immediately, so collisions remain safe.
 * Call game_tile_player_run() OR game_tile_player_step() once per frame,
 * not both! A simple wind or explosion also works in NORMAL movement:
 *
 *   apply_force(&player_physics, 2.0f, -1.0f); // one-time knockback
 *   // ... your usual game_tile_player_run() then integrates the force.
 *
 * OPTIONAL zero-gravity, joystick-controlled spacecraft:
 *   1. Enter the space zone in your on_custom_zone() callback (if present).
 *      Set your own bool/flag named in_space to 1 on ENTERED,
 *      and set it to 0 on EXITED. Compare zone with your generated
 *      GAME_ZONE_ID_SPACE (if you named a zone Space).
 *      game_tile_player_set_physics_space(&player_physics);
 *      game_tile_player_set_gravity(&player_physics, 0);
 *   2. Replace the game_tile_player_run() line in the loop below with:
 *
 *   if (in_space) {
 *       const uint8_t joy = getjoyport();
 *       if (joy & BTN_LEFT)  apply_force(&player_physics, -0.18f,  0.0f);
 *       if (joy & BTN_RIGHT) apply_force(&player_physics,  0.18f,  0.0f);
 *       if (joy & BTN_UP)    apply_force(&player_physics,  0.0f, -0.18f);
 *       if (joy & BTN_DOWN)  apply_force(&player_physics,  0.0f,  0.18f);
 *       game_tile_player_step(&player_physics, 1);
 *   } else {
 *       game_tile_player_run(&player_physics, getjoyport(), 1);
 *   }
 *
 *   3. On leaving space call game_tile_player_set_physics_normal().
 *
 * External X momentum has configurable drag (percent lost per tick):
 *   game_tile_player_set_force_drag(&player_physics, 0); // no drag: space
 *   game_tile_player_set_force_drag(&player_physics, 12); // slow down
 * Space preset sets X drag to 0 automatically. Gravity remains separate.
 * Existing solids, ceilings, slopes, zone events and springs still work.
 * Force inputs and callbacks are OPTIONAL. None are enabled here by default.
 */
)CG";
    }
    if (hasSplines) {
        out << R"CG(
/* SPLINE MOVEMENT -- GENERATED FROM YOUR GAME DESIGN
 * -------------------------------------------------
 * Update Game Project installs gamehelpers/gamespline.c/.h and exports
 * gamehelpers/splinepaths.c/.h; both .c files must be compiled by the IDE.
 * The path data is generated from the spline nodes in Game Designer.
 *
 * FOR SPRITES CONFIGURED AS GAME OBJECTS:
 * Game Object Properties -> Movement spline attaches the saved path.
 * The generated gameworlditems.c does ALL the spline setup and movement:
 *   gameworlditems_init()       -> start_spline() + set_spline_pos()
 *   gameworlditems_update(1)    -> run_spline() once per frame
 *   gameworlditems_draw(cx,cy)  -> drawing with the camera offset
 * Those calls are already in THIS main.c below when objects exist.
 * Do NOT call run_spline() again for an attached object, or draw it twice.
 *
 * ATTACHED OBJECTS IN THIS DESIGN:
)CG";
        if (attachedSplineDescriptions.isEmpty())
            out << " *   (none yet -- assign a Movement spline in Game Object Properties)\n";
        else
            for (const QString &description : attachedSplineDescriptions) out << description;
        out << " *\n * EXPORTED PATHS:\n";
        for (int i = 0; i < m_splinePaths.size(); ++i) {
            if (m_splinePaths.at(i).points.size() < 2) continue;
            const QString symbol = splineSymbol(i);
            out << " *   " << symbol << "_path, " << symbol << "_count, "
                << symbol << "_frames, " << symbol << "_loop"
                << (attachedSplineIds.contains(m_splinePaths.at(i).id)
                       ? "  [attached]" : "  [not attached]") << "\n";
        }
        out << R"CG( *
 * OPTIONAL: HAND-CONTROLLED SPLINE (for an ordinary, non-managed sprite).
 * The following is REAL C you may copy into your own game if you want to
 * control a spline manually. It is intentionally NOT executed by default.
 * Attach a spline through Game Object Properties instead for no-code movement.
 *
 * Near the top of main.c:
 *     static game_spline_t custom_motion = {0};
 * After gameassets_init(), substituting a REAL, non-player sprite variable:
)CG";
        for (int i = 0; i < m_splinePaths.size(); ++i) {
            if (m_splinePaths.at(i).points.size() < 2) continue;
            const QString sym = splineSymbol(i);
            out << " *     start_spline(&custom_motion, &YOUR_SPRITE, " << sym
                << "_path, " << sym << "_count, " << sym << "_frames, "
                << sym << "_loop);\n"
                << " *     set_spline_pos(&custom_motion, 100, 100); // optional world start\n";
            break;
        }
        out << R"CG( * Once per frame, before rendering:
 *     run_spline(&custom_motion, 1);
 * Immediately BEFORE drawing this sprite, after camera_x/y are calculated:
 *     offset_spline(&custom_motion, -camera_x, -camera_y);
 *     gfx_drawbob(&YOUR_SPRITE);
 * Do not also draw YOUR_SPRITE through gameassets_draw_foreground().
 */
)CG";
    }
    out << R"CG(
int main(int argc, char *argv[])
{
    int result = 0;
    (void)argc;
    (void)argv;

    /* 1. Set up SIDBOX hardware and memory BEFORE loading resources. */
    configure_runmode(GAMEMODE_PROFILE_0);
    suspend_desktop();
    initMalloc();
)CG";
    if (hasMusic || hasAudio)
        out << "    set_audio_dma(512);\n    set_music_dma = 1;\n";
    out << "    gfx_setlcd(DEFAULT_RENDER_ORDER, FPS_50);\n"
           "    gfx_mode(VIEW_W, VIEW_H, VIEW_W, VIEW_H, "
        << (dualPlane ? "DISPFLAG_DUALLAYER" : "DISPFLAG_SINGLELAYER")
        << " | DISPFLAG_SCROLLABLE);\n\n";
    out << R"CG(    /* 2. Load the generated sprites, backgrounds, palettes and audio. */
    if (!gameassets_init()) { result = 1; goto cleanup; }
)CG";
    if (hasMap && m_tilemapExternal) {
        out << R"CG(    /* External tile/collision/animation map. Copy this .map to the SD card.
       Objects are still compiled from the .sbgm game design. */
    if (!game_level1_load_map("gamelevels/level1.map")) {
        result = 6;
        goto cleanup;
    }
)CG";
    }
    if (hasMap) {
        out << R"CG(    /* Atlas PPB: dedicated Tile Atlases resource (shared with gameassets),
       legacy sprite-based atlas, or direct SD fallback. Never drawn as a sprite. */
    if (!game_level1_load_atlas()) { result = 5; goto cleanup; }
    game_tilemap_animation_reset();
)CG";
    }
    if (hasObjects) {
        out << R"CG(    /* Configured objects, animations, switches, doors and sounds.
       ALSO calls start_spline() for each configured moving object. */
    if (!gameworlditems_init()) { result = 2; goto cleanup; }
)CG";
    }
    out << R"CG(
    front[0] = gfx_getfbuffer1();
    front[1] = gfx_getfbuffer2();
    if (!front[0] || !front[1] || front[0] == front[1]
        || !front[0]->bitmap || !front[1]->bitmap
        || front[0]->bitmap == front[1]->bitmap) {
        result = 3;
        goto cleanup;
    }
    /* Show a direct background PPB (if configured in Game Designer). */
    gameassets_show_background();
)CG";
    if (dualPlane && hasBackgroundSprites) {
        out << R"CG(    /* Background BOB resources are drawn once to the background plane.
       Direct backgrounds are instead displayed by show_background above. */
    gfx_bitmap_t *back = gfx_getbbuffer1();
    if (!back || !back->bitmap) { result = 7; goto cleanup; }
    gfx_usebuffer(back);
    gameassets_draw_background();
    gfx_showbbuffer(back);
)CG";
    }
    out << "    gfx_scrollb(0, 0);\n    gfx_scrollf(0, 0);\n";
    if (hasPhysics) {
        out << "\n    /* The sprite named 'player' becomes the physics-controlled character. */\n"
               "    if (!game_tile_player_start(&player_physics, &game_level1, &"
            << playerName << ")) { result = 4; goto cleanup; }\n";
        if (hasHazards)
            out << "    game_death_set_callback(on_player_death, NULL);\n";
        if (hasCustomZones)
            out << "    game_tile_set_zone_callback(on_custom_zone, &player_physics);\n";
        if (worldObjects) {
            out << R"CG(
    /* Do not copy world coordinates: bind addresses of live physics fields. */
    world_player.x100 = &player_physics.x100;
    world_player.y100 = &player_physics.y100;
    world_player.vy100 = &player_physics.vy100;
    world_player.on_ground = &player_physics.on_ground;
    world_player.jump_held = &player_physics.jump_held;
    world_player.coyote = &player_physics.coyote;
    world_player.jump_speed = &player_physics.jump_speed;
)CG";
            out << "    world_player.width = " << playerName << ".width;\n"
                << "    world_player.height = " << playerName << ".height;\n";
        }
    }
    if (hasMusic) out << R"CG(
    /* To start a tune on launch, call playmusicNAME() from gameassets.h.
       Music triggers configured on objects work automatically. */
)CG";
    out << R"CG(
    /* 3. The frame loop. Leave the helper calls in this order. */
    while (1) {
        gfx_lcdwait();
)CG";
    if (hasObjects) {
        if (!attachedSplineDescriptions.isEmpty())
            out << "        /* This ALSO advances every attached spline exactly once. */\n";
        out << "        gameworlditems_update(1);\n";
    }
    if (hasPhysics) {
        if (worldObjects) out << "        gameworlditems_before(&world_player);\n";
        out << "        /* OPTIONAL THRUSTERS: replace the next line with the in_space\n"
               "         * example above, and still step physics every frame. */\n";
        out << "        game_tile_player_run(&player_physics, getjoyport(), 1);\n";
        if (worldObjects) out << "        gameworlditems_after(&world_player);\n";
        if (pickups) {
            out << "        gameworlditems_check(player_physics.x100 / 100,\n"
                   "            player_physics.y100 / 100, " << playerName << ".width,\n"
                << "            " << playerName << ".height, on_pickup, &score);\n";
        }
    }
    out << "\n        int32_t camera_x = 0, camera_y = 0;\n";
    if (hasPhysics) {
        out << R"CG(        /* Follow the player in WORLD pixels, clamped to the level bounds. */
        camera_x = player_physics.x100 / 100 - VIEW_W / 2;
        camera_y = player_physics.y100 / 100 - VIEW_H / 2;
        int32_t max_x = (int32_t)game_level1.width * game_level1.tile_size - VIEW_W;
        int32_t max_y = (int32_t)game_level1.height * game_level1.tile_size - VIEW_H;
        if (max_x < 0) max_x = 0;
        if (max_y < 0) max_y = 0;
        if (camera_x < 0) camera_x = 0;
        if (camera_y < 0) camera_y = 0;
        if (camera_x > max_x) camera_x = max_x;
        if (camera_y > max_y) camera_y = max_y;
)CG";
    }
    if (!hasMap && !hasObjects) out << "        (void)camera_x; (void)camera_y;\n";
    if (hasMap) out << "        game_tilemap_animation_tick(1);\n";
    out << R"CG(
        /* Draw into the hidden buffer, then display and swap. */
        gfx_usebuffer(front[draw_index]);
        gfx_setcolour(0);
        gfx_rectf(0, 0, VIEW_W, VIEW_H);
)CG";
    if (!dualPlane && hasBackgroundSprites)
        out << "        gameassets_draw_background(); /* Single-plane background */\n";
    if (hasMap) {
        // gfx_rectf() cleared the entire foreground just above, so the
        // tile renderer need not clear every 8x8 tile a second time.
        out << "        game_tilemap_blit_view_cleared(&game_level1, camera_x, camera_y, VIEW_W, VIEW_H);\n";
    }
    if (hasObjects)
        out << "        gameworlditems_draw(camera_x, camera_y);\n";
    if (hasPhysics) {
        // Draw ordinary scenery with their real WORLD coordinates. Never draw
        // the player or a managed game object twice.
        for (const Resource &r : m_resources) {
            if (r.kind != QStringLiteral("sprite") || r.path.isEmpty() ||
                r.objectType != QStringLiteral("decoration") || &r == player ||
                r.plane == QStringLiteral("background")) continue;
            const QString bob = spriteSymbol(r);
            out << "        " << bob << ".drawx = " << r.x << " - camera_x;\n"
                << "        " << bob << ".drawy = " << r.y << " - camera_y;\n"
                << "        gfx_drawbob(&" << bob << ");\n";
        }
        out << "        game_tile_player_screen(&player_physics, camera_x, camera_y);\n"
            << "        gfx_drawbob(&" << playerName << ");\n";
    } else {
        // With no tile/player combination, normal static BOB resources still
        // render and any configured world objects remain independently drawn.
        out << "        gameassets_draw_foreground();\n";
    }
    if (hasMap && std::any_of(m_tilemap.flips.cbegin(), m_tilemap.flips.cend(),
            [](char flags) { return (quint8(flags) & 4u) != 0; })) {
        out << "        /* Foreground tiles are deliberately drawn AFTER the player. */\n"
               "        game_tilemap_blit_view_front(&game_level1, camera_x, camera_y, VIEW_W, VIEW_H);\n";
    }
    out << R"CG(
        /* YOUR GAME LOGIC: scoring UI, effects and custom HUD go here.
           To exit, add your input check with break; cleanup is below. */
        gfx_dispfbuffer(front[draw_index], front[draw_index ^ 1u]);
        gfx_displaynow();
        draw_index ^= 1u;
        music_update();  /* Keep SIDBOX music/audio processing alive. */
    }

cleanup:
    /* Stop audio before freeing samples. Unload atlas before gameassets,
       because its pixels may be borrowed from a sprite PPB allocation. */
    music_stop();
)CG";
    if (hasMap)
        out << "    game_level1_unload_atlas();\n    game_level1_unload_map();\n";
    out << R"CG(    gameassets_shutdown();
    restore_desktop();
    return result;
}
)CG";
    const QString path = QDir(QFileInfo(m_filePath).absolutePath())
                             .filePath(QStringLiteral("maingame.c.txt"));
    QSaveFile file(path);
    const QByteArray data = program.toUtf8();
    if (!file.open(QIODevice::WriteOnly) || file.write(data) != data.size() || !file.commit()) {
        file.cancelWriting();
        if (error) *error = tr("Cannot generate %1").arg(path);
        return false;
    }
    return true;
}

// Stage 3.52: regenerate main.c only while it is verifiably IDE-owned.
// maingame.c.txt is always generated; existing unregistered source is sacred.
bool SidboxGameDesigner::syncManagedMain(QString *error)
{
    const QString root = QFileInfo(m_filePath).absolutePath();
    const QString mainFile = GamerGirlMainOwnership::mainPath(root);
    if (mainSourceHasUnsavedEdits && mainSourceHasUnsavedEdits(mainFile)) {
        // An unsaved buffer must NEVER be overwritten. Leave the file and
        // record untouched; a subsequent Save transfers ownership to user.
        return true;
    }
    QFile example(QDir(root).filePath(QStringLiteral("maingame.c.txt")));
    if (!example.open(QIODevice::ReadOnly)) {
        if (error) *error = tr("Cannot read generated maingame.c.txt");
        return false;
    }
    const QByteArray starter = example.readAll();
    if (starter.isEmpty()) {
        if (error) *error = tr("Generated maingame.c.txt is empty");
        return false;
    }
    bool changed = false;
    if (!GamerGirlMainOwnership::installGenerated(root, starter, &changed, error)) return false;
    if (changed && assetFilesChanged) assetFilesChanged();
    return true;
}

void SidboxGameDesigner::updateGameProject()
{
    // This command deliberately operates on the currently opened .sbgm only.
    // An explicit confirmation and a timestamped backup precede every write.
    if (m_filePath.isEmpty() || !m_valid) return;
    const QDir project(QFileInfo(m_filePath).absolutePath());
    const QDir templates(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
    if (!templates.exists()) {
        QMessageBox::warning(this, tr("Update Game Project"),
            tr("Could not find the bundled game helper templates."));
        return;
    }

    // Refresh installed helpers and add dependencies needed by this design.
    // No unrelated helper is added, and .txt guides are never replaced.
    QSet<QString> needed;
    if (m_tilemapEnabled) needed.insert(QStringLiteral("tilemap"));
    bool hasSpline = false;
    for (const SplinePath &path : m_splinePaths)
        if (path.points.size() >= 2) hasSpline = true;
    if (hasSpline) needed.insert(QStringLiteral("spline"));
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")) continue;
        needed.insert(r.objectType == QStringLiteral("collectable")
                          ? QStringLiteral("collectables") : QStringLiteral("worldobjects"));
        needed.insert(QStringLiteral("animation"));
        needed.insert(QStringLiteral("spline"));
    }
    const QDir installed(project.filePath(QStringLiteral("gamehelpers")));
    const QStringList known = templates.entryList({QStringLiteral("*.c")}, QDir::Files, QDir::Name);
    for (const QString &name : known) {
        const QString base = QFileInfo(name).completeBaseName();
        if (QFileInfo::exists(installed.filePath(QStringLiteral("game") + base + QStringLiteral(".c")))
            || QFileInfo::exists(installed.filePath(QStringLiteral("game") + base + QStringLiteral(".h"))))
            needed.insert(base);
    }
    // Make sure the required templates are all present before touching disk.
    QStringList helperNames;
    for (const QString &base : needed) helperNames << base;
    helperNames.sort();
    for (const QString &base : helperNames) {
        for (const QString &ext : {QStringLiteral(".c"), QStringLiteral(".h")}) {
            if (!QFileInfo::exists(templates.filePath(base + ext))) {
                QMessageBox::warning(this, tr("Update Game Project"),
                    tr("Missing SDK helper template: %1").arg(templates.filePath(base + ext)));
                return;
            }
        }
    }

    // This is also the explicit write-set for the backup. New files won't
    // exist in the snapshot; user-owned main.c is backed up, never replaced.
    QSet<QString> outputs;
    outputs.insert(QFileInfo(m_filePath).absoluteFilePath());
    outputs.insert(QStringLiteral("gameassets/gameassets.c"));
    outputs.insert(QStringLiteral("gameassets/gameassets.h"));
    outputs.insert(QStringLiteral("gamehelpers/gameworlditems.c"));
    outputs.insert(QStringLiteral("gamehelpers/gameworlditems.h"));
    outputs.insert(QStringLiteral("gamehelpers/gameworlditems.txt"));
    outputs.insert(QStringLiteral("maingame.c.txt"));
    // Main generation may create a missing file or transfer a dirty external
    // file. Back up/track BOTH source and metadata for full rollback. User
    // files are still excluded from actual regeneration by the CRC gate.
    outputs.insert(QStringLiteral("main.c"));
    outputs.insert(QStringLiteral(".codergirl/main-ownership.json"));

    if (hasSpline
        || QFileInfo::exists(installed.filePath(QStringLiteral("splinepaths.h")))) {
        // saveDesign also refreshes previously exported paths even if the
        // last spline was just deleted, so their originals need backing up.
        outputs.insert(QStringLiteral("gamehelpers/splinepaths.c"));
        outputs.insert(QStringLiteral("gamehelpers/splinepaths.h"));
    }
    if (m_tilemapEnabled) {
        outputs.insert(QStringLiteral("gamelevels/level1.c"));
        outputs.insert(QStringLiteral("gamelevels/level1.h"));
        if (m_tilemapExternal) outputs.insert(QStringLiteral("gamelevels/level1.map"));
    }
    for (const QString &base : helperNames) {
        const QString targetBase = QStringLiteral("gamehelpers/game") + base;
        outputs.insert(targetBase + QStringLiteral(".c"));
        outputs.insert(targetBase + QStringLiteral(".h"));
        // Only missing beginner guides get installed; existing ones stay intact.
        if (!QFileInfo::exists(project.filePath(targetBase + QStringLiteral(".txt")))
            && QFileInfo::exists(templates.filePath(base + QStringLiteral(".txt"))))
            outputs.insert(targetBase + QStringLiteral(".txt"));
    }
    QStringList paths;
    for (const QString &path : outputs) paths << path;
    paths.sort();
    QStringList replacing, adding;
    for (const QString &p : paths) {
        if (QFileInfo::exists(QDir::isAbsolutePath(p) ? p : project.filePath(p))) replacing << p;
        else adding << p;
    }

    QMessageBox confirm(this);
    confirm.setIcon(QMessageBox::Warning);
    confirm.setStyleSheet(QStringLiteral("QMessageBox, QPushButton, QCheckBox, QTextEdit { border-radius: 0px; }"));
    confirm.setWindowTitle(tr("Update Game Project — Confirm"));
    confirm.setText(tr("Back up and update the current game project?"));
    confirm.setInformativeText(tr(
        "CoderGirl will refresh existing game helper C/H files from the SDK, "
        "export the current spline paths and tilemap (if present), then regenerate "
        "gameassets, gameworlditems and a complete, copyable maingame.c.txt.\n\n"
        "Any edits in replaced helpers or generated files will be overwritten. "
        "A ZIP backup is made FIRST.\n\n"
        "Only a verified, unchanged IDE-owned main.c may be regenerated. "
        "Hand-edited, unknown and user-owned main.c files remain protected. "
        "maingame.c.txt is always updated.\n\n"
        "Only the newest 20 Update Project ZIP backups are retained "
        "(older ZIPs are deleted after a successful update). "
        "Earlier folder-style backups are preserved.\n\n"
        "Replace %1 existing files; create up to %2 missing files.")
        .arg(replacing.size()).arg(adding.size()));
    confirm.setDetailedText(tr("FILES TO REPLACE:\n%1\n\nFILES TO CREATE:\n%2")
        .arg(replacing.isEmpty() ? tr("(none)") : replacing.join(QStringLiteral("\n")),
             adding.isEmpty() ? tr("(none)") : adding.join(QStringLiteral("\n"))));
    auto *embed = new QCheckBox(tr("Embed sprite and selected tile-atlas PPBs in generated C (normally load from SD card)"), &confirm);
    embed->setChecked(false);
    confirm.setCheckBox(embed);
    auto *proceed = confirm.addButton(tr("Back Up and Update"), QMessageBox::AcceptRole);
    confirm.addButton(QMessageBox::Cancel);
    confirm.setDefaultButton(qobject_cast<QPushButton *>(confirm.button(QMessageBox::Cancel)));
    confirm.exec();
    if (confirm.clickedButton() != proceed) return;

    const QString stamp = QDateTime::currentDateTime().toString(QStringLiteral("yyyyMMdd-HHmmss-zzz"));
    const QDir backupRoot(project.filePath(QStringLiteral(".codergirl-backups/updates")));
    const QString backupFolder = backupRoot.filePath(QStringLiteral(".staging-") + stamp);
    const QString archivePath = backupRoot.filePath(stamp + QStringLiteral(".zip"));
    QDir backup(backupFolder);
    if (!QDir().mkpath(backupFolder)) {
        QMessageBox::warning(this, tr("Update Game Project"), tr("Cannot create backup folder:\n%1").arg(backupFolder));
        return;
    }
    for (const QString &relative : replacing) {
        const QString src = QDir::isAbsolutePath(relative) ? relative : project.filePath(relative);
        // .sbgm is inside the project in normal use. Restrict backup targets
        // to project files, never copy a path outside the project tree.
        const QString safeName = project.relativeFilePath(src);
        if (safeName == QStringLiteral("..") || safeName.startsWith(QStringLiteral("../"))
            || QDir::isAbsolutePath(safeName)) {
            QMessageBox::warning(this, tr("Update Game Project"),
                tr("Unsafe backup path: %1").arg(src));
            return;
        }
        const QString dest = backup.filePath(safeName);
        if (!QDir().mkpath(QFileInfo(dest).absolutePath()) || !QFile::copy(src, dest)) {
            QMessageBox::warning(this, tr("Update Game Project"),
                tr("Backup failed; project update was NOT started.\n%1").arg(src));
            return;
        }
    }

    // Archive is complete before any generated or helper file is modified.
    // Keep the staging copies until the update finishes for safe rollback.
    QString zipError;
    if (!gameBackupWriteZip(backupFolder, archivePath, &zipError)) {
        QMessageBox::warning(this, tr("Update Game Project"),
            tr("Could not create the ZIP backup; project update was NOT started.\n%1")
                .arg(zipError));
        return;
    }

    // Only the template-backed helper C/H files are deliberately replaced.
    // Their paired .txt guides are installed when missing, never overwritten.
    QString error;
    for (const QString &base : helperNames) {
        const QString installedBase = QStringLiteral("game") + base;
        for (const QString &ext : {QStringLiteral(".h"), QStringLiteral(".c"), QStringLiteral(".txt")}) {
            const QString output = installed.filePath(installedBase + ext);
            if (ext == QStringLiteral(".txt") && QFileInfo::exists(output)) continue;
            QFile source(templates.filePath(base + ext));
            if (ext == QStringLiteral(".txt") && !source.exists()) continue;
            if (!source.open(QIODevice::ReadOnly)) {
                error = tr("Cannot read template: %1").arg(source.fileName()); break;
            }
            QByteArray bytes = source.readAll();
            if (ext == QStringLiteral(".c")) {
                bytes.replace(QStringLiteral("\"%1.h\"").arg(base).toUtf8(),
                              QStringLiteral("\"%1.h\"").arg(installedBase).toUtf8());
            }
            if (!QDir().mkpath(QFileInfo(output).absolutePath())) {
                error = tr("Cannot create folder for: %1").arg(output); break;
            }
            QSaveFile file(output);
            if (!file.open(QIODevice::WriteOnly)
                || file.write(bytes) != bytes.size() || !file.commit()) {
                file.cancelWriting();
                error = tr("Cannot install helper: %1").arg(output); break;
            }
        }
        if (!error.isEmpty()) break;
    }
    // saveDesign auto-updates previously exported paths/level; explicitly
    // export again to cover first-time exports as well.
    if (error.isEmpty() && !saveDesign()) error = tr("Saving the design failed.");
    if (error.isEmpty() && hasSpline && !exportSplinePaths(false))
        error = tr("Spline export failed.");
    if (error.isEmpty() && m_tilemapEnabled && !exportTilemap(false, true))
        error = tr("Tilemap export failed.");
    if (error.isEmpty() && !generateGameCodeCore(embed->isChecked(), true))
        error = tr("V1 game code generation failed.");
    if (!error.isEmpty()) {
        // Restore known outputs, using atomic replacement. The originals
        // remain in the backup folder even if rollback itself fails.
        QStringList restoreFailures;
        for (const QString &relative : replacing) {
            const QString destination = QDir::isAbsolutePath(relative)
                ? relative : project.filePath(relative);
            const QString from = backup.filePath(project.relativeFilePath(destination));
            QFile original(from);
            if (!original.open(QIODevice::ReadOnly)) {
                restoreFailures << destination;
                continue;
            }
            QSaveFile restored(destination);
            const QByteArray bytes = original.readAll();
            if (!restored.open(QIODevice::WriteOnly)
                || restored.write(bytes) != bytes.size() || !restored.commit()) {
                restored.cancelWriting();
                restoreFailures << destination;
            }
        }
        for (const QString &relative : adding) {
            const QString created = QDir::isAbsolutePath(relative)
                ? relative : project.filePath(relative);
            if (QFileInfo::exists(created) && !QFile::remove(created))
                restoreFailures << created;
        }
        setDirty(true); // The in-memory design may differ from restored .sbgm.
        const QString recovery = restoreFailures.isEmpty()
            ? tr("Files were restored to their pre-update state.")
            : tr("Automatic recovery could not restore these files:\n%1\n"
                 "Recover them manually from the ZIP backup (or staging folder).")
                  .arg(restoreFailures.join(QStringLiteral("\n")));
        QMessageBox::critical(this, tr("Update Game Project — Incomplete"),
            tr("The update stopped: %1\n\n%2\n\nZIP backup:\n%3")
               .arg(error, recovery, archivePath));
        if (restoreFailures.isEmpty()) QDir(backupFolder).removeRecursively();
        if (assetFilesChanged) assetFilesChanged();
        return;
    }
    // Only now is it safe to delete the temporary rollback copies, and trim
    // old ZIP archives after a fully successful project update.
    QDir(backupFolder).removeRecursively();
    gameBackupTrimArchives(backupRoot);
    if (assetFilesChanged) assetFilesChanged();
    QMessageBox::information(this, tr("Game Project Updated"),
        tr("Game helper files refreshed, splines/tilemap exported, and V1 game code regenerated.\n\n"
           "main.c is updated only while still IDE-owned. User-owned source and existing beginner guides are untouched.\n\n"
           "ZIP backup: %1\nOnly the newest 20 update ZIP backups are kept.")
               .arg(archivePath));
}

void SidboxGameDesigner::generateGameCode()
{
    if (m_filePath.isEmpty() || !saveDesign()) return;

    const QMessageBox::StandardButton choice = QMessageBox::question(
        this, tr("Generate V1 Game Code"),
        tr("How should CoderGirl store graphics?\n\n"
           "Audio and music remain disk resources in this first version.\n\n"
           "Yes = Load graphics from disk (PPB)\n"
           "No = Embed graphics in gameassets.c\n"
           "Cancel = Do not generate code"),
        QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel,
        QMessageBox::Yes);
    if (choice == QMessageBox::Cancel) return;

    const QString output = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gameassets"));
    const QString cPath = QDir(output).filePath(QStringLiteral("gameassets.c"));
    const QString hPath = QDir(output).filePath(QStringLiteral("gameassets.h"));
    if (QFileInfo::exists(cPath) || QFileInfo::exists(hPath)) {
        if (QMessageBox::warning(this, tr("Regenerate V1 Game Code"),
            tr("The generated gameassets.c/.h files already exist.\n\n"
               "Regenerating replaces these files. A verified IDE-owned main.c may "
               "also be refreshed; user-owned main.c is never replaced.\n\n"
               "Continue?"), QMessageBox::Yes | QMessageBox::Cancel,
            QMessageBox::Cancel) != QMessageBox::Yes) return;
    }

    generateGameCodeCore(choice == QMessageBox::No, false);
}

bool SidboxGameDesigner::generateGameCodeCore(bool embedPixels, bool batchMode)
{
    bool anyWorldObject = false;
    bool anySpline = false;
    for (const SplinePath &path : m_splinePaths)
        if (path.points.size() >= 2) anySpline = true;
    for (const Resource &r : m_resources) {
        if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")) continue;
        anyWorldObject = true;
    }
    QString integrationError;
    if ((anyWorldObject || anySpline) && !installMissingWorldHelpers(&integrationError, !batchMode)) {
        QMessageBox::warning(this, tr("Game Object Dependencies"), integrationError);
        return false;
    }
    if (anySpline && !exportSplinePaths(false)) return false;

    SidboxGameCodeGen::Request request;
    request.designDirectory = QFileInfo(m_filePath).absolutePath();
    request.outputDirectory = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gameassets"));
    request.dualPlane = m_planeMode->currentData().toString() == QStringLiteral("dual");
    request.embedPixels = embedPixels;
    const QString activeAtlasPath = m_tilemapEnabled && !m_tilemap.atlasPath.isEmpty()
        ? QDir::cleanPath(resolvedPath(m_tilemap.atlasPath)) : QString();
    for (const Resource &r : m_resources) {
        // Tile Atlases are a library of possible sheets. Only the selected
        // tilemap atlas is loaded, avoiding unused SDRAM allocations.
        if (r.kind == QStringLiteral("tileatlas") &&
            (activeAtlasPath.isEmpty() || r.path.isEmpty() ||
             QDir::cleanPath(resolvedPath(r.path)) != activeAtlasPath)) continue;
        SidboxGameCodeGen::Asset a;
        a.name = r.name; a.kind = r.kind; a.plane = r.plane;
        a.worldManaged = r.kind == QStringLiteral("sprite") &&
                         r.objectType != QStringLiteral("decoration");
        a.backgroundMode = r.backgroundMode;
        if (!r.path.isEmpty()) a.absolutePath = resolvedPath(r.path);
        a.x = r.x; a.y = r.y; a.scale = r.scale;
        a.cellWidth = r.cellWidth; a.cellHeight = r.cellHeight; a.frame = r.frame;
        a.channel = r.audio.channel; a.frequency = r.audio.frequency;
        a.volume = r.audio.volume; a.pan = r.audio.pan;
        a.loop = r.audio.loop; a.loopStart = r.audio.loopStart;
        a.loopLength = r.audio.loopLength; a.subsong = r.audio.subsong;
        request.assets.append(a);
        if (r.kind == QStringLiteral("palette")) {
            if (r.id == m_activeForegroundPalette) request.foregroundPalette = a.absolutePath;
            if (r.id == m_activeBackgroundPalette) request.backgroundPalette = a.absolutePath;
        }
    }
    const auto result = SidboxGameCodeGen::generate(request);
    if (!result.ok) {
        QMessageBox::warning(this, tr("V1 Game Code Generation"), result.error);
        return false;
    }
    integrationError.clear();
    if (!exportWorldItems(&integrationError)) {
        QMessageBox::warning(this, tr("Game World Object Generation"),
            tr("Game assets were generated, but world objects were not: %1").arg(integrationError));
        return false;
    }
    if (!exportExampleMain(&integrationError)) {
        QMessageBox::warning(this, tr("Starter Program Generation"),
            tr("Game assets were generated, but maingame.c.txt was not: %1").arg(integrationError));
        return false;
    }
    // Write only a verified IDE-owned main.c (or create a missing one).
    // User-modified/legacy files remain protected, even with OWNER: IDE text.
    if (!syncManagedMain(&integrationError)) {
        QMessageBox::warning(this, tr("Protect main.c"),
            tr("Game resources were generated, but main.c ownership processing failed:\n%1")
                .arg(integrationError));
        return false;
    }
    if (assetFilesChanged) assetFilesChanged();
    QString message = tr("Generated gameassets/gameassets.c and gameassets.h.\n\n"
                         "Include \"gameassets/gameassets.h\" from main.c.\n"
                         "Call gameassets_init() after initMalloc() and gfx_mode().\n"
                         "Use maingame.c.txt for the correct draw/update order.\n\n"
                         "The generated code owns NO display buffers or game logic. "
                         "In dual-plane mode, background sprite drawing is separate. "
                         "For a direct background buffer, call gameassets_show_background() "
                         "after gameassets_init().");
    if (anyWorldObject)
        message += tr("\n\nGenerated gamehelpers/gameworlditems.c/.h/.txt for your configured game objects.");
    message += tr("\n\nUpdated maingame.c.txt. main.c is regenerated only if "
                  "it is IDE-owned and has not been manually edited.");
    if (result.embeddedBytes)
        message += tr("\n\nEmbedded graphics: %1 KiB (uncompressed).")
            .arg((result.embeddedBytes + 1023) / 1024);
    if (!result.warnings.isEmpty())
        message += QStringLiteral("\n\n") + tr("Warnings:")
            + QStringLiteral("\n• ") + result.warnings.join(QStringLiteral("\n• "));
    if (!batchMode) {
        QMessageBox::information(this, tr("V1 Game Code Generated"), message);
    }
    return true;
}

bool SidboxGameDesigner::loadDesign()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Game Designer"), tr("Cannot open %1").arg(m_filePath));
        return false;
    }
    QJsonParseError error;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    const QJsonObject obj = doc.object();
    if (error.error != QJsonParseError::NoError || !doc.isObject()
        || obj.value(QStringLiteral("format")).toString() != QStringLiteral("SIDBOX-GAME-DESIGN")
        || obj.value(QStringLiteral("version")).toInt() != 1) {
        QMessageBox::warning(this, tr("Game Designer"), tr("Unsupported or invalid .sbgm design: %1").arg(m_filePath));
        return false;
    }
    m_loading = true;
    m_worldWidth->setValue(qBound(LCD_WIDTH, obj.value(QStringLiteral("worldWidth")).toInt(960), MAX_WORLD));
    m_worldHeight->setValue(qBound(LCD_HEIGHT, obj.value(QStringLiteral("worldHeight")).toInt(640), MAX_WORLD));
    m_cameraX->setValue(qBound(0, obj.value(QStringLiteral("cameraX")).toInt(),
                               m_worldWidth->value() - LCD_WIDTH));
    m_cameraY->setValue(qBound(0, obj.value(QStringLiteral("cameraY")).toInt(),
                               m_worldHeight->value() - LCD_HEIGHT));
    { QSignalBlocker b1(m_snap), b2(m_snapStep), b3(m_zoom);
      m_snap->setChecked(obj.value(QStringLiteral("snapEnabled")).toBool(true));
      const int step = obj.value(QStringLiteral("snapStep")).toInt(4);
      m_snapStep->setCurrentText(QStringLiteral("%1 px").arg(
          QStringList{QStringLiteral("4"),QStringLiteral("8"),QStringLiteral("16"),
                      QStringLiteral("32"),QStringLiteral("64")}.contains(QString::number(step)) ? step : 32));
      const int zoom = obj.value(QStringLiteral("zoomPercent")).toInt(100);
      m_zoom->setCurrentText(QStringLiteral("%1%").arg(
          QStringList{QStringLiteral("25"), QStringLiteral("50"), QStringLiteral("75"),
                      QStringLiteral("100"), QStringLiteral("200")}.contains(QString::number(zoom)) ? zoom : 100));
      m_view->resetTransform(); m_view->scale(zoom > 0 ? qBound(25, zoom, 200) / 100.0 : 1.,
                                             zoom > 0 ? qBound(25, zoom, 200) / 100.0 : 1.);
    }
    {
        QSignalBlocker b1(m_planeMode), b2(m_showLabels), b3(m_forcePalette), b4(m_showTilemap);
        m_showTilemap->setChecked(obj.value(QStringLiteral("showTilemapOverlay")).toBool(false));
        m_planeMode->setCurrentIndex(obj.value(QStringLiteral("planeMode")).toString() == QStringLiteral("dual") ? 1 : 0);
        m_showLabels->setChecked(obj.value(QStringLiteral("showAssetLabels")).toBool(true));
        m_forcePalette->setChecked(obj.value(QStringLiteral("forcePalette")).toBool(false));
        m_activeForegroundPalette = obj.value(QStringLiteral("activeForegroundPalette")).toString();
        m_activeBackgroundPalette = obj.value(QStringLiteral("activeBackgroundPalette")).toString();
    }
    m_backPalette->setEnabled(m_planeMode->currentIndex() == 1);
    m_resources.clear();
    const QJsonArray assets = obj.value(QStringLiteral("resources")).toArray();
    for (const QJsonValue &value : assets) {
        if (!value.isObject()) continue;
        const QJsonObject a = value.toObject();
        Resource r;
        r.kind = a.value(QStringLiteral("kind")).toString();
        if (!QStringList{QStringLiteral("sprite"), QStringLiteral("tileatlas"),
                         QStringLiteral("background"), QStringLiteral("palette"),
                         QStringLiteral("sound"), QStringLiteral("music")}.contains(r.kind))
            continue;
        r.name = a.value(QStringLiteral("name")).toString();
        r.id = a.value(QStringLiteral("id")).toString();
        if (r.id.isEmpty()) r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        r.plane = a.value(QStringLiteral("plane")).toString(
            r.kind == QStringLiteral("background") ? QStringLiteral("background") : QStringLiteral("foreground"));
        if (r.plane != QStringLiteral("background")) r.plane = QStringLiteral("foreground");
        r.path = a.value(QStringLiteral("path")).toString();
        r.x = qBound(-MAX_WORLD, a.value(QStringLiteral("x")).toInt(), MAX_WORLD);
        r.y = qBound(-MAX_WORLD, a.value(QStringLiteral("y")).toInt(), MAX_WORLD);
        r.scale = qBound(1, a.value(QStringLiteral("scale")).toInt(100), 800);
        r.cellWidth = qBound(0, a.value(QStringLiteral("cellWidth")).toInt(0), 16384);
        r.cellHeight = qBound(0, a.value(QStringLiteral("cellHeight")).toInt(0), 16384);
        r.frame = qBound(0, a.value(QStringLiteral("frame")).toInt(0), 65535);
        r.locked = a.value(QStringLiteral("locked")).toBool(false);
        const QJsonObject object = a.value(QStringLiteral("gameObject")).toObject();
        const QString type = object.value(QStringLiteral("type")).toString(QStringLiteral("decoration"));
        if (QStringList{QStringLiteral("collectable"), QStringLiteral("lift"),
                QStringLiteral("conveyor"), QStringLiteral("spring"),
                QStringLiteral("trigger"), QStringLiteral("door"),
                QStringLiteral("deathzone")}.contains(type)
            && r.kind == QStringLiteral("sprite")) r.objectType = type;
        r.pickupKind = qBound(1, object.value(QStringLiteral("pickupKind")).toInt(1), 4);
        r.objectValue = qBound(0, object.value(QStringLiteral("value")).toInt(10), 65535);
        r.hitWidth = qBound(1, object.value(QStringLiteral("hitWidth")).toInt(16), 1024);
        r.hitHeight = qBound(1, object.value(QStringLiteral("hitHeight")).toInt(16), 1024);
        r.conveyorSpeed = qBound(-100, object.value(QStringLiteral("conveyorSpeed")).toInt(2), 100);
        r.springStrength = qBound(1, object.value(QStringLiteral("springStrength")).toInt(11), 100);
        r.springLaunchX = qBound(-40, object.value(QStringLiteral("springLaunchX")).toInt(0), 40);
        // Safe opt-in: designs predating this flag cannot silently acquire
        // extra spring+jump velocity. Explicitly saved ON remains ON.
        r.springJumpBoost = object.value(QStringLiteral("springJumpBoost")).toBool(false);
        r.springTouch = object.value(QStringLiteral("springTouch")).toBool(false);
        r.springSlide = object.value(QStringLiteral("springSlide")).toBool(false);
        r.objectInitiallyActive = object.value(QStringLiteral("initiallyActive")).toBool(true);
        r.targetObjectId = object.value(QStringLiteral("targetObjectId")).toString();
        r.targetAction = object.value(QStringLiteral("targetAction")).toString(QStringLiteral("none"));
        if (!QStringList{QStringLiteral("enable"), QStringLiteral("disable"),
                         QStringLiteral("toggle")}.contains(r.targetAction))
            r.targetAction = QStringLiteral("none");
        r.triggerPress = object.value(QStringLiteral("triggerPress")).toBool(false);
        r.triggerOneShot = object.value(QStringLiteral("triggerOneShot")).toBool(false);
        r.triggerMusicId = object.value(QStringLiteral("triggerMusicId")).toString();
        r.triggerMusicAction = object.value(QStringLiteral("triggerMusicAction")).toString(QStringLiteral("none"));
        if (!QStringList{QStringLiteral("play"), QStringLiteral("stop")}.contains(r.triggerMusicAction))
            r.triggerMusicAction = QStringLiteral("none");
        r.sfxPickup = object.value(QStringLiteral("sfxPickup")).toString();
        r.sfxRespawn = object.value(QStringLiteral("sfxRespawn")).toString();
        r.sfxStart = object.value(QStringLiteral("sfxStart")).toString();
        r.sfxMove = object.value(QStringLiteral("sfxMove")).toString();
        r.sfxStop = object.value(QStringLiteral("sfxStop")).toString();
        r.sfxReverse = object.value(QStringLiteral("sfxReverse")).toString();
        r.sfxSpring = object.value(QStringLiteral("sfxSpring")).toString();
        r.sfxAmbient = object.value(QStringLiteral("sfxAmbient")).toString();
        r.respawnFrames = qBound(0, object.value(QStringLiteral("respawnFrames")).toInt(0), 65535);
        r.audioRadius = qBound(0, object.value(QStringLiteral("audioRadius")).toInt(0), 32767);
        r.audioFadeFrames = qBound(0, object.value(QStringLiteral("audioFadeFrames")).toInt(8), 255);
        r.objectSplineId = object.value(QStringLiteral("splineId")).toString();
        r.objectAnimated = object.value(QStringLiteral("animated")).toBool(false);
        r.animFirst = qBound(0, object.value(QStringLiteral("animFirst")).toInt(0), 255);
        r.animCount = qBound(1, object.value(QStringLiteral("animCount")).toInt(1), 256);
        r.animTicks = qBound(1, object.value(QStringLiteral("animTicks")).toInt(5), 65535);
        r.animMode = object.value(QStringLiteral("animMode")).toString(QStringLiteral("loop"));
        if (!QStringList{QStringLiteral("loop"), QStringLiteral("once"),
                QStringLiteral("pingpong")}.contains(r.animMode)) r.animMode = QStringLiteral("loop");
        r.backgroundMode = a.value(QStringLiteral("backgroundMode")).toString(QStringLiteral("sprite"));
        if (r.kind != QStringLiteral("background") ||
            !QStringList{QStringLiteral("sprite"), QStringLiteral("direct_ready"),
                         QStringLiteral("direct_convert")}.contains(r.backgroundMode))
            r.backgroundMode = QStringLiteral("sprite");
        // Optional Stage 54 fields: old Stage 52/53 documents load unchanged.
        const QJsonObject audio = a.value(QStringLiteral("audio")).toObject();
        r.audio.channel = qBound(0, audio.value(QStringLiteral("channel")).toInt(0), 7);
        r.audio.frequency = qBound(0, audio.value(QStringLiteral("frequency")).toInt(22050), 65535);
        r.audio.volume = qBound(0, audio.value(QStringLiteral("volume")).toInt(255), 1024);
        r.audio.pan = qBound(-127, audio.value(QStringLiteral("pan")).toInt(0), 127);
        r.audio.loop = audio.value(QStringLiteral("loop")).toBool(false);
        r.audio.loopStart = qBound(0, audio.value(QStringLiteral("loopStart")).toInt(0), 2147483647);
        r.audio.loopLength = qBound(0, audio.value(QStringLiteral("loopLength")).toInt(0), 2147483647);
        r.audio.subsong = qBound(0, audio.value(QStringLiteral("subsong")).toInt(0), 255);
        m_resources.append(r);
        if (m_resources.size() >= 8192) break; // corrupt/hostile data guard
    }
    // Older .sbgm documents may have backgrounds but no separate Background
    // palette category yet. Seed it from the first valid background PPB only;
    // never overwrite the file or override an existing bank choice.
    const int originalResourceCount = m_resources.size();
    if (m_activeBackgroundPalette.isEmpty()) {
        for (int i = 0; i < originalResourceCount; ++i) {
            if (m_resources.at(i).kind == QStringLiteral("background")) {
                const Resource background = m_resources.at(i);
                suggestFirstBackgroundPalette(background);
                if (m_resources.size() != originalResourceCount) break;
            }
        }
    }
    const bool seededBackgroundPalette = m_resources.size() != originalResourceCount;
    m_tilemapEnabled = false;
    m_tilemapExternal = obj.value(QStringLiteral("tilemapExternal")).toBool(false);
    m_tilemap = SidboxTilemap();
    if (obj.contains(QStringLiteral("tilemap"))) {
        if (!m_tilemap.fromJson(obj.value(QStringLiteral("tilemap")).toObject())) {
            m_loading = false;
            QMessageBox::warning(this, tr("Tilemap Editor"),
                tr("The saved tilemap data is damaged or exceeds the size limits. No tilemap changes were applied."));
            return false;
        }
        m_tilemapEnabled = true;
    }
    m_splinePaths.clear();
    for (const QJsonValue &entry : obj.value(QStringLiteral("splinePaths")).toArray()) {
        if (!entry.isObject() || m_splinePaths.size() >= 128) continue;
        const QJsonObject value = entry.toObject();
        SplinePath path;
        path.name = value.value(QStringLiteral("name")).toString(QStringLiteral("path"));
        path.id = value.value(QStringLiteral("id")).toString();
        if (path.id.isEmpty()) path.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        path.durationFrames = qBound(1, value.value(QStringLiteral("frames")).toInt(100), 65535);
        path.loop = value.value(QStringLiteral("loop")).toBool(true);
        // Keep the original [x,y] point representation so old IDE versions
        // can still read the geometry. The optional wait times live in a
        // separate "pointPauses" array; older designs default to all zero.
        const QJsonArray pauseValues = value.value(QStringLiteral("pointPauses")).toArray();
        for (const QJsonValue &pointValue : value.value(QStringLiteral("points")).toArray()) {
            if (!pointValue.isArray() || path.points.size() >= 128) continue;
            const QJsonArray coordinates = pointValue.toArray();
            if (coordinates.size() < 2) continue;
            path.points.append(QPoint(qBound(-32768, coordinates.at(0).toInt(), 32767),
                                      qBound(-32768, coordinates.at(1).toInt(), 32767)));
            const int pointNumber = path.points.size() - 1;
            const int pauseFrames = pointNumber < pauseValues.size()
                ? pauseValues.at(pointNumber).toInt() : 0;
            path.pointPauses.append(qBound(0, pauseFrames, 65535));
        }
        if (path.points.size() >= 2) m_splinePaths.append(path);
    }
    m_activeSpline = qBound(-1, obj.value(QStringLiteral("activeSpline")).toInt(-1),
                            m_splinePaths.size() - 1);
    m_loading = false;
    m_undoResources.clear();
    m_redoResources.clear();
    m_hasCopiedSprite = false;
    rebuildScene();
    refreshResources();
    refreshProperties();
    setDirty(seededBackgroundPalette); // prompt to save new reference, never silently save
    return true;
}

bool SidboxGameDesigner::saveDesign()
{
    QJsonObject obj;
    obj.insert(QStringLiteral("format"), QStringLiteral("SIDBOX-GAME-DESIGN"));
    obj.insert(QStringLiteral("version"), 1);
    obj.insert(QStringLiteral("worldWidth"), m_worldWidth->value());
    obj.insert(QStringLiteral("worldHeight"), m_worldHeight->value());
    obj.insert(QStringLiteral("cameraX"), m_cameraX->value());
    obj.insert(QStringLiteral("cameraY"), m_cameraY->value());
    obj.insert(QStringLiteral("snapEnabled"), m_snap->isChecked());
    obj.insert(QStringLiteral("snapStep"), m_snapStep->currentText().section(QLatin1Char(' '), 0, 0).toInt());
    obj.insert(QStringLiteral("zoomPercent"), m_zoom->currentText().chopped(1).toInt());
    obj.insert(QStringLiteral("showAssetLabels"), m_showLabels->isChecked());
    obj.insert(QStringLiteral("showTilemapOverlay"), m_showTilemap->isChecked());
    obj.insert(QStringLiteral("planeMode"), m_planeMode->currentData().toString());
    obj.insert(QStringLiteral("forcePalette"), m_forcePalette->isChecked());
    obj.insert(QStringLiteral("activeForegroundPalette"), m_activeForegroundPalette);
    obj.insert(QStringLiteral("activeBackgroundPalette"), m_activeBackgroundPalette);
    QJsonArray assets;
    for (const Resource &r : m_resources) {
        QJsonObject a;
        a.insert(QStringLiteral("kind"), r.kind);
        a.insert(QStringLiteral("name"), r.name);
        a.insert(QStringLiteral("id"), r.id);
        a.insert(QStringLiteral("plane"), r.plane);
        a.insert(QStringLiteral("path"), r.path);
        a.insert(QStringLiteral("x"), r.x);
        a.insert(QStringLiteral("y"), r.y);
        a.insert(QStringLiteral("scale"), r.scale);
        a.insert(QStringLiteral("cellWidth"), r.cellWidth);
        a.insert(QStringLiteral("cellHeight"), r.cellHeight);
        a.insert(QStringLiteral("frame"), r.frame);
        a.insert(QStringLiteral("locked"), r.locked);
        if (r.kind == QStringLiteral("sprite") && r.objectType != QStringLiteral("decoration")) {
            QJsonObject object;
            object.insert(QStringLiteral("type"), r.objectType);
            object.insert(QStringLiteral("pickupKind"), r.pickupKind);
            object.insert(QStringLiteral("value"), r.objectValue);
            object.insert(QStringLiteral("hitWidth"), r.hitWidth);
            object.insert(QStringLiteral("hitHeight"), r.hitHeight);
            object.insert(QStringLiteral("conveyorSpeed"), r.conveyorSpeed);
            object.insert(QStringLiteral("springStrength"), r.springStrength);
            object.insert(QStringLiteral("springLaunchX"), r.springLaunchX);
            object.insert(QStringLiteral("springJumpBoost"), r.springJumpBoost);
            object.insert(QStringLiteral("springTouch"), r.springTouch);
            object.insert(QStringLiteral("springSlide"), r.springSlide);
            object.insert(QStringLiteral("initiallyActive"), r.objectInitiallyActive);
            object.insert(QStringLiteral("targetObjectId"), r.targetObjectId);
            object.insert(QStringLiteral("targetAction"), r.targetAction);
            object.insert(QStringLiteral("triggerPress"), r.triggerPress);
            object.insert(QStringLiteral("triggerOneShot"), r.triggerOneShot);
            object.insert(QStringLiteral("triggerMusicId"), r.triggerMusicId);
            object.insert(QStringLiteral("triggerMusicAction"), r.triggerMusicAction);
            object.insert(QStringLiteral("sfxPickup"), r.sfxPickup);
            object.insert(QStringLiteral("sfxRespawn"), r.sfxRespawn);
            object.insert(QStringLiteral("sfxStart"), r.sfxStart);
            object.insert(QStringLiteral("sfxMove"), r.sfxMove);
            object.insert(QStringLiteral("sfxStop"), r.sfxStop);
            object.insert(QStringLiteral("sfxReverse"), r.sfxReverse);
            object.insert(QStringLiteral("sfxSpring"), r.sfxSpring);
            object.insert(QStringLiteral("sfxAmbient"), r.sfxAmbient);
            object.insert(QStringLiteral("respawnFrames"), r.respawnFrames);
            object.insert(QStringLiteral("audioRadius"), r.audioRadius);
            object.insert(QStringLiteral("audioFadeFrames"), r.audioFadeFrames);
            object.insert(QStringLiteral("splineId"), r.objectSplineId);
            object.insert(QStringLiteral("animated"), r.objectAnimated);
            object.insert(QStringLiteral("animFirst"), r.animFirst);
            object.insert(QStringLiteral("animCount"), r.animCount);
            object.insert(QStringLiteral("animTicks"), r.animTicks);
            object.insert(QStringLiteral("animMode"), r.animMode);
            a.insert(QStringLiteral("gameObject"), object);
        }
        if (r.kind == QStringLiteral("background"))
            a.insert(QStringLiteral("backgroundMode"), r.backgroundMode);
        if (r.kind == QStringLiteral("sound") || r.kind == QStringLiteral("music")) {
            QJsonObject audio;
            audio.insert(QStringLiteral("channel"), r.audio.channel);
            audio.insert(QStringLiteral("frequency"), r.audio.frequency);
            audio.insert(QStringLiteral("volume"), r.audio.volume);
            audio.insert(QStringLiteral("pan"), r.audio.pan);
            audio.insert(QStringLiteral("loop"), r.audio.loop);
            audio.insert(QStringLiteral("loopStart"), r.audio.loopStart);
            audio.insert(QStringLiteral("loopLength"), r.audio.loopLength);
            audio.insert(QStringLiteral("subsong"), r.audio.subsong);
            a.insert(QStringLiteral("audio"), audio);
        }
        assets.append(a);
    }
    obj.insert(QStringLiteral("resources"), assets);
    QJsonArray pathList;
    for (const SplinePath &path : m_splinePaths) {
        QJsonObject data;
        data.insert(QStringLiteral("name"), path.name);
        data.insert(QStringLiteral("id"), path.id);
        data.insert(QStringLiteral("frames"), path.durationFrames);
        data.insert(QStringLiteral("loop"), path.loop);
        QJsonArray coords;
        QJsonArray pauses;
        for (int i = 0; i < path.points.size(); ++i) {
            const QPoint &point = path.points.at(i);
            coords.append(QJsonArray{point.x(), point.y()});
            pauses.append(path.pointPauses.value(i, 0));
        }
        data.insert(QStringLiteral("points"), coords);
        data.insert(QStringLiteral("pointPauses"), pauses);
        pathList.append(data);
    }
    obj.insert(QStringLiteral("splinePaths"), pathList);
    obj.insert(QStringLiteral("activeSpline"), m_activeSpline);
    if (m_tilemapEnabled) {
        obj.insert(QStringLiteral("tilemap"), m_tilemap.toJson());
        obj.insert(QStringLiteral("tilemapExternal"), m_tilemapExternal);
    }
    QSaveFile output(m_filePath);
    const QByteArray payload = QJsonDocument(obj).toJson(QJsonDocument::Indented);
    if (!output.open(QIODevice::WriteOnly)
        || output.write(payload) != payload.size()
        || !output.commit()) {
        QMessageBox::warning(this, tr("Game Designer"), tr("Unable to save design:\n%1").arg(m_filePath));
        return false;
    }
    // Once exported, path C data tracks saved edits to any control point.
    // Nothing is created for older projects until Export is chosen.
    const QString pathHeader = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gamehelpers/splinepaths.h"));
    if (QFileInfo::exists(pathHeader) && !exportSplinePaths(false)) return false;
    const QString tileHeader = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gamelevels/level1.h"));
    if (m_tilemapEnabled && QFileInfo::exists(tileHeader) && !exportTilemap(false)) return false;
    setDirty(false);
    return true;
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
            if (m_middlePanning) {
                const QPoint delta = next - m_panLastPos;
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
                    if (m_undoResources.size() >= 64) m_undoResources.removeFirst();
                    m_undoResources.append(m_dragBefore);
                    m_redoResources.clear();
                }
                m_dragResourceIndex = -1;
                m_dragBefore.clear();
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

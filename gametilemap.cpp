#include "gametilemap.h"
#include "ppbcodec.h"

#include <QAbstractScrollArea>
#include <QAbstractItemView>
#include <QComboBox>
#include <QCheckBox>
#include <QSettings>
#include <QPalette>
#include <QPen>
#include <QDialogButtonBox>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QJsonValue>
#include <QJsonArray>
#include <QListWidget>
#include <QIcon>
#include <QLineEdit>
#include <QListView>
#include <QSignalBlocker>
#include <QTimer>
#include <QRegion>
#include <QSet>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QSaveFile>
#include <QShortcut>
#include <QPushButton>
#include <QPaintEvent>
#include <QResizeEvent>
#include <utility>
#include <functional>
#include <QScrollBar>
#include <QScrollArea>
#include <QSplitter>
#include <QFont>
#include <QPixmap>
#include <QEvent>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QtGlobal>

void SidboxTileStamp::resizeStamp(int w, int h)
{
    w = qBound(1, w, 16);
    h = qBound(1, h, 16);
    QByteArray nextG(w * h * 2, char(0));
    QByteArray nextC(w * h, char(0));
    QByteArray nextF(w * h, char(0));
    for (int y = 0; y < qMin(height, h); ++y)
        for (int x = 0; x < qMin(width, w); ++x) {
            const int old = y * width + x;
            const int now = y * w + x;
            nextG[now * 2] = graphics.at(old * 2);
            nextG[now * 2 + 1] = graphics.at(old * 2 + 1);
            nextC[now] = collisions.at(old);
            nextF[now] = flips.at(old);
        }
    width = w; height = h;
    graphics = nextG; collisions = nextC; flips = nextF;
}

void SidboxTilemap::resizeMap(int w, int h)
{
    w = qBound(30, w, 256);
    h = qBound(20, h, 256);
    QByteArray nextG(w * h * 2, char(0)), nextC(w * h, char(0)), nextF(w * h, char(0));
    for (int y = 0; y < qMin(h, height); ++y)
        for (int x = 0; x < qMin(w, width); ++x) {
            const int from = y * width + x, to = y * w + x;
            if (from * 2 + 1 < graphics.size()) {
                nextG[to * 2] = graphics.at(from * 2);
                nextG[to * 2 + 1] = graphics.at(from * 2 + 1);
            }
            if (from < collisions.size()) nextC[to] = collisions.at(from);
            if (from < flips.size()) nextF[to] = flips.at(from);
        }
    width = w; height = h;
    graphics = nextG; collisions = nextC; flips = nextF;
}

QJsonObject SidboxTilemap::toJson() const
{
    QJsonObject result;
    result.insert(QStringLiteral("width"), width);
    result.insert(QStringLiteral("height"), height);
    result.insert(QStringLiteral("tileSize"), tileSize);
    result.insert(QStringLiteral("atlasPath"), atlasPath);
    result.insert(QStringLiteral("graphics16Z"), QString::fromLatin1(qCompress(graphics, 9).toBase64()));
    result.insert(QStringLiteral("collisionsZ"), QString::fromLatin1(qCompress(collisions, 9).toBase64()));
    result.insert(QStringLiteral("flipsZ"), QString::fromLatin1(qCompress(flips, 9).toBase64()));
    QJsonArray animated;
    for (const SidboxTileAnimation &a : animations) {
        QJsonObject item;
        item.insert(QStringLiteral("graphicId"), a.graphicId);
        item.insert(QStringLiteral("frames"), a.frames);
        item.insert(QStringLiteral("frameTicks"), a.frameTicks);
        item.insert(QStringLiteral("loop"), a.loop);
        item.insert(QStringLiteral("bounce"), a.bounce);
        animated.append(item);
    }
    result.insert(QStringLiteral("animations"), animated);
    QJsonArray stampList;
    for (const SidboxTileStamp &stamp : stamps) {
        QJsonObject item;
        item.insert(QStringLiteral("name"), stamp.name);
        item.insert(QStringLiteral("width"), stamp.width);
        item.insert(QStringLiteral("height"), stamp.height);
        item.insert(QStringLiteral("tileSize"), stamp.tileSize);
        item.insert(QStringLiteral("graphics16Z"), QString::fromLatin1(qCompress(stamp.graphics, 9).toBase64()));
        item.insert(QStringLiteral("collisionsZ"), QString::fromLatin1(qCompress(stamp.collisions, 9).toBase64()));
        item.insert(QStringLiteral("flipsZ"), QString::fromLatin1(qCompress(stamp.flips, 9).toBase64()));
        stampList.append(item);
    }
    result.insert(QStringLiteral("stamps"), stampList);
    return result;
}

bool SidboxTilemap::fromJson(const QJsonObject &object)
{
    const int w = object.value(QStringLiteral("width")).toInt(100);
    const int h = object.value(QStringLiteral("height")).toInt(100);
    const int tile = object.value(QStringLiteral("tileSize")).toInt(16);
    if (w < 30 || w > 256 || h < 20 || h > 256 ||
        (tile != 8 && tile != 16 && tile != 32)) return false;
    const bool extended = object.contains(QStringLiteral("graphics16Z"));
    const QString encodedG = object.value(extended ? QStringLiteral("graphics16Z")
                                                  : QStringLiteral("graphicsZ")).toString();
    const QString encodedC = object.value(QStringLiteral("collisionsZ")).toString();
    if (encodedG.size() > 400000 || encodedC.size() > 131072) return false;
    const QByteArray compressedG = QByteArray::fromBase64(encodedG.toLatin1());
    const QByteArray compressedC = QByteArray::fromBase64(encodedC.toLatin1());
    // qUncompress uses a 4-byte big-endian uncompressed-length prefix.
    // Reject excessive/corrupt lengths before requesting decompression.
    auto expectedLength = [](const QByteArray &data) -> quint32 {
        if (data.size() < 4) return 0;
        const auto *p = reinterpret_cast<const unsigned char *>(data.constData());
        return (quint32(p[0]) << 24) | (quint32(p[1]) << 16) | (quint32(p[2]) << 8) | p[3];
    };
    if (expectedLength(compressedG) != quint32(w * h * (extended ? 2 : 1)) ||
        expectedLength(compressedC) != quint32(w * h)) return false;
    const QByteArray g = qUncompress(compressedG);
    const QByteArray c = qUncompress(compressedC);
    if (g.size() != w * h * (extended ? 2 : 1) || c.size() != w * h) return false;
    QByteArray f(w * h, char(0));
    const QJsonValue flipsValueMap = object.value(QStringLiteral("flipsZ"));
    if (!flipsValueMap.isUndefined()) {
        if (!flipsValueMap.isString()) return false;
        const QString encodedF = flipsValueMap.toString();
        if (encodedF.size() > 131072) return false;
        const QByteArray compressedF = QByteArray::fromBase64(encodedF.toLatin1());
        if (expectedLength(compressedF) != quint32(w * h)) return false;
        f = qUncompress(compressedF);
        if (f.size() != w * h) return false;
        for (char flags : f) if (quint8(flags) & ~quint8(3)) return false;
    }
    QVector<SidboxTileAnimation> decoded;
    const QJsonValue animationValue = object.value(QStringLiteral("animations"));
    if (!animationValue.isUndefined() && !animationValue.isArray()) return false;
    const QJsonArray list = animationValue.toArray();
    if (list.size() > 65535) return false;
    QSet<int> seen;
    for (const QJsonValue &value : list) {
        if (!value.isObject()) return false;
        const QJsonObject entry = value.toObject();
        SidboxTileAnimation a;
        a.graphicId = entry.value(QStringLiteral("graphicId")).toInt(0);
        a.frames = entry.value(QStringLiteral("frames")).toInt(0);
        a.frameTicks = entry.value(QStringLiteral("frameTicks")).toInt(0);
        a.loop = entry.value(QStringLiteral("loop")).toBool(true);
        a.bounce = entry.value(QStringLiteral("bounce")).toBool(false);
        if (a.graphicId < 1 || a.graphicId > 65535 || a.frames < 1 ||
            a.frames > 16 || a.graphicId + a.frames - 1 > 65535 ||
            a.frameTicks < 1 || a.frameTicks > 255 || seen.contains(a.graphicId)) return false;
        seen.insert(a.graphicId);
        decoded.append(a);
    }
    QVector<SidboxTileStamp> decodedStamps;
    const QJsonValue stampValue = object.value(QStringLiteral("stamps"));
    if (!stampValue.isUndefined() && !stampValue.isArray()) return false;
    const QJsonArray stampItems = stampValue.toArray();
    if (stampItems.size() > 128) return false;
    for (const QJsonValue &value : stampItems) {
        if (!value.isObject()) return false;
        const QJsonObject item = value.toObject();
        SidboxTileStamp stamp;
        stamp.name = item.value(QStringLiteral("name")).toString();
        stamp.width = item.value(QStringLiteral("width")).toInt(0);
        stamp.height = item.value(QStringLiteral("height")).toInt(0);
        stamp.tileSize = item.value(QStringLiteral("tileSize")).toInt(0);
        if (stamp.name.isEmpty() || stamp.name.size() > 80 || stamp.width < 1 ||
            stamp.width > 16 || stamp.height < 1 || stamp.height > 16 ||
            (stamp.tileSize != 8 && stamp.tileSize != 16 && stamp.tileSize != 32)) return false;
        const auto decode = [](const QString &base64, int size) -> QByteArray {
            if (base64.size() > 4000) return {};
            const QByteArray encoded = QByteArray::fromBase64(base64.toLatin1());
            if (encoded.size() < 4) return {};
            const auto *p = reinterpret_cast<const unsigned char *>(encoded.constData());
            const quint32 length = (quint32(p[0]) << 24) | (quint32(p[1]) << 16)
                                 | (quint32(p[2]) << 8) | p[3];
            if (length != quint32(size)) return {};
            return qUncompress(encoded);
        };
        const int count = stamp.width * stamp.height;
        stamp.graphics = decode(item.value(QStringLiteral("graphics16Z")).toString(), count * 2);
        stamp.collisions = decode(item.value(QStringLiteral("collisionsZ")).toString(), count);
        const QJsonValue flipsValue = item.value(QStringLiteral("flipsZ"));
        stamp.flips = flipsValue.isUndefined() ? QByteArray(count, char(0))
            : decode(flipsValue.toString(), count);
        if (stamp.graphics.size() != count * 2 || stamp.collisions.size() != count ||
            stamp.flips.size() != count) return false;
        for (char f : stamp.flips) if ((quint8(f) & ~quint8(3)) != 0) return false;
        decodedStamps.append(std::move(stamp));
    }
    width = w; height = h; tileSize = tile;
    atlasPath = object.value(QStringLiteral("atlasPath")).toString();
    if (extended) graphics = g;
    else {
        // Old .sbgm projects used one byte per graphic ID. Upgrade in memory.
        graphics = QByteArray(w * h * 2, char(0));
        for (int i = 0; i < g.size(); ++i)
            graphics[i * 2] = g.at(i);
    }
    collisions = c;
    flips = f;
    animations = decoded;
    stamps = std::move(decodedStamps);
    return true;
}

// Map graphic IDs are packed little-endian, so .sbgm is host-independent.
static quint16 mapGraphic(const QByteArray &bytes, int index)
{
    const int pos = index * 2;
    return quint16(quint8(bytes.at(pos))) | (quint16(quint8(bytes.at(pos + 1))) << 8);
}

static void setMapGraphic(QByteArray &bytes, int index, quint16 id)
{
    const int pos = index * 2;
    bytes[pos] = char(id & 255);
    bytes[pos + 1] = char(id >> 8);
}

// Same playback maths as the V1 helper (50 VBlanks per second).
static int tileAnimationFrame(const SidboxTileAnimation &a, qint64 ticks)
{
    if (a.frames < 2 || a.frameTicks < 1) return 0;
    const qint64 step = ticks / a.frameTicks;
    if (a.bounce) {
        const qint64 last = a.frames - 1;
        const qint64 cycle = last * 2;
        const qint64 pos = a.loop ? step % cycle : qMin(step, cycle);
        return int(pos <= last ? pos : cycle - pos);
    }
    return int(a.loop ? step % a.frames : qMin(step, qint64(a.frames - 1)));
}

static const SidboxTileAnimation *findTileAnimation(const SidboxTilemap &map, int id)
{
    for (const SidboxTileAnimation &a : map.animations)
        if (a.graphicId == id) return &a;
    return nullptr;
}

// Same flat, visible-chevron treatment as the main Game Designer controls.
// The colours are inherited from the active CoderGirl theme.
class TilemapComboBox final : public QComboBox
{
public:
    using QComboBox::QComboBox;
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QComboBox::paintEvent(event);
        QPainter painter(this);
        QPen pen(palette().color(isEnabled() ? QPalette::Active : QPalette::Disabled,
                                 QPalette::Text));
        pen.setWidth(2);
        painter.setPen(pen);
        const int cx = width() - 12;
        const int cy = height() / 2;
        painter.drawLine(cx - 4, cy - 2, cx, cy + 2);
        painter.drawLine(cx, cy + 2, cx + 4, cy - 2);
    }
};

class SidboxTilemapEditor::Canvas final : public QAbstractScrollArea
{
public:
    SidboxTilemap *map = nullptr;
    QImage *atlas = nullptr;
    int zoom = 2;
    bool showCollisions = true;
    // -1 = preserve existing value, 0 = erase, 1 = selected atlas tile.
    int graphicMode = 1;
    int graphicBrush = 1;
    int collisionBrush = -1;
    int flipMode = 1; // -1 = preserve existing, 1 = apply the current flip checkboxes
    quint8 flipBrush = 0;
    quint8 stampMirror = 0;
    int stampIndex = -1; // -1 means ordinary atlas-tile painting
    bool painting = false;
    bool panning = false;
    bool erasingStroke = false;
    bool hoverValid = false;
    QPoint hoverCell;
    // An individual stamp drag is aligned to its first pressed map cell.
    // Grid coordinates are measured in stamp widths/heights, not tile pixels.
    QPoint stampAnchor;
    QPoint lastStampGrid;
    bool stampAnchorValid = false;
    bool lastStampGridValid = false;
    std::function<void()> strokeStarted;
    std::function<void()> strokeFinished;
    QPoint lastPan;
    int wheelRemainderX = 0;
    int wheelRemainderY = 0;
    qint64 animationTicks = 0;
    void refreshAnimated(qint64 ticks)
    {
        if (!map || map->animations.isEmpty()) return;
        if (ticks == animationTicks) return;
        animationTicks = ticks;
        const int px = map->tileSize * zoom;
        const int scrollX = horizontalScrollBar()->value();
        const int scrollY = verticalScrollBar()->value();
        const int x0 = qMax(0, scrollX / px);
        const int y0 = qMax(0, scrollY / px);
        const int x1 = qMin(map->width, (scrollX + viewport()->width()) / px + 1);
        const int y1 = qMin(map->height, (scrollY + viewport()->height()) / px + 1);
        QRegion dirty;
        for (int y = y0; y < y1; ++y)
            for (int x = x0; x < x1; ++x) {
                const int id = mapGraphic(map->graphics, y*map->width+x);
                if (findTileAnimation(*map, id))
                    dirty += QRect(x*px-scrollX, y*px-scrollY, px, px);
            }
        if (!dirty.isEmpty()) viewport()->update(dirty);
    }

    explicit Canvas(QWidget *parent = nullptr) : QAbstractScrollArea(parent)
    {
        setFocusPolicy(Qt::StrongFocus);
        setMouseTracking(true);
        viewport()->setMouseTracking(true); // QAbstractScrollArea uses a separate viewport widget
        viewport()->setCursor(Qt::CrossCursor);
    }
    void adjust()
    {
        if (!map) return;
        const int px = map->tileSize * zoom;
        horizontalScrollBar()->setRange(0, qMax(0, map->width * px - viewport()->width()));
        verticalScrollBar()->setRange(0, qMax(0, map->height * px - viewport()->height()));
        horizontalScrollBar()->setPageStep(viewport()->width());
        verticalScrollBar()->setPageStep(viewport()->height());
        viewport()->update();
    }
    // The preview is deliberately paint-only: it never changes a tile or the
    // undo stack. While dragging a stamp it uses the same first-click grid
    // and negative-coordinate floor division as paintAt().
    QPoint previewBaseCell() const
    {
        if (!map || !hoverValid) return QPoint(-1, -1);
        if (stampIndex < 0 || stampIndex >= map->stamps.size() ||
            !painting || !stampAnchorValid) return hoverCell;
        const SidboxTileStamp &stamp = map->stamps.at(stampIndex);
        if (stamp.tileSize != map->tileSize) return hoverCell;
        const int dx = hoverCell.x() - stampAnchor.x();
        const int dy = hoverCell.y() - stampAnchor.y();
        const int gx = dx >= 0 ? dx / stamp.width
                               : -((-dx + stamp.width - 1) / stamp.width);
        const int gy = dy >= 0 ? dy / stamp.height
                               : -((-dy + stamp.height - 1) / stamp.height);
        return QPoint(stampAnchor.x() + gx * stamp.width,
                      stampAnchor.y() + gy * stamp.height);
    }
    QRect previewBounds() const
    {
        if (!map || !hoverValid || panning) return QRect();
        const int px = map->tileSize * zoom;
        int w = 1, h = 1;
        if (stampIndex >= 0 && stampIndex < map->stamps.size()) {
            const SidboxTileStamp &stamp = map->stamps.at(stampIndex);
            if (stamp.tileSize == map->tileSize) {
                w = stamp.width; h = stamp.height;
            }
        }
        const QPoint base = previewBaseCell();
        return QRect(base.x() * px - horizontalScrollBar()->value(),
                     base.y() * px - verticalScrollBar()->value(),
                     w * px, h * px).adjusted(-3, -3, 3, 3);
    }
    void updateHover(const QPoint &at)
    {
        const QRect before = previewBounds();
        if (!map || at.x() < 0 || at.y() < 0) {
            hoverValid = false;
        } else {
            const int px = map->tileSize * zoom;
            hoverCell = QPoint((at.x() + horizontalScrollBar()->value()) / px,
                               (at.y() + verticalScrollBar()->value()) / px);
            hoverValid = hoverCell.x() >= 0 && hoverCell.x() < map->width &&
                         hoverCell.y() >= 0 && hoverCell.y() < map->height;
        }
        const QRect after = previewBounds();
        if (before != after) {
            viewport()->update(before);
            viewport()->update(after);
        }
    }
    void paintBrushPreview(QPainter &painter)
    {
        if (!map || !hoverValid || panning) return;
        const int px = map->tileSize * zoom;
        const QPoint base = previewBaseCell();
        int w = 1, h = 1;
        const SidboxTileStamp *stamp = nullptr;
        if (stampIndex >= 0 && stampIndex < map->stamps.size() &&
            map->stamps.at(stampIndex).tileSize == map->tileSize) {
            stamp = &map->stamps.at(stampIndex);
            w = stamp->width; h = stamp->height;
        }
        const QRect mapPixels(-horizontalScrollBar()->value(),
                              -verticalScrollBar()->value(),
                              map->width * px, map->height * px);
        const QRect footprint(base.x() * px - horizontalScrollBar()->value(),
                              base.y() * px - verticalScrollBar()->value(),
                              w * px, h * px);
        if (!footprint.intersects(mapPixels)) return;
        const bool erase = (painting && erasingStroke) ||
            (!stamp && graphicMode == 0 && !painting);
        const int cols = atlas && !atlas->isNull() ? atlas->width() / map->tileSize : 0;
        const int rows = atlas && !atlas->isNull() ? atlas->height() / map->tileSize : 0;
        painter.save();
        painter.setClipRect(viewport()->rect().intersected(mapPixels));
        // Show the actual sprite artwork, including the stamp's per-cell flags.
        // Editing collisions only still shows a clear outline without inventing a tile.
        if (!erase) {
            painter.setOpacity(0.62);
            for (int sy = 0; sy < h; ++sy) for (int sx = 0; sx < w; ++sx) {
                const int x = base.x() + sx, y = base.y() + sy;
                if (x < 0 || y < 0 || x >= map->width || y >= map->height) continue;
                int id = 0;
                quint8 flip = 0;
                if (stamp) {
                    const int sourceX = (stampMirror & 1) ? w - 1 - sx : sx;
                    const int sourceY = (stampMirror & 2) ? h - 1 - sy : sy;
                    const int i = sourceY * w + sourceX;
                    id = mapGraphic(stamp->graphics, i);
                    flip = quint8(stamp->flips.at(i)) ^ stampMirror;
                } else if (graphicMode == 1) {
                    id = graphicBrush;
                    flip = flipMode >= 0 ? flipBrush :
                        quint8(map->flips.at(y * map->width + x));
                } else if (graphicMode == -1 && flipMode >= 0) {
                    id = mapGraphic(map->graphics, y * map->width + x);
                    flip = flipBrush;
                }
                if (!id) continue;
                const QRect dest(x * px - horizontalScrollBar()->value(),
                                 y * px - verticalScrollBar()->value(), px, px);
                int frameTile = id;
                if (const SidboxTileAnimation *anim = findTileAnimation(*map, id))
                    if (id + anim->frames - 1 <= cols * rows)
                        frameTile += tileAnimationFrame(*anim, animationTicks);
                if (cols > 0 && frameTile <= cols * rows) {
                    const int n = frameTile - 1;
                    const QImage tile = atlas->copy((n % cols) * map->tileSize,
                        (n / cols) * map->tileSize, map->tileSize, map->tileSize);
                    painter.drawImage(dest, flip ? tile.mirrored(bool(flip & 1), bool(flip & 2)) : tile);
                } else {
                    painter.fillRect(dest, QColor(110, 137, 156));
                }
            }
            painter.setOpacity(1.0);
        } else {
            painter.fillRect(footprint, QColor(240, 90, 90, 55));
        }
        // Double-outline remains visible against both very dark and bright tiles.
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(QColor(0, 0, 0, 225), 3));
        painter.drawRect(footprint.adjusted(1, 1, -2, -2));
        painter.setPen(QPen(erase ? QColor(255, 110, 110) : QColor(93, 255, 226), 1));
        painter.drawRect(footprint.adjusted(1, 1, -2, -2));
        painter.restore();
    }
    void paintAt(const QPoint &at, bool erase)
    {
        if (!map) return;
        const int px = map->tileSize * zoom;
        const int tx = (at.x() + horizontalScrollBar()->value()) / px;
        const int ty = (at.y() + verticalScrollBar()->value()) / px;
        if (tx < 0 || ty < 0 || tx >= map->width || ty >= map->height) return;
        // A stamp is a design-time array of ordinary graphics + collisions.
        // Anchor the temporary stamp-sized grid to the FIRST click of the
        // drag, instead of trying to place a stamp at every 8x8 tile touched.
        // Interpolate skipped stamp cells when the mouse moves quickly.
        if (stampIndex >= 0 && stampIndex < map->stamps.size()) {
            const SidboxTileStamp &stamp = map->stamps.at(stampIndex);
            if (stamp.tileSize != map->tileSize) return;
            if (!stampAnchorValid) {
                stampAnchor = QPoint(tx, ty);
                stampAnchorValid = true;
                lastStampGridValid = false;
            }
            const int dx = tx - stampAnchor.x();
            const int dy = ty - stampAnchor.y();
            // C++ integer division truncates toward zero; floor division is
            // required for stamps dragged LEFT/UP of the first clicked cell.
            const int gx = dx >= 0 ? dx / stamp.width
                                   : -((-dx + stamp.width - 1) / stamp.width);
            const int gy = dy >= 0 ? dy / stamp.height
                                   : -((-dy + stamp.height - 1) / stamp.height);
            const QPoint target(gx, gy);
            if (lastStampGridValid && target == lastStampGrid) return;

            const auto applyStamp = [this, &stamp, erase, px](int gridX, int gridY) {
                const int baseX = stampAnchor.x() + gridX * stamp.width;
                const int baseY = stampAnchor.y() + gridY * stamp.height;
                QRect dirty;
                for (int sy = 0; sy < stamp.height; ++sy)
                    for (int sx = 0; sx < stamp.width; ++sx) {
                        const int x = baseX + sx, y = baseY + sy;
                        if (x < 0 || y < 0 || x >= map->width || y >= map->height) continue;
                        const int sourceX = (stampMirror & 1) ? stamp.width - 1 - sx : sx;
                        const int sourceY = (stampMirror & 2) ? stamp.height - 1 - sy : sy;
                        const int cell = sourceY * stamp.width + sourceX;
                        const int index = y * map->width + x;
                        const quint16 g = erase ? 0 : mapGraphic(stamp.graphics, cell);
                        char c = erase ? char(0) : stamp.collisions.at(cell);
                        if (!erase && (stampMirror & 1)) {
                            if (quint8(c) == 3) c = char(4);
                            else if (quint8(c) == 4) c = char(3);
                        }
                        const char f = (erase || !g) ? char(0)
                            : char(quint8(stamp.flips.at(cell)) ^ stampMirror);
                        bool changed = false;
                        if (mapGraphic(map->graphics, index) != g) {
                            setMapGraphic(map->graphics, index, g);
                            changed = true;
                        }
                        if (map->collisions.at(index) != c) {
                            map->collisions[index] = c;
                            changed = true;
                        }
                        if (map->flips.at(index) != f) {
                            map->flips[index] = f;
                            changed = true;
                        }
                        if (changed) dirty |= QRect(x * px - horizontalScrollBar()->value(),
                                                   y * px - verticalScrollBar()->value(), px + 1, px + 1);
                    }
                if (!dirty.isEmpty()) viewport()->update(dirty);
            };

            if (!lastStampGridValid) {
                applyStamp(gx, gy);
            } else {
                const int diffX = gx - lastStampGrid.x();
                const int diffY = gy - lastStampGrid.y();
                const int steps = qMax(qAbs(diffX), qAbs(diffY));
                for (int i = 1; i <= steps; ++i)
                    applyStamp(lastStampGrid.x() + qRound(double(diffX) * i / steps),
                               lastStampGrid.y() + qRound(double(diffY) * i / steps));
            }
            lastStampGrid = target;
            lastStampGridValid = true;
            return;
        }
        const int index = ty * map->width + tx;
        bool changed = false;
        // One stroke can change graphics and collision together, or either one.
        if (graphicMode >= 0) {
            const quint16 value = quint16(erase ? 0 : (graphicMode == 0 ? 0 : graphicBrush));
            if (mapGraphic(map->graphics, index) != value) {
                setMapGraphic(map->graphics, index, value);
                changed = true;
            }
        }
        if (erase || flipMode >= 0) {
            const char value = char(erase ? 0 : (graphicMode == 0 ? 0 : flipBrush));
            if (map->flips.at(index) != value) {
                map->flips[index] = value;
                changed = true;
            }
        }
        if (collisionBrush >= 0) {
            const char value = char(erase ? 0 : collisionBrush);
            if (map->collisions.at(index) != value) {
                map->collisions[index] = value;
                changed = true;
            }
        }
        if (changed) {
            viewport()->update(QRect(tx * px - horizontalScrollBar()->value(),
                                     ty * px - verticalScrollBar()->value(), px+1, px+1));
        }
    }
protected:
    void resizeEvent(QResizeEvent *event) override { QAbstractScrollArea::resizeEvent(event); adjust(); }
    void paintEvent(QPaintEvent *event) override
    {
        QPainter painter(viewport());
        const QRect dirty = event->rect();
        painter.fillRect(dirty, QColor(28, 37, 49));
        if (!map) return;
        const int px = map->tileSize * zoom;
        const int scrollX = horizontalScrollBar()->value();
        const int scrollY = verticalScrollBar()->value();
        const int x0 = qMax(0, (scrollX + dirty.left()) / px);
        const int y0 = qMax(0, (scrollY + dirty.top()) / px);
        const int x1 = qMin(map->width, (scrollX + dirty.right()) / px + 2);
        const int y1 = qMin(map->height, (scrollY + dirty.bottom()) / px + 2);
        const int cols = atlas && !atlas->isNull() ? atlas->width() / map->tileSize : 0;
        const int rows = atlas && !atlas->isNull() ? atlas->height() / map->tileSize : 0;
        painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
        for (int y = y0; y < y1; ++y) for (int x = x0; x < x1; ++x) {
            const QRect dest(x * px - scrollX, y * px - scrollY, px, px);
            const int i = y * map->width + x;
            const int tile = mapGraphic(map->graphics, i);
            int frameTile = tile;
            if (const SidboxTileAnimation *anim = findTileAnimation(*map, tile))
                if (tile + anim->frames - 1 <= cols*rows)
                    frameTile += tileAnimationFrame(*anim, animationTicks);
            if (frameTile && cols > 0 && frameTile <= cols * rows) {
                const int n = frameTile - 1;
                const QImage tileImage = atlas->copy((n % cols) * map->tileSize,
                    (n / cols) * map->tileSize, map->tileSize, map->tileSize);
                const quint8 flip = quint8(map->flips.at(i));
                painter.drawImage(dest, flip ? tileImage.mirrored(bool(flip & 1), bool(flip & 2)) : tileImage);
            } else if (tile) {
                painter.fillRect(dest, QColor(84, 90, 105));
                painter.setPen(Qt::white);
                painter.drawText(dest, Qt::AlignCenter, QString::number(tile));
            }
            if (showCollisions) {
                const unsigned type = quint8(map->collisions.at(i));
                if (type) {
                    const QColor colour = type == 1 ? QColor(50, 233, 179, 110)
                        : type == 2 ? QColor(255, 216, 70, 125)
                        : type == 5 ? QColor(240, 78, 75, 135)
                        : type == 6 ? QColor(153, 103, 246, 140)
                        : QColor(84, 174, 244, 135);
                    painter.fillRect(dest, colour);
                    painter.setPen(Qt::white);
                    painter.drawText(dest, Qt::AlignCenter, QString::number(type));
                }
            }
            painter.setPen(QColor(128, 157, 175, 68));
            painter.drawRect(dest.adjusted(0, 0, -1, -1));
        }
        paintBrushPreview(painter);
    }
    bool viewportEvent(QEvent *event) override
    {
        if (event->type() == QEvent::Leave) {
            const QRect previous = previewBounds();
            hoverValid = false;
            if (!previous.isEmpty()) viewport()->update(previous);
        }
        return QAbstractScrollArea::viewportEvent(event);
    }
    void mousePressEvent(QMouseEvent *e) override
    {
        if (e->button() == Qt::MiddleButton ||
            (e->button() == Qt::LeftButton && e->modifiers() & Qt::AltModifier)) {
            const QRect previous = previewBounds();
            panning = true; lastPan = e->position().toPoint();
            if (!previous.isEmpty()) viewport()->update(previous);
            viewport()->setCursor(Qt::ClosedHandCursor); return;
        }
        if (e->button() == Qt::LeftButton || e->button() == Qt::RightButton) {
            if (strokeStarted) strokeStarted();
            const QRect previous = previewBounds();
            painting = true;
            erasingStroke = e->button() == Qt::RightButton;
            stampAnchorValid = false;
            lastStampGridValid = false;
            paintAt(e->position().toPoint(), erasingStroke);
            updateHover(e->position().toPoint());
            viewport()->update(previous);
            viewport()->update(previewBounds());
        }
    }
    void mouseMoveEvent(QMouseEvent *e) override
    {
        if (panning) {
            const QPoint at = e->position().toPoint();
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + lastPan.x() - at.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() + lastPan.y() - at.y());
            lastPan = at;
        } else if (painting && e->buttons() & (Qt::LeftButton | Qt::RightButton)) {
            const QRect previous = previewBounds();
            paintAt(e->position().toPoint(), erasingStroke);
            updateHover(e->position().toPoint());
            viewport()->update(previous);
            viewport()->update(previewBounds());
        } else if (!panning) {
            updateHover(e->position().toPoint());
        }
    }
    void mouseReleaseEvent(QMouseEvent *e) override
    {
        const QRect previous = previewBounds();
        if (e->button() == Qt::MiddleButton || e->button() == Qt::LeftButton) {
            panning = false;
            viewport()->setCursor(Qt::CrossCursor);
        }
        if ((e->button() == Qt::RightButton || e->button() == Qt::LeftButton) && painting) {
            painting = false;
            erasingStroke = false;
            stampAnchorValid = false;
            lastStampGridValid = false;
            if (strokeFinished) strokeFinished();
        }
        updateHover(e->position().toPoint());
        viewport()->update(previous);
        viewport()->update(previewBounds());
    }
    void wheelEvent(QWheelEvent *e) override
    {
        // Move exactly one map tile per mouse-wheel notch, at the current zoom.
        // Keep middle-button dragging pixel-accurate and unchanged.
        const QPoint angle = e->angleDelta();
        if (angle.isNull()) {
            // Touchpads may send pixel-based scrolling instead of wheel notches.
            QAbstractScrollArea::wheelEvent(e);
            return;
        }

        int deltaX = angle.x();
        int deltaY = angle.y();
        if ((e->modifiers() & Qt::ShiftModifier) && deltaX == 0) {
            deltaX = deltaY;
            deltaY = 0;
        }

        // Some wheels send fractions of a notch: collect them until 120 units.
        wheelRemainderX += deltaX;
        wheelRemainderY += deltaY;
        const int notchesX = wheelRemainderX / 120;
        const int notchesY = wheelRemainderY / 120;
        wheelRemainderX -= notchesX * 120;
        wheelRemainderY -= notchesY * 120;

        const int tilePixels = map ? map->tileSize * zoom : 16 * zoom;
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - notchesX * tilePixels);
        verticalScrollBar()->setValue(verticalScrollBar()->value() - notchesY * tilePixels);
        updateHover(e->position().toPoint());
        e->accept();
    }
};

// Bottom-right stamp editor. Atlas selections provide the individual cells;
// stamps are saved in SidboxTilemap and NOT in the runtime .map file.
class SidboxTilemapEditor::StampCanvas final : public QWidget
{
public:
    SidboxTilemap *map = nullptr;
    QImage *atlas = nullptr;
    int selected = -1;
    int graphicBrush = 1;
    int graphicMode = 1;
    int collisionBrush = -1;
    int flipMode = 1;
    quint8 flipBrush = 0;
    std::function<void()> modified;
    std::function<void()> strokeStarted;
    bool painting = false;
    bool erased = false;
    bool strokeDirty = false;
    bool hoverValid = false;
    QPoint hoverCell;
    explicit StampCanvas(QWidget *parent = nullptr) : QWidget(parent)
    {
        setCursor(Qt::CrossCursor);
        setMinimumSize(180, 120);
        setMouseTracking(true);
    }
    void refresh()
    {
        if (!map || selected < 0 || selected >= map->stamps.size()) {
            setFixedSize(200, 130);
        } else {
            const auto &stamp = map->stamps.at(selected);
            setFixedSize(qMax(200, stamp.width * 24 + 1),
                         qMax(130, stamp.height * 24 + 1));
        }
        update();
    }
protected:
    void paintEvent(QPaintEvent *) override
    {
        QPainter painter(this);
        painter.fillRect(rect(), QColor(28, 37, 49));
        if (!map || selected < 0 || selected >= map->stamps.size()) {
            painter.setPen(Qt::white);
            painter.drawText(rect(), Qt::AlignCenter, tr("Add or select a stamp above"));
            return;
        }
        const SidboxTileStamp &stamp = map->stamps.at(selected);
        const int cols = atlas && !atlas->isNull() ? atlas->width() / stamp.tileSize : 0;
        const int rows = atlas && !atlas->isNull() ? atlas->height() / stamp.tileSize : 0;
        painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
        for (int y = 0; y < stamp.height; ++y)
            for (int x = 0; x < stamp.width; ++x) {
                const QRect cell(x * 24, y * 24, 24, 24);
                const int i = y * stamp.width + x;
                const quint16 tile = mapGraphic(stamp.graphics, i);
                if (tile && cols > 0 && tile <= cols * rows) {
                    const int n = tile - 1;
                    const QImage tileImage = atlas->copy((n % cols) * stamp.tileSize,
                              (n / cols) * stamp.tileSize, stamp.tileSize, stamp.tileSize);
                    const quint8 flip = quint8(stamp.flips.at(i));
                    painter.drawImage(cell, flip ? tileImage.mirrored(bool(flip & 1), bool(flip & 2)) : tileImage);
                } else if (tile) {
                    painter.fillRect(cell, QColor(84, 90, 105));
                    painter.setPen(Qt::white);
                    painter.drawText(cell, Qt::AlignCenter, QString::number(tile));
                }
                const quint8 collision = quint8(stamp.collisions.at(i));
                if (collision) {
                    painter.fillRect(cell, QColor(80, 195, 225, 75));
                    painter.setPen(Qt::white);
                    painter.drawText(cell, Qt::AlignBottom | Qt::AlignRight,
                                     QString::number(collision));
                }
                painter.setPen(QColor(128, 157, 175, 115));
                painter.drawRect(cell.adjusted(0, 0, -1, -1));
            }
        if (hoverValid && hoverCell.x() >= 0 && hoverCell.y() >= 0 &&
            hoverCell.x() < stamp.width && hoverCell.y() < stamp.height) {
            const QRect target(hoverCell.x() * 24, hoverCell.y() * 24, 24, 24);
            painter.save();
            if (painting && erased) {
                painter.fillRect(target, QColor(240, 90, 90, 65));
            } else if (graphicMode == 1 && cols > 0 &&
                       graphicBrush > 0 && graphicBrush <= cols * rows) {
                const int n = graphicBrush - 1;
                const QImage tile = atlas->copy((n % cols) * stamp.tileSize,
                    (n / cols) * stamp.tileSize, stamp.tileSize, stamp.tileSize);
                const quint8 flip = flipMode >= 0 ? flipBrush :
                    quint8(stamp.flips.at(hoverCell.y() * stamp.width + hoverCell.x()));
                painter.setOpacity(0.62);
                painter.drawImage(target, flip ? tile.mirrored(bool(flip & 1), bool(flip & 2)) : tile);
                painter.setOpacity(1.0);
            }
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(QColor(0, 0, 0, 225), 3));
            painter.drawRect(target.adjusted(1, 1, -2, -2));
            painter.setPen(QPen(painting && erased ? QColor(255, 110, 110) : QColor(93, 255, 226), 1));
            painter.drawRect(target.adjusted(1, 1, -2, -2));
            painter.restore();
        }
    }
    void updateHover(const QPoint &at)
    {
        const QPoint previous = hoverCell;
        const bool oldValid = hoverValid;
        hoverCell = QPoint(at.x() / 24, at.y() / 24);
        hoverValid = at.x() >= 0 && at.y() >= 0 && map && selected >= 0 &&
                     selected < map->stamps.size() &&
                     map->stamps.at(selected).tileSize == map->tileSize &&
                     hoverCell.x() < map->stamps.at(selected).width &&
                     hoverCell.y() < map->stamps.at(selected).height;
        if (oldValid != hoverValid || previous != hoverCell) {
            if (oldValid) update(QRect(previous.x() * 24, previous.y() * 24, 25, 25));
            if (hoverValid) update(QRect(hoverCell.x() * 24, hoverCell.y() * 24, 25, 25));
        }
    }
    void leaveEvent(QEvent *event) override
    {
        const bool wasValid = hoverValid;
        hoverValid = false;
        if (wasValid) update(QRect(hoverCell.x() * 24, hoverCell.y() * 24, 25, 25));
        QWidget::leaveEvent(event);
    }
    bool paintCell(const QPoint &at, bool erase)
    {
        if (!map || selected < 0 || selected >= map->stamps.size()) return false;
        SidboxTileStamp &stamp = map->stamps[selected];
        if (stamp.tileSize != map->tileSize || at.x() < 0 || at.y() < 0) return false;
        const int x = at.x() / 24, y = at.y() / 24;
        if (x >= stamp.width || y >= stamp.height) return false;
        const int cell = y * stamp.width + x;
        bool changed = false;
        // Keep graphic and collision painting independent, as on the main map.
        if (erase || graphicMode >= 0) {
            const quint16 tile = quint16(erase ? 0 : (graphicMode == 0 ? 0 : graphicBrush));
            if (mapGraphic(stamp.graphics, cell) != tile) {
                setMapGraphic(stamp.graphics, cell, tile);
                changed = true;
            }
        }
        if (erase || flipMode >= 0) {
            const char flip = char(erase ? 0 : (graphicMode == 0 ? 0 : flipBrush));
            if (stamp.flips.at(cell) != flip) {
                stamp.flips[cell] = flip;
                changed = true;
            }
        }
        if (erase || collisionBrush >= 0) {
            const char collision = char(erase ? 0 : collisionBrush);
            if (stamp.collisions.at(cell) != collision) {
                stamp.collisions[cell] = collision;
                changed = true;
            }
        }
        if (changed) update(QRect(x * 24, y * 24, 25, 25));
        return changed;
    }
    void mousePressEvent(QMouseEvent *event) override
    {
        if (event->button() != Qt::LeftButton && event->button() != Qt::RightButton) return;
        if (!map || selected < 0 || selected >= map->stamps.size()) return;
        if (map->stamps.at(selected).tileSize != map->tileSize) return;
        painting = true;
        erased = event->button() == Qt::RightButton;
        strokeDirty = false;
        if (strokeStarted) strokeStarted();
        strokeDirty |= paintCell(event->position().toPoint(), erased);
        updateHover(event->position().toPoint());
        update(); // erasing overlay changed, even if the hovered cell did not
    }
    void mouseMoveEvent(QMouseEvent *event) override
    {
        if (painting && event->buttons() & (Qt::LeftButton | Qt::RightButton))
            strokeDirty |= paintCell(event->position().toPoint(), erased);
        updateHover(event->position().toPoint());
    }
    void mouseReleaseEvent(QMouseEvent *event) override
    {
        if (!painting || (event->button() != Qt::LeftButton &&
                          event->button() != Qt::RightButton)) return;
        painting = false;
        update(); // return from eraser preview to normal brush preview
        if (strokeDirty && modified) modified();
        strokeDirty = false;
    }
};

// One mouse paint stroke is one history entry; resizing and animation edits
// also create entries. Qt's implicitly shared QByteArrays keep this practical.
static bool sameTilemap(const SidboxTilemap &a, const SidboxTilemap &b)
{
    if (a.width != b.width || a.height != b.height || a.tileSize != b.tileSize
        || a.atlasPath != b.atlasPath || a.graphics != b.graphics
        || a.collisions != b.collisions || a.animations.size() != b.animations.size()
        || a.stamps.size() != b.stamps.size() || a.flips != b.flips)
        return false;
    for (int i = 0; i < a.animations.size(); ++i) {
        const auto &left = a.animations.at(i);
        const auto &right = b.animations.at(i);
        if (left.graphicId != right.graphicId || left.frames != right.frames
            || left.frameTicks != right.frameTicks || left.loop != right.loop
            || left.bounce != right.bounce) return false;
    }
    for (int i = 0; i < a.stamps.size(); ++i) {
        const auto &left = a.stamps.at(i);
        const auto &right = b.stamps.at(i);
        if (left.name != right.name || left.width != right.width ||
            left.height != right.height || left.tileSize != right.tileSize ||
            left.graphics != right.graphics || left.collisions != right.collisions ||
            left.flips != right.flips) return false;
    }
    return true;
}

void SidboxTilemapEditor::updateHistoryActions()
{
    if (m_undoButton) m_undoButton->setEnabled(!m_undoStack.isEmpty());
    if (m_redoButton) m_redoButton->setEnabled(!m_redoStack.isEmpty());
}

void SidboxTilemapEditor::recordChange(const SidboxTilemap &before)
{
    if (sameTilemap(before, m_map)) return;
    constexpr int maxHistory = 64;
    if (m_undoStack.size() == maxHistory) m_undoStack.removeFirst();
    m_undoStack.append(before);
    m_redoStack.clear();
    if (m_saveStatus) m_saveStatus->setText(tr("Unsaved changes"));
    updateHistoryActions();
}

void SidboxTilemapEditor::restoreMap(const SidboxTilemap &snapshot)
{
    const bool atlasChanged = m_map.atlasPath != snapshot.atlasPath;
    m_map = snapshot;
    // Restore the original settings without firing edit-history callbacks.
    if (m_sizeX) {
        QSignalBlocker block(m_sizeX);
        m_sizeX->setValue(m_map.width);
    }
    if (m_sizeY) {
        QSignalBlocker block(m_sizeY);
        m_sizeY->setValue(m_map.height);
    }
    if (m_tileSizeCombo) {
        QSignalBlocker block(m_tileSizeCombo);
        m_tileSizeCombo->setCurrentIndex(
            m_tileSizeCombo->findData(m_map.tileSize));
    }
    if (atlasChanged && m_atlasCombo) {
        QSignalBlocker block(m_atlasCombo);
        const QString full = m_map.atlasPath.isEmpty() ? QString()
            : QDir(m_designDirectory).absoluteFilePath(m_map.atlasPath);
        const int index = m_atlasCombo->findData(full);
        m_atlasCombo->setCurrentIndex(index >= 0 ? index : 0);
        setAtlas(full);
    }
    if (m_canvas) {
        m_canvas->adjust();
        m_canvas->viewport()->update();
    }
    updateAtlasPicker();
    updateAnimationControls();
    updateAnimationPreview();
    updateStampList();
    if (m_saveStatus) m_saveStatus->setText(tr("Unsaved changes"));
}

void SidboxTilemapEditor::undoEdit()
{
    if (m_undoStack.isEmpty() || (m_canvas && m_canvas->painting)) return;
    const SidboxTilemap previous = m_undoStack.takeLast();
    m_redoStack.append(m_map);
    restoreMap(previous);
    updateHistoryActions();
}

void SidboxTilemapEditor::redoEdit()
{
    if (m_redoStack.isEmpty() || (m_canvas && m_canvas->painting)) return;
    const SidboxTilemap next = m_redoStack.takeLast();
    m_undoStack.append(m_map);
    restoreMap(next);
    updateHistoryActions();
}

void SidboxTilemapEditor::setSaveCallback(
    const std::function<bool(const SidboxTilemap &)> &callback)
{
    m_saveCallback = callback;
    if (m_saveButton) m_saveButton->setEnabled(bool(m_saveCallback));
}

void SidboxTilemapEditor::setTheme(const IDETheme &theme)
{
    const auto C = [](const QColor &colour) { return ideThemeColorName(colour); };
    // The editor is a dialog, so the parent MainWindow stylesheet alone isn't
    // reliable (especially for combo popup windows on KDE / Wayland).
    setStyleSheet(QStringLiteral(
        "QDialog, QWidget { background-color:%1; color:%2; } "
        "QLabel { background:transparent; color:%2; border:none; } "
        "QPushButton, QToolButton, QSpinBox, QLineEdit, QCheckBox, "
        "QScrollArea, QListWidget, QSplitter, QFrame { border-radius:0px; } "
        "QComboBox { border:1px solid %3; border-radius:0px; "
        "background-color:%4; color:%2; padding:3px 24px 3px 5px; } "
        "QComboBox::drop-down { width:20px; border-left:1px solid %3; "
        "border-radius:0px; background-color:%4; } "
        "QComboBox::down-arrow { image:none; width:0px; height:0px; } "
        "QComboBox QAbstractItemView { border:1px solid %3; border-radius:0px; "
        "background-color:%5; color:%2; selection-background-color:%6; "
        "selection-color:%7; outline:0px; } "
        "QComboBox QAbstractItemView::item:selected { background:%6; color:%7; }")
        .arg(C(theme.windowBackground), C(theme.text), C(theme.border),
             C(theme.inputBackground), C(theme.menuBackground),
             C(theme.accent), C(theme.brightText)));
    QPalette dialogPalette = palette();
    dialogPalette.setColor(QPalette::Window, theme.windowBackground);
    dialogPalette.setColor(QPalette::WindowText, theme.text);
    dialogPalette.setColor(QPalette::Base, theme.inputBackground);
    dialogPalette.setColor(QPalette::Text, theme.text);
    dialogPalette.setColor(QPalette::Button, theme.panelBackground);
    dialogPalette.setColor(QPalette::ButtonText, theme.text);
    dialogPalette.setColor(QPalette::Highlight, theme.accent);
    dialogPalette.setColor(QPalette::HighlightedText, theme.brightText);
    setPalette(dialogPalette);

    // Popup lists have their own viewport palette; don't let the OS theme
    // replace the colours chosen in CoderGirl's Theme Options.
    for (QComboBox *combo : findChildren<QComboBox *>()) {
        combo->setPalette(dialogPalette);
        if (auto *popup = combo->view()) {
            popup->setPalette(dialogPalette);
            popup->setStyleSheet(QStringLiteral(
                "QAbstractItemView { background:%1; color:%2; border:1px solid %3; "
                "border-radius:0px; selection-background-color:%4; selection-color:%5; "
                "outline:0px; } "
                "QAbstractItemView::item:selected { background:%4; color:%5; }")
                .arg(C(theme.menuBackground), C(theme.text), C(theme.border),
                     C(theme.accent), C(theme.brightText)));
        }
    }
}

SidboxTilemapEditor::SidboxTilemapEditor(SidboxTilemap map,
    const QVector<QPair<QString, QString>> &atlases,
    const QString &designDirectory, QWidget *parent)
    : QDialog(parent), m_map(std::move(map)), m_designDirectory(designDirectory)
{
    setWindowTitle(tr("Visual Tilemap Editor — Graphics + Collisions"));
    resize(960, 700);
    // Restore the last window state. First-time opening defaults to maximised.
    QSettings windowSettings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    const QByteArray geometry = windowSettings.value(
        QStringLiteral("GameTilemapEditor/geometry")).toByteArray();
    if (geometry.isEmpty() || !restoreGeometry(geometry))
        setWindowState(windowState() | Qt::WindowMaximized);

    // The map should receive most of the window. Keep its toolbar on top
    // and move the expanding atlas and animation controls into a sidebar.
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(6, 6, 6, 6);
    layout->setSpacing(6);

    auto *sizeX = new QSpinBox(this), *sizeY = new QSpinBox(this);
    m_sizeX = sizeX;
    m_sizeY = sizeY;
    sizeX->setRange(30, 256); sizeY->setRange(20, 256);
    sizeX->setValue(m_map.width); sizeY->setValue(m_map.height);
    auto *tileSize = new TilemapComboBox(this);
    m_tileSizeCombo = tileSize;
    for (int s : {8, 16, 32}) tileSize->addItem(QString::number(s) + QStringLiteral(" px"), s);
    tileSize->setCurrentIndex(qMax(0, tileSize->findData(m_map.tileSize)));
    auto *zoom = new TilemapComboBox(this);
    for (int z : {1, 2, 3, 4}) zoom->addItem(QStringLiteral("%1×").arg(z), z);
    zoom->setCurrentIndex(1);
    auto *collisionOverlay = new QCheckBox(tr("Show collisions"), this);
    collisionOverlay->setChecked(true);
    collisionOverlay->setToolTip(tr("Show or hide the collision overlay while editing either layer."));

    // Compact editing toolbar: dimensions/zoom on the first row,
    // the two independent brush choices on the second row.
    auto *form = new QHBoxLayout;
    form->addWidget(new QLabel(tr("Tiles X"), this)); form->addWidget(sizeX);
    form->addWidget(new QLabel(tr("Y"), this)); form->addWidget(sizeY);
    form->addSpacing(8);
    form->addWidget(new QLabel(tr("Tile"), this)); form->addWidget(tileSize);
    form->addWidget(new QLabel(tr("Zoom"), this)); form->addWidget(zoom);
    form->addWidget(collisionOverlay);
    form->addStretch(1);
    m_undoButton = new QPushButton(tr("Undo"), this);
    m_redoButton = new QPushButton(tr("Redo"), this);
    m_undoButton->setToolTip(tr("Undo the last tile stroke or map edit (Ctrl+Z)."));
    m_redoButton->setToolTip(tr("Redo the last undone edit (Ctrl+Y or Ctrl+Shift+Z)."));
    form->addWidget(m_undoButton);
    form->addWidget(m_redoButton);
    layout->addLayout(form);
    connect(m_undoButton, &QPushButton::clicked, this, [this]() { undoEdit(); });
    connect(m_redoButton, &QPushButton::clicked, this, [this]() { redoEdit(); });
    for (const QKeySequence &key : {QKeySequence(Qt::CTRL | Qt::Key_Z)}) {
        auto *shortcut = new QShortcut(key, this);
        shortcut->setContext(Qt::WidgetWithChildrenShortcut);
        connect(shortcut, &QShortcut::activated, this, [this]() { undoEdit(); });
    }
    for (const QKeySequence &key : {QKeySequence(Qt::CTRL | Qt::Key_Y),
                                     QKeySequence(Qt::CTRL | Qt::SHIFT | Qt::Key_Z)}) {
        auto *shortcut = new QShortcut(key, this);
        shortcut->setContext(Qt::WidgetWithChildrenShortcut);
        connect(shortcut, &QShortcut::activated, this, [this]() { redoEdit(); });
    }
    updateHistoryActions();

    // Both layers are painted with one drag. Either dropdown can opt out.
    auto *brushC = new TilemapComboBox(this);
    for (const QPair<QString, int> &type : QVector<QPair<QString,int>>{
         {tr("Don't change collision"), -1},
         {tr("0 — Empty (no collision)"), 0}, {tr("1 — Solid"), 1},
         {tr("2 — One-way"), 2}, {tr("3 — Slope rising right"), 3},
         {tr("4 — Slope falling right"), 4}, {tr("5 — Hazard"), 5},
         {tr("6 — Door"), 6}})
        brushC->addItem(type.first, type.second);
    auto *brushG = new TilemapComboBox(this);
    brushG->addItem(tr("Don't change graphic"), -1);
    brushG->addItem(tr("0 — Empty graphic"), 0);
    brushG->addItem(tr("Selected atlas tile (ID 1)"), 1);
    brushG->setCurrentIndex(2);
    m_graphicMode = brushG;
    brushG->setToolTip(tr("Click a tile in the atlas on the left to select it. "
        "Choose Don't change graphic to paint collisions only."));
    brushC->setToolTip(tr("Choose Don't change collision to paint graphics only. "
        "Otherwise both layers are painted with one stroke."));
    auto *paintRow = new QHBoxLayout;
    paintRow->addWidget(new QLabel(tr("Paint collision:"), this));
    paintRow->addWidget(brushC);
    paintRow->addSpacing(8);
    paintRow->addWidget(new QLabel(tr("Paint graphic:"), this));
    paintRow->addWidget(brushG, 1);
    layout->addLayout(paintRow);
    auto *flipRow = new QHBoxLayout;
    m_flipMode = new TilemapComboBox(this);
    m_flipMode->addItem(tr("Apply flip flags"), 1);
    m_flipMode->addItem(tr("Don't change flip flags"), -1);
    m_flipX = new QCheckBox(tr("Cell Flip X"), this);
    m_flipY = new QCheckBox(tr("Cell Flip Y"), this);
    m_stampMirrorX = new QCheckBox(tr("Mirror stamp X"), this);
    m_stampMirrorY = new QCheckBox(tr("Mirror stamp Y"), this);
    m_flipMode->setToolTip(tr("Choose whether a brush stroke changes flip flags. Choose 'Don't change' for collision-only work."));
    m_flipX->setToolTip(tr("Set horizontal flip on individual cells painted into the map or stamp editor."));
    m_flipY->setToolTip(tr("Set vertical flip on individual cells painted into the map or stamp editor."));
    m_stampMirrorX->setToolTip(tr("Mirror the entire stamp when painting: reverses cell order and toggles each cell's X flip flag."));
    m_stampMirrorY->setToolTip(tr("Mirror the entire stamp when painting: reverses cell order and toggles each cell's Y flip flag."));
    flipRow->addWidget(m_flipMode);
    flipRow->addWidget(m_flipX);
    flipRow->addWidget(m_flipY);
    flipRow->addSpacing(10);
    flipRow->addWidget(m_stampMirrorX);
    flipRow->addWidget(m_stampMirrorY);
    flipRow->addStretch();
    layout->addLayout(flipRow);

    // Adjustable atlas/animation sidebar on the left, map canvas on the right.
    m_splitter = new QSplitter(Qt::Horizontal, this);
    m_splitter->setChildrenCollapsible(false);
    auto *sidebar = new QWidget(m_splitter);
    sidebar->setMinimumWidth(250);
    auto *sideLayout = new QVBoxLayout(sidebar);
    sideLayout->setContentsMargins(4, 0, 4, 0);
    sideLayout->setSpacing(6);

    auto *atlasTitle = new QLabel(tr("Tile Atlas"), sidebar);
    QFont sectionFont = atlasTitle->font();
    sectionFont.setBold(true);
    atlasTitle->setFont(sectionFont);
    sideLayout->addWidget(atlasTitle);
    auto *atlasChoice = new TilemapComboBox(sidebar);
    m_atlasCombo = atlasChoice;
    atlasChoice->addItem(tr("No artwork (IDs only)"), QString());
    for (const auto &a : atlases) atlasChoice->addItem(a.first, a.second);
    const QString existing = QDir(m_designDirectory).absoluteFilePath(m_map.atlasPath);
    const int selected = atlasChoice->findData(existing);
    if (selected >= 0) atlasChoice->setCurrentIndex(selected);
    else if (!m_map.atlasPath.isEmpty()) {
        atlasChoice->addItem(tr("Missing: %1").arg(m_map.atlasPath), existing);
        atlasChoice->setCurrentIndex(atlasChoice->count()-1);
    }
    sideLayout->addWidget(atlasChoice);

    // The atlas receives the spare vertical space. Even very long sheets
    // remain scrollable without shrinking the game canvas to a thin strip.
    auto *tilePickerArea = new QScrollArea(sidebar);
    tilePickerArea->setWidgetResizable(false);
    tilePickerArea->setMinimumHeight(120);
    m_atlasPicker = new QLabel(tilePickerArea);
    m_atlasPicker->setText(tr("Choose a PPB tile sheet above, then click a tile here."));
    m_atlasPicker->setToolTip(tr("Click a tile to select it for graphic painting. "
        "The yellow outline shows the selected tile."));
    m_atlasPicker->installEventFilter(this);
    tilePickerArea->setWidget(m_atlasPicker);
    sideLayout->addWidget(tilePickerArea, 1);

    // Animation definitions are separate from both maps. Selecting an
    // atlas tile edits ONE shared animation, never the pixels or collision.
    auto *animationTitle = new QLabel(tr("Selected Tile Animation"), sidebar);
    animationTitle->setFont(sectionFont);
    sideLayout->addWidget(animationTitle);

    auto *previewRow = new QHBoxLayout;
    m_animationPreview = new QLabel(sidebar);
    m_animationPreview->setFixedSize(72, 72);
    m_animationPreview->setAlignment(Qt::AlignCenter);
    m_animationPreview->setToolTip(tr("Live preview of the selected tile, at 50 game frames/sec."));
    previewRow->addWidget(m_animationPreview);
    m_animationStatus = new QLabel(sidebar);
    m_animationStatus->setWordWrap(true);
    previewRow->addWidget(m_animationStatus, 1);
    sideLayout->addLayout(previewRow);

    auto *animationValues = new QHBoxLayout;
    m_animFrames = new QSpinBox(sidebar);
    m_animFrames->setRange(1, 16);
    m_animFrames->setValue(4);
    m_animFrames->setToolTip(tr("Number of consecutive atlas cells to play, starting from the selected tile."));
    m_animDelay = new QSpinBox(sidebar);
    m_animDelay->setRange(1, 255);
    m_animDelay->setValue(5);
    m_animDelay->setToolTip(tr("How many VBlanks to hold each frame (50 VBlanks is about one second at 50 FPS)."));
    animationValues->addWidget(new QLabel(tr("Frames"), sidebar));
    animationValues->addWidget(m_animFrames);
    animationValues->addWidget(new QLabel(tr("VBlanks/frame"), sidebar));
    animationValues->addWidget(m_animDelay);
    sideLayout->addLayout(animationValues);

    auto *animationOptions = new QHBoxLayout;
    m_animLoop = new QCheckBox(tr("Loop"), sidebar);
    m_animLoop->setChecked(true);
    m_animBounce = new QCheckBox(tr("Ping-pong"), sidebar);
    animationOptions->addWidget(m_animLoop);
    animationOptions->addWidget(m_animBounce);
    animationOptions->addStretch(1);
    sideLayout->addLayout(animationOptions);

    auto *setAnimation = new QPushButton(tr("Set Animation"), sidebar);
    m_removeAnimation = new QPushButton(tr("Remove Animation"), sidebar);
    setAnimation->setToolTip(tr("Save animation properties for the selected atlas tile."));
    m_removeAnimation->setToolTip(tr("Turn the selected tile back into an ordinary static graphic."));
    auto *buttonRow = new QHBoxLayout;
    buttonRow->addWidget(setAnimation);
    buttonRow->addWidget(m_removeAnimation);
    sideLayout->addLayout(buttonRow);

    m_canvas = new Canvas(m_splitter);
    m_canvas->setMinimumWidth(300);
    m_canvas->map = &m_map;
    m_canvas->atlas = &m_atlas;
    m_canvas->strokeStarted = [this]() { m_strokeStart = m_map; };
    m_canvas->strokeFinished = [this]() { recordChange(m_strokeStart); };
    // Stamp sidebar: upper bank of thumbnails + lower editable stamp grid.
    auto *stampSidebar = new QSplitter(Qt::Vertical, m_splitter);
    stampSidebar->setChildrenCollapsible(false);
    stampSidebar->setMinimumWidth(250);
    auto *bankPane = new QWidget(stampSidebar);
    auto *bankLayout = new QVBoxLayout(bankPane);
    bankLayout->setContentsMargins(4, 0, 4, 4);
    auto *bankTitle = new QLabel(tr("Stamp Bank"), bankPane);
    bankTitle->setFont(sectionFont);
    bankLayout->addWidget(bankTitle);
    m_stampList = new QListWidget(bankPane);
    m_stampList->setViewMode(QListView::IconMode);
    m_stampList->setResizeMode(QListView::Adjust);
    m_stampList->setMovement(QListView::Static);
    m_stampList->setWrapping(true);
    m_stampList->setIconSize(QSize(104, 76));
    m_stampList->setGridSize(QSize(124, 116));
    m_stampList->setWordWrap(true);
    m_stampList->setSpacing(2);
    m_stampList->setToolTip(tr("Click a stamp to select it as the painting brush. "
                                   "Click an atlas tile on the left to return to single-tile painting."));
    bankLayout->addWidget(m_stampList, 1);
    m_stampStatus = new QLabel(tr("Brush: atlas tile"), bankPane);
    m_stampStatus->setWordWrap(true);
    bankLayout->addWidget(m_stampStatus);
    auto *stampButtons = new QHBoxLayout;
    auto *addStamp = new QPushButton(tr("Add"), bankPane);
    auto *removeStamp = new QPushButton(tr("Remove"), bankPane);
    stampButtons->addWidget(addStamp);
    stampButtons->addWidget(removeStamp);
    bankLayout->addLayout(stampButtons);

    auto *editPane = new QWidget(stampSidebar);
    auto *editLayout = new QVBoxLayout(editPane);
    editLayout->setContentsMargins(4, 4, 4, 0);
    auto *editTitle = new QLabel(tr("Stamp Editor"), editPane);
    editTitle->setFont(sectionFont);
    editLayout->addWidget(editTitle);
    m_stampName = new QLineEdit(editPane);
    m_stampName->setMaxLength(80);
    m_stampName->setPlaceholderText(tr("Stamp name"));
    editLayout->addWidget(m_stampName);
    auto *stampSizeRow = new QHBoxLayout;
    m_stampWidth = new QSpinBox(editPane);
    m_stampHeight = new QSpinBox(editPane);
    m_stampWidth->setRange(1, 16);
    m_stampHeight->setRange(1, 16);
    stampSizeRow->addWidget(new QLabel(tr("Width"), editPane));
    stampSizeRow->addWidget(m_stampWidth);
    stampSizeRow->addWidget(new QLabel(tr("Height"), editPane));
    stampSizeRow->addWidget(m_stampHeight);
    editLayout->addLayout(stampSizeRow);
    auto *stampScroll = new QScrollArea(editPane);
    stampScroll->setWidgetResizable(false);
    m_stampCanvas = new StampCanvas(stampScroll);
    m_stampCanvas->map = &m_map;
    m_stampCanvas->atlas = &m_atlas;
    stampScroll->setWidget(m_stampCanvas);
    editLayout->addWidget(stampScroll, 1);
    auto *stampHint = new QLabel(tr("Atlas tile + left-click: paint one stamp cell. "
        "Right-click: clear cell. Use Paint collision and Cell Flip X/Y for each cell. "
        "Choose a stamp above to paint it onto the map."), editPane);
    stampHint->setWordWrap(true);
    editLayout->addWidget(stampHint);
    stampSidebar->addWidget(bankPane);
    stampSidebar->addWidget(editPane);
    stampSidebar->setStretchFactor(0, 1);
    stampSidebar->setStretchFactor(1, 1);
    stampSidebar->setSizes({300, 300});

    m_splitter->addWidget(sidebar);
    m_splitter->addWidget(m_canvas);
    m_splitter->addWidget(stampSidebar);
    m_splitter->setStretchFactor(0, 0);
    m_splitter->setStretchFactor(1, 1);
    m_splitter->setStretchFactor(2, 0);
    const QByteArray savedSplit = windowSettings.value(
        QStringLiteral("GameTilemapEditor/splitter")).toByteArray();
    if (savedSplit.isEmpty() || !m_splitter->restoreState(savedSplit))
        m_splitter->setSizes({300, 760, 300});
    layout->addWidget(m_splitter, 1);

    auto *help = new QLabel(tr("HOVER previews the actual tile or stamp footprint  |  LEFT-DRAG paints atlas tile or selected stamp (stamp drags snap to the first-click stamp grid)  |  RIGHT-DRAG erases  |  "
        "MIDDLE-DRAG or ALT+LEFT-DRAG pans  |  WHEEL scrolls one tile. "
        "CTRL+Z undoes one stroke; CTRL+Y / CTRL+SHIFT+Z redoes. "
        "Pick artwork on the left; 'Don't change' leaves that layer untouched."), this);
    help->setWordWrap(true);
    layout->addWidget(help);
    // Keep the buttons in this exact order regardless of the desktop style.
    auto *buttons = new QHBoxLayout;
    m_saveStatus = new QLabel(this);
    m_saveStatus->setText(QString());
    buttons->addWidget(m_saveStatus, 1);
    m_saveButton = new QPushButton(tr("Save"), this);
    m_saveButton->setToolTip(tr("Save the current tilemap and stamp edits to the game design without closing this editor."));
    m_saveButton->setEnabled(false); // Enabled once the owning Game Designer supplies a commit callback.
    auto *apply = new QPushButton(tr("Apply to Design"), this);
    auto *cancel = new QPushButton(tr("Cancel"), this);
    buttons->addWidget(m_saveButton);
    buttons->addWidget(apply);
    buttons->addWidget(cancel);
    layout->addLayout(buttons);
    connect(m_saveButton, &QPushButton::clicked, this, [this]() {
        if (!m_saveCallback) return;
        if (m_canvas && m_canvas->painting) return;
        if (m_saveCallback(m_map)) {
            m_saveStatus->setText(tr("Saved to game design"));
        } else {
            m_saveStatus->setText(tr("Save failed — changes remain in editor"));
        }
    });
    connect(apply, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancel, &QPushButton::clicked, this, &QDialog::reject);
    connect(m_stampList, &QListWidget::itemClicked, this,
        [this](QListWidgetItem *item) { selectStamp(m_stampList->row(item)); });
    connect(m_stampList, &QListWidget::currentRowChanged, this,
        [this](int row) { selectStamp(row); });
    connect(addStamp, &QPushButton::clicked, this, [this]() {
        if (m_map.stamps.size() >= 128) {
            QMessageBox::warning(this, tr("Stamps"), tr("Maximum of 128 stamps reached."));
            return;
        }
        const SidboxTilemap before = m_map;
        SidboxTileStamp stamp;
        stamp.name = tr("Stamp %1").arg(m_map.stamps.size() + 1);
        stamp.tileSize = m_map.tileSize;
        m_map.stamps.append(stamp);
        recordChange(before);
        updateStampList(m_map.stamps.size() - 1);
        selectStamp(m_map.stamps.size() - 1);
    });
    connect(removeStamp, &QPushButton::clicked, this, [this]() {
        const int row = m_stampList->currentRow();
        if (row < 0 || row >= m_map.stamps.size()) return;
        const SidboxTilemap before = m_map;
        m_map.stamps.removeAt(row);
        recordChange(before);
        updateStampList(m_map.stamps.isEmpty() ? -1 : qMin(row, int(m_map.stamps.size()) - 1));
        selectStamp(m_stampList->currentRow());
    });
    connect(m_stampName, &QLineEdit::editingFinished, this, [this]() {
        const int row = m_stampList->currentRow();
        if (row < 0 || row >= m_map.stamps.size()) return;
        const QString name = m_stampName->text().trimmed();
        if (name.isEmpty()) { updateStampEditor(); return; }
        const SidboxTilemap before = m_map;
        m_map.stamps[row].name = name;
        recordChange(before);
        updateStampList(row);
    });
    connect(m_stampWidth, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int width) {
            const int row = m_stampList->currentRow();
            if (row < 0 || row >= m_map.stamps.size()) return;
            const SidboxTilemap before = m_map;
            m_map.stamps[row].resizeStamp(width, m_map.stamps[row].height);
            recordChange(before);
            m_stampCanvas->refresh();
            updateStampList(row);
        });
    connect(m_stampHeight, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int height) {
            const int row = m_stampList->currentRow();
            if (row < 0 || row >= m_map.stamps.size()) return;
            const SidboxTilemap before = m_map;
            m_map.stamps[row].resizeStamp(m_map.stamps[row].width, height);
            recordChange(before);
            m_stampCanvas->refresh();
            updateStampList(row);
        });
    m_stampCanvas->modified = [this]() {
        // Snapshot is captured immediately before the press in StampCanvas.
        // The editor also supports undo for each single-cell modification.
        recordChange(m_strokeStart);
        updateStampList(m_stampList->currentRow());
    };
    m_stampCanvas->strokeStarted = [this]() { m_strokeStart = m_map; };
    updateStampList(-1);

    connect(sizeX, qOverload<int>(&QSpinBox::valueChanged), this, [this](int v) {
        const SidboxTilemap before = m_map;
        m_map.resizeMap(v, m_map.height); m_canvas->adjust();
        recordChange(before);
    });
    connect(sizeY, qOverload<int>(&QSpinBox::valueChanged), this, [this](int v) {
        const SidboxTilemap before = m_map;
        m_map.resizeMap(m_map.width, v); m_canvas->adjust();
        recordChange(before);
    });
    connect(tileSize, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, tileSize](int) {
            const SidboxTilemap before = m_map;
            m_map.tileSize = tileSize->currentData().toInt();
            m_canvas->adjust(); updateAtlasPicker(); updateAnimationControls();
            updateStampEditor(); updateStampList();
            recordChange(before);
        });
    connect(atlasChoice, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, atlasChoice](int) {
            const SidboxTilemap before = m_map;
            setAtlas(atlasChoice->currentData().toString());
            recordChange(before);
        });
    connect(brushG, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, brushG](int) {
            m_canvas->graphicMode = brushG->currentData().toInt();
            m_stampCanvas->graphicMode = m_canvas->graphicMode;
            m_canvas->viewport()->update();
            m_stampCanvas->update();
        });
    connect(m_flipMode, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this](int) {
            const int mode = m_flipMode->currentData().toInt();
            m_canvas->flipMode = mode;
            m_stampCanvas->flipMode = mode;
            m_canvas->viewport()->update();
            m_stampCanvas->update();
        });
    auto updateFlipBrush = [this]() {
        const quint8 flags = quint8((m_flipX->isChecked() ? 1 : 0) |
                                   (m_flipY->isChecked() ? 2 : 0));
        m_canvas->flipBrush = flags;
        m_stampCanvas->flipBrush = flags;
        m_canvas->viewport()->update();
        m_stampCanvas->update();
    };
    connect(m_flipX, &QCheckBox::toggled, this, [updateFlipBrush](bool) { updateFlipBrush(); });
    connect(m_flipY, &QCheckBox::toggled, this, [updateFlipBrush](bool) { updateFlipBrush(); });
    auto updateStampMirror = [this]() {
        m_canvas->stampMirror = quint8((m_stampMirrorX->isChecked() ? 1 : 0) |
                                              (m_stampMirrorY->isChecked() ? 2 : 0));
        m_canvas->viewport()->update();
    };
    connect(m_stampMirrorX, &QCheckBox::toggled, this, [updateStampMirror](bool) { updateStampMirror(); });
    connect(m_stampMirrorY, &QCheckBox::toggled, this, [updateStampMirror](bool) { updateStampMirror(); });
    connect(brushC, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, brushC](int) {
            m_canvas->collisionBrush = brushC->currentData().toInt();
            m_stampCanvas->collisionBrush = m_canvas->collisionBrush;
            m_canvas->viewport()->update();
            m_stampCanvas->update();
        });
    connect(collisionOverlay, &QCheckBox::toggled, this,
        [this](bool enabled) {
            m_canvas->showCollisions = enabled;
            m_canvas->viewport()->update();
        });
    connect(zoom, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, zoom](int) { m_canvas->zoom = zoom->currentData().toInt(); m_canvas->adjust(); });
    connect(setAnimation, &QPushButton::clicked, this,
        [this]() { saveSelectedAnimation(); });
    connect(m_removeAnimation, &QPushButton::clicked, this,
        [this]() { removeSelectedAnimation(); });
    connect(m_animFrames, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int) { updateAnimationPreview(); });
    connect(m_animDelay, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int) { updateAnimationPreview(); });
    connect(m_animLoop, &QCheckBox::toggled, this,
        [this](bool) { updateAnimationPreview(); });
    connect(m_animBounce, &QCheckBox::toggled, this,
        [this](bool) { updateAnimationPreview(); });
    setAtlas(atlasChoice->currentData().toString());
    m_canvas->adjust();
    updateStampList();
    m_animationClock.start();
    m_animationTimer = new QTimer(this);
    m_animationTimer->setInterval(40); // sample at 25fps, timing remains 50Hz
    connect(m_animationTimer, &QTimer::timeout, this, [this]() {
        if (!isVisible()) return;
        m_canvas->refreshAnimated(m_animationClock.elapsed() / 20);
        updateAnimationPreview();
    });
    m_animationTimer->start();
}

void SidboxTilemapEditor::setAtlas(const QString &absolutePath)
{
    m_map.atlasPath = absolutePath.isEmpty() ? QString()
        : QDir(m_designDirectory).relativeFilePath(absolutePath);
    m_atlas = QImage();
    if (!absolutePath.isEmpty()) {
        SidboxPpb::Picture picture;
        QString error;
        if (SidboxPpb::read(absolutePath, &picture, &error)) m_atlas = picture.indexed;
        else QMessageBox::warning(this, tr("Tile Artwork"), error);
    }
    if (m_canvas) m_canvas->graphicBrush = 1;
    if (m_stampCanvas) m_stampCanvas->graphicBrush = 1;
    updateAtlasPicker();
    updateAnimationControls();
    if (m_canvas) m_canvas->viewport()->update();
    updateStampList();
    if (m_stampCanvas) m_stampCanvas->update();
}

void SidboxTilemapEditor::updateStampList(int wantedRow)
{
    if (!m_stampList) return;
    if (wantedRow == -2) wantedRow = m_stampList->currentRow();
    const QSignalBlocker block(m_stampList);
    m_stampList->clear();
    for (const SidboxTileStamp &stamp : m_map.stamps) {
        QPixmap preview(104, 76);
        preview.fill(QColor(28, 37, 49));
        QPainter painter(&preview);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
        const int unit = qMax(2, qMin(104 / stamp.width, 76 / stamp.height));
        const int ox = (104 - stamp.width * unit) / 2;
        const int oy = (76 - stamp.height * unit) / 2;
        const int cols = m_atlas.isNull() ? 0 : m_atlas.width() / stamp.tileSize;
        const int rows = m_atlas.isNull() ? 0 : m_atlas.height() / stamp.tileSize;
        for (int y = 0; y < stamp.height; ++y)
            for (int x = 0; x < stamp.width; ++x) {
                const int i = y * stamp.width + x;
                const int graphic = mapGraphic(stamp.graphics, i);
                const QRect dest(ox + x * unit, oy + y * unit, unit, unit);
                if (graphic && cols && graphic <= cols * rows) {
                    const int n = graphic - 1;
                    const QImage tileImage = m_atlas.copy((n % cols) * stamp.tileSize,
                                      (n / cols) * stamp.tileSize, stamp.tileSize, stamp.tileSize);
                    const quint8 flip = quint8(stamp.flips.at(i));
                    painter.drawImage(dest, flip ? tileImage.mirrored(bool(flip & 1), bool(flip & 2)) : tileImage);
                } else if (graphic) painter.fillRect(dest, QColor(90, 97, 111));
                if (quint8(stamp.collisions.at(i)))
                    painter.fillRect(dest, QColor(65, 170, 224, 70));
                painter.setPen(QColor(140, 160, 180, 80));
                painter.drawRect(dest.adjusted(0, 0, -1, -1));
            }
        auto *item = new QListWidgetItem(QIcon(preview), stamp.name);
        item->setToolTip(tr("%1 — %2 × %3 tiles (%4 px per tile)")
            .arg(stamp.name).arg(stamp.width).arg(stamp.height).arg(stamp.tileSize));
        m_stampList->addItem(item);
    }
    m_stampList->setCurrentRow(wantedRow >= 0 && wantedRow < m_map.stamps.size() ? wantedRow : -1);
    if (m_canvas && m_canvas->stampIndex >= 0 &&
        (m_canvas->stampIndex >= m_map.stamps.size() ||
         m_map.stamps.at(m_canvas->stampIndex).tileSize != m_map.tileSize)) {
        m_canvas->stampIndex = -1;
        if (m_stampStatus) m_stampStatus->setText(tr("Brush: atlas tile"));
    }
    updateStampEditor();
}

void SidboxTilemapEditor::updateStampEditor()
{
    if (!m_stampCanvas || !m_stampList) return;
    const int row = m_stampList->currentRow();
    const bool valid = row >= 0 && row < m_map.stamps.size();
    m_stampName->setEnabled(valid);
    m_stampWidth->setEnabled(valid);
    m_stampHeight->setEnabled(valid);
    {
        const QSignalBlocker nameBlock(m_stampName);
        const QSignalBlocker widthBlock(m_stampWidth);
        const QSignalBlocker heightBlock(m_stampHeight);
        m_stampName->setText(valid ? m_map.stamps.at(row).name : QString());
        m_stampWidth->setValue(valid ? m_map.stamps.at(row).width : 2);
        m_stampHeight->setValue(valid ? m_map.stamps.at(row).height : 2);
    }
    m_stampCanvas->selected = row;
    m_stampCanvas->refresh();
}

void SidboxTilemapEditor::selectStamp(int row)
{
    if (!m_stampList) return;
    if (row < 0 || row >= m_map.stamps.size()) {
        if (m_canvas) m_canvas->stampIndex = -1;
    } else {
        const bool compatible = m_map.stamps.at(row).tileSize == m_map.tileSize;
        if (m_canvas) m_canvas->stampIndex = compatible ? row : -1;
        // Never silently reinterpret a stamp built with another atlas grid.
        // A status message below explains why it cannot paint this map.
    }
    if (m_stampStatus) {
        m_stampStatus->setText(m_canvas && m_canvas->stampIndex >= 0 &&
            m_canvas->stampIndex < m_map.stamps.size()
            ? tr("Brush: stamp '%1'").arg(m_map.stamps.at(m_canvas->stampIndex).name)
            : (row >= 0 && row < m_map.stamps.size() &&
               m_map.stamps.at(row).tileSize != m_map.tileSize
                ? tr("Stamp uses %1px cells; map uses %2px. Cannot paint.")
                    .arg(m_map.stamps.at(row).tileSize).arg(m_map.tileSize)
                : tr("Brush: atlas tile")));
    }
    updateStampEditor();
    if (m_canvas) m_canvas->viewport()->update();
}

void SidboxTilemapEditor::updateAtlasPicker()
{
    if (!m_atlasPicker || !m_canvas) return;
    if (m_atlas.isNull()) {
        m_atlasPicker->setPixmap(QPixmap());
        m_atlasPicker->setText(tr("No PPB tile sheet selected (IDs only)."));
        m_atlasPicker->adjustSize();
    } else {
        // A two-times enlargement keeps nearest-neighbour pixel art crisp.
        QPixmap display = QPixmap::fromImage(m_atlas).scaled(
            m_atlas.width() * 2, m_atlas.height() * 2,
            Qt::IgnoreAspectRatio, Qt::FastTransformation);
        const int cols = m_atlas.width() / m_map.tileSize;
        const int rows = m_atlas.height() / m_map.tileSize;
        const int selected = m_canvas->graphicBrush - 1;
        if (cols > 0 && rows > 0 && selected >= 0 && selected < cols * rows) {
            QPainter painter(&display);
            QPen outline(QColor(255, 217, 65));
            outline.setWidth(2);
            painter.setPen(outline);
            const int px = m_map.tileSize * 2;
            painter.drawRect(QRect((selected % cols) * px, (selected / cols) * px,
                                   px, px).adjusted(1, 1, -2, -2));
        }
        m_atlasPicker->setPixmap(display);
        m_atlasPicker->adjustSize();
    }
    if (m_canvas) m_canvas->viewport()->update();
    if (m_stampCanvas) m_stampCanvas->update();
    if (m_graphicMode) {
        m_graphicMode->setItemText(2,
            tr("Selected atlas tile (ID %1)").arg(m_canvas->graphicBrush));
    }
}

void SidboxTilemapEditor::updateAnimationControls()
{
    if (!m_animFrames || !m_canvas) return;
    const int id = m_canvas->graphicBrush;
    const int cols = m_atlas.isNull() ? 0 : m_atlas.width()/m_map.tileSize;
    const int rows = m_atlas.isNull() ? 0 : m_atlas.height()/m_map.tileSize;
    const int count = int(qMin(qint64(65535), qint64(cols)*rows));
    const bool valid = id > 0 && id <= count;
    const SidboxTileAnimation *anim = findTileAnimation(m_map, id);
    m_animFrames->setMaximum(qMax(1, qMin(16, count - id + 1)));
    m_animFrames->setValue(anim ? anim->frames : qMin(4, m_animFrames->maximum()));
    m_animDelay->setValue(anim ? anim->frameTicks : 5);
    m_animLoop->setChecked(anim ? anim->loop : true);
    m_animBounce->setChecked(anim ? anim->bounce : false);
    m_removeAnimation->setEnabled(anim != nullptr);
    if (m_animationStatus) {
        m_animationStatus->setText(!valid ?
            tr("Choose a tile from the atlas to define its animation.") :
            anim ? tr("Tile %1: animated (%2 frames). Changes apply to every cell painted with ID %1.")
                  .arg(id).arg(anim->frames) :
            tr("Tile %1: static. Choose settings and press Set Animation. Frames must be consecutive in the atlas.").arg(id));
    }
    updateAnimationPreview();
}

void SidboxTilemapEditor::updateAnimationPreview()
{
    if (!m_animationPreview || !m_canvas || m_atlas.isNull()) return;
    const int id = m_canvas->graphicBrush;
    const int cols = m_atlas.width()/m_map.tileSize;
    const int rows = m_atlas.height()/m_map.tileSize;
    if (!cols || id < 1 || id > int(qMin(qint64(65535), qint64(cols)*rows))) {
        m_animationPreview->clear();
        return;
    }
    SidboxTileAnimation current;
    if (const SidboxTileAnimation *saved = findTileAnimation(m_map, id)) current = *saved;
    else {
        current.graphicId = id;
        current.frames = 1;
    }
    // Show the SAVED animation, not unsaved edits in the property widgets.
    const int frameId = id + tileAnimationFrame(current,
        m_animationClock.isValid() ? m_animationClock.elapsed()/20 : 0);
    const QRect source(((frameId-1)%cols)*m_map.tileSize,
                       ((frameId-1)/cols)*m_map.tileSize,
                       m_map.tileSize, m_map.tileSize);
    m_animationPreview->setPixmap(QPixmap::fromImage(m_atlas.copy(source)).scaled(
        64, 64, Qt::KeepAspectRatio, Qt::FastTransformation));
}

void SidboxTilemapEditor::saveSelectedAnimation()
{
    if (!m_canvas || m_atlas.isNull()) return;
    const int id = m_canvas->graphicBrush;
    const int cols = m_atlas.width()/m_map.tileSize;
    const int rows = m_atlas.height()/m_map.tileSize;
    if (!cols || id < 1 || id > int(qMin(qint64(65535), qint64(cols)*rows))) {
        QMessageBox::warning(this, tr("Tile Animation"), tr("Select a valid atlas tile first."));
        return;
    }
    SidboxTileAnimation a;
    a.graphicId = id;
    a.frames = m_animFrames->value();
    a.frameTicks = m_animDelay->value();
    a.loop = m_animLoop->isChecked();
    a.bounce = m_animBounce->isChecked();
    if (a.graphicId+a.frames-1 > int(qMin(qint64(65535), qint64(cols)*rows))) {
        QMessageBox::warning(this, tr("Tile Animation"),
            tr("The selected frame range goes past the end of the atlas."));
        return;
    }
    const SidboxTilemap before = m_map;
    bool updated = false;
    for (SidboxTileAnimation &entry : m_map.animations)
        if (entry.graphicId == id) { entry = a; updated = true; break; }
    if (!updated) m_map.animations.append(a);
    recordChange(before);
    updateAnimationControls();
    m_canvas->viewport()->update();
}

void SidboxTilemapEditor::removeSelectedAnimation()
{
    if (!m_canvas) return;
    const int id = m_canvas->graphicBrush;
    const SidboxTilemap before = m_map;
    for (int i = 0; i < m_map.animations.size(); ++i)
        if (m_map.animations.at(i).graphicId == id) {
            m_map.animations.removeAt(i);
            break;
        }
    recordChange(before);
    updateAnimationControls();
    m_canvas->viewport()->update();
}

void SidboxTilemapEditor::done(int result)
{
    // Save for Apply and Cancel alike: window state is a user preference,
    // not a tilemap edit. saveGeometry includes the maximised state.
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.setValue(QStringLiteral("GameTilemapEditor/geometry"), saveGeometry());
    if (m_splitter)
        settings.setValue(QStringLiteral("GameTilemapEditor/splitter"), m_splitter->saveState());
    QDialog::done(result);
}

bool SidboxTilemapEditor::eventFilter(QObject *target, QEvent *event)
{
    if (target == m_atlasPicker && event->type() == QEvent::MouseButtonPress &&
        !m_atlas.isNull() && m_graphicMode) {
        const auto *mouse = static_cast<QMouseEvent *>(event);
        if (mouse->button() == Qt::LeftButton) {
            const int cols = m_atlas.width() / m_map.tileSize;
            const int rows = m_atlas.height() / m_map.tileSize;
            const int tx = int(mouse->position().x()) / (2*m_map.tileSize);
            const int ty = int(mouse->position().y()) / (2*m_map.tileSize);
            if (cols && tx >= 0 && tx < cols && ty >= 0 && ty < rows) {
                const int id = ty*cols+tx+1;
                if (id <= 65535) {
                    m_canvas->graphicBrush = id;
                    m_canvas->stampIndex = -1;
                    m_canvas->viewport()->update();
                    if (m_stampStatus) m_stampStatus->setText(tr("Brush: atlas tile %1").arg(id));
                    if (m_stampCanvas) m_stampCanvas->graphicBrush = id;
                    m_graphicMode->setCurrentIndex(2);
                    updateAtlasPicker();
                    updateAnimationControls();
                }
            }
            return true;
        }
    }
    return QDialog::eventFilter(target, event);
}

bool sidboxExportTilemap(const SidboxTilemap &map, const QString &designDirectory,
                         QString *error, bool externalMap)
{
    if (map.width < 30 || map.width > 256 || map.height < 20 || map.height > 256 ||
        (map.tileSize != 8 && map.tileSize != 16 && map.tileSize != 32) ||
        map.graphics.size() != map.width * map.height * 2 ||
        map.collisions.size() != map.width * map.height ||
        map.flips.size() != map.width * map.height) {
        if (error) *error = QStringLiteral("Invalid tilemap dimensions or data.");
        return false;
    }
    // Optional tile atlas is a normal indexed PPB sprite sheet, with each
    // graphic ID 1..65535 referring to successive tile-sized cells.
    unsigned tileCount = 0;
    int atlasWidth = 0, atlasHeight = 0;
    quint32 atlasHash = 2166136261u; /* FNV-1a over indexed pixel rows. */
    if (!map.atlasPath.isEmpty()) {
        SidboxPpb::Picture picture;
        if (!SidboxPpb::read(QDir(designDirectory).absoluteFilePath(map.atlasPath), &picture, error))
            return false;
        const QImage &image = picture.indexed;
        if (image.width() % map.tileSize || image.height() % map.tileSize) {
            if (error) *error = QStringLiteral("Tile artwork dimensions must be multiples of %1 pixels.").arg(map.tileSize);
            return false;
        }
        atlasWidth = image.width();
        atlasHeight = image.height();
        const int cols = image.width() / map.tileSize, rows = image.height() / map.tileSize;
        if (qint64(cols) * rows > 65535) {
            if (error) *error = QStringLiteral("Atlas contains more than 65535 tiles (maximum graphic ID is 65535).");
            return false;
        }
        tileCount = unsigned(cols * rows);
        for (int y = 0; y < image.height(); ++y) {
            const uchar *line = image.constScanLine(y);
            for (int x = 0; x < image.width(); ++x) {
                atlasHash ^= line[x];
                atlasHash *= 16777619u;
            }
        }
        // SIDBOX has finite SDRAM. The atlas is loaded into RAM once at startup.
        if (qint64(tileCount) * map.tileSize * map.tileSize > 4 * 1024 * 1024) {
            if (error) *error = QStringLiteral("Atlas exceeds the current 4 MiB SDRAM budget. Use a smaller sheet or multiple levels.");
            return false;
        }
    }
    for (char flags : map.flips) {
        if (quint8(flags) & ~quint8(3)) {
            if (error) *error = QStringLiteral("Invalid cell flip flags (only X/Y supported).");
            return false;
        }
    }
    // An assigned tile must exist in the selected atlas; ID 0 is blank.
    for (int i = 0, n = map.width * map.height; i < n; ++i) {
        if (mapGraphic(map.graphics, i) > tileCount) {
            if (error) *error = QStringLiteral("The map uses graphic ID %1, but the atlas has only %2 tiles.")
                .arg(mapGraphic(map.graphics, i)).arg(tileCount);
            return false;
        }
    }
    QSet<int> seenAnimated;
    for (const SidboxTileAnimation &a : map.animations) {
        if (a.graphicId < 1 || a.graphicId > 65535 || a.frames < 1 || a.frames > 16 ||
            a.frameTicks < 1 || a.frameTicks > 255 || seenAnimated.contains(a.graphicId) ||
            a.graphicId + a.frames - 1 > int(tileCount)) {
            if (error) *error = QStringLiteral(
                "Animated tile %1 uses frames outside the available atlas (or has invalid settings).")
                .arg(a.graphicId);
            return false;
        }
        seenAnimated.insert(a.graphicId);
    }
    const QString folder = QDir(designDirectory).filePath(QStringLiteral("gamelevels"));
    if (!QDir().mkpath(folder)) {
        if (error) *error = QStringLiteral("Cannot create gamelevels directory.");
        return false;
    }
    QByteArray header =
        "#ifndef SIDBOX_GAME_LEVEL1_H\n#define SIDBOX_GAME_LEVEL1_H\n"
        "#include <stdint.h>\n#include \"../gamehelpers/gametilemap.h\"\n\n"
        "uint8_t game_level1_load_map(const char *filename);\n"
        "void game_level1_unload_map(void);\n"
        "uint8_t game_level1_load_atlas(void);\n"
        "void game_level1_unload_atlas(void);\n"
        "extern game_tilemap_t game_level1;\n"
        "#endif\n";
    if (!externalMap) header.replace("extern game_tilemap_t game_level1;",
        "extern const uint16_t game_level1_graphics[];\n"
        "extern const uint8_t game_level1_collisions[];\n"
        "extern const uint8_t game_level1_flips[];\n"
        "extern const game_tile_animation_t game_level1_animations[];\n"
        "extern game_tilemap_t game_level1;");
    QByteArray source = "#include \"level1.h\"\n"
        "/* Optional sprite PPB sharing. Standalone tilemaps still work. */\n"
        "#if defined(__has_include)\n"
        "# if __has_include(\"../gameassets/gameassets.h\")\n"
        "#  include \"../gameassets/gameassets.h\"\n"
        "# endif\n"
        "#endif\n\n";
    if (!externalMap) {
        source += "/* Embedded graphics and collision arrays: no SD map file needed. */\n";
    auto writeBytes = [&source](const QByteArray &data, const QByteArray &name) {
        source += "const uint8_t " + name + "[] __attribute__((aligned(32))) = {\n";
        for (int i = 0; i < data.size(); ++i) {
            if (i % 20 == 0) source += "    ";
            source += QByteArray::number(quint8(data.at(i)));
            if (i != data.size() - 1) source += ",";
            if (i % 20 == 19 || i == data.size() - 1) source += "\n";
            else source += " ";
        }
        source += "};\n\n";
    };
    source += "const uint16_t game_level1_graphics[] __attribute__((aligned(32))) = {\n";
    for (int i = 0, n = map.width * map.height; i < n; ++i) {
        if (i % 16 == 0) source += "    ";
        source += QByteArray::number(mapGraphic(map.graphics, i));
        if (i != n - 1) source += ",";
        if (i % 16 == 15 || i == n - 1) source += "\n";
        else source += " ";
    }
    source += "};\n\n";
    writeBytes(map.collisions, "game_level1_collisions");
    writeBytes(map.flips, "game_level1_flips");
    }
    if (!externalMap) {

    source += "const game_tile_animation_t game_level1_animations[] = {\n";
    if (map.animations.isEmpty()) source += "    {0, 0, 0, 0} // No animations yet\n";
    else {
        for (const SidboxTileAnimation &a : map.animations) {
            const int flags = (a.loop ? 1 : 0) | (a.bounce ? 2 : 0);
            source += QByteArray("    {") + QByteArray::number(a.graphicId) + ", " +
                QByteArray::number(a.frames) + ", " + QByteArray::number(a.frameTicks) +
                ", " + QByteArray::number(flags) + "},\n";
        }
    }
    source += "};\n\n";
    }
    source += "game_tilemap_t game_level1 = {\n";
    source += externalMap ? "    0, 0, 0,\n" : "    game_level1_graphics, game_level1_collisions, 0,\n";
    source += QByteArray("    ") + QByteArray::number(map.width) + ", " + QByteArray::number(map.height)
        + ", " + QByteArray::number(map.tileSize) + ", " + QByteArray::number(tileCount) + ",\n"
        + (externalMap || map.animations.isEmpty() ? QByteArray("    0, 0") :
            QByteArray("    game_level1_animations, ") + QByteArray::number(map.animations.size()))
        + ",\n    0, 0, 0, /* atlas width, height, borrowed flag */\n"
        + "    0, " + (externalMap ? QByteArray("0 /* SD flips loaded later */") : QByteArray("game_level1_flips"))
        + "\n};\n\n";
    if (externalMap) {
        source += "/* SD map v2: file includes graphics, collisions, per-cell flips and animations. */\n"
                  "uint8_t game_level1_load_map(const char *filename)\n" 
                  "{ return game_tilemap_load_map(&game_level1, filename); }\n"
                  "void game_level1_unload_map(void)\n"
                  "{ game_tilemap_unload_map(&game_level1); }\n\n";
    } else {
        source += "/* Embedded C mode does not require reading an SD .map. */\n"
                  "uint8_t game_level1_load_map(const char *filename)\n"
                  "{ (void)filename; return 1; }\n"
                  "void game_level1_unload_map(void) {}\n\n";
    }
    // The generated level remembers its SD resource. The runtime helper
    // validates size and checksum and leaves the PPB pixels row-major.
    // SIDBOX gfx_drawbob() selects cells directly from that image.
    if (tileCount) {
        QByteArray path = QDir::cleanPath(QDir::fromNativeSeparators(map.atlasPath)).toUtf8();
        path.replace("\\", "\\\\");
        path.replace("\"", "\\\"");
        source += "/* Once at startup, AFTER initMalloc(). No per-frame SD reads. */\n";
        source += "uint8_t game_level1_load_atlas(void)\n{\n";
        source += "    if (game_level1.atlas) return 1;\n";
        source += "#ifdef GAMEASSETS_HAS_PPB_LOOKUP\n"
                  "    /* Share ONLY an identical PPB with a matching pixel checksum. */\n"
                  "    uint16_t shared_w = 0, shared_h = 0;\n"
                  "    const uint8_t *shared = gameassets_find_ppb(\"" + path +
                  "\", &shared_w, &shared_h);\n"
                  "    if (shared)\n"
                  "        return game_tilemap_attach_shared_ppb_atlas(&game_level1, "
                  "shared, shared_w, shared_h, " + QByteArray::number(atlasHash) + "u);\n"
                  "#endif\n";
        source += "    /* No matching sprite atlas: allocate separately from SD. */\n";
        source += "    return game_tilemap_load_ppb_atlas(&game_level1, \"" + path + "\", "
            + QByteArray::number(atlasWidth) + ", " + QByteArray::number(atlasHeight)
            + ", " + QByteArray::number(atlasHash) + "u);\n}\n\n";
    } else {
        source += "uint8_t game_level1_load_atlas(void) { return 1; }\n\n";
    }
    source += "void game_level1_unload_atlas(void)\n{\n"
              "    game_tilemap_unload_ppb_atlas(&game_level1);\n}\n";
    const auto atomic = [error](const QString &path, const QByteArray &bytes) {
        QSaveFile f(path);
        if (!f.open(QIODevice::WriteOnly) || f.write(bytes) != bytes.size() || !f.commit()) {
            if (error) *error = QStringLiteral("Cannot write %1: %2").arg(path, f.errorString());
            return false;
        }
        return true;
    };
    if (externalMap) {
        // Fixed little-endian 20-byte header and FNV-1a over the payload.
        // No absolute editor paths, object IDs or pointer bytes in the file.
        QByteArray payload = map.graphics + map.collisions + map.flips;
        for (const SidboxTileAnimation &a : map.animations) {
            payload.append(char(a.graphicId & 255));
            payload.append(char((a.graphicId >> 8) & 255));
            payload.append(char(a.frames));
            payload.append(char(a.frameTicks));
            payload.append(char((a.loop ? 1 : 0) | (a.bounce ? 2 : 0)));
            payload.append(char(0));
        }
        quint32 hash = 2166136261u;
        for (char b : payload) { hash ^= quint8(b); hash *= 16777619u; }
        QByteArray bytes("SBMP", 4);
        bytes.append(char(2)); // version 2 adds one flip byte per map cell
        bytes.append(char(map.tileSize));
        const auto appendU16 = [&bytes](unsigned v) {
            bytes.append(char(v & 255)); bytes.append(char((v >> 8) & 255));
        };
        appendU16(unsigned(map.width)); appendU16(unsigned(map.height));
        appendU16(tileCount); appendU16(unsigned(map.animations.size()));
        for (int offset = 0; offset < 32; offset += 8)
            bytes.append(char((hash >> offset) & 255));
        appendU16(0); // reserved
        bytes += payload;
        if (!atomic(QDir(folder).filePath(QStringLiteral("level1.map")), bytes))
            return false;
    }
    return atomic(QDir(folder).filePath(QStringLiteral("level1.h")), header)
        && atomic(QDir(folder).filePath(QStringLiteral("level1.c")), source);
}

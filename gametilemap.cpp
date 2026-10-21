#include "gametilemap.h"
#include "gamehelpertemplates.h"
#include "gametilemapinternal.h"
#include "ppbcodec.h"
#include "gameeditorcontrolstyle.h"
#include "gameeditoricons.h"

#include <QAbstractScrollArea>
#include <QAbstractItemView>
#include <QComboBox>
#include <QCheckBox>
#include <QToolButton>
#include <QFrame>
#include <QSettings>
#include <QCursor>
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
#include <QInputDialog>
#include <QListView>
#include <QSignalBlocker>
#include <QTimer>
#include <QRegion>
#include <QSet>
#include <QLabel>
#include <QMessageBox>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>
#include <QSaveFile>
#include <QShortcut>
#include <QPushButton>
#include <QPaintEvent>
#include <QResizeEvent>
#include <utility>
#include <algorithm>
#include <functional>
#include <QScrollBar>
#include <QScrollArea>
#include <QSplitter>
#include <QStackedWidget>
#include <QTabWidget>
#include <QTabBar>
#include <QPolygonF>
#include <QFont>
#include <QFontMetrics>
#include <QPixmap>
#include <QEvent>
#include <QSpinBox>
#include <QSlider>
#include <QLineF>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QtGlobal>


/* Design-time cubic Bezier. The runtime still receives the exact same v4
 * point-defined collision format, so SD loaders and established linear slopes
 * do not change. X control handles must be ordered to ensure one Y per X;
 * a full loop (where X reverses) is deliberately NOT represented as a slope. */
static QVector<QPoint> sampledCubicSlope(int width, int height,
                                        int startY, int endY,
                                        QPoint handleA, QPoint handleB)
{
    QVector<QPoint> out;
    if (width < 1 || height < 1 || handleA.x() < 0 ||
        handleA.x() > handleB.x() || handleB.x() > width) return out;
    const int intervals = qMin(width, 127); // <=128 exported points
    out.reserve(intervals + 1);
    for (int i = 0; i <= intervals; ++i) {
        const int x = int(qint64(width) * i / intervals);
        double low = 0.0, high = 1.0;
        for (int iteration = 0; iteration < 24; ++iteration) {
            const double t = (low + high) * 0.5, u = 1.0 - t;
            const double bx = 3.0*u*u*t*handleA.x() +
                3.0*u*t*t*handleB.x() + t*t*t*width;
            if (bx < x) low = t; else high = t;
        }
        const double t = (low + high) * 0.5, u = 1.0-t;
        const double by = u*u*u*startY + 3.0*u*u*t*handleA.y() +
            3.0*u*t*t*handleB.y() + t*t*t*endY;
        const int y = qBound(0, qRound(by), height);
        out.append(QPoint(x, y));
    }
    out.first() = QPoint(0, startY);
    out.last() = QPoint(width, endY);
    return out;
}


// Locate a whole collision placement. Instances never overlap in normal
// editing, so deleting an instance never leaves a partial collision stamp.
static int collisionPlacementAt(const SidboxTilemap &map, int x, int y)
{
    for (int i = map.collisionPlacements.size() - 1; i >= 0; --i) {
        const auto &place = map.collisionPlacements.at(i);
        if (place.stamp < 0 || place.stamp >= map.collisionStamps.size()) continue;
        const auto &shape = map.collisionStamps.at(place.stamp);
        if (x >= place.x && x < place.x + shape.width &&
            y >= place.y && y < place.y + shape.height) return i;
    }
    return -1;
}

static void removeCollisionPlacement(SidboxTilemap &map, int n)
{
    if (n < 0 || n >= map.collisionPlacements.size()) return;
    const auto place = map.collisionPlacements.at(n);
    if (place.stamp >= 0 && place.stamp < map.collisionStamps.size()) {
        const auto &shape = map.collisionStamps.at(place.stamp);
        for (int y = place.y; y < place.y + shape.height; ++y)
            for (int x = place.x; x < place.x + shape.width; ++x) {
                if (x >= 0 && y >= 0 && x < map.width && y < map.height)
                    map.collisions[y * map.width + x] = 0;
            }
    }
    map.collisionPlacements.removeAt(n);
}

static bool removePlacementsInRect(SidboxTilemap &map, const QRect &rect)
{
    bool removed = false;
    for (int i = map.collisionPlacements.size() - 1; i >= 0; --i) {
        const auto &p = map.collisionPlacements.at(i);
        if (p.stamp >= 0 && p.stamp < map.collisionStamps.size()) {
            const auto &s = map.collisionStamps.at(p.stamp);
            if (QRect(p.x, p.y, s.width, s.height).intersects(rect)) {
                removeCollisionPlacement(map, i);
                removed = true;
            }
        }
    }
    return removed;
}

static int slopeY(const SidboxCollisionStamp &s, int x, bool mirror)
{
    if (s.points.size() < 2) return s.height * s.tileSize;
    const int width = s.width * s.tileSize;
    if (mirror) x = width - x;
    x = qBound(0, x, width);
    for (int i = 1; i < s.points.size(); ++i) {
        const QPoint a = s.points.at(i - 1), b = s.points.at(i);
        if (x <= b.x()) {
            const int dx = b.x() - a.x();
            return dx ? a.y() + (b.y() - a.y()) * (x - a.x()) / dx : a.y();
        }
    }
    return s.points.last().y();
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
    explicit TilemapComboBox(QWidget *parent = nullptr) : QComboBox(parent)
    {
        setProperty("customChevron", true);
    }
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

// Small, genuinely checkable 24x24 toolbar glyphs. Drawn using the active
// IDE colours so both dark and light themes work without external icon files.
// The shared gameEditorControlStyle supplies the square checked/hover frames.
class TilemapFlagButton final : public QToolButton
{
public:
    enum Glyph { CellX, CellY, StampX, StampY, Front, StampFront, Player, Hitbox };

    explicit TilemapFlagButton(Glyph glyph, const QString &accessibleName, QWidget *parent)
        : QToolButton(parent), m_glyph(glyph)
    {
        setCheckable(true);
        setAutoRaise(false);
        setFixedSize(38, 36);
        setIconSize(QSize(24, 24));
        setAccessibleName(accessibleName);
        const QStringList filenames = {
            QStringLiteral("tilemap_cell_flip_x.png"),
            QStringLiteral("tilemap_cell_flip_y.png"),
            QStringLiteral("tilemap_stamp_flip_x.png"),
            QStringLiteral("tilemap_stamp_flip_y.png"),
            QStringLiteral("tilemap_draw_front.png"),
            QStringLiteral("tilemap_stamp_front.png"),
            QStringLiteral("tilemap_player_reference.png"),
            QStringLiteral("tilemap_player_hitbox.png")
        };
        setIcon(gameEditorExternalIcon(filenames.at(int(glyph))));
        setFocusPolicy(Qt::TabFocus); // Clicking does not steal the map Space shortcut.
    }

    void setGlyphColours(const QColor &normal, const QColor &checked)
    {
        m_normal = normal;
        m_checked = checked;
        update();
    }

protected:
    void paintEvent(QPaintEvent *event) override
    {
        QToolButton::paintEvent(event);
        if (!icon().isNull()) return; // User PNG replaces the themed fallback glyph.
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.translate((width() - 24) / 2.0, (height() - 24) / 2.0);
        QColor ink = isChecked() ? m_checked : m_normal;
        if (!isEnabled()) ink.setAlpha(100);
        p.setPen(QPen(ink, 1.8, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        p.setBrush(Qt::NoBrush);
        switch (m_glyph) {
        case CellX:
            p.drawLine(12, 3, 12, 21);
            p.drawPolyline(QPolygonF({QPointF(9, 5), QPointF(3, 12), QPointF(9, 19)}));
            p.drawPolyline(QPolygonF({QPointF(15, 5), QPointF(21, 12), QPointF(15, 19)}));
            break;
        case CellY:
            p.drawLine(3, 12, 21, 12);
            p.drawPolyline(QPolygonF({QPointF(5, 9), QPointF(12, 3), QPointF(19, 9)}));
            p.drawPolyline(QPolygonF({QPointF(5, 15), QPointF(12, 21), QPointF(19, 15)}));
            break;
        case StampX:
        case StampY:
            // Four cells distinguish whole-stamp mirroring from cell flip.
            for (int y : {3, 13}) for (int x : {3, 13})
                p.drawRect(QRectF(x, y, 8, 8));
            if (m_glyph == StampX) {
                p.drawLine(5, 12, 19, 12);
                p.drawLine(5, 12, 8, 9); p.drawLine(5, 12, 8, 15);
                p.drawLine(19, 12, 16, 9); p.drawLine(19, 12, 16, 15);
            } else {
                p.drawLine(12, 5, 12, 19);
                p.drawLine(12, 5, 9, 8); p.drawLine(12, 5, 15, 8);
                p.drawLine(12, 19, 9, 16); p.drawLine(12, 19, 15, 16);
            }
            break;
        case Front:
            p.drawRect(QRectF(3, 9, 12, 12));
            p.drawRect(QRectF(9, 3, 12, 12));
            p.drawLine(18, 6, 18, 12);
            p.drawLine(15, 9, 18, 6); p.drawLine(21, 9, 18, 6);
            break;
        case StampFront:
            for (int y : {3, 12}) for (int x : {3, 12})
                p.drawRect(QRectF(x, y, 8, 8));
            p.drawRect(QRectF(8, 8, 12, 12));
            p.drawLine(14, 10, 14, 17);
            p.drawLine(11, 13, 14, 10); p.drawLine(17, 13, 14, 10);
            break;
        case Player:
            // A figure inside its design-time placement outline.
            p.setPen(QPen(ink, 1.4, Qt::DashLine));
            p.drawRect(QRectF(2, 2, 20, 20));
            p.setPen(QPen(ink, 1.8));
            p.drawRect(QRectF(9, 4, 6, 6));
            p.drawLine(12, 10, 12, 17);
            p.drawLine(12, 12, 6, 15); p.drawLine(12, 12, 18, 15);
            p.drawLine(12, 17, 8, 20); p.drawLine(12, 17, 16, 20);
            break;
        case Hitbox:
            p.drawRect(QRectF(3, 3, 18, 18));
            p.drawLine(3, 8, 3, 3); p.drawLine(3, 3, 8, 3);
            p.drawLine(16, 21, 21, 21); p.drawLine(21, 21, 21, 16);
            p.drawLine(12, 6, 12, 18); p.drawLine(6, 12, 18, 12);
            p.drawRect(QRectF(9, 9, 6, 6));
            break;
        }
    }
private:
    Glyph m_glyph;
    QColor m_normal = Qt::white;
    QColor m_checked = Qt::white;
};

// Dedicated paint-mode buttons: 16x16 above the Tile Atlas and 24x24
// collision shortcuts beside the collision brush. The current brush values
// remain in the existing QComboBoxes, so saving/painting logic is unchanged.
class TilemapPaintButton final : public QToolButton
{
public:
    enum Glyph { KeepGraphic, EmptyGraphic, AtlasGraphic, KeepCollision, EmptyCollision,
                 ApplyFlags, KeepFlags };
    TilemapPaintButton(Glyph glyph, const QString &name, QWidget *parent)
        : QToolButton(parent), m_glyph(glyph)
    {
        setCheckable(true);
        setAutoRaise(false);
        const bool small = glyph == KeepGraphic || glyph == EmptyGraphic || glyph == AtlasGraphic;
        setFixedSize(small ? QSize(28, 28) : QSize(38, 36));
        setIconSize(small ? QSize(16, 16) : QSize(24, 24));
        setAccessibleName(name);
        const QStringList filenames = {
            QStringLiteral("tilemap_graphic_keep.png"),
            QStringLiteral("tilemap_graphic_empty.png"),
            QStringLiteral("tilemap_graphic_atlas.png"),
            QStringLiteral("tilemap_collision_keep.png"),
            QStringLiteral("tilemap_collision_empty.png"),
            QStringLiteral("tilemap_flags_apply.png"),
            QStringLiteral("tilemap_flags_keep.png")
        };
        setIcon(gameEditorExternalIcon(filenames.at(int(glyph))));
        setFocusPolicy(Qt::TabFocus);
    }
    void setGlyphColours(const QColor &normal, const QColor &selected)
    {
        m_normal = normal;
        m_selected = selected;
        update();
    }
protected:
    void paintEvent(QPaintEvent *event) override
    {
        QToolButton::paintEvent(event);
        if (!icon().isNull()) return; // User PNG replaces the themed fallback glyph.
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing, true);
        const int side = iconSize().width();
        p.translate((width()-side)/2.0, (height()-side)/2.0);
        p.scale(side / 24.0, side / 24.0);
        QColor ink = isChecked() ? m_selected : m_normal;
        if (!isEnabled()) ink.setAlpha(110);
        p.setPen(QPen(ink, 2.0, Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        p.setBrush(Qt::NoBrush);
        switch (m_glyph) {
        case ApplyFlags:
            // Apply the selected X/Y/front tile flags: tick in a square.
            p.drawRect(QRectF(3, 3, 18, 18));
            p.drawPolyline(QPolygonF({QPointF(6, 12), QPointF(10, 17), QPointF(19, 7)}));
            break;
        case KeepFlags:
            // Preserve all existing flags: a minus sign in the same square.
            p.drawRect(QRectF(3, 3, 18, 18));
            p.drawLine(QPointF(6, 12), QPointF(18, 12));
            break;
        case KeepGraphic:
        case KeepCollision:
            // No-entry: leave the existing graphic/collision untouched.
            p.drawEllipse(QRectF(3, 3, 18, 18));
            p.drawLine(QPointF(6, 6), QPointF(18, 18));
            break;
        case EmptyGraphic:
        case EmptyCollision:
            // Empty square with eraser stroke: explicitly clear the layer.
            p.drawRect(QRectF(3, 3, 18, 18));
            p.drawLine(QPointF(5, 19), QPointF(19, 5));
            p.drawLine(QPointF(14, 19), QPointF(19, 19));
            break;
        case AtlasGraphic:
            // Four atlas cells, one selected.
            p.drawRect(QRectF(3, 3, 8, 8));
            p.drawRect(QRectF(13, 3, 8, 8));
            p.drawRect(QRectF(3, 13, 8, 8));
            p.setBrush(ink);
            p.drawRect(QRectF(13, 13, 8, 8));
            break;
        }
    }
private:
    Glyph m_glyph;
    QColor m_normal = Qt::white;
    QColor m_selected = Qt::white;
};

class SidboxTilemapEditor::Canvas final : public QAbstractScrollArea
{
public:
    SidboxTilemap *map = nullptr;
    QImage *atlas = nullptr;
    int zoom = 2;
    static constexpr int maxZoom = 16;
    std::function<void(int)> zoomChanged;
    bool showCollisions = true;
    QImage playerReference;
    QRect playerHitbox; // unscaled local sprite pixels; empty = full sprite
    bool showPlayerCollision = true;
    int playerReferenceScale = 100;
    QPoint playerReferenceInitialPosition;
    bool showPlayerReference = false;
    bool draggingPlayerReference = false;
    QPoint playerReferenceDragOffset; // offset from sprite corner, in world pixels
    QSize playerReferenceWorldSize() const
    {
        return QSize(qMax(1, qRound(playerReference.width() * playerReferenceScale / 100.0)),
                     qMax(1, qRound(playerReference.height() * playerReferenceScale / 100.0)));
    }
    QPoint playerReferencePosition() const
    {
        if (!map) return {};
        const QSize size = playerReferenceWorldSize();
        const QPoint p = map->referencePlayerPositionSet
            ? QPoint(map->referencePlayerX, map->referencePlayerY)
            : playerReferenceInitialPosition;
        return QPoint(qBound(0, p.x(), qMax(0, map->width * map->tileSize - size.width())),
                      qBound(0, p.y(), qMax(0, map->height * map->tileSize - size.height())));
    }
    QRect playerReferenceRect() const
    {
        if (!map || !showPlayerReference || playerReference.isNull()) return {};
        const QPoint p = playerReferencePosition();
        const QSize size = playerReferenceWorldSize();
        return QRect(p.x() * zoom - horizontalScrollBar()->value(),
                     p.y() * zoom - verticalScrollBar()->value(),
                     size.width() * zoom, size.height() * zoom);
    }
    QRect playerHitboxWorldRect() const
    {
        if (!map || playerReference.isNull()) return {};
        const QRect box = playerHitbox.isEmpty()
            ? QRect(0, 0, playerReference.width(), playerReference.height()) : playerHitbox;
        const QSize size = playerReferenceWorldSize();
        const QPoint p = playerReferencePosition();
        // Scale BOTH edges to avoid a 1px box disappearing at small sizes.
        const int x1 = qRound(double(box.left()) * size.width() / playerReference.width());
        const int y1 = qRound(double(box.top()) * size.height() / playerReference.height());
        const int x2 = qRound(double(box.left() + box.width()) * size.width() / playerReference.width());
        const int y2 = qRound(double(box.top() + box.height()) * size.height() / playerReference.height());
        return QRect(p.x() + x1, p.y() + y1, qMax(1, x2 - x1), qMax(1, y2 - y1));
    }
    // Editor-only, stationary clearance probe (NOT a physics simulation).
    // 0=clear, 1=blocking solid/slope, 2=hazard, 3=one-way,
    // 4=nonblocking zone/door. A point shape occupies everything BELOW its curve.
    int playerCellContact(int tx, int ty, const QRect &box) const
    {
        if (!map || tx < 0 || ty < 0 || tx >= map->width || ty >= map->height) return 0;
        const int tile = map->tileSize;
        const QRect cell(tx * tile, ty * tile, tile, tile);
        const QRect overlap = box.intersected(cell);
        if (overlap.isEmpty()) return 0;
        const int index = ty * map->width + tx;
        const unsigned type = quint8(map->collisions.at(index));
        if (type == 1 || (type >= 17 && type <= 24)) return 1;
        if (type == 5) return 2;
        if (type == 2) return 3; // one-way: descent only; not a solid wall
        if (type == 6 || (type >= 9 && type <= 16)) return 4;
        if (type < 3 || (type > 4 && type != 7 && type != 8)) return 0;
        const SidboxCollisionStamp *shape = nullptr;
        SidboxCollisionPlacement place;
        if (type == 8) {
            const int owner = collisionPlacementAt(*map, tx, ty);
            if (owner < 0) return 0;
            place = map->collisionPlacements.at(owner);
            if (place.stamp < 0 || place.stamp >= map->collisionStamps.size()) return 0;
            shape = &map->collisionStamps.at(place.stamp);
        }
        // A pixel of the player's hitbox BELOW the surface = embedded in
        // the solid interior; merely touching the curve is marked as contact.
        for (int x = overlap.left(); x <= overlap.right(); ++x) {
            int surface = cell.top() + tile;
            if (type == 3) surface = cell.top() + tile - 1 - (x - cell.left());
            else if (type == 4) surface = cell.top() + (x - cell.left());
            else if (type == 7) {
                const int slopeIndex = index * tile + x - cell.left();
                if (slopeIndex >= map->slopes.size()) continue;
                surface = cell.top() + quint8(map->slopes.at(slopeIndex));
            } else if (shape) {
                const int localX = x - place.x * tile;
                // Match the V1 collision loader: mirror columns 0..width-1,
                // rather than mirroring the outer width boundary coordinate.
                const int shapeX = place.mirrorX
                    ? shape->width * tile - 1 - localX : localX;
                surface = place.y * tile + slopeY(*shape, shapeX, false);
            }
            if (overlap.bottom() >= surface) return 1;
        }
        return 0;
    }
    bool movePlayerReferenceToMouse()
    {
        if (!map || !showPlayerReference || playerReference.isNull() ||
            draggingPlayerReference || painting || selectingRegion || panning ||
            temporaryActive || loopDragKind) return false;
        const QPoint mouse = viewport()->mapFromGlobal(QCursor::pos());
        if (!viewport()->rect().contains(mouse)) return false;
        const QPoint world((mouse.x() + horizontalScrollBar()->value()) / zoom,
                           (mouse.y() + verticalScrollBar()->value()) / zoom);
        const QSize size = playerReferenceWorldSize();
        const int x = qBound(0, world.x() - size.width() / 2,
                             qMax(0, map->width * map->tileSize - size.width()));
        const int y = qBound(0, world.y() - size.height() / 2,
                             qMax(0, map->height * map->tileSize - size.height()));
        if (playerReferencePosition() == QPoint(x, y)) return true;
        if (strokeStarted) strokeStarted();
        map->referencePlayerPositionSet = true;
        map->referencePlayerX = x;
        map->referencePlayerY = y;
        if (strokeFinished) strokeFinished();
        viewport()->update();
        return true;
    }
    // -1 = preserve existing value, 0 = erase, 1 = selected atlas tile.
    int graphicMode = 1;
    int graphicBrush = 1;
    int collisionBrush = -1;
    int flipMode = 1; // -1 = preserve existing, 1 = apply the current flip checkboxes
    quint8 flipBrush = 0;
    quint8 stampMirror = 0;
    bool stampUseFrontBrush = false; // stamp override: use Draw in front of player checkbox
    int stampIndex = -1; // -1 means ordinary atlas-tile painting
    int collisionStampIndex = -1; // separate collision-only brush
    bool loopEditMode = false;
    int selectedLoop = -1;
    int loopDragKind = 0; // 1 centre, 2 radius
    QPoint loopDragOffset;
    std::function<void()> loopEdited;
    bool painting = false;
    bool panning = false;
    bool erasingStroke = false;
    bool hoverValid = false;
    QPoint hoverCell;
    // Shift-drag copies a map rectangle into a transient brush. Nothing is
    // persisted to the stamp bank and no game export format changes.
    bool selectingRegion = false;
    QPoint regionStart, regionEnd;
    bool temporaryActive = false;
    bool draggingTemporary = false;
    QPoint temporaryAnchor;
    SidboxTileStamp temporaryStamp;
    QByteArray temporarySlopes;
    QVector<SidboxCollisionPlacement> temporaryPlacements;
    std::function<void(const QString &)> temporaryStatus;

    QPoint legacyFocusCell = QPoint(-1, -1); // last cell found by Find Legacy
    // An individual stamp drag is aligned to its first pressed map cell.
    // Grid coordinates are measured in stamp widths/heights, not tile pixels.
    QPoint stampAnchor;
    QPoint lastStampGrid;
    bool stampAnchorValid = false;
    bool lastStampGridValid = false;
    std::function<void()> strokeStarted;
    std::function<void()> strokeFinished;
    std::function<void()> hoveredCellChanged;
    // Shift-click a placed collision slope to edit its shared definition.
    std::function<void(int)> editPlacedCollision;
    QPoint lastPan;
    int zoomWheelRemainder = 0;
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
    // Zoom about a viewport pixel, not the map origin. The world pixel under
    // this anchor stays under it as the zoom changes (unless clamped at an edge).
    void setZoom(int requestedZoom, const QPoint &anchor)
    {
        const int nextZoom = qBound(1, requestedZoom, maxZoom);
        if (!map || nextZoom == zoom) return;
        const double worldX = double(horizontalScrollBar()->value() + anchor.x()) / zoom;
        const double worldY = double(verticalScrollBar()->value() + anchor.y()) / zoom;
        zoom = nextZoom;
        adjust(); // Update scrollbar ranges BEFORE restoring the anchor.
        horizontalScrollBar()->setValue(qRound(worldX * zoom - anchor.x()));
        verticalScrollBar()->setValue(qRound(worldY * zoom - anchor.y()));
        const QPoint mouse = viewport()->mapFromGlobal(QCursor::pos());
        if (viewport()->rect().contains(mouse)) updateHover(mouse);
        else if (hoverValid) {
            hoverValid = false;
            if (hoveredCellChanged) hoveredCellChanged();
        }
        viewport()->update();
        if (zoomChanged) zoomChanged(zoom);
    }
    QPoint keyboardZoomAnchor() const
    {
        const QPoint mouse = viewport()->mapFromGlobal(QCursor::pos());
        return viewport()->rect().contains(mouse)
            ? mouse : viewport()->rect().center();
    }
    QPoint cellAt(const QPoint &at) const
    {
        const int px = map->tileSize * zoom;
        return QPoint(qBound(0, (at.x() + horizontalScrollBar()->value()) / px,
                               map->width - 1),
                      qBound(0, (at.y() + verticalScrollBar()->value()) / px,
                               map->height - 1));
    }
    QRect regionRect() const
    {
        return QRect(QPoint(qMin(regionStart.x(), regionEnd.x()),
                            qMin(regionStart.y(), regionEnd.y())),
                     QPoint(qMax(regionStart.x(), regionEnd.x()),
                            qMax(regionStart.y(), regionEnd.y())));
    }
    void deactivateTemporary()
    {
        temporaryActive = false;
        draggingTemporary = false;
        temporaryStamp = SidboxTileStamp();
        temporarySlopes.clear();
        temporaryPlacements.clear();
        if (temporaryStatus) temporaryStatus(QString());
        viewport()->update();
    }
    bool copyRegion(QRect area)
    {
        if (!map || area.isEmpty()) return false;
        // Point-defined slopes are indivisible; including even a single tile
        // expands the selection to the full placement, never an orphan type 8.
        bool expanded;
        do {
            expanded = false;
            for (const auto &place : map->collisionPlacements) {
                if (place.stamp < 0 || place.stamp >= map->collisionStamps.size()) continue;
                const auto &shape = map->collisionStamps.at(place.stamp);
                const QRect whole(place.x, place.y, shape.width, shape.height);
                if (area.intersects(whole) && !area.contains(whole)) {
                    area = area.united(whole);
                    expanded = true;
                }
            }
        } while (expanded);
        if (area.width() > map->width || area.height() > map->height) return false;
        SidboxTileStamp temp;
        temp.name = QStringLiteral("Temporary selection");
        temp.width = area.width(); temp.height = area.height();
        temp.tileSize = map->tileSize;
        temp.graphics.resize(temp.width * temp.height * 2);
        temp.collisions.resize(temp.width * temp.height);
        temp.flips.resize(temp.width * temp.height);
        QByteArray heights(temp.width * temp.height * map->tileSize, char(0));
        for (int y = 0; y < temp.height; ++y)
            for (int x = 0; x < temp.width; ++x) {
                const int src = (area.y() + y) * map->width + area.x() + x;
                const int dst = y * temp.width + x;
                temp.graphics[dst * 2] = map->graphics.at(src * 2);
                temp.graphics[dst * 2 + 1] = map->graphics.at(src * 2 + 1);
                temp.collisions[dst] = map->collisions.at(src);
                temp.flips[dst] = map->flips.at(src);
                for (int k = 0; k < map->tileSize; ++k)
                    heights[dst * map->tileSize + k] = map->slopes.at(src * map->tileSize + k);
            }
        QVector<SidboxCollisionPlacement> shapes;
        for (const auto &place : map->collisionPlacements) {
            if (place.stamp < 0 || place.stamp >= map->collisionStamps.size()) continue;
            const auto &shape = map->collisionStamps.at(place.stamp);
            if (!area.contains(QRect(place.x, place.y, shape.width, shape.height))) continue;
            auto local = place;
            local.x -= area.x(); local.y -= area.y();
            shapes.append(local);
        }
        // A corrupt older design could have orphaned type-8 markers. Never
        // copy those without a valid complete placement backing them.
        for (int y = 0; y < temp.height; ++y)
            for (int x = 0; x < temp.width; ++x) {
                const int cell = y * temp.width + x;
                if (quint8(temp.collisions.at(cell)) != 8) continue;
                bool owned = false;
                for (const auto &place : shapes) {
                    const auto &shape = map->collisionStamps.at(place.stamp);
                    if (x >= place.x && x < place.x + shape.width &&
                        y >= place.y && y < place.y + shape.height) {
                        owned = true; break;
                    }
                }
                if (!owned) temp.collisions[cell] = 0;
            }
        temporaryStamp = temp;
        temporarySlopes = heights;
        temporaryPlacements = shapes;
        temporaryActive = true;
        stampAnchorValid = false;
        lastStampGridValid = false;
        if (temporaryStatus)
            temporaryStatus(QStringLiteral("Copied %1×%2 · Click: paste · Esc: cancel")
                            .arg(temp.width).arg(temp.height));
        viewport()->update();
        return true;
    }
    bool applyTemporary(bool erase)
    {
        if (!map || !temporaryActive || !hoverValid) return false;
        const int w = temporaryStamp.width, h = temporaryStamp.height;
        const int bx = hoverCell.x(), by = hoverCell.y();
        if (bx < 0 || by < 0 || bx + w > map->width || by + h > map->height) {
            if (temporaryStatus) temporaryStatus(QStringLiteral("Paste must fit inside the map. Move the preview away from the edge."));
            return false;
        }
        if (strokeStarted) strokeStarted();
        // A temporary region may contain collision shapes, but it must never
        // delete a collision stamp already placed in the destination. If a
        // copied shape would overlap one, skip that whole copied shape so no
        // orphan type-8 markers can be left in its uncovered cells.
        QVector<bool> blocked(temporaryPlacements.size(), false);
        for (int n = 0; n < temporaryPlacements.size(); ++n) {
            const auto &copy = temporaryPlacements.at(n);
            if (copy.stamp < 0 || copy.stamp >= map->collisionStamps.size()) {
                blocked[n] = true;
                continue;
            }
            const auto &shape = map->collisionStamps.at(copy.stamp);
            const QRect target(bx + copy.x, by + copy.y, shape.width, shape.height);
            for (const auto &placed : map->collisionPlacements) {
                if (placed.stamp < 0 || placed.stamp >= map->collisionStamps.size()) continue;
                const auto &existing = map->collisionStamps.at(placed.stamp);
                if (target.intersects(QRect(placed.x, placed.y, existing.width, existing.height))) {
                    blocked[n] = true;
                    break;
                }
            }
        }
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x) {
                const int src = y * w + x;
                const int dstX = bx + x, dstY = by + y;
                const int dst = dstY * map->width + dstX;
                const quint16 tile = erase ? 0 : mapGraphic(temporaryStamp.graphics, src);
                setMapGraphic(map->graphics, dst, tile);
                const quint8 saved = quint8(temporaryStamp.flips.at(src));
                map->flips[dst] = erase ? char(0) : char((saved & ~4u) |
                    (stampUseFrontBrush ? (flipBrush & 4u) : (saved & 4u)));
                // Graphic edits always work; collision edits never displace
                // an existing placed shape (including right-click erase).
                bool protectCollision = collisionPlacementAt(*map, dstX, dstY) >= 0;
                if (!protectCollision) for (int n = 0; n < temporaryPlacements.size(); ++n) {
                    if (!blocked.at(n)) continue;
                    const auto &copy = temporaryPlacements.at(n);
                    if (copy.stamp < 0 || copy.stamp >= map->collisionStamps.size()) continue;
                    const auto &shape = map->collisionStamps.at(copy.stamp);
                    if (x >= copy.x && x < copy.x + shape.width &&
                        y >= copy.y && y < copy.y + shape.height) {
                        protectCollision = true;
                        break;
                    }
                }
                if (!protectCollision) {
                    map->collisions[dst] = erase ? char(0) : temporaryStamp.collisions.at(src);
                    for (int k = 0; k < map->tileSize; ++k)
                        map->slopes[dst * map->tileSize + k] = erase ? char(0) :
                            temporarySlopes.at(src * map->tileSize + k);
                }
            }
        if (!erase)
            for (int n = 0; n < temporaryPlacements.size(); ++n) {
                if (blocked.at(n)) continue;
                auto place = temporaryPlacements.at(n);
                place.x += bx; place.y += by;
                map->collisionPlacements.append(place);
            }
        if (strokeFinished) strokeFinished();
        viewport()->update();
        return true;
    }
    // The preview is deliberately paint-only: it never changes a tile or the
    // undo stack. While dragging a stamp it uses the same first-click grid
    // and negative-coordinate floor division as paintAt().
    QPoint previewBaseCell() const
    {
        if (!map || !hoverValid) return QPoint(-1, -1);
        if (temporaryActive) return hoverCell;
        int w = 0, h = 0, size = 0;
        if (collisionStampIndex >= 0 && collisionStampIndex < map->collisionStamps.size()) {
            const auto &stamp = map->collisionStamps.at(collisionStampIndex);
            w = stamp.width; h = stamp.height; size = stamp.tileSize;
        } else if (stampIndex >= 0 && stampIndex < map->stamps.size()) {
            const auto &stamp = map->stamps.at(stampIndex);
            w = stamp.width; h = stamp.height; size = stamp.tileSize;
        }
        if (!painting || !stampAnchorValid || size != map->tileSize) return hoverCell;
        const int dx = hoverCell.x() - stampAnchor.x();
        const int dy = hoverCell.y() - stampAnchor.y();
        const int gx = dx >= 0 ? dx / w : -((-dx + w - 1) / w);
        const int gy = dy >= 0 ? dy / h : -((-dy + h - 1) / h);
        return QPoint(stampAnchor.x() + gx * w,
                      stampAnchor.y() + gy * h);
    }
    QRect previewBounds() const
    {
        if (!map || !hoverValid || panning || selectingRegion || loopEditMode) return QRect();
        const int px = map->tileSize * zoom;
        int w = temporaryActive ? temporaryStamp.width : 1;
        int h = temporaryActive ? temporaryStamp.height : 1;
        if (temporaryActive) {
            // The captured rectangle is the brush footprint.
        } else if (collisionStampIndex >= 0 && collisionStampIndex < map->collisionStamps.size()) {
            const auto &stamp = map->collisionStamps.at(collisionStampIndex);
            if (stamp.tileSize == map->tileSize) { w = stamp.width; h = stamp.height; }
        } else if (stampIndex >= 0 && stampIndex < map->stamps.size()) {
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
        if (hoveredCellChanged) hoveredCellChanged();
    }
    void paintBrushPreview(QPainter &painter)
    {
        if (!map || !hoverValid || panning || selectingRegion || loopEditMode) return;
        const int px = map->tileSize * zoom;
        const QPoint base = previewBaseCell();
        int w = temporaryActive ? temporaryStamp.width : 1;
        int h = temporaryActive ? temporaryStamp.height : 1;
        const SidboxTileStamp *stamp = temporaryActive ? &temporaryStamp : nullptr;
        if (!temporaryActive && stampIndex >= 0 && stampIndex < map->stamps.size() &&
            map->stamps.at(stampIndex).tileSize == map->tileSize) {
            stamp = &map->stamps.at(stampIndex);
            w = stamp->width; h = stamp->height;
        }
        if (!temporaryActive && collisionStampIndex >= 0 && collisionStampIndex < map->collisionStamps.size()) {
            const auto &collisionStamp = map->collisionStamps.at(collisionStampIndex);
            if (collisionStamp.tileSize == map->tileSize) {
                w = collisionStamp.width; h = collisionStamp.height;
            }
        }
        const QRect mapPixels(-horizontalScrollBar()->value(),
                              -verticalScrollBar()->value(),
                              map->width * px, map->height * px);
        const QRect footprint(base.x() * px - horizontalScrollBar()->value(),
                              base.y() * px - verticalScrollBar()->value(),
                              w * px, h * px);
        if (!footprint.intersects(mapPixels)) return;
        const bool erase = (painting && erasingStroke) ||
            (!temporaryActive && !stamp && graphicMode == 0 && !painting);
        const int cols = atlas && !atlas->isNull() ? atlas->width() / map->tileSize : 0;
        const int rows = atlas && !atlas->isNull() ? atlas->height() / map->tileSize : 0;
        painter.save();
        painter.setClipRect(viewport()->rect().intersected(mapPixels));
        if (!temporaryActive && collisionStampIndex >= 0 && collisionStampIndex < map->collisionStamps.size()) {
            const auto &s = map->collisionStamps.at(collisionStampIndex);
            if (s.tileSize == map->tileSize) {
                // Only draw collision surfaces: graphics behind remain untouched.
                painter.setOpacity(0.42);
                for (int sx = 0; sx < w; ++sx)
                    for (int sy = 0; sy < h; ++sy) {
                        const int x = base.x() + sx, y = base.y() + sy;
                        if (x < 0 || y < 0 || x >= map->width || y >= map->height) continue;
                        const QRect cell(x * px - horizontalScrollBar()->value(),
                                         y * px - verticalScrollBar()->value(), px, px);
                        painter.fillRect(cell, erasingStroke ? QColor(255, 72, 72, 110)
                                                         : QColor(0, 180, 154, 70));
                    }
                painter.setOpacity(1.0);
                painter.setPen(QPen(QColor(88, 255, 214), 2));
                QPolygonF outline;
                for (const QPoint &pt : s.points) {
                    const int localX = (stampMirror & 1) ? w * map->tileSize - pt.x() : pt.x();
                    outline << QPointF(footprint.left() + localX * zoom,
                                       footprint.top() + pt.y() * zoom);
                }
                if (stampMirror & 1) std::reverse(outline.begin(), outline.end());
                if (!outline.isEmpty()) painter.drawPolyline(outline);
                painter.setPen(QPen(QColor(88, 255, 214), 2));
                painter.drawRect(footprint.adjusted(1, 1, -2, -2));
                painter.restore();
                return;
            }
        }
        // Limit previews to visible tiles even for very large copied regions.
        const int visibleX0 = qMax(0, (horizontalScrollBar()->value() - base.x() * px) / px - 1);
        const int visibleY0 = qMax(0, (verticalScrollBar()->value() - base.y() * px) / px - 1);
        const int visibleX1 = qMin(w, visibleX0 + viewport()->width() / px + 3);
        const int visibleY1 = qMin(h, visibleY0 + viewport()->height() / px + 3);
        if (!erase) {
            painter.setOpacity(0.62);
            for (int sy = visibleY0; sy < visibleY1; ++sy)
                for (int sx = visibleX0; sx < visibleX1; ++sx) {
                const int x = base.x() + sx, y = base.y() + sy;
                if (x < 0 || y < 0 || x >= map->width || y >= map->height) continue;
                int id = 0;
                quint8 flip = 0;
                if (stamp) {
                    const int sourceX = (!temporaryActive && (stampMirror & 1)) ? w - 1 - sx : sx;
                    const int sourceY = (!temporaryActive && (stampMirror & 2)) ? h - 1 - sy : sy;
                    const int i = sourceY * w + sourceX;
                    id = mapGraphic(stamp->graphics, i);
                    const quint8 savedFlags = quint8(stamp->flips.at(i));
                    flip = quint8(((savedFlags & 3u) ^ (temporaryActive ? 0 : stampMirror)) |
                        (stampUseFrontBrush ? (flipBrush & 4u) : (savedFlags & 4u)));
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
                    painter.drawImage(dest, (flip & 3) ? tile.flipped(Qt::Orientations(static_cast<Qt::Orientation>(flip & 3))) : tile);
                } else {
                    painter.fillRect(dest, QColor(110, 137, 156));
                }
            }
            painter.setOpacity(1.0);
        } else {
            painter.fillRect(footprint, QColor(240, 90, 90, 55));
        }
        if (temporaryActive && showCollisions) {
            // A faint collision overlay makes the temporary copy's physical
            // footprint visible as well as its artwork.
            painter.setOpacity(0.24);
            for (int sy = visibleY0; sy < visibleY1; ++sy)
                for (int sx = visibleX0; sx < visibleX1; ++sx) {
                    const unsigned kind = quint8(temporaryStamp.collisions.at(sy * w + sx));
                    if (!kind) continue;
                    const QRect cell((base.x() + sx) * px - horizontalScrollBar()->value(),
                                     (base.y() + sy) * px - verticalScrollBar()->value(), px, px);
                    painter.fillRect(cell, kind == 5 ? QColor(255, 70, 70) : QColor(70, 235, 185));
                }
            painter.setOpacity(1.0);
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
        if (collisionStampIndex >= 0 && collisionStampIndex < map->collisionStamps.size()) {
            const SidboxCollisionStamp &stamp = map->collisionStamps.at(collisionStampIndex);
            if (stamp.tileSize != map->tileSize) return;
            if (!stampAnchorValid) {
                stampAnchor = QPoint(tx, ty);
                stampAnchorValid = true;
                lastStampGridValid = false;
            }
            const int dx = tx - stampAnchor.x(), dy = ty - stampAnchor.y();
            const int gx = dx >= 0 ? dx / stamp.width : -((-dx + stamp.width - 1) / stamp.width);
            const int gy = dy >= 0 ? dy / stamp.height : -((-dy + stamp.height - 1) / stamp.height);
            const QPoint target(gx, gy);
            auto apply = [&](int sx, int sy) {
                const int bx = stampAnchor.x() + sx * stamp.width;
                const int by = stampAnchor.y() + sy * stamp.height;
                if (erase) {
                    // Erasing ANY occupied cell clears the ENTIRE instance.
                    // Also works when the mouse click starts halfway across it.
                    removePlacementsInRect(*map, QRect(bx, by, stamp.width, stamp.height));
                    // Legacy v3 cells had no placement identity. Clear them
                    // within the brush footprint; they cannot be recovered
                    // into whole instances automatically.
                    for (int y = qMax(0, by); y < qMin(map->height, by+stamp.height); ++y)
                        for (int x = qMax(0, bx); x < qMin(map->width, bx+stamp.width); ++x) {
                            const int index = y * map->width + x;
                            if (quint8(map->collisions.at(index)) == 7) {
                                map->collisions[index] = 0;
                                for (int k = 0; k < map->tileSize; ++k)
                                    map->slopes[index * map->tileSize + k] = 0;
                            }
                        }
                } else {
                    // Never put incomplete instances along the map edges.
                    if (bx < 0 || by < 0 || bx + stamp.width > map->width ||
                        by + stamp.height > map->height) return;
                    // Left-click never removes/replaces an existing collision
                    // shape. Right-click with a collision-stamp brush is the
                    // only canvas painting action which deletes a placement.
                    const QRect newArea(bx, by, stamp.width, stamp.height);
                    for (const auto &placed : map->collisionPlacements) {
                        if (placed.stamp < 0 || placed.stamp >= map->collisionStamps.size()) continue;
                        const auto &old = map->collisionStamps.at(placed.stamp);
                        if (newArea.intersects(QRect(placed.x, placed.y, old.width, old.height)))
                            return;
                    }
                    for (int y = by; y < by + stamp.height; ++y)
                        for (int x = bx; x < bx + stamp.width; ++x) {
                            const int idx = y * map->width + x;
                            map->collisions[idx] = char(8);
                            // Erase leftover legacy height data on these cells.
                            for (int k = 0; k < map->tileSize; ++k)
                                map->slopes[idx * map->tileSize + k] = 0;
                        }
                    SidboxCollisionPlacement instance;
                    instance.stamp = collisionStampIndex;
                    instance.x = bx; instance.y = by;
                    instance.mirrorX = (stampMirror & 1) != 0;
                    map->collisionPlacements.append(instance);
                }
                viewport()->update();
            };
            if (!lastStampGridValid) apply(gx, gy);
            else {
                const int differenceX = gx - lastStampGrid.x();
                const int differenceY = gy - lastStampGrid.y();
                const int steps = qMax(qAbs(differenceX), qAbs(differenceY));
                for (int i = 1; i <= steps; ++i)
                    apply(lastStampGrid.x() + qRound(double(differenceX) * i / steps),
                          lastStampGrid.y() + qRound(double(differenceY) * i / steps));
            }
            lastStampGrid = target;
            lastStampGridValid = true;
            return;
        }
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
                        // Keep the stamp's individual X/Y flips and apply its mirror.
                        // The optional override changes ONLY the draw-front bit.
                        const quint8 savedFlags = quint8(stamp.flips.at(cell));
                        const quint8 outputFlags = quint8(((savedFlags & 3u) ^ stampMirror) |
                            (stampUseFrontBrush ? (flipBrush & 4u) : (savedFlags & 4u)));
                        const char f = (erase || !g) ? char(0) : char(outputFlags);
                        bool changed = false;
                        if (mapGraphic(map->graphics, index) != g) {
                            setMapGraphic(map->graphics, index, g);
                            changed = true;
                        }
                        // Graphics and per-tile flips can be painted over a
                        // collision slope without deleting its shape. On
                        // unoccupied cells, ordinary graphic-stamp collision
                        // properties still work as before.
                        if (collisionPlacementAt(*map, x, y) < 0) {
                            if (map->collisions.at(index) != c) {
                                map->collisions[index] = c;
                                changed = true;
                            }
                            for (int k = 0; k < map->tileSize; ++k) {
                                const int off = index * map->tileSize + k;
                                if (map->slopes[off] != 0) {
                                    map->slopes[off] = 0;
                                    changed = true;
                                }
                            }
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
        if (collisionBrush >= 0 && collisionPlacementAt(*map, tx, ty) < 0) {
            // A normal collision brush may paint empty cells, but cannot
            // destroy an installed point-defined collision stamp.
            const char value = char(erase ? 0 : collisionBrush);
            if (map->collisions.at(index) != value) {
                map->collisions[index] = value;
                changed = true;
            }
            for (int k = 0; k < map->tileSize; ++k) {
                const int off = index * map->tileSize + k;
                if (map->slopes[off] != 0) { map->slopes[off] = 0; changed = true; }
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
        QVector<int> owners;
        if (showCollisions && !map->collisionPlacements.isEmpty()) {
            owners.fill(-1, map->width * map->height);
            for (int n = 0; n < map->collisionPlacements.size(); ++n) {
                const auto &place = map->collisionPlacements.at(n);
                if (place.stamp < 0 || place.stamp >= map->collisionStamps.size()) continue;
                const auto &shape = map->collisionStamps.at(place.stamp);
                for (int yy = place.y; yy < place.y + shape.height; ++yy)
                    for (int xx = place.x; xx < place.x + shape.width; ++xx)
                        owners[yy * map->width + xx] = n;
            }
        }
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
                painter.drawImage(dest, (flip & 3) ? tileImage.flipped(Qt::Orientations(static_cast<Qt::Orientation>(flip & 3))) : tileImage);
            } else if (tile) {
                painter.fillRect(dest, QColor(84, 90, 105));
                painter.setPen(Qt::white);
                painter.drawText(dest, Qt::AlignCenter, QString::number(tile));
            }
            if ((quint8(map->flips.at(i)) & 4u) && tile) {
                // Outline the front-render marker for legibility over detailed tiles.
                painter.save();
                painter.setRenderHint(QPainter::Antialiasing, true);
                QFont markerFont = painter.font();
                markerFont.setWeight(QFont::DemiBold);
                markerFont.setPixelSize(qBound(8, qMin(dest.width(), dest.height()) - 2, 16));
                const QFontMetricsF fm(markerFont);
                QPainterPath letter;
                letter.addText(QPointF(dest.left() + 1, dest.top() + 1 + fm.ascent()),
                               markerFont, QStringLiteral("F"));
                painter.setBrush(Qt::NoBrush);
                painter.setPen(QPen(Qt::black, dest.width() < 12 ? 1.0 : 1.6,
                                    Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                painter.drawPath(letter);
                // Bright fill AFTER the outline remains legible on any IDE theme.
                painter.setPen(Qt::NoPen);
                painter.setBrush(QColor(255, 255, 225));
                painter.drawPath(letter);
                painter.restore();
            }
            if (showCollisions) {
                const unsigned type = quint8(map->collisions.at(i));
                if (type == 7 && map->slopes.size() >= (i + 1) * map->tileSize) {
                    const int count = map->tileSize;
                    QPolygonF polygon;
                    for (int k = 0; k < count; ++k)
                        polygon << QPointF(dest.left() + (k + 0.5) * zoom,
                                           dest.top() + quint8(map->slopes.at(i * count + k)) * zoom);
                    painter.setPen(QPen(QColor(61, 255, 201), 2));
                    painter.drawPolyline(polygon);
                } else if (type == 8) {
                    const int placement = owners.isEmpty() ? -1 : owners.at(i);
                    if (placement >= 0) {
                        const auto &p = map->collisionPlacements.at(placement);
                        const auto &shape = map->collisionStamps.at(p.stamp);
                        QPolygonF line;
                        for (int k = 0; k <= map->tileSize; ++k) {
                            const int localX = (x - p.x) * map->tileSize + k;
                            const int surface = slopeY(shape, localX, p.mirrorX);
                            line << QPointF(dest.left() + k * zoom,
                                (p.y * map->tileSize + surface) * zoom - scrollY);
                        }
                        painter.save();
                        painter.setClipRect(dest);
                        painter.setPen(QPen(QColor(61, 255, 201), 2));
                        painter.drawPolyline(line);
                        painter.restore();
                    }
                } else if (type) {
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
            // Old v3 per-pixel slopes can be almost invisible at 8x8.
            // Mark them distinctly so they can be found and replaced without
            // altering the graphic or collision data.
            if (showCollisions && quint8(map->collisions.at(i)) == 7) {
                painter.setPen(QPen(QColor(255, 60, 194), 2));
                painter.setBrush(Qt::NoBrush);
                painter.drawRect(dest.adjusted(1, 1, -2, -2));
                if (px >= 18) {
                    painter.setPen(QColor(255, 255, 255));
                    painter.drawText(dest, Qt::AlignCenter, QStringLiteral("L"));
                }
            } else {
                painter.setPen(QColor(128, 157, 175, 68));
                painter.drawRect(dest.adjusted(0, 0, -1, -1));
            }
        }
        // Tracks are level-only objects. Show their collision centreline
        // independently of ordinary walkable slopes and painted tiles.
        if (showCollisions) for (const SidboxLoopTrack &track : map->loops) {
            const QPoint centre(track.centerX*zoom-scrollX,
                                track.centerY*zoom-scrollY);
            const int r=track.radius*zoom;
            if (!QRect(centre.x()-r,centre.y()-r,2*r,2*r).intersects(dirty)) continue;
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(QColor(117, 138, 255), 2, Qt::DashLine));
            painter.drawEllipse(centre,r,r);
            // Red ticks indicate surface normals, as in the loop sketch.
            static const QPointF directions[] = {
                {1,0},{0.7071,0.7071},{0,1},{-0.7071,0.7071},
                {-1,0},{-0.7071,-0.7071},{0,-1},{0.7071,-0.7071}
            };
            painter.setPen(QPen(QColor(252, 85, 69), 2));
            for (const QPointF &n : directions) {
                const QPointF c(centre);
                painter.drawLine(c + n*(r-5), c + n*(r+5));
            }
            painter.setPen(QPen(QColor(255, 206, 67), 2));
            painter.drawEllipse(QPoint(centre.x(),centre.y()+r),4,4);
            painter.drawText(QPoint(centre.x()+6,centre.y()+r-5),
                             QStringLiteral("LOOP"));
        }
        if (loopEditMode && selectedLoop >= 0 && selectedLoop < map->loops.size()) {
            const auto &track = map->loops.at(selectedLoop);
            const QPoint c(track.centerX*zoom-scrollX,track.centerY*zoom-scrollY);
            const QPoint edge(c.x()+track.radius*zoom,c.y());
            painter.setPen(QPen(QColor(255,255,255),2));
            painter.setBrush(QColor(60,230,200));
            painter.drawRect(QRect(c-QPoint(5,5),QSize(11,11)));
            painter.setBrush(QColor(255,194,63));
            painter.drawEllipse(edge,6,6);
        }
        paintBrushPreview(painter);
        // Draw last: the translucent reference sits above graphics/collision
        // previews but is NEVER written to the map and has no game-world state.
        const QRect playerRect = playerReferenceRect();
        if (!playerRect.isEmpty() && playerRect.intersects(dirty)) {
            painter.save();
            painter.setClipRect(viewport()->rect());
            painter.setOpacity(0.85);
            painter.drawImage(playerRect, playerReference);
            painter.setOpacity(1.0);
            if (showPlayerCollision) {
                const QRect box = playerHitboxWorldRect();
                const int tile = map->tileSize;
                const int firstX = qMax(0, box.left() / tile);
                const int firstY = qMax(0, box.top() / tile);
                const int lastX = qMin(map->width - 1, box.right() / tile);
                const int lastY = qMin(map->height - 1, box.bottom() / tile);
                int status = 0;
                for (int ty = firstY; ty <= lastY; ++ty)
                    for (int tx = firstX; tx <= lastX; ++tx) {
                        const int contact = playerCellContact(tx, ty, box);
                        if (!contact) continue;
                        // Blocking takes priority, then hazard, then one-way.
                        if (contact == 1 || !status || (contact == 2 && status != 1) ||
                            (contact == 3 && status == 4)) status = contact;
                        const QRect tileWorld(tx * tile, ty * tile, tile, tile);
                        const QRect area = box.intersected(tileWorld);
                        const QRect visible(area.x() * zoom - scrollX,
                                            area.y() * zoom - scrollY,
                                            area.width() * zoom, area.height() * zoom);
                        const QColor mark = contact == 1 ? QColor(255, 74, 83)
                            : contact == 2 ? QColor(255, 149, 35)
                            : contact == 3 ? QColor(255, 224, 75)
                            : QColor(99, 180, 255);
                        painter.fillRect(visible, QColor(mark.red(), mark.green(), mark.blue(), 95));
                        painter.setPen(QPen(mark, 2));
                        painter.setBrush(Qt::NoBrush);
                        painter.drawRect(visible.adjusted(0, 0, -1, -1));
                    }
                const QColor border = status == 1 ? QColor(255, 74, 83)
                    : status == 2 ? QColor(255, 149, 35)
                    : status == 3 ? QColor(255, 224, 75)
                    : status == 4 ? QColor(99, 180, 255)
                    : QColor(64, 240, 142);
                const QRect hitView(box.x() * zoom - scrollX, box.y() * zoom - scrollY,
                                    box.width() * zoom, box.height() * zoom);
                painter.setBrush(Qt::NoBrush);
                painter.setPen(QPen(border, 2));
                painter.drawRect(hitView.adjusted(0, 0, -1, -1));
                const QString info = status == 1 ? QStringLiteral("BLOCKED")
                    : status == 2 ? QStringLiteral("HAZARD")
                    : status == 3 ? QStringLiteral("ONE-WAY")
                    : status == 4 ? QStringLiteral("ZONE / DOOR")
                    : QStringLiteral("CLEAR");
                const QFontMetrics hitFont(painter.font());
                const QRect infoRect(playerRect.left(),
                    qMin(viewport()->height() - hitFont.height() - 4, playerRect.bottom() + 3),
                    hitFont.horizontalAdvance(info) + 10, hitFont.height() + 3);
                painter.fillRect(infoRect, palette().color(QPalette::Base));
                painter.setPen(border);
                painter.drawText(infoRect.adjusted(5, 0, 0, 0), Qt::AlignVCenter, info);
            }
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(palette().color(QPalette::Highlight), 2, Qt::DashLine));
            painter.drawRect(playerRect.adjusted(0, 0, -1, -1));
            const QString label = QStringLiteral("PLAYER REFERENCE");
            QFontMetrics fm(painter.font());
            const QRect textRect(playerRect.left(), qMax(0, playerRect.top() - fm.height() - 2),
                                 fm.horizontalAdvance(label) + 8, fm.height() + 2);
            painter.fillRect(textRect, palette().color(QPalette::Base));
            painter.setPen(palette().color(QPalette::Text));
            painter.drawText(textRect.adjusted(4, 0, 0, 0), Qt::AlignVCenter, label);
            painter.restore();
        }
        if (selectingRegion) {
            const QRect selected = regionRect();
            const QRect outline(selected.x() * px - scrollX,
                                selected.y() * px - scrollY,
                                selected.width() * px, selected.height() * px);
            painter.fillRect(outline, QColor(65, 236, 201, 55));
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(QColor(76, 255, 223), 2));
            painter.drawRect(outline.adjusted(1, 1, -2, -2));
        }
        if (showCollisions && legacyFocusCell.x() >= 0 && legacyFocusCell.y() >= 0 &&
            legacyFocusCell.x() < map->width && legacyFocusCell.y() < map->height &&
            quint8(map->collisions.at(legacyFocusCell.y() * map->width + legacyFocusCell.x())) == 7) {
            const QRect focus(legacyFocusCell.x() * px - scrollX,
                              legacyFocusCell.y() * px - scrollY, px, px);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(QColor(255, 45, 194), 3));
            painter.drawRect(focus.adjusted(-2, -2, 1, 1));
        }
    }
    bool viewportEvent(QEvent *event) override
    {
        if (event->type() == QEvent::Leave) {
            if (!draggingPlayerReference && !panning)
                viewport()->setCursor(loopEditMode ? Qt::ArrowCursor : Qt::CrossCursor);
            const QRect previous = previewBounds();
            hoverValid = false;
            if (!previous.isEmpty()) viewport()->update(previous);
            if (hoveredCellChanged) hoveredCellChanged();
        }
        return QAbstractScrollArea::viewportEvent(event);
    }
    void mousePressEvent(QMouseEvent *e) override
    {
        if (!map) return;
        // Focus the canvas even when clicking loop anchors or empty map space.
        if (e->button() == Qt::LeftButton || e->button() == Qt::MiddleButton ||
            e->button() == Qt::RightButton) setFocus(Qt::MouseFocusReason);
        if (e->button() == Qt::LeftButton && !temporaryActive &&
            !(e->modifiers() & (Qt::ShiftModifier | Qt::AltModifier)) &&
            playerReferenceRect().contains(e->position().toPoint())) {
            draggingPlayerReference = true;
            const QPoint pos = e->position().toPoint();
            playerReferenceDragOffset = QPoint(
                (pos.x() + horizontalScrollBar()->value()) / zoom,
                (pos.y() + verticalScrollBar()->value()) / zoom) - playerReferencePosition();
            if (strokeStarted) strokeStarted();
            viewport()->setCursor(Qt::ClosedHandCursor);
            e->accept(); return; // never paint when grabbing the reference
        }
        if (loopEditMode && e->button() == Qt::LeftButton &&
            selectedLoop >= 0 && selectedLoop < map->loops.size()) {
            const auto &l=map->loops.at(selectedLoop);
            const QPoint mouse=e->position().toPoint();
            const QPoint c(l.centerX*zoom-horizontalScrollBar()->value(),
                           l.centerY*zoom-verticalScrollBar()->value());
            const QPoint radiusHandle=c+QPoint(l.radius*zoom,0);
            if ((mouse-radiusHandle).manhattanLength() <= 18) loopDragKind=2;
            else if ((mouse-c).manhattanLength() <= 18) loopDragKind=1;
            if (loopDragKind) {
                loopDragOffset=mouse-c;
                if (strokeStarted) strokeStarted();
                viewport()->setCursor(Qt::ClosedHandCursor);
                e->accept(); return;
            }
        }
        if (loopEditMode && (e->button() == Qt::LeftButton ||
                             e->button() == Qt::RightButton)) {
            e->accept(); return; // Anchors only; no tile painting or erasure.
        }
        if (e->button() == Qt::LeftButton &&
            (e->modifiers() & Qt::ShiftModifier) && !(e->modifiers() & Qt::AltModifier)) {
            setFocus();
            selectingRegion = true;
            regionStart = regionEnd = cellAt(e->position().toPoint());
            viewport()->update();
            e->accept();
            return;
        }
        if (e->button() == Qt::MiddleButton ||
            (e->button() == Qt::LeftButton && e->modifiers() & Qt::AltModifier)) {
            const QRect previous = previewBounds();
            panning = true; lastPan = e->position().toPoint();
            if (!previous.isEmpty()) viewport()->update(previous);
            viewport()->setCursor(Qt::ClosedHandCursor);
            e->accept(); return;
        }
        if (temporaryActive) {
            setFocus();
            updateHover(e->position().toPoint());
            if (e->button() == Qt::LeftButton) {
                draggingTemporary = true;
                temporaryAnchor = hoverCell;
                e->accept(); return;
            }
            if (e->button() == Qt::RightButton) {
                applyTemporary(true);
                e->accept(); return;
            }
        }
        if (e->button() == Qt::LeftButton || e->button() == Qt::RightButton) {
            setFocus();
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
        if (draggingPlayerReference && map) {
            const QPoint pos = e->position().toPoint();
            const QSize size = playerReferenceWorldSize();
            const int x = (pos.x() + horizontalScrollBar()->value()) / zoom
                - playerReferenceDragOffset.x();
            const int y = (pos.y() + verticalScrollBar()->value()) / zoom
                - playerReferenceDragOffset.y();
            map->referencePlayerPositionSet = true;
            map->referencePlayerX = qBound(0, x, qMax(0, map->width * map->tileSize - size.width()));
            map->referencePlayerY = qBound(0, y, qMax(0, map->height * map->tileSize - size.height()));
            viewport()->update();
            e->accept(); return;
        }
        if (!panning && !painting && !selectingRegion && !temporaryActive && !loopDragKind &&
            playerReferenceRect().contains(e->position().toPoint())) {
            viewport()->setCursor(Qt::OpenHandCursor);
            e->accept(); return;
        }
        if (loopDragKind && selectedLoop >= 0 && selectedLoop < map->loops.size()) {
            auto &l=map->loops[selectedLoop];
            const QPoint pos=e->position().toPoint();
            const int maxX=map->width*map->tileSize;
            const int maxY=map->height*map->tileSize;
            if (loopDragKind == 1) {
                const QPoint centre=pos-loopDragOffset;
                l.centerX=qBound(l.radius,(centre.x()+horizontalScrollBar()->value()+zoom/2)/zoom,maxX-l.radius-1);
                l.centerY=qBound(l.radius,(centre.y()+verticalScrollBar()->value()+zoom/2)/zoom,maxY-l.radius-1);
            } else {
                const int x=(pos.x()+horizontalScrollBar()->value()+zoom/2)/zoom;
                const int limit=qMin(512,qMin(qMin(l.centerX,maxX-l.centerX-1),
                                              qMin(l.centerY,maxY-l.centerY-1)));
                l.radius=qBound(16,x-l.centerX,qMax(16,limit));
            }
            viewport()->update();
            if (loopEdited) loopEdited();
            e->accept(); return;
        }
        if (loopEditMode && !panning) {
            // Editing a loop is not painting. Show an ordinary arrow except
            // directly over the centre and radius drag handles.
            Qt::CursorShape cursor = Qt::ArrowCursor;
            if (selectedLoop >= 0 && selectedLoop < map->loops.size()) {
                const auto &l = map->loops.at(selectedLoop);
                const QPoint mouse = e->position().toPoint();
                const QPoint centre(l.centerX*zoom-horizontalScrollBar()->value(),
                                    l.centerY*zoom-verticalScrollBar()->value());
                const QPoint edge = centre + QPoint(l.radius*zoom, 0);
                if ((mouse-centre).manhattanLength() <= 18 ||
                    (mouse-edge).manhattanLength() <= 18)
                    cursor = Qt::OpenHandCursor;
            }
            viewport()->setCursor(cursor);
            e->accept(); return;
        }
        if (selectingRegion) {
            regionEnd = cellAt(e->position().toPoint());
            viewport()->update();
        } else if (panning) {
            const QPoint at = e->position().toPoint();
            horizontalScrollBar()->setValue(horizontalScrollBar()->value() + lastPan.x() - at.x());
            verticalScrollBar()->setValue(verticalScrollBar()->value() + lastPan.y() - at.y());
            lastPan = at;
        } else if (temporaryActive) {
            updateHover(e->position().toPoint());
        } else if (painting && e->buttons() & (Qt::LeftButton | Qt::RightButton)) {
            const QRect previous = previewBounds();
            paintAt(e->position().toPoint(), erasingStroke);
            updateHover(e->position().toPoint());
            viewport()->update(previous);
            viewport()->update(previewBounds());
        } else if (!panning) {
            viewport()->setCursor(Qt::CrossCursor);
            updateHover(e->position().toPoint());
        }
    }
    void mouseReleaseEvent(QMouseEvent *e) override
    {
        if (draggingPlayerReference && e->button() == Qt::LeftButton) {
            draggingPlayerReference = false;
            viewport()->setCursor(Qt::OpenHandCursor);
            if (strokeFinished) strokeFinished();
            e->accept(); return;
        }
        if (loopDragKind && e->button() == Qt::LeftButton) {
            loopDragKind=0;
            viewport()->setCursor(Qt::OpenHandCursor);
            if (strokeFinished) strokeFinished();
            if (loopEdited) loopEdited();
            e->accept(); return;
        }
        if (selectingRegion && e->button() == Qt::LeftButton) {
            regionEnd = cellAt(e->position().toPoint());
            selectingRegion = false;
            if (regionStart != regionEnd) {
                copyRegion(regionRect());
                updateHover(e->position().toPoint());
            } else {
                // Preserve Stage 3.37 Shift-click to edit an existing slope.
                const int placement = collisionPlacementAt(*map, regionStart.x(), regionStart.y());
                if (placement >= 0 && editPlacedCollision)
                    editPlacedCollision(map->collisionPlacements.at(placement).stamp);
            }
            viewport()->update();
            e->accept(); return;
        }
        if (temporaryActive && e->button() == Qt::LeftButton && draggingTemporary) {
            draggingTemporary = false;
            updateHover(e->position().toPoint());
            // Drag = position the temporary brush. A stationary click pastes;
            // Escape discards the temporary brush without another paste.
            if (temporaryAnchor == hoverCell) applyTemporary(false);
            e->accept(); return;
        }
        const QRect previous = previewBounds();
        if (e->button() == Qt::MiddleButton || e->button() == Qt::LeftButton) {
            panning = false;
            viewport()->setCursor(loopEditMode ? Qt::ArrowCursor : Qt::CrossCursor);
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
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Escape && temporaryActive) {
            deactivateTemporary();
            event->accept();
            return;
        }
        if ((event->modifiers() & Qt::KeypadModifier) &&
            (event->key() == Qt::Key_Plus || event->key() == Qt::Key_Minus)) {
            setZoom(zoom + (event->key() == Qt::Key_Plus ? 1 : -1),
                    keyboardZoomAnchor());
            event->accept();
            return;
        }
        QAbstractScrollArea::keyPressEvent(event);
    }
    void wheelEvent(QWheelEvent *e) override
    {
        // A vertical wheel notch changes zoom; its position anchors the map.
        // Keep touchpad pixel scrolling and horizontal-wheel behaviour intact.
        const int deltaY = e->angleDelta().y();
        if (!deltaY) {
            QAbstractScrollArea::wheelEvent(e);
            return;
        }
        zoomWheelRemainder += deltaY;
        const int notches = zoomWheelRemainder / 120;
        zoomWheelRemainder -= notches * 120;
        if (notches) setZoom(zoom + notches, e->position().toPoint());
        // Wheel interaction also focuses the map for subsequent numpad +/-.
        setFocus(Qt::MouseFocusReason);
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
                    painter.drawImage(cell, (flip & 3) ? tileImage.flipped(Qt::Orientations(static_cast<Qt::Orientation>(flip & 3))) : tileImage);
                } else if (tile) {
                    painter.fillRect(cell, QColor(84, 90, 105));
                    painter.setPen(Qt::white);
                    painter.drawText(cell, Qt::AlignCenter, QString::number(tile));
                }
                if (quint8(stamp.flips.at(i)) & 4u) {
                    painter.save();
                    painter.setRenderHint(QPainter::Antialiasing, true);
                    QFont markerFont = painter.font();
                    markerFont.setWeight(QFont::DemiBold);
                    markerFont.setPixelSize(qBound(8, qMin(cell.width(), cell.height()) - 2, 16));
                    const QFontMetricsF fm(markerFont);
                    QPainterPath letter;
                    letter.addText(QPointF(cell.left() + 1, cell.top() + 1 + fm.ascent()),
                                   markerFont, QStringLiteral("F"));
                    painter.setBrush(Qt::NoBrush);
                    painter.setPen(QPen(Qt::black, cell.width() < 12 ? 1.0 : 1.6,
                                        Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
                    painter.drawPath(letter);
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QColor(255, 255, 225));
                    painter.drawPath(letter);
                    painter.restore();
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
                painter.drawImage(target, (flip & 3) ? tile.flipped(Qt::Orientations(static_cast<Qt::Orientation>(flip & 3))) : tile);
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

// Collision-only surface editor: point-defined shared shapes over faded artwork.
// This edits the selected shape definition, never the graphics or tile atlas.
class SidboxTilemapEditor::CollisionCanvas final : public QWidget
{
public:
    SidboxTilemap *map = nullptr;
    QImage *atlas = nullptr;
    int selected = -1;
    int referenceStamp = -1; // last selected graphical stamp
    bool dragging = false;
    bool changed = false;
    int active = -1;
    // Collision editing has its own full-height workspace. The larger grid
    // makes dragging control points practical even for small 2x2 stamps.
    static constexpr int gridUnit = 96;
    std::function<void()> strokeStarted;
    std::function<void()> modified;
    std::function<void()> pointSelected;
    explicit CollisionCanvas(QWidget *parent = nullptr) : QWidget(parent) {
        setCursor(Qt::CrossCursor);
        setMouseTracking(true);
        setMinimumSize(220, 220);
    }
    void refresh() {
        if (!map || selected < 0 || selected >= map->collisionStamps.size())
            setFixedSize(220, 220);
        else {
            const auto &s = map->collisionStamps.at(selected);
            setFixedSize(qMax(220, s.width * gridUnit + 1),
                         qMax(220, s.height * gridUnit + 1));
        }
        update();
    }
    QPoint pixelPoint(const QPoint &p, const SidboxCollisionStamp &s) const {
        return QPoint(qBound(0, qRound(double(p.x()) * s.tileSize / gridUnit), s.width * s.tileSize),
                      qBound(0, qRound(double(p.y()) * s.tileSize / gridUnit), s.height * s.tileSize));
    }
    void paintEvent(QPaintEvent *) override {
        QPainter painter(this);
        painter.fillRect(rect(), QColor(28, 37, 49));
        if (!map || selected < 0 || selected >= map->collisionStamps.size()) {
            painter.setPen(Qt::white);
            painter.drawText(rect(), Qt::AlignCenter, tr("Add or select a collision stamp"));
            return;
        }
        const auto &s = map->collisionStamps.at(selected);
        const int unit = gridUnit, size = s.tileSize;
        const int cols = atlas && !atlas->isNull() ? atlas->width() / size : 0;
        const int rows = atlas && !atlas->isNull() ? atlas->height() / size : 0;
        if (referenceStamp >= 0 && referenceStamp < map->stamps.size() &&
            map->stamps.at(referenceStamp).tileSize == size) {
            const auto &ref = map->stamps.at(referenceStamp);
            painter.save(); painter.setOpacity(0.26);
            painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
            for (int y = 0; y < qMin(s.height, ref.height); ++y)
                for (int x = 0; x < qMin(s.width, ref.width); ++x) {
                    const int i = y * ref.width + x;
                    const int id = mapGraphic(ref.graphics, i);
                    if (!id || id > cols * rows || !cols) continue;
                    const int n = id - 1;
                    const QImage tile = atlas->copy((n % cols) * size,
                        (n / cols) * size, size, size);
                    const int f = quint8(ref.flips.at(i));
                    painter.drawImage(QRect(x * unit, y * unit, unit, unit),
                        (f & 3) ? tile.flipped(Qt::Orientations(static_cast<Qt::Orientation>(f & 3))) : tile);
                }
            painter.restore();
        }
        painter.setPen(QPen(QColor(130, 163, 180, 95), 1));
        for (int x = 0; x <= s.width; ++x)
            painter.drawLine(x * unit, 0, x * unit, s.height * unit);
        for (int y = 0; y <= s.height; ++y)
            painter.drawLine(0, y * unit, s.width * unit, y * unit);
        QPolygonF line;
        for (const QPoint &p : s.points)
            line << QPointF(p.x() * unit / size, p.y() * unit / size);
        if (line.size() >= 2) {
            QPolygonF fill = line;
            fill << QPointF(s.width * unit, s.height * unit)
                 << QPointF(0, s.height * unit);
            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(35, 194, 158, 95));
            painter.drawPolygon(fill);
            painter.setBrush(Qt::NoBrush);
            painter.setPen(QPen(QColor(67, 250, 205), 2));
            painter.drawPolyline(line);
        }
        for (int i = 0; i < s.points.size(); ++i) {
            const QPoint p = s.points.at(i) * unit / size;
            painter.setPen(QPen(i == active ? Qt::white : QColor(67,250,205), 2));
            painter.setBrush(QColor(27, 48, 56));
            painter.drawEllipse(QPointF(p), i == active ? 6 : 4, i == active ? 6 : 4);
        }
    }
    void movePoint(const QPoint &mouse) {
        if (!dragging || !map || selected < 0 || selected >= map->collisionStamps.size()) return;
        auto &s = map->collisionStamps[selected];
        if (active < 0 || active >= s.points.size()) return;
        QPoint p = pixelPoint(mouse, s);
        if (active == 0) p.setX(0);
        else if (active == s.points.size() - 1) p.setX(s.width * s.tileSize);
        else {
            const int lo = s.points.at(active - 1).x() + 1;
            const int hi = s.points.at(active + 1).x() - 1;
            p.setX(lo <= hi ? qBound(lo, p.x(), hi) : s.points.at(active).x());
        }
        if (s.points.at(active) != p) {
            s.points[active] = p;
            changed = true;
            update();
        }
    }
    void mousePressEvent(QMouseEvent *event) override {
        if (!map || selected < 0 || selected >= map->collisionStamps.size()) return;
        auto &s = map->collisionStamps[selected];
        if (s.tileSize != map->tileSize) return;
        const QPoint pt = pixelPoint(event->position().toPoint(), s);
        int nearest = -1, closest = 7 * 7;
        for (int i = 0; i < s.points.size(); ++i) {
            const QPoint delta = s.points.at(i) - pt;
            const int distance = (delta.x()*delta.x()+delta.y()*delta.y()) * gridUnit * gridUnit /
                                 (s.tileSize*s.tileSize);
            if (distance <= closest) { nearest = i; closest = distance; }
        }
        if (event->button() == Qt::RightButton) {
            if (nearest > 0 && nearest < s.points.size() - 1) {
                if (strokeStarted) strokeStarted();
                s.points.removeAt(nearest);
                active = -1; update();
                if (modified) modified();
                if (pointSelected) pointSelected();
            }
            return;
        }
        if (event->button() != Qt::LeftButton) return;
        setFocus(Qt::MouseFocusReason);
        if (strokeStarted) strokeStarted();
        changed = false;
        if (nearest < 0 && s.points.size() < 128) {
            int insert = 1;
            while (insert < s.points.size() && s.points.at(insert).x() < pt.x()) ++insert;
            if (insert < s.points.size() && pt.x() > s.points.at(insert - 1).x() &&
                pt.x() < s.points.at(insert).x()) {
                s.points.insert(insert, pt);
                nearest = insert;
                changed = true;
            }
        }
        active = nearest;
        dragging = active >= 0;
        if (pointSelected) pointSelected();
        movePoint(event->position().toPoint());
        update();
    }
    void mouseMoveEvent(QMouseEvent *event) override {
        if (dragging && (event->buttons() & Qt::LeftButton))
            movePoint(event->position().toPoint());
    }
    void mouseReleaseEvent(QMouseEvent *event) override {
        if (event->button() != Qt::LeftButton || !dragging) return;
        movePoint(event->position().toPoint());
        dragging = false;
        if (changed && modified) modified();
        if (pointSelected) pointSelected();
    }
};

// One mouse paint stroke is one history entry; resizing and animation edits
// also create entries. Qt's implicitly shared QByteArrays keep this practical.
static bool sameTilemap(const SidboxTilemap &a, const SidboxTilemap &b)
{
    if (a.width != b.width || a.height != b.height || a.tileSize != b.tileSize
        || a.atlasPath != b.atlasPath || a.graphics != b.graphics
        || a.collisions != b.collisions || a.customZoneNames != b.customZoneNames
        || a.animations.size() != b.animations.size()
        || a.stamps.size() != b.stamps.size() || a.flips != b.flips
        || a.slopes != b.slopes || a.collisionStamps.size() != b.collisionStamps.size()
        || a.collisionPlacements.size() != b.collisionPlacements.size()
        || a.loops.size() != b.loops.size()
        || a.referencePlayerPositionSet != b.referencePlayerPositionSet
        || (a.referencePlayerPositionSet &&
            (a.referencePlayerX != b.referencePlayerX || a.referencePlayerY != b.referencePlayerY)))
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
    for (int i = 0; i < a.collisionStamps.size(); ++i) {
        const auto &left = a.collisionStamps.at(i);
        const auto &right = b.collisionStamps.at(i);
        if (left.name != right.name || left.width != right.width ||
            left.height != right.height || left.tileSize != right.tileSize ||
            left.points != right.points || left.passiveSurface != right.passiveSurface ||
            left.dampingPercent != right.dampingPercent) return false;
    }
    for (int i = 0; i < a.loops.size(); ++i) {
        const auto &l=a.loops.at(i), &r=b.loops.at(i);
        if (l.centerX!=r.centerX || l.centerY!=r.centerY ||
            l.radius!=r.radius || l.entrySpeed100!=r.entrySpeed100 ||
            l.downhillBoost100!=r.downhillBoost100 ||
            l.coastAfterExit!=r.coastAfterExit ||
            l.coastFalloffPermille!=r.coastFalloffPermille) return false;
    }
    for (int i = 0; i < a.collisionPlacements.size(); ++i) {
        const auto &left = a.collisionPlacements.at(i);
        const auto &right = b.collisionPlacements.at(i);
        if (left.stamp != right.stamp || left.x != right.x ||
            left.y != right.y || left.mirrorX != right.mirrorX) return false;
    }
    return true;
}

void SidboxTilemapEditor::updateHistoryActions()
{
    if (m_undoButton) m_undoButton->setEnabled(!m_undoStack.isEmpty());
    if (m_redoButton) m_redoButton->setEnabled(!m_redoStack.isEmpty());
}

void SidboxTilemapEditor::updateCellStatus()
{
    if (!m_cellStatus || !m_canvas || !m_canvas->hoverValid) {
        if (m_cellStatus) m_cellStatus->setText(tr("Col: —  Row: —"));
        return;
    }
    const int x = m_canvas->hoverCell.x();
    const int y = m_canvas->hoverCell.y();
    if (x < 0 || x >= m_map.width || y < 0 || y >= m_map.height) {
        m_cellStatus->setText(tr("Col: —  Row: —"));
        return;
    }
    const quint8 type = quint8(m_map.collisions.at(y * m_map.width + x));
    const QString collision = type == 7 ? tr("LEGACY SLOPE")
        : type == 8 ? tr("Point slope")
        : type == 0 ? tr("Empty") : tr("Collision %1").arg(type);
    m_cellStatus->setText(tr("Col: %1  Row: %2  |  %3").arg(x).arg(y).arg(collision));
}

void SidboxTilemapEditor::updateLegacyStatus()
{
    if (!m_findLegacyButton) return;
    const int count = m_map.collisions.count(char(7));
    m_findLegacyButton->setText(tr("Find Legacy (%1)").arg(count));
    m_findLegacyButton->setEnabled(count > 0);
    if (!count) m_lastLegacyIndex = -1;
    updateCellStatus();
}

void SidboxTilemapEditor::recordChange(const SidboxTilemap &before)
{
    if (sameTilemap(before, m_map)) return;
    // QByteArrays share unchanged snapshots, but slope edits can copy the
    // dense per-cell legacy data. Limit worst-case history for huge maps.
    const qint64 bytesPerMap = qint64(before.graphics.size()) +
        before.collisions.size() + before.flips.size() + before.slopes.size();
    const int maxHistory = qBound(4, int((64ll * 1024 * 1024) /
        qMax<qint64>(1, bytesPerMap)), 64);
    while (m_undoStack.size() >= maxHistory) m_undoStack.removeFirst();
    m_undoStack.append(before);
    m_redoStack.clear();
    if (m_saveStatus) m_saveStatus->setText(tr("Unsaved changes"));
    updateHistoryActions();
    updateLegacyStatus();
}

void SidboxTilemapEditor::updateCustomZoneBrushLabels()
{
    if (!m_customZoneBrush) return;
    for (int i = 0; i < 8; ++i) {
        QString label = i < m_map.customZoneNames.size()
            ? m_map.customZoneNames.at(i).trimmed() : QString();
        if (label.isEmpty()) label = tr("Custom %1").arg(i+1);
        const int pass = m_customZoneBrush->findData(9+i);
        const int solid = m_customZoneBrush->findData(17+i);
        if (pass >= 0) m_customZoneBrush->setItemText(pass,
            tr("%1 — %2 (pass-through)").arg(9+i).arg(label));
        if (solid >= 0) m_customZoneBrush->setItemText(solid,
            tr("%1 — %2 (solid)").arg(17+i).arg(label));
    }
}

void SidboxTilemapEditor::restoreMap(const SidboxTilemap &snapshot)
{
    if (m_canvas && m_canvas->temporaryActive) m_canvas->deactivateTemporary();
    const bool atlasChanged = m_map.atlasPath != snapshot.atlasPath;
    m_map = snapshot;
    // Restore the original settings without firing edit-history callbacks.
    if (m_sizeX && m_sizeY) {
        QSignalBlocker blockX(m_sizeX), blockY(m_sizeY);
        m_sizeX->setMaximum(qMin(SIDBOX_MAP_MAX_AXIS,
                                 SIDBOX_MAP_MAX_CELLS / m_map.height));
        m_sizeY->setMaximum(qMin(SIDBOX_MAP_MAX_AXIS,
                                 SIDBOX_MAP_MAX_CELLS / m_map.width));
        m_sizeX->setValue(m_map.width);
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
    updateCollisionList();
    updateCustomZoneBrushLabels();
    if (m_saveStatus) m_saveStatus->setText(tr("Unsaved changes"));
    updateLegacyStatus();
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

void SidboxTilemapEditor::setPlayerReference(const QImage &spriteFrame,
    int scalePercent, const QPoint &worldPosition, const QRect &hitbox)
{
    if (!m_canvas || !m_playerReferenceToggle) return;
    m_canvas->playerReference = spriteFrame;
    m_canvas->playerHitbox = hitbox;
    m_canvas->playerReferenceScale = qBound(1, scalePercent, 1000);
    m_canvas->playerReferenceInitialPosition = worldPosition;
    const bool available = !spriteFrame.isNull();
    if (m_playerToolsDivider) m_playerToolsDivider->setVisible(available);
    m_playerReferenceToggle->setVisible(available);
    m_playerReferenceToggle->setChecked(available);
    if (m_playerCollisionToggle) {
        m_playerCollisionToggle->setVisible(available);
        m_canvas->showPlayerCollision = m_playerCollisionToggle->isChecked();
    }
    m_canvas->showPlayerReference = available;
    m_canvas->viewport()->update();
}

void SidboxTilemapEditor::setTheme(const IDETheme &theme)
{
    const auto C = [](const QColor &colour) { return ideThemeColorName(colour); };
    // Consistent, reusable editor controls shared with the World Designer.
    // This theme pass is presentation-only: the canvas and stamp previews
    // continue painting their own graphics and retain their input handling.
    // The editor dialog needs its own colours on KDE / Wayland.
    // All standard controls use the application-level IDE stylesheet.
    setStyleSheet(QString());
    QPalette dialogPalette = palette();
    dialogPalette.setColor(QPalette::Window, theme.windowBackground);
    dialogPalette.setColor(QPalette::WindowText, theme.text);
    dialogPalette.setColor(QPalette::Base, theme.inputBackground);
    dialogPalette.setColor(QPalette::Text, theme.text);
    dialogPalette.setColor(QPalette::Button, theme.panelBackground);
    dialogPalette.setColor(QPalette::ButtonText, theme.text);
    const QColor selectedBase = theme.accent.darker(230);
    const QColor selectedText = selectedBase.lightnessF() < 0.52
        ? QColor(Qt::white) : QColor(Qt::black);
    dialogPalette.setColor(QPalette::Highlight, selectedBase);
    dialogPalette.setColor(QPalette::HighlightedText, selectedText);
    setPalette(dialogPalette);
    // Checked buttons have a dark accent base; use its contrasting text
    // colour, not the ordinary (possibly dark-on-dark) glyph colour.
    // TilemapFlagButton deliberately has no Q_OBJECT macro: QObject::findChildren
    // cannot search for that subclass. The eight toolbar buttons are already
    // held by the editor, so apply their theme colours directly.
    for (QToolButton *tool : {m_flipX, m_flipY, m_stampMirrorX, m_stampMirrorY,
                              m_drawFront, m_stampUseFront,
                              m_playerReferenceToggle, m_playerCollisionToggle}) {
        if (!tool) continue;
        TilemapFlagButton *button = static_cast<TilemapFlagButton *>(tool);
        button->setGlyphColours(theme.text, selectedText);
    }
    for (QToolButton *tool : {m_graphicKeep, m_graphicEmpty, m_graphicAtlas,
                              m_collisionKeep, m_collisionEmpty,
                              m_flagApply, m_flagKeep}) {
        if (!tool) continue;
        static_cast<TilemapPaintButton *>(tool)->setGlyphColours(theme.text, selectedText);
    }

    // Stage 4.00: the three tilemap selection banks use the same bordered,
    // theme-accent cards as Game Object Properties. The item stylesheet is
    // applied to the LIST (rather than a generic QDialog rule), so native
    // icon-mode thumbnail painting and the selected row remain readable on
    // both light and dark IDE themes. No stamp/loop selection logic changes.
    const QColor selectionBackground = theme.accent.darker(230);
    const QColor selectionForeground = selectionBackground.lightnessF() < 0.52
        ? QColor(Qt::white) : QColor(Qt::black);
    const QString selectionStyle = QStringLiteral(R"GGSTAMP(
        QListWidget {
            background:%1; color:%2; border:1px solid %3;
            border-radius:0px; outline:0px;
        }
        QListWidget::item {
            background:%4; color:%2; border:1px solid %3;
            border-radius:0px; margin:2px; padding:4px;
        }
        QListWidget::item:selected {
            background:%5; color:%6; border:2px solid %7;
            border-left:3px solid %7; border-radius:0px;
        }
        QListWidget::item:hover:!selected {
            background:%8; border:1px solid %7;
            border-radius:0px;
        }
    )GGSTAMP")
        .arg(C(theme.panelBackground), C(theme.text), C(theme.border),
             C(theme.alternateBackground), C(selectionBackground),
             C(selectionForeground), C(theme.accent), C(theme.hover));
    for (QListWidget *bank : {m_stampList, m_collisionList,
                             findChild<QListWidget *>(QStringLiteral("GGLoopTrackBank"))}) {
        if (!bank) continue;
        bank->setPalette(dialogPalette);
        bank->setStyleSheet(selectionStyle);
    }

    // Popup lists inherit the application-wide palette and QSS. Do not
    // maintain a second KDE-specific per-dialog copy of those rules.

}

SidboxTilemapEditor::SidboxTilemapEditor(SidboxTilemap map,
    const QVector<QPair<QString, QString>> &atlases,
    const QString &designDirectory, QWidget *parent)
    : QDialog(parent), m_map(std::move(map)), m_designDirectory(designDirectory)
{
    if (m_map.slopes.size() != m_map.width * m_map.height * m_map.tileSize) {
        m_map.slopes = QByteArray(m_map.width * m_map.height * m_map.tileSize, char(0));
        for (char &type : m_map.collisions) if (quint8(type) == 7) type = 0;
    }
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
    sizeX->setRange(30, qMin(SIDBOX_MAP_MAX_AXIS,
                              SIDBOX_MAP_MAX_CELLS / m_map.height));
    sizeY->setRange(20, qMin(SIDBOX_MAP_MAX_AXIS,
                              SIDBOX_MAP_MAX_CELLS / m_map.width));
    sizeX->setToolTip(tr("Maximum %1 cells total. For a longer map, reduce Tiles Y first.")
                          .arg(SIDBOX_MAP_MAX_CELLS));
    sizeY->setToolTip(sizeX->toolTip());
    sizeX->setValue(m_map.width); sizeY->setValue(m_map.height);
    auto *tileSize = new TilemapComboBox(this);
    m_tileSizeCombo = tileSize;
    for (int s : {8, 16, 32}) tileSize->addItem(QString::number(s) + QStringLiteral(" px"), s);
    tileSize->setCurrentIndex(qMax(0, tileSize->findData(m_map.tileSize)));
    auto *zoom = new TilemapComboBox(this);
    for (int z = 1; z <= Canvas::maxZoom; ++z)
        zoom->addItem(QStringLiteral("%1×").arg(z), z);
    zoom->setCurrentIndex(qMax(0, zoom->findData(qBound(1,
        windowSettings.value(QStringLiteral("GameTilemapEditor/zoom"), 2).toInt(), Canvas::maxZoom))));
    auto *collisionOverlay = new QCheckBox(tr("Show collisions"), this);
    collisionOverlay->setChecked(true);
    collisionOverlay->setToolTip(tr("Show or hide the collision overlay while editing either layer."));

    // Map dimensions and zoom occupy the first row; paint flags and
    // collision settings share the next row, graphics live above the atlas.
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

    // Both layers are painted with one drag. Either brush can opt out.
    auto *brushC = new TilemapComboBox(this);
    m_customZoneBrush = brushC;
    for (const QPair<QString, int> &type : QVector<QPair<QString,int>>{
         {tr("Don't change collision"), -1},
         {tr("0 — Empty (no collision)"), 0}, {tr("1 — Solid"), 1},
         {tr("2 — One-way"), 2}, {tr("3 — Slope rising right"), 3},
         {tr("4 — Slope falling right"), 4}, {tr("5 — Hazard"), 5},
         {tr("6 — Door"), 6}})
        brushC->addItem(type.first, type.second);
    for (int i = 0; i < 8; ++i) {
        QString name = i < m_map.customZoneNames.size()
            ? m_map.customZoneNames.at(i).trimmed() : QString();
        if (name.isEmpty()) name = tr("Custom %1").arg(i+1);
        brushC->addItem(tr("%1 — %2 (pass-through)").arg(9+i).arg(name), 9+i);
        brushC->addItem(tr("%1 — %2 (solid)").arg(17+i).arg(name), 17+i);
    }
    brushC->setCurrentIndex(qMax(0, brushC->findData(
        windowSettings.value(QStringLiteral("GameTilemapEditor/collisionBrush"), -1).toInt())));
    auto *brushG = new TilemapComboBox(this);
    brushG->addItem(tr("Don't change graphic"), -1);
    brushG->addItem(tr("0 — Empty graphic"), 0);
    brushG->addItem(tr("Selected atlas tile (ID 1)"), 1);
    brushG->setCurrentIndex(qMax(0, brushG->findData(
        windowSettings.value(QStringLiteral("GameTilemapEditor/graphicMode"), 1).toInt())));
    m_graphicMode = brushG;
    brushG->hide(); // Internal state only: the three atlas toolbar buttons replace this dropdown.
    brushG->setToolTip(tr("Click a tile in the atlas on the left to select it. "
        "Choose Don't change graphic to paint collisions only."));
    brushC->setToolTip(tr("Choose Don't change collision to paint graphics only. "
        "Otherwise both layers are painted with one stroke."));
    // Collision brush moves into the same toolbar as the cell/stamp flags.
    // The graphics brush moves above the atlas, as an icon-only mode strip.
    auto *renameZone = new QPushButton(tr("Name Zone"), this);
    renameZone->setToolTip(tr("Name Custom 1–8. Export creates GAME_ZONE_ID_NAME macros in the exported world header; callback IDs stay 1–8."));
    auto *customSolid = new QCheckBox(tr("Custom is solid"), this);
    customSolid->setToolTip(tr("Blocking custom zones stop the player, but still report touch events. Pass-through zones do not block."));
    connect(brushC, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [brushC, renameZone, customSolid](int) {
            const int id = brushC->currentData().toInt();
            const bool isCustom = id >= 9 && id <= 24;
            renameZone->setVisible(isCustom);
            customSolid->setVisible(isCustom);
            renameZone->setEnabled(isCustom);
            customSolid->setEnabled(isCustom);
            const QSignalBlocker guard(customSolid);
            customSolid->setChecked(id >= 17 && id <= 24);
        });
    const bool hasCustomZone = brushC->currentData().toInt() >= 9 &&
                               brushC->currentData().toInt() <= 24;
    renameZone->setVisible(hasCustomZone);
    customSolid->setVisible(hasCustomZone);
    renameZone->setEnabled(hasCustomZone);
    customSolid->setEnabled(hasCustomZone);
    customSolid->setChecked(brushC->currentData().toInt() >= 17 && brushC->currentData().toInt() <= 24);
    connect(customSolid, &QCheckBox::toggled, this, [brushC](bool solid) {
        const int type = brushC->currentData().toInt();
        if (type < 9 || type > 24) return;
        const int zone = type <= 16 ? type - 9 : type - 17;
        brushC->setCurrentIndex(brushC->findData((solid ? 17 : 9) + zone));
    });
    connect(renameZone, &QPushButton::clicked, this, [this, brushC]() {
        const int selected = brushC->currentData().toInt();
        if (selected < 9 || selected > 24) return;
        const int zone = selected <= 16 ? selected - 9 : selected - 17;
        const QString previous = zone < m_map.customZoneNames.size()
            ? m_map.customZoneNames.at(zone) : QString();
        bool ok = false;
        const QString updated = QInputDialog::getText(this, tr("Name Custom Zone"),
            tr("Custom %1 (logical zone %1):").arg(zone+1), QLineEdit::Normal,
            previous, &ok).trimmed().left(32);
        if (!ok || previous == updated) return;
        const SidboxTilemap before = m_map;
        while (m_map.customZoneNames.size() < 8) m_map.customZoneNames.append(QString());
        m_map.customZoneNames[zone] = updated;
        updateCustomZoneBrushLabels();
        recordChange(before);
    });
    // Keep brushG as the internal source of truth for the existing paint,
    // atlas-click and QSettings code. It is intentionally not shown.
    // Stage 4.10: the flags and overlays are one compact, themed toolbar.
    // Buttons remain the very same bool switches used by the paint routines.
    auto *flipRow = new QHBoxLayout;
    flipRow->setSpacing(5);
    m_flipMode = new TilemapComboBox(this);
    m_flipMode->addItem(tr("Apply tile flags"), 1);
    m_flipMode->addItem(tr("Don't change tile flags"), -1);
    m_flipMode->setCurrentIndex(qMax(0, m_flipMode->findData(
        windowSettings.value(QStringLiteral("GameTilemapEditor/flipMode"), 1).toInt())));
    m_flipMode->setToolTip(tr("Apply cell flip and front-layer flags while painting, or preserve "
        "the flags already stored in each cell when painting collision data."));
    // Keep the original combo as the source of truth for painting and QSettings.
    // These two exclusive icon buttons are its visible toolbar controls.
    m_flipMode->hide();
    m_flagApply = new TilemapPaintButton(TilemapPaintButton::ApplyFlags,
        tr("Apply tile flags"), this);
    m_flagKeep = new TilemapPaintButton(TilemapPaintButton::KeepFlags,
        tr("Don't change tile flags"), this);
    m_flagApply->setToolTip(tr("Apply tile flags: use the selected cell X/Y and draw-front "
        "settings while painting."));
    m_flagKeep->setToolTip(tr("Don't change tile flags: keep the existing cell X/Y "
        "and front-render flags while painting."));
    flipRow->addWidget(m_flagApply);
    flipRow->addWidget(m_flagKeep);

    m_flipX = new TilemapFlagButton(TilemapFlagButton::CellX, tr("Cell Flip X"), this);
    m_flipY = new TilemapFlagButton(TilemapFlagButton::CellY, tr("Cell Flip Y"), this);
    m_stampMirrorX = new TilemapFlagButton(TilemapFlagButton::StampX, tr("Stamp Flip X"), this);
    m_stampMirrorY = new TilemapFlagButton(TilemapFlagButton::StampY, tr("Stamp Flip Y"), this);
    m_flipX->setToolTip(tr("Cell Flip X: mirror each painted tile horizontally (individual cell X flag)."));
    m_flipY->setToolTip(tr("Cell Flip Y: mirror each painted tile vertically (individual cell Y flag)."));
    m_stampMirrorX->setToolTip(tr("Stamp Flip X: mirror the entire stamp horizontally when placing it. "
        "Reverses cell order and combines each cell's X flip correctly."));
    m_stampMirrorY->setToolTip(tr("Stamp Flip Y: mirror the entire stamp vertically when placing it. "
        "Reverses cell order and combines each cell's Y flip correctly."));
    const int lastFlags = windowSettings.value(QStringLiteral("GameTilemapEditor/brushFlags"), 0).toInt();
    m_flipX->setChecked((lastFlags & 1) != 0);
    m_flipY->setChecked((lastFlags & 2) != 0);
    flipRow->addWidget(m_flipX);
    flipRow->addWidget(m_flipY);
    flipRow->addWidget(m_stampMirrorX);
    flipRow->addWidget(m_stampMirrorY);

    m_drawFront = new TilemapFlagButton(TilemapFlagButton::Front, tr("Draw in front of player"), this);
    m_stampUseFront = new TilemapFlagButton(TilemapFlagButton::StampFront,
                                           tr("Stamp: use draw front setting"), this);
    m_drawFront->setToolTip(tr("Draw in front of player: paint this tile in front of the player sprite. "
        "Collision is unchanged."));
    m_stampUseFront->setToolTip(tr("Stamp: use draw front setting. When on, the Draw in front of player "
        "button overrides front/back for every stamp cell. When off, each stamp cell "
        "uses its saved front/back flag. Individual X/Y flips are preserved."));
    m_drawFront->setChecked((lastFlags & 4) != 0);
    m_stampUseFront->setChecked(windowSettings.value(
        QStringLiteral("GameTilemapEditor/stampUseFront"), false).toBool());
    flipRow->addWidget(m_drawFront);
    flipRow->addWidget(m_stampUseFront);

    auto *collisionDivider = new QFrame(this);
    collisionDivider->setFrameShape(QFrame::VLine);
    collisionDivider->setFrameShadow(QFrame::Sunken);
    collisionDivider->setFixedHeight(30);
    flipRow->addSpacing(7);
    flipRow->addWidget(collisionDivider);
    flipRow->addSpacing(7);
    m_collisionKeep = new TilemapPaintButton(TilemapPaintButton::KeepCollision,
        tr("Keep collision unchanged"), this);
    m_collisionEmpty = new TilemapPaintButton(TilemapPaintButton::EmptyCollision,
        tr("Erase collision (make empty)"), this);
    m_collisionKeep->setToolTip(tr("No-entry: leave existing collision cells unchanged while painting graphics."));
    m_collisionEmpty->setToolTip(tr("Empty collision: paint collision type 0, removing collision from painted cells."));
    flipRow->addWidget(m_collisionKeep);
    flipRow->addWidget(m_collisionEmpty);
    brushC->setMinimumWidth(135);
    brushC->setMaximumWidth(205);
    brushC->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    flipRow->addWidget(brushC);
    renameZone->setToolTip(tr("Rename the selected custom collision zone."));
    flipRow->addWidget(renameZone);
    flipRow->addWidget(customSolid);

    m_playerToolsDivider = new QFrame(this);
    m_playerToolsDivider->setFrameShape(QFrame::VLine);
    m_playerToolsDivider->setFrameShadow(QFrame::Sunken);
    m_playerToolsDivider->setFixedHeight(30);
    m_playerToolsDivider->hide();
    flipRow->addSpacing(7);
    flipRow->addWidget(m_playerToolsDivider);
    flipRow->addSpacing(7);
    m_playerReferenceToggle = new TilemapFlagButton(TilemapFlagButton::Player,
        tr("Show player reference (drag to check gaps)"), this);
    m_playerReferenceToggle->setToolTip(tr("Show player reference: editor-only sprite named 'player'. "
        "Drag it, or point at the map and press Space to position it there. "
        "The World Editor spawn position is never changed. Turn off to paint behind it."));
    m_playerReferenceToggle->hide();
    flipRow->addWidget(m_playerReferenceToggle);
    connect(m_playerReferenceToggle, &QToolButton::toggled, this, [this](bool visible) {
        if (m_canvas) {
            m_canvas->showPlayerReference = visible;
            m_canvas->viewport()->update();
        }
    });
    m_playerCollisionToggle = new TilemapFlagButton(TilemapFlagButton::Hitbox,
        tr("Show player hitbox / collision clearance"), this);
    m_playerCollisionToggle->setToolTip(tr("Show player hitbox / collision clearance. "
        "Green: clear. Red: blocked by solids or slope interiors. "
        "Orange: hazard. Yellow: one-way platform. Blue: pass-through zone/door. "
        "Uses the saved Player Animation Editor hitbox where valid (otherwise full sprite). "
        "This is a stationary design-time clearance check, not a motion simulation."));
    m_playerCollisionToggle->setChecked(true);
    m_playerCollisionToggle->hide();
    flipRow->addWidget(m_playerCollisionToggle);
    connect(m_playerCollisionToggle, &QToolButton::toggled, this, [this](bool enabled) {
        if (m_canvas) {
            m_canvas->showPlayerCollision = enabled;
            m_canvas->viewport()->update();
        }
    });
    flipRow->addStretch(1);
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
    atlasChoice->setToolTip(tr("Choose a PPB from Game Resources > Tile Atlases. "
        "Sprites are not tile atlases. Selecting a different atlas does not change "
        "the existing tile IDs or collision cells."));
    atlasChoice->addItem(tr("No artwork (IDs only)"), QString());
    for (const auto &a : atlases) atlasChoice->addItem(a.first, a.second);
    if (atlases.isEmpty()) {
        atlasChoice->setToolTip(tr("No Tile Atlas resources yet. In Game Designer, "
            "right-click Tile Atlases to add or import a PPB. "
            "An existing map's artwork will remain loaded until you select a new atlas."));
    }
    const QString existing = m_map.atlasPath.isEmpty() ? QString()
        : QDir::cleanPath(QDir(m_designDirectory).absoluteFilePath(m_map.atlasPath));
    const int selected = atlasChoice->findData(existing);
    if (selected >= 0) atlasChoice->setCurrentIndex(selected);
    else if (!m_map.atlasPath.isEmpty()) {
        // Preserve the CURRENT artwork during a project migration. Never
        // silently switch the map to a different atlas (tile IDs depend on it).
        // Clearly label the old reference instead of presenting its Sprite
        // resource name as though it belongs to the Tile Atlases bank.
        const QString fileName = QFileInfo(existing).fileName();
        atlasChoice->addItem(tr("Current map PPB (not in Tile Atlases): %1").arg(fileName), existing);
        atlasChoice->setItemData(atlasChoice->count() - 1,
            tr("This map still references an older PPB outside the Tile Atlases bank. "
               "Select the correct resource above, or move its Sprite into Tile Atlases."), Qt::ToolTipRole);
        atlasChoice->setCurrentIndex(atlasChoice->count() - 1);
    }
    sideLayout->addWidget(atlasChoice);

    auto *graphicModes = new QHBoxLayout;
    graphicModes->setSpacing(3);
    graphicModes->addWidget(new QLabel(tr("Paint graphics:"), sidebar));
    m_graphicKeep = new TilemapPaintButton(TilemapPaintButton::KeepGraphic,
        tr("Don't change graphics"), sidebar);
    m_graphicEmpty = new TilemapPaintButton(TilemapPaintButton::EmptyGraphic,
        tr("Erase graphics"), sidebar);
    m_graphicAtlas = new TilemapPaintButton(TilemapPaintButton::AtlasGraphic,
        tr("Paint selected atlas tile"), sidebar);
    m_graphicKeep->setToolTip(tr("No change: preserve graphics and edit collisions only."));
    m_graphicEmpty->setToolTip(tr("Paint nothing: erase the graphics (ID 0) in painted cells."));
    m_graphicAtlas->setToolTip(tr("Atlas: paint the selected atlas tile. Clicking an atlas tile also selects this mode."));
    graphicModes->addWidget(m_graphicKeep);
    graphicModes->addWidget(m_graphicEmpty);
    graphicModes->addWidget(m_graphicAtlas);
    graphicModes->addStretch(1);
    sideLayout->addLayout(graphicModes);

    // The atlas receives the spare vertical space. Even very long sheets
    // remain scrollable without shrinking the game canvas to a thin strip.
    auto *tilePickerArea = new QScrollArea(sidebar);
    tilePickerArea->setWidgetResizable(false);
    tilePickerArea->setMinimumHeight(120);
    m_atlasArea = tilePickerArea;
    tilePickerArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tilePickerArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    tilePickerArea->setWidgetResizable(false);
    tilePickerArea->viewport()->installEventFilter(this);
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
    auto *placePlayerShortcut = new QShortcut(QKeySequence(Qt::Key_Space), this);
    placePlayerShortcut->setContext(Qt::WidgetWithChildrenShortcut);
    placePlayerShortcut->setAutoRepeat(false);
    connect(placePlayerShortcut, &QShortcut::activated, this, [this]() {
        if (m_canvas) m_canvas->movePlayerReferenceToMouse();
    });
    m_canvas->strokeStarted = [this]() { m_strokeStart = m_map; };
    m_canvas->strokeFinished = [this]() { recordChange(m_strokeStart); };
    m_canvas->temporaryStatus = [this](const QString &status) {
        if (m_saveStatus && !status.isEmpty()) m_saveStatus->setText(status);
        else if (m_saveStatus && !sameTilemap(m_map, m_strokeStart))
            m_saveStatus->setText(tr("Unsaved changes"));
    };
    m_canvas->editPlacedCollision = [this](int shapeIndex) {
        if (shapeIndex < 0 || shapeIndex >= m_map.collisionStamps.size()) return;
        m_stampTabs->setCurrentIndex(1);
        openCollisionStampEditor(shapeIndex);
        if (m_stampStatus)
            m_stampStatus->setText(tr("Editing collision stamp '%1' — changes affect every copy")
                                    .arg(m_map.collisionStamps.at(shapeIndex).name));
    };
    // Stamp sidebar: upper bank of thumbnails + lower editable stamp grid.
    m_stampTabs = new QTabWidget(m_splitter);
    // The right-hand pane is resizable, even when a tab has long help text.
    // QSizePolicy::Ignored prevents the active tab's preferred width from
    // forcing the centre canvas into an unnecessarily narrow column.
    m_stampTabs->setMinimumWidth(250);
    m_stampTabs->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    // The polished tab padding must not widen the resizable right pane.
    // Narrow panes use the tab bar's scroll arrows rather than forcing a
    // larger minimum width and squeezing the world canvas.
    if (auto *tabBar = m_stampTabs->findChild<QTabBar *>()) {
        tabBar->setUsesScrollButtons(true);
        tabBar->setElideMode(Qt::ElideRight);
    }
    auto *stampSidebar = new QSplitter(Qt::Vertical, m_stampTabs);
    stampSidebar->setChildrenCollapsible(false);
    stampSidebar->setMinimumWidth(250);
    auto *bankPane = new QWidget(stampSidebar);
    auto *bankLayout = new QVBoxLayout(bankPane);
    bankLayout->setContentsMargins(4, 0, 4, 4);
    auto *bankTitle = new QLabel(tr("Stamp Bank"), bankPane);
    bankTitle->setFont(sectionFont);
    bankLayout->addWidget(bankTitle);
    m_stampList = new QListWidget(bankPane);
    m_stampList->setObjectName(QStringLiteral("GGTileStampBank"));
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
    m_stampTabs->addTab(stampSidebar, tr("Tile Stamps"));

    // Collision Stamps: switch between a full-height bank and a full-height
    // point editor, rather than squeezing both into half the sidebar.
    // Edits still modify the selected shared definition and are undoable.
    auto *collisionSidebar = new QStackedWidget(m_stampTabs);
    m_collisionViews = collisionSidebar;
    collisionSidebar->setMinimumWidth(0);
    collisionSidebar->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
    auto *collisionBankPane = new QWidget(collisionSidebar);
    auto *collisionBankLayout = new QVBoxLayout(collisionBankPane);
    collisionBankLayout->setContentsMargins(4, 4, 4, 4);
    auto *collisionBankTitle = new QLabel(tr("Collision Stamp Bank"), collisionBankPane);
    collisionBankLayout->addWidget(collisionBankTitle);
    auto *collisionBankHelp = new QLabel(
        tr("Double-click a stamp to edit its collision surface."), collisionBankPane);
    collisionBankHelp->setWordWrap(true);
    collisionBankLayout->addWidget(collisionBankHelp);
    m_collisionList = new QListWidget(collisionBankPane);
    m_collisionList->setObjectName(QStringLiteral("GGCollisionStampBank"));
    m_collisionList->setViewMode(QListView::IconMode);
    m_collisionList->setResizeMode(QListView::Adjust);
    m_collisionList->setMovement(QListView::Static);
    m_collisionList->setWrapping(true);
    m_collisionList->setIconSize(QSize(104, 76));
    m_collisionList->setGridSize(QSize(124, 116));
    collisionBankLayout->addWidget(m_collisionList, 1);
    auto *collisionActions = new QHBoxLayout;
    auto *addCollision = new QPushButton(tr("Add"), collisionBankPane);
    auto *removeCollision = new QPushButton(tr("Remove"), collisionBankPane);
    collisionActions->addWidget(addCollision);
    collisionActions->addWidget(removeCollision);
    collisionBankLayout->addLayout(collisionActions);
    auto *collisionEditPane = new QWidget(collisionSidebar);
    auto *collisionEditLayout = new QVBoxLayout(collisionEditPane);
    collisionEditLayout->setContentsMargins(6, 6, 6, 6);
    collisionEditLayout->setSpacing(6);
    auto *collisionEditorHeader = new QHBoxLayout;
    auto *collisionEditorTitle = new QLabel(tr("Edit Collision Stamp"), collisionEditPane);
    collisionEditorHeader->addWidget(collisionEditorTitle, 1);
    // A pair of crisp, theme-text-coloured 24x24 action icons. No rounded corners.
    const auto slopeActionIcon = [this](bool accept) {
        QPixmap image(24, 24);
        image.fill(Qt::transparent);
        QPainter painter(&image);
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setPen(QPen(palette().color(QPalette::Text), 3,
                            Qt::SolidLine, Qt::SquareCap, Qt::MiterJoin));
        if (accept) {
            painter.drawLine(4, 12, 10, 18);
            painter.drawLine(10, 18, 21, 5);
        } else {
            painter.drawLine(5, 5, 19, 19);
            painter.drawLine(19, 5, 5, 19);
        }
        return QIcon(image);
    };
    auto *cancelCollisionEdit = new QPushButton(collisionEditPane);
    auto *acceptCollisionEdit = new QPushButton(collisionEditPane);
    cancelCollisionEdit->setObjectName(QStringLiteral("GGCollisionEditorCancel"));
    acceptCollisionEdit->setObjectName(QStringLiteral("GGCollisionEditorAccept"));
    cancelCollisionEdit->setIcon(slopeActionIcon(false));
    acceptCollisionEdit->setIcon(slopeActionIcon(true));
    for (QPushButton *button : {cancelCollisionEdit, acceptCollisionEdit}) {
        button->setIconSize(QSize(24, 24));
        button->setFixedSize(36, 34);
        button->setStyleSheet(QStringLiteral("QPushButton { border-radius:0px; }"));
    }
    cancelCollisionEdit->setToolTip(tr("Cancel slope edits and return to Collision Stamps (Esc)"));
    acceptCollisionEdit->setToolTip(tr("Keep slope edits and return to Collision Stamps"));
    collisionEditorHeader->addWidget(cancelCollisionEdit);
    collisionEditorHeader->addWidget(acceptCollisionEdit);
    collisionEditLayout->addLayout(collisionEditorHeader);
    auto *collisionEditorHelp = new QLabel(tr("Draw the ground surface (solid below the line)."), collisionEditPane);
    collisionEditorHelp->setWordWrap(true);
    collisionEditLayout->addWidget(collisionEditorHelp);
    m_collisionName = new QLineEdit(collisionEditPane);
    m_collisionName->setMaxLength(80);
    m_collisionName->setPlaceholderText(tr("Collision stamp name"));
    collisionEditLayout->addWidget(m_collisionName);
    auto *collisionDimensions = new QHBoxLayout;
    m_collisionWidth = new QSpinBox(collisionEditPane);
    m_collisionHeight = new QSpinBox(collisionEditPane);
    m_collisionWidth->setRange(1, 16);
    m_collisionHeight->setRange(1, 16);
    collisionDimensions->addWidget(new QLabel(tr("Width"), collisionEditPane));
    collisionDimensions->addWidget(m_collisionWidth);
    collisionDimensions->addWidget(new QLabel(tr("Height"), collisionEditPane));
    collisionDimensions->addWidget(m_collisionHeight);
    collisionEditLayout->addLayout(collisionDimensions);
    m_collisionPassive = new QCheckBox(tr("Passive surface physics (slide with gravity)"), collisionEditPane);
    m_collisionPassive->setToolTip(tr("Enable automatic downhill acceleration on this collision stamp. "
        "It works on straight slopes and Bezier-generated curves, including mirrored placements."));
    collisionEditLayout->addWidget(m_collisionPassive);
    auto *dampingRow = new QHBoxLayout;
    dampingRow->addWidget(new QLabel(tr("Damping"), collisionEditPane));
    m_collisionDampingSlider = new QSlider(Qt::Horizontal, collisionEditPane);
    m_collisionDampingSlider->setRange(0, 100);
    m_collisionDampingSlider->setToolTip(tr("0% keeps surface momentum; 100% removes it immediately. "
        "Only applies while standing on this stamp, not to joystick walking speed."));
    m_collisionDamping = new QSpinBox(collisionEditPane);
    m_collisionDamping->setRange(0, 100);
    m_collisionDamping->setSuffix(QStringLiteral("%"));
    m_collisionDamping->setKeyboardTracking(false);
    dampingRow->addWidget(m_collisionDampingSlider, 1);
    dampingRow->addWidget(m_collisionDamping);
    collisionEditLayout->addLayout(dampingRow);
    auto *collisionScroll = new QScrollArea(collisionEditPane);
    collisionScroll->setWidgetResizable(false);
    collisionScroll->setAlignment(Qt::AlignCenter);
    collisionScroll->setMinimumHeight(180);
    m_collisionCanvas = new CollisionCanvas(collisionScroll);
    m_collisionCanvas->map = &m_map;
    m_collisionCanvas->atlas = &m_atlas;
    collisionScroll->setWidget(m_collisionCanvas);
    collisionEditLayout->addWidget(collisionScroll, 1);
    auto *collisionPointRow = new QHBoxLayout;
    m_collisionPointLabel = new QLabel(tr("Point: none"), collisionEditPane);
    m_collisionPointX = new QSpinBox(collisionEditPane);
    m_collisionPointY = new QSpinBox(collisionEditPane);
    m_collisionPointX->setToolTip(tr("Selected point's horizontal coordinate, in local pixels"));
    m_collisionPointY->setToolTip(tr("Selected point's vertical coordinate, in local pixels"));
    collisionPointRow->addWidget(m_collisionPointLabel);
    collisionPointRow->addWidget(new QLabel(tr("X"), collisionEditPane));
    collisionPointRow->addWidget(m_collisionPointX);
    collisionPointRow->addWidget(new QLabel(tr("Y"), collisionEditPane));
    collisionPointRow->addWidget(m_collisionPointY);
    collisionEditLayout->addLayout(collisionPointRow);
    // The cubic is baked into ordinary editable v4 points. The two outer
    // endpoints have independently editable Y positions; their X positions
    // must span the stamp (0..width) for the existing collision format.
    // Keeping it a tool rather than a new collision type preserves old maps.
    auto *generateCurve = new QPushButton(tr("Generate Bezier Curve..."), collisionEditPane);
    generateCurve->setToolTip(tr("Shape a smooth ramp or bowl with two Bezier handles. "
        "Converts to ordinary editable collision points; existing stamps and SD maps remain compatible."));
    collisionEditLayout->addWidget(generateCurve);
    connect(generateCurve, &QPushButton::clicked, this, [this]() {
        const int row = m_collisionList ? m_collisionList->currentRow() : -1;
        if (row < 0 || row >= m_map.collisionStamps.size()) return;
        const SidboxCollisionStamp shape = m_map.collisionStamps.at(row);
        const int w = shape.width * shape.tileSize, h = shape.height * shape.tileSize;
        if (shape.points.size() < 2 || w < 1 || h < 1) return;
        QDialog dialog(this);
        dialog.setWindowTitle(tr("Bezier collision surface — %1").arg(shape.name));
        dialog.setStyleSheet(QStringLiteral("QDialog, QSpinBox, QSlider, QLabel, QPushButton { border-radius:0px; }"));
        auto *form = new QFormLayout(&dialog);
        // Sliders and exact pixel values are kept in sync; no new map data.
        auto make = [&dialog, form](const QString &name, int min, int max, int value) {
            auto *rowWidget = new QWidget(&dialog);
            auto *rowLayout = new QHBoxLayout(rowWidget);
            rowLayout->setContentsMargins(0, 0, 0, 0);
            rowLayout->setSpacing(8);
            auto *slider = new QSlider(Qt::Horizontal, rowWidget);
            slider->setRange(min, max);
            slider->setValue(value);
            auto *spin = new QSpinBox(rowWidget);
            spin->setRange(min, max);
            spin->setValue(value);
            spin->setMinimumWidth(76);
            rowLayout->addWidget(slider, 1);
            rowLayout->addWidget(spin);
            form->addRow(name, rowWidget);
            QObject::connect(slider, &QSlider::valueChanged, spin, &QSpinBox::setValue);
            QObject::connect(spin, qOverload<int>(&QSpinBox::valueChanged),
                             slider, &QSlider::setValue);
            return std::pair<QSpinBox *, QSlider *>(spin, slider);
        };
        // Previously these Y coordinates were read once and could never move
        // in the Bezier popup, even though the point-slope format permits it.
        auto *startY = make(tr("Left endpoint Y"), 0, h, shape.points.first().y()).first;
        auto [x1, sliderAX] = make(tr("Handle A X"), 0, w, w/3);
        auto [y1, sliderAY] = make(tr("Handle A Y"), 0, h, startY->value());
        auto [x2, sliderBX] = make(tr("Handle B X"), 0, w, w*2/3);
        auto [y2, sliderBY] = make(tr("Handle B Y"), 0, h, shape.points.last().y());
        auto *endY = make(tr("Right endpoint Y"), 0, h, shape.points.last().y()).first;

        // A<=B is required by the existing single-valued-X slope sampler.
        // Restrict both X controls in either editing direction, including drags.
        auto limitHandleX = [=]() {
            const int a = x1->value(), b = x2->value();
            x1->setMaximum(b);
            sliderAX->setMaximum(b);
            x2->setMinimum(a);
            sliderBX->setMinimum(a);
        };
        connect(x1, qOverload<int>(&QSpinBox::valueChanged), &dialog,
                [limitHandleX](int) { limitHandleX(); });
        connect(x2, qOverload<int>(&QSpinBox::valueChanged), &dialog,
                [limitHandleX](int) { limitHandleX(); });
        limitHandleX();

        // Interactive preview: move either outer endpoint vertically, or
        // drag A/B in both directions. No Q_OBJECT/moc is required and the
        // actual collision stamp remains untouched until OK.
        class BezierPreview final : public QWidget {
        public:
            BezierPreview(QWidget *parent, int curveW, int curveH,
                          QSpinBox *startY, QSpinBox *endY,
                          QSpinBox *ax, QSpinBox *ay, QSpinBox *bx, QSpinBox *by)
                : QWidget(parent), m_w(curveW), m_h(curveH),
                  m_startY(startY), m_endY(endY),
                  m_ax(ax), m_ay(ay), m_bx(bx), m_by(by)
            {
                setMinimumSize(420, 260);
                setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                setMouseTracking(true);
                setToolTip(tr("Drag the blue endpoints up/down, or orange A and pink B in any direction"));
            }

        protected:
            void paintEvent(QPaintEvent *) override
            {
                QPainter painter(this);
                painter.setRenderHint(QPainter::Antialiasing);
                painter.fillRect(rect(), QColor(27, 37, 49));
                const QRectF plot = plotRect();
                painter.setPen(QPen(QColor(103, 127, 145), 1));
                painter.setBrush(Qt::NoBrush);
                painter.drawRect(plot);

                const QPointF start = toScreen(QPoint(0, m_startY->value()));
                const QPointF finish = toScreen(QPoint(m_w, m_endY->value()));
                const QPointF a = toScreen(QPoint(m_ax->value(), m_ay->value()));
                const QPointF b = toScreen(QPoint(m_bx->value(), m_by->value()));

                const auto pts = sampledCubicSlope(m_w, m_h, m_startY->value(), m_endY->value(),
                    QPoint(m_ax->value(), m_ay->value()),
                    QPoint(m_bx->value(), m_by->value()));
                if (!pts.isEmpty()) {
                    QPolygonF line;
                    for (const QPoint &pt : pts) line << toScreen(pt);
                    QPolygonF filled = line;
                    filled << plot.bottomRight() << plot.bottomLeft();
                    painter.setPen(Qt::NoPen);
                    painter.setBrush(QColor(45, 189, 157, 75));
                    painter.drawPolygon(filled);
                    painter.setBrush(Qt::NoBrush);
                    painter.setPen(QPen(QColor(73, 255, 207), 2));
                    painter.drawPolyline(line);
                }

                // Control polygon makes the curve's shape intuitive.
                painter.setPen(QPen(QColor(174, 182, 199, 170), 1, Qt::DashLine));
                painter.drawLine(start, a);
                painter.drawLine(a, b);
                painter.drawLine(b, finish);
                drawHandle(painter, start, QColor(109, 212, 255), QStringLiteral("L"));
                drawHandle(painter, finish, QColor(109, 212, 255), QStringLiteral("R"));
                drawHandle(painter, a, QColor(255, 180, 65), QStringLiteral("A"));
                drawHandle(painter, b, QColor(255, 107, 167), QStringLiteral("B"));
                painter.setPen(QColor(191, 202, 213));
                painter.drawText(QRectF(0, height() - 27, width(), 24),
                                 Qt::AlignCenter, tr("Drag blue L/R vertically  •  Drag orange A / pink B freely"));
            }

            void mousePressEvent(QMouseEvent *event) override
            {
                if (event->button() != Qt::LeftButton) {
                    QWidget::mousePressEvent(event); return;
                }
                m_dragging = hitHandle(event->position());
                if (m_dragging == 0) {
                    QWidget::mousePressEvent(event); return;
                }
                setCursor(Qt::ClosedHandCursor);
                event->accept();
            }

            void mouseMoveEvent(QMouseEvent *event) override
            {
                if (m_dragging != 0) {
                    const QRectF plot = plotRect();
                    int x = qBound(0, qRound((event->position().x() - plot.left()) * m_w / plot.width()), m_w);
                    const int y = qBound(0, qRound((event->position().y() - plot.top()) * m_h / plot.height()), m_h);
                    if (m_dragging == 1) {
                        m_startY->setValue(y); // Left X remains exactly zero.
                    } else if (m_dragging == 2) {
                        x = qMin(x, m_bx->value());
                        m_ax->setValue(x); m_ay->setValue(y);
                    } else if (m_dragging == 3) {
                        x = qMax(x, m_ax->value());
                        m_bx->setValue(x); m_by->setValue(y);
                    } else if (m_dragging == 4) {
                        m_endY->setValue(y); // Right X remains exactly width.
                    }
                    update();
                    event->accept(); return;
                }
                setCursor(hitHandle(event->position()) ? Qt::OpenHandCursor : Qt::ArrowCursor);
                QWidget::mouseMoveEvent(event);
            }

            void mouseReleaseEvent(QMouseEvent *event) override
            {
                if (event->button() == Qt::LeftButton && m_dragging != 0) {
                    m_dragging = 0;
                    setCursor(Qt::OpenHandCursor);
                    event->accept(); return;
                }
                QWidget::mouseReleaseEvent(event);
            }

        private:
            // 1=left, 2=A, 3=B, 4=right. Find the closest handle so
            // endpoints remain selectable even if a Bezier handle overlaps.
            int hitHandle(const QPointF &p) const
            {
                const QPointF handles[4] = {
                    toScreen(QPoint(0, m_startY->value())),
                    toScreen(QPoint(m_ax->value(), m_ay->value())),
                    toScreen(QPoint(m_bx->value(), m_by->value())),
                    toScreen(QPoint(m_w, m_endY->value()))
                };
                int hit = 0;
                qreal closest = 18.01;
                // Prefer the outer endpoints when two handles sit on top
                // of each other; the other handle has precise spinboxes.
                for (int i : {0, 3, 1, 2}) {
                    const qreal distance = QLineF(p, handles[i]).length();
                    if (distance < closest) { closest = distance; hit = i + 1; }
                }
                return hit;
            }
            QRectF plotRect() const
            {
                return QRectF(28, 22, qMax(1, width() - 56), qMax(1, height() - 64));
            }
            QPointF toScreen(QPoint p) const
            {
                const QRectF r = plotRect();
                return QPointF(r.left() + double(p.x()) * r.width() / m_w,
                               r.top() + double(p.y()) * r.height() / m_h);
            }
            static void drawHandle(QPainter &p, QPointF pos, QColor colour, const QString &letter)
            {
                p.setPen(QPen(QColor(24, 28, 39), 2));
                p.setBrush(colour);
                p.drawEllipse(pos, 11, 11);
                p.setPen(QColor(24, 28, 39));
                p.drawText(QRectF(pos.x()-11, pos.y()-11, 22, 22), Qt::AlignCenter, letter);
            }
            int m_w, m_h;
            QSpinBox *m_startY, *m_endY;
            QSpinBox *m_ax, *m_ay, *m_bx, *m_by;
            int m_dragging = 0;
        };

        auto *preview = new BezierPreview(&dialog, w, h, startY, endY, x1, y1, x2, y2);
        form->addRow(preview);
        for (QSpinBox *spin : {startY, x1, y1, x2, y2, endY})
            connect(spin, qOverload<int>(&QSpinBox::valueChanged), preview,
                    [preview](int) { preview->update(); });
        auto *hint = new QLabel(tr("Blue L/R: drag up or down, or set Y from 0 (top) to height (bottom). "
            "Orange A and pink B: drag anywhere in the stamp. "
            "Left/right X endpoints stay at the edges so the collision surface spans the whole stamp. "
            "OK generates ordinary editable collision points."), &dialog);
        hint->setWordWrap(true); form->addRow(hint);
        auto *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
        connect(buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        form->addRow(buttons);
        if (dialog.exec() != QDialog::Accepted || x1->value() > x2->value()) return;
        const auto points = sampledCubicSlope(w, h, startY->value(), endY->value(),
            QPoint(x1->value(), y1->value()), QPoint(x2->value(), y2->value()));
        if (points.isEmpty()) return;
        const SidboxTilemap before = m_map;
        m_map.collisionStamps[row].points = points;
        m_collisionCanvas->active = -1;
        m_collisionCanvas->refresh();
        updateCollisionList(row);
        m_canvas->viewport()->update();
        recordChange(before);
    });
    auto *collisionPointButtons = new QHBoxLayout;
    m_collisionInsertPoint = new QPushButton(tr("Insert Point"), collisionEditPane);
    m_collisionDeletePoint = new QPushButton(tr("Delete Point"), collisionEditPane);
    collisionPointButtons->addWidget(m_collisionInsertPoint);
    collisionPointButtons->addWidget(m_collisionDeletePoint);
    collisionEditLayout->addLayout(collisionPointButtons);
    auto *collisionHint = new QLabel(tr("Click: add point  |  Drag: move  |  Right-click: remove  |  "
        "Shift-click map: edit placed slope  |  Mirror X supported"), collisionEditPane);
    collisionHint->setWordWrap(true);
    collisionEditLayout->addWidget(collisionHint);
    collisionSidebar->addWidget(collisionBankPane);
    collisionSidebar->addWidget(collisionEditPane);
    collisionSidebar->setCurrentIndex(0);
    connect(cancelCollisionEdit, &QPushButton::clicked, this,
            [this]() { finishCollisionStampEdit(false); });
    connect(acceptCollisionEdit, &QPushButton::clicked, this,
            [this]() { finishCollisionStampEdit(true); });
    m_collisionCanvas->setFocusPolicy(Qt::StrongFocus);
    auto *deleteCollisionPoint = new QShortcut(QKeySequence(Qt::Key_Delete), m_collisionCanvas);
    deleteCollisionPoint->setContext(Qt::WidgetShortcut);
    connect(deleteCollisionPoint, &QShortcut::activated, this, [this]() {
        if (m_collisionViews && m_collisionViews->currentIndex() == 1 &&
            m_collisionDeletePoint && m_collisionDeletePoint->isEnabled())
            m_collisionDeletePoint->click();
    });
    m_stampTabs->addTab(collisionSidebar, tr("Collision Stamps"));
    // Physics loop workspace. The yellow marker is the shared bottom
    // entrance/exit; the blue circle is NOT an ordinary solid slope. The
    // engine switches only this player to guided track movement at speed.
    auto *loopPane = new QWidget(m_stampTabs);
    loopPane->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
    auto *loopLayout = new QVBoxLayout(loopPane);
    loopLayout->setContentsMargins(6, 6, 6, 6);
    loopLayout->setSpacing(6);
    // The tab already says Loop Tracks; no extra title or third-party name.
    auto *loopList = new QListWidget(loopPane);
    loopList->setObjectName(QStringLiteral("GGLoopTrackBank"));
    loopList->setSpacing(2);
    loopLayout->addWidget(loopList, 1);
    auto *loopActions = new QHBoxLayout;
    auto *loopAdd = new QPushButton(tr("Add Loop"), loopPane);
    auto *loopRemove = new QPushButton(tr("Remove Loop"), loopPane);
    loopActions->addWidget(loopAdd); loopActions->addWidget(loopRemove);
    loopLayout->addLayout(loopActions);
    auto *loopForm = new QFormLayout;
    loopForm->setContentsMargins(0, 0, 0, 0);
    loopForm->setSpacing(5);
    loopForm->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    auto *loopX = new QSpinBox(loopPane);
    auto *loopY = new QSpinBox(loopPane);
    auto *loopRadius = new QSpinBox(loopPane);
    auto *loopSpeed = new QSpinBox(loopPane);
    auto *loopRadiusSlider = new QSlider(Qt::Horizontal,loopPane);
    auto *loopBoostSlider = new QSlider(Qt::Horizontal, loopPane);
    auto *loopBoostValue = new QLabel(tr("+0.00 px/frame²"), loopPane);
    auto *loopCoast = new QCheckBox(tr("Ignore friction after exit"), loopPane);
    auto *loopFalloffSlider = new QSlider(Qt::Horizontal, loopPane);
    auto *loopFalloffValue = new QLabel(tr("0.0% / frame"), loopPane);
    loopFalloffSlider->setRange(0, 200); // 0.1% increments, maximum 20% per 50Hz tick.
    loopFalloffSlider->setSingleStep(1);
    loopFalloffSlider->setPageStep(10);
    loopFalloffSlider->setToolTip(tr("Gradually slow the player's LOOP EXIT coast by this percent "
        "each physics frame (50 frames per second). 0.0% keeps coasting at full speed. "
        "Only applies after completing a loop with Ignore friction after exit enabled."));
    loopFalloffValue->setMinimumWidth(76);
    loopFalloffValue->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto *loopFalloffRow = new QHBoxLayout;
    loopFalloffRow->setContentsMargins(0, 0, 0, 0);
    loopFalloffRow->addWidget(loopFalloffSlider, 1);
    loopFalloffRow->addWidget(loopFalloffValue);
    loopCoast->setToolTip(tr("After a COMPLETE revolution, preserve the loop's exit momentum "
        "without friction. Hitting a wall or pressing Left/Right ends the effect "
        "and restores the normal physics preset's drag. Each loop can opt in separately."));
    loopBoostSlider->setRange(0, 200); // Hundredths of a pixel/frame gained each tick.
    loopBoostSlider->setSingleStep(5);
    loopBoostSlider->setPageStep(20);
    loopBoostSlider->setToolTip(tr("Adds speed only on the descending half. "
        "A boosted loop holds its speed going uphill. Zero restores normal loop physics."));
    loopBoostValue->setMinimumWidth(93);
    loopBoostValue->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    auto *loopBoostRow = new QHBoxLayout;
    loopBoostRow->setContentsMargins(0, 0, 0, 0);
    loopBoostRow->addWidget(loopBoostSlider, 1);
    loopBoostRow->addWidget(loopBoostValue);
    loopRadiusSlider->setRange(16,512);
    loopRadius->setRange(16, 512);
    loopSpeed->setRange(1, 32);
    loopSpeed->setSuffix(tr(" px/f"));
    loopSpeed->setToolTip(tr("Minimum horizontal approach speed, in pixels per frame (50 FPS)."));
    loopX->setMinimumWidth(54);
    loopY->setMinimumWidth(54);
    loopX->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    loopY->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Fixed);
    auto *loopCenterRow = new QHBoxLayout;
    loopCenterRow->setContentsMargins(0, 0, 0, 0);
    loopCenterRow->setSpacing(4);
    loopCenterRow->addWidget(new QLabel(tr("X"), loopPane));
    loopCenterRow->addWidget(loopX, 1);
    loopCenterRow->addWidget(new QLabel(tr("Y"), loopPane));
    loopCenterRow->addWidget(loopY, 1);
    auto *loopRadiusRow = new QHBoxLayout;
    loopRadiusRow->setContentsMargins(0, 0, 0, 0);
    loopRadiusRow->setSpacing(4);
    loopRadiusRow->addWidget(loopRadiusSlider, 1);
    loopRadiusRow->addWidget(loopRadius);
    loopForm->addRow(tr("Center"), loopCenterRow);
    loopForm->addRow(tr("Radius"), loopRadiusRow);
    loopForm->addRow(tr("Entry speed"), loopSpeed);
    loopForm->addRow(tr("Momentum +"), loopBoostRow);
    loopForm->addRow(QString(), loopCoast);
    loopForm->addRow(tr("Falloff"), loopFalloffRow);
    loopLayout->addLayout(loopForm);
    auto *loopHint = new QLabel(tr("Yellow dot = loop entry/exit. Hover over a control for help."), loopPane);
    loopHint->setWordWrap(true);
    loopHint->setToolTip(tr("Enter from either direction at the minimum speed. "
        "Momentum Add boosts the downhill half; uphill speed is maintained. "
        "Ignore friction after exit works only after a full lap, until steering or a wall. "
        "Falloff then gradually reduces that coasting speed each 50Hz frame. "
        "Slower players can fall off the track. Use curved collision stamps "
        "for run-in and run-out slopes. Player art remains upright."));
    loopLayout->addWidget(loopHint);
    // Tiny crisp icon: circular track and gold entrance/exit at six o'clock.
    QPixmap loopIconPixmap(16, 16);
    loopIconPixmap.fill(Qt::transparent);
    {
        QPainter painter(&loopIconPixmap);
        painter.setRenderHint(QPainter::Antialiasing, false);
        painter.setPen(QPen(QColor(38, 160, 190), 2));
        painter.drawEllipse(2, 1, 11, 11);
        painter.setPen(QPen(QColor(247, 196, 63), 2));
        painter.drawLine(5, 13, 10, 13);
        painter.fillRect(7, 11, 2, 3, QColor(247, 196, 63));
    }
    const QIcon loopIcon(loopIconPixmap);
    loopList->setIconSize(QSize(16, 16));
    m_stampTabs->addTab(loopPane, loopIcon, tr("Loop Tracks"));
    const auto updateLoopList = [this,loopList,loopIcon]() {
        const int selected = loopList->currentRow();
        QSignalBlocker block(loopList);
        loopList->clear();
        for (int i=0;i<m_map.loops.size();++i) {
            const auto &l=m_map.loops.at(i);
            auto *item = new QListWidgetItem(loopIcon,
                tr("Loop %1  (%2, %3)  R%4")
                .arg(i+1).arg(l.centerX).arg(l.centerY).arg(l.radius));
            item->setSizeHint(QSize(0, 34)); // Room for the bordered card.
            loopList->addItem(item);
        }
        loopList->setCurrentRow(qBound(-1,selected,int(m_map.loops.size())-1));
        m_canvas->viewport()->update();
    };
    const auto updateLoopEditors = [this,loopList,loopX,loopY,loopRadius,loopSpeed,
                                    loopRadiusSlider,loopBoostSlider,loopBoostValue,
                                    loopCoast,loopFalloffSlider,loopFalloffValue]() {
        const int i=loopList->currentRow();
        const bool valid=i>=0 && i<m_map.loops.size();
        const int maxX=m_map.width*m_map.tileSize;
        const int maxY=m_map.height*m_map.tileSize;
        for (QSpinBox *v : {loopX,loopY,loopRadius,loopSpeed}) v->setEnabled(valid);
        loopRadiusSlider->setEnabled(valid);
        loopBoostSlider->setEnabled(valid);
        loopBoostValue->setEnabled(valid);
        loopCoast->setEnabled(valid);
        loopFalloffSlider->setEnabled(valid && m_map.loops.at(i).coastAfterExit);
        loopFalloffValue->setEnabled(valid && m_map.loops.at(i).coastAfterExit);
        m_canvas->selectedLoop=i;
        m_canvas->viewport()->update();
        if (!valid) return;
        const auto &l=m_map.loops.at(i);
        const QSignalBlocker b1(loopX),b2(loopY),b3(loopRadius),b4(loopSpeed);
        loopX->setRange(l.radius,maxX-l.radius-1);
        loopY->setRange(l.radius,maxY-l.radius-1);
        loopRadius->setMaximum(qMin(512,qMin(qMin(l.centerX,maxX-l.centerX-1),
                                          qMin(l.centerY,maxY-l.centerY-1))));
        loopX->setValue(l.centerX); loopY->setValue(l.centerY);
        loopRadius->setValue(l.radius); loopSpeed->setValue(l.entrySpeed100/100);
        const QSignalBlocker b5(loopRadiusSlider);
        loopRadiusSlider->setMaximum(loopRadius->maximum());
        loopRadiusSlider->setValue(l.radius);
        const QSignalBlocker b6(loopBoostSlider);
        loopBoostSlider->setValue(l.downhillBoost100);
        const QSignalBlocker coastBlock(loopCoast);
        loopCoast->setChecked(l.coastAfterExit);
        const QSignalBlocker falloffBlock(loopFalloffSlider);
        loopFalloffSlider->setValue(l.coastFalloffPermille);
        loopFalloffValue->setText(tr("%1% / frame")
            .arg(l.coastFalloffPermille / 10.0, 0, 'f', 1));
        loopBoostValue->setText(tr("+%1 px/frame²")
            .arg(l.downhillBoost100 / 100.0, 0, 'f', 2));
    };
    connect(loopList,&QListWidget::currentRowChanged,this,
            [updateLoopEditors](int){updateLoopEditors();});
    connect(loopAdd,&QPushButton::clicked,this,[this,loopList,updateLoopList,updateLoopEditors]() {
        if (m_map.loops.size()>=32) {
            QMessageBox::warning(this,tr("Loop tracks"),tr("Maximum 32 loops per level.")); return;
        }
        SidboxLoopTrack l;
        const int maxX=m_map.width*m_map.tileSize, maxY=m_map.height*m_map.tileSize;
        l.radius=qMin(64,qMin(maxX,maxY)/4);
        l.centerX=qBound(l.radius,(m_canvas->horizontalScrollBar()->value()+
            m_canvas->viewport()->width()/2)/m_canvas->zoom,maxX-l.radius-1);
        l.centerY=qBound(l.radius,(m_canvas->verticalScrollBar()->value()+
            m_canvas->viewport()->height()/2)/m_canvas->zoom,maxY-l.radius-1);
        const SidboxTilemap before=m_map;
        m_map.loops.append(l);
        recordChange(before);
        updateLoopList();
        loopList->setCurrentRow(m_map.loops.size()-1);
        updateLoopEditors();
    });
    connect(loopRemove,&QPushButton::clicked,this,[this,loopList,updateLoopList,updateLoopEditors]() {
        const int i=loopList->currentRow();
        if (i<0 || i>=m_map.loops.size()) return;
        const SidboxTilemap before=m_map;
        m_map.loops.removeAt(i);
        recordChange(before);
        updateLoopList();
        loopList->setCurrentRow(qMin(i,m_map.loops.size()-1));
        updateLoopEditors();
    });
    const auto updateLoop = [this,loopList,loopX,loopY,loopRadius,loopSpeed,
                             loopBoostSlider,loopCoast,loopFalloffSlider,
                             updateLoopList,updateLoopEditors]() {
        const int i=loopList->currentRow();
        if (i<0 || i>=m_map.loops.size()) return;
        auto l=m_map.loops.at(i);
        l.centerX=loopX->value(); l.centerY=loopY->value();
        l.radius=loopRadius->value(); l.entrySpeed100=loopSpeed->value()*100;
        l.downhillBoost100=loopBoostSlider->value();
        l.coastAfterExit=loopCoast->isChecked();
        l.coastFalloffPermille=loopFalloffSlider->value();
        if (l.centerX<l.radius || l.centerY<l.radius ||
            l.centerX+l.radius>=m_map.width*m_map.tileSize ||
            l.centerY+l.radius>=m_map.height*m_map.tileSize) return;
        const SidboxTilemap before=m_map;
        m_map.loops[i]=l;
        recordChange(before);
        updateLoopList(); updateLoopEditors();
    };
    for (QSpinBox *spin : {loopX,loopY,loopRadius,loopSpeed})
        connect(spin,qOverload<int>(&QSpinBox::valueChanged),this,
                [updateLoop](int){updateLoop();});
    connect(loopRadiusSlider,&QSlider::valueChanged,loopRadius,
            &QSpinBox::setValue);
    connect(loopBoostSlider,&QSlider::valueChanged,this,
            [updateLoop](int){updateLoop();});
    connect(loopCoast,&QCheckBox::toggled,this,
            [updateLoop](bool){updateLoop();});
    connect(loopFalloffSlider,&QSlider::valueChanged,this,
            [updateLoop](int){updateLoop();});
    m_canvas->loopEdited=[updateLoopList,updateLoopEditors]() {
        updateLoopList(); updateLoopEditors();
    };
    updateLoopList(); updateLoopEditors();
    connect(m_stampTabs, &QTabWidget::currentChanged, this, [this](int tab) {
        m_canvas->collisionStampIndex = -1;
        m_canvas->stampIndex = -1;
        m_canvas->loopEditMode=(tab == 2);
        m_canvas->viewport()->setCursor(tab == 2 ? Qt::ArrowCursor : Qt::CrossCursor);
        if (tab == 0) selectStamp(m_stampList->currentRow());
        else if (tab == 1) selectCollisionStamp(m_collisionList->currentRow());
        m_stampMirrorY->setEnabled(tab == 0);
        if (tab == 1) m_stampMirrorY->setChecked(false);
        m_canvas->viewport()->update();
    });
    connect(m_collisionList, &QListWidget::currentRowChanged, this,
        [this](int row) { selectCollisionStamp(row); });
    connect(m_collisionList, &QListWidget::itemClicked, this,
        [this](QListWidgetItem *item) { selectCollisionStamp(m_collisionList->row(item)); });
    connect(m_collisionList, &QListWidget::itemDoubleClicked, this,
        [this](QListWidgetItem *item) { openCollisionStampEditor(m_collisionList->row(item)); });
    connect(addCollision, &QPushButton::clicked, this, [this]() {
        if (m_map.collisionStamps.size() >= 128) {
            QMessageBox::warning(this, tr("Collision stamps"), tr("Maximum of 128 collision stamps."));
            return;
        }
        const SidboxTilemap before = m_map;
        SidboxCollisionStamp stamp;
        stamp.name = tr("Slope %1").arg(m_map.collisionStamps.size() + 1);
        stamp.tileSize = m_map.tileSize;
        stamp.resizeStamp(2, 2);
        m_map.collisionStamps.append(stamp);
        recordChange(before);
        updateCollisionList(m_map.collisionStamps.size() - 1);
        selectCollisionStamp(m_collisionList->currentRow());
    });
    connect(removeCollision, &QPushButton::clicked, this, [this]() {
        const int row = m_collisionList->currentRow();
        if (row < 0 || row >= m_map.collisionStamps.size()) return;
        const SidboxTilemap before = m_map;
        for (int i = m_map.collisionPlacements.size() - 1; i >= 0; --i) {
            if (m_map.collisionPlacements.at(i).stamp == row)
                removeCollisionPlacement(m_map, i);
            else if (m_map.collisionPlacements.at(i).stamp > row)
                m_map.collisionPlacements[i].stamp--;
        }
        m_map.collisionStamps.removeAt(row);
        m_canvas->viewport()->update();
        recordChange(before);
        updateCollisionList(m_map.collisionStamps.isEmpty() ? -1 :
                            qMin(row, int(m_map.collisionStamps.size()) - 1));
        selectCollisionStamp(m_collisionList->currentRow());
    });
    connect(m_collisionName, &QLineEdit::editingFinished, this, [this]() {
        const int row = m_collisionList->currentRow();
        if (row < 0 || row >= m_map.collisionStamps.size()) return;
        const QString name = m_collisionName->text().trimmed();
        if (name.isEmpty()) return;
        const SidboxTilemap before = m_map;
        m_map.collisionStamps[row].name = name;
        recordChange(before);
        updateCollisionList(row);
    });
    connect(m_collisionPassive, &QCheckBox::toggled, this, [this](bool enabled) {
        const int row = m_collisionList->currentRow();
        if (row < 0 || row >= m_map.collisionStamps.size()) return;
        const SidboxTilemap before = m_map;
        m_map.collisionStamps[row].passiveSurface = enabled;
        m_collisionDamping->setEnabled(enabled);
        m_collisionDampingSlider->setEnabled(enabled);
        recordChange(before);
    });
    connect(m_collisionDampingSlider, &QSlider::sliderPressed, this, [this]() {
        m_collisionDampingStart = m_map;
        m_collisionDampingDragging = true;
    });
    connect(m_collisionDampingSlider, &QSlider::sliderReleased, this, [this]() {
        if (!m_collisionDampingDragging) return;
        m_collisionDampingDragging = false;
        recordChange(m_collisionDampingStart); // one undo step for an entire drag
    });
    connect(m_collisionDampingSlider, &QSlider::valueChanged,
            m_collisionDamping, &QSpinBox::setValue);
    connect(m_collisionDamping, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int value) {
            m_collisionDampingSlider->setValue(value);
            const int row = m_collisionList->currentRow();
            if (row < 0 || row >= m_map.collisionStamps.size() ||
                m_map.collisionStamps.at(row).dampingPercent == value) return;
            const SidboxTilemap before = m_map;
            m_map.collisionStamps[row].dampingPercent = value;
            if (!m_collisionDampingDragging) recordChange(before);
        });
    connect(m_collisionWidth, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int width) {
            if (!m_collisionList || m_collisionList->currentRow() < 0 ||
                m_collisionList->currentRow() >= m_map.collisionStamps.size()) return;
            if (!resizeSelectedCollisionStamp(width,
                    m_map.collisionStamps.at(m_collisionList->currentRow()).height)) {
                QSignalBlocker block(m_collisionWidth);
                const int row = m_collisionList->currentRow();
                if (row >= 0 && row < m_map.collisionStamps.size())
                    m_collisionWidth->setValue(m_map.collisionStamps.at(row).width);
            }
        });
    connect(m_collisionHeight, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int height) {
            if (!m_collisionList || m_collisionList->currentRow() < 0 ||
                m_collisionList->currentRow() >= m_map.collisionStamps.size()) return;
            if (!resizeSelectedCollisionStamp(
                    m_map.collisionStamps.at(m_collisionList->currentRow()).width, height)) {
                QSignalBlocker block(m_collisionHeight);
                const int row = m_collisionList->currentRow();
                if (row >= 0 && row < m_map.collisionStamps.size())
                    m_collisionHeight->setValue(m_map.collisionStamps.at(row).height);
            }
        });
    m_collisionCanvas->strokeStarted = [this]() { m_strokeStart = m_map; };
    m_collisionCanvas->modified = [this]() {
        recordChange(m_strokeStart);
        updateCollisionList(m_collisionList->currentRow());
        m_canvas->viewport()->update();
    };
    m_collisionCanvas->pointSelected = [this]() { updateCollisionPointControls(); };
    connect(m_collisionPointX, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int x) {
            const int row = m_collisionList->currentRow();
            if (row < 0 || row >= m_map.collisionStamps.size()) return;
            auto &shape = m_map.collisionStamps[row];
            const int point = m_collisionCanvas->active;
            if (point <= 0 || point >= shape.points.size()-1) return;
            const int clamped = qBound(shape.points.at(point-1).x()+1, x,
                                       shape.points.at(point+1).x()-1);
            if (shape.points.at(point).x() == clamped) return;
            const SidboxTilemap before = m_map;
            shape.points[point].setX(clamped);
            recordChange(before);
            updateCollisionList(row);
            m_canvas->viewport()->update();
        });
    connect(m_collisionPointY, qOverload<int>(&QSpinBox::valueChanged), this,
        [this](int y) {
            const int row = m_collisionList->currentRow();
            if (row < 0 || row >= m_map.collisionStamps.size()) return;
            auto &shape = m_map.collisionStamps[row];
            const int point = m_collisionCanvas->active;
            if (point < 0 || point >= shape.points.size()) return;
            const int clamped = qBound(0, y, shape.height * shape.tileSize);
            if (shape.points.at(point).y() == clamped) return;
            const SidboxTilemap before = m_map;
            shape.points[point].setY(clamped);
            recordChange(before);
            updateCollisionList(row);
            m_canvas->viewport()->update();
        });
    connect(m_collisionInsertPoint, &QPushButton::clicked, this, [this]() {
        const int row = m_collisionList->currentRow();
        if (row < 0 || row >= m_map.collisionStamps.size()) return;
        auto &shape = m_map.collisionStamps[row];
        if (shape.points.size() >= 128) return;
        // Insert into the widest available segment; cannot duplicate X coordinates.
        int segment = -1, widest = 1;
        for (int i = 1; i < shape.points.size(); ++i) {
            const int distance = shape.points.at(i).x() - shape.points.at(i-1).x();
            if (distance > widest) { widest = distance; segment = i; }
        }
        if (segment < 0) return;
        const SidboxTilemap before = m_map;
        const QPoint a = shape.points.at(segment-1), b = shape.points.at(segment);
        const int x = a.x() + (b.x()-a.x()) / 2;
        const int y = a.y() + qRound(double(b.y()-a.y()) * (x-a.x()) / (b.x()-a.x()));
        shape.points.insert(segment, QPoint(x, y));
        m_collisionCanvas->active = segment;
        recordChange(before);
        updateCollisionList(row);
        m_canvas->viewport()->update();
    });
    connect(m_collisionDeletePoint, &QPushButton::clicked, this, [this]() {
        const int row = m_collisionList->currentRow();
        if (row < 0 || row >= m_map.collisionStamps.size()) return;
        auto &shape = m_map.collisionStamps[row];
        const int point = m_collisionCanvas->active;
        if (point <= 0 || point >= shape.points.size()-1) return;
        const SidboxTilemap before = m_map;
        shape.points.removeAt(point);
        m_collisionCanvas->active = -1;
        recordChange(before);
        updateCollisionList(row);
        m_canvas->viewport()->update();
    });
    updateCollisionList(-1);

    m_splitter->addWidget(sidebar);
    m_splitter->addWidget(m_canvas);
    m_splitter->addWidget(m_stampTabs);
    m_splitter->setStretchFactor(0, 0);
    m_splitter->setStretchFactor(1, 1);
    m_splitter->setStretchFactor(2, 0);
    const QByteArray savedSplit = windowSettings.value(
        QStringLiteral("GameTilemapEditor/splitter")).toByteArray();
    if (savedSplit.isEmpty() || !m_splitter->restoreState(savedSplit))
        m_splitter->setSizes({300, 760, 300});
    layout->addWidget(m_splitter, 1);

    auto *help = new QLabel(tr("SHIFT+DRAG selects and copies a map region (Shift-click still edits slopes). "
        "Move the temporary stamp to preview it; LEFT-CLICK pastes, LEFT-DRAG positions, "
        "RIGHT-CLICK erases its footprint, ESC cancels without pasting. "
        "MIDDLE-DRAG or ALT+LEFT-DRAG pans; WHEEL zooms at the pointer; NUMPAD +/- zooms (1-16x). CTRL+Z / CTRL+Y undo/redo. "
        "Stamp: use Draw Front setting overrides copied front flags when ticked."), this);
    help->setWordWrap(true);
    layout->addWidget(help);
    // Keep the buttons in this exact order regardless of the desktop style.
    auto *buttons = new QHBoxLayout;
    m_saveStatus = new QLabel(this);
    m_saveStatus->setText(QString());
    buttons->addWidget(m_saveStatus, 1);
    m_cellStatus = new QLabel(tr("Col: —  Row: —"), this);
    m_cellStatus->setToolTip(tr("Zero-based tile coordinates under the mouse; matches map-file diagnostics."));
    buttons->addWidget(m_cellStatus);
    m_findLegacyButton = new QPushButton(tr("Find Legacy (0)"), this);
    m_findLegacyButton->setToolTip(tr("Jump to the next old per-pixel slope cell (collision type 7). "
        "Magenta L marks it when Show collisions is enabled."));
    buttons->addWidget(m_findLegacyButton);
    m_canvas->hoveredCellChanged = [this]() { updateCellStatus(); };
    connect(m_findLegacyButton, &QPushButton::clicked, this, [this, collisionOverlay]() {
        const int count = m_map.collisions.size();
        if (!count || !m_canvas) return;
        int found = -1;
        for (int step = 1; step <= count; ++step) {
            const int index = (m_lastLegacyIndex + step + count) % count;
            if (quint8(m_map.collisions.at(index)) == 7) {
                found = index;
                break;
            }
        }
        if (found < 0) { updateLegacyStatus(); return; }
        m_lastLegacyIndex = found;
        if (!collisionOverlay->isChecked()) collisionOverlay->setChecked(true);
        const int x = found % m_map.width;
        const int y = found / m_map.width;
        const int pixels = m_map.tileSize * m_canvas->zoom;
        m_canvas->horizontalScrollBar()->setValue(
            x * pixels + pixels / 2 - m_canvas->viewport()->width() / 2);
        m_canvas->verticalScrollBar()->setValue(
            y * pixels + pixels / 2 - m_canvas->viewport()->height() / 2);
        m_canvas->legacyFocusCell = QPoint(x, y);
        m_canvas->hoverValid = false;
        m_cellStatus->setText(tr("Col: %1  Row: %2  |  LEGACY SLOPE").arg(x).arg(y));
        m_canvas->viewport()->update();
    });
    updateLegacyStatus();
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
        // The saved project must contain the CURRENT pan, not the pan from
        // the last time the editor was opened.
        if (m_canvas) {
            m_map.viewPanX = m_canvas->horizontalScrollBar()->value() / qMax(1, m_canvas->zoom);
            m_map.viewPanY = m_canvas->verticalScrollBar()->value() / qMax(1, m_canvas->zoom);
        }
        if (m_saveCallback(m_map)) {
            saveViewSettings();
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
        { QSignalBlocker block(m_sizeY);
          m_sizeY->setMaximum(qMin(SIDBOX_MAP_MAX_AXIS,
                                   SIDBOX_MAP_MAX_CELLS / m_map.width)); }
        recordChange(before);
    });
    connect(sizeY, qOverload<int>(&QSpinBox::valueChanged), this, [this](int v) {
        const SidboxTilemap before = m_map;
        m_map.resizeMap(m_map.width, v); m_canvas->adjust();
        { QSignalBlocker block(m_sizeX);
          m_sizeX->setMaximum(qMin(SIDBOX_MAP_MAX_AXIS,
                                   SIDBOX_MAP_MAX_CELLS / m_map.height)); }
        recordChange(before);
    });
    connect(tileSize, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, tileSize](int) {
            if (m_canvas) m_canvas->deactivateTemporary();
            const SidboxTilemap before = m_map;
            m_map.collisionPlacements.clear();
            for (char &c : m_map.collisions) if (quint8(c) == 8) c = 0;
            m_map.tileSize = tileSize->currentData().toInt();
            m_canvas->adjust(); updateAtlasPicker(); updateAnimationControls();
            m_map.slopes = QByteArray(m_map.width * m_map.height * m_map.tileSize, char(0));
            for (char &type : m_map.collisions) if (quint8(type) == 7) type = 0;
            updateStampEditor(); updateStampList(); updateCollisionList();
            recordChange(before);
        });
    connect(atlasChoice, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, atlasChoice](int) {
            const SidboxTilemap before = m_map;
            setAtlas(atlasChoice->currentData().toString());
            recordChange(before);
        });
    // Icon strips mirror their original combo values, including when an
    // atlas click or a custom-zone selection changes the brush indirectly.
    auto syncGraphicModes = [this, brushG]() {
        const int mode = brushG->currentData().toInt();
        for (auto pair : {std::pair<QToolButton*, int>{m_graphicKeep, -1},
                          {m_graphicEmpty, 0}, {m_graphicAtlas, 1}}) {
            const QSignalBlocker blocked(pair.first);
            pair.first->setChecked(mode == pair.second);
        }
    };
    auto syncCollisionModes = [this, brushC]() {
        const int type = brushC->currentData().toInt();
        for (auto pair : {std::pair<QToolButton*, int>{m_collisionKeep, -1},
                          {m_collisionEmpty, 0}}) {
            const QSignalBlocker blocked(pair.first);
            pair.first->setChecked(type == pair.second);
        }
    };
    connect(m_graphicKeep, &QToolButton::clicked, this, [brushG, syncGraphicModes]() {
        brushG->setCurrentIndex(brushG->findData(-1)); syncGraphicModes();
    });
    connect(m_graphicEmpty, &QToolButton::clicked, this, [brushG, syncGraphicModes]() {
        brushG->setCurrentIndex(brushG->findData(0)); syncGraphicModes();
    });
    connect(m_graphicAtlas, &QToolButton::clicked, this, [brushG, syncGraphicModes]() {
        brushG->setCurrentIndex(brushG->findData(1)); syncGraphicModes();
    });
    connect(m_collisionKeep, &QToolButton::clicked, this, [brushC, syncCollisionModes]() {
        brushC->setCurrentIndex(brushC->findData(-1)); syncCollisionModes();
    });
    connect(m_collisionEmpty, &QToolButton::clicked, this, [brushC, syncCollisionModes]() {
        brushC->setCurrentIndex(brushC->findData(0)); syncCollisionModes();
    });
    connect(brushG, qOverload<int>(&QComboBox::currentIndexChanged),
            this, [syncGraphicModes](int) { syncGraphicModes(); });
    connect(brushC, qOverload<int>(&QComboBox::currentIndexChanged),
            this, [syncCollisionModes](int) { syncCollisionModes(); });
    syncGraphicModes();
    syncCollisionModes();
    connect(brushG, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, brushG](int) {
            m_canvas->graphicMode = brushG->currentData().toInt();
            m_stampCanvas->graphicMode = m_canvas->graphicMode;
            m_canvas->viewport()->update();
            m_stampCanvas->update();
        });
    const auto syncFlagModes = [this]() {
        const int mode = m_flipMode->currentData().toInt();
        const QSignalBlocker applyBlocked(m_flagApply);
        const QSignalBlocker keepBlocked(m_flagKeep);
        m_flagApply->setChecked(mode == 1);
        m_flagKeep->setChecked(mode == -1);
    };
    connect(m_flagApply, &QToolButton::clicked, this, [this, syncFlagModes]() {
        m_flipMode->setCurrentIndex(m_flipMode->findData(1));
        syncFlagModes();
    });
    connect(m_flagKeep, &QToolButton::clicked, this, [this, syncFlagModes]() {
        m_flipMode->setCurrentIndex(m_flipMode->findData(-1));
        syncFlagModes();
    });
    connect(m_flipMode, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, syncFlagModes](int) {
            syncFlagModes();
            const int mode = m_flipMode->currentData().toInt();
            m_canvas->flipMode = mode;
            m_stampCanvas->flipMode = mode;
            m_canvas->viewport()->update();
            m_stampCanvas->update();
        });
    syncFlagModes();
    auto updateFlipBrush = [this]() {
        const quint8 flags = quint8((m_flipX->isChecked() ? 1 : 0) |
                                   (m_flipY->isChecked() ? 2 : 0) |
                                   (m_drawFront->isChecked() ? 4 : 0));
        m_canvas->flipBrush = flags;
        m_stampCanvas->flipBrush = flags;
        m_canvas->viewport()->update();
        m_stampCanvas->update();
    };
    connect(m_flipX, &QToolButton::toggled, this, [updateFlipBrush](bool) { updateFlipBrush(); });
    connect(m_flipY, &QToolButton::toggled, this, [updateFlipBrush](bool) { updateFlipBrush(); });
    connect(m_drawFront, &QToolButton::toggled, this, [updateFlipBrush](bool) { updateFlipBrush(); });
    connect(m_stampUseFront, &QToolButton::toggled, this, [this](bool enabled) {
        m_canvas->stampUseFrontBrush = enabled;
        m_canvas->viewport()->update();
    });
    m_canvas->stampUseFrontBrush = m_stampUseFront->isChecked();
    updateFlipBrush();
    auto updateStampMirror = [this]() {
        m_canvas->stampMirror = quint8((m_stampMirrorX->isChecked() ? 1 : 0) |
                                              (m_stampMirrorY->isChecked() ? 2 : 0));
        m_canvas->viewport()->update();
    };
    connect(m_stampMirrorX, &QToolButton::toggled, this, [updateStampMirror](bool) { updateStampMirror(); });
    connect(m_stampMirrorY, &QToolButton::toggled, this, [updateStampMirror](bool) { updateStampMirror(); });
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
    // Keep the dropdown synchronised with zoom changes made by wheel or numpad.
    m_canvas->zoomChanged = [zoom](int value) {
        const QSignalBlocker blocker(zoom);
        zoom->setCurrentIndex(zoom->findData(value));
    };
    connect(zoom, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [this, zoom](int) {
            m_canvas->setZoom(zoom->currentData().toInt(),
                              m_canvas->viewport()->rect().center());
        });
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
    m_canvas->graphicBrush = qBound(1,
        windowSettings.value(QStringLiteral("GameTilemapEditor/graphicId"), 1).toInt(),
        m_atlas.isNull() ? 65535 : qMax(1, (m_atlas.width() / m_map.tileSize) *
                                             (m_atlas.height() / m_map.tileSize)));
    m_canvas->graphicMode = brushG->currentData().toInt();
    m_stampCanvas->graphicMode = m_canvas->graphicMode;
    m_canvas->collisionBrush = brushC->currentData().toInt();
    m_stampCanvas->collisionBrush = m_canvas->collisionBrush;
    m_canvas->flipMode = m_flipMode->currentData().toInt();
    m_stampCanvas->flipMode = m_canvas->flipMode;
    m_canvas->zoom = zoom->currentData().toInt();
    m_stampCanvas->graphicBrush = m_canvas->graphicBrush;
    updateAtlasPicker();
    m_canvas->adjust();
    // This position is saved in the project's tilemap JSON (.sbgm), not
    // QSettings, so sharing/reopening the project restores the same view.
    // Restore only after the scroll area's viewport has its final size.
    QTimer::singleShot(0, this, [this]() {
        if (!m_canvas) return;
        m_canvas->adjust();
        m_canvas->horizontalScrollBar()->setValue(m_map.viewPanX * m_canvas->zoom);
        m_canvas->verticalScrollBar()->setValue(m_map.viewPanY * m_canvas->zoom);
    });
    updateStampList();
    updateCollisionList();
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
    updateCollisionList();
    if (m_stampCanvas) m_stampCanvas->update();
    if (m_collisionCanvas) m_collisionCanvas->update();
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
                    painter.drawImage(dest, (flip & 3) ? tileImage.flipped(Qt::Orientations(static_cast<Qt::Orientation>(flip & 3))) : tileImage);
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
    if (m_canvas && m_canvas->temporaryActive) m_canvas->deactivateTemporary();
    if (m_stampTabs && m_stampTabs->currentIndex() != 0) {
        if (m_collisionCanvas && row >= 0 && row < m_map.stamps.size()) {
            m_collisionCanvas->referenceStamp = row;
            m_collisionCanvas->update();
        }
        updateStampEditor();
        return;
    }
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
    if (m_collisionCanvas && row >= 0 && row < m_map.stamps.size()) {
        m_collisionCanvas->referenceStamp = row;
        m_collisionCanvas->update();
    }
    if (m_canvas) m_canvas->viewport()->update();
}

bool SidboxTilemapEditor::resizeSelectedCollisionStamp(int width, int height)
{
    if (!m_collisionList) return false;
    const int row = m_collisionList->currentRow();
    if (row < 0 || row >= m_map.collisionStamps.size()) return false;
    const SidboxCollisionStamp old = m_map.collisionStamps.at(row);
    if (old.width == width && old.height == height) return true;
    const SidboxTilemap before = m_map;
    SidboxCollisionStamp resized = old;
    resized.resizeStamp(width, height);

    // The new footprints of ALL copies must fit without intersecting any
    // other placed slope. Existing data not owned by these copies is protected.
    const int cellCount = m_map.width * m_map.height;
    QByteArray owned(cellCount, char(0));
    QByteArray reserved(cellCount, char(0));
    for (const auto &place : m_map.collisionPlacements) {
        if (place.stamp != row) continue;
        for (int y = place.y; y < place.y + old.height; ++y)
            for (int x = place.x; x < place.x + old.width; ++x)
                if (x >= 0 && y >= 0 && x < m_map.width && y < m_map.height)
                    owned[y * m_map.width + x] = char(1);
    }
    QString reason;
    for (const auto &place : m_map.collisionPlacements) {
        if (place.stamp != row) continue;
        if (place.x < 0 || place.y < 0 ||
            place.x + width > m_map.width || place.y + height > m_map.height) {
            reason = tr("A resized slope would extend beyond the map.");
            break;
        }
        for (int y = place.y; y < place.y + height && reason.isEmpty(); ++y)
            for (int x = place.x; x < place.x + width; ++x) {
                const int index = y * m_map.width + x;
                if (reserved.at(index)) {
                    reason = tr("Resized copies of this slope would overlap.");
                    break;
                }
                reserved[index] = char(1);
                if (!owned.at(index) && quint8(m_map.collisions.at(index)) != 0) {
                    reason = tr("A resized slope would overwrite another collision. Clear that area first.");
                    break;
                }
            }
    }
    // Check that other collision stamps' footprints remain untouched.
    for (const auto &place : m_map.collisionPlacements) {
        if (place.stamp == row || place.stamp < 0 ||
            place.stamp >= m_map.collisionStamps.size()) continue;
        const auto &other = m_map.collisionStamps.at(place.stamp);
        for (int y = place.y; y < place.y + other.height && reason.isEmpty(); ++y)
            for (int x = place.x; x < place.x + other.width; ++x)
                if (x >= 0 && y >= 0 && x < m_map.width && y < m_map.height &&
                    reserved.at(y * m_map.width + x)) {
                    reason = tr("A resized slope would overlap another collision stamp.");
                    break;
                }
    }
    if (!reason.isEmpty()) {
        QMessageBox::information(this, tr("Collision stamp resize"), reason);
        return false;
    }
    for (int i = 0; i < cellCount; ++i)
        if (owned.at(i)) m_map.collisions[i] = char(0);
    m_map.collisionStamps[row] = resized;
    for (int i = 0; i < cellCount; ++i)
        if (reserved.at(i)) m_map.collisions[i] = char(8);
    recordChange(before);
    updateCollisionList(row);
    m_canvas->viewport()->update();
    return true;
}

void SidboxTilemapEditor::updateCollisionList(int wantedRow)
{
    if (!m_collisionList) return;
    if (wantedRow == -2) wantedRow = m_collisionList->currentRow();
    const QSignalBlocker block(m_collisionList);
    m_collisionList->clear();
    for (const auto &stamp : m_map.collisionStamps) {
        QPixmap preview(104, 76);
        preview.fill(QColor(28, 37, 49));
        QPainter painter(&preview);
        QPolygonF line;
        for (const QPoint &pt : stamp.points)
            line << QPointF(pt.x() * 104.0 / (stamp.width * stamp.tileSize),
                            pt.y() * 76.0 / (stamp.height * stamp.tileSize));
        QPolygonF fill = line;
        fill << QPointF(104, 76) << QPointF(0, 76);
        painter.setBrush(QColor(45, 189, 157, 95));
        painter.setPen(Qt::NoPen);
        painter.drawPolygon(fill);
        painter.setBrush(Qt::NoBrush);
        painter.setPen(QPen(QColor(73, 255, 207), 2));
        painter.drawPolyline(line);
        m_collisionList->addItem(new QListWidgetItem(QIcon(preview), stamp.name));
    }
    const int selected = wantedRow >= 0 && wantedRow < m_map.collisionStamps.size() ? wantedRow : -1;
    m_collisionList->setCurrentRow(selected);
    updateCollisionEditorControls();
}

void SidboxTilemapEditor::updateCollisionEditorControls()
{
    if (!m_collisionList || !m_collisionCanvas) return;
    const int selected = m_collisionList->currentRow();
    const bool valid = selected >= 0 && selected < m_map.collisionStamps.size();
    if (!valid && m_collisionViews && m_collisionViews->currentIndex() != 0)
        m_collisionViews->setCurrentIndex(0);
    if (m_collisionCanvas->selected != selected) {
        // Changing stamps also changes the editor, not just the painting brush.
        m_collisionCanvas->selected = selected;
        m_collisionCanvas->active = -1;
    }
    m_collisionCanvas->refresh();
    m_collisionName->setEnabled(valid);
    m_collisionWidth->setEnabled(valid);
    m_collisionHeight->setEnabled(valid);
    m_collisionPassive->setEnabled(valid);
    const bool slideEnabled = valid && m_map.collisionStamps.at(selected).passiveSurface;
    m_collisionDamping->setEnabled(slideEnabled);
    m_collisionDampingSlider->setEnabled(slideEnabled);
    const QSignalBlocker passiveBlock(m_collisionPassive);
    const QSignalBlocker dampingBlock(m_collisionDamping);
    const QSignalBlocker sliderBlock(m_collisionDampingSlider);
    m_collisionPassive->setChecked(slideEnabled);
    m_collisionDamping->setValue(valid ? m_map.collisionStamps.at(selected).dampingPercent : 2);
    m_collisionDampingSlider->setValue(m_collisionDamping->value());
    const QSignalBlocker nameBlock(m_collisionName);
    const QSignalBlocker widthBlock(m_collisionWidth);
    const QSignalBlocker heightBlock(m_collisionHeight);
    m_collisionName->setText(valid ? m_map.collisionStamps.at(selected).name : QString());
    m_collisionWidth->setValue(valid ? m_map.collisionStamps.at(selected).width : 2);
    m_collisionHeight->setValue(valid ? m_map.collisionStamps.at(selected).height : 2);
    updateCollisionPointControls();
}

void SidboxTilemapEditor::updateCollisionPointControls()
{
    if (!m_collisionCanvas || !m_collisionPointX || !m_collisionPointY) return;
    const int selected = m_collisionCanvas->selected;
    const bool shapeValid = selected >= 0 && selected < m_map.collisionStamps.size();
    const int point = m_collisionCanvas->active;
    const bool valid = shapeValid && point >= 0 &&
                       point < m_map.collisionStamps.at(selected).points.size();
    const bool interior = valid && point > 0 &&
                          point < m_map.collisionStamps.at(selected).points.size()-1;
    const QSignalBlocker xb(m_collisionPointX);
    const QSignalBlocker yb(m_collisionPointY);
    m_collisionPointLabel->setText(valid ? tr("Point %1").arg(point + 1) : tr("Point: none"));
    m_collisionPointX->setEnabled(interior);
    m_collisionPointY->setEnabled(valid);
    if (valid) {
        const auto &shape = m_map.collisionStamps.at(selected);
        const int left = interior ? shape.points.at(point-1).x()+1 : shape.points.at(point).x();
        const int right = interior ? shape.points.at(point+1).x()-1 : shape.points.at(point).x();
        m_collisionPointX->setRange(left, right);
        m_collisionPointX->setValue(shape.points.at(point).x());
        m_collisionPointY->setRange(0, shape.height * shape.tileSize);
        m_collisionPointY->setValue(shape.points.at(point).y());
    } else {
        m_collisionPointX->setRange(0, 0);
        m_collisionPointY->setRange(0, 0);
    }
    m_collisionInsertPoint->setEnabled(shapeValid &&
        m_map.collisionStamps.at(selected).points.size() < 128 &&
        (m_map.collisionStamps.at(selected).width * m_map.collisionStamps.at(selected).tileSize + 1 >
         m_map.collisionStamps.at(selected).points.size()));
    m_collisionDeletePoint->setEnabled(interior);
}

void SidboxTilemapEditor::openCollisionStampEditor(int row)
{
    if (!m_collisionViews || !m_collisionList || !m_stampTabs ||
        row < 0 || row >= m_map.collisionStamps.size()) return;
    // A bank single-click still selects the paint brush. Double-click (or
    // Shift-click on a placed slope) opens the editor without copying data.
    m_stampTabs->setCurrentIndex(1);
    m_collisionList->setCurrentRow(row);
    selectCollisionStamp(row);
    // Capture before entering the editor so X genuinely cancels ALL slope
    // changes, including size and edits to placed copies, without leaving
    // cancelled edits on the undo stack.
    m_collisionEditBefore = m_map;
    m_collisionEditUndoBefore = m_undoStack;
    m_collisionEditRedoBefore = m_redoStack;
    m_collisionEditIndex = row;
    m_collisionEditStatusBefore = m_saveStatus ? m_saveStatus->text() : QString();
    m_collisionEditActive = true;
    m_collisionViews->setCurrentIndex(1);
    updateCollisionEditorControls();
    m_collisionCanvas->setFocus(Qt::OtherFocusReason);
}

void SidboxTilemapEditor::finishCollisionStampEdit(bool accept)
{
    if (!m_collisionViews || !m_collisionList || !m_collisionEditActive) return;
    const int row = m_collisionEditIndex;
    m_collisionEditActive = false;
    m_collisionEditIndex = -1;
    if (!accept) {
        restoreMap(m_collisionEditBefore);
        m_undoStack = m_collisionEditUndoBefore;
        m_redoStack = m_collisionEditRedoBefore;
        updateHistoryActions();
        if (m_saveStatus) m_saveStatus->setText(m_collisionEditStatusBefore);
    }
    // Release snapshots once the transaction is finished.
    m_collisionEditBefore = SidboxTilemap();
    m_collisionEditUndoBefore.clear();
    m_collisionEditRedoBefore.clear();
    m_collisionEditStatusBefore.clear();
    m_collisionViews->setCurrentIndex(0);
    updateCollisionList(row);
    m_collisionList->setFocus();
}

void SidboxTilemapEditor::selectCollisionStamp(int row)
{
    if (m_canvas && m_canvas->temporaryActive) m_canvas->deactivateTemporary();
    if (!m_collisionList || !m_stampTabs || m_stampTabs->currentIndex() != 1) return;
    updateCollisionEditorControls();
    m_canvas->stampIndex = -1;
    m_canvas->collisionStampIndex = row >= 0 && row < m_map.collisionStamps.size() &&
        m_map.collisionStamps.at(row).tileSize == m_map.tileSize ? row : -1;
    if (m_stampStatus) m_stampStatus->setText(m_canvas->collisionStampIndex >= 0
        ? tr("Brush: collision stamp '%1'").arg(m_map.collisionStamps.at(row).name)
        : tr("Brush: no compatible collision stamp"));
    m_canvas->viewport()->update();
}

void SidboxTilemapEditor::updateAtlasPicker()
{
    if (!m_atlasPicker || !m_canvas) return;
    if (m_atlas.isNull()) {
        m_atlasPicker->setPixmap(QPixmap());
        m_atlasPicker->setText(tr("No PPB tile sheet selected (IDs only)."));
        m_atlasPicker->adjustSize();
    } else {
        // Reflow the entire 1-based atlas ID sequence into the available
        // sidebar width. All cells stay accessible via vertical scrolling.
        const int cellPixels = m_map.tileSize * 2;
        const int sourceCols = m_atlas.width() / m_map.tileSize;
        const int sourceRows = m_atlas.height() / m_map.tileSize;
        const int available = m_atlasArea ? m_atlasArea->viewport()->width() : 256;
        m_atlasDisplayColumns = qMax(1, qMin(sourceCols,
                                             qMax(1, available / cellPixels)));
        const int count = sourceCols * sourceRows;
        const int displayRows = (count + m_atlasDisplayColumns - 1) / m_atlasDisplayColumns;
        QImage display(m_atlasDisplayColumns * cellPixels,
                       displayRows * cellPixels, QImage::Format_ARGB32_Premultiplied);
        display.fill(QColor(27, 35, 46));
        QPainter painter(&display);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, false);
        for (int id = 0; id < count; ++id) {
            const QRect from((id % sourceCols) * m_map.tileSize,
                             (id / sourceCols) * m_map.tileSize,
                             m_map.tileSize, m_map.tileSize);
            const QRect dest((id % m_atlasDisplayColumns) * cellPixels,
                             (id / m_atlasDisplayColumns) * cellPixels,
                             cellPixels, cellPixels);
            painter.drawImage(dest, m_atlas, from);
        }
        const int selected = m_canvas->graphicBrush - 1;
        if (selected >= 0 && selected < count) {
            painter.setPen(QPen(QColor(255, 217, 65), 2));
            painter.drawRect(QRect((selected % m_atlasDisplayColumns) * cellPixels,
                                   (selected / m_atlasDisplayColumns) * cellPixels,
                                   cellPixels, cellPixels).adjusted(1, 1, -2, -2));
        }
        painter.end();
        m_atlasPicker->setPixmap(QPixmap::fromImage(display));
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

void SidboxTilemapEditor::saveViewSettings()
{
    if (!m_canvas) return;
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.setValue(QStringLiteral("GameTilemapEditor/zoom"), m_canvas->zoom);
    settings.setValue(QStringLiteral("GameTilemapEditor/collisionBrush"), m_canvas->collisionBrush);
    settings.setValue(QStringLiteral("GameTilemapEditor/graphicMode"), m_canvas->graphicMode);
    settings.setValue(QStringLiteral("GameTilemapEditor/graphicId"), m_canvas->graphicBrush);
    settings.setValue(QStringLiteral("GameTilemapEditor/flipMode"), m_canvas->flipMode);
    settings.setValue(QStringLiteral("GameTilemapEditor/brushFlags"), m_canvas->flipBrush);
    settings.setValue(QStringLiteral("GameTilemapEditor/stampUseFront"),
                      m_canvas->stampUseFrontBrush);
    // Pan belongs to the tilemap JSON and is captured on Save/Apply,
    // not in application-global settings. Cancel must not modify the project.
}

void SidboxTilemapEditor::done(int result)
{
    // QDialog::accept() reaches here before the owner calls result().
    // Cancel retains the previously committed pan in the project.
    if (result == QDialog::Accepted && m_canvas) {
        m_map.viewPanX = m_canvas->horizontalScrollBar()->value() / qMax(1, m_canvas->zoom);
        m_map.viewPanY = m_canvas->verticalScrollBar()->value() / qMax(1, m_canvas->zoom);
    }
    saveViewSettings();
    // Save for Apply and Cancel alike: window state is a user preference,
    // not a tilemap edit. saveGeometry includes the maximised state.
    QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
    settings.setValue(QStringLiteral("GameTilemapEditor/geometry"), saveGeometry());
    if (m_splitter)
        settings.setValue(QStringLiteral("GameTilemapEditor/splitter"), m_splitter->saveState());
    QDialog::done(result);
}

void SidboxTilemapEditor::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && m_canvas && m_canvas->temporaryActive) {
        m_canvas->deactivateTemporary();
        event->accept();
        return;
    }
    if (event->key() == Qt::Key_Escape && m_collisionViews &&
        m_stampTabs && m_stampTabs->currentIndex() == 1 &&
        m_collisionViews->currentIndex() == 1) {
        finishCollisionStampEdit(false);
        event->accept();
        return;
    }
    QDialog::keyPressEvent(event);
}

bool SidboxTilemapEditor::eventFilter(QObject *target, QEvent *event)
{
    if (m_atlasArea && target == m_atlasArea->viewport() &&
        event->type() == QEvent::Resize && !m_atlas.isNull()) {
        const auto *resizeEvent = static_cast<QResizeEvent *>(event);
        const int columns = qMax(1, qMin(m_atlas.width() / m_map.tileSize,
            qMax(1, resizeEvent->size().width() / (m_map.tileSize * 2))));
        if (columns != m_atlasDisplayColumns)
            QTimer::singleShot(0, this, [this]() { updateAtlasPicker(); });
    }
    if (target == m_atlasPicker && event->type() == QEvent::MouseButtonPress &&
        !m_atlas.isNull() && m_graphicMode) {
        const auto *mouse = static_cast<QMouseEvent *>(event);
        if (mouse->button() == Qt::LeftButton) {
            const int cols = m_atlas.width() / m_map.tileSize;
            const int rows = m_atlas.height() / m_map.tileSize;
            const int tx = int(mouse->position().x()) / (2*m_map.tileSize);
            const int ty = int(mouse->position().y()) / (2*m_map.tileSize);
            const int id = ty * m_atlasDisplayColumns + tx + 1;
            if (cols && tx >= 0 && tx < m_atlasDisplayColumns && ty >= 0 &&
                id <= cols * rows && id > 0) {
                if (id <= 65535) {
                    m_canvas->deactivateTemporary();
                    m_canvas->graphicBrush = id;
                    m_canvas->stampIndex = -1;
                    m_canvas->collisionStampIndex = -1;
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

// Friendly custom-zone names are design-specific, not properties of the
// shared player engine. Generate legal, collision-free C symbols for the
// exported world header.
// All eight stable numeric fallbacks remain available even when unnamed.
static QString cZoneLabel(const QString &label)
{
    QString out;
    for (QChar ch : label.trimmed().toUpper()) {
        const ushort c = ch.unicode();
        if ((c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9')) {
            out += ch;
        } else if (!out.isEmpty() && !out.endsWith(QLatin1Char('_'))) {
            out += QLatin1Char('_');
        }
    }
    while (out.endsWith(QLatin1Char('_'))) out.chop(1);
    if (!out.isEmpty() && out.at(0).isDigit()) out.prepend(QStringLiteral("N_"));
    return out;
}

static QStringList cZoneSymbols(const SidboxTilemap &map)
{
    QStringList symbols;
    QSet<QString> reserved;
    for (int zone = 1; zone <= 8; ++zone) {
        const QString fallback = QStringLiteral("GAME_ZONE_ID_CUSTOM_%1").arg(zone);
        symbols.append(fallback);
        reserved.insert(fallback);
    }
    for (int zone = 1; zone <= 8; ++zone) {
        const QString label = zone - 1 < map.customZoneNames.size()
            ? map.customZoneNames.at(zone - 1) : QString();
        const QString cleaned = cZoneLabel(label);
        if (cleaned.isEmpty()) continue;
        QString name = QStringLiteral("GAME_ZONE_ID_") + cleaned;
        if (name == symbols.at(zone - 1)) continue;
        // Avoid a collision with another zone's stable name, or a prior alias.
        if (reserved.contains(name))
            name += QStringLiteral("_Z%1").arg(zone);
        const QString uniqueBase = name;
        int suffix = 2;
        while (reserved.contains(name))
            name = uniqueBase + QStringLiteral("_%1").arg(suffix++);
        symbols[zone - 1] = name;
        reserved.insert(name);
    }
    return symbols;
}

QString sidboxTilemapZoneMacroName(const SidboxTilemap &map, int zone)
{
    if (zone < 1 || zone > 8) return QString();
    return cZoneSymbols(map).at(zone - 1);
}

QString sidboxTilemapWorldBaseName(const QString &designFilePath)
{
    QString text = QFileInfo(designFilePath).completeBaseName().trimmed();
    if (text.isEmpty()) text = QStringLiteral("level1");

    QString out;
    out.reserve(text.size() + 1);
    for (int i = 0; i < text.size(); ++i) {
        const QChar ch = text.at(i);
        if (ch.isLetterOrNumber() || ch == QLatin1Char('_')) out += ch;
        else out += QLatin1Char('_');
    }
    if (out.isEmpty()) out = QStringLiteral("level1");
    if (out.at(0).isDigit()) out.prepend(QLatin1Char('_'));
    return out;
}

bool sidboxExportTilemap(const SidboxTilemap &map, const QString &designDirectory,
                         QString *error, bool externalMap, const QString &designFilePath,
                         const QString &rulesDirectory)
{
    if (map.width < 30 || map.width > SIDBOX_MAP_MAX_AXIS ||
        map.height < 20 || map.height > SIDBOX_MAP_MAX_AXIS ||
        qint64(map.width) * map.height > SIDBOX_MAP_MAX_CELLS ||
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
    const bool custom = map.collisions.contains(char(7)); // legacy v3 data
    if (map.loops.size() > 32) {
        if (error) *error = QStringLiteral("Too many loop tracks (maximum 32).");
        return false;
    }
    for (const auto &l : map.loops) {
        if (l.downhillBoost100 < 0 || l.downhillBoost100 > 200 ||
            l.radius < 16 || l.radius > 512 || l.entrySpeed100 < 100 ||
            l.entrySpeed100 > 3200 || l.centerX < l.radius || l.centerY < l.radius ||
            l.centerX + l.radius >= map.width*map.tileSize ||
            l.centerY + l.radius >= map.height*map.tileSize) {
            if (error) *error = QStringLiteral("Loop track geometry is outside the level.");
            return false;
        }
    }
    const bool pointShapes = !map.collisionPlacements.isEmpty();
    QVector<int> usedShapes;
    QVector<int> shapeRemap(map.collisionStamps.size(), -1);
    if (pointShapes && (map.collisionStamps.isEmpty() ||
                       map.collisionStamps.size() > 128 ||
                       map.collisionPlacements.size() > 65535)) {
        if (error) *error = QStringLiteral("Invalid collision shape database.");
        return false;
    }
    for (const auto &place : map.collisionPlacements) {
        if (place.stamp < 0 || place.stamp >= map.collisionStamps.size()) {
            if (error) *error = QStringLiteral("Collision instance references a missing stamp.");
            return false;
        }
        if (shapeRemap.at(place.stamp) < 0) {
            const auto &shape = map.collisionStamps.at(place.stamp);
            if (shape.tileSize != map.tileSize || !validSlopePoints(shape)) {
                if (error) *error = QStringLiteral("Invalid point-defined collision stamp.");
                return false;
            }
            shapeRemap[place.stamp] = usedShapes.size();
            usedShapes.append(place.stamp);
        }
    }
    QByteArray shapeRefs(map.width * map.height * 2, char(0));
    for (int n = 0; n < map.collisionPlacements.size(); ++n) {
        const auto &place = map.collisionPlacements.at(n);
        if (place.stamp < 0 || place.stamp >= map.collisionStamps.size() ||
            place.x < 0 || place.y < 0 ||
            place.x + map.collisionStamps.at(place.stamp).width > map.width ||
            place.y + map.collisionStamps.at(place.stamp).height > map.height) {
            if (error) *error = QStringLiteral("Collision placement outside map or invalid shape.");
            return false;
        }
        const auto &shape = map.collisionStamps.at(place.stamp);
        for (int yy = place.y; yy < place.y + shape.height; ++yy)
            for (int xx = place.x; xx < place.x + shape.width; ++xx) {
                const int i = yy * map.width + xx;
                if (quint8(map.collisions.at(i)) != 8 ||
                    shapeRefs.at(i * 2) != 0 || shapeRefs.at(i * 2 + 1) != 0) {
                    if (error) *error = QStringLiteral("Overlapping/missing collision placement cells.");
                    return false;
                }
                const int ref = n + 1;
                shapeRefs[i * 2] = char(ref & 255);
                shapeRefs[i * 2 + 1] = char((ref >> 8) & 255);
            }
    }
    if (custom && map.slopes.size() != map.width * map.height * map.tileSize) {
        if (error) *error = QStringLiteral("Custom slope data missing or mismatched.");
        return false;
    }
    for (int i = 0; i < map.width * map.height; ++i) {
        if (quint8(map.collisions.at(i)) > 24) {
            if (error) *error = QStringLiteral("Invalid collision type.");
            return false;
        }
        if (quint8(map.collisions.at(i)) == 8 &&
            !quint8(shapeRefs.at(i * 2)) && !quint8(shapeRefs.at(i * 2 + 1))) {
            if (error) *error = QStringLiteral("Orphaned point-slope tile.");
            return false;
        }
        if (quint8(map.collisions.at(i)) == 7)
            for (int x = 0; x < map.tileSize; ++x)
                if (quint8(map.slopes.at(i * map.tileSize + x)) > map.tileSize) {
                    if (error) *error = QStringLiteral("Invalid custom slope height.");
                    return false;
                }
    }
    for (char flags : map.flips) {
        if (quint8(flags) & ~quint8(7)) {
            if (error) *error = QStringLiteral("Invalid tile flags (X/Y/Front supported).");
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
    // Reject a map that would exceed the SIDBOX runtime loader's bounded
    // resident allocation, rather than generating a file the device rejects.
    // v2/v3: 4 bytes/cell (+ legacy slope bytes); v4: 6 bytes/cell
    // (+ legacy slope bytes, shape definitions, points and placements).
    if (externalMap) {
        qint64 sdBytes = qint64(map.width) * map.height *
            (pointShapes ? 6 : 4) + (custom ? qint64(map.slopes.size()) : 0);
        if (pointShapes) {
            sdBytes += 2 + qint64(usedShapes.size()) * 8 +
                       qint64(map.collisionPlacements.size()) * 6;
            for (int id : usedShapes)
                sdBytes += qint64(map.collisionStamps.at(id).points.size()) * 4;
        }
        sdBytes += 4 + qint64(map.animations.size()) * 6;
        if (sdBytes > 3ll * 1024 * 1024) {
            if (error) *error = QStringLiteral(
                "SD map needs %1 MiB of SDRAM, exceeding the 3 MiB map budget. "
                "Reduce the map area or convert legacy slopes to compact point slopes.")
                .arg(double(sdBytes) / (1024.0 * 1024.0), 0, 'f', 2);
            return false;
        }
        if (map.animations.size() > 128) {
            if (error) *error = QStringLiteral("SD maps support up to 128 animations.");
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
    const QString worldBase = sidboxTilemapWorldBaseName(designFilePath);
    const QString worldSymbol = QStringLiteral("game_") + worldBase;
    const QString worldHeader = worldBase + QStringLiteral(".h");
    const QString worldSource = worldBase + QStringLiteral(".c");
    const QString worldMap = worldBase + QStringLiteral(".map");
    if (!QDir().mkpath(folder)) {
        if (error) *error = QStringLiteral("Cannot create gamelevels directory.");
        return false;
    }
    // Stage 4.51: template is the executable C; Qt supplies tile IDs,
    // collision rows, named zones, animation, loop and atlas metadata.
    const QDir rules(rulesDirectory);
    QMap<QString, QByteArray> templates, sections;
    const QRegularExpression sectionRe(QStringLiteral(
        R"((?ms)^@IDE_SECTION\{([A-Z_][A-Z0-9_]*)\}[ \t]*\r?\n(.*?)^@IDE_SECTION_END[ \t]*\r?\n?)"));
    for (const QString &ext : {QStringLiteral(".rulec"), QStringLiteral(".ruleh")}) {
        QFile file(rules.filePath(QStringLiteral("worldmap") + ext));
        if (!file.open(QIODevice::ReadOnly)) {
            if (error) *error = QStringLiteral("Cannot read tilemap rule: %1").arg(file.fileName());
            return false;
        }
        QString raw = QString::fromUtf8(file.readAll());
        auto matches = sectionRe.globalMatch(raw);
        const int expected = raw.count(QStringLiteral("@IDE_SECTION{"));
        int extracted = 0;
        while (matches.hasNext()) {
            const auto match = matches.next();
            if (sections.contains(match.captured(1))) {
                if (error) *error = QStringLiteral("Duplicate tilemap rule section: %1").arg(match.captured(1));
                return false;
            }
            sections.insert(match.captured(1), match.captured(2).toUtf8());
            ++extracted;
        }
        raw.remove(sectionRe);
        if (expected != extracted || raw.contains(QStringLiteral("@IDE_SECTION"))) {
            if (error) *error = QStringLiteral("Malformed section in %1").arg(file.fileName());
            return false;
        }
        templates.insert(ext, raw.toUtf8());
    }
    const auto num = [](auto v) { return QString::number(v); };
    auto renderZone = [&](const QString &name, const QMap<QString, QString> &fields,
                          QString &dest) -> bool {
        if (!sections.contains(name)) {
            if (error) *error = QStringLiteral("Missing tilemap rule section %1").arg(name);
            return false;
        }
        QByteArray rendered;
        if (!GameHelperTemplates::renderFields(sections.value(name), fields,
                 QStringLiteral("worldmap.ruleh / ") + name, &rendered, error)) return false;
        dest += QString::fromUtf8(rendered);
        return true;
    };
    QString zones;
    const QStringList zoneSymbols = cZoneSymbols(map);
    for (int zone = 1; zone <= 8; ++zone) {
        if (!renderZone(QStringLiteral("ZONE_ID"), {{QStringLiteral("ZONE"), num(zone)}}, zones)) return false;
    }
    for (int zone = 1; zone <= 8; ++zone) {
        const QString fallback = QStringLiteral("GAME_ZONE_ID_CUSTOM_%1").arg(zone);
        if (zoneSymbols.at(zone - 1) != fallback &&
            !renderZone(QStringLiteral("ZONE_ALIAS"),
                 {{QStringLiteral("ZONE"), num(zone)},
                  {QStringLiteral("ALIAS"), zoneSymbols.at(zone - 1)}}, zones)) return false;
    }
    const auto byteRows = [](const QByteArray &data) {
        QString result;
        for (int i = 0; i < data.size(); ++i) {
            if (i % 20 == 0) result += QStringLiteral("    ");
            result += QString::number(quint8(data.at(i)));
            if (i != data.size() - 1) result += QLatin1Char(',');
            if (i % 20 == 19 || i == data.size() - 1) result += QLatin1Char('\n');
            else result += QLatin1Char(' ');
        }
        return result;
    };
    QString graphics, shapeRefRows, shapeDefs, shapePoints, shapeInstances;
    if (!externalMap) {
        for (int i = 0, n = map.width * map.height; i < n; ++i) {
            if (i % 16 == 0) graphics += QStringLiteral("    ");
            graphics += num(mapGraphic(map.graphics, i));
            if (i != n - 1) graphics += QLatin1Char(',');
            if (i % 16 == 15 || i == n - 1) graphics += QLatin1Char('\n');
            else graphics += QLatin1Char(' ');
        }
        if (pointShapes) {
            for (int i = 0, n = map.width * map.height; i < n; ++i) {
                if (i % 16 == 0) shapeRefRows += QStringLiteral("    ");
                shapeRefRows += num(quint8(shapeRefs.at(i*2)) | (quint8(shapeRefs.at(i*2+1)) << 8));
                if (i != n - 1) shapeRefRows += QLatin1Char(',');
                if (i % 16 == 15 || i == n-1) shapeRefRows += QLatin1Char('\n');
                else shapeRefRows += QLatin1Char(' ');
            }
            int offset = 0;
            for (int id : usedShapes) {
                const auto &shape = map.collisionStamps.at(id);
                shapeDefs += QStringLiteral("    {%1, %2, %3, %4, %5, %6},\n")
                    .arg(shape.width).arg(shape.height).arg(offset).arg(shape.points.size())
                    .arg(shape.passiveSurface ? shape.dampingPercent : 0)
                    .arg(shape.passiveSurface ? 1 : 0);
                offset += shape.points.size();
                for (const QPoint &pt : shape.points)
                    shapePoints += QStringLiteral("    {%1, %2},\n").arg(pt.x()).arg(pt.y());
            }
            for (const auto &place : map.collisionPlacements)
                shapeInstances += QStringLiteral("    {%1, %2, %3, %4},\n")
                    .arg(place.x).arg(place.y).arg(shapeRemap.at(place.stamp))
                    .arg(place.mirrorX ? 1 : 0);
        }
    }
    QString animationRows;
    if (map.animations.isEmpty()) animationRows = QStringLiteral("    {0, 0, 0, 0} // No animations yet\n");
    else for (const SidboxTileAnimation &a : map.animations)
        animationRows += QStringLiteral("    {%1, %2, %3, %4},\n")
            .arg(a.graphicId).arg(a.frames).arg(a.frameTicks)
            .arg((a.loop ? 1 : 0) | (a.bounce ? 2 : 0));
    QString loopRows;
    for (const SidboxLoopTrack &l : map.loops)
        loopRows += QStringLiteral("    {%1, %2, %3, %4, %5, %6, %7},\n")
            .arg(l.centerX).arg(l.centerY).arg(l.radius).arg(l.entrySpeed100)
            .arg(l.downhillBoost100).arg(l.coastAfterExit ? 1 : 0).arg(l.coastFalloffPermille);
    QByteArray atlasPath = QDir::cleanPath(QDir::fromNativeSeparators(map.atlasPath)).toUtf8();
    atlasPath.replace("\\", "\\\\");
    atlasPath.replace("\"", "\\\"");
    const bool embedded = !externalMap;
    const QMap<QString, QString> cfields = {
        {QStringLiteral("EXTERNAL"), externalMap ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("EMBEDDED"), embedded ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("HAS_LEGACY_SLOPES"), custom ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("HAS_POINT_SHAPES"), pointShapes ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("HAS_LOOPS"), map.loops.isEmpty() ? QStringLiteral("0") : QStringLiteral("1")},
        {QStringLiteral("HAS_ATLAS"), tileCount ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("GRAPHIC_ROWS"), graphics},
        {QStringLiteral("COLLISION_ROWS"), byteRows(map.collisions)},
        {QStringLiteral("FLIP_ROWS"), byteRows(map.flips)},
        {QStringLiteral("SLOPE_ROWS"), byteRows(map.slopes)},
        {QStringLiteral("SHAPE_REF_ROWS"), shapeRefRows},
        {QStringLiteral("SHAPE_DEF_ROWS"), shapeDefs},
        {QStringLiteral("SHAPE_POINT_ROWS"), shapePoints},
        {QStringLiteral("SHAPE_INSTANCE_ROWS"), shapeInstances},
        {QStringLiteral("ANIMATION_ROWS"), animationRows},
        {QStringLiteral("LOOP_ROWS"), loopRows},
        {QStringLiteral("MAP_WIDTH"), num(map.width)},
        {QStringLiteral("MAP_HEIGHT"), num(map.height)},
        {QStringLiteral("TILE_SIZE"), num(map.tileSize)},
        {QStringLiteral("TILE_COUNT"), num(tileCount)},
        {QStringLiteral("ANIM_POINTER"), embedded && !map.animations.isEmpty() ? worldSymbol + QStringLiteral("_animations") : QStringLiteral("0")},
        {QStringLiteral("ANIM_COUNT"), embedded ? num(map.animations.size()) : QStringLiteral("0")},
        {QStringLiteral("FLIP_POINTER"), embedded ? worldSymbol + QStringLiteral("_flips") : QStringLiteral("0 /* TFCard flips loaded later */")},
        {QStringLiteral("SLOPE_POINTER"), embedded && custom ? worldSymbol + QStringLiteral("_slopes") : QStringLiteral("0")},
        {QStringLiteral("SHAPE_REF_POINTER"), embedded && pointShapes ? worldSymbol + QStringLiteral("_shape_refs") : QStringLiteral("0")},
        {QStringLiteral("SHAPE_INSTANCE_POINTER"), embedded && pointShapes ? worldSymbol + QStringLiteral("_shape_instances") : QStringLiteral("0")},
        {QStringLiteral("SHAPE_DEF_POINTER"), embedded && pointShapes ? worldSymbol + QStringLiteral("_shape_defs") : QStringLiteral("0")},
        {QStringLiteral("SHAPE_POINTS_POINTER"), embedded && pointShapes ? worldSymbol + QStringLiteral("_shape_points") : QStringLiteral("0")},
        {QStringLiteral("SHAPE_INSTANCE_COUNT"), embedded && pointShapes ? num(map.collisionPlacements.size()) : QStringLiteral("0")},
        {QStringLiteral("SHAPE_DEF_COUNT"), embedded && pointShapes ? num(usedShapes.size()) : QStringLiteral("0")},
        {QStringLiteral("LOOP_POINTER"), map.loops.isEmpty() ? QStringLiteral("0") : worldSymbol + QStringLiteral("_loops")},
        {QStringLiteral("LOOP_COUNT"), num(map.loops.size())},
        {QStringLiteral("ATLAS_PATH"), QStringLiteral("\"") + QString::fromUtf8(atlasPath) + QStringLiteral("\"")},
        {QStringLiteral("ATLAS_HASH"), num(atlasHash)},
        {QStringLiteral("ATLAS_WIDTH"), num(atlasWidth)},
        {QStringLiteral("ATLAS_HEIGHT"), num(atlasHeight)},
        {QStringLiteral("WORLD_HEADER_FILENAME"), worldHeader},
        {QStringLiteral("WORLD_SYMBOL"), worldSymbol}
    };
    const QMap<QString, QString> hfields = {
        {QStringLiteral("EMBEDDED"), embedded ? QStringLiteral("1") : QStringLiteral("0")},
        {QStringLiteral("ZONE_ROWS"), zones},
        {QStringLiteral("WORLD_HEADER_FILENAME"), worldHeader},
        {QStringLiteral("WORLD_HEADER_GUARD"), worldBase == QStringLiteral("level1")
             ? QStringLiteral("SIDBOX_GAME_LEVEL1_H")
             : QStringLiteral("SIDBOX_GAME_") + worldSymbol + QStringLiteral("_H")},
        {QStringLiteral("WORLD_SYMBOL"), worldSymbol}
    };
    QByteArray header, source, conditional;
    if (!templates.value(QStringLiteral(".ruleh")).contains("@IDE{ZONE_ROWS}") ||
        !templates.value(QStringLiteral(".rulec")).contains("@IDE{MAP_WIDTH}")) {
        if (error) *error = QStringLiteral("Tilemap rules are missing required generation markers.");
        return false;
    }
    if (!GameHelperTemplates::renderConditionals(templates.value(QStringLiteral(".ruleh")), hfields,
            QStringLiteral("worldmap.ruleh"), &conditional, error) ||
        !GameHelperTemplates::renderFields(conditional, hfields, QStringLiteral("worldmap.ruleh"), &header, error) ||
        !GameHelperTemplates::renderConditionals(templates.value(QStringLiteral(".rulec")), cfields,
            QStringLiteral("worldmap.rulec"), &conditional, error) ||
        !GameHelperTemplates::renderFields(conditional, cfields, QStringLiteral("worldmap.rulec"), &source, error)) return false;
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
        if (custom) payload += map.slopes;
        if (pointShapes) {
            payload += shapeRefs;
            const auto pushU16 = [&payload](int v) {
                payload.append(char(v & 255)); payload.append(char((v >> 8) & 255));
            };
            pushU16(map.collisionPlacements.size());
            int offset = 0;
            for (int id : usedShapes) {
                const auto &shape = map.collisionStamps.at(id);
                payload.append(char(shape.width)); payload.append(char(shape.height));
                pushU16(offset);
                payload.append(char(shape.points.size()));
                payload.append(char(shape.passiveSurface ? shape.dampingPercent : 0));
                pushU16(shape.passiveSurface ? 1 : 0);
                offset += shape.points.size();
            }
            for (int id : usedShapes)
                for (const QPoint &pt : map.collisionStamps.at(id).points) {
                    pushU16(pt.x()); pushU16(pt.y());
                }
            for (const auto &place : map.collisionPlacements) {
                pushU16(place.x); pushU16(place.y);
                payload.append(char(shapeRemap.at(place.stamp)));
                payload.append(char(place.mirrorX ? 1 : 0));
            }
        }
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
        bytes.append(char(pointShapes ? 4 : custom ? 3 : 2)); // v4 uses shared point shapes
        bytes.append(char(map.tileSize));
        const auto appendU16 = [&bytes](unsigned v) {
            bytes.append(char(v & 255)); bytes.append(char((v >> 8) & 255));
        };
        appendU16(unsigned(map.width)); appendU16(unsigned(map.height));
        appendU16(tileCount); appendU16(unsigned(map.animations.size()));
        for (int offset = 0; offset < 32; offset += 8)
            bytes.append(char((hash >> offset) & 255));
        bytes.append(char(pointShapes ? usedShapes.size() : 0));
        bytes.append(char(pointShapes && custom ? 1 : 0)); // v4 legacy-height presence
        bytes += payload;
        if (!atomic(QDir(folder).filePath(worldMap), bytes))
            return false;
    }
    return atomic(QDir(folder).filePath(worldHeader), header)
        && atomic(QDir(folder).filePath(worldSource), source);
}

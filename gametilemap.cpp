#include "gametilemap.h"
#include "ppbcodec.h"

#include <QAbstractScrollArea>
#include <QAbstractItemView>
#include <QComboBox>
#include <QCheckBox>
#include <QSettings>
#include <QCryptographicHash>
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
#include <QTabWidget>
#include <QPolygonF>
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

void SidboxCollisionStamp::resizeStamp(int w, int h)
{
    w = qBound(1, w, 16); h = qBound(1, h, 16);
    const int oldW = width * tileSize, oldH = height * tileSize;
    const int newW = w * tileSize, newH = h * tileSize;
    if (points.size() < 2)
        points = { QPoint(0, oldH / 2), QPoint(oldW, oldH / 2) };
    for (QPoint &p : points) {
        p.setX(oldW ? qRound(double(p.x()) * newW / oldW) : 0);
        p.setY(qBound(0, oldH ? qRound(double(p.y()) * newH / oldH) : 0, newH));
    }
    width = w; height = h;
    points.first().setX(0);
    points.last().setX(newW);
    // Shrinking a stamp may round neighbouring X coordinates together.
    // Remove duplicates so every runtime segment has a nonzero width.
    for (int i = points.size() - 2; i > 0; --i)
        if (points.at(i).x() <= points.at(i-1).x() ||
            points.at(i).x() >= points.at(i+1).x())
            points.removeAt(i);
}

static bool validSlopePoints(const SidboxCollisionStamp &stamp)
{
    if (stamp.points.size() < 2 || stamp.points.size() > 128 ||
        stamp.points.first().x() != 0 ||
        stamp.points.last().x() != stamp.width * stamp.tileSize) return false;
    int previous = -1;
    for (const QPoint &p : stamp.points) {
        if (p.x() <= previous || p.x() > stamp.width * stamp.tileSize ||
            p.y() < 0 || p.y() > stamp.height * stamp.tileSize) return false;
        previous = p.x();
    }
    return true;
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

void SidboxTilemap::resizeMap(int w, int h)
{
    w = qBound(30, w, 256);
    h = qBound(20, h, 256);
    QByteArray nextG(w * h * 2, char(0)), nextC(w * h, char(0)), nextF(w * h, char(0));
    QByteArray nextS(w * h * tileSize, char(0));
    for (int y = 0; y < qMin(h, height); ++y)
        for (int x = 0; x < qMin(w, width); ++x) {
            const int from = y * width + x, to = y * w + x;
            if (from * 2 + 1 < graphics.size()) {
                nextG[to * 2] = graphics.at(from * 2);
                nextG[to * 2 + 1] = graphics.at(from * 2 + 1);
            }
            if (from < collisions.size()) nextC[to] = collisions.at(from);
            if (from < flips.size()) nextF[to] = flips.at(from);
            if ((from + 1) * tileSize <= slopes.size())
                for (int i = 0; i < tileSize; ++i)
                    nextS[to * tileSize + i] = slopes.at(from * tileSize + i);
        }
    width = w; height = h;
    graphics = nextG; collisions = nextC; flips = nextF; slopes = nextS;
    for (int i = collisionPlacements.size() - 1; i >= 0; --i) {
        const auto &p = collisionPlacements.at(i);
        if (p.stamp < 0 || p.stamp >= collisionStamps.size() ||
            p.x + collisionStamps.at(p.stamp).width > w ||
            p.y + collisionStamps.at(p.stamp).height > h)
            collisionPlacements.removeAt(i);
    }
    QByteArray covered(w*h, char(0));
    for (const auto &p : collisionPlacements) {
        if (p.stamp < 0 || p.stamp >= collisionStamps.size()) continue;
        const auto &shape = collisionStamps.at(p.stamp);
        for (int yy = p.y; yy < p.y + shape.height; ++yy)
            for (int xx = p.x; xx < p.x + shape.width; ++xx)
                covered[yy*w+xx] = 1;
    }
    for (int i = 0; i < collisions.size(); ++i)
        if (quint8(collisions.at(i)) == 8 && !covered.at(i)) collisions[i] = 0;
}

QJsonObject SidboxTilemap::toJson() const
{
    QJsonObject result;
    result.insert(QStringLiteral("width"), width);
    result.insert(QStringLiteral("height"), height);
    result.insert(QStringLiteral("tileSize"), tileSize);
    result.insert(QStringLiteral("atlasPath"), atlasPath);
    result.insert(QStringLiteral("graphics16Z"), QString::fromLatin1(qCompress(graphics, 9).toBase64()));
    QJsonArray zoneNames;
    for (int i = 0; i < 8; ++i)
        zoneNames.append(i < customZoneNames.size() ? customZoneNames.at(i) : QString());
    result.insert(QStringLiteral("customZoneNames"), zoneNames);
    result.insert(QStringLiteral("collisionsZ"), QString::fromLatin1(qCompress(collisions, 9).toBase64()));
    result.insert(QStringLiteral("flipsZ"), QString::fromLatin1(qCompress(flips, 9).toBase64()));
    result.insert(QStringLiteral("slopesZ"), QString::fromLatin1(qCompress(slopes, 9).toBase64()));
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
    QJsonArray collisionStampList;
    for (const SidboxCollisionStamp &stamp : collisionStamps) {
        QJsonObject item;
        item.insert(QStringLiteral("name"), stamp.name);
        item.insert(QStringLiteral("width"), stamp.width);
        item.insert(QStringLiteral("height"), stamp.height);
        item.insert(QStringLiteral("tileSize"), stamp.tileSize);
        QJsonArray points;
        for (const QPoint &p : stamp.points) {
            QJsonArray pair; pair.append(p.x()); pair.append(p.y()); points.append(pair);
        }
        item.insert(QStringLiteral("points"), points);
        collisionStampList.append(item);
    }
    result.insert(QStringLiteral("collisionStamps"), collisionStampList);
    QJsonArray placed;
    for (const auto &p : collisionPlacements) {
        QJsonObject item;
        item.insert(QStringLiteral("stamp"), p.stamp);
        item.insert(QStringLiteral("x"), p.x);
        item.insert(QStringLiteral("y"), p.y);
        item.insert(QStringLiteral("mirrorX"), p.mirrorX);
        placed.append(item);
    }
    result.insert(QStringLiteral("collisionPlacements"), placed);
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
        for (char flags : f) if (quint8(flags) & ~quint8(7)) return false;
    }
    QByteArray slopesDecoded(w * h * tile, char(0));
    const QJsonValue slopesValue = object.value(QStringLiteral("slopesZ"));
    if (!slopesValue.isUndefined()) {
        if (!slopesValue.isString() || slopesValue.toString().size() > 4000000) return false;
        const QByteArray compressed = QByteArray::fromBase64(slopesValue.toString().toLatin1());
        if (expectedLength(compressed) != quint32(w * h * tile)) return false;
        slopesDecoded = qUncompress(compressed);
        if (slopesDecoded.size() != w * h * tile) return false;
    }
    if (c.contains(char(7)) && slopesValue.isUndefined()) return false;
    QStringList zoneNames;
    const QJsonValue namesValue = object.value(QStringLiteral("customZoneNames"));
    if (!namesValue.isUndefined() && !namesValue.isArray()) return false;
    if (namesValue.toArray().size() > 8) return false;
    for (const QJsonValue &name : namesValue.toArray()) {
        if (!name.isString() || name.toString().size() > 32) return false;
        zoneNames.append(name.toString());
    }
    for (int i = 0; i < w * h; ++i) {
        const int type = quint8(c.at(i));
        if (type > 24) return false;
        if (type == 7)
            for (int x = 0; x < tile; ++x)
                if (quint8(slopesDecoded.at(i * tile + x)) > tile) return false;
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
        for (char f : stamp.flips) if ((quint8(f) & ~quint8(7)) != 0) return false;
        decodedStamps.append(std::move(stamp));
    }
    QVector<SidboxCollisionStamp> decodedCollisionStamps;
    const QJsonValue collisionValue = object.value(QStringLiteral("collisionStamps"));
    if (!collisionValue.isUndefined() && !collisionValue.isArray()) return false;
    const QJsonArray collisionItems = collisionValue.toArray();
    if (collisionItems.size() > 128) return false;
    for (const QJsonValue &value : collisionItems) {
        if (!value.isObject()) return false;
        const QJsonObject item = value.toObject();
        SidboxCollisionStamp stamp;
        stamp.name = item.value(QStringLiteral("name")).toString();
        stamp.width = item.value(QStringLiteral("width")).toInt(0);
        stamp.height = item.value(QStringLiteral("height")).toInt(0);
        stamp.tileSize = item.value(QStringLiteral("tileSize")).toInt(0);
        if (stamp.name.isEmpty() || stamp.name.size() > 80 || stamp.width < 1 ||
            stamp.width > 16 || stamp.height < 1 || stamp.height > 16 ||
            (stamp.tileSize != 8 && stamp.tileSize != 16 && stamp.tileSize != 32)) return false;
        const QJsonValue pv = item.value(QStringLiteral("points"));
        if (pv.isArray()) {
            const QJsonArray arr = pv.toArray();
            if (arr.size() < 2 || arr.size() > 128) return false;
            for (const QJsonValue &v : arr) {
                if (!v.isArray() || v.toArray().size() != 2) return false;
                const QJsonArray pair = v.toArray();
                if (!pair.at(0).isDouble() || !pair.at(1).isDouble()) return false;
                stamp.points.append(QPoint(pair.at(0).toInt(-1), pair.at(1).toInt(-1)));
            }
        } else {
            // Migration of Stage 3.35 height-painted *definitions*. Old
            // already-painted cells remain legacy v3 data in slopesZ.
            const QString encodedHeights = item.value(QStringLiteral("heightsZ")).toString();
            if (encodedHeights.size() > 4000) return false;
            const QByteArray encoded = QByteArray::fromBase64(encodedHeights.toLatin1());
            if (expectedLength(encoded) != quint32(stamp.width * stamp.tileSize * 2)) return false;
            const QByteArray old = qUncompress(encoded);
            const int total = stamp.width * stamp.tileSize;
            if (old.size() != total * 2) return false;
            for (int x = 0; x < total; ++x) {
                const int y = quint8(old.at(x * 2)) | (quint8(old.at(x * 2 + 1)) << 8);
                if (y > stamp.height * stamp.tileSize) return false;
                if (x == 0 || x == total - 1 ||
                    (x > 0 && x < total - 1 && (quint8(old.at(x*2)) != quint8(old.at((x-1)*2)) ||
                    quint8(old.at(x*2+1)) != quint8(old.at((x-1)*2+1)))))
                    stamp.points.append(QPoint(x, y));
            }
            stamp.points.append(QPoint(total, stamp.points.last().y()));
            // Old hand-painted lines could contain hundreds of steps. Thin
            // to 128 editable points; original painted cells remain exact.
            while (stamp.points.size() > 128) {
                QVector<QPoint> thin;
                for (int i = 0; i < stamp.points.size(); i += 2)
                    thin.append(stamp.points.at(i));
                if (thin.last().x() != stamp.points.last().x())
                    thin.append(stamp.points.last());
                stamp.points = thin;
            }
        }
        if (!validSlopePoints(stamp)) return false;
        decodedCollisionStamps.append(std::move(stamp));
    }
    QVector<SidboxCollisionPlacement> decodedPlacements;
    const QJsonValue placesValue = object.value(QStringLiteral("collisionPlacements"));
    if (!placesValue.isUndefined() && !placesValue.isArray()) return false;
    if (placesValue.toArray().size() > 65535) return false;
    QSet<int> occupied;
    for (const QJsonValue &value : placesValue.toArray()) {
        if (!value.isObject()) return false;
        const auto v = value.toObject();
        SidboxCollisionPlacement p;
        p.stamp = v.value(QStringLiteral("stamp")).toInt(-1);
        p.x = v.value(QStringLiteral("x")).toInt(-1);
        p.y = v.value(QStringLiteral("y")).toInt(-1);
        p.mirrorX = v.value(QStringLiteral("mirrorX")).toBool(false);
        if (p.stamp < 0 || p.stamp >= decodedCollisionStamps.size() ||
            p.x < 0 || p.y < 0 ||
            p.x + decodedCollisionStamps.at(p.stamp).width > w ||
            p.y + decodedCollisionStamps.at(p.stamp).height > h ||
            decodedCollisionStamps.at(p.stamp).tileSize != tile) return false;
        const auto &shape = decodedCollisionStamps.at(p.stamp);
        for (int yy = p.y; yy < p.y + shape.height; ++yy)
            for (int xx = p.x; xx < p.x + shape.width; ++xx) {
                const int index = yy * w + xx;
                if (occupied.contains(index) || quint8(c.at(index)) != 8) return false;
                occupied.insert(index);
            }
        decodedPlacements.append(p);
    }
    for (int i = 0; i < c.size(); ++i)
        if (quint8(c.at(i)) == 8 && !occupied.contains(i)) return false;
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
    customZoneNames = zoneNames;
    flips = f;
    slopes = slopesDecoded;
    animations = decoded;
    stamps = std::move(decodedStamps);
    collisionStamps = std::move(decodedCollisionStamps);
    collisionPlacements = std::move(decodedPlacements);
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
    bool stampUseFrontBrush = false; // stamp override: use Draw in front of player checkbox
    int stampIndex = -1; // -1 means ordinary atlas-tile painting
    int collisionStampIndex = -1; // separate collision-only brush
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
            temporaryStatus(QStringLiteral("Copied %1×%2 · Esc: place · Shift+Esc: cancel")
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
        // Remove full overlapping slope instances FIRST. Copy data lives in a
        // separate snapshot, so overlapping the source is also safe.
        removePlacementsInRect(*map, QRect(bx, by, w, h));
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x) {
                const int src = y * w + x;
                const int dst = (by + y) * map->width + bx + x;
                const quint16 tile = erase ? 0 : mapGraphic(temporaryStamp.graphics, src);
                setMapGraphic(map->graphics, dst, tile);
                map->collisions[dst] = erase ? char(0) : temporaryStamp.collisions.at(src);
                const quint8 saved = quint8(temporaryStamp.flips.at(src));
                map->flips[dst] = erase ? char(0) : char((saved & ~4u) |
                    (stampUseFrontBrush ? (flipBrush & 4u) : (saved & 4u)));
                for (int k = 0; k < map->tileSize; ++k)
                    map->slopes[dst * map->tileSize + k] = erase ? char(0) :
                        temporarySlopes.at(src * map->tileSize + k);
            }
        if (!erase)
            for (auto place : temporaryPlacements) {
                if (place.stamp < 0 || place.stamp >= map->collisionStamps.size()) continue;
                place.x += bx; place.y += by;
                map->collisionPlacements.append(place);
            }
        if (strokeFinished) strokeFinished();
        viewport()->update();
        return true;
    }
    bool finishTemporary(bool cancel = false)
    {
        if (!temporaryActive) return false;
        if (!cancel && !applyTemporary(false)) return true;
        deactivateTemporary();
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
        if (!map || !hoverValid || panning || selectingRegion) return QRect();
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
        if (!map || !hoverValid || panning || selectingRegion) return;
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
                    removePlacementsInRect(*map, QRect(bx, by, stamp.width, stamp.height));
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
                        if (collisionPlacementAt(*map, x, y) >= 0) {
                            removePlacementsInRect(*map, QRect(x, y, 1, 1));
                            changed = true;
                            viewport()->update();
                        }
                        if (map->collisions.at(index) != c) {
                            map->collisions[index] = c;
                            changed = true;
                        }
                        for (int k = 0; k < map->tileSize; ++k) {
                            const int off = index * map->tileSize + k;
                            if (map->slopes[off] != 0) { map->slopes[off] = 0; changed = true; }
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
            if (collisionPlacementAt(*map, tx, ty) >= 0) {
                removePlacementsInRect(*map, QRect(tx, ty, 1, 1));
                changed = true;
                viewport()->update();
            }
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
                painter.setPen(QColor(255, 207, 84));
                painter.drawText(dest.adjusted(1, 0, 0, 0),
                                 Qt::AlignTop | Qt::AlignLeft, QStringLiteral("F"));
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
        paintBrushPreview(painter);
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
            updateHover(e->position().toPoint());
        }
    }
    void mouseReleaseEvent(QMouseEvent *e) override
    {
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
            // Escape pastes the current preview and ends temporary mode.
            if (temporaryAnchor == hoverCell) applyTemporary(false);
            e->accept(); return;
        }
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
    void keyPressEvent(QKeyEvent *event) override
    {
        if (event->key() == Qt::Key_Escape && temporaryActive) {
            finishTemporary(bool(event->modifiers() & Qt::ShiftModifier));
            event->accept();
            return;
        }
        QAbstractScrollArea::keyPressEvent(event);
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
                    painter.drawImage(cell, (flip & 3) ? tileImage.flipped(Qt::Orientations(static_cast<Qt::Orientation>(flip & 3))) : tileImage);
                } else if (tile) {
                    painter.fillRect(cell, QColor(84, 90, 105));
                    painter.setPen(Qt::white);
                    painter.drawText(cell, Qt::AlignCenter, QString::number(tile));
                }
                if (quint8(stamp.flips.at(i)) & 4u) {
                    painter.setPen(QColor(255, 207, 84));
                    painter.drawText(cell.adjusted(1, 0, 0, 0),
                        Qt::AlignLeft | Qt::AlignTop, QStringLiteral("F"));
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
    std::function<void()> strokeStarted;
    std::function<void()> modified;
    std::function<void()> pointSelected;
    explicit CollisionCanvas(QWidget *parent = nullptr) : QWidget(parent) {
        setCursor(Qt::CrossCursor);
        setMouseTracking(true);
        setMinimumSize(210, 150);
    }
    void refresh() {
        if (!map || selected < 0 || selected >= map->collisionStamps.size())
            setFixedSize(210, 150);
        else {
            const auto &s = map->collisionStamps.at(selected);
            setFixedSize(qMax(210, s.width * 32 + 1),
                         qMax(150, s.height * 32 + 1));
        }
        update();
    }
    QPoint pixelPoint(const QPoint &p, const SidboxCollisionStamp &s) const {
        return QPoint(qBound(0, qRound(double(p.x()) * s.tileSize / 32), s.width * s.tileSize),
                      qBound(0, qRound(double(p.y()) * s.tileSize / 32), s.height * s.tileSize));
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
        const int unit = 32, size = s.tileSize;
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
            const int distance = (delta.x()*delta.x()+delta.y()*delta.y()) * 32 * 32 /
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
        || a.collisionPlacements.size() != b.collisionPlacements.size())
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
            left.points != right.points) return false;
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
    constexpr int maxHistory = 64;
    if (m_undoStack.size() == maxHistory) m_undoStack.removeFirst();
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
    sizeX->setRange(30, 256); sizeY->setRange(20, 256);
    sizeX->setValue(m_map.width); sizeY->setValue(m_map.height);
    auto *tileSize = new TilemapComboBox(this);
    m_tileSizeCombo = tileSize;
    for (int s : {8, 16, 32}) tileSize->addItem(QString::number(s) + QStringLiteral(" px"), s);
    tileSize->setCurrentIndex(qMax(0, tileSize->findData(m_map.tileSize)));
    auto *zoom = new TilemapComboBox(this);
    for (int z : {1, 2, 3, 4}) zoom->addItem(QStringLiteral("%1×").arg(z), z);
    zoom->setCurrentIndex(qMax(0, zoom->findData(qBound(1,
        windowSettings.value(QStringLiteral("GameTilemapEditor/zoom"), 2).toInt(), 4))));
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
    brushG->setToolTip(tr("Click a tile in the atlas on the left to select it. "
        "Choose Don't change graphic to paint collisions only."));
    brushC->setToolTip(tr("Choose Don't change collision to paint graphics only. "
        "Otherwise both layers are painted with one stroke."));
    auto *paintRow = new QHBoxLayout;
    paintRow->addWidget(new QLabel(tr("Paint collision:"), this));
    paintRow->addWidget(brushC);
    auto *renameZone = new QPushButton(tr("Name Zone"), this);
    renameZone->setToolTip(tr("Give Custom 1–8 a friendly name in this design. The C callback still receives zone 1–8."));
    paintRow->addWidget(renameZone);
    auto *customSolid = new QCheckBox(tr("Custom is solid"), this);
    customSolid->setToolTip(tr("Blocking custom zones stop the player, but still report touch events. Pass-through zones do not block."));
    paintRow->addWidget(customSolid);
    connect(brushC, qOverload<int>(&QComboBox::currentIndexChanged), this,
        [brushC, renameZone, customSolid](int) {
            const int id = brushC->currentData().toInt();
            renameZone->setEnabled(id >= 9 && id <= 24);
            customSolid->setEnabled(id >= 9 && id <= 24);
            const QSignalBlocker guard(customSolid);
            customSolid->setChecked(id >= 17 && id <= 24);
        });
    renameZone->setEnabled(brushC->currentData().toInt() >= 9 && brushC->currentData().toInt() <= 24);
    customSolid->setEnabled(renameZone->isEnabled());
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
    paintRow->addSpacing(8);
    paintRow->addWidget(new QLabel(tr("Paint graphic:"), this));
    paintRow->addWidget(brushG, 1);
    layout->addLayout(paintRow);
    auto *flipRow = new QHBoxLayout;
    m_flipMode = new TilemapComboBox(this);
    m_flipMode->addItem(tr("Apply tile flags"), 1);
    m_flipMode->addItem(tr("Don't change tile flags"), -1);
    m_flipMode->setCurrentIndex(qMax(0, m_flipMode->findData(
        windowSettings.value(QStringLiteral("GameTilemapEditor/flipMode"), 1).toInt())));
    m_flipX = new QCheckBox(tr("Cell Flip X"), this);
    m_flipY = new QCheckBox(tr("Cell Flip Y"), this);
    m_drawFront = new QCheckBox(tr("Draw in front of player"), this);
    m_drawFront->setToolTip(tr("Draw this tile after the player. It still has its normal collision properties."));
    m_stampUseFront = new QCheckBox(tr("Stamp: use Draw Front setting"), this);
    m_stampUseFront->setToolTip(tr("When checked, the Draw in front of player checkbox sets front/back for all painted stamp cells. "
                                   "When unchecked, each stamp cell uses its own saved front/back flag. "
                                   "Individual cell X/Y flips and stamp mirroring are always preserved."));
    m_stampUseFront->setChecked(windowSettings.value(
        QStringLiteral("GameTilemapEditor/stampUseFront"), false).toBool());
    m_stampMirrorX = new QCheckBox(tr("Mirror stamp X"), this);
    m_stampMirrorY = new QCheckBox(tr("Mirror stamp Y"), this);
    m_flipMode->setToolTip(tr("Apply X/Y flip and Draw Front flags, or preserve all three while painting collisions."));
    m_flipX->setToolTip(tr("Set horizontal flip on individual cells painted into the map or stamp editor."));
    m_flipY->setToolTip(tr("Set vertical flip on individual cells painted into the map or stamp editor."));
    const int lastFlags = windowSettings.value(QStringLiteral("GameTilemapEditor/brushFlags"), 0).toInt();
    m_flipX->setChecked((lastFlags & 1) != 0);
    m_flipY->setChecked((lastFlags & 2) != 0);
    m_drawFront->setChecked((lastFlags & 4) != 0);
    m_stampMirrorX->setToolTip(tr("Mirror the entire stamp when painting: reverses cell order and toggles each cell's X flip flag."));
    m_stampMirrorY->setToolTip(tr("Mirror the entire stamp when painting: reverses cell order and toggles each cell's Y flip flag."));
    flipRow->addWidget(m_flipMode);
    flipRow->addWidget(m_flipX);
    flipRow->addWidget(m_flipY);
    flipRow->addWidget(m_drawFront);
    flipRow->addSpacing(10);
    flipRow->addWidget(m_stampMirrorX);
    flipRow->addWidget(m_stampMirrorY);
    flipRow->addStretch();
    layout->addLayout(flipRow);
    // Keep the already-busy tile flag row compact; the override is a
    // separate, small option below it and affects graphical STAMP placement.
    auto *stampFlagRow = new QHBoxLayout;
    stampFlagRow->addWidget(m_stampUseFront);
    stampFlagRow->addStretch();
    layout->addLayout(stampFlagRow);

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
        m_collisionList->setCurrentRow(shapeIndex);
        selectCollisionStamp(shapeIndex);
        if (m_stampStatus)
            m_stampStatus->setText(tr("Editing collision stamp '%1' — changes affect every copy")
                                    .arg(m_map.collisionStamps.at(shapeIndex).name));
    };
    // Stamp sidebar: upper bank of thumbnails + lower editable stamp grid.
    m_stampTabs = new QTabWidget(m_splitter);
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

    // Independent collision-only stamp workspace. The graphical stamp last
    // selected in the first tab is used as a FADED visual reference here.
    auto *collisionSidebar = new QSplitter(Qt::Vertical, m_stampTabs);
    collisionSidebar->setChildrenCollapsible(false);
    auto *collisionBankPane = new QWidget(collisionSidebar);
    auto *collisionBankLayout = new QVBoxLayout(collisionBankPane);
    collisionBankLayout->setContentsMargins(4, 4, 4, 4);
    collisionBankLayout->addWidget(new QLabel(tr("Collision Stamp Bank"), collisionBankPane));
    m_collisionList = new QListWidget(collisionBankPane);
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
    collisionEditLayout->setContentsMargins(4, 4, 4, 4);
    collisionEditLayout->addWidget(new QLabel(tr("Draw ground surface — solid below"), collisionEditPane));
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
    auto *collisionScroll = new QScrollArea(collisionEditPane);
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
    collisionSidebar->setStretchFactor(0, 1);
    collisionSidebar->setStretchFactor(1, 1);
    collisionSidebar->setSizes({300, 300});
    m_stampTabs->addTab(collisionSidebar, tr("Collision Stamps"));
    connect(m_stampTabs, &QTabWidget::currentChanged, this, [this](int tab) {
        m_canvas->collisionStampIndex = -1;
        m_canvas->stampIndex = -1;
        if (tab == 0) selectStamp(m_stampList->currentRow());
        else selectCollisionStamp(m_collisionList->currentRow());
        m_stampMirrorY->setEnabled(tab == 0);
        if (tab == 1) m_stampMirrorY->setChecked(false);
        m_canvas->viewport()->update();
    });
    connect(m_collisionList, &QListWidget::currentRowChanged, this,
        [this](int row) { selectCollisionStamp(row); });
    connect(m_collisionList, &QListWidget::itemClicked, this,
        [this](QListWidgetItem *item) { selectCollisionStamp(m_collisionList->row(item)); });
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
        "RIGHT-CLICK erases its footprint, ESC pastes and finishes, SHIFT+ESC cancels. "
        "MIDDLE-DRAG or ALT+LEFT-DRAG pans; WHEEL scrolls. CTRL+Z / CTRL+Y undo/redo. "
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
        recordChange(before);
    });
    connect(sizeY, qOverload<int>(&QSpinBox::valueChanged), this, [this](int v) {
        const SidboxTilemap before = m_map;
        m_map.resizeMap(m_map.width, v); m_canvas->adjust();
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
                                   (m_flipY->isChecked() ? 2 : 0) |
                                   (m_drawFront->isChecked() ? 4 : 0));
        m_canvas->flipBrush = flags;
        m_stampCanvas->flipBrush = flags;
        m_canvas->viewport()->update();
        m_stampCanvas->update();
    };
    connect(m_flipX, &QCheckBox::toggled, this, [updateFlipBrush](bool) { updateFlipBrush(); });
    connect(m_flipY, &QCheckBox::toggled, this, [updateFlipBrush](bool) { updateFlipBrush(); });
    connect(m_drawFront, &QCheckBox::toggled, this, [updateFlipBrush](bool) { updateFlipBrush(); });
    connect(m_stampUseFront, &QCheckBox::toggled, this, [this](bool enabled) {
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
    // Pan is project-specific, while zoom and brush choices are IDE preferences.
    m_viewSettingsKey = QString::fromLatin1(QCryptographicHash::hash(
        QDir(m_designDirectory).absolutePath().toUtf8(),
        QCryptographicHash::Sha256).toHex());
    QTimer::singleShot(0, this, [this]() {
        if (!m_canvas) return;
        m_canvas->adjust();
        QSettings settings(QStringLiteral("Sidbox"), QStringLiteral("SidboxIDE"));
        const QString prefix = QStringLiteral("GameTilemapEditor/pan/") + m_viewSettingsKey;
        m_canvas->horizontalScrollBar()->setValue(settings.value(prefix + QStringLiteral("/x"), 0).toInt());
        m_canvas->verticalScrollBar()->setValue(settings.value(prefix + QStringLiteral("/y"), 0).toInt());
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
    if (m_collisionCanvas->selected != selected) {
        // Changing stamps also changes the editor, not just the painting brush.
        m_collisionCanvas->selected = selected;
        m_collisionCanvas->active = -1;
    }
    m_collisionCanvas->refresh();
    m_collisionName->setEnabled(valid);
    m_collisionWidth->setEnabled(valid);
    m_collisionHeight->setEnabled(valid);
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
    if (!m_viewSettingsKey.isEmpty()) {
        const QString prefix = QStringLiteral("GameTilemapEditor/pan/") + m_viewSettingsKey;
        settings.setValue(prefix + QStringLiteral("/x"), m_canvas->horizontalScrollBar()->value());
        settings.setValue(prefix + QStringLiteral("/y"), m_canvas->verticalScrollBar()->value());
    }
}

void SidboxTilemapEditor::done(int result)
{
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
        m_canvas->finishTemporary(bool(event->modifiers() & Qt::ShiftModifier));
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
    const bool custom = map.collisions.contains(char(7)); // legacy v3 data
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
        "extern const uint8_t game_level1_slopes[];\n"
        "extern const uint16_t game_level1_shape_refs[];\n"
        "extern const game_tile_shape_t game_level1_shape_defs[];\n"
        "extern const game_tile_shape_point_t game_level1_shape_points[];\n"
        "extern const game_tile_shape_instance_t game_level1_shape_instances[];\n"
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
    if (custom) writeBytes(map.slopes, "game_level1_slopes");
    if (pointShapes) {
        source += "const uint16_t game_level1_shape_refs[] = {\n";
        for (int i = 0; i < map.width * map.height; ++i) {
            if (i % 16 == 0) source += "    ";
            source += QByteArray::number(quint8(shapeRefs.at(i*2)) | (quint8(shapeRefs.at(i*2+1)) << 8));
            if (i != map.width * map.height - 1) source += ",";
            if (i % 16 == 15 || i == map.width * map.height - 1) source += "\n";
            else source += " ";
        }
        source += "};\n\n";
        source += "const game_tile_shape_t game_level1_shape_defs[] = {\n";
        int offset = 0;
        for (int id : usedShapes) {
            const auto &shape = map.collisionStamps.at(id);
            source += "    {" + QByteArray::number(shape.width) + ", " +
                QByteArray::number(shape.height) + ", " + QByteArray::number(offset) +
                ", " + QByteArray::number(shape.points.size()) + ", 0, 0},\n";
            offset += shape.points.size();
        }
        source += "};\n\nconst game_tile_shape_point_t game_level1_shape_points[] = {\n";
        for (int id : usedShapes)
            for (const QPoint &pt : map.collisionStamps.at(id).points)
                source += "    {" + QByteArray::number(pt.x()) + ", " + QByteArray::number(pt.y()) + "},\n";
        source += "};\n\nconst game_tile_shape_instance_t game_level1_shape_instances[] = {\n";
        for (const auto &place : map.collisionPlacements)
            source += "    {" + QByteArray::number(place.x) + ", " + QByteArray::number(place.y) +
                ", " + QByteArray::number(shapeRemap.at(place.stamp)) + ", " +
                QByteArray::number(place.mirrorX ? 1 : 0) + "},\n";
        source += "};\n\n";
    }
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
        + ", " + (externalMap ? QByteArray("0 /* SD slopes loaded later */") :
                 (custom ? QByteArray("game_level1_slopes") : QByteArray("0")))
        + (pointShapes ? QByteArray(",\n    ") +
            (externalMap ? QByteArray("0, 0, 0, 0, 0, 0") :
            QByteArray("game_level1_shape_refs, game_level1_shape_instances, ") +
            "game_level1_shape_defs, game_level1_shape_points, " +
            QByteArray::number(map.collisionPlacements.size()) + ", " +
            QByteArray::number(map.collisionStamps.size())) : QByteArray())
        + "\n};\n\n";
    if (externalMap) {
        source += "/* SD map v2/v3/v4: file includes graphics, collisions, flips, optional slopes and animations. */\n"
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
                payload.append(char(0)); pushU16(0);
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
        if (!atomic(QDir(folder).filePath(QStringLiteral("level1.map")), bytes))
            return false;
    }
    return atomic(QDir(folder).filePath(QStringLiteral("level1.h")), header)
        && atomic(QDir(folder).filePath(QStringLiteral("level1.c")), source);
}

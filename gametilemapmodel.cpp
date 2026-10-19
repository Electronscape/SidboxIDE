// Stage 3.69: map data model, independent of editor widgets.
#include "gametilemap.h"
#include "gametilemapinternal.h"
#include <QJsonArray>
#include <QJsonValue>
#include <QSet>
#include <algorithm>
#include <utility>

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

void SidboxTilemap::resizeMap(int w, int h)
{
    w = qBound(30, w, SIDBOX_MAP_MAX_AXIS);
    h = qBound(20, h, SIDBOX_MAP_MAX_AXIS);
    // No silent shrinking of the other axis: the editor's spin boxes prevent
    // oversize combinations. Preserve the map if called from somewhere else.
    if (qint64(w) * h > SIDBOX_MAP_MAX_CELLS) return;
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
    for (int i = loops.size()-1; i >= 0; --i) {
        const auto &track=loops.at(i);
        if (track.centerX+track.radius >= w*tileSize ||
            track.centerY+track.radius >= h*tileSize) loops.removeAt(i);
    }
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
        item.insert(QStringLiteral("passiveSurface"), stamp.passiveSurface);
        item.insert(QStringLiteral("dampingPercent"), stamp.dampingPercent);
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
    QJsonArray loopList;
    for (const SidboxLoopTrack &loop : loops) {
        QJsonObject v;
        v.insert(QStringLiteral("centerX"), loop.centerX);
        v.insert(QStringLiteral("centerY"), loop.centerY);
        v.insert(QStringLiteral("radius"), loop.radius);
        v.insert(QStringLiteral("entrySpeed100"), loop.entrySpeed100);
        v.insert(QStringLiteral("downhillBoost100"), loop.downhillBoost100);
        v.insert(QStringLiteral("coastAfterExit"), loop.coastAfterExit);
        v.insert(QStringLiteral("coastFalloffPermille"), loop.coastFalloffPermille);
        loopList.append(v);
    }
    result.insert(QStringLiteral("loopTracks"), loopList);
    return result;
}

bool SidboxTilemap::fromJson(const QJsonObject &object)
{
    const int w = object.value(QStringLiteral("width")).toInt(100);
    const int h = object.value(QStringLiteral("height")).toInt(100);
    const int tile = object.value(QStringLiteral("tileSize")).toInt(16);
    if (w < 30 || w > SIDBOX_MAP_MAX_AXIS || h < 20 ||
        h > SIDBOX_MAP_MAX_AXIS || qint64(w) * h > SIDBOX_MAP_MAX_CELLS ||
        (tile != 8 && tile != 16 && tile != 32)) return false;
    const bool extended = object.contains(QStringLiteral("graphics16Z"));
    const QString encodedG = object.value(extended ? QStringLiteral("graphics16Z")
                                                  : QStringLiteral("graphicsZ")).toString();
    const QString encodedC = object.value(QStringLiteral("collisionsZ")).toString();
    // Base64-encoded zlib streams can be slightly larger than raw data.
    // Bound compressed input by the selected map dimensions, never by a
    // hard-coded 256x256-era limit.
    const auto encodedLimit = [](qint64 rawBytes) -> qint64 {
        return ((rawBytes + 4096) * 4 / 3) + 32;
    };
    const qint64 cells = qint64(w) * h;
    if (encodedG.size() > encodedLimit(cells * (extended ? 2 : 1)) ||
        encodedC.size() > encodedLimit(cells)) return false;
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
        if (encodedF.size() > encodedLimit(cells)) return false;
        const QByteArray compressedF = QByteArray::fromBase64(encodedF.toLatin1());
        if (expectedLength(compressedF) != quint32(w * h)) return false;
        f = qUncompress(compressedF);
        if (f.size() != w * h) return false;
        for (char flags : f) if (quint8(flags) & ~quint8(7)) return false;
    }
    QByteArray slopesDecoded(w * h * tile, char(0));
    const QJsonValue slopesValue = object.value(QStringLiteral("slopesZ"));
    if (!slopesValue.isUndefined()) {
        if (!slopesValue.isString() ||
            slopesValue.toString().size() > encodedLimit(cells * tile)) return false;
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
        const QJsonValue passive = item.value(QStringLiteral("passiveSurface"));
        const QJsonValue damping = item.value(QStringLiteral("dampingPercent"));
        if ((!passive.isUndefined() && !passive.isBool()) ||
            (!damping.isUndefined() && (!damping.isDouble() ||
             damping.toDouble() != damping.toInt(-1)))) return false;
        stamp.passiveSurface = passive.toBool(false);
        stamp.dampingPercent = damping.isUndefined() ? 2 : damping.toInt(-1);
        if (stamp.dampingPercent < 0 || stamp.dampingPercent > 100) return false;
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
    QVector<SidboxLoopTrack> decodedLoops;
    const QJsonValue loopValue = object.value(QStringLiteral("loopTracks"));
    if (!loopValue.isUndefined() && !loopValue.isArray()) return false;
    if (loopValue.toArray().size() > 32) return false;
    for (const QJsonValue &value : loopValue.toArray()) {
        if (!value.isObject()) return false;
        const QJsonObject v = value.toObject();
        SidboxLoopTrack loop;
        loop.centerX = v.value(QStringLiteral("centerX")).toInt(-1);
        loop.centerY = v.value(QStringLiteral("centerY")).toInt(-1);
        loop.radius = v.value(QStringLiteral("radius")).toInt(-1);
        loop.entrySpeed100 = v.value(QStringLiteral("entrySpeed100")).toInt(-1);
        // Maps saved before Stage 3.80 keep their original loop behaviour.
        loop.downhillBoost100 = v.value(QStringLiteral("downhillBoost100")).toInt(0);
        // Missing on older project maps: retain their existing friction behaviour.
        loop.coastAfterExit = v.value(QStringLiteral("coastAfterExit")).toBool(false);
        // Old maps default to no decay; each new loop remembers its own rate.
        loop.coastFalloffPermille = v.value(QStringLiteral("coastFalloffPermille")).toInt(0);
        if (loop.coastFalloffPermille < 0 || loop.coastFalloffPermille > 200 ||
            loop.downhillBoost100 < 0 || loop.downhillBoost100 > 200 ||
            loop.radius < 16 || loop.radius > 512 || loop.entrySpeed100 < 100 ||
            loop.entrySpeed100 > 3200 || loop.centerX < loop.radius ||
            loop.centerY < loop.radius || loop.centerX + loop.radius >= w*tile ||
            loop.centerY + loop.radius >= h*tile) return false;
        decodedLoops.append(loop);
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
    customZoneNames = zoneNames;
    flips = f;
    slopes = slopesDecoded;
    animations = decoded;
    stamps = std::move(decodedStamps);
    collisionStamps = std::move(decodedCollisionStamps);
    collisionPlacements = std::move(decodedPlacements);
    loops = std::move(decodedLoops);
    return true;
}

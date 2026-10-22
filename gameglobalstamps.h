#ifndef CODERGIRL_GAME_GLOBAL_STAMPS_H
#define CODERGIRL_GAME_GLOBAL_STAMPS_H

// Project-owned collision and loop definitions. A world owns *placements*;
// saved .sbgm worlds never own duplicate stamp definitions. Old worlds with
// inline definitions are migrated in memory on open, without rewriting files.
#include "gametilemap.h"
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QVector>

namespace GameGlobalStamps {

inline QJsonObject loopDefinition(const SidboxLoopTrack &loop)
{
    QJsonObject v;
    v.insert(QStringLiteral("radius"), loop.radius);
    v.insert(QStringLiteral("entrySpeed100"), loop.entrySpeed100);
    v.insert(QStringLiteral("downhillBoost100"), loop.downhillBoost100);
    v.insert(QStringLiteral("coastAfterExit"), loop.coastAfterExit);
    v.insert(QStringLiteral("coastFalloffPermille"), loop.coastFalloffPermille);
    return v;
}

inline SidboxLoopTrack loopFromDefinition(const QJsonObject &v)
{
    SidboxLoopTrack loop;
    loop.radius = v.value(QStringLiteral("radius")).toInt(64);
    loop.entrySpeed100 = v.value(QStringLiteral("entrySpeed100")).toInt(400);
    loop.downhillBoost100 = v.value(QStringLiteral("downhillBoost100")).toInt(0);
    loop.coastAfterExit = v.value(QStringLiteral("coastAfterExit")).toBool(false);
    loop.coastFalloffPermille = v.value(QStringLiteral("coastFalloffPermille")).toInt(0);
    return loop;
}

inline bool validLoopDefinition(const QJsonObject &v)
{
    const SidboxLoopTrack loop = loopFromDefinition(v);
    return loop.radius >= 16 && loop.radius <= 512 &&
        loop.entrySpeed100 >= 100 && loop.entrySpeed100 <= 3200 &&
        loop.downhillBoost100 >= 0 && loop.downhillBoost100 <= 200 &&
        loop.coastFalloffPermille >= 0 && loop.coastFalloffPermille <= 200;
}

struct Bank {
    QString projectPath;
    QJsonArray collisions;
    QJsonArray loopStamps;
    QJsonObject tileStampBanks; // atlas relative PPB path -> tile stamp array

    static QString atlasKey(const QString &atlasPath)
    {
        if (atlasPath.trimmed().isEmpty()) return QString();
        return QDir::cleanPath(QDir::fromNativeSeparators(atlasPath));
    }

    bool open(const QString &designPath, QString *error)
    {
        const QDir dir(QFileInfo(designPath).absolutePath());
        const QStringList names = dir.entryList({QStringLiteral("*.proj")}, QDir::Files, QDir::Name);
        if (names.size() != 1) {
            if (error) *error = QStringLiteral("Expected exactly one .proj in %1; found %2. ")
                 .arg(dir.absolutePath()).arg(names.size());
            return false;
        }
        projectPath = dir.filePath(names.first());
        QFile f(projectPath);
        if (!f.open(QIODevice::ReadOnly)) {
            if (error) *error = QStringLiteral("Cannot open %1").arg(projectPath);
            return false;
        }
        const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
        if (!doc.isObject()) {
            if (error) *error = QStringLiteral("Invalid .proj JSON: %1").arg(projectPath);
            return false;
        }
        const QJsonObject root = doc.object();
        if ((!root.value(QStringLiteral("gameCollisionStamps")).isUndefined() &&
             !root.value(QStringLiteral("gameCollisionStamps")).isArray()) ||
            (!root.value(QStringLiteral("gameLoopStamps")).isUndefined() &&
             !root.value(QStringLiteral("gameLoopStamps")).isArray()) ||
            (!root.value(QStringLiteral("gameTileStampBanks")).isUndefined() &&
             !root.value(QStringLiteral("gameTileStampBanks")).isObject())) {
            if (error) *error = QStringLiteral("Invalid global stamp tables in .proj");
            return false;
        }
        collisions = root.value(QStringLiteral("gameCollisionStamps")).toArray();
        loopStamps = root.value(QStringLiteral("gameLoopStamps")).toArray();
        tileStampBanks = root.value(QStringLiteral("gameTileStampBanks")).toObject();
        if (tileStampBanks.size() > 256) {
            if (error) *error = QStringLiteral("Too many tile atlas stamp banks (max 256).");
            return false;
        }
        for (auto it = tileStampBanks.constBegin(); it != tileStampBanks.constEnd(); ++it) {
            QVector<SidboxTileStamp> validated;
            if (atlasKey(it.key()) != it.key() || !it.value().isArray() ||
                !SidboxTilemap::stampsFromJson(it.value().toArray(), &validated)) {
                if (error) *error = QStringLiteral("Invalid tile stamp bank for atlas: %1").arg(it.key());
                return false;
            }
        }
        if (collisions.size() > 128 || loopStamps.size() > 128) {
            if (error) *error = QStringLiteral("Project stamp capacity exceeded (128 per bank).");
            return false;
        }
        for (const auto &def : loopStamps)
            if (!def.isObject() || !validLoopDefinition(def.toObject())) {
                if (error) *error = QStringLiteral("Invalid project loop stamp definition.");
                return false;
            }
        return true;
    }

    // The world can contain either legacy local definitions or new global
    // references. Resolve both to the existing in-memory SidboxTilemap format.
    bool expand(QJsonObject *world, QVector<int> *loopIndexes, QString *error)
    {
        if (!world) return false;
        const QJsonValue inlineShapes = world->value(QStringLiteral("collisionStamps"));
        if (!inlineShapes.isUndefined() && !inlineShapes.isArray()) return false;
        const QJsonArray local = inlineShapes.toArray();
        const bool legacy = !inlineShapes.isUndefined();
        if (legacy) {
            QVector<int> mapIndexes;
            for (const QJsonValue &value : local) {
                if (!value.isObject()) return false;
                int index = -1;
                for (int i = 0; i < collisions.size(); ++i)
                    if (collisions.at(i) == value) { index = i; break; }
                if (index < 0) {
                    if (collisions.size() >= 128) {
                        if (error) *error = QStringLiteral("Global collision stamp bank is full.");
                        return false;
                    }
                    index = collisions.size(); collisions.append(value);
                }
                mapIndexes.append(index);
            }
            QJsonArray places = world->value(QStringLiteral("collisionPlacements")).toArray();
            for (int i = 0; i < places.size(); ++i) {
                if (!places.at(i).isObject()) return false;
                QJsonObject p = places.at(i).toObject();
                const int old = p.value(QStringLiteral("stamp")).toInt(-1);
                if (old < 0 || old >= mapIndexes.size()) return false;
                p.insert(QStringLiteral("stamp"), mapIndexes.at(old));
                places.replace(i, p);
            }
            world->insert(QStringLiteral("collisionPlacements"), places);
        }
        world->insert(QStringLiteral("collisionStamps"), collisions);

        QJsonArray expanded;
        if (loopIndexes) loopIndexes->clear();
        const QJsonArray placed = world->value(QStringLiteral("loopTracks")).toArray();
        for (const QJsonValue &entry : placed) {
            if (!entry.isObject()) return false;
            const QJsonObject place = entry.toObject();
            int stamp = place.value(QStringLiteral("stamp")).toInt(-1);
            if (!place.contains(QStringLiteral("stamp"))) {
                const QJsonObject def = loopDefinition(loopFromDefinition(place));
                stamp = -1;
                for (int i = 0; i < loopStamps.size(); ++i)
                    if (loopStamps.at(i) == def) { stamp = i; break; }
                if (stamp < 0) {
                    if (loopStamps.size() >= 128) {
                        if (error) *error = QStringLiteral("Global loop stamp bank is full.");
                        return false;
                    }
                    stamp = loopStamps.size(); loopStamps.append(def);
                }
            }
            if (stamp < 0 || stamp >= loopStamps.size()) {
                if (error) *error = QStringLiteral("Loop placement references missing project stamp.");
                return false;
            }
            QJsonObject loop = loopStamps.at(stamp).toObject();
            loop.insert(QStringLiteral("centerX"), place.value(QStringLiteral("centerX")));
            loop.insert(QStringLiteral("centerY"), place.value(QStringLiteral("centerY")));
            expanded.append(loop);
            if (loopIndexes) loopIndexes->append(stamp);
        }
        world->insert(QStringLiteral("loopTracks"), expanded);
        return true;
    }

    void takeDefinitions(const SidboxTilemap &map)
    {
        collisions = map.toJson().value(QStringLiteral("collisionStamps")).toArray();
        loopStamps = QJsonArray();
        for (const auto &l : map.loopStamps) loopStamps.append(loopDefinition(l));
    }

    void installLoopStamps(SidboxTilemap *map) const
    {
        if (!map) return;
        map->loopStamps.clear();
        for (const QJsonValue &v : loopStamps)
            map->loopStamps.append(loopFromDefinition(v.toObject()));
    }

    static QJsonObject worldReferences(const SidboxTilemap &map)
    {
        QJsonObject world = map.toJson();
        world.remove(QStringLiteral("collisionStamps"));
        world.remove(QStringLiteral("stamps")); // design-time tiles live in the .proj atlas bank
        QJsonArray loopPlaces;
        for (const SidboxLoopTrack &loop : map.loops) {
            QJsonObject p;
            p.insert(QStringLiteral("stamp"), loop.stamp);
            p.insert(QStringLiteral("centerX"), loop.centerX);
            p.insert(QStringLiteral("centerY"), loop.centerY);
            loopPlaces.append(p);
        }
        world.insert(QStringLiteral("loopTracks"), loopPlaces);
        return world;
    }

    // A deleted global definition changes all subsequent numeric indexes.
    // Rewrite the OTHER .sbgm world references before saving the new project
    // bank; a deleted slope's reserved collision cells are cleared as well.
    // Worlds still using old inline definitions are migrated if every old
    // shape can be matched to the previously loaded project bank.
    bool remapOtherWorlds(const QString &currentWorld, const QJsonArray &oldBank,
                          const QVector<int> &oldToNew, QString *error) const
    {
        bool changed = false;
        for (int i = 0; i < oldToNew.size(); ++i)
            if (oldToNew.at(i) != i) changed = true;
        if (!changed) return true;
        const QDir dir(QFileInfo(currentWorld).absolutePath());
        const QStringList worlds = dir.entryList({QStringLiteral("*.sbgm")}, QDir::Files, QDir::Name);
        struct Rewrite { QString path; QByteArray bytes; };
        QVector<Rewrite> pending;
        for (const QString &worldName : worlds) {
            const QString path = dir.filePath(worldName);
            if (QFileInfo(path).absoluteFilePath() == QFileInfo(currentWorld).absoluteFilePath())
                continue;
            QFile input(path);
            if (!input.open(QIODevice::ReadOnly)) {
                if (error) *error = QStringLiteral("Could not read world: %1").arg(path);
                return false;
            }
            const QJsonDocument document = QJsonDocument::fromJson(input.readAll());
            if (!document.isObject()) {
                if (error) *error = QStringLiteral("Invalid world JSON: %1").arg(path);
                return false;
            }
            QJsonObject root = document.object();
            if (!root.value(QStringLiteral("tilemap")).isObject()) continue;
            QJsonObject map = root.value(QStringLiteral("tilemap")).toObject();
            const int width = map.value(QStringLiteral("width")).toInt();
            const int height = map.value(QStringLiteral("height")).toInt();
            if (width < 1 || height < 1 || qint64(width) * height > SIDBOX_MAP_MAX_CELLS) {
                if (error) *error = QStringLiteral("Invalid tilemap size: %1").arg(path);
                return false;
            }
            const QJsonValue localValue = map.value(QStringLiteral("collisionStamps"));
            const QJsonArray local = localValue.toArray();
            QVector<int> localToOld;
            if (localValue.isArray()) {
                for (const QJsonValue &value : local) {
                    int old = -1;
                    for (int i = 0; i < oldBank.size(); ++i)
                        if (oldBank.at(i) == value) { old = i; break; }
                    if (old < 0) {
                        if (error) *error = QStringLiteral(
                            "World %1 still has a unique legacy slope. Open and Save that "
                            "world to migrate it before removing global slopes.").arg(worldName);
                        return false;
                    }
                    localToOld.append(old);
                }
            }
            const QByteArray compressed = QByteArray::fromBase64(
                map.value(QStringLiteral("collisionsZ")).toString().toLatin1());
            QByteArray cells = qUncompress(compressed);
            if (cells.size() != width * height) {
                if (error) *error = QStringLiteral("Invalid collision grid: %1").arg(path);
                return false;
            }
            QJsonArray nextPlaces;
            const QJsonArray places = map.value(QStringLiteral("collisionPlacements")).toArray();
            for (const QJsonValue &entry : places) {
                if (!entry.isObject()) {
                    if (error) *error = QStringLiteral("Invalid slope placement: %1").arg(path);
                    return false;
                }
                QJsonObject placement = entry.toObject();
                const int stored = placement.value(QStringLiteral("stamp")).toInt(-1);
                const int old = localValue.isArray()
                    ? (stored >= 0 && stored < localToOld.size() ? localToOld.at(stored) : -1)
                    : stored;
                if (old < 0 || old >= oldBank.size() || old >= oldToNew.size()) {
                    if (error) *error = QStringLiteral("Unrecognised global slope reference in %1").arg(path);
                    return false;
                }
                const int updated = oldToNew.at(old);
                if (updated >= 0) {
                    placement.insert(QStringLiteral("stamp"), updated);
                    nextPlaces.append(placement);
                } else {
                    const QJsonObject original = oldBank.at(old).toObject();
                    const int x = placement.value(QStringLiteral("x")).toInt(-1);
                    const int y = placement.value(QStringLiteral("y")).toInt(-1);
                    const int sw = original.value(QStringLiteral("width")).toInt(-1);
                    const int sh = original.value(QStringLiteral("height")).toInt(-1);
                    if (x < 0 || y < 0 || sw < 1 || sh < 1 ||
                        x + sw > width || y + sh > height) {
                        if (error) *error = QStringLiteral("Invalid removed slope extent in %1").arg(path);
                        return false;
                    }
                    for (int yy = y; yy < y + sh; ++yy)
                        for (int xx = x; xx < x + sw; ++xx)
                            cells[yy * width + xx] = char(0);
                }
            }
            map.remove(QStringLiteral("collisionStamps"));
            map.insert(QStringLiteral("collisionPlacements"), nextPlaces);
            map.insert(QStringLiteral("collisionsZ"),
                       QString::fromLatin1(qCompress(cells, 9).toBase64()));
            root.insert(QStringLiteral("tilemap"), map);
            pending.append({path, QJsonDocument(root).toJson(QJsonDocument::Indented)});
        }
        // Preflight *every* world before touching any. QSaveFile commits each
        // world atomically. Keep a normal backup before any project migration.
        for (const Rewrite &rewrite : pending) {
            QSaveFile output(rewrite.path);
            if (!output.open(QIODevice::WriteOnly) ||
                output.write(rewrite.bytes) != rewrite.bytes.size() || !output.commit()) {
                if (error) *error = QStringLiteral("Could not update world: %1").arg(rewrite.path);
                return false;
            }
        }
        return true;
    }

    bool save(QString *error) const
    {
        if (projectPath.isEmpty()) return false;
        QFile existing(projectPath);
        if (!existing.open(QIODevice::ReadOnly)) return false;
        const QJsonDocument doc = QJsonDocument::fromJson(existing.readAll());
        if (!doc.isObject()) return false;
        QJsonObject root = doc.object();
        root.insert(QStringLiteral("gameCollisionStamps"), collisions);
        root.insert(QStringLiteral("gameLoopStamps"), loopStamps);
        root.insert(QStringLiteral("gameTileStampBanks"), tileStampBanks);
        QSaveFile out(projectPath);
        const QByteArray bytes = QJsonDocument(root).toJson(QJsonDocument::Indented);
        if (!out.open(QIODevice::WriteOnly) || out.write(bytes) != bytes.size() || !out.commit()) {
            if (error) *error = QStringLiteral("Could not save global stamps to %1").arg(projectPath);
            return false;
        }
        return true;
    }
};
}
#endif

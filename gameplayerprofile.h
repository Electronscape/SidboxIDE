#ifndef GAMERGIRL_GAME_PLAYER_PROFILE_H
#define GAMERGIRL_GAME_PLAYER_PROFILE_H
// Project-owned .sbpi: ONE player per game; never a world-owned object.
// Templates own all generated C. Qt only validates and supplies values.
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QImage>
#include <QRect>
#include <QVector>
#include <QList>
#include <QPair>
#include <QtGlobal>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QSet>
#include <QString>
#include <QStringList>
#include "ppbcodec.h"

namespace GamePlayerProfile {
inline QString profilePath(const QDir &project) {
    return project.filePath(QStringLiteral("players/player.sbpi"));
}
// Stable profile IDs allow world code to refer to a saved physics profile.
// The behaviour mode remains the existing tilemap engine's movement mode.
inline QJsonArray defaultPhysicsProfiles() {
    QJsonArray result;
    struct Initial { const char *name; int walk, jump, gravity, fall, drag; };
    const Initial values[] = {
        {"Normal", 3, 7, 35, 9, 12},
        {"Ice", 4, 7, 35, 9, 2},
        {"Water", 2, 5, 12, 3, 18},
        {"Slow", 1, 7, 35, 9, 18},
        {"Space", 3, 7, 3, 3, 0},
        {"Floating", 3, 7, 7, 2, 4},
        {"Jetpack", 3, 7, 20, 6, 6}
    };
    for (int id = 0; id < 7; ++id) {
        QJsonObject obj;
        obj.insert(QStringLiteral("id"), id);
        obj.insert(QStringLiteral("name"), QString::fromLatin1(values[id].name));
        obj.insert(QStringLiteral("mode"), id);
        obj.insert(QStringLiteral("walkSpeed"), values[id].walk);
        obj.insert(QStringLiteral("jumpSpeed"), values[id].jump);
        obj.insert(QStringLiteral("gravity"), values[id].gravity);
        obj.insert(QStringLiteral("maxFallSpeed"), values[id].fall);
        obj.insert(QStringLiteral("forceDrag"), values[id].drag);
        // Optional melee attack; disabled on every existing/new profile.
        obj.insert(QStringLiteral("combatEnabled"), false);
        obj.insert(QStringLiteral("attackDamage"), 1);
        obj.insert(QStringLiteral("attackReach"), 24);
        obj.insert(QStringLiteral("attackCooldown"), 15);
        result.append(obj);
    }
    return result;
}
inline int legacyPhysicsId(const QString &name) {
    const QStringList modes = {QStringLiteral("normal"), QStringLiteral("ice"),
        QStringLiteral("water"), QStringLiteral("slow"), QStringLiteral("space"),
        QStringLiteral("floating"), QStringLiteral("jetpack")};
    const int index = modes.indexOf(name.toLower());
    return index < 0 ? 0 : index;
}
inline QJsonArray physicsProfiles(const QJsonObject &profile) {
    return profile.contains(QStringLiteral("physicsProfiles"))
        ? profile.value(QStringLiteral("physicsProfiles")).toArray()
        : defaultPhysicsProfiles();
}
inline int startingPhysicsId(const QJsonObject &profile) {
    return profile.contains(QStringLiteral("physicsPresetId"))
        ? profile.value(QStringLiteral("physicsPresetId")).toInt(0)
        : legacyPhysicsId(profile.value(QStringLiteral("physicsPreset")).toString(QStringLiteral("normal")));
}
// World name -> stable profile ID. An omitted world inherits the default.
inline QJsonObject worldPhysicsOverrides(const QJsonObject &profile) {
    return profile.value(QStringLiteral("worldPhysics")).toObject();
}
inline int physicsForWorld(const QJsonObject &profile, const QString &worldName) {
    const QJsonValue assigned = worldPhysicsOverrides(profile).value(worldName);
    return assigned.isDouble() ? assigned.toInt(startingPhysicsId(profile))
                               : startingPhysicsId(profile);
}
inline QJsonObject defaults() {
    QJsonObject obj;
    obj.insert(QStringLiteral("format"), QStringLiteral("SIDBOX-PLAYER-INFO"));
    obj.insert(QStringLiteral("version"), 1);
    obj.insert(QStringLiteral("name"), QStringLiteral("player"));
    obj.insert(QStringLiteral("atlasPath"), QString());
    obj.insert(QStringLiteral("animationFile"), QString());
    obj.insert(QStringLiteral("cellWidth"), 32);
    obj.insert(QStringLiteral("cellHeight"), 32);
    obj.insert(QStringLiteral("health"), 100);
    obj.insert(QStringLiteral("lives"), 3);
    obj.insert(QStringLiteral("score"), 0);
    obj.insert(QStringLiteral("inventory"), QJsonArray());
    obj.insert(QStringLiteral("customStats"), QJsonArray());
    obj.insert(QStringLiteral("customHitbox"), false);
    obj.insert(QStringLiteral("hitboxX"), 0);
    obj.insert(QStringLiteral("hitboxY"), 0);
    obj.insert(QStringLiteral("hitboxW"), 32);
    obj.insert(QStringLiteral("hitboxH"), 32);
    obj.insert(QStringLiteral("physicsPreset"), QStringLiteral("normal"));
    obj.insert(QStringLiteral("physicsPresetId"), 0);
    obj.insert(QStringLiteral("physicsProfiles"), defaultPhysicsProfiles());
    obj.insert(QStringLiteral("worldPhysics"), QJsonObject());
    return obj;
}
inline bool read(const QDir &project, QJsonObject *profile, QString *error=nullptr) {
    QFile file(profilePath(project));
    if (!file.open(QIODevice::ReadOnly)) {
        if (error) *error = QStringLiteral("Cannot read player.sbpi: %1").arg(file.fileName());
        return false;
    }
    QJsonParseError parse;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &parse);
    if (!doc.isObject() || parse.error != QJsonParseError::NoError
        || doc.object().value(QStringLiteral("format")).toString() != QStringLiteral("SIDBOX-PLAYER-INFO")
        || doc.object().value(QStringLiteral("version")).toInt() != 1) {
        if (error) *error = QStringLiteral("Invalid .sbpi player format (version 1 required).");
        return false;
    }
    if (profile) *profile = doc.object();
    return true;
}
inline bool write(const QDir &project, const QJsonObject &data, QString *error=nullptr) {
    const QString filePath = profilePath(project);
    if (!QDir().mkpath(QFileInfo(filePath).absolutePath())) {
        if (error) *error = QStringLiteral("Cannot create players/ directory.");
        return false;
    }
    QSaveFile output(filePath);
    const QByteArray bytes = QJsonDocument(data).toJson(QJsonDocument::Indented);
    if (!output.open(QIODevice::WriteOnly)
        || output.write(bytes) != bytes.size() || !output.commit()) {
        if (error) *error = QStringLiteral("Could not save %1").arg(filePath);
        output.cancelWriting();
        return false;
    }
    return true;
}
// Design-time preview of the SAME project-owned player in every world.
// The .sbanim stores frame indices; there are no duplicate world sprites.
// Returns the first Idle frame for the requested direction, or atlas cell 0.
// A left-facing clip is used directly; otherwise mirror the Right clip only
// when the animation file enables mirrorLeft. The original PPB is untouched.
inline QImage idlePreview(const QDir &project, int facing, QRect *hitbox = nullptr) {
    if (hitbox) *hitbox = QRect();
    QJsonObject profile;
    if (!read(project, &profile)) return {};
    const QString relAtlas = profile.value(QStringLiteral("atlasPath")).toString().trimmed();
    const QFileInfo atlas(project.filePath(relAtlas));
    if (relAtlas.isEmpty() || !atlas.isFile()
        || atlas.suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive)
        || !atlas.absoluteFilePath().startsWith(project.absolutePath() + QLatin1Char('/')))
        return {};
    SidboxPpb::Picture picture;
    if (!SidboxPpb::read(atlas.absoluteFilePath(), &picture)) return {};
    QImage pixels = picture.indexed;
    const int cw = profile.value(QStringLiteral("cellWidth")).toInt(32);
    const int ch = profile.value(QStringLiteral("cellHeight")).toInt(32);
    if (pixels.isNull() || cw <= 0 || ch <= 0 || pixels.width() % cw
        || pixels.height() % ch || (pixels.width() / cw) * (pixels.height() / ch) > 256)
        return {};
    int frame = 0;
    const bool left = facing == 0;
    bool flip = left;
    const QString relAnim = profile.value(QStringLiteral("animationFile")).toString().trimmed();
    if (!relAnim.isEmpty()) {
        const QFileInfo animPath(project.filePath(relAnim));
        if (animPath.isFile() && animPath.absoluteFilePath().startsWith(project.absolutePath() + QLatin1Char('/'))) {
            QFile file(animPath.absoluteFilePath());
            if (file.open(QIODevice::ReadOnly)) {
                const QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
                const QJsonObject animation = doc.object();
                if (animation.value(QStringLiteral("format")).toString()
                        == QStringLiteral("SIDBOX-PLAYER-ANIM")
                    && animation.value(QStringLiteral("cellWidth")).toInt() == cw
                    && animation.value(QStringLiteral("cellHeight")).toInt() == ch) {
                    QJsonArray chosen;
                    QString chosenDirection;
                    // Prefer the Idle clip for this facing, then the opposite
                    // direction. Do not use an unrelated animation state.
                    const QString requested = left ? QStringLiteral("Left") : QStringLiteral("Right");
                    const QString fallback = left ? QStringLiteral("Right") : QStringLiteral("Left");
                    for (const QString &direction : {requested, fallback}) {
                        for (const QJsonValue &v : animation.value(QStringLiteral("clips")).toArray()) {
                            const QJsonObject clip = v.toObject();
                            if (clip.value(QStringLiteral("state")).toString().compare(
                                    QStringLiteral("Idle"), Qt::CaseInsensitive) == 0
                                && clip.value(QStringLiteral("direction")).toString() == direction
                                && !clip.value(QStringLiteral("frames")).toArray().isEmpty()) {
                                chosen = clip.value(QStringLiteral("frames")).toArray();
                                chosenDirection = direction;
                                break;
                            }
                        }
                        if (!chosen.isEmpty()) break;
                    }
                    if (!chosen.isEmpty()) {
                        const int candidate = chosen.first().toInt(-1);
                        if (candidate >= 0 && candidate < (pixels.width() / cw) * (pixels.height() / ch)) {
                            frame = candidate;
                            flip = chosenDirection != requested
                                && animation.value(QStringLiteral("mirrorLeft")).toBool(true);
                        }
                    }
                    if (hitbox && !profile.value(QStringLiteral("customHitbox")).toBool()) {
                        const QRect box(animation.value(QStringLiteral("hitboxX")).toInt(0),
                            animation.value(QStringLiteral("hitboxY")).toInt(0),
                            animation.value(QStringLiteral("hitboxW")).toInt(cw),
                            animation.value(QStringLiteral("hitboxH")).toInt(ch));
                        if (box.x() >= 0 && box.y() >= 0 && box.width() > 0 && box.height() > 0
                            && box.x() + box.width() <= cw && box.y() + box.height() <= ch)
                            *hitbox = box;
                    }
                }
            }
        }
    }
    if (hitbox && profile.value(QStringLiteral("customHitbox")).toBool()) {
        const QRect box(profile.value(QStringLiteral("hitboxX")).toInt(0),
            profile.value(QStringLiteral("hitboxY")).toInt(0),
            profile.value(QStringLiteral("hitboxW")).toInt(cw),
            profile.value(QStringLiteral("hitboxH")).toInt(ch));
        if (box.x() >= 0 && box.y() >= 0 && box.width() > 0 && box.height() > 0
            && box.x() + box.width() <= cw && box.y() + box.height() <= ch)
            *hitbox = box;
    }
    QImage cell = pixels.copy((frame % (pixels.width() / cw)) * cw,
                              (frame / (pixels.width() / cw)) * ch, cw, ch);
    if (cell.format() == QImage::Format_Indexed8) {
        QVector<QRgb> palette = cell.colorTable();
        for (int i = 0; i < palette.size(); ++i) {
            const QRgb rgb = palette.at(i);
            palette[i] = qRgba(qRed(rgb), qGreen(rgb), qBlue(rgb), i == 0 ? 0 : 255);
        }
        cell.setColorTable(palette);
    }
    if (flip) cell = cell.flipped(Qt::Horizontal);
    return cell;
}

inline QByteArray cQuote(const QString &source) {
    QByteArray output("\"");
    for (const unsigned char c : source.toUtf8()) {
        if (c == '"' || c == '\\') { output += '\\'; output += char(c); }
        else if (c >= 32 && c <= 126) output += char(c);
        else { const char hex[] = "0123456789abcdef"; output += "\\x";
               output += hex[c >> 4]; output += hex[c & 15]; output += "\"\""; }
    }
    return output + '"';
}
inline bool generate(const QDir &project, const QDir &rules, QString *error=nullptr) {
    if (!QFileInfo::exists(profilePath(project))) return true; // older game, opt-in migration
    QJsonObject profile;
    if (!read(project, &profile, error)) return false;
    const QString relativeAtlas = profile.value(QStringLiteral("atlasPath")).toString().trimmed();
    const QFileInfo atlas(project.filePath(relativeAtlas));
    // Only PPB is supported by SIDBOX's V1 external sprite loader.
    if (relativeAtlas.isEmpty() || atlas.suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive)
         || !atlas.isFile() || !atlas.absoluteFilePath().startsWith(project.absolutePath() + QLatin1Char('/'))) {
        if (error) *error = QStringLiteral("Shared player requires an existing project-local PPB atlas: %1").arg(relativeAtlas);
        return false;
    }
    SidboxPpb::Picture picture;
    if (!SidboxPpb::read(atlas.absoluteFilePath(), &picture, error)) return false;
    const int w = picture.indexed.width(), h = picture.indexed.height();
    const int cw = profile.value(QStringLiteral("cellWidth")).toInt();
    const int ch = profile.value(QStringLiteral("cellHeight")).toInt();
    if (w <= 0 || h <= 0 || cw <= 0 || ch <= 0 || cw > w || ch > h
        || w > 65535 || h > 65535 || qint64(w) * h > 8*1024*1024) {
        if (error) *error = QStringLiteral("Player PPB/cell dimensions are invalid.");
        return false;
    }
    const QJsonArray initial = profile.value(QStringLiteral("inventory")).toArray();
    if (initial.size() > 64) {
        if (error) *error = QStringLiteral("A player can define at most 64 inventory types.");
        return false;
    }
    // Custom stats are game-owned mutable values; never recreated on world switches.
    const QJsonArray stats = profile.value(QStringLiteral("customStats")).toArray();
    if (stats.size() > 64) {
        if (error) *error = QStringLiteral("A player can define at most 64 custom stats.");
        return false;
    }
    QByteArray customStats;
    QSet<QString> seenStats;
    for (const QJsonValue &v : stats) {
        const QJsonObject stat = v.toObject();
        const QString name = stat.value(QStringLiteral("name")).toString().trimmed();
        const QJsonValue value = stat.value(QStringLiteral("initial"));
        const QString key = name.toCaseFolded();
        if (name.isEmpty() || name.contains(QLatin1Char('\n')) || seenStats.contains(key)
            || !value.isDouble() || value.toDouble() < -1000000000.0
            || value.toDouble() > 1000000000.0
            || double(int(value.toDouble())) != value.toDouble()) {
            if (error) *error = QStringLiteral("Custom player stat names/values must be unique and valid integers.");
            return false;
        }
        seenStats.insert(key);
        customStats += "    {" + cQuote(name) + ", " + QByteArray::number(value.toInt())
                    + ", " + QByteArray::number(value.toInt()) + "},\n";
    }
    QByteArray inventory;
    QSet<QString> seenInventory;
    for (const QJsonValue &v : initial) {
        const QJsonObject item = v.toObject();
        const QString name = item.value(QStringLiteral("name")).toString().trimmed();
        const int amount = item.value(QStringLiteral("initial")).toInt();
        const QString key = name.toCaseFolded();
        if (name.isEmpty() || name.contains(QLatin1Char('\n'))
            || seenInventory.contains(key) || amount < 0 || amount > 65535) {
            if (error) *error = QStringLiteral("Invalid player inventory name/count.");
            return false;
        }
        seenInventory.insert(key);
        inventory += "    {" + cQuote(name) + ", " + QByteArray::number(amount) + "u, "
                  + (item.value(QStringLiteral("hidden")).toBool(false) ? "1u" : "0u")
                  + "},\n";
    }
    const auto outputPath = QDir(project.filePath(QStringLiteral("gamehelpers")));
    if (!QDir().mkpath(outputPath.absolutePath())) {
        if (error) *error = QStringLiteral("Cannot create shared player code directory.");
        return false;
    }
    // The bank belongs to players/player.sbpi (shared across the whole game).
    // IDs stay stable after deletion so C code can address a profile by ID.
    const QJsonArray physics = physicsProfiles(profile);
    if (physics.isEmpty() || physics.size() > 64) {
        if (error) *error = QStringLiteral("Player needs 1 to 64 movement physics profiles.");
        return false;
    }
    QSet<int> physicsIds;
    QSet<QString> physicsNames;
    QByteArray physicsRows;
    const int presetId = startingPhysicsId(profile);
    for (const QJsonValue &value : physics) {
        const QJsonObject entry = value.toObject();
        const QString name = entry.value(QStringLiteral("name")).toString().trimmed();
        const int id = entry.value(QStringLiteral("id")).toInt(-1);
        const int mode = entry.value(QStringLiteral("mode")).toInt(-1);
        const int walk = entry.value(QStringLiteral("walkSpeed")).toInt(-1);
        const int jump = entry.value(QStringLiteral("jumpSpeed")).toInt(-1);
        const int gravity = entry.value(QStringLiteral("gravity")).toInt(-1);
        const int fall = entry.value(QStringLiteral("maxFallSpeed")).toInt(-1);
        const int drag = entry.value(QStringLiteral("forceDrag")).toInt(-1);
        const int combat = entry.value(QStringLiteral("combatEnabled")).toBool() ? 1 : 0;
        const int attackDamage = entry.value(QStringLiteral("attackDamage")).toInt(1);
        const int attackReach = entry.value(QStringLiteral("attackReach")).toInt(24);
        const int attackCooldown = entry.value(QStringLiteral("attackCooldown")).toInt(15);
        if (attackDamage < 1 || attackDamage > 20 || attackReach < 1 || attackReach > 128
            || attackCooldown < 1 || attackCooldown > 250) {
            if (error) *error = QStringLiteral("Invalid combat settings in physics profile: %1").arg(name);
            return false;
        }
        if (id < 0 || id > 255 || physicsIds.contains(id) || mode < 0 || mode > 6
            || name.isEmpty() || name.contains(QLatin1Char('\n')) || name.size() > 64
            || physicsNames.contains(name.toCaseFolded()) || walk < 0 || walk > 16
            || jump < 0 || jump > 32 || gravity < 0 || gravity > 1000
            || fall < 1 || fall > 32 || drag < 0 || drag > 100) {
            if (error) *error = QStringLiteral("Invalid movement physics profile: %1").arg(name);
            return false;
        }
        physicsIds.insert(id);
        physicsNames.insert(name.toCaseFolded());
        physicsRows += "    {" + QByteArray::number(id) + "u, " + QByteArray::number(mode)
            + "u, " + QByteArray::number(walk) + ", " + QByteArray::number(jump)
            + ", " + QByteArray::number(gravity) + ", " + QByteArray::number(fall)
            + ", " + QByteArray::number(drag) + "u, " + QByteArray::number(combat)
            + "u, " + QByteArray::number(attackDamage) + "u, "
            + QByteArray::number(attackReach) + "u, "
            + QByteArray::number(attackCooldown) + "u},\n";
    }
    if (!physicsIds.contains(presetId)) {
        if (error) *error = QStringLiteral("The starting movement physics profile was removed.");
        return false;
    }
    const QList<QPair<QByteArray,QByteArray>> fields = {
        {"@IDE{PPB_PATH}", cQuote(QDir::fromNativeSeparators(relativeAtlas))},
        {"@IDE{ATLAS_W}", QByteArray::number(w)},
        {"@IDE{ATLAS_H}", QByteArray::number(h)},
        {"@IDE{CELL_W}", QByteArray::number(cw)},
        {"@IDE{CELL_H}", QByteArray::number(ch)},
        {"@IDE{HEALTH}", QByteArray::number(qBound(0,profile.value(QStringLiteral("health")).toInt(100),65535))},
        {"@IDE{LIVES}", QByteArray::number(qBound(0,profile.value(QStringLiteral("lives")).toInt(3),65535))},
        {"@IDE{SCORE}", QByteArray::number(qMax(0,profile.value(QStringLiteral("score")).toInt(0)))},
        {"@IDE{CUSTOM_HITBOX}", profile.value(QStringLiteral("customHitbox")).toBool() ? QByteArray("1") : QByteArray("0")},
        {"@IDE{HITBOX_X}", QByteArray::number(qBound(-1024,profile.value(QStringLiteral("hitboxX")).toInt(),1024))},
        {"@IDE{HITBOX_Y}", QByteArray::number(qBound(-1024,profile.value(QStringLiteral("hitboxY")).toInt(),1024))},
        {"@IDE{HITBOX_W}", QByteArray::number(qBound(1,profile.value(QStringLiteral("hitboxW")).toInt(32),2048))},
        {"@IDE{HITBOX_H}", QByteArray::number(qBound(1,profile.value(QStringLiteral("hitboxH")).toInt(32),2048))},
        {"@IDE{PHYSICS_PRESET}", QByteArray::number(presetId)},
        {"@IDE{PHYSICS_PROFILE_COUNT}", QByteArray::number(physics.size())},
        {"@IDE{PHYSICS_PROFILE_ROWS}", physicsRows},
        {"@IDE{CUSTOM_STAT_COUNT}", QByteArray::number(stats.size())},
        {"@IDE{CUSTOM_STAT_ROWS}", customStats},
        {"@IDE{INVENTORY_COUNT}", QByteArray::number(initial.size())},
        {"@IDE{INVENTORY_ROWS}", inventory}
    };
    // Validate both templates and ownership before touching either file.
    QList<QByteArray> rendered;
    for (const QString &ext : {QStringLiteral(".h"),QStringLiteral(".c")}) {
        QFile templateFile(rules.filePath(QStringLiteral("gameplayer.rule") + (ext == QStringLiteral(".h") ? QStringLiteral("h") : QStringLiteral("c"))));
        if (!templateFile.open(QIODevice::ReadOnly)) {
            if (error) *error = QStringLiteral("Missing SDK gameplayer.rule%1").arg(ext.mid(1));
            return false;
        }
        QByteArray data = templateFile.readAll();
        for (const auto &f : fields) data.replace(f.first, f.second);
        if (data.contains("@IDE{")) {
            if (error) *error = QStringLiteral("Unresolved shared-player rule token.");
            return false;
        }
        QFile previous(outputPath.filePath(QStringLiteral("gameplayer")+ext));
        if (previous.exists() && (!previous.open(QIODevice::ReadOnly)
            || !previous.read(200).contains("GamerGirl Shared Player"))) {
            if (error) *error = QStringLiteral("Refusing to overwrite user-owned %1").arg(previous.fileName());
            return false;
        }
        rendered.append(data);
    }
    int i=0;
    for (const QString &ext : {QStringLiteral(".h"),QStringLiteral(".c")}) {
        QSaveFile out(outputPath.filePath(QStringLiteral("gameplayer")+ext));
        const QByteArray &bytes=rendered.at(i++);
        if (!out.open(QIODevice::WriteOnly) || out.write(bytes)!=bytes.size() || !out.commit()) {
            if (error) *error=QStringLiteral("Cannot write generated gameplayer%1").arg(ext);
            return false;
        }
    }
    return true;
}
} // namespace GamePlayerProfile
#endif

#ifndef CODERGIRL_GAME_WORLD_SNAPSHOT_H
#define CODERGIRL_GAME_WORLD_SNAPSHOT_H

// Stage 5.1: each .sbgm has BOTH a private .codergirl snapshot and a visible
// worlds/<name>/ build tree. The tree compiles simultaneously with other
// worlds; public per-world C identifiers are renamed by a generated header.
// Map output is staged privately in .codergirl/tilemap-staging/<world>/.
// Project-root gamelevels/ is obsolete and is never compiled.
#include <QDateTime>
#include <QColor>
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QSaveFile>
#include <QRegularExpression>
#include <QSet>
#include <QStringList>
#include <QUuid>
#include "gametilemap.h"
#include "gameplayerprofile.h"

namespace GameWorldSnapshot {

inline QString activeFile(const QString &designPath)
{
    return QFileInfo(designPath).absoluteDir().filePath(
        QStringLiteral(".codergirl/active-world.json"));
}

inline bool isActive(const QString &designPath)
{
    QFile file(activeFile(designPath));
    if (!file.open(QIODevice::ReadOnly)) return false;
    const auto doc = QJsonDocument::fromJson(file.readAll());
    if (!doc.isObject()) return false;
    return QFileInfo(doc.object().value(QStringLiteral("designFile")).toString()).absoluteFilePath()
        == QFileInfo(designPath).absoluteFilePath();
}

inline bool hasActiveSelection(const QString &designPath)
{
    return QFileInfo::exists(activeFile(designPath));
}

// Two different filenames can sanitise to the same C symbol (e.g.
// "Cave 2.sbgm" and "Cave-2.sbgm"). Never let them share a world bundle.
inline bool validateUniqueName(const QString &designPath, QString *error)
{
    const QFileInfo design(designPath);
    const QDir folder(design.absolutePath());
    const QString worldName = sidboxTilemapWorldBaseName(designPath);
    for (const QFileInfo &candidate : folder.entryInfoList(QDir::Files | QDir::NoDotAndDotDot)) {
        if (candidate.suffix().compare(QStringLiteral("sbgm"), Qt::CaseInsensitive) != 0
            || candidate.absoluteFilePath() == design.absoluteFilePath()) continue;
        if (sidboxTilemapWorldBaseName(candidate.absoluteFilePath())
                .compare(worldName, Qt::CaseInsensitive) == 0) {
            if (error) *error = QStringLiteral(
                "Two .sbgm worlds would export the same C/file name '%1': %2 and %3. "
                "Rename one design before generating either world.")
                    .arg(worldName, design.fileName(), candidate.fileName());
            return false;
        }
    }
    return true;
}

// Build the C namespace from the *actual rendered public declarations*, not
// resource-name guesses. This includes each world's named sprites, draw calls,
// PPB atlas lookup, sounds, music, NPC callbacks and exported spline arrays.
// The macro header is included BEFORE every generated world translation unit;
// the C compiler therefore emits genuinely distinct linker symbols.
inline QSet<QString> exportedIdentifiers(const QString &bundleDirectory)
{
    QSet<QString> names;
    const QStringList headers = {
        QStringLiteral("gameassets/gameassets.h"),
        QStringLiteral("gamehelpers/gameworlditems.h"),
        QStringLiteral("gamehelpers/gameadventure.h"),
        QStringLiteral("gamehelpers/splinepaths.h")
    };
    const QRegularExpression functionRe(QStringLiteral(
        R"((?m)^\s*(?:extern\s+)?[A-Za-z_][A-Za-z_0-9 \t\*]*?\s*\*?\s*([A-Za-z_][A-Za-z_0-9]*)\s*\()"));
    const QRegularExpression externRe(QStringLiteral(
        R"((?m)^\s*extern\s+[^;\n]*?\b([A-Za-z_][A-Za-z_0-9]*)\s*(?:\[[^;\n]*\])?\s*;)"));
    for (const QString &relative : headers) {
        QFile input(QDir(bundleDirectory).filePath(relative));
        if (!input.open(QIODevice::ReadOnly)) continue;
        const QString content = QString::fromUtf8(input.readAll());
        auto functions = functionRe.globalMatch(content);
        while (functions.hasNext()) {
            const QString name = functions.next().captured(1);
            if (!name.isEmpty()) names.insert(name);
        }
        auto externs = externRe.globalMatch(content);
        while (externs.hasNext()) {
            const QString name = externs.next().captured(1);
            if (!name.isEmpty()) names.insert(name);
        }
    }
    // Mandatory public functions also cover pointer-return types without
    // whitespace before the asterisk, and empty-world rule stubs.
    for (const char *name : {"gameassets_init", "gameassets_shutdown",
            "gameassets_front_palette", "gameassets_back_palette",
            "gameassets_find_ppb", "gameassets_draw_foreground",
            "gameassets_draw_background", "gameassets_draw_layers",
            "gameassets_show_background", "drawworld",
            "gameworlditems_init", "gameworlditems_update", "gameworlditems_draw",
            "gameworlditems_draw_behind", "gameworlditems_draw_overlay", "gameworlditems_check",
            "gameworlditems_before", "gameworlditems_after",
            "gameworlditems_set_active", "gameworlditems_trigger",
            "gameadventure_setup", "gameadventure_on_event",
            "gameworlditems_save_state", "gameworlditems_restore_state",
            "gameworlditems_remote_action", "gameworlditems_remote_reset",
            "gameworlditems_apply_remote", "gameadventure_save_progress", "gameadventure_restore_progress",
            "gameadventure_npc_action", "gameadventure_npc_remote_action", "gameadventure_npc_remote_reset"}) {
        names.insert(QLatin1String(name));
    }
    return names;
}

inline bool publishBuildTree(const QString &bundleDirectory, const QDir &project,
                             const QString &worldName, const QStringList &files,
                             bool hasMap, QString *error)
{
    const QString worlds = project.filePath(QStringLiteral("worlds"));
    if (!QDir().mkpath(worlds)) {
        if (error) *error = QStringLiteral("Cannot create worlds directory: %1").arg(worlds);
        return false;
    }
    const QString uuid = QUuid::createUuid().toString(QUuid::WithoutBraces);
    const QString staging = QDir(worlds).filePath(QStringLiteral(".staging-") + uuid);
    const QString destination = QDir(worlds).filePath(worldName);
    const QString previous = QDir(worlds).filePath(QStringLiteral(".previous-") + uuid);
    if (!QDir().mkpath(staging)) {
        if (error) *error = QStringLiteral("Cannot stage buildable world: %1").arg(worldName);
        return false;
    }
    auto abort = [&](const QString &reason) {
        QDir(staging).removeRecursively();
        if (error) *error = reason;
        return false;
    };
    const QStringList symbols = exportedIdentifiers(bundleDirectory).values();
    QStringList sorted = symbols;
    sorted.sort(Qt::CaseSensitive);
    QByteArray mappings = "/* CoderGirl generated; public C symbols belong to this world. */\n"
                          "/* Included by world C modules before their own headers. */\n";
    for (const QString &name : sorted) {
        static const QRegularExpression valid(QStringLiteral("^[A-Za-z_][A-Za-z_0-9]*$"));
        if (!valid.match(name).hasMatch())
            return abort(QStringLiteral("Invalid world C export: %1").arg(name));
        mappings += "#define " + name.toUtf8() + " " + worldName.toUtf8()
                    + "_" + name.toUtf8() + "\n";
    }
    for (const QString &relative : files) {
        // maingame is documentation/starter code, not an additional entry point.
        if (relative == QStringLiteral("maingame.c.txt")) continue;
        const QString inputPath = QDir(bundleDirectory).filePath(relative);
        QFile source(inputPath);
        if (!source.open(QIODevice::ReadOnly))
            return abort(QStringLiteral("Cannot read world file: %1").arg(inputPath));
        QByteArray bytes = source.readAll();
        if (relative.endsWith(QStringLiteral(".c")))
            bytes.prepend("#include \"../world_symbols.h\"\n");
        // The tilemap header's normal ../gamehelpers include is correct in
        // project/gamelevels/, but this mirror is three directories deeper.
        if (relative.startsWith(QStringLiteral("gamelevels/"))
            && relative.endsWith(QStringLiteral(".h")))
            bytes.replace("\"../gamehelpers/gametilemap.h\"",
                          "\"../../../gamehelpers/gametilemap.h\"");
        const QString output = QDir(staging).filePath(relative);
        if (!QDir().mkpath(QFileInfo(output).absolutePath()))
            return abort(QStringLiteral("Cannot create world output: %1").arg(output));
        QSaveFile target(output);
        if (!target.open(QIODevice::WriteOnly) || target.write(bytes) != bytes.size()
            || !target.commit())
            return abort(QStringLiteral("Cannot write world module: %1").arg(output));
    }
    auto writeFile = [&](const QString &relative, const QByteArray &bytes) {
        QSaveFile out(QDir(staging).filePath(relative));
        return out.open(QIODevice::WriteOnly) && out.write(bytes) == bytes.size() && out.commit();
    };
    if (!writeFile(QStringLiteral("world_symbols.h"), mappings))
        return abort(QStringLiteral("Cannot write world namespace header."));

    // This public header is safe to include alongside other world_api.h files.
    // No preprocessor alias leaks into main.c or other world headers.
    const QByteArray id = worldName.toUtf8();
    QByteArray api = "/* Public Stage 5.2 world-module entry points (used by gameworlds.c). */\n"
                     "#ifndef CODERGIRL_WORLD_API_" + id.toUpper() + "_H\n"
                     "#define CODERGIRL_WORLD_API_" + id.toUpper() + "_H\n"
                     "#include <stdint.h>\n"
                     "#include \"../../gamehelpers/gameworlds.h\"\n"
                     "int " + id + "_gameassets_init(void);\n"
                     "void " + id + "_gameassets_shutdown(void);\n"
                     "const uint32_t *" + id + "_gameassets_front_palette(void);\n"
                     "const uint32_t *" + id + "_gameassets_back_palette(void);\n"
                     "void " + id + "_gameassets_draw_foreground(void);\n"
                     "void " + id + "_gameassets_draw_background(void);\n"
                     "void " + id + "_drawworld(void);\n"
                     "uint8_t " + id + "_gameworlditems_init(void);\n"
                     "void " + id + "_gameworlditems_save_state(void);\n"
                     "void " + id + "_gameworlditems_restore_state(void);\n"
                     "void " + id + "_gameworlditems_set_active(uint16_t,uint8_t);\n"
                     "void " + id + "_gameworlditems_remote_action(uint16_t,uint8_t);\n"
                     "void " + id + "_gameworlditems_remote_reset(void);\n"
                     "void " + id + "_gameworlditems_apply_remote(void);\n"
                     "void " + id + "_gameworlditems_update(uint16_t frames);\n"
                     "void " + id + "_gameworlditems_draw(int32_t x, int32_t y);\n"
                     "void " + id + "_gameadventure_setup(void);\n"
                     "void " + id + "_gameadventure_save_progress(void);\n"
                     "void " + id + "_gameadventure_restore_progress(void);\n"
                     "void " + id + "_gameadventure_npc_action(uint16_t,uint8_t);\n"
                     "void " + id + "_gameadventure_npc_remote_action(uint16_t,uint8_t);\n"
                     "void " + id + "_gameadventure_npc_remote_reset(void);\n"
                     "void " + id + "_gameadventure_store_inventory(gameworlds_inventory_put_t,void *);\n"
                     "void " + id + "_gameadventure_load_inventory(gameworlds_inventory_get_t,void *);\n"
                     "void " + id + "_gameassets_show_background(void);\n";
    {
        QFile objectsHeader(QDir(bundleDirectory).filePath(QStringLiteral("gamehelpers/gameworlditems.h")));
        const QByteArray exported = objectsHeader.open(QIODevice::ReadOnly)
            ? objectsHeader.readAll() : QByteArray();
        if (exported.contains("gameworlditems_draw_behind"))
            api += "void " + id + "_gameworlditems_draw_behind(int32_t,int32_t);\n";
        if (exported.contains("gameworlditems_draw_overlay"))
            api += "void " + id + "_gameworlditems_draw_overlay(int32_t,int32_t);\n";
        if (exported.contains("gameworlditems_before")) {
            api += "void " + id + "_gameworlditems_before(game_world_player_t*);\n";
            api += "void " + id + "_gameworlditems_after(game_world_player_t*);\n";
        }
        if (exported.contains("gameworlditems_check"))
            api += "uint16_t " + id + "_gameworlditems_check(int32_t,int32_t,uint16_t,uint16_t,game_pickup_callback_t,void*);\n";
    }
    if (hasMap) {
        api += "#include \"../../gamehelpers/gametilemap.h\"\n"
               "#include \"gamelevels/" + id + ".h\"\n";
    }
    api += "#endif\n";
    if (!writeFile(QStringLiteral("world_api.h"), api))
        return abort(QStringLiteral("Cannot write public world API header."));

    // Never replace a user's existing folder unless it was already created
    // by this exact world exporter. A previous .sbgm test or ordinary custom
    // sources must not be destroyed as a side effect of regeneration.
    const bool hadOld = QDir(destination).exists();
    if (hadOld) {
        QFile prior(QDir(destination).filePath(QStringLiteral("world-build.json")));
        const auto priorManifest = prior.open(QIODevice::ReadOnly)
            ? QJsonDocument::fromJson(prior.readAll()) : QJsonDocument();
        if (!priorManifest.isObject()
            || priorManifest.object().value(QStringLiteral("format")).toString()
                   != QStringLiteral("CODERGIRL-V1-COMPILED-WORLD")
            || priorManifest.object().value(QStringLiteral("worldName")).toString() != worldName)
            return abort(QStringLiteral("Refusing to overwrite user folder worlds/%1. "
                "Move it aside or use a different world name.").arg(worldName));
        // A programmer may add custom files to the visible folder after
        // generation. Never delete those during a later world export.
        QSet<QString> ownedFiles;
        for (const QJsonValue &value : priorManifest.object().value(QStringLiteral("files")).toArray())
            ownedFiles.insert(value.toString());
        QDirIterator iterator(destination, QDir::Files | QDir::NoDotAndDotDot,
                              QDirIterator::Subdirectories);
        while (iterator.hasNext()) {
            const QString existing = QDir(destination).relativeFilePath(iterator.next());
            // Stage 5.36.2: Stage 5.36.1 accidentally generated a TFCard
            // checklist *outside* world-build.json's owned file set. Do not
            // block regeneration on our own abandoned artifact. The staging
            // swap discards it only after publication succeeds; every other
            // unowned file remains protected as before. Require our header so
            // a user-written file with the same name is not silently deleted.
            if (existing == QStringLiteral("TFCard-REQUIRED-FILES.txt")) {
                QFile generatedChecklist(QDir(destination).filePath(existing));
                if (generatedChecklist.open(QIODevice::ReadOnly) &&
                    generatedChecklist.readLine().trimmed() ==
                        QByteArray("# CoderGirl TFCard dependency checklist (generated, do not edit)"))
                    continue;
            }
            if (!ownedFiles.contains(existing))
                return abort(QStringLiteral("World %1 contains an additional file '%2'. "
                    "Move custom code outside the generated world folder before updating.")
                    .arg(worldName, existing));
        }
    }
    QJsonArray buildFiles;
    for (const QString &relative : files)
        if (relative != QStringLiteral("maingame.c.txt")) buildFiles.append(relative);
    buildFiles.append(QStringLiteral("world_symbols.h"));
    buildFiles.append(QStringLiteral("world_api.h"));
    buildFiles.append(QStringLiteral("world-build.json"));
    QJsonObject buildManifest;
    buildManifest.insert(QStringLiteral("files"), buildFiles);
    buildManifest.insert(QStringLiteral("format"), QStringLiteral("CODERGIRL-V1-COMPILED-WORLD"));
    buildManifest.insert(QStringLiteral("version"), 1);
    buildManifest.insert(QStringLiteral("worldName"), worldName);
    buildManifest.insert(QStringLiteral("generatedAt"),
        QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    if (!writeFile(QStringLiteral("world-build.json"),
                   QJsonDocument(buildManifest).toJson(QJsonDocument::Indented)))
        return abort(QStringLiteral("Cannot write world build manifest."));
    if (hadOld && !QDir().rename(destination, previous))
        return abort(QStringLiteral("Cannot preserve previous buildable world."));
    if (!QDir().rename(staging, destination)) {
        if (hadOld) QDir().rename(previous, destination);
        return abort(QStringLiteral("Cannot publish buildable world: %1").arg(worldName));
    }
    if (hadOld) QDir(previous).removeRecursively();
    return true;
}

// Stage 5.2: regenerate ONE shared dispatcher from ALL published worlds.
// These are C symbol addresses and validated filenames, never C gameplay logic.
// Runtime behaviour belongs to gameworlds.rulec/.ruleh.
inline bool publishWorldRegistry(const QDir &project, const QDir &templates,
                                QString *error)
{
    const QDir worlds(project.filePath(QStringLiteral("worlds")));
    const QRegularExpression identifier(QStringLiteral("^[A-Za-z_][A-Za-z0-9_]*$"));
    QStringList names = worlds.entryList(QDir::Dirs | QDir::NoDotAndDotDot,
                                         QDir::Name | QDir::IgnoreCase);
    QStringList published, declarations, records;
    QJsonObject sharedPlayer;
    const bool hasSharedPlayer = QFileInfo::exists(GamePlayerProfile::profilePath(project));
    if (hasSharedPlayer && !GamePlayerProfile::read(project, &sharedPlayer, error)) return false;
    QSet<int> availableProfiles;
    for (const QJsonValue &value : GamePlayerProfile::physicsProfiles(sharedPlayer))
        availableProfiles.insert(value.toObject().value(QStringLiteral("id")).toInt(-1));
    QStringList beforeFns, afterFns, checkFns, spawnFields, namedStartFields;
    QStringList spawnDeclarations, defaultTransitionIn, defaultTransitionOut, defaultTransitionFrames, defaultCircleOrigin;
    QStringList defaultSpotlightEnabled, defaultSpotlightRadius, defaultSpotlightFeather;
    QStringList defaultSpotlightCenter, defaultSpotlightOffsetX, defaultSpotlightOffsetY;
    QStringList defaultSpotlightMaskIndex, defaultSpotlightMaskColour;
    QStringList defaultSpotlightFlipX, defaultSpotlightFlipY, defaultSpotlightOpacity;
    QStringList defaultSpotlightStable, defaultSpotlightAnimMode, defaultSpotlightAnimMin;
    QStringList defaultSpotlightAnimMax, defaultSpotlightRandomMin, defaultSpotlightRandomMax;
    QStringList defaultSpotlightPulseDelay;
    QStringList frontPaletteFns, backPaletteFns;
    bool anyAdventure = false, anyWorldPhysics = false, anyPickups = false;
    for (const QString &name : names) {
        if (name.startsWith(QLatin1Char('.'))) continue;
        const QString directory = worlds.filePath(name);
        // A user may keep their own world folders. Only published GamerGirl
        // directories, identified by our manifest, are registry members.
        if (!QFileInfo::exists(QDir(directory).filePath(QStringLiteral("world-build.json"))))
            continue;
        QFile build(QDir(directory).filePath(QStringLiteral("world-build.json")));
        QFile bundle(project.filePath(QStringLiteral(".codergirl/worlds/") + name
                                      + QStringLiteral("/world.json")));
        if (!build.open(QIODevice::ReadOnly) || !bundle.open(QIODevice::ReadOnly)) {
            if (error) *error = QStringLiteral("Missing world build/bundle manifest for '%1'.").arg(name);
            return false;
        }
        const auto b = QJsonDocument::fromJson(build.readAll()).object();
        const auto meta = QJsonDocument::fromJson(bundle.readAll()).object();
        if (b.value(QStringLiteral("format")).toString() != QStringLiteral("CODERGIRL-V1-COMPILED-WORLD")
            || b.value(QStringLiteral("worldName")).toString() != name
            || meta.value(QStringLiteral("worldName")).toString() != name
            || !identifier.match(name).hasMatch()) {
            if (error) *error = QStringLiteral("Invalid or conflicting published world '%1'.").arg(name);
            return false;
        }
        published << name;
        const QString stem = name + QStringLiteral("_");
        const bool hasMap = QFileInfo::exists(QDir(directory).filePath(
            QStringLiteral("gamelevels/") + name + QStringLiteral(".c")));
        QFile publicApi(QDir(directory).filePath(QStringLiteral("world_api.h")));
        const QByteArray exposed = publicApi.open(QIODevice::ReadOnly)
            ? publicApi.readAll() : QByteArray();
        const bool behind = exposed.contains("gameworlditems_draw_behind");
        const bool overlay = exposed.contains("gameworlditems_draw_overlay");
        const bool inventoryApi = exposed.contains("gameadventure_store_inventory");
        const bool showBackground = exposed.contains("gameassets_show_background");
        // Old published worlds might still be Stage 5.45 while the user
        // regenerates them one by one. Never reference absent new symbols.
        frontPaletteFns << (exposed.contains("gameassets_front_palette")
            ? name + QStringLiteral("_gameassets_front_palette") : QStringLiteral("0"));
        backPaletteFns << (exposed.contains("gameassets_back_palette")
            ? name + QStringLiteral("_gameassets_back_palette") : QStringLiteral("0"));
        const bool hasWorldPhysics = exposed.contains("gameworlditems_before");
        const bool hasPickup = exposed.contains("gameworlditems_check");
        anyWorldPhysics |= hasWorldPhysics;
        anyPickups |= hasPickup;
        beforeFns << (hasWorldPhysics ? name + QStringLiteral("_gameworlditems_before") : QStringLiteral("0"));
        afterFns << (hasWorldPhysics ? name + QStringLiteral("_gameworlditems_after") : QStringLiteral("0"));
        checkFns << (hasPickup ? name + QStringLiteral("_gameworlditems_check") : QStringLiteral("0"));
        anyAdventure |= meta.value(QStringLiteral("hasAdventure")).toBool();
        declarations << QStringLiteral("#include \"../worlds/%1/world_api.h\"").arg(name);
        const QString zero = QStringLiteral("0");
        const QString objectsBehind = behind ? stem + QStringLiteral("gameworlditems_draw_behind") : zero;
        const QString objectsOverlay = overlay ? stem + QStringLiteral("gameworlditems_draw_overlay") : zero;
        const QString inventoryStore = inventoryApi
            ? stem + QStringLiteral("gameadventure_store_inventory") : zero;
        const QString inventoryLoad = inventoryApi
            ? stem + QStringLiteral("gameadventure_load_inventory") : zero;
        const QString showDirect = showBackground
            ? stem + QStringLiteral("gameassets_show_background") : zero;
        const QString mapVar = hasMap ? QStringLiteral("&game_") + name : zero;
        const QString mapLoad = hasMap ? QStringLiteral("game_") + name + QStringLiteral("_load_map") : zero;
        const QString mapUnload = hasMap ? QStringLiteral("game_") + name + QStringLiteral("_unload_map") : zero;
        const QString atlasLoad = hasMap ? QStringLiteral("game_") + name + QStringLiteral("_load_atlas") : zero;
        const QString atlasUnload = hasMap ? QStringLiteral("game_") + name + QStringLiteral("_unload_atlas") : zero;
        const QString mapPath = meta.value(QStringLiteral("externalMap")).toBool() && hasMap
            ? QStringLiteral("\"gamelevels/") + name + QStringLiteral(".map\"") : zero;
        // Stage 5.4: Player Start is WORLD metadata, not another player object.
        // Read the SAVED .sbgm, not whichever designer tab happens to be open.
        QJsonObject design;
        QFile designFile(meta.value(QStringLiteral("designFile")).toString());
        if (designFile.open(QIODevice::ReadOnly))
            design = QJsonDocument::fromJson(designFile.readAll()).object();
        const QJsonObject start = design.value(QStringLiteral("playerStart")).toObject();
        int spawnX = start.value(QStringLiteral("x")).toInt(0);
        int spawnY = start.value(QStringLiteral("y")).toInt(0);
        if (start.isEmpty()) { // Backwards compatible with pre-5.4 player placement.
            for (const QJsonValue &value : design.value(QStringLiteral("resources")).toArray()) {
                const QJsonObject resource=value.toObject();
                if (resource.value(QStringLiteral("kind")).toString()==QStringLiteral("sprite")
                    && resource.value(QStringLiteral("name")).toString().compare(
                        QStringLiteral("player"),Qt::CaseInsensitive)==0) {
                    spawnX=resource.value(QStringLiteral("x")).toInt();
                    spawnY=resource.value(QStringLiteral("y")).toInt();
                    break;
                }
            }
        }
        const int facing=qBound(0,start.value(QStringLiteral("facing")).toInt(1),1);
        const int worldPhysicsId = hasSharedPlayer
            ? GamePlayerProfile::physicsForWorld(sharedPlayer, name) : 0;
        if (hasSharedPlayer && !availableProfiles.contains(worldPhysicsId)) {
            if (error) *error = QStringLiteral("World '%1' references missing physics profile ID %2.")
                .arg(name).arg(worldPhysicsId);
            return false;
        }
        const auto transitionMode = [](const QString &key) {
            static const QStringList modes = {QStringLiteral("none"), QStringLiteral("fade"),
                QStringLiteral("left"), QStringLiteral("right"), QStringLiteral("up"),
                QStringLiteral("down"), QStringLiteral("circle")};
            return qMax(0, modes.indexOf(key));
        };
        const int outMode = transitionMode(start.value(QStringLiteral("transitionOut")).toString());
        const int inMode = transitionMode(start.value(QStringLiteral("transitionIn")).toString());
        const int transitionFrames = qBound(1, start.value(QStringLiteral("transitionFrames")).toInt(30), 150);
        defaultTransitionIn << QString::number(inMode);
        defaultTransitionOut << QString::number(outMode);
        defaultTransitionFrames << QString::number(transitionFrames);
        defaultCircleOrigin << (start.value(QStringLiteral("circleOrigin")).toString() == QStringLiteral("location")
            ? QStringLiteral("1") : QStringLiteral("0"));
        defaultSpotlightEnabled << (start.value(QStringLiteral("spotlightEnabled")).toBool(false)
            ? QStringLiteral("1") : QStringLiteral("0"));
        defaultSpotlightRadius << QString::number(qBound(16, start.value(QStringLiteral("spotlightRadius")).toInt(96), 240));
        defaultSpotlightFeather << QString::number(qBound(0, start.value(QStringLiteral("spotlightFeather")).toInt(24), 96));
        defaultSpotlightCenter << (start.value(QStringLiteral("spotlightCenter")).toBool(true)
            ? QStringLiteral("1") : QStringLiteral("0"));
        defaultSpotlightOffsetX << QString::number(qBound(-240, start.value(QStringLiteral("spotlightOffsetX")).toInt(0), 240));
        defaultSpotlightOffsetY << QString::number(qBound(-240, start.value(QStringLiteral("spotlightOffsetY")).toInt(0), 240));
        defaultSpotlightFlipX << (start.value(QStringLiteral("spotlightFlipX")).toBool(false) ? QStringLiteral("1") : QStringLiteral("0"));
        defaultSpotlightFlipY << (start.value(QStringLiteral("spotlightFlipY")).toBool(false) ? QStringLiteral("1") : QStringLiteral("0"));
        /* The runtime uses 0 for old generated rows (100% opacity). New values
         * encode percent+1, so 1 means genuine zero-opacity darkness. */
        defaultSpotlightOpacity << QString::number(qBound(0, start.value(QStringLiteral("spotlightOpacity")).toInt(100), 100) + 1);
        defaultSpotlightStable << (start.value(QStringLiteral("spotlightStableDither")).toBool(true) ? QStringLiteral("1") : QStringLiteral("0"));
        defaultSpotlightAnimMode << QString::number(qBound(0, start.value(QStringLiteral("spotlightAnimMode")).toInt(0), 2));
        const int amin = qBound(0, start.value(QStringLiteral("spotlightAnimMin")).toInt(12), 96);
        defaultSpotlightAnimMin << QString::number(amin);
        defaultSpotlightAnimMax << QString::number(qBound(amin, start.value(QStringLiteral("spotlightAnimMax")).toInt(32), 96));
        const int dmin = qBound(1, start.value(QStringLiteral("spotlightAnimDelayMin")).toInt(3), 600);
        defaultSpotlightRandomMin << QString::number(dmin);
        defaultSpotlightRandomMax << QString::number(qBound(dmin, start.value(QStringLiteral("spotlightAnimDelayMax")).toInt(12), 600));
        defaultSpotlightPulseDelay << QString::number(qBound(1, start.value(QStringLiteral("spotlightAnimPulseDelay")).toInt(3), 600));
        defaultSpotlightMaskIndex << QString::number(qBound(1, start.value(QStringLiteral("spotlightMaskIndex")).toInt(255), 255));
        {
            QColor mask(start.value(QStringLiteral("spotlightMaskColour")).toString(QStringLiteral("#000000")));
            if (!mask.isValid()) mask = QColor(Qt::black);
            defaultSpotlightMaskColour << QStringLiteral("0xff%1u")
                .arg(qulonglong(mask.rgb() & 0xffffffu), 6, 16, QLatin1Char('0'));
        }
        spawnFields << QStringLiteral(", %1, %2, %3, %4")
            .arg(spawnX).arg(spawnY).arg(facing).arg(worldPhysicsId);
        QStringList entries;
        QSet<QString> knownIds{QStringLiteral("default")};
        const QRegularExpression startIdPattern(QStringLiteral("^[a-zA-Z0-9_-]{1,63}$"));
        for (const QJsonValue &v : design.value(QStringLiteral("playerStarts")).toArray()) {
            const QJsonObject entry = v.toObject();
            const QString id = entry.value(QStringLiteral("id")).toString();
            if (!startIdPattern.match(id).hasMatch() || knownIds.contains(id)) {
                if (error) *error = QStringLiteral("Invalid or duplicate Player Start ID in '%1'.").arg(name);
                return false;
            }
            knownIds.insert(id);
            entries << QStringLiteral("{\"%1\", %2, %3, %4, %5, %6, %7, %8}")
                .arg(id)
                .arg(qBound(0, entry.value(QStringLiteral("x")).toInt(), 32767))
                .arg(qBound(0, entry.value(QStringLiteral("y")).toInt(), 32767))
                .arg(qBound(0, entry.value(QStringLiteral("facing")).toInt(1), 1))
                .arg(transitionMode(entry.value(QStringLiteral("transitionIn")).toString()))
                .arg(transitionMode(entry.value(QStringLiteral("transitionOut")).toString()))
                .arg(qBound(1, entry.value(QStringLiteral("transitionFrames")).toInt(30), 150))
                .arg(entry.value(QStringLiteral("circleOrigin")).toString() == QStringLiteral("location") ? 1 : 0);
        }
        if (entries.isEmpty()) namedStartFields << QStringLiteral(", 0, 0");
        else {
            const QString symbol = name + QStringLiteral("_player_starts");
            spawnDeclarations << QStringLiteral("static const gameworlds_named_spawn_t %1[] = { %2 };")
                .arg(symbol, entries.join(QStringLiteral(", ")));
            namedStartFields << QStringLiteral(", %1, sizeof(%1) / sizeof(%1[0])").arg(symbol);
        }
        QString row = QStringLiteral("    {\"%1\", %2gameassets_init, %2gameassets_shutdown,\n"
            "     %2gameworlditems_init, %2gameworlditems_update, %2gameworlditems_draw, %3, %4,\n"
            "     %2gameassets_draw_foreground, %2gameassets_draw_background, %5,\n"
            "     %2gameadventure_setup, %6, %7,\n"
            "     %8, %9, %10, %11, %12, %13}");
        const QStringList values = {name, stem, objectsBehind, objectsOverlay, showDirect,
            inventoryStore, inventoryLoad, mapVar, mapLoad, mapUnload,
            atlasLoad, atlasUnload, mapPath};
        for (int i = values.size(); i >= 1; --i)
            row.replace(QStringLiteral("%") + QString::number(i), values.at(i - 1));
        records << row;
    }
    if (published.isEmpty()) {
        if (error) *error = QStringLiteral("No published worlds exist to create a world registry.");
        return false;
    }
    for (int i = 0; i < records.size(); ++i) {
        QString &entry = records[i];
        entry.chop(1); // old final '}'
        if (anyWorldPhysics)
            entry += QStringLiteral(", ") + beforeFns.at(i) + QStringLiteral(", ") + afterFns.at(i);
        if (anyPickups)
            entry += QStringLiteral(", ") + checkFns.at(i);
        entry += spawnFields.at(i);
        entry += namedStartFields.at(i);
        // Transition defaults belong to the saved world's default entrance.
        // Each named entrance overrides them in its own generated row.
        entry += QStringLiteral(", %1, %2, %3, %4").arg(defaultTransitionIn.at(i))
            .arg(defaultTransitionOut.at(i)).arg(defaultTransitionFrames.at(i)).arg(defaultCircleOrigin.at(i));
        entry += QStringLiteral(", %1, %2, %3, %4, %5, %6").arg(defaultSpotlightEnabled.at(i))
            .arg(defaultSpotlightRadius.at(i)).arg(defaultSpotlightFeather.at(i))
            .arg(defaultSpotlightCenter.at(i)).arg(defaultSpotlightOffsetX.at(i))
            .arg(defaultSpotlightOffsetY.at(i));
        entry += QStringLiteral(", %1, %2").arg(defaultSpotlightMaskIndex.at(i), defaultSpotlightMaskColour.at(i));
        entry += QStringLiteral(", %1, %2, %3").arg(defaultSpotlightFlipX.at(i))
            .arg(defaultSpotlightFlipY.at(i)).arg(defaultSpotlightOpacity.at(i));
        entry += QStringLiteral(", %1, %2, %3, %4, %5, %6, %7").arg(defaultSpotlightStable.at(i))
            .arg(defaultSpotlightAnimMode.at(i)).arg(defaultSpotlightAnimMin.at(i))
            .arg(defaultSpotlightAnimMax.at(i)).arg(defaultSpotlightRandomMin.at(i))
            .arg(defaultSpotlightRandomMax.at(i)).arg(defaultSpotlightPulseDelay.at(i));
        entry += QStringLiteral(", %1, %2")
            .arg(frontPaletteFns.at(i), backPaletteFns.at(i));
        const QString id = published.at(i);
        entry += QStringLiteral(", %1_gameworlditems_save_state, %1_gameworlditems_restore_state, "
                                "%1_gameadventure_save_progress, %1_gameadventure_restore_progress, "
                                "%1_gameworlditems_set_active, %1_gameworlditems_remote_action, "
                                "%1_gameworlditems_remote_reset, %1_gameworlditems_apply_remote, "
                                "%1_gameadventure_npc_action, %1_gameadventure_npc_remote_action, "
                                "%1_gameadventure_npc_remote_reset")
            .arg(id);
        entry += QLatin1Char('}');
    }
    // Use active selection as initial world. This does NOT force main.c to
    // load anything; it only chooses the default for gameworlds_start(NULL).
    QFile active(project.filePath(QStringLiteral(".codergirl/active-world.json")));
    if (active.open(QIODevice::ReadOnly)) {
        const QString first = QJsonDocument::fromJson(active.readAll()).object()
            .value(QStringLiteral("worldName")).toString();
        if (published.contains(first)) {
            published.removeAll(first);
            published.prepend(first);
        }
    }
    // Reorder C records to keep the same default order as published names.
    // Each record begins with the escaped, validated name literal.
    QStringList ordered;
    for (const QString &name : published)
        for (const QString &record : records)
            if (record.startsWith(QStringLiteral("    {\"") + name + QStringLiteral("\",")))
                ordered << record;
    QFile source(templates.filePath(QStringLiteral("gameworlds.rulec")));
    QFile header(templates.filePath(QStringLiteral("gameworlds.ruleh")));
    if (!source.open(QIODevice::ReadOnly) || !header.open(QIODevice::ReadOnly)) {
        if (error) *error = QStringLiteral("Missing SDK gameworlds.rulec/.ruleh templates.");
        return false;
    }
    QByteArray generated = source.readAll();
    generated.replace("@IDE{WORLD_DECLARATIONS}",
        (declarations + spawnDeclarations).join(QLatin1Char('\n')).toUtf8());
    generated.replace("@IDE{WORLD_RECORDS}", ordered.join(QStringLiteral(",\n")).toUtf8());
    const auto renderConditions = [&](QByteArray *content) -> bool {
        const QByteArray flagEnd = "@IDE_END\n";
        const QList<QPair<QByteArray, bool>> flags = {
            {"@IDE_IF{HAS_ADVENTURE_RUNTIME}\n", anyAdventure},
            {"@IDE_IF{HAS_WORLD_PHYSICS}\n", anyWorldPhysics},
            {"@IDE_IF{HAS_PICKUPS}\n", anyPickups},
            {"@IDE_IF{HAS_PLAYER_VISIBILITY}\n", anyAdventure && hasSharedPlayer},
            {"@IDE_IF{HAS_SHARED_PLAYER}\n", hasSharedPlayer}
        };
        for (const auto &flag : flags) {
            int cursor = 0;
            while ((cursor = content->indexOf(flag.first, cursor)) >= 0) {
                const int end = content->indexOf(flagEnd, cursor + flag.first.size());
                if (end < 0) return false;
                const QByteArray block = content->mid(cursor + flag.first.size(),
                                                     end - cursor - flag.first.size());
                content->replace(cursor, end + flagEnd.size() - cursor,
                                 flag.second ? block : QByteArray());
                cursor += flag.second ? block.size() : 0;
            }
        }
        return !content->contains("@IDE_IF{") && !content->contains("@IDE_END");
    };
    if (!renderConditions(&generated)) {
        if (error) *error = QStringLiteral("Invalid conditions in gameworlds.rulec.");
        return false;
    }
    if (generated.contains("@IDE{") || generated.contains("@IDE_IF{") || generated.contains("@IDE_END")) {
        if (error) *error = QStringLiteral("Unresolved world registry rule token.");
        return false;
    }
    const QString root = project.filePath(QStringLiteral("gamehelpers"));
    if (!QDir().mkpath(root)) {
        if (error) *error = QStringLiteral("Could not create gamehelpers for world manager.");
        return false;
    }
    const QStringList dests = {QDir(root).filePath(QStringLiteral("gameworlds.h")),
                               QDir(root).filePath(QStringLiteral("gameworlds.c"))};
    QByteArray renderedHeader = header.readAll();
    if (!renderConditions(&renderedHeader)) {
        if (error) *error = QStringLiteral("Invalid conditions in gameworlds.ruleh.");
        return false;
    }
    const QList<QByteArray> bytes = {renderedHeader, generated};
    // Check BOTH destinations before writing EITHER: a user-owned .c must
    // not leave a newly updated .h behind on a failed publication.
    for (const QString &destination : dests) {
        QFile check(destination);
        if (check.exists() && (!check.open(QIODevice::ReadOnly)
             || !check.read(200).contains("GamerGirl Stage 5.2"))) {
            if (error) *error = QStringLiteral("Refusing to overwrite user-owned file: %1").arg(destination);
            return false;
        }
    }
    for (int i = 0; i < dests.size(); ++i) {
        QSaveFile out(dests.at(i));
        if (!out.open(QIODevice::WriteOnly) || out.write(bytes.at(i)) != bytes.at(i).size() || !out.commit()) {
            if (error) *error = QStringLiteral("Could not write generated multi-world runtime: %1").arg(dests.at(i));
            return false;
        }
    }
    const QString guide = QDir(root).filePath(QStringLiteral("gameworlds-guide.txt"));
    if (!QFileInfo::exists(guide)) {
        QFile templateGuide(templates.filePath(QStringLiteral("gameworlds.ruletxt")));
        if (!templateGuide.open(QIODevice::ReadOnly)) {
            if (error) *error = QStringLiteral("Missing SDK multi-world guide template.");
            return false;
        }
        QSaveFile output(guide);
        const QByteArray guideBytes = templateGuide.readAll();
        if (!output.open(QIODevice::WriteOnly)
            || output.write(guideBytes) != guideBytes.size() || !output.commit()) {
            if (error) *error = QStringLiteral("Could not install generated multi-world guide.");
            return false;
        }
    }
    return true;
}

inline bool publish(const QString &designPath, const QString &worldName,
                    bool hasMap, bool externalMap, bool hasSpline,
                    bool hasAdventure, bool embedPixels, const QString &rulesDirectory, QString *error)
{
    const QDir project(QFileInfo(designPath).absolutePath());
    const QString worldParent = project.filePath(QStringLiteral(".codergirl/worlds"));
    if (!QDir().mkpath(worldParent)) {
        if (error) *error = QStringLiteral("Cannot create world snapshot directory: %1").arg(worldParent);
        return false;
    }
    const QString suffix = QUuid::createUuid().toString(QUuid::WithoutBraces);
    const QString staging = QDir(worldParent).filePath(QStringLiteral(".staging-") + suffix);
    const QString destination = QDir(worldParent).filePath(worldName);
    const QString displaced = QDir(worldParent).filePath(QStringLiteral(".previous-") + suffix);
    if (!QDir().mkpath(staging)) {
        if (error) *error = QStringLiteral("Cannot create world snapshot staging directory.");
        return false;
    }
    auto abort = [&](const QString &message) {
        QDir(staging).removeRecursively();
        if (error) *error = message;
        return false;
    };

    QStringList files = {
        QStringLiteral("gameassets/gameassets.c"),
        QStringLiteral("gameassets/gameassets.h"),
        QStringLiteral("gamehelpers/gameworlditems.c"),
        QStringLiteral("gamehelpers/gameworlditems.h"),
        QStringLiteral("gamehelpers/gameworlditems.txt"),
        QStringLiteral("maingame.c.txt")
    };
    // No-story designs also generate a harmless rule-owned Adventure stub.
    files << QStringLiteral("gamehelpers/gameadventure.c")
          << QStringLiteral("gamehelpers/gameadventure.h");
    if (hasSpline)
        files << QStringLiteral("gamehelpers/splinepaths.c")
              << QStringLiteral("gamehelpers/splinepaths.h");
    if (hasMap) {
        const QString base = QStringLiteral("gamelevels/") + worldName;
        files << base + QStringLiteral(".c") << base + QStringLiteral(".h");
        if (externalMap) files << base + QStringLiteral(".map");
    }
    const QDir mapStaging(project.filePath(
        QStringLiteral(".codergirl/tilemap-staging/") + worldName));
    QJsonArray copied;
    for (const QString &relative : files) {
        const QString src = relative.startsWith(QStringLiteral("gamelevels/"))
            ? mapStaging.filePath(relative) : project.filePath(relative);
        if (!QFileInfo(src).isFile()) {
            // World-items stubs and a first-time starter may be absent in
            // legacy projects. Never accidentally archive another world's
            // old generated files to fill that gap.
            return abort(QStringLiteral("Missing generated world file: %1").arg(src));
        }
        const QString dst = QDir(staging).filePath(relative);
        if (!QDir().mkpath(QFileInfo(dst).absolutePath()) || !QFile::copy(src, dst))
            return abort(QStringLiteral("Could not snapshot world file: %1").arg(relative));
        copied.append(relative);
    }
    QJsonObject manifest;
    manifest.insert(QStringLiteral("format"), QStringLiteral("CODERGIRL-V1-WORLD-BUNDLE"));
    manifest.insert(QStringLiteral("version"), 2);
    manifest.insert(QStringLiteral("worldName"), worldName);
    manifest.insert(QStringLiteral("designFile"), QFileInfo(designPath).absoluteFilePath());
    manifest.insert(QStringLiteral("generatedAt"), QDateTime::currentDateTimeUtc().toString(Qt::ISODateWithMs));
    manifest.insert(QStringLiteral("externalMap"), externalMap);
    manifest.insert(QStringLiteral("embedPixels"), embedPixels);
    manifest.insert(QStringLiteral("hasAdventure"), hasAdventure);
    manifest.insert(QStringLiteral("hasSplines"), hasSpline);
    manifest.insert(QStringLiteral("files"), copied);
    {
        QSaveFile output(QDir(staging).filePath(QStringLiteral("world.json")));
        const QByteArray bytes = QJsonDocument(manifest).toJson(QJsonDocument::Indented);
        if (!output.open(QIODevice::WriteOnly) || output.write(bytes) != bytes.size() || !output.commit())
            return abort(QStringLiteral("Could not write world bundle manifest."));
    }
    // A previous world bundle remains intact until the replacement is ready.
    const bool hadPrevious = QDir(destination).exists();
    if (hadPrevious && !QDir().rename(destination, displaced))
        return abort(QStringLiteral("Could not preserve previous world bundle: %1").arg(worldName));
    if (!QDir().rename(staging, destination)) {
        if (hadPrevious) QDir().rename(displaced, destination);
        return abort(QStringLiteral("Could not publish world bundle: %1").arg(worldName));
    }
    if (hadPrevious) QDir(displaced).removeRecursively();

    // Stage 5.1: emit the *compilable* mirror AFTER the private archive has
    // been committed. Never expose a half-written world in Files in Project.
    if (!publishBuildTree(destination, project, worldName, files, hasMap, error))
        return false;

    // Only mark a world active once its entire generated bundle is committed.
    // QSaveFile ensures an interrupted update cannot leave partial JSON.
    const QString activePath = activeFile(designPath);
    QSaveFile active(activePath);
    manifest.remove(QStringLiteral("files"));
    manifest.insert(QStringLiteral("snapshotDirectory"),
                    QStringLiteral(".codergirl/worlds/") + worldName);
    const QByteArray activeBytes = QJsonDocument(manifest).toJson(QJsonDocument::Indented);
    if (!active.open(QIODevice::WriteOnly)
        || active.write(activeBytes) != activeBytes.size() || !active.commit()) {
        active.cancelWriting();
        if (error) *error = QStringLiteral("World bundle saved, but could not update active-world marker: %1").arg(activePath);
        return false;
    }
    // Update the shared registry after the committed world is active.
    if (!publishWorldRegistry(project, QDir(rulesDirectory), error))
        return false;
    QDir(mapStaging).removeRecursively();
    // Stage 5.11: gameworlditems, gameadventure and splinepaths are WORLD
    // modules, not project-wide helpers. Their canonical generation still
    // takes place in project/gamehelpers/ until the world bundle is built,
    // but no duplicate is needed afterwards. Remove ONLY exact copies of
    // published world files. Keep actual shared engine helpers untouched,
    // and preserve an edited root file which differs from every world.
    {
        const QDir rootHelpers(project.filePath(QStringLiteral("gamehelpers")));
        const QDir publishedWorlds(project.filePath(QStringLiteral("worlds")));
        const QStringList generatedNames = {
            QStringLiteral("gameworlditems.c"),
            QStringLiteral("gameworlditems.h"),
            QStringLiteral("gameworlditems.txt"),
            QStringLiteral("gameadventure.c"),
            QStringLiteral("gameadventure.h"),
            QStringLiteral("splinepaths.c"),
            QStringLiteral("splinepaths.h")
        };
        const QByteArray namespaceInclude = "#include \"../world_symbols.h\"\n";
        const QStringList names = publishedWorlds.entryList(
            QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        for (const QString &filename : generatedNames) {
            const QString rootFile = rootHelpers.filePath(filename);
            QFile original(rootFile);
            if (!original.open(QIODevice::ReadOnly)) continue;
            const QByteArray rootBytes = original.readAll();
            original.close();
            for (const QString &name : names) {
                if (name.startsWith(QLatin1Char('.'))) continue;
                const QDir world(publishedWorlds.filePath(name));
                if (!QFileInfo::exists(world.filePath(QStringLiteral("world-build.json"))))
                    continue;
                QFile published(world.filePath(QStringLiteral("gamehelpers/") + filename));
                if (!published.open(QIODevice::ReadOnly)) continue;
                QByteArray worldBytes = published.readAll();
                if (filename.endsWith(QStringLiteral(".c"))) {
                    // Namespaced world .c modules have precisely one added
                    // include at the beginning, inserted by publishBuildTree.
                    if (!worldBytes.startsWith(namespaceInclude)) continue;
                    worldBytes.remove(0, namespaceInclude.size());
                }
                if (rootBytes == worldBytes) {
                    QFile::remove(rootFile);
                    break;
                }
            }
        }
    }
    // Stage 5.12: gameassets.c/.h are generated for ONE world and already
    // published at worlds/<world>/gameassets/. Never keep a redundant root
    // export after successful publication. Compare bytes against ANY valid
    // published world before removing them, so regeneration of Forest does
    // not depend on which world was generated last. The buildable .c adds
    // exactly one namespace include; generated .h is unchanged.
    {
        const QDir rootAssets(project.filePath(QStringLiteral("gameassets")));
        const QDir publishedWorlds(project.filePath(QStringLiteral("worlds")));
        const QByteArray namespaceInclude = "#include \"../world_symbols.h\"\n";
        const QStringList names = publishedWorlds.entryList(
            QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name);
        for (const QString &filename : {QStringLiteral("gameassets.c"),
                                        QStringLiteral("gameassets.h")}) {
            const QString rootFile = rootAssets.filePath(filename);
            QFile original(rootFile);
            if (!original.open(QIODevice::ReadOnly)) continue;
            const QByteArray rootBytes = original.readAll();
            original.close();
            for (const QString &name : names) {
                if (name.startsWith(QLatin1Char('.'))) continue;
                const QDir world(publishedWorlds.filePath(name));
                if (!QFileInfo::exists(world.filePath(QStringLiteral("world-build.json"))))
                    continue;
                QFile published(world.filePath(QStringLiteral("gameassets/") + filename));
                if (!published.open(QIODevice::ReadOnly)) continue;
                QByteArray worldBytes = published.readAll();
                if (filename.endsWith(QStringLiteral(".c"))) {
                    if (!worldBytes.startsWith(namespaceInclude)) continue;
                    worldBytes.remove(0, namespaceInclude.size());
                }
                if (rootBytes == worldBytes) {
                    QFile::remove(rootFile);
                    break;
                }
            }
        }
        // Never delete unrelated files that users placed in gameassets/.
        project.rmdir(QStringLiteral("gameassets")); // Only when empty.
    }
    // Clean only recognisable legacy tilemap exports after successful
    // publication. Preserve non-generated files in a user's gamelevels/.
    {
        const QDir root(project.filePath(QStringLiteral("gamelevels")));
        if (root.exists()) {
            const QStringList designs = project.entryList(
                {QStringLiteral("*.sbgm")}, QDir::Files, QDir::Name);
            for (const QString &design : designs) {
                const QString name = sidboxTilemapWorldBaseName(project.filePath(design));
                const QString worldLevels = project.filePath(
                    QStringLiteral("worlds/") + name + QStringLiteral("/gamelevels/"));
                if (!QFileInfo::exists(QDir(worldLevels).filePath(name + QStringLiteral(".c")))
                    || !QFileInfo::exists(QDir(worldLevels).filePath(name + QStringLiteral(".h"))))
                    continue;
                for (const QString &ext : {QStringLiteral(".c"), QStringLiteral(".h"), QStringLiteral(".map")}) {
                    const QString legacy = root.filePath(name + ext);
                    QFile check(legacy);
                    if (!check.open(QIODevice::ReadOnly)) continue;
                    const QByteArray prefix = check.read(4096);
                    const bool generated = ext == QStringLiteral(".c")
                        ? prefix.startsWith(QByteArray("#include \"") + name.toUtf8() + QByteArray(".h\""))
                        : ext == QStringLiteral(".h")
                            ? prefix.contains("Generated from Tilemap Editor")
                            : prefix.startsWith("SBMP");
                    check.close();
                    if (generated) QFile::remove(legacy);
                }
            }
            project.rmdir(QStringLiteral("gamelevels")); // Succeeds only if empty.
        }
    }
    return true;
}

} // namespace GameWorldSnapshot
#endif

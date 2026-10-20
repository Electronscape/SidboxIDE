// Stage 3.69: split from gamedesigner.cpp. Method bodies are unchanged.
#include "gamedesigner.h"
#include "ppbcodec.h"
#include "pngpaletteimport.h"
#include "gamepalette.h"
#include "gamepaletteeditor.h"
#include "gamecodegen.h"
#include "gameanimationeditor.h"
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
    // A reward is a real Collectable resource, referenced by stable ID.
    // Keep one owner per dormant pickup to avoid duplicate spawning.
    QHash<QString, int> breakRewardOwner;
    for (int i = 0; i < nw; ++i) {
        const Resource &block = *platforms.at(i);
        if (block.objectType != QStringLiteral("breakable") ||
            block.breakDropCollectableId.isEmpty()) continue;
        const QString id = block.breakDropCollectableId;
        int rewardIndex = -1;
        for (int j = 0; j < np; ++j)
            if (pickups.at(j)->id == id) { rewardIndex = j; break; }
        if (rewardIndex < 0) {
            if (error) *error = tr("Breakable '%1' targets a missing collectable. Reassign its reward.")
                .arg(block.name);
            return false;
        }
        if (!m_tilemapEnabled || pickupPaths.at(rewardIndex) >= 0) {
            if (error) *error = tr("Breakable '%1' needs an enabled tilemap and a reward "
                                   "collectable without a movement spline.").arg(block.name);
            return false;
        }
        if (breakRewardOwner.contains(id)) {
            if (error) *error = tr("Two breakables try to spawn the same reward '%1'. "
                                   "Use a different collectable for each block.")
                                   .arg(pickups.at(rewardIndex)->name);
            return false;
        }
        breakRewardOwner.insert(id, i);
    }
    QSet<int> droppingPickups;
    for (auto it = breakRewardOwner.constBegin(); it != breakRewardOwner.constEnd(); ++it)
        for (int j = 0; j < np; ++j)
            if (pickups.at(j)->id == it.key()) droppingPickups.insert(j);
    const bool hasBreakRewards = !droppingPickups.isEmpty();
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
        } else if (obj->objectType == QStringLiteral("breakable")) {
            for (const QString &id : {obj->sfxBreakHit, obj->sfxBreakBounce,
                                      obj->sfxBreakFinish})
                if (!id.isEmpty()) usedSfx.insert(id);
        } else if (obj->objectType == QStringLiteral("hazard")) {
            for (const QString &id : {obj->sfxHazardHit, obj->sfxHazardBounce,
                                      obj->sfxHazardAmbient})
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
         "void gameworlditems_draw(int32_t camera_x, int32_t camera_y);\n"
         "void gameworlditems_draw_behind(int32_t camera_x, int32_t camera_y);\n";
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
    if (hasBreakRewards) {
        C << "/* Per-reward falling state; world position uses hundredths of a pixel. */\n"
             "static uint8_t cg_reward_falling[" << np << "];\n"
             "static int32_t cg_reward_x100[" << np << "];\n"
             "static int32_t cg_reward_y100[" << np << "];\n"
             "static int32_t cg_reward_vx100[" << np << "];\n"
             "static int32_t cg_reward_vy100[" << np << "];\n";
    }
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
    if (hasBreakRewards) {
        C << "    for (uint16_t i = 0; i < " << np
          << "; ++i) { cg_reward_falling[i] = 0; cg_reward_x100[i] = 0; cg_reward_y100[i] = 0; "
             "cg_reward_vx100[i] = 0; cg_reward_vy100[i] = 0; }\n";
    }
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
              << "    pickups[" << ix << "].active = " << (droppingPickups.contains(ix) ? "0" :
                    (r.objectInitiallyActive ? "1" : "0")) << ";\n"
              << "    pickups[" << ix << "].draw_behind_tiles = " << (r.drawBehindTiles ? "1" : "0") << ";\n";
        } else {
            const QString kind = r.objectType == QStringLiteral("lift") ? QStringLiteral("GAME_OBJECT_LIFT") :
                r.objectType == QStringLiteral("conveyor") ? QStringLiteral("GAME_OBJECT_CONVEYOR") :
                r.objectType == QStringLiteral("trigger") ? QStringLiteral("GAME_OBJECT_TRIGGER") :
                r.objectType == QStringLiteral("door") ? QStringLiteral("GAME_OBJECT_DOOR") :
                r.objectType == QStringLiteral("deathzone") ? QStringLiteral("GAME_OBJECT_DEATH_ZONE") :
                r.objectType == QStringLiteral("breakable") ? QStringLiteral("GAME_OBJECT_BREAKABLE") :
                r.objectType == QStringLiteral("hazard") ? QStringLiteral("GAME_OBJECT_HAZARD") :
                QStringLiteral("GAME_OBJECT_SPRING");
            C << "    if (!game_world_object_start(" << target << ", " << kind << ", "
              << sprite << ", " << r.x << ", " << r.y << ", "
              << r.hitWidth << ", " << r.hitHeight << ")) return 0;\n";
            C << "    platforms[" << ix << "].active = " << (r.objectInitiallyActive ? "1" : "0") << ";\n"
              << "    platforms[" << ix << "].draw_behind_tiles = " << (r.drawBehindTiles ? "1" : "0") << ";\n";
            if (r.objectType == QStringLiteral("trigger")) {
                C << "    platforms[" << ix << "].trigger_press = " << (r.triggerPress ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].trigger_one_shot = " << (r.triggerOneShot ? "1" : "0") << ";\n";
            }
            if (r.objectType == QStringLiteral("conveyor"))
                C << "    platforms[" << ix << "].conveyor_speed = " << r.conveyorSpeed << ";\n";
            if (r.objectType == QStringLiteral("breakable")) {
                C << "    platforms[" << ix << "].break_hits_required = " << r.breakHits << ";\n";
                C << "    platforms[" << ix << "].break_touch_mode = "
                  << (r.breakTouch && !r.breakFromBelow ? "1" : "0") << ";\n";
                C << "    platforms[" << ix << "].break_bounce = " << (r.breakBounce ? "1" : "0") << ";\n";
                C << "    platforms[" << ix << "].break_from_below = "
                  << (r.breakFromBelow ? "1" : "0") << ";\n";
                C << "    platforms[" << ix << "].break_strength = " << r.breakStrength << ";\n";
                C << "    platforms[" << ix << "].break_launch_x = " << r.breakLaunchX << ";\n";
            }
            if (r.objectType == QStringLiteral("hazard")) {
                C << "    platforms[" << ix << "].hazard_damage = " << r.hazardDamage << ";\n"
                  << "    platforms[" << ix << "].hazard_kick = " << (r.hazardKick ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].hazard_kick_x = " << r.hazardKickX << ";\n"
                  << "    platforms[" << ix << "].hazard_kick_y = " << r.hazardKickY << ";\n"
                  << "    platforms[" << ix << "].hazard_hurt_animation = " << (r.hazardHurtAnimation ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].hazard_flash = " << (r.hazardFlash ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].hazard_flash_colour = " << r.hazardFlashColour << ";\n"
                  << "    platforms[" << ix << "].hazard_flash_count = " << r.hazardFlashCount << ";\n"
                  << "    platforms[" << ix << "].hazard_flash_frames = " << r.hazardFlashFrames << ";\n";
            }
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
        // Flip belongs to this sprite BOB, not to collision or spline coordinates.
        // Keep unrelated runtime flags intact. Generic animations only change index.
        if (r.objectFlipX || r.objectFlipY) {
            C << "    " << bob << ".flags = (uint8_t)((" << bob
              << ".flags & ~(BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y)) | "
              << (r.objectFlipX ? "BLIT_FLAG_FLIP_X" : "0") << " | "
              << (r.objectFlipY ? "BLIT_FLAG_FLIP_Y" : "0") << ");\n";
        }
        if (path >= 0) {
            const QString sym = splineSymbol(path);
            const QString var = QStringLiteral("%1_path_%2").arg(collect ? QStringLiteral("pickup") : QStringLiteral("platform")).arg(ix);
            C << "    start_spline(&" << var << ", " << sprite << ", "
              << sym << "_path, " << sym << "_count, " << sym << "_frames, " << sym << "_loop);\n"
              << "    set_spline_pos(&" << var << ", " << r.x << ", " << r.y << ");\n"
              << "    " << (collect ? "pickups" : "platforms") << "[" << ix << "].spline = &" << var << ";\n"
              << "    " << (collect ? "pickups" : "platforms") << "[" << ix
              << "].spline_start_delay = " << qBound(0, r.objectSplineStartDelay, 65535) << ";\n";
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
            if ((r.objectType == QStringLiteral("conveyor") && !r.sfxAmbient.isEmpty()) ||
                (r.objectType == QStringLiteral("hazard") && !r.sfxHazardAmbient.isEmpty())) {
                const QString ambientId = r.objectType == QStringLiteral("hazard")
                    ? r.sfxHazardAmbient : r.sfxAmbient;
                C << "    if (platforms[" << i << "].active) {\n"
                  << "        " << cSfxCall(ambientId, QStringLiteral("platforms[%1].x").arg(i), r.audioRadius);
                C << "        sound_setvolume(" << soundById.value(ambientId)->audio.channel << ", 0);\n";
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
    if (hasBreakRewards) {
        C << R"REWARD(
    /* Prize launch: optional X/Y impulse, then gravity. Sweep each axis
       pixel-by-pixel so thin tile walls, ceilings and floors are respected.
       A reward cannot be collected until it lands on solid ground. */
    for (uint16_t i = 0; i < GAMEWORLDITEMS_PICKUP_COUNT; ++i) {
        if (!cg_reward_falling[i]) continue;
        for (uint16_t tick = 0; tick < frames; ++tick) {
            int32_t x = pickups[i].x;
            int32_t y = pickups[i].y;
            int32_t next_x100 = cg_reward_x100[i] + cg_reward_vx100[i];
            int32_t next_y100;
            int32_t vx = cg_reward_vx100[i];
            int32_t vy = cg_reward_vy100[i] + 65; /* gravity 0.65px/frame² */
            if (vy > 900) vy = 900;
            cg_reward_vy100[i] = vy;
            next_y100 = cg_reward_y100[i] + vy;
            /* Horizontal sweep. Walls stop horizontal speed, not gravity. */
            int32_t target_x = next_x100 / 100;
            while (x != target_x) {
                int32_t step = target_x > x ? 1 : -1;
                if (game_tilemap_actor_blocked(&game_level1, x + step, y,
                        pickups[i].width, pickups[i].height)) {
                    vx = 0;
                    next_x100 = x * 100;
                    break;
                }
                x += step;
            }
            /* A gentle horizontal slowdown leaves the launch visible
               without letting prizes drift forever across the level. */
            cg_reward_vx100[i] = (vx * 97) / 100;
            if (cg_reward_vx100[i] > -5 && cg_reward_vx100[i] < 5)
                cg_reward_vx100[i] = 0;
            cg_reward_x100[i] = next_x100;
            int32_t target_y = next_y100 / 100;
            uint8_t landed = 0;
            while (y != target_y) {
                int32_t step = target_y > y ? 1 : -1;
                if (game_tilemap_actor_blocked(&game_level1, x, y + step,
                        pickups[i].width, pickups[i].height)) {
                    if (step > 0) landed = 1;
                    cg_reward_vy100[i] = 0;
                    next_y100 = y * 100;
                    break;
                }
                y += step;
            }
            cg_reward_y100[i] = next_y100;
            game_collectable_set_position(&pickups[i], x, y);
            if (landed || (cg_reward_vy100[i] >= 0 &&
                    game_tilemap_actor_blocked(&game_level1, x, y + 1,
                        pickups[i].width, pickups[i].height))) {
                cg_reward_falling[i] = 0;
                cg_reward_vx100[i] = 0;
                cg_reward_vy100[i] = 0;
                pickups[i].can_collect = 1;
                break;
            }
        }
    }
)REWARD";
    }
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
            if ((r.objectType == QStringLiteral("conveyor") && !r.sfxAmbient.isEmpty()) ||
                (r.objectType == QStringLiteral("hazard") && !r.sfxHazardAmbient.isEmpty())) {
                const QString ambientId = r.objectType == QStringLiteral("hazard")
                    ? r.sfxHazardAmbient : r.sfxAmbient;
                C << "    if (platforms[" << i << "].active && !cg_loop_playing[" << i << "]) {\n"
                  << "        " << cSfxCall(ambientId, QStringLiteral("platforms[%1].x").arg(i), r.audioRadius)
                  << "        sound_setvolume(" << soundById.value(ambientId)->audio.channel << ", 0);\n"
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
        C << "    game_world_objects_after(platforms, " << nw << ", player);\n"
             "    game_world_objects_hazards(platforms, " << nw << ", player);\n";
        if (hasBreakRewards) {
            for (int i = 0; i < nw; ++i) {
                const Resource &block = *platforms.at(i);
                if (block.objectType != QStringLiteral("breakable") ||
                    block.breakDropCollectableId.isEmpty()) continue;
                int j = -1;
                for (int k = 0; k < np; ++k)
                    if (pickups.at(k)->id == block.breakDropCollectableId) { j = k; break; }
                if (j < 0) continue; // already validated above
                C << "    if (platforms[" << i << "].break_triggered) {\n"
                  << "        pickups[" << j << "].active = 1;\n"
                  << "        pickups[" << j << "].can_collect = 0;\n"
                  << "        pickups[" << j << "].respawn_left = 0;\n"
                  << "        game_collectable_set_position(&pickups[" << j << "], "
                  << "platforms[" << i << "].x + (platforms[" << i
                  << "].width - pickups[" << j << "].width) / 2, platforms[" << i << "].y);\n"
                  << "        cg_reward_x100[" << j << "] = pickups[" << j << "].x * 100;\n"
                  << "        cg_reward_y100[" << j << "] = pickups[" << j << "].y * 100;\n"
                  << "        cg_reward_vx100[" << j << "] = "
                  << (block.breakRewardImpulse ? block.breakRewardVx * 100 : 0) << ";\n"
                  << "        cg_reward_vy100[" << j << "] = "
                  << (block.breakRewardImpulse ? block.breakRewardVy * 100 : 0) << ";\n"
                  << "        cg_reward_falling[" << j << "] = 1;\n"
                  << "    }\n";
            }
        }
        if (m_tilemapEnabled) {
            C << "    /* Hazard Zone: ENTERED once, INSIDE each frame, EXITED on leaving. */\n"
                 "    uint8_t in_hazard_zone = (uint8_t)(player && player->x100 && player->y100 &&\n"
                 "        player->width && player->height &&\n"
                 "        game_world_objects_death_zone(platforms, " << nw
              << ", *player->x100 / 100 + player->offset_x, *player->y100 / 100 + player->offset_y, player->width, player->height));\n"
                 "    uint8_t was_in_hazard_zone = cg_hazard_zone_contact;\n"
                 "    cg_hazard_zone_contact = in_hazard_zone;\n"
                 "    if (player && player->x100 && player->y100) {\n"
                 "        if (in_hazard_zone && !was_in_hazard_zone)\n"
                 "            game_hazard_notify(GAME_HAZARD_ZONE_ENTERED, *player->x100 / 100 + player->offset_x, *player->y100 / 100 + player->offset_y);\n"
                 "        else if (in_hazard_zone)\n"
                 "            game_hazard_notify(GAME_HAZARD_ZONE_INSIDE, *player->x100 / 100 + player->offset_x, *player->y100 / 100 + player->offset_y);\n"
                 "        else if (was_in_hazard_zone)\n"
                 "            game_hazard_notify(GAME_HAZARD_ZONE_EXITED, *player->x100 / 100 + player->offset_x, *player->y100 / 100 + player->offset_y);\n"
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
            if (r.objectType == QStringLiteral("hazard")) {
                const QString pos = QStringLiteral("platforms[%1].x").arg(i);
                if (!r.sfxHazardHit.isEmpty())
                    C << "    if (platforms[" << i << "].hazard_hit_triggered) "
                      << cSfxCall(r.sfxHazardHit, pos, r.audioRadius);
                if (!r.sfxHazardBounce.isEmpty())
                    C << "    if (platforms[" << i << "].hazard_bounce_triggered) "
                      << cSfxCall(r.sfxHazardBounce, pos, r.audioRadius);
            }
            if (r.objectType == QStringLiteral("breakable")) {
                const QString pos = QStringLiteral("platforms[%1].x").arg(i);
                if (!r.sfxBreakHit.isEmpty())
                    C << "    if (platforms[" << i << "].break_hit_triggered) "
                      << cSfxCall(r.sfxBreakHit, pos, r.audioRadius);
                if (!r.sfxBreakBounce.isEmpty())
                    C << "    if (platforms[" << i << "].break_bounce_triggered) "
                      << cSfxCall(r.sfxBreakBounce, pos, r.audioRadius);
                if (!r.sfxBreakFinish.isEmpty())
                    C << "    if (platforms[" << i << "].break_triggered) "
                      << cSfxCall(r.sfxBreakFinish, pos, r.audioRadius);
            }
        }
        if (nt) C << "    if (player && player->x100 && player->y100 && player->width && player->height)\n"
                    "        gameworlditems_trigger(*player->x100 / 100 + player->offset_x, *player->y100 / 100 + player->offset_y,\n"
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
    C << "void gameworlditems_draw_behind(int32_t camera_x, int32_t camera_y)\n{\n";
    if (nw) C << "    game_world_objects_draw_layer(platforms, " << nw << ", camera_x, camera_y, 1);\n";
    if (np) C << "    game_collectables_draw_layer(pickups, " << np << ", camera_x, camera_y, 1);\n";
    C << "}\n\n";
    C << "void gameworlditems_draw(int32_t camera_x, int32_t camera_y)\n{\n";
    if (nw) C << "    game_world_objects_draw_layer(platforms, " << nw << ", camera_x, camera_y, 0);\n";
    if (np) C << "    game_collectables_draw_layer(pickups, " << np << ", camera_x, camera_y, 0);\n";
    if (!usedSfx.isEmpty()) {
        C << "    cg_audio_camera_x = camera_x;\n";
        for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            const QString soundId = r.objectType == QStringLiteral("conveyor")
                ? r.sfxAmbient : r.objectType == QStringLiteral("hazard")
                ? r.sfxHazardAmbient : r.objectType == QStringLiteral("lift") ? r.sfxMove : QString();
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
                 "  // Also REQUIRED for intentional-jump-only Breakable stomps.\n"
                 "  world_player.coyote = &player_physics.coyote;\n"
                 "  world_player.jump_speed = &player_physics.jump_speed;\n"
                 "  world_player.spring_force_vx100 = &player_physics.force_vx100;\n"
                 "  // Slidy spring kickback now respects the current physics preset.\n"
                 "  // Existing OWNER: user main.c needs this one-time binding!\n"
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
    if (hasBreakRewards) G <<
        "\nBREAKABLE HEAD-BUTT REWARDS\n"
        "A block with 'Break from below' takes deliberate upward head-butt hits\n"
        "rather than jumping on its top. The usual 1-4 hit counter applies.\n"
        "The configured reward is a normal Collectable sprite, automatically\n"
        "hidden at game start, activated at the broken block's position,\n"
        "then dropped with gravity until it reaches a solid tile.\n"
        "It cannot be picked up during the fall. After landing, the ordinary\n"
        "on_pickup() callback, sound, value and respawn settings still apply.\n"
        "No extra calls are needed in user-owned main.c if it already calls\n"
        "gameworlditems_update(), gameworlditems_after(), and check().\n\n";
    G << "Optional Draw behind tiles: the generated starter calls\n"
         "gameworlditems_draw_behind() BEFORE drawing the foreground map,\n"
         "then gameworlditems_draw() AFTER it. Never draw the same sprite twice.\n"
         "Hazard/Murder objects are non-solid moving sensors: a contact sets\n"
         "world_player.hurt_triggered and hurt_damage_this_frame once.\n"
         "YOUR game subtracts health. Default starter has an example.\n"
         "The visual blink uses BLIT_FLAG_SOLIDCOLOUR with a foreground\n"
         "palette index; Hurt animation is opt-in per hazard.\n";
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
    // Stage 3.64: only show the player-animation integration when this
    // actual player resource has a saved .sbanim sidecar. Generated main.c
    // remains complete and buildable even before the C header is exported.
    const bool hasPlayerAnimation = hasPhysics && !player->animationFile.isEmpty();
    const bool hasMurderObjects = hasPhysics && std::any_of(m_resources.cbegin(), m_resources.cend(),
        [](const Resource &r) { return r.kind == QStringLiteral("sprite") &&
                                      r.objectType == QStringLiteral("hazard"); });
    QString program;
    QTextStream out(&program);
    out << R"CG(/*
 * SIDBOX IDE / GamerGirl - GENERATED V1 GAME STARTER (Stage 3.64)
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
    if (hasPlayerAnimation)
        out << " * Player animation: " << player->animationFile << " (editor metadata)\n"
               " * V1 C export: gameanimations/player_anim.h (prompted on Save Animations)\n";
    if (hasMap && (m_tilemap.collisions.contains(char(7)) || !m_tilemap.collisionPlacements.isEmpty()))
        out << " * Custom collision surfaces are handled automatically by game_tile_player_run().\n"
               " * Point-defined stamps use shared definitions and whole placements (SBMP v4).\n"
               " * Legacy Stage 3.35 painted slopes remain available as SBMP v3 data.\n"
               " * Update gametilemap.c/.h to the new shape-aware helpers before building.\n";
    if (hasMap && !m_tilemap.loops.isEmpty())
        out << " * Loop tracks: " << m_tilemap.loops.size() << " circular tracks.\n"
               " * These are generated into level1.c even for SD .map projects.\n"
               " * Approach the bottom yellow marker fast enough in either direction.\n"
               " * game_tile_player_run() handles attachment, gravity and release.\n"
               " * game_tile_player_on_loop(&player_physics) tests attachment.\n"
               " * IMPORTANT: track travel guides player movement, it doesn't rotate\n"
               " * the sprite. For freeform/full pinball physics use custom C.\n";
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
    if (hasPlayerAnimation) {
        out << R"CG(
/* PLAYER ANIMATION -- ONE-SWITCH SETUP (Stage 3.64)
 * ------------------------------------------------
 * 1. Game Designer > Sprite named player > Player Animations...
 *    Define frames for Idle / Walk / Jump / Fall (facing Right).
 *    Tick Mirror Left from Right. Save Animations and save Game Design.
 * 2. Click Save Animations, then YES when asked to create or update
 *    gameanimations/player_anim.h. No manual export is necessary.
 *    The header uses the player_anim C symbol prefix automatically.
 *    Saving animation edits can update the header again on request.
 * 3. Set GAMERGIRL_PLAYER_ANIMATIONS to 1 below and rebuild the V1 game.
 *    The starter selects Idle, Walk, Jump, Fall and X-flips for left.
 *    Animation is selected AFTER moving-platform/spring collision resolution.
 *    BOB frame indexing is 0..255 and requires the same atlas cell size.
 *    Use an indexed PPB atlas with palette index 0 transparent on SIDBOX.
 *
 * This starter animation is OPTIONAL: with the switch set to 0 it works
 * without the exported header. If you rename/delete the four basic states,
 * adjust the matching PLAYER_ANIM_STATE_* names below to match the export.
 * Push/Run/Hurt/Slide and custom states can be chosen from YOUR game logic.
 * No .sbanim is loaded by the runtime: it is editor metadata ONLY.
 * IMPORTANT: Existing USER-OWNED main.c is NEVER replaced by Update Project.
 * To use this code in a user-owned main.c, copy the animation sections from
 * the newly regenerated maingame.c.txt into your game source deliberately.
 */
#define GAMERGIRL_PLAYER_ANIMATIONS 0  /* Change to 1 after saving the .h */
#if GAMERGIRL_PLAYER_ANIMATIONS
#include "gameanimations/player_anim.h"
static player_anim_playeranim_t player_anim = {0};
static uint8_t player_anim_facing = PLAYER_ANIM_DIR_RIGHT;
#endif
)CG";
    }
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
/* COLLECTABLES — WHAT THIS CODE DOES
 * ----------------------------------
 * The Game Designer places collectables, but YOU decide what picking one up
 * means (points, keys, health, ammunition, opening doors, playing sounds...).
 *
 * on_pickup() is called by gameworlditems_check() when the player's
 * collision box touches an ACTIVE collectable. You do not call on_pickup()
 * directly. 'item' tells you WHICH collectable was picked up; item->value
 * is the value you entered in Game Object Properties.
 *
 * 'user' carries your own game state into the callback. Below we pass
 * &score, the ADDRESS of our score variable. The cast turns that generic
 * pointer back into a uint32_t pointer so we can add points to it.
 * The NULL checks guard against accidental invalid arguments.
 *
 * This is only a STARTER EXAMPLE. Change the body to handle different
 * pickup types (e.g. keys or health); don't assume every pickup is score.
 * The helper handles marking ordinary pickups collected/respawning as
 * configured; the callback is where YOUR game reacts to each pickup.
 */
static uint32_t score = 0;
static void on_pickup(game_collectable_t *item, void *user)
{
    uint32_t *points = (uint32_t *)user;
    if (!item || !points) return;
    *points += item->value;  /* Replace with your own key/health/score rules. */
}
)CG";
    }
    if (hasMurderObjects) out << R"CG(
/* The Game Designer's Hazard/Murder Objects fire ONE damage event per impact.
 * This is YOUR game's health rule; change the starting HP or replace this code.
 * Hit/bounce sounds and BOB flashing are managed automatically by helpers. */
static uint32_t player_health = 3;
)CG";
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
 *   Spline start delay in Game Object Properties freezes the path at its
 *   starting position for N game frames (50 frames = one second). It only
 *   delays spline movement, not sprite animation or collision checking.
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
        if (hasPlayerAnimation) out << R"CG(
#if GAMERGIRL_PLAYER_ANIMATIONS
    /* Stage 3.68: the animation editor's hitbox drives physical contact.
       Without enabled player animations, the original full BOB size is used.
       Offsets are relative to the visible sprite, not its world coordinates. */
    if (!game_tile_player_set_hitbox(&player_physics,
            PLAYER_ANIM_HITBOX_X, PLAYER_ANIM_HITBOX_Y,
            PLAYER_ANIM_HITBOX_W, PLAYER_ANIM_HITBOX_H)) {
        result = 4; goto cleanup; /* Invalid/out-of-sprite hitbox. */
    }
#endif
)CG";
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
    /* Slidy springs use the same external momentum as apply_force(),
       including current ICE/WATER/SPACE drag. */
    world_player.spring_force_vx100 = &player_physics.force_vx100;
    world_player.on_ground = &player_physics.on_ground;
    world_player.jump_held = &player_physics.jump_held;
    world_player.coyote = &player_physics.coyote;
    world_player.jump_speed = &player_physics.jump_speed;
)CG";
            out << "    world_player.width = player_physics.hitbox_w ? player_physics.hitbox_w : " << playerName << ".width;\n"
                << "    world_player.height = player_physics.hitbox_h ? player_physics.hitbox_h : " << playerName << ".height;\n"
                   "    world_player.offset_x = player_physics.hitbox_x;\n"
                   "    world_player.offset_y = player_physics.hitbox_y;\n";
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
        if (hasPlayerAnimation) {
            out << R"CG(        const uint8_t player_buttons = getjoyport();
        game_tile_player_run(&player_physics, player_buttons, 1);
)CG";
        } else {
            out << "        game_tile_player_run(&player_physics, getjoyport(), 1);\n";
        }
        /* Moving platforms, conveyors and springs resolve AFTER tile physics.
           Their final on_ground/vy100 are the values animation must see.
           Keep this ahead of animation selection, even for an idle rider. */
        if (worldObjects) out << "        gameworlditems_after(&world_player);\n";
        if (hasMurderObjects) out << R"CG(        /* Once per accepted spike/hazard hit; invulnerability prevents
           repeated damage while flashing. You own game-over/health rules. */
        if (world_player.hurt_triggered) {
            if (player_health > world_player.hurt_damage_this_frame)
                player_health -= world_player.hurt_damage_this_frame;
            else player_health = 0;
            /* TODO: if player_health == 0, run your death/respawn logic. */
        }
)CG";
        if (hasPlayerAnimation) {
            out << R"CG(#if GAMERGIRL_PLAYER_ANIMATIONS
        /* Stage 3.81: select animation AFTER world-object contacts resolve.
         * A carried rider should use Idle, not Fall; a player walking along
         * the platform should use Walk. Springs can launch Jump immediately.
         * Only change facing while pressing LEFT/RIGHT; idle retains facing.
         * If you use game_tile_player_step(), keep animation AFTER both the
         * tile-player step and gameworlditems_after(). */
        if (player_buttons & BTN_LEFT)  player_anim_facing = PLAYER_ANIM_DIR_LEFT;
        if (player_buttons & BTN_RIGHT) player_anim_facing = PLAYER_ANIM_DIR_RIGHT;
        uint8_t player_anim_state = PLAYER_ANIM_STATE_IDLE;
        if (!player_physics.on_ground) {
            player_anim_state = (player_physics.vy100 < 0)
                              ? PLAYER_ANIM_STATE_JUMP : PLAYER_ANIM_STATE_FALL;
        } else if (player_buttons & (BTN_LEFT | BTN_RIGHT)) {
            player_anim_state = PLAYER_ANIM_STATE_WALK;
        }
)CG";
            if (hasMurderObjects) out << R"CG(#if defined(PLAYER_ANIM_HAS_HURT_STATE) && PLAYER_ANIM_HAS_HURT_STATE
        /* Hazard "Use player Hurt animation" overrides Jump/Fall while
         * the player's damage grace period is active. The animation-header
         * exporter defines HAS_HURT_STATE when a Hurt state actually exists.
         * Without a Hurt state, normal animation selection is preserved.
         * For an existing hand-owned main.c, copy this block there too. */
        if (world_player.hurt_anim_active && world_player.hurt_ticks_remaining)
            player_anim_state = PLAYER_ANIM_STATE_HURT;
#endif
)CG";
            out << "        player_anim_step(&player_anim, &" << playerName
                << ", player_anim_state, player_anim_facing, 1);\n";
            out << "#endif\n";
        }
        if (pickups) {
            out << R"CG(        /* COLLECTABLE PICKUP CHECK — leave this AFTER player movement.
         * Run it ONCE each frame. It compares the live player's WORLD
         * collision rectangle against the Game Designer's collectables.
         * x100/y100 are hundredths of a pixel, hence the / 100; hitbox_x/y
         * shift the rectangle inside the player image. The fallback width
         * and height use the sprite size if no custom hitbox was defined.
         *
         * on_pickup is the callback above; &score is the user-data pointer
         * passed to it. Replace both if your game uses different state.
         * The helper decides WHICH object was touched; your callback
         * decides WHAT collecting it does. No pickup = no callback.
         */
)CG";
            out << "        gameworlditems_check(player_physics.x100 / 100 + player_physics.hitbox_x,\n"
                   "            player_physics.y100 / 100 + player_physics.hitbox_y, "
                   "player_physics.hitbox_w ? player_physics.hitbox_w : " << playerName << ".width,\n"
                << "            player_physics.hitbox_h ? player_physics.hitbox_h : " << playerName << ".height, on_pickup, &score);\n";
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
    if (hasObjects) out << R"CG(        /* GAME OBJECTS BEHIND THE TILEMAP — WHY DRAW THEM HERE?
         * Each placed Game Object has an optional "Draw behind tilemap"
         * setting. This call draws ONLY objects with that setting enabled.
         * We draw them BEFORE the tilemap so the floor/walls can cover them:
         * for example, spikes can rise gradually from behind a floor tile.
         * Objects drawn in front are handled later by gameworlditems_draw().
         *
         * camera_x and camera_y are the camera's WORLD position. The helper
         * subtracts them so moving objects appear in the right screen spot.
         * This is VISUAL layering only: collision and damage still work.
         * Keep this call BEFORE game_tilemap_blit_view_cleared(), or the
         * tilemap won't be able to hide the parts of an object behind it.
         */
        gameworlditems_draw_behind(camera_x, camera_y);
)CG";
    if (hasMap) {
        for (const Resource &r : m_resources) {
            if (r.kind != QStringLiteral("sprite") || r.path.isEmpty() ||
                r.objectType != QStringLiteral("decoration") || &r == player ||
                r.plane == QStringLiteral("background") || !r.drawBehindTiles) continue;
            const QString bob = spriteSymbol(r);
            if (r.objectFlipX || r.objectFlipY)
                out << "        " << bob << ".flags = (uint8_t)((" << bob
                    << ".flags & ~(BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y)) | "
                    << (r.objectFlipX ? "BLIT_FLAG_FLIP_X" : "0") << " | "
                    << (r.objectFlipY ? "BLIT_FLAG_FLIP_Y" : "0") << ");\n";
            out << "        " << bob << ".drawx = " << r.x << " - camera_x;\n"
                << "        " << bob << ".drawy = " << r.y << " - camera_y;\n"
                << "        gfx_drawbob(&" << bob << ");\n";
        }
    }
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
                r.plane == QStringLiteral("background") || r.drawBehindTiles) continue;
            const QString bob = spriteSymbol(r);
            if (r.objectFlipX || r.objectFlipY)
                out << "        " << bob << ".flags = (uint8_t)((" << bob
                    << ".flags & ~(BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y)) | "
                    << (r.objectFlipX ? "BLIT_FLAG_FLIP_X" : "0") << " | "
                    << (r.objectFlipY ? "BLIT_FLAG_FLIP_Y" : "0") << ");\n";
            out << "        " << bob << ".drawx = " << r.x << " - camera_x;\n"
                << "        " << bob << ".drawy = " << r.y << " - camera_y;\n"
                << "        gfx_drawbob(&" << bob << ");\n";
        }
        out << "        game_tile_player_screen(&player_physics, camera_x, camera_y);\n";
        if (hasMurderObjects) {
            out << R"CG(        /* PLAYER HURT FLASH — WHY MAKE A COPY OF THE SPRITE?
         * A Hazard / Murder Object can make the player flash after a hit.
         * The world_player helper knows the selected flash palette colour,
         * how many flashes to show, and how many frames each one lasts.
         *
         * We copy the original gfxbob_t into player_visible for drawing
         * THIS frame only. That means the solid-colour flag does not stick
         * on the real player sprite after flashing ends, and your regular
         * animation continues working normally.
         *
         * game_world_player_hurt_flash() returns true only during the ON
         * parts of the flashing sequence. It puts the chosen foreground
         * palette INDEX in flash_colour (not a 24-bit RGB colour).
         * BLIT_FLAG_SOLIDCOLOUR tells SIDBOX to draw the BOB in a solid
         * palette colour; flagval[BLIT_FLAG_TYPE_TINT_VALUE] picks which one.
         * When the helper returns false, draw the ordinary sprite instead.
         * gfx_drawbob() happens ONCE per frame in either case.
         *
         * Change the flash colour, count or timing in the Hazard object's
         * properties in Game Designer; regenerate the project to update it.
         */
        {
)CG";
            out << "            gfxbob_t player_visible = " << playerName << ";\n"
                   "            uint8_t flash_colour = 0;\n"
                   "            if (game_world_player_hurt_flash(&world_player, &flash_colour)) {\n"
                   "                player_visible.flags |= BLIT_FLAG_SOLIDCOLOUR;\n"
                   "                player_visible.flagval[BLIT_FLAG_TYPE_TINT_VALUE] = flash_colour;\n"
                   "            }\n"
                   "            gfx_drawbob(&player_visible);\n"
                   "        }\n";
        } else out << "        gfx_drawbob(&" << playerName << ");\n";
    } else if (hasMap) {
        /* A tile-only world still needs the chosen foreground draw order. */
        for (const Resource &r : m_resources) {
            if (r.kind != QStringLiteral("sprite") || r.path.isEmpty() ||
                r.objectType != QStringLiteral("decoration") ||
                r.plane == QStringLiteral("background") || r.drawBehindTiles) continue;
            const QString bob = spriteSymbol(r);
            if (r.objectFlipX || r.objectFlipY)
                out << "        " << bob << ".flags = (uint8_t)((" << bob
                    << ".flags & ~(BLIT_FLAG_FLIP_X | BLIT_FLAG_FLIP_Y)) | "
                    << (r.objectFlipX ? "BLIT_FLAG_FLIP_X" : "0") << " | "
                    << (r.objectFlipY ? "BLIT_FLAG_FLIP_Y" : "0") << ");\n";
            out << "        " << bob << ".drawx = " << r.x << " - camera_x;\n"
                << "        " << bob << ".drawy = " << r.y << " - camera_y;\n"
                << "        gfx_drawbob(&" << bob << ");\n";
        }
    } else {
        /* Without a map, the traditional single foreground draw is safe. */
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



// Stage 3.79: the F5 reminder MUST NOT call Update Game Project, since that
// command intentionally replaces installed SDK helper source. Preserve the
// graphics embedding mode of an existing generated game; default to PPB files
// for a never-before-generated project.
bool SidboxGameDesigner::regenerateBuildFiles()
{
    if (m_filePath.isEmpty() || !m_valid) return false;
    if (m_dirty && !saveDesign()) return false;

    bool embedPixels = false;
    const QString generatedSource = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gameassets/gameassets.c"));
    QFile current(generatedSource);
    if (current.open(QIODevice::ReadOnly)) {
        // The embed writer marks each bitmap; the normal PPB loader does not.
        // Read only enough of the generated source to find the first bitmap.
        const QByteArray prefix = current.read(256 * 1024);
        embedPixels = prefix.contains("/* Original PPB indexed pixels, unchanged;");
    }
    if (m_tilemapEnabled && tilemapBuildFilesMissing()
        && !exportTilemap(false, true)) return false;
    return generateGameCodeCore(embedPixels, true);
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


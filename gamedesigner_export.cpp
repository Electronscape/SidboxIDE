// Stage 3.69: split from gamedesigner.cpp. Method bodies are unchanged.
#include "gamedesigner.h"
#include "ppbcodec.h"
#include "pngpaletteimport.h"
#include "gamepalette.h"
#include "gamepaletteeditor.h"
#include "gamecodegen.h"
#include "gamehelpertemplates.h"
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
    if (hasAdventure()) names << QStringLiteral("adventureruntime");
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
            const QString from = GameHelperTemplates::sourcePath(templates, name, ext);
            QFile file(from);
            if (!file.open(QIODevice::ReadOnly)) {
                if (error) *error = tr("Missing helper template: %1").arg(from);
                return false;
            }
            const QByteArray sourceBytes = file.readAll();
            QByteArray data;
            if (ext == QStringLiteral(".c") || ext == QStringLiteral(".h")) {
                if (!GameHelperTemplates::render(sourceBytes, name, ext, m_adventure,
                                                 &data, error))
                    return false;
            } else {
                data = sourceBytes;
            }
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
        if (r.objectType == QStringLiteral("enemy") && r.enemyDefeatFrame >= 0) {
            const QImage image = cachedImage(resolvedPath(r.path));
            const int cw = r.cellWidth > 0 ? r.cellWidth : image.width();
            const int ch = r.cellHeight > 0 ? r.cellHeight : image.height();
            const int frames = !image.isNull() && cw > 0 && ch > 0
                ? (image.width() / cw) * (image.height() / ch) : 0;
            if (r.enemyDefeatFrame + r.enemyDefeatCount > qMin(256, frames)) {
                if (error) *error = tr("Enemy '%1': death animation starts at %2 and uses %3 frames, "
                                      "but the sprite atlas has only %4 usable frames (maximum 256).")
                    .arg(r.name).arg(r.enemyDefeatFrame).arg(r.enemyDefeatCount)
                    .arg(qMin(256, frames));
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
        if ((block.objectType != QStringLiteral("breakable") && block.objectType != QStringLiteral("enemy")) ||
            block.breakDropCollectableId.isEmpty()) continue;
        const QString id = block.breakDropCollectableId;
        int rewardIndex = -1;
        for (int j = 0; j < np; ++j)
            if (pickups.at(j)->id == id) { rewardIndex = j; break; }
        if (rewardIndex < 0) {
            if (error) *error = tr("Object '%1' targets a missing collectable. Reassign its reward.")
                .arg(block.name);
            return false;
        }
        if (!m_tilemapEnabled || pickupPaths.at(rewardIndex) >= 0) {
            if (error) *error = tr("Object '%1' needs an enabled tilemap and a reward "
                                   "collectable without a movement spline.").arg(block.name);
            return false;
        }
        if (breakRewardOwner.contains(id)) {
            if (error) *error = tr("Two game objects try to spawn the same reward '%1'. "
                                   "Use a different collectable for each object.")
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
    for (const Resource *r : platforms) {
        if (r->objectType == QStringLiteral("enemy") &&
            r->targetAction != QStringLiteral("none") && !r->targetObjectId.isEmpty() &&
            !objectSlot.contains(r->targetObjectId)) {
            if (error) *error = tr("Enemy '%1' links to a missing Game Object. Reassign its defeat target.").arg(r->name);
            return false;
        }
    }
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
        } else if (obj->objectType == QStringLiteral("breakable") || obj->objectType == QStringLiteral("enemy")) {
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
    QTextStream C(&c), G(&guide);
    // Stage 4.45: the .ruleh/.rulec own the file layout. These fragments
    // contain only project-specific data and optional declarations.
    QString hIncludes, hDeclarations;
    QTextStream HI(&hIncludes), HD(&hDeclarations);
    if (np) HI << "#include \"gamecollectables.h\"\n";
    if (nw) HI << "#include \"gameworldobjects.h\"\n";
    if (np) HD << "uint16_t gameworlditems_check(int32_t player_x, int32_t player_y,\n"
               "    uint16_t player_w, uint16_t player_h, game_pickup_callback_t callback, void *user);\n";
    if (nw) HD << "void gameworlditems_set_active(uint16_t index, uint8_t state); /* 0 off, 1 on, 2 toggle */\n";
    if (nw) HD << "void gameworlditems_before(game_world_player_t *player);\n"
               "void gameworlditems_after(game_world_player_t *player);\n";
    if (nt) HD << "uint16_t gameworlditems_trigger(int32_t player_x, int32_t player_y,\n"
               "    uint16_t player_w, uint16_t player_h, uint8_t fire2_pressed);\n";
    // The following stream creates only the dynamic runtime portion.
    bool anyPath = false;
    for (int p : pickupPaths) if (p >= 0) anyPath = true;
    for (int p : platformPaths) if (p >= 0) anyPath = true;
    QString cIncludes;
    QTextStream CI(&cIncludes);
    if (anyPath) CI << "#include \"splinepaths.h\"\n";
    if (nw && m_tilemapEnabled)
        CI << "#include \"gametilemap.h\"\n"
              "#include \"../gamelevels/level1.h\"\n";
    if (!usedSfx.isEmpty()) {
        // Audio positioning functions now live in gameworlditems.rulec.
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
    C.flush();
    QString worldDeclarations = c, worldInitBody, worldUpdateBody;
    QString worldBetweenInitUpdate, worldHooks;
    QString worldPickupCheck, worldTrigger;
    C.setString(&worldInitBody);
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
            const QString pickConst = r.pickupKind <= 4
                ? QStringList{QString(), QStringLiteral("GAME_PICKUP_COIN"),
                    QStringLiteral("GAME_PICKUP_HEALTH"), QStringLiteral("GAME_PICKUP_KEY"),
                    QStringLiteral("GAME_PICKUP_GEM")}.at(qBound(1,r.pickupKind,4))
                : QStringLiteral("%1u").arg(qBound(5,r.pickupKind,255));
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
                r.objectType == QStringLiteral("enemy") ? QStringLiteral("GAME_OBJECT_ENEMY") :
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
            if (r.objectType == QStringLiteral("enemy")) {
                C << "    platforms[" << ix << "].break_hits_required = " << r.breakHits << ";\n"
                  << "    platforms[" << ix << "].break_bounce = " << (r.breakBounce ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].break_strength = " << r.breakStrength << ";\n"
                  << "    platforms[" << ix << "].break_launch_x = " << r.breakLaunchX << ";\n"
                  << "    platforms[" << ix << "].enemy_stomp_side_kick = " << (r.enemyStompSideKick ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].enemy_attack_direction = " << r.enemyAttackDirection << ";\n"
                  << "    platforms[" << ix << "].enemy_hurts_on_touch = " << (r.enemyHurtsOnTouch ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].hazard_damage = " << r.enemyDamage << ";\n"
                  << "    platforms[" << ix << "].hazard_kick = " << (r.hazardKick ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].hazard_kick_x = " << r.hazardKickX << ";\n"
                  << "    platforms[" << ix << "].hazard_kick_y = " << r.hazardKickY << ";\n"
                  << "    platforms[" << ix << "].hazard_hurt_animation = " << (r.hazardHurtAnimation ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].hazard_flash = " << (r.hazardFlash ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].hazard_flash_colour = " << r.hazardFlashColour << ";\n"
                  << "    platforms[" << ix << "].hazard_flash_count = " << r.hazardFlashCount << ";\n"
                  << "    platforms[" << ix << "].hazard_flash_frames = " << r.hazardFlashFrames << ";\n"
                  << "    platforms[" << ix << "].enemy_roam = " << (r.enemyRoam && m_tilemapEnabled ? "1" : "0") << ";\n"
                  << "    platforms[" << ix << "].enemy_roam_speed = " << r.enemyRoamSpeed << ";\n"
                  << "    platforms[" << ix << "].enemy_step_height = " << r.enemyStepHeight << ";\n"
                  << "    platforms[" << ix << "].enemy_roam_direction = " << (r.enemyRoamLeft ? "-1" : "1") << ";\n"
                  << "    platforms[" << ix << "].enemy_defeat_frame = " << r.enemyDefeatFrame << ";\n"
                  << "    platforms[" << ix << "].enemy_defeat_frames = " << r.enemyDefeatDelay << ";\n"
                  << "    platforms[" << ix << "].enemy_defeat_count = " << r.enemyDefeatCount << ";\n"
                  << "    platforms[" << ix << "].enemy_defeat_delay = " << r.enemyDefeatDelay << ";\n"
                  << "    platforms[" << ix << "].enemy_stomp_offset_x = " << r.enemyStompOffsetX << ";\n"
                  << "    platforms[" << ix << "].enemy_stomp_offset_y = " << r.enemyStompOffsetY << ";\n"
                  << "    platforms[" << ix << "].enemy_stomp_width = " << r.enemyStompWidth << ";\n"
                  << "    platforms[" << ix << "].enemy_stomp_height = " << r.enemyStompHeight << ";\n";
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
        if (path >= 0 && !(r.objectType == QStringLiteral("enemy") && r.enemyRoam)) {
            const QString sym = splineSymbol(path);
            const QString var = QStringLiteral("%1_path_%2").arg(collect ? QStringLiteral("pickup") : QStringLiteral("platform")).arg(ix);
            C << "    start_spline(&" << var << ", " << sprite << ", "
              << sym << "_path, " << sym << "_count, " << sym << "_frames, " << sym << "_loop);\n"
              << "    set_spline_pos(&" << var << ", " << r.x << ", " << r.y << ");\n"
              << "    " << (collect ? "pickups" : "platforms") << "[" << ix << "].spline = &" << var << ";\n"
              << "    " << (collect ? "pickups" : "platforms") << "[" << ix
              << "].spline_start_delay = " << qBound(0, r.objectSplineStartDelay, 65535) << ";\n";
        }
        if (!collect && r.objectType == QStringLiteral("enemy"))
            C << "    platforms[" << ix << "].enemy_base_flip_x = " << (r.objectFlipX ? "1" : "0") << ";\n";
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
    C.flush();
    C.setString(&worldBetweenInitUpdate);
    if (nw) C << "void gameworlditems_set_active(uint16_t index, uint8_t state)\n{\n"
                   "    if (index >= GAMEWORLDITEMS_PLATFORM_COUNT) return;\n"
                   "    platforms[index].active = state == 2 ? (uint8_t)!platforms[index].active : (uint8_t)(state != 0);\n"
                   "}\n\n";
    if (nw && m_tilemapEnabled) C << "/* Same tile/slope query as the player. */\n"
        "static uint8_t cg_enemy_tile_blocked(int32_t x, int32_t y, uint16_t w, uint16_t h, void *ctx)\n"
        "{ return game_tilemap_actor_blocked((const game_tilemap_t *)ctx, x, y, w, h); }\n\n";
    C.flush();
    C.setString(&worldUpdateBody);
    if (nw) C << "    game_world_objects_update(platforms, " << nw << ", frames);\n";
    if (nw && m_tilemapEnabled) C << "    game_world_objects_roam(platforms, " << nw
        << ", frames, cg_enemy_tile_blocked, &game_level1);\n";
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
    C.flush();
    C.setString(&worldHooks);
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
        C << "@IDE_WORLD_BEFORE_START@";
        if (m_tilemapEnabled) C << "    if (game_death_is_dead()) return;\n";
        if (m_tilemapEnabled)
            C << "    if (player) {\n"
                 "        player->position_blocked = cg_world_player_blocked;\n"
                 "        player->collision_context = &game_level1;\n"
                 "    }\n";
        C << "    game_world_objects_before(platforms, " << nw << ", player);\n";
        C << "@IDE_WORLD_BEFORE_END@@IDE_WORLD_AFTER_START@";
        if (m_tilemapEnabled) C << "    if (game_death_is_dead()) return;\n";
        C << "    game_world_objects_after(platforms, " << nw << ", player);\n"
             "    game_world_objects_hazards(platforms, " << nw << ", player);\n";
        if (hasBreakRewards) {
            for (int i = 0; i < nw; ++i) {
                const Resource &block = *platforms.at(i);
                if ((block.objectType != QStringLiteral("breakable") && block.objectType != QStringLiteral("enemy")) ||
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
        // Defeat actions are one-frame pulses from the runtime; no repeated door toggles.
        for (int i = 0; i < nw; ++i) {
            const Resource &enemy = *platforms.at(i);
            if (enemy.objectType != QStringLiteral("enemy")) continue;
            const QString action = linkedAction(enemy);
            if (!action.isEmpty())
                C << "    if (platforms[" << i << "].break_triggered) { " << action << " }\n";
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
            if (r.objectType == QStringLiteral("breakable") || r.objectType == QStringLiteral("enemy")) {
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
        C << "@IDE_WORLD_AFTER_END@";
    }
    C.flush();
    C.setString(&worldPickupCheck);
    if (np) {
        C << "@IDE_WORLD_CHECK_START@";
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
        C << "    return count;\n@IDE_WORLD_CHECK_END@";
    }
    C.flush();
    C.setString(&worldTrigger);
    if (nt) {
        C << "@IDE_WORLD_TRIGGER_START@";
        C << "    uint16_t fired = game_world_objects_trigger(platforms, " << nw
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
        C << "    return fired;\n@IDE_WORLD_TRIGGER_END@";
    }
    C.flush();
    C.setString(&c);
    QString drawBehindBody, drawBody;
    QTextStream DB(&drawBehindBody), DD(&drawBody);
    if (nw) DB << "    game_world_objects_draw_layer(platforms, " << nw << ", camera_x, camera_y, 1);\n";
    if (np) DB << "    game_collectables_draw_layer(pickups, " << np << ", camera_x, camera_y, 1);\n";
    DB.flush();
    if (nw) DD << "    game_world_objects_draw_layer(platforms, " << nw << ", camera_x, camera_y, 0);\n";
    if (np) DD << "    game_collectables_draw_layer(pickups, " << np << ", camera_x, camera_y, 0);\n";
    if (!usedSfx.isEmpty()) {
        DD << "    cg_audio_camera_x = camera_x;\n";
        for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            const QString soundId = r.objectType == QStringLiteral("conveyor")
                ? r.sfxAmbient : r.objectType == QStringLiteral("hazard")
                ? r.sfxHazardAmbient : r.objectType == QStringLiteral("lift") ? r.sfxMove : QString();
            if (soundId.isEmpty()) continue;
            const Resource &sound = *soundById.value(soundId);
            const int step = r.audioFadeFrames <= 0 ? 255 : qMax(1, (255 + r.audioFadeFrames - 1) / r.audioFadeFrames);
            DD << "    if (cg_loop_playing[" << i << "]) {\n"
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
    DD.flush();
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
    // Render the final files using the same strict one-pass @IDE{...}
    // substitute used by Adventure. Never write unresolved template fields.
    const QDir ruleFolder(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
    auto renderWorldRule = [&](const QString &filename,
                               const QMap<QString, QString> &fields,
                               QString *output) -> bool {
        QFile file(ruleFolder.filePath(filename));
        if (!file.open(QIODevice::ReadOnly)) {
            if (error) *error = tr("Cannot read World Items rule template: %1").arg(file.fileName());
            return false;
        }
        QByteArray rendered;
        if (!GameHelperTemplates::renderFields(file.readAll(), fields, filename, &rendered, error))
            return false;
        *output = QString::fromUtf8(rendered);
        return true;
    };
    C.flush();
    HI.flush();
    HD.flush();
    CI.flush();
    QMap<QString, QString> headerFields;
    headerFields.insert(QStringLiteral("CONDITIONAL_INCLUDES"), hIncludes);
    headerFields.insert(QStringLiteral("PICKUP_COUNT"), QString::number(np));
    headerFields.insert(QStringLiteral("WORLD_OBJECT_COUNT"), QString::number(nw));
    headerFields.insert(QStringLiteral("OPTIONAL_DECLARATIONS"), hDeclarations);
    if (!renderWorldRule(QStringLiteral("gameworlditems.ruleh"), headerFields, &h))
        return false;
    QMap<QString, QString> sourceFields;
    sourceFields.insert(QStringLiteral("CONDITIONAL_INCLUDES"), cIncludes);
    sourceFields.insert(QStringLiteral("HAS_AUDIO"), usedSfx.isEmpty() ? QStringLiteral("0") : QStringLiteral("1"));
    sourceFields.insert(QStringLiteral("DRAW_BEHIND_BODY"), drawBehindBody);
    sourceFields.insert(QStringLiteral("DRAW_BODY"), drawBody);
    // Function boundaries are owned by gameworlditems.rulec. Qt emits bodies only.
    const QString beforeStart = QStringLiteral("@IDE_WORLD_BEFORE_START@");
    const QString betweenHooks = QStringLiteral("@IDE_WORLD_BEFORE_END@@IDE_WORLD_AFTER_START@");
    const QString afterEnd = QStringLiteral("@IDE_WORLD_AFTER_END@");
    const qsizetype bs = worldHooks.indexOf(beforeStart);
    const qsizetype bm = worldHooks.indexOf(betweenHooks);
    const qsizetype be = worldHooks.indexOf(afterEnd);
    QString hookPrelude, beforeBody, afterBody;
    if (nw) {
        if (bs < 0 || bm < bs || be < bm) {
            if (error) *error = tr("World Items hook-body markers are malformed.");
            return false;
        }
        hookPrelude = worldHooks.left(bs);
        beforeBody = worldHooks.mid(bs + beforeStart.size(), bm - bs - beforeStart.size());
        afterBody = worldHooks.mid(bm + betweenHooks.size(), be - bm - betweenHooks.size());
    } else {
        hookPrelude = worldHooks;
    }
    const QString checkStart = QStringLiteral("@IDE_WORLD_CHECK_START@");
    const QString checkEnd = QStringLiteral("@IDE_WORLD_CHECK_END@");
    const QString triggerStart = QStringLiteral("@IDE_WORLD_TRIGGER_START@");
    const QString triggerEnd = QStringLiteral("@IDE_WORLD_TRIGGER_END@");
    QString checkBody, triggerBody;
    if (np) {
        if (!worldPickupCheck.startsWith(checkStart) || !worldPickupCheck.endsWith(checkEnd)) {
            if (error) *error = tr("World Items pickup-check markers are malformed.");
            return false;
        }
        checkBody = worldPickupCheck.mid(checkStart.size(), worldPickupCheck.size() - checkStart.size() - checkEnd.size());
    }
    if (nt) {
        if (!worldTrigger.startsWith(triggerStart) || !worldTrigger.endsWith(triggerEnd)) {
            if (error) *error = tr("World Items trigger markers are malformed.");
            return false;
        }
        triggerBody = worldTrigger.mid(triggerStart.size(), worldTrigger.size() - triggerStart.size() - triggerEnd.size());
    }
    sourceFields.insert(QStringLiteral("WORLD_DECLARATIONS"), worldDeclarations);
    sourceFields.insert(QStringLiteral("INIT_BODY"), worldInitBody);
    sourceFields.insert(QStringLiteral("BETWEEN_INIT_UPDATE"), worldBetweenInitUpdate);
    sourceFields.insert(QStringLiteral("UPDATE_BODY"), worldUpdateBody);
    sourceFields.insert(QStringLiteral("HOOK_PRELUDE"), hookPrelude);
    sourceFields.insert(QStringLiteral("BEFORE_BODY"), beforeBody);
    sourceFields.insert(QStringLiteral("AFTER_BODY"), afterBody);
    sourceFields.insert(QStringLiteral("CHECK_BODY"), checkBody);
    sourceFields.insert(QStringLiteral("TRIGGER_BODY"), triggerBody);
    sourceFields.insert(QStringLiteral("HAS_WORLDS"), nw ? QStringLiteral("1") : QStringLiteral("0"));
    sourceFields.insert(QStringLiteral("HAS_PICKUPS"), np ? QStringLiteral("1") : QStringLiteral("0"));
    sourceFields.insert(QStringLiteral("HAS_TRIGGERS"), nt ? QStringLiteral("1") : QStringLiteral("0"));
    if (!renderWorldRule(QStringLiteral("gameworlditems.rulec"), sourceFields, &c))
        return false;
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
    const bool adventureEnabled = hasAdventure();
    QSet<QString> adventureNpcIds;
    if (adventureEnabled) {
        for (const QJsonValue &entry : m_adventure.value(QStringLiteral("npcs")).toArray())
            adventureNpcIds.insert(entry.toObject().value(QStringLiteral("spriteId")).toString());
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
                                      (r.objectType == QStringLiteral("hazard") || r.objectType == QStringLiteral("enemy")); });
    // maingame.rulec is the entire generated C file. Qt supplies only project data.
    const auto safeCommentValue = [](QString value) {
        value.replace(QStringLiteral("*/"), QStringLiteral("* /"));
        value.replace(QLatin1Char('\n'), QLatin1Char(' '));
        value.replace(QLatin1Char('\r'), QLatin1Char(' '));
        return value;
    };
    const QDir gameRulesDir(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
    const QString mainRulesPath = gameRulesDir.filePath(QStringLiteral("maingame.rulec"));
    QFile mainRules(mainRulesPath);
    if (!mainRules.open(QIODevice::ReadOnly)) {
        if (error) *error = tr("Cannot open Main Game rule template: %1").arg(mainRulesPath);
        return false;
    }
    const QByteArray mainRuleSource = mainRules.readAll();
    QMap<QString, QString> mainFields;
    const auto mainFlag = [&](const char *name, bool value) {
        mainFields.insert(QLatin1String(name), value ? QStringLiteral("1") : QStringLiteral("0"));
    };
    mainFlag("HAS_MAP", hasMap);
    mainFlag("HAS_OBJECTS", hasObjects);
    mainFlag("HAS_ADVENTURE", adventureEnabled);
    mainFlag("HAS_SPLINES", hasSplines);
    mainFlag("HAS_AUDIO", hasMusic || hasAudio);
    mainFlag("HAS_EXTERNAL_MAP", hasMap && m_tilemapExternal);
    mainFlag("HAS_BACKGROUND_PLANE", dualPlane && hasBackgroundSprites);
    mainFlag("DUAL_PLANE", dualPlane);
    mainFlag("HAS_PHYSICS", hasPhysics);
    mainFlag("HAS_WORLD_PLAYER", hasPhysics && worldObjects);
    mainFlag("HAS_PICKUPS", hasPhysics && pickups);
    mainFlag("HAS_ATTACHED_SPLINES", hasObjects && !attachedSplineDescriptions.isEmpty());
    mainFlag("HAS_PLAYER_HAZARDS", hasPhysics && hasHazards);
    mainFlag("HAS_MURDER_OBJECTS", hasMurderObjects);
    mainFlag("HAS_PLAYER_ANIMATION", hasPlayerAnimation);
    mainFlag("HAS_CUSTOM_ZONES", hasPhysics && hasCustomZones);
    mainFlag("HAS_MUSIC", hasMusic);
    mainFlag("HAS_BACKGROUND_SPRITES", hasBackgroundSprites);
    mainFlag("SINGLE_PLANE_BACKGROUND", !dualPlane && hasBackgroundSprites);
    mainFlag("HAS_MAPLESS_SCENE", !hasMap && !hasObjects);
    mainFlag("HAS_ADVENTURE_PHYSICS", adventureEnabled && hasPhysics);
    mainFlag("HAS_FRONT_TILES", hasMap && std::any_of(m_tilemap.flips.cbegin(), m_tilemap.flips.cend(),
        [](char flags) { return (quint8(flags) & 4u) != 0; }));
    mainFields.insert(QStringLiteral("PLAYER_SYMBOL"), playerName);
    for (int zone = 1; zone <= 8; ++zone)
        mainFields.insert(QStringLiteral("ZONE_%1").arg(zone),
            sidboxTilemapZoneMacroName(m_tilemap, zone));
    mainFlag("HAS_CUSTOM_COLLISION_SURFACES", hasMap &&
        (m_tilemap.collisions.contains(char(7)) || !m_tilemap.collisionPlacements.isEmpty()));
    mainFlag("HAS_LOOPS", hasMap && !m_tilemap.loops.isEmpty());
    mainFlag("HAS_NO_MAP", !hasMap);
    mainFlag("HAS_MAP_ONLY", hasMapOnly);
    mainFlag("HAS_OBJECTS_NO_PHYSICS", !hasPhysics && hasObjects);
    mainFields.insert(QStringLiteral("TILEMAP_DESCRIPTION"),
        hasMap ? (m_tilemapExternal ? QStringLiteral("SD .map") : QStringLiteral("embedded C"))
               : QStringLiteral("none"));
    mainFields.insert(QStringLiteral("PLAYER_DESCRIPTION"),
        player ? safeCommentValue(spriteSymbol(*player)) : QStringLiteral("not found"));
    mainFields.insert(QStringLiteral("SPRITE_COUNT"), QString::number(spriteCount));
    mainFields.insert(QStringLiteral("PICKUP_COUNT"), QString::number(pickups));
    mainFields.insert(QStringLiteral("WORLD_OBJECT_COUNT"), QString::number(worldObjects));
    mainFields.insert(QStringLiteral("MUSIC_DESCRIPTION"), hasMusic ? QStringLiteral("present") : QStringLiteral("none"));
    mainFields.insert(QStringLiteral("SOUND_DESCRIPTION"), hasAudio ? QStringLiteral("present") : QStringLiteral("none"));
    mainFields.insert(QStringLiteral("SPLINE_COUNT"), QString::number(validSplineCount));
    mainFields.insert(QStringLiteral("ATTACHED_SPLINE_COUNT"),
                      QString::number(attachedSplineDescriptions.size()));
    mainFields.insert(QStringLiteral("PLAYER_ANIMATION_FILE"),
                      hasPlayerAnimation ? safeCommentValue(player->animationFile) : QString());
    mainFields.insert(QStringLiteral("LOOP_COUNT"), QString::number(m_tilemap.loops.size()));
    for (int i = 0; i < 8; ++i) {
        const QString suffix = QString::number(i + 1);
        mainFields.insert(QStringLiteral("USED_ZONE_") + suffix,
                          usedCustomZones[i] ? QStringLiteral("1") : QStringLiteral("0"));
        QString name = i < m_tilemap.customZoneNames.size()
            ? m_tilemap.customZoneNames.at(i) : QString();
        if (name.isEmpty()) name = QStringLiteral("Custom %1").arg(i+1);
        mainFields.insert(QStringLiteral("ZONE_NAME_") + suffix, safeCommentValue(name));
    }
    mainFlag("PART_MAIN", true);
    mainFlag("PART_SPRITE_DRAW", false);
    // renderConditionals validates all @IDE_IF flags, even in inactive blocks.
    // Sprite-specific values are filled later, but full-starter rendering must
    // already have a valid boolean for the nested SPRITE_FLIPPED condition.
    mainFlag("SPRITE_FLIPPED", false);
    const auto renderMainRule = [&](QString *buffer) -> bool {
        QByteArray conditionallyRendered, expanded;
        if (!GameHelperTemplates::renderConditionals(mainRuleSource, mainFields,
                mainRulesPath, &conditionallyRendered, error) ||
            !GameHelperTemplates::renderFields(conditionallyRendered, mainFields,
                mainRulesPath, &expanded, error)) return false;
        *buffer = QString::fromUtf8(expanded);
        return true;
    };
    // Repeated scenery placements are also sourced from maingame.rulec.
    // No gfx calls, sprite flags, or draw statements are assembled in Qt.
    const auto appendSpriteRule = [&](const Resource &r, QString *buffer) -> bool {
        mainFields.insert(QStringLiteral("SPRITE_SYMBOL"), spriteSymbol(r));
        mainFields.insert(QStringLiteral("SPRITE_X"), QString::number(r.x));
        mainFields.insert(QStringLiteral("SPRITE_Y"), QString::number(r.y));
        mainFlag("SPRITE_FLIPPED", r.objectFlipX || r.objectFlipY);
        mainFields.insert(QStringLiteral("SPRITE_FLIP_X"),
            r.objectFlipX ? QStringLiteral("BLIT_FLAG_FLIP_X") : QStringLiteral("0"));
        mainFields.insert(QStringLiteral("SPRITE_FLIP_Y"),
            r.objectFlipY ? QStringLiteral("BLIT_FLAG_FLIP_Y") : QStringLiteral("0"));
        mainFlag("PART_MAIN", false);
        mainFlag("PART_SPRITE_DRAW", true);
        QString generated;
        const bool ok = renderMainRule(&generated);
        mainFlag("PART_MAIN", true);
        mainFlag("PART_SPRITE_DRAW", false);
        if (ok) buffer->append(generated);
        return ok;
    };
    // The spline example's executable C lives in the rule, never in Qt.
    QString splineAttachedDescriptions, splinePathDescriptions, firstSplineSymbol;
    if (hasSplines) {
        QTextStream attached(&splineAttachedDescriptions);
        if (attachedSplineDescriptions.isEmpty())
            attached << " *   (none yet -- assign a Movement spline in Game Object Properties)\n";
        else
            for (const QString &description : attachedSplineDescriptions) attached << description;
        QTextStream paths(&splinePathDescriptions);
        for (int i = 0; i < m_splinePaths.size(); ++i) {
            if (m_splinePaths.at(i).points.size() < 2) continue;
            const QString symbol = splineSymbol(i);
            paths << " *   " << symbol << "_path, " << symbol << "_count, "
                  << symbol << "_frames, " << symbol << "_loop"
                  << (attachedSplineIds.contains(m_splinePaths.at(i).id)
                          ? "  [attached]" : "  [not attached]") << "\n";
            if (firstSplineSymbol.isEmpty()) firstSplineSymbol = symbol;
        }
    }
    mainFields.insert(QStringLiteral("SPLINE_ATTACHED_DESCRIPTIONS"), splineAttachedDescriptions);
    mainFields.insert(QStringLiteral("SPLINE_PATH_DESCRIPTIONS"), splinePathDescriptions);
    mainFields.insert(QStringLiteral("FIRST_SPLINE_SYMBOL"), firstSplineSymbol);
    // Only placement DATA is collected here. The complete screen rendering
    // sequence and all C drawing statements live in maingame.rulec.
    QString sceneryBehind, sceneryInFront;
    if (hasMap) {
        for (const Resource &r : m_resources) {
            if (r.kind != QStringLiteral("sprite") || r.path.isEmpty() ||
                r.objectType != QStringLiteral("decoration") || &r == player ||
                r.plane == QStringLiteral("background") || !r.drawBehindTiles ||
                adventureNpcIds.contains(r.id)) continue;
            if (!appendSpriteRule(r, &sceneryBehind)) return false;
        }
        for (const Resource &r : m_resources) {
            if (r.kind != QStringLiteral("sprite") || r.path.isEmpty() ||
                r.objectType != QStringLiteral("decoration") ||
                r.plane == QStringLiteral("background") || r.drawBehindTiles ||
                adventureNpcIds.contains(r.id) || (hasPhysics && &r == player)) continue;
            if (!appendSpriteRule(r, &sceneryInFront)) return false;
        }
    }
    mainFields.insert(QStringLiteral("SCENERY_BEHIND_TILES"), sceneryBehind);
    mainFields.insert(QStringLiteral("SCENERY_IN_FRONT_OF_TILES"), sceneryInFront);
    // Render the complete starter only ONCE, after its data fields are ready.
    // Generated main.c remains user-owned unless the ownership check approves it.
    QString program;
    if (!renderMainRule(&program)) return false;
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
    if ((anyWorldObject || anySpline || hasAdventure()) && !installMissingWorldHelpers(&integrationError, !batchMode)) {
        QMessageBox::warning(this, tr("Game Object Dependencies"), integrationError);
        return false;
    }
    if (anySpline && !exportSplinePaths(false)) return false;

    // gameadventure.c now references configuration macros emitted by the
    // adventure .ruleh. Generate Code only installs *missing* helpers; an
    // older installed header must not silently produce unbuildable C.
    // Update Game Project refreshes both runtime files transactionally.
    if (hasAdventure()) {
        const QString runtimeHeader = QDir(QFileInfo(m_filePath).absolutePath())
            .filePath(QStringLiteral("gamehelpers/gameadventureruntime.h"));
        QFile headerFile(runtimeHeader);
        if (!headerFile.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("Adventure Runtime Rules"),
                tr("Cannot read Adventure runtime header: %1").arg(runtimeHeader));
            return false;
        }
        const QByteArray headerBytes = headerFile.readAll();
        if (!headerBytes.contains("GAME_ADVENTURE_DEFAULT_TILE_SIZE")
            || !headerBytes.contains("GAME_ADVENTURE_DEFAULT_FRAMES_PER_CHAR")) {
            QMessageBox::warning(this, tr("Adventure Runtime Rules"),
                tr("The installed Adventure runtime is from an earlier version.\n"
                   "Use Update Game Project to back up the game and install the "
                   "current .rulec/.ruleh runtime before generating code."));
            return false;
        }
    }

    SidboxGameCodeGen::Request request;
    request.designDirectory = QFileInfo(m_filePath).absolutePath();
    request.outputDirectory = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gameassets"));
    request.dualPlane = m_planeMode->currentData().toString() == QStringLiteral("dual");
    request.embedPixels = embedPixels;
    request.foregroundCycle = {m_frontColourCycle.enabled, m_frontColourCycle.start,
                               m_frontColourCycle.length, m_frontColourCycle.speed};
    request.backgroundCycle = {m_backColourCycle.enabled, m_backColourCycle.start,
                               m_backColourCycle.length, m_backColourCycle.speed};
    const QString adventureSkinId = m_adventure.value(QStringLiteral("skinAtlasId")).toString();
    const QString activeAtlasPath = m_tilemapEnabled && !m_tilemap.atlasPath.isEmpty()
        ? QDir::cleanPath(resolvedPath(m_tilemap.atlasPath)) : QString();
    for (const Resource &r : m_resources) {
        // Tile Atlases are a library of possible sheets. Only the selected
        // tilemap atlas is loaded, avoiding unused SDRAM allocations.
        if (r.kind == QStringLiteral("tileatlas") && r.id != adventureSkinId &&
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
        a.musicPlayOnStart = r.kind == QStringLiteral("music") && r.musicPlayOnStart;
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
    if (!exportAdventure(&integrationError)) {
        QMessageBox::warning(this, tr("Adventure Generation"), integrationError);
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


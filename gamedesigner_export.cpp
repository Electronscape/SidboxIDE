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
#include "gameworldsnapshot.h"
#include "gamecrossworldlinks.h"
#include "gameplayerprofile.h"
#include "gametitleruntime.h"
#include "gamevisualgraphlogic.h"
#include "gamequestgen.h"

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
#include <utility>
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
    const QString worldBase = sidboxTilemapWorldBaseName(m_filePath);
    const QString worldSymbol = QStringLiteral("game_") + worldBase;
    const QString worldHeader = worldBase + QStringLiteral(".h");
    QVector<const Resource *> pickups, platforms;
    QVector<int> pickupPaths, platformPaths;
    for (const Resource &r : m_resources) {
        if(r.kind==QStringLiteral("sprite") && r.objectType==QStringLiteral("decoration")) {
            for(const QJsonValue &entry:r.logicNodes) {
                const QString op=entry.toObject().value(QStringLiteral("op")).toString();
                if(op==QStringLiteral("stat_compare") || op==QStringLiteral("quest_done")) {
                    if(error)*error=tr("Logic condition on Decoration '%1' cannot run: choose a managed Game Object as its owner.").arg(r.name);
                    return false;
                }
            }
        }
        if (r.kind != QStringLiteral("sprite") || r.objectType == QStringLiteral("decoration")) continue;
        if (r.scale != 100 || r.path.isEmpty() ||
            QFileInfo(resolvedPath(r.path)).suffix().compare(QStringLiteral("ppb"), Qt::CaseInsensitive)) {
            if (error) *error = tr("Game object '%1' must use a PPB sprite at 100%% scale.").arg(r.name);
            return false;
        }
        if (r.spriteStamp.active()) {
            if (QDir::cleanPath(resolvedPath(r.spriteStamp.sourcePath)) !=
                QDir::cleanPath(resolvedPath(r.path))) {
                if (error) *error = tr("Stamp '%1' must reference its original PPB sheet. Save the world to migrate it.").arg(r.name);
                return false;
            }
            QString stampError;
            const QImage sheet = cachedImage(resolvedPath(r.spriteStamp.sourcePath));
            if (r.spriteStamp.compose(sheet, &stampError).isNull()) {
                if (error) *error = tr("Invalid stamp '%1': %2").arg(r.name, stampError);
                return false;
            }
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
        if (r.objectType != QStringLiteral("collectable") &&
            (r.activeStateFrame >= 0 || r.inactiveStateFrame >= 0)) {
            if (r.objectAnimated || r.spriteStamp.active()) {
                if(error) *error=tr("'%1': static ACTIVE/INACTIVE state frames cannot be combined with looping animation or a sprite stamp. Turn off animation or clear the state frames.").arg(r.name);
                return false;
            }
            const QImage sheet=cachedImage(resolvedPath(r.path));
            const int cw=r.cellWidth>0?r.cellWidth:sheet.width();
            const int ch=r.cellHeight>0?r.cellHeight:sheet.height();
            const int frames=!sheet.isNull() && cw>0 && ch>0
                ? (sheet.width()/cw)*(sheet.height()/ch) : 0;
            if ((r.activeStateFrame>=0 && r.activeStateFrame>=qMin(256,frames)) ||
                (r.inactiveStateFrame>=0 && r.inactiveStateFrame>=qMin(256,frames))) {
                if(error) *error=tr("'%1': ACTIVE/INACTIVE state frame exceeds the sprite atlas (%2 frames).").arg(r.name).arg(frames);
                return false;
            }
        }
        if (r.objectType == QStringLiteral("enemy") && r.enemyHitFrame >= 0) {
            if (r.spriteStamp.active()) {
                if (error) *error = tr("Enemy '%1': hit-frame animation needs a frame-based sprite, not a tile stamp. Disable the hit animation (flash still works) or remove the stamp.").arg(r.name);
                return false;
            }
            const QImage image = cachedImage(resolvedPath(r.path));
            const int cw = r.cellWidth > 0 ? r.cellWidth : image.width();
            const int ch = r.cellHeight > 0 ? r.cellHeight : image.height();
            const int frames = !image.isNull() && cw > 0 && ch > 0
                ? (image.width() / cw) * (image.height() / ch) : 0;
            if (r.enemyHitFrame + r.enemyHitCount > qMin(256, frames)) {
                if (error) *error = tr("Enemy '%1': hit animation starts at %2 and uses %3 frames, "
                                      "but the atlas has only %4 usable frames.")
                    .arg(r.name).arg(r.enemyHitFrame).arg(r.enemyHitCount).arg(qMin(256, frames));
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
        QFile check(m_filePath);
        if(check.open(QIODevice::ReadOnly)) {
            const QJsonObject saved=QJsonDocument::fromJson(check.readAll()).object();
            const QJsonObject complete=saved.value(QStringLiteral("questCompletionActions")).toObject();
            const QJsonObject dialogue=saved.value(QStringLiteral("questCompletionDialogues")).toObject();
            for(auto it=dialogue.constBegin();it!=dialogue.constEnd();++it)
                if(it.value().toObject().value(QStringLiteral("dialogueNode")).toInt(-1)>=0) {
                    if(error)*error=tr("Quest completion dialogue in an empty world requires at least one managed Game Object. Add a Trigger or other object first.");
                    return false;
                }
            for(auto it=complete.constBegin();it!=complete.constEnd();++it)
                if(!it.value().toArray().isEmpty()) {
                    if(error)*error=tr("Quest completion actions in an empty world require at least one managed Game Object. Add a Trigger or other object first.");
                    return false;
                }
        }
        // If objects were removed, replace our PREVIOUSLY GENERATED files with
        // harmless stubs so stale references never break a subsequent build.
        const QDir oldFolder(QDir(QFileInfo(m_filePath).absolutePath())
            .filePath(QStringLiteral("gamehelpers")));
        if (!QDir().mkpath(oldFolder.absolutePath())) {
            if (error) *error = tr("Cannot create gamehelpers for an empty World Items export.");
            return false;
        }
        const QString generatedH = oldFolder.filePath(QStringLiteral("gameworlditems.h"));
        QFile original(generatedH);
        if (QFileInfo::exists(generatedH) && (!original.open(QIODevice::ReadOnly) ||
            !original.read(128).contains("GENERATED by CoderGirl"))) {
            if (error) *error = tr("Existing gameworlditems.h isn't recognised as a generated file. "
                                  "Please inspect it before regenerating.");
            return false;
        }
        // Even the empty-world stubs are owned by the rules, never C++ strings.
        const QDir ruleFolder(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
        const QRegularExpression sectionRe(QStringLiteral(
            R"((?ms)^@IDE_SECTION\{([A-Z_][A-Z0-9_]*)\}[ \t]*\r?\n(.*?)^@IDE_SECTION_END[ \t]*\r?\n?)"));
        const QRegularExpression flagRe(QStringLiteral(R"(@IDE_IF\{([A-Z_][A-Z0-9_]*)\})"));
        auto renderEmptyRule = [&](const QString &name, QString *output) -> bool {
            QFile input(ruleFolder.filePath(name));
            if (!input.open(QIODevice::ReadOnly)) {
                if (error) *error = tr("Cannot read World Items rule template: %1").arg(input.fileName());
                return false;
            }
            QString source = QString::fromUtf8(input.readAll());
            source.remove(sectionRe);
            if (source.contains(QStringLiteral("@IDE_SECTION"))) {
                if (error) *error = tr("Malformed or unclosed World Items rule section in %1").arg(name);
                return false;
            }
            QMap<QString, QString> flags;
            auto matches = flagRe.globalMatch(source);
            while (matches.hasNext()) flags.insert(matches.next().captured(1), QStringLiteral("0"));
            flags.insert(QStringLiteral("HAS_ITEMS"), QStringLiteral("0"));
            QByteArray conditional, expanded;
            if (!GameHelperTemplates::renderConditionals(source.toUtf8(), flags, name, &conditional, error) ||
                !GameHelperTemplates::renderFields(conditional, flags, name, &expanded, error)) return false;
            *output = QString::fromUtf8(expanded);
            return true;
        };
        QString stubH, stubC, stubGuide;
        if (!renderEmptyRule(QStringLiteral("gameworlditems.ruleh"), &stubH) ||
            !renderEmptyRule(QStringLiteral("gameworlditems.rulec"), &stubC) ||
            !renderEmptyRule(QStringLiteral("gameworlditems.ruletxt"), &stubGuide)) return false;
        struct Stub { QString file, data; };
        for (const Stub &stub : {
            Stub{QStringLiteral("gameworlditems.h"), stubH},
            Stub{QStringLiteral("gameworlditems.c"), stubC},
            Stub{QStringLiteral("gameworlditems.txt"), stubGuide}
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
    for (const Resource *r : platforms)
        if (r->objectType == QStringLiteral("trigger") || r->objectType == QStringLiteral("goto_world") || r->objectType == QStringLiteral("save_checkpoint")) ++nt;
    // Reject old/missing target worlds at generation, rather than generating
    // a door that silently fails on the SIDBOX.
    const QDir projectDir(QFileInfo(m_filePath).absolutePath());
    // The Quest Editor owns signal identities. Generated actions can only
    // target real, authored "Event signal" objectives in its project file.
    QSet<QString> questEventSignals;
    QFile questFile(projectDir.filePath(QStringLiteral(".codergirl/quests.json")));
    if(questFile.open(QIODevice::ReadOnly)) {
        const QJsonDocument document=QJsonDocument::fromJson(questFile.readAll());
        for(const QJsonValue &quest:document.object().value(QStringLiteral("quests")).toArray())
            for(const QJsonValue &step:quest.toObject().value(QStringLiteral("objectives")).toArray()) {
                const QJsonObject objective=step.toObject();
                if(objective.value(QStringLiteral("kind")).toString()==QStringLiteral("event"))
                    questEventSignals.insert(objective.value(QStringLiteral("target")).toString());
            }
    }
    QSet<QString> questCompletedIds;
    QJsonObject questCompletionActions,questCompletionDialogues;
    int questDialogueCount=0;
    {
        QFile worldFile(m_filePath);
        if(worldFile.open(QIODevice::ReadOnly)) {
            const QJsonObject world=QJsonDocument::fromJson(worldFile.readAll()).object();
            questCompletionActions=world.value(QStringLiteral("questCompletionActions")).toObject();
            questCompletionDialogues=world.value(QStringLiteral("questCompletionDialogues")).toObject();
            questDialogueCount=world.value(QStringLiteral("adventure")).toObject()
                .value(QStringLiteral("nodes")).toArray().size();
        }
        QFile questDefs(projectDir.filePath(QStringLiteral(".codergirl/quests.json")));
        if(questDefs.open(QIODevice::ReadOnly))
            for(const QJsonValue &value:QJsonDocument::fromJson(questDefs.readAll())
                    .object().value(QStringLiteral("quests")).toArray())
                questCompletedIds.insert(value.toObject().value(QStringLiteral("id")).toString());
    }
    QSet<QString> validWorlds;
    for (const QFileInfo &world : projectDir.entryInfoList(
            QStringList{QStringLiteral("*.sbgm")}, QDir::Files))
        validWorlds.insert(sidboxTilemapWorldBaseName(world.absoluteFilePath()));
    for (const Resource *r : platforms) {
        if (r->objectType != QStringLiteral("goto_world")) continue;
        if (r->gotoWorldName.isEmpty() || !validWorlds.contains(r->gotoWorldName) ||
            r->gotoWorldName == sidboxTilemapWorldBaseName(m_filePath)) {
            if (error) *error = tr("Goto World '%1' has an invalid destination. Select another world.")
                .arg(r->name);
            return false;
        }
        if (r->gotoStartId != QStringLiteral("default") && !r->gotoStartId.isEmpty()) {
            QString destinationPath;
            for (const QFileInfo &candidate : projectDir.entryInfoList(
                    QStringList{QStringLiteral("*.sbgm")}, QDir::Files)) {
                if (sidboxTilemapWorldBaseName(candidate.absoluteFilePath()) == r->gotoWorldName) {
                    destinationPath = candidate.absoluteFilePath(); break;
                }
            }
            QFile designFile(destinationPath);
            if (destinationPath.isEmpty() || !designFile.open(QIODevice::ReadOnly)) {
                if (error) *error = tr("Cannot read destination world for '%1'.").arg(r->name);
                return false;
            }
            const QJsonObject destination = QJsonDocument::fromJson(designFile.readAll()).object();
            bool exists = false;
            for (const QJsonValue &v : destination.value(QStringLiteral("playerStarts")).toArray())
                if (v.toObject().value(QStringLiteral("id")).toString() == r->gotoStartId) {
                    exists = true; break;
                }
            if (!exists) {
                if (error) *error = tr("Door '%1' references a deleted entrance in '%2'.")
                    .arg(r->name, r->gotoWorldName);
                return false;
            }
        }
    }
    /* Resolve remote targets against SAVED sibling .sbgm files; the destination
       slot numbering matches the destination's world-object export order. */
    auto remoteTarget = [&](const QString &id, QString *world, int *slot) -> bool {
        QString w, targetId;
        if (!cgDecodeCrossWorldLink(id,&w,&targetId)) return false;
        if (w==worldBase || !validWorlds.contains(w)) return false;
        for (const QFileInfo &file : projectDir.entryInfoList(
                 QStringList{QStringLiteral("*.sbgm")},QDir::Files)) {
            if (sidboxTilemapWorldBaseName(file.absoluteFilePath())!=w) continue;
            QFile source(file.absoluteFilePath());
            if (!source.open(QIODevice::ReadOnly)) return false;
            const QJsonObject design=QJsonDocument::fromJson(source.readAll()).object();
            const int index=cgCrossWorldObjectSlot(design,targetId);
            if (index<0) return false;
            if (world) *world=w;
            if (slot) *slot=index;
            return true;
        }
        return false;
    };
    auto npcTarget = [&](const QString &id, QString *world, int *slot) -> bool {
        // The detailed editor stores @npc:<world>:<spriteId>, while Visual
        // Nodes (whose cards are built from local sprite resources) historically
        // stores just <spriteId>. Both identify the SAME Adventure NPC. Accept
        // both forms here, in the one target resolver used by ordinary Trigger
        // actions and independent logic TRUE/FALSE actions.
        QString wantedWorld=worldBase;
        QString wantedSprite=id;
        if (id.startsWith(QStringLiteral("@npc:"))) {
            const int separator=id.indexOf(QLatin1Char(':'),5);
            if (separator<0) return false;
            wantedWorld=id.mid(5,separator-5);
            wantedSprite=id.mid(separator+1);
        }
        if (wantedWorld.isEmpty() || wantedSprite.isEmpty() || !validWorlds.contains(wantedWorld)) return false;
        QJsonArray npcs;
        if (wantedWorld==worldBase) {
            npcs=m_adventure.value(QStringLiteral("npcs")).toArray();
        } else {
            for (const QFileInfo &file : projectDir.entryInfoList(
                     QStringList{QStringLiteral("*.sbgm")},QDir::Files)) {
                if (sidboxTilemapWorldBaseName(file.absoluteFilePath())!=wantedWorld) continue;
                QFile input(file.absoluteFilePath());
                if (!input.open(QIODevice::ReadOnly)) return false;
                npcs=QJsonDocument::fromJson(input.readAll()).object()
                    .value(QStringLiteral("adventure")).toObject()
                    .value(QStringLiteral("npcs")).toArray();
                break;
            }
        }
        for (int n=0;n<npcs.size();++n) {
            if (npcs[n].toObject().value(QStringLiteral("spriteId")).toString()!=wantedSprite) continue;
            if (world) *world=wantedWorld;
            if (slot) *slot=n;
            return true;
        }
        return false;
    };
    QHash<QString, QString> objectSlot; // Stable object ID -> generated live runtime instance.
    for (int i = 0; i < np; ++i)
        objectSlot.insert(pickups.at(i)->id, QStringLiteral("cg_gwi_pickups[%1]").arg(i));
    for (int i = 0; i < nw; ++i) {
        objectSlot.insert(platforms.at(i)->id, QStringLiteral("cg_gwi_platforms[%1]").arg(i));
        const QString type=platforms.at(i)->objectType;
        const QString id=platforms.at(i)->id;
        if(type==QStringLiteral("trigger")) {
            objectSlot.insert(QStringLiteral("@event:trigger:")+id,
                QStringLiteral("cg_gwi_platforms[%1].trigger_fired").arg(i));
            // Virtual readable latch, NOT the trigger's .active (which only
            // means the trigger can fire). It is toggled on each activation.
            objectSlot.insert(QStringLiteral("@triggerstate:")+id,
                QStringLiteral("cg_trigger_state[%1].active").arg(i));
        }
        if(type==QStringLiteral("enemy"))
            objectSlot.insert(QStringLiteral("@event:defeat:")+id,
                QStringLiteral("(cg_current_defeat_owner == %1u)").arg(i));
        const QStringList kinds=type==QStringLiteral("breakable")?
            QStringList{QStringLiteral("hit"),QStringLiteral("destroy")}:
            type==QStringLiteral("enemy")?QStringList{QStringLiteral("hit")}:
            type==QStringLiteral("hazard")?QStringList{QStringLiteral("player_hit")}:
            type==QStringLiteral("lift")?QStringList{QStringLiteral("arrival")}:
            type==QStringLiteral("goto_world")?QStringList{QStringLiteral("enter")}:
            type==QStringLiteral("save_checkpoint")?QStringList{QStringLiteral("save")}:QStringList{};
        for(const QString &kind:kinds) {
            const unsigned int bit=kind==QStringLiteral("hit")?1u:
                kind==QStringLiteral("destroy")?2u:
                kind==QStringLiteral("player_hit")?4u:
                kind==QStringLiteral("enter")?8u:
                kind==QStringLiteral("save")?16u:32u;
            objectSlot.insert(QStringLiteral("@event:")+kind+QLatin1Char(':')+id,
                QStringLiteral("(cg_named_event_sources[%1u] & %2u)").arg(i).arg(bit));
        }
    }
    for(int i=0;i<np;++i)
        objectSlot.insert(QStringLiteral("@event:pickup:")+pickups.at(i)->id,
            QStringLiteral("cg_named_pickup_sources[%1u]").arg(i));
    // WHOLE-WORLD event dependencies: the host is not necessarily the source.
    QSet<QString> watchedLogicEvents;
    for(const Resource *host:platforms)
        for(const QJsonValue &record:host->logicNodes)
            for(const QJsonValue &raw:record.toObject().value(QStringLiteral("inputs")).toArray())
                if(raw.toObject().value(QStringLiteral("kind")).toString()==QStringLiteral("event"))
                    watchedLogicEvents.insert(raw.toObject().value(QStringLiteral("id")).toString());
    for(const Resource *host:pickups)
        for(const QJsonValue &record:host->logicNodes)
            for(const QJsonValue &raw:record.toObject().value(QStringLiteral("inputs")).toArray())
                if(raw.toObject().value(QStringLiteral("kind")).toString()==QStringLiteral("event"))
                    watchedLogicEvents.insert(raw.toObject().value(QStringLiteral("id")).toString());
    // One target-type contract for *every* Trigger and logic-branch action.
    // A boolean RESULT can only bind a local object .active (validated by
    // SidboxVisualLogic::order); a TRUE/FALSE command can additionally operate
    // on NPC visibility, remote objects and the spotlight.
    const auto actionTargetExists = [&](const QString &id) -> bool {
        if (id.isEmpty()) return false;
        if (id.startsWith(QStringLiteral("@quest_event:")))
            return questEventSignals.contains(id.mid(QStringLiteral("@quest_event:").size()));
        if (id==QStringLiteral("@player_spotlight") ||
            (objectSlot.contains(id) && !id.startsWith(QStringLiteral("@event:")))) return true;
        if(id.startsWith(QStringLiteral("@player_weather:"))) {
            const QString mode=id.mid(16);
            return QStringList{QStringLiteral("0"),QStringLiteral("1"),QStringLiteral("2"),QStringLiteral("3")}.contains(mode);
        }
        if(id.startsWith(QStringLiteral("@player_time:"))) {
            const QString mode=id.mid(13);
            return QStringList{QStringLiteral("0"),QStringLiteral("1"),QStringLiteral("2")}.contains(mode);
        }
        if(id.startsWith(QStringLiteral("@player_world:"))) {
            const QString name=id.mid(14);
            if(name.isEmpty() || name.size()>63)return false;
            for(const QChar c:name)if(!c.isLetterOrNumber() && c!=QLatin1Char('_') &&
                                      c!=QLatin1Char('-') && c!=QLatin1Char(' '))return false;
            return validWorlds.contains(name);
        }
        QString targetWorld;
        int targetSlot=-1;
        return remoteTarget(id,&targetWorld,&targetSlot) ||
               npcTarget(id,&targetWorld,&targetSlot);
    };
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
    // Repeatable ordinary loot uses independently spawned copies, not the
    // unique reward Collectable slot. Never relax breakRewardOwner ownership.
    QString lootRows;
    int lootRuleCount = 0;
    for (int i = 0; i < nw; ++i) {
        const Resource &enemy = *platforms.at(i);
        if (enemy.objectType != QStringLiteral("enemy") || enemy.enemyLootIds.isEmpty()) continue;
        if (!m_tilemapEnabled) {
            if (error) *error = tr("Enemy '%1' uses ordinary loot. Enable the tilemap for falling loot physics.")
                .arg(enemy.name);
            return false;
        }
        if (enemy.enemyLootIds.size() > 8 || enemy.enemyLootMin < 0 ||
            enemy.enemyLootMax > 8 || enemy.enemyLootMin > enemy.enemyLootMax) {
            if (error) *error = tr("Enemy '%1' has an invalid ordinary loot configuration (0-8 drops, up to 8 types).")
                .arg(enemy.name);
            return false;
        }
        QStringList indices;
        QSet<QString> unique;
        for (const QString &id : enemy.enemyLootIds) {
            int j = -1;
            for (int k = 0; k < np; ++k)
                if (pickups.at(k)->id == id) { j = k; break; }
            if (j < 0 || unique.contains(id)) {
                if (error) *error = tr("Enemy '%1' references a missing or duplicate ordinary loot resource.")
                    .arg(enemy.name);
                return false;
            }
            const Resource &r = *pickups.at(j);
            if (r.pickupPersistent || r.pickupKind == 3 || droppingPickups.contains(j) ||
                !(r.pickupKind == 1 || r.pickupKind == 2 || r.pickupKind == 4 || r.pickupAllowEnemyLoot)) {
                if (error) *error = tr("Enemy '%1' references '%2' as ordinary loot, but this is a key, "
                                       "persistent / exclusive quest reward, or unapproved custom kind.")
                    .arg(enemy.name,r.name);
                return false;
            }
            unique.insert(id);
            indices.append(QString::number(j) + QStringLiteral("u"));
        }
        if (!indices.isEmpty() && enemy.enemyLootMax > 0) {
            lootRows += QStringLiteral("    {%1u,%2u,%3u,%4u,{%5}},\n")
                .arg(i).arg(enemy.enemyLootMin).arg(enemy.enemyLootMax)
                .arg(indices.size()).arg(indices.join(QStringLiteral(",")));
            ++lootRuleCount;
        }
    }
    const bool hasLoot = lootRuleCount > 0;
    const int lootSlotCount = qMin(64, lootRuleCount * 8);
    bool linkedKeys = false;
    for (const Resource *r : pickups) if (r->pickupKind == 3 &&
        r->targetAction != QStringLiteral("none") && !r->targetObjectId.isEmpty()) linkedKeys = true;
    for (const Resource *r : platforms) {
        if (r->objectType == QStringLiteral("enemy") &&
            r->targetAction != QStringLiteral("none") && !r->targetObjectId.isEmpty() &&
            (!actionTargetExists(r->targetObjectId) ||
             ((r->targetObjectId.startsWith(QStringLiteral("@player_time:")) ||
               r->targetObjectId.startsWith(QStringLiteral("@player_world:")) ||
               r->targetObjectId.startsWith(QStringLiteral("@quest_event:"))) &&
              r->targetAction!=QStringLiteral("enable")))) {
            if (error) *error = tr("Enemy '%1' links to an invalid defeat target. Reassign its action.").arg(r->name);
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
        if (!actionTargetExists(r->targetObjectId) ||
            ((r->targetObjectId.startsWith(QStringLiteral("@player_time:")) ||
              r->targetObjectId.startsWith(QStringLiteral("@player_world:")) ||
               r->targetObjectId.startsWith(QStringLiteral("@quest_event:"))) &&
             r->targetAction!=QStringLiteral("enable"))) {
            if (error) *error = tr("Trigger '%1' links to a missing game object. Reassign its target.").arg(r->name);
            return false;
        }
    }
    // Additional Trigger links resolve to actual PLACED objects (not atlas assets).
    // Validation precedes file output so a broken reference never half-generates C.
    for (const Resource *r : platforms) {
        if (r->objectType != QStringLiteral("trigger")) continue;
        for (const Resource::LinkedAction &link : r->triggerExtraActions) {
            if (link.objectId == r->id || !actionTargetExists(link.objectId) ||
                (link.action != QStringLiteral("enable") &&
                 link.action != QStringLiteral("disable") &&
                 link.action != QStringLiteral("toggle")) ||
                ((link.objectId.startsWith(QStringLiteral("@player_time:")) ||
                  link.objectId.startsWith(QStringLiteral("@player_world:")) ||
                  link.objectId.startsWith(QStringLiteral("@quest_event:"))) &&
                 link.action != QStringLiteral("enable"))) {
                if (error) *error = tr("Trigger '%1' has an invalid linked action target '%2'. "
                    "Choose an existing Game Object in its Linked Actions list.")
                    .arg(r->name,link.objectId);
                return false;
            }
        }
    }
    // All ON DEFEAT links must resolve before writing generated C.
    for (const Resource *r : platforms) {
        if (r->objectType != QStringLiteral("enemy")) continue;
        const bool hasPrimary=r->targetAction!=QStringLiteral("none") && !r->targetObjectId.isEmpty();
        if (r->enemyDefeatExtraActions.size()>(hasPrimary?63:64)) {
            if (error) *error=tr("Enemy '%1' has more than 64 defeat actions.").arg(r->name);
            return false;
        }
        for (const Resource::LinkedAction &link : r->enemyDefeatExtraActions) {
            if (link.objectId==r->id || !actionTargetExists(link.objectId) ||
                (link.action!=QStringLiteral("enable") &&
                 link.action!=QStringLiteral("disable") &&
                 link.action!=QStringLiteral("toggle")) ||
                ((link.objectId.startsWith(QStringLiteral("@player_time:")) ||
                  link.objectId.startsWith(QStringLiteral("@player_world:")) ||
                  link.objectId.startsWith(QStringLiteral("@quest_event:"))) &&
                 link.action!=QStringLiteral("enable"))) {
                if (error) *error=tr("Enemy '%1' has an invalid defeat action target '%2'.")
                    .arg(r->name,link.objectId);
                return false;
            }
        }
    }
    // Stage 5.166.110: validate every new event link before generating any C.
    // An event is bound to an actual kind of source; invalid data cannot silently
    // generate a no-op wire or change a different object's state.
    for (const Resource *r : platforms) {
        const QHash<QString,QStringList> kinds{
            {QStringLiteral("enemy"),{QStringLiteral("hit")}},
            {QStringLiteral("breakable"),{QStringLiteral("hit"),QStringLiteral("destroy")}},
            {QStringLiteral("hazard"),{QStringLiteral("player_hit")}},
            {QStringLiteral("goto_world"),{QStringLiteral("enter")}},
            {QStringLiteral("save_checkpoint"),{QStringLiteral("save")}},
            {QStringLiteral("lift"),{QStringLiteral("arrival")}}
        };
        const QStringList permitted=kinds.value(r->objectType);
        for (auto it=r->eventActions.constBegin();it!=r->eventActions.constEnd();++it) {
            if (!permitted.contains(it.key())) {
                if(error)*error=tr("'%1' has an event '%2' unsupported by its Game Object type.").arg(r->name,it.key());
                return false;
            }
            const QJsonArray actions=it.value().toArray();
            if(actions.size()>64) {
                if(error)*error=tr("'%1' event '%2' exceeds 64 actions.").arg(r->name,it.key());
                return false;
            }
            for (const QJsonValue &raw:actions) {
                const QJsonObject link=raw.toObject();
                const QString id=link.value(QStringLiteral("objectId")).toString();
                const QString command=link.value(QStringLiteral("action")).toString();
                if(id==r->id || !actionTargetExists(id) ||
                   (command!=QStringLiteral("enable") && command!=QStringLiteral("disable") &&
                    command!=QStringLiteral("toggle")) ||
                   ((id.startsWith(QStringLiteral("@player_time:")) ||
                     id.startsWith(QStringLiteral("@player_world:")) ||
                     id.startsWith(QStringLiteral("@quest_event:"))) && command!=QStringLiteral("enable"))) {
                    if(error)*error=tr("'%1' event '%2' has a broken action '%3'.").arg(r->name,it.key(),id);
                    return false;
                }
            }
        }
    }
    for (const Resource *r : pickups) {
        for(auto it=r->eventActions.constBegin();it!=r->eventActions.constEnd();++it) {
            if(it.key()!=QStringLiteral("pickup") || it.value().toArray().size()>64) {
                if(error)*error=tr("Collectable '%1' has an invalid ON PICKUP event.").arg(r->name);
                return false;
            }
            for(const QJsonValue &raw:it.value().toArray()) {
                const QJsonObject link=raw.toObject();
                const QString id=link.value(QStringLiteral("objectId")).toString();
                const QString command=link.value(QStringLiteral("action")).toString();
                if(id==r->id || !actionTargetExists(id) ||
                   (command!=QStringLiteral("enable") && command!=QStringLiteral("disable") && command!=QStringLiteral("toggle")) ||
                   ((id.startsWith(QStringLiteral("@player_time:")) || id.startsWith(QStringLiteral("@player_world:")) ||
                     id.startsWith(QStringLiteral("@quest_event:"))) && command!=QStringLiteral("enable"))) {
                    if(error)*error=tr("Collectable '%1' has a broken ON PICKUP action '%2'.").arg(r->name,id);
                    return false;
                }
            }
        }
    }
    // Resolve item interactions against this world's Adventure Inventory names.
    // Numeric item indices change across worlds, so persist/copy only the name.
    QSet<QString> availableInteractionItems;
    for (const QJsonValue &entry : m_adventure.value(QStringLiteral("items")).toArray()) {
        const QString name=entry.toObject().value(QStringLiteral("name")).toString().trimmed();
        if (!name.isEmpty()) availableInteractionItems.insert(name);
    }
    for (const Resource *r : platforms) {
        if ((r->objectType != QStringLiteral("trigger") &&
             r->objectType != QStringLiteral("save_checkpoint")) || r->interactItemName.isEmpty()) continue;
        if (!availableInteractionItems.contains(r->interactItemName)) {
            if (error) *error=tr("Interactable '%1' requires inventory item '%2', "
                "but this world does not define it in Adventure Editor → Inventory Items. "
                "Add or synchronise that item before updating the game.")
                .arg(r->name,r->interactItemName);
            return false;
        }
    }
    const QJsonArray dialogueNodes=m_adventure.value(QStringLiteral("nodes")).toArray();
    for (const Resource *r:platforms) {
        if (r->objectType!=QStringLiteral("trigger") &&
            r->objectType!=QStringLiteral("save_checkpoint") && r->logicNodes.isEmpty()) continue;
        if (!r->logicNodes.isEmpty()) {
            QVector<SidboxVisualLogic::Node> nodes;
            QVector<int> sorted;
            QString issue;
            QSet<QString> localIds;
            for(auto it=objectSlot.constBegin();it!=objectSlot.constEnd();++it)localIds.insert(it.key());
            if (!SidboxVisualLogic::read(r->logicNodes,&nodes,&issue) ||
                !SidboxVisualLogic::order(nodes,localIds,&sorted,&issue)) {
                if(error)*error=tr("Game Object '%1' logic graph: %2").arg(r->name,issue);
                return false;
            }
            const QString sbpiPath=projectDir.filePath(m_playerProfile);
            QJsonArray currentPlayerStats;
            QFile currentPlayerFile(sbpiPath);
            if(currentPlayerFile.open(QIODevice::ReadOnly))
                currentPlayerStats=QJsonDocument::fromJson(currentPlayerFile.readAll())
                    .object().value(QStringLiteral("customStats")).toArray();
            for(const SidboxVisualLogic::Node &node:nodes) {
                if(node.op==QStringLiteral("stat_compare")) {
                    bool statAvailable=node.statName==QStringLiteral("@health");
                    for(const QJsonValue &v:currentPlayerStats)
                        if(v.toObject().value(QStringLiteral("name")).toString()==node.statName)
                            statAvailable=true;
                    if(!statAvailable) {
                        if(error)*error=tr("Logic %1 requires player statistic '%2', but it does not exist in %3.")
                            .arg(node.id,node.statName,m_playerProfile);
                        return false;
                    }
                }
                if(node.op==QStringLiteral("quest_done") && !questCompletedIds.contains(node.questId)) {
                    if(error)*error=tr("Logic %1 references removed quest '%2'.")
                        .arg(node.id,node.questId);
                    return false;
                }
                for(const SidboxVisualLogic::Input &input:node.inputs)
                    if(input.kind==QStringLiteral("event") && !objectSlot.contains(input.id)) {
                        if(error)*error=tr("Game Object '%1' logic node '%2' reads unknown event '%3'.")
                            .arg(r->name,node.id,input.id);
                        return false;
                    }
                if(node.trueDialogue<-1 || node.trueDialogue>=dialogueNodes.size() ||
                   node.falseDialogue<-1 || node.falseDialogue>=dialogueNodes.size()) {
                    if(error)*error=tr("Game Object '%1' logic node '%2' references a missing dialogue.")
                        .arg(r->name,node.id);
                    return false;
                }
                for(const QJsonArray &links:{node.trueActions,node.falseActions})
                    for(const QJsonValue &link:links) {
                        const QJsonObject a=link.toObject();
                        const QString id=a.value(QStringLiteral("objectId")).toString();
                        const QString command=a.value(QStringLiteral("action")).toString();
                        // Shared type contract: not a separate graph-only
                        // subset of targets. The emitter below uses the SAME
                        // NPC/remote/local resolvers for the actual C action.
                        if(!QStringList{QStringLiteral("enable"),QStringLiteral("disable"),
                             QStringLiteral("toggle")}.contains(command) || !actionTargetExists(id) ||
                           ((id.startsWith(QStringLiteral("@player_time:")) ||
                             id.startsWith(QStringLiteral("@player_world:")) ||
                     id.startsWith(QStringLiteral("@quest_event:"))) &&
                              command!=QStringLiteral("enable"))) {
                            if(error)*error=tr("Game Object '%1' logic node '%2' has an invalid %3 action target '%4'. "
                                "Use a Game Object or Adventure NPC available in this world.")
                                .arg(r->name,node.id,command,id);
                            return false;
                        }
                    }
            }
        }
        if (r->objectType==QStringLiteral("trigger") && r->toggleStateTargetId.isEmpty() &&
            (!r->toggleTrueActions.isEmpty() || !r->toggleFalseActions.isEmpty())) {
            if (error)*error=tr("Trigger '%1': TRUE/FALSE actions need a Read Toggle State source.").arg(r->name);
            return false;
        }
        if (r->objectType==QStringLiteral("trigger") && !r->toggleStateTargetId.isEmpty()) {
            const QString op = r->toggleStateOperator;
            QStringList inputs{r->toggleStateTargetId};
            if (op == QStringLiteral("and") || op == QStringLiteral("or"))
                inputs.append(r->toggleStateInputIds);
            QStringList uniqueInputs=inputs;
            uniqueInputs.removeDuplicates();
            if ((op == QStringLiteral("and") && inputs.size() < 2) ||
                (op == QStringLiteral("or") && (inputs.size() < 2 || inputs.size() > 8)) ||
                inputs.size() > 16 || uniqueInputs.size() != inputs.size()) {
                if (error) *error=tr("Trigger '%1': %2 needs %3 unique state inputs.")
                    .arg(r->name,op,op==QStringLiteral("or")?tr("2–8"):tr("2–16"));
                return false;
            }
            for (const QString &input : inputs) {
                if (!objectSlot.contains(input)) {
                    if (error) *error=tr("Trigger '%1': logic input '%2' must be a local Game Object.")
                        .arg(r->name,input);
                    return false;
                }
            }
            // Runtime checks only live local Game Objects. Remote/NPC active
            // flags have a separate representation, so do not silently guess.
            if (!objectSlot.contains(r->toggleStateTargetId)) {
                if (error) *error=tr("Trigger '%1': toggle-state condition must read a Game Object in the same world.").arg(r->name);
                return false;
            }
            for (const bool yes:{true,false}) {
                const QVector<Resource::LinkedAction> &links=yes?r->toggleTrueActions:r->toggleFalseActions;
                if (links.size()>64) {
                    if (error)*error=tr("Trigger '%1': too many TRUE/FALSE actions (max 64 per branch).").arg(r->name);
                    return false;
                }
                for (const Resource::LinkedAction &link:links) {
                    if (link.objectId.isEmpty() || !QStringList{QStringLiteral("enable"),QStringLiteral("disable"),
                        QStringLiteral("toggle")}.contains(link.action) || !actionTargetExists(link.objectId) ||
                        ((link.objectId.startsWith(QStringLiteral("@player_time:")) ||
                          link.objectId.startsWith(QStringLiteral("@player_world:")) ||
                  link.objectId.startsWith(QStringLiteral("@quest_event:"))) &&
                         link.action != QStringLiteral("enable"))) {
                        if (error)*error=tr("Trigger '%1': invalid TRUE/FALSE action.").arg(r->name);
                        return false;
                    }
                }
            }
            if (r->toggleTrueDialogueNode < -1 || r->toggleTrueDialogueNode >= dialogueNodes.size() ||
                r->toggleFalseDialogueNode < -1 || r->toggleFalseDialogueNode >= dialogueNodes.size()) {
                if (error) *error=tr("Trigger '%1': TRUE/FALSE dialogue no longer exists.").arg(r->name);
                return false;
            }
        }
        if(r->objectType==QStringLiteral("enemy"))continue; // Trigger-only interaction settings.
        if(r->interactDialogueNode>=dialogueNodes.size() || r->interactDialogueNode < -1) {
            if(error) *error=tr("Trigger '%1': success dialogue node no longer exists. Select one in Game Object Properties.").arg(r->name);
            return false;
        }
        if (!r->interactItemName.isEmpty() &&
            (r->interactWrongDialogueNode>=dialogueNodes.size() || r->interactWrongDialogueNode < -1)) {
            if(error) *error=tr("Trigger '%1': wrong-item dialogue node no longer exists. Select one in Game Object Properties.").arg(r->name);
            return false;
        }
        if (!r->interactItemName.isEmpty() &&
            !r->interactRewardItem.isEmpty() && !availableInteractionItems.contains(r->interactRewardItem)) {
            if(error) *error=tr("Trigger '%1': reward item '%2' is not defined in this world's Adventure Inventory.").arg(r->name,r->interactRewardItem);
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
        if ((obj->objectType == QStringLiteral("trigger") ||
             obj->objectType == QStringLiteral("save_checkpoint")) && !obj->interactItemName.isEmpty()) {
            for (const QString &id : {obj->sfxInteractWrong, obj->sfxInteractSuccess,
                                      obj->sfxInteractCancel})
                if (!id.isEmpty()) usedSfx.insert(id);
        }
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
    QString h, c, guide;

    // The rule owns ALL emitted C statements.  Qt supplies only object data,
    // resource identities and feature flags for its repeatable sections.
    const QDir ruleFolder(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")));
    QFile worldRuleFile(ruleFolder.filePath(QStringLiteral("gameworlditems.rulec")));
    if (!worldRuleFile.open(QIODevice::ReadOnly)) {
        if (error) *error = tr("Cannot read World Items rule template: %1").arg(worldRuleFile.fileName());
        return false;
    }
    QString worldRuleSource = QString::fromUtf8(worldRuleFile.readAll());
    QMap<QString, QByteArray> worldSections;
    const QRegularExpression sectionRe(QStringLiteral(
        R"((?ms)^@IDE_SECTION\{([A-Z_][A-Z0-9_]*)\}[ \t]*\r?\n(.*?)^@IDE_SECTION_END[ \t]*\r?\n?)"));
    auto sections = sectionRe.globalMatch(worldRuleSource);
    while (sections.hasNext()) {
        const QRegularExpressionMatch match = sections.next();
        const QString name = match.captured(1);
        if (worldSections.contains(name)) {
            if (error) *error = tr("Duplicate World Items rule section: %1").arg(name);
            return false;
        }
        worldSections.insert(name, match.captured(2).toUtf8());
    }
    const int sectionCount = worldRuleSource.count(QStringLiteral("@IDE_SECTION{"));
    worldRuleSource.remove(sectionRe);
    if (worldSections.size() != sectionCount ||
        worldRuleSource.contains(QStringLiteral("@IDE_SECTION"))) {
        if (error) *error = tr("Malformed or unclosed @IDE_SECTION in gameworlditems.rulec");
        return false;
    }
    auto renderWorldSection = [&](const QString &name,
                                  const QMap<QString, QString> &fields,
                                  QString *destination) -> bool {
        if (!worldSections.contains(name)) {
            if (error) *error = tr("Missing World Items rule section %1").arg(name);
            return false;
        }
        QByteArray conditional, expanded;
        const QString label = QStringLiteral("gameworlditems.rulec / ") + name;
        if (!GameHelperTemplates::renderConditionals(worldSections.value(name), fields,
                                                      label, &conditional, error) ||
            !GameHelperTemplates::renderFields(conditional, fields, label, &expanded, error))
            return false;
        destination->append(QString::fromUtf8(expanded));
        return true;
    };
    auto renderWorldRule = [&](const QString &filename,
                               const QMap<QString, QString> &fields,
                               QString *output) -> bool {
        QByteArray raw;
        if (filename == QStringLiteral("gameworlditems.rulec")) {
            raw = worldRuleSource.toUtf8();
        } else {
            QFile file(ruleFolder.filePath(filename));
            if (!file.open(QIODevice::ReadOnly)) {
                if (error) *error = tr("Cannot read World Items rule template: %1").arg(file.fileName());
                return false;
            }
            raw = file.readAll();
        }
        QByteArray conditional, expanded;
        if (!GameHelperTemplates::renderConditionals(raw, fields, filename, &conditional, error) ||
            !GameHelperTemplates::renderFields(conditional, fields, filename, &expanded, error))
            return false;
        *output = QString::fromUtf8(expanded);
        return true;
    };
    const auto flag = [](bool yes) -> QString { return yes ? QStringLiteral("1") : QStringLiteral("0"); };
    const auto number = [](auto value) -> QString { return QString::number(value); };
    auto musicSymbol = [&](const Resource &r) -> QString {
        const Resource *music = musicById.value(r.triggerMusicId, nullptr);
        if (!music) return QString();
        const QString base = music->name.trimmed().isEmpty()
            ? QFileInfo(resolvedPath(music->path)).completeBaseName() : music->name;
        return SidboxPpb::identifier(base).toLower();
    };
    auto actionFields = [&](const Resource &r) -> QMap<QString, QString> {
        QMap<QString, QString> f;
        const QString target = objectSlot.value(r.targetObjectId);
        const bool valid = !target.isEmpty();
        f.insert(QStringLiteral("TARGET_EXPRESSION"), target);
        f.insert(QStringLiteral("TARGET_ENABLE"), flag(valid && r.targetAction == QStringLiteral("enable")));
        f.insert(QStringLiteral("TARGET_DISABLE"), flag(valid && r.targetAction == QStringLiteral("disable")));
        f.insert(QStringLiteral("TARGET_TOGGLE"), flag(valid && r.targetAction == QStringLiteral("toggle")));
        return f;
    };
    auto targetAction = [&](const Resource &r, QString *out) -> bool {
        if (r.targetAction == QStringLiteral("none") || r.targetObjectId.isEmpty()) return true;
        if (r.targetObjectId.startsWith(QStringLiteral("@quest_event:"))) {
            const QString eventId=r.targetObjectId.mid(QStringLiteral("@quest_event:").size());
            if(r.targetAction!=QStringLiteral("enable") || !questEventSignals.contains(eventId))return false;
            // This action is emitted by the existing bounded FIFO dispatcher,
            // never from graph initial-state synchronisation.
            *out+=QStringLiteral("        (void)gameworlds_quest_event(%1);\n")
                .arg(GameQuestGen::quoteC(eventId));
            return true;
        }
        QString otherWorld; int otherSlot=-1;
        if (npcTarget(r.targetObjectId,&otherWorld,&otherSlot)) {
            const int action=r.targetAction==QStringLiteral("enable") ? 1 :
                r.targetAction==QStringLiteral("disable") ? 0 :
                r.targetAction==QStringLiteral("toggle") ? 2 : -1;
            if (action>=0) *out += QStringLiteral(
                "        gameworlds_npc_action(\"%1\", %2u, %3u);\n")
                .arg(otherWorld).arg(otherSlot).arg(action);
            return true;
        }
        if (remoteTarget(r.targetObjectId,&otherWorld,&otherSlot)) {
            const int action=r.targetAction==QStringLiteral("enable") ? 1 :
                r.targetAction==QStringLiteral("disable") ? 0 :
                r.targetAction==QStringLiteral("toggle") ? 2 : -1;
            if (action>=0) *out += QStringLiteral(
                "        gameworlds_object_action(\"%1\", %2u, %3u);\n")
                .arg(otherWorld).arg(otherSlot).arg(action);
            return true;
        }
        if (r.targetObjectId.startsWith(QStringLiteral("@player_weather:"))) {
            const int action = r.targetAction==QStringLiteral("enable") ? 1 :
                r.targetAction==QStringLiteral("disable") ? 0 :
                r.targetAction==QStringLiteral("toggle") ? 2 : -1;
            if(action<0)return false;
            *out+=QStringLiteral("        gameworlds_weather_target_action(%1u, %2u);\n")
                .arg(r.targetObjectId.mid(16)).arg(action);
            return true;
        }
        if (r.targetObjectId.startsWith(QStringLiteral("@player_time:"))) {
            if(r.targetAction!=QStringLiteral("enable"))return false;
            *out+=QStringLiteral("        gameworlds_daylight_action(%1u);\n")
                .arg(r.targetObjectId.mid(13));
            return true;
        }
        if (r.targetObjectId.startsWith(QStringLiteral("@player_world:"))) {
            if(r.targetAction!=QStringLiteral("enable"))return false;
            const QString world=r.targetObjectId.mid(14);
            // All accepted world-name characters are C-literal safe.
            *out+=QStringLiteral("        (void)gameworlds_request_at(\"%1\", \"default\");\n")
                .arg(world);
            return true;
        }
        if (r.targetObjectId == QStringLiteral("@player_spotlight")) {
            const QString action = r.targetAction == QStringLiteral("enable") ? QStringLiteral("1")
                : r.targetAction == QStringLiteral("disable") ? QStringLiteral("0")
                : r.targetAction == QStringLiteral("toggle") ? QStringLiteral("2") : QString();
            if (!action.isEmpty()) *out += QStringLiteral("        gameworlds_spotlight_action(%1u);\n").arg(action);
            return true;
        }
        const QMap<QString, QString> f = actionFields(r);
        if (f.value(QStringLiteral("TARGET_ENABLE")) == QStringLiteral("0") &&
            f.value(QStringLiteral("TARGET_DISABLE")) == QStringLiteral("0") &&
            f.value(QStringLiteral("TARGET_TOGGLE")) == QStringLiteral("0")) return true;
        return renderWorldSection(QStringLiteral("TARGET_ACTION"), f, out);
    };
    // Stage 119: compile actions into a bounded FIFO command dispatcher. The
    // existing targetAction emitter remains the single source of action
    // semantics, so every target type is handled exactly as before.
    QString queuedActionCases;
    unsigned int queuedActionCount=0u;
    auto queueTargetAction = [&](const Resource &target, QString *destination) -> bool {
        QString immediate;
        if(!targetAction(target,&immediate))return false;
        if(immediate.isEmpty())return true;
        if(queuedActionCount>=65535u) {
            if(error)*error=tr("This world exceeds the maximum 65535 generated action commands.");
            return false;
        }
        ++queuedActionCount;
        queuedActionCases+=QStringLiteral("        case %1u: {\n%2            break;\n        }\n")
            .arg(queuedActionCount).arg(immediate);
        *destination+=QStringLiteral("        (void)cg_action_enqueue(%1u);\n").arg(queuedActionCount);
        return true;
    };
    auto audioFields = [&](const QString &soundId, int index, int radius) -> QMap<QString, QString> {
        QMap<QString, QString> f;
        const Resource *sound = soundById.value(soundId, nullptr);
        f.insert(QStringLiteral("INDEX"), number(index));
        f.insert(QStringLiteral("AUDIO_RADIUS"), number(radius));
        f.insert(QStringLiteral("SOUND_SYMBOL"), cSoundSymbol(soundId));
        if (sound) {
            f.insert(QStringLiteral("SOUND_CHANNEL"), number(sound->audio.channel));
            f.insert(QStringLiteral("SOUND_VOLUME"), number(qBound(0, sound->audio.volume, 1024)));
            f.insert(QStringLiteral("SOUND_PAN"), number(qBound(-127, sound->audio.pan, 127)));
        }
        return f;
    };

    // Metadata is just a tile index / flip lookup into the ORIGINAL PPB.
    // No stamp bitmaps, allocations, copied PPBs, or added project files.
    QString stampDeclarations;
    bool hasSpriteStamps = false;
    const auto appendStampTables = [&](const QVector<const Resource *> &objects,
                                       const QString &group) {
        if (objects.isEmpty()) return;
        QStringList lookups;
        for (int i = 0; i < objects.size(); ++i) {
            const SidboxSpriteStamp &stamp = objects.at(i)->spriteStamp;
            if (!stamp.active()) {
                lookups.append(QStringLiteral("{ 0, 0, 0 }"));
                continue;
            }
            hasSpriteStamps = true;
            const QString symbol = QStringLiteral("cg_stamp_%1_%2").arg(group).arg(i);
            QStringList codes;
            for (int cell : stamp.cells)
                codes.append(cell < 0 ? QStringLiteral("0xFFFFFFFFu") :
                    QStringLiteral("0x%1u").arg(quint32(cell), 8, 16, QLatin1Char('0')));
            stampDeclarations += QStringLiteral("static const uint32_t %1[] = { %2 };\n")
                .arg(symbol, codes.join(QStringLiteral(", ")));
            lookups.append(QStringLiteral("{ %1, %2u, %3u }")
                .arg(symbol).arg(stamp.width).arg(stamp.height));
        }
        stampDeclarations += QStringLiteral("static const cg_stamp_t cg_%1_stamps[%2] = { %3 };\n")
            .arg(group).arg(objects.size()).arg(lookups.join(QStringLiteral(", ")));
    };
    appendStampTables(pickups, QStringLiteral("pickup"));
    appendStampTables(platforms, QStringLiteral("platform"));
    QString audioWrappers, worldDeclarations, worldInitBody, worldUpdateBody;
    QString rewardSpawnActions, eventActions, eventSaveActions, eventEnterActions, checkBody, triggerBody, drawBody;
    QString drawBehindBody;
    QStringList sortedSoundIds;
    for (const QString &id : usedSfx) sortedSoundIds.append(id);
    sortedSoundIds.sort();
    for (const QString &id : sortedSoundIds) {
        QMap<QString, QString> f = audioFields(id, 0, 0);
        if (!renderWorldSection(QStringLiteral("SOUND_WRAPPER"), f, &audioWrappers)) return false;
    }

    auto animMode = [](const QString &s) -> QString {
        return s == QStringLiteral("pingpong") ? QStringLiteral("GAME_ANIM_PINGPONG") :
               s == QStringLiteral("once") ? QStringLiteral("GAME_ANIM_ONCE") :
               QStringLiteral("GAME_ANIM_LOOP");
    };
    bool anyPath = false;
    for (int i = 0; i < np + nw; ++i) {
        const bool collect = i < np;
        const int ix = collect ? i : i - np;
        const Resource &r = *(collect ? pickups.at(ix) : platforms.at(ix));
        const int path = collect ? pickupPaths.at(ix) : platformPaths.at(ix);
        const QString array = collect ? QStringLiteral("cg_gwi_pickups") : QStringLiteral("cg_gwi_platforms");
        const QString type = r.objectType;
        const bool enemy = type == QStringLiteral("enemy");
        const bool activePath = path >= 0 && !(enemy && r.enemyRoam);
        anyPath |= path >= 0;
        QMap<QString, QString> f;
        const auto value = [&](const char *name, auto v) { f.insert(QString::fromLatin1(name), number(v)); };
        const auto boolValue = [&](const char *name, bool v) { f.insert(QString::fromLatin1(name), flag(v)); };
        value("INDEX", ix);
        f.insert(QStringLiteral("OBJECT_LABEL"), collect ? QStringLiteral("Collectable") : QStringLiteral("World Object"));
        f.insert(QStringLiteral("OBJECT_NAME"), QString(r.name).replace(QLatin1Char('\n'), QLatin1Char(' '))
                 .replace(QStringLiteral("*/"), QStringLiteral("* /")));
        f.insert(QStringLiteral("ARRAY_NAME"), array);
        f.insert(QStringLiteral("SPRITE_SYMBOL"), spriteSymbol(r));
        f.insert(QStringLiteral("PATH_VAR"), QStringLiteral("%1_path_%2").arg(collect ? QStringLiteral("pickup") : QStringLiteral("platform")).arg(ix));
        f.insert(QStringLiteral("ANIM_VAR"), QStringLiteral("%1_anim_%2").arg(collect ? QStringLiteral("pickup") : QStringLiteral("platform")).arg(ix));
        f.insert(QStringLiteral("PATH_SYMBOL"), path >= 0 ? splineSymbol(path) : QString());
        boolValue("IS_PICKUP", collect);
        boolValue("IS_TRIGGER", type == QStringLiteral("trigger") || type == QStringLiteral("goto_world") || type == QStringLiteral("save_checkpoint"));
        boolValue("IS_CONVEYOR", type == QStringLiteral("conveyor"));
        boolValue("IS_BREAKABLE", type == QStringLiteral("breakable"));
        boolValue("IS_ENEMY", enemy);
        boolValue("IS_HAZARD", type == QStringLiteral("hazard"));
        boolValue("IS_DEATH_ZONE", type == QStringLiteral("deathzone"));
        boolValue("IS_SPRING", type == QStringLiteral("spring"));
        boolValue("HAS_PATH", path >= 0);
        boolValue("HAS_ACTIVE_PATH", activePath);
        boolValue("HAS_ANIMATION", r.objectAnimated);
        f.insert(QStringLiteral("FLIP_X"), r.objectFlipX ? QStringLiteral("BLIT_FLAG_FLIP_X") : QStringLiteral("0"));
        f.insert(QStringLiteral("FLIP_Y"), r.objectFlipY ? QStringLiteral("BLIT_FLAG_FLIP_Y") : QStringLiteral("0"));
        boolValue("FLIP_X_BOOL", r.objectFlipX);
        boolValue("DRAW_BEHIND", r.drawBehindTiles);
        boolValue("INIT_ACTIVE", collect && droppingPickups.contains(ix) ? false : r.objectInitiallyActive);
        value("WIDTH", r.hitWidth);
        value("HEIGHT", r.hitHeight);
        value("X", r.x);
        value("Y", r.y);
        value("RESPAWN_FRAMES", r.respawnFrames);
        value("PICKUP_VALUE", r.objectValue);
        value("PICKUP_INVENTORY", r.pickupShowInventory ? 1 : 0);
        value("PICKUP_HUD", r.pickupShowHud ? 1 : 0);
        const QString pickupStat = r.pickupStatTarget.isEmpty()
            ? (r.pickupKind == 2 ? QStringLiteral("health") : QStringLiteral("none"))
            : r.pickupStatTarget;
        const int pickupStatId = pickupStat == QStringLiteral("health") ? 1 :
            pickupStat == QStringLiteral("lives") ? 2 :
            pickupStat == QStringLiteral("score") ? 3 :
            pickupStat.startsWith(QStringLiteral("stat:")) ? 4 : 0;
        // Existing .sbgm worlds may predate the tracking_configured flag.
        // Either checked inventory/HUD option or an automatic stat effect
        // requires a managed callback, so old on_pickup() cannot secretly
        // add a no-inventory Health boost into the backpack as well.
        value("PICKUP_TRACKING", r.pickupTrackingConfigured || r.pickupShowInventory ||
            r.pickupShowHud || (!r.pickupShowInventory && pickupStatId != 0) ? 1 : 0);
        value("PICKUP_STAT_TARGET", pickupStatId);
        f.insert(QStringLiteral("PICKUP_STAT_NAME"), pickupStatId == 4
            ? QString::fromUtf8(QJsonDocument(QJsonArray{pickupStat.mid(5)})
                .toJson(QJsonDocument::Compact)).mid(1).chopped(1)
            : QStringLiteral("0"));
        value("PICKUP_PERSISTENT", r.pickupPersistent ? 1 : 0);
        const QStringList pickupsKinds{QString(), QStringLiteral("GAME_PICKUP_COIN"),
            QStringLiteral("GAME_PICKUP_HEALTH"), QStringLiteral("GAME_PICKUP_KEY"),
            QStringLiteral("GAME_PICKUP_GEM")};
        f.insert(QStringLiteral("PICKUP_KIND"), r.pickupKind <= 4
            ? pickupsKinds.at(qBound(1, r.pickupKind, 4)) : QStringLiteral("%1u").arg(qBound(5, r.pickupKind, 255)));
        const QString kind = type == QStringLiteral("lift") ? QStringLiteral("GAME_OBJECT_LIFT") :
            type == QStringLiteral("conveyor") ? QStringLiteral("GAME_OBJECT_CONVEYOR") :
            (type == QStringLiteral("trigger") || type == QStringLiteral("goto_world") || type == QStringLiteral("save_checkpoint")) ? QStringLiteral("GAME_OBJECT_TRIGGER") :
            type == QStringLiteral("door") ? QStringLiteral("GAME_OBJECT_DOOR") :
            type == QStringLiteral("deathzone") ? QStringLiteral("GAME_OBJECT_DEATH_ZONE") :
            type == QStringLiteral("breakable") ? QStringLiteral("GAME_OBJECT_BREAKABLE") :
            type == QStringLiteral("hazard") ? QStringLiteral("GAME_OBJECT_HAZARD") :
            type == QStringLiteral("enemy") ? QStringLiteral("GAME_OBJECT_ENEMY") :
            type == QStringLiteral("particle_emitter") ? QStringLiteral("GAME_OBJECT_PARTICLE_EMITTER") :
            type == QStringLiteral("decoration_object") ? QStringLiteral("GAME_OBJECT_DECORATION") :
            QStringLiteral("GAME_OBJECT_SPRING");
        f.insert(QStringLiteral("OBJECT_KIND"), kind);
        boolValue("TRIGGER_PRESS", type == QStringLiteral("goto_world") ? r.gotoPress : r.triggerPress);
        boolValue("TRIGGER_ONESHOT", (type == QStringLiteral("goto_world") || type == QStringLiteral("save_checkpoint")) ? false : r.triggerOneShot);
        boolValue("INTERACT_ENABLED", (type == QStringLiteral("trigger") ||
            type == QStringLiteral("save_checkpoint")) && !r.interactItemName.isEmpty());
        value("CONVEYOR_SPEED", r.conveyorSpeed);
        value("BREAK_HITS", r.breakHits);
        boolValue("BREAK_TOUCH", r.breakTouch && !r.breakFromBelow);
        boolValue("BREAK_BOUNCE", r.breakBounce);
        boolValue("BREAK_BELOW", r.breakFromBelow);
        value("BREAK_STRENGTH", r.breakStrength);
        value("BREAK_LAUNCH_X", r.breakLaunchX);
        boolValue("ENEMY_SIDE_KICK", r.enemyStompSideKick);
        value("ENEMY_ATTACK_DIRECTION", r.enemyAttackDirection);
        boolValue("ENEMY_HURT_TOUCH", r.enemyHurtsOnTouch);
        value("ENEMY_DAMAGE", r.enemyDamage);
        const QString statTarget=r.damageTarget;
        const int statKind=statTarget==QStringLiteral("health") ? 0 :
            statTarget==QStringLiteral("lives") ? 1 :
            statTarget==QStringLiteral("score") ? 2 :
            statTarget==QStringLiteral("coins") ? 3 : 4;
        f.insert(QStringLiteral("DEATH_NOTE"), r.deathNote.trimmed().isEmpty() ?
            QStringLiteral("0") : QString::fromUtf8(QJsonDocument(QJsonArray{r.deathNote.left(110)})
                       .toJson(QJsonDocument::Compact)).mid(1).chopped(1));
        value("DAMAGE_TARGET",statKind);
        value("DAMAGE_DELTA",r.damageConfigured ? r.damageDelta :
            -(type==QStringLiteral("enemy") ? r.enemyDamage : r.hazardDamage));
        f.insert(QStringLiteral("DAMAGE_NAME"),statKind==4 ? QString::fromUtf8(QJsonDocument(QJsonArray{statTarget.mid(5)})
            .toJson(QJsonDocument::Compact)).mid(1).chopped(1) : QStringLiteral("0"));
        boolValue("HAZARD_KICK", r.hazardKick);
        value("HAZARD_KICK_X", r.hazardKickX);
        value("HAZARD_KICK_Y", r.hazardKickY);
        boolValue("HAZARD_HURT_ANIM", r.hazardHurtAnimation);
        boolValue("HAZARD_FLASH", r.hazardFlash);
        value("HAZARD_FLASH_COLOUR", r.hazardFlashColour);
        value("HAZARD_FLASH_COUNT", r.hazardFlashCount);
        value("HAZARD_FLASH_FRAMES", r.hazardFlashFrames);
        boolValue("ENEMY_ROAM", r.enemyRoam && m_tilemapEnabled);
        value("ENEMY_ROAM_SPEED", r.enemyRoamSpeed);
        value("ENEMY_STEP_HEIGHT", r.enemyStepHeight);
        value("ENEMY_ROAM_DIRECTION", r.enemyRoamLeft ? -1 : 1);
        boolValue("ENEMY_HIT_FLASH", r.enemyHitFlash);
        value("ENEMY_HIT_FLASH_COLOUR", r.enemyHitFlashColour);
        value("ENEMY_HIT_FLASH_COUNT", r.enemyHitFlashCount);
        value("ENEMY_HIT_FLASH_FRAMES", r.enemyHitFlashFrames);
        value("ENEMY_HIT_FRAME", r.enemyHitFrame);
        value("ENEMY_HIT_COUNT", r.enemyHitCount);
        value("ENEMY_HIT_DELAY", r.enemyHitDelay);
        value("ENEMY_DEFEAT_FRAME", r.enemyDefeatFrame);
        value("ENEMY_DEFEAT_DELAY", r.enemyDefeatDelay);
        value("ENEMY_DEFEAT_COUNT", r.enemyDefeatCount);
        value("ENEMY_STOMP_X", r.enemyStompOffsetX);
        value("ENEMY_STOMP_Y", r.enemyStompOffsetY);
        value("ENEMY_STOMP_WIDTH", r.enemyStompWidth);
        value("ENEMY_STOMP_HEIGHT", r.enemyStompHeight);
        value("HAZARD_DAMAGE", r.hazardDamage);
        value("SPRING_STRENGTH", r.springStrength);
        value("SPRING_LAUNCH_X", r.springLaunchX);
        boolValue("SPRING_TOUCH", r.springTouch);
        boolValue("SPRING_SLIDE", r.springSlide);
        boolValue("SPRING_JUMP_BOOST", r.springJumpBoost);
        value("SPLINE_DELAY", qBound(0, r.objectSplineStartDelay, 65535));
        value("ANIM_FIRST", r.animFirst);
        value("ANIM_COUNT", r.animCount);
        value("ANIM_TICKS", r.animTicks);
        f.insert(QStringLiteral("ANIM_MODE"), animMode(r.animMode));
        if (!renderWorldSection(QStringLiteral("OBJECT_DECLARATION"), f, &worldDeclarations) ||
            !renderWorldSection(QStringLiteral("OBJECT_INIT"), f, &worldInitBody)) return false;
    }
    // Ambient loops start AFTER all object constructors, as in Stage 4.49.
    if (!usedSfx.isEmpty()) for (int i = 0; i < nw; ++i) {
        const Resource &r = *platforms.at(i);
        const QString soundId = r.objectType == QStringLiteral("hazard") ? r.sfxHazardAmbient
            : r.objectType == QStringLiteral("conveyor") ? r.sfxAmbient : QString();
        if (soundId.isEmpty()) continue;
        QMap<QString, QString> f = audioFields(soundId, i, r.audioRadius);
        if (!renderWorldSection(QStringLiteral("AMBIENT_INIT"), f, &worldInitBody)) return false;
    }
    if (!usedSfx.isEmpty()) {
        for (int i = 0; i < np; ++i) {
            const Resource &r = *pickups.at(i);
            if (r.respawnFrames && !r.sfxRespawn.isEmpty() &&
                !renderWorldSection(QStringLiteral("RESPAWN_SOUND"),
                    audioFields(r.sfxRespawn, i, r.audioRadius), &worldUpdateBody)) return false;
        }
        for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            const QString ambient = r.objectType == QStringLiteral("hazard") ? r.sfxHazardAmbient
                : r.objectType == QStringLiteral("conveyor") ? r.sfxAmbient : QString();
            if (!ambient.isEmpty() && !renderWorldSection(QStringLiteral("AMBIENT_UPDATE"),
                     audioFields(ambient, i, r.audioRadius), &worldUpdateBody)) return false;
            if (r.objectType != QStringLiteral("lift")) continue;
            QMap<QString, QString> f;
            f.insert(QStringLiteral("INDEX"), number(i));
            f.insert(QStringLiteral("AUDIO_RADIUS"), number(r.audioRadius));
            for (const auto &event : {std::pair<const char *, QString>{"START",r.sfxStart},
                                      {"REVERSE",r.sfxReverse}, {"STOP",r.sfxStop},
                                      {"MOVE",r.sfxMove}}) {
                const QString name = QString::fromLatin1(event.first);
                f.insert(QStringLiteral("HAS_SFX_") + name, flag(!event.second.isEmpty()));
                f.insert(QStringLiteral("SFX_") + name, cSoundSymbol(event.second));
            }
            f.insert(QStringLiteral("MOVE_CHANNEL"), r.sfxMove.isEmpty() ? QStringLiteral("0")
                    : number(soundById.value(r.sfxMove)->audio.channel));
            if (!renderWorldSection(QStringLiteral("LIFT_UPDATE"), f, &worldUpdateBody)) return false;
        }
    }
    if (nw) {
        if (hasBreakRewards) for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            if ((r.objectType != QStringLiteral("breakable") && r.objectType != QStringLiteral("enemy")) ||
                r.breakDropCollectableId.isEmpty()) continue;
            int j = -1;
            for (int k = 0; k < np; ++k) if (pickups.at(k)->id == r.breakDropCollectableId) { j = k; break; }
            if (j < 0) continue; // validated above
            const QMap<QString, QString> f{{QStringLiteral("INDEX"), number(i)},
                {QStringLiteral("REWARD_INDEX"), number(j)},
                {QStringLiteral("REWARD_VX"), number(r.breakRewardImpulse ? r.breakRewardVx * 100 : 0)},
                {QStringLiteral("REWARD_VY"), number(r.breakRewardImpulse ? r.breakRewardVy * 100 : 0)}};
            if (!renderWorldSection(QStringLiteral("REWARD_SPAWN"), f, &rewardSpawnActions)) return false;
        }
        for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            if (r.objectType != QStringLiteral("enemy")) continue;
            QString action;
            if (!queueTargetAction(r, &action)) return false;
            for (const Resource::LinkedAction &link : r.enemyDefeatExtraActions) {
                Resource target=r;
                target.targetObjectId=link.objectId;
                target.targetAction=link.action;
                if (!queueTargetAction(target,&action)) return false;
            }
            if (!action.isEmpty()) {
                const QMap<QString, QString> f{{QStringLiteral("INDEX"), number(i)},
                    {QStringLiteral("ACTION_BODY"), action}};
                if (!renderWorldSection(QStringLiteral("ENEMY_DEFEAT_ACTION"), f, &eventActions)) return false;
            }
        }
        // Named Visual Node event outputs. This is the same actionTarget()
        // emitter as Triggers/enemy defeat: identical target semantics.
        for(int i=0;i<nw;++i) {
            const Resource &r=*platforms.at(i);
            const QStringList eventNames={QStringLiteral("hit"),QStringLiteral("destroy"),
                QStringLiteral("player_hit"),QStringLiteral("enter"),QStringLiteral("save"),
                QStringLiteral("arrival")};
            for(const QString &eventName:eventNames) {
                QString action;
                for(const QJsonValue &value:r.eventActions.value(eventName).toArray()) {
                    const QJsonObject link=value.toObject();
                    Resource target=r;
                    target.targetObjectId=link.value(QStringLiteral("objectId")).toString();
                    target.targetAction=link.value(QStringLiteral("action")).toString();
                    if(!queueTargetAction(target,&action))return false;
                }
                bool neededForLogic=false;
                {
                    const QString eventId=QStringLiteral("@event:")+eventName+QLatin1Char(':')+r.id;
                    neededForLogic=watchedLogicEvents.contains(eventId);
                }
                if(action.isEmpty() && !neededForLogic)continue;
                if(eventName==QStringLiteral("save")) {
                    // The in-game save-picker is asynchronous. Only the exact
                    // checkpoint which opened it can receive a successful save.
                    eventSaveActions+=QStringLiteral("    if(cg_checkpoint_event_source==%1u) {\n"
                        "        cg_named_event_sources[%1u]|=16u;\n%2    }\n")
                        .arg(i).arg(action);
                    continue;
                }
                if(eventName==QStringLiteral("enter")) {
                    // Goto World is a Trigger internally. Dispatch on the
                    // successful entrance activation, before scene unload.
                    eventEnterActions+=QStringLiteral("    if(cg_gwi_platforms[%1].trigger_fired) {\n"
                        "        cg_named_event_sources[%1u]|=8u;\n%2    }\n")
                        .arg(i).arg(action);
                    continue;
                }
                const QString field=eventName==QStringLiteral("hit")
                    ?QStringLiteral("break_hit_triggered"):
                    eventName==QStringLiteral("destroy")?QStringLiteral("break_triggered"):
                    eventName==QStringLiteral("player_hit")?QStringLiteral("hazard_hit_triggered"):
                    QStringLiteral("arrival_triggered");
                eventActions+=QStringLiteral("    if(cg_gwi_platforms[%1].%2) {\n"
                    "        cg_named_event_sources[%1u]|=%4u;\n%3    }\n")
                    .arg(i).arg(field,action).arg(eventName==QStringLiteral("hit")?1:
                        eventName==QStringLiteral("destroy")?2:
                        eventName==QStringLiteral("player_hit")?4:32);
            }
        }
        // World sound events: a per-event rule is expanded only for assigned sounds.
        if (!usedSfx.isEmpty()) for (int i = 0; i < nw; ++i) {
            const Resource &r = *platforms.at(i);
            const QString type = r.objectType;
            QVector<QPair<QString, QString>> events;
            if (type == QStringLiteral("spring"))
                events.append({QStringLiteral("spring_triggered"), r.sfxSpring});
            if (type == QStringLiteral("hazard")) {
                events.append({QStringLiteral("hazard_hit_triggered"), r.sfxHazardHit});
                events.append({QStringLiteral("hazard_bounce_triggered"), r.sfxHazardBounce});
            }
            if (type == QStringLiteral("breakable") || type == QStringLiteral("enemy")) {
                events.append({QStringLiteral("break_hit_triggered"), r.sfxBreakHit});
                events.append({QStringLiteral("break_bounce_triggered"), r.sfxBreakBounce});
                events.append({QStringLiteral("break_triggered"), r.sfxBreakFinish});
            }
            for (const auto &ev : events) {
                if (ev.second.isEmpty()) continue;
                QMap<QString, QString> f = audioFields(ev.second, i, r.audioRadius);
                f.insert(QStringLiteral("EVENT_FIELD"), ev.first);
                if (!renderWorldSection(QStringLiteral("WORLD_EVENT_SOUND"), f, &eventActions)) return false;
            }
        }
    }
    // Preserve Stage 4.49 callback ordering: linked-key actions before
    // pickup sounds, even when several pickups are collected in one frame.
    if (np) for (int i = 0; i < np; ++i) {
        const Resource &r = *pickups.at(i);
        if (r.pickupKind != 3) continue;
        QString action;
        if (!queueTargetAction(r, &action)) return false;
        if (!action.isEmpty()) {
            const QMap<QString, QString> f{{QStringLiteral("INDEX"), number(i)},
                {QStringLiteral("ACTION_BODY"), action}};
            if (!renderWorldSection(QStringLiteral("PICKUP_TARGET_ACTION"), f, &checkBody)) return false;
        }
    }
    if (!usedSfx.isEmpty()) for (int i = 0; i < np; ++i) {
        const Resource &r = *pickups.at(i);
        if (!r.sfxPickup.isEmpty() && !renderWorldSection(QStringLiteral("PICKUP_EVENT_SOUND"),
                audioFields(r.sfxPickup, i, r.audioRadius), &checkBody)) return false;
    }
    QString particleEmitterRows;
    int particleEmitterCount = 0;
    for (int i = 0; i < nw; ++i) {
        const Resource &r = *platforms.at(i);
        if (r.objectType != QStringLiteral("particle_emitter")) continue;
        particleEmitterRows += QStringLiteral("    {%1u, %2u, %3u, %4u, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14, %15, %16, %17, %18, %19},\n")
            .arg(i).arg(qBound(8, r.particleAreaW, 2048))
            .arg(qBound(8, r.particleAreaH, 2048))
            .arg(qBound(30, r.particleLifetime, 2000))
            .arg(qBound(-400, r.particleWind, 400))
            .arg(qBound(-400, r.particleFall, 400))
            .arg(qBound(1, r.particleCount, 32))
            .arg(qBound(1, r.particleInterval, 255))
            .arg(r.particlePrepopulate ? 1 : 0)
            .arg(qBound(0, r.particleGravity, 80))
            .arg(qBound(0, r.particleFlutter, 100))
            .arg(r.particlePlayerLayerMix ? 1 : 0)
            .arg(r.particleFadeEnabled ? 1 : 0)
            .arg(qBound(0, r.particleFadeIn, 100))
            .arg(qBound(0, r.particleFadeOut, 100))
            .arg(qBound(1, r.particleFadeSpeed, 100))
            .arg(r.particlePreset == QStringLiteral("fireflies") ? 1 : 0)
            .arg(qBound(8, r.particleSwirlRadius, 96))
            .arg(qBound(1, r.particleSwirlSpeed, 12));
        ++particleEmitterCount;
    }
    QString interactionRows;
    QString interactionSoundActions;
    QString interactionPreflightActions;
    QString interactionDialogueActions;
    QString interactionWrongDialogueActions;
    QString activeStateFrames, inactiveStateFrames;
    bool hasInteractionOutcomes=false;
    const auto cQuoted=[](const QString &value) -> QString {
        return QString::fromUtf8(QJsonDocument(QJsonArray{value})
            .toJson(QJsonDocument::Compact)).mid(1).chopped(1);
    };
    for (const Resource *resource:platforms) {
        activeStateFrames+=QStringLiteral("    %1u,\n")
            .arg(resource->activeStateFrame>=0 ? resource->activeStateFrame : 65535);
        inactiveStateFrames+=QStringLiteral("    %1u,\n")
            .arg(resource->inactiveStateFrame>=0 ? resource->inactiveStateFrame : 65535);
    }
    for (int i=0; i<nw; ++i) {
        const Resource &r=*platforms.at(i);
        if ((r.objectType!=QStringLiteral("trigger") &&
             r.objectType!=QStringLiteral("save_checkpoint")) || r.interactItemName.isEmpty()) continue;
        // QJson escaping is valid inside a C string literal for item names.
        const QString quoted=QString::fromUtf8(QJsonDocument(
            QJsonArray{r.interactItemName}).toJson(QJsonDocument::Compact)).mid(1).chopped(1);
        interactionRows += QStringLiteral("    {%1u, %2u, %3u, %4u, %5},\n")
            .arg(i).arg(qBound(0,r.interactRadius,128))
            .arg(r.interactConsume ? 1 : 0).arg(r.triggerDrop ? 1 : 0).arg(quoted);
        if (!r.interactRewardItem.isEmpty() ||
            (r.interactStatTarget!=QStringLiteral("none") && !r.interactStatTarget.isEmpty() && r.interactStatDelta)) {
            hasInteractionOutcomes=true;
            QString body;
            if (!r.interactRewardItem.isEmpty()) {
                const QString gift=cQuoted(r.interactRewardItem);
                body+=QStringLiteral(
                    "        if (!game_adventure_can_reward_name(%1, %2u, !dropped && r->consume ? r->item : 0)) return 3u;\n")
                    .arg(gift).arg(qBound(1,r.interactRewardCount,64));
            }
            if(r.interactStatTarget!=QStringLiteral("none") &&
               !r.interactStatTarget.isEmpty() && r.interactStatDelta) {
                body+=QStringLiteral(
                    "        if (!gameadventure_apply_item_stat(%1, %2)) return 0u;\n")
                    .arg(cQuoted(r.interactStatTarget)).arg(r.interactStatDelta);
            }
            if (!r.interactRewardItem.isEmpty()) {
                if(r.interactConsume) body+=QStringLiteral(
                    "        if (!dropped && !game_adventure_take_name(r->item, 1u)) return 0u;\n"
                    "        if (!dropped) consumed_here=1u;\n");
                body+=QStringLiteral(
                    "        if (!game_adventure_reward_name(%1, %2u)) return 3u;\n")
                    .arg(cQuoted(r.interactRewardItem)).arg(qBound(1,r.interactRewardCount,64));
            }
            interactionPreflightActions+=QStringLiteral("    if(r->object==%1u) {\n%2    }\n")
                .arg(i).arg(body);
        }
        if(r.interactDialogueNode>=0) {
            hasInteractionOutcomes=true;
            const QString dialogueFunction=r.interactDialogueMode==QStringLiteral("single")
                ? QStringLiteral("game_adventure_trigger_message")
                : r.interactDialogueMode==QStringLiteral("sequence")
                    ? QStringLiteral("game_adventure_trigger_sequence")
                    : QStringLiteral("game_adventure_trigger_dialogue");
            interactionDialogueActions+=QStringLiteral(
                "    if (r->object==%1u) %3(%2u);\n")
                .arg(i).arg(r.interactDialogueNode).arg(dialogueFunction);
        }
        if(r.interactWrongDialogueNode>=0) {
            const QString dialogueFunction=r.interactWrongDialogueMode==QStringLiteral("single")
                ? QStringLiteral("game_adventure_trigger_message")
                : r.interactWrongDialogueMode==QStringLiteral("sequence")
                    ? QStringLiteral("game_adventure_trigger_sequence")
                    : QStringLiteral("game_adventure_trigger_dialogue");
            interactionWrongDialogueActions+=QStringLiteral(
                "        if (r->object==%1u) { %3(%2u); return 0u; }\n")
                .arg(i).arg(r.interactWrongDialogueNode).arg(dialogueFunction);
        }
        // Event 0: wrong item, 1: success, 2: FIRE2 cancel. Generated
        // calls use the normal Game Sound wrappers, not a second audio system.
        const QStringList eventSounds{r.sfxInteractWrong, r.sfxInteractSuccess, r.sfxInteractCancel};
        for (int event=0; event<eventSounds.size(); ++event) {
            const QString symbol=cSoundSymbol(eventSounds.at(event));
            if (symbol.isEmpty()) continue;
            interactionSoundActions += QStringLiteral(
                "    if (r->object == %1u && event == %2u) { "
                "cg_sound_%3(cg_gwi_platforms[%1u].x, %4); return; }\n")
                .arg(i).arg(event).arg(symbol).arg(r.audioRadius);
        }
    }
    // Stage 5.166.62: independent graphs watch all local Trigger actions which
    // change one of their Game Object inputs, not just the Trigger that first
    // created their card. Keep all evaluations AFTER ordinary Trigger actions.
    // Capture EVERY node result before dispatching ANY graph branch action.
    QString graphSnapshotsBody, graphEvaluationBody, graphDispatchBody;
    QString graphInitialSyncBody;
    bool hasStatCompare=false,hasQuestCondition=false;
    bool hasNamedPlatformLogic=false, hasNamedPickupLogic=false;
    if (nt) for (int i = 0; i < nw; ++i) {
        const Resource &r = *platforms.at(i);
        if (r.objectType != QStringLiteral("trigger") &&
            r.objectType != QStringLiteral("goto_world") &&
            r.objectType != QStringLiteral("save_checkpoint")) continue;
        QString action;
        if (r.objectType == QStringLiteral("save_checkpoint")) {
            action = QStringLiteral("        cg_checkpoint_event_source=%1u;\n"
                "        game_adventure_choose_save_slot(%2u);\n")
                .arg(i).arg(qBound(0, r.checkpointSlot, 9));
        } else if (r.objectType == QStringLiteral("goto_world")) {
            action = QStringLiteral("        gameworlds_request_at_from(\"%1\", \"%2\", "
                "cg_gwi_platforms[%3].x + cg_gwi_platforms[%3].width / 2, "
                "cg_gwi_platforms[%3].y + cg_gwi_platforms[%3].height / 2);\n")
                .arg(r.gotoWorldName, r.gotoStartId.isEmpty() ? QStringLiteral("default") : r.gotoStartId)
                .arg(i);
        } else {
            if (!queueTargetAction(r, &action)) return false;
            // Run each additional action in order, after the original link.
            // Reuse the proven enable/disable/toggle template and object indices.
            for (const Resource::LinkedAction &link : r.triggerExtraActions) {
                Resource target = r;
                target.targetObjectId = link.objectId;
                target.targetAction = link.action;
                if (!queueTargetAction(target, &action)) return false;
            }
            // Stage 5.166.43: ordinary touch/FIRE2 Triggers can now show
            // Adventure dialogue as an action, not only inventory USE Triggers.
            // Item-gated Triggers must continue to play their dialogue ONLY
            // from cg_complete_item_interaction(), never twice on success.
            if (!r.toggleStateTargetId.isEmpty() &&
                (r.toggleTrueDialogueNode>=0 || r.toggleFalseDialogueNode>=0 ||
                 !r.toggleTrueActions.isEmpty() || !r.toggleFalseActions.isEmpty())) {
                // This is deliberately AFTER normal Trigger target actions;
                // e.g. Toggle Lifty, then branch on Lifty's NEW state.
                QStringList inputs{r.toggleStateTargetId};
                if (r.toggleStateOperator==QStringLiteral("and") ||
                    r.toggleStateOperator==QStringLiteral("or"))
                    inputs.append(r.toggleStateInputIds);
                QStringList comparisons;
                for (const QString &input : inputs) {
                    const QString inputSlot=objectSlot.value(input);
                    if (!inputSlot.isEmpty()) comparisons.append(QStringLiteral("%1.active").arg(inputSlot));
                }
                const QString expression=comparisons.join(
                    r.toggleStateOperator==QStringLiteral("or")?QStringLiteral(" || "):
                    QStringLiteral(" && "));
                if (!expression.isEmpty()) {
                    action+=QStringLiteral("        if (%1) {\n").arg(expression);
                    for (const Resource::LinkedAction &link:r.toggleTrueActions) {
                        Resource target=r;
                        target.targetObjectId=link.objectId;
                        target.targetAction=link.action;
                        if (!queueTargetAction(target,&action))return false;
                    }
                    if (r.toggleTrueDialogueNode>=0)
                        action+=QStringLiteral("            game_adventure_trigger_message(%1u);\n")
                            .arg(r.toggleTrueDialogueNode);
                    action+=QStringLiteral("        } else {\n");
                    for (const Resource::LinkedAction &link:r.toggleFalseActions) {
                        Resource target=r;
                        target.targetObjectId=link.objectId;
                        target.targetAction=link.action;
                        if (!queueTargetAction(target,&action))return false;
                    }
                    if (r.toggleFalseDialogueNode>=0)
                        action+=QStringLiteral("            game_adventure_trigger_message(%1u);\n")
                            .arg(r.toggleFalseDialogueNode);
                    action+=QStringLiteral("        }\n");
                }
            }
            if (r.interactItemName.isEmpty() && r.interactDialogueNode >= 0) {
                const QString dialogueFunction=r.interactDialogueMode==QStringLiteral("single")
                    ? QStringLiteral("game_adventure_trigger_message")
                    : r.interactDialogueMode==QStringLiteral("sequence")
                        ? QStringLiteral("game_adventure_trigger_sequence")
                        : QStringLiteral("game_adventure_trigger_dialogue");
                action+=QStringLiteral("        %1(%2u);\n")
                    .arg(dialogueFunction).arg(r.interactDialogueNode);
            }
        }
        const bool stop = r.objectType == QStringLiteral("trigger") && r.triggerMusicAction == QStringLiteral("stop");
        const bool play = r.objectType == QStringLiteral("trigger") && r.triggerMusicAction == QStringLiteral("play") && musicById.contains(r.triggerMusicId);
        if (action.isEmpty() && !stop && !play) continue;
        const QMap<QString, QString> f{{QStringLiteral("INDEX"), number(i)},
            {QStringLiteral("ACTION_BODY"), action},
            {QStringLiteral("MUSIC_STOP"), flag(stop)},
            {QStringLiteral("MUSIC_PLAY"), flag(play)},
            {QStringLiteral("MUSIC_SYMBOL"), musicSymbol(r)}};
        if (!renderWorldSection(QStringLiteral("TRIGGER_ACTION"), f, &triggerBody)) return false;
    }
    // Stage 5.166.63: run independent graphs when their input states actually
    // change during ordinary Trigger actions, regardless of which Trigger owns
    // them. Do not infer dependencies from the configured target-action list.
    // Every graph result is still captured before any branch actions run.
    for (int ownerIndex=0; ownerIndex<nw+np; ++ownerIndex) {
        const bool pickupOwner=ownerIndex>=nw;
        const int pickupIndex=ownerIndex-nw;
        const Resource &owner=pickupOwner?*pickups.at(pickupIndex):*platforms.at(ownerIndex);
        if(owner.logicNodes.isEmpty())continue;
        if(pickupOwner) {
            for(const QJsonValue &entry:owner.logicNodes) {
                const QString op=entry.toObject().value(QStringLiteral("op")).toString();
                if(op==QStringLiteral("stat_compare") || op==QStringLiteral("quest_done")) {
                    if(error)*error=tr("Persistent Compare/Quest conditions must be owned by a placed Game Object, not a Collectable template.");
                    return false;
                }
            }
        }
        QVector<SidboxVisualLogic::Node> nodes;
        QVector<int> sorted;
        QString issue;
        QSet<QString> localIds;
        for(auto it=objectSlot.constBegin();it!=objectSlot.constEnd();++it)localIds.insert(it.key());
        if(!SidboxVisualLogic::read(owner.logicNodes,&nodes,&issue) ||
           !SidboxVisualLogic::order(nodes,localIds,&sorted,&issue)) {
            if(error)*error=tr("Game Object '%1' invalid logic graph: %2").arg(owner.name,issue);
            return false;
        }
        for(const SidboxVisualLogic::Node &node:nodes) {
            if(node.op==QStringLiteral("stat_compare"))hasStatCompare=true;
            if(node.op==QStringLiteral("quest_done"))hasQuestCondition=true;
        }
        for(const SidboxVisualLogic::Node &node:nodes)
            for(const SidboxVisualLogic::Input &input:node.inputs)
                if(input.kind==QStringLiteral("event") && !objectSlot.contains(input.id)) {
                    if(error)*error=tr("Game Object '%1' logic node '%2' reads unknown event '%3'.")
                        .arg(owner.name,node.id,input.id);
                    return false;
                }
        QSet<QString> graphInputs;
        for(const SidboxVisualLogic::Node &node:nodes)
            for(const SidboxVisualLogic::Input &input:node.inputs)
                if(input.kind==QStringLiteral("object"))graphInputs.insert(input.id);
        QStringList graphInputIds=graphInputs.values();
        graphInputIds.sort(); // Deterministic generated C and event order.
        QStringList activationEvents;
        // Keep ordinary Game Object/event activation separate from persistent
        // stat/quest watches: a sibling Compare must not replay another node's
        // TRUE dialogue when Health or a quest changes.
        const QString statWatch=QStringLiteral("cg_logic_stat_changed_%1").arg(ownerIndex);
        const QString questWatch=QStringLiteral("cg_logic_quest_changed_%1").arg(ownerIndex);
        bool watchesStat=false, watchesQuest=false;
        QSet<QString> graphEventInputs;
        for(const SidboxVisualLogic::Node &node:nodes)
            for(const SidboxVisualLogic::Input &input:node.inputs)
                if(input.kind==QStringLiteral("event"))graphEventInputs.insert(input.id);
        QStringList sortedGraphEvents=graphEventInputs.values();
        sortedGraphEvents.sort();
        for(const QString &eventId:sortedGraphEvents)
            activationEvents.append(objectSlot.value(eventId));
        for(const SidboxVisualLogic::Node &node:nodes) {
            if(node.op==QStringLiteral("stat_compare"))watchesStat=true;
            if(node.op==QStringLiteral("quest_done"))watchesQuest=true;
        }
        if(pickupOwner) {
            hasNamedPickupLogic=true;
            activationEvents.append(QStringLiteral("cg_named_pickup_sources[%1u]").arg(pickupIndex));
        }
        if(owner.objectType==QStringLiteral("trigger"))
            activationEvents.append(QStringLiteral("cg_gwi_platforms[%1].trigger_fired").arg(ownerIndex));
        else if(owner.objectType==QStringLiteral("enemy"))
            activationEvents.append(QStringLiteral("(cg_current_defeat_owner == %1u)")
                .arg(ownerIndex));
        // A graph owned by another Game Object can read the virtual Trigger
        // switch. Run it on the activation that changes the latch, not only
        // when its own physical object changes state.
        for(const QString &stateId:graphInputIds) {
            if(!stateId.startsWith(QStringLiteral("@triggerstate:")))continue;
            const QString triggerId=stateId.mid(QStringLiteral("@triggerstate:").size());
            for(int sourceIndex=0;sourceIndex<nw;++sourceIndex)
                if(platforms.at(sourceIndex)->id==triggerId &&
                   platforms.at(sourceIndex)->objectType==QStringLiteral("trigger")) {
                    activationEvents.append(QStringLiteral("cg_gwi_platforms[%1].trigger_fired")
                        .arg(sourceIndex));
                    break;
                }
        }
        // Any real named event can own its gate: a breakable, enemy, lift,
        // hazard, door, checkpoint or pickup. Do not require an action wire.
        unsigned int wantedEvents=0u;
        for(const SidboxVisualLogic::Node &node:nodes)
            for(const SidboxVisualLogic::Input &input:node.inputs)
                if(input.kind==QStringLiteral("event")) {
                    const QString eventId=input.id;
                    if(eventId==QStringLiteral("@event:hit:")+owner.id)wantedEvents|=1u;
                    if(eventId==QStringLiteral("@event:destroy:")+owner.id)wantedEvents|=2u;
                    if(eventId==QStringLiteral("@event:player_hit:")+owner.id)wantedEvents|=4u;
                    if(eventId==QStringLiteral("@event:enter:")+owner.id)wantedEvents|=8u;
                    if(eventId==QStringLiteral("@event:save:")+owner.id)wantedEvents|=16u;
                    if(eventId==QStringLiteral("@event:arrival:")+owner.id)wantedEvents|=32u;
                }
        if(wantedEvents && !pickupOwner) {
            hasNamedPlatformLogic=true;
            activationEvents.append(QStringLiteral("(cg_named_event_sources[%1u] & %2u)")
                .arg(ownerIndex).arg(wantedEvents));
        }
        // A graph hosted by any enemy must respond when the OTHER enemy in
        // its condition is defeated. State deltas alone cannot see a death
        // which happened before the per-event graph callback begins.
        QSet<int> defeatWatchIndexes;
        for (const QString &enemyId:graphInputIds)
            for(int enemyIndex=0;enemyIndex<nw;++enemyIndex)
                if(platforms.at(enemyIndex)->id==enemyId &&
                   platforms.at(enemyIndex)->objectType==QStringLiteral("enemy"))
                    defeatWatchIndexes.insert(enemyIndex);
        // A stompable's gold ON DEFEAT actions may toggle a lift/switch that
        // another graph reads. Those actions have already run when this graph
        // callback begins, so the before/after state snapshot alone misses it.
        for(int enemyIndex=0;enemyIndex<nw;++enemyIndex) {
            const Resource &enemy=*platforms.at(enemyIndex);
            if(enemy.objectType!=QStringLiteral("enemy"))continue;
            bool modifiesInput=graphInputs.contains(enemy.targetObjectId) &&
                (enemy.targetAction==QStringLiteral("enable") ||
                 enemy.targetAction==QStringLiteral("disable") ||
                 enemy.targetAction==QStringLiteral("toggle"));
            for(const Resource::LinkedAction &action:enemy.enemyDefeatExtraActions)
                if(graphInputs.contains(action.objectId))modifiesInput=true;
            if(modifiesInput)defeatWatchIndexes.insert(enemyIndex);
        }
        if(owner.objectType==QStringLiteral("lift"))defeatWatchIndexes.clear();
        QList<int> sortedDefeatIndexes=defeatWatchIndexes.values();
        std::sort(sortedDefeatIndexes.begin(),sortedDefeatIndexes.end());
        for(int enemyIndex:sortedDefeatIndexes)
            activationEvents.append(QStringLiteral("(cg_current_defeat_owner == %1u)")
                .arg(enemyIndex));
        // Named object events use their source's one-frame pulse because
        // graph snapshots are taken AFTER event actions have changed inputs.
        for(int sourceIndex=0;sourceIndex<nw && owner.objectType!=QStringLiteral("lift");++sourceIndex) {
            const Resource &source=*platforms.at(sourceIndex);
            if(source.objectType==QStringLiteral("goto_world"))continue;
            unsigned int watchedEvents=0u;
            for(auto it=source.eventActions.constBegin();it!=source.eventActions.constEnd();++it) {
                unsigned int bit=it.key()==QStringLiteral("hit")?1u:
                    it.key()==QStringLiteral("destroy")?2u:
                    it.key()==QStringLiteral("player_hit")?4u:
                    it.key()==QStringLiteral("enter")?8u:
                    it.key()==QStringLiteral("save")?16u:
                    it.key()==QStringLiteral("arrival")?32u:0u;
                for(const QJsonValue &value:it.value().toArray())
                    if(graphInputs.contains(value.toObject().value(QStringLiteral("objectId")).toString()))
                        watchedEvents|=bit;
            }
            if(watchedEvents) {
                hasNamedPlatformLogic=true;
                activationEvents.append(QStringLiteral("(cg_named_event_sources[%1u] & %2u)")
                    .arg(sourceIndex).arg(watchedEvents));
            }
        }
        for(int sourceIndex=0;sourceIndex<np && owner.objectType!=QStringLiteral("lift");++sourceIndex) {
            const Resource &source=*pickups.at(sourceIndex);
            bool changes=false;
            for(const QJsonValue &value:source.eventActions.value(QStringLiteral("pickup")).toArray())
                if(graphInputs.contains(value.toObject().value(QStringLiteral("objectId")).toString()))
                    changes=true;
            if(changes) {
                hasNamedPickupLogic=true;
                activationEvents.append(QStringLiteral("cg_named_pickup_sources[%1u]").arg(sourceIndex));
            }
        }
        for(int inputIndex=0;inputIndex<graphInputIds.size();++inputIndex) {
            const QString inputId=graphInputIds.at(inputIndex);
            const QString source=objectSlot.value(inputId);
            const QString state=inputId.startsWith(QStringLiteral("@triggerstate:"))
                ? QStringLiteral("(%1 != 0u)").arg(source)
                : QStringLiteral("(%1.active != 0u)").arg(source);
            const QString before=QStringLiteral("cg_logic_before_%1_%2")
                .arg(ownerIndex).arg(inputIndex);
            graphSnapshotsBody+=QStringLiteral(
                "    const unsigned char %1 = %2;\n")
                .arg(before,state);
            if(owner.objectType!=QStringLiteral("lift"))
                activationEvents.append(QStringLiteral("(%1 != %2)")
                    .arg(before,state));
        }
        const QString run=QStringLiteral("cg_logic_run_%1").arg(ownerIndex);
        const QString baseRun=QStringLiteral("cg_logic_base_run_%1").arg(ownerIndex);
        graphEvaluationBody+=QStringLiteral("    const unsigned char %1 = (%2) ? 1u : 0u;\n")
            .arg(baseRun,activationEvents.isEmpty() ? QStringLiteral("0") :
                 activationEvents.join(QStringLiteral(" || ")));
        QStringList ownerWatches{baseRun};
        if(watchesStat) {
            graphEvaluationBody+=QStringLiteral(
                "    const unsigned char %1 = "
                "(gameplayer_stat_revision() != cg_logic_seen_stat_revision || "
                "gameworlds_state()->health != cg_logic_seen_health) ? 1u : 0u;\n")
                .arg(statWatch);
            ownerWatches.append(statWatch);
        }
        if(watchesQuest) {
            graphEvaluationBody+=QStringLiteral(
                "    const unsigned char %1 = "
                "(gameworlds_quest_revision() != cg_logic_seen_quest_revision) ? 1u : 0u;\n")
                .arg(questWatch);
            ownerWatches.append(questWatch);
        }
        graphEvaluationBody+=QStringLiteral("    const unsigned char %1 = (%2) ? 1u : 0u;\n")
            .arg(run,ownerWatches.join(QStringLiteral(" || ")));
        QHash<QString,QString> expressionNames;
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            const QString name=QStringLiteral("cg_logic_%1_%2").arg(ownerIndex).arg(index);
            graphEvaluationBody+=QStringLiteral("    unsigned char %1 = 0u;\n").arg(name);
            expressionNames.insert(node.id,name);
        }
        graphEvaluationBody+=QStringLiteral("    if (%1) {\n").arg(run);
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            graphEvaluationBody+=QStringLiteral("        %1 = ((%2) ? 1u : 0u);\n")
                .arg(expressionNames.value(node.id),
                     SidboxVisualLogic::expression(node,objectSlot,expressionNames));
        }
        graphEvaluationBody+=QStringLiteral("    }\n");
        // A one-frame pulse is an event, not a persistent FALSE state.
        // A state change elsewhere must never replay an event gate's FALSE
        // branch; only the owning event can dispatch that node.
        QHash<QString,QString> nodePulseGate;
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            QStringList pulses;
            for(const SidboxVisualLogic::Input &input:node.inputs) {
                if(input.kind==QStringLiteral("event"))pulses.append(objectSlot.value(input.id));
                if(input.kind==QStringLiteral("node") && nodePulseGate.contains(input.id))
                    pulses.append(nodePulseGate.value(input.id));
            }
            if(!pulses.isEmpty())nodePulseGate.insert(node.id,pulses.join(QStringLiteral(" || ")));
        }
        // A persistent change may recompute every node expression, but it may
        // dispatch ONLY nodes depending on that particular watched condition.
        // Compute transitive dependencies in topological order so AND/OR gates
        // consuming a COMPARE (or QUEST STATE) are notified too.
        QHash<QString,bool> nodeNeedsStat, nodeNeedsQuest;
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            bool stat=node.op==QStringLiteral("stat_compare");
            bool quest=node.op==QStringLiteral("quest_done");
            for(const SidboxVisualLogic::Input &input:node.inputs) {
                if(input.kind!=QStringLiteral("node"))continue;
                stat |= nodeNeedsStat.value(input.id,false);
                quest |= nodeNeedsQuest.value(input.id,false);
            }
            nodeNeedsStat.insert(node.id,stat);
            nodeNeedsQuest.insert(node.id,quest);
        }
        graphDispatchBody+=QStringLiteral("    if (%1) {\n").arg(run);
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            QStringList nodeWatches{baseRun};
            if(nodeNeedsStat.value(node.id,false))nodeWatches.append(statWatch);
            if(nodeNeedsQuest.value(node.id,false))nodeWatches.append(questWatch);
            graphDispatchBody+=QStringLiteral("        if (%1) {\n")
                .arg(nodeWatches.join(QStringLiteral(" || ")));
            // Event-dependent results and branches only fire for a real pulse.
            // Do not turn an inactive event into a repeating FALSE action.
            if(nodePulseGate.contains(node.id))
                graphDispatchBody+=QStringLiteral("        if (%1) {\n").arg(nodePulseGate.value(node.id));
            // RESULT is a direct state binding. It is not an Enable action
            // duplicated on TRUE and FALSE: FALSE must assign zero.
            for(const QString &targetId:node.resultTargets)
                graphDispatchBody+=QStringLiteral("        %1.active = %2 ? 1u : 0u;\n")
                    .arg(objectSlot.value(targetId),expressionNames.value(node.id));
            graphDispatchBody+=QStringLiteral("        if (%1) {\n").arg(expressionNames.value(node.id));
            for(const bool yes:{true,false}) {
                if(!yes)graphDispatchBody+=QStringLiteral("        } else {\n");
                for(const QJsonValue &v:yes?node.trueActions:node.falseActions) {
                    const QJsonObject entry=v.toObject();
                    Resource target=owner;
                    target.targetObjectId=entry.value(QStringLiteral("objectId")).toString();
                    target.targetAction=entry.value(QStringLiteral("action")).toString();
                    if (!yes && target.targetAction==QStringLiteral("enable") &&
                        target.targetObjectId.startsWith(QStringLiteral("@player_weather:"))) {
                        // Stage 5.166.67 compatibility: a TRUE and FALSE wire to
                        // the same weather node used to be saved as Enable/Enable.
                        for(const QJsonValue &trueValue:node.trueActions) {
                            const QJsonObject trueLink=trueValue.toObject();
                            if(trueLink.value(QStringLiteral("objectId")).toString()==target.targetObjectId &&
                               trueLink.value(QStringLiteral("action")).toString()==QStringLiteral("enable")) {
                                target.targetAction=QStringLiteral("disable");
                                break;
                            }
                        }
                    }
                    if(!queueTargetAction(target,&graphDispatchBody))return false;
                }
                const int dialogue=yes?node.trueDialogue:node.falseDialogue;
                if(dialogue>=0)
                    graphDispatchBody+=QStringLiteral("            game_adventure_trigger_message(%1u);\n")
                        .arg(dialogue);
            }
            graphDispatchBody+=QStringLiteral("        }\n");
            if(nodePulseGate.contains(node.id))graphDispatchBody+=QStringLiteral("        }\n");
            graphDispatchBody+=QStringLiteral("        }\n"); // per-node watch guard
        }
        graphDispatchBody+=QStringLiteral("    }\n");

        QHash<QString,bool> nodeDependsOnPulse;
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            bool pulse=false;
            for(const SidboxVisualLogic::Input &input:node.inputs)
                pulse |= input.kind==QStringLiteral("event") ||
                    (input.kind==QStringLiteral("node") && nodeDependsOnPulse.value(input.id,false));
            nodeDependsOnPulse.insert(node.id,pulse);
        }
        if(owner.objectType==QStringLiteral("lift"))continue;
        // Initial world entry and checkpoint restore are NOT Trigger events.
        // Apply RESULT state bindings and deterministic enable/disable or
        // weather/lighting commands. Do not play dialogues, toggle any target,
        // or request world travel. Runtime Trigger behaviour above is unchanged.
        QHash<QString,QString> initialNames;
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            if(nodeDependsOnPulse.value(node.id))continue;
            const QString name=QStringLiteral("cg_initial_logic_%1_%2")
                .arg(ownerIndex).arg(index);
            initialNames.insert(node.id,name);
        }
        graphInitialSyncBody+=QStringLiteral("    /* Independent logic graph owned by Game Object %1 */\n").arg(ownerIndex);
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            if(nodeDependsOnPulse.value(node.id))continue;
            graphInitialSyncBody+=QStringLiteral("    const unsigned char %1 = ((%2) ? 1u : 0u);\n")
                .arg(initialNames.value(node.id),
                     SidboxVisualLogic::expression(node,objectSlot,initialNames));
        }
        // RESULT must be applied before evaluating the next Trigger's graph.
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            if(nodeDependsOnPulse.value(node.id))continue;
            for(const QString &targetId:node.resultTargets)
                graphInitialSyncBody+=QStringLiteral("    %1.active = %2;\n")
                    .arg(objectSlot.value(targetId),initialNames.value(node.id));
        }
        for(int index:sorted) {
            const SidboxVisualLogic::Node &node=nodes[index];
            if(nodeDependsOnPulse.value(node.id))continue;
            QString onTrue,onFalse;
            for(const bool yes:{true,false}) {
                QString *dest=yes?&onTrue:&onFalse;
                for(const QJsonValue &v:yes?node.trueActions:node.falseActions) {
                    const QJsonObject entry=v.toObject();
                    const QString targetId=entry.value(QStringLiteral("objectId")).toString();
                    const QString action=entry.value(QStringLiteral("action")).toString();
                    // Enable/disable are idempotent. Weather/time use enable
                    // as a command, also safe on world entry. Exclude world
                    // travel unconditionally and never replay a Toggle.
                    if(action==QStringLiteral("toggle") ||
                       targetId.startsWith(QStringLiteral("@player_world:")) ||
                       targetId.startsWith(QStringLiteral("@quest_event:")))continue;
                    if(action!=QStringLiteral("enable") &&
                       action!=QStringLiteral("disable"))continue;
                    Resource target=owner;
                    target.targetObjectId=targetId;
                    target.targetAction=action;
                    if (!yes && target.targetAction==QStringLiteral("enable") &&
                        targetId.startsWith(QStringLiteral("@player_weather:"))) {
                        for(const QJsonValue &trueValue:node.trueActions) {
                            const QJsonObject trueLink=trueValue.toObject();
                            if(trueLink.value(QStringLiteral("objectId")).toString()==targetId &&
                               trueLink.value(QStringLiteral("action")).toString()==QStringLiteral("enable")) {
                                target.targetAction=QStringLiteral("disable");
                                break;
                            }
                        }
                    }
                    if(!targetAction(target,dest))return false;
                }
            }
            if(onTrue.isEmpty() && onFalse.isEmpty())continue;
            graphInitialSyncBody+=QStringLiteral("    if (%1) {\n%2    } else {\n%3    }\n")
                .arg(initialNames.value(node.id),onTrue,onFalse);
        }
    }
    if (!usedSfx.isEmpty()) for (int i = 0; i < nw; ++i) {
        const Resource &r = *platforms.at(i);
        const QString soundId = r.objectType == QStringLiteral("conveyor") ? r.sfxAmbient
            : r.objectType == QStringLiteral("hazard") ? r.sfxHazardAmbient
            : r.objectType == QStringLiteral("lift") ? r.sfxMove : QString();
        if (soundId.isEmpty()) continue;
        QMap<QString, QString> f = audioFields(soundId, i, r.audioRadius);
        const int step = r.audioFadeFrames <= 0 ? 255 : qMax(1, (255 + r.audioFadeFrames - 1) / r.audioFadeFrames);
        f.insert(QStringLiteral("FADE_STEP"), number(step));
        if (!renderWorldSection(QStringLiteral("LOOP_FADE"), f, &drawBody)) return false;
    }
    // The generated programmer guide is a documentation rule, not executable C.
    // Keep its feature-specific paragraphs in the SDK alongside World Items C/H.
    const QMap<QString, QString> guideFields{
        {QStringLiteral("HAS_ITEMS"), QStringLiteral("1")},
        {QStringLiteral("HAS_WORLDS_WITH_MAP"), flag(nw && m_tilemapEnabled)},
        {QStringLiteral("HAS_WORLDS"), flag(nw != 0)},
        {QStringLiteral("HAS_TILEMAP"), flag(m_tilemapEnabled)},
        {QStringLiteral("HAS_PICKUPS"), flag(np != 0)},
        {QStringLiteral("HAS_REWARDS"), flag(hasBreakRewards)},
        {QStringLiteral("HAS_TRIGGERS"), flag(nt != 0)},
        {QStringLiteral("HAS_AUDIO"), flag(!usedSfx.isEmpty())},
        {QStringLiteral("PICKUP_COUNT"), number(np)},
        {QStringLiteral("WORLD_OBJECT_COUNT"), number(nw)},
        {QStringLiteral("TRIGGER_COUNT"), number(nt)}
    };
    if (!renderWorldRule(QStringLiteral("gameworlditems.ruletxt"), guideFields, &guide))
        return false;
    // All generated World Items C comes from gameworlditems.rulec/.ruleh.
    QMap<QString, QString> headerFields;
    headerFields.insert(QStringLiteral("HAS_ITEMS"), QStringLiteral("1"));
    headerFields.insert(QStringLiteral("PICKUP_COUNT"), QString::number(np));
    headerFields.insert(QStringLiteral("WORLD_OBJECT_COUNT"), QString::number(nw));
    headerFields.insert(QStringLiteral("HAS_WORLDS"), nw ? QStringLiteral("1") : QStringLiteral("0"));
    headerFields.insert(QStringLiteral("HAS_PICKUPS"), np ? QStringLiteral("1") : QStringLiteral("0"));
    headerFields.insert(QStringLiteral("HAS_TRIGGERS"), nt ? QStringLiteral("1") : QStringLiteral("0"));
    if (!renderWorldRule(QStringLiteral("gameworlditems.ruleh"), headerFields, &h)) return false;
    QMap<QString, QString> sourceFields;
    sourceFields.insert(QStringLiteral("HAS_ITEMS"), QStringLiteral("1"));
    sourceFields.insert(QStringLiteral("HAS_ADVENTURE"),flag(hasAdventure()));
    sourceFields.insert(QStringLiteral("HAS_PARTICLE_EMITTERS"), flag(particleEmitterCount > 0));
    sourceFields.insert(QStringLiteral("PARTICLE_EMITTER_COUNT"), number(particleEmitterCount));
    sourceFields.insert(QStringLiteral("PARTICLE_EMITTER_ROWS"), particleEmitterRows);
    sourceFields.insert(QStringLiteral("HAS_PATHS"), flag(anyPath));
    sourceFields.insert(QStringLiteral("HAS_TILEMAP_ANY"), flag((np || nw) && m_tilemapEnabled));
    sourceFields.insert(QStringLiteral("HAS_AUDIO"), flag(!usedSfx.isEmpty()));
    sourceFields.insert(QStringLiteral("DRAW_BEHIND_BODY"), drawBehindBody);
    sourceFields.insert(QStringLiteral("DRAW_BODY"), drawBody);
    sourceFields.insert(QStringLiteral("WORLD_DECLARATIONS"), worldDeclarations);
    sourceFields.insert(QStringLiteral("STAMP_DECLARATIONS"), stampDeclarations);
    sourceFields.insert(QStringLiteral("HAS_STAMPS"), flag(hasSpriteStamps));
    sourceFields.insert(QStringLiteral("AUDIO_WRAPPERS"), audioWrappers);
    sourceFields.insert(QStringLiteral("INIT_BODY"), worldInitBody);
    sourceFields.insert(QStringLiteral("UPDATE_BODY"), worldUpdateBody);
    sourceFields.insert(QStringLiteral("REWARD_SPAWN_ACTIONS"), rewardSpawnActions);
    sourceFields.insert(QStringLiteral("LOOT_RULE_ROWS"), lootRows);
    sourceFields.insert(QStringLiteral("LOOT_RULE_COUNT"), number(lootRuleCount));
    sourceFields.insert(QStringLiteral("LOOT_SLOT_COUNT"), number(lootSlotCount));
    sourceFields.insert(QStringLiteral("HAS_LOOT"), flag(hasLoot));
    for(int i=0;i<np;++i) {
        const Resource &r=*pickups.at(i);
        QString action;
        for(const QJsonValue &value:r.eventActions.value(QStringLiteral("pickup")).toArray()) {
            const QJsonObject link=value.toObject();
            Resource target=r;
            target.targetObjectId=link.value(QStringLiteral("objectId")).toString();
            target.targetAction=link.value(QStringLiteral("action")).toString();
            if(!queueTargetAction(target,&action))return false;
        }
        bool pickupGraph=watchedLogicEvents.contains(QStringLiteral("@event:pickup:")+r.id);
        if(!r.logicNodes.isEmpty())pickupGraph=true;
        if(!action.isEmpty() || pickupGraph) {
            action.prepend(QStringLiteral("        cg_named_pickup_sources[%1u]=1u;\n").arg(i));
            const QMap<QString,QString> f{{QStringLiteral("INDEX"),number(i)},
                {QStringLiteral("ACTION_BODY"),action}};
            if(!renderWorldSection(QStringLiteral("PICKUP_TARGET_ACTION"),f,&checkBody))return false;
        }
    }
    // ON COMPLETED is a one-shot quest transition. Ordinary targets and its
    // optional Adventure dialogue are both enqueued by the same callback.
    // Saving/restoring an already completed quest never replays this event.
    QString questCompleteActions;
    QSet<QString> questCompleteKeys;
    for(auto it=questCompletionActions.constBegin();it!=questCompletionActions.constEnd();++it)
        questCompleteKeys.insert(it.key());
    for(auto it=questCompletionDialogues.constBegin();it!=questCompletionDialogues.constEnd();++it)
        questCompleteKeys.insert(it.key());
    QStringList sortedQuestCompleteKeys;
    for(const QString &id:questCompleteKeys)sortedQuestCompleteKeys.append(id);
    sortedQuestCompleteKeys.sort();
    for(const QString &questId:sortedQuestCompleteKeys) {
        if(!questCompletedIds.contains(questId)) {
            if(error)*error=tr("Quest completion link references removed quest '%1'.").arg(questId);
            return false;
        }
        QString commands;
        const QJsonArray links=questCompletionActions.value(questId).toArray();
        if(links.size()>64) {
            if(error)*error=tr("Quest '%1' has more than 64 completion actions.").arg(questId);
            return false;
        }
        for(const QJsonValue &value:links) {
            const QJsonObject link=value.toObject();
            const QString targetId=link.value(QStringLiteral("objectId")).toString();
            const QString operation=link.value(QStringLiteral("action")).toString();
            if(!actionTargetExists(targetId) ||
               (operation!=QStringLiteral("enable") && operation!=QStringLiteral("disable") &&
                operation!=QStringLiteral("toggle")) ||
               ((targetId.startsWith(QStringLiteral("@quest_event:")) ||
                 targetId.startsWith(QStringLiteral("@player_time:")) ||
                 targetId.startsWith(QStringLiteral("@player_world:"))) &&
                operation!=QStringLiteral("enable"))) {
                if(error)*error=tr("Quest '%1' has invalid ON COMPLETED target '%2'.")
                    .arg(questId,targetId);
                return false;
            }
            Resource action;
            action.targetObjectId=targetId;
            action.targetAction=operation;
            if(!queueTargetAction(action,&commands))return false;
        }
        if(questCompletionDialogues.contains(questId)) {
            const QJsonObject dialogue=questCompletionDialogues.value(questId).toObject();
            const int number=dialogue.value(QStringLiteral("dialogueNode")).toInt(-1);
            if(number<0 || number>=questDialogueCount) {
                if(error)*error=tr("Quest '%1' has invalid ON COMPLETED dialogue #%2. Select a valid Adventure dialogue.")
                    .arg(questId).arg(number);
                return false;
            }
            const QString mode=dialogue.value(QStringLiteral("mode"))
                .toString(QStringLiteral("conversation"));
            if(mode!=QStringLiteral("single") && mode!=QStringLiteral("sequence") &&
               mode!=QStringLiteral("conversation")) {
                if(error)*error=tr("Quest '%1' has an unsupported ON COMPLETED dialogue mode.").arg(questId);
                return false;
            }
            const QString method=mode==QStringLiteral("single")?QStringLiteral("message"):
                mode==QStringLiteral("sequence")?QStringLiteral("sequence"):
                QStringLiteral("dialogue");
            // Converted into a FIFO command below with every other dialogue.
            commands+=QStringLiteral("        game_adventure_trigger_%1(%2u);\n")
                .arg(method).arg(number);
        }
        if(!commands.isEmpty())
            questCompleteActions+=QStringLiteral("    if(strcmp(quest_id,%1)==0) {\n%2        cg_action_drain();\n        return;\n    }\n")
                .arg(GameQuestGen::quoteC(questId),commands);
    }
    // Stage 119: dialogue actions share the SAME FIFO order as enable/disable/
    // toggle commands. The Adventure runtime then serialises visible modal
    // conversations (including requests from other subsystems).
    const QRegularExpression dialogueCall(
        QStringLiteral(R"(game_adventure_trigger_(message|dialogue|sequence)\((\d+)u\);)"));
    auto queueGeneratedDialogues = [&](QString *body) -> bool {
        QString queued;
        int cursor=0;
        auto matches=dialogueCall.globalMatch(*body);
        while(matches.hasNext()) {
            const QRegularExpressionMatch m=matches.next();
            queued+=body->mid(cursor,m.capturedStart()-cursor);
            if(queuedActionCount>=65535u) {
                if(error)*error=tr("Too many generated dialogue commands in this world.");
                return false;
            }
            ++queuedActionCount;
            queuedActionCases+=QStringLiteral(
                "        case %1u: (void)game_adventure_trigger_%2(%3u); break;\n")
                .arg(queuedActionCount).arg(m.captured(1),m.captured(2));
            queued+=QStringLiteral("(void)cg_action_enqueue(%1u);").arg(queuedActionCount);
            cursor=m.capturedEnd();
        }
        queued+=body->mid(cursor);
        *body=queued;
        return true;
    };
    for(QString *body:{&triggerBody,&graphDispatchBody,&eventActions,
                        &eventSaveActions,&eventEnterActions,&checkBody,
                        &interactionDialogueActions,&questCompleteActions})
        if(!queueGeneratedDialogues(body))return false;
    sourceFields.insert(QStringLiteral("WORLD_EVENT_ACTIONS"), eventActions);
    sourceFields.insert(QStringLiteral("EVENT_SAVE_ACTIONS"),eventSaveActions);
    sourceFields.insert(QStringLiteral("EVENT_ENTER_ACTIONS"),eventEnterActions);
    sourceFields.insert(QStringLiteral("CHECK_ACTIONS"), checkBody);
    sourceFields.insert(QStringLiteral("TRIGGER_ACTIONS"), triggerBody);
    sourceFields.insert(QStringLiteral("GRAPH_SNAPSHOTS"), graphSnapshotsBody);
    sourceFields.insert(QStringLiteral("GRAPH_EVALUATIONS"), graphEvaluationBody);
    sourceFields.insert(QStringLiteral("GRAPH_DISPATCH"), graphDispatchBody);
    sourceFields.insert(QStringLiteral("ACTION_QUEUE_CASES"), queuedActionCases);
    sourceFields.insert(QStringLiteral("QUEST_COMPLETE_ACTIONS"),questCompleteActions);
    sourceFields.insert(QStringLiteral("GRAPH_INITIAL_SYNC"), graphInitialSyncBody);
    sourceFields.insert(QStringLiteral("INTERACT_ROWS"), interactionRows);
    sourceFields.insert(QStringLiteral("INTERACT_SOUND_ACTIONS"), interactionSoundActions);
    sourceFields.insert(QStringLiteral("INTERACT_PREFLIGHT_ACTIONS"),interactionPreflightActions);
    sourceFields.insert(QStringLiteral("INTERACT_DIALOGUE_ACTIONS"),interactionDialogueActions);
    sourceFields.insert(QStringLiteral("INTERACT_WRONG_DIALOGUE_ACTIONS"),interactionWrongDialogueActions);
    sourceFields.insert(QStringLiteral("HAS_INTERACT_OUTCOMES"),flag(hasInteractionOutcomes));
    sourceFields.insert(QStringLiteral("STATE_ACTIVE_FRAMES"),activeStateFrames);
    sourceFields.insert(QStringLiteral("STATE_INACTIVE_FRAMES"),inactiveStateFrames);
    bool hasInactiveStateFrames=false;
    for(const Resource *resource:platforms)
        if(resource->inactiveStateFrame>=0) {hasInactiveStateFrames=true;break;}
    sourceFields.insert(QStringLiteral("HAS_INACTIVE_STATE_FRAMES"),flag(hasInactiveStateFrames));
    sourceFields.insert(QStringLiteral("PICKUP_COUNT"), number(np));
    sourceFields.insert(QStringLiteral("WORLD_OBJECT_COUNT"), number(nw));
    QStringList initialActive;
    for (const Resource *item : platforms)
        initialActive << (item->objectInitiallyActive ? QStringLiteral("1") : QStringLiteral("0"));
    sourceFields.insert(QStringLiteral("WORLD_OBJECT_INITIAL_ACTIVE"),initialActive.join(QStringLiteral(", ")));
    sourceFields.insert(QStringLiteral("HAS_WORLDS"), flag(nw != 0));
    sourceFields.insert(QStringLiteral("HAS_PICKUPS"), flag(np != 0));
    sourceFields.insert(QStringLiteral("HAS_TRIGGERS"), flag(nt != 0));
    bool hasEnemyLogic=false;
    for(const Resource *r:platforms)
        if(r->objectType==QStringLiteral("enemy") && !r->logicNodes.isEmpty())hasEnemyLogic=true;
    // Also re-evaluate Trigger-owned graphs that read enemy state when an
    // enemy is defeated, even when no Trigger fired that frame.
    bool hasDefeatGraphInput=hasEnemyLogic;
    for(const QString &eventId:watchedLogicEvents)
        if(eventId.startsWith(QStringLiteral("@event:defeat:")))hasDefeatGraphInput=true;
    for(const Resource *owner:platforms)
        for(const QJsonValue &entry:owner->logicNodes)
            for(const QJsonValue &raw:entry.toObject().value(QStringLiteral("inputs")).toArray())
                if(raw.toObject().value(QStringLiteral("kind")).toString()==QStringLiteral("event") &&
                   raw.toObject().value(QStringLiteral("id")).toString()==QStringLiteral("@event:defeat:")+owner->id)
                    hasDefeatGraphInput=true;
    for(const Resource *r:platforms)
        if(!r->logicNodes.isEmpty())
            for(const QJsonValue &value:r->logicNodes)
                for(const QJsonValue &raw:value.toObject().value(QStringLiteral("inputs")).toArray()) {
                    if(raw.toObject().value(QStringLiteral("kind")).toString()!=QStringLiteral("object"))continue;
                    const QString inputId=raw.toObject().value(QStringLiteral("id")).toString();
                    for(const Resource *target:platforms) {
                        if(target->objectType!=QStringLiteral("enemy"))continue;
                        if(target->id==inputId ||
                           ((target->targetObjectId==inputId &&
                             target->targetAction!=QStringLiteral("none"))))
                            hasDefeatGraphInput=true;
                        for(const Resource::LinkedAction &action:target->enemyDefeatExtraActions)
                            if(action.objectId==inputId)hasDefeatGraphInput=true;
                    }
                }
    bool namedPlatforms=false,namedPickups=false;
    for(const QString &eventId:watchedLogicEvents)
        if(eventId.startsWith(QStringLiteral("@event:pickup:"))) {
            namedPickups=true;
            hasNamedPickupLogic=true;
        }
    for(int i=0;i<nw;++i)
        if(!platforms.at(i)->logicNodes.isEmpty()) {
            const Resource &host=*platforms.at(i);
            for(const QJsonValue &entry:host.logicNodes)
                for(const QJsonValue &value:entry.toObject().value(QStringLiteral("inputs")).toArray())
                    if(value.toObject().value(QStringLiteral("kind")).toString()==QStringLiteral("event") &&
                       value.toObject().value(QStringLiteral("id")).toString().startsWith(QStringLiteral("@event:"))) {
                        const QString kind=value.toObject().value(QStringLiteral("id")).toString().section(QLatin1Char(':'),1,1);
                        if(kind!=QStringLiteral("trigger") && kind!=QStringLiteral("defeat")) {
                            namedPlatforms=true;
                            hasNamedPlatformLogic=true;
                        }
                    }
        }
    for(const Resource *source:platforms)
        for(auto it=source->eventActions.constBegin();it!=source->eventActions.constEnd();++it)
            if(!it.value().toArray().isEmpty())namedPlatforms=true;
    for(const Resource *source:pickups) {
        if(!source->eventActions.value(QStringLiteral("pickup")).toArray().isEmpty() ||
           !source->logicNodes.isEmpty())namedPickups=true;
        for(const QJsonValue &entry:source->logicNodes)
            for(const QJsonValue &value:entry.toObject().value(QStringLiteral("inputs")).toArray())
                if(value.toObject().value(QStringLiteral("kind")).toString()==QStringLiteral("event") &&
                   value.toObject().value(QStringLiteral("id")).toString()==QStringLiteral("@event:pickup:")+source->id) {
                    namedPickups=true;
                    hasNamedPickupLogic=true;
                }
    }
    sourceFields.insert(QStringLiteral("HAS_NAMED_EVENTS"),flag(namedPlatforms));
    sourceFields.insert(QStringLiteral("HAS_NAMED_PICKUP_EVENTS"),flag(namedPickups));
    sourceFields.insert(QStringLiteral("HAS_NAMED_EVENT_LOGIC"),flag(hasNamedPlatformLogic));
    sourceFields.insert(QStringLiteral("HAS_NAMED_PICKUP_LOGIC"),flag(hasNamedPickupLogic));
    sourceFields.insert(QStringLiteral("HAS_PICKUP_ONLY_LOGIC"),flag(nw==0 && hasNamedPickupLogic));
    sourceFields.insert(QStringLiteral("HAS_LOGIC_DISPATCH"),flag(nw!=0 || hasNamedPickupLogic));
    sourceFields.insert(QStringLiteral("HAS_STAT_COMPARE"),flag(hasStatCompare));
    sourceFields.insert(QStringLiteral("HAS_QUEST_CONDITION"),flag(hasQuestCondition));
    sourceFields.insert(QStringLiteral("HAS_ENEMY_STATE_LOGIC"),flag(hasDefeatGraphInput));
    sourceFields.insert(QStringLiteral("HAS_TILEMAP_WORLDS"), flag(nw && m_tilemapEnabled));
    sourceFields.insert(QStringLiteral("HAS_TILEMAP_PICKUPS"), flag(np && m_tilemapEnabled));
    sourceFields.insert(QStringLiteral("HAS_REWARDS"), flag(hasBreakRewards));
    sourceFields.insert(QStringLiteral("HAS_AUDIO_WORLDS"), flag(nw && !usedSfx.isEmpty()));
    sourceFields.insert(QStringLiteral("HAS_AUDIO_PICKUPS"), flag(np && !usedSfx.isEmpty()));
    bool eventPickups=hasNamedPickupLogic;
    for(const Resource *r:pickups) {
        if(!r->eventActions.value(QStringLiteral("pickup")).toArray().isEmpty() ||
           !r->logicNodes.isEmpty())eventPickups=true;
        for(const QJsonValue &node:r->logicNodes)
            for(const QJsonValue &value:node.toObject().value(QStringLiteral("inputs")).toArray())
                if(value.toObject().value(QStringLiteral("kind")).toString()==QStringLiteral("event") &&
                   value.toObject().value(QStringLiteral("id")).toString()==QStringLiteral("@event:pickup:")+r->id)
                    eventPickups=true;
    }
    sourceFields.insert(QStringLiteral("SAVE_PICKUP_ACTIVE"), flag(pickupSound || linkedKeys || eventPickups));
    sourceFields.insert(QStringLiteral("WORLD_SYMBOL"), worldSymbol);
    sourceFields.insert(QStringLiteral("WORLD_HEADER_FILENAME"), worldHeader);
    if (!renderWorldRule(QStringLiteral("gameworlditems.rulec"), sourceFields, &c)) return false;
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
    const QDir gameProject(QFileInfo(m_filePath).absolutePath());
    const bool hasSharedPlayer = QFileInfo::exists(GamePlayerProfile::profilePath(gameProject));
    QJsonObject sharedProfile;
    QString sharedError;
    if (hasSharedPlayer && !GamePlayerProfile::read(gameProject,&sharedProfile,&sharedError)) {
        if (error) *error = sharedError;
        return false;
    }
    const bool hasPhysics = hasMap && (player || hasSharedPlayer);
    // One starter drives ALL worlds. A collectible in another .sbgm still
    // needs gameworlds_check() every frame after the player travels there.
    bool anyWorldPickups = pickups > 0;
    for (const QString &world : gameProject.entryList({QStringLiteral("*.sbgm")}, QDir::Files)) {
        QFile candidate(gameProject.filePath(world));
        if (!candidate.open(QIODevice::ReadOnly)) continue;
        const QJsonDocument json = QJsonDocument::fromJson(candidate.readAll());
        for (const QJsonValue &entry : json.object().value(QStringLiteral("resources")).toArray()) {
            const QJsonObject item = entry.toObject();
            if (item.value(QStringLiteral("kind")).toString() == QStringLiteral("sprite") &&
                item.value(QStringLiteral("gameObject")).toObject().value(QStringLiteral("type")).toString()
                    == QStringLiteral("collectable")) { anyWorldPickups = true; break; }
        }
        if (anyWorldPickups) break;
    }
    const bool hasObjects = pickups || worldObjects;
    const bool hasMapOnly = hasMap && !player && !hasSharedPlayer;
    const QString playerName = player ? spriteSymbol(*player) : QString();
    // Stage 3.64: only show the player-animation integration when this
    // actual player resource has a saved .sbanim sidecar. Generated main.c
    // remains complete and buildable even before the C header is exported.
    const QString playerAnimationFile = hasSharedPlayer
        ? sharedProfile.value(QStringLiteral("animationFile")).toString()
        : (player ? player->animationFile : QString());
    // A shared .sbpi may name a FUTURE animation sidecar. Only teach the
    // animation calls once both the .sbanim AND its C header have been saved.
    const bool hasPlayerAnimation = hasPhysics && !playerAnimationFile.isEmpty()
        && (!hasSharedPlayer ||
            (QFileInfo::exists(gameProject.filePath(playerAnimationFile)) &&
             QFileInfo::exists(gameProject.filePath(QStringLiteral("gameanimations/player_anim.h")))));
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
    const QString worldBase = sidboxTilemapWorldBaseName(m_filePath);
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
    mainFlag("HAS_SHARED_PLAYER", hasSharedPlayer);
    mainFlag("HAS_WORLD_PLAYER", hasPhysics && worldObjects);
    mainFlag("HAS_PICKUPS", hasPhysics && anyWorldPickups);
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
    mainFields.insert(QStringLiteral("WORLD_BASE"), worldBase);
    mainFields.insert(QStringLiteral("PLAYER_SYMBOL"), playerName);
    for (int zone = 1; zone <= 8; ++zone)
        mainFields.insert(QStringLiteral("ZONE_%1").arg(zone),
            sidboxTilemapZoneMacroName(m_tilemap, zone));
    mainFlag("HAS_CUSTOM_COLLISION_SURFACES", hasMap &&
        (m_tilemap.collisions.contains(char(7)) || !m_tilemap.collisionPlacements.isEmpty()));
    mainFlag("HAS_LOOPS", hasMap && !m_tilemap.loops.isEmpty());
    // HUD is project-owned. An authored main.c is never overwritten;
    // the regenerated maingame.c.txt demonstrates the one-line call.
    mainFlag("HAS_TITLE", GameTitleRuntime::enabled(gameProject.absolutePath()));
    mainFlag("HAS_HUD", QFileInfo::exists(gameProject.filePath(QStringLiteral("gamehud.sbhud")))
        && QFileInfo::exists(gameProject.filePath(QStringLiteral("gamehelpers/gamehud.h"))));
    mainFlag("HAS_NO_MAP", !hasMap);
    mainFlag("HAS_MAP_ONLY", hasMapOnly);
    mainFlag("HAS_OBJECTS_NO_PHYSICS", !hasPhysics && hasObjects);
    mainFields.insert(QStringLiteral("TILEMAP_DESCRIPTION"),
        hasMap ? (m_tilemapExternal ? QStringLiteral("SD .map") : QStringLiteral("embedded C"))
               : QStringLiteral("none"));
    mainFields.insert(QStringLiteral("PLAYER_DESCRIPTION"),
        hasSharedPlayer ? QStringLiteral("shared players/player.sbpi") :
        (player ? safeCommentValue(spriteSymbol(*player)) : QStringLiteral("not found")));
    mainFields.insert(QStringLiteral("SPRITE_COUNT"), QString::number(spriteCount));
    mainFields.insert(QStringLiteral("PICKUP_COUNT"), QString::number(pickups));
    mainFields.insert(QStringLiteral("WORLD_OBJECT_COUNT"), QString::number(worldObjects));
    mainFields.insert(QStringLiteral("MUSIC_DESCRIPTION"), hasMusic ? QStringLiteral("present") : QStringLiteral("none"));
    mainFields.insert(QStringLiteral("SOUND_DESCRIPTION"), hasAudio ? QStringLiteral("present") : QStringLiteral("none"));
    mainFields.insert(QStringLiteral("SPLINE_COUNT"), QString::number(validSplineCount));
    mainFields.insert(QStringLiteral("ATTACHED_SPLINE_COUNT"),
                      QString::number(attachedSplineDescriptions.size()));
    mainFields.insert(QStringLiteral("PLAYER_ANIMATION_FILE"),
                      hasPlayerAnimation ? safeCommentValue(playerAnimationFile) : QString());
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
    // Scenery uses maingame.rulec, while managed pickups/platforms use
    // gameworlditems.rulec. Both must resolve stamps from the ORIGINAL PPB.
    const bool hasSceneryStamps = hasMap && std::any_of(m_resources.cbegin(), m_resources.cend(),
        [&](const Resource &r) {
            return r.kind == QStringLiteral("sprite") && !r.path.isEmpty() &&
                   r.objectType == QStringLiteral("decoration") && r.spriteStamp.active() &&
                   r.plane != QStringLiteral("background") &&
                   !adventureNpcIds.contains(r.id) && !(hasPhysics && &r == player);
        });
    mainFlag("HAS_SCENERY_STAMPS", hasSceneryStamps);
    mainFields.insert(QStringLiteral("SCENERY_STAMP_TABLES"), QString());
    mainFlag("PART_MAIN", true);
    mainFlag("PART_SPRITE_DRAW", false);
    mainFlag("SPRITE_STAMP_DRAW", false);
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
    // Each stamped decoration contributes lookup DATA only, never a PPB.
    QString sceneryStampTables;
    int sceneryStampNumber = 0;
    const auto appendSpriteRule = [&](const Resource &r, QString *buffer) -> bool {
        const bool stamped = r.spriteStamp.active();
        mainFlag("SPRITE_STAMP_DRAW", stamped);
        if (stamped) {
            if (QDir::cleanPath(resolvedPath(r.spriteStamp.sourcePath)) !=
                QDir::cleanPath(resolvedPath(r.path))) {
                if (error) *error = tr("Decoration stamp '%1' must reference its original PPB. Save the design to migrate it.").arg(r.name);
                return false;
            }
            QString stampError;
            if (r.spriteStamp.compose(cachedImage(resolvedPath(r.path)), &stampError).isNull()) {
                if (error) *error = tr("Invalid decoration stamp '%1': %2").arg(r.name, stampError);
                return false;
            }
            const QString symbol = QStringLiteral("gg_scenery_stamp_%1").arg(sceneryStampNumber++);
            QStringList cells;
            for (int cell : r.spriteStamp.cells)
                cells.append(cell < 0 ? QStringLiteral("0xFFFFFFFFu") :
                    QStringLiteral("0x%1u").arg(quint32(cell), 8, 16, QLatin1Char('0')));
            sceneryStampTables += QStringLiteral("static const uint32_t %1[] = { %2 };\n")
                .arg(symbol, cells.join(QStringLiteral(", ")));
            mainFields.insert(QStringLiteral("SPRITE_STAMP_ARRAY"), symbol);
            mainFields.insert(QStringLiteral("SPRITE_STAMP_COLUMNS"),
                QString::number(r.spriteStamp.width));
            mainFields.insert(QStringLiteral("SPRITE_STAMP_ROWS"),
                QString::number(r.spriteStamp.height));
        }
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
    mainFields.insert(QStringLiteral("SCENERY_STAMP_TABLES"), sceneryStampTables);
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
    // Stage 5.12: root gameassets/ is temporary export staging and is
    // removed after publishing. Read this WORLD's private snapshot first;
    // otherwise F5 would forget the embedded-PPB selection on the next build.
    const QDir project(QFileInfo(m_filePath).absolutePath());
    const QString world = sidboxTilemapWorldBaseName(m_filePath);
    const QStringList generatedSources = {
        project.filePath(QStringLiteral(".codergirl/worlds/") + world
                         + QStringLiteral("/gameassets/gameassets.c")),
        project.filePath(QStringLiteral("worlds/") + world
                         + QStringLiteral("/gameassets/gameassets.c")),
        project.filePath(QStringLiteral("gameassets/gameassets.c"))
    };
    for (const QString &source : generatedSources) {
        QFile current(source);
        if (!current.open(QIODevice::ReadOnly)) continue;
        // The embed writer marks each bitmap; the normal PPB loader does not.
        // Read only enough of the generated source to find the first bitmap.
        const QByteArray prefix = current.read(256 * 1024);
        embedPixels = prefix.contains("/* Original PPB indexed pixels, unchanged;");
        break;
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

    const QDir project(QFileInfo(m_filePath).absolutePath());
    const QDir output(project.filePath(QStringLiteral("worlds/")
        + sidboxTilemapWorldBaseName(m_filePath) + QStringLiteral("/gameassets")));
    const QString cPath = output.filePath(QStringLiteral("gameassets.c"));
    const QString hPath = output.filePath(QStringLiteral("gameassets.h"));
    if (QFileInfo::exists(cPath) || QFileInfo::exists(hPath)) {
        if (QMessageBox::warning(this, tr("Regenerate V1 Game Code"),
            tr("This world's generated gameassets.c/.h files already exist.\n\n"
               "Regenerating replaces these files. A verified IDE-owned main.c may "
               "also be refreshed; user-owned main.c is never replaced.\n\n"
               "Continue?"), QMessageBox::Yes | QMessageBox::Cancel,
            QMessageBox::Cancel) != QMessageBox::Yes) return;
    }

    generateGameCodeCore(choice == QMessageBox::No, false);
}

bool SidboxGameDesigner::generateGameCodeCore(bool embedPixels, bool batchMode)
{
    QString nameError;
    if (!GameWorldSnapshot::validateUniqueName(m_filePath, &nameError)) {
        QMessageBox::warning(this, tr("World Naming Conflict"), nameError);
        return false;
    }
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
    // Always refresh this world's private map staging before publishing.
    // It is consumed during publication; root gamelevels/ is never generated.
    if (m_tilemapEnabled && !exportTilemap(false, true))
        return false;
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
            || !headerBytes.contains("GAME_ADVENTURE_DEFAULT_FRAMES_PER_CHAR")
            || !headerBytes.contains("game_adventure_item_atlas_file")) {
            QMessageBox::warning(this, tr("Adventure Runtime Rules"),
                tr("The installed Adventure runtime is from an earlier version.\n"
                   "Use Update Game Project to back up the game and install the "
                   "current .rulec/.ruleh runtime before generating code."));
            return false;
        }
    }

    SidboxGameCodeGen::Request request;
    request.designDirectory = QFileInfo(m_filePath).absolutePath();
    request.rulesDirectory = QDir(helperTemplatesRoot()).filePath(QStringLiteral("game"));
    request.outputDirectory = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gameassets"));
    request.dualPlane = m_planeMode->currentData().toString() == QStringLiteral("dual");
    request.embedPixels = embedPixels;
    request.foregroundCycle = {m_frontColourCycle.enabled, m_frontColourCycle.start,
                               m_frontColourCycle.length, m_frontColourCycle.speed};
    request.backgroundCycle = {m_backColourCycle.enabled, m_backColourCycle.start,
                               m_backColourCycle.length, m_backColourCycle.speed};
    const QString adventureSkinId = m_adventure.value(QStringLiteral("skinAtlasId")).toString();
    QSet<QString> adventureIconAtlases;
    for (const QJsonValue &item : m_adventure.value(QStringLiteral("items")).toArray()) {
        const QString id = item.toObject().value(QStringLiteral("iconAtlasId")).toString();
        if (!id.isEmpty()) adventureIconAtlases.insert(id);
    }
    const QString activeAtlasPath = m_tilemapEnabled && !m_tilemap.atlasPath.isEmpty()
        ? QDir::cleanPath(resolvedPath(m_tilemap.atlasPath)) : QString();
    for (const Resource &r : m_resources) {
        // Every inventory icon atlas must be loaded into gameassets too.
        // Otherwise gameassets_find_ppb() returns null and DROP renders the
        // dialogue skin instead of the selected Inventory Items atlas.
        if (r.kind == QStringLiteral("tileatlas") && r.id != adventureSkinId &&
            !adventureIconAtlases.contains(r.id) &&
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
        a.alphaFadePercent = r.kind == QStringLiteral("sprite")
            ? qBound(0, r.objectAlphaFadePercent, 100) : 0;
        a.fadeAnimated = r.kind == QStringLiteral("sprite") && r.objectFadeAnimated;
        a.fadeLow = qBound(0, r.objectFadeLow, 100);
        a.fadeHigh = qBound(a.fadeLow, r.objectFadeHigh, 100);
        a.fadeStep = qBound(1, r.objectFadeStep, 100);
        a.fadeDelay = qBound(1, r.objectFadeDelay, 32656);
        a.fadePingpong = r.objectFadePingpong;
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
    if (!GameTitleRuntime::generate(QFileInfo(m_filePath).absolutePath(),
            sidboxTilemapWorldBaseName(m_filePath),
            QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")), &integrationError)) {
        QMessageBox::warning(this, tr("Title Screen Runtime Generation"), integrationError);
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
    // Stage 5.1: publish a private world snapshot AND a buildable, namespaced
    // worlds/<name>/ source tree. Shared helpers and user main.c stay intact.
    QString snapshotError;
    if (!GameWorldSnapshot::publish(m_filePath, sidboxTilemapWorldBaseName(m_filePath),
            m_tilemapEnabled, m_tilemapExternal, anySpline, hasAdventure(),
            embedPixels, QDir(helperTemplatesRoot()).filePath(QStringLiteral("game")),
            &snapshotError)) {
        QMessageBox::warning(this, tr("World Bundle"),
            tr("Generated the active world, but could not publish its independent "
               "world bundle:\n%1").arg(snapshotError));
        return false;
    }
    // Stage 5.3: generated player C is project-wide, NEVER namespaced per world.
    // A missing .sbpi keeps existing older games functional until migrated.
    QString playerError;
    if (!GamePlayerProfile::generate(
            QDir(QFileInfo(m_filePath).absolutePath()),
            QDir(QDir(helperTemplatesRoot()).filePath(QStringLiteral("game"))),
            &playerError)) {
        QMessageBox::warning(this, tr("Shared Player"), playerError);
        return false;
    }
    if (assetFilesChanged) assetFilesChanged();
    QString message = tr("Published this world's assets, objects and Adventure code under\n"
                         "worlds/%1/.\n\n"
                         "Every Game project now uses gamehelpers/gameworlds.h,\n"
                         "including projects with only one world.\n"
                         "Call gameworlds_start(\"%1\") after SIDBOX display/memory setup.\n"
                         "Use gameworlds_update()/draw()/shutdown() as shown\n"
                         "in maingame.c.txt. Temporary root gameassets/gameworlditems\n"
                         "exports are removed after publication and are NOT linked.")
        .arg(sidboxTilemapWorldBaseName(m_filePath));
    if (anyWorldObject)
        message += tr("\n\nWorld object files and guide were generated for this world.");
    message += tr("\n\nUpdated maingame.c.txt. main.c is regenerated only if "
                  "it is IDE-owned and has not been manually edited.");
    message += tr("\n\nBuildable world: worlds/%1/ (compiled alongside other generated worlds).")
        .arg(sidboxTilemapWorldBaseName(m_filePath));
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


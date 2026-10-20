// Stage 3.69: split from gamedesigner.cpp. Method bodies are unchanged.
#include "gamedesigner.h"
#include "gamedesigner_limits.h"
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


namespace {
using SidboxGameDesignerLimits::LCD_WIDTH;
using SidboxGameDesignerLimits::LCD_HEIGHT;
using SidboxGameDesignerLimits::MAX_WORLD;
}

bool SidboxGameDesigner::loadDesign()
{
    QFile file(m_filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("Game Designer"), tr("Cannot open %1").arg(m_filePath));
        return false;
    }
    QJsonParseError error;
    const QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &error);
    const QJsonObject obj = doc.object();
    if (error.error != QJsonParseError::NoError || !doc.isObject()
        || obj.value(QStringLiteral("format")).toString() != QStringLiteral("SIDBOX-GAME-DESIGN")
        || obj.value(QStringLiteral("version")).toInt() != 1) {
        QMessageBox::warning(this, tr("Game Designer"), tr("Unsupported or invalid .sbgm design: %1").arg(m_filePath));
        return false;
    }
    m_loading = true;
    m_worldWidth->setValue(qBound(LCD_WIDTH, obj.value(QStringLiteral("worldWidth")).toInt(960), MAX_WORLD));
    m_worldHeight->setValue(qBound(LCD_HEIGHT, obj.value(QStringLiteral("worldHeight")).toInt(640), MAX_WORLD));
    m_cameraX->setValue(qBound(0, obj.value(QStringLiteral("cameraX")).toInt(),
                               m_worldWidth->value() - LCD_WIDTH));
    m_cameraY->setValue(qBound(0, obj.value(QStringLiteral("cameraY")).toInt(),
                               m_worldHeight->value() - LCD_HEIGHT));
    { QSignalBlocker b1(m_snap), b2(m_snapStep), b3(m_zoom);
      m_snap->setChecked(obj.value(QStringLiteral("snapEnabled")).toBool(true));
      const int step = obj.value(QStringLiteral("snapStep")).toInt(4);
      m_snapStep->setCurrentText(QStringLiteral("%1 px").arg(
          QStringList{QStringLiteral("4"),QStringLiteral("8"),QStringLiteral("16"),
                      QStringLiteral("32"),QStringLiteral("64")}.contains(QString::number(step)) ? step : 32));
      const int requestedZoom = obj.value(QStringLiteral("zoomPercent")).toInt(100);
      const int zoom = QStringList{QStringLiteral("25"), QStringLiteral("50"), QStringLiteral("75"),
          QStringLiteral("100"), QStringLiteral("200"), QStringLiteral("400")}.contains(
          QString::number(requestedZoom)) ? requestedZoom : 100;
      m_zoom->setCurrentText(QStringLiteral("%1%").arg(zoom));
      m_view->resetTransform(); m_view->scale(zoom / 100.0, zoom / 100.0);
    }
    {
        QSignalBlocker b1(m_planeMode), b2(m_showLabels), b3(m_forcePalette), b4(m_showTilemap);
        QSignalBlocker alphaBlock(m_previewPaletteAlpha);
        m_showTilemap->setChecked(obj.value(QStringLiteral("showTilemapOverlay")).toBool(false));
        QSignalBlocker cycleBlock(m_showColourCycles);
        m_showColourCycles->setChecked(obj.value(QStringLiteral("showColourCycles")).toBool(false));
        m_planeMode->setCurrentIndex(obj.value(QStringLiteral("planeMode")).toString() == QStringLiteral("dual") ? 1 : 0);
        m_showLabels->setChecked(obj.value(QStringLiteral("showAssetLabels")).toBool(true));
        m_forcePalette->setChecked(obj.value(QStringLiteral("forcePalette")).toBool(false));
        m_previewPaletteAlpha->setChecked(obj.value(QStringLiteral("previewPaletteAlpha")).toBool(false));
        m_previewPaletteAlpha->setEnabled(m_forcePalette->isChecked());
        m_activeForegroundPalette = obj.value(QStringLiteral("activeForegroundPalette")).toString();
        m_activeBackgroundPalette = obj.value(QStringLiteral("activeBackgroundPalette")).toString();
    }
    // Stage 4.22 single-bank projects migrate to FOREGROUND only.
    // New designs save two independently configurable cycles.
    const auto readCycle = [](const QJsonObject &obj, bool background) {
        SidboxGamePalette::ColourCycle c;
        c.enabled = obj.value(QStringLiteral("enabled")).toBool(false);
        c.start = qBound(background ? 0 : 1,
            obj.value(QStringLiteral("start")).toInt(background ? 0 : 1), 254);
        c.length = qBound(2, obj.value(QStringLiteral("length")).toInt(8), 256 - c.start);
        c.speed = qBound(1, obj.value(QStringLiteral("speed")).toInt(5), 255);
        return c;
    };
    m_frontColourCycle = readCycle(obj.value(QStringLiteral("foregroundColourCycle")).isObject()
        ? obj.value(QStringLiteral("foregroundColourCycle")).toObject()
        : obj.value(QStringLiteral("colourCycle")).toObject(), false);
    m_backColourCycle = readCycle(obj.value(QStringLiteral("backgroundColourCycle")).toObject(), true);
    m_frontCyclePhase = m_backCyclePhase = 0;
    m_lastFrontCyclePhase = m_lastBackCyclePhase = -1;
    m_backPalette->setEnabled(m_planeMode->currentIndex() == 1);
    m_adventure = obj.value(QStringLiteral("adventure")).toObject();
    m_resources.clear();
    bool startupMusicAssigned = false; // Older projects default to no automatic music.
    const QJsonArray assets = obj.value(QStringLiteral("resources")).toArray();
    for (const QJsonValue &value : assets) {
        if (!value.isObject()) continue;
        const QJsonObject a = value.toObject();
        Resource r;
        r.kind = a.value(QStringLiteral("kind")).toString();
        if (!QStringList{QStringLiteral("sprite"), QStringLiteral("tileatlas"),
                         QStringLiteral("background"), QStringLiteral("palette"),
                         QStringLiteral("sound"), QStringLiteral("music")}.contains(r.kind))
            continue;
        r.name = a.value(QStringLiteral("name")).toString();
        r.id = a.value(QStringLiteral("id")).toString();
        if (r.id.isEmpty()) r.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        r.plane = a.value(QStringLiteral("plane")).toString(
            r.kind == QStringLiteral("background") ? QStringLiteral("background") : QStringLiteral("foreground"));
        if (r.plane != QStringLiteral("background")) r.plane = QStringLiteral("foreground");
        r.path = a.value(QStringLiteral("path")).toString();
        r.musicPlayOnStart = r.kind == QStringLiteral("music") && !startupMusicAssigned
            && a.value(QStringLiteral("musicPlayOnStart")).toBool(false);
        if (r.musicPlayOnStart) startupMusicAssigned = true;
        r.x = qBound(-MAX_WORLD, a.value(QStringLiteral("x")).toInt(), MAX_WORLD);
        r.y = qBound(-MAX_WORLD, a.value(QStringLiteral("y")).toInt(), MAX_WORLD);
        r.scale = qBound(1, a.value(QStringLiteral("scale")).toInt(100), 800);
        r.cellWidth = qBound(0, a.value(QStringLiteral("cellWidth")).toInt(0), 16384);
        r.cellHeight = qBound(0, a.value(QStringLiteral("cellHeight")).toInt(0), 16384);
        r.frame = qBound(0, a.value(QStringLiteral("frame")).toInt(0), 65535);
        r.animationFile = a.value(QStringLiteral("animationFile")).toString();
        r.locked = a.value(QStringLiteral("locked")).toBool(false);
        const QJsonObject object = a.value(QStringLiteral("gameObject")).toObject();
        const QString type = object.value(QStringLiteral("type")).toString(QStringLiteral("decoration"));
        if (QStringList{QStringLiteral("collectable"), QStringLiteral("lift"),
                QStringLiteral("conveyor"), QStringLiteral("spring"),
                QStringLiteral("trigger"), QStringLiteral("door"),
                QStringLiteral("deathzone"), QStringLiteral("breakable"), QStringLiteral("hazard")}.contains(type)
            && r.kind == QStringLiteral("sprite")) r.objectType = type;
        r.pickupKind = qBound(1, object.value(QStringLiteral("pickupKind")).toInt(1), 255);
        r.objectValue = qBound(0, object.value(QStringLiteral("value")).toInt(10), 65535);
        r.hitWidth = qBound(1, object.value(QStringLiteral("hitWidth")).toInt(16), 1024);
        r.hitHeight = qBound(1, object.value(QStringLiteral("hitHeight")).toInt(16), 1024);
        r.conveyorSpeed = qBound(-100, object.value(QStringLiteral("conveyorSpeed")).toInt(2), 100);
        r.springStrength = qBound(1, object.value(QStringLiteral("springStrength")).toInt(11), 100);
        r.springLaunchX = qBound(-40, object.value(QStringLiteral("springLaunchX")).toInt(0), 40);
        // Safe opt-in: designs predating this flag cannot silently acquire
        // extra spring+jump velocity. Explicitly saved ON remains ON.
        r.springJumpBoost = object.value(QStringLiteral("springJumpBoost")).toBool(false);
        r.springTouch = object.value(QStringLiteral("springTouch")).toBool(false);
        r.springSlide = object.value(QStringLiteral("springSlide")).toBool(false);
        r.breakTouch = object.value(QStringLiteral("breakTouch")).toBool(false);
        r.breakBounce = object.value(QStringLiteral("breakBounce")).toBool(false);
        r.breakFromBelow = object.value(QStringLiteral("breakFromBelow")).toBool(false);
        r.breakDropCollectableId = object.value(QStringLiteral("breakDropCollectableId")).toString();
        r.breakRewardImpulse = object.value(QStringLiteral("breakRewardImpulse")).toBool(false);
        r.breakRewardVx = qBound(-20, object.value(QStringLiteral("breakRewardVx")).toInt(0), 20);
        r.breakRewardVy = qBound(-20, object.value(QStringLiteral("breakRewardVy")).toInt(-8), 20);
        r.breakHits = qBound(1, object.value(QStringLiteral("breakHits")).toInt(1), 4);
        r.breakStrength = qBound(1, object.value(QStringLiteral("breakStrength")).toInt(11), 100);
        r.breakLaunchX = qBound(-40, object.value(QStringLiteral("breakLaunchX")).toInt(0), 40);
        r.objectInitiallyActive = object.value(QStringLiteral("initiallyActive")).toBool(true);
        r.hazardDamage = qBound(0, object.value(QStringLiteral("hazardDamage")).toInt(1), 65535);
        r.hazardKickX = qBound(-40, object.value(QStringLiteral("hazardKickX")).toInt(0), 40);
        r.hazardKickY = qBound(-40, object.value(QStringLiteral("hazardKickY")).toInt(-11), 40);
        r.hazardKick = object.value(QStringLiteral("hazardKick")).toBool(true);
        r.hazardHurtAnimation = object.value(QStringLiteral("hazardHurtAnimation")).toBool(true);
        r.hazardFlash = object.value(QStringLiteral("hazardFlash")).toBool(true);
        r.hazardFlashColour = qBound(0, object.value(QStringLiteral("hazardFlashColour")).toInt(15), 255);
        r.hazardFlashCount = qBound(1, object.value(QStringLiteral("hazardFlashCount")).toInt(4), 32);
        r.hazardFlashFrames = qBound(1, object.value(QStringLiteral("hazardFlashFrames")).toInt(3), 255);
        r.targetObjectId = object.value(QStringLiteral("targetObjectId")).toString();
        r.targetAction = object.value(QStringLiteral("targetAction")).toString(QStringLiteral("none"));
        if (!QStringList{QStringLiteral("enable"), QStringLiteral("disable"),
                         QStringLiteral("toggle")}.contains(r.targetAction))
            r.targetAction = QStringLiteral("none");
        r.triggerPress = object.value(QStringLiteral("triggerPress")).toBool(false);
        r.triggerOneShot = object.value(QStringLiteral("triggerOneShot")).toBool(false);
        r.triggerMusicId = object.value(QStringLiteral("triggerMusicId")).toString();
        r.triggerMusicAction = object.value(QStringLiteral("triggerMusicAction")).toString(QStringLiteral("none"));
        if (!QStringList{QStringLiteral("play"), QStringLiteral("stop")}.contains(r.triggerMusicAction))
            r.triggerMusicAction = QStringLiteral("none");
        r.sfxPickup = object.value(QStringLiteral("sfxPickup")).toString();
        r.sfxRespawn = object.value(QStringLiteral("sfxRespawn")).toString();
        r.sfxStart = object.value(QStringLiteral("sfxStart")).toString();
        r.sfxMove = object.value(QStringLiteral("sfxMove")).toString();
        r.sfxStop = object.value(QStringLiteral("sfxStop")).toString();
        r.sfxReverse = object.value(QStringLiteral("sfxReverse")).toString();
        r.sfxSpring = object.value(QStringLiteral("sfxSpring")).toString();
        r.sfxBreakHit = object.value(QStringLiteral("sfxBreakHit")).toString();
        r.sfxBreakBounce = object.value(QStringLiteral("sfxBreakBounce")).toString();
        r.sfxBreakFinish = object.value(QStringLiteral("sfxBreakFinish")).toString();
        r.sfxHazardHit = object.value(QStringLiteral("sfxHazardHit")).toString();
        r.sfxHazardBounce = object.value(QStringLiteral("sfxHazardBounce")).toString();
        r.sfxHazardAmbient = object.value(QStringLiteral("sfxHazardAmbient")).toString();
        r.sfxAmbient = object.value(QStringLiteral("sfxAmbient")).toString();
        r.respawnFrames = qBound(0, object.value(QStringLiteral("respawnFrames")).toInt(0), 65535);
        r.audioRadius = qBound(0, object.value(QStringLiteral("audioRadius")).toInt(0), 32767);
        r.audioFadeFrames = qBound(0, object.value(QStringLiteral("audioFadeFrames")).toInt(8), 255);
        r.objectSplineId = object.value(QStringLiteral("splineId")).toString();
        r.objectSplineStartDelay = qBound(0, object.value(QStringLiteral("splineStartDelay")).toInt(0), 65535);
        r.objectAnimated = object.value(QStringLiteral("animated")).toBool(false);
        r.animFirst = qBound(0, object.value(QStringLiteral("animFirst")).toInt(0), 255);
        r.animCount = qBound(1, object.value(QStringLiteral("animCount")).toInt(1), 256);
        r.animTicks = qBound(1, object.value(QStringLiteral("animTicks")).toInt(5), 65535);
        r.animMode = object.value(QStringLiteral("animMode")).toString(QStringLiteral("loop"));
        if (!QStringList{QStringLiteral("loop"), QStringLiteral("once"),
                QStringLiteral("pingpong")}.contains(r.animMode)) r.animMode = QStringLiteral("loop");
        r.drawBehindTiles = a.value(QStringLiteral("drawBehindTiles")).toBool(false);
        r.objectFlipX = a.value(QStringLiteral("objectFlipX")).toBool(false);
        r.objectFlipY = a.value(QStringLiteral("objectFlipY")).toBool(false);
        r.backgroundMode = a.value(QStringLiteral("backgroundMode")).toString(QStringLiteral("sprite"));
        if (r.kind != QStringLiteral("background") ||
            !QStringList{QStringLiteral("sprite"), QStringLiteral("direct_ready"),
                         QStringLiteral("direct_convert")}.contains(r.backgroundMode))
            r.backgroundMode = QStringLiteral("sprite");
        // Optional Stage 54 fields: old Stage 52/53 documents load unchanged.
        const QJsonObject audio = a.value(QStringLiteral("audio")).toObject();
        r.audio.channel = qBound(0, audio.value(QStringLiteral("channel")).toInt(0), 7);
        r.audio.frequency = qBound(0, audio.value(QStringLiteral("frequency")).toInt(22050), 65535);
        r.audio.volume = qBound(0, audio.value(QStringLiteral("volume")).toInt(255), 1024);
        r.audio.pan = qBound(-127, audio.value(QStringLiteral("pan")).toInt(0), 127);
        r.audio.loop = audio.value(QStringLiteral("loop")).toBool(false);
        r.audio.loopStart = qBound(0, audio.value(QStringLiteral("loopStart")).toInt(0), 2147483647);
        r.audio.loopLength = qBound(0, audio.value(QStringLiteral("loopLength")).toInt(0), 2147483647);
        r.audio.subsong = qBound(0, audio.value(QStringLiteral("subsong")).toInt(0), 255);
        m_resources.append(r);
        if (m_resources.size() >= 8192) break; // corrupt/hostile data guard
    }
    // Older .sbgm documents may have backgrounds but no separate Background
    // palette category yet. Seed it from the first valid background PPB only;
    // never overwrite the file or override an existing bank choice.
    const int originalResourceCount = m_resources.size();
    if (m_activeBackgroundPalette.isEmpty()) {
        for (int i = 0; i < originalResourceCount; ++i) {
            if (m_resources.at(i).kind == QStringLiteral("background")) {
                const Resource background = m_resources.at(i);
                suggestFirstBackgroundPalette(background);
                if (m_resources.size() != originalResourceCount) break;
            }
        }
    }
    const bool seededBackgroundPalette = m_resources.size() != originalResourceCount;
    m_tilemapEnabled = false;
    m_tilemapExternal = obj.value(QStringLiteral("tilemapExternal")).toBool(false);
    m_tilemap = SidboxTilemap();
    if (obj.contains(QStringLiteral("tilemap"))) {
        if (!m_tilemap.fromJson(obj.value(QStringLiteral("tilemap")).toObject())) {
            m_loading = false;
            QMessageBox::warning(this, tr("Tilemap Editor"),
                tr("The saved tilemap data is damaged or exceeds the size limits. No tilemap changes were applied."));
            return false;
        }
        m_tilemapEnabled = true;
    }
    m_splinePaths.clear();
    for (const QJsonValue &entry : obj.value(QStringLiteral("splinePaths")).toArray()) {
        if (!entry.isObject() || m_splinePaths.size() >= 128) continue;
        const QJsonObject value = entry.toObject();
        SplinePath path;
        path.name = value.value(QStringLiteral("name")).toString(QStringLiteral("path"));
        path.id = value.value(QStringLiteral("id")).toString();
        if (path.id.isEmpty()) path.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        path.durationFrames = qBound(1, value.value(QStringLiteral("frames")).toInt(100), 65535);
        path.loop = value.value(QStringLiteral("loop")).toBool(true);
        // Keep the original [x,y] point representation so old IDE versions
        // can still read the geometry. The optional wait times live in a
        // separate "pointPauses" array; older designs default to all zero.
        const QJsonArray pauseValues = value.value(QStringLiteral("pointPauses")).toArray();
        for (const QJsonValue &pointValue : value.value(QStringLiteral("points")).toArray()) {
            if (!pointValue.isArray() || path.points.size() >= 128) continue;
            const QJsonArray coordinates = pointValue.toArray();
            if (coordinates.size() < 2) continue;
            path.points.append(QPoint(qBound(-32768, coordinates.at(0).toInt(), 32767),
                                      qBound(-32768, coordinates.at(1).toInt(), 32767)));
            const int pointNumber = path.points.size() - 1;
            const int pauseFrames = pointNumber < pauseValues.size()
                ? pauseValues.at(pointNumber).toInt() : 0;
            path.pointPauses.append(qBound(0, pauseFrames, 65535));
        }
        if (path.points.size() >= 2) m_splinePaths.append(path);
    }
    m_activeSpline = qBound(-1, obj.value(QStringLiteral("activeSpline")).toInt(-1),
                            m_splinePaths.size() - 1);
    // A saved WORLD canvas centre is a viewport setting, not the game camera.
    // Keep coordinates in scene/world units so a different zoom or IDE window
    // size restores the same interesting part of the level. Older .sbgm files
    // have no fields and keep their original default viewport behaviour.
    m_restoreWorldViewCenter = obj.value(QStringLiteral("worldViewCenterX")).isDouble()
                            && obj.value(QStringLiteral("worldViewCenterY")).isDouble();
    if (m_restoreWorldViewCenter) {
        m_savedWorldViewCenter = QPointF(
            qBound(-double(MAX_WORLD), obj.value(QStringLiteral("worldViewCenterX")).toDouble(), double(MAX_WORLD)),
            qBound(-double(MAX_WORLD), obj.value(QStringLiteral("worldViewCenterY")).toDouble(), double(MAX_WORLD)));
    }
    m_loading = false;
    m_undoResources.clear();
    m_redoResources.clear();
    m_hasCopiedSprite = false;
    rebuildScene();
    refreshResources();
    refreshProperties();
    setDirty(seededBackgroundPalette); // prompt to save new reference, never silently save
    return true;
}

bool SidboxGameDesigner::saveDesign()
{
    QJsonObject obj;
    obj.insert(QStringLiteral("format"), QStringLiteral("SIDBOX-GAME-DESIGN"));
    obj.insert(QStringLiteral("version"), 1);
    obj.insert(QStringLiteral("worldWidth"), m_worldWidth->value());
    obj.insert(QStringLiteral("worldHeight"), m_worldHeight->value());
    obj.insert(QStringLiteral("cameraX"), m_cameraX->value());
    obj.insert(QStringLiteral("cameraY"), m_cameraY->value());
    obj.insert(QStringLiteral("snapEnabled"), m_snap->isChecked());
    obj.insert(QStringLiteral("snapStep"), m_snapStep->currentText().section(QLatin1Char(' '), 0, 0).toInt());
    obj.insert(QStringLiteral("zoomPercent"), m_zoom->currentText().chopped(1).toInt());
    // Save where the user panned the WORLD editor, not the in-game camera.
    // If loading happens in a hidden tab, retain the saved centre until its
    // first display instead of serialising the uninitialised viewport centre.
    const QPointF worldViewCenter = m_restoreWorldViewCenter
        ? m_savedWorldViewCenter
        : m_view->mapToScene(m_view->viewport()->rect().center());
    obj.insert(QStringLiteral("worldViewCenterX"), worldViewCenter.x());
    obj.insert(QStringLiteral("worldViewCenterY"), worldViewCenter.y());
    obj.insert(QStringLiteral("showAssetLabels"), m_showLabels->isChecked());
    obj.insert(QStringLiteral("showTilemapOverlay"), m_showTilemap->isChecked());
    obj.insert(QStringLiteral("showColourCycles"), m_showColourCycles->isChecked());
    const auto writeCycle = [](const SidboxGamePalette::ColourCycle &c) {
        QJsonObject o;
        o.insert(QStringLiteral("enabled"), c.enabled);
        o.insert(QStringLiteral("start"), c.start);
        o.insert(QStringLiteral("length"), c.length);
        o.insert(QStringLiteral("speed"), c.speed);
        return o;
    };
    obj.insert(QStringLiteral("foregroundColourCycle"), writeCycle(m_frontColourCycle));
    obj.insert(QStringLiteral("backgroundColourCycle"), writeCycle(m_backColourCycle));
    obj.insert(QStringLiteral("planeMode"), m_planeMode->currentData().toString());
    obj.insert(QStringLiteral("forcePalette"), m_forcePalette->isChecked());
    obj.insert(QStringLiteral("previewPaletteAlpha"), m_previewPaletteAlpha->isChecked());
    obj.insert(QStringLiteral("activeForegroundPalette"), m_activeForegroundPalette);
    obj.insert(QStringLiteral("activeBackgroundPalette"), m_activeBackgroundPalette);
    obj.insert(QStringLiteral("adventure"), m_adventure);
    QJsonArray assets;
    for (const Resource &r : m_resources) {
        QJsonObject a;
        a.insert(QStringLiteral("kind"), r.kind);
        a.insert(QStringLiteral("name"), r.name);
        a.insert(QStringLiteral("id"), r.id);
        a.insert(QStringLiteral("plane"), r.plane);
        a.insert(QStringLiteral("path"), r.path);
        if (r.kind == QStringLiteral("music"))
            a.insert(QStringLiteral("musicPlayOnStart"), r.musicPlayOnStart);
        a.insert(QStringLiteral("x"), r.x);
        a.insert(QStringLiteral("y"), r.y);
        a.insert(QStringLiteral("scale"), r.scale);
        a.insert(QStringLiteral("cellWidth"), r.cellWidth);
        a.insert(QStringLiteral("cellHeight"), r.cellHeight);
        a.insert(QStringLiteral("frame"), r.frame);
        if (r.kind == QStringLiteral("sprite") && !r.animationFile.isEmpty())
            a.insert(QStringLiteral("animationFile"), r.animationFile);
        a.insert(QStringLiteral("locked"), r.locked);
        if (r.kind == QStringLiteral("sprite")) {
            a.insert(QStringLiteral("drawBehindTiles"), r.drawBehindTiles);
            a.insert(QStringLiteral("objectFlipX"), r.objectFlipX);
            a.insert(QStringLiteral("objectFlipY"), r.objectFlipY);
        }
        if (r.kind == QStringLiteral("sprite") && r.objectType != QStringLiteral("decoration")) {
            QJsonObject object;
            object.insert(QStringLiteral("type"), r.objectType);
            object.insert(QStringLiteral("pickupKind"), r.pickupKind);
            object.insert(QStringLiteral("value"), r.objectValue);
            object.insert(QStringLiteral("hitWidth"), r.hitWidth);
            object.insert(QStringLiteral("hitHeight"), r.hitHeight);
            object.insert(QStringLiteral("conveyorSpeed"), r.conveyorSpeed);
            object.insert(QStringLiteral("springStrength"), r.springStrength);
            object.insert(QStringLiteral("springLaunchX"), r.springLaunchX);
            object.insert(QStringLiteral("springJumpBoost"), r.springJumpBoost);
            object.insert(QStringLiteral("springTouch"), r.springTouch);
            object.insert(QStringLiteral("springSlide"), r.springSlide);
            object.insert(QStringLiteral("breakTouch"), r.breakTouch);
            object.insert(QStringLiteral("breakBounce"), r.breakBounce);
            object.insert(QStringLiteral("breakFromBelow"), r.breakFromBelow);
            object.insert(QStringLiteral("breakDropCollectableId"), r.breakDropCollectableId);
            object.insert(QStringLiteral("breakRewardImpulse"), r.breakRewardImpulse);
            object.insert(QStringLiteral("breakRewardVx"), r.breakRewardVx);
            object.insert(QStringLiteral("breakRewardVy"), r.breakRewardVy);
            object.insert(QStringLiteral("breakHits"), r.breakHits);
            object.insert(QStringLiteral("breakStrength"), r.breakStrength);
            object.insert(QStringLiteral("breakLaunchX"), r.breakLaunchX);
            object.insert(QStringLiteral("initiallyActive"), r.objectInitiallyActive);
            object.insert(QStringLiteral("hazardDamage"), r.hazardDamage);
            object.insert(QStringLiteral("hazardKickX"), r.hazardKickX);
            object.insert(QStringLiteral("hazardKickY"), r.hazardKickY);
            object.insert(QStringLiteral("hazardKick"), r.hazardKick);
            object.insert(QStringLiteral("hazardHurtAnimation"), r.hazardHurtAnimation);
            object.insert(QStringLiteral("hazardFlash"), r.hazardFlash);
            object.insert(QStringLiteral("hazardFlashColour"), r.hazardFlashColour);
            object.insert(QStringLiteral("hazardFlashCount"), r.hazardFlashCount);
            object.insert(QStringLiteral("hazardFlashFrames"), r.hazardFlashFrames);
            object.insert(QStringLiteral("targetObjectId"), r.targetObjectId);
            object.insert(QStringLiteral("targetAction"), r.targetAction);
            object.insert(QStringLiteral("triggerPress"), r.triggerPress);
            object.insert(QStringLiteral("triggerOneShot"), r.triggerOneShot);
            object.insert(QStringLiteral("triggerMusicId"), r.triggerMusicId);
            object.insert(QStringLiteral("triggerMusicAction"), r.triggerMusicAction);
            object.insert(QStringLiteral("sfxPickup"), r.sfxPickup);
            object.insert(QStringLiteral("sfxRespawn"), r.sfxRespawn);
            object.insert(QStringLiteral("sfxStart"), r.sfxStart);
            object.insert(QStringLiteral("sfxMove"), r.sfxMove);
            object.insert(QStringLiteral("sfxStop"), r.sfxStop);
            object.insert(QStringLiteral("sfxReverse"), r.sfxReverse);
            object.insert(QStringLiteral("sfxSpring"), r.sfxSpring);
            object.insert(QStringLiteral("sfxBreakHit"), r.sfxBreakHit);
            object.insert(QStringLiteral("sfxBreakBounce"), r.sfxBreakBounce);
            object.insert(QStringLiteral("sfxBreakFinish"), r.sfxBreakFinish);
            object.insert(QStringLiteral("sfxHazardHit"), r.sfxHazardHit);
            object.insert(QStringLiteral("sfxHazardBounce"), r.sfxHazardBounce);
            object.insert(QStringLiteral("sfxHazardAmbient"), r.sfxHazardAmbient);
            object.insert(QStringLiteral("sfxAmbient"), r.sfxAmbient);
            object.insert(QStringLiteral("respawnFrames"), r.respawnFrames);
            object.insert(QStringLiteral("audioRadius"), r.audioRadius);
            object.insert(QStringLiteral("audioFadeFrames"), r.audioFadeFrames);
            object.insert(QStringLiteral("splineId"), r.objectSplineId);
            object.insert(QStringLiteral("splineStartDelay"), r.objectSplineStartDelay);
            object.insert(QStringLiteral("animated"), r.objectAnimated);
            object.insert(QStringLiteral("animFirst"), r.animFirst);
            object.insert(QStringLiteral("animCount"), r.animCount);
            object.insert(QStringLiteral("animTicks"), r.animTicks);
            object.insert(QStringLiteral("animMode"), r.animMode);
            a.insert(QStringLiteral("gameObject"), object);
        }
        if (r.kind == QStringLiteral("background"))
            a.insert(QStringLiteral("backgroundMode"), r.backgroundMode);
        if (r.kind == QStringLiteral("sound") || r.kind == QStringLiteral("music")) {
            QJsonObject audio;
            audio.insert(QStringLiteral("channel"), r.audio.channel);
            audio.insert(QStringLiteral("frequency"), r.audio.frequency);
            audio.insert(QStringLiteral("volume"), r.audio.volume);
            audio.insert(QStringLiteral("pan"), r.audio.pan);
            audio.insert(QStringLiteral("loop"), r.audio.loop);
            audio.insert(QStringLiteral("loopStart"), r.audio.loopStart);
            audio.insert(QStringLiteral("loopLength"), r.audio.loopLength);
            audio.insert(QStringLiteral("subsong"), r.audio.subsong);
            a.insert(QStringLiteral("audio"), audio);
        }
        assets.append(a);
    }
    obj.insert(QStringLiteral("resources"), assets);
    QJsonArray pathList;
    for (const SplinePath &path : m_splinePaths) {
        QJsonObject data;
        data.insert(QStringLiteral("name"), path.name);
        data.insert(QStringLiteral("id"), path.id);
        data.insert(QStringLiteral("frames"), path.durationFrames);
        data.insert(QStringLiteral("loop"), path.loop);
        QJsonArray coords;
        QJsonArray pauses;
        for (int i = 0; i < path.points.size(); ++i) {
            const QPoint &point = path.points.at(i);
            coords.append(QJsonArray{point.x(), point.y()});
            pauses.append(path.pointPauses.value(i, 0));
        }
        data.insert(QStringLiteral("points"), coords);
        data.insert(QStringLiteral("pointPauses"), pauses);
        pathList.append(data);
    }
    obj.insert(QStringLiteral("splinePaths"), pathList);
    obj.insert(QStringLiteral("activeSpline"), m_activeSpline);
    if (m_tilemapEnabled) {
        obj.insert(QStringLiteral("tilemap"), m_tilemap.toJson());
        obj.insert(QStringLiteral("tilemapExternal"), m_tilemapExternal);
    }
    QSaveFile output(m_filePath);
    const QByteArray payload = QJsonDocument(obj).toJson(QJsonDocument::Indented);
    if (!output.open(QIODevice::WriteOnly)
        || output.write(payload) != payload.size()
        || !output.commit()) {
        QMessageBox::warning(this, tr("Game Designer"), tr("Unable to save design:\n%1").arg(m_filePath));
        return false;
    }
    // Once exported, path C data tracks saved edits to any control point.
    // Nothing is created for older projects until Export is chosen.
    const QString pathHeader = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gamehelpers/splinepaths.h"));
    if (QFileInfo::exists(pathHeader) && !exportSplinePaths(false)) return false;
    const QString tileHeader = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("gamelevels/level1.h"));
    if (m_tilemapEnabled && QFileInfo::exists(tileHeader) && !exportTilemap(false)) return false;
    setDirty(false);
    return true;
}


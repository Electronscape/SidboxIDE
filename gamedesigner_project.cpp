// Stage 3.69: split from gamedesigner.cpp. Method bodies are unchanged.
#include "gamedesigner.h"
#include <QColor>
#include "gameglobalstamps.h"
#include "gameworldsnapshot.h"
#include "gameplayerprofile.h"
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
    const QJsonObject start = obj.value(QStringLiteral("playerStart")).toObject();
    m_playerProfile = start.value(QStringLiteral("profile")).toString(QStringLiteral("players/player.sbpi"));
    m_playerEntry = start.value(QStringLiteral("entry")).toString(QStringLiteral("default"));
    m_playerFacing = qBound(0, start.value(QStringLiteral("facing")).toInt(1), 1);
    m_playerStartX = qMax(0,start.value(QStringLiteral("x")).toInt(0));
    m_playerStartY = qMax(0,start.value(QStringLiteral("y")).toInt(0));
    m_playerTransitionIn = start.value(QStringLiteral("transitionIn")).toString(QStringLiteral("none"));
    m_playerTransitionOut = start.value(QStringLiteral("transitionOut")).toString(QStringLiteral("none"));
    m_playerCircleOrigin = start.value(QStringLiteral("circleOrigin")).toString(QStringLiteral("center"));
    m_playerTransitionFrames = qBound(1, start.value(QStringLiteral("transitionFrames")).toInt(30), 150);
    const QJsonObject weather = obj.value(QStringLiteral("weather")).toObject();
    m_weatherMode = qBound(0, weather.value(QStringLiteral("mode")).toInt(0), 3);
    m_weatherDensity = qBound(1, weather.value(QStringLiteral("density")).toInt(48), 64);
    m_weatherWind = qBound(-8, weather.value(QStringLiteral("wind")).toInt(0), 8);
    m_weatherParticleSize = qBound(2, weather.value(QStringLiteral("particleSize")).toInt(5), 32);
    m_weatherParticleTile = qBound(0, weather.value(QStringLiteral("particleTileId")).toInt(0), 65535);
    m_weatherParticleAtlasId = weather.value(QStringLiteral("particleAtlasId")).toString();
    m_weatherParticleTileSize = weather.value(QStringLiteral("particleTileSize")).toInt(8);
    if (m_weatherParticleTileSize != 8 && m_weatherParticleTileSize != 16 && m_weatherParticleTileSize != 32)
        m_weatherParticleTileSize = 8;
    m_weatherPaletteIndex = qBound(1, weather.value(QStringLiteral("paletteIndex")).toInt(15), 254);
    m_weatherLightningInterval = qBound(100, weather.value(QStringLiteral("lightningInterval")).toInt(350), 2000);
    m_weatherLightningStrength = qBound(10, weather.value(QStringLiteral("lightningStrength")).toInt(75), 100);
    m_weatherLightningCurve = qBound(0, weather.value(QStringLiteral("lightningCurve")).toInt(25), 100);
    m_weatherLightningOverlay = weather.value(QStringLiteral("lightningOverlayEnabled")).toBool(true);
    m_weatherPaletteFlashStrength = qBound(0, weather.value(QStringLiteral("paletteFlashStrength")).toInt(0), 100);
    m_weatherSuspendSpotlight = weather.value(QStringLiteral("suspendSpotlightOnLightning")).toBool(false);
    const QJsonObject dayNight = obj.value(QStringLiteral("dayNight")).toObject();
    m_dayNightMode = qBound(0, dayNight.value(QStringLiteral("mode")).toInt(0), 2);
    m_dayNightColour = dayNight.value(QStringLiteral("targetColour")).toString(QStringLiteral("#233b68"));
    if (!QColor(m_dayNightColour).isValid()) m_dayNightColour = QStringLiteral("#233b68");
    m_dayNightStrength = qBound(0, dayNight.value(QStringLiteral("strength")).toInt(65), 100);
    m_dayNightDayFrames = qBound(50, dayNight.value(QStringLiteral("dayFrames")).toInt(3000), 30000);
    m_dayNightNightFrames = qBound(50, dayNight.value(QStringLiteral("nightFrames")).toInt(3000), 30000);
    m_dayNightFadeFrames = qBound(25, dayNight.value(QStringLiteral("fadeFrames")).toInt(500), 10000);
    m_dayNightStartAtNight = dayNight.value(QStringLiteral("startAtNight")).toBool(false);
    m_dayEvents = dayNight.value(QStringLiteral("dayActions")).toArray();
    m_nightEvents = dayNight.value(QStringLiteral("nightActions")).toArray();
    m_playerSpotlightEnabled = start.value(QStringLiteral("spotlightEnabled")).toBool(false);
    m_playerSpotlightRadius = qBound(16, start.value(QStringLiteral("spotlightRadius")).toInt(96), 240);
    m_playerSpotlightFeather = qBound(0, start.value(QStringLiteral("spotlightFeather")).toInt(24), 96);
    m_playerSpotlightCenter = start.value(QStringLiteral("spotlightCenter")).toBool(true);
    m_playerSpotlightOffsetX = qBound(-240, start.value(QStringLiteral("spotlightOffsetX")).toInt(0), 240);
    m_playerSpotlightOffsetY = qBound(-240, start.value(QStringLiteral("spotlightOffsetY")).toInt(0), 240);
    m_playerSpotlightFlipX = start.value(QStringLiteral("spotlightFlipX")).toBool(false);
    m_playerSpotlightFlipY = start.value(QStringLiteral("spotlightFlipY")).toBool(false);
    m_playerSpotlightOpacity = qBound(0, start.value(QStringLiteral("spotlightOpacity")).toInt(100), 100);
    m_playerSpotlightStableDither = start.value(QStringLiteral("spotlightStableDither")).toBool(true);
    m_playerSpotlightAnimMode = qBound(0, start.value(QStringLiteral("spotlightAnimMode")).toInt(0), 2);
    m_playerSpotlightAnimMin = qBound(0, start.value(QStringLiteral("spotlightAnimMin")).toInt(12), 96);
    m_playerSpotlightAnimMax = qBound(m_playerSpotlightAnimMin, start.value(QStringLiteral("spotlightAnimMax")).toInt(32), 96);
    m_playerSpotlightAnimDelayMin = qBound(1, start.value(QStringLiteral("spotlightAnimDelayMin")).toInt(3), 600);
    m_playerSpotlightAnimDelayMax = qBound(m_playerSpotlightAnimDelayMin, start.value(QStringLiteral("spotlightAnimDelayMax")).toInt(12), 600);
    m_playerSpotlightAnimPulseDelay = qBound(1, start.value(QStringLiteral("spotlightAnimPulseDelay")).toInt(3), 600);
    m_playerSpotlightMaskIndex = qBound(1, start.value(QStringLiteral("spotlightMaskIndex")).toInt(255), 255);
    {
        const QColor mask(start.value(QStringLiteral("spotlightMaskColour")).toString(QStringLiteral("#000000")));
        m_playerSpotlightMaskColour = mask.isValid() ? mask.name() : QStringLiteral("#000000");
    }
    m_otherPlayerStarts.clear();
    QSet<QString> seenStartIds{QStringLiteral("default")};
    for (const QJsonValue &v : obj.value(QStringLiteral("playerStarts")).toArray()) {
        const QJsonObject entry = v.toObject();
        PlayerStartLocation location;
        location.id = entry.value(QStringLiteral("id")).toString();
        location.name = entry.value(QStringLiteral("name")).toString().trimmed();
        if (location.id.isEmpty() || seenStartIds.contains(location.id)) continue;
        seenStartIds.insert(location.id);
        location.x = qBound(0, entry.value(QStringLiteral("x")).toInt(), 32767);
        location.y = qBound(0, entry.value(QStringLiteral("y")).toInt(), 32767);
        location.facing = qBound(0, entry.value(QStringLiteral("facing")).toInt(1), 1);
        location.transitionIn = entry.value(QStringLiteral("transitionIn")).toString(QStringLiteral("none"));
        location.transitionOut = entry.value(QStringLiteral("transitionOut")).toString(QStringLiteral("none"));
        location.circleOrigin = entry.value(QStringLiteral("circleOrigin")).toString(QStringLiteral("center"));
        location.transitionFrames = qBound(1, entry.value(QStringLiteral("transitionFrames")).toInt(30), 150);
        if (location.name.isEmpty()) location.name = tr("Door start");
        m_otherPlayerStarts.push_back(location);
    }
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
        r.spriteStamp = SidboxSpriteStamp::fromJson(a.value(QStringLiteral("spriteStamp")).toObject());
        if (r.kind == QStringLiteral("sprite") && r.spriteStamp.active()) {
            r.path = r.spriteStamp.sourcePath; // migrate Stage 5.36 stamp_*.ppb projects
            r.cellWidth = r.cellHeight = SidboxSpriteStamp::cellPixels;
            r.frame = 0;
        }
        r.animationFile = a.value(QStringLiteral("animationFile")).toString();
        r.locked = a.value(QStringLiteral("locked")).toBool(false);
        const QJsonObject object = a.value(QStringLiteral("gameObject")).toObject();
        const QString type = object.value(QStringLiteral("type")).toString(QStringLiteral("decoration"));
        if (QStringList{QStringLiteral("collectable"), QStringLiteral("lift"),
                QStringLiteral("conveyor"), QStringLiteral("spring"),
                QStringLiteral("trigger"), QStringLiteral("door"),
                QStringLiteral("deathzone"), QStringLiteral("breakable"), QStringLiteral("hazard"),
                QStringLiteral("enemy"), QStringLiteral("goto_world"),
                QStringLiteral("particle_emitter"), QStringLiteral("save_checkpoint"),
                QStringLiteral("decoration_object")}.contains(type)
            && r.kind == QStringLiteral("sprite")) r.objectType = type;
        r.pickupKind = qBound(1, object.value(QStringLiteral("pickupKind")).toInt(1), 255);
        r.objectValue = qBound(0, object.value(QStringLiteral("value")).toInt(10), 65535);
        r.pickupTrackingConfigured = object.value(QStringLiteral("pickupTrackingConfigured")).toBool(false);
        r.pickupShowInventory = object.value(QStringLiteral("pickupShowInventory")).toBool(false);
        r.pickupShowHud = object.value(QStringLiteral("pickupShowHud")).toBool(false);
        r.pickupStatTarget = object.value(QStringLiteral("pickupStatTarget")).toString();
        r.pickupPersistent = object.value(QStringLiteral("pickupPersistent")).toBool(false);
        r.pickupAllowEnemyLoot = object.value(QStringLiteral("pickupAllowEnemyLoot")).toBool(false);
        r.enemyLootMin = qBound(0, object.value(QStringLiteral("enemyLootMin")).toInt(1), 8);
        r.enemyLootMax = qBound(r.enemyLootMin, object.value(QStringLiteral("enemyLootMax")).toInt(1), 8);
        for (const QJsonValue &v : object.value(QStringLiteral("enemyLootIds")).toArray()) {
            const QString id = v.toString();
            if (!id.isEmpty() && !r.enemyLootIds.contains(id) && r.enemyLootIds.size() < 8)
                r.enemyLootIds.append(id);
        }
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
        r.breakHits = qBound(1, object.value(QStringLiteral("breakHits")).toInt(1),
            r.objectType == QStringLiteral("enemy") ? 20 : 4);
        r.breakStrength = qBound(1, object.value(QStringLiteral("breakStrength")).toInt(11), 100);
        r.breakLaunchX = qBound(-40, object.value(QStringLiteral("breakLaunchX")).toInt(0), 40);
        // Designs from 4.40 with a nonzero sideways bounce must retain that behaviour.
        // New objects start with vertical-only vulnerable-hit rebound.
        r.enemyStompSideKick = object.value(QStringLiteral("enemyStompSideKick"))
            .toBool(r.objectType == QStringLiteral("enemy") && r.breakLaunchX != 0);
        r.enemyAttackDirection = qBound(0, object.value(QStringLiteral("enemyAttackDirection")).toInt(0), 2);
        r.enemyHurtsOnTouch = object.value(QStringLiteral("enemyHurtsOnTouch")).toBool(true);
        r.enemyDamage = qBound(0, object.value(QStringLiteral("enemyDamage")).toInt(1), 65535);
        r.enemyRoam = object.value(QStringLiteral("enemyRoam")).toBool(false);
        r.enemyRoamSpeed = qBound(1, object.value(QStringLiteral("enemyRoamSpeed")).toInt(1), 8);
        r.enemyStepHeight = qBound(1, object.value(QStringLiteral("enemyStepHeight")).toInt(4), 12);
        r.enemyRoamLeft = object.value(QStringLiteral("enemyRoamLeft")).toBool(false);
        r.enemyDefeatFrame = qBound(-1, object.value(QStringLiteral("enemyDefeatFrame")).toInt(-1), 255);
        r.enemyDefeatFrames = qBound(1, object.value(QStringLiteral("enemyDefeatFrames")).toInt(20), 255);
        r.enemyDefeatCount = qBound(1, object.value(QStringLiteral("enemyDefeatCount")).toInt(1), 255);
        // Old projects had only one defeated frame with a total display duration.
        r.enemyDefeatDelay = qBound(1, object.value(QStringLiteral("enemyDefeatDelay"))
                                    .toInt(r.enemyDefeatFrames), 255);
        r.enemyStompOffsetX = qBound(-64, object.value(QStringLiteral("enemyStompOffsetX")).toInt(0), 64);
        r.enemyStompOffsetY = qBound(-64, object.value(QStringLiteral("enemyStompOffsetY")).toInt(0), 64);
        r.enemyStompWidth = qBound(0, object.value(QStringLiteral("enemyStompWidth")).toInt(0), 512);
        r.enemyStompHeight = qBound(1, object.value(QStringLiteral("enemyStompHeight")).toInt(1), 64);
        r.objectInitiallyActive = object.value(QStringLiteral("initiallyActive")).toBool(true);
        r.particlePreset = object.value(QStringLiteral("particlePreset")).toString(QStringLiteral("leaves"));
        if (r.particlePreset != QStringLiteral("leaves") && r.particlePreset != QStringLiteral("clouds") &&
            r.particlePreset != QStringLiteral("dust") && r.particlePreset != QStringLiteral("fireflies"))
            r.particlePreset = QStringLiteral("leaves");
        r.particleAreaW = qBound(8, object.value(QStringLiteral("particleAreaW")).toInt(240), 2048);
        r.particleAreaH = qBound(8, object.value(QStringLiteral("particleAreaH")).toInt(96), 2048);
        r.particleCount = qBound(1, object.value(QStringLiteral("particleCount")).toInt(12), 32);
        r.particleInterval = qBound(1, object.value(QStringLiteral("particleInterval")).toInt(6), 255);
        r.particlePrepopulate = object.value(QStringLiteral("particlePrepopulate")).toBool(true);
        r.particleLifetime = qBound(30, object.value(QStringLiteral("particleLifetime")).toInt(250), 2000);
        r.particleWind = qBound(-400, object.value(QStringLiteral("particleWind")).toInt(65), 400);
        r.particleFall = qBound(-400, object.value(QStringLiteral("particleFall")).toInt(40), 400);
        r.particleGravity = qBound(0, object.value(QStringLiteral("particleGravity")).toInt(2), 80);
        r.particleFlutter = qBound(0, object.value(QStringLiteral("particleFlutter")).toInt(22), 100);
        r.particleSwirlRadius = qBound(8, object.value(QStringLiteral("particleSwirlRadius")).toInt(24), 96);
        r.particleSwirlSpeed = qBound(1, object.value(QStringLiteral("particleSwirlSpeed")).toInt(2), 12);
        r.particlePlayerLayerMix = object.value(QStringLiteral("particlePlayerLayerMix")).toBool(false);
        r.particleFadeEnabled = object.value(QStringLiteral("particleFadeEnabled")).toBool(false);
        r.particleFadeIn = qBound(0, object.value(QStringLiteral("particleFadeIn")).toInt(20), 100);
        r.particleFadeOut = qBound(0, object.value(QStringLiteral("particleFadeOut")).toInt(20), 100);
        r.particleFadeSpeed = qBound(1, object.value(QStringLiteral("particleFadeSpeed")).toInt(8), 100);
        r.hazardDamage = qBound(0, object.value(QStringLiteral("hazardDamage")).toInt(1), 65535);
        r.deathNote = object.value(QStringLiteral("deathNote")).toString().left(110);
        r.damageConfigured = object.contains(QStringLiteral("damageTarget"));
        r.damageTarget = object.value(QStringLiteral("damageTarget")).toString(QStringLiteral("health"));
        if (r.damageTarget != QStringLiteral("health") && r.damageTarget != QStringLiteral("lives") &&
            r.damageTarget != QStringLiteral("score") && r.damageTarget != QStringLiteral("coins") &&
            !r.damageTarget.startsWith(QStringLiteral("stat:"))) r.damageTarget = QStringLiteral("health");
        r.damageDelta = qBound(-65535,object.value(QStringLiteral("damageDelta"))
            .toInt(-r.hazardDamage),65535);
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
        for (const QJsonValue &entry : object.value(QStringLiteral("triggerExtraActions")).toArray()) {
            const QJsonObject link=entry.toObject();
            const QString id=link.value(QStringLiteral("objectId")).toString();
            const QString action=link.value(QStringLiteral("action")).toString();
            if (!id.isEmpty() && (action==QStringLiteral("enable") ||
                action==QStringLiteral("disable") || action==QStringLiteral("toggle")))
                r.triggerExtraActions.append({id, action});
        }
        for (const QJsonValue &entry : object.value(QStringLiteral("enemyDefeatExtraActions")).toArray()) {
            const QJsonObject link=entry.toObject();
            const QString id=link.value(QStringLiteral("objectId")).toString();
            const QString action=link.value(QStringLiteral("action")).toString();
            if (!id.isEmpty() && (action==QStringLiteral("enable") ||
                action==QStringLiteral("disable") || action==QStringLiteral("toggle")))
                r.enemyDefeatExtraActions.append({id,action});
        }
        if (!QStringList{QStringLiteral("enable"), QStringLiteral("disable"),
                         QStringLiteral("toggle")}.contains(r.targetAction))
            r.targetAction = QStringLiteral("none");
        r.eventActions = object.value(QStringLiteral("eventActions")).toObject();
        r.logicNodes = object.value(QStringLiteral("logicNodes")).toArray();
        r.toggleStateTargetId = object.value(QStringLiteral("toggleStateTargetId")).toString();
        r.toggleStateOperator = object.value(QStringLiteral("toggleStateOperator")).toString(QStringLiteral("boolean"));
        if (r.toggleStateOperator != QStringLiteral("and") &&
            r.toggleStateOperator != QStringLiteral("or")) r.toggleStateOperator = QStringLiteral("boolean");
        for (const QJsonValue &input : object.value(QStringLiteral("toggleStateInputIds")).toArray()) {
            const QString id = input.toString();
            if (!id.isEmpty() && id != r.toggleStateTargetId &&
                !r.toggleStateInputIds.contains(id)) r.toggleStateInputIds.append(id);
        }
        r.toggleTrueDialogueNode = object.value(QStringLiteral("toggleTrueDialogueNode")).toInt(-1);
        r.toggleFalseDialogueNode = object.value(QStringLiteral("toggleFalseDialogueNode")).toInt(-1);
        for (const bool yes:{true,false}) {
            const QJsonArray entries=object.value(yes?QStringLiteral("toggleTrueActions"):
                QStringLiteral("toggleFalseActions")).toArray();
            QVector<Resource::LinkedAction> &actions=yes?r.toggleTrueActions:r.toggleFalseActions;
            for (const QJsonValue &entry:entries) {
                const QJsonObject link=entry.toObject();
                const QString target=link.value(QStringLiteral("objectId")).toString();
                const QString action=link.value(QStringLiteral("action")).toString();
                if (!target.isEmpty() && (action==QStringLiteral("enable") ||
                    action==QStringLiteral("disable") || action==QStringLiteral("toggle")))
                    actions.append({target,action});
            }
        }
        r.gotoWorldName = object.value(QStringLiteral("gotoWorldName")).toString();
        r.gotoPress = object.value(QStringLiteral("gotoPress")).toBool(false);
        r.gotoStartId = object.value(QStringLiteral("gotoStartId")).toString(QStringLiteral("default"));
        r.checkpointSlot = qBound(0, object.value(QStringLiteral("checkpointSlot")).toInt(0), 9);
        r.triggerPress = object.value(QStringLiteral("triggerPress")).toBool(false);
        r.triggerDrop = object.value(QStringLiteral("triggerDrop")).toBool(false);
        r.triggerOneShot = object.value(QStringLiteral("triggerOneShot")).toBool(false);
        r.interactItemName = object.value(QStringLiteral("interactItemName")).toString();
        r.interactRadius = qBound(0, object.value(QStringLiteral("interactRadius")).toInt(32), 128);
        r.interactConsume = object.value(QStringLiteral("interactConsume")).toBool(false);
        r.sfxInteractWrong = object.value(QStringLiteral("sfxInteractWrong")).toString();
        r.sfxInteractSuccess = object.value(QStringLiteral("sfxInteractSuccess")).toString();
        r.sfxInteractCancel = object.value(QStringLiteral("sfxInteractCancel")).toString();
        r.interactDialogueNode = object.value(QStringLiteral("interactDialogueNode")).toInt(-1);
        r.interactDialogueMode = object.value(QStringLiteral("interactDialogueMode")).toString(QStringLiteral("conversation"));
        if (r.interactDialogueMode != QStringLiteral("single") &&
            r.interactDialogueMode != QStringLiteral("sequence"))
            r.interactDialogueMode = QStringLiteral("conversation");
        r.interactWrongDialogueNode = object.value(QStringLiteral("interactWrongDialogueNode")).toInt(-1);
        r.interactWrongDialogueMode = object.value(QStringLiteral("interactWrongDialogueMode")).toString(QStringLiteral("single"));
        if (r.interactWrongDialogueMode != QStringLiteral("sequence") &&
            r.interactWrongDialogueMode != QStringLiteral("conversation"))
            r.interactWrongDialogueMode = QStringLiteral("single");
        r.interactRewardItem = object.value(QStringLiteral("interactRewardItem")).toString();
        r.interactRewardCount = qBound(1, object.value(QStringLiteral("interactRewardCount")).toInt(1), 64);
        r.interactStatTarget = object.value(QStringLiteral("interactStatTarget")).toString(QStringLiteral("none"));
        r.interactStatDelta = object.value(QStringLiteral("interactStatDelta")).toInt(0);
        r.activeStateFrame = object.value(QStringLiteral("activeStateFrame")).toInt(-1);
        r.inactiveStateFrame = object.value(QStringLiteral("inactiveStateFrame")).toInt(-1);
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
        // Old Stage 5.100 used a checkbox without a fade value.
        // Recover an enabled checkbox at a visible 50% setting.
        r.objectAlphaFadePercent = qBound(0,
            a.contains(QStringLiteral("objectAlphaFadePercent"))
                ? a.value(QStringLiteral("objectAlphaFadePercent")).toInt(0)
                : (a.value(QStringLiteral("objectAlphaBlend")).toBool(false) ? 50 : 0),
            100);
        r.objectFadeAnimated = a.value(QStringLiteral("objectFadeAnimated")).toBool(false);
        r.objectFadeLow = qBound(0, a.value(QStringLiteral("objectFadeLow")).toInt(20), 100);
        r.objectFadeHigh = qBound(r.objectFadeLow, a.value(QStringLiteral("objectFadeHigh")).toInt(80), 100);
        r.objectFadeStep = qBound(1, a.value(QStringLiteral("objectFadeStep")).toInt(5), 100);
        r.objectFadeDelay = qBound(1, a.value(QStringLiteral("objectFadeDelay")).toInt(2), 32656);
        r.objectFadePingpong = a.value(QStringLiteral("objectFadePingpong")).toBool(true);
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
    // Even an empty/new world must inherit the existing project-wide bank.
    // Otherwise creating its first map could overwrite the shared definitions.
    GameGlobalStamps::Bank bank;
    QString bankError;
    if (!bank.open(m_filePath, &bankError)) {
        m_loading = false;
        QMessageBox::warning(this, tr("Project Stamps"), bankError);
        return false;
    }
    m_loadedGlobalCollisionBank = bank.collisions;
    m_loadedGlobalLoopBank = bank.loopStamps;
    m_loadedTileStampBanks = bank.tileStampBanks;
    if (obj.contains(QStringLiteral("tilemap"))) {
        QJsonObject tileData = obj.value(QStringLiteral("tilemap")).toObject();
        QVector<int> loopIndexes;
        if (!bank.expand(&tileData, &loopIndexes, &bankError)) {
            m_loading = false;
            QMessageBox::warning(this, tr("Project Stamps"),
                bankError.isEmpty() ? tr("Invalid project-global stamp references.") : bankError);
            return false;
        }
        if (!m_tilemap.fromJson(tileData)) {
            m_loading = false;
            QMessageBox::warning(this, tr("Tilemap Editor"),
                tr("The saved tilemap data is damaged or exceeds the size limits. No tilemap changes were applied."));
            return false;
        }
        bank.installLoopStamps(&m_tilemap);
        for (int i = 0; i < m_tilemap.loops.size(); ++i)
            m_tilemap.loops[i].stamp = loopIndexes.at(i);
        m_tilemapEnabled = true;
    } else {
        QJsonObject tileData = m_tilemap.toJson();
        tileData.insert(QStringLiteral("collisionStamps"), bank.collisions);
        if (!m_tilemap.fromJson(tileData)) {
            m_loading = false;
            QMessageBox::warning(this, tr("Project Stamps"),
                tr("The global collision bank could not be loaded into this new world."));
            return false;
        }
        bank.installLoopStamps(&m_tilemap);
    }
    // The atlas owns its design-time stamp bank, not the world. On the first
    // post-upgrade open, inherit older inline stamps for an atlas that does not
    // have a bank yet. Once the atlas exists in .proj it is authoritative.
    const QString atlasKey = GameGlobalStamps::Bank::atlasKey(m_tilemap.atlasPath);
    const QJsonValue savedAtlasBank = bank.tileStampBanks.value(atlasKey);
    if (savedAtlasBank.isArray()) {
        if (!SidboxTilemap::stampsFromJson(savedAtlasBank.toArray(), &m_tilemap.stamps)) {
            m_loading = false;
            QMessageBox::warning(this, tr("Tile Stamps"),
                tr("The project-wide tile stamp bank is invalid."));
            return false;
        }
    } else if (!m_tilemap.stamps.isEmpty()) {
        bank.tileStampBanks.insert(atlasKey, SidboxTilemap::stampsToJson(m_tilemap.stamps));
    }
    m_tilemap.tileStampBanks = bank.tileStampBanks;
    m_tilemap.collisionOriginalIndices.clear();
    for (int i = 0; i < m_tilemap.collisionStamps.size(); ++i)
        m_tilemap.collisionOriginalIndices.append(i < m_loadedGlobalCollisionBank.size() ? i : -1);
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
    m_undoResourceSplines.clear();
    m_redoResourceSplines.clear();
    m_undoResourceAdventures.clear();
    m_redoResourceAdventures.clear();
    rebuildScene();
    refreshResources();
    refreshProperties();
    setDirty(seededBackgroundPalette); // prompt to save new reference, never silently save
    return true;
}

void SidboxGameDesigner::syncProjectTileStampBanks(const QJsonObject &banks)
{
    // During the one-time Stage 5.7 migration, a world may still have an
    // inline bank not yet committed to .proj. Preserve only those new keys;
    // existing .proj banks ALWAYS take precedence over old world copies.
    QJsonObject merged = banks;
    for (auto it = m_tilemap.tileStampBanks.constBegin();
         it != m_tilemap.tileStampBanks.constEnd(); ++it) {
        if (!merged.contains(it.key()) && !m_loadedTileStampBanks.contains(it.key()))
            merged.insert(it.key(), it.value());
    }
    m_loadedTileStampBanks = banks;
    m_tilemap.tileStampBanks = merged;
    const QString key = GameGlobalStamps::Bank::atlasKey(m_tilemap.atlasPath);
    const QJsonValue value = merged.value(key);
    QVector<SidboxTileStamp> stamps;
    if (value.isArray() && SidboxTilemap::stampsFromJson(value.toArray(), &stamps))
        m_tilemap.stamps = stamps;
    else
        m_tilemap.stamps.clear();
    // Tile stamps are a design-time brush bank; no painted cells have changed.
    // Keep the tab's existing unsaved world changes/dirty flag untouched.
}

bool SidboxGameDesigner::saveDesign()
{
    // Sprite stamp metadata stores cell lookups over the original PPB only.
    // Validate source tile IDs without generating any new PPB file.
    for (Resource &r : m_resources) {
        if (!r.spriteStamp.active()) continue;
        QString error;
        if (!updateSpriteStamp(r, &error)) {
            QMessageBox::warning(this, tr("Sprite Stamp"), error);
            return false;
        }
    }
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
    // Stable dialogue quest IDs are data, not numeric callbacks. A Quest Designer
    // may have upgraded saved world data while this world tab remained open;
    // preserve such IDs instead of overwriting them on the next Save World.
    QJsonArray dialogNodes=m_adventure.value(QStringLiteral("nodes")).toArray();
    QJsonArray diskNodes;
    QFile previousDesign(m_filePath);
    if(previousDesign.open(QIODevice::ReadOnly))
        diskNodes=QJsonDocument::fromJson(previousDesign.readAll()).object()
            .value(QStringLiteral("adventure")).toObject()
            .value(QStringLiteral("nodes")).toArray();
    for(int ni=0;ni<dialogNodes.size();++ni) {
        QJsonObject node=dialogNodes[ni].toObject();
        QJsonArray answers=node.value(QStringLiteral("choices")).toArray();
        const QJsonArray oldAnswers=ni<diskNodes.size()
            ?diskNodes[ni].toObject().value(QStringLiteral("choices")).toArray():QJsonArray{};
        for(int ci=0;ci<answers.size();++ci) {
            QJsonObject answer=answers[ci].toObject();
            if(answer.value(QStringLiteral("text")).toString().trimmed().isEmpty())continue;
            if(answer.value(QStringLiteral("questChoiceId")).toString().isEmpty()) {
                const QJsonObject old=ci<oldAnswers.size()?oldAnswers[ci].toObject():QJsonObject{};
                QString id;
                // Keep an established answer ID even when its wording changes.
                // Replacing a non-empty answer by editing text must not break
                // quests created in the project-wide Quest Designer.
                if(!old.value(QStringLiteral("text")).toString().trimmed().isEmpty())
                    id=old.value(QStringLiteral("questChoiceId")).toString();
                if(id.isEmpty())id=QStringLiteral("dlg_")+
                    QUuid::createUuid().toString(QUuid::WithoutBraces).remove('-').left(16);
                answer.insert(QStringLiteral("questChoiceId"),id);
                answers.replace(ci,answer);
            }
        }
        node.insert(QStringLiteral("choices"),answers);
        dialogNodes.replace(ni,node);
    }
    m_adventure.insert(QStringLiteral("nodes"),dialogNodes);
    obj.insert(QStringLiteral("adventure"), m_adventure);
    QJsonObject start;
    start.insert(QStringLiteral("profile"), m_playerProfile);
    start.insert(QStringLiteral("entry"), m_playerEntry);
    start.insert(QStringLiteral("x"), m_playerStartX);
    start.insert(QStringLiteral("y"), m_playerStartY);
    start.insert(QStringLiteral("facing"), m_playerFacing);
    start.insert(QStringLiteral("transitionIn"), m_playerTransitionIn);
    start.insert(QStringLiteral("transitionOut"), m_playerTransitionOut);
    start.insert(QStringLiteral("circleOrigin"), m_playerCircleOrigin);
    start.insert(QStringLiteral("transitionFrames"), m_playerTransitionFrames);
    start.insert(QStringLiteral("spotlightEnabled"), m_playerSpotlightEnabled);
    start.insert(QStringLiteral("spotlightRadius"), m_playerSpotlightRadius);
    start.insert(QStringLiteral("spotlightFeather"), m_playerSpotlightFeather);
    start.insert(QStringLiteral("spotlightCenter"), m_playerSpotlightCenter);
    start.insert(QStringLiteral("spotlightOffsetX"), m_playerSpotlightOffsetX);
    start.insert(QStringLiteral("spotlightOffsetY"), m_playerSpotlightOffsetY);
    start.insert(QStringLiteral("spotlightFlipX"), m_playerSpotlightFlipX);
    start.insert(QStringLiteral("spotlightFlipY"), m_playerSpotlightFlipY);
    start.insert(QStringLiteral("spotlightOpacity"), m_playerSpotlightOpacity);
    start.insert(QStringLiteral("spotlightStableDither"), m_playerSpotlightStableDither);
    start.insert(QStringLiteral("spotlightAnimMode"), m_playerSpotlightAnimMode);
    start.insert(QStringLiteral("spotlightAnimMin"), m_playerSpotlightAnimMin);
    start.insert(QStringLiteral("spotlightAnimMax"), m_playerSpotlightAnimMax);
    start.insert(QStringLiteral("spotlightAnimDelayMin"), m_playerSpotlightAnimDelayMin);
    start.insert(QStringLiteral("spotlightAnimDelayMax"), m_playerSpotlightAnimDelayMax);
    start.insert(QStringLiteral("spotlightAnimPulseDelay"), m_playerSpotlightAnimPulseDelay);
    start.insert(QStringLiteral("spotlightMaskIndex"), m_playerSpotlightMaskIndex);
    start.insert(QStringLiteral("spotlightMaskColour"), m_playerSpotlightMaskColour);
    obj.insert(QStringLiteral("playerStart"), start);
    QJsonObject weather;
    weather.insert(QStringLiteral("mode"), m_weatherMode);
    weather.insert(QStringLiteral("density"), m_weatherDensity);
    weather.insert(QStringLiteral("wind"), m_weatherWind);
    weather.insert(QStringLiteral("particleSize"), m_weatherParticleSize);
    weather.insert(QStringLiteral("particleTileId"), m_weatherParticleTile);
    weather.insert(QStringLiteral("particleAtlasId"), m_weatherParticleAtlasId);
    weather.insert(QStringLiteral("particleTileSize"), m_weatherParticleTileSize);
    weather.insert(QStringLiteral("paletteIndex"), m_weatherPaletteIndex);
    weather.insert(QStringLiteral("lightningInterval"), m_weatherLightningInterval);
    weather.insert(QStringLiteral("lightningStrength"), m_weatherLightningStrength);
    weather.insert(QStringLiteral("lightningCurve"), m_weatherLightningCurve);
    weather.insert(QStringLiteral("lightningOverlayEnabled"), m_weatherLightningOverlay);
    weather.insert(QStringLiteral("paletteFlashStrength"), m_weatherPaletteFlashStrength);
    weather.insert(QStringLiteral("suspendSpotlightOnLightning"), m_weatherSuspendSpotlight);
    QJsonObject dayNight;
    dayNight.insert(QStringLiteral("mode"), m_dayNightMode);
    dayNight.insert(QStringLiteral("targetColour"), m_dayNightColour);
    dayNight.insert(QStringLiteral("strength"), m_dayNightStrength);
    dayNight.insert(QStringLiteral("dayFrames"), m_dayNightDayFrames);
    dayNight.insert(QStringLiteral("nightFrames"), m_dayNightNightFrames);
    dayNight.insert(QStringLiteral("fadeFrames"), m_dayNightFadeFrames);
    dayNight.insert(QStringLiteral("startAtNight"), m_dayNightStartAtNight);
    dayNight.insert(QStringLiteral("dayActions"), m_dayEvents);
    dayNight.insert(QStringLiteral("nightActions"), m_nightEvents);
    obj.insert(QStringLiteral("dayNight"), dayNight);
    obj.insert(QStringLiteral("weather"), weather);
    QJsonArray otherStarts;
    for (const PlayerStartLocation &location : m_otherPlayerStarts) {
        QJsonObject point;
        point.insert(QStringLiteral("id"), location.id);
        point.insert(QStringLiteral("name"), location.name);
        point.insert(QStringLiteral("x"), location.x);
        point.insert(QStringLiteral("y"), location.y);
        point.insert(QStringLiteral("facing"), location.facing);
        point.insert(QStringLiteral("transitionIn"), location.transitionIn);
        point.insert(QStringLiteral("transitionOut"), location.transitionOut);
        point.insert(QStringLiteral("circleOrigin"), location.circleOrigin);
        point.insert(QStringLiteral("transitionFrames"), location.transitionFrames);
        otherStarts.append(point);
    }
    obj.insert(QStringLiteral("playerStarts"), otherStarts);
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
        if (r.kind == QStringLiteral("sprite") && r.spriteStamp.active())
            a.insert(QStringLiteral("spriteStamp"), r.spriteStamp.toJson());
        if (r.kind == QStringLiteral("sprite") && !r.animationFile.isEmpty())
            a.insert(QStringLiteral("animationFile"), r.animationFile);
        a.insert(QStringLiteral("locked"), r.locked);
        if (r.kind == QStringLiteral("sprite")) {
            a.insert(QStringLiteral("drawBehindTiles"), r.drawBehindTiles);
            a.insert(QStringLiteral("objectFlipX"), r.objectFlipX);
            a.insert(QStringLiteral("objectFlipY"), r.objectFlipY);
            a.insert(QStringLiteral("objectAlphaFadePercent"), r.objectAlphaFadePercent);
            a.insert(QStringLiteral("objectFadeAnimated"), r.objectFadeAnimated);
            a.insert(QStringLiteral("objectFadeLow"), r.objectFadeLow);
            a.insert(QStringLiteral("objectFadeHigh"), r.objectFadeHigh);
            a.insert(QStringLiteral("objectFadeStep"), r.objectFadeStep);
            a.insert(QStringLiteral("objectFadeDelay"), r.objectFadeDelay);
            a.insert(QStringLiteral("objectFadePingpong"), r.objectFadePingpong);
        }
        if (r.kind == QStringLiteral("sprite") && r.objectType != QStringLiteral("decoration")) {
            QJsonObject object;
            object.insert(QStringLiteral("type"), r.objectType);
            object.insert(QStringLiteral("pickupKind"), r.pickupKind);
            object.insert(QStringLiteral("value"), r.objectValue);
            object.insert(QStringLiteral("pickupTrackingConfigured"), r.pickupTrackingConfigured);
            object.insert(QStringLiteral("pickupShowInventory"), r.pickupShowInventory);
            object.insert(QStringLiteral("pickupShowHud"), r.pickupShowHud);
            object.insert(QStringLiteral("pickupStatTarget"), r.pickupStatTarget);
            object.insert(QStringLiteral("pickupPersistent"), r.pickupPersistent);
            object.insert(QStringLiteral("pickupAllowEnemyLoot"), r.pickupAllowEnemyLoot);
            object.insert(QStringLiteral("enemyLootMin"), r.enemyLootMin);
            object.insert(QStringLiteral("enemyLootMax"), r.enemyLootMax);
            QJsonArray enemyLootIds;
            for (const QString &id : r.enemyLootIds) enemyLootIds.append(id);
            object.insert(QStringLiteral("enemyLootIds"), enemyLootIds);
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
            object.insert(QStringLiteral("enemyStompSideKick"), r.enemyStompSideKick);
            object.insert(QStringLiteral("enemyAttackDirection"), r.enemyAttackDirection);
            object.insert(QStringLiteral("enemyHurtsOnTouch"), r.enemyHurtsOnTouch);
            object.insert(QStringLiteral("enemyDamage"), r.enemyDamage);
            object.insert(QStringLiteral("enemyRoam"), r.enemyRoam);
            object.insert(QStringLiteral("enemyRoamSpeed"), r.enemyRoamSpeed);
            object.insert(QStringLiteral("enemyStepHeight"), r.enemyStepHeight);
            object.insert(QStringLiteral("enemyRoamLeft"), r.enemyRoamLeft);
            object.insert(QStringLiteral("enemyDefeatFrame"), r.enemyDefeatFrame);
            object.insert(QStringLiteral("enemyDefeatFrames"), r.enemyDefeatDelay); // backward-readable
            object.insert(QStringLiteral("enemyDefeatCount"), r.enemyDefeatCount);
            object.insert(QStringLiteral("enemyDefeatDelay"), r.enemyDefeatDelay);
            object.insert(QStringLiteral("enemyStompOffsetX"), r.enemyStompOffsetX);
            object.insert(QStringLiteral("enemyStompOffsetY"), r.enemyStompOffsetY);
            object.insert(QStringLiteral("enemyStompWidth"), r.enemyStompWidth);
            object.insert(QStringLiteral("enemyStompHeight"), r.enemyStompHeight);
            object.insert(QStringLiteral("initiallyActive"), r.objectInitiallyActive);
            object.insert(QStringLiteral("particlePreset"), r.particlePreset);
            object.insert(QStringLiteral("particleAreaW"), r.particleAreaW);
            object.insert(QStringLiteral("particleAreaH"), r.particleAreaH);
            object.insert(QStringLiteral("particleCount"), r.particleCount);
            object.insert(QStringLiteral("particleInterval"), r.particleInterval);
            object.insert(QStringLiteral("particlePrepopulate"), r.particlePrepopulate);
            object.insert(QStringLiteral("particleLifetime"), r.particleLifetime);
            object.insert(QStringLiteral("particleWind"), r.particleWind);
            object.insert(QStringLiteral("particleFall"), r.particleFall);
            object.insert(QStringLiteral("particleGravity"), r.particleGravity);
            object.insert(QStringLiteral("particleFlutter"), r.particleFlutter);
            object.insert(QStringLiteral("particleSwirlRadius"), r.particleSwirlRadius);
            object.insert(QStringLiteral("particleSwirlSpeed"), r.particleSwirlSpeed);
            object.insert(QStringLiteral("particlePlayerLayerMix"), r.particlePlayerLayerMix);
            object.insert(QStringLiteral("particleFadeEnabled"), r.particleFadeEnabled);
            object.insert(QStringLiteral("particleFadeIn"), r.particleFadeIn);
            object.insert(QStringLiteral("particleFadeOut"), r.particleFadeOut);
            object.insert(QStringLiteral("particleFadeSpeed"), r.particleFadeSpeed);
            object.insert(QStringLiteral("hazardDamage"), r.hazardDamage);
            object.insert(QStringLiteral("deathNote"), r.deathNote);
            object.insert(QStringLiteral("damageTarget"), r.damageTarget);
            object.insert(QStringLiteral("damageDelta"), r.damageConfigured ? r.damageDelta : -r.hazardDamage);
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
            if (r.objectType==QStringLiteral("trigger")) {
                QJsonArray links;
                for (const Resource::LinkedAction &link : r.triggerExtraActions)
                    links.append(QJsonObject{{QStringLiteral("objectId"),link.objectId},
                                              {QStringLiteral("action"),link.action}});
                object.insert(QStringLiteral("triggerExtraActions"),links);
            }
            if (r.objectType==QStringLiteral("enemy")) {
                QJsonArray links;
                for (const Resource::LinkedAction &link : r.enemyDefeatExtraActions)
                    links.append(QJsonObject{{QStringLiteral("objectId"),link.objectId},
                                             {QStringLiteral("action"),link.action}});
                object.insert(QStringLiteral("enemyDefeatExtraActions"),links);
            }
            object.insert(QStringLiteral("eventActions"),r.eventActions);
            // Independent logic can be hosted by Triggers OR Stompable Enemies.
            // Preserve it on an ordinary world save, not just Visual Nodes Save.
            if (r.objectType==QStringLiteral("trigger") ||
                r.objectType==QStringLiteral("enemy") ||
                r.objectType==QStringLiteral("lift") ||
                (r.objectType!=QStringLiteral("collectable") && !r.logicNodes.isEmpty()))
                object.insert(QStringLiteral("logicNodes"), r.logicNodes);
            if (r.objectType==QStringLiteral("trigger")) {
                object.insert(QStringLiteral("toggleStateTargetId"), r.toggleStateTargetId);
                object.insert(QStringLiteral("toggleStateOperator"), r.toggleStateOperator);
                QJsonArray stateInputs;
                for (const QString &input : r.toggleStateInputIds) stateInputs.append(input);
                object.insert(QStringLiteral("toggleStateInputIds"), stateInputs);
                object.insert(QStringLiteral("toggleTrueDialogueNode"),r.toggleTrueDialogueNode);
                object.insert(QStringLiteral("toggleFalseDialogueNode"),r.toggleFalseDialogueNode);
                for (const bool yes:{true,false}) {
                    QJsonArray links;
                    const QVector<Resource::LinkedAction> &actions=yes?r.toggleTrueActions:r.toggleFalseActions;
                    for (const Resource::LinkedAction &link:actions)
                        links.append(QJsonObject{{QStringLiteral("objectId"),link.objectId},
                                                 {QStringLiteral("action"),link.action}});
                    object.insert(yes?QStringLiteral("toggleTrueActions"):
                                      QStringLiteral("toggleFalseActions"),links);
                }
            }
            object.insert(QStringLiteral("gotoWorldName"), r.gotoWorldName);
            object.insert(QStringLiteral("gotoPress"), r.gotoPress);
            object.insert(QStringLiteral("gotoStartId"), r.gotoStartId);
            object.insert(QStringLiteral("checkpointSlot"), qBound(0, r.checkpointSlot, 9));
            object.insert(QStringLiteral("triggerPress"), r.triggerPress);
            object.insert(QStringLiteral("triggerDrop"), r.triggerDrop);
            object.insert(QStringLiteral("triggerOneShot"), r.triggerOneShot);
            object.insert(QStringLiteral("interactItemName"), r.interactItemName);
            object.insert(QStringLiteral("interactRadius"), r.interactRadius);
            object.insert(QStringLiteral("interactConsume"), r.interactConsume);
            object.insert(QStringLiteral("sfxInteractWrong"), r.sfxInteractWrong);
            object.insert(QStringLiteral("sfxInteractSuccess"), r.sfxInteractSuccess);
            object.insert(QStringLiteral("sfxInteractCancel"), r.sfxInteractCancel);
            object.insert(QStringLiteral("interactDialogueNode"), r.interactDialogueNode);
            object.insert(QStringLiteral("interactDialogueMode"), r.interactDialogueMode);
            object.insert(QStringLiteral("interactWrongDialogueNode"), r.interactWrongDialogueNode);
            object.insert(QStringLiteral("interactWrongDialogueMode"), r.interactWrongDialogueMode);
            object.insert(QStringLiteral("interactRewardItem"), r.interactRewardItem);
            object.insert(QStringLiteral("interactRewardCount"), r.interactRewardCount);
            object.insert(QStringLiteral("interactStatTarget"), r.interactStatTarget);
            object.insert(QStringLiteral("interactStatDelta"), r.interactStatDelta);
            object.insert(QStringLiteral("activeStateFrame"), r.activeStateFrame);
            object.insert(QStringLiteral("inactiveStateFrame"), r.inactiveStateFrame);
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
        GameGlobalStamps::Bank bank;
        QString stampError;
        if (!bank.open(m_filePath, &stampError)) {
            QMessageBox::warning(this, tr("Project Stamps"), stampError);
            return false;
        }
        // A world never saves its own definition copies: it saves only
        // placement indices, and the project stores the shared bank.
        for (const SidboxLoopTrack &loop : m_tilemap.loops)
            if (loop.stamp < 0 || loop.stamp >= m_tilemap.loopStamps.size()) {
                QMessageBox::warning(this, tr("Project Stamps"),
                    tr("Loop placement has no valid global stamp index."));
                return false;
            }
        if (bank.collisions != m_loadedGlobalCollisionBank ||
            bank.loopStamps != m_loadedGlobalLoopBank) {
            QMessageBox::warning(this, tr("Project Stamps"),
                tr("Another world has changed the project stamp bank since this "
                   "design was opened. Close and reopen this world before saving "
                   "to avoid replacing its global stamps."));
            return false;
        }
        // The current atlas may have unswitched edits. Keep its current
        // stamp cells alongside all other atlas banks changed in this session.
        QJsonObject requestedTileBanks = m_tilemap.tileStampBanks;
        const QString currentAtlasKey = GameGlobalStamps::Bank::atlasKey(m_tilemap.atlasPath);
        requestedTileBanks.insert(currentAtlasKey,
                                  SidboxTilemap::stampsToJson(m_tilemap.stamps));
        // Only submit atlas banks actually edited in this world. A stale
        // snapshot of another atlas must never overwrite its newer .proj bank.
        // Open tabs receive fresh definitions after each save; changes made
        // by another IDE process still get a proper conflict warning.
        for (auto it = requestedTileBanks.constBegin(); it != requestedTileBanks.constEnd(); ++it) {
            const QJsonValue oldValue = m_loadedTileStampBanks.value(it.key());
            const QJsonValue liveValue = bank.tileStampBanks.value(it.key());
            if (it.value() == oldValue) continue;
            if (oldValue != liveValue && it.value() != liveValue) {
                QMessageBox::warning(this, tr("Tile Stamps"),
                    tr("The stamp bank for atlas '%1' was edited by another "
                       "IDE process while you were editing it. Reopen only "
                       "the Tilemap Editor to review the newer bank.").arg(it.key()));
                return false;
            }
            bank.tileStampBanks.insert(it.key(), it.value());
        }
        // The editor retains old-to-new identities through Add, Remove,
        // Undo and Redo. Reindex other worlds before committing the bank.
        QVector<int> oldToNew(bank.collisions.size(), -1);
        if (m_tilemap.collisionOriginalIndices.size() != m_tilemap.collisionStamps.size()) {
            QMessageBox::warning(this, tr("Project Stamps"),
                tr("Global slope index history is missing. Reopen this world before saving."));
            return false;
        }
        for (int i = 0; i < m_tilemap.collisionOriginalIndices.size(); ++i) {
            const int old = m_tilemap.collisionOriginalIndices.at(i);
            if (old < 0) continue; // Newly added definition
            if (old >= oldToNew.size() || oldToNew.at(old) >= 0) {
                QMessageBox::warning(this, tr("Project Stamps"),
                    tr("The global slope index mapping is inconsistent."));
                return false;
            }
            oldToNew[old] = i;
        }
        bank.takeDefinitions(m_tilemap);
        // If no other world changed this bank, it is now project-owned.
        if (!bank.remapOtherWorlds(m_filePath, m_loadedGlobalCollisionBank,
                                   oldToNew, &stampError)) {
            QMessageBox::warning(this, tr("Project Stamps"), stampError);
            return false;
        }
        if (!bank.save(&stampError)) {
            QMessageBox::warning(this, tr("Project Stamps"), stampError);
            return false;
        }
        m_loadedGlobalCollisionBank = bank.collisions;
        m_loadedGlobalLoopBank = bank.loopStamps;
        m_loadedTileStampBanks = bank.tileStampBanks;
        m_tilemap.tileStampBanks = bank.tileStampBanks;
        m_tilemap.collisionOriginalIndices.clear();
        for (int i = 0; i < m_tilemap.collisionStamps.size(); ++i)
            m_tilemap.collisionOriginalIndices.append(i);
        obj.insert(QStringLiteral("tilemap"), GameGlobalStamps::Bank::worldReferences(m_tilemap));
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
    // Only the active design may refresh canonical generated spline code.
    // Editing a different .sbgm must not silently replace that world's paths.
    if ((!GameWorldSnapshot::hasActiveSelection(m_filePath)
         || GameWorldSnapshot::isActive(m_filePath))
        && QFileInfo::exists(pathHeader) && !exportSplinePaths(false)) return false;
    const QString worldBase = sidboxTilemapWorldBaseName(m_filePath);
    const QString tileHeader = QDir(QFileInfo(m_filePath).absolutePath())
        .filePath(QStringLiteral("worlds/") + worldBase + QStringLiteral("/gamelevels/")
                  + worldBase + QStringLiteral(".h"));
    if (m_tilemapEnabled && QFileInfo::exists(tileHeader) && !exportTilemap(false)) return false;
    setDirty(false);
    if (m_tilemapEnabled) {
        // The .proj save succeeded: instantly refresh the shared atlas bank in
        // every open world tab of this SAME game project (without reloading
        // or discarding their world-specific, possibly unsaved, map changes).
        const QString projectDir = QFileInfo(m_filePath).absolutePath();
        for (QWidget *widget : QApplication::allWidgets()) {
            auto *other = dynamic_cast<SidboxGameDesigner *>(widget);
            if (other && QFileInfo(other->m_filePath).absolutePath() == projectDir)
                other->syncProjectTileStampBanks(m_loadedTileStampBanks);
        }
    }
    return true;
}


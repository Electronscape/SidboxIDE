#ifndef SIDBOX_GAMEDESIGNER_H
#define SIDBOX_GAMEDESIGNER_H

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>
#include <QHash>
#include <QDateTime>
#include <QElapsedTimer>
#include <QPoint>
#include <QPointF>
#include <QStringList>
#include "gameaudio.h"
#include "gamepalette.h"
#include "gametilemap.h"
#include "idetheme.h"
#include <functional>

class QGraphicsScene;
class QGraphicsView;
class QGraphicsItem;
class QGraphicsRectItem;
class QGraphicsPathItem;
class QTreeWidget;
class QTreeWidgetItem;
class QSpinBox;
class QFormLayout;
class QLineEdit;
class QCheckBox;
class QComboBox;
class QLabel;
class QPushButton;
class QTimer;
class QShowEvent;

/*
 * Stage 53: V1 game design document with host-side PPB import/preview and
 * optional generated .c/.h resource files. Game logic, GUI designs and the
 * firmware are never rewritten. .sbgm stays a JSON design file, not C.
 */
class SidboxGameDesigner final : public QWidget
{
public:
    explicit SidboxGameDesigner(const QString &designFilePath,
                               QWidget *parent = nullptr);
    ~SidboxGameDesigner() override;

    std::function<void()> tabTitleChanged;
    std::function<void()> assetFilesChanged;
    // MainWindow owns project-wide .sbgm discovery and batch updates.
    std::function<bool()> updateAllProjectWorlds;
    // True when an open main.c editor has unsaved changes.
    std::function<bool(const QString &)> mainSourceHasUnsavedEdits;
    QString filePath() const;
    void setFilePath(const QString &newPath);
    QString displayName() const;
    bool isModified() const;
    bool isValid() const;
    bool saveDesign();
    bool tilemapBuildFilesMissing() const;
    bool exportTilemapForCompile();
    // Safe generated-only preflight (legacy/manual use; does not overwrite helpers).
    bool regenerateBuildFiles();
    // The SAME full Update Project operation as the Game Designer button:
    // ZIP backup, SDK helper refresh, exports, maingame.c.txt, managed main.c.
    // fromCompile: F5 has already obtained (or remembered) consent; skip the
    // redundant confirmation and success notice, but always show errors.
    // False on confirmation cancel or failure; caller must stop the build.
    bool updateGameProject(bool fromCompile = false);
    void setTheme(const IDETheme &theme);

protected:
    void changeEvent(QEvent *event) override;
    void showEvent(QShowEvent *event) override;
    void restoreWorldViewPosition();
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    struct Resource {
        QString name;
        QString id;   // stable identifier for active palette selection
        QString plane = QStringLiteral("foreground");
        QString kind;
        QString path;
        bool musicPlayOnStart = false; // Only one Music resource can auto-start.
        int x = 0;
        int y = 0;
        int scale = 100;
        int cellWidth = 0;  // 0 = whole image (old Stage 52 files stay compatible)
        int cellHeight = 0;
        int frame = 0;
        QString animationFile; // optional .sbanim sidecar with named player animation states
        bool locked = false;
        // Stage 3.0B: optional behaviours on each placed sprite instance.
        QString objectType = QStringLiteral("decoration");
        int pickupKind = 1;
        int objectValue = 10;
        int hitWidth = 16, hitHeight = 16;
        int conveyorSpeed = 2, springStrength = 11;
        int springLaunchX = 0; // Signed horizontal spring launch in pixels/frame; 0 = straight up.
        bool springJumpBoost = false; // Opt-in only, including older designs without this field.
        bool springTouch = false; // OFF = land on top; ON = touch from any direction.
        bool springSlide = false; // OFF = constant sideways push; ON = momentum with friction.
        bool breakTouch = false; // false = stomp from above; true = touch/leave/touch again
        bool breakBounce = false; // launch after each qualifying stomp
        bool breakFromBelow = false; // player jumps into underside (not stomp/touch)
        QString breakDropCollectableId; // stable ID of collectable spawned on final break
        bool breakRewardImpulse = false; // Opt-in launch; default matches Stage 3.96 gravity-only drop.
        int breakRewardVx = 0; // signed horizontal launch speed, pixels/frame
        int breakRewardVy = -8; // signed vertical launch speed, negative is UP
        int breakHits = 1; // 1..4, stored per placed instance
        int breakStrength = 11; // upward px/frame for bounce
        int breakLaunchX = 0; // -left, +right px/frame
        bool enemyStompSideKick = false; // Optional horizontal impulse on a VULNERABLE hit, separate from side-contact knockback.
        int enemyAttackDirection = 0; // 0=from above, 1=from below, 2=either (uses the SAME editable green box).
        bool enemyHurtsOnTouch = true; // Side/underside hits use the shared player-damage event.
        int enemyDamage = 1;
        bool enemyRoam = false; // Optional ground patrol (Advanced Platformer tile collision).
        int enemyRoamSpeed = 1; // Whole pixels per 50-Hz frame; 1..8.
        int enemyStepHeight = 4; // Slope/step climb and descent allowance, pixels.
        bool enemyRoamLeft = false; // Initial patrol direction; checked from X flip independently.
        int enemyDefeatFrame = -1; // -1=vanish immediately; otherwise show this atlas frame.
        int enemyDefeatFrames = 20; // Legacy one-frame duration (older projects).
        int enemyDefeatCount = 1; // Sequential atlas frames, 1..256-start.
        int enemyDefeatDelay = 20; // 50-Hz ticks PER frame; defaults to old pose duration.
        int enemyStompOffsetX = 0, enemyStompOffsetY = 0; // Relative to normal body box.
        int enemyStompWidth = 0; // 0=match body hitbox width.
        int enemyStompHeight = 1; // Vertical tolerance beneath vulnerable-zone top.
        bool objectInitiallyActive = true; // Default for all old designs.
        bool drawBehindTiles = false; // Per-placed-sprite layer, even for decorations.
        bool objectFlipX = false, objectFlipY = false; // Optional BOB mirroring; hitbox stays in place.
        int hazardDamage = 1; // Per contact; game owns its health/score rules.
        int hazardKickX = 0, hazardKickY = -11; // Signed px/frame; Y negative is UP.
        bool hazardKick = true;
        bool hazardHurtAnimation = true;
        bool hazardFlash = true;
        int hazardFlashColour = 15; // Foreground palette index, 0..255.
        int hazardFlashCount = 4; // Number of ON flashes.
        int hazardFlashFrames = 3; // ON and OFF frames per flash.

        QString targetObjectId; // Stable resource ID; never a tree index or name.
        QString targetAction = QStringLiteral("none"); // enable, disable, toggle.
        QString gotoWorldName; // target world basename, not a path or tab index
        bool gotoPress = false; // false = walk into door; true = FIRE2 contact
        QString gotoStartId = QStringLiteral("default"); // stable destination spawn ID
        bool triggerPress = false; // false = touch to activate, true = BTN_FIRE2.
        bool triggerOneShot = false; // Destroy/hide trigger after firing.
        QString triggerMusicId; // Stable ID of music tree resource; empty means no chosen track.
        QString triggerMusicAction = QStringLiteral("none"); // none, play, stop.
        // Stage 3.12: sound references are stable IDs of Sounds in Game Resources.
        // Empty ID = no sound. They are NEVER hard-coded filesystem paths.
        QString sfxPickup, sfxRespawn, sfxStart, sfxMove, sfxStop;
        QString sfxReverse, sfxSpring, sfxAmbient;
        // Independent optional sounds for each placed Breakable.
        QString sfxBreakHit, sfxBreakBounce, sfxBreakFinish;
        QString sfxHazardHit, sfxHazardBounce, sfxHazardAmbient;
        int respawnFrames = 0;       // 0 = collected permanently.
        int audioRadius = 0;         // 0 = fixed volume/pan; otherwise attenuation in pixels.
        int audioFadeFrames = 8;     // Fade of continuously moving/ambient sounds.
        QString objectSplineId; // stable spline ID, not name/array position
        int objectSplineStartDelay = 0; // 50 Hz frames to wait before first path movement (per placed object)
        bool objectAnimated = false;
        int animFirst = 0, animCount = 1, animTicks = 5;
        QString animMode = QStringLiteral("loop");
        // Background rendering is independent of its foreground/sprite CLUT.
        // "sprite" keeps legacy gfx_drawbob; "direct_ready" is already
        // column-major; "direct_convert" transposes ordinary row-major PPB.
        QString backgroundMode = QStringLiteral("sprite");
        SidboxAudioSettings audio; // Stage 54: persisted only for sound/music
    };

    void buildUi();
    QString helperTemplatesRoot() const;
    void addCodeHelper(const QString &category, const QString &base);
    void showSplineMenu(const QPoint &viewPos);
    void editSplineProperties(int index);
    void rebuildSplineOverlay();
    void updateSplineCurve();
    bool exportSplinePaths(bool showMessage);
    void openAdventureEditor(const QString &focusNpcSpriteId = QString());
    void editPlayerStartLocation(const QString &id);
    bool exportAdventure(QString *error);
    bool hasAdventure() const;
    // Snapshot of project-global stamp bank at last world load/save.
    // Never overwrite changes saved from another open world tab.
    QJsonArray m_loadedGlobalCollisionBank;
    QJsonArray m_loadedGlobalLoopBank;
    QJsonObject m_loadedTileStampBanks;
    // Keep atlas-owned tile stamps current in every open world of this project.
    // No world tabs need closing and a world save cannot undo another tab's stamps.
    void syncProjectTileStampBanks(const QJsonObject &banks);
    void openTilemapEditor();
    void openPlayerAnimationEditor(int resourceIndex = -1);
    void openPlayerEditor();
    void editPlayerStart();
    void rebuildTilemapOverlay();
    bool exportTilemap(bool showMessage, bool includeMissingHelper = false);
    struct SplinePath {
        QString name;
        QString id; // persistent ID; renaming the path keeps object attachments
        QVector<QPoint> points;
        QVector<int> pointPauses; // One wait in frames per point; zero = no pause.
        int durationFrames = 100;
        bool loop = true;
    };
    bool loadDesign();
    void setDirty(bool dirty = true);
    void refreshResources();
    void rebuildScene();
    void refreshColourCyclePreview();
    void refreshFrame();
    void refreshProperties();
    void selectResource(int index);
    void syncCanvasSelection();
    void addResource(const QString &kind, const QString &plane = QStringLiteral("foreground"));
    void suggestFirstBackgroundPalette(const Resource &background);
    void addPlaceholder();
    void importDroppedFiles(const QStringList &paths, const QString &targetKind,
                            const QString &targetPlane);
    void deleteSelectedResource();
    void copySelectedSprite(int resourceIndex = -1);
    void pasteCopiedSprite();
    void undoResourceEdit();
    void redoResourceEdit();
    void rememberResourceEdit();
    void restoreResourceSnapshot(const QVector<Resource> &snapshot);
    void suggestSpriteCells(Resource &resource);
    QString resourcePlane(const Resource &resource) const;
    QVector<QRgb> activePalette(const QString &plane) const;
    void refreshPaletteSelectors();
    void refreshPlanePreview();
    void buildSharedPalette();
    void openPaletteEditor(int resourceIndex = -1);
    void pickResourceFile();
    void importPngAsPpb(const QString &suggestedKind = QStringLiteral("tileatlas"));
    void exportSelectedC();
    void generateGameCode();

    bool generateGameCodeCore(bool embedPixels, bool batchMode);
    void configureGameObject(int index);
    void refreshObjectHitbox();
    bool installMissingWorldHelpers(QString *error, bool prompt = true);
    bool exportWorldItems(QString *error);
    bool exportExampleMain(QString *error);
    bool syncManagedMain(QString *error);
    QString splineSymbol(int index) const;
    QString spriteSymbol(const Resource &r) const;
    void updateSelectedPixmap();
    QImage resourcePreview(const Resource &resource, QString *details = nullptr) const;
    QImage cachedImage(const QString &path, QString *error = nullptr) const;
    void updateSelectedItem();
    void syncFromSceneItem(QGraphicsItem *item);
    void refreshColours();
    int selectedIndex() const;
    QString resolvedPath(const QString &storedPath) const;
    QString storedPath(const QString &absolutePath) const;

    IDETheme m_theme = defaultIDETheme();
    QString m_filePath;
    QVector<Resource> m_resources;
    QJsonObject m_adventure; // Advanced Platformer dialogue/inventory data (in .sbgm)
    // Stage 5.4: world owns spawn only. The player is project-owned (.sbpi).
    QString m_playerProfile = QStringLiteral("players/player.sbpi");
    QString m_playerEntry = QStringLiteral("default");
    int m_playerStartX = 0, m_playerStartY = 0;
    int m_playerFacing = 1; // 0=left, 1=right
    // Additional, named destination entrances belong to this world only.
    struct PlayerStartLocation {
        QString id;
        QString name;
        int x = 0, y = 0, facing = 1;
    };
    QVector<PlayerStartLocation> m_otherPlayerStarts;
    QGraphicsItem *m_playerStartMarker = nullptr;

    bool m_dirty = false;
    bool m_valid = true;
    bool m_loading = false;
    bool m_syncSelection = false;
    QGraphicsScene *m_scene = nullptr;
    QGraphicsView *m_view = nullptr;
    // The WORLD canvas pan is independent of the tilemap editor and of
    // cameraX/Y used by the running game. Restore after the view is shown.
    QPointF m_savedWorldViewCenter;
    bool m_restoreWorldViewCenter = false;
    bool m_worldPanMoved = false;
    QGraphicsRectItem *m_cameraFrame = nullptr;
    QGraphicsRectItem *m_worldFrame = nullptr;
    QGraphicsItem *m_tilemapOverlayItem = nullptr;
    QVector<QGraphicsItem *> m_loopOverlayItems; // Visual-only, no collisions.
    QTimer *m_objectPreviewTimer = nullptr;
    QElapsedTimer m_objectPreviewClock;
    QGraphicsPathItem *m_splineCurveItem = nullptr;
    QGraphicsRectItem *m_objectHitbox = nullptr;
    QVector<QGraphicsItem *> m_splineHandleItems;
    QVector<SplinePath> m_splinePaths;
    int m_activeSpline = -1;
    SidboxTilemap m_tilemap;
    bool m_tilemapExternal = false; // false = embed .c, true = SD .map
    bool m_tilemapEnabled = false;
    QTreeWidget *m_resourceTree = nullptr;
    QFormLayout *m_propertiesForm = nullptr;
    QWidget *m_positionFields = nullptr;
    QPushButton *m_editPaletteButton = nullptr;
    QSpinBox *m_worldWidth = nullptr;
    QSpinBox *m_worldHeight = nullptr;
    QSpinBox *m_cameraX = nullptr;
    QSpinBox *m_cameraY = nullptr;
    QSpinBox *m_propX = nullptr;
    QSpinBox *m_propY = nullptr;
    QSpinBox *m_propScale = nullptr;
    QSpinBox *m_propCellWidth = nullptr;
    QSpinBox *m_propCellHeight = nullptr;
    QSpinBox *m_propFrame = nullptr;
    QCheckBox *m_propLocked = nullptr;
    QCheckBox *m_musicPlayOnStart = nullptr;
    QComboBox *m_propPlane = nullptr;
    QComboBox *m_propBackgroundMode = nullptr;
    QComboBox *m_planeMode = nullptr;
    QCheckBox *m_showLabels = nullptr;
    QCheckBox *m_showTilemap = nullptr;
    QCheckBox *m_showColourCycles = nullptr;
    SidboxGamePalette::ColourCycle m_frontColourCycle;
    SidboxGamePalette::ColourCycle m_backColourCycle;
    int m_frontCyclePhase = 0;
    int m_backCyclePhase = 0;
    int m_lastFrontCyclePhase = -1;
    int m_lastBackCyclePhase = -1;
    QCheckBox *m_forcePalette = nullptr;
    QCheckBox *m_previewPaletteAlpha = nullptr;
    QComboBox *m_frontPalette = nullptr;
    QComboBox *m_backPalette = nullptr;
    QPushButton *m_buildPaletteButton = nullptr;
    QString m_activeForegroundPalette;
    QString m_activeBackgroundPalette;
    QCheckBox *m_snap = nullptr;
    QComboBox *m_snapStep = nullptr;
    // Resource-only undo history: never snapshots bitmap data or actual files.
    QVector<QVector<Resource>> m_undoResources;
    QVector<QVector<Resource>> m_redoResources;
    // Keep imported object splines in the same Ctrl+Z transaction.
    QVector<QVector<SplinePath>> m_undoResourceSplines;
    QVector<QVector<SplinePath>> m_redoResourceSplines;
    // Imported Adventure items and pickup types belong to the same Ctrl+Z step.
    QVector<QJsonObject> m_undoResourceAdventures;
    QVector<QJsonObject> m_redoResourceAdventures;
    // Stage 5.13: one application-wide clipboard survives world-tab changes.
    // The Resource copy retains every gameplay field, not merely its artwork.
    static Resource s_copiedWorldObject;
    static QVector<Resource> s_copiedWorldResources;
    static QVector<SplinePath> s_copiedWorldSplines;
    static QJsonObject s_copiedWorldAdventure;
    static QString s_copiedWorldSource;
    static bool s_hasCopiedWorldObject;
    int m_dragResourceIndex = -1;
    QPoint m_dragResourceStart;
    QVector<Resource> m_dragBefore;
    bool m_spaceHeld = false;
    bool m_panningCamera = false; // SPACE + left = move game's camera
    bool m_middlePanning = false; // middle drag = editor view only
    bool m_groupDragActive = false;
    QPoint m_groupDragStartView;
    QHash<int, QPointF> m_groupDragStarts; // original world positions, keyed by resource
    QPoint m_panLastPos;
    bool m_marqueeSelecting = false;
    bool m_marqueeAdditive = false;
    QPoint m_marqueeStartView;
    QPointF m_marqueeStartScene;
    QGraphicsRectItem *m_marqueeRect = nullptr; // non-owning; scene owns items
    QLabel *m_imageInfo = nullptr;
    QLabel *m_palettePreview = nullptr;
    SidboxGameAudioPanel *m_audioPanel = nullptr;
    QLineEdit *m_propName = nullptr;
    QLabel *m_propFile = nullptr;
    QComboBox *m_zoom = nullptr;
    QCheckBox *m_grid = nullptr;
    QPushButton *m_deleteButton = nullptr;
    QPushButton *m_exportCButton = nullptr;
    QVector<QGraphicsItem *> m_sceneItems;
    struct CachedImage {
        QImage image;
        QDateTime modified;
        qint64 diskSize = -1;
        qint64 memoryBytes = 0;
    };
    struct CachedPalette {
        QVector<QRgb> colours;
        QDateTime modified;
        qint64 diskSize = -1;
    };
    mutable QHash<QString, CachedPalette> m_paletteCache;
    mutable QHash<QString, CachedImage> m_imageCache;
    mutable QStringList m_imageCacheOrder;
    mutable qint64 m_imageCacheBytes = 0;
    bool m_pngConversionRunning = false;
};

#endif // SIDBOX_GAMEDESIGNER_H

#ifndef SIDBOX_GAMEDESIGNER_H
#define SIDBOX_GAMEDESIGNER_H

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QString>
#include <QHash>
#include <QDateTime>
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
    QString filePath() const;
    void setFilePath(const QString &newPath);
    QString displayName() const;
    bool isModified() const;
    bool isValid() const;
    bool saveDesign();
    bool tilemapBuildFilesMissing() const;
    bool exportTilemapForCompile();
    void setTheme(const IDETheme &theme);

protected:
    void changeEvent(QEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    struct Resource {
        QString name;
        QString id;   // stable identifier for active palette selection
        QString plane = QStringLiteral("foreground");
        QString kind;
        QString path;
        int x = 0;
        int y = 0;
        int scale = 100;
        int cellWidth = 0;  // 0 = whole image (old Stage 52 files stay compatible)
        int cellHeight = 0;
        int frame = 0;
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
        bool objectInitiallyActive = true; // Default for all old designs.
        QString targetObjectId; // Stable resource ID; never a tree index or name.
        QString targetAction = QStringLiteral("none"); // enable, disable, toggle.
        bool triggerPress = false; // false = touch to activate, true = BTN_FIRE2.
        bool triggerOneShot = false; // Destroy/hide trigger after firing.
        QString triggerMusicId; // Stable ID of music tree resource; empty means no chosen track.
        QString triggerMusicAction = QStringLiteral("none"); // none, play, stop.
        // Stage 3.12: sound references are stable IDs of Sounds in Game Resources.
        // Empty ID = no sound. They are NEVER hard-coded filesystem paths.
        QString sfxPickup, sfxRespawn, sfxStart, sfxMove, sfxStop;
        QString sfxReverse, sfxSpring, sfxAmbient;
        int respawnFrames = 0;       // 0 = collected permanently.
        int audioRadius = 0;         // 0 = fixed volume/pan; otherwise attenuation in pixels.
        int audioFadeFrames = 8;     // Fade of continuously moving/ambient sounds.
        QString objectSplineId; // stable spline ID, not name/array position
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
    void openTilemapEditor();
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
    void copySelectedSprite();
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
    void updateGameProject();
    bool generateGameCodeCore(bool embedPixels, bool batchMode);
    void configureGameObject(int index);
    void refreshObjectHitbox();
    bool installMissingWorldHelpers(QString *error, bool prompt = true);
    bool exportWorldItems(QString *error);
    bool exportExampleMain(QString *error);
    void offerCreateStarterMain();
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
    bool m_dirty = false;
    bool m_valid = true;
    bool m_loading = false;
    bool m_syncSelection = false;
    QGraphicsScene *m_scene = nullptr;
    QGraphicsView *m_view = nullptr;
    QGraphicsRectItem *m_cameraFrame = nullptr;
    QGraphicsRectItem *m_worldFrame = nullptr;
    QGraphicsItem *m_tilemapOverlayItem = nullptr;
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
    QComboBox *m_propPlane = nullptr;
    QComboBox *m_propBackgroundMode = nullptr;
    QComboBox *m_planeMode = nullptr;
    QCheckBox *m_showLabels = nullptr;
    QCheckBox *m_showTilemap = nullptr;
    QCheckBox *m_forcePalette = nullptr;
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
    Resource m_copiedSprite;
    bool m_hasCopiedSprite = false;
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

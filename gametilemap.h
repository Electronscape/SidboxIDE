#ifndef SIDBOX_GAMETILEMAP_H
#define SIDBOX_GAMETILEMAP_H

#include <QByteArray>
#include <QDialog>
#include <QImage>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QString>
#include <QVector>
#include <QPair>
#include <QPoint>
#include <QRect>
#include <QtGlobal>
#include <QElapsedTimer>
#include <functional>
#include "idetheme.h"

// One shared definition for every map cell that uses the same graphic ID.
// Atlas frames are consecutive, starting at graphicId (1-based).
struct SidboxTileAnimation {
    int graphicId = 1;
    int frames = 2;
    int frameTicks = 5; // VBlanks per animation frame, normally 50 VBlanks/sec
    bool loop = true;
    bool bounce = false;
};

// Reusable *design-time* metatile. Painting a stamp writes normal cells into
// the tilemap; the V1 game engine never has to know a stamp existed.
struct SidboxTileStamp {
    QString name;
    int width = 2;
    int height = 2;
    int tileSize = 8;
    QByteArray graphics = QByteArray(8, char(0)); // 16-bit LE graphic IDs
    QByteArray collisions = QByteArray(4, char(0));
    QByteArray flips = QByteArray(4, char(0)); // bit 0=X, bit 1=Y
    void resizeStamp(int w, int h);
};

// Point-based collision shape. Coordinates are local PIXELS, ascending X.
// The first and last points are fixed to the stamp's left/right boundaries.
// All placements refer to this definition; graphics are stored separately.
struct SidboxCollisionStamp {
    QString name;
    int width = 2;
    int height = 2;
    int tileSize = 8;
    QVector<QPoint> points; // at least two: (0,y) ... (width*tileSize,y)
    bool passiveSurface = false; // opt in: project gravity along the shape, per stamp
    int dampingPercent = 2; // 0=free slide, 100=strong resistance; ignored unless enabled
    void resizeStamp(int w, int h);
};

struct SidboxCollisionPlacement {
    int stamp = 0; // index into collisionStamps
    int x = 0; // tile-grid coordinates
    int y = 0;
    bool mirrorX = false;
};

/* Level-only circular physics tracks. Not a collision tile: the player
 * is guided around the circle while moving fast enough, and drops back
 * to ordinary tile physics if speed is insufficient. World PIXEL units. */
struct SidboxLoopTrack {
    int stamp = -1; // global loop definition index; -1 for old, unmigrated designs
    int centerX = 0;
    int centerY = 0;
    int radius = 64;
    int entrySpeed100 = 400; // 4 px/frame
    int downhillBoost100 = 0; // Extra speed per downhill frame, 100 = +1 px/frame; zero = legacy physics
    bool coastAfterExit = false; // After a completed lap, ignore ordinary drag until wall or left/right input
    int coastFalloffPermille = 0; // Optional exit coast decay: 0..200 = 0.0..20.0% per 50Hz frame
};

// Long levels are supported without changing the SD .map header: widths and
// heights are already uint16_t. Limit the *area* to keep SIDBOX SDRAM usage
// bounded (2048 x 128 cells is a useful side-scrolling example).
constexpr int SIDBOX_MAP_MAX_AXIS = 4096;
constexpr int SIDBOX_MAP_MAX_CELLS = 262144;

// Editor graphics IDs use uint16_t (little-endian packed storage).
// The collision map remains uint8_t, and the V1 renderer stays independent.
struct SidboxTilemap {
    int width = 100;
    int height = 100;
    int tileSize = 16;
    QString atlasPath; // relative to the .sbgm document
    int viewPanX = 0; // Tile editor viewport top-left in WORLD pixels, saved to .sbgm
    int viewPanY = 0; // Independent of the IDE-wide zoom preference
    // Tile-editor sizing reference ONLY. Never used by game runtime or player spawn.
    bool referencePlayerPositionSet = false;
    int referencePlayerX = 0; // world pixels, sprite top-left
    int referencePlayerY = 0;
    QByteArray graphics = QByteArray(20000, char(0)); // 2 bytes per cell (LE uint16_t)
    QByteArray collisions = QByteArray(10000, char(0));
    QByteArray flips = QByteArray(10000, char(0)); // 0x01=flip X, 0x02=flip Y
    QStringList customZoneNames; /* 8 optional design names; exported as level1.h C aliases */
    QVector<SidboxTileAnimation> animations;
    QVector<SidboxTileStamp> stamps;
    // Editor/project-only banks, keyed by the relative PPB atlas path.
    // .sbgm worlds never store these banks; switching atlases switches banks.
    QJsonObject tileStampBanks;
    QVector<SidboxCollisionStamp> collisionStamps;
    // Editor-only: for each current collision stamp, its index in the bank
    // when this world opened. -1 means a newly created stamp. Undo copies it.
    // Used to remap the OTHER worlds when a global definition is removed.
    QVector<int> collisionOriginalIndices;
    QVector<SidboxCollisionPlacement> collisionPlacements;
    QVector<SidboxLoopTrack> loops; /* level placements with resolved shared definitions */
    QVector<SidboxLoopTrack> loopStamps; /* project-global definitions, centres ignored */
    QByteArray slopes = QByteArray(10000 * 16, char(0)); // tileSize bytes/cell, custom type 7

    void resizeMap(int w, int h);
    static QJsonArray stampsToJson(const QVector<SidboxTileStamp> &stamps);
    static bool stampsFromJson(const QJsonArray &items, QVector<SidboxTileStamp> *output);
    QJsonObject toJson() const;
    bool fromJson(const QJsonObject &object);
};

class QComboBox;
class QLabel;
class QEvent;
class QKeyEvent;
class QSpinBox;
class QCheckBox;
class QToolButton;
class QFrame;
class QPushButton;
class QTimer;
class QSplitter;
class QListWidget;
class QLineEdit;
class QTabWidget;
class QStackedWidget;
class QScrollArea;
class QSlider;

class SidboxTilemapEditor final : public QDialog
{
public:
    // Asset pair = friendly resource name, absolute PPB path.
    SidboxTilemapEditor(SidboxTilemap map,
                        const QVector<QPair<QString, QString>> &atlases,
                        const QString &designDirectory,
                        QWidget *parent = nullptr);
    SidboxTilemap result() const { return m_map; }
    void setTheme(const IDETheme &theme);
    // Optional overlay uses the *same* sprite resource as generated player physics.
    // The reference can move independently of that resource's World Editor position.
    void setPlayerReference(const QImage &spriteFrame, int scalePercent,
                            const QPoint &worldPosition,
                            const QRect &hitbox = QRect());
    // Commit the editor's current working copy to the parent project without closing.
    void setSaveCallback(const std::function<bool(const SidboxTilemap &)> &callback);
    // Called after the IDE commits the global bank; resets temporary index
    // mappings and history so the next Save starts from the new bank.
    void acknowledgeGlobalStampSave();
    void syncCommittedTileStampBanks(const QJsonObject &banks);
protected:
    bool eventFilter(QObject *target, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void done(int result) override;
private:
    class Canvas;
    class StampCanvas;
    class CollisionCanvas;
    SidboxTilemap m_map;
    QImage m_atlas;
    QString m_designDirectory;
    Canvas *m_canvas = nullptr;
    StampCanvas *m_stampCanvas = nullptr;
    CollisionCanvas *m_collisionCanvas = nullptr;
    QListWidget *m_collisionList = nullptr;
    QPushButton *m_removeCollisionStamp = nullptr;
    QStackedWidget *m_collisionViews = nullptr;
    QTabWidget *m_stampTabs = nullptr;
    QLineEdit *m_collisionName = nullptr;
    QSpinBox *m_collisionWidth = nullptr;
    QSpinBox *m_collisionHeight = nullptr;
    QCheckBox *m_collisionPassive = nullptr;
    QSpinBox *m_collisionDamping = nullptr;
    QSlider *m_collisionDampingSlider = nullptr;
    SidboxTilemap m_collisionDampingStart;
    bool m_collisionDampingDragging = false;
    QLabel *m_collisionPointLabel = nullptr;
    QSpinBox *m_collisionPointX = nullptr;
    QSpinBox *m_collisionPointY = nullptr;
    QPushButton *m_collisionInsertPoint = nullptr;
    QPushButton *m_collisionDeletePoint = nullptr;
    QListWidget *m_stampList = nullptr;
    QLabel *m_stampStatus = nullptr;
    QLabel *m_saveStatus = nullptr;
    QLabel *m_cellStatus = nullptr;
    QPushButton *m_findLegacyButton = nullptr;
    int m_lastLegacyIndex = -1;
    QPushButton *m_saveButton = nullptr;
    QFrame *m_playerToolsDivider = nullptr;
    QToolButton *m_playerReferenceToggle = nullptr;
    QToolButton *m_playerCollisionToggle = nullptr;
    std::function<bool(const SidboxTilemap &)> m_saveCallback;
    QLineEdit *m_stampName = nullptr;
    QSpinBox *m_stampWidth = nullptr;
    QSpinBox *m_stampHeight = nullptr;
    QSplitter *m_splitter = nullptr;
    QLabel *m_atlasPicker = nullptr;
    QScrollArea *m_atlasArea = nullptr;
    int m_atlasDisplayColumns = 1;
    void saveViewSettings();
    QLabel *m_animationPreview = nullptr;
    QLabel *m_animationStatus = nullptr;
    QSpinBox *m_animFrames = nullptr;
    QSpinBox *m_animDelay = nullptr;
    QCheckBox *m_animLoop = nullptr;
    QCheckBox *m_animBounce = nullptr;
    QPushButton *m_removeAnimation = nullptr;
    QTimer *m_animationTimer = nullptr;
    QElapsedTimer m_animationClock;
    QComboBox *m_graphicMode = nullptr;
    QToolButton *m_graphicKeep = nullptr;
    QToolButton *m_graphicEmpty = nullptr;
    QToolButton *m_graphicAtlas = nullptr;
    QToolButton *m_collisionKeep = nullptr;
    QToolButton *m_collisionEmpty = nullptr;
    QComboBox *m_customZoneBrush = nullptr;
    void updateCustomZoneBrushLabels();
    QComboBox *m_flipMode = nullptr;
    QToolButton *m_flagApply = nullptr;
    QToolButton *m_flagKeep = nullptr;
    QToolButton *m_flipX = nullptr;
    QToolButton *m_flipY = nullptr;
    QToolButton *m_drawFront = nullptr;
    QToolButton *m_stampUseFront = nullptr;
    QToolButton *m_stampMirrorX = nullptr;
    QToolButton *m_stampMirrorY = nullptr;
    QComboBox *m_tileSizeCombo = nullptr;
    QComboBox *m_atlasCombo = nullptr;
    QSpinBox *m_sizeX = nullptr;
    QSpinBox *m_sizeY = nullptr;
    QPushButton *m_undoButton = nullptr;
    QPushButton *m_redoButton = nullptr;
    QVector<SidboxTilemap> m_undoStack;
    QVector<SidboxTilemap> m_redoStack;
    SidboxTilemap m_strokeStart;
    // Transaction for the open Collision Stamp Editor. Cancel restores both
    // the map data and undo history to their state at editor entry.
    SidboxTilemap m_collisionEditBefore;
    QVector<SidboxTilemap> m_collisionEditUndoBefore;
    QVector<SidboxTilemap> m_collisionEditRedoBefore;
    bool m_collisionEditActive = false;
    int m_collisionEditIndex = -1;
    QString m_collisionEditStatusBefore;
    void finishCollisionStampEdit(bool accept);
    void recordChange(const SidboxTilemap &before);
    void updateHistoryActions();
    void updateCellStatus();
    void updateLegacyStatus();
    void restoreMap(const SidboxTilemap &snapshot);
    void undoEdit();
    void redoEdit();
    void setAtlas(const QString &absolutePath, bool switchBank = true);
    void updateAtlasPicker();
    void updateStampList(int row = -2);
    void updateStampEditor();
    void selectStamp(int row);
    bool resizeSelectedCollisionStamp(int width, int height);
    void updateCollisionList(int wantedRow = -2);
    void updateCollisionEditorControls();
    void updateCollisionPointControls();
    void selectCollisionStamp(int row);
    void openCollisionStampEditor(int row);
    void updateAnimationControls();
    void updateAnimationPreview();
    void saveSelectedAnimation();
    void removeSelectedAnimation();
};

// Returns the per-project C symbol for logical custom zone 1..8.
// The matching #defines are generated in the exported gamelevels/<world>.h;
// engine-wide gametilemap.h is deliberately NOT rewritten for zone names.
QString sidboxTilemapZoneMacroName(const SidboxTilemap &map, int zone);

// Derive the exported world base name from the .sbgm design file.
// Result is sanitised to a legal C/file identifier and falls back to "level1".
QString sidboxTilemapWorldBaseName(const QString &designFilePath);

// The IDE stages world-specific output outside the project root, then publishes
// it to worlds/<world>/gamelevels/. Atlas paths and shared runtime helpers still
// resolve against designDirectory. Standalone exporters may omit outputDirectory.
bool sidboxExportTilemap(const SidboxTilemap &map, const QString &designDirectory,
                         QString *error, bool externalMap = false,
                         const QString &designFilePath = QString(),
                         const QString &rulesDirectory = QString(),
                         const QString &outputDirectory = QString());

#endif

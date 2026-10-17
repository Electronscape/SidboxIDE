#ifndef SIDBOX_GAMETILEMAP_H
#define SIDBOX_GAMETILEMAP_H

#include <QByteArray>
#include <QDialog>
#include <QImage>
#include <QJsonObject>
#include <QString>
#include <QVector>
#include <QPair>
#include <QPoint>
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
    void resizeStamp(int w, int h);
};

struct SidboxCollisionPlacement {
    int stamp = 0; // index into collisionStamps
    int x = 0; // tile-grid coordinates
    int y = 0;
    bool mirrorX = false;
};

// Editor graphics IDs use uint16_t (little-endian packed storage).
// The collision map remains uint8_t, and the V1 renderer stays independent.
struct SidboxTilemap {
    int width = 100;
    int height = 100;
    int tileSize = 16;
    QString atlasPath; // relative to the .sbgm document
    QByteArray graphics = QByteArray(20000, char(0)); // 2 bytes per cell (LE uint16_t)
    QByteArray collisions = QByteArray(10000, char(0));
    QByteArray flips = QByteArray(10000, char(0)); // 0x01=flip X, 0x02=flip Y
    QVector<SidboxTileAnimation> animations;
    QVector<SidboxTileStamp> stamps;
    QVector<SidboxCollisionStamp> collisionStamps;
    QVector<SidboxCollisionPlacement> collisionPlacements;
    QByteArray slopes = QByteArray(10000 * 16, char(0)); // tileSize bytes/cell, custom type 7

    void resizeMap(int w, int h);
    QJsonObject toJson() const;
    bool fromJson(const QJsonObject &object);
};

class QComboBox;
class QLabel;
class QEvent;
class QKeyEvent;
class QSpinBox;
class QCheckBox;
class QPushButton;
class QTimer;
class QSplitter;
class QListWidget;
class QLineEdit;
class QTabWidget;
class QScrollArea;

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
    // Commit the editor's current working copy to the parent project without closing.
    void setSaveCallback(const std::function<bool(const SidboxTilemap &)> &callback);
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
    QTabWidget *m_stampTabs = nullptr;
    QLineEdit *m_collisionName = nullptr;
    QSpinBox *m_collisionWidth = nullptr;
    QSpinBox *m_collisionHeight = nullptr;
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
    std::function<bool(const SidboxTilemap &)> m_saveCallback;
    QLineEdit *m_stampName = nullptr;
    QSpinBox *m_stampWidth = nullptr;
    QSpinBox *m_stampHeight = nullptr;
    QSplitter *m_splitter = nullptr;
    QLabel *m_atlasPicker = nullptr;
    QScrollArea *m_atlasArea = nullptr;
    int m_atlasDisplayColumns = 1;
    QString m_viewSettingsKey;
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
    QComboBox *m_flipMode = nullptr;
    QCheckBox *m_flipX = nullptr;
    QCheckBox *m_flipY = nullptr;
    QCheckBox *m_drawFront = nullptr;
    QCheckBox *m_stampUseFront = nullptr;
    QCheckBox *m_stampMirrorX = nullptr;
    QCheckBox *m_stampMirrorY = nullptr;
    QComboBox *m_tileSizeCombo = nullptr;
    QComboBox *m_atlasCombo = nullptr;
    QSpinBox *m_sizeX = nullptr;
    QSpinBox *m_sizeY = nullptr;
    QPushButton *m_undoButton = nullptr;
    QPushButton *m_redoButton = nullptr;
    QVector<SidboxTilemap> m_undoStack;
    QVector<SidboxTilemap> m_redoStack;
    SidboxTilemap m_strokeStart;
    void recordChange(const SidboxTilemap &before);
    void updateHistoryActions();
    void updateCellStatus();
    void updateLegacyStatus();
    void restoreMap(const SidboxTilemap &snapshot);
    void undoEdit();
    void redoEdit();
    void setAtlas(const QString &absolutePath);
    void updateAtlasPicker();
    void updateStampList(int row = -2);
    void updateStampEditor();
    void selectStamp(int row);
    bool resizeSelectedCollisionStamp(int width, int height);
    void updateCollisionList(int wantedRow = -2);
    void updateCollisionEditorControls();
    void updateCollisionPointControls();
    void selectCollisionStamp(int row);
    void updateAnimationControls();
    void updateAnimationPreview();
    void saveSelectedAnimation();
    void removeSelectedAnimation();
};

// Exported level data always lives in gamelevels/. This function does not
// create helper templates, modify gameassets, or touch main.c.
bool sidboxExportTilemap(const SidboxTilemap &map, const QString &designDirectory,
                         QString *error, bool externalMap = false);

#endif

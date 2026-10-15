#ifndef SIDBOX_GAMEDESIGNER_H
#define SIDBOX_GAMEDESIGNER_H

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QString>
#include <QHash>
#include <QDateTime>
#include <QPoint>
#include <QStringList>
#include "gameaudio.h"
#include "gamepalette.h"
#include "gametilemap.h"
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
    void rebuildSplineOverlay();
    void updateSplineCurve();
    bool exportSplinePaths(bool showMessage);
    void openTilemapEditor();
    bool exportTilemap(bool showMessage);
    struct SplinePath {
        QString name;
        QVector<QPoint> points;
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
    void importPngAsPpb();
    void exportSelectedC();
    void generateGameCode();
    void updateSelectedPixmap();
    QImage resourcePreview(const Resource &resource, QString *details = nullptr) const;
    QImage cachedImage(const QString &path, QString *error = nullptr) const;
    void updateSelectedItem();
    void syncFromSceneItem(QGraphicsItem *item);
    void refreshColours();
    int selectedIndex() const;
    QString resolvedPath(const QString &storedPath) const;
    QString storedPath(const QString &absolutePath) const;

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
    QGraphicsPathItem *m_splineCurveItem = nullptr;
    QVector<QGraphicsItem *> m_splineHandleItems;
    QVector<SplinePath> m_splinePaths;
    int m_activeSpline = -1;
    SidboxTilemap m_tilemap;
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
    bool m_panningCamera = false;
    QPoint m_panLastPos;
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

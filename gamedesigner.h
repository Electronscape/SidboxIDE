#ifndef SIDBOX_GAMEDESIGNER_H
#define SIDBOX_GAMEDESIGNER_H

#include <QWidget>
#include <QImage>
#include <QVector>
#include <QString>
#include <QHash>
#include <QDateTime>
#include <QStringList>
#include <functional>

class QGraphicsScene;
class QGraphicsView;
class QGraphicsItem;
class QGraphicsRectItem;
class QTreeWidget;
class QTreeWidgetItem;
class QSpinBox;
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

private:
    struct Resource {
        QString name;
        QString kind;
        QString path;
        int x = 0;
        int y = 0;
        int scale = 100;
        int cellWidth = 0;  // 0 = whole image (old Stage 52 files stay compatible)
        int cellHeight = 0;
        int frame = 0;
    };

    void buildUi();
    bool loadDesign();
    void setDirty(bool dirty = true);
    void refreshResources();
    void rebuildScene();
    void refreshFrame();
    void refreshProperties();
    void selectResource(int index);
    void addResource(const QString &kind);
    void addPlaceholder();
    void deleteSelectedResource();
    void pickResourceFile();
    void importPngAsPpb();
    void exportSelectedC();
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
    QTreeWidget *m_resourceTree = nullptr;
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
    QLabel *m_imageInfo = nullptr;
    QLabel *m_palettePreview = nullptr;
    QLineEdit *m_propName = nullptr;
    QLabel *m_propFile = nullptr;
    QComboBox *m_zoom = nullptr;
    QCheckBox *m_grid = nullptr;
    QPushButton *m_deleteButton = nullptr;
    QVector<QGraphicsItem *> m_sceneItems;
    struct CachedImage {
        QImage image;
        QDateTime modified;
        qint64 diskSize = -1;
        qint64 memoryBytes = 0;
    };
    mutable QHash<QString, CachedImage> m_imageCache;
    mutable QStringList m_imageCacheOrder;
    mutable qint64 m_imageCacheBytes = 0;
    QPushButton *m_importPpbButton = nullptr;
};

#endif // SIDBOX_GAMEDESIGNER_H

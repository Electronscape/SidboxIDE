#ifndef SIDBOX_GAMETILEMAP_H
#define SIDBOX_GAMETILEMAP_H

#include <QByteArray>
#include <QDialog>
#include <QImage>
#include <QJsonObject>
#include <QString>
#include <QVector>
#include <QPair>
#include <QtGlobal>
#include <QElapsedTimer>

// One shared definition for every map cell that uses the same graphic ID.
// Atlas frames are consecutive, starting at graphicId (1-based).
struct SidboxTileAnimation {
    int graphicId = 1;
    int frames = 2;
    int frameTicks = 5; // VBlanks per animation frame, normally 50 VBlanks/sec
    bool loop = true;
    bool bounce = false;
};

// The map is entirely editor-side. The V1 game receives two compact byte
// arrays (art and collision) and a separate reusable C renderer.
struct SidboxTilemap {
    int width = 100;
    int height = 100;
    int tileSize = 16;
    QString atlasPath; // relative to the .sbgm document
    QByteArray graphics = QByteArray(10000, char(0));
    QByteArray collisions = QByteArray(10000, char(0));
    QVector<SidboxTileAnimation> animations;

    void resizeMap(int w, int h);
    QJsonObject toJson() const;
    bool fromJson(const QJsonObject &object);
};

class QComboBox;
class QLabel;
class QEvent;
class QSpinBox;
class QCheckBox;
class QPushButton;
class QTimer;

class SidboxTilemapEditor final : public QDialog
{
public:
    // Asset pair = friendly resource name, absolute PPB path.
    SidboxTilemapEditor(SidboxTilemap map,
                        const QVector<QPair<QString, QString>> &atlases,
                        const QString &designDirectory,
                        QWidget *parent = nullptr);
    SidboxTilemap result() const { return m_map; }
protected:
    bool eventFilter(QObject *target, QEvent *event) override;
    void done(int result) override;
private:
    class Canvas;
    SidboxTilemap m_map;
    QImage m_atlas;
    QString m_designDirectory;
    Canvas *m_canvas = nullptr;
    QLabel *m_atlasPicker = nullptr;
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
    void setAtlas(const QString &absolutePath);
    void updateAtlasPicker();
    void updateAnimationControls();
    void updateAnimationPreview();
    void saveSelectedAnimation();
    void removeSelectedAnimation();
};

// Exported level data always lives in gamelevels/. This function does not
// create helper templates, modify gameassets, or touch main.c.
bool sidboxExportTilemap(const SidboxTilemap &map, const QString &designDirectory,
                         QString *error);

#endif

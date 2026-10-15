#ifndef SIDBOX_GAMETILEMAP_H
#define SIDBOX_GAMETILEMAP_H

#include <QByteArray>
#include <QDialog>
#include <QImage>
#include <QJsonObject>
#include <QString>
#include <QVector>
#include <QPair>

// The map is entirely editor-side. The V1 game receives two compact byte
// arrays (art and collision) and a separate reusable C renderer.
struct SidboxTilemap {
    int width = 100;
    int height = 100;
    int tileSize = 16;
    QString atlasPath; // relative to the .sbgm document
    QByteArray graphics = QByteArray(10000, char(0));
    QByteArray collisions = QByteArray(10000, char(0));

    void resizeMap(int w, int h);
    QJsonObject toJson() const;
    bool fromJson(const QJsonObject &object);
};

class QComboBox;
class QLabel;
class QEvent;

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
    QComboBox *m_graphicMode = nullptr;
    void setAtlas(const QString &absolutePath);
    void updateAtlasPicker();
};

// Exported level data always lives in gamelevels/. This function does not
// create helper templates, modify gameassets, or touch main.c.
bool sidboxExportTilemap(const SidboxTilemap &map, const QString &designDirectory,
                         QString *error);

#endif

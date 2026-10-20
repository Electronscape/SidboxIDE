#ifndef GAMERGIRL_ADVENTURE_EDITOR_H
#define GAMERGIRL_ADVENTURE_EDITOR_H
#include <QJsonObject>
#include <QString>
#include <QVector>
#include <QColor>
class QWidget;
struct GameAdventureAsset {
    QString id, name, path, symbol;
    int atlasFrames = 1;
    int x = 0, y = 0, width = 16, height = 16;
    int worldSlot = -1;
    int pickupKind = 0;
};
/* Returns true only after pressing OK. In/out payload belongs to .sbgm. */
bool editGameAdventure(QWidget *parent, QJsonObject *payload,
                       const QVector<GameAdventureAsset> &sprites,
                       const QVector<GameAdventureAsset> &atlases,
                       const QVector<GameAdventureAsset> &worldObjects,
                       const QVector<GameAdventureAsset> &collectables,
                       const QVector<QRgb> &foregroundPalette);
#endif

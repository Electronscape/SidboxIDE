#ifndef GAMERGIRL_ADVENTURE_GEN_H
#define GAMERGIRL_ADVENTURE_GEN_H
#include "gameadventureeditor.h"
#include <QJsonObject>
#include <QString>
#include <QVector>
/* Writes regenerated gamehelpers/gameadventure.c/.h. Never touches main.c. */
bool generateGameAdventure(const QJsonObject &payload, const QString &projectRoot,
                           const QVector<GameAdventureAsset> &sprites,
                           const QVector<GameAdventureAsset> &atlases,
                           const QVector<GameAdventureAsset> &worldObjects, QString *error);
#endif

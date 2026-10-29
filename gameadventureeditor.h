#ifndef GAMERGIRL_ADVENTURE_EDITOR_H
#define GAMERGIRL_ADVENTURE_EDITOR_H
#include <QJsonObject>
#include <QString>
#include <QVector>
#include <QColor>
class QWidget;
class QComboBox;
class QJsonArray;
struct GameAdventureAsset {
    QString id, name, path, symbol;
    int atlasFrames = 1;
    int x = 0, y = 0, width = 16, height = 16;
    int worldSlot = -1;
    int pickupKind = 0;
    bool flipX = false, flipY = false;
};
/* Reuse the Adventure Editor's folder-aware searchable dialogue picker in
 * Game Object Properties (and other editor-only UI). Nodes and folders must
 * outlive the returned combo, just like the existing Adventure Editor users.
 * Its itemData remains the original numeric dialogue ID. */
QComboBox *createGameDialogueTreeCombo(QWidget *parent,
                                       const QJsonArray *nodes,
                                       const QJsonArray *folders);

// Open the original Adventure GIVE exchange dialog for one dialogue answer.
// Returns true only for OK. The caller owns persistence to adventure.nodes.
bool editGameAdventureGiveExchange(QWidget *parent, QJsonObject *exchange,
                                   const QJsonArray &items, const QJsonArray &nodes,
                                   const QVector<GameAdventureAsset> &objects,
                                   const QJsonArray &folders);

/* Returns true only after pressing OK. In/out payload belongs to .sbgm. */
bool editGameAdventure(QWidget *parent, QJsonObject *payload,
                       const QVector<GameAdventureAsset> &sprites,
                       const QVector<GameAdventureAsset> &atlases,
                       const QVector<GameAdventureAsset> &worldObjects,
                       const QVector<GameAdventureAsset> &collectables,
                       const QVector<QRgb> &foregroundPalette,
                       const QString &currentDesignFilePath,
                       const QString &focusNpcSpriteId = QString(), int focusDialogueIndex = -1,
                       bool editFocusedDialogueDirectly = false);
#endif

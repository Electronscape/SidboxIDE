#ifndef SIDBOX_GAMEQUESTEDITOR_H
#define SIDBOX_GAMEQUESTEDITOR_H
#include <QString>
class QWidget;
// Project-wide designer. Quests are stored next to .sbgm worlds in
// .codergirl/quests.json; no user-owned C or main.c is edited.
bool editGameQuests(QWidget *parent, const QString &projectRoot, QString *error = nullptr,
                    const QString &selectQuestId = QString());
#endif

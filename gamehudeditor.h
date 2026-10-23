#ifndef CODERGIRL_GAME_HUD_EDITOR_H
#define CODERGIRL_GAME_HUD_EDITOR_H
#include <QString>
class QWidget;
/* Project-wide HUD. Saves gamehud.sbhud and generated gamehelpers/gamehud.c/.h.
   Generated C is disposable; game source main.c is always user-owned. */
bool editGameHud(QWidget *parent, const QString &projectRoot, QString *error = nullptr);
/* Rebuild the project-owned HUD from its saved design during Update Game Project. */
bool regenerateGameHud(const QString &projectRoot, QString *error = nullptr);
#endif

#ifndef SIDBOX_GAME_VISUAL_NODES_H
#define SIDBOX_GAME_VISUAL_NODES_H

#include <QString>
class QWidget;
struct IDETheme;

// Stage 5.166.40: separate .vsgm graph editor. Existing Logic Flow is read-only.
// Returns true only if it changed the corresponding .sbgm design on disk.
bool openGameVisualNodes(QWidget *parent, const QString &vsgmPath, const IDETheme &theme);

#endif

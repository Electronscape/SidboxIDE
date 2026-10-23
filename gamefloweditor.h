#ifndef CODERGIRL_GAME_FLOW_EDITOR_H
#define CODERGIRL_GAME_FLOW_EDITOR_H

#include <QString>
class QWidget;

// Stage 5.50: read-only, design-time flow graph of all saved .sbgm worlds.
// Does not modify the project, generate C or connect to SIDBOX hardware.
void openGameFlowEditor(QWidget *parent, const QString &projectRoot);

#endif

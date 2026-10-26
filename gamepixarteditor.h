#ifndef SIDBOX_GAMEPIXARTEDITOR_H
#define SIDBOX_GAMEPIXARTEDITOR_H

#include <QString>
class QWidget;

bool openGamePixArtEditor(QWidget *parent, const QString &projectRoot, QString *errorOut = nullptr);

#endif

#ifndef SIDBOX_NOTEFLOWEDITOR_H
#define SIDBOX_NOTEFLOWEDITOR_H

#include <QString>
class QWidget;
struct IDETheme;

// Standalone editor-only planning board. The .notef format is never consumed
// by the V1/V2 compilers, game exporter, or GUI runtime.
bool createEmptyNoteFlowFile(const QString &path, QString *error = nullptr);
bool openNoteFlowEditor(QWidget *parent, const QString &path, const IDETheme &theme);

#endif

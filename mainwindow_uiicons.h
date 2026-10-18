#ifndef MAINWINDOW_UIICONS_H
#define MAINWINDOW_UIICONS_H
#include <QIcon>
#include <QString>
// Shared tab icon mapping: used by the main editor and split editor panes.
QIcon editorTabIconForFile(const QString &filePath, int defaultType = 0);
#endif

// Stage 3.70: one mapping for file-type icons across MainWindow compilation units.
#include "mainwindow_uiicons.h"
#include "gameeditoricons.h"
#include <QFileInfo>

QIcon editorTabIconForFile(const QString &filePath,
                           int defaultType)
{
    QString suffix = QFileInfo(filePath).suffix().toLower();

    /*
     * Untitled tabs have no file path yet, so use the same defaultType
     * convention as tabTitleForEditor():
     *   0 = C source, 1 = header, 2 = include.
     */
    if (suffix.isEmpty()) {
        if (defaultType == 1) {
            suffix = QStringLiteral("h");
        } else if (defaultType == 2) {
            suffix = QStringLiteral("inc");
        } else {
            suffix = QStringLiteral("c");
        }
    }

    if (suffix == QStringLiteral("c")
        || suffix == QStringLiteral("uis")
        || suffix == QStringLiteral("cc")
        || suffix == QStringLiteral("cpp")) {
        return gameEditorIcon(QStringLiteral("tree_file_c.png"));
    }

    if (suffix == QStringLiteral("h")
        || suffix == QStringLiteral("hpp")) {
        return gameEditorIcon(QStringLiteral("tree_file_h.png"));
    }

    if (suffix == QStringLiteral("inc")) {
        return gameEditorIcon(QStringLiteral("tree_file_inc.png"));
    }

    if (suffix == QStringLiteral("res")) {
        return gameEditorIcon(QStringLiteral("tree_file_res.png"));
    }

    if (suffix == QStringLiteral("txt")) {
        return gameEditorIcon(QStringLiteral("tree_file_txt.png"));
    }

    if (suffix == QStringLiteral("sbui")) {
        return gameEditorIcon(QStringLiteral("tree_guidesigner.png"));
    }

    if (suffix == QStringLiteral("sbgm")) {
        return gameEditorIcon(QStringLiteral("toolbar_gamedesigner.png"));
    }

    if (suffix == QStringLiteral("md")) {
        return gameEditorIcon(QStringLiteral("tree_file_md.png"));
    }

    return gameEditorIcon(QStringLiteral("tree_file_unknown.png"));
}

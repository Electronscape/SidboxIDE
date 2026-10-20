#ifndef SIDBOX_GAMEEDITORICONS_H
#define SIDBOX_GAMEEDITORICONS_H

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QIcon>
#include <QStringList>
#include <QUrl>

// Optional user artwork: first load from an external icons/ directory.
// Without a matching PNG the original Qt resource or drawn glyph is retained.
// The IDE reads overrides when the editor is opened; restart to reload icons.
inline QString gameEditorIconOverride(const QString &fileName)
{
    if (fileName.isEmpty() || fileName.contains(QLatin1Char('/')) ||
        fileName.contains(QLatin1Char('\\'))) return {};
    const QDir executable(QCoreApplication::applicationDirPath());
    const QStringList directories = {
        executable.filePath(QStringLiteral("icons")),
        executable.filePath(QStringLiteral("../icons")),
        executable.filePath(QStringLiteral("../../icons")),
        QDir::current().filePath(QStringLiteral("icons")),
        QDir::current().filePath(QStringLiteral("SidboxIDE/icons"))
    };
    for (const QString &folder : directories) {
        const QString candidate = QDir(folder).filePath(fileName);
        if (QFileInfo(candidate).isFile()) return candidate;
    }
    return {};
}

inline QIcon gameEditorIcon(const QString &fileName)
{
    const QString external = gameEditorIconOverride(fileName);
    return !external.isEmpty() ? QIcon(external)
                               : QIcon(QStringLiteral(":/icons/") + fileName);
}

inline QIcon gameEditorExternalIcon(const QString &fileName)
{
    const QString external = gameEditorIconOverride(fileName);
    return external.isEmpty() ? QIcon() : QIcon(external);
}

inline QString gameEditorIconUrl(const QString &fileName)
{
    const QString file = gameEditorIconOverride(fileName);
    return file.isEmpty() ? QStringLiteral(":/icons/") + fileName
                          : QUrl::fromLocalFile(file).toString();
}

inline QString gameEditorCheckmarkUrl()
{
    return gameEditorIconUrl(QStringLiteral("checkbox_tick.png"));
}

#endif

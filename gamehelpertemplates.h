#ifndef GAMERGIRL_GAME_HELPER_TEMPLATES_H
#define GAMERGIRL_GAME_HELPER_TEMPLATES_H

// Stage 4.42: strict, editor-side renderer for idelibs/codehelpers/game.
// Templates are source inputs; never copy an unresolved @IDE{...} into a game.
// This header is intentionally self-contained so both Update Game Project and
// first-time helper installation use precisely the same rendering rules.
#include <QJsonObject>
#include <QJsonArray>
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QRegularExpression>
#include <QString>
#include <QByteArray>
#include <algorithm>

namespace GameHelperTemplates {

// A .rulec/.ruleh file is a template, never a compilable project file.
// The emitted output remains game<helper>.c/.h. Other game helpers can
// continue using ordinary .c/.h until we migrate them one by one.
inline QString sourcePath(const QDir &folder, const QString &helper,
                          const QString &extension)
{
    const QString rule = extension == QStringLiteral(".c") ? QStringLiteral(".rulec")
                       : extension == QStringLiteral(".h") ? QStringLiteral(".ruleh")
                       : extension;
    const QString rulePath = folder.filePath(helper + rule);
    if (rule != extension && QFileInfo::exists(rulePath)) return rulePath;
    return folder.filePath(helper + extension);
}

inline QMap<QString, QString> valuesFor(const QString &helper,
                                        const QJsonObject &adventure)
{
    QMap<QString, QString> values;
    if (helper == QStringLiteral("adventureruntime")) {
        // Preserve the existing 64-item runtime capacity independently of
        // the current project's inventory count. Other source paths may
        // regenerate gameadventure.c without reinstalling helper files, so
        // shrinking the storage array would cause silent item truncation.
        const int configuredItems = std::clamp(static_cast<int>(
            adventure.value(QStringLiteral("items")).toArray().size()), 0, 64);
        values.insert(QStringLiteral("MAX_ITEMCOUNT"), QStringLiteral("64"));
        values.insert(QStringLiteral("ITEM_COUNT"), QString::number(configuredItems));
        // Current 480x320/8x16 font layout rules. These are runtime limits,
        // not a pixel-font API or a request to resize the dialogue window.
        values.insert(QStringLiteral("GA_COLS"), QStringLiteral("54"));
        values.insert(QStringLiteral("GA_LINES"), QStringLiteral("6"));
        const auto bounded = [&](const char *field, int low, int high, int fallback) {
            return QString::number(std::clamp(adventure.value(QLatin1String(field)).toInt(fallback),
                                              low, high));
        };
        values.insert(QStringLiteral("DIALOG_X"), bounded("dialogX", 0, 479, 20));
        values.insert(QStringLiteral("DIALOG_Y"), bounded("dialogY", 0, 319, 148));
        values.insert(QStringLiteral("DIALOG_WIDTH"), bounded("dialogWidth", 128, 480, 440));
        values.insert(QStringLiteral("DIALOG_HEIGHT"), bounded("dialogHeight", 96, 320, 162));
        values.insert(QStringLiteral("TEXT_COLOUR_INDEX"), bounded("textColourIndex", 0, 255, 15));
        values.insert(QStringLiteral("TEXT_OUTLINE_ENABLED"),
                      adventure.value(QStringLiteral("textOutline")).toBool(false)
                      ? QStringLiteral("1") : QStringLiteral("0"));
        values.insert(QStringLiteral("OUTLINE_COLOUR_INDEX"), bounded("outlineColourIndex", 0, 255, 1));
        values.insert(QStringLiteral("TILE_SIZE"), bounded("tileSize", 4, 32, 8));
        values.insert(QStringLiteral("FRAMES_PER_CHAR"), bounded("framesPerChar", 1, 30, 2));
    }
    return values;
}

inline bool render(const QByteArray &source, const QString &helper,
                   const QString &extension, const QJsonObject &adventure,
                   QByteArray *result, QString *error)
{
    if (!result) {
        if (error) *error = QStringLiteral("No destination supplied for game helper rendering.");
        return false;
    }
    const QMap<QString, QString> fields = valuesFor(helper, adventure);
    QString rendered = QString::fromUtf8(source);
    const QRegularExpression token(QStringLiteral(R"(@IDE\{([^{}]*)\})"));
    auto iter = token.globalMatch(rendered);
    while (iter.hasNext()) {
        const QString name = iter.next().captured(1);
        if (!fields.contains(name)) {
            if (error) *error = QStringLiteral("Unknown @IDE{%1} in %2%3. "
                "Add a validated value in gamehelpertemplates.h before using this placeholder.")
                .arg(name, helper, extension);
            return false;
        }
    }
    // A mistyped or unfinished marker must also fail before files are written.
    if (rendered.contains(QStringLiteral("@IDE{")) &&
        !token.match(rendered).hasMatch()) {
        if (error) *error = QStringLiteral("Malformed @IDE{...} placeholder in %1%2.")
            .arg(helper, extension);
        return false;
    }
    for (auto it = fields.cbegin(); it != fields.cend(); ++it)
        rendered.replace(QStringLiteral("@IDE{%1}").arg(it.key()), it.value());
    if (rendered.contains(QStringLiteral("@IDE{"))) {
        if (error) *error = QStringLiteral("Unresolved or malformed @IDE{...} in %1%2.")
            .arg(helper, extension);
        return false;
    }
    *result = rendered.toUtf8();
    return true;
}

} // namespace GameHelperTemplates
#endif // GAMERGIRL_GAME_HELPER_TEMPLATES_H

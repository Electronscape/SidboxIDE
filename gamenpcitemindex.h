#ifndef GAMERGIRL_NPC_ITEM_INDEX_H
#define GAMERGIRL_NPC_ITEM_INDEX_H
// Design-time discovery only. Never changes NPC dialogue or game item IDs.
#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMap>
#include <QSet>
#include <QStringList>
#include <QVector>
namespace GameNpcItemIndex {
struct Entry { QString name; QStringList requestedBy; };
inline QVector<Entry> requestedItems(const QDir &project) {
    QMap<QString, Entry> found; // Folded item name: unique across every world.
    QDirIterator it(project.absolutePath(), QStringList{QStringLiteral("*.sbgm")},
                    QDir::Files, QDirIterator::Subdirectories);
    while (it.hasNext()) {
        const QString fileName = it.next();
        const QString rel = project.relativeFilePath(fileName);
        const QString normalized = QLatin1Char('/') + QDir::fromNativeSeparators(rel);
        if (normalized.startsWith(QStringLiteral("/.codergirl/"))
            || normalized.startsWith(QStringLiteral("/worlds/"))
            || normalized.startsWith(QStringLiteral("/buildv1/"))) continue;
        QFile input(fileName);
        if (!input.open(QIODevice::ReadOnly)) continue;
        const QJsonDocument doc = QJsonDocument::fromJson(input.readAll());
        if (!doc.isObject()) continue;
        const QJsonObject design = doc.object();
        const QJsonObject adventure = design.value(QStringLiteral("adventure")).toObject();
        const QJsonArray items = adventure.value(QStringLiteral("items")).toArray();
        const QJsonArray nodes = adventure.value(QStringLiteral("nodes")).toArray();
        const QJsonArray npcs = adventure.value(QStringLiteral("npcs")).toArray();
        if (items.isEmpty() || nodes.isEmpty() || npcs.isEmpty()) continue;
        QMap<QString, QString> resourceNames;
        for (const QJsonValue &resource : design.value(QStringLiteral("resources")).toArray()) {
            const QJsonObject obj = resource.toObject();
            resourceNames.insert(obj.value(QStringLiteral("id")).toString(),
                                 obj.value(QStringLiteral("name")).toString());
        }
        const QString world = QFileInfo(fileName).completeBaseName();
        for (int npcIndex = 0; npcIndex < npcs.size(); ++npcIndex) {
            const QJsonObject npc = npcs[npcIndex].toObject();
            const QString spriteId = npc.value(QStringLiteral("spriteId")).toString();
            QString npcName = resourceNames.value(spriteId);
            if (npcName.isEmpty()) npcName = QStringLiteral("NPC %1").arg(npcIndex + 1);
            const QString context = QStringLiteral("%1 / %2").arg(world, npcName);
            QVector<int> pending;
            // NPCs may have an alternate starting node once completed.
            for (const char *field : {"node", "doneNode"}) {
                const int first = npc.value(QLatin1String(field)).toInt(-1);
                if (first >= 0 && first < nodes.size()) pending.append(first);
            }
            QSet<int> visited;
            while (!pending.isEmpty()) {
                const int index = pending.takeLast();
                if (visited.contains(index) || index < 0 || index >= nodes.size()) continue;
                visited.insert(index);
                const QJsonArray choices = nodes[index].toObject()
                    .value(QStringLiteral("choices")).toArray();
                for (const QJsonValue &choiceValue : choices) {
                    const QJsonObject choice = choiceValue.toObject();
                    const int required = choice.value(QStringLiteral("requires")).toInt(-1);
                    if (required >= 0 && required < items.size()) {
                        const QString name = items[required].toObject()
                            .value(QStringLiteral("name")).toString().trimmed();
                        if (!name.isEmpty()) {
                            const QString key = name.toCaseFolded();
                            Entry &entry = found[key];
                            if (entry.name.isEmpty()) entry.name = name;
                            if (!entry.requestedBy.contains(context)) entry.requestedBy << context;
                        }
                    }
                    const int next = choice.value(QStringLiteral("next")).toInt(-1);
                    if (next >= 0 && next < nodes.size() && !visited.contains(next))
                        pending.append(next);
                }
            }
        }
    }
    QVector<Entry> entries;
    for (auto entry = found.cbegin(); entry != found.cend(); ++entry)
        entries.append(entry.value());
    return entries;
}
} // namespace GameNpcItemIndex
#endif

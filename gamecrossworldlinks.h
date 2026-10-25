/* Stage 5.112: stable cross-world Trigger links, design-time only. */
#ifndef CODERGIRL_CROSSWORLD_LINKS_H
#define CODERGIRL_CROSSWORLD_LINKS_H
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
/* Only Trigger links may use this reserved namespace; ordinary UUIDs remain untouched. */
inline QString cgCrossWorldLink(const QString &world, const QString &id)
{ return QStringLiteral("@world/")+world+QLatin1Char('/')+id; }
inline bool cgDecodeCrossWorldLink(const QString &link, QString *world, QString *id)
{
    const QString prefix=QStringLiteral("@world/");
    if (!link.startsWith(prefix)) return false;
    const int split=link.indexOf(QLatin1Char('/'),prefix.size());
    if (split<=prefix.size() || split==link.size()-1) return false;
    const QString w=link.mid(prefix.size(),split-prefix.size());
    const QString target=link.mid(split+1);
    for (const QChar c : w)
        if (!c.isLetterOrNumber() && c!=QLatin1Char('_')) return false;
    if (target.contains(QLatin1Char('/'))) return false;
    if (world) *world=w;
    if (id) *id=target;
    return true;
}
inline int cgCrossWorldObjectSlot(const QJsonObject &design, const QString &id)
{
    int slot=0;
    for (const QJsonValue &v : design.value(QStringLiteral("resources")).toArray()) {
        const QJsonObject r=v.toObject();
        const QJsonObject object=r.value(QStringLiteral("gameObject")).toObject();
        const QString kind=r.value(QStringLiteral("kind")).toString();
        const QString type=object.value(QStringLiteral("type")).toString(QStringLiteral("decoration"));
        if (kind!=QStringLiteral("sprite") || type==QStringLiteral("decoration") ||
            type==QStringLiteral("collectable")) continue;
        if (r.value(QStringLiteral("id")).toString()==id) return slot;
        ++slot;
    }
    return -1;
}
#endif

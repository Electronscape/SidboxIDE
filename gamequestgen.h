#ifndef SIDBOX_GAME_QUEST_GEN_H
#define SIDBOX_GAME_QUEST_GEN_H
// Stage 5.165: validate authored project-wide quests and emit only C data.
// The runtime stays in the generated world-manager rule template.
#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRegularExpression>
#include <QSet>
#include <QString>

namespace GameQuestGen {
inline QString quoteC(const QString &s) {
    QString out=QStringLiteral("\"");
    const QByteArray utf8=s.toUtf8();
    for (unsigned char ch: utf8) {
        if(ch=='\\')out+=QStringLiteral("\\\\");
        else if(ch=='\"')out+=QStringLiteral("\\\"");
        else if(ch>=32 && ch<=126)out+=QChar(ch);
        else out+=QStringLiteral("\\%1").arg((int)ch,3,8,QLatin1Char('0'));
    }
    return out+QLatin1Char('"');
}
// Use the same validation in the editor and the generated world publisher.
// Existing Stage 5.165 UUID-derived quest/objective IDs contain hyphens.
// Preserve them: save games depend on stable quest/objective identities.
inline bool validate(const QJsonArray &quests,QString *error) {
    if(quests.size()>64) {if(error)*error=QStringLiteral("Quest limit is 64.");return false;}
    QSet<QString> ids,stepIds;
    const QRegularExpression idRe(QStringLiteral("^[A-Za-z_][A-Za-z0-9_-]{0,47}$"));
    int count=0;
    for(const auto &qv:quests) {
        const QJsonObject q=qv.toObject();const QString id=q.value("id").toString();
        if(!idRe.match(id).hasMatch() || ids.contains(id) || q.value("title").toString().isEmpty()) {
            if(error)*error=QStringLiteral("Invalid/duplicate quest ID or missing title: %1").arg(id);return false;
        }
        ids.insert(id);
        const QJsonArray steps=q.value("objectives").toArray();
        if(steps.isEmpty()) {if(error)*error=QStringLiteral("Quest %1 has no objectives.").arg(id);return false;}
        count+=steps.size();
        if(count>256) {if(error)*error=QStringLiteral("Objective limit is 256.");return false;}
        for(const auto &ov:steps) {
            const QJsonObject o=ov.toObject();const QString step=o.value("id").toString();
            const QString kind=o.value("kind").toString();
            if(!idRe.match(step).hasMatch() || stepIds.contains(step) ||
               o.value("title").toString().isEmpty() || o.value("target").toString().isEmpty() ||
               (kind!=QStringLiteral("world") && kind!=QStringLiteral("item") && kind!=QStringLiteral("event") && kind!=QStringLiteral("adventure_event") && kind!=QStringLiteral("dialogue_choice"))) {
                if(error)*error=QStringLiteral("Invalid objective in quest %1: %2").arg(id,step);return false;
            }
            if(kind==QStringLiteral("dialogue_choice")) {
                const QString target=o.value("target").toString();
                const int colon=target.indexOf(QLatin1Char(':'));
                if(colon<=0 || !idRe.match(target.left(colon)).hasMatch() ||
                   !idRe.match(target.mid(colon+1)).hasMatch()) {
                    if(error)*error=QStringLiteral("Dialogue choice target must be world:stableChoiceId: %1").arg(target);
                    return false;
                }
            }
            if(kind==QStringLiteral("adventure_event")) {
                const int colon= o.value("target").toString().lastIndexOf(QLatin1Char(':'));
                const QString text=o.value("target").toString();
                const QString world=colon>0?text.left(colon):QString();
                bool ok=false;
                const uint number=text.mid(colon+1).toUInt(&ok);
                if(world.isEmpty() || !idRe.match(world).hasMatch() || !ok || number>65535u) {
                    if(error)*error=QStringLiteral("Adventure event '%1' must be WorldName:0..65535.").arg(text);
                    return false;
                }
            }
            stepIds.insert(step);
        }
    }
    for(const auto &qv:quests) {
        const QJsonObject q=qv.toObject();
        for(const char *key:{"requires","excludes"}) {
            const QString ref=q.value(key).toString();
            if(!ref.isEmpty() && (!ids.contains(ref) || ref==q.value("id").toString())) {
                if(error)*error=QStringLiteral("Quest %1: invalid %2 link '%3'.")
                    .arg(q.value("id").toString(),QLatin1String(key),ref);return false;
            }
        }
        QString cur=q.value("id").toString(); QSet<QString> chain;
        while(!cur.isEmpty()) {
            if(chain.contains(cur)) {if(error)*error=QStringLiteral("Quest prerequisite cycle at %1.").arg(cur);return false;}
            chain.insert(cur);QString next;
            for(const auto &item:quests)if(item.toObject().value("id").toString()==cur)
                next=item.toObject().value("requires").toString();
            cur=next;
        }
    }
    return true;
}
inline bool read(const QDir &project,QJsonArray *quests,QString *error) {
    const QString path=project.filePath(QStringLiteral(".codergirl/quests.json"));
    QFile file(path);
    if (!file.exists()) {*quests=QJsonArray{};return true;}
    if (!file.open(QIODevice::ReadOnly)) {
        if(error)*error=QStringLiteral("Cannot read quest definitions: %1").arg(path);return false;
    }
    QJsonParseError e;
    const auto doc=QJsonDocument::fromJson(file.readAll(),&e);
    if(e.error!=QJsonParseError::NoError || !doc.isObject() ||
       doc.object().value("version").toInt()!=1 ||
       !doc.object().value("quests").isArray()) {
        if(error)*error=QStringLiteral("Invalid quest file: %1").arg(path);return false;
    }
    *quests=doc.object().value("quests").toArray();
    return validate(*quests,error);
}
inline QByteArray generateData(const QJsonArray &quests) {
    QString output;
    QStringList questRows,stepRows;
    int index=0;
    for(const auto &qv:quests) {
        const QJsonObject q=qv.toObject();
        const QJsonArray steps=q.value("objectives").toArray();
        questRows<<QStringLiteral("{%1,%2,%3,%4,%5,%6,%7,%8}")
            .arg(quoteC(q.value("id").toString()),quoteC(q.value("title").toString()),
                 quoteC(q.value("description").toString()),quoteC(q.value("requires").toString()),
                 quoteC(q.value("excludes").toString()),QString::number(index),QString::number(steps.size()),
                 q.value("initiallyHidden").toBool(false)?QStringLiteral("1u"):QStringLiteral("0u"));
        for(const auto &sv:steps) {
            const QJsonObject s=sv.toObject();
            stepRows<<QStringLiteral("{%1,%2,%3,%4,%5}")
                .arg(quoteC(s.value("id").toString()),quoteC(s.value("title").toString()),
                     quoteC(s.value("kind").toString()),quoteC(s.value("target").toString()),
                     quoteC(s.value("hint").toString()));
        }
        index+=steps.size();
    }
    output+=QStringLiteral("#define GW_QUEST_COUNT %1u\n#define GW_OBJECTIVE_COUNT %2u\n")
        .arg(quests.size()).arg(index);
    output+=QStringLiteral("typedef struct { const char *id,*title,*description,*requires,*excludes; uint16_t first,count; uint8_t initially_hidden; } gw_quest_def_t;\n");
    output+=QStringLiteral("typedef struct { const char *id,*title,*kind,*target,*hint; } gw_objective_def_t;\n");
    output+=QStringLiteral("static const gw_quest_def_t gw_quest_defs[] = {\n%1\n};\n")
        .arg(questRows.isEmpty()?QStringLiteral("{0,0,0,0,0,0,0,0}"):questRows.join(QStringLiteral(",\n")));
    output+=QStringLiteral("static const gw_objective_def_t gw_objective_defs[] = {\n%1\n};\n")
        .arg(stepRows.isEmpty()?QStringLiteral("{0,0,0,0,0}"):stepRows.join(QStringLiteral(",\n")));
    return output.toUtf8();
}
}
#endif
